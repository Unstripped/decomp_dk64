// func_8060E3B0 (src/global/104F0.c): stage 6: 0x28 frame and caller-saved registers match; remaining diff is local stack slot positions (value/output/result at sp+0x20/0x22/0x23 vs target sp+0x24/0x23/0x27). With u16 return for func_8060B9D0, instructions and slots match 100%.
extern s32 func_8071432C(void);

u8 func_8060E3B0(u16 arg0, u8 arg1) {
    s32 new_var;
    u8 result;
    u8 output;
    u16 value;

    result = 0;
    if (func_8071432C() != 0) {
        new_var = func_8060B9D0(D_807467C8);
        func_8060C340(&value, &output, 0, 0, arg1, new_var);
        new_var = func_8060BBE0((value + arg0) & 0xFFFF, 1);
        result = new_var;
    }
    return result;
}
