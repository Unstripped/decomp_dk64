// func_8065F678 (src/global/63EC0.c): stage 4-5: frame 0x270 exact (s32 size local + pad[2]); ~54 lines: sp120 address hoisted into s3 (mine s3/s4/s5 = sp120/spD8/sp98) so 0x1C8 constant never gets fp and multiply is shift chain instead of multu fp; tried &sp120[0], &sp120, f32 array: no change
typedef struct EffAF678Sub {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x10];
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x1A];
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50[1];
    u8 pad52[0x15];
    u8 unk67;
} EffAF678Sub;

s32 effectCheckTargetActive(EffectSubNode *);
void effectWaterSetMeshColors(Vtx *, EffectNode *);
void func_8065F964(EffectNode *, f32, f32, f32, u8, void *, void *);
void func_80660D38(void *, void *);
void func_80660520(void *, void *);
s32 func_8062DBDC(s16, s16, s16, s16, s32, s16, f32, f32, f32, f32, void *);
s32 matrix4Invert(f32 (*)[4], f32 (*)[4]);
extern f32 D_807F5FAC;
extern void *D_807FC924;

void func_8065F678(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    EffectNode *node;
    u8 *var_s1;
    s32 var_s5;
    f32 temp_fs1;
    f32 temp_fs0;
    s32 size;
    u8 sp120[0x138];
    u32 pad[2];
    f32 spD8[4][4];
    f32 sp98[4][4];

    node = D_807F93C0;
    var_s5 = 0;
    size = sizeof(EffectBufferEntry);

    if (node != NULL) {
        do {
            if (effectCheckTargetActive(node->target) != 0 && !(node->unk4C & 1)) {
                temp_fs1 = ((EffAF678Sub *)node->target)->unk10 + ((EffAF678Sub *)node->target)->unkC;
                temp_fs0 = (f32)((EffAF678Sub *)node->target)->unk4E + node->unk4;
                if (((EffAF678Sub *)node->target)->unk67 == 1) {
                    var_s1 = (u8 *)&D_807F6C18[((EffAF678Sub *)node->target)->unk50[0]] + 0x88;
                } else {
                    var_s1 = sp120;
                    if (var_s5 == 0) {
                        var_s5 = 1;
                        guMtxL2F(spD8, (Mtx *)((u8 *)D_807FC924 + (arg3 * 0x2F0) + (D_807444FC << 6) + 8));
                        matrix4Invert(sp98, spD8);
                    }
                    func_8065F964(node, arg0, arg1, arg2, arg3, sp98, sp120);
                }
                if (func_8062DBDC(((EffAF678Sub *)node->target)->unk46, (s16)(temp_fs0 - temp_fs1), ((EffAF678Sub *)node->target)->unk48, ((EffAF678Sub *)node->target)->unk4A,
                                  (s32)(temp_fs0 + temp_fs1), ((EffAF678Sub *)node->target)->unk4C, arg0, arg1, arg2, D_807F5FAC, var_s1) != 0 || node->pad4D[0] != 0) {
                    if ((f64)((EffAF678Sub *)node->target)->unk24 != 0.0 || (f64)((EffAF678Sub *)node->target)->unk28 != 0.0) {
                        func_80660D38(node->dl[D_807444FC], node);
                    }
                    if ((f64)((EffAF678Sub *)node->target)->unkC != 0.0 || (f64)((EffAF678Sub *)node->target)->unk10 != 0.0) {
                        func_80660520(node->dl[D_807444FC], node);
                    }
                    effectWaterSetMeshColors((Vtx *)node->dl[D_807444FC], node);
                    node->unk4C |= 1;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}
