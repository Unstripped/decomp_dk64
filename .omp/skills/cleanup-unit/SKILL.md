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

1. `git status` + `git log -3` (unexpected changes are the user's: never stage them; a lead whose handle died may still run: new commits or a dirty `drafts/quality/` → message it, wait until quiet).
2. `find src -name '*.c' -exec touch {} +`; `tools/dk make` must end `build/dk64.us.z64: OK`;
   `tools/dk make expected`.
3. `uv run tools/protos.py gen --check` exits 0 (else regenerate and commit `include/proto` first);
   `uv run tools/clint.py compdb`; `uv run tools/quality.py report --markdown` → starting numbers.

## 2. Pick

1. `uv run tools/quality.py rank --limit 25`: at most 6 files, one agent each (never two per file); skip files edited in the previous round and prefer the least recently dispatched (whole-file second looks produced most r35-36 fixes).
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
and pure typedef renames, never a type change. Before committing a widely reached change, measure the stale cost with the header AND its user copies temp-swapped (header alone: users stop compiling) — full `status` before/after, then `carry --dry-run` in a temp worktree holding the commit (copy `asm/`): functions losing fresh
non-sweep rungs AND EXHAUSTED→OPEN (r18 0xEC union: 112 re-opened, one sweep; r34 MpSettings: 357 raw, 18 after carry). Hold above ~100 non-sweep losses; sweep the rest. A header change bundled with ANY body edit stales that body's agent rungs: measure even "automatic-only" changes (r34 s8: restored the local).

Callee-prototype work is its own workstream, prepared by a batch worker in `.scratch/<A>/<name>batch/`
(owner + caller copies, `measure.json` per-file cfe before/after, `ledger/<file>.txt`; verify header edits with make's compile
and `-I include` swapped for a full `include/` copy: `fdiff.sh`/`cwarn --as` shadow-prepend, so headers nested in proto headers hit the repo's). Measure on the
checked-out agents' copies too: if any would rise, hold the batch and gate it in ONE unit with those
copies. Merge owner + callers, `protos.py gen`, objdiff every includer, one gate with every `--stage`d
header; sweep + carry. A batch stales the review of every caller whose BODY it edits: list them and
run a grouped re-review pass after the batches (batch → re-review loop, round 16).

## 5. Merge

As each agent reports:
1. Check the report: every site of its file in the LEDGER block, one `review` per function, evidence present (ladder.md); missing lines go back. A `review` must come from a full read of the function at the base (13D170's first pass, reviews written from a skim, went back).
2. `uv run tools/clint.py uninit .scratch/<A>/<f>.c --base src/<seg>/<f>.c` must exit 0.
3. Merge per decomp-unit merge.md:
   `tools/merge_gate.sh --commit "<seg>: clean <f> (<n> FAKE −, <n> goto −)" .scratch/<A> <base> src/<seg>/<f>.c`.
   Read `GATE_OK` and `COMMITTED`; never pipe the gate.
4. A copy that changed a non-static signature carries stand-in `#define PROTO_SKIP_<f>` + declarations:
   after the merge put the src without both into `.scratch/<x>/<f>.c`, `protos.py gen` (prints the new
   signature already), gate `--stage include/proto/<seg>/<f>.h .scratch/<x> <merge> src/<seg>/<f>.c`
   (one `--stage` per header; `- -` gates need `.scratch/bases/` snapshots); `gen --check` exits 0.
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
   `critter/0` vs `minecart/0`) need separate dirs and gates. `cfe: ... if directive is not terminated`
   on unchanged headers is a stale dkd file-size cache (rounds 13, 18): `(cd .scratch/gate && ../../tools/dk
   --stop)`, rerun; swap a main-tree header via temp + `mv` (new inode). Commit explicit paths only; headers go in `--stage`, never as a
   gate file argument. A copy byte-identical to its base is ledger-only (`cmp` first); one whose file
   changed since its base merges 3-way (`<copy-dir> <base>`). A copy retyping a shared global's extern:
   fix every other file's extern in the SAME gate (objdiff each; a file whose cfe would rise or that no longer
   compiles keeps its type and goes to the follow-ups). Check a batch copy has the edits its request claims (r21 17540).
Invariants: `src/` and `include/` change only through the gate; every commit passes the full ROM
gate; a merged file's net HACKS (tagged `// FAKE` + untagged AST sites) and cfe warnings never rise.
Tag pre-existing untagged hacks ("pre-existing, now tagged", one copy-only line each): compare `status --file` site totals base vs
applied copy; the tags are the only accepted rise (a new steer replacing untracked puns goes back, r19 b7). Accept a pre-existing uninit read a K&R → ANSI conversion exposes (note). `make expected` before sweeping a relocation-only diff.

## 6. Round end

Once every agent of the round is idle:
1. Apply proposed `func_`/`D_`/shared-field names ([naming.md](naming.md)) with `rename.py
   func|global|field` (dry-run first; skip names whose dry-run touches a checked-out file). It refuses
   references inside macros and address-shaped targets (`func_807444E0` data → `D_`): apply the
   `--dry-run` positions incl. the macro-argument lines by hand (`.scratch/r20-rename.py`), one gate. A renamed
   GLOBAL_ASM data label needs `tools/dk make split` BEFORE that gate; split labels: `rename.py fold` (dry-run first).
2. `tools/dk make split`, touch all src, `make` OK, `make expected`, `unit_check.py vanished` → OK.
3. `carry --rev <commit before the renames> --unit "<unit>" <files>` (once: a rerun duplicates events; leave out files whose
   GLOBAL_ASM paths were renamed) re-stamps pure renames; sweep what it skipped AND every file with stale automatic rungs. Commit.
4. Re-review: `review=stale` functions in the round's touched files plus their never-reviewed OPEN
   functions → ~3 whole-file groups in `.scratch/rereview<N>.md`, one agent each (brief.md).

## 7. Stop rule

A file is done when `status --file` shows every function EXHAUSTED; any OPEN function goes back into
the ranking. The campaign is done at `reviewed <n>/<n>` with no OPEN function in `rank`. A
`proto-type` site stops blocking once the types phase recorded `views` `blocked` with a reason.

## 8. Close

1. `uv run tools/quality.py report --baseline 2b2532bc --markdown` (campaign start) replaces
   the table in ROADMAP.md `### 11. Code quality (ongoing)` under "To do".
2. File the knowledge queue in ONE commit: one entry per finding with `--see-also` and `--unit U`
   (the round: its own rungs on the entry's `functions` stay fresh); extend an entry only to correct
   it (an edit stales every rung citing it); drop pure confirmations; tooling rules → ladder.md;
   `quirks.py check`. Count what it staled per OPEN stale rung: `fp_local` (text), `hdr_fresh`
   (automatic) and `ledger.related_knowledge` paths newer than the event (`.scratch/r16_census.py`);
   re-record only rungs staled by procedure-only entries with unchanged text, never codegen ones.
3. Procedure lessons → this skill (caps: SKILL.md and references ≤150 lines, brief.md ≤180; a
   lesson replaces or merges text). 4. One [run-log.md](run-log.md) row; commit `cleanup-unit skill: …`.
