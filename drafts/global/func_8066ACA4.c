// func_8066ACA4 (src/global/6AD90.c): FP temp permutation f4/f10 vs f18/f16; K&R u8 arg2 gives frame/spills
#include "common.h"

typedef struct R1C_TriangleF {
    f32 x[3];
    f32 y[3];
    f32 z[3];
} R1C_TriangleF;

typedef struct R2D_TriangleAC10 {
    u8 pad0[0x24];
    R1C_TriangleF tri;
} R2D_TriangleAC10;

typedef struct R5Q_Cross3D {
    f32 cross[3];
    f32 v0[3];
    f32 v1[3];
} R5Q_Cross3D;

void func_80666AF8();

void func_8066ACA4(arg0, arg1, arg2)
s32 arg0;
R2D_TriangleAC10 *arg1;
u8 arg2;
{
    R5Q_Cross3D sp;

    sp.v1[0] = arg1->tri.x[2] - arg1->tri.x[0];
    sp.v1[1] = arg1->tri.y[2] - arg1->tri.y[0];
    sp.v1[2] = arg1->tri.z[2] - arg1->tri.z[0];
    sp.v0[0] = arg1->tri.x[1] - arg1->tri.x[0];
    sp.v0[1] = arg1->tri.y[1] - arg1->tri.y[0];
    sp.v0[2] = arg1->tri.z[1] - arg1->tri.z[0];
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v0[1] * sp.v1[2]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v0[2] * sp.v1[0]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v0[0] * sp.v1[1]);
    func_80666AF8(arg0, sp.cross[0], sp.cross[1], sp.cross[2], 1, arg2, 2);
}
