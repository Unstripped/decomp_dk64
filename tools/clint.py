# /// script
# requires-python = ">=3.12"
# dependencies = ["libclang==18.1.1"]
# ///
"""Read-only clang (libclang) analysis of the game's C: lint, struct layout, metrics, LSP database.

clang never builds anything here: IDO stays the only compiler (tools/fdiff.sh, tools/merge_gate.sh).
Every tool parses with CLANG_ARGS (the Makefile's -D/-I flags, IDO's -signed as -fsigned-char)
and without -DNON_MATCHING, so parked blocks are invisible as in the matching build.

  uv run tools/clint.py scan [src.c...]                 parse errors (werrors: of the warnings-mode parse
                                                          `uninit` uses, first one shown) and function counts
  uv run tools/clint.py uninit <copy.c> [--base <src.c>] UNINIT <file>:<line> <function> <variable>;
                                                          --base: exit 1 on a (function, variable) pair
                                                          the base lacks (NEW UNINIT ...); exit 3 (UNKNOWN
                                                          <file> ...) when either warnings-mode parse has
                                                          errors: clang then skips the analysis
  uv run tools/clint.py layout --base <REV> <include/h.h>...
                                                          record sizes and field offsets vs REV:
                                                          LAYOUT OK (0) or LAYOUT CHANGED <Type> ... (1)
  uv run tools/clint.py compdb                          write compile_commands.json (host clangd / lsp)
  uv run tools/clint.py metrics <src.c>... [--json]     per-function gotos, empty ifs, no-op arithmetic,
                                                          punned casts, m2c names, unk fields, D_ refs,
                                                          plus `untagged` steering shapes without // FAKE
Exit 2: libclang unavailable. Exit 3: uninit UNKNOWN.
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys
import tempfile

import clang.cindex as ci
from clang.cindex import CursorKind, TypeKind

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CLANG_ARGS = ["-std=gnu89", "-target", "mips-linux-gnu", "-fsigned-char", "-nostdinc", "-Iinclude", "-Iinclude/PR",
              "-Iinclude/libultra", "-Iinclude/compiler/ido", "-D_LANGUAGE_C", "-D_FINALROM", "-DF3DEX_GBI_2",
              "-DTARGET_N64", "-D_MIPS_SZLONG=32", "-DBUILD_VERSION=VERSION_J", "-Wno-everything"]
UNINIT_FLAGS = ["-Wuninitialized", "-Wsometimes-uninitialized", "-Wconditional-uninitialized"]
FALLBACK_LIB = "/Library/Developer/CommandLineTools/usr/lib/libclang.dylib"
M2C_NAME = re.compile(r"^(sp[0-9A-F]+|var_\w+|temp_\w+|phi_\w+|arg[0-9]+)$")
UNK_FIELD = re.compile(r"^unk[0-9A-F]+$")
D_REF = re.compile(r"^D_[0-9A-F]{8}$")
NOOP_OPS = {"^", "|", "+", "&", "*"}

_index = None


def index():
    """The shared clang Index; falls back to the Command Line Tools libclang, exits 2 without one."""
    global _index
    if _index is None:
        try:
            _index = ci.Index.create()
        except Exception:
            try:
                ci.Config.set_library_file(FALLBACK_LIB)
                _index = ci.Index.create()
            except Exception:
                print("clint: libclang unavailable", file=sys.stderr)
                sys.exit(2)
    return _index


def clang_args(inc="include", warnings=False):
    """CLANG_ARGS with the include root replaced by INC; WARNINGS enables the uninit set after
    -Wno-everything, and nothing else: a default-error warning such as -Wint-conversion would make
    clang skip the uninitialised-read analysis of every later function."""
    out = []
    for a in CLANG_ARGS:
        if a.startswith("-Iinclude"):
            a = "-I" + inc + a[len("-Iinclude"):]
        out.append(a)
        if a == "-Wno-everything" and warnings:
            out += UNINIT_FLAGS
    return out


def parse(path, extra=(), args=None, unsaved=None):
    """TranslationUnit for PATH parsed with CLANG_ARGS from the repo root; `tu.diagnostics_errors`
    counts error/fatal diagnostics (the TU is returned anyway)."""
    path = os.path.abspath(os.path.join(ROOT, path))
    a = [f"-working-directory={ROOT}", *(args if args is not None else CLANG_ARGS), *extra]
    tu = index().parse(path, args=a, unsaved_files=unsaved,
                       options=ci.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
    tu.diagnostics_errors = sum(1 for d in tu.diagnostics if d.severity >= ci.Diagnostic.Error)
    return tu


def same_file(cursor, path):
    f = cursor.location.file
    return f is not None and os.path.realpath(os.path.join(ROOT, f.name)) == os.path.realpath(os.path.join(ROOT, path))


def knr(c):
    """True for a K&R / empty-parameter-list definition or a no-prototype declaration. clang 18 gives
    old-style definitions a FUNCTIONPROTO type, so definitions are judged by their tokens."""
    if c.type.kind == TypeKind.FUNCTIONNOPROTO:
        return True
    if not c.is_definition():
        return False
    toks = [t.spelling for t in c.get_tokens()]
    for i in range(len(toks) - 1):
        if toks[i] == c.spelling and toks[i + 1] == "(":
            depth = 0
            for j in range(i + 1, len(toks)):
                depth += {"(": 1, ")": -1}.get(toks[j], 0)
                if depth == 0:
                    return j + 1 < len(toks) and toks[j + 1] != "{"
    return False


def functions(tu, path):
    """(name, is_static, is_definition, has_prototype, start_line, end_line, cursor) for every
    top-level FUNCTION_DECL located in PATH (has_prototype is False for K&R definitions)."""
    for c in tu.cursor.get_children():
        if c.kind == CursorKind.FUNCTION_DECL and same_file(c, path):
            yield (c.spelling, c.storage_class == ci.StorageClass.STATIC, c.is_definition(),
                   not knr(c), c.extent.start.line, c.extent.end.line, c)


def definitions(path):
    """[(name, is_static, start_line, end_line)] of the function definitions of one file."""
    tu = parse(path)
    return [(n, st, s, e) for n, st, d, _, s, e, _ in functions(tu, path) if d]


def walk(c):
    for ch in c.get_children():
        yield ch
        yield from walk(ch)


def strip(c):
    """Expression cursor without parentheses and implicit/unexposed wrappers."""
    while c.kind in (CursorKind.PAREN_EXPR, CursorKind.UNEXPOSED_EXPR):
        ch = list(c.get_children())
        if len(ch) != 1:
            break
        c = ch[0]
    return c


def is_zero(c):
    c = strip(c)
    if c.kind != CursorKind.INTEGER_LITERAL:
        return False
    toks = [t.spelling for t in c.get_tokens()]
    if len(toks) != 1:
        return False
    try:
        return int(toks[0].rstrip("uUlL"), 0) == 0
    except ValueError:
        return False


def binop(c):
    """Operator token of a BINARY_OPERATOR / COMPOUND_ASSIGNMENT_OPERATOR cursor, or None."""
    ch = list(c.get_children())
    if len(ch) != 2:
        return None
    end = ch[0].extent.end.offset
    for t in c.get_tokens():
        if t.extent.start.offset >= end:
            return t.spelling
    return None


def unop(c):
    toks = list(c.get_tokens())
    return toks[0].spelling if toks else None


def punned(c):
    """A cast to a scalar pointer type of `&expr` whose type differs from the pointee: reading an
    object as another scalar (`*(s32 *)&f`, `*(u8 *)&s8var`). Void pointees and struct/union
    pointees (views and API type bridges, handled by the types phase) are excluded."""
    t = c.type.get_canonical()
    if t.kind != TypeKind.POINTER:
        return False
    ch = [x for x in c.get_children() if x.kind != CursorKind.TYPE_REF]
    if not ch:
        return False
    op = strip(ch[-1])
    if op.kind != CursorKind.UNARY_OPERATOR or unop(op) != "&":
        return False
    inner = list(op.get_children())
    if not inner:
        return False
    pointee = t.get_pointee().get_canonical()
    src = inner[0].type.get_canonical()
    if pointee.kind in (TypeKind.VOID, TypeKind.RECORD):
        return False
    return pointee.spelling.replace("volatile ", "").replace("const ", "") != \
        src.spelling.replace("volatile ", "").replace("const ", "")


def function_metrics(fn, lines):
    """Metrics dict and untagged hits [(line, kind, code)] for one definition cursor."""
    m = dict(gotos=0, empty_ifs=0, noop_arith=0, punned=0, volatile=0, m2c_names=0, unk_fields=0, d_refs=0,
             func_name=fn.spelling.startswith("func_"))
    hits, names = [], set()

    def hit(line, kind):
        code = lines[line - 1] if 0 < line <= len(lines) else ""
        if kind == "goto" or "// FAKE" not in code:
            hits.append((line, kind, code.strip()))

    for c in walk(fn):
        k = c.kind
        if k == CursorKind.GOTO_STMT:
            m["gotos"] += 1
            hit(c.location.line, "goto")
        elif k == CursorKind.IF_STMT:
            ch = list(c.get_children())
            if len(ch) == 2 and ch[1].kind == CursorKind.COMPOUND_STMT and not list(ch[1].get_children()):
                m["empty_ifs"] += 1
                hit(c.location.line, "dead-if")
        elif k == CursorKind.BINARY_OPERATOR:
            ch = list(c.get_children())
            if len(ch) == 2 and binop(c) in NOOP_OPS and (is_zero(ch[0]) or is_zero(ch[1])):
                m["noop_arith"] += 1
                hit(c.location.line, "noop-arith")
        elif k == CursorKind.CSTYLE_CAST_EXPR:
            if punned(c):
                m["punned"] += 1
                hit(c.location.line, "punned-cast")
        elif k in (CursorKind.PARM_DECL, CursorKind.VAR_DECL):
            if M2C_NAME.match(c.spelling):
                names.add(c.spelling)
            if k == CursorKind.VAR_DECL and c.type.is_volatile_qualified():
                m["volatile"] += 1
                hit(c.location.line, "volatile")
        elif k == CursorKind.MEMBER_REF_EXPR:
            if UNK_FIELD.match(c.spelling):
                m["unk_fields"] += 1
        elif k == CursorKind.DECL_REF_EXPR:
            if D_REF.match(c.spelling):
                m["d_refs"] += 1
    # K&R parameters are PARM_DECL children of the definition too (walk covers them).
    m["m2c_names"] = len(names)
    return m, hits


def metrics(path):
    """{function name: dict(metrics..., line, end, static, untagged=[(line, kind, code)])} for one file."""
    tu = parse(path)
    lines = open(os.path.join(ROOT, path), encoding="utf-8", errors="replace").read().split("\n")
    out = {}
    for name, st, d, _, s, e, c in functions(tu, path):
        if not d:
            continue
        m, hits = function_metrics(c, lines)
        out[name] = dict(m, line=s, end=e, static=st, untagged=hits)
    return out


def src_files():
    return sorted(p for p in glob.glob("src/**/*.c", root_dir=ROOT, recursive=True) if "/libultra/" not in p)


def first_error(tu):
    """The first error/fatal diagnostic of TU, or None."""
    return next((d for d in tu.diagnostics if d.severity >= ci.Diagnostic.Error), None)


def cmd_scan(a):
    for p in a.files or src_files():
        tu = parse(p)
        wtu = parse(p, args=clang_args(warnings=True))
        n = sum(1 for f in functions(tu, p) if f[2])
        print(f"{p} errors={tu.diagnostics_errors} werrors={wtu.diagnostics_errors} functions={n}")
        if wtu.diagnostics_errors:
            print(f"  werror: {first_error(wtu)}")


VARNAME = re.compile(r"variable '(\w+)'")


def uninit(path, tu=None):
    """{(function, variable): line} of the uninitialized-read warnings of one file (TU: an existing
    parse of PATH with clang_args(warnings=True), to share one parse with other analyses)."""
    tu = tu if tu is not None else parse(path, args=clang_args(warnings=True))
    spans = [(s, e, n) for n, _, d, _, s, e, _ in functions(tu, path) if d]
    out = {}
    for d in tu.diagnostics:
        if d.severity != ci.Diagnostic.Warning or not d.location.file or not same_file(d, path):
            continue
        if "uninitialized" not in d.spelling:
            continue
        m = VARNAME.search(d.spelling)
        if not m:
            continue
        line = d.location.line
        fn = next((n for s, e, n in spans if s <= line <= e), "?")
        out.setdefault((fn, m.group(1)), line)
    return out


def analysed_uninit(path):
    """`uninit(PATH)`, or None after printing `UNKNOWN` when its warnings-mode parse has errors:
    clang skips the uninitialised-read analysis of every function after a TU's first error, so no
    warning there is unknown, not none."""
    tu = parse(path, args=clang_args(warnings=True))
    if tu.diagnostics_errors:
        print(f"UNKNOWN {path}: {tu.diagnostics_errors} error(s) in the warnings-mode parse, uninitialised "
              f"reads not analysed; first: {first_error(tu)}")
        return None
    return uninit(path, tu)


def cmd_uninit(a):
    cur = analysed_uninit(a.copy)
    for (fn, var), line in sorted((cur or {}).items(), key=lambda x: x[1]):
        print(f"UNINIT {a.copy}:{line} {fn} {var}")
    base = analysed_uninit(a.base) if a.base else {}
    if cur is None or base is None:
        sys.exit(3)
    if a.base:
        new = [(k, v) for k, v in cur.items() if k not in base]
        for (fn, var), line in sorted(new, key=lambda x: x[1]):
            print(f"NEW UNINIT {a.copy}:{line} {fn} {var}")
        sys.exit(1 if new else 0)


UNNAMED = re.compile(r"\((?:unnamed|anonymous) at [^)]*\)")


def type_sig(t):
    """Canonical spelling of T with unnamed records spelled out (`struct {name@bit offset:sig; ...}`,
    anonymous members named ''), so it compares across header versions: clang spells unnamed
    records by their source location."""
    t = t.get_canonical()
    if t.kind == TypeKind.POINTER:
        return type_sig(t.get_pointee()) + " *"
    if t.kind == TypeKind.CONSTANTARRAY:
        return f"{type_sig(t.element_type)}[{t.element_count}]"
    if t.kind == TypeKind.RECORD and UNNAMED.search(t.spelling):
        return t.spelling.split(" ")[0] + " {" + "; ".join(
            f"{field_name(f)}@{f.get_field_offsetof()}:{type_sig(f.type)}" for f in t.get_fields()) + "}"
    return t.spelling


def field_name(f):
    """F's name; '' for an anonymous member (clang spells it by its type's source location)."""
    return "" if UNNAMED.search(f.spelling) else f.spelling


def record_layout(t):
    """(size, [(field name, bit offset, bit size, `type_sig`)], align) of record type T, or None
    when T is not a complete record."""
    t = t.get_canonical()
    if t.kind != TypeKind.RECORD or t.get_size() < 0:
        return None
    return (t.get_size(), [(field_name(f), f.get_field_offsetof(),
                            f.get_bitfield_width() if f.is_bitfield() else max(f.type.get_size(), 0) * 8,
                            type_sig(f.type)) for f in t.get_fields()], t.get_align())


def records(args, rel):
    """{type name: `record_layout`} of every complete named record of a TU that includes common.h
    and REL (a path under the include roots of ARGS)."""
    path = "/clint-virtual/layout.c"  # virtual: no directory whose headers could shadow REL
    tu = parse(path, args=args, unsaved=[(path, f'#include "common.h"\n#include "{rel}"\n')])
    if tu.diagnostics_errors:
        print(f"clint: {rel}: {first_error(tu)}", file=sys.stderr)
    out = {}

    def add(name, t):
        lay = record_layout(t)
        if name and lay is not None:
            out[name] = lay

    for c in walk(tu.cursor):
        if c.kind in (CursorKind.STRUCT_DECL, CursorKind.UNION_DECL) and c.is_definition() and c.spelling \
                and not c.is_anonymous():
            add(c.spelling, c.type)
        elif c.kind == CursorKind.TYPEDEF_DECL:
            add(c.spelling, c.underlying_typedef_type)
    return out


ARRAY_SIG = re.compile(r"^(.*)\[(\d+)\]$")


def layout_diff(old, new, types=False, resized=None):
    """['<Type> <detail>'] for records whose size changed, whose surviving fields moved, or whose old
    field start is no longer the start of or inside a new field (renaming or splitting padding, or
    merging fields into an array over the same bytes, keeps the layout). TYPES (quality.py carry
    --header-carve) also reports a changed alignment, a surviving field whose `type_sig` changed and
    an anonymous member not kept with the same offset and signature; with a RESIZED list, a surviving
    array that only changed its (outer) length, e.g. padding shrunk for a carved field, is appended
    there as ('<Type>', '<field>', False) instead (its accesses compile the same; `sizeof` of it does
    not), and one shrunk to a scalar of its element type (`u8 pad36[2]` -> `u8 pad36; u8 unk37`)
    as ('<Type>', '<field>', True) (only code not accessing it compiles the same)."""
    out = []
    for name, (size, fields, align) in sorted(old.items()):
        if name not in new:
            out.append(f"{name} removed")
            continue
        nsize, nfields, nalign = new[name]
        if nsize != size:
            out.append(f"{name} size 0x{size:X} -> 0x{nsize:X}")
        by_name = {f: (o, s) for f, o, _, s in nfields if f}
        for f, o, _, s in fields:
            if f in by_name and by_name[f][0] != o:
                out.append(f"{name} {f} offset 0x{o // 8:X} -> 0x{by_name[f][0] // 8:X}")
            elif f not in by_name and not any(no <= o < no + max(nb, 1) for _, no, nb, _ in nfields):
                out.append(f"{name} {f or '<anonymous>'} at 0x{o // 8:X} gone")
            elif types and f in by_name and by_name[f][1] != s:
                ns = by_name[f][1]
                a, b = ARRAY_SIG.match(s), ARRAY_SIG.match(ns)
                if resized is not None and a and (b and a[1] == b[1] or a[1] == ns):
                    resized.append((name, f, a[1] == ns))
                else:
                    out.append(f"{name} {f} type {s} -> {ns}")
            elif types and not f and (f, o, s) not in {(nf, no, ns) for nf, no, _, ns in nfields}:
                out.append(f"{name} <anonymous> at 0x{o // 8:X} changed")
        if types and nalign != align:
            out.append(f"{name} align {align} -> {nalign}")
    return out


def cmd_layout(a):
    bad = False
    with tempfile.TemporaryDirectory() as tmp:
        arch = subprocess.run(["git", "archive", a.base, "include"], cwd=ROOT, capture_output=True, check=True).stdout
        subprocess.run(["tar", "-x", "-C", tmp], input=arch, check=True)
        for h in a.headers:
            h = os.path.relpath(os.path.abspath(h), ROOT)
            old_path = os.path.join(tmp, h)
            if not os.path.exists(old_path):
                print(f"LAYOUT NEW {h} (not in {a.base})")
                continue
            rel = os.path.relpath(h, "include")
            old = records(clang_args(os.path.join(tmp, "include")), rel)
            new = records(clang_args(), rel)
            for d in layout_diff(old, new):
                print(f"LAYOUT CHANGED {d}")
                bad = True
    if not bad:
        print("LAYOUT OK")
    sys.exit(1 if bad else 0)


def cmd_compdb(a):
    db = [{"directory": ROOT, "file": p, "arguments": ["clang", *CLANG_ARGS, "-c", p]} for p in src_files()]
    with open(os.path.join(ROOT, "compile_commands.json"), "w") as f:
        json.dump(db, f, indent=1)
        f.write("\n")
    print(f"compile_commands.json: {len(db)} entries")


def cmd_metrics(a):
    res = {p: metrics(p) for p in a.files}
    if a.json:
        json.dump(res, sys.stdout, indent=1)
        print()
        return
    keys = ("gotos", "empty_ifs", "noop_arith", "punned", "volatile", "m2c_names", "unk_fields", "d_refs")
    for p, fns in res.items():
        for name, m in fns.items():
            print(f"{p}:{m['line']} {name} " + " ".join(f"{k}={m[k]}" for k in keys)
                  + (" func_name" if m["func_name"] else ""))
            for line, kind, code in m["untagged"]:
                print(f"  UNTAGGED {p}:{line} {kind} {code}")


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(required=True)
    s = sub.add_parser("scan")
    s.add_argument("files", nargs="*")
    s.set_defaults(fn=cmd_scan)
    s = sub.add_parser("uninit")
    s.add_argument("copy")
    s.add_argument("--base")
    s.set_defaults(fn=cmd_uninit)
    s = sub.add_parser("layout")
    s.add_argument("--base", required=True)
    s.add_argument("headers", nargs="+")
    s.set_defaults(fn=cmd_layout)
    s = sub.add_parser("compdb")
    s.set_defaults(fn=cmd_compdb)
    s = sub.add_parser("metrics")
    s.add_argument("files", nargs="+")
    s.add_argument("--json", action="store_true")
    s.set_defaults(fn=cmd_metrics)
    a = p.parse_args()
    index()
    a.fn(a)


if __name__ == "__main__":
    main()
