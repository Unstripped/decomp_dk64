// func_806F1C04 (src/global/F56F0.c): stage 2: full m2c reconstruction saved; needs local view types and block/frame matching
? actorGetNodePos(void *, ?, f32 *, f32 *, f32 *);  /* extern */
f32 func_80611BB4(f32, f32);                        /* extern */
? func_806F1A18(f32, f32, void *, f32 *);           /* extern */
f32 func_806F1AE0(void *, void *, ?);               /* extern */
s32 func_806F1B58(void *, ?);                       /* extern */
f32 func_806F1B90(void *, f32);                     /* extern */

void func_806F1C04(void *arg0, s32 arg1, s32 *arg2) {
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    s32 sp90;
    f32 sp80;
    f32 sp7C;
    f32 temp_ft0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fs2;
    f32 var_fs3;
    s32 var_s2;
    s32 var_s4;
    s8 var_fp;
    s8 var_s3;
    u8 temp_v0;
    void *temp_s0;
    void *var_s0;
    void *var_s1;

    temp_s0 = arg0->unk178;
    var_fp = -0x80;
    var_fs2 = 0.0f;
    var_fs3 = 0.0f;
    var_s1 = temp_s0 + 0x1C;
    sp90 = func_806F1B58(temp_s0, 2);
    sp80 = 0.0f;
    sp7C = 0.0f;
    var_s4 = *arg2;
    var_s3 = 0x14;
    actorGetNodePos(arg0, 0xD, &spA4, &spA8, &spAC);
    actorGetNodePos(arg0, 0xE, &spB0, &spB4, &spB8);
    temp_fv0 = func_80611BB4(spAC - spB8, spA4 - spB0);
    if (sp90 == 0) {
        temp_v0 = temp_s0->unk14;
        temp_s0->unk0 = temp_fv0;
        temp_s0->unk4 = spA8;
        if ((temp_v0 != 0) && (arg0->unk60 & 0x100) && (temp_s0->unk18 == 2)) {
            temp_s0->unk14 = (u8) (temp_v0 - 1);
        }
    } else {
        temp_fv0_2 = func_806F1B90(temp_s0, temp_fv0);
        temp_fv1 = temp_s0->unk10;
        temp_s0->unk10 = (f32) ((f64) temp_fv1 + ((f64) (-128.0f - temp_fv1) * 0.3));
        var_fs3 = 0.4f * temp_fv0_2;
        var_fp = (s8) (s32) temp_s0->unk10;
        var_fs2 = func_806F1AE0(arg0, temp_s0, 0x3CA3D70A);
    }
    var_s0 = arg1 + (var_s4 * 8);
    var_s2 = 0;
    do {
        if (sp90 != 0) {
            func_806F1A18(var_fs2, 0.06f, var_s1, &sp80);
            func_806F1A18(var_fs3, 0.06f, var_s1 + 0xC, &sp7C);
        }
        var_s0->unk0 = var_fp;
        var_s0->unk1 = var_s3;
        var_s0->unk4 = 0;
        var_s2 += 1;
        temp_ft0 = var_s1->unk4 + var_s1->unk0;
        var_s1 += 0x18;
        var_s4 += 1;
        var_s0 += 8;
        var_s3 += 1;
        var_s0->unk-6 = (s16) (s32) ((f64) temp_ft0 * 10430.218905280077);
        var_s0->unk-2 = (s16) (s32) ((f64) (var_s1->unk-8 + var_s1->unk-C) * 10430.218905280077);
    } while (var_s2 != 4);
    *arg2 = var_s4;
}
