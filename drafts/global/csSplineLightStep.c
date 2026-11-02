// csSplineLightStep (src/global/478F0.c): Cs 2026-11-02: PARKED stage 4 in copy (count 180 = target, frame 0x70, deadsweep score 27 -> 23 full / shape 12). Remaining diff = stack slots (named f64 fd lives at 72(sp), target keeps the CSE'd (f64)frac in a save-around-call temp at 56(sp), arg1*4 temp 60 vs 68), FP ring regs of the stack-arg temps (f8/f10,f4/f6 vs target f16/f18 every call) and swc1 16(sp) order. KEY: target frac is an UNCOLOURED isvar (swc1 at def in bgez delay slot, lwc1+cvt.d.s at call 1) with the cvt CSE'd across the 3 calls; scalar frac always gets coloured f16 (adjsave 0.5 = uses - 0.5*defs; no no-code FP def exists: *1.0f/+0.0f/-0.0f fold away, *1.0 adds cvt.d.s/cvt.s.d, dead FP tests only add a save-around-call). f32 frac[1] gives memory residency (count 181: 3 lwc1+cvt, cvt not CSE'd across calls); + named f64 fd = frac[0] before call 1 restores 180 and the exact prologue. Tried (all <=27): do-while/if(1)/for(;;) wrappers (fold), &frac==&px address-taken (181), scope blocks, frac = *arg0-(s32)*arg0 orders, t=*arg0 locals with (t-i) inline (sub not hoisted), nested lightAdd(splineEvalCubic...) without named px/py (hidden temps land at 76/80 ascending, frame 104), 3 named tm locals, dead tests on frac/arg3 after each call, annealing (3 harnesses, ~35k evals). Untried: none cheap; a plain uncoloured FP isvar is the missing lever.
f32 splineEvalCubic(f64, f32, f32, f32, f32);

void csSplineLightStep(f32 *arg0, s16 arg1, s16 arg2, f32 arg3) {
    f32 frac[1]; // FAKE: memory-resident frac (swc1 at def, lwc1 at the first call)
    s32 d1; // FAKE: frame pad
    u8 idx[4];
    f32 px;
    f32 py;
    s32 i;
    s32 d0; // FAKE: frame pad
    f64 fd; // FAKE: names the CSE'd (f64)frac that the target keeps in a save-around-call temp
    f32 tm;
    *arg0 -= arg3;
    if (*arg0 < 0.0f) {
        *arg0 = arg2;
    }
    i = *arg0;
    frac[0] = *arg0 - i;
    idx[0] = i - 1 < 0 ? 0 : i - 1;
    idx[1] = i;
    idx[2] = i + 1 >= arg2 ? arg2 - 1 : i + 1;
    idx[3] = i + 2 >= arg2 ? arg2 - 1 : i + 2;
    fd = frac[0];
    px = splineEvalCubic(fd, D_807F5FD4[arg1][idx[0]].x, (tm = D_807F5FD4[arg1][idx[1]].x), D_807F5FD4[arg1][idx[2]].x, D_807F5FD4[arg1][idx[3]].x); // FAKE: tm assignment steers the 3rd arg through a coloured FP candidate (f2)
    py = splineEvalCubic(fd, D_807F5FD4[arg1][idx[0]].y, (tm = D_807F5FD4[arg1][idx[1]].y), D_807F5FD4[arg1][idx[2]].y, D_807F5FD4[arg1][idx[3]].y); // FAKE: tm assignment (as above)
    if (py == 0) {} // FAKE: deadsweep, FP candidate piece colouring
    lightAdd(px, py, splineEvalCubic(fd, D_807F5FD4[arg1][idx[0]].z, (tm = D_807F5FD4[arg1][idx[1]].z), D_807F5FD4[arg1][idx[2]].z, D_807F5FD4[arg1][idx[3]].z), 0.0f, 0.0f, 0.0f, 250.0f, 0, 0xFF, 0xFF, 0xFF); // FAKE: tm assignment (as above)
    if (px && px) {} // FAKE: deadsweep, FP candidate piece colouring
    if (px && px) {} // FAKE: deadsweep, FP candidate piece colouring
    if (idx[1]) {} // FAKE: deadsweep, FP candidate piece colouring
}
