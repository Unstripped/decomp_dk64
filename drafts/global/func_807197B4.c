// func_807197B4 (src/global/11BC10.c): Stage 3: behavioural matrix/scale reconstruction compiled; frame/register allocation remains.
typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
} Ub9Motion3;

void func_807197B4(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp78[4][4];
    f32 sp34;
    f32 sp2C;
    f32 temp_fv0;
    f64 temp_ft3;
    Ub9Motion3 *temp_v0;
    Ub9Motion3 *temp_v1;
    Ub9Motion3 *temp_v1_2;
    Ub9Motion3 *temp_v1_3;
    Ub9Motion3 *var_v1;
    u8 temp_v0_2;

    var_v1 = (Ub9Motion3 *)arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0;
        ((Ub9Motion3 *)arg0->unk384)->unk4 = arg0->unk360;
        ((Ub9Motion3 *)arg0->unk384)->unk8 = arg0->unk364;
        var_v1 = (Ub9Motion3 *)arg0->unk384;
    }
    var_v1->unk4 = (f32)((f64)var_v1->unk4 + 0.0015);
    temp_v1 = (Ub9Motion3 *)arg0->unk384;
    temp_v1->unk8 = (f32)((f64)temp_v1->unk8 + 0.0015);
    sp2C = (f32)((f64)func_80612D1C((f32)(arg0->unk35C * 2)) * 0.2);
    temp_fv0 = func_80612D10((f32)(arg0->unk35C * 2));
    temp_v1_2 = (Ub9Motion3 *)arg0->unk384;
    arg0->unk340 -= sp2C;
    arg0->unk344 = (f32)((f64)arg0->unk344 + 0.12);
    arg0->unk348 -= (f32)((f64)temp_fv0 * 0.2);
    arg0->unk360 = temp_v1_2->unk4;
    arg0->unk364 = temp_v1_2->unk8;
    sp34 = func_80612D1C((f32)((f64)temp_v1_2->unk0 * 0.17));
    temp_v1_3 = (Ub9Motion3 *)arg0->unk384;
    temp_ft3 = 1.0 + ((f64)func_80612D1C((f32)((f64)temp_v1_3->unk0 * 0.2267)) * 0.15);
    arg0->unk360 = (f32)((f64)arg0->unk360 * (1.0 + ((f64)sp34 * 0.15)));
    arg0->unk364 = (f32)((f64)arg0->unk364 * temp_ft3);
    temp_v1_3->unk0 += 1;
    if ((*((s32 *)((u8 *)arg0 + 0x354)) - *((s32 *)((u8 *)arg0 + 0x358))) < 0xA) {
        temp_v0_2 = arg0->unk36D;
        if ((s32)temp_v0_2 >= 0x16) {
            arg0->unk36D = temp_v0_2 - 0x14;
        } else {
            arg0->unk36D = 0;
        }
    }
    guScaleF(sp78, arg0->unk360, arg0->unk364, 0.0f);
    guMtxF2L(sp78, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *)arg0)[0x32C] = 2;
}
