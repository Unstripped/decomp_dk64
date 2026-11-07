#!/usr/bin/env python3
"""Persist in-progress C for functions that do not match yet.

Tracked drafts live in drafts/<segment>/<FUNC>.c, one per (segment, function) that is still
`#pragma GLOBAL_ASM` in src/. Overlays share VRAM 0x80024000, so a splat name such as
`func_80024000` exists in several segments: every draft is keyed by segment AND name. The
first line is a `// <FUNC> (<src file>): <note>` header (closest diff, what was tried); the
rest is the draft C (the function plus the local declarations it needs). .scratch/ stays
the per-session work area; anything worth continuing in a later session goes here.

    python3 tools/drafts.py save SEG FUNC FILE --note "stage N: full=F text=T reloc=R shape=S; ..."  # store/replace a draft
    python3 tools/drafts.py show SEG FUNC                     # print its path and contents
    python3 tools/drafts.py list [SEG]                        # drafts with their notes
    python3 tools/drafts.py collect                           # import newer .scratch/*/<FUNC>_best.c
    python3 tools/drafts.py prune                             # delete drafts of matched functions
    python3 tools/drafts.py paste SEG FUNC                    # put a draft into its src file
    python3 tools/drafts.py unpark SEG FUNC [--note TEXT]     # park -> draft, src back to the bare pragma
    python3 tools/drafts.py note SEG FUNC "stage N: ..."      # prepend a corrected note, keep the history

SEG is the asm directory name: boot, global, or an overlay (boss, jetpac, ...).
`collect` takes the segment of a `.scratch/<Agent>/<FUNC>_best.c` from the private copy of
the source file in the same directory (the one whose GLOBAL_ASM line names
`asm/<seg>/nonmatchings/.../<FUNC>.s`); a name that is unmatched in only one segment needs no
copy. Drafts whose segment can't be determined are reported and skipped, never guessed.
`save` and `collect` refuse a draft containing `#pragma GLOBAL_ASM` lines; they and `paste`
refuse one that defines another function the src file already defines (a saved private copy).
`save` requires a note giving the stage and the deadsweep score (`score=none` when FUNC does not
compile): `tools/ledger.py` reads both. `collect` keeps the note of a `_best.c` that starts
with a `// <FUNC> (...): <note>` header.
`prune` runs after every merge: a function that left GLOBAL_ASM is matched.
`paste` replaces FUNC's `GLOBAL_ASM` line (or the whole `#ifdef NON_MATCHING` park around it)
in its src file with the draft minus its header, for "text-identical, reloc only" reports;
then `tools/merge_gate.sh - - <src file>` prunes duplicated declarations and lets the ROM
hash decide.
`unpark` is the reverse for a `NON_MATCHING` park that must not stay parked (instruction count
differs from the target, or not equivalent): the parked C becomes the draft (header: TEXT, then
the old draft's note) and the block becomes the bare `#pragma GLOBAL_ASM` line again.
`note` puts TEXT (which must name the stage) in front of the header note and keeps the old note
after ` | `, e.g. when an agent's reported stage is wrong (count-inexact "stage 4" is stage 3);
extra `// <FUNC> (...)` header lines left by hand edits are folded into the one header.
"""
import argparse
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DRAFTS = os.path.join(ROOT, "drafts")
PRAGMA = re.compile(r'#pragma GLOBAL_ASM\("asm/(?:(\w+)/)?nonmatchings/[^"]*/(\w+)\.s"\)')  # boot: asm/nonmatchings


def pragmas(text: str):
    """(segment, FUNC) for every GLOBAL_ASM line in a C source text."""
    for m in PRAGMA.finditer(text):
        yield m.group(1) or "boot", m.group(2)


def unmatched() -> dict:
    """(segment, FUNC) -> src path for every GLOBAL_ASM function in src/."""
    out = {}
    for path in glob.glob(os.path.join(ROOT, "src", "**", "*.c"), recursive=True):
        rel = os.path.relpath(path, ROOT)
        for key in pragmas(open(path).read()):
            out[key] = rel
    return out


def draft_path(seg: str, func: str) -> str:
    return os.path.join(DRAFTS, seg, func + ".c")


def stored() -> dict:
    """(segment, FUNC) -> draft path for every stored draft."""
    out = {}
    for p in glob.glob(os.path.join(DRAFTS, "*", "*.c")):
        out[(os.path.basename(os.path.dirname(p)), os.path.basename(p)[:-2])] = p
    return out


# a top-level definition: return type, name, parameter list, then `{` (K&R definitions are missed)
DEFN = re.compile(r'^[A-Za-z_][\w \t*]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{', re.M)


def foreign_definitions(body: str, func: str, src_text: str) -> set:
    """Functions other than FUNC that the draft defines and the source file already defines."""
    return {m.group(1) for m in DEFN.finditer(body)} & {m.group(1) for m in DEFN.finditer(src_text)} - {func}


def write(seg: str, func: str, src_file: str, note: str, todo: dict) -> str:
    owner = todo.get((seg, func))
    if owner is None:
        sys.exit(f"{seg} {func} is not GLOBAL_ASM in src/ (matched, misspelt, or wrong segment)")
    body = open(src_file).read()
    if body.startswith(f"// {func} ("):  # re-saving a stored draft: drop its old header
        body = body.split("\n", 1)[1] if "\n" in body else ""
    if PRAGMA.search(body):
        sys.exit(f"{src_file} contains #pragma GLOBAL_ASM lines: pass a file holding only the "
                 f"{func} draft and the declarations it needs, not your whole private copy")
    other = foreign_definitions(body, func, open(os.path.join(ROOT, owner)).read())
    if other:
        sys.exit(f"{src_file} also defines {', '.join(sorted(other))} (already in {owner}): "
                 f"pass a file holding only the {func} draft and the declarations it needs")
    dest = draft_path(seg, func)
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    with open(dest, "w") as f:
        f.write(f"// {func} ({owner}): {note or 'no note'}\n{body.rstrip()}\n")
    return os.path.relpath(dest, ROOT)


def scratch_segment(path: str, func: str, todo: dict):
    """Segment of a scratch draft, or None when it can't be told."""
    segs = {seg for seg, f in todo if f == func}
    if len(segs) == 1:
        return segs.pop()
    found = set()
    for copy in glob.glob(os.path.join(os.path.dirname(path), "*.c")):
        if copy.endswith("_best.c"):
            continue
        found |= {seg for seg, f in pragmas(open(copy).read()) if f == func}
    # the agent may have matched it in its copy (no pragma left): fall back to the copy's file
    # name, e.g. .scratch/Boss3A/0.c, only when exactly one candidate segment has that file
    if not found:
        names = {os.path.basename(c) for c in glob.glob(os.path.join(os.path.dirname(path), "*.c"))}
        found = {seg for seg in segs if os.path.basename(todo[(seg, func)]) in names}
    return found.pop() if len(found) == 1 else None


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("save")
    s.add_argument("seg")
    s.add_argument("func")
    s.add_argument("file")
    s.add_argument("--note", default="")
    sh = sub.add_parser("show")
    sh.add_argument("seg")
    sh.add_argument("func")
    sub.add_parser("list").add_argument("seg", nargs="?")
    sub.add_parser("collect")
    sub.add_parser("prune")
    pa = sub.add_parser("paste")
    pa.add_argument("seg")
    pa.add_argument("func")
    up = sub.add_parser("unpark")
    up.add_argument("seg")
    up.add_argument("func")
    up.add_argument("--note", default="unparked")
    nt = sub.add_parser("note")
    nt.add_argument("seg")
    nt.add_argument("func")
    nt.add_argument("text")
    args = ap.parse_args()

    if args.cmd == "save":
        if not (re.search(r"stage\s*[1-6]", args.note, re.I)
                and re.search(r"full=\d+ text=\d+ reloc=\d+ shape=\d+|score=none", args.note)):
            sys.exit('note must give the stage and the deadsweep score: "stage N: full=F text=T reloc=R shape=S; '
                     '<what you tried>" (tools/deadsweep.py score), or "stage N: score=none; ..." when FUNC does not compile')
        print(write(args.seg, args.func, args.file, args.note, unmatched()))
    elif args.cmd == "show":
        path = stored().get((args.seg, args.func))
        if not path:
            sys.exit(f"no draft for {args.seg} {args.func}")
        print(os.path.relpath(path, ROOT))
        print(open(path).read(), end="")
    elif args.cmd == "note":
        if not re.search(r"stage\s*[1-6]", args.text, re.I):
            sys.exit('note must name the stage: "stage N: <closest diff, next step>"')
        path = stored().get((args.seg, args.func))
        if not path:
            sys.exit(f"no draft for {args.seg} {args.func}")
        prefix = f"// {args.func} ("
        lines = open(path).read().split("\n")
        head, notes = None, []
        while lines and lines[0].startswith(prefix):
            head, _, old = lines.pop(0).partition("): ")
            notes.append(old)
        if head is None:
            sys.exit(f"{os.path.relpath(path, ROOT)} has no `{prefix}...)` header")
        with open(path, "w") as f:
            f.write(f"{head}): " + " | ".join([args.text] + notes) + "\n" + "\n".join(lines))
        print(os.path.relpath(path, ROOT))
    elif args.cmd == "list":
        for (seg, func), path in sorted(stored().items()):
            if args.seg and seg != args.seg:
                continue
            print(f"{os.path.relpath(path, ROOT)}  {open(path).readline().rstrip()}")
    elif args.cmd == "collect":
        todo, have = unmatched(), stored()
        names = {f for _, f in todo}
        newest = {}
        for p in glob.glob(os.path.join(ROOT, ".scratch", "*", "*_best.c")):
            func = os.path.basename(p)[: -len("_best.c")]
            if func not in names:
                continue
            seg = scratch_segment(p, func, todo)
            if seg is None:
                print(f"skipped {os.path.relpath(p, ROOT)}: segment ambiguous; use `save SEG {func} ...`")
                continue
            key = (seg, func)
            if key not in newest or os.path.getmtime(p) > os.path.getmtime(newest[key]):
                newest[key] = p
        for (seg, func), p in sorted(newest.items()):
            if (seg, func) in have and os.path.getmtime(have[(seg, func)]) >= os.path.getmtime(p):
                continue
            try:
                head = open(p).readline()
                rel = os.path.relpath(p, ROOT)
                note = (head.split("): ", 1)[1].strip() if head.startswith(f"// {func} (") and "): " in head
                        else f"from {rel}")
                print(write(seg, func, p, note, todo))
            except SystemExit as e:
                print(f"skipped: {e}")
    elif args.cmd == "prune":
        todo = unmatched()
        for key, path in sorted(stored().items()):
            if key not in todo:
                os.remove(path)
                print(f"removed {os.path.relpath(path, ROOT)} (matched or not in that segment)")
        for d in glob.glob(os.path.join(DRAFTS, "*")):
            if os.path.isdir(d) and not os.listdir(d):
                os.rmdir(d)
    elif args.cmd == "paste":
        key = (args.seg, args.func)
        src, path = unmatched().get(key), stored().get(key)
        if not src or not path:
            sys.exit(f"{args.seg} {args.func}: {'no draft' if src else 'not GLOBAL_ASM in src/'}")
        body = open(path).read().split("\n", 1)[1].strip("\n") + "\n"
        text = open(src).read()
        other = foreign_definitions(body, args.func, text)
        if other:
            sys.exit(f"{os.path.relpath(path, ROOT)} also defines {', '.join(sorted(other))}, already in {src}: "
                     f"trim the draft to {args.func} and its declarations first")
        line = next(m for m in PRAGMA.finditer(text) if (m.group(1) or "boot", m.group(2)) == key)
        start, end = line.start(), text.index("\n", line.end()) + 1
        park = text.rfind("#ifdef NON_MATCHING\n", 0, start)
        if park != -1 and "#endif" not in text[park:start] and text.startswith("#endif\n", end):
            start, end = park, end + len("#endif\n")
        with open(src, "w") as f:
            f.write(text[:start] + body + text[end:])
        print(f"pasted {os.path.relpath(path, ROOT)} into {os.path.relpath(src, ROOT)}")
    elif args.cmd == "unpark":
        key = (args.seg, args.func)
        src = unmatched().get(key)
        if not src:
            sys.exit(f"{args.seg} {args.func}: not GLOBAL_ASM in src/")
        text = open(os.path.join(ROOT, src)).read()
        line = next(m for m in PRAGMA.finditer(text) if (m.group(1) or "boot", m.group(2)) == key)
        start, end = line.start(), text.index("\n", line.end()) + 1
        park = text.rfind("#ifdef NON_MATCHING\n", 0, start)
        mid = text.rfind("#else\n", 0, start)
        if park == -1 or mid < park or "#endif" in text[park:start] or not text.startswith("#endif\n", end):
            sys.exit(f"{args.seg} {args.func}: not parked under #ifdef NON_MATCHING in {src}")
        body = text[park + len("#ifdef NON_MATCHING\n"):mid]
        old = stored().get(key)
        prev = open(old).readline().split(": ", 1)[1].strip() if old else ""
        dest = draft_path(*key)
        os.makedirs(os.path.dirname(dest), exist_ok=True)
        with open(dest, "w") as f:
            f.write(f"// {args.func} ({src}): {args.note}" + (f"; {prev}" if prev else "") + f"\n{body.rstrip()}\n")
        with open(os.path.join(ROOT, src), "w") as f:
            f.write(text[:park] + text[mid + len("#else\n"):end] + text[end + len("#endif\n"):])
        print(f"unparked {args.func} in {src}; draft {os.path.relpath(dest, ROOT)}")


if __name__ == "__main__":
    main()
