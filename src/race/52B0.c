#include "common.h"
#include "actor.h"
#include "race.h"
#include "sched.h"
#include "proto/global/117190.h"
#include "proto/global/112080.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/ACDC0.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/FCCD0.h"
#include "proto/race/52B0.h"
#include "proto/race/7BD0.h"
#include "proto/race/A960.h"

extern s32 D_8002FC5C[];

// Competitor racers (raceCompetitorMotionUpdate): the participant record at 0x174 and the motion state
// the shared 936B0 racer helpers step at 0x178.
typedef struct RaceCompetitorActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ void *motion;
} RaceCompetitorActor;

// Opponent racers (raceOpponentRacerBehaviorUpdate, spawnNodeSpawnById(1, ...) in competitor races): the
// participant record at 0x178, motion state at 0x17C and the rubber-band target at 0x180.
typedef struct RaceOpponentActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RaceParticipant *participant;
    /* 0x17C */ void *motion;
    /* 0x180 */ RaceTarget *target;
} RaceOpponentActor;

extern u8 gPlayerCount;
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern PlayerStruct *gPlayerSlots;
void actorInitFromSpawnPoint(void *, void *);

void raceRacerRenderCallback(Gfx *gfx, Actor *actor) {
    raceRenderHud(gfx, actor, actor->customState);
}

void raceSpawnCompetitors(Actor *actor) {
    RaceParticipant *managerData;
    RaceParticipant *racerState;
    Actor *spawnedActor;
    s32 slotIndex;
    s32 i;
    s32 numCompetitors;

    numCompetitors = gPlayerCount;
    slotIndex = 0;
    managerData = actor->customState;
    if (numCompetitors == 1) {
        numCompetitors++;
    }
    raceInitParticipantArray(actor, numCompetitors);
    for (i = 0; i < gPlayerCount; i++) {
        actorSpawn(0x133, 0x9F);
        spawnedActor = gSpawnedActor;
        racerState = spawnedActor->customState;
        racerState->unk27 = 0;
        raceRegisterParticipant(actor, slotIndex, spawnedActor, racerState);
        slotIndex++;
        racerState->playerIdx = i;
    }
    i = 0;
    if (gPlayerCount == 1) {
        spawnedActor = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        racerState = ((RaceOpponentActor *)spawnedActor)->participant;
        racerState->unk27 = 1;
        raceRegisterParticipant(actor, slotIndex, spawnedActor, racerState);
        raceGetParticipantPair(actor, 0, &((RaceOpponentActor *)spawnedActor)->target->actor, &((RaceOpponentActor *)spawnedActor)->target->participant);
        managerData->unk25 = 1;
    } else {
        managerData->unk25 = 0;
    }
    if (numCompetitors > 0) {
        do {
            raceGetParticipantPair(actor, i, &spawnedActor, &racerState);
            racerState->unk36 = i;
            racerState->actor = actor;
            if (racerState->unk27 == 0) {
                actorInitFromSpawnPoint(spawnedActor, racerState);
            }
            i++;
        } while (i != numCompetitors);
    }
    managerData->route = 0;
}

void raceInitCompetitorsAndManager(void) {
    raceInitCompetitorRaceManager();
}

void actorInitAnimations(Actor *, Actor *);
void func_80690190(void *, void *);
void func_8068F72C(void *, void *, s32, s32);
void actorInterpolateAngles(u8, void *, void *);

void raceCompetitorMotionUpdate(void) {
    s32 status;
    void *motion;
    RaceParticipant *participant;
    PlayerState *playerState;
    RaceParticipant *managerData;
    s32 i;
    Actor *manager;
    u8 pad;
    u8 subFlag;

    participant = gCurrentActor->customState;
    motion = ((RaceCompetitorActor *)gCurrentActor)->motion;
    playerState = gPlayerSlots[participant->playerIdx].actor->customState;
    subFlag = gCurrentActor->contactFlags & 1;
    if (!(gCurrentActor->flags & 0x10)) {
        actorInitAnimations(gCurrentActor, gPlayerSlots[participant->playerIdx].actor);
        gCurrentActor->unk144 |= 0x10;
        gCurrentActor->flags &= 0xFFFDFFFF;
        participant->unk44 = 5;
        actorOrNodeFlags(gCurrentActor, 2, 0xC);
    }
    func_80690190(participant, motion);
    status = participant->unk34;
    if (status < 5) {
        if (status == 1) {
            manager = participant->actor;
            managerData = manager->customState;
            if (participant->unk35 == 0) {
                slotQueueUpdate(0xB, 1, 0);
                participant->unk35++;
            }
            if (managerData->unk1C == 0x3C) {
                camSetTargetScaled(playerState->camActor, gCurrentActor, 4, 0x800, 0x32, 0, 0x28, 0x1E, 0x14, 0, 0.4f);
            }
        }
        if (participant->unk34 == 2) {
            if (participant->route != 0) {
                participant->unk4 = raceGetHandicapSpeedBonus(participant) * 2;
                if (participant->unk4 > 1.0) {
                    participant->unk25 = 0x14;
                }
                participant->route = 0;
            }
            if (participant->unk25 != 0) {
                participant->unk25--;
            }
        }
        func_8068F72C(participant, motion, 1, 1);
        if (func_807142D8() == 0) {
            renderCallbacksRegister(raceRacerRenderCallback, gCurrentActor, 3);
        }
    } else if (status == 5 && participant->unk35 == 0) {
        gCurrentActor->flags &= ~4;
        gCurrentActor->speedXZ = 0.0f;
        slotQueueCancel(0xB, 0);
        participant->unk35++;
        for (i = 0; i < 2; i++) {
            if (gCurrentActor->soundSlots[i] != -1) {
                sfxStopSlotSound(gCurrentActor, i);
            }
        }
    }
    actorInterpolateAngles(subFlag, participant, motion);
    actorUpdateModelMatrix(gCurrentActor, 0);
}
extern s16 D_80750AC8;
extern RaceCurvePoint D_8002FC20[];
extern RaceVec3f D_8002FC50;


extern f32 sqrtf(f32);

f32 raceRacerSteerTowardWaypoint(void) {
    s32 idx;
    RaceParticipant *participant;
    RaceTarget *target;
    Actor *manager;
    RaceParticipant *managerData;
    RaceRoute *route;
    s32 pad[2];
    f32 leadDistance;
    f32 targetSpeed;
    f32 dx;
    f32 dz;
    f32 distToWaypoint;
    f32 span;
    u8 subFlag;
    u8 prevTargetState;
    u8 prevSubPhase;
    f32 lo;
    f32 thr;
    f32 fr;
    s16 ang;

    participant = ((RaceOpponentActor *)gCurrentActor)->participant;
    target = ((RaceOpponentActor *)gCurrentActor)->target;
    manager = participant->actor;
    managerData = manager->customState;
    route = raceGetRoute(managerData->route);
    leadDistance = raceGetPathDistanceBetweenTrackers(route, participant, target->participant);
    targetSpeed = 0.0f;
    subFlag = gCurrentActor->contactFlags & 1;
    prevSubPhase = participant->unk35;
    idx = gBehaviourAnimState->path[gBehaviourWorkState->unk25][0];
    dx = (f32)D_807FDCA0->entries[idx].x - gCurrentActor->x;
    dz = (f32)D_807FDCA0->entries[idx].z - gCurrentActor->z;
    distToWaypoint = sqrtf(dx * dx + dz * dz);
    if (distToWaypoint < (f32)D_807FDCA0->entries[idx].radius) {
        gBehaviourWorkState->unk25++;
        gBehaviourWorkState->unk25 = gBehaviourWorkState->unk25 % gBehaviourExtraState->pathCount;
        target->unk10 = (D_807FDCA0->entries[idx].height == 0) && (target->curveMode != 0);
        switch (D_807FDCA0->entries[idx].height) {
            case 2:
                if (leadDistance < 0.0f) {
                    actorScriptStart(gCurrentActor, 0x29E);
                    if (target->curveMode >= 2) {
                        raceSetPiecewiseCurveMode(target, 1, D_8002FC20, &D_8002FC50);
                    }
                    participant->unk35 = 1;
                }
                break;
            case 3:
                actorScriptStart(gCurrentActor, 0x2A1);
                break;
        }
    }
    ang = mathAngleDiscrete((f32)D_807FDCA0->entries[idx].x, (f32)D_807FDCA0->entries[idx].z, gCurrentActor->x, gCurrentActor->z, distToWaypoint);
    ang = mathAngleSignedDistance(ang, participant->heading);
    thr = D_807FDCA0->entries[idx].radius * 1.2;
    if (distToWaypoint < thr) {
        lo = distToWaypoint - (f32)D_807FDCA0->entries[idx].radius;
        span = thr - (f32)D_807FDCA0->entries[idx].radius;
        fr = lo / span;
        ang = ang * (1.0 + (1.0f - fr) * 1.5 * (2.0f * participant->unk4));
    }
    participant->unkC += (ang * 0.0033333334f - participant->unkC) * 0.5f;
    if (participant->unk34 < 2 || participant->unk34 >= 5) {
        return leadDistance;
    }
    if (target->curveMode != 0 && raceGetProgressPercent(route, participant, managerData) > 0.75) {
        raceSetPiecewiseCurveMode(target, 0, D_8002FC20, &D_8002FC50);
    }
    switch (target->curveMode) {
        case 0:
        case 1:
            switch (participant->unk35) {
                case 0:
                    if (gCurrentActor->sub4->animId == 0x29E && target->unk10 != 0 && D_8002FC20[1].x < leadDistance && leadDistance < D_8002FC20[2].x && (randomLcgNext() & 0xFF) < 0xFU) {
                        actorScriptStart(gCurrentActor, 0x29F);
                    }
                    break;
                case 1:
                    targetSpeed = D_8002FC50.z;
                    gCurrentActor->accelY = -50.0f;
                    break;
                case 2:
                    gCurrentActor->speedY = 500.0f;
                    participant->unk35++;
                    break;
                case 4:
                    if (subFlag) {
                        actorScriptStart(gCurrentActor, 0x2A2);
                        participant->unk35++;
                        gCurrentActor->accelY = -30.0f;
                    }
                    break;
                case 5:
                    if (gCurrentActor->y <= gCurrentActor->waterY) {
                        actorScriptStart(gCurrentActor, 0x29D);
                        participant->unk35 = 0;
                        target->unk10 = target->curveMode != 0;
                    }
                    break;
            }
            break;
        case 4:
            ang = 0;
            switch (participant->unk35) {
                case 1:
                    participant->unk35++;
                    break;
                case 2:
                    ang = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, target->actor->x, target->actor->z) - participant->heading;
                    ang &= 0xFFF;
                    break;
                case 4:
                    raceSetPiecewiseCurveMode(target, 5, D_8002FC20, &D_8002FC50);
                    participant->unk2 = 0;
                    break;
            }
            participant->unk2 = mathAngleEaseToward(participant->unk2, ang, 5.0f);
            break;
    }
    if (targetSpeed == 0.0f) {
        prevTargetState = target->curveMode;
        targetSpeed = raceEvaluateCurveWithRubberband(target, leadDistance, D_8002FC20, &D_8002FC50);
        if (prevTargetState == 2 && target->curveMode == 3) {
            actorScriptStart(gCurrentActor, 0x2A0);
        }
        if (prevTargetState == 3 && target->curveMode == 4) {
            participant->unk35 = prevSubPhase;
        }
    }
    if (subFlag != 0) {
        targetSpeed *= 0.9;
        participant->unk8 = 0.1f;
        gCurrentActor->speedXZ = (gCurrentActor->speedXZ < 350.0f) ? gCurrentActor->speedXZ : 350.0f;
    } else {
        participant->unk8 = 0.0f;
    }
    participant->unk4 = targetSpeed;
    return leadDistance;
}





void raceAdjustRubberbandTargetSpeed(Actor *actor, RaceParticipant *racerState, f32 relSpeed, f32 leadDelta, f32 targetDist) {
    AnimSlot *anim;
    f32 rampSpeed;
    f32 framesLeft;
    f64 speed;
    f32 frame;

    anim = actor->sub4->model;
    frame = anim->frame;
    if (relSpeed != 0) {
        framesLeft = (s32)(leadDelta / relSpeed);
        if (!(framesLeft <= 0)) {
            rampSpeed = (targetDist - frame) / framesLeft;
            if (rampSpeed < 0.0f) {
                rampSpeed = 0.01f;
            }
            speed = anim->speed < 0.01 ? 0.01 : anim->speed;
            rampSpeed = (f64)rampSpeed / speed;
            if (rampSpeed > 2.0f) {
                rampSpeed = 2.0f;
            }
            scriptSetActorRampTarget(actor, rampSpeed, 0.0f);
        }
    }
}

s32 raceGetFinishCutsceneCam(RaceParticipant *racerState, RaceParticipant *chased) {
    return D_8002FC5C[raceCheckLapCompletionThreshold(racerState, chased, 10)];
}


void raceOpponentRacerBehaviorUpdate(void) {
    RaceParticipant *participant;
    void *motion;
    RaceTarget *target;
    f32 leadDistance;
    f64 pad;
    RaceParticipant *managerData;
    Actor *manager;
    RaceParticipant *chased;
    u8 idx;
    s32 raceResult;
    s32 pathFrames;
    f32 rampSpeed;

    participant = ((RaceOpponentActor *)gCurrentActor)->participant;
    motion = ((RaceOpponentActor *)gCurrentActor)->motion;
    target = ((RaceOpponentActor *)gCurrentActor)->target;
    leadDistance = 0.0f;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        manager = participant->actor;
        managerData = manager->customState;
        participant->unk10 = 1.0f;
        gCurrentActor->flags &= 0xFFFDFFFE;
        gCurrentActor->drawDistance = 0x5DC;
        raceSetPiecewiseCurveMode(target, 5, D_8002FC20, &D_8002FC50);
        participant->unk34 = 0;
        camRequestPathLength();
        pathFrames = camStartPath(gCurrentActor, 1, 1) - 0x3C;
        managerData->unk1C = pathFrames;
        target->startCountdown = pathFrames;
        participant->unk4 = 1.0f;
        gBehaviourWorkState->unk25 = gBehaviourExtraState->pathCount - 5;
        idx = gBehaviourAnimState->path[gBehaviourWorkState->unk25][0];
        gCurrentActor->x = D_807FDCA0->entries[idx].x;
        gCurrentActor->y = D_807FDCA0->entries[idx].y;
        gCurrentActor->z = D_807FDCA0->entries[idx].z;
        D_80750AC8 = 0xA;
    }
    if (target->startCountdown != 0) {
        target->startCountdown--;
    }
    if (participant->unk34 < 5) {
        leadDistance = raceRacerSteerTowardWaypoint();
        if (participant->unk34 == 2) {
            raceHandleRacerCollision(target);
        } else if (participant->unk34 == 4 && target->finishCamStarted == 0) {
            target->finishCamStarted = 1;
            if (flagGet(0xA5, 0) == 0) {
                camStartPath(target->actor, 0, 1);
                currentActorClearFlag();
            } else {
                mapCheckAutoTransition();
            }
        }
        func_8068F72C(participant, motion, 0, 0);
    } else if (participant->unk34 == 5) {
        switch (participant->unk35) {
        case 0:
            if (flagGet(0xA5, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                gCurrentActor->pitch = 0;
                gCurrentActor->roll = 0;
                actorScriptStart(gCurrentActor, 0x29A);
            }
            participant->unk35++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                chased = target->participant;
                currentActorClearFlag();
                resQueueAttachActor(gCurrentActor, 0x12, raceGetFinishCutsceneCam(participant, chased));
                participant->unk35++;
            }
            break;
        case 2:
            if (!(gCurrentActor->flags & 0x02000000)) {
                camResumePath();
                participant->unk35++;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                raceResult = (s32)target->participant; // FAKE: the s32 result variable first holds the chased participant pointer
                raceResult = raceGetFinishCutsceneCam(participant, (RaceParticipant *)raceResult);
                currentActorClearFlag();
                if (raceResult == 0) {
                    csModelStateSetFirstByte(0x3B, 0xA);
                    flagSet(0xA5, 1, 0);
                } else {
                    hudSpawnTextScreen(1);
                    participant->unk35++;
                }
                participant->unk35++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                mapCheckAutoTransition();
                participant->unk35++;
            }
            break;
        }
    }
    switch (gCurrentActor->sub4->animId) {
    case 0x29E:
    case 0x2A2:
        rampSpeed = gCurrentActor->speedXZ * 0.0025f;
        rampSpeed = rampSpeed < 0.1 ? 0.1 : rampSpeed;
        scriptSetActorRampTarget(gCurrentActor, rampSpeed, 10.0f);
        break;
    case 0x2A0:
        if (gCurrentActor->sub4->model->animId == 0x4A7) {
            raceAdjustRubberbandTargetSpeed(gCurrentActor, participant, gCurrentActor->speedXZ - target->actor->speedXZ, (leadDistance - D_8002FC20[2].x) * 40.0f, 23.0f);
            break;
        }
    default:
        if (gCurrentActor->sub4->model->animId != 0x49B) {
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 10.0f);
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    func_8072881C(0, &gBehaviourWorkState->unk28);
}
