---
name: cleanup-unit
description: Orchestrate the DK64 code-quality campaign (remove FAKE hacks and gotos, consolidate prototypes, shared types, names) over matched C with a rolling queue of subagents and the quality ledger. Use when asked to run the next cleanup/defake/quality session or unit on this decomp.
---

# DK64 cleanup session

Every function is matched; this campaign makes the matched C readable without losing the
match. One session = a rolling queue: hack workers (functions with hacks), polish workers (files:
types, names, reviews) and one `TypesOwner` (headers), each in PRIVATE COPY mode, merged and
recorded the moment it reports; close once per session. AGENTS.md rules always apply. IDO facts:
`knowledge/ido/` (`tools/quirks.py`); merge: `skill://decomp-unit/merge.md`.

|File|Read when|
|---|---|
|[brief-hack.md](brief-hack.md)|dispatching a hack worker|
|[brief-polish.md](brief-polish.md)|dispatching a polish worker|
|[types-stream.md](types-stream.md)|running `TypesOwner`; any header request or callee-prototype batch|
|[ladder.md](ladder.md)|checking a report's LEDGER block; what `status`/`rank` print|
|[naming.md](naming.md)|polish phase 2 and session-close renames|
|[pending.md](pending.md)|blocked owner/header changes (the `TypesOwner` queue)|
|[run-log.md](run-log.md)|sizing a session; close appends a row|

## 0. Model

Use the model the user named for every worker spawn (`task` `model`; none named: ask once). With
`task.perCallModel: off` spawn without it only if the default task agent runs that model
(`history://<agent>`), else tell the user. Never run `ledger.py plan`/`route`, never write
`.scratch/routes/`, never use workpools routed by `.omp/extensions/decomp-router.ts`. Pass the
spawned workers' selector (`provider/model:level`, e.g. `anthropic/claude-opus-5-5:xhigh`) to
`merge_record.py --model`: `rank` orders functions by the strongest model that already tried them.

## 1. Ingest

1. `git status` + `git log -3` (unexpected changes are the user's: never stage them; a lead whose handle died may still run: new commits or a dirty `drafts/quality/` → message it, wait until quiet).
2. `find src -name '*.c' -exec touch {} +`; `tools/dk make` must end `build/dk64.us.z64: OK`;
   `tools/dk make expected`.
3. `uv run tools/protos.py gen --check` exits 0 (else regenerate and commit `include/proto` first);
   `uv run tools/clint.py compdb`; `uv run tools/quality.py report --markdown` → starting numbers.
4. `uv run tools/quality.py rank --limit 40` (hack queue: `str att strong hacks state file function
   kinds`, weakest earlier attempts first) and `rank --polish` (per file: functions without hack
   sites still open, `unrev` = never or stale reviewed).

## 2. Queue (rolling)

Keep up to 6 workers plus one `TypesOwner` running. Never two agents on one src file; a file listed
in an open types batch (`.scratch/TypesOwner/batch_*/files.txt`) is not dispatched.
- **Coverage first.** Until `report` shows `reviewed` equal to functions minus the blocked ones
  (today `renderHitCounterHUD`, blocked on the string convention), dispatch only polish workers on
  `rank --polish` files with `unrev > 0` and hack workers on `rank` functions in state `next=review`.
- **After coverage.** Five slots take the top of `rank`, one the top of `rank --polish` (a hack
  item too when polish is empty).
- **Hack item:** one function with 3+ hack sites, or up to 4 functions with 1–2 sites from the same
  file, in queue order.
- When a worker reports, merge it (§5), then fill its slot at once. No rounds: nothing waits for
  the slowest worker.

## 3. Dispatch

1. Base = `git rev-parse HEAD` at dispatch; `python3 tools/merge_drafts.py snapshot src/<seg>/<f>.c`.
2. Fill the WHOLE [brief-hack.md](brief-hack.md) or [brief-polish.md](brief-polish.md) into
   `.scratch/briefs/<Agent>.md`. Names: `Hack<FUNC>` (first function of the item),
   `Polish<seg><file>`, `TypesOwner`. Task context: "Read `.scratch/briefs/<Agent>.md` FIRST and
   follow it exactly".
3. Hack items carry each function's `uv run tools/quality.py history <FUNC>` and its dossier path
   `drafts/quality/dossiers/<seg>/<FUNC>.md` (if any) in the brief.
4. Files of 100+ functions take 2–4 polish turns (per-turn request budgets): merge and record
   between passes and send the agent back with the new base.

## 4. Types stream

See [types-stream.md](types-stream.md). Workers never edit `include/`: they write the hunk to
`.scratch/<A>/header-request.md` and message the lead, which forwards it to `TypesOwner`
(`write agent://TypesOwner`) and gates its batches.

## 5. Merge

As each worker reports:
1. Check the report: every site of the assigned functions (polish: every reviewed function) in the
   LEDGER block, one `review` per function from a full read at the base, evidence present
   ([ladder.md](ladder.md)), a `new=` on every retry; missing lines go back.
   `uv run tools/clint.py uninit .scratch/<A>/<f>.c --base src/<seg>/<f>.c` must exit 0.
2. `python3 tools/merge_record.py --agent <A> --unit "<YYYY-MM-DD>: cleanup <A>" --base <base>
   --model <selector> --ledger .scratch/<A>/ledger_<f>.txt [--copy-only .scratch/<A>/ledger-copy-only.txt]
   [--keymap .scratch/<A>/keymap.txt] [--stage include/proto/<seg>/<f>.h] src/<seg>/<f>.c`. It gates
   (`merge_gate.sh --commit`), records at the base, `make expected`, sweeps, re-records at the merge
   commit (`--skip-missing`), records copy-only lines, carries, files dossiers, commits
   `drafts/quality`. Read `MERGE_RECORD_OK`; on `MERGE_RECORD_FAIL: <step>` fix that step by hand and
   run the remaining steps (its docstring lists them); never pipe it.
3. Append the report's IDO findings (file, function, merge commit, rule, see-also IDs) to
   `.scratch/s<YYYY-MM-DD>-knowledge-queue.md`; §6 files them once.
4. A copy that changed a non-static signature carries stand-in `#define PROTO_SKIP_<f>` + declarations:
   after the merge put the src without both into `.scratch/<x>/<f>.c`, `protos.py gen` (prints the new
   signature already), gate `--stage include/proto/<seg>/<f>.h .scratch/<x> <merge> src/<seg>/<f>.c`
   (one `--stage` per header; `- -` gates need `.scratch/bases/` snapshots); `gen --check` exits 0.
5. Bundles: strip stand-ins, apply the `.patch` (not shadow headers), merge, gen, objdiff callers
   (`--reloc-ok`), one gate. Copies keyed by the same basename (`boss/52B0` vs `race/52B0`,
   `critter/0` vs `minecart/0`) need separate dirs and gates. `cfe: ... if directive is not terminated`
   on unchanged headers is a stale dkd file-size cache (rounds 13, 18): `(cd .scratch/gate && ../../tools/dk
   --stop)`, rerun; swap a main-tree header via temp + `mv` (new inode). Commit explicit paths only; headers go in `--stage`, never as a
   gate file argument. A copy whose file changed since its base merges 3-way (`<copy-dir> <base>`); a
   copy retyping a shared global's extern: fix every other file's extern in the SAME gate (objdiff each;
   a file whose cfe would rise or that no longer compiles keeps its type and goes to pending.md).
Invariants: `src/` and `include/` change only through the gate; every commit passes the full ROM
gate; a merged file's net HACKS (tagged `// FAKE` + untagged AST sites) and cfe warnings never rise.
Tag pre-existing untagged hacks ("pre-existing, now tagged", one copy-only line each): compare `status --file` site totals base vs
applied copy; the tags are the only accepted rise (a new steer replacing untracked puns goes back, r19 b7). `// ORIG:`
replacing `// FAKE` needs the cited target-asm offset (check it). Accept a pre-existing uninit read a K&R → ANSI conversion exposes (note).

## 6. Session close (once per session)

Once every worker is idle:
1. Apply proposed `func_`/`D_`/shared-field names ([naming.md](naming.md)) with `rename.py
   func|global|field` (dry-run first). It refuses references inside macros and address-shaped targets
   (`func_807444E0` data → `D_`): apply the `--dry-run` positions incl. the macro-argument lines by hand,
   one gate. A renamed GLOBAL_ASM data label needs `tools/dk make split` BEFORE that gate; split
   labels: `rename.py fold --held` (dry-run first; no files after `--held`: every worker is idle).
2. `tools/dk make split`, touch all src, `make` OK, `make expected`, `unit_check.py vanished` → OK.
3. `carry --rev <commit before the renames> --unit "<unit>" <files>` (once: a rerun duplicates events;
   leave out files whose GLOBAL_ASM paths were renamed); sweep what it skipped AND every file with
   stale automatic rungs. Commit.
4. File the knowledge queue in ONE commit: one entry per finding with `--see-also` and `--unit` = the
   reporting worker's unit (its own rungs on the entry's `functions` stay fresh); extend an entry only to correct it (an
   edit stales every rung of the functions it names); drop pure confirmations; tooling rules →
   ladder.md; `quirks.py check`. Knowledge stales agent rungs only through the function names
   in an entry, never through note similarity.
5. `uv run tools/quality.py report --baseline 2b2532bc --markdown` (campaign start) replaces the
   table in ROADMAP.md `### 11. Code quality (ongoing)` under "To do".
6. One [run-log.md](run-log.md) row; procedure lessons → this skill (caps: SKILL.md and references
   ≤150 lines, briefs ≤180; a lesson replaces or merges text); commit `cleanup-unit skill: …`.
No separate re-review groups: stale reviews show as `next=review` in `rank --polish` and go out as
polish work.

## 7. Stop rule

A function leaves the hack queue only when it has no hack site (fixed, or `// ORIG:` with a cited
offset). The campaign is done at `reviewed <n>/<n>` with every `rank` function at `strong >= 3`;
then the user decides about the rest. A `proto-type` site stops blocking once the types stream
recorded `views` `blocked` with a reason.
