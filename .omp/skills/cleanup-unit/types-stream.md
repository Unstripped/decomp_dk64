# Types stream (`TypesOwner`)

Header and shared-type work is its own stream with ONE owner: `TypesOwner` is the only agent that
edits `include/`, always in its private batch copies; the lead gates its batches. Workers never
edit `include/`: they write the hunk to `.scratch/<A>/header-request.md` and message the lead,
which forwards it (`write agent://TypesOwner`).

## Queue

1. pending.md "Blocked owner/header changes" (oldest first, skipping items marked held or closed);
2. forwarded header requests, in arrival order.
Each batch works in `.scratch/TypesOwner/batch_<n>/` and first writes `files.txt`: every src file and
header it edits, one path per line. The lead dispatches no worker on a listed src file while the batch
is open, and a batch that reaches a file a worker holds waits until that worker's merge.

## Headers (unchanged rules)

A function defined in the agent's own file needing a new prototype type is no header request: it
retypes the definition with a stand-in (`#define PROTO_SKIP_<f>` + declaration), merged via SKILL §5.4.
Applying a request: carve only padding, keep landed names, list users with `uv run tools/rename.py
field --dry-run include/<h>.h <Struct> <field> zzProbe` (+ text-grep casts), skip checked-out files'
fields; snapshot and edit users, objdiff each, `clint.py layout --base HEAD include/<h>.h` → `LAYOUT
OK`, `tools/merge_gate.sh --commit "include: <what>" --stage include/<h>.h - - <src files>` (anchor
one includer). A header commit stales the automatic rungs of every function reaching the changed
declarations (`fp_hdr2`). Gate a field TYPE change apart from carves/moves: `carry --header-carve`
then plain `carry --rev <commit before> <files>` re-stamp carves, moved types, respelled declarations
and pure typedef renames, never a type change. Before committing a widely reached change, measure the stale cost with the header AND its user copies temp-swapped (header alone: users stop compiling) — full `status` before/after, then `carry --dry-run` in a temp worktree holding the commit (copy `asm/`): functions losing fresh
non-sweep rungs AND EXHAUSTED→OPEN (r18 0xEC union: 112 re-opened, one sweep; r34 MpSettings: 357 raw, 18 after carry). Hold above ~100 non-sweep losses; sweep the rest. A header change bundled with ANY body edit stales that body's agent rungs: measure even "automatic-only" changes (r34 s8: restored the local).

## Callee-prototype batches

Callee-prototype work is prepared by `TypesOwner` in `.scratch/TypesOwner/batch_<n>/`
(owner + caller copies, `measure.json` per-file cfe before/after, `ledger/<file>.txt`; verify header edits with make's compile
and `-I include` swapped for a full `include/` copy: `fdiff.sh`/`cwarn --as` shadow-prepend, so headers nested in proto headers hit the repo's). Measure on the
checked-out workers' copies too: if any would rise, hold the batch and gate it together with those
copies after their merge. Merge owner + callers, `protos.py gen`, objdiff every includer, one gate with every `--stage`d
header; sweep + carry. A batch stales the review of every caller whose BODY it edits: those show as
`next=review` in `rank --polish` and go out as polish work.

## Gating a batch (lead)

1. The stale-cost measurement above; hold or split a batch above ~100 non-sweep losses.
2. `tools/merge_gate.sh --commit "include: <what>" --stage include/<h>.h ... - - <srcs>` (or
   `.scratch/TypesOwner/batch_<n> <base> <srcs>` when the batch holds src copies); read `GATE_OK`
   and `COMMITTED`.
3. Record the batch's ledger lines as `merge_record.py` does after its gate: `uv run tools/quality.py
   record --unit "<YYYY-MM-DD>: cleanup TypesOwner" --agent TypesOwner --base <batch base> --model <selector>
   --batch <ledger>`; `tools/dk make expected`; `quality.py sweep <srcs> -j 4 --record --unit ...`;
   `quality.py carry --rev <merge>^ --unit ... <srcs>` (plus `--header-carve` for layout-keeping carves);
   commit `drafts/quality`.
4. Remove the batch's `files.txt` (its files return to the queue); move a closed pending.md item to
   its outcome line.
