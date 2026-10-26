// func_8060BEA8 (src/global/104F0.c): stage 3: typed switch/fallthrough candidate compiled and fdiffed; remaining jump-table and temporary register layout.
extern s16 D_807ECEA0;

void func_8060BEA8(s32 arg0, ? arg1, u16 *arg2, u8 *arg3) {
    *arg2 = *arg2 + D_807ECEA0 + 0x645;
    *arg3 = 0;
    switch (arg0) {
    case 15:
        if (*arg3 == 0) {
            *arg3 = 2;
        }
        *arg2 += 0x18;
        /* fallthrough */
    case 16:
        if (*arg3 == 0) {
            *arg3 = 0x18;
        }
        *arg2 += 0x16;
        /* fallthrough */
    case 14:
        if (*arg3 == 0) {
            *arg3 = 0x16;
        }
        *arg2 += 1;
        /* fallthrough */
    case 13:
        if (*arg3 == 0) {
            *arg3 = 1;
        }
        *arg2 += 2;
        /* fallthrough */
    case 12:
        if (*arg3 == 0) {
            *arg3 = 2;
        }
        break;
    }
}
