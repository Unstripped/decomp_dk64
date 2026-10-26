// func_80614644 (src/global/17B90.c): stage 4; typed behavior rebuilt and fdiff iterated. Exact field offsets, 2*float mul idiom, and zero-sub negation resolved. Remaining diff is FPR/GPR allocation and scheduling (input held f12/f0 vs target f14, mask -9 repeatedly rematerialized rather than target t1), with candidate still three instructions longer; tried corrected s16 offset E, signed flag clear, integer multiplier, and explicit zero subtraction.
typedef struct {
    void *unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    u8 pad10[4];
    f32 unk14;
    f32 unk18;
    u16 unk1C;
    s16 unk1E;
    s16 unk20;
    u8 pad22[2];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} P17c2MotionWindow;

typedef struct {
    void *unk0;
    void *unk4;
    u8 pad8[0x70];
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    s32 unk84;
} P17c2MotionCore;

typedef struct {
    u8 pad0[4];
    P17c2MotionCore *unk4;
} P17c2MotionOwner;

void func_80614644(P17c2MotionOwner *arg0, P17c2MotionWindow *arg1, f32 arg2) {
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa1;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_t2;
    void *var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    u16 temp_v1;
    P17c2MotionCore *temp_v0;

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
            arg1->unk8 = -temp_fa0;
        }
        if ((f64) arg1->unk8 < 1.0) {
            arg1->unk4 = var_fa1;
            arg1->unkC = arg1->unk1E;
            arg1->unkE = arg1->unk20;
            return;
        }
        arg1->unk1C = (u16) ((s16) arg1->unk1C & 0xFFF7);
        var_fa1 += (f32) ((arg1->unk20 - arg1->unk1E) - (s32) temp_fa0);
        if (arg1 == var_a0) {
            temp_v0->unk78 &= ~0x20;
        }
    }
    if (temp_v1 & 4) {
        if (temp_fv1 < var_fa1) {
            var_a3 = 1;
            var_fa1 = (2 * temp_fv1) - var_fa1;
        } else if (var_fa1 < temp_fv0) {
            var_a3 = 1;
            var_a2 = 1;
            var_fa1 = (2 * temp_fv0) - var_fa1;
        }
        if (var_a3 != 0) {
            arg1->unk24 = 0.0f - arg1->unk24;
            if (arg1->unk34 != 0.0f) {
                arg1->unk2C = 0.0f - arg1->unk2C;
                arg1->unk28 = 0.0f - arg1->unk28;
            }
            if (arg1 == var_a0) {
                temp_v0->unk78 &= ~4;
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
                    temp_v0->unk7C = temp_a0 - 1;
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
                    if (temp_ft4 != temp_fa0_2) temp_v0->unk78 = var_v1 & ~8;
                } else if (temp_fa0_2 < var_fa1) {
                    if ((temp_ft4 < temp_fa0_2) && (var_a2 == 0)) temp_v0->unk78 = var_v1 & ~8;
                    else if ((temp_fa0_2 < temp_ft4) && (var_a2 != 0)) temp_v0->unk78 = var_v1 & ~8;
                } else if ((temp_fa0_2 < temp_ft4) && (var_a2 == 0)) temp_v0->unk78 = var_v1 & ~8;
                else if ((temp_ft4 < temp_fa0_2) && (var_a2 != 0)) temp_v0->unk78 = var_v1 & ~8;
            }
        }
    }
    arg1->unk4 = var_fa1;
    arg1->unkC = (s16) var_fa1;
    temp_v0_2 = arg1->unkC;
    arg1->unkE = temp_v0_2 + 1;
    arg1->unk8 = var_fa1 - (f32) temp_v0_2;
    if (temp_fv1 < (f32) arg1->unkE) {
        if (temp_v1 & 2) {
            arg1->unkE = (s16) temp_fv0;
            return;
        }
        arg1->unkE = temp_v0_2;
    }
}
