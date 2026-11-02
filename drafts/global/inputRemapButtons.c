// inputRemapButtons (src/global/E4090.c): stage 6, 2 diff lines (unchanged): mask 'lhu a0,2(sp)' vs target t0 ('and a3,v0,t0' exact with (u32)var_v0 & arg0 dead+real test). W3IntB: uopt -l5/-l6 trace shows colour order by table index 0,2,6,9,23(mask cvt chain)=a0,24(and)=a3,41(const home reload)=t0 UNUSED; target needs 23 absent or a0 forbidden. Tried: K&R def (formal stays in a0), 2520-variant dummy-z grid (z=0/z=expr + no-code defs/dead tests: a no-code z holds NO reg), hit var w/ entry init, *(&arg0)/p=&arg0 reads, entry-block mask refs, type x cast grids (14k), 40k-step hill-climbs with x|0,x&MASK,x=0 forms: none below 2.
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
