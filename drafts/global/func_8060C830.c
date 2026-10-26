// func_8060C830 (src/global/104F0.c): stage 3: direct mask and byte-local lifetime remain; closest wide temporary keeps word rather than target byte home slot.
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
