// func_80669E04 (src/global/6AD90.c): func_80669E04 (src/global/6AD90.c): stage 4 (frame 0xC8 + f20-f30 saved set exact; loop/switch body identical, parked NON_MATCHING in the file). ~58 of 162 lines differ: prologue only. Target keeps x1/x2/z2 f32 coords in regs for early (x2+x1)*0.5 math then spills them (stores late at 0x60/0x64/0x5C), reloads z1/x0/z0 from 0x58/0x54/0x44 immediately after store, shares one 0.5 const in f0/f1; ours allocates f12..f20 per f32 and rematerialises 0.5 x4. Wins: statement order in cases dx,dz,ox,oz (gives ox/oz/dx/dz = f16/f18/f12/f14 like target), u8 return. Tried: decl-order hill climb, assign/early-use random search, array/struct/volatile/addr-taken coords, permuter 600s (no 0).
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
