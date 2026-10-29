// func_8071EB70 (src/global/11BC10.c): Fx11BI copy C (agent stopped: subagent credits ran out), deadsweep score full=63 vs expected; earlier note: stage 3: m2c behavior recovered; frame/type integration remains
extern s32 D_807FC924;

void func_8071EB70(TimedEffectActorView *arg0, s8 *arg1) {
    f32 *sp24;
    f32 sp1C;
    f32 *temp_v0;
    f32 *var_v1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fa1;
    f32 temp_fv0_2;
    f32 temp_fv1_2;
    f32 var_fa0;
    f32 var_ft2;
    u8 temp_t9;

    var_v1 = (f32 *)arg0->unk384;
    sp1C = (f32)((arg0->unk35C * 3) / 4);
    if (var_v1 == NULL) {
        temp_v0 = (f32 *)func_80610FE8(4);
        temp_t9 = arg0->unk36D;
        arg0->unk384 = temp_v0;
        var_ft2 = (f32)(u32)temp_t9;
        *temp_v0 = var_ft2;
        var_v1 = (f32 *)arg0->unk384;
    }
    temp_fv0 = *(f32 *)((u8 *)D_807FC924 + 0x224) - arg0->unk348;
    temp_fv1 = *(f32 *)((u8 *)D_807FC924 + 0x21C) - arg0->unk340;
    temp_fa1 = *(f32 *)((u8 *)D_807FC924 + 0x220) - arg0->unk344;
    sp24 = var_v1;
    temp_fv0_2 = sqrtf((temp_fv0 * temp_fv0) + ((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1)));
    if (temp_fv0_2 < sp1C) {
        arg0->unk36D = (u8)(u32)*sp24;
        return;
    }
    temp_fv1_2 = *sp24;
    var_fa0 = (f32)(s32)(temp_fv1_2 * ((temp_fv0_2 - sp1C) / ((f32)arg0->unk35C - sp1C)));
    if (temp_fv1_2 < var_fa0) {
        var_fa0 = (f32)(s32)temp_fv1_2;
    }
    arg0->unk36D = (u8)(u32)(temp_fv1_2 - var_fa0);
}
