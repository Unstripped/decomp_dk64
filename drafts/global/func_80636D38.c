// func_80636D38 (src/global/36880.c): stage 4, parked NON_MATCHING in src copy: frame 0x48 + s0/s1/ra match; 117 vs 113 insns. Needs FAKE volatile seg2 (copy of arg0->unk20 reloaded from 0x3C(sp) in the else branch, as target) + if(0){&node;}; decl order found by search (seg,obj,seg2,sp30,node,flags,res,sp24,sp20). Remaining diff: target loads obj into v0 then 'move s1,v0' after the first store (obj->unk8) and reads obj->unk0 via v0 (two webs), flags lives in a3 (mine v1), lbu t5,0x53(sp) hoisted above the arg0 reload, stack slot order of node/sp24/sp30/res (target sp20@20 sp24@24 res@2B node@2C sp30@30, mine permuted). Tried hdr temp for obj, order variants, volatile seg2 / address-taken seg2 (0x50 frame)
s32 dlResolveNodeTextures(DisplayListCmd *, DisplayListCmd *, ModelSegmentNode *, u8);

void func_80636D38(arg0, arg1, arg2)
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
    obj->unk8 = D_8076A064;
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
