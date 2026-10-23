// func_8066A988 (src/global/6AD90.c): Identical twin of func_80669E04 at +0x24 offset; same-side half-plane point in triangle test

#include "common.h"
typedef struct {
    f32 x[3];
    f32 y[3];
    f32 z[3];
} R1C_TriangleF;

s32 func_80669E04(R1C_TriangleF *arg0, f32 arg1, f32 arg2) {
    f64 spA0;
    f64 sp98;
    f64 sp90;
    f64 sp88;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp44;
    f64 sp38;
    f32 temp_fs0;
    f32 temp_ft4;
    f32 temp_ft5;
    f64 temp_fa1;
    f64 temp_fs1;
    f64 temp_fs2;
    f64 temp_fs3;
    f64 temp_fs4;
    f64 temp_fs5;
    f64 var_fa0;
    f64 var_fa1;
    f64 var_fs0;
    f64 var_ft4;
    f64 var_ft5;
    f64 var_fv0;
    f64 var_fv1;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    temp_ft5 = arg0->x[1];
    temp_ft4 = arg0->x[2];
    temp_fs0 = arg0->z[2];
    sp58 = arg0->z[1];
    var_v1 = 0;
    sp54 = arg0->x[0];
    sp60 = temp_ft5;
    temp_fs5 = (f64) sp54;
    sp44 = arg0->z[0];
    sp64 = temp_ft4;
    temp_fa1 = (f64) sp44;
    temp_fs1 = (temp_fs5 + ((f64) (temp_ft4 + temp_ft5) * 0.5)) * 0.5;
    sp38 = temp_fa1;
    var_fa1 = sp98;
    temp_fs2 = (temp_fa1 + ((f64) (temp_fs0 + sp58) * 0.5)) * 0.5;
    var_fa0 = spA0;
    var_ft4 = sp90;
    var_ft5 = sp88;
    var_v0 = 0;
    sp5C = temp_fs0;
    temp_fs4 = (f64) arg2;
    temp_fs3 = (f64) arg1;
    do {
        switch (var_v0) {
        default:
            var_fv0 = (temp_fs3 - var_ft4) * var_fa1;
            var_fv1 = (temp_fs4 - var_ft5) * var_fa0;
            var_fs0 = ((temp_fs1 - var_ft4) * var_fa1) - ((temp_fs2 - var_ft5) * var_fa0);
            break;
        case 0:
            var_ft5 = sp38;
            var_ft4 = temp_fs5;
            var_fa0 = (f64) (sp60 - sp54);
            var_fa1 = (f64) (sp58 - sp44);
            var_fv0 = (temp_fs3 - temp_fs5) * var_fa1;
            var_fv1 = (temp_fs4 - var_ft5) * var_fa0;
            var_fs0 = ((temp_fs1 - temp_fs5) * var_fa1) - ((temp_fs2 - var_ft5) * var_fa0);
            break;
        case 1:
            var_ft5 = sp38;
            var_ft4 = temp_fs5;
            var_fa0 = (f64) (sp64 - sp54);
            var_fa1 = (f64) (sp5C - sp44);
            var_fv0 = (temp_fs3 - temp_fs5) * var_fa1;
            var_fv1 = (temp_fs4 - var_ft5) * var_fa0;
            var_fs0 = ((temp_fs1 - temp_fs5) * var_fa1) - ((temp_fs2 - var_ft5) * var_fa0);
            break;
        case 2:
            var_ft4 = (f64) sp60;
            var_fa0 = (f64) (sp64 - sp60);
            var_fa1 = (f64) (sp5C - sp58);
            var_ft5 = (f64) sp58;
            var_fv0 = (temp_fs3 - var_ft4) * var_fa1;
            var_fv1 = (temp_fs4 - var_ft5) * var_fa0;
            var_fs0 = ((temp_fs1 - var_ft4) * var_fa1) - ((temp_fs2 - var_ft5) * var_fa0);
            break;
        }
        var_v0 += 1;
        var_a1 = -1;
        if (var_fv1 <= var_fv0) {
            var_a1 = 1;
        }
        var_a0 = -1;
        if (var_fs0 >= 0.0) {
            var_a0 = 1;
        }
        if (var_a0 != var_a1) {
            var_v1 = 1;
        }
    } while (var_v0 != 3);
    sp88 = var_ft5;
    sp90 = var_ft4;
    sp98 = var_fa1;
    spA0 = var_fa0;
    return (var_v1 == 0) & 0xFF;
}
