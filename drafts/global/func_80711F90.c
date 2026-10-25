// func_80711F90 (src/global/114270.c): Stage 4: exact frame/saved-register set; remaining threshold block order and FP register allocation.
typedef struct R114cPlayerView {
    u8 pad0[0x2C4];
    f32 unk2C4;
} R114cPlayerView;

extern void *D_807FC924;
extern u16 *D_807550E0;
extern s16 D_807FDA1E;
extern u8 D_807FDA1B;
s32 func_80611A44(void);
f32 func_80612D10(f32);
void func_8070F5CC(u8, s16, f32, s16, s32, s32);
void func_80710CA0(void);
void renderCallbacksRegister(void *, void *, s32);

void func_80711F90(f32 arg0, s16 arg1, s32 arg2, s16 arg3, f32 arg4) {
    f32 temp_fs1;
    s32 var_s0;
    s32 var_s4;

    D_807FDA1E = (s16)(s32)(func_80612D10(((R114cPlayerView *)D_807FC924)->unk2C4) * (f32)arg1);
    if ((f64)arg0 < 1.0) {
        if ((f32)((s32)((s32)(func_80611A44() >> 0xF) % 32767) % 100) < (arg0 * 100.0f)) {
            var_s4 = 1;
        } else {
            var_s4 = 0;
        }
    } else {
        var_s4 = (s32)arg0;
    }
    D_807FDA1B = 0xFF;
    var_s0 = 0;
    if (var_s4 > 0) {
        do {
            temp_fs1 = (f32)((s32)((s32)(func_80611A44() >> 0xF) % 32767) % 320);
            func_8070F5CC(2, arg3, (f32)(((f64)(f32)((f64)((s32)((s32)(func_80611A44() >> 0xF) % 32767) % 125) / 800.0) + 0.1) * 2.5 * (f64)arg4), (s16)(s32)temp_fs1, -10, 0xFF);
            var_s0 += 1;
        } while (var_s0 != var_s4);
    }
    if (*D_807550E0 != 0) {
        renderCallbacksRegister(&func_80710CA0, 0, 1);
    }
}
