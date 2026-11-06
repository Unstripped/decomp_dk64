---
title: "IDO loadOverlay: matching through coordinated cross-loop lifetimes"
description: "How loadOverlay reached a byte-exact ROM match: coordinated q/p/hp lifetime reuse resolves the final seven register-allocation differences."
origin: "ok-fine dk64/notes/ido-load-overlay-diagnostics"
---
# IDO loadOverlay diagnostics

Matched on 2026-11-04: `loadOverlay` is ordinary C in `src/global/15050.c`, not parked. All 423 instructions (1,692 bytes) match after linking; the full ROM SHA-1 passes. The preceding park was full 8 / text 7 / reloc 1. Coordinated pointer reuse across the survivor, rebuild and final clearing loops resolved every text difference; `D_80744478 - 8` versus `D_80744470` remains only an equivalent relocation spelling.[^c]

## How uopt picks a register (read before guessing)

`uoptreg2.c` colours candidates in descending `adjsave` (ties: lowest bit = first appearance in the ucode) and assigns the **cheapest register not in the candidate's `forbidden` set**: `cupcosts` (2094–2140) charges a move cost per caller-saved register for live units adjacent to a call and a first-use cost for callee-saved registers not yet used; among equal costs the lowest-numbered register wins, which is the whole story for call-free ranges like the ones here but not for ranges spanning a call (where a callee-saved pick or a spill is a cost decision, see the `s4` vs `a0` case below). `forbidden` = union over every basic block of the candidate's live range of `node->regsused`, plus the registers of already-coloured interfering ranges; interference is block-granular (`intfering` = live-block sets intersect). `regsused` of a block contains the argument registers of every call parameter in that block (`Upar`), the precoloured parameters in the entry block, and every register assigned so far to a range live in that block. So a variable's register is explained by (a) what was coloured before it (priority) and (b) which blocks its range touches.[^reg2][^reg1]

Two consequences used here:

- **One variable reused in two regions unions the forbidden sets.** `hp` used in both survivor loops gets one register; the first loop's block contributes `v0` (the handle value) and `a0,a1,a2` (the call arguments), so `hp` lands in `a3` as soon as `v1` is also forbidden. (The resolved `v1` occupant is `p`, shared with the final clearing-loop bound.)
- `q` used for `HL(i-1)`, `*hp`, the saved-header pointer, the rebuild-loop predecessor and the final loop's pointer is coloured first (highest priority) and `v0` everywhere, which is why `lw v0,0(t9)` and `lw v0,0(a3)` share a register: they are the same variable, not a ugen temp.

## Call-argument precolouring needs an unconverted expression

`makelivranges` precolours an `isop` argument to its argument register only when the parameter statement's expression *is* the candidate (`uoptreg1.c` ~1862). A conversion node (`u32` expression passed to a pointer or `s32` parameter) makes the `ucvt` the parameter and the shared sub-expression an ordinary candidate, which then prefers a callee-saved register (`s4`) across the call instead of `a0` plus a spill. loadOverlay's loop 1 passes `(u32)q - 0x10` to `heapMoveWords`/`heapRebaseHandles` three times (size load + two calls); declaring both callees with `u32` parameters gives the target's `addiu a0,v0,-16; lw s3,4(a0); sw a0,0x4C(sp)` and the reload after the call.[^reg1][^c]

## Expression candidates spill to templocs, variables to their home

A 3-use expression kept across a call is saved to a **temploc** below the locals (`sw a0,0x4C(sp)` here, where `0x4C` is below every declared local), whereas a variable is saved to its home slot. `def Mmt len` in the uopt output = declared locals + templocs (call-save templocs for spilled expression candidates, then `spilltemps` slots for cross-block `coloreditems`, rounded to 8). This is how to tell from a spill offset whether the original had a variable: loadOverlay has no `src` local; it has a 4-slot temp area (`0x40..0x4C`).[^reg2][^c]

## Copy propagation of a pure expression into a loop costs a temploc

`fb1 = ((size + bssSize + 0x8002403F) & ~0x3F) + lo` is propagated into the loop's `fb1 + lo` (`uoptcopy.c` `find_replacements`: refused only for `has_ilod`, `is_incr` (param +/- const), `countvars >= 10`, or when the assignment is not available, e.g. it contains a global load killed by the loop's stores). The propagated expression becomes a cross-block `coloreditem` (one temploc). That is correct here: the target's frame needs exactly that slot, the and-expression X is then a 2-use candidate coloured `v0` (`addu v0,s0,t9; addu v0,v0,at; and t4,v0,at; sw t4; addu a2,t4,t0`), and `fb1` is no local. A single-use X is evaluated in `t4..t6`.[^copy][^c]

## cfe operand order and offset folding

- cfe evaluates the operand that needs a conversion first, otherwise source order: `D_80744470 + lo` emits `lo + D` when `D` is `u32` and `lo` `s32`, and `D + lo` when both are `s32` (`addu a2,t4,t0`). `q + size` with `u8 *q` keeps `size` first (`addu s2,t4,v0`); a cast on `q` flips it.
- uopt folds a constant into a load offset for signed or pointer arithmetic (`((HeapBlock *)(x - 0x10))->size` with `s32`/`u8 *` x becomes `lw -12(x)`) but **not** for `u32` arithmetic cast to a pointer (`lw 4(reg)` from the subtracted value). Choose the type by which form the target shows.[^c]

## Other levers that landed

- No `FAKE` in region 1: the CSE temp of `0x805FAE00 - cur` (`D_8076A060` store then `h`) is coloured `a3` in the preheader and forbids `a3` for `cur`, which is what the old `if (D_8074450C != 0) {}` FAKE did.
- Rebuild block: `sz = pool.size - 0x20; freeList = (u32)blk + blk->size + 0x10; sz = start + (sz - freeList); freeList->physPrev = blk; freeList->size = sz;` reads `size`/`start` before the indirect store without FAKE preloads, keeps `(sz - freeList) + start` association, and reusing `sz` raises `last` above the `&D_807F0988` address in priority (`last` = `v0`, address = `a0`).
- Final loop as `for (id = 0; id < 2; id++) q = (&D_80744470)[id]` emits the pointer base with the region loads (last), matching `addiu a1` after `addiu t1`; an explicit `p = &D_80744470` is a statement and comes first. uopt then names the base `D_80744478 - 8` (reloc differs, bytes do not).
- An early constant store to a later-used local (`last = NULL` at the top) does not rematerialise; it keeps the variable in a callee-saved register across calls. Dead stores to register candidates are removed and have no effect.
- ugen never uses `v0`/`v1`/`a*`/`t0..t3` for expression temps unless uopt coloured something there and it is dead at that point; `t4..t9` otherwise.
- `-Wo,-varref,N` (block split after N variable references) does not change this function for N in 6..18.

## Resolution: coordinated lifetime partitions

The matching source needs three connected choices, not one independent register tweak:[^c]

- Reuse `hp` explicitly in both survivor loops.
- Reuse `p` for the handle value in survivor loop 2 and for the final clearing-loop end pointer; the latter overlaps `q`, forbidding `v0` for `p`.
- Reuse `q` as the predecessor in the heap-rebuild loop instead of `last`. This changes the competing allocation priorities so `q` retains `v0` before `p` takes `v1` and `hp` takes `a3`.

The matched level-5 trace gives `q` candidate 117: `adjsave=126`, register 1 (`v0`), forbidden `[3 4 5]`; `p` candidate 162: `adjsave=75`, register 2 (`v1`), forbidden `[1]`; `hp` candidate 128: `adjsave=30`, register 6 (`a3`), forbidden `[1 2 3 4 5]`. Trace reproduction: `tools/dk tools/uopt_trace.sh -l 5 -s src/global/15050.c src/global/15050.c loadOverlay`.[^c]

The decisive grid tested survivor value (`h`, `blk`, `p`) × reuse in the initial pool layout × final bound × rebuild predecessor. `p` plus final-bound reuse without predecessor reuse scored full 139; adding predecessor reuse reached full 1 / text 0 / reloc 1. Thus individually worsening reuse choices must not be rejected before testing their coordinated lifetime partition. Earlier single-variable substitutions and dead-statement sweeps did not establish impossibility. No new FAKE was added; the existing rebuild-loop dead-test tag remains.[^c]

## Verification

At the source commit, full-TU `fdiff.sh` reports `TEXT OK`; `tools/merge_gate.sh` reports `GATE_OK`; `tools/dk make` in the working checkout ends `build/dk64.us.z64: OK` with all global and overlay text/data hashes passing. The gate also syntax-checks the file's `NON_MATCHING` configuration. The entire heap translation unit is now 30/30 matched, and the obsolete loadOverlay draft is removed.[^c]

## Sources

[^c]: src/global/15050.c @ 839d716e9e8d
[^reg2]: github.com/n64decomp/ido/src/uopt/uoptreg2.c @ d068e439f526
[^reg1]: github.com/n64decomp/ido/src/uopt/uoptreg1.c @ d068e439f526
[^copy]: github.com/n64decomp/ido/src/uopt/uoptcopy.c @ d068e439f526
