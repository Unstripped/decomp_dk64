#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/67890/func_80662B90.s")

typedef struct R1F67890_Entry40 {
    u8 pad0[0x38];
    s16 unk38;
    u8 pad3A[6];
} R1F67890_Entry40;

extern R1F67890_Entry40 *D_807F93F0;
extern s32 D_807F93F8;

s32 func_80663040(s32 arg0) {
    s32 i;

    for (i = 0; i < D_807F93F8; i++) {
        if (arg0 == D_807F93F0[i].unk38) {
            return 1;
        }
    }
    return 0;
}

typedef struct R2G67890_Entry40 {
    f32 unk0[8];
    s16 unk20[12];
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    u8 unk3E;
    u8 unk3F;
} R2G67890_Entry40;

typedef struct R2G67890_Entry14 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 unk11;
    s8 unk12;
    s8 unk13;
} R2G67890_Entry14;

extern u8 *D_807F6C2C;
extern R2G67890_Entry14 *D_807F93F4;
f32 func_80611BB4(f32, f32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void func_8066308C(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    f32 ratio;
    f32 dist2d;
    s16 angle;
    f32 dz, dx;

    for (i = 0; i < D_807F93F8; i++) {
        D_807F93F4[i].unk11 = 0;
        if (D_807F6C2C[((R2G67890_Entry40 *)D_807F93F0)[i].unk38] != 0) {
            D_807F93F4[i].unk0 = sqrtf((((arg0 - D_807F93F4[i].unk4) * (arg0 - D_807F93F4[i].unk4)) + ((arg1 - D_807F93F4[i].unk8) * (arg1 - D_807F93F4[i].unk8))) + ((arg2 - D_807F93F4[i].unkC) * (arg2 - D_807F93F4[i].unkC)));
            ratio = (D_807F93F4[i].unk0 - (f32)((R2G67890_Entry40 *)D_807F93F0)[i].unk3A) / (f32)(((R2G67890_Entry40 *)D_807F93F0)[i].unk3C - ((R2G67890_Entry40 *)D_807F93F0)[i].unk3A);
            if ((f64)ratio > 1.0) {
                D_807F93F4[i].unk10 = ((R2G67890_Entry40 *)D_807F93F0)[i].unk3F;
            } else if ((f64)ratio < 0.0) {
                D_807F93F4[i].unk10 = ((R2G67890_Entry40 *)D_807F93F0)[i].unk3E;
            } else {
                u8 e3E = ((R2G67890_Entry40 *)D_807F93F0)[i].unk3E;
                f32 fa = (u32)e3E;
                D_807F93F4[i].unk10 = (u8)(u32)(((f32)(((R2G67890_Entry40 *)D_807F93F0)[i].unk3F - e3E) * ratio) + fa);
            }
            D_807F93F4[i].unk12 = (s32)((f64)mathAngleBetweenPoints2D(arg0, arg2, D_807F93F4[i].unk4, D_807F93F4[i].unkC) * 0.5) % 255;
            dz = arg2 - D_807F93F4[i].unkC;
            dx = arg0 - D_807F93F4[i].unk4;
            dist2d = sqrtf((dz * dz) + (dx * dx));
            angle = ((f64)func_80611BB4(D_807F93F4[i].unk8 - arg1, dist2d) * 2048.0) / 3.1415927410125732;
            D_807F93F4[i].unk13 = (s32)((f64)angle * 0.5) % 255;
            D_807F93F4[i].unk11 = 1;
        } else {
            D_807F93F4[i].unk11 = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/67890/func_806634A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/67890/func_80663594.s")
