// func_8071F758 (src/global/11BC10.c): Fx11BI copy C (agent stopped: subagent credits ran out), deadsweep score full=34 vs expected; earlier note: stage 5: behavior and matrix sequence reached; target needs state in v1 then s0 and matrix bases sp+0x6C/sp+0x2C rather than current allocation.
void func_8071F758(TimedEffectActorView *arg0, s8 *arg1) {
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
    arg0->unk360 = (f32)(((f64)func_80612794((s16)(D_8076A064 * 50)) * 0.1) + (f64)var_v1->unk0);
    arg0->unk364 = (f32)(((f64)func_80612790((s16)(D_8076A064 * 25)) * 0.1) + (f64)var_v1->unk0);
    guScaleF(sp6C, arg0->unk360, arg0->unk364, 0.0f);
    matrixMakeRotationZ(sp2C, var_v1->unk8);
    guMtxCatF(sp6C, sp2C, sp6C);
    guMtxF2L(sp6C, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->pad0[0x32C] = 2;
}
