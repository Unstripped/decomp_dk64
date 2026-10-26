// func_8060E3B0 (src/global/104F0.c): stage 3: behavioural/control-flow match; tested typed and unprototyped func_8060C340 plus direct/separate result locals. All retain an 0x30 frame instead of target 0x28; best matches body instructions once frame-adjusted.
extern s32 func_8060B9D0(u8);
extern s32 func_8060BBE0(s32, s32);
extern void func_8060C340();
extern s32 func_8071432C(void);

u8 func_8060E3B0(u16 arg0, u8 arg1) {
    u8 sp27;
    u16 value;
    u8 unk;
    u8 result;

    sp27 = 0;
    result = sp27;
    if (func_8071432C() != 0) {
        func_8060C340(&value, &unk, 0, 0, arg1, func_8060B9D0(D_807467C8));
        result = func_8060BBE0((value + arg0) & 0xFFFF, 1);
    }
    return result;
}
