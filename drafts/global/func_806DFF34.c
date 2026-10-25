// func_806DFF34 (src/global/E4090.c): Structure/text identical; only regalloc differs: target keeps u16 arg0 unpromoted (lhu 2(sp) twice, in t9/t0 hoisted) with loop mask in v0/and-temp a3; ours promotes arg0 to a0. 'u16 *unused=&arg0;' reproduces the lhu-from-home but regs still differ (loop var a3/v0, and-temp t7). Tried decl-order sweep, K&R, s32 vars, permuter 400s.
u16 func_806DFF34(u16 arg0, u16 *arg1) {
    u16 var_v0;
    u16 var_v1;
    u16 var_a2;

    var_v0 = *arg1;
    var_v1 = 0;
    var_a2 = 0;
    if (var_v0 != 0) {
        do {
            var_v1 |= var_v0;
            arg1++;
            if (var_v0 & arg0) {
                var_a2 |= arg1[0];
            }
            var_v0 = arg1[1];
            arg1++;
        } while (var_v0 != 0);
    }
    return var_a2 | (arg0 & ~var_v1);
}
