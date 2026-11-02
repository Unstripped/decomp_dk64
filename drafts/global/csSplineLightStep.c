// csSplineLightStep (src/global/478F0.c): csSplineLightStep (src/global/478F0.c): stage 5, 27 diff lines (unchanged). Root cause confirmed: target frac (isvar, uopt cand 17) is UNCOLOURED (swc1 f4,108(sp) at def, lwc1 f6,108(sp) before first cvt.d.s, +2 insns vs ours 178/180) while ours colours it f16 (adjsave 0.5, forbidden f0-f14 only); the early FP ring diffs (trunc f6 vs f4, cvt f4 vs f18) cascade. Tried leitovers-5 levers: f32 frac[1] and &frac dead tests (memory-resident: frame 104 vs 112 and cvt.d.s not CSE'd across calls: 58 lines), declaration order+pad permutations (best 31), dead if/FP tests on frac after each call and 1-6 dead ifs inside def-use range, frac copy locals/chained defs, wrapping calls in if(1)/do-while, deadsweep (336 variants). None made adjsave<=0.
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
