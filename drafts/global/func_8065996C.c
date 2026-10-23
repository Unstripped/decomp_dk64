// func_8065996C (src/global/5E2F0.c): stage 1: m2c translation, copies vectors from D_8076A0C0/C4/C8 to D_8076A0B4/B8/BC
#include "common.h"

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern f32 *D_8076A0C0;
extern f32 *D_8076A0C4;
extern f32 *D_8076A0C8;
extern s32 D_807F6C28;

void func_8065996C(s16 arg0) {
    s32 count;
    s32 i;

    count = (D_807F6C28 <= 0) ? 1 : (D_807F6C28 & 0xFF);
    if (arg0 != -1) {
        if (arg0 < count) {
            D_8076A0B4[arg0] = D_8076A0C0[arg0];
            D_8076A0B8[arg0] = D_8076A0C4[arg0];
            D_8076A0BC[arg0] = D_8076A0C8[arg0];
        }
    } else {
        for (i = 0; i < count; i++) {
            D_8076A0B4[i] = D_8076A0C0[i];
            D_8076A0B8[i] = D_8076A0C4[i];
            D_8076A0BC[i] = D_8076A0C8[i];
        }
    }
}
