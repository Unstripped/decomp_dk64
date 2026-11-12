#include "common.h"
#include "actor.h"
#include "boss.h"
#include "sched.h"
#include "proto/boss/3840.h"
#include "proto/boss/C920.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/42630.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/7130.h"
#include "proto/global/A2F10.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"

// K. Rool (Chunky phase) actor: component 1 (0x174) is gBehaviourWorkState, component 2 the script state.
typedef struct BossKRoolChunkyActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
} BossKRoolChunkyActor;

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;
extern Actor *gCamActor;
extern PlayerStruct *gPlayerSlots;

void bossKRoolChunkySetupFight(BossScriptState *unused) {
    gActivePlayerState->unk1FE = 1;
    bossSetCannonsVisible(1);
    gCurrentActor->unk144 = 0x24;
    playerStateQueueCallback(0x19, gCurrentActor, 0);
    zoneEntryGetPosition(1, 8, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
    gBehaviourWorkState->targetX = gCurrentActor->x;
    gBehaviourWorkState->targetY = gCurrentActor->y;
    gBehaviourWorkState->targetZ = gCurrentActor->z;
    zoneEntryGetPosition(1, 0x20, &gPrimaryPlayerActor->x, &gPrimaryPlayerActor->y, &gPrimaryPlayerActor->z);
    gPrimaryPlayerActor->yaw = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, gPrimaryPlayerActor->x, gPrimaryPlayerActor->z);
    gCurrentActor->moveYaw = gCurrentActor->yaw = gPrimaryPlayerActor->yaw + 0x800;
    actorScriptStart(gCurrentActor, 0x3F9);
    if (camIsCutsceneActive() != 0) {
        camEndPath(gCamActor);
    }
    camSetTarget(gCamActor, gPrimaryPlayerActor, 4, 0x800, 0x5A, 0, 0x46, 0x64, 0x3A, 0, 0.3f);
}

void bossKRoolChunkyResetPhase(BossScriptState *scriptState) {
    bossSetCannonsVisible(0);
    gActivePlayerState->stateFlags2 = 0;
    if (gPrimaryPlayerActor->state != 0x36) {
        playerResumeLocomotion(gPrimaryPlayerActor);
    }
    camReturnToFollow(gCamActor, gPrimaryPlayerActor);
    gActivePlayerState->scaleChangeRate = 0.01f;
    csModelStateSetFirstByte(0xB, (scriptState->phase < 1) ? 0 : 4);
    csModelStateSetFirstByte(0xC, (scriptState->phase < 2) ? 0 : 4);
    csModelStateSetFirstByte(0xD, (scriptState->phase < 3) ? 0 : 4);
    csModelStateSetFirstByte(0xE, (scriptState->phase < 4) ? 0 : 4);
    csModelStateSetFirstByte(0xA, 0xA);
}

void bossKRoolChunkyInterpolatePosition(f32 stepRate) {
    gCurrentActor->x = (gPrimaryPlayerActor->x - gBehaviourWorkState->targetX) * gCurrentActor->splineT + gBehaviourWorkState->targetX;
    gCurrentActor->y = (gPrimaryPlayerActor->y - gBehaviourWorkState->targetY) * gCurrentActor->splineT + gBehaviourWorkState->targetY;
    gCurrentActor->z = (gPrimaryPlayerActor->z - gBehaviourWorkState->targetZ) * gCurrentActor->splineT + gBehaviourWorkState->targetZ;
    gCurrentActor->splineT += stepRate;
    if (gCurrentActor->splineT > 0.8) {
        gCurrentActor->splineT = 0.8;
    }
}

void bossKRoolChunkyOscillateSway(void) {
    s32 pad[1];
    f32 sinOffset;
    sinOffset = mathSinF(gCurrentActor->splineT * 10240.0);
    gCurrentActor->x += (80.0f * mathSinF(gCurrentActor->yaw + 0x400)) * sinOffset;
    sinOffset = mathSinF(gCurrentActor->splineT * 10240.0);
    gCurrentActor->z += (80.0f * mathCosF(gCurrentActor->yaw + 0x400)) * sinOffset;
}

void bossKRoolChunkyPlayTauntSfx(void) {
    gBehaviourWorkState->flags |= 1;
    sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x2E2, 0xFF, 0x65, 0, 0, 0.0f, 0);
}

extern u8 sKRoolChunkyScriptPhase0[];
extern u8 sKRoolChunkyScriptLate[];

// C920's .data (0x80035AC0-0x80035AF4; the TU ends here, DAA0's data starts 16-aligned at 0x80035B00)
u8 *sKRoolChunkyPhaseScripts[4] = { sKRoolChunkyScriptPhase0, sKRoolChunkyScriptLate, sKRoolChunkyScriptLate, sKRoolChunkyScriptLate };
u8 sKRoolChunkyPathGroupState[4] = { 3, 0, 2, 1 };
f32 sKRoolChunkyPhaseApproachRate[4] = { 0.015f, 0.025f, 0.03f, 0.01f };
f32 sKRoolChunkyPhaseRampTarget[4] = { 1.0f, 1.3f, 1.8f, 0.7f };

void bossKRoolChunkyStep(void) {
    BossScriptState *scriptState;
    u8 *scriptOpcodes;
    s16 waypointCoords[3];

    scriptState = ((BossKRoolChunkyActor *)gCurrentActor)->scriptState;
    scriptOpcodes = sKRoolChunkyPhaseScripts[scriptState->phase];
    behaviourFrameBegin();
    bossRoundFrame(scriptOpcodes);
    if (!(gCurrentActor->flags & 0x10)) {
        camSetSecondTarget(gCamActor, 0, 0);
        gCurrentActor->unk146 = 5;
        gCurrentActor->state = 0x1E;
        gCurrentActor->unk155 = 0;
        gCurrentActor->floorNodeId = 0;
        func_80724CA4(2, 1);
        gCurrentActor->attachMode = 0;
        gCurrentActor->flags &= ~0x8000;
        playerSetLargeModeScale(0.45f);
        bossSetCannonsVisible(0);
        flagSet(0x5F, 0, 2);
    }
    if (gBehaviourWorkState->flags & 1) {
        gCurrentActor->alpha -= (scriptState->phase > 0) ? 10 : 5;
        if (gCurrentActor->alpha < 0) {
            gCurrentActor->alpha = 0;
            gBehaviourWorkState->flags &= ~1;
        }
    } else if (gCurrentActor->state != 0x29 && (gActivePlayerState->stateFlags & 0x40) && gCurrentActor->alpha < 0xFF) {
        if (!(gBehaviourWorkState->flags & 0x8000)) {
            camStartPath(gCurrentActor, 2, 1);
            gBehaviourWorkState->flags |= 0x8000;
        } else {
            csSendActorMessagePayload(2, 0);
        }
        gCurrentActor->alpha += 5;
        if (gCurrentActor->alpha >= 0x100) {
            gCurrentActor->alpha = 0xFF;
        }
    }
    if (gPlayerSlots->unk2C0 != 1 && (gCurrentActor->state == 0x42 || gCurrentActor->state == 0x27)) {
        gCurrentActor->unk144 = 1;
        actorSetTargetSpeed(gCurrentActor, 0);
        gCurrentActor->state = 0x29;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unk155 = 1;
    }
    switch (gCurrentActor->state) {
    case 0x29:
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0x309, 0.0f);
            break;
        case 1:
            if (scriptState->phase >= 2) {
                bossKRoolChunkyPlayTauntSfx();
            }
            gCurrentActor->interactionType = 4;
            bossKRoolChunkySetupFight(scriptState);
            scriptSetActorRampTarget(gCurrentActor, sKRoolChunkyPhaseRampTarget[scriptState->phase], 0.0f);
            gCurrentActor->unk155++;
            break;
        case 3:
            gCurrentActor->splineT = 0.0;
            gCurrentActor->unk155++;
            /* fallthrough */
        case 4:
            bossKRoolChunkyInterpolatePosition(sKRoolChunkyPhaseApproachRate[scriptState->phase]);
            if (scriptState->phase == 3) {
                bossKRoolChunkyOscillateSway();
            }
            break;
        case 5:
            gCurrentActor->unk155++;
            break;
        case 6:
            if (gActorGlobalState.bossFightPhase == 5 && gPrimaryPlayerActor->state == 0x24 && gCurrentActor->splineT > 0.79) {
                if (scriptState->phase == 3) {
                    gCurrentActor->state = 0x37;
                    gCurrentActor->unk155 = 0;
                    actorScriptStart(gPrimaryPlayerActor, 0);
                    actorScriptStart(gCurrentActor, 0);
                    camStartPath(gCurrentActor, 0x16, 1);
                    flagSet(0x1B0, 1, 0);
                } else {
                    gCurrentActor->alpha = 0xFF;
                    gCurrentActor->interactionType = 1;
                    gCurrentActor->unk155 = 8;
                    camStartPath(gCurrentActor, 0x17, 1);
                    actorScriptStart(gCurrentActor, 0);
                }
                csSendActorMessagePayload(2, 0xFF);
            }
            bossKRoolChunkyInterpolatePosition(sKRoolChunkyPhaseApproachRate[scriptState->phase]);
            if (scriptState->phase == 3) {
                bossKRoolChunkyOscillateSway();
            }
            break;
        case 7:
            gCurrentActor->alpha = 0xFF;
            gActivePlayerState->surfaceTimer = 0x12C;
            camStartPath(gCurrentActor, 0x18, 1);
            csSendActorMessagePayload(2, 0xFF);
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
            actorScriptStart(gCurrentActor, 0);
            gCurrentActor->unk155 = 0xA;
            break;
        case 8:
            if (camIsCutsceneActive() == 0) {
                gCurrentActor->unk155++;
            }
            break;
        case 9:
            scriptState->scriptPos = 0;
            scriptState->phase++;
            scriptOpcodes = sKRoolChunkyPhaseScripts[scriptState->phase];
            /* fallthrough */
        case 10:
        case 11:
        case 12:
            if (camIsCutsceneActive() == 0) {
                playerSetSizeMode(gPrimaryPlayerActor, 1);
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
                if (gCurrentActor->interactionType != 1) {
                    if (func_806C9974(0, -1) != 0) {
                        actorScriptStartByIndex(gPrimaryPlayerActor, 0x27);
                        gPrimaryPlayerActor->state = 0x36;
                        gPrimaryPlayerActor->unk155 = 0;
                    }
                    gCurrentActor->interactionType = 1;
                    scriptState->scriptPos = scriptState->loopPos;
                }
                bossKRoolChunkyResetPhase(scriptState);
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
                scriptState->scriptPos++;
                gCurrentActor->unk155 = 0;
                actorScriptStart(gCurrentActor, 0x3E4);
                bossKRoolChunkyPlayTauntSfx();
            }
            break;
        }
        break;
    case 0x28:
        bossKRoolChunkyPlayTauntSfx();
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
        scriptState->scriptPos++;
        gCurrentActor->unk155 = 0;
        break;
    case 0x27:
        switch (gCurrentActor->unk155) {
        case 0:
            patrolGetNextWaypointPos(&waypointCoords[2], &waypointCoords[1], &waypointCoords[0]);
            actorSetGroupState(sKRoolChunkyPathGroupState[gBehaviourAnimState->path[gBehaviourWorkState->unk25 & 0x7F][0] - 1], 1);
            gCurrentActor->unkEC = mathAngleBetweenPoints2D(waypointCoords[2], waypointCoords[0], gCurrentActor->x, gCurrentActor->z);
            if (mathAngleSignedDistance(gCurrentActor->yaw, gCurrentActor->unkEC) < 0) {
                actorScriptStart(gCurrentActor, 0x401);
            } else {
                actorScriptStart(gCurrentActor, 0x402);
            }
            actorSetTargetSpeed(gCurrentActor, 0);
            gCurrentActor->unk155++;
            break;
        case 1:
            gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gCurrentActor->unkEC + 0x800, 10.0f);
            actorMoveWithinZone(0, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0x309, 0.0f);
            break;
        case 2:
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            gCurrentActor->speedXZ = -150.0f;
            gCurrentActor->unk155++;
            /* fallthrough */
        case 3:
            actorMoveWithinZone(0, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0x309, 0.0f);
            break;
        case 4:
            gCurrentActor->speedXZ *= -1.0f;
            gCurrentActor->yaw += 0x800;
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
            scriptState->scriptPos++;
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x1E:
        scriptState->phase = 0;
        scriptState->scriptPos = 0;
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
        scriptState->scriptPos++;
        gCurrentActor->unk155 = 0;
        gCurrentActor->speedXZ = gBehaviourExtraState->targetSpeed;
        break;
    case 0:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x3EA);
            gCurrentActor->unk155++;
            break;
        case 2:
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
            scriptState->scriptPos++;
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                gPrimaryPlayerActor->flags &= ~4;
                camStartPath(gCurrentActor, 0x1A, 1);
                gCurrentActor->unk155++;
            }
            break;
        }
        break;
    default:
        bossScriptStep(scriptOpcodes, 0x19, 0.0f);
        break;
    }
    if (gCurrentActor->flags & 4) {
        billboardSetFlags(1);
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x3C, 0x3C, 1, 0x12C, 0xB4, 0, 1.0f);
    }
    if (func_8072881C(0, &gBehaviourWorkState->unk28) != 0) {
        func_8072881C(0x81, &gBehaviourWorkState->unk28);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/sKRoolChunkyScriptPhase0.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/C920/sKRoolChunkyScriptLate.s")
