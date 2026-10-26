// func_8060B968 (src/global/104F0.c): stage 6: CRC loop flow matches; remaining allocation includes CRC state/table base and target arg1 home store; permuter best 165.
extern u32 D_807463C0[];

u32 func_8060B968(u8 *arg0, s32 arg1) {
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_v0;
    u32 var_v1;

    temp_t6 = arg1 & 0xFFFF;
    var_v1 = -1U;
    arg1 = (temp_t6 - 1) & 0xFFFF;
    if (temp_t6 != 0) {
        do {
            temp_v0 = arg1;
            temp_t3 = D_807463C0[(*arg0 ^ var_v1) & 0xFF];
            arg1 = (arg1 - 1) & 0xFFFF;
            arg0++;
            var_v1 = temp_t3 ^ (var_v1 >> 8);
        } while (temp_v0 != 0);
    }
    return var_v1 ^ -1;
}
