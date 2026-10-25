// func_80723484 (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
extern ? D_807FDBF8;

void func_80723484(s32 arg0) {
    f32 temp_fa0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 var_ft1;
    f32 var_ft5;
    s16 temp_a1_3;
    s16 temp_t1;
    s16 var_a0_2;
    s32 *var_a0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a3;
    s32 temp_a3_2;
    s32 temp_ft3;
    s32 temp_hi;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_t0;
    s32 temp_t0_3;
    s32 temp_t0_5;
    s32 temp_t1_2;
    s32 temp_t4;
    s32 temp_t7;
    s32 var_a2;
    u8 temp_a1_2;
    u8 temp_t0_2;
    u8 temp_t0_4;
    u8 temp_t0_6;
    u8 temp_t2;
    u8 temp_t9;
    void *temp_a1;

    if ((arg0 != -1) && (temp_a1 = *(&D_807FDBF8 + (arg0 * 4)), (temp_a1 != NULL)) && (temp_a1->unk21 != 0)) {
        temp_a1_2 = temp_a1->unk16;
        var_a0 = temp_a1 + 4;
        if (temp_a1_2 == 0) {
            var_a0 = temp_a1 + 4;
            var_a2 = temp_a1->unk10 + 1;
        } else {
            temp_t1 = var_a0->unk4;
            temp_t0 = temp_a1->unk10 + 1;
            if (temp_t0 >= temp_t1) {
                var_a2 = temp_t0 % (s32) (temp_t1 - 1);
            } else {
                var_a2 = temp_t0;
            }
        }
        temp_t1_2 = *var_a0;
        temp_fv1 = temp_a1->unkC;
        temp_t2 = (temp_t1_2 + (temp_a1->unk10 * 0xA))->unk8;
        var_ft1 = (f32) temp_t2;
        if ((s32) temp_t2 < 0) {
            var_ft1 += 4294967296.0f;
        }
        temp_t9 = temp_a1->unk20;
        var_ft5 = (f32) temp_t9;
        if ((s32) temp_t9 < 0) {
            var_ft5 += 4294967296.0f;
        }
        temp_t0_2 = temp_a1->unk14;
        temp_fa0 = var_ft5 * (f32) ((f64) (var_ft1 + ((f32) ((temp_t1_2 + (var_a2 * 0xA))->unk8 - temp_t2) * temp_fv1)) / 300.0);
        switch (temp_t0_2) {                        /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            temp_a1->unkC = (f32) (temp_fv1 + temp_fa0);
            temp_fv1_2 = temp_a1->unkC;
            temp_ft3 = (s32) temp_fv1_2;
            temp_a1->unk10 = (s32) (temp_a1->unk10 + temp_ft3);
            temp_a1->unkC = (f32) (temp_fv1_2 - (f32) temp_ft3);
            if (temp_a1_2 == 0) {
                var_a0_2 = temp_a1->unk8 - 1;
            } else {
                var_a0_2 = temp_a1->unk8;
            }
            temp_a3 = temp_a1->unk10;
            temp_a0 = temp_a1->unk8 - 1;
            if (temp_a3 >= var_a0_2) {
                temp_lo = temp_a3 / temp_a0;
                temp_t0_3 = temp_a1->unk18;
                temp_t7 = temp_a1->unk1C + temp_lo;
                temp_a1->unk1C = temp_t7;
                if ((temp_t7 >= temp_t0_3) && (temp_t0_3 != -1)) {
                    temp_a1->unk10 = (s32) (temp_a1->unk8 - 2);
                    temp_a1->unk21 = 0U;
                    temp_a1->unkC = 1.0f;
                    if (temp_a1->unk15 == 1) {
                        temp_a1->unk14 = 1U;
                        return;
                    }
                } else {
                    temp_t0_4 = temp_a1->unk15;
                    switch (temp_t0_4) {            /* switch 2; irregular */
                    case 0:                         /* switch 2 */
                        if (temp_a1->unk16 == 0) {
                            temp_a1->unk10 = (s32) (temp_a3 % temp_a0);
                            return;
                        }
                        temp_a1->unk10 = (s32) (temp_a3 % temp_a1->unk8);
                        return;
                    case 1:                         /* switch 2 */
                        if (temp_lo != 0) {
                            temp_a1->unk14 = 1U;
                            temp_a1->unk10 = (s32) (temp_a1->unk8 - 2);
                            temp_a1->unkC = 1.0f;
                            return;
                        }
                        break;
                    }
                }
            }
            break;
        case 1:                                     /* switch 1 */
            temp_a1->unkC = (f32) (temp_fv1 - temp_fa0);
            temp_fv1_3 = temp_a1->unkC;
            if ((f64) temp_fv1_3 < 0.0) {
                temp_a0_2 = (s32) temp_fv1_3 - 1;
                temp_a1->unk10 = (s32) (temp_a1->unk10 + temp_a0_2);
                temp_a1->unkC = (f32) (temp_fv1_3 - (f32) temp_a0_2);
            }
            temp_a3_2 = temp_a1->unk10;
            temp_a0_3 = -temp_a3_2;
            if (temp_a3_2 < 0) {
                temp_a1_3 = temp_a1->unk8;
                temp_t0_5 = temp_a1->unk18;
                temp_lo_2 = temp_a0_3 / temp_a1_3;
                temp_t4 = temp_a1->unk1C + temp_lo_2 + 1;
                temp_a1->unk1C = temp_t4;
                if ((temp_t4 >= temp_t0_5) && (temp_t0_5 != -1)) {
                    temp_a1->unk10 = 0;
                    temp_a1->unk21 = 0U;
                    temp_a1->unkC = 0.0f;
                    if (temp_a1->unk15 == 1) {
                        temp_a1->unk14 = 0U;
                        return;
                    }
                } else {
                    temp_t0_6 = temp_a1->unk15;
                    switch (temp_t0_6) {            /* switch 3; irregular */
                    case 0:                         /* switch 3 */
                        temp_hi = temp_a0_3 % (s32) (temp_a1_3 - 1);
                        temp_a1->unk10 = temp_hi;
                        if (temp_hi != 0) {
                            temp_a1->unk10 = (s32) ((temp_a1_3 - temp_hi) - 1);
                            return;
                        }
                        break;
                    case 1:                         /* switch 3 */
                        if ((temp_lo_2 + 1) != 0) {
                            temp_a1->unk14 = 0U;
                            temp_a1->unk10 = 0;
                            temp_a1->unkC = 0.0f;
                        }
                        break;
                    }
                }
            }
            break;
        }
    }
}
