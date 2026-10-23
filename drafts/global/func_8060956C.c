// func_8060956C (src/global/7130.c): matched 100% TEXT OK; 403 insns text-identical; rodata bit-for-bit identical; reloc differences only due to section relative rodata offsets vs symbol labels
#include "common.h"

typedef struct {
    char pad0[0x20F];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0xA8];
    f32 unk2C4;
} Aud7130M1_AudPlayer;

extern Aud7130M1_AudPlayer *D_807FC924;
extern f32 D_80770DE4;
extern u8 D_80745838;
extern u8 D_8077058E;
extern s32 D_807457C8;
extern s32 D_8076D1F8;
extern s32 D_8076D1FC;

f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
f32 func_80612D1C(f32);
u32 func_806119A0(void);
void n_alSndpAllocate(s32, s16, s32, s32, f32, s32, s32 *);
void n_alSndpDeallocate(s32);

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

void func_8060956C(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 arg4, f32 arg5, u8 arg6, u8 arg7) {
    s32 dx, dy, dz;
    s32 vol;
    f32 pan;
    u8 reverb;
    f64 pad;

    reverb = 0;
    dx = D_807FC924->unk210 - arg0;
    dy = D_807FC924->unk214 - arg1;
    dz = D_807FC924->unk218 - arg2;
    D_80770DE4 = sqrtf((f32)(dx * dx + dy * dy + dz * dz));
    if (D_80770DE4 < 1.0f) {
        D_80770DE4 = 1.0f;
    }
    vol = (s32)(((f64)((f32)(arg7 * 4000) / sqrtf(D_80770DE4))) - (((f64)(f32)(arg7 * 4000) / 7.74596600000000013) - 32767.0));
    if (vol >= 0x8000) {
        vol = 0x7FFF;
    }
    vol = (s32)((f64)(arg4 * vol) / 255.0);
    if (vol >= 0x8000) {
        vol = 0x7FFF;
    }
    if (vol < 1001) {
        return;
    }
    vol = (s32)((f64)(arg4 * vol) / 255.0);
    if (arg6 != 0) {
        vol = (s32)((1.0 - (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)arg6 / 155.0))) * (f64)vol);
        arg5 = ((f64)arg5 - ((f64)(u32)arg6 / 255.0)) + (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)arg6 / 100.0));
    }
    pan = mathAngleBetweenPointsRad(D_807FC924->unk210, D_807FC924->unk218, arg0, arg2) - D_807FC924->unk2C4;
    if (pan < 0.0f) {
        pan += 6.2831855f;
    }
    if (pan > 0.7853982f && (f64)pan < 5.497787296772003) {
        vol = (s32)((((f64)func_80612D1C(((2.0 * (f64)pan) / 3.0) + 2.617993950843811) * 0.3) + 1.0) * (f64)vol);
    }
    pan = (f32)((f64)(1.0f - func_80612D1C(pan)) * 63.5);
    if (D_80745838 != 0) {
        reverb = 30;
    } else if (D_8077058E >= 21) {
        reverb = (D_8077058E * 100) / 255;
    }
    if (D_807457C8 != 0) {
        n_alSndpDeallocate(D_807457C8);
    }
    osSetThreadPri(NULL, 26);
    if (arg3 < 0x800) {
        n_alSndpAllocate(D_8076D1F8, arg3, (u16)vol, (u8)pan, arg5, reverb, &D_807457C8);
    } else {
        n_alSndpAllocate(D_8076D1FC, arg3 - 0x7FF, (u16)vol, (u8)pan, arg5, reverb, &D_807457C8);
    }
    osSetThreadPri(NULL, 10);
}
