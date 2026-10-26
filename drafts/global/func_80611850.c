// func_80611850 (src/global/16550.c): stage 4: five fdiff candidates (m2c, ternary, permuter best, pointer alias, declaration order); exact 43-instruction shape/frame, only FPR allocation remains (target f4/f6/f8/f10/f16 vs f2/f4/f6/f8/f10). uopt level 6 traced; permuter -j2 --seconds 600 best score 60.
s32 func_80611DA0(s16);

f32 func_80611850(f32 arg0) {
    f32 var_ft0;
    s32 new_var;
    s16 var_a0;
    s32 temp_v0;

    new_var = (s32)(arg0 * 32767.0f);
    if (arg0 >= 1.0f) {
        var_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        var_a0 = -0x7FFF;
    } else {
        var_a0 = (s16)new_var;
    }
    temp_v0 = func_80611DA0(var_a0);
    var_ft0 = (f32)temp_v0;
    if (temp_v0 < 0) {
        var_ft0 += 4294967296;
    }
    return (var_ft0 * 3.1415927f) / 65535.0f;
}
