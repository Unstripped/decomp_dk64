#!/usr/bin/env python3
"""Probe IDO 5.3's assembler stage (as1) for stage-6 scheduling / delay-slot near-misses.

The `cc -S` + assemble round trip is not faithful (as0 drops `.option O2`), so as1 questions are
answered on ugen's binary output instead: compile FUNC's reduced TU (deadsweep's: the copy's head,
other bodies turned into prototypes, NON_MATCHING resolved) with the file's make flags plus `-K`
(keeps every phase's output), then re-run as1 on edited ugen records and score each result.
Run in the container:

  tools/dk python3 tools/as1probe.py keep <copy.c> <src/seg/file.c> FUNC [--body F] [--out DIR]
  tools/dk python3 tools/as1probe.py as1 DIR <records.G> [--keep-obj]
  tools/dk python3 tools/as1probe.py records DIR [--start N] [--count N]

  keep     writes DIR/t.c and the kept phase files t.B (cfe ucode), t.O (uopt ucode), t.G (ugen output,
           16-byte big-endian records: 4 words), t.T (symbol table), t.o, the as1 command line (DIR/as1.cmd)
           and FUNC/src for scoring (DIR/probe.json); prints deadsweep's score of t.o (full/text/reloc/shape).
           DIR defaults to .scratch/as1probe/<seg>_FUNC and is recreated.
  as1      runs DIR's as1 command on <records.G> (an edited copy of DIR/t.G) and prints the same score.
  records  prints t.G records as `index: w0 w1 w2 w3` (hex) for orientation before editing.

What it found so far: as1's delay-slot and hoist choices depend on label reference counts, including
dead records it deletes (an extra record before a `default:` label stops a `lui` hoist into the entry
stall; an extra reference to a loop-head label turns `bnez; move` into `bnezl; copy`); store-count
positions decide where ugen places homed FP-argument reloads. Edits to t.G are diagnosis only: the
fix must still be C that makes cfe/uopt/ugen emit that stream.
"""
import argparse, json, shlex, shutil, struct, subprocess, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import deadsweep as ds  # noqa: E402

ROOT = ds.ROOT


def score(obj, info):
    exp = ROOT / "expected" / "build" / (info["src"][:-2] + ".o")
    e, g = ds.dis(exp, info["func"]), ds.dis(obj, info["func"])
    if not g:
        return "error: function not in object"
    txt = lambda x, want=None, mask=False: [ds.REG.sub("R", t) if mask else t for r, t in x if want is None or r == want]
    return "full=%d text=%d reloc=%d shape=%d n=%d" % (
        ds.sdiff(txt(e), txt(g)), ds.sdiff(txt(e, False), txt(g, False)), ds.sdiff(txt(e, True), txt(g, True)),
        ds.sdiff(txt(e, mask=True), txt(g, mask=True)), len(g))


def keep(a):
    head, body, _ = ds.load(a.copy, a.func, a.body)
    seg = Path(a.src).parent.name
    d = Path(a.out) if a.out else ROOT / ".scratch" / "as1probe" / f"{seg}_{a.func}"
    shutil.rmtree(d, ignore_errors=True)
    d.mkdir(parents=True)
    (d / "t.c").write_text(head + "\n" + body + "\n")
    cc, flags = ds.compile_flags(a.src)
    # the TU is compiled in DIR (so -K leaves the phase files there): make relative -I paths absolute
    flags = [str(ROOT / f) if k and flags[k - 1] == "-I" and not f.startswith("/") else
             "-I" + str(ROOT / f[2:]) if f.startswith("-I") and len(f) > 2 and not f[2:].startswith("/") else f
             for k, f in enumerate(flags)]
    r = subprocess.run([cc] + flags + ["-K", "-v", "-c", "-o", "t.o", "t.c"], cwd=d, capture_output=True, text=True)
    msg = r.stdout + r.stderr
    if r.returncode or "cfe: Error" in msg or not (d / "t.G").exists():
        sys.exit("compile failed:\n" + "\n".join(l for l in msg.splitlines() if "Error" in l or "error" in l)[-2000:])
    line = next((l for l in msg.splitlines() if "/as1 " in l), None)
    if not line:
        sys.exit("no as1 command in cc -v output")
    t = shlex.split(line)
    t[0] = str(Path(cc).parent / Path(t[0]).name)  # cc -v prints IDO's own /usr/lib/as1 path
    (d / "as1.cmd").write_text(shlex.join(t) + "\n")
    info = {"func": a.func, "src": a.src}
    (d / "probe.json").write_text(json.dumps(info))
    print(d)
    print(score(d / "t.o", info))


def as1(a):
    d = Path(a.dir).resolve()
    info = json.loads((d / "probe.json").read_text())
    t = shlex.split((d / "as1.cmd").read_text())
    g = Path(a.records).resolve()
    out = d / (g.stem + ".probe.o")
    i = t.index("-o")
    t[i + 1] = str(out)
    t[i - 1] = str(g)  # as1 ... <input.G> -o <out.o> ...
    r = subprocess.run(t, cwd=d, capture_output=True, text=True)
    if r.returncode or not out.exists():
        sys.exit("as1 failed:\n" + (r.stdout + r.stderr)[-2000:])
    print(score(out, info))
    if not a.keep_obj:
        out.unlink()


def records(a):
    data = (Path(a.dir) / "t.G").read_bytes()
    n = len(data) // 16
    for k in range(a.start, min(n, a.start + a.count)):
        print("%5d: %08x %08x %08x %08x" % ((k,) + struct.unpack(">4I", data[16 * k:16 * k + 16])))


def main():
    ap = argparse.ArgumentParser(description="as1 probe (see the module docstring)")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("keep")
    p.add_argument("copy"), p.add_argument("src"), p.add_argument("func")
    p.add_argument("--body"), p.add_argument("--out")
    p = sub.add_parser("as1")
    p.add_argument("dir"), p.add_argument("records"), p.add_argument("--keep-obj", action="store_true")
    p = sub.add_parser("records")
    p.add_argument("dir"), p.add_argument("--start", type=int, default=0), p.add_argument("--count", type=int, default=1 << 30)
    a = ap.parse_args()
    {"keep": keep, "as1": as1, "records": records}[a.cmd](a)


if __name__ == "__main__":
    main()
