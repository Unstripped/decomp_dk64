// modelSlotResolveAssetTextures (src/global/36880.c): pick-one attempt 3 (base 5f3a78ec): joining the arm's first 12 statements on ONE source line (as1 .loc scheduling) takes the draft shape4->1 at unchanged full29/text29 (the one remaining shape row is the extra move a0,v1; 122 vs 121 normalized rows, not instructions: the target is 113 instructions). Pointer-first variant (pad = seg->unkA0 before the diff; diff = (seg->unkA8 - pad) >> 3) matches the row count (121) with A0 in a0 and no move, but full40 shape2: left are flags v1 vs a3, A8/diff v0/v1 swap, ring t1/t2 at lbu 28(s1), second-call addu operand order. uopt -l5 observations (reg ids 1=v0 2=v1 3=a0 4=a1 5=a2 6=a3): flags forbids only {v0 (p), s0} so it takes v1. HYPOTHESIS, unverified: the target a3 needs ids 1-5 forbidden at its turn (p v0, a v1 web, arg entry pieces; node0 regsused a0-a2), i.e. flags in an early node, and the &arg2 / arg0->unk20 dead-test FAKEs may push it to node 5; dropping the dead test did not give a3, it shifted the ugen ring (full47). Dead-statement sweep on the pointer-first base (12 symbols, 1824 variants), 8 diff-variable forms, 162 pad/pointer holder forms and a 25-minute permuter run found nothing better.
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
        if (!(p->unk0 & 0x10) || arg2 != 0) {
            p = (ModelSlotObjHeader *)seg;
            arg0->unk8C |= 0x20;
            obj->unk3C += 1;
            if (obj->unk1C == 1) {
                node = (ModelSegmentNode *)((ModelSlotSegOwner *)arg0)->unk20->unkB8; pad = seg->unkA8 - seg->unkA0; sp24 = ((u32)pad >> 3) * 8; sp30 = (seg->unkB0 - seg->unkA8) >> 3; pad = seg->unkA0; res = dlResolveNodeTextures((DisplayListCmd *)pad, (DisplayListCmd *)(pad + sp24), node, arg2); sp20 = sp30 * 8; if (res && res) {} sp30 = seg->unkA8; res |= dlResolveNodeTextures((DisplayListCmd *)sp30, (DisplayListCmd *)(sp30 + sp20), node, arg2); if (node != 0) { pad = seg->unkA4;  // LAYOUT: arm statements on one source line steer as1 scheduling; FAKE: pad/sp30 reuse and dead `res && res` test steer uopt colouring
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
