// func_80666F04 (src/global/699B0.c): needs .double 150 in .late_rodata vs constant folding to float
extern f32 D_807F9468;
extern u8 D_807F946C;

s32 func_80666F04(f32 arg0, f32 arg1, u8 arg2, u8 arg3) {
    f64 var_fv0;
    s32 var_v1;

    var_v1 = 0;
    if (arg3 == 0xFF && arg0 < arg1) {
        if (arg2 == 1) {
            var_fv0 = 150.0;
        } else {
            var_fv0 = 25.0;
        }
        if ((arg1 - arg0) < (f32)var_fv0) {
            D_807F946C = 1;
            var_v1 = 1;
            D_807F9468 = arg1 - (f32)var_fv0;
            if (arg2 != 0) {
                D_807F9468 /= 6.0f;
            }
            D_807F9468 = (f64)D_807F9468 + 6.0;
        }
    }
    return var_v1;
}
