// func_8003155C (src/menu/3E10.c): W3Sched 2026-11-02: stage 4, COUNT-EXACT (177, frame 0x38), full=20 (was 26), FAKE-free and NO volatile (parked in copy). The volatile 'ret' was unnecessary: plain 'return arg1;' gives 176 insns, but with index spelling '(&D_8003373C[4 * arg1])[3] = -D_8003378C[(4 * arg1) + 1];' and call arg '((arg1 << 2) << 2)' (first call) the natural tail spill appears (sw s0,0x30(sp)/lw v0) at 177. Remaining: ring phase (lb t7 vs t6), E1 coloured v1 vs target uncoloured t7, E2a a3 vs v1. Annealing (T>0, 31k evals x3, 28k x4) from it: no lower.
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
    arg1 += ((MenuA_SelectorView *)arg0)->unk17;
    if (arg1 >= 5) {
        arg1 -= 5;
    }
    (&D_8003378C[arg1 * 4])[2] = D_8003373C[arg1 * 4];
    D_8003373C[(arg1 * 4) + 2] = -D_8003378C[arg1 * 4];
    D_8003378C[(4 * arg1) + 3] = D_8003373C[(arg1 * 4) + 1];
    (&D_8003373C[4 * arg1])[3] = -D_8003378C[(4 * arg1) + 1];
    *arg2 = menuEvaluateSpline((f32 *)((u8 *)D_8003373C + ((arg1 << 2) << 2)), ((MenuA_SelectorView *)arg0)->unk4, NULL);
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
