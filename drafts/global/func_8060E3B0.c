// func_8060E3B0 (src/global/104F0.c): stage 6: exact code used (u8 *)&value - 1 to place the helper output at sp+0x23, but this writes outside the value object and is UB. A legitimate struct { u8 padding; u8 output; u16 value; } state candidate was fdiff'd; it grew the frame to 0x30 (target 0x28), placing output/value at sp+0x2D/sp+0x2E instead of sp+0x23/sp+0x24. Restored GLOBAL_ASM rather than retain the UB candidate.
extern s32 func_8060B9D0();
extern s32 func_8060BBE0(s32, s32);
extern void func_8060C340();
extern s32 func_8071432C(void);
extern u8 D_807467C8;

u8 func_8060E3B0(u16 arg0, u8 arg1) {
    u8 result;
    u8 sp27;
    u16 value;

    sp27 = 0;
    result = sp27;
    if (func_8071432C() != 0) {
        func_8060C340(&value, (u8 *)&value - 1, 0, 0, arg1, func_8060B9D0(D_807467C8));
        result = func_8060BBE0((value + arg0) & 0xFFFF, 1);
    }
    return result;
}
