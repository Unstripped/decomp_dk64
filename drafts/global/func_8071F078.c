// func_8071F078 (src/global/11BC10.c): Fx11BI copy C (agent stopped: subagent credits ran out), deadsweep score full=23 vs expected; earlier note: stage 3: m2c behavior recovered; state typing/frame integration remains
void func_8071F078(TimedEffectActorView *arg0, s8 *arg1) {
    TimedMotionState *var_v1;
    TimedMotionState *temp_v0;

    var_v1 = (TimedMotionState *)arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = (TimedMotionState *)func_80610FE8(8);
        arg0->unk384 = temp_v0;
        var_v1 = (TimedMotionState *)arg0->unk384;
        var_v1->unk0 = (f32)(((f64)((randomNonNegative() >> 0xF) % 100) / 10.0) + 2.0);
        var_v1->unk4 = (f32)(-8.0 - ((f64)((randomNonNegative() >> 0xF) % 100) / 70.0));
        arg0->unk35C = (arg0->unk35C + (s16)((randomNonNegative() >> 0xF) % 800)) - 0x190;
        arg0->unk35C = arg0->unk35C % 4095;
    }
    var_v1 = (TimedMotionState *)arg0->unk384;
    arg0->unk340 = arg0->unk340 + (var_v1->unk0 * func_80612794(*(s16 *)((u8 *)arg0 + 0x35E)));
    arg0->unk348 = arg0->unk348 + (var_v1->unk0 * func_80612790(*(s16 *)((u8 *)arg0 + 0x35E)));
    arg0->unk344 = arg0->unk344 + var_v1->unk4;
}
