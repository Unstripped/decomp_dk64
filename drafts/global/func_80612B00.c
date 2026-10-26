// func_80612B00 (src/global/17540.c): stage 2: m2c starter; remaining diff not yet reduced
f32 func_80612B00(f32 arg0, s16 arg1) {
    f32 var_fv1;
    s16 var_v0;

    var_fv1 = 1.0f;
    if (arg1 != 0) {
        var_v0 = 0;
        if (arg1 > 0) {
            do {
                var_v0 += 1;
                var_fv1 *= arg0;
            } while (var_v0 < arg1);
        }
    }
    return var_fv1;
}
