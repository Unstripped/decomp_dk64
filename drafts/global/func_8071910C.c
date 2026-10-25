// func_8071910C (src/global/11BC10.c): stage 3: behavioral m2c-derived draft; cached state pointers still yield 0xF8 with s1 rather than target 0xD8/s0-only. Next step is direct arg0->unk384 accesses.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s32 unk14;
} Ub8RotationState;

s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
s32 func_806086CC(f32, f32, f32, s32, u32, s32, s32, s32, f32, s32);
extern s32 D_8072073C;
extern s32 D_807212B0;
extern s32 D_807212C8;

void func_8071910C(Ub2ActorView *arg0, s8 *arg1) {
    f32 sp98[4][4];
    f32 sp58[4][4];
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp44;
    f32 temp_fv0;
    f32 temp_fa1;
    f32 var_fv0;
    f32 var_ft2;
    f32 var_ft4;
    f64 var_ft1;
    Ub8RotationState *var_v1;
    Ub8RotationState *temp_v1;
    s32 var_a3;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        arg0->unk384 = func_80610FE8(0x1C);
        var_v1 = arg0->unk384;
        var_v1->unk0 = (f32)(((f64)(func_806119A0() / 10000U % 100U) / 25.0) + 5.0 + ((s32)arg0->unk35C >> 8) * 3.0);
        var_ft4 = (f32)(func_806119A0() / 10000U % 1000U);
        sp54 = (var_ft4 / 500.0f) + (arg0->unk35C & 0xFF);
        var_fv0 = (f32)(func_806119A0() / 10000U % 360U);
        sp50 = var_fv0;
        sp4C = func_80612D1C(var_fv0 * 0.017453292f) * sp54;
        temp_fv0 = func_80612D10(sp50 * 0.017453292f);
        var_v1->unk4 = sp4C;
        var_v1->unk8 = temp_fv0 * sp54;
        var_ft2 = (f32)(func_806119A0() % 36000U / 100U);
        var_v1->unkC = var_ft2;
        sp44 = arg0->unk344;
        if (collisionCheckGroundAtPoint(arg0->unk340, arg0->unk348, &sp44) != 0) var_v1->unk10 = sp44;
        else var_v1->unk10 = 0.0f;
        var_v1->unk14 = 0;
    }
    var_v1->unk0 = (f32)((f64)var_v1->unk0 - 0.63);
    temp_v1 = arg0->unk384;
    arg0->unk340 += temp_v1->unk4;
    arg0->unk348 += temp_v1->unk8;
    arg0->unk344 += temp_v1->unk0;
    temp_fa1 = arg0->unk344;
    if (temp_fa1 < temp_v1->unk10) {
        var_a3 = 0x56;
        if (*(void **)arg0->unk330 == &D_8072073C) var_a3 = 0x1B1;
        else if ((*(void **)arg0->unk330 == &D_807212C8) || (*(void **)arg0->unk330 == &D_807212B0)) var_a3 = 7;
        var_ft1 = (f64)arg0->unk36D;
        func_806086CC(arg0->unk340, temp_fa1, arg0->unk348, var_a3, (u32)(var_ft1 * 0.7), 0x96, 1, 0x4B, 0.3f, 0);
        temp_v1->unk0 = 5.0f;
        if (temp_v1->unk14 != 2) temp_v1->unk14++;
    }
    if (temp_v1->unk14 == 2) {
        if ((s32)arg0->unk36D >= 0xB) arg0->unk36D -= 0xA;
        else arg0->unk36D = 0;
    }
    temp_v1->unkC = (f32)((f64)temp_v1->unkC + 5.9);
    guScaleF(sp98, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp58, temp_v1->unkC, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp98, sp58, sp98);
    guMtxF2L(sp98, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *)arg0)[0x32C] = 2;
}
