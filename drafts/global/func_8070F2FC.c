// func_8070F2FC (src/global/1135F0.c): Stage 1 macro draft: correct three-command gSPTextureRectangle form reaches target 0x58 frame and block order, but differs from first floating-point allocation and has an extra arg2 sign-extension.
typedef struct R1135bTexture {
    s32 image;
    u8 pad4[4];
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    s16 unk10;
    s16 unk12;
} R1135bTexture;

extern R1135bTexture *D_807550D0;

void func_8070F2FC(Gfx **arg0, s16 arg1, s16 arg2) {
    Gfx *sp20;
    s32 sp4;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_t5;
    s16 temp_t6;
    s16 var_t2;
    s16 var_t3;
    s16 temp_t0;
    s16 temp_t1;
    s32 temp_ft3;
    s32 temp_ft3_2;
    s32 var_a0;
    s32 var_v1;
    Gfx *temp_t5_2;
    Gfx *temp_v0;
    Gfx *temp_v0_2;

    temp_v0 = *arg0;
    if (D_807550D0 != NULL) {
        temp_fv0 = (f32)arg1 * 0.25f;
        temp_t5 = D_807550D0->unkA;
        temp_ft3 = (s32)temp_fv0;
        temp_fa0 = (f32)temp_ft3;
        temp_t6 = D_807550D0->unkC;
        sp4 = (s32)temp_t6;
        temp_fv1 = (f32)arg2 * 0.25f;
        var_v1 = (s32)(((f32)D_807550D0->unk10 - (temp_fv0 - temp_fa0)) * 32.0f);
        temp_ft3_2 = (s32)temp_fv1;
        temp_fa1 = (f32)temp_ft3_2;
        var_a0 = (s32)(((f32)D_807550D0->unk12 - (temp_fv1 - temp_fa1)) * 32.0f);
        temp_t0 = (s16)(s32)((temp_fa0 + ((f32)temp_t5 * (1024.0f / (f32)D_807FD9D0))) * 4.0f);
        temp_t1 = (s16)(s32)((temp_fa1 + ((f32)temp_t6 * (1024.0f / (f32)D_807FD9D2))) * 4.0f);
        if (D_807FD9D4 != 0) {
            var_v1 = (var_v1 + (temp_t5 << 5)) - 0x20;
            var_t2 = -D_807FD9D0;
        } else {
            var_t2 = D_807FD9D0;
        }
        temp_t5_2 = temp_v0 + 1;
        if (D_807FD9D5 != 0) {
            var_a0 = (var_a0 + (sp4 << 5)) - 0x20;
            var_t3 = -D_807FD9D2;
        } else {
            var_t3 = D_807FD9D2;
        }
        gSPTextureRectangle(temp_v0++, arg1 * 4, arg2 * 4, temp_t0, temp_t1,
                            G_TX_RENDERTILE, var_v1, var_a0, var_t2, var_t3);
        temp_v0_2 = temp_t5_2 + 2;
        sp20 = temp_v0_2;
        *arg0 = sp20;
    }
}
