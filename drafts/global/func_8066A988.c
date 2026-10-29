// func_8066A988 (src/global/6AD90.c): func_8066A988 (src/global/6AD90.c): twin of func_80669E04 at CollisionBoxTriangle +0x24 (arg0->tri.x/z); same stage 4 NON_MATCHING park, same prologue diff (see func_80669E04 draft note).
#include "common.h"

typedef struct CollisionTriF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
} CollisionTriF;

typedef struct CollisionBoxTriangle {
    u8 pad0[0x24];
    CollisionTriF tri;
} CollisionBoxTriangle;

u8 func_8066A988(CollisionBoxTriangle *arg0, f32 arg1, f32 arg2) {
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f32 x0;
    f32 x1;
    f32 x2;
    f32 z0;
    f32 z1;
    f32 z2;
    f64 cx;
    f64 cz;
    f64 a;
    f64 b;
    f64 c;
    s32 i;
    s32 outside;
    s32 sideP;
    s32 sideC;

    x1 = arg0->tri.x[1];
    x2 = arg0->tri.x[2];
    z2 = arg0->tri.z[2];
    z1 = arg0->tri.z[1];
    outside = 0;
    x0 = arg0->tri.x[0];
    z0 = arg0->tri.z[0];
    cx = (x0 + (f64)(x2 + x1) * 0.5) * 0.5;
    cz = (z0 + (f64)(z2 + z1) * 0.5) * 0.5;
    i = 0;
    do {
        switch (i) {
        case 0:
            dx = x1 - x0;
            dz = z1 - z0;
            ox = x0;
            oz = z0;
            break;
        case 1:
            dx = x2 - x0;
            dz = z2 - z0;
            ox = x0;
            oz = z0;
            break;
        case 2:
            dx = x2 - x1;
            dz = z2 - z1;
            ox = x1;
            oz = z1;
            break;
        }
        a = (arg1 - ox) * dz;
        b = (arg2 - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        i++;
        if (b <= a) {
            sideP = 1;
        } else {
            sideP = -1;
        }
        if (c >= 0.0) {
            sideC = 1;
        } else {
            sideC = -1;
        }
        if (sideC != sideP) {
            outside = 1;
        }
    } while (i != 3);
    return outside == 0;
}
