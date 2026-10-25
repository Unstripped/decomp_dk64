// func_806FA7BC (src/global/FCCD0.c): stage 3: semantic position-transition draft; local packing and signed widths differ
? func_806F8CB0(s32);                               /* extern */
? func_806F8D58(?, ?);                              /* extern */
s32 func_806FA504(s32, void *, s32, s32);           /* extern */
s32 func_806FA7A4(s32, u16, u16);                   /* extern */
extern s32 D_80754280;

s32 func_806FA7BC(s32 arg0, s32 arg1) {
    u8 sp4F;
    s32 sp30;
    s32 temp_t6;
    s32 temp_v0;
    s32 temp_v1_3;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a3;
    s32 var_s1;
    s32 var_s3;
    s32 var_v0_2;
    u16 *temp_v1;
    u16 *temp_v1_2;
    u16 var_a1;
    u16 var_a2;
    u8 temp_v1_4;
    void *temp_v0_2;
    void *var_s0;
    void *var_v0;

    temp_t6 = arg0 * 0x30;
    sp30 = temp_t6;
    var_v0 = D_80754280 + temp_t6;
    temp_v1 = var_v0->unk0;
    var_s3 = arg1;
    var_s0 = var_v0->unk28;
    var_s1 = 0;
    if (temp_v1 != NULL) {
        sp4F = *temp_v1 == var_v0->unk4;
    } else {
        sp4F = 1;
    }
    if (var_s0 != NULL) {
        do {
            var_s3 = func_806FA504(arg0, var_s0, var_s1, var_s3);
            if (var_s0->unk0 == 1) {
                var_s1 += 1;
            }
            var_s0 = var_s0->unk18;
        } while (var_s0 != NULL);
        var_v0 = D_80754280 + sp30;
    }
    if (sp4F == 0) {
        temp_v1_2 = var_v0->unk0;
        var_a2 = var_v0->unk4;
        var_a1 = *temp_v1_2;
        if (temp_v1_2 != NULL) {
            temp_v0 = func_806FA7A4(arg0, var_a1, var_a2);
            temp_v1_3 = var_a1 - var_a2;
            var_a3 = temp_v0;
            if (temp_v1_3 > 0) {
                var_a0 = temp_v1_3;
            } else {
                var_a0 = -temp_v1_3;
            }
            var_a0_2 = -1;
            if (var_a0 < temp_v0) {
                var_v0_2 = -temp_v1_3;
                if (temp_v1_3 > 0) {
                    var_v0_2 = temp_v1_3;
                }
                var_a3 = var_v0_2;
            }
            if (temp_v1_3 >= 0) {
                var_a0_2 = 1;
            }
            temp_v0_2 = D_80754280 + sp30;
            temp_v0_2->unk4 = (u16) (temp_v0_2->unk4 + (var_a0_2 * var_a3));
            var_v0 = D_80754280 + sp30;
            var_a2 = var_v0->unk4;
            var_a1 = *var_v0->unk0;
        }
        sp4F = var_a1 == var_a2;
    }
    temp_v1_4 = var_v0->unk7;
    if ((temp_v1_4 == 0) && (sp4F != 0)) {
        var_v0->unk20 = 3;
        func_806F8CB0(arg0);
        if (sp30 == 0x180) {
            func_806F8D58(9, 5);
        }
    } else if ((temp_v1_4 != 0) && (var_v0->unk6 == 0)) {
        var_v0->unk7 = (u8) (temp_v1_4 - 1);
    }
    return var_s3;
}
