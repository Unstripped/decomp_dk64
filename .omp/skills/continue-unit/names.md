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
   (the second prints `not found`). A refusal stays in the queue with the reason. A cross-segment alias (one
   address named in symbol_addrs.us.txt and an overlay's file) renames in one run from either side (9496edbb).
3. All of steps 2-4 in one command: `python3 tools/names_window.py --unit "<unit>" --message MSG
   [--fields F]... [--globals SEG:F.tsv]... [--funcs SEG:F.tsv]... [--macro-arg FILE:LINE:COL]...
   [--in-macros D_X]...` (dry-run first with `--dry-run`; keep func and global tsv names distinct: a
   `w-global-*` glob once swallowed func files). It snapshots, renames, splits, builds, gates, then
   runs `carry --rev <gate>^` once per touched file (aliasing renamed `assets/inc` files for REV's text),
   printing each file's result (a failure prints the command, exit code and stderr tail and names the
   files not yet carried: finish with the printed `retry:` command), and `carry --header-carve` when a
   header changed: without it every function reaching a
   renamed field loses its automatic rungs (unit 1: sites_open 8 -> 120). Commit `drafts/quality`.
4. Macro uses: a field spelled as a macro argument at the call site (`MIN(p->unkD, x)`) or a global in
   a `#define` body is renamed only after reading that line: `--macro-arg` with the exact column,
   `--in-macros` per global. A field used inside a macro's own body stays unnamed (rename the macro).
5. Check carry's skip lines: `not a pure rename` on functions whose bodies only changed by renames
   means a carry gap (fix `tools/quality.py`, e.g. renamed callees), not a re-review; a union carve's
   moved sites are real re-reviews (one ledger-only worker).
