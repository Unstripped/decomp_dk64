// controllerStepMotionWindows (src/global/17B90.c): stage 4; frame 0x40 and save set s0/ra match; spill slots (0x3C,0x38,0x2C,0x28,0x20) and byte size 7792 match; local declaration order core,win0,win4,unk8,unkC,pos,rate,step and integer-0 ternary (step > 0); remaining diff is spill scheduling and regalloc
extern u32 D_80744478;
extern u8 D_80746B60;
void func_80613944();
void actorScriptExecute(void *);

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
void controllerApplyMotionWindow(AnimScaleController *, AnimScaleState *, f32);

void controllerStepMotionWindows(MotionOwner *arg0) {
    MotionCore *core;
    MotionWindow *win0;
    MotionWindow *win4;
    void *unk8;
    void *unkC;
    f32 pos;
    f32 rate;
    f32 step;

    core = arg0->unk4;
    win0 = core->unk0;
    win4 = core->unk4;
    unk8 = core->unk8;
    pos = win0->unk4;
    unkC = core->unkC;
    rate = 1.0f;
    if (core->unk30 & 1) {
        rate = (f32) ((f64) (u32) D_80744478 * 0.5);
    }
    core->unk30 &= ~1;
    if (D_80746B60 == 0) {
        core->unk30 |= (win0->unk1C & 1);
    }
    if (core->unk58 > 0.0f) {
        core->unk54 += rate;
        if (core->unk54 < core->unk58) {
            core->unk48 = core->unk4C + (((core->unk50 - core->unk4C) * core->unk54) / core->unk58);
        } else {
            core->unk58 = 0.0f;
            core->unk48 = core->unk50;
        }
    }
    step = core->unk48 * rate;
    if (win0->unk34 > 0.0f) {
        win0->unk30 += (step > 0) ? step : -step;
        if (win0->unk30 < win0->unk34) {
            win0->unk24 = win0->unk28 + (((win0->unk2C - win0->unk28) * win0->unk30) / win0->unk34);
        } else {
            win0->unk34 = 0.0f;
            win0->unk24 = win0->unk2C;
        }
    }
    if (win4->unk34 > 0.0f) {
        win4->unk30 += (step > 0) ? step : -step;
        if (win4->unk30 < win4->unk34) {
            win4->unk24 = win4->unk28 + (((win4->unk2C - win4->unk28) * win4->unk30) / win4->unk34);
        } else {
            win4->unk34 = 0.0f;
            win4->unk24 = win4->unk2C;
        }
    }
    if (*(s32 *)unk8 != 0) {
        core->unk40 += (step > 0) ? step : -step;
        if (core->unk40 < core->unk44) {
            core->unk10 = (core->unk44 - core->unk40) / core->unk44;
        } else {
            func_80613944(arg0, unk8);
            func_80613944(arg0, unkC);
            core->unk78 &= ~0x10;
        }
        pos += ((step * win0->unk24) / 2.0f) * (1.0f - core->unk10);
    } else {
        pos += step * win0->unk24;
    }
    controllerApplyMotionWindow((AnimScaleController *)arg0, (AnimScaleState *)win0, pos);
    if (win4->unk0 != NULL) {
        if (core->unk28 < core->unk2C) {
            core->unk28 += core->unk2E;
            if (core->unk28 > core->unk2C) {
                core->unk28 = core->unk2C;
            }
        } else if (core->unk28 > core->unk2C) {
            core->unk28 -= core->unk2E;
            if (core->unk28 < core->unk2C) {
                core->unk28 = core->unk2C;
            }
        }
        pos = win4->unk4 + win4->unk24;
        controllerApplyMotionWindow((AnimScaleController *)arg0, (AnimScaleState *)win4, pos);
        if ((win4->unk24 == 0.0f) && (win4->unk1C & 0x10)) {
            core->unk2C = 0;
            if (core->unk28 == 0) {
                func_80613944(arg0, win4);
            }
        }
    }
    actorScriptExecute(arg0);
}
