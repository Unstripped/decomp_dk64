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

Use the model the user named when starting the run for every worker spawn (`task` `model`
field). None named: ask once before the first spawn. With `task.perCallModel: off` the field is
rejected: spawn without it only if the default task agent runs that model (its transcript's
`"model"` entries, `history://<agent>`), else tell the user. Never run `ledger.py plan`/`route`,
never write `.scratch/routes/`, never use workpools routed by `.omp/extensions/decomp-router.ts`.

## 1. Ingest

1. `git status` (unexpected changes are the user's: never stage them).
2. `find src -name '*.c' -exec touch {} +`; `tools/dk make` must end `build/dk64.us.z64: OK`;
   `tools/dk make expected`.
3. `uv run tools/protos.py gen --check` must exit 0 (else regenerate and commit `include/proto` first).
4. `uv run tools/clint.py compdb` (agents' `lsp` tool resolves references through it).
5. `uv run tools/quality.py report --markdown` → the round's starting numbers.

## 2. Pick

1. `uv run tools/quality.py rank --limit 6`: the top files, at most 6, one agent each.
   Never two agents on one file.
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
3. gotos;
4. names: locals, params, file-local struct fields (`rename.py local`/`field` on the copy);
5. review: every function top to bottom, also those with no sites, against the checklist;
   one `review` line per function in the LEDGER block; a new problem becomes a site and goes
   back through phases 2–4 in the same task.

## 4. Headers

Agents never edit `include/`: they write the exact hunk to `.scratch/<A>/header-request.md`
and message you. A function defined in the agent's own file whose generated prototype needs a
new type is NOT a header request: the agent retypes the definition, verifies with a stand-in
(`#define PROTO_SKIP_<f>` + the new declaration) and you merge via §5.4. Before applying a
request: carve only padding, reconcile with fields already landed (keep existing names), list
every user with `uv run tools/rename.py field --dry-run include/<h>.h <Struct> <field> zzProbe`
(it lists macro uses as `MACRO`; text-grep casts like `*(f32 *)p->f` too), skip fields used by
a checked-out file. Snapshot users, edit them, `touch` + `tools/objdiff.sh` each, then
`uv run tools/clint.py layout --base HEAD include/<h>.h` → `LAYOUT OK`, then
`tools/merge_gate.sh --commit "include: <what>" --stage include/<h>.h - - <edited src files>`
(anchor one src file if none). Each header commit stales the automatic rungs (sweep methods,
consolidate, views, names) of every function reaching the changed declarations (`fp_hdr2`). Gate a
field TYPE change apart from padding carves and type moves: carry re-stamps carves, moved types and
respelled declarations (`--header-carve`, then plain `carry --rev <commit before> <touched files>`), never a
type change; for what both skip, re-sweep `--record` and re-record the agents' lines. Carry also re-stamps a pure
local typedef rename (c8455c73). A header-only gate still needs one anchor src file (an includer).

Callee-prototype work is its own workstream, prepared by a batch worker in `.scratch/<A>/<name>batch/`
(owner + caller copies, `measure.json` per-file cfe before/after, `ledger/<file>.txt`; verify header edits with a
full copy of `include/` (shadow-prepending leaks through quoted includes in real headers)). Measure on the
checked-out agents' copies too: if any would rise, hold the batch and gate it in ONE unit with those
copies. Merge owner + callers, `protos.py gen`, objdiff every includer, one gate with every `--stage`d
header; sweep + carry. A batch stales the review of every caller whose BODY it edits: queue a grouped re-review pass.

## 5. Merge

As each agent reports:
1. Check the report: every site of its file in the LEDGER block, one `review` per function, evidence present (ladder.md); missing lines go back.
2. `uv run tools/clint.py uninit .scratch/<A>/<f>.c --base src/<seg>/<f>.c` must exit 0.
3. Merge per decomp-unit merge.md:
   `tools/merge_gate.sh --commit "<seg>: clean <f> (<n> FAKE −, <n> goto −)" .scratch/<A> <base> src/<seg>/<f>.c`.
   Read `GATE_OK` and `COMMITTED`; never pipe the gate.
4. A copy that changed a non-static signature carries stand-in `#define PROTO_SKIP_<f>` lines
   plus declarations: after the merge delete both, `uv run tools/protos.py gen` (a function it
   SKIPs, e.g. untagged local struct param, keeps its in-file declaration), objdiff every caller
   and includer, then `tools/merge_gate.sh --commit MSG --stage include/proto/<seg>/<f>.h - -
   src/<seg>/<f>.c` (one `--stage` per header written). Afterwards `protos.py gen --check` exits 0.
5. Knowledge first: file the report's IDO findings (`quirks.py search`, edit the entry or `add
   --source <path>@<merge commit>`; `quirks.py check`) and commit BEFORE recording (a later
   knowledge commit stales events naming its functions).
6. Record (the copy's file-scope edits change most fingerprints; ok-fine
   `playbooks/cleanup-merge-and-record`): `record --base <copy base> --batch ledger.txt`
   (all-or-nothing); `make expected`; `sweep <src> --record`; re-record the same lines
   `--base <merge commit>` after applying the key map and dropping the removed sites' lines
   (`no site` in `--dry-run`); `ledger-copy-only.txt` at the merge commit; then `carry --rev
   <merge>^ <src>`. A batch's `fixed` lines for sites it removed: `record --base <patch base>`. Commit `drafts/quality/`.
7. Bundles: strip stand-ins, apply the `.patch` (not shadow headers), merge, gen, objdiff callers
   (`--reloc-ok`), one gate; two `0.c` copies need two dirs. Commit explicit paths only. A copy
   retyping a shared global's extern: fix every other file's extern in the SAME gate (objdiff each).
Invariants: `src/` and `include/` change only through the gate; every commit passes the full ROM
gate; a merged file's net HACKS (tagged `// FAKE` + untagged AST sites) and cfe warnings never rise.
Tag pre-existing untagged hacks ("pre-existing, now tagged"). A K&R → ANSI conversion may expose a
pre-existing uninit read (same code at HEAD): accept with a note. `make expected` before sweeping a
merged file that differs from `expected/` only in relocations (else sweep skips it).

## 6. Round end

Once every agent of the round is idle:
1. Apply proposed `func_`/`D_`/shared-field names ([naming.md](naming.md)) with
   `uv run tools/rename.py func|global|field ...` (dry-run first; check the evidence line: a
   field read as a volume in one place and a pitch in another is not confirmed).
2. `tools/dk make split`, `find src -name '*.c' -exec touch {} +`, `tools/dk make` OK,
   `tools/dk make expected`, `python3 tools/unit_check.py vanished` → `vanished OK`.
3. Commit `<seg>: name N symbols` (symbol files, renamed src, moved drafts, the `include/proto`
   headers `gen` rewrote).
4. A rename changes the fingerprints of every function it touches: `carry --rev <commit before
   the renames> --unit "<unit>"` re-stamps pure renames (it lists what it skipped: sweep those). Commit.
5. Re-review: functions still `review=stale` in the round's touched files (bodies edited by batches)
   go into ~4 balanced whole-file groups in `.scratch/rereview<N>.md`, one agent per group.

## 7. Stop rule

An assigned file is done when `quality.py status --file` shows every function EXHAUSTED:
a fresh `review` and every site fixed or exhausted. A file with any OPEN function goes back
into the next round's ranking. The campaign is done when `quality.py report` shows
`reviewed <n>/<n>` and `rank` lists no OPEN function. A `proto-type` site stops blocking its
function only once the types phase recorded `views` `blocked` with a reason.

## 8. Close

1. `uv run tools/quality.py report --baseline 2b2532bc --markdown` (campaign start) replaces
   the table in ROADMAP.md `### 11. Code quality (ongoing)` under "To do".
2. Procedure lessons → this skill (caps: SKILL.md and reference files ≤150 lines, brief.md
   ≤180; a lesson replaces or merges text). IDO facts were filed per merge (§5.5); a fact filed
   now stales the round's events for the functions it names: re-record those lines after it.
3. Append one [run-log.md](run-log.md) row; commit `cleanup-unit skill: <what changed>`.
