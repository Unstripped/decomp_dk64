// func_8060C758 (src/global/104F0.c): stage 3: typed candidate based on this starter was compiled and fdiffed; reset/call control flow recovered, remaining stack/register allocation for size and bank.
? func_8060B8F8(?);                                 /* extern */
s32 func_8060B9D0(s8);                              /* extern */
? func_8060C648(?, ?, ?, s32, s32);                 /* extern */
extern s8 D_807467C8;
extern s16 D_807ECEA0;
extern ? D_807ECEA8;

void func_8060C758(s32 arg0, s32 arg1) {
    s32 temp_lo;
    s32 temp_t8;
    s8 temp_s0;

    temp_s0 = arg0 & 0xFF;
    temp_t8 = (s32) ((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
    temp_lo = func_8060B9D0(temp_s0) * temp_t8;
    D_807467C8 = temp_s0;
    bzero(temp_lo + &D_807ECEA8, temp_t8);
    func_8060C648(0xC, 0, 0, temp_s0 & 0xFF, 1);
    func_8060C648(0xF, 0, 0, temp_s0 & 0xFF, (s32) temp_s0);
    if (arg1 != 0) {
        func_8060B8F8(1);
    }
}
