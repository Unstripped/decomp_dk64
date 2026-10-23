// func_8066C2D0 (src/global/70FD0.c): Unmatched: starter m2c draft (matrix math, translation, rotation)
s32 func_80610FE8(s32, s32);                        /* extern */
? func_8066C7F4(void *, s32, f32 (*)[4]);           /* extern */
s32 func_8066CEE4(void *, s32, f32 (*)[4]);         /* extern */
extern u8 D_807444FC;
extern s32 D_8076A064;
extern s32 D_807F6000;

void func_8066C2D0(s32 arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    void *sp5C;
    s32 sp58;
    void *sp54;
    s32 temp_a2;
    s32 temp_fp;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s2;
    s8 temp_v0_2;
    s8 var_s6;
    void *temp_t0;
    void *var_s0;
    void *var_t0;

    temp_v0 = arg0 * 0x90;
    temp_a2 = (D_807F6000 + temp_v0)->unk78;
    temp_t0 = temp_v0 + D_807F6000;
    var_s6 = -1;
    var_t0 = temp_t0 + 0x28;
    if (temp_a2 != 0) {
        sp58 = *(temp_a2 + (D_807444FC * 4));
    } else {
        sp58 = 0;
    }
    sp54 = arg1->unk60 + arg1;
    var_t0->unkC = (s32) ((f64) ((f32) arg1->unk20 * arg8 * 8.0f) * 1.5);
    temp_t0->unk28 = (s32) (arg2 * 8.0f);
    var_t0->unk4 = (s32) (arg3 * 8.0f);
    var_t0->unk8 = (s32) (arg4 * 8.0f);
    temp_fp = *(arg1->unk4C + arg1);
    if (temp_fp != 0) {
        var_t0->unk15 = (u8) (var_t0->unk15 | 2);
        sp5C = var_t0;
        if (!(var_t0->unk15 & 1)) {
            sp5C = var_t0;
            sp5C->unk18 = func_80610FE8(temp_fp * 0x58, temp_a2);
        }
        var_s0 = arg1->unk4C + arg1 + 4;
        var_s1 = sp5C->unk18;
        guScaleF((f32 (*)[4]) &sp124[0], arg8, arg8, arg8);
        guRotateF((f32 (*)[4]) &spE4[0], arg5, 1.0f, 0.0f, 0.0f);
        guMtxCatF((f32 (*)[4]) &sp124[0], (f32 (*)[4]) &spE4[0], (f32 (*)[4]) &sp124[0]);
        guRotateF((f32 (*)[4]) &spE4[0], arg6, 0.0f, 1.0f, 0.0f);
        guMtxCatF((f32 (*)[4]) &sp124[0], (f32 (*)[4]) &spE4[0], (f32 (*)[4]) &sp124[0]);
        guRotateF((f32 (*)[4]) &spE4[0], arg7, 0.0f, 0.0f, 1.0f);
        guMtxCatF((f32 (*)[4]) &sp124[0], (f32 (*)[4]) &spE4[0], (f32 (*)[4]) &sp124[0]);
        guTranslateF((f32 (*)[4]) &spE4[0], arg2, arg3, arg4);
        guMtxCatF((f32 (*)[4]) &sp124[0], (f32 (*)[4]) &spE4[0], (f32 (*)[4]) &sp124[0]);
        var_s2 = 0;
        if (temp_fp > 0) {
            do {
                temp_v0_2 = var_s0->unk14;
                if (temp_v0_2 == -1) {
                    if (func_8066CEE4(var_s0, var_s1, (f32 (*)[4]) &sp124[0]) != 0) {
                        goto block_14;
                    }
                } else {
                    if (var_s6 != temp_v0_2) {
                        func_8066C7F4((temp_v0_2 << 5) + sp54, sp58, (f32 (*)[4]) &spA4[0]);
                        guMtxCatF((f32 (*)[4]) &spA4[0], (f32 (*)[4]) &sp124[0], (f32 (*)[4]) &sp64[0]);
                        var_s6 = var_s0->unk14;
                    }
                    if (func_8066CEE4(var_s0, var_s1, (f32 (*)[4]) &sp64[0]) != 0) {
block_14:
                        var_s1 += 0x58;
                    }
                }
                var_s2 += 1;
                var_s0 += 0x16;
            } while (var_s2 != temp_fp);
        }
        var_t0 = sp5C;
        var_t0->unk1C = var_s1;
    } else {
        var_t0->unk18 = 0;
        var_t0->unk1C = 0;
    }
    var_t0->unk15 = (u8) (var_t0->unk15 | 1);
    var_t0->unk10 = (s32) D_8076A064;
}
