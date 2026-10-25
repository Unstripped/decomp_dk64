// func_80719A0C (src/global/11BC10.c): Stage 3: behavioural m2c reconstruction compiled; stack frame/register allocation still differs.
typedef struct {
    f32 unk0;
    f32 unk4;
} Ub9Motion2;

void func_80719A0C(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp24;
    Ub9Motion2 *sp1C;
    f32 temp_fv1;
    f32 var_ft2;
    s32 temp_t0;
    Ub9Motion2 *temp_v0;
    Ub9Motion2 *var_v1;

    var_v1 = (Ub9Motion2 *)arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (f32)(((f64)arg0->unk360 / 0.36) * 2.5);
        temp_t0 = (D_8076A064 * 0x28) + (arg0->unk35C << 9);
        var_ft2 = (f32)temp_t0;
        if (temp_t0 < 0) {
            var_ft2 += 4294967296.0f;
        }
        temp_v0->unk4 = var_ft2;
        var_v1 = (Ub9Motion2 *)arg0->unk384;
    }
    var_v1->unk0 = (f32)((f64)var_v1->unk0 - 0.2);
    if ((f64)var_v1->unk0 < 0.8) {
        var_v1->unk0 = 0.8f;
    }
    sp1C = var_v1;
    sp24 = var_v1->unk0 * func_80612794((s16)(s32)var_v1->unk4);
    temp_fv1 = var_v1->unk0 * func_80612790((s16)(s32)var_v1->unk4);
    arg0->unk340 += sp24;
    arg0->unk348 += temp_fv1;
}
