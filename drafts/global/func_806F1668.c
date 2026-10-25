// func_806F1668 (src/global/F56F0.c): Stage 3 algebraic draft from FPU instruction flow; expression grouping and floating scheduling remain unmatched.
s32 func_806F1668(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp;

    if ((arg0 < 0.0f) || (arg2 <= 0.0f) || (arg3 < 0.0f)) {
        return 0;
    }
    temp = (arg2 - arg1) / arg3;
    if ((arg1 + arg2) * 0.5f * temp + arg0 > 0.0f) {
        temp -= ((arg1 + arg2) * 0.5f * temp + arg0) / arg2;
    } else {
        temp = (-sqrtf(arg1 * arg1 - arg3 * 0.5f * arg0) - arg1) / arg3;
    }
    return (s32)(temp + 0.5f);
}
