#include "common.h"
#include "proto/global/2C700.h"

extern f32 gCardinalSplineBasis[16];

f32 splineEvalCubic(f64 t, f32 p0, f32 p1, f32 p2, f32 p3) {
    f32 *m = gCardinalSplineBasis;
    f32 a, b, d, c, t2;

    a = m[0] * p0 + m[4] * p1 + m[8] * p2 + m[12] * p3;
    b = m[1] * p0 + m[5] * p1 + m[9] * p2 + m[13] * p3;
    c = m[2] * p0 + m[6] * p1 + m[10] * p2 + m[14] * p3;
    d = m[3] * p0 + m[7] * p1 + m[11] * p2 + m[15] * p3;
    t2 = t * t;
    return (f32)(t2 * t) * a + t2 * b + t * c + d;
}

void splineSetBasisTension(f32 t) {
    gCardinalSplineBasis[0] = -t;
    gCardinalSplineBasis[1] = 2.0 * t;
    gCardinalSplineBasis[2] = -t;
    gCardinalSplineBasis[3] = 0.0f;
    gCardinalSplineBasis[4] = 2.0 - t;
    gCardinalSplineBasis[5] = t - 3.0;
    gCardinalSplineBasis[6] = 0.0f;
    gCardinalSplineBasis[7] = 1.0f;
    gCardinalSplineBasis[8] = t - 2.0;
    gCardinalSplineBasis[9] = 3.0 - 2.0 * t;
    gCardinalSplineBasis[10] = t;
    gCardinalSplineBasis[11] = 0.0f;
    gCardinalSplineBasis[12] = t;
    gCardinalSplineBasis[13] = -t;
    gCardinalSplineBasis[14] = 0.0f;
    gCardinalSplineBasis[15] = 0.0f;
}
