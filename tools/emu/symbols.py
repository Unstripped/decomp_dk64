#!/usr/bin/env python3
"""DK64 address ↔ function symbolizer and overlay detector.

Parses ELF32 big-endian symbols (.symtab/.strtab) from build/dk64.us.elf (boot),
build/global.elf (global), and build/<overlay>.elf (multiplayer, minecart, bonus,
race, critter, boss, arcade, jetpac, menu).

Provides function symbol lookup, address-to-function resolution with overlay
disambiguation, and runtime overlay identification.
"""

import argparse
import bisect
import os
import struct
import sys
from pathlib import Path
from typing import Callable, Dict, List, Optional, Tuple, Union

OVERLAYS: List[str] = [
    "multiplayer",
    "minecart",
    "bonus",
    "race",
    "critter",
    "boss",
    "arcade",
    "jetpac",
    "menu",
]

SEGMENTS: List[str] = ["boot", "global"] + OVERLAYS

OVERLAY_VRAM_START: int = 0x80024000
GLOBAL_VRAM_START: int = 0x805FB300
OVERLAY_WINDOW_SIZE: int = 0x200  # 512 bytes uniquely distinguishes all 9 overlays
ADDR_LOADED_OVERLAY_RECORD: int = 0x80744470
ADDR_GAME_MODE: int = 0x807444EC

OVERLAY_END_VRAM: Dict[int, str] = {
    0x80027140: "multiplayer",
    0x80028E40: "minecart",
    0x8002DF40: "bonus",
    0x80030180: "race",
    0x8002A200: "critter",
    0x80036E00: "boss",
    0x8004C780: "arcade",
    0x80045C00: "jetpac",
    0x80034000: "menu",
}

_FINGERPRINT_CACHE: Dict[Tuple[Path, int], Dict[str, bytes]] = {}


def _find_repo_root() -> Path:
    """Find repository root containing build/ directory."""
    candidate = Path(__file__).resolve().parents[2]
    if (candidate / "build" / "dk64.us.elf").is_file():
        return candidate
    cwd = Path.cwd().resolve()
    if (cwd / "build" / "dk64.us.elf").is_file():
        return cwd
    return candidate


class Symbols:
    """Symbol database for boot, global, and overlay segments."""

    def __init__(self, repo_root: Union[str, Path]):
        self.repo_root = Path(repo_root).resolve()
        # segment -> sorted list of (name, start_addr, size)
        self._segments: Dict[str, List[Tuple[str, int, int]]] = {}
        # segment -> sorted list of (name, addr, size) for data/rodata/bss symbols
        self._data: Dict[str, List[Tuple[str, int, int]]] = {}
        # global name -> (start_addr, segment)
        self._name_index: Dict[str, Tuple[int, str]] = {}
        self._load_all()

    def _parse_elf(
        self, elf_path: Path, seg: str
    ) -> Tuple[List[Tuple[str, int, int]], List[Tuple[str, int, int]]]:
        """Parse ELF32 big-endian symtab: (functions, data symbols), both sorted by address."""
        with open(elf_path, "rb") as f:
            data = f.read()

        if len(data) < 52 or data[:4] != b"\x7fELF":
            raise ValueError(f"Not a valid 32-bit ELF file: {elf_path}")

        endian = ">"
        (e_shoff,) = struct.unpack_from(endian + "I", data, 32)
        e_shentsize, e_shnum, e_shstrndx = struct.unpack_from(
            endian + "HHH", data, 46
        )

        shstr_off = e_shoff + e_shstrndx * e_shentsize
        (shstr_offset,) = struct.unpack_from(endian + "I", data, shstr_off + 16)
        (shstr_size,) = struct.unpack_from(endian + "I", data, shstr_off + 20)
        shstrtab = data[shstr_offset : shstr_offset + shstr_size]

        symtab_info = None
        exec_shndx = set()
        data_shndx = set()

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

            if sh_type == 2:  # SHT_SYMTAB
                symtab_info = (sh_offset, sh_size, sh_link, sh_entsize or 16)
            if sh_flags & 0x4:  # SHF_EXECINSTR
                exec_shndx.add(i)
            elif sh_flags & 0x2:  # SHF_ALLOC: data, rodata, bss
                data_shndx.add(i)

        if not symtab_info:
            return [], []

        strtab_off = e_shoff + symtab_info[2] * e_shentsize
        (str_offset,) = struct.unpack_from(endian + "I", data, strtab_off + 16)
        (str_size,) = struct.unpack_from(endian + "I", data, strtab_off + 20)
        strtab = data[str_offset : str_offset + str_size]

        sym_off, sym_size, _, entsize = symtab_info
        count = sym_size // entsize

        raw_funcs: List[Tuple[str, int, int]] = []
        data_syms: List[Tuple[str, int, int]] = []
        text_end: Optional[int] = None
        text_start: Optional[int] = None

        for i in range(count):
            off = sym_off + i * entsize
            (
                st_name,
                st_val,
                st_sz,
                st_info,
                _,
                st_shndx,
            ) = struct.unpack_from(endian + "IIIBBH", data, off)
            st_type = st_info & 0xF

            # Overlays (and some boot/global files) keep data in their executable section.
            if (st_shndx in data_shndx or st_shndx in exec_shndx) and st_type in (0, 1):  # NOTYPE, OBJECT
                name_end = strtab.find(b"\0", st_name)
                name = strtab[st_name:name_end].decode("ascii", "replace")
                if name and not name.startswith((".", "$")) and not name.endswith(("_START", "_END", "_SIZE")):
                    data_syms.append((name, st_val, st_sz))

            # Only inspect symbols defined in this ELF's executable section(s)
            if st_shndx in exec_shndx:
                name_end = strtab.find(b"\0", st_name)
                name = strtab[st_name:name_end].decode("ascii", "replace")

                if name == f"{seg}_TEXT_END":
                    text_end = st_val
                elif name in (f"{seg}_TEXT_START", "entry_TEXT_START"):
                    if text_start is None or st_val < text_start:
                        text_start = st_val

                # Filter function symbols
                if st_type == 2:  # STT_FUNC
                    # Exclude local labels, jump tables, data symbols
                    if (
                        name.startswith(".L")
                        or name.startswith("jtbl_")
                        or name.startswith("D_")
                    ):
                        continue
                    raw_funcs.append((name, st_val, st_sz))

        raw_funcs.sort(key=lambda x: x[1])
        data_syms.sort(key=lambda x: x[1])

        # Derive function extents: runs up to next function start or text end
        final_funcs: List[Tuple[str, int, int]] = []
        n_funcs = len(raw_funcs)
        for i in range(n_funcs):
            name, val, sz = raw_funcs[i]
            next_start = (
                raw_funcs[i + 1][1] if i + 1 < n_funcs else (text_end or (val + sz))
            )
            extent = next_start - val
            final_size = sz if sz > 0 else extent
            final_funcs.append((name, val, final_size))

        return final_funcs, data_syms

    def _load_all(self) -> None:
        """Load symbols for all segments."""
        build_dir = self.repo_root / "build"
        seg_files: List[Tuple[str, str]] = [
            ("boot", "dk64.us.elf"),
            ("global", "global.elf"),
        ] + [(ovl, f"{ovl}.elf") for ovl in OVERLAYS]

        for seg, elf_name in seg_files:
            elf_path = build_dir / elf_name
            if not elf_path.is_file():
                continue
            funcs, data_syms = self._parse_elf(elf_path, seg)
            self._segments[seg] = funcs
            self._data[seg] = data_syms
            for name, addr, sz in funcs:
                if name not in self._name_index:
                    self._name_index[name] = (addr, seg)

    def function_at(
        self, addr: Union[int, str], segment: Optional[str] = None
    ) -> Optional[Tuple[str, int, int, str]]:
        """Look up function containing addr.

        addr: Virtual address (int or hex string).
        segment: Optional segment name. Overlays share 0x80024000.. and return None
                 unless disambiguated by specifying segment.

        Returns (name, start, size, segment) or None.
        """
        if isinstance(addr, str):
            addr = int(addr, 0)

        if segment is None:
            # Overlays collide at 0x80024000; require explicit segment
            if OVERLAY_VRAM_START <= addr < GLOBAL_VRAM_START:
                return None
            if addr < OVERLAY_VRAM_START:
                target_seg = "boot"
            elif addr >= GLOBAL_VRAM_START:
                target_seg = "global"
            else:
                return None
            return self._find_in_segment(target_seg, addr)
        else:
            if segment not in self._segments:
                return None
            return self._find_in_segment(segment, addr)

    def _find_in_segment(
        self, segment: str, addr: int
    ) -> Optional[Tuple[str, int, int, str]]:
        funcs = self._segments.get(segment, [])
        if not funcs:
            return None
        starts = [f[1] for f in funcs]
        idx = bisect.bisect_right(starts, addr) - 1
        if idx >= 0:
            name, start, size = funcs[idx]
            if start <= addr < start + size:
                return (name, start, size, segment)
        return None

    def data_at(
        self, addr: Union[int, str], segment: Optional[str] = None, max_offset: int = 0x400
    ) -> Optional[Tuple[str, int, int, str]]:
        """Data/rodata/bss symbol at or before addr: (name, start, offset, segment).

        A symbol with a size must contain addr; an unsized one (most splat D_ names)
        covers at most max_offset bytes and never past the next symbol. Overlay
        addresses need `segment`, as in function_at.
        """
        if isinstance(addr, str):
            addr = int(addr, 0)
        if segment is None:
            if OVERLAY_VRAM_START <= addr < GLOBAL_VRAM_START:
                return None
            segment = "boot" if addr < OVERLAY_VRAM_START else "global"
        syms = self._data.get(segment, [])
        idx = bisect.bisect_right([s[1] for s in syms], addr) - 1
        if idx < 0:
            return None
        name, start, size = syms[idx]
        off = addr - start
        limit = size if size > 0 else max_offset
        if off >= limit:
            return None
        return (name, start, off, segment)

    def lookup(
        self, name: str, segment: Optional[str] = None
    ) -> Optional[Tuple[int, str]]:
        """Look up function address and segment by name.

        Returns (addr, segment) or None.
        """
        if segment is not None:
            for n, addr, _ in self._segments.get(segment, []):
                if n == name:
                    return (addr, segment)
            return None
        return self._name_index.get(name)

    def functions(self, segment: str) -> List[Tuple[str, int, int]]:
        """Return list of (name, start, size) for segment, sorted by start."""
        if segment not in self._segments:
            raise ValueError(f"Unknown segment: {segment}")
        return list(self._segments[segment])

    def fallthrough_entries(self, segment: str) -> List[Tuple[str, int]]:
        """Functions the previous function runs straight into (no jr/j before it).

        These symbols are mid-function splits, not call targets. A breakpoint at one
        wedges ares's GDB stub under the recompiler: `continue` never reports another
        stop (func_806138B0, the tail of func_80613794). Breakpoint tools skip them.
        Uses build/<segment>.text.bin; boot (no such file) returns [].
        """
        text = self.repo_root / "build" / f"{segment}.text.bin"
        funcs = self._segments.get(segment, [])
        if not funcs or not text.is_file():
            return []
        data = text.read_bytes()
        base = funcs[0][1]

        def is_jump(word: int) -> bool:
            op = word >> 26
            return op == 2 or (op == 0 and (word & 0x3F) == 8)  # j, jr

        result = []
        for name, addr, _ in funcs[1:]:
            end = addr - base
            while end >= 4 and data[end - 4:end] == b"\0\0\0\0":
                end -= 4  # alignment padding (or a nop delay slot)
            if end < 8:
                continue
            last, before = struct.unpack(">II", data[end - 8:end])[::-1]
            if not (is_jump(last) or is_jump(before)):
                result.append((name, addr))
        return result


def load(repo_root: Optional[Union[str, Path]] = None) -> Symbols:
    """Load symbol database from repository root."""
    if repo_root is None:
        repo_root = _find_repo_root()
    return Symbols(repo_root)


def detect_overlay(
    read_mem: Callable[[int, int], bytes],
    repo_root: Optional[Union[str, Path]] = None,
    return_details: bool = False,
) -> Union[Optional[str], Tuple[Optional[str], Optional[str]]]:
    """Detect active overlay in emulator memory.

    Uses game runtime state (0x80744470 overlay end record and 0x807444EC mode byte)
    AND confirms with the byte fingerprint at 0x80024000.

    read_mem(addr, n) -> bytes: callable reading emulator memory.
    repo_root: Path to repository root.
    return_details: If True, returns (overlay_name, disagreement_str).

    Returns overlay name, or None if no overlay is loaded or on disagreement.
    """
    if repo_root is None:
        root_path = _find_repo_root()
    else:
        root_path = Path(repo_root).resolve()

    cache_key = (root_path, OVERLAY_WINDOW_SIZE)
    if cache_key not in _FINGERPRINT_CACHE:
        fingerprints: Dict[str, bytes] = {}
        build_dir = root_path / "build"
        for ovl in OVERLAYS:
            bin_path = build_dir / f"{ovl}.text.bin"
            if bin_path.is_file():
                with open(bin_path, "rb") as f:
                    chunk = f.read(OVERLAY_WINDOW_SIZE)
                if len(chunk) == OVERLAY_WINDOW_SIZE:
                    fingerprints[ovl] = chunk
        _FINGERPRINT_CACHE[cache_key] = fingerprints

    fingerprints = _FINGERPRINT_CACHE[cache_key]

    # 1. Read game state: loaded overlay end pointer (0x80744470) and mode (0x807444EC)
    vram_end = None
    mode = None
    try:
        rec_bytes = read_mem(ADDR_LOADED_OVERLAY_RECORD, 4)
        if rec_bytes and len(rec_bytes) == 4:
            vram_end = int.from_bytes(rec_bytes, "big")
    except Exception:
        pass

    try:
        mode_bytes = read_mem(ADDR_GAME_MODE, 1)
        if mode_bytes and len(mode_bytes) >= 1:
            mode = mode_bytes[0]
    except Exception:
        pass

    # Determine expected overlay from game state
    expected_overlay: Optional[str] = None
    if vram_end is not None:
        if vram_end == OVERLAY_VRAM_START:
            # Game state explicitly records NO overlay loaded
            expected_overlay = None
        elif vram_end in OVERLAY_END_VRAM:
            expected_overlay = OVERLAY_END_VRAM[vram_end]
        else:
            # Unknown pointer in 0x80744470 (e.g. uninitialized before loadOverlay)
            expected_overlay = None

    # Check mode byte consistency
    if mode == 3 and expected_overlay != "arcade":
        diag = f"mode byte is 3 (arcade) but 0x80744470 is 0x{vram_end:08X} ({expected_overlay})"
        print(f"[detect_overlay] Disagreement: {diag}", file=sys.stderr)
        return (None, diag) if return_details else None
    elif mode == 4 and expected_overlay != "jetpac":
        diag = f"mode byte is 4 (jetpac) but 0x80744470 is 0x{vram_end:08X} ({expected_overlay})"
        print(f"[detect_overlay] Disagreement: {diag}", file=sys.stderr)
        return (None, diag) if return_details else None
    # 2. Check byte fingerprint at 0x80024000
    try:
        mem = read_mem(OVERLAY_VRAM_START, OVERLAY_WINDOW_SIZE)
    except Exception:
        return (None, None) if return_details else None
    byte_matched_ovl: Optional[str] = None
    if mem and len(mem) >= OVERLAY_WINDOW_SIZE:
        target = mem[:OVERLAY_WINDOW_SIZE]
        for ovl, ref in fingerprints.items():
            if target == ref:
                byte_matched_ovl = ovl
                break

    # 3. Confirm game state against byte fingerprint
    if expected_overlay is None:
        if byte_matched_ovl is not None:
            # Memory contains bytes from an overlay, but game state says no overlay loaded
            diag = (
                f"game state records no overlay loaded (0x80744470=0x{vram_end or 0:08X}), "
                f"but 0x80024000 matches {byte_matched_ovl} fingerprint (stale overlay bytes)"
            )
            print(f"[detect_overlay] Disagreement: {diag}", file=sys.stderr)
            return (None, diag) if return_details else None
        return (None, None) if return_details else None

    if byte_matched_ovl == expected_overlay:
        return (expected_overlay, None) if return_details else expected_overlay

    diag = (
        f"game state indicates {expected_overlay} (0x80744470=0x{vram_end:08X}), "
        f"but 0x80024000 matches {byte_matched_ovl or 'unknown code'}"
    )
    print(f"[detect_overlay] Disagreement: {diag}", file=sys.stderr)
    return (None, diag) if return_details else None

def main() -> None:
    parser = argparse.ArgumentParser(
        description="Donkey Kong 64 function symbolizer and overlay detector."
    )
    parser.add_argument(
        "--repo-root",
        type=Path,
        default=None,
        help="Path to repository root (defaults to detected root)",
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    # addr ADDR [--segment S]
    parser_addr = subparsers.add_parser("addr", help="Resolve address to function")
    parser_addr.add_argument("addr", help="Address (hex e.g. 0x805FF378 or dec)")
    parser_addr.add_argument(
        "--segment",
        "-s",
        choices=SEGMENTS,
        default=None,
        help="Segment name (required for overlay addresses)",
    )

    # name NAME
    parser_name = subparsers.add_parser("name", help="Look up function address by name")
    parser_name.add_argument("name", help="Function name")

    # list SEGMENT
    parser_list = subparsers.add_parser("list", help="List all functions in a segment")
    parser_list.add_argument("segment", choices=SEGMENTS, help="Segment name")

    # stats
    subparsers.add_parser("stats", help="Report function counts per segment")

    args = parser.parse_args()

    try:
        symbols = load(args.repo_root)
    except Exception as e:
        sys.exit(f"Error loading symbols: {e}")

    try:
        _run_command(args, symbols)
    except BrokenPipeError:
        # Python flushes standard streams on exit; redirect to /dev/null to avoid noisy exception
        devnull = os.open(os.devnull, os.O_WRONLY)
        os.dup2(devnull, sys.stdout.fileno())
        sys.exit(0)


def _run_command(args: argparse.Namespace, symbols: Symbols) -> None:
    if args.command == "addr":
        addr = int(args.addr, 0)
        res = symbols.function_at(addr, segment=args.segment)
        if res is None:
            print("None")
        else:
            name, _, _, seg = res
            print(f"{name} in {seg}")

    elif args.command == "name":
        res = symbols.lookup(args.name)
        if res is None:
            print("None")
        else:
            addr, seg = res
            print(f"0x{addr:08X} in {seg}")

    elif args.command == "list":
        funcs = symbols.functions(args.segment)
        for name, start, size in funcs:
            print(f"0x{start:08x} {size} {name}")

    elif args.command == "stats":
        total = 0
        print(f"{'Segment':<15} {'Functions':>10}")
        print("-" * 26)
        for seg in SEGMENTS:
            count = len(symbols.functions(seg))
            total += count
            print(f"{seg:<15} {count:>10}")
        print("-" * 26)
        print(f"{'Total':<15} {total:>10}")


if __name__ == "__main__":
    main()
