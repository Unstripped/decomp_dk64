// func_80711410 (src/global/114270.c): stage 4: target frame and saved-register set match; callback-volume, clamp, random count, and spawn loop reconstructed. A 1200-second two-worker permuter search did not yield a readable score-zero candidate; FP conversion scheduling and allocation still differ.
typedef struct R114dPlayerView {
    u8 pad0[0x2C4];
    f32 unk2C4;
} R114dPlayerView;

extern s32 D_807FBB60;
extern f32 *D_8076A0B4;
extern u8 D_8077058C[];
extern s16 D_807FDA1E;
extern u8 D_807FDA1B;
s32 func_80611A44(void);
f32 func_80612D10(f32);
void func_8070F5CC(u8, s16, f32, s16, s32, s32);
void func_80710CA0(void);
void renderCallbacksRegister(void *, void *, s32);

void func_80711410(f32 arg0, s16 arg1, f32 arg2, s16 arg3, f32 arg4) {
    f32 temp_fs1;
    f64 temp_fa0;
    f64 temp_fv1;
    f64 var_fv0;
    s32 var_s0;
    s32 var_s5;

    if (D_807FBB60 & 0x10) {
        temp_fv1 = (f64)arg0;
        D_807FDA1E = (s16)(s32)(func_80612D10(((R114dPlayerView *)D_807FC924)->unk2C4) * (f32)arg1);
        temp_fa0 = (temp_fv1 * 255.0) / 3.9;
        if (temp_fa0 > 255.0) {
            var_fv0 = 255.0;
        } else {
            var_fv0 = temp_fa0;
        }
        D_8077058C[0] = (u8)(u32)(var_fv0 * (f64)arg2);
        if (temp_fv1 < 1.0) {
            if ((f32)((s32)((s32)(func_80611A44() >> 0xF) % 32767) % 100) < (arg0 * 100.0f)) {
                var_s5 = 1;
            } else {
                var_s5 = 0;
            }
        } else {
            var_s5 = (s32)arg0;
        }
        var_s0 = 0;
        D_807FDA1B = (u8)(u32)((*D_8076A0B4 * 100.0f) + 100.0f);
        if (var_s5 > 0) {
            do {
                temp_fs1 = (f32)((s32)((s32)(func_80611A44() >> 0xF) % 32767) % 320);
                func_8070F5CC(0, arg3, (f32)(((f64)(f32)((f64)((s32)((s32)(func_80611A44() >> 0xF) % 32767) % 125) / 800.0) + 0.1) * 2.5 * (f64)arg4), (s16)(s32)temp_fs1, -10, (u32)(90.0f * arg4) & 0xFF);
                var_s0 += 1;
            } while (var_s0 != var_s5);
        }
        if (*D_807550E0 != 0) {
            renderCallbacksRegister(&func_80710CA0, 0, 1);
        }
    }
}
