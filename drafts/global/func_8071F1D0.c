// func_8071F1D0 (src/global/11BC10.c): Fx11BI copy C (agent stopped: subagent credits ran out), deadsweep score full=48 vs expected; earlier note: stage 3: m2c behavior recovered; typed attempt had 0x38 frame versus target 0x28
extern s8 D_8075567C;

void func_8071F1D0(TimedEffectActorView *arg0, s8 *arg1) {
    TimedMotionState *var_v1;
    TimedMotionState *temp_v0;
    f32 temp_ft5;

    var_v1 = (TimedMotionState *)arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = (TimedMotionState *)func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = arg0->unk340;
        temp_v0->unk4 = arg0->unk348;
        temp_v0->unk8 = (f32)D_8075567C;
        D_8075567C = -D_8075567C;
        var_v1 = (TimedMotionState *)arg0->unk384;
    }
    var_v1 = (TimedMotionState *)arg0->unk384;
    arg0->unk340 = (func_80612794(*(s16 *)((u8 *)arg0 + 0x35E)) * 14.0f) + var_v1->unk0;
    temp_ft5 = (func_80612790(*(s16 *)((u8 *)arg0 + 0x35E)) * 14.0f) + var_v1->unk4;
    arg0->unk344 = arg0->unk344 + 0.5f;
    arg0->unk348 = temp_ft5;
    if (arg0->unk36D < 5) {
        *arg1 = 1;
    } else {
        arg0->unk36D = arg0->unk36D - 4;
    }
    arg0->unk35C = arg0->unk35C + (s32)((f64)var_v1->unk8 * 200.0);
}
