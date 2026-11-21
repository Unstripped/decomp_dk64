---
name: continue-unit
description: Run the next DK64 "continue unit": one session that retires whatever decompilation or cleanup debt is cheapest next (unmatched functions, asm data, FAKE/goto/LAYOUT hacks, reviews, warnings, prototypes, func_/D_/unkXX names), scored by the weighted debt of autoresearch.sh. Use when asked to continue, run the next unit, or drive the remaining work down.
---

# DK64 continue unit

One unit = measure the debt, apply the names queued by the last unit, keep up to 6 subagent slots
busy on the streams with the most debt, merge each report the moment it lands, close. AGENTS.md rules
always apply (matching build, no game data, build tools only via `tools/dk`). This skill only
allocates work; each stream's procedure lives in its own skill and is followed unchanged:

|Stream|Debt (`tools/debt.py`)|Procedure|Worker|
|---|---|---|---|
|decomp|unmatched functions ×100, asm data bytes ×0.25|`skill://decomp-unit` §1–3 (`data.md` for data)|matching agents, `brief.md`|
|hack|FAKE ×20, goto ×20, LAYOUT ×10, proto-type ×10, open sites ×5|`skill://cleanup-unit` §2–5|`brief-hack.md`|
|polish|unreviewed ×5, cfe warnings ×5, protos mismatch ×5, uninit ×2|`skill://cleanup-unit` §2–5|`brief-polish.md`|
|types|blocked header items in `drafts/cleanup/pending.md`|`cleanup-unit/types-stream.md`|`TypesOwner`|
|names|func_ ×2, m2c names ×2, unkXX field refs ×1, D_ refs ×1|[names.md](names.md)|[names-brief.md](names-brief.md)|

Weights are the benchmark's (`autoresearch.sh`); `tools/debt.py` mirrors them. Read each referenced
file when its stream first gets a slot, and again after a context compaction.

## 0. Model

Use the model the user named for every worker spawn (none named: ask once, with the stream mix).
Fallback checks and `--model` selectors: `skill://cleanup-unit` §0.

## 1. Measure

1. `git status` + `git log -3` (unexpected changes are the user's: never stage them). ok-fine:
   `list_projects` (repository = `git remote get-url origin`), `search_concepts` for the files the
   ranking below names.
2. `bash autoresearch.sh` (full rebuild gate + both reports, ~5 min). It must exit 0: a non-matching
   tree is fixed first, nothing else runs. Note `METRIC debt=` as the unit's start.
3. `tools/dk make expected`; `uv run tools/clint.py compdb`; `uv run tools/protos.py gen --check`.
4. `uv run tools/debt.py --from .scratch/autoresearch/quality.json --progress .scratch/autoresearch/progress.json`
   prints the stream totals and the files holding the most debt; `--stream <s>` ranks one stream.
   Queues per stream: decomp `python3 tools/ledger.py rank`; hack `uv run tools/quality.py rank
   --limit 40`; polish `rank --polish`; types `drafts/cleanup/pending.md`; names `uv run tools/debt.py
   names` ([names.md](names.md)).

## 2. Names window (start of unit, nothing checked out)

Apply the proposals the last unit queued in `drafts/cleanup/names-queue.md` ([names.md](names.md)
"Apply"), gate, `carry`, commit, before any worker copies a file: renames touch many files, and a
copy taken after them never conflicts with them. An empty queue skips this step.

## 3. Slots (rolling, harness cap 6)

Allocate by debt, re-checked at every refill (a merge changes the numbers; `debt.py` on the stream's
own report is enough between full runs):
- decomp: unmatched functions or asm data > 0 → up to 4 slots, before everything else (decomp-unit
  §3 rounds, stop rule included).
- types: 1 slot while `pending.md` has an unheld item or a names worker wrote a header request
  (mixed-meaning fields: union carve keeping the dominant old name, the dominant rename then goes
  through a names window so the ledger carries; 2026-11-20: Actor.unk155 1485 refs).
- the rest split hack / names / polish in proportion to stream debt, at least 1 slot each for a
  stream with debt > 0 and an unexhausted queue item; a stream whose queue is all EXHAUSTED, held or
  blocked gets none, whatever its debt (2026-11-20: hack and polish were all EXHAUSTED, names took
  every slot: one worker per record or per 3-7 neighbouring files' `D_`, or per file of `func_`).
- one src file in one slot at a time (types batches list theirs in `files.txt`); names workers check
  out nothing and never block another slot.
Refill a slot the moment its worker reports and its merge lands. No rounds: nothing waits for the
slowest worker. Names yield falls once every file has had a reader: the leftovers are held items
(no evidence), macro uses (hand edits, inspected) and rulings; stop names slots there.

## 4. Merge and record

Per stream, exactly as its skill says: decomp `skill://decomp-unit/merge.md` + `ledger.py record`;
hack/polish/types `skill://cleanup-unit` §5 (`tools/merge_record.py`, `MERGE_RECORD_OK`); names
proposals are not merged: check each against [names.md](names.md) "Check" and apply them with
`tools/names_window.py` as reports land (one window per 2-4 reports; 2026-11-20 windows of 184-570
renames carried every review). A types batch whose sites move to new members stales those
functions' reviews (carry: `not a pure rename`): one ledger-only re-review worker records them
before the next window. Every commit passes the full ROM gate; a merged file's net hacks and cfe
warnings never rise.

## 5. Close (user asks to stop, or every stream's queue is empty/exhausted/held)

1. No new dispatches; merge what lands. Once every worker is idle: apply the names queue again
   (step 2: the close is the next quiet window), then cleanup-unit §6 steps 2–5 (carry, knowledge
   queue, ROADMAP `### 11` table via `quality.py report --baseline`, `sessions.md` row).
2. `bash autoresearch.sh` again: record start → end debt and each stream's delta in one row of
   [run-log.md](run-log.md) (keep the last ~10).
3. Fold procedure lessons into the file that owns them (this skill for allocation; the stream skills
   for their own procedure), within the size caps (SKILL.md and references ≤ 150 lines, briefs ≤ 180);
   commit `continue-unit skill: <what changed>`.

## Invariants

- `src/` and `include/` change only through the gates (merge_gate / merge_record, the names window).
- Never trade one stream's debt for another's: a rename that adds a cast, a hack fix that adds a
  warning, a carve that unreviews 100 functions without measuring (types-stream.md) all count.
- Never game the score: names describe confirmed behaviour (no `field_0x10`, `padXX`, `data_XXXX`),
  a `// FAKE` tag goes only with its steer, counters and weights are not edited to move the number.
