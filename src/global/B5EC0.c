#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern s32 D_8071FFA0;

s32 actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_80685B44(void *, s32, f32, s32, s32, s32, s32, s32, s32);
void actorSpawnEffectChild(f32, f32, f32, f32, f32, Actor *, u8);

void func_806B11C0(u8 arg0) {
    f32 x;
    f32 y;
    f32 z;

    actorGetNodePos(D_807FBB40, arg0, &x, &y, &z);
    func_80685B44(&D_8071FFA0, 0, 1.0f, 3, 5, 0x28, x, D_807FBB40->unkA4, z);
    actorSpawnEffectChild(x, D_807FBB40->unkA4, z, 0.05f, 0.04f, D_807FBB40, 0);
}

typedef struct M4Actor {
    /* 0x000 */ u8 pad0[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0xF0];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} M4Actor;

typedef struct M4Sub90 {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
} M4Sub90;


s32 func_80611A44(void);

void func_806B1290(void) {
    if (((M4Sub90 *)D_807FDC90)->unk18 >= 0x65
        && (((((M4Sub90 *)D_807FDC90)->unk1A & 0x80) && (func_80611A44() >> 15) % 1000 >= 0x3D5)
            || ((func_80611A44() >> 15) % 1000 >= 0x3DF && (D_807FBB40->unk60 & 0x100)))) {
        ((M4Actor *)D_807FBB40)->unk154 = 0x28;
        ((M4Actor *)D_807FBB40)->unk155 = 0;
    }
}

extern u8 D_807FBD70;

s32 func_8072DE10(s32);

void func_806B1348(void) {
    if (((M4Sub90 *)D_807FDC90)->unk18 >= 0x65 && D_807FBD70 == 2 && func_8072DE10(0x2710) != 0) {
        ((M4Actor *)D_807FBB40)->unk154 = 0x27;
        ((M4Actor *)D_807FBB40)->unk155 = 0;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/B5EC0/func_806B13B4.s")

void animSetLoopLimit(Actor *, s32, s32);
void animSetFinished(Actor *, s32, s32);
void animSetFrameAndSubframe(Actor *, s32, u8, f32);

void func_806B1D78(u8 arg0) {
    animSetLoopLimit(D_807FBB40, 0, 1);
    animSetFinished(D_807FBB40, 0, 1);
    animSetFrameAndSubframe(D_807FBB40, 0, arg0, 0.0f);
}

typedef struct M4Tail {
    /* 0x000 */ u8 pad0[0x15F];
    /* 0x15F */ u8 unk15F;
} M4Tail;

extern u8 D_8076A0AB;
extern s32 D_80750600[];

s32 func_805FF000(u8);
s32 func_805FF030(u8, s32);
void func_806B13B4(u8);
s32 func_80731A04(s32, s32, s32, s32);

void func_806B1DD4(u8 arg0) {
    u8 flag;
    s32 temp;

    if (!(D_807FBB40->unk60 & 0x10)) {
        flag = 0;
        temp = func_805FF000(D_8076A0AB);
        if (temp != 9 && temp != 0xA) {
            temp = func_805FF030(D_8076A0AB, 1);
            flag = func_80731A04(0x1D5, temp, temp, D_80750600[arg0]) == 0;
        }
        func_806B1D78(flag != 0 ? arg0 : 5);
        ((M4Tail *)D_807FBB40)->unk15F = flag;
    }
    func_806B13B4(((M4Tail *)D_807FBB40)->unk15F);
}

void func_806B1EA8(void) {
    func_806B1DD4(4);
}

void func_806B1EC8(void) {
    func_806B1DD4(2);
}

void func_806B1EE8(void) {
    func_806B1DD4(3);
}

void func_806B1F08(void) {
    func_806B1DD4(0);
}

void func_806B1F28(void) {
    func_806B1DD4(1);
}
