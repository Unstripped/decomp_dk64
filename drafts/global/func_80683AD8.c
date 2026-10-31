// func_80683AD8 (src/global/80150.c): stage 5: frame 0x108 + GBI macros (SetCombineMode DECALRGBA / LERP TEXEL0*PRIM alpha) + .rodata match; diff ~100 lines is int-temp rotation (t-reg numbering from 2nd renderRotatedSprite call: expected mfc1 t6 + sw in jal delay, ours v1 spX) and block 2 float colours (spF8 f2/var f12 vs ours f12/f2); f4-style empty-arm if fixes block 1
extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern s16 D_80744490;
extern s16 D_80744494;
extern u32 D_8076A064;

Gfx *renderRotatedSprite(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, s32);
u32 textGetFontHeight(s32);

Gfx *func_80683AD8(Gfx *arg0, Actor *arg1) {
    u8 padF8[0xC];
    f32 spF8;
    s32 pad244;
    f32 spF0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_v0;
    TagBarrelDataN3 *temp_s1;
    s32 spX;
    u8 pad70[0x38];
    s32 sp6C;
    s32 sp44;

    temp_s1 = (TagBarrelDataN3 *)arg1->unk174;
    spF0 = (f32)((f64)(D_80744494 - 0x1E) * 4.0);
    if (arg1->unk154 != 1) {
        return arg0;
    }
    gSPDisplayList(arg0++, &D_1000118);
    gDPSetCombineMode(arg0++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gSPMatrix(arg0++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(arg0++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    sp44 = (s16)(s32)spF0;
    arg0 = renderRotatedSprite(arg0, (((u32)(D_8076A064 >> 1) % 12) + 0x83) & 0xFFFF, 0, 2, 0x20, 0x10, 0xA0, sp44, 5.0f, 5.0f, 0, 0.0f);
    arg0 = renderRotatedSprite(arg0, (((u32)(D_8076A064 >> 1) % 12) + 0x83) & 0xFFFF, 0, 2, 0x20, 0x10, spX = (s32)((f64)(D_80744490 - 0x28) * 4.0), sp44, 5.0f, 5.0f, 0xB4, 0.0f); // FAKE: spX keeps arg 7 in an int temp (no swc1 merge)
    spF8 = (f32)(u32)temp_s1->unk4 * 0.05f;
    sp6C = tagBarrelIsKongUnlocked((ActorGroup5 *)temp_s1, temp_s1->unk6);
    spF0 -= (f32) textGetFontHeight(1) * 1.2f;
    gDPSetCombineLERP(arg0++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    if (sp6C != 0) {
        temp_fv0 = 1.0f - spF8;
        temp_fv1 = temp_fv0 * 0.5f;
        var_fa0 = temp_fv1;
        if (temp_s1->unk20 >= 0) { // FAKE: empty arm flips the branch polarity/float reg colouring
        } else {
            var_fa0 = 1.0f - temp_fv1;
        }
        temp_fv1_2 = 2.0f * temp_fv0;
        var_fa0 *= (f32)D_80744490 * 4.0f;
        if (temp_fv1_2 < 1.0f) {
            var_fv0 = 0.0f;
        } else {
            temp_fv0_2 = temp_fv1_2 - 1.0f;
            if (temp_fv0_2 > 1.0f) {
                var_fv1 = 1.0f;
            } else {
                var_fv1 = temp_fv0_2;
            }
            var_fv0 = var_fv1;
        }
        var_fv0 *= 255.0f;
        gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, (u32)var_fv0);
        arg0 = hudDrawScaledText(arg0, (s16)(s32)var_fa0, (s16)(s32)spF0, 0.6f, sp6C);
    }
    if (temp_s1->unk4 != 0) {
        temp_v0 = tagBarrelIsKongUnlocked((ActorGroup5 *)temp_s1, temp_s1->unk7);
        if (temp_v0 != 0) {
            temp_fv0_3 = 0.5f * spF8;
            var_fa0_2 = temp_fv0_3;
            if (temp_s1->unk20 > 0) {
                var_fa0_2 = 1.0f - temp_fv0_3;
            }
            temp_fv0_4 = 2.0f * spF8;
            var_fa0_2 *= (f32)D_80744490 * 4.0f;
            if (temp_fv0_4 < 1.0f) {
                var_fv0_2 = 0.0f;
            } else {
                temp_fa1 = temp_fv0_4 - 1.0f;
                if (temp_fa1 > 1.0f) {
                    var_fv1_2 = 1.0f;
                } else {
                    var_fv1_2 = temp_fa1;
                }
                var_fv0_2 = var_fv1_2;
            }
            var_fv0_2 *= 255.0f;
            gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, (u32)var_fv0_2);
            arg0 = hudDrawScaledText(arg0, (s16)(s32)var_fa0_2, (s16)(s32)spF0, 0.6f, temp_v0);
        }
    }
    return arg0;
}
