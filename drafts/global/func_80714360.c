// func_80714360 (src/global/117190.c): stage 6: exact comparison blocks; result temporary allocated v1 with trailing move v0,v1
extern u8 D_80755314;
extern u8 D_80755318;

s32 func_80714360(void) {
    s32 var_v0;

    var_v0 = D_80755314 == 8;
    if (var_v0 == 0) {
        var_v0 = D_80755318 == 8;
    }
    return var_v0;
}
