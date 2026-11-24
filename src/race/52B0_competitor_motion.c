#include "common.h"
#include "actor.h"
#include "race.h"
#include "sched.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/112080_resource_parse.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/166A0_random.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2C910.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/42630_cutscene_interp.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/90D80_render_callbacks.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/ACDC0_pause_menu.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/FCCD0_slot_queue.h"
#include "proto/race/52B0_competitor_motion.h"
#include "proto/race/7BD0_manager.h"
#include "proto/race/A960_route_gates.h"

RaceCurvePoint raceOpponentSpeedCurve[6] = {
    { -1000.0f, 0.8f }, { -150.0f, 1.0f }, { -70.0f, 1.0f }, { 90.0f, 1.0f }, { 100.0f, 1.0f }, { 200.0f, 2.5f },
};
RaceVec3f raceOpponentSpeedLevels = { 0.8f, 1.0f, 2.5f };
s32 raceOpponentFinishCamIds[5] = { 3, 0, 1, 2, 0 };

// Opponent racers (raceOpponentRacerBehaviorUpdate, spawnNodeSpawnById(1, ...) in competitor races): the
// participant record at 0x178, motion state at 0x17C and the rubber-band target at 0x180.
typedef struct RaceOpponentActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RaceParticipant *participant;
    /* 0x17C */ struct VehicleMotion *motion;
    /* 0x180 */ RaceTarget *target;
} RaceOpponentActor;

extern u8 gPlayerCount;
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern PlayerStruct *gPlayerSlots;

Gfx *raceRacerRenderCallback(Gfx *gfx, Actor *actor) {
    return raceRenderHud(gfx, actor, actor->customState);
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
        racerState->isCpu = 0;
        raceRegisterParticipant(actor, slotIndex, spawnedActor, racerState);
        slotIndex++;
        racerState->playerIdx = i;
    }
    if (gPlayerCount == 1) {
        spawnedActor = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        racerState = ((RaceOpponentActor *)spawnedActor)->participant;
        racerState->isCpu = 1;
        raceRegisterParticipant(actor, slotIndex, spawnedActor, racerState);
        raceGetParticipantPair(actor, 0, &((RaceOpponentActor *)spawnedActor)->target->actor, &((RaceOpponentActor *)spawnedActor)->target->participant);
        managerData->hasCpuRival = 1;
    } else {
        managerData->hasCpuRival = 0;
    }
    for (i = 0; i < numCompetitors; i++) {
        raceGetParticipantPair(actor, i, &spawnedActor, &racerState);
        racerState->place = i;
        racerState->actor = actor;
        if (racerState->isCpu == 0) {
            actorInitFromSpawnPoint(spawnedActor, racerState);
        }
    }
    managerData->route = 0;
}

void raceInitCompetitorsAndManager(void) {
    raceInitCompetitorRaceManager();
}

void raceCompetitorMotionUpdate(void) {
    s32 status;
    struct VehicleMotion *motion;
    RaceParticipant *participant;
    PlayerState *playerState;
    RaceParticipant *managerData;
    s32 i;
    Actor *manager;
    u8 pad;
    u8 onGround;

    participant = gCurrentActor->customState;
    motion = ((VehicleActor *)gCurrentActor)->motion;
    playerState = gPlayerSlots[participant->playerIdx].actor->customState;
    onGround = gCurrentActor->contactFlags & 1;
    if (!(gCurrentActor->flags & 0x10)) {
        actorInitAnimations(gCurrentActor, gPlayerSlots[participant->playerIdx].actor);
        gCurrentActor->collisionMode |= 0x10;
        gCurrentActor->flags &= ~0x20000;
        participant->gateMissesLeft = 5;
        actorOrNodeFlags(gCurrentActor, 2, 0xC);
    }
    vehicleUpdateEngineSound(participant, motion);
    status = participant->raceStatus;
    if (status < 5) {
        if (status == 1) {
            manager = participant->actor;
            managerData = manager->customState;
            if (participant->statusStep == 0) {
                slotQueueUpdate(0xB, 1, 0);
                participant->statusStep++;
            }
            if (managerData->phaseTimer == 0x3C) {
                camSetTargetScaled(playerState->camActor, gCurrentActor, 4, 0x800, 0x32, 0, 0x28, 0x1E, 0x14, 0, 0.4f);
            }
        }
        if (participant->raceStatus == 2) {
            if (participant->boostCharge != 0) {
                participant->throttle = raceGetHandicapSpeedBonus(participant) * 2;
                if (participant->throttle > 1.0) {
                    participant->boostTimer = 0x14;
                }
                participant->boostCharge = 0;
            }
            if (participant->boostTimer != 0) {
                participant->boostTimer--;
            }
        }
        vehicleUpdateMotion(participant, motion, 1, 1);
        if (menuIsTransitionType3Or4() == 0) {
            renderCallbacksRegister(raceRacerRenderCallback, gCurrentActor, 3);
        }
    } else if (status == 5 && participant->statusStep == 0) {
        gCurrentActor->flags &= ~4;
        gCurrentActor->speedXZ = 0.0f;
        slotQueueCancel(0xB, 0);
        participant->statusStep++;
        for (i = 0; i < 2; i++) {
            if (gCurrentActor->soundSlots[i] != -1) {
                sfxStopSlotSound(gCurrentActor, i);
            }
        }
    }
    actorInterpolateAngles(onGround, participant, motion);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 gTextNumberArg; // ORIG: this file declares it s16: the target keeps li t5,10 (0xf80, stored by sh at 0xfb8) apart from the idx * 10 sll/addu/sll at 0xf30-0xf3c, which the shared u16 extern in text.h merges into a multu

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
    f32 approachWidth;
    u8 onGround;
    u8 prevCurveMode;
    u8 prevSubPhase;
    f32 pastRadius;
    f32 approachRadius;
    f32 approachFrac;
    s16 ang;

    participant = ((RaceOpponentActor *)gCurrentActor)->participant;
    target = ((RaceOpponentActor *)gCurrentActor)->target;
    manager = participant->actor;
    managerData = manager->customState;
    route = raceGetRoute(managerData->route);
    leadDistance = raceGetPathDistanceBetweenTrackers(route, participant, target->participant);
    targetSpeed = 0.0f;
    onGround = gCurrentActor->contactFlags & 1;
    prevSubPhase = participant->statusStep;
    idx = gBehaviourAnimState->path[gBehaviourWorkState->waypointIndex][0];
    dx = gBehaviourZone->entries[idx].x - gCurrentActor->x;
    dz = gBehaviourZone->entries[idx].z - gCurrentActor->z;
    distToWaypoint = sqrtf(dx * dx + dz * dz);
    if (distToWaypoint < gBehaviourZone->entries[idx].radius) {
        gBehaviourWorkState->waypointIndex++;
        gBehaviourWorkState->waypointIndex %= gBehaviourExtraState->pathCount;
        target->chaseEnabled = (gBehaviourZone->entries[idx].height == 0) && (target->curveMode != 0);
        switch (gBehaviourZone->entries[idx].height) {
            case 2:
                if (leadDistance < 0.0f) {
                    actorScriptStart(gCurrentActor, 0x29E);
                    if (target->curveMode >= 2) {
                        raceSetPiecewiseCurveMode(target, 1, raceOpponentSpeedCurve, &raceOpponentSpeedLevels);
                    }
                    participant->statusStep = 1;
                }
                break;
            case 3:
                actorScriptStart(gCurrentActor, 0x2A1);
                break;
        }
    }
    ang = mathAngleDiscrete(gBehaviourZone->entries[idx].x, gBehaviourZone->entries[idx].z, gCurrentActor->x, gCurrentActor->z, distToWaypoint);
    ang = mathAngleSignedDistance(ang, participant->heading);
    approachRadius = gBehaviourZone->entries[idx].radius * 1.2;
    if (distToWaypoint < approachRadius) {
        pastRadius = distToWaypoint - gBehaviourZone->entries[idx].radius;
        approachWidth = approachRadius - gBehaviourZone->entries[idx].radius;
        approachFrac = pastRadius / approachWidth;
        ang = ang * (1.0 + (1.0f - approachFrac) * 1.5 * (2.0f * participant->throttle));
    }
    participant->steer += (ang * 0.0033333334f - participant->steer) * 0.5f;
    if (participant->raceStatus < 2 || participant->raceStatus >= 5) {
        return leadDistance;
    }
    if (target->curveMode != 0 && raceGetProgressPercent(route, participant, managerData) > 0.75) {
        raceSetPiecewiseCurveMode(target, 0, raceOpponentSpeedCurve, &raceOpponentSpeedLevels);
    }
    switch (target->curveMode) {
        case 0:
        case 1:
            switch (participant->statusStep) {
                case 0:
                    if (gCurrentActor->sub4->animId == 0x29E && target->chaseEnabled != 0 && raceOpponentSpeedCurve[1].x < leadDistance && leadDistance < raceOpponentSpeedCurve[2].x && (randomLcgNext() & 0xFF) < 0xF) {
                        actorScriptStart(gCurrentActor, 0x29F);
                    }
                    break;
                case 1:
                    targetSpeed = raceOpponentSpeedLevels.z;
                    gCurrentActor->accelY = -50.0f;
                    break;
                case 2:
                    gCurrentActor->speedY = 500.0f;
                    participant->statusStep++;
                    break;
                case 4:
                    if (onGround) {
                        actorScriptStart(gCurrentActor, 0x2A2);
                        participant->statusStep++;
                        gCurrentActor->accelY = -30.0f;
                    }
                    break;
                case 5:
                    if (gCurrentActor->y <= gCurrentActor->waterY) {
                        actorScriptStart(gCurrentActor, 0x29D);
                        participant->statusStep = 0;
                        target->chaseEnabled = target->curveMode != 0;
                    }
                    break;
            }
            break;
        case 4:
            ang = 0;
            switch (participant->statusStep) {
                case 1:
                    participant->statusStep++;
                    break;
                case 2:
                    ang = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, target->actor->x, target->actor->z) - participant->heading;
                    ang &= 0xFFF;
                    break;
                case 4:
                    raceSetPiecewiseCurveMode(target, 5, raceOpponentSpeedCurve, &raceOpponentSpeedLevels);
                    participant->yawOffset = 0;
                    break;
            }
            participant->yawOffset = mathAngleEaseToward(participant->yawOffset, ang, 5.0f);
            break;
    }
    if (targetSpeed == 0.0f) {
        prevCurveMode = target->curveMode;
        targetSpeed = raceEvaluateCurveWithRubberband(target, leadDistance, raceOpponentSpeedCurve, &raceOpponentSpeedLevels);
        if (prevCurveMode == 2 && target->curveMode == 3) {
            actorScriptStart(gCurrentActor, 0x2A0);
        }
        if (prevCurveMode == 3 && target->curveMode == 4) {
            participant->statusStep = prevSubPhase;
        }
    }
    if (onGround != 0) {
        targetSpeed *= 0.9;
        participant->brake = 0.1f;
        gCurrentActor->speedXZ = (gCurrentActor->speedXZ < 350.0f) ? gCurrentActor->speedXZ : 350.0f;
    } else {
        participant->brake = 0.0f;
    }
    participant->throttle = targetSpeed;
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
    return raceOpponentFinishCamIds[raceCheckLapCompletionThreshold(racerState, chased, 10)];
}


void raceOpponentRacerBehaviorUpdate(void) {
    RaceParticipant *participant;
    struct VehicleMotion *motion;
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
        participant->steerGain = 1.0f;
        gCurrentActor->flags &= ~0x20001;
        gCurrentActor->drawDistance = 0x5DC;
        raceSetPiecewiseCurveMode(target, 5, raceOpponentSpeedCurve, &raceOpponentSpeedLevels);
        participant->raceStatus = 0;
        camRequestPathLength();
        pathFrames = camStartPath(gCurrentActor, 1, 1) - 0x3C;
        managerData->phaseTimer = pathFrames;
        target->startCountdown = pathFrames;
        participant->throttle = 1.0f;
        gBehaviourWorkState->waypointIndex = gBehaviourExtraState->pathCount - 5;
        idx = gBehaviourAnimState->path[gBehaviourWorkState->waypointIndex][0];
        gCurrentActor->x = gBehaviourZone->entries[idx].x;
        gCurrentActor->y = gBehaviourZone->entries[idx].y;
        gCurrentActor->z = gBehaviourZone->entries[idx].z;
        gTextNumberArg = 0xA;
    }
    if (target->startCountdown != 0) {
        target->startCountdown--;
    }
    if (participant->raceStatus < 5) {
        leadDistance = raceRacerSteerTowardWaypoint();
        if (participant->raceStatus == 2) {
            raceHandleRacerCollision(target);
        } else if (participant->raceStatus == 4 && target->finishCamStarted == 0) {
            target->finishCamStarted = 1;
            if (flagGet(0xA5, 0) == 0) {
                camStartPath(target->actor, 0, 1);
                currentActorClearFlag();
            } else {
                mapCheckAutoTransition();
            }
        }
        vehicleUpdateMotion(participant, motion, 0, 0);
    } else if (participant->raceStatus == 5) {
        switch (participant->statusStep) {
        case 0:
            if (flagGet(0xA5, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                gCurrentActor->pitch = 0;
                gCurrentActor->roll = 0;
                actorScriptStart(gCurrentActor, 0x29A);
            }
            participant->statusStep++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                chased = target->participant;
                currentActorClearFlag();
                resQueueAttachActor(gCurrentActor, 0x12, raceGetFinishCutsceneCam(participant, chased));
                participant->statusStep++;
            }
            break;
        case 2:
            if (!(gCurrentActor->flags & 0x02000000)) {
                camResumePath();
                participant->statusStep++;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                RaceParticipant *rival = target->participant;

                raceResult = raceGetFinishCutsceneCam(participant, rival);
                currentActorClearFlag();
                if (raceResult == 0) {
                    csModelStateSetFirstByte(0x3B, 0xA);
                    flagSet(0xA5, 1, 0);
                } else {
                    hudSpawnTextScreen(1);
                    participant->statusStep++;
                }
                participant->statusStep++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                mapCheckAutoTransition();
                participant->statusStep++;
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
            raceAdjustRubberbandTargetSpeed(gCurrentActor, participant, gCurrentActor->speedXZ - target->actor->speedXZ, (leadDistance - raceOpponentSpeedCurve[2].x) * 40.0f, 23.0f);
            break;
        }
    default:
        if (gCurrentActor->sub4->model->animId != 0x49B) {
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 10.0f);
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
}
