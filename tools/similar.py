#!/usr/bin/env python3
"""Find matched C functions that look like a given function.

Usage: tools/dk python3 tools/similar.py [-s SEGMENT] [-n N] [--min SCORE] FUNC [FUNC ...]

Lists matched C functions whose opcode sequence resembles FUNC's. Score = 1 - Levenshtein
distance / longer length; registers, immediates and relocations are ignored, trailing nops
dropped. Compares against every matched C function of every segment in the current build/
(run `tools/dk make` first).
"""

import argparse
import math
import re
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

import Levenshtein

import progress


@dataclass
class Func:
    seg: str
    name: str
    addr: int
    seq: str
    matched: bool
    c_file: Path | None


SEG_ORDER = {name: i for i, (name, _, _) in enumerate(progress.SEGMENTS)}

# opcode key -> one character, so a function becomes a string for Levenshtein
_ALPHABET: dict = {}


def opcode_key(w: int):
    """Hashable opcode identity of one instruction word (no registers or immediates)."""
    if w == 0:
        return "nop"
    op = w >> 26
    if op == 0:
        return ("special", w & 0x3F)
    if op == 1:
        return ("regimm", (w >> 16) & 0x1F)
    if 0x10 <= op <= 0x12:
        fmt = (w >> 21) & 0x1F
        if fmt >= 0x10:
            return ("cop", op, fmt, w & 0x3F)
        if fmt == 8:  # BC: tf/nd bits select bc1f/bc1t/bc1fl/bc1tl
            return ("cop", op, fmt, (w >> 16) & 3)
        return ("cop", op, fmt)
    return ("op", op)


def encode(words) -> str:
    keys = [opcode_key(w) for w in words]
    while keys and keys[-1] == "nop":
        keys.pop()
    return "".join(_ALPHABET.setdefault(k, chr(0x100 + len(_ALPHABET))) for k in keys)


def load_functions(repo_root: Path) -> list[Func]:
    funcs = []
    for seg, elf_name, map_name in progress.SEGMENTS:
        elf = repo_root / "build" / elf_name
        map_path = repo_root / "build" / map_name
        for p in (elf, map_path):
            if not p.is_file():
                print(f"similar: build/{p.name} missing: run tools/dk make", file=sys.stderr)
                sys.exit(2)
        data = elf.read_bytes()
        _, sections = progress.read_elf_sections(data)
        for f in progress.iter_segment_functions(elf, map_path, repo_root):
            sec = sections[f["shndx"]]
            if sec["type"] == 8:  # SHT_NOBITS
                continue
            words = struct.unpack_from(f">{f['size'] // 4}I", data, sec["offset"] + f["value"] - sec["addr"])
            funcs.append(Func(seg, f["name"], f["value"], encode(words), f["c_matched"], f["c_file"]))
    return funcs


def closest(target: Func, candidates: list[Func], n: int, min_score: float) -> list[tuple[float, Func]]:
    """Best n matched candidates scoring >= min_score, highest first."""
    la = len(target.seq)
    if la == 0:
        return []
    pool = sorted(
        (c for c in candidates if c.matched and c.seq and (c.seg, c.addr) != (target.seg, target.addr)),
        key=lambda c: (abs(len(c.seq) - la), SEG_ORDER[c.seg], c.addr),
    )
    best: list[tuple[float, Func]] = []
    for c in pool:
        lb = len(c.seq)
        longer = max(la, lb)
        floor = best[-1][0] if len(best) == n else min_score
        # The length difference alone bounds the score: skip without computing the distance
        if min(la, lb) / longer < floor - 1e-9:
            continue
        # ceil: (1 - 0.8) * 5 is 0.999..., and int() would drop a valid 0.80 match
        cut = math.ceil((1 - floor) * longer)
        d = Levenshtein.distance(target.seq, c.seq, score_cutoff=cut)
        if d > cut:
            continue
        score = 1 - d / longer
        if score < min_score - 1e-9:
            continue
        best.append((score, c))
        best.sort(key=lambda t: (-t[0], abs(len(t[1].seq) - la), SEG_ORDER[t[1].seg], t[1].addr))
        del best[n:]
    return best


_defs_cache: dict = {}


def def_location(c_file: Path, name: str, repo_root: Path) -> str:
    """`src/...c:LINE` of name's definition, or just the file when it is not found."""
    rel = c_file.relative_to(repo_root)
    if c_file not in _defs_cache:
        _defs_cache[c_file] = c_file.read_text(encoding="utf-8", errors="replace").splitlines()
    pat = re.compile(rf"^[A-Za-z_].*\b{re.escape(name)}\s*\(")
    for i, line in enumerate(_defs_cache[c_file], 1):
        if pat.match(line) and not line.rstrip().endswith(";"):
            return f"{rel}:{i}"
    return str(rel)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n", 2)[2].strip())
    ap.add_argument("-s", "--segment", default="boot", choices=[s[0] for s in progress.SEGMENTS])
    ap.add_argument("-n", type=int, default=3, help="matches listed per function (default 3)")
    ap.add_argument(
        "--min", dest="min_score", type=float, default=0.50,
        help="lowest score listed (default 0.50; random same-length pairs score <= 0.44 at p99)",
    )
    ap.add_argument("--pairs", action="store_true",
                    help="pair the given FUNCs with each other (greedy, highest score first)")
    ap.add_argument("funcs", nargs="+", metavar="FUNC")
    args = ap.parse_args()
    if args.n < 1:
        ap.error("-n must be >= 1")
    if not 0 <= args.min_score <= 1:
        ap.error("--min must be between 0 and 1")

    repo_root = Path(__file__).resolve().parent.parent
    funcs = load_functions(repo_root)

    rc = 0
    if args.pairs:
        picked = []
        for name in args.funcs:
            t = min((f for f in funcs if f.seg == args.segment and f.name == name), key=lambda f: f.addr, default=None)
            if t is None:
                print(f"similar: {name} not found in segment {args.segment}", file=sys.stderr)
                rc = 1
                continue
            picked.append(t)
        scored = []
        for i, a in enumerate(picked):
            for b in picked[i + 1:]:
                if a.seq and b.seq:
                    s = 1 - Levenshtein.distance(a.seq, b.seq) / max(len(a.seq), len(b.seq))
                    scored.append((-s, a.name, b.name, a, b))
        scored.sort(key=lambda t: t[:3])
        used = set()
        for neg, _, _, a, b in scored:
            if a.name in used or b.name in used or -neg < args.min_score - 1e-9:
                continue
            used |= {a.name, b.name}
            print(f"pair  {-neg:.2f}  {a.name} ({len(a.seq)} insns)  {b.name} ({len(b.seq)} insns)")
        for t in picked:
            if t.name not in used:
                print(f"single  {t.name} ({len(t.seq)} insns)")
        sys.exit(rc)
    for name in args.funcs:
        targets = sorted((f for f in funcs if f.seg == args.segment and f.name == name), key=lambda f: f.addr)
        if not targets:
            print(f"similar: {name} not found in segment {args.segment}", file=sys.stderr)
            rc = 1
            continue
        for t in targets:
            status = "matched" if t.matched else ("unmatched" if t.c_file else "asm")
            head = f"{t.name} ({t.seg}, {status}, {len(t.seq)} insns)"
            hits = closest(t, funcs, args.n, args.min_score)
            if not hits:
                print(f"{head}: no matched function scores >= {args.min_score:.2f}")
                continue
            print(f"{head}: closest matched functions")
            for score, c in hits:
                print(f"  {score:.2f}  {c.name}  {c.seg}  {len(c.seq)} insns  {def_location(c.c_file, c.name, repo_root)}")
    sys.exit(rc)


if __name__ == "__main__":
    main()
