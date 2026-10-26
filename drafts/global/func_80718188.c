// func_80718188 (src/global/11BC10.c): stage 4: target/draft frame 0x20 and $s0 save, 61/61 insns; branch-likely block order matches, but D_807502D0 is based in v0 target/a0 draft and FP temps differ.
// func_80718188 draft: behavior recovered; target requires different register lifetime and branch-likely shape.
extern s16 D_807502D0;

void func_80718188(TimedEffectActorView *arg0, s8 *arg1) {
    s16 *temp_v0;
    s16 *temp_v1;
    s16 *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(2);
        arg0->unk384 = temp_v0;
        *temp_v0 = 0;
        var_v1 = arg0->unk384;
    }
    arg0->unk344 = arg0->unk344 + (f32) *var_v1;
    *var_v1 -= 1;
    temp_v1 = arg0->unk384;
    if (*temp_v1 < D_807502D0) {
        *temp_v1 = D_807502D0;
    }
    if (arg0->unk344 < (f32) arg0->unk35C) {
        *arg1 = 1;
        func_80718124((f32) ((f64) arg0->unk360 * 1.5), arg0->unk340, arg0->unk35C, arg0->unk348);
    }
}
