#include "common.h"
#include "actor.h"
#include "proto/boss/3840.h"
#include "proto/boss/9C60.h"
#include "proto/boss/A7A0.h"
#include "proto/global/17B90.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"

typedef struct BossC_A7A0_178 {
    s32 unk0;
    u8 pad4[0x10];
    u8 unk14;
} BossC_A7A0_178;

typedef struct BossC_A7A0_Actor {
    char pad[0x58];
    s32 unk58;
    s32 pad5C;
    s32 unk60;
    char pad64[0xB8];
    struct BossC_A7A0_Actor *unk11C;
    char pad120[8];
    s16 unk128;
    char pad12A[0x1A];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x12];
    s16 unk168;
    char pad16A[0xE];
    BossC_A7A0_178 *unk178;
} BossC_A7A0_Actor;

typedef struct BossC_A7A0_BB70 {
    char pad[0x15];
    u8 unk15;
    char pad16[0x1E6];
    BossC_A7A0_Actor *targetActor;
    u8 unk200;
} BossC_A7A0_BB70;

extern BossC_A7A0_BB70 gActorGlobalState;
extern BossC_A7A0_Actor *gCurrentActor;
extern BossC_A7A0_Actor *gPrimaryPlayerActor;
void actorDespawn(BossC_A7A0_Actor *);

typedef struct {
    BossC_A7A0_Actor *actor;
    s32 pad;
} BossC_A7A0_Entry;

extern BossC_A7A0_Entry gActiveActors[];
extern u16 gActiveActorCount;

void bossResetMinions(BossC_A7A0_Actor *excludeActor) {
    s16 i;
    BossC_A7A0_Actor *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if ((excludeActor == NULL || actor != excludeActor) && actor->unk58 == 0xDE) {
            actor->unk60 &= ~0x8000;
            actor->unk154 = 1;
            actor->unk155 = 0;
        }
    }
}

void bossPhaseTick(void) {
    BossC_A7A0_Actor *other;
    s16 timer;

    if (!(gCurrentActor->unk60 & 0x10)) {
        bossResetMinions(gCurrentActor);
        gCurrentActor->unk168 = 0x258;
        gCurrentActor->unk144 = 2;
    }
    if (gPrimaryPlayerActor->unk154 != 0x67) {
        timer = gCurrentActor->unk168;
        if (timer != 0) {
            gCurrentActor->unk168 = timer - 1;
        } else {
            gCurrentActor->unk60 &= ~0x8000;
            gCurrentActor->unk154 = 1;
            gCurrentActor->unk155 = 0;
        }
    }
    if (((gActorGlobalState.unk15 != 0) || (gActorGlobalState.unk200 == 9)) &&
        ((other = gActorGlobalState.targetActor)->unk154 == 0x2B) &&
        (other->unk155 == 3)) {
        gCurrentActor->unk154 = 1;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unk11C->unk154 = 0x64;
        gCurrentActor->unk11C->unk155 = 0;
        other->unk155 = 0;
        other->unk154 = 0x31;
    }
    if (gCurrentActor->unk154 == 1) {
        gCurrentActor->unk144 = 1;
        gCurrentActor->unk128 -= 10;
        if (gCurrentActor->unk128 < 0) {
            actorDespawn(gCurrentActor);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void actorScriptStart(BossC_A7A0_Actor *, s32);
void actorScriptExecute(BossC_A7A0_Actor *);

void bossKRoolLankySetAnim(s32 scriptId, s16 animId) {
    BossC_A7A0_178 *link = gCurrentActor->unk178;

    actorScriptStart(gCurrentActor, scriptId);
    actorScriptExecute(gCurrentActor);
    controllerAnimSetState(link->unk0, animId, 0.0f, 6.0f);
}


void actorSetTargetSpeed(BossC_A7A0_Actor *, s32);

void bossKRoolLankyRunTowardPlayer(void) {
    BossC_A7A0_178 *link = gCurrentActor->unk178;

    bossKRoolLankySetAnim(0x406, 0x674);
    actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkC + (link->unk14 * 10) + 15);
}

typedef struct BossScriptState {
    void *unk0;
    char pad4[0x10];
    u8 unk14;
    u8 unk15;
} BossScriptState;

typedef struct BossModelInfo {
    char pad0[0x64];
    u16 unk64;
} BossModelInfo;

typedef struct BossActorSub140 {
    char pad0[0xC];
    s32 unkC;
} BossActorSub140;

typedef struct BossActor {
    char pad0[4];
    BossModelInfo *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x60];
    f32 unkC4;
    char padC8[4];
    u8 unkCC;
    char padCD[0x73];
    BossActorSub140 *unk140;
    char pad144[2];
    s16 unk146;
    char pad148[0xC];
    u8 unk154;
    u8 unk155;
    char pad156[0x22];
    BossScriptState *unk178;
} BossActor;

typedef struct BossStageInfo {
    char pad[0x1B];
    u8 unk1B;
    char pad1C[0x200 - 0x1C];
    u8 unk200;
} BossStageInfo;




extern u8 *D_80035A80[];
void behaviourFrameBegin(void);
void func_80724CA4(s32, s32);
s32 camStartPath(void *, s32, s32);
s32 camIsPlayingPath(s32);
void actorMoveWithinZone(s32, f32, f32, s32, f32);
void playerStateQueueCallback(s32, void *, s32);
void actorSetCollisionRadius(void *, f32);
void actorOrNodeFlags(void *, s32, s32);
s32 currentActorTestClearFlag(void);
void scriptSetActorRampTarget(void *, f32, f32);
void behaviourUpdateShadowAlpha(void);
s32 func_8072881C(s32, void *);

#define ACTOR40 ((BossActor *)gCurrentActor)
#define ACTOR4C ((BossActor *)gPrimaryPlayerActor)
#define BB70 (*(BossStageInfo *)&gActorGlobalState)

void bossKRoolLankyStep(void) {
    BossScriptState *scriptState;
    u8 *scriptOpcodes;

    scriptState = (BossScriptState *)gCurrentActor->unk178;
    scriptOpcodes = D_80035A80[scriptState->unk14];
    behaviourFrameBegin();
    bossRoundFrame(scriptOpcodes);
    if (!(ACTOR40->unk60 & 0x10)) {
        ACTOR40->unk146 = 1;
        ACTOR40->unk154 = 0x1E;
        ACTOR40->unk155 = 0;
        ACTOR40->unkCC = 1;
        func_80724CA4(2, 1);
        bossAttachActor();
        ACTOR40->unkC4 = 0.0f;
    }
    if ((ACTOR4C->unk154 == 0x48) && !(gBehaviourWorkState->flags & 0x8000)) {
        camStartPath(ACTOR40, 0, 1);
        gBehaviourWorkState->flags |= 0x8000;
    }
    if ((camIsPlayingPath(0) == 0) && (camIsPlayingPath(1) == 0) && ((ACTOR4C->unk154 != 0x67) || (ACTOR40->unk154 != 0x42))) {
        switch (ACTOR40->unk154) {
        case 0x2B:
            switch (ACTOR40->unk155) {
            case 0:
                actorSetTargetSpeed(gCurrentActor, 0);
                camStartPath(ACTOR4C, 9, 1);
                bossKRoolLankySetAnim(0x3F5, 0x679);
                ACTOR40->unk155++;
                break;
            case 2:
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkD);
                bossKRoolLankySetAnim(0x3F4, 0x678);
                ACTOR40->unk155++;
                break;
            case 3:
                if (BB70.unk1B != 0) {
                    ACTOR40->unk154 = 0x31;
                    ACTOR40->unk155 = 0;
                } else if (BB70.unk200 == 2) {
                    bossResetMinions(NULL);
                    ACTOR40->unk154 = 0x2C;
                    ACTOR40->unk155 = 0;
                }
                actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
                break;
            }
            break;
        case 0x2C:
            if (ACTOR40->unk155 == 0) {
                playerStateQueueCallback(0x36, ACTOR40, 0);
                bossKRoolLankyRunTowardPlayer();
                ACTOR40->unk154 = 0x42;
                ACTOR40->unk155 = 0;
            }
            break;
        case 0x1E:
            scriptState->unk14 = 0;
            scriptState->unk15 = 0;
            ACTOR40->unk154 = scriptOpcodes[scriptState->unk15++];
            ACTOR40->unk155 = 0;
            break;
        case 0:
            switch (ACTOR40->unk155) {
            case 0:
                bossKRoolLankySetAnim(0x3F5, 0x679);
                ACTOR40->unk155++;
                break;
            case 2:
                bossKRoolLankyRunTowardPlayer();
                ACTOR40->unk154 = scriptOpcodes[scriptState->unk15++];
                ACTOR40->unk155 = 0;
                actorSetCollisionRadius(ACTOR4C, (f32)(ACTOR4C->unk140->unkC * 2));
                actorOrNodeFlags(ACTOR4C, 6, 1);
                actorOrNodeFlags(ACTOR4C, 7, 1);
                actorOrNodeFlags(ACTOR4C, 8, 1);
                actorOrNodeFlags(ACTOR4C, 9, 1);
                actorOrNodeFlags(ACTOR4C, 0xA, 1);
                actorOrNodeFlags(ACTOR4C, 0xB, 1);
                break;
            }
            break;
        case 0x31:
            switch (ACTOR40->unk155) {
            case 0:
                if (scriptState->unk14 == 3) {
                    ACTOR40->unk154 = 0x37;
                    ACTOR40->unk155 = 0;
                } else {
                    actorScriptStart(gCurrentActor, 0x3F2);
                    actorScriptStart(scriptState->unk0, 0x3F1);
                    actorSetTargetSpeed(gCurrentActor, 0);
                    ACTOR40->unk155++;
                }
                break;
            case 1:
                actorMoveWithinZone(0, 0.0f, 0.0f, 0x310, 0.0f);
                break;
            case 2:
                bossResetMinions(NULL);
                bossKRoolLankyRunTowardPlayer();
                scriptState->unk15 = 0;
                scriptState->unk14++;
                scriptOpcodes = D_80035A80[scriptState->unk14];
                ACTOR40->unk154 = scriptOpcodes[scriptState->unk15++];
                ACTOR40->unk155 = 0;
                break;
            }
            break;
        case 0x37:
            switch (ACTOR40->unk155) {
            case 0:
                actorDespawn(scriptState->unk0);
                actorScriptStart(gCurrentActor, 0);
                camStartPath(ACTOR40, 5, 1);
                ACTOR40->unk155++;
                break;
            case 1:
                if (currentActorTestClearFlag() != 0) {
                    screenSetTransitionFadeType(0);
                    mapRequestTransition(0xCE, 0);
                    ACTOR40->unk155++;
                }
                break;
            }
            break;
        default:
            bossScriptStep(scriptOpcodes, 0x10, 0.0f);
            break;
        }
    } else if (ACTOR40->unk4->unk64 == 0x406) {
        scriptSetActorRampTarget(ACTOR40, 0.0f, 0.0f);
    }
    behaviourUpdateShadowAlpha();
    if (func_8072881C(0, gBehaviourWorkState->unk28) != 0) {
        func_8072881C(0x81, gBehaviourWorkState->unk28);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


#pragma GLOBAL_ASM("asm/boss/nonmatchings/A7A0/D_80036840.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/A7A0/D_80036850.s")
