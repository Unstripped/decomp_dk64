// func_80706F90 (src/global/109660.c): m2c reconstruction; direct Gfx command loop requires stage-2 block ordering and target 0x100 frame/saved-register mapping.
s32 func_8066B0F8(?, s16, ?, ?);                    /* extern */
extern s16 D_80754CE0;
extern s16 D_80754CEC;
extern s16 D_80754F70;
extern s16 D_80754F74;
extern s32 D_807FD978;
extern ? D_807FD998;

void *func_80706F90(void *arg0) {
    s32 spF8;
    s32 spF4;
    u16 spE6;
    s16 spE4;
    s32 sp40;
    s16 *var_s2;
    s16 temp_fp;
    s16 temp_s4;
    s16 temp_s7;
    s16 temp_t0;
    s16 temp_t2;
    s16 temp_t3;
    s16 temp_v0_4;
    s16 temp_v1;
    s16 var_a0;
    s16 var_a0_2;
    s16 var_a0_3;
    s16 var_a0_4;
    s16 var_a0_5;
    s16 var_a0_6;
    s16 var_s4;
    s16 var_t4;
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v0_4;
    s16 var_v0_5;
    s16 var_v0_7;
    s16 var_v0_8;
    s32 *var_s1;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t7_3;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_t5;
    s32 var_v0_3;
    s32 var_v0_6;
    s32 var_v0_9;
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
    void *temp_s0_24;
    void *temp_s0_25;
    void *temp_s0_26;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s0_7;
    void *temp_s0_8;
    void *temp_s0_9;
    void *var_s0;

    temp_s0_2 = arg0 + 8;
    arg0->unk0 = 0xD9000000;
    arg0->unk4 = 0;
    temp_s0_3 = temp_s0_2 + 8;
    arg0->unk8 = 0xD9FFFFFF;
    temp_s0_2->unk4 = 0x200004;
    temp_s0_4 = temp_s0_3 + 8;
    temp_s0_2->unk8 = 0xE3000A01;
    temp_s0_3->unk4 = 0;
    temp_s0_5 = temp_s0_4 + 8;
    temp_s0_4->unk4 = 0x504240;
    temp_s0_3->unk8 = 0xE200001C;
    temp_s0_6 = temp_s0_5 + 8;
    temp_s0_5->unk4 = -0xC07;
    temp_s0_4->unk8 = 0xFC11FE23;
    temp_s0_7 = temp_s0_6 + 8;
    temp_s0_5->unk8 = 0xE3000C00;
    temp_s0_6->unk4 = 0;
    temp_s0_8 = temp_s0_7 + 8;
    temp_s0_6->unk8 = 0xE3001201;
    temp_s0_7->unk4 = 0;
    temp_s0_9 = temp_s0_8 + 8;
    temp_s0_7->unk8 = 0xD7000002;
    temp_s0_8->unk4 = 0x80008000;
    temp_s0_8->unk8 = 0xFA000000;
    temp_s0_10 = temp_s0_9 + 8;
    temp_s0_9->unk4 = -1;
    temp_s0_9->unk8 = 0xE7000000;
    temp_s0_10->unk4 = 0;
    var_s0 = temp_s0_10 + 8;
    temp_s4 = D_80754F74 + D_80754CE0;
    var_s4 = temp_s4;
    if (temp_s4 < 0) {
        var_s4 = temp_s4 + 0x200;
    }
    if (var_s4 >= 0x200) {
        var_s4 -= 0x200;
    }
    var_s1 = &D_807FD978;
    var_s2 = &D_80754CEC;
    if (D_807FD978 == 0) {
        do {
            temp_v0 = func_8066B0F8(0x19, *var_s2, 0, 0);
            var_s1 += 4;
            var_s2 += 2;
            var_s1->unk-4 = temp_v0;
        } while (var_s1 != &D_807FD998);
    }
    spE4 = var_s4;
    spE6 = 0;
    spF4 = 0x40;
    do {
        spF8 = 0;
        temp_fp = (spF4 * 4) - spE4;
        temp_s7 = temp_fp + 0x100;
        sp40 = temp_fp + 0x200;
loop_9:
        var_s0->unk0 = 0xE7000000;
        var_s0->unk4 = 0;
        temp_s0_11 = var_s0 + 8;
        temp_s0_12 = temp_s0_11 + 8;
        temp_s0_11->unk4 = (s32) ((&D_807FD978)[spE6] + 0x80000000);
        var_s0->unk8 = 0xFD100000;
        temp_s0_13 = temp_s0_12 + 8;
        temp_s0_11->unk8 = 0xF5100000;
        temp_s0_12->unk4 = 0x07080200;
        temp_s0_14 = temp_s0_13 + 8;
        temp_s0_12->unk8 = 0xE6000000;
        temp_s0_13->unk4 = 0;
        temp_s0_15 = temp_s0_14 + 8;
        temp_s0_13->unk8 = 0xF3000000;
        temp_s0_14->unk4 = 0x077FF100;
        temp_s0_16 = temp_s0_15 + 8;
        temp_s0_14->unk8 = 0xE7000000;
        temp_s0_15->unk4 = 0;
        temp_s0_17 = temp_s0_16 + 8;
        temp_s0_16->unk4 = 0x80200;
        temp_s0_15->unk8 = 0xF5101000;
        temp_s0_16->unk8 = 0xF2000000;
        temp_s0_17->unk4 = 0x7C0FC;
        var_s0 = temp_s0_17 + 8;
        var_t5 = 0;
        var_t4 = (spF8 * 4) - D_80754F70;
loop_10:
        temp_t3 = var_t4 + 0x80;
        temp_s0_18 = var_s0 + 8;
        if (temp_t3 > 0) {
            var_a0 = temp_t3;
        } else {
            var_a0 = 0;
        }
        if (temp_s7 > 0) {
            var_v0 = temp_s7;
        } else {
            var_v0 = 0;
        }
        var_s0->unk0 = (s32) ((var_v0 & 0xFFF) | 0xE4000000 | ((var_a0 & 0xFFF) << 0xC));
        if (var_t4 > 0) {
            var_a0_2 = var_t4;
        } else {
            var_a0_2 = 0;
        }
        if (temp_fp > 0) {
            var_v0_2 = temp_fp;
        } else {
            var_v0_2 = 0;
        }
        var_s0->unk4 = (s32) ((var_v0_2 & 0xFFF) | ((var_a0_2 & 0xFFF) << 0xC));
        var_s0->unk8 = 0xE1000000;
        temp_s0_19 = temp_s0_18 + 8;
        if (var_t4 < 0) {
            temp_t7 = (s32) (var_t4 << 0xA) >> 7;
            if (temp_t7 < 0) {
                var_a2 = temp_t7;
            } else {
                var_a2 = 0;
            }
        } else {
            var_a2 = 0;
        }
        if (temp_fp < 0) {
            temp_t9 = (s32) (temp_fp * -0x400) >> 7;
            if (temp_t9 > 0) {
                var_v0_3 = temp_t9;
            } else {
                var_v0_3 = 0;
            }
        } else {
            var_v0_3 = 0;
        }
        temp_s0_18->unk4 = (s32) (((0x7FF - var_v0_3) & 0xFFFF) | (var_a2 * -0x10000));
        temp_s0_20 = temp_s0_19 + 8;
        temp_s0_19->unk4 = 0x0400FC00;
        temp_s0_18->unk8 = 0xF1000000;
        temp_s0_21 = temp_s0_20 + 8;
        if (temp_t3 > 0) {
            var_a0_3 = temp_t3;
        } else {
            var_a0_3 = 0;
        }
        temp_v1 = sp40 + 0x100;
        if (temp_v1 > 0) {
            var_v0_4 = temp_v1;
        } else {
            var_v0_4 = 0;
        }
        temp_s0_19->unk8 = (s32) ((var_v0_4 & 0xFFF) | 0xE4000000 | ((var_a0_3 & 0xFFF) << 0xC));
        if (var_t4 > 0) {
            var_a0_4 = var_t4;
        } else {
            var_a0_4 = 0;
        }
        if ((s16) sp40 > 0) {
            var_v0_5 = (s16) sp40;
        } else {
            var_v0_5 = 0;
        }
        temp_s0_20->unk4 = (s32) ((var_v0_5 & 0xFFF) | ((var_a0_4 & 0xFFF) << 0xC));
        temp_s0_20->unk8 = 0xE1000000;
        temp_s0_22 = temp_s0_21 + 8;
        if (var_t4 < 0) {
            temp_t6 = (s32) (var_t4 << 0xA) >> 7;
            if (temp_t6 < 0) {
                var_a2_2 = temp_t6;
            } else {
                var_a2_2 = 0;
            }
        } else {
            var_a2_2 = 0;
        }
        if (sp40 < 0) {
            temp_t7_2 = (s32) ((s16) sp40 * -0x400) >> 7;
            if (temp_t7_2 > 0) {
                var_v0_6 = temp_t7_2;
            } else {
                var_v0_6 = 0;
            }
        } else {
            var_v0_6 = 0;
        }
        temp_s0_23 = temp_s0_22 + 8;
        temp_s0_21->unk4 = (s32) (((0x7FF - var_v0_6) & 0xFFFF) | (var_a2_2 * -0x10000));
        temp_s0_22->unk4 = 0x0400FC00;
        temp_s0_21->unk8 = 0xF1000000;
        temp_t0 = sp40 + 0x200;
        temp_s0_24 = temp_s0_23 + 8;
        if (temp_t3 > 0) {
            var_a0_5 = temp_t3;
        } else {
            var_a0_5 = 0;
        }
        temp_t2 = temp_t0 + 0x100;
        if (temp_t2 > 0) {
            var_v0_7 = temp_t2;
        } else {
            var_v0_7 = 0;
        }
        temp_s0_22->unk8 = (s32) ((var_v0_7 & 0xFFF) | 0xE4000000 | ((var_a0_5 & 0xFFF) << 0xC));
        if (var_t4 > 0) {
            var_a0_6 = var_t4;
        } else {
            var_a0_6 = 0;
        }
        if (temp_t0 > 0) {
            var_v0_8 = temp_t0;
        } else {
            var_v0_8 = 0;
        }
        temp_s0_23->unk4 = (s32) ((var_v0_8 & 0xFFF) | ((var_a0_6 & 0xFFF) << 0xC));
        temp_s0_23->unk8 = 0xE1000000;
        temp_s0_25 = temp_s0_24 + 8;
        if (var_t4 < 0) {
            temp_t7_3 = (s32) (var_t4 << 0xA) >> 7;
            if (temp_t7_3 < 0) {
                var_a2_3 = temp_t7_3;
            } else {
                var_a2_3 = 0;
            }
        } else {
            var_a2_3 = 0;
        }
        if (temp_t2 < 0x100) {
            temp_t8 = (s32) (temp_t0 * -0x400) >> 7;
            if (temp_t8 > 0) {
                var_v0_9 = temp_t8;
            } else {
                var_v0_9 = 0;
            }
        } else {
            var_v0_9 = 0;
        }
        var_t5 += 1;
        temp_s0_24->unk4 = (s32) (((0x7FF - var_v0_9) & 0xFFFF) | (var_a2_3 * -0x10000));
        temp_s0_25->unk4 = 0x0400FC00;
        temp_s0_24->unk8 = 0xF1000000;
        var_s0 = temp_s0_25 + 8;
        var_t4 += 0x200;
        if (var_t5 != 4) {
            goto loop_10;
        }
        temp_v0_3 = spF8 + 0x20;
        spE6 += 1;
        spF8 = temp_v0_3;
        if (temp_v0_3 != 0x80) {
            goto loop_9;
        }
        temp_v0_2 = spF4 - 0x40;
        spF4 = temp_v0_2;
    } while (temp_v0_2 >= 0);
    temp_v0_4 = D_80754F70 + 4;
    D_80754F74 += 4;
    D_80754F70 = temp_v0_4;
    if (temp_v0_4 >= 0x200) {
        D_80754F70 = 0;
    }
    temp_s0_26 = var_s0 + 8;
    if (D_80754F74 >= 0x200) {
        D_80754F74 = 0;
    }
    temp_s0_25->unk8 = 0xE7000000;
    var_s0->unk4 = 0;
    temp_s0 = temp_s0_26 + 8;
    temp_s0_26->unk4 = 0x80000;
    var_s0->unk8 = 0xE3000C00;
    temp_s0->unk4 = 0x2000;
    temp_s0_26->unk8 = 0xE3001201;
    return temp_s0 + 8;
}
