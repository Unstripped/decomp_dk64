// func_80705F5C (src/global/109660.c): stage 3 candidate; behavior reconstructed, frame and saved-register allocation differ
typedef struct { u8 unk0[0x2CA]; s16 unk2CA; } R1F109660aPlayerView;
extern f32 D_80754CE8;
extern u8 D_2000100;
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *func_806FEDB0(Gfx *, s32);
void func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

Gfx *func_80705F5C(Gfx *arg0, s16 arg1, s16 arg2, s32 arg3) {
    s16 sp76;
    f32 sp6C, sp68, sp60, sp5C, sp58, var_fv1;
    f64 temp_fv0, var_fv0;
    s32 temp_v0, var_v1;
    Gfx *temp_v0_2;
    Gfx *var_s0 = arg0;

    temp_v0 = arg3 & 0xFF;
    var_v1 = 0xFF;
    if (temp_v0 == 1) {
        lightGetColor(&sp60, &sp5C, &sp58, *(s16 *)D_807FBB4C->unk12C);
        temp_fv0 = (1.0 - (f64)sp5C) / 0.7;
        if (temp_fv0 > 1.0) {
            var_fv1 = (f32)1.0;
        } else {
            var_fv1 = (f32)temp_fv0;
        }
        var_v1 = (u32)((f64)var_fv1 * 255.0) & 0xFF;
        goto block_11;
    }
    if (temp_v0 == 2) {
        var_fv0 = (f64)(f32)((f64)D_80754CE8 - 0.5);
        if (var_fv0 < 0.0) var_fv0 = 0.0f;
        var_fv1 = (f32)(var_fv0 * 512.0);
        if ((f64)var_fv1 > 255.0) var_fv1 = 255.0f;
        var_v1 = (u32)var_fv1 & 0xFF;
block_11:
        sp60 = var_fv1;
    }
    var_s0->words.w0 = 0xFA000000;
    var_s0->words.w1 = (var_v1 & 0xFF) | ~0xFF;
    var_s0++;
    sp76 = (s16)(s32)((f64)func_80612794(arg1) * 32767.0);
    func_80626F8C((f32)sp76, (f32)(s16)(s32)((f64)arg2 - (8.0 * (f64)((R1F109660aPlayerView *)D_807FC924)->unk2CA)), (f32)(s16)(s32)((f64)func_80612790(arg1) * 32767.0), &sp6C, &sp68, 0, 4.0f, 0);
    if ((sp6C > -320.0f) && (sp6C < 1600.0f) && (sp68 > -240.0f) && (sp68 < 1200.0f)) {
        temp_v0_2 = func_806FEDB0(var_s0, 0);
        temp_v0_2->words.w0 = 0xE200001C;
        temp_v0_2->words.w1 = 0x504240;
        (temp_v0_2 + 1)->words.w0 = 0xDA380007;
        (temp_v0_2 + 1)->words.w1 = (u32)&D_2000100;
        var_s0 = func_8068C5A8(temp_v0_2 + 2, 0x35, 3, 1, 0x40, 0x40, (s32)sp6C, (s32)sp68, 4.0f, 4.0f, 0, 0.0f);
    }
    return var_s0;
}
