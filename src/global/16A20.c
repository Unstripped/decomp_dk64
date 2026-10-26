#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/16A20/func_80611D20.s")

s32 func_80611D20(s32);

s32 func_80611DA0(s16 arg0) {
    s32 var_a0_2;
    s32 temp_v0;

    if (arg0 >= 0) {
        var_a0_2 = arg0;
    } else {
        var_a0_2 = -arg0;
    }
    temp_v0 = func_80611D20(var_a0_2);
    var_a0_2 = temp_v0;
    if (arg0 < 0) {
        var_a0_2 = 0xFFFF - temp_v0;
    }
    return var_a0_2 & 0xFFFF;
}

s16 func_80611DF4(s16 arg0) {
    s32 var_a0;
    s32 var_a0_2;
    s32 temp_v0;

    if (arg0 >= 0) {
        var_a0_2 = arg0;
    } else {
        var_a0_2 = -arg0;
    }
    temp_v0 = func_80611D20(var_a0_2);
    if (arg0 >= 0) {
        var_a0 = 0x7FFF - temp_v0;
    } else {
        temp_v0 = temp_v0 - 0x8000;
        var_a0 = temp_v0;
    }
    return var_a0;
}
