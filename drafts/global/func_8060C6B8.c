// func_8060C6B8 (src/global/104F0.c): stage 6: all instructions match except temporary stack locations sp+0x26/0x25 vs target sp+0x22/0x21; best permuter score 161 after 600s.
extern s32 func_8060B9D0(s32);
extern s32 func_8060BBE0();
extern void func_8060C340();
extern s32 func_8060C430(s32, u32, s32);

s32 func_8060C6B8(s32 arg0, u8 arg1, u8 arg2, u8 arg3) {
    u16 sp22;
    u8 sp21;

    func_8060C340(&sp22, &sp21, arg0, arg1, (s32)arg2, func_8060B9D0(arg3));
    func_8060C430(arg0, func_8060BBE0(sp22, sp21), 0);
}
