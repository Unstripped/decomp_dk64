#include "common.h"
#include "proto/global/17800.h"

f32 powfInt(f32 base, s16 exp) {
    f32 result = 1.0f;
    s16 i;

    if (exp != 0) {
        for (i = 0; i < exp; i++) {
            result *= base;
        }
    }
    return result;
}

f32 floorLog10(s16 val) {
    s16 digits;

    digits = 0;
    while (val != 0) {
        val /= 10;
        digits++;
    }
    return digits - 1;
}

f32 cosApprox(f32);
f32 sinApprox(f32);

void matrixMakeRotationX(f32 (*dst)[4], f32 angleDeg) {
    f32 sine;
    f32 cosine;

    angleDeg *= 0.01745329238f;
    sine = sinApprox(angleDeg);
    cosine = cosApprox(angleDeg);
    guMtxIdentF(dst);
    dst[1][2] = sine;
    dst[2][1] = -sine;
    dst[1][1] = cosine;
    dst[2][2] = cosine;
}

void matrixMakeRotationY(f32 (*dst)[4], f32 angleDeg) {
    f32 sine;
    f32 cosine;

    angleDeg *= 0.01745329238f;
    sine = sinApprox(angleDeg);
    cosine = cosApprox(angleDeg);
    guMtxIdentF(dst);
    dst[2][0] = sine;
    dst[0][2] = -sine;
    dst[0][0] = cosine;
    dst[2][2] = cosine;
}

void matrixMakeRotationZ(f32 (*dst)[4], f32 angleDeg) {
    f32 sine;
    f32 cosine;

    angleDeg *= 0.01745329238f;
    sine = sinApprox(angleDeg);
    cosine = cosApprox(angleDeg);
    guMtxIdentF(dst);
    dst[0][1] = sine;
    dst[1][0] = -sine;
    dst[0][0] = cosine;
    dst[1][1] = cosine;
}
