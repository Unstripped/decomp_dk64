// func_806FA504 (src/global/FCCD0.c): stage 3: control flow/calls recovered; frame and result register allocation differ
s32 func_806FA504(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 result;

    result = arg3;
    if (*(s32 *)arg1 == 0) {
        if (arg0 != 8) {
            result = func_806F9D8C(arg0, arg1, arg3, arg3);
        } else {
            result = func_806FA1A4(arg0, arg1);
        }
    } else if ((arg0 == 8) || (arg0 == 0xA) || (arg0 == 0xC)) {
        func_806F8DC4(*(s8 **)((u8 *)arg1 + 0x14), arg2, arg0);
    }
    return result;
}
