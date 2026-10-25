// func_8071F660 (src/global/11BC10.c): Stage 1 m2c starter; matrix local declarations unresolved.
f32 func_80612794(s16);                             /* extern */
? func_80612CA0(f32 (*)[4], f32);                   /* extern */
extern u8 D_807444FC;

void func_8071F660(void *arg0, ? arg1) {
    f32 sp24;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = (f32) arg0->unk358 / (f32) (arg0->unk354 - 1);
    sp24 = temp_fv0;
    temp_fv1 = (f32) ((f64) func_80612794((s16) (s32) (temp_fv0 * 2048.0f)) * 3.0);
    arg0->unk360 = temp_fv1;
    arg0->unk364 = temp_fv1;
    guScaleF((f32 (*)[4]) &sp68[0], temp_fv1, temp_fv1, 0.0f);
    func_80612CA0((f32 (*)[4]) &sp28[0], sp24 * 180.0f);
    guMtxCatF((f32 (*)[4]) &sp68[0], (f32 (*)[4]) &sp28[0], (f32 (*)[4]) &sp68[0]);
    guMtxF2L((f32 (*)[4]) &sp68[0], arg0 + (D_807444FC << 6) + 0x128);
    arg0->unk32C = 2;
}
