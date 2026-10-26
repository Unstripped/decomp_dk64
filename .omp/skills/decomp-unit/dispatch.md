# Dispatch matching agents (SKILL.md §3)

Up to 6 agents at once. Agents follow [brief.md](brief.md); the matching method itself
(stage order, `uopt_trace.sh`, permuter, NON_MATCHING parking) is AGENTS.md "Decompiling a
function" step 4, and IDO tricks are ok-fine `notes/ido-matching-quirks`.

## Before the first dispatch

1. Snapshot each file: `python3 tools/merge_drafts.py snapshot src/<seg>/<file>.c`.
2. Fill the WHOLE [brief.md](brief.md) template into `local://brief.md`. It contains fenced
   code blocks: never cut it at the first ```` ``` ````. For a `-g` unit add a section saying
   uopt/regalloc advice does not apply and temp differences come from expression-tree shape.
3. Start `local://findings.md`: the unit's IDO tricks and unified struct/prototype
   declarations. Append each report's new quirks and declarations right after merging it,
   with Python file I/O on the local path (not `str()` of a `tool.read` result).
4. Every task's `context`: "Read `local://brief.md` FIRST and follow it exactly, then read
   `local://findings.md`" plus file facts (unified type names, hidden empty functions).
5. Every task names its exact base commit for the PRIVATE COPY
   (`git show <commit>:src/<seg>/<file>.c > .scratch/<Name>/<file>.c`), even for a lone agent
   on a file: `src/` then changes only through your merges.
6. Check the lists: `python3 tools/unit_check.py coverage src/<seg>/<file>.c
   <Agent>=func_A,func_B ... <Large1>=func_C` must print `coverage OK` (no function in two
   lists or in none, held-back large functions included).

## List sizes

- Round 1: ~600–1,300 instructions per agent, ≤20 functions, contiguous by address.
  If agents report after a few minutes with most of a long list unattempted (the
  `FCCD0` unit: 12–20-function lists matched 1–4 each), switch to 3–6-function lists
  rather than re-prompting the long ones: "unattempted" means too long, not too hard.
- Functions over ~400 instructions: held back from round 1, one agent each (2–3 per agent
  once single ones finish quickly), smallest first, dispatched as soon as slots free.
- Later passes: ≤6 functions, near-misses first. A stage-6 near-miss of 1–8 instructions is
  worth one dedicated agent; a second dedicated pass is worth it only with new findings in
  the context.
- Each `tasks[]` item lists its functions with the last diff note and stage; agents start
  from the stored draft (`tools/drafts.py show <seg> <FUNC>`), not m2c.
- The agent's budget is its context window, not wall-clock time: the brief gates on outcome
  (every function matched, or back on its `GLOBAL_ASM` line with a staged draft and no
  untried idea). No `date`/minute gates: they only make finished agents idle.

## Rolling dispatch

- Rounds are per agent, not per file. Merge EACH agent as soon as it reports
  ([merge.md](merge.md)), commit, and refill the slot from the new HEAD.
- Continuation is your job: for functions left, send a fresh list with each draft's diff
  note and the exact next step (frame size to reach, expression to flip, one named trick).
  Re-prompts without a concrete next step yield nothing; "continue" re-prompts yielded no
  matches.
- Re-prompting a finished agent (`write agent://<id>`) works well when it stays on its file
  (it keeps that file's types): give it a NEW private copy from the HEAD that contains its
  merge (`.scratch/<Name>2/`), never its old copy, and merge with `--base` that HEAD.
- Productive follow-ups: second passes of 4–6 functions from stage-4+ drafts with the
  findings; fresh-eyes agents on a sibling's near-miss; dedicated permuter agents told to
  put a score-0 result into their copy as C; dead-test placement hill-climbing against the
  objdiff score. When typed-C passes stall (F4C0 unit: four zero-yield passes in a row),
  switch to near-miss agents with 4 functions each, re-prompted with the next 4: they first
  bring each function to the same blocks, frame and callee-saved set (stage 4, AGENTS.md
  step 4), then run a bounded permuter search (`-j 2 --seconds`); they matched 2–4 per pass
  where plain passes matched 0. Reject permuter C that reads/writes outside an object
  (`(u8 *)&x - 1`); no-op idioms (`(0, 1) +`, `x = x`, empty `if`) are accepted.
- Forward a key pattern that unblocks a common near-miss to running siblings at once,
  one by one (`write agent://<id>`; `agent://all` also wakes finished agents, which act).
- Only a TU re-split of a file waits for every agent on that file.

## Large functions

- Same method as near-misses, plus forward every trick a finished large agent found into
  the next large agent's task text.
- A single huge function can be worked on a private copy with a splice script (regenerate
  the copy from `git show HEAD:src/...` + the function draft each time).
- Jump-table functions: split both objdumps at every branch to the epilogue and diff case
  by case with registers normalised (ugen numbering cascades from the first divergence; raw
  counts overstate the diff ~5×).

## Checking reports

- Compare every report against its assigned list: agents have silently skipped functions
  and deleted another function's `GLOBAL_ASM` line (`merge_drafts.py` refuses the latter).
- Check the stage of everything parked: agents park stage-2/3 C despite the brief. Only
  stage 4+ (same blocks, saved registers and frame) stays parked; turn the rest back into
  the bare pragma with the draft kept.
- An agent whose last message answers a late async notice ("earlier report stands") hides
  its report: read `history://<id>` and take the last `## 1.` section.
- Save every report as it arrives: append `read agent://<id>` to `.scratch/all-reports.md`
  (fresh per unit); the namer gets it as `local://all-reports.md`.

## Stop rule

Before stopping, list what is left: `python3 tools/unit_check.py left src/<seg>/<file>.c ...`
(`-` = never given a draft: possibly never assigned). Stop a file after a round that
matched fewer than ~1 function per agent, or when only near-misses and 500+-instruction
functions remain. Record the closest diffs in ROADMAP.
