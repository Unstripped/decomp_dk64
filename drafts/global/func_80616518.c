// func_80616518 (src/global/19A00.c): stage 3: m2c behavioural starter; typed view candidate compiled and fdiff'd, remaining frame/register allocation and source-order differences
? func_80614F4C(u16 *, void *);                     /* extern */
extern s32 D_807F5AF0;

s32 func_80616518(void *arg0) {
    u16 sp26;
    void *sp20;
    void *temp_v0;
    void *var_v1;

    temp_v0 = arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_v1 = temp_v0->unk4;
    } else {
        var_v1 = temp_v0->unk0;
    }
    sp20 = var_v1;
    D_807F5AF0 += 1;
    func_80614F4C(&sp26, arg0);
    arg0->unk4->unk88 = (s32) (sp20->unk10 - sp26);
    return 1;
}
