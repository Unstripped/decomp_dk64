#!/usr/bin/env python3
"""Locate data differences between a built segment and the original.

    python3 tools/datadiff.py <seg> [-n N] [--expected PATH]

The built image is build/<seg>.data.bin (build/boot.bin for boot), the expected one
bin/segments/<stream>.data.bin (baserom.us.z64 truncated to 0x113F0 for boot);
--expected overrides it. Prints the first N (default 10) differing byte ranges as
`0x<vram>-0x<vram> <map object> <nearest preceding symbol>+0x<off> exp <hex> got <hex>`.
Exit 0 with `<seg>: data OK (0x<len> bytes)` when identical, else 1.

`check` fails after writing the bins, so after a failed `tools/dk make` run
`python3 tools/datadiff.py <seg>` to locate a carve error.
"""

import argparse
import bisect
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from data_owners import SHN_ABS, SHN_UNDEF, STT_FILE, STT_SECTION, Elf, map_rows  # noqa: E402
from progress import SEGMENT_STREAMS, segment_paths  # noqa: E402

REPO = Path(__file__).resolve().parent.parent
BOOT_SIZE = 0x113F0
BOOT_VRAM = 0x7FFFF400
LINKER_SYMBOL = re.compile(r"_(ROM_START|ROM_END|VRAM|VRAM_END|START|END|SIZE)$")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("seg", choices=sorted(SEGMENT_STREAMS))
    ap.add_argument("-n", type=int, default=10, help="differing ranges to print (default 10)")
    ap.add_argument("--expected", type=Path, help="expected image (default: the original's)")
    args = ap.parse_args()

    build = REPO / "build"
    elf_path, map_path = segment_paths(build, args.seg)
    if args.seg == "boot":
        built_path = build / "boot.bin"
        expected_path = args.expected or REPO / "baserom.us.z64"
        base = BOOT_VRAM
    else:
        built_path = build / f"{args.seg}.data.bin"
        stream = Path(SEGMENT_STREAMS[args.seg][0]).stem
        expected_path = args.expected or REPO / "bin" / "segments" / f"{stream}.data.bin"
        base = None
    for path in (built_path, expected_path, map_path, elf_path):
        if not path.is_file():
            print(f"no {path}: run tools/dk make", file=sys.stderr)
            return 1
    built = built_path.read_bytes()
    expected = expected_path.read_bytes()
    if args.seg == "boot":
        if args.expected is None:
            expected = expected[:BOOT_SIZE]
    else:
        m = re.search(rf"^\s+(0x[0-9a-fA-F]+)\s+{args.seg}_DATA_START = \.",
                      map_path.read_text(encoding="utf-8", errors="replace"), re.MULTILINE)
        if not m:
            print(f"{map_path}: no {args.seg}_DATA_START", file=sys.stderr)
            return 1
        base = int(m.group(1), 16)

    if built == expected:
        print(f"{args.seg}: data OK (0x{len(built):X} bytes)")
        return 0
    if len(built) != len(expected):
        print(f"size: expected 0x{len(expected):X} got 0x{len(built):X} "
              f"({len(built) - len(expected):+d} bytes)")

    rows = sorted((addr, size, obj) for _sec, addr, size, obj in map_rows(map_path) if size > 0)
    row_starts = [r[0] for r in rows]
    symbols = sorted(
        (s["value"], s["name"]) for s in Elf(elf_path).symbols
        if s["shndx"] not in (SHN_UNDEF, SHN_ABS) and s["type"] not in (STT_SECTION, STT_FILE)
        and s["name"] and not LINKER_SYMBOL.search(s["name"])
    )
    sym_starts = [v for v, _ in symbols]

    def describe(addr):
        i = bisect.bisect_right(row_starts, addr) - 1
        obj = rows[i][2] if i >= 0 and addr < rows[i][0] + rows[i][1] else "?"
        j = bisect.bisect_right(sym_starts, addr) - 1
        sym = f"{symbols[j][1]}+0x{addr - symbols[j][0]:X}" if j >= 0 else "?"
        return obj, sym

    shown = 0
    i, n = 0, min(len(built), len(expected))
    while i < n and shown < args.n:
        if built[i] == expected[i]:
            i += 1
            continue
        j = i
        while j < n and built[j] != expected[j]:
            j += 1
        obj, sym = describe(base + i)
        print(f"0x{base + i:08X}-0x{base + j:08X} {obj} {sym} "
              f"exp {expected[i:min(j, i + 16)].hex()} got {built[i:min(j, i + 16)].hex()}")
        shown += 1
        i = j
    return 1


if __name__ == "__main__":
    sys.exit(main())
