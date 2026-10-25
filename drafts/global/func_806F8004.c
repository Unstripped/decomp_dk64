// func_806F8004 (src/global/FCCD0.c): m2c behavioural starter; 91-insn matrix transform requires local view struct and stage work.
extern s32 D_807FC924;
extern u8 D_807FC929;

void func_806F8004(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp34;
    f32 sp30;
    f32 temp_fv1;
    f32 temp_fv1_2;

    sp34 = (D_807FC924 + (D_807FC929 * 0x2F0))->unk284;
    guRotateF((f32 (*)[4]) &sp88[0], arg0, 1.0f, 0.0f, 0.0f);
    temp_fv1 = -sp34;
    sp30 = temp_fv1;
    guMtxXFMF((f32 (*)[4]) &sp88[0], 0.0f, 0.0f, temp_fv1, &sp3C, &sp40, &sp44);
    guRotateF((f32 (*)[4]) &sp48[0], arg1, 0.0f, 1.0f, 0.0f);
    guMtxXFMF((f32 (*)[4]) &sp48[0], sp3C, sp40, sp44, arg2, arg3, arg4);
    temp_fv1_2 = sp30 / *arg4;
    *arg2 *= temp_fv1_2;
    *arg3 *= temp_fv1_2;
    *arg4 = sp30;
    *arg2 = (f32) ((f64) *arg2 * 10.5);
    *arg3 = (f32) ((f64) *arg3 * 10.5);
    *arg4 = (f32) ((f64) *arg4 * 10.5);
}
