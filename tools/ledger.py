#!/usr/bin/env python3
"""Per-function attempt ledger: which unmatched functions to work on next.

`drafts/attempts.jsonl` is an append-only event log (one JSON object per line), keyed by
(segment, VRAM) because names change when functions get named and overlay addresses
collide. The orchestrator is its only writer: it records every assigned function when it
ingests the agent's report, including attempts that improved nothing.

    python3 tools/ledger.py record --unit U --agent A --seg SEG [--task FILE|-] [FUNC[=OUTCOME] ...]
    python3 tools/ledger.py rank [--seg SEG] [--file SRC ...] [--limit N]
    python3 tools/ledger.py show SEG FUNC
    python3 tools/ledger.py seed-git            # one-off approximate history (idempotent)

record: functions come from the `- \\`FUNC\\`` lines of a task file (`-` = stdin, e.g.
  `cat local://tasks/A.md | ... --task -`) plus explicit FUNC arguments. Every function must
  be a function of SEG, or of the segment its task line names (`segment \\`X\\``, so one task
  may span segments) (a C definition in src/<seg>/ or a `glabel` of a GLOBAL_ASM file
  there; names resolve through the symbol file, the `.s`, then the link map), else nothing
  is written: a typo, a data symbol or the wrong segment is never logged as `matched`.
  Run it AFTER the
  agent's copy is merged (or rejected): the default OUTCOME is derived from the tree:
  `matched` (no longer GLOBAL_ASM), `parked` (inside `#ifdef NON_MATCHING`), else `attempted`;
  the stage comes from the draft's first line. Override with FUNC=matched|parked|attempted|
  blocked|skipped (`blocked` = needs split/data work, not C; `skipped` = assigned but not
  worked on: it does not count as an attempt). The first record of a new unit id also
  writes a `unit` event (the point after which that unit's findings exist); `--unit -`
  records a fact outside any unit (a `blocked` finding) without one.

rank: every function still GLOBAL_ASM (or parked) in C files, tiered:
  1 never attempted (no exact or approximate event), smallest first;
  2 attempted, most units since its last attempt first (new findings since then; its own
    unit does not count), then fewest exact attempts, unparked before parked, smallest first;
  3 blocked (last outcome `blocked`).
  `last` is the newest exact event; approximate events (from seed-git) count only when a
  function has no exact one, and only say "worked on around this date": their `since`
  may be off by one and `tries` excludes them.

seed-git: approximate events from git history, marked "approx": true:
  - last commit touching drafts/<seg>/<FUNC>.c (renames followed by name, so a pure rename
    also counts as a touch: approximate);
  - first commit whose ROADMAP.md added a line naming the function (pre-drafts attempts);
  - one `unit` event per run-log row, at the commit that added the row.
"""
import argparse
import datetime
import glob
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LEDGER = os.path.join(ROOT, "drafts", "attempts.jsonl")
RUNLOG = ".omp/skills/decomp-unit/run-log.md"
PRAGMA = re.compile(r'#pragma GLOBAL_ASM\("asm/(?:(\w+)/)?nonmatchings/[^"]*/(\w+)\.s"\)')
PARKED = re.compile(r"#ifdef NON_MATCHING.*?GLOBAL_ASM\(\"[^\"]*/(\w+)\.s\"\).*?#endif", re.S)
INSN = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/")
STAGE = re.compile(r"stage\s*([0-9](?:\s*[-–]\s*[0-9])?)", re.I)
TASKFN = re.compile(r"^- `(\w+)`(.*)$", re.M)
TASKSEG = re.compile(r"segment `(\w+)`")
OUTCOMES = ("matched", "parked", "attempted", "blocked", "skipped")


def utc(iso):
    """Any ISO-8601 timestamp (git %cI carries an offset) as UTC `...Z`, comparable as text."""
    t = datetime.datetime.fromisoformat(iso.replace("Z", "+00:00"))
    return t.astimezone(datetime.timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def now():
    return datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, check=True).stdout


def symfile(seg):
    return os.path.join(ROOT, "symbol_addrs.us.txt" if seg in ("boot", "global") else f"symbol_addrs.{seg}.us.txt")


_syms = {}


def symbols(seg):
    """name -> vram and vram -> name for one segment's symbol file."""
    if seg not in _syms:
        n2v, v2n = {}, {}
        if os.path.exists(symfile(seg)):
            for line in open(symfile(seg)):
                m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)\s*;", line)
                if m:
                    v = int(m.group(2), 16)
                    n2v[m.group(1)] = v
                    v2n.setdefault(v, m.group(1))
        _syms[seg] = (n2v, v2n)
    return _syms[seg]


_maps = {}


def map_symbols(seg):
    """name -> vram of the .text symbols the link map gives src/<seg>/ objects (names that
    are in no symbol file, e.g. ultralib's); empty before the first build."""
    if seg not in _maps:
        path = os.path.join(ROOT, "build", "dk64.us.map" if seg == "boot" else f"{seg}.map")
        out, obj = {}, None
        if os.path.exists(path):
            for line in open(path):
                m = re.match(r"\s*\.text\s+0x[0-9a-f]+\s+0x[0-9a-f]+\s+(\S+)", line)
                if m:
                    obj = m.group(1)
                    continue
                if re.match(r"\s*\.\w+\s", line):
                    obj = None
                s = re.match(r"\s+0x0*([0-9a-f]{8})\s+(\w+)\s*$", line)
                if s and obj and f"/src/{seg}/" in obj:
                    out[s.group(2)] = int(s.group(1), 16)
        _maps[seg] = out
    return _maps[seg]


def vram_of(seg, name):
    m = re.fullmatch(r"func_([0-9A-Fa-f]{8})", name)
    if m:
        return int(m.group(1), 16)
    v = symbols(seg)[0].get(name)
    if v is None:
        asmdir = os.path.join(ROOT, "asm", "nonmatchings") if seg == "boot" else os.path.join(ROOT, "asm", seg, "nonmatchings")
        for p in glob.glob(os.path.join(asmdir, "**", name + ".s"), recursive=True):
            for line in open(p):
                mm = INSN.match(line)
                if mm:
                    return int(mm.group(1), 16)
    if v is None:
        v = map_symbols(seg).get(name)
    return v


def name_of(seg, vram):
    n = symbols(seg)[1].get(vram)
    if n is None:
        n = next((k for k, v in map_symbols(seg).items() if v == vram and not k.startswith("func_")), None)
    return n or f"func_{vram:08X}"


def unmatched():
    """(seg, vram) -> dict(name, src, parked, stage, insns, note) for every GLOBAL_ASM function in C."""
    out = {}
    for src in sorted(glob.glob(os.path.join(ROOT, "src", "**", "*.c"), recursive=True)):
        text = open(src).read()
        parked = set(PARKED.findall(text))
        for m in PRAGMA.finditer(text):
            seg, func = m.group(1) or "boot", m.group(2)
            path = re.search(r'"([^"]+)"', m.group(0)).group(1)
            full = os.path.join(ROOT, path)
            if os.path.exists(full):
                lines = open(full).read().split("\n")
                if not any(line.startswith("glabel ") for line in lines):
                    continue  # rodata-only pragma (dlabel blocks), not a function
                n = sum(1 for line in lines if INSN.match(line) and not line.split("*/", 1)[1].strip().startswith("."))
            elif func.startswith(("D_", "jtbl_")):
                continue
            else:
                n = 0  # .s missing (deleted by a re-split): still unmatched, size unknown
            v = vram_of(seg, func)
            d = os.path.join(ROOT, "drafts", seg, func + ".c")
            note, stage = "", None
            if os.path.exists(d):
                note = open(d).readline().strip()
                sm = STAGE.search(note)
                stage = sm.group(1).replace(" ", "") if sm else None
            out[(seg, v)] = dict(name=func, src=os.path.relpath(src, ROOT), parked=func in parked,
                                 stage=stage, insns=n, note=note)
    return out

# A C function DEFINITION starting at column 0 (`T name(params)`, or `name(params)` with the
# return type on the line above) then `{`, optionally after K&R parameter declarations
# (`T a; T (*cb)(Actor *);`). A prototype has `;` right after `)`, so it never matches.
# Comments are stripped first (ultralib puts them between `)` and `{`).
DEFN = re.compile(r"^(?:[A-Za-z_][\w \t\*]*?\b)?(\w+)\s*\([^;{}]*\)(?:\s*[A-Za-z_][^;{}]*;)*\s*\{", re.M)
COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)


def inventory(seg):
    """VRAMs of every function of SEG: C definitions in src/<seg>/ plus every `glabel` of the
    GLOBAL_ASM files they include (a `.s` can hold more than one function)."""
    vrams = {v for (s, v) in unmatched() if s == seg}
    for src in glob.glob(os.path.join(ROOT, "src", seg, "**", "*.c"), recursive=True):
        text = open(src).read()
        for name in DEFN.findall(COMMENT.sub(" ", text)):
            if name in ("if", "while", "for", "switch", "return", "sizeof"):
                continue
            v = vram_of(seg, name)
            if v is not None:
                vrams.add(v)
        for m in PRAGMA.finditer(text):
            if (m.group(1) or "boot") != seg:
                continue
            path = os.path.join(ROOT, re.search(r'"([^"]+)"', m.group(0)).group(1))
            if not os.path.exists(path):
                continue
            pending = False
            for line in open(path):
                if line.startswith("glabel "):
                    pending = True
                elif pending and INSN.match(line):
                    vrams.add(int(INSN.match(line).group(1), 16))
                    pending = False
    return vrams


def load():
    if not os.path.exists(LEDGER):
        return []
    return [json.loads(line) for line in open(LEDGER) if line.strip()]


def append(events):
    with open(LEDGER, "a") as f:
        for e in events:
            f.write(json.dumps(e, sort_keys=True) + "\n")


def cmd_record(a):
    funcs = []  # (name, outcome, segment)
    if a.task:
        text = sys.stdin.read() if a.task == "-" else open(a.task).read()
        for f, rest in TASKFN.findall(text):  # a task line naming `segment `X`` overrides --seg
            m = TASKSEG.search(rest)
            funcs.append((f, None, m.group(1) if m else a.seg))
    for arg in a.funcs:
        f, _, o = arg.partition("=")
        if o and o not in OUTCOMES:
            sys.exit(f"bad outcome {o!r}: one of {', '.join(OUTCOMES)}")
        seg = next((x[2] for x in funcs if x[0] == f), a.seg)
        funcs = [x for x in funcs if x[0] != f] + [(f, o or None, seg)]
    if not funcs:
        sys.exit("no functions: give --task or FUNC arguments")
    live = unmatched()
    ts = utc(a.ts) if a.ts else now()
    events = []
    if a.unit == "-":  # a fact outside any unit (e.g. a `blocked` note): no unit event
        a.unit = None
    elif not any(e["type"] == "unit" and e["unit"] == a.unit for e in load()):
        events.append(dict(type="unit", unit=a.unit, ts=ts, approx=False))
    known = {}
    for f, o, seg in funcs:
        if seg not in known:
            known[seg] = inventory(seg)
        v = vram_of(seg, f)
        if v is None or v not in known[seg]:
            sys.exit(f"{seg} {f}: not a function of segment {seg} (no C definition or GLOBAL_ASM function in src/{seg}/); nothing recorded")
        cur = live.get((seg, v))
        if o is None:
            o = "matched" if cur is None else "parked" if cur["parked"] else "attempted"
        events.append(dict(type="attempt", seg=seg, vram=f"0x{v:08X}", name=name_of(seg, v), unit=a.unit,
                           agent=a.agent, ts=ts, outcome=o, stage=None if cur is None else cur["stage"],
                           note=a.note or "", approx=False))
    append(events)
    for e in events:
        if e["type"] == "attempt":
            print(f"{e['seg']} {e['vram']} {e['name']}: {e['outcome']}" + (f" (stage {e['stage']})" if e["stage"] else ""))


def history(events):
    units = sorted((e for e in events if e["type"] == "unit"), key=lambda e: e["ts"])
    by = {}
    for e in events:
        if e["type"] == "attempt":
            by.setdefault((e["seg"], int(e["vram"], 16)), []).append(e)
    for k in by:
        by[k].sort(key=lambda e: e["ts"])
    return units, by


def cmd_rank(a):
    live = unmatched()
    units, by = history(load())
    rows = []
    for (seg, v), info in live.items():
        if a.seg and seg != a.seg:
            continue
        if a.file and info["src"] not in a.file:
            continue
        ev = [e for e in by.get((seg, v), []) if e["outcome"] != "skipped"]
        exact = [e for e in ev if not e.get("approx")]
        last = (exact or ev)[-1] if ev else None  # approximate history only when nothing exact exists
        since = None
        if last:
            since = sum(1 for u in units if u["ts"] > last["ts"] and u["unit"] != last.get("unit"))
        stage = info["stage"] or (exact[-1]["stage"] if exact and exact[-1]["stage"] else None)
        tier = 3 if last and last["outcome"] == "blocked" else 1 if not ev else 2
        key = ((tier, info["insns"]) if tier != 2
               else (tier, -since, len(exact), info["parked"], info["insns"]))
        rows.append((key, seg, v, info, stage, len(exact), last, since))
    rows.sort(key=lambda r: r[0])
    print(f"{'tier':4} {'seg':11} {'vram':10} {'name':40} {'insns':>5} {'stage':5} {'park':4} {'tries':>5} {'since':>5} last")
    for key, seg, v, info, stage, n, last, since in rows[: a.limit or None]:
        lt = "-" if not last else last["ts"][:10] + ("~" if last.get("approx") else "")
        print(f"{key[0]:<4} {seg:11} 0x{v:08X} {info['name']:40} {info['insns']:>5} {stage or '-':5} "
              f"{'P' if info['parked'] else '':4} {n:>5} {'-' if since is None else since:>5} {lt} {info['src']}")
    t = [r[0][0] for r in rows]
    print(f"\n{len(rows)} functions: tier 1 (never attempted) {t.count(1)}, tier 2 {t.count(2)}, tier 3 (blocked) {t.count(3)}")


def cmd_show(a):
    v = vram_of(a.seg, a.func)
    if v is None:
        sys.exit("unknown function")
    for e in load():
        if e["type"] == "attempt" and e["seg"] == a.seg and int(e["vram"], 16) == v:
            print(json.dumps(e, sort_keys=True))


def cmd_seed_git(a):
    events = load()
    if any(e.get("approx") for e in events):
        sys.exit("already seeded (approximate events exist)")
    live = unmatched()
    out = []
    # run-log units: the commit that added each row
    log = git("log", "--reverse", "--format=@@%cI", "-p", "--", RUNLOG)
    seen = set()
    ts = None
    for line in log.split("\n"):
        if line.startswith("@@") and not line.startswith("@@ "):
            ts = utc(line[2:])
        elif line.startswith("+|20") and ts:
            cols = line[1:].split("|")
            uid = f"{cols[1].strip()}: {cols[2].strip()[:60]}"
            if uid not in seen:
                seen.add(uid)
                end = utc(cols[1].strip() + "T23:59:59+00:00")  # rows were often added in bulk later
                out.append(dict(type="unit", unit=uid, ts=min(ts, end), approx=True))
    # draft touches: last commit per draft path (follows renames by path history)
    touched = {}
    log = git("log", "--format=@@%cI", "--name-status", "--", "drafts")
    ts = None
    for line in log.split("\n"):
        if line.startswith("@@"):
            ts = utc(line[2:])
            continue
        parts = line.split("\t")
        if len(parts) < 2 or not ts:
            continue
        for p in parts[1:]:
            m = re.fullmatch(r"drafts/(\w+)/(\w+)\.c", p)
            if m and (m.group(1), m.group(2)) not in touched:
                touched[(m.group(1), m.group(2))] = ts  # newest first
    # first ROADMAP line naming a function
    named = {}
    log = git("log", "--reverse", "--format=@@%cI", "-p", "--unified=0", "--", "ROADMAP.md")
    ts = None
    wanted = {}
    for (seg, v), info in live.items():
        for n in {info["name"], f"func_{v:08X}"}:
            wanted.setdefault(n, []).append((seg, v))
    tok = re.compile(r"\b(\w+)\b")
    for line in log.split("\n"):
        if line.startswith("@@") and not line.startswith("@@ "):
            ts = utc(line[2:])
        elif line.startswith("+") and not line.startswith("+++") and ts:
            for t in set(tok.findall(line)):
                for k in wanted.get(t, ()):
                    named.setdefault(k, ts)
    for (seg, v), info in live.items():
        cands = []
        for n in {info["name"], f"func_{v:08X}"}:
            if (seg, n) in touched:
                cands.append((touched[(seg, n)], "git: last draft commit"))
        if (seg, v) in named:
            cands.append((named[(seg, v)], "git: first ROADMAP mention"))
        if cands:
            t, src = max(cands)
            out.append(dict(type="attempt", seg=seg, vram=f"0x{v:08X}", name=info["name"], unit=None, agent=None,
                            ts=t, outcome="parked" if info["parked"] else "attempted", stage=info["stage"],
                            note=src, approx=True))
    append(out)
    print(f"seeded {sum(e['type'] == 'unit' for e in out)} units, {sum(e['type'] == 'attempt' for e in out)} approximate attempts")


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    r = sub.add_parser("record")
    r.add_argument("--unit", required=True)
    r.add_argument("--agent", required=True)
    r.add_argument("--seg", required=True)
    r.add_argument("--task")
    r.add_argument("--note")
    r.add_argument("--ts", help="ISO timestamp (default now; for back-filling)")
    r.add_argument("funcs", nargs="*")
    r.set_defaults(fn=cmd_record)
    k = sub.add_parser("rank")
    k.add_argument("--seg")
    k.add_argument("--file", nargs="*", help="src/<seg>/<file>.c paths")
    k.add_argument("--limit", type=int)
    k.set_defaults(fn=cmd_rank)
    s = sub.add_parser("show")
    s.add_argument("seg")
    s.add_argument("func")
    s.set_defaults(fn=cmd_show)
    g = sub.add_parser("seed-git")
    g.set_defaults(fn=cmd_seed_git)
    a = p.parse_args()
    a.fn(a)


if __name__ == "__main__":
    main()
