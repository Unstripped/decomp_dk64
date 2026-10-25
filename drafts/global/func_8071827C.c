// func_8071827C (src/global/11BC10.c): Exact instruction stream; literal 0.07 creates a TU-local rodata relocation rather than D_8075E748, while externing it adds loads.
// func_8071827C draft: exact instruction stream; f64 0.07 emits a TU-local rodata relocation instead of D_8075E748.
typedef f32 Ub2bMtxF[4][4];

void func_8071827C(Ub2ActorView *arg0, s8 *arg1) {
    Ub2bMtxF sp70;
    Ub2bMtxF sp30;
    u8 temp_v0;

    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    guTranslateF(sp30, arg0->unk340, arg0->unk344, arg0->unk348);
    guMtxCatF(sp70, sp30, sp70);
    temp_v0 = arg0->unk36D;
    arg0->unk360 = (f32) ((f64) arg0->unk360 + 0.07);
    arg0->unk364 = (f32) ((f64) arg0->unk364 + 0.07);
    if ((s32) temp_v0 >= 0xA) {
        arg0->unk36D = (u8) (temp_v0 - 0xA);
    } else {
        arg0->unk36D = 0U;
    }
    guMtxF2L(sp70, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 3;
}
