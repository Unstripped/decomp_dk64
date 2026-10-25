// func_80711BD0 (src/global/114270.c): Stage 6: exact frame, saved registers, unsigned threshold divisions, and FP constant allocation; residual clamp branch-likely scheduling and one local rodata constant.

extern void *D_807FC924;
extern u16 *D_807550E0;
extern s32 D_807FBB60;
extern void *D_807212E0;
extern s16 D_807FDA1E;
extern u8 D_807FDA1B;
extern u8 D_807FDA1C;
s32 func_80611A44(void);
s32 func_806119A0(void);
f32 func_80612D10(f32);
void func_8070F5CC(u8, s16, f32, s16, s32, s32);
void func_80710CA0(void);
void func_8071495C(void);
void func_8071498C(void (*)(void));
void func_807149FC(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_8071F444(void);
void renderCallbacksRegister(void *, void *, s32);

void func_80711BD0(f32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    f32 temp_fv1;
    f64 new_var;
    f32 var_fs0;
    f64 temp_fv0;
    f64 var_fv1;
    s32 temp_s0;
    s32 var_s0;
    s32 var_s1;

    if (D_807FBB60 & 0x10) {
        if ((arg3 == 3) && (((s32)(func_80611A44() >> 0xF) % 1000) >= 0x3DA)) {
            func_807149FC(-1);
            func_8071498C(&func_8071F444);
            func_8071495C();
            temp_s0 = func_80611A44();
            func_80714CC0(&D_807212E0, (f32)(((f64)((s32)(temp_s0 >> 0xF) % 100) * 0.01) + 0.4), (f32)((s32)(func_80611A44() >> 0xF) % 320), 0.0f, -5.0f);
        }
        D_807FDA1E = (s16)(s32)(func_80612D10(((R114cPlayerView *)D_807FC924)->unk2C4) * (f32)arg1);
        if ((f64)arg0 < 1.0) {
            arg0 *= 100.0f;
            if ((f32)(s32)((u32)(func_806119A0() / 10000U) % 100U) < arg0) {
                var_s1 = 1;
            } else {
                var_s1 = 0;
            }
        } else {
            var_s1 = (s32)arg0;
        }
        D_807FDA1B = 0xFF;
        var_s0 = 0;
        if (var_s1 > 0) {
            do {
                temp_fv1 = (f32)((f64)((s32)((s32)(func_80611A44() >> 0xF) % 32767) % 80) * 0.005);
                var_fs0 = temp_fv1;
                if (D_807FDA1C != 3) {
                    temp_fv0 = (f64)temp_fv1 * 3.0;
                    if (temp_fv0 > 0.3) {
                        var_fv1 = temp_fv0;
                    } else {
                        var_fv1 = 0.3;
                    }
                    new_var = 2.0;
                    if (var_fv1 < new_var) {
                        if (temp_fv0 > 0.3) {
                            var_fs0 = (f32)temp_fv0;
                        } else {
                            var_fs0 = (f32)0.3;
                        }
                    } else {
                        var_fs0 = (f32)new_var;
                    }
                }
                var_fs0 = (f32)((f64)var_fs0 + 0.2);
                if ((D_807FDA1C == 4) && (((s32)(func_80611A44() >> 0xF) % 100) >= 0x33)) {
                    var_fs0 *= -1.0f;
                }
                func_8070F5CC(arg3, arg2, var_fs0, (s16)(s32)((u32)(func_806119A0() / 10000U) % 320U), -10, 0xC8);
                var_s0 += 1;
            } while (var_s0 != var_s1);
        }
        if (*D_807550E0 != 0) {
            renderCallbacksRegister(&func_80710CA0, 0, 1);
        }
    }
}
