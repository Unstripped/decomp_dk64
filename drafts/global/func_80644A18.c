// func_80644A18 (src/global/478F0.c): CsNM7 stage 5: still 27 lines / 2 insns short (frame 0x70 ok). Root cause (uopt trace -l 5): in the target frac (cand 17) is NOT register-colored (plain M var: swc1 at def in the bgez delay slot, lwc1 right before cvt.d.s; the cvt.d.s(frac) expr is the CSE'd/spilled double at sp+0x38, a uopt spill not a named local, a1*4 spilled at 0x44), and that makes every FP temp of the early part come out f6/f4/f8/f10; mine colors frac into f16 (allowed regs 28/29 only). Verified starvation theory: an extra live f32 'q = *arg0; i = q; ... if (q == 0) {} before lightAdd' reproduces the target's FP numbering exactly (trunc f6, cvt.s.w f4, mtc1 f8, cvt f10) but adds a mov.s + 8 frame bytes. Declaring frac as 'f32 frac[1]' (+2 pad s32) gives the store in the bgez slot and the lwc1 reload (frame 0x70) but array loads are not CSE'd across calls (3 reload+cvt.d.s per call, no sdc1/ldc1) -> 31 lines/181 insns; an f64 fd named local gives sdc1 at a named (wrong) slot. Union/struct{f32}/&frac dummy/volatile/{f32 fz} scope/dead stores/dead compares of frac all keep it colored or add frame. Also tried: deadsweep sweep incl --forms and frac/px/py/tm/arg3 extras, every (f32)/(f64)/narrowing spelling of frac, i, px, py, tm, joiner over all same-line masks of the body (<=5 joins), random decl-order/pad search (150+300 orders), permuter 600s (best 975 vs 1111 base). Needs a source form where frac is an uncolored non-aliased scalar (one def, one use) i.e. a zero-code FP candidate that occupies f16/f18 across the idx diamond.
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
