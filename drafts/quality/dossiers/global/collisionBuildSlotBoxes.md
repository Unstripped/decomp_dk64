# collisionBuildSlotBoxes (global, src/global/70FD0.c)
## Sites
global:8066C2D0:other:23002c other: removed. Was `off = slot * sizeof(ModelSlot); anim = ((ModelSlot *)((u8 *)gModelSlots + off))->unk78;` (byte-offset view) keeping gModelSlots in v1 and the slot * 0x90 product in v0 (0x4-0x14), so `addu t6,v1,v0` at 0x48 and `addu t0,v0,v1` at 0x50.
global:8066C2D0:noop-arith:483ad9 noop-arith: removed 2026-11-11 (Rev13B: `bone ^ 0` gone by testing entry->bone directly).
## Attempts
2026-11-09 cleanup round 2 Clean70FD0 claude-opus-5-5:low: 483ad9 `bone == -1` plain -> bne operand order; permute best=0 only re-spells the no-op.
2026-11-10/11 rounds 6, 10, 11 (ReReview, Rev10F, Rev11D) claude-opus-5-5: 483ad9 plain/-1 == bone/assignment-in-test score 10 (bne v0,s7 vs s7,v0 at 0x26c); 23002c `gModelSlots[slot].unk78` swaps v0/v1; a dead `off = slot * 0x90` store kept the match (dead-store steer, rejected).
2026-11-11 round 13 Rev13B claude-opus-5-5:low: 483ad9 fixed (entry->bone tested directly, fdiff 0); 23002c permute zero only with the dead off store.
2026-11-11 rounds 16, 17 (Rev16G, Rev17N) claude-opus-5-5:low: 23002c `gModelSlots[slot].unk78` in place, best 60 (gModelSlots/product v0/v1 swap); permuter re-reads/pointer temps only.
2026-11-13/14 CleanGlobal70FD0, PolishGlobal70FD0Names: reviews nohit/fixed (names: CollisionAssetTri.unk14 -> bone).
2026-11-17 cleanup CleancollisionBuildSlotBoxes CleancollisionBuildSlotBoxes claude-opus-5-5: 23002c fixed. `lastBone = -1; buf = &gModelSlots[slot].unk28; anim = gModelSlots[slot].unk78;` (address statement first, the 36880 modelSlotBuildTriangleBuffer lever) with off gone -> 14 (registers and schedule exact; every frame home +4: off's word was the first-declared slot above slotMtx). Pads: `s32 pad` first / after anim / after out -> 0; `s32 pad[2]` -> 29. Declaring `s8 lastBone` first (or after anim / after out) -> 0, kept (no pad needed). buf statement after anim/lastBone orders -> 18. Review: do-while with `if (count > 0)` guard -> `for (i = 0; i < count; i++)`, `animFrame = NULL`, `boneTable + (bone << 5)` (twin spelling), all 0; fdiff 0.
## Untried ideas
none for this function (no hack sites left).
modelSlotBuildTransformMatrix (same file, site global:8066C610:other:c06b00, not this unit): same byte-offset `(ModelSlot *)((u8 *)gModelSlots + slot * sizeof(ModelSlot))` view; try the Q0900/Q0175 first-appearance lever there (statement order / `&gModelSlots[slot]` vs field access first) (this unit).
## Evidence
0x4-0x14: `lui v1,%hi(gModelSlots); lw v1,%lo(gModelSlots)(v1); sll v0,a0,3; addu v0,v0,a0; sll v0,v0,4`: gModelSlots in v1, slot * 0x90 in v0.
0x48 `addu t6,v1,v0; lw a2,120(t6)` = gModelSlots[slot].unk78 (uixa base first); 0x50 `addu t0,v0,v1` + 0x60 `addiu t0,t0,40` = &gModelSlots[slot].unk28 (uadd product first).
Frame 376 (0x0); homes: animFrame sp+88 (0x7c/0x80, read 0x298), boneTable sp+84 (0x94, read 0x294), buf spill sp+92 (0x138, 0x160); slotMtx sp+292 (0x178), tmpMtx sp+228 (0x1a0), boneMtx sp+100 (0x258), boneWorldMtx sp+164 (0x25c).
