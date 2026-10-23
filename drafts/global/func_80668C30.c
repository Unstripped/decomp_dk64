// func_80668C30 (src/global/6AD90.c): pointInTriangle2D_S, stack frame 0xA0 vs 0xC8
typedef struct R1C_TriangleS {
    s16 x[3];
    s16 y[3];
    s16 z[3];
} R1C_TriangleS;

s32 func_80668C30(R1C_TriangleS *arg0, f32 arg1, f32 arg2) {
    f64 var_fa0, var_fa1, var_ft4, var_ft5;
    f64 var_fv0, var_fv1, var_fs0;
    f64 mid_x, mid_z;
    f64 d_arg1, d_arg2;
    f64 t0_d, t1_d;
    s32 i;
    s32 mismatch = 0;

    d_arg1 = arg1;
    d_arg2 = arg2;
    t0_d = arg0->x[0];
    t1_d = arg0->z[0];

    mid_x = (t0_d + (f64)(arg0->x[2] + arg0->x[1]) * 0.5) * 0.5;
    mid_z = (t1_d + (f64)(arg0->z[2] + arg0->z[1]) * 0.5) * 0.5;

    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            var_ft4 = t0_d;
            var_ft5 = t1_d;
            var_fa0 = (f64)(arg0->x[1] - arg0->x[0]);
            var_fa1 = (f64)(arg0->z[1] - arg0->z[0]);
            break;
        case 1:
            var_ft4 = t0_d;
            var_ft5 = t1_d;
            var_fa0 = (f64)(arg0->x[2] - arg0->x[0]);
            var_fa1 = (f64)(arg0->z[2] - arg0->z[0]);
            break;
        case 2:
            var_ft4 = (f64)arg0->x[1];
            var_ft5 = (f64)arg0->z[1];
            var_fa0 = (f64)(arg0->x[2] - arg0->x[1]);
            var_fa1 = (f64)(arg0->z[2] - arg0->z[1]);
            break;
        }

        var_fv0 = (d_arg1 - var_ft4) * var_fa1;
        var_fv1 = (d_arg2 - var_ft5) * var_fa0;
        var_fs0 = ((mid_x - var_ft4) * var_fa1) - ((mid_z - var_ft5) * var_fa0);

        if ((var_fv1 <= var_fv0 ? 1 : -1) != (var_fs0 >= 0.0 ? 1 : -1)) {
            mismatch = 1;
        }
    }

    return (mismatch == 0) & 0xFF;
}
