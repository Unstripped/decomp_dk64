// func_80615C34 (src/global/19A00.c): stage 3: m2c behavioural starter; typed view candidate compiled and fdiff'd, remaining frame/register allocation and source-order differences
? func_80614644(void *, s32, f32, void *);          /* extern */
? func_80614F28(u8 *, s32, void *);                 /* extern */
extern s32 D_807F5AF0;

s32 func_80615C34(void *arg0) {
    u8 sp27;
    s32 sp20;
    f32 var_ft0;
    s32 var_a1;
    void *temp_v0;

    temp_v0 = arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_a1 = temp_v0->unk4;
    } else {
        var_a1 = temp_v0->unk0;
    }
    sp20 = var_a1;
    D_807F5AF0 += 1;
    func_80614F28(&sp27, var_a1, arg0);
    if (sp27 == 0xFF) {
        sp27 = (u8) arg0->unk4->unk88;
    }
    var_ft0 = (f32) sp27;
    if ((s32) sp27 < 0) {
        var_ft0 += 4294967296.0f;
    }
    func_80614644(arg0, sp20, var_ft0, arg0);
    return 1;
}
