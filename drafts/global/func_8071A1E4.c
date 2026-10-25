// func_8071A1E4 (src/global/11BC10.c): Stage 3: behavioural random-matrix reconstruction compiled; frame/register allocation remains.
typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
} Ub9Motion3;

void func_8071A1E4(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp8C[4][4];
    f32 sp4C[4][4];
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s16 sp46;
    s8 sp48;
    s8 sp49;
    s8 sp4A;
    s8 sp4B;
    s32 temp_t5;
    u8 temp_v1;
    Ub9Motion3 *var_v0;

    var_v0 = (Ub9Motion3 *)arg0->unk384;
    if (var_v0 == NULL) {
        sp48 = (s8)((u32)-(s32)(func_806119A0() / 10000U) % 30U);
        sp46 = (s16)((u32)(func_806119A0() / 10000U) % 180U);
        guRotateF(sp8C, (f32)sp48, 0.0f, 1.0f, 0.0f);
        temp_t5 = arg0->unk35C;
        sp4B = (s8)(temp_t5 >> 0x10);
        sp4A = (s8)(temp_t5 >> 8);
        sp49 = (s8)temp_t5;
        arg0->unk384 = func_80610FE8(0xC);
        guAlignF(sp4C, (f32)sp46, (f32)sp4B, (f32)sp4A, (f32)sp49);
        guMtxCatF(sp8C, sp4C, sp8C);
        guMtxXFMF(sp8C, 0.0f, 0.0f, -2.0f, &sp40, &sp3C, &sp38);
        ((Ub9Motion3 *)arg0->unk384)->unk0 = (f32)((f64)sp40 * 0.5);
        if (sp3C < 0.0f) {
            ((Ub9Motion3 *)arg0->unk384)->unk4 = (f32)((f64)-sp3C * 0.5);
        } else {
            ((Ub9Motion3 *)arg0->unk384)->unk4 = (f32)((f64)sp3C * 0.5);
        }
        ((Ub9Motion3 *)arg0->unk384)->unk8 = (f32)((f64)sp38 * 0.5);
        var_v0 = (Ub9Motion3 *)arg0->unk384;
    }
    arg0->unk340 += var_v0->unk0;
    arg0->unk344 += var_v0->unk4;
    arg0->unk348 += var_v0->unk8;
    if ((*((s32 *)((u8 *)arg0 + 0x354)) - *((s32 *)((u8 *)arg0 + 0x358))) < 0xA) {
        var_v0->unk4 = (f32)((f64)var_v0->unk4 - 0.1);
        temp_v1 = arg0->unk36D;
        if ((s32)temp_v1 >= 0x16) {
            arg0->unk36D = temp_v1 - 0x14;
            return;
        }
        arg0->unk36D = 0;
    }
}
