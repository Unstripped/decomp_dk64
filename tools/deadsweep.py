#!/usr/bin/env python3
"""Dead-statement sweep for IDO 5.3 near-misses (stage 5-6: scheduling / register allocation).

Dead statements such as `if (D_8004BC84 == 0) {}` emit no code but change uopt's live ranges and
candidate priorities. This tool compiles a REDUCED TU (the copy's head, with every other function body
turned into a prototype and NON_MATCHING branches resolved to their C side, plus FUNC's body), scores
FUNC against expected/ and greedily inserts dead statements. Run in the container:

  tools/dk python3 tools/deadsweep.py score <copy.c> <src/seg/file.c> FUNC [--body F] [--diff]
  tools/dk python3 tools/deadsweep.py sweep <copy.c> <src/seg/file.c> FUNC [--body F] [--rounds N]
        [--forms F...] [--extra SYM...] [--shape-w W] [-j N] [--out DIR]

  <copy.c>  private copy of the file (.scratch/<you>/...). FUNC is taken from it: plain C or C parked under
            `#ifdef NON_MATCHING` (the park's externs/#defines stay in the head). --body F replaces the body
            (function definition text) at the position of FUNC's definition or GLOBAL_ASM pragma in the copy.
  <src>     the original src file: `make -n -W` gives compiler + flags, expected/build/<src>.o the target.
  score     diff sizes of FUNC vs the expected object (`error` on `cfe: Error`, never a stale object): SequenceMatcher
            hunks (max(del, ins)) over `objdump -dr` text, branch/jump targets -> L, `N(at)` -> X(at), padding after
            the last `jr ra` + delay slot dropped, data relocations normalised (section/rodata-defined symbols ->
            .rodata, D_/jtbl_ address names + LO16 immediate -> @ADDR) so own-data differences do not count.
              full = instructions + relocations   text = instructions only
              reloc = relocations only            shape = full with registers masked to R
  sweep     greedy rounds: each inserts ONE of `if (G && G) {}`, `if (G == 0) {}`, `if (G) {}`, `if (G != 0) {}`
            (arrays: `if (G) {}`) at every statement boundary of the current body for every global FUNC uses
            (scalar/pointer externs of the head found in the body, `D_xxxxxxxx` names, names inside used #defines,
            --extra SYM) and keeps the lowest full + shape-w * shape (default 0.25). Stops when a round does not
            improve, at text == 0 (the floor: code identical; leftover reloc lines are printed) or after --rounds
            (default 8). --forms replaces the forms (`@` = each symbol; without `@` once per position). Bodies go
            to --out (default .scratch/deadsweep/out/FUNC): roundN.c per improvement, best.c = last.
  -j N      parallel compiles (default 2). Scratch files: .scratch/deadsweep/<uuid>/ (removed on exit);
            identical object code is scored once. Results are search hints: review before porting.
"""
import argparse, atexit, difflib, hashlib, os, re, shlex, shutil, subprocess, sys, uuid
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
if not os.path.exists("/opt/ido5.3"):
    sys.exit(subprocess.call([str(ROOT / "tools" / "dk"), "python3", "tools/deadsweep.py"] + sys.argv[1:]))

MARK = "/*@@DEADSWEEP_FUNC@@*/"
SCALAR = set("s8 s16 s32 s64 u8 u16 u32 u64 f32 f64 int char short long float double unsigned signed".split())
FORMS = ["if (@ && @) {}", "if (@ == 0) {}", "if (@) {}", "if (@ != 0) {}"]
REG = re.compile(r"\$?\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|gp|k[01]|fp|f\d+)\b")
DECL = re.compile(r"(?!(?:return|goto|else|case|break|continue|do|default)\b)[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*[\s*]\s*\**"
                  r"[A-Za-z_]\w*(?:\[[^\]]*\])*\s*(?:=[^;]*)?(?:,\s*\**\w+(?:\[[^\]]*\])*)*;")
TOK = re.compile(r"""/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|^[ \t]*\#(?:\\\n|[^\n])*|[{};()]|[^{};()"'/#\n]+|.""", re.S | re.M)

# ---- source handling ------------------------------------------------------------------------
def skip_block(text, i):
    """text[i] == '{': index just past the matching '}' (comments, strings, preprocessor lines skipped)."""
    depth = 0
    for m in TOK.finditer(text, i):
        depth += {"{": 1, "}": -1}.get(m.group(), 0)
        if depth == 0:
            return m.end()
    raise ValueError("unbalanced braces")

def resolve_nm(text, func):
    """Keep the C side of every NON_MATCHING conditional, drop GLOBAL_ASM pragmas (FUNC's becomes MARK).
    Returns (text, set of line numbers inside a NON_MATCHING branch)."""
    out, parked, stack = [], set(), []  # stack entries: [is_nm, active]
    for l in text.split("\n"):
        m = re.match(r"\s*#\s*(ifdef|ifndef|if|else|elif|endif)\b\s*(.*)", l)
        if m:
            d, arg = m.group(1), m.group(2).strip()
            nm = arg == "NON_MATCHING" or (d == "if" and re.fullmatch(r"defined\s*\(\s*NON_MATCHING\s*\)", arg))
            if d in ("if", "ifdef", "ifndef"):
                stack.append([nm, d != "ifndef"])
                if nm:
                    continue
            elif d == "else" and stack and stack[-1][0]:
                stack[-1][1] = not stack[-1][1]
                continue
            elif d == "endif" and stack and stack.pop()[0]:
                continue
        if not all(a for nm, a in stack if nm):
            continue
        if re.match(r"\s*(#\s*pragma\s+GLOBAL_ASM|INCLUDE_ASM)", l):
            if re.search(r"\b%s\b" % re.escape(func), l):
                out.append(MARK)
            continue
        if any(nm for nm, _ in stack):
            parked.add(len(out))
        out.append(l)
    return "\n".join(out), parked

def strip_bodies(text):
    """Top-level function bodies -> ';' (static/inline ones kept); everything else unchanged."""
    out, i, mark, last = [], 0, 0, ""
    while i < len(text):
        m = TOK.match(text, i)
        t, i = m.group(), m.end()
        if t == "{":
            j = skip_block(text, m.start())
            drop = last == ")" and not re.search(r"\b(static|inline)\b", "".join(out[mark:]))
            out.append(";" if drop else text[m.start():j])
            i, mark, last = j, len(out), ""
            continue
        out.append(t)
        if t == ";" or t.lstrip().startswith("#"):
            mark, last = len(out), ""
        elif t.strip() and not t.startswith(("/*", "//")):
            last = t.strip()[-1]
    return "".join(out)

def find_def(text, func):
    """(start, end) of FUNC's definition incl. a return type on the previous line, or None."""
    pat = re.compile(r"(?m)^((?:[A-Za-z_]\w*(?:[ \t]+|(?=\*))|\*+[ \t]*)*)%s\s*\([^;{}]*\)\s*\{" % re.escape(func))
    for m in pat.finditer(text):
        if re.search(r"\b(return|else|if|while|for|do|case)\b", m.group(1)):
            continue
        start = m.start()
        prev = text.rfind("\n", 0, max(start - 1, 0)) + 1
        if not m.group(1) and re.fullmatch(r"[A-Za-z_][\w \t*]*", text[prev:start].strip()):
            start = prev
        return start, skip_block(text, m.end() - 1)
    return None

def load(copy, func, body_file):
    """(head, body, parked) of the reduced TU."""
    text, parked = resolve_nm(Path(copy).read_text(), func)
    d = find_def(text, func)
    if d:
        start, body, is_parked = d[0], text[d[0]:d[1]] + "\n", text.count("\n", 0, d[0]) in parked
    elif MARK in text:
        start, body, is_parked = text.index(MARK), None, False
    else:
        sys.exit(f"error: {func} not found in {copy} (no definition, no GLOBAL_ASM pragma)")
    if body_file:
        body = Path(body_file).read_text()
    if body is None:
        sys.exit(f"error: {func} is only a GLOBAL_ASM pragma in {copy}; pass --body")
    return strip_bodies(text[:start]), body, is_parked

# ---- compile + score ------------------------------------------------------------------------
def compile_flags(src):
    """(cc, flags) exactly as make compiles src (asm-processor wrapper unwrapped, like permute.py)."""
    p = subprocess.run(["make", "-n", "-W", str(src), f"build/{str(src)[:-2]}.o"], cwd=ROOT, capture_output=True, text=True)
    for line in p.stdout.splitlines():
        t = shlex.split(line)
        ci = next((i for i, x in enumerate(t) if re.fullmatch(r"/opt/ido[0-9.]+/cc", x)), None)
        if ci is None:
            continue
        rest = t[len(t) - t[::-1].index("--"):] if "--" in t else t[ci + 1:]
        flags = [x for k, x in enumerate(rest) if x != "-o" and not x.endswith(".c") and rest[k - 1:k] != ["-o"]]
        return t[ci], flags
    sys.exit(f"error: no compile rule found for {src} (make -n)")

def objdump(obj, *opts):
    return subprocess.run(["mips-linux-gnu-objdump", *opts, str(obj)], capture_output=True, text=True).stdout.splitlines()

def dis(obj, func):
    """[(is_reloc, normalised text)] for FUNC up to the delay slot of its last `jr ra`.
    HI16/LO16 relocations: section symbols and symbols defined in rodata -> `.rodata`; address-named symbols
    (D_8004A308, jtbl_..., L...) plus the LO16 instruction's immediate -> `@ADDR`."""
    syms = {t[-1]: t[-3] for t in (l.split() for l in objdump(obj, "-t")) if len(t) > 3 and re.match(r"[0-9a-f]{8}$", t[0])}
    items, on = [], False
    for l in objdump(obj, "-dr", "--no-show-raw-insn"):
        m = re.match(r"^[0-9a-f]+ <(.+)>:$", l)
        if m:
            on = m.group(1) == func
        elif on and (m := re.match(r"^\s*[0-9a-f]+:\s+R_MIPS_(\w+)\s+([^+\s]+)(?:\+0x([0-9a-f]+))?", l)):
            items.append((True, m.group(1), m.group(2), int(m.group(3) or "0", 16)))
        elif on and (m := re.match(r"^\s*[0-9a-f]+:\s+(.*)$", l)):
            t = re.sub(r"\s+", " ", re.sub(r"[\s,][0-9a-f]+ <[^>]*>", " L", m.group(1)).strip())
            items.append((False, re.sub(r"-?\d+\(at\)", "X(at)", t)))
    imm = re.compile(r"(-?\d+)(?=\(\w+\)$)|(?<=,)(-?\d+)$")

    def addr(k):  # absolute address behind reloc k, adding the LO16 instruction's immediate
        _, ty, sym, add = items[k]
        m = imm.search(items[k - 1][1]) if ty == "LO16" else None
        return int(sym[-8:], 16) + add + (int(m.group(1) or m.group(2)) if m else 0)

    res = []
    for k, it in enumerate(items):
        if not it[0]:
            res.append(it)
            continue
        _, ty, sym, add = it
        sec = sym if sym.startswith(".") else syms.get(sym, "")
        addrname = ty in ("HI16", "LO16") and re.match(r"(?:D|jtbl|L|jpt)_?[0-9A-F]{8}$", sym)
        if not ("rodata" in sec or sym.startswith(".") or addrname):
            res.append((True, f"R {ty} {sym}" + (f"+0x{add:x}" if add else "")))
            continue
        if ty == "LO16":
            res[-1] = (False, imm.sub("X", res[-1][1]))
        j = k if ty == "LO16" else next((j for j in range(k + 1, len(items)) if items[j][0] and items[j][1:3] == ("LO16", sym)), k)
        res.append((True, f"R {ty} " + (".rodata" if "rodata" in sec else sym if sym.startswith(".") else f"@{addr(j):08X}")))
    last = max((i for i, (r, t) in enumerate(res) if not r and t == "jr ra"), default=len(res) - 2)
    end = last + 2
    while end < len(res) and res[end][0]:
        end += 1
    return res[:end]

def sdiff(a, b):
    if a == b:
        return 0
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    return sum(max(i2 - i1, j2 - j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != "equal")

class Scorer:
    def __init__(self, copy, src, func, body_file, shape_w):
        self.func, self.shape_w, self.cache = func, shape_w, {}
        self.head, self.body0, self.parked = load(copy, func, body_file)
        exp = ROOT / "expected" / "build" / (str(src)[:-2] + ".o")
        if not exp.exists():
            sys.exit(f"error: {exp} not found (run make expected)")
        self.exp = dis(exp, func)
        if not self.exp:
            sys.exit(f"error: {func} not in {exp}")
        self.cc, self.flags = compile_flags(src)
        self.dir = ROOT / ".scratch" / "deadsweep" / uuid.uuid4().hex
        self.dir.mkdir(parents=True)
        atexit.register(shutil.rmtree, self.dir, ignore_errors=True)

    def evaluate(self, body):
        """dict(full, text, reloc, shape, key, n, lines) or dict(err=..., key=inf)."""
        base = self.dir / uuid.uuid4().hex
        c, o = f"{base}.c", f"{base}.o"
        Path(c).write_text(self.head + "\n" + body + "\n")
        try:
            r = subprocess.run([self.cc] + self.flags + ["-o", o, c], cwd=ROOT, capture_output=True, text=True, timeout=300)
            msg = r.stdout + r.stderr
            if r.returncode or "cfe: Error" in msg or not os.path.exists(o):
                return {"err": next((x for x in msg.splitlines() if "Error" in x), msg.strip()[-200:]).strip(), "key": float("inf")}
            got = dis(o, self.func)
        finally:
            for f in (c, o):
                if os.path.exists(f):
                    os.remove(f)
        if not got:
            return {"err": "function not in object", "key": float("inf")}
        h = hashlib.sha1("\n".join(t for _, t in got).encode()).hexdigest()
        if h not in self.cache:
            e, g = self.exp, got
            txt = lambda x, want=None, mask=False: [REG.sub("R", t) if mask else t for r, t in x if want is None or r == want]
            full, shape = sdiff(txt(e), txt(g)), sdiff(txt(e, mask=True), txt(g, mask=True))
            self.cache[h] = {"full": full, "shape": shape, "key": full + self.shape_w * shape, "n": len(g), "lines": txt(g),
                             "text": sdiff(txt(e, False), txt(g, False)), "reloc": sdiff(txt(e, True), txt(g, True))}
        return self.cache[h]

# ---- sweep ----------------------------------------------------------------------------------
def code_of(l):
    return re.sub(r'"(\\.|[^"\\])*"|\'(\\.|[^\'\\])*\'', '""', l).split("//")[0].strip()

def points(lines):
    """Line indices after which a dead statement may be inserted: statement boundaries outside parentheses
    from the end of the declarations to before the function's closing brace."""
    paren = 0
    for open_idx, l in enumerate(lines):
        paren += code_of(l).count("(") - code_of(l).count(")")
        if paren == 0 and code_of(l).endswith("{"):
            break
    else:
        sys.exit("error: could not find the function's opening brace in the body")
    j = open_idx + 1
    while j < len(lines) and (not code_of(lines[j]) or DECL.fullmatch(code_of(lines[j]))):
        j += 1
    last, pts, paren = max(i for i, l in enumerate(lines) if code_of(l)), [j - 1], 0
    for i in range(j, last):
        s = code_of(lines[i])
        paren += s.count("(") - s.count(")")
        nxt = code_of(lines[i + 1])
        if paren == 0 and s and not s.startswith("#") and (s.endswith((";", "{", ":")) or s == "}") \
                and not nxt.startswith(("else", "} else", "while")):
            pts.append(i)
    return pts

def symbols(head, body, extra):
    """[(name, is_array)] of globals FUNC uses."""
    decl = {}
    for m in re.finditer(r"\bextern\s+([^;()]*?)(\w+)\s*(\[[^\]]*\])?\s*;", head + "\n" + body):
        words = re.findall(r"\w+", m.group(1))
        decl[m.group(2)] = (bool(m.group(3)), "*" in m.group(1) or (bool(words) and words[-1] in SCALAR))
    ids = set(re.findall(r"[A-Za-z_]\w*", body))
    for m in re.finditer(r"#define\s+(\w+)\s+(.*)", head):
        if m.group(1) in ids:
            ids |= set(re.findall(r"[A-Za-z_]\w*", m.group(2)))
    names = {n for n in decl if n in ids and decl[n][1]} | {n for n in ids if re.fullmatch(r"D_[0-9A-F]{8}", n)} | set(extra)
    return [(n, decl.get(n, (False, True))[0]) for n in sorted(names)]

def make_variants(lines, syms, forms, default):
    """[(line, symbol, form)]; the default forms are reduced to `if (@) {}` for arrays."""
    plain, templ, out = [f for f in forms if "@" not in f], [f for f in forms if "@" in f], []
    for p in points(lines):
        out += [(p, "", f) for f in plain]
        for name, arr in syms:
            out += [(p, name, f) for f in (["if (@) {}"] if arr and default else templ)]
    return out

def insert(lines, p, name, form):
    ind = re.match(r"\s*", lines[p]).group(0) + ("    " if code_of(lines[p]).endswith(("{", ":")) else "")
    return "\n".join(lines[:p + 1] + [ind + form.replace("@", name)] + lines[p + 1:])

def cmd_score(a):
    s = Scorer(a.copy, a.src, a.func, a.body, 0.25)
    r = s.evaluate(s.body0)
    if "err" in r:
        print(f"{a.func}: error: {r['err']}")
        return 2
    print(f"{a.func}{' (parked)' if s.parked and not a.body else ''}: full={r['full']} text={r['text']} reloc={r['reloc']} "
          f"shape={r['shape']} (expected {len(s.exp)} lines, got {r['n']})")
    if a.diff:
        print("\n".join(difflib.unified_diff([t for _, t in s.exp], r["lines"], "expected", "got", lineterm="", n=2)))
    return 0

def cmd_sweep(a):
    s = Scorer(a.copy, a.src, a.func, a.body, a.shape_w)
    out = Path(a.out or ROOT / ".scratch" / "deadsweep" / "out" / a.func)
    out.mkdir(parents=True, exist_ok=True)
    body, cur = s.body0, s.evaluate(s.body0)
    if "err" in cur:
        print(f"error: start body does not compile: {cur['err']}")
        return 2
    syms = symbols(s.head, body, a.extra or [])
    row = lambda r: f"{r['full']:>5} {r['text']:>5} {r['reloc']:>5} {r['shape']:>5}"
    print(f"{a.func}: {len(syms)} symbols: {' '.join(n for n, _ in syms)}")
    print(f"round  full  text reloc shape  inserted (line in new body, after which line)\n{0:>5} {row(cur)}  (start body)", flush=True)
    (out / "round0.c").write_text(body)
    with ThreadPoolExecutor(a.jobs) as ex:
        for rd in range(1, a.rounds + 1):
            if cur["text"] == 0:
                break
            lines = body.split("\n")
            vs = make_variants(lines, syms, a.forms or FORMS, not a.forms)
            res = list(ex.map(lambda v: s.evaluate(insert(lines, *v)), vs))
            bi = min(range(len(vs)), key=lambda i: (res[i]["key"], i), default=None)
            nerr = sum(1 for r in res if "err" in r)
            if bi is None or res[bi]["key"] >= cur["key"]:
                print(f"round {rd}: {len(vs)} variants ({nerr} errors), no improvement; stop")
                break
            p, name, f = vs[bi]
            body, cur, stmt = insert(lines, p, name, f), res[bi], f.replace("@", name)
            prev = next(l.strip() for l in reversed(lines[:p + 1]) if l.strip())
            print(f"{rd:>5} {row(cur)}  `{stmt}` at line {p + 2} after `{prev[:50]}` ({len(vs)} variants, {nerr} errors)", flush=True)
            for n in (f"round{rd}.c", "best.c"):
                (out / n).write_text(f"// deadsweep round {rd}: full={cur['full']} text={cur['text']} inserted `{stmt}` at line {p + 2}\n{body}")
    if cur["text"] == 0:
        print(f"floor: instruction text identical to expected; remaining reloc diff lines: {cur['reloc']}")
    print(f"best body: {out / 'best.c'}" if (out / "best.c").exists() else "no improving statement found")
    return 0

def main():
    ap = argparse.ArgumentParser(description="dead-statement sweep (see the module docstring)")
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name in ("score", "sweep"):
        p = sub.add_parser(name)
        p.add_argument("copy")
        p.add_argument("src")
        p.add_argument("func")
        p.add_argument("--body")
        if name == "score":
            p.add_argument("--diff", action="store_true")
        else:
            p.add_argument("--rounds", type=int, default=8)
            p.add_argument("--forms", nargs="+")
            p.add_argument("--extra", nargs="+")
            p.add_argument("--shape-w", type=float, default=0.25)
            p.add_argument("-j", "--jobs", type=int, default=2)
            p.add_argument("--out")
    a = ap.parse_args()
    sys.exit(cmd_score(a) if a.cmd == "score" else cmd_sweep(a))

if __name__ == "__main__":
    main()
