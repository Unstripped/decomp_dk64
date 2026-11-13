#include "common.h"
#include "proto/global/16A20.h"

extern u16 D_80746A50[];
extern u16 D_80746ACC[];
extern u16 D_80746B4C[];

s32 mathFixedPointInterp(s32 inputVal) {
    u32 val;
    u16 *table;
    s32 shift;
    s32 mask;
    s32 index;
    u16 cur;
    u16 next;
    s32 masked;

    mask = 7;
    if (inputVal >= 0x7FE0) {
        shift = 3;
        table = D_80746B4C;
        inputVal -= 0x7FE0;
    } else {
        mask = 0x1FF;
        if (inputVal >= 0x7800) {
            mask = 0x1F;
            shift = 5;
            table = D_80746ACC;
            inputVal -= 0x7800;
        } else {
            shift = 9;
            table = D_80746A50;
        }
    }
    index = inputVal >> shift;
    cur = table[index];
    next = table[index + 1];
    masked = inputVal & mask;
    val = cur;
    return val - ((s32)((val - next) * masked) >> shift);
}


s32 acosFixed16(s16 val) {
    s32 absVal;
    s32 interpVal;

    if (val >= 0) {
        absVal = val;
    } else {
        absVal = -val;
    }
    interpVal = mathFixedPointInterp(absVal);
    absVal = interpVal;
    if (val < 0) {
        absVal = 0xFFFF - interpVal;
    }
    return absVal & 0xFFFF;
}

s16 asinFixed16(s16 val) {
    s32 result;
    s32 absVal;
    s32 interpVal;

    if (val >= 0) {
        absVal = val;
    } else {
        absVal = -val;
    }
    interpVal = mathFixedPointInterp(absVal);
    if (val >= 0) {
        result = 0x7FFF - interpVal;
    } else {
        interpVal = interpVal - 0x8000;
        result = interpVal;
    }
    return result;
}
