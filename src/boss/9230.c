#include "common.h"
#include "actor.h"
#include "boss.h"
#include "proto/boss/3840.h"
#include "proto/boss/9230.h"
#include "proto/global/12E800.h"
#include "proto/global/1295B0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/7130.h"
#include "proto/global/936B0.h"

// K. Rool (DK phase) actor: component 2 (0x178) is the script state.
typedef struct BossKRoolDkActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
} BossKRoolDkActor;

extern u8 *D_80035A50[];
extern Actor *gCamActor;
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;

void bossKRoolDkStep(void) {
    BossScriptState *scriptState;
    s32 pad40;
    u8 *scriptOpcodes;

    scriptState = ((BossKRoolDkActor *)gCurrentActor)->scriptState;
    scriptOpcodes = D_80035A50[scriptState->phase];
    behaviourFrameBegin();
    bossRoundFrame(scriptOpcodes);
    if (!(gCurrentActor->flags & 0x10)) {
        camSetSecondTarget(gCamActor, 0, 0);
        gCurrentActor->segmentFlags = 5;
        gCurrentActor->state = 0x1E;
        gCurrentActor->unk155 = 0;
        gCurrentActor->floorNodeId = 1;
    }
    switch (gCurrentActor->state) {
    case 0x2B:
        csSendActorMessagePayload(1, 0);
        csSendActorMessagePayload(2, 0);
        csSendActorMessagePayload(3, 0);
        csSendActorMessagePayload(4, 0);
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->unk155 = 0;
        break;
    case 0x1E:
        scriptState->phase = 0;
        scriptState->scriptPos = 0;
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
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
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x29:
    case 0x2A:
        actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
        if (gActorGlobalState.bossFightPhase == 4) {
            csSendActorMessagePayload(gActivePlayerState->hitActorId, 1);
            if (scriptState->phase == 3) {
                gCurrentActor->state = 0x37;
                gCurrentActor->unk155 = 0;
            } else {
                behaviourSpawnExplosionAndSound(0x3EE, 0x31, gPrimaryPlayerActor);
                camStartPath(gCurrentActor, 1, 1);
                gCurrentActor->speedXZ *= 0.7;
            }
        } else if (gActorGlobalState.bossFightPhase == 2 && gCurrentActor->unk155 > 0) {
            actorScriptStart(gCurrentActor, 0);
            gCurrentActor->state = 0;
            gCurrentActor->unk155 = 0;
        } else
            if (gPrimaryPlayerActor->state != 0x42 && gPrimaryPlayerActor->state != 0x44 && gCurrentActor->unk155 > 0) {
                actorScriptStart(gCurrentActor, 0);
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
            } else {
            switch (gCurrentActor->unk155) {
            case 0:
                scriptState->unk18[0] = scriptOpcodes[scriptState->scriptPos++];
                scriptState->unk18[1] = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155++;
                /* fallthrough */
            case 1:
                gBehaviourWorkState->timer = scriptState->unk18[0];
                gCurrentActor->unk155++;
                /* fallthrough */
            case 2:
                gCurrentActor->interactionType = 1;
                actorScriptStart(gCurrentActor, 0x3EC);
                gCurrentActor->unk155++;
                break;
            case 4:
                if (gBehaviourWorkState->timer != 0) {
                    gBehaviourWorkState->timer--;
                    gCurrentActor->unk155 = 2;
                } else {
                    gCurrentActor->interactionType = 2;
                    actorScriptStart(gCurrentActor, 0x3E9);
                    gBehaviourWorkState->timer = scriptState->unk18[1];
                    gCurrentActor->unk155++;
                }
                break;
            case 5:
                if (gBehaviourWorkState->timer != 0) {
                    gBehaviourWorkState->timer--;
                } else if (gCurrentActor->state == 0x2A) {
                    gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                    gCurrentActor->unk155 = 0;
                } else {
                    gCurrentActor->unk155 = 1;
                }
                break;
            }
        }
        break;
    case 0x28:
    case 0x2C:
        actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
        if (gPrimaryPlayerActor->state == 0x42 && gCurrentActor->unk155 > 0) {
            actorScriptStart(gCurrentActor, 0);
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155 = 0;
        } else {
            switch (gCurrentActor->unk155) {
            case 0:
                scriptState->unk18[0] = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155++;
                /* fallthrough */
            case 1:
                if (camIsCutsceneActive() == 0) {
                    gBehaviourWorkState->timer = scriptState->unk18[0];
                    gBehaviourWorkState->unk2E = 9;
                    actorScriptStart(gCurrentActor, 0x3E7);
                    gCurrentActor->unk155++;
                }
                break;
            case 3:
                if (gCurrentActor->state == 0x28 || (gCurrentActor->state == 0x2C && (gBehaviourWorkState->unk2E % 3) == 0)) {
                    projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 0x96, 3, (f32)(((f64)scriptState->phase * 0.01) + 1.04), 0.0f, 0.0f, 0.0f);
                    sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x25A, 0xFF, 0x7F, 1, 0, 0.3f, 0);
                    controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0.0f, 0.0f);
                    scriptSetActorRampTarget(gSpawnedActor, 0.5f, 0.0f);
                }
                if (gCurrentActor->state == 0x28 || (gCurrentActor->state == 0x2C && gBehaviourWorkState->unk2E == 0)) {
                    gCurrentActor->unk155++;
                } else {
                    gBehaviourWorkState->unk2E--;
                    break;
                }
                /* fallthrough */
            case 4:
                if (gBehaviourWorkState->timer != 0) {
                    gBehaviourWorkState->timer--;
                } else if (scriptState->loopPos != 0) {
                    gCurrentActor->unk155 = 1;
                } else {
                    gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                    gCurrentActor->unk155 = 0;
                }
                break;
            }
        }
        break;
    case 0x31:
        switch (gCurrentActor->unk155) {
        case 0:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4310, 0.0f);
            break;
        case 1:
            gCurrentActor->speedXZ = -40.0f;
            gCurrentActor->unk155++;
            /* fallthrough */
        case 2:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4310, 0.0f);
            break;
        case 3:
            actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
            scriptState->scriptPos = 0;
            scriptState->loopPos = 0;
            scriptState->phase++;
            scriptOpcodes = D_80035A50[scriptState->phase];
            actorScriptStart(gCurrentActor, 0x3E3);
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0);
            camStartPath(gCurrentActor, 2, 1);
            gCurrentActor->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                screenSetTransitionFadeType(0);
                mapRequestTransition(0xCC, 0);
                gCurrentActor->unk155++;
            }
            break;
        }
        break;
    default:
        bossScriptStep(scriptOpcodes, 0x10, 0.0f);
        break;
    }
    behaviourUpdateShadowAlpha();
    if (func_8072881C(0, &gBehaviourWorkState->unk28) != 0) {
        func_8072881C(0x81, &gBehaviourWorkState->unk28);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9230/D_80036660.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9230/D_80036678.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9230/D_80036688.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9230/D_8003669C.s")
