// modelSlotResolveAssetTextures (src/global/36880.c): Model36 2026-11-03 (revisit 8): stage 4 park, count-exact 121, frame 72, deadsweep full 36 (was 39), shape 10. NEW: statement order p=arg0->unk24; seg=...unk20; seg2=seg; obj=(T*)((u32)p|0); p->unk8=gFrameCounter (p BEFORE seg, store AFTER obj) gives p=v0 (was v1; found by random search over entry-statement order x declaration order x flags-local forms, 3000 evals); dropped dead 'if (0) { &node; }' (no effect). Remaining: flags coloured v1 (target a3) and arg2's first piece coloured a3 ('andi a3,a2,0xff; sb a3,83(sp)') where target keeps arg2 memory-resident (lbu t5,83(sp) at the test, lbu a3,83(sp) at calls) and fills the load-use stall with 'move s1,v0'. uopt -l5: arg2 piece cand 25 has adjsave 0.25 and gets a3 only because a3 is the last free reg (forbidden v0 v1 a0 a1 a2): target flags=a3 means something holds v1 over flags' range (dead-test/ghost-local sweeps incl. 14k ghost vars, 3680 singles on 2 bases, 780 pairs: none produced lbu a3,140 or removed the piece without count loss). Tried and no effect: ANSI vs K&R header (u8/u8), call-arg/test spellings of arg2 (u8)/&0xFF/!=0U, sibling-style head/mid/count vars (worse: 100), natural no-FAKE body (100), &arg2 in if(0).
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
    p = (ModelSlotObjHeader *)arg0->unk24;
    seg = ((ModelSlotSegOwner *)arg0)->unk20;
    seg2 = seg;
    obj = (ModelSlotObjHeader *)((u32)p | 0); // FAKE: blocks copy propagation
    p->unk8 = gFrameCounter;
    if (arg0->unk20 && arg0->unk20) {} // FAKE: dead test steers uopt colouring
    if (!(arg0->unk8C & 0x20)) {
        if (!(obj->unk0 & 0x10) || arg2 != 0) {
            arg0->unk8C |= 0x20;
            obj->unk3C += 1;
            if (obj->unk1C == 1) {
                node = (ModelSegmentNode *)((ModelSlotSegOwner *)arg0)->unk20->unkB8;
                sp24 = ((seg->unkA8 - seg->unkA0) >> 3) * 8;
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
