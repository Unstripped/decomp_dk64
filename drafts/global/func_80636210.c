// func_80636210 (src/global/36880.c): stage 4: loop matches structurally but target uses 4 callee-saved regs (s3=arg0 kept, s2=i, s1=extra var, s0=p); mine 3 (s2=arg0,s1=i,s0=p) so saves differ. Needs a 4th live variable (second pointer?).
void func_80636210(u8 *arg0, u8 arg1) {
    s32 *p;
    s32 i;

    if (arg1 == 2 && *(s32 *)(arg0 + 0x50) == 0) {
        i = 0;
        p = (s32 *)arg0;
        if (arg0[0x20] > 0) {
            do {
                if (p[9] != 0) {
                    assetFreeBuffer((void *)p[9], 0xA2B, 7);
                    p[9] = 0;
                }
                if (p[13] != 0) {
                    assetFreeBuffer((void *)p[13], 0xA30, 7);
                    p[13] = 0;
                }
                i++;
                p++;
            } while (i < arg0[0x20]);
        }
    }
}
