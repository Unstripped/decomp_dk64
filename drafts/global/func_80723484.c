// func_80723484 (src/global/127B00.c): Fx127A2 stage 5 (QS2 revisit 2): parked NON_MATCHING in 127B00.c. All integer regs/ctrl flow match (needs the 2 FAKE deadsweep stmts: path==0, total&&total; without them 338 diff lines); only FP left (4 shape rows): target has NO prog copy (lwc1 f2 shared by mul/add/sub, no mov.s f0,f2), fa is an uncolored ring temp (f6), ratio f0, step f12; mine has prog f0 + load temp f2, fa f12, ratio f14, step f16. 'ratio' local (narrowed div result, step = unk20 * ratio) moves ldc1 300.0 into place (shape 8 -> 4). Tried: noprog/inline all (fa cvt fixup branch lands after the mul: bgezl), pb->unkC = prog +/- step, decl-order perms of fp locals (no effect), unused locals (none), deadsweep round 1 on locals (best -8 rows full only: if (fa && fa) {} full 85 shape 5), permuter 540s (845 vs 1335 via junk).
typedef struct PathPlaybackView {
    s32 unk0;
    PathEntry path;
    f32 unkC;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 pad17;
    s32 unk18;
    s32 unk1C;
    u8 unk20;
    u8 unk21;
} PathPlaybackView;

void func_80723484(s32 arg0) {
    PathPlaybackView *pb;
    PathEntry *path;
    f32 prog;
    f32 step;
    f32 fa;
    f32 ratio;
    s32 next;
    s32 tmp;
    s32 limit;
    s32 quot;
    s32 total;
    u32 tq;
    s32 whole;

    if (arg0 != -1 && D_807FDBF8[arg0] != NULL && ((PathPlaybackView *)D_807FDBF8[arg0])->unk21 != 0) {
        pb = (PathPlaybackView *)D_807FDBF8[arg0];
        path = &pb->path;
        if (path == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (pb->unk16 == 0) {
            path = &pb->path;
            next = pb->unk10 + 1;
        } else {
            tmp = pb->unk10 + 1;
            if (tmp >= path->unk4) {
                next = tmp % (path->unk4 - 1);
            } else {
                next = tmp;
            }
        }
        prog = pb->unkC;
        fa = (f32)(u32)path->unk0[pb->unk10 * 10 + 8];
        ratio = (f32)((f64)(fa + (f32)(path->unk0[next * 10 + 8] - path->unk0[pb->unk10 * 10 + 8]) * prog) / 300.0);
        step = (f32)(u32)pb->unk20 * ratio;
        switch (pb->unk14) {
        case 0:
            pb->unkC += step;
            whole = (s32)pb->unkC;
            pb->unk10 = pb->unk10 + whole;
            pb->unkC -= (f32)whole;
            if (pb->unk16 == 0) {
                limit = pb->path.unk4 - 1;
            } else {
                limit = pb->path.unk4;
            }
            if (pb->unk10 >= limit) {
                limit = pb->path.unk4 - 1;
                quot = pb->unk10 / limit;
                total = pb->unk1C += quot;
                if (total >= pb->unk18 && pb->unk18 != -1) {
                    pb->unk10 = pb->path.unk4 - 2;
                    pb->unk21 = 0;
                    pb->unkC = 1.0f;
                    if (pb->unk15 == 1) {
                        pb->unk14 = 1;
                    }
                } else {
                    switch (pb->unk15) {
                    case 0:
                        if (total && total) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        if (pb->unk16 == 0) {
                            pb->unk10 = pb->unk10 % limit;
                        } else {
                            pb->unk10 = pb->unk10 % pb->path.unk4;
                        }
                        break;
                    case 1:
                        if (quot != 0) {
                            pb->unk14 = 1;
                            pb->unk10 = pb->path.unk4 - 2;
                            pb->unkC = 1.0f;
                        }
                        break;
                    }
                }
            }
            break;
        case 1:
            pb->unkC -= step;
            if ((f64)pb->unkC < 0.0) {
                whole = (s32)pb->unkC - 1;
                pb->unk10 = pb->unk10 + whole;
                pb->unkC -= (f32)whole;
            }
            if (pb->unk10 < 0) {
                limit = -pb->unk10;
                quot = limit / pb->path.unk4;
                total = pb->unk1C += quot + 1;
                if (total >= pb->unk18 && pb->unk18 != -1) {
                    pb->unk10 = 0;
                    pb->unk21 = 0;
                    pb->unkC = 0.0f;
                    if (pb->unk15 == 1) {
                        pb->unk14 = 0;
                    }
                } else {
                    switch (pb->unk15) {
                    case 0:
                        pb->unk10 = limit % (pb->path.unk4 - 1);
                        if (pb->unk10 != 0) {
                            pb->unk10 = pb->path.unk4 - pb->unk10 - 1;
                        }
                        break;
                    case 1:
                        tq = quot + 1;
                        if (tq) {
                            pb->unk14 = 0;
                            pb->unk10 = 0;
                            pb->unkC = 0.0f;
                        }
                        break;
                    }
                }
            }
            break;
        }
    }
}
