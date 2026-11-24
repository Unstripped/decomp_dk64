#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/103AB0_view_effects.h"
#include "proto/global/10D2D0_health_hud.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/133A90_prox_path.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2C910.h"
#include "proto/global/2DE90_screen_wipe.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/450_main_loop.h"
#include "proto/global/55B20_map_chunk.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/61AA0_render_caches.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/6AD90_collision.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/8D3E0_actor_list.h"
#include "proto/global/90D80_render_callbacks.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/ACDC0_pause_menu.h"
#include "proto/global/CC800_player_setup.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/D5E10_player_states.h"
#include "proto/global/E4090_player_input.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/F56F0_player_weapon.h"
#include "proto/global/F93B0_void_height.h"
#include "proto/global/F9450_grid_nodes.h"
#include "proto/global/FCCD0_slot_queue.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;

// Actor types playerStateSquishDeath looks for (mapFindClosestTargetNearSavedPos) around the saved exit position.
typedef struct ActorTypeTriple {
    s16 types[3];
} ActorTypeTriple;

ActorTypeTriple sSquishDeathExitTypes = { { 0x1C, 0x86, 0x6B } };
s32 D_80750FB8[2] = { 0, 30 }; // unreferenced
f32 gSlopeSlideParticleScale = 0.2f;
s32 gSlopeSlideParticleSinkSpeed = -100;
s32 gSlopeSlideParticleSpreadX = 5;
s32 gSlopeSlideParticleSpreadY = 5;
s32 gSlopeSlideParticleSpreadZ = 5;
u8 gSlopeSlideParticleCount = 2;
f32 gSlopeSlideParticleMinSpeed = 80.0f;
s32 gCutscenePauseDecelRate = 50;
s32 gConsumableRefillSlots[4] = { 2, 4, 6, 5 };

#define KONG_ACTOR ((KongActor *)gCurrentActor)

void playerStateCarried(void) {
    playerStateQueueCallback(0x3C, NULL, gCurrentPlayerIndex);
    playerInputUpdate(0xB);
    gActivePlayerActor->speedXZ = gActivePlayerState->maxSpeed;
    gActivePlayerActor->moveYaw = gActivePlayerState->targetYaw;
    gActivePlayerActor->yaw = gActivePlayerState->targetYaw;
    playerApplyMotionWithHorizontalVelocity();
    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x200C)) {
        playerResumeLocomotion(gCurrentActor);
        actorSetInteractionTimer(gCurrentActor);
    } else {
        gCurrentActor->collisionMode = 1;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerClampYAboveFloor(void) {
    if (gCurrentActor->waterY < gCurrentActor->y + 4.5f) {
        gCurrentActor->y = gCurrentActor->waterY - 4.5f;
    }
}

void playerInputUpdate66(void) {
    playerInputUpdate(0x66);
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdateNoop(void) {
}

void playerInputUpdate1AndCheckLocomotion(void) {
    playerInputUpdate(1);
    if (!(gActivePlayerState->stateFlags & 0x10000)) {
        playerResumeLocomotion(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateUnderwaterSwim(void) {
    gCurrentActor->speedY = mathApproachF32(gCurrentActor->speedY, 50.0f, 4.0f);
    switch (gCurrentActor->subState) {
        case 0:
            gActivePlayerState->swimFrames = 0;
            gActivePlayerState->targetSpeed = 100.0f;
            playerInputUpdate(0x67);
            playerApplyMotionWithHorizontalVelocity();
            gCurrentActor->subState++;
            break;
        case 1:
            playerApplyMotionWithHorizontalVelocity();
            if ((gCurrentActor->speedXZ > 10.0f) && (gCurrentActor->sub4->animId != 0x317)) {
                actorScriptStart(gCurrentActor, 0x317);
            } else if ((gCurrentActor->speedXZ == 0.0f) && (gCurrentActor->sub4->animId != 0x314)) {
                actorScriptStart(gCurrentActor, 0x314);
            }
            playerInputUpdate(0x67);
            break;
    }
    playerClampYAboveFloor();
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void playerStateSurfaceDiving(void) {
    gActivePlayerState->swimFrames = 0;
    if (gCurrentActor->subState == 0) {
        gActivePlayerState->turnRate = 0xA;
        gCurrentActor->accelY = -8.0f;
        gCurrentActor->roll = mathAngleFromVector2D(gCurrentActor->speedXZ, gCurrentActor->speedY);
        mathAngleStepToward(&gCurrentActor->pitch, 0, 0x32);
        mathAngleStepToward(&gCurrentActor->roll, mathAngleFromVector2D(gCurrentActor->speedXZ, gCurrentActor->speedY), 0xA);
        playerInputUpdate(0x6A);
        gCurrentActor->moveYaw = gCurrentActor->yaw;
        playerApplyGravityAndMotion();
    }
    if ((gCurrentActor->y + 4.0f < gCurrentActor->waterY) && (gCurrentActor->speedY < 0.0f)) {
        gCurrentActor->state = 0x7F;
        gCurrentActor->subState = 0;
        gActivePlayerState->slideSpeed = 2.0f;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongSwimAccel[];
extern s16 gKongSwimIdleDelays[];

void playerStateUnderwaterSwimming(void) {
    f64 scaledXZ;
    f64 scaledY;
    f32 step;

    gActivePlayerState->swimFrames++;
    gActivePlayerState->airAccel = gKongSwimAccel[gCurrentCharacterIndex];
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x4C);
            step = -gCurrentActor->speedY * 0.125;
            gCurrentActor->speedY = mathApproachF32(gCurrentActor->speedY, 0.0f, step);
            if (gActivePlayerState->swimFrames >= 6) {
                if ((gCurrentActor->speedXZ != 0.0f) || (gActivePlayerState->actionTimer != 0)) {
                    gCurrentActor->subState = 3;
                } else {
                    gCurrentActor->subState = 2;
                }
                gCurrentActor->sub4->scriptWaitFlags &= ~0x4000;
            }
            playerDecelerateAndApplyMotion();
            break;
        case 1:
            mathAngleStepToward(&gCurrentActor->roll, mathAngleFromVector2D(gCurrentActor->speedXZ, gCurrentActor->speedY), 0x32);
            gActivePlayerState->targetSpeed = 500.0f;
            playerInputUpdate(0x57);
            playerApplyDecelVelocityVector(0.0f);
            if (gActivePlayerState->actionTimer == 0) {
                gCurrentActor->subState = 3;
            }
            break;
        case 2:
            playerInputUpdate(0x55);
            playerApplyDecelVelocityVector(0.0f);
            if (gCurrentActor->state == 0x7F) {
                if (gCurrentActor->speedXZ != 0.0f) {
                    gActivePlayerState->unk18 = 0;
                    gCurrentActor->subState = 3;
                } else {
                    if (gActivePlayerState->idleDelay != 0) {
                        gActivePlayerState->idleDelay--;
                        if (gActivePlayerState->idleDelay == 0) {
                            actorScriptStart(gCurrentActor, 0x315);
                        }
                    }
                }
                if (gCurrentActor->waterY < gCurrentActor->y + 4.0f) {
                    gCurrentActor->state = 0x7E;
                    gCurrentActor->subState = 0;
                }
            }
            break;
        case 3:
            playerInputUpdate(0x56);
            playerApplyDecelVelocityVector(0.0f);
            scaledXZ = gCurrentActor->speedXZ / 200.0;
            scaledY = gCurrentActor->speedY / 200.0;
            scriptSetActorRampTarget(gCurrentActor, sqrtf(scaledXZ * scaledXZ + scaledY * scaledY), 5.0f);
            if ((gCurrentActor->speedXZ == 0.0f) || (gActivePlayerState->unk18 != 0)) {
                gActivePlayerState->idleDelay = gKongSwimIdleDelays[gCurrentCharacterIndex];
                scriptSetActorRampTarget(gCurrentActor, 0.5f, gActivePlayerState->idleDelay);
                gCurrentActor->subState = 2;
            }
            if (gCurrentActor->waterY < gCurrentActor->y + 4.0f) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x10, 0xFF, 0x7F, 1);
                if (gCurrentActor->speedY > 150.0f) {
                    gCurrentActor->state = 0x82;
                    gCurrentActor->subState = 0;
                    actorScriptStart(gCurrentActor, 0);
                } else {
                    gCurrentActor->state = 0x7E;
                    gCurrentActor->subState = 0;
                }
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateUnderwaterTurn(void) {
    gCurrentActor->speedY = mathApproachF32(gCurrentActor->speedY, 50.0f, 4.0f);
    switch (gCurrentActor->subState) {
        case 0:
            gActivePlayerState->turnRate = 0x50;
            playerInputUpdate(0x68);
            playerApplyDeceleration();
            playerApplyMotion();
            break;
        case 1:
            gActivePlayerState->slideLaunchSpeed = 200.0f;
            gActivePlayerState->airAccel = 40.0f;
            playerApproachVelocity(gCurrentActor->yaw, gActivePlayerState->slideLaunchSpeed, gActivePlayerState->slideLaunchSpeed);
            playerInputUpdate(0x68);
            playerApplyMotion();
            break;
        case 2:
            playerInputUpdate(0x68);
            playerApproachVelocity(gCurrentActor->yaw, gActivePlayerState->maxSpeed, gActivePlayerState->slideLaunchSpeed);
            playerApplyMotion();
            break;
        case 3:
            playerInputUpdate(0x68);
            playerApplyMotionWithHorizontalVelocity();
            if (gCurrentActor->waterY < gCurrentActor->y + 4.0f) {
                gCurrentActor->state = 0x7E;
                gCurrentActor->subState = 0;
            } else {
                gCurrentActor->state = 0x7F;
                gCurrentActor->subState = 0;
            }
            break;
    }
    playerClampYAboveFloor();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateUnderwaterCharge(void) {
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x69);
            playerApplyDeceleration();
            playerApplyMotion();
            gActivePlayerState->subTimer = gCurrentActor->roll;
            gActivePlayerState->pitchAngle = gCurrentActor->yaw;
            break;
        case 1:
            gActivePlayerState->airAccel = 40.0f;
            gActivePlayerState->actionTimer = 0xA;
            gActivePlayerState->targetSpeed = 200.0f;
            playerInputUpdate(0x69);
            playerApplyDecelVelocityVector(0.0f);
            break;
        case 2:
            playerInputUpdate(0x69);
            playerApproachVelocity(gCurrentActor->yaw, gActivePlayerState->maxSpeed, gActivePlayerState->slideLaunchSpeed);
            playerApplyMotion();
            break;
        case 3:
            playerInputUpdate(0x69);
            playerApplyHorizontalMotion();
            if (gCurrentActor->waterY < gCurrentActor->y + 4.0f) {
                gCurrentActor->state = 0x7E;
                gCurrentActor->subState = 0;
                actorScriptStart(gCurrentActor, 0x317);
            } else {
                gCurrentActor->state = 0x7F;
                gCurrentActor->subState = 3;
                actorScriptStart(gCurrentActor, 0x318);
                gActivePlayerState->targetSpeed = 300.0f;
                gActivePlayerState->actionTimer = 0xF;
            }
            break;
    }
    playerClampYAboveFloor();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdate65(void) {
    gActivePlayerState->maxSpeed = 0.0f;
    playerInputUpdate(0x65);
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateDamageFall(void) {
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->decelRate = 20.0f;
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateDeathTransition(void) {
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->decelRate = 20.0f;
    playerApplyFullPhysics();
    if ((currentActorTestClearFlag() != 0) || (gCurrentActor->subState == 1) || --gActivePlayerState->stateCountdown == 0) {
        mapTransitionToMenuOrPrevious();
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void playerStateExitTransition(void) {
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->decelRate = 20.0f;
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    playerApplyFullPhysics();
    if (gCurrentActor->subState != 0) {
        mapTransitionToPreviousOrExit();
        gCurrentActor->subState++;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateGameOver(void) {
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->decelRate = 20.0f;
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    if (!(gCurrentActor->contactFlags & 4)) {
        playerApplyFullPhysics();
    } else {
        playerCanPerformActionCheck();
        if (!(gCurrentActor->prevContactFlags & 4)) {
            actorScriptStartByIndex(gPrimaryPlayerActor, 0x34);
        }
        gCurrentActor->speedY = gCurrentActor->speedY * 0.25;
        playerApplyFullPhysics();
    }
    if ((currentActorTestClearFlag() != 0) || --gActivePlayerState->stateCountdown == 0) {
        hudSpawnTextScreen(0);
        gCurrentActor->subState++;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSquishDeath(void) {
    s32 map;
    s32 target;
    s32 pad;
    ActorTypeTriple table = sSquishDeathExitTypes;

    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->decelRate = 20.0f;
    if (!(gCurrentActor->contactFlags & 4)) {
        playerApplyFullPhysics();
    } else {
        playerCanPerformActionCheck();
        if (!(gCurrentActor->prevContactFlags & 4)) {
            actorScriptStartByIndex(gPrimaryPlayerActor, 0x34);
        }
        gCurrentActor->speedY = gCurrentActor->speedY * 0.25;
        playerApplyMotionWithHorizontalVelocity();
    }
    if ((currentActorTestClearFlag() != 0) || --gActivePlayerState->stateCountdown == 0) {
        if (menuIsTransitionTypeD() == 0) {
            target = mapFindClosestTargetNearSavedPos(table.types, 3, &map);
            actorListSetCustomFloat(map, target, 7, 2.0f);
        }
        mapTransitionToPreviousOrExit();
        gCurrentActor->subState++;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdate0(void) {
    playerInputUpdate(0);
    if (!(gGlobalPauseFlags & 0x4000) && !(gGlobalPauseFlags & 0x8000)) {
        playerResumeLocomotion(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdate1InitScript0(void) {
    playerInputUpdate(1);
    if (gCurrentActor->subState == 0) {
        actorScriptStartByIndex(gCurrentActor, 0);
        gCurrentActor->subState = 1;
        gCurrentActor->flags &= ~4;
    }
}

void playerInputUpdate1(void) {
    playerInputUpdate(1);
}

void playerInputUpdate62(void) {
    playerInputUpdate(0x62);
    switch (gCurrentActor->subState) {
        case 1:
        case 2:
            gCurrentActor->subState++;
            break;
        case 0:
        case 0x3C:
        case 0x3D:
            break;
        default:
            gCurrentActor->subState++;
    }
}

void actorRegisterCurrentActorGlobalCallback(void *callbackFn) {
    ActorCallbackNode *node;

    node = heapAlloc(0x14);
    node->callback = callbackFn;
    node->source = gActivePlayerActor;
    node->dispatchPass = 1;
    actorRegisterGlobalCallback(node);
}

void actorRegisterSnapToBoneCallback(void) {
    actorRegisterCurrentActorGlobalCallback(&actorSnapToBone);
}

extern s32 gCurrentMap;

void playerInputUpdateByMap(void) {
    actorRegisterSnapToBoneCallback();
    switch (gCurrentMap) {
        case 0x37:
            playerInputUpdate(0x5F);
            playerApplyMotion();
            return;
        case 0x6A:
            playerInputUpdate(0x60);
            playerApplyMotion();
            return;
        case 0x4D:
        case 0x81:
        case 0x82:
            if ((gActivePlayerState->stateFlags & 8) && (currentActorTestClearFlag() != 0)) {
                gActivePlayerState->actor->state = 0xA;
                gCurrentActor->subState++;
            }
            playerInputUpdate(0x5B);
            playerApplyMotion();
            return;
        default:
            playerInputUpdate(0x5C);
            gCurrentActor->speedY = gCurrentActor->terminalSpeedY;
            playerApplyGravityAndMotion();
            return;
    }
}

void playerInputUpdate5D(void) {
    actorRegisterSnapToBoneCallback();
    playerInputUpdate(0x5D);
    gCurrentActor->speedY = gCurrentActor->terminalSpeedY;
    playerApplyGravityAndMotion();
}

void playerInputUpdate5E(void) {
    actorRegisterSnapToBoneCallback();
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x5E);
            playerApplyGravityAndMotion();
            return;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            gCurrentActor->subState++;
            playerInputUpdate(0x5E);
            playerSetBaseGravityIfFalling();
            playerApplyGravityAndMotion();
            return;
        case 2:
            playerApplyGravityAndMotion();
            playerInputUpdate(0x5E);
            playerSetBaseGravityIfFalling();
            return;
        case 3:
            playerInputUpdate(0x5C);
            playerApplyGravityAndMotion();
            return;
    }
}

void playerInputUpdateByMapDirect(void) {
    switch (gCurrentMap) {
        case 0x6A:
            playerInputUpdate(0x60);
            playerApplyMotion();
            break;
        case 0x37:
            playerInputUpdate(0x5F);
            playerApplyMotion();
            break;
        case 0x4D:
            playerInputUpdate(0x5B);
            playerApplyMotion();
            break;
        default:
            playerInputUpdate(0x5C);
            gCurrentActor->speedY = gCurrentActor->terminalSpeedY;
            playerApplyGravityAndMotion();
            break;
    }
}

void playerInputUpdateNode3(void) {
    f32 x;
    f32 y;
    f32 z;

    actorRegisterSnapToBoneCallback();
    playerInputUpdateByMapDirect();
    actorGetNodePos(gCurrentActor, 3, &x, &y, &z);
    gridSetNodeBounds(gCurrentPlayerIndex, x, y, z, 25.0f);
}

void playerInputUpdateNode2(void) {
    f32 x;
    f32 y;
    f32 z;

    actorRegisterSnapToBoneCallback();
    playerInputUpdateByMapDirect();
    actorGetNodePos(gCurrentActor, 2, &x, &y, &z);
    gridSetNodeBounds(gCurrentPlayerIndex, x, y, z, 25.0f);
}

void playerSyncParentAndInputUpdate(s32 inputId) {
    actorRegisterCurrentActorGlobalCallback(&actorSyncTransformFromParent);
    playerInputUpdate(inputId);
    gCurrentActor->prevContactFlags = gCurrentActor->contactFlags;
}

void playerInputUpdate61(void) {
    playerSyncParentAndInputUpdate(0x61);
}

void playerInputUpdate63(void) {
    playerSyncParentAndInputUpdate(0x63);
    if (camIsPlayingPath(5) != 0) {
        if (gCurrentActor->sub4->animId != 0x3B0) {
            actorScriptStart(gCurrentActor, 0x3B0);
        }
        if ((currentActorTestClearFlag() != 0) || (gCurrentActor->subState != 0)) {
            mapTransitionToMenuOrPrevious();
        }
    }
}

void playerStateRidingActor(void) {
    s16 *counter;

    counter = gActivePlayerState->actor->customState;
    if (gCurrentActor->subState != 0) {
        gCurrentActor->state = 0x6D;
        gCurrentActor->subState = 0;
    } else {
        playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    }
    *counter += gActivePlayerState->rideSpin;
    if (gActivePlayerState->rideSpin >= 8) {
        gActivePlayerState->rideSpin -= 7;
    } else if (gActivePlayerState->rideSpin < -7) {
        gActivePlayerState->rideSpin += 7;
    } else {
        gActivePlayerState->rideSpin = 0;
    }
    playerSyncParentAndInputUpdate(1);
}

void playerInputUpdate64(void) {
    playerSyncParentAndInputUpdate(0x64);
}

void playerInputUpdateWaitC9(void) {
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (gCurrentActor->subState++ >= 0xC9) {
        playerResumeLocomotion(gCurrentActor);
    }
}

void playerRegisterWeaponHudRenderCallback(s16 inputId) {
    if ((gActivePlayerState->gunDrawn != 0) && (hudCanRender() != 0)) {
        if (gCurrentKongInventory->weaponFlags == 7) {
            inputId = 0xF;
            renderCallbacksRegister(&playerViewDrawScopeCrosshair, gCurrentActor, 5);
        } else {
            inputId = 0xE;
            renderCallbacksRegister(&playerViewDrawCrosshair, gCurrentActor, 5);
        }
    }
    if (gCurrentActor->subState != 0) {
        inputId = 5;
        gCurrentActor->subState--;
    }
    playerInputUpdate(inputId);
}

void playerRegisterInstrumentHudRenderCallback(s16 inputId) {
    if (gCurrentActor->subState != 0) {
        inputId = 5;
        gCurrentActor->subState--;
    }
    if (hudCanRender() != 0) {
        if (playerInputUpdate(inputId) == 0) {
            renderCallbacksRegister(&playerViewDrawCameraViewfinder, gCurrentActor, 3);
        }
        renderCallbacksRegister(&playerViewCornerMasksCallback, gCurrentActor, 3);
    }
}

void playerRegisterCameraHudRenderCallback(s16 nextState) {
    playerInputUpdate(1);
    if (gCurrentActor->subState < 6) {
        renderCallbacksRegister(&playerViewDrawCameraShutter, gCurrentActor, 3);
        gCurrentActor->subState++;
    } else {
        gCurrentActor->state = nextState;
        gCurrentActor->subState = 0;
    }
    if (gCurrentActor->subState == 2) {
        actorSpawn(0xCA, 0x8D);
        gActivePlayerState->actor = gSpawnedActor;
        *(void **)gSpawnedActor->customState = gActivePlayerState;
        gActivePlayerState->stateFlags |= 0x8000;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdateCase4(void) {
    playerRegisterCameraHudRenderCallback(4);
}

void playerInputUpdateCase5(void) {
    playerRegisterCameraHudRenderCallback(5);
}

extern u8 gDemoPlaybackState;

void playerInputUpdateCaseC(void) {
    playerRegisterWeaponHudRenderCallback(0xC);
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
    if ((camIsCutsceneActive() != 0) && (gCurrentActor->soundSlots[0] != -1)) {
        sfxStopSlotSound(gCurrentActor, 0);
    }
    if (gDemoPlaybackState == 3) {
        playerCheckAndResetCarriedActor(gCurrentActor);
    }
}

void playerInputUpdateCase10(void) {
    playerRegisterInstrumentHudRenderCallback(0x10);
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (gDemoPlaybackState == 3) {
        playerCheckAndResetCarriedActor(gCurrentActor);
    }
}

extern f32 gKongSwimBuoyancy[];

void playerInputUpdateCaseD(void) {
    gActivePlayerState->airAccel = gKongSwimAccel[gCurrentCharacterIndex];
    playerRegisterWeaponHudRenderCallback(0xD);
    playerApplyDecelVelocityVector(gKongSwimBuoyancy[gCurrentCharacterIndex]);
    if (playerCanPerformActionCheck() != 0) {
        playerLeaveViewMode(gCurrentActor, 1);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdateCase11(void) {
    gActivePlayerState->airAccel = gKongSwimAccel[gCurrentCharacterIndex];
    playerRegisterInstrumentHudRenderCallback(0x11);
    playerApplyDecelVelocityVector(gKongSwimBuoyancy[gCurrentCharacterIndex]);
    if (playerCanPerformActionCheck() != 0) {
        playerLeaveViewMode(gCurrentActor, 1);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void playerStateClimbTree(void) {
    s32 sel = 0x13;

    gCurrentActor->moveYaw = gCurrentActor->yaw;
    gCurrentActor->renderFlags |= 0x200;
    if (gCurrentActor->subState != 0) {
        gCurrentActor->subState--;
        sel = 0x14;
    }
    if ((gFrameCounter >= 2) && (playerInputUpdate(sel) == 0)) {
        s16 nextState = playerSelectWalkRunState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);

        if (nextState != 0xC) {
            gCurrentActor->state = nextState;
            gCurrentActor->subState = 0;
        }
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongLightGravity[];
extern s32 gGlobalCutsceneFlags;

void playerStateVineSwing(void) {
    f32 margin;
    f32 voidY;
    s32 sel;

    if (gGlobalCutsceneFlags & 2) {
        f64 t = (gCurrentActor->y - 120.0f) * 0.5;

        margin = (t > 0.0) ? t : 0.0;
        if (gCurrentActor->x < 590.0f - margin) {
            gCurrentActor->x = 590.0f - margin;
        }
        if (987.0f + margin < gCurrentActor->x) {
            gCurrentActor->x = 987.0f + margin;
        }
        if (gCurrentActor->z < 571.0f - margin) {
            gCurrentActor->z = 571.0f - margin;
        }
        if (965.0f + margin < gCurrentActor->z) {
            gCurrentActor->z = 965.0f + margin;
        }
        gCurrentActor->collisionMode &= 0xFFF7;
    }
    playerInputUpdate(0x1B);
    voidY = mapGetVoidHeightForCharacter(gPrimaryPlayerActor->chunkIndex);
    if (voidY < gCurrentActor->y) {
        gCurrentActor->accelY = gKongLightGravity[gCurrentCharacterIndex];
        if (gCurrentActor->speedY > 0.0f) {
            gCurrentActor->speedY = gCurrentActor->speedY * 0.7;
        }
    }
    if (gActivePlayerState->thrustApplied != 0) {
        s32 pitch = gActivePlayerState->aimPitch;

        if (pitch >= 0x8000) {
            pitch -= 0x10000;
        }
        pitch += 0x9E8;
        if (pitch >= 0x7D1) {
            sel = 0x7D;
        } else if (pitch < -0x7D0) {
            sel = 0x80;
        } else {
            sel = 0x7F;
        }
    } else {
        sel = 0x7E;
    }
    if ((sel != gCurrentActor->sub4->animId) && (gCurrentActor->sub4->animId != 0x81)) {
        actorScriptStart(gCurrentActor, sel);
    }
    if ((gActivePlayerState->stateFlags & 0x40000000) && (gActivePlayerState->attachmentExitTimer == 0)) {
        effectScreenCenterFlash();
        gActivePlayerState->attachmentExitTimer = 0x1E;
    }
    if (gActivePlayerState->attachmentExitTimer != 0) {
        gActivePlayerState->attachmentExitTimer--;
    }
    if ((gCurrentActor->contactFlags & 1) || (gActivePlayerState->attachmentExitTimer == 1)) {
        if (gGlobalCutsceneFlags & 2) {
            gCurrentActor->collisionMode |= 8;
        }
        playerResumeLocomotion(gCurrentActor);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 1, 0xFF, 0x7F, 0x1E);
    }
    if (camIsCutsceneActive() == 0) {
        playerApplyGravityAndMotion();
        if ((slotQueueGetValue(5, gCurrentPlayerIndex) != 0) && !(gActivePlayerState->stateFlags & 0x10000)) {
            slotQueueAddValue(5, gCurrentPlayerIndex, -1);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateClimbTop(void) {
    gCurrentActor->moveYaw = gCurrentActor->yaw;
    if (playerInputUpdate(0x1D) == 0) {
        s16 nextState = playerSelectCarryState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);

        if (nextState != 0x5D) {
            gCurrentActor->state = nextState;
            gCurrentActor->subState = 0;
        }
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateMinecart(void) {
    if ((gCurrentMap == 0x4E) || (gCurrentMap == 0x4F) || (gCurrentMap == 0x83)) {
        playerInputUpdate(0x1F);
    } else {
        playerInputUpdate(0x1E);
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongMaxTierExitSpeeds[];

void playerStateClimbLadder(void) {
    if (gCurrentActor->subState == 0) {
        gCurrentActor->subState++;
        gActivePlayerState->prevPrevTargetYaw = -1;
        gActivePlayerState->prevTargetYaw = -1;
    }
    if (playerInputUpdate(0x13) == 0) {
        s16 nextState = playerSelectWalkRunState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);

        if (nextState != 0xD) {
            gCurrentActor->state = nextState;
            gCurrentActor->subState = 0;
        }
    }
    if ((camIsCutsceneActive() == 0) && (gKongMaxTierExitSpeeds[gCurrentCharacterIndex] < gCurrentActor->speedXZ) && (gKongMaxTierExitSpeeds[gCurrentCharacterIndex] < gActivePlayerState->maxSpeed) &&
        (gActivePlayerState->prevPrevTargetYaw >= 0) && (mathAngleDistance(gActivePlayerState->prevPrevTargetYaw, gActivePlayerState->targetYaw) >= 0x401) &&
        (mathAngleDistance(gCurrentActor->moveYaw, gActivePlayerState->targetYaw) >= 0x539)) {
        gCurrentActor->state = 0xE;
        gCurrentActor->subState = 0;
        playerApplyGravityAndMotion();
    } else {
        playerApplyFullPhysics();
    }
    gActivePlayerState->prevPrevTargetYaw = gActivePlayerState->prevTargetYaw;
    gActivePlayerState->prevTargetYaw = gActivePlayerState->targetYaw;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSlideDownLadder(void) {
    if (playerInputUpdate(0x1C) == 0) {
        s16 nextState = playerSelectCarryState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);

        if (nextState != 0x5E) {
            gCurrentActor->state = nextState;
            gCurrentActor->subState = 0;
        }
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerUpdateFallTimer(void) {
    if (((gCurrentActor->peakY - gCurrentActor->y) > 50.0f) && (gCurrentActor->distToFloor > 250.0f)) {
        gActivePlayerState->fallTimer++;
    } else {
        gActivePlayerState->fallTimer = 0;
    }
    if ((gActivePlayerState->fallTimer++ >= 0xB) || (gCurrentActor->y < -10.0f)) {
        playerStateQueueCallback(0x2D, 0, gCurrentPlayerIndex);
    }
}

void playerUpdateFallAndStepSounds(void) {
    f32 scale = gCurrentActor->sub4->scaleY / 0.15;

    if (!(gGlobalOverlayFlags & 0x40000) && (camIsCutsceneActive() == 0)) {
        if (gCurrentMap == 0xE) {
            playerUpdateFallTimer();
            return;
        }
        if ((290.0f * scale) < (gCurrentActor->peakY - gCurrentActor->y)) {
            playerStateQueueCallback(0x2C, 0, gCurrentPlayerIndex);
        }
    }
}


void playerStateFallDamageLand(void) {
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x20);
            playerUpdateFallAndStepSounds();
            break;
        case 1:
            playerInputUpdate(0x31);
            playerSetBaseGravity();
            break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateFallDamageHard(void) {
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x20);
            playerUpdateFallAndStepSounds();
            break;
        case 1:
            playerInputUpdate(0x32);
            playerSetBaseGravity();
            break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateFallDamageCrouch(void) {
    if (gCurrentActor->subState == 0) {
        playerInputUpdate(0x20);
        playerApplyFullPhysics();
        if (gCurrentActor->contactFlags & 1) {
            if (gCurrentActor->floorSlopeFactor != 0.0f) {
                playerResumeLocomotion(gCurrentActor);
            } else {
                playerSetBaseGravity();
                playerStateQueueCallback(0x35, 0, gCurrentPlayerIndex);
            }
        }
    } else {
        playerInputUpdate(0x20);
        gActivePlayerState->maxSpeed = 0.0f;
        gCurrentActor->speedXZ = 0.0f;
        playerApplyFullPhysics();
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerApplyImpactRumble(s32 inputId) {
    effectSpawnSpeedDustAtBone(0.5f, 0x64, 5);
    gCurrentActor->arcSpeedCapMax = 0x12C;
    if ((gCurrentActor->y - gCurrentActor->floorY) > 5.0f) {
        if (gCurrentActor->accelY == -260.0f) {
            playerSetBaseGravity();
        } else if (gCurrentActor->accelY != -30.0f) {
            gCurrentActor->contactFlags |= 0x1000;
        } else {
            gCurrentActor->speedY = (gCurrentActor->speedY > 0.0f) ? 0.0f : gCurrentActor->speedY;
        }
        gCurrentActor->state = 0x14;
        gCurrentActor->subState = 0;
        gActivePlayerState->jumpVelocityY = gCurrentActor->speedY;
        gActivePlayerState->gravityDelay = 0;
        actorScriptStartByIndex(gCurrentActor, 0x67);
    }
    playerInputUpdate(inputId);
    playerApplyFullPhysics();
    if (!(gCurrentActor->contactFlags & 0x200)) {
        playerResumeLocomotion(gCurrentActor);
        sfxStopSlotSound(gCurrentActor, 0);
        camReturnToFollow(gActivePlayerState->camActor, gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSlideCameraInit(void) {
    if (gCurrentActor->subState == 0) {
        camSetTarget(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, 0x32, 0, 5, 0x32, 0x14, 0, 0.2f);
        gCurrentActor->subState++;
    }
    playerApplyImpactRumble(0x3D);
}

void playerStateSlide(void) {
    playerApplyImpactRumble(0x3D);
}

void playerStateSlideSteep(void) {
    playerApplyImpactRumble(0x3D);
}

void playerStateSlideMedium(void) {
    playerApplyImpactRumble(0x3D);
}

void playerStateSlideGentle(void) {
    playerApplyImpactRumble(0x3D);
}

void playerStateSlideRecover(void) {
    gActivePlayerState->maxSpeed = 0.0f;
    playerApplyFullPhysics();
    gCurrentActor->subState++;
    if (gCurrentActor->subState == 0x32) {
        RaceParticipant *participant = gActivePlayerState->actor->customState;
        participant->eliminated = 1;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSlideFall(void) {
    playerInputUpdate(0x3E);
    playerApplyFullPhysics();
    switch (gCurrentActor->subState) {
        case 0:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            gCurrentActor->subState++;
            break;
        case 1:
            if (gCurrentMap == 0xE) {
                playerUpdateFallTimer();
            }
            break;
        case 2:
            if (gCurrentActor->contactFlags & 1) {
                gCurrentActor->contactFlags &= ~0x1000;
                playerSetBaseGravity();
                gCurrentActor->state = 0xF;
                gCurrentActor->subState = 0;
                actorScriptStartByIndex(gCurrentActor, 0x5E);
            } else {
                playerUpdateFallTimer();
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSlideBrake(void) {
    effectSpawnSpeedDustAtBone(0.5f, 0x64, 5);
    playerInputUpdate(0x3C);
    playerApplyFullPhysics();
    if (gCurrentActor->speedXZ == 0.0f && gCurrentActor->floorSlopeFactor == 0.0f) {
        playerResumeLocomotion(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSlideReverse(void) {
    effectSpawnSpeedDustAtBone(0.5f, 0x64, 5);
    playerInputUpdate(0x3B);
    playerApplyFullPhysics();
    if (gCurrentActor->speedXZ == 0.0f && gCurrentActor->floorSlopeFactor == 0.0f) {
        playerResumeLocomotion(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongSkidTurnDecelRates[];
extern s16 gKongSkidTurnRates[];

void playerStateSkidTurn(void) {
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x41);
            actorScriptStartByIndex(gCurrentActor, 5);
            gActivePlayerState->decelRate = gKongSkidTurnDecelRates[gCurrentCharacterIndex];
            playerApplyDeceleration();
            playerApplyGravityAndMotion();
            gCurrentActor->subState++;
            break;
        case 1:
            playerInputUpdate(0x41);
            playerApplyDeceleration();
            playerApplyGravityAndMotion();
            break;
        case 2:
            playerInputUpdate(0x41);
            playerApplyDeceleration();
            mathAngleStepTowardThreshold(&gCurrentActor->yaw, gActivePlayerState->targetYaw, gKongSkidTurnRates[gCurrentCharacterIndex], 0xC00);
            playerApplyGravityAndMotion();
            break;
        case 3:
            playerInputUpdate(0x41);
            mathAngleStepTowardThreshold(&gCurrentActor->yaw, gActivePlayerState->targetYaw, gKongSkidTurnRates[gCurrentCharacterIndex], 0xC00);
            if (gActivePlayerState->maxSpeed == 0.0f) {
                playerResumeLocomotion(gCurrentActor);
            }
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerUpdateTargetYawFromStick(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].stickMagNorm != 0.0f) {
        gCurrentActor->targetYaw = gActivePlayerState->targetYaw;
    } else {
        gCurrentActor->targetYaw = gCurrentActor->yaw;
    }
}

extern SchedStruct gScheduler;
extern f32 gKongAirJumpVelocity[];

void playerStateDoubleJump(void) {
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x2C);
            playerApplyFullPhysics();
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            playerUpdateTargetYawFromStick();
            gCurrentActor->subState++;
            playerInputUpdate(0x21);
            playerSetBaseGravityIfFalling();
            playerApplyFullPhysics();
            break;
        case 2:
            playerApplyFullPhysics();
            if (gCurrentActor->actorType == 5) {
                playerInputUpdate(0x22);
            } else {
                playerInputUpdate(0x21);
            }
            playerSetBaseGravityIfFalling();
            break;
        case 3:
            if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
                gActivePlayerState->jumpTimer = gScheduler.tickCount;
            }
            if (gScheduler.tickCount - gActivePlayerState->jumpTimer < 0xA && gPlayerCharacterId[gCurrentPlayerIndex] == 1 && gCurrentActor->floorSlopeFactor == 0.0f) {
                gCurrentActor->state = 0x1A;
                gCurrentActor->subState = 0;
                gActivePlayerState->jumpVelocityY = gKongAirJumpVelocity[gCurrentCharacterIndex];
                gActivePlayerState->gravityDelay = 0;
                actorScriptStartByIndex(gCurrentActor, 0x13);
            }
            playerInputUpdate(0x30);
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdate5(void) {
    gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
    playerInputUpdate(5);
    playerApplyMotionWithHorizontalVelocity();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongAirAccel[];

void playerStateLongJump(void) {
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x2C);
            if (gActivePlayerState->airTimer != 0) {
                playerApplyGravityAndMotion();
                gActivePlayerState->airTimer--;
            } else {
                playerApplyFullPhysics();
            }
            break;
        case 1:
            if (gActivePlayerState->airTimer != 0) {
                gActivePlayerState->airAccel = 0.0f;
                playerApplyFullPhysics();
                gActivePlayerState->airTimer--;
                gCurrentActor->targetYaw = gCurrentActor->yaw;
            } else {
                playerUpdateTargetYawFromStick();
                playerApplyFullPhysics();
            }
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            gCurrentActor->subState++;
            playerInputUpdate(0x21);
            playerSetBaseGravityIfFalling();
            break;
        case 2:
            if (gActivePlayerState->airTimer != 0) {
                gActivePlayerState->airAccel = 0.0f;
                playerApplyFullPhysics();
                gActivePlayerState->airTimer--;
            } else {
                gActivePlayerState->airAccel = gKongAirAccel[gCurrentCharacterIndex];
                playerApplyFullPhysics();
            }
            if (gCurrentActor->actorType == 5) {
                playerInputUpdate(0x22);
            } else {
                playerInputUpdate(0x21);
            }
            playerUpdateFallAndStepSounds();
            playerSetBaseGravityIfFalling();
            break;
        case 3:
            gActivePlayerState->airTimer = 0;
            if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
                gActivePlayerState->jumpTimer = gScheduler.tickCount;
            }
            if (gScheduler.tickCount - gActivePlayerState->jumpTimer < 0xA && gPlayerCharacterId[gCurrentPlayerIndex] == 1 && gCurrentActor->floorSlopeFactor == 0.0f) {
                gCurrentActor->state = 0x1A;
                gCurrentActor->subState = 0;
                gActivePlayerState->jumpVelocityY = gKongAirJumpVelocity[gCurrentCharacterIndex];
                gActivePlayerState->gravityDelay = 0;
                actorScriptStartByIndex(gCurrentActor, 0x13);
            }
            playerInputUpdate(0x30);
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void playerStateLaunchAir(void) {
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x2C);
            playerApplyFullPhysics();
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            playerUpdateTargetYawFromStick();
            gCurrentActor->subState++;
            playerInputUpdate(0x21);
            playerSetBaseGravityIfFalling();
            playerApplyFullPhysics();
            break;
        case 2:
            playerApplyFullPhysics();
            if (gCurrentActor->actorType == 5) {
                playerInputUpdate(0x22);
            } else {
                playerInputUpdate(0x21);
            }
            playerUpdateFallAndStepSounds();
            playerSetBaseGravityIfFalling();
            break;
        case 3:
            gActivePlayerState->moveTier = -1;
            gCurrentActor->state = playerSelectSurfaceState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);
            gCurrentActor->subState = 0;
            if (gCurrentActor->state == 0x3F) {
                gCurrentActor->subState = 1;
            }
            playerInputUpdate(0x46);
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateApproachVelocity(void) {
    switch (gCurrentActor->subState) {
        case 0:
            if (gActivePlayerState->approachTimer != 0) {
                if (mathAngleDistance(gCurrentActor->moveYaw, gActivePlayerState->approachYaw)) {} // FAKE: block split after the call; the gActivePlayerState piece stops at the jal, so $v0 is not forbidden (Q0198, Q0738)
                playerApproachVelocity(gActivePlayerState->approachYaw, 50.0f, gActivePlayerState->targetSpeed);
                gActivePlayerState->approachTimer--;
            }
            playerInputUpdate(0x23);
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 2) {
                gActivePlayerState->maxSpeed *= 0.63;
            }
            playerApplyFullPhysics();
            break;
        case 1:
            playerInputUpdate(0x23);
            switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                case 0:
                case 2:
                    gActivePlayerState->maxSpeed *= 0.63;
                    break;
            }
            playerSetBaseGravity();
            playerUpdateFallAndStepSounds();
            playerApplyFullPhysics();
            break;
        case 2:
            playerApplyFullPhysics();
            if (playerInputUpdate(0x31) == 0 && gCurrentActor->speedXZ < gActivePlayerState->maxSpeed) {
                playerResumeLocomotion(gCurrentActor);
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateCrouchJump(void) {
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x26);
            playerApplyFullPhysics();
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            playerUpdateTargetYawFromStick();
            gCurrentActor->subState++;
            playerInputUpdate(0x25);
            playerSetBaseGravityIfFalling();
            playerApplyFullPhysics();
            break;
        case 2:
            playerApplyFullPhysics();
            playerInputUpdate(0x25);
            playerSetBaseGravityIfFalling();
            playerUpdateFallAndStepSounds();
            break;
        case 3:
            if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
                gActivePlayerState->jumpTimer = gScheduler.tickCount;
            }
            playerInputUpdate(0x34);
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void playerStateBackflip(void) {
    switch (gCurrentActor->subState) {
    case 0:
        if (gActivePlayerState->approachTimer != 0) {
            mathAngleDistance(gCurrentActor->moveYaw, gActivePlayerState->approachYaw);
            playerApproachVelocity(gActivePlayerState->approachYaw, 50.0f, gActivePlayerState->targetSpeed);
            gActivePlayerState->approachTimer--;
        }
        playerApplyFullPhysics();
        if (gCurrentActor->speedY <= -15.0f) {
            gCurrentActor->speedY = -15.0f;
            gCurrentActor->subState++;
        }
        playerInputUpdate(0x24);
        if (gCurrentActor->contactFlags & 1) {
            playerResumeLocomotionDecel(gCurrentActor);
        }
        break;
    case 1:
        playerInputUpdate(0x24);
        if (gActivePlayerState->approachTimer != 0) {
            if (mathAngleDistance(gCurrentActor->moveYaw, gActivePlayerState->approachYaw)) {} // FAKE: dead if keeps the ignored s32 result out of $v0 (Q0198)
            playerApproachVelocity(gActivePlayerState->approachYaw, 30.0f, gActivePlayerState->targetSpeed);
            gActivePlayerState->approachTimer--;
        }
        playerApplyMotionWithHorizontalVelocity();
        if (gCurrentActor->contactFlags & 1) {
            playerResumeLocomotionDecel(gCurrentActor);
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 1, 0xFF, 0x7F, 0x1E);
        }
        break;
    case 2:
        gCurrentActor->accelY = -4.0f;
        playerInputUpdate(0x24);
        playerApplyFullPhysics();
        if (gCurrentActor->contactFlags & 1) {
            playerResumeLocomotionDecel(gCurrentActor);
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongFlapGlideTargetSpeed[];
extern f32 gKongFlapGlideAccelY[];

void playerStateFlapGlide(void) {
    switch (gCurrentActor->subState) {
    case 0:
        scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
        playerInputUpdate(0x2C);
        playerApplyFullPhysics();
        break;
    case 1:
        gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
        gCurrentActor->accelY = gKongFlapGlideAccelY[gCurrentCharacterIndex];
        gCurrentActor->subState++;
        playerUpdateTargetYawFromStick();
        playerInputUpdate(0x2B);
        gActivePlayerState->targetSpeed = gKongFlapGlideTargetSpeed[gCurrentCharacterIndex];
        playerApplyFullPhysics();
        break;
    case 2:
        playerApplyFullPhysics();
        playerInputUpdate(0x2B);
        playerSetTerminalVelocity658();
        playerUpdateFallAndStepSounds();
        break;
    case 3:
        playerInputUpdate(0x2B);
        playerSetBaseGravity();
        playerApplyFullPhysics();
        break;
    case 4:
        playerInputUpdate(0x30);
        playerSetBaseGravity();
        playerApplyFullPhysics();
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongHoverStartSpeedY[];
extern f32 gKongHoverStartAccelY[];
extern f32 gKongHoverTargetSpeeds[];

void playerStateHover(void) {
    playerSpawnJumpTrailEffects();
    switch (gCurrentActor->subState) {
    case 0:
        scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
        playerInputUpdate(0x2C);
        playerApplyFullPhysics();
        break;
    case 1:
        gCurrentActor->speedY = gKongHoverStartSpeedY[gCurrentCharacterIndex];
        gCurrentActor->accelY = gKongHoverStartAccelY[gCurrentCharacterIndex];
        playerUpdateTargetYawFromStick();
        gCurrentActor->subState++;
        playerInputUpdate(0x2B);
        playerApplyFullPhysics();
        break;
    case 2:
        playerApplyFullPhysics();
        playerInputUpdate(0x2D);
        playerUpdateFallAndStepSounds();
        break;
    case 3:
        playerInputUpdate(0x36);
        playerApplyFullPhysics();
        break;
    case 4:
        playerInputUpdate(0x36);
        playerApplyFullPhysics();
        break;
    case 5:
        gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
        gCurrentActor->accelY = gKongLightGravity[gCurrentCharacterIndex];
        gCurrentActor->subState++;
        playerInputUpdate(0x2B);
        gActivePlayerState->targetSpeed = gKongHoverTargetSpeeds[gCurrentCharacterIndex];
        playerApplyFullPhysics();
        break;
    case 6:
        playerApplyFullPhysics();
        playerInputUpdate(0x2C);
        playerSetTerminalVelocity700();
        playerUpdateFallAndStepSounds();
        break;
    case 7:
        playerInputUpdate(0x30);
        playerSetBaseGravity();
        playerApplyFullPhysics();
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateGroundPound(void) {
    switch (gCurrentActor->subState) {
    case 0:
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->speedY = 0.0f;
        playerInputUpdate(0x2E);
        playerApplyMotion();
        break;
    case 1:
        playerInputUpdate(0x2E);
        gCurrentActor->accelY = -30.0f;
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->speedY = -100.0f;
        gCurrentActor->subState++;
        playerApplyGravityAndMotion();
        break;
    case 2:
        playerInputUpdate(0x2E);
        playerUpdateFallAndStepSounds();
        playerApplyGravityAndMotion();
        break;
    case 3:
        playerInputUpdate(0x2E);
        if (!(gCurrentActor->contactFlags & 4)) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x96, 0xFF, 0x7F, 0x19);
            effectSpawnMultiTierRingWithActor(gCurrentActor, gCurrentKongInventory->slamLevel);
            camStartShake(gActivePlayerState->camActor, 0x14, gCurrentKongInventory->slamLevel * 5);
        }
        scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
        gCurrentActor->subState++;
        playerApplyGravityAndMotion();
        break;
    case 4:
        playerInputUpdate(0x2E);
        playerApplyGravityAndMotion();
        break;
    case 5:
        playerInputUpdate(0x2F);
        gCurrentActor->subState++;
        playerApplyFullPhysics();
        break;
    case 6:
        playerInputUpdate(0x2F);
        playerApplyFullPhysics();
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateTurnDecel(void) {
    switch (gCurrentActor->subState) {
    case 0:
        gActivePlayerState->decelRate = gActivePlayerState->decelRate / 1.8;
        gCurrentActor->subState++;
    case 1:
        playerInputUpdate(5);
        playerApplyFullPhysics();
        mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, gActivePlayerState->turnRate * 1.25);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern void *gPuffSprites[];
extern f32 gKongSlideBounceSpeeds[];

void playerStateSlopeSlide(void) {
    f32 pad;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    f32 scale;
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    if (gCurrentActor->subState < 2 || gSlopeSlideParticleMinSpeed < gCurrentActor->speedXZ) {
        scale = gCurrentActor->sub4->scaleY / 0.15;
        actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
        for (i = 0; i < gSlopeSlideParticleCount; i++) {
            x = (randomNonNegative() >> 15) % 10000 % gSlopeSlideParticleSpreadX - gSlopeSlideParticleSpreadX / 2;
            y = (randomNonNegative() >> 15) % 10000 % gSlopeSlideParticleSpreadY - gSlopeSlideParticleSpreadY / 2;
            z = (randomNonNegative() >> 15) % 10000 % gSlopeSlideParticleSpreadZ - gSlopeSlideParticleSpreadZ / 2;
            effectSetSpeed(gSlopeSlideParticleSinkSpeed);
            effectSetCallback(effectSinkBySpeedUpdate);
            effectSetDepth(1);
            effectCreateAtPosition(gPuffSprites[randomNonNegative() % 10000 % 3], gSlopeSlideParticleScale * scale, x * scale + nodeX, y * scale + nodeY, z * scale + nodeZ);
        }
    }
    switch (gCurrentActor->subState) {
    case 0:
        playerInputUpdate(5);
        gActivePlayerState->maxSpeed = 0.0f;
        break;
    case 1:
        playerInputUpdate(5);
        gCurrentActor->moveYaw = gCurrentActor->yaw;
        if (!(gActivePlayerState->stateFlags2 & 8)) {
            gCurrentActor->speedXZ = 140.0f;
        }
        gActivePlayerState->decelRate = 6.0f;
        gCurrentActor->subState++;
        break;
    case 2:
        if (gCurrentActor->hasArcBounds != 0) {
            f32 bounceSpeed = gKongSlideBounceSpeeds[gCurrentCharacterIndex];

            if (bounceSpeed < gCurrentActor->speedXZ && !(gActivePlayerState->stateFlags2 & 8)) {
                gCurrentActor->speedXZ = bounceSpeed;
                gActivePlayerState->slideLaunchSpeed = gKongSlideBounceSpeeds[gCurrentCharacterIndex];
            }
        }
        playerInputUpdate(5);
        break;
    case 3:
        gCurrentActor->speedXZ = 0.0f;
        playerInputUpdate(5);
        playerResumeLocomotionDecel(gCurrentActor);
        break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdate1WithZeroUnk4(void) {
    playerInputUpdate(1);
    gActivePlayerState->maxSpeed = 0.0f;
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateRunDecel(void) {
    switch (gCurrentActor->subState) {
    case 0:
        gActivePlayerState->decelRate = gActivePlayerState->decelRate / 1.8;
        gCurrentActor->subState++;
        gActivePlayerState->jumpStartTime = gScheduler.tickCount - 0x64;
        gActivePlayerState->turnRate = 0x50;
    case 1:
        playerInputUpdate(9);
        gActivePlayerState->decelRate = 10.0f;
        playerApplyDeceleration();
        mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, gActivePlayerState->turnRate * 1.25);
        break;
    case 2:
        if (gScheduler.tickCount - gActivePlayerState->jumpStartTime < 0x32) {
            switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                case 2:
                    gCurrentActor->state = 0x27;
                    gCurrentActor->subState = 0;
                    actorScriptStartByIndex(gCurrentActor, 0x40);
                    break;
                default:
                    gCurrentActor->state = 0x28;
                    gCurrentActor->subState = 0;
                    actorScriptStartByIndex(gCurrentActor, 0x41);
                    break;
            }
        }
        break;
    }
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateWalkDecel(void) {
    switch (gCurrentActor->subState) {
        case 0:
            gActivePlayerState->decelRate = gActivePlayerState->decelRate / 1.8;
            gCurrentActor->subState++;
            gActivePlayerState->jumpStartTime = gScheduler.tickCount - 0x64;
        case 1:
            playerInputUpdate(9);
            gActivePlayerState->decelRate = 10.0f;
            playerApplyDeceleration();
            mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, gActivePlayerState->turnRate * 1.25);
            break;
        case 2:
            if (gScheduler.tickCount - gActivePlayerState->jumpStartTime < 0x32) {
                gCurrentActor->state = 0x28;
                gCurrentActor->subState = 0;
                actorScriptStartByIndex(gCurrentActor, 0x41);
            }
            break;
    }
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateBrake(void) {
    switch (gCurrentActor->subState) {
        case 0:
            gActivePlayerState->decelRate = gActivePlayerState->decelRate / 1.8;
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 3) {
                gCurrentActor->speedXZ = 50.0f;
            }
            gCurrentActor->subState++;
        case 1:
            playerInputUpdate(0xA);
            mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, gActivePlayerState->turnRate * 1.25);
            break;
        case 2:
            playerInputUpdate(0xA);
            gActivePlayerState->decelRate = 50.0f;
            playerApplyDeceleration();
            mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, gActivePlayerState->turnRate * 1.25);
            break;
    }
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongTurnDecelRates[];

void playerStateSlopeSlideByCharacter(void) {
    mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
    playerUpdateFallAndStepSounds();
    switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
        case 1:
            switch (gCurrentActor->subState) {
                case 0:
                    playerSetTerminalVelocity5B0();
                    playerInputUpdate(0x17);
                    playerApplyGravityAndMotion();
                    break;
                case 1:
                    playerSetTerminalVelocity5B0();
                    playerInputUpdate(0x16);
                    playerApplyGravityAndMotion();
                    break;
            }
            break;
        case 0:
            switch (gCurrentActor->subState) {
                case 0:
                    gActivePlayerState->decelRate = 7.0f;
                    gActivePlayerState->airAccel = 8.0f;
                    gActivePlayerState->turnRate = 0x12C;
                    playerInputUpdate(0x15);
                    gActivePlayerState->maxSpeed = 0.0f;
                    playerApplyFullPhysics();
                    break;
                case 1:
                    gCurrentActor->speedXZ = gKongTurnDecelRates[gCurrentCharacterIndex];
                    gActivePlayerState->airAccel = 20.0f;
                    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
                    playerInputUpdate(0x15);
                    playerApplyGravityAndMotion();
                    break;
                case 2:
                    gCurrentActor->speedY = 150.0f;
                    gActivePlayerState->airAccel = 20.0f;
                    gActivePlayerState->targetSpeed = 200.0f;
                    playerInputUpdate(0x15);
                    gActivePlayerState->maxSpeed = 200.0f;
                    playerApplyFullPhysics();
                    gCurrentActor->subState++;
                    break;
                case 3:
                    gCurrentActor->speedXZ = 200.0f;
                    gActivePlayerState->targetSpeed = 200.0f;
                    playerInputUpdate(0x15);
                    playerApplyGravityAndMotion();
                    break;
            }
            break;
        default:
        case 3:
            switch (gCurrentActor->subState) {
                case 0:
                    gActivePlayerState->sharpTurn = 0;
                    gActivePlayerState->decelRate = 0.2f;
                    gActivePlayerState->airAccel = 8.0f;
                    gActivePlayerState->turnRate = 0x12C;
                    playerInputUpdate(0x15);
                    playerApplyGravityAndMotion();
                    break;
                case 1:
                    gActivePlayerState->decelRate = 20.0f;
                    gActivePlayerState->airAccel = 20.0f;
                    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
                    playerInputUpdate(0x15);
                    playerApplyGravityAndMotion();
                    break;
                case 2:
                    gActivePlayerState->sharpTurn = 1;
                    if (gScheduler.tickCount - gActivePlayerState->jumpStartTime < 0x14) {
                        gCurrentActor->state = 0x26;
                        gCurrentActor->subState = 0;
                        actorScriptStartByIndex(gCurrentActor, 0x3F);
                    }
                    playerInputUpdate(0x15);
                    playerApplyFullPhysics();
                    break;
            }
            break;
        case 6:
            switch (gCurrentActor->subState) {
                case 0:
                    gActivePlayerState->sharpTurn = 0;
                    gActivePlayerState->airAccel = 20.0f;
                    gActivePlayerState->turnRate = 0x12C;
                    playerInputUpdate(0x15);
                    gActivePlayerState->decelRate = 10.0f;
                    playerApplyDeceleration();
                    playerApplyGravityAndMotion();
                    break;
                case 1:
                    gActivePlayerState->airAccel = 30.0f;
                    gActivePlayerState->slideLaunchSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
                    playerApproachVelocity(gCurrentActor->yaw, gActivePlayerState->slideLaunchSpeed, gActivePlayerState->slideLaunchSpeed);
                    playerInputUpdate(0x15);
                    playerApplyGravityAndMotion();
                    break;
                case 2:
                    gActivePlayerState->sharpTurn = 1;
                    playerInputUpdate(0x15);
                    playerApplyFullPhysics();
                    break;
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 gKongRunAttackStopDecelRates[];
extern s16 gKongSteepSlideLaunchSpeeds[];

void playerStateSteepSlide(void) {
    mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
    playerUpdateFallAndStepSounds();
    switch (gCurrentActor->subState) {
        case 0:
            gActivePlayerState->decelRate = 0.2f;
            gActivePlayerState->airAccel = 10.0f;
            gActivePlayerState->turnRate = 0x32;
            gActivePlayerState->slideLaunchSpeed = gKongSteepSlideLaunchSpeeds[gCurrentCharacterIndex];
            playerInputUpdate(0x18);
            if (gCurrentActor->floorSlopeFactor != 0.0f) {
                gActivePlayerState->decelRate = 20.0f;
                playerApplyDeceleration();
            } else {
                playerApproachVelocity(gCurrentActor->yaw, gActivePlayerState->slideLaunchSpeed, gActivePlayerState->slideLaunchSpeed);
            }
            playerCheckLandingSfx();
            playerApplyGravityAndMotion();
            mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, gActivePlayerState->turnRate);
            if (gCurrentActor->hasArcBounds != 0) {
                gCurrentActor->speedXZ = gCurrentActor->speedXZ * 0.9;
            }
            break;
        case 1:
            playerInputUpdate(0x18);
            playerApplyGravityAndMotion();
            gCurrentActor->speedY = 150.0f;
            gCurrentActor->subState++;
            break;
        case 2:
            playerInputUpdate(0x18);
            playerApproachVelocity(gCurrentActor->yaw, gActivePlayerState->slideLaunchSpeed, gActivePlayerState->slideLaunchSpeed);
            playerApplyGravityAndMotion();
            mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, gActivePlayerState->turnRate);
            break;
        case 3:
            gActivePlayerState->decelRate = gKongRunAttackStopDecelRates[gCurrentCharacterIndex];
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 0) {
                playerInputUpdate(0x19);
            } else {
                playerInputUpdate(0x19);
            }
            playerApplyFullPhysics();
            break;
        case 4:
            gActivePlayerState->decelRate = gKongRunAttackStopDecelRates[gCurrentCharacterIndex];
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 0) {
                playerInputUpdate(0x19);
            } else {
                playerInputUpdate(0x19);
            }
            playerApplyFullPhysics();
            if (gActivePlayerState->maxSpeed != 0.0f) {
                playerResumeLocomotion(gCurrentActor);
            }
            break;
        case 5:
            playerInputUpdate(5);
            gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) % 4096;
            playerSetUnk586Flag();
            playerCheckLandingSfx();
            playerApplyGravityAndMotion();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 gKongChargeStopDecelRates[];

void playerStateDecelMotion(void) {
    playerUpdateFallAndStepSounds();
    switch (gCurrentActor->subState) {
        case 0:
            gActivePlayerState->decelRate = 20.0f;
            playerApplyDeceleration();
            playerApplyMotion();
            break;
        case 1:
            playerInputUpdate(0x1A);
            if (gActivePlayerState->slideLaunchSpeed < gCurrentActor->speedXZ) {
                gActivePlayerState->slideLaunchSpeed = gCurrentActor->speedXZ;
            }
            if (gCurrentActor->hasArcBounds != 0) {
                if (gKongSlideBounceSpeeds[gCurrentCharacterIndex] < gCurrentActor->speedXZ) {
                    gCurrentActor->speedXZ = gKongSlideBounceSpeeds[gCurrentCharacterIndex];
                    gActivePlayerState->slideLaunchSpeed = gKongSlideBounceSpeeds[gCurrentCharacterIndex];
                }
            }
            if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->yaw) == 0) {
                actorScriptStartByIndex(gCurrentActor, 0x49);
                gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) % 4096;
                gCurrentActor->subState = 3;
                gCurrentActor->speedXZ = gKongSlideBounceSpeeds[gCurrentCharacterIndex];
                gActivePlayerState->slideLaunchSpeed = gKongSlideBounceSpeeds[gCurrentCharacterIndex];
                break;
            }
            playerCheckLandingSfx();
            if (gCurrentActor->floorSlopeFactor != 0.0f) {
                gActivePlayerState->decelRate = 20.0f;
                playerApplyDeceleration();
            } else {
                playerApproachVelocity(gCurrentActor->yaw, gActivePlayerState->slideLaunchSpeed, gActivePlayerState->targetSpeed);
            }
            playerApplyGravityAndMotion();
            break;
        case 2:
            playerInputUpdate(0x1A);
            if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->yaw) == 0) {
                actorScriptStartByIndex(gCurrentActor, 0x49);
                gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) % 4096;
                gCurrentActor->subState++;
                gCurrentActor->speedXZ = gKongSlideBounceSpeeds[gCurrentCharacterIndex];
                gActivePlayerState->slideLaunchSpeed = gKongSlideBounceSpeeds[gCurrentCharacterIndex];
                break;
            }
            mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
            playerCheckLandingSfx();
            playerApplyDeceleration();
            playerApplyGravityAndMotion();
            gActivePlayerState->decelRate = gKongChargeStopDecelRates[gCurrentCharacterIndex];
            break;
        case 3:
            playerInputUpdate(5);
            gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) % 4096;
            playerSetUnk586Flag();
            playerCheckLandingSfx();
            playerApplyGravityAndMotion();
            break;
        case 4:
            playerInputUpdate(5);
            gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) % 4096;
            gActivePlayerState->decelRate = 5.0f;
            playerApplyDeceleration();
            playerSetUnk586Flag();
            playerCheckLandingSfx();
            playerApplyGravityAndMotion();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongSwimTurnSpeeds[];
extern f32 gKongSwimPaddleSpeeds[];
extern f32 gKongSwimSpeeds[];
extern s16 gKongSwimSurfaceDepths[];

s32 playerCheckSlopeLaunchArc(void) {
    if (gCurrentActor->hasArcBounds != 0) {
        if (mathAngleDistance(gCurrentActor->yaw, ((((gCurrentActor->arcYawMax - gCurrentActor->arcYawMin) & 0xFFF) / 2) + gCurrentActor->arcYawMin + 0x800) & 0xFFF) < 0x2BC) {
            if (gCurrentActor->speedXZ > 150.0f) {
                actorScriptStartByIndex(gCurrentActor, 0x49);
                gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) % 4096;
                gCurrentActor->subState = 2;
                gCurrentActor->speedXZ = gKongSlideBounceSpeeds[gCurrentCharacterIndex];
                gActivePlayerState->slideLaunchSpeed = gKongSlideBounceSpeeds[gCurrentCharacterIndex];
            } else {
                playerResumeLocomotion(gCurrentActor);
            }
            return 1;
        }
        mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
    }
    return 0;
}

extern EffectGridAsset gEffectSpriteDustPuff;

void playerStateSlopeSlideArc(void) {
    playerUpdateFallAndStepSounds();
    switch (gCurrentActor->subState) {
    case 0:
        gActivePlayerState->sharpTurn = 0;
        playerInputUpdate(0x1A);
        if (gActivePlayerState->slideLaunchSpeed < gCurrentActor->speedXZ) {
            gActivePlayerState->slideLaunchSpeed = gCurrentActor->speedXZ;
        }
        if (playerCheckSlopeLaunchArc() != 0) {
            break;
        }
        playerCheckLandingSfx();
        if (gCurrentActor->floorSlopeFactor != 0.0f) {
            gActivePlayerState->decelRate = 20.0f;
            playerApplyDeceleration();
        } else {
            playerApproachVelocity(gCurrentActor->yaw, gActivePlayerState->slideLaunchSpeed, gActivePlayerState->targetSpeed);
        }
        playerApplyGravityAndMotion();
        break;
    case 1:
        playerInputUpdate(0x1A);
        if (playerCheckSlopeLaunchArc() != 0) {
            break;
        }
        mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
        playerCheckLandingSfx();
        playerApplyDeceleration();
        playerApplyGravityAndMotion();
        gActivePlayerState->decelRate = gKongChargeStopDecelRates[gCurrentCharacterIndex];
        if (gCurrentActor->speedXZ > 20.0f) {
            if (randomLcgNext() % 3U == 0) {
                effectSetCallback(effectSineHorizontalDriftUpdate);
                effectSetFrameDelay(2);
                effectSetDepth(1);
                effectCreateAtActorBone(&gEffectSpriteDustPuff, 0.2f, gCurrentActor, 2, 0);
            }
            if (randomLcgNext() % 3U == 0) {
                effectSetCallback(effectSineHorizontalDriftUpdate);
                effectSetFrameDelay(2);
                effectSetDepth(1);
                effectCreateAtActorBone(&gEffectSpriteDustPuff, 0.2f, gCurrentActor, 3, 0);
            }
            if (randomLcgNext() % 3U == 0) {
                effectSetCallback(effectSineHorizontalDriftUpdate);
                effectSetFrameDelay(2);
                effectSetDepth(1);
                effectCreateAtActorBone(&gEffectSpriteDustPuff, 0.2f, gCurrentActor, 9, 0);
            }
            if (randomLcgNext() % 3U == 0) {
                effectSetCallback(effectSineHorizontalDriftUpdate);
                effectSetFrameDelay(2);
                effectSetDepth(1);
                effectCreateAtActorBone(&gEffectSpriteDustPuff, 0.2f, gCurrentActor, 0xA, 0);
            }
        }
        break;
    case 2:
        playerInputUpdate(5);
        gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) % 4096;
        playerSetUnk586Flag();
        playerCheckLandingSfx();
        playerApplyGravityAndMotion();
        break;
    case 3:
        playerInputUpdate(5);
        gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) % 4096;
        gActivePlayerState->decelRate = 5.0f;
        playerApplyDeceleration();
        playerSetUnk586Flag();
        playerCheckLandingSfx();
        playerApplyGravityAndMotion();
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdate8(void) {
    mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
    playerInputUpdate(8);
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSwimTurn(void) {
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    gCurrentActor->renderFlags |= 0x200;
    switch (gCurrentActor->subState) {
    case 0:
        playerInputUpdate(3);
        gActivePlayerState->maxSpeed = gKongSwimTurnSpeeds[gCurrentCharacterIndex];
        gActivePlayerState->targetYaw = gCurrentActor->moveYaw;
        mathAngleStepToward(&gCurrentActor->yaw, (gCurrentActor->moveYaw + 0x800) & 0xFFF, gActivePlayerState->turnRate * 2);
        break;
    case 1:
        playerInputUpdate(3);
        gActivePlayerState->maxSpeed = 0.0f;
        gCurrentActor->speedXZ = 0.0f;
        break;
    case 2:
        playerResumeLocomotion(gCurrentActor);
        break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSwimTread(void) {
    playerInputUpdate(3);
    gCurrentActor->renderFlags |= 0x200;
    switch (gCurrentActor->subState) {
    case 0:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gActivePlayerState->damageSource->yaw + 0x800, 8.0f);
        gActivePlayerState->maxSpeed = 0.0f;
        gCurrentActor->speedXZ = 0.0f;
        playerApplyFullPhysics();
        break;
    case 1:
        playerResumeLocomotion(gCurrentActor);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSwimIdle(void) {
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    playerInputUpdate(3);
    switch (gCurrentActor->subState) {
    case 0:
        gActivePlayerState->maxSpeed = 0.0f;
        gCurrentActor->speedXZ = 0.0f;
        playerApplyFullPhysics();
        break;
    case 1:
        effectSpawnJointBeam(1, 4, 5, 8);
        break;
    case 2:
        effectSpawnRandomBoneDebris(1, 8);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSwimDrown(void) {
    playerStateQueueCallback(0x5C, 0, gCurrentPlayerIndex);
    playerInputUpdate(3);
    gCurrentActor->collisionMode = 1;
    gActivePlayerState->maxSpeed = 0.0f;
    gCurrentActor->speedXZ = 0.0f;
    playerApplyFullPhysics();
    if (gActivePlayerState->fadeLevel == 0) {
        playerRefillHealth(gCurrentActor, gCurrentPlayerIndex);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSwimPaddle(void) {
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    gCurrentActor->renderFlags |= 0x200;
    switch (gCurrentActor->subState) {
    case 0:
        playerInputUpdate(3);
        gActivePlayerState->maxSpeed = gKongSwimPaddleSpeeds[gCurrentCharacterIndex];
        gActivePlayerState->targetYaw = gCurrentActor->moveYaw;
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gActivePlayerState->damageSource->yaw + 0x800, 8.0f);
        playerApplyFullPhysics();
        break;
    case 1:
        playerInputUpdate(3);
        gActivePlayerState->maxSpeed = 0.0f;
        if (gPlayerCharacterId[gCurrentPlayerIndex] == 4) {
            f32 frame = gCurrentActor->sub4->model->frame;

            if (frame >= 29.0f && frame < 33.0f) {
                gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) & 0xFFF;
                gCurrentActor->speedXZ = 150.0f;
                playerApplyGravityAndMotion();
                break;
            }
            if (frame >= 48.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 60.0f;
                playerApplyGravityAndMotion();
                break;
            }
        }
        gCurrentActor->speedXZ = 0.0f;
        playerApplyFullPhysics();
        break;
    case 2:
        gCurrentActor->speedXZ = 0.0f;
        playerResumeLocomotion(gCurrentActor);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSwimBackwards(void) {
    gCurrentActor->renderFlags |= 0x200;
    switch (gCurrentActor->subState) {
    case 0:
        playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
        playerInputUpdate(4);
        mathAngleStepToward(&gCurrentActor->yaw, (gCurrentActor->moveYaw + 0x800) & 0xFFF, gActivePlayerState->turnRate * 2);
        if (gCurrentActor->hasArcBounds != 0) {
            gCurrentActor->speedXZ = gCurrentActor->speedXZ * 0.5;
        }
        break;
    case 1:
        playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
        gActivePlayerState->maxSpeed = 0.0f;
        if (gCurrentActor->hasArcBounds != 0) {
            gCurrentActor->speedXZ = gCurrentActor->speedXZ * 0.5;
        }
        break;
    case 2:
        gCurrentActor->speedXZ = 0.0f;
        playerStateQueueCallback(0x18, 0, gCurrentPlayerIndex);
        break;
    }
    if (gCurrentActor->waterY < gKongSwimSurfaceDepths[gCurrentCharacterIndex] + gCurrentActor->y) {
        gCurrentActor->y = gCurrentActor->waterY - gKongSwimSurfaceDepths[gCurrentCharacterIndex];
    }
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->decelRate = 2.0f;
    playerApplyMotionWithHorizontalVelocity();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSurfaceSwimSprint(void) {
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    gCurrentActor->renderFlags |= 0x200;
    switch (gCurrentActor->subState) {
    case 0:
        gCurrentActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex];
        playerInputUpdate(5);
        gActivePlayerState->maxSpeed = gKongSwimSpeeds[gCurrentCharacterIndex];
        if (gActivePlayerState->isHoldingObject != 0) {
            sfxStopSlotSound(gCurrentActor, 0);
            gActivePlayerState->isHoldingObject = 0;
        }
        gActivePlayerState->targetYaw = gCurrentActor->moveYaw;
        mathAngleStepToward(&gCurrentActor->yaw, (gCurrentActor->moveYaw + 0x800) & 0xFFF, gActivePlayerState->turnRate * 2);
        break;
    case 1:
        playerInputUpdate(3);
        gCurrentActor->speedXZ = 0.0f;
        break;
    case 2:
        playerInputUpdate(3);
        playerResumeLocomotion(gCurrentActor);
        break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSwimSink(void) {
    f64 scale = gCurrentActor->sub4->scaleY;

    actorSetUniformScale(gCurrentActor, (0.001 - scale) * 0.01 + scale);
    gCurrentActor->alpha -= 0x14;
    if (gCurrentActor->alpha < 0) {
        gCurrentActor->alpha = 0;
    }
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    switch (gCurrentActor->subState) {
    case 0:
        playerApplyFullPhysics();
        break;
    case 1:
        playerApplyFullPhysics();
        if (gActivePlayerState->stateTimer-- == 0) {
            gCurrentActor->subState++;
        }
        break;
    case 2:
        if (gCurrentMap != 0x52 && gCurrentMap != 0xE) {
            playerRefillHealth(gCurrentActor, gCurrentPlayerIndex);
        }
        gCurrentActor->subState++;
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSwimDrift(void) {
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongSwimStrokeSpeeds[];
extern f32 gKongSwimStrokeMaxSpeeds[];

void playerStateSwimStroke(void) {
    u8 flag;
    u8 timer;

    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    playerInputUpdate(1);
    switch (gCurrentActor->subState) {
        case 0:
            gCurrentActor->accelY = gKongSwimStrokeSpeeds[gCurrentCharacterIndex];
            if (gGlobalCutsceneFlags & 2) {
                sfxPlayOnFreeSlot(0x424, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
            if (gPlayerCount == 1) {
                camStartPathNearWall(gPrimaryPlayerActor, 0xC, 0x25, 0x85);
            }
            gCurrentActor->subState++;
            /* fallthrough */
        case 1:
            gActivePlayerState->maxSpeed = gKongSwimStrokeMaxSpeeds[gCurrentCharacterIndex];
            gActivePlayerState->targetYaw = gCurrentActor->moveYaw;
            mathAngleStepToward(&gCurrentActor->yaw, (gCurrentActor->moveYaw + 0x800) & 0xFFF, gActivePlayerState->turnRate * 2);
            playerApplyFullPhysics();
            gActivePlayerState->stateTimer = 0xF;
            gActivePlayerState->swimStrokeTriggered = 0;
            break;
        case 2:
            gCurrentActor->subState++;
            gCurrentActor->speedXZ = 0.0f;
            playerApplyMotion();
            break;
        case 3:
            flag = mpIsMatchType(0);
            if (gActivePlayerState->stateTimer == 0 && gActivePlayerState->swimStrokeTriggered == 0) {
                if (!flag) {
                    playerSpawnSpiralDriftEffects();
                }
                gActivePlayerState->swimStrokeTriggered = 1;
            } else {
                gActivePlayerState->stateTimer--;
            }
            if (gActivePlayerState->swimStrokeTriggered != 0) {
                timer = gActivePlayerState->stateTimer;
                if (timer >= 0xBF) {
                    if (!flag && timer % 3 == 0) {
                        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, ((timer & 2) / 2) + 0x57, 0xFF, 0x7F, 0x1E);
                    }
                } else if (flag) {
                    playerRefillHealth(gCurrentActor, gCurrentPlayerIndex);
                }
            }
            if ((gActivePlayerState->stateFlags & 0x1000) && !(gFrameCounter & 3)) {
                effectSetColor(0x64, 0x64, 0x64, 0xC8);
                effectSetFrameDelay(2);
                effectSpawnBoneDefault(gCurrentActor, ((randomNonNegative() >> 15) % 32767) % 8 + 1, 0.4f, 0.0f, 0.0f, 0.0f, -0x50);
            }
            gCurrentActor->speedXZ = 0.0f;
            playerApplyMotion();
            break;
        default:
            if (gPlayerCount >= 2) {
                playerRefillHealth(gCurrentActor, gCurrentPlayerIndex);
            }
            gActivePlayerState->stateFlags &= ~0x1000;
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateUnderwaterPaddle(void) {
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x45);
            gActivePlayerState->maxSpeed = 0.0f;
            break;
        case 1:
            playerInputUpdate(0x44);
            gActivePlayerState->maxSpeed = 0.0f;
            break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateUnderwaterSink(void) {
    s16 nextState;

    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x46);
            gActivePlayerState->maxSpeed = 0.0f;
            break;
        case 1:
            if (playerInputUpdate(0x46) == 0) {
                nextState = playerSelectSurfaceState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);
                if (nextState != 0x3F) {
                    gCurrentActor->state = nextState;
                    gCurrentActor->subState = 0;
                }
            }
            break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateUnderwaterLand(void) {
    s16 nextState;

    playerCheckLandingSfx();
    if (playerInputUpdate(0x46) == 0) {
        nextState = playerSelectSurfaceState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);
        if (nextState != 0x40) {
            gCurrentActor->state = nextState;
            gCurrentActor->subState = 0;
            if (nextState == 0x3F) {
                gCurrentActor->subState = 1;
            }
        }
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateScriptTransition(void) {
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(1);
            break;
        case 1:
            gCurrentActor->state = 0x3C;
            gCurrentActor->subState = 1;
            actorScriptStartByIndex(gCurrentActor, 0xB);
            break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdate1FullPhysics(void) {
    playerInputUpdate(1);
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongUnderwaterRampTargetSpeed[];
extern f32 gKongUnderwaterRampAirAccel[];
extern f32 gKongUnderwaterRampDecelRate[];
extern s16 gKongUnderwaterRampTurnRate[];
extern f32 gKongCrouchHighJumpAccelY[];

void playerStateUnderwaterRamp(void) {
    switch (gCurrentActor->subState) {
        case 0:
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
            playerInputUpdate(0x47);
            playerApplyGravityAndMotion();
            playerApplyDeceleration();
            gActivePlayerState->airAccel = gKongUnderwaterRampAirAccel[gCurrentCharacterIndex];
            gActivePlayerState->decelRate = gKongUnderwaterRampDecelRate[gCurrentCharacterIndex];
            gActivePlayerState->targetSpeed = gKongUnderwaterRampTargetSpeed[gCurrentCharacterIndex];
            gActivePlayerState->turnRate = gKongUnderwaterRampTurnRate[gCurrentCharacterIndex];
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            gCurrentActor->accelY = gKongCrouchHighJumpAccelY[gCurrentCharacterIndex];
            gCurrentActor->speedXZ = 0.0f;
            gCurrentActor->subState++;
            playerInputUpdate(0x47);
            playerSetTerminalVelocity754();
            playerApplyGravityAndMotion();
            break;
        case 2:
            mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x32);
            playerSetTerminalVelocity754();
            playerUpdateFallAndStepSounds();
            playerApplyFullPhysics();
            mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x32);
            playerInputUpdate(0x47);
            break;
        case 3:
            playerInputUpdate(0x35);
            if (gPlayerPadState[gCurrentPlayerIndex].stickMagNorm != 0.0f) {
                scriptSetActorRampTarget(gCurrentActor, 3.0f, 0.0f);
            }
            gActivePlayerState->maxSpeed = 0.0f;
            playerSetBaseGravity();
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongCrouchLeapSpeeds[];
extern f32 gKongCrouchLeapAccelY[];
extern f32 gKongDiveLandDecelRates[];

void playerStateDive(void) {
    switch (gCurrentActor->subState) {
        case 0:
            gCurrentActor->targetYaw = gCurrentActor->moveYaw;
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0);
            playerInputUpdate(0x48);
            playerApplyGravityAndMotion();
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            gCurrentActor->accelY = gKongCrouchLeapAccelY[gCurrentCharacterIndex];
            gCurrentActor->speedXZ = gKongCrouchLeapSpeeds[gCurrentCharacterIndex];
            gCurrentActor->targetYaw = gCurrentActor->moveYaw;
            gCurrentActor->subState++;
            playerInputUpdate(0x48);
            playerSetTerminalVelocity754();
            playerApplyGravityAndMotion();
            break;
        case 2:
            playerSetTerminalVelocity754();
            playerUpdateFallAndStepSounds();
            playerApplyGravityAndMotion();
            playerInputUpdate(0x48);
            break;
        case 3:
            gActivePlayerState->decelRate = gKongDiveLandDecelRates[gCurrentCharacterIndex];
            playerInputUpdate(0x33);
            playerSetBaseGravity();
            playerApplyFullPhysics();
            break;
        case 4:
            if (gActivePlayerState->maxSpeed > 10.0f) {
                playerResumeLocomotion(gCurrentActor);
            }
            gActivePlayerState->decelRate = gKongDiveLandDecelRates[gCurrentCharacterIndex];
            playerInputUpdate(0x33);
            playerSetBaseGravity();
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern PlayerStruct *gPlayerSlots;
extern s16 gKongNormalSwimExitDepths[];
extern s16 gKongNormalSwimSurfaceDepths[];
extern s16 gKongSwimExitDepths[];
extern s16 gKongDiveFrames[];
extern s16 gKongDiveAngles[];

s32 playerCanPerformActionCheck(void) {
    f32 surfaceOffset;
    f32 exitDepth;

    if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
        surfaceOffset = gKongNormalSwimSurfaceDepths[gCurrentCharacterIndex];
    } else {
        surfaceOffset = gKongSwimSurfaceDepths[gCurrentCharacterIndex];
    }
    if (gCurrentActor->state == 0x4E && playerInputCanPerformFairySnap() != 0 && gCurrentActor->subState != 0 &&
        gCurrentActor->y + surfaceOffset < gCurrentActor->waterY - 10.0f) {
        gActivePlayerState->subTimer = gKongDiveAngles[gCurrentCharacterIndex];
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        gActivePlayerState->actionTimer = gKongDiveFrames[gCurrentCharacterIndex] * 0.5;
        gCurrentActor->state = 0x4F;
        gCurrentActor->subState = 1;
        if (gCurrentActor->speedY > 0.0f) {
            gCurrentActor->speedY = 0.0f;
        }
        actorScriptStartByIndex(gCurrentActor, 0x36);
        controllerAnimSetStateRemap(gCurrentActor, 0x31, 0, 8.0f);
        scriptSetActorRampTarget(gCurrentActor, 0.5f, 0);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x10, 0xFF, 0x7F, 1);
    }
    if (gCurrentActor->waterY < gCurrentActor->y + surfaceOffset) {
        gCurrentActor->y = gCurrentActor->waterY - surfaceOffset;
    }
    exitDepth = (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) ? gKongNormalSwimExitDepths[gCurrentCharacterIndex] : gKongSwimExitDepths[gCurrentCharacterIndex];
    if (gCurrentActor->waterY - gCurrentActor->floorY < exitDepth) {
        playerStateQueueCallback(2, 0, gCurrentPlayerIndex);
        return 1;
    }
    return 0;
}

extern f32 gKongSwimTopSpeeds[];
extern f32 gKongSurfaceSwimRiseRates[];

void playerStateSurfaceSwim(void) {
    f32 curSpeedY;
    f32 step;
    f32 sinkStep;
    f32 target;
    f32 animSpeed;

    curSpeedY = gCurrentActor->speedY;
    step = gKongSurfaceSwimRiseRates[gCurrentCharacterIndex];
    target = gKongSwimTopSpeeds[gCurrentCharacterIndex];
    if (curSpeedY < 0.0f) {
        sinkStep = -curSpeedY / 3.0f;
        step = MAX(step, sinkStep);
    }
    if (gCurrentActor->distToFloor == 0.0f && curSpeedY < -0.1) {
        gCurrentActor->speedY = -0.1f;
    }
    curSpeedY = gCurrentActor->speedY;
    gCurrentActor->speedY = mathApproachF32(curSpeedY, target, step);
    gActivePlayerState->swimFrames = 0;
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x4E);
            playerApplyMotionWithHorizontalVelocity();
            break;
        case 1:
            playerInputUpdate(0x4D);
            playerApplyMotionWithHorizontalVelocity();
            if (gCurrentActor->speedXZ != 0.0f) {
                actorScriptStartByIndex(gCurrentActor, 0x3A);
                gCurrentActor->subState = 2;
            }
            break;
        default:
            playerInputUpdate(0x4D);
            playerApplyMotionWithHorizontalVelocity();
            if (gCurrentActor->speedXZ == 0.0f) {
                actorScriptStartByIndex(gCurrentActor, 0x33);
                gCurrentActor->subState = 1;
            } else {
                animSpeed = gActivePlayerState->maxSpeed * 1.5 / 40.0;
                if (gCurrentActor->sub4->speed < animSpeed) {
                    scriptSetActorRampTarget(gCurrentActor, animSpeed, 0.0f);
                } else {
                    scriptSetActorRampTarget(gCurrentActor, animSpeed, 5.0f);
                }
            }
            break;
    }
    playerCanPerformActionCheck();
    gCurrentActor->flags &= ~1;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSurfaceSwimStroke(void) {
    gActivePlayerState->swimFrames = 0;
    switch (gCurrentActor->subState) {
        case 0:
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0);
            playerInputUpdate(0x4B);
            playerApplyFullPhysics();
            break;
        case 1:
            gCurrentActor->roll = 0;
            gCurrentActor->pitch = 0;
            playerResumeLocomotion(gCurrentActor);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 gKongUnderwaterStrokeFrames[];
extern f32 gKongUnderwaterStrokeSpeeds[];

void playerStateSurfaceTreadWater(void) {
    f32 target; // FAKE: one local for the case 0 buoyancy target speed and the case 1 animation speed: a separate animation-speed local (either declaration slot) changes regalloc (Q1055)

    gActivePlayerState->swimFrames++;
    gActivePlayerState->airAccel = gKongSwimAccel[gCurrentCharacterIndex];
    switch (gCurrentActor->subState) {
        case 0:
            playerInputUpdate(0x4C);
            target = gKongSwimBuoyancy[gCurrentCharacterIndex];
            gCurrentActor->speedY = mathApproachF32(gCurrentActor->speedY, target, gActivePlayerState->slideSpeed);
            if (target <= gCurrentActor->speedY) {
                if (gCurrentActor->speedXZ != 0.0f || gActivePlayerState->actionTimer != 0) {
                    gCurrentActor->subState = 3;
                } else {
                    gCurrentActor->subState = 2;
                }
                gCurrentActor->sub4->scriptWaitFlags &= ~0x4000;
            }
            playerDecelerateAndApplyMotion();
            effectSpawnAuraBurst(1);
            goto end;
        case 1:
            playerInputUpdate(0x4F);
            playerApplyDecelVelocityVector(0.0f);
            if (gActivePlayerState->actionTimer == 0) {
                gCurrentActor->subState = 3;
            }
            target = gActivePlayerState->actionTimer / 7.5 + 1.0;
            if (gCurrentActor->sub4->speed < target) {
                scriptSetActorRampTarget(gCurrentActor, target, 0.0f);
            } else {
                scriptSetActorRampTarget(gCurrentActor, target, 15.0f);
            }
            effectSpawnAuraBurst(2);
            if (gCurrentActor->waterY < gKongSwimSurfaceDepths[gCurrentCharacterIndex] + gCurrentActor->y) {
                gCurrentActor->y = gCurrentActor->waterY - gKongSwimSurfaceDepths[gCurrentCharacterIndex];
            }
            goto end;
        default:
            playerInputUpdate(0x54);
            playerApplyDecelVelocityVector(gKongSwimBuoyancy[gCurrentCharacterIndex]);
            if (gCurrentActor->speedXZ != 0.0f) {
                gActivePlayerState->unk18 = 0;
                gCurrentActor->subState = 3;
            } else if (gActivePlayerState->idleDelay != 0) {
                gActivePlayerState->idleDelay--;
                if (gActivePlayerState->idleDelay == 0) {
                    actorScriptStartByIndex(gCurrentActor, 0x34);
                }
            }
            playerClampWaterSurfaceHeight(gCurrentActor);
            goto end;
        case 3:
            playerInputUpdate(0x50);
            playerApplyDecelVelocityVector(0.0f);
            break;
        case 4:
            playerInputUpdate(0x51);
            gActivePlayerState->subTimer = gCurrentActor->roll;
            gActivePlayerState->pitchAngle = gCurrentActor->yaw;
            gActivePlayerState->targetSpeed = gKongUnderwaterStrokeSpeeds[gCurrentCharacterIndex];
            gActivePlayerState->actionTimer = gKongUnderwaterStrokeFrames[gCurrentCharacterIndex];
            playerApplyDecelVelocityVector(0.0f);
            gCurrentActor->subState++;
            break;
        case 5:
            playerInputUpdate(0x51);
            playerApplyDecelVelocityVector(0.0f);
            break;
        case 6:
            playerInputUpdate(0x52);
            playerApplyDecelVelocityVector(0.0f);
            break;
        case 7:
            playerInputUpdate(0x51);
            playerApplyDecelVelocityVector(0.0f);
            break;
        case 8:
            playerInputUpdate(0x53);
            playerApplyDecelVelocityVector(0.0f);
            break;
    }
    if (gCurrentActor->speedXZ == 0.0f || gActivePlayerState->unk18 != 0) {
        gActivePlayerState->idleDelay = gKongSwimIdleDelays[gCurrentCharacterIndex];
        scriptSetActorRampTarget(gCurrentActor, 0.5f, gActivePlayerState->idleDelay);
        gCurrentActor->subState = 2;
    }
    playerClampWaterSurfaceHeight(gCurrentActor);
end:
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSurfacePaddleTurn(void) {
    gActivePlayerState->swimFrames = 0;
    gCurrentActor->pitch = 0;
    gCurrentActor->roll = 0;
    switch (gCurrentActor->subState) {
        case 0:
            playerUpdateTargetYawFromStick();
            playerInputUpdate(0x21);
            playerApplyMotionWithHorizontalVelocity();
            break;
        case 1:
            playerApplyFullPhysics();
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            gCurrentActor->subState++;
            playerInputUpdate(0x21);
            playerSetBaseGravityIfFalling();
            break;
        case 2:
            playerApplyFullPhysics();
            playerInputUpdate(0x21);
            if (gCurrentActor->actorType == 5) {
                playerInputUpdate(0x22);
            } else {
                playerInputUpdate(0x21);
            }
            playerSetBaseGravityIfFalling();
            break;
        case 3:
            playerApplyFullPhysics();
            playerInputUpdate(0x30);
            playerSetBaseGravity();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateFreezeIdle(void) {
    playerInputUpdate(1);
    gCurrentActor->speedXZ = 0.0f;
    gCurrentActor->speedY = 0.0f;
    playerApplyMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateFreezeIdleCopy(void) {
    playerStateFreezeIdle();
}

extern EffectGridAsset gEffectSpriteSmokePuff;

void playerStateEnterFallOnCheck(void) {
    s32 decel;

    if (gCurrentActor->hasArcBounds) {
        gCurrentActor->speedXZ = 0.0f;
        playerEnterFall(gCurrentActor);
    }
    if (gCurrentActor->hasArcBounds || ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1))) {
        camReturnToFollow(gActivePlayerState->camActor, gCurrentActor);
    }
    if (!(gCurrentActor->contactFlags & 1)) {
        effectSetDepth(1);
        effectSetDuration(1);
        effectCreateAtActorBone(&gEffectSpriteSmokePuff, 0.8f, gCurrentActor, 1, 0);
    }
    decel = (gCurrentActor->contactFlags & gCurrentActor->prevContactFlags & 1) ? 2 : 1;
    if (!gCurrentActor->prevContactFlags & gCurrentActor->contactFlags & 1) {
        gCurrentActor->speedXZ *= 0.25;
    }
    if (gCurrentActor->speedXZ < decel) {
        gCurrentActor->speedXZ = 0.0f;
    } else {
        gCurrentActor->speedXZ -= decel;
    }
    playerInputUpdate(1);
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongTargetLaunchGravity[];
extern f32 gKongDecelRate[];

void playerStateDamageFallTumble(void) {
    f32 pad;
    f32 dy;
    f32 dist;
    f32 dx;
    f32 dz;
    f32 launchSpeed;
    f32 flightFrames;
    s32 decel;

    switch (gCurrentActor->subState) {
        case 0:
            gCurrentActor->flags &= 0xFFBFFFFF;
            if (gCurrentActor->hasArcBounds || ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1))) {
                camReturnToFollow(gActivePlayerState->camActor, gCurrentActor);
            }
            if (!(gCurrentActor->contactFlags & 1)) {
                effectSetDepth(1);
                effectSetDuration(1);
                effectCreateAtActorBone(&gEffectSpriteSmokePuff, 0.8f, gCurrentActor, 1, 0);
            }
            decel = (gCurrentActor->contactFlags & gCurrentActor->prevContactFlags & 1) ? 2 : 1;
            if (!gCurrentActor->prevContactFlags & gCurrentActor->contactFlags & 1) {
                gCurrentActor->speedXZ = gCurrentActor->speedXZ * 0.25;
            }
            if (gCurrentActor->speedXZ < decel) {
                gCurrentActor->speedXZ = 0.0f;
            } else {
                gCurrentActor->speedXZ = gCurrentActor->speedXZ - decel;
            }
            gCurrentActor->roll = mathAtan2(gCurrentActor->speedXZ, gCurrentActor->speedY) * 4096.0f / 6.2831855f;
            gCurrentActor->yaw = (mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, gActivePlayerState->launchTargetX, gActivePlayerState->launchTargetZ) + 0x800) % 4095;
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            dy = gActivePlayerState->launchTargetY - gPrimaryPlayerActor->y;
            dy = dy / (gPrimaryPlayerActor->sub4->scaleY * 0.16666666675);
            dz = gActivePlayerState->launchTargetZ - gPrimaryPlayerActor->z;
            dx = gActivePlayerState->launchTargetX - gPrimaryPlayerActor->x;
            dist = sqrtf(dz * dz + dx * dx) / (gPrimaryPlayerActor->sub4->scaleY * 0.16666666675);
            launchSpeed = gPrimaryPlayerActor->speedXZ;
            if (launchSpeed == 0.0) {
                launchSpeed = 1.0f;
            }
            flightFrames = dist / launchSpeed - 1.0f;
            if (flightFrames < 1.0f) {
                flightFrames = 1.0f;
            }
            gPrimaryPlayerActor->speedY = (0.0 - (gKongTargetLaunchGravity[gCurrentCharacterIndex] * 0.5 * (flightFrames * flightFrames) - dy)) / flightFrames;
            gPrimaryPlayerActor->accelY = -0.001f;
            if (flightFrames < 2.0f || launchSpeed < 2.0) {
                playerSetBaseGravity();
                gCurrentActor->subState++;
            }
            if (gCurrentActor->hasArcBounds) {
                gCurrentActor->speedXZ = 0.0f;
                playerSetBaseGravity();
                gCurrentActor->subState++;
            }
            playerInputUpdate(1);
            break;
        case 1:
            playerInputUpdate(0x20);
            actorScriptStartByIndex(gCurrentActor, 0x23);
            gCurrentActor->roll = 0;
            playerSetBaseGravity();
            gCurrentActor->subState++;
            break;
        case 2:
            playerInputUpdate(0x20);
            break;
        case 3:
            sfxPlayScriptActorSoundForPlayer(gCurrentActor, 0x10, 0);
            gActivePlayerState->decelRate = gKongDecelRate[gCurrentCharacterIndex];
            gCurrentActor->subState++;
            /* fallthrough */
        case 4:
            playerApplyDeceleration();
            playerInputUpdate(0x30);
            break;
    }
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerApproachAirVelocity(void) {
    playerInputUpdate(5);
    if (gCurrentActor->speedY < 0.0f) {
        gActivePlayerState->launchSpeedXZ = 0.0f;
    }
    playerApproachVelocity(gActivePlayerState->launchYaw, gActivePlayerState->launchSpeedXZ, gActivePlayerState->targetSpeed);
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerUpdateAirTumble(void) {
    f32 rate;
    f32 animSpeed;

    playerInputUpdate(0x4A);
    switch (gCurrentActor->subState) {
        case 0:
            if (gActivePlayerState->targetSpeed < gCurrentActor->speedXZ) {
                playerApplyDeceleration();
                playerApplyGravityAndMotion();
            } else {
                playerApplyFullPhysics();
            }
            rate = gCurrentActor->speedXZ * 0.025;
            animSpeed = (rate > 1.0) ? rate : 1.0;
            scriptSetActorRampTarget(gCurrentActor, animSpeed, 0.0f);
            break;
        case 1:
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerClearPitchRollFlags(Actor *actor) {
    actor->roll = 0;
    actor->pitch = 0;
    actor->flags &= ~1;
}

void playerStateCutsceneIdle(void) {
    s32 channel;
    f32 volume;

    playerInputUpdate(1);
    if (gCurrentActor->subState < 3 ||
        (camIsPathFlag4Active() != 0 && (camIsPlayingPath(7) != 0 || camIsPlayingPath(0) != 0 || camIsPlayingPath(4) != 0 ||
                                  camIsPlayingPath(9) != 0 || camIsPlayingPath(8) != 0))) {
        mapChunkSetIndexOverride(1);
    }
    switch (gCurrentActor->subState) {
        case 0:
            if (!(gGlobalCutsceneFlags & 2)) {
                gCurrentActor->collisionMode = 1;
            }
            break;
        case 1:
            volume = 1.0f;
            channel = 0xA;
            switch (gCurrentActor->actorType) {
                case 2:
                    channel = 0xB;
                    break;
                case 5:
                    channel = 0xD;
                    break;
                case 4:
                    channel = 0xC;
                    if (!(gGlobalCutsceneFlags & 2)) {
                        volume = 0.82f;
                    }
                    break;
                case 6:
                    channel = 9;
                    break;
            }
            sfxAllocateChannel(channel, volume);
            gCurrentActor->subState++;
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongHoldPutDownAngles[];

extern EffectGridAsset gEffectSpriteSparkleYellow;

void playerStateTransformSparkles(void) {
    f32 pad;
    f32 posY;

    playerInputUpdate(1);
    if (gCurrentActor->subState == 1 || gCurrentActor->subState == 2) {
        randomNonNegative();
        posY = (randomNonNegative() >> 15) % 30 + gCurrentActor->y;
        randomNonNegative();
        effectSetDepth(1);
        effectSetSpeed((gActivePlayerState->rampLevel << 16) + (s32)(15.0 * (gCurrentActor->alpha / 255.0)));
        effectSetCallback(effectOrbitXZUpdate);
        effectCreateAtPosition(&gEffectSpriteSparkleYellow, 0.5f, gCurrentActor->x, posY, gCurrentActor->z);
    }
    switch (gCurrentActor->subState) {
    case 0:
        gActivePlayerState->rampLevel = 0;
        gCurrentActor->subState++;
        gCurrentActor->flags &= 0xFFFF7FFF;
        gCurrentActor->alpha = 0xFF;
        break;
    case 1:
        gActivePlayerState->rampLevel += 0x1E;
        if (gActivePlayerState->rampLevel >= 0x191) {
            gActivePlayerState->rampLevel = 0x190;
        }
        if (gActivePlayerState->rampLevel == 0xD2) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x264, 0xFF, 0x64, 0x19);
        }
        if (gActivePlayerState->rampLevel >= 0x12D) {
            gActivePlayerState->stateFlags &= ~0x40;
            gCurrentActor->alpha -= 5;
            if (gCurrentActor->alpha < 0xA) {
                gCurrentActor->subState++;
            }
        }
        break;
    case 2:
        mapSaveSlotAndTransition(gActivePlayerState->destMap, 0, 0, 3);
        gCurrentActor->subState++;
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStatePonytailFloat(void) {
    f32 dist;

    switch (gCurrentActor->subState) {
    case 0:
        gCurrentActor->speedY = 0.0f;
        gCurrentActor->speedXZ = 0.0f;
        gActivePlayerState->decelRate = 1.0f;
        gActivePlayerState->airAccel = 3.0f;
        gCurrentActor->accelY = 2.0f;
        gActivePlayerState->bobPhase = 0;
        gActivePlayerState->floatBaseY = gCurrentActor->y;
        gCurrentActor->subState++;
        break;
    case 1:
        playerInputUpdate(0x43);
        mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x32);
        gCurrentActor->y = gActivePlayerState->floatBaseY;
        playerApplyFullPhysics();
        if (gActivePlayerState->floatBaseY - gCurrentActor->yawSpeed > 50.0f) {
            gCurrentActor->y -= 1.0;
        }
        gActivePlayerState->floatBaseY = gCurrentActor->y;
        gCurrentActor->y = mathSinF(gActivePlayerState->bobPhase) * 10.0 + gActivePlayerState->floatBaseY;
        gActivePlayerState->bobPhase += 0x64;
        if (gCurrentActor->yawSpeed < gCurrentActor->y) {
            dist = gCurrentActor->y - gCurrentActor->yawSpeed;
        } else {
            dist = -(gCurrentActor->y - gCurrentActor->yawSpeed);
        }
        if (dist < 150.0) {
            gCurrentActor->accelY = 2.0 * ((gCurrentActor->yawSpeed - gCurrentActor->y) / 150.0);
        }
        if (gCurrentActor->yawSpeed <= gCurrentActor->y) {
            gCurrentActor->speedY = 0.0f;
            gCurrentActor->accelY = -0.01f;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStatePonytailTwirl(void) {
    switch (gCurrentActor->subState) {
    case 0:
        gCurrentActor->speedY = 0.0f;
        gCurrentActor->speedXZ = 0.0f;
        gActivePlayerState->decelRate = 2.0f;
        gActivePlayerState->airAccel = 5.0f;
        break;
    case 1:
        mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x32);
        playerInputUpdate(0x43);
        gCurrentActor->accelY -= 0.036;
        playerApplyFullPhysics();
        sfxSetChannelTempo(0x6B, 0.995f);
        if (gCurrentActor->speedY <= 0.0f && gCurrentActor->accelY < 0.0f) {
            gCurrentActor->speedY = 0.0f;
            gCurrentActor->accelY = -0.01f;
            gCurrentActor->yawSpeed = 0;
            gCurrentActor->subState++;
        }
        if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000) {
            gCurrentActor->subState = 3;
            gCurrentActor->accelY = -1.0f;
        }
        break;
    case 2:
        mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x32);
        playerInputUpdate(0x43);
        mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x32);
        gCurrentActor->yawSpeed++;
        gCurrentActor->y += mathSinF(gCurrentActor->yawSpeed << 5) * 0.25;
        playerApplyMotionWithHorizontalVelocity();
        sfxSetChannelTempo(0x6B, 0.995f);
        gActivePlayerState->twirlTimer--;
        if (gActivePlayerState->twirlTimer < 0 || (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000)) {
            gCurrentActor->subState++;
        }
        break;
    case 3:
        actorScriptStart(gCurrentActor, 0x16A);
        playerInputUpdate(0x43);
        playerApplyFullPhysics();
        gCurrentActor->subState++;
        break;
    case 4:
        gCurrentActor->accelY -= 1.0f;
        playerInputUpdate(0x43);
        playerApplyFullPhysics();
        break;
    case 5:
        sfxStopChannel(0x6B, 0);
        playerInputUpdate(0x43);
        playerApplyFullPhysics();
        break;
    case 6:
        sfxStopChannel(0x6B, 0);
        playerInputUpdate(0x43);
        playerApplyFullPhysics();
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateHoldMoveRamp(void) {
    f32 speed;
    if (gActorGlobalState.forcedContactSpeed != 0.0) {
        speed = gActorGlobalState.forcedContactSpeed;
    } else {
        speed = gCurrentActor->speedXZ;
    }
    scriptSetActorRampTarget(gCurrentActor, speed / 25.0f + 0.25, 2.0f);
    playerInputUpdate(0x49);
    if (!(gCurrentActor->contactFlags & 0x10)) {
        playerResumeLocomotion(gCurrentActor);
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateThrowCarried(void) {
    playerClearCarriedItemState();
    playerInputUpdate(5);
    gCurrentActor->speedXZ = 0.0f;
    gCurrentActor->x = (gActivePlayerState->savedX - gCurrentActor->x) * 0.2 + gCurrentActor->x;
    gCurrentActor->z = (gActivePlayerState->savedZ - gCurrentActor->z) * 0.2 + gCurrentActor->z;
    mathAngleStepToward(&gCurrentActor->yaw, mathAngleBetweenPoints2D(gActivePlayerState->targetPos[0], gActivePlayerState->targetPos[2], gCurrentActor->x, gCurrentActor->z), 0x32);
    playerApplyMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateHoldPickup(void) {
    if (actorTableContains(gActivePlayerState->queuedHeldActor) == 0 || gActivePlayerState->queuedHeldActor->instanceId != gActivePlayerState->queuedHeldActorId) {
        gActivePlayerState->heldActor = NULL;
        gActivePlayerState->queuedHeldActor = NULL;
        playerResumeLocomotion(gCurrentActor);
        playerApplyFullPhysics();
        actorUpdateModelMatrix(gCurrentActor, 0);
        return;
    }
    switch (gCurrentActor->subState) {
    case 0:
        gCurrentActor->speedXZ = 0.0f;
        gActivePlayerState->maxSpeed = 0.0f;
        playerStartPickupApproach(gActivePlayerState->queuedHeldActor);
        gCurrentActor->x += gActivePlayerState->unk78;
        gCurrentActor->z += gActivePlayerState->unk7C;
        gCurrentActor->yaw = gActivePlayerState->unk80;
        gCurrentActor->subState++;
        break;
    case 1:
        gCurrentActor->x += gActivePlayerState->unk78;
        gCurrentActor->z += gActivePlayerState->unk7C;
        gCurrentActor->yaw = gActivePlayerState->unk80;
        break;
    case 2:
        gActivePlayerState->heldActor = gActivePlayerState->queuedHeldActor;
        gActivePlayerState->heldActorType = gActivePlayerState->heldActor->actorType;
        actorAppendCallback(gActivePlayerState->heldActor, gCurrentActor, 0x2000, 1, 0, 0);
        playerRegisterHeldActorFollow(0.4f);
        playerComputePickupHoldPitch();
        gCurrentActor->subState++;
        break;
    case 3:
        playerInputUpdate(5);
        playerRegisterHeldActorFollow(0.4f);
        playerComputePickupHoldPitch();
        break;
    case 4:
        playerInputUpdate(5);
        actorAppendLaunch(gCurrentActor, gActivePlayerState->heldActor, gActivePlayerActor->yaw, gKongHoldPutDownAngles[gCurrentCharacterIndex] * 3.0 * gCurrentActor->sub4->scale[0] / 0.15, 0); // FAKE: scale[0] union-array spelling of scaleX orders the mul.d operands (scaleX gives full=1)
        gCurrentActor->subState++;
        break;
    case 5:
        playerInputUpdate(5);
        break;
    case 6:
        gActivePlayerState->heldActor = gActivePlayerState->queuedHeldActor;
        gActivePlayerState->heldActorType = gActivePlayerState->heldActor->actorType;
        actorAppendCallback(gActivePlayerState->heldActor, gCurrentActor, 0x2000, 1, 0, 0);
        playerRegisterHeldActorFollow(0.4f);
        playerComputePickupHoldPitch();
        gCurrentActor->subState = 3;
        break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateCrouch(void) {
    playerInputUpdate(6);
    if (gPlayerPadState[gCurrentPlayerIndex].stickMagNorm != 0.0f) {
        scriptSetActorRampTarget(gCurrentActor, 3.0f, 0.0f);
    }
    mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, gActivePlayerState->turnRate);
    gActivePlayerState->maxSpeed = 0.0f;
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateCrawl(void) {
    playerInputUpdate(7);
    if (gPlayerPadState[gCurrentPlayerIndex].stickMagNorm != 0.0f) {
        scriptSetActorRampTarget(gCurrentActor, 2.0f, 0.0f);
    }
    mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, gActivePlayerState->turnRate);
    gActivePlayerState->maxSpeed = 0.0f;
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateHoldWalk(void) {
    gActivePlayerState->stateFlags &= 0xFEFFFFFF;
    playerRegisterHeldActorFollow(1.0f);
    playerRegisterHeldActorAlign();
    playerComputePickupHoldPitch();
    gCurrentActor->state = playerSelectCarryMoveState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);
    gCurrentActor->subState = 0;
    playerInputUpdate(0x37);
    if (!(gCurrentActor->contactFlags & 1)) {
        playerUpdateFallAndStepSounds();
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateHoldRun(void) {
    gActivePlayerState->stateFlags &= 0xFEFFFFFF;
    playerRegisterHeldActorFollow(1.0f);
    playerRegisterHeldActorAlign();
    playerComputePickupHoldPitch();
    gCurrentActor->state = playerSelectCarryMoveState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);
    gCurrentActor->subState = 0;
    playerInputUpdate(0x37);
    if (!(gCurrentActor->contactFlags & 1)) {
        playerUpdateFallAndStepSounds();
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateHoldIdle(void) {
    gActivePlayerState->stateFlags &= 0xFEFFFFFF;
    playerInputUpdate(0x3A);
    playerComputePickupHoldPitch();
    switch (gCurrentActor->subState) {
        case 0:
            playerRegisterHeldActorFollow(0.5f);
            break;
        case 1:
            playerRegisterHeldActorFollow(0.5f);
            if (gActivePlayerState->heldActor != NULL) {
                actorAppendCallback(gActivePlayerState->heldActor, gCurrentActor, 0x2000, 0, 0, 0);
            }
            gActivePlayerState->heldActor = NULL;
            gActivePlayerState->queuedHeldActor = NULL;
            gCurrentActor->subState++;
            break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongHoldReleaseSpeeds[];
extern f32 gKongHoldReleaseDecels[];
extern f32 gKongHoldPutDownOffsets[];

void playerStateHoldPutDown(void) {
    gActivePlayerState->stateFlags &= 0xFEFFFFFF;
    playerInputUpdate(1);
    switch (gCurrentActor->subState) {
        case 0:
            playerRegisterHeldActorFollow(1.0f);
            gCurrentActor->speedXZ = 0.0f;
            break;
        case 1:
            actorAppendLaunch(gCurrentActor, gActivePlayerState->heldActor, gActivePlayerActor->yaw, gKongHoldPutDownAngles[gCurrentCharacterIndex], gKongHoldPutDownOffsets[gCurrentCharacterIndex]);
            gActivePlayerState->heldActor = NULL;
            gActivePlayerState->queuedHeldActor = NULL;
            gCurrentActor->subState++;
            gCurrentActor->speedXZ = gKongHoldReleaseSpeeds[gCurrentCharacterIndex];
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            break;
        default:
            if (gCurrentActor->speedXZ != 0.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ -= gKongHoldReleaseDecels[gCurrentCharacterIndex];
                if (gCurrentActor->speedXZ < 0.0f) {
                    gCurrentActor->speedXZ = 0.0f;
                }
            }
            break;
    }
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongHoldThrowOffsets[];
extern f32 gKongHoldThrowAngles[];

void playerStateHoldThrow(void) {
    gActivePlayerState->stateFlags &= 0xFEFFFFFF;
    playerInputUpdate(1);
    switch (gCurrentActor->subState) {
        case 0:
            playerRegisterHeldActorFollow(1.0f);
            gCurrentActor->speedXZ = 0.0f;
            break;
        case 1:
            actorAppendLaunch(gCurrentActor, gActivePlayerState->heldActor, gActivePlayerActor->yaw, gKongHoldThrowAngles[gCurrentCharacterIndex], gKongHoldThrowOffsets[gCurrentCharacterIndex]);
            gActivePlayerState->heldActor = NULL;
            gActivePlayerState->queuedHeldActor = NULL;
            gCurrentActor->subState++;
            gCurrentActor->speedXZ = gKongHoldReleaseSpeeds[gCurrentCharacterIndex];
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            break;
        default:
            if (gCurrentActor->speedXZ != 0.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ -= gKongHoldReleaseDecels[gCurrentCharacterIndex];
                if (gCurrentActor->speedXZ < 0.0f) {
                    gCurrentActor->speedXZ = 0.0f;
                }
            }
            break;
    }
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateHoldJump(void) {
    gActivePlayerState->stateFlags &= 0xFEFFFFFF;
    playerRegisterHeldActorFollow(1.0f);
    playerComputePickupHoldPitch();
    switch (gCurrentActor->subState) {
        case 0:
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0);
            playerInputUpdate(0x21);
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            playerUpdateTargetYawFromStick();
            gCurrentActor->subState++;
            playerInputUpdate(0x21);
            playerSetBaseGravityIfFalling();
            break;
        case 2:
            playerUpdateFallAndStepSounds();
            playerInputUpdate(0x39);
            playerSetBaseGravityIfFalling();
            break;
        case 3:
            playerInputUpdate(0x38);
            playerSetBaseGravity();
            break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdate12(void) {
    playerInputUpdate(0x12);
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 gKongTurnRate[];

void playerStateTransformHold(void) {
    f32 dx;
    f32 dz;

    if (gActorGlobalState.destPointReceived != 0) {
        gActivePlayerState->damageSource = gActorGlobalState.destPointSource;
        gActivePlayerState->walkStartX = gCurrentActor->x;
        gActivePlayerState->walkStartZ = gCurrentActor->z;
        gActivePlayerState->walkEndX = gActorGlobalState.destPointX;
        gActivePlayerState->walkEndZ = gActorGlobalState.destPointZ;
        gActivePlayerState->walkProgress = 0.0f;
        dx = gActivePlayerState->walkEndX - gActivePlayerState->walkStartX;
        dz = gActivePlayerState->walkEndZ - gActivePlayerState->walkStartZ;
        gActivePlayerState->forwardSpeed = sqrtf(dx * dx + dz * dz) * 0.8;
        gActivePlayerState->walkFacingYaw = mathAtan2(dx, dz) * 4096.0f / 6.2831855f;
        gActivePlayerState->moveTier = -1;
    }
    gActivePlayerState->walkProgress += 0.02;
    if (gActivePlayerState->walkProgress > 1.0) {
        if (gActivePlayerState->damageSource != NULL) {
            dx = gActivePlayerState->damageSource->x - gActivePlayerState->walkStartX;
            dz = gActivePlayerState->damageSource->z - gActivePlayerState->walkStartZ;
            gActivePlayerState->walkFacingYaw = mathAtan2(dx, dz) * 4096.0f / 6.2831855f;
            if ((s16)gActivePlayerState->walkFacingYaw == gCurrentActor->yaw) {
                playerResumeLocomotion(gCurrentActor);
            }
        }
        gActivePlayerState->walkProgress = 1.0f;
    }
    gCurrentActor->x = gActivePlayerState->walkStartX + (gActivePlayerState->walkEndX - gActivePlayerState->walkStartX) * gActivePlayerState->walkProgress;
    gCurrentActor->z = gActivePlayerState->walkStartZ + (gActivePlayerState->walkEndZ - gActivePlayerState->walkStartZ) * gActivePlayerState->walkProgress;
    playerApplyMotion();
    playerSelectWalkRunState(gCurrentActor, gActivePlayerState->forwardSpeed, gActivePlayerState->forwardSpeed, 0);
    mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->walkFacingYaw, gKongTurnRate[gCurrentCharacterIndex] / 2);
    gCurrentActor->moveYaw = gCurrentActor->yaw;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateTagBarrelFade(void) {
    gCurrentActor->speedXZ = 0.0f;
    switch (gCurrentActor->subState) {
        case 0:
            gCurrentActor->collisionMode = 1;
            gCurrentActor->flags &= 0xFFFF7FFF;
            gCurrentActor->alpha = 0xFF;
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xE6, 0xFF, 0x7F, 0, 0, 0.3f, 0);
            gCurrentActor->subState++;
            break;
        case 1:
            gCurrentActor->alpha -= 0xF;
            if (gCurrentActor->alpha < 0x10) {
                matrixCacheSetDefaultLimit();
                gCurrentActor->subState++;
            }
            break;
        case 2:
            actorClearMovementFlags(gCurrentActor);
            gCurrentActor->x = gActivePlayerState->warpX;
            gCurrentActor->y = gActivePlayerState->warpY + 10.0;
            gCurrentActor->prevY = gCurrentActor->y;
            gCurrentActor->z = gActivePlayerState->warpZ;
            kongChainInit(0, KONG_ACTOR->chains, gCurrentActor->actorType);
            camResetPlayer(gCurrentActor, gActivePlayerState->playerIndex);
            screenWipeStart(6);
            gActivePlayerState->stateCountdown = 0x14;
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xE6, 0xFF, 0x7F, 0, 0, 0.3f, 0);
            gCurrentActor->subState++;
            break;
        case 3:
            gActivePlayerState->stateCountdown--;
            if (gActivePlayerState->stateCountdown == 0) {
                gCurrentActor->subState++;
            }
            break;
        case 4:
            gCurrentActor->alpha += 0xF;
            if (gCurrentActor->alpha >= 0xF1) {
                gCurrentActor->flags |= 0x8000;
                gCurrentActor->subState++;
            }
            break;
        case 5:
            actorSetInteractionTimer(gCurrentActor);
            matrixCacheRestoreLimit();
            playerResumeLocomotion(gCurrentActor);
            playerInputUpdate(0x30);
            break;
    }
    playerApplyMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateTagBarrelPadEnter(void) {
    gCurrentActor->speedXZ = 0.0f;
    switch (gCurrentActor->subState) {
        case 0:
            gCurrentActor->collisionMode = 1;
            if (actorSpawn(0x3C, 0x98)) {
                actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.15f);
            }
            gCurrentActor->subState++;
            break;
        case 1:
            gCurrentActor->subState++;
            gActivePlayerState->stateCountdown = 4;
            break;
        case 2:
            gCurrentActor->x = (gActivePlayerState->warpEffectX - gCurrentActor->x) * 0.5 + gCurrentActor->x;
            gCurrentActor->y = (gActivePlayerState->warpEffectY - gCurrentActor->y) * 0.5 + gCurrentActor->y;
            gCurrentActor->z = (gActivePlayerState->warpEffectZ - gCurrentActor->z) * 0.5 + gCurrentActor->z;
            if (gActivePlayerState->stateCountdown != 0) {
                gActivePlayerState->stateCountdown--;
                if (gActivePlayerState->stateCountdown == 0) {
                    gCurrentActor->flags &= 0xFFFF7FFF;
                    gCurrentActor->alpha = 0;
                }
            }
            break;
        case 3:
            gCurrentActor->flags &= 0xFFFF7FFF;
            gCurrentActor->alpha = 0;
            gCurrentActor->subState++;
            break;
        case 5:
            gActivePlayerState->stateCountdown = 0x14;
            break;
        case 6:
            gActivePlayerState->stateCountdown--;
            if (gActivePlayerState->stateCountdown == 0) {
                matrixCacheSetDefaultLimit();
                gCurrentActor->subState++;
            }
            break;
        case 7:
            gGlobalPauseFlags &= 0xFFFCFFDF;
            actorClearMovementFlags(gCurrentActor);
            gCurrentActor->x = gActivePlayerState->warpX;
            gCurrentActor->y = gActivePlayerState->warpY;
            gCurrentActor->prevY = gCurrentActor->y;
            gCurrentActor->z = gActivePlayerState->warpZ;
            kongChainInit(0, KONG_ACTOR->chains, gCurrentActor->actorType);
            camResetPlayer(gCurrentActor, gActivePlayerState->playerIndex);
            gActivePlayerState->stateCountdown = 0x14;
            screenWipeStart(2);
            gCurrentActor->subState++;
            break;
        case 8:
            gGlobalPauseFlags |= 0x30020;
            gActivePlayerState->stateCountdown--;
            if (gActivePlayerState->stateCountdown == 0) {
                sfxStartAreaAmbient();
                if (actorSpawn(0x3C, 0x98)) {
                    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.15f);
                }
                gCurrentActor->subState++;
                gActivePlayerState->stateCountdown = 0xC;
            }
            break;
        case 10:
            if (gActivePlayerState->stateCountdown != 0) {
                gActivePlayerState->stateCountdown--;
                if (gActivePlayerState->stateCountdown == 0) {
                    gCurrentActor->x = gActivePlayerState->warpEffectX;
                    gCurrentActor->y = gActivePlayerState->warpEffectY;
                    gCurrentActor->z = gActivePlayerState->warpEffectZ;
                    gCurrentActor->flags |= 0x8000;
                }
            }
            break;
        case 11:
            playerInputUpdate(0x20);
            actorScriptStartByIndex(gCurrentActor, 0x1B);
            playerSetBaseGravity();
            gCurrentActor->subState++;
            break;
        case 12:
        case 13:
            playerInputUpdate(0x20);
            playerApplyGravity();
            break;
        case 14:
            sfxPlayScriptActorSoundForPlayer(gCurrentActor, 0x2F, 0);
            gCurrentActor->subState++;
        case 15:
            actorSetInteractionTimer(gCurrentActor);
            matrixCacheRestoreLimit();
            playerInputUpdate(0x30);
            break;
    }
    playerApplyMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern EffectGridAsset gEffectSpriteSparklePurple;
extern EffectGridAsset gEffectSpriteSparkleGreen;

void playerStateKnockbackTumble(void) {
    f32 lightX;
    f32 lightY;
    f32 lightZ;
    u8 kind;
    f32 px;
    f32 py;
    f32 pz;
    f32 sine;

    playerInputUpdate(1);
    switch (gCurrentActor->subState) {
    case 0:
        gActivePlayerState->tumbleTimer = 50.0f;
        gCurrentActor->subState++;
        break;
    case 1:
        if (gActivePlayerState->tumbleTimer != 0.0f) {
            gActivePlayerState->tumbleTimer -= 1.0f;
        } else if (gCurrentActor->y - gCurrentActor->floorY < 60.0f) {
            gCurrentActor->y += 1.0f;
        } else {
            gActivePlayerState->tumbleTimer = 150.0f;
            gCurrentActor->subState++;
            camSetTargetScaled(gActivePlayerState->camActor, gCurrentActor, 6, 0, 0x1E, 0, 5, 0x2D, 0x14, 0xC8, 0.15f);
        }
        break;
    case 2:
        gActivePlayerState->tumbleTimer -= 1.0f;
        if (gActivePlayerState->tumbleTimer == 0.0f) {
            gActivePlayerState->tumbleTimer = 150.0f;
            gCurrentActor->subState++;
        }
        sine = (mathSinF(gActivePlayerState->tumblePhase) > 0.0f) ? mathSinF(gActivePlayerState->tumblePhase) : -mathSinF(gActivePlayerState->tumblePhase);
        gCurrentActor->yaw += 120.0 * (0.5 + sine);
        break;
    case 3:
        gActivePlayerState->tumbleTimer -= 1.0f;
        if (gActivePlayerState->tumbleTimer == 0.0f) {
            gActivePlayerState->tumbleTimer = 500.0f;
            gCurrentActor->subState++;
        }
        sine = (mathSinF(gActivePlayerState->tumblePhase) > 0.0f) ? mathSinF(gActivePlayerState->tumblePhase) : -mathSinF(gActivePlayerState->tumblePhase);
        gCurrentActor->yaw += 120.0 * (0.5 + sine);
        sine = mathSinF(gActivePlayerState->tumblePhase + 0x400);
        gCurrentActor->pitch += 60.0f * sine;
        break;
    case 4:
        playerStateQueueCallback(0x1B, 0, 0);
        gActivePlayerState->stateFlags |= 4;
        gCurrentActor->pitch = 0;
        gCurrentActor->yaw = 0;
        break;
    }
    gActivePlayerState->tumblePhase += 6;
    gActivePlayerState->tumblePhase &= 0xFFF;
    if (!(gFrameCounter & 1)) {
        kind = (randomNonNegative() >> 15) % 65535 % 3;
        actorGetNodePos(gCurrentActor, 5, &px, &py, &pz);
        px += (randomNonNegative() >> 15) % 65535 % 16 - 8;
        py += (randomNonNegative() >> 15) % 65535 % 16 - 8;
        pz += (randomNonNegative() >> 15) % 65535 % 16 - 8;
        effectSetFrameDelay(2);
        effectSetDepth(1);
        effectSetCallback(effectPuffRiseUpdate);
        effectSetSpeed((randomNonNegative() >> 15) % 100 + 0x64);
        if (kind == 2) {
            effectCreateAtPosition(&gEffectSpriteSparkleGreen, 0.5f, px, py, pz);
        } else if (kind == 1) {
            effectCreateAtPosition(&gEffectSpriteSparkleYellow, 0.5f, px, py, pz);
        } else {
            effectCreateAtPosition(&gEffectSpriteSparklePurple, 0.5f, px, py, pz);
        }
    }
    gCurrentActor->speedY = 0.0f;
    gCurrentActor->speedXZ = 0.0f;
    playerApplyMotion();
    actorGetNodePos(gCurrentActor, 0xC, &lightX, &lightY, &lightZ);
    lightAdd(lightX, lightY, lightZ, 0.0f, 0.0f, 0.0f, 80.0f, 0, 0xFF, 0xFF, 0);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateStationaryInteraction(void) {
    s16 yaw;
    f32 scale;
    s32 i;

    playerInputUpdate(1);
    gCurrentActor->speedXZ = 0.0f;
    switch (gCurrentActor->subState) {
    case 0:
        gCurrentActor->collisionMode = 1;
        gActivePlayerState->rampLevel = 0xA;
        gCurrentActor->subState++;
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x2EB, 0xFF, 0x7F, 2);
        break;
    case 1:
        if (gActivePlayerState->rampLevel >= 2) {
            gActivePlayerState->rampLevel--;
        } else {
            gCurrentActor->subState++;
        }
        break;
    case 2:
        actorClearMovementFlags(gCurrentActor);
        gCurrentActor->x = gActivePlayerState->warpX;
        gCurrentActor->y = gActivePlayerState->warpY;
        gCurrentActor->prevY = gCurrentActor->y;
        gCurrentActor->z = gActivePlayerState->warpZ;
        yaw = gActivePlayerState->warpYaw;
        gCurrentActor->moveYaw = yaw;
        gCurrentActor->yaw = yaw;
        camResetPlayer(gCurrentActor, gActivePlayerState->playerIndex);
        kongChainInit(0, KONG_ACTOR->chains, gCurrentActor->actorType);
        gCurrentActor->subState++;
        break;
    case 3:
        if (gActivePlayerState->rampLevel < 0xA) {
            gActivePlayerState->rampLevel++;
        } else {
            gCurrentActor->subState++;
        }
        break;
    case 4:
        gActivePlayerState->transitionTimer = 0x3C;
        playerResumeLocomotion(gCurrentActor);
        break;
    }
    scale = (f32)gActivePlayerState->rampLevel * 0.015;
    for (i = 0; i < 3; i++) {
        gCurrentActor->sub4->scale[i] = scale;
    }
    playerApplyMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStepForwardSpeedTowardTarget(f32 step) {
    f32 speed = gActivePlayerState->forwardSpeed;
    f32 target = gActivePlayerState->maxSpeed;

    if (speed < target) {
        speed += step;
        if (target < speed) {
            speed = target;
        }
    } else if (target < speed) {
        speed -= step;
        if (speed < target) {
            speed = target;
        }
    }
    gActivePlayerState->forwardSpeed = speed;
}

extern s16 D_80753C84[];
extern f32 gKongPathAccelUp[];
extern f32 gKongPathAccelDown[];
extern f32 gKongPathAccelNeutral[];

void playerStateAttachedCallbackFall(void) {
    ActorCallbackNode *node;
    s32 pad[1];
    f32 targetSpeed;
    f32 animSpeed;
    f64 rate;

    if (gCurrentActor->subState != 0 && !(gCurrentActor->contactFlags & 0x40)) {
        playerEnterFall(gCurrentActor);
        if (gActivePlayerState->gunDrawn != 0) {
            playerStateFallDamageHard();
            return;
        }
        playerStateFallDamageLand();
        return;
    }
    gActivePlayerState->respawnTimer = D_80753C84[gCurrentCharacterIndex];
    node = heapAlloc(0x14);
    node->callback = proxPathFollowerStep;
    node->source = gActivePlayerActor;
    node->dispatchPass = 1;
    actorRegisterGlobalCallback(node);
    mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0xC8);
    switch (gCurrentActor->subState) {
    case 0:
        playerInputUpdate(5);
        gActivePlayerState->forwardSpeed = 0.0f;
        gActivePlayerState->leapTarget = 0;
        gCurrentActor->moveYaw = gActivePlayerState->pathOwner->yaw;
        if (mathAngleDistance(gCurrentActor->yaw, gActivePlayerState->pathOwner->yaw) >= 0x400) {
            gCurrentActor->moveYaw = (gCurrentActor->moveYaw + 0x800) & 0xFFF;
        }
        break;
    case 1:
        if (playerInputUpdate(0x58) == 0) {
            switch (gActivePlayerState->moveDir) {
            case 1:
                targetSpeed = gKongPathAccelUp[gCurrentCharacterIndex];
                gCurrentActor->subState = 3;
                actorScriptStartByIndex(gActivePlayerActor, 0x6A);
                break;
            case 0:
                targetSpeed = gKongPathAccelNeutral[gCurrentCharacterIndex];
                break;
            case -1:
                targetSpeed = gKongPathAccelDown[gCurrentCharacterIndex];
                gCurrentActor->subState = 4;
                actorScriptStartByIndex(gActivePlayerActor, 0x6B);
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
        }
        break;
    case 2:
        if (playerInputUpdate(0x58) == 0) {
            if (gActivePlayerState->forwardSpeed == 0.0f && gActivePlayerState->maxSpeed == 0.0f) {
                gCurrentActor->subState = 1;
                actorScriptStartByIndex(gActivePlayerActor, 0x6C);
            } else if (gActivePlayerState->forwardSpeed > 0.0f && gActivePlayerState->maxSpeed > 0.0f) {
                gCurrentActor->subState = 3;
                actorScriptStartByIndex(gActivePlayerActor, 0x6A);
            } else if (gActivePlayerState->forwardSpeed < 0.0f && gActivePlayerState->maxSpeed < 0.0f) {
                gCurrentActor->subState = 4;
                actorScriptStartByIndex(gActivePlayerActor, 0x6B);
            }
            playerStepForwardSpeedTowardTarget(gKongPathAccelNeutral[gCurrentCharacterIndex]);
            rate = gActivePlayerState->forwardSpeed * 0.025;
            if (rate > 0.0) {
                animSpeed = rate;
            } else {
                animSpeed = -rate;
            }
            scriptSetActorRampTarget(gCurrentActor, animSpeed, 0.0f);
        }
        break;
    case 3:
        if (playerInputUpdate(0x58) == 0) {
            if (gActivePlayerState->forwardSpeed <= 0.0f) {
                gCurrentActor->subState = 2;
            }
            switch (gActivePlayerState->moveDir) {
            case -1:
                targetSpeed = gKongPathAccelDown[gCurrentCharacterIndex] * 2;
                break;
            case 0:
                targetSpeed = gKongPathAccelNeutral[gCurrentCharacterIndex];
                break;
            case 1:
                targetSpeed = gKongPathAccelUp[gCurrentCharacterIndex];
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            rate = gActivePlayerState->forwardSpeed * 0.025;
            if (rate > 0.0) {
                animSpeed = rate;
            } else {
                animSpeed = -rate;
            }
            scriptSetActorRampTarget(gCurrentActor, animSpeed, 0.0f);
        }
        break;
    case 4:
        if (playerInputUpdate(0x58) == 0) {
            if (gActivePlayerState->forwardSpeed >= 0.0f) {
                gCurrentActor->subState = 2;
            }
            switch (gActivePlayerState->moveDir) {
            case -1:
                targetSpeed = gKongPathAccelDown[gCurrentCharacterIndex];
                break;
            case 0:
                targetSpeed = gKongPathAccelNeutral[gCurrentCharacterIndex];
                break;
            case 1:
                targetSpeed = gKongPathAccelUp[gCurrentCharacterIndex];
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            rate = gActivePlayerState->forwardSpeed * 0.025;
            if (rate > 0.0) {
                animSpeed = rate;
            } else {
                animSpeed = -rate;
            }
            scriptSetActorRampTarget(gCurrentActor, animSpeed, 0.0f);
        }
        break;
    }
    playerApplyMotion();
}

void playerStateSwingLeap(void) {
    f32 dist;
    f32 time;
    f32 dy;
    f32 speed;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    s32 diff;
    s32 absDiff;
    s16 roll;

    gCurrentActor->flags &= 0xFFBFFFFF;
    gCurrentActor->contactFlags &= 0xFFBF;
    roll = gCurrentActor->roll;
    gCurrentActor->roll = roll + -roll * 0.1;
    switch (gCurrentActor->subState) {
    case 0:
        playerFindClosestTargetActor();
        gCurrentActor->speedXZ = gActivePlayerState->leapSpeedXZ / 2;
        gCurrentActor->moveYaw = gActivePlayerState->leapYaw;
        diff = gCurrentActor->moveYaw - gCurrentActor->yaw;
        if (diff < -0x800) {
            diff += 0x1000;
        }
        if (diff >= 0x801) {
            diff -= 0x1000;
        }
        if (diff > 0) {
            absDiff = diff;
        } else {
            absDiff = -diff;
        }
        if (absDiff < 0x400) {
            actorScriptStartByIndex(gCurrentActor, 0x6D);
        } else {
            actorScriptStartByIndex(gCurrentActor, 0x6E);
        }
        mathAngleStepTowardThreshold(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x78, 0x600);
        gCurrentActor->speedY = gActivePlayerState->leapSpeedY;
        gCurrentActor->subState++;
        playerInputUpdate(0x27);
        gActivePlayerState->decelRate = gActivePlayerState->decelRate / 2;
        playerApplyGravityAndMotion();
        break;
    case 2:
        if (gActivePlayerState->leapTarget == 0) {
            actorScriptStartByIndex(gActivePlayerActor, 0x6F);
            gCurrentActor->subState = 3;
            break;
        }
    case 1:
        playerFindClosestTargetActor();
        if (gCurrentActor->actorType == 5) {
            playerInputUpdate(0x28);
        } else {
            playerInputUpdate(0x27);
        }
        gCurrentActor->speedXZ = gActivePlayerState->leapSpeedXZ;
        gCurrentActor->moveYaw = gActivePlayerState->leapYaw;
        mathAngleStepTowardThreshold(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x78, 0x600);
        gActivePlayerState->targetYaw = gCurrentActor->moveYaw;
        gActivePlayerState->maxSpeed = 150.0f;
        gActivePlayerState->targetSpeed = 150.0f;
        if (gActivePlayerState->leapTarget != 0) {
            actorGetNodePos(gActivePlayerState->leapTarget, 1, &nodeX, &nodeY, &nodeZ);
            dy = nodeY - gActivePlayerActor->y;
            dy = dy / (gActivePlayerActor->sub4->scaleY * 0.16666666675);
            dist = sqrtf((nodeX - gActivePlayerActor->x) * (nodeX - gActivePlayerActor->x) + (nodeZ - gActivePlayerActor->z) * (nodeZ - gActivePlayerActor->z)) / (gActivePlayerActor->sub4->scaleY * 0.16666666675);
            speed = gActivePlayerActor->speedXZ;
            time = dist / speed - 1.0f;
            if (time < 1.0f) {
                time = 1.0f;
            }
        }
        if ((gActivePlayerState->leapTarget != 0) && (time < 30.0f)) {
            gActivePlayerActor->speedY = (0.0 - (gKongTargetLaunchGravity[gCurrentCharacterIndex] * 0.5 * (time * time) - dy)) / time;
            gActivePlayerActor->accelY = -0.001f;
        } else {
            gActivePlayerState->leapTarget = 0;
            playerSetBaseGravity();
        }
        playerApplyGravityAndMotion();
        break;
    case 3:
        playerInputUpdate(0x30);
        playerSetBaseGravity();
        playerApplyFullPhysics();
        gActivePlayerState->decelRate = 10.0f;
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerFindClosestTargetActor(void) {
    f32 best = 100.0f;
    Actor *target = gActivePlayerState->leapTarget;
    Actor *actor;
    s16 angle;
    s16 angleDiff;
    s32 i;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 absDy;

    if ((target != NULL) || (gCurrentActor->subState == 1)) {
        if (target == NULL) {
            for (i = 0; i < gActiveActorCount; i++) {
                actor = gActiveActors[i].actor;
                if (!(actor->flags & 0x2000) && (actor->flags & 0x04000000) && (actor != gActivePlayerState->pathOwner) && (actor != gActivePlayerActor)) {
                    angle = mathAngleBetweenPointsRad(actor->x, actor->z, gActivePlayerActor->x, gActivePlayerActor->z) * 57.295776f / 360.0 * 4095.0;
                    angleDiff = mathAngleDistance(angle, gActivePlayerState->leapYaw);
                    dx = actor->x - gActivePlayerActor->x;
                    dz = actor->z - gActivePlayerActor->z;
                    dist = sqrtf(dx * dx + dz * dz);
                    if ((angleDiff < 0x258) && (dist < best)) {
                        if (gActivePlayerActor->y < actor->y) {
                            absDy = actor->y - gActivePlayerActor->y;
                        } else {
                            absDy = -(actor->y - gActivePlayerActor->y);
                        }
                        if (absDy < 100.0) {
                            best = dist;
                            gActivePlayerState->leapYaw = angle;
                            gActivePlayerState->leapTarget = actor;
                        }
                    }
                }
            }
        } else {
            angle = mathAngleBetweenPointsRad(target->x, target->z, gActivePlayerActor->x, gActivePlayerActor->z) * 57.295776f / 360.0 * 4095.0;
            if (mathAngleDistance(angle, gActivePlayerState->leapYaw) < 0x258) {
                gActivePlayerState->leapYaw = angle;
            }
        }
    }
}

extern s16 D_80753CA4[];

void playerStateAttachedCallbackFallCheck(void) {
    ActorCallbackNode *node;
    s32 pad[1];
    f32 targetSpeed;
    f32 animSpeed;
    f64 rate;

    if (gCurrentActor->subState != 0 && (!(gCurrentActor->contactFlags & 0x40) || ((gCurrentActor->contactFlags & 4) && gCurrentActor->waterY - gCurrentActor->y > 3.0))) {
        playerEnterFall(gCurrentActor);
        if (gActivePlayerState->gunDrawn != 0) {
            playerStateFallDamageHard();
            return;
        }
        playerStateFallDamageLand();
        return;
    }
    gActivePlayerState->respawnTimer = D_80753CA4[gCurrentCharacterIndex];
    node = heapAlloc(0x14);
    node->callback = proxPathFollowerStep;
    node->source = gActivePlayerActor;
    node->dispatchPass = 1;
    actorRegisterGlobalCallback(node);
    switch (gCurrentActor->subState) {
    case 0:
        playerInputUpdate(5);
        gActivePlayerState->forwardSpeed = 0.0f;
        break;
    case 1:
        if (playerInputUpdate(0x59) == 0) {
            switch (gActivePlayerState->moveDir) {
            case 1:
                targetSpeed = gKongPathAccelUp[gCurrentCharacterIndex];
                gCurrentActor->subState = 3;
                actorScriptStartByIndex(gActivePlayerActor, 0x71);
                break;
            case 0:
                targetSpeed = gKongPathAccelNeutral[gCurrentCharacterIndex];
                break;
            case -1:
                targetSpeed = gKongPathAccelDown[gCurrentCharacterIndex];
                gCurrentActor->subState = 4;
                actorScriptStartByIndex(gActivePlayerActor, 0x72);
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
        }
        break;
    case 2:
        if (playerInputUpdate(0x59) == 0) {
            if (gActivePlayerState->forwardSpeed == 0.0f && gActivePlayerState->maxSpeed == 0.0f) {
                gCurrentActor->subState = 1;
                actorScriptStartByIndex(gActivePlayerActor, 0x73);
            } else if (gActivePlayerState->forwardSpeed > 0.0f && gActivePlayerState->maxSpeed > 0.0f) {
                gCurrentActor->subState = 3;
                actorScriptStartByIndex(gActivePlayerActor, 0x71);
            } else if (gActivePlayerState->forwardSpeed < 0.0f && gActivePlayerState->maxSpeed < 0.0f) {
                gCurrentActor->subState = 4;
                actorScriptStartByIndex(gActivePlayerActor, 0x72);
            }
            playerStepForwardSpeedTowardTarget(gKongPathAccelNeutral[gCurrentCharacterIndex]);
            rate = gActivePlayerState->forwardSpeed * 0.025;
            if (rate > 0.0) {
                animSpeed = rate;
            } else {
                animSpeed = -rate;
            }
            scriptSetActorRampTarget(gCurrentActor, animSpeed, 0.0f);
        }
        break;
    case 3:
        if (playerInputUpdate(0x59) == 0) {
            if (gActivePlayerState->forwardSpeed <= 0.0f) {
                gCurrentActor->subState = 2;
            }
            switch (gActivePlayerState->moveDir) {
            case -1:
                targetSpeed = gKongPathAccelDown[gCurrentCharacterIndex] * 2;
                break;
            case 0:
                targetSpeed = gKongPathAccelNeutral[gCurrentCharacterIndex];
                break;
            case 1:
                targetSpeed = gKongPathAccelUp[gCurrentCharacterIndex];
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            rate = gActivePlayerState->forwardSpeed * 0.025;
            if (rate > 0.0) {
                animSpeed = rate;
            } else {
                animSpeed = -rate;
            }
            scriptSetActorRampTarget(gCurrentActor, animSpeed, 0.0f);
        }
        break;
    case 4:
        if (playerInputUpdate(0x59) == 0) {
            if (gActivePlayerState->forwardSpeed >= 0.0f) {
                gCurrentActor->subState = 2;
            }
            switch (gActivePlayerState->moveDir) {
            case -1:
                targetSpeed = gKongPathAccelDown[gCurrentCharacterIndex];
                break;
            case 0:
                targetSpeed = gKongPathAccelNeutral[gCurrentCharacterIndex];
                break;
            case 1:
                targetSpeed = gKongPathAccelUp[gCurrentCharacterIndex];
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            rate = gActivePlayerState->forwardSpeed * 0.025;
            if (rate > 0.0) {
                animSpeed = rate;
            } else {
                animSpeed = -rate;
            }
            scriptSetActorRampTarget(gCurrentActor, animSpeed, 0.0f);
        }
        break;
    }
    playerApplyMotion();
}

extern f32 gKongKnockbackSpeeds[];

void playerStateKnockbackBounce(void) {
    gCurrentActor->arcSpeedCap = 0x12C;
    playerSetUnk586Flag();
    switch (gCurrentActor->subState) {
    case 1:
        gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) & 0xFFF;
        gCurrentActor->speedY = gKongKnockbackSpeeds[gCurrentCharacterIndex];
        gCurrentActor->speedXZ = 100.0f;
        playerSetTerminalVelocity5B0();
        gCurrentActor->subState++;
        gActivePlayerState->airTimer = 3;
        playerInputUpdate(0x29);
        gActivePlayerState->airAccel = 30.0f;
        gActivePlayerState->turnRate = 0x64;
        playerSetBaseGravityIfFalling();
        gActivePlayerState->decelRate /= 2;
        playerApplyGravityAndMotion();
        break;
    case 2:
        if (gCurrentActor->actorType == 5) {
            playerInputUpdate(0x2A);
        } else {
            playerInputUpdate(0x29);
        }
        gActivePlayerState->targetSpeed = 150.0f;
        playerUpdateFallAndStepSounds();
        playerSetBaseGravityIfFalling();
        if (gPlayerPadState[gCurrentPlayerIndex].stickMagNorm != 0.0f) {
            mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, gActivePlayerState->turnRate);
        }
        if (gActivePlayerState->airTimer != 0) {
            playerApplyGravityAndMotion();
            gActivePlayerState->airTimer--;
        } else {
            playerApplyFullPhysics();
        }
        break;
    case 3:
        playerInputUpdate(0x30);
        playerSetBaseGravity();
        playerApplyFullPhysics();
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongNormalLedgeHangOffsets[];
extern f32 gKongLedgeHangOffsets[];
extern s16 gKongNormalLedgeHangMinFloorHeights[];
extern s16 gKongLedgeHangMinFloorHeights[];

void playerStateBounceRecover(void) {
    f32 ledgeY;
    u8 pad1;
    u8 angleOk;
    s16 angle;
    f32 rate;
    s16 pad2;
    u8 letGo;
    f32 animSpeed;
    f32 ledgeOffset;
    u8 lostGrip;
    s16 hitA;
    s16 hitB;
    u8 onLedge;
    s32 pad3;

    onLedge = 0;
    if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
        ledgeOffset = gKongNormalLedgeHangOffsets[gCurrentCharacterIndex];
    } else {
        ledgeOffset = gKongLedgeHangOffsets[gCurrentCharacterIndex];
    }
    switch (gCurrentActor->subState) {
    case 0:
        playerInputUpdate(0x5A);
        gActivePlayerState->hangFacingYaw = gCurrentActor->yaw;
        gActivePlayerState->hangInputDelay = 5;
        gCurrentActor->subState = 2;
        break;
    case 1:
    case 2:
    case 3:
        if (gActivePlayerState->hangInputDelay != 0) {
            gActivePlayerState->hangInputDelay--;
        }
        if (playerInputUpdate(0x5A) == 0) {
            switch (gActivePlayerState->moveDir) {
            case -1:
                if (gCurrentActor->subState == 1) {
                    rate = gCurrentActor->speedXZ * 0.025;
                    animSpeed = rate > 0.1 ? rate : 0.1;
                    scriptSetActorRampTarget(gCurrentActor, animSpeed, 1.0f);
                } else {
                    actorScriptStartByIndex(gActivePlayerActor, 0x77);
                    gCurrentActor->subState = 1;
                }
                break;
            case 0:
                if (gCurrentActor->subState != 2) {
                    actorScriptStartByIndex(gActivePlayerActor, 0x76);
                    gCurrentActor->subState = 2;
                }
                break;
            case 1:
                if (gCurrentActor->subState == 3) {
                    rate = gCurrentActor->speedXZ * 0.025;
                    animSpeed = rate > 0.1 ? rate : 0.1;
                    scriptSetActorRampTarget(gCurrentActor, animSpeed, 0.0f);
                } else {
                    actorScriptStartByIndex(gActivePlayerActor, 0x78);
                    gCurrentActor->subState = 3;
                }
                break;
            }
        }
        gCurrentActor->speedY = 0.0f;
        gCurrentActor->speedXZ = gActivePlayerState->maxSpeed;
        if (playerProbeLedgeAhead(gCurrentActor, &ledgeY, 1, 15.0f) != 0) {
            if (gCurrentActor->y <= ledgeY && ledgeY - ledgeOffset - gCurrentActor->y < 10.0f && collisionGetHitFlags() != 0) {
                gCurrentActor->y = ledgeY - ledgeOffset;
                onLedge = 1;
            }
        }
        if (gCurrentActor->speedXZ < 0.0f) {
            gCurrentActor->speedXZ = (gCurrentActor->speedXZ > 0.0f) ? gCurrentActor->speedXZ : -gCurrentActor->speedXZ;
            angle = gActivePlayerState->wallNormalYaw + 0x400;
            angle &= 0xFFF;
            gCurrentActor->moveYaw = gCurrentActor->arcYawMin + 0xA;
        } else if (gCurrentActor->speedXZ > 0.0f) {
            angle = gActivePlayerState->wallNormalYaw - 0x400;
            angle &= 0xFFF;
            gCurrentActor->moveYaw = gCurrentActor->arcYawMax - 0xA;
        }
        angleOk = actorSetTargetAngleAndCheck(gCurrentActor, angle);
        if (angleOk == 0) {
            gCurrentActor->speedXZ = 0.0f;
        }
        gActivePlayerState->hangFacingYaw = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax) + 0x800;
        gActivePlayerState->hangFacingYaw &= 0xFFF;
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gActivePlayerState->hangFacingYaw, 3.0f);
        gCurrentActor->x = gActivePlayerState->wallContactX;
        gCurrentActor->z = gActivePlayerState->wallContactZ;
        if (angleOk == 0 || gCurrentActor->speedXZ == 0.0) {
            gCurrentActor->flags |= 0x800;
        } else {
            gCurrentActor->flags &= ~0x800;
        }
        break;
    }
    letGo = gPlayerPadState[gCurrentPlayerIndex].stickY < -0x32 && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000);
    if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
        letGo |= gCurrentActor->y - gCurrentActor->floorY < gKongNormalLedgeHangMinFloorHeights[gCurrentCharacterIndex];
    } else {
        letGo |= gCurrentActor->y - gCurrentActor->floorY < gKongLedgeHangMinFloorHeights[gCurrentCharacterIndex];
    }
    if (gActivePlayerState->hangInputDelay == 0) {
        lostGrip = gCurrentActor->hasArcBounds == 0 || onLedge == 0;
        collisionGetCoords(&hitA, &hitB);
        if (hitB < 0x385) {
            lostGrip |= 1;
        }
    } else {
        lostGrip = 0;
    }
    if (letGo != 0 || lostGrip != 0) {
        gActivePlayerState->invulnTimer = 0x14;
        playerResumeLocomotion(gCurrentActor);
        gCurrentActor->flags &= ~0x800;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickY >= 0x33 && gActivePlayerState->hangInputDelay == 0 && lostGrip == 0) {
        actorScriptStartByIndex(gActivePlayerActor, 0x79);
        gCurrentActor->state = 0x5C;
        gCurrentActor->subState = 0;
        gActivePlayerState->ledgeY = gCurrentActor->y + ledgeOffset;
        gActivePlayerState->prevLedgeY = gActivePlayerState->ledgeY;
    }
    actorStepPhysics(gCurrentActor, gCurrentActor->moveYaw, gCurrentActor->moveYaw);
    actorApplyVelocity(gCurrentActor);
    actorSkipFloorSnap();
    actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateLandRecover(void) {
    f32 nodeZ;
    f32 nodeY;
    f32 nodeX;
    f32 f; // FAKE: one local for the ledge/floor height deltas and the case 0 animation frame: a separate frame or delta local (any declaration slot) changes regalloc (Q1055)
    f32 ledgeY;
    f32 nodeHeight;

    gCurrentActor->speedY = 0.0f;
    gCurrentActor->speedXZ = 0.0f;
    playerInputUpdate(1);
    if (playerProbeLedgeAhead(gCurrentActor, &ledgeY, 1, 15.0f) != 0) {
        gActivePlayerState->ledgeY = ledgeY;
    }
    if (gActivePlayerState->ledgeY < gActivePlayerState->prevLedgeY) {
        f = gActivePlayerState->prevLedgeY - gActivePlayerState->ledgeY;
    } else {
        f = -(gActivePlayerState->prevLedgeY - gActivePlayerState->ledgeY);
    }
    if (f > 20.0) {
        playerEnterFall(gCurrentActor);
        actorUpdateModelMatrix(gCurrentActor, 0);
        return;
    }
    gActivePlayerState->prevLedgeY = gActivePlayerState->ledgeY;
    gCurrentActor->flags |= 0x08000000;
    actorUpdateModelMatrix(gCurrentActor, 0);
    actorCheckBoundsAndMotion(gCurrentActor);
    switch (gCurrentActor->subState) {
    case 0:
        switch (gCurrentActor->actorType) {
        case 4:
            f = gCurrentActor->sub4->model->frame;
            if (f < 25.0f) {
                actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
                nodeHeight = nodeY - gCurrentActor->y;
                gCurrentActor->y = gActivePlayerState->ledgeY - nodeHeight;
                f = gCurrentActor->sub4->model->frame;
            }
            if (f < 25.0f) {
                gCurrentActor->x = gActivePlayerState->wallContactX;
                gCurrentActor->z = gActivePlayerState->wallContactZ;
            } else if (f < 31.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 70.0f;
                gCurrentActor->y = gActivePlayerState->ledgeY;
            } else {
                gCurrentActor->y = gActivePlayerState->ledgeY;
            }
            break;
        case 5:
            f = gCurrentActor->sub4->model->frame;
            if (f < 17.0f) {
                actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
                nodeHeight = nodeY - gCurrentActor->y;
                gCurrentActor->y = gActivePlayerState->ledgeY - nodeHeight;
                f = gCurrentActor->sub4->model->frame;
            }
            if (f < 19.0f) {
                gCurrentActor->x = gActivePlayerState->wallContactX;
                gCurrentActor->z = gActivePlayerState->wallContactZ;
            } else if (f < 29.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 40.0f;
                gCurrentActor->y = gActivePlayerState->ledgeY;
            } else {
                gCurrentActor->y = gActivePlayerState->ledgeY;
            }
            break;
        case 2:
            actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
            nodeHeight = nodeY - gCurrentActor->y;
            gCurrentActor->y = gActivePlayerState->ledgeY - nodeHeight;
            if (gCurrentActor->sub4->model->frame > 16.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->y = gActivePlayerState->ledgeY;
                gCurrentActor->speedXZ = 30.0f;
            } else {
                gCurrentActor->x = gActivePlayerState->wallContactX;
                gCurrentActor->z = gActivePlayerState->wallContactZ;
            }
            break;
        case 6:
        case 7:
            f = gCurrentActor->sub4->model->frame;
            if (f < 18.0f) {
                actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
                nodeHeight = nodeY - gCurrentActor->y;
                gCurrentActor->y = gActivePlayerState->ledgeY - nodeHeight;
                gCurrentActor->x = gActivePlayerState->wallContactX;
                gCurrentActor->z = gActivePlayerState->wallContactZ;
            } else if (f < 26.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 50.0f;
                gCurrentActor->y = gActivePlayerState->ledgeY;
            } else {
                if (gActivePlayerState->ledgeY < gCurrentActor->floorY) {
                    f = gCurrentActor->floorY - gActivePlayerState->ledgeY;
                } else {
                    f = -(gCurrentActor->floorY - gActivePlayerState->ledgeY);
                }
                if (f >= 20.0) {
                    playerEnterFall(gCurrentActor);
                } else {
                    gCurrentActor->y = gCurrentActor->floorY;
                }
            }
            break;
        default:
            actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
            nodeHeight = nodeY - gCurrentActor->y;
            gCurrentActor->y = gActivePlayerState->ledgeY - nodeHeight;
            if (gCurrentActor->sub4->model->frame > 14.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 10.0f;
                gCurrentActor->y = gActivePlayerState->ledgeY;
            } else {
                gCurrentActor->x = gActivePlayerState->wallContactX;
                gCurrentActor->z = gActivePlayerState->wallContactZ;
            }
            break;
        }
        playerApplyMotion();
        break;
    case 1:
        playerApplyMotion();
        if (gActivePlayerState->ledgeY < gCurrentActor->floorY) {
            f = gCurrentActor->floorY - gActivePlayerState->ledgeY;
        } else {
            f = -(gCurrentActor->floorY - gActivePlayerState->ledgeY);
        }
        if (f < 20.0) {
            gCurrentActor->y = gCurrentActor->floorY;
            gCurrentActor->contactFlags |= 1;
            gCurrentActor->speedY = -50.0f;
            playerResumeLocomotion(gCurrentActor);
        } else {
            playerEnterFall(gCurrentActor);
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
    actorCheckWorldBounds(gCurrentActor);
}

void playerStateCutsceneTransition(void) {
    gActivePlayerState->maxSpeed = 0.0f;
    if ((playerInputUpdate(1) == 0) && (gCurrentActor->contactFlags & 1)) {
        playerSelectWalkRunState(gCurrentActor, gCurrentActor->speedXZ, 0, 1);
    }
    if (gCurrentMap == 0x52) {
        gActivePlayerState->decelRate = gKongDecelRate[gCurrentCharacterIndex] * 5.0;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateCutscenePause(void) {
    if (gCurrentActor->subState == 0) {
        camSetTarget(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, 0x32, 0, 5, 0x32, 0x14, 0, 0.2f);
        gCurrentActor->subState++;
    }
    playerApplyImpactRumble(1);
    gActivePlayerState->decelRate = gCutscenePauseDecelRate;
}

void playerStateBarrelBlast(void) {
    switch (gCurrentActor->subState) {
    case 0:
        camSetTargetScaled(gActivePlayerState->camActor, gCurrentActor, 4, 0, 0x19, 0, 5, -3, 0xA, 0, 0.15f);
        actorScriptStartByIndex(gCurrentActor, 0x85);
        gCurrentActor->subState++;
    case 2:
        camSetTargetScaled(gActivePlayerState->camActor, gCurrentActor, 4, 0x396, 0x19, 0, 5, 0xB, 0xB, 0, 0.15f);
        gCurrentActor->subState++;
        break;
    case 4:
        camSetTargetScaled(gActivePlayerState->camActor, gCurrentActor, 4, 0xE74, 0x14, 0, 5, 0x13, 0xA, 0, 0.15f);
        gCurrentActor->subState++;
        break;
    case 6:
        camSetTargetScaled(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, 0x11, 0, 5, 0x29, 0xA, 0, 0.15f);
        gCurrentActor->subState++;
        break;
    case 8:
        camResetPlayer(gCurrentActor, 0);
        gActivePlayerState->stateFlags |= 4;
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateResumeFromCutscene(void) {
    if (gCurrentActor->subState == 1) {
        camResumePath();
        gCurrentActor->subState++;
        playerResumeLocomotion(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct G20Light {
    /* 0x00 */ f32 savedR;
    /* 0x04 */ f32 savedG;
    /* 0x08 */ f32 savedB;
    /* 0x0C */ Actor *effectActor;
    /* 0x10 */ Actor *owner;
    /* 0x14 */ s16 pitch;
    /* 0x16 */ s16 roll;
    /* 0x18 */ s32 chunk;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u8 allFairies; // all 20 banana fairies found
} G20Light;

void playerStateDialogueWait(void) {
    G20Light *light;
    PlayerState *ps;
    s32 chunk;
    s32 i;
    s16 pathIndex;

    playerInputUpdate(1);
    playerClearPitchRollFlags(gCurrentActor);
    switch (gCurrentActor->subState) {
    case 0:
        if (countBananaFairies() == 0x14) {
            pathIndex = 0x1A;
        } else {
            pathIndex = 0x11;
        }
        camStartPath(gCurrentActor, pathIndex, 5);
        gCurrentActor->subState = 1;
        break;
    case 1:
        gGlobalPauseFlags &= ~0x10030;
        actorSpawn(0x141, 0x3D);
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY * 2);
        gSpawnedActor->flags |= 0x40000000;
        gSpawnedActor->yaw += 0x800;
        gSpawnedActor->yaw &= 0xFFF;
        gSpawnedActor->parentActor = gCurrentActor;
        actorScriptStart(gSpawnedActor, 0x2B7);
        light = gSpawnedActor->customState;
        light->owner = gCurrentActor;
        light->chunk = gCurrentActor->chunkIndex;
        chunk = light->chunk;
        if (chunk == -1) {
            light->chunk = 0;
            chunk = 0;
        }
        light->roll = gCurrentActor->roll;
        light->pitch = gCurrentActor->pitch;
        lightGetColor(&light->savedR, &light->savedG, &light->savedB, chunk);
        lightSetColor(1.0f, 1.0f, 1.0f, light->chunk);
        actorSpawn(0x136, 0xA8);
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleX);
        gSpawnedActor->flags |= 0x40000000;
        light->effectActor = gSpawnedActor;
        light->allFairies = countBananaFairies() == 0x14;
        gCurrentActor->subState = 2;
        break;
    case 2:
        if (currentActorTestClearFlag()) {
            currentActorClearFlag();
            effectSpawnKongRing();
            sfxAllocateChannel(0x3B, 1.0f);
            gCurrentActor->subState = 3;
        }
        /* fallthrough */
    case 3:
        if (currentActorTestClearFlag()) {
            ps = gCurrentActor->customState;
            currentActorClearFlag();
            playerResumeLocomotion(gCurrentActor);
            healthRefill(ps->playerIndex);
            for (i = 0; i < 4; i++) {
                slotQueueAddValue(gConsumableRefillSlots[i], 0, 0x270F);
                slotQueueUpdate(gConsumableRefillSlots[i], 0, 0);
            }
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 gSplitScreenMode;

void playerStateDialogueHold(void) {
    PlayerState *ps = gCurrentActor->customState;
    s32 step;
    s16 alpha;

    playerStateQueueCallback(0x5C, 0, gCurrentPlayerIndex);
    if (gSplitScreenMode == 0) {
        gPlayerSlots[ps->playerIndex].viewFadingOut = 1;
    }
    gPlayerSlots[ps->playerIndex].rumbleDisabled = 1;
    gCurrentActor->flags &= 0xFFFF7FFF;
    alpha = gCurrentActor->alpha;
    step = (alpha < 4) ? alpha : 4;
    gCurrentActor->alpha = alpha - step;
    if (gCurrentActor->alpha == 0) {
        if (gSplitScreenMode == 0) {
            gPlayerSlots[ps->playerIndex].active = 0;
        }
        gCurrentActor->flags &= ~4;
    }
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateShrinkToPoint(void) {
    PlayerState *ps = gCurrentActor->customState;

    gCurrentActor->sub4->scaleX *= 0.92;
    gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleX;
    gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleX;
    gCurrentActor->x += (ps->savedX - gCurrentActor->x) * 0.125f;
    gCurrentActor->y += (ps->savedY - gCurrentActor->y) * 0.125f;
    gCurrentActor->z += (ps->savedZ - gCurrentActor->z) * 0.125f;
    gCurrentActor->pitch += 0xFF;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateGrowFromPoint(void) {
    PlayerState *ps = gCurrentActor->customState;

    gCurrentActor->sub4->scaleX *= 1.08;
    if (gCurrentActor->sub4->scaleX > 0.15) {
        gCurrentActor->sub4->scaleX = 0.15f;
        gCurrentActor->state = 0xC;
        gCurrentActor->subState = 0;
        gCurrentActor->pitch = -0xFF;
    }
    gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleX;
    gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleX;
    gCurrentActor->x += ps->heading[0];
    gCurrentActor->z += ps->heading[2];
    gCurrentActor->pitch += 0xFF;
    gCurrentActor->pitch &= 0xFFF;
    actorUpdateModelMatrix(gCurrentActor, 0);
}
