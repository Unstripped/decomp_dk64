// controllerApplyMotionWindow (src/global/17B90.c): stage 4; leaf frame 0; score down to 245; zero-sub resolved via if (arg1->unk34 != 0) separate int zero web; remaining diff is t1 vs t2 regalloc between -9 and var_v1 & ~1
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
} MotionWindow;

typedef struct {
    MotionWindow *unk0;
    MotionWindow *unk4;
    void *unk8;
    void *unkC;
    f32 unk10;
    u8 pad14[0x14];
    s16 unk28;
    u8 pad2A[2];
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    u8 pad32[0xE];
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    u8 pad5C[0x1C];
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    s32 unk84;
} MotionCore;

typedef struct {
    u8 pad0[4];
    MotionCore *unk4;
} MotionOwner;

typedef struct { u8 pad[0x14]; f32 a; f32 b; } AnimScaleState;
typedef struct { u8 pad[4]; void *holder; } AnimScaleController;

void controllerApplyMotionWindow(AnimScaleController *arg0_raw, AnimScaleState *arg1_raw, f32 arg2) {
    MotionOwner *arg0 = (MotionOwner *)arg0_raw;
    MotionWindow *arg1 = (MotionWindow *)arg1_raw;
    s8 new_var;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_t2;
    void *var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    u16 temp_v1;
    MotionCore *temp_v0;

    temp_v0 = arg0->unk4;
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
        temp_fa0 = arg2 - (f32) arg1->unk1E;
        if (temp_fa0 > 0) {
            arg1->unk8 = temp_fa0;
        } else {
            arg1->unk8 = -temp_fa0;
        }
        if ((f64) arg1->unk8 < 1.0) {
            arg1->unk4 = arg2;
            arg1->unkC = arg1->unk1E;
            arg1->unkE = arg1->unk20;
            return;
        }
        arg2 += (f32) ((arg1->unk20 - arg1->unk1E) - (s32) temp_fa0);
        new_var = 0xFFF7;
        arg1->unk1C = (u16) ((s16) arg1->unk1C & new_var);
        if (arg1 == var_a0) {
            temp_v0->unk78 &= ~0x20;
        }
    }
    new_var = ~8;
    if (temp_v1 & 4) {
        if (temp_fv1 < arg2) {
            var_a3 = 1;
            arg2 = (2 * temp_fv1) - arg2;
        } else if (arg2 < temp_fv0) {
            var_a3 = 1;
            var_a2 = 1;
            arg2 = (2 * temp_fv0) - arg2;
        }
        if (var_a3 != 0) {
            arg1->unk24 = 0.0f - arg1->unk24;
            if (arg1->unk34 != 0) {
                arg1->unk2C = 0.0f - arg1->unk2C;
                arg1->unk28 = 0.0f - arg1->unk28;
            }
            if (arg1 == var_a0) {
                temp_v0->unk78 &= ~4;
            }
        }
    } else if (temp_v1 & 2) {
        if (((f64) temp_fv1 + 1.0) <= (f64) arg2) {
            var_a2 = 1;
            arg2 -= (1.0f + temp_fv1) - temp_fv0;
        } else if (arg2 < temp_fv0) {
            var_a2 = 1;
            arg2 += (1.0f + temp_fv1) - temp_fv0;
        }
    } else if (temp_fv1 <= arg2) {
        arg2 = temp_fv1;
        if (arg1->unk24 >= 0.0f) {
            arg1->unk24 = 0.0f;
            arg1->unk34 = 0.0f;
            var_a2 = 1;
        }
    } else if (arg2 < temp_fv0) {
        arg2 = temp_fv0;
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
                    var_v1 = (temp_v0->unk78 &= ~2);
                }
            }
            if (var_v1 & 8) {
                temp_fa0_2 = temp_v0->unk80;
                temp_ft4 = arg1->unk4;
                if (arg2 == temp_fa0_2) {
                    if (temp_ft4 != temp_fa0_2) temp_v0->unk78 = var_v1 & new_var;
                } else if (temp_fa0_2 < arg2) {
                    if ((temp_ft4 < temp_fa0_2) && (var_a2 == 0)) temp_v0->unk78 = var_v1 & new_var;
                    else if ((temp_fa0_2 < temp_ft4) && (var_a2 != 0)) temp_v0->unk78 = var_v1 & new_var;
                } else if ((temp_fa0_2 < temp_ft4) && (var_a2 == 0)) temp_v0->unk78 = var_v1 & new_var;
                else if ((temp_fa0_2 < temp_ft4) && (var_a2 != 0)) temp_v0->unk78 = var_v1 & new_var;
            }
        }
    }
    arg1->unk4 = arg2;
    arg1->unkC = (s16) arg2;
    temp_v0_2 = arg1->unkC;
    arg1->unkE = temp_v0_2 + 1;
    arg1->unk8 = arg2 - (f32) temp_v0_2;
    if (temp_fv1 < (f32) arg1->unkE) {
        if (temp_v1 & 2) {
            arg1->unkE = (s16) temp_fv0;
            return;
        }
        arg1->unkE = temp_v0_2;
    }
    if (var_a3) {}
}
