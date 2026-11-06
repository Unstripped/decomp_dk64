#!/usr/bin/env python3
"""Per-function attempt ledger: which unmatched functions to work on next.

`drafts/attempts.jsonl` is an event log (one JSON object per line), append-only, except that
`backfill-models` adds `model`/`model_src` to existing attempt events. It is keyed by
(segment, VRAM) because names change when functions get named and overlay addresses
collide. The orchestrator is its only writer: it records every assigned function when it
ingests the agent's report, including attempts that improved nothing.

    python3 tools/ledger.py record --unit U --agent A --seg SEG [--task FILE|-] [--model M] [FUNC[=OUTCOME] ...]
    python3 tools/ledger.py rank [--seg SEG] [--file SRC ...] [--limit N]
    python3 tools/ledger.py show SEG FUNC
    python3 tools/ledger.py route --seg SEG [--agent NAME] [--task FILE|-] [--force] [--tier finish|strong] [--dry-run] [FUNC ...]
    python3 tools/ledger.py backfill-models SESSIONS_DIR
    python3 tools/ledger.py seed-git            # one-off approximate history (idempotent)
    python3 tools/ledger.py plan [--seg SEG] [--arms a,b] [--objective rate|value] [--seed N] [--force] [--write PREFIX]

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
  records a fact outside any unit (a `blocked` finding) without one. Each attempt also gets
  `model` (--model, else the agent's spawn in drafts/spawns.jsonl), `fp` (the route's
  evidence fingerprint) and `score` (the draft note's deadsweep numbers).

route: the model tier for one agent's functions, written to .scratch/routes/<agent>.json for
  .omp/extensions/decomp-router.ts to apply at spawn. `finish` while a function has at most
  2 exact attempts (or its last attempt lowered the draft's full score to <= 10), else
  `strong`; `blocked` (exit 2, nothing written) when already matched, last outcome blocked,
  or no new evidence (same draft C, quirk hits, task-line `next:` text and Qnnnn cites)
  since the last attempt; `--force` overrides the last two. `--dry-run` only prints.

backfill-models: fills `model` on past attempt events from the omp subagent transcripts
  (`<agent>.jsonl` started at most 36 h before the attempt) under SESSIONS_DIR.

plan: sizes the outstanding work and picks a model per function by Thompson sampling. Arms
  are the models in ARMS (selector, relative cost, per-agent capacity). Each attempt with a
  known model is a Bernoulli trial (matched or not) in a cell (arm, tries before it 0/1-2/
  3-5/6+, size s<=150/m<=400/l insns); a cell's Beta posterior is shrunk towards the arm's
  overall rate scaled by the bucket's difficulty, and one function's own failures with an arm
  lower that arm for it. One draw per function picks the arm with the best sampled p/cost;
  on a function with 6+ tries non-frontier arms cost HARD_COST_MULT times more (soft rule)
  (`--objective value`: p*value - cost; all negative = hold); the printed shares come from
  extra draws. A function is held without new evidence since its last attempt: changed
  draft/quirk hits/next step (route fingerprint), or a related knowledge/ido entry (naming it,
  or among the top quirk hits for its draft note) committed after that attempt. Functions
  with 6+ tries or over 400 insns go to an agent alone; the rest are packed per arm by diff
  class (from the draft note) and file under the arm's capacity. `--write PREFIX` writes
  one pool route per arm (.scratch/routes/PREFIX_<arm>.json, `pool: true`: the router keeps
  it for every worker of workpool `PREFIX_<arm>` until it expires) and one task file per
  item under .scratch/plan/PREFIX/; record an item with `--agent PREFIX_<arm> --task <file>`.

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
import hashlib
import json
import os
import random
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import quirks  # noqa: E402

LEDGER = os.path.join(ROOT, "drafts", "attempts.jsonl")
SPAWNS = os.path.join(ROOT, "drafts", "spawns.jsonl")
ROUTES = os.path.join(ROOT, ".scratch", "routes")
RUNLOG = ".omp/skills/decomp-unit/run-log.md"
PRAGMA = re.compile(r'#pragma GLOBAL_ASM\("asm/(?:(\w+)/)?nonmatchings/[^"]*/(\w+)\.s"\)')
PARKED = re.compile(r"#ifdef NON_MATCHING.*?GLOBAL_ASM\(\"[^\"]*/(\w+)\.s\"\).*?#endif", re.S)
INSN = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/")
STAGE = re.compile(r"stage\s*([0-9](?:\s*[-–]\s*[0-9])?)", re.I)
TASKFN = re.compile(r"^- `(\w+)`(.*)$", re.M)
TASKSEG = re.compile(r"segment `(\w+)`")
OUTCOMES = ("matched", "parked", "attempted", "blocked", "skipped")
SCORE = re.compile(r"full=(\d+) text=(\d+) reloc=(\d+) shape=(\d+)")
NEXT = re.compile(r"\bnext:\s*(.*)$")
QID = re.compile(r"\bQ\d{4}\b")
AGENT = re.compile(r"[A-Za-z0-9_]{1,48}")
FRESH_TRIES = 2
CLOSE_FULL = 10
TIERS = {"finish": ["anthropic/claude-sonnet-5-5:high"],
         "strong": ["openai-codex/gpt-6-astra:xhigh", "anthropic/claude-fable-5-1:xhigh"]}
RANK = {"finish": 0, "strong": 1}


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


def task_functions(a):
    """[(name, outcome or None, segment, rest of its task line)] from --task and FUNC args."""
    funcs = []
    if a.task:
        text = sys.stdin.read() if a.task == "-" else open(a.task).read()
        for f, rest in TASKFN.findall(text):  # a task line naming `segment `X`` overrides --seg
            m = TASKSEG.search(rest)
            funcs.append((f, None, m.group(1) if m else a.seg, rest))
    for arg in a.funcs:
        f, _, o = arg.partition("=")
        if o and o not in OUTCOMES:
            sys.exit(f"bad outcome {o!r}: one of {', '.join(OUTCOMES)}")
        seg, rest = next(((x[2], x[3]) for x in funcs if x[0] == f), (a.seg, ""))
        funcs = [x for x in funcs if x[0] != f] + [(f, o or None, seg, rest)]
    if not funcs:
        sys.exit("no functions: give --task or FUNC arguments")
    return funcs


def resolve(funcs):
    """[(name, outcome, segment, vram, rest)]; exits on a name that is no function of its segment."""
    known, out = {}, []
    for f, o, seg, rest in funcs:
        if seg not in known:
            known[seg] = inventory(seg)
        v = vram_of(seg, f)
        if v is None or v not in known[seg]:
            sys.exit(f"{seg} {f}: not a function of segment {seg} (no C definition or GLOBAL_ASM function in src/{seg}/); nothing recorded")
        out.append((f, o, seg, v, rest))
    return out


def sha1(text):
    return hashlib.sha1(text.encode("utf-8")).hexdigest()


def draft_path(seg, name):
    return os.path.join(ROOT, "drafts", seg, name + ".c")


def draft_score(seg, name):
    """The deadsweep numbers on the draft's note line, or None."""
    p = draft_path(seg, name)
    if not os.path.exists(p):
        return None
    with open(p) as f:
        m = SCORE.search(f.readline())
    return dict(zip(("full", "text", "reloc", "shape"), map(int, m.groups()))) if m else None


def fingerprint(seg, name, rest, corpus):
    """Evidence available for an attempt: draft C (not its note), quirk hits, `next:` step, cites."""
    p = draft_path(seg, name)
    text = open(p).read() if os.path.exists(p) else ""
    body = text.split("\n", 1)[1] if "\n" in text else ""
    draft = sha1(body) if body else ""
    _, hits, _ = quirks.func_hits(corpus, [name], Path(ROOT), limit=10**6)
    qh = sorted([h.id, sha1(h.entry.path.read_text() if h.kind == "entry" else h.chunk.heading + "\n" + h.chunk.text)]
                for h in hits)
    m = NEXT.search(rest)
    nxt = " ".join(m.group(1).split()) if m else ""
    cites = sorted(set(QID.findall(rest)))
    return sha1(json.dumps([draft, qh, nxt, cites]))[:16]


def decide(events, fp_now, force=False):
    """(tier, reason) for one function's attempt events (sorted by ts)."""
    ex = [e for e in events if not e.get("approx") and e["outcome"] != "skipped"]
    last, n = (ex[-1] if ex else None), len(ex)
    if not force and last and last["outcome"] == "blocked":
        return "blocked", f"last outcome blocked ({last['ts'][:10]}): split/data work first"
    if (not force and last and last["outcome"] in ("attempted", "parked") and last.get("fp")
            and last["fp"] == fp_now):
        who = last.get("agent") or "-"
        if last.get("model"):
            who += f", {last['model']}"
        return "blocked", f"no new evidence since {last['ts'][:10]} ({who})"
    pre = "forced; " if force else ""
    if n <= FRESH_TRIES:
        return "finish", pre + ("never attempted" if n == 0 else f"{n} tries")
    scored = [e for e in ex if e.get("score")]
    if (len(scored) >= 2 and scored[-1] is last and last["score"]["full"] < scored[-2]["score"]["full"]
            and last["score"]["full"] <= CLOSE_FULL):
        return "finish", pre + f"{n} tries; last attempt lowered full {scored[-2]['score']['full']} -> {last['score']['full']}"
    return "strong", pre + f"{n} tries" + (f", stage {last['stage']}" if last.get("stage") else "")


def spawn_for(agent, ts):
    """Newest drafts/spawns.jsonl entry for AGENT at or before TS, or None when that newest
    spawn was unrouted (the hook logs those with model null: an older routed spawn of the
    same name belongs to an earlier invocation)."""
    if not os.path.exists(SPAWNS):
        return None
    best = None
    for line in open(SPAWNS):
        if not line.strip():
            continue
        s = json.loads(line)
        if s.get("agent") == agent and utc(s["ts"]) <= ts and (best is None or utc(s["ts"]) >= utc(best["ts"])):
            best = s
    return best if best and best.get("model") else None


def cmd_record(a):
    funcs = resolve(task_functions(a))
    live = unmatched()
    ts = utc(a.ts) if a.ts else now()
    events = []
    if a.unit == "-":  # a fact outside any unit (e.g. a `blocked` note): no unit event
        a.unit = None
    elif not any(e["type"] == "unit" and e["unit"] == a.unit for e in load()):
        events.append(dict(type="unit", unit=a.unit, ts=ts, approx=False))
    sp = spawn_for(a.agent, ts)
    model = a.model or (sp["model"] if sp else None)
    src = "flag" if a.model else "route" if sp else None
    for f, o, seg, v, _ in funcs:
        cur = live.get((seg, v))
        if o is None:
            o = "matched" if cur is None else "parked" if cur["parked"] else "attempted"
        sf = next((x for x in (sp or {}).get("functions", [])
                   if x["seg"] == seg and int(x["vram"], 16) == v), None)
        events.append(dict(type="attempt", seg=seg, vram=f"0x{v:08X}", name=name_of(seg, v), unit=a.unit,
                           agent=a.agent, ts=ts, outcome=o, stage=None if cur is None else cur["stage"],
                           note=a.note or "", approx=False, model=model, model_src=src,
                           fp=sf["fp"] if sf else None, score=draft_score(seg, name_of(seg, v))))
    append(events)
    for e in events:
        if e["type"] == "attempt":
            print(f"{e['seg']} {e['vram']} {e['name']}: {e['outcome']}" + (f" (stage {e['stage']})" if e["stage"] else "")
                  + (f", model {e['model']}" if e["model"] else ""))


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


def cmd_route(a):
    if not a.dry_run and not a.agent:
        sys.exit("route: --agent is required unless --dry-run")
    if a.agent and not AGENT.fullmatch(a.agent):
        sys.exit("route: agent name must be 1-48 letters, digits or underscores (omp spawn ids)")
    if any("=" in f for f in a.funcs):
        sys.exit("route: FUNC=OUTCOME is a record argument")
    funcs = resolve(task_functions(a))
    live = unmatched()
    _, by = history(load())
    corpus = quirks.load()
    rows = []
    for f, _, seg, v, rest in funcs:
        name = name_of(seg, v)
        if (seg, v) not in live:
            tier, reason, fp = "blocked", "already matched", None
        else:
            fp = fingerprint(seg, name, rest, corpus)
            tier, reason = decide(by.get((seg, v), []), fp, a.force)
            if a.tier and tier != "blocked":
                tier, reason = a.tier, reason + "; tier set by --tier"
        rows.append(dict(seg=seg, vram=f"0x{v:08X}", name=name, tier=tier, reason=reason, fp=fp))
        print(f"{seg} 0x{v:08X} {name}: {tier} ({reason})")
    open_rows = [r for r in rows if r["tier"] != "blocked"]
    tier = max((r["tier"] for r in open_rows), key=RANK.get) if open_rows else None
    print(f"route {a.agent or '-'}: " + (f"{tier} {'|'.join(TIERS[tier])}" if tier else "blocked"))
    if a.dry_run:
        return
    if not open_rows or len(open_rows) < len(rows):
        print(f"route {a.agent}: not written: drop the blocked functions, give them a new draft or a next: step, or pass --force",
              file=sys.stderr)
        sys.exit(2)
    model = random.choice(TIERS[tier])
    route = dict(agent=a.agent, created=now(), tier=tier, model=model, forced=a.force,
                 note=(f"{tier}: " + "; ".join(f"{r['name']} {r['reason']}" for r in rows))[:200],
                 functions=rows)
    os.makedirs(ROUTES, exist_ok=True)
    with open(os.path.join(ROUTES, a.agent + ".json"), "w") as f:
        json.dump(route, f, indent=1)
        f.write("\n")
    print(f"route {a.agent}: {tier} {model} -> .scratch/routes/{a.agent}.json")


# ---------------------------------------------------------------- plan (Thompson sampling)

# Arms of the model bandit. `cost`: relative cost of one agent attempt (tune: only ratios
# matter); `capacity`/`max_funcs`: how many instructions/functions one agent of this model
# gets in one item; `prior`: assumed match rate while the arm has no recorded attempts
# (`prior_from`: borrow that arm's overall rate instead); `frontier`: high-reasoning arm, no
# HARD_COST_MULT on heavily tried functions. Arms of one model at different thinking levels
# are separate arms; a recorded model without a level counts for the first arm of its model.
ARMS = {
    "flash": dict(model="google-antigravity/gemini-3.8-flash:high", cost=1.0, capacity=1200, max_funcs=6, prior=0.25),
    "sonnet": dict(model="anthropic/claude-sonnet-5-5:high", cost=4.0, capacity=900, max_funcs=4, prior=0.35),
    "sonnet_xhigh": dict(model="anthropic/claude-sonnet-5-5:xhigh", cost=6.0, capacity=900, max_funcs=4, prior=0.35,
                         prior_from="sonnet", frontier=True),
    "astra": dict(model="openai-codex/gpt-6-astra:xhigh", cost=10.0, capacity=10**6, max_funcs=1, prior=0.35, frontier=True),
    "fable": dict(model="anthropic/claude-fable-5-1:xhigh", cost=10.0, capacity=10**6, max_funcs=1, prior=0.35, frontier=True),
}
ARM_STRENGTH = 4   # pseudo-attempts of the hierarchical prior behind each (arm, bucket) cell
FUNC_STRENGTH = 20  # pseudo-attempts of the cell rate behind one function's own failures
SINGLE_TRIES = 6   # functions tried this often (or larger than SINGLE_INSNS) go to an agent alone
SINGLE_INSNS = 400
HARD_COST_MULT = 3.0  # soft rule: a non-frontier arm costs this much more on a SINGLE_TRIES+ function
CLASSES = {"schedule": ("switch", "jr", "as1", "hoist", "delay", "schedul", "xbb", "label"),
           "stack": ("spill", "frame", "stack", "home", "temploc", "slot", "sp+"),
           "regalloc": ("regalloc", "uopt", "register", "colour", "color", "candidate", "priority", "forbidden")}


def arm_of(model):
    """Arm name of a recorded model selector (provider/name[:level]), or None: the arm with that
    exact selector, else the first arm of that model."""
    if not model:
        return None
    exact = next((k for k, c in ARMS.items() if c["model"] == model), None)
    if exact:
        return exact
    base = model.split(":")[0]
    return next((k for k, c in ARMS.items() if c["model"].split(":")[0] == base), None)


def arm_cost(arm, tries):
    """Cost of one attempt by ARM on a function tried TRIES times. Soft rule: heavily tried
    functions make non-frontier arms HARD_COST_MULT times dearer, so they win only when their
    sampled match rate is that much higher (they keep getting picked, and learning, sometimes)."""
    c = ARMS[arm]["cost"]
    return c * HARD_COST_MULT if tries >= SINGLE_TRIES and not ARMS[arm].get("frontier") else c


def tries_bucket(n):
    return "0" if n == 0 else "1-2" if n <= 2 else "3-5" if n < SINGLE_TRIES else f"{SINGLE_TRIES}+"


def size_bucket(n):
    return "?" if not n else "s" if n <= 150 else "m" if n <= SINGLE_INSNS else "l"


def elf_func_sizes(path):
    """vram -> instruction count of every sized FUNC symbol of a big-endian ELF32 file."""
    import struct
    data = open(path, "rb").read()
    shoff, = struct.unpack_from(">I", data, 0x20)
    shentsize, shnum = struct.unpack_from(">HH", data, 0x2E)
    secs = [struct.unpack_from(">IIIIIIIIII", data, shoff + i * shentsize) for i in range(shnum)]
    out = {}
    for s in secs:
        if s[1] != 2:  # SHT_SYMTAB
            continue
        off, size, entsize = s[4], s[5], s[9] or 16
        for i in range(size // entsize):
            _, value, sz, info, _, _ = struct.unpack_from(">IIIBBH", data, off + i * entsize)
            if info & 0xF == 2 and sz:
                out[value] = sz // 4
    return out


def all_sizes(live):
    """(seg, vram) -> instructions for live functions (their .s) and every sized symbol of the build ELFs."""
    sizes = {}
    for path in glob.glob(os.path.join(ROOT, "build", "*.elf")):
        stem = os.path.basename(path)[:-4]
        seg = "boot" if stem == "dk64.us" else stem
        try:
            for v, n in elf_func_sizes(path).items():
                sizes[(seg, v)] = n
        except Exception:
            continue
    for k, info in live.items():
        if info["insns"]:
            sizes[k] = info["insns"]
    return sizes


def knowledge_times():
    """knowledge/ido path -> UTC time of its newest commit; uncommitted changes count as now."""
    out, cur = {}, None
    for line in git("log", "--format=__%cI", "--name-only", "--", "knowledge/ido").split("\n"):
        if line.startswith("__"):
            cur = utc(line[2:])
        elif line.strip() and line not in out:
            out[line.strip()] = cur
    for line in git("status", "--porcelain", "--", "knowledge/ido").split("\n"):
        if line.strip():
            out[line[3:].strip()] = now()
    return out


def related_knowledge(corpus, name, note, k=8):
    """Repo-relative paths of the quirk entries/guides about NAME: those naming it, plus the
    top-K entries for its draft note (symptom- and structure-relevant knowledge)."""
    paths = set()
    _, hits, _ = quirks.func_hits(corpus, [name], Path(ROOT), limit=10**6)
    if note:
        hits = list(hits) + quirks.search(corpus, note, kind="entry", limit=k)
    for h in hits:
        obj = h.entry if h.kind == "entry" else h.guide
        p = getattr(obj, "path", None)
        if p:
            paths.add(os.path.relpath(str(p), ROOT))
    return paths


def diff_class(note):
    low = note.lower()
    counts = {c: sum(low.count(w) for w in ws) for c, ws in CLASSES.items()}
    best = max(counts, key=counts.get)
    return best if counts[best] else "other"


def bandit_cells(by, sizes):
    """(arm, tries bucket, size bucket) -> [successes, failures] from exact attempts with a known
    model; also per-arm and per-bucket totals for the hierarchical prior."""
    cells, arm_tot, bucket_tot = {}, {}, {}
    for key, evs in by.items():
        n = 0
        for e in evs:
            if e.get("approx") or e["outcome"] in ("skipped", "blocked"):
                continue
            arm = arm_of(e.get("model"))
            if arm:
                b = (tries_bucket(n), size_bucket(sizes.get(key)))
                hit = e["outcome"] == "matched"
                for d, k in ((cells, (arm,) + b), (arm_tot, arm), (bucket_tot, b)):
                    d.setdefault(k, [0, 0])[0 if hit else 1] += 1
            n += 1
    return cells, arm_tot, bucket_tot


def cell_prior(arm, b, arm_tot, bucket_tot):
    """Prior mean of one (arm, bucket) cell: the arm's overall rate scaled by how hard the bucket
    is relative to all attempts (while the arm has no data: its `prior_from` arm's rate, else
    the configured `prior`)."""
    s, f = arm_tot.get(arm, (0, 0))
    if not s + f and ARMS[arm].get("prior_from"):
        s, f = arm_tot.get(ARMS[arm]["prior_from"], (0, 0))
    arm_rate = (s + 1) / (s + f + 2) if s + f else ARMS[arm]["prior"]
    gs = sum(v[0] for v in bucket_tot.values())
    gn = sum(v[0] + v[1] for v in bucket_tot.values())
    bs, bf = bucket_tot.get(b, (0, 0))
    scale = ((bs + 1) / (bs + bf + 2)) / ((gs + 1) / (gn + 2)) if gn else 1.0
    return min(max(arm_rate * scale, 0.01), 0.95)


def sample_theta(rng, arm, b, fails, cells, arm_tot, bucket_tot):
    """One Thompson draw of this function's match rate under ARM: the cell rate from its Beta
    posterior, then the function's own failures with that arm on top."""
    mu0 = cell_prior(arm, b, arm_tot, bucket_tot)
    s, f = cells.get((arm,) + b, (0, 0))
    mu = rng.betavariate(ARM_STRENGTH * mu0 + s, ARM_STRENGTH * (1 - mu0) + f)
    mu = min(max(mu, 1e-4), 1 - 1e-4)
    return rng.betavariate(FUNC_STRENGTH * mu, FUNC_STRENGTH * (1 - mu) + fails)


def cmd_plan(a):
    if a.write and not AGENT.fullmatch(a.write):
        sys.exit("plan: --write prefix must be letters, digits or underscores")
    arms = [x for x in (a.arms.split(",") if a.arms else ARMS) if x in ARMS]
    if not arms:
        sys.exit(f"plan: --arms must name some of {', '.join(ARMS)}")
    rng = random.Random(a.seed)
    live = unmatched()
    units, by = history(load())
    sizes = all_sizes(live)
    cells, arm_tot, bucket_tot = bandit_cells(by, sizes)
    corpus = quirks.load()
    ktimes = knowledge_times()
    rows, held = [], []
    for key, info in sorted(live.items()):
        if a.seg and key[0] != a.seg:
            continue
        seg, v = key
        if info["src"].endswith(".s"):
            continue
        evs = by.get(key, [])
        ex = [e for e in evs if not e.get("approx") and e["outcome"] != "skipped"]
        last = ex[-1] if ex else None
        name = info["name"]
        fp = fingerprint(seg, name, "", corpus)
        evidence = []
        if last is None:
            evidence.append("never attempted")
        else:
            if last["outcome"] == "blocked" and not a.force:
                held.append((info, f"blocked {last['ts'][:10]}: split/data work first"))
                continue
            if last.get("fp") and last["fp"] != fp:
                evidence.append("draft/quirk/next changed")
            new = sorted(p for p in related_knowledge(corpus, name, info["note"])
                         if ktimes.get(p) and ktimes[p] > last["ts"])
            if new:
                evidence.append("new knowledge: " + ", ".join(os.path.basename(p)[:-3] for p in new[:4])
                                + (f" +{len(new) - 4}" if len(new) > 4 else ""))
            if not evidence and not a.force:
                held.append((info, f"no new evidence since {last['ts'][:10]} ({len(ex)} tries)"))
                continue
        fails = Counter(arm_of(e.get("model")) for e in ex if e["outcome"] != "matched")
        b = (tries_bucket(len(ex)), size_bucket(info["insns"]))
        n_tries = len(ex)
        value = lambda arm, th: (th / arm_cost(arm, n_tries) if a.objective == "rate"
                                 else th * a.value - arm_cost(arm, n_tries))
        elig = list(arms)
        wins = Counter()
        for _ in range(a.draws):
            th = {arm: sample_theta(rng, arm, b, fails.get(arm, 0), cells, arm_tot, bucket_tot) for arm in elig}
            wins[max(elig, key=lambda arm: value(arm, th[arm]))] += 1
        th = {arm: sample_theta(rng, arm, b, fails.get(arm, 0), cells, arm_tot, bucket_tot) for arm in elig}
        arm = max(elig, key=lambda x: value(x, th[x]))  # the Thompson decision: one draw
        if a.objective == "value" and value(arm, th[arm]) < 0 and not a.force:
            held.append((info, f"expected value negative for every arm (best {arm} p~{th[arm]:.2f})"))
            continue
        mean = {}
        for x in elig:
            mu0 = cell_prior(x, b, arm_tot, bucket_tot)
            s, f = cells.get((x,) + b, (0, 0))
            mu = (ARM_STRENGTH * mu0 + s) / (ARM_STRENGTH + s + f)
            mean[x] = FUNC_STRENGTH * mu / (FUNC_STRENGTH + fails.get(x, 0))
        rows.append(dict(seg=seg, vram=f"0x{v:08X}", name=name, src=info["src"], insns=info["insns"],
                         tries=len(ex), stage=info["stage"], cls=diff_class(info["note"]), bucket=b,
                         arm=arm, p=mean[arm], share=wins[arm] / a.draws, wins=dict(wins),
                         evidence="; ".join(evidence), fp=fp))
    # pack: hard or large functions alone; the rest by diff class, then file, under the arm's capacity
    items = []
    for arm in arms:
        cap, mx = ARMS[arm]["capacity"], ARMS[arm]["max_funcs"]
        mine = sorted((r for r in rows if r["arm"] == arm), key=lambda r: (r["cls"], r["src"], r["insns"]))
        group = []
        for r in mine:
            if mx == 1 or r["tries"] >= SINGLE_TRIES or r["insns"] > SINGLE_INSNS:
                items.append((arm, [r]))
                continue
            if group and (len(group) >= mx or sum(g["insns"] for g in group) + r["insns"] > cap
                          or group[-1]["cls"] != r["cls"]):
                items.append((arm, group))
                group = []
            group.append(r)
        if group:
            items.append((arm, group))
    total = len(rows) + len(held)
    print(f"outstanding {total}: dispatch {len(rows)} in {len(items)} items, hold {len(held)}"
          f"  (objective {a.objective}, {a.draws} draws/function, seed {a.seed})")
    print("arm stats (matched/attempts by tries bucket): "
          + "; ".join(f"{x} " + " ".join(f"{tb}:{sum(v[0] for k, v in cells.items() if k[0] == x and k[1] == tb)}/"
                                        f"{sum(v[0] + v[1] for k, v in cells.items() if k[0] == x and k[1] == tb)}"
                                        for tb in ("0", "1-2", "3-5", f"{SINGLE_TRIES}+")) for x in arms))
    for arm in arms:
        mine = [it for it in items if it[0] == arm]
        if not mine:
            continue
        fs = [r for _, g in mine for r in g]
        exp = sum(r["p"] for r in fs)
        print(f"\npool {(a.write + '_' + arm) if a.write else arm}: {ARMS[arm]['model']}  {len(mine)} items, "
              f"{len(fs)} functions, {sum(r['insns'] for r in fs)} insns, E[matches] {exp:.1f}, "
              f"cost {len(mine) * ARMS[arm]['cost']:.0f}")
        for i, (_, g) in enumerate(mine, 1):
            print(f"  item {i}: {sum(r['insns'] for r in g)} insns, {g[0]['cls']}")
            for r in g:
                alt = " ".join(f"{k}:{n / a.draws:.0%}" for k, n in sorted(r["wins"].items(), key=lambda kv: -kv[1]))
                print(f"    {r['seg']:8} {r['name']:36} {r['insns']:>5} insns  {r['tries']:>2} tries  "
                      f"stage {r['stage'] or '-'}  p~{r['p']:.2f}  [{alt}]  ({r['evidence']})")
    if held:
        print("\nheld:")
        for info, why in held:
            print(f"  {info['name']:40} {info['insns']:>5} insns  {why}")
    if not a.write:
        return
    base = git("rev-parse", "HEAD").strip()
    tdir = os.path.join(ROOT, ".scratch", "plan", a.write)
    os.makedirs(tdir, exist_ok=True)
    os.makedirs(ROUTES, exist_ok=True)
    plan = dict(created=now(), base=base, pools={})
    for arm in arms:
        mine = [g for x, g in items if x == arm]
        if not mine:
            continue
        pool = f"{a.write}_{arm}"
        fs = [r for g in mine for r in g]
        route = dict(agent=pool, created=now(), tier=arm, model=ARMS[arm]["model"], forced=a.force, pool=True,
                     note=f"{arm}: plan {a.write}, {len(mine)} items, {len(fs)} functions"[:200],
                     functions=[dict(seg=r["seg"], vram=r["vram"], name=r["name"], tier=arm,
                                     reason=r["evidence"], fp=r["fp"]) for r in fs])
        with open(os.path.join(ROUTES, pool + ".json"), "w") as f:
            json.dump(route, f, indent=1)
            f.write("\n")
        tasks = []
        for i, g in enumerate(mine, 1):
            item = f"{pool}_{i}"
            lines = [f"# Task {item}", f"Pool: {pool} ({ARMS[arm]['model']})", f"Base commit: {base}", "Private copies:"]
            for src in sorted({r["src"] for r in g}):
                lines.append(f"  mkdir -p .scratch/{item} && git show {base}:{src} > .scratch/{item}/{os.path.basename(src)}")
            lines.append("Functions:")
            for r in g:
                lines.append(f"- `{r['name']}` ({r['insns']} insns, {r['tries']} tries, stage {r['stage'] or '-'}, "
                             f"{r['cls']}; segment `{r['seg']}`; file {r['src']}; draft: `python3 tools/drafts.py show "
                             f"{r['seg']} {r['name']}`; evidence: {r['evidence']})")
            path = os.path.join(tdir, item + ".md")
            with open(path, "w") as f:
                f.write("\n".join(lines) + "\n")
            tasks.append(os.path.relpath(path, ROOT))
        plan["pools"][pool] = dict(arm=arm, model=ARMS[arm]["model"], tasks=tasks)
        print(f"route {pool}: {ARMS[arm]['model']} -> .scratch/routes/{pool}.json; {len(tasks)} task files in "
              f"{os.path.relpath(tdir, ROOT)}/")
    with open(os.path.join(tdir, "plan.json"), "w") as f:
        json.dump(plan, f, indent=1)
        f.write("\n")



def _when(t):
    """Transcript timestamp (ISO string or epoch ms) as an aware UTC datetime."""
    if isinstance(t, (int, float)):
        return datetime.datetime.fromtimestamp(t / 1000, datetime.timezone.utc)
    return datetime.datetime.fromisoformat(t.replace("Z", "+00:00")).astimezone(datetime.timezone.utc)


def transcripts(sessions):
    """name -> [(start, model)] for every subagent transcript under SESSIONS."""
    out = {}
    for path in glob.glob(os.path.join(sessions, "*", "**", "*.jsonl"), recursive=True):
        start, models = None, Counter()
        with open(path, errors="replace") as fh:
            for i, line in enumerate(fh):
                if i >= 5 and '"model"' not in line:
                    continue
                try:
                    d = json.loads(line)
                except ValueError:
                    continue
                if not isinstance(d, dict):
                    continue
                if start is None and d.get("timestamp") is not None:
                    start = _when(d["timestamp"])
                m = d.get("message")
                if isinstance(m, dict) and m.get("role") == "assistant" and m.get("model"):
                    models[f"{m.get('provider')}/{m['model']}"] += 1
        if start is None or not models:
            continue
        name = os.path.basename(path)[: -len(".jsonl")]
        out.setdefault(name, []).append((start, models.most_common(1)[0][0]))
    return out


def main_sessions(sessions):
    """[dict(start, end, changes, msgs)] for every top-level (orchestrator) session transcript
    directly under SESSIONS: `changes` = [(time, model selector or None, thinking level or None)],
    `msgs` = [(time, provider/model, message text, tool-call argument texts)] of its assistant messages."""
    out = []
    for path in glob.glob(os.path.join(sessions, "*.jsonl")):
        start = end = None
        changes, msgs = [], []
        with open(path, errors="replace") as fh:
            for line in fh:
                try:
                    d = json.loads(line)
                except ValueError:
                    continue
                if not isinstance(d, dict) or d.get("timestamp") is None:
                    continue
                t = _when(d["timestamp"])
                start = start or t
                end = t
                if d.get("type") == "model_change" and d.get("model"):
                    changes.append((t, d["model"], None))
                elif d.get("type") == "thinking_level_change" and d.get("thinkingLevel"):
                    changes.append((t, None, d["thinkingLevel"]))
                m = d.get("message")
                if isinstance(m, dict) and m.get("role") == "assistant" and isinstance(m.get("content"), list):
                    text, calls = [], []
                    for c in m["content"]:
                        if not isinstance(c, dict):
                            continue
                        if "arguments" in c:
                            calls.append(json.dumps(c["arguments"]))
                        else:
                            text.append(str(c.get("text") or c.get("thinking") or ""))
                    model = f"{m.get('provider')}/{m['model']}" if m.get("model") else None
                    msgs.append((t, model, "\n".join(text), calls))
        if start and changes:
            out.append(dict(path=path, start=start, end=end, changes=changes, msgs=msgs))
    return out


def session_model(changes, ts):
    """`provider/model:level` active at TS from a session's model/thinking-level changes."""
    model = level = None
    for t, m, lv in changes:
        if t > ts:
            break
        model, level = m or model, lv or level
    return None if model is None else model + (f":{level}" if level else "")


def orchestrator_model(sess, name, ts, window=datetime.timedelta(minutes=15)):
    """Model of an orchestrator attempt on NAME recorded at TS in session SESS, or None unless
    provenance is unambiguous: one of its tool calls within WINDOW of TS ran `ledger.py record`
    with `orchestrator` and NAME in its arguments, and the model and thinking level did not change
    between the session's first assistant mention of NAME and that call (every assistant message
    in between ran on that model)."""
    word = re.compile(rf"\b{re.escape(name)}\b")
    rec = [t for t, _, _, calls in sess["msgs"] if abs(t - ts) <= window
           and any("ledger.py record" in c and "orchestrator" in c and word.search(c) for c in calls)]
    if not rec:
        return None
    rt = min(rec, key=lambda t: abs(t - ts))
    first = next((t for t, _, text, calls in sess["msgs"]
                  if t <= rt and (word.search(text) or any(word.search(c) for c in calls))), rt)
    sel = session_model(sess["changes"], rt)
    if sel is None or session_model(sess["changes"], first) != sel:
        return None
    if any(first < t <= rt for t, _, _ in sess["changes"]):
        return None
    base = sel.split(":")[0]
    if any(m and m.split("/")[-1] != base.split("/")[-1] for t, m, _, _ in sess["msgs"] if first <= t <= rt):
        return None
    return sel


def cmd_backfill_models(a):
    index = transcripts(a.sessions)
    mains = main_sessions(a.sessions)
    with open(LEDGER) as fh:
        lines = [line.rstrip("\n") for line in fh if line.strip()]
    filled = total = 0
    for i, line in enumerate(lines):
        e = json.loads(line)
        if e["type"] != "attempt" or e.get("approx") or e.get("agent") is None or e.get("model") is not None:
            continue
        total += 1
        ts = _when(e["ts"])
        if e["agent"] == "orchestrator":
            cands = {m for s in mains if s["start"] <= ts <= s["end"] + datetime.timedelta(minutes=15)
                     for m in [orchestrator_model(s, e["name"], ts)] if m}
            if len(cands) == 1:
                e["model"], e["model_src"] = cands.pop(), "session"
                lines[i] = json.dumps(e, sort_keys=True)
                filled += 1
            continue
        cands = [(s, m) for s, m in index.get(e["agent"], [])
                 if s <= ts and ts - s <= datetime.timedelta(hours=36)]
        if cands:
            e["model"], e["model_src"] = max(cands)[1], "transcript"
            lines[i] = json.dumps(e, sort_keys=True)  # untouched lines keep their exact text
            filled += 1
    with open(LEDGER + ".tmp", "w") as f:
        f.write("".join(line + "\n" for line in lines))
    os.replace(LEDGER + ".tmp", LEDGER)
    print(f"filled {filled} of {total} attempt events ({total - filled} without a transcript)")


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
    r.add_argument("--model", help="model selector this agent ran on (default: its route)")
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
    o = sub.add_parser("route")
    o.add_argument("--seg", required=True)
    o.add_argument("--agent")
    o.add_argument("--task")
    o.add_argument("--force", action="store_true")
    o.add_argument("--tier", choices=sorted(TIERS))
    o.add_argument("--dry-run", action="store_true")
    o.add_argument("funcs", nargs="*")
    o.set_defaults(fn=cmd_route)
    n = sub.add_parser("plan")
    n.add_argument("--seg")
    n.add_argument("--arms", help=f"comma list of arms to consider (default all: {','.join(ARMS)})")
    n.add_argument("--objective", choices=("rate", "value"), default="rate",
                   help="rate: sampled p / cost (matches per cost unit); value: p * --value - cost")
    n.add_argument("--value", type=float, default=20.0, help="worth of one match in cost units (--objective value)")
    n.add_argument("--draws", type=int, default=200, help="extra draws per function for the printed arm shares")
    n.add_argument("--seed", type=int)
    n.add_argument("--force", action="store_true", help="dispatch held functions too")
    n.add_argument("--write", metavar="PREFIX", help="write pool routes PREFIX_<arm> and task files")
    n.set_defaults(fn=cmd_plan)
    b = sub.add_parser("backfill-models")
    b.add_argument("sessions")
    b.set_defaults(fn=cmd_backfill_models)
    a = p.parse_args()
    a.fn(a)


if __name__ == "__main__":
    main()
