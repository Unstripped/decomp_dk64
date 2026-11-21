# Names stream

The largest debt by weight is names (`unkXX` field references, `D_` references, `func_` definitions):
one rename retires every reference at once, so the stream works by reference count, not by file.
Research runs in parallel (names workers read code, propose, edit nothing); renames land only in a
names window (unit start or close, no private copies checked out) because they touch many files.

## Queue

`uv run tools/debt.py names [--seg SEG] [--limit N]`: unkXX fields grouped by declaring record (with
its header), `D_` globals per segment (boot+global one space, each overlay its own), `func_`
definitions per segment, highest reference count first. Totals equal the report's `unk fields` /
`D_ refs` rows. Skip items already in `drafts/cleanup/names-queue.md` or held there.

Give each worker one record (all its top unk fields), or 10–20 globals / `func_` functions of one
subsystem (same file or neighbouring files), so one reading of the code names several items.
A field used with different meanings by different actor types is not a names item: its worker
writes the union/view split as a header request for `TypesOwner` (types-stream.md) instead.

## Check (lead, each report)

Per proposal, before appending it to the queue:
- the rules of [naming.md](../cleanup-unit/naming.md) "Rules" (no offset/address-encoding names, no
  name in scope, no macro references, not `include/PR`/`include/libultra` prototyped);
- `--dry-run` of the exact `rename.py` command prints only the positions the proposal lists
  (`field` lists every user: the worker's evidence must cover every file it prints);
- evidence is behaviour seen in the code (what is stored, compared, passed), never the address,
  the m2c type or a guess from one site; an unconfirmed item stays unnamed (`held: <why>`).

## Queue file (`drafts/cleanup/names-queue.md`, tracked)

One line per accepted proposal, appended by the lead, deleted by the window that applies it:
`- [field|global|func] <seg or include/h.h> <Record|-> <old> -> <new> | <evidence, file:line> | <worker>`
`held:` lines keep an item out of the queue until new evidence arrives.

## Apply (names window)

1. Nothing checked out: no worker copy, no open types batch (`.scratch/TypesOwner/batch_*/files.txt`).
2. `base=$(git rev-parse HEAD)`. Per line: the `rename.py` command with `--dry-run`, then
   `python3 tools/merge_drafts.py snapshot <every src file it lists>` (the gate needs a base for each),
   then the command without `--dry-run` (`field include/<h>.h <Record> <old> <new>`, `global <seg> <old>
   <new>`, `func <seg> <old> <new>`). A refusal (macro, in scope) stays in the queue with the reason.
3. naming.md "Round-end check" (`make split`, touch, `make`, `make expected`, `unit_check.py vanished`,
   `-w` stat compare), then one gate: `tools/merge_gate.sh --commit "<unit>: name N symbols" --stage
   include/<h>.h... --stage symbol_addrs*.txt - - <touched src files>`.
4. `uv run tools/quality.py carry --rev $base --unit "<unit>" <touched src files>` (field renames of
   shared records carry; a skip line names what did not), commit `drafts/quality` with the emptied queue.
