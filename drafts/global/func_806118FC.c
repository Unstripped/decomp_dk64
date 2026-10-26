// func_806118FC (src/global/16550.c): stage 2: m2c starter; remaining diff not yet reduced
s32 func_80611DF4(s16);                             /* extern */

f32 func_806118FC(f32 arg0) {
    s16 var_a0;

    if (arg0 >= 1.0f) {
        var_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        var_a0 = -0x7FFF;
    } else {
        var_a0 = (s16) (s32) (arg0 * 32767.0f);
    }
    return ((f32) func_80611DF4(var_a0) * 3.1415927f) / 65535.0f;
}
