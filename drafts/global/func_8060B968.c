// func_8060B968 (src/global/104F0.c): stage 4: m2c-equivalent CRC loop; target uses incoming a0/a1/v1 registers directly, candidate keeps separate pointer/counter/checksum locals
extern u32 D_807463C0[];

u32 func_8060B968(u8 *arg0, s32 arg1) {
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_v0;
    s32 var_a1;
    u32 var_v1;
    u8 *var_a0;

    var_a0 = arg0;
    temp_t6 = arg1 & 0xFFFF;
    var_v1 = -1U;
    var_a1 = (temp_t6 - 1) & 0xFFFF;
    if (temp_t6 != 0) {
        do {
            temp_v0 = var_a1;
            temp_t3 = D_807463C0[(*var_a0 ^ var_v1) & 0xFF];
            var_a1 = (var_a1 - 1) & 0xFFFF;
            var_a0 += 1;
            var_v1 = temp_t3 ^ (var_v1 >> 8);
        } while (temp_v0 != 0);
    }
    return var_v1 ^ -1;
}
