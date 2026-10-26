// func_8060CBBC (src/global/104F0.c): stage 1: m2c starter; needs global type/prototype reconstruction and first fdiff
? func_8060B8F8(?);                                 /* extern */
s32 func_8060B968(void *, s32, s32, ? *);           /* extern */
? func_8060C648(?, ?, ?, s32, s32);                 /* extern */
u8 func_8060C6B8(?, ?, ?, s32);                     /* extern */
? func_8060C758(s32, ?);                            /* extern */
? func_8060CB74();                                  /* extern */
? memcpy(? *, ? *, ?);                              /* extern */
extern u8 D_80744530;
extern u8 D_807550C8;
extern s16 D_807ECEA0;
extern ? D_807ECEA8;
extern ? D_807ED6A8;
extern s8 D_807EDEA8;
extern u8 D_807EDEA9;

void func_8060CBBC(void) {
    u8 sp7C;
    u8 sp78;
    u8 *sp54;
    u8 *sp4C;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s6;
    s32 temp_t3;
    s32 temp_t9;
    s32 temp_v1;
    s32 var_fp;
    s32 var_s0_4;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s4_2;
    s32 var_s4_3;
    s8 *var_v1;
    s8 var_s4;
    u8 *var_a0;
    u8 *var_s0_2;
    u8 *var_s0_3;
    u8 *var_v0;
    u8 temp_s2_2;
    u8 temp_t2;
    u8 temp_v0;
    u8 var_s0;
    u8 var_s4_4;
    u8 var_s5;

    var_fp = 0;
    memcpy(&D_807ECEA8, &D_807ED6A8, 0x800);
    var_v1 = &D_807EDEA8;
    var_s4 = 0;
    var_a0 = &sp78;
    do {
        *var_v1 = var_s4;
        var_s4 += 1;
        var_v1 += 1;
        var_a0 += 1;
        var_a0->unk-1 = 0xFF;
    } while (var_s4 < 4);
    sp4C = &sp7C;
    var_s4_2 = 0;
    do {
        temp_s2 = var_s4_2 + 1;
        var_s0 = 1;
        temp_t9 = (s32) ((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
        temp_a2 = ((s32) (temp_s2 * temp_t9) / 4) - 1;
        temp_s1 = *(&D_807ED6A8 + ((temp_a2 & 0xFFFF) * 4));
        temp_s3 = var_s4_2 & 0xFF;
        if (temp_s1 != func_8060B968(((temp_t9 * var_s4_2) & 0xFFFF) + &D_807ED6A8, (temp_t9 - 4) & 0xFFFF, temp_a2, &D_807ED6A8)) {
            var_s0 = 0;
            func_8060C758(temp_s3 & 0xFF, 0);
            func_8060C648(0xF, 0, 0, temp_s3 & 0xFF, 0xFF);
        }
        *sp4C = var_s0;
        sp4C += 1;
        var_s4_2 = temp_s2;
        var_fp = (var_fp | (var_s0 == 0)) & 0xFF;
    } while (temp_s2 < 4);
    var_v0 = &sp7C;
    var_s4_3 = 0;
    do {
        sp4C = var_v0;
        if (*var_v0 != 0) {
            temp_s3_2 = var_s4_3 & 0xFF;
            sp4C = var_v0;
            if (func_8060C6B8(0xD, 0, 0, temp_s3_2 & 0xFF) != 0) {
                sp54 = &(&sp78)[var_s4_3];
                var_s1 = 0;
                temp_v0 = func_8060C6B8(0xF, 0, 0, temp_s3_2 & 0xFF);
                temp_v1 = temp_v0 & 0xFF;
                temp_s6 = temp_v0 & 0xFF;
                var_s5 = temp_v0 & 0xFF;
                if (temp_v1 == temp_v1) {
loop_10:
                    if ((var_s1 != var_s4_3) && ((&sp7C)[var_s1] != 0)) {
                        temp_s0 = var_s1 & 0xFF;
                        if ((func_8060C6B8(0xD, 0, 0, temp_s0 & 0xFF) != 0) && (func_8060C6B8(0xF, 0, 0, temp_s0 & 0xFF) == temp_s6)) {
                            temp_s2_2 = func_8060C6B8(0x10, 0, 0, temp_s3_2 & 0xFF);
                            if (func_8060C6B8(0x10, 0, 0, temp_s0 & 0xFF) >= temp_s2_2) {
                                var_s5 = 0xFF;
                                func_8060C758(temp_s3_2 & 0xFF, 0);
                                func_8060C648(0xF, 0, 0, temp_s3_2 & 0xFF, 0xFF);
                                var_fp = (var_fp | 1) & 0xFF;
                            }
                        }
                    }
                    var_s1 += 1;
                    if ((var_s1 < 4) && (temp_s6 == var_s5)) {
                        goto loop_10;
                    }
                }
                *sp54 = var_s5;
            }
        }
        var_s4_3 += 1;
        var_v0 = sp4C + 1;
    } while (var_s4_3 < 4);
    var_s4_4 = 0;
    do {
        var_s2 = 0;
        var_s0_2 = &sp78;
loop_22:
        temp_t2 = *var_s0_2;
        var_s0_2 += 1;
        if (var_s4_4 == temp_t2) {
            var_s2 = 1;
        }
        if (((u32) var_s0_2 < (u32) &sp7C) && (var_s2 == 0)) {
            goto loop_22;
        }
        if (var_s2 == 0) {
            var_s1_2 = 0;
            if (var_s2 == 0) {
                var_s0_3 = &sp78;
loop_29:
                if (*var_s0_3 == 0xFF) {
                    *var_s0_3 = var_s4_4;
                    var_s2 = 1;
                    func_8060C648(0xF, 0, 0, var_s1_2 & 0xFF, (s32) var_s4_4);
                }
                var_s1_2 += 1;
                var_s0_3 += 1;
                if ((var_s1_2 < 4) && (var_s2 == 0)) {
                    goto loop_29;
                }
            }
        }
        var_s4_4 += 1;
    } while ((s32) var_s4_4 < 4);
    D_807EDEA9 = sp79;
    D_807EDEA9 = sp7A;
    D_807EDEA9 = sp7B;
    D_807EDEA9 = sp78;
    var_s0_4 = 1;
    temp_t3 = (s32) (((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8;
    temp_a2_2 = ((s32) (temp_t3 + 0x40) / 4) - 1;
    temp_s1_2 = *(&D_807ED6A8 + ((temp_a2_2 & 0xFFFF) * 4));
    if (temp_s1_2 != func_8060B968((temp_t3 & 0xFFFF) + &D_807ED6A8, 0x3C, temp_a2_2)) {
        var_s0_4 = 0;
        func_8060CB74();
    }
    D_807550C8 = func_8060C6B8(0x1F, 0, 0, 0);
    D_80744530 = func_8060C6B8(0x20, 0, 0, 0);
    if ((s32) D_807550C8 > 0) {
        D_807550C8 = 0;
        func_8060C648(0x1F, 0, 0, 0, 0 & 0xFF);
    }
    if ((var_fp | (var_s0_4 == 0)) & 0xFF) {
        func_8060B8F8(1);
    }
}
