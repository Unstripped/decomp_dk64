# modelSlotsStepSegmentCommands (global, src/global/36880.c)

## Sites
global:80636C00:other:cf6d7c (removed): byte-offset `slot = (ModelSlot *)((u8 *)gModelSlots + D_80747D74 * 0x90)` kept li t3,0x90 / gModelSlots base in t2.
global:80636C00:other:56a075 (removed): `seg = ((ModelSlot *)((u8 *)gModelSlots + D_80747D74 * 0x90))->unk20` re-derived the slot address at 0x5140-0x5150.

## Attempts
2026-11-09..13 (Clean36880, Rev17M, Rev20A, Rev21B, Rev23A, CleanGlobal36880 permS5/S6 660 s): every attempt kept a ModelSlot * slot local (&gModelSlots[D_80747D74] swaps t2/t3; slot->unk20 drops the 0x5140 recompute). See history.
2026-11-15 HackmodelSlotsStepSegmentCommands anthropic/claude-opus-5-5:high: no slot local; `obj = gModelSlots[D_80747D74].unk24`, `gModelSlots[D_80747D74].unk8C` test and `&= ~0x20`, `seg = gModelSlots[D_80747D74].unk20` -> full=0, fdiff 0 (kept, no pad needed).

## Untried ideas
(none open)

## Evidence
Target 0x50c4-0x50d8 multu v1,t3 / lw t8,0(t2) / addu a0,t8,t9 (slot address in a0, reused for lbu v1,140(a0) at 0x50f0 and sb t9,140(a0) at 0x5118); after the sb/sh stores 0x5140-0x5154 re-read lh t8,0(t1) (D_80747D74) and lw t7,0(t2) (gModelSlots), multu t8,t3, addu t4,t7,t9, lw a3,32(t4): the stores kill the address CSE, i.e. indexed gModelSlots[D_80747D74].field at each use (Q0352).
