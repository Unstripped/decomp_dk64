#!/usr/bin/env python3
"""Report matching decompilation progress for Donkey Kong 64 (USA).

Reports matched vs total code bytes and function counts per segment
(boot, global, and nine overlays in Makefile order) and overall total.

Usage:
  tools/dk python3 tools/progress.py [--json] [segment]
"""

import argparse
import json
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

# Segments in Makefile OVERLAYS order: boot, global, overlays
SEGMENTS = [
    ("boot", "dk64.us.elf", "dk64.us.map"),
    ("global", "global.elf", "global.map"),
    ("multiplayer", "multiplayer.elf", "multiplayer.map"),
    ("minecart", "minecart.elf", "minecart.map"),
    ("bonus", "bonus.elf", "bonus.map"),
    ("race", "race.elf", "race.map"),
    ("critter", "critter.elf", "critter.map"),
    ("boss", "boss.elf", "boss.map"),
    ("arcade", "arcade.elf", "arcade.map"),
    ("jetpac", "jetpac.elf", "jetpac.map"),
    ("menu", "menu.elf", "menu.map"),
]


def get_unmatched_in_c(c_path: Path) -> set[str]:
    """Return function names still included via GLOBAL_ASM or INCLUDE_ASM in a C file."""
    unmatched = set()
    if not c_path.is_file():
        return unmatched

    with open(c_path, "r", encoding="utf-8", errors="replace") as f:
        content = f.read()

    # #pragma GLOBAL_ASM("asm/nonmatchings/boot/main/func_800004B4.s")
    for m in re.finditer(r"#pragma\s+GLOBAL_ASM\s*\(\s*[\"']([^\"']+)[\"']\s*\)", content):
        asm_path = m.group(1)
        unmatched.add(Path(asm_path).stem)

    # INCLUDE_ASM("asm/nonmatchings/...", func) or INCLUDE_ASM(s32, "...", func, ...)
    for m in re.finditer(r"INCLUDE_ASM\s*\([^)]*?([a-zA-Z0-9_]+)\s*\)", content):
        unmatched.add(m.group(1))

    return unmatched


def parse_map_text_sections(map_path: Path):
    """Parse object file .text section address ranges from a GNU ld map file."""
    if not map_path.is_file():
        raise FileNotFoundError(f"Map file not found: {map_path}")

    with open(map_path, "r", encoding="utf-8", errors="replace") as f:
        content = f.read()

    pattern = re.compile(
        r"^\s*(\.text)\s*\n?\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)\s+(build/[^\n]+\.o)",
        re.MULTILINE,
    )
    sections = []
    for m in pattern.finditer(content):
        addr = int(m.group(2), 16)
        size = int(m.group(3), 16)
        obj = m.group(4).strip()
        if size > 0:
            sections.append((addr, size, obj))
    return sections


def read_elf_symbols(elf_path: Path):
    """Read symbols from a 32-bit big-endian ELF file with readelf fallback."""
    if not elf_path.is_file():
        raise FileNotFoundError(f"ELF file not found: {elf_path}")

    try:
        with open(elf_path, "rb") as f:
            data = f.read()

        if len(data) < 52 or data[:4] != b"\x7fELF":
            raise ValueError(f"Not a valid ELF file: {elf_path}")

        ei_class = data[4]
        ei_data = data[5]
        endian = ">" if ei_data == 2 else "<"

        if ei_class != 1:
            raise ValueError(f"Only 32-bit ELF supported: {elf_path}")

        e_shoff, = struct.unpack_from(endian + "I", data, 32)
        e_shentsize, e_shnum, e_shstrndx = struct.unpack_from(endian + "HHH", data, 46)

        sections = []
        for i in range(e_shnum):
            off = e_shoff + i * e_shentsize
            (
                sh_name,
                sh_type,
                sh_flags,
                sh_addr,
                sh_offset,
                sh_size,
                sh_link,
                sh_info,
                sh_addralign,
                sh_entsize,
            ) = struct.unpack_from(endian + "IIIIIIIIII", data, off)
            sections.append({
                "name_off": sh_name,
                "type": sh_type,
                "flags": sh_flags,
                "addr": sh_addr,
                "offset": sh_offset,
                "size": sh_size,
                "link": sh_link,
                "info": sh_info,
                "entsize": sh_entsize,
            })

        symbols = []
        for s in sections:
            if s["type"] == 2:  # SHT_SYMTAB
                strtab_sec = sections[s["link"]]
                strtab = data[strtab_sec["offset"] : strtab_sec["offset"] + strtab_sec["size"]]
                entsize = s["entsize"] or 16
                count = s["size"] // entsize
                for i in range(count):
                    sym_off = s["offset"] + i * entsize
                    st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack_from(
                        endian + "IIIBBH", data, sym_off
                    )
                    st_type = st_info & 0xF
                    st_bind = st_info >> 4
                    name_end = strtab.find(b"\x00", st_name)
                    name = strtab[st_name:name_end].decode("ascii", "replace")
                    symbols.append({
                        "name": name,
                        "value": st_value,
                        "size": st_size,
                        "type": st_type,
                        "bind": st_bind,
                        "shndx": st_shndx,
                    })
        return symbols

    except Exception:
        # Fallback to readelf tool if direct parsing fails
        readelf_bin = shutil.which("mips-linux-gnu-readelf") or shutil.which("readelf")
        if not readelf_bin:
            raise
        out = subprocess.check_output([readelf_bin, "-W", "-s", str(elf_path)]).decode()
        symbols = []
        for line in out.splitlines():
            parts = line.split()
            if len(parts) >= 8 and parts[0].endswith(":"):
                try:
                    val = int(parts[1], 16)
                    size = int(parts[2], 16) if parts[2].startswith("0x") else int(parts[2])
                    st_type = 2 if parts[3] == "FUNC" else (1 if parts[3] == "OBJECT" else 0)
                    shndx = 0xFFF1 if parts[6] == "ABS" else (0 if parts[6] == "UND" else int(parts[6]))
                    name = parts[7]
                    symbols.append({
                        "name": name,
                        "value": val,
                        "size": size,
                        "type": st_type,
                        "shndx": shndx,
                    })
                except ValueError:
                    pass
        return symbols


def compute_segment_progress(name: str, elf_path: Path, map_path: Path, repo_root: Path):
    """Compute matched and total function bytes and counts for a segment."""
    obj_secs = parse_map_text_sections(map_path)
    symbols = read_elf_symbols(elf_path)

    c_unmatched_cache = {}

    matched_bytes = 0
    matched_funcs = 0
    total_bytes = 0
    total_funcs = 0

    for s in symbols:
        # STT_FUNC = 2, size > 0, shndx < 0xFF00 (not ABS / COMMON / UNDEF)
        if s["type"] != 2 or s["size"] == 0 or s["shndx"] >= 0xFF00:
            continue

        val = s["value"]
        # Find which object file section contains this function
        containing_obj = None
        for sec_addr, sec_size, obj in obj_secs:
            if sec_addr <= val < sec_addr + sec_size:
                containing_obj = obj
                break

        if not containing_obj:
            continue

        total_funcs += 1
        total_bytes += s["size"]

        # Check if compiled from C
        if containing_obj.startswith("build/src/"):
            rel_c_path = Path(containing_obj).relative_to("build/src").with_suffix(".c")
            c_file = repo_root / "src" / rel_c_path
            if c_file not in c_unmatched_cache:
                c_unmatched_cache[c_file] = get_unmatched_in_c(c_file)
            unmatched_funcs = c_unmatched_cache[c_file]

            if s["name"] not in unmatched_funcs:
                matched_funcs += 1
                matched_bytes += s["size"]

    pct = (matched_bytes / total_bytes * 100.0) if total_bytes > 0 else 0.0
    return {
        "name": name,
        "matched_bytes": matched_bytes,
        "total_bytes": total_bytes,
        "percent": pct,
        "matched_funcs": matched_funcs,
        "total_funcs": total_funcs,
        "code": matched_bytes,
        "code/total": total_bytes,
    }


def main():
    parser = argparse.ArgumentParser(
        description="Report matching decompilation progress for Donkey Kong 64 (USA)."
    )
    parser.add_argument(
        "--json",
        action="store_true",
        help="Emit machine-readable JSON output.",
    )
    parser.add_argument(
        "segment",
        nargs="?",
        choices=[s[0] for s in SEGMENTS],
        help="Optional segment name to filter reporting.",
    )

    args = parser.parse_args()

    repo_root = Path(__file__).resolve().parent.parent
    build_dir = repo_root / "build"

    if not build_dir.is_dir():
        sys.exit(f"Error: build directory '{build_dir}' not found. Run 'tools/dk make' first.")

    target_segments = [s for s in SEGMENTS if args.segment is None or s[0] == args.segment]

    results = []
    for name, elf_name, map_name in target_segments:
        elf_path = build_dir / elf_name
        map_path = build_dir / map_name
        if not elf_path.is_file() or not map_path.is_file():
            sys.exit(
                f"Error: missing build files for '{name}' ({elf_name}, {map_name}). "
                f"Run 'tools/dk make' first."
            )
        res = compute_segment_progress(name, elf_path, map_path, repo_root)
        results.append(res)

    # Compute overall total
    total_matched_bytes = sum(r["matched_bytes"] for r in results)
    total_total_bytes = sum(r["total_bytes"] for r in results)
    total_matched_funcs = sum(r["matched_funcs"] for r in results)
    total_total_funcs = sum(r["total_funcs"] for r in results)
    total_pct = (
        (total_matched_bytes / total_total_bytes * 100.0)
        if total_total_bytes > 0
        else 0.0
    )
    total_row = {
        "name": "total",
        "matched_bytes": total_matched_bytes,
        "total_bytes": total_total_bytes,
        "percent": total_pct,
        "matched_funcs": total_matched_funcs,
        "total_funcs": total_total_funcs,
        "code": total_matched_bytes,
        "code/total": total_total_bytes,
    }

    if args.json:
        json_data = {}
        for r in results:
            json_data[r["name"]] = {
                "matched_bytes": r["matched_bytes"],
                "total_bytes": r["total_bytes"],
                "percent": r["percent"],
                "matched_funcs": r["matched_funcs"],
                "total_funcs": r["total_funcs"],
                "code": r["code"],
                "code/total": r["code/total"],
            }
        json_data["total"] = {
            "matched_bytes": total_row["matched_bytes"],
            "total_bytes": total_row["total_bytes"],
            "percent": total_row["percent"],
            "matched_funcs": total_row["matched_funcs"],
            "total_funcs": total_row["total_funcs"],
            "code": total_row["code"],
            "code/total": total_row["code/total"],
        }
        print(json.dumps(json_data, indent=2))
        return

    # Text table output
    print(f"{'Segment':<15s} {'Matched / Total Bytes':>23s}   {'Percent':>7s}   {'Matched / Total Funcs':>21s}")
    for r in results:
        bytes_str = f"{r['matched_bytes']:>7d} / {r['total_bytes']:>7d}"
        funcs_str = f"{r['matched_funcs']:>5d} / {r['total_funcs']:>5d}"
        print(f"{r['name']:<15s} {bytes_str:>23s}   {r['percent']:>6.2f}%   {funcs_str:>21s}")

    # Separator line and total row
    print("-" * 75)
    total_bytes_str = f"{total_row['matched_bytes']:>7d} / {total_row['total_bytes']:>7d}"
    total_funcs_str = f"{total_row['matched_funcs']:>5d} / {total_row['total_funcs']:>5d}"
    print(f"{'Total':<15s} {total_bytes_str:>23s}   {total_row['percent']:>6.2f}%   {total_funcs_str:>21s}")


if __name__ == "__main__":
    main()
