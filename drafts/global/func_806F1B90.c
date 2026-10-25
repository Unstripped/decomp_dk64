// func_806F1B90 (src/global/F56F0.c): stage 4: m2c reconstruction; floating temporary/register allocation and rodata remain
f32 func_806F1B90(f32 *arg0, f32 arg1) {
    f32 temp_ft0;
    f32 var_fv1;

    temp_ft0 = *arg0;
    *arg0 = arg1;
    var_fv1 = arg1 - temp_ft0;
    if (var_fv1 > 3.1415927f) {
        var_fv1 = 6.2831855f - var_fv1;
    } else if (var_fv1 < -3.1415927f) {
        var_fv1 = -(6.2831855f + var_fv1);
    }
    return var_fv1 * 0.15915494f;
}
