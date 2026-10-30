// func_80605380 (src/global/7130.c): Stage 6 (one insn): K&R definition + pure expression form (no locals) + 'faultSetMessage(9, E * 1, 0, 0)' fake: text identical except 'move t1,t6' sits before 'addiu a0,a0,lo' (target: after it, before beqz t0). Tried (all no change): first-stmt forms (--x, -=1, +=-1), tail store permutations (120), fake forms (+0,|0,^0,<<0,...), cond forms (!(>=0&&<23), >22, etc.), local-based hybrids (a1 s16/s32/int x count local x reassign x fake, best 10 lines worse), deadsweep single stmt x 8 syms x 3 forms at every position (327), random dead-stmt hill-climb 12000x2. Candidate ids show the move is the {62}=arg0*2 live-range split inserted in candidate order vs the &D_80770658 addiu.
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

void func_80605380(arg0)
s16 arg0;
{
    D_80770740[D_80770628[arg0]]--;

    if (D_80770740[D_80770628[arg0]] != 0) {
        D_80770658[D_807707A0[D_80770628[arg0]][D_80770740[D_80770628[arg0]]]] = D_80770658[D_807707A0[D_80770628[arg0]][D_80770658[arg0]]];
        D_807707A0[D_80770628[arg0]][D_80770658[arg0]] = D_807707A0[D_80770628[arg0]][D_80770740[D_80770628[arg0]]];
    } else {
        D_80770710[D_80770628[arg0]] = 0;
        D_807706F8[D_80770628[arg0]] = 0;
    }

    if (D_80770740[D_80770628[arg0]] < 0 || D_80770740[D_80770628[arg0]] >= 23) {
        faultSetMessage(9, D_80770740[D_80770628[arg0]] * 1, 0, 0);  // FAKE: keeps count out of $a1
    }

    D_807707A0[D_80770628[arg0]][D_80770740[D_80770628[arg0]]] = -1;
    D_807705F8[arg0] = -1;
    D_807705A0[arg0] = NULL;
    D_80770628[arg0] = -1;
    D_80770658[arg0] = -1;
}
