// func_80723484 (src/global/127B00.c): R2Fp2 stage 5, whole-file diff 54->14 lines, text size equal (280): FP all match (ratio local f0 / step f12 / pb->unkC read directly as f2 load temp, expr 'mul + fa' order so fa is a ring temp), ints match except ONE ring slot: target 'move t5,t4' (dead copy of sum in case 1 of the negative branch, ring temp) vs ours 'move a3,t4' (total web) -> ring shifted by one after it (lbu t6 vs t5, mfhi t8 vs t7). KEY: case 0 w/o 'total' local (pb->unk1C += quot; if (pb->unk1C >= ...)) gives the target's dead 'move t8,t7' ring copy; same in case 1 flips pb v0->v1 (pb stops being a constrained candidate, 295 lines). 4 FAKEs: path==0, limit (after limit=-pb->unk10, fixes all 'li t1,1' ring), pb&&pb after the %, tq&&tq. Target tq is a v1 web computed BEFORE the switch(unk15).
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
    f32 step;
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
        if (path == 0) {}  // FAKE: ring/web steer
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
        ratio = (f32)((f64)((f32)(path->unk0[next * 10 + 8] - path->unk0[pb->unk10 * 10 + 8]) * pb->unkC + (f32)(u32)path->unk0[pb->unk10 * 10 + 8]) / 300.0);
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
                pb->unk1C += quot;
                if (pb->unk1C >= pb->unk18 && pb->unk18 != -1) {
                    pb->unk10 = pb->path.unk4 - 2;
                    pb->unk21 = 0;
                    pb->unkC = 1.0f;
                    if (pb->unk15 == 1) {
                        pb->unk14 = 1;
                    }
                } else {
                    switch (pb->unk15) {
                    case 0:
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
                if (limit) {}  // FAKE: ring/web steer
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
                        if (pb && pb) {}  // FAKE: ring/web steer
                        if (pb->unk10 != 0) {
                            pb->unk10 = pb->path.unk4 - pb->unk10 - 1;
                        }
                        break;
                    case 1:
                        tq = quot + 1;
                        if (tq && tq) {}  // FAKE: ring/web steer
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
