// func_807009F4 (src/global/103AB0.c): func_807009F4 (src/global/103AB0.c): Stage 6: 62 lines, instruction-identical except hi/mid regs: target hi=a1, mid=v1 (mine hi=v1, mid=a1). Needs 's32 ret; ret = t < 0 ? 0 : t' tail (not if/else) and s16 lo/hi/mid. Spelling toggles (32 variants), declaration order, deadsweep, 240s permuter: no change. Parked under NON_MATCHING.
extern s16 *D_8076A0A0;

s16 func_807009F4(s16 arg0) {
    s16 lo;
    s16 hi;
    s16 mid;
    s32 ret;
    s32 t;

    lo = 0;
    hi = 0x1FE;
    if (arg0 == -1) {
        return 0;
    }
    do {
        mid = (lo + hi) / 2;
        if (arg0 < D_8076A0A0[mid]) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
        if (arg0 >= D_8076A0A0[mid] && arg0 < D_8076A0A0[mid + 1]) {
            return mid + 8;
        }
    } while (hi >= lo);
    t = arg0 - 0x7C1B;
    ret = t < 0 ? 0 : t;
    return ret;
}
