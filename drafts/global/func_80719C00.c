// func_80719C00 (src/global/11BC10.c): stage 3: 188 of 189 insns; frame and stack homes match; remaining diff is the f-register allocation ring in the malloc-init region (0.0f constant and unk348 load swap f6/f8) plus one interleaved store; six declaration orders tried
void func_80719C00(TimedEffectActorView *arg0, s8 *arg1) {
    f32 temp_fv0;
    f32 var_fv1;
    Fx11BDMotion6 *var_v0;
    Fx11BDMotion6 *var_v1;
    TimedEffectActorView *var_a2;

    var_v1 = (Fx11BDMotion6 *)(var_a2 = arg0)->unk384;
    if (var_v1 == NULL) {
        var_v0 = func_80610FE8(0x18);
        arg0->unk384 = var_v0;
        var_v0->unk0 = arg0->unk340;
        var_v0->unk8 = 0.0f;
        var_v0->unk4 = arg0->unk348;
        var_v0->unkC = (f32)arg0->unk35C * 455.1111f;
        var_v0->unk10 = ((arg0->unk35C % 3) * 0x64) - 0x64;
        var_v0->unk14 = 375.0f;
        var_v1 = (Fx11BDMotion6 *)arg0->unk384;
    }
    var_v0 = var_v1;
    var_a2->unk344 = (f32)((f64)var_a2->unk344 + 0.3);
    temp_fv0 = var_v1->unk14;
    if (temp_fv0 < 15.0f) {
        var_fv1 = temp_fv0;
    } else {
        var_fv1 = 15.0f;
    }
    var_v0->unk14 = temp_fv0 - var_fv1;
    temp_fv0 = var_v0->unk14;
    var_fv1 = 255.0f;
    if (temp_fv0 > var_fv1) {
        var_a2->unk36D = (u8)(u32)var_fv1;
    } else {
        var_a2->unk36D = (u8)(u32)temp_fv0;
    }
    var_v1 = var_v0;
    var_v1->unkC += var_v1->unk10;
    var_v0->unk8 = (f32)((f64)var_v0->unk8 + 1.5);
    var_a2->unk340 = (func_80612794((s16)(s32)var_v1->unkC) * var_v0->unk8) + var_v0->unk0;
    var_a2->unk348 = (func_80612790((s16)(s32)var_v1->unkC) * var_v1->unk8) + var_v0->unk4;
    if (var_a2->unk36D == 0) {
        *arg1 = 1;
    }
}
