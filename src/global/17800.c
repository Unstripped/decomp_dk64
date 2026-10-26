#include "common.h"

f32 powfInt(f32 arg0, s16 arg1) {
    f32 result;
    s16 i;

    result = 1.0f;
    if (arg1 != 0) {
        i = 0;
        if (arg1 > 0) {
            do {
                i++;
                result *= arg0;
            } while (i < arg1);
        }
    }
    return result;
}

f32 floorLog10(s16 arg0) {
    s16 digits;

    digits = 0;
    if (arg0 != 0) {
        do {
            arg0 = (s16)(arg0 / 10);
            digits++;
        } while (arg0 != 0);
    }
    return (f32)(digits - 1);
}

f32 cosApprox(f32);
f32 sinApprox(f32);

void matrixMakeRotationX(f32 (*arg0)[4], f32 arg1) {
    f32 sine;
    f32 cosine;

    arg1 *= 0.01745329238f;
    sine = sinApprox(arg1);
    cosine = cosApprox(arg1);
    guMtxIdentF(arg0);
    arg0[1][2] = sine;
    arg0[2][1] = -sine;
    arg0[1][1] = cosine;
    arg0[2][2] = cosine;
}
void matrixMakeRotationY(f32 (*arg0)[4], f32 arg1) {
    f32 sine;
    f32 cosine;

    arg1 *= 0.01745329238f;
    sine = sinApprox(arg1);
    cosine = cosApprox(arg1);
    guMtxIdentF(arg0);
    arg0[2][0] = sine;
    arg0[0][2] = -sine;
    arg0[0][0] = cosine;
    arg0[2][2] = cosine;
}

void matrixMakeRotationZ(f32 (*arg0)[4], f32 arg1) {
    f32 sine;
    f32 cosine;

    arg1 *= 0.01745329238f;
    sine = sinApprox(arg1);
    cosine = cosApprox(arg1);
    guMtxIdentF(arg0);
    arg0[0][1] = sine;
    arg0[1][0] = -sine;
    arg0[0][0] = cosine;
    arg0[1][1] = cosine;
}


