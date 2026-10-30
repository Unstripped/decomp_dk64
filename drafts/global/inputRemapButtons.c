// inputRemapButtons (src/global/E4090.c): stage 6, 2 diff lines: only the hoisted loop mask is colored a0 (target: uncolored/7th color t0, 'and a3,v0,t0'; ours 'and a3,a0,v0'). Theory this unit (uopt -l 5/6): a0 must be unavailable to BOTH the mask (cand cvt(cvt(arg0)), allowed {a0,a3,t0}) and the and-result (colored first -> a3), but the &arg0 const candidate is forbidden regs 1-6 so cannot take a0; priority order is mask before and-result. Tried this unit without effect: 1440+4000 type/test/pin combos (ANSI/K&R, s32/u16/u32 locals, tmp locals, tests plain/rev/cast), 648 positions x counts of dead 'if (&arg0) {}' (raising its adjsave to 7.5 does not reorder coloring), SA over dead tests/forms 80k iters (arg0,&arg0,v&arg0,~var_v1 syms).
u16 inputRemapButtons(u16 arg0, u16 *arg1) {
    u32 var_v0;
    u16 var_v1;
    u16 var_a2;

    var_v0 = *arg1;
    var_v1 = 0;
    var_a2 = 0;
    if (var_v0 != 0) {
        do {
            var_v1 |= var_v0;
            if (&arg0) {} // FAKE: pins arg0 in memory
            arg1++;
            if (var_v0 & arg0) {} // FAKE: makes the and-result a uopt candidate
            if (var_v0 & arg0) {
                var_a2 |= arg1[0];
            }
            var_v0 = arg1[1];
            arg1++;
        } while (var_v0 != 0);
    }
    return var_a2 | (arg0 & ~var_v1);
}
