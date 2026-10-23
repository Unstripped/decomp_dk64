// func_80659670 (src/global/5E2F0.c): stage 1: m2c translation, clamps RGB floats to 1.0f and sets array elements by index or loops over count
#include "common.h"

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern s32 D_807F6C28;

void func_80659670(f32 arg0, f32 arg1, f32 arg2, s16 arg3) {
    s32 count;
    s32 i;

    count = (D_807F6C28 <= 0) ? 1 : (D_807F6C28 & 0xFF);
    if (arg3 != -1) {
        if (arg3 < count) {
            D_8076A0B4[arg3] = (arg0 <= 1.0f) ? arg0 : 1.0f;
            D_8076A0B8[arg3] = (arg1 <= 1.0f) ? arg1 : 1.0f;
            D_8076A0BC[arg3] = (arg2 <= 1.0f) ? arg2 : 1.0f;
        }
    } else {
        for (i = 0; i < count; i++) {
            D_8076A0B4[i] = (arg0 <= 1.0f) ? arg0 : 1.0f;
            D_8076A0B8[i] = (arg1 <= 1.0f) ? arg1 : 1.0f;
            D_8076A0BC[i] = (arg2 <= 1.0f) ? arg2 : 1.0f;
        }
    }
}
