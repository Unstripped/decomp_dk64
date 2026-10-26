// func_80611DF4 (src/global/16A20.c): stage 4: exact frame, control flow, stack homes, and size; remaining result live range in v1 rather than target a0
s32 func_80611D20(s32);

s16 func_80611DF4(s16 arg0) {
    s32 var_a0;
    s32 var_a0_2;
    s32 temp_v0;

    if (arg0 >= 0) {
        var_a0_2 = arg0;
    } else {
        var_a0_2 = -arg0;
    }
    temp_v0 = func_80611D20(var_a0_2);
    if (arg0 >= 0) {
        var_a0 = 0x7FFF - temp_v0;
    } else {
        var_a0 = temp_v0 - 0x8000;
    }
    return var_a0;
}
