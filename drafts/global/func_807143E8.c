// func_807143E8 (src/global/117190.c): stage 6: exact comparison blocks; result temporary allocated v1 with trailing move v0,v1
extern u8 D_80755314;
extern u8 D_80755318;

s32 func_807143E8(void) {
    s32 var_v0;

    var_v0 = D_80755314 == 0xD;
    if (var_v0 == 0) {
        var_v0 = D_80755318 == 0xD;
    }
    return var_v0;
}
