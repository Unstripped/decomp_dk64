// func_8066A834 (src/global/6AD90.c): 85 insns: logic fully recovered (2D XZ triangle bounding box test), K&R definition reproduces spills at 0x2C/0x30; frame size 0x28 vs 0x10
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

s32 func_8066A834(arg0, arg1, arg2)
R2D_TriangleAC10 *arg0;
f32 arg1;
f32 arg2;
{
    f32 sp20;
    f32 sp1C;
    f32 sp0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fv0;
    s32 var_v0;

    temp_fv1 = arg0->tri.x[1];
    temp_fv0 = arg0->tri.x[0];
    if (temp_fv0 < temp_fv1) {
        var_fa0 = temp_fv0;
    } else {
        var_fa0 = temp_fv1;
    }
    temp_fa1 = arg0->tri.x[2];
    if (!(var_fa0 < temp_fa1)) {
        var_fa0 = temp_fa1;
    }
    temp_ft4 = arg0->tri.z[0];
    temp_ft5 = arg0->tri.z[1];
    if (temp_ft4 < temp_ft5) {
        sp20 = temp_ft4;
    } else {
        sp20 = temp_ft5;
    }
    sp0 = arg0->tri.z[2];
    if (!(sp20 < sp0)) {
        sp20 = sp0;
    }
    if (temp_fv1 < temp_fv0) {
        sp1C = temp_fv0;
    } else {
        sp1C = temp_fv1;
    }
    if (!(temp_fa1 < sp1C)) {
        sp1C = temp_fa1;
    }
    if (temp_ft5 < temp_ft4) {
        var_fv0 = temp_ft4;
    } else {
        var_fv0 = temp_ft5;
    }
    if (!(sp0 < var_fv0)) {
        var_fv0 = sp0;
    }
    if ((arg1 < var_fa0) || (sp1C < arg1) || (arg2 < sp20) || (var_v0 = 1, (var_fv0 < arg2))) {
        var_v0 = 0;
    }
    return var_v0;
}
