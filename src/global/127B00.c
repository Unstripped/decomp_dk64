#include "common.h"
#include "actor.h"

void *func_80610FE8(s32);
typedef struct PathEntry {
    u8 *unk0;
    s16 unk4;
} PathEntry;


typedef struct PathPlayback {
    s32 unk0;
    u8 *unk4;
    s16 unk8;
    u8 padA[2];
    f32 unkC;
    s16 unk10;
    u8 pad12[2];
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 pad17;
    s32 unk18;
    s32 unk1C;
    u8 unk20;
    u8 unk21;
} PathPlayback;

extern PathEntry *D_807FDB90[];


void assetFreeBuffer(s32, s32, s32);
s32 assetLoad(s32, s32, s32, s32);
void pathTableLoad(s16 *);

void pathFreeAsset(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = assetLoad(0xF, arg0, 1, 1);
    sp1C = temp_v0;
    pathTableLoad((s16 *) temp_v0);
    assetFreeBuffer(sp1C, 0x47, 0x27);
}

typedef struct PathPoint {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} PathPoint;

extern PathPlayback *D_807FDBF8[];

void pathTableLoad(s16 *arg0) {
    s16 *var_s2;
    PathPoint *var_a0;
    s16 temp_s5;
    s16 temp_s7;
    s16 var_s0;
    s16 var_s4;

    for (var_s4 = 0; var_s4 < 0x1A; var_s4++) {
        D_807FDB90[var_s4] = NULL;
    }
    temp_s7 = *arg0;
    var_s2 = arg0 + 1;
    for (var_s4 = 0; var_s4 < temp_s7; var_s4++) {
        temp_s5 = *var_s2++;
        D_807FDB90[temp_s5] = func_80610FE8(8);
        D_807FDB90[temp_s5]->unk4 = *var_s2++;
        var_s2++;
        D_807FDB90[temp_s5]->unk0 = func_80610FE8((D_807FDB90[temp_s5]->unk4 + 1) * sizeof(PathPoint));
        var_s0 = 0;
        var_a0 = (PathPoint *)var_s2;
        while (var_s0 < D_807FDB90[temp_s5]->unk4) {
            ((PathPoint *)D_807FDB90[temp_s5]->unk0)[var_s0] = *var_a0;
            var_s0 += 1;
            var_a0 += 1;
        }
        var_s2 = (s16 *)var_a0;
    }
    for (var_s4 = 0; var_s4 < 0x20; var_s4++) {
        D_807FDBF8[var_s4] = NULL;
    }
}

s32 pathExists(u8 arg0) {
    if (D_807FDB90[arg0] != NULL) {
        return 1;
    }
    return 0;
}

void *memcpy(void *, const void *, unsigned int);

s32 pathPlaybackStart(s32 arg0, s32 arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6) {
    PathEntry *path;
    s32 i;
    s32 found;
    PathPlayback *pad; // FAKE: unused local steers stack layout (spill and sp54 slots)
    PathPoint sp54;
    s32 extra;
    s32 j;
    s32 dstOff;
    s32 srcOff;

    i = 0;
    found = 0;
    extra = 0;
    if (D_807FDB90[arg1] == NULL) {
        return -1;
    }
    while (i < 0x20 && !found) {
        if (D_807FDBF8[i] == NULL) {
            found = 1;
        } else {
            i++;
        }
    }
    if (!found) {
        return -1;
    }
    if (D_807FDB90[arg1]->unk4 == 1 && !arg2) {
        return -1;
    }
    D_807FDBF8[i] = func_80610FE8(0x2C);
    path = (PathEntry *)&D_807FDBF8[i]->unk4;
    path->unk4 = D_807FDB90[arg1]->unk4;
    path->unk0 = func_80610FE8(path->unk4 * 10 + 10);
    if (arg2 != 0) {
        path->unk4++;
        ((u8 *)&sp54)[8] = arg6;
        sp54.unk2 = arg3;
        sp54.unk4 = arg4;
        sp54.unk6 = arg5;
        memcpy(path->unk0, &sp54, 10);
        extra = 1;
    }
    for (j = 0, dstOff = extra * 10, srcOff = 0; j < D_807FDB90[arg1]->unk4; j++) {
        memcpy(path->unk0 + dstOff, D_807FDB90[arg1]->unk0 + srcOff, 10);
        srcOff += 10;
        dstOff += 10;
    }
    D_807FDBF8[i]->unk0 = arg0;
    D_807FDBF8[i]->unkC = 0.0f;
    *(s32 *)((u8 *)D_807FDBF8[i] + 0x1C) = 0;
    *(s32 *)((u8 *)D_807FDBF8[i] + 0x10) = 0;
    D_807FDBF8[i]->unk16 = 0;
    D_807FDBF8[i]->unk15 = 0;
    D_807FDBF8[i]->unk14 = 0;
    D_807FDBF8[i]->unk18 = 1;
    D_807FDBF8[i]->unk21 = 0;
    D_807FDBF8[i]->unk20 = 1;
    return i;
}


void func_80723284(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk20 = arg1;
        }
    }
}

void func_807232B8(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk16 = arg1;
        }
    }
}

void func_807232EC(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk15 = arg1;
        }
    }
}

void func_80723320(s32 arg0, s32 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk18 = arg1;
        }
    }
}

void func_8072334C(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk21 = arg1;
        }
    }
}

void func_80723380(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk14 = arg1;
        }
    }
}

void pathPlaybackFree(s32);

void pathPlaybackStopForActor(s32 arg0) {
    PathPlayback **var_s1;
    PathPlayback *temp_v0;
    s32 var_s0;

    var_s1 = D_807FDBF8;
    var_s0 = 0;
    do {
        temp_v0 = *var_s1;
        if ((temp_v0 != NULL) && (arg0 == temp_v0->unk0)) {
            pathPlaybackFree(var_s0);
        }
        var_s0 += 1;
        var_s1 += 1;
    } while (var_s0 != 0x20);
}

void heapFree(void *);

void pathPlaybackFree(s32 arg0) {
    if ((arg0 == -1) || (D_807FDBF8[arg0] != NULL)) {
        heapFree(D_807FDBF8[arg0]);
        D_807FDBF8[arg0] = NULL;
    }
}

#ifdef NON_MATCHING
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
        step = (f32)(u32)pb->unk20 *
               (f32)((f64)(fa +
                           (f32)(path->unk0[next * 10 + 8] - path->unk0[pb->unk10 * 10 + 8]) * prog) /
                     300.0);
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723484.s")
#endif

typedef struct SplinePathPoint {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} SplinePathPoint;

#define SPLINE_PATH_PT(e) ((SplinePathPoint *)(e)->unk0)

typedef struct SplinePlayback {
    s32 unk0;
    PathEntry path;
    f32 unkC;
    s32 unk10;
    u8 pad14[2];
    u8 unk16;
} SplinePlayback;

f32 splineEvalCubic(f64, f32, f32, f32, f32);
void splineSetBasisTension(f32);
f32 pathSplineDistance(s32, f32, f32, f32, s32, f32);

void pathPlaybackGetPosition(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 ids[4];
    SplinePlayback *p;
    PathEntry *e;

    if (arg0 != -1) {
        if (D_807FDBF8[arg0] != NULL) {
            splineSetBasisTension(0.5f);
            p = (SplinePlayback *)D_807FDBF8[arg0];
            e = &p->path;
            if (p->unk16 == 0) {
                if (p->unk10 - 1 < 0) {
                    ids[0] = 0;
                } else {
                    ids[0] = p->unk10 - 1;
                }
                if (p->unk10 + 1 >= e->unk4) {
                    ids[2] = e->unk4 - 1;
                } else {
                    ids[2] = p->unk10 + 1;
                }
                if (p->unk10 + 2 >= e->unk4) {
                    ids[3] = e->unk4 - 1;
                } else {
                    ids[3] = p->unk10 + 2;
                }
            } else {
                if (p->unk10 - 1 < 0) {
                    ids[0] = e->unk4 - 1;
                } else {
                    ids[0] = p->unk10 - 1;
                }
                if (p->unk10 + 1 >= e->unk4) {
                    ids[2] = (p->unk10 + 1) % e->unk4;
                } else {
                    ids[2] = p->unk10 + 1;
                }
                if (p->unk10 + 2 >= e->unk4) {
                    ids[3] = (p->unk10 + 2) % e->unk4;
                } else {
                    ids[3] = p->unk10 + 2;
                }
            }
            ids[1] = p->unk10;
            *arg1 = splineEvalCubic(p->unkC, SPLINE_PATH_PT(e)[ids[0]].unk2, SPLINE_PATH_PT(e)[ids[1]].unk2, SPLINE_PATH_PT(e)[ids[2]].unk2, SPLINE_PATH_PT(e)[ids[3]].unk2);
            *arg2 = splineEvalCubic(p->unkC, SPLINE_PATH_PT(e)[ids[0]].unk4, SPLINE_PATH_PT(e)[ids[1]].unk4, SPLINE_PATH_PT(e)[ids[2]].unk4, SPLINE_PATH_PT(e)[ids[3]].unk4);
            *arg3 = splineEvalCubic(p->unkC, SPLINE_PATH_PT(e)[ids[0]].unk6, SPLINE_PATH_PT(e)[ids[1]].unk6, SPLINE_PATH_PT(e)[ids[2]].unk6, SPLINE_PATH_PT(e)[ids[3]].unk6);
        }
    }
}

u8 func_80723C98(s32 arg0) {
    PathPlayback *temp_v1;

    if ((arg0 == -1) || ((temp_v1 = D_807FDBF8[arg0]) == NULL)) {
        return 0;
    }
    return temp_v1->unk21;
}

void pathSplineSample(s32 arg0, s32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    u8 ids[4];
    PathEntry *e;

    splineSetBasisTension(0.5f);
    e = D_807FDB90[arg0];
    if (arg1 >= e->unk4) {
        arg1 = e->unk4 - 1;
    }
    if (arg1 - 1 < 0) {
        ids[0] = 0;
    } else {
        ids[0] = arg1 - 1;
    }
    ids[1] = arg1;
    if (arg1 + 1 >= e->unk4) {
        ids[2] = e->unk4 - 1;
    } else {
        ids[2] = arg1 + 1;
    }
    if (arg1 + 2 >= e->unk4) {
        ids[3] = e->unk4 - 1;
    } else {
        ids[3] = arg1 + 2;
    }
    *arg3 = splineEvalCubic(arg2, SPLINE_PATH_PT(e)[ids[0]].unk2, SPLINE_PATH_PT(e)[ids[1]].unk2, SPLINE_PATH_PT(e)[ids[2]].unk2, SPLINE_PATH_PT(e)[ids[3]].unk2);
    *arg4 = splineEvalCubic(arg2, SPLINE_PATH_PT(e)[ids[0]].unk4, SPLINE_PATH_PT(e)[ids[1]].unk4, SPLINE_PATH_PT(e)[ids[2]].unk4, SPLINE_PATH_PT(e)[ids[3]].unk4);
    *arg5 = splineEvalCubic(arg2, SPLINE_PATH_PT(e)[ids[0]].unk6, SPLINE_PATH_PT(e)[ids[1]].unk6, SPLINE_PATH_PT(e)[ids[2]].unk6, SPLINE_PATH_PT(e)[ids[3]].unk6);
}

void pathFindClosestPoint(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 *arg4, f32 *arg5) {
    f32 best;
    f32 frac;
    f32 d;
    s32 bestIdx;
    s32 i;
    s32 end;

    best = 999999.0f;
    frac = 0.0f;
    splineSetBasisTension(0.5f);
    for (i = 0; i < D_807FDB90[arg0]->unk4; i++) {
        d = pathSplineDistance(arg0, arg1, arg2, arg3, i, 0.0f);
        if (d < best) {
            bestIdx = i;
            *arg4 = i;
            *arg5 = 0.0f;
            best = d;
        }
    }
    end = bestIdx;
    if (bestIdx - 1 < 0) {
        i = 0;
    } else {
        i = bestIdx - 1;
    }
    end++;
    goto fake_label; fake_label: ; // FAKE: block boundary before refinement loop (register/scheduling steer)
    while (i <= end) {
        d = pathSplineDistance(arg0, arg1, arg2, arg3, i, frac);
        if (d < best) {
            *arg4 = i;
            *arg5 = frac;
            best = d;
        }
        frac = frac + 0.005;
        if (frac >= 1.0) {
            frac = frac - 1.0;
            i++;
        }
    }
}

void pathRefineClosestPoint(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 *arg4, f32 *arg5) {
    f32 best;
    f32 frac;
    f32 d;
    s32 idx;
    s32 i;

    best = 999999.0f;
    idx = *arg4;
    frac = *arg5 - 0.5;
    i = 20;
    if (frac < 0.0) {
        if (idx > 0) {
            idx -= 1;
            frac += 1.0f;
        } else {
            frac = 0.0f;
        }
    }
    while (i--) {
        d = pathSplineDistance(arg0, arg1, arg2, arg3, idx, frac);
        if (d < best) {
            *arg4 = idx;
            *arg5 = frac;
            best = d;
        }
        frac = frac + 0.05;
        if (frac >= 1.0f && idx < D_807FDB90[arg0]->unk4) {
            idx += 1;
            frac -= 1.0f;
        } else if (frac >= 1.0f) {
            frac = 1.0f;
        }
    }
}

f32 pathSplineDistance(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5) {
    u8 ids[4];
    PathEntry *e;
    f32 sx;
    f32 sy;
    f32 sz;

    e = D_807FDB90[arg0];
    if (arg4 >= e->unk4) {
        arg4 = e->unk4 - 1;
    }
    if (arg4 - 1 < 0) {
        ids[0] = 0;
    } else {
        ids[0] = arg4 - 1;
    }
    ids[1] = arg4;
    if (arg4 + 1 >= e->unk4) {
        ids[2] = e->unk4 - 1;
    } else {
        ids[2] = arg4 + 1;
    }
    if (arg4 + 2 >= e->unk4) {
        ids[3] = e->unk4 - 1;
    } else {
        ids[3] = arg4 + 2;
    }
    sx = splineEvalCubic(arg5, SPLINE_PATH_PT(e)[ids[0]].unk2, SPLINE_PATH_PT(e)[ids[1]].unk2, SPLINE_PATH_PT(e)[ids[2]].unk2, SPLINE_PATH_PT(e)[ids[3]].unk2);
    sy = splineEvalCubic(arg5, SPLINE_PATH_PT(e)[ids[0]].unk0, SPLINE_PATH_PT(e)[ids[1]].unk0, SPLINE_PATH_PT(e)[ids[2]].unk0, SPLINE_PATH_PT(e)[ids[3]].unk0);
    sz = splineEvalCubic(arg5, SPLINE_PATH_PT(e)[ids[0]].unk6, SPLINE_PATH_PT(e)[ids[1]].unk6, SPLINE_PATH_PT(e)[ids[2]].unk6, SPLINE_PATH_PT(e)[ids[3]].unk6);
    return sqrtf((arg1 - sx) * (arg1 - sx) + (arg2 - sy) * (arg2 - sy) + (arg3 - sz) * (arg3 - sz));
}

s16 pathEntryCount(s32 arg0) {
    return D_807FDB90[arg0]->unk4;
}
