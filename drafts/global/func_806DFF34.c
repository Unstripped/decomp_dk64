// func_806DFF34 (src/global/E4090.c): stage 6, 4 diff lines: only the loop mask is colored a0 (target: uncolored ugen temp t0, so 'and a3,v0,t0' with v0 first; ours 'and a3,a0,v0'). Found this unit: dead 'if (var_v0 & arg0) {}' before the real test makes the and-result a uopt candidate (a3, fixes t6-t9/t0 shifts and the return-load), and 'if (&arg0) {}' in the loop pins arg0 in memory (no 'u16 *unused'); K&R, s32/u16 mask locals, extra dead tests at every position and 60k permuter iterations on a standalone base did not stop the mask taking a0.
u16 func_806DFF34(u16 arg0, u16 *arg1) {
    u32 var_v0;
    u16 var_v1;
    u16 var_a2;

    var_v0 = *arg1;
    var_v1 = 0;
    var_a2 = 0;
    if (var_v0 != 0) {
        do {
            var_v1 |= var_v0;
            if (&arg0) {}
            arg1++;
            if (var_v0 & arg0) {}
            if (var_v0 & arg0) {
                var_a2 |= arg1[0];
            }
            var_v0 = arg1[1];
            arg1++;
        } while (var_v0 != 0);
    }
    return var_a2 | (arg0 & ~var_v1);
}
