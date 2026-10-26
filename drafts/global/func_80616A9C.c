// func_80616A9C (src/global/19A00.c): stage 3: f64 conversion expression and local stack layout remain unresolved
? func_80609140(s16, s32, f32, f32, s32, s32);      /* extern */
? func_80614F28(u8 *);                              /* extern */
? func_80614F4C(s16 *);                             /* extern */
extern s32 D_807F5AF0;

s32 func_80616A9C(s32 arg0) {
    s16 sp26;
    u8 sp25;
    s16 sp22;
    u8 sp21;
    u8 sp20;
    f32 var_ft1_2;
    f64 var_ft1;

    D_807F5AF0 += 1;
    func_80614F4C(&sp26);
    func_80614F28(&sp25);
    func_80614F28(&sp20);
    func_80614F4C(&sp22);
    func_80614F28(&sp21);
    var_ft1 = (f64) sp25;
    if ((s32) sp25 < 0) {
        var_ft1 += 4294967296.0;
    }
    var_ft1_2 = (f32) sp20;
    if ((s32) sp20 < 0) {
        var_ft1_2 += 4294967296.0f;
    }
    func_80609140(sp26, (s32) ((var_ft1 * 32767.0) / 255.0), var_ft1_2, (f32) ((f64) sp22 / 127.0), (s32) sp21, 0);
    return 1;
}
