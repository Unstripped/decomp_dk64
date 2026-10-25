// func_807184F4 (src/global/11BC10.c): Stage 3: behavioral matrix/angle draft compiled; frame is 0xC8 vs target 0xB0 because six live temporary slots remain.
typedef struct {
    f32 unk0;
    f32 unk4;
} Ub3TwoFloats;

typedef struct {
    u8 pad0[0xAC];
    f32 unkAC;
} Ub3TargetView;

void func_807184F4(Ub2ActorView *arg0, s8 *arg1) {
    Ub2bMtxF sp70;
    Ub2bMtxF sp30;
    Ub3TwoFloats *temp_v0;
    Ub3TwoFloats *temp_v0_3;
    f32 var_ft2;
    u32 temp_lo;
    u8 temp_v1;
    Ub3TargetView *temp_v0_2;

    if (arg0->unk384 == NULL) {
        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0.0f;
        temp_lo = (u32) (func_806119A0() % 400U) / 100U;
        var_ft2 = (f32) temp_lo;
        if ((s32) temp_lo < 0) {
            var_ft2 += 4294967296.0f;
        }
        ((Ub3TwoFloats *) arg0->unk384)->unk4 = var_ft2;
    }
    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, ((Ub3TwoFloats *) arg0->unk384)->unk0, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp70, sp30, sp70);
    guRotateF(sp30, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    temp_v0_2 = arg0->unk338;
    if (temp_v0_2 != NULL) {
        arg0->unk344 = temp_v0_2->unkAC;
    }
    guTranslateF(sp30, arg0->unk340, arg0->unk344, arg0->unk348);
    guMtxCatF(sp70, sp30, sp70);
    guMtxF2L(sp70, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    if (arg0->unk35C != 0) {
        temp_v0_3 = arg0->unk384;
        temp_v0_3->unk0 += temp_v0_3->unk4;
        temp_v1 = arg0->unk36D;
        arg0->unk360 = (f32) ((f64) arg0->unk360 - 0.02);
        arg0->unk364 = (f32) ((f64) arg0->unk364 - 0.02);
        if ((s32) temp_v1 >= 0xA) {
            arg0->unk36D = (u8) (temp_v1 - 0xA);
        } else {
            arg0->unk36D = 0U;
        }
    }
    ((u8 *) arg0)[0x32C] = 3;
}
