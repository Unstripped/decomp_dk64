// func_80718380 (src/global/11BC10.c): Stage-4 candidate has exact instruction stream and b0 frame; verify final rodata after adjacent candidates revert.
// func_80718380 draft: exact instruction stream in the private TU.
typedef f32 Ub2bMtxF[4][4];

void func_80718380(Ub2ActorView *arg0, s8 *arg1) {
    Ub2bMtxF sp70;
    Ub2bMtxF sp30;
    u32 temp_v1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(4);
        temp_v1 = (u32) (func_806119A0() % 36000U) / 100U;
        *(f32 *) arg0->unk384 = (f32) temp_v1;
    }
    guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp30, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    guRotateF(sp30, *(f32 *) arg0->unk384, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp70, sp30, sp70);
    guTranslateF(sp30, arg0->unk340, arg0->unk344, arg0->unk348);
    guMtxCatF(sp70, sp30, sp70);
    if ((s32) arg0->unk36D >= 0xA) {
        arg0->unk36D -= 0xA;
    } else {
        arg0->unk36D = 0U;
    }
    guMtxF2L(sp70, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 3;
    if (arg0->unk36D == 0) {
        *arg1 = 1;
    }
}
