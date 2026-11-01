// inputRemapButtons (src/global/E4090.c): stage 6, 2 diff lines unchanged: hoisted loop mask (cvt(cvt(arg0)), uopt cand 23) colored a0, target t0 ('and a3,v0,t0'). uopt -l 5/6 facts: all 7 cands are 'unconstrained' and colored in INDEX order (0,2,6,9,23,24,41), each taking the lowest reg not used by already-colored interferers (forbidden lists = neighbours' colors); 23 (sub-expression of 24) always precedes 24, so target order (and=a3 before mask=t0 with a0 occupied) needs an extra a0 occupant X plus 24 colored before 23, i.e. not reachable by index order. Tried this unit without effect: 4000 dead 'if (x op y) {}' pairs over {arg0,var_v0,var_v1,var_a2,arg1,1,0xFF} at loop positions, 26k-iter hill-climb adding dead tests + extra u16/s32/u32/u8 locals with assignments, loop forms (while/for/assign-in-cond), *(u16*)&arg0 / *(&arg0) / u16 *p=&arg0 spellings, named and-result locals (copy-propagated away).
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
