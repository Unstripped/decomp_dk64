// func_80644A18 (src/global/478F0.c): CsNM4 stage 5-6: 27 diff lines (was 30). Frame 0x70 + text size now equal (178 vs 180 lines: target 2 more). Found: inline 'tm = D_807F5FD4[arg1][idx[1]].x' (f32 temp local) for the 2nd spline point of each call makes the target's lwc1 f2;mfc1 a3 (plain load gave lw a3); tm declared after idx..d2 with pz dropped keeps frame. Remaining: target spills frac to sp+0x6c at def (swc1 in the bgez delay slot) and reloads before cvt.d.s (f6) => frac web uncolored; mine colours frac f2, no store; temps f4/f6/f8/f10 vs f18/f16; swc1 x2,16(sp) after sw a1,68(sp) in target. Tried: &frac via fp local (gives frame/slot match and the spill but 3 separate cvt.d.s per call, no cached sdc1 double: worse 37), f64 t, volatile, arrays, dead stmts incl. idx forms, permuter 2x600s (no 0).
f32 splineEvalCubic(f64, f32, f32, f32, f32);

void func_80644A18(f32 *arg0, s16 arg1, s16 arg2, f32 arg3) {
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
