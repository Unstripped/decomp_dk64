// func_8069DC10 (src/global/9DD70.c): stage 6: target computes (i*n)*4 as the loop invariant and adds arg1+j*4 inside; mine folds arg1 into the invariant (1 addu vs move difference)
void func_8069DC10(s32 *arg0, s32 *arg1, u8 arg2) {
    s16 i;
    s16 j;

    i = 0;
    do {
        for (j = 0; j < arg2; j++) {
            *arg0++ = arg1[i * arg2 + j];
        }
        i++;
    } while (i < 0x20);
}
