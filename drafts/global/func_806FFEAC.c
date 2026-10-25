// func_806FFEAC (src/global/103AB0.c): Stage 5: exact loop operations/frame; only s1-s4 allocation and save order differ. arg1 must be s32 with explicit u16 cast to preserve byte offsets.
s16 func_806FFC04(u16);

s16 *func_806FFEAC(s16 *arg0, s32 arg1) {
    s16 *var_s1;
    s16 temp_v0;
    s16 var_s0;
    s16 var_s3;

    var_s1 = arg0;
    var_s3 = 0;
    do {
        var_s0 = 0;
        do {
            temp_v0 = func_806FFC04(*(u16 *)(arg1 + (var_s0 * 2) + (var_s3 * D_80744490 * 2)));
            var_s0++;
            *var_s1 = temp_v0;
            var_s1++;
        } while (var_s0 < 0x20);
        var_s3++;
    } while (var_s3 < 0x40);
    return var_s1;
}
