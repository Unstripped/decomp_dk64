# modelAnimEntryQueueMatrixCopies (global, src/global/54150.c)
## Sites
(02baa4 fixed 2026-11-17 CleanmodelAnimEntryQueueMatrixCopies: no hack site left.)
- global:8064FA7C:dead-if:02baa4 `if (!p) {}`: its own short live range (LR8) takes uopt reg 1 ($v0) in the prologue. That pushes the gGfxBufferIndex load (LR19) to $v1 and the D_807F6BE0/E4 address temps to a2/a3.
## Attempts
- rounds 7/11 (opus:low): two dead gGfxBufferIndex tests merged into this one by the permuter; remove/cond/classify/diagnose/permute.
- 2026-11-14 U, scored with variants.py try (full=):
  - 288-body structural grid: 10 at best
  - snapshot-local grid: 10 at best
  - snapshot for the ^1 index only: 2 (a mixed spelling, a steer)
## Untried ideas
- a natural value with a short prologue live range that takes $v0 before the gGfxBufferIndex load (the target's v0 is only the loop's matrix offset load)
## Evidence
- target 0x630-0x6a0: lui/lbu v1 gGfxBufferIndex, xori t9,v1,1
- a2/a3 hold the global addresses
- blez entry guard on matrixCount (0x6b8)
- p in s0 = node + 60

## Attempts (HackmodelAnimEntryQueueMatrixCopies2, anthropic/claude-opus-5-5:high, after the ModelAnimEntry retype 52539211)
- 72-body grid: p as u8/u32/s32 *, p's first assignment (before stride / after stride / after the bases), while vs for, bases as u32 or u8 * locals with the cast only at the global stores, dst temp or none. All full=10.
- 48-body grid: a named u32 offset local (first/last/none), base+offset vs offset+base, p via node + 1 or sizeof(ModelAnimNodeHeader), p in the for header. Best 10.
- NULL/0 initialisers (Q0199) on p/node/dst/srcBase/dstBase/stride, singly and in pairs; early return on matrixCount == 0; guarded do-while. All 10.

## Evidence
- The 10 differing words are all in the prologue:
  - gGfxBufferIndex `lbu` in v1 (target) vs v0 at 0x630/0x65c/0x678;
  - the D_807F6BE0/E4 address temps in a2/a3 (target) vs v1/a2 at 0x670-0x6a0.
- The loop (0x6bc-0x6ec) matches in every variant. The dead `!p` test's extra block (Q0523) gives an early short range v0, which pushes gGfxBufferIndex to v1.

## Untried ideas
- A natural statement that adds one prologue basic block without a dead test. None found: guards, early returns and do-while guards all compile to the same blocks as the plain loop.

## Attempts (HackmodelAnimEntryQueueMatrixCopies3, anthropic/claude-opus-5-5:high, base 43305fcf)
- uopt -l 6 (FAKE vs plain): the v0 holder is candidate 8, the CSE expression `node + 60` (uadd{node}{60}).
  The dead `!p` test gives it a second use, so it is coloured reg 1 (v0) ahead of candidate 19 (the gGfxBufferIndex lbu, reg 2 = v1).
  Its own code vanishes: p is still emitted as `addiu s0,s2,0x3c` at 0x6bc.
  Without the test, candidate 8 has no savings: 19 takes v0 and the address temps take v1/a2.
- Indexed walk `(u8 *)(node + 1) + i * stride` (for/while, p local or inline): full=39; `p = node + 1 + i * stride` at the loop bottom: 57.
- Byte offset local `off += stride` read through `(u8 *)(node + 1) + off`: 25.
- Real guards `if (p != NULL)`, `if (node != NULL)`, `p != NULL &&` in the loop condition: 35-43 (they emit a branch).
- p re-initialised in the for header after a prologue init: 17 (a redundant store, a steer anyway).
- `node->times + 0x3B` start pointer, a `u8 **frames` local, `n = node = entry->unk0` alias, increment order swaps: all 10.
- One `dst = *(u32 *)p` shared by both sums: 19. Operands swapped to `srcBase + *(u32 *)p`: 12.
- `other = gGfxBufferIndex ^ 1` local (u8/s32/u32): objdiff 320-865, against 65 for the plain body.
- A u8 snapshot used only for the `^ 1` index, the global read again for the other: objdiff 10. Only `lui v0` vs `lui v1` at 0x630 is left, since ugen still takes the free v0 for the lui. It is a mixed spelling (a steer).
- Permuter, 900 s, hack-free weights, plain body, base 65 (.scratch/HackmodelAnimEntryQueueMatrixCopies3/perm): both zeros re-insert `if (p) {}` / `if (!p) {}`, the site itself. The hack-free best is 10 (the mixed snapshot above).

## Untried ideas (after U3)
- A natural second use of `node + 60` that vanishes after colouring, other than an empty test (none found). A late-folded comparison is unlikely: `node + 60 == 0` is never folded.

## Attempts (2026-11-17: cleanup CleanmodelAnimEntryQueueMatrixCopies, CleanmodelAnimEntryQueueMatrixCopies, base 62ab4b74)
- FIXED (fdiff 0, uninit 0, FAKE 1 -> 0): `node = entry->unk0; p = (u8 *)(entry->unk0 + 1);` (the field read inline for p instead of through node), no dead test, `while` -> `for`.
- Same score 0 for: p first then node; declaration initialisers `ModelAnimNodeHeader *node = entry->unk0; u8 *p = (u8 *)(entry->unk0 + 1);`; `(u8 *)entry->unk0 + sizeof(ModelAnimNodeHeader)`; stride read inline too (`entry->unk0->keyCount`), node assigned before or after p/stride but before the bases; p after stride. p after the bases: 12; node assigned after the bases: 18 (the D_807F6BE0/E4 stores force a reload of entry->unk0).
- No effect (10): `u8 **frames = group->frames` (a copy of the param, copy-propagated before the candidate table); `p = (u8 *)node; p += sizeof(ModelAnimNodeHeader)` with the `+=` right after, after stride or after the bases (10), at the old test position after `i = 0` (17). Reverse chain `D_807F6BE0 = srcBase = ...`: 35.
- The sibling modelAnimEntryBuildNodeMatrices also matches with `p = (u8 *)(entry->unk0 + 1)` (measured with variants.py try, not applied: not assigned).

## Evidence (CleanmodelAnimEntryQueueMatrixCopies)
- Fixed body, uopt -l5/-l6: uilod{1181} (entry->unk0) is cand 4, 3 occurrences in block 0, adjsave 4.0 > 3.0 of cand 19 (gGfxBufferIndex lbu) -> reg 1 ($v0). uopt output ucode: `v0 := ilod 0(a1); s2 := v0; s0 := v0 + 0x3c; ilod u8 0(v0)`; ugen folds v0 into node's s2 (`lw s2,0(a1)` 0x658, `lbu s4,0(s2)` 0x66c, `addiu s0,s2,60` 0x6bc), so $v0 has no code. Cand 19 -> reg 2 ($v1), D_807F6BE0/E4 address consts (1338/1354, adjsave 1.0) -> regs 5/6 (a2/a3).
- What the dead `!p` supplied (lever b): a second occurrence of uadd(node, 60) (cand 8, adjsave 3.0, live in block 0 only), tying cand 19 at 3.0 and coloured first on bit order (8 < 19); uopt output `v0 := s2 + 0x3c; s0 := v0; tjp lab11` with lab11 next, which ugen deletes, leaving `addiu s0,s2,60`. Not a block count: cand 19 is 3.0 at 8 blocks (hack) and at 6 blocks (plain).
