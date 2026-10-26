// func_8060C6B8 (src/global/104F0.c): stage 4: s32 B9/caller mask candidate fdiffed; target locals occupy sp+0x22/0x21 while candidate uses sp+0x26/0x25
extern s32 func_8060B9D0(s32);
extern s32 func_8060BBE0(u16, u8);
extern void func_8060C340();
extern s32 func_8060C430(s32, s32, s32);

s32 func_8060C6B8(s32 arg0, u8 arg1, u8 arg2, s32 arg3) {
    u16 sp22;
    u8 sp21;

    func_8060C340(&sp22, &sp21, arg0, arg1, (s32) arg2, func_8060B9D0(arg3 & 0xFF));
    func_8060C430(arg0, func_8060BBE0(sp22, sp21), 0);
}
