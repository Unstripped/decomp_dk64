// func_80669E04 (src/global/6AD90.c): func_80669E04 (src/global/6AD90.c): stage 4, parked NON_MATCHING, unchanged C (fdiff full=94 text=94 shape=77, 162 vs 165 lines). Prologue only: target keeps x1/x2/z2 f32 in regs (f18/f16/f20) for the pre-loop sums and spills them later, but z1/x0/z0 are plain stack vars (store at def then immediate reload: swc1 f8,0x58; lwc1 f10,0x58) -- ours enregisters all six. Target shares ONE 0.5 const pair in f0/f1 (ours rematerialises 4x: (double)z0 candidate takes f0 in ours, f14 in target). NM4 pass tried without gain: 6 statement-order/cx-form random searches (best 91), decl-order hill-climb w/ pads, f64 mid temps (mx/mz), 0.5 as named local, /2.0 and /2 forms, volatile on every subset of the six floats (worse), assign cx/cz inside loop, dead cx=0.0 redefs, deadsweep sweep (no improving statement), uopt -l 5/6 trace (cx/cz candidates 36/45 colour f22/f24 like target; difference is only which of the 6 f32 homes colour pre-loop).
#include "common.h"

typedef struct CollisionTriF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
} CollisionTriF;

u8 func_80669E04(CollisionTriF *arg0, f32 arg1, f32 arg2) {
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

    x1 = arg0->x[1];
    x2 = arg0->x[2];
    z2 = arg0->z[2];
    z1 = arg0->z[1];
    outside = 0;
    x0 = arg0->x[0];
    z0 = arg0->z[0];
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
