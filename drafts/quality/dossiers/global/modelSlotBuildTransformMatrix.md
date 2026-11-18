# modelSlotBuildTransformMatrix (global, src/global/70FD0.c)
## Sites
global:8066C610:other:c06b00 other (REMOVED 2026-11-17f): `entry = (ModelSlot *)((u8 *)gModelSlots + slot * sizeof(ModelSlot)); // FAKE` byte-offset view; kept lw gModelSlots in t8 (0x354) and slot*0x90 in t9 (0x358-0x360) for `addu v1,t8,t9` (0x378); `&gModelSlots[slot]` / `gModelSlots + slot` swap t8/t9.
global:8066C610:other:033ca8 (FIXED round 37): the `0.0` (double) z argument of the rotZ guRotateF keeps the float zero out of a $f20 candidate (Q0747); keep it.
## Attempts
2026-11-10..13 rounds 10/11/16/34/35/37 (Rev10F, Rev11D, Rev16G, CleanGlobal70FD0): `&gModelSlots[slot]` and `gModelSlots + slot` (5 lines, score 40, t8/t9 swapped; cand 6 uadd{umpy}{base}); byte offset builds cand 7 uadd{657 uilod gModelSlots, umpy{ucvt slot,144}}; permutes from the &gModelSlots[slot] body (905 s) stayed at 40 -> kept FAKE.
2026-11-17 2026-11-17: cleanup CleanmodelSlotBuildTransformMatrix CleanmodelSlotBuildTransformMatrix anthropic/claude-opus-5-5: no `entry` pointer, typed element reads:
  - all reads inline (`gModelSlots[slot].unk78` test + frames, `gModelSlots[slot].unk24->unk60 + (u8 *)gModelSlots[slot].unk24`) -> full=1 (only `addu t5,v0,t4` @0x3cc vs target `t4,v0`)
  - inline + `(u8 *)gModelSlots[slot].unk24 + gModelSlots[slot].unk24->unk60` -> 0 (operand order flipped vs the base: not kept)
  - inline + `asset = gModelSlots[slot].unk24; boneTable = asset->unk60 + (u8 *)asset;` -> 0; with `(u8 *)asset + asset->unk60` -> 1
  - `ModelData *anim = gModelSlots[slot].unk78` + `asset` local (twin collisionBuildSlotBoxes spelling) -> 0, KEPT, fdiff 0
  - `entry = gModelSlots + slot;` -> 5; `entry = &gModelSlots[slot];` -> 5 (re-measured)
  - without `s32 pad;` -> 7 (frame word still needed; untagged pad)
  - variants.py scan of the final body: no regressions to fix (only neutral swaps/float/pad-width zeros)
## Untried ideas
none open: the site is fixed.
## Evidence
Target (expected/build/src/global/70FD0.o, function at 0x340, frame 0xf0): 0x350/0x354 lui/lw t8 gModelSlots; 0x358 sll t9,a0,3; 0x35c addu t9,t9,a0; 0x360 sll t9,t9,4; 0x378 addu v1,t8,t9; 0x37c lw v0,120(v1) (unk78); 0x3b0 lw v0,36(v1) (unk24); 0x3bc lw t4,96(v0); 0x3cc addu t5,t4,v0; 0x3d0 sw t5,68(sp) (boneTable home); animFrame home 72(sp).
Fixed copy uopt trace (.scratch/CleanmodelSlotBuildTransformMatrix/trace_fixed.list): cand 6 = uixa{657 uilod gModelSlots}{1524 umpy{765 slot},144} (base first, Q0781/Q0816), shared by the .unk78 load (bit 7) and the .unk24 load (bit 21), coloured reg 2 (v1).
Lever (2026-11-17f, 36880 modelSlotBuildTriangleBuffer 0685a368, 70FD0 collisionBuildSlotBoxes 53766941): an element READ `a[i].g` lowers to uixa{base}{umpy} (base numbered first), `&a[i]` to uadd{umpy}{base}.
