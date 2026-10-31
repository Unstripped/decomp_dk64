// func_80668C30 (src/global/6AD90.c): func_80668C30 (src/global/6AD90.c): stage 5, parked NON_MATCHING. Registers now right: u32 mismatch (fixes li v1,1 vs move v1,t4: the s32 1 is CSE'd with the case/ternary 1 constant, a u32 one is not) and case assignments in declaration order var_fa0,fa1,ft4,ft5 (uopt FP var regs f12,f14,f16,f18 follow first-appearance order, so ft5 gets f18) -> shape 0 (instruction shapes identical), spill slots 136..160 and f12/f18 now match. Remaining (full=99 only from ordering): (1) prologue FIFO temp ring one slot off (mtc1 t1,f8/add.d f6 in target vs f6/f8 ours; 4480 hx,hz,t0,mid_x,t1,mid_z,d1,d2 statement orders tried, none fixes it and keep f22..f28), (2) in each case body the target emits a1,b1,mulA,c1,mulB,c2... (source order a,b,c: ring a1=f4,b1=f6,c1=f8,c2=f4) but ours emits c first then a,b (ring c1=f4...): all 6 a/b/c statement orders and mul operand swaps (96 forms), inlining a/b into the compare, q1/q2 temps in place of the pads: no change.
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
    u32 mismatch = 0;

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
            var_fa0 = (f64)(arg0[1] - arg0[0]);
            var_fa1 = (f64)(arg0[7] - arg0[6]);
            var_ft4 = t0_d;
            var_ft5 = t1_d;
            break;
        case 1:
            var_fa0 = (f64)(arg0[2] - arg0[0]);
            var_fa1 = (f64)(arg0[8] - arg0[6]);
            var_ft4 = t0_d;
            var_ft5 = t1_d;
            break;
        case 2:
            var_fa0 = (f64)(arg0[2] - arg0[1]);
            var_fa1 = (f64)(arg0[8] - arg0[7]);
            var_ft4 = (f64)arg0[1];
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
