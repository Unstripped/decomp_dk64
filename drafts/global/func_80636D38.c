// func_80636D38 (src/global/36880.c): stage 4 (K&R, needs prototype change at ~line 583 to void func_80636D38(); and s32 dlResolveNodeTextures proto above; ModelSlotObjHeader is inside an #ifdef NON_MATCHING block so local R36880fObjHdr typedef is included): compiles with 14 hunks unmasked. Layout: sp2B/var_v1 get separate homes (mine sb 0x2F and 0x23 vs target single 0x2B); &sp2B alias, &arg2 alias, pad/decl-order brute force (pads 0-2, all positions) all leave >=3 slot offsets missing. Other diffs: arg2 promoted (andi a3) vs target lbu 0x53(sp) each use (adding &arg2 alias grows code +4), obj in s1 vs v0 then move, flags v1 vs a3.
typedef struct R36880fObjHdr {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 pad1D[0x1F];
    /* 0x3C */ s16 unk3C;
} R36880fObjHdr;

#define SEG ((ModelSegmentData *)arg0->unk20)
void func_80636D38(arg0, arg1, arg2)
ModelSlot *arg0;
u8 arg1;
u8 arg2;
{
    ModelSegmentData *seg;
    R36880fObjHdr *obj;
    void *sp3C;
    u8 flags;
    u32 sp30;
    ModelSegmentNode *sp2C;
    u8 sp2B;
    s32 sp24;
    s32 sp20;
    u8 var_v1;

    if (0) {
        modelSlotClearAssetTextures((s32)&sp24, 0);
        modelSlotClearAssetTextures((s32)&sp20, 0);
        modelSlotClearAssetTextures((s32)&sp3C, 0);
    }
    seg = arg0->unk20;
    obj = (R36880fObjHdr *)arg0->unk24;
    sp3C = seg;
    obj->unk8 = D_8076A064;
    flags = arg0->unk8C;
    if (!(flags & 0x20) && (!(obj->unk0 & 0x10) || arg2 != 0)) {
        arg0->unk8C = flags | 0x20;
        obj->unk3C += 1;
        if (obj->unk1C == 1) {
            sp2C = (ModelSegmentNode *)((ModelSegmentData *)arg0->unk20)->unkB8;
            sp24 = ((seg->unkA8 - seg->unkA0) >> 3) * 8;
            sp30 = (seg->unkB0 - seg->unkA8) >> 3;
            sp2B = dlResolveNodeTextures((DisplayListCmd *)seg->unkA0, (DisplayListCmd *)(seg->unkA0 + sp24), sp2C, arg2);
            sp20 = sp30 * 8;
            var_v1 = (sp2B | dlResolveNodeTextures((DisplayListCmd *)seg->unkA8, (DisplayListCmd *)(seg->unkA8 + sp20), sp2C, arg2)) & 0xFF;
            if (sp2C != NULL) {
                sp2B = var_v1;
                sp2B |= dlResolveNodeTextures((DisplayListCmd *)seg->unkA4, (DisplayListCmd *)(seg->unkA4 + sp24), sp2C, arg2);
                var_v1 = (sp2B | dlResolveNodeTextures((DisplayListCmd *)seg->unkAC, (DisplayListCmd *)(seg->unkAC + sp20), sp2C, arg2)) & 0xFF;
            }
            if (var_v1 != 0) {
                obj->unk0 &= ~0x10;
            }
        } else {
            if (((ModelType2Obj *)sp3C)->unk50 != 0 || arg1 != 0) {
                modelSlotLoadAssetTextures((u8 *)obj, (ModelSlotAsset *)sp3C);
                return;
            }
            modelSlotClearAssetTextures((s32)obj, sp3C);
        }
    }
}
