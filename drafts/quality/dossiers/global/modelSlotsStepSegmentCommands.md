# modelSlotsStepSegmentCommands (global, src/global/36880.c)

## Sites
global:80636C00:other:cf6d7c (removed): byte-offset `slot = (ModelSlot *)((u8 *)gModelSlots + D_80747D74 * 0x90)` kept li t3,0x90 / gModelSlots base in t2.
global:80636C00:other:56a075 (removed): `seg = ((ModelSlot *)((u8 *)gModelSlots + D_80747D74 * 0x90))->unk20` re-derived the slot address at 0x5140-0x5150.
global:80636C00:other:91d1c8 (removed 2026-11-17): `start = head` redundant copy (pre-existing, tagged 2026-11-15); head held displayListA and then the A count. Replaced by per-role locals with displayListB as a CSE'd load (no mid local): start (bit 50) a0, head (bit 54) v0, displayListB uilod (bit 47) v1, seg (bit 40) a3, tail (bit 44) t0, restore (bit 36) a2.

## Attempts
2026-11-09..13 (Clean36880, Rev17M, Rev20A, Rev21B, Rev23A, CleanGlobal36880 permS5/S6 660 s): every attempt kept a ModelSlot * slot local (&gModelSlots[D_80747D74] swaps t2/t3; slot->unk20 drops the 0x5140 recompute). See history.
2026-11-15 HackmodelSlotsStepSegmentCommands anthropic/claude-opus-5-5:high: no slot local; `obj = gModelSlots[D_80747D74].unk24`, `gModelSlots[D_80747D74].unk8C` test and `&= ~0x20`, `seg = gModelSlots[D_80747D74].unk20` -> full=0, fdiff 0 (kept, no pad needed).
2026-11-15 Polishglobal36880c: start = head copy tagged; natural start/head split shifts every temp by one (diagnose nohit).
2026-11-17 CleanmodelSlotReplaceSegment6Commands anthropic/claude-opus-5-5: the modelSlotReplaceSegment6Commands recipe (no mid local; tail = segmentData - displayListB first; start = displayListA; head = displayListB - start; head >>= 3; tail >>= 3) via variants.py try: decls head,seg,start,tail 0; start,seg,head,tail 0 (applied); s32 pad first 0 (not needed); head,seg,tail,start 2; seg,head,tail,..,start last 8; start = A as the first statement 2 (A/B load order at 0x5158/0x515c). Locals obj -> asset, flag -> restore, count -> tail. fdiff 0, uninit 0.

## Untried ideas
(none open for hack sites; D_80747D74 is only used here but defined in asm data 14C9E0, so a function-local static needs a data carve: rename proposal gModelSlotStepIndex)

## Evidence
Target 0x50c4-0x50d8 multu v1,t3 / lw t8,0(t2) / addu a0,t8,t9 (slot address in a0, reused for lbu v1,140(a0) at 0x50f0 and sb t9,140(a0) at 0x5118); after the sb/sh stores 0x5140-0x5154 re-read lh t8,0(t1) (D_80747D74) and lw t7,0(t2) (gModelSlots), multu t8,t3, addu t4,t7,t9, lw a3,32(t4): the stores kill the address CSE, i.e. indexed gModelSlots[D_80747D74].field at each use (Q0352).
0x5158 lw v1,168(a3) displayListB before 0x515c lw a0,160(a3) displayListA; 0x5168 subu v0,v1,a0 (head's register); 0x5170 subu t0,t5,v1 (tail in t0); 0x517c sw t8,32(sp) tail >> 3 spill; 0x5180 sw a3,40(sp) seg spill; 0x5164 sb a2,31(sp) restore spill.
