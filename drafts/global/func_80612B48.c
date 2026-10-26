// func_80612B48 (src/global/17540.c): stage 2: m2c starter; remaining diff not yet reduced
f32 func_80612B48(s16 arg0) {
    s16 temp_t9;
    s16 var_a0;
    s16 var_v0;

    var_a0 = arg0;
    var_v0 = 0;
    if (arg0 != 0) {
        do {
            temp_t9 = (s16) (var_a0 / 10);
            var_a0 = temp_t9;
            var_v0 += 1;
        } while (temp_t9 != 0);
    }
    return (f32) (var_v0 - 1);
}
