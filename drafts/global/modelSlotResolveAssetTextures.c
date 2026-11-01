// modelSlotResolveAssetTextures (src/global/36880.c): stage 4, parked NON_MATCHING: frame 0x48 + s0/s1/ra match; 118 vs 113 insns. Target loads obj into v0 then move s1,v0 after first store; flags in a3 (ours v1); stack slot order permuted
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
    u8 flags;
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
                res |= dlResolveNodeTextures((DisplayListCmd *)seg->unkA8, (DisplayListCmd *)(seg->unkA8 + sp20), node, arg2);
                if (node != 0) {
                    res |= dlResolveNodeTextures((DisplayListCmd *)seg->unkA4, (DisplayListCmd *)(seg->unkA4 + sp24), node, arg2);
                    res |= dlResolveNodeTextures((DisplayListCmd *)seg->unkAC, (DisplayListCmd *)(seg->unkAC + sp20), node, arg2);
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
