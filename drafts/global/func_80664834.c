// func_80664834 (src/global/68EA0.c): Frame 0x28 matches; only slight schedule difference in 3-coord eval for func_80714CC0
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

s32 func_80611A44(void);
void func_807149B8(s32);
void func_80714998(s32);
void func_80714950(s32);
void func_8071498C(void *);
void func_807149C8(s32, s32, s32, s32);
void func_80714A08(f32, f32);
void func_80714A28(s32);
void func_80714CC0(void *, s32, f32, f32, f32);

extern u8 D_807213D0;
void func_80717DB4(void);

void func_80664834(s16 arg0) {
    s32 pad[1];
    s32 sp20;

    if (((func_80611A44() % 10000) % 12) == 0) {
        func_807149B8(1);
        func_80714998(7);
        func_80714950(((func_80611A44() % 10000) % 50) - 120);
        func_8071498C(func_80717DB4);
        func_807149C8(255, 200, 200, 200);
        func_80714A08(0.2f, 0.1f);
        func_80714A28(4);
        sp20 = func_80611A44();
        func_80714CC0(&D_807213D0, 0,
            (((f64) ((sp20 % 10000) % 100) / 20.0) + (f64) D_807F9430[arg0].unk2) - 2.5,
            (f64) D_807F9430[arg0].unk4 + 4.0,
            (((f64) ((func_80611A44() % 10000) % 100) / 20.0) + (f64) D_807F9430[arg0].unk6) - 2.5);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/68EA0/func_80664A38.s")
