// func_806F8EDC (src/global/FCCD0.c): m2c behavioural starter; 192-insn selector switch requires local views and stage work.
s32 func_806C8DE0(s32);                             /* extern */
s32 func_806F6EDC(s32, s32);                        /* extern */
s32 func_806F8EB4();                                /* extern */
s32 func_8073110C(?, ?);                            /* extern */
extern u8 D_807FC928;
extern ? D_807FC953;
extern ? D_807FC954;

s32 func_806F8EDC(s32 arg0, s32 arg1) {
    s32 temp_t5;
    s32 temp_v0;
    s32 var_a0;
    s32 var_v1;
    u8 temp_a0;
    u8 var_v0;

    temp_v0 = func_806C8DE0(arg1);
    var_a0 = 0x64;
    switch (arg0) {
    case 1:
        var_a0 = 0x3E7;
        break;
    case 2:
        var_a0 = ((1 << *(&D_807FC953 + ((arg1 * 0x306) + (temp_v0 * 0x5E)))) * 0x32) & 0xFFFF;
        break;
    case 3:
        if ((s32) D_807FC928 >= 2) {
            var_a0 = 0xA;
        } else {
            var_a0 = ((1 << *(&D_807FC953 + ((arg1 * 0x306) + (temp_v0 * 0x5E)))) * 0x32) & 0xFFFF;
        }
        break;
    case 4:
        var_a0 = ((*(&D_807FC953 + ((arg1 * 0x306) + (temp_v0 * 0x5E))) * 5) + 0x14) & 0xFFFF;
        break;
    case 5:
        if ((s32) D_807FC928 >= 2) {
            var_a0 = 0xBB8;
        } else if (func_806F6EDC(0x64, arg1) != 0) {
            var_a0 = ((func_806F8EB4() * 0x96) + 0xBB8) & 0xFFFF;
        } else {
            var_a0 = 0;
        }
        break;
    case 7:
        if ((s32) D_807FC928 >= 2) {
            var_a0 = 0x14;
        } else {
            temp_a0 = *(&D_807FC954 + ((arg1 * 0x306) + (temp_v0 * 0x5E)));
            var_v1 = 1;
            if (temp_a0 & 1) {
                var_v0 = temp_a0;
                if (temp_a0 != 0) {
                    do {
                        temp_t5 = (s32) var_v0 >> 1;
                        var_v1 += 1;
                        var_v0 = (u8) temp_t5;
                    } while (temp_t5 != 0);
                }
                var_a0 = (var_v1 * 5) & 0xFFFF;
            } else {
                var_a0 = 0;
            }
        }
        break;
    case 6:
        if (func_8073110C(0x179, 0) != 0) {
            var_a0 = (func_806F8EB4() + 0xA) & 0xFFFF;
        } else {
            var_a0 = 0;
        }
        break;
    case 9:
        var_a0 = 0xC8;
        break;
    }
    return var_a0;
}
