// func_807024E0 (src/global/103AB0.c): Stage 2 m2c control-flow draft; compiles only after replacing m2c unknowns. Local cleaned renderer reached 0x150 frame vs target 0x1D8; target needs exact unsigned float conversions, s0-s7/fs0-fs2 allocation, and m2c's per-branch Gfx word order.
s32 func_80610FE8(s32);                             /* extern */
? func_80704130(s32, ?, ?, ?, s32, s32);            /* extern */
? func_80704444(s32, s16, s16, s16, s32, s32);      /* extern */
? heapFreeDeferred(s32);                            /* extern */

void func_807024E0(void **arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, u8 arg13, u8 arg14, u8 arg15, ? (*arg16)(s32, s32, s32)) {
    s32 sp1D0;
    s32 sp1C8;
    s32 sp1C4;
    u32 sp18C;
    u32 sp184;
    u8 sp183;
    s32 spDC;
    s32 spD8;
    s32 spD4;
    u32 spD0;
    u32 spCC;
    u32 spC8;
    u32 spC4;
    u32 spC0;
    s32 spBC;
    u32 spB4;
    s32 spB0;
    u32 spAC;
    s32 spA8;
    u32 sp90;
    u32 sp8C;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    s32 sp68;
    s32 sp64;
    f32 temp_fs0;
    f32 temp_ft1;
    f32 temp_fv0;
    f64 temp_fv0_2;
    s16 temp_s6;
    s16 temp_v1;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_ft1_2;
    s32 temp_ft2;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t2_3;
    s32 temp_t6;
    s32 temp_t7_2;
    s32 temp_t7_3;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t8_4;
    s32 temp_t9;
    s32 temp_t9_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v1_2;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a1;
    s32 var_s2;
    s32 var_s5;
    s32 var_t1;
    s32 var_t5;
    u32 temp_s1;
    u32 temp_s3;
    u32 temp_t7;
    u32 temp_t8;
    u32 temp_v1_3;
    u32 var_ra;
    u32 var_s4;
    u32 var_s5_2;
    u32 var_t0;
    u32 var_v0;
    u8 var_s6;
    void *temp_s0;
    void *temp_s0_10;
    void *temp_s0_11;
    void *temp_s0_12;
    void *temp_s0_13;
    void *temp_s0_14;
    void *temp_s0_15;
    void *temp_s0_16;
    void *temp_s0_17;
    void *temp_s0_18;
    void *temp_s0_19;
    void *temp_s0_20;
    void *temp_s0_21;
    void *temp_s0_22;
    void *temp_s0_23;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s0_7;
    void *temp_s0_8;
    void *temp_s0_9;
    void *var_s0;
    void *var_s0_2;
    void *var_s0_3;

    temp_ft1 = arg9 * 32.0f;
    temp_s0 = *arg0;
    var_s6 = 1;
    if (M2C_ERROR(/* cfc1 */) & 0x78) {
        if (!(M2C_ERROR(/* cfc1 */) & 0x78)) {
            var_s5 = (s32) (temp_ft1 - 2.1474836e9f) | 0x80000000;
        } else {
            goto block_3;
        }
    } else {
        var_s5 = (s32) temp_ft1;
        if (var_s5 < 0) {
block_3:
            var_s5 = -1;
        }
    }
    sp18C = (u32) var_s5;
    temp_s3 = (u32) (arg10 * 32.0f);
    sp184 = temp_s3;
    if (arg3 >= 0x201U) {
        temp_s0->unk4 = -1;
        temp_s0->unk0 = 0xD7000002;
        var_s0 = temp_s0 + 8;
        var_s6 = 0;
    } else {
        temp_s0->unk0 = 0xD7000002;
        temp_s0->unk4 = 0x80008000;
        var_s0 = temp_s0 + 8;
    }
    var_s4 = (u32) (arg7 * 32.0f);
    temp_t8 = arg5 << 5;
    spC0 = temp_t8;
    temp_t7 = arg6 << 5;
    temp_s1 = (u32) (arg8 * 32.0f);
    spC4 = temp_t7;
    temp_v0 = func_80610FE8(((((u32) (var_s5 - var_s4) / temp_t8) + 1) * (((u32) (temp_s3 - temp_s1) / temp_t7) + 1)) << 6);
    var_s2 = temp_v0;
    heapFreeDeferred(temp_v0);
    var_s0->unk0 = 0xE7000000;
    var_s0->unk4 = 0;
    var_s0_2 = var_s0 + 8;
    var_v0 = temp_s1;
    temp_fv0 = (f32) arg13;
    var_a1 = (s32) (temp_fv0 * arg12);
    if (temp_s1 < temp_s3) {
        spDC = (s32) arg13;
        spC8 = temp_s3;
        spCC = (u32) var_s5;
        sp183 = var_s6;
        spD4 = arg13 * arg6;
        spBC = (s32) (temp_fv0 * arg11);
        do {
            var_s5_2 = var_s4;
            sp1C8 = spBC;
            if (var_s4 < spCC) {
                sp1C4 = var_a1;
                sp1D0 = (s32) var_v0;
                temp_v0_2 = (s32) var_v0 >> 5;
                spB0 = temp_v0_2 - 1;
                spD8 = spDC * arg5;
                spAC = temp_v0_2 + arg6;
                temp_fv0_2 = (f64) (f32) var_v0 - 16.0;
                spD0 = var_s4;
                spA8 = (s32) arg14;
                sp90 = (spCC >> 5) - 1;
                temp_v1 = var_a1 + spD4;
                sp8C = (spC8 >> 5) - 1;
                sp80 = (s32) temp_v1;
                sp84 = (s32) temp_v1;
                sp78 = (s32) (s16) (s32) ((f32) temp_fv0_2 + (f32) spC4);
                sp68 = (s32) (s16) var_a1;
                sp64 = (s32) (s16) (s32) (f32) temp_fv0_2;
                do {
                    temp_v0_3 = (s32) var_s5_2 >> 5;
                    temp_v1_2 = temp_v0_3 - 1;
                    if (temp_v1_2 > 0) {
                        var_t1 = temp_v1_2;
                    } else {
                        var_t1 = 0;
                    }
                    temp_v1_3 = temp_v0_3 + arg5;
                    if (temp_v1_3 < sp90) {
                        var_t0 = temp_v1_3;
                    } else {
                        var_t0 = sp90;
                    }
                    if (spB0 > 0) {
                        var_t5 = spB0;
                    } else {
                        var_t5 = 0;
                    }
                    if (spAC < sp8C) {
                        var_ra = spAC;
                    } else {
                        var_ra = sp8C;
                    }
                    if (spA8 == 8) {
                        temp_v0_4 = (arg2 & 7) << 0x15;
                        var_s0_2->unk0 = (s32) (temp_v0_4 | 0xFD000000 | 0x80000 | ((arg3 - 1) & 0xFFF));
                        var_s0_2->unk4 = arg1;
                        temp_s0_2 = var_s0_2 + 8;
                        temp_t2 = temp_v0_4 | 0xF5000000 | 0x80000 | ((((s32) ((var_t0 - var_t1) + 8) >> 3) & 0x1FF) << 9);
                        temp_s0_3 = temp_s0_2 + 8;
                        temp_s0_2->unk4 = 0x07080200;
                        var_s0_2->unk8 = temp_t2;
                        temp_s0_2->unk8 = 0xE6000000;
                        temp_v1_4 = ((var_t1 * 4) & 0xFFF) << 0xC;
                        temp_t9 = (var_t5 * 4) & 0xFFF;
                        temp_s0_3->unk4 = 0;
                        temp_s0_4 = temp_s0_3 + 8;
                        temp_a1 = ((var_t0 * 4) & 0xFFF) << 0xC;
                        temp_s0_3->unk8 = (s32) (temp_v1_4 | 0xF4000000 | temp_t9);
                        temp_t8_2 = (var_ra * 4) & 0xFFF;
                        temp_s0_5 = temp_s0_4 + 8;
                        temp_s0_4->unk4 = (s32) (temp_a1 | 0x07000000 | temp_t8_2);
                        temp_s0_6 = temp_s0_5 + 8;
                        temp_s0_4->unk8 = 0xE7000000;
                        var_s0_3 = temp_s0_6 + 8;
                        temp_s0_5->unk4 = 0;
                        temp_s0_6->unk4 = 0x80200;
                        temp_s0_5->unk8 = temp_t2;
                        var_s0_3->unk4 = (s32) (temp_a1 | temp_t8_2);
                        temp_s0_6->unk8 = (s32) (temp_v1_4 | 0xF2000000 | temp_t9);
                        goto block_32;
                    }
                    if (spA8 == 0x10) {
                        temp_v0_5 = (arg2 & 7) << 0x15;
                        var_s0_2->unk0 = (s32) (temp_v0_5 | 0xFD000000 | 0x100000 | ((arg3 - 1) & 0xFFF));
                        var_s0_2->unk4 = arg1;
                        temp_s0_7 = var_s0_2 + 8;
                        temp_t2_2 = temp_v0_5 | 0xF5000000 | 0x100000 | ((((s32) (((var_t0 - var_t1) * 2) + 9) >> 3) & 0x1FF) << 9);
                        temp_s0_8 = temp_s0_7 + 8;
                        temp_s0_7->unk4 = 0x07080200;
                        var_s0_2->unk8 = temp_t2_2;
                        temp_s0_7->unk8 = 0xE6000000;
                        temp_v1_5 = ((var_t1 * 4) & 0xFFF) << 0xC;
                        temp_t6 = (var_t5 * 4) & 0xFFF;
                        temp_s0_8->unk4 = 0;
                        temp_s0_9 = temp_s0_8 + 8;
                        temp_a1_2 = ((var_t0 * 4) & 0xFFF) << 0xC;
                        temp_s0_8->unk8 = (s32) (temp_v1_5 | 0xF4000000 | temp_t6);
                        temp_t7_2 = (var_ra * 4) & 0xFFF;
                        temp_s0_10 = temp_s0_9 + 8;
                        temp_s0_9->unk4 = (s32) (temp_a1_2 | 0x07000000 | temp_t7_2);
                        temp_s0_11 = temp_s0_10 + 8;
                        temp_s0_9->unk8 = 0xE7000000;
                        var_s0_3 = temp_s0_11 + 8;
                        temp_s0_10->unk4 = 0;
                        temp_s0_11->unk4 = 0x80200;
                        temp_s0_10->unk8 = temp_t2_2;
                        var_s0_3->unk4 = (s32) (temp_a1_2 | temp_t7_2);
                        temp_s0_11->unk8 = (s32) (temp_v1_5 | 0xF2000000 | temp_t6);
                        goto block_32;
                    }
                    if (spA8 == 0x20) {
                        temp_v0_6 = (arg2 & 7) << 0x15;
                        var_s0_2->unk0 = (s32) (temp_v0_6 | 0xFD000000 | 0x180000 | ((arg3 - 1) & 0xFFF));
                        var_s0_2->unk4 = arg1;
                        temp_s0_12 = var_s0_2 + 8;
                        temp_t2_3 = temp_v0_6 | 0xF5000000 | 0x180000 | ((((s32) (((var_t0 - var_t1) * 2) + 9) >> 3) & 0x1FF) << 9);
                        temp_s0_13 = temp_s0_12 + 8;
                        temp_s0_12->unk4 = 0x07080200;
                        var_s0_2->unk8 = temp_t2_3;
                        temp_s0_12->unk8 = 0xE6000000;
                        temp_v1_6 = ((var_t1 * 4) & 0xFFF) << 0xC;
                        temp_t9_2 = (var_t5 * 4) & 0xFFF;
                        temp_s0_13->unk4 = 0;
                        temp_s0_14 = temp_s0_13 + 8;
                        temp_a1_3 = ((var_t0 * 4) & 0xFFF) << 0xC;
                        temp_s0_13->unk8 = (s32) (temp_v1_6 | 0xF4000000 | temp_t9_2);
                        temp_t8_3 = (var_ra * 4) & 0xFFF;
                        temp_s0_15 = temp_s0_14 + 8;
                        temp_s0_14->unk4 = (s32) (temp_a1_3 | 0x07000000 | temp_t8_3);
                        temp_s0_16 = temp_s0_15 + 8;
                        temp_s0_14->unk8 = 0xE7000000;
                        var_s0_3 = temp_s0_16 + 8;
                        temp_s0_15->unk4 = 0;
                        temp_s0_16->unk4 = 0x80200;
                        temp_s0_15->unk8 = temp_t2_3;
                        var_s0_3->unk4 = (s32) (temp_a1_3 | temp_t8_3);
                        temp_s0_16->unk8 = (s32) (temp_v1_6 | 0xF2000000 | temp_t9_2);
                        goto block_32;
                    }
                    if (spA8 == 4) {
                        temp_v0_7 = (arg2 & 7) << 0x15;
                        var_s0_2->unk0 = (s32) (temp_v0_7 | 0xFD000000 | 0x80000 | (((arg3 >> 1) - 1) & 0xFFF));
                        temp_s0_17 = var_s0_2 + 8;
                        temp_a2 = temp_v0_7 | 0xF5000000;
                        temp_a3 = (((s32) (((s32) ((var_t0 - var_t1) + 1) >> 1) + 7) >> 3) & 0x1FF) << 9;
                        var_s0_2->unk4 = arg1;
                        temp_s0_17->unk4 = 0x07080200;
                        var_s0_2->unk8 = (s32) (temp_a2 | 0x80000 | temp_a3);
                        temp_s0_18 = temp_s0_17 + 8;
                        temp_t8_4 = (var_t5 * 4) & 0xFFF;
                        temp_s0_17->unk8 = 0xE6000000;
                        temp_s0_19 = temp_s0_18 + 8;
                        temp_s0_18->unk4 = 0;
                        temp_t7_3 = (var_ra * 4) & 0xFFF;
                        temp_s0_18->unk8 = (s32) ((((var_t1 * 2) & 0xFFF) << 0xC) | 0xF4000000 | temp_t8_4);
                        temp_s0_20 = temp_s0_19 + 8;
                        temp_s0_19->unk4 = (s32) ((((var_t0 * 2) & 0xFFF) << 0xC) | 0x07000000 | temp_t7_3);
                        temp_s0_19->unk8 = 0xE7000000;
                        temp_s0_21 = temp_s0_20 + 8;
                        temp_s0_20->unk4 = 0;
                        temp_s0_20->unk8 = (s32) (temp_a2 | temp_a3);
                        temp_s0_21->unk4 = 0x80200;
                        var_s0_3 = temp_s0_21 + 8;
                        temp_s0_21->unk8 = (s32) ((((var_t1 * 4) & 0xFFF) << 0xC) | 0xF2000000 | temp_t8_4);
                        var_s0_3->unk4 = (s32) ((((var_t0 * 4) & 0xFFF) << 0xC) | temp_t7_3);
block_32:
                        var_s0_2 = var_s0_3 + 8;
                    }
                    if (arg15 != 0) {
                        if ((var_s5_2 == spD0) && (arg15 == 1)) {
                            func_80704130(var_s2, 0xFF, 0xFF, 0xFF, 0, 0);
                        } else {
                            func_80704130(var_s2, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                        }
                    }
                    if (arg16 != NULL) {
                        arg16(sp1C8, sp1C4, var_s2);
                    }
                    temp_s2 = var_s2 + 0x10;
                    sp88 = (s32) unksp1CA;
                    temp_fs0 = (f32) ((f64) (f32) var_s5_2 - 16.0);
                    temp_ft2 = (s32) temp_fs0;
                    sp7C = (s32) (s16) temp_ft2;
                    func_80704444(var_s2, unksp1CA, unksp6A, (s16) temp_ft2, sp64, (s32) sp183);
                    if (arg15 != 0) {
                        if (((u32) (var_s5_2 + spC0) >= spCC) && (arg15 == 2)) {
                            func_80704130(temp_s2, 0xFF, 0xFF, 0xFF, 0, 0);
                        } else {
                            func_80704130(temp_s2, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                        }
                    }
                    spB4 = var_s5_2 + spC0;
                    if (arg16 != NULL) {
                        arg16((s32) (s16) (sp1C8 + spD8), sp1C4, temp_s2);
                    }
                    temp_ft1_2 = (s32) (temp_fs0 + (f32) spC0);
                    temp_s6 = sp1C8 + spD8;
                    temp_s2_2 = temp_s2 + 0x10;
                    func_80704444(temp_s2, temp_s6, unksp6A, (s16) temp_ft1_2, sp64, (s32) sp183);
                    if (arg15 != 0) {
                        if ((spB4 >= spCC) && (arg15 == 2)) {
                            func_80704130(temp_s2_2, 0xFF, 0xFF, 0xFF, 0, 0);
                        } else {
                            func_80704130(temp_s2_2, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                        }
                    }
                    if (arg16 != NULL) {
                        arg16((s32) temp_s6, sp84, temp_s2_2);
                    }
                    temp_s2_3 = temp_s2_2 + 0x10;
                    func_80704444(temp_s2_2, temp_s6, unksp82, (s16) temp_ft1_2, sp78, (s32) sp183);
                    if (arg15 != 0) {
                        if ((var_s5_2 == spD0) && (arg15 == 1)) {
                            func_80704130(temp_s2_3, 0xFF, 0xFF, 0xFF, 0, 0);
                        } else {
                            func_80704130(temp_s2_3, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                        }
                    }
                    if (arg16 != NULL) {
                        arg16(sp1C8, sp84, temp_s2_3);
                    }
                    var_s2 = temp_s2_3 + 0x10;
                    func_80704444(temp_s2_3, unksp8A, unksp82, unksp7E, sp78, (s32) sp183);
                    var_s0_2->unk0 = 0x01004008;
                    temp_s0_22 = var_s0_2 + 8;
                    var_s0_2->unk4 = osVirtualToPhysical(var_s2 - 0x40);
                    temp_s0_23 = temp_s0_22 + 8;
                    temp_s0_22->unk4 = 0x406;
                    var_s0_2->unk8 = 0x06000204;
                    temp_s0_22->unk8 = 0xE7000000;
                    temp_s0_23->unk4 = 0;
                    var_s5_2 = spB4;
                    sp1C8 = (s32) temp_s6;
                    var_s0_2 = temp_s0_23 + 8;
                } while (var_s5_2 < sp18C);
                var_s4 = spD0;
                var_a1 = sp1C4;
                var_v0 = (u32) sp1D0;
            }
            var_v0 += spC4;
            var_a1 += spD4;
        } while (var_v0 < sp184);
    }
    *arg0 = var_s0_2;
}
