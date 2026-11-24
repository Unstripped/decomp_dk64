#include "common.h"
#include "actor.h"
#include "sched.h"
#include "text.h"
#include "proto/global/104F0_eeprom.h"
#include "proto/global/112080_resource_parse.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
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
#include "proto/global/5E2F0_light.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/90D80_render_callbacks.h"
#include "proto/global/A2F10.h"
#include "proto/global/ACDC0_pause_menu.h"
#include "proto/global/B7490_enemy_swim_fly.h"
#include "proto/global/C4620_npc_kongs.h"
#include "proto/global/C8C10.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/FCCD0_slot_queue.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;

// Actor types with more than one component keep per-type pointers from 0x178 on (see Actor in actor.h).
typedef struct ComponentActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ s16 *secondComponent;
    /* 0x17C */ u8 pad17C[4];
    /* 0x180 */ s16 *fourthComponent;
} ComponentActor;

#define COMPONENT_ACTOR ((ComponentActor *)gCurrentActor)

extern PlayerStruct *gPlayerSlots;

extern s32 gCurrentMap;


void actorCarryMiniPlayerUpdate(u8 startActionId, u8 exitActionId, u8 camPathId) {
    s16 *hoverHeightPtr = COMPONENT_ACTOR->secondComponent;

    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x20;
        if (camPathId) {
            camStartPath(gCurrentActor, camPathId, 1);
        } else {
            camSetTargetCutsceneUnscaled(gCamActor, gCurrentActor, 4, 0x800, 0x19, 0, 0xA, 0x14, 0xC, 0, 0.1f);
        }
        gBehaviourExtraState->actorState = 0x27;
        gCurrentActor->state = 0x27;
        gCurrentActor->subState = 0;
    }
    {
        s32 deltaHeight = gBehaviourWorkState->targetY - gBehaviourExtraState->y;

        if (deltaHeight < 0) {
            *hoverHeightPtr = 0;
        } else {
            *hoverHeightPtr = deltaHeight;
        }
    }
    switch (gCurrentActor->state) {
        case 0x27:
            if ((gBehaviourWorkState->flags & 4) && (gBehaviourWorkState->waypointIndex & 0x7F) == startActionId) {
                if (gPlayerSlots->sizeMode == 0) {
                    resQueueAttachActor(gCurrentActor, 0x10, 1);
                    gCurrentActor->state = 0x29;
                    gCurrentActor->subState = 0;
                    gBehaviourExtraState->actorState = 0x29;
                    gActivePlayerState->stateFlags |= 0x10000;
                    playerStateQueueCallback(0x54, 0, 0);
                    gBehaviourWorkState->flags |= 0x8000;
                } else {
                    resQueueAttachActor(gCurrentActor, 0x10, 0);
                    gCurrentActor->state = 0x28;
                    gCurrentActor->subState = 0;
                    gBehaviourExtraState->actorState = 0x28;
                    if (!camPathId) {
                        camSetTarget(gCamActor, gCurrentActor, 4, 0x800, 0x19, 0, 0xA, 0x14, 0xC, 0x78, 0.1f);
                    }
                }
            }
        case 0x28:
            actorAirPatrolStep(2, 0x23D, 0x23E);
            break;
        case 0x26:
        case 0x29:
            if (gBehaviourWorkState->flags & 0x8000) {
                if ((gBehaviourWorkState->flags & 4) && (gBehaviourWorkState->waypointIndex & 0x7F) == exitActionId) {
                    if (!camPathId) {
                        camSetFollowMode(gCamActor);
                    }
                    camStartPath(gPrimaryPlayerActor, 3, 5);
                    gCurrentActor->state = 0x28;
                    gCurrentActor->subState = 0;
                    gBehaviourExtraState->actorState = 0x28;
                    gActivePlayerState->stateFlags &= ~0x10000;
                    gBehaviourWorkState->flags &= ~0x8000;
                } else {
                    if (!camPathId) {
                        camSetTarget(gCamActor, gPrimaryPlayerActor, 4, gFrameCounter * 20, 0x1E, 0, 0xA, 0x1E, 0xC, 0, 0.2f);
                    }
                    gPrimaryPlayerActor->yaw = gCurrentActor->yaw;
                    gPrimaryPlayerActor->x = gCurrentActor->x;
                    gPrimaryPlayerActor->y = gCurrentActor->y - 2.0f;
                    gPrimaryPlayerActor->z = gCurrentActor->z;
                    gPrimaryPlayerActor->contactFlags &= ~1;
                    gPrimaryPlayerActor->attachMode = 0;
                }
            }
            actorAirPatrolStep((gCurrentActor->state == 0x26) ? 0x26 : 2, 0x23D, 0x23E);
            break;
        case 0:
            break;
    }
}


void actorRestoreMapMusic(void) {
    s32 sfx = 0;

    switch (gCurrentMap) {
        case 6:
            sfx = 3;
            break;
        case 0x6A:
            sfx = 0x6A;
            break;
        case 0x37:
            sfx = 0x4A;
            break;
    }
    if (sfx != 0) {
        sfxAllocateChannel(sfx, 1.0f);
    }
}


void actorCountGoalRewardUpdate(s32 startPathId, s32 lowCountPathId, s32 rewardPathId, s32 startSpawnId, s32 goalSpawnId, s32 targetCount, s32 rewardFlag) {
    s16 *heightOffsetPtr = COMPONENT_ACTOR->secondComponent;
    PlayerState *playerState = gPlayerSlots->actor->customState;
    Actor *attachedActor = playerState->actor;
    s32 pathId;

    gTextNumberArg = targetCount;
    lightAdd(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0.0f, 0.0f, 0.0f, 80.0f, 0, 0xFF, 0xFF, 0xFF);
    if (!(gCurrentActor->flags & 0x10)) {
        pathId = -1;
        if (flagGet(rewardFlag, 0) != 0 || menuIsTransitionType3Or4() != 0) {
            if (gBehaviourExtraState->id == startSpawnId) {
                actorRestoreMapMusic();
            }
            gCurrentActor->state = 0x40;
            return;
        }
        actorAllocBoneRotations(1, 1);
        if (gBehaviourExtraState->id == startSpawnId) {
            pathId = startPathId;
        } else {
            playerStateQueueCallback(0x46, 0, 0);
            if (slotQueueGetValue(0xB, 0) < targetCount) {
                gCurrentActor->goalMetAndPhase = 0;
                pathId = lowCountPathId;
            } else {
                if (flagGet(rewardFlag, 0) == 0) {
                    pathId = rewardPathId;
                }
                gCurrentActor->goalMetAndPhase = 0x80;
            }
        }
        *heightOffsetPtr = 0xF;
        if (pathId >= 0) {
            camStartPath(NULL, pathId, 1);
        }
        if (attachedActor != NULL) {
            attachedActor->yawSpeed = 0;
        }
    }
    if (gBehaviourExtraState->id == goalSpawnId && (gCurrentActor->goalMetAndPhase & 0x80) && gBehaviourWorkState->timer == 0x5A && flagGet(rewardFlag, 0) == 0) {
        actorSpawnNodeEntryAtActor(0x2D, rewardFlag);
        sfxAllocateChannel(0x14, 1.0f);
    }
    actorPlaceAttachedChildren(-0x1E);
    actorTrackBoneTowardTarget(0);
    gCurrentActor->yaw = (gBehaviourTargetActor->yaw + 0x800) & 0xFFF;
    gCurrentActor->x = mathSinF(gCurrentActor->moveYaw) * 12.0f + gBehaviourTargetActor->x;
    gCurrentActor->z = mathCosF(gCurrentActor->moveYaw) * 15.0f + gBehaviourTargetActor->z;
    gCurrentActor->y = gBehaviourTargetActor->y + *heightOffsetPtr + mathSinF(gFrameCounter * 100) * 5.0f;
    gCurrentActor->moveYaw += 0x3C;
    switch (gCurrentActor->goalMetAndPhase & 0x7F) {
        case 0:
            if (!(gCurrentActor->flags & 0x2000000)) {
                gBehaviourWorkState->timer = 0x1E;
            } else {
                gCurrentActor->goalMetAndPhase++;
            }
            break;
        case 1:
            if (gCurrentActor->flags & 0x2000000) {
                gBehaviourWorkState->timer = 0x1E;
            } else {
                gCurrentActor->goalMetAndPhase++;
                if (gBehaviourExtraState->id == goalSpawnId && slotQueueGetValue(0xB, 0) >= targetCount) {
                    gBehaviourWorkState->timer = 0x78;
                }
            }
            break;
    }
    if (gBehaviourWorkState->timer != 0) {
        gBehaviourWorkState->timer--;
    }
    if (gBehaviourWorkState->timer == 0) {
        if (++*heightOffsetPtr >= 0x3D) {
            gCurrentActor->state = 0x40;
            actorRestoreMapMusic();
            if (gBehaviourExtraState->id == goalSpawnId) {
                if (flagGet(rewardFlag, 0) != 0 || slotQueueGetValue(0xB, 0) >= targetCount) {
                    mapCheckAutoTransition();
                } else {
                    hudSpawnTextScreen(1);
                }
            }
        }
    }
}

void minecartCoinGoalUpdateJungleJapes(void) {
    actorCountGoalRewardUpdate(0, 1, 2, 0xF, 0x10, 0x32, 0x18);
}

void minecartCoinGoalUpdateFungiForest(void) {
    actorCountGoalRewardUpdate(6, 7, 8, 0x10, 0xE, 0x32, 0xD7);
}

void minecartCoinGoalUpdateCreepyCastle(void) {
    actorCountGoalRewardUpdate(1, 2, 3, 4, 5, 0x19, 0x13E);
}


void actorPerMapCarrierUpdate(void) {
    behaviourFrameBegin();
    switch (gCurrentMap) {
        case 0x26:
            actorCarryMiniPlayerUpdate(2, 6, 0);
            break;
        case 6:
            minecartCoinGoalUpdateJungleJapes();
            break;
        case 0x37:
            minecartCoinGoalUpdateFungiForest();
            break;
        case 0x6A:
            minecartCoinGoalUpdateCreepyCastle();
            break;
        case 0x30:
            if (gBehaviourExtraState->id == 6) {
                actorCarryMiniPlayerUpdate(2, 7, 0x1A);
            } else {
                actorCarryMiniPlayerUpdate(2, 3, 0);
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern Actor *gSpawnedActor;


u8 actorSpawnNumberedTargetsUpdate(u16 spawnCooldown, u16 maxSpawns) {
    u8 ret = 0;
    s32 pad;
    s16 *cooldownPtr;
    s16 *hoverHeightPtr;
    f32 playerAngle;

    hoverHeightPtr = COMPONENT_ACTOR->secondComponent;
    cooldownPtr = COMPONENT_ACTOR->fourthComponent;
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x20;
        gCurrentActor->speedXZ = gBehaviourExtraState->targetSpeed;
    }
    {
        s32 deltaHeight = gBehaviourWorkState->targetY - gBehaviourExtraState->y;

        if (deltaHeight < 0) {
            *hoverHeightPtr = 0;
        } else {
            *hoverHeightPtr = deltaHeight;
        }
    }
    switch (gCurrentActor->state) {
        case 0x37:
            actorMoveWithinZone(0x37, 0.0f, 0.0f, 0x22, 0.0f);
            break;
        case 2:
        case 0x26:
            gActivePlayerState->stateFlags2 |= 0x40;
            playerAngle = mathAngleBetweenPointsDeg(gCurrentActor->x, gCurrentActor->z, gPrimaryPlayerActor->x, gPrimaryPlayerActor->z);
            gCurrentActor->arrowAngle = playerAngle - mathAngleBetweenPointsDeg(gPlayerSlots->focusX, gPlayerSlots->focusZ, gPlayerSlots->camX, gPlayerSlots->camZ);
            actorAirPatrolStep(gCurrentActor->state, gBehaviourAnimState->animId1, gBehaviourAnimState->animId2);
            gCurrentActor->targetNumber = maxSpawns - gBehaviourWorkState->timer + 1;
            if (gActorGlobalState.notifyReceived != 0) {
                if (gCurrentActor->targetNumber != gActorGlobalState.notifyValue[0]) {
                    ret = 1;
                } else {
                    gBehaviourWorkState->timer--;
                    if (gBehaviourWorkState->timer == 0) {
                        ret = 2;
                    }
                }
            }
            if (gPlayerCharacterId[0] != 1) {
                ret = 1;
            }
            if (*cooldownPtr != 0) {
                (*cooldownPtr)--;
            } else if (gCurrentActor->yawSpeed < maxSpawns) {
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x1DD, 0xFF, 0x7F, 0x14, 0x14, 0.0f, 0);
                actorSpawn(0x18, 0);
                gCurrentActor->yawSpeed++;
                gSpawnedActor->targetNumber = gCurrentActor->yawSpeed;
                gSpawnedActor->x = gCurrentActor->x;
                gSpawnedActor->y = gCurrentActor->y - 10.0f;
                gSpawnedActor->z = gCurrentActor->z;
                gSpawnedActor->yaw = gCurrentActor->yaw;
                gSpawnedActor->parentActor = gCurrentActor;
                *cooldownPtr = spawnCooldown;
            }
            renderCallbacksRegister(actorDrawAnimatedEffect, gCurrentActor, 3);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    return ret;
}


void targetGameHideCounter(void) {
    slotQueueSetDisplayMode(5, 0, 0);
}


void targetGameEndRound(void) {
    csModelStateSetFirstByte(0x2C, 0xB);
    targetGameHideCounter();
}


void actorStartRewardCutscene(u8 subAction, u8 succeeded) {
    gBehaviourWorkState->countdown = 0;
    resQueueSetValue(1);
    resQueueAttachActor(gCurrentActor, 0xF, subAction);
    gCurrentActor->state = 0x29;
    gCurrentActor->subState = 0;
    gCurrentActor->yawSpeed = succeeded;
    gCurrentActor->movePitch = 0;
}

void actorTargetGameHostUpdate(void) {
    s32 pad;
    s16 *cooldownPtr;
    f32 dx;
    f32 dy;
    f32 dz;

    cooldownPtr = COMPONENT_ACTOR->fourthComponent;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->state = 0x1E;
        behaviourSetAnimIds(0x244, 0x244, 0x246);
        gCurrentActor->eyeHeight = gCurrentActor->eyeHeight / 2.0;
    }
    gActivePlayerState->stateFlags2 &= ~0x40;
    switch (gCurrentActor->state) {
        case 0:
        case 0xE:
        case 0xF:
        case 0x1E:
            actorScriptedCommandUpdate();
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(0x2D, 0x14);
                gCurrentActor->drawDistance = 0x3E8;
                gBehaviourAnimState->flags |= 0x24;
                resQueueAttachActor(gCurrentActor, 0xF, 0);
                actorScriptStart(gCurrentActor, 0x244);
                gCurrentActor->state = 0x27;
                gBehaviourWorkState->countdown = 0xF0;
            }
            break;
        case 0x27:
            gActivePlayerState->stateFlags2 |= 0x40;
            actorAirPatrolStep(2, 0x244, 0x246);
            if ((gBehaviourWorkState->flags & 4) && ((gBehaviourWorkState->waypointIndex & 0x7F) == 3)) {
                gCurrentActor->state = 0x28;
                gCurrentActor->subState = 0;
                actorScriptStart(gCurrentActor, 0x244);
            }
            break;
        case 0x28:
            gActivePlayerState->stateFlags2 |= 0x40;
            switch (gCurrentActor->subState) {
                case 0:
                case 1:
                case 2:
                    if (gCurrentActor->floorY + 10.0f < gCurrentActor->y) {
                        gCurrentActor->y -= 2.0f;
                    }
                    dx = gPrimaryPlayerActor->x - gCurrentActor->x;
                    dy = gPrimaryPlayerActor->y - gCurrentActor->y;
                    dz = gPrimaryPlayerActor->z - gCurrentActor->z;
                    if (dx * dx + dy * dy + dz * dz < 6400.0f) {
                        gCurrentActor->subState = 3;
                        camStartPath(gCurrentActor, 0x1A, 1);
                        actorScriptStart(gCurrentActor, 0x245);
                    } else if (gBehaviourWorkState->countdown != 0) {
                        gBehaviourWorkState->countdown--;
                    } else {
                        gCurrentActor->state = 0x29;
                        gCurrentActor->subState = 0;
                        gBehaviourWorkState->countdown = 0;
                        resQueueSetValue(1);
                        resQueueAttachActor(gCurrentActor, 0xF, 2);
                    }
                    break;
                case 3:
                    if (camIsCutsceneActive() == 0) {
                        csModelStateSetFirstByte(0x2C, 0x1E);
                        *cooldownPtr = 0x78;
                        gBehaviourWorkState->timer = 0xA;
                        gCurrentActor->state = 2;
                        gCurrentActor->subState = 0;
                        slotQueueSetDisplayMode(5, 0, 1);
                        actorScriptStart(gCurrentActor, 0x244);
                    }
                    break;
            }
            behaviourUpdateShadowAlpha();
            break;
        case 0x29:
            if (gCurrentActor->movePitch == 0) {
                camStartPath(gCurrentActor, 0x1C, 1);
                gCurrentActor->movePitch++;
            } else if (camIsCutsceneActive() == 0) {
                if (gCurrentActor->yawSpeed == 0) {
                    targetGameEndRound();
                    hudSpawnTextScreen(3);
                    gCurrentActor->state = 0x2A;
                    gCurrentActor->subState = 0;
                } else if (gCurrentActor->movePitch == 1) {
                    csModelStateSetFirstByte(0xEB, 0xA);
                    gCurrentActor->movePitch++;
                }
                gCurrentActor->y += 3.0f;
                gBehaviourWorkState->countdown++;
                if (gBehaviourWorkState->countdown >= 0x83) {
                    gBehaviourAnimState->flags &= ~4;
                    targetGameEndRound();
                    gCurrentActor->state = 0x3C;
                }
            }
            behaviourUpdateShadowAlpha();
            break;
        case 0x2A:
            volumeTriggerApplyActorState();
            break;
        case 0x30:
            gCurrentActor->yaw = 0xA82;
            gPrimaryPlayerActor->yaw = 0xA82;
            zoneEntryGetPosition(8, 2, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
            actorClearMovementFlags(gPrimaryPlayerActor);
            zoneEntryGetPosition(8, 2, &gPrimaryPlayerActor->x, &gPrimaryPlayerActor->y, &gPrimaryPlayerActor->z);
            gPrimaryPlayerActor->y -= 25.0f;
            gCurrentActor->state = 0x28;
            gCurrentActor->subState = 0;
            actorScriptStart(gCurrentActor, 0x244);
            gBehaviourWorkState->waypointIndex = 2;
            slotQueueSetDisplayMode(5, 0, 1);
            break;
    }
    switch (actorSpawnNumberedTargetsUpdate(0x78, 0xA)) {
        case 1:
            actorStartRewardCutscene(2, 0);
            break;
        case 2:
            actorStartRewardCutscene(3, 1);
            break;
    }
    currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
}

void actorBehaviourNoop(void) {
}

void actorGatedTargetGameHostUpdate(void) {
    s32 pad;
    s16 *cooldownPtr;
    f32 dx;
    f32 dz;

    cooldownPtr = COMPONENT_ACTOR->fourthComponent;
    behaviourFrameBegin();
    if (!(gActivePlayerState->stateFlags & 0x100000)) {
        gCurrentActor->state = 0x40;
        return;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        behaviourSetAnimIds(0x357, 0x357, 0x359);
        gBehaviourAnimState->flags |= 0x20;
        gCurrentActor->state = 0x1E;
        gCurrentActor->drawDistance = 0x3E8;
        currentActorAnimFinish(0);
    }
    switch (gCurrentActor->state) {
        case 0x1E:
            effectSpawnSmoke(1);
            volumeTriggerApplyActorState();
            break;
        case 0x27:
            switch (gCurrentActor->subState) {
                case 0:
                    if (camIsCutsceneActive() == 0) {
                        currentActorAnimSetFrame(0, 0);
                        camStartPath(gCurrentActor, 0x13, 1);
                        gCurrentActor->subState++;
                    }
                    break;
                case 1:
                    if (currentActorTestClearFlag() != 0) {
                        actorScriptStart(gCurrentActor, 0x354);
                        gCurrentActor->subState++;
                    }
                    break;
                case 3:
                    resQueueAttachActor(gCurrentActor, 0x15, 0);
                    gCurrentActor->subState++;
                    break;
                case 4:
                    if (!(gCurrentActor->flags & 0x2000000)) {
                        camResumePath();
                        gCurrentActor->state = 0x28;
                    }
                    break;
            }
            break;
        case 0x28:
            if (gPrimaryPlayerActor->state == 0x63) {
                dx = gCurrentActor->x - gPrimaryPlayerActor->x;
                dz = gCurrentActor->z - gPrimaryPlayerActor->z;
                if (dx * dx + dz * dz < 10000.0f) {
                    camStartPath(gCurrentActor, 0x15, 1);
                    resQueueAttachActor(gCurrentActor, 0x15, 1);
                    gCurrentActor->state = 0x29;
                    gCurrentActor->subState = 0;
                }
            }
            break;
        case 0x29:
            switch (gCurrentActor->subState) {
                case 0:
                    if (!(gCurrentActor->flags & 0x2000000)) {
                        actorScriptStart(gCurrentActor, 0x358);
                        gCurrentActor->subState = 1;
                    }
                    break;
                case 2:
                    camResumePath();
                    gBehaviourAnimState->flags |= 0x24;
                    gCurrentActor->state = 2;
                    slotQueueSetDisplayMode(5, 0, 1);
                    slotQueueUpdate(5, 1, 0);
                    *cooldownPtr = 0x78;
                    gBehaviourWorkState->timer = 0x10;
                    gCurrentActor->yawSpeed = 0;
                    actorScriptStart(gCurrentActor, 0x357);
                    break;
            }
            break;
        case 0x2A:
            switch (gCurrentActor->subState) {
                case 0:
                    gCurrentActor->pitch = 0;
                    gCurrentActor->roll = 0;
                    if (!(gCurrentActor->flags & 0x2000000)) {
                        camResumePath();
                        targetGameHideCounter();
                        if (gCurrentActor->sub4->animId == 0x35A && gPrimaryPlayerActor->state == 0x63) {
                            hudSpawnTextScreen(4);
                            gCurrentActor->subState = 3;
                        } else {
                            gCurrentActor->subState++;
                            gCurrentActor->flags &= ~0x8000;
                        }
                    }
                    break;
                case 1:
                    behaviourFadeOutWithinZone(5);
                    break;
                case 2:
                    gCurrentActor->state = 0x3C;
                    break;
                case 3:
                    volumeTriggerApplyActorState();
                    break;
            }
            break;
        case 0x30:
            actorScriptStart(gCurrentActor, 0x355);
            actorSetPositionFromPoint(gCurrentActor, gBehaviourExtraState);
            gBehaviourWorkState->waypointIndex = 0;
            gCurrentActor->yawSpeed = 0;
            actorClearMovementFlags(gPrimaryPlayerActor);
            gPrimaryPlayerActor->y = gCurrentActor->y;
            gPrimaryPlayerActor->x = mathSinF(gCurrentActor->yaw) * 50.0f + gCurrentActor->x;
            gPrimaryPlayerActor->z = mathCosF(gCurrentActor->yaw) * 50.0f + gCurrentActor->z;
            gPrimaryPlayerActor->yaw = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, gPrimaryPlayerActor->x, gPrimaryPlayerActor->z);
            camStartPath(gCurrentActor, 0x15, 1);
            resQueueAttachActor(gCurrentActor, 0x15, 1);
            gCurrentActor->state = 0x29;
            gCurrentActor->subState = 0;
            break;
    }
    gActivePlayerState->stateFlags2 &= ~0x40;
    switch (actorSpawnNumberedTargetsUpdate(0x78, 0x10)) {
        case 1:
            actorSetPositionFromPoint(gCurrentActor, gBehaviourExtraState);
            resQueueAttachActor(gCurrentActor, 0x15, 2);
            actorScriptStart(gCurrentActor, 0x35A);
            gCurrentActor->state = 0x2A;
            gCurrentActor->subState = 0;
            camStartPath(gCurrentActor, 0x16, 1);
            break;
        case 2:
            actorSetPositionFromPoint(gCurrentActor, gBehaviourExtraState);
            resQueueAttachActor(gCurrentActor, 0x15, 3);
            actorScriptStart(gCurrentActor, 0x35B);
            gCurrentActor->state = 0x2A;
            gCurrentActor->subState = 0;
            camStartPath(gCurrentActor, 0x14, 1);
            break;
    }
    if (gCurrentActor->state != 0x1E) {
        currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame);
    }
}

// customState of the cutscene actor run by cutsceneRestoreUpdate: what it restores when the scene ends.
typedef struct CutsceneRestoreState {
    /* 0x00 */ f32 savedLightR;
    /* 0x04 */ f32 savedLightG;
    /* 0x08 */ f32 savedLightB;
    /* 0x0C */ Actor *helperActor;
    /* 0x10 */ Actor *player;
    /* 0x14 */ s16 savedPitch;
    /* 0x16 */ s16 savedRoll;
    /* 0x18 */ u8 pad18[2];
    /* 0x1A */ s16 lightChunk;
    /* 0x1C */ s16 frameCount;
    /* 0x1E */ s8 phase;
} CutsceneRestoreState;


extern s16 gCurrentLevelIndex;
extern s32 gEffectSpriteSparklesBlue;
extern s16 gPhotoSubjectDepthDist;
extern s16 gPhotoSubjectScreenX;
extern s16 gPhotoSubjectScreenY;

void actorPhotoSubjectUpdate(void) {
    f32 screenX;
    f32 screenY;
    f32 dist;
    f32 dz;
    s32 flagIndex;
    f32 dx;

    behaviourFrameBegin();
    actorClearMovementFlags(gCurrentActor);
    if (!(gCurrentActor->flags & 0x10)) {
        gBehaviourAnimState->flags |= 0x40;
        gCurrentActor->drawDistance = 0xFA;
        actorAllocBoneRotations(2, 1);
    }
    if ((randomNonNegative() >> 15) % 1000 >= 971) {
        gCurrentActor->speedXZ = gBehaviourExtraState->targetSpeed << 2;
    }
    actorTrackBoneTowardTarget(6);
    actorMoveWithinZone(1, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x2C9, 0.0f);
    if (!(gFrameCounter & 3)) {
        effectSetDepth(1);
        effectSetCallback(effectShrinkFadeMatrixUpdate);
        effectCreateAtPosition(&gEffectSpriteSparklesBlue, 1.6f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
    }
    if (!(gActivePlayerState->stateFlags & 0x8000)) {
        dz = gPlayerSlots->camZ - gCurrentActor->z;
        dx = gPlayerSlots->camX - gCurrentActor->x;
        dist = sqrtf(dz * dz + dx * dx) - gPlayerSlots->nearClip;
        if (gPhotoSubjectScreenX >= 0x8A && gPhotoSubjectScreenX < 0xB1 && gPhotoSubjectScreenY >= 0x61 && gPhotoSubjectScreenY < 0x88 && dist < gPhotoSubjectDepthDist) {
            if (gActivePlayerState->photoSubjectStatus != 1) {
                if (behaviourIsTargetWithinAngle(0x1388) != 0) {
                    actorScriptStart(gCurrentActor, 0x2B6);
                }
            }
            gActivePlayerState->photoSubjectStatus = 1;
        } else {
            if (gActivePlayerState->photoSubjectStatus != 2) {
                actorScriptStart(gCurrentActor, 0x2B5);
            }
            gActivePlayerState->photoSubjectStatus = 2;
        }
    }
    if ((gActivePlayerState->stateFlags & 0x8000) && gActivePlayerState->photoSubjectStatus == 1) {
        if (gCurrentActor->state != 0x40) {
            flagSet(spawnFlagLookup(gCurrentLevelIndex, spawnNodeIdForActor(gCurrentActor), &flagIndex), 1, 0);
            eepromSavePlayerData();
        }
        gCurrentActor->state = 0x40;
    }
    if (gCurrentActor->state != 0x40) {
        sfxAllocateChannel(0x42, 1.0f);
    } else {
        sfxStopChannel(0x42, 0);
    }
    camProjectToScreen(gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z, &screenX, &screenY, 0, 1.0f, 0);
    gPhotoSubjectScreenX = screenX;
    gPhotoSubjectScreenY = screenY;
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void cutsceneRestoreUpdate(void) {
    CutsceneRestoreState *restore;

    restore = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        restore->frameCount = 0;
        gCurrentActor->flags |= 0x400;
    }
    restore->frameCount++;
    switch (restore->phase) {
        case 1:
            if (gPrimaryPlayerActor->subState == 3) {
                resQueueAttachActor(gCurrentActor, 0x1E, 3);
                restore->phase = 2;
            } else if (restore->player->state != 0x83) {
                restore->phase = 3;
            }
            break;
        case 2:
            if (!(gCurrentActor->flags & 0x2000000)) {
                restore->phase = 3;
                camResumePath();
            }
            break;
        default:
            if (restore->player->state != 0x83) {
                ((PlayerState *)restore->player->customState)->stateFlags2 &= ~0x10;
                restore->player->flags &= ~0x40000000;
                restore->player->flags |= 1;
                restore->player->roll = restore->savedRoll;
                restore->player->pitch = restore->savedPitch;
                gGlobalPauseFlags |= 0x10030;
                lightSetColor(restore->savedLightR, restore->savedLightG, restore->savedLightB, restore->lightChunk);
                sfxStopChannel(0x3B, 0);
                actorDespawn(restore->helperActor);
                actorDespawn(gCurrentActor);
                return;
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void actorPresentBeforePlayerUpdate(void) {
    f32 frontX;
    f32 frontZ;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->hoverHeight = 0x3C;
        actorScriptStart(gCurrentActor, 0x23D);
        if (gPrimaryPlayerActor->state == 0xC) {
            actorScriptStartByIndex(gPrimaryPlayerActor, 0x87);
        }
    }
    frontX = mathSinF(gPrimaryPlayerActor->yaw) * 50.0f + gPrimaryPlayerActor->x;
    frontZ = mathCosF(gPrimaryPlayerActor->yaw) * 50.0f + gPrimaryPlayerActor->z;
    gCurrentActor->yaw = (gPrimaryPlayerActor->yaw + 0x800) & 0xFFF;
    if (gCurrentActor->hoverHeight == 0x3C) {
        gCurrentActor->x = mathSinF(gCurrentActor->moveYaw) * 10.0f + frontX;
        gCurrentActor->z = mathCosF(gCurrentActor->moveYaw) * 10.0f + frontZ;
    }
    gCurrentActor->y = mathSinF(gFrameCounter * 100) * 5.0f + (gCurrentActor->itemRaise + gPrimaryPlayerActor->y + 3.0f + gCurrentActor->hoverHeight);
    if (!(gCurrentActor->flags & 0x10)) {
        if (gCurrentActor->movePitch != 0) {
            gCurrentActor->itemRaise = 0x14;
            actorSpawnNodeEntryAtActor(0x2D, flagLookupIdByIndex(gCurrentActor->movePitch));
        }
    }
    if (gCurrentActor->movePitch != 0) {
        actorPlaceAttachedChildren(-0x1E);
    }
    gCurrentActor->moveYaw += 60.0f * mathSinF(gFrameCounter * 50);
    if (gCurrentActor->flags & 0x2000000) {
        gCurrentActor->yawSpeed = 0x14;
    }
    if (gCurrentActor->yawSpeed != 0) {
        gCurrentActor->yawSpeed--;
    }
    if (gCurrentActor->yawSpeed == 0) {
        gCurrentActor->hoverHeight++;
        if (gCurrentActor->hoverHeight >= 0x3D) {
            if (gCurrentActor->movePitch != 0) {
                actorAttachChildCallbacks();
            }
            actorDespawn(gCurrentActor);
            camResumePath();
            if (gPrimaryPlayerActor->state == 0xC) {
                actorScriptStartByIndex(gPrimaryPlayerActor, 9);
            }
        }
    } else if (gCurrentActor->hoverHeight >= 0x10) {
        gCurrentActor->hoverHeight--;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
