// func_806699C4 (src/global/6AD90.c): diff 85 (t7 vs t0 regalloc only; frame 0x118, all stack offsets match, instruction sequence exact)
#include "common.h"
#include "actor.h"

typedef struct R3Q_Sub7C {
    u8 pad0[8];
    f32 unk8;
    f32 unkC;
    u8 pad10[0x34 - 0x10];
    f32 unk34;
} R3Q_Sub7C;

typedef struct R3Q_D_807F6000 {
    u8 pad[0x7C];
    R3Q_Sub7C *unk7C;
    u8 pad80[0x88 - 0x80];
    s16 unk88;
    u8 pad8A[6];
} R3Q_D_807F6000;

extern R3Q_D_807F6000 *D_807F6000;

void func_8066C610(s16, s8, float [4][4]);
void matrix4Invert(float [4][4], float [4][4]);

typedef struct R3Q_Actor_99C4 {
    u8 pad[0x100];
    f32 unk100;
    f32 unk104;
    f32 unk108;
    s16 unk10C;
    s8 unk10E;
    s8 unk10F;
} R3Q_Actor_99C4;

void func_806699C4(R3Q_Actor_99C4 *arg0, s16 arg1, s8 arg2, s8 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 pad2[10];
    float spB0[4][4];
    float pad[4][4];
    float sp30[4][4];

    arg0->unk10C = (arg1 + D_807F6000)->unk88;
    arg0->unk10E = arg3;
    arg0->unk10F = arg2;
    func_8066C610(arg1, arg2, spB0);
    matrix4Invert(sp30, spB0);
    guMtxXFMF(sp30, arg4, arg5, arg6, &arg0->unk100, &arg0->unk104, &arg0->unk108);
}
