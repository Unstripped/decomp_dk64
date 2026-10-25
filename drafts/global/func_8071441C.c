// func_8071441C (src/global/117190.c): stage 6: exact comparison blocks; result temporary allocated v1 with trailing move v0,v1
extern u8 D_80755314;
extern u8 D_80755318;

s32 func_8071441C(void) {
    s32 var_v0;

    var_v0 = D_80755314 == 0xC;
    if (var_v0 == 0) {
        var_v0 = D_80755318 == 0xC;
    }
    return var_v0;
}
