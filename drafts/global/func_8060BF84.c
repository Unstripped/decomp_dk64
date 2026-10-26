// func_8060BF84 (src/global/104F0.c): stage 3: correct fall-through switch; target preserves arg1's initial mask in a1, candidate remasks at each multiplier case and misses entry parameter home.
void func_8060BF84(s32 arg0, s32 arg1, u16 *arg2, u8 *arg3) {
    s32 temp_t6;

    temp_t6 = arg1 & 0xFF;
    *arg2 = (((((((D_807ECEA0[0] + 0x6B7) & 0xFFC0) + 0x27) & 0xFFF8) * 4) + 0x3F) & 0xFFC0) + 0x40;
    *arg3 = 0;
    switch (arg0) {
    case 32: if (*arg3 == 0) *arg3 = 1; *arg2 += 3;
    case 31: if (*arg3 == 0) *arg3 = 3; *arg2 += 2;
    case 30: if (*arg3 == 0) *arg3 = 2; *arg2 += 0x2D;
    case 29: if (*arg3 == 0) { *arg3 = 9; *arg2 += temp_t6 * 9; } *arg2 += 0x19;
    case 28: if (*arg3 == 0) { *arg3 = 5; *arg2 += temp_t6 * 5; } *arg2 += 0x19;
    case 27: if (*arg3 == 0) { *arg3 = 5; *arg2 += temp_t6 * 5; } *arg2 += 0x19;
    case 26: if (*arg3 == 0) { *arg3 = 5; *arg2 += temp_t6 * 5; } *arg2 += 0x2D;
    case 25: if (*arg3 == 0) { *arg3 = 9; *arg2 += temp_t6 * 9; } *arg2 += 0x19;
    case 24: if (*arg3 == 0) { *arg3 = 5; *arg2 += temp_t6 * 5; } *arg2 += 0x19;
    case 23: if (*arg3 == 0) { *arg3 = 5; *arg2 += temp_t6 * 5; } *arg2 += 0x19;
    case 22: if (*arg3 == 0) { *arg3 = 5; *arg2 += temp_t6 * 5; } *arg2 += 0x4B;
    case 21: if (*arg3 == 0) { *arg3 = 0xF; *arg2 += temp_t6 * 0xF; } *arg2 += 0x19;
    case 20: if (*arg3 == 0) { *arg3 = 5; *arg2 += temp_t6 * 5; } *arg2 += 0x19;
    case 19: if (*arg3 == 0) { *arg3 = 5; *arg2 += temp_t6 * 5; } *arg2 += 0x19;
    case 18: if (*arg3 == 0) { *arg3 = 5; *arg2 += temp_t6 * 5; } *arg2 += 0x11;
    case 17: if (*arg3 == 0) *arg3 = 0x12;
    }
}
