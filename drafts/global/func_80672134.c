// func_80672134 (src/global/70FD0.c): Unattempted starter draft from m2c (actor path / waypoint coordinate step)
s16 func_80672A70(s16, s16, s16, s16);              /* extern */

s16 func_80672134(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 sp1E;
    f32 var_fv1;
    f64 var_fv0;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 var_a1;
    s16 var_a3;
    s16 var_v0;

    temp_a0 = arg0;
    if (arg1 >= arg0) {
        if ((arg2 >= arg0) && (arg1 >= arg2)) {
            return 0x270F;
        }
        goto block_7;
    }
    if ((arg2 >= temp_a0) || (arg1 >= arg2)) {
        return 0x270F;
    }
block_7:
    temp_v0 = arg2 + 0x800;
    var_a3 = temp_v0;
    if (temp_v0 >= 0x1000) {
        var_a3 = temp_v0 - 0x1000;
    }
    arg0 = temp_a0;
    sp1E = var_a3;
    temp_v0_2 = func_80672A70(temp_a0, arg1, arg2, var_a3);
    if ((arg0 - temp_v0_2) > 0) {
        var_a1 = arg0 - temp_v0_2;
    } else {
        var_a1 = (arg0 - temp_v0_2) * -1;
    }
    temp_a0_2 = var_a3 - temp_v0_2;
    if (var_a1 >= 0x800) {
        var_a1 = 0xFFF - var_a1;
    }
    if (temp_a0_2 > 0) {
        var_v0 = temp_a0_2;
    } else {
        var_v0 = temp_a0_2 * -1;
    }
    if (var_v0 >= 0x800) {
        var_v0 = 0xFFF - var_v0;
    }
    if (var_a1 != 0) {
        var_fv1 = (f32) var_v0 / (f32) var_a1;
    } else {
        var_fv1 = 0.0f;
    }
    var_fv0 = (f64) var_fv1;
    if (var_fv0 > 1.0) {
        var_fv1 = 1.0f;
        var_fv0 = (f64) 1.0f;
    }
    if (var_fv0 < 0.2) {
        var_fv1 = 0.0f;
    }
    return (s16) (s32) ((f32) arg3 * var_fv1);
}
