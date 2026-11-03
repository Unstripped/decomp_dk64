// func_8003155C (src/menu/3E10.c): W3Sched 2026-11-02: unchanged stage-4 park, full=26 (count-exact 177, frame 0x38). ucode of the park: E1=mul $3,$16,4 coloured v1, E2a=mul $7,$3,4 (a3), E2b=sll $8,$3,2 spilled with p1 (0x2C/0x28 match); target has E1 as an UNcoloured ring temp t7 used twice (sll v1,t7,2 / sll t0,t7,2), E2a v1, first ring temp lb t6 (ours t7 because the two '(arg1*4)<<2' FAKE tests burn a ring step). New runs: template annealer over each of the 11 index/call sites in {arg1*4, 4*arg1, arg1<<2, k, k*4, m} x named locals k/m (s32/u32, m=k<<2 or k*4) x dead tests, T>0, 3 x 500 s: count-exact best 30; the 178-insn family reaches full 12 but needs frame 64 (two named locals). Plain hill-climb with 7 alts per site + line joins + 6 dead forms x 19 syms: 26 unchanged. The volatile 'ret' is emitted as '.set volatile; sw; .set novolatile' (target: plain sw s0,0x30(sp) + lw v0,0x30(sp)): the real source probably has no volatile; the spill is uopt's split of idx's tail piece (only 1 use, s-regs taken by arg0/arg2/arg3).
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
    volatile s32 ret;
    if ((arg1 * 4) << 2) {} // FAKE: extra reference of the shared (arg1 * 4) << 2 expression; steers its CSE candidate priority
    if ((arg1 * 4) << 2) {} // FAKE: second reference, same purpose (count-exact 177 insns; first one alone leaves 42)
    arg1 += ((MenuA_SelectorView *)arg0)->unk17;
    if (arg1 >= 5) {
        arg1 -= 5;
    }
    ret = arg1;
    (&D_8003378C[arg1 * 4])[2] = D_8003373C[arg1 * 4];
    D_8003373C[(arg1 * 4) + 2] = -D_8003378C[arg1 * 4];
    D_8003378C[(4 * arg1) + 3] = D_8003373C[(arg1 * 4) + 1];
    (&D_8003373C[arg1 * 4])[3] = -D_8003378C[(arg1 * 4) + 1];
    *arg2 = menuEvaluateSpline((f32 *)((u8 *)D_8003373C + ((arg1 * 4) << 2)), ((MenuA_SelectorView *)arg0)->unk4, NULL);
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
    return ret;
}
