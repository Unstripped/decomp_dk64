#include "common.h"

extern s32 D_80746A40;

#pragma GLOBAL_ASM("asm/global/nonmatchings/166A0/func_806119A0.s")

void setRandomSeed(s32 arg0) {
    D_80746A40 = arg0;
}

s32 func_806119A0(void);

#pragma GLOBAL_ASM("asm/global/nonmatchings/166A0/func_806119FC.s")

s32 randomNonNegative(void) {
    return func_806119A0() & 0x7FFFFFFF;
}

void func_80611A70(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 value;
    f64 delta;

    value = *arg2;
    delta = (f64)(value - arg0);
    if ((delta < 0.25) && (delta >= 0.0)) {
        *arg2 = (f32)((f64)value + 0.125);
    }
    value = *arg3;
    delta = (f64)(value - arg1);
    if ((delta < 0.25) && (delta >= 0.0)) {
        *arg3 = (f32)((f64)value + 0.125);
    }
    value = *arg2;
    delta = (f64)(value - arg0);
    if ((delta > -0.25) && (delta <= 0.0)) {
        *arg2 = (f32)((f64)value - 0.125);
    }
    value = *arg3;
    delta = (f64)(value - arg1);
    if ((delta > -0.25) && (delta <= 0.0)) {
        *arg3 = (f32)((f64)value - 0.125);
    }
}

f32 func_80611850(f32);

f32 func_80611BB4(f32 arg0, f32 arg1) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fv1;

    if (arg0 == 0.0f) {
        if (arg1 >= 0.0f) {
            var_fv1 = 0.0f;
        } else {
            var_fv1 = 3.1415927f;
        }
    } else if (arg1 == 0.0f) {
        if (arg0 > 0.0f) {
            var_fv1 = 1.5707964f;
        } else {
            var_fv1 = 4.712389f;
        }
    } else {
        temp_fv0 = sqrtf((arg0 * arg0) + (arg1 * arg1));
        if (arg1 < arg0) {
            temp_fv0_2 = func_80611850(arg1 / temp_fv0);
            var_fv1 = temp_fv0_2;
            if (arg0 < 0.0f) {
                var_fv1 = 6.2831855f - temp_fv0_2;
            }
        } else {
            temp_fa0 = 1.5707964f - func_80611850(arg0 / temp_fv0);
            var_fv1 = temp_fa0;
            if (arg1 < 0.0f) {
                var_fv1 = 3.1415927f - temp_fa0;
            }
            if (var_fv1 < 0.0f) {
                var_fv1 += 6.2831855f;
            }
        }
    }
    return var_fv1;
}

