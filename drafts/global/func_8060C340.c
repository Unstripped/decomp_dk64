// func_8060C340 (src/global/104F0.c): stage 4: frame 0x28, exact control flow, registers s0/s1/ra match; remaining 6 preamble regalloc substitutions (multu $t6/$t1 vs $t0/$t1)
#include <ultra64.h>
extern s16 D_807ECEA0[];
extern void func_8060BF84(s32, u8, u16 *, u8 *);
extern void func_8060BEA8(s32, u8, u16 *, u8 *);
extern void func_8060BCA0(s32, u8, u8, u16 *, u8 *);
extern void func_8060C2C4(s32, s32, u8, u16 *, s8 *);

void func_8060C340(arg0, arg1, arg2, arg3, arg4, arg5)
u16 *arg0;
u8 *arg1;
s32 arg2;
unsigned char arg3;
unsigned char arg4;
unsigned char arg5;
{
    *arg0 = arg5 * ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7);
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
    func_8060C2C4(arg2, arg3, arg4, arg0, (s8 *)arg1);
}
