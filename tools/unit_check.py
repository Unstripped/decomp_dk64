#!/usr/bin/env python3
"""Host-side checks for one decomp unit (orchestrator bookkeeping; no build, no container).

  count <seg> [<file>...]          functions and instructions per still-asm file (asm/<seg>/<file>.s),
                                   or per GLOBAL_ASM function of src/<seg>/<file>.c when that exists
  handasm <seg> <file>...          64-bit ops / $k0 $k1 per asm file (non-zero: hand-written, not IDO C)
  empty-funcs <seg> <file>...      hidden empty functions: a `jr $ra` two instructions after the
                                   previous one and not a .L branch target (prints owner and address;
                                   owner == address is an already-symbolised empty function)
  boundaries <seg> <file>...       per asm file, functions that do not end in jr/j/b (fall into the next
                                   glabel: a spimdisasm split at a continuation label, fix with
                                   `size:` in the symbol file, or hand-written fall-through) and
                                   functions followed by 2+ nops before the next glabel (16-byte TU
                                   padding: a hidden TU boundary at the next function)
  coverage <src.c> <agent>=<f1>,<f2>... [...]
                                   every GLOBAL_ASM function of <src.c> in exactly one list; prints
                                   duplicates, unassigned functions and listed names that are not
                                   GLOBAL_ASM there; exit 1 on any
  left <src.c>...                  GLOBAL_ASM functions left, with the stage of their stored draft
                                   (`-` = no draft) and `parked` for #ifdef NON_MATCHING ones
  vanished [<rev>]                 src/ files changed since <rev> (default HEAD) whose count of
                                   function definitions + GLOBAL_ASM lines changed (a namer or
                                   merge that deleted a function); exit 1 on any
  pragma-tail <src.c>...           files ending in a #pragma GLOBAL_ASM directly after a function's
                                   closing `}`, or without a trailing newline (that file once built
                                   without its last function: undefined reference at link); exit 1
  drafts [--prune] <src.c>...      draft paths (drafts/<seg>/<FUNC>.c, existing or deleted) of the
                                   functions that are GLOBAL_ASM in these files at HEAD or now;
                                   --prune first deletes the drafts of those no longer GLOBAL_ASM
                                   (matched). Scope for merge_gate.sh --commit: other drafts stay
                                   untouched
  protos [--seg SEG] <src.c>...    file-scope function declarations whose return/param register class
                                   (u8/s8/u16/s16/32-bit/f32/f64/void) or arity differs from the C
                                   definition in src/ (same segment, else global/boot; SEG defaults to
                                   the path's src/<seg>/, else global: pass it for a private copy of an
                                   overlay file): callee-prototype levers for a caller's near-miss
                                   (informational, exit 0)
"""
import argparse
import glob
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INSN = re.compile(r"^\s*/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(\S+)(.*)$")
PRAGMA = re.compile(r'#pragma GLOBAL_ASM\("asm/(?:(\w+)/)?nonmatchings/[^"]*/(\w+)\.s"\)')
HANDASM = re.compile(r"\s(dmult|dmultu|ddiv|ddivu|ld|sd|daddu?|dsubu?|dsll|dsra|dsrl)\s|\$k[01]")


def asm_path(seg, f):
    f = f[:-2] if f.endswith(".s") else f
    return os.path.join(ROOT, "asm", seg, f + ".s") if seg != "boot" else os.path.join(ROOT, "asm", f + ".s")


def insns(path):
    """(glabel, address, mnemonic, operands, is_branch_target) per instruction."""
    g, target, out = None, False, []
    for line in open(path):
        if line.startswith("glabel "):
            g = line.split()[1]
            continue
        if re.match(r"^\s*\.L\w+:", line):
            target = True
            continue
        m = INSN.match(line)
        if m:
            addr = line.split()[2]
            out.append((g, addr, m.group(1), m.group(2), target))
            target = False
    return out


def cmd_count(a):
    for f in a.files or sorted(os.path.basename(p)[:-2] for p in glob.glob(os.path.join(ROOT, "asm", a.seg, "*.s"))):
        src = os.path.join(ROOT, "src", a.seg, f + ".c")
        if os.path.exists(src):
            total = 0
            for seg, func in PRAGMA.findall(open(src).read()):
                p = glob.glob(os.path.join(ROOT, "asm", seg or "", "nonmatchings", "*", f"{func}.s"))
                n = len(insns(p[0])) if p else 0
                total += n
                print(f"{n:6d} {func}")
            print(f"{total:6d} total {f}")
        else:
            ins = insns(asm_path(a.seg, f))
            print(f"{f} {len({i[0] for i in ins})} functions {len(ins)} insns")


def cmd_handasm(a):
    for f in a.files:
        n = sum(1 for line in open(asm_path(a.seg, f)) if INSN.match(line) and HANDASM.search(line))
        print(f"{n:6d} {f}")


def cmd_empty(a):
    for f in a.files:
        ins, last = insns(asm_path(a.seg, f)), None
        for i, (g, addr, mn, _, tgt) in enumerate(ins):
            if mn == "jr" and "$ra" in ins[i][3]:
                if last is not None and i - last == 2 and not tgt:
                    print(g, f"func_{addr}")
                last = i


def cmd_boundaries(a):
    for f in a.files:
        funcs = {}
        for g, _, mn, ops, _ in insns(asm_path(a.seg, f)):
            funcs.setdefault(g, []).append((mn, ops))
        names = list(funcs)
        for i, g in enumerate(names[:-1]):
            body = funcs[g]
            ends = [k for k, (mn, _) in enumerate(body) if mn in ("jr", "j", "b")]
            last = ends[-1] if ends else -1
            pad = body[last + 2:]
            if last < 0 or any(mn != "nop" for mn, _ in pad):
                print(f"{f} {g}: falls into {names[i + 1]}")
            elif len(pad) >= 2 and body[last][0] == "jr":
                print(f"{f} {g}: {len(pad)} trailing nops (TU padding: hidden TU at {names[i + 1]})")


def code_pragmas(text):
    """(seg, func) of GLOBAL_ASM pragmas holding code; data-only `.s` files (no glabel) are skipped."""
    out = []
    for seg, func in PRAGMA.findall(text):
        p = glob.glob(os.path.join(ROOT, "asm", seg or "", "nonmatchings", "*", f"{func}.s"))
        if p and "glabel" not in open(p[0]).read():
            continue
        out.append((seg, func))
    return out


def unmatched(src):
    return [func for _, func in code_pragmas(open(src).read())]


def cmd_coverage(a):
    left = unmatched(a.src)
    seen, bad = {}, False
    for spec in a.lists:
        agent, _, funcs = spec.partition("=")
        for fn in filter(None, funcs.split(",")):
            seen.setdefault(fn, []).append(agent)
    for fn, agents in seen.items():
        if len(agents) > 1:
            print(f"duplicate {fn}: {' '.join(agents)}"); bad = True
        if fn not in left:
            print(f"not GLOBAL_ASM in {a.src}: {fn} ({agents[0]})"); bad = True
    for fn in left:
        if fn not in seen:
            print(f"unassigned {fn}"); bad = True
    print("coverage OK" if not bad else "coverage FAILED")
    sys.exit(1 if bad else 0)


def cmd_left(a):
    for src in a.srcs:
        text = open(src).read()
        parked = set(re.findall(r"#ifdef NON_MATCHING.*?GLOBAL_ASM\(\"[^\"]*/(\w+)\.s\"\).*?#endif", text, re.S))
        for seg, func in code_pragmas(text):
            seg = seg or "boot"
            d = os.path.join(ROOT, "drafts", seg, func + ".c")
            stage = "-"
            if os.path.exists(d):
                m = re.search(r"stage\s*([0-9](?:\s*[-–]\s*[0-9])?)", open(d).readline(), re.I)
                stage = f"stage {m.group(1)}" if m else "draft (no stage)"
            print(f"{src} {func} {stage}{' parked' if func in parked else ''}")


def count_funcs(text):
    return len(re.findall(r"^[A-Za-z].*\) \{$|^#pragma GLOBAL_ASM", text, re.M))


def cmd_vanished(a):
    files = subprocess.run(["git", "diff", "--name-only", a.rev, "--", "src"], cwd=ROOT, capture_output=True, text=True, check=True).stdout.split()
    bad = False
    for f in files:
        if not f.endswith(".c") or not os.path.exists(os.path.join(ROOT, f)):
            continue
        old = subprocess.run(["git", "show", f"{a.rev}:{f}"], cwd=ROOT, capture_output=True, text=True)
        if old.returncode:
            continue
        o, n = count_funcs(old.stdout), count_funcs(open(os.path.join(ROOT, f)).read())
        if o != n:
            print(f"{f} {o} -> {n}"); bad = True
    print("vanished OK" if not bad else "vanished FAILED")
    sys.exit(1 if bad else 0)


def cmd_tail(a):
    bad = False
    for src in a.srcs:
        text = open(src).read()
        if not text.endswith("\n"):
            print(f"{src}: no trailing newline"); bad = True
        lines = [line for line in text.split("\n") if line.strip()]
        if len(lines) > 1 and lines[-1].startswith("#pragma GLOBAL_ASM") and text.rstrip("\n").split("\n")[-2].strip() == "}":
            print(f"{src}: last line is a GLOBAL_ASM directly after `}}`: add a blank line before it"); bad = True
    sys.exit(1 if bad else 0)


def cmd_drafts(a):
    tracked = set(subprocess.run(["git", "ls-files", "drafts"], cwd=ROOT, capture_output=True, text=True).stdout.split())
    paths = set()
    for src in a.srcs:
        rel = os.path.relpath(os.path.abspath(src), ROOT)
        old = subprocess.run(["git", "show", f"HEAD:{rel}"], cwd=ROOT, capture_output=True, text=True).stdout
        now = {(s or "boot", f) for s, f in PRAGMA.findall(open(src).read())}
        for seg, func in now | {(s or "boot", f) for s, f in PRAGMA.findall(old)}:
            path = os.path.join("drafts", seg, func + ".c")
            if a.prune and (seg, func) not in now and os.path.exists(os.path.join(ROOT, path)):
                os.remove(os.path.join(ROOT, path))
                print(f"pruned {path}", file=sys.stderr)
            if path in tracked or os.path.exists(os.path.join(ROOT, path)):
                paths.add(path)
    print("\n".join(sorted(paths)))


SCALAR = {"void": "void", "u8": "u8", "s8": "s8", "char": "s8", "unsigned char": "u8", "u16": "u16", "s16": "s16",
          "short": "s16", "unsigned short": "u16", "u32": "w", "s32": "w", "int": "w", "long": "w", "unsigned": "w",
          "unsigned int": "w", "f32": "f32", "float": "f32", "f64": "f64", "double": "f64", "u64": "d", "s64": "d"}
PROTO_HEAD = re.compile(r"^(extern\s+)?([A-Za-z_][\w\t ]*?[\t \*]+)(\w+)\s*\((.*)\)\s*([;{].*)?$")
NOT_FUNC = {"if", "while", "for", "switch", "return", "sizeof"}


def proto_lines(text):
    """(line_no, kind, ret, name, args, knr) for column-0 one-line function headers; kind 'decl' or 'def'."""
    lines = text.split("\n")
    for i, line in enumerate(lines):
        if not line[:1].isalpha() or line.startswith(("static ", "typedef ")):
            continue
        m = PROTO_HEAD.match(line)
        if not m or m.group(3) in NOT_FUNC:
            continue
        ext, ret, name, args, tail = m.groups()
        tail = (tail or "").strip()
        if tail.startswith(";"):
            yield i + 1, "decl", ret, name, args, False
        elif tail.startswith("{") and not ext:
            yield i + 1, "def", ret, name, args, False
        elif not tail and not ext:
            j, knr = i + 1, False
            while j < len(lines) and lines[j].strip().endswith(";") and "(" not in lines[j]:
                j, knr = j + 1, True
            if j < len(lines) and lines[j].strip().startswith("{"):
                yield i + 1, "def", ret, name, args, knr


def tclass(t):
    """register class of a C type: void / u8 / s8 / u16 / s16 / w (32-bit int or pointer) / f32 / f64 / d; None if unknown."""
    if "*" in t or "[" in t or "(" in t:
        return "w"
    words = [w for w in t.split() if w not in ("const", "volatile", "extern", "static", "register", "signed")]
    for n in (2, 1):
        for i in range(len(words) - n + 1):
            k = " ".join(words[i:i + n])
            if k in SCALAR:
                return SCALAR[k]
    return None


def proto_params(args):
    """None = unprototyped `()`, [] = `(void)`, else [(class, is_bare_identifier)]."""
    args = args.strip()
    if not args:
        return None
    if args == "void":
        return []
    parts, depth, cur = [], 0, ""
    for ch in args:
        depth += ch == "("
        depth -= ch == ")"
        if ch == "," and depth == 0:
            parts.append(cur); cur = ""
        else:
            cur += ch
    parts.append(cur)
    return [(tclass(p), re.fullmatch(r"\s*\w+\s*", p) is not None and tclass(p) is None) for p in parts]


def proto_defs():
    defs = {}
    for path in glob.glob(os.path.join(ROOT, "src", "**", "*.c"), recursive=True):
        for line, kind, ret, name, args, knr in proto_lines(open(path).read()):
            if kind == "def":
                defs.setdefault(name, []).append((os.path.relpath(path, ROOT), line, tclass(ret), proto_params(args), knr))
    return defs


def cmd_protos(a):
    defs, bad = proto_defs(), False
    for src in a.srcs:
        m = re.search(r"(?:^|/)src/(\w+)/", os.path.abspath(src))
        seg = a.seg or (m.group(1) if m else "global")
        text = open(src).read()
        for line, kind, ret, name, args, _ in proto_lines(text):
            if kind != "decl":
                continue
            cands = defs.get(name, [])
            same = [d for d in cands if d[0].split(os.sep)[1] == seg]
            shared = [d for d in cands if d[0].split(os.sep)[1] in ("global", "boot")]
            pick = same or shared
            if len(pick) != 1:
                continue
            path, dline, dret, dparams, knr = pick[0]
            params, why = proto_params(args), []
            r = tclass(ret)
            if r and dret and r != dret:
                why.append(f"return {r} vs {dret}")
            if params is not None and dparams is not None:
                if len(params) != len(dparams):
                    why.append(f"{len(params)} params vs {len(dparams)}")
                elif not knr:
                    for i, ((pc, _), (dc, _)) in enumerate(zip(params, dparams)):
                        if pc and dc and pc != dc:
                            why.append(f"param {i + 1} {pc} vs {dc}")
            if why:
                bad = True
                print(f"{src}:{line} {name}: {'; '.join(why)} (definition {path}:{dline}{', K&R' if knr else ''})")
    print("protos OK" if not bad else "protos: declarations above differ from their definitions (lever list for callers' "
          "near-misses: narrow/void/phantom params change caller codegen; matched callers may rely on the old one)")


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    s = p.add_subparsers(dest="cmd", required=True)
    c = s.add_parser("count"); c.add_argument("seg"); c.add_argument("files", nargs="*"); c.set_defaults(fn=cmd_count)
    c = s.add_parser("handasm"); c.add_argument("seg"); c.add_argument("files", nargs="+"); c.set_defaults(fn=cmd_handasm)
    c = s.add_parser("empty-funcs"); c.add_argument("seg"); c.add_argument("files", nargs="+"); c.set_defaults(fn=cmd_empty)
    c = s.add_parser("boundaries"); c.add_argument("seg"); c.add_argument("files", nargs="+"); c.set_defaults(fn=cmd_boundaries)
    c = s.add_parser("coverage"); c.add_argument("src"); c.add_argument("lists", nargs="+"); c.set_defaults(fn=cmd_coverage)
    c = s.add_parser("left"); c.add_argument("srcs", nargs="+"); c.set_defaults(fn=cmd_left)
    c = s.add_parser("vanished"); c.add_argument("rev", nargs="?", default="HEAD"); c.set_defaults(fn=cmd_vanished)
    c = s.add_parser("pragma-tail"); c.add_argument("srcs", nargs="+"); c.set_defaults(fn=cmd_tail)
    c = s.add_parser("drafts"); c.add_argument("--prune", action="store_true"); c.add_argument("srcs", nargs="+"); c.set_defaults(fn=cmd_drafts)
    c = s.add_parser("protos"); c.add_argument("--seg"); c.add_argument("srcs", nargs="+"); c.set_defaults(fn=cmd_protos)
    a = p.parse_args()
    a.fn(a)


if __name__ == "__main__":
    main()
