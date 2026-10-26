// func_806119FC (src/global/166A0.c): stage 3; m2c, branch returns, ternary, and sequenced-assignment candidates fdiffed; closest m2c has one early cvt.s.w/mov.s and FPR allocation difference, target converts in bgez delay slot.
s32 func_806119A0(void);

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
