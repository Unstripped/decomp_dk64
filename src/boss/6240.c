#include "common.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_effectSetColor // FAKE: callee prototype steer
#include "proto/boss/3840.h"
#include "proto/boss/6240.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/135D30.h"
#include "proto/global/13A7A0.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/35000.h"
#include "proto/global/63EC0.h"
#include "proto/global/FCCD0.h"
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

typedef struct BossC_6240_17C {
    char pad[4];
    u8 unk4;
    u8 pad5;
    s16 unk6;
    s16 unk8;
} BossC_6240_17C;

typedef struct BossC_6240_178 {
    char pad0[0x12];
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    char pad17[1];
    u8 unk18;
    char pad19[3];
    struct GfSndState *unk1C;
} BossC_6240_178;

typedef struct BossC_6240_Model_0 {
    char pad[4];
    f32 unk4;
} BossC_6240_Model_0;

typedef struct BossC_6240_Actor40 {
    Actor base;
    BossC_6240_178 *scriptState;
    BossC_6240_17C *unk17C;
} BossC_6240_Actor40;





typedef struct BossC_6240_Model {
    char pad[0x10];
    s16 unk10;
} BossC_6240_Model;


typedef struct BossC_6240_SubA0 {
    char pad[0xA0];
    s16 unkA0;
    s16 unkA2;
    s16 unkA4;
} BossC_6240_SubA0;

typedef struct BossC_6240_DCA0 {
    char pad0[0x14];
    BossC_6240_SubA0 *unk14;
    char pad18[0xC];
    u8 unk24[1];
} BossC_6240_DCA0;

extern BossC_6240_Actor40 *gCurrentActor;
extern u32 gFrameCounter;

f32 mathCosF(s16);
f32 mathSinF(s16);

void bossPufftossBobStep(void) {
    BossC_6240_17C *s0 = gCurrentActor->unk17C;
    f32 sinVal;
    if (s0->unk4 != 0) {
        s0->unk4--;
        sinVal = (f32)(mathSinF((s16)(((f64)s0->unk4 / 10.0) * (s0->unk8 - (s0->unk8 + 0x400)) + (s0->unk8 + 0x400))) * 20.0);
        gCurrentActor->base.x += sinVal * mathSinF(s0->unk6);
        gCurrentActor->base.z += sinVal * mathCosF(s0->unk6);
        if (s0->unk4 == 0) {
            s0->unk8 += 0x400;
        }
    } else if (((randomNonNegative() >> 15) % 1000) >= 941) {
        s0->unk4 = 10;
    }
    gCurrentActor->base.y += 8.0 * (f64)mathSinF((s16)((f64)gFrameCounter * 200.0));
}
void *actorFindByType(s32);
void actorAppendCallbackMemcpy8(void *, void *, s32, s32, void *, s32);

void bossPufftossNotifyLaser(u8 targetIndex) {
    void *target;
    f32 targetPos[2];

    switch (targetIndex) {
    case 0:
        target = actorFindByType(0x61);
        if (target != NULL) {
            actorAppendCallbackMemcpy8(gCurrentActor, target, 0x01000000, 1, targetPos, 0);
        }
        break;
    case 1:
        target = actorFindByType(0x60);
        if (target != NULL) {
            actorAppendCallbackMemcpy8(gCurrentActor, target, 0x01000000, 1, targetPos, 0);
        }
        target = actorFindByType(0x61);
        if (target != NULL) {
            actorAppendCallbackMemcpy8(gCurrentActor, target, 0x01000000, 3, targetPos, 0);
        }
        break;
    case 2:
        target = actorFindByType(0x60);
        if (target != NULL) {
            actorAppendCallbackMemcpy8(gCurrentActor, target, 0x01000000, 1, targetPos, 0);
        }
        target = actorFindByType(0x61);
        if (target != NULL) {
            actorAppendCallbackMemcpy8(gCurrentActor, target, 0x01000000, 2, targetPos, 0);
        }
        break;
    }
}

extern u8 D_80720120[];

void effectSetColor(s32, s32, s32, s32); // FAKE: callee prototype steer

void bossPufftossSpawnGlow(u8 sparkleInterval, f32 scale) {
    if (!(sparkleInterval & gFrameCounter)) {
        effectSetDepth(1);
        effectSetColor(0xFF, 0xD7, 0x58, 0xFF);
        effectCreateAtActorBone(D_80720120, scale, gCurrentActor, 1, 0);
    }
}

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
extern void *D_8074E880[];

void bossSpawnSparkles(void) {
    f32 sparkX;
    f32 sparkY;
    f32 sparkZ;
    s16 i;

    actorGetNodePos(gCurrentActor, 1, &sparkX, &sparkY, &sparkZ);
    sparkX += (f32)(((randomNonNegative() >> 15) % 80) - 40);
    sparkY += (f32)(((randomNonNegative() >> 15) % 100) + 50);
    sparkZ += (f32)(((randomNonNegative() >> 15) % 80) - 40);
    effectSetDepth(1);
    effectSetCallback(func_8071EDEC);
    effectSetSpeed(gCurrentActor);
    effectSetColor(0xFF, 0xD7, 0x58, 0xFF);
    effectCreateAtPosition(D_80720120, 1.5f, sparkX, sparkY, sparkZ);
    for (i = 0; i < 4; i++) {
        effectSetMode(2);
        effectSetCallback(effectPuffRiseUpdate);
        effectSetDepth(1);
        effectCreateAtActorBone(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3], 1.5f, gCurrentActor, ((randomNonNegative() >> 15) % 32767 % 22) + 2, 0);
    }
}

extern Actor *gPrimaryPlayerActor;
s32 polygonContainsPoint2D(s16, s16, s32);

void bossClampPosition(s32 radius) {
    if (!polygonContainsPoint2D((s32)gPrimaryPlayerActor->x, (s32)gPrimaryPlayerActor->z, radius)) {
        gPrimaryPlayerActor->x = gPrimaryPlayerActor->prevX;
        gPrimaryPlayerActor->z = gPrimaryPlayerActor->prevZ;
    }
}


extern u8 *D_80035A20[][5];
extern u8 *D_80035A34[];
extern u8 D_800362F0[];
extern u8 D_8071FB34[];
extern f32 D_807502E8;
extern f32 D_807502FC;
extern s32 gCurrentMap;
extern s32 D_8076D1F8;
extern s32 gCamActor;
extern void *gSpawnedActor;
extern ActorGlobalState gActorGlobalState;
extern PlayerStruct *gPlayerSlots;
extern PlayerState *gActivePlayerState;
extern BossC_6240_DCA0 *D_807FDCA0;

void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s16 sfxPlayOnFreeSlot(s16, s32, f32, f32, u8, u8);
void scriptSetActorRampTarget(void *, f32, f32);
void actorScriptStart(void *, s32);
void camSetTargetFocusActor(s32, void *);
void camSetTarget(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 camIsCutsceneActive(void);
void camStartPath(void *, s32, s32);
void camReturnToFollow(s32, void *);
void camSetFollowMode(s32);
void camSetSecondTarget(s32, s32, s32);
s32 currentActorTestClearFlag(void);
void currentActorClearFlag(void);
void csModelStateSetFirstByte(s16, s32);
void actorApplyVelocityCustom(void *, f32, f32);
void collisionCheckActorFloor(void *, f32, f32, f32, void *);
void actorGetOrSetNodeScale(void *, s32, f32);
s32 actorTableContains(void *);
void effectSpawnChildAtNode(s32, s16, s16);
void effectSpawnActorBoneEffects(s32);
void projectileGetTargetCoords(void *, s32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);
void projectileClampAngleAndSpawn(s16, s32, s32, s32, f32, f32, f32, f32, f32, void *);
void projectileSpawnWithShockwave(s32, f32, s32, s32, s32, s32, f32, f32, f32, f32);
void loadModelAssetTable(void);
void playerSetLargeModeScale(f32);
void playerSetSizeMode(void *, s32);
void func_8072881C(s32, void *);
void behaviourFrameBegin(void);
void actorApplyGravity(void);
void actorTurnTowardTarget(s32, f32, f32, s32);
void behaviourUpdateShadowAlpha(void);
s32 actorMoveWithinZone(s32, f32, f32, s32, f32);
void actorSetTargetSpeed(void *, u8);
s32 patrolPathStep(s32, s32);


void bossPufftossStep(void) {
    BossC_6240_178 *state;
    BossC_6240_17C *state17C;
    u8 *scriptData;
    f32 prevY;
    u8 checkFloor;
    u8 updateY;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    u16 roll;
    s16 sndId;
    f32 floorCheckX;
    f32 floorCheckY;
    f32 floorCheckZ;

    state = gCurrentActor->scriptState;
    state17C = gCurrentActor->unk17C;
    scriptData = D_80035A20[(gCurrentMap == 0xC5) ? 0 : 1][state->unk14];
    prevY = gCurrentActor->base.y;
    updateY = checkFloor = 1;
    behaviourFrameBegin();
    if (!(gCurrentActor->base.flags & 0x10)) {
        camSetSecondTarget(gCamActor, 0, 0);
        slotQueueSetDisplayMode(5, 0, 1);
        currentActorClearFlag();
        playerSetLargeModeScale(1.2f);
        loadModelAssetTable();
        gCurrentActor->base.floorNodeId = 2;
        bossInitScriptData(&D_800362F0);
        gBehaviourAnimState->unk30 = 3.0f;
        gCurrentActor->base.speedXZ = 0.0f;
        gCurrentActor->base.flags |= 0x800000;
        gBehaviourAnimState->stateFlags |= 0x20;
        state->unk1C = 0;
        gCurrentActor->base.state = scriptData[state->unk15++];
        gCurrentActor->base.unk155[0] = 0;
    }
    gActivePlayerState->surfaceTimer = (gActivePlayerState->surfaceTimer < 50) ? gActivePlayerState->surfaceTimer : 50;
    gCurrentActor->base.tintR = (u8) (((f64) mathSinF((s16) (gFrameCounter * 0x64)) * 50.0) + 200.0);
    gCurrentActor->base.tintG = gCurrentActor->base.tintR;
    gCurrentActor->base.tintB = gCurrentActor->base.tintR;
    if (gCurrentActor->base.state == 0x55) {
        gCurrentActor->base.interactionType = 2;
    } else {
        gCurrentActor->base.interactionType = 1;
    }
    gCurrentActor->base.unk144 = 0x24;
    if (gActorGlobalState.unk200 == 4) {
        if (state->unk14 == 3) {
            actorGetOrSetNodeScale(gCurrentActor, 1, 200.0f);
            bossPufftossNotifyLaser(0);
            gCurrentActor->base.state = 0x56;
            gCurrentActor->base.unk155[0] = 0;
            actorScriptStart(gCurrentActor, 0x2D1);
            gBehaviourWorkState->timer = 0x12C;
        } else {
            effectFreeAll();
            waterRippleStop();
            gCurrentActor->base.state = 0x4D;
            gCurrentActor->base.unk155[0] = 0;
            gCurrentActor->base.accelY = (f32) D_807502FC;
            actorScriptStart(gCurrentActor, 0x2CD);
            gBehaviourWorkState->targetY = -0x2BC;
            state->unk15 = 0;
            state->unk14++;
            scriptData = D_80035A34[state->unk14];
            if ((state->unk14 == 3) && (gCurrentMap == 0xC5)) {
                camStartPath(gCurrentActor, 8, 1);
            } else {
                camStartPath(gCurrentActor, 2, 1);
            }
        }
    } else if ((gActorGlobalState.unk200 == 5) && (gPlayerSlots->unk2C0 != 1)) {
        sndId = 0x14B;
        actorScriptStart(gCurrentActor, 0x2D2);
        actorGetNodePos(gCurrentActor, 2, &nodeX, &nodeY, &nodeZ);
        if (gCurrentActor->base.health == 1) {
            gBehaviourWorkState->flags |= 0x8000;
        }
        gBehaviourWorkState->unk16 = (s16) ((BossC_6240_Model *)gBehaviourTargetActor->sub4->model)->unk10;
        gCurrentActor->base.flags |= 0x20000000;
        effectCreateAtPosition(&D_8071FB34, 2.0f, ((randomNonNegative() >> 0xF) % 30 + nodeX) - 15.0f, ((randomNonNegative() >> 0xF) % 30 + nodeY) - 15.0f, ((randomNonNegative() >> 0xF) % 30 + nodeZ) - 15.0f);
        sfxPlayOnFreeSlot(0x1CA, 0x7FFF, 63.0f, 1.0f, 0, 0);
        roll = (randomNonNegative() >> 0xF) % 2048;
        if (roll < 0x2A8) {
            sndId = 0x14E;
        } else if (roll < 0x550) {
            sndId = 0x14D;
        }
        if (state->unk1C != 0) {
            n_alSndpStop(state->unk1C);
        }
        n_alSndpPlay(D_8076D1F8, sndId, 0x7FFF, 0x3F, 1.0f, 0, &state->unk1C);
    } else if (((gActorGlobalState.unk200 == 9) || (gActorGlobalState.unk15 != 0)) && (actorTableContains(gActorGlobalState.targetActor) != 0) && (gActorGlobalState.targetActor->collisionFlags == 1)) {
        playerSetSizeMode(gPrimaryPlayerActor, 2);
        bossPufftossNotifyLaser(1);
        csModelStateSetFirstByte(0, 0xA);
        camSetFollowMode(gCamActor);
        camStartPath(gCurrentActor, 8, 1);
        gCurrentActor->base.state = 0x37;
        gCurrentActor->base.unk155[0] = 0;
        gCurrentActor->base.flags &= ~4;
    }
    if (!(state->unk12 & 1) && (effectNodeGetValue(1) > 640.0f) && (gPrimaryPlayerActor->state != 0x42)) {
        if (gPlayerSlots->unk2C0 != 1) {
            playerSetSizeMode(gPrimaryPlayerActor, 1);
            gActivePlayerState->scaleChangeRate = 0.1f;
        }
        camStartPath(gCurrentActor, 0xA, 1);
        state->unk12 |= 1;
        state->unk14 = 4;
        state->unk15 = 0;
        scriptData = D_80035A20[(gCurrentMap == 0xC5) ? 0 : 1][state->unk14];
        gCurrentActor->base.state = scriptData[state->unk15];
        state->unk15 += 1;
        gCurrentActor->base.unk155[0] = 0;
    }
    switch (gCurrentActor->base.state) {
    case 0x6A:
        break;
    case 0x56:
        updateY = 0;
        gCurrentActor->base.interactionType = 4;
        actorMoveWithinZone(0x45, 606.0f, 566.0f, 0x292, 0.0f);
        if (gCurrentActor->base.unk155[0] == 1) {
            bossClampPosition((s32)D_807FDCA0->unk24);
        }
        if ((gCurrentActor->base.unk155[0] == 0) && (gPrimaryPlayerActor->state == 0x42)) {
            gCurrentActor->base.unk155[0] = 1;
            camSetTarget(gCamActor, gCurrentActor, 4, 0xD48, 0x320, 0, 0, 0xC8, 0x64, 0, 0.03f);
            camSetTargetFocusActor(gCamActor, gPrimaryPlayerActor);
        }
        if (!(gBehaviourWorkState->flags & 0x8000)) {
            if (gBehaviourWorkState->timer != 0) {
                if (gBehaviourWorkState->timer == 100) {
                    bossPufftossNotifyLaser(2);
                }
                if (gBehaviourWorkState->timer < 21) {
                    gCurrentActor->base.flags |= 0x20000000;
                }
                if (gBehaviourWorkState->timer == 20) {
                    if (gPlayerSlots->unk2C0 != 1) {
                        gActivePlayerState->surfaceTimer = 0x64;
                    }
                    camReturnToFollow(gCamActor, gPrimaryPlayerActor);
                    playerSetSizeMode(gPrimaryPlayerActor, 1);
                    gActivePlayerState->scaleChangeRate = 0.04f;
                }
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->base.flags &= 0xDFFFFFFF;
                actorGetOrSetNodeScale(gCurrentActor, 1, 64.0f);
                bossPufftossNotifyLaser(1);
                state->unk15 = state->unk16;
                gCurrentActor->base.state = scriptData[state->unk15++];
                gCurrentActor->base.unk155[0] = 0;
            }
        }
        break;
    case 0x37:
        checkFloor = 0;
        updateY = 0;
        gCurrentActor->base.interactionType = 4;
        bossClampPosition((s32)D_807FDCA0->unk24);
        if ((gCurrentActor->base.unk155[0] == 0) && (currentActorTestClearFlag() != 0)) {
            gCurrentActor->base.unk155[0] += 1;
            bossSpawnParticleRing(0xEC, D_807FDCA0->unk14->unkA0, (s16)(D_807FDCA0->unk14->unkA2 + 0x14), D_807FDCA0->unk14->unkA4, 0x5DC, 4);
        }
        break;
    case 0x27:
        updateY = 0;
        switch (gCurrentActor->base.unk155[0]) {
        case 0:
            if ((gCurrentMap == 0xC5) || (flagGet(0x69, 2) != 0)) {
                if (gCurrentMap == 0xC5) {
                    gCurrentActor->base.flags &= ~4;
                } else {
                    actorScriptStart(gCurrentActor, 0x2C6);
                }
                gCurrentActor->base.unk155[0] = 6;
            } else {
                controllerAnimSetStateIfChanged(gCurrentActor, 0x539, 0, 0);
                scriptSetActorRampTarget(gCurrentActor, 0, 0);
                gCurrentActor->base.unk155[0] = 1;
            }
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gCurrentActor, 0x2C4);
                scriptSetActorRampTarget(gCurrentActor, 0.5f, 0);
                gCurrentActor->base.unk155[0] = 2;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                gBehaviourWorkState->targetY = 0x1F4;
                actorScriptStart(gCurrentActor, 0x2C5);
                gCurrentActor->base.unk155[0] = 4;
            }
            break;
        case 5:
            if ((gCurrentActor->base.floorY + 180.0f) < gCurrentActor->base.y) {
                gCurrentActor->base.state = 0x11;
                gCurrentActor->base.unk155[0] = 0;
            }
            gCurrentActor->base.y += ((gCurrentActor->base.floorY + 200.0f) - gCurrentActor->base.y) * 0.12;
            break;
        case 6:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->base.state = scriptData[state->unk15++];
                gCurrentActor->base.unk155[0] = 0;
            }
            break;
        }
        break;
    case 0x2B:
        gCurrentActor->base.interactionType = 2;
        switch (gCurrentActor->base.unk155[0]) {
        case 0:
            actorScriptStart(gCurrentActor, 0x2CF);
            gCurrentActor->base.unk155[0] = 1;
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(0, 1);
                gCurrentActor->base.state = scriptData[state->unk15++];
                gCurrentActor->base.unk155[0] = 0;
            }
            break;
        }
        break;
    case 0x29:
        gCurrentActor->base.interactionType = 2;
        switch (gCurrentActor->base.unk155[0]) {
        case 0:
            actorScriptStart(gCurrentActor, 0x2CE);
            gCurrentActor->base.unk155[0] = 1;
            break;
        case 2:
            sfxPlayAtPositionPooled(gCurrentActor->base.x, gCurrentActor->base.y, gCurrentActor->base.z, 0x14A, 0xFF, 0x7F, 0, 0, 0, 0);
            sfxPlayAtPositionPooled(gCurrentActor->base.x, gCurrentActor->base.y, gCurrentActor->base.z, 0x221, 0xFF, 0x7F, 0, 0, 0, 0);
            projectileSpawnWithShockwave(0xBB, 0.14f, 0xFF, 0x96, 0x64, 6, 1.04f, 40.0f, 8.0f, 600.0f);
            controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0, 0);
            scriptSetActorRampTarget(gSpawnedActor, 0.5f, 0);
            gCurrentActor->base.state = scriptData[state->unk15++];
            gCurrentActor->base.unk155[0] = 0;
            break;
        }
        break;
    case 0x28:
        actorTurnTowardTarget(0x23, 606.0f, 566.0f, 0);
        switch (gCurrentActor->base.unk155[0]) {
        case 0:
            gBehaviourWorkState->unk25 += 4;
            patrolPathStep(0x42, 0);
            gBehaviourWorkState->unk25 -= 4;
            actorScriptStart(gCurrentActor, 0x2CB);
            gCurrentActor->base.unk155[0] = 1;
            gBehaviourWorkState->timer = 0;
            break;
        case 2:
            effectSpawnChildAtNode(2, (s16) ((((s32) (randomNonNegative() >> 0xF) % 2048) + gCurrentActor->base.yaw) - 0x400), (s16) ((s32) (randomNonNegative() >> 0xF) % 2048));
            /* fallthrough */
        case 3:
            bossSpawnSparkles();
            break;
        case 5:
            projectileGetTargetCoords(gCurrentActor, 1);
            if (gBehaviourWorkState->timer != 0) {
                projectileAimAndSpawn(0x51, 1, (f32) (((f64) ((s32) (randomNonNegative() >> 0xF) % 10) / 20.0) + 0.8), (f32) gBehaviourWorkState->targetX, (f32) gBehaviourWorkState->targetY, (f32) gBehaviourWorkState->targetZ, 500.0f, gCurrentActor);
            } else {
                projectileAimAndSpawn(0x1E, 0x14, 0.2f, (f32) gBehaviourWorkState->targetX, (f32) gBehaviourWorkState->targetY, (f32) gBehaviourWorkState->targetZ, 500.0f, gCurrentActor);
            }
            gBehaviourWorkState->timer = 1;
            break;
        case 7:
            gCurrentActor->base.state = scriptData[state->unk15++];
            gCurrentActor->base.unk155[0] = 0;
            break;
        }
        break;
    case 0x2A:
    case 0x2C:
        updateY = 0;
        gCurrentActor->base.interactionType = 2;
        switch (gCurrentActor->base.unk155[0]) {
        case 0:
            gBehaviourWorkState->unk25 += 4;
            gCurrentActor->base.unk155[0] = 1;
            /* fallthrough */
        case 1:
            actorMoveWithinZone(0x42, (f32) gBehaviourWorkState->targetX, (f32) gBehaviourWorkState->targetZ, 0x291, 0.0f);
            if (patrolPathStep(0x42, 0) != 0) {
                gCurrentActor->base.speedY = 100.0f;
                actorScriptStart(gCurrentActor, 0x2C8);
                gCurrentActor->base.unk155[0] = 2;
                gBehaviourWorkState->unk25 -= 4;
                if (gCurrentActor->base.state == 0x2C) {
                    camStartPath(gCurrentActor, 6, 1);
                }
            }
            break;
        case 2:
            actorMoveWithinZone(0x45, 606.0f, 566.0f, 0x292, 0.0f);
            break;
        case 3:
            gCurrentActor->base.state = scriptData[state->unk15++];
            gCurrentActor->base.unk155[0] = 0;
            break;
        }
        break;
    case 0x48:
        gCurrentActor->base.interactionType = 2;
        switch (gCurrentActor->base.unk155[0]) {
        case 0:
            actorScriptStart(gCurrentActor, 0x2C9);
            gBehaviourWorkState->timer = (s16) *(state->unk15 + scriptData);
            state->unk15 += 1;
            gCurrentActor->base.unk155[0] = 1;
            /* fallthrough */
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->base.state = scriptData[state->unk15++];
                gCurrentActor->base.unk155[0] = 0;
            }
            break;
        }
        break;
    case 0x43:
        gCurrentActor->base.interactionType = 2;
        switch (gCurrentActor->base.unk155[0]) {
        case 0:
            actorScriptStart(gCurrentActor, 0x2CA);
            gCurrentActor->base.unk155[0] = 1;
            break;
        case 2:
            if ((gCurrentActor->base.floorY + 180.0f) < gCurrentActor->base.y) {
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkC);
                gCurrentActor->base.state = scriptData[state->unk15++];
                gCurrentActor->base.unk155[0] = 0;
            }
            gCurrentActor->base.y += ((gCurrentActor->base.floorY + 200.0f) - gCurrentActor->base.y) * 0.12;
            updateY = 0;
            break;
        }
        break;
    case 0x11:
        actorMoveWithinZone(0x45, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x293, 0.0f);
        if (currentActorTestClearFlag() != 0) {
            gCurrentActor->base.state = scriptData[state->unk15++];
            gCurrentActor->base.unk155[0] = 0;
        }
        break;
    case 0x46:
        actorMoveWithinZone(0x45, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0x293, 0.0f);
        switch (gCurrentActor->base.unk155[0]) {
        case 0:
            state->unk18 = scriptData[state->unk15++];
            state17C->unk6 = (s16) (mathAngleBetweenPoints2D(606.0f, 566.0f, gCurrentActor->base.x, gCurrentActor->base.z) + 0x400);
            gCurrentActor->base.unk155[0] = 1;
            /* fallthrough */
        case 1:
            actorScriptStart(gCurrentActor, 0x2C7);
            gCurrentActor->base.unk155[0] = 2;
            break;
        case 2:
            bossPufftossSpawnGlow(0, (f32) (((f64) ((BossC_6240_Model_0 *)gCurrentActor->base.sub4->model)->unk4 * 0.06) + 2.0));
            break;
        case 3:
            projectileGetTargetCoords(gCurrentActor, 1);
            projectileClampAngleAndSpawn(gCurrentActor->base.yaw, 0x320, 0x1E, 0xB, 1.2f, gBehaviourTargetActor->x, gBehaviourTargetActor->y + 30.0f, gBehaviourTargetActor->z, (f32) ((state->unk14 * 0x50) + 0x2BC), gCurrentActor);
            gCurrentActor->base.unk155[0] = 4;
            break;
        case 5:
            if (state->unk18--) {
                gCurrentActor->base.unk155[0] = 1;
            } else {
                gCurrentActor->base.state = scriptData[state->unk15++];
                gCurrentActor->base.unk155[0] = 0;
            }
            break;
        }
        bossPufftossBobStep();
        break;
    case 0x4D:
        updateY = 0;
        switch (gCurrentActor->base.unk155[0]) {
        case 1:
            bossPufftossSpawnGlow(3, 3.0f);
            break;
        case 2:
            checkFloor = 0;
            actorApplyGravity();
            gCurrentActor->base.y = (f32) (gCurrentActor->base.y + gCurrentActor->base.speedY);
            if (gCurrentActor->base.y < (f32) gBehaviourWorkState->targetY) {
                gCurrentActor->base.unk155[0] = 3;
                sfxPlayAtPositionPooled(gCurrentActor->base.x, gCurrentActor->base.y, gCurrentActor->base.z, 0xC, 0xFF, 0x50, 0, 0, 0, 0);
            }
            if ((gCurrentMap == 0xC5) && (state->unk14 == 3) && (currentActorTestClearFlag() != 0)) {
                bossSpawnParticleRing(0x4A, D_807FDCA0->unk14->unkA0, (s16)(D_807FDCA0->unk14->unkA2 + 0x14), D_807FDCA0->unk14->unkA4, 0x5DC, 4);
            }
            break;
        case 3:
            checkFloor = 0;
            if (currentActorTestClearFlag() != 0) {
                if ((gCurrentMap == 0xC5) && (state->unk14 == 3)) {
                    gCurrentActor->base.state = 0x37;
                    gCurrentActor->base.unk155[0] = 1;
                } else {
                    gCurrentActor->base.accelY = (f32) D_807502E8;
                    actorScriptStart(gCurrentActor, 0x2CC);
                    gCurrentActor->base.unk155[0] = 4;
                    gBehaviourWorkState->targetY = 0xC8;
                }
            }
            break;
        case 4:
            effectSpawnActorBoneEffects(0);
            checkFloor = 0;
            gCurrentActor->base.y = ((gBehaviourWorkState->targetY + 5) - gCurrentActor->base.y) * 0.12 + gCurrentActor->base.y;
            actorTurnTowardTarget(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0);
            if ((gBehaviourWorkState->targetY - 300) < gCurrentActor->base.y) {
                if (gCurrentActor->base.soundSlots[0] == -1) {
                    sfxPlayActorSound(gCurrentActor, 0x10F, 0, 1, 0, 0xFF, 0.8f, 0);
                }
                controllerAnimSetStateIfChanged(gCurrentActor, 0x53D, 0, 24.0f);
            }
            if (gBehaviourWorkState->targetY < gCurrentActor->base.y) {
                actorScriptStart(gCurrentActor, 0x2D0);
                gCurrentActor->base.unk155[0] = 5;
            }
            break;
        case 5:
            effectSpawnActorBoneEffects(0);
            break;
        case 6:
            effectSpawnActorBoneEffects(1);
            break;
        case 7:
            actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkC);
            gCurrentActor->base.state = 0x11;
            gCurrentActor->base.unk155[0] = 0;
            break;
        }
        break;
    case 0x42:
        gCurrentActor->base.unk144 = 1;
        if (gCurrentActor->base.sub4->animId != 0x2C6) {
            actorScriptStart(gCurrentActor, 0x2C6);
        }
        /* fallthrough */
    default:
        bossScriptStep(scriptData, 0x291, 0);
        break;
    }
    if (updateY != 0) {
        if (gCurrentActor->base.y < gBehaviourWorkState->targetY) {
            gCurrentActor->base.y = (gBehaviourWorkState->targetY - prevY) * 0.03 + prevY;
            gCurrentActor->base.speedY = 0.0f;
        } else {
            actorApplyGravity();
            if ((f32) gBehaviourWorkState->targetY < gCurrentActor->base.y) {
                actorApplyVelocityCustom(gCurrentActor, 0, gCurrentActor->base.speedY);
            }
        }
    }
    func_8072881C(0, gBehaviourWorkState->unk28);
    if (checkFloor != 0) {
        actorGetNodePos(gCurrentActor, gCurrentActor->base.floorNodeId, &floorCheckX, &floorCheckY, &floorCheckZ);
        collisionCheckActorFloor(gCurrentActor, floorCheckX, floorCheckY, floorCheckZ, &gCurrentActor->base.floorY);
        behaviourUpdateShadowAlpha();
    }
    if (camIsCutsceneActive() != 0) {
        gCurrentActor->base.unk144 = 1;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_800362F0.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_800362FC.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036308.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_8003631C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036334.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036340.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036354.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_80036388.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/6240/D_8003639C.s")
