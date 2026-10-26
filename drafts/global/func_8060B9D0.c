// func_8060B9D0 (src/global/104F0.c): stage 4: s32 formal matches unmasked target entry; remaining target holds table base in v0 and increments v1 in bnel delay, candidate uses a2 plus a1 temporary
extern u8 D_807EDEA8[];

s32 func_8060B9D0(s32 arg0) {
    s32 temp_t8;
    s32 var_v1;

    var_v1 = 0;
loop_1:
    if (arg0 == D_807EDEA8[var_v1]) {
        return var_v1;
    }
    temp_t8 = (var_v1 + 1) & 0xFF;
    var_v1 = temp_t8;
    if (temp_t8 >= 4) {
        return 0;
    }
    goto loop_1;
}
