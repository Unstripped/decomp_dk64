#include "common.h"
#include "proto/global/16550.h"
#include "proto/global/166A0.h"

extern u32 sRandomSeed;

u32 randomLcgNext(void) {
    u64 seed = sRandomSeed;
    u64 prod = seed * 0x01DF5E0D;
    return sRandomSeed = (prod + 1) & 0xFFFFFFFF;
}

void setRandomSeed(s32 seed) {
    sRandomSeed = seed;
}

f32 randomFloat(void) {
    return randomLcgNext() * 2.3283064e-10f;
}

s32 randomNonNegative(void) {
    return randomLcgNext() & 0x7FFFFFFF;
}

void mathNudgeCoords(f32 refX, f32 refY, f32 *outX, f32 *outY) {
    f32 value;
    f64 delta;

    value = *outX;
    delta = value - refX;
    if ((delta < 0.25) && (delta >= 0.0)) {
        *outX = value + 0.125;
    }
    value = *outY;
    delta = value - refY;
    if ((delta < 0.25) && (delta >= 0.0)) {
        *outY = value + 0.125;
    }
    value = *outX;
    delta = value - refX;
    if ((delta > -0.25) && (delta <= 0.0)) {
        *outX = value - 0.125;
    }
    value = *outY;
    delta = value - refY;
    if ((delta > -0.25) && (delta <= 0.0)) {
        *outY = value - 0.125;
    }
}

f32 mathAtan2(f32 dx, f32 dy) {
    f32 hypot;
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
            angle = acosApprox(dy / hypot);
            if (dx < 0.0f) {
                angle = 6.2831855f - angle;
            }
        } else {
            angle = 1.5707964f - acosApprox(dx / hypot);
            if (dy < 0.0f) {
                angle = 3.1415927f - angle;
            }
            if (angle < 0.0f) {
                angle += 6.2831855f;
            }
        }
    }
    return angle;
}

