// modelSlotResolveAssetTextures (src/global/36880.c): stage 6: full=35 text=35 reloc=0 shape=0 (prior draft 39/shape 2); pick-one session 2026-11-06. Levers: drop the if (&arg2) FAKE, add dead if (res) {} (uninitialised read) right after the arg0->unk8C test so res (v1) is live there and flags takes a3; dead if (seg->unkA8) {} at the arm head gives shape 0; sp30 statement before sp24. Remaining: A8/len0 v0<->v1 swap, target sp30-pre=t0 and sp24-pre=t1 webs (ugen ring then starts t2 not t1). Order/holder/type grids and dead-test hill-climbs found nothing below 35 at shape 0.
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
    s32 sp30;
    ModelSegmentNode *node;
    u8 res;
    s32 sp24;
    s32 sp20;
    p = (ModelSlotObjHeader *)arg0->unk24;
    seg = ((ModelSlotSegOwner *)arg0)->unk20;
    seg2 = seg;
    obj = (ModelSlotObjHeader *)p;
    p->unk8 = gFrameCounter;
    if (!(arg0->unk8C & 0x20)) {
    if (res) {} // FAKE: x
        if (!(p->unk0 & 0x10) || arg2 != 0) {
            p = (ModelSlotObjHeader *)seg;
            arg0->unk8C |= 0x20;
            obj->unk3C += 1;
            if (obj->unk1C == 1) {
                if (seg->unkA8) {} // FAKE: sweep
                node = (ModelSegmentNode *)((ModelSlotSegOwner *)arg0)->unk20->unkB8; pad = seg->unkA0; sp30 = (seg->unkB0 - seg->unkA8) >> 3; sp24 = ((u32)(seg->unkA8 - pad) >> 3) * 8; res = dlResolveNodeTextures((DisplayListCmd *)pad, (DisplayListCmd *)(pad + sp24), node, arg2); sp20 = sp30 * 8; if (res && res) {} sp30 = seg->unkA8; res |= dlResolveNodeTextures((DisplayListCmd *)sp30, (DisplayListCmd *)(sp30 + sp20), node, arg2); if (node != 0) { pad = seg->unkA4; // LAYOUT: arm statements on one source line steer as1 scheduling; FAKE: pad/sp30 reuse and dead `res && res` test steer uopt colouring
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
