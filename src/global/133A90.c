#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
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
extern void *gPlayerSlots;

typedef struct ProxPathSegment {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
} ProxPathSegment; // size = 0x1C

typedef struct ProxPath {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 pad32[2];
    /* 0x34 */ ProxPathSegment *unk34;
    /* 0x38 */ struct ProxPath *next;
} ProxPath; // size = 0x3C

extern ProxPath *D_807FDCC0;

void proxPathListClear(void) {
    D_807FDCC0 = NULL;
}

void proxPathSetEnabled(Actor *actor, u8 pathIndex, u8 enabled) {
    ProxPath *node;
    s32 found;

    node = D_807FDCC0;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == actor && node->unk5 == pathIndex) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (found) {
        node->unk31 = enabled;
    }
}

void proxPathSetEndBehavior(Actor *actor, u8 pathIndex, u8 endBehavior) {
    ProxPath *node;
    s32 found;

    node = D_807FDCC0;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == actor && node->unk5 == pathIndex) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (found) {
        node->unk18 = endBehavior;
    }
}

void proxPathAdd(Actor *actor, u8 slotType, u8 pathIndex, u8 pathType, u8 segmentCount, f32 minDist, f32 maxDist, f32 moveSpeed, f32 attachDist, f32 detachDist, f32 actionDist, u8 endBehavior, f32 paramC, f32 paramD, u8 paramE) {
    ProxPath **tail;
    ProxPath *node;

    tail = &D_807FDCC0;
    node = D_807FDCC0;
    while (node != NULL) {
        tail = &node->next;
        node = node->next;
    }
    node = *tail = heapAlloc(0x3C);
    node->unk0 = actor;
    node->unk4 = slotType;
    node->unk5 = pathIndex;
    node->unk6 = pathType;
    node->unk7 = segmentCount;
    node->unk8 = minDist;
    node->unkC = maxDist;
    node->unk14 = moveSpeed;
    node->unk1C = attachDist;
    node->unk20 = detachDist;
    node->unk24 = actionDist;
    node->unk18 = endBehavior;
    node->unk28 = paramC;
    node->unk2C = paramD;
    node->unk30 = paramE;
    node->unk31 = 1;
    node->next = NULL;
    node->unk34 = heapAlloc(segmentCount * 0x1C);
}

void proxPathSetSegment(Actor *actor, u8 pathIndex, u8 segmentIndex, u8 startNode, u8 endNode, f32 length, f32 param6, f32 param7, u8 disabled, s16 minAngle, s16 maxAngle, s16 angleB, s16 angleC) {
    ProxPath *node;
    s32 found;

    node = D_807FDCC0;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == actor && node->unk5 == pathIndex) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (found) {
        node->unk34[segmentIndex].unk0 = startNode;
        node->unk34[segmentIndex].unk1 = endNode;
        node->unk34[segmentIndex].unk4 = length;
        node->unk34[segmentIndex].unk8 = param6;
        node->unk34[segmentIndex].unkC = param7;
        node->unk34[segmentIndex].unk18 = disabled;
        node->unk34[segmentIndex].unk10 = minAngle;
        node->unk34[segmentIndex].unk14 = maxAngle;
        node->unk34[segmentIndex].unk12 = angleB;
        node->unk34[segmentIndex].unk16 = angleC;
    }
}

void proxPathRemoveActor(Actor *actor) {
    ProxPath **prev;
    ProxPath *node;
    ProxPath *next;

    prev = &D_807FDCC0;
    node = *prev;
    while (node != NULL) {
        if (node->unk0 == actor) {
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

typedef struct PlayerSlot {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x2E8];
} PlayerSlot; // size = 0x2F0

extern u8 gPlayerCount;
extern u32 gGlobalOverlayFlags;

void proxPathUpdateAllPlayers(void) {
    u8 i;

    for (i = 0; i < gPlayerCount; i++) {
        if (((PlayerSlot *)gPlayerSlots)[i].unk0 != 0) {
            proxPathAttachNearestToPlayer(((PlayerSlot *)gPlayerSlots)[i].unk4, i, flagGet(0x183, 0) || (gGlobalOverlayFlags & 0x10000000) || gPlayerCount >= 2 || func_807142D8());
        }
    }
}

typedef struct H1PlayerBlock {
    /* 0x000 */ u8 pad0[0x2C0];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F0 - 0x2C1];
} H1PlayerBlock; // size = 0x2F0

typedef struct H1ActorState {
    /* 0x000 */ u8 pad0[0x130];
    /* 0x130 */ Actor *unk130;
    /* 0x134 */ u8 unk134;
    /* 0x135 */ u8 pad135[3];
    /* 0x138 */ f32 unk138;
    /* 0x13C */ f32 unk13C;
    /* 0x140 */ f32 unk140;
    /* 0x144 */ f32 unk144;
    /* 0x148 */ f32 unk148;
    /* 0x14C */ u8 pad14C[0x10];
    /* 0x15C */ u8 unk15C[0x40];
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ u8 pad1A0[4];
    /* 0x1A4 */ u8 playerIndex;
} H1ActorState;

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
    H1ActorState *state;
    f32 dz;
    f32 dist;

    state = playerActor->customState;
    isPlayer = playerActor->actorType == 6;
    node = D_807FDCC0;
    bestDist = 9999.0f;
    best = NULL;
    if (isPlayer) {
        isPlayer = ((H1PlayerBlock *)gPlayerSlots)[state->playerIndex].unk2C0 == 2;
    }
    while (node != NULL) {
        got = proxPathGetActorPosition(node->unk0, node->unk4, &x, &y, &z);
        dx = playerActor->x - x;
        dy = playerActor->y - y;
                dz = playerActor->z - z;
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        if (dist < node->unk1C && node->unk31 != 0) {
            if (node->unk6 == 1 || (allowBoss != 0 && (node->unk0->flags & 0x04000000))) {
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
        state->unk138 = out;
        state->unk130 = best->unk0;
        state->unk134 = best->unk5;
        state->unk19C = 0;
        state->unk19E = 0xFFF;
        playerActor->speedXZ = 0.0f;
        isPlayer = best->unk6;
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

typedef struct H1SlotEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[8];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ u32 *unk24;
    /* 0x28 */ u8 pad28[0x5C];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ u8 pad86[0xA];
} H1SlotEntry; // size = 0x90

extern H1SlotEntry *gModelSlots;

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
        slot = hashTableLookup(actor);
        *outX = gModelSlots[slot].unk0;
        *outY = gModelSlots[slot].unk4;
        *outZ = gModelSlots[slot].unk8;
        if (*gModelSlots[slot].unk24 & 1) {
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
        r2 = path->unk24 * path->unk24;
    } else {
        r2 = path->unk20 * path->unk20;
    }
    if (path->unk6 == 1) {
        r2 += D_80753B74[gCurrentCharacterIndex];
    }
    for (i = 0; i < path->unk7; i++) {
        if (path->unk34[i].unk18 == 0) {
            idA = path->unk34[i].unk0;
            idB = path->unk34[i].unk1;
            switch (path->unk4) {
            case 0:
                actorGetNodePos(path->unk0, idA, &ax, &ay, &az);
                actorGetNodePos(path->unk0, idB, &bx, &by, &bz);
                break;
            case 1:
            case 2:
                modelSlotGetNodePos(path->unk0, 1, idA, &ax, &ay, &az);
                modelSlotGetNodePos(path->unk0, 1, idB, &bx, &by, &bz);
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

    if (path->unk4 == 0) {
        return 1;
    }
    slot = hashTableLookup(path->unk0);
    if (!(gModelSlots[slot].unk84 == 0xC9 || gModelSlots[slot].unk84 == 0xCA || gModelSlots[slot].unk84 == 0x1CB || gModelSlots[slot].unk84 == 0x1F7 || gModelSlots[slot].unk84 == 0x1F8)) {
        return 1;
    }
    delta = gModelSlots[slot].unk14 * 4096.0f / 360.0f;
    if (mathAngleInArcWithMargin((s16)((path->unk34[segmentIndex].unk10 + delta) & 0xFFF), (s16)((path->unk34[segmentIndex].unk14 + delta) & 0xFFF), angle, 0)) {
        return 1;
    }
    return 0;
}


f32 proxPathAttachToSegment(Actor *actor, H1ActorState *state, ProxPath *path, u8 segmentIndex) {
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

    idA = path->unk34[segmentIndex].unk0;
    idB = path->unk34[segmentIndex].unk1;
    switch (path->unk4) {
    case 0:
        actorGetNodePos(path->unk0, idA, &ax, &ay, &az);
        actorGetNodePos(path->unk0, idB, &bx, &by, &bz);
        break;
    case 1:
    case 2:
        modelSlotGetNodePos(path->unk0, 1, idA, &ax, &ay, &az);
        modelSlotGetNodePos(path->unk0, 1, idB, &bx, &by, &bz);
        break;
    }
    actorGetNodePos(actor, 1, &px, &py, &pz);
    camClosestPointOnSegment(px, py, pz, ax, ay, az, bx, by, bz, &ox, &oy, &oz);
    t = (oy - ay) / (by - ay);
    if (path->unk18 == 2 || path->unk18 == 3) {
        if (segmentIndex == 0) {
            if (t < 0.05) {
                t = 0.05f;
            }
        }
    }
    if (path->unk18 == 1 || path->unk18 == 3) {
        if (segmentIndex + 1 == path->unk7) {
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
        *outDist = *outDist + path->unk34[i].unk4;
    }
    *outDist = *outDist + path->unk34[segmentIndex].unk4 * t;
}

void proxPathFindDistanceSegment(ProxPath *path, f32 dist, u8 *outSegment, f32 *outT) {
    f32 rem;
    u8 i;

    i = 0;
    rem = dist;
    do {
        dist = rem;
        rem -= path->unk34[i++].unk4;
    } while (0.0 < rem && i < path->unk7);
    i--;
    *outSegment = i;
    *outT = dist / path->unk34[i].unk4;
}

typedef struct H1CamState {
    /* 0x000 */ u8 pad0[0x124];
    /* 0x124 */ f32 unk124;
    /* 0x128 */ f32 unk128;
    /* 0x12C */ u8 unk12C;
    /* 0x12D */ u8 pad12D[3];
    /* 0x130 */ Actor *unk130;
    /* 0x134 */ u8 unk134;
    /* 0x135 */ u8 pad135[3];
    /* 0x138 */ f32 unk138;
    /* 0x13C */ u8 pad13C[0x68];
    /* 0x1A4 */ u8 playerIndex;
} H1CamState;

typedef struct H1ActorView {
    /* 0x00 */ u8 pad0[0x6A];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x7A];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
} H1ActorView;

#define H1BB48 ((H1ActorView *)gActivePlayerActor)

extern H1CamState *gActivePlayerState;
extern u32 gFrameDelta;

void proxPathAdvance(f32 speedMultiplier) {
    f32 step;
    ProxPath *node;
    s32 found;

    node = D_807FDCC0;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == gActivePlayerState->unk130 && node->unk5 == gActivePlayerState->unk134) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (!found || node->unk31 == 0) {
        H1BB48->unk6A &= ~0x40;
        return;
    }
    gActivePlayerState->unk124 = node->unk28;
    gActivePlayerState->unk128 = node->unk2C;
    gActivePlayerState->unk12C = node->unk30;
    step = gFrameDelta * 0.5;
    gActivePlayerState->unk138 = gActivePlayerState->unk138 + node->unk14 * step * speedMultiplier;
    H1BB48->unk6A &= ~0x80;
    if (node->unkC < gActivePlayerState->unk138) {
        if (node->unk18 == 1 || node->unk18 == 3) {
            H1BB48->unkEE = H1BB48->unkE6;
            playerStateQueueCallback(0xD, NULL, gActivePlayerState->playerIndex);
        }
        gActivePlayerState->unk138 = node->unkC;
    }
    if (gActivePlayerState->unk138 < node->unk8) {
        if (node->unk18 == 2 || node->unk18 == 3) {
            H1BB48->unkEE = H1BB48->unkE6;
            playerResumeLocomotion(gActivePlayerActor);
        }
        gActivePlayerState->unk138 = node->unk8;
    }
    if (node->unkC <= gActivePlayerState->unk138 || gActivePlayerState->unk138 <= node->unk8) {
        H1BB48->unk6A |= 0x80;
    }
}

typedef struct H1ActorB {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[4];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0xC];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[8];
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x8A];
    /* 0x174 */ H1ActorState *unk174;
} H1ActorB;


void proxPathFollowerStep(H1ActorB **pActor) {
    H1ActorB *actor;
    H1ActorState *state;
    u8 idx;
    f32 t;
    ProxPath *node;
    void *p128;
    void *p124;
    s32 found;
    Mtx mtx;
    f32 mA[4][4];
    f32 m6[4][4];
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
    node = D_807FDCC0;
    state = actor->unk174;
    found = 0;
    while (node != NULL && !found) {
        if (node->unk0 == state->unk130 && node->unk5 == state->unk134) {
            found = 1;
        } else {
            node = node->next;
        }
    }
    if (!found || (actor->unk64 & 0x2000)) {
        actor->unk6A &= ~0x40;
        return;
    }
    proxPathFindDistanceSegment(node, state->unk138, &idx, &t);
    idA = node->unk34[idx].unk0;
    idB = node->unk34[idx].unk1;
    switch (node->unk6) {
    case 0:
        proxPathGetSegmentMatrices(node->unk0, node->unk4, idA, idB, &p128, &p124);
        mtxLerpL(p128, p124, 1.0 - t, &mtx);
        rot = (actor->unkE6 - state->unk130->yaw) & 0xFFF;
        guRotateF(m6, rot / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
        guTranslateF(mA, 0.0f, state->unk138 + -80.0, 0.0f);
        guMtxCatF(m6, mA, mA);
        guMtxL2F(actor->unkC, &mtx);
        guMtxCatF(mA, actor->unkC, actor->unkC);
        actorGetNodePos(actor, 8, &actor->unk7C, &actor->unk80, &actor->unk84);
        state->unk19C = 0;
        state->unk19E = 0xFFF;
        if (gCurrentActor->contactFlags & 0x40) {
            switch (actor->unk58) {
            case 2:
            case 5:
                nodeId = 0xF;
                break;
            default:
                nodeId = 0xD;
                break;
            }
            actorGetNodePos(actor, nodeId, &x, &y, &z);
            dy = y - actor->unk80;
            dx = x - actor->unk7C;
            dz = z - actor->unk84;
            dist = sqrtf(dx * dx + dz * dz);
            ang = mathAtan2(dist, dy);
            actor->unkE8 = 0.0 - ang * 2048.0 / 3.1415927f;
        } else {
            actor->unkE8 = 0;
        }
        break;
    case 1:
        proxPathActorFollowSpline(actor, state, node, idx, t);
        actorGetNodePos(actor, 1, &actor->unk7C, &actor->unk80, &actor->unk84);
        break;
    }
}



void proxPathActorFollowSpline(H1ActorB *actor, H1ActorState *state, ProxPath *path, u8 segmentIndex, f32 t) {
    f32 one;
    f32 pad1[20];
    f32 p2[3];
    f32 p1[3];
    f32 p0[3];
    s8 idx2;
    f32 a;
    f32 b;
    s16 slot;
    f32 m1[4][4];
    f32 m2[4][4];
    s32 gapw;
    f32 m3[4][4];
    f32 ox;
    f32 oy;
    f32 oz;
    f32 yaw;
    f32 pad2[4];
    Mtx mA;
    s8 idx;
    f32 savedScale;
    Mtx mB;
    Mtx mC;
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
        if (idx2 == path->unk7) {
            idx2 = path->unk7 - 1;
            b = 1.0f;
        }
    }
    proxPathInterpolatePosition(idx2, b, path, &p1[0], &p1[1], &p1[2]);
    proxPathInterpolatePosition(segmentIndex, t, path, &p2[0], &p2[1], &p2[2]);
    savedScale = state->unk148;
    state->unk148 = one;
    actor->unk7C = (p2[0] - state->unk13C) * state->unk148 + state->unk13C;
    actor->unk80 = (p2[1] - state->unk140) * state->unk148 + state->unk140;
    actor->unk84 = (p2[2] - state->unk144) * state->unk148 + state->unk144;
    mathNudgeCoords(p0[0], p0[2], &p1[0], &p1[2]);
    yaw = mathAtan2(p1[0] - p0[0], p1[2] - p0[2]) * 57.29577637f + 180.0f;
    guTranslateF(m1, 0.0f, state->unk148 * -80.0f, 0.0f);
    guScaleF(m2, actor->unk4->scaleX, actor->unk4->scaleY, actor->unk4->scaleZ);
    guMtxCatF(m1, m2, m1);
    guRotateF(m2, actor->unkE6 / 4095.0 * 360.0, 0.0f, one, 0.0f);
    guMtxCatF(m1, m2, m1);
    guRotateF(m2, -90.0f, one, 0.0f, 0.0f);
    guMtxCatF(m1, m2, m1);
    guAlignF(m2, yaw, p1[0] - p0[0], p1[1] - p0[1], p1[2] - p0[2]);
    guMtxCatF(m1, m2, m1);
    guRotateF(m3, actor->unkE6 / 4095.0 * 360.0, 0.0f, one, 0.0f);
    yaw = path->unk34[segmentIndex].unk8 + (path->unk34[segmentIndex].unkC - path->unk34[segmentIndex].unk8) * t;
    guMtxXFMF(m3, 0.0f, 0.0f, -yaw * state->unk148, &ox, &oy, &oz);
    guTranslateF(m2, ox, oy, oz);
    guMtxCatF(m1, m2, m1);
    guMtxCatF(m1, m2, m1);
    guTranslateF(m2, actor->unk7C, actor->unk80, actor->unk84);
    guMtxCatF(m1, m2, actor->unkC);
    state->unk148 = savedScale;
    if (savedScale < 1.0) {
        guMtxF2L((f32 (*)[4])state->unk15C, &mB);
        guMtxF2L(actor->unkC, &mC);
        mtxLerpL(&mB, &mC, 1.0 - state->unk148, &mA);
        guMtxL2F(actor->unkC, &mA);
    }
    state->unk148 = state->unk148 + 0.1;
    if (state->unk148 > 1.0) {
        state->unk148 = one;
    }
    state->unk19C = (s16)(path->unk34[segmentIndex].unk10 + (path->unk34[segmentIndex].unk12 - path->unk34[segmentIndex].unk10) * t);
    state->unk19E = (s16)(path->unk34[segmentIndex].unk14 + (path->unk34[segmentIndex].unk16 - path->unk34[segmentIndex].unk14) * t);
    switch (path->unk4) {
    case 1:
    case 2:
        slot = hashTableLookup(path->unk0);
        state->unk19C = ((s32)(gModelSlots[slot].unk14 * 4096.0f / 360.0f) + state->unk19C) & 0xFFF;
        state->unk19E = ((s32)(gModelSlots[slot].unk14 * 4096.0f / 360.0f) + state->unk19E) & 0xFFF;
        break;
    case 0:
        state->unk19C = (state->unk19C + path->unk0->yaw) & 0xFFF;
        state->unk19E = (state->unk19E + path->unk0->yaw) & 0xFFF;
        break;
    }
}


void proxPathInterpolatePosition(u8 segmentIndex, f32 t, ProxPath *path, f32 *outX, f32 *outY, f32 *outZ) {
    u8 ids[4];
    f32 p[4][3];

    ids[0] = path->unk34[segmentIndex - 1 > 0 ? segmentIndex - 1 : 0].unk0;
    ids[1] = path->unk34[segmentIndex].unk0;
    ids[2] = path->unk34[segmentIndex].unk1;
    ids[3] = path->unk34[segmentIndex + 1 < path->unk7 - 1 ? segmentIndex + 1 : path->unk7 - 1].unk1;
    switch (path->unk4) {
    case 1:
    case 2:
        modelSlotGetNodePos(path->unk0, 1, ids[0], &p[0][0], &p[0][1], &p[0][2]);
        modelSlotGetNodePos(path->unk0, 1, ids[1], &p[1][0], &p[1][1], &p[1][2]);
        modelSlotGetNodePos(path->unk0, 1, ids[2], &p[2][0], &p[2][1], &p[2][2]);
        modelSlotGetNodePos(path->unk0, 1, ids[3], &p[3][0], &p[3][1], &p[3][2]);
        break;
    case 0:
        actorGetNodePos(path->unk0, ids[0], &p[0][0], &p[0][1], &p[0][2]);
        actorGetNodePos(path->unk0, ids[1], &p[0][0], &p[0][1], &p[0][2]);
        actorGetNodePos(path->unk0, ids[1], &p[0][0], &p[0][1], &p[0][2]);
        actorGetNodePos(path->unk0, ids[2], &p[0][0], &p[0][1], &p[0][2]);
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
        tmp = modelSlotGetNodeMatrix(actor, 1, nodeA);
        *outMtxA = tmp;
        heapFreeDeferred(tmp);
        tmp = modelSlotGetNodeMatrix(actor, 1, nodeB);
        *outMtxB = tmp;
        heapFreeDeferred(tmp);
        break;
    }
}

void mtxLerpL(Mtx *mA, Mtx *mB, f32 t, Mtx *dst) {
    f32 m1[4][4];
    f32 m2[4][4];
    s32 i;
    s32 j;

    guMtxL2F(m1, mA);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m1[i][j] = m1[i][j] * t;
        }
    }
    guMtxL2F(m2, mB);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m2[i][j] = m2[i][j] * (1.0 - t);
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m1[i][j] += m2[i][j];
        }
    }
    guMtxF2L(m1, dst);
}
