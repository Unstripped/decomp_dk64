// func_806F8004 (src/global/FCCD0.c): Stage 4: 900-second stack permutation found a score-41 candidate (direct fdiff score 51); remaining mismatch is the initial source/negated scalar register and stack placement.
typedef struct R2FCCD0ePlayer {
    u8 pad0[0x284];
    f32 unk284;
    u8 pad288[0x68];
} R2FCCD0ePlayer;

void func_806F8004(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    f32 sp88[4][4];
    f32 sp48[4][4];
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp34;
    f32 sp30;

    sp34 = ((R2FCCD0ePlayer *)D_807FC924)[D_807FC929].unk284;
    guRotateF(sp88, arg0, 1.0f, 0.0f, 0.0f);
    sp30 = -sp34;
    sp34++;
    sp34--;
    guMtxXFMF(sp88, 0.0f, 0.0f, sp30, &sp3C, &sp40, &sp44);
    guRotateF(sp48, arg1, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp48, sp3C, sp40, sp44, arg2, arg3, arg4);
    sp34 = sp30 / *arg4;
    *arg2 *= sp34;
    *arg3 *= sp34;
    *arg4 = sp30;
    *arg2 = (f32)((f64)*arg2 * 10.5);
    *arg3 = (f32)((f64)*arg3 * 10.5);
    *arg4 = (f32)((f64)*arg4 * 10.5);
}
