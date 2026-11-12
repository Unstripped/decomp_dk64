#include "common.h"
#include "actor.h"
#include "proto/boss/3840.h"
#include "proto/boss/9C60.h"
#include "proto/boss/A7A0.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/70FD0.h"
#include "proto/global/7CA80.h"
#include "proto/global/EFDC0.h"

typedef struct BossScriptState {
    /* 0x00 */ Actor *linkedActor;
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ u8 phase;
    /* 0x15 */ u8 scriptPos;
} BossScriptState;

// K. Rool (Lanky phase) actor: component 1 (0x174) is gBehaviourWorkState, component 2 the script state.
typedef struct BossKRoolLankyActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
} BossKRoolLankyActor;

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern u8 *D_80035A80[];

void bossResetMinions(Actor *excludeActor) {
    s16 i;
    Actor *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if ((excludeActor == NULL || actor != excludeActor) && actor->actorType == 0xDE) {
            actor->flags &= ~0x8000;
            actor->state = 1;
            actor->unk155 = 0;
        }
    }
}

void bossPhaseTick(void) {
    Actor *other;

    if (!(gCurrentActor->flags & 0x10)) {
        bossResetMinions(gCurrentActor);
        gCurrentActor->yawSpeed = 0x258;
        gCurrentActor->unk144 = 2;
    }
    if (gPrimaryPlayerActor->state != 0x67) {
        if (gCurrentActor->yawSpeed != 0) {
            gCurrentActor->yawSpeed--;
        } else {
            gCurrentActor->flags &= ~0x8000;
            gCurrentActor->state = 1;
            gCurrentActor->unk155 = 0;
        }
    }
    if (((gActorGlobalState.unk15 != 0) || (gActorGlobalState.bossFightPhase == 9)) &&
        ((other = gActorGlobalState.targetActor)->state == 0x2B) &&
        (other->unk155 == 3)) {
        gCurrentActor->state = 1;
        gCurrentActor->unk155 = 0;
        gCurrentActor->parentActor->state = 0x64;
        gCurrentActor->parentActor->unk155 = 0;
        other->unk155 = 0;
        other->state = 0x31;
    }
    if (gCurrentActor->state == 1) {
        gCurrentActor->unk144 = 1;
        gCurrentActor->alpha -= 10;
        if (gCurrentActor->alpha < 0) {
            actorDespawn(gCurrentActor);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bossKRoolLankySetAnim(s32 scriptId, s16 animId) {
    BossScriptState *scriptState = ((BossKRoolLankyActor *)gCurrentActor)->scriptState;

    actorScriptStart(gCurrentActor, scriptId);
    actorScriptExecute(gCurrentActor);
    controllerAnimSetState(scriptState->linkedActor, animId, 0.0f, 6.0f);
}

void bossKRoolLankyRunTowardPlayer(void) {
    BossScriptState *scriptState = ((BossKRoolLankyActor *)gCurrentActor)->scriptState;

    bossKRoolLankySetAnim(0x406, 0x674);
    actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed + (scriptState->phase * 10) + 15);
}

void bossKRoolLankyStep(void) {
    BossScriptState *scriptState;
    u8 *scriptOpcodes;

    scriptState = ((BossKRoolLankyActor *)gCurrentActor)->scriptState;
    scriptOpcodes = D_80035A80[scriptState->phase];
    behaviourFrameBegin();
    bossRoundFrame(scriptOpcodes);
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk146 = 1;
        gCurrentActor->state = 0x1E;
        gCurrentActor->unk155 = 0;
        gCurrentActor->floorNodeId = 1;
        func_80724CA4(2, 1);
        bossAttachActor();
        gCurrentActor->accelY = 0.0f;
    }
    if ((gPrimaryPlayerActor->state == 0x48) && !(gBehaviourWorkState->flags & 0x8000)) {
        camStartPath(gCurrentActor, 0, 1);
        gBehaviourWorkState->flags |= 0x8000;
    }
    if ((camIsPlayingPath(0) == 0) && (camIsPlayingPath(1) == 0) && ((gPrimaryPlayerActor->state != 0x67) || (gCurrentActor->state != 0x42))) {
        switch (gCurrentActor->state) {
        case 0x2B:
            switch (gCurrentActor->unk155) {
            case 0:
                actorSetTargetSpeed(gCurrentActor, 0);
                camStartPath(gPrimaryPlayerActor, 9, 1);
                bossKRoolLankySetAnim(0x3F5, 0x679);
                gCurrentActor->unk155++;
                break;
            case 2:
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkD);
                bossKRoolLankySetAnim(0x3F4, 0x678);
                gCurrentActor->unk155++;
                break;
            case 3:
                if (gActorGlobalState.unk1B != 0) {
                    gCurrentActor->state = 0x31;
                    gCurrentActor->unk155 = 0;
                } else if (gActorGlobalState.bossFightPhase == 2) {
                    bossResetMinions(NULL);
                    gCurrentActor->state = 0x2C;
                    gCurrentActor->unk155 = 0;
                }
                actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
                break;
            }
            break;
        case 0x2C:
            if (gCurrentActor->unk155 == 0) {
                playerStateQueueCallback(0x36, gCurrentActor, 0);
                bossKRoolLankyRunTowardPlayer();
                gCurrentActor->state = 0x42;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 0x1E:
            scriptState->phase = 0;
            scriptState->scriptPos = 0;
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        case 0:
            switch (gCurrentActor->unk155) {
            case 0:
                bossKRoolLankySetAnim(0x3F5, 0x679);
                gCurrentActor->unk155++;
                break;
            case 2:
                bossKRoolLankyRunTowardPlayer();
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
                actorSetCollisionRadius(gPrimaryPlayerActor, gPrimaryPlayerActor->collision->scaledRadius * 2);
                actorOrNodeFlags(gPrimaryPlayerActor, 6, 1);
                actorOrNodeFlags(gPrimaryPlayerActor, 7, 1);
                actorOrNodeFlags(gPrimaryPlayerActor, 8, 1);
                actorOrNodeFlags(gPrimaryPlayerActor, 9, 1);
                actorOrNodeFlags(gPrimaryPlayerActor, 0xA, 1);
                actorOrNodeFlags(gPrimaryPlayerActor, 0xB, 1);
                break;
            }
            break;
        case 0x31:
            switch (gCurrentActor->unk155) {
            case 0:
                if (scriptState->phase == 3) {
                    gCurrentActor->state = 0x37;
                    gCurrentActor->unk155 = 0;
                } else {
                    actorScriptStart(gCurrentActor, 0x3F2);
                    actorScriptStart(scriptState->linkedActor, 0x3F1);
                    actorSetTargetSpeed(gCurrentActor, 0);
                    gCurrentActor->unk155++;
                }
                break;
            case 1:
                actorMoveWithinZone(0, 0.0f, 0.0f, 0x310, 0.0f);
                break;
            case 2:
                bossResetMinions(NULL);
                bossKRoolLankyRunTowardPlayer();
                scriptState->scriptPos = 0;
                scriptState->phase++;
                scriptOpcodes = D_80035A80[scriptState->phase];
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
                break;
            }
            break;
        case 0x37:
            switch (gCurrentActor->unk155) {
            case 0:
                actorDespawn(scriptState->linkedActor);
                actorScriptStart(gCurrentActor, 0);
                camStartPath(gCurrentActor, 5, 1);
                gCurrentActor->unk155++;
                break;
            case 1:
                if (currentActorTestClearFlag() != 0) {
                    screenSetTransitionFadeType(0);
                    mapRequestTransition(0xCE, 0);
                    gCurrentActor->unk155++;
                }
                break;
            }
            break;
        default:
            bossScriptStep(scriptOpcodes, 0x10, 0.0f);
            break;
        }
    } else if (gCurrentActor->sub4->animId == 0x406) {
        scriptSetActorRampTarget(gCurrentActor, 0.0f, 0.0f);
    }
    behaviourUpdateShadowAlpha();
    if (func_8072881C(0, &gBehaviourWorkState->unk28) != 0) {
        func_8072881C(0x81, &gBehaviourWorkState->unk28);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/A7A0/D_80036840.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/A7A0/D_80036850.s")
