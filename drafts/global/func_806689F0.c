// func_806689F0 (src/global/6AD90.c): diff 240 (regalloc only: f8/f10 swapped in cross terms; frame 0x60 and all stack offsets exact)
#include "common.h"
#include "actor.h"

typedef struct R3Q_TriangleS {
    s16 x[3];
    s16 y[3];
    s16 z[3];
    s16 unk12;
    u8 unk14;
} R3Q_TriangleS;

typedef struct R3Q_Cross3D {
    f32 cross[3];
    f32 v0[3];
    f32 v1[3];
} R3Q_Cross3D;

void func_80666AF8(s32, f32, f32, f32, u8, u8, s32);

void func_806689F0(arg0, arg1, arg2)
s32 arg0;
R3Q_TriangleS *arg1;
u8 arg2;
{
    R3Q_Cross3D sp;

    sp.v1[0] = arg1->x[2] - arg1->x[0];
    sp.v1[1] = arg1->y[2] - arg1->y[0];
    sp.v1[2] = arg1->z[2] - arg1->z[0];
    sp.v0[0] = arg1->x[1] - arg1->x[0];
    sp.v0[1] = arg1->y[1] - arg1->y[0];
    sp.v0[2] = arg1->z[1] - arg1->z[0];
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v0[1] * sp.v1[2]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v0[2] * sp.v1[0]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v0[0] * sp.v1[1]);
    func_80666AF8(arg0, sp.cross[0], sp.cross[1], sp.cross[2], arg1->unk14, arg2, 0);
}
