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

typedef struct BossA_Struct_807FBB40 {
    u8 pad0[0x7C];
    f32 unk7C;
    u8 pad80[4];
    f32 unk84;
} BossA_Struct_807FBB40;


typedef struct BossA_Struct_807FBB44 {
    u8 pad0[0xC8];
    f32 unkC8;
    u8 padCC[0x12A - 0xCC];
    s16 unk12A;
} BossA_Struct_807FBB44;

extern BossA_Struct_807FBB40 *gCurrentActor;
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
        sinVal * fArg1 + gCurrentActor->unk7C,
        gBehaviourExtraState->y,
        mathCosF(angle) * fArg1 + gCurrentActor->unk84,
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
void projectileAimAndSpawn(s16, s16, f32, f32, f32, f32, f32, s32);

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

typedef struct BossModelInfo {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
} BossModelInfo;

typedef struct BossActor {
    char pad0[4];
    BossModelInfo *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x18];
    f32 unkA0;
    f32 unkA4;
    char padA8[0x18];
    f32 unkC0;
    char padC4[0x22];
    s16 unkE6;
    s16 unkE8;
    char padEA[4];
    s16 unkEE;
    char padF0[0x42];
    s16 unk132;
    s16 unk134;
    char pad136[0xE];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[8];
    u8 unk15E;
    char pad15F[0x19];
    BossSwayState *unk178;
} BossActor;





extern u8 gBossFightPhase;
extern u8 D_807FBB85;
extern s32 D_807FBD6C;
extern void *gCamActor;

void behaviourFrameBegin(void);
void tagBarrelSpawnActorSmokePuffs(s32, s32);
void behaviourCalculateDamageForce(s32, s32);
void actorSetUniformScale(void *, f32);
void actorScriptStart(void *, s32);
s16 sfxPlayAtPositionPooled(f32, f32, f32, s16, u8, s16, u8, u8, f32, u8);
s32 currentActorTestClearFlag(void);
void actorSetTargetSpeed(void *, s32);
void camSetSecondTarget(struct CamActor *, s16, s16);
s16 mathAngleEaseToward(s16, s16, s32);
u8 spawnNodeHasActor(u8);
u8 camIsCutsceneActive(void);
void behaviourSpawnPuffParticle(void);
u32 actorMoveWithinZone(u8, f32, f32, u16, f32);

#define A40 ((BossActor *)gCurrentActor)

void bossKutOutStep(void) {
    BossSwayState *swayState;

    swayState = A40->unk178;
    behaviourFrameBegin();
    if (!(A40->unk60 & 0x10)) {
        func_8002C748(0);
        func_8002C748(1);
        gBehaviourAnimState->unk30 = 2.5f;
        gBehaviourAnimState->flags &= 0xFFF7;
        gBehaviourAnimState->flags |= 0x200;
        A40->unk60 |= 0x400;
        A40->unk132 = 4;
        A40->unk154 = 0x1E;
        actorSetUniformScale(gCurrentActor, 2.0 * A40->unk4->unk34);
        actorSpawnLinkedFollower();
    }
    if (((gBossFightPhase == 9) || (D_807FBB85 != 0)) && (A40->unk154 != 0x37)) {
        if (flagGet(0xF7, 0) != 0) {
            tagBarrelSpawnActorSmokePuffs(0, 1);
            A40->unk154 = 0x40;
        } else {
            camStartPath(gCurrentActor, 6, 1);
            A40->unkC0 = 200.0f;
            behaviourCalculateDamageForce(D_807FBD6C, 0x2F7);
        }
    }
    switch (A40->unk154) {
    case 0x28:
        switch (A40->unk155) {
        case 0:
            camStartPath(gCurrentActor, 8, 1);
            actorScriptStart(gCurrentActor, 0);
            controllerAnimSetStateIfChanged(gCurrentActor, 0x589, 0.0f, 0.0f);
            gBehaviourWorkState->timer = 0;
            A40->unk155 = 1;
            A40->unk144 = 1;
            sfxPlayAtPositionPooled(A40->unk7C, A40->unk80, A40->unk84, 0x2FC, 0xFF, 0x7F, 0, 0, 0.0f, 0);
        case 1:
            gBehaviourWorkState->timer += 8;
            if (gBehaviourWorkState->timer >= 0x259) {
                A40->unk155 = 2;
            }
            A40->unk80 += 2.0f;
            A40->unkE6 += gBehaviourWorkState->timer;
            actorSetUniformScale(gCurrentActor, ((0.3 - A40->unk4->unk38) * 0.05) + A40->unk4->unk38);
            break;
        case 2: {
            s16 v;
            gBehaviourWorkState->timer -= 0x14;
            v = gBehaviourWorkState->timer;
            if (v < 0) {
                gBehaviourWorkState->timer = 0;
                v = gBehaviourWorkState->timer;
            }
            A40->unkE6 += v;
            if (currentActorTestClearFlag() != 0) {
                A40->unk155 = 3;
                A40->unk60 &= ~4;
            }
            break;
        }
        case 3:
            if (currentActorTestClearFlag() != 0) {
                A40->unk15E = 0xA;
                DC90->unk28 |= 0x8000;
                A40->unk132 = 1;
                A40->unk154 = 0x23;
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->unkD);
                A40->unk144 = 0x24;
                actorScriptStart(gCurrentActor, 0x2F4);
            }
            break;
        }
        break;
    case 0x1E:
        switch (A40->unk155) {
        case 0:
            if (currentActorTestClearFlag() != 0) {
                DC90->unk28 |= 0x8000;
                A40->unk155 = 1;
            }
            break;
        case 2:
            if ((A40->unk80 - A40->unkA4) > 300.0f) {
                A40->unk80 -= 10.0f;
            } else {
                DC90->unk28 |= 0x8000;
                A40->unk155 = 3;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                A40->unk154 = 0x27;
                A40->unk155 = 0;
                camSetSecondTarget(gCamActor, 0, 0);
            }
            break;
        }
        break;
    case 0x27:
        A40->unkE6 = mathAngleEaseToward(A40->unkE6, mathAngleBetweenPoints2D(gBehaviourTargetActor->x, gBehaviourTargetActor->z, A40->unk7C, A40->unk84), 0x41000000);
        switch (A40->unk155) {
        case 0:
            bossKutOutSpawnGhosts();
            A40->unk155 = 1;
            break;
        case 1:
            if ((spawnNodeHasActor(2) == 0) && (spawnNodeHasActor(3) == 0) && (spawnNodeHasActor(4) == 0)) {
                A40->unk155 = 2;
                gBehaviourWorkState->timer = 0x96;
                DC90->unk28 |= 0x8000;
                A40->unk132 = 8;
                actorScriptStart(gCurrentActor, 0x2FA);
            }
            if ((camIsCutsceneActive() == 0) && ((randomNonNegative() >> 15) % 1000 >= 0x3E4)) {
                actorScriptStart(gCurrentActor, 0x2FD);
                A40->unk155 = 3;
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
                    A40->unkEE = A40->unkE6;
                    if (A40->unk134 == 1) {
                        A40->unk154 = 0x28;
                        A40->unk155 = 0;
                    }
                }
                A40->unk132 = 4;
                DC90->unk28 |= 0x8000;
                A40->unk155 = 0;
            }
            break;
        case 4:
            A40->unk155 = 1;
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
        A40->unkE8 = -swayState->unk0;
        A40->unk7C = mathSinF(A40->unkEE) * swayState->unk0 + gBehaviourExtraState->x;
        A40->unk84 = mathCosF(A40->unkEE) * swayState->unk0 + gBehaviourExtraState->z;
        A40->unk80 = gBehaviourExtraState->y - sqrtf(0x1C390 - swayState->unk0 * swayState->unk0);
    }
    if (DC90->unk28 & 0x8000) {
        bossAnimFrameBounceStep();
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

