// func_8060C6B8 (src/global/104F0.c): stage 3: typed candidate based on this starter was compiled and fdiffed twice; target frame/calls match except local byte/halfword offsets and B9 byte-mask scheduling.
s32 func_8060B9D0(s32);                             /* extern */
s32 func_8060BBE0(u16, u8);                         /* extern */
? func_8060C340(u16 *, u8 *, s32, u8, s32, s32);    /* extern */
? func_8060C430(s32, s32, ?);                       /* extern */

void func_8060C6B8(s32 arg0, u8 arg1, u8 arg2, s32 arg3) {
    u16 sp22;
    u8 sp21;

    func_8060C340(&sp22, &sp21, arg0, arg1, (s32) arg2, func_8060B9D0(arg3 & 0xFF));
    func_8060C430(arg0, func_8060BBE0(sp22, sp21), 0);
}
