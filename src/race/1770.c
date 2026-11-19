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



// Racer actor: its participant is the customState (0x174); path cursor and aux state follow.
typedef struct RaceRacerActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RacePathState *path;
    /* 0x17C */ RaceAuxState *aux;
} RaceRacerActor;

/* Effect node actor spawned by spawnNodeSpawnById: participant, path cursor and the race pair it registers. */
typedef struct RaceNodeActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RaceParticipant *participant;
    /* 0x17C */ RacePathState *path;
    /* 0x180 */ u8 pad180[4];
    /* 0x184 */ RacePair *pair;
} RaceNodeActor;

extern Actor *gCurrentActor;

void raceInterpolateWaypointPos(RacePathState *pathState, f32 *outPos, f32 *inPos, s32 nextWaypoint, s32 nextNextWaypoint) {
    s32 padA;
    s32 padB;
    TargetVec3f *points;
    s32 i;
    f32 closerTarget[3];
    s32 padM;
    s8 laneDiff;
    TargetVec3f *curPoint;

    points = gMinecartTrackPoints[pathState->targetLane];
    curPoint = &points[pathState->waypoint];
    laneDiff = pathState->lane - pathState->targetLane;
    mathPickCloserTargetPoint3D(inPos[0], inPos[1], inPos[2], curPoint, &points[nextWaypoint], &points[nextWaypoint], &points[nextNextWaypoint], &closerTarget[0], &closerTarget[1], &closerTarget[2]);
    pathState->laneBlend += 0.01 * gCurrentActor->speedXZ;
    if (pathState->laneBlend >= 1.0f) {
        pathState->laneBlend = 1.0f;
        pathState->lane = pathState->targetLane;
    }
    pathState->laneOffset = mathSinF(pathState->laneBlend * 2048.0f) * (laneDiff * 300);
    for (i = 0; i < 3; i++) {
        outPos[i] = outPos[i] + pathState->laneBlend * (closerTarget[i] - outPos[i]);
    }
}

extern s32 gMinecartTrackCount;

void raceInitSplinePoints(void) {
    TargetVec3f *buf;
    TargetVec3f *src;
    TargetVec3f **tbl;
    TargetVec3f *next;
    s32 i;
    s32 count;

    count = (gMinecartTrackPoints[1] - gMinecartTrackPoints[0]) / 2;
    buf = heapAlloc(count * 0x24);
    tbl = heapAlloc(0x10);
    for (i = 0; i < 4; i++) {
        tbl[i] = buf + i * count;
    }
    src = gMinecartTrackPoints[0];
    buf = tbl[0];
    memcpy(buf, src, count * sizeof(TargetVec3f));
    buf = tbl[2];
    memcpy(buf, src + count, count * sizeof(TargetVec3f));
    buf = tbl[1];
    src = tbl[0];
    next = tbl[2];
    for (i = 0; i < count; i++) {
        buf[i].x = (next[i].x + src[i].x) * 0.5;
        buf[i].y = (next[i].y + src[i].y) * 0.5;
        buf[i].z = (next[i].z + src[i].z) * 0.5;
    }
    gMinecartTrackCount = 3;
    gMinecartTrackPoints = tbl;
}

extern s16 gMinigameCoinCount;
extern Actor *gSpawnedActor;

void raceInitOpponentEntities(Actor *parent) {
    RaceParticipant *parentPart;
    Actor *racer;
    RacePathState *path;
    RaceParticipant *participant;
    RacePair *pair;
    Actor *spawnedNode;
    Actor *spawnedActor;
    u8 *pad;

    parentPart = parent->customState;
    raceInitParticipantArray(parent, 2);
    actorSpawn(0x12E, 0x95);
    racer = gSpawnedActor;
    participant = racer->customState;
    raceRegisterParticipant(parent, 1, racer, participant);
    participant->lap = 0;
    participant->isCpu = 0;
    participant->actor = parent;
    participant->place = 1;
    participant->playerIdx = 0;
    path = ((RaceRacerActor *)racer)->path;
    spawnedNode = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
    path->targetActor = spawnedNode;
    pair = ((RaceNodeActor *)spawnedNode)->pair;
    pair->data = participant;
    pair->actor = racer;
    actorSpawn(0x130, 0);
    spawnedActor = gSpawnedActor;
    path->cameraActor = spawnedActor;
    participant = ((RaceNodeActor *)spawnedNode)->participant;
    raceRegisterParticipant(parent, 0, spawnedNode, participant);
    participant->lap = 0;
    participant->isCpu = 1;
    participant->actor = parent;
    participant->place = 0;
    path = ((RaceNodeActor *)spawnedNode)->path;
    path->targetActor = racer;
    path->cameraActor = spawnedActor;
    participant = spawnedActor->customState;
    participant->actor = parent;
    path = ((RaceRacerActor *)spawnedActor)->path;
    path->targetActor = racer;
    gMinigameCoinCount = 0;
    parentPart->hasCpuRival = 1;
}


void raceInitSplineAndOpponent(void) {
    raceInitSplinePoints();
    raceInitCarRaceManager();
}


void racePlayCheckpointSfx(RacePathState *pathState, u8 timer, f32 volume) {
    pathState->boostTimer = timer;
    pathState->boostAmount = volume;
    sfxPlayOnFreeSlot(0x1EB, 0x7FFF, 64.0f, 1.0f, 0, 0);
}

void raceAdvanceCheckpoint(RacePathState *pathState, RaceParticipant *participant, s32 pathLength) {
    if (pathState->waypoint + 1 != pathLength) {
        pathState->waypoint++;
    } else {
        pathState->waypoint = 0;
        if (participant != NULL) {
            participant->lap++;
        }
    }
    if (participant != NULL) {
        participant->unk3A = pathState->waypoint + 1;
    }
}

extern u8 gSparkEffectSprite[];
void *gRaceSparkEffects[4] = { 0 };
u8 gLightSlotNext = 0;
void raceApplyPositionOffset(f32 *tgt, f32 *pos) {
    s16 angle;
    f32 dist;
    f32 offsetDist;
    f32 dz;
    f32 dx;

    angle = mathAngleBetweenPointsRad(tgt[0], tgt[2], pos[0], pos[2]) * 2048.0 / 3.1415927f;
    dz = pos[2] - tgt[2];
    dx = pos[0] - tgt[0];
    dist = sqrtf((dz * dz) + (dx * dx));
    offsetDist = gCurrentActor->speedXZ * 0.03 * dist;
    gCurrentActor->x = pos[0] + (mathSinF(angle) * offsetDist);
    gCurrentActor->z = pos[2] + (mathCosF(angle) * offsetDist);
    gCurrentActor->y = gCurrentActor->y + (tgt[1] - gCurrentActor->y) * 0.8;
}


void raceUpdateOrientation(RacePathState *pathState) {
    s16 pad;
    s16 tilt;
    f32 cosYaw;
    s16 yawOffset;
    f32 sinYaw;

    yawOffset = pathState->bankAngle + pathState->laneOffset;
    tilt = mathAngleSignedDistance(0, (s16)pathState->pitchAngle);
    yawOffset &= 0xFFF;
    cosYaw = mathCosF(yawOffset);
    sinYaw = mathSinF(yawOffset);
    gCurrentActor->yaw = gCurrentActor->moveYaw + yawOffset;
    gCurrentActor->yaw &= 0xFFF;
    gCurrentActor->roll = tilt * cosYaw;
    gCurrentActor->roll += pathState->shakeRoll;
    gCurrentActor->roll &= 0xFFF;
    gCurrentActor->pitch = tilt * sinYaw;
    gCurrentActor->pitch += pathState->shakePitch;
    gCurrentActor->pitch &= 0xFFF;
}


void racePathFollowStep(RacePathState *pathState, RaceParticipant *participant, u8 spawnSparks) {
    s32 count;
    s32 next;
    s32 next2;
    TargetVec3f *points;
    TargetVec3f *cur;
    TargetVec3f *nxt;
    TargetVec3f *nxt2;
    f32 pos[3];
    f32 tgt[3];
    f32 ang;
    f32 thrust;
    f32 oldAng;
    f32 drag;
    f32 dist;
    u8 stunned;
    s16 yawDelta;
    f32 sparkX;
    f32 sparkY;
    f32 sparkZ;

    count = gMinecartTrackPoints[pathState->lane + 1] - gMinecartTrackPoints[pathState->lane];
    next = raceGetNextWaypointIndex(count, pathState->waypoint);
    next2 = raceGetNextWaypointIndex(count, next);
    points = gMinecartTrackPoints[pathState->lane];
    cur = &points[pathState->waypoint];
    nxt2 = &points[next2];
    nxt = &points[next];
    oldAng = gCurrentActor->moveYaw;
    stunned = pathState->stunTimer;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->x = cur->x;
        gCurrentActor->y = cur->y;
        gCurrentActor->z = cur->z;
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->yaw = mathAngleBetweenPointsRad(nxt->x, nxt->z, gCurrentActor->x, gCurrentActor->z) * 2048.0 / 3.1415927f;
        gCurrentActor->moveYaw = gCurrentActor->yaw;
        pathState->bankAngle = 0.0f;
    }
    if (stunned != 0) {
        thrust = 0.0f;
        pathState->stunTimer--;
        gCurrentActor->speedXZ = 0.0f;
        pathState->boostAmount = 0.0f;
        pathState->boostTimer = 0;
    } else {
        thrust = participant->throttle;
    }
    if (pathState->boostTimer != 0) {
        pathState->boostTimer--;
    } else {
        pathState->boostAmount *= 0.7;
    }
    drag = gCurrentActor->speedXZ * gCurrentActor->speedXZ * 0.0033333334f + 0.2;
    gCurrentActor->speedXZ += thrust - drag;
    if (gCurrentActor->speedXZ < 0.0f) {
        gCurrentActor->speedXZ = 0.0f;
    }
    ang = mathAngleBetweenPointsRad(nxt->x, nxt->z, cur->x, cur->z) * 2048.0 / 3.1415927f;
    pos[0] = mathSinF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ + gCurrentActor->x;
    pos[2] = mathCosF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ + gCurrentActor->z;
    pos[1] = gCurrentActor->y;
    dist = sqrtf((cur->x - nxt->x) * (cur->x - nxt->x) + (cur->z - nxt->z) * (cur->z - nxt->z));
    pathState->pitchAngle = mathAngleEaseToward(pathState->pitchAngle, mathAtan2(cur->y - nxt->y, dist) * 2048.0 / 3.1415927f, 3.0f);
    if (gCurrentActor->speedXZ > 0.001) {
        gCurrentActor->moveYaw = mathAngleEaseToward(gCurrentActor->moveYaw, ang, 50.0f / gCurrentActor->speedXZ);
    }
    if (mathPickCloserTargetPoint3D(pos[0], pos[1], pos[2], cur, nxt, nxt, nxt2, &tgt[0], &tgt[1], &tgt[2]) != 0) {
        raceAdvanceCheckpoint(pathState, participant, count);
        next = raceGetNextWaypointIndex(count, pathState->waypoint);
        next2 = raceGetNextWaypointIndex(count, next);
        cur = &points[pathState->waypoint];
        nxt2 = &points[next2];
    }
    if (pathState->lane != pathState->targetLane) {
        raceInterpolateWaypointPos(pathState, tgt, pos, next, next2);
    } else if (pathState->unk4 != 0) {
        pathState->unk4--;
    }
    raceApplyPositionOffset(tgt, pos);
    yawDelta = mathAngleSignedDistance(gCurrentActor->moveYaw, (s16)oldAng);
    pathState->bankVelocity += -0.04f * gCurrentActor->speedXZ * yawDelta * mathCosF(pathState->bankAngle);
    pathState->bankVelocity -= 10.0f * gCurrentActor->speedXZ * mathSinF(pathState->bankAngle);
    pathState->bankVelocity *= 0.7f;
    pathState->bankAngle += pathState->bankVelocity;
    raceUpdateOrientation(pathState);
    if (spawnSparks != 0) {
        if ((randomLcgNext() & 0xFF) < gCurrentActor->speedXZ * 0.3 && pathState->lane == pathState->targetLane) {
            mathPickCloserTargetPoint3D(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, cur, &points[next], &points[next], nxt2, &sparkX, &sparkY, &sparkZ);
            effectSetSpeed((s32)gCurrentActor);
            effectSetCallback(timedLightOrbitUpdate);
            gRaceSparkEffects[gLightSlotNext] = effectCreateAtPosition(gSparkEffectSprite, 0.4f, sparkX, sparkY, sparkZ);
            gLightSlotNext++;
            gLightSlotNext = gLightSlotNext % 4;
            sfxPlayAtPositionPooled(sparkX, sparkY, sparkZ, 0x8A, 0x96, 0x7F, 0x14, 0x50, 0.3f, 0);
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

    if (participant->projectile == NULL && participant->projectileAmmo != 0) {
        actorPath = ((RaceRacerActor *)gCurrentActor)->path;
        participant->projectileAmmo--;
        actorSpawn(0x131, 0x96);
        projPath = ((RaceRacerActor *)gSpawnedActor)->path;
        projAux = ((RaceRacerActor *)gSpawnedActor)->aux;
        projAux->owner = gCurrentActor;
        projAux->target = raceFindNearestParticipant(gCurrentActor);
        participant->projectile = gSpawnedActor;
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
    participant->fireRequested = 0;
}


void racePlayEngineSfx(void) {
    sfxPlayActorSound(gCurrentActor, 0x12D, 0, 1, 0, 0xFF, 1.0f, 0);
    sfxPlayActorSound(gCurrentActor, 0x12E, 0, 1, 1, 0xFF, 1.0f, 0);
}

extern s16 gSfxSourceVoice[];
extern f32 gSfxVoicePitch[];
extern f32 D_80770BC0[];

void raceUpdateEngineSoundPitch(f32 moveSpeed) {
    s32 pad;
    s16 idx;

    idx = gSfxSourceVoice[gCurrentActor->soundSlots[0]];
    gSfxVoicePitch[idx] = moveSpeed / 20.0 + 1.0;
    D_80770BC0[idx] = 1.0f;
    idx = gSfxSourceVoice[gCurrentActor->soundSlots[1]];
    gCurrentActor->unk74 = moveSpeed / 20.0;
    if (gCurrentActor->unk74 > 1.0) {
        gCurrentActor->unk74 = 1.0f;
    }
    if (gCurrentActor->unk74 < 0.0) {
        gCurrentActor->unk74 = 0.0f;
    }
    if (D_80770BC0[idx] == 0.0f) {
        gSfxVoicePitch[idx] = ((u32)randomLcgNext() / 4294967295.0 * 0.05 + 0.975) * (0.2 + moveSpeed / 15.0);
        D_80770BC0[idx] = 3.0f;
    }
}


void raceVehicleRenderCallback(void *glist, Actor *actor) {
    raceRenderHud(glist, actor, actor->customState);
}

extern Actor *gPrimaryPlayerActor;

void raceVehicleBehaviorUpdate(void) {
    s32 len;
    RacePathState *pathState;
    RaceParticipant *participant;
    s16 shakeAngle;
    f32 nodeYOffset;
    f32 bonus;
    Actor *manager;
    RaceParticipant *managerData;
    s32 i;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;

    participant = gCurrentActor->customState;
    pathState = ((RaceRacerActor *)gCurrentActor)->path;
    if (!(gCurrentActor->flags & 0x10)) {
        len = gMinecartTrackPoints[pathState->lane + 1] - gMinecartTrackPoints[pathState->lane];
        participant->projectileAmmo = 3;
        gCurrentActor->unk144 = 0x3C;
        pathState->waypoint = raceGetPrevWaypointIndex(len, 0);
        racePathFollowStep(pathState, participant, 1);
        if (menuIsTransitionType3Or4() != 0 || flagGet(0x12, 2) != 0) {
            playerStateQueueCallback(0x4B, gCurrentActor, participant->playerIdx);
        } else {
            playerWaypointPathStartPacked(gPrimaryPlayerActor, gCurrentActor, 0, 0x4B);
        }
        actorClearNodeFlag(gCurrentActor, 2);
        racePlayEngineSfx();
    }
    if (gActorGlobalState.bossFightPhase == 5 && pathState->stunTimer == 0) {
        if (participant->raceStatus == 2) {
            behaviourAddSlotQueueValueB(3);
        }
        pathState->stunTimer = 0x1E;
    }
    if (participant->unk35 == 0) {
        if (participant->raceStatus == 1) {
            slotQueueUpdate(0xB, 1, 0);
            participant->unk35++;
        } else if (participant->raceStatus == 5) {
            slotQueueCancel(0xB, 0);
            participant->unk35++;
        }
    }
    if (participant->raceStatus == 1) {
        manager = participant->actor;
        managerData = manager->customState;
        if (managerData->unk1C == 8 || managerData->unk1C == 0x13) {
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x187, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        raceUpdateEngineSoundPitch(participant->route * 1.5);
    } else if (participant->raceStatus < 5) {
        shakeAngle = 0;
        if (participant->route != 0) {
            bonus = raceGetHandicapSpeedBonus(participant);
            if (bonus != 0) {
                bonus = 1.5f * bonus + 1.5f;
                racePlayCheckpointSfx(pathState, 0x1E, bonus);
            }
            participant->route = 0;
        }
        if (pathState->stunTimer != 0) {
            if (pathState->stunTimer > 10.0f) {
                shakeAngle = (pathState->stunTimer - 10.0f) * 204.8f;
                pathState->shakeRoll = mathSinF(shakeAngle) * 300.0f;
                pathState->shakePitch = mathSinF(shakeAngle * 2) * 300.0f;
            } else {
                pathState->shakeRoll = 0.0f;
                pathState->shakePitch = 0.0f;
            }
        }
        racePathFollowStep(pathState, participant, 1);
        gCurrentActor->y += 20.0f * mathSinF(shakeAngle * 0.5f);
        raceUpdateEngineSoundPitch(gCurrentActor->speedXZ);
    } else if (participant->raceStatus == 5) {
        gCurrentActor->flags &= ~4;
        gCurrentActor->speedXZ = 0.0f;
        for (i = 0; i < 2; i++) {
            if (gCurrentActor->soundSlots[i] != -1) {
                sfxStopSlotSound(gCurrentActor, i);
            }
        }
    }
    if (participant->fireRequested != 0) {
        raceSpawnProjectile(participant);
    }
    if (participant->raceStatus < 5) {
        if (participant->raceStatus == 2) {
            nodeYOffset = 10.0;
        } else {
            nodeYOffset = -200.0f;
        }
        nodeX = gCurrentActor->x;
        nodeZ = gCurrentActor->z;
        nodeY = gCurrentActor->y + nodeYOffset;
        gridSetNodeBounds(participant->playerIdx, nodeX, nodeY, nodeZ, 12.0f);
        nodeX += gCurrentActor->prevX;
        nodeX *= 0.5;
        nodeZ += gCurrentActor->prevZ;
        nodeZ *= 0.5;
        gridAppendPositionNode(participant->playerIdx, nodeX, nodeY, nodeZ, 12.0f);
    }
    if (gCurrentActor->flags & 4) {
        actorSpawnNodeEffectFacingCamera(1, 0xC8);
        actorSpawnNodeEffectFacingCamera(2, 0xC8);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (participant->raceStatus > 0 && participant->raceStatus < 5) {
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
    RaceAuxState *aux;
    u16 pad2;

    hasCollided = 0;
    participant = gCurrentActor->customState;
    pathState = ((RaceRacerActor *)gCurrentActor)->path;
    aux = ((RaceRacerActor *)gCurrentActor)->aux;
    if (!(gCurrentActor->flags & 0x10)) {
        aux->lifetime = 0x78;
        gCurrentActor->flags |= 0x10;
        gCurrentActor->unk144 = 0x3C;
        participant->throttle = 5.0f;
    }
    if ((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0) || (gActorGlobalState.bossFightPhase == 5)) {
        effectSetDepth(1);
        effectCreateAtPosition(D_80720340, 3.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xF6, 0xFF, 0x7F, 0x14, 0x32, 0.3f, 0);
        hasCollided = 1;
    }
    racePathFollowStep(pathState, participant, 0);
    gCurrentActor->y += 5.0f;
    if (aux->lifetime != 0) {
        effectSetDepth(1);
        effectCreateAtPosition(sEffectSparkConfig, 1.0f, gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z);
        if (--aux->lifetime == 0) {
            hasCollided = 1;
        }
    }
    if (hasCollided != 0) {
        raceDespawnProjectile(gCurrentActor, aux);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
