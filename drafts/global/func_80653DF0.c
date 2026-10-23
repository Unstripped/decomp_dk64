// func_80653DF0 (src/global/55B20.c): stage 6: frame/logic match; s2=0xFD via extra local zero + dead if(zero){} block; remaining: tag/mask temp in t7 (target v0) so target copies v0->a1 and branches bnez to p+=8; permuter score 270
void *func_80653DF0(u8 *arg0, u8 *arg1, s16 arg2) {
    s32 count;
    u8 *p;
    s32 zero;

    p = arg0;
    zero = 0;
    count = zero;
    if ((p != arg1) && (arg2 > zero)) {
        do {
            if ((*(u32 *)p >> 0x18) == 0xFD) {
                if (((u32)(*(s32 *)(p + 4) * 0x10) >> 0x1C) == zero) {
                    *(s32 *)(p + 4) = func_8066B0F8(0x19, *(s32 *)(p + 4), zero, zero);
                    count++;
                }
                if (zero) {
                }
            }
            p += 8;
        } while ((p != arg1) && (count < arg2));
    }
    return p;
}
