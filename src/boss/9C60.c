#include "common.h"
#include "actor.h"
#include "proto/boss/3840.h"
#include "proto/boss/9C60.h"
#include "proto/global/17B90.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

// Actor plus its component pointers (0x174 on).
typedef struct BossC_9C60_Actor {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ void* unk178;
} BossC_9C60_Actor;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;

s32 actorSpawn(s32, s32);
void actorCopyPoseAndScale(Actor *, Actor *, f32);
void actorDespawn(void *);
void bossAttachActor(void) {
    Actor **attachedActorSlot = ((BossC_9C60_Actor *)gCurrentActor)->unk178;

    actorSpawn(0xDD, 0xE3);
    gSpawnedActor->flags |= 0x400;
    gSpawnedActor->parentActor = gCurrentActor;
    *attachedActorSlot = gSpawnedActor;
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

typedef struct BossC_9C60_Target {
    char pad[0x58];
    s32 unk58;
} BossC_9C60_Target;

typedef struct {
    BossC_9C60_Target *actor;
    s32 pad;
} BossC_9C60_Entry;

extern BossC_9C60_Entry gActiveActors[];
extern u16 gActiveActorCount;

void actorDespawn(void *);

void bossDespawnEntities(void) {
    s16 i;
    BossC_9C60_Target *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (actor->unk58 == 0xAA) {
            actorDespawn(actor);
        }
    }
}

typedef struct Boss2F_9C60_178 {
    void *unk0;
    char pad4[0x10];
    u8 unk14;
    u8 unk15;
    char pad16[2];
    u8 unk18;
    u8 unk19;
} Boss2F_9C60_178;

typedef struct Boss2F_9C60_BB4C {
    char pad[0x6A];
    u16 unk6A;
} Boss2F_9C60_BB4C;



extern u8 *D_80035A60[];
extern Actor *gCamActor;
extern Boss2F_9C60_BB4C *gPrimaryPlayerActor;

void actorScriptExecute(Actor *);
void actorScriptStart(Actor *, s32);
u8 camIsCutsceneActive(void);
u16 camStartPath(void *, s16, u8);
void camStartShake(struct CamActor *, u8, u16);
void camSetSecondTarget(struct CamActor *, s16, s16);
s32 currentActorTestClearFlag(void);
void csModelStateSetFirstByte(s16, s16);
void projectileGetTargetCoords(Actor *, s32);
void projectileSpawnNodeEntry(s16, s16, f32, s16, f32, f32, Actor *);
void func_80724CA4(s16, s16);
void func_80724E48(u8);
u8 func_8072881C(u8, u32 *);
void behaviourFrameBegin(void);
void behaviourUpdateShadowAlpha(void);
void actorSetTargetSpeed(Actor *, s32);
void actorTurnTowardActorYaw(u8, Actor *);

void bossKRoolDiddyStep(void) {
    Boss2F_9C60_178 *scriptState;
    u8 *scriptOpcodes;
    s32 pad34;
    f32 projectileScale;
    u8 action;

    scriptState = ((BossC_9C60_Actor *)gCurrentActor)->unk178;
    scriptOpcodes = D_80035A60[scriptState->unk14];
    projectileScale = (gPrimaryPlayerActor->unk6A & 1) ? 0.7 : 1.0;
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
        scriptState->unk14 = 0;
        scriptState->unk15 = 0;
        gCurrentActor->state = scriptOpcodes[scriptState->unk15++];
        gCurrentActor->unk155 = 0;
        gCurrentActor->speedXZ = gBehaviourExtraState->targetSpeed;
        break;
    case 0x27:
        actorScriptStart(gCurrentActor, 0x3E1);
        gCurrentActor->state = scriptOpcodes[scriptState->unk15++];
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
                csModelStateSetFirstByte((scriptState->unk14 * 2) + 8, 0xA);
                csModelStateSetFirstByte((scriptState->unk14 * 2) + 9, 0xA);
                gCurrentActor->state = scriptOpcodes[scriptState->unk15++];
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
            gCurrentActor->state = scriptOpcodes[scriptState->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x28:
        switch (gCurrentActor->unk155) {
        case 0:
            scriptState->unk18 = scriptOpcodes[scriptState->unk15++];
            scriptState->unk19 = scriptOpcodes[scriptState->unk15++];
            gCurrentActor->unk155++;
            /* fallthrough */
        case 1:
            if (camIsCutsceneActive() == 0) {
                gBehaviourWorkState->timer = scriptState->unk18;
                actorScriptStart(gCurrentActor, 0x3EF);
                gCurrentActor->unk155++;
            }
            break;
        case 3:
            gCurrentActor->unk146 = 6;
            projectileGetTargetCoords(gCurrentActor, 4);
            projectileSpawnNodeEntry(0xAA, 1, gCurrentActor->sub4->scaleY, 0, (f32)scriptState->unk19 * projectileScale, 0.0f, gCurrentActor);
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
                if ((gPrimaryPlayerActor->unk6A & 1) && (gBehaviourWorkState->timer >= 0xB)) {
                    gBehaviourWorkState->timer = 0xA;
                }
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->state = scriptOpcodes[scriptState->unk15++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x29:
        switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->unk146 = 5;
            actorScriptStart(gCurrentActor, scriptState->unk14 ? 0x409 : 0x408);
            actorScriptExecute(gCurrentActor);
            controllerAnimSetStateIfChanged(scriptState->unk0, 0x675, 0.0f, 0.0f);
            gCurrentActor->unk155++;
            break;
        case 2:
            gCurrentActor->state = scriptOpcodes[scriptState->unk15++];
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
                if (scriptState->unk14 == 3) {
                    gCurrentActor->state = 0x37;
                    gCurrentActor->unk155 = 0;
                } else {
                    bossAttachActor();
                    gCurrentActor->unk146 = 1;
                    actorScriptStart(gCurrentActor, 0x404);
                    actorScriptExecute(gCurrentActor);
                    controllerAnimSetStateIfChanged(scriptState->unk0, 0x673, 0.0f, 0.0f);
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
            scriptState->unk15 = 0;
            scriptState->unk14++;
            scriptOpcodes = D_80035A60[scriptState->unk14];
            actorScriptStart(gCurrentActor, 0x406);
            actorScriptExecute(gCurrentActor);
            controllerAnimSetStateIfChanged(scriptState->unk0, 0x674, 0.0f, 0.0f);
            gCurrentActor->state = scriptOpcodes[scriptState->unk15++];
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
