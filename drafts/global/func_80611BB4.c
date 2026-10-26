// func_80611BB4 (src/global/166A0.c): stage 2: m2c candidate; remaining atan-like branch and literal layout.
f32 func_80611850(f32, f32);                        /* extern */

f32 func_80611BB4(f32 arg0, f32 arg1) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fv1;

    if (arg0 == 0.0f) {
        if (arg1 >= 0.0f) {
            var_fv1 = 0.0f;
        } else {
            var_fv1 = 3.1415927f;
        }
    } else if (arg1 == 0.0f) {
        if (arg0 > 0.0f) {
            var_fv1 = 1.5707964f;
        } else {
            var_fv1 = 4.712389f;
        }
    } else {
        temp_fv0 = sqrtf((arg0 * arg0) + (arg1 * arg1));
        if (arg1 < arg0) {
            temp_fv0_2 = func_80611850(arg1 / temp_fv0, arg1);
            var_fv1 = temp_fv0_2;
            if (arg0 < 0.0f) {
                var_fv1 = 6.2831855f - temp_fv0_2;
            }
        } else {
            temp_fa0 = 1.5707964f - func_80611850(arg0 / temp_fv0, arg1);
            var_fv1 = temp_fa0;
            if (arg1 < 0.0f) {
                var_fv1 = 3.1415927f - temp_fa0;
            }
            if (var_fv1 < 0.0f) {
                var_fv1 += 6.2831855f;
            }
        }
    }
    return var_fv1;
}
