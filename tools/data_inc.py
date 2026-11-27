#!/usr/bin/env python3
"""Generate C initialiser includes of ROM-extracted data (asset-like blobs inside a C TU).

    python3 tools/data_inc.py gen [--manifest PATH]

IDO has no `.incbin` and a splat `bin` subsegment cannot sit inside one TU's `.data`,
so asset bytes become C arrays whose initialiser is a generated include:

    const u8 D_80032220[0x208] = {
    #include "arcade/D_80032220.inc.c"
    };

Each row of the manifest (default data_inc.us.txt; `#` comments) is
`seg name vram size width file`: width 1, 2 or 4 (u8/u16/u32 elements), file the owning
src/...c. `gen` reads the bytes from the segment's code stream (boot: baserom.us.z64;
global: bin/segments/global.bin; overlays: bin/segments/ovlNN.bin) and writes
assets/inc/<seg>/<name>.inc.c as comma-terminated big-endian hex literals. `make split`
runs it last; assets/ is gitignored, so the bytes never enter git. CFLAGS has
`-I assets/inc`.
"""

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from progress import SEGMENT_STREAMS, read_data_inc  # noqa: E402

REPO = Path(__file__).resolve().parent.parent
PER_LINE = {1: 16, 2: 8, 4: 8}


def render(data: bytes, width: int) -> str:
    values = [int.from_bytes(data[i:i + width], "big") for i in range(0, len(data), width)]
    per = PER_LINE[width]
    lines = []
    for i in range(0, len(values), per):
        lines.append(" ".join(f"0x{v:0{width * 2}X}," for v in values[i:i + per]))
    return "\n".join(lines) + "\n"


def gen(manifest: Path) -> int:
    try:
        rows = read_data_inc(manifest)
    except ValueError as e:
        print(e, file=sys.stderr)
        return 1
    streams = {}
    written = 0
    # IDO cc fails on a missing -I directory: create it even for an empty manifest.
    (REPO / "assets" / "inc").mkdir(parents=True, exist_ok=True)
    for row in rows:
        where = f"{manifest}:{row['line']}"
        if row["seg"] not in SEGMENT_STREAMS:
            print(f"{where}: unknown segment {row['seg']}", file=sys.stderr)
            return 1
        if row["width"] not in PER_LINE:
            print(f"{where}: width must be 1, 2 or 4", file=sys.stderr)
            return 1
        if row["size"] % row["width"]:
            print(f"{where}: size 0x{row['size']:X} is not a multiple of width {row['width']}", file=sys.stderr)
            return 1
        stream, base = SEGMENT_STREAMS[row["seg"]]
        if stream not in streams:
            path = REPO / stream
            if not path.is_file():
                print(f"no {stream}: run tools/dk make setup", file=sys.stderr)
                return 1
            streams[stream] = path.read_bytes()
        data = streams[stream]
        off = row["vram"] - base
        if off < 0 or off + row["size"] > len(data):
            print(f"{where}: 0x{row['vram']:08X}+0x{row['size']:X} is outside {stream}", file=sys.stderr)
            return 1
        out = REPO / "assets" / "inc" / row["seg"] / f"{row['name']}.inc.c"
        out.parent.mkdir(parents=True, exist_ok=True)
        text = render(data[off:off + row["size"]], row["width"])
        if not out.is_file() or out.read_text(encoding="utf-8") != text:
            open(out, "w", encoding="utf-8", newline="\n").write(text)
        written += 1
    print(f"data_inc: {written} include(s) in assets/inc")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    g = sub.add_parser("gen", help="write assets/inc/<seg>/<name>.inc.c for every manifest row")
    g.add_argument("--manifest", type=Path, default=REPO / "data_inc.us.txt")
    args = ap.parse_args()
    return gen(args.manifest)


if __name__ == "__main__":
    sys.exit(main())
