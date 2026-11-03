// modelSlotResolveAssetTextures (src/global/36880.c): W3CountB 2026-11-02: PARKED stage 4, count-exact 121/121, frame 72, s0/s1 same, full 54 (was 63 at 124 insns). Lever: reuse the DEAD locals sp30 (calls 2) and a widened u32 flags (calls 3,4) as the CSE'd 'p = seg->unkXX' copy for the dlResolveNodeTextures args (new locals grow the frame 80/88); plus 2 dead tests. Remaining diff: target obj in v0 then move s1,v0; flags in a3; unkA0/A4/AC loaded straight into a0.
s32 dlResolveNodeTextures(DisplayListCmd *, DisplayListCmd *, ModelSegmentNode *, u8);

s32 modelSlotResolveAssetTextures(arg0, arg1, arg2)
ModelSlot *arg0;
u8 arg1;
volatile u8 arg2;
{
    ModelSegmentData *seg;
    ModelSlotObjHeader *obj;
    ModelSegmentData *volatile seg2; // FAKE: keeps a memory copy of seg (target reloads it from 0x3C(sp) in the else branch)
    u32 sp30;
    ModelSegmentNode *node;
    u32 flags; // FAKE: u32 so the dead flags can hold a segment pointer
    u8 res;
    s32 sp24;
    s32 sp20;
    if (0) {
        &node; // FAKE: node must be stack resident
    }
    seg = ((ModelSlotSegOwner *)arg0)->unk20;
    obj = (ModelSlotObjHeader *)arg0->unk24;
    seg2 = seg;
    obj->unk8 = gFrameCounter;
    flags = arg0->unk8C;
    if (!(flags & 0x20)) {
        if (!(obj->unk0 & 0x10) || arg2 != 0) {
            arg0->unk8C = flags | 0x20;
            obj->unk3C += 1;
            if (obj->unk1C == 1) {
                node = (ModelSegmentNode *)((ModelSlotSegOwner *)arg0)->unk20->unkB8;
                sp24 = ((seg->unkA8 - seg->unkA0) >> 3) * 8;
                sp30 = (seg->unkB0 - seg->unkA8) >> 3;
                res = dlResolveNodeTextures((DisplayListCmd *)seg->unkA0, (DisplayListCmd *)(seg->unkA0 + sp24), node, arg2);
                sp20 = sp30 * 8;
                if (res && res) {} // FAKE: dead test steers uopt colouring
                sp30 = seg->unkA8; // FAKE: reuses dead sp30 as the CSE'd pointer (steers uopt colouring)
                res |= dlResolveNodeTextures((DisplayListCmd *)sp30, (DisplayListCmd *)(sp30 + sp20), node, arg2);
                if (node != 0) {
                    flags = seg->unkA4; // FAKE: reuses dead flags (u32) as the CSE'd pointer
                    res |= dlResolveNodeTextures((DisplayListCmd *)flags, (DisplayListCmd *)(flags + sp24), node, arg2);
                    flags = seg->unkAC; // FAKE: reuses dead flags (u32) as the CSE'd pointer
                    res |= dlResolveNodeTextures((DisplayListCmd *)flags, (DisplayListCmd *)(flags + sp20), node, arg2);
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
