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
} CommandState;

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
} Command;

extern CommandState D_807FDB60;
extern s32 D_807FDB70;

void commandSetParameters(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    D_807FDB76 = arg0;
    D_807FDB78 = arg1;
    D_807FDB7A = arg2;
    D_807FDB7E = arg3;
    D_807FDB7F = arg4;
    D_807FDB80 = arg5;
}

void commandSetColor(s8 arg0, s8 arg1, s8 arg2) {
    D_807FDB60.unkB = arg0;
    D_807FDB60.unkC = arg1;
    D_807FDB60.unkD = arg2;
}

void commandSetFlags(s8 arg0, s8 arg1) {
    D_807FDB7C = arg0;
    D_807FDB7D = arg1;
}

void commandStateInit(void) {
    D_807FDB60.unk8 = 0;
    D_807FDB60.unkB = 0x6B;
    D_807FDB60.unkC = 0x30;
    D_807FDB60.unkD = 0x50;
    D_807FDB60.unkE = 7;
    D_807FDB60.unk6 = D_807FDB60.unk8;
    D_807FDB60.unk4 = D_807FDB60.unk8;
    D_807FDB70 = (s32) func_80610FE8(0x200);
    commandSetParameters(0x320, 0x82, 0, 0xFF, 0xFF, 0xFF);
    commandSetFlags(1, 1);
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

void func_8072177C(s32 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8) {
    s32 var_v0;
    s32 temp_t3;
    Command *temp_v1;

    var_v0 = D_807FDB74;
    if (var_v0 >= 0x20) {
        temp_t3 = var_v0 - 1;
        D_807FDB74 = temp_t3 & 0xFFFF;
        var_v0 = temp_t3 & 0xFF;
    }
    temp_v1 = (Command *)(D_807FDB70 + var_v0 * 0x10);
    D_807FDB74 = var_v0 + 1;
    temp_v1->unk0 = arg0;
    temp_v1->unk4 = arg1;
    temp_v1->unk6 = arg2;
    temp_v1->unk8 = arg3;
    temp_v1->unkA = arg4;
    temp_v1->unkB = arg5;
    temp_v1->unkC = arg6;
    temp_v1->unkD = arg7;
    temp_v1->unkE = arg8;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/126260/func_80721814.s")

void commandQueueReset(void) {
    D_807FDB74 = 0;
    D_807FDB75 = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/126260/func_80722294.s")
