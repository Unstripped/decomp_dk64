// func_8060C340 (src/global/104F0.c): stage 3: typed dispatch candidate compiled and fdiffed; remaining branch layout, argument homes, and callee register allocation.
? func_8060BCA0(s32, u8, u8, s16 *, s32);           /* extern */
? func_8060BEA8(s32, u8, s16 *, s32);               /* extern */
? func_8060BF84(s32, u8, s16 *, s32);               /* extern */
? func_8060C2C4(s32, u8, u8, s16 *, s32);           /* extern */
extern s16 D_807ECEA0;

void func_8060C340(s16 *arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5) {
    *arg0 = arg5 * ((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7);
    if (arg2 >= 0x11) {
        func_8060BF84(arg2, arg4, arg0, arg1);
        return;
    }
    if (arg2 >= 0xC) {
        func_8060BEA8(arg2, arg4, arg0, arg1);
        return;
    }
    if (arg2 > 0) {
        func_8060BCA0(arg2, arg3, arg4, arg0, arg1);
        return;
    }
    func_8060C2C4(arg2, arg3, arg4, arg0, arg1);
}
