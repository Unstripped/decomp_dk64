#include "common.h"
#include "proto/global/16550.h"
#include "proto/global/16A20.h"


f32 acosApprox(f32 val) {
    s16 fixedVal;

    if (val >= 1.0f) {
        fixedVal = 0x7FFF;
    } else if (val <= -1.0f) {
        fixedVal = -0x7FFF;
    } else {
        fixedVal = (s16)(s32)(val * 32767.0f);
    }
    return ((f32)(u32)acosFixed16(fixedVal) * 3.141592741f) / 65535.0f;
}


f32 asinApprox(f32 val) {
    s16 fixedVal;

    if (val >= 1.0f) {
        fixedVal = 0x7FFF;
    } else if (val <= -1.0f) {
        fixedVal = -0x7FFF;
    } else {
        fixedVal = (s16)(s32)(val * 32767.0f);
    }
    return ((f32)asinFixed16(fixedVal) * 3.1415927f) / 65535.0f;
}
