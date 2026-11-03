// func_8003155C (src/menu/3E10.c): MenuA 2026-11-03 (revisit 8): stage 4 park full=15 text=16 shape=8, count-exact 177 (stored park was full=20). Return value stays in s0 (no ret spill: target spills s0 to 48(sp) and reloads it for return = 3 lines). Body: FAKE-top '(arg1*4)<<2' dead test + UNUSED 's32 ret;' local (declaring it matters: removing it 15->19, isvar id) + 'if (arg1 == 0) {}' + call-1 offset 'arg1 << 4', call-2 '(4*arg1)<<2' + index spellings 4*arg1/arg1*4/1+(4*arg1) (annealed 17k evals over 16 spelling sites incl. a 'm4' local, 4 seeds). Remaining: M4 (arg1*4) coloured t0 and spilled (target: uncoloured ring t7 shared by sll v1 and sll t0; E=M4<<2 coloured t0 shared by both calls), ring phase one step off. Other regime (ret=arg1 + 'arg1 = 0' FAKE in compare arm, W2Frame): shape 0 / full 26: only regs (M4 v1, M16 a3, ptrC t1). NEW tried, no gain: RHS cast wrappers {u8,s8,u16,s16,s32,u32,f32} at every assignment (1 and 2 sites, both regimes), pad locals 1-3 of 4 types x 3 positions, pointer-local form (pb/pc: 62), 8k-eval FAKE hill-climbs from both bases.
typedef struct MenuA_SelectorView {
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    char padE[9];
    s8 unk17;
} MenuA_SelectorView;

extern f32 D_8003373C[];
extern f32 D_8003378C[];
f32 menuEvaluateSpline(f32 *, f32, f32 *);

s32 func_8003155C(void *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5, s16 *arg6) {
    f32 v;
    s32 ret; // FAKE: unused local still takes an isvar id (19 -> 15)
    if ((arg1 * 4) << 2 && (arg1 * 4) << 2) {}  // FAKE: steers uopt candidate numbering / ring phase of arg1 * 4
    arg1 += ((MenuA_SelectorView *)arg0)->unk17;
    if (arg1 >= 5) {
        arg1 -= 5;
    }
    if (arg1 == 0) {} // FAKE: extra reference of arg1
    (&D_8003378C[4 * arg1])[2] = D_8003373C[arg1 * 4];
    D_8003373C[(4 * arg1) + 2] = -D_8003378C[4 * arg1];
    D_8003378C[(4 * arg1) + 3] = D_8003373C[1 + (4 * arg1)];
    (&D_8003373C[4 * arg1])[3] = -D_8003378C[1 + (arg1 * 4)];
    *arg2 = menuEvaluateSpline((f32 *)((u8 *)D_8003373C + (arg1 << 4)), ((MenuA_SelectorView *)arg0)->unk4, NULL);
    *arg3 = menuEvaluateSpline((f32 *)((u8 *)D_8003378C + ((4 * arg1) << 2)), ((MenuA_SelectorView *)arg0)->unk4, NULL);
    if (*arg3 < -40.0f) {
        v = -*arg3 - 40.0f;
        if (v > 20.0f) {
            v = 20.0f;
        }
        *arg4 = (v / 60.0f) + 1.0f;
        *arg5 = (s32)(v * 6.2f) + 0x80;
    } else {
        *arg4 = 1.0f;
        *arg5 = 0x80;
    }
    *arg6 = 0xFF;
    if (D_8003373C == &D_8003373C[4 * arg1]) {
        *arg3 *= 1.0f - D_80033F3C;
        *arg4 += D_80033F3C * 3.5f;
        if (D_80033F3C != 0.0f) {
            *arg6 = 0xFF - (s32)(((MenuA_SelectorView *)arg0)->unk0 * 255.0f);
            if (*arg6 < 0) {
                *arg6 = 0;
            }
        }
    }
    *arg2 *= 4.0f + (((MenuA_SelectorView *)arg0)->unk0 * 4.0f);
    *arg3 *= 4.0f + (((MenuA_SelectorView *)arg0)->unk0 * 4.0f);
    *arg2 += 640.0f;
    *arg3 += 480.0f;
    return arg1;
}
