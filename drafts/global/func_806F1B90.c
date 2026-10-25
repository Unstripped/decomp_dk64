// func_806F1B90 (src/global/F56F0.c): Stage 4: splitting final multiply makes target tail exact. Remaining initial temp/main FP allocation f0/f14 versus f4/f2 and float rodata register sequence.
f32 func_806F1B90(f32 *arg0, f32 arg1) {
    f32 var_fv1;
    f32 temp_ft0;

    temp_ft0 = *arg0;
    *arg0 = arg1;
    var_fv1 = arg1 - temp_ft0;
    if (var_fv1 > 3.1415927f) {
        var_fv1 = 6.2831855f - var_fv1;
    } else if (var_fv1 < -3.1415927f) {
        var_fv1 = -(6.2831855f + var_fv1);
    }
    var_fv1 *= 0.15915494f;
    return var_fv1;
}
