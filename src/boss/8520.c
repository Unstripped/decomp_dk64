#include "common.h"
#include "actor.h"
#include "proto/boss/8520.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/35000.h"
#include "proto/global/8CA50.h"
#include "proto/global/B1F60.h"
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

typedef struct BossA_Struct_807FBB44 {
    u8 pad0[0xC8];
    f32 unkC8;
    u8 padCC[0x12A - 0xCC];
    s16 unk12A;
} BossA_Struct_807FBB44;

extern Actor *gCurrentActor;
extern BossA_Struct_807FBB44 *gSpawnedActor;

f32 mathCosF(s16);
f32 mathSinF(s16);
Actor *spawnNodeSpawnById(s16, s16, s16, s16, s16, s16, s16);

void bossKutOutSpawnGhost(s16 actorType, s16 distance, s16 angle) {
    f32 pad;
    f32 sinVal;
    f32 fArg1;

    sinVal = mathSinF(angle);
    fArg1 = distance;
    spawnNodeSpawnById(
        actorType,
        sinVal * fArg1 + gCurrentActor->x,
        gBehaviourExtraState->y,
        mathCosF(angle) * fArg1 + gCurrentActor->z,
        0, 0, 0
    );
    gSpawnedActor->unkC8 *= 2;
    gSpawnedActor->unk12A = 0x7D0;
}



u16 camStartPath(void *, s16, u8);

void bossKutOutSpawnGhosts(void) {
    bossKutOutSpawnGhost(2, ((randomNonNegative() >> 15) % 100) + 300, (randomNonNegative() >> 15) % 4096);
    bossKutOutSpawnGhost(3, ((randomNonNegative() >> 15) % 100) + 300, (randomNonNegative() >> 15) % 4096);
    bossKutOutSpawnGhost(4, ((randomNonNegative() >> 15) % 100) + 300, (randomNonNegative() >> 15) % 4096);

    if (!(gBehaviourWorkState->flags & 0x8000)) {
        gBehaviourWorkState->flags |= 0x8000;
        camStartPath(gSpawnedActor, 2, 1);
    }
}

// polymorphic: behaviour work word at 0x28 read as s32
typedef struct BossWorkState {
    char pad0[0x28];
    s32 unk28;
} BossWorkState;
#define DC90 ((BossWorkState *)gBehaviourWorkState)


void func_8002C748(animSlot)
u8 animSlot;
{
    DC90->unk28 = 2;
    animSetLoopLimit(gCurrentActor, animSlot, 1);
    animSetFinished(gCurrentActor, animSlot, 1);
    animSetFrameAndSubframe(gCurrentActor, animSlot, DC90->unk28 & 0xF, 0.0f);
}

void bossAnimFrameBounceStep(void) {
    u16 directionBit = 0;
    u8 directionFlag;
    u8 val;
    directionFlag = DC90->unk28 & 0x80;
    val = DC90->unk28 & 0xF;
    if (directionFlag) {
        val += 1;
        if (val >= 2) {
            directionFlag = 0;
        } else {
            directionBit = 0x8000;
        }
    } else {
        val -= 1;
        if (val <= 0) {
            directionFlag = 0x80;
        } else {
            directionBit = 0x8000;
        }
    }
    animSetFrameAndSubframe(gCurrentActor, 0, (s16)val, 0.0f);
    animSetFrameAndSubframe(gCurrentActor, 1, (s16)val, 0.0f);
    DC90->unk28 = directionBit | val | directionFlag;
}



void projectileGetTargetCoords(void *, s32);
void projectileAimAndSpawn(s16, s16, f32, f32, f32, f32, f32, Actor *);

void bossKutOutFireLaser(void) {
    projectileGetTargetCoords(gCurrentActor, 1);
    projectileAimAndSpawn(
        0x116,
        ((randomNonNegative() >> 15) % 3) + 1,
        1.0f,
        gBehaviourTargetActor->x,
        gBehaviourTargetActor->y + (f32)gBehaviourTargetActor->eyeHeight,
        gBehaviourTargetActor->z,
        300.0f,
        gCurrentActor
    );
}

typedef struct BossSwayState {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} BossSwayState;

// Boss actor with its sway-state component (the first pointer after Actor, 0x178).
typedef struct BossActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossSwayState *unk178;
} BossActor;





extern u8 gBossFightPhase;
extern s32 D_807FBD6C;
extern void *gCamActor;

void behaviourFrameBegin(void);
void tagBarrelSpawnActorSmokePuffs(u8, u8);
void behaviourCalculateDamageForce(s32, s32);
void actorSetUniformScale(void *, f32);
void actorScriptStart(void *, s32);
s16 sfxPlayAtPositionPooled(f32, f32, f32, s16, u8, s16, u8, u8, f32, u8);
s32 currentActorTestClearFlag(void);
void actorSetTargetSpeed(void *, s32);
void camSetSecondTarget(struct CamActor *, s16, s16);
s16 mathAngleEaseToward(s16, s16, f32);
u8 spawnNodeHasActor(u8);
u8 camIsCutsceneActive(void);
void behaviourSpawnPuffParticle(void);
u32 actorMoveWithinZone(u8, f32, f32, u16, f32);


void bossKutOutStep(void) {
    BossSwayState *swayState;

    swayState = ((BossActor *)gCurrentActor)->unk178;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        func_8002C748(0);
        func_8002C748(1);
        gBehaviourAnimState->unk30 = 2.5f;
        gBehaviourAnimState->flags &= 0xFFF7;
        gBehaviourAnimState->flags |= 0x200;
        gCurrentActor->flags |= 0x400;
        gCurrentActor->interactionType = 4;
        gCurrentActor->state = 0x1E;
        actorSetUniformScale(gCurrentActor, 2.0 * gCurrentActor->sub4->scaleX);
        actorSpawnLinkedFollower();
    }
    if (((gBossFightPhase == 9) || (gActorGlobalState.unk15 != 0)) && (gCurrentActor->state != 0x37)) {
        if (flagGet(0xF7, 0) != 0) {
            tagBarrelSpawnActorSmokePuffs(0, 1);
            gCurrentActor->state = 0x40;
        } else {
            camStartPath(gCurrentActor, 6, 1);
            gCurrentActor->speedY = 200.0f;
            behaviourCalculateDamageForce(D_807FBD6C, 0x2F7);
        }
    }
    switch (gCurrentActor->state) {
    case 0x28:
        switch (gCurrentActor->unk155) {
        case 0:
            camStartPath(gCurrentActor, 8, 1);
            actorScriptStart(gCurrentActor, 0);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x589, 0.0f, 0.0f);
            gBehaviourWorkState->timer = 0;
            gCurrentActor->unk155 = 1;
            gCurrentActor->unk144 = 1;
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x2FC, 0xFF, 0x7F, 0, 0, 0.0f, 0);
        case 1:
            gBehaviourWorkState->timer += 8;
            if (gBehaviourWorkState->timer >= 0x259) {
                gCurrentActor->unk155 = 2;
            }
            gCurrentActor->y += 2.0f;
            gCurrentActor->yaw += gBehaviourWorkState->timer;
            actorSetUniformScale(gCurrentActor, ((0.3 - gCurrentActor->sub4->scaleY) * 0.05) + gCurrentActor->sub4->scaleY);
            break;
        case 2: {
            s16 v;
            gBehaviourWorkState->timer -= 0x14;
            v = gBehaviourWorkState->timer;
            if (v < 0) {
                gBehaviourWorkState->timer = 0;
                v = gBehaviourWorkState->timer;
            }
            gCurrentActor->yaw += v;
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->unk155 = 3;
                gCurrentActor->flags &= ~4;
            }
            break;
        }
        case 3:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->eyeHeight = 0xA;
                DC90->unk28 |= 0x8000;
                gCurrentActor->interactionType = 1;
                gCurrentActor->state = 0x23;
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkD);
                gCurrentActor->unk144 = 0x24;
                actorScriptStart(gCurrentActor, 0x2F4);
            }
            break;
        }
        break;
    case 0x1E:
        switch (gCurrentActor->unk155) {
        case 0:
            if (currentActorTestClearFlag() != 0) {
                DC90->unk28 |= 0x8000;
                gCurrentActor->unk155 = 1;
            }
            break;
        case 2:
            if ((gCurrentActor->y - gCurrentActor->floorY) > 300.0f) {
                gCurrentActor->y -= 10.0f;
            } else {
                DC90->unk28 |= 0x8000;
                gCurrentActor->unk155 = 3;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155 = 0;
                camSetSecondTarget(gCamActor, 0, 0);
            }
            break;
        }
        break;
    case 0x27:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, gCurrentActor->x, gCurrentActor->z), 8.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            bossKutOutSpawnGhosts();
            gCurrentActor->unk155 = 1;
            break;
        case 1:
            if ((spawnNodeHasActor(2) == 0) && (spawnNodeHasActor(3) == 0) && (spawnNodeHasActor(4) == 0)) {
                gCurrentActor->unk155 = 2;
                gBehaviourWorkState->timer = 0x96;
                DC90->unk28 |= 0x8000;
                gCurrentActor->interactionType = 8;
                actorScriptStart(gCurrentActor, 0x2FA);
            }
            if ((camIsCutsceneActive() == 0) && ((randomNonNegative() >> 15) % 1000 >= 0x3E4)) {
                actorScriptStart(gCurrentActor, 0x2FD);
                gCurrentActor->unk155 = 3;
            }
            break;
        case 2:
            if ((gBehaviourWorkState->timer != 0) && (gBossFightPhase != 4)) {
                gBehaviourWorkState->timer -= 1;
            } else {
                if (gBossFightPhase == 4) {
                    actorScriptStart(gCurrentActor, 0x2FC);
                    behaviourSpawnPuffParticle();
                    swayState->unk2 = 0x96;
                    swayState->unk4 = 0x800;
                    gCurrentActor->moveYaw = gCurrentActor->yaw;
                    if (gCurrentActor->health == 1) {
                        gCurrentActor->state = 0x28;
                        gCurrentActor->unk155 = 0;
                    }
                }
                gCurrentActor->interactionType = 4;
                DC90->unk28 |= 0x8000;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 4:
            gCurrentActor->unk155 = 1;
            bossKutOutFireLaser();
            break;
        }
        break;
    case 0x23:
        actorMoveWithinZone(0x23, gBehaviourTargetActor->x, gBehaviourTargetActor->z, 0, 0.0f);
        break;
    case 0x37:
        actorPatrolFollowerUpdate(0x2F7, 1, 0);
        break;
    }
    if (swayState->unk2 > 0) {
        swayState->unk0 = mathSinF(swayState->unk4) * swayState->unk2;
        swayState->unk4 += 0x32;
        swayState->unk2 -= 1;
        gCurrentActor->roll = -swayState->unk0;
        gCurrentActor->x = mathSinF(gCurrentActor->moveYaw) * swayState->unk0 + gBehaviourExtraState->x;
        gCurrentActor->z = mathCosF(gCurrentActor->moveYaw) * swayState->unk0 + gBehaviourExtraState->z;
        gCurrentActor->y = gBehaviourExtraState->y - sqrtf(0x1C390 - swayState->unk0 * swayState->unk0);
    }
    if (DC90->unk28 & 0x8000) {
        bossAnimFrameBounceStep();
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

