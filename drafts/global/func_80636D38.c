// func_80636D38 (src/global/36880.c): stage 4: frame 0x48 matches target; callee-saved s0/s1/ra match; entry home stores sw a0-a2 match; arg2 lbu 0x53(sp) matches; unified res eliminates extra var_v1 stack slot; remaining: stack offset ordering of spilled temps sp20/sp24/res/node/sp30
typedef struct ModelSlotObjHeader {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 pad1D[0x1F];
    /* 0x3C */ s16 unk3C;
} ModelSlotObjHeader;

s32 dlResolveNodeTextures();
void modelSlotLoadAssetTextures();
void modelSlotClearAssetTextures();

void func_80636D38(arg0, arg1, arg2)
ModelSlot *arg0;
u8 arg1;
volatile u8 arg2;
{
    ModelSegmentData *seg;
    ModelSlotObjHeader *obj;
    ModelSegmentNode *node;
    u8 flags;
    u32 sp30;
    s32 sp24;
    s32 sp20;
    u8 res;

    if (0) {
        &node;
    }
    seg = arg0->unk20;
    obj = arg0->unk24;
    obj->unk8 = D_8076A064;
    flags = arg0->unk8C;
    if (!(flags & 0x20)) {
        if (!(obj->unk0 & 0x10) || arg2 != 0) {
            arg0->unk8C = flags | 0x20;
            obj->unk3C += 1;
            if (obj->unk1C == 1) {
                node = arg0->unk20->unkB8;
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
                if (((ModelType2Obj *)seg)->unk50 != 0 || arg1 != 0) {
                    modelSlotLoadAssetTextures(obj, seg);
                } else {
                    modelSlotClearAssetTextures(obj, seg);
                }
            }
        }
    }
}
