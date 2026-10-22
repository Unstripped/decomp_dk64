---
name: decomp-unit
description: Orchestrate one unit of DK64 matching-decompilation work (split a segment into C, parallel matching rounds, naming, ROADMAP, ok-fine) with subagents. Use when asked to "orchestrate the next unit of work" on this decomp.
---

# DK64 decompilation unit

One unit = pick the next segment or subsystem, make it C, match as many functions as the
rounds yield, name them, record status. AGENTS.md rules always apply (matching build,
no game data, tools only via `tools/dk`). Compiler quirks and per-overlay facts live in
ok-fine, not here; this skill is the procedure.

## 0. Ingest

1. ok-fine: `list_projects` with `repository` = `git remote get-url origin`; read
   `architecture/overlay-c-units`, `notes/ido-matching-quirks`, `runbooks/decompile-function`,
   and any concept for the chosen subsystem (`search_concepts`).
2. Re-read `ROADMAP.md` section 9 and this skill's Run log; `git status` (unexpected
   changes are the user's).
3. `tools/dk make` must end with `build/dk64.us.z64: OK`; `tools/dk make progress` for the
   starting numbers.

## 1. Pick the unit

ROADMAP order: overlays smallest-first by `<ovl>_TEXT_SIZE` in `Makefile`, two at a time
(they are independent); then the listed global subsystems. Count the work:

```sh
for s in asm/<seg>/nonmatchings/<file>/*.s; do echo "$(grep -c '^ *\/\* ' $s) $s"; done
```

## 2. Split into C (one agent per segment, parallel)

Agent edits only `dk64.<seg>.us.yaml`, `symbol_addrs.<seg>.us.txt`, `src/<seg>/*.c`;
re-splits only its own segment (`tools/dk python3 -m splat split dk64.<seg>.us.yaml`) and
may build only `build/<seg>.text.bin build/<seg>.data.bin` + `sha1sum -c dk64.<seg>.us.sha1`.
TU boundary evidence: nop padding only at file ends, a TU's strings precede its floats,
rodata/data labels referenced from one file, 16-byte alignment. Data stays one named asm
`[0xOFF, data, 0]`; rodata `.rodata` per file.

Gate: `tools/dk make` OK, then `tools/dk make expected`. Commit
`Overlays: split <a> (<files>) and <b> (<files>) as C units (GLOBAL_ASM baseline)`.

## 3. Matching rounds (up to 6 agents per round)

1. Partition by instruction count, ~4,000–5,000 per agent, ≤20 functions, never a function
   in two agents' lists. A file with one agent: DIRECT mode; shared file: PRIVATE COPY.
2. For every shared file, BEFORE dispatch: `python3 tools/merge_drafts.py snapshot src/<seg>/<file>.c`.
3. Dispatch with [brief.md](brief.md) as `context`; each `tasks[]` item lists its functions
   with the last known diff note.
4. Merge each shared file: `python3 tools/merge_drafts.py merge src/<seg>/<file>.c .scratch/<A>/<file>.c ...`
   (merges into the current `src`, so edits made after the snapshot survive; drops
   duplicate/unused declarations the drafts added; prints clashing declarations on
   compile errors; exit 2 on conflicts leaves `src` untouched).
   Clashes between drafts' types: unify into one declaration at the top of the file; a
   type unification across many functions is a fix-up agent's job, not inline work.
5. DIRECT files: `git diff` them; revert declaration-only leftovers from zero-yield agents.
6. Gate: `tools/dk make` OK (only once no agent is editing `src/` directly). Commit
   `Overlays: match N/T <a> functions and N/T <b> functions`.
7. Stop rule: stop after a round that matched fewer than ~1 function per agent, or when
   only near-misses and 500+-insn functions remain. Record the closest diffs in ROADMAP.

## 4. Names, ROADMAP, knowledge

1. One naming agent per segment: only matched-C functions with behaviour confirmed from
   the code, `name = 0xADDR; // type:func` in `symbol_addrs.<seg>.us.txt`, rename in
   `src/<seg>/`, re-split own segment, check own sha1. Give it the agents' reports
   (save them first: `read agent://<id>` → `local://all-reports.md`).
2. `tools/dk make split && tools/dk make` OK; `tools/dk make expected`.
3. ROADMAP: one bullet per segment (files, data/rodata offsets, N of T matched per file,
   named groups, near misses, unattempted large functions). Check every name you cite
   exists in the symbol file.
4. Commit `<A>/<b>: name N functions; ROADMAP: overlay unit status`.
5. ok-fine (you, not agents): update `architecture/overlay-c-units` (or the subsystem
   concept) and append new quirks to `notes/ido-matching-quirks`; sources at
   `git rev-parse HEAD`; `verify_concept`. Agents editing ok-fine in parallel broke
   footnote source ids once; keep them read-only.

## 5. Improve this skill (mandatory, every run)

Before the final yield:
1. Edit this file and `brief.md` with what this run taught you about the *procedure*:
   a step that failed, a brief instruction agents misread, a better partition size or
   stop threshold, a new tool flag. Fix or delete stale advice rather than appending
   contradictions. IDO quirks go to ok-fine, not here.
2. Append one row to the Run log (keep the last ~10 rows).
3. If a manual step repeated across rounds, turn it into a `tools/` script and replace
   the prose here with the command.
4. Commit `decomp-unit skill: <what changed>` together with or right after the unit's
   last commit.

## Known pitfalls

- The persistent shell keeps `set -e` between calls; use it only inside `sh -c`.
- Agents hit budget limits after ~20 min; "unattempted" functions mean the list was too
  long, not that they are hard. Shorter lists, near-misses first.
- An agent that reverts its function to GLOBAL_ASM often leaves its declarations; the
  merge tool prunes unused ones, DIRECT files need a manual `git diff` look.
- Probe/test files belong in `.scratch/` (gitignored). Older probes in the repo root
  (`test_*.c`, `t.s`, `tl.c`) are tracked; ask the user before removing them.

## Run log

|Date|Unit|Rounds × agents|Matched per round|Result|
|---|---|---|---|---|
|2026-10-21|arcade (ovl08) + menu (ovl10)|split 2; match 6/6/6 (+1 type-unify fix-up)|81 / 31 / 7|arcade 62/98, menu 57/113, 84 named; tools added after this run|
