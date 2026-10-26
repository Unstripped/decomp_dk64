// func_8060E3B0 (src/global/104F0.c): stage 4: permutation search (600s) reduced score from 66 to 5. Frame and all instructions match except the helper's output-byte address: target uses sp+0x23; closest candidate aliases arg1 and emits sp+0x2F. Tested declaration reorders and compact byte-array local, which worsened the diff.
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
        func_8060C340(&value, &arg1, 0, 0, arg1, func_8060B9D0(D_807467C8));
        result = func_8060BBE0((value + arg0) & 0xFFFF, 1);
    }
    return result;
}
