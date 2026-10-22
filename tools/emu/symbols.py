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
        # global name -> (start_addr, segment)
        self._name_index: Dict[str, Tuple[int, str]] = {}
        self._load_all()

    def _parse_elf(
        self, elf_path: Path, seg: str
    ) -> Tuple[List[Tuple[str, int, int]], int, int]:
        """Parse ELF32 big-endian symtab and return functions and text bounds."""
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

        if not symtab_info:
            return [], 0, 0

        strtab_off = e_shoff + symtab_info[2] * e_shentsize
        (str_offset,) = struct.unpack_from(endian + "I", data, strtab_off + 16)
        (str_size,) = struct.unpack_from(endian + "I", data, strtab_off + 20)
        strtab = data[str_offset : str_offset + str_size]

        sym_off, sym_size, _, entsize = symtab_info
        count = sym_size // entsize

        raw_funcs: List[Tuple[str, int, int]] = []
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

        return final_funcs, text_start or 0, text_end or 0

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
            funcs, _, _ = self._parse_elf(elf_path, seg)
            self._segments[seg] = funcs
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


def load(repo_root: Optional[Union[str, Path]] = None) -> Symbols:
    """Load symbol database from repository root."""
    if repo_root is None:
        repo_root = _find_repo_root()
    return Symbols(repo_root)


def detect_overlay(
    read_mem: Callable[[int, int], bytes],
    repo_root: Optional[Union[str, Path]] = None,
) -> Optional[str]:
    """Detect active overlay in emulator memory at 0x80024000.

    read_mem(addr, n) -> bytes: callable reading emulator memory.
    repo_root: Path to repository root.

    Returns overlay name or None if memory does not match any overlay.
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
    try:
        mem = read_mem(OVERLAY_VRAM_START, OVERLAY_WINDOW_SIZE)
    except Exception:
        return None

    if not mem or len(mem) < OVERLAY_WINDOW_SIZE:
        return None

    # Check against known overlay headers
    target = mem[:OVERLAY_WINDOW_SIZE]
    for ovl, ref in fingerprints.items():
        if target == ref:
            return ovl

    return None


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
