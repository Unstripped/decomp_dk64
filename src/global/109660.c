#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_80704960.s")


extern f32 D_807FD968;
extern f32 D_807FD96C;
extern f32 D_807FD970;

void func_80704AFC(f32 arg0, f32 arg1, f32 arg2) {
    D_807FD968 = arg0;
    D_807FD96C = arg1;
    D_807FD970 = arg2;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_80704B20.s")

typedef struct {
    u8 unk0[0xC];
    s8 unkC;
    s8 unkD;
    s8 unkE;
} R1F109660aArgs;

void func_80705B14(R1F109660aArgs *arg0, s8 arg1, s8 arg2, s8 arg3) {
    arg0->unkC = arg1;
    arg0->unkD = arg2;
    arg0->unkE = arg3;
}

extern s32 D_807FD8A0;
extern Mtx D_807FD928;
extern s32 D_807FD978;

void func_80705B30(void) {
    D_807FD8A0 = 0;
    guOrtho(&D_807FD928, 0.0f, (f32)((f64)((f32)D_80744490 * 16.0f) - 1.0), (f32)((f64)((f32)D_80744494 * 16.0f) - 1.0), 0.0f, -20000.0f, 20000.0f, 1.0f);
    D_807FD968 = -1.0f;
    D_807FD978 = 0;
}

typedef struct {
    u8 unk0[0x2CA];
    s16 unk2CA;
} R1F109660aPlayerView;

f32 func_80612790(s16);
f32 func_80612794(s16);
void func_8070033C(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32);
void lightGetColor(f32 *, f32 *, f32 *, s16);

void func_80705C00(s16 arg0, s16 arg1, u8 arg2) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s16 sp42;
    s16 sp40;
    s16 sp3E;
    s32 unused;

    sp42 = (s16)(s32)((f64)func_80612794(arg0) * 32767.0);
    sp3E = (s16)(s32)((f64)func_80612790(arg0) * 32767.0);
    sp40 = (s16)(s32)((f64)arg1 - (8.0 * (f64)((R1F109660aPlayerView *)D_807FC924)->unk2CA));
    if (arg2 != 0) {
        if (arg2 == 1) {
            lightGetColor(&sp4C, &sp48, &sp44, *(s16 *)D_807FBB4C->unk12C);
            if ((f64)sp4C > 0.5) {
                func_8070033C((f32)sp42, (f32)sp40, (f32)sp3E, 0.0f, 0.0f, 0.0f, 0.0f, (u32)(sp4C * 255.0f), (u32)(sp48 * 255.0f), (u32)(sp44 * 255.0f));
            }
        }
    } else {
        func_8070033C((f32)sp42, (f32)sp40, (f32)sp3E, 0.0f, 0.0f, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_80705F5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_807063B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_807065F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_807069A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_80706F90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_8070770C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_80707980.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/109660/func_8070835C.s")

extern f32 D_80754CE8;

void func_80708574(f32 arg0) {
    f64 var_fv0;

    var_fv0 = (f64)arg0;
    if (var_fv0 < 0.0) {
        arg0 = 0.0f;
        var_fv0 = (f64)arg0;
    }
    if (var_fv0 > 1.0) {
        arg0 = 1.0f;
    }
    D_80754CE8 = arg0;
}
