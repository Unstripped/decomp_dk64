#!/usr/bin/env python3
"""Suggest translation-unit boundaries for a segment that is still all asm.

Run on a freshly split segment whose text subsegments are all `asm` (before
converting files to `c`):

    python3 tools/rodata_owners.py <segment>      # e.g. boss, reads asm/<segment>/

For every data/rodata label in asm/<segment>/data/*.s it finds the text files
(asm/<segment>/*.s) that reference it. Labels referenced only from other data
(string/script tables) inherit the owner of the data object that points at them.
Output: one line per run of consecutive labels with the same owner, plus a kind
string per run (s = string, J = jump table, f = float, d = double, w = word/blob).
A TU's .rodata (strings, const arrays) precedes its .late_rodata (floats, doubles,
jump tables), so s/w after d/J inside one splat file flags a hidden TU boundary;
each rodata run should start 16-byte aligned. An owner of `-` is an unreferenced
label: a late_rodata float there needs `type:f32 force_migration:True
function_owner:<func>` in the symbol file or splat emits it as .rodata.
"""
import glob
import os
import re
import sys

LABEL = re.compile(r"\s*(?:dlabel|jlabel|glabel)\s+(\w+)")
KIND = re.compile(r"\.(word|float|double|asciz|ascii|short|byte)\b")
OFFSET = re.compile(r"/\* ([0-9A-F]+) [0-9A-F]{8}")


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    seg = sys.argv[1]
    data_files = sorted(glob.glob(f"asm/{seg}/data/*.s"))
    text = {os.path.basename(f)[:-2]: open(f).read() for f in sorted(glob.glob(f"asm/{seg}/*.s"))}
    if not data_files or not text:
        sys.exit(f"no asm/{seg}/*.s or asm/{seg}/data/*.s; run splat with every text file as asm first")

    labels = []  # (name, rom offset, kind)
    pointed_by = {}  # label -> data label containing a .word pointing at it
    for path in data_files:
        cur = None
        for line in open(path):
            m = LABEL.match(line)
            if m:
                cur = m.group(1)
                labels.append([cur, None, None])
                continue
            if cur is None:
                continue
            entry = labels[-1]
            if entry[1] is None:
                o = OFFSET.search(line)
                if o:
                    entry[1] = int(o.group(1), 16)
            if entry[2] is None:
                k = KIND.search(line)
                if k:
                    entry[2] = k.group(1)
            for target in re.findall(r"\.word ((?:D|jtbl)_\w+)", line):
                pointed_by.setdefault(target, cur)

    refs_by_name = {}  # identifier -> text files mentioning it, built once (global has ~1,400 files)
    for f, t in text.items():
        for ident in set(re.findall(r"\b[A-Za-z_]\w*", t)):
            refs_by_name.setdefault(ident, []).append(f)

    def owners(name: str, depth: int = 0) -> str:
        refs = refs_by_name.get(name)
        if refs:
            return ",".join(refs)
        parent = pointed_by.get(name)
        if parent and depth < 4:
            return owners(parent, depth + 1)
        return "-"

    runs = []
    for name, off, kind in labels:
        if off is None:
            continue
        code = "J" if name.startswith("jtbl") else {"float": "f", "double": "d", "asciz": "s", "ascii": "s"}.get(kind, "w")
        own = owners(name)
        if runs and runs[-1][1] == own:
            runs[-1][2] += code
        else:
            runs.append([off, own, code])

    for off, own, kinds in runs:
        flag = "" if off % 16 == 0 else "  (not 16-aligned)"
        late = re.search(r"[dJ][fdJ]*[sw]", kinds)
        if late:
            flag += "  (string/word after late_rodata: hidden TU?)"
        print(f"0x{off:X}  {own:<12} {kinds}{flag}")


if __name__ == "__main__":
    main()
