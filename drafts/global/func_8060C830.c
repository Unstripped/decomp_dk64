// func_8060C830 (src/global/104F0.c): stage 3: typed candidate based on this starter was compiled and fdiffed; complete control flow recovered, remaining byte-local and home-slot placement.
? func_8060B8F8(?);                                 /* extern */
s32 func_8060C6B8(?, ?, ?, ?);                      /* extern */
? func_8060C758(u8, ?);                             /* extern */
extern u8 D_807467C8;

void func_8060C830(u8 arg0, s32 arg1) {
    u8 temp_t6;

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
