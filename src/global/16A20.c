#include "common.h"

extern u16 D_80746A50[];
extern u16 D_80746ACC[];
extern u16 D_80746B4C[];

s32 mathFixedPointInterp(s32 arg0) {
    u32 val;
    u16 *var_a2;
    s32 var_a1;
    s32 var_v1;
    s32 index;
    u16 temp_a3;
    u16 next;
    s32 masked;
    s32 diff;

    var_v1 = 7;
    if (arg0 >= 0x7FE0) {
        var_a1 = 3;
        var_a2 = D_80746B4C;
        arg0 -= 0x7FE0;
    } else {
        var_v1 = 0x1FF;
        if (arg0 >= 0x7800) {
            var_v1 = 0x1F;
            var_a1 = 5;
            var_a2 = D_80746ACC;
            arg0 -= 0x7800;
        } else {
            var_a1 = 9;
            var_a2 = D_80746A50;
        }
    }
    index = arg0 >> var_a1;
    temp_a3 = var_a2[index];
    next = var_a2[index + 1];
    masked = arg0 & var_v1;
    val = temp_a3;
    diff = val - next;
    return val - (((s32)(((u32)diff) * masked)) >> var_a1);
}

s32 mathFixedPointInterp(s32);

s32 acosFixed16(s16 arg0) {
    s32 var_a0_2;
    s32 temp_v0;

    if (arg0 >= 0) {
        var_a0_2 = arg0;
    } else {
        var_a0_2 = -arg0;
    }
    temp_v0 = mathFixedPointInterp(var_a0_2);
    var_a0_2 = temp_v0;
    if (arg0 < 0) {
        var_a0_2 = 0xFFFF - temp_v0;
    }
    return var_a0_2 & 0xFFFF;
}

s16 asinFixed16(s16 arg0) {
    s32 var_a0;
    s32 var_a0_2;
    s32 temp_v0;

    if (arg0 >= 0) {
        var_a0_2 = arg0;
    } else {
        var_a0_2 = -arg0;
    }
    temp_v0 = mathFixedPointInterp(var_a0_2);
    if (arg0 >= 0) {
        var_a0 = 0x7FFF - temp_v0;
    } else {
        temp_v0 = temp_v0 - 0x8000;
        var_a0 = temp_v0;
    }
    return var_a0;
}
