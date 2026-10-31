// csSplineLightStep (src/global/478F0.c): OlW stage 5 (unchanged, 27 diff lines of 180 insns, frame 0x70 ok). Re-diffed: ALL diff lines come from one cause: target frac is an uncolored M var (swc1 f4,108(sp) in the bgez delay slot, lwc1 f6,108(sp) before the one cvt.d.s that is CSE'd to sdc1/ldc1 0x38) while mine colors frac into f16 (uopt trace -l 6: no starvation); this shifts the FP ring (trunc f6/f4/f8/f10 vs f4/f18/f6/f8) and the later arg temps. Tried: comma/unary-plus wrappers (0,x)/+x/(f32)/(f64) on every site of the early statements incl pairs (<=2 combos, 12 sites, no score change), 1300-iter hill-climb of statement swaps/joins/decl swaps (27 never improved), plus everything in the previous note. Still needs a zero-code source form that makes frac uncolored.
f32 splineEvalCubic(f64, f32, f32, f32, f32);

void csSplineLightStep(f32 *arg0, s16 arg1, s16 arg2, f32 arg3) {
    f32 frac;
    s32 i;
    u8 idx[4];
    f32 px;
    f32 py;
    f32 tm;
    s32 d0;
    s32 d1;
    s32 d2;
    *arg0 -= arg3;
    if (*arg0 < 0.0f) {
        *arg0 = arg2;
    }
    i = *arg0;
    frac = *arg0 - i;
    idx[0] = i - 1 < 0 ? 0 : i - 1;
    idx[1] = i;
    idx[2] = i + 1 >= arg2 ? arg2 - 1 : i + 1;
    idx[3] = i + 2 >= arg2 ? arg2 - 1 : i + 2;
    px = splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].x, (tm = D_807F5FD4[arg1][idx[1]].x), D_807F5FD4[arg1][idx[2]].x, D_807F5FD4[arg1][idx[3]].x);
    py = splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].y, (tm = D_807F5FD4[arg1][idx[1]].y), D_807F5FD4[arg1][idx[2]].y, D_807F5FD4[arg1][idx[3]].y);
    lightAdd(px, py, splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].z, (tm = D_807F5FD4[arg1][idx[1]].z), D_807F5FD4[arg1][idx[2]].z, D_807F5FD4[arg1][idx[3]].z), 0.0f, 0.0f, 0.0f, 250.0f, 0, 0xFF, 0xFF, 0xFF);
}
