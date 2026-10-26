#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/16550/func_80611850.s")

s16 func_80611DF4(s16);

f32 func_806118FC(f32 arg0) {
    s16 var_a0;

    if (arg0 >= 1.0f) {
        var_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        var_a0 = -0x7FFF;
    } else {
        var_a0 = (s16)(s32)(arg0 * 32767.0f);
    }
    return ((f32)func_80611DF4(var_a0) * 3.1415927f) / 65535.0f;
}
