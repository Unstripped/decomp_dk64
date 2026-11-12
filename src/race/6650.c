#include "common.h"
#include "actor.h"
#include "race.h"
#include "sched.h"
#include "proto/global/112080.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/ACDC0.h"
#include "proto/global/CEAE0.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"
#include "proto/race/1770.h"
#include "proto/race/36B0.h"
#include "proto/race/6650.h"
#include "proto/race/7BD0.h"
#include "proto/race/A960.h"

extern u8 gPlayerCount;
extern Actor *gSpawnedActor;
extern Actor *gCurrentActor;
extern PlayerStruct *gPlayerSlots;
extern RaceCurvePoint D_8002FC70[];
extern RaceVec3f D_8002FCA0;
extern s16 D_80750AC8;

extern s32 gGlobalOverlayFlags;

void playerStateQueueCallback(); // FAKE: callee prototype steer
s32 sfxStopSlotSound(Actor *, u8); // FAKE: callee prototype steer
void actorSpawnNodeEffectFacingCamera(s32, u8);
void actorInitFromSpawnPoint(void *, void *);

void raceInitParticipants(Actor *manager) {
    RaceParticipant *managerData;
    RaceParticipant *racerState;
    Actor *racerActor;
    s32 participantIndex;
    s32 i;
    s32 numParticipants;

    numParticipants = gPlayerCount;
    participantIndex = 0;
    managerData = manager->customState;
    if (numParticipants == 1) {
        numParticipants++;
    }
    raceInitParticipantArray(manager, numParticipants);
    for (i = 0; i < gPlayerCount; i++) {
        actorSpawn(0x142, 0x95);
        racerActor = gSpawnedActor;
        racerState = racerActor->customState;
        racerState->unk27 = 0;
        raceRegisterParticipant(manager, participantIndex, racerActor, racerState);
        participantIndex++;
        racerState->playerIdx = i;
    }
    i = 0;
    if (gPlayerCount == 1) {
        racerActor = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        racerState = ((RaceComponentActor *)racerActor)->participant;
        racerState->unk27 = 1;
        raceRegisterParticipant(manager, participantIndex, racerActor, racerState);
        raceGetParticipantPair(manager, 0, &((RaceComponentActor *)racerActor)->target->actor, &((RaceComponentActor *)racerActor)->target->participant);
        managerData->unk25 = 1;
    } else {
        managerData->unk25 = 0;
    }
    if (numParticipants > 0) {
        do {
            raceGetParticipantPair(manager, i, &racerActor, &racerState);
            racerState->unk36 = i;
            racerState->actor = manager;
            actorInitFromSpawnPoint(racerActor, racerState);
            i++;
        } while (i != numParticipants);
    }
    managerData->route = 0;
}

void raceUpdateRacerMotion(RaceParticipant *racerState) {
    f32 velX;
    f32 velZ;
    f32 forwardAccel;
    u8 onGround;
    s16 thrustYaw;
    s16 targetRoll;
    s16 targetPitch;
    f32 value;
    f32 friction;
    f32 steerAmount;
    f32 factor;
    s32 steerSign;
    s16 signedDist;
    s16 pitchAngle;
    s16 yawDelta;
    s16 airPitch;
    s16 airYaw;
    f32 tiltScale;

    onGround = gCurrentActor->contactFlags & 1;
    thrustYaw = gCurrentActor->yaw;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk144 = 0x3C;
        gCurrentActor->flags |= 0x10400;
        gCurrentActor->state = 0;
        gCurrentActor->unk155 = 0;
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->accelY = -20.0f;
        gCurrentActor->terminalSpeedY = -900.0f;
        gCurrentActor->unkF8 = 0x12C;
    }
    velX = mathSinF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ;
    velZ = mathCosF(gCurrentActor->moveYaw) * gCurrentActor->speedXZ;
    if (racerState->reverseThrust != 0) {
        thrustYaw = thrustYaw + 0x800;
        thrustYaw = thrustYaw & 0xFFF;
        racerState->unk4 = (f32)((f64)racerState->unk4 * 0.85);
    }
    if (onGround != 0) {
        factor = (f32)((f64)(racerState->unk8 * gCurrentActor->speedXZ) * 0.2);
        if (!(factor > 1.0f)) {
            factor = 1.0f;
        }
        forwardAccel = (f32)((f64)(racerState->unk4 * 35.0f) + ((f64)gCurrentActor->speedXZ * 0.13));
        friction = (f32)((f64)(gCurrentActor->speedXZ * gCurrentActor->speedXZ * 0.00025f) + (27.0 + (f64)factor));
    } else {
        forwardAccel = racerState->unk4 * 2;
        friction = (gCurrentActor->speedXZ * gCurrentActor->speedXZ * 0.00002f) + 2;
    }
    velX += mathSinF(thrustYaw) * forwardAccel;
    velZ += mathCosF(thrustYaw) * forwardAccel;
    gCurrentActor->speedXZ = sqrtf((velX * velX) + (velZ * velZ));
    gCurrentActor->moveYaw = (s16)(s32)(mathAtan2(velX, velZ) * 651.8986f);
    if (onGround) {
        pitchAngle = 0x400 - gCurrentActor->floorSlopePitch;
        signedDist = mathAngleSignedDistance(gCurrentActor->floorSlopeYaw, gCurrentActor->yaw);
        tiltScale = (f32)pitchAngle;
        targetRoll = (s16)(s32)(mathCosF(signedDist) * tiltScale);
        factor = mathSinF(signedDist) * tiltScale;
        targetRoll = targetRoll & 0xFFF;
        targetPitch = (s32)factor;
        targetPitch = targetPitch & 0xFFF;
    } else {
        airPitch = mathAngleFromVector2D(gCurrentActor->speedXZ, gCurrentActor->speedY);
        airYaw = gCurrentActor->moveYaw;
        if (airPitch >= 0x800) {
            airPitch = 0xFFF - airPitch;
            airYaw = airYaw + 0x800;
            airYaw = airYaw & 0xFFF;
        }
        yawDelta = mathAngleSignedDistance(airYaw, gCurrentActor->yaw);
        tiltScale = (f32)airPitch;
        targetRoll = (s16)(s32)(mathCosF(yawDelta) * tiltScale);
        targetPitch = (s32)(mathSinF(yawDelta) * tiltScale);
        targetRoll = targetRoll & 0xFFF;
        targetPitch = targetPitch & 0xFFF;
    }
    value = racerState->unk8;
    steerAmount = racerState->unk10 * racerState->unkC;
    if (value > 0) {
        if (steerAmount > 0.0f) {
            factor = steerAmount;
        } else {
            factor = -steerAmount;
        }
        if (factor > 0.1f) {
            if (steerAmount >= 0.0f) {
                steerSign = 1;
            } else {
                steerSign = -1;
            }
            steerAmount += 2.0f * (f32)steerSign * value;
        }
    }
    gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, targetRoll, 4.0f);
    gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, targetPitch, 4.0f);
    gCurrentActor->speedXZ = gCurrentActor->speedXZ - friction;
    if (gCurrentActor->speedXZ < 0.0f) {
        gCurrentActor->speedXZ = 0.0f;
    }
    if (racerState->reverseThrust != 0) {
        gCurrentActor->speedXZ = (gCurrentActor->speedXZ < 100.0f) ? gCurrentActor->speedXZ : 100.0f;
    }
    factor = gCurrentActor->speedXZ - gCurrentActor->prevSpeedXZ;
    if (factor < 0.0f) {
        factor = 0.0f;
    }
    gCurrentActor->yaw = (s16)(s32)((f64)gCurrentActor->yaw + ((f64)(steerAmount * -40.0f) * (1.0 + ((f64)factor * 0.05))));
    gCurrentActor->yaw = gCurrentActor->yaw & 0xFFF;
    gCurrentActor->speedY = gCurrentActor->speedY + gCurrentActor->accelY;
    if (gCurrentActor->speedY < gCurrentActor->terminalSpeedY) {
        gCurrentActor->speedY = gCurrentActor->terminalSpeedY;
    }
    airYaw = gCurrentActor->moveYaw;
    actorStepPhysics(gCurrentActor, airYaw, airYaw);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (gGlobalOverlayFlags & 0x2000) {
        raceUpdateLapAndWaypointTracker(racerState);
    }
}


void raceParticleRenderCallback(Gfx *glist, Actor *actor) {
    actorDrawAnimatedEffect(raceRenderHud(glist, actor, actor->customState), actor);
}

void raceParticipantMotionUpdate(void) {
    RaceParticipant *racerState;
    s32 i;
    s32 playerIdx;
    u8 colorMode;
    u32 flags;

    racerState = gCurrentActor->customState;
    playerIdx = racerState->playerIdx;
    colorMode = 0xB4;
    if (!(gCurrentActor->flags & 0x10)) {
        playerStateQueueCallback(0x4D, gCurrentActor, playerIdx);
        gCurrentActor->unk144 = 0x3C;
        gCurrentActor->flags &= 0xFFFDFFFF;
        for (i = 0; i < 3; i++) {
            gCurrentActor->sub4->scale[i] *= 0.3;
        }
        racerState->unk44 = 5;
        actorOrNodeFlags(gCurrentActor, 2, 8);
        racePlayEngineSfx();
    }
    switch (racerState->unk34) {
        case 1:
            if (racerState->unk35 == 0) {
                racerState->unk35++;
                slotQueueUpdate(0xB, 1, 0);
            }
        case 0:
        case 2:
        case 3:
        case 4:
            raceUpdateEngineSoundPitch(gCurrentActor->speedXZ * 0.0307692308f);
            raceUpdateRacerMotion(racerState);
            break;
        case 5:
            if (racerState->unk35 == 0) {
                racerState->unk35++;
                slotQueueCancel(0xB, 0);
                gCurrentActor->flags &= ~4;
                gCurrentActor->speedXZ = 0.0f;
                for (i = 0; i < 2; i++) {
                    if (gCurrentActor->soundSlots[i] != -1) {
                        sfxStopSlotSound(gCurrentActor, i);
                    }
                }
            }
            break;
    }
    flags = gCurrentActor->flags;
    if (racerState->unk4 <= 0 || racerState->unk8 > 0) {
        colorMode = 0xF0;
    }
    if (flags & 4) {
        actorSpawnNodeEffectFacingCamera(1, colorMode);
        actorSpawnNodeEffectFacingCamera(2, colorMode);
    }
    if (racerState->unk34 > 0 && racerState->unk34 < 5) {
        gridSetNodeBounds(racerState->playerIdx, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, gCurrentActor->sub4->scaleY / 0.15 * 40.0);
        renderCallbacksRegister(raceParticleRenderCallback, gCurrentActor, 3);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void raceSteerTowardTargetWaypoint(RaceParticipant *racerState, RaceTarget *target) {
    f32 steerAngle;
    f32 waypointRadius;
    f32 angleDelta;
    f32 distToWaypoint;
    f32 waypointThreshold[1]; // FAKE: one-element array keeps the threshold in a stack slot
    f32 dx;
    f32 dz;
    f32 targetVel;
    f32 work;
    RaceParticipant *managerData;
    RaceRoute *route;
    f32 targetSpeed;
    ZoneEntry *waypoint;
    u8 idx;
    Actor *manager;

    manager = racerState->actor;
    managerData = manager->customState;
    route = raceGetRoute(managerData->route);
    targetSpeed = raceGetPathDistanceBetweenTrackers(route, racerState, target->participant);
    idx = gBehaviourAnimState->path[gBehaviourWorkState->unk25][0];
    waypoint = &D_807FDCA0->entries[idx];
    dx = (f32)waypoint->x - gCurrentActor->x;
    dz = (f32)waypoint->z - gCurrentActor->z;
    distToWaypoint = sqrtf((dx * dx) + (dz * dz));
    waypoint = &D_807FDCA0->entries[idx];
    if (distToWaypoint < (f32)waypoint->radius) {
        if (gCurrentActor->x) { // FAKE: empty guard steers float regalloc
        }
        gBehaviourWorkState->unk25++;
        gBehaviourWorkState->unk25 = gBehaviourWorkState->unk25 % gBehaviourExtraState->pathCount;
    }
    waypoint = &D_807FDCA0->entries[idx];
    work = mathAngleDiscrete((f32)waypoint->x, (f32)waypoint->z, gCurrentActor->x, gCurrentActor->z, distToWaypoint);
    angleDelta = mathAngleSignedDistance((s16)work, gCurrentActor->yaw);

    work = distToWaypoint; // FAKE: the angle temp reused for a distance copy steers float regalloc
    steerAngle = angleDelta;
    waypointRadius = (u32)D_807FDCA0->entries[idx].radius;
    waypointThreshold[0] = waypointRadius * 1.2f;
    if (waypointRadius) { // FAKE: empty guard steers float regalloc
    }
    if (work < waypointThreshold[0]) {
        work = work - waypointRadius;
        dz = waypointThreshold[0] - waypointRadius;
        steerAngle = angleDelta * (1.0 + ((1.0f - (work / dz)) * 1.5 * (2.0f * racerState->unk4)));
    }
    racerState->unkC += ((steerAngle * 0.0033333334f) - racerState->unkC) * 0.5f;
    if (racerState->unk34 >= 2 && racerState->unk34 < 5) {
        if (target->curveMode != 0 && raceGetProgressPercent(route, racerState, managerData) > 0.75) {
            raceSetPiecewiseCurveMode(target, 0, D_8002FC70, &D_8002FCA0);
        }
        targetVel = raceEvaluateCurveTargetSpeed(target, targetSpeed, D_8002FC70, &D_8002FCA0);
        gCurrentActor->speedXZ = (gCurrentActor->speedXZ < 650.0f) ? gCurrentActor->speedXZ : 650.0f;
        racerState->unk4 = targetVel;
    }
}


void raceUpdateCountdownState(RaceParticipant *racerState) {
    switch (racerState->unk35) {
        case 0:
            if (gCurrentActor->flags & 0x2000000) {
                racerState->unk35++;
            }
            break;
        case 1:
            if (!(gCurrentActor->flags & 0x2000000)) {
                camResumePath();
                racerState->unk35++;
            }
            break;
        case 2:
            if (currentActorTestClearFlag()) {
                currentActorClearFlag();
                racerState->unk35++;
            }
            break;
    }
    if (racerState->unk35 < 3) {
        raceSetIntroCutscenePhase(racerState->actor);
    } else {
        raceClearIntroCutscenePhase(racerState->actor);
    }
}

void racePlayIntroCameraCutscene(RaceParticipant *racerState, RaceTarget *target) {
    if (racerState->unk35 == 0) {
        RaceParticipant *chased = target->participant;
        Actor *player = gPlayerSlots[chased->playerIdx].actor;
        PlayerState *playerState = player->customState;
        camSetTargetScaled(playerState->camActor, target->actor, 4, 0x800, 0xBE, 0, 0x4A, 0xAE, 0x2D, 0, 0.2f);
        racerState->unk35++;
    }
    racePlayTireScreechSfx();
}

extern s32 D_8002FCAC[];

s32 raceGetFinishCameraId(RaceParticipant *racerState, RaceParticipant *chased) {
    return D_8002FCAC[raceCheckLapCompletionThreshold(racerState, chased, 10)];
}



void raceFinishCameraCutscene(RaceParticipant *racerState, RaceParticipant *chased) {
    if (racerState->unk35 == 0) {
        if (flagGet(0x145, 0) == 0) {
            camStartPath(gCurrentActor, 1, 1);
            currentActorClearFlag();
        } else {
            mapCheckAutoTransition();
        }
        racerState->unk35++;
    }
}

void raceHandlePostRaceFinished(RaceParticipant *racerState, RaceParticipant *chased) {
    s32 i;
    s32 cameraId;

    switch (racerState->unk35) {
        case 0:
            if (flagGet(0x145, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                gCurrentActor->pitch = 0;
                gCurrentActor->roll = 0;
                for (i = 0; i < 2; i++) {
                    if (gCurrentActor->soundSlots[i] != -1) {
                        sfxStopSlotSound(gCurrentActor, i);
                    }
                }
            }
            racerState->unk35++;
            break;
        case 1:
            if (currentActorTestClearFlag()) {
                currentActorClearFlag();
                resQueueAttachActor(gCurrentActor, 0x22, raceGetFinishCameraId(racerState, chased));
                racerState->unk35++;
            }
            break;
        case 2:
            if (!(gCurrentActor->flags & 0x2000000)) {
                camResumePath();
                racerState->unk35++;
            }
            break;
        case 3:
            if (currentActorTestClearFlag()) {
                cameraId = raceGetFinishCameraId(racerState, chased);
                currentActorClearFlag();
                if (cameraId == 0) {
                    csModelStateSetFirstByte(1, 0xA);
                    flagSet(0x145, 1, 0);
                } else {
                    hudSpawnTextScreen(1);
                    racerState->unk35++;
                }
                racerState->unk35++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag()) {
                currentActorClearFlag();
                mapCheckAutoTransition();
                racerState->unk35++;
            }
            break;
    }
}

void raceOpponentRacerMotionUpdate(void) {
    RaceParticipant *racerState;
    RaceTarget *target;
    s32 i;

    racerState = ((RaceComponentActor *)gCurrentActor)->participant;
    target = ((RaceComponentActor *)gCurrentActor)->target;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        target->unk10 = 1;
        raceSetPiecewiseCurveMode(target, 5, D_8002FC70, &D_8002FCA0);
        gCurrentActor->unk144 = 0x3C;
        gCurrentActor->flags &= 0xFFFDFFFE;
        racerState->unk10 = 1.0f;
        for (i = 0; i < 3; i++) {
            gCurrentActor->sub4->scale[i] *= 0.3;
        }
        if (flagGet(0x38, 2) == 0 && flagGet(0x145, 0) == 0) {
            camStartPath(gCurrentActor, 0, 1);
            currentActorClearFlag();
            flagSet(0x38, 1, 2);
        } else {
            racerState->unk35 = 3;
        }
        D_80750AC8 = 0xA;
        actorOrNodeFlags(gCurrentActor, 4, 8);
    }
    switch (racerState->unk34) {
        case 0:
            raceUpdateCountdownState(racerState);
            break;
        case 1:
            racePlayIntroCameraCutscene(racerState, target);
            break;
        case 4:
            raceFinishCameraCutscene(racerState, target->participant);
            break;
        case 5:
            raceHandlePostRaceFinished(racerState, target->participant);
            break;
    }
    if (racerState->unk34 < 5) {
        raceHandleRacerCollision(target);
        raceSteerTowardTargetWaypoint(racerState, target);
        raceUpdateRacerMotion(racerState);
        raceUpdateOpponentEnginePitch(gCurrentActor->speedXZ * 0.0307692308f);
    } else {
        gCurrentActor->speedXZ = 0.0f;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

