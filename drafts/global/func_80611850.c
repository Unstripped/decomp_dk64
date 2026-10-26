// func_80611850 (src/global/16550.c): stage 2: m2c candidate; requires correct narrow sine-table helper return type.
s32 func_80611DA0(s16);                             /* extern */

f32 func_80611850(f32 arg0) {
    f32 var_ft0;
    s16 var_a0;
    s32 temp_v0;

    if (arg0 >= 1.0f) {
        var_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        var_a0 = -0x7FFF;
    } else {
        var_a0 = (s16) (s32) (arg0 * 32767.0f);
    }
    temp_v0 = func_80611DA0(var_a0);
    var_ft0 = (f32) temp_v0;
    if (temp_v0 < 0) {
        var_ft0 += 4294967296.0f;
    }
    return (var_ft0 * 3.1415927f) / 65535.0f;
}
