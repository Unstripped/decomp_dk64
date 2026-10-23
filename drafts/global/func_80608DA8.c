// func_80608DA8 (src/global/7130.c): Stage 4 (stack frame 0x58 vs 0x48, behaviourally equivalent sound effect play/alloc)
#include "common.h"

u32 func_806119A0(void);
void n_alSndpAllocate(s32, s16, s32, s32, f32, s32, s32 *);
void n_alSndpDeallocate(s32);
void n_alSndpPlayAt(s32, s32);
extern s32 D_807457D0[];
extern u8 D_807457D8;
extern s32 D_8076D1F8;
extern u8 D_8077058E;

void func_80608DA8(s16 arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4) {
    s32 vol;
    f32 pan;
    f32 pitch;
    u8 reverb;
    f32 orig_pitch;
    f64 var_fv0;

    vol = (s32)(((f64)((arg1 & 0xFF) * 0x7FFF)) / 255.0);
    if (vol < 1001) {
        return;
    }

    pitch = (f64)(u32)(arg2 & 0xFF) / 127.0;
    orig_pitch = pitch;
    var_fv0 = (f64)(u32)(arg3 & 0xFF);
    pan = ((f64)(u32)func_806119A0() / 4294967295.0) * (2.0 * var_fv0) + (63.5 - var_fv0);
    reverb = 0;

    if (arg3 != 0) {
        vol = (1.0 - (((f64)(u32)func_806119A0() / 4294967295.0) * (var_fv0 / 155.0))) * (f64)vol;
        pitch = (((f64)(u32)func_806119A0() / 4294967295.0) * (var_fv0 / 100.0)) + ((f64)orig_pitch - (var_fv0 / 255.0));
    }

    if (D_8077058E >= 21) {
        reverb = (D_8077058E * 100) / 255;
    }
    if (arg4 != 0) {
        reverb |= 0x80;
    }

    if (D_807457D0[D_807457D8] != 0) {
        n_alSndpDeallocate(D_807457D0[D_807457D8]);
    }
    n_alSndpAllocate(D_8076D1F8, arg0, (u16)vol, (u8)pan, pitch, reverb, &D_807457D0[D_807457D8]);
    n_alSndpPlayAt(D_807457D0[D_807457D8], 0);
    D_807457D8 ^= 1;
}
