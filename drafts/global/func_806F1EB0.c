// func_806F1EB0 (src/global/F56F0.c): stage 2: full m2c reconstruction saved; needs local view types and block/frame matching
? actorGetNodePos(void *, ?, f32 *, ? *, f32 *);    /* extern */
f32 func_80611BB4(f32, f32);                        /* extern */
? func_806F1A18(f32, f32, f32 *, f32 *);            /* extern */
f32 func_806F1AE0(void *, f32 *, ?);                /* extern */
s32 func_806F1B58(f32 *, ?);                        /* extern */
f32 func_806F1B90(f32, f32 *, f32);                 /* extern */
extern ? D_80752CBF;

void func_806F1EB0(void *arg0, s32 arg1, s32 *arg2) {
    f32 spE0;
    s32 spCC;
    f32 spC8;
    f32 spC4;
    ? spBC;
    f32 spB8;
    ? spB4;
    f32 spB0;
    f32 spAC;
    ? spA8;
    f32 spA4;
    f32 *sp94;
    s32 sp90;
    f32 *temp_s0;
    f32 *var_s0;
    f32 *var_v0;
    f32 *var_v1;
    f32 temp_fa0;
    f32 temp_ft2;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 var_fs2;
    f32 var_fs2_2;
    f32 var_fs3;
    f32 var_fs5;
    f32 var_fv0;
    f32 var_fv1;
    s16 temp_v0_2;
    s32 temp_t2;
    s32 var_s2;
    s32 var_s7;
    s8 var_fp;
    s8 var_s3;
    u8 temp_v0;
    void *var_s1;

    temp_s0 = arg0->unk178;
    var_s7 = *arg2;
    var_fs5 = 0.0f;
    var_s3 = 0x16;
    sp94 = temp_s0;
    sp90 = func_806F1B58(temp_s0, 5);
    var_fp = -0x80;
    actorGetNodePos(arg0, 0xD, &spA4, &spA8, &spAC);
    actorGetNodePos(arg0, 0xE, &spB0, &spB4, &spB8);
    temp_fv0 = func_80611BB4(spAC - spB8, spA4 - spB0);
    var_v0 = &spA4;
    var_v1 = temp_s0;
    if (sp90 == 0) {
        do {
            *var_v1 = temp_fv0;
            temp_ft4 = var_v0->unk4;
            var_v0 += 0xC;
            var_v1 += 0x13C;
            var_v1->unk-138 = temp_ft4;
        } while (var_v0 != &spBC);
        temp_v0 = temp_s0->unk14;
        if ((temp_v0 != 0) && (arg0->unk60 & 0x100) && (temp_s0->unk18 == 5)) {
            temp_s0->unk14 = (u8) (temp_v0 - 1);
        }
    } else {
        temp_v0_2 = (*arg0->unk4)->unk10;
        if (temp_v0_2 >= 0) {
            var_fv1 = (f32) *(&D_80752CBF + temp_v0_2);
        } else {
            var_fv1 = -128.0f;
        }
        temp_fv0_2 = temp_s0->unk10;
        temp_s0->unk10 = (f32) ((f64) temp_fv0_2 + ((f64) (var_fv1 - temp_fv0_2) * 0.3));
        var_fp = (s8) (s32) temp_s0->unk10;
        var_fs5 = func_806F1B90(temp_fv0, temp_s0, temp_fv0);
        spE0 = func_806F1AE0(arg0, temp_s0, 0x3CA3D70A);
    }
    var_s1 = arg1 + (var_s7 * 8);
    spCC = 0;
    do {
        var_fs3 = 0.0f;
        var_fs2 = 0.0f;
        spC8 = 0.0f;
        spC4 = 0.0f;
        var_s0 = sp94 + 0x1C;
        if (sp90 != 0) {
            temp_fv0_3 = (sp + (spCC * 0xC))->unkA8;
            temp_ft3 = sp94->unk8;
            temp_fv1 = temp_fv0_3 - sp94->unk4;
            sp94->unk4 = temp_fv0_3;
            sp94->unk8 = temp_fv1;
            temp_fa0 = temp_fv1 - temp_ft3;
            if (var_fs5 > 0.0f) {
                var_fv0 = var_fs5;
            } else {
                var_fv0 = -var_fs5;
            }
            if (spCC != 0) {
                var_fs2_2 = -spE0;
                var_fs3 = -((var_fv0 * 0.3f) + ((-0.015f * temp_fa0) - (0.0008f * temp_fv1)));
            } else {
                var_fs2_2 = spE0;
                var_fs3 = (var_fv0 * 0.3f) + ((-0.015f * temp_fa0) - (0.0008f * temp_fv1));
            }
            var_fs2 = var_fs2_2 + (0.4f * var_fs5);
        }
        var_s2 = 0;
loop_21:
        if (sp90 != 0) {
            func_806F1A18(var_fs3, 0.06f, var_s0, &spC8);
            func_806F1A18(var_fs2, 0.06f, var_s0 + 0xC, &spC4);
        }
        var_s1->unk0 = var_fp;
        var_s1->unk1 = var_s3;
        var_s1->unk2 = 0;
        temp_ft2 = var_s0->unkC;
        temp_ft3_2 = var_s0->unk10;
        var_s2 += 1;
        var_s0 += 0x18;
        var_s7 += 1;
        var_s1 += 8;
        var_s3 += 1;
        var_s1->unk-4 = (s16) (s32) ((f64) (temp_ft3_2 + temp_ft2) * 10430.218905280077);
        var_s1->unk-2 = (s16) (s32) ((f64) (var_s0->unk-14 + var_s0->unk-18) * 10430.218905280077);
        if (var_s2 != 8) {
            goto loop_21;
        }
        temp_t2 = spCC + 1;
        sp94 += 0x13C;
        spCC = temp_t2;
    } while (temp_t2 != 2);
    *arg2 = var_s7;
}
