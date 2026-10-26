// func_8060C648 (src/global/104F0.c): stage 4: s32 B9/caller mask candidate fdiffed; target hoists arg3 mask before argument homes and passes C430 result unmasked to BB18
extern s32 func_8060B9D0(s32);
extern void func_8060BB18(s32, s32, s32);
extern void func_8060C340();
extern s32 func_8060C430(s32, s32, s32);

void func_8060C648(s32 arg0, u8 arg1, u8 arg2, s32 arg3, s32 arg4) {
    u16 sp26;
    u8 sp25;

    func_8060C340(&sp26, &sp25, arg0, arg1, (s32) arg2, func_8060B9D0(arg3 & 0xFF));
    func_8060BB18(func_8060C430(arg0, arg4, 1), sp26, sp25);
}
