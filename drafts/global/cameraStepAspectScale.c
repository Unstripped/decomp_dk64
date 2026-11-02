// cameraStepAspectScale (src/global/2F550.c): stage 5, diff 8: pointer spelling (p = &D_80747CD0; cur = *p; *p = cur) gives separate lui at (no lda hoist, lui at hoist matches). Remaining: ucode order of return mov.s f0,f12 vs store: target has mov.s BEFORE s.s (join: mov; jr; swc1 delay, bc1fl copies mov); ours store then mov (jr delay = mov, bc1f+nop). as1probe: swapping the two ugen records gives 0. Tried ret local (copy-propagated), f64 ret (cvt), chain assigns, x=x, one-line, return *p. Open: C order that puts the return move before the store.
extern u8 D_807444F0;
extern u8 D_807444EC;
extern s8 D_807444C0;
extern s32 gCurrentMap;
extern f32 D_80747CD0;

f32 cameraStepAspectScale(void) {
    f32 target;
    f32 step;
    f32 cur;
    s32 flag;
    f32 *p;

    target = 1.0f;
    if (D_807444F0 != 1 && D_807444EC == 1) {
        step = 999.0f;
    } else {
        step = 0.02f;
    }
    flag = D_807444EC == 1;
    if (flag) {
        flag = gCurrentMap != 0x50;
    }
    if (D_807444C0 != 0 && !flag) {
        target = target * 1.2;
    }
    p = &D_80747CD0;
    cur = *p;
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
    *p = cur;
    return cur;
}
