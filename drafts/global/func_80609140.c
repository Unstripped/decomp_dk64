// func_80609140 (src/global/7130.c): Stage 6, exact 0x38 frame, 266/269 insns, diff is v0 vs v1 in reverb block
#include "common.h"
u32 func_806119A0(void);
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, s32 *);
void n_alSndpSetPriority(s32, s32);
extern s32 D_807457E4[];
extern u8 D_80745834;
extern s32 D_8076D1F8;
extern s32 D_8076D1FC;
extern u8 D_8077058E;

s16 func_80609140(s16 arg0, s32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    s16 res;
    s16 i;

    if (arg4 != 0) {
        arg1 = (1.0 - (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)arg4 / 155.0))) * (f64)arg1;
        arg3 = (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)arg4 / 100.0)) + ((f64)arg3 - ((f64)(u32)arg4 / 255.0));
    }

    for (i = 20; i > 0; i--) {
        if (D_807457E4[D_80745834] == 0) {
            break;
        }
        if (++D_80745834 == 20) {
            D_80745834 = 0;
        }
    }

    if (i > 0) {
        osSetThreadPri(NULL, 26);
        if (D_8077058E >= 21) {
            u8 rev_raw = D_8077058E;
            s32 reverb = (rev_raw * 100) / 255;
            reverb = (reverb < (arg5 & 0x7F)) ? (arg5 & 0x7F) : reverb;
            arg5 = reverb | (arg5 & 0x80);
        }

        if (arg0 < 0x800) {
            n_alSndpPlay(D_8076D1F8, arg0, (u16)arg1, (u8)arg2, arg3, arg5, &D_807457E4[D_80745834]);
        } else {
            n_alSndpPlay(D_8076D1FC, arg0 - 0x7FF, (u16)arg1, (u8)arg2, arg3, arg5, &D_807457E4[D_80745834]);
        }

        if (arg0 == 0x137) {
            n_alSndpSetPriority(D_807457E4[D_80745834], 100);
        }

        res = -1;
        if (D_807457E4[D_80745834] != 0) {
            res = (s16)D_80745834;
        } else {
            res = -1;
        }
        osSetThreadPri(NULL, 10);
        return res;
    }

    return -1;
}
