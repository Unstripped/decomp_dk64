// func_8060C724 (src/global/104F0.c): stage 4: correct frame and all instructions except target andi a3,a0,0xFF versus C lbu a3,0x1B(sp); prototype/expression tuning remains
extern s32 func_8060C6B8();

s32 func_8060C724(s32 arg0) {
    return func_8060C6B8(0x10, 0, 0, (u8)arg0) + 1;
}
