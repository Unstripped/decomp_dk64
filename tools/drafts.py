#!/usr/bin/env python3
"""Persist in-progress C for functions that do not match yet.

Tracked drafts live in drafts/<segment>/<FUNC>.c, one per (segment, function) that is still
`#pragma GLOBAL_ASM` in src/. Overlays share VRAM 0x80024000, so a splat name such as
`func_80024000` exists in several segments: every draft is keyed by segment AND name. The
first line is a `// <FUNC> (<src file>): <note>` header (closest diff, what was tried); the
rest is the draft C (the function plus the local declarations it needs). .scratch/ stays
the per-session work area; anything worth continuing in a later session goes here.

    python3 tools/drafts.py save SEG FUNC FILE [--note TEXT]  # store/replace a draft
    python3 tools/drafts.py show SEG FUNC                     # print its path and contents
    python3 tools/drafts.py list [SEG]                        # drafts with their notes
    python3 tools/drafts.py collect                           # import newer .scratch/*/<FUNC>_best.c
    python3 tools/drafts.py prune                             # delete drafts of matched functions
    python3 tools/drafts.py paste SEG FUNC                    # put a draft into its src file

SEG is the asm directory name: boot, global, or an overlay (boss, jetpac, ...).
`collect` takes the segment of a `.scratch/<Agent>/<FUNC>_best.c` from the private copy of
the source file in the same directory (the one whose GLOBAL_ASM line names
`asm/<seg>/nonmatchings/.../<FUNC>.s`); a name that is unmatched in only one segment needs no
copy. Drafts whose segment can't be determined are reported and skipped, never guessed.
`prune` runs after every merge: a function that left GLOBAL_ASM is matched.
`paste` replaces FUNC's `GLOBAL_ASM` line (or the whole `#ifdef NON_MATCHING` park around it)
in its src file with the draft minus its header, for "text-identical, reloc only" reports;
then `tools/merge_gate.sh - - <src file>` prunes duplicated declarations and lets the ROM
hash decide.
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
    args = ap.parse_args()

    if args.cmd == "save":
        print(write(args.seg, args.func, args.file, args.note, unmatched()))
    elif args.cmd == "show":
        path = stored().get((args.seg, args.func))
        if not path:
            sys.exit(f"no draft for {args.seg} {args.func}")
        print(os.path.relpath(path, ROOT))
        print(open(path).read(), end="")
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
            print(write(seg, func, p, f"from {os.path.relpath(p, ROOT)}", todo))
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
        line = next(m for m in PRAGMA.finditer(text) if (m.group(1) or "boot", m.group(2)) == key)
        start, end = line.start(), text.index("\n", line.end()) + 1
        park = text.rfind("#ifdef NON_MATCHING\n", 0, start)
        if park != -1 and "#endif" not in text[park:start] and text.startswith("#endif\n", end):
            start, end = park, end + len("#endif\n")
        with open(src, "w") as f:
            f.write(text[:start] + body + text[end:])
        print(f"pasted {os.path.relpath(path, ROOT)} into {os.path.relpath(src, ROOT)}")


if __name__ == "__main__":
    main()
