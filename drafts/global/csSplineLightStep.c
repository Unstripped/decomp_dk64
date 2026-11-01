// csSplineLightStep (src/global/478F0.c): stage 5, 27 diff lines: frac assigned f16 (adjsave 0.5) vs left in stack home 0x6C(sp). Tested f32 frac[1] memory-resident local which reproduces exact delay-slot swc1 and jal-delay lwc1 ft4/ft5 instructions; remaining blocker is preventing uopt from assigning f16 to scalar frac without altering 0x70 frame.
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
