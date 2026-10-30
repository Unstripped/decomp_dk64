// func_8060BEA8 (src/global/104F0.c): matched: TEXT OK (reloc-only difference: .rodata+144 vs jtbl_807570B0 named label)
void func_8060BEA8(s32 arg0, u8 arg1, u16 *arg2, u8 *arg3) {
    *arg2 = D_807ECEA0[0] + *arg2 + 0x645;
    *arg3 = 0;
    switch (arg0) {
    case 15:
        if (*arg3 == 0) {
            *arg3 = 2;
        }
        *arg2 += 0x18;
    case 16:
        if (*arg3 == 0) {
            *arg3 = 0x18;
        }
        *arg2 += 0x16;
    case 14:
        if (*arg3 == 0) {
            *arg3 = 0x16;
        }
        *arg2 += 1;
    case 13:
        if (*arg3 == 0) {
            *arg3 = 1;
        }
        *arg2 += 2;
    case 12:
        if (*arg3 == 0) {
            *arg3 = 2;
        }
    }
}
