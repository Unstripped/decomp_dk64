// func_80605380 (src/global/7130.c): Stage 6, frame 0x30 exact, same insn count. Remaining: uopt colors count var (adjsave 2.67) before a1 var (2.33) so count->$a1, a1->$a2 (expected a1->$a1, count->$t0 via 'or a1,t0,zero'); cascades into arg0 t0 vs t1, t3/t2 swaps. Tried: s32/s16 var types, decl order, single dead 'if (a1) {}' / 'if (t0) {}' / 'if (arg0) {}' at every position (none helps; two deadsweep stmts reach text score 31 but move count into $s0 and grow frame to 0x38)
#include "common.h"

extern s16 D_80770628[];
extern s16 D_80770740[];
extern s16 D_80770658[];
extern s16 D_80770710[];
extern u8 D_807706F8[];
extern s16 D_807707A0[][22];
extern s16 D_807705F8[];
extern void *D_807705A0[];

void faultSetMessage(s32, s32, s32, s32);

void func_80605380(s16 arg0) {
    s16 a1 = D_80770628[arg0];
    s16 t0;

    t0 = --D_80770740[a1];

    if (t0 != 0) {
        s16 v1 = D_807707A0[a1][t0];
        D_80770658[v1] = D_80770658[D_807707A0[a1][D_80770658[arg0]]];
        D_807707A0[a1][D_80770658[arg0]] = v1;
    } else {
        D_80770710[a1] = 0;
        D_807706F8[a1] = 0;
    }

    if (t0 < 0 || t0 >= 23) {
        faultSetMessage(9, t0, 0, 0);
        a1 = D_80770628[arg0];
        t0 = D_80770740[a1];
    }

    D_807707A0[a1][t0] = -1;
    D_807705F8[arg0] = -1;
    D_807705A0[arg0] = NULL;
    D_80770628[arg0] = -1;
    D_80770658[arg0] = -1;
}
