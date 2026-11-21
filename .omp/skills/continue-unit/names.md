# Names stream

The largest debt by weight is names (`unkXX` field references, `D_` references, `func_` definitions):
one rename retires every reference at once, so the stream works by reference count, not by file.
Research runs in parallel (names workers read code, propose, edit nothing); renames land only in a
names window (unit start or close, no private copies checked out) because they touch many files.

## Queue

`uv run tools/debt.py names [--seg SEG] [--limit N]`: unkXX fields grouped by declaring record (with
its header), `D_` globals by name space (an address in overlay VRAM `0x80024000`–`0x805FB300` is the
referencing overlay's; any other is one boot/global symbol, refs summed over every segment, renamed with
`rename.py global global`, whichever overlay file uses it), `func_`
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
   Names workers check out nothing, so a window may run while they work (token renames keep their
   file:line evidence valid): apply each report's batch as it lands.
2. `base=$(git rev-parse HEAD)`. Fields: all lines in one batch file, `rename.py fields <batch> --dry-run`
   (seconds; refused lines print `REFUSE`), snapshot, then without `--dry-run`. Globals/functions: per line
   `rename.py global|func --dry-run <seg> <old> <new>`, `python3 tools/merge_drafts.py snapshot <every src
   file listed>` (the gate needs a base for each), then the command (it also renames `data_inc.us.txt`
   rows and regenerates their `assets/inc` file). Two workers naming one symbol: the first applied wins
   (the second prints `not found`). A refusal stays in the queue with the reason.
3. naming.md "Round-end check" (`make split`, touch, `make`, `make expected`, `unit_check.py vanished`,
   `-w` stat compare), then one gate: `tools/merge_gate.sh --commit "<unit>: name N symbols" --stage
   include/<h>.h... --stage symbol_addrs*.txt [--stage data_inc.us.txt] - - <touched src files>`.
4. `uv run tools/quality.py carry --rev <gate commit>^ --unit "<unit>" <touched src files with functions>`
   (`--dry-run` first: every line must say `identifier renames only`; a data-only file such as
   arcade/E220.c cannot compile at REV after an inc rename: leave it out). Window 1 carried 826 of 826
   functions; commit `drafts/quality` with the emptied queue.
