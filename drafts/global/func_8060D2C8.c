// func_8060D2C8 (src/global/104F0.c): stage 1: m2c starter; needs global type/prototype reconstruction and first fdiff
? _sprintf(void *, s32);                            /* extern */
? func_8060B84C(?);                                 /* extern */
s32 func_8060B968(void *, s32);                     /* extern */
? func_8060BA14();                                  /* extern */
? memcpy(s32 (*)[], ? *, s32);                      /* extern */
s32 strlen(s32);                                    /* extern */
extern s8 D_80744460;
extern s32 D_807467C0;
extern s8 D_807467C4;
extern s8 D_807467E4;
extern f32 D_807467E8;
extern OSMesgQueue D_807ECCF0;
extern u8 D_807ECD08;
extern s16 D_807ECEA0;
extern ? D_807ECEA8;
extern ? D_807ED6A8;
extern s32 D_807EDEAC;

void func_8060D2C8(s32 arg0) {
    u8 *sp5C;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_t3;
    s32 temp_t5_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_v0;
    u32 var_s2;
    void *temp_t4;
    void *temp_t5;
    void *temp_t8;
    void *temp_t9;

    sp5C = &D_807ECD08;
    if (D_807EDEAC == 2) {
        _sprintf(((s32) (((((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) + 0x207) & ~7) / 8) + &D_807ECEA8, D_807467C0);
        memcpy((s32 (*)[]) &sp860[0], &D_807ECEA8, 0x800);
        memcpy((s32 (*)[]) &sp60[0], &D_807ED6A8, 0x800);
        if (arg0 == 0) {
            func_8060BA14();
            var_s1 = 0;
            var_s0 = 0;
            do {
                temp_t3 = (s32) ((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
                temp_s2 = (((s32) ((var_s0 + 1) * temp_t3) / 4) - 1) & 0xFFFF;
                temp_v0 = func_8060B968(((var_s0 * temp_t3) & 0xFFFF) + &sp860[0], (temp_t3 - 4) & 0xFFFF);
                var_s0 = (var_s1 + 1) & 0xFF;
                var_s1 = var_s0;
                (&sp860[0])[temp_s2] = temp_v0;
            } while (var_s0 < 4);
            var_s1_2 = 0;
            var_v0 = (s32) (((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8;
        } else {
            var_v0 = (s32) (((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8;
            var_s1_2 = (var_v0 / 8) & 0xFFFF;
        }
        (&sp860[0])[(((s32) (var_v0 + 0x40) / 4) - 1) & 0xFFFF] = func_8060B968((var_v0 & 0xFFFF) + &sp860[0], 0x3C);
        temp_s0 = strlen(D_807467C0);
        temp_v1 = 0x800 - ((s32) (((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8);
        bzero((temp_s0 - temp_v1) + &sp860[0] + 0x840, (temp_v1 - strlen(D_807467C0)) - 0x40);
        osWritebackDCacheAll();
        temp_v0_2 = var_s1_2 * 8;
        memcpy(temp_v0_2 + &D_807ED6A8, &sp860[0] + temp_v0_2, 0x800 - (var_s1_2 * 8));
        if (D_807ECD08 != 0) {
            do {
                func_8060B84C(0x3F800000);
            } while (*sp5C != 0);
        }
        if (D_80744460 != 0) {

        } else {
            D_807467C4 = 1;
            var_s2 = var_s1_2 & 0xFFFF;
            if (var_s1_2 < 0x100) {
loop_13:
                D_807467E4 = 0x1E;
                temp_v0_3 = var_s2 * 8;
                temp_t8 = &sp60[0] + temp_v0_3;
                temp_t9 = &sp860[0] + temp_v0_3;
                var_s0_2 = 0;
                D_807467E8 = (f32) var_s2 * 0.00390625f;
                if ((temp_t8->unk0 != temp_t9->unk0) || (temp_v0_4 = var_s2 * 8, (temp_t8->unk4 != temp_t9->unk4)) || (temp_t4 = &sp60[0] + temp_v0_4, temp_t5 = &sp860[0] + temp_v0_4, (temp_t4->unk8 != temp_t5->unk8)) || (temp_t4->unkC != temp_t5->unkC)) {
loop_17:
                    if (D_80744460 != 0) {

                    } else {
                        osEepromWrite(&D_807ECCF0, (var_s2 + var_s0_2) & 0xFF, &sp860[0] + (var_s2 * 8) + (var_s0_2 * 8));
                        func_8060B84C(0x41700000);
                        var_s0_2 += 1;
                        if (var_s0_2 == 2) {
                            goto block_20;
                        }
                        goto loop_17;
                    }
                } else {
block_20:
                    temp_t5_2 = (var_s2 + 2) & 0xFFFF;
                    var_s2 = (u32) temp_t5_2;
                    if (temp_t5_2 < 0x100) {
                        goto loop_13;
                    }
                }
            }
        }
        D_807467C4 = 0;
    }
}
