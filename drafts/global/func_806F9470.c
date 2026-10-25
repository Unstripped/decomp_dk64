// func_806F9470 (src/global/FCCD0.c): m2c behavioural draft; 15-instruction bit-test helper not isolated after concurrent candidates.
s32 func_805FF030(s32, ?);                          /* extern */

s32 func_806F9470(u16 arg0, s32 arg1) {
    return (1 << func_805FF030(arg1 & 0xFF, 1)) & arg0 & 0xFF;
}
