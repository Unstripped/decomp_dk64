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


def cmd_backfill_models(a):
    index = transcripts(a.sessions)
    with open(LEDGER) as fh:
        lines = [line.rstrip("\n") for line in fh if line.strip()]
    filled = total = 0
    for i, line in enumerate(lines):
        e = json.loads(line)
        if (e["type"] != "attempt" or e.get("approx") or e.get("agent") in (None, "orchestrator")
                or e.get("model") is not None):
            continue
        total += 1
        ts = _when(e["ts"])
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
    b = sub.add_parser("backfill-models")
    b.add_argument("sessions")
    b.set_defaults(fn=cmd_backfill_models)
    a = p.parse_args()
    a.fn(a)


if __name__ == "__main__":
    main()
