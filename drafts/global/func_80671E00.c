// func_80671E00 (src/global/70FD0.c): Frame 0x60 vs target 0x50, all instructions match but stack offset shift
#include "common.h"

extern u8 D_807FB606;
void func_80672E90(s32, s32, s32);
void func_80672C70(u16);
s32 func_80671F54(f32, f32, f32, f32, s16 *, s16 *);
s32 func_806730A4(s32, s32, s32, s32);
u8 func_806734E4(s32, s32, s32, s32, s16 *, s16 *);

s32 func_80671E00(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 *arg4, s16 *arg5, u8 arg6, u16 arg7) {
    u8 sp4F;
    s32 sp48;
    s32 sp44;
    s32 sp40;

    arg0 *= 8.0f;
    arg1 *= 8.0f;
    arg2 *= 8.0f;
    *arg4 = 0;
    *arg5 = 0xFFF;
    sp44 = arg1;
    sp40 = arg2;
    arg3 *= 8.0f;
    sp48 = arg0;
    D_807FB606 = 0;
    func_80672E90(sp48, sp44, sp40);
    func_80672C70(arg7);
    if (arg6 != 0) {
        sp4F = func_806734E4(sp48, sp44, sp40, (s32)arg3, arg4, arg5);
        return sp4F | func_80671F54(arg0, arg1, arg2, arg3, arg4, arg5);
    } else {
        if ((sp40 = func_806730A4(sp48, sp44, sp40, (s32)arg3)) != 0) {
            return sp40;
        }
        return func_80671F54(arg0, arg1, arg2, arg3, arg4, arg5);
    }
}
