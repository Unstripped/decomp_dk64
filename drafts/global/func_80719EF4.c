// func_80719EF4 (src/global/11BC10.c): Stage 3: behavioural m2c reconstruction compiled; stack frame/register allocation still differs.
typedef struct {
    f32 unk0;
    f32 unk4;
} Ub9Motion2;

void func_80719EF4(Ub2ActorView *arg0, s8 *arg1) {
    f32 sp1C;
    Ub9Motion2 *temp_v0;
    Ub9Motion2 *temp_v1;
    Ub9Motion2 *temp_v1_2;
    Ub9Motion2 *var_v1;
    f32 temp_fv1;

    var_v1 = (Ub9Motion2 *)arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 3.2f;
        ((Ub9Motion2 *)arg0->unk384)->unk4 = (f32)arg0->unk35C;
        var_v1 = (Ub9Motion2 *)arg0->unk384;
    }
    var_v1->unk0 = (f32)((f64)var_v1->unk0 - 0.2);
    temp_v1 = (Ub9Motion2 *)arg0->unk384;
    if ((f64)temp_v1->unk0 < 0.8) {
        temp_v1->unk0 = 0.8f;
    }
    temp_v1_2 = (Ub9Motion2 *)arg0->unk384;
    sp1C = temp_v1_2->unk0 * func_80612D1C(((Ub9Motion2 *)arg0->unk384)->unk4 * 0.017453292f);
    temp_fv1 = ((Ub9Motion2 *)arg0->unk384)->unk0 * func_80612D10(temp_v1_2->unk4 * 0.017453292f);
    arg0->unk340 += sp1C;
    arg0->unk344 += 1.0f;
    arg0->unk348 += temp_fv1;
}
