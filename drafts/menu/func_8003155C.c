// func_8003155C (src/menu/3E10.c): W2Frame 2026-11-03 (revisit 7 wave 2): MenuA body + 'if ((arg1 * 4) << 2 && (arg1 * 4) << 2) {}' (FAKE, first statement) = COUNT-EXACT 177, shape 0 (registers only), full 26 (stored park in src full=20 is structurally off: count compensated; keep it unless this gets < 20). Re-derived roles: target has arg1*4 (M4) as an UNCOLOURED ring temp t7 shared by 'sll v1,t7,2' (arg1*16, uixa scale, coloured v1) and 'sll t0,t7,2' (call byte offset, spilled 44(sp), shared by both calls); ours colours M4 (v1) first (adjsave 3.0 == M16 3.0, ties go to the lower candidate bit) so M16 -> a3, C -> t1, B -> t0 and the whole ring is one step off. Levers: call-1 offset spelled '(arg1<<2)<<2' gives target-like v1/t0 but count 178 (non-shared offset); 3^7 grids of index spellings (arg1*4 / 4*arg1 / arg1<<2) at 7 sites, expression dead-test forms, 17k-eval anneals from both the MenuA and the stored park bodies. Needs: M4 uncoloured / M16 coloured before M4 (M16 needs adjsave > 3.0).
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
    s32 ret;
    if ((arg1 * 4) << 2 && (arg1 * 4) << 2) {}  // FAKE: burns ugen ring temps / numbers uopt candidates (M4 phase)
    arg1 += ((MenuA_SelectorView *)arg0)->unk17;
    if (arg1 >= 5) {
        arg1 -= 5;
    }
    if (arg1 == 0) {}
    ret = arg1;
    (&D_8003378C[arg1 * 4])[2] = D_8003373C[arg1 * 4];
    D_8003373C[(arg1 * 4) + 2] = -D_8003378C[arg1 * 4];
    D_8003378C[(4 * arg1) + 3] = D_8003373C[(arg1 * 4) + 1];
    (&D_8003373C[arg1 * 4])[3] = -D_8003378C[(arg1 * 4) + 1];
    *arg2 = menuEvaluateSpline((f32 *)((u8 *)D_8003373C + ((4 * arg1) << 2)), ((MenuA_SelectorView *)arg0)->unk4, NULL);
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
        arg1 = 0; // FAKE: x
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
