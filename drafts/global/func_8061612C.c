// func_8061612C (src/global/19A00.c): stage 3: compiled typed candidate; state selection and parameter frame/register allocation remain.
? func_80614FD8(f32 *);                             /* extern */
extern s32 D_807F5AF0;

s32 func_8061612C(void *arg0) {
    f32 sp24;
    f32 sp20;
    void *sp1C;
    void *temp_v1;
    void *var_v0;

    temp_v1 = arg0->unk4;
    if (temp_v1->unk84 != 0) {
        var_v0 = temp_v1->unk4;
    } else {
        var_v0 = temp_v1->unk0;
    }
    sp1C = var_v0;
    D_807F5AF0 += 1;
    func_80614FD8(&sp24);
    func_80614FD8(&sp20);
    if (sp20 > 0.0f) {
        sp1C->unk34 = sp20;
        sp1C->unk30 = 0.0f;
        sp1C->unk2C = sp24;
        sp1C->unk28 = (f32) sp1C->unk24;
    } else {
        sp1C->unk24 = sp24;
        sp1C->unk34 = 0.0f;
    }
    return 1;
}
