#include "common.h"
#include "actor.h"
#include "text.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/7130.h"
#include "proto/global/ACDC0.h"
#include "proto/global/CEAE0.h"
#include "proto/global/E4090.h"
#include "proto/global/EFDC0.h"
#include "proto/global/FCCD0.h"
#include "proto/race/0.h"
#include "proto/race/7BD0.h"
#include "proto/race/A960.h"


typedef struct RaceRouteEvent { // per-route event row: applied when the racer reaches its waypoint (zone entry)
    s16 waypoint;
    f32 gravity;
    u8 action;
} RaceRouteEvent;


extern s32 gCurrentMap;
extern Actor *gCurrentActor;
extern Actor *gActivePlayerActor;
RaceRouteEvent D_8002FB10[8] = {
    { 0x10, -360.0f, 0 }, { 0x11, -19.0f, 0 }, { 0x17, -20.0f, 1 }, { 0x1B, -360.0f, 0 },
    { 0x1C, -17.0f, 0 }, { 0x33, -20.0f, 1 }, { 0x38, -20.0f, 2 }, { 0x3C, -20.0f, 2 },
};
RaceRouteEvent D_8002FB70[3] = { { 0x26, -20.0f, 1 }, { 0x28, -20.0f, 2 }, { 0x32, -20.0f, 2 } };

void raceOpponentFollowWaypoints(void) {
    f32 speedDelta;
    f32 turnDelta;
    f32 vx;
    f32 vz;
    f32 curSpeed;
    f32 oscSpeed;
    ZoneEntry *zone;
    f32 heightAdjust;
    u8 routeRowIdx;
    RaceRouteEvent *routeRows;
    f32 friction;
    f32 dist;
    f32 heading;
    s16 yawDiff;

    routeRowIdx = gBehaviourWorkState->routeRow;
    if (gCurrentMap == 0x52) {
        routeRows = D_8002FB10;
    } else {
        routeRows = D_8002FB70;
    }
    curSpeed = gCurrentActor->speedXZ;
    oscSpeed = mathSinF(gCurrentActor->floorSlopeFactor * 11.4) * 20.0f;
    zone = &gBehaviourZone->entries[gBehaviourWorkState->waypointIndex];
    vx = gCurrentActor->x - zone->x;
    vz = gCurrentActor->z - zone->z;
    dist = sqrtf(vz * vz + vx * vx);
    zone = &gBehaviourZone->entries[gBehaviourWorkState->waypointIndex];
    if (dist < zone->radius) {
        if ((zone->y < gCurrentActor->y ? gCurrentActor->y - zone->y : -(gCurrentActor->y - zone->y)) < 80.0f && gBehaviourWorkState->waypointIndex < gBehaviourZone->entryCount - 1) {
            if (routeRows[routeRowIdx].waypoint == gBehaviourWorkState->waypointIndex) {
                gCurrentActor->accelY = routeRows[routeRowIdx].gravity;
                if (routeRows[routeRowIdx].action == 1) {
                    actorScriptStart(gCurrentActor, 0x286);
                    gCurrentActor->speedY = 200.0f;
                    gCurrentActor->state += 1;
                }
                gBehaviourWorkState->routeRow += 1;
            }
            gBehaviourWorkState->waypointIndex++;
        }
    }
    zone = &gBehaviourZone->entries[gBehaviourWorkState->waypointIndex];
    speedDelta = (zone->height - gCurrentActor->speedXZ / 10.0f) * 0.8;
    heightAdjust = (gCurrentActor->y - gActivePlayerActor->y) * 0.25;
    if (heightAdjust > 6.0f) {
        heightAdjust = 6.0f;
    }
    if (heightAdjust < -6.0f) {
        heightAdjust = -6.0f;
    }
    speedDelta += heightAdjust;
    yawDiff = mathAtan2(-vx, -vz) * 4096.0 / 6.2831854820251465;
    yawDiff -= gCurrentActor->moveYaw;
    if (yawDiff >= 0x800) {
        yawDiff -= 4096.0;
    }
    if (yawDiff < -0x800) {
        yawDiff += 4096.0;
    }
    turnDelta = (gCurrentActor->speedXZ * yawDiff) / 10000.0;
    vx = mathSinF(gCurrentActor->moveYaw) * curSpeed; // FAKE: vx/vz (the waypoint offset) reused for the velocity; separate dx/dz offset locals grow .text by 0x50
    vz = mathCosF(gCurrentActor->moveYaw) * curSpeed;
    if (gCurrentActor->contactFlags & 1) {
        vx += mathSinF(gCurrentActor->floorSlopeYaw) * oscSpeed;
        vz += mathCosF(gCurrentActor->floorSlopeYaw) * oscSpeed;
    }
    vx += mathSinF(gCurrentActor->moveYaw) * speedDelta;
    vz += mathCosF(gCurrentActor->moveYaw) * speedDelta;
    vx += mathCosF(gCurrentActor->moveYaw) * turnDelta;
    vz -= mathSinF(gCurrentActor->moveYaw) * turnDelta;
    curSpeed = sqrtf(vx * vx + vz * vz);
    heading = mathAtan2(vx, vz);
    if (gCurrentActor->accelY != -20.0f && gCurrentActor->accelY != -360.0f) {
        gCurrentActor->speedXZ = gBehaviourZone->entries[gBehaviourWorkState->waypointIndex].height * 10.0;
    } else {
        gCurrentActor->speedXZ = curSpeed;
    }
    gCurrentActor->moveYaw = heading * 4096.0 / 6.2831854820251465;
    if (gCurrentActor->contactFlags & 1) {
        friction = (gCurrentActor->speedXZ * gCurrentActor->speedXZ) / 15000.0;
        gCurrentActor->speedXZ -= friction;
        if (gCurrentActor->speedXZ < 0.0f) {
            gCurrentActor->speedXZ = 0.0f;
        }
    }
}

typedef struct RaceCoinConfig { // component at Actor 0x17C of the coin-race opponent
    u8 pad0[4];
    RaceParticipant *rival;
    u8 pad8[0x18 - 0x8];
    union {
        s32 w;
        struct {
            s16 hi;
            s16 rewardFlag;
        } h;
    } reward;
    s32 requiredCoins;
} RaceCoinConfig;

extern u16 gMinigameCoinCount;

int raceCheckCoinRequirement(RaceParticipant *controller, RaceCoinConfig *config) {
    return controller->place != 0 && flagGet(config->reward.h.rewardFlag, 0) == 0 && gMinigameCoinCount >= config->requiredCoins;
}


typedef struct RaceCoinRacerActor {
    Actor base;
    RaceParticipant *participant;
    RaceCoinConfig *config;
} RaceCoinRacerActor;


extern Actor *gPrimaryPlayerActor;
s32 raceResultCamPathIds[5] = { 4, 1, 3, 2, 0 };


void raceOpponentBehaviourUpdate(void) {
    f32 dx;
    f32 dz;
    s16 ang16;
    s32 pathId;
    s32 pad;
    u8 rowIdx;
    RaceParticipant *controller;
    RaceCoinConfig *config;
    Actor *manager;
    RaceParticipant *managerData;
    RaceRouteEvent *routeRows;
    s32 flag;
    s32 callbackId;
    f32 yawDiff;
    f32 dist;
    f32 dy;
    u16 angU;

    controller = ((RaceCoinRacerActor *)gCurrentActor)->participant;
    config = ((RaceCoinRacerActor *)gCurrentActor)->config;
    manager = controller->actor;
    managerData = NULL;
    if (gCurrentMap == 0x52) {
        routeRows = D_8002FB10;
    } else {
        routeRows = D_8002FB70;
    }
    if (manager != NULL) {
        managerData = manager->customState;
    }
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->collisionMode = 0x1C;
        gCurrentActor->flags |= 0x10400;
        gCurrentActor->flags &= ~0x20000;
        gCurrentActor->state = 0;
        gCurrentActor->unk155 = 0;
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->accelY = -20.0f;
        gCurrentActor->terminalSpeedY = -900.0f;
        gCurrentActor->drawDistance = 0x7D0;
        gBehaviourWorkState->acceleration = 0;
        gBehaviourWorkState->timer = 0x64; // ORIG: the target stores 100 (sh t5,44(t6) at 0x7d0) before the 0 store at 0x7e0
        gBehaviourWorkState->timer = 0;
        gBehaviourWorkState->routeRow = 0;
        gCurrentActor->flags2 &= ~0x40;
        if (gCurrentMap == 0x52) {
            config->requiredCoins = gTextNumberArg = 0x32;
            config->reward.w = 0x103;
            flag = 0x65;
        } else {
            config->requiredCoins = gTextNumberArg = 0x32;
            config->reward.w = 0x4B;
            flag = 0x66;
        }
        if (flagGet(flag, 2) == 0 && flagGet(config->reward.h.rewardFlag, 0) == 0) {
            camStartPath(gCurrentActor, 0, 1);
            currentActorClearFlag();
            flagSet(flag, 1, 2);
        } else {
            controller->statusStep = 3;
        }
    }
    rowIdx = gBehaviourWorkState->routeRow;
    if (managerData != NULL && controller->raceStatus < 3 && gActorGlobalState.bossFightPhase == 4) {
        playerStateQueueCallback(0x33, gCurrentActor, 0);
    }
    if (controller->raceStatus < 3 && gCurrentActor->state == 2 && gActorGlobalState.bossFightPhase == 5) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1CA, 0xFF, 0x7F, 0xA);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x209, 0xFF, 0x7F, 0xA);
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->state = 0x14;
        gCurrentActor->accelY = -40.0f;
        gCurrentActor->speedY = 400.0f;
    }
    if (playerIsDamageOrKnockbackState() != 0) {
        gCurrentActor->interactionType = 1;
    } else {
        gCurrentActor->interactionType = 2;
    }
    switch (gCurrentActor->state) {
    case 20:
        gCurrentActor->roll = (gCurrentActor->roll - 0xC8) & 0xFFF;
        if ((gCurrentActor->contactFlags & 1) && gCurrentActor->speedY <= 0.0f) {
            gCurrentActor->state = 2;
            gCurrentActor->roll = 0;
        }
        break;
    case 0:
        if (managerData != NULL && managerData->phaseTimer == 0) {
            gCurrentActor->state++;
            gCurrentActor->unk155 = 0;
            gCurrentActor->contactFlags |= 0x200;
        }
        break;
    case 1:
        if (controller->raceStatus == 2) {
            if (gCurrentMap == 0x52) {
                actorSetTargetSpeed(gCurrentActor, 0x10E);
            } else {
                actorSetTargetSpeed(gCurrentActor, 0xAA);
            }
            gBehaviourWorkState->acceleration = 0xA;
            actorScriptStart(gCurrentActor, 0x282);
            gCurrentActor->state++;
            break;
        }
    case 2:
        actorApproachTargetSpeed(0);
        dx = gCurrentActor->x - gBehaviourZone->entries[gBehaviourWorkState->waypointIndex].x;
        dz = gCurrentActor->z - gBehaviourZone->entries[gBehaviourWorkState->waypointIndex].z;
        dist = sqrtf(dz * dz + dx * dx);
        if (dist < gBehaviourZone->entries[gBehaviourWorkState->waypointIndex].radius) {
            if (gBehaviourZone->entries[gBehaviourWorkState->waypointIndex].y < gCurrentActor->y) {
                dy = gCurrentActor->y - gBehaviourZone->entries[gBehaviourWorkState->waypointIndex].y;
            } else {
                dy = -(gCurrentActor->y - gBehaviourZone->entries[gBehaviourWorkState->waypointIndex].y);
            }
            if (dy < 80.0f) {
                if (gBehaviourWorkState->waypointIndex < gBehaviourZone->entryCount - 1) {
                    if (gBehaviourZone->entries[gBehaviourWorkState->waypointIndex].height == 0) {
                        actorScriptStart(gCurrentActor, 0x283);
                        gCurrentActor->state++;
                    }
                    if (gBehaviourWorkState->waypointIndex == routeRows[rowIdx].waypoint) {
                        gCurrentActor->accelY = routeRows[rowIdx].gravity;
                        gBehaviourWorkState->routeRow++;
                    }
                    gBehaviourWorkState->waypointIndex++;
                }
            }
        }
        ang16 = angU = (s32)(mathAtan2(-dx, -dz) * 4096.0 / 6.2831854820251465);
        mathAngleStepToward(&gCurrentActor->yaw, (angU + angU - gCurrentActor->moveYaw) & 0xFFF, 0x32);
        mathAngleStepToward(&gCurrentActor->moveYaw, ang16, 0xF);
        if (gBehaviourWorkState->waypointIndex == routeRows[gBehaviourWorkState->routeRow].waypoint && routeRows[gBehaviourWorkState->routeRow].action == 2 && controller->raceStatus == 3) {
            if (controller->place == 1) {
                gCurrentActor->state = 0xA;
            } else {
                gCurrentActor->state = 9;
            }
            actorScriptStart(gCurrentActor, 0);
            gCurrentActor->unk155 = 0;
        }
        break;
    case 3:
        actorApproachTargetSpeed(0x200);
        break;
    case 4:
        actorApproachTargetSpeed(0x200);
        gCurrentActor->speedY = 200.0f;
        gCurrentActor->state++;
        break;
    case 5:
        actorApproachTargetSpeed(0x200);
        break;
    case 6:
        if (gBehaviourWorkState->unk2E != 0) {
            gBehaviourWorkState->unk2E--;
        } else if (gCurrentActor->hasArcBounds != 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xFF, 0x46, 0x7F, 2);
            gBehaviourWorkState->unk2E = 0x14;
        }
        if (gBehaviourWorkState->waypointIndex == routeRows[gBehaviourWorkState->routeRow].waypoint && routeRows[gBehaviourWorkState->routeRow].action == 1) {
            yawDiff = gCurrentActor->moveYaw - gCurrentActor->yaw;
            if (yawDiff > 2048.0f) {
                yawDiff -= 4096.0f;
            }
            if (yawDiff < -2048.0f) {
                yawDiff += 4096.0f;
            }
            if (yawDiff > 50.0f) {
                yawDiff = 50.0f;
            }
            if (yawDiff < -50.0f) {
                yawDiff = -50.0f;
            }
            gBehaviourWorkState->timer += yawDiff;
            gBehaviourWorkState->timer -= gBehaviourWorkState->timer * 0.3;
        } else {
            if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
                actorScriptStart(gCurrentActor, 0x285);
                gCurrentActor->accelY = -20.0f;
            }
            yawDiff = gCurrentActor->moveYaw - gCurrentActor->floorSlopeYaw;
            if (yawDiff > 2048.0f) {
                yawDiff -= 4096.0f;
            }
            if (yawDiff < -2048.0f) {
                yawDiff += 4096.0f;
            }
            gBehaviourWorkState->timer += (yawDiff * gCurrentActor->speedXZ) / 8000.0;
            if (gBehaviourWorkState->timer > 500) {
                gBehaviourWorkState->timer = 500;
            }
            if (gBehaviourWorkState->timer < -500) {
                gBehaviourWorkState->timer = -500;
            }
        }
        gCurrentActor->yaw = (gCurrentActor->yaw + gBehaviourWorkState->timer) & 0xFFF;
        raceOpponentFollowWaypoints();
        break;
    case 7:
        if (gCurrentMap == 0xE) {
            actorSetTargetSpeed(gCurrentActor, 0xB4);
        }
        raceOpponentFollowWaypoints();
        break;
    case 8:
        gCurrentActor->state = 2;
        gCurrentActor->yaw = gCurrentActor->moveYaw;
        break;
    case 9:
        gBehaviourWorkState->acceleration = 8;
        actorSetTargetSpeed(gCurrentActor, 0);
        actorApproachTargetSpeed(0x200);
        if (gCurrentActor->unk155 == 0) {
            actorScriptStart(gCurrentActor, 0x287);
            gCurrentActor->unk155++;
        }
        break;
    case 10:
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            gBehaviourWorkState->acceleration = 8;
            gCurrentActor->unk155 = 1;
            break;
        case 1:
            if (gCurrentActor->speedXZ == 0.0f) {
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            gBehaviourWorkState->acceleration = 0;
            actorScriptStart(gCurrentActor, 0x288);
            gCurrentActor->unk155++;
            break;
        }
        actorApproachTargetSpeed(0x200);
        break;
    }
    switch (controller->raceStatus) {
    case 0:
        switch (controller->statusStep) {
        case 0:
            if (gCurrentActor->flags & 0x02000000) {
                controller->statusStep++;
            }
            break;
        case 1:
            if (!(gCurrentActor->flags & 0x02000000)) {
                camResumePath();
                controller->statusStep++;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                controller->statusStep++;
            }
            break;
        }
        if (controller->statusStep < 3) {
            raceSetIntroCutscenePhase(manager);
        }
        break;
    case 1:
        if (controller->statusStep == 0) {
            slotQueueUpdate(0xB, 1, 0);
            controller->statusStep++;
        }
        break;
    case 3:
        if (controller->statusStep == 0) {
            callbackId = 0x55;
            if (gPrimaryPlayerActor->contactFlags & 0x200) {
                callbackId = 0x56;
            }
            playerStateQueueCallback(callbackId, NULL, 0);
            controller->statusStep++;
        }
        break;
    case 4:
        if (controller->statusStep == 0) {
            slotQueueCancel(0xB, 0);
            controller->unkD0 = 0;
            if (flagGet(config->reward.h.rewardFlag, 0) == 0) {
                pathId = raceResultCamPathIds[raceCheckLapCompletionThreshold(controller, config->rival, config->requiredCoins)];
                camStartPath(gCurrentActor, pathId, 1);
                currentActorClearFlag();
            } else {
                mapCheckAutoTransition();
            }
            controller->statusStep++;
        }
        break;
    case 5:
        switch (controller->statusStep) {
        case 0:
            if (flagGet(config->reward.h.rewardFlag, 0) == 0) {
                sfxStopSlotSound(gActivePlayerActor, 0);
                playerStateQueueCallback(0x55, NULL, 0);
                gCurrentActor->speedXZ = 0.0f;
                if (raceCheckCoinRequirement(controller, config) != 0) {
                    gCurrentActor->state = 0xA;
                    gCurrentActor->unk155 = 0;
                } else {
                    gCurrentActor->state = 9;
                    gCurrentActor->unk155 = 0;
                }
            }
            controller->statusStep++;
            break;
        case 1:
            if (gCurrentActor->flags & 0x02000000) {
                controller->statusStep++;
            }
            break;
        case 2:
            if (!(gCurrentActor->flags & 0x02000000)) {
                camResumePath();
                if (raceCheckCoinRequirement(controller, config) == 0) {
                    controller->statusStep = 4;
                }
                controller->statusStep++;
                gCurrentActor->unk15F = 0;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (gCurrentMap == 0xE) {
                    csModelStateSetFirstByte(0x48, 0xA);
                } else {
                    csModelStateSetFirstByte(1, 0xA);
                }
                controller->statusStep++;
            }
            break;
        case 4:
            if (flagGet(config->reward.h.rewardFlag, 0) != 0) {
                controller->statusStep++;
            }
            break;
        case 5:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (flagGet(config->reward.h.rewardFlag, 0) != 0) {
                    mapCheckAutoTransition();
                } else {
                    hudSpawnTextScreen(1);
                }
                controller->statusStep++;
            }
            break;
        }
        break;
    }
    actorApplyGravity();
    actorStepPhysics(gCurrentActor, gCurrentActor->moveYaw, gCurrentActor->moveYaw);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x96, 0x78, 0, 1.0f);
    if (controller->raceStatus == 2) {
        raceUpdateLapAndWaypointTracker(controller);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
