// func_8071EEE0 (src/global/11BC10.c): stage 4: frame and state arithmetic match; matrix-call state spill/register allocation differs
void *func_80610FE8(?);                             /* extern */
? func_80612CA0(f32 (*)[4], s32);                   /* extern */
extern u8 D_807444FC;

void func_8071EEE0(void *arg0, ? arg1) {
    void *spAC;
    f32 temp_fv0;
    void *temp_v0;
    void *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0.01f;
        temp_v0->unk8 = 0.0f;
        temp_v0->unk4 = (f32) arg0->unk360;
        var_v1 = arg0->unk384;
    }
    temp_fv0 = var_v1->unk0;
    var_v1->unk8 = (f32) (var_v1->unk8 + 5.0f);
    var_v1->unk0 = (f32) (((f64) (var_v1->unk4 - temp_fv0) * 0.1) + (f64) temp_fv0);
    spAC = var_v1;
    guScaleF((f32 (*)[4]) &sp6C[0], arg0->unk360, arg0->unk364, 0.0f);
    func_80612CA0((f32 (*)[4]) &sp2C[0], spAC->unk8);
    guMtxCatF((f32 (*)[4]) &sp6C[0], (f32 (*)[4]) &sp2C[0], (f32 (*)[4]) &sp6C[0]);
    guMtxF2L((f32 (*)[4]) &sp6C[0], arg0 + (D_807444FC << 6) + 0x128);
    arg0->unk32C = 2;
}
