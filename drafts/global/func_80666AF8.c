// func_80666AF8 (src/global/699B0.c): starter m2c, collision bounding/surface processing
f32 func_80611BB4(f32, f32, u8);                    /* extern */
extern ? D_807F9490;
extern ? D_807F9498;
extern ? D_807F949E;
extern s16 D_807F94A6;
extern s16 D_807F94A8;

void func_80666AF8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    f32 temp_fv0_2;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fa1;
    f64 temp_fv0;
    s16 var_v0_2;
    s16 var_v0_3;
    u8 var_a0;
    u8 var_v0;

    var_a0 = arg4;
    var_v0 = var_a0;
    if (var_a0 == 0xFF) {
        var_a0 = 0;
        var_v0 = 0;
    }
    if (var_v0 == 0xFE) {
        var_a0 = 0;
    }
    *(&D_807F949E + arg6) = var_a0;
    if (arg3 > 0.0f) {
        var_fa1 = arg3;
    } else {
        var_fa1 = -arg3;
    }
    if ((f64) var_fa1 < 0.01) {
        var_v0_2 = 0x400;
    } else {
        if (arg1 > 0.0f) {
            var_fa0 = arg1;
        } else {
            var_fa0 = -arg1;
        }
        var_v0_2 = (s16) (s32) ((func_80611BB4(var_fa0, var_fa1, var_a0) / 3.1415927f) * 2048.0f);
    }
    temp_fv0 = (f64) arg1;
    if ((temp_fv0 >= 0.0) && ((f64) arg3 >= 0.0)) {
        var_v0_2 -= 0x800;
    } else if ((temp_fv0 >= 0.0) && ((f64) arg3 < 0.0)) {
        var_v0_2 *= -1;
    } else if ((temp_fv0 < 0.0) && ((f64) arg3 >= 0.0)) {
        var_v0_2 = 0x800 - var_v0_2;
    }
    if (arg5 != 0) {
        *(&D_807F9490 + (arg6 * 2)) = var_v0_2 & 0xFFF;
    }
    D_807F94A6 = var_v0_2 & 0xFFF;
    temp_fv0_2 = sqrtf((arg1 * arg1) + (arg3 * arg3));
    if ((f64) temp_fv0_2 < 0.01) {
        var_v0_3 = 0x400;
    } else {
        if (arg2 > 0.0f) {
            var_fa0_2 = arg2;
        } else {
            var_fa0_2 = -arg2;
        }
        var_v0_3 = (s16) (s32) ((func_80611BB4(var_fa0_2, temp_fv0_2) / 3.1415927f) * 2048.0f);
    }
    if (arg5 != 0) {
        *(&D_807F9498 + (arg6 * 2)) = var_v0_3;
    }
    D_807F94A8 = var_v0_3;
}
