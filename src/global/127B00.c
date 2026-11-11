#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "proto/global/127B00.h"
#include "proto/global/15050.h"
#include "proto/global/2C700.h"
#include "proto/global/6AD90.h"

typedef struct PathPoint {
    s16 unk0;
    s16 x;
    s16 y;
    s16 z;
    u8 speed;
    u8 unk9;
} PathPoint;

typedef struct PathEntry {
    PathPoint *points;
    s16 count;
} PathEntry;


typedef struct PathPlayback {
    Actor *owner;
    PathEntry path;
    f32 t;
    s32 pointIndex;
    u8 direction;
    u8 loopMode;
    u8 isLooping;
    u8 pad17;
    s32 loopLimit;
    s32 loopCount;
    u8 stepSpeed;
    u8 active;
    u8 pad22[0xA];
} PathPlayback;

extern PathEntry *gPathTable[];



void pathFreeAsset(s32 assetId) {
    void *asset;

    asset = assetLoad(0xF, assetId, 1, 1);
    pathTableLoad(asset);
    assetFreeBuffer(asset, 0x47, 0x27);
}

extern PathPlayback *gPathPlaybacks[];

void pathTableLoad(s16 *src) {
    s16 *srcPtr;
    PathPoint *point;
    s16 pathId;
    s16 pathCount;
    s16 j;
    s16 i;

    for (i = 0; i < 0x1A; i++) {
        gPathTable[i] = NULL;
    }
    pathCount = *src;
    srcPtr = src + 1;
    for (i = 0; i < pathCount; i++) {
        pathId = *srcPtr++;
        gPathTable[pathId] = heapAlloc(sizeof(PathEntry));
        gPathTable[pathId]->count = *srcPtr++;
        srcPtr++;
        gPathTable[pathId]->points = heapAlloc((gPathTable[pathId]->count + 1) * sizeof(PathPoint));
        point = (PathPoint *)srcPtr;
        for (j = 0; j < gPathTable[pathId]->count; j++) {
            gPathTable[pathId]->points[j] = *point++;
        }
        srcPtr = (s16 *)point;
    }
    for (i = 0; i < 0x20; i++) {
        gPathPlaybacks[i] = NULL;
    }
}

s32 pathExists(u8 pathId) {
    if (gPathTable[pathId] != NULL) {
        return 1;
    }
    return 0;
}


s32 pathPlaybackStart(Actor *owner, s32 pathId, u8 prependStartPoint, f32 x, f32 y, f32 z, u8 pointFlag) {
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
    if (gPathTable[pathId] == NULL) {
        return -1;
    }
    while (i < 0x20 && !found) {
        if (gPathPlaybacks[i] == NULL) {
            found = 1;
        } else {
            i++;
        }
    }
    if (!found) {
        return -1;
    }
    if (gPathTable[pathId]->count == 1 && !prependStartPoint) {
        return -1;
    }
    gPathPlaybacks[i] = heapAlloc(sizeof(PathPlayback));
    path = &gPathPlaybacks[i]->path;
    path->count = gPathTable[pathId]->count;
    path->points = heapAlloc(path->count * sizeof(PathPoint) + sizeof(PathPoint));
    if (prependStartPoint != 0) {
        path->count++;
        startPoint.speed = pointFlag;
        startPoint.x = x;
        startPoint.y = y;
        startPoint.z = z;
        memcpy(path->points, &startPoint, sizeof(PathPoint));
        extra = 1;
    }
    for (j = 0, dstOff = extra * sizeof(PathPoint), srcOff = 0; j < gPathTable[pathId]->count; j++) {
        memcpy((u8 *)path->points + dstOff, (u8 *)gPathTable[pathId]->points + srcOff, sizeof(PathPoint));
        srcOff += sizeof(PathPoint);
        dstOff += sizeof(PathPoint);
    }
    gPathPlaybacks[i]->owner = owner;
    gPathPlaybacks[i]->t = 0.0f;
    gPathPlaybacks[i]->loopCount = 0;
    gPathPlaybacks[i]->pointIndex = 0;
    gPathPlaybacks[i]->isLooping = 0;
    gPathPlaybacks[i]->loopMode = 0;
    gPathPlaybacks[i]->direction = 0;
    gPathPlaybacks[i]->loopLimit = 1;
    gPathPlaybacks[i]->active = 0;
    gPathPlaybacks[i]->stepSpeed = 1;
    return i;
}


void pathPlaybackSetSpeed(s32 slot, u8 stepSpeed) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = gPathPlaybacks[slot];
        if (playback != NULL) {
            playback->stepSpeed = stepSpeed;
        }
    }
}

void pathPlaybackSetLooping(s32 slot, u8 isLooping) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = gPathPlaybacks[slot];
        if (playback != NULL) {
            playback->isLooping = isLooping;
        }
    }
}

void pathPlaybackSetLoopMode(s32 slot, u8 loopMode) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = gPathPlaybacks[slot];
        if (playback != NULL) {
            playback->loopMode = loopMode;
        }
    }
}

void pathPlaybackSetLoopLimit(s32 slot, s32 loopLimit) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = gPathPlaybacks[slot];
        if (playback != NULL) {
            playback->loopLimit = loopLimit;
        }
    }
}

void pathPlaybackSetActive(s32 slot, u8 active) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = gPathPlaybacks[slot];
        if (playback != NULL) {
            playback->active = active;
        }
    }
}

void pathPlaybackSetDirection(s32 slot, u8 direction) {
    PathPlayback *playback;

    if (slot != -1) {
        playback = gPathPlaybacks[slot];
        if (playback != NULL) {
            playback->direction = direction;
        }
    }
}


void pathPlaybackStopForActor(Actor *actor) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (gPathPlaybacks[i] != NULL && actor == gPathPlaybacks[i]->owner) {
            pathPlaybackFree(i);
        }
    }
}


void pathPlaybackFree(s32 slot) {
    if ((slot == -1) || (gPathPlaybacks[slot] != NULL)) {
        heapFree(gPathPlaybacks[slot]);
        gPathPlaybacks[slot] = NULL;
    }
}

void pathPlaybackAdvance(s32 slot) {
    PathPlayback *pb;
    PathEntry *path;
    f32 step;
    f32 ratio;
    s32 next;
    s32 tmp;
    s32 limit;
    s32 quot;
    u32 tq;
    s32 whole;

    if (slot != -1 && gPathPlaybacks[slot] != NULL && gPathPlaybacks[slot]->active != 0) {
        pb = gPathPlaybacks[slot];
        path = &pb->path;
        if (path == 0) {}  // FAKE: ring/web steer
        if (pb->isLooping == 0) {
            next = pb->pointIndex + 1;
        } else {
            tmp = pb->pointIndex + 1;
            if (tmp >= path->count) {
                next = tmp % (path->count - 1);
            } else {
                next = tmp;
            }
        }
        ratio = ((path->points[next].speed - path->points[pb->pointIndex].speed) * pb->t + path->points[pb->pointIndex].speed) / 300.0;
        step = pb->stepSpeed * ratio;
        switch (pb->direction) {
        case 0:
            pb->t += step;
            pb->pointIndex += (s32)pb->t;
            pb->t -= (s32)pb->t;
            if (pb->isLooping == 0) {
                limit = pb->path.count - 1;
            } else {
                limit = pb->path.count;
            }
            if (pb->pointIndex >= limit) {
                limit = pb->path.count - 1;
                quot = pb->pointIndex / limit;
                pb->loopCount += quot;
                if (pb->loopCount >= pb->loopLimit && pb->loopLimit != -1) {
                    pb->pointIndex = pb->path.count - 2;
                    pb->active = 0;
                    pb->t = 1.0f;
                    if (pb->loopMode == 1) {
                        pb->direction = 1;
                    }
                } else {
                    switch (pb->loopMode) {
                    case 0:
                        if (pb->isLooping == 0) {
                            pb->pointIndex = pb->pointIndex % limit;
                        } else {
                            pb->pointIndex = pb->pointIndex % pb->path.count;
                        }
                        break;
                    case 1:
                        if (quot != 0) {
                            pb->direction = 1;
                            pb->pointIndex = pb->path.count - 2;
                            pb->t = 1.0f;
                        }
                        break;
                    }
                }
            }
            break;
        case 1:
            pb->t -= step;
            if (pb->t < 0.0) {
                whole = (s32)pb->t - 1;
                pb->pointIndex += whole;
                pb->t -= whole;
            }
            if (pb->pointIndex < 0) {
                limit = -pb->pointIndex;
                quot = limit / pb->path.count;
                pb->loopCount += quot + 1;
                if (pb->loopCount >= pb->loopLimit && pb->loopLimit != -1) {
                    pb->pointIndex = 0;
                    pb->active = 0;
                    pb->t = 0.0f;
                    if (pb->loopMode == 1) {
                        pb->direction = 0;
                    }
                } else {
                    switch (pb->loopMode) {
                    case 0:
                        pb->pointIndex = limit % (pb->path.count - 1);
                        if (pb && pb) {}  // FAKE: ring/web steer
                        if (pb->pointIndex != 0) {
                            pb->pointIndex = pb->path.count - pb->pointIndex - 1;
                        }
                        break;
                    case 1:
                        tq = quot + 1;
                        if (tq && tq) {}  // FAKE: ring/web steer
                        if (tq) {
                            pb->direction = 0;
                            pb->pointIndex = 0;
                            pb->t = 0.0f;
                        }
                        break;
                    }
                }
            }
            break;
        }
    }
}


void pathPlaybackGetPosition(s32 slot, f32 *outX, f32 *outY, f32 *outZ) {
    u8 ids[4];
    PathPlayback *p;
    PathEntry *e;

    if (slot != -1) {
        if (gPathPlaybacks[slot] != NULL) {
            splineSetBasisTension(0.5f);
            p = gPathPlaybacks[slot];
            e = &p->path;
            if (p->isLooping == 0) {
                if (p->pointIndex - 1 < 0) {
                    ids[0] = 0;
                } else {
                    ids[0] = p->pointIndex - 1;
                }
                if (p->pointIndex + 1 >= e->count) {
                    ids[2] = e->count - 1;
                } else {
                    ids[2] = p->pointIndex + 1;
                }
                if (p->pointIndex + 2 >= e->count) {
                    ids[3] = e->count - 1;
                } else {
                    ids[3] = p->pointIndex + 2;
                }
            } else {
                if (p->pointIndex - 1 < 0) {
                    ids[0] = e->count - 1;
                } else {
                    ids[0] = p->pointIndex - 1;
                }
                if (p->pointIndex + 1 >= e->count) {
                    ids[2] = (p->pointIndex + 1) % e->count;
                } else {
                    ids[2] = p->pointIndex + 1;
                }
                if (p->pointIndex + 2 >= e->count) {
                    ids[3] = (p->pointIndex + 2) % e->count;
                } else {
                    ids[3] = p->pointIndex + 2;
                }
            }
            ids[1] = p->pointIndex;
            *outX = splineEvalCubic(p->t, e->points[ids[0]].x, e->points[ids[1]].x, e->points[ids[2]].x, e->points[ids[3]].x);
            *outY = splineEvalCubic(p->t, e->points[ids[0]].y, e->points[ids[1]].y, e->points[ids[2]].y, e->points[ids[3]].y);
            *outZ = splineEvalCubic(p->t, e->points[ids[0]].z, e->points[ids[1]].z, e->points[ids[2]].z, e->points[ids[3]].z);
        }
    }
}

u8 pathPlaybackIsActive(s32 slot) {
    PathPlayback *playback;

    if ((slot == -1) || ((playback = gPathPlaybacks[slot]) == NULL)) {
        return 0;
    }
    return playback->active;
}

void pathSplineSample(s32 pathId, s32 pointIndex, f32 t, f32 *outX, f32 *outY, f32 *outZ) {
    u8 ids[4];
    PathEntry *e;

    splineSetBasisTension(0.5f);
    e = gPathTable[pathId];
    if (pointIndex >= e->count) {
        pointIndex = e->count - 1;
    }
    if (pointIndex - 1 < 0) {
        ids[0] = 0;
    } else {
        ids[0] = pointIndex - 1;
    }
    ids[1] = pointIndex;
    if (pointIndex + 1 >= e->count) {
        ids[2] = e->count - 1;
    } else {
        ids[2] = pointIndex + 1;
    }
    if (pointIndex + 2 >= e->count) {
        ids[3] = e->count - 1;
    } else {
        ids[3] = pointIndex + 2;
    }
    *outX = splineEvalCubic(t, e->points[ids[0]].x, e->points[ids[1]].x, e->points[ids[2]].x, e->points[ids[3]].x);
    *outY = splineEvalCubic(t, e->points[ids[0]].y, e->points[ids[1]].y, e->points[ids[2]].y, e->points[ids[3]].y);
    *outZ = splineEvalCubic(t, e->points[ids[0]].z, e->points[ids[1]].z, e->points[ids[2]].z, e->points[ids[3]].z);
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
    for (i = 0; i < gPathTable[pathId]->count; i++) {
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
        if (frac >= 1.0f && idx < gPathTable[pathId]->count) {
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

    e = gPathTable[pathId];
    if (pointIndex >= e->count) {
        pointIndex = e->count - 1;
    }
    if (pointIndex - 1 < 0) {
        ids[0] = 0;
    } else {
        ids[0] = pointIndex - 1;
    }
    ids[1] = pointIndex;
    if (pointIndex + 1 >= e->count) {
        ids[2] = e->count - 1;
    } else {
        ids[2] = pointIndex + 1;
    }
    if (pointIndex + 2 >= e->count) {
        ids[3] = e->count - 1;
    } else {
        ids[3] = pointIndex + 2;
    }
    sx = splineEvalCubic(t, e->points[ids[0]].x, e->points[ids[1]].x, e->points[ids[2]].x, e->points[ids[3]].x);
    sy = splineEvalCubic(t, e->points[ids[0]].unk0, e->points[ids[1]].unk0, e->points[ids[2]].unk0, e->points[ids[3]].unk0);
    sz = splineEvalCubic(t, e->points[ids[0]].z, e->points[ids[1]].z, e->points[ids[2]].z, e->points[ids[3]].z);
    return sqrtf((x - sx) * (x - sx) + (y - sy) * (y - sy) + (z - sz) * (z - sz));
}

s16 pathEntryCount(s32 pathId) {
    return gPathTable[pathId]->count;
}
