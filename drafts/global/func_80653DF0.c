// func_80653DF0 (src/global/55B20.c): stage6: prologue moves s0=a0 order (sunk after sw a2), bnel operand order t7,s2 vs s2,t7, lw v0+move a1 vs lw a1, bnez-to-increment vs bnezl-to-test. permuter 400s no zero
extern s32 func_8066B0F8(s32, s32, s32, s32);

u8 *func_80653DF0(u8 *arg0, u8 *arg1, s16 arg2) {
    s32 count;
    u8 *p;
    s32 temp_v0;
    s32 zero;
    u32 tag;

    p = arg0;
    zero = 0;
    count = zero;
    if ((p != arg1) && (arg2 > zero)) {
        do {
            tag = *(u32 *)p;
            if ((tag >> 0x18) == 0xFD) {
                temp_v0 = *(s32 *)(p + 4);
                if (((u32)(temp_v0 * 0x10) >> 0x1C) == zero) {
                    *(s32 *)(p + 4) = func_8066B0F8(0x19, temp_v0, zero, zero);
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
