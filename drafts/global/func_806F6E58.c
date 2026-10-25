// func_806F6E58 (src/global/F9450.c): Stage 4: all operations align except boolean temporary register allocation
s32 func_8073110C(s32, s32);
extern u8 D_80754238[];
extern u8 D_807FC950[];

s32 func_806F6E58(s16 arg0) {
    u8 var_v1;

    var_v1 = 0;
    if (arg0 < 5) {
        var_v1 = (D_807FC950[arg0 * 0x5E] < D_80754238[arg0]) ^ 1;
        var_v1 &= 0xFF;
    }
    var_v1 |= func_8073110C(0x179, 0);
    return var_v1;
}
