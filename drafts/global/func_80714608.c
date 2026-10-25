// func_80714608 (src/global/117190.c): stage 6: exact blocks; predicate result allocated v1 with trailing move v0,v1
extern s32 D_807552E4;
extern u8 D_807FC928;

s32 func_80714608(s32 arg0) {
    s32 var_v0;

    var_v0 = (s32) D_807FC928 >= 2;
    if (var_v0 != 0) {
        var_v0 = arg0 == D_807552E4;
    }
    return var_v0;
}
