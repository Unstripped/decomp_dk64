// func_80712F10 (src/global/117190.c): State-transition condition behavior recovered; compiler shape remains off
void func_80712F10(s32 *arg0, s32 *arg1) {
    if (D_80755314 == 0xC) {
        if (((D_807FBB68 & 2) == 0) || ((D_8076A0A8 == 0xCF) || (*arg0 == 0x22))) {
            *arg0 = 0x50;
            *arg1 = 0;
            D_80755318 = 5;
        }
    } else if ((D_80755314 == 0xD) && (D_8076A0A8 != *arg0)) {
        *arg0 = 0xF;
        *arg1 = 0;
        D_80755318 = 6;
    } else if (D_80755330 != 0) {
        *arg0 = -1;
    }
}
