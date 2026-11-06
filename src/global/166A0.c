#include "common.h"

extern s32 D_80746A40;
extern u64 __ll_mul(u64, u64);

s32 randomLcgNext(void) {
    u64 seed = (u32)D_80746A40;
    u64 prod = __ll_mul(seed, 0x01DF5E0DULL);
    return D_80746A40 = (prod + 1) & 0xFFFFFFFF;
}

void setRandomSeed(s32 seed) {
    D_80746A40 = seed;
}

s32 randomLcgNext(void);

f32 randomFloat(void) {
    return (f32)(u32)randomLcgNext() * 2.3283064e-10f;
}

s32 randomNonNegative(void) {
    return randomLcgNext() & 0x7FFFFFFF;
}

void func_80611A70(f32 refX, f32 refY, f32 *outX, f32 *outY) {
    f32 value;
    f64 delta;

    value = *outX;
    delta = (f64)(value - refX);
    if ((delta < 0.25) && (delta >= 0.0)) {
        *outX = (f32)((f64)value + 0.125);
    }
    value = *outY;
    delta = (f64)(value - refY);
    if ((delta < 0.25) && (delta >= 0.0)) {
        *outY = (f32)((f64)value + 0.125);
    }
    value = *outX;
    delta = (f64)(value - refX);
    if ((delta > -0.25) && (delta <= 0.0)) {
        *outX = (f32)((f64)value - 0.125);
    }
    value = *outY;
    delta = (f64)(value - refY);
    if ((delta > -0.25) && (delta <= 0.0)) {
        *outY = (f32)((f64)value - 0.125);
    }
}

f32 acosApprox(f32);

f32 func_80611BB4(f32 dx, f32 dy) {
    f32 angleA;
    f32 hypot;
    f32 temp_fv0_2;
    f32 angle;

    if (dx == 0.0f) {
        if (dy >= 0.0f) {
            angle = 0.0f;
        } else {
            angle = 3.1415927f;
        }
    } else if (dy == 0.0f) {
        if (dx > 0.0f) {
            angle = 1.5707964f;
        } else {
            angle = 4.712389f;
        }
    } else {
        hypot = sqrtf((dx * dx) + (dy * dy));
        if (dy < dx) {
            temp_fv0_2 = acosApprox(dy / hypot);
            angle = temp_fv0_2;
            if (dx < 0.0f) {
                angle = 6.2831855f - temp_fv0_2;
            }
        } else {
            angleA = 1.5707964f - acosApprox(dx / hypot);
            angle = angleA;
            if (dy < 0.0f) {
                angle = 3.1415927f - angleA;
            }
            if (angle < 0.0f) {
                angle += 6.2831855f;
            }
        }
    }
    return angle;
}

