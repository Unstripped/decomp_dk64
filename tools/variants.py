#!/usr/bin/env python3
"""Natural respellings ("recipes") of one function, scored against expected/: the shared tool for
trying candidate bodies instead of per-agent trial scripts. Run in the container (re-execs through
tools/dk on the host):

  tools/dk python3 tools/variants.py scan <copy.c> <src/seg/file.c> FUNC
        [--recipes truth,switch,branch,swap,arith,elem,float,width,declswap,splitlocal,unalias]
        [--max 120] [-j 2] [--out DIR] [--json FILE]
  tools/dk python3 tools/variants.py try <copy.c> <src/seg/file.c> FUNC BODY.c... [-j 2]

  scan   FUNC's definition in <copy.c> (plain, or parked under NON_MATCHING) is the start body. Each recipe
         makes one-edit variants of it, in this order, truncated to --max (0: every variant, as the recipe
         rung of tools/quality.py sweep scans):
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
                     `X = ...;` alone on its line whose tag names X (or, for a tagged declaration of X without
                     an initialiser, from each later store beginning a new role) to the line before X's next
                     store beginning a new role, a `for (X = ...)` header included, X becomes a new local
                     X_<n> (smallest unused n >= 2) declared at every slot of the declaration block. A store
                     whose right-hand side reads X (a clamp, an update), or a conditional one (if/else arm,
                     switch case, loop body) whose value merges with X's at a later read, refines the role in
                     place; an if/else or switch storing X on every path is one store. The start keeps
                     reading X on its right-hand side (`X_2 = f(X)`). Only when an untagged line of the range
                     reads X_<n> (else it renames a steer) and X keeps a store and an untagged read of its own,
                     the start's right-hand side included (else it renames every use of X); never for a name
                     declared again in a nested block
           unalias   (lines tagged `// FAKE` only) a redundant alias `A = B;` / `T *A = B;` of a local A
                     deleted, A respelled B up to the next store to A or B (`for` headers included); A's
                     separate declaration line deleted too once unused, and kept (a frame slot) in a second
                     variant. Only when an untagged line of that range reads A (else the deletion re-points
                     tagged readers at B, the steer unchanged); never when that store lies in a loop entered
                     in the range that reads A before it, or a nested block declares A or B
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
sys.path.insert(0, str(ROOT / "tools"))
from shadow import dk_argv  # noqa: E402

if __name__ == "__main__" and not os.path.exists("/opt/ido5.3"):
    sys.exit(subprocess.call(dk_argv("python3", "tools/variants.py", *sys.argv[1:])))
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


def _writes(code, x):
    """Whether CODE stores to X with a plain `=` (never `==` or a compound `+=`)."""
    return bool(re.search(r"(?<![\w.])(?<!->)" + re.escape(x) + r"\s*=(?!=)", code))


def _reads(code, x):
    """Whether CODE reads X: names it other than as the target of a plain `=`."""
    return bool(_name(x).search(re.sub(r"(?<![\w.])(?<!->)" + re.escape(x) + r"(?=\s*=(?!=))", "", code)))


CASE_LABEL = re.compile(r"(?:case\b[^:]*|default\s*):\s*")
BRACELESS = re.compile(r"(?:(?:else\s+)?if|for|while)\s*\(.*\)|else")


def _store(code, x):
    """The right-hand side of a plain store to X that starts CODE's statement (after a case label), or the
    initialiser of a `for (X = ...)` header; None for any other line (a one-line `if (c) X = v;` included)."""
    m = re.match(r"\s*(?:" + CASE_LABEL.pattern + r")?(?:for\s*\(\s*)?" + re.escape(x) + r"\s*=(?!=)([^;]*)", code)
    return m.group(1) if m else None


class _Blocks:
    """Brace structure of a function body (the lines after its opening line O). ctx[i]: keys of the constructs
    enclosing line I's code, outermost first (a line opening a block is outside it); kind[k]: `arm` (an if /
    else if / else arm, or the statement of a brace-less one), `case` (one case region of a switch body),
    `loop` (a for/while body), `do`, `switch` or `block`; inner[k]: the ctx of a line directly in K; own[k]:
    (first, last) line of K's own region; span[k]: (first, last) line of the whole statement (an if chain
    through its last arm, a case region's switch). An if chain or a switch is a record {first, last, arms (its
    arm / case keys), else (ends in `else` / has `default`)}: rec[k] of each member, opens[line], ends[line]."""
    COND = ("arm", "case", "loop")

    def __init__(self, lines, o):
        n = len(lines)
        self.ctx, self.kind, self.inner, self.span, self.own = [()] * n, {}, {}, {}, {}
        self.rec, self.opens, self._recs = {}, {}, []
        self._ids, self._stack, self._last = itertools.count(), [], None
        brace = None  # (kind, line) of a brace-less if/else/for/while waiting for its statement
        pre, paren = "", 0  # the statement text before a `{` (a `for (;;)` header or a condition across lines)
        for i in range(o + 1, n):
            c = "" if lines[i].lstrip().startswith("#") else deadsweep.code_of(lines[i])
            while paren == 0 and c.startswith("}"):
                self._close(i)
                c, pre = c[1:].lstrip(), ""
            top = self._stack[-1] if self._stack else None
            if paren == 0 and c and top and top["kind"] == "switch" and CASE_LABEL.match(c):
                if top["case"] is not None:
                    self.own[top["case"]] = (self.own[top["case"]][0], i - 1)
                top["case"] = self._key("case", top["line"], i)
                self._member(top["rec"], top["case"])
                top["rec"]["else"] |= c.startswith("default")
                self.inner[top["case"]] = self._keys()
            keys, over = list(self._keys()), None
            if brace and c:
                if c.startswith("{"):
                    over = brace
                else:
                    keys.append(self._key(brace[0], brace[1], i))
                brace = None
            self.ctx[i] = tuple(keys)
            for ch in c:
                if paren == 0 and ch in "{};":
                    if ch == "{":
                        self._open(pre, i, over)
                        over = None
                    elif ch == "}":
                        self._close(i)
                    pre = ""
                else:
                    paren += (ch == "(") - (ch == ")")
                    pre += ch
            pre += " "
            if BRACELESS.fullmatch(c) and _balanced(c):
                brace = ("loop" if c.startswith(("for", "while")) else "arm", i)
        while self._stack:  # a truncated body: close what is open
            self._close(n - 1)
        self.ends = {}
        for r in self._recs:
            if "last" in r:
                self.ends.setdefault(r["last"], []).append(r)

    def _keys(self):
        return tuple(k for f in self._stack for k in (f["key"], f["case"]) if k is not None)

    def _key(self, kind, first, last=None):
        k = next(self._ids)
        self.kind[k], self.own[k], self.span[k] = kind, (first, last), (first, last)
        return k

    def _member(self, rec, k):
        rec["arms"].append(k)
        self.rec[k] = rec

    def _open(self, pre, i, over):
        p = re.sub(r"^(?:(?:case\b[^:]*|[A-Za-z_]\w*)\s*:\s*)+", "", pre.strip())  # case and goto labels
        kind, line, rec, last = "block", i, None, self._last
        if over:
            kind, line = over
        elif re.match(r"if\b", p):
            kind = "arm"
        elif p.startswith("else"):
            kind = "arm"
            if last and last["kind"] == "arm" and last["depth"] == len(self._stack):
                rec = last["rec"]
        elif re.match(r"switch\b", p):
            kind = "switch"
        elif re.match(r"(?:for|while)\b", p):
            kind = "loop"
        elif re.match(r"do\b", p):
            kind = "do"
        if kind == "switch" or (kind == "arm" and rec is None):
            rec = self.opens[line] = {"first": line, "arms": [], "else": False}
            self._recs.append(rec)
        k = self._key(kind, line)
        if kind == "arm":
            self._member(rec, k)
            rec["else"] = bool(re.fullmatch(r"else", p))
        self.inner[k] = self._keys() + (k,)
        self._stack.append(dict(key=k, kind=kind, line=line, rec=rec, case=None, depth=len(self._stack)))

    def _close(self, i):
        if not self._stack:
            return
        f = self._last = self._stack.pop()
        self.own[f["key"]] = self.span[f["key"]] = (f["line"], i)
        if f["case"] is not None:
            self.own[f["case"]] = (self.own[f["case"]][0], i)
        if f["rec"]:
            f["rec"]["last"] = i
            for a in f["rec"]["arms"]:
                self.span[a] = (f["rec"]["first"], i)

    def conds(self, r, i):
        """The constructs enclosing line I but not line R that run conditionally (if/else arms, switch cases,
        loop bodies), outermost first."""
        return [k for k in self.ctx[i] if k not in self.ctx[r] and self.kind[k] in self.COND]

    def under(self, c, t):
        """Whether line T lies within each construct of C (a ctx): after a store under C, T sees its value."""
        return self.ctx[t][:len(c)] == c

    def sibling(self, i, t):
        """Whether line T lies in another arm of an if chain, or another case of a switch, that line I lies in."""
        g = [id(self.rec[k]) for k in self.ctx[i] if k in self.rec]
        return any(id(self.rec[k]) in g for k in self.ctx[t] if k in self.rec and k not in self.ctx[i])


class _Roles:
    """The roles of local X in a function body. A store to X begins a new role unless it refines the current
    one in place: its right-hand side reads X (a clamp or an update), or it runs conditionally (an if/else
    arm, a switch case, a loop body; a one-line `if (c) X = v;` is no store here at all) and its value merges
    with the current one at a later read. An if chain ending in `else` or a switch with `default` that stores X
    on every path counts as one store."""

    def __init__(self, st, code, x):
        self.st, self.code, self.x = st, code, x

    def _covers(self, rec):
        """Whether every arm (case) of REC stores X directly in it, or in such a nested statement (an empty
        case falls through to the next)."""
        st = self.st
        if not rec["else"]:
            return False
        for k in rec["arms"]:
            top = [w for w in range(st.own[k][0], st.own[k][1] + 1) if st.ctx[w] == st.inner[k]]
            if st.kind[k] == "case" and all(not self.code[w] or CASE_LABEL.fullmatch(self.code[w]) for w in top):
                continue
            if not any(_store(self.code[w], self.x) is not None or (w in st.opens and self._covers(st.opens[w]))
                       for w in top):
                return False
        return True

    def _reached(self, lines, i=None):
        """Whether one of LINES reads X before a store among them that it lies under. With I (escape scan from
        line I's store): lines in sibling regions of I's are skipped, and a store every path from I passes
        ends the scan."""
        st, kills = self.st, []  # ctx of each store passed: a line under one sees that store's value
        for t in lines:
            if i is not None and st.sibling(i, t):
                continue
            rhs = _store(self.code[t], self.x)
            if _reads(self.code[t] if rhs is None else rhs, self.x) and not any(st.under(c, t) for c in kills):
                return True
            new = [st.ctx[t]] if rhs is not None else []
            new += [st.ctx[r["first"]] for r in st.ends.get(t, ())
                    if (i is None or not any(k in st.ctx[i] for k in r["arms"])) and self._covers(r)]
            for c in new:
                if i is not None and st.under(c, i):
                    return False
                kills.append(c)
        return False

    def _lift(self, i, r):
        """(P, KS): line I's store lifted to the head of each innermost if chain / switch around it that
        stores X on every path and does not hold line R; KS: the conditional constructs around P but not R."""
        st, ks = self.st, self.st.conds(r, i)
        while ks and (rec := st.rec.get(ks[-1])) and not any(k in st.ctx[r] for k in rec["arms"]) \
                and self._covers(rec):
            i = rec["first"]
            ks = st.conds(r, i)
        return i, ks

    def begins(self, i, r, rhs_ok=False):
        """Whether the store to X at line I begins a new role after line R of the current role (RHS_OK: its
        right-hand side may read X, as a tagged start's does)."""
        st, rhs = self.st, _store(self.code[i], self.x)
        if rhs is None or (not rhs_ok and _reads(rhs, self.x)):
            return False
        for k in st.ctx[i]:  # a loop entered after R: its test, or a read before I, sees this value next time
            if k not in st.ctx[r] and st.kind[k] in ("loop", "do"):
                lo = st.span[k][0]
                if _reads(self.code[lo], self.x) or self._reached(range(lo + 1, i)):
                    return False
        p, ks = self._lift(i, r)  # entered conditionally: a new role only if no later read sees it merged
        return not ks or not self._reached(range(st.span[ks[-1]][1] + 1, len(self.code)), p)

    def end(self, s, r):
        """Last line of the role starting at line S after line R: the line before X's next store beginning a
        new role, at most the end of the innermost conditional region the role runs in (its value reaches no
        read outside it)."""
        ks = self._lift(s, r)[1]
        last = (self.st.own[ks[-1]][1] if ks else None) or len(self.code) - 1
        return next((i - 1 for i in range(s + 1, last + 1) if self.begins(i, s)), last)


def _rename_store(code, x, new):
    """CODE with X renamed NEW except in the right-hand side of its first plain store to X: `X = f(X);` ->
    `NEW = f(X);`, `for (X = a; X < b; X++)` -> `for (NEW = a; NEW < b; NEW++)`."""
    m = re.search(r"(?<![\w.])(?<!->)" + re.escape(x) + r"(?=\s*=(?!=))", code)
    k = code.find(";", m.end())
    k = len(code) if k < 0 else k
    return code[:m.start()] + new + code[m.end():k] + _name(x).sub(new, code[k:])


def _unfake(code, cm):
    """CODE with comment CM minus its `// FAKE...` part (other comment text before it kept)."""
    rest = re.sub(r"\s*(?://\s*)?FAKE\b.*$", "", cm).rstrip()
    return code.rstrip() + (" " + rest if rest.strip("/ \t") else "")


def _declares(code, x):
    """Whether CODE is a single-declarator declaration of a local named X."""
    return bool(deadsweep.DECL.fullmatch(code) and (m := LOCAL.match(code)) and m.group(3) == x)


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


def gen_splitlocal(text):
    """One local serving two roles split in two: from a FAKE-tagged `X = ...;` alone on its line whose tag
    names X (or, for a FAKE-tagged declaration of X without an initialiser, from each later store beginning a
    new role) to the line before X's next store beginning a new role (_Roles), X becomes a new local X_n
    declared at each slot of the declaration block; the start keeps reading X on its right-hand side. Only
    when an untagged line of the range reads X_n and X keeps a store and an untagged read of its own (else
    the split just renames a steer, or every use of X)."""
    lines = text.split("\n")
    if not (b := decl_block(lines)):
        return []
    o, j = b
    decls = {}  # name -> (line index, indent, type text, initialised)
    for i in range(o + 1, j):
        sc = split_code(lines[i])
        m = sc and LOCAL.match(sc[0])
        if not m or m.group(4) or (m.group(5) and (_top_comma(m.group(5)) or _name(m.group(3)).search(m.group(5)))):
            continue
        decls[m.group(3)] = (i, m.group(1), m.group(2), m.group(5) is not None)
    code = [deadsweep.code_of(l) for l in lines]
    for x in [x for x in decls if any(_declares(code[i], x) for i in range(j, len(lines)))]:
        del decls[x]  # declared again in a nested block: the name holds two variables
    st = _Blocks(lines, o)
    tagged = [bool((sc := split_code(l)) and "FAKE" in sc[1]) for l in lines]
    out = []
    for n, line in enumerate(lines):
        if not tagged[n]:
            continue
        m = re.fullmatch(r"([A-Za-z_]\w*)\s*=(?!=)[^;]*;", code[n])
        if m and m.group(1) in decls and n >= j:
            x = m.group(1)
            roles = _Roles(st, code, x)
            r = next((i for i in range(n - 1, o, -1) if _writes(code[i], x)), decls[x][0])
            if not _name(x).search(split_code(line)[1]) or not roles.begins(n, r, rhs_ok=True):
                continue  # the tag is about another construct, or the store refines X's role in place
            starts = [(n, r)]
        else:
            x = next((k for k, d in decls.items() if d[0] == n), None)
            if x is None or decls[x][3]:
                continue
            roles, starts = _Roles(st, code, x), []
            r = next((i for i in range(j, len(lines)) if _writes(code[i], x)), None)
            while r is not None and (s := next((i for i in range(r + 1, len(lines)) if roles.begins(i, r)), None)):
                starts.append((s, r))
                r = s
        _, ind, typ, init = decls[x]
        k = next(k for k in itertools.count(2) if not re.search(rf"\b{re.escape(x)}_{k}\b", text))
        xn = f"{x}_{k}"
        for s, r in starts:
            e = roles.end(s, r)
            if not any(not tagged[i] and _reads(code[i], x) for i in range(s + 1, e + 1)):
                continue  # the new local would be read only by tagged lines: a renamed steer, not a split
            own = [i for i in range(j, len(lines)) if not s <= i <= e]  # X's own lines after the declarations
            if not ((init or any(_writes(code[i], x) for i in own)) and (_reads(_store(code[s], x), x) or any(
                    not tagged[i] and _reads(code[i], x) for i in own))):
                continue  # X would keep no role of its own: the split renames every use of X
            if any(split_code(lines[i]) is None and _name(x).search(code[i]) for i in range(s, e + 1)):
                continue  # a literal line naming X is never renamed
            new = _rename(lines, s + 1, e, _name(x), xn)
            c, cm = split_code(new[s])
            new[s] = _rename_store(c, x, xn) + cm
            new[n] = _unfake(*split_code(new[n]))
            for p in range(j - o):
                out.append(("splitlocal", f"line {n + 1}: {x} -> new local {xn} from line {s + 1} (decl slot {p})",
                            "\n".join(new[:o + 1 + p] + [f"{ind}{typ}{xn};"] + new[o + 1 + p:])))
    return out


def gen_unalias(text):
    """A FAKE-tagged alias `A = B;` (or `T *A = B;`) of a local A removed, A respelled B up to the next
    store to A or B (_store); A's separate declaration line deleted once unused (a variant keeping it, for
    its frame slot, when that differs). Only when an untagged line of that range reads A (else the deletion
    re-points tagged readers at B, the steer unchanged), and not when that store lies in a loop entered within
    the range that reads A before it (its next iteration, or a `for` step, reads the stored value)."""
    lines = text.split("\n")
    b = decl_block(lines)
    decls = {}
    for i in range(b[0] + 1, b[1]) if b else ():
        sc = split_code(lines[i])
        if sc and (m := LOCAL.match(sc[0])) and not m.group(4):
            decls.setdefault(m.group(3), i)
    code, st = [deadsweep.code_of(l) for l in lines], _Blocks(lines, b[0]) if b else None
    out = []
    for n, line in enumerate(lines):
        sc = split_code(line)
        if not sc or "FAKE" not in sc[1] or not (m := ALIAS.match(sc[0])):
            continue
        typ, a, bb = m.groups()
        if a == bb or (not typ and a not in decls):
            continue
        e = next((i - 1 for i in range(n + 1, len(lines)) if _store(code[i], a) is not None
                  or _store(code[i], bb) is not None), len(lines) - 1)
        if not any((c := split_code(lines[i])) and "FAKE" not in c[1] and _reads(code[i], a) for i in range(n + 1, e + 1)):
            continue  # only tagged lines read A: the deletion re-points the steer at B, nothing more
        if any(_declares(code[i], a) or _declares(code[i], bb) for i in range(n + 1, e + 1)):
            continue  # a nested block declares its own A or B
        if st and e + 1 < len(lines) and any(_reads(code[t], a) for k in st.ctx[e + 1] if st.kind[k] in ("loop", "do")
                                             and n < st.span[k][0] <= e for t in range(st.span[k][0], e + 1)):
            continue
        new = _rename(lines, n + 1, e, _name(a), bb)
        keep = [l for i, l in enumerate(new) if i != n]
        d = None if typ else decls.get(a)
        texts = []
        if d is not None and not any(_name(a).search(deadsweep.code_of(l)) for i, l in enumerate(new) if i not in (n, d)):
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
    """[(recipe, desc, new_text)] of TEXT (a function definition), in RECIPES order, at most MAX_N (None or
    0: all)."""
    out = [v for r in RECIPES if r in recipes for v in GENERATORS[r](text)]
    return out[:max_n] if max_n else out


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
            p.add_argument("--max", type=int, default=120, help="score the first N variants (0: every one)")
            p.add_argument("--out")
            p.add_argument("--json")
        else:
            p.add_argument("bodies", nargs="+")
    a = ap.parse_args(argv)
    return cmd_scan(a) if a.cmd == "scan" else cmd_try(a)


if __name__ == "__main__":
    sys.exit(main())
