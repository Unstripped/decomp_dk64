// func_8060C724 (src/global/104F0.c): stage 4: fdiffed s32 fourth-parameter candidate; target directly masks a0 into a3 while candidate reloads and masks through t6
extern s32 func_8060C6B8(s32, u8, u8, s32);

s32 func_8060C724(s32 arg0) {
    return func_8060C6B8(0x10, 0, 0, arg0 & 0xFF) + 1;
}
