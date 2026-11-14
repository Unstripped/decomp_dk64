#!/usr/bin/env python3
"""Natural respellings ("recipes") of one function, scored against expected/: the shared tool for
trying candidate bodies instead of per-agent trial scripts. Run in the container (re-execs through
tools/dk on the host):

  tools/dk python3 tools/variants.py scan <copy.c> <src/seg/file.c> FUNC [--recipes swap,float,width,declswap]
        [--max 120] [-j 2] [--out DIR] [--json FILE]
  tools/dk python3 tools/variants.py try <copy.c> <src/seg/file.c> FUNC BODY.c... [-j 2]

  scan   FUNC's definition in <copy.c> (plain, or parked under NON_MATCHING) is the start body. Each recipe
         makes one-edit variants of it, in this order, truncated to --max:
           swap      a comparison mirrored, `a < b->c` -> `b->c > a` (== and != keep their operator); only
                     where both operands are plain names/members/array elements/literals bounded by
                     lower-precedence operators, so the meaning never changes
           float     a float literal with its `f` suffix dropped, or added when the value is exact in f32
           width     a single-declarator local of s8/u8/s16/u16/s32/u32 as each of the other five types
           declswap  two adjacent lines of the leading declaration block swapped
         Prints the baseline, then `full text reloc recipe desc` per variant (deadsweep score's measures;
         `err` on a cfe error), best first. A variant with full == 0 is written into a whole-file copy
         DIR/zero_<n>.c (default DIR .scratch/variants/<seg>_<FUNC>_<uuid8>) and printed as
         `ZERO <path> <recipe> <desc>` (`ZERO (not written: parked) ...` for a parked body). --json writes
         [{recipe, desc, full, text, reloc, path}]. A zero is a candidate: gate it with tools/fdiff.sh
         --reloc-ok and clint uninit like any edit.
  try    scores each BODY.c (a full function definition) in place of FUNC's:
         `<file> full= text= reloc= shape=`.
Edits touch only the code part of a line (before `//`); preprocessor lines and lines with string or
character literals are left alone.
"""
import argparse, json, os, re, struct, subprocess, sys, uuid
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
if __name__ == "__main__" and not os.path.exists("/opt/ido5.3"):
    sys.exit(subprocess.call([str(ROOT / "tools" / "dk"), "python3", "tools/variants.py"] + sys.argv[1:]))
sys.path.insert(0, str(ROOT / "tools"))
import deadsweep  # noqa: E402

RECIPES = ("swap", "float", "width", "declswap")
OPND = r"(?:[A-Za-z_]\w*(?:(?:->|\.)\w+|\[[^\]\[]*\])*|0x[0-9A-Fa-f]+[uUlL]*|-?\d+(?:\.\d+)?[fFuUlL]*)"
OPND_END = re.compile(OPND + r"(?=\s*$)")
OPND_START = re.compile(r"\s*(" + OPND + r")")
CMP = re.compile(r"==|!=|<=|>=|<|>")
MIRROR = {"<": ">", ">": "<", "<=": ">=", ">=": "<=", "==": "==", "!=": "!="}
FLOAT = re.compile(r"(?<![\w.])(\d+\.\d*)(f?)(?![\w.])")
WIDTHS = ("s8", "u8", "s16", "u16", "s32", "u32")
WIDTH = re.compile(r"^(\s*)(s8|u8|s16|u16|s32|u32)(\s+)([A-Za-z_]\w*)(\s*(?:=[^;]*)?;.*)$")
# tokens that may precede / follow `a OP b` without binding tighter than the comparison
BEFORE = ("(", ",", ";", "{", "}", "?", ":", "&&", "||", "|", "^")
AFTER = (")", ",", ";", "?", ":", "&", "|", "^")


def split_code(line):
    """(code, comment) of LINE, or None when it is a preprocessor line or holds a string/char literal."""
    if line.lstrip().startswith("#") or '"' in line.split("//")[0] or "'" in line.split("//")[0]:
        return None
    i = line.find("//")
    return (line, "") if i < 0 else (line[:i], line[i:])


def _before_ok(pre, op):
    p = pre.rstrip()
    if not p or p.endswith(BEFORE) or re.search(r"\breturn$", p):
        return True
    if p.endswith("&"):  # binary & only (an operand before it), never address-of
        return bool(re.search(r"[\w)\]]\s*&$", p))
    if p.endswith("=") and (len(p) < 2 or p[-2] not in "=!<>"):
        return True  # assignment
    return op in ("<", ">", "<=", ">=") and p.endswith(("==", "!="))  # `x == a < b`: (a < b) binds first


def _after_ok(post, op):
    s = post.lstrip()
    if not s or s.startswith(AFTER):
        return True
    return op in ("<", ">", "<=", ">=") and s.startswith(("==", "!="))


def gen_swap(text):
    out, lines = [], text.split("\n")
    for n, line in enumerate(lines):
        sc = split_code(line)
        if not sc:
            continue
        code, cm = sc
        for m in CMP.finditer(code):
            op, i, j = m.group(), m.start(), m.end()
            if (i and code[i - 1] in "<>=!-") or (j < len(code) and code[j] in "<>="):
                continue  # shifts, ->, and the halves of longer operators
            a, b = OPND_END.search(code[:i]), OPND_START.match(code, j)
            if not a or not b:
                continue
            a_s, b_s, b_e = a.start(), b.start(1), b.end(1)
            if not _before_ok(code[:a_s], op) or not _after_ok(code[b_e:], op):
                continue
            new = (code[:a_s] + code[b_s:b_e] + code[a.end():i] + MIRROR[op] + code[j:b_s] + a.group()
                   + code[b_e:])
            out.append(("swap", f"line {n + 1}: `{code[a_s:b_e].strip()}` -> `{new[a_s:b_e].strip()}`",
                        "\n".join(lines[:n] + [new + cm] + lines[n + 1:])))
    return out


def gen_float(text):
    out, lines = [], text.split("\n")
    for n, line in enumerate(lines):
        sc = split_code(line)
        if not sc:
            continue
        code, cm = sc
        for m in FLOAT.finditer(code):
            lit, f = m.group(1), m.group(2)
            if f:
                rep = lit
            else:
                v = float(lit)
                if struct.unpack("f", struct.pack("f", v))[0] != v:
                    continue
                rep = lit + "f"
            new = code[:m.start()] + rep + code[m.end():]
            out.append(("float", f"line {n + 1}: `{m.group()}` -> `{rep}`",
                        "\n".join(lines[:n] + [new + cm] + lines[n + 1:])))
    return out


def gen_width(text):
    out, lines = [], text.split("\n")
    for n, line in enumerate(lines):
        m = WIDTH.match(line)
        if not m or line.lstrip().startswith("#"):
            continue
        for t in WIDTHS:
            if t != m.group(2):
                new = m.group(1) + t + m.group(3) + m.group(4) + m.group(5)
                out.append(("width", f"line {n + 1}: `{m.group(4)}` {m.group(2)} -> {t}",
                            "\n".join(lines[:n] + [new] + lines[n + 1:])))
    return out


def gen_declswap(text):
    lines, paren = text.split("\n"), 0
    for o, line in enumerate(lines):
        c = deadsweep.code_of(line)
        paren += c.count("(") - c.count(")")
        if paren == 0 and c.endswith("{"):
            break
    else:
        return []
    j = o + 1
    while j < len(lines) and deadsweep.DECL.fullmatch(deadsweep.code_of(lines[j])):
        j += 1
    out = []
    for i in range(o + 1, j - 1):
        new = lines[:i] + [lines[i + 1], lines[i]] + lines[i + 2:]
        out.append(("declswap", f"lines {i + 1}-{i + 2}: `{lines[i].strip()}` <-> `{lines[i + 1].strip()}`",
                    "\n".join(new)))
    return out


GENERATORS = {"swap": gen_swap, "float": gen_float, "width": gen_width, "declswap": gen_declswap}


def variants(text, recipes=RECIPES, max_n=None):
    """[(recipe, desc, new_text)] of TEXT (a function definition), in RECIPES order, at most MAX_N."""
    out = [v for r in RECIPES if r in recipes for v in GENERATORS[r](text)]
    return out[:max_n] if max_n is not None else out


def cmd_scan(a):
    recipes = [r for r in a.recipes.split(",") if r]
    bad = [r for r in recipes if r not in RECIPES]
    if bad:
        print(f"error: unknown recipe {','.join(bad)} (one of {','.join(RECIPES)})")
        return 2
    s = deadsweep.Scorer(a.copy, a.src, a.func, None, 0.25)
    base = s.evaluate(s.body0)
    if "err" in base:
        print(f"{a.func}: error: start body does not compile: {base['err']}")
        return 2
    print(f"{a.func}{' (parked)' if s.parked else ''}: baseline full={base['full']} text={base['text']} "
          f"reloc={base['reloc']}")
    vs = variants(s.body0, recipes, a.max)
    with ThreadPoolExecutor(a.jobs) as ex:
        res = list(ex.map(lambda v: s.evaluate(v[2]), vs))
    order = sorted(range(len(vs)), key=lambda i: (res[i]["key"], i))
    print(f"{len(vs)} variants\n {'full':>5} {'text':>5} {'reloc':>5}  recipe  desc")
    for i in order:
        r = res[i]
        nums = f"{'err':>5} {'':>5} {'':>5}" if "err" in r else f"{r['full']:>5} {r['text']:>5} {r['reloc']:>5}"
        print(f" {nums}  {vs[i][0]}  {vs[i][1]}")
    seg = Path(a.src).parts[1] if len(Path(a.src).parts) > 2 else "src"
    out = Path(a.out) if a.out else ROOT / ".scratch" / "variants" / f"{seg}_{a.func}_{uuid.uuid4().hex[:8]}"
    copy_text, body = Path(a.copy).read_text(), s.body0.rstrip("\n")
    rows, nz = [], 0
    for i in order:
        r, (recipe, desc, text) = res[i], vs[i]
        path = None
        if r.get("full") == 0:
            if s.parked or body not in copy_text:
                print(f"ZERO (not written: parked) {recipe} {desc}")
            else:
                nz += 1
                out.mkdir(parents=True, exist_ok=True)
                path = out / f"zero_{nz}.c"
                path.write_text(copy_text.replace(body, text.rstrip("\n"), 1))
                path = os.path.relpath(path.resolve(), ROOT)  # ROOT-relative: the same on the host
                print(f"ZERO {path} {recipe} {desc}")
        rows.append(dict(recipe=recipe, desc=desc, full=r.get("full"), text=r.get("text"), reloc=r.get("reloc"),
                         path=path))
    if a.json:
        Path(a.json).write_text(json.dumps(rows, indent=1) + "\n")
    return 0


def cmd_try(a):
    s = deadsweep.Scorer(a.copy, a.src, a.func, a.bodies[0], 0.25)
    with ThreadPoolExecutor(a.jobs) as ex:
        res = list(ex.map(lambda b: s.evaluate(Path(b).read_text()), a.bodies))
    for b, r in zip(a.bodies, res):
        print(f"{b} error: {r['err']}" if "err" in r else
              f"{b} full={r['full']} text={r['text']} reloc={r['reloc']} shape={r['shape']}")
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name in ("scan", "try"):
        p = sub.add_parser(name)
        p.add_argument("copy")
        p.add_argument("src")
        p.add_argument("func")
        p.add_argument("-j", "--jobs", type=int, default=2)
        if name == "scan":
            p.add_argument("--recipes", default=",".join(RECIPES))
            p.add_argument("--max", type=int, default=120)
            p.add_argument("--out")
            p.add_argument("--json")
        else:
            p.add_argument("bodies", nargs="+")
    a = ap.parse_args(argv)
    return cmd_scan(a) if a.cmd == "scan" else cmd_try(a)


if __name__ == "__main__":
    sys.exit(main())
