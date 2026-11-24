#include "common.h"
#include "actor.h"
#include "sched.h"
#include "race.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/5E020_hash_table.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/8D3E0_actor_list.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/CC800_player_setup.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/E4090_player_input.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/F56F0_player_weapon.h"
#include "proto/global/FCCD0_slot_queue.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;
extern s32 gCurrentMap;

extern PlayerStruct *gPlayerSlots;

/* Racer actor ridden by the player: the race overlay's path cursor follows the base Actor (RaceRacerActor). */
typedef struct EfExtActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ RacePathState *path;
} EfExtActor;

/* Arguments for the next queued player-state callback (playerStateSetCallbackParameters). */
typedef struct EfCallbackParams {
    /* 0x00 */ s32 param0; // cutscene command 0x73's a, playerTryEnterViewMode's view mode, callback 0x2F
                           // playerTakeQueuedDamage's amount; copied to queuedParam0
    /* 0x04 */ s32 param1;
    /* 0x08 */ s32 param2;
} EfCallbackParams;

extern EfCallbackParams gPlayerStateCallbackParams;

s32 playerStateQueueCallback(s16 priority, Actor *actor, u8 player) {
    if (gPlayerSlots[player].queuedState < priority) {
        gPlayerSlots[player].queuedState = priority;
        gPlayerSlots[player].queuedActor = actor;
        gPlayerSlots[player].queuedParam0 = gPlayerStateCallbackParams.param0;
        gPlayerSlots[player].queuedParam1 = gPlayerStateCallbackParams.param1;
        gPlayerSlots[player].queuedParam2 = gPlayerStateCallbackParams.param2;
        if (actor != NULL) {
            gPlayerSlots[player].queuedActorId = actor->instanceId;
        }
        return 1;
    }
    return 0;
}

void playerStateSetCallbackParameters(s32 unused, s32 param0, s32 param1, s32 param2) {
    gPlayerStateCallbackParams.param0 = param0;
    gPlayerStateCallbackParams.param1 = param1;
    gPlayerStateCallbackParams.param2 = param2;
}

void (*gPlayerStateCallbacks[])(void) = {
    playerStateEnterDamageTake,
    playerStateEnterKnockbackRecovery,
    playerStateEnterDamageKnockback,
    playerStateEnterHoldPickup,
    playerStateEnterGroundImpact,
    playerStateEnterKnockbackState2,
    playerStateEnterKnockbackState4,
    playerStateEnterKnockbackState3,
    playerStateEnterKnockbackState5,
    playerStateInitApproachVelocity,
    playerStateEnterHoldThrow,
    playerStateEnterState59,
    playerStateEnterState57,
    playerStateEnterState17,
    playerStateTakeHitAndDamage,
    playerStateInitLaunchParams,
    playerStateEnterState10,
    playerStateEnterState11,
    playerStateEnterState12,
    playerStateEnterState29,
    playerStateInitState5F,
    playerStateInitState60,
    playerStateEnterState15ThrowHeldActor,
    playerStateSetLaunchVelocity,
    playerStateEnterState4F,
    playerStateLockMovementAndResume,
    playerStateThrowHeldActorAndResume,
    playerStateThrowHeldActorWithScript,
    playerStateSwimTreadWithScript,
    playerStateEnterFadeWarp,
    playerResumeLocomotionAndThrow,
    playerStateInitKongAction78,
    playerStateEnterDoubleJumpWithSfx,
    playerStateEnterSlideBrake,
    playerStateEnterSlideReverse,
    playerStateDropAndResume,
    playerStateEnterState3D,
    playerStateInitTumble,
    playerStateEnterAction24,
    playerStateEnterKnockbackState,
    playerStateEnterBarrelBlast,
    playerStateStopChannelAndClearCarried,
    playerStateEnterPulseForm,
    playerStateTakeDamageAndDrop,
    playerStateAttachHeldActorToPlayer,
    playerStateEnterSlideRecover,
    playerStateCutsceneDamageCheck,
    playerTakeQueuedDamage,
    playerStateDamageCheck,
    playerStateDamageCheck2,
    playerStateDamageCheck3,
    playerStateDamageCheck4,
    playerStateDamageTargetCheck,
    playerTakeFallDamage,
    playerStateDamageSelector,
    playerStateDamageCheck5,
    playerStateStopSfxAndClearCarried,
    playerStateEnterFallAndSetGravity,
    playerStateInitAnimalTransformation,
    playerRevertToSavedKong,
    playerStateNoop1,
    playerStateCheckLandingAir,
    playerStateEnterState3C,
    playerStateEnterDamageReaction,
    playerStateEnterDamageReaction2,
    playerStateDropHeldActor,
    playerStateDropHeldActorAndScript,
    playerStateDropHeldActorSetKong,
    playerStateDropHeldActorSetKong2,
    playerStateEnterSquish,
    playerStateSetFlag8,
    playerStateEnterFlattened,
    playerStateEnterKnockbackState6,
    playerStateEnterElectrocute,
    playerStateEnterStunState1,
    playerStateInitKongAction69,
    playerStateEnterSlideSlope,
    playerStateEnterFrozen,
    playerStateClearCarriedAndCallF00BC,
    playerStateAdjustUpwardVelocity,
    playerStateAdjustUpwardVelocity200,
    playerStateAdjustUpwardVelocity300,
    playerStateSpawnParticles,
    playerStateSetFlagsByActorType,
    playerStateInitState23,
    playerStateClearCarriedSetFlags,
    playerStateEnterCutscenePause,
    playerStateEnterClimbTree,
    playerStateEnterFairyReward,
    playerStateEnterShrinkToSavedPoint,
    playerStateEnterGrowFromSavedPoint,
    playerStateEnterMpEliminated,
    playerStateNoop2,
};

void playerStateDispatchQueuedCallback(void) {
    if (gPlayerSlots[gCurrentPlayerIndex].queuedState >= 0) {
        if (gPlayerSlots[gCurrentPlayerIndex].queuedActor != NULL) {
            if ((actorTableContains(gPlayerSlots[gCurrentPlayerIndex].queuedActor) == 0) ||
                (gPlayerSlots[gCurrentPlayerIndex].queuedActor->instanceId != gPlayerSlots[gCurrentPlayerIndex].queuedActorId)) {
                gPlayerSlots[gCurrentPlayerIndex].queuedActor = NULL;
            }
        }
        gPlayerStateCallbacks[gPlayerSlots[gCurrentPlayerIndex].queuedState]();
    }
    gPlayerSlots[gCurrentPlayerIndex].queuedState = -1;
}

void playerStateInitApproachVelocity(void) {
    playerSetTerminalVelocity5B0();
    gCurrentActor->state = 0x22;
    gCurrentActor->subState = 0;
    gCurrentActor->speedY = 100.0f;
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->airAccel = 100.0f;
    if (gActivePlayerState->airTimer == 0) {
        playerApproachVelocity(gActivePlayerState->targetYaw, gActivePlayerState->maxSpeed, gActivePlayerState->targetSpeed);
    }
    gActivePlayerState->airAccel = 10.0f;
    actorScriptStart(gCurrentActor, 0x17B);
}

void playerStateEnterState3D(void) {
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 6) {
        playerResumeLocomotion(gActivePlayerActor);
        return;
    }
    gCurrentActor->state = 0x3D;
    gCurrentActor->subState = 0;
    if (gActivePlayerState->animIndex == 0x22) {
        actorScriptStart(gCurrentActor, 0x131);
        return;
    }
    actorScriptStartByIndex(gCurrentActor, 0xD);
}

s32 playerCanTakeHit(Actor *actor) {
    s32 canHit;
    PlayerState *playerState;

    playerState = actor->customState;
    canHit = (playerState->surfaceTimer == 0) || (gPlayerSlots[gCurrentPlayerIndex].queuedState == 0x3F);
    if ((gPlayerCharacterId[gCurrentPlayerIndex] == 7) || (playerState->stateFlags & 0x8000)) {
        return 0;
    }
    switch (actor->state) {
    case 0x34:
    case 0x36:
        canHit = 0;
        break;
    default:
        canHit &= 1;
        break;
    }
    return canHit;
}

void playerStateInitState23(void) {
    gCurrentActor->state = 0x23;
    gCurrentActor->subState = 0;
    actorScriptStart(gActivePlayerActor, 0x3BC);
}

void playerStateInitState5F(void) {
    gCurrentActor->state = 0x5F;
    gCurrentActor->subState = 0;
    gActivePlayerState->isHoldingObject = 0;
    actorScriptStartByIndex(gCurrentActor, 0x4A);
}

void playerStateInitState60(void) {
    s32 selector;

    selector = 2;
    if (slotQueueGetValue(3, gActivePlayerState->playerIndex) != 0) {
        selector = 3;
    }
    slotQueueUpdate(selector, 0, 0);
    gCurrentActor->state = 0x60;
    gCurrentActor->subState = 0;
    gActivePlayerState->isHoldingObject = 0;
    actorScriptStartByIndex(gCurrentActor, 0x4B);
}

void playerStateInitLaunchParams(void) {
    switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
    case 0:
    case 1:
    case 2:
        gCurrentActor->speedY = 50.0f;
        gCurrentActor->accelY = -2.5f;
        break;
    case 3:
        gCurrentActor->speedY = 140.0f;
        gCurrentActor->accelY = -20.0f;
        break;
    case 4:
    case 5:
        gCurrentActor->speedY = 40.0f;
        gCurrentActor->accelY = -7.0f;
        break;
    }
    gCurrentActor->state = 0x2A;
    gCurrentActor->subState = 0;
    actorScriptStartByIndex(gCurrentActor, 0x43);
    gActivePlayerState->unk64 = 0;
    gActivePlayerState->chargeTimer = 0x32;
}

void playerStateInitTumble(void) {
    gActivePlayerState->moveTier = -1;
    gActivePlayerState->targetSpeed = 170.0f;
    gCurrentActor->state = 0x3F;
    gCurrentActor->subState = 0;
    gActivePlayerState->animIndex = 0;
    actorScriptStart(gCurrentActor, 0x14F);
}

void playerStateTakeDamagePrep(void) {
    CamState *camState;
    s16 heightGoal;
    u8 zoomLevel;

    camState = gActivePlayerState->camActor->customState;
    zoomLevel = camState->zoomLevel;
    heightGoal = camState->followHeightGoal;
    if (zoomLevel != 0) {
        camState->savedZoomLevel = zoomLevel;
        heightGoal = 0x80;
    }
    camSaveYaw(gActivePlayerState->camActor);
    camSetZoomLevel(gActivePlayerState->camActor, 0);
    camState->mode = gPlayerSlots[gCurrentPlayerIndex].queuedParam0;
    if (camState->mode == 3) {
        sfxStopSlotSound(gActivePlayerActor, 0);
        sfxPlayOnFreeSlot(0x26, 0x7FFF, 63.0f, 1.0f, 0, 0);
        if (gPlayerSlots[gCurrentPlayerIndex].queuedParam1 != 0) {
            playerKongDrawGun(gActivePlayerActor);
        }
    }
    camState->aimHeightBase = 0x80;
    gActivePlayerState->camActor->distToFloor = heightGoal;
    camState->followHeightGoal = heightGoal;
    camState->orbitYaw = gActivePlayerActor->yaw + 0x800;
    gActivePlayerActor->speedXZ = 0.0f;
    gActivePlayerActor->contactFlags |= 0x2000;
}

void playerStateEnterKnockbackState2(void) {
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 2;
    gActivePlayerActor->subState = 0;
    gActivePlayerActor->subState = 0xA;
    if (gActivePlayerState->gunDrawn != 0) {
        actorScriptStart(gActivePlayerActor, 0x23);
    } else {
        actorScriptStart(gActivePlayerActor, 0x13);
    }
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->targetSpeed = 0.0f;
}

void playerStateEnterKnockbackState4(void) {
    sfxPlayOnFreeSlot(0x1B9, 0x7FFF, 63.0f, 1.0f, 0xA, 0);
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 4;
    gActivePlayerActor->subState = 0;
    gActivePlayerActor->subState = 0xA;
    actorScriptStart(gActivePlayerActor, 0x13);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->targetSpeed = 0.0f;
    slotQueueUpdate(6, 1, 0);
}

void playerStateEnterKnockbackState3(void) {
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 3;
    gActivePlayerActor->subState = 0;
    gActivePlayerActor->subState = 0xA;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->targetSpeed = 0.0f;
}

void playerStateEnterKnockbackState5(void) {
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 5;
    gActivePlayerActor->subState = 0;
    gActivePlayerActor->subState = 0xA;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->targetSpeed = 0.0f;
    slotQueueUpdate(6, 1, 0);
}

void playerStateEnterState4F(void) {
    gCurrentActor->state = 0x4F;
    gCurrentActor->subState = 2;
    actorScriptStartByIndex(gCurrentActor, 0x34);
    gActivePlayerState->gravityDelay = 0;
}

void playerStateEnterStunState1(void) {
    gGlobalPauseFlags |= 0x4000;
    gActivePlayerActor->state = 1;
    gActivePlayerActor->subState = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0.0f, 0.0f);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->moveTier = -1;
}

void playerStateEnterKnockbackState6(void) {
    gActivePlayerActor->state = 6;
    gActivePlayerActor->subState = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0.0f, 0.0f);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->moveTier = -1;
    gActivePlayerActor->flags &= ~4;
}

void playerStateEnterElectrocute(void) {
    gActivePlayerActor->state = 0x6B;
    gActivePlayerActor->subState = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0.0f, 0.0f);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->moveTier = -1;
    gActivePlayerActor->flags &= ~4;
}

void playerStateEnterSquish(void) {
    gActivePlayerActor->state = 7;
    gActivePlayerActor->subState = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x7A);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->moveTier = -1;
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
    gActivePlayerActor->flags &= ~0x40000;
    gActivePlayerActor->speedXZ = 0.0f;
}

void playerStateSetFlag8(void) {
    gActivePlayerState->stateFlags |= 8;
}

void playerStateInitKongAction69(void) {
    gActivePlayerActor->state = 0x69;
    gActivePlayerActor->subState = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0.0f, 0.0f);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->moveTier = -1;
    gActivePlayerActor->flags &= ~0x1000000;
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
}

/* The race overlay's racePlayCheckpointSfx: starts a boost of the path cursor's racer. */
void func_80026004(RacePathState *, u8, f32);

void playerStateAdjustUpwardVelocity(void) {
    Actor *actor;
    RacePathState *path;

    actor = gActivePlayerState->actor;
    path = ((EfExtActor *)actor)->path;
    if (actor->state < 3) {
        func_80026004(path, 0x1E, 1.0f);
    }
}

void playerStateAdjustUpwardVelocity200(void) {
    gActivePlayerState->actor->speedY += 200.0f;
    if (gActivePlayerState->actor->speedY > 200.0f) {
        gActivePlayerState->actor->speedY = 200.0f;
    }
    behaviourAddSlotQueueValueB(3);
}

void playerStateAdjustUpwardVelocity300(void) {
    gActivePlayerState->actor->speedY += 300.0f;
    behaviourAddSlotQueueValueB(3);
}

void playerStateInitAnimalTransformation(void) {
    playerTransformAnimalStartSfx(gActivePlayerActor);
    gActivePlayerState->transformTimer = gPlayerSlots[gCurrentPlayerIndex].queuedParam0;
}

void playerStateInitKongAction78(void) {
    actorScriptStart(gActivePlayerActor, 0x1A);
    gActivePlayerActor->state = 0x78;
    gActivePlayerActor->subState = 0;
}

void playerStateDropAndResume(void) {
    playerDropHeldActor(gCurrentActor);
    playerResumeLocomotion(gCurrentActor);
}

extern ModelSlot *gModelSlots;
extern s16 gKongDiveFrames[];
extern s16 gKongDiveAngles[];

void playerStateEnterFlattened(void) {
    f32 speed;

    speed = 1.0f;
    playerKongHolsterGun(gCurrentActor);
    gActivePlayerActor->state = 0x6C;
    gActivePlayerActor->subState = 0;
    actorScriptStart(gActivePlayerActor, 0x3B);
    if (gPlayerCharacterId[0] == 0) {
        speed = 0.5f;
    }
    scriptSetActorRampTarget(gActivePlayerActor, speed, 0.0f);
    actorClearMovementFlags(gActivePlayerActor);
    gActivePlayerActor->x = gModelSlots[hashTableLookup(gActivePlayerActor->cutsceneId)].x;
    gActivePlayerActor->y = gModelSlots[hashTableLookup(gActivePlayerActor->cutsceneId)].y + 5.0f;
    gActivePlayerActor->z = gModelSlots[hashTableLookup(gActivePlayerActor->cutsceneId)].z;
    gActivePlayerActor->pitch = 0;
    gActivePlayerActor->roll = 0;
    camStartPath(gActivePlayerActor, 0, 1);
    slotQueueUpdate(0, 1, 0);
}

void playerStateEnterSlideSlope(void) {
    s32 animation;

    ((CamState *)gActivePlayerState->camActor->customState)->flags |= 4;
    gActivePlayerActor->state = 0x6D;
    gActivePlayerActor->subState = 0;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->moveTier = -1;
    gActivePlayerActor->flags &= ~1;
    if (gCurrentMap == 0x27) {
        gActivePlayerActor->collisionMode = 1;
    }
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
    if (gActivePlayerActor->actorType == 2) { animation = 0x53; } else { animation = 0x1C7; } controllerAnimSetStateIfChanged(gActivePlayerActor, animation, 0.0f, 0.0f); // LAYOUT: one source line steers the scheduler (li at,2 after mfc1)
}

void playerStateEnterFrozen(void) {
    Actor *actor;

    gActivePlayerActor->state = 0x75;
    gActivePlayerActor->subState = 0;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->moveTier = -1;
    gActivePlayerActor->flags &= ~1;
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
    actor = gActivePlayerState->actor;
    actorCopyPoseAndScale(gActivePlayerActor, actor, actor->sub4->scaleX);
    gActivePlayerActor->collisionMode = 1;
    controllerAnimSetStateIfChanged(gActivePlayerActor, 0x22A, 0.0f, 0.0f);
}

void playerStateEnterState3C(void) {
    gActivePlayerState->subTimer = gKongDiveAngles[gCurrentCharacterIndex];
    gActivePlayerState->pitchAngle = gCurrentActor->yaw;
    gActivePlayerState->actionTimer = gKongDiveFrames[gCurrentCharacterIndex];
    gCurrentActor->state = 0x4F;
    gCurrentActor->subState = 1;
    if (gCurrentActor->speedY > 0.0f) {
        gCurrentActor->speedY = 0.0f;
    }
    actorScriptStartByIndex(gCurrentActor, 0x36);
    controllerAnimSetStateRemap(gCurrentActor, 0x31, 0.0f, 8.0f);
    scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
}

extern f32 gKongMaxTierEnterSpeeds[];
extern f32 gKongTurnDecelRates[];
extern f32 gKongArcContactTargetSpeed[];
extern f32 gKongArcContactAirAccel[];
extern s16 gKongArcContactTurnRate[];
extern f32 gKongWaterJumpVelocityY[];
extern f32 gKongWaterJumpAirAccel[];
extern f32 gKongWaterJumpDecelRates[];
extern f32 gKongNormalLedgeHangOffsets[];
extern f32 gKongLedgeHangOffsets[];
extern SchedStruct gScheduler;
extern f32 gKongDecelRate[];
extern s16 gKongNormalSwimSurfaceDepths[];
extern s16 gKongWaterEntryMaxFallHeights[];
extern s16 gKongWaterEntryMinSinkDepths[];
extern s16 gKongWaterEntryMaxSinkDepths[];
extern f32 gKongSwimTopSpeeds[];
extern s16 gKongWaterEntryTurnRates[];
extern f32 gKongSwimBuoyancy[];

void playerStateCheckLandingAir(void) {
    f32 rise;
    f32 waterY;
    f32 decelMinSigned;
    f32 maxDepth;
    f32 speed;
    f32 maxSpeed;
    f32 speedY;
    f32 decelMin;
    f32 depth;
    f32 decel;

    playerThrowHeldActor(gActivePlayerActor);
    decelMinSigned = gKongSwimBuoyancy[gCurrentCharacterIndex];
    if (decelMinSigned > 0.0f) {
        decelMin = decelMinSigned;
    } else {
        decelMin = -decelMinSigned;
    }
    waterY = gActivePlayerActor->waterY;
    maxDepth = gKongWaterEntryMaxFallHeights[gCurrentCharacterIndex];
    depth = gActivePlayerActor->prevPeakY - waterY;
    if (maxDepth < depth) {
        depth = maxDepth;
    }
    rise = gKongWaterEntryMinSinkDepths[gCurrentCharacterIndex] + ((gKongWaterEntryMaxSinkDepths[gCurrentCharacterIndex] - gKongWaterEntryMinSinkDepths[gCurrentCharacterIndex]) * (depth / maxDepth));
    rise -= (waterY - gKongNormalSwimSurfaceDepths[gCurrentCharacterIndex]) - gActivePlayerActor->y;
    rise *= 40.0f;
    depth *= 40.0f;
    maxDepth *= 40.0f;
    if (rise > 0.0f) {
        speedY = gActivePlayerActor->speedY;
        speedY = speedY * (0.5 + depth / (2 * maxDepth));
        decel = (speedY * speedY) / (2 * rise);
        if (decel < decelMin) {
            decel = decelMin;
        }
    } else {
        speedY = 0.0f;
        decel = decelMin;
    }
    gActivePlayerActor->speedY = speedY;
    gActivePlayerState->slideSpeed = decel;
    gActivePlayerState->actionTimer = 0;
    gActivePlayerState->decelRate = gKongDecelRate[gCurrentCharacterIndex];
    speed = gCurrentActor->speedXZ;
    maxSpeed = gKongSwimTopSpeeds[gCurrentCharacterIndex];
    if (speed < maxSpeed) {
        gCurrentActor->speedXZ = speed;
    } else {
        gCurrentActor->speedXZ = maxSpeed;
    }
    gActivePlayerActor->state = 0x4E;
    gActivePlayerActor->subState = 0;
    actorScriptStartByIndex(gCurrentActor, 0x35);
    gActivePlayerState->turnRate = gKongWaterEntryTurnRates[gCurrentCharacterIndex];
}

void playerStateEnterKnockbackRecovery(void) {
    gActivePlayerActor->state = 0x51;
    gActivePlayerActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongWaterJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    gActivePlayerState->airAccel = gKongWaterJumpAirAccel[gCurrentCharacterIndex];
    gActivePlayerState->decelRate = gKongWaterJumpDecelRates[gCurrentCharacterIndex];
    actorScriptStartByIndex(gActivePlayerActor, 0x3E);
    scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}

void playerStateEnterDamageKnockback(void) {
    f32 current;
    f32 limit;

    gActivePlayerActor->state = 0x50;
    gActivePlayerActor->subState = 0;
    gCurrentActor->speedY = -10.0f;
    gActivePlayerState->gravityDelay = 0;
    current = gCurrentActor->speedXZ;
    limit = gKongMaxTierEnterSpeeds[gCurrentCharacterIndex];
    if (current < limit) {
        gCurrentActor->speedXZ = current;
    } else {
        gCurrentActor->speedXZ = limit;
    }
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    actorScriptStartByIndex(gActivePlayerActor, 0x3C);
}

void playerStateEnterHoldPickup(void) {
    gActivePlayerState->queuedHeldActor = gActorGlobalState.grabCandidate;
    gActivePlayerState->queuedHeldActorId = gActivePlayerState->queuedHeldActor->instanceId;
    switch (gActivePlayerState->queuedHeldActor->actorType) {
    case 0x3D:
    case 0x3F:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x55:
    case 0x82:
        actorScriptStart(gActivePlayerActor, 0x1C8);
        break;
    default:
        actorScriptStartByIndex(gActivePlayerActor, 0x2B);
        break;
    }
    gActivePlayerActor->state = 0x47;
    gActivePlayerActor->subState = 0;
}

void playerStateEnterGroundImpact(void) {
    actorScriptStartByIndex(gActivePlayerActor, 8);
    scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
    controllerAnimSetStateRemap(gActivePlayerActor, 0x2E, 0.0f, 6.0f);
    gActivePlayerActor->state = 0x46;
    gActivePlayerActor->subState = 0;
    gActivePlayerState->targetSpeed = gKongArcContactTargetSpeed[gCurrentCharacterIndex];
    gActivePlayerState->airAccel = gKongArcContactAirAccel[gCurrentCharacterIndex];
    gActivePlayerState->turnRate = gKongArcContactTurnRate[gCurrentCharacterIndex];
    gActivePlayerState->moveTier = -1;
}

void playerStateEnterAction24(void) {
    gCurrentActor->state = 0x24;
    gCurrentActor->subState = 0;
    actorScriptStart(gCurrentActor, 0x1B2);
    gActivePlayerState->chargeTimer = 0x32;
}

void playerStateEnterHoldThrow(void) {
    f32 height;

    if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
        height = gKongNormalLedgeHangOffsets[gCurrentCharacterIndex];
    } else {
        height = gKongLedgeHangOffsets[gCurrentCharacterIndex];
    }
    gActivePlayerActor->state = 0x5B;
    gActivePlayerActor->subState = 0;
    gActivePlayerState->ledgeHangOffset = height;
    gActivePlayerActor->y = gActivePlayerState->ledgeY - gActivePlayerState->ledgeHangOffset;
    gActivePlayerActor->moveYaw = gActivePlayerActor->arcYawMin + 0x14;
    gActivePlayerActor->speedY = 0.0f;
    actorScriptStartByIndex(gActivePlayerActor, 0x75);
    actorScriptExecute(gActivePlayerActor);
}

void playerStateEnterState57(void) {
    gActivePlayerActor->contactFlags |= 0x40;
    gActivePlayerActor->renderFlags &= ~0x2000;
    gActivePlayerActor->state = 0x57;
    gActivePlayerActor->subState = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x69);
    actorScriptExecute(gActivePlayerActor);
}

extern s32 gGlobalCutsceneFlags;
extern f32 gKongJumpVelocityY[];
extern s16 gKongChargeLaunchSpeeds[];

void playerStateEnterState59(void) {
    CamState *camState;

    camState = gActivePlayerState->camActor->customState;
    gActivePlayerActor->contactFlags |= 0x40;
    gActivePlayerActor->renderFlags &= ~0x2000;
    gActivePlayerActor->state = 0x59;
    gActivePlayerActor->subState = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x70);
    actorScriptExecute(gActivePlayerActor);
    camStartBlendRamp(camState, 0x14);
}

void playerStateEnterState17(void) {
    CamState *camState;

    camState = gActivePlayerState->camActor->customState;
    gCurrentActor->state = 0x17;
    gCurrentActor->subState = 0;
    if (gGlobalCutsceneFlags & 2) {
        gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex] * 1.3;
    } else {
        gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
    }
    gActivePlayerActor->speedXZ = gActivePlayerState->pathExitSpeedXZ;
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->airTimer = 0xA;
    actorScriptStartByIndex(gCurrentActor, 0x10);
    camStartBlendRamp(camState, 0x14);
}

void playerStateTakeHitAndDamage(void) {
    s32 damage;

    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        if (gGlobalCutsceneFlags & 2) {
            damage = 0;
        } else {
            damage = 1;
        }
        playerTakeDamage(damage);
    }
}

void playerStateEnterState10(void) {
    if ((gPlayerCount >= 2) || (gActivePlayerActor->actorType != 6) || (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1)) {
        gActivePlayerActor->speedY = 260.0f;
        playerSetBaseGravity();
        gActivePlayerState->gravityDelay = 0;
        gActivePlayerState->turnRate = 0x64;
        actorScriptStartByIndex(gActivePlayerActor, 0x1F);
        scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
        gActivePlayerActor->state = 0x30;
        gActivePlayerActor->subState = 0;
        playerDropHeldActor(gActivePlayerActor);
    }
}

void playerStateEnterState11(void) {
    gActivePlayerActor->speedY = 260.0f;
    playerSetBaseGravity();
    gActivePlayerState->gravityDelay = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x20);
    scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
    gActivePlayerActor->state = 0x30;
    gActivePlayerActor->subState = 0;
    playerDropHeldActor(gActivePlayerActor);
}

extern s16 gKongSlideLaunchGravityDelays[];
extern s16 gKongSlideLaunchSpeedSteps[];
extern s16 gKongSlideLaunchSpeedMax[];

void playerStateEnterState12(void) {
    gActivePlayerState->gravityDelay = gKongSlideLaunchGravityDelays[gCurrentCharacterIndex];
    gActivePlayerState->slideLaunchSpeed += gKongSlideLaunchSpeedSteps[gCurrentCharacterIndex];
    if (gKongSlideLaunchSpeedMax[gCurrentCharacterIndex] < gActivePlayerState->slideLaunchSpeed) {
        gActivePlayerState->slideLaunchSpeed = gKongSlideLaunchSpeedMax[gCurrentCharacterIndex];
    }
    gActivePlayerActor->speedY = 0.0f;
    gActivePlayerState->gravityDelay = 0;
}

void playerStateEnterState29(void) {
    if ((gCurrentActor->state != 2) && (gPlayerCharacterId[gCurrentPlayerIndex] == 6)) {
        gCurrentActor->state = 0x29;
        gCurrentActor->subState = 0;
        actorScriptStartByIndex(gCurrentActor, 0x3F);
        gActivePlayerState->unk64 = 0;
        gActivePlayerState->slideLaunchSpeed = gKongChargeLaunchSpeeds[gCurrentCharacterIndex];
    }
}

void playerStateEnterState15ThrowHeldActor(void) {
    Actor *target;

    playerClearCarriedItemState();
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerState->gunDrawn = 0;
    playerKongHolsterGun(gCurrentActor);
    sfxStopSlotSound(gCurrentActor, 0);
    sfxStopSlotSound(gCurrentActor, 1);
    actorScriptStartByIndex(gActivePlayerActor, 0x21);
    target = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
    if (target != NULL) {
        gActivePlayerState->hitActorType = target->actorType;
        gActivePlayerState->hitActorId = actorListFindIdByActor(gPlayerSlots[gCurrentPlayerIndex].queuedActor);
    } else {
        gActivePlayerState->hitActorType = 0;
        gActivePlayerState->hitActorId = -1;
    }
    if (gCurrentActor->contactFlags & 4) {
        gActivePlayerActor->state = 0x43;
        gActivePlayerActor->subState = 0;
        return;
    }
    gActivePlayerActor->state = 0x42;
    gActivePlayerActor->subState = 0;
}

extern s16 gKongDamageInvulnFrames[];

#define ABSF(x) ((x) > 0.0f ? (x) : -(x))

void playerStateDamageTargetCheck(void) {
    Actor *hitter;
    Actor *target;
    f32 speed;

    target = gActivePlayerState->actor;
    if (target->speedXZ >= 0.0f) {
        behaviourAddSlotQueueValueB(3);
    }
    hitter = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
    target = gActivePlayerState->actor;
    if (hitter != NULL) {
        if (hitter->speedXZ != 0.0f) {
            speed = ABSF(hitter->speedXZ);
            target->speedXZ = 2.0 * speed;
        } else {
            speed = ABSF(target->speedXZ);
            target->speedXZ = speed < 50.0f ? -50.0f : -ABSF(target->speedXZ);
        }
    } else {
        speed = ABSF(target->speedXZ);
        target->speedXZ = speed < 50.0f ? -50.0f : -ABSF(target->speedXZ);
    }
    actorScriptStart(gActivePlayerState->actor, 0x292);
    if (gActivePlayerActor->state != 9) {
        actorScriptStartByIndex(gActivePlayerActor, 0x83);
    }
}

void playerStateDamageCheck4(void) {
    if (gActivePlayerState->surfaceTimer == 0) {
        playerClearCarriedItemState();
        behaviourAddSlotQueueValueB(3);
        switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
        case 3:
            sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0xB9, 0xFF, 0x7F, 0x14);
            break;
        case 2:
            sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0xD2, 0xFF, 0x7F, 0x14);
            break;
        }
        gActivePlayerState->surfaceTimer = gKongDamageInvulnFrames[gCurrentCharacterIndex];
        gActivePlayerActor->speedXZ = gActivePlayerActor->speedXZ / 2;
    }
}

void playerStatePlayAnimationByDamageType(u16 damageType) {
    u16 flag;
    s16 camPath;

    switch (damageType) {
    case 0x12:
        flag = 0x16D;
        camPath = 0x23;
        break;
    case 0x81:
        flag = 0x16E;
        camPath = 0x24;
        break;
    }
    if (flagGet(flag, 0) == 0) {
        if (damageType == 0x81) {
            gActivePlayerActor->speedXZ = 0.0f;
        }
        camStartPath(NULL, camPath, 5);
        flagSet(flag, 1, 0);
    }
}

void playerStateApplyAttackerDamage(Actor *attacker) {
    s16 id;
    u16 type;
    s32 flag;

    type = attacker->actorType;
    id = actorListFindIdByActor(attacker);
    switch (gCurrentMap) {
    case 26:
        if (id == 0x11) {
            return;
        }
        break;
    case 48:
        if (id == 0x17) {
            return;
        }
        break;
    }
    switch (type) {
    case 0x19:
        flag = 0x169;
        break;
    case 0x28:
        flag = 0x168;
        break;
    case 0x39:
        flag = 0x16B;
        break;
    case 0x38:
        flag = 0x16A;
        break;
    default:
        return;
    }
    if (flagGet(flag, 0) == 0) {
        camStartPath(NULL, 0x16, 5);
        flagSet(flag, 1, 0);
    }
}

void playerStateSetLaunchVelocity(void) {
    u8 drawGun;
    s32 sizeMode;
    s32 kongId;

    drawGun = 0;
    gActivePlayerActor->speedXZ = gActivePlayerState->launchSpeedXZ;
    gActivePlayerActor->moveYaw = gActivePlayerState->launchYaw;
    gActivePlayerActor->yaw = gActivePlayerState->launchYaw;
    gActivePlayerActor->speedY = gActivePlayerState->launchSpeedY;
    scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
    if (gPlayerSlots[gCurrentPlayerIndex].queuedActor == NULL) {
        gActivePlayerActor->state = 0x44;
        gActivePlayerActor->subState = 0;
        actorScriptStartByIndex(gActivePlayerActor, 0x22);
        gActivePlayerState->gravityDelay = 0x14;
        playerSetBaseGravity();
    } else {
        switch (gPlayerSlots[gCurrentPlayerIndex].queuedActor->actorType) {
        case 0x17:
        case 0xA7:
            gActivePlayerActor->state = 0x45;
            gActivePlayerActor->subState = 0;
            actorScriptStartByIndex(gActivePlayerActor, 0x22);
            gActivePlayerState->gravityDelay = 0x14;
            playerSetBaseGravity();
            break;
        case 0x11:
            gActivePlayerActor->state = 0x44;
            gActivePlayerActor->subState = 0;
            actorScriptStartByIndex(gActivePlayerActor, 0x22);
            gActivePlayerState->gravityDelay = 0x14;
            playerSetBaseGravity();
            break;
        case 0x1C:
        case 0x6B:
        case 0x86:
            if (actorFindByType(0x25) != NULL) {
                gActivePlayerActor->state = 0x63;
                gActivePlayerActor->subState = 0;
                actorScriptStart(gActivePlayerActor, 0x7D);
                gActivePlayerActor->speedXZ = 0.0f;
                gActivePlayerState->targetSpeed = 300.0f;
                drawGun = 1;
                slotQueueUpdate(5, 1, 0);
                break;
            }
            /* No actor of type 0x25: fall through to the plain fall. */
        case 0x62:
        case 0x88:
        case 0x89:
            actorSetInteractionTimer(gActivePlayerActor);
            playerEnterFall(gCurrentActor);
            playerSetBaseGravity();
            break;
        case 0x19:
        case 0x28:
        case 0x60:
            if (gPlayerSlots[gCurrentPlayerIndex].queuedActor->actorType == 0x28) {
                sizeMode = 0;
            } else {
                sizeMode = 2;
            }
            playerSetSizeMode(gActivePlayerActor, sizeMode);
            if (gActivePlayerActor->actorType == 6) {
                gActivePlayerActor->flags &= ~0x8000;
            } else {
                gActivePlayerActor->flags |= 0x8000;
            }
            playerResumeLocomotion(gActivePlayerActor);
            break;
        case 0x39:
            gActivePlayerState->stateFlags |= 0x10;
            gActivePlayerActor->flags &= ~0x8000;
            gActivePlayerActor->alpha = 0x7F;
            effectSpawnActorOrbitParticles(gActivePlayerActor);
            playerEnterFall(gCurrentActor);
            playerSetBaseGravity();
            break;
        case 0x38:
            gActivePlayerState->stateFlags |= 0x20;
            gActivePlayerActor->state = 0x41;
            gActivePlayerActor->subState = 0;
            actorScriptStart(gActivePlayerActor, 0x156);
            gActivePlayerActor->speedXZ = 0.0f;
            gActivePlayerState->gravityDelay = 4;
            playerSetTerminalVelocity5B0();
            break;
        case 0x31:
            gActivePlayerActor->state = 0x63;
            gActivePlayerActor->subState = 0;
            actorScriptStart(gActivePlayerActor, 0x7D);
            gActivePlayerActor->speedXZ = 0.0f;
            gActivePlayerState->targetSpeed = 300.0f;
            break;
        case 0x12:
        case 0x81:
            gActivePlayerState->savedActorType = gActivePlayerActor->actorType;
            if (gPlayerSlots[gCurrentPlayerIndex].queuedActor->actorType == 0x12) {
                playerSetKongByActorType(8);
                gActivePlayerActor->state = 0xC;
                gActivePlayerActor->subState = 0;
                actorScriptStartByIndex(gActivePlayerActor, 9);
                gActivePlayerActor->speedXZ = 0.0f;
            } else {
                playerSetKongByActorType(9);
                if (gActivePlayerActor->waterY < gActivePlayerActor->y) {
                    gActivePlayerActor->state = 0x82;
                    gActivePlayerActor->subState = 0;
                } else {
                    gActivePlayerActor->state = 0x7F;
                    gActivePlayerActor->subState = 0;
                }
                actorScriptStart(gActivePlayerActor, 0x317);
                gActivePlayerActor->speedXZ = 100.0f;
            }
            gActivePlayerState->gravityDelay = 4;
            playerSetTerminalVelocity5B0();
            playerStatePlayAnimationByDamageType(gPlayerSlots[gCurrentPlayerIndex].queuedActor->actorType);
            break;
        case 0x84:
            kongId = playerGetResolvedKongId(gCurrentPlayerIndex);
            if (kongId != gPlayerCharacterId[gCurrentPlayerIndex]) {
                playerSetKongByActorType(kongId + 2);
            }
            actorSpawnChildActor(gActivePlayerActor);
            break;
        }
    }
    if (((gPlayerSlots[gCurrentPlayerIndex].queuedActor != NULL) && (gPlayerSlots[gCurrentPlayerIndex].queuedActor->actorType == 0x31)) || (drawGun != 0)) {
        if (gCurrentKongInventory->weaponFlags & 1) {
            if (gActivePlayerState->gunDrawn != 0) {
                gActivePlayerState->stateFlags2 |= 4;
            } else {
                gActivePlayerState->stateFlags2 &= ~4;
            }
            gActivePlayerState->gunDrawn = 1;
            playerKongDrawGun(gActivePlayerActor);
        }
    } else {
        playerKongHolsterGun(gCurrentActor);
    }
    if (gPlayerSlots[gCurrentPlayerIndex].queuedActor != NULL) {
        playerStateApplyAttackerDamage(gPlayerSlots[gCurrentPlayerIndex].queuedActor);
    }
    if ((gActivePlayerActor->contactFlags & 4) && (gPlayerSlots[gCurrentPlayerIndex].queuedActor->actorType != 0x81)) {
        gActivePlayerState->subTimer = gKongDiveAngles[gCurrentCharacterIndex];
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        gActivePlayerState->actionTimer = gKongDiveFrames[gCurrentCharacterIndex] * 0.5;
        gCurrentActor->state = 0x4F;
        gCurrentActor->subState = 1;
        if (gCurrentActor->speedY > 0.0f) {
            gCurrentActor->speedY = 0.0f;
        }
        actorScriptStartByIndex(gCurrentActor, 0x36);
        controllerAnimSetStateRemap(gCurrentActor, 0x31, 0.0f, 8.0f);
        scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
    }
}

void playerRevertToSavedKong(void) {
    playerSetKongByActorType(gActivePlayerState->savedActorType);
    playerResumeLocomotion(gActivePlayerActor);
}

void playerStateThrowHeldActorAndResume(void) {
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x55;
    gActivePlayerActor->subState = 0;
}

void playerStateThrowHeldActorWithScript(void) {
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x56;
    gActivePlayerActor->subState = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x87);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->targetSpeed = 0.0f;
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
}

void playerStateEnterDamageTake(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        playerClearCarriedItemState();
        if (playerAddHealthDelta(gCurrentPlayerIndex, -1) != 0) {
            if (gActivePlayerActor->contactFlags & 4) {
                actorScriptStartByIndex(gActivePlayerActor, 0x29);
            } else {
                actorScriptStartByIndex(gActivePlayerActor, 0x27);
            }
            gActivePlayerActor->state = 0x36;
            gActivePlayerActor->subState = 0;
        }
        gActivePlayerState->surfaceTimer = gKongDamageInvulnFrames[gCurrentCharacterIndex];
    }
}

void playerStateAttachHeldActorToPlayer(void) {
    Actor *held = gActivePlayerState->heldActor;

    if (held != NULL) {
        actorAppendLaunch(gCurrentActor, held, gActivePlayerActor->yaw, gCurrentActor->speedY,
                                gCurrentActor->speedXZ);
        gActivePlayerState->heldActor = NULL;
        gActivePlayerState->queuedHeldActor = NULL;
    }
    playerClearCarriedItemState();
    actorScriptStartByIndex(gCurrentActor, 0x1C);
    gActivePlayerActor->state = 0x20;
    gActivePlayerActor->subState = 0;
}

void playerStateEnterSlideRecover(void) {
    playerClearCarriedItemState();
    actorScriptStartByIndex(gCurrentActor, 0x1C);
    gActivePlayerActor->state = 0x21;
    gActivePlayerActor->subState = 0;
}

void playerStateDamageSelector(void) {
    s32 shake = 1;
    s8 healthDelta;
    Actor *target;

    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        healthDelta = -1;
        playerClearCarriedItemState();
        target = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
        if ((target != NULL) && (target->actorType == 0x123)) {
            healthDelta = -2;
        }
        if (playerAddHealthDelta(gCurrentPlayerIndex, healthDelta) != 0) {
            shake = 0;
            if (gActivePlayerActor->contactFlags & 4) {
                actorScriptStartByIndex(gActivePlayerActor, 0x29);
            } else {
                actorScriptStartByIndex(gActivePlayerActor, 0x27);
            }
            gActivePlayerActor->state = 0x36;
            gActivePlayerActor->subState = 0;
        } else {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0);
            actorScriptStartByIndex(gCurrentActor, 0x1E);
            gCurrentActor->state = 0x20;
            gCurrentActor->subState = 1;
        }
    }
    if ((gActivePlayerState->surfaceTimer == 0) && (gPlayerCount < 2)) {
        gActivePlayerState->surfaceTimer = gKongDamageInvulnFrames[gCurrentCharacterIndex];
    }
    if (shake != 0) {
        camStartShake(gActivePlayerState->camActor, 0x14, 0x14);
    }
}

void playerTakeFallDamage(void) {
    s32 shake = 1;

    playerClearCarriedItemState();
    if ((playerCanTakeHit(gActivePlayerActor) != 0) && (playerAddHealthDelta(gCurrentPlayerIndex, -1) != 0)) {
        shake = 0;
        if (gActivePlayerActor->contactFlags & 4) {
            actorScriptStartByIndex(gActivePlayerActor, 0x29);
        } else {
            actorScriptStartByIndex(gActivePlayerActor, 0x27);
        }
        gActivePlayerActor->state = 0x36;
        gActivePlayerActor->subState = 0;
    } else {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0);
        actorScriptStartByIndex(gCurrentActor, 0x1E);
        gCurrentActor->state = 0x20;
        gCurrentActor->subState = 1;
    }
    if ((gActivePlayerState->surfaceTimer == 0) && (gPlayerCount < 2)) {
        gActivePlayerState->surfaceTimer = gKongDamageInvulnFrames[gCurrentCharacterIndex];
    }
    if (shake != 0) {
        camStartShake(gActivePlayerState->camActor, 0x14, 0x14);
    }
}

void playerStateStopSfxAndClearCarried(void) {
    playerClearCarriedItemState();
    sfxStopChannel(0x6B, 0);
    gCurrentActor->yawSpeed = gPlayerSlots[gCurrentPlayerIndex].queuedParam0;
    actorScriptStartByIndex(gCurrentActor, 0x1D);
    gActivePlayerActor->state = 0x6F;
    gActivePlayerActor->subState = 0;
}

void playerStateEnterFallAndSetGravity(void) {
    playerSetBaseGravity();
    playerEnterFall(gCurrentActor);
}

void playerStateSwimTreadWithScript(void) {
    playerThrowHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x32);
    gActivePlayerActor->state = 0x52;
    gActivePlayerActor->subState = 0;
}

void playerStateEnterFadeWarp(void) {
    playerThrowHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x86);
    gActivePlayerActor->state = 0x53;
    gActivePlayerActor->subState = 0;
}

void playerResumeLocomotionAndThrow(void) {
    playerThrowHeldActor(gActivePlayerActor);
    playerResumeLocomotion(gActivePlayerActor);
    gActivePlayerActor->state = 0x54;
    gActivePlayerActor->subState = 0;
}

void playerStateDamageCheck(void) {
    RaceParticipant *participant;

    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        if ((gCurrentMap != 0x52) && (gCurrentMap != 0xE)) {
            playerTakeDamage(0x40);
            return;
        }
        participant = gActivePlayerState->actor->customState;
        participant->eliminated = 1;
    }
}

void playerTakeQueuedDamage(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        playerTakeDamage(gPlayerStateCallbackParams.param0);
        playerSetBaseGravity();
    }
}

void playerStateCutsceneDamageCheck(void) {
    if (gGlobalCutsceneFlags & 2) {
        playerKongClearFlagsByActorType(gActivePlayerActor);
        sfxStopChannel(0xC, 0);
    }
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        if ((gGlobalCutsceneFlags & 2) && (camIsCutsceneActive() != 0)) {
            return;
        }
        playerTakeDamage(1);
        playerSetBaseGravity();
    }
}

void playerStateDamageCheck5(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        gActivePlayerState->damageSource = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
        if (gPlayerSlots[gCurrentPlayerIndex].queuedActor == NULL) {
            actorSpawnAttachment(gActivePlayerActor, 3.2f);
        }
        playerTakeDamage(1);
        playerSetBaseGravity();
        actorAppendActiveCallback8();
    }
}

void playerStateTakeDamageAndDrop(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        gActivePlayerState->damageSource = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
        playerTakeDamage(1);
        playerSetBaseGravity();
    }
}

void playerStateDamageCheck2(void) {
    if (playerCanTakeHit(gCurrentActor) != 0) {
        gActivePlayerState->damageSource = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
        gCurrentActor->collisionMode = 1;
        gCurrentActor->state = 0x34;
        gCurrentActor->subState = 0;
        actorScriptStart(gCurrentActor, 0);
        playerAddHealthDelta(gCurrentPlayerIndex, -0x40);
        playerSetBaseGravity();
        scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
    }
}

void playerStateDamageCheck3(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        s32 damage = 1;

        gActivePlayerState->damageSource = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
        if ((gActivePlayerState->damageSource != NULL) && (gActivePlayerState->damageSource->actorType == 0x123)) {
            damage = 2;
        }
        playerTakeDamage(damage);
    }
}

extern f32 gKongSwimStrokeSpeeds[], gKongQueuedDamageLaunchSpeedY[], gKongSwimTurnSpeeds[], gKongDeathLaunchSpeedY[];
extern s16 D_807530D0[], gKongMinecartHitInvulnFrames[], gKongTakeHitInvulnFrames[], gKongNormalSwimEnterDepths[];
extern f32 gKongSwimPaddleSpeeds[], gKongDamageAccelY[], gKongDamageLaunchSpeedY[], gKongSwimSpeeds[], gKongSwimEnterDepths[];

void playerTakeDamage(s16 damage) {
    s16 yaw;
    f32 depth;
    f32 deepThreshold;
    u8 isDeep;
    s32 isDead;
    s8 healthDelta;

    isDeep = 0;
    if (gActivePlayerActor->contactFlags & 4) {
        depth = gCurrentActor->waterY - gCurrentActor->floorY;
        if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
            deepThreshold = gKongNormalSwimEnterDepths[gCurrentCharacterIndex];
        } else {
            deepThreshold = gKongSwimEnterDepths[gCurrentCharacterIndex];
        }
        isDeep = deepThreshold < depth;
    }
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        sfxStopChannel(0x6B, 0);
        gActivePlayerActor->flags |= 4;
        gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
        gActivePlayerActor->contactFlags &= ~0x40;
        slotQueueCancel(6, 1);
        if (gActivePlayerState->surfaceTimer == 0) {
            playerClearCarriedItemState();
            playerDropHeldActor(gActivePlayerActor);
            if ((gActivePlayerState->actor != NULL) &&
                ((gActivePlayerState->actor->actorType == 0x1D) || (gActivePlayerState->actor->actorType == 0x57) ||
                 (gActivePlayerState->actor->actorType == 0x50) || (gActivePlayerState->actor->actorType == 0x3E))) {
                gActivePlayerState->surfaceTimer = gKongMinecartHitInvulnFrames[gCurrentCharacterIndex];
                actorScriptStart(gActivePlayerState->actor, 0x292);
                sfxPlayScriptActorSoundForPlayer(gActivePlayerActor, 0x11, 0);
                if (gActivePlayerState->actor->actorType != 0x57) {
                    behaviourAddSlotQueueValueB(3);
                }
            } else {
                isDead = 0;
                if (gPlayerCount >= 2) {
                    if (playerHitSourceIsStale(gPlayerSlots[gCurrentPlayerIndex].queuedState) == 0) {
                        return;
                    }
                    playerRecordHitSource(gActivePlayerActor, gPlayerSlots[gCurrentPlayerIndex].queuedActor,
                                  gPlayerSlots[gCurrentPlayerIndex].queuedState);
                    if ((mpIsMatchType(0) != 0) && (gActivePlayerActor->state == 0x3C) &&
                        (gPlayerSlots[gCurrentPlayerIndex].queuedState != 0xE)) {
                        gActivePlayerState->effectTimer -= damage * 0xA;
                        if (gActivePlayerState->effectTimer < 0) {
                            gActivePlayerState->effectTimer = 0;
                        }
                        if (gActivePlayerState->effectTimer != 0) {
                            return;
                        }
                    }
                }
                if (((gPlayerCount != 1) || (gPlayerSlots[gCurrentPlayerIndex].queuedState != 0x2B)) &&
                    (menuIsTransitionType3Or4() == 0)) {
                    healthDelta = playerResolveHitDamage(-damage, gActivePlayerActor);
                    if (healthDelta < 0) {
                        isDead = playerAddHealthDelta(gCurrentPlayerIndex, healthDelta);
                    }
                }
                if (isDead != 0) {
                    if (gActivePlayerActor->contactFlags & 4) {
                        actorScriptStartByIndex(gActivePlayerActor, 0x29);
                    } else {
                        actorScriptStartByIndex(gActivePlayerActor, 0x27);
                    }
                    gActivePlayerActor->state = 0x36;
                    gActivePlayerActor->subState = 0;
                    if (mpIsMatchType(0) != 0) {
                        gActivePlayerActor->speedY = gKongDamageLaunchSpeedY[gCurrentCharacterIndex] * 5.0f;
                        gActivePlayerActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex] * 5.0f;
                        gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex] * 5.0f;
                        gActivePlayerActor->accelY = gKongDamageAccelY[gCurrentCharacterIndex];
                    }
                } else {
                    switch (gPlayerSlots[gCurrentPlayerIndex].queuedState) {
                    case 0xE:
                        gActivePlayerActor->state = 0x66;
                        gActivePlayerActor->subState = 0;
                        actorScriptStartByIndex(gActivePlayerActor, 0x26);
                        gActivePlayerActor->accelY = gKongDamageAccelY[gCurrentCharacterIndex];
                        break;
                    case 0x31:
                        if (isDeep != 0) {
                            gActivePlayerActor->state = 0x37;
                            gActivePlayerActor->subState = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x28);
                        } else {
                            gActivePlayerActor->state = 0x34;
                            gActivePlayerActor->subState = 0;
                            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0);
                            actorScriptStartByIndex(gCurrentActor, 0x1E);
                        }
                        break;
                    case 0x2B:
                        if (isDeep != 0) {
                            gActivePlayerActor->state = 0x37;
                            gActivePlayerActor->subState = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x28);
                        } else {
                            gActivePlayerActor->state = 0x32;
                            gActivePlayerActor->subState = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x25);
                        }
                        break;
                    case 0x32:
                        if (isDeep != 0) {
                            gActivePlayerActor->state = 0x37;
                            gActivePlayerActor->subState = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x28);
                        } else {
                            gActivePlayerActor->state = 0x35;
                            gActivePlayerActor->subState = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x26);
                        }
                        break;
                    case 0x37:
                        gActivePlayerActor->state = 0x33;
                        gActivePlayerActor->subState = 0;
                        actorScriptStart(gActivePlayerActor, 4);
                        break;
                    case 0x2E:
                    case 0x2F:
                        if (isDeep != 0) {
                            if (gCurrentMap == 0x6F) {
                                gActivePlayerActor->state = 0x38;
                                gActivePlayerActor->subState = 0;
                                actorScriptStart(gActivePlayerActor, 0x3B5);
                                actorScriptStart(gActivePlayerState->actor, 0x3BB);
                                gActivePlayerState->rideSpin = (gFrameCounter & 1) ? -0xFA : 0xFA;
                            } else {
                                gActivePlayerActor->state = 0x37;
                                gActivePlayerActor->subState = 0;
                                actorScriptStartByIndex(gActivePlayerActor, 0x28);
                            }
                        } else if (gActivePlayerActor->state != 0x63) {
                            gActivePlayerActor->state = 0x31;
                            gActivePlayerActor->subState = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x24);
                        } else {
                            actorScriptStart(gActivePlayerActor, 0x81);
                        }
                        break;
                    }
                }
                if (gPlayerSlots[gCurrentPlayerIndex].queuedActor != NULL) {
                    yaw = mathAngleBetweenPoints2D(gActivePlayerActor->x, gActivePlayerActor->z,
                                                      gPlayerSlots[gCurrentPlayerIndex].queuedActor->x,
                                                      gPlayerSlots[gCurrentPlayerIndex].queuedActor->z);
                } else {
                    yaw = (gActivePlayerActor->moveYaw + 0x800) & 0xFFF;
                }
                gActivePlayerActor->moveYaw = yaw;
                switch (gPlayerSlots[gCurrentPlayerIndex].queuedState) {
                case 0x2E:
                case 0x2F:
                    if (gActivePlayerActor->contactFlags & 4) {
                        gActivePlayerActor->speedXZ = gKongSwimTurnSpeeds[gCurrentCharacterIndex];
                        gActivePlayerState->surfaceTimer = gKongDamageInvulnFrames[gCurrentCharacterIndex];
                    } else {
                        if (gPlayerCount >= 2) {
                            playerSetRecentAttacker(actorResolveKillCreditOwner(gPlayerSlots[gCurrentPlayerIndex].queuedActor),
                                          gActivePlayerState);
                        }
                        gActivePlayerActor->speedY = gKongQueuedDamageLaunchSpeedY[gCurrentCharacterIndex];
                        gActivePlayerActor->speedXZ = gKongSwimTurnSpeeds[gCurrentCharacterIndex];
                        gActivePlayerState->surfaceTimer = gKongDamageInvulnFrames[gCurrentCharacterIndex];
                        gActivePlayerActor->accelY = gKongSwimStrokeSpeeds[gCurrentCharacterIndex];
                    }
                    break;
                case 0x32:
                    if (gPlayerCount >= 2) {
                        playerSetRecentAttacker(actorResolveKillCreditOwner(gPlayerSlots[gCurrentPlayerIndex].queuedActor),
                                      gActivePlayerState);
                    }
                    gActivePlayerState->surfaceTimer = D_807530D0[gCurrentCharacterIndex];
                    gActivePlayerActor->speedXZ = gKongSwimPaddleSpeeds[gCurrentCharacterIndex];
                    gActivePlayerActor->accelY = gKongDamageAccelY[gCurrentCharacterIndex];
                    break;
                case 0xE:
                    if (gPlayerCount >= 2) {
                        playerSetRecentAttacker(actorResolveKillCreditOwner(gPlayerSlots[gCurrentPlayerIndex].queuedActor),
                                      gActivePlayerState);
                    }
                    if (mpIsMatchType(0) != 0) {
                        gActivePlayerActor->speedY = gKongDamageLaunchSpeedY[gCurrentCharacterIndex] * 10.0f;
                        gActivePlayerActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex] * 10.0f;
                        gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex] * 10.0f;
                        gActivePlayerState->surfaceTimer = 0xA;
                        gActivePlayerActor->accelY = gKongDamageAccelY[gCurrentCharacterIndex];
                    } else {
                        gActivePlayerActor->speedY = gKongDamageLaunchSpeedY[gCurrentCharacterIndex];
                        gActivePlayerActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex];
                        if (damage != 0) {
                            gActivePlayerState->surfaceTimer = gKongTakeHitInvulnFrames[gCurrentCharacterIndex];
                        }
                        gActivePlayerActor->accelY = gKongDamageAccelY[gCurrentCharacterIndex];
                    }
                    break;
                case 0x37:
                    gActivePlayerState->surfaceTimer = gKongDamageInvulnFrames[gCurrentCharacterIndex];
                    break;
                case 0x2B: // ORIG: target's jump table starts at 0x2B (addiu t6,v0,-43; sltiu at,t6,13 at 0x4360), its .rodata+0x210 entry is the switch exit 0x46bc
                    break;
                }
                if ((gPlayerCount >= 2) && (isDead == 0)) {
                    gActivePlayerState->surfaceTimer = 0x3C;
                }
                if (gActivePlayerActor->state == 0x36) {
                    if (gActivePlayerActor->contactFlags & 4) {
                        gActivePlayerActor->speedY = gKongDeathLaunchSpeedY[gCurrentCharacterIndex] / 4;
                    } else {
                        gActivePlayerActor->speedY = gKongDeathLaunchSpeedY[gCurrentCharacterIndex];
                    }
                }
                gActivePlayerState->gravityDelay = 0;
            }
        }
    }
}

void playerStateEnterDamageReaction(void) {
    RaceParticipant *participant;

    if ((gActivePlayerActor->state == 0x36) || (gActivePlayerActor->state == 0x39) ||
        (gActivePlayerActor->state == 0x3A) || (gActivePlayerActor->state == 0x71) ||
        (gActivePlayerActor->state == 0x73) || (gActivePlayerActor->state == 0x74)) {
        return;
    }
    playerClearCarriedItemState();
    gActivePlayerActor->flags &= ~0x8000;
    actorScriptStartByIndex(gActivePlayerActor, 0x27);
    gActivePlayerActor->state = 0x39;
    gActivePlayerActor->subState = 0;
    gActivePlayerState->stateTimer = 0x19;
    camSnapToTargetHeight(gActivePlayerState->camActor);
    if ((gCurrentMap != 0x52) && (gCurrentMap != 0xE)) {
        playerAddHealthDelta(gCurrentPlayerIndex, -0x40);
    } else {
        participant = gActivePlayerState->actor->customState;
        participant->eliminated = 1;
    }
}

void playerStateEnterDamageReaction2(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        if (gActivePlayerActor->state != 0x3B) {
            if (camIsCutsceneActive() == 0) {
                playerClearCarriedItemState();
                playerDropHeldActor(gActivePlayerActor);
                gActivePlayerActor->collisionMode = 1;
                actorScriptStartByIndex(gActivePlayerActor, 0x2A);
                gActivePlayerActor->state = 0x3B;
                gActivePlayerActor->subState = 0;
                playerAddHealthDelta(gCurrentPlayerIndex, -0x40);
                camStartPath(gActivePlayerActor, 0xB, 0x85);
                gActivePlayerActor->speedXZ = 0.0f;
            }
        }
    }
}

void playerStateSetCartDamage(void) {
    gActivePlayerState->cartDamage = 1;
}

void playerStateEnterBarrelBlast(void) {
    gCurrentActor->state = 0x6A;
    gCurrentActor->subState = 0;
}

typedef struct EfKongScriptIds {
    u16 values[5];
} EfKongScriptIds;

extern const EfKongScriptIds gKongNewMoveScriptIds;

void playerStateSpawnParticles(void) {
    EfKongScriptIds scriptIds;
    s32 pad;
    f32 scale;

    scriptIds = gKongNewMoveScriptIds;
    scale = gActivePlayerActor->sub4->scaleX;
    actorSpawn(0x140, 0xB9);
    if (gActivePlayerActor->actorType == 2) {
        scale *= 1.25;
    }
    actorCopyPoseAndScale(gSpawnedActor, gActivePlayerActor, scale);
    actorScriptStart(gSpawnedActor, scriptIds.values[gPlayerCharacterId[gActivePlayerState->playerIndex]]);
    gSpawnedActor->flags |= 0x40000000;
    actorScriptStartByIndex(gActivePlayerActor, 0x88);
    gCurrentActor->state = 0x79;
    gCurrentActor->subState = 0;
}

void playerStateStopChannelAndClearCarried(void) {
    sfxStopChannel(0x6B, 0);
    playerClearCarriedItemState();
    playerCheckAndResetCarriedActor(gActivePlayerActor);
    playerDropHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x5B);
    gActivePlayerActor->state = 0x70;
    gActivePlayerActor->subState = 0;
    if (gActivePlayerActor->hasArcBounds != 0) {
        gActivePlayerActor->yaw = mathAngleArcMidpoint(gActivePlayerActor->arcYawMin, gActivePlayerActor->arcYawMax);
    } else {
        gActivePlayerActor->yaw = mathAngleBetweenPoints2D(
            gPlayerSlots[gCurrentPlayerIndex].camX,
            gPlayerSlots[gCurrentPlayerIndex].camZ,
            gActivePlayerActor->x,
            gActivePlayerActor->z);
    }
    camStartPathNearWall(gActivePlayerActor, 0x15, 0x1F, 5);
}

void playerStateDropHeldActor(void) {
    playerClearCarriedItemState();
    playerDropHeldActor(gActivePlayerActor);
    playerCheckAndResetCarriedActor(gActivePlayerActor);
    if (gActivePlayerActor->state != 0x6D) {
        actorScriptStartByIndex(gActivePlayerActor, 0x5B);
        gActivePlayerActor->state = 0x71;
        gActivePlayerActor->subState = 0;
    }
    gActivePlayerActor->yaw = mathAngleBetweenPoints2D(
        gPlayerSlots[gCurrentPlayerIndex].camX,
        gPlayerSlots[gCurrentPlayerIndex].camZ,
        gActivePlayerActor->x,
        gActivePlayerActor->z);
    if (gCurrentMap == 8) {
        camStartPath(gActivePlayerActor, 2, 1);
        gActivePlayerActor->subState = 0xFF;
        gActivePlayerState->stateCountdown = 0xFFFF;
    } else {
        camStartPath(gActivePlayerActor, 5, 5);
        gActivePlayerState->stateCountdown = 100;
    }
}

void playerStateDropHeldActorAndScript(void) {
    playerClearCarriedItemState();
    playerDropHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x5B);
    gActivePlayerActor->state = 0x72;
    gActivePlayerActor->subState = 0;
    gActivePlayerActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ,
                                                  gActivePlayerActor->x, gActivePlayerActor->z);
    camStartPath(gActivePlayerActor, 0x15, 5);
}

void playerStateDropHeldActorSetKong(void) {
    playerSetKongByActorType(gActivePlayerState->savedActorType);
    playerDropHeldActor(gActivePlayerActor);
    playerClearCarriedItemState();
    gActivePlayerActor->collisionMode = 1;
    if (gActivePlayerActor->state != 0x7D) {
        if (gActivePlayerActor->contactFlags & 4) {
            actorScriptStartByIndex(gActivePlayerActor, 0x34);
        } else if (!(gActivePlayerActor->contactFlags & 2)) {
            actorScriptStartByIndex(gActivePlayerActor, 0x5D);
        }
    }
    gActivePlayerActor->state = 0x73;
    gActivePlayerActor->subState = 0;
    if ((gActivePlayerState->actor == NULL) || (gActivePlayerState->actor->actorType != 0x57)) {
        gActivePlayerActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ,
                                                      gActivePlayerActor->x, gActivePlayerActor->z);
    }
    gActivePlayerActor->speedY = 0.0f;
    gActivePlayerState->stateCountdown = 0x5A;
    playerSetBaseGravity();
}

void playerStateDropHeldActorSetKong2(void) {
    playerSetKongByActorType(gActivePlayerState->savedActorType);
    playerDropHeldActor(gActivePlayerActor);
    playerClearCarriedItemState();
    gActivePlayerActor->collisionMode = 1;
    if (gActivePlayerActor->state != 0x7D) {
        if (gActivePlayerActor->contactFlags & 4) {
            actorScriptStartByIndex(gActivePlayerActor, 0x34);
        } else if (!(gActivePlayerActor->contactFlags & 2)) {
            actorScriptStartByIndex(gActivePlayerActor, 0x5C);
        }
    }
    gActivePlayerActor->state = 0x74;
    gActivePlayerActor->subState = 0;
    if ((gActivePlayerState->actor == NULL) || (gActivePlayerState->actor->actorType != 0x57)) {
        gActivePlayerActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ,
                                                      gActivePlayerActor->x, gActivePlayerActor->z);
    }
    gActivePlayerActor->speedY = 0.0f;
    gActivePlayerState->stateCountdown = 0x5A;
    playerSetBaseGravity();
}

void playerStateNoop1(void) {
}

void playerStateNoop2(void) {
}

void playerStateEnterMpEliminated(void) {
    gCurrentActor->state = 0x84;
    gCurrentActor->subState = 0;
    actorScriptStart(gCurrentActor, 0);
}

void playerStateClearCarriedSetFlags(void) {
    playerClearCarriedItemState();
    gActivePlayerState->stateFlags &= ~0x20;
    gActivePlayerActor->interactionType = 2;
    gActivePlayerState->moveTier = -1;
    gActivePlayerState->decelRate = gKongDecelRate[gCurrentCharacterIndex];
    gActivePlayerActor->state = 0x7A;
    gActivePlayerActor->subState = 0;
}

void playerStateLockMovementAndResume(void) {
    gActivePlayerState->stateFlags2 |= 8;
    playerResumeLocomotion(gActivePlayerActor);
}

void playerStateEnterCutscenePause(void) {
    playerClearCarriedItemState();
    gActivePlayerState->stateFlags &= ~0x20;
    gActivePlayerActor->state = 0x7B;
    gActivePlayerActor->subState = 0;
}

void playerStateClearCarriedAndCallF00BC(void) {
    playerClearCarriedItemState();
    playerStateClearCarriedSetFlags();
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
}

void playerStateEnterClimbTree(void) {
    actorScriptStartByIndex(gActivePlayerActor, 9);
    gActivePlayerActor->state = 0xC;
    gActivePlayerActor->subState = 0;
}

void playerStateEnterKnockbackState(void) {
    gActivePlayerState->moveTier = -1;
    gActivePlayerState->decelRate = gKongDecelRate[gCurrentCharacterIndex];
    playerSetBaseGravity();
    if (gActivePlayerActor->state != 0x7C) {
        playerClearCarriedItemState();
        gActivePlayerActor->state = 0x7C;
        gActivePlayerActor->subState = 0;
        actorScriptStart(gActivePlayerActor, 0x13);
        actorSpawn(0x117, 0xC5);
        gSpawnedActor->parentActor = gActivePlayerActor;
        actorSetInteractionTimer(gActivePlayerActor);
    }
}

void playerStateEnterPulseForm(void) {
    playerSetBaseGravity();
    gActivePlayerActor->state = 0x7D;
    gActivePlayerActor->subState = 0;
    gActivePlayerActor->flags &= ~4;
    actorSpawn(0x11A, 0x21);
    actorScriptStart(gSpawnedActor, 0x232);
    gSpawnedActor->parentActor = gActivePlayerActor;
}

void playerStateSetFlagsByActorType(void) {
    s32 camPath;

    /* The original leaves camPath unset on the default path (other actor types); camStartPath reads it. */
    switch (gActivePlayerActor->actorType) {
    case 2:
        camPath = 7;
        break;
    case 3:
        camPath = 0;
        break;
    case 4:
        gActivePlayerState->stateFlags |= 0x100;
        camPath = 4;
        break;
    case 5:
        if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
            camPath = 8;
        } else {
            camPath = 0x1F;
        }
        break;
    case 6:
        camPath = 9;
        break;
    default: // ORIG: own default block at +0x16c..+0x190 (gPlayerSlots[gCurrentPlayerIndex] address, 10 insns) before the join +0x194, reached by the bound check beqz at +0x1c; each case keeps its own copy (playerStateSetFlagsByActorType 0x5304)
        break;
    }
    gActivePlayerActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ,
                                                  gActivePlayerActor->x, gActivePlayerActor->z);
    if (gGlobalCutsceneFlags & 2) {
        gActivePlayerState->stateFlags &= ~0x100;
        actorScriptStart(gActivePlayerActor, 0x165);
    } else {
        if (gActivePlayerActor->state != 0x56) {
            camStartPath(gActivePlayerActor, camPath, 5);
        }
        actorScriptStartByIndex(gActivePlayerActor, 0x5A);
    }
    gActivePlayerActor->state = 0x67;
    gActivePlayerActor->subState = 0;
}

void playerStateEnterFairyReward(void) {
    gActivePlayerState->stateFlags2 |= 0x10;
    playerLeaveFairyCamera(gActivePlayerState);
    gActivePlayerActor->state = 0x83;
    gActivePlayerActor->subState = 0;
    gActivePlayerActor->flags |= 0x40000004;
    gActivePlayerActor->flags &= ~1;
}

void playerStateEnterShrinkToSavedPoint(void) {
    gActivePlayerActor->state = 0x87;
    gActivePlayerActor->subState = 0;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->moveTier = -1;
}

void playerStateEnterGrowFromSavedPoint(void) {
    gActivePlayerActor->state = 0x88;
    gActivePlayerActor->subState = 0;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerActor->x = gActivePlayerState->savedX;
    gActivePlayerActor->y = gActivePlayerState->savedY;
    gActivePlayerActor->z = gActivePlayerState->savedZ;
    gActivePlayerActor->pitch = -0x3E6;
    gActivePlayerActor->sub4->scaleX = 0.01f;
    gActivePlayerActor->sub4->scaleY = 0.01f;
    gActivePlayerActor->sub4->scaleZ = 0.01f;
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->moveTier = -1;
}

void playerStateEnterDoubleJumpWithSfx(void) {
    sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0xF3, 0xFF, 0x7F, 0x19);
    gActivePlayerActor->state = 0x19;
    gActivePlayerActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex] * 2.6;
    gActivePlayerState->gravityDelay = 0xC;
    actorScriptStartByIndex(gActivePlayerActor, 0x10);
}

void playerStateEnterSlideBrake(void) {
    if (gActivePlayerActor->floorTriSurface[0] == 0xC) {
        sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0x76, 0x64, 0x7F, 0);
    }
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x15;
    gActivePlayerActor->subState = 0;
    actorScriptStartByIndex(gActivePlayerActor, 6);
    gActivePlayerActor->contactFlags |= 0x20;
    actorScriptExecute(gActivePlayerActor);
}

void playerStateEnterSlideReverse(void) {
    if (gActivePlayerActor->floorTriSurface[0] == 0xC) {
        sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0x76, 0xFF, 0x7F, 0);
    }
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x16;
    gActivePlayerActor->subState = 0;
    actorScriptStartByIndex(gActivePlayerActor, 7);
    gActivePlayerActor->contactFlags |= 0x20;
    actorScriptExecute(gActivePlayerActor);
}

const EfKongScriptIds gKongNewMoveScriptIds = { { 10, 11, 12, 13, 14 } };
