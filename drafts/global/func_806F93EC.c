// func_806F93EC (src/global/FCCD0.c): m2c behavioural draft; 16-instruction bit-set helper not isolated after concurrent candidates.
s32 func_805FF030(s32, ?);                          /* extern */

void func_806F93EC(u16 *arg0, s32 arg1) {
    *arg0 |= 1 << func_805FF030(arg1 & 0xFF, 1);
}
