// func_807142D8 (src/global/117190.c): stage 6: exact blocks; result/value temporary allocated v1 with trailing move v0,v1
extern u8 D_80755314;
extern u8 D_80755318;

s32 func_807142D8(void) {
    s32 var_v0;

    var_v0 = D_80755318 == 3;
    if (var_v0 == 0) {
        var_v0 = D_80755318 == 4;
        if (var_v0 == 0) {
            var_v0 = D_80755314 == 3;
            if (var_v0 == 0) {
                var_v0 = D_80755314 == 4;
            }
        }
    }
    return var_v0;
}
