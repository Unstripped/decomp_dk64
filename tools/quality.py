# /// script
# requires-python = ">=3.12"
# dependencies = ["libclang==18.1.1"]
# ///
"""Code-quality ledger of the cleanup campaign: FAKE/goto/untagged-hack sites per C function, the
method ladder that exhausts them, and the per-function `review` coverage.

  uv run tools/quality.py sweep <src.c>... [-j N] [--copy-of <src.c>] [--record --unit U]
  uv run tools/quality.py record --unit U --agent A [--base REV] [--model SEL] [--skip-missing] --batch FILE|-
  uv run tools/quality.py status [--file src/..c] [--func NAME]
  uv run tools/quality.py rank [--seg S] [--limit N] [--polish]
                                         hack queue: functions with hack sites, weakest earlier
                                         attempts first (best model strength, then most hacks);
                                         --polish: per file, functions without hack sites left open
  uv run tools/quality.py history FUNC [--file src/..c] [--all]
                                         the function's agent events (sweep/carry with --all)
  uv run tools/quality.py backfill-models SESSIONS_DIR [--dry-run]
                                         fill drafts/quality/models.jsonl (unit, agent) -> model
                                         from worker session transcripts
  uv run tools/quality.py permute-candidates --max-base N --out DIR [--limit N]
                                         copies + list.tsv for `tools/permute.py batch`
  uv run tools/quality.py report [--baseline REV] [--markdown]
  uv run tools/quality.py carry --rev REV --unit U [--header-carve] [--dry-run] [--func NAME]... [src.c...]
                                         re-stamp results of functions that
                                         changed since REV only by renames of declared names (same type,
                                         field offset or symbol address; clang-checked) or only by
                                         file-scope text of the .c they do not use (same body tokens,
                                         same text for every declaration/type/macro they reach; both
                                         versions parse against the current headers for these checks;
                                         a reached declaration that moved between the .c and an
                                         include/ header counts as unchanged when identical: a record
                                         with the same clint record_layout, else the same tokens;
                                         "(moved to|from <header>, identical)"; a function or
                                         variable declaration respelled, in place or so moved, with
                                         the same canonical clang type counts as unchanged too:
                                         "(<name> declaration respelled|moved ..., same type)"). REV's sites and
                                         fingerprints use REV's headers, and automatic results carry
                                         only when the reached include/ declarations apart from moved
                                         ones are unchanged since REV. A body renaming fields of a
                                         reached record (include/ or the .c's own), or unchanged while
                                         such a record's unused fields were renamed, carries
                                         (automatic results too) when its body parsed at REV with REV's
                                         headers is such a rename of (or equal to) HEAD's and every
                                         declaration it reaches (.c or header) is unchanged apart from the
                                         renames (or moved/respelled with the same type, as above), each
                                         changed record keeping its clint record_layout modulo field names
                                         (nested unnamed records' too); unused file-scope text may differ
                                         ("(renames; record field renames: <record>)"); a global replaced by
                                         a field access (a split-label fold) is no rename.
                                         --header-carve: instead carry the automatic results of functions
                                         whose fp_local and sites are unchanged and whose reached include/
                                         declarations changed only by record carves keeping size, offsets,
                                         alignment and field types (clint layout_diff; REV parsed with REV's
                                         headers); any other reached change (prototype, macro, typedef,
                                         enum, layout) is listed as skipped. --dry-run writes nothing.
                                         --func NAME (repeatable; REV's or HEAD's name): only those functions.

Ledger: drafts/quality/ (env DK64_QUALITY_LEDGER overrides), append-only, sharded: units.jsonl plus
<seg>/<VRAM top 16 bits>.jsonl (one function's events always share a shard). Functions are keyed
by (seg, vram): symbol file / asm / link map via tools/ledger.py, else the build ELF symbol table,
else (statics IDO keeps out of the symbol table) the object's .mdebug procedure symbol plus its
link-map .text address; an unresolvable function is an error.

Sites: every `// FAKE` or `// PROTO:` line outside `#ifdef NON_MATCHING` (file-scope lines belong
to the first later function that names the declared symbol), plus clint's AST `untagged` hits
(gotos always), plus one `warning` site per IDO `cfe: Warning` line of the file's matching compile
(tools/cwarn.py; a header's warnings are counted but get no site). Key
`<seg>:<VRAM8>:<kind>:<sha1(code without comments/whitespace)[:6]>[#n]`; an untagged site's hash
starts with `u`; a warning site hashes `<warning code>\\0` + its line's code; #n (n >= 2) orders
identical sites within the function.

Ladder (required fresh methods per kind; first missing = next):
  dead-if                        remove cond classify, then recipe diagnose unless classify kept
  volatile do-while0 dead-store  remove cond recipe diagnose
  noop-arith comma punned-cast other  plain recipe diagnose
  proto-steer implicit-steer     consolidate diagnose
  goto                           goto-hand
  proto-type                     never exhausted (its function ignores it after a fresh `views` blocked)
  warning                        retype (`fixed`; `kept` with note `fdiff=<1|3>` of the attempted fix;
                                 `blocked` with a note naming the missing header/owner change)
permute is optional (in no ladder); an offline batch (`permute-candidates`, `permute.py batch`) runs it.
Satisfied by the method's newest event (by time) when fresh and not `blocked`; a fresh `hit` means
next=apply.
Fresh: remove/plain/cond/classify/recipe/consolidate/views/names need equal fp_local and fp_hdr2 (hash
of the include/ declarations, types and macros the function reaches, or the whole header fp_hdr when
it reaches a `##` macro; events without it: the whole
header fp_hdr); diagnose/permute/reconstruct/goto-hand/retype/review need equal fp_local and no
knowledge/ido file committed after the event that names the function (never through note text),
except an entry naming the function whose frontmatter `unit` produced the event (a carried event:
the event it copies).
`// ORIG: ... 0x<offset>` lines (a construct the target asm really performs) are not sites.
Review checklist tokens: fake goto casts views protos temps names uninit warn.
A function is EXHAUSTED with a fresh `review`, every site exhausted, and (3+ non-kept non-warning sites) a
fresh function-level `reconstruct`; without a fresh review it is OPEN next=review.

sweep: remove (dead ifs, (void)x, dead stores, do{}while(0) wrappers, volatile; all together,
  singles, pairs if >2, triples if 3..6), plain (one rewrite per site line), cond (condition flips
  with all / each removal, pre-scored by deadsweep score --body), classify (dead if -> `if (<int
  local>) {}`: kept = class 1), recipe (tools/variants.py natural respellings, swapped comparison
  operands, float literal suffixes, local widths, declaration order, scanned on the all-removal,
  each single removal when there are several, and each plain rewrite). A hit needs tools/fdiff.sh --reloc-ok exit 0 (OK or RELOC-EQUIV OK) and no new clint uninit pair; it
  is written to .scratch/quality/hits/<seg>_<file>_<n>.c (`HIT <keys> <method> <path>`), never
  applied. --record appends one event per site and method (agent `sweep`), every sweep method of
  the site's ladder included: a site the sweep has no edit for (a dead test or `do {` sharing its
  line with other statements, an if with a body) records remove/cond/recipe `nohit` (`no removal`) and
  classify `nohit` (`no guard`), so the next sweep refreshes them after a header change. Warning sites are not
  swept; each prints `WARN <key> line <n> [W<code> <msg>]` (a copy's warning-site keys).
record line: <site-key|func:<seg>:<name>> <method> <outcome> [quirks=Q1,Q2] [seconds=N] [base=N]
  [best=N] [commit=H] [note="..."] [new="..."]; all lines validated (keys at HEAD, fixed sites at --base REV:
  REV's text analysed and compiled against REV's headers) before anything is written. A failed
  compile exits 1 naming the file, the rev and the first `cfe: Error` line. A diagnose/permute/
  reconstruct/goto-hand line on a site (reconstruct: function) another unit or agent already tried
  with that method needs new="<what this attempt tried that earlier ones did not>". --model
  stores the worker selector on every event; --skip-missing drops lines whose key no longer
  resolves (`record: skipped line N`).
"""
import argparse
import collections
import datetime
import hashlib
import itertools
import json
import glob
import multiprocessing
import os
import re
import shlex
import shutil
import struct
import subprocess
import sys
import tempfile
import threading
import time
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import clint  # noqa: E402
import cwarn  # noqa: E402
import ledger  # noqa: E402
import quirks  # noqa: E402
from clang.cindex import CursorKind, StorageClass, TokenKind, TypeKind  # noqa: E402

ROOT = clint.ROOT
LEDGER = os.environ.get("DK64_QUALITY_LEDGER") or os.path.join(ROOT, "drafts", "quality")
SCRATCH = os.path.join(ROOT, ".scratch", "quality")

KINDS = ("dead-if", "volatile", "do-while0", "dead-store", "noop-arith", "comma", "punned-cast",
         "proto-steer", "implicit-steer", "proto-type", "goto", "other", "warning")
LADDER = {"dead-if": ("remove", "cond", "classify", "recipe", "diagnose"),
          **dict.fromkeys(("volatile", "do-while0", "dead-store"), ("remove", "cond", "recipe", "diagnose")),
          **dict.fromkeys(("noop-arith", "comma", "punned-cast", "other"), ("plain", "recipe", "diagnose")),
          **dict.fromkeys(("proto-steer", "implicit-steer"), ("consolidate", "diagnose")),
          "goto": ("goto-hand",), "proto-type": (), "warning": ("retype",)}
METHODS = ("remove", "plain", "cond", "classify", "recipe", "consolidate", "diagnose", "permute", "reconstruct",
           "goto-hand", "views", "names", "review", "retype")
AUTO = {"remove", "plain", "cond", "classify", "recipe", "consolidate", "views", "names"}
HARD = ("diagnose", "permute", "reconstruct", "goto-hand")  # agent methods a retry must name something new for
FUNC_ONLY = {"views", "names", "review"}
OUTCOMES = ("hit", "fixed", "nohit", "kept", "blocked")
CHECKLIST = ("fake", "goto", "casts", "views", "protos", "temps", "names", "uninit", "warn")
PLAIN_KINDS = {"noop-arith", "comma", "punned-cast", "other"}

DEAD_IF = re.compile(r"if \(.*\)\s*\{\s*\}")
NOOP = re.compile(r"\^ ?0\b|\| ?0\b|& ?0\b|\* ?0\b|\+ ?0U?\b")
DO_WHILE = re.compile(r"\bdo \{|while \(0\)")
PUN = re.compile(r"\*\([^)]*\*\)&")
GUARD = re.compile(r"^(\s*)if \((.*)\)\s*\{\s*\}\s*(//.*)?$")
VOID = re.compile(r"^\s*\(void\)[^;]*;\s*(//.*)?$")
STORE = re.compile(r"^\s*[A-Za-z_]\w*(\[[^\]]*\])?\s*=\s*[^=;][^;]*;\s*//")
DEAD_WORD = re.compile(r"dead|kill|no-code|extra web|ghost", re.I)
DO_OPEN = re.compile(r"^\s*do \{\s*$")
DO_CLOSE = re.compile(r"^\s*\}\s*while \(0\);\s*$")
DO_LINE = re.compile(r"^\s*do \{\s*\} while \(0\);\s*$")
GOTO = re.compile(r"\bgoto\b")
SITE_KEY = re.compile(r"^(\w+):([0-9A-F]{8}):([a-z0-9-]+):([0-9a-fu][0-9a-f]{5})(?:#(\d+))?$")
FUNC_KEY = re.compile(r"^func:(\w+):(\w+)$")
INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+"([^"]+)"', re.M)
HDR_DIRS = ("include", "include/PR", "include/libultra", "include/compiler/ido")
INT_KINDS = {TypeKind.BOOL, TypeKind.CHAR_U, TypeKind.UCHAR, TypeKind.USHORT, TypeKind.UINT, TypeKind.ULONG,
             TypeKind.ULONGLONG, TypeKind.CHAR_S, TypeKind.SCHAR, TypeKind.SHORT, TypeKind.INT, TypeKind.LONG,
             TypeKind.LONGLONG}
LVALUE = r"([A-Za-z_]\w*(?:(?:->|\.)\w+)*)"
PLAIN = [(re.compile(r"\s*\^\s*0\b"), ""), (re.compile(r"\s*\|\s*0\b"), ""), (re.compile(r"\s*\+\s*0U?\b"), ""),
         (re.compile(r"\s*&\s*0xFFFFFFFF\b"), ""), (re.compile(r"\(0,\s*"), "("),
         (re.compile(r"\*\(\w+\s*\*\)&(\w+)"), r"\1"), (re.compile(r"\(s16\)\(s32\)"), "(s16)"),
         (re.compile(r"\[([^\]]+) \* 1\]"), r"[\1]"),
         # the low half/byte of a wider big-endian object, `((T *)&g)[n]` / `*((T *)&g + n)` with
         # n = sizeof(g) / sizeof(T) - 1: plain `g` when a narrow assignment or parameter truncates (Q0594)
         (re.compile(r"\(\(\w+\s*\*\)&" + LVALUE + r"\)\[[1-9]\]"), r"\1"),
         (re.compile(r"\*\(\(\w+\s*\*\)&" + LVALUE + r"\s*\+\s*[1-9]\)"), r"\1")]
FLIPS = [(re.compile(r"\bif \(([^()]*?) != 0\)"), r"if (\1)"),
         (re.compile(r"\bif \(([^()]*?) == 0\)"), r"if (!\1)"),
         (re.compile(r"\bif \(!([A-Za-z_][\w\->\.\[\]]*)\)"), r"if (\1 == 0)"),
         (re.compile(r"\bif \(([A-Za-z_][\w\->\.\[\]]*)\) \{(?!\})"), r"if (\1 != 0) {")]


def rel(p):
    """ROOT-relative form of a repo path. Relative inputs are already ROOT-relative
    (git, ledger, internal joins) and are never re-resolved against the process cwd."""
    return os.path.relpath(os.path.join(ROOT, p), ROOT)


def cli_path(p):
    """argparse type: a user-typed path, relative to the user's cwd, made ROOT-relative once."""
    return rel(os.path.abspath(p))


def seg_of(path):
    parts = rel(path).split(os.sep)
    if len(parts) < 3 or parts[0] != "src":
        sys.exit(f"quality: {path}: not a src/<seg>/ file (sweep a copy with --copy-of <src.c>)")
    return parts[1]


def seg_files(seg):
    d = os.path.join(ROOT, "src", seg)
    return sorted(os.path.join("src", seg, f) for f in os.listdir(d) if f.endswith(".c"))


# ---------------------------------------------------------------- function identity

_elf, _mdebug, _text = {}, {}, {}


def elf_secs(d):
    shoff, = struct.unpack_from(">I", d, 0x20)
    shentsize, shnum = struct.unpack_from(">HH", d, 0x2E)
    return [struct.unpack_from(">IIIIIIIIII", d, shoff + i * shentsize) for i in range(shnum)]


def cstr(d, a):
    return d[a:d.index(b"\0", a)].decode("latin-1")


def elf_funcs(seg):
    """{name: [(vram, object stem)]} of every FUNC symbol of the segment's build ELF (local ones included)."""
    if seg not in _elf:
        path = os.path.join(ROOT, "build", "dk64.us.elf" if seg == "boot" else f"{seg}.elf")
        out = collections.defaultdict(list)
        if os.path.exists(path):
            d = open(path, "rb").read()
            secs = elf_secs(d)
            for s in secs:
                if s[1] != 2:  # SHT_SYMTAB
                    continue
                strtab, stem = secs[s[6]][4], None
                for i in range(s[5] // (s[9] or 16)):
                    nm, val, _, info, _, _ = struct.unpack_from(">IIIBBH", d, s[4] + i * (s[9] or 16))
                    if info & 0xF == 4:  # STT_FILE: the locals that follow belong to it
                        stem = os.path.splitext(os.path.basename(cstr(d, strtab + nm)))[0]
                    elif info & 0xF == 2:
                        out[cstr(d, strtab + nm)].append((val, stem if info >> 4 == 0 else None))
        _elf[seg] = dict(out)
    return _elf[seg]


def mdebug_procs(obj):
    """{name: .text offset} of the procedure symbols of an IDO object's .mdebug (static functions,
    which IDO leaves out of the ELF symbol table, included)."""
    if obj not in _mdebug:
        out, path = {}, os.path.join(ROOT, obj)
        if os.path.exists(path):
            d = open(path, "rb").read()
            for s in elf_secs(d):
                if s[1] != 0x70000005:  # SHT_MIPS_DEBUG (ECOFF symbolic header)
                    continue
                h = struct.unpack_from(">hh" + "I" * 23, d, s[4])[2:]
                sym_off, ss_off, nfd, fd_off = h[8], h[14], h[17], h[18]
                for f in range(nfd):
                    _, _, iss_base, _, isym_base, csym = struct.unpack_from(">IIIIII", d, fd_off + f * 72)
                    for i in range(csym):
                        iss, val, bits = struct.unpack_from(">III", d, sym_off + (isym_base + i) * 12)
                        if bits >> 26 in (6, 14):  # stProc, stStaticProc
                            out.setdefault(cstr(d, ss_off + iss_base + iss), val)
        _mdebug[obj] = out
    return _mdebug[obj]


def text_base(seg, obj):
    """Link-map .text address of one object of SEG."""
    if seg not in _text:
        path, out = os.path.join(ROOT, "build", "dk64.us.map" if seg == "boot" else f"{seg}.map"), {}
        if os.path.exists(path):
            for line in open(path):
                m = re.match(r"\s*\.text\s+0x([0-9a-f]+)\s+0x[0-9a-f]+\s+(\S+\.o)\s*$", line)
                if m:
                    out.setdefault(m.group(2), int(m.group(1), 16))
        _text[seg] = out
    return _text[seg].get(obj)


def resolve_vram(seg, name, src):
    """VRAM of function NAME defined in SRC: symbol file / asm / link map (tools/ledger.py), else the
    build ELF symbol table, else the object's .mdebug procedure plus its link-map .text address."""
    v = ledger.vram_of(seg, name)
    if v is not None:
        return v
    cands = elf_funcs(seg).get(name, [])
    stem = os.path.splitext(os.path.basename(src))[0]
    mine = [x for x, f in cands if f == stem]
    if len(mine) == 1:
        return mine[0]
    if len(cands) == 1:
        return cands[0][0]
    obj = "build/" + src[:-2] + ".o"
    off, base = mdebug_procs(obj).get(name), text_base(seg, obj)
    return None if off is None or base is None else base + off


def names_at(seg, vram):
    return [ledger.name_of(seg, vram)] + [n for n, c in elf_funcs(seg).items() if any(v == vram for v, _ in c)]


def require_resolved(analyses):
    bad = [(an["path"], n) for an in analyses for n in an["unresolved"]]
    for p, n in bad:
        print(f"quality: cannot resolve {n} ({p}): not in the symbol file, asm, link map or build ELF",
              file=sys.stderr)
    if bad:
        sys.exit(1)


# ---------------------------------------------------------------- sites

def split_comment(line):
    i = line.find("//")
    return (line, "") if i < 0 else (line[:i], line[i:])


def dead_store(line):
    code, cm = split_comment(line)
    return bool(STORE.match(line)) and code.count(";") == 1 and "while" not in code and bool(DEAD_WORD.search(cm))


def kind_of(line):
    """Kind of a tagged (`// FAKE` / `// PROTO:`) line, from its comment text and code."""
    code, cm = split_comment(line)
    if "callee prototype steer" in cm:
        return "proto-steer"
    if "implicit declaration steer" in cm:
        return "implicit-steer"
    if "// PROTO:" in line:
        return "proto-type"
    for kind, rx in (("dead-if", DEAD_IF), ("volatile", re.compile("volatile")), ("noop-arith", NOOP),
                     ("do-while0", DO_WHILE), ("comma", re.compile(r"\(0, ")), ("punned-cast", PUN)):
        if rx.search(code):
            return kind
    return "dead-store" if dead_store(line) else "other"


def norm(lines):
    return re.sub(r"\s+", "", ledger.COMMENT.sub("", "\n".join(lines)))


def parked_lines(lines):
    """Line indexes inside the NON_MATCHING side of `#ifdef NON_MATCHING` / `#ifndef` conditionals."""
    out, stack = set(), []
    for i, l in enumerate(lines):
        m = re.match(r"\s*#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)", l)
        if m:
            d, rest = m.groups()
            if d in ("ifdef", "ifndef", "if"):
                nm = "NON_MATCHING" in rest
                neg = d == "ifndef" or "!" in rest
                stack.append(("live" if neg else "park") if nm else "other")
            elif d in ("else", "elif") and stack:
                stack[-1] = {"park": "live", "live": "park"}.get(stack[-1], "other")
            elif d == "endif" and stack:
                stack.pop()
            continue
        if "park" in stack:
            out.add(i)
    return out


def do_pair(lines, i):
    """(open, close) line indexes of the `do {` ... `} while (0);` wrapper tagged at line I, or None."""
    code = split_comment(lines[i])[0]
    if DO_CLOSE.match(code):
        depth = 0
        for j in range(i - 1, -1, -1):
            t = split_comment(lines[j])[0]
            depth += t.count("}") - t.count("{")
            if DO_OPEN.match(t) and depth < 0:
                return (j, i)
    elif DO_OPEN.match(code):
        depth = 1
        for j in range(i + 1, len(lines)):
            t = split_comment(lines[j])[0]
            if DO_CLOSE.match(t) and depth == 1:
                return (i, j)
            depth += t.count("{") - t.count("}")
    return None


def owner_of(i, code, defs, lines):
    """Index into DEFS of the function a file-scope site at line index I serves: the first later
    definition whose body names the declared symbol, else any that does, else the next one."""
    m = (re.search(r"PROTO_SKIP_(\w+)", code) or re.search(r"(\w+)\s*\(", code)
         or re.search(r"(\w+)\s*(?:\[[^\]]*\]\s*)*[=;]", code))
    if m:
        rx = re.compile(rf"\b{re.escape(m.group(1))}\b")
        use = [k for k, d in enumerate(defs) if rx.search("\n".join(lines[d["line"]:d["end"]]))]
        after = [k for k in use if d_after(defs[k], i)]
        if after or use:
            return (after or use)[0]
    nxt = [k for k, d in enumerate(defs) if d_after(d, i)]
    return nxt[0] if nxt else (len(defs) - 1 if defs else None)


def d_after(d, i):
    return d["line"] - 1 >= i


_htext = {}


def header_text(p):
    if p not in _htext:
        _htext[p] = open(os.path.join(ROOT, p), encoding="utf-8", errors="replace").read()
    return _htext[p]


def included(text, here, hdrs=None):
    """Sorted include/ headers TEXT quote-includes, transitively. HDRS: {header path: text, or None
    when absent} overriding the working tree (the headers at another rev)."""
    hdrs, seen = hdrs or {}, set()

    def visit(text, here):
        for inc in INCLUDE.findall(text):
            for d in (here, *HDR_DIRS):
                p = os.path.normpath(os.path.join(d, inc))
                if hdrs[p] is not None if p in hdrs else os.path.isfile(os.path.join(ROOT, p)):
                    break
            else:
                continue
            if p.startswith("include" + os.sep) and p not in seen:
                seen.add(p)
                visit(hdrs[p] if p in hdrs else header_text(p), os.path.dirname(p))

    visit(text, here)
    return sorted(seen)


def fp_hdr(text, here, hdrs=None):
    """sha1 of every include/ header TEXT quote-includes, transitively (HDRS: as `included`)."""
    hdrs = hdrs or {}
    h = hashlib.sha1()
    for p in included(text, here, hdrs):
        h.update(f"{p}\0{hdrs[p] if p in hdrs else header_text(p)}\0".encode("utf-8", "replace"))
    return h.hexdigest()[:16]


def rev_headers(rev):
    """{path: text at REV, or None when absent there} of every include/ file (and src/ *.h) that differs
    between REV and the working tree: `analyze`'s HDRS for REV's text."""
    hdrs = {}
    for p in ledger.git("diff", "--name-only", rev, "--", "include", ":(glob)src/**/*.h").split():
        r = subprocess.run(["git", "show", f"{rev}:{p}"], cwd=ROOT, capture_output=True, text=True)
        hdrs[p] = r.stdout if r.returncode == 0 else None
    return hdrs


def text_metrics(text):
    c = collections.Counter()
    for line in text.split("\n"):
        if "// FAKE" in line:
            c["FAKE"] += 1
            c["FAKE " + kind_of(line)] += 1
        if "// LAYOUT" in line:
            c["LAYOUT"] += 1
        if clint.ORIG_OK.search(line):
            c["ORIG"] += 1
        if "// PROTO:" in line:
            c["proto-type"] += 1
    c["goto"] = len(GOTO.findall(ledger.COMMENT.sub("", text)))
    return c


def analyze(path, seg, text=None, uninit=False, src=None, hdrs=None, keep=False, warns=None, warnings=True,
            rev=None):
    """dict(path, seg, fp_hdr, functions=[dict(name, static, line, end, seg, vram, fp_local, fp_hdr,
    fp_hdr2 (`Scope.fp_hdr2`: only the include/ declarations the function reaches),
    metrics, int_locals, sites=[dict(key, kind, line, lines, tagged, code, name)])], unresolved,
    uninit=[(func, var, line)], text=text metrics, errors) of one C file (TEXT: its content, e.g. at a
    rev; SRC: the src file PATH is a copy of, for function identity; HDRS: {include/ path: text or
    None} overriding the working-tree headers, as `included`; KEEP adds tu, scope, toks (the file's
    own tokens) and by_line). REV: TEXT is REV's, analysed with REV's headers (HDRS default
    `rev_headers(REV)`) and compiled against them. WARNINGS (not with HDRS unless REV is given): the
    IDO cfe warnings of the matching compile (`cwarn.collect`, or WARNS when given) become `warning`
    sites (plus `warning`: "<code> <msg>") and `warnings` counts them all (header paths included; None
    without WARNINGS). A failed compile raises `cwarn.CompileError`."""
    path = rel(path)
    full = os.path.join(ROOT, path)
    if rev is not None and hdrs is None:
        hdrs = rev_headers(rev)
    if warnings and (hdrs is None or rev is not None):
        if warns is None:
            try:  # REV's headers equal to the working tree's: the shared working-tree cache
                warns = cwarn.collect([(path, text, src)], rev=rev if hdrs else None)[0]
            except cwarn.CompileError as ex:
                ex.rev = ex.rev or rev
                raise
    else:
        warns = None
    if text is None:
        text = open(full, encoding="utf-8", errors="replace").read()
    lines = text.split("\n")
    args = clint.clang_args(warnings=True) if uninit else None
    over = [(os.path.join(ROOT, p), t) for p, t in (hdrs or {}).items() if t is not None]
    tu = clint.parse(path, args=args, unsaved=[(full, text), *over])
    defs = []
    for name, st, d, _, s, e, c in clint.functions(tu, path):
        if not d:
            continue
        m, hits = clint.function_metrics(c, lines)
        locs = [(x.spelling, x.location.line) for x in clint.walk(c) if x.kind == CursorKind.VAR_DECL
                and x.storage_class != StorageClass.STATIC and x.type.get_canonical().kind in INT_KINDS]
        defs.append(dict(name=name, static=st, line=s, end=e, seg=seg, metrics=m, untagged=hits,
                         int_locals=locs, sites=[]))
    inside = {i: k for k, d in enumerate(defs) for i in range(d["line"] - 1, d["end"])}
    top = "\n".join(l for i, l in enumerate(lines) if i not in inside)
    hdr = fp_hdr(text, os.path.dirname(path), hdrs)
    toks = file_tokens(tu, path)
    scope, by_line = Scope(tu), idents_by_line(toks)
    raw, park, paired = collections.defaultdict(list), parked_lines(lines), set()
    for i, l in enumerate(lines):
        hack_tag = "// FAKE" in l or "// PROTO:" in l or ("// ORIG" in l and not clint.ORIG_OK.search(l))
        if not hack_tag or i in park or i in paired:
            continue
        code = split_comment(l)[0]
        if GOTO.search(code):
            continue  # gotos are AST sites
        kind, idx = kind_of(l), (i,)
        if kind == "do-while0":
            idx = do_pair(lines, i) or idx
            paired.update(idx)
        k = inside.get(i)
        if k is None:
            k = owner_of(i, code, defs, lines)
        if k is not None:
            raw[k].append((idx, kind, True, None))
    for w in warns or ():
        if w["path"] != path:
            continue  # a header's warning: counted, no site
        i = w["line"] - 1
        k = inside.get(i)
        if k is None:
            k = owner_of(i, split_comment(lines[i])[0], defs, lines)
        if k is not None:
            raw[k].append(((i,), "warning", False, f"{w['code']} {w['msg']}"))
    for k, d in enumerate(defs):
        on_tagged = {j for idx, _, t, _ in raw[k] if t for j in idx}  # an ORIG line without an offset
        raw[k] += [((line - 1,), kind, False, None) for line, kind, _ in d.pop("untagged") if line - 1 not in on_tagged]
    unresolved = []
    for k, d in enumerate(defs):
        v = d["vram"] = resolve_vram(seg, d["name"], src or path)
        if v is None:
            unresolved.append(d["name"])
        d["fp_local"] = ledger.sha1("\n".join(lines[d["line"] - 1:d["end"]]) + "\0" + top)[:16]
        d["fp_hdr"] = hdr
        d["fp_hdr2"] = scope.fp_hdr2(body_names(by_line, d), hdr)
        seen = collections.Counter()
        for idx, kind, tagged, warning in sorted(raw[k], key=lambda r: (r[0][0], not r[2])):
            if warning is not None:
                h = ledger.sha1(f"{warning.split(' ', 1)[0]}\0" + norm(lines[j] for j in idx))[:6]
            else:
                h = ledger.sha1(norm(lines[j] for j in idx))[:6]
                if not tagged:
                    h = "u" + h[1:]
            seen[(kind, h)] += 1
            n = seen[(kind, h)]
            key = None if v is None else f"{seg}:{v:08X}:{kind}:{h}" + (f"#{n}" if n > 1 else "")
            d["sites"].append(dict(key=key, kind=kind, line=idx[0] + 1, lines=list(idx), tagged=tagged,
                                   code=lines[idx[0]].strip(), name=d["name"]))
            if warning is not None:
                d["sites"][-1]["warning"] = warning
    unin = [(f, var, line) for (f, var), line in clint.uninit(path, tu).items()] if uninit else []
    out = dict(path=path, seg=seg, fp_hdr=hdr, functions=defs, unresolved=unresolved, uninit=unin,
               text=dict(text_metrics(text)), errors=tu.diagnostics_errors,
               warnings=None if warns is None else len(warns))
    if keep:
        out.update(tu=tu, scope=scope, toks=toks, by_line=by_line)
    return out


def _analyze_job(job):
    return analyze(*job)


def analyze_many(paths, uninit=False):
    warns = cwarn.collect([(p, None, None) for p in paths])
    jobs = [(p, seg_of(p), None, uninit, None, None, False, w) for p, w in zip(paths, warns)]
    if len(jobs) <= 2:
        return [_analyze_job(j) for j in jobs]
    with multiprocessing.get_context("spawn").Pool(min(os.cpu_count() or 4, len(jobs))) as pool:
        return pool.map(_analyze_job, jobs, chunksize=2)


# ---------------------------------------------------------------- ledger and exhaustion

def _shard(e):
    """Ledger file for event e: units.jsonl, or <seg>/<VRAM top 16 bits>.jsonl, so every event of one
    function lands in one shard in append order (shards stay far below GitHub's 50 MB warning)."""
    if e.get("type") == "unit":
        return os.path.join(LEDGER, "units.jsonl")
    return os.path.join(LEDGER, e["seg"], e["vram"][:4] + ".jsonl")


def load_events():
    """Unit events, then every shard in path order; each function's events keep ledger order."""
    if not os.path.isdir(LEDGER):
        return []
    units = os.path.join(LEDGER, "units.jsonl")
    paths = ([units] if os.path.exists(units) else []) + sorted(glob.glob(os.path.join(LEDGER, "*", "*.jsonl")))
    return [json.loads(line) for p in paths for line in open(p) if line.strip()]


def index_events(events):
    """(site key -> events, (seg, VRAM8) -> function-level events), each in ledger order."""
    by_site, by_func = collections.defaultdict(list), collections.defaultdict(list)
    for e in events:
        if e.get("type") == "quality":
            (by_site[e["site"]] if e["site"] else by_func[(e["seg"], e["vram"])]).append(e)
    return by_site, by_func


def append_events(events):
    shards = collections.defaultdict(list)
    for e in events:
        shards[_shard(e)].append(e)
    for path, es in shards.items():
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "a") as f:
            f.writelines(json.dumps(e) + "\n" for e in es)


def unit_events(unit, events):
    if any(e.get("type") == "unit" and e.get("unit") == unit for e in events):
        return []
    return [{"type": "unit", "t": ledger.now(), "unit": unit, "commit": ledger.git("rev-parse", "HEAD").strip()}]


def event(unit, agent, fn, site, method, outcome, quirks=(), seconds=None, base=None, best=None, commit=None,
          note=None, model=None, new=None):
    return {"type": "quality", "t": ledger.now(), "unit": unit, "agent": agent, "seg": fn["seg"],
            "vram": f"{fn['vram']:08X}", "name": fn["name"], "file": fn["file"],
            "site": site["key"] if site else None, "kind": site["kind"] if site else None, "method": method,
            "outcome": outcome, "fp_local": fn["fp_local"], "fp_hdr": fn["fp_hdr"],
            "fp_hdr2": fn.get("fp_hdr2"), "quirks": list(quirks),
            "seconds": seconds, "base": base, "best": best, "commit": commit, "note": note,
            "model": model, "new": new}


_know = {}


def knowledge_after(name, t, unit=None):
    """Whether a knowledge/ido file committed after T names NAME (its current or func_ADDR name),
    entries filed by UNIT (frontmatter `unit`) aside: the event's own unit derived them from runs
    like it, so it already had the finding. Note text never stales: its top-8 hits matched
    unrelated broad entries and re-ran the same attempts."""
    if "times" not in _know:
        _know["times"] = ledger.knowledge_times()
        _know["newest"] = max((v for v in _know["times"].values() if v), default="")
    if _know["newest"] <= t:
        return False
    if "corpus" not in _know:
        _know["corpus"] = quirks.load()
    key = ("name", name)
    if key not in _know:
        _know[key] = ledger.related_knowledge(_know["corpus"], name, None)
    new = {p for p in _know[key] if (_know["times"].get(p) or "") > t}
    return bool(new) and not new <= own_knowledge(name, unit)


def own_knowledge(name, unit):
    """Repo-relative paths of the entries filed by UNIT that name NAME (its current or func_ADDR
    name, as `quirks.py func` matches)."""
    if not unit:
        return set()
    if "units" not in _know:
        _know["units"] = collections.defaultdict(list)
        for e in _know["corpus"].entries.values():
            if e.unit:
                _know["units"][e.unit].append(e)
    if not _know["units"].get(unit):
        return set()
    key = ("own", name, unit)
    if key not in _know:
        aliases = quirks.function_aliases(name, ledger.ROOT)
        _know[key] = {os.path.relpath(str(e.path), ledger.ROOT) for e in _know["units"][unit]
                      if aliases & set(e.functions)}
    return _know[key]


def hdr_fresh(e, now_fp):
    """Header part of an automatic method's freshness: the event's per-function `fp_hdr2` when
    both sides have one, else the whole-header `fp_hdr` (events recorded before fp_hdr2)."""
    if e.get("fp_hdr2") is not None and len(now_fp) > 2 and now_fp[2] is not None:
        return e["fp_hdr2"] == now_fp[2]
    return e["fp_hdr"] == now_fp[1]


def origin_unit(e, evs=()):
    """The unit whose agent produced E. A carried event (agent `carry`) holds an earlier result under
    the carrying unit: its producer is the uncarried event of the same method and time in EVS (None
    when that is not among them, e.g. a re-keyed site)."""
    if e.get("agent") != "carry":
        return e.get("unit")
    return next((x.get("unit") for x in evs
                 if x.get("agent") != "carry" and x["method"] == e["method"] and x["t"] == e["t"]), None)


def fresh(e, now_fp, name, evs=()):
    """NOW_FP = (fp_local, fp_hdr[, fp_hdr2]). Knowledge stales an agent method only through the
    function's name, never through its note (a retry must name what is new instead: `record`'s
    `new=` gate). An entry filed by the unit that produced the event (`origin_unit` over EVS) and
    naming the function does not stale it (`own_knowledge`)."""
    if e["fp_local"] != now_fp[0]:
        return False
    if e["method"] in AUTO:
        return hdr_fresh(e, now_fp)
    return not knowledge_after(name or e["name"], e["t"], origin_unit(e, evs))


def mark(evs, method, now_fp, name):
    """('✓' | 'stale' | '—', newest event of METHOD or None, whether it is fresh). Newest by `t`
    (ties: ledger order): carried events keep their original time, so one appended after a later
    agent event must not win."""
    e = None
    for x in evs:
        if x["method"] == method and (e is None or x["t"] >= e["t"]):
            e = x
    if e is None:
        return "—", None, False
    if not fresh(e, now_fp, name, evs):
        return "stale", e, False
    return ("—" if e["outcome"] == "blocked" else "✓"), e, True


def ladder(site, events, now_fp):
    """dict(done, next, marks={method: mark}, kept) of one site."""
    evs = [e for e in events if e.get("site") == site["key"]]
    kind, name = site["kind"], site.get("name")
    marks, last = {}, {}
    for m in dict.fromkeys([*LADDER[kind], *(e["method"] for e in evs)]):
        marks[m], last[m], _ = mark(evs, m, now_fp, name)
    term = {"dead-if": "classify", "goto": "goto-hand", "warning": "retype"}.get(kind)
    kept = bool(term) and marks.get(term) == "✓" and last[term]["outcome"] == "kept"
    shown = {m: marks[m] for m in LADDER[kind]}
    if kind == "proto-type":
        return dict(done=False, next="views", marks=shown, kept=False)
    if any(marks[m] == "✓" and last[m]["outcome"] == "hit" for m in marks):
        return dict(done=False, next="apply", marks=shown, kept=kept)
    need = (LADDER[kind][:3] if kind == "dead-if" else (term,)) if kept else LADDER[kind]
    missing = [m for m in need if marks[m] != "✓"]
    return dict(done=not missing, next=missing[0] if missing else None, marks=shown, kept=kept)


def exhausted(site, events, now_fp):
    """(done, next method or None, {method: '✓'|'stale'|'—'}) of SITE under EVENTS at fingerprints
    NOW_FP = (fp_local, fp_hdr)."""
    r = ladder(site, events, now_fp)
    return r["done"], r["next"], r["marks"]


def function_state(fn, by_site, by_func):
    """dict(done, next, review, reconstruct, sites=[(site, ladder)], open=[(site, ladder)], waived)."""
    fp, name = (fn["fp_local"], fn["fp_hdr"], fn.get("fp_hdr2")), fn["name"]
    fevs = by_func.get((fn["seg"], f"{fn['vram']:08X}"), [])
    review = mark(fevs, "review", fp, name)[0]
    _, ve, vf = mark(fevs, "views", fp, name)
    waived = vf and ve["outcome"] == "blocked" and bool(ve["note"])
    sites = [(s, ladder(s, by_site.get(s["key"], []), fp)) for s in fn["sites"]]
    open_ = [(s, r) for s, r in sites if not r["done"] and not (s["kind"] == "proto-type" and waived)]
    rec = (mark(fevs, "reconstruct", fp, name)[0]
           if sum(not r["kept"] for s, r in sites if s["kind"] != "warning") >= 3 else None)
    nxt = ("review" if review != "✓" else open_[0][1]["next"] if open_
           else "reconstruct" if rec not in (None, "✓") else None)
    return dict(done=nxt is None, next=nxt, review=review, reconstruct=rec, sites=sites, open=open_, waived=waived)


# ---------------------------------------------------------------- sweep

_seq = itertools.count(1)
_lock = threading.Lock()
_base_uninit = {}


def job_dir():
    d = os.path.join(SCRATCH, "sweep", f"{os.getpid()}_{next(_seq)}")
    os.makedirs(d, exist_ok=True)
    return d


def cleanup(d, copy):
    shutil.rmtree(d, ignore_errors=True)
    obj = os.path.join(ROOT, "build", ".scratch", copy.replace("/", "_") + ".o")
    if os.path.exists(obj):
        os.remove(obj)


def fdiff(copy, src):
    # --reloc-ok: a copy reaching the same addresses through other symbol names (split splat
    # labels) is a match: same instructions, same linked ROM (`RELOC-EQUIV OK`, exit 0)
    return subprocess.run(["tools/fdiff.sh", "--reloc-ok", copy, src], cwd=ROOT, capture_output=True).returncode


def new_uninit(copy, src):
    with _lock:  # one libclang user at a time
        if src not in _base_uninit:
            _base_uninit[src] = set(clint.uninit(src))
        return set(clint.uninit(copy)) - _base_uninit[src]


def check(text, path, src, uninit=True):
    """Whole-object match of TEXT as a copy of PATH (fdiff exit 0) without a new uninitialised read."""
    d = job_dir()
    copy = rel(os.path.join(d, os.path.basename(path)))
    open(os.path.join(ROOT, copy), "w").write(text)
    try:
        return fdiff(copy, src) == 0 and not (uninit and new_uninit(copy, src))
    finally:
        cleanup(d, copy)


def cond_check(text, body, path, src, func):
    d = job_dir()
    bf = rel(os.path.join(d, "body.c"))
    open(os.path.join(ROOT, bf), "w").write(body)
    try:
        r = subprocess.run(["tools/dk", "python3", "tools/deadsweep.py", "score", path, src, func, "--body", bf],
                           cwd=ROOT, capture_output=True, text=True)
    finally:
        shutil.rmtree(d, ignore_errors=True)
    m = re.search(r" full=(\d+) ", r.stdout)
    return bool(m) and m.group(1) == "0" and check(text, path, src)


def recipe_check(text, path, src, func):
    """Text of the first tools/variants.py recipe variant of FUNC in TEXT (a copy of PATH) that passes
    check(), or None."""
    d = job_dir()
    copy = rel(os.path.join(d, os.path.basename(path)))
    open(os.path.join(ROOT, copy), "w").write(text)
    js = os.path.join(d, "v.json")
    try:
        subprocess.run(["tools/dk", "python3", "tools/variants.py", "scan", copy, src, func, "--max", "120", "-j", "2",
                        "--out", rel(os.path.join(d, "zeros")), "--json", rel(js)],
                       cwd=ROOT, capture_output=True, text=True)
        rows = json.load(open(js)) if os.path.exists(js) else []
        for row in rows:
            if row.get("path"):
                t = open(os.path.join(ROOT, row["path"]), encoding="utf-8", errors="replace").read()
                if check(t, path, src):
                    return t
        return None
    finally:
        cleanup(d, copy)


def apply(lines, edits, lo=0, hi=None):
    """Lines LO..HI joined, with EDITS {index: replacement or None (delete)}."""
    return "\n".join(edits.get(i, l) for i, l in enumerate(lines[:hi]) if i >= lo and edits.get(i, l) is not None)


def untag(line):
    code, cm = split_comment(line)
    return code.rstrip() if "FAKE" in cm else line


def remove_edit(site, lines, fn):
    """{line index: replacement or None} deleting / neutralising SITE, or None when it has no removal."""
    idx = site["lines"]
    if not all(fn["line"] - 1 <= i < fn["end"] for i in idx):
        return None
    l = lines[idx[0]]
    if site["kind"] == "do-while0":
        if len(idx) == 2:
            return {i: None for i in idx}
        return {idx[0]: None} if DO_LINE.match(split_comment(l)[0]) else None
    if site["kind"] == "volatile" and "volatile " in split_comment(l)[0]:
        return {idx[0]: untag(l.replace("volatile ", "", 1))}
    if site["kind"] == "dead-if" and GUARD.match(l):
        return {idx[0]: None}
    if site["tagged"] and (VOID.match(l) or dead_store(l)):
        return {idx[0]: None}
    return None


def combos(items):
    n, out, seen = len(items), [tuple(items)], set()
    if n > 1:
        out += [(x,) for x in items]
    if n > 2:
        out += list(itertools.combinations(items, 2))
    if 3 <= n <= 6:
        out += list(itertools.combinations(items, 3))
    for c in out:
        k = frozenset(s["key"] for s, _ in c)
        if k not in seen:
            seen.add(k)
            yield c


def plain_rewrites(site, lines):
    """Whole-file texts with SITE's line rewritten by each PLAIN rule that changes it (its `// FAKE`
    comment dropped, any other comment kept)."""
    i = site["lines"][0]
    code, cm = split_comment(lines[i])
    tail = "" if "FAKE" in cm or not cm else " " + cm
    return [apply(lines, {i: new.rstrip() + tail}) for rx, rep in PLAIN for new in [rx.sub(rep, code)] if new != code]


def merged(group):
    out = {}
    for _, e in group:
        out.update(e)
    return out


def plan_file(an, path, src, pool):
    """Submit every sweep candidate of one file: dict(an, path, src, jobs=[(method, keys, future or
    classify futures, variant text)], tried={(key, method): note of a method run without a hit})."""
    lines = open(os.path.join(ROOT, path), encoding="utf-8", errors="replace").read().split("\n")
    jobs, tried = [], {}

    def submit(method, group, fn, text, *args):
        jobs.append((method, [s["key"] for s, _ in group], pool.submit(fn, text, *args), text))

    for fn in an["functions"]:
        sites = [s for s in fn["sites"] if s["kind"] != "warning"]  # retype is an agent method
        if not sites:
            continue
        rem = [(s, e) for s in sites if (e := remove_edit(s, lines, fn)) is not None]
        for c in combos(rem) if rem else ():
            submit("remove", c, check, apply(lines, merged(c)), path, src)
        flips = 0
        for rs in ([rem] + ([[x] for x in rem] if len(rem) > 1 else [])) if rem else ():
            base = merged(rs)
            for i in range(fn["line"] - 1, fn["end"]):
                if i in base or "// FAKE" in lines[i]:
                    continue
                for rx, rep in FLIPS:
                    if rx.search(lines[i]):
                        ed = {**base, i: rx.sub(rep, lines[i], count=1)}
                        submit("cond", rs, cond_check, apply(lines, ed), apply(lines, ed, fn["line"] - 1, fn["end"]),
                               path, src, fn["name"])
                        flips += 1
        for s, _ in rem:
            tried[(s["key"], "remove")] = None
            tried[(s["key"], "cond")] = None if flips else "no flips"
        removable = {s["key"] for s, _ in rem}
        for s in sites:  # no edit to try still records the rung: else it stays stale after a header change
            if "remove" in LADDER[s["kind"]] and s["key"] not in removable:
                tried[(s["key"], "remove")] = tried[(s["key"], "cond")] = "no removal"
            if s["kind"] == "dead-if" and not GUARD.match(lines[s["lines"][0]]):
                tried[(s["key"], "classify")] = "no guard"
        first_plain = {}  # site key -> (site, its first plain rewrite): a recipe base
        for s in sites:
            i = s["lines"][0]
            if s["kind"] in PLAIN_KINDS:
                texts = plain_rewrites(s, lines)
                for text in texts:
                    submit("plain", [(s, None)], check, text, path, src)
                if texts:
                    first_plain[s["key"]] = (s, texts[0])
                tried[(s["key"], "plain")] = None if texts else "no rewrite"
            m = GUARD.match(lines[i])
            if s["kind"] == "dead-if" and m:
                cands = [v for v, ln in fn["int_locals"] if ln < s["line"] and not re.search(rf"\b{re.escape(v)}\b", m.group(2))]
                cands = list(dict.fromkeys(cands))[:3]
                tried[(s["key"], "classify")] = None if cands else "no local"
                if cands:
                    futs = [pool.submit(check, apply(lines, {i: f"{m.group(1)}if ({v}) {{}}"}), path, src, False)
                            for v in cands]
                    jobs.append(("classify", [s["key"]], futs, None))
        # recipe: natural respellings of the function around each removal / plain rewrite
        bases = []
        if rem:
            bases.append(([s for s, _ in rem], apply(lines, merged(rem))))
            if len(rem) > 1:
                bases += [([x[0]], apply(lines, merged([x]))) for x in rem]
        bases += [([s], text) for s, text in first_plain.values()]
        for group, text in bases:
            submit("recipe", [(s, None) for s in group], recipe_check, text, path, src, fn["name"])
        based = {s["key"] for group, _ in bases for s in group}
        for s in sites:
            if "recipe" in LADDER[s["kind"]]:
                tried[(s["key"], "recipe")] = None if s["key"] in based else "no removal"
    return dict(an=an, path=path, src=src, jobs=jobs, tried=tried)


def write_hit(seg, src, text):
    stem = os.path.splitext(os.path.basename(src))[0]
    d = os.path.join(SCRATCH, "hits")
    os.makedirs(d, exist_ok=True)
    for n in itertools.count(1):
        p = os.path.join(d, f"{seg}_{stem}_{n}.c")
        if not os.path.exists(p):
            open(p, "w").write(text)
            return rel(p)


def finish(plan):
    """({(key, method): [outcome, note]}, [(keys, method, hit text)], checks run) once PLAN's futures are done."""
    out = {k: ["nohit", note] for k, note in plan["tried"].items()}
    hits, checks = [], 0
    for method, keys, fut, text in plan["jobs"]:
        if method == "classify":
            rs = [f.result() for f in fut]
            checks += len(rs)
            out[(keys[0], method)] = ["kept", "class 1"] if any(rs) else ["nohit", "class 2"]
            continue
        checks += 1
        r = fut.result()
        if r:
            hits.append((keys, method, r if method == "recipe" else text))  # recipe: the matching variant
            for k in keys:
                out[(k, method)] = ["hit", None]
    return out, hits, checks


def cmd_sweep(a):
    if a.copy_of and len(a.files) != 1:
        sys.exit("quality: --copy-of takes exactly one copy")
    if a.record and not a.unit:
        sys.exit("quality: --record needs --unit")
    t0, plans, events = time.time(), [], []
    nchecks = nhits = 0
    with ThreadPoolExecutor(a.j) as pool:
        for f in a.files:
            path = rel(f)
            src = rel(a.copy_of) if a.copy_of else path
            an = analyze(path, seg_of(src), src=src)
            require_resolved([an])
            for s in (s for fn in an["functions"] for s in fn["sites"] if s["kind"] == "warning"):
                print(f"WARN {s['key']} line {s['line']} [W{s['warning']}]")  # keys of the copy's warning sites
            if not any(s["kind"] != "warning" for fn in an["functions"] for s in fn["sites"]):
                print(f"{path}: no sites")
                continue
            rc = fdiff(path, src)
            if rc != 0:
                print(f"SKIP {path}: does not match before the sweep (fdiff exit {rc})")
                continue
            plans.append(plan_file(an, path, src, pool))
        for p in plans:
            out, hits, checks = finish(p)
            an = p["an"]
            sites = {s["key"]: (fn, s) for fn in an["functions"] for s in fn["sites"] if s["kind"] != "warning"}
            print(f"{p['path']}: {len(sites)} sites, {checks} checks, {len(hits)} hits")
            for keys, method, text in hits:
                hp = write_hit(an["seg"], p["src"], text)
                print(f"HIT {','.join(keys)} {method} {hp}")
            for (key, method), (outcome, note) in sorted(out.items(), key=lambda x: (sites[x[0][0]][1]["line"], x[0])):
                print(f"  {key} {method} {outcome}" + (f" ({note})" if note else ""))
                fn, s = sites[key]
                events.append(event(a.unit, "sweep", dict(fn, file=p["path"]), s, method, outcome, note=note))
            nchecks += checks
            nhits += len(hits)
    print(f"sweep: {len(plans)} files, {nchecks} checks, {nhits} hits in {time.time() - t0:.0f}s")
    if a.record:
        ev = unit_events(a.unit, load_events()) + events
        append_events(ev)
        print(f"recorded {len(events)} events to {rel(LEDGER)}")


# ---------------------------------------------------------------- record

def parse_line(line):
    toks = shlex.split(line)
    if len(toks) < 3:
        raise ValueError("need <key> <method> <outcome> [field=value...]")
    opts = dict(quirks=[], seconds=None, base=None, best=None, commit=None, note=None, new=None)
    for t in toks[3:]:
        k, eq, v = t.partition("=")
        if not eq or k not in opts:
            raise ValueError(f"unknown field {t!r}")
        if k == "quirks":
            opts[k] = [q for q in v.split(",") if q]
        elif k in ("seconds", "base", "best"):
            if not re.fullmatch(r"\d+", v):
                raise ValueError(f"{k} must be an integer")
            opts[k] = int(v)
        else:
            opts[k] = v
    return toks[0], toks[1], toks[2], opts


def validate(key, method, outcome, o):
    """Error message for one record line's method/outcome/evidence rules, or None."""
    fk, sk = FUNC_KEY.match(key), SITE_KEY.match(key)
    note = o["note"] or ""
    if not fk and not sk:
        return f"bad key {key!r} (<seg>:<VRAM8>:<kind>:<hash>[#n] or func:<seg>:<name>)"
    if sk and sk.group(3) not in KINDS:
        return f"unknown site kind {sk.group(3)!r}"
    if method not in METHODS:
        return f"unknown method {method!r} (one of {' '.join(METHODS)})"
    if outcome not in OUTCOMES:
        return f"unknown outcome {outcome!r} (one of {' '.join(OUTCOMES)})"
    if method in FUNC_ONLY and not fk:
        return f"{method} is function-level: key func:<seg>:<name>"
    warn_site = bool(sk) and sk.group(3) == "warning"
    if warn_site and method != "retype":
        return "warning sites take only retype"
    if method == "retype":
        if not warn_site:
            return "retype needs a warning site key"
        if outcome not in ("fixed", "kept", "blocked"):
            return "retype outcome is fixed, kept or blocked"
        if outcome == "kept" and not re.search(r"\bfdiff=[13]\b", note):
            return "retype kept needs note with fdiff=<1|3> of the attempted fix"
        if outcome == "blocked" and not note.strip():
            return "retype blocked needs a note naming the missing header/owner change"
    if fk and method not in FUNC_ONLY and method != "reconstruct":
        return f"{method} needs a site key"
    if outcome == "kept" and method != "retype" and not ((method == "classify" and "class 1" in note) or
                                                         (method == "goto-hand" and "Q0591" in note)):
        return "kept is only for classify (note \"class 1\"), goto-hand (note citing Q0591) or retype"
    if method == "diagnose" and not o["quirks"]:
        return "diagnose needs quirks=Q1,Q2"
    if method == "permute" and (o["base"] is None or o["best"] is None
                                or ((o["seconds"] or 0) < 600 and o["best"] != 0)):
        return "permute needs base= and best=, and seconds>=600 unless best=0 (a zero score settles it)"
    if method == "review":
        if outcome not in ("fixed", "nohit", "blocked"):
            return "review outcome is fixed, nohit or blocked"
        missing = [c + "=" for c in CHECKLIST if not re.search(rf"(?<![\w-]){c}=", note)]
        if missing:
            return "review note lacks " + " ".join(missing)
    return None


class Resolver:
    """Finds the function (and site) a record key names in the C files at HEAD, else at BASE."""

    def __init__(self, base):
        self.revs = ["HEAD"] + ([base] if base else [])
        self.cache, self.hdrs = {}, {}

    def analysis(self, path, seg, rev):
        if (path, rev) not in self.cache:
            text = subprocess.run(["git", "show", f"{rev}:{path}"], cwd=ROOT, capture_output=True, text=True).stdout
            if rev == "HEAD":  # HEAD's text with the working-tree headers, as sweeps and status see it
                self.cache[(path, rev)] = analyze(path, seg, text=text)
            else:
                if rev not in self.hdrs:
                    self.hdrs[rev] = rev_headers(rev)
                self.cache[(path, rev)] = analyze(path, seg, text=text, hdrs=self.hdrs[rev], rev=rev)
        return self.cache[(path, rev)]

    def files(self, seg, names, rev):
        r = subprocess.run(["git", "grep", "-l", "-w", "-F", *sum((["-e", n] for n in names), []), rev, "--",
                            f"src/{seg}"], cwd=ROOT, capture_output=True, text=True)
        paths = [line.split(":", 1)[1] for line in r.stdout.splitlines()]
        return [p for p in paths if os.path.dirname(p) == f"src/{seg}" and p.endswith(".c")]

    def find(self, key):
        """(fn with file, site or None) or an error message."""
        fk, sk = FUNC_KEY.match(key), SITE_KEY.match(key)
        seg = (fk or sk).group(1)
        if not os.path.isdir(os.path.join(ROOT, "src", seg)):
            return f"unknown segment {seg!r}"
        vram = int(sk.group(2), 16) if sk else None
        names = [fk.group(2)] if fk else names_at(seg, vram)
        for rev in self.revs:
            for path in self.files(seg, names, rev):
                an = self.analysis(path, seg, rev)
                for fn in an["functions"]:
                    if fk and fn["name"] == fk.group(2):
                        if fn["vram"] is None:
                            return f"cannot resolve {fn['name']} ({path})"
                        return dict(fn, file=path), None
                    if sk and fn["vram"] == vram:
                        s = next((s for s in fn["sites"] if s["key"] == key), None)
                        if s:
                            return dict(fn, file=path), s
        where = " or ".join(self.revs)
        return f"no {'C function' if fk else 'site'} {key} at {where}"


AGENT_ID = re.compile(r"[A-Za-z0-9_]{1,48}(\.[A-Za-z0-9_]{1,48}){0,3}")  # subagents: `Clean12E800.SnXxx`


MODEL_SEL = re.compile(r"[\w.-]+/[\w.-]+(:\w+)?")  # provider/model[:thinking level]


def retry_error(ev, by_site, by_func, unit, agent):
    """Error text when EV is a HARD-method attempt without `new=` on a site (function, for
    reconstruct) that another unit or agent already tried with that method, else None. A re-record
    of UNIT/AGENT's own attempt (merge_record.py at the merge commit) is exempt."""
    if ev["method"] not in HARD or ev.get("new"):
        return None
    prior = by_func[(ev["seg"], ev["vram"])] if ev["method"] == "reconstruct" else by_site[ev["site"]]
    prior = [e for e in prior if e["method"] == ev["method"] and e.get("agent") != "sweep"]
    if not prior or any((e.get("unit"), e.get("agent")) == (unit, agent) for e in prior):
        return None
    return (f"tried before ({len(prior)} earlier events): "
            f'add new="<what this attempt tried that earlier ones did not>"')


def cmd_record(a):
    if not AGENT_ID.fullmatch(a.agent):
        sys.exit(f"quality: bad agent name {a.agent!r}")
    if a.model is not None and not MODEL_SEL.fullmatch(a.model):
        sys.exit("quality: bad model selector")
    src = sys.stdin if a.batch == "-" else open(a.batch)
    rows, errors = [], []
    for n, line in enumerate(src.read().split("\n"), 1):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        try:
            key, method, outcome, o = parse_line(line)
        except ValueError as ex:
            errors.append(f"line {n}: {ex}")
            continue
        err = validate(key, method, outcome, o)
        if err:
            errors.append(f"line {n}: {key} {method}: {err}")
        else:
            rows.append((n, key, method, outcome, o))
    res, events, numbered = Resolver(a.base), [], []
    for n, key, method, outcome, o in rows if not errors else ():
        found = res.find(key)
        if isinstance(found, str):
            if a.skip_missing and (found.startswith("no site") or found.startswith("no C function")):
                print(f"record: skipped line {n}: {key} (no site)", file=sys.stderr)
                continue
            errors.append(f"line {n}: {found}")
            continue
        fn, site = found
        events.append(event(a.unit, a.agent, fn, site, method, outcome, model=a.model, **o))
        numbered.append((n, key))
    old = load_events()
    by_site, by_func = index_events(old)
    for (n, key), ev in zip(numbered, events):
        err = retry_error(ev, by_site, by_func, a.unit, a.agent)
        if err:
            errors.append(f"line {n}: {key} {ev['method']}: {err}")
    if errors:
        for e in errors:
            print(f"record: {e}", file=sys.stderr)
        print("record: nothing written", file=sys.stderr)
        sys.exit(1)
    if a.dry_run:
        print(f"would record {len(events)} events (unit {a.unit}) to {rel(LEDGER)}")
        return
    append_events(unit_events(a.unit, old) + events)
    print(f"recorded {len(events)} events (unit {a.unit}) to {rel(LEDGER)}")


# ---------------------------------------------------------------- worker models

def models_path():
    """drafts/quality/models.jsonl: {unit, agent, model, src} rows, the worker model of one agent in
    one unit for events recorded without `model` (load_events reads only the shards, not this file)."""
    return os.path.join(LEDGER, "models.jsonl")


def load_models():
    """{(unit, agent): model selector}, {} when there is no sidecar."""
    if not os.path.exists(models_path()):
        return {}
    with open(models_path()) as fh:
        rows = [json.loads(line) for line in fh if line.strip()]
    return {(r["unit"], r["agent"]): r["model"] for r in rows}


def cmd_backfill_models(a):
    index, have, first = ledger.transcripts(a.sessions), load_models(), {}
    for e in load_events():
        if e.get("type") != "quality" or e.get("agent") in ("sweep", "carry"):
            continue
        k = (e["unit"], e["agent"])
        if k not in have and (k not in first or e["t"] < first[k]):
            first[k] = e["t"]
    rows, window = [], datetime.timedelta(hours=36)
    for (unit, agent), t in sorted(first.items(), key=lambda kv: kv[1]):
        ts, leaf = ledger._when(t), agent.rsplit(".", 1)[-1]
        cands = [(s, m) for name, runs in index.items() if re.fullmatch(re.escape(leaf) + r"(-\d+)?", name)
                 for s, m in runs if s <= ts and ts - s <= window]
        if cands:
            rows.append({"unit": unit, "agent": agent, "model": max(cands)[1], "src": "transcript"})
    if rows and not a.dry_run:
        os.makedirs(LEDGER, exist_ok=True)
        with open(models_path(), "a") as f:
            f.writelines(json.dumps(r, sort_keys=True) + "\n" for r in rows)
    print(f"filled {len(rows)} of {len(first)} agent units ({len(first) - len(rows)} without a transcript)"
          + (" (dry run)" if a.dry_run else ""))


# ---------------------------------------------------------------- status / rank / report

def grep_files(name):
    r = subprocess.run(["git", "grep", "-l", "-w", "-F", name, "--", "src"], cwd=ROOT, capture_output=True, text=True)
    return [p for p in r.stdout.split() if p.endswith(".c") and "/libultra/" not in p]


def cmd_status(a):
    files = [rel(a.file)] if a.file else grep_files(a.func) if a.func else clint.src_files()
    ans = analyze_many(files)
    require_resolved(ans)
    by_site, by_func = index_events(load_events())
    for an in ans:
        fns = [fn for fn in an["functions"] if not a.func or fn["name"] == a.func]
        if not fns:
            continue
        states = [(fn, function_state(fn, by_site, by_func)) for fn in fns]
        print(f"{an['path']}: {len(fns)} functions ({sum(st['done'] for _, st in states)} EXHAUSTED), "
              f"{sum(len(fn['sites']) for fn in fns)} sites")
        for fn, st in states:
            print(f"{fn['name']} {fn['seg']}:{fn['vram']:08X} line {fn['line']} review={st['review']}"
                  + (f" reconstruct={st['reconstruct']}" if st["reconstruct"] else "")
                  + (" EXHAUSTED" if st["done"] else f" OPEN next={st['next']}"))
            for s, r in st["sites"]:
                state = ("EXHAUSTED" if r["done"] else "WAIVED (views blocked)"
                         if s["kind"] == "proto-type" and st["waived"] else f"OPEN next={r['next']}")
                marks = " ".join(f"{m}={v}" for m, v in r["marks"].items())
                code = f"[W{s['warning']}] {s['code']}"[:100] if s["kind"] == "warning" else s["code"][:70]
                print(f"  {s['key']} line {s['line']} {s['kind']} {marks} {state} | {code}")


HACK_KINDS = set(KINDS) - {"warning", "proto-type"}
LEVEL_RANK = {"minimal": 0, "low": 0, "medium": 1, "high": 2, "xhigh": 3, "max": 3}
WEAK_MODELS = ("flash", "haiku")


def strength(sel):
    """Strength of one attempt by model selector provider/model[:level]: 0 for flash/haiku models,
    else its thinking level's LEVEL_RANK; 1 when the selector or its level is unknown."""
    if not sel:
        return 1
    model, _, level = sel.partition(":")
    if any(w in model.lower() for w in WEAK_MODELS):
        return 0
    return LEVEL_RANK.get(level, 1)


def attempts(fn, by_site, by_func, models):
    """dict(best, units, strong) over the HARD-method agent events on FN's hack sites plus its
    reconstruct events: per attempting unit (a carried event counts for the unit and agent of the
    event it copies) the strongest model, `best` the strongest unit (-1: none), `units` their
    count, `strong` the units at strength 3. MODELS: load_models()."""
    evs = [e for s in fn["sites"] if s["kind"] in HACK_KINDS for e in by_site.get(s["key"], [])]
    evs += [e for e in by_func.get((fn["seg"], f"{fn['vram']:08X}"), []) if e["method"] == "reconstruct"]
    per_unit = {}
    for e in evs:
        if e["method"] not in HARD or e.get("agent") == "sweep":
            continue
        src = e
        if e.get("agent") == "carry":
            src = next((x for x in evs if x.get("agent") != "carry" and x["method"] == e["method"]
                        and x["t"] == e["t"]), e)
        unit = (origin_unit(e, evs) or e["unit"]) if e.get("agent") == "carry" else e["unit"]
        sel = e.get("model") or src.get("model") or models.get((src["unit"], src["agent"]))
        per_unit[unit] = max(per_unit.get(unit, 0), strength(sel))
    return dict(best=max(per_unit.values(), default=-1), units=len(per_unit),
                strong=sum(v >= 3 for v in per_unit.values()))


def cmd_rank(a):
    files = seg_files(a.seg) if a.seg else clint.src_files()
    ans = analyze_many(files)
    require_resolved(ans)
    by_site, by_func = index_events(load_events())
    if a.polish:  # file-level work: functions with no hack site left that are not done
        rows = []
        for an in ans:
            left = [st for fn in an["functions"] if not any(s["kind"] in HACK_KINDS for s in fn["sites"])
                    for st in [function_state(fn, by_site, by_func)] if not st["done"]]
            if left:
                rows.append((len(left), sum(st["review"] != "✓" for st in left), an["path"],
                             collections.Counter(st["next"] for st in left)))
        rows.sort(key=lambda r: (-r[1], -r[0], r[2]))
        print(f"{'count':>5} {'unrev':>5}  file  next")
        for n, unrev, path, nxt in rows[:a.limit]:
            print(f"{n:>5} {unrev:>5}  {path}  " + " ".join(f"{k}={v}" for k, v in sorted(nxt.items())))
        print(f"{len(rows)} files, {sum(r[0] for r in rows)} functions")
        return
    models, rows = load_models(), []
    for an in ans:
        for fn in an["functions"]:
            hacks = [s for s in fn["sites"] if s["kind"] in HACK_KINDS]
            if not hacks:
                continue
            st, at = function_state(fn, by_site, by_func), attempts(fn, by_site, by_func, models)
            kinds = " ".join(f"{k}={v}" for k, v in sorted(collections.Counter(s["kind"] for s in hacks).items()))
            rows.append((at["best"], len(hacks), at["units"], at["strong"], an["path"], fn["name"],
                         "EXHAUSTED" if st["done"] else f"next={st['next']}", kinds))
    rows.sort(key=lambda r: (r[0], -r[1], r[2], r[4], r[5]))
    print(f"{'str':>3} {'att':>3} {'strong':>6} {'hacks':>5}  state  file  function  kinds")
    for best, hacks, units, strong, path, name, state, kinds in rows[:a.limit]:
        print(f"{'-' if best < 0 else best:>3} {units:>3} {strong:>6} {hacks:>5}  {state}  {path}  {name}  {kinds}")
    print(f"{len(rows)} functions with hacks ({sum(r[1] for r in rows)} sites), "
          f"{sum(r[3] >= 3 for r in rows)} with 3+ strong attempts")


def cmd_history(a):
    files = [rel(a.file)] if a.file else grep_files(a.func)
    fns = [dict(fn, file=an["path"]) for an in analyze_many(files) for fn in an["functions"]
           if fn["name"] == a.func]
    if not fns:
        sys.exit(f"history: no C function {a.func}")
    events, models = load_events(), load_models()
    for fn in fns:
        if fn["vram"] is None:
            sys.exit(f"history: cannot resolve {fn['name']} ({fn['file']})")
        here = (fn["seg"], f"{fn['vram']:08X}")  # every event of the function, removed sites' too
        evs = [e for e in events if e.get("type") == "quality" and (e["seg"], e["vram"]) == here
               and (a.all or e.get("agent") not in ("sweep", "carry"))]
        print(f"{fn['name']} ({fn['seg']}:{here[1]}, {fn['file']}): {len(evs)} events")
        for e in sorted(evs, key=lambda e: e["t"]):
            model = e.get("model") or models.get((e["unit"], e["agent"])) or "-"
            new = f' new="{e["new"]}"' if e.get("new") else ""
            print(f"{e['t'][:16]} {e['unit']} {e['agent']} {model} {e['method']} {e['outcome']} "
                  f"{e['site'] or 'func'} {(e.get('note') or '')[:160]}{new}")


def cmd_permute_candidates(a):
    """Copies with one hack site removed (or plainly rewritten) for `tools/permute.py batch`: sites
    whose agent permute runs reached a base score <= --max-base, whose edit does not already match."""
    out = cli_path(a.out)
    if os.path.isdir(os.path.join(ROOT, out)) and os.listdir(os.path.join(ROOT, out)):
        sys.exit(f"permute-candidates: {out} is not empty")
    ans = analyze_many(clint.src_files())
    require_resolved(ans)
    by_site, _ = index_events(load_events())
    cands = []
    for an in ans:
        lines = open(os.path.join(ROOT, an["path"]), encoding="utf-8", errors="replace").read().split("\n")
        for fn in an["functions"]:
            for s in fn["sites"]:
                bases = [e["base"] for e in by_site.get(s["key"], []) if e["method"] == "permute"
                         and e.get("agent") != "sweep" and e.get("base") is not None]
                if s["kind"] not in HACK_KINDS or not bases or min(bases) > a.max_base:
                    continue
                ed = remove_edit(s, lines, fn)
                texts = ([apply(lines, merged([(s, ed)]))] if ed is not None
                         else plain_rewrites(s, lines)[:1] if s["kind"] in PLAIN_KINDS else [])
                if texts:
                    cands.append((an, fn, s, min(bases), texts[0]))
    rows = []
    for an, fn, s, base, text in cands:
        if a.limit and len(rows) >= a.limit:
            break
        if check(text, an["path"], an["path"], uninit=False):
            continue  # already matches: a sweep matter
        d = os.path.join(out, f"{len(rows) + 1:03d}_{an['seg']}_{fn['name']}")
        os.makedirs(os.path.join(ROOT, d))
        copy = os.path.join(d, os.path.basename(an["path"]))
        open(os.path.join(ROOT, copy), "w").write(text)
        rows.append("\t".join((d, an["seg"], fn["name"], copy, an["path"], s["key"], str(base))))
    os.makedirs(os.path.join(ROOT, out), exist_ok=True)
    open(os.path.join(ROOT, out, "list.tsv"), "w").write("".join(r + "\n" for r in rows))
    print(f"{len(rows)} candidates ({len(cands)} sites with permute base <= {a.max_base}) in {out}/list.tsv")


# ---------------------------------------------------------------- carry (renames keep results)

SYM_LINE = re.compile(r"^\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)\s*;", re.M)
ADDR_NAME = re.compile(r"(?:D|func)_([0-9A-F]{8})")
_symtext = {}


def sym_addr(seg, name, rev):
    """Address of global symbol NAME seen from segment SEG in the symbol files at REV (None: the
    working tree), or None. `D_XXXXXXXX`/`func_XXXXXXXX` names carry their address."""
    m = ADDR_NAME.fullmatch(name)
    if m:
        return int(m.group(1), 16)
    own = "symbol_addrs.us.txt" if seg in ("boot", "global") else f"symbol_addrs.{seg}.us.txt"
    for f in dict.fromkeys([own, "symbol_addrs.us.txt", "undefined_syms.us.txt"]):
        if (f, rev) not in _symtext:
            if rev:
                text = subprocess.run(["git", "show", f"{rev}:{f}"], cwd=ROOT, capture_output=True, text=True).stdout
            else:
                p = os.path.join(ROOT, f)
                text = open(p).read() if os.path.exists(p) else ""
            d = {}
            for n, v in SYM_LINE.findall(text):
                d.setdefault(n, int(v, 16))
            _symtext[(f, rev)] = d
        if name in _symtext[(f, rev)]:
            return _symtext[(f, rev)][name]
    return None


def token_meaning(tok):
    """What an identifier token denotes, ignoring its spelling, or None when it is not a
    renameable declaration (type names, macros, labels, enum constants: their spelling must stay).
    A local is its canonical type (declarations are in the compared text, so the one-to-one name
    map pins which local); a global or function its kind and type (its address is checked
    separately); a field its type, offset and record size."""
    c = tok.cursor
    if c is None:
        return None
    ref = c.referenced or c
    k = ref.kind
    if k in (CursorKind.VAR_DECL, CursorKind.PARM_DECL):
        local = ref.semantic_parent is not None and ref.semantic_parent.kind == CursorKind.FUNCTION_DECL
        return ("local" if local else "global", ref.type.get_canonical().spelling)
    if k == CursorKind.FUNCTION_DECL:
        return ("func", ref.type.get_canonical().spelling)
    if k == CursorKind.FIELD_DECL:
        return ("field", ref.type.get_canonical().spelling, ref.get_field_offsetof(),
                ref.semantic_parent.type.get_size() if ref.semantic_parent is not None else None)
    return None


def field_record(tok):
    """Canonical spelling of the record declaring the field identifier TOK names."""
    p = (tok.cursor.referenced or tok.cursor).semantic_parent
    return p.type.get_canonical().spelling if p is not None else None


def file_tokens(tu, path):
    """Non-comment tokens of PATH's own text, in order."""
    want = os.path.realpath(os.path.join(ROOT, path))
    return [t for t in tu.get_tokens(extent=tu.cursor.extent)
            if t.kind != TokenKind.COMMENT and t.location.file is not None
            and os.path.realpath(os.path.join(ROOT, t.location.file.name)) == want]


def rename_map(old_toks, new_toks, addr_old, addr_new):
    """{old: new} of every renamed identifier when NEW_TOKS is OLD_TOKS with only declared names
    renamed: keywords, literals, punctuation and every non-renameable identifier (types, macros,
    labels, enum constants) unchanged; names mapped one-to-one (a field's name per record: keys
    and values ('field', record type, name)); each renamed token keeping its declaration kind and
    canonical type, a field its offset, a global or function its address (ADDR_OLD / ADDR_NEW:
    name -> address or None). `PROTO_SKIP_<name>` follows the mapping of <name>. Else None."""
    if len(old_toks) != len(new_toks):
        return None
    fwd, back = {}, {}
    for x, y in zip(old_toks, new_toks):
        if x.kind != y.kind:
            return None
        xs, ys = x.spelling, y.spelling
        if x.kind != TokenKind.IDENTIFIER:
            if xs != ys:
                return None
            continue
        px, py = xs.startswith("PROTO_SKIP_"), ys.startswith("PROTO_SKIP_")
        if px or py:
            if not (px and py):
                return None
            xs, ys = xs[len("PROTO_SKIP_"):], ys[len("PROTO_SKIP_"):]
        else:
            mx, my = token_meaning(x), token_meaning(y)
            if mx != my:
                return None
            if xs != ys:
                if mx is None:
                    return None
                if mx[0] in ("global", "func"):
                    a = addr_old(xs)
                    if a is None or a != addr_new(ys):
                        return None
            if mx is not None and mx[0] == "field":
                xs, ys = ("field", field_record(x), xs), ("field", field_record(y), ys)
        if fwd.setdefault(xs, ys) != ys or back.setdefault(ys, xs) != xs:
            return None
    return {x: y for x, y in fwd.items() if x != y}


def rename_equivalent(old_toks, new_toks, addr_old, addr_new):
    """Whether NEW_TOKS is OLD_TOKS with only declared names renamed (`rename_map`)."""
    return rename_map(old_toks, new_toks, addr_old, addr_new) is not None


def field_renames(ot, nt):
    """{(record spelling, old field name): new name} of the fields renamed between records OT and NT
    (equal `clint.record_layout` modulo field names), unnamed records nested in their field types
    (as `clint.type_sig` spells them out) included; None when an anonymous member gains or loses a
    name."""
    out = {}

    def inner(t):
        t = t.get_canonical()
        while t.kind in (TypeKind.POINTER, TypeKind.CONSTANTARRAY):
            t = (t.get_pointee() if t.kind == TypeKind.POINTER else t.element_type).get_canonical()
        return t

    def walk(a, b):
        for fa, fb in zip(a.get_fields(), b.get_fields()):
            na, nb = clint.field_name(fa), clint.field_name(fb)
            if na != nb:
                if not na or not nb:
                    return False
                out[(a.spelling, na)] = nb
            ta, tb = inner(fa.type), inner(fb.type)
            if ta.kind == TypeKind.RECORD and clint.UNNAMED.search(ta.spelling) and not walk(ta, tb):
                return False
        return True

    return out if walk(ot.get_canonical(), nt.get_canonical()) else None


def header_renames(path, old_scope, old_closure, new_scope, new_closure, fwd, old_body):
    """(sorted records whose fields were renamed, {name: `respelled_decl`/`moved_decl` description},
    None) when every declaration OLD_CLOSURE reaches (in OLD_SCOPE: REV's text parsed with REV's
    headers) has NEW_CLOSURE's text once FWD's (`rename_map`) name renames apply (a renamed function
    or global keyed by its new name), is a function or variable declaration moved or respelled with
    the same type (`moved_decl`, `respelled_decl`), or is a record (include/ or PATH's own) keeping
    size, alignment and every field offset, width and type (`clint.record_layout` modulo field
    names, nested unnamed records' too) whose text matches once its field renames apply, every
    renamed field OLD_BODY (REV's body tokens, in OLD_SCOPE's parse) uses renamed alike in FWD (an
    unchanged body uses none); else (None, None, why)."""
    def texts(scope, name, m):  # `Scope.direct`'s texts with M's renames applied
        return sorted({(rel(os.path.join(ROOT, c.location.file.name)),
                        " ".join(m.get(t.spelling, t.spelling) if t.kind == TokenKind.IDENTIFIER else t.spelling
                                 for t in decl_tokens(c)))
                       for c in scope.idx.get(name, [])})

    def unnamed(lay):  # field names dropped, nested unnamed records' (`name@offset:`) too
        return lay[0], [(o, w, re.sub(r"\w*@", "@", s)) for _, o, w, s in lay[1]], lay[2]

    used = {(field_record(t), t.spelling) for t in old_body
            if t.kind == TokenKind.IDENTIFIER and (token_meaning(t) or ("",))[0] == "field"}
    sfwd = {k: v for k, v in fwd.items() if isinstance(k, str)}
    olds, recs, moved = {sfwd.get(k, k): k for k in old_closure}, [], {}
    for name in sorted(set(olds) | set(new_closure)):
        if name not in olds or name not in new_closure:
            return None, None, f"{name} only {'at HEAD' if name in new_closure else 'at REV'}"
        o, nv = olds[name], new_closure[name]
        if texts(old_scope, o, sfwd) == nv:
            continue
        ot, nt = record_type(old_scope.idx[o]), record_type(new_scope.idx[name])
        if ot is None or nt is None:
            how, mwhy = moved_decl(path, name, old_closure[o], nv, old_scope, new_scope) if o == name else (None, None)
            resp = respelled_decl(path, name, old_closure[o], nv, old_scope, new_scope) if o == name else None
            if how is None and resp is None:
                return None, None, mwhy or f"{name} changed"
            moved[name] = f"{how}, identical" if how is not None else resp
            continue
        lo, ln = clint.record_layout(ot), clint.record_layout(nt)
        if lo is None or ln is None:
            return None, None, f"record {name} incomplete"
        if unnamed(lo) != unnamed(ln):
            diff = clint.layout_diff({name: lo}, {name: ln}, types=True)
            return None, None, "layout changed: " + ("; ".join(diff) if diff else f"{name} fields")
        frn = field_renames(ot, nt)
        fmap = dict(sfwd)
        for (_, x), y in (frn or {}).items():
            if fmap.setdefault(x, y) != y:
                frn = None
        if frn is None or texts(old_scope, o, fmap) != nv:
            return None, None, f"record {name} changed beyond field renames"
        for (r, x), y in frn.items():
            if (r, x) in used and fwd.get(("field", r, x), (None, None, x))[2] != y:
                return None, None, f"record {name} field {x} renamed {y}, body keeps {x}"
        recs.append(name)
    return recs, moved, None


def carry_lines(fns, fn, nlines):
    """1-based lines analyze() hashes into FN's fp_local: its body plus the file's top level."""
    inside = {i for f in fns for i in range(f["line"], f["end"] + 1)}
    return set(range(fn["line"], fn["end"] + 1)) | {i for i in range(1, nlines + 1) if i not in inside}


def top_index(tu):
    """name -> top-level cursors of the TU (main file and headers) declaring it: declarations,
    typedefs, record/enum definitions (forward `struct T;` lines change no layout and are left
    out), enum constants (their enum), macro definitions."""
    idx = collections.defaultdict(list)
    for c in tu.cursor.get_children():
        if c.location.file is None or c.kind in (CursorKind.MACRO_INSTANTIATION, CursorKind.INCLUSION_DIRECTIVE):
            continue
        if c.kind in (CursorKind.STRUCT_DECL, CursorKind.UNION_DECL, CursorKind.ENUM_DECL) and not c.is_definition():
            continue
        if c.spelling and re.fullmatch(r"\w+", c.spelling):
            idx[c.spelling].append(c)
        if c.kind == CursorKind.ENUM_DECL:
            for e in c.get_children():
                idx[e.spelling].append(c)
    return idx


def decl_tokens(c):
    """Non-comment tokens of a top-level cursor; a function definition only up to its body."""
    stop = next((ch.extent.start.offset for ch in c.get_children() if ch.kind == CursorKind.COMPOUND_STMT), None)
    return [t for t in c.get_tokens() if t.kind != TokenKind.COMMENT and (stop is None or t.extent.start.offset < stop)]


class Scope:
    """Name reachability over one TU's top-level declarations (`top_index`), memoized per name."""

    def __init__(self, tu):
        self.idx, self.memo, self.pasting, self.paste_memo = top_index(tu), {}, set(), {}

    def direct(self, name):
        """(sorted (file, text) of NAME's top-level declarations, identifiers their tokens name).
        Records NAME in `pasting` when one of its macro definitions uses `##`: the identifiers it
        pastes together are not tokens, so closures through it are incomplete."""
        if name not in self.memo:
            vals, names = set(), set()
            for c in self.idx[name]:
                dt = decl_tokens(c)
                vals.add((rel(os.path.join(ROOT, c.location.file.name)), " ".join(t.spelling for t in dt)))
                names.update(t.spelling for t in dt if t.kind == TokenKind.IDENTIFIER)
                if c.kind == CursorKind.MACRO_DEFINITION and any(t.spelling == "##" for t in dt):
                    self.pasting.add(name)
            self.memo[name] = (sorted(vals), names)
        return self.memo[name]

    def paste_names(self, name):
        """Names the `##` pastes of macro NAME can form, or None when one is unbounded. A paste
        `frag ## param` can only form a name starting with the literal identifier FRAG, `param ##
        frag` one ending with it (`GBL_c##clk` -> GBL_c1, GBL_c2); two parameters pasted together
        could form anything."""
        if name not in self.paste_memo:
            out = set()
            for c in self.idx[name]:
                if c.kind != CursorKind.MACRO_DEFINITION:
                    continue
                dt = decl_tokens(c)
                params = set()
                if len(dt) > 1 and dt[1].spelling == "(" and dt[1].extent.start.offset == dt[0].extent.end.offset:
                    for t in dt[2:]:
                        if t.spelling == ")":
                            break
                        if t.kind == TokenKind.IDENTIFIER:
                            params.add(t.spelling)
                for i, t in enumerate(dt):
                    if t.spelling != "##":
                        continue
                    left, right = dt[i - 1].spelling, dt[i + 1].spelling if i + 1 < len(dt) else ""
                    lfix = left if dt[i - 1].kind == TokenKind.IDENTIFIER and left not in params else None
                    rfix = right if i + 1 < len(dt) and dt[i + 1].kind in (
                        TokenKind.IDENTIFIER, TokenKind.LITERAL) and right not in params else None
                    if lfix is None and rfix is None:
                        out = None
                        break
                    out |= {n for n in self.idx if (lfix and n.startswith(lfix)) or (rfix and n.endswith(rfix))}
                if out is None:
                    break
            self.paste_memo[name] = out
        return self.paste_memo[name]

    def closure(self, names, pastes=False, leaves=()):
        """name -> sorted (file, text) of every top-level declaration NAMES reach, transitively
        through the declarations' own tokens (types, fields' types, macros, prototypes). Name-based,
        so it over-includes (a local shadowing a global name pulls the global in), never
        under-includes, except through token-pasting macros (`pasted`). PASTES follows bounded
        pastes too (`paste_names`): every name a paste could form is reached. LEAVES are reached
        but not followed."""
        seen, stack = {}, list(names)
        while stack:
            name = stack.pop()
            if name in seen or name not in self.idx:
                continue
            seen[name], more = self.direct(name)
            if name in leaves:
                continue
            if pastes and name in self.pasting:
                more = more | (self.paste_names(name) or set())
            stack += [n for n in more if n not in seen]
        return seen

    def pasted(self, closure):
        """First (sorted) token-pasting macro in CLOSURE, or None."""
        return min((n for n in closure if n in self.pasting), default=None)

    def unbounded(self, closure):
        """First (sorted) macro in CLOSURE with a paste `paste_names` cannot bound, or None."""
        return min((n for n in closure if n in self.pasting and self.paste_names(n) is None), default=None)

    def fp_hdr2(self, names, whole, skip=()):
        """sha1 of the include/ declarations NAMES reach: a function's own header fingerprint
        (a regenerated proto header or an edited struct changes it only for its users). When they
        reach a `##` macro the reached set is incomplete, so it derives from WHOLE (fp_hdr) instead.
        SKIP: names left out (declarations `scope_equivalent` found moved unchanged)."""
        inc = "include" + os.sep
        h = hashlib.sha1()
        cl = self.closure(names)
        if self.pasted(cl):
            h.update(f"whole\0{whole}".encode())
            return h.hexdigest()[:16]
        for name, vals in sorted(cl.items()):
            if name in skip:
                continue
            for f, text in vals:
                if f.startswith(inc):
                    h.update(f"{name}\0{f}\0{text}\0".encode("utf-8", "replace"))
        return h.hexdigest()[:16]


def idents_by_line(toks):
    """line -> identifier spellings of TOKS (one pass: token locations are slow to read)."""
    out = collections.defaultdict(list)
    for t in toks:
        if t.kind == TokenKind.IDENTIFIER:
            out[t.location.line].append(t.spelling)
    return out


def body_names(by_line, fn):
    return [n for i in range(fn["line"], fn["end"] + 1) for n in by_line.get(i, ())]


def moved_decl(path, name, ov, nv, old_scope, new_scope):
    """('moved to|from <header>', None) when NAME's top-level declarations only moved between PATH's
    own file scope and an include/ header: OV and NV (its `Scope.closure` values in OLD_SCOPE and
    NEW_SCOPE) differ only in entries of one file each, PATH on one side and the header on the
    other, and the moved declaration is identical: a record (typedef'd or tagged; a tag added to an
    anonymous typedef'd record keeps its name) with the same `clint.record_layout` (size, alignment,
    field names, offsets, widths and types: `clint.layout_diff` with types, plus renames), anything
    else (enum, typedef of a scalar, macro, prototype) with the same token text; else (None, why)."""
    inc = "include" + os.sep
    oe, ne = [v for v in ov if v not in nv], [v for v in nv if v not in ov]
    ofiles, nfiles = {f for f, _ in oe}, {f for f, _ in ne}
    if len(ofiles) != 1 or len(nfiles) != 1:
        return None, None
    (of,), (nf,) = ofiles, nfiles
    if of == path and nf.startswith(inc):
        how = f"moved to {nf}"
    elif nf == path and of.startswith(inc):
        how = f"moved from {of}"
    else:
        return None, None
    ot, nt = record_type(old_scope.idx.get(name, [])), record_type(new_scope.idx.get(name, []))
    if ot is not None and nt is not None:
        lo, ln = clint.record_layout(ot), clint.record_layout(nt)
        if lo is None or ln is None:
            return None, f"{name} {how}, incomplete"
        diff = clint.layout_diff({name: lo}, {name: ln}, types=True)
        if not diff and lo != ln:  # layout_diff keeps renamed fields (padding names) and bitfield widths
            diff = [f"{name} {o[0]} -> {n[0]}" if o[0] != n[0] else f"{name} {o[0]} width {o[2]} -> {n[2]}"
                    for o, n in zip(lo[1], ln[1]) if o != n] or [f"{name} fields {len(lo[1])} -> {len(ln[1])}"]
        return (None, f"{name} {how}, changed: " + "; ".join(diff)) if diff else (how, None)
    if ot is not None or nt is not None or sorted(t for _, t in oe) != sorted(t for _, t in ne):
        return None, f"{name} {how}, changed"
    return how, None


def decl_signature(c):
    """Canonical type of a function or variable declaration (not a definition): (kind, storage
    class, canonical type, and for a function its canonical return and parameter types,
    variadic-ness and written prototype-ness: `T f();` is unprototyped even where clang lends a
    builtin its prototype), else None."""
    if c.kind not in (CursorKind.FUNCTION_DECL, CursorKind.VAR_DECL) or c.is_definition():
        return None
    t = c.type.get_canonical()
    sig = (c.kind.name, c.storage_class.name, t.spelling)
    if c.kind == CursorKind.FUNCTION_DECL:
        proto = t.kind == TypeKind.FUNCTIONPROTO
        toks = [x.spelling for x in c.get_tokens()]
        for i in range(len(toks) - 2):
            if toks[i] == c.spelling and toks[i + 1] == "(":
                proto = proto and toks[i + 2] != ")"  # clang gives `T builtin();` the builtin's prototype
                break
        sig += (t.get_result().spelling, proto, proto and t.is_function_variadic(),
                tuple(a.spelling for a in t.argument_types()) if proto else ())
    return sig


def respelled_decl(path, name, ov, nv, old_scope, new_scope):
    """'NAME declaration respelled|moved to|from <header>, same type' when NAME's top-level
    declarations (OV and NV, its `Scope.closure` values in OLD_SCOPE and NEW_SCOPE) are function or
    variable declarations whose text changed, possibly moving between PATH's file scope and an
    include/ header, but whose `decl_signature`s are identical (K&R vs prototyped is a change);
    else None."""
    os_, ns = ([decl_signature(c) for c in sc.idx.get(name, [])] for sc in (old_scope, new_scope))
    if not os_ or not ns or None in os_ or None in ns or set(os_) != set(ns):
        return None
    inc = "include" + os.sep
    ofiles = {f for f, _ in ov if (f, _) not in nv}
    nfiles = {f for f, _ in nv if (f, _) not in ov}
    if ofiles == {path} and len(nfiles) == 1 and next(iter(nfiles)).startswith(inc):
        return f"{name} declaration moved to {next(iter(nfiles))}, same type"
    if nfiles == {path} and len(ofiles) == 1 and next(iter(ofiles)).startswith(inc):
        return f"{name} declaration moved from {next(iter(ofiles))}, same type"
    return f"{name} declaration respelled, same type"


def type_renames(path, old_body, new_body, old_closure, new_closure, old_scope, new_scope):
    """({old: new}, closure renamer) when OLD_BODY and NEW_BODY differ only in identifiers naming a
    file-local typedef, record or enum (typedef name and/or tag) of PATH that was renamed, mapped
    one-to-one, each renamed declaration identical apart from the name (same token text once renamed;
    a record also the same `clint.record_layout`, field types included). A local type only in
    OLD_CLOSURE (reached through a declaration, not the body) pairs with the one new-only local type
    whose renamed text it matches. ({}, None) when nothing was renamed; else None. The renamer maps
    a `Scope.closure` of the old side onto new names and texts."""
    if len(old_body) != len(new_body):
        return None
    fwd, back = {}, {}
    for x, y in zip(old_body, new_body):
        if x.kind != y.kind or (x.kind != TokenKind.IDENTIFIER and x.spelling != y.spelling):
            return None
        if x.spelling != y.spelling and (fwd.setdefault(x.spelling, y.spelling) != y.spelling
                                         or back.setdefault(y.spelling, x.spelling) != x.spelling):
            return None
    want, typed = os.path.realpath(os.path.join(ROOT, path)), (
        CursorKind.TYPEDEF_DECL, CursorKind.STRUCT_DECL, CursorKind.UNION_DECL, CursorKind.ENUM_DECL)

    def local_type(scope, name):
        cs = scope.idx.get(name, [])
        return cs if cs and all(c.kind in typed and c.location.file is not None
                                and os.path.realpath(c.location.file.name) == want for c in cs) else None

    def texts(scope, name):
        return sorted((rel(os.path.join(ROOT, c.location.file.name)),
                       " ".join(fwd.get(t.spelling, t.spelling) if t.kind == TokenKind.IDENTIFIER else t.spelling
                                for t in decl_tokens(c)))
                      for c in scope.idx.get(name, []))

    news = [n for n in set(new_closure) - set(old_closure) if local_type(new_scope, n) and n not in old_scope.idx]
    for o in sorted(set(old_closure) - set(new_closure) - set(fwd)):
        if not local_type(old_scope, o):
            continue
        hits = []
        for n in news:
            if n not in back:
                fwd[o] = n
                if texts(old_scope, o) == new_scope.direct(n)[0]:
                    hits.append(n)
                del fwd[o]
        if len(hits) == 1:
            fwd[o], back[hits[0]] = hits[0], o
    if not fwd:
        return {}, None

    for o, n in fwd.items():
        oc, nc = local_type(old_scope, o), local_type(new_scope, n)
        if oc is None or nc is None or n in old_scope.idx or texts(old_scope, o) != new_scope.direct(n)[0]:
            return None
        ot, nt = record_type(oc), record_type(nc)
        if ot is not None and nt is not None:
            lo, ln = clint.record_layout(ot), clint.record_layout(nt)
            if lo is None or ln is None or clint.layout_diff({n: lo}, {n: ln}, types=True):
                return None

    def renamer(scope, closure):
        return {fwd.get(k, k): texts(scope, k) if v is not None else v for k, v in closure.items()}
    return fwd, renamer


def scope_equivalent(path, old_body, new_body, old_closure, new_closure, old_scope, new_scope, rev=None):
    """({name: 'NAME moved to|from <header>, identical' or a `respelled_decl` description}, None)
    when a function is unchanged apart from file-scope text it does not use: same body tokens, and
    every top-level declaration, typedef, record, enum or macro it reaches (its `Scope.closure` in
    each version, OLD_CLOSURE and NEW_CLOSURE) has the same text in both versions, only moved,
    identical, between PATH's file scope and an include/ header (`moved_decl`), or is a function
    or variable declaration respelled with the same canonical type (`respelled_decl`); names only
    reached through respelled declarations (a `size_t` in the new prototype) may appear or vanish
    and map to None; else (None, why: '' or the changed moved declaration). Callers parse both
    versions against the current headers; REV = (scope, closure) of the old text parsed with REV's
    headers supplies the old side of a name whose declarations differ (the current headers may
    already hold a declaration moved into them, or no longer one moved out). A file-local typedef,
    record or enum renamed with an otherwise identical declaration (`type_renames`) maps old name to
    new in the body and closures: 'type OLD renamed NEW, identical'."""
    tr = type_renames(path, old_body, new_body, old_closure, new_closure,
                      rev[0] if rev is not None else old_scope, new_scope)
    if tr is None:
        return None, ""
    renamed, renamer = tr
    if renamed:
        old_closure = renamer(old_scope, old_closure)
        if rev is not None:
            rev = (rev[0], renamer(rev[0], rev[1]))
        old_body = new_body
    moved = {n: f"type {o} renamed {n}, identical" for o, n in renamed.items()}
    oneside = []
    for name in sorted(set(old_closure) | set(new_closure)):
        ov, nv, oscope = old_closure.get(name), new_closure.get(name), old_scope
        if ov == nv:
            continue
        if rev is not None:
            oscope, ov = rev[0], rev[1].get(name)
            if ov == nv:
                continue
        if ov is None or nv is None:
            oneside.append((name, ov is None))
            continue
        how, why = moved_decl(path, name, ov, nv, oscope, new_scope)
        if how is not None:
            moved[name] = f"{how}, identical"
            continue
        resp = respelled_decl(path, name, ov, nv, oscope, new_scope)
        if resp is None:
            return None, why or ""
        moved[name] = resp
    if oneside:
        # a name on one side only is unchanged when only respelled declarations reach it there
        leaves = {n for n, m in moved.items() if m.endswith(", same type")}
        if not leaves:
            return None, ""
        roots = {t.spelling for t in old_body if t.kind == TokenKind.IDENTIFIER}
        oscope = rev[0] if rev is not None else old_scope
        ocl, ncl = (sc.closure(roots, pastes=True, leaves=leaves) for sc in (oscope, new_scope))
        for name, new_only in oneside:
            if name in (ncl if new_only else ocl):
                return None, ""
            moved[name] = None
    return moved, None


PARAM_TYPE_PREFIX = {"(", ",", "const", "volatile", "unsigned", "signed", "short", "long", "struct", "union",
                     "enum", "register"}
C_TYPE_WORDS = PARAM_TYPE_PREFIX | {"void", "int", "char", "float", "double"}


def params_renamed(old_closure, new_closure, old_name, new_name):
    """NEW_CLOSURE with each function whose declarations differ from OLD_CLOSURE's only in
    parameter names (a prototype naming none counts as the same) given OLD_CLOSURE's entry;
    the carried function itself may have been renamed from OLD_NAME to NEW_NAME."""
    def proto(s, rename=None):
        w = s.split(" ")
        if rename:
            w = [old_name if x == rename else x for x in w]
        return {" ".join(x for i, x in enumerate(w) if not (
            0 < i < len(w) - 1 and w[i + 1] in (",", ")") and w[i - 1] not in PARAM_TYPE_PREFIX
            and re.fullmatch(r"[A-Za-z_]\w*", x) and x not in C_TYPE_WORDS))}

    def sig(v, rename=None):
        return set().union(*(proto(s, rename) for _, s in v)) if v else None

    out = dict(new_closure)
    if old_name != new_name:
        if old_name in out or new_name not in out or old_name not in old_closure:
            return new_closure
        nv = out.pop(new_name)
        if len(sig(old_closure[old_name])) != 1 or sig(nv, new_name) != sig(old_closure[old_name]):
            return new_closure
        out[old_name] = old_closure[old_name]
    for name, nv in out.items():
        ov = old_closure.get(name)
        if ov is not None and ov != nv and len(sig(ov)) == 1 and sig(ov) == sig(nv):
            out[name] = ov
    return out


def carry_renames(a, by_site, by_func):
    """(events, skipped, carried lines) re-stamping the newest fresh-at-REV events of every function
    that changed from REV to HEAD only by renames of declared names (`rename_equivalent` over its
    body and the file's top level), or by renames in its body or none (REV's parsed with REV's
    headers, so renamed fields of an include/ record resolve) with every declaration it reaches
    equal modulo the renames (`header_renames`: records, include/ or the .c's own, keeping their
    layout modulo field names; declarations moved or respelled with the same type), or only by
    file-scope text of the .c it does not use or by declarations it uses moving unchanged between
    the .c and an include/ header (`scope_equivalent`), with HEAD's fingerprints and site keys.
    REV's text is analysed (parsed, fingerprinted and compiled for its warning sites) with REV's
    headers. A.func: only functions so named at REV or HEAD."""
    files = a.files or [p for p in ledger.git("diff", "--name-only", a.rev, "HEAD", "--", "src").split()
                        if p.endswith(".c") and "/libultra/" not in p and os.path.exists(os.path.join(ROOT, p))]
    out, skipped, lines = [], [], []
    hdrs = rev_headers(a.rev)
    for path in files:
        path, seg = rel(path), seg_of(path)
        old_text = subprocess.run(["git", "show", f"{a.rev}:{path}"], cwd=ROOT, capture_output=True, text=True).stdout
        new_text = open(os.path.join(ROOT, path), encoding="utf-8", errors="replace").read()
        # REV's sites (its warning sites compiled against REV's headers) and fingerprints, so events
        # recorded at REV are found; the equivalence checks below parse both texts against the current
        # headers (header changes are --header-carve's; REV's scope only for declarations moved out of
        # a header since)
        old, new = analyze(path, seg, text=old_text, hdrs=hdrs, rev=a.rev, keep=True), analyze(path, seg)
        if len(old["functions"]) != len(new["functions"]):
            skipped.append(f"{path}: function count changed")
            continue
        full = os.path.join(ROOT, path)
        otu, ntu = clint.parse(path, unsaved=[(full, old_text)]), clint.parse(path, unsaved=[(full, new_text)])
        otoks = [(t.location.line, t) for t in file_tokens(otu, path)]
        ntoks = [(t.location.line, t) for t in file_tokens(ntu, path)]
        oscope, nscope = Scope(otu), Scope(ntu)
        onames, nnames = idents_by_line(t for _, t in otoks), idents_by_line(t for _, t in ntoks)
        for fo, fn in zip(old["functions"], new["functions"]):
            if a.func and fo["name"] not in a.func and fn["name"] not in a.func:
                continue
            if fn["vram"] is None or fo["vram"] not in (None, fn["vram"]):
                skipped.append(f"{path}: {fn['name']}: identity changed")
                continue
            if fo["fp_local"] == fn["fp_local"]:
                continue  # same text: its events are as fresh as they were (header changes: --header-carve)
            # file-scope sites (skip and declaration lines above the function) may be tagged, retagged
            # (`// PROTO:` -> `// FAKE: callee prototype steer`) or untagged: comments only, the tokens
            # are compared below. Body sites must keep their kinds; file-scope ones pair by key, so a
            # new or retagged one starts its own ladder.
            ob = [s for s in fo["sites"] if fo["line"] <= s["line"] <= fo["end"]]
            nb = [s for s in fn["sites"] if fn["line"] <= s["line"] <= fn["end"]]
            sites_match = [s["kind"] for s in ob] == [s["kind"] for s in nb]
            nkeys = {s["key"]: s for s in fn["sites"] if s not in nb}
            pairs = list(zip(ob, nb)) + [(s, nkeys[s["key"]]) for s in fo["sites"]
                                         if s not in ob and s["key"] in nkeys]
            lo = carry_lines(old["functions"], fo, old_text.count("\n") + 1)
            ln = carry_lines(new["functions"], fn, new_text.count("\n") + 1)
            how, hdr_moved = "identifier renames only", False
            if not sites_match or not rename_equivalent(
                    [t for i, t in otoks if i in lo], [t for i, t in ntoks if i in ln],
                    lambda n: sym_addr(seg, n, a.rev), lambda n: sym_addr(seg, n, None)):
                how = "unrelated file-scope changes only"
                if not sites_match:
                    skipped.append(f"{path}: {fn['name']}: sites changed")
                    continue
                ocl = oscope.closure(body_names(onames, fo), pastes=True)
                ncl = nscope.closure(body_names(nnames, fn), pastes=True)
                paste = oscope.unbounded(ocl) or nscope.unbounded(ncl)
                if paste:
                    skipped.append(f"{path}: {fn['name']}: token-pasting macro {paste}: dependencies not tracked")
                    continue
                rnames = body_names(old["by_line"], fo)
                obody = [t for i, t in otoks if fo["line"] <= i <= fo["end"]]
                nbody = [t for i, t in ntoks if fn["line"] <= i <= fn["end"]]
                # a body differing only by renames of its own locals/params (each keeping its
                # type) is compared at file scope as REV's body: renamed names are never
                # file-scope (rename_equivalent rejects globals/functions), so the reach is the same
                body_renamed = len(obody) == len(nbody) and any(
                    x.spelling != y.spelling for x, y in zip(obody, nbody)) and rename_equivalent(
                    obody, nbody, lambda n: sym_addr(seg, n, a.rev), lambda n: sym_addr(seg, n, None))
                if body_renamed:
                    ncl = params_renamed(ocl, ncl, fo["name"], fn["name"])
                moved, why = scope_equivalent(
                    path, obody, obody if body_renamed else nbody, ocl, ncl, oscope, nscope,
                    rev=(old["scope"], old["scope"].closure(rnames, pastes=True)))
                if moved is None:
                    # renamed fields of a reached record only resolve in REV's text against REV's
                    # headers: compare that parse of the body with HEAD's (identical, or renaming
                    # names), and every declaration the body reaches (the .c's own ones too, so unused
                    # file-scope text may differ) modulo the renames
                    obt = [t for t in old["toks"] if fo["line"] <= t.location.line <= fo["end"]]
                    fwd = rename_map(obt, nbody, lambda n: sym_addr(seg, n, a.rev), lambda n: sym_addr(seg, n, None))
                    recs = None
                    if fwd is not None:
                        ocl = old["scope"].closure(rnames, pastes=True)
                        paste = old["scope"].unbounded(ocl)
                        recs, hmoved, hwhy = (None, None, f"token-pasting macro {paste}") if paste else header_renames(
                            path, old["scope"], ocl, nscope, nscope.closure(body_names(nnames, fn), pastes=True),
                            fwd, obt)
                        why = why or hwhy
                    if recs is None:
                        skipped.append(f"{path}: {fn['name']}: not a pure rename; body or a declaration it uses changed"
                                       + (f" ({why})" if why else ""))
                        continue
                    # every reached declaration unchanged apart from the renames: automatic results carry too
                    how = "; ".join((["renames"] if fwd else []) + (
                        ["record field renames: " + ", ".join(recs)] if recs else []) + sorted(set(hmoved.values()))) or how
                    moved, body_renamed, hdr_moved = {}, False, True
                if moved:
                    how = "; ".join(sorted({m for m in moved.values() if m}))
                    # the reached include/ declarations apart from the moved ones unchanged since REV:
                    # automatic results carry too
                    hdr_moved = old["scope"].fp_hdr2(rnames, fo["fp_hdr"], skip=moved) == nscope.fp_hdr2(
                        body_names(nnames, fn), fn["fp_hdr"], skip=moved)
                if body_renamed:
                    how = f"renames; {how}"
            vram, n0 = f"{fn['vram']:08X}", len(out)
            keys = [(None, None)] + [(so["key"], sn_) for so, sn_ in pairs]
            for okey, nsite in keys:
                evs = by_func[(seg, vram)] if okey is None else by_site.get(okey, [])
                newest = {}
                ofp = (fo["fp_local"], fo["fp_hdr"], fo.get("fp_hdr2"))
                for e in evs:  # newest by time, as `mark` reads them (carried events keep their `t`)
                    if e["fp_local"] == fo["fp_local"] and (e["method"] not in AUTO or hdr_fresh(e, ofp)):
                        if e["method"] not in newest or e["t"] >= newest[e["method"]]["t"]:
                            newest[e["method"]] = e
                for e in newest.values():
                    if e["method"] in AUTO and not hdr_fresh(e, (fn["fp_local"], fn["fp_hdr"], fn.get("fp_hdr2"))) \
                            and not (hdr_moved and e.get("fp_hdr2") is not None):
                        continue  # reached headers changed since REV, not compared: automatic results stay stale
                    c = dict(e, unit=a.unit, agent="carry", name=fn["name"], file=path, fp_local=fn["fp_local"],
                             fp_hdr=fn["fp_hdr"], fp_hdr2=fn.get("fp_hdr2"), site=nsite["key"] if nsite else None,
                             note=f"carried from {a.rev} ({how})"
                             + (f": {e['note']}" if e["note"] else ""))
                    out.append(c)
            if len(out) > n0:
                lines.append(f"{path}: {fn['name']}: {', '.join(sorted({e['method'] for e in out[n0:]}))} ({how})")
    return out, skipped, lines


CARVE_KIND = {CursorKind.FUNCTION_DECL: "prototype", CursorKind.MACRO_DEFINITION: "macro",
              CursorKind.TYPEDEF_DECL: "typedef", CursorKind.ENUM_DECL: "enum", CursorKind.VAR_DECL: "declaration"}


def record_type(cursors):
    """The record type a name's top-level CURSORS (`top_index`) define (struct/union definitions,
    typedefs of that record), or None when any of them is something else."""
    t = None
    for c in cursors:
        if c.kind in (CursorKind.STRUCT_DECL, CursorKind.UNION_DECL):
            u = c.type.get_canonical()
        elif c.kind == CursorKind.TYPEDEF_DECL:
            u = c.underlying_typedef_type.get_canonical()
        else:
            return None
        if u.kind != TypeKind.RECORD or (t is not None and u.spelling != t.spelling):
            return None
        t = u
    return t


SIZEOF = re.compile(r"\bsizeof\b")


def carve_changes(old_scope, new_scope, old_names, new_names, body):
    """(changed record names, None) when every declaration either version's closure reaches has the
    same text in both, or is a record whose layout, alignment and surviving field types are kept
    (`clint.layout_diff` with types: padding carved into named fields; a padding array shrunk around
    them, to a shorter array or to a scalar of its element type, only when neither BODY (the
    function's text) nor a reached declaration uses `sizeof`, and to a scalar only when neither
    accesses that field) or that only one version declares (a type introduced or dropped by such a
    carve); else (names so far, reason)."""
    ocl, ncl = old_scope.closure(old_names), new_scope.closure(new_names)
    changed, resized = [], []
    for name in sorted(set(ocl) | set(ncl)):
        ocur, ncur = old_scope.idx.get(name, []), new_scope.idx.get(name, [])
        ov = ocl[name] if name in ocl else old_scope.direct(name)[0] if ocur else None
        nv = ncl[name] if name in ncl else new_scope.direct(name)[0] if ncur else None
        if ov == nv:
            continue
        ot, nt = record_type(ocur), record_type(ncur)
        if (ocur and ot is None) or (ncur and nt is None):
            c = next((c for c in ocur + ncur if c.kind in CARVE_KIND), (ocur + ncur)[0])
            return changed, f"{CARVE_KIND.get(c.kind, 'record')} {name} changed"
        if ot is not None and nt is not None:
            lo, ln = clint.record_layout(ot), clint.record_layout(nt)
            if lo is None or ln is None:
                return changed, f"record {name} incomplete"
            diff = clint.layout_diff({name: lo}, {name: ln}, types=True, resized=resized)
            if diff:
                return changed, "layout changed: " + "; ".join(diff)
        changed.append(name)
    texts = [body] + [t for cl in (ocl, ncl) for v in cl.values() for _, t in v]
    if resized and any(SIZEOF.search(t) for t in texts):
        return changed, f"array {resized[0][0]}.{resized[0][1]} resized and sizeof reached"
    for rec, f, scalar in resized:
        if scalar and any(re.search(rf"(?:->|\.)\s*{f}\b", t) for t in texts):
            return changed, f"array {rec}.{f} became a scalar and is accessed"
    return changed, None


def _carve_job(job):
    """([dict(path, seg, name, vram, rev_fp, now_fp, keys, reason, how)], file-level skips) for every
    function of PATH whose fingerprints differ between REV (its text and HDRS) and the working tree."""
    path, seg, rev, hdrs, added = job
    r = subprocess.run(["git", "show", f"{rev}:{path}"], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        return [], []  # no events can be fresh at REV
    # warning sites stay out on both sides: retype (the warning method) is not carried here
    old = analyze(path, seg, text=r.stdout, hdrs=hdrs, keep=True, warnings=False)
    new = analyze(path, seg, keep=True, warnings=False)
    shadow = sorted({rel(i.include.name) for i in old["tu"].get_includes()} & added)
    if shadow:
        return [], [f"{path}: includes {shadow[0]} at {rev}, added since"]
    if old["errors"] > new["errors"]:
        return [], [f"{path}: more clang errors at {rev} (a header deleted since?)"]
    count = collections.Counter(f["name"] for f in old["functions"])
    by_name = {f["name"]: f for f in old["functions"] if count[f["name"]] == 1}
    res = []
    for fn in new["functions"]:
        fo = by_name.get(fn["name"])
        if fn["vram"] is None or fo is None or fo["vram"] not in (None, fn["vram"]):
            continue
        rev_fp = (fo["fp_local"], fo["fp_hdr"], fo["fp_hdr2"])
        now_fp = (fn["fp_local"], fn["fp_hdr"], fn["fp_hdr2"])
        if rev_fp == now_fp:
            continue
        reason, how = None, None
        if fo["fp_local"] != fn["fp_local"]:
            reason = "body or file-scope text changed (carry without --header-carve)"
        elif [s["key"] for s in fo["sites"]] != [s["key"] for s in fn["sites"]]:
            reason = "sites changed"
        else:
            onames, nnames = body_names(old["by_line"], fo), body_names(new["by_line"], fn)
            paste = old["scope"].pasted(old["scope"].closure(onames)) or new["scope"].pasted(
                new["scope"].closure(nnames))
            if paste:
                reason = f"token-pasting macro {paste}: dependencies not tracked"
            else:
                body = "\n".join(r.stdout.split("\n")[fo["line"] - 1:fo["end"]])
                changed, reason = carve_changes(old["scope"], new["scope"], onames, nnames, body)
                how = "header carve: " + (", ".join(changed) or "no reached declaration changed")
        res.append(dict(path=path, seg=seg, name=fn["name"], vram=fn["vram"], rev_fp=rev_fp, now_fp=now_fp,
                        keys=[s["key"] for s in fn["sites"]], reason=reason, how=how))
    return res, []


def carry_carves(a, by_site, by_func):
    """(events, skipped, carried lines) re-stamping the newest automatic-method events fresh at REV
    (REV's text of the file and REV's headers) of every function whose fp_local (so its body text)
    and site keys are unchanged and whose reached include/ declarations changed only by layout-
    keeping record carves (`carve_changes`). The other methods depend on fp_local alone and stay
    fresh by themselves. A function is listed as skipped only when it had something to carry."""
    hdrs = rev_headers(a.rev)
    added = {p for p, t in hdrs.items() if t is None}
    jobs = []
    for path in [rel(p) for p in a.files] or clint.src_files():
        text = open(os.path.join(ROOT, path), encoding="utf-8", errors="replace").read()
        if hdrs and set(included(text, os.path.dirname(path))) & set(hdrs):
            jobs.append((path, seg_of(path), a.rev, hdrs, added))
    if len(jobs) <= 2:
        results = [_carve_job(j) for j in jobs]
    else:
        with multiprocessing.get_context("spawn").Pool(min(os.cpu_count() or 4, len(jobs))) as pool:
            results = pool.map(_carve_job, jobs, chunksize=2)
    out, skipped, lines = [], [], []
    for res, skips in results:
        skipped += skips
        for r in res:
            if a.func and r["name"] not in a.func:
                continue
            vram, rev_fp, now_fp, carry = f"{r['vram']:08X}", r["rev_fp"], r["now_fp"], []
            for key in [None] + r["keys"]:
                evs = by_func[(r["seg"], vram)] if key is None else by_site.get(key, [])
                newest = {}
                for e in evs:  # newest by time, as `mark` reads them (carried events keep their `t`)
                    if e["method"] in AUTO and e["fp_local"] == rev_fp[0] and hdr_fresh(e, rev_fp):
                        if e["method"] not in newest or e["t"] >= newest[e["method"]]["t"]:
                            newest[e["method"]] = e
                for e in newest.values():
                    if any(x["method"] == e["method"] and x["t"] >= e["t"] and x["fp_local"] == now_fp[0]
                           and hdr_fresh(x, now_fp) for x in evs):
                        continue  # already fresh at HEAD (unaffected, or carried before)
                    carry.append(dict(e, unit=a.unit, agent="carry", file=r["path"], fp_local=now_fp[0],
                                      fp_hdr=now_fp[1], fp_hdr2=now_fp[2],
                                      note=f"carried from {a.rev} ({r['how']})"
                                      + (f": {e['note']}" if e["note"] else "")))
            if not carry:
                continue
            if r["reason"]:
                skipped.append(f"{r['path']}: {r['name']}: {r['reason']}")
                continue
            out += carry
            lines.append(f"{r['path']}: {r['name']}: {', '.join(sorted({e['method'] for e in carry}))} ({r['how']})")
    return out, skipped, lines


def cmd_carry(a):
    """Re-stamp results across renames and file-scope edits (`carry_renames`) or, with
    --header-carve, across layout-keeping header carves (`carry_carves`). Events keep their time,
    so knowledge filed after them still makes them stale."""
    by_site, by_func = index_events(load_events())
    out, skipped, lines = (carry_carves if a.header_carve else carry_renames)(a, by_site, by_func)
    for s in skipped:
        print(f"carry: skipped {s}")
    if a.dry_run:
        for line in lines:
            print(f"carry: would carry {line}")
        print(f"would carry {len(out)} events from {a.rev}")
        return
    if out:
        append_events(unit_events(a.unit, load_events()) + out)
    print(f"carried {len(out)} events from {a.rev} to {rel(LEDGER)}")


TEXT_ROWS = ["FAKE", *(f"FAKE {k}" for k in KINDS if k not in ("goto", "proto-type", "warning")), "LAYOUT", "ORIG",
             "goto", "proto-type"]
ROWS = TEXT_ROWS + ["protos mismatch", "sites open", "sites exhausted", "functions", "reviewed",
                    "exhausted functions", "uninit warnings", "cfe warnings", "func_ defs", "m2c names", "unk fields",
                    "D_ refs"]


def baseline(rev):
    tot = collections.Counter()
    with tempfile.TemporaryDirectory() as tmp:
        arc = subprocess.Popen(["git", "archive", rev, "src", "include"], cwd=ROOT, stdout=subprocess.PIPE)
        subprocess.run(["tar", "-x", "-C", tmp], stdin=arc.stdout, check=True)
        if arc.wait():
            sys.exit(f"quality: git archive {rev} failed")
        for root, _, names in os.walk(os.path.join(tmp, "src")):
            for n in names:
                p = os.path.join(root, n)
                if n.endswith(".c") and not os.path.relpath(p, tmp).startswith(os.path.join("src", "boot", "libultra")):
                    tot.update(text_metrics(open(p, encoding="utf-8", errors="replace").read()))
    return tot


def cmd_report(a):
    files = clint.src_files()
    ans = analyze_many(files, uninit=True)
    require_resolved(ans)
    by_site, by_func = index_events(load_events())
    cols = collections.defaultdict(collections.Counter)
    for an in ans:
        c = cols[an["seg"]]
        c.update(an["text"])
        c["uninit warnings"] += len(an["uninit"])
        c["cfe warnings"] += an["warnings"]
        for fn in an["functions"]:
            st = function_state(fn, by_site, by_func)
            m = fn["metrics"]
            c.update({"functions": 1, "reviewed": st["review"] == "✓", "exhausted functions": st["done"],
                      "sites open": len(st["open"]), "sites exhausted": len(st["sites"]) - len(st["open"]),
                      "func_ defs": m["func_name"], "m2c names": m["m2c_names"], "unk fields": m["unk_fields"],
                      "D_ refs": m["d_refs"]})
    r = subprocess.run([sys.executable, "tools/unit_check.py", "protos", *files], cwd=ROOT, capture_output=True,
                       text=True)
    for line in r.stdout.splitlines():
        m = re.match(r"src/(\w+)/[^:\s]+:\d+ ", line)
        if m:
            cols[m.group(1)]["protos mismatch"] += 1
    segs = sorted(cols, key=lambda s: (s not in ("boot", "global"), s != "boot", s))
    total = sum(cols.values(), collections.Counter())
    start = baseline(a.baseline) if a.baseline else None
    head = ["metric", *segs, "total"] + (["start"] if start is not None else [])
    body = [[row, *(str(cols[s][row]) for s in segs), str(total[row])]
            + ([str(start[row]) if row in TEXT_ROWS else "-"] if start is not None else []) for row in ROWS]
    if a.markdown:
        print("| " + " | ".join(head) + " |")
        print("|" + "|".join(["---"] + ["--:"] * (len(head) - 1)) + "|")
        for b in body:
            print("| " + " | ".join(b) + " |")
    else:
        w = [max(len(x[i]) for x in [head] + body) for i in range(len(head))]
        for b in [head] + body:
            print("  ".join(x.ljust(w[0]) if i == 0 else x.rjust(w[i]) for i, x in enumerate(b)))
    print(f"\nreviewed {total['reviewed']}/{total['functions']}")
    print(f"exhausted {total['exhausted functions']}/{total['functions']}")


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    s = p.add_subparsers(dest="cmd", required=True)
    c = s.add_parser("sweep")
    c.add_argument("files", nargs="+", type=cli_path)
    c.add_argument("-j", type=int, default=2)
    c.add_argument("--copy-of", type=cli_path)
    c.add_argument("--record", action="store_true")
    c.add_argument("--unit")
    c.set_defaults(fn=cmd_sweep)
    c = s.add_parser("record")
    c.add_argument("--unit", required=True)
    c.add_argument("--agent", required=True)
    c.add_argument("--base")
    c.add_argument("--batch", required=True)
    c.add_argument("--model", help="worker selector provider/model[:level], stored on every event")
    c.add_argument("--skip-missing", action="store_true",
                   help="drop lines whose site or function no longer exists instead of failing")
    c.add_argument("--dry-run", action="store_true")
    c.set_defaults(fn=cmd_record)
    c = s.add_parser("status")
    c.add_argument("--file", type=cli_path)
    c.add_argument("--func")
    c.set_defaults(fn=cmd_status)
    c = s.add_parser("rank")
    c.add_argument("--seg")
    c.add_argument("--limit", type=int)
    c.add_argument("--polish", action="store_true", help="file-level queue: functions without hack sites")
    c.set_defaults(fn=cmd_rank)
    c = s.add_parser("history")
    c.add_argument("func")
    c.add_argument("--file", type=cli_path)
    c.add_argument("--all", action="store_true", help="include sweep and carry events")
    c.set_defaults(fn=cmd_history)
    c = s.add_parser("report")
    c.add_argument("--baseline")
    c.add_argument("--markdown", action="store_true")
    c.set_defaults(fn=cmd_report)
    c = s.add_parser("carry")
    c.add_argument("--rev", required=True, help="commit before the renames / header carves")
    c.add_argument("--unit", required=True)
    c.add_argument("--header-carve", action="store_true",
                   help="carry automatic results across layout-keeping record carves in include/")
    c.add_argument("--dry-run", action="store_true", help="list what would be carried; write nothing")
    c.add_argument("--func", action="append", default=[], metavar="NAME",
                   help="only this function (REV's or HEAD's name; repeatable)")
    c.add_argument("files", nargs="*", type=cli_path)
    c.set_defaults(fn=cmd_carry)
    c = s.add_parser("backfill-models")
    c.add_argument("sessions", help="omp sessions directory of this checkout")
    c.add_argument("--dry-run", action="store_true")
    c.set_defaults(fn=cmd_backfill_models)
    c = s.add_parser("permute-candidates")
    c.add_argument("--max-base", type=int, required=True, help="sites whose best permute base score is <= N")
    c.add_argument("--out", required=True, help="new or empty directory")
    c.add_argument("--limit", type=int)
    c.set_defaults(fn=cmd_permute_candidates)
    a = p.parse_args(argv)
    try:
        a.fn(a)
    except cwarn.CompileError as ex:  # e.g. REV's text of a record --base / carry --rev file
        sys.exit(f"{a.cmd}: {ex}")


if __name__ == "__main__":
    main()
