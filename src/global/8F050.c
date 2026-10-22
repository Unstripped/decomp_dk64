#include "common.h"

typedef struct Act8CA_Struct_8F050 {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    u8 unk8;
    u8 unk9;
    s16 unkA;
    s32 unkC[2];
} Act8CA_Struct_8F050;

extern Act8CA_Struct_8F050 D_80750100[];
extern s16 D_80750102[];

typedef struct Act8CA_Actor4C {
    u8 pad[0x4C];
    s32 unk4C;
} Act8CA_Actor4C;

typedef struct Act8CA_Actor {
    u8 pad[0x146];
    s16 unk146;
} Act8CA_Actor;

s32 func_80612E90(void *, s32, s32);
void func_8068842C(s32, s32, s32);
void func_80688460(s32, s32, s32);
void func_806883F4(s32, s32, s16, f32);

void func_8068A350(s32 arg0, s32 arg1, s32 arg2) {
    func_8068842C(arg0, arg1, -1);
    func_80688460(arg0, arg1, 1);
    func_806883F4(arg0, arg1, arg2, 0.0f);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8F050/func_8068A3A0.s")

void func_8068A404(Act8CA_Actor4C *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 temp;

    if (arg0->unk4C == 0) {
        arg0->unk4C = func_80612E90(arg0, *(s16 *)((u8 *)D_80750102 + arg1 * 20), 0);
    }
    for (i = 0; i < 8; i += 4) {
        temp = *(s32 *)((u8 *)&D_80750100[arg1] + i + 0xC);
        if (temp != -1) {
            func_8068A350((s32)arg0, temp, arg2);
        }
    }
}

s32 func_8068A3A0(s32, s32 *);

void func_8068A4C8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp1C;

    if (func_8068A3A0(arg1, &sp1C)) {
        func_8068A404((Act8CA_Actor4C *)arg0, sp1C, arg2);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8F050/func_8068A508.s")

void func_8068A764(Act8CA_Actor *arg0, u8 arg1) {
    arg0->unk146 |= (1 << arg1);
}

void func_8068A784(Act8CA_Actor *arg0, u8 arg1) {
    arg0->unk146 &= ~(1 << arg1);
}
