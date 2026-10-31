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
    a = p.parse_args()
    a.fn(a)


if __name__ == "__main__":
    main()
