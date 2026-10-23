// func_8066ACA4 (src/global/6AD90.c): near-miss: 63 insns, K&R u8 arg2 gives frame/spills, only FP temp set alternation (/ vs /) remains
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

void func_80666AF8();

void func_8066ACA4(arg0, arg1, arg2)
s32 arg0;
R2D_TriangleAC10 *arg1;
u8 arg2;
{
    f32 v1[3];
    f32 v2[3];
    f32 cross[3];

    v1[0] = arg1->tri.x[2] - arg1->tri.x[0];
    v1[1] = arg1->tri.y[2] - arg1->tri.y[0];
    v1[2] = arg1->tri.z[2] - arg1->tri.z[0];

    v2[0] = arg1->tri.x[1] - arg1->tri.x[0];
    v2[1] = arg1->tri.y[1] - arg1->tri.y[0];
    v2[2] = arg1->tri.z[1] - arg1->tri.z[0];

    cross[0] = (v1[1] * v2[2]) - (v2[1] * v1[2]);
    cross[1] = (v1[2] * v2[0]) - (v2[2] * v1[0]);
    cross[2] = (v1[0] * v2[1]) - (v2[0] * v1[1]);

    func_80666AF8(arg0, cross[0], cross[1], cross[2], 1, arg2, 2);
}
