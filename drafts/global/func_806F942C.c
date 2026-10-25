// func_806F942C (src/global/FCCD0.c): m2c behavioural draft; 17-instruction bit-clear helper not isolated after concurrent candidates.
s32 func_805FF030(s32, ?);                          /* extern */

void func_806F942C(u16 *arg0, s32 arg1) {
    *arg0 &= ~(1 << func_805FF030(arg1 & 0xFF, 1));
}
