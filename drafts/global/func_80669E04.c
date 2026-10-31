// func_80669E04 (src/global/6AD90.c): func_80669E04 (src/global/6AD90.c): stage 4, parked NON_MATCHING (fdiff full=93 text=93 shape=76; was 94/77). New: u32 outside gives target's li v1,1 (s32 1 CSE'd with the switch/ternary 1; the 68C30 twin too). Remaining: prologue only. Target keeps x1/x2/z2 f32 in regs (f18/f16/f20) for the pre-loop sums but z1/x0/z0 are plain stack vars (store at def then immediate reload swc1 f8,0x58; lwc1 f10,0x58; cvt.d.s fs5 from the reload): ours enregisters all six; target shares one 0.5 pair in f0/f1 (ours rematerialises 4x). Frame layout in target (offsets 56 z0 temp/double, z0 68, x0 84,z1 88,z2 92,x1 96,x2 100, doubles 136..160) needs decl order x2,x1,z2,z1,x0 (first-declared highest) then 3 reg-only words, z0, 1 word, and 8+8 reserved double words above/below dx..oz: named d1,d2,x0d,z0d,hx,hz variants (gen over 1500 random G1/G2 splits) never reproduced that layout, frame 224/232 (extra 3-4 conversion temps keep homes). deadsweep sweep (1 round, all locals) best 84 with 'if (sideC && sideC) {}' (not adopted: shape unchanged); permuter -j2 540s: no gain. See 68C30 note: FP var registers follow first-appearance order, not declaration order; try that on case bodies.
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
    u32 outside;
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
