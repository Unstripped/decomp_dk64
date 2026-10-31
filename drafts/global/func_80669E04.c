// func_80669E04 (src/global/6AD90.c): R2Frm1 (wave 2): stage 4 (u32 outside, NON_MATCHING park unchanged; frame 200 = target, saved f20-f30 = target; 165 vs 162 insns, 125 objdump-diff lines incl. sp offsets). Re-read: ours ALSO stores all six f32 locals to stack (swc1 then lwc1 in loop); the difference is only (a) homes: target doubles dx..oz at 136..160 with 4 doubles of reserved homes ABOVE them (168..199 unused) and floats x2,x1,z2,z1,x0 at 100..84, 3 reg-only words, z0 68, double CSE temp 56; ours dx..oz 168..192, floats 144..164; (b) pre-loop: target loads x1,x2,z1,z2 first (z1 stored 88 then reloaded; x0 84, z0 68 likewise reloaded; x1/x2/z2 used straight from the load regs), one shared 0.5 pair f0/f1, (f64)x0 in fs5, (f64)z0 spilled sdc1 56; ours rematerialises 0.5 three times. Tried this round (all no gain): random statement order of the 6 loads / outside / i / cx / cz with cx,cz placed after their operands (hc2/hc4 hill-climb, ~15 min), field-read vs variable form of every operand in the cx/cz sums, declaration-order + unused f64/f32/s32 pad hill-climb (best 125 -> 97 with moved decls but stack layout still wrong, ~25 min). No layout reproducing 168..199 reserved + 136..167 dx..oz found.
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
