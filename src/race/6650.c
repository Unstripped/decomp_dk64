#include "common.h"
#include "actor.h"
#include "race.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"
#include "proto/race/1770.h"
#include "proto/race/36B0.h"
#include "proto/race/6650.h"
#include "proto/race/7BD0.h"
#include "proto/race/A960.h"

typedef struct Struct_sp58 {
    char pad0[0x4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    char pad14[0x20 - 0x14];
    s32 unk20;
    char pad24[0x27 - 0x24];
    u8 unk27;
    u8 unk28;
    char pad29[0x30 - 0x29];
    void *unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    char pad37[0x44 - 0x37];
    u8 unk44;
} Struct_sp58;

extern u8 gPlayerCount;
extern Actor *gSpawnedActor;
typedef struct {
    char pad[0x34];
    f32 unk34[3];
} Actor_BB40_Sub4;

typedef struct {
    void *pad0;
    void *unk4;
    char pad8[0x10 - 0x8];
    u8 unk10;
} Struct_sp20;

// Actor plus its component pointers (0x174 on); unk4 keeps a file-local type.
typedef struct Actor_BB40 {
    /* 0x000 */ u8 pad0[0x4];
    /* 0x004 */ Actor_BB40_Sub4 * unk4;
    /* 0x008 */ u8 pad8[0x16C];
    /* 0x174 */ Struct_sp58 * unk174;
    /* 0x178 */ Struct_sp58 * unk178;
    /* 0x17C */ Struct_sp20 * unk17C;
} Actor_BB40;
extern Actor *gCurrentActor;

void behaviourFrameBegin(void);
void actorOrNodeFlags(Actor *, s32, u8);
typedef struct Struct_8002B180_Arg1 {
    char pad[0x4];
    void *unk4;
    char pad8[0xF - 0x8];
    u8 unkF;
} Struct_8002B180_Arg1;
extern void *D_8002FC70;
extern void *D_8002FCA0;
extern s16 D_80750AC8;

void playerStateQueueCallback(); // FAKE: callee prototype steer
s32 sfxStopSlotSound(Actor *, u8); // FAKE: callee prototype steer
void resQueueAttachActor(Actor *, s32, u8);
void csModelStateSetFirstByte(s16, s16);
void hudSpawnTextScreen(u8);
void actorSpawnNodeEffectFacingCamera(s32, u8);
void renderCallbacksRegister(void *, void *, u8);



s16 mathAngleDiscrete(f32, f32, f32, f32, f32);
s16 mathAngleSignedDistance(s16, s16);
extern s32 gGlobalOverlayFlags;
f32 mathSinF(s16);
f32 mathCosF(s16);
s16 mathAngleFromVector2D(f32, f32);
s16 mathAngleEaseToward(s16, s16, f32, s16); // FAKE: callee prototype steer
void actorStepPhysics(Actor *, s16, s16);
void actorApplyVelocity(Actor *);
void actorUpdateFloorContactAndTilt(Actor *, f32);
typedef struct {
    char pad[0x104];
    void *unk104;
} Struct_174;

typedef struct {
    char pad[0x174];
    Struct_174 *unk174;
} Struct_PlayerActor;

typedef struct {
    char pad[0x4];
    Struct_PlayerActor *unk4;
    char pad8[0x2F0 - 0x8];
} Struct_Player;

extern Struct_Player *gPlayerSlots;

typedef struct {
    char pad[0x28];
    u8 unk28;
} Struct_8002B610_Sub;

typedef struct Struct_8002B610_Arg1 {
    void *unk0;
    Struct_8002B610_Sub *unk4;
} Struct_8002B610_Arg1;

void camSetTargetScaled(struct CamActor *, struct CamActor *, u8, s16, s16, s16, s16, s16, s16, s16, f32);

s32 currentActorTestClearFlag(void);
void currentActorClearFlag(void);
void camResumePath(void);

s32 actorSpawn(s32, s32);
Actor *spawnNodeSpawnById(s16, s16, s16, s16, s16, s16, s16);
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

void raceUpdateRacerMotion(Struct_sp58 *racerState) {
    f32 velX;
    f32 velZ;
    f32 forwardAccel;
    u8 onGround;
    s16 a1;
    s16 targetTilt;
    s16 a3;
    f32 fv1;
    f32 friction;
    f32 steerAmount;
    f32 fv0;
    s32 v0;
    s16 signedDist;
    s16 pitchAngle;
    s16 yawDelta;
    s16 v1;
    s16 a0;
    f32 tiltScale;

    onGround = gCurrentActor->contactFlags & 1;
    a1 = gCurrentActor->yaw;
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
    if (racerState->unk20 != 0) {
        a1 = a1 + 0x800;
        a1 = a1 & 0xFFF;
        racerState->unk4 = (f32)((f64)racerState->unk4 * 0.85);
    }
    if (onGround != 0) {
        fv0 = (f32)((f64)(racerState->unk8 * gCurrentActor->speedXZ) * 0.2);
        if (!(fv0 > 1.0f)) {
            fv0 = 1.0f;
        }
        forwardAccel = (f32)((f64)(racerState->unk4 * 35.0f) + ((f64)gCurrentActor->speedXZ * 0.13));
        friction = (f32)((f64)(gCurrentActor->speedXZ * gCurrentActor->speedXZ * 0.00025f) + (27.0 + (f64)fv0));
    } else {
        forwardAccel = racerState->unk4 * 2;
        friction = (gCurrentActor->speedXZ * gCurrentActor->speedXZ * 0.00002f) + 2;
    }
    velX += mathSinF(a1) * forwardAccel;
    velZ += mathCosF(a1) * forwardAccel;
    gCurrentActor->speedXZ = sqrtf((velX * velX) + (velZ * velZ));
    gCurrentActor->moveYaw = (s16)(s32)(mathAtan2(velX, velZ) * 651.8986f);
    if (onGround) {
        pitchAngle = 0x400 - gCurrentActor->floorSlopePitch;
        signedDist = mathAngleSignedDistance(gCurrentActor->floorSlopeYaw, gCurrentActor->yaw);
        tiltScale = (f32)pitchAngle;
        targetTilt = (s16)(s32)(mathCosF(signedDist) * tiltScale);
        fv0 = mathSinF(signedDist) * tiltScale;
        targetTilt = targetTilt & 0xFFF;
        a3 = (s32)fv0;
        a3 = a3 & 0xFFF;
    } else {
        v1 = mathAngleFromVector2D(gCurrentActor->speedXZ, gCurrentActor->speedY);
        a0 = gCurrentActor->moveYaw;
        if (v1 >= 0x800) {
            v1 = 0xFFF - v1;
            a0 = a0 + 0x800;
            a0 = a0 & 0xFFF;
        }
        yawDelta = mathAngleSignedDistance(a0, gCurrentActor->yaw);
        tiltScale = (f32)v1;
        targetTilt = (s16)(s32)(mathCosF(yawDelta) * tiltScale);
        a3 = (s32)(mathSinF(yawDelta) * tiltScale);
        targetTilt = targetTilt & 0xFFF;
        a3 = a3 & 0xFFF;
    }
    fv1 = racerState->unk8;
    steerAmount = racerState->unk10 * racerState->unkC;
    if (fv1 > 0) {
        if (steerAmount > 0.0f) {
            fv0 = steerAmount;
        } else {
            fv0 = -steerAmount;
        }
        if (fv0 > 0.1f) {
            if (steerAmount >= 0.0f) {
                v0 = 1;
            } else {
                v0 = -1;
            }
            steerAmount += 2.0f * (f32)v0 * fv1;
        }
    }
    gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, targetTilt, 4.0f, a3);
    gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, (s32)a3, 4.0f, a3);
    gCurrentActor->speedXZ = gCurrentActor->speedXZ - friction;
    fv1 = gCurrentActor->speedXZ;
    if (fv1 < 0.0f) {
        gCurrentActor->speedXZ = 0.0f;
        fv1 = gCurrentActor->speedXZ;
    }
    if (racerState->unk20 != 0) {
        if (fv1 < 100.0f) {
            gCurrentActor->speedXZ = fv1;
            fv1 = gCurrentActor->speedXZ;
        } else {
            gCurrentActor->speedXZ = 100.0f;
            fv1 = gCurrentActor->speedXZ;
        }
    }
    fv0 = fv1 - gCurrentActor->prevSpeedXZ;
    if (fv0 < 0.0f) {
        fv0 = 0.0f;
    }
    gCurrentActor->yaw = (s16)(s32)((f64)gCurrentActor->yaw + ((f64)(steerAmount * -40.0f) * (1.0 + ((f64)fv0 * 0.05))));
    gCurrentActor->yaw = gCurrentActor->yaw & 0xFFF;
    gCurrentActor->speedY = gCurrentActor->speedY + gCurrentActor->accelY;
    fv1 = gCurrentActor->terminalSpeedY;
    if (gCurrentActor->speedY < fv1) {
        gCurrentActor->speedY = fv1;
    }
    a0 = gCurrentActor->moveYaw;
    actorStepPhysics(gCurrentActor, a0, a0);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (gGlobalOverlayFlags & 0x2000) {
        raceUpdateLapAndWaypointTracker(racerState);
    }
}

Gfx *actorDrawAnimatedEffect(Gfx *, struct ActorEffect *);

void raceParticleRenderCallback(void *glist, Actor *actor) {
    actorDrawAnimatedEffect(raceRenderHud(glist, actor, ((Actor_BB40 *)actor)->unk174), actor);
}

void raceParticipantMotionUpdate(void) {
    Actor *actor;
    Struct_sp58 *racerState;
    s32 i;
    u8 colorMode;
    s32 j;
    u32 flags;

    actor = gCurrentActor;
    racerState = ((Actor_BB40 *)actor)->unk174;
    j = racerState->unk28;
    colorMode = 0xB4;
    if (!(actor->flags & 0x10)) {
        playerStateQueueCallback(0x4D, actor, j);
        gCurrentActor->unk144 = 0x3C;
        actor = gCurrentActor;
        actor->flags &= 0xFFFDFFFF;
        for (i = 0; i < 3; i++) {
            ((Actor_BB40 *)gCurrentActor)->unk4->unk34[i] *= 0.3;
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
                actor = gCurrentActor;
                actor->flags &= ~4;
                gCurrentActor->speedXZ = 0.0f;
                for (i = 0; i < 2; i++) {
                    actor = gCurrentActor;
                    if (actor->soundSlots[i] != -1) {
                        sfxStopSlotSound(actor, i);
                    }
                }
            }
            break;
    }
    actor = gCurrentActor;
    flags = actor->flags;
    if (racerState->unk4 <= 0 || racerState->unk8 > 0) {
        colorMode = 0xF0;
    }
    if (flags & 4) {
        actorSpawnNodeEffectFacingCamera(1, colorMode);
        actorSpawnNodeEffectFacingCamera(2, colorMode);
        actor = gCurrentActor;
    }
    if (racerState->unk34 > 0 && racerState->unk34 < 5) {
        gridSetNodeBounds(racerState->unk28, actor->x, actor->y, actor->z, ((Actor_BB40 *)actor)->unk4->unk34[1] / 0.15 * 40.0);
        renderCallbacksRegister(raceParticleRenderCallback, gCurrentActor, 3);
    }
    actor = gCurrentActor;
    actorUpdateModelMatrix(actor, 0);
}

void raceSteerTowardTargetWaypoint(Struct_sp58 *racerState, Struct_8002B180_Arg1 *aux) {
    f32 steerAngle;
    f32 waypointRadius;
    f32 angleDelta;
    f32 distToWaypoint;
    f32 waypointThreshold[1];
    f32 dx;
    f32 dz;
    f32 targetVel;
    f32 sp_angle;
    RaceParticipant *managerData;
    RaceRoute *route;
    f32 targetSpeed;
    ZoneEntry *waypoint;
    u8 idx;
    Actor *manager;

    manager = racerState->unk30;
    managerData = manager->customState;
    route = raceGetRoute(managerData->route);
    targetSpeed = raceGetPathDistanceBetweenTrackers(route, racerState, aux->unk4);
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
    sp_angle = mathAngleDiscrete((f32)waypoint->x, (f32)waypoint->z, gCurrentActor->x, gCurrentActor->z, distToWaypoint);
    angleDelta = mathAngleSignedDistance((s16)sp_angle, gCurrentActor->yaw);

    sp_angle = distToWaypoint;
    steerAngle = angleDelta;
    waypointRadius = (u32)D_807FDCA0->entries[idx].radius;
    waypointThreshold[0] = waypointRadius * 1.2f;
    if (waypointRadius) { // FAKE: empty guard steers float regalloc
    }
    if (sp_angle < waypointThreshold[0]) {
        sp_angle = sp_angle - waypointRadius;
        dz = waypointThreshold[0] - waypointRadius;
        targetVel = (steerAngle = angleDelta * (1.0 + ((1.0f - (sp_angle / dz)) * 1.5 * (2.0f * racerState->unk4))));
    }
    racerState->unkC += ((steerAngle * 0.0033333334f) - racerState->unkC) * 0.5f;
    if (racerState->unk34 >= 2 && racerState->unk34 < 5) {
        if (aux->unkF != 0 && raceGetProgressPercent(route, racerState, managerData) > 0.75) {
            raceSetPiecewiseCurveMode(aux, 0, &D_8002FC70, &D_8002FCA0);
        }
        targetVel = raceEvaluateCurveTargetSpeed(aux, targetSpeed, &D_8002FC70, &D_8002FCA0);
        gCurrentActor->speedXZ = (gCurrentActor->speedXZ < 650.0f) ? gCurrentActor->speedXZ : 650.0f;
        racerState->unk4 = targetVel;
    }
}


void raceUpdateCountdownState(Struct_sp58 *racerState) {
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
        raceSetIntroCutscenePhase(racerState->unk30);
    } else {
        raceClearIntroCutscenePhase(racerState->unk30);
    }
}

void racePlayIntroCameraCutscene(Struct_sp58 *racerState, Struct_8002B610_Arg1 *aux) {
    if (racerState->unk35 == 0) {
        Struct_8002B610_Sub *sub = aux->unk4;
        Struct_PlayerActor *actor = gPlayerSlots[sub->unk28].unk4;
        Struct_174 *unk174 = actor->unk174;
        camSetTargetScaled(unk174->unk104, aux->unk0, 4, 0x800, 0xBE, 0, 0x4A, 0xAE, 0x2D, 0, 0.2f);
        racerState->unk35++;
    }
    racePlayTireScreechSfx();
}

extern s32 D_8002FCAC[];

s32 raceGetFinishCameraId(void *racerState, void *aux) {
    return D_8002FCAC[raceCheckLapCompletionThreshold(racerState, aux, 10)];
}


u16 camStartPath(void *, s16, u8);
void currentActorClearFlag(void);

void raceFinishCameraCutscene(Struct_sp58 *racerState, void *aux) {
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

void raceHandlePostRaceFinished(Struct_sp58 *racerState, void *aux) {
    s32 i;
    s32 var;

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
                resQueueAttachActor(gCurrentActor, 0x22, (u8)raceGetFinishCameraId(racerState, aux));
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
                var = raceGetFinishCameraId(racerState, aux);
                currentActorClearFlag();
                if (var == 0) {
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
    Struct_sp58 *racerState;
    Struct_sp20 *aux;
    s32 i;

    racerState = ((Actor_BB40 *)gCurrentActor)->unk178;
    aux = ((Actor_BB40 *)gCurrentActor)->unk17C;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        aux->unk10 = 1;
        raceSetPiecewiseCurveMode(aux, 5, &D_8002FC70, &D_8002FCA0);
        gCurrentActor->unk144 = 0x3C;
        gCurrentActor->flags &= 0xFFFDFFFE;
        racerState->unk10 = 1.0f;
        for (i = 0; i < 3; i++) {
            ((Actor_BB40 *)gCurrentActor)->unk4->unk34[i] *= 0.3;
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
            racePlayIntroCameraCutscene(racerState, (Struct_8002B610_Arg1 *)aux);
            break;
        case 4:
            raceFinishCameraCutscene(racerState, aux->unk4);
            break;
        case 5:
            raceHandlePostRaceFinished(racerState, aux->unk4);
            break;
    }
    if (racerState->unk34 < 5) {
        raceHandleRacerCollision(aux);
        raceSteerTowardTargetWaypoint(racerState, (Struct_8002B180_Arg1 *)aux);
        raceUpdateRacerMotion(racerState);
        raceUpdateOpponentEnginePitch(gCurrentActor->speedXZ * 0.0307692308f);
    } else {
        gCurrentActor->speedXZ = 0.0f;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

