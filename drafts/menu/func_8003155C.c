// func_8003155C (src/menu/3E10.c): MenuA 2026-11-03 (revisit 7): stage 4, COUNT-EXACT (177), frame 0x38, full=42 shape=4 (stored park in src is full=20, count-exact; this body is the structurally closer one). KEY NEW LEVER: the target's tail spill (sw s0,0x30(sp) after the join / lw v0,0x30(sp) at return) is a separate returned local: 'ret = arg1;' right after the wrap, a dead redefinition 'arg1 = 0; // FAKE' as the first statement of the final 'if (D_8003373C == &D_8003373C[4*arg1])' body (stops copy-propagation of ret; ret conflicts with arg1 so uopt leaves it uncoloured and spills at def), and 'return ret;'. Also fixed: s-reg order (target s0=arg1 s1=arg3) needs one dead test 'if (arg1 == 0) {}' after the wrap (raises arg1 priority over arg3); both calls spelled ((4 * arg1) << 2) share one E_C=shl(E_A,2) candidate (t0, spilled around call 1) exactly like the target (a3 uixa D373C spilled, E_B=umpy(E_A,4)). Remaining diff is ONE root cause: E_A=umpy(arg1,4) is a coloured uopt candidate here (v1, adjsave 3.0, coloured before E_B) where the target keeps it an uncoloured ring temp (t7) and E_B v1, uixa2 a3, E_C t0, lda D373C t1 (everything else follows from that: registers only). cfe/ugen fold mpy(mpy(arg1,4),4) to sll 4 when E_A is not a candidate, so E_A must stay a candidate with adjsave<=0 (-ve save). Tried: arg1 var/idx local (m4/m5), (u8*)D+off accesses (all addresses CSE into pointers), arg1<<4 / *16 calls (E_B folds), annealing 13k evals count-exact (best 42), deadsweep sweep (38). A count-off body (178, call 1 spelled (arg1<<2)<<2) reaches full=13 (/tmp an155z_best): E_A t0 spilled, first call folded sll 4.
typedef struct MenuSelectorView {
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    char padE[9];
    s8 unk17;
} MenuSelectorView;

extern f32 D_8003373C[];
extern f32 D_8003378C[];
f32 menuEvaluateSpline(f32 *, f32, f32 *);

s32 func_8003155C(void *arg0, s32 arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5, s16 *arg6) {
    f32 v;
    s32 ret;
    arg1 += ((MenuSelectorView *)arg0)->unk17;
    if (arg1 >= 5) {
        arg1 -= 5;
    }
    if (arg1 == 0) {}
    ret = arg1;
    (&D_8003378C[arg1 * 4])[2] = D_8003373C[arg1 * 4];
    D_8003373C[(arg1 * 4) + 2] = -D_8003378C[arg1 * 4];
    D_8003378C[(4 * arg1) + 3] = D_8003373C[(arg1 * 4) + 1];
    (&D_8003373C[arg1 * 4])[3] = -D_8003378C[(arg1 * 4) + 1];
    *arg2 = menuEvaluateSpline((f32 *)((u8 *)D_8003373C + ((4 * arg1) << 2)), ((MenuSelectorView *)arg0)->unk4, NULL);
    *arg3 = menuEvaluateSpline((f32 *)((u8 *)D_8003378C + ((4 * arg1) << 2)), ((MenuSelectorView *)arg0)->unk4, NULL);
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
        arg1 = 0; // FAKE: x
        *arg3 *= 1.0f - D_80033F3C;
        *arg4 += D_80033F3C * 3.5f;
        if (D_80033F3C != 0.0f) {
            *arg6 = 0xFF - (s32)(((MenuSelectorView *)arg0)->unk0 * 255.0f);
            if (*arg6 < 0) {
                *arg6 = 0;
            }
        }
    }
    *arg2 *= 4.0f + (((MenuSelectorView *)arg0)->unk0 * 4.0f);
    *arg3 *= 4.0f + (((MenuSelectorView *)arg0)->unk0 * 4.0f);
    *arg2 += 640.0f;
    *arg3 += 480.0f;
    return ret;
}
