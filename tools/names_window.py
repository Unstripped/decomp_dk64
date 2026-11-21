#!/usr/bin/env python3
"""Apply one continue-unit names window (`.omp/skills/continue-unit/names.md` "Apply") from batch files.

    python3 tools/names_window.py --unit U --message MSG [--fields F.txt]... [--globals SEG:F.tsv]... [--funcs SEG:F.tsv]...
                                  [--dry-run] [--no-carry]

--fields: `rename.py fields` batches (`<path> <Struct> <field> <new>` lines); --globals/--funcs: `<old> <new>` lines
(tab or space separated) for `rename.py global|func <SEG>`. Steps: dry-run everything (refusals printed and skipped;
`--dry-run` stops here), snapshot every src file a rename touches, apply, `tools/dk make split`, touch src, `tools/dk
make` (must end `build/dk64.us.z64: OK`), `make expected`, `unit_check.py vanished`, one `merge_gate.sh --commit`
staging every changed include/, symbol and data_inc file, then `quality.py carry --rev <gate>^` over the touched src
files with functions (data-only files skipped). Prints `NAMES_WINDOW_OK gate=<sha> renamed=<n> refused=<n>` or
`NAMES_WINDOW_FAIL: <step>`; the ledger commit is left to the caller (`drafts/quality`)."""
import argparse
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LOC = re.compile(r"^((?:src|include)/[^:\s]+|symbol_addrs[^:\s]*|data_inc\.us\.txt):\d+:\d+ ")


def run(cmd, **kw):
    return subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, **kw)


def fail(step, out=""):
    sys.stderr.write(out[-3000:])
    print(f"NAMES_WINDOW_FAIL: {step}")
    sys.exit(1)


def pairs(spec):
    seg, path = spec.split(":", 1)
    out = []
    for line in open(os.path.join(ROOT, path)):
        f = line.split()
        if len(f) >= 2 and not line.lstrip().startswith("#"):
            out.append((seg, f[0], f[1]))
    return out


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--unit", required=True)
    p.add_argument("--message", required=True)
    p.add_argument("--fields", action="append", default=[])
    p.add_argument("--macro-arg", action="append", default=[], metavar="FILE:LINE:COL",
                   help="inspected macro-argument position, passed to `rename.py fields --macro-arg`")
    p.add_argument("--globals", action="append", default=[])
    p.add_argument("--funcs", action="append", default=[])
    p.add_argument("--in-macros", action="append", default=[], metavar="OLD",
                   help="symbol whose #define-body uses were inspected: renamed there too (`rename.py --in-macros`)")
    p.add_argument("--dry-run", action="store_true")
    p.add_argument("--no-carry", action="store_true")
    a = p.parse_args(argv)

    # everything the gate stages must be this window's own change: refuse any pre-existing edit
    if run(["git", "status", "--porcelain", "--", "src", "include", "symbol_addrs*.txt", "undefined_syms.us.txt",
            "data_inc.us.txt"]).stdout.strip():
        fail("src/, include/, symbol files or data_inc.us.txt have uncommitted changes")
    batch = os.path.join(ROOT, ".scratch", "names_window_fields.txt")
    rows = [l for f in a.fields for l in open(os.path.join(ROOT, f)) if l.strip() and not l.lstrip().startswith("#")]
    os.makedirs(os.path.dirname(batch), exist_ok=True)
    open(batch, "w").write("".join(rows))
    syms = [("global", *x) for s in a.globals for x in pairs(s)] + [("func", *x) for s in a.funcs for x in pairs(s)]

    touched, refused, ok_syms = set(), [], []
    if rows:
        margs = [x for m in a.macro_arg for x in ("--macro-arg", m)]
        r = run(["uv", "run", "tools/rename.py", "fields", batch, "--dry-run", *margs])
        touched |= {m.group(1) for l in r.stdout.splitlines() if (m := LOC.match(l))}
        refused += [l for l in r.stdout.splitlines() if l.startswith("REFUSE")]
        if r.returncode not in (0, 2):
            fail("fields dry-run", r.stdout + r.stderr)
    seen = set()
    for kind, seg, old, new in syms:
        if (seg, old) in seen:
            refused.append(f"REFUSE {kind} {seg} {old} {new}: proposed twice")
            continue
        seen.add((seg, old))
        im = ["--in-macros"] if old in a.in_macros else []
        r = run(["uv", "run", "tools/rename.py", kind, "--dry-run", seg, old, new, *im])
        if r.returncode:
            refused.append(f"REFUSE {kind} {seg} {old} {new}: {(r.stdout + r.stderr).strip().splitlines()[-1]}")
            continue
        touched |= {m.group(1) for l in r.stdout.splitlines() if (m := LOC.match(l))}
        ok_syms.append((kind, seg, old, new))
    for l in refused:
        print(l)
    n_fields = len(rows) - sum(1 for l in refused if not l.startswith(("REFUSE global", "REFUSE func")))
    print(f"names_window: {n_fields} fields + {len(ok_syms)} symbols to apply, {len(refused)} refused")
    if a.dry_run:
        return 0
    srcs = sorted(t for t in touched if t.startswith("src/") and t.endswith(".c"))
    r = run([sys.executable, "tools/merge_drafts.py", "snapshot", *srcs])
    if r.returncode:
        fail("snapshot", r.stdout + r.stderr)
    if rows:
        r = run(["uv", "run", "tools/rename.py", "fields", batch, *margs])
        if r.returncode not in (0, 2):
            fail("fields", r.stdout + r.stderr)
    for kind, seg, old, new in ok_syms:
        r = run(["uv", "run", "tools/rename.py", kind, seg, old, new, "--no-gen",
                 *(["--in-macros"] if old in a.in_macros else [])])
        if r.returncode:
            fail(f"{kind} {seg} {old} {new}", r.stdout + r.stderr)

    if ok_syms:  # one prototype-header regeneration for the whole batch (rename.py --no-gen)
        r = run(["uv", "run", "tools/protos.py", "gen"])
        if r.returncode:
            fail("protos.py gen", r.stdout + r.stderr)
    for step, cmd in (("make split", ["tools/dk", "make", "split"]),):
        r = run(cmd)
        if r.returncode:
            fail(step, r.stdout + r.stderr)
    for dp, _, fs in os.walk(os.path.join(ROOT, "src")):
        for f in fs:
            if f.endswith(".c"):
                os.utime(os.path.join(dp, f))
    r = run(["tools/dk", "make"])
    if r.returncode or not r.stdout.rstrip().endswith("build/dk64.us.z64: OK"):
        fail("make (not matching)", r.stdout + r.stderr)
    r = run(["tools/dk", "make", "expected"])
    if r.returncode:
        fail("make expected", r.stdout + r.stderr)
    r = run([sys.executable, "tools/unit_check.py", "vanished"])
    if "vanished OK" not in r.stdout:
        fail("vanished", r.stdout + r.stderr)

    changed = run(["git", "status", "--porcelain"]).stdout.splitlines()
    paths = [l[3:] for l in changed]
    src = [x for x in paths if x.startswith("src/")]
    stage = [x for x in paths if x.startswith(("include/", "symbol_addrs", "data_inc.us.txt"))]
    cmd = ["tools/merge_gate.sh", "--commit", a.message]
    for s in stage:
        cmd += ["--stage", s]
    r = run(cmd + ["-", "-", *src])
    m = re.search(r"COMMITTED (\w+)", r.stdout)
    if "GATE_OK" not in r.stdout or not m:
        fail("merge_gate", r.stdout + r.stderr)
    gate = m.group(1)
    if not a.no_carry:
        funcs = [s for s in src if re.search(r"^[A-Za-z_][^;=]*\)\s*\{?\s*$", open(os.path.join(ROOT, s)).read(), re.M)]
        # carry compiles REV's text, whose #includes still name the old assets/inc files: alias each renamed
        # data_inc row's generated file under its old name for the duration of the carry
        diff = run(["git", "diff", f"{gate}^", gate, "--", "data_inc.us.txt"]).stdout.splitlines()
        old = [l[1:].split() for l in diff if l.startswith("-") and not l.startswith("---")]
        new = [l[1:].split() for l in diff if l.startswith("+") and not l.startswith("+++")]
        aliases = []
        for o, n in zip(old, new):
            src_inc = os.path.join(ROOT, "assets", "inc", n[0], f"{n[1]}.inc.c")
            dst_inc = os.path.join(ROOT, "assets", "inc", o[0], f"{o[1]}.inc.c")
            if o[2] == n[2] and os.path.exists(src_inc) and not os.path.exists(dst_inc):
                open(dst_inc, "w").write(open(src_inc).read())
                aliases.append(dst_inc)
        try:
            r = run(["uv", "run", "tools/quality.py", "carry", "--rev", f"{gate}^", "--unit", a.unit, *funcs])
        finally:
            for p_ in aliases:
                os.unlink(p_)
        if r.returncode:
            fail("carry", r.stdout + r.stderr)
        print(r.stdout.strip().splitlines()[-1] if r.stdout.strip() else "carry: nothing")
        if any(s.startswith("include/") for s in stage):
            # functions whose body did not change but which reach a renamed header field: their automatic
            # rungs carry only with --header-carve (field renames keep every layout)
            r = run(["uv", "run", "tools/quality.py", "carry", "--rev", f"{gate}^", "--unit", a.unit, "--header-carve"])
            if r.returncode:
                fail("carry --header-carve", r.stdout + r.stderr)
            print(r.stdout.strip().splitlines()[-1] if r.stdout.strip() else "carry --header-carve: nothing")
    print(f"NAMES_WINDOW_OK gate={gate} renamed={n_fields + len(ok_syms)} refused={len(refused)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
