// func_806119FC (src/global/166A0.c): stage 2: m2c starter; remaining diff not yet reduced
s32 func_806119A0();                                /* extern */

f32 func_806119FC(void) {
    f32 var_ft1;
    s32 temp_v0;

    temp_v0 = func_806119A0();
    var_ft1 = (f32) temp_v0;
    if (temp_v0 < 0) {
        var_ft1 += 4294967296.0f;
    }
    return var_ft1 * 2.3283064e-10f;
}
