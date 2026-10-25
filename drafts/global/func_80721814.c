// func_80721814 (src/global/126260.c): stage 1 m2c behavioral baseline; compact private candidate reaches 5696 vs target 6304 bytes but requires restoration of original expression/temporary structure
extern s32 D_8076A048;
extern u8 D_807FDB75;

s32 func_80721814(s32 arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4) {
    void *sp24;
    void *sp20;
    void *sp1C;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_5;
    f32 temp_fv0_6;
    f32 temp_fv1;
    f32 temp_fv1_3;
    f32 var_fa1;
    f32 var_ft0;
    f32 var_ft1;
    f32 var_ft2;
    f32 var_ft3;
    f32 var_ft3_2;
    f32 var_ft3_3;
    f32 var_ft3_4;
    f32 var_ft5;
    f32 var_fv1;
    f64 temp_fa0;
    f64 temp_fa0_2;
    f64 temp_fv0_2;
    f64 temp_fv0_3;
    f64 temp_fv0_4;
    f64 temp_fv1_2;
    f64 temp_fv1_4;
    f64 var_fv0;
    f64 var_fv0_2;
    f64 var_fv1_2;
    f64 var_fv1_3;
    s16 temp_v0_3;
    s32 temp_t6;
    s32 temp_v0;
    s32 var_v0;
    u32 temp_v0_10;
    u32 temp_v0_11;
    u32 temp_v0_12;
    u32 temp_v0_4;
    u32 temp_v0_5;
    u32 temp_v0_6;
    u32 temp_v0_7;
    u32 temp_v0_8;
    u32 temp_v0_9;
    u8 temp_a0;
    u8 temp_a1;
    u8 temp_t2;
    u8 temp_t3;
    u8 temp_t5;
    u8 temp_t6_2;
    u8 temp_t7;
    u8 temp_t8;
    u8 temp_v0_2;
    u8 temp_v1;
    void *temp_a3;
    void *temp_t0;
    void *temp_t1;

    temp_t6 = arg0 & 0xFF;
    temp_v0 = D_8076A048 + (D_807FDB75 * 0x78);
    temp_a3 = temp_v0 + 0x278;
    temp_t0 = temp_v0 + 0x270;
    temp_t1 = temp_v0 + (temp_t6 * 0x10) + 0x278;
    if (temp_t6 >= 7) {
        return 0;
    }
    if (arg1->unkE == 5) {
        sp1C = temp_t1;
        sp20 = temp_t0;
        sp24 = temp_a3;
        temp_fv0 = arg2 - (f32) arg1->unk4;
        temp_fv1 = arg4 - (f32) arg1->unk8;
        temp_fv1_2 = (f64) sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
        if (temp_fv1_2 > 0.001) {
            var_ft5 = (f32) temp_fv1_2;
        } else {
            var_ft5 = (f32) 0.001;
        }
        temp_v0_2 = arg1->unkA;
        temp_fv0_2 = (f64) (var_ft5 - (f32) ((s32) temp_v0_2 / 2));
        if (temp_fv0_2 < 1.0) {
            var_fv1 = (f32) 1.0;
        } else {
            var_fv1 = (f32) temp_fv0_2;
        }
        temp_fv0_3 = (f64) var_fv1;
        var_ft3 = (f32) temp_v0_2;
        if ((s32) temp_v0_2 < 0) {
            var_ft3 += 4294967296.0f;
        }
        temp_fa0 = (f64) var_ft3 / (0.5 * temp_fv0_3 * temp_fv0_3);
        if (temp_fa0 > 1.0) {
            var_fa1 = (f32) 1.0;
        } else {
            var_fa1 = (f32) temp_fa0;
        }
        temp_v0_3 = arg1->unk6;
        if ((f32) (temp_v0_3 + 0x32) < arg3) {
            temp_fv0_4 = (f64) ((arg3 - (f32) temp_v0_3) - 50.0f);
            if (temp_fv0_4 > 20.0) {
                var_fv1_2 = 20.0;
            } else {
                var_fv1_2 = temp_fv0_4;
            }
            var_fa1 = (f32) ((f64) var_fa1 * (1.0 - (var_fv1_2 / 20.0)));
        }
    } else {
        sp1C = temp_t1;
        sp20 = temp_t0;
        sp24 = temp_a3;
        temp_fv0_5 = arg2 - (f32) arg1->unk4;
        temp_fa1 = arg3 - (f32) arg1->unk6;
        temp_fv1_3 = arg4 - (f32) arg1->unk8;
        temp_fv1_4 = (f64) sqrtf((temp_fv0_5 * temp_fv0_5) + (temp_fa1 * temp_fa1) + (temp_fv1_3 * temp_fv1_3));
        if (temp_fv1_4 > 0.001) {
            var_ft5 = (f32) temp_fv1_4;
        } else {
            var_ft5 = (f32) 0.001;
        }
        var_fa1 = 1.0f;
    }
    if (arg1->unkE == 5) {
        temp_fa0_2 = (f64) var_fa1;
        if (temp_fa0_2 > 0.1) {
            temp_v1 = *temp_a3;
            var_ft1 = (f32) temp_v1;
            if ((s32) temp_v1 < 0) {
                var_ft1 += 4294967296.0f;
            }
            temp_v0_4 = (u32) (((f32) (arg1->unkB - temp_v1) * var_fa1) + var_ft1);
            temp_a3->unk4 = (s8) temp_v0_4;
            *temp_a3 = (u8) temp_v0_4;
            temp_a0 = temp_a3->unk1;
            var_ft2 = (f32) temp_a0;
            if ((s32) temp_a0 < 0) {
                var_ft2 += 4294967296.0f;
            }
            temp_v0_5 = (u32) (((f32) (arg1->unkC - temp_a0) * var_fa1) + var_ft2);
            temp_a3->unk5 = (s8) temp_v0_5;
            temp_a3->unk1 = (u8) temp_v0_5;
            temp_a1 = temp_a3->unk2;
            var_ft0 = (f32) temp_a1;
            if ((s32) temp_a1 < 0) {
                var_ft0 += 4294967296.0f;
            }
            temp_v0_6 = (u32) (((f32) (arg1->unkD - temp_a1) * var_fa1) + var_ft0);
            temp_a3->unk6 = (s8) temp_v0_6;
            temp_a3->unk2 = (u8) temp_v0_6;
            temp_t7 = *temp_t0;
            var_fv0 = (f64) temp_t7;
            if ((s32) temp_t7 < 0) {
                var_fv0 += 4294967296.0;
            }
            temp_v0_7 = (u32) ((((var_fv0 * 0.5) - var_fv0) * temp_fa0_2) + var_fv0);
            temp_t2 = temp_t0->unk1;
            temp_t0->unk4 = (s8) temp_v0_7;
            *temp_t0 = (u8) temp_v0_7;
            var_fv1_3 = (f64) temp_t2;
            if ((s32) temp_t2 < 0) {
                var_fv1_3 += 4294967296.0;
            }
            temp_v0_8 = (u32) ((((var_fv1_3 * 0.5) - var_fv1_3) * temp_fa0_2) + var_fv1_3);
            temp_t5 = temp_t0->unk2;
            temp_t0->unk5 = (s8) temp_v0_8;
            temp_t0->unk1 = (u8) temp_v0_8;
            var_fv0_2 = (f64) temp_t5;
            if ((s32) temp_t5 < 0) {
                var_fv0_2 += 4294967296.0;
            }
            temp_v0_9 = (u32) ((((var_fv0_2 * 0.5) - var_fv0_2) * temp_fa0_2) + var_fv0_2);
            temp_t0->unk6 = (s8) temp_v0_9;
            temp_t0->unk2 = (u8) temp_v0_9;
        }
        return 0;
    }
    var_v0 = 0;
    if ((f64) var_fa1 > 0.02) {
        temp_t8 = arg1->unkB;
        var_ft3_2 = (f32) temp_t8;
        if ((s32) temp_t8 < 0) {
            var_ft3_2 += 4294967296.0f;
        }
        temp_v0_10 = (u32) (var_ft3_2 * var_fa1);
        temp_t1->unk4 = (s8) temp_v0_10;
        *temp_t1 = (s8) temp_v0_10;
        temp_t3 = arg1->unkC;
        var_ft3_3 = (f32) temp_t3;
        if ((s32) temp_t3 < 0) {
            var_ft3_3 += 4294967296.0f;
        }
        temp_v0_11 = (u32) (var_ft3_3 * var_fa1);
        temp_t1->unk5 = (s8) temp_v0_11;
        temp_t1->unk1 = (s8) temp_v0_11;
        temp_t6_2 = arg1->unkD;
        var_ft3_4 = (f32) temp_t6_2;
        if ((s32) temp_t6_2 < 0) {
            var_ft3_4 += 4294967296.0f;
        }
        temp_v0_12 = (u32) (var_ft3_4 * var_fa1);
        temp_t1->unk6 = (s8) temp_v0_12;
        temp_fv0_6 = 127.0f / var_ft5;
        temp_t1->unk2 = (s8) temp_v0_12;
        var_v0 = 1;
        temp_t1->unk8 = (s8) (s32) (((f32) arg1->unk4 - arg2) * temp_fv0_6);
        temp_t1->unk9 = (s8) (s32) (((f32) arg1->unk6 - arg3) * temp_fv0_6);
        temp_t1->unkA = (s8) (s32) (((f32) arg1->unk8 - arg4) * temp_fv0_6);
    }
    return var_v0;
}
