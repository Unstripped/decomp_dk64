// func_80719C00 (src/global/11BC10.c): Stage 3: behavioural projectile-motion reconstruction compiled; frame/register allocation remains.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} Ub9Motion6;

void func_80719C00(Ub2ActorView *arg0, s8 *arg1) {
    Ub9Motion6 *sp1C;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fv1;
    Ub9Motion6 *temp_v0;
    Ub9Motion6 *var_v1;

    var_v1 = (Ub9Motion6 *)arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(0x18);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = arg0->unk340;
        temp_v0->unk8 = 0.0f;
        temp_v0->unk4 = arg0->unk348;
        temp_v0->unkC = (f32)arg0->unk35C * 455.1111f;
        temp_v0->unk10 = ((arg0->unk35C % 3) * 0x64) - 0x64;
        temp_v0->unk14 = 375.0f;
        var_v1 = (Ub9Motion6 *)arg0->unk384;
    }
    arg0->unk344 = (f32)((f64)arg0->unk344 + 0.3);
    temp_fv0 = var_v1->unk14;
    if (temp_fv0 < 15.0f) {
        var_fv1 = temp_fv0;
    } else {
        var_fv1 = 15.0f;
    }
    var_v1->unk14 = temp_fv0 - var_fv1;
    temp_fv0_2 = var_v1->unk14;
    if (temp_fv0_2 > 255.0f) {
        arg0->unk36D = (u8)(u32)255.0f;
    } else {
        arg0->unk36D = (u8)(u32)temp_fv0_2;
    }
    var_v1->unkC += var_v1->unk10;
    var_v1->unk8 = (f32)((f64)var_v1->unk8 + 1.5);
    sp1C = var_v1;
    arg0->unk340 = (func_80612794((s16)(s32)var_v1->unkC) * var_v1->unk8) + var_v1->unk0;
    arg0->unk348 = (func_80612790((s16)(s32)var_v1->unkC) * var_v1->unk8) + var_v1->unk4;
    if (arg0->unk36D == 0) {
        *arg1 = 1;
    }
}
