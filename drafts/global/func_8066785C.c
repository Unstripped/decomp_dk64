// func_8066785C (src/global/6AD90.c): plane-height from s16 triangle normal; frame 0x20 exact
#include "common.h"
#include "actor.h"

typedef struct R3Q_TriangleS_785C {
    s16 x[3];
    s16 y[3];
    s16 z[3];
} R3Q_TriangleS_785C;

f32 func_8066785C(R3Q_TriangleS_785C *arg0, f32 arg1, f32 arg2) {
    f64 dy01 = arg0->y[0] - arg0->y[1];
    f64 dx01 = arg0->x[0] - arg0->x[1];
    f64 dz02 = arg0->z[0] - arg0->z[2];
    f64 dz01 = arg0->z[0] - arg0->z[1];
    f64 dy02 = arg0->y[0] - arg0->y[2];
    f64 dx02 = arg0->x[0] - arg0->x[2];
    f64 nx = (dy01 * dz02) - (dz01 * dy02);
    f64 ny = (dz01 * dx02) - (dx01 * dz02);
    f64 nz = (dx01 * dy02) - (dy01 * dx02);
    f64 d = (nx * arg0->x[1]) + (ny * arg0->y[1]) + (nz * arg0->z[1]);
    f64 val = ((nx * arg1) + (ny * -1000.0) + (nz * arg2) - d) / (ny * 2000.0);
    return (2000.0 * (0.0 - val)) - 1000.0;
}
