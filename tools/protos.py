# /// script
# requires-python = ">=3.12"
# dependencies = ["libclang==18.1.1"]
# ///
"""Generated prototype headers (include/proto/<seg>/<file>.h) and per-file consolidation onto them.

  uv run tools/protos.py gen [--check]       one header per defining src file, from its non-static
                                             definitions (K&R stays `ret name();`); prints
                                             `SKIP <name>: <reason>` for declarations it cannot write;
                                             deletes stale headers. --check writes nothing, exit 1
                                             listing headers that would change
  uv run tools/protos.py tag-structs <src.c> IN PLACE (run on a private copy): `typedef struct {`
                                             -> `typedef struct <Name> {` for untagged typedef'd
                                             structs used in non-static function signatures
  uv run tools/protos.py consolidate <src.c>... [-j N] --out DIR
                                             DIR/<file>.c copies (never src/) that include the shared
                                             headers and drop the file's own callee declarations where
                                             the whole object still matches (tools/fdiff.sh); one
                                             segment per DIR (basenames collide across segments)

Callee scope: a file in src/<overlay>/ sees its overlay's, global's and boot's headers (that order,
first hit wins); global sees global then boot; boot sees boot.
"""
import argparse
import concurrent.futures
import glob
import os
import re
import shutil
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import clint  # noqa: E402
from clang.cindex import CursorKind, TypeKind  # noqa: E402

ROOT = clint.ROOT
INCLUDE = os.path.join(ROOT, "include")
PROTO = os.path.join(INCLUDE, "proto")
NAMED = (TypeKind.ELABORATED, TypeKind.TYPEDEF, TypeKind.RECORD, TypeKind.ENUM)
FUNC_TYPES = (TypeKind.FUNCTIONPROTO, TypeKind.FUNCTIONNOPROTO)
ENTRY = re.compile(r"^#ifndef PROTO_SKIP_(\w+)\n(.*);\n#endif$", re.M)
CFE_ERROR = re.compile(r"cfe: Error: .*?, line \d+: (.*)")
PARKED_IF = re.compile(r"^\s*#\s*if(?:n?def)?\b.*\bNON_MATCHING\b")


class Skip(Exception):
    pass


def rel(path):
    return os.path.relpath(os.path.realpath(os.path.join(ROOT, path)), ROOT)


def seg_stem(path):
    """('global', '7130') for src/global/7130.c, ('boot', 'main') for src/boot/main.c."""
    parts = rel(path).split(os.sep)
    return parts[1], os.path.splitext(parts[-1])[0]


def header_of(seg, stem):
    return f"proto/{seg}/{stem}.h"


def guard(seg, stem):
    return "PROTO_" + re.sub(r"[^A-Za-z0-9]", "_", f"{seg}_{stem}").upper() + "_H"


_closure = None


def common_closure():
    """Real paths of common.h and everything it includes: never repeated as header includes."""
    global _closure
    if _closure is None:
        tu = clint.parse("include/common.h")
        _closure = {os.path.realpath(os.path.join(INCLUDE, "common.h"))}
        _closure |= {os.path.realpath(os.path.join(ROOT, i.include.name)) for i in tu.get_includes()}
    return _closure


class Ctx:
    """Rendering context of one declaration: the defining file, plus the includes/forward lines it needs."""

    def __init__(self, src):
        self.src = os.path.realpath(os.path.join(ROOT, src))
        self.includes, self.forwards = set(), set()


def tag_of(decl):
    """Tag of a record/enum declaration cursor, None when untagged (`struct {`)."""
    toks = [t.spelling for t in decl.get_tokens()][:2]
    return toks[1] if len(toks) == 2 and re.match(r"^[A-Za-z_]\w*$", toks[1]) else None


def quals(t):
    return ("const " if t.is_const_qualified() else "") + ("volatile " if t.is_volatile_qualified() else "")


def named(t, ctx, under_ptr):
    d = t.get_declaration()
    if d.location.file is None:
        raise Skip("unresolved type")
    path = os.path.realpath(os.path.join(ROOT, d.location.file.name))
    if path.startswith(INCLUDE + os.sep):
        if path not in common_closure():
            ctx.includes.add(os.path.relpath(path, INCLUDE))
        return t.spelling
    if path != ctx.src:
        raise Skip(f"type from {os.path.relpath(path, ROOT)}")
    if d.kind == CursorKind.TYPEDEF_DECL:
        u = d.underlying_typedef_type
        if quals(t) and u.kind == TypeKind.POINTER:
            raise Skip("qualified local pointer typedef")
        return quals(t) + render(u, ctx, under_ptr)
    if d.kind == CursorKind.ENUM_DECL:
        return quals(t) + "int"
    if d.kind in (CursorKind.STRUCT_DECL, CursorKind.UNION_DECL):
        kw = "struct" if d.kind == CursorKind.STRUCT_DECL else "union"
        if not under_ptr:
            raise Skip(f"by-value local {kw}")
        tag = tag_of(d)
        if tag is None:
            raise Skip(f"untagged local {kw}")
        ctx.forwards.add(f"{kw} {tag};")
        return quals(t) + f"{kw} {tag}"
    raise Skip(f"local {d.kind.name.lower()}")


def verbatim(t, parts, ctx):
    """t.spelling when every component type renders as itself (no file-local types), else Skip."""
    for p in parts:
        if p.kind != TypeKind.VOID and render(p, ctx) != p.spelling:
            raise Skip("function pointer naming local types")
    return t.spelling


def render(t, ctx, under_ptr=False):
    """Spelling of type T valid outside its defining file (typedef names kept), or Skip."""
    k = t.kind
    if k == TypeKind.INVALID:
        raise Skip("unresolved type")
    if k in NAMED:
        return named(t, ctx, under_ptr)
    if k == TypeKind.POINTER:
        p = t.get_pointee()
        if p.kind in FUNC_TYPES:
            args = list(p.argument_types()) if p.kind == TypeKind.FUNCTIONPROTO else []
            return verbatim(t, [p.get_result(), *args], ctx)
        if p.get_canonical().kind in (TypeKind.CONSTANTARRAY, TypeKind.INCOMPLETEARRAY):
            return verbatim(t, [p], ctx)
        s = render(p, ctx, True)
        return s + ("*" if s.endswith("*") else " *") + (" const" if t.is_const_qualified() else "")
    if k in (TypeKind.CONSTANTARRAY, TypeKind.INCOMPLETEARRAY):
        return verbatim(t, [t.element_type], ctx)
    if k in FUNC_TYPES:
        raise Skip("function type")
    return t.spelling


def declaration(c, ctx):
    """`<ret> <name>(<params>)` for function cursor C, or Skip."""
    rt = c.result_type
    if rt.kind == TypeKind.POINTER and rt.get_pointee().kind in FUNC_TYPES:
        raise Skip("function pointer return")
    ret = render(rt, ctx)
    if clint.knr(c):
        params = ""
    else:
        args = [render(a, ctx) for a in c.type.argument_types()]
        if c.type.is_function_variadic():
            args.append("...")
        params = ", ".join(args) or "void"
    return f"{ret}{'' if ret.endswith('*') else ' '}{c.spelling}({params})"


def header_text(path, seg=None, stem=None):
    """(header text or None when the file defines no non-static function, [(name, reason)] skips)."""
    if seg is None:
        seg, stem = seg_stem(path)
    tu = clint.parse(path)
    ctx, decls, skips = Ctx(path), [], []
    for name, static, defn, _, _, _, c in clint.functions(tu, path):
        if not defn or static:
            continue
        one = Ctx(path)
        try:
            decls.append((name, declaration(c, one)))
        except Skip as e:
            skips.append((name, str(e)))
            continue
        ctx.includes |= one.includes
        ctx.forwards |= one.forwards
    if not decls and not skips:
        return None, skips
    g = guard(seg, stem)
    out = [f"/* Generated by tools/protos.py gen from {rel(path)}: do not edit. */", f"#ifndef {g}", f"#define {g}",
           '#include "common.h"', *[f'#include "{h}"' for h in sorted(ctx.includes)], *sorted(ctx.forwards)]
    for name, d in decls:
        out += [f"#ifndef PROTO_SKIP_{name}", d + ";", "#endif"]
    out.append("#endif")
    return "\n".join(out) + "\n", skips


def _gen_one(path):
    seg, stem = seg_stem(path)
    text, skips = header_text(path, seg, stem)
    return os.path.join(PROTO, seg, stem + ".h"), text, skips


def cmd_gen(a):
    files = clint.src_files()
    with concurrent.futures.ProcessPoolExecutor() as ex:
        results = list(ex.map(_gen_one, files))
    want, nskip = {}, 0
    for hpath, text, skips in results:
        for name, why in skips:
            print(f"SKIP {name}: {why}")
        nskip += len(skips)
        if text is not None:
            want[hpath] = text
    have = set(glob.glob(os.path.join(PROTO, "**", "*.h"), recursive=True))
    changed = [h for h, t in sorted(want.items()) if not os.path.exists(h) or open(h).read() != t]
    stale = sorted(have - set(want))
    if a.check:
        for h in changed + stale:
            print(f"CHANGED {os.path.relpath(h, ROOT)}")
        print(f"gen --check: {len(changed) + len(stale)} header(s) out of date")
        sys.exit(1 if changed or stale else 0)
    for h in changed:
        os.makedirs(os.path.dirname(h), exist_ok=True)
        with open(h + ".tmp", "w") as f:  # atomic: concurrent compiles may be reading the old header
            f.write(want[h])
        os.replace(h + ".tmp", h)
    for h in stale:
        os.remove(h)
    for d in sorted(glob.glob(os.path.join(PROTO, "*")), reverse=True):
        if os.path.isdir(d) and not os.listdir(d):
            os.rmdir(d)
    print(f"gen: {len(want)} headers ({len(changed)} written, {len(stale)} deleted), {nskip} skipped")


def signature_records(t, src, out):
    """Collect (typedef cursor, record cursor) of untagged typedef'd records of SRC that type T names."""
    if t.kind in NAMED:
        d = t.get_declaration()
        if d.location.file is None or os.path.realpath(os.path.join(ROOT, d.location.file.name)) != src:
            return
        if d.kind == CursorKind.TYPEDEF_DECL:
            u = d.underlying_typedef_type
            r = u.get_declaration()
            if r.kind in (CursorKind.STRUCT_DECL, CursorKind.UNION_DECL) and tag_of(r) is None:
                out[d.spelling] = r
            signature_records(u, src, out)
    elif t.kind == TypeKind.POINTER:
        signature_records(t.get_pointee(), src, out)
    elif t.kind == TypeKind.FUNCTIONPROTO:
        for p in [t.get_result(), *t.argument_types()]:
            signature_records(p, src, out)


def cmd_tag_structs(a):
    path = a.src
    src = os.path.realpath(path)
    tu = clint.parse(path)
    found = {}
    for _, static, defn, _, _, _, c in clint.functions(tu, path):
        if defn and not static:
            signature_records(c.type, src, found)
    used = {tag_of(c) for c in clint.walk(tu.cursor) if clint.same_file(c, path) and
            c.kind in (CursorKind.STRUCT_DECL, CursorKind.UNION_DECL, CursorKind.ENUM_DECL)} - {None}
    lines = open(path).read().split("\n")
    edits = []
    for name, r in sorted(found.items()):
        if name in used:
            print(f"SKIP {name}: tag in use")
            continue
        kw = next(r.get_tokens())
        edits.append((kw.extent.end.line, kw.extent.end.column, name))
        print(f"TAG {name}")
    for line, col, name in sorted(edits, reverse=True):
        s = lines[line - 1]
        lines[line - 1] = s[:col - 1] + " " + name + s[col - 1:]
    with open(path, "w") as f:
        f.write("\n".join(lines))


# ---------------------------------------------------------------- consolidate


def load_headers():
    """{seg: [(include path, {name: declaration})]} from the generated headers, path order."""
    out = {}
    for h in sorted(glob.glob(os.path.join(PROTO, "*", "*.h"))):
        seg = os.path.basename(os.path.dirname(h))
        out.setdefault(seg, []).append((os.path.relpath(h, INCLUDE), dict(ENTRY.findall(open(h).read()))))
    return out


def scope(seg):
    return {"boot": ["boot"], "global": ["global", "boot"]}.get(seg, [seg, "global", "boot"])


def find_header(name, seg, table):
    for s in scope(seg):
        for h, names in table.get(s, []):
            if name in names:
                return h, names[name]
    return None


def top_include(lines):
    """Index of the last `#include` line of the file's leading include block."""
    last, comment = None, False
    for i, s in enumerate(lines):
        t = s.strip()
        if comment:
            comment = "*/" not in t
            continue
        if not t or t.startswith("//"):
            continue
        if t.startswith("/*"):
            comment = "*/" not in t
            continue
        if re.match(r"#\s*include\b", t):
            last = i
            continue
        break
    return last


def removable(c, lines):
    """Line indices of top-level declaration C when it alone occupies them, else None."""
    s, e = c.extent.start, c.extent.end
    if s.file is None or lines[s.line - 1][:s.column - 1].strip():
        return None
    rest = lines[e.line - 1][e.column - 1:].lstrip()
    if not re.match(r"^;\s*(//.*|/\*.*\*/\s*)?$", rest):
        return None
    return set(range(s.line - 1, e.line))


def parked_regions(lines):
    """Line numbers (1-based) inside `#if...NON_MATCHING` conditionals (both branches)."""
    out, stack = set(), []
    for i, s in enumerate(lines, 1):
        t = s.strip()
        if re.match(r"#\s*if", t):
            stack.append(bool(PARKED_IF.match(t)))
        elif re.match(r"#\s*endif", t) and stack:
            stack.pop()
        if any(stack):
            out.add(i)
    return out


class Analysis:
    """What consolidate needs from the clang view of one src file."""

    def __init__(self, path):
        self.path = path
        self.lines = open(os.path.join(ROOT, path)).read().split("\n")
        tu = clint.parse(path)
        self.decls, self.defs, self.static, self.refs, self.block, self.first = {}, set(), set(), {}, {}, {}
        self.tops = [c for c in tu.cursor.get_children() if clint.same_file(c, path)]
        # Names a header must not declare here: static functions, and file-scope non-functions.
        self.clash = {c.spelling: "// PROTO: not a function here" for c in self.tops
                      if c.kind in (CursorKind.VAR_DECL, CursorKind.TYPEDEF_DECL)}
        for c in self.tops:
            if c.kind != CursorKind.FUNCTION_DECL:
                continue
            self.mark(c.spelling, c.extent.start.line)
            if c.storage_class == clint.ci.StorageClass.STATIC:
                self.static.add(c.spelling)
                self.clash[c.spelling] = "// PROTO: static in this file"
            if c.is_definition():
                self.defs.add(c.spelling)
                for d in clint.walk(c):
                    if d.kind == CursorKind.FUNCTION_DECL:
                        self.block.setdefault(d.spelling, []).append(d.location.line)
            else:
                self.decls.setdefault(c.spelling, []).append(c)
        for top in self.tops:
            for d in clint.walk(top):
                if d.kind == CursorKind.DECL_REF_EXPR and d.referenced is not None and \
                        d.referenced.kind == CursorKind.FUNCTION_DECL and clint.same_file(d, path):
                    self.refs.setdefault(d.spelling, []).append(d.location.line)
                    self.mark(d.spelling, d.location.line)
        # Functions declared inside NON_MATCHING conditionals, seen with and without -DNON_MATCHING.
        region = parked_regions(self.lines)
        self.parked = set()
        for t in (tu, clint.parse(path, extra=("-DNON_MATCHING",))):
            for d in clint.walk(t.cursor):
                if d.kind == CursorKind.FUNCTION_DECL and clint.same_file(d, path) and d.location.line in region:
                    self.parked.add(d.spelling)

    def mark(self, name, line):
        self.first[name] = min(line, self.first.get(name, line))


class Work:
    """One file's consolidation state: the copy is rebuilt from src text plus these edits."""

    def __init__(self, src, out):
        self.src = rel(src)
        seg, stem = seg_stem(src)
        self.dir = os.path.join(out, ".work", f"{seg}_{stem}")
        os.makedirs(os.path.join(ROOT, self.dir), exist_ok=True)
        self.try_path = os.path.join(self.dir, os.path.basename(src))
        self.obj = os.path.join(ROOT, "build", ".scratch", self.try_path.replace("/", "_") + ".o")
        self.skips, self.includes, self.removed, self.tags = {}, set(), set(), {}

    def text(self, a):
        at = top_include(a.lines)
        block = [f"#define PROTO_SKIP_{n}" + (f" {c}" if c else "") for n, c in sorted(self.skips.items())]
        block += [f'#include "{h}"' for h in sorted(self.includes)]
        out = [] if at is not None else block
        for i, s in enumerate(a.lines):
            if i not in self.removed:
                out.append(s + (" " + self.tags[i] if i in self.tags else ""))
            if i == at:
                out += block
        return "\n".join(out)

    def run(self, text, nonmatching=False):
        """(status, message): status 'error' (no object), else the fdiff exit code."""
        with open(os.path.join(ROOT, self.try_path), "w") as f:
            f.write(text)
        if os.path.exists(self.obj):
            os.remove(self.obj)
        cmd = ["tools/fdiff.sh", *(["--non-matching"] if nonmatching else []), self.try_path, self.src]
        r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
        out = r.stdout + r.stderr
        m = CFE_ERROR.search(out)
        if m or not os.path.exists(self.obj):
            msg = m.group(1) if m else next((s for s in out.splitlines() if "rror" in s), f"exit {r.returncode}")
            return "error", msg.strip()[:60]
        return r.returncode, ""


def consolidate(src, out):
    """Consolidate one file; returns (report lines, copy text or None)."""
    a, w, log = Analysis(src), Work(src, out), []
    seg, _ = seg_stem(src)
    table = load_headers()
    base, msg = w.run("\n".join(a.lines))
    if base == "error":
        return [f"BLOCKED {w.src}: src does not compile: {msg}", f"{w.src} KEEP 0 STEER 0 PROTO 0 BLOCKED 1"], None

    def ok(text):
        return w.run(text)[0] == base

    # 1. Callees: referenced or file-scope-declared functions with a header in scope.
    callees = {}
    for name in sorted(set(a.refs) | set(a.decls) | a.defs, key=lambda n: (a.first[n], n)):
        if name not in a.static and (hit := find_header(name, seg, table)):
            callees[name] = hit
    headers = sorted({h for h, _ in callees.values()})
    clashes = {h: sorted(set(a.clash) & set(dict(table_entries(table, h)))) for h in headers}
    counts = dict(KEEP=0, STEER=0, PROTO=0, BLOCKED=0)

    # 2. Initial copy: every callee skipped; drop (BLOCKED) headers that break the compile.
    def add(h):
        w.includes.add(h)
        for n, (hh, _) in callees.items():
            if hh == h:
                w.skips[n] = ""
        for n in clashes[h]:
            w.skips[n] = a.clash[n]

    def drop(h):
        w.includes.discard(h)
        for n in [n for n, (hh, _) in callees.items() if hh == h]:
            w.skips.pop(n, None)
            del callees[n]
        for n in clashes[h]:
            if not any(n in dict(table_entries(table, x)) for x in w.includes):
                w.skips.pop(n, None)

    for h in headers:
        add(h)
    if headers and not ok(w.text(a)):
        w.includes.clear()
        w.skips.clear()
        for h in headers:
            add(h)
            st, m = w.run(w.text(a))
            if st != base:
                drop(h)
                log.append(f"BLOCKED {h}: {m or f'fdiff exit {st}'}")
                counts["BLOCKED"] += 1
    for n in sorted(n for n in w.skips if n in a.clash):
        log.append(f"PROTO {n}: {a.clash[n][len('// PROTO: '):]}")
        counts["PROTO"] += 1

    for n in callees:
        for line in a.block.get(n, []):
            log.append(f"LOCAL {n}: block-scope declaration at {w.src}:{line} left alone")

    def decl_lines(n):
        """Line indices of N's file-scope declarations, or None when one shares its lines."""
        out = set()
        for c in a.decls.get(n, []):
            r = removable(c, a.lines)
            if r is None:
                return None
            out |= r
        return out

    # 3. Bulk pass: identical declarations that precede the first call, and own definitions that do.
    def bulk_ok(n):
        first_ref = min(a.refs.get(n, [10 ** 9]))
        ds = a.decls.get(n, [])
        if not ds:
            return n in a.defs and first_ref >= a.first[n]
        if decl_lines(n) is None or min(c.extent.start.line for c in ds) > first_ref:
            return False
        for c in ds:
            try:
                if declaration(c, Ctx(src)) != callees[n][1]:
                    return False
            except Skip:
                return False
        return True

    bulk = [n for n in callees if bulk_ok(n)]
    done = set()
    if bulk:
        saved = set(w.removed)
        for n in bulk:
            w.skips.pop(n)
            w.removed |= decl_lines(n)
        if ok(w.text(a)):
            done = set(bulk)
            for n in bulk:
                log.append(f"KEEP {n}")
            counts["KEEP"] += len(bulk)
        else:
            w.removed = saved
            for n in bulk:
                w.skips[n] = ""

    # 4. Greedy pass in order of first appearance.
    for n in callees:
        if n in done:
            continue
        lines = decl_lines(n) or set()
        saved = set(w.removed)
        w.skips.pop(n)
        w.removed |= lines
        st, m = w.run(w.text(a))
        if st == base:
            log.append(f"KEEP {n}")
            counts["KEEP"] += 1
            continue
        w.removed = saved
        if st == "error":
            w.skips[n] = f"// PROTO: {m}"
            log.append(f"PROTO {n}: {m}")
            counts["PROTO"] += 1
            continue
        declared = bool(a.decls.get(n) or a.block.get(n))
        w.skips[n] = "// FAKE: callee prototype steer" if declared else "// FAKE: implicit declaration steer"
        for c in a.decls.get(n, []):
            last = c.extent.end.line - 1
            if "// FAKE" not in a.lines[last] and last not in w.tags:
                w.tags[last] = "// FAKE: callee prototype steer"
        log.append(f"STEER {n}")
        counts["STEER"] += 1

    # 5. Final check: match, and the parked (-DNON_MATCHING) compile.
    text = w.text(a)
    final = w.run(text)
    if final[0] != base:
        log.append(f"BLOCKED {w.src}: final check {final}")
        counts["BLOCKED"] += 1
        return log + [summary(w.src, counts)], None
    if w.run(text, nonmatching=True)[0] != 0:
        for n in sorted(a.parked):
            if n in callees and n not in w.skips:
                w.skips[n] = "// PROTO: parked block declares its own"
                w.removed -= decl_lines(n) or set()
                counts["KEEP"] -= 1
                counts["PROTO"] += 1
                log.append(f"PROTO {n}: parked block declares its own")
        text = w.text(a)
        st, m = w.run(text, nonmatching=True)
        if st != 0 or w.run(text)[0] != base:
            src_nm = w.run("\n".join(a.lines), nonmatching=True)[0]
            if st != 0 and src_nm != 0:
                log.append(f"NOTE {w.src}: src itself fails the non-matching compile")
            else:
                log.append(f"BLOCKED {w.src}: non-matching")
                return log + [summary(w.src, dict(counts, BLOCKED=counts["BLOCKED"] + 1))], None
    changed = text != "\n".join(a.lines)
    return log + [summary(w.src, counts) + ("" if changed else " (unchanged)")], text if changed else None


def table_entries(table, h):
    seg = h.split("/")[1]
    for hh, names in table.get(seg, []):
        if hh == h:
            return names.items()
    return ()


def summary(src, c):
    return f"{src} KEEP {c['KEEP']} STEER {c['STEER']} PROTO {c['PROTO']} BLOCKED {c['BLOCKED']}"


def _consolidate_one(src, out):
    log, text = consolidate(src, out)
    if text is not None:
        with open(os.path.join(ROOT, out, os.path.basename(src)), "w") as f:
            f.write(text)
    shutil.rmtree(os.path.join(ROOT, out, ".work", "_".join(seg_stem(src))), ignore_errors=True)
    return "\n".join(log)


def cmd_consolidate(a):
    out = os.path.relpath(os.path.abspath(a.out), ROOT)
    os.makedirs(os.path.join(ROOT, out), exist_ok=True)
    srcs = [rel(s) for s in a.srcs]
    with concurrent.futures.ProcessPoolExecutor(max_workers=a.j) as ex:
        for text in ex.map(_consolidate_one, srcs, [out] * len(srcs)):
            print(text, flush=True)
    work = os.path.join(ROOT, out, ".work")
    if os.path.isdir(work) and not os.listdir(work):
        os.rmdir(work)


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    s = p.add_subparsers(dest="cmd", required=True)
    c = s.add_parser("gen")
    c.add_argument("--check", action="store_true")
    c.set_defaults(fn=cmd_gen)
    c = s.add_parser("tag-structs")
    c.add_argument("src")
    c.set_defaults(fn=cmd_tag_structs)
    c = s.add_parser("consolidate")
    c.add_argument("srcs", nargs="+")
    c.add_argument("-j", type=int, default=1)
    c.add_argument("--out", required=True)
    c.set_defaults(fn=cmd_consolidate)
    a = p.parse_args()
    for k in ("src", "out"):
        if getattr(a, k, None):
            setattr(a, k, os.path.abspath(getattr(a, k)))
    if getattr(a, "srcs", None):
        a.srcs = [os.path.abspath(s) for s in a.srcs]
    os.chdir(ROOT)
    a.fn(a)


if __name__ == "__main__":
    main()
