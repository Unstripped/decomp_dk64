// func_8070F2FC (src/global/1135F0.c): Stage 1 compiled C draft; behavior is a three-command texture rectangle/tile display-list emitter. Closest diff retains block behavior but has no target frame because pointer-view reconstruction changes IDO regalloc.
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} R1135Gfx;

typedef struct {
    s32 unk0;
    u8 pad4[4];
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    s16 unk10;
    s16 unk12;
} R1135Texture;

extern R1135Texture *D_807550D0;
#define R1135_GFX(ptr) ((R1135Gfx *)(ptr))

void func_8070F2FC(Gfx **arg0, s16 arg1, s16 arg2) {
    u8 *sp20;
    s32 sp4;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_t5;
    s16 temp_t6;
    s16 var_t2;
    s16 var_t3;
    s32 temp_ft3;
    s32 temp_ft3_2;
    s32 var_a0;
    s32 var_v1;
    u8 *temp_t5_2;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (u8 *)*arg0;
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
        if (D_807FD9D4 != 0) {
            var_v1 = (var_v1 + (temp_t5 << 5)) - 0x20;
            var_t2 = D_807FD9D0 * -1;
        } else {
            var_t2 = D_807FD9D0;
        }
        temp_t5_2 = temp_v0 + 8;
        if (D_807FD9D5 != 0) {
            var_a0 = (var_a0 + (sp4 << 5)) - 0x20;
            var_t3 = D_807FD9D2 * -1;
        } else {
            var_t3 = D_807FD9D2;
        }
        R1135_GFX(temp_v0)->unk0 = (s32)((((s16)(s32)((temp_fa0 + ((f32)temp_t5 * (1024.0f / (f32)D_807FD9D0))) * 4.0f) & 0xFFF) << 0xC) | 0xE4000000 | ((s16)(s32)((temp_fa1 + ((f32)temp_t6 * (1024.0f / (f32)D_807FD9D2))) * 4.0f) & 0xFFF));
        R1135_GFX(temp_v0)->unk4 = (s32)((((temp_ft3 * 4) & 0xFFF) << 0xC) | ((temp_ft3_2 * 4) & 0xFFF));
        R1135_GFX(temp_v0)->unk8 = 0xE1000000;
        R1135_GFX(temp_t5_2)->unk4 = (s32)((var_v1 << 0x10) | (var_a0 & 0xFFFF));
        temp_v0_2 = temp_t5_2 + 8;
        sp20 = temp_v0_2;
        R1135_GFX(sp20)->unk0 = 0xF1000000;
        R1135_GFX(sp20)->unk4 = (s32)((var_t2 << 0x10) | (var_t3 & 0xFFFF));
        *arg0 = temp_v0_2 + 8;
    }
}
