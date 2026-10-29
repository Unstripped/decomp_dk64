// func_8071F444 (src/global/11BC10.c): Fx11BI copy C (agent stopped: subagent credits ran out), deadsweep score full=29 vs expected; earlier note: stage 4: target 0x20 frame and callee-saved set retained; state-init/FP scheduling differs
void func_8071F444(TimedEffectActorView *arg0, s8 *arg1) {
    TimedMotionState *var_s0;

    if (arg0->unk384 == NULL) {
        if (D_8076A064 & 1) {
            arg0->unk360 = arg0->unk360 * -1.0f;
        }
        arg0->unk384 = func_80610FE8(8);
        var_s0 = (TimedMotionState *)arg0->unk384;
        var_s0->unk4 = 0.0f;
        var_s0->unk0 = (f32)(((randomNonNegative() >> 0xF) % 20) + 5);
        var_s0->unkC = 0.0f;
        var_s0->unk8 = (f32)(((randomNonNegative() >> 0xF) % 100) + 0xA);
    }
    var_s0 = (TimedMotionState *)arg0->unk384;
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((1.0 + (f64)func_80612794((s16)var_s0->unk4)) * (f64)(f32)(1.0 + ((f64)var_s0->unk0 * 0.4))));
    arg0->unk340 = arg0->unk340 + (func_80612794((s16)var_s0->unkC) * (f32)((f64)var_s0->unk8 * 0.5));
    if (*(u8 *)((u8 *)arg0 + 0x350) == 0) {
        *(s16 *)((u8 *)arg0 + 0x34E) = (s16)(s32)(((f64)func_80612794((s16)var_s0->unkC) * 2.5) + 2.5);
    }
    var_s0->unk4 = var_s0->unk4 + 100.0f;
    var_s0->unkC = var_s0->unkC + 50.0f;
    if (arg0->unk344 > 960.0f) {
        *arg1 = 1;
    }
}
