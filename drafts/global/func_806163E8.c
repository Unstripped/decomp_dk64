// func_806163E8 (src/global/19A00.c): stage 3: m2c behavioural starter; typed view candidate compiled and fdiff'd, remaining frame/register allocation and source-order differences
? func_80614FD8(f32 *, void *);                     /* extern */
extern s32 D_807F5AF0;

s32 func_806163E8(void *arg0) {
    f32 sp24;
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
    func_80614FD8(&sp24, arg0);
    arg0->unk4->unk88 = (s32) (sp20->unk4 - sp24);
    return 1;
}
