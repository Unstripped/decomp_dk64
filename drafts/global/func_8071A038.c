// func_8071A038 (src/global/11BC10.c): Stage 3: behavioural matrix reconstruction compiled; frame/register allocation remains.
void func_8071A038(Ub2ActorView *arg0, s8 *arg1) {
    f32 sp78[4][4];
    f32 sp38[4][4];
    f32 sp34;
    f32 sp24;
    f32 sp20;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 var_fv1;
    u8 *temp_v0;

    temp_fv0 = (f32)((*((s16 *)((u8 *)arg0 + 0x34E)) * 2) + *((u8 *)arg0 + 0x351));
    temp_v0 = (u8 *)(s32)arg0->unk35C;
    if (temp_fv0 < 28.0f) {
        sp34 = temp_fv0;
    } else {
        sp34 = 56.0f - temp_fv0;
    }
    if (*temp_v0 != 0) {
        arg0->unk340 -= 12.0f;
        *temp_v0 -= 1;
    }
    temp_fa0 = (f32)(((f64)temp_fv0 / 56.0) * 6.2831854820251465);
    sp20 = temp_fa0;
    if (func_80612D1C(temp_fa0) > 0.0f) {
        var_fv1 = func_80612D1C(temp_fa0);
    } else {
        var_fv1 = -func_80612D1C(temp_fa0);
    }
    sp24 = var_fv1;
    guScaleF(sp78, arg0->unk360, arg0->unk364, 0.0f);
    guTranslateF(sp38, (f32)((f64)arg0->unk340 + ((f64)sp34 * 0.5)), arg0->unk344 - (sp24 * 15.0f), arg0->unk348);
    guMtxCatF(sp78, sp38, sp78);
    guMtxF2L(sp78, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *)arg0)[0x32C] = 3;
}
