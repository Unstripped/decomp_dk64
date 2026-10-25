// func_80724154 (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
f32 func_80724308(f32, f32, s32, ?, f32, f32, s32, f32); /* extern */
extern ? D_807FDB90;

s32 func_80724154(s32 arg0, ? arg1, f32 arg2, f32 arg3, s32 *arg4, f32 *arg5) {
    f32 temp_fv0;
    f32 var_fs1;
    f32 var_fs4;
    s32 var_s0;
    s32 var_s1;
    s32 var_v0;

    var_fs4 = 999999.0f;
    var_fs1 = (f32) ((f64) *arg5 - 0.5);
    var_v0 = 0x14;
    var_s0 = *arg4;
    if ((f64) var_fs1 < 0.0) {
        if (var_s0 > 0) {
            var_s0 -= 1;
            var_fs1 += 1.0f;
        } else {
            var_fs1 = 0.0f;
        }
    }
    var_s1 = 0x13;
    if (0x14 != 0) {
        do {
            temp_fv0 = func_80724308(arg2, arg3, arg0, arg1, arg2, arg3, var_s0, var_fs1);
            var_v0 = var_s1;
            if (temp_fv0 < var_fs4) {
                *arg4 = var_s0;
                *arg5 = var_fs1;
                var_fs4 = temp_fv0;
            }
            var_fs1 = (f32) ((f64) var_fs1 + 0.05);
            if ((var_fs1 >= 1.0f) && (var_s0 < (*(&D_807FDB90 + (arg0 * 4)))->unk4)) {
                var_s0 += 1;
                var_fs1 -= 1.0f;
            } else if (var_fs1 >= 1.0f) {
                var_fs1 = 1.0f;
            }
            var_s1 -= 1;
        } while (var_s1 != 0);
    }
    return var_v0;
}
