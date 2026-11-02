// csSplineLightStep (src/global/478F0.c): UNPARKED 2026-11-02: park was 168 insns vs target 170 (count-inexact parks stay drafts); W4FpB: stage 5, 27 diff lines (unchanged, copy parked unchanged). frac (cand 17) adjsave 0.5 coloured f16, target uncoloured. Tried: dead ifs 1-4 after frac (adjsave 0.5->0.33 but still coloured), frac spelling (*1.0f,+0.0f,neg,casts,f64), i types, copy locals (fa/fb) and 2 hill-climbs (400s x2, annealing over dead tests/copies/decl order) no improvement below 27; frac def moved before px = 145.
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
