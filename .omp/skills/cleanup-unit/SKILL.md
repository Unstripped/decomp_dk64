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
|[types-stream.md](types-stream.md)|running `TypesOwner`; any header request or callee-prototype batch; special merges (§5.4)|
|[ladder.md](ladder.md)|checking a report's LEDGER block; what `status`/`rank` print|
|[naming.md](naming.md)|polish phase 2 and session-close renames|
|[rulings.md](rulings.md)|deciding whether a construct is ordinary C, a steer, ORIG or LAYOUT (§5.6); checking a report's tags|

Campaign state lives outside the skill in `drafts/cleanup/`: `pending.md` (the `TypesOwner` queue, director rulings in force, ready hack items, held names, tooling fixes) and `sessions.md` (one row per session).

## 0. Model

Use the model the user named for every worker spawn (`task` `model`; none named: ask once). A `task` without a model parameter inherits
the lead's model and thinking level: check each worker's session jsonl (`model_change`, `thinking_level_change`) and tell the user if it
differs. Fallback: before merging, grep the jsonl for `resolvedModelIsFallback` (provider limits swap the model mid-run, 2026-11-18 →
gpt-6.1-terra); cancel a running fallen-back worker and stop dispatching; one that already reported merges only after re-verifying its
copy, with `--model <fallback selector>` and unit "<…> (mixed opus→<fallback> at <time>)". Never run `ledger.py plan`/`route`, write
`.scratch/routes/` or use `.omp/extensions/decomp-router.ts` workpools. Pass the workers' selector (`provider/model:level`, e.g.
`anthropic/claude-opus-5-5:xhigh`) to `merge_record.py --model`, read from the harness, never from the report (a gpt worker reported
opus, 2026-11-16c; fix a wrong one through a lead `--copy-dir`). `rank` orders functions by the strongest model that tried them.

## 1. Ingest

1. `git status` + `git log -3` (unexpected changes are the user's: never stage them; a lead whose handle died may still run: new commits or a dirty `drafts/quality/` → message it, wait until quiet).
   Director mode: the director spawns each worker from `.scratch/briefs/<A>.md` and relays its report; keep 2-3 briefs ready, reply briefly.
   Lead context runs out (4 leads in 2026-11-17b): one merge per turn, read line ranges, pipe output through `tail`/`head`; after EVERY merge
   update `.scratch/<lead>/dispatch.md` (rulings, merges, queue), `close.md` and the handoff, so a successor resumes from files
   alone. A successor first checks `git log`, `ps` and `history://<old lead>` (a lead the harness calls dead can still run
   and land commits: 2026-11-17 close renames 2cda5579; message it to stop after its current step) before re-merging any report; never run `merge_record` twice for one worker. A dead
   lead's FINISHED workers (status.md + dry-run ledger, no transcript): merge_record needs `--model`, so run its steps by hand,
   `record` without `--model`, unit "<date>: cleanup <A> (orphaned <lead> result, model unknown)", after re-verifying the copy.
2. `find src -name '*.c' -exec touch {} +`; `tools/dk make` must end `build/dk64.us.z64: OK` (no image: `docker compose build`); `tools/dk make expected`.
3. `uv run tools/protos.py gen --check` exits 0 (else regenerate and commit `include/proto` first); `uv run tools/clint.py compdb`;
   `uv run tools/quality.py report --markdown` → starting numbers. Far fewer reviews than the last close reported after a history
   rewrite: `carry --rev <pre-rewrite twin of the files' last commit>` over the files the rewrite changed (2026-11-20: 4d9e6a23, 132).
4. `uv run tools/quality.py rank --limit 40` (hack queue, weakest earlier attempts first), `rank --polish` (per file: `unrev` = never or stale reviewed); read `drafts/cleanup/pending.md` (ready items, rulings, held files).

## 2. Queue (rolling)

Keep up to 5 workers plus one `TypesOwner` (harness cap: 6 subagents in total). Never two agents on one src file; a file in an open types batch (`.scratch/TypesOwner/batch_*/files.txt`) is not dispatched.
- **Coverage first.** Until `report` shows `reviewed` equal to functions minus blocked ones (none since 2026-11-17d), dispatch
  only polish workers on `rank --polish` files with `unrev > 0` and hack workers on `rank` functions in state `next=review`
  (met once all are in flight). A blocked item waits for a director ruling: write the exact decision options (dispatch.md).
  Small files go out as polish bundles of ~25-45 reviews (one ledger per file, one merge over all; never two same-basename files).
  A hack function reviewed by a polish item gets a `review` line only; a body with any fresh site rung stays byte-identical; an
  all-stale body may take ordinary-C fixes, its FAKE/ORIG/LAYOUT lines untouched unless that worker runs the hack ladder (2026-11-18b).
- **After coverage.** Five slots take the top of `rank`, one the top of `rank --polish` (a hack item too when polish is empty).
- **Hack item:** one function with 3+ hack sites, or up to 4 functions with 1–2 sites from the same file, in queue order.
- When a worker reports, merge it (§5), then fill its slot at once. No rounds: nothing waits for the slowest worker.

## 3. Dispatch

1. Base = `git rev-parse HEAD` at dispatch; `python3 tools/merge_drafts.py snapshot src/<seg>/<f>.c`.
2. Fill the WHOLE [brief-hack.md](brief-hack.md) or [brief-polish.md](brief-polish.md) into `.scratch/briefs/<Agent>.md`. Names: `Clean<FUNC>`
   (first function of the item; `b` suffix if `.scratch/<name>` exists), `Polish<seg><file>`, `TypesOwner`; never a name starting "Hack" (17e:
   some ran on another model). Task context: "Read `.scratch/briefs/<Agent>.md` FIRST and follow it exactly"; a long history goes in `<Agent>-history-<FUNC>.txt`.
3. Hack items carry each function's `uv run tools/quality.py history <FUNC>` and dossier path `drafts/quality/dossiers/<seg>/<FUNC>.md` (if any).
4. Files of 100+ functions take 2–4 polish turns (per-turn request budgets): merge and record between passes, send the agent back with the new base.

## 4. Types stream

See [types-stream.md](types-stream.md). Workers never edit `include/`: they write the hunk to `.scratch/<A>/header-request.md` and message
the lead, which forwards it to `TypesOwner` (`write agent://TypesOwner`) and gates its batches (no batch open: `drafts/cleanup/pending.md`).

## 5. Merge

As each worker reports:
1. Check the report: every site of the assigned functions (polish: every reviewed function) in the
   LEDGER block, one `review` per function from a full read at the base, evidence present
   ([ladder.md](ladder.md)), a `new=` on every retry (one that repeats an earlier unit's attempt in `history` is stripped
   from a lead ledger copy); a `permute` line's base/best/seconds must match its log; missing lines go back; hand-recorded
   sweep methods (`plain`/`recipe`/`classify`/`cond`/`remove`) are stripped, hand `consolidate` lines become `diagnose fixed`
   (or go when one exists). `uv run tools/clint.py uninit .scratch/<A>/<f>.c --base src/<seg>/<f>.c` must exit 0.
2. `python3 tools/merge_record.py --agent <A> --unit "<YYYY-MM-DD>: cleanup <A>" --base <base>
   --model <selector> --ledger .scratch/<A>/ledger_<f>.txt [--copy-only .scratch/<A>/ledger-copy-only.txt]
   [--keymap .scratch/<A>/keymap.txt] [--stage include/proto/<seg>/<f>.h] src/<seg>/<f>.c`. It gates
   (`merge_gate.sh --commit`), records at the base, `make expected`, sweeps, re-records at the merge
   commit (`--skip-missing`), records copy-only lines, carries, files dossiers, commits
   `drafts/quality`. Read `MERGE_RECORD_OK`; on `MERGE_RECORD_FAIL: <step>` fix that step by hand and run the remaining steps
   (docstring); never pipe it, never run two at once (they race on `git add drafts/quality`: lost unit 2026-11-25). Then grep its
   log for `restored deleted local declaration` and diff src against the copy (false positives: `case 'c':` re-added `int c;`).
   `--ledger` takes ONE file (`ledger_<f>.txt`, `<f>` = basename WITHOUT `.c`; a `.c.txt` name recorded 0 events yet printed
   MERGE_RECORD_OK, 2026-11-18b): read `recorded N events`, N > 0. A ledger-only merge (copy == src) skips the sweep:
   `sweep <src> --record` its stale automatic rungs.
3. Append the report's IDO findings (file, function, merge commit, rule, see-also IDs) to `.scratch/s<date>-knowledge-queue.md`; §6 files them.
4. Signature bundles (stand-in `PROTO_SKIP_`), worker header-request bundles (strip into a lead clean dir, `git apply` the
   patch, one gen that must equal the worker's diff, `merge_record --copy-dir <clean> --stage` each header: no TypesOwner
   needed), same-basename copies, 3-way merges, shared-extern retypes, data to C, yaml carves and `COMMIT_FAILED`:
   [types-stream.md](types-stream.md) "Special merges".
5. Data carves: a function with a switch `jr` needing XBB guards or an as1-hoist blocker may only miss its TU's own
   `.word`/table data (Q0552): carve before steering; without a switch `jr` look for a one-path store or real control flow
   first (Q0548). Carve window: `rm -f .scratch/<lead>/RESUME`, wait for jobs 0, gate, split/make/expected/vanished,
   re-record, carry, commit, `touch` it. A merge whose file-scope edit stales other reviews, or whose body respelling stales the function's other sites (3D20 PUTC: 9), queues that item at once;
   if the idle worker already measured those sites on the new body, ask it for the lines and `quality.py record --base <merge>` them (42630 45a97280).
6. Rule every new, changed or dropped tag by [rulings.md](rulings.md) (the lead retags a steer in a `--copy-dir` copy with a keymap or copy-only
   line). An unsettled construct goes to the director as exact options with checked offsets: hold the merge, log Rn in dispatch.md, fold it
   into rulings.md at §6. A storage change (array size) merges only with a code proof that every write fits (R11: enumerate each write).
7. A worker's function rename (or a dossier filed under a new name) replaces `drafts/quality/dossiers/<seg>/<old>.md`: delete
   the old file before `merge_record` so its ledger commit carries the deletion. Its re-record printing "no site" for a fixed site is normal.
Invariants: `src/` and `include/` change only through the gate; every commit passes the full ROM
gate; a merged file's net HACKS (tagged `// FAKE` + untagged AST sites) and cfe warnings never rise.
Tag pre-existing untagged hacks ("pre-existing, now tagged", one copy-only line each): compare `status --file` site totals base vs
applied copy (`git worktree add --detach` at the base, cp the copy + `asm/<seg>/nonmatchings/<file>`, `status --file` there); the
tags are the only accepted rise. `// ORIG:` needs a cited target-asm offset the lead checks ([rulings.md](rulings.md)); accept a K&R → ANSI uninit read (note).

## 6. Session close (once per session)

Wrap-up (user asks to stop): no new dispatch; merge reports as they land; while the last (permuter) rows finish, file
the knowledge queue and fold lessons into the skill (no src/include); then steps 1-5 once every worker is idle. Within a
session, a consolidation in a quiet window runs steps 1-3 only. Once every worker is idle:
1. Names ([naming.md](naming.md)): `rename.py func|global|field` (dry-run first). It refuses macro references, address-shaped
   targets (`func_807444E0` data → `D_`) and names in scope (`include/PR/ucode.h` rsp/asp symbols: hold for a types item), also a
   mention in a macro-line comment and the new name in any comment: reword those first, rename, restore (42630 gCsCountdown); apply
   those positions by hand; a hand-renamed global with no symbol_addrs line needs one (C-defined too) or `carry` cannot map it.
   Field renames are never carried: re-read and record a lead `review` for each touched function. Split labels: `rename.py fold
   --held`. Then `make split`, touch src, `make`, `make expected`, `unit_check.py vanished`, ONE gate staging headers/symbol files.
2. `carry --rev <commit before the renames> --unit "<unit>" <files>` once (a rerun duplicates events; `--func` re-runs only
   named functions); sweep what it skipped AND every file with stale automatic rungs. Commit.
3. Knowledge queue in ONE commit (scripted `quirks.py add`, `--see-also`, `--unit` = the reporting worker's unit); a dated paragraph only
   corrects (it stales every function in the entry's list, the reporter's rungs too: 17b's 14 paragraphs staled 67 rungs); extensions are new
   entries (a superseded claim goes in the new entry, not a paragraph); drop confirmations; tooling rules → ladder.md; `quirks.py check`.
   Every new finding is filed (AGENTS.md), never withheld to keep rungs fresh: the rungs it stales are the next session's leftovers.
4. `uv run tools/quality.py report --baseline 2b2532bc --markdown` replaces the ROADMAP.md `### 11. Code quality` table.
5. One row in `drafts/cleanup/sessions.md`; lessons → this skill, new tag rulings → [rulings.md](rulings.md), open state
   (header requests, ready items, held names, rulings in force) → `drafts/cleanup/pending.md`, landed items deleted there
   (caps: SKILL.md and references ≤150 lines, briefs ≤180, `drafts/cleanup/` uncapped; a lesson replaces or merges text);
   one commit `cleanup-unit skill: …` with the `drafts/cleanup/` edits. No re-review groups: stale reviews show as
   `next=review` and go out as polish work.

## 7. Stop rule

A function leaves the hack queue only when it has no hack site (fixed, or `// ORIG:` with a cited offset). The FAKE queue
never ends: once its rungs are fresh a FAKE function shows `next=retry` and `rank` brings it back, least recently attempted
first. Its next attempt follows the retry rule (`new=` naming what history lacks, `fakehunt.py show` output in the brief).
goto-only functions finish at `goto-hand` kept. A `proto-type` site stops blocking once the types stream recorded `views`
`blocked` with a reason.
