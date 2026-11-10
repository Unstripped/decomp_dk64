#include "common.h"
#include "actor.h"
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

typedef struct {
    char pad[0x25];
    u8 unk25;
    u8 unk26;
} Struct_sp5C;

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

typedef struct {
    char pad[0x174];
    Struct_sp58 *unk174;
    Struct_sp58 *unk178;
    void *unk17C;
} Struct_sp54;

typedef struct Struct_arg0 {
    char pad[0x174];
    Struct_sp5C *unk174;
} Struct_arg0;

extern u8 gPlayerCount;
extern Struct_sp54 *gSpawnedActor;
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

typedef struct Actor_BB40 {
    char pad[0x4];
    Actor_BB40_Sub4 *unk4;
    char pad8[0x60 - 0x8];
    u32 unk60;
    char pad64[0x6A - 0x64];
    u16 unk6A;
    char pad6C[0x6E - 0x6C];
    s16 unk6E[2];
    char pad72[0x7C - 0x72];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xB8 - 0x88];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    char padCC[0xDC - 0xCC];
    s16 unkDC;
    s16 unkDE;
    char padE0[0xE4 - 0xE0];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    char padEA[0xEE - 0xEA];
    s16 unkEE;
    char padF0[0xF8 - 0xF0];
    s16 unkF8;
    char padFA[0x144 - 0xFA];
    u8 unk144;
    char pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
    char pad156[0x174 - 0x156];
    Struct_sp58 *unk174;
    Struct_sp58 *unk178;
    Struct_sp20 *unk17C;
} Actor_BB40;
extern Actor_BB40 *gCurrentActor;

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
extern Actor_BB40 *gCurrentActor;

void playerStateQueueCallback(); // FAKE: callee prototype steer
s32 sfxStopSlotSound(Actor_BB40 *, u8); // FAKE: callee prototype steer
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
void actorStepPhysics(Actor_BB40 *, s16, s16);
void actorApplyVelocity(Actor_BB40 *);
void actorUpdateFloorContactAndTilt(Actor_BB40 *, f32);
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

void raceInitParticipants(Struct_arg0 *raceMgr) {
    Struct_sp5C *cursor;
    Struct_sp58 *racerState;
    Struct_sp54 *racerActor;
    s32 participantIndex;
    s32 i;
    s32 numParticipants;

    numParticipants = gPlayerCount;
    participantIndex = 0;
    cursor = raceMgr->unk174;
    if (numParticipants == 1) {
        numParticipants++;
    }
    raceInitParticipantArray(raceMgr, numParticipants);
    for (i = 0; i < gPlayerCount; i++) {
        actorSpawn(0x142, 0x95);
        racerActor = gSpawnedActor;
        racerState = racerActor->unk174;
        racerState->unk27 = 0;
        raceRegisterParticipant(raceMgr, participantIndex, racerActor, racerState);
        participantIndex++;
        racerState->unk28 = i;
    }
    i = 0;
    if (gPlayerCount == 1) {
        racerActor = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        racerState = racerActor->unk178;
        racerState->unk27 = 1;
        raceRegisterParticipant(raceMgr, participantIndex, racerActor, racerState);
        raceGetParticipantPair(raceMgr, 0, racerActor->unk17C, (u8 *)racerActor->unk17C + 4);
        cursor->unk25 = 1;
    } else {
        cursor->unk25 = 0;
    }
    if (numParticipants > 0) {
        do {
            raceGetParticipantPair(raceMgr, i, &racerActor, &racerState);
            racerState->unk36 = i;
            racerState->unk30 = raceMgr;
            actorInitFromSpawnPoint(racerActor, racerState);
            i++;
        } while (i != numParticipants);
    }
    cursor->unk26 = 0;
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

    onGround = gCurrentActor->unk6A & 1;
    a1 = gCurrentActor->unkE6;
    if (!(gCurrentActor->unk60 & 0x10)) {
        gCurrentActor->unk144 = 0x3C;
        gCurrentActor->unk60 |= 0x10400;
        gCurrentActor->unk154 = 0;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unkB8 = 0.0f;
        gCurrentActor->unkC4 = -20.0f;
        gCurrentActor->unkC8 = -900.0f;
        gCurrentActor->unkF8 = 0x12C;
    }
    velX = mathSinF(gCurrentActor->unkEE) * gCurrentActor->unkB8;
    velZ = mathCosF(gCurrentActor->unkEE) * gCurrentActor->unkB8;
    if (racerState->unk20 != 0) {
        a1 = a1 + 0x800;
        a1 = a1 & 0xFFF;
        racerState->unk4 = (f32)((f64)racerState->unk4 * 0.85);
    }
    if (onGround != 0) {
        fv0 = (f32)((f64)(racerState->unk8 * gCurrentActor->unkB8) * 0.2);
        if (!(fv0 > 1.0f)) {
            fv0 = 1.0f;
        }
        forwardAccel = (f32)((f64)(racerState->unk4 * 35.0f) + ((f64)gCurrentActor->unkB8 * 0.13));
        friction = (f32)((f64)(gCurrentActor->unkB8 * gCurrentActor->unkB8 * 0.00025f) + (27.0 + (f64)fv0));
    } else {
        forwardAccel = racerState->unk4 * 2;
        friction = (gCurrentActor->unkB8 * gCurrentActor->unkB8 * 0.00002f) + 2;
    }
    velX += mathSinF(a1) * forwardAccel;
    velZ += mathCosF(a1) * forwardAccel;
    gCurrentActor->unkB8 = sqrtf((velX * velX) + (velZ * velZ));
    gCurrentActor->unkEE = (s16)(s32)(mathAtan2(velX, velZ) * 651.8986f);
    if (onGround) {
        pitchAngle = 0x400 - gCurrentActor->unkDE;
        signedDist = mathAngleSignedDistance(gCurrentActor->unkDC, gCurrentActor->unkE6);
        tiltScale = (f32)pitchAngle;
        targetTilt = (s16)(s32)(mathCosF(signedDist) * tiltScale);
        fv0 = mathSinF(signedDist) * tiltScale;
        targetTilt = targetTilt & 0xFFF;
        a3 = (s32)fv0;
        a3 = a3 & 0xFFF;
    } else {
        v1 = mathAngleFromVector2D(gCurrentActor->unkB8, gCurrentActor->unkC0);
        a0 = gCurrentActor->unkEE;
        if (v1 >= 0x800) {
            v1 = 0xFFF - v1;
            a0 = a0 + 0x800;
            a0 = a0 & 0xFFF;
        }
        yawDelta = mathAngleSignedDistance(a0, gCurrentActor->unkE6);
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
    gCurrentActor->unkE8 = mathAngleEaseToward(gCurrentActor->unkE8, targetTilt, 4.0f, a3);
    gCurrentActor->unkE4 = mathAngleEaseToward(gCurrentActor->unkE4, (s32)a3, 4.0f, a3);
    gCurrentActor->unkB8 = gCurrentActor->unkB8 - friction;
    fv1 = gCurrentActor->unkB8;
    if (fv1 < 0.0f) {
        gCurrentActor->unkB8 = 0.0f;
        fv1 = gCurrentActor->unkB8;
    }
    if (racerState->unk20 != 0) {
        if (fv1 < 100.0f) {
            gCurrentActor->unkB8 = fv1;
            fv1 = gCurrentActor->unkB8;
        } else {
            gCurrentActor->unkB8 = 100.0f;
            fv1 = gCurrentActor->unkB8;
        }
    }
    fv0 = fv1 - gCurrentActor->unkBC;
    if (fv0 < 0.0f) {
        fv0 = 0.0f;
    }
    gCurrentActor->unkE6 = (s16)(s32)((f64)gCurrentActor->unkE6 + ((f64)(steerAmount * -40.0f) * (1.0 + ((f64)fv0 * 0.05))));
    gCurrentActor->unkE6 = gCurrentActor->unkE6 & 0xFFF;
    gCurrentActor->unkC0 = gCurrentActor->unkC0 + gCurrentActor->unkC4;
    fv1 = gCurrentActor->unkC8;
    if (gCurrentActor->unkC0 < fv1) {
        gCurrentActor->unkC0 = fv1;
    }
    a0 = gCurrentActor->unkEE;
    actorStepPhysics(gCurrentActor, a0, a0);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    if (gGlobalOverlayFlags & 0x2000) {
        raceUpdateLapAndWaypointTracker(racerState);
    }
}

Gfx *actorDrawAnimatedEffect(Gfx *, struct ActorEffect *);

void raceParticleRenderCallback(void *glist, Actor_BB40 *actor) {
    actorDrawAnimatedEffect(raceRenderHud(glist, actor, actor->unk174), actor);
}

void raceParticipantMotionUpdate(void) {
    Actor_BB40 *actor;
    Struct_sp58 *racerState;
    s32 i;
    u8 colorMode;
    s32 j;
    u32 flags;

    actor = gCurrentActor;
    racerState = actor->unk174;
    j = racerState->unk28;
    colorMode = 0xB4;
    if (!(actor->unk60 & 0x10)) {
        playerStateQueueCallback(0x4D, actor, j);
        gCurrentActor->unk144 = 0x3C;
        actor = gCurrentActor;
        actor->unk60 &= 0xFFFDFFFF;
        for (i = 0; i < 3; i++) {
            gCurrentActor->unk4->unk34[i] *= 0.3;
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
            raceUpdateEngineSoundPitch(gCurrentActor->unkB8 * 0.0307692308f);
            raceUpdateRacerMotion(racerState);
            break;
        case 5:
            if (racerState->unk35 == 0) {
                racerState->unk35++;
                slotQueueCancel(0xB, 0);
                actor = gCurrentActor;
                actor->unk60 &= ~4;
                gCurrentActor->unkB8 = 0.0f;
                for (i = 0; i < 2; i++) {
                    actor = gCurrentActor;
                    if (actor->unk6E[i] != -1) {
                        sfxStopSlotSound(actor, i);
                    }
                }
            }
            break;
    }
    actor = gCurrentActor;
    flags = actor->unk60;
    if (racerState->unk4 <= 0 || racerState->unk8 > 0) {
        colorMode = 0xF0;
    }
    if (flags & 4) {
        actorSpawnNodeEffectFacingCamera(1, colorMode);
        actorSpawnNodeEffectFacingCamera(2, colorMode);
        actor = gCurrentActor;
    }
    if (racerState->unk34 > 0 && racerState->unk34 < 5) {
        gridSetNodeBounds(racerState->unk28, actor->unk7C, actor->unk80, actor->unk84, actor->unk4->unk34[1] / 0.15 * 40.0);
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
    Struct_sp5C *cursor;
    s32 routeIndex;
    f32 targetSpeed;
    ZoneEntry *waypoint;
    u8 idx;
    Struct_arg0 *pad;

    pad = racerState->unk30;
    cursor = pad->unk174;
    routeIndex = raceGetRoute(cursor->unk26);
    targetSpeed = raceGetPathDistanceBetweenTrackers(routeIndex, racerState, aux->unk4);
    idx = gBehaviourAnimState->path[gBehaviourWorkState->unk25][0];
    waypoint = &D_807FDCA0->entries[idx];
    dx = (f32)waypoint->x - gCurrentActor->unk7C;
    dz = (f32)waypoint->z - gCurrentActor->unk84;
    distToWaypoint = sqrtf((dx * dx) + (dz * dz));
    waypoint = &D_807FDCA0->entries[idx];
    if (distToWaypoint < (f32)waypoint->radius) {
        if (gCurrentActor->unk7C) { // FAKE: empty guard steers float regalloc
        }
        gBehaviourWorkState->unk25++;
        gBehaviourWorkState->unk25 = gBehaviourWorkState->unk25 % gBehaviourExtraState->pathCount;
    }
    waypoint = &D_807FDCA0->entries[idx];
    sp_angle = mathAngleDiscrete((f32)waypoint->x, (f32)waypoint->z, gCurrentActor->unk7C, gCurrentActor->unk84, distToWaypoint);
    angleDelta = mathAngleSignedDistance((s16)sp_angle, gCurrentActor->unkE6);

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
        if (aux->unkF != 0 && raceGetProgressPercent(routeIndex, racerState, cursor) > 0.75) {
            raceSetPiecewiseCurveMode(aux, 0, &D_8002FC70, &D_8002FCA0);
        }
        targetVel = raceEvaluateCurveTargetSpeed(aux, targetSpeed, &D_8002FC70, &D_8002FCA0);
        gCurrentActor->unkB8 = (gCurrentActor->unkB8 < 650.0f) ? gCurrentActor->unkB8 : 650.0f;
        racerState->unk4 = targetVel;
    }
}


void raceUpdateCountdownState(Struct_sp58 *racerState) {
    switch (racerState->unk35) {
        case 0:
            if (gCurrentActor->unk60 & 0x2000000) {
                racerState->unk35++;
            }
            break;
        case 1:
            if (!(gCurrentActor->unk60 & 0x2000000)) {
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
                gCurrentActor->unkE4 = 0;
                gCurrentActor->unkE8 = 0;
                for (i = 0; i < 2; i++) {
                    if (gCurrentActor->unk6E[i] != -1) {
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
            if (!(gCurrentActor->unk60 & 0x2000000)) {
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

    racerState = gCurrentActor->unk178;
    aux = gCurrentActor->unk17C;
    behaviourFrameBegin();
    if (!(gCurrentActor->unk60 & 0x10)) {
        aux->unk10 = 1;
        raceSetPiecewiseCurveMode(aux, 5, &D_8002FC70, &D_8002FCA0);
        gCurrentActor->unk144 = 0x3C;
        gCurrentActor->unk60 &= 0xFFFDFFFE;
        racerState->unk10 = 1.0f;
        for (i = 0; i < 3; i++) {
            gCurrentActor->unk4->unk34[i] *= 0.3;
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
        raceUpdateOpponentEnginePitch(gCurrentActor->unkB8 * 0.0307692308f);
    } else {
        gCurrentActor->unkB8 = 0.0f;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

