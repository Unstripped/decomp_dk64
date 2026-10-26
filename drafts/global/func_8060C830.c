// func_8060C830 (src/global/104F0.c): stage 4: correct frame/control flow; remaining direct-mask register and byte home (target t6/sp+0x1B, candidate v0/word home). Tried u8/s32 formals, u8/s32 temporaries, direct value, and a legitimate union grouping; union grows the frame.
void func_8060C830(s32 arg0, s32 arg1) {
    s32 temp_t6;

    temp_t6 = arg0 & 0xFF;
    D_807467C8 = temp_t6;
    arg0 = temp_t6;
    func_8060C758(temp_t6, 0);
    if (func_8060C6B8(0xF, 0, 0, 3) == arg0) {
        func_8060C758(3U, 0);
    }
    if (arg1 != 0) {
        func_8060B8F8(1);
    }
}
