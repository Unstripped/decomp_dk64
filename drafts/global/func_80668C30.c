// func_80668C30 (src/global/6AD90.c): STAGE 4: frame 0xC8 and stack slot layout exact (padTop[4]+padMid[1] reserve slots; first-declared highest: fa0 0xA0,fa1,ft4,ft5 then 10 doubles down to t1_d 0x38). ~119 text rows left: regalloc/load order (expected loads x1,x2,z2,z1 first then x0,z0; mid_x/mid_z before t0_d/t1_d). Permuted the 6 head statements (720 orders): no improvement.
s32 func_80668C30(s16 *arg0, f32 arg1, f32 arg2) {
    f64 padTop[4]; // pad: reproduces frame 0xC8 / slot layout (unused)
    f64 var_fa0, var_fa1, var_ft4, var_ft5;
    f64 padMid[1]; // pad: reproduces slot layout (unused)
    f64 var_fv0, var_fv1, var_fs0;
    f64 mid_x, mid_z;
    f64 d_arg1, d_arg2;
    f64 t0_d, t1_d;
    s32 i;
    s32 mismatch = 0;

    d_arg1 = arg1;
    d_arg2 = arg2;
    mid_x = ((f64)arg0[0] + (f64)(arg0[2] + arg0[1]) * 0.5) * 0.5;
    mid_z = ((f64)arg0[6] + (f64)(arg0[8] + arg0[7]) * 0.5) * 0.5;
    t0_d = arg0[0];
    t1_d = arg0[6];

    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            var_ft4 = t0_d;
            var_ft5 = t1_d;
            var_fa0 = (f64)(arg0[1] - arg0[0]);
            var_fa1 = (f64)(arg0[7] - arg0[6]);
            break;
        case 1:
            var_ft4 = t0_d;
            var_ft5 = t1_d;
            var_fa0 = (f64)(arg0[2] - arg0[0]);
            var_fa1 = (f64)(arg0[8] - arg0[6]);
            break;
        case 2:
            var_ft4 = (f64)arg0[1];
            var_ft5 = (f64)arg0[7];
            var_fa0 = (f64)(arg0[2] - arg0[1]);
            var_fa1 = (f64)(arg0[8] - arg0[7]);
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
