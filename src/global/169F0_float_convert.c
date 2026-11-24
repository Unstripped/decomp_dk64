#include "common.h"
#include "proto/global/169F0_float_convert.h"

f32 truncateFloat(f32 val) {
    return (f32)(s32)val;
}

s32 floatToS32(f32 val) {
    return (s32) val;
}
