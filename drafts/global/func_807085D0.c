// func_807085D0 (src/global/10D2D0.c): Stage 3 typed m2c draft; matching callee-saved set but frame remains 0x128 vs 0x100; direct Gfx field writes and m2c local order tried.
typedef struct R3F10D2D0_PlayerView {
    u8 pad0[0x2E0];
    u16 unk2E0;
    u8 unk2E2;
    u8 unk2E3;
    u8 unk2E4;
    u8 unk2E5;
} R3F10D2D0_PlayerView;

typedef struct R3F10D2D0_HudView {
    u8 pad0[0x2FB];
    s8 unk2FB;
    u8 unk2FC;
    u8 pad2FD[9];
} R3F10D2D0_HudView;

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern s32 D_8076A064;
extern s32 D_807FBB60;
f32 func_80612794(s16);
f32 func_80612D1C();
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
s32 func_80714464();
#define R3F10D2D0_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }
#define R3F10D2D0_FLAGS(player) (*(u16 *)&(player)->unk2E2)



Gfx *func_807085D0(Gfx *arg0, R3F10D2D0_HudView *arg1, void *arg2, R3F10D2D0_PlayerView *arg3) {
    f32 spE8;
    f32 spA4;
    f32 spA0;
    f32 sp94;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 var_ft1_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f64 temp_ft1;
    f64 var_ft1;
    s16 temp_s0_2;
    s16 var_s3;
    s32 temp_ft0;
    s32 temp_ft1_2;
    s32 temp_s0;
    s32 temp_v0_2;
    s32 var_t5;
    s32 var_v1;
    s8 temp_v0_3;
    s8 var_s4;
    u16 temp_t6;
    Gfx *temp_s2;
    Gfx *temp_s2_2;
    Gfx *temp_s2_3;
    Gfx *temp_s2_4;
    Gfx *temp_v0;
    Gfx *var_s2;

    temp_t6 = arg3->unk2E0;
    var_s4 = arg1->unk2FB;
    var_ft1 = (f64)temp_t6;
    if ((s32)temp_t6 < 0) {
        var_ft1 += 4294967296.0;
    }
    temp_s0 = ((arg1->unk2FC * 0x46) - 0x46) & 0xFF;
    temp_fs0 = (f32)(var_ft1 / 65535.0);
    if ((D_807FBB60 & 3) || (func_80714464() != 0)) {
        return arg0;
    }
    temp_s2 = arg0 + 1;
    arg0->words.w1 = (u32)&D_1000118;
    arg0->words.w0 = 0xDE000000;
    temp_s2_2 = temp_s2 + 1;
    temp_s2->words.w0 = 0xFC119623;
    temp_s2->words.w1 = 0xFF2FFFFF;
    temp_s2_3 = temp_s2_2 + 1;
    temp_s2_2->words.w0 = 0xE200001C;
    temp_s2_2->words.w1 = 0x504240;
    temp_s2_3->words.w0 = 0xDA380007;
    temp_s2_3->words.w1 = (u32)&D_20000C0;
    var_s2 = temp_s2_3 + 1;
    var_s3 = 0;
    if ((s32)arg1->unk2FC > 0) {
        var_ft1_2 = (f32)temp_s0;
        spA4 = temp_fs0 * 511.0f;
        if (temp_s0 < 0) {
            var_ft1_2 += 4294967296.0f;
        }
        spA0 = var_ft1_2;
        sp94 = (f32)(s16)(s32)((f64)temp_fs0 * 200.0);
        do {
            temp_s0_2 = (var_s3 << 0xA) + (D_8076A064 * 0xC8);
            spE8 = (f32)(((f64)func_80612794(temp_s0_2) * 0.3) + 3.0);
            temp_fs2 = (f32)(((f64)func_80612794((s16)(temp_s0_2 + 0x800)) * 0.3) + 3.0);
            temp_fs0_2 = (f32)((f64)func_80612794((s16)((temp_s0_2 >> 1) + 0x200)) * 10.0);
            temp_ft1 = (f64)func_80612794(temp_s0_2) * 0.5;
            temp_s2_4 = var_s2 + 1;
            var_s2->words.w0 = 0xE7000000;
            var_s2->words.w1 = 0;
            var_s2->words.w0 = 0xFA000000;
            var_fv0 = (spA4 > 80.0f) ? 80.0f : spA4;
            temp_s2_4->words.w1 = (s32)(((u32)var_fv0 & 0xFF) | ~0xFF);
            temp_fs1 = -temp_fs2;
            temp_ft0 = (s32)(sp94 + (f32)((temp_ft1 + 0.5) * 30.0));
            temp_ft1_2 = (s32)(((f32)((var_s3 * 0x8C) + 0x280) + temp_fs0_2) - spA0);
            temp_v0 = func_8068C5A8(temp_s2_4 + 1, 0x5D, 0, 2, 0x30, 0x2A, (s32)(s16)temp_ft1_2, (s32)(s16)temp_ft0, spE8, temp_fs1, 0, 0.0f);
            temp_v0->words.w0 = 0xE7000000;
            temp_v0->words.w1 = 0;
            temp_v0->words.w0 = 0xFA000000;
            var_s2 = temp_v0 + 2;
            var_fv0_2 = spA4;
            if (spA4 > 255.0f) {
                var_fv0_2 = 255.0f;
            }
            temp_v0->words.w1 = (s32)(((u32)var_fv0_2 & 0xFF) | ~0xFF);
            if (var_s4 > 0) {
                temp_v0_2 = var_s4 - 1;
                var_v1 = 3;
                if (temp_v0_2 < 3) {
                    var_v1 = temp_v0_2;
                }
                var_s2 = func_8068C5A8(var_s2, (var_v1 + 0x5A) & 0xFFFF, 0, 2, 0x30, 0x2A, (s32)(s16)temp_ft1_2, (s32)(s16)temp_ft0, spE8, temp_fs1, 0, 0.0f);
            }
            temp_v0_3 = var_s4 - 4;
            if (temp_v0_3 < 0) {
                var_s4 = 0;
            } else {
                var_s4 = temp_v0_3;
            }
            var_s3 += 1;
        } while (var_s3 < (s32)arg1->unk2FC);
    }
    var_s2->words.w0 = 0xE7000000;
    var_s2->words.w1 = 0;
    return var_s2 + 1;
}
