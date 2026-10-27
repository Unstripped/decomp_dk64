// func_807238D4 (src/global/127B00.c): stage 1: m2c starter regenerated in second pass; not yet integrated after priority small-function matches
f32 splineEvalCubic(f64, f32, void *, void **, f32, f32); /* extern */
? splineSetBasisTension(?);                                 /* extern */
extern ? D_807FDBF8;

void func_807238D4(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 sp2F;                                        /* compiler-managed */
    s8 sp2E;
    u8 sp2D;
    s8 sp2C;
    void *sp28;
    void **sp20;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s8 temp_v0_2;
    s8 temp_v0_5;
    s8 temp_v1;
    s8 temp_v1_2;
    s8 var_v1;
    void **temp_v0;
    void **var_a1;
    void *temp_a0;
    void *temp_v0_10;
    void *temp_v0_8;
    void *temp_v0_9;

    if (arg0 != -1) {
        temp_v0 = (arg0 * 4) + &D_807FDBF8;
        if (*temp_v0 != NULL) {
            sp20 = temp_v0;
            splineSetBasisTension(0x3F000000);
            temp_a0 = *temp_v0;
            var_a1 = temp_a0 + 4;
            if (temp_a0->unk16 == 0) {
                temp_v0_2 = temp_a0->unk10 - 1;
                if (temp_v0_2 < 0) {
                    sp2C = 0;
                } else {
                    sp2C = temp_v0_2;
                }
                temp_v0_3 = var_a1->unk4;
                temp_v1 = temp_a0->unk10 + 1;
                if (temp_v1 >= temp_v0_3) {
                    sp2E = temp_v0_3 - 1;
                } else {
                    sp2E = temp_v1;
                }
                temp_v0_4 = var_a1->unk4;
                var_v1 = temp_a0->unk10 + 2;
                if (var_v1 >= temp_v0_4) {
                    sp2F = temp_v0_4 - 1;
                } else {
                    goto block_20;
                }
            } else {
                var_a1 = temp_a0 + 4;
                temp_v0_5 = temp_a0->unk10 - 1;
                if (temp_v0_5 < 0) {
                    var_a1 = temp_a0 + 4;
                    sp2C = var_a1->unk4 - 1;
                } else {
                    sp2C = temp_v0_5;
                }
                temp_v0_6 = var_a1->unk4;
                temp_v1_2 = temp_a0->unk10 + 1;
                if (temp_v1_2 >= temp_v0_6) {
                    sp2E = (s8) (temp_v1_2 % temp_v0_6);
                } else {
                    sp2E = temp_v1_2;
                }
                temp_v0_7 = var_a1->unk4;
                var_v1 = temp_a0->unk10 + 2;
                if (var_v1 >= temp_v0_7) {
                    sp2F = (u8) (var_v1 % temp_v0_7);
                } else {
block_20:
                    sp2F = var_v1;
                }
            }
            sp2D = (u8) temp_a0->unk10;
            temp_v0_8 = *var_a1;
            sp20 = var_a1;
            sp28 = temp_a0;
            *arg1 = splineEvalCubic((f64) temp_a0->unkC, (f32) (temp_v0_8 + ((u8) sp2C * 0xA))->unk2, temp_a0, var_a1, (f32) (temp_v0_8 + ((u8) sp2E * 0xA))->unk2, (f32) (temp_v0_8 + ((u8) sp2F * 0xA))->unk2);
            temp_v0_9 = *var_a1;
            *arg2 = splineEvalCubic((f64) temp_a0->unkC, (f32) (temp_v0_9 + ((u8) sp2C * 0xA))->unk4, temp_a0, var_a1, (f32) (temp_v0_9 + ((u8) sp2E * 0xA))->unk4, (f32) (temp_v0_9 + ((u8) sp2F * 0xA))->unk4);
            temp_v0_10 = *var_a1;
            *arg3 = splineEvalCubic((f64) temp_a0->unkC, (f32) (temp_v0_10 + ((u8) sp2C * 0xA))->unk6, temp_a0, var_a1, (f32) (temp_v0_10 + ((u8) sp2E * 0xA))->unk6, (f32) (temp_v0_10 + ((u8) sp2F * 0xA))->unk6);
        }
    }
}
