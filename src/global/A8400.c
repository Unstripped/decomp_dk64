#include "common.h"
#include "actor.h"

void func_806A3700(s32 arg0, s32 arg1) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A370C.s")

void func_806A370C(s32 *, void *, void *, void *);

typedef struct M7Actor {
    /* 0x00 */ u8 pad0[0x11];
    /* 0x11 */ u8 unk11;
} M7Actor;

typedef struct M7Node {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ struct M7Node *unkA0;
} M7Node;

typedef struct M7Sub {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[0xB];
    /* 0x0C */ struct M7Node *unkC;
} M7Sub;

void func_806A3B78(s32 *arg0, M7Actor *arg1, M7Sub *arg2, u8 arg3, u8 *arg4) {
    s32 sp44;
    s32 i;
    M7Node *node;

    sp44 = *arg0;
    node = arg2->unkC;
    i = 0;
    while (node != NULL && *arg4 == 0) {
        if (arg3 && (i == arg1->unk11)) {
            *arg4 = 1;
        }
        if (arg2->unk0 & 1) {
            func_806A370C(&sp44, arg1, arg2, node);
        }
        node = node->unkA0;
        i++;
    }
    *arg0 = sp44;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A3C6C.s")

f32 func_80612790(s16);
f32 func_80612794(s16);

typedef struct M7Angle {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
} M7Angle;

void func_806A3DA0(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3, M7Angle *arg4) {
    *arg0 += (arg2 * arg3) * 24.0f * func_80612794((s16) ((s16) ((s32) ((f32) arg4->unk38 + (arg2 * 3000.0f))) & 0xFFF));
    *arg1 += (arg2 * arg3) * 16.0f * func_80612790((s16) ((s16) ((s32) ((f32) arg4->unk3A + (arg2 * 3000.0f))) & 0xFFF));
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A3E9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A4284.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A495C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A4B84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A4DDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A5174.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A57C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/func_806A5868.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A8400/D_8075A740.s")
