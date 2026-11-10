#include "common.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_playerApplyGravityAndMotion // FAKE: callee prototype steer (owner takes no parameter; the extra argument steers a0)
#include "proto/global/103AB0.h"
#include "proto/global/10D2D0.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/2DE90.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/450.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8D3E0.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/ACDC0.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/D5E10.h"
#include "proto/global/E4090.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F93B0.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;

// The player's actor is larger than the shared Actor.
typedef struct ActorExt {
    /* 0x000 */ u8 pad0[0x4];
    /* 0x004 */ ActorSub4 *sub4;
    /* 0x008 */ u8 pad8[0x170];
    /* 0x178 */ void *unk178;
} ActorExt;

#define ACTOR_EXT ((ActorExt *)gCurrentActor)

// One per-player 0x34-byte slot of gPlayerPadState, anchored at a field offset (the
// original references the fields through these labels, not through gPlayerPadState).
typedef struct PadU16Slot {
    /* 0x00 */ u16 value;
    /* 0x02 */ u8 pad2[0x32];
} PadU16Slot;

extern PadU16Slot D_807FD63C[];

extern u32 gGlobalPauseFlags;
extern PadU16Slot D_807FD63A[];

void playerStateCarried(void) {
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    playerInputUpdate(0xB);
    gActivePlayerActor->speedXZ = gActivePlayerState->maxSpeed;
    gActivePlayerActor->moveYaw = gActivePlayerState->targetYaw;
    gActivePlayerActor->yaw = gActivePlayerState->targetYaw;
    playerApplyMotionWithHorizontalVelocity();
    if (!(D_807FD63A[gCurrentPlayerIndex].value & 0x200C)) {
        playerResumeLocomotion(gCurrentActor);
        actorSetInteractionTimer(gCurrentActor);
    } else {
        gCurrentActor->unk144 = 1;
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
    switch (gCurrentActor->unk155) {
        case 0:
            gActivePlayerState->unk24 = 0;
            gActivePlayerState->targetSpeed = 100.0f;
            playerInputUpdate(0x67);
            playerApplyMotionWithHorizontalVelocity();
            gCurrentActor->unk155++;
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

void playerApplyGravityAndMotion();

void playerStateSurfaceDiving(void) {
    Actor *a;

    gActivePlayerState->unk24 = 0;
    if (gCurrentActor->unk155 == 0) {
        gActivePlayerState->turnRate = 0xA;
        gCurrentActor->accelY = -8.0f;
        gCurrentActor->roll = mathAngleFromVector2D(gCurrentActor->speedXZ, gCurrentActor->speedY);
        mathAngleStepToward(&gCurrentActor->pitch, 0, 0x32);
        mathAngleStepToward(&gCurrentActor->roll, (s16)mathAngleFromVector2D(gCurrentActor->speedXZ, gCurrentActor->speedY), 0xA);
        playerInputUpdate(0x6A);
        a = gCurrentActor;
        a->moveYaw = a->yaw;
        playerApplyGravityAndMotion(a);
    }
    if ((gCurrentActor->y + 4.0f < gCurrentActor->waterY) && (gCurrentActor->speedY < 0.0f)) {
        gCurrentActor->state = 0x7F;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->slideSpeed = 2.0f;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 D_80753AFC[];
extern s16 D_80753A78[];

void playerStateUnderwaterSwimming(void) {
    f64 scaledXZ;
    f64 scaledY;
    f32 step;

    gActivePlayerState->unk24++;
    gActivePlayerState->airAccel = D_80753AFC[gCurrentCharacterIndex];
    switch (gCurrentActor->unk155) {
        case 0:
            playerInputUpdate(0x4C);
            step = -gCurrentActor->speedY * 0.125;
            gCurrentActor->speedY = mathApproachF32(gCurrentActor->speedY, 0.0f, step);
            if (gActivePlayerState->unk24 >= 6) {
                if ((gCurrentActor->speedXZ != 0.0f) || (gActivePlayerState->actionTimer != 0)) {
                    gCurrentActor->unk155 = 3;
                } else {
                    gCurrentActor->unk155 = 2;
                }
                gCurrentActor->sub4->scriptWaitFlags &= ~0x4000;
            }
            playerDecelerateAndApplyMotion();
            break;
        case 1:
            mathAngleStepToward(&gCurrentActor->roll, (s16)mathAngleFromVector2D(gCurrentActor->speedXZ, gCurrentActor->speedY), 0x32);
            gActivePlayerState->targetSpeed = 500.0f;
            playerInputUpdate(0x57);
            playerApplyDecelVelocityVector(0.0f);
            if (gActivePlayerState->actionTimer == 0) {
                gCurrentActor->unk155 = 3;
            }
            break;
        case 2:
            playerInputUpdate(0x55);
            playerApplyDecelVelocityVector(0.0f);
            if (gCurrentActor->state == 0x7F) {
                if (gCurrentActor->speedXZ != 0.0f) {
                    gActivePlayerState->unk18 = 0;
                    gCurrentActor->unk155 = 3;
                } else {
                    if (gActivePlayerState->unk50 != 0) {
                        gActivePlayerState->unk50--;
                        if (gActivePlayerState->unk50 == 0) {
                            actorScriptStart(gCurrentActor, 0x315);
                        }
                    }
                }
                if (gCurrentActor->waterY < gCurrentActor->y + 4.0f) {
                    gCurrentActor->state = 0x7E;
                    gCurrentActor->unk155 = 0;
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
                gActivePlayerState->unk50 = D_80753A78[gCurrentCharacterIndex];
                scriptSetActorRampTarget(gCurrentActor, 0.5f, gActivePlayerState->unk50);
                gCurrentActor->unk155 = 2;
            }
            if (gCurrentActor->waterY < gCurrentActor->y + 4.0f) {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x10, 0xFF, 0x7F, 1);
                if (gCurrentActor->speedY > 150.0f) {
                    gCurrentActor->state = 0x82;
                    gCurrentActor->unk155 = 0;
                    actorScriptStart(gCurrentActor, 0);
                } else {
                    gCurrentActor->state = 0x7E;
                    gCurrentActor->unk155 = 0;
                }
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateUnderwaterTurn(void) {
    gCurrentActor->speedY = mathApproachF32(gCurrentActor->speedY, 50.0f, 4.0f);
    switch (gCurrentActor->unk155) {
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
                gCurrentActor->unk155 = 0;
            } else {
                gCurrentActor->state = 0x7F;
                gCurrentActor->unk155 = 0;
            }
            break;
    }
    playerClampYAboveFloor();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateUnderwaterCharge(void) {
    switch (gCurrentActor->unk155) {
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
                gCurrentActor->unk155 = 0;
                actorScriptStart(gCurrentActor, 0x317);
            } else {
                gCurrentActor->state = 0x7F;
                gCurrentActor->unk155 = 3;
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
    if ((currentActorTestClearFlag() != 0) || (gCurrentActor->unk155 == 1) || --gActivePlayerState->unk23C == 0) {
        mapTransitionToMenuOrPrevious();
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void playerStateExitTransition(void) {
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->decelRate = 20.0f;
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    playerApplyFullPhysics();
    if (gCurrentActor->unk155 != 0) {
        mapTransitionToPreviousOrExit();
        gCurrentActor->unk155++;
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
    if ((currentActorTestClearFlag() != 0) || --gActivePlayerState->unk23C == 0) {
        hudSpawnTextScreen(0);
        gCurrentActor->unk155++;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct NmD5E10aTbl {
    s16 unk0[3];
} NmD5E10aTbl;

extern NmD5E10aTbl D_80750FB0;

void playerStateSquishDeath(void) {
    s16 out[2];
    s32 r;
    s32 pad;
    NmD5E10aTbl table = D_80750FB0;

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
    if ((currentActorTestClearFlag() != 0) || --gActivePlayerState->unk23C == 0) {
        if (menuIsTransitionTypeD() == 0) {
            r = func_80600340(table.unk0, 3, out);
            actorListSetCustomFloat(out[1], r, 7, 2.0f);
        }
        mapTransitionToPreviousOrExit();
        gCurrentActor->unk155++;
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
    if (gCurrentActor->unk155 == 0) {
        actorScriptStartByIndex(gCurrentActor, 0);
        gCurrentActor->unk155 = 1;
        gCurrentActor->flags &= ~4;
    }
}

void playerInputUpdate1(void) {
    playerInputUpdate(1);
}

void playerInputUpdate62(void) {
    playerInputUpdate(0x62);
    switch (gCurrentActor->unk155) {
        case 1:
        case 2:
            gCurrentActor->unk155++;
            break;
        case 0:
        case 0x3C:
        case 0x3D:
            break;
        default:
            gCurrentActor->unk155++;
    }
}

void actorRegisterCurrentActorGlobalCallback(void *callbackFn) {
    ActorCallbackNode *node;

    node = heapAlloc(0x14);
    node->callback = callbackFn;
    node->source = gActivePlayerActor;
    node->unk4 = 1;
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
                gCurrentActor->unk155++;
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
    switch (gCurrentActor->unk155) {
        case 0:
            playerInputUpdate(0x5E);
            playerApplyGravityAndMotion();
            return;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            gCurrentActor->unk155++;
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
        if ((currentActorTestClearFlag() != 0) || (gCurrentActor->unk155 != 0)) {
            mapTransitionToMenuOrPrevious();
        }
    }
}

void playerStateRidingActor(void) {
    s16 *counter;

    counter = gActivePlayerState->actor->customState;
    if (gCurrentActor->unk155 != 0) {
        gCurrentActor->state = 0x6D;
        gCurrentActor->unk155 = 0;
    } else {
        playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    }
    *counter += gActivePlayerState->unkC2;
    if (gActivePlayerState->unkC2 >= 8) {
        gActivePlayerState->unkC2 -= 7;
    } else if (gActivePlayerState->unkC2 < -7) {
        gActivePlayerState->unkC2 += 7;
    } else {
        gActivePlayerState->unkC2 = 0;
    }
    playerSyncParentAndInputUpdate(1);
}

void playerInputUpdate64(void) {
    playerSyncParentAndInputUpdate(0x64);
}

void playerInputUpdateWaitC9(void) {
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (gCurrentActor->unk155++ >= 0xC9) {
        playerResumeLocomotion(gCurrentActor);
    }
}

typedef struct G09Sub568 {
    /* 0x0 */ u8 pad0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
} G09Sub568;

extern G09Sub568 *D_807FD568;

void playerRegisterWeaponHudRenderCallback(s16 inputId) {
    if ((gActivePlayerState->gunDrawn != 0) && (hudCanRender() != 0)) {
        if (D_807FD568->unk2 == 7) {
            inputId = 0xF;
            renderCallbacksRegister(&func_806FF75C, gCurrentActor, 5);
        } else {
            inputId = 0xE;
            renderCallbacksRegister(&func_806FF01C, gCurrentActor, 5);
        }
    }
    if (gCurrentActor->unk155 != 0) {
        inputId = 5;
        gCurrentActor->unk155--;
    }
    playerInputUpdate(inputId);
}

void playerRegisterInstrumentHudRenderCallback(s16 inputId) {
    if (gCurrentActor->unk155 != 0) {
        inputId = 5;
        gCurrentActor->unk155--;
    }
    if (hudCanRender() != 0) {
        if (playerInputUpdate(inputId) == 0) {
            renderCallbacksRegister(&func_806FF358, gCurrentActor, 3);
        }
        renderCallbacksRegister(&func_806FF32C, gCurrentActor, 3);
    }
}

void playerRegisterCameraHudRenderCallback(s16 nextState) {
    playerInputUpdate(1);
    if (gCurrentActor->unk155 < 6) {
        renderCallbacksRegister(&func_806FFB2C, gCurrentActor, 3);
        gCurrentActor->unk155++;
    } else {
        gCurrentActor->state = nextState;
        gCurrentActor->unk155 = 0;
    }
    if (gCurrentActor->unk155 == 2) {
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

extern u8 D_807463B8;

void playerInputUpdateCaseC(void) {
    playerRegisterWeaponHudRenderCallback(0xC);
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
    if ((camIsCutsceneActive() != 0) && (gCurrentActor->soundSlots[0] != -1)) {
        sfxStopSlotSound(gCurrentActor, 0);
    }
    if (D_807463B8 == 3) {
        playerCheckAndResetCarriedActor(gCurrentActor);
    }
}

void playerInputUpdateCase10(void) {
    playerRegisterInstrumentHudRenderCallback(0x10);
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
    if (D_807463B8 == 3) {
        playerCheckAndResetCarriedActor(gCurrentActor);
    }
}

extern f32 D_80753A5C[];

void playerInputUpdateCaseD(void) {
    gActivePlayerState->airAccel = D_80753AFC[gCurrentCharacterIndex];
    playerRegisterWeaponHudRenderCallback(0xD);
    playerApplyDecelVelocityVector(D_80753A5C[gCurrentCharacterIndex]);
    if (playerCanPerformActionCheck() != 0) {
        func_806EAB44(gCurrentActor, 1);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerInputUpdateCase11(void) {
    gActivePlayerState->airAccel = D_80753AFC[gCurrentCharacterIndex];
    playerRegisterInstrumentHudRenderCallback(0x11);
    playerApplyDecelVelocityVector(D_80753A5C[gCurrentCharacterIndex]);
    if (playerCanPerformActionCheck() != 0) {
        func_806EAB44(gCurrentActor, 1);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u32 gFrameCounter;

void playerStateClimbTree(void) {
    s32 sel = 0x13;

    gCurrentActor->moveYaw = gCurrentActor->yaw;
    gCurrentActor->renderFlags |= 0x200;
    if (gCurrentActor->unk155 != 0) {
        gCurrentActor->unk155--;
        sel = 0x14;
    }
    if ((gFrameCounter >= 2) && (playerInputUpdate(sel) == 0)) {
        s16 temp = playerSelectWalkRunState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);

        if (temp != 0xC) {
            gCurrentActor->state = temp;
            gCurrentActor->unk155 = 0;
        }
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 D_807536E4[];
extern s32 gGlobalCutsceneFlags;

void playerStateVineSwing(void) {
    f32 v;
    f32 r;
    s32 sel;

    if (gGlobalCutsceneFlags & 2) {
        f64 t = (gCurrentActor->y - 120.0f) * 0.5;

        v = (t > 0.0) ? t : 0.0;
        if (gCurrentActor->x < 590.0f - v) {
            gCurrentActor->x = 590.0f - v;
        }
        if (987.0f + v < gCurrentActor->x) {
            gCurrentActor->x = 987.0f + v;
        }
        if (gCurrentActor->z < 571.0f - v) {
            gCurrentActor->z = 571.0f - v;
        }
        if (965.0f + v < gCurrentActor->z) {
            gCurrentActor->z = 965.0f + v;
        }
        gCurrentActor->unk144 &= 0xFFF7;
    }
    playerInputUpdate(0x1B);
    r = mapGetVoidHeightForCharacter(gPrimaryPlayerActor->chunkIndex);
    if (r < gCurrentActor->y) {
        gCurrentActor->accelY = D_807536E4[gCurrentCharacterIndex];
        if (gCurrentActor->speedY > 0.0f) {
            gCurrentActor->speedY = gCurrentActor->speedY * 0.7;
        }
    }
    if (gActivePlayerState->unk1A2 != 0) {
        s32 x = gActivePlayerState->unk1A0;

        if (x >= 0x8000) {
            x -= 0x10000;
        }
        x += 0x9E8;
        if (x >= 0x7D1) {
            sel = 0x7D;
        } else if (x < -0x7D0) {
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
    if ((gActivePlayerState->stateFlags & 0x40000000) && (gActivePlayerState->unk240 == 0)) {
        func_80687400();
        gActivePlayerState->unk240 = 0x1E;
    }
    if (gActivePlayerState->unk240 != 0) {
        gActivePlayerState->unk240--;
    }
    if ((gCurrentActor->contactFlags & 1) || (gActivePlayerState->unk240 == 1)) {
        if (gGlobalCutsceneFlags & 2) {
            gCurrentActor->unk144 |= 8;
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
        s16 temp = playerSelectCarryState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);

        if (temp != 0x5D) {
            gCurrentActor->state = temp;
            gCurrentActor->unk155 = 0;
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

extern f32 D_807531E0[];

void playerStateClimbLadder(void) {
    if (gCurrentActor->unk155 == 0) {
        gCurrentActor->unk155++;
        gActivePlayerState->unkC = -1;
        gActivePlayerState->unkE = -1;
    }
    if (playerInputUpdate(0x13) == 0) {
        s16 temp = playerSelectWalkRunState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);

        if (temp != 0xD) {
            gCurrentActor->state = temp;
            gCurrentActor->unk155 = 0;
        }
    }
    if ((camIsCutsceneActive() == 0) && (D_807531E0[gCurrentCharacterIndex] < gCurrentActor->speedXZ) && (D_807531E0[gCurrentCharacterIndex] < gActivePlayerState->maxSpeed) &&
        (gActivePlayerState->unkC >= 0) && (mathAngleDistance(gActivePlayerState->unkC, gActivePlayerState->targetYaw) >= 0x401) &&
        (mathAngleDistance(gCurrentActor->moveYaw, gActivePlayerState->targetYaw) >= 0x539)) {
        gCurrentActor->state = 0xE;
        gCurrentActor->unk155 = 0;
        playerApplyGravityAndMotion();
    } else {
        playerApplyFullPhysics();
    }
    gActivePlayerState->unkC = gActivePlayerState->unkE;
    gActivePlayerState->unkE = gActivePlayerState->targetYaw;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSlideDownLadder(void) {
    if (playerInputUpdate(0x1C) == 0) {
        s16 temp = playerSelectCarryState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);

        if (temp != 0x5E) {
            gCurrentActor->state = temp;
            gCurrentActor->unk155 = 0;
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

extern s32 gGlobalOverlayFlags;

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
    switch (gCurrentActor->unk155) {
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
    switch (gCurrentActor->unk155) {
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
    if (gCurrentActor->unk155 == 0) {
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
    func_80685210(0.5f, 0x64, 5);
    gCurrentActor->unkF8 = 0x12C;
    if ((gCurrentActor->y - gCurrentActor->floorY) > 5.0f) {
        if (gCurrentActor->accelY == -260.0f) {
            playerSetBaseGravity();
        } else if (gCurrentActor->accelY != -30.0f) {
            gCurrentActor->contactFlags |= 0x1000;
        } else {
            gCurrentActor->speedY = (gCurrentActor->speedY > 0.0f) ? 0.0f : gCurrentActor->speedY;
        }
        gCurrentActor->state = 0x14;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->jumpVelocityY = gCurrentActor->speedY;
        gActivePlayerState->unk50 = 0;
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
    if (gCurrentActor->unk155 == 0) {
        camSetTarget(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, 0x32, 0, 5, 0x32, 0x14, 0, 0.2f);
        gCurrentActor->unk155++;
    }
    playerApplyImpactRumble(0x3D);
}

void playerStateSlide(void) {
    playerApplyImpactRumble(0x3D);
}

typedef struct PlayerCustomState {
    /* 0x00 */ u8 pad0[0x45];
    /* 0x45 */ u8 unk45;
} PlayerCustomState;

typedef struct PadF32Slot {
    /* 0x00 */ f32 value;
    /* 0x04 */ u8 pad4[0x30];
} PadF32Slot;

extern PadF32Slot D_807FD618[];

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
    gCurrentActor->unk155++;
    if (gCurrentActor->unk155 == 0x32) {
        PlayerCustomState *e = gActivePlayerState->actor->customState;
        e->unk45 = 1;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSlideFall(void) {
    playerInputUpdate(0x3E);
    playerApplyFullPhysics();
    switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            gCurrentActor->unk155++;
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
                gCurrentActor->unk155 = 0;
                actorScriptStartByIndex(gCurrentActor, 0x5E);
            } else {
                playerUpdateFallTimer();
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSlideBrake(void) {
    func_80685210(0.5f, 0x64, 5);
    playerInputUpdate(0x3C);
    playerApplyFullPhysics();
    if (gCurrentActor->speedXZ == 0.0f && gCurrentActor->floorSlopeFactor == 0.0f) {
        playerResumeLocomotion(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSlideReverse(void) {
    func_80685210(0.5f, 0x64, 5);
    playerInputUpdate(0x3B);
    playerApplyFullPhysics();
    if (gCurrentActor->speedXZ == 0.0f && gCurrentActor->floorSlopeFactor == 0.0f) {
        playerResumeLocomotion(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 D_8075327C[];
extern s16 D_80753298[];

void playerStateSkidTurn(void) {
    switch (gCurrentActor->unk155) {
        case 0:
            playerInputUpdate(0x41);
            actorScriptStartByIndex(gCurrentActor, 5);
            gActivePlayerState->decelRate = D_8075327C[gCurrentCharacterIndex];
            playerApplyDeceleration();
            playerApplyGravityAndMotion();
            gCurrentActor->unk155++;
            break;
        case 1:
            playerInputUpdate(0x41);
            playerApplyDeceleration();
            playerApplyGravityAndMotion();
            break;
        case 2:
            playerInputUpdate(0x41);
            playerApplyDeceleration();
            mathAngleStepTowardThreshold(&gCurrentActor->yaw, gActivePlayerState->targetYaw, D_80753298[gCurrentCharacterIndex], 0xC00);
            playerApplyGravityAndMotion();
            break;
        case 3:
            playerInputUpdate(0x41);
            mathAngleStepTowardThreshold(&gCurrentActor->yaw, gActivePlayerState->targetYaw, D_80753298[gCurrentCharacterIndex], 0xC00);
            if (gActivePlayerState->maxSpeed == 0.0f) {
                playerResumeLocomotion(gCurrentActor);
            }
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerUpdateTargetYawFromStick(void) {
    if (D_807FD618[gCurrentPlayerIndex].value != 0.0f) {
        gCurrentActor->unkEA = gActivePlayerState->targetYaw;
    } else {
        gCurrentActor->unkEA = gCurrentActor->yaw;
    }
}

extern u8 gPlayerCharacterId[];
extern s32 D_80767CC0;
extern f32 D_80753604[];

void playerStateDoubleJump(void) {
    switch (gCurrentActor->unk155) {
        case 0:
            playerInputUpdate(0x2C);
            playerApplyFullPhysics();
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            playerUpdateTargetYawFromStick();
            gCurrentActor->unk155++;
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
            if (D_807FD63C[gCurrentPlayerIndex].value & 0x8000) {
                gActivePlayerState->jumpTimer = D_80767CC0;
            }
            if ((u32)(D_80767CC0 - gActivePlayerState->jumpTimer) < 0xA && gPlayerCharacterId[gCurrentPlayerIndex] == 1 && gCurrentActor->floorSlopeFactor == 0.0f) {
                gCurrentActor->state = 0x1A;
                gCurrentActor->unk155 = 0;
                gActivePlayerState->jumpVelocityY = D_80753604[gCurrentCharacterIndex];
                gActivePlayerState->unk50 = 0;
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

extern f32 D_80753234[];

void playerStateLongJump(void) {
    switch (gCurrentActor->unk155) {
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
                gCurrentActor->unkEA = gCurrentActor->yaw;
            } else {
                playerUpdateTargetYawFromStick();
                playerApplyFullPhysics();
            }
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            gCurrentActor->unk155++;
            playerInputUpdate(0x21);
            playerSetBaseGravityIfFalling();
            break;
        case 2:
            if (gActivePlayerState->airTimer != 0) {
                gActivePlayerState->airAccel = 0.0f;
                playerApplyFullPhysics();
                gActivePlayerState->airTimer--;
            } else {
                gActivePlayerState->airAccel = D_80753234[gCurrentCharacterIndex];
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
            if (D_807FD63C[gCurrentPlayerIndex].value & 0x8000) {
                gActivePlayerState->jumpTimer = D_80767CC0;
            }
            if ((u32)(D_80767CC0 - gActivePlayerState->jumpTimer) < 0xA && gPlayerCharacterId[gCurrentPlayerIndex] == 1 && gCurrentActor->floorSlopeFactor == 0.0f) {
                gCurrentActor->state = 0x1A;
                gCurrentActor->unk155 = 0;
                gActivePlayerState->jumpVelocityY = D_80753604[gCurrentCharacterIndex];
                gActivePlayerState->unk50 = 0;
                actorScriptStartByIndex(gCurrentActor, 0x13);
            }
            playerInputUpdate(0x30);
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void playerStateLaunchAir(void) {
    switch (gCurrentActor->unk155) {
        case 0:
            playerInputUpdate(0x2C);
            playerApplyFullPhysics();
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            playerUpdateTargetYawFromStick();
            gCurrentActor->unk155++;
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
            gActivePlayerState->unk4C = -1;
            gCurrentActor->state = playerSelectSurfaceState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);
            gCurrentActor->unk155 = 0;
            if (gCurrentActor->state == 0x3F) {
                gCurrentActor->unk155 = 1;
            }
            playerInputUpdate(0x46);
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateApproachVelocity(void) {
    switch (gCurrentActor->unk155) {
        case 0:
            if (gActivePlayerState->approachTimer != 0) {
                if (mathAngleDistance(gCurrentActor->moveYaw, gActivePlayerState->approachYaw)) {} // FAKE: dead if keeps the ignored s32 result out of $v0 (Q0198)
                playerApproachVelocity(gActivePlayerState->approachYaw, 50.0f, gActivePlayerState->targetSpeed);
                gActivePlayerState->approachTimer--;
            }
            playerInputUpdate(0x23);
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 2) {
                gActivePlayerState->maxSpeed = gActivePlayerState->maxSpeed * 0.63;
            }
            playerApplyFullPhysics();
            break;
        case 1:
            playerInputUpdate(0x23);
            switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                case 0:
                case 2:
                    gActivePlayerState->maxSpeed = gActivePlayerState->maxSpeed * 0.63;
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
    switch (gCurrentActor->unk155) {
        case 0:
            playerInputUpdate(0x26);
            playerApplyFullPhysics();
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            playerUpdateTargetYawFromStick();
            gCurrentActor->unk155++;
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
            if (D_807FD63C[gCurrentPlayerIndex].value & 0x8000) {
                gActivePlayerState->jumpTimer = D_80767CC0;
            }
            playerInputUpdate(0x34);
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void playerStateBackflip(void) {
    switch (gCurrentActor->unk155) {
    case 0:
        if (gActivePlayerState->approachTimer != 0) {
            mathAngleDistance(gCurrentActor->moveYaw, gActivePlayerState->approachYaw);
            playerApproachVelocity(gActivePlayerState->approachYaw, 50.0f, gActivePlayerState->targetSpeed);
            gActivePlayerState->approachTimer--;
        }
        playerApplyFullPhysics();
        if (gCurrentActor->speedY <= -15.0f) {
            gCurrentActor->speedY = -15.0f;
            gCurrentActor->unk155++;
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

extern f32 D_80753620[];
extern f32 D_8075363C[];

void playerStateFlapGlide(void) {
    switch (gCurrentActor->unk155) {
    case 0:
        scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
        playerInputUpdate(0x2C);
        playerApplyFullPhysics();
        break;
    case 1:
        gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
        gCurrentActor->accelY = D_8075363C[gCurrentCharacterIndex];
        gCurrentActor->unk155++;
        playerUpdateTargetYawFromStick();
        playerInputUpdate(0x2B);
        gActivePlayerState->targetSpeed = D_80753620[gCurrentCharacterIndex];
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

extern f32 D_80753674[];
extern f32 D_80753690[];
extern f32 D_807536C8[];
extern f32 D_807536E4[];

void playerStateHover(void) {
    playerSpawnJumpTrailEffects();
    switch (gCurrentActor->unk155) {
    case 0:
        scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
        playerInputUpdate(0x2C);
        playerApplyFullPhysics();
        break;
    case 1:
        gCurrentActor->speedY = D_80753674[gCurrentCharacterIndex];
        gCurrentActor->accelY = D_80753690[gCurrentCharacterIndex];
        playerUpdateTargetYawFromStick();
        gCurrentActor->unk155++;
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
        gCurrentActor->accelY = D_807536E4[gCurrentCharacterIndex];
        gCurrentActor->unk155++;
        playerInputUpdate(0x2B);
        gActivePlayerState->targetSpeed = D_807536C8[gCurrentCharacterIndex];
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
    switch (gCurrentActor->unk155) {
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
        gCurrentActor->unk155++;
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
            effectSpawnMultiTierRingWithActor(gCurrentActor, D_807FD568->unk1);
            camStartShake(gActivePlayerState->camActor, 0x14, (u16)(D_807FD568->unk1 * 5));
        }
        scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
        gCurrentActor->unk155++;
        playerApplyGravityAndMotion();
        break;
    case 4:
        playerInputUpdate(0x2E);
        playerApplyGravityAndMotion();
        break;
    case 5:
        playerInputUpdate(0x2F);
        gCurrentActor->unk155++;
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
    switch (gCurrentActor->unk155) {
    case 0:
        gActivePlayerState->decelRate = gActivePlayerState->decelRate / 1.8;
        gCurrentActor->unk155++;
    case 1:
        playerInputUpdate(5);
        playerApplyFullPhysics();
        mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, (s16)(gActivePlayerState->turnRate * 1.25));
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 D_80750FC0;
extern s32 D_80750FC4;
extern s32 D_80750FC8;
extern s32 D_80750FCC;
extern s32 D_80750FD0;
extern u8 D_80750FD4;
extern f32 D_80750FD8;
extern void *D_8074E880[];
extern f32 D_8075352C[];

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

    if (gCurrentActor->unk155 < 2 || D_80750FD8 < gCurrentActor->speedXZ) {
        scale = gCurrentActor->sub4->scaleY / 0.15;
        actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
        for (i = 0; i < D_80750FD4; i++) {
            x = (randomNonNegative() >> 15) % 10000 % D_80750FC8 - D_80750FC8 / 2;
            y = (randomNonNegative() >> 15) % 10000 % D_80750FCC - D_80750FCC / 2;
            z = (randomNonNegative() >> 15) % 10000 % D_80750FD0 - D_80750FD0 / 2;
            effectSetSpeed(D_80750FC4);
            effectSetCallback(&func_80717D4C);
            effectSetDepth(1);
            effectCreateAtPosition(D_8074E880[randomNonNegative() % 10000 % 3], D_80750FC0 * scale, x * scale + nodeX, y * scale + nodeY, z * scale + nodeZ);
        }
    }
    switch (gCurrentActor->unk155) {
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
        gCurrentActor->unk155++;
        break;
    case 2:
        if (gCurrentActor->hasArcBounds != 0) {
            f32 t = D_8075352C[gCurrentCharacterIndex];

            if (t < gCurrentActor->speedXZ && !(gActivePlayerState->stateFlags2 & 8)) {
                gCurrentActor->speedXZ = t;
                gActivePlayerState->slideLaunchSpeed = D_8075352C[gCurrentCharacterIndex];
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
    switch (gCurrentActor->unk155) {
    case 0:
        gActivePlayerState->decelRate = gActivePlayerState->decelRate / 1.8;
        gCurrentActor->unk155++;
        gActivePlayerState->jumpStartTime = D_80767CC0 - 0x64;
        gActivePlayerState->turnRate = 0x50;
    case 1:
        playerInputUpdate(9);
        gActivePlayerState->decelRate = 10.0f;
        playerApplyDeceleration();
        mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, (s16)(gActivePlayerState->turnRate * 1.25));
        break;
    case 2:
        if ((u32)(D_80767CC0 - gActivePlayerState->jumpStartTime) < 0x32) {
            switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                case 2:
                    gCurrentActor->state = 0x27;
                    gCurrentActor->unk155 = 0;
                    actorScriptStartByIndex(gCurrentActor, 0x40);
                    break;
                default:
                    gCurrentActor->state = 0x28;
                    gCurrentActor->unk155 = 0;
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
    switch (gCurrentActor->unk155) {
        case 0:
            gActivePlayerState->decelRate = gActivePlayerState->decelRate / 1.8;
            gCurrentActor->unk155++;
            gActivePlayerState->jumpStartTime = D_80767CC0 - 0x64;
        case 1:
            playerInputUpdate(9);
            gActivePlayerState->decelRate = 10.0f;
            playerApplyDeceleration();
            mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, (s16)(gActivePlayerState->turnRate * 1.25));
            break;
        case 2:
            if ((u32)(D_80767CC0 - gActivePlayerState->jumpStartTime) < 0x32) {
                gCurrentActor->state = 0x28;
                gCurrentActor->unk155 = 0;
                actorScriptStartByIndex(gCurrentActor, 0x41);
            }
            break;
    }
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateBrake(void) {
    switch (gCurrentActor->unk155) {
        case 0:
            gActivePlayerState->decelRate = gActivePlayerState->decelRate / 1.8;
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 3) {
                gCurrentActor->speedXZ = 50.0f;
            }
            gCurrentActor->unk155++;
        case 1:
            playerInputUpdate(0xA);
            mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, (s16)(gActivePlayerState->turnRate * 1.25));
            break;
        case 2:
            playerInputUpdate(0xA);
            gActivePlayerState->decelRate = 50.0f;
            playerApplyDeceleration();
            mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, (s16)(gActivePlayerState->turnRate * 1.25));
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
            switch (gCurrentActor->unk155) {
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
            switch (gCurrentActor->unk155) {
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
                    gCurrentActor->unk155++;
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
            switch (gCurrentActor->unk155) {
                case 0:
                    gActivePlayerState->unk28 = 0;
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
                    gActivePlayerState->unk28 = 1;
                    if ((u32)(D_80767CC0 - gActivePlayerState->jumpStartTime) < 0x14) {
                        gCurrentActor->state = 0x26;
                        gCurrentActor->unk155 = 0;
                        actorScriptStartByIndex(gCurrentActor, 0x3F);
                    }
                    playerInputUpdate(0x15);
                    playerApplyFullPhysics();
                    break;
            }
            break;
        case 6:
            switch (gCurrentActor->unk155) {
                case 0:
                    gActivePlayerState->unk28 = 0;
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
                    gActivePlayerState->unk28 = 1;
                    playerInputUpdate(0x15);
                    playerApplyFullPhysics();
                    break;
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 D_80753558[];
extern s16 D_80753568[];

void playerStateSteepSlide(void) {
    mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
    playerUpdateFallAndStepSounds();
    switch (gCurrentActor->unk155) {
        case 0:
            gActivePlayerState->decelRate = 0.2f;
            gActivePlayerState->airAccel = 10.0f;
            gActivePlayerState->turnRate = 0x32;
            gActivePlayerState->slideLaunchSpeed = D_80753568[gCurrentCharacterIndex];
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
            gCurrentActor->unk155++;
            break;
        case 2:
            playerInputUpdate(0x18);
            playerApproachVelocity(gCurrentActor->yaw, gActivePlayerState->slideLaunchSpeed, gActivePlayerState->slideLaunchSpeed);
            playerApplyGravityAndMotion();
            mathAngleStepToward(&gCurrentActor->moveYaw, gCurrentActor->yaw, gActivePlayerState->turnRate);
            break;
        case 3:
            gActivePlayerState->decelRate = D_80753558[gCurrentCharacterIndex];
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 0) {
                playerInputUpdate(0x19);
            } else {
                playerInputUpdate(0x19);
            }
            playerApplyFullPhysics();
            break;
        case 4:
            gActivePlayerState->decelRate = D_80753558[gCurrentCharacterIndex];
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

extern s16 D_80753548[];

void playerStateDecelMotion(void) {
    playerUpdateFallAndStepSounds();
    switch (gCurrentActor->unk155) {
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
                if (D_8075352C[gCurrentCharacterIndex] < gCurrentActor->speedXZ) {
                    gCurrentActor->speedXZ = D_8075352C[gCurrentCharacterIndex];
                    gActivePlayerState->slideLaunchSpeed = D_8075352C[gCurrentCharacterIndex];
                }
            }
            if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->yaw) == 0) {
                actorScriptStartByIndex(gCurrentActor, 0x49);
                gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) % 4096;
                gCurrentActor->unk155 = 3;
                gCurrentActor->speedXZ = D_8075352C[gCurrentCharacterIndex];
                gActivePlayerState->slideLaunchSpeed = D_8075352C[gCurrentCharacterIndex];
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
                gCurrentActor->unk155++;
                gCurrentActor->speedXZ = D_8075352C[gCurrentCharacterIndex];
                gActivePlayerState->slideLaunchSpeed = D_8075352C[gCurrentCharacterIndex];
                break;
            }
            mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
            playerCheckLandingSfx();
            playerApplyDeceleration();
            playerApplyGravityAndMotion();
            gActivePlayerState->decelRate = D_80753548[gCurrentCharacterIndex];
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
extern s16 D_807538C8[];

s32 playerCheckSlopeLaunchArc(void) {
    if (gCurrentActor->hasArcBounds != 0) {
        if (mathAngleDistance(gCurrentActor->yaw, (s16)(((((gCurrentActor->arcYawMax - gCurrentActor->arcYawMin) & 0xFFF) / 2) + gCurrentActor->arcYawMin + 0x800) & 0xFFF)) < 0x2BC) {
            if (gCurrentActor->speedXZ > 150.0f) {
                actorScriptStartByIndex(gCurrentActor, 0x49);
                gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) % 4096;
                gCurrentActor->unk155 = 2;
                gCurrentActor->speedXZ = D_8075352C[gCurrentCharacterIndex];
                gActivePlayerState->slideLaunchSpeed = D_8075352C[gCurrentCharacterIndex];
            } else {
                playerResumeLocomotion(gCurrentActor);
            }
            return 1;
        }
        mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
    }
    return 0;
}

extern u8 D_8071FF18;

void playerStateSlopeSlideArc(void) {
    playerUpdateFallAndStepSounds();
    switch (gCurrentActor->unk155) {
    case 0:
        gActivePlayerState->unk28 = 0;
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
        gActivePlayerState->decelRate = D_80753548[gCurrentCharacterIndex];
        if (gCurrentActor->speedXZ > 20.0f) {
            if (randomLcgNext() % 3U == 0) {
                effectSetCallback(&effectSineHorizontalDriftUpdate);
                effectSetMode(2);
                effectSetDepth(1);
                effectCreateAtActorBone(&D_8071FF18, 0.2f, gCurrentActor, 2, 0);
            }
            if (randomLcgNext() % 3U == 0) {
                effectSetCallback(&effectSineHorizontalDriftUpdate);
                effectSetMode(2);
                effectSetDepth(1);
                effectCreateAtActorBone(&D_8071FF18, 0.2f, gCurrentActor, 3, 0);
            }
            if (randomLcgNext() % 3U == 0) {
                effectSetCallback(&effectSineHorizontalDriftUpdate);
                effectSetMode(2);
                effectSetDepth(1);
                effectCreateAtActorBone(&D_8071FF18, 0.2f, gCurrentActor, 9, 0);
            }
            if (randomLcgNext() % 3U == 0) {
                effectSetCallback(&effectSineHorizontalDriftUpdate);
                effectSetMode(2);
                effectSetDepth(1);
                effectCreateAtActorBone(&D_8071FF18, 0.2f, gCurrentActor, 0xA, 0);
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
    switch (gCurrentActor->unk155) {
    case 0:
        playerInputUpdate(3);
        gActivePlayerState->maxSpeed = gKongSwimTurnSpeeds[gCurrentCharacterIndex];
        gActivePlayerState->targetYaw = gCurrentActor->moveYaw;
        mathAngleStepToward(&gCurrentActor->yaw, (s16)((gCurrentActor->moveYaw + 0x800) & 0xFFF), (s16)(gActivePlayerState->turnRate * 2));
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
    switch (gCurrentActor->unk155) {
    case 0:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, (s16)(gActivePlayerState->damageSource->yaw + 0x800), 8.0f);
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
    switch (gCurrentActor->unk155) {
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
    gCurrentActor->unk144 = 1;
    gActivePlayerState->maxSpeed = 0.0f;
    gCurrentActor->speedXZ = 0.0f;
    playerApplyFullPhysics();
    if (gActivePlayerState->unk21E == 0) {
        playerRefillHealth(gCurrentActor, gCurrentPlayerIndex);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSwimPaddle(void) {
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    gCurrentActor->renderFlags |= 0x200;
    switch (gCurrentActor->unk155) {
    case 0:
        playerInputUpdate(3);
        gActivePlayerState->maxSpeed = gKongSwimPaddleSpeeds[gCurrentCharacterIndex];
        gActivePlayerState->targetYaw = gCurrentActor->moveYaw;
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, (s16)(gActivePlayerState->damageSource->yaw + 0x800), 8.0f);
        playerApplyFullPhysics();
        break;
    case 1:
        playerInputUpdate(3);
        gActivePlayerState->maxSpeed = 0.0f;
        if (gPlayerCharacterId[gCurrentPlayerIndex] == 4) {
            f32 t = gCurrentActor->sub4->model->frame;

            if (t >= 29.0f && t < 33.0f) {
                gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) & 0xFFF;
                gCurrentActor->speedXZ = 150.0f;
                playerApplyGravityAndMotion();
                break;
            }
            if (t >= 48.0f) {
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
    switch (gCurrentActor->unk155) {
    case 0:
        playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
        playerInputUpdate(4);
        mathAngleStepToward(&gCurrentActor->yaw, (s16)((gCurrentActor->moveYaw + 0x800) & 0xFFF), (s16)(gActivePlayerState->turnRate * 2));
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
    if (gCurrentActor->waterY < D_807538C8[gCurrentCharacterIndex] + gCurrentActor->y) {
        gCurrentActor->y = gCurrentActor->waterY - D_807538C8[gCurrentCharacterIndex];
    }
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->decelRate = 2.0f;
    playerApplyMotionWithHorizontalVelocity();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSurfaceSwimSprint(void) {
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    gCurrentActor->renderFlags |= 0x200;
    switch (gCurrentActor->unk155) {
    case 0:
        gCurrentActor->speedXZ = gKongSwimSpeeds[gCurrentCharacterIndex];
        playerInputUpdate(5);
        gActivePlayerState->maxSpeed = gKongSwimSpeeds[gCurrentCharacterIndex];
        if (gActivePlayerState->isHoldingObject != 0) {
            sfxStopSlotSound(gCurrentActor, 0);
            gActivePlayerState->isHoldingObject = 0;
        }
        gActivePlayerState->targetYaw = gCurrentActor->moveYaw;
        mathAngleStepToward(&gCurrentActor->yaw, (s16)((gCurrentActor->moveYaw + 0x800) & 0xFFF), (s16)(gActivePlayerState->turnRate * 2));
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
    f64 t = gCurrentActor->sub4->scaleY;

    actorSetUniformScale(gCurrentActor, (0.001 - t) * 0.01 + t);
    gCurrentActor->alpha -= 0x14;
    if (gCurrentActor->alpha < 0) {
        gCurrentActor->alpha = 0;
    }
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    switch (gCurrentActor->unk155) {
    case 0:
        playerApplyFullPhysics();
        break;
    case 1:
        playerApplyFullPhysics();
        if (gActivePlayerState->unk11C-- == 0) {
            gCurrentActor->unk155++;
        }
        break;
    case 2:
        if (gCurrentMap != 0x52 && gCurrentMap != 0xE) {
            playerRefillHealth(gCurrentActor, gCurrentPlayerIndex);
        }
        gCurrentActor->unk155++;
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSwimDrift(void) {
    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s32 gGlobalCutsceneFlags;
extern f32 gKongSwimStrokeSpeeds[];
extern f32 D_80753094[];

void playerStateSwimStroke(void) {
    u8 flag;
    u8 timer;

    playerStateQueueCallback(0x3C, 0, gCurrentPlayerIndex);
    playerInputUpdate(1);
    switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->accelY = gKongSwimStrokeSpeeds[gCurrentCharacterIndex];
            if (gGlobalCutsceneFlags & 2) {
                sfxPlayOnFreeSlot(0x424, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
            if (gPlayerCount == 1) {
                camStartPathNearWall(gPrimaryPlayerActor, 0xC, 0x25, 0x85);
            }
            gCurrentActor->unk155++;
        case 1:
            gActivePlayerState->maxSpeed = D_80753094[gCurrentCharacterIndex];
            gActivePlayerState->targetYaw = gCurrentActor->moveYaw;
            mathAngleStepToward(&gCurrentActor->yaw, (s16)((gCurrentActor->moveYaw + 0x800) & 0xFFF), (s16)(gActivePlayerState->turnRate * 2));
            playerApplyFullPhysics();
            gActivePlayerState->unk11C = 0xF;
            gActivePlayerState->unk11D = 0;
            break;
        case 2:
            gCurrentActor->unk155++;
            gCurrentActor->speedXZ = 0.0f;
            playerApplyMotion();
            break;
        case 3:
            flag = func_80714608(0);
            if (gActivePlayerState->unk11C == 0 && gActivePlayerState->unk11D == 0) {
                if (!flag) {
                    playerSpawnSpiralDriftEffects();
                }
                gActivePlayerState->unk11D = 1;
            } else {
                gActivePlayerState->unk11C = gActivePlayerState->unk11C - 1;
            }
            if (gActivePlayerState->unk11D != 0) {
                timer = gActivePlayerState->unk11C;
                if (timer >= 0xBF) {
                    if (!flag && timer % 3 == 0) {
                        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, (s16)(((timer & 2) / 2) + 0x57), 0xFF, 0x7F, 0x1E);
                    }
                } else if (flag) {
                    playerRefillHealth(gCurrentActor, gCurrentPlayerIndex);
                }
            }
            if ((gActivePlayerState->stateFlags & 0x1000) && !(gFrameCounter & 3)) {
                effectSetColor(0x64, 0x64, 0x64, 0xC8);
                effectSetMode(2);
                effectSpawnBoneDefault(gCurrentActor, (s16)(((randomNonNegative() >> 15) % 32767) % 8 + 1), 0.4f, 0.0f, 0.0f, 0.0f, -0x50);
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
    switch (gCurrentActor->unk155) {
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
    s16 v;

    switch (gCurrentActor->unk155) {
        case 0:
            playerInputUpdate(0x46);
            gActivePlayerState->maxSpeed = 0.0f;
            break;
        case 1:
            if (playerInputUpdate(0x46) == 0) {
                v = playerSelectSurfaceState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);
                if (v != 0x3F) {
                    gCurrentActor->state = v;
                    gCurrentActor->unk155 = 0;
                }
            }
            break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateUnderwaterLand(void) {
    s16 r;

    playerCheckLandingSfx();
    if (playerInputUpdate(0x46) == 0) {
        r = playerSelectSurfaceState(gCurrentActor, gCurrentActor->speedXZ, gActivePlayerState->maxSpeed, 1);
        if (r != 0x40) {
            gCurrentActor->state = r;
            gCurrentActor->unk155 = 0;
            if (r == 0x3F) {
                gCurrentActor->unk155 = 1;
            }
        }
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateScriptTransition(void) {
    switch (gCurrentActor->unk155) {
        case 0:
            playerInputUpdate(1);
            break;
        case 1:
            gCurrentActor->state = 0x3C;
            gCurrentActor->unk155 = 1;
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

extern f32 D_80753454[];
extern f32 D_80753470[];
extern f32 D_8075348C[];
extern s16 D_807534A8[];
extern f32 D_80753738[];

void playerStateUnderwaterRamp(void) {
    switch (gCurrentActor->unk155) {
        case 0:
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0);
            playerInputUpdate(0x47);
            playerApplyGravityAndMotion();
            playerApplyDeceleration();
            gActivePlayerState->airAccel = D_80753470[gCurrentCharacterIndex];
            gActivePlayerState->decelRate = D_8075348C[gCurrentCharacterIndex];
            gActivePlayerState->targetSpeed = D_80753454[gCurrentCharacterIndex];
            gActivePlayerState->turnRate = D_807534A8[gCurrentCharacterIndex];
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            gCurrentActor->accelY = D_80753738[gCurrentCharacterIndex];
            gCurrentActor->speedXZ = 0.0f;
            gCurrentActor->unk155++;
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
            if (D_807FD618[gCurrentPlayerIndex].value != 0.0f) {
                scriptSetActorRampTarget(gCurrentActor, 3.0f, 0.0f);
            }
            gActivePlayerState->maxSpeed = 0.0f;
            playerSetBaseGravity();
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 D_80753770[];
extern f32 D_807537A8[];
extern f32 D_807537C4[];

void playerStateDive(void) {
    switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->unkEA = gCurrentActor->moveYaw;
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0);
            playerInputUpdate(0x48);
            playerApplyGravityAndMotion();
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            gCurrentActor->accelY = D_807537A8[gCurrentCharacterIndex];
            gCurrentActor->speedXZ = D_80753770[gCurrentCharacterIndex];
            gCurrentActor->unkEA = gCurrentActor->moveYaw;
            gCurrentActor->unk155++;
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
            gActivePlayerState->decelRate = D_807537C4[gCurrentCharacterIndex];
            playerInputUpdate(0x33);
            playerSetBaseGravity();
            playerApplyFullPhysics();
            break;
        case 4:
            if (gActivePlayerState->maxSpeed > 10.0f) {
                playerResumeLocomotion(gCurrentActor);
            }
            gActivePlayerState->decelRate = D_807537C4[gCurrentCharacterIndex];
            playerInputUpdate(0x33);
            playerSetBaseGravity();
            playerApplyFullPhysics();
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern PlayerStruct *gPlayerSlots;
extern s16 D_8075387C[];
extern s16 D_8075388C[];
extern s16 D_807538B8[];
extern s16 D_807539DC[];
extern s16 D_807539EC[];

s32 playerCanPerformActionCheck(void) {
    f32 surfaceOffset;
    f32 lim;

    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        surfaceOffset = D_8075388C[gCurrentCharacterIndex];
    } else {
        surfaceOffset = D_807538C8[gCurrentCharacterIndex];
    }
    if (gCurrentActor->state == 0x4E && playerInputCanPerformFairySnap() != 0 && gCurrentActor->unk155 != 0 &&
        gCurrentActor->y + surfaceOffset < gCurrentActor->waterY - 10.0f) {
        gActivePlayerState->subTimer = D_807539EC[gCurrentCharacterIndex];
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        gActivePlayerState->actionTimer = (s32)(D_807539DC[gCurrentCharacterIndex] * 0.5);
        gCurrentActor->state = 0x4F;
        gCurrentActor->unk155 = 1;
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
    lim = (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) ? D_8075387C[gCurrentCharacterIndex] : D_807538B8[gCurrentCharacterIndex];
    if (gCurrentActor->waterY - gCurrentActor->floorY < lim) {
        playerStateQueueCallback(2, 0, gCurrentPlayerIndex);
        return 1;
    }
    return 0;
}

extern f32 D_80753988[];
extern f32 D_807539A4[];

void playerStateSurfaceSwim(void) {
    f32 curSpeedY;
    f32 step;
    f32 t;
    f32 target;

    curSpeedY = gCurrentActor->speedY;
    step = D_807539A4[gCurrentCharacterIndex];
    target = D_80753988[gCurrentCharacterIndex];
    if (curSpeedY < 0.0f) {
        t = -curSpeedY / 3.0f;
        if (!(t < step)) {
            step = t;
        }
    }
    if (gCurrentActor->distToFloor == 0.0f && (f64)curSpeedY < -0.1) {
        gCurrentActor->speedY = -0.1f;
    }
    curSpeedY = gCurrentActor->speedY;
    gCurrentActor->speedY = mathApproachF32(curSpeedY, target, step);
    gActivePlayerState->unk24 = 0;
    switch (gCurrentActor->unk155) {
        case 0:
            playerInputUpdate(0x4E);
            playerApplyMotionWithHorizontalVelocity();
            break;
        case 1:
            playerInputUpdate(0x4D);
            playerApplyMotionWithHorizontalVelocity();
            if (gCurrentActor->speedXZ != 0.0f) {
                actorScriptStartByIndex(gCurrentActor, 0x3A);
                gCurrentActor->unk155 = 2;
            }
            break;
        default:
            playerInputUpdate(0x4D);
            playerApplyMotionWithHorizontalVelocity();
            if (gCurrentActor->speedXZ == 0.0f) {
                actorScriptStartByIndex(gCurrentActor, 0x33);
                gCurrentActor->unk155 = 1;
            } else {
                t = gActivePlayerState->maxSpeed * 1.5 / 40.0;
                if (gCurrentActor->sub4->unk48 < t) {
                    scriptSetActorRampTarget(gCurrentActor, t, 0.0f);
                } else {
                    scriptSetActorRampTarget(gCurrentActor, t, 5.0f);
                }
            }
            break;
    }
    playerCanPerformActionCheck();
    gCurrentActor->flags &= ~1;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSurfaceSwimStroke(void) {
    gActivePlayerState->unk24 = 0;
    switch (gCurrentActor->unk155) {
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

extern s16 D_80753A88[];
extern f32 D_80753AE0[];

void playerStateSurfaceTreadWater(void) {
    f32 t;
    f32 waterLevel;

    gActivePlayerState->unk24 = gActivePlayerState->unk24 + 1;
    gActivePlayerState->airAccel = D_80753AFC[gCurrentCharacterIndex];
    switch (gCurrentActor->unk155) {
        case 0:
            playerInputUpdate(0x4C);
            t = D_80753A5C[gCurrentCharacterIndex];
            gCurrentActor->speedY = mathApproachF32(gCurrentActor->speedY, t, gActivePlayerState->slideSpeed);
            if (t <= gCurrentActor->speedY) {
                if (gCurrentActor->speedXZ != 0.0f || gActivePlayerState->actionTimer != 0) {
                    gCurrentActor->unk155 = 3;
                } else {
                    gCurrentActor->unk155 = 2;
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
                gCurrentActor->unk155 = 3;
            }
            t = gActivePlayerState->actionTimer / 7.5 + 1.0;
            if (gCurrentActor->sub4->unk48 < t) {
                scriptSetActorRampTarget(gCurrentActor, t, 0.0f);
            } else {
                scriptSetActorRampTarget(gCurrentActor, t, 15.0f);
            }
            effectSpawnAuraBurst(2);
            waterLevel = gCurrentActor->waterY;
            if (waterLevel < (f32)D_807538C8[gCurrentCharacterIndex] + gCurrentActor->y) {
                gCurrentActor->y = waterLevel - (f32)D_807538C8[gCurrentCharacterIndex];
            }
            goto end;
        default:
            playerInputUpdate(0x54);
            playerApplyDecelVelocityVector(D_80753A5C[gCurrentCharacterIndex]);
            if (gCurrentActor->speedXZ != 0.0f) {
                gActivePlayerState->unk18 = 0;
                gCurrentActor->unk155 = 3;
            } else {
                if (gActivePlayerState->unk50 != 0) {
                    gActivePlayerState->unk50 = gActivePlayerState->unk50 - 1;
                    if (gActivePlayerState->unk50 == 0) {
                        actorScriptStartByIndex(gCurrentActor, 0x34);
                    }
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
            gActivePlayerState->targetSpeed = D_80753AE0[gCurrentCharacterIndex];
            gActivePlayerState->actionTimer = D_80753A88[gCurrentCharacterIndex];
            playerApplyDecelVelocityVector(0.0f);
            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
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
        gActivePlayerState->unk50 = D_80753A78[gCurrentCharacterIndex];
        scriptSetActorRampTarget(gCurrentActor, 0.5f, (f32)gActivePlayerState->unk50);
        gCurrentActor->unk155 = 2;
    }
    playerClampWaterSurfaceHeight(gCurrentActor);
end:
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateSurfacePaddleTurn(void) {
    gActivePlayerState->unk24 = 0;
    gCurrentActor->pitch = 0;
    gCurrentActor->roll = 0;
    switch (gCurrentActor->unk155) {
        case 0:
            playerUpdateTargetYawFromStick();
            playerInputUpdate(0x21);
            playerApplyMotionWithHorizontalVelocity();
            break;
        case 1:
            playerApplyFullPhysics();
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
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

extern s32 D_8072014C;

void playerStateEnterFallOnCheck(void) {
    s32 n;
    u16 b;
    s32 z;

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
        effectCreateAtActorBone(&D_8072014C, 0.8f, gCurrentActor, 1, 0);
    }
    b = gCurrentActor->prevContactFlags;
    z = (b == 0);
    n = (gCurrentActor->contactFlags & b & 1) ? 2 : 1;
    if (((z ^ 0) & gCurrentActor->contactFlags) & 1) { // FAKE: no-op ^ 0 steers regalloc
        gCurrentActor->speedXZ = gCurrentActor->speedXZ * 0.25;
    }
    if (z) {} // FAKE: dead guard is a real uopt use (Q0561)
    if (gCurrentActor->speedXZ < (f32)n) {
        gCurrentActor->speedXZ = 0.0f;
    } else {
        gCurrentActor->speedXZ = gCurrentActor->speedXZ - (f32)n;
    }
    playerInputUpdate(1);
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 D_80753CD0[];
extern f32 gKongCannonInitialPitch[];

void playerStateDamageFallTumble(void) {
    f32 pad;
    f32 dy;
    f32 dist;
    f32 dz;
    f32 dx;
    f32 fa0;
    f32 fv0;
    s32 n;
    u16 b;
    s32 z;

    switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->flags &= 0xFFBFFFFF;
            if (gCurrentActor->hasArcBounds || ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1))) {
                camReturnToFollow(gActivePlayerState->camActor, gCurrentActor);
            }
            if (!(gCurrentActor->contactFlags & 1)) {
                effectSetDepth(1);
                effectSetDuration(1);
                effectCreateAtActorBone(&D_8072014C, 0.8f, gCurrentActor, 1, 0);
            }
            b = gCurrentActor->prevContactFlags;
            z = (b == 0);
            n = (gCurrentActor->contactFlags & b & 1) ? 2 : 1;
            if (z) {} // FAKE: dead guard is a real uopt use (Q0561)
            if (((z ^ 0) & gCurrentActor->contactFlags) & 1) { // FAKE: no-op ^ 0 steers regalloc
                gCurrentActor->speedXZ = gCurrentActor->speedXZ * 0.25;
            }
            if (gCurrentActor->speedXZ < (f32)n) {
                gCurrentActor->speedXZ = 0.0f;
            } else {
                gCurrentActor->speedXZ = gCurrentActor->speedXZ - (f32)n;
            }
            gCurrentActor->roll = mathAtan2(gCurrentActor->speedXZ, gCurrentActor->speedY) * 4096.0f / 6.2831855f;
            gCurrentActor->yaw = (mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, gActivePlayerState->unkB0, gActivePlayerState->unkB8) + 0x800) % 4095;
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            dy = gActivePlayerState->unkB4 - gPrimaryPlayerActor->y;
            dy = dy / (gPrimaryPlayerActor->sub4->scaleY * 0.16666666675);
            dx = gActivePlayerState->unkB8 - gPrimaryPlayerActor->z;
            dz = gActivePlayerState->unkB0 - gPrimaryPlayerActor->x;
            dist = sqrtf(dx * dx + dz * dz) / (gPrimaryPlayerActor->sub4->scaleY * 0.16666666675);
            fa0 = gPrimaryPlayerActor->speedXZ;
            if (fa0 == 0.0) {
                fa0 = 1.0f;
            }
            fv0 = dist / fa0 - 1.0f;
            if (fv0 < 1.0f) {
                fv0 = 1.0f;
            }
            gPrimaryPlayerActor->speedY = (0.0 - (D_80753CD0[gCurrentCharacterIndex] * 0.5 * (fv0 * fv0) - dy)) / fv0;
            gPrimaryPlayerActor->accelY = -0.001f;
            if (fv0 < 2.0f || fa0 < 2.0) {
                playerSetBaseGravity();
                gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
            }
            if (gCurrentActor->hasArcBounds) {
                gCurrentActor->speedXZ = 0.0f;
                playerSetBaseGravity();
                gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
            }
            playerInputUpdate(1);
            break;
        case 1:
            playerInputUpdate(0x20);
            actorScriptStartByIndex(gCurrentActor, 0x23);
            gCurrentActor->roll = 0;
            playerSetBaseGravity();
            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
            break;
        case 2:
            playerInputUpdate(0x20);
            break;
        case 3:
            sfxPlayScriptActorSoundForPlayer(gCurrentActor, 0x10, 0);
            gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex];
            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
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
        gActivePlayerState->unk6C = 0.0f;
    }
    playerApproachVelocity(gActivePlayerState->unk70, gActivePlayerState->unk6C, gActivePlayerState->targetSpeed);
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerUpdateAirTumble(void) {
    f32 t;
    f32 v;

    playerInputUpdate(0x4A);
    switch (gCurrentActor->unk155) {
        case 0:
            if (gActivePlayerState->targetSpeed < gCurrentActor->speedXZ) {
                playerApplyDeceleration();
                playerApplyGravityAndMotion();
            } else {
                playerApplyFullPhysics();
            }
            t = gCurrentActor->speedXZ * 0.025;
            v = (t > 1.0) ? t : 1.0;
            scriptSetActorRampTarget(gCurrentActor, v, 0.0f);
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
    s32 ch;
    f32 vol;

    playerInputUpdate(1);
    if (gCurrentActor->unk155 < 3 ||
        (camIsPathFlag4Active() != 0 && (camIsPlayingPath(7) != 0 || camIsPlayingPath(0) != 0 || camIsPlayingPath(4) != 0 ||
                                  camIsPlayingPath(9) != 0 || camIsPlayingPath(8) != 0))) {
        mapChunkSetIndexOverride(1);
    }
    switch (gCurrentActor->unk155) {
        case 0:
            if (!(gGlobalCutsceneFlags & 2)) {
                gCurrentActor->unk144 = 1;
            }
            break;
        case 1:
            vol = 1.0f;
            ch = 0xA;
            switch (gCurrentActor->actorType) {
                case 2:
                    ch = 0xB;
                    break;
                case 5:
                    ch = 0xD;
                    break;
                case 4:
                    ch = 0xC;
                    if (!(gGlobalCutsceneFlags & 2)) {
                        vol = 0.82f;
                    }
                    break;
                case 6:
                    ch = 9;
                    break;
            }
            sfxAllocateChannel(ch, vol);
            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 gKongHoldPutDownAngles[];

extern u8 D_8071FC8C;
f32 mathSinF(s16);

void playerStateTransformSparkles(void) {
    f32 pad;
    f32 posY;

    playerInputUpdate(1);
    if (gCurrentActor->unk155 == 1 || gCurrentActor->unk155 == 2) {
        randomNonNegative();
        posY = (s32)(randomNonNegative() >> 15) % 30 + gCurrentActor->y;
        randomNonNegative();
        effectSetDepth(1);
        effectSetSpeed((gActivePlayerState->unk23C << 16) + (s32)(15.0 * (gCurrentActor->alpha / 255.0)));
        effectSetCallback(effectOrbitXZUpdate);
        effectCreateAtPosition(&D_8071FC8C, 0.5f, gCurrentActor->x, posY, gCurrentActor->z);
    }
    switch (gCurrentActor->unk155) {
    case 0:
        gActivePlayerState->unk23C = 0;
        gCurrentActor->unk155++;
        gCurrentActor->flags &= 0xFFFF7FFF;
        gCurrentActor->alpha = 0xFF;
        break;
    case 1:
        gActivePlayerState->unk23C += 0x1E;
        if (gActivePlayerState->unk23C >= 0x191) {
            gActivePlayerState->unk23C = 0x190;
        }
        if (gActivePlayerState->unk23C == 0xD2) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x264, 0xFF, 0x64, 0x19);
        }
        if (gActivePlayerState->unk23C >= 0x12D) {
            gActivePlayerState->stateFlags &= ~0x40;
            gCurrentActor->alpha -= 5;
            if (gCurrentActor->alpha < 0xA) {
                gCurrentActor->unk155++;
            }
        }
        break;
    case 2:
        func_805FF9AC(gActivePlayerState->unk242, 0, 0, 3);
        gCurrentActor->unk155++;
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStatePonytailFloat(void) {
    f32 v;

    switch (gCurrentActor->unk155) {
    case 0:
        gCurrentActor->speedY = 0.0f;
        gCurrentActor->speedXZ = 0.0f;
        gActivePlayerState->decelRate = 1.0f;
        gActivePlayerState->airAccel = 3.0f;
        gCurrentActor->accelY = 2.0f;
        gActivePlayerState->unk23C = 0;
        gActivePlayerState->unk238 = gCurrentActor->y;
        gCurrentActor->unk155++;
        break;
    case 1:
        playerInputUpdate(0x43);
        mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x32);
        gCurrentActor->y = gActivePlayerState->unk238;
        playerApplyFullPhysics();
        if (gActivePlayerState->unk238 - gCurrentActor->yawSpeed > 50.0f) {
            gCurrentActor->y -= 1.0;
        }
        gActivePlayerState->unk238 = gCurrentActor->y;
        gCurrentActor->y = mathSinF((s16)gActivePlayerState->unk23C) * 10.0 + gActivePlayerState->unk238;
        gActivePlayerState->unk23C += 0x64;
        if (gCurrentActor->yawSpeed < gCurrentActor->y) {
            v = gCurrentActor->y - gCurrentActor->yawSpeed;
        } else {
            v = -(gCurrentActor->y - gCurrentActor->yawSpeed);
        }
        if (v < 150.0) {
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
    switch (gCurrentActor->unk155) {
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
            gCurrentActor->unk155++;
        }
        if (D_807FD63C[gCurrentPlayerIndex].value & 0x2000) {
            gCurrentActor->unk155 = 3;
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
        gActivePlayerState->unkC0--;
        if (gActivePlayerState->unkC0 < 0 || (D_807FD63C[gCurrentPlayerIndex].value & 0x2000)) {
            gCurrentActor->unk155++;
        }
        break;
    case 3:
        actorScriptStart(gCurrentActor, 0x16A);
        playerInputUpdate(0x43);
        playerApplyFullPhysics();
        gCurrentActor->unk155++;
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
    f32 v;
    if (gActorGlobalState.unkE8 != 0.0) {
        v = gActorGlobalState.unkE8;
    } else {
        v = gCurrentActor->speedXZ;
    }
    scriptSetActorRampTarget(gCurrentActor, v / 25.0f + 0.25, 2.0f);
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
    mathAngleStepToward(&gCurrentActor->yaw, (s16)mathAngleBetweenPoints2D(gActivePlayerState->unk220, gActivePlayerState->unk228, gCurrentActor->x, gCurrentActor->z), 0x32);
    playerApplyMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateHoldPickup(void) {
    f64 baseScale;

    if (actorTableContains(gActivePlayerState->queuedHeldActor) == 0 || gActivePlayerState->queuedHeldActor->instanceId != gActivePlayerState->queuedHeldActorId) {
        gActivePlayerState->heldActor = NULL;
        gActivePlayerState->queuedHeldActor = NULL;
        playerResumeLocomotion(gCurrentActor);
        playerApplyFullPhysics();
        actorUpdateModelMatrix(gCurrentActor, 0);
        return;
    }
    switch (gCurrentActor->unk155) {
    case 0:
        gCurrentActor->speedXZ = 0.0f;
        gActivePlayerState->maxSpeed = 0.0f;
        playerStartPickupApproach(gActivePlayerState->queuedHeldActor);
        gCurrentActor->x += gActivePlayerState->unk78;
        gCurrentActor->z += gActivePlayerState->unk7C;
        gCurrentActor->yaw = gActivePlayerState->unk80;
        gCurrentActor->unk155++;
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
        gCurrentActor->unk155++;
        break;
    case 3:
        playerInputUpdate(5);
        playerRegisterHeldActorFollow(0.4f);
        playerComputePickupHoldPitch();
        break;
    case 4:
        playerInputUpdate(5);
        actorAppendCallback4000(gCurrentActor, gActivePlayerState->heldActor, gActivePlayerActor->yaw, gCurrentActor->sub4->scaleX * (gKongHoldPutDownAngles[gCurrentCharacterIndex] * 3.0) / (baseScale = 0.15), 0); // FAKE: mul.d operand order
        gCurrentActor->unk155++;
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
        gCurrentActor->unk155 = 3;
        break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateCrouch(void) {
    playerInputUpdate(6);
    if (D_807FD618[gCurrentPlayerIndex].value != 0.0f) {
        scriptSetActorRampTarget(gCurrentActor, 3.0f, 0.0f);
    }
    mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, gActivePlayerState->turnRate);
    gActivePlayerState->maxSpeed = 0.0f;
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateCrawl(void) {
    playerInputUpdate(7);
    if (D_807FD618[gCurrentPlayerIndex].value != 0.0f) {
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
    gCurrentActor->unk155 = 0;
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
    gCurrentActor->unk155 = 0;
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
    switch (gCurrentActor->unk155) {
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
            gCurrentActor->unk155++;
            break;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 D_80753364[];
extern f32 D_80753380[];
extern f32 gKongHoldPutDownOffsets[];

void playerStateHoldPutDown(void) {
    gActivePlayerState->stateFlags &= 0xFEFFFFFF;
    playerInputUpdate(1);
    switch (gCurrentActor->unk155) {
        case 0:
            playerRegisterHeldActorFollow(1.0f);
            gCurrentActor->speedXZ = 0.0f;
            break;
        case 1:
            actorAppendCallback4000(gCurrentActor, gActivePlayerState->heldActor, gActivePlayerActor->yaw, gKongHoldPutDownAngles[gCurrentCharacterIndex], (s32)gKongHoldPutDownOffsets[gCurrentCharacterIndex]);
            gActivePlayerState->heldActor = NULL;
            gActivePlayerState->queuedHeldActor = NULL;
            gCurrentActor->unk155++;
            gCurrentActor->speedXZ = D_80753364[gCurrentCharacterIndex];
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            break;
        default:
            if (gCurrentActor->speedXZ != 0.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ -= D_80753380[gCurrentCharacterIndex];
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
    switch (gCurrentActor->unk155) {
        case 0:
            playerRegisterHeldActorFollow(1.0f);
            gCurrentActor->speedXZ = 0.0f;
            break;
        case 1:
            actorAppendCallback4000(gCurrentActor, gActivePlayerState->heldActor, gActivePlayerActor->yaw, gKongHoldThrowAngles[gCurrentCharacterIndex], (s32)gKongHoldThrowOffsets[gCurrentCharacterIndex]);
            gActivePlayerState->heldActor = NULL;
            gActivePlayerState->queuedHeldActor = NULL;
            gCurrentActor->unk155++;
            gCurrentActor->speedXZ = D_80753364[gCurrentCharacterIndex];
            gCurrentActor->moveYaw = gCurrentActor->yaw;
            break;
        default:
            if (gCurrentActor->speedXZ != 0.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ -= D_80753380[gCurrentCharacterIndex];
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
    switch (gCurrentActor->unk155) {
        case 0:
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0);
            playerInputUpdate(0x21);
            break;
        case 1:
            gCurrentActor->speedY = gActivePlayerState->jumpVelocityY;
            playerSetTerminalVelocity5B0();
            playerUpdateTargetYawFromStick();
            gCurrentActor->unk155++;
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

extern s16 D_8075326C[];

void playerStateTransformHold(void) {
    f32 dx;
    f32 dz;

    if (gActorGlobalState.unkE4 != 0) {
        gActivePlayerState->damageSource = gActorGlobalState.unkEC;
        gActivePlayerState->unk9C = gCurrentActor->x;
        gActivePlayerState->unkA0 = gCurrentActor->z;
        gActivePlayerState->unkA4 = gActorGlobalState.unkD8;
        gActivePlayerState->unkA8 = gActorGlobalState.unkE0;
        gActivePlayerState->unkAC = 0.0f;
        dx = gActivePlayerState->unkA4 - gActivePlayerState->unk9C;
        dz = gActivePlayerState->unkA8 - gActivePlayerState->unkA0;
        gActivePlayerState->unk94 = sqrtf(dx * dx + dz * dz) * 0.8;
        gActivePlayerState->unk98 = mathAtan2(dx, dz) * 4096.0f / 6.2831855f;
        gActivePlayerState->unk4C = -1;
    }
    gActivePlayerState->unkAC += 0.02;
    if (gActivePlayerState->unkAC > 1.0) {
        if (gActivePlayerState->damageSource != NULL) {
            gActivePlayerState->unk98 = mathAtan2(gActivePlayerState->damageSource->x - gActivePlayerState->unk9C, gActivePlayerState->damageSource->z - gActivePlayerState->unkA0) * 4096.0f / 6.2831855f;
            if ((s16)gActivePlayerState->unk98 == gCurrentActor->yaw) {
                playerResumeLocomotion(gCurrentActor);
            }
        }
        gActivePlayerState->unkAC = 1.0f;
    }
    dx = gActivePlayerState->unkAC;
    gCurrentActor->x = gActivePlayerState->unk9C + (gActivePlayerState->unkA4 - gActivePlayerState->unk9C) * dx;
    gCurrentActor->z = gActivePlayerState->unkA0 + (gActivePlayerState->unkA8 - gActivePlayerState->unkA0) * gActivePlayerState->unkAC;
    playerApplyMotion();
    playerSelectWalkRunState(gCurrentActor, gActivePlayerState->unk94, gActivePlayerState->unk94, 0);
    mathAngleStepToward(&gCurrentActor->yaw, (s16)gActivePlayerState->unk98, (s16)(D_8075326C[gCurrentCharacterIndex] / 2));
    gCurrentActor->moveYaw = gCurrentActor->yaw;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateTagBarrelFade(void) {
    gCurrentActor->speedXZ = 0.0f;
    switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->unk144 = 1;
            gCurrentActor->flags &= 0xFFFF7FFF;
            gCurrentActor->alpha = 0xFF;
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xE6, 0xFF, 0x7F, 0, 0, 0.3f, 0);
            gCurrentActor->unk155++;
            break;
        case 1:
            gCurrentActor->alpha -= 0xF;
            if (gCurrentActor->alpha < 0x10) {
                matrixCacheSetDefaultLimit();
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            actorClearMovementFlags(gCurrentActor);
            gCurrentActor->x = gActivePlayerState->unk204;
            gCurrentActor->y = gActivePlayerState->unk208 + 10.0;
            gCurrentActor->prevY = gCurrentActor->y;
            gCurrentActor->z = gActivePlayerState->unk20C;
            func_806C8220(0, ACTOR_EXT->unk178, gCurrentActor->actorType);
            camResetPlayer(gCurrentActor, gActivePlayerState->playerIndex);
            screenWipeStart(6);
            gActivePlayerState->unk23C = 0x14;
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xE6, 0xFF, 0x7F, 0, 0, 0.3f, 0);
            gCurrentActor->unk155++;
            break;
        case 3:
            gActivePlayerState->unk23C--;
            if (gActivePlayerState->unk23C == 0) {
                gCurrentActor->unk155++;
            }
            break;
        case 4:
            gCurrentActor->alpha += 0xF;
            if (gCurrentActor->alpha >= 0xF1) {
                gCurrentActor->flags |= 0x8000;
                gCurrentActor->unk155++;
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
    switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->unk144 = 1;
            if (actorSpawn(0x3C, 0x98)) {
                actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.15f);
            }
            gCurrentActor->unk155++;
            break;
        case 1:
            gCurrentActor->unk155++;
            gActivePlayerState->unk23C = 4;
            break;
        case 2:
            gCurrentActor->x = (gActivePlayerState->unk210 - gCurrentActor->x) * 0.5 + gCurrentActor->x;
            gCurrentActor->y = (gActivePlayerState->unk214 - gCurrentActor->y) * 0.5 + gCurrentActor->y;
            gCurrentActor->z = (gActivePlayerState->unk218 - gCurrentActor->z) * 0.5 + gCurrentActor->z;
            if (gActivePlayerState->unk23C != 0) {
                gActivePlayerState->unk23C--;
                if (gActivePlayerState->unk23C == 0) {
                    gCurrentActor->flags &= 0xFFFF7FFF;
                    gCurrentActor->alpha = 0;
                }
            }
            break;
        case 3:
            gCurrentActor->flags &= 0xFFFF7FFF;
            gCurrentActor->alpha = 0;
            gCurrentActor->unk155++;
            break;
        case 5:
            gActivePlayerState->unk23C = 0x14;
            break;
        case 6:
            gActivePlayerState->unk23C--;
            if (gActivePlayerState->unk23C == 0) {
                matrixCacheSetDefaultLimit();
                gCurrentActor->unk155++;
            }
            break;
        case 7:
            gGlobalPauseFlags &= 0xFFFCFFDF;
            actorClearMovementFlags(gCurrentActor);
            gCurrentActor->x = gActivePlayerState->unk204;
            gCurrentActor->y = gActivePlayerState->unk208;
            gCurrentActor->prevY = gCurrentActor->y;
            gCurrentActor->z = gActivePlayerState->unk20C;
            func_806C8220(0, ACTOR_EXT->unk178, gCurrentActor->actorType);
            camResetPlayer(gCurrentActor, gActivePlayerState->playerIndex);
            gActivePlayerState->unk23C = 0x14;
            screenWipeStart(2);
            gCurrentActor->unk155++;
            break;
        case 8:
            gGlobalPauseFlags |= 0x30020;
            gActivePlayerState->unk23C--;
            if (gActivePlayerState->unk23C == 0) {
                sfxStartAreaAmbient();
                if (actorSpawn(0x3C, 0x98)) {
                    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.15f);
                }
                gCurrentActor->unk155++;
                gActivePlayerState->unk23C = 0xC;
            }
            break;
        case 10:
            if (gActivePlayerState->unk23C != 0) {
                gActivePlayerState->unk23C--;
                if (gActivePlayerState->unk23C == 0) {
                    gCurrentActor->x = gActivePlayerState->unk210;
                    gCurrentActor->y = gActivePlayerState->unk214;
                    gCurrentActor->z = gActivePlayerState->unk218;
                    gCurrentActor->flags |= 0x8000;
                }
            }
            break;
        case 11:
            playerInputUpdate(0x20);
            actorScriptStartByIndex(gCurrentActor, 0x1B);
            playerSetBaseGravity();
            gCurrentActor->unk155++;
            break;
        case 12:
        case 13:
            playerInputUpdate(0x20);
            playerApplyGravity();
            break;
        case 14:
            sfxPlayScriptActorSoundForPlayer(gCurrentActor, 0x2F, 0);
            gCurrentActor->unk155++;
        case 15:
            actorSetInteractionTimer(gCurrentActor);
            matrixCacheRestoreLimit();
            playerInputUpdate(0x30);
            break;
    }
    playerApplyMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 D_8071FC58;
extern u8 D_8071FCC0;

void playerStateKnockbackTumble(void) {
    f32 lightX;
    f32 lightY;
    f32 lightZ;
    u8 kind;
    f32 px;
    f32 py;
    f32 pz;
    f32 s;

    playerInputUpdate(1);
    switch (gCurrentActor->unk155) {
    case 0:
        gActivePlayerState->unk108 = 50.0f;
        gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
        break;
    case 1:
        if (gActivePlayerState->unk108 != 0.0f) {
            gActivePlayerState->unk108 = gActivePlayerState->unk108 - 1.0f;
        } else if (gCurrentActor->y - gCurrentActor->floorY < 60.0f) {
            gCurrentActor->y = gCurrentActor->y + 1.0f;
        } else {
            gActivePlayerState->unk108 = 150.0f;
            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
            camSetTargetScaled(gActivePlayerState->camActor, gCurrentActor, 6, 0, 0x1E, 0, 5, 0x2D, 0x14, 0xC8, 0.15f);
        }
        break;
    case 2:
        gActivePlayerState->unk108 = gActivePlayerState->unk108 - 1.0f;
        if (gActivePlayerState->unk108 == 0.0f) {
            gActivePlayerState->unk108 = 150.0f;
            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
        }
        s = (mathSinF(gActivePlayerState->unkCC) > 0.0f) ? mathSinF(gActivePlayerState->unkCC) : -mathSinF(gActivePlayerState->unkCC);
        gCurrentActor->yaw = gCurrentActor->yaw + 120.0 * (0.5 + s);
        break;
    case 3:
        gActivePlayerState->unk108 = gActivePlayerState->unk108 - 1.0f;
        if (gActivePlayerState->unk108 == 0.0f) {
            gActivePlayerState->unk108 = 500.0f;
            gCurrentActor->unk155 = gCurrentActor->unk155 + 1;
        }
        s = (mathSinF(gActivePlayerState->unkCC) > 0.0f) ? mathSinF(gActivePlayerState->unkCC) : -mathSinF(gActivePlayerState->unkCC);
        gCurrentActor->yaw = gCurrentActor->yaw + 120.0 * (0.5 + s);
        s = mathSinF((s16)(gActivePlayerState->unkCC + 0x400));
        gCurrentActor->pitch = gCurrentActor->pitch + 60.0f * s;
        break;
    case 4:
        playerStateQueueCallback(0x1B, 0, 0);
        gActivePlayerState->stateFlags |= 4;
        gCurrentActor->pitch = 0;
        gCurrentActor->yaw = 0;
        break;
    }
    gActivePlayerState->unkCC = gActivePlayerState->unkCC + 6;
    gActivePlayerState->unkCC = gActivePlayerState->unkCC & 0xFFF;
    if (!(gFrameCounter & 1)) {
        kind = (randomNonNegative() >> 15) % 65535 % 3;
        actorGetNodePos(gCurrentActor, 5, &px, &py, &pz);
        px += (f32)((randomNonNegative() >> 15) % 65535 % 16 - 8);
        py += (f32)((randomNonNegative() >> 15) % 65535 % 16 - 8);
        pz += (f32)((randomNonNegative() >> 15) % 65535 % 16 - 8);
        effectSetMode(2);
        effectSetDepth(1);
        effectSetCallback(effectPuffRiseUpdate);
        effectSetSpeed((randomNonNegative() >> 15) % 100 + 0x64);
        if (kind == 2) {
            effectCreateAtPosition(&D_8071FCC0, 0.5f, px, py, pz);
        } else if (kind == 1) {
            effectCreateAtPosition(&D_8071FC8C, 0.5f, px, py, pz);
        } else {
            effectCreateAtPosition(&D_8071FC58, 0.5f, px, py, pz);
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
    s16 t;
    f32 f;
    s32 i;

    playerInputUpdate(1);
    gCurrentActor->speedXZ = 0.0f;
    switch (gCurrentActor->unk155) {
    case 0:
        gCurrentActor->unk144 = 1;
        gActivePlayerState->unk23C = 0xA;
        gCurrentActor->unk155++;
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x2EB, 0xFF, 0x7F, 2);
        break;
    case 1:
        if (gActivePlayerState->unk23C >= 2) {
            gActivePlayerState->unk23C--;
        } else {
            gCurrentActor->unk155++;
        }
        break;
    case 2:
        actorClearMovementFlags(gCurrentActor);
        gCurrentActor->x = gActivePlayerState->unk204;
        gCurrentActor->y = gActivePlayerState->unk208;
        gCurrentActor->prevY = gCurrentActor->y;
        gCurrentActor->z = gActivePlayerState->unk20C;
        t = gActivePlayerState->unk21C;
        gCurrentActor->moveYaw = t;
        gCurrentActor->yaw = t;
        camResetPlayer(gCurrentActor, gActivePlayerState->playerIndex);
        func_806C8220(0, ACTOR_EXT->unk178, gCurrentActor->actorType);
        gCurrentActor->unk155++;
        break;
    case 3:
        if (gActivePlayerState->unk23C < 0xA) {
            gActivePlayerState->unk23C++;
        } else {
            gCurrentActor->unk155++;
        }
        break;
    case 4:
        gActivePlayerState->transitionTimer = 0x3C;
        playerResumeLocomotion(gCurrentActor);
        break;
    }
    f = (f32)gActivePlayerState->unk23C * 0.015;
    for (i = 0; i < 3; i++) {
        (&gCurrentActor->sub4->scaleX)[i] = f;
    }
    playerApplyMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStepForwardSpeedTowardTarget(f32 step) {
    f32 cur = gActivePlayerState->unk94;
    f32 tgt = gActivePlayerState->maxSpeed;

    if (cur < tgt) {
        cur += step;
        if (tgt < cur) {
            cur = tgt;
        }
    } else if (tgt < cur) {
        cur -= step;
        if (cur < tgt) {
            cur = tgt;
        }
    }
    gActivePlayerState->unk94 = cur;
}

extern s16 D_80753C84[];
extern f32 D_80753C30[];
extern f32 D_80753C4C[];
extern f32 D_80753C68[];
extern u8 proxPathFollowerStep;

void playerStateAttachedCallbackFall(void) {
    ActorCallbackNode *node;
    s32 pad[1];
    f32 targetSpeed;
    f32 f;
    f64 d;

    if (gCurrentActor->unk155 != 0 && !(gCurrentActor->contactFlags & 0x40)) {
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
    node->callback = &proxPathFollowerStep;
    node->source = gActivePlayerActor;
    node->unk4 = 1;
    actorRegisterGlobalCallback(node);
    mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0xC8);
    switch (gCurrentActor->unk155) {
    case 0:
        playerInputUpdate(5);
        gActivePlayerState->unk94 = 0.0f;
        gActivePlayerState->unk158 = 0;
        gCurrentActor->moveYaw = gActivePlayerState->unk130->yaw;
        if (mathAngleDistance(gCurrentActor->yaw, gActivePlayerState->unk130->yaw) >= 0x400) {
            gCurrentActor->moveYaw = (gCurrentActor->moveYaw + 0x800) & 0xFFF;
        }
        break;
    case 1:
        if (playerInputUpdate(0x58) == 0) {
            switch (gActivePlayerState->unk8) {
            case 1:
                targetSpeed = D_80753C30[gCurrentCharacterIndex];
                gCurrentActor->unk155 = 3;
                actorScriptStartByIndex(gActivePlayerActor, 0x6A);
                break;
            case 0:
                targetSpeed = D_80753C68[gCurrentCharacterIndex];
                break;
            case -1:
                targetSpeed = D_80753C4C[gCurrentCharacterIndex];
                gCurrentActor->unk155 = 4;
                actorScriptStartByIndex(gActivePlayerActor, 0x6B);
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
        }
        break;
    case 2:
        if (playerInputUpdate(0x58) == 0) {
            if (gActivePlayerState->unk94 == 0.0f && gActivePlayerState->maxSpeed == 0.0f) {
                gCurrentActor->unk155 = 1;
                actorScriptStartByIndex(gActivePlayerActor, 0x6C);
            } else if (gActivePlayerState->unk94 > 0.0f && gActivePlayerState->maxSpeed > 0.0f) {
                gCurrentActor->unk155 = 3;
                actorScriptStartByIndex(gActivePlayerActor, 0x6A);
            } else if (gActivePlayerState->unk94 < 0.0f && gActivePlayerState->maxSpeed < 0.0f) {
                gCurrentActor->unk155 = 4;
                actorScriptStartByIndex(gActivePlayerActor, 0x6B);
            }
            playerStepForwardSpeedTowardTarget(D_80753C68[gCurrentCharacterIndex]);
            d = gActivePlayerState->unk94 * 0.025;
            if (d > 0.0) {
                f = d;
            } else {
                f = -d;
            }
            scriptSetActorRampTarget(gCurrentActor, f, 0.0f);
        }
        break;
    case 3:
        if (playerInputUpdate(0x58) == 0) {
            if (gActivePlayerState->unk94 <= 0.0f) {
                gCurrentActor->unk155 = 2;
            }
            switch (gActivePlayerState->unk8) {
            case -1:
                targetSpeed = D_80753C4C[gCurrentCharacterIndex] * 2;
                break;
            case 0:
                targetSpeed = D_80753C68[gCurrentCharacterIndex];
                break;
            case 1:
                targetSpeed = D_80753C30[gCurrentCharacterIndex];
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            d = gActivePlayerState->unk94 * 0.025;
            if (d > 0.0) {
                f = d;
            } else {
                f = -d;
            }
            scriptSetActorRampTarget(gCurrentActor, f, 0.0f);
        }
        break;
    case 4:
        if (playerInputUpdate(0x58) == 0) {
            if (gActivePlayerState->unk94 >= 0.0f) {
                gCurrentActor->unk155 = 2;
            }
            switch (gActivePlayerState->unk8) {
            case -1:
                targetSpeed = D_80753C4C[gCurrentCharacterIndex];
                break;
            case 0:
                targetSpeed = D_80753C68[gCurrentCharacterIndex];
                break;
            case 1:
                targetSpeed = D_80753C30[gCurrentCharacterIndex];
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            d = gActivePlayerState->unk94 * 0.025;
            if (d > 0.0) {
                f = d;
            } else {
                f = -d;
            }
            scriptSetActorRampTarget(gCurrentActor, f, 0.0f);
        }
        break;
    }
    playerApplyMotion();
}

void func_806DCA7C(void) {
    f32 dist;
    f32 time;
    f32 dy;
    f32 speed;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    s32 diff;
    s32 absd;
    s16 t;

    gCurrentActor->flags &= 0xFFBFFFFF;
    gCurrentActor->contactFlags &= 0xFFBF;
    t = gCurrentActor->roll;
    gCurrentActor->roll = t + -t * 0.1;
    switch (gCurrentActor->unk155) {
    case 0:
        playerFindClosestTargetActor();
        gCurrentActor->speedXZ = gActivePlayerState->unk14C / 2;
        gCurrentActor->moveYaw = gActivePlayerState->unk154;
        diff = gCurrentActor->moveYaw - gCurrentActor->yaw;
        if (diff < -0x800) {
            diff += 0x1000;
        }
        if (diff >= 0x801) {
            diff -= 0x1000;
        }
        if (diff > 0) {
            absd = diff;
        } else {
            absd = -diff;
        }
        if (absd < 0x400) {
            actorScriptStartByIndex(gCurrentActor, 0x6D);
        } else {
            actorScriptStartByIndex(gCurrentActor, 0x6E);
        }
        mathAngleStepTowardThreshold(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x78, 0x600);
        gCurrentActor->speedY = gActivePlayerState->unk150;
        gCurrentActor->unk155++;
        playerInputUpdate(0x27);
        gActivePlayerState->decelRate = gActivePlayerState->decelRate / 2;
        playerApplyGravityAndMotion();
        break;
    case 2:
        if (gActivePlayerState->unk158 == 0) {
            actorScriptStartByIndex(gActivePlayerActor, 0x6F);
            gCurrentActor->unk155 = 3;
            break;
        }
    case 1:
        playerFindClosestTargetActor();
        if (gCurrentActor->actorType == 5) {
            playerInputUpdate(0x28);
        } else {
            playerInputUpdate(0x27);
        }
        gCurrentActor->speedXZ = gActivePlayerState->unk14C;
        gCurrentActor->moveYaw = gActivePlayerState->unk154;
        mathAngleStepTowardThreshold(&gCurrentActor->yaw, gCurrentActor->moveYaw, 0x78, 0x600);
        gActivePlayerState->targetYaw = gCurrentActor->moveYaw;
        gActivePlayerState->maxSpeed = 150.0f;
        gActivePlayerState->targetSpeed = 150.0f;
        if (gActivePlayerState->unk158 != 0) {
            actorGetNodePos(gActivePlayerState->unk158, 1, &nodeX, &nodeY, &nodeZ);
            dy = nodeY - gActivePlayerActor->y;
            dy = dy / (gActivePlayerActor->sub4->scaleY * 0.16666666675);
            dist = sqrtf((nodeX - gActivePlayerActor->x) * (nodeX - gActivePlayerActor->x) + (nodeZ - gActivePlayerActor->z) * (nodeZ - gActivePlayerActor->z)) / (gActivePlayerActor->sub4->scaleY * 0.16666666675);
            speed = gActivePlayerActor->speedXZ;
            time = dist / speed - 1.0f;
            if (time < 1.0f) {
                time = 1.0f;
            }
        }
        if ((gActivePlayerState->unk158 != 0) && (time < 30.0f)) {
            gActivePlayerActor->speedY = (0.0 - (D_80753CD0[gCurrentCharacterIndex] * 0.5 * (time * time) - dy)) / time;
            gActivePlayerActor->accelY = -0.001f;
        } else {
            gActivePlayerState->unk158 = 0;
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

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

void playerFindClosestTargetActor(void) {
    f32 best = 100.0f;
    Actor *cur = gActivePlayerState->unk158;
    Actor *a;
    s16 ang;
    s16 d;
    s32 i;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 v;

    if ((cur != NULL) || (gCurrentActor->unk155 == 1)) {
        if (cur == NULL) {
            for (i = 0; i < gActiveActorCount; i++) {
                a = gActiveActors[i].actor;
                if (!(a->flags & 0x2000) && (a->flags & 0x04000000) && (a != gActivePlayerState->unk130) && (a != gActivePlayerActor)) {
                    ang = (s32)(((f64)(mathAngleBetweenPointsRad(a->x, a->z, gActivePlayerActor->x, gActivePlayerActor->z) * 57.295776f) / 360.0) * 4095.0);
                    d = mathAngleDistance(ang, gActivePlayerState->unk154);
                    dx = a->x - gActivePlayerActor->x;
                    dz = a->z - gActivePlayerActor->z;
                    dist = sqrtf(dx * dx + dz * dz);
                    if ((d < 0x258) && (dist < best)) {
                        if (gActivePlayerActor->y < a->y) {
                            v = a->y - gActivePlayerActor->y;
                        } else {
                            v = -(a->y - gActivePlayerActor->y);
                        }
                        if (v < 100.0) {
                            best = dist;
                            gActivePlayerState->unk154 = ang;
                            gActivePlayerState->unk158 = a;
                        }
                    }
                }
            }
        } else {
            ang = (s32)(((f64)(mathAngleBetweenPointsRad(cur->x, cur->z, gActivePlayerActor->x, gActivePlayerActor->z) * 57.295776f) / 360.0) * 4095.0);
            if (mathAngleDistance(ang, gActivePlayerState->unk154) < 0x258) {
                gActivePlayerState->unk154 = ang;
            }
        }
    }
}

extern s16 D_80753CA4[];

void playerStateAttachedCallbackFallCheck(void) {
    ActorCallbackNode *node;
    s32 pad[1];
    f32 targetSpeed;
    f32 f;
    f64 d;

    if (gCurrentActor->unk155 != 0 && (!(gCurrentActor->contactFlags & 0x40) || ((gCurrentActor->contactFlags & 4) && (f64)(gCurrentActor->waterY - gCurrentActor->y) > 3.0))) {
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
    node->callback = &proxPathFollowerStep;
    node->source = gActivePlayerActor;
    node->unk4 = 1;
    actorRegisterGlobalCallback(node);
    switch (gCurrentActor->unk155) {
    case 0:
        playerInputUpdate(5);
        gActivePlayerState->unk94 = 0.0f;
        break;
    case 1:
        if (playerInputUpdate(0x59) == 0) {
            switch (gActivePlayerState->unk8) {
            case 1:
                targetSpeed = D_80753C30[gCurrentCharacterIndex];
                gCurrentActor->unk155 = 3;
                actorScriptStartByIndex(gActivePlayerActor, 0x71);
                break;
            case 0:
                targetSpeed = D_80753C68[gCurrentCharacterIndex];
                break;
            case -1:
                targetSpeed = D_80753C4C[gCurrentCharacterIndex];
                gCurrentActor->unk155 = 4;
                actorScriptStartByIndex(gActivePlayerActor, 0x72);
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
        }
        break;
    case 2:
        if (playerInputUpdate(0x59) == 0) {
            if (gActivePlayerState->unk94 == 0.0f && gActivePlayerState->maxSpeed == 0.0f) {
                gCurrentActor->unk155 = 1;
                actorScriptStartByIndex(gActivePlayerActor, 0x73);
            } else if (gActivePlayerState->unk94 > 0.0f && gActivePlayerState->maxSpeed > 0.0f) {
                gCurrentActor->unk155 = 3;
                actorScriptStartByIndex(gActivePlayerActor, 0x71);
            } else if (gActivePlayerState->unk94 < 0.0f && gActivePlayerState->maxSpeed < 0.0f) {
                gCurrentActor->unk155 = 4;
                actorScriptStartByIndex(gActivePlayerActor, 0x72);
            }
            playerStepForwardSpeedTowardTarget(D_80753C68[gCurrentCharacterIndex]);
            d = gActivePlayerState->unk94 * 0.025;
            if (d > 0.0) {
                f = d;
            } else {
                f = -d;
            }
            scriptSetActorRampTarget(gCurrentActor, f, 0.0f);
        }
        break;
    case 3:
        if (playerInputUpdate(0x59) == 0) {
            if (gActivePlayerState->unk94 <= 0.0f) {
                gCurrentActor->unk155 = 2;
            }
            switch (gActivePlayerState->unk8) {
            case -1:
                targetSpeed = D_80753C4C[gCurrentCharacterIndex] * 2;
                break;
            case 0:
                targetSpeed = D_80753C68[gCurrentCharacterIndex];
                break;
            case 1:
                targetSpeed = D_80753C30[gCurrentCharacterIndex];
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            d = gActivePlayerState->unk94 * 0.025;
            if (d > 0.0) {
                f = d;
            } else {
                f = -d;
            }
            scriptSetActorRampTarget(gCurrentActor, f, 0.0f);
        }
        break;
    case 4:
        if (playerInputUpdate(0x59) == 0) {
            if (gActivePlayerState->unk94 >= 0.0f) {
                gCurrentActor->unk155 = 2;
            }
            switch (gActivePlayerState->unk8) {
            case -1:
                targetSpeed = D_80753C4C[gCurrentCharacterIndex];
                break;
            case 0:
                targetSpeed = D_80753C68[gCurrentCharacterIndex];
                break;
            case 1:
                targetSpeed = D_80753C30[gCurrentCharacterIndex];
                break;
            }
            playerStepForwardSpeedTowardTarget(targetSpeed);
            d = gActivePlayerState->unk94 * 0.025;
            if (d > 0.0) {
                f = d;
            } else {
                f = -d;
            }
            scriptSetActorRampTarget(gCurrentActor, f, 0.0f);
        }
        break;
    }
    playerApplyMotion();
}

extern f32 gKongKnockbackSpeeds[];

void playerStateKnockbackBounce(void) {
    gCurrentActor->unkFA = 0x12C;
    playerSetUnk586Flag();
    switch (gCurrentActor->unk155) {
    case 1:
        gCurrentActor->moveYaw = (gCurrentActor->yaw + 0x800) & 0xFFF;
        gCurrentActor->speedY = gKongKnockbackSpeeds[gCurrentCharacterIndex];
        gCurrentActor->speedXZ = 100.0f;
        playerSetTerminalVelocity5B0();
        gCurrentActor->unk155++;
        gActivePlayerState->airTimer = 3;
        playerInputUpdate(0x29);
        gActivePlayerState->airAccel = 30.0f;
        gActivePlayerState->turnRate = 0x64;
        playerSetBaseGravityIfFalling();
        gActivePlayerState->decelRate = gActivePlayerState->decelRate / 2;
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
        if (D_807FD618[gCurrentPlayerIndex].value != 0.0f) {
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

typedef struct LD5Pad {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ u16 buttons;
    /* 0x2E */ u8 pad2E;
    /* 0x2F */ s8 stickY;
    /* 0x30 */ u8 pad30[4];
} LD5Pad;

extern LD5Pad gPlayerPadState[];
typedef struct PadS8Slot {
    /* 0x00 */ s8 value;
    /* 0x01 */ u8 pad1[0x33];
} PadS8Slot;

extern PadS8Slot D_807FD63F[];
extern f32 D_80753D70[];
extern f32 D_80753D8C[];
extern s16 D_80753DA8[];
extern s16 D_80753DB8[];

void playerStateBounceRecover(void) {
    f32 ledgeY;
    u8 pad1;
    u8 angleOk;
    s16 angle;
    f32 t;
    s16 pad2;
    u8 a;
    f32 f;
    f32 ledgeOffset;
    u8 v;
    u8 flag;
    s16 hitA;
    s16 hitB;
    u8 onLedge;
    s32 pad3;

    onLedge = 0;
    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        ledgeOffset = D_80753D70[gCurrentCharacterIndex];
    } else {
        ledgeOffset = D_80753D8C[gCurrentCharacterIndex];
    }
    switch (gCurrentActor->unk155) {
    case 0:
        playerInputUpdate(0x5A);
        gActivePlayerState->unkEC = gCurrentActor->yaw;
        gActivePlayerState->unkF8 = 5;
        gCurrentActor->unk155 = 2;
        break;
    case 1:
    case 2:
    case 3:
        if (gActivePlayerState->unkF8 != 0) {
            gActivePlayerState->unkF8 -= 1;
        }
        if (playerInputUpdate(0x5A) == 0) {
            switch (gActivePlayerState->unk8) {
            case -1:
                if (gCurrentActor->unk155 == 1) {
                    t = gCurrentActor->speedXZ * 0.025;
                    f = t > 0.1 ? t : 0.1;
                    scriptSetActorRampTarget(gCurrentActor, f, 1.0f);
                } else {
                    actorScriptStartByIndex(gActivePlayerActor, 0x77);
                    gCurrentActor->unk155 = 1;
                }
                break;
            case 0:
                if (gCurrentActor->unk155 != 2) {
                    actorScriptStartByIndex(gActivePlayerActor, 0x76);
                    gCurrentActor->unk155 = 2;
                }
                break;
            case 1:
                if (gCurrentActor->unk155 == 3) {
                    t = gCurrentActor->speedXZ * 0.025;
                    f = t > 0.1 ? t : 0.1;
                    scriptSetActorRampTarget(gCurrentActor, f, 0.0f);
                } else {
                    actorScriptStartByIndex(gActivePlayerActor, 0x78);
                    gCurrentActor->unk155 = 3;
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
            angle = gActivePlayerState->unkEA + 0x400;
            angle &= 0xFFF;
            gCurrentActor->moveYaw = gCurrentActor->arcYawMin + 0xA;
        } else if (gCurrentActor->speedXZ > 0.0f) {
            angle = gActivePlayerState->unkEA - 0x400;
            angle &= 0xFFF;
            gCurrentActor->moveYaw = gCurrentActor->arcYawMax - 0xA;
        }
        angleOk = actorSetTargetAngleAndCheck(gCurrentActor, angle);
        if (angleOk == 0) {
            gCurrentActor->speedXZ = 0.0f;
        }
        gActivePlayerState->unkEC = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax) + 0x800;
        gActivePlayerState->unkEC &= 0xFFF;
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, gActivePlayerState->unkEC, 3.0f);
        gCurrentActor->x = gActivePlayerState->unkE0;
        gCurrentActor->z = gActivePlayerState->unkE4;
        if (angleOk == 0 || gCurrentActor->speedXZ == 0.0) {
            gCurrentActor->flags |= 0x800;
        } else {
            gCurrentActor->flags &= ~0x800;
        }
        break;
    }
    flag = gPlayerPadState[gCurrentPlayerIndex].stickY < -0x32 && (gPlayerPadState[gCurrentPlayerIndex].buttons & 0x2000);
    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        a = flag;
        a |= gCurrentActor->y - gCurrentActor->floorY < D_80753DA8[gCurrentCharacterIndex];
    } else {
        a = flag;
        a |= gCurrentActor->y - gCurrentActor->floorY < D_80753DB8[gCurrentCharacterIndex];
    }
    if (gActivePlayerState->unkF8 == 0) {
        v = gCurrentActor->hasArcBounds == 0 || onLedge == 0;
        collisionGetCoords(&hitA, &hitB);
        if (hitB < 0x385) {
            v |= 1;
        }
    } else {
        v = 0;
    }
    if (a != 0 || v != 0) {
        gActivePlayerState->invulnTimer = 0x14;
        playerResumeLocomotion(gCurrentActor);
        gCurrentActor->flags &= ~0x800;
    }
    if (D_807FD63F[gCurrentPlayerIndex].value >= 0x33 && gActivePlayerState->unkF8 == 0 && v == 0) {
        actorScriptStartByIndex(gActivePlayerActor, 0x79);
        gCurrentActor->state = 0x5C;
        gCurrentActor->unk155 = 0;
        gActivePlayerState->unkF0 = gCurrentActor->y + ledgeOffset;
        gActivePlayerState->unkF4 = gActivePlayerState->unkF0;
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
    f32 f;
    f32 ledgeY;
    f32 d;

    gCurrentActor->speedY = 0.0f;
    gCurrentActor->speedXZ = 0.0f;
    playerInputUpdate(1);
    if (playerProbeLedgeAhead(gCurrentActor, &ledgeY, 1, 15.0f) != 0) {
        gActivePlayerState->unkF0 = ledgeY;
    }
    if (gActivePlayerState->unkF0 < gActivePlayerState->unkF4) {
        f = gActivePlayerState->unkF4 - gActivePlayerState->unkF0;
    } else {
        f = -(gActivePlayerState->unkF4 - gActivePlayerState->unkF0);
    }
    if (f > 20.0) {
        playerEnterFall(gCurrentActor);
        actorUpdateModelMatrix(gCurrentActor, 0);
        return;
    }
    gActivePlayerState->unkF4 = gActivePlayerState->unkF0;
    gCurrentActor->flags |= 0x08000000;
    actorUpdateModelMatrix(gCurrentActor, 0);
    actorCheckBoundsAndMotion(gCurrentActor);
    switch (gCurrentActor->unk155) {
    case 0:
        switch (gCurrentActor->actorType) {
        case 4:
            f = gCurrentActor->sub4->model->frame;
            if (f < 25.0f) {
                actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
                d = nodeY - gCurrentActor->y;
                gCurrentActor->y = gActivePlayerState->unkF0 - d;
                f = gCurrentActor->sub4->model->frame;
            }
            if (f < 25.0f) {
                gCurrentActor->x = gActivePlayerState->unkE0;
                gCurrentActor->z = gActivePlayerState->unkE4;
            } else if (f < 31.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 70.0f;
                gCurrentActor->y = gActivePlayerState->unkF0;
            } else {
                gCurrentActor->y = gActivePlayerState->unkF0;
            }
            break;
        case 5:
            f = gCurrentActor->sub4->model->frame;
            if (f < 17.0f) {
                actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
                d = nodeY - gCurrentActor->y;
                gCurrentActor->y = gActivePlayerState->unkF0 - d;
                f = gCurrentActor->sub4->model->frame;
            }
            if (f < 19.0f) {
                gCurrentActor->x = gActivePlayerState->unkE0;
                gCurrentActor->z = gActivePlayerState->unkE4;
            } else if (f < 29.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 40.0f;
                gCurrentActor->y = gActivePlayerState->unkF0;
            } else {
                gCurrentActor->y = gActivePlayerState->unkF0;
            }
            break;
        case 2:
            actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
            d = nodeY - gCurrentActor->y;
                gCurrentActor->y = gActivePlayerState->unkF0 - d;
            if (gCurrentActor->sub4->model->frame > 16.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->y = gActivePlayerState->unkF0;
                gCurrentActor->speedXZ = 30.0f;
            } else {
                gCurrentActor->x = gActivePlayerState->unkE0;
                gCurrentActor->z = gActivePlayerState->unkE4;
            }
            break;
        case 6:
        case 7:
            f = gCurrentActor->sub4->model->frame;
            if (f < 18.0f) {
                actorGetNodePos(gCurrentActor, 7, &nodeX, &nodeY, &nodeZ);
                d = nodeY - gCurrentActor->y;
                gCurrentActor->y = gActivePlayerState->unkF0 - d;
                gCurrentActor->x = gActivePlayerState->unkE0;
                gCurrentActor->z = gActivePlayerState->unkE4;
            } else if (f < 26.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 50.0f;
                gCurrentActor->y = gActivePlayerState->unkF0;
            } else {
                if (gActivePlayerState->unkF0 < gCurrentActor->floorY) {
                    f = gCurrentActor->floorY - gActivePlayerState->unkF0;
                } else {
                    f = -(gCurrentActor->floorY - gActivePlayerState->unkF0);
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
            d = nodeY - gCurrentActor->y;
                gCurrentActor->y = gActivePlayerState->unkF0 - d;
            if (gCurrentActor->sub4->model->frame > 14.0f) {
                gCurrentActor->moveYaw = gCurrentActor->yaw;
                gCurrentActor->speedXZ = 10.0f;
                gCurrentActor->y = gActivePlayerState->unkF0;
            } else {
                gCurrentActor->x = gActivePlayerState->unkE0;
                gCurrentActor->z = gActivePlayerState->unkE4;
            }
            break;
        }
        playerApplyMotion();
        break;
    case 1:
        playerApplyMotion();
        if (gActivePlayerState->unkF0 < gCurrentActor->floorY) {
            f = gCurrentActor->floorY - gActivePlayerState->unkF0;
        } else {
            f = -(gCurrentActor->floorY - gActivePlayerState->unkF0);
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
        gActivePlayerState->decelRate = gKongCannonInitialPitch[gCurrentCharacterIndex] * 5.0;
    }
    playerApplyFullPhysics();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s32 D_80750FDC;

void playerStateCutscenePause(void) {
    if (gCurrentActor->unk155 == 0) {
        camSetTarget(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, 0x32, 0, 5, 0x32, 0x14, 0, 0.2f);
        gCurrentActor->unk155++;
    }
    playerApplyImpactRumble(1);
    gActivePlayerState->decelRate = D_80750FDC;
}

void playerStateBarrelBlast(void) {
    switch (gCurrentActor->unk155) {
    case 0:
        camSetTargetScaled(gActivePlayerState->camActor, gCurrentActor, 4, 0, 0x19, 0, 5, -3, 0xA, 0, 0.15f);
        actorScriptStartByIndex(gCurrentActor, 0x85);
        gCurrentActor->unk155++;
    case 2:
        camSetTargetScaled(gActivePlayerState->camActor, gCurrentActor, 4, 0x396, 0x19, 0, 5, 0xB, 0xB, 0, 0.15f);
        gCurrentActor->unk155++;
        break;
    case 4:
        camSetTargetScaled(gActivePlayerState->camActor, gCurrentActor, 4, 0xE74, 0x14, 0, 5, 0x13, 0xA, 0, 0.15f);
        gCurrentActor->unk155++;
        break;
    case 6:
        camSetTargetScaled(gActivePlayerState->camActor, gCurrentActor, 4, 0x800, 0x11, 0, 5, 0x29, 0xA, 0, 0.15f);
        gCurrentActor->unk155++;
        break;
    case 8:
        camResetPlayer(gCurrentActor, 0);
        gActivePlayerState->stateFlags |= 4;
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void playerStateResumeFromCutscene(void) {
    if (gCurrentActor->unk155 == 1) {
        camResumePath();
        gCurrentActor->unk155++;
        playerResumeLocomotion(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct G20Sub174 {
    /* 0x000 */ u8 pad0[0x1A4];
    /* 0x1A4 */ u8 playerIndex;
} G20Sub174;

typedef struct G20Light {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[2];
    /* 0x1E */ u8 unk1E;
} G20Light;

extern s32 D_80750FE0;
extern s32 D_80750FF0;

void playerStateDialogueWait(void) {
    G20Light *light;
    G20Sub174 *owner;
    s32 col;
    s32 *p;
    s32 sel;
    s16 pathIndex;

    playerInputUpdate(1);
    playerClearPitchRollFlags(gCurrentActor);
    sel = gCurrentActor->unk155;
    switch (sel) {
    case 0:
        if (func_806F8EB4() == 0x14) {
            pathIndex = 0x1A;
        } else {
            pathIndex = 0x11;
        }
        camStartPath(gCurrentActor, pathIndex, 5);
        gCurrentActor->unk155 = 1;
        break;
    case 1:
        gGlobalPauseFlags &= 0xFFFEFFCF;
        actorSpawn(0x141, 0x3D);
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY * 2);
        gSpawnedActor->flags |= 0x40000000;
        gSpawnedActor->yaw += 0x800;
        gSpawnedActor->yaw &= 0xFFF;
        gSpawnedActor->parentActor = gCurrentActor;
        actorScriptStart(gSpawnedActor, 0x2B7);
        light = gSpawnedActor->customState;
        light->unk10 = gCurrentActor;
        light->unk18 = gCurrentActor->chunkIndex;
        col = light->unk18;
        if (col == -1) {
            light->unk18 = 0;
            col = 0;
        }
        light->unk16 = gCurrentActor->roll;
        light->unk14 = gCurrentActor->pitch;
        lightGetColor(&light->unk0, &light->unk4, &light->unk8, col);
        lightSetColor(1.0f, 1.0f, 1.0f, light->unk18);
        actorSpawn(0x136, 0xA8);
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleX);
        gSpawnedActor->flags |= 0x40000000;
        light->unkC = gSpawnedActor;
        light->unk1E = func_806F8EB4() == 0x14;
        gCurrentActor->unk155 = 2;
        break;
    case 2:
        if (currentActorTestClearFlag()) {
            currentActorClearFlag();
            effectSpawnKongRing();
            sfxAllocateChannel(0x3B, 1.0f);
            gCurrentActor->unk155 = 3;
        }
    case 3:
        if (currentActorTestClearFlag()) {
            owner = gCurrentActor->customState;
            currentActorClearFlag();
            playerResumeLocomotion(gCurrentActor);
            healthRefill(owner->playerIndex);
            p = &D_80750FE0;
            do {
                slotQueueAddValue(*p, 0, 0x270F);
                slotQueueUpdate(*p, 0, 0);
            } while (++p != &D_80750FF0);
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 gSplitScreenMode;

void playerStateDialogueHold(void) {
    G20Sub174 *sub = gCurrentActor->customState;
    s32 step;
    s16 cur;

    playerStateQueueCallback(0x5C, 0, gCurrentPlayerIndex);
    if (gSplitScreenMode == 0) {
        gPlayerSlots[sub->playerIndex].unk2EA = 1;
    }
    gPlayerSlots[sub->playerIndex].unk2EB = 1;
    gCurrentActor->flags &= 0xFFFF7FFF;
    cur = gCurrentActor->alpha;
    step = (cur < 4) ? cur : 4;
    gCurrentActor->alpha = cur - step;
    if (gCurrentActor->alpha == 0) {
        if (gSplitScreenMode == 0) {
            gPlayerSlots[sub->playerIndex].unk0 = 0;
        }
        gCurrentActor->flags &= ~4;
    }
    playerApplyGravityAndMotion();
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct G20Target {
    /* 0x000 */ u8 pad0[0x220];
    /* 0x220 */ f32 unk220;
    /* 0x224 */ u8 pad224[4];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
} G20Target;

void func_806DF1A0(void) {
    G20Target *t = gCurrentActor->customState;

    gCurrentActor->sub4->scaleX *= 0.92;
    gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleX;
    gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleX;
    gCurrentActor->x += (t->unk22C - gCurrentActor->x) * 0.125f;
    gCurrentActor->y += (t->unk230 - gCurrentActor->y) * 0.125f;
    gCurrentActor->z += (t->unk234 - gCurrentActor->z) * 0.125f;
    gCurrentActor->pitch += 0xFF;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void func_806DF280(void) {
    G20Target *t = gCurrentActor->customState;

    gCurrentActor->sub4->scaleX *= 1.08;
    if (gCurrentActor->sub4->scaleX > 0.15) {
        gCurrentActor->sub4->scaleX = 0.15f;
        gCurrentActor->state = 0xC;
        gCurrentActor->unk155 = 0;
        gCurrentActor->pitch = -0xFF;
    }
    gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleX;
    gCurrentActor->sub4->scaleZ = gCurrentActor->sub4->scaleX;
    gCurrentActor->x += t->unk220;
    gCurrentActor->z += t->unk228;
    gCurrentActor->pitch += 0xFF;
    gCurrentActor->pitch &= 0xFFF;
    actorUpdateModelMatrix(gCurrentActor, 0);
}
