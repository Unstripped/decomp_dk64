---
name: cleanup-unit
description: Orchestrate one round of the DK64 code-quality campaign (remove FAKE hacks and gotos, consolidate prototypes, shared types, names) over matched C with subagents and the quality ledger. Use when asked to run the next cleanup/defake/quality unit on this decomp.
---

# DK64 cleanup unit

Every function is matched; this campaign makes the matched C readable without losing the
match. One round = pick up to 6 files, one agent per file in PRIVATE COPY mode, merge through
the gate, record every result in `drafts/quality/`, apply cross-file names. AGENTS.md rules
always apply. IDO facts: `knowledge/ido/` (`tools/quirks.py`); merge: `skill://decomp-unit/merge.md`.

|File|Read when|
|---|---|
|[brief.md](brief.md)|fill into `local://cleanup-brief.md` before dispatch|
|[ladder.md](ladder.md)|choosing an agent's next method; checking a report's LEDGER block|
|[naming.md](naming.md)|phase 4 and round-end renames|
|[run-log.md](run-log.md)|sizing a round; Close appends a row|

## 0. Model

Use the model the user named for every worker spawn (`task` `model`; none named: ask once). With
`task.perCallModel: off` spawn without it only if the default task agent runs that model
(`history://<agent>`), else tell the user. Never run `ledger.py plan`/`route`, never write
`.scratch/routes/`, never use workpools routed by `.omp/extensions/decomp-router.ts`.

## 1. Ingest

1. `git status` (unexpected changes are the user's: never stage them).
2. `find src -name '*.c' -exec touch {} +`; `tools/dk make` must end `build/dk64.us.z64: OK`;
   `tools/dk make expected`.
3. `uv run tools/protos.py gen --check` exits 0 (else regenerate and commit `include/proto` first);
   `uv run tools/clint.py compdb`; `uv run tools/quality.py report --markdown` → starting numbers.

## 2. Pick

1. `uv run tools/quality.py rank --limit 6`: the top files, at most 6, one agent each (never two per file).
2. `uv run tools/quality.py status --file <f>` for each: a site showing `stale` gets a fresh
   `uv run tools/quality.py sweep <f> -j 4 --record --unit "<YYYY-MM-DD>: <unit>"` first.
3. Base commit = `git rev-parse HEAD` after those records are committed;
   `python3 tools/merge_drafts.py snapshot src/<seg>/<f>.c` per file.

## 3. Dispatch

Fill the WHOLE [brief.md](brief.md) into `local://cleanup-brief.md` (director mode:
`.scratch/cleanup-brief.md`, one `# Round N` section; `rename.py fold` reads the last one). Spawn
one agent per file, named `Clean<File>`, task context "Read the brief FIRST and follow it exactly".
Files of 100+ functions take 2–4 agent turns (per-turn request budgets): merge and record
between passes and send the agent back with the new base. Per-file phase order (one agent does all five):

1. types: local views of shared globals become shared types; casts become real fields; `warning`
   sites are retyped (`retype`); then `uv run tools/quality.py sweep <copy> --copy-of <src>`;
2. defake: the ladder ([ladder.md](ladder.md)) for each OPEN site, tagged and untagged, in `status` order;
3. gotos; 4. names: locals, params, file-local struct fields (`rename.py local`/`field` on the copy);
5. review: every function top to bottom, also those with no sites, against the checklist;
   one `review` line per function in the LEDGER block; a new problem becomes a site and goes
   back through phases 2–4 in the same task.

## 4. Headers

Agents never edit `include/`: they write the exact hunk to `.scratch/<A>/header-request.md`. A
function defined in the agent's own file needing a new prototype type is no header request: it
retypes the definition with a stand-in (`#define PROTO_SKIP_<f>` + declaration), merged via §5.4.
Applying a request: carve only padding, keep landed names, list users with `uv run tools/rename.py
field --dry-run include/<h>.h <Struct> <field> zzProbe` (+ text-grep casts), skip checked-out files'
fields; snapshot and edit users, objdiff each, `clint.py layout --base HEAD include/<h>.h` → `LAYOUT
OK`, `tools/merge_gate.sh --commit "include: <what>" --stage include/<h>.h - - <src files>` (anchor
one includer). A header commit stales the automatic rungs of every function reaching the changed
declarations (`fp_hdr2`). Gate a field TYPE change apart from carves/moves: `carry --header-carve`
then plain `carry --rev <commit before> <files>` re-stamp carves, moved types, respelled declarations
and pure typedef renames, never a type change. Before committing a widely reached change, measure
the stale cost (full `status` before/after, functions losing fresh non-sweep rungs after a carry
`--dry-run`); hold it above ~100 functions.

Callee-prototype work is its own workstream, prepared by a batch worker in `.scratch/<A>/<name>batch/`
(owner + caller copies, `measure.json` per-file cfe before/after, `ledger/<file>.txt`; verify header edits with a
full copy of `include/` (shadow-prepending leaks through quoted includes in real headers)). Measure on the
checked-out agents' copies too: if any would rise, hold the batch and gate it in ONE unit with those
copies. Merge owner + callers, `protos.py gen`, objdiff every includer, one gate with every `--stage`d
header; sweep + carry. A batch stales the review of every caller whose BODY it edits: list them and
run a grouped re-review pass after the batches (batch → re-review loop, round 16).

## 5. Merge

As each agent reports:
1. Check the report: every site of its file in the LEDGER block, one `review` per function, evidence present (ladder.md); missing lines go back.
2. `uv run tools/clint.py uninit .scratch/<A>/<f>.c --base src/<seg>/<f>.c` must exit 0.
3. Merge per decomp-unit merge.md:
   `tools/merge_gate.sh --commit "<seg>: clean <f> (<n> FAKE −, <n> goto −)" .scratch/<A> <base> src/<seg>/<f>.c`.
   Read `GATE_OK` and `COMMITTED`; never pipe the gate.
4. A copy that changed a non-static signature carries stand-in `#define PROTO_SKIP_<f>` lines plus
   declarations: after the merge delete both, `protos.py gen` (a SKIPped function keeps its in-file
   declaration), objdiff every caller and includer, gate `--stage include/proto/<seg>/<f>.h - -
   src/<seg>/<f>.c` (one `--stage` per header written); `protos.py gen --check` then exits 0.
5. Knowledge is queued, not filed: append the report's IDO findings (file, function, merge commit,
   rule, see-also IDs) to `.scratch/r<N>-knowledge-queue.md`. A knowledge commit stales every rung
   whose function it names or whose note ranks it in the top 8, so filing per merge staled the
   round's own earlier events (round 16: 137 of 201 stale rungs). §8 files the queue once.
6. Record (the copy's file-scope edits change most fingerprints; ok-fine
   `playbooks/cleanup-merge-and-record`): every function the report says it reviewed must have a
   `func:` review line (else send it back); `record --base <copy base> --batch ledger.txt`
   (all-or-nothing); `make expected`; `sweep <src> --record`; re-record the same lines
   `--base <merge commit>` after applying the key map and dropping the removed sites' lines
   (`no site` in `--dry-run`); `ledger-copy-only.txt` at the merge commit; then `carry --rev
   <merge>^ <src>`. A batch's `fixed` lines for sites it removed: `record --base <patch base>`. Commit `drafts/quality/`.
7. Bundles: strip stand-ins, apply the `.patch` (not shadow headers), merge, gen, objdiff callers
   (`--reloc-ok`), one gate. Copies keyed by the same basename (`boss/52B0` vs `race/52B0`,
   `critter/0` vs `minecart/0`) need separate dirs and gates. A gate failing with `cfe: ... if
   directive is not terminated` on unchanged headers is a stale dkd server: `(cd .scratch/gate &&
   ../../tools/dk --stop)` and rerun. Commit explicit paths only. A copy retyping a shared global's
   extern: fix every other file's extern in the SAME gate (objdiff each).
Invariants: `src/` and `include/` change only through the gate; every commit passes the full ROM
gate; a merged file's net HACKS (tagged `// FAKE` + untagged AST sites) and cfe warnings never rise.
Tag pre-existing untagged hacks ("pre-existing, now tagged"). A K&R → ANSI conversion may expose a
pre-existing uninit read (same code at HEAD): accept with a note. `make expected` before sweeping a
merged file that differs from `expected/` only in relocations (else sweep skips it).

## 6. Round end

Once every agent of the round is idle:
1. Apply proposed `func_`/`D_`/shared-field names ([naming.md](naming.md)) with `rename.py
   func|global|field` (dry-run first; skip names whose dry-run touches a checked-out file).
2. `tools/dk make split`, touch all src, `tools/dk make` OK, `tools/dk make expected`,
   `python3 tools/unit_check.py vanished` → `vanished OK`; commit `<seg>: name N symbols` (symbol
   files, renamed src, moved drafts, the `include/proto` headers `gen` rewrote).
3. A rename changes the fingerprints of every function it touches: `carry --rev <commit before
   the renames> --unit "<unit>"` re-stamps pure renames (it lists what it skipped: sweep those). Commit.
4. Re-review: functions still `review=stale` in the round's touched files (bodies edited by batches)
   plus those files' never-reviewed OPEN functions go into ~3 whole-file groups in
   `.scratch/rereview<N>.md`, one agent per group (checkpointing per brief.md).

## 7. Stop rule

A file is done when `quality.py status --file` shows every function EXHAUSTED (fresh `review`, every
site fixed or exhausted); one with any OPEN function goes back into the next ranking. The campaign is
done when `report` shows `reviewed <n>/<n>` and `rank` lists no OPEN function. A `proto-type` site stops blocking its
function only once the types phase recorded `views` `blocked` with a reason.

## 8. Close

1. `uv run tools/quality.py report --baseline 2b2532bc --markdown` (campaign start) replaces
   the table in ROADMAP.md `### 11. Code quality (ongoing)` under "To do".
2. File the knowledge queue in ONE commit: a new entry per finding with `--see-also` (extend an
   entry only to correct it: an edit stales every rung citing it); drop pure confirmations; tooling
   rules go into ladder.md, not `knowledge/ido`; `quirks.py check`. Then count what it staled: for
   each OPEN function's stale rung compare `fp_local` (text), `hdr_fresh` (automatic rungs) and
   `ledger.related_knowledge` paths committed after the event (`.scratch/r16_census.py`). Re-record
   only rungs staled by procedure-only entries with unchanged text, never codegen-staled ones.
3. Procedure lessons → this skill (caps: SKILL.md and references ≤150 lines, brief.md ≤180; a
   lesson replaces or merges text). 4. One [run-log.md](run-log.md) row; commit `cleanup-unit skill: …`.
