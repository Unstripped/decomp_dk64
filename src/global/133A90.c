#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "model.h"
#include "sched.h"
#include "proto/global/117190.h"
#include "proto/global/133A90.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/2C700.h"
#include "proto/global/36880.h"
#include "proto/global/5E020.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"

extern Actor *gCurrentActor;
extern Actor *gActivePlayerActor;
extern PlayerStruct *gPlayerSlots;

typedef struct ProxPathSegment {
    /* 0x00 */ u8 startNode;
    /* 0x01 */ u8 endNode;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 length;
    /* 0x08 */ f32 param6;
    /* 0x0C */ f32 param7;
    /* 0x10 */ s16 minAngle;
    /* 0x12 */ s16 maxAngle;
    /* 0x14 */ s16 angleB;
    /* 0x16 */ s16 angleC;
    /* 0x18 */ u8 disabled;
    /* 0x19 */ u8 pad19[3];
} ProxPathSegment; // size = 0x1C

typedef struct ProxPath {
    /* 0x00 */ Actor *owner;
    /* 0x04 */ u8 slotType;
    /* 0x05 */ u8 pathIndex;
    /* 0x06 */ u8 pathType;
    /* 0x07 */ u8 segmentCount;
    /* 0x08 */ f32 minDist;
    /* 0x0C */ f32 maxDist;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ f32 moveSpeed;
    /* 0x18 */ u8 endBehavior;
    /* 0x19 */ u8 pad19[3];
    /* 0x1C */ f32 attachDist;
    /* 0x20 */ f32 detachDist;
    /* 0x24 */ f32 actionDist;
    /* 0x28 */ f32 paramC;
    /* 0x2C */ f32 paramD;
    /* 0x30 */ u8 paramE;
    /* 0x31 */ u8 enabled;
    /* 0x32 */ u8 pad32[2];
    /* 0x34 */ ProxPathSegment *segments;
    /* 0x38 */ struct ProxPath *next;
} ProxPath; // size = 0x3C

extern ProxPath *gProxPathList;

void proxPathListClear(void) {
    gProxPathList = NULL;
}

void proxPathSetEnabled(Actor *actor, u8 pathIndex, u8 enabled) {
    ProxPath *node;
    s32 found;

    node = gProxPathList;
    found = 0;
    while (node != NULL && !found) {
        if (node->owner == actor && node->pathIndex == pathIndex) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (found) {
        node->enabled = enabled;
    }
}

void proxPathSetEndBehavior(Actor *actor, u8 pathIndex, u8 endBehavior) {
    ProxPath *node;
    s32 found;

    node = gProxPathList;
    found = 0;
    while (node != NULL && !found) {
        if (node->owner == actor && node->pathIndex == pathIndex) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (found) {
        node->endBehavior = endBehavior;
    }
}

void proxPathAdd(Actor *actor, u8 slotType, u8 pathIndex, u8 pathType, u8 segmentCount, f32 minDist, f32 maxDist, f32 moveSpeed, f32 attachDist, f32 detachDist, f32 actionDist, u8 endBehavior, f32 paramC, f32 paramD, u8 paramE) {
    ProxPath **tail;
    ProxPath *node;

    tail = &gProxPathList;
    node = gProxPathList;
    while (node != NULL) {
        tail = &node->next;
        node = node->next;
    }
    node = *tail = heapAlloc(0x3C);
    node->owner = actor;
    node->slotType = slotType;
    node->pathIndex = pathIndex;
    node->pathType = pathType;
    node->segmentCount = segmentCount;
    node->minDist = minDist;
    node->maxDist = maxDist;
    node->moveSpeed = moveSpeed;
    node->attachDist = attachDist;
    node->detachDist = detachDist;
    node->actionDist = actionDist;
    node->endBehavior = endBehavior;
    node->paramC = paramC;
    node->paramD = paramD;
    node->paramE = paramE;
    node->enabled = 1;
    node->next = NULL;
    node->segments = heapAlloc(segmentCount * 0x1C);
}

void proxPathSetSegment(Actor *actor, u8 pathIndex, u8 segmentIndex, u8 startNode, u8 endNode, f32 length, f32 param6, f32 param7, u8 disabled, s16 minAngle, s16 maxAngle, s16 angleB, s16 angleC) {
    ProxPath *node;
    s32 found;

    node = gProxPathList;
    found = 0;
    while (node != NULL && !found) {
        if (node->owner == actor && node->pathIndex == pathIndex) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (found) {
        node->segments[segmentIndex].startNode = startNode;
        node->segments[segmentIndex].endNode = endNode;
        node->segments[segmentIndex].length = length;
        node->segments[segmentIndex].param6 = param6;
        node->segments[segmentIndex].param7 = param7;
        node->segments[segmentIndex].disabled = disabled;
        node->segments[segmentIndex].minAngle = minAngle;
        node->segments[segmentIndex].angleB = maxAngle;
        node->segments[segmentIndex].maxAngle = angleB;
        node->segments[segmentIndex].angleC = angleC;
    }
}

void proxPathRemoveActor(Actor *actor) {
    ProxPath **prev;
    ProxPath *node;
    ProxPath *next;

    prev = &gProxPathList;
    node = *prev;
    while (node != NULL) {
        if (node->owner == actor) {
            *prev = node->next;
            next = node->next;
            heapFree(node);
            node = next;
        } else {
            prev = &node->next;
            node = node->next;
        }
    }
}

extern u8 gPlayerCount;
extern u32 gGlobalOverlayFlags;

void proxPathUpdateAllPlayers(void) {
    u8 i;

    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].active != 0) {
            proxPathAttachNearestToPlayer(gPlayerSlots[i].actor, i, flagGet(0x183, 0) || (gGlobalOverlayFlags & 0x10000000) || gPlayerCount >= 2 || func_807142D8());
        }
    }
}

f32 sqrtf(f32);

void proxPathAttachNearestToPlayer(Actor *playerActor, u8 playerIndex, u8 allowBoss) {
    f32 dx;
    f32 x;
    f32 y;
    f32 z;
    ProxPath *node;
    ProxPath *best;
    f32 d;
    f32 bestDist;
    s32 isPlayer;
    u8 bestSub;
    u8 sub;
    u8 got;
    f32 out;
    f32 dy;
    PlayerState *state;
    f32 dz;
    f32 dist;

    state = playerActor->customState;
    isPlayer = playerActor->actorType == 6;
    node = gProxPathList;
    bestDist = 9999.0f;
    best = NULL;
    if (isPlayer) {
        isPlayer = gPlayerSlots[state->playerIndex].unk2C0 == 2;
    }
    while (node != NULL) {
        got = proxPathGetActorPosition(node->owner, node->slotType, &x, &y, &z);
        dx = playerActor->x - x;
        dy = playerActor->y - y;
        dz = playerActor->z - z;
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        if (dist < node->attachDist && node->enabled != 0) {
            if (node->pathType == 1 || (allowBoss != 0 && (node->owner->flags & 0x04000000))) {
                if (got == 0 || !(u8)isPlayer) {
                    if (proxPathFindNearestSegment(playerActor, node, &d, &sub)) {
                        if (d < bestDist) {
                            bestDist = d;
                            best = node;
                            bestSub = sub;
                        }
                    }
                }
            }
        }
        node = node->next;
    }
    if (best != NULL) {
        proxPathGetDistanceAt(best, bestSub, proxPathAttachToSegment(playerActor, state, best, bestSub), &out);
        state->pathDist = out;
        state->pathOwner = best->owner;
        state->pathIndex = best->pathIndex;
        state->pathYawMin = 0;
        state->pathYawMax = 0xFFF;
        playerActor->speedXZ = 0.0f;
        isPlayer = best->pathType;
        switch (isPlayer) {
        case 0:
            playerStateQueueCallback(0xC, NULL, playerIndex);
            break;
        case 1:
            playerStateQueueCallback(0xB, NULL, playerIndex);
            break;
        }
    }
}

extern ModelSlot *gModelSlots;

u8 proxPathGetActorPosition(Actor *actor, u8 mode, f32 *outX, f32 *outY, f32 *outZ) {
    s16 slot;
    u8 ret;

    ret = 0;
    switch (mode) {
    case 0:
        *outX = actor->x;
        *outY = actor->y;
        *outZ = actor->z;
        break;
    case 1:
    case 2:
        slot = hashTableLookup((s32)actor);
        *outX = gModelSlots[slot].unk0;
        *outY = gModelSlots[slot].unk4;
        *outZ = gModelSlots[slot].unk8;
        if (gModelSlots[slot].unk24->unk0 & 1) {
            ret = 1;
        }
        break;
    }
    return ret;
}

extern s16 gCurrentCharacterIndex;
extern s16 D_80753B74[];

s32 proxPathFindNearestSegment(Actor *actor, ProxPath *path, f32 *outDist, u8 *outSegment) {
    s32 i;
    f32 bz;
    f32 by;
    f32 bx;
    f32 az;
    f32 ay;
    f32 ax;
    s32 ang;
    u8 ret;
    u8 idA;
    u8 idB;
    f32 best;
    f32 r2;
    f32 ox;
    f32 oy;
    f32 oz;

    ret = 0;
    best = 999999.0f;
    if (actor->state == 0x5A || actor->state == 0x58) {
        r2 = path->actionDist * path->actionDist;
    } else {
        r2 = path->detachDist * path->detachDist;
    }
    if (path->pathType == 1) {
        r2 += D_80753B74[gCurrentCharacterIndex];
    }
    for (i = 0; i < path->segmentCount; i++) {
        if (path->segments[i].disabled == 0) {
            idA = path->segments[i].startNode;
            idB = path->segments[i].endNode;
            switch (path->slotType) {
            case 0:
                actorGetNodePos(path->owner, idA, &ax, &ay, &az);
                actorGetNodePos(path->owner, idB, &bx, &by, &bz);
                break;
            case 1:
            case 2:
                modelSlotGetNodePos((s32)path->owner, 1, idA, &ax, &ay, &az);
                modelSlotGetNodePos((s32)path->owner, 1, idB, &bx, &by, &bz);
                break;
            }
            camClosestPointOnSegment(actor->x, actor->y, actor->z, ax, ay, az, bx, by, bz, &ox, &oy, &oz);
            *outDist = (actor->x - ox) * (actor->x - ox) + (actor->y - oy) * (actor->y - oy) + (actor->z - oz) * (actor->z - oz);
            if (*outDist < r2 && *outDist < best) {
                ang = mathAtan2(ox - actor->x, oz - actor->z) * 4096.0 / 6.2831855f;
                if (mathAngleDistance(ang, actor->yaw) < 0x2BC) {
                    if (proxPathSegmentAngleCheck(path, i, actor->yaw)) {
                        best = *outDist;
                        ret = 1;
                        *outSegment = i;
                    }
                }
            }
        }
    }
    *outDist = sqrtf(best);
    return ret;
}


s32 proxPathSegmentAngleCheck(ProxPath *path, s32 segmentIndex, s16 angle) {
    s16 slot;
    s32 delta;

    if (path->slotType == 0) {
        return 1;
    }
    slot = hashTableLookup((s32)path->owner);
    if (!(gModelSlots[slot].unk84 == 0xC9 || gModelSlots[slot].unk84 == 0xCA || gModelSlots[slot].unk84 == 0x1CB || gModelSlots[slot].unk84 == 0x1F7 || gModelSlots[slot].unk84 == 0x1F8)) {
        return 1;
    }
    delta = gModelSlots[slot].unk14 * 4096.0f / 360.0f;
    if (mathAngleInArcWithMargin((s16)((path->segments[segmentIndex].minAngle + delta) & 0xFFF), (s16)((path->segments[segmentIndex].angleB + delta) & 0xFFF), angle, 0)) {
        return 1;
    }
    return 0;
}


f32 proxPathAttachToSegment(Actor *actor, PlayerState *state, ProxPath *path, u8 segmentIndex) {
    u8 idA;
    u8 idB;
    f32 bz;
    f32 by;
    f32 bx;
    f32 az;
    f32 ay;
    f32 ax;
    f32 ox;
    f32 oy;
    f32 oz;
    f32 t;
    f32 px;
    f32 py;
    f32 pz;

    idA = path->segments[segmentIndex].startNode;
    idB = path->segments[segmentIndex].endNode;
    switch (path->slotType) {
    case 0:
        actorGetNodePos(path->owner, idA, &ax, &ay, &az);
        actorGetNodePos(path->owner, idB, &bx, &by, &bz);
        break;
    case 1:
    case 2:
        modelSlotGetNodePos((s32)path->owner, 1, idA, &ax, &ay, &az);
        modelSlotGetNodePos((s32)path->owner, 1, idB, &bx, &by, &bz);
        break;
    }
    actorGetNodePos(actor, 1, &px, &py, &pz);
    camClosestPointOnSegment(px, py, pz, ax, ay, az, bx, by, bz, &ox, &oy, &oz);
    t = (oy - ay) / (by - ay);
    if (path->endBehavior == 2 || path->endBehavior == 3) {
        if (segmentIndex == 0) {
            if (t < 0.05) {
                t = 0.05f;
            }
        }
    }
    if (path->endBehavior == 1 || path->endBehavior == 3) {
        if (segmentIndex + 1 == path->segmentCount) {
            if (t > 0.95) {
                t = 0.95f;
            }
        }
    }
    state->unk13C = actor->x;
    state->unk140 = actor->y;
    state->unk144 = actor->z;
    state->unk148 = 0.0f;
    memcpy(state->unk15C, actor->modelMtx, 0x40);
    actor->yaw = mathAngleBetweenPointsRad(ox, oz, actor->x, actor->z) * 57.29577637f / 360.0 * 4095.0;
    return t;
}

void proxPathGetDistanceAt(ProxPath *path, u8 segmentIndex, f32 t, f32 *outDist) {
    s32 i;

    *outDist = 0.0f;
    for (i = 0; i < segmentIndex; i++) {
        *outDist = *outDist + path->segments[i].length;
    }
    *outDist = *outDist + path->segments[segmentIndex].length * t;
}

void proxPathFindDistanceSegment(ProxPath *path, f32 dist, u8 *outSegment, f32 *outT) {
    f32 rem;
    u8 i;

    i = 0;
    rem = dist;
    do {
        dist = rem;
        rem -= path->segments[i++].length;
    } while (0.0 < rem && i < path->segmentCount);
    i--;
    *outSegment = i;
    *outT = dist / path->segments[i].length;
}

extern PlayerState *gActivePlayerState;
extern u32 gFrameDelta;

void proxPathAdvance(f32 speedMultiplier) {
    f32 step;
    ProxPath *node;
    s32 found;

    node = gProxPathList;
    found = 0;
    while (node != NULL && !found) {
        if (node->owner == gActivePlayerState->pathOwner && node->pathIndex == gActivePlayerState->pathIndex) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (!found || node->enabled == 0) {
        gActivePlayerActor->contactFlags &= ~0x40;
        return;
    }
    gActivePlayerState->unk124 = node->paramC;
    gActivePlayerState->unk128 = node->paramD;
    gActivePlayerState->unk12C = node->paramE;
    step = gFrameDelta * 0.5;
    gActivePlayerState->pathDist += node->moveSpeed * step * speedMultiplier;
    gActivePlayerActor->contactFlags &= ~0x80;
    if (node->maxDist < gActivePlayerState->pathDist) {
        if (node->endBehavior == 1 || node->endBehavior == 3) {
            gActivePlayerActor->moveYaw = gActivePlayerActor->yaw;
            playerStateQueueCallback(0xD, NULL, gActivePlayerState->playerIndex);
        }
        gActivePlayerState->pathDist = node->maxDist;
    }
    if (gActivePlayerState->pathDist < node->minDist) {
        if (node->endBehavior == 2 || node->endBehavior == 3) {
            gActivePlayerActor->moveYaw = gActivePlayerActor->yaw;
            playerResumeLocomotion(gActivePlayerActor);
        }
        gActivePlayerState->pathDist = node->minDist;
    }
    if (node->maxDist <= gActivePlayerState->pathDist || gActivePlayerState->pathDist <= node->minDist) {
        gActivePlayerActor->contactFlags |= 0x80;
    }
}


void proxPathFollowerStep(Actor **pActor) {
    Actor *actor;
    PlayerState *state;
    u8 idx;
    f32 t;
    ProxPath *node;
    void *mtxFrom;
    void *mtxTo;
    s32 found;
    Mtx mtx;
    f32 transMtx[4][4];
    f32 rotMtx[4][4];
    s16 rot;
    u8 idA;
    u8 idB;
    s32 nodeId;
    f32 dx;
    f32 x;
    f32 y;
    f32 z;
    f32 dz;
    f32 dy;
    f32 dist;
    f32 ang;

    actor = *pActor;
    node = gProxPathList;
    state = actor->customState;
    found = 0;
    while (node != NULL && !found) {
        if (node->owner == state->pathOwner && node->pathIndex == state->pathIndex) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (!found || (actor->renderFlags & 0x2000)) {
        actor->contactFlags &= ~0x40;
        return;
    }
    proxPathFindDistanceSegment(node, state->pathDist, &idx, &t);
    idA = node->segments[idx].startNode;
    idB = node->segments[idx].endNode;
    switch (node->pathType) {
    case 0:
        proxPathGetSegmentMatrices(node->owner, node->slotType, idA, idB, &mtxFrom, &mtxTo);
        mtxLerpL(mtxFrom, mtxTo, 1.0 - t, &mtx);
        rot = (actor->yaw - state->pathOwner->yaw) & 0xFFF;
        guRotateF(rotMtx, rot / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
        guTranslateF(transMtx, 0.0f, state->pathDist + -80.0, 0.0f);
        guMtxCatF(rotMtx, transMtx, transMtx);
        guMtxL2F(actor->modelMtx, &mtx);
        guMtxCatF(transMtx, actor->modelMtx, actor->modelMtx);
        actorGetNodePos(actor, 8, &actor->x, &actor->y, &actor->z);
        state->pathYawMin = 0;
        state->pathYawMax = 0xFFF;
        if (gCurrentActor->contactFlags & 0x40) {
            switch (actor->actorType) {
            case 2:
            case 5:
                nodeId = 0xF;
                break;
            default:
                nodeId = 0xD;
                break;
            }
            actorGetNodePos(actor, nodeId, &x, &y, &z);
            dy = y - actor->y;
            dx = x - actor->x;
            dz = z - actor->z;
            dist = sqrtf(dx * dx + dz * dz);
            ang = mathAtan2(dist, dy);
            actor->roll = 0.0 - ang * 2048.0 / 3.1415927f;
        } else {
            actor->roll = 0;
        }
        break;
    case 1:
        proxPathActorFollowSpline(actor, state, node, idx, t);
        actorGetNodePos(actor, 1, &actor->x, &actor->y, &actor->z);
        break;
    }
}



void proxPathActorFollowSpline(Actor *actor, PlayerState *state, ProxPath *path, u8 segmentIndex, f32 t) {
    f32 one; // FAKE: value-named 1.0f local keeps one $f register for the guRotateF axes and unk148 stores
    f32 pad1[20];
    f32 p2[3];
    f32 p1[3];
    f32 p0[3];
    s8 idx2;
    f32 a;
    f32 b;
    s16 slot;
    f32 modelF[4][4];
    f32 stepF[4][4];
    s32 pad3;
    f32 yawRotF[4][4];
    f32 ox;
    f32 oy;
    f32 oz;
    f32 yaw;
    f32 pad2[4];
    Mtx blendMtx;
    s8 idx;
    f32 savedScale;
    Mtx prevMtx;
    Mtx curMtx;
    splineSetBasisTension(0.5f);
    idx = segmentIndex;
    a = t - 0.1;
    if (a < 0.0) {
        a = a + 1.0;
        idx--;
        if (idx < 0) {
            a = 0.0f;
            idx = 0;
        }
    }
    proxPathInterpolatePosition(idx, a, path, &p0[0], &p0[1], &p0[2]);
    one = 1.0f;
    b = t + 0.1;
    idx2 = segmentIndex;
    if (b > 1.0) {
        b = b - 1.0;
        idx2++;
        if (idx2 == path->segmentCount) {
            idx2 = path->segmentCount - 1;
            b = 1.0f;
        }
    }
    proxPathInterpolatePosition(idx2, b, path, &p1[0], &p1[1], &p1[2]);
    proxPathInterpolatePosition(segmentIndex, t, path, &p2[0], &p2[1], &p2[2]);
    savedScale = state->unk148;
    state->unk148 = one;
    actor->x = (p2[0] - state->unk13C) * state->unk148 + state->unk13C;
    actor->y = (p2[1] - state->unk140) * state->unk148 + state->unk140;
    actor->z = (p2[2] - state->unk144) * state->unk148 + state->unk144;
    mathNudgeCoords(p0[0], p0[2], &p1[0], &p1[2]);
    yaw = mathAtan2(p1[0] - p0[0], p1[2] - p0[2]) * 57.29577637f + 180.0f;
    guTranslateF(modelF, 0.0f, state->unk148 * -80.0f, 0.0f);
    guScaleF(stepF, actor->sub4->scaleX, actor->sub4->scaleY, actor->sub4->scaleZ);
    guMtxCatF(modelF, stepF, modelF);
    guRotateF(stepF, actor->yaw / 4095.0 * 360.0, 0.0f, one, 0.0f);
    guMtxCatF(modelF, stepF, modelF);
    guRotateF(stepF, -90.0f, one, 0.0f, 0.0f);
    guMtxCatF(modelF, stepF, modelF);
    guAlignF(stepF, yaw, p1[0] - p0[0], p1[1] - p0[1], p1[2] - p0[2]);
    guMtxCatF(modelF, stepF, modelF);
    guRotateF(yawRotF, actor->yaw / 4095.0 * 360.0, 0.0f, one, 0.0f);
    yaw = path->segments[segmentIndex].param6 + (path->segments[segmentIndex].param7 - path->segments[segmentIndex].param6) * t;
    guMtxXFMF(yawRotF, 0.0f, 0.0f, -yaw * state->unk148, &ox, &oy, &oz);
    guTranslateF(stepF, ox, oy, oz);
    guMtxCatF(modelF, stepF, modelF);
    guMtxCatF(modelF, stepF, modelF);
    guTranslateF(stepF, actor->x, actor->y, actor->z);
    guMtxCatF(modelF, stepF, actor->modelMtx);
    state->unk148 = savedScale;
    if (savedScale < 1.0) {
        guMtxF2L((f32 (*)[4])state->unk15C, &prevMtx);
        guMtxF2L(actor->modelMtx, &curMtx);
        mtxLerpL(&prevMtx, &curMtx, 1.0 - state->unk148, &blendMtx);
        guMtxL2F(actor->modelMtx, &blendMtx);
    }
    state->unk148 += 0.1;
    if (state->unk148 > 1.0) {
        state->unk148 = one;
    }
    state->pathYawMin = (s16)(path->segments[segmentIndex].minAngle + (path->segments[segmentIndex].maxAngle - path->segments[segmentIndex].minAngle) * t);
    state->pathYawMax = (s16)(path->segments[segmentIndex].angleB + (path->segments[segmentIndex].angleC - path->segments[segmentIndex].angleB) * t);
    switch (path->slotType) {
    case 1:
    case 2:
        slot = hashTableLookup((s32)path->owner);
        state->pathYawMin = ((s32)(gModelSlots[slot].unk14 * 4096.0f / 360.0f) + state->pathYawMin) & 0xFFF;
        state->pathYawMax = ((s32)(gModelSlots[slot].unk14 * 4096.0f / 360.0f) + state->pathYawMax) & 0xFFF;
        break;
    case 0:
        state->pathYawMin = (state->pathYawMin + path->owner->yaw) & 0xFFF;
        state->pathYawMax = (state->pathYawMax + path->owner->yaw) & 0xFFF;
        break;
    }
}


void proxPathInterpolatePosition(u8 segmentIndex, f32 t, ProxPath *path, f32 *outX, f32 *outY, f32 *outZ) {
    u8 ids[4];
    f32 p[4][3];

    ids[0] = path->segments[segmentIndex - 1 > 0 ? segmentIndex - 1 : 0].startNode;
    ids[1] = path->segments[segmentIndex].startNode;
    ids[2] = path->segments[segmentIndex].endNode;
    ids[3] = path->segments[segmentIndex + 1 < path->segmentCount - 1 ? segmentIndex + 1 : path->segmentCount - 1].endNode;
    switch (path->slotType) {
    case 1:
    case 2:
        modelSlotGetNodePos((s32)path->owner, 1, ids[0], &p[0][0], &p[0][1], &p[0][2]);
        modelSlotGetNodePos((s32)path->owner, 1, ids[1], &p[1][0], &p[1][1], &p[1][2]);
        modelSlotGetNodePos((s32)path->owner, 1, ids[2], &p[2][0], &p[2][1], &p[2][2]);
        modelSlotGetNodePos((s32)path->owner, 1, ids[3], &p[3][0], &p[3][1], &p[3][2]);
        break;
    case 0:
        actorGetNodePos(path->owner, ids[0], &p[0][0], &p[0][1], &p[0][2]);
        actorGetNodePos(path->owner, ids[1], &p[0][0], &p[0][1], &p[0][2]);
        actorGetNodePos(path->owner, ids[1], &p[0][0], &p[0][1], &p[0][2]);
        actorGetNodePos(path->owner, ids[2], &p[0][0], &p[0][1], &p[0][2]);
        break;
    }
    *outX = splineEvalCubic(t, p[0][0], p[1][0], p[2][0], p[3][0]);
    *outY = splineEvalCubic(t, p[0][1], p[1][1], p[2][1], p[3][1]);
    *outZ = splineEvalCubic(t, p[0][2], p[1][2], p[2][2], p[3][2]);
}


void proxPathGetSegmentMatrices(Actor *actor, u8 slotType, u8 nodeA, u8 nodeB, void **outMtxA, void **outMtxB) {
    void *tmp;

    switch (slotType) {
    case 0:
        *outMtxA = (void *)actorStepSubNodeList(actor, nodeA);
        *outMtxB = (void *)actorStepSubNodeList(actor, nodeB);
        break;
    case 1:
    case 2:
        tmp = modelSlotGetNodeMatrix((s32)actor, 1, nodeA);
        *outMtxA = tmp;
        heapFreeDeferred(tmp);
        tmp = modelSlotGetNodeMatrix((s32)actor, 1, nodeB);
        *outMtxB = tmp;
        heapFreeDeferred(tmp);
        break;
    }
}

void mtxLerpL(Mtx *from, Mtx *to, f32 t, Mtx *dst) {
    f32 fromF[4][4];
    f32 toF[4][4];
    s32 i;
    s32 j;

    guMtxL2F(fromF, from);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            fromF[i][j] = fromF[i][j] * t;
        }
    }
    guMtxL2F(toF, to);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            toF[i][j] = toF[i][j] * (1.0 - t);
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            fromF[i][j] += toF[i][j];
        }
    }
    guMtxF2L(fromF, dst);
}
