// func_80671E00 (src/global/70FD0.c): Frame 0x50 requires 0 declared locals (compiler spills take all 16B 0x40-0x4F); reusing arg6 matches frame 0x50 and offsets exactly, diff is andi on u8 branch
#include "common.h"

extern u8 D_807FB606;
void func_80672E90(s32, s32, s32);
void func_80672C70(u16);
s32 func_80671F54(f32, f32, f32, f32, s16 *, s16 *);
s32 func_806730A4(s32, s32, s32, s32);
u8 func_806734E4(s32, s32, s32, s32, s16 *, s16 *);

s32 func_80671E00(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 *arg4, s16 *arg5, u8 arg6, u16 arg7) {
    arg0 *= 8.0f;
    arg1 *= 8.0f;
    arg2 *= 8.0f;
    *arg4 = 0;
    *arg5 = 0xFFF;
    arg3 *= 8.0f;
    D_807FB606 = 0;
    func_80672E90(arg0, arg1, arg2);
    func_80672C70(arg7);
    if (arg6 != 0) {
        return (u8)func_806734E4(arg0, arg1, arg2, (s32)arg3, arg4, arg5) | func_80671F54(arg0, arg1, arg2, arg3, arg4, arg5);
    } else {
        if ((arg6 = func_806730A4(arg0, arg1, arg2, (s32)arg3)) != 0) {
            return arg6;
        }
        return func_80671F54(arg0, arg1, arg2, arg3, arg4, arg5);
    }
}
