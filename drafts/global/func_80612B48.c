// func_80612B48 (src/global/17540.c): stage 2: simplified m2c loop; remaining sign-extension/register allocation
f32 func_80612B48(s16 arg0) {
    s16 value;
    s16 digits;
    value = arg0;
    digits = 0;
    if (arg0 != 0) {
        do {
            value = (s16)(value / 10);
            digits++;
        } while (value != 0);
    }
    return (f32)(digits - 1);
}
