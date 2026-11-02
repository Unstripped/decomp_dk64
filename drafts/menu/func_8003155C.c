// func_8003155C (src/menu/3E10.c): MenuA 2026-11-02: stage 4, COUNT-EXACT (177 insns, frame 0x38 + s0-s3), harness diff 26 (shape 0), parked in copy. Key: ALL index spellings uniform 'arg1 * 4' (the old 'arg1 * 2 * 2' for the 373C sites folds to 'sll 4' = 178 insns, diff 9) + two '(arg1 * 4) << 2' dead tests (one alone: 42). Remaining: uopt colours E1=arg1*4 first (v1) and the pointer-site index E2a=E1*4 a3; target has E2a=v1 (pointer sites 378C v0, 373C a3), E1 uncoloured ring t7, E2b=(arg1*4)<<2 for the call args in t0 (shared by both calls), 'lb t6' first ring temp. The 178-insn family (373C sites spelled arg1*2*2 or first call '(arg1<<2)*4') reaches diff 9-13 but is one insn over. Tried: 5 annealers (~90k evals) over index/access/call/compare spellings x dead tests, named idx local (30), local i for arg1 (66, 175 insns), RHS wrappers (no gain), hill-climb of 15 dead forms.
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
