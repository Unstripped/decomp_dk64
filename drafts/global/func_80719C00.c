// func_80719C00 (src/global/11BC10.c): from .scratch/Fx11BD/func_80719C00_best.c
void func_80719C00(TimedEffectActorView *arg0, s8 *arg1) {
    TimedEffectActorView *var_a2;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0x18);
        ((Fx11BDMotion6 *)arg0->unk384)->unk0 = arg0->unk340;
        ((Fx11BDMotion6 *)arg0->unk384)->unk8 = 0.0f;
        ((Fx11BDMotion6 *)arg0->unk384)->unk4 = arg0->unk348;
        ((Fx11BDMotion6 *)arg0->unk384)->unkC = (f32)arg0->unk35C * 455.1111f;
        ((Fx11BDMotion6 *)arg0->unk384)->unk10 = ((arg0->unk35C % 3) * 0x64) - 0x64;
        ((Fx11BDMotion6 *)arg0->unk384)->unk14 = 375.0f;
        arg0->unk384 = arg0->unk384; // FAKE: forces the target's end-of-if reload of unk384
    }
    var_a2 = arg0;
    var_a2->unk344 = (f32)((f64)var_a2->unk344 + 0.3);
    ((Fx11BDMotion6 *)var_a2->unk384)->unk14 = ((Fx11BDMotion6 *)var_a2->unk384)->unk14 - (((Fx11BDMotion6 *)var_a2->unk384)->unk14 < 15.0f ? ((Fx11BDMotion6 *)var_a2->unk384)->unk14 : 15.0f);
    if (((Fx11BDMotion6 *)var_a2->unk384)->unk14 > 255.0f) {
        var_a2->unk36D = (u8)(u32)255.0f;
    } else {
        var_a2->unk36D = (u8)(u32)((Fx11BDMotion6 *)var_a2->unk384)->unk14;
    }
    ((Fx11BDMotion6 *)var_a2->unk384)->unkC += ((Fx11BDMotion6 *)var_a2->unk384)->unk10;
    ((Fx11BDMotion6 *)var_a2->unk384)->unk8 = (f32)((f64)((Fx11BDMotion6 *)var_a2->unk384)->unk8 + 1.5);
    var_a2->unk340 = (func_80612794((s16)(s32)((Fx11BDMotion6 *)var_a2->unk384)->unkC) * ((Fx11BDMotion6 *)var_a2->unk384)->unk8) + ((Fx11BDMotion6 *)var_a2->unk384)->unk0;
    var_a2->unk348 = (func_80612790((s16)(s32)((Fx11BDMotion6 *)var_a2->unk384)->unkC) * ((Fx11BDMotion6 *)var_a2->unk384)->unk8) + ((Fx11BDMotion6 *)var_a2->unk384)->unk4;
    if (var_a2->unk36D == 0) {
        *arg1 = 1;
    }
}
