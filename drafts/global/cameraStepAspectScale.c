// cameraStepAspectScale (src/global/2F550.c): cameraStepAspectScale (src/global/2F550.c): stage 5, diff 8 (W4FpA, unchanged park): only the tail differs: target join block = [mov.s f0,f12; swc1 f12 (jr delay)], bc1fl copies the mov; ours [swc1; mov.s (jr delay)], bc1f+nop. NEW tried (all 8): ret local with copy-prop killers (cur=0.0f dead store makes ret an f2 web: 6 text but mov.s f2 + trailing mov f0), ret assigned per arm, store per arm / per arm + ret (16), returns in arms (16), comma returns, chain assigns via p and via global (global chain reloads f0 after store), volatile store cast (8) / volatile p (18), f64 return (text 5, cvt pair), K&R def, target=cur / step=cur return variable, 512-way line-join grid over the tail braces/stores/return (all 8), deadsweep 540 variants (none). Why ret cannot be f0: -l 5 shows a ret var copied into R is forbidden f0 (R candidate 58 overlaps) so it takes f2. uopt candidate order shows the istr numbered BEFORE the R store; target needs R=cur before the store in ucode. Open: any C that emits the retval copy before the global store (no similar matched function: similar.py none).
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
