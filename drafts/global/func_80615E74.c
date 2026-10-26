// func_80615E74 (src/global/19A00.c): stage 3: m2c behavioural starter; typed view candidate compiled and fdiff'd, remaining frame/register allocation and source-order differences
? func_80614F28(u8 *);                              /* extern */
extern s32 D_807F5AF0;

s32 func_80615E74(void *arg0) {
    u8 sp2F;
    u8 sp2E;
    void *sp28;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v1_2;
    void *temp_v1;
    void *temp_v1_3;
    void *var_v0;

    temp_v1 = arg0->unk4;
    if (temp_v1->unk84 != 0) {
        var_v0 = temp_v1->unk4;
    } else {
        var_v0 = temp_v1->unk0;
    }
    sp28 = var_v0;
    D_807F5AF0 += 1;
    func_80614F28(&sp2F);
    func_80614F28(&sp2E);
    temp_v1_2 = sp28->unkC;
    if (sp2F == temp_v1_2) {
        temp_fv1 = sp28->unk4;
        temp_fv0 = (f32) temp_v1_2;
        sp28->unk1E = temp_v1_2;
        sp28->unk1C = (s16) (sp28->unk1C | 8);
        sp28->unk20 = (s16) sp2E;
        if (temp_fv0 < temp_fv1) {
            sp28->unk8 = (f32) (temp_fv1 - temp_fv0);
        } else {
            sp28->unk8 = (f32) -(temp_fv1 - temp_fv0);
        }
        sp28->unkE = (s16) sp2E;
        temp_v1_3 = arg0->unk4;
        temp_v1_3->unk78 = (s32) (temp_v1_3->unk78 | 0x20);
    } else {
        sp28->unkC = (s16) ((temp_v1_2 + sp2E) - sp2F);
        sp28->unkE = (s16) ((sp28->unkE + sp2E) - sp2F);
        sp28->unk4 = (f32) (sp28->unk4 + (f32) (sp2E - sp2F));
    }
    return 1;
}
