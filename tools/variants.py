#!/usr/bin/env python3
"""Natural respellings ("recipes") of one function, scored against expected/: the shared tool for
trying candidate bodies instead of per-agent trial scripts. Run in the container (re-execs through
tools/dk on the host):

  tools/dk python3 tools/variants.py scan <copy.c> <src/seg/file.c> FUNC
        [--recipes truth,switch,branch,swap,arith,elem,float,width,declswap,splitlocal,unalias]
        [--max 120] [-j 2] [--out DIR] [--json FILE]
  tools/dk python3 tools/variants.py try <copy.c> <src/seg/file.c> FUNC BODY.c... [-j 2]

  scan   FUNC's definition in <copy.c> (plain, or parked under NON_MATCHING) is the start body. Each recipe
         makes one-edit variants of it, in this order, truncated to --max:
           truth     a truth test respelled inside a condition: `x != 0` <-> bare `x`, `x == 0` <-> `!x`
                     (operand a plain name/member/array element; only where the test is a whole operand
                     of `(`, `!`, `&&`, `||`): the same value, but cfe compares the variable itself instead
                     of a widened copy (Q1116/Q1066: 80150 tagBarrelCheckProximityAndFall lost its volatile)
           switch    `if (x == K) {A} else {B}` as `switch (x) { case K: A break; default: B break; }`, and an
                     `if (x == K) {...return;}` as a one-case switch (R3; no `break` in the bodies): the switch's
                     extra CFG node replaced dead tests in 70FD0 and 36880 (Q1589)
           branch    `if (C) {A} else {B}` with its arms swapped: `if (!(C)) {B} else {A}`, and for a single
                     `==`/`!=` test the inverse operator instead of `!(...)` (block order and branch sense;
                     actorMoveWithinZone: a real if/else replaced `if (0) {}` + `do {} while (0)`)
           swap      a comparison mirrored, `a < b->c` -> `b->c > a` (== and != keep their operator); only
                     where both operands are plain names/members/array elements/literals bounded by
                     lower-precedence operators, so the meaning never changes
           arith     a commutative operand pair swapped, `a + b` -> `b + a`, `a * b` -> `b * a` (plain operands
                     bounded by lower-precedence operators; never after `-`, `/`, `%` or a same-level operator
                     whose associativity would regroup it): cfe keeps the source operand order (Q0171)
           elem      an array element's member respelled `X[i].f` -> `(X + i)->f` / `(&X[i])->f` and back
                     (the same address; base-first vs index-first sums, Q0813)
           float     a float literal with its `f` suffix dropped, or added when the value is exact in f32
           width     a single-declarator local of s8/u8/s16/u16/s32/u32/int/unsigned int as each of the others
                     (`int` and `long` (s32) differ in IDO's cfe: Q0128 menu/E550 maxLevel)
           declswap  two adjacent lines of the leading declaration block swapped
           splitlocal  (lines tagged `// FAKE` only) one local serving two roles split in two: from a tagged
                     plain assignment `X = ...;` (or, for a tagged declaration of X, from each plain assignment
                     after X's first) to the line before X's next plain assignment, X becomes a new local
                     X_<n> (smallest unused n >= 2) declared at every slot of the declaration block; only
                     when an untagged line in that range reads X (else it would just rename a steer)
           unalias   (lines tagged `// FAKE` only) a redundant alias `A = B;` / `T *A = B;` of a local A
                     deleted, A respelled B up to the next plain assignment of A or B; A's separate
                     declaration line deleted too once unused, and kept (a frame slot) in a second variant
         splitlocal/unalias drop the acted-on line's `// FAKE` comment and prove nothing: a rename across a
         loop back-edge is caught by the gates (fdiff --reloc-ok, clint uninit --base).
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
import argparse, itertools, json, os, re, struct, subprocess, sys, uuid
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
if __name__ == "__main__" and not os.path.exists("/opt/ido5.3"):
    sys.exit(subprocess.call([str(ROOT / "tools" / "dk"), "python3", "tools/variants.py"] + sys.argv[1:]))
sys.path.insert(0, str(ROOT / "tools"))
import deadsweep  # noqa: E402

RECIPES = ("truth", "switch", "branch", "swap", "arith", "elem", "float", "width", "declswap", "splitlocal", "unalias")
OPND = r"(?:[A-Za-z_]\w*(?:(?:->|\.)\w+|\[[^\]\[]*\])*|0x[0-9A-Fa-f]+[uUlL]*|-?\d+(?:\.\d+)?[fFuUlL]*)"
OPND_END = re.compile(OPND + r"(?=\s*$)")
OPND_START = re.compile(r"\s*(" + OPND + r")")
CMP = re.compile(r"==|!=|<=|>=|<|>")
MIRROR = {"<": ">", ">": "<", "<=": ">=", ">=": "<=", "==": "==", "!=": "!="}
FLOAT = re.compile(r"(?<![\w.])(\d+\.\d*)(f?)(?![\w.])")
WIDTHS = ("s8", "u8", "s16", "u16", "s32", "u32", "int", "unsigned int")
WIDTH = re.compile(r"^(\s*)(s8|u8|s16|u16|s32|u32|unsigned int|int)(\s+)([A-Za-z_]\w*)(\s*(?:=[^;]*)?;.*)$")
ARITH = re.compile(r"[+*]")
# what may precede / follow `a + b` (resp. `a * b`) without regrouping it: lower-precedence operators only
ARITH_BEFORE = ("(", ",", ";", "{", "}", "?", ":", "&&", "||", "|", "^", "==", "!=", "<", ">", "<=", ">=")
ARITH_AFTER = (")", ",", ";", "?", ":", "&", "|", "^", "==", "!=", "<", ">")
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


def decl_block(lines):
    """(o, j): LINES[o] is the function's opening `{` line (the first ending in `{` at paren depth 0),
    LINES[o + 1:j] its leading declaration block; None without an opening line."""
    paren = 0
    for o, line in enumerate(lines):
        c = deadsweep.code_of(line)
        paren += c.count("(") - c.count(")")
        if paren == 0 and c.endswith("{"):
            break
    else:
        return None
    j = o + 1
    while j < len(lines) and deadsweep.DECL.fullmatch(deadsweep.code_of(lines[j])):
        j += 1
    return o, j


def gen_declswap(text):
    lines = text.split("\n")
    if not (b := decl_block(lines)):
        return []
    o, j = b
    out = []
    for i in range(o + 1, j - 1):
        new = lines[:i] + [lines[i + 1], lines[i]] + lines[i + 2:]
        out.append(("declswap", f"lines {i + 1}-{i + 2}: `{lines[i].strip()}` <-> `{lines[i + 1].strip()}`",
                    "\n".join(new)))
    return out


# a single-declarator local: indent, type text (pointer stars kept), name, array suffix, initialiser
TYPE = r"(?:[A-Za-z_]\w*\s+)*[A-Za-z_]\w*[\s*]+?"
LOCAL = re.compile(r"^(\s*)(" + TYPE + r"\**)([A-Za-z_]\w*)(\[[^\]]*\])?\s*(=[^;]*)?;\s*$")
ALIAS = re.compile(r"^\s*(?!(?:return|goto|else|case|do)\b)(" + TYPE + r"\**)?([A-Za-z_]\w*)\s*=\s*([A-Za-z_]\w*)\s*;\s*$")


def _name(x):
    """X as a whole identifier, not a member (`p->x`, `s.x`)."""
    return re.compile(r"(?<![\w.])(?<!->)" + re.escape(x) + r"(?!\w)")


def _assigns(x):
    """A plain assignment to X starting a line's code (never `==` or a compound `+=`)."""
    return re.compile(r"^\s*" + re.escape(x) + r"\s*=(?!=)")


def _unfake(code, cm):
    """CODE with comment CM minus its `// FAKE...` part (other comment text before it kept)."""
    rest = re.sub(r"\s*(?://\s*)?FAKE\b.*$", "", cm).rstrip()
    return code.rstrip() + (" " + rest if rest.strip("/ \t") else "")


def _top_comma(s):
    depth = 0
    for ch in s:
        depth += ch in "([{"
        depth -= ch in ")]}"
        if ch == "," and depth == 0:
            return True
    return False


def _rename(lines, lo, hi, rx, new):
    """LINES with RX replaced by NEW in the code part of lines LO..HI (literal lines left unchanged)."""
    out = list(lines)
    for i in range(lo, hi + 1):
        sc = split_code(out[i])
        if sc:
            out[i] = rx.sub(new, sc[0]) + sc[1]
    return out


def _code(line):
    return line.split("//")[0]


def gen_splitlocal(text):
    """One local serving two roles split in two: from a FAKE-tagged plain assignment `X = ...;` (or, for a
    FAKE-tagged declaration of X, from each later plain assignment after the first) to the line before the
    next plain assignment of X, X becomes a new local X_n declared at each slot of the declaration block."""
    lines = text.split("\n")
    if not (b := decl_block(lines)):
        return []
    o, j = b
    decls = {}  # name -> (line index, indent, type text)
    for i in range(o + 1, j):
        sc = split_code(lines[i])
        m = sc and LOCAL.match(sc[0])
        if not m or m.group(4) or (m.group(5) and (_top_comma(m.group(5)) or _name(m.group(3)).search(m.group(5)))):
            continue
        decls[m.group(3)] = (i, m.group(1), m.group(2))
    out = []
    for n, line in enumerate(lines):
        sc = split_code(line)
        if not sc or "FAKE" not in sc[1]:
            continue
        m = re.match(r"^\s*([A-Za-z_]\w*)\s*=(?!=)", sc[0])
        if m and m.group(1) in decls and n >= j:
            x, starts = m.group(1), [n]
        else:
            x = next((k for k, d in decls.items() if d[0] == n), None)
            if x is None:
                continue
            asg = [i for i in range(j, len(lines)) if _assigns(x).match(_code(lines[i]))]
            starts = [i for i in asg[1:] if split_code(lines[i])]
        d, ind, typ = decls[x]
        k = next(k for k in itertools.count(2) if not re.search(rf"\b{re.escape(x)}_{k}\b", text))
        xn = f"{x}_{k}"
        for s in starts:
            e = next((i - 1 for i in range(s + 1, len(lines)) if _assigns(x).match(_code(lines[i]))), len(lines) - 1)
            if not any((c := split_code(lines[i])) and "FAKE" not in c[1] and _name(x).search(c[0])
                       for i in range(s + 1, e + 1)):
                continue  # the new local would be read only by tagged lines: a renamed steer, not a split
            new = _rename(lines, s, e, _name(x), xn)
            new[n] = _unfake(*split_code(new[n]))
            for p in range(j - o):
                out.append(("splitlocal", f"line {n + 1}: {x} -> new local {xn} from line {s + 1} (decl slot {p})",
                            "\n".join(new[:o + 1 + p] + [f"{ind}{typ}{xn};"] + new[o + 1 + p:])))
    return out


def gen_unalias(text):
    """A FAKE-tagged alias `A = B;` (or `T *A = B;`) of a local A removed, A respelled B up to the next
    plain assignment of A or B; A's separate declaration line deleted once unused (a variant keeping it,
    for its frame slot, when that differs)."""
    lines = text.split("\n")
    b = decl_block(lines)
    decls = {}
    for i in range(b[0] + 1, b[1]) if b else ():
        sc = split_code(lines[i])
        if sc and (m := LOCAL.match(sc[0])) and not m.group(4):
            decls.setdefault(m.group(3), i)
    out = []
    for n, line in enumerate(lines):
        sc = split_code(line)
        if not sc or "FAKE" not in sc[1] or not (m := ALIAS.match(sc[0])):
            continue
        typ, a, bb = m.groups()
        if a == bb or (not typ and a not in decls):
            continue
        stop = re.compile(r"^\s*(?:" + re.escape(a) + "|" + re.escape(bb) + r")\s*=(?!=)")
        e = next((i - 1 for i in range(n + 1, len(lines)) if stop.match(_code(lines[i]))), len(lines) - 1)
        new = _rename(lines, n + 1, e, _name(a), bb)
        keep = [l for i, l in enumerate(new) if i != n]
        d = None if typ else decls.get(a)
        texts = []
        if d is not None and not any(_name(a).search(_code(l)) for i, l in enumerate(new) if i not in (n, d)):
            texts.append("\n".join(l for i, l in enumerate(new) if i not in (n, d)))
        texts.append("\n".join(keep))
        for t in dict.fromkeys(texts):
            out.append(("unalias", f"line {n + 1}: alias {a} = {bb} removed, {a} -> {bb} to line {e + 1}", t))
    return out


TRUTH_CMP = re.compile(r"(\s*)(" + OPND + r")\s*(!=|==)\s*0(?![\w.xX])(?=\s*(?:\)|&&|\|\|))")
TRUTH_BARE = re.compile(r"(\s*)(!?)(" + OPND + r")(?=\s*(?:\)|&&|\|\|))")


def bool_context(pre):
    """Whether an operand right after PRE is read only for its truth: an operand of `&&`/`||`, or the whole
    test of an `if (`/`while (` or of `!(`/`&&(`/`||(` (never a call argument, cast or arithmetic paren)."""
    p = pre.rstrip()
    return p.endswith(("&&", "||")) or bool(re.search(r"(?:\b(?:if|while)\s*|!\s*|&&\s*|\|\|\s*)\($", p))


def gen_truth(text):
    out, lines = [], text.split("\n")
    for n, line in enumerate(lines):
        sc = split_code(line)
        if not sc or not re.search(r"\b(?:if|while)\s*\(|&&|\|\|", sc[0]):
            continue
        code, cm = sc
        for pat in (TRUTH_CMP, TRUTH_BARE):
            for m in pat.finditer(code):
                if not bool_context(code[:m.start()]):
                    continue
                if m.start() and (code[m.start() - 1].isalnum() or code[m.start() - 1] in "_.>]"):
                    continue  # the match starts inside a longer operand
                if pat is TRUTH_CMP:
                    rep = m.group(1) + ("" if m.group(3) == "!=" else "!") + m.group(2)
                else:
                    if re.fullmatch(r"-?\d.*|0x.*", m.group(3)):
                        continue  # a literal (`if (1)`): no variable to compare
                    rep = m.group(1) + m.group(3) + (" == 0" if m.group(2) else " != 0")
                new = code[:m.start()] + rep + code[m.end():]
                out.append(("truth", f"line {n + 1}: `{m.group().strip()}` -> `{rep.strip()}`",
                            "\n".join(lines[:n] + [new + cm] + lines[n + 1:])))
    return out


SWITCH_IF = re.compile(r"^(\s*)if \((" + OPND + r") == (-?(?:0x[0-9A-Fa-f]+|\d+))\) \{\s*(?://.*)?$")


def _block_end(lines, i, indent):
    """Index of the line closing the block opened at line I: the first later line starting with INDENT + `}`."""
    for k in range(i + 1, len(lines)):
        s = lines[k]
        if s.startswith(indent + "}"):
            return k
        if s.strip() and len(s) - len(s.lstrip()) <= len(indent):
            return None  # at or below the if's indent without its `}`: not a well-formed block
    return None


def gen_switch(text):
    """`if (x == K) { A } else { B }` -> `switch (x) { case K: A break; default: B break; }`, and when A ends in
    `return`, `if (x == K) { A }` -> `switch (x) { case K: A }` (one-case selector switch, ruling R3): the switch's
    extra CFG node lowers loop constants / splits blocks where a dead test did (Q1589; 70FD0
    actorUpdateNodePositions, 36880 modelSlotResolveAssetTextures)."""
    out, lines = [], text.split("\n")
    for i, line in enumerate(lines):
        m = SWITCH_IF.match(line)
        if not m:
            continue
        ind, x, k = m.groups()
        j = _block_end(lines, i, ind)
        if j is None:
            continue
        body_a = [("    " + l if l.strip() else l) for l in lines[i + 1:j]]
        if any(re.search(r"\bbreak\b", l.split("//")[0]) for l in lines[i + 1:j]):
            continue  # a `break` would leave the switch instead of the enclosing loop
        if lines[j].strip() == "} else {":
            e = _block_end(lines, j, ind)
            if e is None or lines[e].strip() != "}":
                continue
            body_b = [("    " + l if l.strip() else l) for l in lines[j + 1:e]]
            if any(re.search(r"\bbreak\b", l.split("//")[0]) for l in lines[j + 1:e]):
                continue
            new = ([f"{ind}switch ({x}) {{", f"{ind}    case {k}:"] + body_a + [f"{ind}        break;", f"{ind}    default:"]
                   + body_b + [f"{ind}        break;", f"{ind}}}"])
            out.append(("switch", f"line {i + 1}: if ({x} == {k}) / else -> switch", "\n".join(lines[:i] + new + lines[e + 1:])))
        elif lines[j].strip() == "}" and j > i + 1 and lines[j - 1].strip().startswith("return"):
            new = [f"{ind}switch ({x}) {{", f"{ind}    case {k}:"] + body_a + [f"{ind}}}"]
            out.append(("switch", f"line {i + 1}: if ({x} == {k}) {{ ... return; }} -> one-case switch",
                        "\n".join(lines[:i] + new + lines[j + 1:])))
    return out


BRANCH_IF = re.compile(r"^(\s*)if \((.*)\) \{\s*(?://.*)?$")


def _balanced(s):
    depth = 0
    for ch in s:
        depth += {"(": 1, ")": -1}.get(ch, 0)
        if depth < 0:
            return False
    return depth == 0


def _negate(c):
    """C negated: `!x` -> `x`, a single `a == b` / `a != b` with the inverse operator, else `!(C)`."""
    m = re.fullmatch(r"!\s*(" + OPND + r")", c)
    if m:
        return m.group(1)
    m = re.fullmatch(r"(" + OPND + r")\s*(==|!=)\s*(" + OPND + r")", c)
    if m:
        return f"{m.group(1)} {'!=' if m.group(2) == '==' else '=='} {m.group(3)}"
    return f"!({c})"


def gen_branch(text):
    """`if (C) {A} else {B}` -> `if (<not C>) {B} else {A}`: block order and branch sense of a branch the
    function already has (an else-if chain or an arm ending in its own `else` stays untouched)."""
    out, lines = [], text.split("\n")
    for i, line in enumerate(lines):
        m = BRANCH_IF.match(line)
        if not m or line.lstrip().startswith("}") or not _balanced(m.group(2)):
            continue
        ind, c = m.group(1), m.group(2).strip()
        j = _block_end(lines, i, ind)
        if j is None or lines[j].strip() != "} else {":
            continue
        e = _block_end(lines, j, ind)
        if e is None or lines[e].strip() != "}":
            continue
        new = [f"{ind}if ({_negate(c)}) {{"] + lines[j + 1:e] + [f"{ind}}} else {{"] + lines[i + 1:j] + [f"{ind}}}"]
        out.append(("branch", f"line {i + 1}: if ({c}) arms swapped", "\n".join(lines[:i] + new + lines[e + 1:])))
    return out


def gen_arith(text):
    """`a + b` -> `b + a`, `a * b` -> `b * a` for plain operands whose neighbours bind less tightly, so the
    expression tree keeps its shape (left associativity: an operator of the same level may follow, never
    precede)."""
    out, lines = [], text.split("\n")
    for n, line in enumerate(lines):
        sc = split_code(line)
        if not sc or deadsweep.DECL.fullmatch(deadsweep.code_of(line)):
            continue
        code, cm = sc
        for m in ARITH.finditer(code):
            op, i, j = m.group(), m.start(), m.end()
            if (i and code[i - 1] in "+*/=") or (j < len(code) and code[j] in "+*=/"):
                continue  # ++, +=, *=, comments
            if (i and code[i - 1] == " ") != (j < len(code) and code[j] == " "):
                continue  # `u8 *p`, `x = *p`: a declarator or a dereference, not a binary operator
            a, b = OPND_END.search(code[:i]), OPND_START.match(code, j)
            if not a or not b:
                continue
            p, s = code[:a.start()].rstrip(), code[b.end(1):].lstrip()
            before = (not p or p.endswith(ARITH_BEFORE) or re.search(r"\breturn$", p)
                      or (p.endswith("=") and p[-2:-1] not in "=!<>")
                      or (op == "*" and p.endswith(("+", "-")) and not p.endswith(("++", "--"))))
            after = not s or s.startswith(ARITH_AFTER) or (s[0] in "+-" and s[:2] not in ("++", "--", "->")) or (
                op == "*" and s[0] in "*/%")
            if not before or not after:
                continue
            new = code[:a.start()] + b.group(1) + code[a.end():i] + op + code[j:b.start(1)] + a.group() + code[b.end(1):]
            out.append(("arith", f"line {n + 1}: `{code[a.start():b.end(1)].strip()}` operands swapped",
                        "\n".join(lines[:n] + [new + cm] + lines[n + 1:])))
    return out


ELEM_IDX = re.compile(r"(?<![\w.>\]])([A-Za-z_]\w*)\[([^\[\]]+)\]\.(\w+)")
ELEM_PTR = re.compile(r"\((&?)([A-Za-z_]\w*)(?:\[([^\[\]]+)\]| \+ ([^()]+))\)->(\w+)")


def gen_elem(text):
    """An array element's member respelled: `X[i].f` -> `(X + i)->f` / `(&X[i])->f`, and those back to
    `X[i].f` (the same address; cfe builds base-first or index-first sums differently, Q0813)."""
    out, lines = [], text.split("\n")
    for n, line in enumerate(lines):
        sc = split_code(line)
        if not sc:
            continue
        code, cm = sc
        reps = []
        for m in ELEM_IDX.finditer(code):
            x, i, f = m.groups()
            isum = i if re.fullmatch(OPND, i.strip()) else f"({i})"  # `X + a ? b : c` would regroup
            reps += [(m, f"({x} + {isum})->{f}"), (m, f"(&{x}[{i}])->{f}")]
        for m in ELEM_PTR.finditer(code):
            amp, x, idx, add, f = m.groups()
            if (amp and idx is not None) or (not amp and add is not None):
                reps.append((m, f"{x}[{idx if idx is not None else add}].{f}"))
        for m, rep in reps:
            new = code[:m.start()] + rep + code[m.end():]
            out.append(("elem", f"line {n + 1}: `{m.group()}` -> `{rep}`", "\n".join(lines[:n] + [new + cm] + lines[n + 1:])))
    return out


GENERATORS = {"swap": gen_swap, "float": gen_float, "width": gen_width, "declswap": gen_declswap, "truth": gen_truth,
              "switch": gen_switch, "branch": gen_branch, "arith": gen_arith, "elem": gen_elem,
              "splitlocal": gen_splitlocal, "unalias": gen_unalias}


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
