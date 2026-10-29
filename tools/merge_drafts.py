#!/usr/bin/env python3
"""Merge several agents' private copies of one C file back into src/.

    python3 tools/merge_drafts.py snapshot src/menu/3E10.c [...]
        Save the current file(s) as the merge base (.scratch/bases/). Run this right
        before agents copy the file; every copy must start from this exact content.

    python3 tools/merge_drafts.py merge [--base REV] src/menu/3E10.c [.scratch/A/3E10.c ...]
        3-way merge every copy against the base into the CURRENT src file (git merge-file),
        so edits made to src after the snapshot survive; drop file-scope declarations that
        are exact duplicates of an earlier line (or an identical typedef block) or whose name
        is used nowhere else in the file (left behind by reverted drafts), restore a local
        declaration a draft deleted but its function still uses (parked NON_MATCHING bodies
        are not compiled by the check), then check the object with tools/objdiff.sh.
        Compile errors are printed with the text of both clashing declarations. With no
        copies it only prunes and checks (use after resolving conflicts by hand).
        --base REV uses `git show REV:<src>` as the base instead of the snapshot: for drafts
        copied before a later snapshot (agents still running from an earlier round), pass
        the commit their copy started from. A copy that dropped another function's (or
        standalone data/rodata symbol's) GLOBAL_ASM line without a C definition of it is
        refused before merging (exit 1, src untouched).

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
    """(index, name, conditional) for one-line declarations outside any function body;
    conditional = inside an #if/#ifdef block (e.g. a parked NON_MATCHING function)."""
    depth = 0
    cond = 0
    out = []
    for i, line in enumerate(lines):
        if line.startswith("#if"):
            cond += 1
        elif line.startswith("#endif"):
            cond -= 1
        if depth == 0 and not line.startswith((" ", "\t", "#")):
            m = DECL_EXTERN.match(line) or DECL_PROTO.match(line)
            if m:
                out.append((i, m.group(1), cond > 0))
        depth += line.count("{") - line.count("}")
    return out


def prune(lines, base_lines):
    """Drop declarations added since the base that duplicate another line or declare a
    name used nowhere else; lines already in the base are never touched."""
    text = "".join(lines)
    decls = file_scope_decls(lines)
    # Declarations already in the base are kept. Of identical added lines, the FIRST is
    # kept: an earlier function may use it, so dropping it would leave a use before decl.
    # Only an unconditional declaration covers later duplicates: a copy inside an #if
    # block (parked NON_MATCHING code, or one branch of #if/#else) may be compiled out, so
    # conditional declarations never cause a drop (identical redeclarations are legal C).
    in_base = Counter(base_lines[i].strip() for i, _, _ in file_scope_decls(base_lines))
    seen = set()  # unconditional declarations kept so far
    drop = set()
    for i, name, cond in decls:
        key = lines[i].strip()
        if in_base[key] > 0:
            in_base[key] -= 1
            if not cond:
                seen.add(key)
            continue
        if key in seen:
            drop.add(i)
            print(f"  dropped duplicate: {key}")
        elif len(re.findall(rf"\b{re.escape(name)}\b", text)) == 1:
            drop.add(i)
            print(f"  dropped unused:    {key}")
        elif not cond:
            seen.add(key)
    drop_typedefs(lines, base_lines, drop)
    return [l for i, l in enumerate(lines) if i not in drop]


def typedef_blocks(lines):
    """(start, end, name, conditional, normalised text) for file-scope `typedef ...;`
    declarations, one line or a multi-line `typedef struct X {` ... `} X;` block."""
    depth = 0
    cond = 0
    out = []
    i = 0
    while i < len(lines):
        line = lines[i]
        if line.startswith("#if"):
            cond += 1
        elif line.startswith("#endif"):
            cond -= 1
        if depth == 0 and line.startswith("typedef"):
            j, d = i, 0
            while j < len(lines):
                d += lines[j].count("{") - lines[j].count("}")
                if d <= 0 and lines[j].rstrip().endswith(";"):
                    break
                j += 1
            else:
                break
            text = " ".join("".join(lines[i:j + 1]).split())
            m = re.search(r"(\w+)\s*(?:\[[^\]]*\]\s*)*;$", text)
            out.append((i, j, m.group(1) if m else text, cond > 0, text))
            i = j + 1
            continue
        depth += line.count("{") - line.count("}")
        i += 1
    return out


def drop_typedefs(lines, base_lines, drop):
    """Drop a typedef (block) added since the base that is textually identical (whitespace
    normalised) to an earlier unconditional one: cfe rejects the redeclaration. A same-name
    typedef with a different body is left for the compiler to report."""
    in_base = Counter(t[4] for t in typedef_blocks(base_lines))
    seen = set()
    for start, end, name, cond, text in typedef_blocks(lines):
        if in_base[text] > 0:
            in_base[text] -= 1
        elif text in seen:
            drop.update(range(start, end + 1))
            if end + 1 < len(lines) and not lines[end + 1].strip() and (start == 0 or not lines[start - 1].strip()):
                drop.add(end + 1)
            print(f"  dropped duplicate typedef: {name}")
            continue
        if not cond:
            seen.add(text)


LOCAL_DECL = re.compile(
    r"^[ \t]+(?!(?:return|goto|else|case|do|default|break|continue)\b)"
    r"(?:(?:const|volatile|static|register|unsigned|signed|struct|union|enum)\s+)*"
    r"[A-Za-z_]\w*[\s\*]+(\w+)(?:\[[^\]]*\])*\s*(?:=[^;]*)?;\s*$")


def function_body(lines, header):
    """(start, end) line range of the unique function whose header line is `header`."""
    hits = [i for i, l in enumerate(lines) if l.strip() == header]
    if len(hits) != 1:
        return None
    for j in range(hits[0] + 1, len(lines)):
        if lines[j].startswith("}"):
            return hits[0], j
    return None


def restore_locals(lines, base_lines):
    """A draft that deleted a local declaration still used in its function (a parked
    #ifdef NON_MATCHING body is not compiled by the normal check) gets the line put back
    right after the line that preceded it in the base. Deletions of unused locals stand."""
    for i, line in enumerate(base_lines):
        m = LOCAL_DECL.match(line)
        if not m:
            continue
        name = m.group(1)
        k = i - 1
        while k >= 0 and (base_lines[k].startswith((" ", "\t", "#")) or not base_lines[k].strip()):
            k -= 1
        header = base_lines[k].strip() if k >= 0 else ""
        if not header.endswith("{") or "(" not in header:
            continue
        span = function_body(lines, header)
        if span is None:
            continue
        start, end = span
        body = lines[start + 1:end]
        if any(l.strip() == line.strip() for l in body):
            continue
        use = rf"\b{re.escape(name)}\b"
        # declared again elsewhere in the body, also inline after a brace: `{ s32 tv = ...;`
        redecl = re.compile(
            r"(?:^|[{;])\s*(?!(?:return|goto|else|case|do|default|break|continue|sizeof)\b)"
            r"(?:(?:const|volatile|static|register|unsigned|signed|struct|union|enum)\s+)*"
            rf"[A-Za-z_]\w*[\s\*]+{re.escape(name)}\s*(?:\[[^\]]*\]\s*)*(?:=|;)")
        if re.search(use, header) or any(redecl.search(l) for l in body):
            continue  # a parameter, or declared again elsewhere in the body
        if not any(re.search(use, l) for l in body):
            continue
        at = start + 1
        prev = base_lines[i - 1].strip() if i - 1 > k else None
        if prev is not None:
            for n in range(start + 1, end):
                if lines[n].strip() == prev:
                    at = n + 1
                    break
        lines.insert(at, line)
        print(f"  restored deleted local declaration: {line.strip()}  (in {header})")
    return lines


def lost_functions(base_text, draft_text):
    """Symbols whose GLOBAL_ASM line is in the base but neither that line nor a C definition
    is in the draft: an agent deleted another function's pragma (the link then fails with an
    undefined reference from data, e.g. a callback table). A function counts as defined by
    `T name(...)` without a trailing `;`; a standalone data/rodata pragma (`D_....s`) by a
    non-extern file-scope object definition `T name[...] = ...;` / `T name;`."""
    lost = []
    for path, name in re.findall(r'GLOBAL_ASM\("([^"]*/(\w+)\.s)"\)', base_text):
        if f'GLOBAL_ASM("{path}")' in draft_text:
            continue
        n = re.escape(name)
        if re.search(rf"^[A-Za-z_][\w \t\*]*\b{n}\([^;]*$", draft_text, re.M):
            continue
        # K&R definition: `T name(a, b) T1 a; T2 *b; {` (identifier list, then declarations)
        if re.search(rf"^[A-Za-z_][\w \t\*]*\b{n}\(\s*\w+(?:\s*,\s*\w+)*\s*\)\s*"
                     rf"(?:[A-Za-z_][\w \t\*]*?\w+(?:\s*\[[^\]]*\])?(?:\s*,\s*\**\s*\w+)*\s*;\s*)+\{{",
                     draft_text, re.M):
            continue
        if re.search(rf"^(?!extern\b)[A-Za-z_][\w \t\*]*\b{n}\s*(\[[^\]]*\]\s*)*(=|;)",
                     draft_text, re.M):
            continue
        lost.append(name)
    return lost


def merge(src, drafts, rev=None):
    base = base_path(src)
    if rev:
        os.makedirs(os.path.join(SCRATCH, "bases"), exist_ok=True)
        base = os.path.join(SCRATCH, "bases", f"{rev}_" + src.replace("/", "_"))
        with open(base, "w") as f:
            f.write(subprocess.run(["git", "show", f"{rev}:{src}"], check=True,
                                   capture_output=True, text=True).stdout)
    elif not os.path.exists(base):
        print(f"Error: no base for {src}; run `snapshot` before agents copy it.", file=sys.stderr)
        return 1
    os.makedirs(os.path.join(SCRATCH, "merged"), exist_ok=True)
    out = os.path.join(SCRATCH, "merged", src.replace("/", "_"))
    # Start from the CURRENT src, not the base: edits made to src after the snapshot
    # (inline fixes, DIRECT agents) are one more side of the merge and are never lost.
    shutil.copyfile(src, out)
    with open(base) as f:
        base_text = f.read()
    for d in drafts:
        with open(d) as f:
            lost = lost_functions(base_text, f.read())
        if lost:
            print(f"Error: {d} lost {', '.join(lost)} (no GLOBAL_ASM line, no definition); "
                  f"restore them in the copy first. {src} untouched.", file=sys.stderr)
            return 1
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
        base_lines = f.readlines()
    lines = restore_locals(prune(lines, base_lines), base_lines)
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
    if len(sys.argv) >= 5 and sys.argv[1] == "merge" and sys.argv[2] == "--base":
        return merge(sys.argv[4], sys.argv[5:], sys.argv[3])
    if len(sys.argv) >= 3 and sys.argv[1] == "merge":
        return merge(sys.argv[2], sys.argv[3:])
    print(__doc__, file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
