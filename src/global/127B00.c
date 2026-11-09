#include "common.h"
#include "actor.h"

void *heapAlloc(s32);
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
void * assetLoad(s32, u32, u8, u8);
void pathTableLoad(s16 *);

void pathFreeAsset(s32 assetId) {
    s32 loadedAsset;
    s32 asset;

    asset = assetLoad(0xF, assetId, 1, 1);
    loadedAsset = asset;
    pathTableLoad((s16 *) asset);
    assetFreeBuffer(loadedAsset, 0x47, 0x27);
}

typedef struct PathPoint {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} PathPoint;

extern PathPlayback *D_807FDBF8[];

void pathTableLoad(s16 *src) {
    s16 *srcPtr;
    PathPoint *point;
    s16 pathId;
    s16 pathCount;
    s16 j;
    s16 i;

    for (i = 0; i < 0x1A; i++) {
        D_807FDB90[i] = NULL;
    }
    pathCount = *src;
    srcPtr = src + 1;
    for (i = 0; i < pathCount; i++) {
        pathId = *srcPtr++;
        D_807FDB90[pathId] = heapAlloc(8);
        D_807FDB90[pathId]->unk4 = *srcPtr++;
        srcPtr++;
        D_807FDB90[pathId]->unk0 = heapAlloc((D_807FDB90[pathId]->unk4 + 1) * sizeof(PathPoint));
        j = 0;
        point = (PathPoint *)srcPtr;
        while (j < D_807FDB90[pathId]->unk4) {
            ((PathPoint *)D_807FDB90[pathId]->unk0)[j] = *point;
            j += 1;
            point += 1;
        }
        srcPtr = (s16 *)point;
    }
    for (i = 0; i < 0x20; i++) {
        D_807FDBF8[i] = NULL;
    }
}

s32 pathExists(u8 pathId) {
    if (D_807FDB90[pathId] != NULL) {
        return 1;
    }
    return 0;
}

void *memcpy(void *, const void *, unsigned int);

s32 pathPlaybackStart(s32 owner, s32 pathId, u8 prependStartPoint, f32 x, f32 y, f32 z, u8 pointFlag) {
    PathEntry *path;
    s32 i;
    s32 found;
    PathPlayback *pad;
    PathPoint startPoint;
    s32 extra;
    s32 j;
    s32 dstOff;
    s32 srcOff;

    i = 0;
    found = 0;
    extra = 0;
    if (D_807FDB90[pathId] == NULL) {
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
    if (D_807FDB90[pathId]->unk4 == 1 && !prependStartPoint) {
        return -1;
    }
    D_807FDBF8[i] = heapAlloc(0x2C);
    path = (PathEntry *)&D_807FDBF8[i]->unk4;
    path->unk4 = D_807FDB90[pathId]->unk4;
    path->unk0 = heapAlloc(path->unk4 * 10 + 10);
    if (prependStartPoint != 0) {
        path->unk4++;
        ((u8 *)&startPoint)[8] = pointFlag;
        startPoint.unk2 = x;
        startPoint.unk4 = y;
        startPoint.unk6 = z;
        memcpy(path->unk0, &startPoint, 10);
        extra = 1;
    }
    for (j = 0, dstOff = extra * 10, srcOff = 0; j < D_807FDB90[pathId]->unk4; j++) {
        memcpy(path->unk0 + dstOff, D_807FDB90[pathId]->unk0 + srcOff, 10);
        srcOff += 10;
        dstOff += 10;
    }
    D_807FDBF8[i]->unk0 = owner;
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


void pathPlaybackSetSpeed(s32 slot, u8 stepSpeed) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = D_807FDBF8[slot];
        if (playback != NULL) {
            playback->unk20 = stepSpeed;
        }
    }
}

void pathPlaybackSetLooping(s32 slot, u8 isLooping) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = D_807FDBF8[slot];
        if (playback != NULL) {
            playback->unk16 = isLooping;
        }
    }
}

void pathPlaybackSetLoopMode(s32 slot, u8 loopMode) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = D_807FDBF8[slot];
        if (playback != NULL) {
            playback->unk15 = loopMode;
        }
    }
}

void pathPlaybackSetLoopLimit(s32 slot, s32 loopLimit) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = D_807FDBF8[slot];
        if (playback != NULL) {
            playback->unk18 = loopLimit;
        }
    }
}

void pathPlaybackSetActive(s32 slot, u8 active) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = D_807FDBF8[slot];
        if (playback != NULL) {
            playback->unk21 = active;
        }
    }
}

void pathPlaybackSetDirection(s32 slot, u8 direction) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = D_807FDBF8[slot];
        if (playback != NULL) {
            playback->unk14 = direction;
        }
    }
}

void pathPlaybackFree(s32);

void pathPlaybackStopForActor(s32 actor) {
    PathPlayback **playbacks;
    PathPlayback *playback;
    s32 i;

    playbacks = D_807FDBF8;
    i = 0;
    do {
        playback = *playbacks;
        if ((playback != NULL) && (actor == playback->unk0)) {
            pathPlaybackFree(i);
        }
        i += 1;
        playbacks += 1;
    } while (i != 0x20);
}

void heapFree(void *);

void pathPlaybackFree(s32 slot) {
    if ((slot == -1) || (D_807FDBF8[slot] != NULL)) {
        heapFree(D_807FDBF8[slot]);
        D_807FDBF8[slot] = NULL;
    }
}

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

void pathPlaybackAdvance(s32 slot) {
    PathPlaybackView *pb;
    PathEntry *path;
    f32 step;
    f32 ratio;
    s32 next;
    s32 tmp;
    s32 limit;
    s32 quot;
    u32 tq;
    s32 whole;
    s32 pad;

    if (slot != -1 && D_807FDBF8[slot] != NULL && ((PathPlaybackView *)D_807FDBF8[slot])->unk21 != 0) {
        pb = (PathPlaybackView *)D_807FDBF8[slot];
        pad = pb->unk1C;  // FAKE: extra web (keeps pb a constrained uopt candidate)
        if (pad) {}  // FAKE: extra web (keeps pb a constrained uopt candidate)
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
                quot = limit / pb->path.unk4;
                pb->unk1C += quot + 1;
                if (pb->unk1C >= pb->unk18 && pb->unk18 != -1) {
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

void pathPlaybackGetPosition(s32 slot, f32 *outX, f32 *outY, f32 *outZ) {
    u8 ids[4];
    SplinePlayback *p;
    PathEntry *e;

    if (slot != -1) {
        if (D_807FDBF8[slot] != NULL) {
            splineSetBasisTension(0.5f);
            p = (SplinePlayback *)D_807FDBF8[slot];
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
            *outX = splineEvalCubic(p->unkC, SPLINE_PATH_PT(e)[ids[0]].unk2, SPLINE_PATH_PT(e)[ids[1]].unk2, SPLINE_PATH_PT(e)[ids[2]].unk2, SPLINE_PATH_PT(e)[ids[3]].unk2);
            *outY = splineEvalCubic(p->unkC, SPLINE_PATH_PT(e)[ids[0]].unk4, SPLINE_PATH_PT(e)[ids[1]].unk4, SPLINE_PATH_PT(e)[ids[2]].unk4, SPLINE_PATH_PT(e)[ids[3]].unk4);
            *outZ = splineEvalCubic(p->unkC, SPLINE_PATH_PT(e)[ids[0]].unk6, SPLINE_PATH_PT(e)[ids[1]].unk6, SPLINE_PATH_PT(e)[ids[2]].unk6, SPLINE_PATH_PT(e)[ids[3]].unk6);
        }
    }
}

u8 pathPlaybackIsActive(s32 slot) {
    PathPlayback *playback;

    if ((slot == -1) || ((playback = D_807FDBF8[slot]) == NULL)) {
        return 0;
    }
    return playback->unk21;
}

void pathSplineSample(s32 pathId, s32 pointIndex, f32 t, f32 *outX, f32 *outY, f32 *outZ) {
    u8 ids[4];
    PathEntry *e;

    splineSetBasisTension(0.5f);
    e = D_807FDB90[pathId];
    if (pointIndex >= e->unk4) {
        pointIndex = e->unk4 - 1;
    }
    if (pointIndex - 1 < 0) {
        ids[0] = 0;
    } else {
        ids[0] = pointIndex - 1;
    }
    ids[1] = pointIndex;
    if (pointIndex + 1 >= e->unk4) {
        ids[2] = e->unk4 - 1;
    } else {
        ids[2] = pointIndex + 1;
    }
    if (pointIndex + 2 >= e->unk4) {
        ids[3] = e->unk4 - 1;
    } else {
        ids[3] = pointIndex + 2;
    }
    *outX = splineEvalCubic(t, SPLINE_PATH_PT(e)[ids[0]].unk2, SPLINE_PATH_PT(e)[ids[1]].unk2, SPLINE_PATH_PT(e)[ids[2]].unk2, SPLINE_PATH_PT(e)[ids[3]].unk2);
    *outY = splineEvalCubic(t, SPLINE_PATH_PT(e)[ids[0]].unk4, SPLINE_PATH_PT(e)[ids[1]].unk4, SPLINE_PATH_PT(e)[ids[2]].unk4, SPLINE_PATH_PT(e)[ids[3]].unk4);
    *outZ = splineEvalCubic(t, SPLINE_PATH_PT(e)[ids[0]].unk6, SPLINE_PATH_PT(e)[ids[1]].unk6, SPLINE_PATH_PT(e)[ids[2]].unk6, SPLINE_PATH_PT(e)[ids[3]].unk6);
}

void pathFindClosestPoint(s32 pathId, f32 x, f32 y, f32 z, s32 *outPointIndex, f32 *outT) {
    f32 best;
    f32 frac;
    f32 d;
    s32 bestIdx;
    s32 i;

    best = 999999.0f;
    frac = 0.0f;
    splineSetBasisTension(0.5f);
    for (i = 0; i < D_807FDB90[pathId]->unk4; i++) {
        d = pathSplineDistance(pathId, x, y, z, i, 0.0f);
        if (d < best) {
            bestIdx = i;
            *outPointIndex = i;
            *outT = 0.0f;
            best = d;
        }
    }
    if (bestIdx - 1 < 0) {
        i = 0;
    } else {
        i = bestIdx - 1;
    }
    while (i <= bestIdx + 1) {
        d = pathSplineDistance(pathId, x, y, z, i, frac);
        if (d < best) {
            *outPointIndex = i;
            *outT = frac;
            best = d;
        }
        frac = frac + 0.005;
        if (frac >= 1.0) {
            frac = frac - 1.0;
            i++;
        }
    }
}

void pathRefineClosestPoint(s32 pathId, f32 x, f32 y, f32 z, s32 *outPointIndex, f32 *outT) {
    f32 best;
    f32 frac;
    f32 d;
    s32 idx;
    s32 i;

    best = 999999.0f;
    idx = *outPointIndex;
    frac = *outT - 0.5;
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
        d = pathSplineDistance(pathId, x, y, z, idx, frac);
        if (d < best) {
            *outPointIndex = idx;
            *outT = frac;
            best = d;
        }
        frac = frac + 0.05;
        if (frac >= 1.0f && idx < D_807FDB90[pathId]->unk4) {
            idx += 1;
            frac -= 1.0f;
        } else if (frac >= 1.0f) {
            frac = 1.0f;
        }
    }
}

f32 pathSplineDistance(s32 pathId, f32 x, f32 y, f32 z, s32 pointIndex, f32 t) {
    u8 ids[4];
    PathEntry *e;
    f32 sx;
    f32 sy;
    f32 sz;

    e = D_807FDB90[pathId];
    if (pointIndex >= e->unk4) {
        pointIndex = e->unk4 - 1;
    }
    if (pointIndex - 1 < 0) {
        ids[0] = 0;
    } else {
        ids[0] = pointIndex - 1;
    }
    ids[1] = pointIndex;
    if (pointIndex + 1 >= e->unk4) {
        ids[2] = e->unk4 - 1;
    } else {
        ids[2] = pointIndex + 1;
    }
    if (pointIndex + 2 >= e->unk4) {
        ids[3] = e->unk4 - 1;
    } else {
        ids[3] = pointIndex + 2;
    }
    sx = splineEvalCubic(t, SPLINE_PATH_PT(e)[ids[0]].unk2, SPLINE_PATH_PT(e)[ids[1]].unk2, SPLINE_PATH_PT(e)[ids[2]].unk2, SPLINE_PATH_PT(e)[ids[3]].unk2);
    sy = splineEvalCubic(t, SPLINE_PATH_PT(e)[ids[0]].unk0, SPLINE_PATH_PT(e)[ids[1]].unk0, SPLINE_PATH_PT(e)[ids[2]].unk0, SPLINE_PATH_PT(e)[ids[3]].unk0);
    sz = splineEvalCubic(t, SPLINE_PATH_PT(e)[ids[0]].unk6, SPLINE_PATH_PT(e)[ids[1]].unk6, SPLINE_PATH_PT(e)[ids[2]].unk6, SPLINE_PATH_PT(e)[ids[3]].unk6);
    return sqrtf((x - sx) * (x - sx) + (y - sy) * (y - sy) + (z - sz) * (z - sz));
}

s16 pathEntryCount(s32 pathId) {
    return D_807FDB90[pathId]->unk4;
}
