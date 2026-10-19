#!/usr/bin/env python3
"""Extract DK64 (US) code segments into individual binaries.

Input: a user-supplied ROM in any byte order (.z64 big-endian, .v64/.n64 byte-swapped,
or little-endian). Output:
  baserom.us.z64                    big-endian copy of the ROM (SHA-1 verified)
  bin/segments/<name>.bin           uncompressed boot pieces
  bin/segments/<name>.text.bin      inflated code stream of a compressed segment
  bin/segments/<name>.data.bin      inflated data stream of a compressed segment
  bin/layout.json                   ROM/VRAM/stream metadata consumed by later build steps

Segment ROM ranges and VRAM come from the runtime segment table at 0x8000DCC4
(romStart/romEnd written by the boot code at 0x80000764, VRAM fields written by
func_805FB300). Each entry is 0x18 bytes: romStart, romEnd, vramStart, vramEnd,
bssStart, bssEnd. Every compressed segment is a code gzip member followed by a data
gzip member, then zero padding up to romEnd.
"""

import argparse
import hashlib
import json
import sys
import zlib
from pathlib import Path

US_SHA1 = "cf806ff2603640a748fca5026ded28802f1f4a50"
ROM_SIZE = 0x2000000

# Uncompressed regions of the boot path.
RAW_SEGMENTS = [
    # name, romStart, romEnd, vram
    ("header", 0x0000, 0x0040, None),
    ("ipl3", 0x0040, 0x1000, None),
    ("entry", 0x1000, 0x1050, 0x80000400),  # bss clear + jump to 0x800009D0
    ("boot", 0x1050, 0x11320, 0x80000450),  # table entry 0; bss 0x80010720-0x80016630
    ("rspboot", 0x11320, 0x113F0, None),  # RSP boot microcode
    ("table12", 0x101A40, 0x101C50, None),  # table entry 12: raw display-list data
    ("assets", 0x101C50, 0x2000000, None),  # asset tables 11, 13-17 + padding
]
BOOT_BSS = (0x80010720, 0x80016630)

# Compressed code segments (segment table entries 1-10).
GZ_SEGMENTS = [
    # name, table index, romStart, romEnd, vramStart, vramEnd, bssStart, bssEnd
    ("global", 1, 0x113F0, 0xCBE70, 0x805FB300, 0x807FF100, 0x80761050, 0x807FF100),
    ("ovl02", 2, 0xD4B00, 0xD6B00, 0x80024000, 0x80027110, 0x80027100, 0x80027110),
    ("ovl03", 3, 0xD6B00, 0xD9A40, 0x80024000, 0x80028E20, 0x80028E10, 0x80028E20),
    ("ovl04", 4, 0xD9A40, 0xDF600, 0x80024000, 0x8002DF10, 0x8002DEF0, 0x8002DF10),
    ("ovl05", 5, 0xDF600, 0xE6780, 0x80024000, 0x80030170, 0x80030160, 0x80030170),
    ("ovl06", 6, 0xE6780, 0xEA0B0, 0x80024000, 0x8002A1E0, 0x8002A1B0, 0x8002A1E0),
    ("ovl07", 7, 0xEA0B0, 0xF41A0, 0x80024000, 0x80036DF0, 0x80036DC0, 0x80036DF0),
    ("ovl08", 8, 0xF41A0, 0xFD2F0, 0x80024000, 0x8004C750, 0x8004AC00, 0x8004C750),
    ("ovl09", 9, 0xFD2F0, 0x101A40, 0x80024000, 0x80045C00, 0x8002EC30, 0x80045C00),
    ("ovl10", 10, 0xCBE70, 0xD4B00, 0x80024000, 0x80033FD0, 0x80033F10, 0x80033FD0),
]


def to_big_endian(data: bytes) -> bytes:
    magic = data[:4]
    if magic == b"\x80\x37\x12\x40":
        return data
    if magic == b"\x37\x80\x40\x12":  # byte-swapped (.v64 / most .n64)
        out = bytearray(len(data))
        out[0::2] = data[1::2]
        out[1::2] = data[0::2]
        return bytes(out)
    if magic == b"\x40\x12\x37\x80":  # little-endian
        out = bytearray(len(data))
        for i in range(4):
            out[i::4] = data[3 - i :: 4]
        return bytes(out)
    sys.exit(f"error: unrecognised ROM magic {magic.hex()}")


def read_gzip_member(rom: bytes, offset: int) -> dict:
    """Inflate one gzip member at `offset`; return its payload and exact extent."""
    head = rom[offset : offset + 10]
    if head[:3] != b"\x1f\x8b\x08":
        sys.exit(f"error: no gzip member at ROM 0x{offset:X}")
    flags = head[3]
    if flags != 0:
        sys.exit(f"error: unexpected gzip flags 0x{flags:02X} at ROM 0x{offset:X}")
    inflater = zlib.decompressobj(-zlib.MAX_WBITS)
    payload = inflater.decompress(rom[offset + 10 :])
    if not inflater.eof:
        sys.exit(f"error: truncated deflate stream at ROM 0x{offset:X}")
    deflate_end = len(rom) - len(inflater.unused_data)
    crc, isize = int.from_bytes(rom[deflate_end : deflate_end + 4], "little"), int.from_bytes(
        rom[deflate_end + 4 : deflate_end + 8], "little"
    )
    if crc != zlib.crc32(payload) or isize != len(payload) & 0xFFFFFFFF:
        sys.exit(f"error: gzip trailer mismatch at ROM 0x{offset:X}")
    return {
        "payload": payload,
        "rom_start": offset,
        "rom_end": deflate_end + 8,
        "mtime": int.from_bytes(head[4:8], "little"),
        "xfl": head[8],
        "os": head[9],
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("rom", type=Path, help="DK64 (US) ROM in any byte order")
    parser.add_argument("--out", type=Path, default=Path("."), help="project root (default: .)")
    args = parser.parse_args()

    rom = to_big_endian(args.rom.read_bytes())
    sha1 = hashlib.sha1(rom).hexdigest()
    if len(rom) != ROM_SIZE or sha1 != US_SHA1:
        sys.exit(f"error: expected DK64 US (sha1 {US_SHA1}), got {sha1}")

    root = args.out
    seg_dir = root / "bin" / "segments"
    seg_dir.mkdir(parents=True, exist_ok=True)
    (root / "baserom.us.z64").write_bytes(rom)

    layout = {"sha1": sha1, "raw": [], "compressed": []}

    for name, start, end, vram in RAW_SEGMENTS:
        (seg_dir / f"{name}.bin").write_bytes(rom[start:end])
        entry = {"name": name, "rom_start": start, "rom_end": end, "vram": vram}
        if name == "boot":
            entry["bss_start"], entry["bss_end"] = BOOT_BSS
        layout["raw"].append(entry)

    for name, index, rom_start, rom_end, vram, vram_end, bss_start, bss_end in GZ_SEGMENTS:
        text = read_gzip_member(rom, rom_start)
        data = read_gzip_member(rom, text["rom_end"])
        padding = rom[data["rom_end"] : rom_end]
        if any(padding) or len(padding) >= 0x10:
            sys.exit(f"error: {name}: unexpected bytes between 0x{data['rom_end']:X} and 0x{rom_end:X}")
        loaded = len(text["payload"]) + len(data["payload"])
        if vram + loaded != bss_start:
            sys.exit(f"error: {name}: text+data 0x{loaded:X} does not end at bss 0x{bss_start:X}")

        streams = []
        for kind, member in (("text", text), ("data", data)):
            out_name = f"{name}.{kind}.bin"
            (seg_dir / out_name).write_bytes(member["payload"])
            streams.append(
                {
                    "kind": kind,
                    "file": f"bin/segments/{out_name}",
                    "rom_start": member["rom_start"],
                    "rom_end": member["rom_end"],
                    "size": len(member["payload"]),
                    "sha1": hashlib.sha1(member["payload"]).hexdigest(),
                    "gzip": {"mtime": member["mtime"], "xfl": member["xfl"], "os": member["os"]},
                }
            )
        layout["compressed"].append(
            {
                "name": name,
                "table_index": index,
                "rom_start": rom_start,
                "rom_end": rom_end,
                "vram": vram,
                "data_vram": vram + len(text["payload"]),
                "vram_end": vram_end,
                "bss_start": bss_start,
                "bss_end": bss_end,
                "streams": streams,
            }
        )

    (root / "bin" / "layout.json").write_text(json.dumps(layout, indent=2) + "\n")
    print(f"extracted {len(RAW_SEGMENTS)} raw and {len(GZ_SEGMENTS)} compressed segments to {seg_dir}")


if __name__ == "__main__":
    main()
