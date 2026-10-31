---
name: decomp-unit
description: Orchestrate one unit of DK64 matching-decompilation work (split a segment into C, parallel matching rounds, naming, ROADMAP, ok-fine) with subagents. Use when asked to "orchestrate the next unit of work" on this decomp.
---

# DK64 decompilation unit

One unit = pick the next segment or subsystem, make it C, match as many functions as the
rounds yield, name them, record status. AGENTS.md rules always apply (matching build, no
game data, build tools only via `tools/dk`). This skill is the procedure; IDO/compiler
facts live in ok-fine (`notes/ido-matching-quirks`), the matching method in AGENTS.md
"Decompiling a function".

Read each file when its phase starts (`skill://decomp-unit/<file>`), and re-read it after
a context compaction:

|File|Read when|
|---|---|
|[split.md](split.md)|§1–2: choosing files, TU boundaries, empty functions, `-g` files, stub seeding|
|[dispatch.md](dispatch.md)|§3: before the first dispatch; list sizes, rolling dispatch, report checks, stop rule|
|[brief.md](brief.md)|§3: fill into `local://brief.md` for matching agents|
|[merge.md](merge.md)|§3: before the first merge and on every failed merge or gate|
|[namer-brief.md](namer-brief.md)|§4: fill for the naming agent|
|[troubleshooting.md](troubleshooting.md)|usage limits, crashes, missing `.s` files, Docker disk, tool quirks|
|[run-log.md](run-log.md)|sizing lists; §5 appends a row|

## 0. Ingest

1. ok-fine: `list_projects` with `repository` = `git remote get-url origin`; read
   `architecture/overlay-c-units` and the concept for the chosen subsystem
   (`search_concepts`). Agents read `notes/ido-matching-quirks` themselves (brief); it is
   ~75 KB, so search it (`search_concepts`, or grep the body read from Python) when you
   write an agent's next step, fix a split symbol, or append quirks in §4.
2. `ROADMAP.md` section 9; `git status` (unexpected changes are the user's: never stage them).
3. `find src -name '*.c' -exec touch {} +`, then `tools/dk make` must end with
   `build/dk64.us.z64: OK` (make has no header deps: an `include/` retype left 6 files of
   stale objects hiding broken C); `tools/dk make progress` for the starting numbers.

## 1. Pick the unit ([split.md](split.md))

Every global file is C, so a unit is matching rounds on unmatched functions. Pick from
`python3 tools/ledger.py rank` (attempt ledger `drafts/attempts.jsonl`): never-attempted
first, then most units (new findings) since the last attempt, fewest attempts, unparked
before parked; tier 3 = `blocked` (split/data work first). Group the top of the ranking by
file/subsystem (`rank --file src/<seg>/<f>.c ...` shows a file's set). For a file still to
convert, check it first:
- `python3 tools/unit_check.py count global <file>...` (size);
- `python3 tools/unit_check.py handasm global <file>...`: every count must be 0 (else
  hand-written asm: keep it asm);
- compiler: `-O2` game code or `-g` library code (split.md);
- hidden TUs: `python3 tools/rodata_owners.py <seg>` (split.md);
- hidden empty functions: `python3 tools/unit_check.py empty-funcs <seg> <file>...`.
- false splits, fall-through hand asm, TU padding: `python3 tools/unit_check.py boundaries <seg> <file>...`.
- revisit of an early unit's leftovers: grep their drafts' notes for rodata/pad/"together"
  claims first; a text-identical function blocked by a pad between functions is a hidden TU
  (7AF60 → 7BA00 landed 2 functions); note-less old drafts get a stage in round 1.

## 2. Split into C ([split.md](split.md))

Split at every TU boundary BEFORE round 1, seed the stubs' shared externs, keep everything
`GLOBAL_ASM`. Gate: `tools/dk make` OK, `tools/dk make expected`, commit the split alone.

## 3. Matching rounds ([dispatch.md](dispatch.md), [merge.md](merge.md))

1. Per file: `python3 tools/merge_drafts.py snapshot src/<seg>/<file>.c`.
2. Fill the WHOLE [brief.md](brief.md) into `local://brief.md`; start `local://findings.md`.
3. Partition (dispatch.md) and verify each file with
   `python3 tools/unit_check.py coverage src/<seg>/<file>.c <Agent>=<funcs>...`.
4. Dispatch up to 6 agents, each in PRIVATE COPY mode from a named base commit.
5. As each agent reports: check the report against its list and the stage of anything
   parked; append it to `.scratch/all-reports.md`. A zero-yield copy is merged only for parks (merge.md).
   `python3 tools/drafts.py collect`, then `git diff drafts/` (restore any note it
   replaced), then
   `tools/merge_gate.sh --commit "<Seg>: match N/T <file> functions" [--stage include/<h>.h] .scratch/<A> <base> src/<seg>/<f>.c`
   (`--stage` every file the merge depends on outside the given `src` files: headers a unify
   agent extended, symbol files). Continue only after `GATE_OK` and `COMMITTED`. Append new
   findings to `local://findings.md`; refill the slot from the new HEAD with a concrete
   next step per function. Then record every function of the task, matched or not (zero
   yield too, also when the copy is not merged):
   `cat local://tasks/<A>.md | python3 tools/ledger.py record --unit "<YYYY-MM-DD: unit>" --agent <A> --seg <seg> --task -`
   (outcome and stage come from the tree after the merge; add `FUNC=skipped` for functions
   the report says it never reached). Your own probes: `--agent orchestrator FUNC`; a
   split/data blocker: `--unit - FUNC=blocked --note "..."`.
6. Stop rule (dispatch.md): a round matching fewer than ~1 function per agent, or only
   near-misses and 500+-instruction functions left. List what is left with
   `python3 tools/unit_check.py left src/<seg>/<file>.c ...` before stopping.

Invariants: never a function in two agents' lists or in none; `src/` changes only through
your merges; every commit passes the full ROM gate (never commit a non-matching state);
a parked `NON_MATCHING` function is stage 4+ and counts as unmatched.

## 4. Names, ROADMAP, knowledge

1. Copy `.scratch/all-reports.md` to `local://all-reports.md`. Naming agent per segment
   from [namer-brief.md](namer-brief.md). Check its diff before committing:
   - `git diff --stat` vs `git diff -w --stat` per file (a reformatted file shows up as a
     large difference; rebuild it from the pre-rename version by token renames);
   - `python3 tools/unit_check.py vanished` must print `vanished OK`;
   - no `#pragma weak` aliases, no edits under `tools/`, no names encoding offsets.
2. `tools/dk make split` (the WHOLE split: overlay asm calls renamed global functions), then
   `touch src/*/*.c`, `tools/dk make` OK, `tools/dk make expected`. If agents still run, do the
   split and the restore as one lease (no other `tools/dk` call runs between them):
   `tools/dk --hold sh -c 'tools/dk make split && tools/restore_split_asm.sh <oldest running base> dk64.global.us.yaml'`.
   A failing gate after the namer: troubleshooting.md "Namer broke the build".
   Named parked/`GLOBAL_ASM` functions: splat writes a `.s` only for pragma paths it finds, so
   point those pragmas at the new names, split again, and `git mv` their drafts to the new names.
3. ROADMAP: one bullet per segment (files, data/rodata offsets, N of T matched per file,
   named groups, near-misses incl. parked ones, unattempted large functions; check every
   cited name exists in the symbol file). `tools/dk python3 tools/progress.py --readme`.
4. Commit `<A>/<b>: name N functions; ROADMAP + README: <unit> status`.
5. ok-fine (you, not agents: parallel agent edits broke footnote ids once): update
   `architecture/overlay-c-units` (overlays) or the subsystem concept, and append new quirks
   from the reports to `notes/ido-matching-quirks`; sources at `git rev-parse HEAD`;
   `verify_concept`.

## 5. Improve this skill (every run, before the final yield)

1. Fold what this run taught about the *procedure* into the file that owns the phase (a
   step that failed, a brief instruction agents misread, a better list size or stop
   threshold, a new tool flag). IDO/compiler facts go to ok-fine, never here.
2. Size caps: SKILL.md and each reference file ≤ 150 lines, brief.md ≤ 180 (every agent
   reads all of it). A new lesson replaces or merges existing text; over the cap, condense
   in the same commit. One rule per lesson, with at most one clause of why; the evidence
   stays in git history and the run log.
3. A manual check repeated across rounds becomes a `tools/` command (`tools/unit_check.py`
   or a flag on an existing tool) and its prose here becomes the command. Delete a pitfall
   once a tool rejects that exact failure.
4. Append one row to [run-log.md](run-log.md) (keep the last ~10).
5. Commit `decomp-unit skill: <what changed>` with or right after the unit's last commit.
