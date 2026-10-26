// func_80615FA0 (src/global/19A00.c): stage 3: m2c behavioural starter; typed view candidate compiled and fdiff'd, remaining frame/register allocation and source-order differences
? func_80614F4C(s16 *);                             /* extern */
extern s32 D_807F5AF0;

s32 func_80615FA0(void *arg0) {
    s16 sp26;
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
    func_80614F4C(&sp26);
    sp20->unk1C = (s16) (sp20->unk1C | sp26);
    return 1;
}
