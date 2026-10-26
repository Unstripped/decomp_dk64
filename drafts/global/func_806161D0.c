// func_806161D0 (src/global/19A00.c): stage 3: compiled typed candidate; state selection and float negation scheduling remain.
extern s32 D_807F5AF0;

s32 func_806161D0(void *arg0) {
    f32 temp_fv0;
    void *temp_v0;
    void *var_v1;

    temp_v0 = arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_v1 = temp_v0->unk4;
    } else {
        var_v1 = temp_v0->unk0;
    }
    D_807F5AF0 += 1;
    temp_fv0 = var_v1->unk24;
    if (temp_fv0 < 0.0f) {
        var_v1->unk24 = (f32) (0.0f - temp_fv0);
        if (var_v1->unk34 != 0.0f) {
            var_v1->unk2C = (f32) (0.0f - var_v1->unk2C);
            var_v1->unk28 = (f32) (0.0f - var_v1->unk28);
        }
    }
    return 1;
}
