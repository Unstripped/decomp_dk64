// func_8070FA58 (src/global/114270.c): Baseline pursuit reconstruction; stack-slot layout and register allocation differ.
typedef struct M114aPlayerView {
    u8 unk0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    f32 unk21C;
    f32 unk220;
    f32 unk224;
    u8 unk228[0x9C];
    f32 unk2C4;
    s16 unk2C8;
} M114aPlayerView;

typedef struct M114aAngle {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    s16 unk20;
} M114aAngle;

extern void *D_807FC924;
extern s16 D_807FDA1E;
f32 func_80612794(s16);
f32 func_80612D1C(f32);
s16 func_806CC10C(s16, s16);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_8070FA58(M114aAngle *arg0) {
    f32 sp30;
    s16 sp26;
    f32 sp20;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 var_fa0;
    M114aPlayerView *player = (M114aPlayerView *)D_807FC924;

    temp_fv0 = player->unk218 - arg0->unk1C;
    temp_fv1 = player->unk210 - arg0->unk18;
    temp_fv1_2 = sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
    arg0->unk18 = player->unk210;
    arg0->unk1C = player->unk218;
    var_fa0 = player->unk2C4 - arg0->unk14;
    if (var_fa0 > 3.1415927f) {
        var_fa0 = 6.2831855f - var_fa0;
    }
    if (var_fa0 < -3.1415927f) {
        var_fa0 = -6.2831855f - var_fa0;
    }
    arg0->unk4 = (f32)((f64)arg0->unk4 + ((f64)(var_fa0 * 180.0f) - (0.3 * (f64)D_807FDA1E)));
    sp30 = temp_fv1_2;
    arg0->unk4 = (f32)(arg0->unk4 + (4.0f * temp_fv1_2 * func_80612D1C(var_fa0)));
    sp26 = mathAngleBetweenPoints2D(player->unk210, player->unk218, player->unk21C, player->unk224);
    temp_fv0_2 = player->unk218 - player->unk224;
    temp_fv1_3 = player->unk210 - player->unk21C;
    sp20 = sqrtf((temp_fv0_2 * temp_fv0_2) + (temp_fv1_3 * temp_fv1_3));
    arg0->unk4 = (f32)((f64)arg0->unk4 - (2.0 * (f64)sp20 * (f64)func_80612794(func_806CC10C(player->unk2C8, sp26))));
    arg0->unk14 = player->unk2C4;
}
