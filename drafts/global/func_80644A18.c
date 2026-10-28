// func_80644A18 (src/global/478F0.c): stage 5-6: frame 0x70 OK (needs 4 dummy locals pz,d0-d2 after py), text size equal. Diff: frac (sp+0x6c) is spilled in orig (swc1 in bgez delay slot, lwc1 reload before cvt.d.s; f4/f6/f8/f10 temps) but colored f2 here; 3rd splineEvalCubic arg is lwc1 f2+mfc1 a3 in orig vs lw a3 here. Tried t f64 local, volatile, f32* indexing, deadsweep, permuter 240s (best 3379 vs 3590)
f32 splineEvalCubic(f64, f32, f32, f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_80644A18(f32 *arg0, s16 arg1, s16 arg2, f32 arg3) {
    f32 frac;
    s32 i;
    u8 idx[4];
    f32 px;
    f32 py;
    f32 pz;
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
    px = splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].x, D_807F5FD4[arg1][idx[1]].x, D_807F5FD4[arg1][idx[2]].x, D_807F5FD4[arg1][idx[3]].x);
    py = splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].y, D_807F5FD4[arg1][idx[1]].y, D_807F5FD4[arg1][idx[2]].y, D_807F5FD4[arg1][idx[3]].y);
    lightAdd(px, py, splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].z, D_807F5FD4[arg1][idx[1]].z, D_807F5FD4[arg1][idx[2]].z, D_807F5FD4[arg1][idx[3]].z), 0.0f, 0.0f, 0.0f, 250.0f, 0, 0xFF, 0xFF, 0xFF);
}
