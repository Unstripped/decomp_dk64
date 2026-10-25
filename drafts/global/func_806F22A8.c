// func_806F22A8 (src/global/F56F0.c): stage 2: full m2c reconstruction saved; needs local view types and block/frame matching
? actorGetNodePos(void *, ?, ? *, f32 *, ? *);      /* extern */
s32 func_80611A44();                                /* extern */
? func_806F1A18(f32, f32, void *, f32 *);           /* extern */
f32 func_806F1AE0(f32, f32, void *, void *, ?);     /* extern */
s32 func_806F1B58(void *, ?);                       /* extern */
extern ? D_80752D4E;
extern f32 D_80752F4C;

void func_806F22A8(void *arg0, s32 arg1, s32 *arg2) {
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    ? sp90;
    f32 sp8C;
    ? sp88;
    s8 sp87;
    f32 sp7C;
    f32 temp_fa1;
    f32 temp_fs2;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fs3;
    s16 temp_v0_2;
    s32 temp_fp;
    s32 var_s1;
    s32 var_s7;
    s8 var_s3;
    u8 temp_v0;
    void *temp_s0;
    void *var_s0;
    void *var_s2;

    temp_s0 = arg0->unk178;
    var_s7 = *arg2;
    var_s3 = 0x1A;
    var_fs1 = 0.06f;
    var_s2 = temp_s0 + 0x1C;
    spAC = 0.0f;
    spB0 = 0.0f;
    var_fs3 = 0.0f;
    var_fs2 = 0.0f;
    spA8 = 0.0003f;
    spA4 = 1.0f;
    temp_fp = func_806F1B58(temp_s0, 3);
    sp87 = -0x80;
    actorGetNodePos(arg0, 5, &sp88, &sp8C, &sp90);
    if (temp_fp == 0) {
        temp_s0->unk0 = (f32) arg0->unkE6;
        temp_s0->unk4 = sp8C;
        D_80752F4C = 0.0f;
        temp_v0 = temp_s0->unk14;
        if ((temp_v0 != 0) && (arg0->unk60 & 0x100) && (temp_s0->unk18 == 3)) {
            temp_s0->unk14 = (u8) (temp_v0 - 1);
        }
    } else {
        temp_fs2 = sp8C - temp_s0->unk4;
        temp_v0_2 = (*arg0->unk4)->unk10;
        temp_fv1 = (f32) arg0->unkE6;
        temp_fa1 = temp_fs2 - temp_s0->unk8;
        var_fs0 = temp_s0->unk0 - temp_fv1;
        if (temp_v0_2 >= 0) {
            var_fa0 = (f32) *(&D_80752D4E + temp_v0_2);
        } else {
            var_fa0 = -128.0f;
        }
        temp_fv0 = temp_s0->unk10;
        temp_s0->unk0 = temp_fv1;
        temp_s0->unk10 = (f32) ((f64) temp_fv0 + ((f64) (var_fa0 - temp_fv0) * 0.3));
        sp87 = (s8) (s32) temp_s0->unk10;
        if (arg0->unk154 == 0x4F) {
            var_fs1 = 0.01f;
            spA8 = 0.0001f;
            spA4 = 0.4f;
        }
        sp7C = temp_fa1;
        temp_fv0_2 = func_806F1AE0(var_fa0, temp_fa1, arg0, temp_s0, 0x3C343958);
        temp_s0->unk8 = temp_fs2;
        temp_s0->unk4 = sp8C;
        var_fs3 = (-temp_fv0_2 - ((0.005f * temp_fa1) + (0.0008f * temp_fs2))) * spA4;
        if ((32.0f + ((1.0f - spA4) * 8.0f)) < (f32) ((s32) (func_80611A44() >> 0xF) % 40)) {
            D_80752F4C = (f32) (0x14 - ((s32) (func_80611A44() >> 0xF) % 40)) * spA8;
        }
        if (var_fs0 > 2048.0f) {
            var_fs0 = 4096.0f - var_fs0;
        } else if (var_fs0 < -2048.0f) {
            var_fs0 = -(4096.0f + var_fs0);
        }
        var_fs2 = (f32) ((f64) ((1.0f - (arg0->unkB8 / 130.0f)) * D_80752F4C) + (2e-05 * (f64) var_fs0));
    }
    var_s0 = arg1 + (var_s7 * 8);
    var_s1 = 0;
    do {
        if (temp_fp != 0) {
            func_806F1A18(var_fs3, var_fs1, var_s2, &spB0);
            func_806F1A18(var_fs2, var_fs1, var_s2 + 0xC, &spAC);
        }
        var_s0->unk1 = var_s3;
        var_s1 += 1;
        var_s0->unk0 = sp87;
        temp_ft4 = var_s2->unk0;
        temp_ft5 = var_s2->unk4;
        var_s2 += 0x18;
        var_s7 += 1;
        var_s0 += 8;
        var_s3 += 1;
        var_s0->unk-6 = (s16) (s32) ((f64) (temp_ft5 + temp_ft4) * 10430.218905280077);
        var_s0->unk-2 = 0;
        var_s0->unk-4 = (s16) (s32) ((f64) (var_s2->unk-8 + var_s2->unk-C) * 10430.218905280077);
    } while (var_s1 != 0xB);
    *arg2 = var_s7;
}
