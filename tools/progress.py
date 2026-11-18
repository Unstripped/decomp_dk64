#!/usr/bin/env python3
"""Report matching decompilation progress for Donkey Kong 64 (USA).

Reports matched vs total code bytes and function counts per segment
(boot, global, and nine overlays in Makefile order) and overall total.
Matched includes compiled C and the handwritten files in handwritten_asm.json;
both categories are reported separately. Only ELF function bytes are counted,
not alignment padding or data embedded in assembly.

Data (.data + .rodata input sections from the map, raw assets and the ROM header
excluded) is counted separately: C, ROM-extracted includes (data_inc.us.txt),
handwritten-asm data (registry objects) and asm (other splat asm plus data
still included via GLOBAL_ASM in a C file).

Usage:
  tools/dk python3 tools/progress.py [--json] [segment]
  tools/dk python3 tools/progress.py --readme   # rewrite README.md progress section
"""

import argparse
import bisect
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

# Code stream of each segment: (file under bin/segments/ or the boot ROM image,
# VRAM of that file's byte 0). Boot is the ROM itself (valid from file offset 0x1050).
SEGMENT_STREAMS = {
    "boot": ("baserom.us.z64", 0x7FFFF400),
    "global": ("bin/segments/global.bin", 0x805FB300),
    **{
        name: (f"bin/segments/ovl{n:02d}.bin", 0x80024000)
        for n, name in enumerate(
            ["multiplayer", "minecart", "bonus", "race", "critter", "boss", "arcade", "jetpac", "menu"], 2)
    },
}


def segment_paths(build_dir: Path, seg: str) -> tuple[Path, Path]:
    """(ELF, map) of a segment name from SEGMENTS."""
    for name, elf, map_name in SEGMENTS:
        if name == seg:
            return build_dir / elf, build_dir / map_name
    raise KeyError(seg)


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


def parse_map_data_sections(map_path: Path):
    """Return (section, addr, size, obj) for every non-empty .data/.rodata input section.

    Rows before the "Linker script and memory map" line (the Discarded input sections
    block) are ignored.
    """
    if not map_path.is_file():
        raise FileNotFoundError(f"Map file not found: {map_path}")

    content = map_path.read_text(encoding="utf-8", errors="replace")
    marker = content.find("Linker script and memory map")
    if marker >= 0:
        content = content[marker:]
    pattern = re.compile(
        r"^\s*(\.data|\.rodata)\s*\n?\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)\s+(build/[^\n]+\.o)",
        re.MULTILINE,
    )
    sections = []
    for m in pattern.finditer(content):
        size = int(m.group(3), 16)
        if size > 0:
            sections.append((m.group(1), int(m.group(2), 16), size, m.group(4).strip()))
    return sections


_DIRECTIVE_SIZES = {".word": 4, ".float": 4, ".short": 2, ".half": 2, ".byte": 1, ".double": 8}
_STRING_ESCAPE = re.compile(r"\\([0-7]{1,3}|.)")


def _split_operands(text: str) -> list[str]:
    """Comma-separated directive operands, ignoring commas inside string literals."""
    operands, cur, in_str, i = [], "", False, 0
    while i < len(text):
        ch = text[i]
        if in_str and ch == "\\" and i + 1 < len(text):
            cur += text[i:i + 2]
            i += 2
            continue
        if ch == '"':
            in_str = not in_str
        if ch == "," and not in_str:
            operands.append(cur.strip())
            cur = ""
        else:
            cur += ch
        i += 1
    if cur.strip():
        operands.append(cur.strip())
    return operands


def _string_length(literal: str) -> int:
    """Byte length of a quoted gas string literal; every escape counts as one byte."""
    body = literal.strip()
    if body.startswith('"') and body.endswith('"'):
        body = body[1:-1]
    return len(_STRING_ESCAPE.sub("x", body))


def asm_data_size(s_path: Path) -> int:
    """Bytes a splat data `.s` emits: sized directives, strings, `.space` and `.align`."""
    size = 0
    for raw in s_path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = re.sub(r"/\*.*?\*/", "", raw).strip()
        m = re.match(r"(\.[a-z0-9_]+)\s*(.*)$", line)
        if not m:
            continue
        directive, rest = m.group(1), m.group(2)
        if directive in _DIRECTIVE_SIZES:
            size += _DIRECTIVE_SIZES[directive] * len(_split_operands(rest))
        elif directive in (".asciz", ".ascii"):
            extra = 1 if directive == ".asciz" else 0
            size += sum(_string_length(op) + extra for op in _split_operands(rest))
        elif directive == ".space":
            size += int(_split_operands(rest)[0], 0)
        elif directive == ".align":
            align = 1 << int(rest, 0)
            size = (size + align - 1) // align * align
    return size


def read_data_inc(manifest: Path) -> list[dict]:
    """Rows of data_inc.us.txt: `seg name vram size width file`, `#` comments."""
    rows = []
    if not manifest.is_file():
        return rows
    for lineno, line in enumerate(manifest.read_text(encoding="utf-8").splitlines(), 1):
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) != 6:
            raise ValueError(f"{manifest}:{lineno}: expected 6 columns, got {len(parts)}")
        seg, name, vram, size, width, file = parts
        rows.append({
            "line": lineno, "seg": seg, "name": name, "vram": int(vram, 0),
            "size": int(size, 0), "width": int(width, 0), "file": file,
        })
    return rows


def handwritten_registry_objects(repo_root: Path) -> set[str]:
    """`build/<path>.o` for every asm path in handwritten_asm.json."""
    return {
        f"build/{Path(path).with_suffix('.o').as_posix()}"
        for path in json.loads((repo_root / "handwritten_asm.json").read_text(encoding="utf-8"))
        if path.startswith("asm/")
    }


def global_asm_paths(c_path: Path) -> list[str]:
    """Every `#pragma GLOBAL_ASM` path in a C file."""
    content = c_path.read_text(encoding="utf-8", errors="replace")
    return re.findall(r"#pragma\s+GLOBAL_ASM\s*\(\s*[\"']([^\"']+)[\"']\s*\)", content)


def compute_segment_data(name: str, elf_path: Path, map_path: Path, repo_root: Path):
    """Initialised data bytes (.data + .rodata) of a segment by origin.

    c: compiled from C; extracted: C arrays initialised from ROM-extracted includes
    (data_inc.us.txt); handwritten: asm objects registered in handwritten_asm.json;
    asm: other splat asm, plus data still included via GLOBAL_ASM in a C file.
    Raw objects (build/assets/*, the ROM header) are not counted.
    """
    handwritten_objects = handwritten_registry_objects(repo_root)
    func_names = {s["name"] for s in read_elf_symbols(elf_path) if s["type"] == 2}
    inc_rows = read_data_inc(repo_root / "data_inc.us.txt")
    totals = {"c": 0, "extracted": 0, "handwritten": 0, "asm": 0}
    seen_c = set()
    for _section, _addr, size, obj in parse_map_data_sections(map_path):
        if obj.startswith("build/assets/") or obj == "build/asm/header.o":
            continue
        if obj in handwritten_objects:
            totals["handwritten"] += size
        elif obj.startswith("build/asm/"):
            totals["asm"] += size
        elif obj.startswith("build/src/"):
            totals["c"] += size
            c_rel = Path(obj).relative_to("build").with_suffix(".c")
            if c_rel in seen_c:
                continue
            seen_c.add(c_rel)
            c_file = repo_root / c_rel
            if not c_file.is_file():
                continue
            for asm_path in global_asm_paths(c_file):
                if Path(asm_path).stem in func_names:
                    continue
                moved = asm_data_size(repo_root / asm_path)
                totals["c"] -= moved
                totals["asm"] += moved
            for row in inc_rows:
                if row["file"] == c_rel.as_posix():
                    totals["c"] -= row["size"]
                    totals["extracted"] += row["size"]
    return data_keys(totals)


def data_keys(totals: dict) -> dict:
    """Result keys for data byte totals {c, extracted, handwritten, asm}."""
    total = sum(totals.values())
    done = totals["c"] + totals["extracted"] + totals["handwritten"]
    return {
        "data_c_bytes": totals["c"],
        "data_extracted_bytes": totals["extracted"],
        "data_handwritten_bytes": totals["handwritten"],
        "data_asm_bytes": totals["asm"],
        "data_total_bytes": total,
        "data_percent": (done / total * 100.0) if total > 0 else 0.0,
    }


def data_done(r: dict) -> int:
    return r["data_c_bytes"] + r["data_extracted_bytes"] + r["data_handwritten_bytes"]


def read_elf_sections(data: bytes) -> tuple[str, list[dict]]:
    """Return (struct endian prefix, section header dicts) of a 32-bit ELF image."""
    if len(data) < 52 or data[:4] != b"\x7fELF":
        raise ValueError("not a valid ELF file")

    ei_class = data[4]
    ei_data = data[5]
    endian = ">" if ei_data == 2 else "<"

    if ei_class != 1:
        raise ValueError("only 32-bit ELF supported")

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
    return endian, sections


def read_elf_symbols(elf_path: Path):
    """Read symbols from a 32-bit big-endian ELF file with readelf fallback."""
    if not elf_path.is_file():
        raise FileNotFoundError(f"ELF file not found: {elf_path}")

    try:
        with open(elf_path, "rb") as f:
            data = f.read()

        endian, sections = read_elf_sections(data)

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


def iter_segment_functions(elf_path: Path, map_path: Path, repo_root: Path):
    """Yield ELF functions with obj, c_file, c_matched, handwritten, and matched."""
    obj_secs = sorted(parse_map_text_sections(map_path))
    starts = [a for a, _, _ in obj_secs]
    c_unmatched_cache = {}
    handwritten_objects = handwritten_registry_objects(repo_root)

    for s in read_elf_symbols(elf_path):
        # STT_FUNC = 2, size > 0, shndx < 0xFF00 (not ABS / COMMON / UNDEF)
        if s["type"] != 2 or s["size"] == 0 or s["shndx"] >= 0xFF00:
            continue

        val = s["value"]
        # Object file whose .text section contains this function
        i = bisect.bisect_right(starts, val) - 1
        if i < 0:
            continue
        sec_addr, sec_size, obj = obj_secs[i]
        if val >= sec_addr + sec_size:
            continue

        # Unlisted assembly and GLOBAL_ASM/INCLUDE_ASM placeholders remain unmatched.
        c_file = None
        c_matched = False
        handwritten = obj in handwritten_objects
        if obj.startswith("build/src/"):
            c_file = repo_root / "src" / Path(obj).relative_to("build/src").with_suffix(".c")
            if c_file not in c_unmatched_cache:
                c_unmatched_cache[c_file] = get_unmatched_in_c(c_file)
            c_matched = s["name"] not in c_unmatched_cache[c_file]

        yield {
            **s, "obj": obj, "c_file": c_file,
            "c_matched": c_matched, "handwritten": handwritten,
            "matched": c_matched or handwritten,
        }


def compute_segment_progress(name: str, elf_path: Path, map_path: Path, repo_root: Path):
    """Compute C, handwritten assembly, matched, and total function bytes/counts."""
    c_matched_bytes = 0
    c_matched_funcs = 0
    handwritten_bytes = 0
    handwritten_funcs = 0
    total_bytes = 0
    total_funcs = 0

    for f in iter_segment_functions(elf_path, map_path, repo_root):
        total_funcs += 1
        total_bytes += f["size"]
        if f["c_matched"]:
            c_matched_funcs += 1
            c_matched_bytes += f["size"]
        elif f["handwritten"]:
            handwritten_funcs += 1
            handwritten_bytes += f["size"]

    matched_bytes = c_matched_bytes + handwritten_bytes
    matched_funcs = c_matched_funcs + handwritten_funcs
    pct = (matched_bytes / total_bytes * 100.0) if total_bytes > 0 else 0.0
    return {
        "name": name,
        "c_matched_bytes": c_matched_bytes,
        "c_matched_funcs": c_matched_funcs,
        "handwritten_bytes": handwritten_bytes,
        "handwritten_funcs": handwritten_funcs,
        "matched_bytes": matched_bytes,
        "total_bytes": total_bytes,
        "percent": pct,
        "matched_funcs": matched_funcs,
        "total_funcs": total_funcs,
        "code": matched_bytes,
        "code/total": total_bytes,
        **compute_segment_data(name, elf_path, map_path, repo_root),
    }


README_START = "<!-- progress:start -->"
README_END = "<!-- progress:end -->"

# Short description per segment for the README table.
SEGMENT_NOTES = {
    "boot": "boot, libultra, inflate",
    "global": "main game code",
    "multiplayer": "`ovl02`, multiplayer modes",
    "minecart": "`ovl03`, minecart rides",
    "bonus": "`ovl04`, bonus barrels",
    "race": "`ovl05`, races",
    "critter": "`ovl06`, critter minigames",
    "boss": "`ovl07`, boss fights",
    "arcade": "`ovl08`, Donkey Kong arcade",
    "jetpac": "`ovl09`, Jetpac",
    "menu": "`ovl10`, main menu / file select",
}


def progress_bar(percent: float, width: int = 20) -> str:
    """Unicode bar in a code span: GitHub markdown strips <progress>."""
    filled = int(round(percent / 100.0 * width))
    return "`" + "█" * filled + "░" * (width - filled) + "`"


def render_markdown(results, total_row) -> str:
    """Progress section for README.md: overall bar plus one row per segment."""
    lines = [
        README_START,
        f"**Overall: {total_row['percent']:.2f}%** of code bytes matched "
        f"({total_row['matched_bytes']:,} / {total_row['total_bytes']:,} bytes, "
        f"{total_row['matched_funcs']:,} / {total_row['total_funcs']:,} functions)",
        "",
        progress_bar(total_row["percent"], 40),
        "",
        f"**Data: {total_row['data_percent']:.2f}%** of initialised data bytes (.data + .rodata) "
        "are C, ROM-extracted (`tools/data_inc.py`) or handwritten-asm data "
        f"({data_done(total_row):,} / {total_row['data_total_bytes']:,} bytes)",
        "",
        "| Segment | Contents | Progress | C bytes | Handwritten bytes | Matched / total bytes | Functions | Data |",
        "|---|---|---|--:|--:|--:|--:|--:|",
    ]
    for r in results + [total_row]:
        name = "**Total**" if r is total_row else f"`{r['name']}`"
        notes = "" if r is total_row else SEGMENT_NOTES.get(r["name"], "")
        lines.append(
            f"| {name} | {notes} | {progress_bar(r['percent'])} {r['percent']:.1f}% "
            f"| {r['c_matched_bytes']:,} | {r['handwritten_bytes']:,} "
            f"| {r['matched_bytes']:,} / {r['total_bytes']:,} "
            f"| {r['matched_funcs']:,} / {r['total_funcs']:,} "
            f"| {r['data_percent']:.1f}% ({data_done(r):,} / {r['data_total_bytes']:,}) |"
        )
    lines.append(README_END)
    return "\n".join(lines)


def update_readme(readme: Path, section: str) -> None:
    """Replace the text between the progress markers in README.md."""
    text = readme.read_text(encoding="utf-8")
    start = text.find(README_START)
    end = text.find(README_END)
    if start < 0 or end < start:
        sys.exit(f"Error: {readme} lacks the {README_START} / {README_END} markers.")
    readme.write_text(text[:start] + section + text[end + len(README_END):], encoding="utf-8")


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
        "--readme",
        action="store_true",
        help="Rewrite the progress section of README.md (all segments).",
    )
    parser.add_argument(
        "segment",
        nargs="?",
        choices=[s[0] for s in SEGMENTS],
        help="Optional segment name to filter reporting.",
    )

    args = parser.parse_args()
    if args.readme and args.segment:
        parser.error("--readme reports every segment; drop the segment argument.")

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
        "c_matched_bytes": sum(r["c_matched_bytes"] for r in results),
        "c_matched_funcs": sum(r["c_matched_funcs"] for r in results),
        "handwritten_bytes": sum(r["handwritten_bytes"] for r in results),
        "handwritten_funcs": sum(r["handwritten_funcs"] for r in results),
        "matched_bytes": total_matched_bytes,
        "total_bytes": total_total_bytes,
        "percent": total_pct,
        "matched_funcs": total_matched_funcs,
        "total_funcs": total_total_funcs,
        "code": total_matched_bytes,
        "code/total": total_total_bytes,
        **data_keys({
            key: sum(r[f"data_{key}_bytes"] for r in results)
            for key in ("c", "extracted", "handwritten", "asm")
        }),
    }

    if args.readme:
        update_readme(repo_root / "README.md", render_markdown(results, total_row))
        return

    if args.json:
        json_data = {
            r["name"]: {key: value for key, value in r.items() if key != "name"}
            for r in results + [total_row]
        }
        print(json.dumps(json_data, indent=2))
        return

    # Text table output, with handwritten bytes separate from compiled C.
    print(
        f"{'Segment':<15s} {'C Bytes':>9s} {'Hand ASM':>9s} "
        f"{'Matched / Total Bytes':>23s}   {'Percent':>7s}   {'Matched / Total Funcs':>21s}   {'Data':>7s}"
    )
    for r in results + [total_row]:
        if r is total_row:
            print("-" * 116)
        name = "Total" if r is total_row else r["name"]
        bytes_str = f"{r['matched_bytes']:>7d} / {r['total_bytes']:>7d}"
        funcs_str = f"{r['matched_funcs']:>5d} / {r['total_funcs']:>5d}"
        print(
            f"{name:<15s} {r['c_matched_bytes']:>9d} {r['handwritten_bytes']:>9d} "
            f"{bytes_str:>23s}   {r['percent']:>6.2f}%   {funcs_str:>21s}   {r['data_percent']:>6.2f}%"
        )


if __name__ == "__main__":
    main()
