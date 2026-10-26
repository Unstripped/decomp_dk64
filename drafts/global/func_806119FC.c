// func_806119FC (src/global/166A0.c): stage 4: 5+ fdiff attempts; pointer alias removes size mismatch and leaves only FPR allocation (target f6/f8/f10 vs candidate f2/f6/f8). Permuter -j2 --seconds 600 best score 40, no zero.
s32 func_806119A0(void);

f32 func_806119FC(void) {
    f32 var_ft1;
    s32 temp_v0;
    f32 *result;

    result = &var_ft1;
    temp_v0 = func_806119A0();
    var_ft1 = (f32)temp_v0;
    if (temp_v0 < 0) {
        var_ft1 += 4294967296.0f;
    }
    return *result * 2.3283064e-10f;
}
