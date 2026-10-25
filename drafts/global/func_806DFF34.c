// func_806DFF34 (src/global/E4090.c): stage 6, 16 diff lines: &arg0 pin (u16 *unused = &arg0) + u32 var_v0. Target keeps the loop mask as plain temp t0 and the and-result in a3 (lhu t9,2(sp) return load hoisted into beqz delay slot); ours promotes the loop mask into a0 and the and-result is a temp t7. Tried K&R, types of locals, tmp var, mask copies, if(1)/do-while wrappers, permuter 600s.
u16 func_806DFF34(u16 arg0, u16 *arg1) {
    u16 *unused = &arg0;
    u32 var_v0;
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
