// func_80605380 (src/global/7130.c): Stage 6 (frame 0x30 exact, 99/100 insns, diff score 92: uopt assigns t0 before a1 causing t0->$a1, a1->$a2 which drops move $a1, $t0 before func_80732354; tested permuter and var ordering)
#include "common.h"

extern s16 D_80770628[];
extern s16 D_80770740[];
extern s16 D_80770658[];
extern s16 D_80770710[];
extern u8 D_807706F8[];
extern s16 D_807707A0[][22];
extern s16 D_807705F8[];
extern void *D_807705A0[];

void func_80732354(s32, s32, s32, s32);

void func_80605380(s16 arg0) {
    s16 a1 = D_80770628[arg0];
    s16 t0 = --D_80770740[a1];

    if (t0 != 0) {
        s16 v1 = D_807707A0[a1][t0];
        D_80770658[v1] = D_80770658[D_807707A0[a1][D_80770658[arg0]]];
        D_807707A0[a1][D_80770658[arg0]] = v1;
    } else {
        D_80770710[a1] = 0;
        D_807706F8[a1] = 0;
    }

    if (t0 < 0 || t0 >= 23) {
        func_80732354(9, t0, 0, 0);
        a1 = D_80770628[arg0];
        t0 = D_80770740[a1];
    }

    D_807707A0[a1][t0] = -1;
    D_807705F8[arg0] = -1;
    D_807705A0[arg0] = NULL;
    D_80770628[arg0] = -1;
    D_80770658[arg0] = -1;
}
