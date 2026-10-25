// func_806F4778 (src/global/F9450.c): stage 1: m2c reconstruction retained for later type recovery
? assetFreeBuffer(s32, ?, ?);                       /* extern */
? assetSetImmediateFree();                          /* extern */
void *func_80610FE8(s32, s16 *, s16 *);             /* extern */
u16 func_80631D8C(u8);                              /* extern */
s32 func_80631EB8(u16);                             /* extern */
? func_80631F58(s32, s32 **, ? *);                  /* extern */
s32 func_8063254C(s16, s32 *, f32 *, f32 *, f32 *, s16 *, s16 *); /* extern */
s32 func_8066B0F8(?, s32, ?, ?);                    /* extern */
? func_806F833C(?, u8);                             /* extern */
? heapClearBlock(void *);                           /* extern */
? heapFree(void *);                                 /* extern */
? memcpy(void *, void *, ?);                        /* extern */
extern ? D_80753EF0;
extern void *D_80754240;
extern void *D_80754244;
extern ? D_8076A0A8;
extern u16 D_807F9450;
extern u16 D_807F9452;
extern u16 D_807F9454;
extern u16 D_807F9456;
extern s32 D_807FBB64;
extern u8 D_807FC928;
extern s16 D_807FD720;
extern s16 D_807FD722;
extern s16 D_807FD724;
extern s16 D_807FD726;
extern s16 D_807FD728;
extern s32 D_807FD72C;
extern s32 D_807FD730;
extern s8 D_807FD738;
extern ? D_807FD740;
extern ? D_807FD780;
extern s8 D_807FD798;

void func_806F4778(void) {
    s32 spC4;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    s16 spB2;
    void *spAC;
    s32 sp94;
    s32 sp90;
    s32 sp88;
    s32 sp7C;
    s32 *sp78;
    ? sp74;
    s32 sp70;
    s32 *sp6C;
    u16 sp6A;
    s16 sp66;
    ? *var_s7;
    ? *var_v0;
    ? *var_v1;
    s16 temp_lo;
    s16 temp_s1;
    s16 temp_s6;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v1;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_v0_2;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s7_2;
    void *temp_a0;
    void *temp_v0;
    void *temp_v0_3;
    void *temp_v0_6;
    void *var_s0;
    void *var_s3;
    void *var_s5;
    void *var_s5_2;

    var_s5 = NULL;
    spAC = NULL;
    sp70 = 0;
    D_807FD738 = 0;
    if (D_807FBB64 & 0x10000) {
        temp_v0 = func_80610FE8(0x4B0);
        D_80754240 = temp_v0;
        heapClearBlock(temp_v0);
    } else {
        D_80754240 = NULL;
    }
    sp6A = func_80631D8C(D_8076A0A8.unk3);
    temp_v0_2 = func_8066B0F8(9, D_8076A0A8.unk0, 1, 1);
    sp7C = temp_v0_2;
    if (temp_v0_2 != 0) {
        func_80631F58(temp_v0_2, &sp78, &sp74);
        sp6C = sp78 + 4;
        sp70 = *sp78;
    }
    D_807FD726 = 0;
    D_807FD728 = 0;
    D_807FD730 = 0;
    D_807FD72C = 0;
    sp88 = 0;
    if ((s32) D_807FC928 > 0) {
        var_v1 = &D_807FD780;
        var_v0 = &D_807FD740;
        do {
            var_v1 += 4;
            var_v0 += 0x10;
            var_v0->unk-10 = 0.0f;
            var_v0->unk-C = 0.0f;
            var_v0->unk-8 = 0.0f;
            var_v0->unk-4 = 0.0f;
            var_v1->unk-4 = 0;
        } while ((u32) var_v1 < (u32) ((D_807FC928 * 4) + &D_807FD780));
        sp88 = 0;
    }
    D_807FD798 = 0;
    func_806F833C(1, D_807FC928);
    var_s7 = &D_80753EF0;
    do {
        temp_s6 = var_s7->unk0;
        spC4 = 0;
        if (func_8063254C(temp_s6, &spC4, &spBC, &spB8, &spB4, &spB2, &sp66) != 0) {
            do {
                temp_v0_3 = func_80610FE8(0x1C);
                temp_v0_3->unk8 = (s16) (s32) spBC;
                temp_v0_3->unkA = (s16) (s32) spB8;
                temp_v0_3->unkC = (s16) (s32) spB4;
                temp_v0_3->unk0 = spB2;
                temp_v0_3->unk2 = temp_s6;
                temp_v0_3->unkE = 0;
                temp_v0_3->unk10 = 0;
                temp_v0_3->unk12 = 1;
                temp_v0_3->unk13 = 0;
                temp_v0_3->unk4 = (s16) var_s7->unkC;
                temp_v0_3->unk14 = (s8) sp88;
                if (func_80631EB8((u16) var_s7->unk0) != 0) {
                    var_s2 = 0;
                    var_s1 = 0;
                    var_s4 = 0;
                    if (sp70 > 0) {
                        var_s0 = sp6C + (0 * 0x30);
loop_14:
                        if (sp66 == var_s0->unk2A) {
                            var_s2 = 1;
                        } else {
                            var_s1 += 1;
                            var_s0 += 0x30;
                        }
                        if ((var_s2 == 0) && (func_80631EB8(var_s0->unk-8) != 0)) {
                            var_s4 = (var_s4 + 1) & 0xFFFF;
                        }
                        if ((var_s2 == 0) && (var_s1 < sp70)) {
                            goto loop_14;
                        }
                    }
                    if (var_s2 != 0) {
                        temp_v0_3->unk6 = (s16) (sp6A + var_s4);
                    } else {
                        goto block_25;
                    }
                } else {
block_25:
                    temp_v0_3->unk6 = -1;
                }
                temp_v0_3->unk18 = 0;
                if (var_s5 != NULL) {
                    var_s5->unk18 = temp_v0_3;
                } else {
                    spAC = temp_v0_3;
                }
                var_s5 = temp_v0_3;
            } while (func_8063254C(temp_s6, &spC4, &spBC, &spB8, &spB4, &spB2, &sp66) != 0);
        }
        var_s7 += 0x14;
        temp_t8 = sp88 + 1;
        sp88 = temp_t8;
    } while (temp_t8 != 0x2A);
    D_807FD726 = D_807F9450 * D_807F9454;
    D_807FD728 = D_807F9452 * D_807F9456;
    D_807FD722 = ((s16) D_807FD726 / 500) + 1;
    D_807FD724 = ((s16) D_807FD728 / 500) + 1;
    D_807FD720 = D_807FD722 * D_807FD724;
    D_80754244 = func_80610FE8(D_807FD720 * 4, &D_807FD726, &D_807FD728);
    sp94 = 0;
    var_s7_2 = 0;
    if (D_807FD724 > 0) {
        temp_v0_4 = D_807FD722;
        do {
            sp90 = 0;
            if (temp_v0_4 > 0) {
                var_s4_2 = sp94 * 4;
                do {
                    var_s5_2 = NULL;
                    *(D_80754244 + var_s4_2) = 0;
                    var_s3 = spAC;
                    if (var_s3 != NULL) {
                        temp_s1 = sp90 * 0x1F4;
                        do {
                            temp_v0_5 = var_s3->unk8;
                            if ((temp_v0_5 >= temp_s1) && (temp_v0_5 < (s16) (temp_s1 + 0x1F4))) {
                                temp_lo = var_s7_2 * 0x1F4;
                                temp_v1 = var_s3->unkC;
                                if ((temp_v1 >= temp_lo) && (temp_v1 < (s16) (temp_lo + 0x1F4))) {
                                    temp_v0_6 = func_80610FE8(0x1C);
                                    memcpy(temp_v0_6, var_s3, 0x1C);
                                    temp_v0_6->unk18 = 0;
                                    if (var_s5_2 != NULL) {
                                        var_s5_2->unk18 = temp_v0_6;
                                    } else {
                                        *(D_80754244 + var_s4_2) = temp_v0_6;
                                    }
                                    var_s5_2 = temp_v0_6;
                                }
                            }
                            var_s3 = var_s3->unk18;
                        } while (var_s3 != NULL);
                    }
                    temp_t6 = sp90 + 1;
                    sp90 = temp_t6;
                    sp94 += 1;
                    var_s4_2 += 4;
                } while (temp_t6 < D_807FD722);
            }
            var_s7_2 += 1;
        } while (var_s7_2 < D_807FD724);
    }
    if (spAC != NULL) {
        do {
            temp_a0 = spAC;
            spAC = temp_a0->unk18;
            heapFree(temp_a0);
        } while (spAC != NULL);
    }
    if (sp70 != 0) {
        assetSetImmediateFree();
        assetFreeBuffer(sp7C, 0x1C0, 0x14);
    }
}
