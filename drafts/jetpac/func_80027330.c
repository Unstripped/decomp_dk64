// func_80027330 (src/jetpac/3060.c): stage 6: 4 insns off; result variable lands in v1 (move v1,v0 / move v1,zero / li v1,1 / move v0,v1) instead of v0 throughout. Tried &&, nested if, ternary, u8/s8/u32 returns, != 0, line splits, permuter 120s (best 15 not equivalent).
s32 func_80027330(f32 arg0) {
    s32 r;
    r = (165.0f <= arg0);
    if (r != 0) {
        r = (arg0 <= 171.0f);
    }
    return r;
}
