#!/usr/bin/env python3
"""Persist in-progress C for functions that do not match yet.

Tracked drafts live in drafts/<segment>/<FUNC>.c, one per function that is still
`#pragma GLOBAL_ASM` in src/. The first line is a `// <FUNC> (<src file>): <note>` header
(closest diff, what was tried); the rest is the draft C (the function plus the local
declarations it needs). .scratch/ stays the per-session work area; anything worth
continuing in a later session goes here.

    python3 tools/drafts.py save FUNC FILE [--note TEXT]   # store/replace FUNC's draft
    python3 tools/drafts.py show FUNC                      # print its path and contents
    python3 tools/drafts.py list [SEGMENT]                 # drafts with their notes
    python3 tools/drafts.py collect                        # import newest .scratch/*/<FUNC>_best.c
    python3 tools/drafts.py prune                          # delete drafts of matched functions

`collect` only imports a scratch draft newer than the stored one. `prune` runs after every
merge: a function that left GLOBAL_ASM is matched, its draft is dead weight.
"""
import argparse
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PRAGMA = re.compile(r'#pragma GLOBAL_ASM\("asm/(?:(\w+)/)?nonmatchings/[^"]*/(\w+)\.s"\)')  # boot: asm/nonmatchings
DRAFTS = os.path.join(ROOT, "drafts")


def unmatched() -> dict:
    """FUNC -> (segment, src path) for every GLOBAL_ASM function in src/."""
    out = {}
    for path in glob.glob(os.path.join(ROOT, "src", "**", "*.c"), recursive=True):
        rel = os.path.relpath(path, ROOT)
        for m in PRAGMA.finditer(open(path).read()):
            out[m.group(2)] = (m.group(1) or "boot", rel)
    return out


def draft_path(seg: str, func: str) -> str:
    return os.path.join(DRAFTS, seg, func + ".c")


def stored() -> dict:
    """FUNC -> draft path for every stored draft."""
    return {os.path.basename(p)[:-2]: p for p in glob.glob(os.path.join(DRAFTS, "*", "*.c"))}


def write(func: str, src_file: str, note: str, todo: dict) -> str:
    if func not in todo:
        sys.exit(f"{func} is not GLOBAL_ASM in src/ (matched, or misspelt): nothing to save")
    seg, owner = todo[func]
    body = open(src_file).read()
    if body.startswith(f"// {func} ("):  # re-saving a stored draft: drop its old header
        body = body.split("\n", 1)[1] if "\n" in body else ""
    dest = draft_path(seg, func)
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    with open(dest, "w") as f:
        f.write(f"// {func} ({owner}): {note or 'no note'}\n{body.rstrip()}\n")
    return os.path.relpath(dest, ROOT)


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("save")
    s.add_argument("func")
    s.add_argument("file")
    s.add_argument("--note", default="")
    sub.add_parser("show").add_argument("func")
    sub.add_parser("list").add_argument("segment", nargs="?")
    sub.add_parser("collect")
    sub.add_parser("prune")
    args = ap.parse_args()

    if args.cmd == "save":
        print(write(args.func, args.file, args.note, unmatched()))
    elif args.cmd == "show":
        path = stored().get(args.func)
        if not path:
            sys.exit(f"no draft for {args.func}")
        print(os.path.relpath(path, ROOT))
        print(open(path).read(), end="")
    elif args.cmd == "list":
        for func, path in sorted(stored().items(), key=lambda kv: kv[1]):
            if args.segment and os.path.basename(os.path.dirname(path)) != args.segment:
                continue
            print(f"{os.path.relpath(path, ROOT)}  {open(path).readline().rstrip()}")
    elif args.cmd == "collect":
        todo, have = unmatched(), stored()
        newest = {}
        for p in glob.glob(os.path.join(ROOT, ".scratch", "*", "*_best.c")):
            func = os.path.basename(p)[: -len("_best.c")]
            if func in todo and (func not in newest or os.path.getmtime(p) > os.path.getmtime(newest[func])):
                newest[func] = p
        for func, p in sorted(newest.items()):
            if func in have and os.path.getmtime(have[func]) >= os.path.getmtime(p):
                continue
            note = f"from {os.path.relpath(p, ROOT)}"
            print(write(func, p, note, todo))
    elif args.cmd == "prune":
        todo = unmatched()
        for func, path in sorted(stored().items()):
            if func not in todo:
                os.remove(path)
                print(f"removed {os.path.relpath(path, ROOT)} (matched)")
        for d in glob.glob(os.path.join(DRAFTS, "*")):
            if os.path.isdir(d) and not os.listdir(d):
                os.rmdir(d)


if __name__ == "__main__":
    main()
