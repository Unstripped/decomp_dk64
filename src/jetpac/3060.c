#include "common.h"
s32 randomNonNegative(void);


u32 jetpacCheckAabbOverlap(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    arg0 = (arg4 < arg0) ? arg0 : arg4;
    arg1 = (arg5 < arg1) ? arg1 : arg5;
    arg2 = (arg2 < arg6) ? arg2 : arg6;
    arg3 = (arg3 < arg7) ? arg3 : arg7;
    if (arg0 <= arg2 && arg1 <= arg3) {
        return 1;
    }
    return 0;
}

void func_80027108(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;

    if (arg0 < 0.0f) {
        if (arg1 <= 0.0f) {
            temp_fv0 = arg0 + 256.0f;
            temp_fv1 = arg1 + 256.0f;
            *arg2 = temp_fv0;
            *arg3 = temp_fv1;
            *arg4 = temp_fv0;
            *arg5 = temp_fv1;
            return;
        }
        *arg2 = 0.0f;
        *arg3 = arg1;
        *arg4 = arg0 + 256.0f;
        *arg5 = 256.0f;
        return;
    }
    if (arg0 >= 256.0f) {
        temp_fv0_2 = arg0 - 256.0f;
        temp_fv1_2 = arg1 - 256.0f;
        *arg2 = temp_fv0_2;
        *arg3 = temp_fv1_2;
        *arg4 = temp_fv0_2;
        *arg5 = temp_fv1_2;
        return;
    }
    if (arg1 > 256.0f) {
        *arg2 = 0.0f;
        *arg3 = arg1 - 256.0f;
        *arg4 = arg0;
        *arg5 = 256.0f;
        return;
    }
    *arg2 = arg0;
    *arg3 = arg1;
    *arg4 = arg0;
    *arg5 = arg1;
}

f32 jetpacRandFloat(void) {
    return (f32)((randomNonNegative() >> 15) % 60000) / 60000.0f;
}

#if 0
// Differs only in boolean branching registers (sltu $t0 vs beqz)
s32 func_80027250(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp44, sp40, sp3C, sp38, sp34, sp30, sp2C, sp28;
    func_80027108(arg0, arg2, &sp44, &sp40, &sp3C, &sp38);
    func_80027108(arg4, arg6, &sp34, &sp30, &sp2C, &sp28);
    if (jetpacCheckAabbOverlap(sp44, arg1, sp40, arg3, sp34, arg5, sp30, arg7)) {
        return 1;
    }
    return jetpacCheckAabbOverlap(sp3C, arg1, sp38, arg3, sp2C, arg5, sp28, arg7) != 0;
}
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3060/func_80027250.s")

#if 0
// 4 instructions off: evaluating directly into $v0 rather than $v1
s32 func_80027330(f32 arg0) {
    return (165.0f <= arg0) && (arg0 <= 171.0f);
}
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3060/func_80027330.s")

typedef struct {
    f32 x;
    f32 y;
    s32 pad8[5];
    s32 min_x;
    s32 min_y;
    s32 max_x;
    s32 max_y;
} JetpacEntity;

f32 jetpacGetEntityCenterX(JetpacEntity *arg0) {
    return (f32)((f64)(arg0->x + (f32)arg0->min_x) + (f64)(f32)(arg0->max_x - arg0->min_x) * 0.5);
}

f32 jetpacGetEntityCenterY(JetpacEntity *arg0) {
    return (f32)((f64)(arg0->y + (f32)arg0->min_y) + (f64)(f32)(arg0->max_y - arg0->min_y) * 0.5);
}

f32 jetpacRoundFloat(f32 arg0) {
    if (arg0 >= 0.0f) {
        return (f32)(s32)(arg0 + 0.5f);
    }
    return (f32)(s32)(arg0 - 0.5f);
}
