// modelSlotResolveAssetTextures (src/global/36880.c): SlotTex stage 4: full 33 shape 5 reloc 0 over 113 instructions (121 normalized rows), frame 72 and s0/s1 preserved; prior park full36 shape10. Coordinated address-taken arg2 + pad length-difference reuse + direct obj=p improves and removes obj|0 fake. Exact residual: initial obj load/store uses s1 rather than v0, flags v0 rather than a3, missing early move s1,v0 balanced by first-call move a0,v1, first two DL-call arithmetic registers/order/ring through third call; remainder exact. uopt5 on baseline and best; as1probe keep/scan1413 mutations (no full improvement), deadsweep301 none; structural/type/signature/reuse/arity grids; anneal9272 variants found33, extra deadtests pruned. Permuter -j2 --seconds600 completed50517 iterations,1206 errors; best474 invalid uninitialized p, seven safe hints failed to improve when reconciled with exact scorer. Three/four-arg unused loader/clear params and incoming a2/a3 forwarding (width/copy barriers) did not improve: can put flags in a3 but adds lbu a2 in type2 tail; no signature changes retained. Resolver callers modelSlotInit and renderModelAnimatedSlot explicitly set a1/a2, neither sets a3. All resolver/loader/clear declarations and C callers are in36880.c; no other file updates. Final copy .scratch/SlotTex/36880.c parked NON_MATCHING: plain fdiff prints OK; --non-matching compiles exit0. C remains unmatched.
s32 dlResolveNodeTextures(DisplayListCmd *, DisplayListCmd *, ModelSegmentNode *, u8);

s32 modelSlotResolveAssetTextures(arg0, arg1, arg2)
ModelSlot *arg0;
u8 arg1;
u8 arg2;
{
    ModelSegmentData *seg;
    ModelSlotObjHeader *obj;
    ModelSegmentData *volatile seg2; // FAKE: keeps a memory copy of seg (target reloads it from 0x3C(sp) in the else branch)
    ModelSlotObjHeader *p;
    s32 pad;
    u32 sp30;
    ModelSegmentNode *node;
    u8 res;
    s32 sp24;
    s32 sp20;
    if (&arg2) {} // FAKE: preserves the argument's memory home
    p = (ModelSlotObjHeader *)arg0->unk24;
    seg = ((ModelSlotSegOwner *)arg0)->unk20;
    seg2 = seg;
    obj = (ModelSlotObjHeader *)p;
    p->unk8 = gFrameCounter;
    if (arg0->unk20 && arg0->unk20) {} // FAKE: dead test steers uopt colouring
    if (!(arg0->unk8C & 0x20)) {
        if (!(obj->unk0 & 0x10) || arg2 != 0) {
            arg0->unk8C |= 0x20;
            obj->unk3C += 1;
            if (obj->unk1C == 1) {
                node = (ModelSegmentNode *)((ModelSlotSegOwner *)arg0)->unk20->unkB8;
                pad = seg->unkA8 - seg->unkA0; // FAKE: reuses pad for the length difference (steers uopt colouring)
                sp24 = ((u32)pad >> 3) * 8;
                sp30 = (seg->unkB0 - seg->unkA8) >> 3;
                pad = seg->unkA0; // FAKE: reuses the pad word as the CSE'd pointer (steers uopt colouring)
                res = dlResolveNodeTextures((DisplayListCmd *)pad, (DisplayListCmd *)(pad + sp24), node, arg2);
                sp20 = sp30 * 8;
                if (res && res) {} // FAKE: dead test steers uopt colouring
                sp30 = seg->unkA8; // FAKE: reuses dead sp30 as the CSE'd pointer (steers uopt colouring)
                res |= dlResolveNodeTextures((DisplayListCmd *)sp30, (DisplayListCmd *)(sp30 + sp20), node, arg2);
                if (node != 0) {
                    pad = seg->unkA4; // FAKE: reuses the pad word as the CSE'd pointer (steers uopt colouring)
                    res |= dlResolveNodeTextures((DisplayListCmd *)pad, (DisplayListCmd *)(pad + sp24), node, arg2);
                    pad = seg->unkAC; // FAKE: reuses the pad word as the CSE'd pointer (steers uopt colouring)
                    res |= dlResolveNodeTextures((DisplayListCmd *)pad, (DisplayListCmd *)(pad + sp20), node, arg2);
                    if (seg->unkA0 == 0) {} // FAKE: dead test steers uopt colouring
                }
                if (res != 0) {
                    obj->unk0 &= ~0x10;
                }
            } else {
                if (((ModelType2Obj *)seg2)->unk50 != 0 || arg1 != 0) {
                    modelSlotLoadAssetTextures((u8 *)obj, (ModelSlotAsset *)seg2);
                } else {
                    modelSlotClearAssetTextures((s32)obj, (u8 *)seg2);
                }
            }
        }
    }
}
