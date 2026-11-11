#include "common.h"
#include "actor.h"
#include "proto/boss/3840.h"
#include "proto/boss/52B0.h"
#include "proto/global/119370.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/42630.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/7130.h"
#include "proto/global/89250.h"
#include "proto/global/936B0.h"
#include "proto/global/CEAE0.h"

typedef struct {
    char pad0[0x38];
    f32 unk38;
} BossB_Sub44;

typedef struct {
    char pad0[4];
    BossB_Sub44 *unk4;
    char pad8[0x80 - 8];
    f32 unk80;
} BossB_ActorBB44;

// Actor plus its component pointers (0x174 on).
typedef struct BossB_ActorBB40 {
    /* 0x000 */ u8 pad0[0x174];
} BossB_ActorBB40;

extern Actor *gCurrentActor;
extern BossB_ActorBB44 *gSpawnedActor;


void bossMadJackSpawnShockwave(f32 scale) {
    projectileSpawnWithShockwave(0x6A, 1.2f, 0, 0x96, 0xFF, 0xB, 1.015f, 0.0f, 0.0f, 0.0f);
    sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x221, 0x80, 0x7F, 1, 0, 0.3f, 0);
    gSpawnedActor->unk80 = gCurrentActor->y;
    gSpawnedActor->unk4->unk38 *= scale;
    controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0.0f, 0.0f);
    scriptSetActorRampTarget(gSpawnedActor, 1.5f, 0.0f);
}



void bossMadJackSpawnSparkles(void) {
    randomNonNegative();
    effectSetDepth(1);
    effectSetMode(3);
    effectSetColor(0x78, 0x78, 0x78, 0xC8);
    effectSpawnBoneDefault(gCurrentActor, (((randomNonNegative() >> 15) % 0x7FFF) % 16) + 3, 2.0f, 0.0f, 0.0f, 0.0f, -0x96);
}

typedef struct Boss3F_52B0_178 {
    char pad0[8];
    s16 unk8;
    char padA[0xA];
    u8 unk14;
    u8 unk15;
    char pad16[2];
    u8 unk18;
    u8 unk19;
} Boss3F_52B0_178;

typedef struct Boss3F_52B0_Actor {
    char pad0[0x60];
    s32 unk60;
    s32 unk64;
    char pad68[0x14];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x24];
    f32 unkAC;
    char padB0[8];
    f32 unkB8;
    char padBC[4];
    f32 unkC0;
    f32 unkC4;
    char padC8[6];
    s16 unkCE;
    char padD0[0x16];
    s16 unkE6;
    char padE8[0x5C];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[9];
    u8 unk15F;
    char pad160[0x18];
    Boss3F_52B0_178 *unk178;
} Boss3F_52B0_Actor;

typedef struct Boss3F_52B0_BB4C {
    char pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} Boss3F_52B0_BB4C;

typedef struct Boss3F_52B0_D580 {
    char pad0[0x88];
    void *actor;
} Boss3F_52B0_D580;




extern u8 *D_80035A00[];
extern s32 gFrameCounter;
extern Boss3F_52B0_BB4C *gPrimaryPlayerActor;
extern Boss3F_52B0_D580 *gActivePlayerState;

#define ACTOR ((Boss3F_52B0_Actor *)gCurrentActor)

void bossMadJackStep(void) {

    Boss3F_52B0_178 *scriptState;
    s32 pad48;
    u8 *scriptOpcodes;
    s16 targetAngle;
    s16 angleOffset;
    f32 targetX;
    f32 targetZ;

    scriptState = ACTOR->unk178;
    scriptOpcodes = D_80035A00[scriptState->unk14];
    targetAngle = mathAngleBetweenPoints2D(gPrimaryPlayerActor->unk7C, gPrimaryPlayerActor->unk84, ACTOR->unk7C, ACTOR->unk84);
    behaviourFrameBegin();
    if (!(ACTOR->unk60 & 0x10)) {
        ACTOR->unkCE = 0x64;
        ACTOR->unk15F = 0;
        gBehaviourAnimState->flags |= 0x20;
        ACTOR->unk64 |= 4;
        ACTOR->unk144 = 0x24;
        lightSetColor(0.0f, 0.0f, 0.0f, -1);
        scriptState->unk14 = 0;
        scriptState->unk15 = 0;
        ACTOR->unk154 = 0x1E;
        ACTOR->unk155 = 0;
    }
    func_80724A20();
    switch (ACTOR->unk154) {
    case 0x2D:
        switch (ACTOR->unk155) {
        case 0:
            actorScriptStart(ACTOR, 0x219);
            ACTOR->unk155++;
            break;
        case 2:
            bossMadJackSpawnShockwave(1.8f);
            gBehaviourWorkState->timer = 0x14;
            ACTOR->unk155++;
            break;
        case 3:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                bossMadJackSpawnShockwave(1.0f);
                ACTOR->unk155++;
            }
            break;
        case 5:
            ACTOR->unk154 = scriptOpcodes[scriptState->unk15++];
            ACTOR->unk155 = 0;
            break;
        }
        break;
    case 0x1E:
        switch (ACTOR->unk155) {
        case 0:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B1);
                actorScriptStart(gActivePlayerState->actor, 0x3B7);
                ACTOR->unk155++;
            }
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B2);
                actorScriptStart(gActivePlayerState->actor, 0x3B8);
                ACTOR->unk155++;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B3);
                actorScriptStart(gActivePlayerState->actor, 0x3B9);
                ACTOR->unk155++;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(ACTOR, 0x217);
                ACTOR->unk155++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B4);
                actorScriptStart(gActivePlayerState->actor, 0x3BA);
                ACTOR->unk155++;
            }
            break;
        case 5:
            if (currentActorTestClearFlag() != 0) {
                controllerAnimSetStateIfChanged(gPrimaryPlayerActor, 0x1C7, 0.0f, 0.0f);
                ACTOR->unk154 = scriptOpcodes[scriptState->unk15++];
                ACTOR->unk155 = 0;
            }
            break;
        }
        break;
    case 0x2C:
        csModelStateSetFirstByte(scriptOpcodes[scriptState->unk15++], 0xA);
        ACTOR->unk154 = scriptOpcodes[scriptState->unk15++];
        ACTOR->unk155 = 0;
        break;
    case 0x2B:
        csModelStateSetFirstByte(scriptOpcodes[scriptState->unk15++], 0);
        ACTOR->unk154 = scriptOpcodes[scriptState->unk15++];
        ACTOR->unk155 = 0;
        break;
    case 0x4D:
        if (scriptState->unk14 == 4) {
            ACTOR->unk154 = 0x37;
            ACTOR->unk155 = 0;
            camStartPath(ACTOR, 4, 1);
            actorAppendActiveCallback8();
        } else {
            switch (ACTOR->unk155) {
            case 0:
                ACTOR->unkE6 = 0;
                actorScriptStart(ACTOR, 0x213);
                camStartPath(ACTOR, 2, 1);
                actorAppendActiveCallback8();
                ACTOR->unk155++;
                break;
            case 1:
                if (currentActorTestClearFlag() != 0) {
                    actorScriptStart(ACTOR, 0x21A);
                    ACTOR->unk155++;
                }
                break;
            case 2:
                effectSpawnJointBeam(3, 6, 7, 0xA);
                effectSpawnJointBeam(0xB, 0xE, 0xF, 0x12);
                break;
            case 3:
                if (!(gFrameCounter & 3)) {
                    bossMadJackSpawnSparkles();
                }
                break;
            case 4:
                csModelStateSetFirstByte(0, 0);
                csModelStateSetFirstByte(6, 0);
                csModelStateSetFirstByte(7, 0);
                csModelStateSetFirstByte(9, 0);
                csModelStateSetFirstByte(0xB, 0);
                scriptState->unk15 = 0;
                scriptState->unk14++;
                scriptOpcodes = D_80035A00[scriptState->unk14];
                ACTOR->unk154 = scriptOpcodes[scriptState->unk15++];
                ACTOR->unk155 = 0;
                break;
            }
        }
        break;
    case 0x28:
    case 0x2A:
        actorTurnTowardActorYaw(0x14, gBehaviourTargetActor);
        goto block_28;
    case 0x46:
        ACTOR->unkE6 += gBehaviourWorkState->unk2E;
        if (mathAngleSignedDistance(ACTOR->unkE6, targetAngle) > 0) {
            pad48 = gBehaviourWorkState->unk2E + 2;
            if (pad48 < 0x32) {
                gBehaviourWorkState->unk2E = pad48;
            } else {
                gBehaviourWorkState->unk2E = 0x32;
            }
        } else {
            pad48 = gBehaviourWorkState->unk2E - 2;
            if (pad48 >= -0x31) {
                gBehaviourWorkState->unk2E = pad48;
            } else {
                gBehaviourWorkState->unk2E = -0x32;
            }
        }
block_28:
        switch (ACTOR->unk155) {
        case 0:
            scriptState->unk18 = scriptOpcodes[scriptState->unk15++];
            scriptState->unk19 = scriptState->unk18;
            scriptState->unk8 = scriptOpcodes[scriptState->unk15++];
            if (ACTOR->unk154 == 0x46) {
                ACTOR->unk155 = 2;
            } else {
                actorScriptStart(ACTOR, 0x214);
                ACTOR->unk155++;
            }
            break;
        case 2:
            if (camIsCutsceneActive() == 0) {
                if (ACTOR->unk154 == 0x46) {
                    if (mathAngleDistance(ACTOR->unkE6, mathAngleBetweenPoints2D(gPrimaryPlayerActor->unk7C, gPrimaryPlayerActor->unk84, ACTOR->unk7C, ACTOR->unk84)) < 0x320) {
                        actorScriptStart(ACTOR, 0x218);
                        ACTOR->unk155++;
                    }
                } else {
                    actorScriptStart(ACTOR, 0x215);
                    ACTOR->unk155++;
                }
            }
            break;
        case 4:
            sfxPlayAtPositionPooled(ACTOR->unk7C, ACTOR->unk80, ACTOR->unk84, 0xF6, 0x37, 0x7F, 1, 0x1E, 0.3f, 0);
            projectileGetTargetCoords(ACTOR, 2);
            switch (ACTOR->unk154) {
            case 0x2A:
                projectileAimAndSpawn(0xA9, 1, 1.0f, gPrimaryPlayerActor->unk7C, gPrimaryPlayerActor->unk80 + 2.0f, gPrimaryPlayerActor->unk84, 450.0f, ACTOR);
                actorScriptStart(ACTOR, 0x213);
                ACTOR->unk154 = scriptOpcodes[scriptState->unk15++];
                ACTOR->unk155 = 0;
                break;
            case 0x46:
                projectileSpawnNodeEntry(0x1E, 0x63, 0.7f, ACTOR->unkE6, 300.0f, 0.0f, ACTOR);
                gBehaviourWorkState->timer = scriptState->unk8;
                ACTOR->unk155 = 8;
                break;
            default:
                projectileSpawnNodeEntry(0x1E, 5, 0.7f, ACTOR->unkE6, 600.0f, 500.0f, ACTOR);
                ACTOR->unk155++;
                break;
            }
            break;
        case 6:
            actorScriptStart(ACTOR, 0x213);
            ACTOR->unk155++;
            scriptState->unk18 = scriptState->unk19;
            break;
        case 7:
            angleOffset = ((randomNonNegative() >> 15) % 1024) - 0x200;
            targetX = ((f64)mathSinF(gBehaviourTargetActor->yaw + angleOffset) * ((f64)gBehaviourTargetActor->speedXZ * 1.2)) + (f64)gBehaviourTargetActor->x;
            targetZ = ((f64)mathCosF(gBehaviourTargetActor->yaw + angleOffset) * ((f64)gBehaviourTargetActor->speedXZ * 1.2)) + (f64)gBehaviourTargetActor->z;
            projectileSetTargetCoords(targetX, gBehaviourTargetActor->y + 500.0f, targetZ);
            projectileAimAndSpawn(0x1E, 0x1E, 1.0f, targetX, gBehaviourTargetActor->y, targetZ, 600.0f, ACTOR);
            gBehaviourWorkState->timer = scriptState->unk8;
            ACTOR->unk155 = 9;
            /* fallthrough */
        case 9:
        case 10:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                scriptState->unk18--;
                if (scriptState->unk18 != 0) {
                    if (ACTOR->unk154 == 0x46) {
                        ACTOR->unk155 = 2;
                    } else {
                        ACTOR->unk155 = 7;
                    }
                } else {
                    actorScriptStart(ACTOR, 0x213);
                    ACTOR->unk154 = scriptOpcodes[scriptState->unk15++];
                    ACTOR->unk155 = 0;
                }
            }
            break;
        }
        break;
    case 0x37:
        if (currentActorTestClearFlag() != 0) {
            bossSpawnParticleRing(0xA8, (s16)ACTOR->unk7C, (s16)ACTOR->unk80, (s16)ACTOR->unk84, 0x5DC, 1);
            ACTOR->unk154 = 0x40;
        }
        break;
    case 0:
        switch (ACTOR->unk155) {
        case 0:
        case 1:
            actorScriptStart(ACTOR, 0x213);
            scriptState->unk8 = scriptOpcodes[scriptState->unk15++];
            ACTOR->unk155 = 2;
            break;
        default:
            if (scriptState->unk8 != 0) {
                scriptState->unk8--;
            } else {
                ACTOR->unk154 = scriptOpcodes[scriptState->unk15++];
                ACTOR->unk155 = 0;
            }
            break;
        }
        actorMoveWithinZone(0x23, 0.0f, 0.0f, 0x202, 0.0f);
        break;
    default:
        bossScriptStep(scriptOpcodes, 0, 0.0f);
        break;
    }
    if (ACTOR->unk80 < ACTOR->unkAC) {
        ACTOR->unk80 = ACTOR->unkAC;
        ACTOR->unkC0 = ACTOR->unkC4;
    }
    actorUpdateModelMatrix(ACTOR, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036160.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_8003616C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036178.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036188.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_8003619C.s")
