// func_8060BB18 (src/global/104F0.c): stage 3: full bitfield writer compiled from m2c typed locals; remaining diff is missing target s0/frame and pervasive loop register allocation. Tried compact typed loop and m2c-shaped temporaries.
void func_8060BB18(u32 arg0, s32 arg1, s32 arg2) {
    s32 *var_t1;
    s32 temp_at, temp_t2, temp_t3, temp_t6, temp_t7, temp_t9;
    s32 var_a2, var_a3, var_v0, var_v1;
    u32 var_s0;

    temp_t6 = arg1 & 0xFFFF;
    temp_t7 = arg2 & 0xFF;
    var_a2 = temp_t7;
    var_s0 = arg0;
    var_v0 = -1;
    var_v1 = 0;
    var_a3 = temp_t6 & 0x1F;
    var_t1 = ((temp_t6 >> 5) * 4) + (s32 *)D_807ECEA8;
    if (temp_t7 != 0) {
        do {
            temp_t9 = (var_a3 + 1) & 0xFF;
            temp_t2 = (var_a2 - 1) & 0xFF;
            temp_at = temp_t9 < 0x20;
            var_v0 ^= 1 << var_a3;
            var_v1 |= (var_s0 & 1) << var_a3;
            var_s0 >>= 1;
            var_a3 = temp_t9;
            var_a2 = temp_t2;
            if ((temp_at == 0) || (temp_t2 == 0)) {
                temp_t3 = *var_t1;
                var_t1++;
                var_a3 = 0;
                *(var_t1 - 1) = (temp_t3 & var_v0) | var_v1;
                var_v1 = 0;
                var_v0 = -1;
            }
        } while (var_a2 != 0);
    }
}
