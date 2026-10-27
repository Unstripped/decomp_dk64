// func_8062A850 (src/global/2F550.c): func_8062A850 (src/global/2F550.c): stage 5, 12 diff lines. Target loads/stores D_80747CD0 with separate 'lui at' (no la); ours hoists 'lui v0/addiu v0' because uopt CSEs the lda of the load+store pair across blocks (not fixable by volatile, raw-address cast, (0,x) idioms, array decl, defining the var in the TU, storing in each branch). If the store goes through a different symbol the lui is separate (text then 7 diff lines) but the join block order stays [store; mov.s f0] vs target [mov.s f0; store in jr delay slot]. Permuter 400s found nothing readable (best deletes the store).
extern u8 D_807444F0;
extern u8 D_807444EC;
extern s8 D_807444C0;
extern s32 D_8076A0A8;
extern f32 D_80747CD0;

f32 func_8062A850(void) {
    f32 target;
    f32 step;
    f32 cur;
    s32 flag;

    target = 1.0f;
    if (D_807444F0 != 1 && D_807444EC == 1) {
        step = 999.0f;
    } else {
        step = 0.02f;
    }
    flag = D_807444EC == 1;
    if (flag) {
        flag = D_8076A0A8 != 0x50;
    }
    if (D_807444C0 != 0 && !flag) {
        target = target * 1.2;
    }
    cur = D_80747CD0;
    if (cur < target) {
        cur += step;
        if (target < cur) {
            cur = target;
        }
    } else {
        cur -= step;
        if (cur < target) {
            cur = target;
        }
    }
    D_80747CD0 = cur;
    return cur;
}
