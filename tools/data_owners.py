#!/usr/bin/env python3
"""Find the text owners of a segment's data objects from the relocations of a built tree.

    python3 tools/data_owners.py <seg> [--range 0xLO-0xHI] [--all]

<seg> is `boot`, `global` or an overlay name; reads build/<seg>.map/.elf (boot:
build/dk64.us.map/.elf) and every object the map names, so it works on a mixed C/asm
tree (tools/rodata_owners.py needs an all-asm split). Run after `tools/dk make`.

Data objects: every symbol inside a .data/.rodata input section of the map's objects.
Listed: those of build/asm/** objects plus the labels a C file still includes via
GLOBAL_ASM; `--all` lists the C-defined ones too (they always take part in owner
propagation, so a C pointer table passes its owners to asm targets). An object's size
runs to the next symbol or its section end, capped by its .size. `--range` takes VRAMs,
or segment file offsets (the yaml's) below 0x80000000. A RUN never bridges an
unlisted object.

Owners: the src stems (.c/.s basename) whose .text relocations (R_MIPS_32, HI16/LO16)
hit the object; an object without one inherits the owners of the data objects whose
.data/.rodata relocations point at it (`via <label>`), else `-`.

Output: `0x<vram> 0x<size> <label> <kinds> <owners>` per object (kinds from the asm
source: s string, f float, d double, w word/blob, J jump table; `p` has R_MIPS_32
relocations, `F` one targets a function; `.` none known), then one
`RUN 0x<lo>-0x<hi> <owners> [PAD16] [ORDER?]` per maximal run of objects with the
same owners. PAD16: the run ends with 4+ zero bytes on a 16-aligned address (a TU-end
candidate). ORDER?: the run's first owner comes earlier in .text order than the
previous run's (data order equals text order across TUs).
"""

import argparse
import bisect
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from progress import (  # noqa: E402
    SEGMENT_STREAMS,
    global_asm_paths,
    read_elf_sections,
    segment_paths,
)

REPO = Path(__file__).resolve().parent.parent
MAP_ROW = re.compile(
    r"^\s*(\.[A-Za-z_.]+)\s*\n?\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)\s+(build/[^\n]+\.o)",
    re.MULTILINE,
)
DATA_SECTIONS = (".data", ".rodata")
LINKER_SYMBOL = re.compile(r"(_ROM_START|_ROM_END|_VRAM|_VRAM_END|_START|_END|_SIZE)$")
R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16 = 2, 4, 5, 6
STT_FUNC, STT_SECTION, STT_FILE = 2, 3, 4
SHN_UNDEF, SHN_ABS, SHN_COMMON = 0, 0xFFF1, 0xFFF2
LABEL = re.compile(r"\s*(?:dlabel|jlabel|glabel)\s+(\w+)")
KIND = re.compile(r"\.(word|float|double|asciz|ascii|short|byte|space)\b")


def map_rows(map_path: Path) -> list[tuple[str, int, int, str]]:
    """(section, addr, size, obj) for every input section after the memory map line."""
    content = map_path.read_text(encoding="utf-8", errors="replace")
    marker = content.find("Linker script and memory map")
    if marker >= 0:
        content = content[marker:]
    return [
        (m.group(1), int(m.group(2), 16), int(m.group(3), 16), m.group(4).strip())
        for m in MAP_ROW.finditer(content)
    ]


class Elf:
    """Sections (with names and contents), symbols and REL entries of a 32-bit ELF."""

    def __init__(self, path: Path):
        self.data = path.read_bytes()
        self.endian, self.sections = read_elf_sections(self.data)
        shstrndx = struct.unpack_from(self.endian + "H", self.data, 50)[0]
        strtab = self.sections[shstrndx]
        for s in self.sections:
            start = strtab["offset"] + s["name_off"]
            s["name"] = self.data[start:self.data.index(b"\0", start)].decode("ascii", "replace")
        self.symbols = []
        for s in self.sections:
            if s["type"] != 2:  # SHT_SYMTAB
                continue
            names = self.sections[s["link"]]
            for i in range(s["size"] // 16):
                name_off, value, size, info, _other, shndx = struct.unpack_from(
                    self.endian + "IIIBBH", self.data, s["offset"] + i * 16)
                start = names["offset"] + name_off
                name = self.data[start:self.data.index(b"\0", start)].decode("ascii", "replace")
                self.symbols.append({
                    "name": name, "value": value, "size": size,
                    "type": info & 0xF, "bind": info >> 4, "shndx": shndx,
                })

    def section_bytes(self, index: int) -> bytes:
        s = self.sections[index]
        if s["type"] == 8:  # SHT_NOBITS
            return bytes(s["size"])
        return self.data[s["offset"]:s["offset"] + s["size"]]

    def rels(self):
        """Yield (target section index, r_offset, symbol index, type) of every SHT_REL entry."""
        for s in self.sections:
            if s["type"] != 9:  # SHT_REL
                continue
            for i in range(s["size"] // 8):
                r_offset, r_info = struct.unpack_from(self.endian + "II", self.data, s["offset"] + i * 8)
                yield s["info"], r_offset, r_info >> 8, r_info & 0xFF


def parse_range(text: str, seg: str) -> tuple[int, int]:
    lo, hi = (int(v, 16) for v in text.split("-"))
    base = SEGMENT_STREAMS[seg][1]
    if lo < 0x80000000:
        lo += base
    if hi < 0x80000000:
        hi += base
    return lo, hi


def stem(obj: str) -> str:
    return Path(obj).name.split(".")[0]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("seg", choices=sorted(SEGMENT_STREAMS))
    ap.add_argument("--range", help="0xLO-0xHI (VRAM, or segment file offsets)")
    ap.add_argument("--all", action="store_true", help="also list C-defined data objects")
    args = ap.parse_args()

    build = REPO / "build"
    elf_path, map_path = segment_paths(build, args.seg)
    if not map_path.is_file() or not elf_path.is_file():
        print(f"no {map_path.relative_to(REPO)}: run tools/dk make", file=sys.stderr)
        return 1

    rows = map_rows(map_path)
    # (obj, section name) -> map address; data rows sorted by address
    sec_addr = {(obj, sec): addr for sec, addr, size, obj in rows if size > 0}
    data_rows = sorted(
        (addr, size, sec, obj) for sec, addr, size, obj in rows
        if sec in DATA_SECTIONS and size > 0
        and not obj.startswith("build/assets/") and obj != "build/asm/header.o"
    )
    text_order = {}
    for sec, addr, size, obj in sorted(rows, key=lambda r: r[1]):
        if sec == ".text" and size > 0:
            text_order.setdefault(stem(obj), len(text_order))

    # Global names: the segment's ELF first, then global, then boot.
    chain = [elf_path]
    if args.seg != "boot":
        if args.seg != "global":
            chain.append(build / "global.elf")
        chain.append(build / "dk64.us.elf")
    names, func_addrs = {}, set()
    seg_elf = None
    for path in chain:
        elf = Elf(path)
        seg_elf = seg_elf or elf
        for s in elf.symbols:
            if s["shndx"] == SHN_UNDEF or s["type"] in (STT_SECTION, STT_FILE) or not s["name"]:
                continue
            names.setdefault(s["name"], s["value"])
            if s["type"] == STT_FUNC:
                func_addrs.add(s["value"])

    # Pragma data labels still included by C files.
    pragma_labels = set()
    asm_sources = []
    for obj in {obj for _, _, _, obj in data_rows if obj.startswith("build/src/")}:
        c_file = REPO / Path(obj).relative_to("build").with_suffix(".c")
        if not c_file.is_file():
            continue
        for p in global_asm_paths(c_file):
            pragma_labels.add(Path(p).stem)
            asm_sources.append(REPO / p)
    pragma_labels -= {name for name, value in names.items() if value in func_addrs}

    # Every map object's ELF (asm and C), loaded once.
    elfs = {}
    for obj in sorted({obj for _, _, _, obj in rows}):
        path = REPO / obj
        if (obj.startswith("build/src/") or obj.startswith("build/asm/")) and path.is_file():
            elfs[obj] = Elf(path)

    # Data objects from each input object's own symbols (locals included). Size: to the
    # next symbol of that section or its end, capped by the symbol's own .size.
    objects = []
    for addr, size, sec, obj in data_rows:
        elf = elfs.get(obj)
        if elf is None:
            continue
        syms = {}
        for s in elf.symbols:
            if (s["shndx"] in (SHN_UNDEF, SHN_ABS, SHN_COMMON) or s["type"] in (STT_SECTION, STT_FILE)
                    or not s["name"] or s["name"].startswith(".") or s["name"].startswith("$")
                    or elf.sections[s["shndx"]]["name"] != sec):
                continue
            prev = syms.get(s["value"])
            if prev is None or (prev["name"].startswith("D_") and not s["name"].startswith("D_")):
                syms[s["value"]] = s
        offsets = sorted(syms)
        for k, off in enumerate(offsets):
            s = syms[off]
            # C-defined objects stay in the graph (their pointers propagate ownership); only listed with --all.
            listed = args.all or not obj.startswith("build/src/") or s["name"] in pragma_labels
            end = offsets[k + 1] if k + 1 < len(offsets) else size
            if s["size"]:
                end = min(end, off + s["size"])
            objects.append({"addr": addr + off, "size": end - off, "name": s["name"], "obj": obj,
                            "sec": sec, "text": set(), "via": set(), "p": False, "F": False,
                            "k": len(objects), "listed": listed})
    obj_starts = [o["addr"] for o in objects]

    def find(addr):
        k = bisect.bisect_right(obj_starts, addr) - 1
        if k >= 0 and addr < objects[k]["addr"] + objects[k]["size"]:
            return objects[k]
        return None

    # Relocations of every object in the map.
    for obj, elf in elfs.items():
        hi_pending = {}
        for target_sec, r_offset, sym_index, rtype in elf.rels():
            if rtype not in (R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16):
                continue
            sec_name = elf.sections[target_sec]["name"]
            base = sec_addr.get((obj, sec_name))
            if base is None:
                continue
            raw = elf.section_bytes(target_sec)
            word = struct.unpack_from(elf.endian + "I", raw, r_offset)[0]
            if rtype == R_MIPS_HI16:
                hi_pending[sym_index] = word & 0xFFFF
                continue
            if rtype == R_MIPS_LO16:
                lo = word & 0xFFFF
                addend = (hi_pending.get(sym_index, 0) << 16) + (lo - 0x10000 if lo & 0x8000 else lo)
            else:
                addend = word
            sym = elf.symbols[sym_index]
            if sym["shndx"] == SHN_UNDEF:
                if sym["name"] not in names:
                    continue
                target = names[sym["name"]] + addend
            elif sym["shndx"] == SHN_ABS:
                target = sym["value"] + addend
            else:
                own = sec_addr.get((obj, elf.sections[sym["shndx"]]["name"]))
                if own is None:
                    continue
                target = own + sym["value"] + addend
            target &= 0xFFFFFFFF
            dst = find(target)
            if sec_name == ".text":
                if dst is not None:
                    dst["text"].add(stem(obj))
                continue
            src = find(base + r_offset) if sec_name in DATA_SECTIONS else None
            if src is None:
                continue
            if rtype == R_MIPS_32:
                src["p"] = True
                if target in func_addrs:
                    src["F"] = True
            if dst is not None and dst is not src:
                dst["via"].add(src["k"])

    # Inherited owners, to a fixed point (objects keyed by index: static names repeat).
    index = {id(o): o["k"] for o in objects}
    owners = [set(o["text"]) for o in objects]
    via_label = {}
    changed = True
    while changed:
        changed = False
        for k, o in enumerate(objects):
            if o["text"]:
                continue
            for parent in sorted(o["via"]):
                extra = owners[parent] - owners[k]
                if extra:
                    owners[k] |= extra
                    via_label.setdefault(k, objects[parent]["name"])
                    changed = True

    # Kinds from asm sources.
    kinds = {}
    if args.seg == "boot":
        asm_sources += sorted((REPO / "asm" / "data").rglob("*.s"))
    else:
        asm_sources += sorted((REPO / "asm" / args.seg / "data").glob("*.s"))
    for path in asm_sources:
        if not path.is_file():
            continue
        cur = None
        for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
            m = LABEL.match(line)
            if m:
                cur = m.group(1)
                if cur.startswith("jtbl"):
                    kinds[cur] = "J"
                continue
            if cur is None or cur in kinds:
                continue
            k = KIND.search(line)
            if k:
                kinds[cur] = {"float": "f", "double": "d", "asciz": "s", "ascii": "s"}.get(k.group(1), "w")

    lo, hi = parse_range(args.range, args.seg) if args.range else (0, 0xFFFFFFFF)
    shown = [o for o in objects if lo <= o["addr"] < hi and o["listed"]]

    def order_key(s):
        return (text_order.get(s, 1 << 30), s)

    for o in shown:
        k = index[id(o)]
        kind = kinds.get(o["name"], "") + ("p" if o["p"] else "") + ("F" if o["F"] else "")
        own = ",".join(sorted(owners[k], key=order_key)) or "-"
        if owners[k] and not o["text"]:
            own += f" via {via_label[k]}"
        print(f"0x{o['addr']:08X} 0x{o['size']:X} {o['name']} {kind or '.'} {own}")

    runs = []
    for o in shown:
        key = frozenset(owners[index[id(o)]])
        # An unlisted (C) object between two listed ones ends the run: no bridging over omitted ranges.
        if (runs and runs[-1]["key"] == key and runs[-1]["last"]["sec"] == o["sec"]
                and o["k"] == runs[-1]["last"]["k"] + 1):
            runs[-1]["end"] = o["addr"] + o["size"]
            runs[-1]["last"] = o
        else:
            runs.append({"key": key, "lo": o["addr"], "end": o["addr"] + o["size"], "last": o})
    prev_first, prev_sec = None, None
    for run in runs:
        flags = []
        last = run["last"]
        if last["sec"] != prev_sec:
            prev_first, prev_sec = None, last["sec"]
        if run["end"] % 16 == 0 and last["size"] >= 4:
            data = object_bytes(last, elfs, sec_addr)
            if data is not None and data[-4:] == b"\0\0\0\0":
                flags.append("PAD16")
        first = min((text_order.get(s, 1 << 30) for s in run["key"]), default=None)
        if first is not None:
            if prev_first is not None and first < prev_first:
                flags.append("ORDER?")
            prev_first = first
        own = ",".join(sorted(run["key"], key=order_key)) or "-"
        print(f"RUN 0x{run['lo']:08X}-0x{run['end']:08X} {own}" + "".join(" " + f for f in flags))
    return 0


def object_bytes(o, elfs, sec_addr):
    """The bytes of a data object, from its input section in the built object file."""
    elf = elfs.get(o["obj"])
    if elf is None:
        return None
    for i, s in enumerate(elf.sections):
        if s["name"] == o["sec"]:
            off = o["addr"] - sec_addr[(o["obj"], o["sec"])]
            return elf.section_bytes(i)[off:off + o["size"]]
    return None


if __name__ == "__main__":
    sys.exit(main())
