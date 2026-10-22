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
(they are independent); then the listed global subsystems. All nine overlays are C units
since the boss unit (2026-10-22): next units are global subsystems (actor behaviour files
next to `7CA80`/`80150`, see ROADMAP) or further matching rounds on near-misses listed in
ROADMAP. A global subsystem is a set of `asm/global/<file>.s` files: find them from what
the overlays' named functions call (`grep -o 'func_80[67]…'` in their C) and from the
globals each file references most (`grep -oE '%hi\(D_[0-9A-F]+\)' asm/global/<f>.s | sort | uniq -c`).
Count the work:

```sh
for s in asm/<seg>/nonmatchings/<file>/*.s; do echo "$(grep -c '^ *\/\* ' $s) $s"; done
for f in asm/global/*.s; do echo "$f $(grep -c ^glabel $f) $(grep -c '^ *\/\* [0-9A-F]' $f)"; done  # still-asm global files
```

## 2. Split into C (one agent per segment, parallel; a lone segment: do it inline)

Agent edits only `dk64.<seg>.us.yaml`, `symbol_addrs.<seg>.us.txt`, `src/<seg>/*.c`;
re-splits only its own segment (`tools/dk python3 -m splat split dk64.<seg>.us.yaml`) and
may build only `build/<seg>.text.bin build/<seg>.data.bin` + `sha1sum -c dk64.<seg>.us.sha1`.
TU boundary evidence, from the all-asm split: `python3 tools/rodata_owners.py <seg>` lists
each run of data/rodata labels with its owning text file and kinds (on `global` it ran
over 300 s without finishing: run it async with a long timeout, or only look at the runs
around your files); a string/word run
after doubles/jump tables inside one splat file is a hidden TU (boss `9C60` was three:
`9C60`/`A7A0`/`B100`); place the text boundary at the only 16-byte-aligned function start
between the owners' functions. Also: nop padding only at file ends, 16-byte alignment.
Unreferenced strings that end exactly where a file's first rodata label starts (no
alignment gap) belong to that file's TU (actor `7CA80` kong names).
Overlays: data stays one named asm `[0xOFF, data, 0]`. Global: data stays in the shared
`[0x14B740, data]` blob; only add `.rodata` entries. Rodata `.rodata` per file. A first build
that is exactly N bytes long usually means an unreferenced late_rodata float (owner `-`
in the tool output) was emitted as `.rodata`; fix in the symbol file (ok-fine quirks).

Gate: `tools/dk make` OK, then `tools/dk make expected`. Commit
`Overlays: split <a> (<files>) and <b> (<files>) as C units (GLOBAL_ASM baseline)`.

## 3. Matching rounds (up to 6 agents per round)

1. Partition by instruction count: round 1 ~1,000–1,700 per agent, ≤25 functions,
   contiguous by address; functions over ~500 insns held back for later rounds, each
   600+-insn function on its own agent. Later rounds ≤6 functions per agent, near-misses
   first. Never a function in two agents' lists. A file with one agent: DIRECT mode;
   shared file: PRIVATE COPY.
2. For every shared file, BEFORE dispatch: `python3 tools/merge_drafts.py snapshot src/<seg>/<file>.c`.
3. Dispatch with [brief.md](brief.md) as `context`; each `tasks[]` item lists its functions
   with the last known diff note and the path of the previous round's best draft
   (`.scratch/<Agent>/<FUNC>_best.c`), so the next agent starts from it, not from m2c.
   Agents finish after 15–25 min whatever the list length; re-prompting an idle agent to
   "continue" returned the same report with no new matches (boss round 1, 5 tries):
   dispatch the next round instead.
   Rolling dispatch: rounds are per file, not global. When all agents on one file finish,
   merge, gate, commit and re-snapshot that file, then fill freed slots (max 6) with its
   next round while the other file's agents keep running.
4. Merge each shared file: `python3 tools/merge_drafts.py merge src/<seg>/<file>.c .scratch/<A>/<file>.c ...`
   (merges into the current `src`, so edits made after the snapshot survive; drops
   duplicate declarations (keeping the first) and unused ones the drafts added; prints
   clashing declarations on compile errors; exit 2 on conflicts leaves `src` untouched).
   Drafts copied before the latest snapshot (an agent still running from an older round):
   `merge --base <commit the copy started from> src/... .scratch/<A>/...`, else the merge
   reverts everything committed since.
   Round 1 on a fresh file always yields per-agent types (`ActAActor`, `BehBActor`) that
   clash: dispatch one unify fix-up agent per file right after round 1, DIRECT mode, that
   creates/extends a shared header (`include/actor.h`) with one struct per object and moves
   all declarations to one top block. Two files sharing a header: serialize their unify
   agents (second extends the header additively), but start the first file's round 2 at
   once. A clash of one global between two drafts: unify inline.
5. DIRECT files: `git diff` them; revert declaration-only leftovers from zero-yield agents.
6. Gate: `tools/dk make` OK (agents in PRIVATE COPY mode may keep running). Commit
   `<Seg>: match N/T <file> functions`.
7. Stop rule: stop a file after a round that matched fewer than ~1 function per agent, or
   when only near-misses and 500+-insn functions remain. Record the closest diffs in ROADMAP.

## 4. Names, ROADMAP, knowledge

1. One naming agent per segment: only matched-C functions with behaviour confirmed from
   the code, `name = 0xADDR; // type:func` in `symbol_addrs.<seg>.us.txt`, rename in
   `src/<seg>/`, re-split own segment, check own sha1. Give it the agents' reports
   (save them first: `read agent://<id>` → `local://all-reports.md`).
2. `tools/dk make split`, then `touch src/*/*.c` (renamed global functions are referenced
   from overlay GLOBAL_ASM; their objects are not rebuilt and fail to link with the old
   name otherwise), `tools/dk make` OK; `tools/dk make expected`.
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
- Agents asked to change an existing `void f(void)` prototype to `void f();` (needed when a
  caller passes its own argument through in `$a0`). The brief allows it as long as every
  C caller still matches; check that in the merged file.
- `tools/dk` runs each call in a fresh container: `/tmp` files from one call are gone in the
  next, so objdump-and-diff must be one `tools/dk sh -c '...'`.

## Run log

|Date|Unit|Rounds × agents|Matched per round|Result|
|---|---|---|---|---|
|2026-10-21|arcade (ovl08) + menu (ovl10)|split 2; match 6/6/6 (+1 type-unify fix-up)|81 / 31 / 7|arcade 62/98, menu 57/113, 84 named; tools added after this run|
|2026-10-22|boss (ovl07), last overlay|split inline (11 TUs, 9C60 = 3); match 6/6/6; 5 "continue" re-prompts|46 / 8 / 4|boss 58/79, 15 named; `tools/rodata_owners.py` added; best-draft handoff between rounds|
|2026-10-22|global actor core (7CA80 + 80150)|split inline; match 6 / 11 rolling (incl. 4 one-function large agents) / 4; +2 unify fix-ups|85 / 21 / 3|7CA80 62/73, 80150 47/64, 31 named; `include/actor.h`; merge_drafts keeps first duplicate, `--base REV`; large (600–1400 insn) agents: 0 matches, best 8–19 insns off|
