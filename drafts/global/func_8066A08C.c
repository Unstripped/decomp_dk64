// func_8066A08C (src/global/699B0.c): starter m2c draft (unattempted)
? func_80666D88(f32, f32, ?, s32, s32);             /* extern */
s32 func_80666FC8(f32, f32, f32, f32, ?);           /* extern */
? func_8066A584(void *, f32);                       /* extern */
? func_8066A64C(s32, void *, void *, f32, f32, f32); /* extern */
s32 func_8066A834(void *, f32, f32);                /* extern */
s32 func_8066A988(void *, f32, f32);                /* extern */
s32 func_8066AC10(void *);                          /* extern */
? func_8066ACA4(s32, void *, ?);                    /* extern */
extern s8 D_807F94AD;
extern u8 D_807F94BC;
extern void *D_807FB930;
extern u16 D_807FBB34;

s32 func_8066A08C(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    void *sp128;
    f64 sp108;
    f32 spAC;
    void *sp98;
    f32 sp8C;
    void **sp88;
    f32 sp84;
    f32 sp80;
    f32 sp78;
    f32 temp_fa1;
    f32 temp_fs1;
    f32 temp_fs2_2;
    f32 temp_ft5;
    f64 temp_fa0;
    f64 temp_fs0;
    f64 temp_fs1_2;
    f64 temp_fs2;
    f64 temp_fs3;
    f64 temp_fs5;
    f64 temp_ft4;
    f64 temp_fv0;
    f64 temp_fv1;
    f64 var_fv0;
    s32 temp_v1;
    s32 var_fp;
    s32 var_s1;
    s32 var_s5;
    u16 temp_a1;
    void *temp_s2;
    void *temp_v0;
    void *var_s0;
    void *var_s6;
    void *var_s7;
    s32 phi_a1;

    temp_a1 = D_807FBB34;
    var_s5 = 0;
    var_fp = 0;
    spAC = 999999.0f;
    phi_a1 = (s32) temp_a1;
    if ((s32) temp_a1 > 0) {
        sp88 = &D_807FB930;
        var_s7 = sp98;
        var_s6 = sp128;
        do {
            temp_s2 = *sp88;
            temp_v1 = temp_s2->unk60;
            if (!(temp_v1 & 0x2000)) {
                temp_v0 = temp_s2->unk140;
                if ((temp_v0 != NULL) && (arg0 != temp_s2) && (temp_v1 & 0x10)) {
                    var_s0 = temp_v0->unk98;
                    var_s1 = 0;
                    if (temp_v0->unk94 > 0) {
                        do {
                            if ((func_8066A834(var_s0, arg1, arg2) != 0) && (func_8066A988(var_s0, arg1, arg2) != 0) && (var_s0->unk56 != 0) && ((temp_fa1 = var_s0->unk24, sp8C = var_s0->unk28, temp_ft5 = var_s0->unk30, sp84 = var_s0->unk34, temp_fa0 = (f64) (temp_fa1 - sp8C), temp_fs1 = var_s0->unk3C, sp80 = var_s0->unk40, temp_ft4 = (f64) (temp_ft5 - sp84), temp_fv0 = (f64) (temp_fs1 - sp80), temp_fs2 = (f64) (temp_fa1 - var_s0->unk2C), temp_fs3 = (f64) (temp_ft5 - var_s0->unk38), sp78 = sp8C, temp_fv1 = (f64) (temp_fs1 - var_s0->unk44), temp_fs5 = (temp_ft4 * temp_fv1) - (temp_fv0 * temp_fs3), temp_fs0 = (temp_fv0 * temp_fs2) - (temp_fa0 * temp_fv1), temp_fs1_2 = (temp_fa0 * temp_fs3) - (temp_ft4 * temp_fs2), var_fv0 = -(((f64) sp80 * temp_fs1_2) + ((temp_fs5 * (f64) sp78) + (temp_fs0 * (f64) sp84))), ((temp_fs0 * 2000.0) > 0.01)) || ((temp_fs0 * 2000.0) < -0.01))) {
                                if (arg0 != 0) {
                                    sp108 = var_fv0;
                                    func_80666D88(arg3, (f32) ((2000.0 * (0.0 - ((((f64) arg1 * temp_fs5) + (temp_fs0 * -1000.0) + (temp_fs1_2 * (f64) arg2) + var_fv0) / (temp_fs0 * 2000.0)))) - 1000.0), 0, arg0, 0);
                                }
                                if (D_807F94BC != 0) {
                                    sp108 = var_fv0;
                                    func_8066A584(var_s0, (f32) ((2000.0 * (0.0 - ((((f64) arg1 * temp_fs5) + (temp_fs0 * -1000.0) + (temp_fs1_2 * (f64) arg2) + var_fv0) / (temp_fs0 * 2000.0)))) - 1000.0));
                                }
                                sp108 = var_fv0;
                                if (func_8066AC10(var_s0) != 0) {
                                    temp_fs2_2 = (f32) ((2000.0 * (0.0 - ((((f64) arg1 * temp_fs5) + (temp_fs0 * -1000.0) + (temp_fs1_2 * (f64) arg2) + var_fv0) / (temp_fs0 * 2000.0)))) - 1000.0);
                                    if (func_80666FC8(spAC, temp_fs2_2, (f32) ((f64) arg3 + 4.0), 0.0f) != 0) {
                                        var_s6 = var_s0;
                                        var_s7 = temp_s2;
                                        var_s5 = 1;
                                        spAC = temp_fs2_2;
                                    }
                                }
                            }
                            var_s1 += 1;
                            var_s0 += 0x58;
                        } while (var_s1 < temp_s2->unk140->unk94);
                        phi_a1 = (s32) D_807FBB34;
                    }
                }
            }
            var_fp += 1;
            sp88 += 8;
        } while (var_fp < phi_a1);
        sp128 = var_s6;
        sp98 = var_s7;
    }
    if ((var_s5 != 0) && (func_80666FC8(*arg4, spAC, (bitwise f32) temp_a1, (f32) ((f64) arg3 + 4.0), 0) != 0)) {
        *arg4 = spAC;
        func_8066ACA4(arg0, sp128, 1);
        if (sp98->unk68 & 8) {
            D_807F94AD = 1;
        }
        if (arg0 != 0) {
            func_8066A64C(arg0, sp98, sp128, arg1, spAC, arg2);
        }
    }
    return var_s5;
}
