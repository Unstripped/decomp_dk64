// func_80615DA4 (src/global/19A00.c): stage 3: compiled typed candidate; target frame is 0x28 versus candidate 0x30. Tried current shared state view; state-local allocation remains.
? func_80614F28(u8 *, void *, void *);              /* extern */
extern s32 D_807F5AF0;

s32 func_80615DA4(void *arg0) {
    u8 sp27;
    void *sp20;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    void *temp_a1;
    void *temp_a1_2;
    void *var_v1;

    temp_a1 = arg0->unk4;
    if (temp_a1->unk84 != 0) {
        var_v1 = temp_a1->unk4;
    } else {
        var_v1 = temp_a1->unk0;
    }
    sp20 = var_v1;
    D_807F5AF0 += 1;
    func_80614F28(&sp27, temp_a1, arg0);
    temp_v0 = sp20->unkC;
    temp_fv1 = sp20->unk4;
    sp20->unk1E = temp_v0;
    temp_fv0 = (f32) temp_v0;
    sp20->unk1C = (s16) (sp20->unk1C | 8);
    sp20->unk20 = (s16) sp27;
    if (temp_fv0 < temp_fv1) {
        sp20->unk8 = (f32) (temp_fv1 - temp_fv0);
    } else {
        sp20->unk8 = (f32) -(temp_fv1 - temp_fv0);
    }
    sp20->unkE = (s16) sp27;
    temp_a1_2 = arg0->unk4;
    temp_a1_2->unk78 = (s32) (temp_a1_2->unk78 | 0x20);
    return 1;
}
