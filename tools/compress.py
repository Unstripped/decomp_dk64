#!/usr/bin/env python3
"""Pack DK64 code streams into a ROM segment.

Each input file becomes one gzip member produced by GNU gzip 1.2.4 -9 -n
(header: no flags, mtime=0, xfl=2, os=3, matching the original ROM). Members
are concatenated in argument order and, with --size, zero-padded to exactly
that many bytes.

  tools/compress.py --size 0xBAA80 build/global.gz build/global.text.bin build/global.data.bin
"""

import argparse
import subprocess
import sys
from pathlib import Path

GZIP = "/usr/local/bin/gzip-1.2.4"
GZIP_HEADER = b"\x1f\x8b\x08\x00\x00\x00\x00\x00\x02\x03"


def gzip_member(payload: bytes) -> bytes:
    proc = subprocess.run(
        [GZIP, "-9", "-n", "-c"],
        input=payload,
        stdout=subprocess.PIPE,
        check=True,
    )
    out = proc.stdout
    assert out[:10] == GZIP_HEADER, f"unexpected gzip header: {out[:10]!r}"
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--size", type=lambda s: int(s, 0), help="zero-pad output to exactly this many bytes")
    parser.add_argument("out", type=Path)
    parser.add_argument("inputs", type=Path, nargs="+")
    args = parser.parse_args()

    out = b"".join(gzip_member(path.read_bytes()) for path in args.inputs)
    if args.size is not None:
        if len(out) > args.size:
            sys.exit(f"error: {args.out}: 0x{len(out):X} bytes exceed segment size 0x{args.size:X}")
        out += bytes(args.size - len(out))
    args.out.write_bytes(out)


if __name__ == "__main__":
    main()
