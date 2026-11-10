# /// script
# requires-python = ">=3.12"
# dependencies = ["libclang==18.1.1"]
# ///
"""AST-backed renames: the namer rules as code.

  uv run tools/rename.py func <seg> <old> <new>      function: \\b<old>\\b tokens (GLOBAL_ASM paths included),
                                                       PROTO_SKIP_<old>, D_<VRAM8>, the symbol-file line,
                                                       drafts/<seg>/<old>.c, then tools/protos.py gen
  uv run tools/rename.py global <seg> <old> <new>    data symbol: the same without drafts/
  uv run tools/rename.py field <path> <Struct> <field> <new>
                                                     one struct's field by AST: every non-libultra src TU
                                                       when <path> is under include/, else that file only
  uv run tools/rename.py local <file.c> <FUNC> <old> <new>
                                                     a parameter or local of FUNC (works on private copies)
  uv run tools/rename.py fold <seg> <label> <parent-expr> [--per-ref] [--held SRC...]
                                                     a split label (D_80744474, D_8002F054) becomes an access
                                                       through its parent (gFramebuffers[1], jetpacPlayer.y):
                                                       every AST reference in the segment's src is replaced,
                                                       each touched file must pass `fdiff --reloc-ok` (else
                                                       it is left alone; --per-ref keeps the references
                                                       whose fold still matches), its now-unused extern is
                                                       dropped, and the symbol-file / undefined_syms line
                                                       goes once nothing (src, include, asm) names it.
                                                       Refuses when a reference sits in a checked-out file
                                                       (--held, default the last `# Round` of
                                                       .scratch/cleanup-brief.md) or inside a macro.
                                                       Exit 2 when some references stay.

func/global edit src/<seg>/ for an overlay, every non-libultra src/ file plus the top-level game headers
(include/*.h) for global and boot. AST renames also parse files with #ifdef NON_MATCHING a second time
with -DNON_MATCHING, so parked C is renamed too.
Every subcommand takes --dry-run (print `file:line:col old→new`, write nothing) and --root DIR (tests).
`field --dry-run` lists every reference even when some lie inside macro expansions: those print as
`MACRO <macro> file:line:col` after the others, and the command still exits 1 at the end.
Exit 1 with nothing written when <new> encodes an address/offset or is m2c-shaped, <new> already names a
symbol, macro or field in scope, a reference lies inside a macro expansion, or (func) <old> is declared
in include/PR, include/PRinternal or include/libultra (`header-prototyped: <header>`).
"""
import argparse
import concurrent.futures
import glob
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import clint  # noqa: E402
import ledger  # noqa: E402
from clint import CursorKind  # noqa: E402

ROOT = clint.ROOT
IDENT = re.compile(r"[A-Za-z_]\w*")
HEXRUN = re.compile(r"[0-9A-F]{3,}")
PREFIXED = re.compile(r"^(func|D|unk|sp|var|temp|arg)_?[0-9A-Fa-f]*[0-9]")
KEYWORDS = set("auto break case char const continue default do double else enum extern float for goto if int "
               "long register return short signed sizeof static struct switch typedef union unsigned void "
               "volatile while".split())
LIBULTRA_HEADERS = ("include/PR", "include/PRinternal", "include/libultra")


class Refuse(Exception):
    pass


def set_root(root):
    global ROOT
    ROOT = clint.ROOT = ledger.ROOT = os.path.abspath(root)
    ledger._syms.clear()
    ledger._maps.clear()


def rel(p):
    return os.path.relpath(os.path.join(ROOT, p), ROOT)


def read(p):
    with open(os.path.join(ROOT, p), encoding="latin-1", newline="") as f:
        return f.read()


def write(p, text):
    with open(os.path.join(ROOT, p), "w", encoding="latin-1", newline="") as f:
        f.write(text)


def check_name(new):
    if not IDENT.fullmatch(new) or new in KEYWORDS:
        raise Refuse(f"not an identifier: {new}")
    if HEXRUN.search(new) or PREFIXED.match(new) or clint.M2C_NAME.match(new) or clint.UNK_FIELD.match(new) \
            or clint.D_REF.match(new):
        raise Refuse(f"address-shaped name: {new}")


def word(name):
    return re.compile(rf"\b{re.escape(name)}\b")


def first_hit(rx, paths):
    """'file:line' of the first match of RX in PATHS, or None."""
    for p in paths:
        for i, line in enumerate(read(p).split("\n"), 1):
            if rx.search(line):
                return f"{p}:{i}"
    return None


def apply(edits, dry):
    """Print and (unless DRY) apply [(file, line, col, old, new)]; col 0 inserts NEW as a line before LINE.
    Every edit is checked against the text before anything is written."""
    edits = sorted(set(edits))
    for f, l, c, o, n in edits:
        print(f"{f}:{l}:{max(c, 1)} {o}→{n}")
    out = {}
    for f in sorted({e[0] for e in edits}):
        lines = read(f).split("\n")
        for _, l, c, o, n in sorted((e for e in edits if e[0] == f), key=lambda e: (e[1], e[2]), reverse=True):
            if c == 0:
                lines.insert(l - 1, n)
                continue
            s = lines[l - 1]
            if s[c - 1:c - 1 + len(o)] != o:
                raise Refuse(f"{f}:{l}:{c}: expected {o}")
            lines[l - 1] = s[:c - 1] + n + s[c - 1 + len(o):]
        out[f] = "\n".join(lines)
    if not dry:
        for f, text in out.items():
            write(f, text)
    return len(edits)


# ---- func / global: token renames ----

def scope_files(seg):
    if seg in ("boot", "global"):
        heads = sorted(p for p in glob.glob("include/*.h", root_dir=ROOT))
        return clint.src_files() + heads
    if not os.path.isdir(os.path.join(ROOT, "src", seg)):
        raise Refuse(f"unknown segment: {seg}")
    return sorted(glob.glob(f"src/{seg}/**/*.c", root_dir=ROOT, recursive=True))


def define_lines(text):
    """[(line number, logical #define text)] with backslash continuations joined."""
    out, lines, i = [], text.split("\n"), 0
    while i < len(lines):
        start, s = i + 1, lines[i]
        while s.endswith("\\") and i + 1 < len(lines):
            i += 1
            s = s[:-1] + lines[i]
        if re.match(r"\s*#\s*define\b", s):
            out.append((start, s))
        i += 1
    return out


def symbol_edits(seg, old, new, vram, func):
    """Token renames of OLD in the segment's symbol file, or the new line when OLD has none."""
    sf = rel(ledger.symfile(seg))
    if not os.path.exists(os.path.join(ROOT, sf)):
        raise Refuse(f"no symbol file: {sf}")
    lines = read(sf).split("\n")
    rx, edits, has = word(old), [], False
    for i, line in enumerate(lines, 1):
        has |= bool(re.match(rf"\s*{re.escape(old)}\s*=", line))
        edits += [(sf, i, m.start() + 1, old, new) for m in rx.finditer(line)]
    if has:
        return edits
    if vram is None:
        raise Refuse(f"no vram for {old}")
    lower = first = 0
    for i, line in enumerate(lines, 1):
        m = re.match(r"\s*\w+\s*=\s*0x([0-9A-Fa-f]+)\s*;", line)
        if m:
            first = first or i
            lower = i if int(m.group(1), 16) < vram else lower
    at = lower + 1 if lower else first or len(lines) + (lines[-1] != "")
    text = f"{new} = 0x{vram:08X};" + (" // type:func" if func else "")
    return edits + [(sf, at, 0, "", text)]


def cmd_symbol(a, func):
    old, new, seg = a.old, a.new, a.seg
    check_name(new)
    files = scope_files(seg)
    rx = word(old)
    heads = [p for d in LIBULTRA_HEADERS for p in sorted(glob.glob(f"{d}/**/*.h", root_dir=ROOT, recursive=True))]
    if func and (hit := first_hit(rx, heads)):
        raise Refuse(f"header-prototyped: {hit.split(':')[0]}")
    if seg in ("boot", "global"):
        ultra = sorted(glob.glob("src/**/libultra/**/*.c", root_dir=ROOT, recursive=True))
        if hit := first_hit(rx, ultra):
            raise Refuse(f"referenced in libultra: {hit}")
    syms = sorted(glob.glob("symbol_addrs*.txt", root_dir=ROOT))
    if hit := first_hit(word(new), files + syms + sorted(glob.glob("include/**/*.h", root_dir=ROOT, recursive=True))):
        raise Refuse(f"in use: {new} at {hit}")
    m = re.fullmatch(r"D_([0-9A-F]{8})", old)
    vram = int(m.group(1), 16) if m else ledger.vram_of(seg, old)
    pats = [(rx, new), (word(f"PROTO_SKIP_{old}"), f"PROTO_SKIP_{new}")]
    if vram is not None and f"D_{vram:08X}" != old:
        pats.append((word(f"D_{vram:08X}"), new))
    edits, macro = [], []
    for f in files:
        text = read(f)
        for ln, d in define_lines(text):
            if any(p.search(d) for p, n in pats if not n.startswith("PROTO_SKIP_")):  # skip defines are fine
                macro.append(f"{f}:{ln}")
        for i, line in enumerate(text.split("\n"), 1):
            for p, n in pats:
                edits += [(f, i, mm.start() + 1, mm.group(0), n) for mm in p.finditer(line)]
    if macro:
        raise Refuse("reference inside a macro: " + " ".join(macro))
    if not edits:
        raise Refuse(f"not found: {old}")
    edits += symbol_edits(seg, old, new, vram, func)
    apply(edits, a.dry_run)
    draft = f"drafts/{seg}/{old}.c"
    if func and os.path.exists(os.path.join(ROOT, draft)):
        dst = f"drafts/{seg}/{new}.c"
        print(f"MV {draft} {dst}")
        if not a.dry_run and subprocess.run(["git", "mv", draft, dst], cwd=ROOT, capture_output=True).returncode:
            os.replace(os.path.join(ROOT, draft), os.path.join(ROOT, dst))
    if not a.dry_run and os.path.exists(os.path.join(ROOT, "tools", "protos.py")):
        r = subprocess.run(["uv", "run", "tools/protos.py", "gen"], cwd=ROOT)
        if r.returncode:
            print(f"rename: tools/protos.py gen failed (exit {r.returncode})", file=sys.stderr)
            return 1
    return 0


# ---- field / local: AST renames ----

def key(c):
    f = c.location.file
    return None if f is None else (os.path.realpath(os.path.join(ROOT, f.name)), c.location.line, c.location.column)


def site(c, old, lines_of):
    """(file, line, col) of cursor C, and whether OLD is spelled there (False: inside a macro expansion)."""
    loc = c.location
    f = rel(loc.file.name)
    line = lines_of(f)[loc.line - 1]
    m = IDENT.match(line, loc.column - 1)
    return (f, loc.line, loc.column), bool(m and m.group(0) == old)


def line_cache():
    cache = {}

    def get(f):
        if f not in cache:
            cache[f] = read(f).split("\n")
        return cache[f]
    return get


def modes(f):
    return ([], ["-DNON_MATCHING"]) if "NON_MATCHING" in read(f) else ([],)


def macro_names(tu):
    return {c.spelling for c in tu.cursor.get_children() if c.kind == CursorKind.MACRO_DEFINITION}


def scan_members(job):
    """Member references to the FIELD_DECL at KEY in one TU: ([(file, line, col)], [(file, line, col,
    macro name)] for references inside a macro expansion)."""
    root, f, k, old = job
    set_root(root)
    lines_of, hits, macro = line_cache(), set(), set()
    for extra in modes(f):
        tu = clint.parse(f, extra)
        for top in tu.cursor.get_children():
            if not clint.same_file(top, f):
                continue
            for c in clint.walk(top):
                if c.kind in (CursorKind.MEMBER_REF_EXPR, CursorKind.MEMBER_REF):
                    r = c.referenced
                    if r is not None and r.kind == CursorKind.FIELD_DECL and key(r) == k:
                        s, ok = site(c, old, lines_of)
                        if ok:
                            hits.add(s)
                        else:  # the expansion site spells the macro's name
                            m = IDENT.match(lines_of(s[0])[s[1] - 1], s[2] - 1)
                            macro.add((*s, m.group(0) if m else "?"))
    return sorted(hits), sorted(macro)


def record_fields(rec):
    for ch in rec.get_children():
        if ch.kind == CursorKind.FIELD_DECL:
            yield ch
        elif ch.kind in (CursorKind.STRUCT_DECL, CursorKind.UNION_DECL) and ch.is_anonymous():
            yield from record_fields(ch)


def find_record(tu, path, name):
    for c in clint.walk(tu.cursor):
        rec = None
        if c.kind in (CursorKind.STRUCT_DECL, CursorKind.UNION_DECL) and c.spelling == name and c.is_definition():
            rec = c
        elif c.kind == CursorKind.TYPEDEF_DECL and c.spelling == name:
            d = c.underlying_typedef_type.get_canonical().get_declaration()
            rec = d.get_definition() if d.kind in (CursorKind.STRUCT_DECL, CursorKind.UNION_DECL) else None
        if rec is not None and clint.same_file(rec, path):
            return rec
    return None


def cmd_field(a):
    path, old, new = rel(a.path), a.field, a.new
    check_name(new)
    header = path.startswith("include" + os.sep)
    if header:
        virt = "/rename-virtual/field.c"
        inc = os.path.relpath(path, "include")
        tu = clint.parse(virt, unsaved=[(virt, f'#include "common.h"\n#include "{inc}"\n')])
    else:
        tu = clint.parse(path)
    rec = find_record(tu, path, a.struct)
    if rec is None:
        raise Refuse(f"{a.struct} is not defined in {path}")
    fields = list(record_fields(rec))
    target = next((f for f in fields if f.spelling == old), None)
    if target is None:
        raise Refuse(f"no field {a.struct}.{old}")
    if any(f.spelling == new for f in fields):
        raise Refuse(f"in use: field {a.struct}.{new}")
    if new in macro_names(tu):
        raise Refuse(f"in use: macro {new}")
    lines_of = line_cache()
    s, ok = site(target, old, lines_of)
    if not ok:
        raise Refuse(f"reference inside a macro: {s[0]}:{s[1]}:{s[2]}")
    files = clint.src_files() if header else [path]
    jobs = [(ROOT, f, key(target), old) for f in files]
    if a.j > 1 and len(jobs) > 1:
        with concurrent.futures.ProcessPoolExecutor(a.j) as ex:
            res = list(ex.map(scan_members, jobs))
    else:
        res = [scan_members(j) for j in jobs]
    set_root(ROOT)
    macro = sorted({m for _, ms in res for m in ms})
    edits = [(*s, old, new)] + [(f, l, c, old, new) for hs, _ in res for f, l, c in hs]
    if macro:
        if a.dry_run:  # list every reference, then refuse: a real rename cannot edit macro bodies
            apply(edits, True)
            for f, l, c, name in macro:
                print(f"MACRO {name} {f}:{l}:{c}")
        raise Refuse("reference inside a macro: " + " ".join(f"{f}:{l}:{c}" for f, l, c, _ in macro))
    apply(edits, a.dry_run)
    return 0


def cmd_local(a):
    path, old, new = rel(a.file), a.old, a.new
    check_name(new)
    lines_of, edits, macro, found = line_cache(), set(), set(), False
    for extra in modes(path):
        tu = clint.parse(path, extra)
        fn = next((c for n, _, d, _, _, _, c in clint.functions(tu, path) if n == a.func and d), None)
        if fn is None:
            continue
        decls = [c for c in clint.walk(fn) if c.kind in (CursorKind.PARM_DECL, CursorKind.VAR_DECL)]
        mine = {key(c) for c in decls}
        targets = {key(c) for c in decls if c.spelling == old}
        if not targets:
            continue
        found = True
        taken = {c.spelling for c in decls if c.spelling != old} | macro_names(tu) | {a.func}
        for c in clint.walk(fn):
            r = c.referenced if c.kind in (CursorKind.DECL_REF_EXPR, CursorKind.TYPE_REF) else None
            if r is not None and key(r) not in mine:
                taken.add(r.spelling)
        if new in taken:
            raise Refuse(f"in use in {a.func}: {new}")
        body = next(c for c in fn.get_children() if c.kind == CursorKind.COMPOUND_STMT)
        start = (body.extent.start.line, body.extent.start.column)
        for t in fn.get_tokens():  # parameter list and K&R declarations
            if (t.location.line, t.location.column) >= start:
                break
            if t.kind.name == "IDENTIFIER" and t.spelling == old:
                edits.add((path, t.location.line, t.location.column))
        for c in clint.walk(body):
            if (c.kind == CursorKind.VAR_DECL and key(c) in targets) or \
                    (c.kind == CursorKind.DECL_REF_EXPR and c.referenced is not None and key(c.referenced) in targets):
                s, ok = site(c, old, lines_of)
                (edits if ok else macro).add(s)
    if not found:
        raise Refuse(f"no parameter or local {old} in {a.func}")
    if macro:
        raise Refuse("reference inside a macro: " + " ".join(f"{f}:{l}:{c}" for f, l, c in sorted(macro)))
    apply([(*s, old, new) for s in edits], a.dry_run)
    return 0

# ---- fold: a split label into an access through its parent ----

HELD_BRIEF = ".scratch/cleanup-brief.md"


def held_files():
    """src files checked out by the current cleanup round: the `- src:` lines of the last `# Round`
    section of .scratch/cleanup-brief.md (none when there is no brief)."""
    p = os.path.join(ROOT, HELD_BRIEF)
    if not os.path.exists(p):
        return set()
    text = read(HELD_BRIEF)
    rounds = [m.start() for m in re.finditer(r"(?m)^# Round ", text)]
    last = text[rounds[-1]:] if rounds else ""
    return set(re.findall(r"(?m)^- src: (src/\S+?\.c)", last))


def fdiff_reloc_ok(copy, src):
    """Exit status of tools/fdiff.sh --reloc-ok COPY SRC (0: OK or RELOC-EQUIV OK)."""
    return subprocess.run(["tools/fdiff.sh", "--reloc-ok", copy, src], cwd=ROOT, capture_output=True).returncode


VERIFY = fdiff_reloc_ok


def label_sites(f, label):
    """([(line, col)] of DECL_REF_EXPRs naming LABEL, [(line, col, macro)] inside macro expansions,
    [line] of file-scope declarations of LABEL) in F."""
    lines_of, refs, macro, decls = line_cache(), set(), set(), set()
    for extra in modes(f):
        tu = clint.parse(f, extra)
        for top in tu.cursor.get_children():
            if not clint.same_file(top, f):
                continue
            if top.kind == CursorKind.VAR_DECL and top.spelling == label:
                decls.add(top.extent.start.line)
            for c in clint.walk(top):
                if c.kind == CursorKind.DECL_REF_EXPR and c.spelling == label:
                    s, ok = site(c, label, lines_of)
                    if ok:
                        refs.add(s[1:])
                    else:
                        m = IDENT.match(lines_of(s[0])[s[1] - 1], s[2] - 1)
                        macro.add((*s[1:], m.group(0) if m else "?"))
    return sorted(refs), sorted(macro), sorted(decls)


def fold_text(text, label, expr, refs, drop_decls):
    lines = text.split("\n")
    for ln, col in sorted(refs, reverse=True):
        s = lines[ln - 1]
        if s[col - 1:col - 1 + len(label)] != label:
            raise Refuse(f"line {ln}:{col}: expected {label}")
        lines[ln - 1] = s[:col - 1] + expr + s[col - 1 + len(label):]
    for ln in sorted(drop_decls, reverse=True):
        if not re.match(rf"\s*extern\b[^;]*\b{re.escape(label)}\b[^;]*;\s*(//.*)?$", lines[ln - 1]):
            raise Refuse(f"line {ln}: not a one-line extern declaration of {label}")
        del lines[ln - 1]
    return "\n".join(lines)


def cmd_fold(a):
    seg, label, expr = a.seg, a.label, a.expr
    parent = IDENT.match(expr)
    if not parent or parent.group(0) == label:
        raise Refuse(f"parent expression must start with the parent symbol: {expr}")
    files = [f for f in scope_files(seg) if f.endswith(".c") and word(label).search(read(f))]
    if not files:
        raise Refuse(f"not found: {label}")
    held = sorted(set(files) & (set(a.held) if a.held is not None else held_files()))
    if held:
        raise Refuse("referenced in checked-out files: " + " ".join(held))
    scratch = os.path.join(ROOT, ".scratch", "fold")
    folded, kept = {}, []
    for f in files:
        refs, macro, decls = label_sites(f, label)
        if macro:
            raise Refuse(f"reference inside a macro: {f}:" + " ".join(f"{l}:{c} ({m})" for l, c, m in macro))
        text = read(f)
        copy = os.path.join(scratch, f.replace("/", "_"), os.path.basename(f))
        os.makedirs(os.path.dirname(copy), exist_ok=True)

        def ok(subset):
            t = fold_text(text, label, expr, subset, decls if len(subset) == len(refs) else [])
            with open(copy, "w", encoding="latin-1", newline="") as fh:
                fh.write(t)
            return VERIFY(rel(copy), f) == 0, t

        good, t = ok(refs)
        chosen = list(refs) if good else []
        if not good and a.per_ref:  # greedy: keep each reference whose fold still matches
            for r in refs:
                g, _ = ok(chosen + [r])
                if g:
                    chosen.append(r)
            good, t = ok(chosen) if chosen else (False, text)
        for r in refs:
            print(f"{f}:{r[0]}:{r[1]} {label}→{expr}" + ("" if r in chosen else "  KEPT (fdiff mismatch)"))
        if good and (chosen or decls):  # also a file holding only the extern
            folded[f] = t
        if len(chosen) < len(refs):
            kept.append(f)
    if not a.dry_run:
        for f, t in folded.items():
            write(f, t)
    left = [f for f in scope_files(seg) if word(label).search(folded.get(f) or read(f))]
    left += [p for p in sorted(glob.glob("asm/**/*.s", root_dir=ROOT, recursive=True))
             if "nonmatchings" in p and word(label).search(read(p))][:1]
    if not left:
        for sf in sorted(glob.glob("symbol_addrs*.txt", root_dir=ROOT)) + sorted(glob.glob("undefined_syms*.txt", root_dir=ROOT)):
            lines = read(sf).split("\n")
            keep = [x for x in lines if not re.match(rf"\s*{re.escape(label)}\s*=", x)]
            if len(keep) != len(lines):
                print(f"{sf}: drop {label}")
                if not a.dry_run:
                    write(sf, "\n".join(keep))
    print(f"fold: {len(folded)} file(s) folded" + (f", references kept in {' '.join(kept)}" if kept else "")
          + (" (dry run)" if a.dry_run else ""))
    return 0 if not kept else 2



def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--root", default=clint.ROOT, help="repository root (default: this checkout)")
    sub = p.add_subparsers(dest="cmd", required=True)
    for name in ("func", "global"):
        s = sub.add_parser(name)
        s.add_argument("seg")
        s.add_argument("old")
        s.add_argument("new")
    s = sub.add_parser("field")
    s.add_argument("path")
    s.add_argument("struct")
    s.add_argument("field")
    s.add_argument("new")
    s.add_argument("-j", type=int, default=os.cpu_count() or 1)
    s = sub.add_parser("local")
    s.add_argument("file")
    s.add_argument("func")
    s.add_argument("old")
    s.add_argument("new")
    s = sub.add_parser("fold")
    s.add_argument("seg")
    s.add_argument("label")
    s.add_argument("expr")
    s.add_argument("--per-ref", action="store_true", help="fold only the references whose file still matches")
    s.add_argument("--held", nargs="*", default=None, help="checked-out src files (default: the brief's last round)")
    for s in sub.choices.values():
        s.add_argument("--dry-run", action="store_true")
    a = p.parse_args(argv)
    set_root(a.root)
    try:
        if a.cmd in ("func", "global"):
            return cmd_symbol(a, a.cmd == "func")
        if a.cmd == "fold":
            return cmd_fold(a)
        return cmd_field(a) if a.cmd == "field" else cmd_local(a)
    except Refuse as e:
        print(f"rename: refused: {e}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
