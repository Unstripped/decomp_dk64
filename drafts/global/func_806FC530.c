// func_806FC530 (src/global/100180.c): Stage 1 m2c starter. Reconstruct local font/glyph structs from target stack slots: frame 0xC8; saved s0-s7/fp; s16 at C2/CE/D6 and byte locals A9-AA-AB/C5-C7. Signature must remain void func_806FC530(s32, s16, s16, s16, s32, u8).
s32 *func_805FD030(void *, s16, s32);               /* extern */
void *func_80610FE8(s32);                           /* extern */
s32 func_806FB914(s16, u8 *);                       /* extern */
s32 func_806FBD5C(s16, u8 *, u8);                   /* extern */
s32 func_806FBEAC(u8 *);                            /* extern */
s32 *func_806FBEF0(s32 *, u8, s16, s8);             /* extern */
? func_80704298(void *, u8, u8, s8);                /* extern */
? heapFreeDeferred(void *);                         /* extern */
extern ? D_20000C0;
extern ? D_2000180;
extern ? D_807549FC;
extern ? D_80754A18;
extern ? D_80754A34;

void *func_806FC530(void *arg0, s16 arg1, s16 arg2, s16 arg3, u8 *arg4, u8 arg5) {
    u8 spC7;
    u8 spC6;
    u8 spC5;
    s16 spC2;
    u8 *spBC;
    void *spAC;
    s8 spAB;
    u8 spAA;
    u8 spA9;
    s8 sp83;
    s16 sp7E;
    s16 sp7A;
    s16 sp78;
    s32 sp5C;
    void *sp58;
    s32 *sp50;
    s16 temp_a0_2;
    s16 temp_a1_2;
    s16 temp_a2;
    s16 temp_s2;
    s16 temp_s3;
    s16 temp_t0;
    s16 temp_t6;
    s16 temp_t8_2;
    s16 temp_t9_2;
    s16 temp_v0_5;
    s16 temp_v1_3;
    s16 var_a1;
    s16 var_s5;
    s16 var_t1;
    s32 *temp_s2_2;
    s32 *temp_s2_3;
    s32 *temp_v0_3;
    s32 *var_s0;
    s32 temp_t0_2;
    s32 temp_t0_3;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t5;
    s32 temp_t5_3;
    s32 temp_t5_4;
    s32 temp_t6_2;
    s32 temp_t7_2;
    s32 temp_t7_3;
    s32 temp_t8_3;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_fp;
    s32 var_t5;
    s32 var_v1;
    s32 var_v1_2;
    s8 temp_a3;
    u8 temp_a0;
    u8 temp_a1;
    u8 temp_t5_2;
    u8 temp_t7;
    u8 temp_t8;
    u8 var_a2;
    void *temp_a0_3;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0_2;
    void *temp_v1;
    void *var_s0_2;
    void *var_s1;
    void *var_t3;

    var_s5 = arg2;
    spC6 = 0;
    spC2 = arg2;
    var_fp = 0;
    spAA = 0;
    spBC = arg4;
    temp_v0 = func_806FBEAC(arg4);
    if (temp_v0 == 0) {
        return arg0;
    }
    temp_v0_2 = func_80610FE8(temp_v0 << 6);
    var_s1 = temp_v0_2;
    heapFreeDeferred(temp_v0_2);
    var_a2 = arg5;
    spAC = var_s1;
    if (var_a2 & 0x80) {
        arg5 = var_a2 & 0xFF7F;
        temp_t5 = func_806FBD5C(arg1, arg4, var_a2) * 2;
        var_a2 = arg5;
        var_s5 -= temp_t5;
        spC2 = var_s5;
        sp5C = (s32) var_a2;
    }
    var_a1 = arg1;
    var_s0_2 = arg0 + 8;
    if (var_a1 & 0x80) {
        var_a1 ^= 0x80;
        spAA = 1;
    }
    arg0->unk4 = 0x2000;
    arg0->unk0 = 0xE3001201;
    if (!(var_a2 & 4)) {
        arg0->unk8 = 0xDA380007;
        var_s0_2->unk4 = &D_20000C0;
        var_s0_2 += 8;
    }
    if (var_a2 & 0x12) {
        temp_s0 = var_s0_2 + 8;
        var_s0_2->unk0 = 0xE7000000;
        var_s0_2->unk4 = 0;
        var_s0_2->unk8 = 0xFC121824;
        temp_s0->unk4 = 0xFF33FFFF;
        var_s0_2 = temp_s0 + 8;
    }
    if (var_a2 & 0x20) {
        temp_s0_2 = var_s0_2 + 8;
        var_s0_2->unk0 = 0xE7000000;
        var_s0_2->unk4 = 0;
        var_s0_2->unk8 = 0xFC121803;
        temp_s0_2->unk4 = 0xFF0FFFFF;
        var_s0_2 = temp_s0_2 + 8;
    }
    if (var_a2 & 1) {
        var_s0_2->unk0 = 0xDA380003;
        var_s0_2->unk4 = &D_2000180;
        var_s0_2 += 8;
    }
    arg1 = var_a1;
    sp5C = (s32) var_a2;
    temp_v0_3 = func_805FD030(var_s0_2, var_a1, (s32) var_a2);
    var_t3 = (arg1 * 6) + &D_80754A34;
    spC7 = 1;
    var_s0 = temp_v0_3;
    if ((var_t3->unk1 + 1) >= 2) {
        do {
            var_s0->unk0 = 0xE7000000;
            var_s0->unk4 = 0;
            spA9 = 0;
            var_s0 += 8;
            temp_t8 = *arg4;
            arg4 += 1;
            spC5 = temp_t8;
            if (temp_t8 & 0xFF) {
                do {
                    if (spC5 != 0x20) {
                        temp_v0_4 = arg1 * 4;
                        sp50 = temp_v0_4 + &D_80754A18;
                        sp58 = var_t3;
                        temp_a3 = func_806FB914(arg1, &spC5) * 4;
                        var_t3 = sp58;
                        temp_v1 = *sp50 + (spC5 * 4);
                        temp_a0 = temp_v1->unk2;
                        temp_a1 = var_t3->unk2;
                        temp_s3 = temp_a0 * 4;
                        temp_t0 = temp_a1 * 4;
                        temp_s2 = temp_v1->unk0;
                        if (spAA != 0) {
                            temp_t9 = (s32) ((var_t3->unk5 * 4) - temp_s3) / 2;
                            if (temp_t9 < 0) {
                                spAB = 0;
                            } else {
                                spAB = (s8) temp_t9;
                            }
                            var_s5 += spAB;
                        }
                        temp_v1_2 = *(temp_v0_4 + &D_807549FC);
                        if (((s32) spC5 >= (s32) (temp_v1_2 + spC7)->unk-1) && ((s32) spC5 < (s32) *(temp_v1_2 + spC7))) {
                            if (spA9 == 0) {
                                spA9 = 1;
                                sp83 = temp_a3;
                                sp7E = temp_t0;
                                sp7A = (s16) temp_a0;
                                sp78 = (s16) temp_a1;
                                var_s0 = func_806FBEF0(var_s0, (u8) arg1, (s16) spC7, temp_a3);
                            }
                            var_s1->unk0 = var_s5;
                            temp_v1_3 = temp_a3 + arg3;
                            temp_v0_5 = (temp_v1_3 + temp_t0) - 1;
                            var_s1->unk2 = temp_v0_5;
                            var_s1->unk12 = temp_v0_5;
                            temp_a0_2 = temp_s2 << 6;
                            temp_a1_2 = (s16) temp_a1 << 6;
                            temp_a2 = (var_s5 + temp_s3) - 1;
                            temp_t8_2 = (temp_s2 + (s16) temp_a0) << 6;
                            var_s1->unk4 = -5;
                            var_s1->unkA = temp_a1_2;
                            var_s1->unk8 = temp_a0_2;
                            var_s1->unk10 = temp_a2;
                            var_s1->unk14 = -5;
                            var_s1->unk18 = temp_t8_2;
                            var_s1->unk1A = temp_a1_2;
                            var_s1->unk20 = temp_a2;
                            var_s1->unk22 = temp_v1_3;
                            var_s1->unk24 = -5;
                            var_s1->unk28 = temp_t8_2;
                            var_s1->unk2A = 0;
                            var_s1->unk32 = temp_v1_3;
                            var_s1->unk30 = var_s5;
                            var_s1->unk34 = -5;
                            var_s1->unk38 = temp_a0_2;
                            var_s1->unk3A = 0;
                            var_s1 += 0x40;
                            if (sp5C & 0x32) {
                                sp58 = var_t3;
                                func_80704298(var_s1 - 0x40, spC6, arg5, temp_a3);
                            }
                            var_fp += 4;
                            temp_s2_2 = var_s0;
                            if (var_fp >= 0x20) {
                                temp_s2_2->unk0 = 0x01020040;
                                sp58 = var_t3;
                                var_s0 += 8;
                                temp_s2_2->unk4 = osVirtualToPhysical(spAC);
                                temp_t7_2 = var_fp / 4;
                                if (temp_t7_2 > 0) {
                                    var_a0 = (temp_t7_2 - 1) * 8;
                                    var_a1_2 = var_a0 + 2;
                                    var_a2_2 = var_a0 + 4;
                                    var_v1 = var_a0 + 6;
                                    do {
                                        temp_t8_3 = (var_a0 & 0xFF) << 0x10;
                                        temp_t0_2 = var_a2_2 & 0xFF;
                                        temp_t7_3 = temp_t8_3 | (temp_t0_2 << 8) | (var_v1 & 0xFF);
                                        temp_t1 = var_v1 < 0xE;
                                        var_v1 -= 8;
                                        var_s0->unk4 = temp_t7_3;
                                        var_s0->unk0 = temp_t8_3 | ((var_a1_2 & 0xFF) << 8) | temp_t0_2 | 0x07000000;
                                        var_s0 += 8;
                                        var_a2_2 -= 8;
                                        var_a1_2 -= 8;
                                        var_a0 -= 8;
                                    } while (temp_t1 == 0);
                                }
                                var_fp = 0;
                                spAC = var_s1;
                            }
                        }
                        if (spAA != 0) {
                            temp_t9_2 = var_t3->unk5 * 4;
                            if (temp_s3 < temp_t9_2) {
                                var_t1 = temp_s3;
                            } else {
                                var_t1 = temp_t9_2;
                            }
                            temp_t6 = var_s5 + var_t1;
                            var_s5 = temp_t6;
                            if (temp_s3 < temp_t9_2) {
                                var_t5 = (((temp_t6 + temp_t9_2) - spAB) - temp_s3) << 0x10;
                                goto block_44;
                            }
                        } else {
                            var_s5 += ((*sp50 + (spC5 * 4))->unk2 + var_t3->unk4) * 4;
                        }
                    } else if (spAA != 0) {
                        var_s5 += var_t3->unk5 * 4;
                    } else {
                        var_t5 = (var_s5 + (var_t3->unk3 * 4)) << 0x10;
block_44:
                        var_s5 = (s16) (var_t5 >> 0x10);
                    }
                    spC6 += 1;
                    temp_t5_2 = *arg4;
                    arg4 += 1;
                    spC5 = temp_t5_2;
                } while (temp_t5_2 & 0xFF);
                spC6 = 0;
            }
            var_s5 = spC2;
            if (var_fp != 0) {
                temp_s2_3 = var_s0;
                temp_s2_3->unk0 = ((var_fp & 0xFF) << 0xC) | 0x01000000 | ((var_fp & 0x7F) * 2);
                temp_a0_3 = spAC;
                spAC = var_s1;
                sp58 = var_t3;
                var_s0 += 8;
                temp_s2_3->unk4 = osVirtualToPhysical(temp_a0_3);
                temp_t5_3 = var_fp / 4;
                if (temp_t5_3 > 0) {
                    var_a0_2 = (temp_t5_3 - 1) * 8;
                    var_a1_3 = var_a0_2 + 2;
                    var_a2_3 = var_a0_2 + 4;
                    var_v1_2 = var_a0_2 + 6;
                    do {
                        temp_t6_2 = (var_a0_2 & 0xFF) << 0x10;
                        temp_t0_3 = var_a2_3 & 0xFF;
                        temp_t5_4 = temp_t6_2 | (temp_t0_3 << 8) | (var_v1_2 & 0xFF);
                        temp_t1_2 = var_v1_2 < 0xE;
                        var_v1_2 -= 8;
                        var_s0->unk4 = temp_t5_4;
                        var_s0->unk0 = temp_t6_2 | ((var_a1_3 & 0xFF) << 8) | temp_t0_3 | 0x07000000;
                        var_s0 += 8;
                        var_a2_3 -= 8;
                        var_a1_3 -= 8;
                        var_a0_2 -= 8;
                    } while (temp_t1_2 == 0);
                }
                var_fp = 0;
            }
            temp_t7 = spC7 + 1;
            arg4 = spBC;
            spC7 = temp_t7;
        } while ((temp_t7 & 0xFF) < (var_t3->unk1 + 1));
    }
    var_s0->unk0 = 0xE7000000;
    var_s0->unk4 = 0;
    return var_s0 + 8;
}
