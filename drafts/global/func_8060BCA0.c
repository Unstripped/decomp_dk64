// func_8060BCA0 (src/global/104F0.c): stage 3: correct fall-through switch; target homes a1/a2 then masks arg2 once, candidate lacks homes and redundantly remasks in final cases.
void func_8060BCA0(s32 arg0, s32 arg1, s32 arg2, u16 *arg3, u8 *arg4) {
    s32 temp_t7;

    temp_t7 = arg2 & 0xFF;
    *arg3 = *arg3 + D_807ECEA0[0] + ((arg1 & 0xFF) * 0xA1) + 0x320;
    *arg4 = 0;
    switch (arg0) {
    case 11: if (*arg4 == 0) *arg4 = 1; *arg3 += 3;
    case 10: if (*arg4 == 0) *arg4 = 3; *arg3 += 8;
    case 9: if (*arg4 == 0) *arg4 = 8; *arg3 += 4;
    case 8: if (*arg4 == 0) *arg4 = 4; *arg3 += 2;
    case 7: if (*arg4 == 0) *arg4 = 2; *arg3 += 3;
    case 6: if (*arg4 == 0) *arg4 = 3; *arg3 += 2;
    case 5: if (*arg4 == 0) *arg4 = 2; *arg3 += 2;
    case 4: if (*arg4 == 0) *arg4 = 2; *arg3 += 0x18;
    case 3: if (*arg4 == 0) { *arg4 = 3; *arg3 += temp_t7 * 3; } *arg3 += 0x38;
    case 2: if (*arg4 == 0) { *arg4 = 7; *arg3 += temp_t7 * 7; } *arg3 += 0x38;
    case 1: if (*arg4 == 0) { *arg4 = 7; *arg3 += temp_t7 * 7; }
    }
}
