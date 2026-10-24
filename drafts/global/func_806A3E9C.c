// func_806A3E9C (src/global/A8400.c): stage 1: unedited m2c starter from the base asm (never attempted this round)
s32 func_806A3C6C(s32, s32, s32, s32);              /* extern */
? func_806A3DA0(f32 *, f32 *, f32, ?, void *);      /* extern */
extern u8 D_807444FC;

s32 func_806A3E9C(s32 arg0, void *arg1, s32 arg2) {
    f32 spA4;
    f32 spA0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f64 temp_fs0;
    f64 temp_fv0;
    f64 temp_fv0_4;
    f64 var_ft5;
    f64 var_fv1;
    f64 var_fv1_2;
    s32 temp_s0;
    s32 var_a2;
    s32 var_s3;
    s32 var_s5;
    s32 var_s7;
    u32 temp_v0;

    temp_fv0 = (f64) arg1->unk20;
    var_s7 = arg0;
    if (temp_fv0 < 0.32) {
        var_fv1 = temp_fv0;
    } else {
        var_fv1 = 0.32;
    }
    var_s5 = 1;
    var_s3 = 1;
    temp_v0 = (u32) (var_fv1 * 12.5);
    if ((temp_v0 & 0xFF) > 0) {
        do {
            temp_fv0_2 = arg1->unk24;
            var_ft5 = (f64) var_s5;
            if (var_s5 < 0) {
                var_ft5 += 4294967296.0;
            }
            temp_fs0 = var_ft5 * 0.08;
            spA4 = (f32) (((f64) (arg1->unk2C - temp_fv0_2) * temp_fs0) + (f64) temp_fv0_2);
            temp_fv1 = arg1->unk28;
            spA0 = (f32) (((f64) (arg1->unk30 - temp_fv1) * temp_fs0) + (f64) temp_fv1);
            guTranslateF((f32 (*)[4]) &spE8[0], -48.0f, -32.0f, 0.0f);
            temp_fv0_3 = (f32) (temp_fs0 * 1.899999976158142 * 4.0 * 0.5);
            guScaleF((f32 (*)[4]) &spA8[0], temp_fv0_3, temp_fv0_3, 1.0f);
            guMtxCatF((f32 (*)[4]) &spE8[0], (f32 (*)[4]) &spA8[0], (f32 (*)[4]) &spE8[0]);
            func_806A3DA0(&spA4, &spA0, (f32) temp_fs0, 0x3F800000, arg1);
            guTranslateF((f32 (*)[4]) &spA8[0], spA4 * 4.0f, spA0 * 4.0f, 0.0f);
            guMtxCatF((f32 (*)[4]) &spE8[0], (f32 (*)[4]) &spA8[0], (f32 (*)[4]) &spE8[0]);
            temp_s0 = var_s3 * 2;
            guMtxF2L((f32 (*)[4]) &spE8[0], arg1->unk34 + ((temp_s0 + D_807444FC) << 6));
            temp_fv0_4 = (f64) (var_s3 * 0x12C) * 0.08;
            if (temp_fv0_4 > 150.0) {
                var_fv1_2 = 150.0;
            } else {
                var_fv1_2 = temp_fv0_4;
            }
            if (M2C_ERROR(/* cfc1 */) & 0x78) {
                if (!(M2C_ERROR(/* cfc1 */) & 0x78)) {
                    var_a2 = (s32) (var_fv1_2 - 2147483648.0) | 0x80000000;
                } else {
                    goto block_13;
                }
            } else {
                var_a2 = (s32) var_fv1_2;
                if (var_a2 < 0) {
block_13:
                    var_a2 = -1;
                }
            }
            var_s3 = (var_s5 + 1) & 0xFF;
            var_s5 = var_s3;
            var_s7 = func_806A3C6C(var_s7, arg1->unk34 + ((temp_s0 + D_807444FC) << 6), var_a2 & 0xFF, arg2);
        } while ((temp_v0 & 0xFF) >= var_s3);
    }
    return var_s7;
}
