#include "common.h"
#include "actor.h"
#include "proto/boss/3840.h"
#include "proto/boss/9230.h"
#include "proto/global/17B90.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"

typedef struct Boss2F_9230_178 {
    char pad0[0x14];
    u8 unk14;
    u8 unk15;
    u8 unk16;
    char pad17[1];
    u8 unk18;
    u8 unk19;
} Boss2F_9230_178;

typedef struct Boss2F_9230_Actor {
    char pad[0x60];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x30];
    f32 unkB8;
    char padBC[0x10];
    u8 unkCC;
    char padCD[0x65];
    s16 unk132;
    char pad134[0x12];
    s16 unk146;
    char pad148[0xC];
    u8 unk154;
    u8 unk155;
    char pad156[0x22];
    Boss2F_9230_178 *unk178;
} Boss2F_9230_Actor;

typedef struct Boss2F_9230_BB4C {
    char pad[0x154];
    u8 unk154;
} Boss2F_9230_BB4C;

typedef struct Boss2F_9230_D580 {
    char pad[0xBE];
    s16 unkBE;
} Boss2F_9230_D580;



extern u8 *D_80035A50[];
extern Actor *gCamActor;
extern Boss2F_9230_Actor *gCurrentActor;
extern void *gSpawnedActor;
extern Boss2F_9230_BB4C *gPrimaryPlayerActor;
extern Boss2F_9230_D580 *gActivePlayerState;

s16 sfxPlayAtPositionPooled(f32, f32, f32, s16, u8, s16, u8, u8, f32, u8);
void scriptSetActorRampTarget(void *, f32, f32);
void actorScriptStart(Boss2F_9230_Actor *, s32);
u8 camIsCutsceneActive(void);
u16 camStartPath(void *, s16, u8);
void camSetSecondTarget(struct CamActor *, s16, s16);
s32 currentActorTestClearFlag();
void projectileSpawnWithShockwave(s16, f32, u8, u8, u8, u8, f32, f32, f32, f32);
u8 func_8072881C(u8, u32 *);
void behaviourFrameBegin(void);
void behaviourUpdateShadowAlpha(void);
u32 actorMoveWithinZone(u8, f32, f32, u16, f32);
void actorSetTargetSpeed(Boss2F_9230_Actor *, s32);
void behaviourSpawnExplosionAndSound(void *, u8, Actor *);
void actorTurnTowardActorYaw(u8, Actor *);

void bossKRoolDkStep(void) {
    Boss2F_9230_178 *scriptState;
    s32 pad40;
    u8 *scriptOpcodes;

    scriptState = gCurrentActor->unk178;
    scriptOpcodes = D_80035A50[scriptState->unk14];
    behaviourFrameBegin();
    bossRoundFrame(scriptOpcodes);
    if (!(gCurrentActor->unk60 & 0x10)) {
        camSetSecondTarget(gCamActor, 0, 0);
        gCurrentActor->unk146 = 5;
        gCurrentActor->unk154 = 0x1E;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unkCC = 1;
    }
    switch (gCurrentActor->unk154) {
    case 0x2B:
        csSendActorMessagePayload(1, 0);
        csSendActorMessagePayload(2, 0);
        csSendActorMessagePayload(3, 0);
        csSendActorMessagePayload(4, 0);
        gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
        gCurrentActor->unk155 = 0;
        break;
    case 0x1E:
        scriptState->unk14 = 0;
        scriptState->unk15 = 0;
        gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
        gCurrentActor->unk155 = 0;
        gCurrentActor->unkB8 = gBehaviourExtraState->targetSpeed;
        break;
    case 0:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x3EA);
            gCurrentActor->unk155++;
            break;
        case 2:
            gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x29:
    case 0x2A:
        actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
        if (gActorGlobalState.bossFightPhase == 4) {
            csSendActorMessagePayload(gActivePlayerState->unkBE, 1);
            if (scriptState->unk14 == 3) {
                gCurrentActor->unk154 = 0x37;
                gCurrentActor->unk155 = 0;
            } else {
                behaviourSpawnExplosionAndSound(0x3EE, 0x31, gPrimaryPlayerActor);
                camStartPath(gCurrentActor, 1, 1);
                gCurrentActor->unkB8 *= 0.7;
            }
        } else if (gActorGlobalState.bossFightPhase == 2 && gCurrentActor->unk155 > 0) {
            actorScriptStart(gCurrentActor, 0);
            gCurrentActor->unk154 = 0;
            gCurrentActor->unk155 = 0;
        } else
            if (gPrimaryPlayerActor->unk154 != 0x42 && gPrimaryPlayerActor->unk154 != 0x44 && gCurrentActor->unk155 > 0) {
                actorScriptStart(gCurrentActor, 0);
                gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
                gCurrentActor->unk155 = 0;
            } else {
            switch (gCurrentActor->unk155) {
            case 0:
                scriptState->unk18 = scriptOpcodes[scriptState->unk15++];
                scriptState->unk19 = scriptOpcodes[scriptState->unk15++];
                gCurrentActor->unk155++;
                /* fallthrough */
            case 1:
                gBehaviourWorkState->timer = scriptState->unk18;
                gCurrentActor->unk155++;
                /* fallthrough */
            case 2:
                gCurrentActor->unk132 = 1;
                actorScriptStart(gCurrentActor, 0x3EC);
                gCurrentActor->unk155++;
                break;
            case 4:
                if (gBehaviourWorkState->timer != 0) {
                    gBehaviourWorkState->timer--;
                    gCurrentActor->unk155 = 2;
                } else {
                    gCurrentActor->unk132 = 2;
                    actorScriptStart(gCurrentActor, 0x3E9);
                    gBehaviourWorkState->timer = scriptState->unk19;
                    gCurrentActor->unk155++;
                }
                break;
            case 5:
                if (gBehaviourWorkState->timer != 0) {
                    gBehaviourWorkState->timer--;
                } else if (gCurrentActor->unk154 == 0x2A) {
                    gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
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
        if (gPrimaryPlayerActor->unk154 == 0x42 && gCurrentActor->unk155 > 0) {
            actorScriptStart(gCurrentActor, 0);
            gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
            gCurrentActor->unk155 = 0;
        } else {
            switch (gCurrentActor->unk155) {
            case 0:
                scriptState->unk18 = scriptOpcodes[scriptState->unk15++];
                gCurrentActor->unk155++;
                /* fallthrough */
            case 1:
                if (camIsCutsceneActive() == 0) {
                    gBehaviourWorkState->timer = scriptState->unk18;
                    gBehaviourWorkState->unk2E = 9;
                    actorScriptStart(gCurrentActor, 0x3E7);
                    gCurrentActor->unk155++;
                }
                break;
            case 3:
                if (gCurrentActor->unk154 == 0x28 || (gCurrentActor->unk154 == 0x2C && (gBehaviourWorkState->unk2E % 3) == 0)) {
                    projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 0x96, 3, (f32)(((f64)scriptState->unk14 * 0.01) + 1.04), 0.0f, 0.0f, 0.0f);
                    sfxPlayAtPositionPooled(gCurrentActor->unk7C, gCurrentActor->unk80, gCurrentActor->unk84, 0x25A, 0xFF, 0x7F, 1, 0, 0.3f, 0);
                    controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0.0f, 0.0f);
                    scriptSetActorRampTarget(gSpawnedActor, 0.5f, 0.0f);
                }
                if (gCurrentActor->unk154 == 0x28 || (gCurrentActor->unk154 == 0x2C && gBehaviourWorkState->unk2E == 0)) {
                    gCurrentActor->unk155++;
                } else {
                    gBehaviourWorkState->unk2E--;
                    break;
                }
                /* fallthrough */
            case 4:
                if (gBehaviourWorkState->timer != 0) {
                    gBehaviourWorkState->timer--;
                } else if (scriptState->unk16 != 0) {
                    gCurrentActor->unk155 = 1;
                } else {
                    gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
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
            gCurrentActor->unkB8 = -40.0f;
            gCurrentActor->unk155++;
            /* fallthrough */
        case 2:
            actorMoveWithinZone(0, 0.0f, 0.0f, 0x4310, 0.0f);
            break;
        case 3:
            actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
            scriptState->unk15 = 0;
            scriptState->unk16 = 0;
            scriptState->unk14++;
            scriptOpcodes = D_80035A50[scriptState->unk14];
            actorScriptStart(gCurrentActor, 0x3E3);
            gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
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
