// func_80609140 (src/global/7130.c): Stage 4 (sound effect play with pitch/pan and voice slot allocation)
#include "common.h"

u32 func_806119A0(void);
void n_alSndpAllocate(s32, s16, s32, s32, f32, s32, s32 *);
void n_alSndpPlayAt(s32, s32);
extern s32 D_807457E4[];
extern u8 D_80745834;
extern s32 D_8076D1F8;
extern s32 D_8076D1FC;
extern u8 D_8077058E;

s16 func_80609140(s16 arg0, s32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    s16 res = -1;
    s32 i;
    f32 var_fa0 = arg3;

    if (arg4 != 0) {
        f64 var_fv0 = (f64)(u32)arg4;
        f64 r1 = (f64)(u32)func_806119A0() / 4294967295.0;
        f64 r2;

        arg1 = (1.0 - (r1 * (var_fv0 / 155.0))) * (f64)arg1;
        r2 = (f64)(u32)func_806119A0() / 4294967295.0;
        var_fa0 = (r2 * (var_fv0 / 100.0)) + ((f64)arg3 - (var_fv0 / 255.0));
    }

    for (i = 20; i > 0; i--) {
        u8 next = D_80745834 + 1;
        if (D_807457E4[D_80745834] == 0) {
            break;
        }
        D_80745834 = next;
        if (D_80745834 == 20) {
            D_80745834 = 0;
        }
    }

    if (i > 0) {
        osSetThreadPri(NULL, 26);
        if (D_8077058E >= 21) {
            s32 reverb = (D_8077058E * 100) / 255;
            s32 min_rev = arg5 & 0x7F;
            if (reverb < min_rev) {
                reverb = min_rev;
            }
            arg5 = reverb | (arg5 & 0x80);
        }

        if (arg0 < 0x800) {
            n_alSndpAllocate(D_8076D1F8, arg0, (u16)arg1, (u8)arg2, var_fa0, arg5, &D_807457E4[D_80745834]);
        } else {
            n_alSndpAllocate(D_8076D1FC, arg0 - 0x7FF, (u16)arg1, (u8)arg2, var_fa0, arg5, &D_807457E4[D_80745834]);
        }

        if (arg0 == 0x137) {
            n_alSndpPlayAt(D_807457E4[D_80745834], 100);
        }

        if (D_807457E4[D_80745834] != 0) {
            res = D_80745834;
        }
        osSetThreadPri(NULL, 10);
    }
    return res;
}
