// func_80711950 (src/global/114270.c): Stage 4: retained signed random local draft. Testing u32 local produces unsigned-to-float correction code absent from target; target divu therefore comes from the RNG return, while modulo-to-float needs signed handling.
typedef struct R114bPlayerView {
    u8 unk0[0x2C4];
    f32 unk2C4;
} R114bPlayerView;

extern s32 D_807FBB60;
extern s16 D_807FDA1E;
extern u8 D_807FDA1B;
extern u16 *D_807550E0;
f32 func_80612D10(f32);
u32 func_806119A0(void);
void func_8070F5CC(s32, s16, f32, s16, s16, s32);
void func_80710CA0(void);
void renderCallbacksRegister(void (*)(void), s32, s32);

void func_80711950(f32 arg0, s16 arg1, s16 arg2) {
    s32 random;
    s32 count;
    s32 i;
    f32 value;

    if (D_807FBB60 & 0x10) {
        D_807FDA1E = (s16)(func_80612D10(((R114bPlayerView *)D_807FC924)->unk2C4) * arg1);
        if (arg0 < 1.0) {
            arg0 *= 100.0f;
            random = func_806119A0() / 10000;
            count = ((random % 100) < arg0);
        } else {
            count = (s32)arg0;
        }
        D_807FDA1B = 0xFF;
        for (i = 0; i < count; i++) {
            random = func_806119A0() / 10000;
            value = (f32)(((f64)(random % 125) / 1000.0) + 0.075);
            random = func_806119A0() / 10000;
            func_8070F5CC(1, arg2, value, (s16)(random % 320), -10, 200);
        }
        if (*D_807550E0 != 0) {
            renderCallbacksRegister(func_80710CA0, 0, 1);
        }
    }
}
