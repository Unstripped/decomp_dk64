// func_8061522C (src/global/19A00.c): stage 4: typed random-range candidate compiled with target frame; remaining local byte offsets and register allocation
// Stage 2: m2c behavioral starter; remaining diff: RNG prototype, state view, modulo expression.
s32 func_80611A44();
void func_80614F28(u8 *arg0);
extern u8 *D_807F5AF0;

s32 func_8061522C(void *arg0) {
    u8 sp1E;
    u8 sp1D;
    s32 temp_a0;
    s32 var_v0;
    void *temp_v1;

    D_807F5AF0 += 1;
    func_80614F28(&sp1E);
    func_80614F28(&sp1D);
    var_v0 = 1;
    temp_a0 = ((s32)((s32)(func_80611A44() >> 0xF) % 32767) % (s32)((sp1D - sp1E) + 1)) + sp1E;
    if (temp_a0 & 0xFF) {
        var_v0 = 0;
        arg0->unk4->unk7C = (s32)((temp_a0 & 0xFF) - 1);
        temp_v1 = arg0->unk4;
        temp_v1->unk78 = (s32)(temp_v1->unk78 | 2);
    }
    return var_v0;
}
