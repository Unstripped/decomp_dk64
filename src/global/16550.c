#include "common.h"

s32 acosFixed16(s16);

f32 acosApprox(f32 arg0) {
    s16 var_a0;

    if (arg0 >= 1.0f) {
        var_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        var_a0 = -0x7FFF;
    } else {
        var_a0 = (s16)(s32)(arg0 * 32767.0f);
    }
    return ((f32)(u32)acosFixed16(var_a0) * 3.141592741f) / 65535.0f;
}

s16 asinFixed16(s16);

f32 asinApprox(f32 arg0) {
    s16 var_a0;

    if (arg0 >= 1.0f) {
        var_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        var_a0 = -0x7FFF;
    } else {
        var_a0 = (s16)(s32)(arg0 * 32767.0f);
    }
    return ((f32)asinFixed16(var_a0) * 3.1415927f) / 65535.0f;
}
