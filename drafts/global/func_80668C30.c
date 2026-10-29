// func_80668C30 (src/global/6AD90.c): func_80668C30 (src/global/6AD90.c): stage 4/5 (64 text rows, shape 9, was 119): frame 0xC8 + slot layout exact. Remaining: f12/f18 (var_fa0/var_ft5) FP register swap in the spill reloads (target ldc1 f14,152;f18,136;f12,160;f16,144), li v1,1 vs move v1,t4 (hoisted 1), case-body f-reg numbering. Wins: split hx/hz half-sums with t0_d/t1_d before mid_x/mid_z, per-case assignment order (13824-perm search), decl-order hill-climb. Tried: m2c int temps (frame wrong), dead-stmt sweeps, mismatch spellings.
s32 func_80668C30(s16 *arg0, f32 arg1, f32 arg2) {
    f64 t0_d;
    f64 hx;
    f64 pad0[1]; // pad: reproduces slot layout (unused)
    f64 var_fv0;
    f64 var_fa0, var_fa1, var_ft4, var_ft5;
    f64 mid_x;
    f64 pad1[1]; // pad: reproduces slot layout (unused)
    f64 hz;
    f64 mid_z;
    f64 d_arg2;
    f64 d_arg1;
    f64 var_fv1;
    f64 pad2[1]; // pad: reproduces slot layout (unused)
    f64 var_fs0;
    f64 t1_d;
    s32 i;
    s32 mismatch = 0;

    hx = (f64)(arg0[1] + arg0[2]) * 0.5;
    hz = (f64)(arg0[7] + arg0[8]) * 0.5;
    t0_d = arg0[0];
    mid_x = (t0_d + hx) * 0.5;
    t1_d = arg0[6];
    mid_z = (t1_d + hz) * 0.5;
    d_arg1 = arg1;
    d_arg2 = arg2;

    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            var_ft5 = t1_d;
            var_fa1 = (f64)(arg0[7] - arg0[6]);
            var_ft4 = t0_d;
            var_fa0 = (f64)(arg0[1] - arg0[0]);
            break;
        case 1:
            var_ft4 = t0_d;
            var_ft5 = t1_d;
            var_fa0 = (f64)(arg0[2] - arg0[0]);
            var_fa1 = (f64)(arg0[8] - arg0[6]);
            break;
        case 2:
            var_fa0 = (f64)(arg0[2] - arg0[1]);
            var_ft4 = (f64)arg0[1];
            var_fa1 = (f64)(arg0[8] - arg0[7]);
            var_ft5 = (f64)arg0[7];
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
