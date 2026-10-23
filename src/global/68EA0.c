#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/68EA0/func_806641A0.s")

typedef struct R1Small_68EA0_Entry {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} R1Small_68EA0_Entry;

extern R1Small_68EA0_Entry *D_807F9430;
extern s16 D_807F9434;


void func_806643C4(s32 arg0, s32 arg1, f32 arg2) {
    s32 pad[2];
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp2C[4][4];

    if (arg1 == 0x138) {
        guRotateF(sp2C, arg2, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(sp2C, 0.0f, 0.0f, -10.0f, &sp74, &sp70, &sp6C);
        D_807F9430[arg0].unk2 += sp74;
        D_807F9430[arg0].unk6 += sp6C;
    }
}

void func_806644B0(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    s32 i;

    for (i = 0; i < D_807F9434; i++) {
        if (arg0 == D_807F9430[i].unkA) {
            D_807F9430[i].unk2 = arg1;
            D_807F9430[i].unk4 = arg2;
            D_807F9430[i].unk6 = arg3;
            func_806643C4(i, D_807F9430[i].unk0, arg5);
            D_807F9430[i].unk8 = arg4 * 100.0;
            return;
        }
    }
}


void func_806645B8(s16 arg0) {
    s32 i;

    for (i = 0; i < D_807F9434; i++) {
        if (arg0 == D_807F9430[i].unkA) {
            D_807F9430[i].unkA = -1;
        }
    }
}

s32 func_8066461C(s16 arg0) {
    if ((arg0 == 1) || (arg0 == 0x10) || (arg0 == 0x74) || (arg0 == 0xF3) || (arg0 == 0x138) || (arg0 == 0x288)) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/68EA0/func_8066466C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/68EA0/func_80664834.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/68EA0/func_80664A38.s")
