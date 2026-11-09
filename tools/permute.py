#!/usr/bin/env python3
"""Permuter tooling for Donkey Kong 64 matching decompilation.

METHODOLOGY AND SAFETY POLICY:
Permuter mutations are NOT semantics-preserving (upstream randomizer.py has
perm_reorder_stmts "Move a statement to another random place", perm_randomize_*_type,
perm_remove_ast deleting if statements without else, *_zero passes), and its scorer
compares disassembly only (stack offsets only with --stack-diffs; it does not check
relocations or data). A result is a search hint: rewrite the idea into readable C
that keeps the asm's behaviour, then the normal gates apply (fdiff/objdiff OK or
TEXT OK, then full ROM `build/dk64.us.z64: OK`). Never paste permuter output into
src unreviewed.

Subcommands:
  setup  Build permuter input directory (.scratch/permuter/<seg>_<FUNC>/, or --out DIR)
         and record its source, scores and file digests in setup.json; refuses a
         directory set up for another function or source file unless --force
  run    Run permuter with --stack-diffs and optional wall-clock limit; refuses a
         directory whose base.c/target.o/compile.sh changed since its setup, or
         whose setup baseline is already 0
  best   List best outputs and print diff against base.c
"""

import argparse
import difflib
import glob
import hashlib
import json
import os
import re
import shutil
import signal
import struct
import subprocess
import sys
from pathlib import Path
from typing import List, Optional, Tuple

ROOT = Path(__file__).resolve().parent.parent

# ---------------------------------------------------------------------------
# Container re-exec when running on host without /opt/decomp-permuter
# (tools/dk honours DK64_IMAGE)
# ---------------------------------------------------------------------------
if __name__ == "__main__" and not os.path.exists("/opt/decomp-permuter"):
    sys.exit(subprocess.call([str(ROOT / "tools" / "dk"), "python3", "tools/permute.py"] + sys.argv[1:]))


# ---------------------------------------------------------------------------
# Helper functions
# ---------------------------------------------------------------------------
def locate_asm(seg: str, func: str) -> Optional[Path]:
    """Find asm file for func in segment."""
    patterns = []
    if seg == "boot":
        patterns.extend([
            f"asm/nonmatchings/*/{func}.s",
            f"asm/boot/nonmatchings/*/{func}.s",
        ])
    else:
        patterns.append(f"asm/{seg}/nonmatchings/*/{func}.s")
    patterns.append(f"asm/**/{func}.s")

    for pat in patterns:
        hits = list(ROOT.glob(pat))
        if hits:
            return hits[0]
    return None


def deduce_src(asm_path: Path, seg: str, func: str) -> Path:
    """Deduce src C file from asm path or pragma lookup."""
    try:
        rel = asm_path.relative_to(ROOT / "asm")
    except ValueError:
        rel = asm_path

    parts = rel.parts
    candidate = None
    if len(parts) >= 3 and parts[1] == "nonmatchings":
        seg_dir = parts[0]
        subpath = Path(*parts[2:-1])
        candidate = ROOT / "src" / seg_dir / f"{subpath}.c"
    elif len(parts) >= 2 and parts[0] == "nonmatchings":
        subpath = Path(*parts[1:-1])
        c1 = ROOT / "src" / "boot" / f"{subpath}.c"
        c2 = ROOT / "src" / f"{subpath}.c"
        candidate = c1 if c1.exists() else c2

    if candidate and candidate.exists():
        return candidate

    # Search src/ for GLOBAL_ASM referencing func.s
    for c_file in (ROOT / "src").glob("**/*.c"):
        try:
            content = c_file.read_text(encoding="utf-8", errors="ignore")
            if f"{func}.s" in content:
                return c_file
        except Exception:
            pass

    if candidate:
        return candidate
    sys.exit(f"error: could not determine src C file for '{func}'")


# MIPS REL relocation types IDO objects use in .text (ELF numbering).
_MIPS_RELOC_NAMES = {
    2: "R_MIPS_32",
    4: "R_MIPS_26",
    5: "R_MIPS_HI16",
    6: "R_MIPS_LO16",
    7: "R_MIPS_GPREL16",
    8: "R_MIPS_LITERAL",
    9: "R_MIPS_GOT16",
    10: "R_MIPS_PC16",
    11: "R_MIPS_CALL16",
}


def function_asm_from_object(obj: bytes, func: str) -> str:
    """Return GNU as source reproducing only `func` from a big-endian ELF32 MIPS object.

    The permuter scores every instruction of target.o's .text against the
    candidate, whose .text holds just the one function, so a whole-TU object is
    not a usable target. The function's words are emitted verbatim at offset 0
    (REL addends live in the words) with its relocations as `.reloc` directives;
    R_MIPS_26 section-relative jumps are rebased so that jumps inside the
    function stay relative to it and calls into other functions of the file name
    the callee, as the candidate's prototype-only calls do.
    """
    if obj[:4] != b"\x7fELF" or obj[4] != 1 or obj[5] != 2:
        raise ValueError("not a big-endian ELF32 object")
    e_shoff, = struct.unpack_from(">I", obj, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from(">HHH", obj, 0x2E)
    sections = [
        struct.unpack_from(">10I", obj, e_shoff + i * e_shentsize) for i in range(e_shnum)
    ]

    def cstr(off: int) -> str:
        return obj[off:obj.index(b"\0", off)].decode("ascii")

    shstr_off = sections[e_shstrndx][4]
    sec_names = [cstr(shstr_off + s[0]) for s in sections]

    symtab_idx = next((i for i, s in enumerate(sections) if s[1] == 2), None)
    if symtab_idx is None:
        raise ValueError("object has no symbol table")
    _, _, _, _, sym_off, sym_size, sym_link, _, _, _ = sections[symtab_idx]
    str_off = sections[sym_link][4]
    symbols = []  # (name, value, size, type, shndx)
    for off in range(sym_off, sym_off + sym_size, 16):
        st_name, st_value, st_size, st_info, _, st_shndx = struct.unpack_from(">IIIBBH", obj, off)
        sym_type = st_info & 0xF
        name = sec_names[st_shndx] if sym_type == 3 and st_shndx < e_shnum else cstr(str_off + st_name)
        symbols.append((name, st_value, st_size, sym_type, st_shndx))

    hits = [s for s in symbols if s[0] == func and s[3] == 2]
    if len(hits) != 1:
        raise ValueError(f"expected one FUNC symbol '{func}', found {len(hits)}")
    _, start, size, _, shndx = hits[0]
    if size == 0:
        raise ValueError(f"symbol '{func}' has no size")
    text_off = sections[shndx][4]
    code = obj[text_off + start:text_off + start + size]
    words = list(struct.unpack(f">{size // 4}I", code))
    # Functions of this section by offset, to name the callee of a section-relative call.
    funcs_at = {s[1]: s[0] for s in symbols if s[3] == 2 and s[4] == shndx}

    relocs = []
    for s in sections:
        if s[7] != shndx or s[1] not in (4, 9):
            continue
        if s[1] == 4:
            raise ValueError("RELA relocations are not supported")
        for off in range(s[4], s[4] + s[5], 8):
            r_offset, r_info = struct.unpack_from(">II", obj, off)
            if not start <= r_offset < start + size:
                continue
            rtype = r_info & 0xFF
            if rtype not in _MIPS_RELOC_NAMES:
                raise ValueError(f"unsupported relocation type {rtype} at 0x{r_offset:X}")
            sym_name, _, _, sym_type, sym_shndx = symbols[r_info >> 8]
            idx = (r_offset - start) // 4
            if rtype == 4 and sym_type == 3 and sym_shndx == shndx:
                target = (words[idx] & 0x3FFFFFF) << 2
                if start <= target < start + size:
                    words[idx] = (words[idx] & ~0x3FFFFFF) | ((target - start) >> 2)
                elif target in funcs_at:
                    sym_name = funcs_at[target]
                    words[idx] &= ~0x3FFFFFF
            relocs.append((r_offset - start, _MIPS_RELOC_NAMES[rtype], sym_name))

    lines = [
        ".set noreorder",
        ".set noat",
        '.section .text, "ax"',
        f".globl {func}",
        f".type {func}, @function",
        f"{func}:",
    ]
    lines += [f".word 0x{w:08X}" for w in words]
    lines.append(f".size {func}, .-{func}")
    lines += [f".reloc {func}+0x{off:X}, {rname}, {sym}" for off, rname, sym in sorted(relocs)]
    return "\n".join(lines) + "\n"



def get_compile_flags(src_file: Path) -> tuple[str, str]:
    """Determine the IDO compiler and CFLAGS make uses for this src file."""
    rel_src = src_file.relative_to(ROOT)
    rel_obj = Path("build") / rel_src.with_suffix(".o")

    cmd = ["make", "-n", "-W", str(rel_src), str(rel_obj)]
    res = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)

    cc = "/opt/ido5.3/cc"
    cflags = ""
    for line in res.stdout.splitlines():
        m_cc = re.search(r"/opt/ido[0-9.]+/cc", line)
        if m_cc or "asm-processor" in line:
            if m_cc:
                cc = m_cc.group(0)
            if "--" in line:
                # asm-processor format: ... /opt/idoX/cc -- <as flags> -- <cflags> -o <obj> <src>
                parts = line.split("--")
                cflags = parts[-1].strip()
                cflags = cflags.split("-o")[0].strip()
            else:
                # direct cc format: /opt/idoX/cc <cflags> -o <obj> <src>
                m = re.search(r"/opt/ido[0-9.]+/cc\s+(.*?)\s+-o", line)
                if m:
                    cflags = m.group(1).strip()

    if not cflags:
        # Fallback default flags
        cflags = (
            "-c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -signed -woff 649,654,838,807 "
            "-I include -D_FINALROM -DF3DEX_GBI_2 -DTARGET_N64 -D_MIPS_SZLONG=32 -O2 -mips2"
        )
    return cc, cflags


# Text between a definition's `)` and its `{`: whitespace, comments and K&R
# parameter declarations (`ActorHitView *arg1;`, `volatile u8 arg4; // FAKE: ...`).
_C_COMMENT = r"(?://[^\n]*|/\*[\s\S]*?\*/)"
_C_GAP = rf"(?:\s|{_C_COMMENT})*"
_KR_DECLS = rf"{_C_GAP}(?:[a-zA-Z0-9_* \t,()\[\]]+;{_C_GAP})*"

_C_TYPE_WORDS = {
    "void", "char", "short", "int", "long", "float", "double", "signed", "unsigned",
    "const", "volatile", "struct", "union", "enum",
}


def _is_knr_definition(params: str, decls: str) -> bool:
    """True if a definition with this parameter text and pre-`{` text is K&R style.

    K&R: parameter declarations between `)` and `{`, or an identifier list (every
    ANSI definition parameter has a type and a name, so a lone word other than a
    type keyword is an identifier).
    """
    if re.sub(_C_COMMENT, "", decls).strip():
        return True
    items = [p.strip() for p in params.split(",")]
    if items == [""]:
        return False
    return all(re.fullmatch(r"[A-Za-z_]\w*", p) and p not in _C_TYPE_WORDS for p in items)


def _fn_decl_re(fn_name: str) -> "re.Pattern[str]":
    """Column-0 (file-scope) declarations of fn_name; group 1 is the parameter text."""
    return re.compile(
        rf"^(?!return\b)[A-Za-z_][\w \t*]*\b{re.escape(fn_name)}\s*\(([^;{{}}]*)\)\s*;[ \t]*\n?",
        re.MULTILINE,
    )


def _resolve_knr_declarations(pieces: list) -> str:
    """Join strip_other_fns pieces, replacing each stripped K&R definition.

    Pieces are text, ("target", text) for the kept function, or ("knr", name, decl) for
    a stripped K&R definition whose `T f();` is decl. Only the declarations in force at
    the target affect its code, and IDO uses a function's prototype once one has been
    seen before the call, before or after a K&R definition; otherwise a K&R definition
    gives the non-prototype, default-promoted type `T f();`. A non-definition `T f();`
    and a prototype with narrow parameters cannot both be declared (cfe error), so:
    - K&R definition after the target: dropped.
    - prototype before the target: definition dropped, and every `T f();` of f too.
    - otherwise: definition becomes `T f();`, and prototypes after the target go.
    """
    merged: list = []
    buf: List[str] = []
    for p in pieces:
        if isinstance(p, str):
            buf.append(p)
        else:
            merged += ["".join(buf), p]
            buf = []
    pieces = merged + ["".join(buf)]
    target = next((k for k, p in enumerate(pieces) if isinstance(p, tuple) and p[0] == "target"), len(pieces))
    text_before = "".join(p for p in pieces[:target] if isinstance(p, str))
    drop_nonproto, drop_proto_after = set(), set()
    out = list(pieces)
    for k, p in enumerate(pieces):
        if not (isinstance(p, tuple) and p[0] == "knr"):
            continue
        _, name, decl = p
        if k > target:
            out[k] = ""
        elif any(d.group(1).strip() for d in _fn_decl_re(name).finditer(text_before)):
            out[k] = ""
            drop_nonproto.add(name)
        else:
            out[k] = decl
            drop_proto_after.add(name)

    def drop_decls(text: str, names: set, prototypes: bool) -> str:
        for name in names:
            text = _fn_decl_re(name).sub(lambda d: "" if bool(d.group(1).strip()) == prototypes else d.group(0), text)
        return text

    joined = []
    for k, p in enumerate(out):
        if isinstance(p, tuple):
            joined.append(p[1])
            continue
        p = drop_decls(p, drop_nonproto, prototypes=False)
        if k > target:
            p = drop_decls(p, drop_proto_after, prototypes=True)
        joined.append(p)
    return "".join(joined)


def strip_other_fns(source: str, keep_fn: str) -> str:
    """Turn all function bodies except keep_fn into forward declarations.

    K&R definitions (identifier lists are only valid in a definition) become `T f();`
    or nothing, never an ANSI prototype: see _resolve_knr_declarations.
    """
    fn_regex = re.compile(
        r"(?:([a-zA-Z0-9_*][a-zA-Z0-9_* \t]*?)\b)?(\w+)\s*\(([^;{}]*?)\)" + _KR_DECLS + r"\{"
    )
    control_flow = {"if", "while", "for", "switch", "catch"}

    result = []
    n = len(source)
    pos = 0
    brace_depth = 0

    while pos < n:
        at_col0 = (pos == 0 or source[pos - 1] == "\n")

        if brace_depth == 0 and at_col0 and source[pos] not in " \t\r\n#":
            m = fn_regex.match(source, pos)
            if m:
                fn_name = m.group(2)
                if fn_name not in control_flow:
                    start_idx = m.end() - 1
                    level = 1
                    i = start_idx + 1
                    while i < n and level > 0:
                        c = source[i]
                        if c == "/" and i + 1 < n:
                            c2 = source[i + 1]
                            if c2 == "/":
                                i += 2
                                while i < n and source[i] != "\n":
                                    i += 1
                                continue
                            elif c2 == "*":
                                i += 2
                                while i + 1 < n and not (source[i] == "*" and source[i + 1] == "/"):
                                    i += 1
                                i += 2 if i + 1 < n else 1
                                continue
                        elif c == '"':
                            i += 1
                            while i < n and source[i] != '"':
                                if source[i] == "\\" and i + 1 < n:
                                    i += 1
                                i += 1
                            i += 1
                            continue
                        elif c == "'":
                            i += 1
                            while i < n and source[i] != "'":
                                if source[i] == "\\" and i + 1 < n:
                                    i += 1
                                i += 1
                            i += 1
                            continue
                        elif c == "{":
                            level += 1
                        elif c == "}":
                            level -= 1
                        i += 1

                    if fn_name == keep_fn:
                        result.append(("target", source[pos:i]))
                    elif fn_name.startswith("PERM"):
                        result.append(source[pos:i])
                    elif _is_knr_definition(m.group(3), source[m.end(3) + 1 : m.end() - 1]):
                        result.append(("knr", fn_name, source[pos : m.start(3)].rstrip() + ");\n"))
                    else:
                        proto = source[pos : m.end(3) + 1].rstrip() + ";"
                        result.append(proto + "\n")
                    pos = i
                    continue

        c = source[pos]
        if c == "/" and pos + 1 < n:
            c2 = source[pos + 1]
            if c2 == "/":
                start_c = pos
                pos += 2
                while pos < n and source[pos] != "\n":
                    pos += 1
                result.append(source[start_c:pos])
                continue
            elif c2 == "*":
                start_c = pos
                pos += 2
                while pos + 1 < n and not (source[pos] == "*" and source[pos + 1] == "/"):
                    pos += 1
                pos += 2 if pos + 1 < n else 1
                result.append(source[start_c:pos])
                continue
        elif c == '"':
            start_s = pos
            pos += 1
            while pos < n and source[pos] != '"':
                if source[pos] == "\\" and pos + 1 < n:
                    pos += 1
                pos += 1
            pos += 1
            result.append(source[start_s:pos])
            continue
        elif c == "'":
            start_ch = pos
            pos += 1
            while pos < n and source[pos] != "'":
                if source[pos] == "\\" and pos + 1 < n:
                    pos += 1
                pos += 1
            pos += 1
            result.append(source[start_ch:pos])
            continue
        elif c == "{":
            brace_depth += 1
        elif c == "}":
            brace_depth = max(0, brace_depth - 1)

        result.append(c)
        pos += 1

    return _resolve_knr_declarations(result)


def deduplicate_externs(source: str, func_name: str) -> str:
    """Deduplicate extern variable declarations.

    Keeps, per symbol, the last declaration before func_name's definition (the one the
    kept function compiles against), or the first one when all follow it.
    """
    lines = source.splitlines()
    func_pat = re.compile(rf"\b{re.escape(func_name)}\s*\([^;]*$|\b{re.escape(func_name)}\s*\([^{{}}]*?\)" + _KR_DECLS + r"\{", re.DOTALL)
    func_line = next((i for i, l in enumerate(lines) if func_pat.search(l) and not l.lstrip().startswith("extern")), len(lines))
    decl_re = re.compile(r"extern\s+[a-zA-Z0-9_* \t]+\b([A-Za-z0-9_]+)\s*(?:\[[^\]]*\])*\s*;")
    keep = {}
    for i, l in enumerate(lines):
        m = decl_re.search(l)
        if m:
            sym = m.group(1)
            if sym not in keep or i < func_line:
                keep[sym] = i

    new_lines = []
    for i, l in enumerate(lines):
        m = decl_re.search(l)
        if m and keep[m.group(1)] != i:
            continue
        new_lines.append(l)
    return "\n".join(new_lines)


_CONTROL_HEADER = re.compile(r"(?<![\w.>])(?:if|while|for|switch)\s*\(\)$")
_LEADING_KEYWORD = re.compile(r"(else|do)\b\s*(.+)")
_LEADING_LABEL = re.compile(r"((?:case\b[^:]*|default|[A-Za-z_]\w*)\s*:)(?!:)\s*(.+)")


def _mask_line(line: str) -> Optional[str]:
    """Drop string/char literal and parenthesised contents; None if parens are unbalanced."""
    out = []
    depth = 0
    i, n = 0, len(line)
    while i < n:
        c = line[i]
        if c in "\"'":
            j = i + 1
            while j < n and line[j] != c:
                j += 2 if line[j] == "\\" else 1
            if depth == 0:
                out.append(c + c)
            i = j + 1
            continue
        if c == "(":
            depth += 1
            if depth == 1:
                out.append(c)
        elif c == ")":
            depth -= 1
            if depth < 0:
                return None
            if depth == 0:
                out.append(c)
        elif depth == 0:
            out.append(c)
        i += 1
    return "".join(out) if depth == 0 else None


def _line_pieces(masked: str) -> List[str]:
    """Split a masked source line into the pieces pycparser prints on separate lines."""
    pieces: List[str] = []
    cur = ""

    def flush() -> None:
        nonlocal cur
        rest = cur.strip()
        cur = ""
        while rest:
            m = _LEADING_KEYWORD.fullmatch(rest) or _LEADING_LABEL.fullmatch(rest)
            if not m:
                pieces.append(rest)
                return
            pieces.append(m.group(1))
            rest = m.group(2).strip()

    for c in masked:
        if c in "{}":
            flush()
            pieces.append(c)
        elif c == ";":
            cur += c
            flush()
        else:
            cur += c
            if c == ")" and _CONTROL_HEADER.search(cur):
                flush()
    flush()
    return pieces


def _needs_sameline(line: str) -> bool:
    """True if pycparser would print two code pieces of this line on separate lines.

    IDO schedules by source line (as1), so the permuter's reprint of e.g.
    `i = 0; do {` or `if (x) return;` compiles differently from the original.
    Pieces that carry no code of their own (`{`, `}`, `else`, an empty `;`) do not count.
    """
    masked = _mask_line(line.strip())
    if masked is None or not masked or masked[-1] not in ";{}:":
        return False
    if re.search(r"=\s*\{", masked):  # aggregate initializer, not a block
        return False
    code = [p for p in _line_pieces(masked) if p not in ("{", "}", "else", ";")]
    return len(code) > 1


def wrap_multi_statement_lines(source: str, func_name: str) -> str:
    """Wrap lines of func_name whose pieces pycparser would split in PERM_FORCE_SAMELINE.

    A wrapped line may open or close a block: the evaluated sameline pragmas
    then sit at statement boundaries inside and outside it, which pycparser
    accepts. A pragma never goes where it would end up as the body of an
    `if`/`else`/`do` or split an `if` from its `else` or a do-body from its
    `while`, so such lines stay unwrapped.
    """
    pat = re.compile(rf"(^|\n)([^\n;{{}}]*?\b{re.escape(func_name)}\s*\([^{{}}]*?\)" + _KR_DECLS + r"\{)", re.DOTALL)
    m = pat.search(source)
    if not m:
        return source
    start_idx = m.start(2)
    brace_idx = m.end(2) - 1
    level = 1
    i = brace_idx + 1
    n = len(source)
    while i < n and level > 0:
        if source[i] == "{":
            level += 1
        elif source[i] == "}":
            level -= 1
        i += 1
    func_text = source[start_idx:i]

    lines = func_text.splitlines()
    body_first = func_text[:brace_idx - start_idx].count("\n") + 1
    body = lines[body_first:-1]
    code_idx = [k for k, line in enumerate(body) if line.strip() and not line.strip().startswith("#")]

    def continues(prev_end: str, s: str) -> bool:
        return bool(re.match(r"else\b", s)) or (prev_end == "}" and bool(re.match(r"while\b", s)))

    wrap = set()
    for pos, k in enumerate(code_idx):
        s = body[k].strip()
        prev_end = body[code_idx[pos - 1]].strip()[-1] if pos else "{"
        nxt = body[code_idx[pos + 1]].strip() if pos + 1 < len(code_idx) else "}"
        if (
            "PERM_" not in s
            and prev_end in ";{}:"
            and not continues(prev_end, s)
            and (s[-1] == "{" or not continues(s[-1], nxt))
            and _needs_sameline(s)
        ):
            wrap.add(k)

    new_lines = lines[:body_first]
    for k, line in enumerate(body):
        if k in wrap:
            indent = line[:len(line) - len(line.lstrip())]
            new_lines.append(f"{indent}PERM_FORCE_SAMELINE({line.strip()})")
        else:
            new_lines.append(line)
    new_lines += lines[-1:] if len(lines) > body_first else []

    new_func_text = "\n".join(new_lines)
    return source[:start_idx] + new_func_text + source[i:]


def preprocess_whole_source(source_text: str, extra_flags: List[str]) -> str:
    """Preprocess a complete assembled source file with cpp, expanding macros."""
    cpp_bin = shutil.which("mips-linux-gnu-cpp") or shutil.which("cpp") or "cpp"
    cmd = [
        cpp_bin,
        "-E",
        "-P",
        "-D_LANGUAGE_C",
        "-D_FINALROM",
        "-DF3DEX_GBI_2",
        "-DTARGET_N64",
        "-D_MIPS_SZLONG=32",
        "-D_Static_assert(x, y)=",
        "-D__attribute__(x)=",
        "-D__extension__=",
        "-I",
        "include",
    ]
    for flag in extra_flags:
        if flag.startswith("-I") or flag.startswith("-D"):
            if flag not in cmd:
                cmd.append(flag)

    res = subprocess.run(cmd, cwd=ROOT, input=source_text, capture_output=True, text=True)
    if res.returncode != 0:
        sys.exit(f"error preprocessing source ({cpp_bin}):\n{res.stderr}")

    defines = (
        "#ifndef NULL\n#define NULL 0\n#endif\n"
        "#ifndef TRUE\n#define TRUE 1\n#endif\n"
        "#ifndef FALSE\n#define FALSE 0\n#endif\n"
    )
    return res.stdout + "\n" + defines


# ---------------------------------------------------------------------------
# Setup record: what setup built a directory from, checked by setup and run
# ---------------------------------------------------------------------------
SETUP_RECORD = "setup.json"
_RECORDED_FILES = ("base.c", "target.o", "compile.sh")


def _rel_to_root(path: Path) -> str:
    path = path.resolve()
    return str(path.relative_to(ROOT)) if path.is_relative_to(ROOT) else str(path)


def _file_digests(out_dir: Path) -> dict:
    return {
        name: hashlib.sha256((out_dir / name).read_bytes()).hexdigest()
        for name in _RECORDED_FILES
        if (out_dir / name).exists()
    }


def read_setup_record(out_dir: Path) -> Optional[dict]:
    path = out_dir / SETUP_RECORD
    if not path.exists():
        return None
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return None


def write_setup_record(out_dir: Path, record: dict) -> None:
    data = dict(record, digests=_file_digests(out_dir))
    (out_dir / SETUP_RECORD).write_text(json.dumps(data, indent=2) + "\n", encoding="utf-8")


def setup_conflict(previous: Optional[dict], record: dict) -> Optional[str]:
    """Why setting up `record` must not silently replace the previous setup, or None.

    Re-setup from the same source (an updated copy) is the normal workflow; another
    function or another source file means the directory belongs to other work.
    """
    if previous is None:
        return None
    for key in ("func", "source"):
        if previous.get(key) != record[key]:
            return f"was set up for {previous.get('func')} from {previous.get('source')}, not {record['func']} from {record['source']}"
    return None


def run_record_problem(out_dir: Path, record: Optional[dict]) -> Optional[str]:
    """Why run must not start on out_dir, or None.

    The permuter scores its own compile of base.c against target.o; if another setup
    replaced them, it starts from a different base (e.g. an already matching source,
    base score 0, and a "zero" found at once).
    """
    if record is None:
        return None
    digests = _file_digests(out_dir)
    changed = [name for name, digest in record.get("digests", {}).items() if digests.get(name) != digest]
    origin = f"{record.get('func')} from {record.get('source')}"
    if changed:
        return f"{', '.join(changed)} changed since setup of {origin} (another setup into this directory?); re-run setup"
    if record.get("baseline_score") == 0:
        return f"setup of {origin} already scores 0 (permuter baseline); nothing to search"
    return None



# ---------------------------------------------------------------------------
# Subcommand: setup
# ---------------------------------------------------------------------------
def cmd_setup(args: argparse.Namespace) -> None:
    seg = args.seg
    func = args.func

    # 1. Locate asm and src files
    asm_path = locate_asm(seg, func)
    if args.src:
        src_path = Path(args.src)
        if not src_path.is_absolute():
            src_path = ROOT / src_path
    else:
        if asm_path is None:
            sys.exit(f"error: assembly file for '{func}' in segment '{seg}' not found (pass --src src/...)")
        src_path = deduce_src(asm_path, seg, func)

    if not src_path.exists():
        sys.exit(f"error: src file '{src_path}' not found")

    src_text = src_path.read_text(encoding="utf-8", errors="ignore")

    # Source of base.c (picked before anything is written, for the overwrite check)
    if args.from_file:
        from_path = Path(args.from_file)
        if not from_path.is_absolute():
            from_path = ROOT / from_path
        if not from_path.exists():
            sys.exit(f"error: input file '{from_path}' not found")
        from_text = from_path.read_text(encoding="utf-8", errors="ignore")
    else:
        # Check if func is parked inside #ifdef NON_MATCHING in src_text
        pat_parked = rf"#if(?:def|\s+defined\s*\()\s*NON_MATCHING[\s\S]*?\b{re.escape(func)}\s*\([^{{}}]*?\)\s*[^{{}}]*?\{{"
        if re.search(pat_parked, src_text):
            from_path = src_path
            from_text = src_text
        else:
            # A function already written as C in the given --src (e.g. a private copy) is
            # taken from there; otherwise fall back to the stored draft.
            src_has_c = re.search(rf"^[^\n;#]*\b{re.escape(func)}\s*\([^{{}}]*?\)\s*[^{{}}]*?\{{", src_text, re.M) and not re.search(
                rf"#pragma\s+GLOBAL_ASM\(\"[^\"]*/{re.escape(func)}\.s\"\)", src_text
            )
            if src_has_c:
                from_path = src_path
                from_text = src_text
            else:
                from_path = ROOT / "drafts" / seg / f"{func}.c"
                if not from_path.exists():
                    sys.exit(f"error: input file '{from_path}' not found (provide a draft or --from FILE.c)")
                from_text = from_path.read_text(encoding="utf-8", errors="ignore")

    if args.out:
        out_dir = Path(args.out)
        if not out_dir.is_absolute():
            out_dir = ROOT / out_dir
    else:
        out_dir = ROOT / ".scratch" / "permuter" / f"{seg}_{func}"
    record = {"seg": seg, "func": func, "src": _rel_to_root(src_path), "source": _rel_to_root(from_path)}
    conflict = setup_conflict(read_setup_record(out_dir), record)
    if conflict and not args.force:
        sys.exit(
            f"error: {out_dir} {conflict}; another agent may be using it. Pass --out DIR "
            "for a separate directory, or --force to replace it"
        )
    out_dir.mkdir(parents=True, exist_ok=True)

    # 2. Build target.o
    target_o = out_dir / "target.o"
    if asm_path is None:
        # Matched function: rebuild just this function from expected/ (the whole
        # TU object would be scored instruction by instruction against it).
        rel_src = src_path.relative_to(ROOT) if src_path.is_absolute() else src_path
        expected_o = ROOT / "expected" / "build" / rel_src.with_suffix(".o")
        if not expected_o.exists():
            sys.exit(f"error: expected object '{expected_o}' not found (run make expected)")
        try:
            target_asm = function_asm_from_object(expected_o.read_bytes(), func)
        except ValueError as e:
            sys.exit(f"error: cannot extract '{func}' from '{expected_o}': {e}")
        asm_path = out_dir / "target.s"
        asm_path.write_text(target_asm, encoding="utf-8")

    # Assemble with project prelude and VR4300 flags
    as_bin = shutil.which("mips-linux-gnu-as") or "mips-linux-gnu-as"
    as_cmd = [
        as_bin,
        "-EB",
        "-march=vr4300",
        "-mabi=32",
        "-mgp32",
        "-mfp32",
        "-I",
        "include",
        "include/asm_prelude.inc",
        str(asm_path),
        "-o",
        str(target_o),
    ]
    res_as = subprocess.run(as_cmd, cwd=ROOT, capture_output=True, text=True)
    if res_as.returncode != 0:
        sys.exit(f"error assembling target.o:\n{res_as.stderr}")

    # 3. Build compile.sh
    cc, cflags = get_compile_flags(src_file=src_path)
    compile_sh = out_dir / "compile.sh"
    sh_content = f"""#!/bin/bash
{cc} {cflags} "$1" -o "$3"
"""
    compile_sh.write_text(sh_content, encoding="utf-8")
    compile_sh.chmod(0o755)

    # 4. Build settings.toml
    settings_toml = out_dir / "settings.toml"
    settings_content = f"""func_name = "{func}"
compiler_type = "ido"
"""
    settings_toml.write_text(settings_content, encoding="utf-8")

    # Determine if NON_MATCHING should be enabled
    use_non_matching = bool(args.non_matching)
    if not use_non_matching:
        pat_nm = rf"#if(?:def|\s+defined\s*\()\s*NON_MATCHING[\s\S]*?\b{re.escape(func)}\b[\s\S]*?#endif"
        if re.search(pat_nm, from_text) or re.search(pat_nm, src_text):
            use_non_matching = True

    # Check whether from_path is a whole file (e.g. private copy of src/ with GLOBAL_ASM / other functions)
    is_whole_file = False
    if from_path == src_path or args.from_file:
        if re.search(r"#pragma\s+GLOBAL_ASM", from_text):
            is_whole_file = True
        else:
            top_fns = re.findall(r"^(?:[a-zA-Z0-9_*]+\s+)+(\w+)\s*\([^{}]*?\)\s*[^{}]*?\{", from_text, re.MULTILINE)
            top_fns = [f for f in top_fns if f not in ("if", "while", "for", "switch", "catch")]
            if len(top_fns) > 1:
                is_whole_file = True

    if is_whole_file:
        combined = from_text
    else:
        # Stored draft or single function snippet
        draft_lines = []
        for line in from_text.splitlines():
            s = line.strip()
            if s.startswith("//"):
                continue
            if s.startswith("#include"):
                inc = s.split()[1] if len(s.split()) > 1 else ""
                if inc in src_text:
                    continue
            draft_lines.append(line)
        draft_text = "\n".join(draft_lines).strip()

        # Replace target GLOBAL_ASM with draft_text, or append if pragma absent
        target_pragma = re.compile(rf"#pragma\s+GLOBAL_ASM\(\"[^\"]*{re.escape(func)}\.s\"\)")
        if target_pragma.search(src_text):
            combined = target_pragma.sub(lambda _: draft_text, src_text, count=1)
        else:
            combined = src_text + "\n\n" + draft_text

    combined = deduplicate_externs(combined, func)
    combined = strip_other_fns(combined, func)
    combined = re.sub(r"#pragma\s+GLOBAL_ASM\([^\)]*\)", "", combined)

    extra_flags = [tok for tok in cflags.split() if tok.startswith("-I") or tok.startswith("-D")]
    if use_non_matching and "-DNON_MATCHING" not in extra_flags:
        extra_flags.append("-DNON_MATCHING")

    base_c_content = preprocess_whole_source(combined, extra_flags)
    base_c_content = wrap_multi_statement_lines(base_c_content, func)
    base_c = out_dir / "base.c"
    base_c.write_text(base_c_content, encoding="utf-8")

    # 6. Verify compilation and compute starting score
    base_o = out_dir / "base.o"
    if "PERM_" in base_c_content:
        sys.path.insert(0, "/opt/decomp-permuter")
        from src.perm.eval import perm_evaluate_one
        from src.perm.parse import perm_parse
        perms = perm_parse(base_c_content)
        test_c_content, _ = perm_evaluate_one(perms)
        test_c_file = out_dir / "test_base.c"
        test_c_file.write_text(test_c_content, encoding="utf-8")
        comp_file = test_c_file
    else:
        comp_file = base_c

    comp_res = subprocess.run(
        [str(compile_sh), str(comp_file), "-o", str(base_o)],
        cwd=out_dir,
        capture_output=True,
        text=True,
    )
    if "PERM_" in base_c_content and comp_file.exists():
        comp_file.unlink()

    if comp_res.returncode != 0:
        print(f"Compilation error in {base_c}:", file=sys.stderr)
        print(comp_res.stderr or comp_res.stdout, file=sys.stderr)
        sys.exit(1)

    # Score base.o vs target.o and compute permuter baseline score
    direct_score = cand_score = None
    sys.path.insert(0, "/opt/decomp-permuter")
    try:
        from src.scorer import Scorer
        from src.preprocess import preprocess
        from src.perm.parse import perm_parse
        from src.perm.eval import perm_evaluate_one
        from src.candidate import Candidate
        from src.helpers import get_default_randomization_weights

        scorer = Scorer(
            str(target_o),
            stack_differences=True,
            algorithm="difflib",
            debug_mode=False,
            ign_branch_targets=False,
            objdump_command=None,
        )
        direct_score, _ = scorer.score(str(base_o))

        # Evaluate through decomp-permuter pipeline as run will
        c_source = preprocess(str(base_c))
        weights = get_default_randomization_weights("ido")
        perms = perm_parse(c_source)
        base_source, eval_state = perm_evaluate_one(perms)
        cand = Candidate.from_source(base_source, eval_state, func, weights, rng_seed=0)
        cand_c = out_dir / "cand_base.c"
        cand_o = out_dir / "cand_base.o"
        cand_c.write_text(cand.get_source(), encoding="utf-8")
        cand_comp = subprocess.run(
            [str(compile_sh), str(cand_c), "-o", str(cand_o)],
            cwd=out_dir,
            capture_output=True,
            text=True,
        )
        if cand_c.exists():
            cand_c.unlink()
        cand_score = None
        if cand_comp.returncode == 0:
            cand_score, _ = scorer.score(str(cand_o))
            if cand_o.exists():
                cand_o.unlink()

        print(f"Permuter setup complete: {out_dir}")
        print(f"Starting score (direct compile): {direct_score}")
        if cand_score is not None:
            print(f"Starting score (permuter baseline): {cand_score}")
            if cand_score != direct_score:
                print(
                    f"WARNING: Direct compile score ({direct_score}) and permuter baseline score ({cand_score}) differ!\n"
                    f"IDO 5.3 is sensitive to same-line statements and formatting.\n"
                    f"The permuter will search relative to the baseline score ({cand_score})."
                )
    except Exception as e:
        print(f"Permuter setup complete: {out_dir}")
        print(f"(Scorer check warning: {e})")

    # What run checks the directory against (another setup into it changes base.c/target.o)
    record.update(non_matching=use_non_matching, direct_score=direct_score, baseline_score=cand_score)
    write_setup_record(out_dir, record)

# ---------------------------------------------------------------------------
# Subcommand: run
# ---------------------------------------------------------------------------
def cmd_run(args: argparse.Namespace, extra_args: List[str]) -> None:
    target_dir = Path(args.dir)
    if not target_dir.is_absolute():
        target_dir = ROOT / target_dir

    if not target_dir.exists():
        sys.exit(f"error: directory '{target_dir}' does not exist")

    for req in ["base.c", "target.o", "compile.sh"]:
        if not (target_dir / req).exists():
            sys.exit(f"error: missing '{req}' in {target_dir}")

    record = read_setup_record(target_dir)
    if record is None:
        print(f"warning: no {SETUP_RECORD} in {target_dir}: cannot check that it still holds what setup scored")
    else:
        problem = run_record_problem(target_dir, record)
        if problem:
            sys.exit(f"error: {target_dir}: {problem}")
        print(
            f"Setup: {record.get('func')} from {record.get('source')}, "
            f"baseline {record.get('baseline_score')} (direct {record.get('direct_score')})",
            flush=True,
        )

    threads = args.threads
    if threads is None or threads <= 0:
        cpu_cnt = os.cpu_count() or 2
        threads = max(1, cpu_cnt // 2)

    permuter_py = Path("/opt/decomp-permuter/permuter.py")
    if not permuter_py.exists():
        sys.exit("error: /opt/decomp-permuter/permuter.py not found")

    cmd = [
        sys.executable,
        str(permuter_py),
        str(target_dir),
        "--stack-diffs",
        "--stop-on-zero",
        "-j",
        str(threads),
    ] + extra_args

    print(f"Running permuter on {target_dir} ({threads} threads, --stack-diffs, stop-on-zero)...", flush=True)
    if args.seconds is not None and args.seconds > 0:
        proc = subprocess.Popen(cmd)
        try:
            ret = proc.wait(timeout=args.seconds)
            sys.exit(ret)
        except subprocess.TimeoutExpired:
            print(f"\nWall-clock limit reached ({args.seconds}s). Stopping permuter.")
            proc.send_signal(signal.SIGINT)
            try:
                proc.wait(timeout=5)
            except subprocess.TimeoutExpired:
                proc.kill()
            sys.exit(0)
    else:
        ret = subprocess.call(cmd)
        sys.exit(ret)


# ---------------------------------------------------------------------------
# Subcommand: best
# ---------------------------------------------------------------------------
def cmd_best(args: argparse.Namespace) -> None:
    target_dir = Path(args.dir)
    if not target_dir.is_absolute():
        target_dir = ROOT / target_dir

    if not target_dir.exists():
        sys.exit(f"error: directory '{target_dir}' does not exist")

    output_dirs = []
    for d in target_dir.iterdir():
        if d.is_dir() and d.name.startswith("output-"):
            score = None
            score_file = d / "score.txt"
            if score_file.exists():
                try:
                    score = int(score_file.read_text().strip())
                except ValueError:
                    pass
            if score is None:
                parts = d.name.split("-")
                if len(parts) >= 2:
                    try:
                        score = int(parts[1])
                    except ValueError:
                        score = 999999
            output_dirs.append((score, d))

    if not output_dirs:
        print(f"No output directories found in {target_dir}")
        return

    output_dirs.sort(key=lambda x: (x[0] if x[0] is not None else 999999, x[1].name))

    print(f"Outputs in {target_dir} ({len(output_dirs)} total, sorted by score):")
    for score, d in output_dirs:
        rel = d.relative_to(ROOT) if d.is_relative_to(ROOT) else d
        print(f"  score: {score:<6d} path: {rel}")

    best_score, best_d = output_dirs[0]
    rel_best = best_d.relative_to(ROOT) if best_d.is_relative_to(ROOT) else best_d
    print(f"\n=== Best result: score {best_score} in {rel_best} ===")

    diff_file = best_d / "diff.txt"
    if diff_file.exists() and diff_file.stat().st_size > 0:
        print(diff_file.read_text(encoding="utf-8", errors="ignore"))
    else:
        # Fallback to computing unified diff between base.c and source.c
        base_c = target_dir / "base.c"
        source_c = best_d / "source.c"
        if base_c.exists() and source_c.exists():
            base_lines = base_c.read_text(encoding="utf-8", errors="ignore").splitlines()
            source_lines = source_c.read_text(encoding="utf-8", errors="ignore").splitlines()
            udiff = list(difflib.unified_diff(base_lines, source_lines, fromfile="base.c", tofile="source.c", lineterm=""))
            print("\n".join(udiff))


# ---------------------------------------------------------------------------
# CLI Entrypoint
# ---------------------------------------------------------------------------
def main() -> None:
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    sub = parser.add_subparsers(dest="subcommand", required=True)

    # setup
    p_setup = sub.add_parser("setup", help="Set up a permuter input directory")
    p_setup.add_argument("seg", help="Segment name (boot, global, boss, ...)")
    p_setup.add_argument("func", help="Function name (e.g. func_80663BE8)")
    p_setup.add_argument("--from", dest="from_file", help="Input C file (default: drafts/<seg>/<func>.c)")
    p_setup.add_argument("--src", help="Path to original C file in src/ (default: auto-detected)")
    p_setup.add_argument("--non-matching", action="store_true", help="Enable NON_MATCHING define for parked function definitions")
    p_setup.add_argument("--out", help="Output directory (default: .scratch/permuter/<seg>_<FUNC>)")
    p_setup.add_argument("--force", action="store_true", help="Replace a directory set up for another function or source file")

    # run
    p_run = sub.add_parser("run", help="Run permuter on an input directory")
    p_run.add_argument("dir", help="Permuter input directory")
    p_run.add_argument("-j", "--threads", type=int, default=None, help="Number of threads (default: half CPUs)")
    p_run.add_argument("--seconds", type=int, default=None, help="Wall-clock limit in seconds")

    # best
    p_best = sub.add_parser("best", help="List best outputs and show diff")
    p_best.add_argument("dir", help="Permuter input directory")

    # Parse known args so trailing permuter args can be forwarded to run
    args, extra = parser.parse_known_args()

    if args.subcommand == "setup":
        if extra:
            sys.exit(f"error: unrecognized arguments: {' '.join(extra)}")
        cmd_setup(args)
    elif args.subcommand == "run":
        cmd_run(args, extra)
    elif args.subcommand == "best":
        if extra:
            sys.exit(f"error: unrecognized arguments: {' '.join(extra)}")
        cmd_best(args)


if __name__ == "__main__":
    main()
