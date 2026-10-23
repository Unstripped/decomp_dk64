// func_806672B8 (src/global/699B0.c): starter m2c, large collision sweep loop
s32 func_8065F5F0(void *);                          /* extern */
f32 func_806608FC(void *, s32, s32, s32, s32, s32); /* extern */
s32 func_80666FC8(f32, f32, f32, ?);                /* extern */
f32 func_8066785C(s16 *, f32, f32);                 /* extern */
s32 func_80668C30(f32, f32, s16 *, f32, f32);       /* extern */
extern void *D_807F93C0;
extern s8 D_807F9484;
extern f32 D_807F9488;
extern s8 D_807F94AF;
extern s8 D_807F94B0;

u8 func_806672B8(f32 arg0, f32 arg1, f32 *arg2, void *arg3) {
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    s16 spB0;
    s16 spAE;
    s16 spAC;
    s16 spAA;
    s16 spA8;
    s16 spA6;
    s16 spA4;
    s16 spA2;
    s16 spA0;
    u8 sp9F;
    f32 sp8C;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_ft2_2;
    f32 temp_ft3;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 var_fa0;
    f32 var_fs5;
    f32 var_fv1;
    s16 temp_t0;
    s16 temp_t1;
    s32 temp_a3;
    s32 temp_ft0;
    s32 temp_ft5;
    s32 temp_s0;
    s32 temp_v0;
    u8 temp_v1_3;
    void *temp_v1;
    void *temp_v1_2;
    void *var_s3;

    sp9F = 0;
    var_fs5 = 999999.0f;
    var_s3 = D_807F93C0;
    sp8C = (f32) ((f64) *arg2 + 4.0);
    if (var_s3 != NULL) {
        do {
            temp_v1 = var_s3->unk0;
            if (((f32) temp_v1->unk46 <= arg0) && ((f32) temp_v1->unk48 <= arg1) && (arg0 <= (f32) temp_v1->unk4A) && (arg1 <= (f32) temp_v1->unk4C)) {
                temp_fs0 = arg0 * 6.0f;
                temp_fs1 = arg1 * 6.0f;
                temp_v0 = func_8065F5F0(var_s3);
                temp_v1_2 = var_s3->unk0;
                temp_t1 = var_s3->unk2C;
                temp_s0 = temp_v0 & 0xFF;
                temp_t0 = temp_v1_2->unk46;
                temp_fv0 = (f32) temp_t1;
                temp_a3 = temp_v0 & 0xFF;
                temp_ft0 = (s32) ((arg0 - (f32) temp_t0) / temp_fv0);
                temp_ft5 = (s32) ((arg1 - (f32) temp_v1_2->unk48) / temp_fv0);
                temp_ft1 = (f32) ((temp_t1 * temp_ft0) + temp_t0);
                spD8 = temp_ft1;
                temp_ft3 = (f32) ((var_s3->unk2C * temp_ft5) + var_s3->unk0->unk48);
                spB8 = temp_ft3;
                spC8 = func_806608FC(var_s3, (s32) temp_ft1, (s32) temp_ft3, temp_a3);
                spBC = spB8;
                temp_ft2 = (f32) (((temp_ft0 + 1) * var_s3->unk2C) + var_s3->unk0->unk46);
                spDC = temp_ft2;
                spCC = func_806608FC(var_s3, (s32) temp_ft2, (s32) spB8, temp_s0 & 0xFF);
                spE0 = spD8;
                temp_ft2_2 = (f32) (((temp_ft5 + 1) * var_s3->unk2C) + var_s3->unk0->unk48);
                spC0 = temp_ft2_2;
                spD0 = func_806608FC(var_s3, (s32) spD8, (s32) temp_ft2_2, temp_s0 & 0xFF);
                spE4 = spDC;
                spC4 = spC0;
                temp_fv0_2 = func_806608FC((bitwise void *) spDC, (bitwise s32) spC0, (s32) var_s3, (s32) spDC, (s32) spC0, temp_s0 & 0xFF);
                spD4 = temp_fv0_2;
                spA0 = (s16) (s32) (spD8 * 6.0f);
                spA6 = (s16) (s32) (spC8 * 6.0f);
                spAC = (s16) (s32) (spB8 * 6.0f);
                spA2 = (s16) (s32) (spDC * 6.0f);
                spA8 = (s16) (s32) (spCC * 6.0f);
                spAE = (s16) (s32) (spB8 * 6.0f);
                spA4 = (s16) (s32) (spDC * 6.0f);
                spAA = (s16) (s32) (temp_fv0_2 * 6.0f);
                spB0 = (s16) (s32) (spC0 * 6.0f);
                if (func_80668C30(spDC, spC0, &spA0, temp_fs0, temp_fs1) != 0) {
                    var_fv1 = func_8066785C(&spA0, temp_fs0, temp_fs1) / 6.0f;
                } else {
                    spA2 = (s16) (s32) (spE0 * 6.0f);
                    spA8 = (s16) (s32) (spD0 * 6.0f);
                    spAE = (s16) (s32) (spC0 * 6.0f);
                    var_fv1 = func_8066785C(&spA0, temp_fs0, temp_fs1) / 6.0f;
                }
                temp_v1_3 = var_s3->unk0->unk60;
                if (temp_v1_3 != 0) {
                    if (temp_v1_3 != 1) {
                        if ((temp_v1_3 == 2) || (temp_v1_3 == 3)) {
                            goto block_13;
                        }
                    } else {
                        if (arg3 != NULL) {
                            if (arg3->unk80 < var_fv1) {
                                arg3->unkB0 = -1;
                                arg3->unk6A = (u16) (arg3->unk6A | 4);
                                if (var_s3->unk4A & 1) {
                                    D_807F94B0 = 1;
                                }
                            }
                            arg3->unkAC = var_fv1;
                            arg3->unk6A = (u16) (arg3->unk6A | 2);
                        }
                        D_807F9484 = 1;
                        D_807F9488 = var_fv1;
                    }
                } else {
block_13:
                    sp9F = 1;
                    if ((temp_v1_3 == 2) || (temp_v1_3 == 3)) {
                        temp_fv0_3 = *arg2;
                        if (var_fv1 < temp_fv0_3) {
                            var_fa0 = temp_fv0_3 - var_fv1;
                        } else {
                            var_fa0 = -(temp_fv0_3 - var_fv1);
                        }
                        if (var_fa0 < 6.0f) {
                            switch (temp_v1_3) {    /* irregular */
                            case 2:
                                D_807F94AF = 2;
                                break;
                            case 3:
                                D_807F94AF = 1;
                                break;
                            }
                        }
                    }
                    if (func_80666FC8(var_fs5, var_fv1, sp8C, 0) != 0) {
                        var_fs5 = var_fv1;
                    }
                }
            }
            var_s3 = var_s3->unk50;
        } while (var_s3 != NULL);
    }
    if (sp9F != 0) {
        *arg2 = var_fs5;
    }
    return sp9F;
}
