// func_8071EEE0 (src/global/11BC10.c): Fx11BI copy C (agent stopped: subagent credits ran out), deadsweep score full=33 vs expected; earlier note: stage 4: frame and state arithmetic match; matrix-call state spill/register allocation differs
void matrixMakeRotationZ(f32 (*arg0)[4], f32 arg1);

void func_8071EEE0(TimedEffectActorView *arg0, s8 *arg1) {
    TimedMotionState *var_v1;
    TimedMotionState *temp_v0;
    f32 sp6C[4][4];
    f32 sp2C[4][4];
    f32 temp_fv0;

    var_v1 = (TimedMotionState *)arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = (TimedMotionState *)func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0.01f;
        temp_v0->unk8 = 0.0f;
        temp_v0->unk4 = arg0->unk360;
        var_v1 = (TimedMotionState *)arg0->unk384;
    }
    temp_fv0 = var_v1->unk0;
    var_v1->unk8 = var_v1->unk8 + 5.0f;
    var_v1->unk0 = (f32)(((f64)(var_v1->unk4 - temp_fv0) * 0.1) + (f64)temp_fv0);
    guScaleF(sp6C, arg0->unk360, arg0->unk364, 0.0f);
    matrixMakeRotationZ(sp2C, var_v1->unk8);
    guMtxCatF(sp6C, sp2C, sp6C);
    guMtxF2L(sp6C, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->pad0[0x32C] = 2;
}
