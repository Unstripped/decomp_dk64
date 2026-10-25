// func_806F6E58 (src/global/F9450.c): Stage 1 m2c starter; reviewed 33-instruction predicate target.
s32 func_8073110C(?, ?);                            /* extern */
extern ? D_80754238;
extern ? D_807FC950;

s32 func_806F6E58(s16 arg0) {
    u8 sp1F;
    u8 var_v1;

    var_v1 = 0;
    if (arg0 < 5) {
        var_v1 = ((s32) *(&D_807FC950 + (arg0 * 0x5E)) >= (s32) *(&D_80754238 + arg0)) & 0xFF;
    }
    sp1F = var_v1;
    return (var_v1 | func_8073110C(0x179, 0)) & 0xFF;
}
