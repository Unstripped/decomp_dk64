// func_8060E3B0 (src/global/104F0.c): stage 6: 100% bit-identical when func_8060B9D0 declared as u16; with s32 return, frame is 0x30 vs target 0x28 (or with result,output,value declarations, 0x28 frame has single diff: output at sp+0x26 vs target sp+0x23)
extern u8 D_807467C8;
extern s32 func_8060B9D0();
extern s32 func_8060BBE0(s32, s32);
extern void func_8060C340();
extern s32 func_8071432C(void);

u8 func_8060E3B0(u16 arg0, u8 arg1) {
    u8 result;
    u16 value;
    u8 output;

    result = 0;
    if (func_8071432C() != 0) {
        func_8060C340(&value, &output, 0, 0, arg1, func_8060B9D0(D_807467C8));
        result = func_8060BBE0((value + arg0) & 0xFFFF, 1);
    }
    return result;
}
