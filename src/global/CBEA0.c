#include "common.h"
#include "actor.h"

void func_806C71A0(void) {
}

void func_806C71A8(void) {
}

void func_806C71B0(void) {
}

void func_806C71B8(void) {
}

void func_806C71C0(void) {
}

void func_806C71C8(void) {
}

void func_806C71D0(void) {
}

void func_806C71D8(void) {
}

void func_806C71E0(void) {
}

void func_806C71E8(void) {
}

void func_806C71F0(void) {
}

void func_806C71F8(void) {
}

void func_806C7200(void) {
}

void func_806C7208(void) {
}

void func_806C7210(void) {
}

void func_806C7218(void) {
}

void func_806C7220(void) {
}

void func_806C7228(void) {
}

void func_806C7230(void) {
}

void func_806C7238(void) {
}

void func_806C7240(void) {
}

void func_806C7248(void) {
}

void func_806C7250(void) {
}

void func_806C7258(void) {
}

void func_806C7260(void) {
}

void func_806C7268(void) {
}

#ifdef NON_MATCHING
typedef struct R1C2CB_Entry {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s8 unk4;
    /* 0x5 */ s8 unk5;
} R1C2CB_Entry;

typedef struct R1C2CB_Pair {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ f32 unk4;
} R1C2CB_Pair;

extern Actor *D_807FBB40;
extern s8 D_80750754;
extern s16 D_80750758;
extern R1C2CB_Entry D_807506D0[];
extern s8 D_807506D5[];
extern R1C2CB_Pair D_8075075C[];
extern s16 D_807FC8E0;
extern s16 D_807FC8E2;
extern s16 D_807FC8E4;
extern f32 D_807FC8E8;
extern f32 D_807FC8EC;
extern u8 *D_807FC8F0;

u8 *func_8066B0F8(s32, s32, s32, s32);
void renderCallbacksRegister(void *, void *, s32);
Gfx *func_806C75A4(Gfx *, Actor *);

void func_806C7270(void) {
    f32 frac;
    f32 x0;
    f32 y0;
    R1C2CB_Pair *e;
    Actor *actor;
    s32 i;
    s32 t;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FC8F0 = func_8066B0F8(0x13, 7, 1, 1);
        D_807FC8E0 = 0;
        for (i = 0; D_807FC8F0[i] != 0x2A; i++) {
            if (D_807FC8F0[i] == 0xA) {
                D_807FC8F0[i] = 0;
                D_807FC8E0++;
            }
        }
        if (D_80750754 == -2) {
            D_807FC8E4 = 0x320;
            D_80750754 = -1;
            D_807FC8E2 = 0;
            D_807FC8E8 = 0;
        } else if (D_80750754 == -1) {
            D_807FC8E4 = 0x3C;
            D_807FC8E2 = 0;
            D_807FC8E8 = 0;
        }
    }
    actor = D_807FBB40;
    if (D_807FC8E2 > 0) {
        D_807FC8E2--;
    }
    if (D_807FC8E2 == 0) {
        D_807FC8E2 = 0;
        D_807FC8E4--;
        if (D_807FC8E4 <= 0) {
            if (D_80750754 >= 0) {
                D_80750758 += D_807506D5[D_80750754 * 6];
            }
            if (D_80750758 >= D_807FC8E0) {
                D_80750758 = 0;
            }
            D_80750754++;
            D_807FC8E2 = D_807506D0[D_80750754].unk0;
            D_807FC8E4 = D_807506D0[D_80750754].unk2;
        }
    }
    if (D_807FC8E2 < 0xB) {
        D_807FC8E8 -= 0.1f;
        if (D_807FC8E8 < 0.0f) {
            D_807FC8E8 = 0.0f;
        }
        D_807FC8EC = 1;
    } else {
        t = D_807506D0[D_80750754].unk0 - D_807FC8E2;
        if ((t >> 1) < 0x16) {
            e = &D_8075075C[t >> 1];
            frac = (f64)(f32)(t & 1) * 0.5;
            x0 = e[0].unk0;
            y0 = e[0].unk4;
            D_807FC8E8 = (e[1].unk0 - x0) * frac + x0;
            D_807FC8EC = (e[1].unk4 - y0) * frac + y0;
        } else {
            D_807FC8E8 = 1.0f;
            D_807FC8EC = 1.0f;
        }
    }
    renderCallbacksRegister(func_806C75A4, actor, 3);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CBEA0/func_806C7270.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/CBEA0/func_806C75A4.s")
