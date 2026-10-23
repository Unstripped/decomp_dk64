// func_80669830 (src/global/6AD90.c): diff 120 (regalloc only: alternating f4/f18 in cross terms); all stack offsets and frame 0x60 exact
#include "common.h"
#include "actor.h"

typedef struct R3Q_TriangleF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
    u8 unk24;
} R3Q_TriangleF;

typedef struct R3Q_Cross3D {
    f32 cross[3];
    f32 v0[3];
    f32 v1[3];
} R3Q_Cross3D;

void func_80666AF8(s32, f32, f32, f32, u8, u8, s32);

void func_80669830(arg0, arg1, arg2)
s32 arg0;
R3Q_TriangleF *arg1;
u8 arg2;
{
    R3Q_Cross3D sp;

    sp.v1[0] = arg1->x[2] - arg1->x[0];
    sp.v1[1] = arg1->y[2] - arg1->y[0];
    sp.v1[2] = arg1->z[2] - arg1->z[0];
    sp.v0[0] = arg1->x[1] - arg1->x[0];
    sp.v0[1] = arg1->y[1] - arg1->y[0];
    sp.v0[2] = arg1->z[1] - arg1->z[0];
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v1[2] * sp.v0[1]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v0[2] * sp.v1[0]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v0[0] * sp.v1[1]);
    func_80666AF8(arg0, sp.cross[0], sp.cross[1], sp.cross[2], arg1->unk24, arg2, 1);
}
