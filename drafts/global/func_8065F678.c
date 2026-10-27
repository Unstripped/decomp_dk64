// func_8065F678 (src/global/63EC0.c): u8 arg3 parameter, 0x270 frame with pad[2], size variable for multu
typedef struct R4A_Sub678 {
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
} R4A_Sub678;

extern s32 func_8062DBDC(s16, s16, s16, s16, s32, s16, f32, f32, f32, f32, void *);
extern void matrix4Invert(void *, f32 (*)[4]);
extern void func_8065F964(EffectNode *, f32, f32, f32, s32, void *, void *);
extern void func_80660520(Vtx *, EffectNode *);
extern void func_80660830(Vtx *, EffectNode *);
extern void func_80660D38(Vtx *, EffectNode *);
extern f32 D_807F5FAC;
extern u8 *D_807FC924;

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
            if (func_8065FB04(node->target) != 0 && !(node->unk4C & 1)) {
                temp_fs1 = ((R4A_Sub678 *)node->target)->unk10 + ((R4A_Sub678 *)node->target)->unkC;
                temp_fs0 = (f32)((R4A_Sub678 *)node->target)->unk4E + node->unk4;
                if (((R4A_Sub678 *)node->target)->unk67 == 1) {
                    var_s1 = (u8 *)D_807F6C18 + (((R4A_Sub678 *)node->target)->unk50[0] * size) + 0x88;
                } else {
                    var_s1 = sp120;
                    if (var_s5 == 0) {
                        var_s5 = 1;
                        guMtxL2F(spD8, (Mtx *)(D_807FC924 + (arg3 * 0x2F0) + (D_807444FC << 6) + 8));
                        matrix4Invert(sp98, spD8);
                    }
                    func_8065F964(node, arg0, arg1, arg2, arg3, sp98, sp120);
                }
                if (func_8062DBDC(((R4A_Sub678 *)node->target)->unk46, (s16)(temp_fs0 - temp_fs1), ((R4A_Sub678 *)node->target)->unk48, ((R4A_Sub678 *)node->target)->unk4A,
                                  (s32)(temp_fs0 + temp_fs1), ((R4A_Sub678 *)node->target)->unk4C, arg0, arg1, arg2, D_807F5FAC, var_s1) != 0 || node->pad4D[0] != 0) {
                    if ((f64)((R4A_Sub678 *)node->target)->unk24 != 0.0 || (f64)((R4A_Sub678 *)node->target)->unk28 != 0.0) {
                        func_80660D38(node->dl[D_807444FC], node);
                    }
                    if ((f64)((R4A_Sub678 *)node->target)->unkC != 0.0 || (f64)((R4A_Sub678 *)node->target)->unk10 != 0.0) {
                        func_80660520(node->dl[D_807444FC], node);
                    }
                    func_80660830(node->dl[D_807444FC], node);
                    node->unk4C |= 1;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}
