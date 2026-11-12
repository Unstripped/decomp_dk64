#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/117190.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/5E020.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8D3E0.h"
#include "proto/global/936B0.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/E4090.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/FCCD0.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;
extern s32 gCurrentMap;
extern u8 gPlayerCharacterId[];

extern PlayerStruct *gPlayerSlots;

/* Actors with a word past the base Actor (gActivePlayerState->actor in playerStateAdjustUpwardVelocity). */
typedef struct EfExtActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ s32 unk178;
} EfExtActor;

typedef struct EfCallbackParams {
    s32 param0;
    s32 param1;
    s32 param2;
} EfCallbackParams;

extern EfCallbackParams gPlayerStateCallbackParams;

s32 playerStateQueueCallback(s16 priority, void *actor, u8 player) {
    if (gPlayerSlots[player].queuedState < priority) {
        gPlayerSlots[player].queuedState = priority;
        gPlayerSlots[player].queuedActor = actor;
        gPlayerSlots[player].queuedParam0 = gPlayerStateCallbackParams.param0;
        gPlayerSlots[player].queuedParam1 = gPlayerStateCallbackParams.param1;
        gPlayerSlots[player].queuedParam2 = gPlayerStateCallbackParams.param2;
        if (actor != NULL) {
            gPlayerSlots[player].queuedActorId = ((Actor *)actor)->instanceId;
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

extern void (*gPlayerStateCallbacks[])(void);

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
    gCurrentActor->unk155 = 0;
    gCurrentActor->speedY = 100.0f;
    gActivePlayerState->unk50 = 0;
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
    gCurrentActor->unk155 = 0;
    if (gActivePlayerState->unk4E == 0x22) {
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
    gCurrentActor->unk155 = 0;
    actorScriptStart(gActivePlayerActor, 0x3BC);
}

void playerStateInitState5F(void) {
    gCurrentActor->state = 0x5F;
    gCurrentActor->unk155 = 0;
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
    gCurrentActor->unk155 = 0;
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
    gCurrentActor->unk155 = 0;
    actorScriptStartByIndex(gCurrentActor, 0x43);
    gActivePlayerState->unk64 = 0;
    gActivePlayerState->unkC8 = 0x32;
}

void playerStateInitTumble(void) {
    gActivePlayerState->unk4C = -1;
    gActivePlayerState->targetSpeed = 170.0f;
    gCurrentActor->state = 0x3F;
    gCurrentActor->unk155 = 0;
    gActivePlayerState->unk4E = 0;
    actorScriptStart(gCurrentActor, 0x14F);
}

void playerStateTakeDamagePrep(void) {
    Actor *camActor;
    s16 speed;
    s32 param;
    s16 kind;
    CamState *camState;
    u8 type;

    camActor = gActivePlayerState->camActor;
    camState = camActor->customState;
    if (gPlayerSlots && gPlayerSlots) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    type = camState->unkEF;
    speed = camState->unkB8;
    if (type != 0) {
        camState->unkF0 = type;
        speed = 0x80;
    }
    camSaveYaw(gActivePlayerState->camActor);
    camSetZoomLevel(gActivePlayerState->camActor, 0);
    param = gPlayerSlots[gCurrentPlayerIndex].queuedParam0;
    kind = param;
    camState->unkF3 = kind;
    if ((u8)kind == 3) {
        sfxStopSlotSound(gActivePlayerActor, 0);
        sfxPlayOnFreeSlot(0x26, 0x7FFF, 63.0f, 1.0f, 0, 0);
        if (gPlayerSlots[gCurrentPlayerIndex].queuedParam1 != 0) {
            playerKongPlaySoundByState(gActivePlayerActor);
        }
    }
    camState->unkBC = 0x80;
    gActivePlayerState->camActor->distToFloor = speed;
    camState->unkB8 = speed;
    camState->unkB2 = gActivePlayerActor->yaw + 0x800;
    gActivePlayerActor->speedXZ = 0.0f;
    gActivePlayerActor->contactFlags |= 0x2000;
}

void playerStateEnterKnockbackState2(void) {
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 2;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerActor->unk155 = 0xA;
    if (gActivePlayerState->gunDrawn != 0) {
        actorScriptStart(gActivePlayerActor, 0x23);
    } else {
        actorScriptStart(gActivePlayerActor, 0x13);
    }
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->targetSpeed = 0.0f;
}

void playerStateEnterKnockbackState4(void) {
    sfxPlayOnFreeSlot(0x1B9, 0x7FFF, 63.0f, 1.0f, 0xA, 0);
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 4;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerActor->unk155 = 0xA;
    actorScriptStart(gActivePlayerActor, 0x13);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->targetSpeed = 0.0f;
    slotQueueUpdate(6, 1, 0);
}

void playerStateEnterKnockbackState3(void) {
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 3;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerActor->unk155 = 0xA;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->targetSpeed = 0.0f;
}

void playerStateEnterKnockbackState5(void) {
    playerStateTakeDamagePrep();
    gActivePlayerActor->state = 5;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerActor->unk155 = 0xA;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->targetSpeed = 0.0f;
    slotQueueUpdate(6, 1, 0);
}

void playerStateEnterState4F(void) {
    gCurrentActor->state = 0x4F;
    gCurrentActor->unk155 = 2;
    actorScriptStartByIndex(gCurrentActor, 0x34);
    gActivePlayerState->unk50 = 0;
}

void playerStateEnterStunState1(void) {

    gGlobalPauseFlags |= 0x4000;
    gActivePlayerActor->state = 1;
    gActivePlayerActor->unk155 = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0, 0);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->unk4C = -1;
}

void playerStateEnterKnockbackState6(void) {
    gActivePlayerActor->state = 6;
    gActivePlayerActor->unk155 = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0, 0);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->unk4C = -1;
    gActivePlayerActor->flags &= ~4;
}

void playerStateEnterElectrocute(void) {
    gActivePlayerActor->state = 0x6B;
    gActivePlayerActor->unk155 = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0, 0);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->unk4C = -1;
    gActivePlayerActor->flags &= ~4;
}

void func_80026004(s32, s32, f32);

void playerStateEnterSquish(void) {
    gActivePlayerActor->state = 7;
    gActivePlayerActor->unk155 = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x7A);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->unk4C = -1;
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
    gActivePlayerActor->flags &= 0xFFFBFFFF;
    gActivePlayerActor->speedXZ = 0.0f;
}

void playerStateSetFlag8(void) {
    gActivePlayerState->stateFlags |= 8;
}

void playerStateInitKongAction69(void) {
    gActivePlayerActor->state = 0x69;
    gActivePlayerActor->unk155 = 0;
    actorScriptStart(gActivePlayerActor, 0);
    scriptSetRampValue(gActivePlayerActor, 0.0f, 0.0f);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->unk4C = -1;
    gActivePlayerActor->flags &= 0xFEFFFFFF;
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
}

void playerStateAdjustUpwardVelocity(void) {
    Actor *actor;
    s32 handle;

    actor = gActivePlayerState->actor;
    handle = ((EfExtActor *)actor)->unk178;
    if (actor->state < 3) {
        func_80026004(handle, 0x1E, 1.0f);
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
    gActivePlayerState->unk1FE = gPlayerSlots[gCurrentPlayerIndex].queuedParam0;
}

void playerStateInitKongAction78(void) {
    actorScriptStart(gActivePlayerActor, 0x1A);
    gActivePlayerActor->state = 0x78;
    gActivePlayerActor->unk155 = 0;
}

void playerStateDropAndResume(void) {
    playerDropHeldActor(gCurrentActor);
    playerResumeLocomotion(gCurrentActor);
}

typedef struct EfModelSlot {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0x84];
} EfModelSlot;

extern EfModelSlot *gModelSlots;
extern s16 D_807539DC[];
extern s16 D_807539EC[];

void playerStateEnterFlattened(void) {
    f32 speed;

    speed = 1.0f;
    playerKongStopSoundByState(gCurrentActor);
    gActivePlayerActor->state = 0x6C;
    gActivePlayerActor->unk155 = 0;
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

    ((CamState *)gActivePlayerState->camActor->customState)->unkAC |= 4;
    gActivePlayerActor->state = 0x6D;
    gActivePlayerActor->unk155 = 0;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->unk4C = -1;
    gActivePlayerActor->flags &= ~1;
    if (gCurrentMap == 0x27) {
        gActivePlayerActor->unk144 = 1;
    }
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
    if (gActivePlayerActor->actorType == 2) { animation = 0x53; } else { animation = 0x1C7; } controllerAnimSetStateIfChanged(gActivePlayerActor, (s16)animation, 0.0f, 0.0f); // LAYOUT: one source line steers the scheduler (li at,2 after mfc1)
}

void playerStateEnterFrozen(void) {
    Actor *actor;

    gActivePlayerActor->state = 0x75;
    gActivePlayerActor->unk155 = 0;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->unk4C = -1;
    gActivePlayerActor->flags &= ~1;
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
    actor = gActivePlayerState->actor;
    actorCopyPoseAndScale(gActivePlayerActor, actor, actor->sub4->scaleX);
    gActivePlayerActor->unk144 = 1;
    controllerAnimSetStateIfChanged(gActivePlayerActor, 0x22A, 0.0f, 0.0f);
}

void playerStateEnterState3C(void) {
    gActivePlayerState->subTimer = D_807539EC[gCurrentCharacterIndex];
    gActivePlayerState->pitchAngle = gCurrentActor->yaw;
    gActivePlayerState->actionTimer = D_807539DC[gCurrentCharacterIndex];
    gCurrentActor->state = 0x4F;
    gCurrentActor->unk155 = 1;
    if (gCurrentActor->speedY > 0.0f) {
        gCurrentActor->speedY = 0.0f;
    }
    actorScriptStartByIndex(gCurrentActor, 0x36);
    controllerAnimSetStateRemap(gCurrentActor, 0x31, 0.0f, 8.0f);
    scriptSetActorRampTarget(gCurrentActor, 0.5f, 0.0f);
}

extern f32 D_807531C4[];
extern f32 gKongTurnDecelRates[];
extern f32 D_807534E4[];
extern f32 D_80753500[];
extern s16 D_8075351C[];
extern f32 D_80753908[];
extern f32 D_80753924[];
extern f32 D_80753940[];
extern f32 D_80753D70[];
extern f32 D_80753D8C[];
extern SchedStruct gScheduler;
extern f32 gKongCannonInitialPitch[];
extern s16 D_8075388C[];
extern s16 D_807538D8[];
extern s16 D_807538E8[];
extern s16 D_807538F8[];
extern f32 D_80753988[];
extern s16 D_807539FC[];
extern f32 D_80753A5C[];

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
    decelMinSigned = D_80753A5C[gCurrentCharacterIndex];
    if (decelMinSigned > 0.0f) {
        decelMin = decelMinSigned;
    } else {
        decelMin = -decelMinSigned;
    }
    waterY = gActivePlayerActor->waterY;
    maxDepth = D_807538D8[gCurrentCharacterIndex];
    depth = gActivePlayerActor->prevPeakY - waterY;
    if (maxDepth < depth) {
        depth = maxDepth;
    }
    rise = D_807538E8[gCurrentCharacterIndex] + ((D_807538F8[gCurrentCharacterIndex] - D_807538E8[gCurrentCharacterIndex]) * (depth / maxDepth));
    rise -= (waterY - D_8075388C[gCurrentCharacterIndex]) - gActivePlayerActor->y;
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
    gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
    speed = gCurrentActor->speedXZ;
    maxSpeed = D_80753988[gCurrentCharacterIndex];
    if (speed < maxSpeed) {
        gCurrentActor->speedXZ = speed;
    } else {
        gCurrentActor->speedXZ = maxSpeed;
    }
    gActivePlayerActor->state = 0x4E;
    gActivePlayerActor->unk155 = 0;
    actorScriptStartByIndex(gCurrentActor, 0x35);
    gActivePlayerState->turnRate = D_807539FC[gCurrentCharacterIndex];
}

void playerStateEnterKnockbackRecovery(void) {
    gActivePlayerActor->state = 0x51;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerState->jumpVelocityY = D_80753908[gCurrentCharacterIndex];
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    gActivePlayerState->airAccel = D_80753924[gCurrentCharacterIndex];
    gActivePlayerState->decelRate = D_80753940[gCurrentCharacterIndex];
    actorScriptStartByIndex(gActivePlayerActor, 0x3E);
    scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
    gActivePlayerState->jumpTimer = gScheduler.unk280 - 0x1E;
}

void playerStateEnterDamageKnockback(void) {
    f32 current;
    f32 limit;

    gActivePlayerActor->state = 0x50;
    gActivePlayerActor->unk155 = 0;
    gCurrentActor->speedY = -10.0f;
    gActivePlayerState->unk50 = 0;
    current = gCurrentActor->speedXZ;
    limit = D_807531C4[gCurrentCharacterIndex];
    if (current < limit) {
        gCurrentActor->speedXZ = current;
    } else {
        gCurrentActor->speedXZ = limit;
    }
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    actorScriptStartByIndex(gActivePlayerActor, 0x3C);
}

extern Actor *D_807FBB90;

void playerStateEnterAirDamageReaction(void) {
    gActivePlayerState->queuedHeldActor = D_807FBB90;
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
    gActivePlayerActor->unk155 = 0;
}

void playerStateEnterGroundImpact(void) {
    actorScriptStartByIndex(gActivePlayerActor, 8);
    scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
    controllerAnimSetStateRemap(gActivePlayerActor, 0x2E, 0.0f, 6.0f);
    gActivePlayerActor->state = 0x46;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerState->targetSpeed = D_807534E4[gCurrentCharacterIndex];
    gActivePlayerState->airAccel = D_80753500[gCurrentCharacterIndex];
    gActivePlayerState->turnRate = D_8075351C[gCurrentCharacterIndex];
    gActivePlayerState->unk4C = -1;
}

void playerStateEnterAction24(void) {
    gCurrentActor->state = 0x24;
    gCurrentActor->unk155 = 0;
    actorScriptStart(gCurrentActor, 0x1B2);
    gActivePlayerState->unkC8 = 0x32;
}

void playerStateEnterHoldThrow(void) {
    f32 height;

    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        height = D_80753D70[gCurrentCharacterIndex];
    } else {
        height = D_80753D8C[gCurrentCharacterIndex];
    }
    gActivePlayerActor->state = 0x5B;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerState->unk10C = height;
    gActivePlayerActor->y = gActivePlayerState->unkF0 - gActivePlayerState->unk10C;
    gActivePlayerActor->moveYaw = gActivePlayerActor->arcYawMin + 0x14;
    gActivePlayerActor->speedY = 0.0f;
    actorScriptStartByIndex(gActivePlayerActor, 0x75);
    actorScriptExecute(gActivePlayerActor);
}

void playerStateEnterState57(void) {
    gActivePlayerActor->contactFlags |= 0x40;
    gActivePlayerActor->renderFlags &= ~0x2000;
    gActivePlayerActor->state = 0x57;
    gActivePlayerActor->unk155 = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x69);
    actorScriptExecute(gActivePlayerActor);
}

extern s32 gGlobalCutsceneFlags;
extern f32 D_807535CC[];
extern s16 D_8075380C[];

void playerStateEnterState59(void) {
    CamState *camState;

    camState = gActivePlayerState->camActor->customState;
    gActivePlayerActor->contactFlags |= 0x40;
    gActivePlayerActor->renderFlags &= ~0x2000;
    gActivePlayerActor->state = 0x59;
    gActivePlayerActor->unk155 = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x70);
    actorScriptExecute(gActivePlayerActor);
    camStartBlendRamp(camState, 0x14);
}

void playerStateEnterState17(void) {
    CamState *camState;

    camState = gActivePlayerState->camActor->customState;
    gCurrentActor->state = 0x17;
    gCurrentActor->unk155 = 0;
    if (gGlobalCutsceneFlags & 2) {
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex] * 1.3;
    } else {
        gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex];
    }
    gActivePlayerActor->speedXZ = gActivePlayerState->unk124;
    gActivePlayerState->unk50 = 0;
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
    if ((gPlayerCount >= 2) || (gActivePlayerActor->actorType != 6) || (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1)) {
        gActivePlayerActor->speedY = 260.0f;
        playerSetBaseGravity();
        gActivePlayerState->unk50 = 0;
        gActivePlayerState->turnRate = 0x64;
        actorScriptStartByIndex(gActivePlayerActor, 0x1F);
        scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
        gActivePlayerActor->state = 0x30;
        gActivePlayerActor->unk155 = 0;
        playerDropHeldActor(gActivePlayerActor);
    }
}

void playerStateEnterState11(void) {
    gActivePlayerActor->speedY = 260.0f;
    playerSetBaseGravity();
    gActivePlayerState->unk50 = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x20);
    scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
    gActivePlayerActor->state = 0x30;
    gActivePlayerActor->unk155 = 0;
    playerDropHeldActor(gActivePlayerActor);
}

extern s16 D_807537FC[];
extern s16 D_8075383C[];
extern s16 D_8075384C[];

void playerStateEnterState12(void) {
    gActivePlayerState->unk50 = D_807537FC[gCurrentCharacterIndex];
    gActivePlayerState->slideLaunchSpeed += D_8075383C[gCurrentCharacterIndex];
    if (D_8075384C[gCurrentCharacterIndex] < gActivePlayerState->slideLaunchSpeed) {
        gActivePlayerState->slideLaunchSpeed = D_8075384C[gCurrentCharacterIndex];
    }
    gActivePlayerActor->speedY = 0.0f;
    gActivePlayerState->unk50 = 0;
}

void playerStateEnterState29(void) {
    if ((gCurrentActor->state != 2) && (gPlayerCharacterId[gCurrentPlayerIndex] == 6)) {
        gCurrentActor->state = 0x29;
        gCurrentActor->unk155 = 0;
        actorScriptStartByIndex(gCurrentActor, 0x3F);
        gActivePlayerState->unk64 = 0;
        gActivePlayerState->slideLaunchSpeed = D_8075380C[gCurrentCharacterIndex];
    }
}

void playerStateEnterState15ThrowHeldActor(void) {
    Actor *target;

    playerClearCarriedItemState();
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerState->gunDrawn = 0;
    playerKongStopSoundByState(gCurrentActor);
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
        gActivePlayerActor->unk155 = 0;
        return;
    }
    gActivePlayerActor->state = 0x42;
    gActivePlayerActor->unk155 = 0;
}

extern s16 D_807530B0[];

void playerStateDamageTargetCheck(void) {
    Actor *camTarget;
    Actor *target;
    f32 v;

    target = gActivePlayerState->actor;
    if (target->speedXZ >= 0.0f) {
        behaviourAddSlotQueueValueB(3);
        target = gActivePlayerState->actor;
    }
    camTarget = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
    if (camTarget != NULL) {
        if (camTarget->speedXZ != 0.0f) {
            v = camTarget->speedXZ > 0.0f ? camTarget->speedXZ : -camTarget->speedXZ;
            target->speedXZ = 2.0 * v;
        } else {
            v = target->speedXZ > 0.0f ? target->speedXZ : -target->speedXZ;
            target->speedXZ = v < 50.0f ? -50.0f : -(target->speedXZ > 0.0f ? target->speedXZ : -target->speedXZ);
        }
    } else {
        v = target->speedXZ > 0.0f ? target->speedXZ : -target->speedXZ;
        target->speedXZ = v < 50.0f ? -50.0f : -(target->speedXZ > 0.0f ? target->speedXZ : -target->speedXZ);
    }
    actorScriptStart(gActivePlayerState->actor, 0x292);
    if (gActivePlayerState && gActivePlayerState) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (gActivePlayerActor->state != 9) {
        actorScriptStartByIndex(gActivePlayerActor, 0x83);
    }
}

void playerStateDamageCheck4(void) {
    u8 character;

    if (gActivePlayerState->surfaceTimer == 0) {
        playerClearCarriedItemState();
        behaviourAddSlotQueueValueB(3);
        character = gPlayerCharacterId[gCurrentPlayerIndex];
        if (character != 2) {
            if (character == 3) {
                sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0xB9, 0xFF, 0x7F, 0x14);
            }
        } else {
            sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0xD2, 0xFF, 0x7F, 0x14);
        }
        gActivePlayerState->surfaceTimer = D_807530B0[gCurrentCharacterIndex];
        gActivePlayerActor->speedXZ = gActivePlayerActor->speedXZ / 2;
    }
}

void playerStatePlayAnimationByDamageType(u16 damageType) {
    u16 ev;
    s16 anim;

    switch (damageType) {
    case 0x12:
        ev = 0x16D;
        anim = 0x23;
        break;
    case 0x81:
        ev = 0x16E;
        anim = 0x24;
        break;
    }
    if (flagGet(ev, 0) == 0) {
        if (damageType == 0x81) {
            gActivePlayerActor->speedXZ = 0.0f;
        }
        camStartPath(NULL, anim, 5);
        flagSet(ev, 1, 0);
    }
}

void playerStateApplyAttackerDamage(Actor *attacker) {
    s16 id;
    u16 type;
    s32 ev;

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
        ev = 0x169;
        break;
    case 0x28:
        ev = 0x168;
        break;
    case 0x39:
        ev = 0x16B;
        break;
    case 0x38:
        ev = 0x16A;
        break;
    default:
        return;
    }
    if (flagGet(ev, 0) == 0) {
        camStartPath(NULL, 0x16, 5);
        flagSet(ev, 1, 0);
    }
}

extern u8 *D_807FD568;

void playerStateSetLaunchVelocity(void) {
    u8 gunSound;
    s32 sizeMode;
    s32 kongId;

    gunSound = 0;
    gActivePlayerActor->speedXZ = gActivePlayerState->unk6C;
    gActivePlayerActor->moveYaw = gActivePlayerState->unk70;
    gActivePlayerActor->yaw = gActivePlayerState->unk70;
    gActivePlayerActor->speedY = gActivePlayerState->unk74;
    scriptSetActorRampTarget(gActivePlayerActor, 1.0f, 0.0f);
    if (gPlayerSlots[gCurrentPlayerIndex].queuedActor == NULL) {
        gActivePlayerActor->state = 0x44;
        gActivePlayerActor->unk155 = 0;
        actorScriptStartByIndex(gActivePlayerActor, 0x22);
        gActivePlayerState->unk50 = 0x14;
        playerSetBaseGravity();
    } else {
        switch (gPlayerSlots[gCurrentPlayerIndex].queuedActor->actorType) {
        case 0x17:
        case 0xA7:
            gActivePlayerActor->state = 0x45;
            gActivePlayerActor->unk155 = 0;
            actorScriptStartByIndex(gActivePlayerActor, 0x22);
            gActivePlayerState->unk50 = 0x14;
            playerSetBaseGravity();
            break;
        case 0x11:
            gActivePlayerActor->state = 0x44;
            gActivePlayerActor->unk155 = 0;
            actorScriptStartByIndex(gActivePlayerActor, 0x22);
            gActivePlayerState->unk50 = 0x14;
            playerSetBaseGravity();
            break;
        case 0x1C:
        case 0x6B:
        case 0x86:
            if (actorFindByType(0x25) != NULL) {
                gActivePlayerActor->state = 0x63;
                gActivePlayerActor->unk155 = 0;
                actorScriptStart(gActivePlayerActor, 0x7D);
                gActivePlayerActor->speedXZ = 0.0f;
                gActivePlayerState->targetSpeed = 300.0f;
                gunSound = 1;
                slotQueueUpdate(5, 1, 0);
                break;
            }
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
                gActivePlayerActor->flags &= 0xFFFF7FFF;
            } else {
                gActivePlayerActor->flags |= 0x8000;
            }
            playerResumeLocomotion(gActivePlayerActor);
            break;
        case 0x39:
            gActivePlayerState->stateFlags |= 0x10;
            gActivePlayerActor->flags &= 0xFFFF7FFF;
            gActivePlayerActor->alpha = 0x7F;
            effectSpawnActorOrbitParticles(gActivePlayerActor);
            playerEnterFall(gCurrentActor);
            playerSetBaseGravity();
            break;
        case 0x38:
            gActivePlayerState->stateFlags |= 0x20;
            gActivePlayerActor->state = 0x41;
            gActivePlayerActor->unk155 = 0;
            actorScriptStart(gActivePlayerActor, 0x156);
            gActivePlayerActor->speedXZ = 0.0f;
            gActivePlayerState->unk50 = 4;
            playerSetTerminalVelocity5B0();
            break;
        case 0x31:
            gActivePlayerActor->state = 0x63;
            gActivePlayerActor->unk155 = 0;
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
                gActivePlayerActor->unk155 = 0;
                actorScriptStartByIndex(gActivePlayerActor, 9);
                gActivePlayerActor->speedXZ = 0.0f;
            } else {
                playerSetKongByActorType(9);
                if (gActivePlayerActor->waterY < gActivePlayerActor->y) {
                    gActivePlayerActor->state = 0x82;
                    gActivePlayerActor->unk155 = 0;
                } else {
                    gActivePlayerActor->state = 0x7F;
                    gActivePlayerActor->unk155 = 0;
                }
                actorScriptStart(gActivePlayerActor, 0x317);
                gActivePlayerActor->speedXZ = 100.0f;
            }
            gActivePlayerState->unk50 = 4;
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
    if (((gPlayerSlots[gCurrentPlayerIndex].queuedActor != NULL) && (gPlayerSlots[gCurrentPlayerIndex].queuedActor->actorType == 0x31)) || (gunSound != 0)) {
        if (D_807FD568[2] & 1) {
            if (gActivePlayerState->gunDrawn != 0) {
                gActivePlayerState->stateFlags2 |= 4;
            } else {
                gActivePlayerState->stateFlags2 &= ~4;
            }
            gActivePlayerState->gunDrawn = 1;
            playerKongPlaySoundByState(gActivePlayerActor);
        }
    } else {
        playerKongStopSoundByState(gCurrentActor);
    }
    if (gPlayerSlots[gCurrentPlayerIndex].queuedActor != NULL) {
        playerStateApplyAttackerDamage(gPlayerSlots[gCurrentPlayerIndex].queuedActor);
    }
    if ((gActivePlayerActor->contactFlags & 4) && (gPlayerSlots[gCurrentPlayerIndex].queuedActor->actorType != 0x81)) {
        gActivePlayerState->subTimer = D_807539EC[gCurrentCharacterIndex];
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        gActivePlayerState->actionTimer = D_807539DC[gCurrentCharacterIndex] * 0.5;
        gCurrentActor->state = 0x4F;
        gCurrentActor->unk155 = 1;
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
    gActivePlayerActor->unk155 = 0;
}

void playerStateThrowHeldActorWithScript(void) {
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x56;
    gActivePlayerActor->unk155 = 0;
    actorScriptStartByIndex(gActivePlayerActor, 0x87);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->targetSpeed = 0.0f;
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
}


void playerStateEnterDamageTake(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        playerClearCarriedItemState();
        if (func_806C9974(gCurrentPlayerIndex, -1) != 0) {
            if (gActivePlayerActor->contactFlags & 4) {
                actorScriptStartByIndex(gActivePlayerActor, 0x29);
            } else {
                actorScriptStartByIndex(gActivePlayerActor, 0x27);
            }
            gActivePlayerActor->state = 0x36;
            gActivePlayerActor->unk155 = 0;
        }
        gActivePlayerState->surfaceTimer = D_807530B0[gCurrentCharacterIndex];
    }
}


void playerStateAttachHeldActorToPlayer(void) {
    Actor *held = gActivePlayerState->heldActor;

    if (held != NULL) {
        actorAppendCallback4000(gCurrentActor, held, gActivePlayerActor->yaw, gCurrentActor->speedY,
                                gCurrentActor->speedXZ);
        gActivePlayerState->heldActor = NULL;
        gActivePlayerState->queuedHeldActor = NULL;
    }
    playerClearCarriedItemState();
    actorScriptStartByIndex(gCurrentActor, 0x1C);
    gActivePlayerActor->state = 0x20;
    gActivePlayerActor->unk155 = 0;
}

void playerStateEnterSlideRecover(void) {
    playerClearCarriedItemState();
    actorScriptStartByIndex(gCurrentActor, 0x1C);
    gActivePlayerActor->state = 0x21;
    gActivePlayerActor->unk155 = 0;
}

void playerStateDamageSelector(void) {
    s32 shake = 1;
    s8 selector;
    Actor *target;

    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        selector = -1;
        playerClearCarriedItemState();
        target = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
        if ((target != NULL) && (target->actorType == 0x123)) {
            selector = -2;
        }
        if (func_806C9974(gCurrentPlayerIndex, selector) != 0) {
            shake = 0;
            if (gActivePlayerActor->contactFlags & 4) {
                actorScriptStartByIndex(gActivePlayerActor, 0x29);
            } else {
                actorScriptStartByIndex(gActivePlayerActor, 0x27);
            }
            gActivePlayerActor->state = 0x36;
            gActivePlayerActor->unk155 = 0;
        } else {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0);
            actorScriptStartByIndex(gCurrentActor, 0x1E);
            gCurrentActor->state = 0x20;
            gCurrentActor->unk155 = 1;
        }
    }
    if ((gActivePlayerState->surfaceTimer == 0) && (gPlayerCount < 2)) {
        gActivePlayerState->surfaceTimer = D_807530B0[gCurrentCharacterIndex];
    }
    if (shake != 0) {
        camStartShake(gActivePlayerState->camActor, 0x14, 0x14);
    }
}

void playerTakeFallDamage(void) {
    s32 shake = 1;

    playerClearCarriedItemState();
    if ((playerCanTakeHit(gActivePlayerActor) != 0) && (func_806C9974(gCurrentPlayerIndex, -1) != 0)) {
        shake = 0;
        if ((gActivePlayerActor->contactFlags & 4) != 0) {
            actorScriptStartByIndex(gActivePlayerActor, 0x29);
        } else {
            actorScriptStartByIndex(gActivePlayerActor, 0x27);
        }
        gActivePlayerActor->state = 0x36;
        gActivePlayerActor->unk155 = 0;
    } else {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0);
        actorScriptStartByIndex(gCurrentActor, 0x1E);
        gCurrentActor->state = 0x20;
        gCurrentActor->unk155 = 1;
    }
    if ((gActivePlayerState->surfaceTimer == 0) && (gPlayerCount < 2)) {
        gActivePlayerState->surfaceTimer = D_807530B0[gCurrentCharacterIndex];
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
    gActivePlayerActor->unk155 = 0;
}

void playerStateEnterFallAndSetGravity(void) {
    playerSetBaseGravity();
    playerEnterFall(gCurrentActor);
}

void playerStateSwimTreadWithScript(void) {
    playerThrowHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x32);
    gActivePlayerActor->state = 0x52;
    gActivePlayerActor->unk155 = 0;
}

void func_806EE6B0(void) {
    playerThrowHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x86);
    gActivePlayerActor->state = 0x53;
    gActivePlayerActor->unk155 = 0;
}

void playerResumeLocomotionAndThrow(void) {
    playerThrowHeldActor(gActivePlayerActor);
    playerResumeLocomotion(gActivePlayerActor);
    gActivePlayerActor->state = 0x54;
    gActivePlayerActor->unk155 = 0;
}

extern s16 D_807FD6F2;

/* customState of gActivePlayerState->actor on maps 0x0E and 0x52. */
typedef struct EfRideState {
    /* 0x00 */ u8 pad0[0x45];
    /* 0x45 */ u8 unk45;
} EfRideState;

void playerStateDamageCheck(void) {
    EfRideState *ride;

    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        if ((gCurrentMap != 0x52) && (gCurrentMap != 0xE)) {
            playerTakeDamage(0x40);
            return;
        }
        ride = gActivePlayerState->actor->customState;
        ride->unk45 = 1;
    }
}

void playerTakeQueuedDamage(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        playerTakeDamage(D_807FD6F2);
        playerSetBaseGravity();
    }
}

void playerStateCutsceneDamageCheck(void) {
    if ((gGlobalCutsceneFlags & 2) != 0) {
        playerKongClearFlagsByActorType(gActivePlayerActor);
        sfxStopChannel(0xC, 0);
    }
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        if (((gGlobalCutsceneFlags & 2) != 0) && (camIsCutsceneActive() != 0)) {
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
        gCurrentActor->unk144 = 1;
        gCurrentActor->state = 0x34;
        gCurrentActor->unk155 = 0;
        actorScriptStart(gCurrentActor, 0);
        func_806C9974(gCurrentPlayerIndex, -0x40);
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

extern f32 gKongSwimStrokeSpeeds[], D_80753040[], gKongSwimTurnSpeeds[], D_80753078[];
extern s16 D_807530B0[], D_807530D0[], D_807530E0[], D_80753160[], D_8075386C[];
extern f32 gKongSwimPaddleSpeeds[], D_8075310C[], D_80753128[], gKongSwimSpeeds[], gKongTurnDecelRates[], D_8075389C[];
extern s32 gFrameCounter;

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
        if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
            deepThreshold = D_8075386C[gCurrentCharacterIndex];
        } else {
            deepThreshold = D_8075389C[gCurrentCharacterIndex];
        }
        isDeep = deepThreshold < depth;
    }
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        sfxStopChannel(0x6B, 0);
        gActivePlayerActor->flags |= 4;
        gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
        gActivePlayerActor->contactFlags &= 0xFFBF;
        slotQueueCancel(6, 1);
        if (gActivePlayerState->surfaceTimer == 0) {
            playerClearCarriedItemState();
            playerDropHeldActor(gActivePlayerActor);
            if ((gActivePlayerState->actor != NULL) &&
                ((gActivePlayerState->actor->actorType == 0x1D) || (gActivePlayerState->actor->actorType == 0x57) ||
                 (gActivePlayerState->actor->actorType == 0x50) || (gActivePlayerState->actor->actorType == 0x3E))) {
                gActivePlayerState->surfaceTimer = D_807530E0[gCurrentCharacterIndex];
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
                    if ((func_80714608(0) != 0) && (gActivePlayerActor->state == 0x3C) &&
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
                    (func_807142D8() == 0)) {
                    healthDelta = func_806C9830((s8)-damage, gActivePlayerActor);
                    if (healthDelta < 0) {
                        isDead = func_806C9974(gCurrentPlayerIndex, healthDelta);
                    }
                }
                if (isDead != 0) {
                    if (gActivePlayerActor->contactFlags & 4) {
                        actorScriptStartByIndex(gActivePlayerActor, 0x29);
                    } else {
                        actorScriptStartByIndex(gActivePlayerActor, 0x27);
                    }
                    gActivePlayerActor->state = 0x36;
                    gActivePlayerActor->unk155 = 0;
                    if (func_80714608(0) != 0) {
                        gActivePlayerActor->speedY = D_80753128[gCurrentCharacterIndex] * 5.0f;
                        gActivePlayerActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex] * 5.0f;
                        gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex] * 5.0f;
                        gActivePlayerActor->accelY = D_8075310C[gCurrentCharacterIndex];
                    }
                } else {
                    switch (gPlayerSlots[gCurrentPlayerIndex].queuedState) {
                    case 0xE:
                        gActivePlayerActor->state = 0x66;
                        gActivePlayerActor->unk155 = 0;
                        actorScriptStartByIndex(gActivePlayerActor, 0x26);
                        gActivePlayerActor->accelY = D_8075310C[gCurrentCharacterIndex];
                        break;
                    case 0x31:
                        if (isDeep != 0) {
                            gActivePlayerActor->state = 0x37;
                            gActivePlayerActor->unk155 = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x28);
                        } else {
                            gActivePlayerActor->state = 0x34;
                            gActivePlayerActor->unk155 = 0;
                            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x16, 0xFF, 0x7F, 0);
                            actorScriptStartByIndex(gCurrentActor, 0x1E);
                        }
                        break;
                    case 0x2B:
                        if (isDeep != 0) {
                            gActivePlayerActor->state = 0x37;
                            gActivePlayerActor->unk155 = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x28);
                        } else {
                            gActivePlayerActor->state = 0x32;
                            gActivePlayerActor->unk155 = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x25);
                        }
                        break;
                    case 0x32:
                        if (isDeep != 0) {
                            gActivePlayerActor->state = 0x37;
                            gActivePlayerActor->unk155 = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x28);
                        } else {
                            gActivePlayerActor->state = 0x35;
                            gActivePlayerActor->unk155 = 0;
                            actorScriptStartByIndex(gActivePlayerActor, 0x26);
                        }
                        break;
                    case 0x37:
                        gActivePlayerActor->state = 0x33;
                        gActivePlayerActor->unk155 = 0;
                        actorScriptStart(gActivePlayerActor, 4);
                        break;
                    case 0x2E:
                    case 0x2F:
                        if (isDeep != 0) {
                            if (gCurrentMap == 0x6F) {
                                gActivePlayerActor->state = 0x38;
                                gActivePlayerActor->unk155 = 0;
                                actorScriptStart(gActivePlayerActor, 0x3B5);
                                actorScriptStart(gActivePlayerState->actor, 0x3BB);
                                gActivePlayerState->unkC2 = (gFrameCounter & 1) ? -0xFA : 0xFA;
                            } else {
                                gActivePlayerActor->state = 0x37;
                                gActivePlayerActor->unk155 = 0;
                                actorScriptStartByIndex(gActivePlayerActor, 0x28);
                            }
                        } else if (gActivePlayerActor->state != 0x63) {
                            gActivePlayerActor->state = 0x31;
                            gActivePlayerActor->unk155 = 0;
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
                        gActivePlayerState->surfaceTimer = D_807530B0[gCurrentCharacterIndex];
                    } else {
                        if (gPlayerCount >= 2) {
                            playerSetRecentAttacker(actorResolveKillCreditOwner(gPlayerSlots[gCurrentPlayerIndex].queuedActor),
                                          gActivePlayerState);
                        }
                        gActivePlayerActor->speedY = D_80753040[gCurrentCharacterIndex];
                        gActivePlayerActor->speedXZ = gKongSwimTurnSpeeds[gCurrentCharacterIndex];
                        gActivePlayerState->surfaceTimer = D_807530B0[gCurrentCharacterIndex];
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
                    gActivePlayerActor->accelY = D_8075310C[gCurrentCharacterIndex];
                    break;
                case 0xE:
                    if (gPlayerCount >= 2) {
                        playerSetRecentAttacker(actorResolveKillCreditOwner(gPlayerSlots[gCurrentPlayerIndex].queuedActor),
                                      gActivePlayerState);
                    }
                    if (func_80714608(0) != 0) {
                        gActivePlayerActor->speedY = D_80753128[gCurrentCharacterIndex] * 10.0f;
                        gActivePlayerActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex] * 10.0f;
                        gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex] * 10.0f;
                        gActivePlayerState->surfaceTimer = 0xA;
                        gActivePlayerActor->accelY = D_8075310C[gCurrentCharacterIndex];
                    } else {
                        gActivePlayerActor->speedY = D_80753128[gCurrentCharacterIndex];
                        gActivePlayerActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex];
                        if (damage != 0) {
                            gActivePlayerState->surfaceTimer = D_80753160[gCurrentCharacterIndex];
                        }
                        gActivePlayerActor->accelY = D_8075310C[gCurrentCharacterIndex];
                    }
                    break;
                case 0x37:
                    gActivePlayerState->surfaceTimer = D_807530B0[gCurrentCharacterIndex];
                    break;
                case 0x2B: // FAKE: extends the jump table down to 0x2B
                    break;
                }
                if ((gPlayerCount >= 2) && (isDead == 0)) {
                    gActivePlayerState->surfaceTimer = 0x3C;
                }
                if (gActivePlayerActor->state == 0x36) {
                    if (gActivePlayerActor->contactFlags & 4) {
                        gActivePlayerActor->speedY = D_80753078[gCurrentCharacterIndex] / 4;
                    } else {
                        gActivePlayerActor->speedY = D_80753078[gCurrentCharacterIndex];
                    }
                }
                gActivePlayerState->unk50 = 0;
            }
        }
    }
}

void playerStateEnterDamageReaction(void) {
    EfRideState *ride;

    if ((gActivePlayerActor->state == 0x36) || (gActivePlayerActor->state == 0x39) ||
        (gActivePlayerActor->state == 0x3A) || (gActivePlayerActor->state == 0x71) ||
        (gActivePlayerActor->state == 0x73) || (gActivePlayerActor->state == 0x74)) {
        return;
    }
    playerClearCarriedItemState();
    gActivePlayerActor->flags &= 0xFFFF7FFF;
    actorScriptStartByIndex(gActivePlayerActor, 0x27);
    gActivePlayerActor->state = 0x39;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerState->unk11C = 0x19;
    camSnapToTargetHeight(gActivePlayerState->camActor);
    if ((gCurrentMap != 0x52) && (gCurrentMap != 0xE)) {
        func_806C9974(gCurrentPlayerIndex, -0x40);
    } else {
        ride = gActivePlayerState->actor->customState;
        ride->unk45 = 1;
    }
}

void playerStateEnterDamageReaction2(void) {
    if (playerCanTakeHit(gActivePlayerActor) != 0) {
        if (gActivePlayerActor->state != 0x3B) {
            if (camIsCutsceneActive() == 0) {
                playerClearCarriedItemState();
                playerDropHeldActor(gActivePlayerActor);
                gActivePlayerActor->unk144 = 1;
                actorScriptStartByIndex(gActivePlayerActor, 0x2A);
                gActivePlayerActor->state = 0x3B;
                gActivePlayerActor->unk155 = 0;
                func_806C9974(gCurrentPlayerIndex, -0x40);
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
    gCurrentActor->unk155 = 0;
}

typedef struct EfKongScriptIds {
    u16 values[5];
} EfKongScriptIds;

extern EfKongScriptIds D_8075D380;

void playerStateSpawnParticles(void) {
    EfKongScriptIds spawnParams;
    s32 pad;
    f32 height;

    spawnParams = D_8075D380;
    height = gActivePlayerActor->sub4->scaleX;
    actorSpawn(0x140, 0xB9);
    if (gActivePlayerActor->actorType == 2) {
        height *= 1.25;
    }
    actorCopyPoseAndScale(gSpawnedActor, gActivePlayerActor, height);
    actorScriptStart(gSpawnedActor, spawnParams.values[gPlayerCharacterId[gActivePlayerState->playerIndex]]);
    gSpawnedActor->flags |= 0x40000000;
    actorScriptStartByIndex(gActivePlayerActor, 0x88);
    gCurrentActor->state = 0x79;
    gCurrentActor->unk155 = 0;
}

void playerStateStopChannelAndClearCarried(void) {
    sfxStopChannel(0x6B, 0);
    playerClearCarriedItemState();
    playerCheckAndResetCarriedActor(gActivePlayerActor);
    playerDropHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x5B);
    gActivePlayerActor->state = 0x70;
    gActivePlayerActor->unk155 = 0;
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
        gActivePlayerActor->unk155 = 0;
    }
    gActivePlayerActor->yaw = mathAngleBetweenPoints2D(
        gPlayerSlots[gCurrentPlayerIndex].camX,
        gPlayerSlots[gCurrentPlayerIndex].camZ,
        gActivePlayerActor->x,
        gActivePlayerActor->z);
    if (gCurrentMap == 8) {
        camStartPath(gActivePlayerActor, 2, 1);
        gActivePlayerActor->unk155 = 0xFF;
        gActivePlayerState->unk23C = 0xFFFF;
    } else {
        camStartPath(gActivePlayerActor, 5, 5);
        gActivePlayerState->unk23C = 100;
    }
}

void playerStateDropHeldActorAndScript(void) {
    playerClearCarriedItemState();
    playerDropHeldActor(gActivePlayerActor);
    actorScriptStartByIndex(gActivePlayerActor, 0x5B);
    gActivePlayerActor->state = 0x72;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ,
                                                  gActivePlayerActor->x, gActivePlayerActor->z);
    camStartPath(gActivePlayerActor, 0x15, 5);
}

void playerStateDropHeldActorSetKong(void) {
    playerSetKongByActorType(gActivePlayerState->savedActorType);
    playerDropHeldActor(gActivePlayerActor);
    playerClearCarriedItemState();
    gActivePlayerActor->unk144 = 1;
    if (gActivePlayerActor->state != 0x7D) {
        if (gActivePlayerActor->contactFlags & 4) {
            actorScriptStartByIndex(gActivePlayerActor, 0x34);
        } else if (!(gActivePlayerActor->contactFlags & 2)) {
            actorScriptStartByIndex(gActivePlayerActor, 0x5D);
        }
    }
    gActivePlayerActor->state = 0x73;
    gActivePlayerActor->unk155 = 0;
    if ((gActivePlayerState->actor == NULL) || (gActivePlayerState->actor->actorType != 0x57)) {
        gActivePlayerActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ,
                                                      gActivePlayerActor->x, gActivePlayerActor->z);
    }
    gActivePlayerActor->speedY = 0.0f;
    gActivePlayerState->unk23C = 0x5A;
    playerSetBaseGravity();
}

void playerStateDropHeldActorSetKong2(void) {
    playerSetKongByActorType(gActivePlayerState->savedActorType);
    playerDropHeldActor(gActivePlayerActor);
    playerClearCarriedItemState();
    gActivePlayerActor->unk144 = 1;
    if (gActivePlayerActor->state != 0x7D) {
        if (gActivePlayerActor->contactFlags & 4) {
            actorScriptStartByIndex(gActivePlayerActor, 0x34);
        } else if (!(gActivePlayerActor->contactFlags & 2)) {
            actorScriptStartByIndex(gActivePlayerActor, 0x5C);
        }
    }
    gActivePlayerActor->state = 0x74;
    gActivePlayerActor->unk155 = 0;
    if ((gActivePlayerState->actor == NULL) || (gActivePlayerState->actor->actorType != 0x57)) {
        gActivePlayerActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ,
                                                      gActivePlayerActor->x, gActivePlayerActor->z);
    }
    gActivePlayerActor->speedY = 0.0f;
    gActivePlayerState->unk23C = 0x5A;
    playerSetBaseGravity();
}

void playerStateNoop1(void) {
}

void playerStateNoop2(void) {
}

void func_806F007C(void) {
    gCurrentActor->state = 0x84;
    gCurrentActor->unk155 = 0;
    actorScriptStart(gCurrentActor, 0);
}

void playerStateClearCarriedSetFlags(void) {
    playerClearCarriedItemState();
    gActivePlayerState->stateFlags &= ~0x20;
    gActivePlayerActor->interactionType = 2;
    gActivePlayerState->unk4C = -1;
    gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
    gActivePlayerActor->state = 0x7A;
    gActivePlayerActor->unk155 = 0;
}

void func_806F014C(void) {
    gActivePlayerState->stateFlags2 |= 8;
    playerResumeLocomotion(gActivePlayerActor);
}

void func_806F0184(void) {
    playerClearCarriedItemState();
    gActivePlayerState->stateFlags &= ~0x20;
    gActivePlayerActor->state = 0x7B;
    gActivePlayerActor->unk155 = 0;
}

void playerStateClearCarriedAndCallF00BC(void) {
    playerClearCarriedItemState();
    playerStateClearCarriedSetFlags();
    gActivePlayerState->actor = gPlayerSlots[gCurrentPlayerIndex].queuedActor;
}

void playerStateEnterClimbTree(void) {
    actorScriptStartByIndex(gActivePlayerActor, 9);
    gActivePlayerActor->state = 0xC;
    gActivePlayerActor->unk155 = 0;
}

void playerStateEnterKnockbackState(void) {
    gActivePlayerState->unk4C = -1;
    gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
    playerSetBaseGravity();
    if (gActivePlayerActor->state != 0x7C) {
        playerClearCarriedItemState();
        gActivePlayerActor->state = 0x7C;
        gActivePlayerActor->unk155 = 0;
        actorScriptStart(gActivePlayerActor, 0x13);
        actorSpawn(0x117, 0xC5);
        gSpawnedActor->parentActor = gActivePlayerActor;
        actorSetInteractionTimer(gActivePlayerActor);
    }
}

void func_806F0344(void) {
    playerSetBaseGravity();
    gActivePlayerActor->state = 0x7D;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerActor->flags &= ~4;
    actorSpawn(0x11A, 0x21);
    actorScriptStart(gSpawnedActor, 0x232);
    gSpawnedActor->parentActor = gActivePlayerActor;
}

void playerStateSetFlagsByActorType(void) {
    s32 ev;

    /* The original leaves ev unset on the default path (other actor types); camStartPath reads it. */
    switch (gActivePlayerActor->actorType) {
    case 2:
        ev = 7;
        break;
    case 3:
        ev = 0;
        break;
    case 4:
        gActivePlayerState->stateFlags |= 0x100;
        ev = 4;
        break;
    case 5:
        if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
            ev = 8;
        } else {
            ev = 0x1F;
        }
        break;
    case 6:
        ev = 9;
        break;
    default:
        break;
    }
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    if (gActivePlayerActor && gActivePlayerActor && gActivePlayerActor) {}  // FAKE: pads as1 XBB source window
    gActivePlayerActor->yaw = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ,
                                                  gActivePlayerActor->x, gActivePlayerActor->z);
    if (gGlobalCutsceneFlags & 2) {
        gActivePlayerState->stateFlags &= ~0x100;
        actorScriptStart(gActivePlayerActor, 0x165);
    } else {
        if (gActivePlayerActor->state != 0x56) {
            camStartPath(gActivePlayerActor, (s16)ev, 5);
        }
        actorScriptStartByIndex(gActivePlayerActor, 0x5A);
    }
    gActivePlayerActor->state = 0x67;
    gActivePlayerActor->unk155 = 0;
}

void func_806F0624(void) {
    gActivePlayerState->stateFlags2 |= 0x10;
    func_806E9964(gActivePlayerState);
    gActivePlayerActor->state = 0x83;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerActor->flags |= 0x40000004;
    gActivePlayerActor->flags &= ~1;
}

void func_806F06A4(void) {
    gActivePlayerActor->state = 0x87;
    gActivePlayerActor->unk155 = 0;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->unk4C = -1;
}

void func_806F0700(void) {
    gActivePlayerActor->state = 0x88;
    gActivePlayerActor->unk155 = 0;
    actorScriptStart(gActivePlayerActor, 0);
    gActivePlayerActor->x = gActivePlayerState->savedX;
    gActivePlayerActor->y = gActivePlayerState->savedY;
    gActivePlayerActor->z = gActivePlayerState->savedZ;
    gActivePlayerActor->pitch = -0x3E6;
    gActivePlayerActor->sub4->scaleX = 0.01f;
    gActivePlayerActor->sub4->scaleY = 0.01f;
    gActivePlayerActor->sub4->scaleZ = 0.01f;
    gActivePlayerState->unk50 = 0;
    gActivePlayerState->unk4C = -1;
}

void playerStateEnterDoubleJumpWithSfx(void) {
    sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0xF3, 0xFF, 0x7F, 0x19);
    gActivePlayerActor->state = 0x19;
    gActivePlayerActor->unk155 = 0;
    gActivePlayerState->jumpVelocityY = D_807535CC[gCurrentCharacterIndex] * 2.6;
    gActivePlayerState->unk50 = 0xC;
    actorScriptStartByIndex(gActivePlayerActor, 0x10);
}

void func_806F0878(void) {
    if (gActivePlayerActor->unk78[0] == 0xC) {
        sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0x76, 0x64, 0x7F, 0);
    }
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x15;
    gActivePlayerActor->unk155 = 0;
    actorScriptStartByIndex(gActivePlayerActor, 6);
    gActivePlayerActor->contactFlags |= 0x20;
    actorScriptExecute(gActivePlayerActor);
}

void func_806F0930(void) {
    if (gActivePlayerActor->unk78[0] == 0xC) {
        sfxPlayFromActorWithAltitudeCheck(gActivePlayerActor, 0x76, 0xFF, 0x7F, 0);
    }
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    playerThrowHeldActor(gActivePlayerActor);
    gActivePlayerActor->state = 0x16;
    gActivePlayerActor->unk155 = 0;
    actorScriptStartByIndex(gActivePlayerActor, 7);
    gActivePlayerActor->contactFlags |= 0x20;
    actorScriptExecute(gActivePlayerActor);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/EFDC0/D_8075D380.s")
