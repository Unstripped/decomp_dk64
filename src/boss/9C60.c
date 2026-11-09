#include "common.h"
#include "proto/boss/3840.h"
#include "proto/boss/9C60.h"
#include "proto/global/17B90.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

typedef struct BossC_9C60_Sub0 {
    char pad[0x10];
    s16 unk10;
    char pad12[0x12];
    f32 unk24;
} BossC_9C60_Sub0;

typedef struct BossC_9C60_Sub4 {
    BossC_9C60_Sub0 *unk0;
    char pad4[0x18];
    void *unk1C;
    char pad20[0x18];
    f32 unk38;
    char pad3C[0xC];
    f32 unk48;
} BossC_9C60_Sub4;

typedef struct BossC_9C60_Actor {
    char pad[4];
    BossC_9C60_Sub4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
    char pad88[0x30];
    f32 unkB8;
    char padBC[0x10];
    u8 unkCC;
    char padCD[0x19];
    s16 unkE6;
    char padE8[0x34];
    struct BossC_9C60_Actor *unk11C;
    char pad120[0x26];
    s16 unk146;
    char pad148[0xC];
    u8 unk154;
    u8 unk155;
    char pad156[0x22];
    void *unk178;
} BossC_9C60_Actor;

extern BossC_9C60_Actor *gCurrentActor;
extern BossC_9C60_Actor *gSpawnedActor;

void actorSpawn(s32, s32);
void actorCopyPoseAndScale(BossC_9C60_Actor *, BossC_9C60_Actor *, f32);
void actorDespawn(void *);
void bossAttachActor(void) {
    BossC_9C60_Actor **attachedActorSlot = gCurrentActor->unk178;

    actorSpawn(0xDD, 0xE3);
    gSpawnedActor->unk60 |= 0x400;
    gSpawnedActor->unk11C = gCurrentActor;
    *attachedActorSlot = gSpawnedActor;
    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->unk4->unk38);
}

void bossUpdateAttachment(void) {
    actorCopyPoseAndScale(gCurrentActor, gCurrentActor->unk11C, gCurrentActor->unk4->unk38);
    gCurrentActor->unk4->unk48 = gCurrentActor->unk11C->unk4->unk48;
    if (gCurrentActor->unk4->unk0->unk10 == 0x675 && gCurrentActor->unk4->unk0->unk24 == 0.0f) {
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

typedef struct Boss2F_9C60_DC90 {
    char pad[0x28];
    u8 unk28[4];
    s16 unk2C;
} Boss2F_9C60_DC90;

typedef struct Boss2F_9C60_DC9C {
    char pad[0xC];
    u8 unkC;
} Boss2F_9C60_DC9C;

typedef struct Boss2F_9C60_DCA0_Sub {
    char pad[0x28];
    s16 unk28;
    char pad2A[2];
    s16 unk2C;
} Boss2F_9C60_DCA0_Sub;
typedef struct Boss2F_9C60_DCA0 {
    char pad[0x14];
    Boss2F_9C60_DCA0_Sub *unk14;
} Boss2F_9C60_DCA0;

typedef struct Boss2F_9C60_Sub1C {
    char pad[2];
    u16 unk2;
} Boss2F_9C60_Sub1C;

extern u8 *D_80035A60[];
extern s32 gCamActor;
extern Boss2F_9C60_BB4C *gPrimaryPlayerActor;
extern Boss2F_9C60_DC90 *gBehaviourWorkState;
extern Boss2F_9C60_DC9C *gBehaviourExtraState;
extern Boss2F_9C60_DCA0 *D_807FDCA0;

void actorScriptExecute(BossC_9C60_Actor *);
void actorScriptStart(BossC_9C60_Actor *, s32);
s32 camIsCutsceneActive(void);
void camStartPath(BossC_9C60_Actor *, s32, s32);
void camStartShake(s32, s32, s32);
void camSetSecondTarget(s32, s32, s32);
s32 currentActorTestClearFlag(void);
void csModelStateSetFirstByte(s16, s32);
void projectileGetTargetCoords(BossC_9C60_Actor *, s32);
void projectileSpawnNodeEntry(s32, s32, f32, s32, f32, f32, BossC_9C60_Actor *);
void func_80724CA4(s32, s32);
void func_80724E48(s32);
s32 func_8072881C(s32, void *);
void behaviourFrameBegin(void);
void behaviourUpdateShadowAlpha(void);
void actorSetTargetSpeed(BossC_9C60_Actor *, s32);
void actorTurnTowardActorYaw(s32, void *);

void bossKRoolDiddyStep(void) {
    Boss2F_9C60_178 *scriptState;
    u8 *scriptOpcodes;
    s32 pad34;
    f32 projectileScale;
    u8 action;

    scriptState = gCurrentActor->unk178;
    scriptOpcodes = D_80035A60[scriptState->unk14];
    projectileScale = (gPrimaryPlayerActor->unk6A & 1) ? 0.7 : 1.0;
    behaviourFrameBegin();
    bossRoundFrame(scriptOpcodes);
    if (!(gCurrentActor->unk60 & 0x10)) {
        camSetSecondTarget(gCamActor, 0, 0);
        gCurrentActor->unk146 = 5;
        gCurrentActor->unk154 = 0x1E;
        gCurrentActor->unk155 = 0;
        gCurrentActor->unkCC = 1;
        actorScriptStart(gCurrentActor, 0x3E3);
        func_80724CA4(2, 1);
    }
    if (gCurrentActor->unk154 != 0x28) {
        func_80724E48(5);
    }
    switch (gCurrentActor->unk154) {
    case 0x1E:
        scriptState->unk14 = 0;
        scriptState->unk15 = 0;
        gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
        gCurrentActor->unk155 = 0;
        gCurrentActor->unkB8 = gBehaviourExtraState->unkC;
        break;
    case 0x27:
        actorScriptStart(gCurrentActor, 0x3E1);
        gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
        gCurrentActor->unk155 = 0;
        break;
    case 0x2C:
        switch (gCurrentActor->unk155) {
        case 0:
            gBehaviourWorkState->unk2C = 0x14;
            gCurrentActor->unk155++;
            break;
        case 1:
            actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
            if (gBehaviourWorkState->unk2C != 0) {
                gBehaviourWorkState->unk2C--;
            } else {
                csModelStateSetFirstByte((scriptState->unk14 * 2) + 8, 0xA);
                csModelStateSetFirstByte((scriptState->unk14 * 2) + 9, 0xA);
                gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
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
            gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
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
                gBehaviourWorkState->unk2C = scriptState->unk18;
                actorScriptStart(gCurrentActor, 0x3EF);
                gCurrentActor->unk155++;
            }
            break;
        case 3:
            gCurrentActor->unk146 = 6;
            projectileGetTargetCoords(gCurrentActor, 4);
            projectileSpawnNodeEntry(0xAA, 1, gCurrentActor->unk4->unk38, 0, (f32)scriptState->unk19 * projectileScale, 0.0f, gCurrentActor);
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
            if (((Boss2F_9C60_Sub1C *)gCurrentActor->unk4->unk1C)->unk2 < 0x7FFF) {
                ((Boss2F_9C60_Sub1C *)gCurrentActor->unk4->unk1C)->unk2 = 0xFFFF;
            }
            actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
            if (gBehaviourWorkState->unk2C != 0) {
                if ((gPrimaryPlayerActor->unk6A & 1) && (gBehaviourWorkState->unk2C >= 0xB)) {
                    gBehaviourWorkState->unk2C = 0xA;
                }
                gBehaviourWorkState->unk2C--;
            } else {
                gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
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
            gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
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
                    gCurrentActor->unk154 = 0x37;
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
            actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkC);
            scriptState->unk15 = 0;
            scriptState->unk14++;
            scriptOpcodes = D_80035A60[scriptState->unk14];
            actorScriptStart(gCurrentActor, 0x406);
            actorScriptExecute(gCurrentActor);
            controllerAnimSetStateIfChanged(scriptState->unk0, 0x674, 0.0f, 0.0f);
            gCurrentActor->unk154 = scriptOpcodes[scriptState->unk15++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->unkE6 = mathAngleBetweenPoints2D(D_807FDCA0->unk14->unk28, D_807FDCA0->unk14->unk2C, gCurrentActor->unk7C, gCurrentActor->unk84);
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
    if (func_8072881C(0, gBehaviourWorkState->unk28) != 0) {
        func_8072881C(0x81, gBehaviourWorkState->unk28);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036750.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036768.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036774.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/9C60/D_80036780.s")
