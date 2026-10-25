// func_807195D4 (src/global/11BC10.c): Stage 4: compiled behavioral draft reaches target frame and blocks; local scalar/temporary layout shifts matrices by 8 bytes and floating register allocation differs.
typedef struct {
    f32 unk0;
    f32 unk4;
} Ub3TwoFloats;

void func_807195D4(Ub2ActorView *arg0, s8 *arg1) {
    f32 spB0;
    Ub2bMtxF sp6C;
    Ub2bMtxF sp2C;
    f32 temp_fv0;

    if (arg0->unk384 == NULL) {
        Ub3TwoFloats *temp_v0;

        temp_v0 = func_80610FE8(8);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (f32) (arg0->unk35C * 2);
        ((Ub3TwoFloats *) arg0->unk384)->unk4 = 0.0f;
        arg0->unk36D = 0U;
    }
    if ((s32) arg0->unk36D >= 0xDD) {
        arg0->unk36D = 0xFFU;
    } else {
        arg0->unk36D += 0x14;
    }
    spB0 = (f32) ((f64) func_80612D1C(((Ub3TwoFloats *) arg0->unk384)->unk0 * 0.017453292f) * 2.5);
    temp_fv0 = func_80612D10(((Ub3TwoFloats *) arg0->unk384)->unk0 * 0.017453292f);
    arg0->unk340 = (f32) (arg0->unk340 + spB0);
    arg0->unk344 = (f32) ((f64) arg0->unk344 + 3.5);
    arg0->unk348 = (f32) (arg0->unk348 + (f32) ((f64) temp_fv0 * 2.5));
    ((Ub3TwoFloats *) arg0->unk384)->unk0 = (f32) ((f64) ((Ub3TwoFloats *) arg0->unk384)->unk0 + 8.0);
    ((Ub3TwoFloats *) arg0->unk384)->unk4 = (f32) ((f64) ((Ub3TwoFloats *) arg0->unk384)->unk4 + 7.3);
    guScaleF(sp6C, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp2C, ((Ub3TwoFloats *) arg0->unk384)->unk4, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp6C, sp2C, sp6C);
    guMtxF2L(sp6C, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 2;
}
