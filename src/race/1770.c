#include "common.h"
#include "race.h"
#include "compiler/ido/memory.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/35000.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"
#include "proto/race/1770.h"
#include "proto/race/7BD0.h"

s32 raceGetNextWaypointIndex(s32 pathLength, s32 curWaypoint) {
    s32 next = curWaypoint + 1;
    if (pathLength != next) {
        return curWaypoint + 1; // FAKE: recomputes next; returning next changes the addiu placement
    }
    return 0;
}

s32 raceGetPrevWaypointIndex(s32 pathLength, s32 curWaypoint) {
    if (curWaypoint == 0) {
        return pathLength - 1;
    }
    return curWaypoint - 1;
}

typedef TargetVec3f RaceAPoint3f;


// Race actor: Actor plus its component pointers from 0x174 on.
typedef struct RaceActor {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ RaceParticipant *unk174;
    /* 0x178 */ RacePathState *unk178;
    /* 0x17C */ RaceAuxState *unk17C;
    /* 0x180 */ u8 pad180[4];
    /* 0x184 */ void *unk184;
} RaceActor;

/* Effect node actor spawned by spawnNodeSpawnById. */
typedef struct {
    u8 pad0[0x178];
    RaceParticipant *unk178;
    RacePathState *unk17C;
    u8 pad180[4];
    RacePair *unk184;
} RaceNodeActor;

extern RaceAPoint3f **gMinecartTrackPoints;
extern Actor *gCurrentActor;

void raceInterpolateWaypointPos(RacePathState *pathState, f32 *outPos, f32 *inPos, s32 nextWaypoint, s32 nextNextWaypoint) {
    s32 padA;
    s32 padB;
    RaceAPoint3f *points;
    s32 i;
    f32 closerTarget[3];
    s32 padM;
    s8 laneDiff;
    RaceAPoint3f *curPoint;

    points = gMinecartTrackPoints[pathState->unk1];
    curPoint = &points[pathState->unk2];
    laneDiff = pathState->unk0 - pathState->unk1;
    mathPickCloserTargetPoint3D(inPos[0], inPos[1], inPos[2], curPoint, &points[nextWaypoint], &points[nextWaypoint], &points[nextNextWaypoint], &closerTarget[0], &closerTarget[1], &closerTarget[2]);
    pathState->unk8 += 0.01 * gCurrentActor->speedXZ;
    if (pathState->unk8 >= 1.0f) {
        pathState->unk8 = 1.0f;
        pathState->unk0 = pathState->unk1;
    }
    pathState->unkC = mathSinF(pathState->unk8 * 2048.0f) * (laneDiff * 300);
    for (i = 0; i < 3; i++) {
        outPos[i] = outPos[i] + pathState->unk8 * (closerTarget[i] - outPos[i]);
    }
}

extern s32 D_807F5FD0;

void raceInitSplinePoints(void) {
    RaceAPoint3f *buf;
    u8 *src;
    RaceAPoint3f **tbl;
    u32 lo; // FAKE: one slot holds the byte length, then the tbl[2] pointer; a separate pointer local reallocates the loop
    s32 i;
    s32 count;

    count = (gMinecartTrackPoints[1] - gMinecartTrackPoints[0]) / 2;
    buf = heapAlloc(count * 0x24);
    tbl = heapAlloc(0x10);
    for (i = 0; i < 4; i++) {
        tbl[i] = buf + i * count;
    }
    src = (u8 *)gMinecartTrackPoints[0];
    lo = count * 12;
    buf = tbl[0];
    memcpy(buf, src, lo);
    buf = tbl[2];
    memcpy(buf, lo + src, lo);
    buf = tbl[1];
    src = (u8 *)tbl[0];
    lo = (u32)tbl[2];
    for (i = 0; i < count; i++) {
        buf[i].x = (((RaceAPoint3f *)lo)[i].x + ((RaceAPoint3f *)src)[i].x) * 0.5;
        buf[i].y = (((RaceAPoint3f *)lo)[i].y + ((RaceAPoint3f *)src)[i].y) * 0.5;
        buf[i].z = (((RaceAPoint3f *)lo)[i].z + ((RaceAPoint3f *)src)[i].z) * 0.5;
    }
    D_807F5FD0 = 3;
    gMinecartTrackPoints = tbl;
}

extern s16 D_80750AC4;
extern Actor *gSpawnedActor;

void raceInitOpponentEntities(Actor *parent) {
    RaceParticipant *parentPart;
    Actor *s2;
    RacePathState *s1;
    RaceParticipant *s0;
    RacePair *temp;
    Actor *spawnedNode;
    Actor *spawnedActor;
    u8 *pad;

    parentPart = ((RaceActor *)parent)->unk174;
    raceInitParticipantArray(parent, 2);
    actorSpawn(0x12E, 0x95);
    s2 = gSpawnedActor;
    s0 = ((RaceActor *)s2)->unk174;
    raceRegisterParticipant(parent, 1, s2, s0);
    s0->lap = 0;
    s0->unk27 = 0;
    s0->actor = parent;
    s0->unk36 = 1;
    s0->playerIdx = 0;
    s1 = ((RaceActor *)s2)->unk178;
    spawnedNode = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
    s1->unk30 = spawnedNode;
    temp = ((RaceNodeActor *)spawnedNode)->unk184;
    temp->data = s0;
    temp->actor = s2;
    actorSpawn(0x130, 0);
    spawnedActor = gSpawnedActor;
    s1->unk34 = spawnedActor;
    s0 = ((RaceNodeActor *)spawnedNode)->unk178;
    raceRegisterParticipant(parent, 0, spawnedNode, s0);
    s0->lap = 0;
    s0->unk27 = 1;
    s0->actor = parent;
    s0->unk36 = 0;
    s1 = ((RaceNodeActor *)spawnedNode)->unk17C;
    s1->unk30 = s2;
    s1->unk34 = spawnedActor;
    s0 = ((RaceActor *)spawnedActor)->unk174;
    s0->actor = parent;
    s1 = ((RaceActor *)spawnedActor)->unk178;
    s1->unk30 = s2;
    D_80750AC4 = 0;
    parentPart->unk25 = 1;
}


void raceInitSplineAndOpponent(void) {
    raceInitSplinePoints();
    raceInitCarRaceManager();
}


void racePlayCheckpointSfx(RacePathState *pathState, u8 timer, f32 volume) {
    pathState->unk10 = timer;
    pathState->unk14 = volume;
    sfxPlayOnFreeSlot(0x1EB, 0x7FFF, 64.0f, 1.0f, 0, 0);
}

void raceAdvanceCheckpoint(RacePathState *pathState, RaceParticipant *participant, s32 pathLength) {
    if (pathState->unk2 + 1 != pathLength) {
        pathState->unk2++;
    } else {
        pathState->unk2 = 0;
        if (participant != NULL) {
            participant->lap++;
        }
    }
    if (participant != NULL) {
        participant->unk3A = pathState->unk2 + 1;
    }
}

extern u8 D_8072006C[];
extern void *D_8002FBB0[4];
extern u8 gLightSlotsEnd;
void raceApplyPositionOffset(f32 *tgt, f32 *pos) {
    s16 angle;
    s32 pad;
    f32 offsetDist;
    f32 dz;
    f32 dx;

    angle = mathAngleBetweenPointsRad(tgt[0], tgt[2], pos[0], pos[2]) * 2048.0 / 3.1415927f;
    dz = pos[2] - tgt[2];
    dx = pos[0] - tgt[0];
    offsetDist = sqrtf((dz * dz) + (dx * dx)) * (*(f32 *)&gCurrentActor->speedXZ * 0.03); // FAKE: punned re-read of the f32 speedXZ; the plain field changes the load scheduling
    gCurrentActor->x = pos[0] + (mathSinF(angle) * offsetDist);
    gCurrentActor->z = pos[2] + (mathCosF(angle) * offsetDist);
    gCurrentActor->y = gCurrentActor->y + (tgt[1] - gCurrentActor->y) * 0.8;
}


void raceUpdateOrientation(RacePathState *pathState) {
    s16 pad;
    s16 rollOffset;
    f32 cosYaw;
    s16 yawOffset;
    f32 rollScaled;
    f32 sinYaw;

    yawOffset = pathState->unk18 + pathState->unkC;
    rollOffset = mathAngleSignedDistance(0, (s16)pathState->unk1C);
    yawOffset &= 0xFFF;
    cosYaw = mathCosF(yawOffset);
    sinYaw = mathSinF(yawOffset);
    gCurrentActor->yaw = gCurrentActor->moveYaw + yawOffset;
    gCurrentActor->yaw &= 0xFFF;
    rollScaled = rollOffset;
    gCurrentActor->roll = rollScaled * cosYaw;
    gCurrentActor->roll = gCurrentActor->roll + pathState->unk20;
    gCurrentActor->roll &= 0xFFF;
    gCurrentActor->pitch = rollScaled * sinYaw;
    gCurrentActor->pitch = gCurrentActor->pitch + pathState->unk24;
    gCurrentActor->pitch &= 0xFFF;
}


void racePathFollowStep(RacePathState *pathState, RaceParticipant *participant, u8 spawnSparks) {
    s32 count;
    s32 next;
    s32 next2;
    RaceAPoint3f *points;
    RaceAPoint3f *cur;
    RaceAPoint3f *nxt;
    RaceAPoint3f *nxt2;
    f32 pos[3];
    f32 tgt[3];
    f32 ang;
    f32 thrust;
    f32 oldAng;
    f32 spd;
    f32 dist;
    u8 flag;
    s16 yawDelta;
    f32 hx;
    f32 hy;
    f32 hz;

    count = gMinecartTrackPoints[pathState->unk0 + 1] - gMinecartTrackPoints[pathState->unk0];
    next = raceGetNextWaypointIndex(count, pathState->unk2);
    next2 = raceGetNextWaypointIndex(count, next);
    points = gMinecartTrackPoints[pathState->unk0];
    cur = &points[pathState->unk2];
    nxt2 = &points[next2];
    nxt = &points[next];
    oldAng = gCurrentActor->moveYaw;
    flag = pathState->unk39;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->x = cur->x;
        gCurrentActor->y = cur->y;
        gCurrentActor->z = cur->z;
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->yaw = mathAngleBetweenPointsRad(nxt->x, nxt->z, gCurrentActor->x, gCurrentActor->z) * 2048.0 / 3.1415927f;
        gCurrentActor->moveYaw = gCurrentActor->yaw;
        pathState->unk18 = 0.0f;
    }
    if (flag != 0) {
        thrust = 0.0f;
        pathState->unk39--;
        gCurrentActor->speedXZ = 0.0f;
        pathState->unk14 = 0.0f;
        pathState->unk10 = 0;
    } else {
        thrust = participant->unk4;
    }
    if (pathState->unk10 != 0) {
        pathState->unk10--;
    } else {
        pathState->unk14 = pathState->unk14 * 0.7;
    }
    spd = gCurrentActor->speedXZ * gCurrentActor->speedXZ * 0.0033333334f + 0.2;
    gCurrentActor->speedXZ = gCurrentActor->speedXZ + (thrust - spd);
    if (gCurrentActor->speedXZ < 0.0f) {
        gCurrentActor->speedXZ = 0.0f;
    }
    ang = mathAngleBetweenPointsRad(nxt->x, nxt->z, cur->x, cur->z) * 2048.0 / 3.1415927f;
    pos[0] = mathSinF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ + gCurrentActor->x;
    pos[2] = mathCosF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ + gCurrentActor->z;
    pos[1] = gCurrentActor->y;
    dist = sqrtf((cur->x - nxt->x) * (cur->x - nxt->x) + (cur->z - nxt->z) * (cur->z - nxt->z));
    pathState->unk1C = mathAngleEaseToward(pathState->unk1C, mathAtan2(cur->y - nxt->y, dist) * 2048.0 / 3.1415927f, 3.0f);
    if (gCurrentActor->speedXZ > 0.001) {
        gCurrentActor->moveYaw = mathAngleEaseToward(gCurrentActor->moveYaw, ang, 50.0f / gCurrentActor->speedXZ);
    }
    if (mathPickCloserTargetPoint3D(pos[0], pos[1], pos[2], cur, nxt, nxt, nxt2, &tgt[0], &tgt[1], &tgt[2]) != 0) {
        raceAdvanceCheckpoint(pathState, participant, count);
        next = raceGetNextWaypointIndex(count, pathState->unk2);
        next2 = raceGetNextWaypointIndex(count, next);
        cur = &points[pathState->unk2];
        nxt2 = &points[next2];
    }
    if (pathState->unk0 != pathState->unk1) {
        raceInterpolateWaypointPos(pathState, tgt, pos, next, next2);
    } else if (pathState->unk4 != 0) {
        pathState->unk4--;
    }
    raceApplyPositionOffset(tgt, pos);
    yawDelta = mathAngleSignedDistance(gCurrentActor->moveYaw, (s16)oldAng);
    pathState->unk28 += -0.04f * gCurrentActor->speedXZ * yawDelta * mathCosF(pathState->unk18);
    pathState->unk28 -= 10.0f * gCurrentActor->speedXZ * mathSinF(pathState->unk18);
    pathState->unk28 = pathState->unk28 * 0.7f;
    pathState->unk18 = pathState->unk18 + pathState->unk28;
    raceUpdateOrientation(pathState);
    if (spawnSparks != 0) {
        if ((randomLcgNext() & 0xFF) < gCurrentActor->speedXZ * 0.3 && pathState->unk0 == pathState->unk1) {
            mathPickCloserTargetPoint3D(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, cur, &points[next], &points[next], nxt2, &hx, &hy, &hz);
            effectSetSpeed((s32)gCurrentActor);
            effectSetCallback(timedLightOrbitUpdate);
            D_8002FBB0[gLightSlotsEnd] = effectCreateAtPosition(D_8072006C, 0.4f, hx, hy, hz);
            gLightSlotsEnd++;
            gLightSlotsEnd = gLightSlotsEnd % 4;
            sfxPlayAtPositionPooled(hx, hy, hz, 0x8A, 0x96, 0x7F, 0x14, 0x50, 0.3f, 0);
        }
    }
    if (participant != NULL) {
        nxt = &points[next];
        participant->unk40 = (gCurrentActor->x - nxt->x) * (gCurrentActor->x - nxt->x) + (gCurrentActor->y - nxt->y) * (gCurrentActor->y - nxt->y) + (gCurrentActor->z - nxt->z) * (gCurrentActor->z - nxt->z);
    }
}


void raceSpawnProjectile(RaceParticipant *participant) {
    RacePathState *projPath;
    RacePathState *actorPath;
    RaceAuxState *projAux;

    if (participant->unk2C == NULL && participant->unk2A != 0) {
        actorPath = ((RaceActor *)gCurrentActor)->unk178;
        participant->unk2A--;
        actorSpawn(0x131, 0x96);
        projPath = ((RaceActor *)gSpawnedActor)->unk178;
        projAux = ((RaceActor *)gSpawnedActor)->unk17C;
        projAux->owner = gCurrentActor;
        projAux->target = raceFindNearestParticipant(gCurrentActor);
        participant->unk2C = gSpawnedActor;
        gSpawnedActor->x = gCurrentActor->x;
        gSpawnedActor->y = gCurrentActor->y;
        gSpawnedActor->z = gCurrentActor->z;
        gSpawnedActor->moveYaw = gCurrentActor->moveYaw;
        gSpawnedActor->yaw = gCurrentActor->yaw;
        gSpawnedActor->speedXZ = gCurrentActor->speedXZ;
        *projPath = *actorPath;
        sfxPlayOnFreeSlot(0x18B, 0x7FFF, 64.0f, 1.0f, 0, 0);
    } else {
        sfxPlayOnFreeSlot(0xE2, 0x7FFF, 64.0f, 1.0f, 0, 0);
    }
    participant->unk29 = 0;
}


void racePlayEngineSfx(void) {
    sfxPlayActorSound(gCurrentActor, 0x12D, 0, 1, 0, 0xFF, 1.0f, 0);
    sfxPlayActorSound(gCurrentActor, 0x12E, 0, 1, 1, 0xFF, 1.0f, 0);
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void raceUpdateEngineSoundPitch(f32 moveSpeed) {
    s32 pad;
    s16 idx;

    idx = D_80770628[gCurrentActor->soundSlots[0]];
    D_80770B68[idx] = moveSpeed / 20.0 + 1.0;
    D_80770BC0[idx] = 1.0f;
    idx = D_80770628[gCurrentActor->soundSlots[1]];
    gCurrentActor->unk74 = moveSpeed / 20.0;
    if (gCurrentActor->unk74 > 1.0) {
        gCurrentActor->unk74 = 1.0f;
    }
    if (gCurrentActor->unk74 < 0.0) {
        gCurrentActor->unk74 = 0.0f;
    }
    if (D_80770BC0[idx] == 0.0f) {
        D_80770B68[idx] = ((u32)randomLcgNext() / 4294967295.0 * 0.05 + 0.975) * (0.2 + moveSpeed / 15.0);
        D_80770BC0[idx] = 3.0f;
    }
}


void raceVehicleRenderCallback(void *glist, Actor *actor) {
    raceRenderHud(glist, actor, ((RaceActor *)actor)->unk174);
}

extern u8 gBossFightPhase;
extern void *gPrimaryPlayerActor;

void raceVehicleBehaviorUpdate(void) {
    s32 len;
    RacePathState *pathState;
    RaceParticipant *participant;
    s16 shakeAngle;
    f32 off;
    f32 bonus;
    Actor *manager;
    RaceParticipant *managerData;
    s32 i;
    f32 bumpX;
    f32 bumpY;
    f32 bumpZ;

    participant = gCurrentActor->customState;
    pathState = ((RaceActor *)gCurrentActor)->unk178;
    if (!(gCurrentActor->flags & 0x10)) {
        len = gMinecartTrackPoints[pathState->unk0 + 1] - gMinecartTrackPoints[pathState->unk0];
        participant->unk2A = 3;
        gCurrentActor->unk144 = 0x3C;
        pathState->unk2 = raceGetPrevWaypointIndex(len, 0);
        racePathFollowStep(pathState, participant, 1);
        if (func_807142D8() != 0 || flagGet(0x12, 2) != 0) {
            playerStateQueueCallback(0x4B, gCurrentActor, participant->playerIdx);
        } else {
            playerWaypointPathStartPacked(gPrimaryPlayerActor, gCurrentActor, 0, 0x4B);
        }
        actorClearNodeFlag(gCurrentActor, 2);
        racePlayEngineSfx();
    }
    if (gBossFightPhase == 5 && pathState->unk39 == 0) {
        if (participant->unk34 == 2) {
            behaviourAddSlotQueueValueB(3);
        }
        pathState->unk39 = 0x1E;
    }
    if (participant->unk35 == 0) {
        if (participant->unk34 == 1) {
            slotQueueUpdate(0xB, 1, 0);
            participant->unk35++;
        } else if (participant->unk34 == 5) {
            slotQueueCancel(0xB, 0);
            participant->unk35++;
        }
    }
    if (participant->unk34 == 1) {
        manager = participant->actor;
        managerData = manager->customState;
        if (managerData->unk1C == 8 || managerData->unk1C == 0x13) {
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x187, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        raceUpdateEngineSoundPitch(participant->route * 1.5);
    } else if (participant->unk34 < 5) {
        shakeAngle = 0;
        if (participant->route != 0) {
            bonus = raceGetHandicapSpeedBonus(participant);
            if (bonus != 0) {
                bonus = 1.5f * bonus + 1.5f;
                racePlayCheckpointSfx(pathState, 0x1E, bonus);
            }
            participant->route = 0;
        }
        if (pathState->unk39 != 0) {
            bumpX = pathState->unk39;
            if (bumpX > 10.0f) {
                shakeAngle = (bumpX - 10.0f) * 204.8f;
                bumpX = 300.0f;
                pathState->unk20 = mathSinF(shakeAngle) * bumpX;
                pathState->unk24 = mathSinF(shakeAngle * 2) * bumpX;
            } else {
                pathState->unk20 = 0.0f;
                pathState->unk24 = 0.0f;
            }
        }
        racePathFollowStep(pathState, participant, 1);
        gCurrentActor->y += 20.0f * mathSinF(shakeAngle * 0.5f);
        raceUpdateEngineSoundPitch(gCurrentActor->speedXZ);
    } else if (participant->unk34 == 5) {
        gCurrentActor->flags &= ~4;
        gCurrentActor->speedXZ = 0.0f;
        for (i = 0; i != 2; i++) {
            if (gCurrentActor->soundSlots[i] != -1) {
                sfxStopSlotSound(gCurrentActor, i);
            }
        }
    }
    if (participant->unk29 != 0) {
        raceSpawnProjectile(participant);
    }
    if (participant->unk34 < 5) {
        if (participant->unk34 == 2) {
            off = 10.0;
        } else {
            off = -200.0f;
        }
        bumpX = gCurrentActor->x;
        bumpZ = gCurrentActor->z;
        bumpY = gCurrentActor->y + off;
        gridSetNodeBounds(participant->playerIdx, bumpX, bumpY, bumpZ, 12.0f);
        bumpX += gCurrentActor->prevX;
        bumpX *= 0.5;
        bumpZ += gCurrentActor->prevZ;
        bumpZ *= 0.5;
        gridAppendPositionNode(participant->playerIdx, bumpX, bumpY, bumpZ, 12.0f);
    }
    if (gCurrentActor->flags & 4) {
        actorSpawnNodeEffectFacingCamera(1, 0xC8);
        actorSpawnNodeEffectFacingCamera(2, 0xC8);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (participant->unk34 > 0 && participant->unk34 < 5) {
        renderCallbacksRegister(raceVehicleRenderCallback, gCurrentActor, 3);
    }
}

extern u8 D_80720340[];
extern u8 sEffectSparkConfig[];


void raceProjectileBehaviorUpdate(void) {
    RaceParticipant *participant;
    RacePathState *pathState;
    s32 pad[3];
    u8 hasCollided;
    RaceAuxState *s1;
    u16 t3;

    hasCollided = 0;
    participant = ((RaceActor *)gCurrentActor)->unk174;
    pathState = ((RaceActor *)gCurrentActor)->unk178;
    s1 = ((RaceActor *)gCurrentActor)->unk17C;
    if (!(gCurrentActor->flags & 0x10)) {
        s1->unk0 = 0x78;
        gCurrentActor->flags |= 0x10;
        gCurrentActor->unk144 = 0x3C;
        participant->unk4 = 5.0f;
    }
    if ((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0) || (gActorGlobalState.bossFightPhase == 5)) {
        effectSetDepth(1);
        effectCreateAtPosition(D_80720340, 3.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xF6, 0xFF, 0x7F, 0x14, 0x32, 0.3f, 0);
        hasCollided = 1;
    }
    racePathFollowStep(pathState, participant, 0);
    gCurrentActor->y += 5.0f;
    if (s1->unk0 != 0) {
        effectSetDepth(1);
        effectCreateAtPosition(sEffectSparkConfig, 1.0f, gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z);
        if (--s1->unk0 == 0) {
            hasCollided = 1;
        }
    }
    if (hasCollided != 0) {
        raceDespawnProjectile(gCurrentActor, s1);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
