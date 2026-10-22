#!/usr/bin/env python3
"""Merge several agents' private copies of one C file back into src/.

    python3 tools/merge_drafts.py snapshot src/menu/3E10.c [...]
        Save the current file(s) as the merge base (.scratch/bases/). Run this right
        before agents copy the file; every copy must start from this exact content.

    python3 tools/merge_drafts.py merge src/menu/3E10.c [.scratch/A/3E10.c .scratch/B/3E10.c ...]
        3-way merge every copy against the base into the CURRENT src file (git merge-file),
        so edits made to src after the snapshot survive; drop file-scope declarations that
        are exact duplicates of an earlier line or whose name is used nowhere else in the
        file (left behind by reverted drafts), then check the object with tools/objdiff.sh.
        Compile errors are printed with the text of both clashing declarations. With no
        copies it only prunes and checks (use after resolving conflicts by hand).

Runs on the host (needs git and tools/dk). Exit codes: 0 OK / TEXT OK, 1 compile error
or mismatch, 2 merge conflicts (src untouched; conflicted result in .scratch/merged/).
"""
import os
from collections import Counter
import re
import shutil
import subprocess
import sys

SCRATCH = ".scratch"
DECL_EXTERN = re.compile(r"^extern\b[^{}()]*?\b(\w+)\s*(\[[^\]]*\]\s*)*;\s*$")
DECL_PROTO = re.compile(r"^(?!typedef\b|return\b|extern\b)[A-Za-z_][\w\s\*]*?\b(\w+)\s*\([^;{}]*\)\s*;\s*$")
REDECL = re.compile(r"line (\d+): redeclaration of '(\w+)'; previous declaration at line (\d+)")


def base_path(src):
    return os.path.join(SCRATCH, "bases", src.replace("/", "_"))


def snapshot(srcs):
    os.makedirs(os.path.join(SCRATCH, "bases"), exist_ok=True)
    for src in srcs:
        shutil.copyfile(src, base_path(src))
        print(f"base saved: {base_path(src)}")
    return 0


def file_scope_decls(lines):
    """(index, name) for one-line declarations outside any function body."""
    depth = 0
    out = []
    for i, line in enumerate(lines):
        if depth == 0 and not line.startswith((" ", "\t", "#")):
            m = DECL_EXTERN.match(line) or DECL_PROTO.match(line)
            if m:
                out.append((i, m.group(1)))
        depth += line.count("{") - line.count("}")
    return out


def prune(lines, base_lines):
    """Drop declarations added since the base that duplicate another line or declare a
    name used nowhere else; lines already in the base are never touched."""
    text = "".join(lines)
    decls = file_scope_decls(lines)
    # Occurrences per declaration text: in the base (kept) and in the merged file.
    in_base = Counter(base_lines[i].strip() for i, _ in file_scope_decls(base_lines))
    total = Counter(lines[i].strip() for i, _ in decls)
    drop = set()
    for i, name in decls:
        key = lines[i].strip()
        if in_base[key] > 0:
            in_base[key] -= 1
            continue
        if total[key] > 1:
            drop.add(i)
            total[key] -= 1
            print(f"  dropped duplicate: {key}")
        elif len(re.findall(rf"\b{re.escape(name)}\b", text)) == 1:
            drop.add(i)
            print(f"  dropped unused:    {key}")
    return [l for i, l in enumerate(lines) if i not in drop]


def merge(src, drafts):
    base = base_path(src)
    if not os.path.exists(base):
        print(f"Error: no base for {src}; run `snapshot` before agents copy it.", file=sys.stderr)
        return 1
    os.makedirs(os.path.join(SCRATCH, "merged"), exist_ok=True)
    out = os.path.join(SCRATCH, "merged", src.replace("/", "_"))
    # Start from the CURRENT src, not the base: edits made to src after the snapshot
    # (inline fixes, DIRECT agents) are one more side of the merge and are never lost.
    shutil.copyfile(src, out)
    conflicts = 0
    for d in drafts:
        r = subprocess.run(["git", "merge-file", "-L", src, "-L", "base", "-L", d, out, base, d])
        if r.returncode < 0 or r.returncode > 127:
            print(f"Error: git merge-file failed on {d}", file=sys.stderr)
            return 1
        conflicts += r.returncode
    if conflicts:
        print(f"{conflicts} conflict(s); {src} untouched. Resolve in {out}, copy it to {src}, "
              f"then run `merge {src}` with no copies to prune and check it.")
        return 2

    with open(out) as f:
        lines = f.readlines()
    with open(base) as f:
        lines = prune(lines, f.readlines())
    with open(src, "w") as f:
        f.writelines(lines)
    print(f"merged {len(drafts)} draft(s) into {src}")

    r = subprocess.run(["tools/dk", "tools/objdiff.sh", src], capture_output=True, text=True)
    output = r.stdout + r.stderr
    errors = [l for l in output.splitlines() if "cfe: Error" in l]
    if errors:
        for l in errors:
            print(l)
            m = REDECL.search(l)
            if m:
                print(f"    {m.group(3)}: {lines[int(m.group(3)) - 1].rstrip()}")
                print(f"    {m.group(1)}: {lines[int(m.group(1)) - 1].rstrip()}")
        return 1
    print(output.strip().splitlines()[-1] if output.strip() else "(no output)")
    return 0 if r.returncode in (0, 3) else 1


def main():
    if len(sys.argv) >= 3 and sys.argv[1] == "snapshot":
        return snapshot(sys.argv[2:])
    if len(sys.argv) >= 3 and sys.argv[1] == "merge":
        return merge(sys.argv[2], sys.argv[3:])
    print(__doc__, file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
