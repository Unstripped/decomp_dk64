// func_8062A944 (src/global/2F550.c): OlR2a: stage 5, harness diff 181 (was 244 on the old park, whole-TU variant harness). Gain: re-expanding '(-arg2)' instead of negZ in 3 stores (D_807F5DF8/E10/E1C = (-arg2)) via a 2^10 subset search of the 10 negZ uses. Still left: fp colour order f20=0.0,f22=negZ (target f20=negZ,f22=0.0; uneg cand adjsave 2.75 < const 0.0 3.75) plus spill homes (0x54/0x4C/0x48 vs 0x58/0x54/0x4C). Tried on top: zero local for any subset of the 16 0.0f (255 subsets), sp4C inline, scale=(-arg2)/D, store order swaps, local decl order swaps, (0,0.0f) wraps: no further gain.
extern f32 D_807F5DF0;
extern f32 D_807F5DF4;
extern f32 D_807F5DF8;
extern f32 D_807F5DFC;
extern f32 D_807F5E00;
extern f32 D_807F5E04;
extern f32 D_807F5E08;
extern f32 D_807F5E0C;
extern f32 D_807F5E10;
extern f32 D_807F5E14;
extern f32 D_807F5E18;
extern f32 D_807F5E1C;

void func_8062A944(f32 arg0, f32 arg1, f32 arg2) {
    f32 negZ;
    f32 scale;
    f32 spB0[4][4];
    f32 sp70[4][4];
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp58;
    f32 sp54;
    f32 sp4C;

    sp58 = arg0 * 0.5;
    guRotateF(spB0, sp58, 1.0f, 0.0f, 0.0f);
    negZ = -arg2;
    guMtxXFMF(spB0, 0.0f, 0.0f, negZ, &sp64, &sp68, &sp6C);
    sp54 = sp58 * arg1;
    guRotateF(sp70, sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DF0, &D_807F5DF4, &D_807F5DF8);
    sp4C = -sp54;
    guRotateF(sp70, sp4C, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5DFC, &D_807F5E00, &D_807F5E04);
    guRotateF(spB0, -sp58, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(spB0, 0.0f, 0.0f, negZ, &sp64, &sp68, &sp6C);
    guRotateF(sp70, sp54, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5E08, &D_807F5E0C, &D_807F5E10);
    guRotateF(sp70, sp4C, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp70, sp64, sp68, sp6C, &D_807F5E14, &D_807F5E18, &D_807F5E1C);
    scale = negZ / D_807F5DF8;
    D_807F5DF0 *= scale;
    D_807F5DF4 *= scale;
    D_807F5DF8 = (-arg2); // FAKE: re-expands -arg2 so uopt colours the neg expression
    scale = negZ / D_807F5E04;
    D_807F5DFC *= scale;
    D_807F5E00 *= scale;
    D_807F5E04 = negZ;
    scale = negZ / D_807F5E10;
    D_807F5E08 *= scale;
    D_807F5E0C *= scale;
    D_807F5E10 = (-arg2); // FAKE: re-expands -arg2 so uopt colours the neg expression
    scale = negZ / D_807F5E1C;
    D_807F5E14 *= scale;
    D_807F5E18 *= scale;
    D_807F5E1C = (-arg2); // FAKE: re-expands -arg2 so uopt colours the neg expression
}
