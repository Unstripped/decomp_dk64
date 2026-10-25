#include "common.h"
#include "actor.h"

extern s32 D_8076A048;
extern u8 D_807FDB74;
extern u8 D_807FDB75;
extern s16 D_807FDB76;
extern s16 D_807FDB78;
extern s16 D_807FDB7A;
extern u8 D_807FDB7C;
extern u8 D_807FDB7D;
extern u8 D_807FDB7E;
extern u8 D_807FDB7F;
extern u8 D_807FDB80;

void *func_80610FE8(s32);
f32 func_80612790(s16);
f32 func_80612794(s16);

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 unkA;
    s8 unkB;
    s8 unkC;
    s8 unkD;
    s8 unkE;
} Ud1CommandState;

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    u8 unkE;
} Ud1Command;

extern Ud1CommandState D_807FDB60;
extern s32 D_807FDB70;

void func_80721560(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    D_807FDB76 = arg0;
    D_807FDB78 = arg1;
    D_807FDB7A = arg2;
    D_807FDB7E = arg3;
    D_807FDB7F = arg4;
    D_807FDB80 = arg5;
}

void func_807215AC(s8 arg0, s8 arg1, s8 arg2) {
    D_807FDB60.unkB = arg0;
    D_807FDB60.unkC = arg1;
    D_807FDB60.unkD = arg2;
}

void func_807215D0(s8 arg0, s8 arg1) {
    D_807FDB7C = arg0;
    D_807FDB7D = arg1;
}

void func_807215EC(void) {
    D_807FDB60.unk8 = 0;
    D_807FDB60.unkB = 0x6B;
    D_807FDB60.unkC = 0x30;
    D_807FDB60.unkD = 0x50;
    D_807FDB60.unkE = 7;
    D_807FDB60.unk6 = D_807FDB60.unk8;
    D_807FDB60.unk4 = D_807FDB60.unk8;
    D_807FDB70 = (s32) func_80610FE8(0x200);
    func_80721560(0x320, 0x82, 0, 0xFF, 0xFF, 0xFF);
    func_807215D0(1, 1);
}

extern s16 D_80755680;
extern f32 D_80755684;
extern f32 D_80755688;
extern f32 D_8075568C;

void func_8072167C(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    D_80755680 = (s16) (s32) ((f64) D_80755680 + ((f64) (arg3 - D_80755680) * 0.1));
    D_80755684 = (f32) ((f64) D_80755684 + ((f64) ((f32) arg0 - D_80755684) * 0.1));
    D_80755688 = (f32) ((f64) D_80755688 + ((f64) ((f32) arg1 - D_80755688) * 0.1));
    D_8075568C = (f32) ((f64) D_8075568C + ((f64) ((f32) arg2 - D_8075568C) * 0.1));
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/126260/func_8072177C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/126260/func_80721814.s")

void func_80722280(void) {
    D_807FDB74 = 0;
    D_807FDB75 = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/126260/func_80722294.s")
