// inputRemapButtons (src/global/E4090.c): stage 6, 2 diff lines unchanged ('lhu a0,2(sp); and a3,a0,v0' vs expected 'lhu t0,2(sp); and a3,v0,t0'). uopt -l5: mask cvt(cvt(P 3 2)) is coloured a0 (index order 0,2,6,9,23,24,41; cand 9 var_a2 skips a0 because arg0's incoming a0 interferes in the entry block). Target has the mask as a ring temp (t0) after the post-loop t9 load: needs the mask NOT a candidate, or an extra a0 occupant coloured before it. W3Label 2026-11-01: K&R definition (reg-resident via andi, 26 lines), 'used/out/cur' rewrites with while/do forms (18-26), prior note's other attempts. No new lever found. || PREVIOUS NOTES: stage 6, 2 diff lines unchanged: hoisted loop mask (cvt(cvt(arg0)), uopt cand 23) colored a0, target t0 ('and a3,v0,t0'). uopt -l 5/6 facts: all 7 cands are 'unconstrained' and colored in INDEX order (0,2,6,9,23,24,41), each taking the lowest reg not used by already-colored interferers (forbidden lists = neighbours' colors); 23 (sub-expression of 24) always precedes 24, so target order (and=a3 before mask=t0 with a0 occupied) needs an extra a0 occupant X plus 24 colored before 23, i.e. not reachable by index order. Tried this unit without effect: 4000 dead 'if (x op y) {}' pairs over {arg0,var_v0,var_v1,var_a2,arg1,1,0xFF} at loop positions, 26k-iter hill-climb adding dead tests + extra u16/s32/u32/u8 locals with assignments, loop forms (while/for/assign-in-cond), *(u16*)&arg0 / *(&arg0) / u16 *p=&arg0 spellings, named and-result locals (copy-propagated away).
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
