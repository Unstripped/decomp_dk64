---
title: "IDO uopt temp frame slots: how spilltemps orders them"
description: "How IDO 5.3 uopt assigns frame slots to CSE/PRE temporaries (spilltemps: candidate-bit order, slot reuse when regions do not overlap), how to observe it with uopt_trace levels 3-6, and which C changes move a temp. Learned on func_807024E0 (103AB0.c)."
origin: "ok-fine dk64/notes/ido-uopt-temp-slots"
---
The frame area between the outgoing-argument/saved-register block and the declared locals holds uopt temporaries. Their order is not program order; it comes from `spilltemps()`.[^uoptreg2]

## Mechanism

- **Phase order** in `oneproc`: `getexpsources` (computes each node's PRE `region`, unions them into `coloreditems`) -> `makelivranges` (adds sub-expressions inserted by code motion to `region`/`coloreditems`) -> `regdataflow` -> `localcolor` -> `spilltemps` -> `globalcolor` -> `reemit`.[^uoptmain]
- **`spilltemps`** walks candidate bits `0..firstconstbit` in bit order. Every bit in `coloreditems` gets a slot: the first existing slot of the same size not used by a lower bit whose region shares a flow-graph node, otherwise a new slot below the previous one (8-byte temps are 8-aligned).[^uoptreg2]
- **Temps that end up in registers keep their slot.** Unused 4-byte holes in the temp area are register-coloured temps (or alignment padding before an 8-byte double temp), not missing locals.
- **Block-local CSE temps** (`count > 1` inside one block) are allocated later in `reemit` by `gettemp`, reusing any slot that no item live in that block holds.[^uopttemp]
- **Candidate bits** are the `bit` column of the `uopt_trace.sh` candidate table. They follow ucode input order, after same-block substitution of locals; expressions created by global copy propagation get late bits, roughly bottom-up through the function. So a value whose variable is assigned in another basic block, or copied through another variable, is a late bit, and its temp is pushed down.

## Observing it

`tools/uopt_trace.sh -l 4` prints each node's final `region`/`source`/`sink`; `-l 3` prints `insert`/`subinsert`/`delete`; `-l 5`/`-l 6` print the candidate table and colouring.[^uopttrace] Emulating `spilltemps` from these (level-4 regions plus the isop bits that appear in the `-l 6` colouring list but not in any level-4 region, given the nodes where their parent is inserted) reproduced the stored-temp layout of a 931-instruction draft to within one slot.

## What moves a temp (func_807024E0)

- No effect: declaration order of locals, statement order of loop-invariant assignments at a loop top, moving them into the inner loop, or rewriting `for` as `while`; uopt canonicalises all of these.[^src103ab0]
- Effect: a local's type (an `s32` copy of a `u8` argument gets its temp right after the other loop-top values; a `u8` one does not), whether a value is a named variable or written inline (changes which ichain owns the temp), and an extra copy variable (makes the uses late bits and can introduce a register `move`).
- Frame accounting: frame = declared locals (including one slot per gbi macro `_g` block local) + temps + saved registers + outgoing arguments. If the first temp sits N words too low while the frame size matches, the draft has N extra declared words and N fewer temps; pad locals hide this and break the temp order.

Related: IDO uopt statics, live ranges and temps (guide ido-uopt-statics-and-live-ranges: python3 tools/quirks.py get ido-uopt-statics-and-live-ranges), large functions and near-misses (guide large-functions-and-near-misses: python3 tools/quirks.py get large-functions-and-near-misses).

[^uoptreg2]: n64decomp/ido `src/uopt/uoptreg2.c`, `spilltemps`.
[^uoptmain]: n64decomp/ido `src/uopt/uoptmain.c`, `oneproc`.
[^uopttemp]: n64decomp/ido `src/uopt/uopttemp.c`, `gettemp`/`findbbtemps`.
[^uopttrace]: `tools/uopt_trace.sh` debug levels.
[^src103ab0]: experiments on `func_807024E0` in `src/global/103AB0.c` (draft `drafts/global/func_807024E0.c`).
