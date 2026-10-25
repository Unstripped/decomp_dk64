// func_806FA5A4 (src/global/FCCD0.c): stage 3: semantic transition-in draft; branch form and local packing differ
? func_806F9848(s32, u8);                           /* extern */
? func_806F9B64(s32, u8);                           /* extern */
? func_806F9CD0(s32, u8);                           /* extern */
s32 func_806FA504(s32, void *, s32, s32);           /* extern */
extern s32 D_80754280;

s32 func_806FA5A4(s32 arg0, s32 arg1) {
    s32 sp40;
    s16 temp_v0_2;
    s32 temp_t6;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s7;
    u8 temp_a2;
    void *temp_v1;
    void *temp_v1_2;
    void *var_s0;

    temp_t6 = arg0 * 0x30;
    sp40 = temp_t6;
    temp_v1 = D_80754280 + temp_t6;
    temp_a2 = temp_v1->unk7;
    var_s7 = arg1;
    var_s0 = temp_v1->unk28;
    var_s2 = 0;
    var_s3 = 0;
    var_s1 = 0;
    if (temp_a2 != 0) {
        temp_v1->unk7 = (u8) (temp_a2 - 1);
        return arg1;
    }
    if (var_s0 == NULL) {
        switch (arg0) {                             /* irregular */
        case 8:
            func_806F9B64(arg0, temp_a2);
            return var_s7;
        case 10:
        case 12:
            func_806F9CD0(arg0, temp_a2);
            return var_s7;
        default:
            func_806F9848(arg0, temp_a2);
            return var_s7;
        }
    } else {
        if (var_s0 != NULL) {
            do {
                temp_v0 = var_s0->unkC;
                var_s3 += 1;
                if (temp_v0 != 0) {
                    var_s0->unkC = (s32) (temp_v0 - 1);
                } else {
                    temp_v0_2 = var_s0->unk10;
                    if (temp_v0_2 < 0x400) {
                        var_s0->unk10 = (s16) (s32) ((f32) temp_v0_2 + 102.4f);
                    } else {
                        var_s2 += 1;
                    }
                    if (var_s0->unk10 >= 0x401) {
                        var_s0->unk10 = 0x400;
                    }
                    var_s7 = func_806FA504(arg0, var_s0, var_s1, var_s7);
                }
                if (var_s0->unk0 == 1) {
                    var_s1 += 1;
                }
                var_s0 = var_s0->unk18;
            } while (var_s0 != NULL);
        }
        if (var_s2 == var_s3) {
            temp_v1_2 = D_80754280 + sp40;
            if ((sp40 == 0x180) || (sp40 == 0x1B0)) {
                temp_v1_2->unk7 = 0x5A;
            } else {
                temp_v1_2->unk7 = 0x1E;
            }
            (D_80754280 + sp40)->unk20 = 2;
        }
        return var_s7;
    }
}
