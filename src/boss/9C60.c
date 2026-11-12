#include "common.h"
#include "actor.h"
#include "boss.h"
#include "proto/boss/3840.h"
#include "proto/boss/9C60.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/69E60.h"
#include "proto/global/7CA80.h"
#include "proto/global/936B0.h"

// K. Rool (Diddy phase) actor: component 1 (0x174) is gBehaviourWorkState, component 2 the script state.
typedef struct BossKRoolDiddyActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
} BossKRoolDiddyActor;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gCamActor;
extern Actor *gPrimaryPlayerActor;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern u8 *D_80035A60[];

void bossAttachActor(void) {
    BossScriptState *scriptState = ((BossKRoolDiddyActor *)gCurrentActor)->scriptState;

    actorSpawn(0xDD, 0xE3);
    gSpawnedActor->flags |= 0x400;
    gSpawnedActor->parentActor = gCurrentActor;
    scriptState->linkedActor = gSpawnedActor;
    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY);
}

void bossUpdateAttachment(void) {
    actorCopyPoseAndScale(gCurrentActor, gCurrentActor->parentActor, gCurrentActor->sub4->scaleY);
    gCurrentActor->sub4->unk48 = gCurrentActor->parentActor->sub4->unk48;
    if (gCurrentActor->sub4->model->animId == 0x675 && gCurrentActor->sub4->model->speed == 0.0f) {
        actorDespawn(gCurrentActor);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bossDespawnEntities(void) {
    s16 i;
    Actor *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (actor->actorType == 0xAA) {
            actorDespawn(actor);
        }
    }
}

void bossKRoolDiddyStep(void) {
    BossScriptState *scriptState;
    u8 *scriptOpcodes;
    s32 pad34;
    f32 projectileScale;
    u8 action;

    scriptState = ((BossKRoolDiddyActor *)gCurrentActor)->scriptState;
    scriptOpcodes = D_80035A60[scriptState->phase];
    projectileScale = (gPrimaryPlayerActor->contactFlags & 1) ? 0.7 : 1.0;
    behaviourFrameBegin();
    bossRoundFrame(scriptOpcodes);
    if (!(gCurrentActor->flags & 0x10)) {
        camSetSecondTarget(gCamActor, 0, 0);
        gCurrentActor->unk146 = 5;
        gCurrentActor->state = 0x1E;
        gCurrentActor->unk155 = 0;
        gCurrentActor->floorNodeId = 1;
        actorScriptStart(gCurrentActor, 0x3E3);
        func_80724CA4(2, 1);
    }
    if (gCurrentActor->state != 0x28) {
        func_80724E48(5);
    }
    switch (gCurrentActor->state) {
    case 0x1E:
        scriptState->phase = 0;
        scriptState->scriptPos = 0;
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->unk155 = 0;
        gCurrentActor->speedXZ = gBehaviourExtraState->targetSpeed;
        break;
    case 0x27:
        actorScriptStart(gCurrentActor, 0x3E1);
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->unk155 = 0;
        break;
    case 0x2C:
        switch (gCurrentActor->unk155) {
        case 0:
            gBehaviourWorkState->timer = 0x14;
            gCurrentActor->unk155++;
            break;
        case 1:
            actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                csModelStateSetFirstByte((scriptState->phase * 2) + 8, 0xA);
                csModelStateSetFirstByte((scriptState->phase * 2) + 9, 0xA);
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x3EA);
            gCurrentActor->unk155++;
            break;
        case 1:
            actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
            break;
        case 2:
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x28:
        switch (gCurrentActor->unk155) {
        case 0:
            scriptState->unk18[0] = scriptOpcodes[scriptState->scriptPos++];
            scriptState->unk18[1] = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155++;
            /* fallthrough */
        case 1:
            if (camIsCutsceneActive() == 0) {
                gBehaviourWorkState->timer = scriptState->unk18[0];
                actorScriptStart(gCurrentActor, 0x3EF);
                gCurrentActor->unk155++;
            }
            break;
        case 3:
            gCurrentActor->unk146 = 6;
            projectileGetTargetCoords(gCurrentActor, 4);
            projectileSpawnNodeEntry(0xAA, 1, gCurrentActor->sub4->scaleY, 0, (f32)scriptState->unk18[1] * projectileScale, 0.0f, gCurrentActor);
            gCurrentActor->unk155++;
            break;
        case 5:
            actorScriptStart(gCurrentActor, 0x3F0);
            gCurrentActor->unk155++;
            break;
        case 7:
            gCurrentActor->unk146 = 5;
            gCurrentActor->unk155++;
            /* fallthrough */
        case 8:
            func_80724E48(0);
            if (gCurrentActor->sub4->boneRotations->rotX < 0x7FFF) {
                gCurrentActor->sub4->boneRotations->rotX = 0xFFFF;
            }
            actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
            if (gBehaviourWorkState->timer != 0) {
                if ((gPrimaryPlayerActor->contactFlags & 1) && (gBehaviourWorkState->timer >= 0xB)) {
                    gBehaviourWorkState->timer = 0xA;
                }
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x29:
        switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->unk146 = 5;
            actorScriptStart(gCurrentActor, scriptState->phase ? 0x409 : 0x408);
            actorScriptExecute(gCurrentActor);
            controllerAnimSetStateIfChanged(scriptState->linkedActor, 0x675, 0.0f, 0.0f);
            gCurrentActor->unk155++;
            break;
        case 2:
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x31:
        switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->unk146 = 5;
            actorScriptStart(gCurrentActor, 0);
            bossDespawnEntities();
            camStartPath(gCurrentActor, 1, 1);
            gCurrentActor->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gCurrentActor, 0x403);
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                camStartShake(gCamActor, 5, 0x14);
                if (scriptState->phase == 3) {
                    gCurrentActor->state = 0x37;
                    gCurrentActor->unk155 = 0;
                } else {
                    bossAttachActor();
                    gCurrentActor->unk146 = 1;
                    actorScriptStart(gCurrentActor, 0x404);
                    actorScriptExecute(gCurrentActor);
                    controllerAnimSetStateIfChanged(scriptState->linkedActor, 0x673, 0.0f, 0.0f);
                    gCurrentActor->unk155++;
                }
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->unk155++;
            }
            break;
        case 4:
            actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
            scriptState->scriptPos = 0;
            scriptState->phase++;
            scriptOpcodes = D_80035A60[scriptState->phase];
            actorScriptStart(gCurrentActor, 0x406);
            actorScriptExecute(gCurrentActor);
            controllerAnimSetStateIfChanged(scriptState->linkedActor, 0x674, 0.0f, 0.0f);
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->yaw = mathAngleBetweenPoints2D(D_807FDCA0->entries[4].x, D_807FDCA0->entries[4].z, gCurrentActor->x, gCurrentActor->z);
            actorScriptStart(gCurrentActor, 0);
            camStartPath(gCurrentActor, 2, 1);
            gCurrentActor->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                screenSetTransitionFadeType(0);
                mapRequestTransition(0xCD, 0);
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

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036750.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036768.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036774.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036780.s")
