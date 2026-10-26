// func_80614644 (src/global/17B90.c): stage 1: m2c behavioral starter saved; requires typed controller/window views and first compilable fdiff attempt.
void func_80614644(void *arg0, void *arg1, f32 arg2) {
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa1;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_t2;
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    u16 temp_v1;
    void *temp_v0;

    temp_v0 = arg0->unk4;
    var_fa1 = arg2;
    temp_v1 = arg1->unk1C;
    temp_fv0 = arg1->unk14;
    temp_fv1 = arg1->unk18;
    var_a2 = 0;
    var_a3 = 0;
    if (temp_v0->unk84 != 0) {
        var_a0 = temp_v0->unk4;
    } else {
        var_a0 = temp_v0->unk0;
    }
    if (temp_v1 & 8) {
        temp_fa0 = var_fa1 - (f32) arg1->unk1E;
        if (temp_fa0 > 0.0f) {
            arg1->unk8 = temp_fa0;
        } else {
            arg1->unk8 = (f32) -temp_fa0;
        }
        if ((f64) arg1->unk8 < 1.0) {
            arg1->unk4 = var_fa1;
            arg1->unkC = (s16) arg1->unk1E;
            arg1->unkE = (s16) arg1->unk20;
            return;
        }
        arg1->unk1C = (u16) ((s16) arg1->unk1C & 0xFFF7);
        var_fa1 += (f32) ((arg1->unk20 - arg1->unk1E) - (s32) temp_fa0);
        if (arg1 == var_a0) {
            temp_v0->unk78 = (s32) (temp_v0->unk78 & ~0x20);
        }
        goto block_11;
    }
block_11:
    if (temp_v1 & 4) {
        if (temp_fv1 < var_fa1) {
            var_a3 = 1;
            var_fa1 = (2.0f * temp_fv1) - var_fa1;
        } else if (var_fa1 < temp_fv0) {
            var_a3 = 1;
            var_a2 = 1;
            var_fa1 = (2.0f * temp_fv0) - var_fa1;
        }
        if (var_a3 != 0) {
            arg1->unk24 = (f32) (0.0f - arg1->unk24);
            if (arg1->unk34 != 0.0f) {
                arg1->unk2C = (f32) (0.0f - arg1->unk2C);
                arg1->unk28 = (f32) (0.0f - arg1->unk28);
            }
            if (arg1 == var_a0) {
                temp_v0->unk78 = (s32) (temp_v0->unk78 & ~4);
            }
        }
    } else if (temp_v1 & 2) {
        if (((f64) temp_fv1 + 1.0) <= (f64) var_fa1) {
            var_a2 = 1;
            var_fa1 -= (1.0f + temp_fv1) - temp_fv0;
        } else if (var_fa1 < temp_fv0) {
            var_a2 = 1;
            var_fa1 += (1.0f + temp_fv1) - temp_fv0;
        }
    } else if (temp_fv1 <= var_fa1) {
        var_fa1 = temp_fv1;
        if (arg1->unk24 >= 0.0f) {
            arg1->unk24 = 0.0f;
            arg1->unk34 = 0.0f;
            var_a2 = 1;
        }
    } else if (var_fa1 < temp_fv0) {
        var_fa1 = temp_fv0;
        var_a2 = 1;
        if (arg1->unk24 <= 0.0f) {
            arg1->unk24 = 0.0f;
            arg1->unk34 = 0.0f;
        }
    }
    if (arg1 == var_a0) {
        var_v1 = temp_v0->unk78;
        if (var_v1 & 0x3F) {
            if (var_a2 != 0) {
                temp_a0 = temp_v0->unk7C;
                temp_t2 = var_v1 & ~1;
                temp_v0->unk78 = temp_t2;
                if (temp_a0 != 0) {
                    temp_v0->unk7C = (s32) (temp_a0 - 1);
                    var_v1 = temp_t2;
                } else {
                    var_v1 = temp_v0->unk78 & ~2;
                    temp_v0->unk78 = var_v1;
                }
            }
            if (var_v1 & 8) {
                temp_fa0_2 = temp_v0->unk80;
                temp_ft4 = arg1->unk4;
                if (var_fa1 == temp_fa0_2) {
                    if (temp_ft4 != temp_fa0_2) {
                        temp_v0->unk78 = (s32) (var_v1 & ~8);
                    }
                } else if (temp_fa0_2 < var_fa1) {
                    if ((temp_ft4 < temp_fa0_2) && (var_a2 == 0)) {
                        temp_v0->unk78 = (s32) (var_v1 & ~8);
                    } else if ((temp_fa0_2 < temp_ft4) && (var_a2 != 0)) {
                        temp_v0->unk78 = (s32) (var_v1 & ~8);
                    }
                } else if ((temp_fa0_2 < temp_ft4) && (var_a2 == 0)) {
                    temp_v0->unk78 = (s32) (var_v1 & ~8);
                } else if ((temp_ft4 < temp_fa0_2) && (var_a2 != 0)) {
                    temp_v0->unk78 = (s32) (var_v1 & ~8);
                }
            }
        }
    }
    arg1->unk4 = var_fa1;
    arg1->unkC = (s16) (s32) var_fa1;
    temp_v0_2 = arg1->unkC;
    arg1->unkE = (s16) (temp_v0_2 + 1);
    arg1->unk8 = (f32) (var_fa1 - (f32) temp_v0_2);
    if (temp_fv1 < (f32) arg1->unkE) {
        if (temp_v1 & 2) {
            arg1->unkE = (s16) (s32) temp_fv0;
            return;
        }
        arg1->unkE = temp_v0_2;
    }
}
