// inputRemapButtons (src/global/E4090.c): W2IntA: stage 6, score 2 unchanged ('lhu a0,2(sp)' + 'and a3,v0,a0' vs target t0). Trace: cand 23 (ucvt(u16 home load), preheader def, forbidden [v0 v1 a1 a2]) takes a0 as first free; target needs a0 blocked (or the cand live in the entry block: 'a0 skipped'). Tried this unit: preheader m local (u32/s32/u16/s16/u8 x 5 init spellings x 5 test spellings x dead on/off, 110 variants: all 2); without '&arg0' FAKE arg0 stays register-resident (andi t6,a0 / move a0,t6 + a3 copy: 15), so the original must have kept arg0 in memory some other way.
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
            if ((u32)var_v0 & arg0) {} // FAKE: makes the and-result a uopt candidate
            if ((u32)var_v0 & arg0) {
                var_a2 |= arg1[0];
            }
            var_v0 = arg1[1];
            arg1++;
        } while (var_v0 != 0);
    }
    return var_a2 | (arg0 & ~var_v1);
}
