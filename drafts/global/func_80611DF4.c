// func_80611DF4 (src/global/16A20.c): stage 2: m2c starter; remaining diff not yet reduced
s32 func_80611D20(s16, s16);                        /* extern */

s16 func_80611DF4(s16 arg0) {
    s16 temp_a1;
    s16 var_a0;
    s16 var_a0_2;
    s32 temp_v0;

    temp_a1 = arg0;
    if (arg0 >= 0) {
        var_a0_2 = arg0;
    } else {
        var_a0_2 = -temp_a1;
    }
    arg0 = temp_a1;
    temp_v0 = func_80611D20(var_a0_2, temp_a1);
    if (arg0 >= 0) {
        var_a0 = 0x7FFF - temp_v0;
    } else {
        var_a0 = temp_v0 - 0x8000;
    }
    return var_a0;
}
