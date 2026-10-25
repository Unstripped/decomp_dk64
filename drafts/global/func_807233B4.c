// func_807233B4 (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
? func_80723428(s32);                               /* extern */
extern s32 *D_807FDBF8;

void func_807233B4(s32 arg0) {
    s32 **var_s1;
    s32 *temp_v0;
    s32 var_s0;

    var_s1 = &D_807FDBF8;
    var_s0 = 0;
    do {
        temp_v0 = *var_s1;
        if ((temp_v0 != NULL) && (arg0 == *temp_v0)) {
            func_80723428(var_s0);
        }
        var_s0 += 1;
        var_s1 += 4;
    } while (var_s0 != 0x20);
}
