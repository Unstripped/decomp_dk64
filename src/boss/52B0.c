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

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;

void bossMadJackSpawnShockwave(f32 scale) {
    projectileSpawnWithShockwave(0x6A, 1.2f, 0, 0x96, 0xFF, 0xB, 1.015f, 0.0f, 0.0f, 0.0f);
    sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x221, 0x80, 0x7F, 1, 0, 0.3f, 0);
    gSpawnedActor->y = gCurrentActor->y;
    gSpawnedActor->sub4->scaleY *= scale;
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
    s16 delay;
    char padA[0xA];
    u8 scriptIndex;
    u8 scriptPos;
    char pad16[2];
    u8 shotsLeft;
    u8 shotCount;
} Boss3F_52B0_178;

typedef struct Boss3F_52B0_Actor {
    Actor base;
    Boss3F_52B0_178 *unk178;
} Boss3F_52B0_Actor;

extern u8 *D_80035A00[];
extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;

void bossMadJackStep(void) {
    Boss3F_52B0_178 *scriptState;
    s32 turnSpeed;
    u8 *scriptOpcodes;
    s16 targetAngle;
    s16 angleOffset;
    f32 targetX;
    f32 targetZ;

    scriptState = ((Boss3F_52B0_Actor *) gCurrentActor)->unk178;
    scriptOpcodes = D_80035A00[scriptState->scriptIndex];
    targetAngle = mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z);
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->boundingRadius = 0x64;
        gCurrentActor->unk15F = 0;
        gBehaviourAnimState->flags |= 0x20;
        gCurrentActor->renderFlags |= 4;
        gCurrentActor->unk144 = 0x24;
        lightSetColor(0.0f, 0.0f, 0.0f, -1);
        scriptState->scriptIndex = 0;
        scriptState->scriptPos = 0;
        gCurrentActor->state = 0x1E;
        gCurrentActor->unk155 = 0;
    }
    func_80724A20();
    switch (gCurrentActor->state) {
    case 0x2D:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x219);
            gCurrentActor->unk155++;
            break;
        case 2:
            bossMadJackSpawnShockwave(1.8f);
            gBehaviourWorkState->timer = 0x14;
            gCurrentActor->unk155++;
            break;
        case 3:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                bossMadJackSpawnShockwave(1.0f);
                gCurrentActor->unk155++;
            }
            break;
        case 5:
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x1E:
        switch (gCurrentActor->unk155) {
        case 0:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B1);
                actorScriptStart(gActivePlayerState->actor, 0x3B7);
                gCurrentActor->unk155++;
            }
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B2);
                actorScriptStart(gActivePlayerState->actor, 0x3B8);
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B3);
                actorScriptStart(gActivePlayerState->actor, 0x3B9);
                gCurrentActor->unk155++;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gCurrentActor, 0x217);
                gCurrentActor->unk155++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B4);
                actorScriptStart(gActivePlayerState->actor, 0x3BA);
                gCurrentActor->unk155++;
            }
            break;
        case 5:
            if (currentActorTestClearFlag() != 0) {
                controllerAnimSetStateIfChanged(gPrimaryPlayerActor, 0x1C7, 0.0f, 0.0f);
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x2C:
        csModelStateSetFirstByte(scriptOpcodes[scriptState->scriptPos++], 0xA);
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->unk155 = 0;
        break;
    case 0x2B:
        csModelStateSetFirstByte(scriptOpcodes[scriptState->scriptPos++], 0);
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->unk155 = 0;
        break;
    case 0x4D:
        if (scriptState->scriptIndex == 4) {
            gCurrentActor->state = 0x37;
            gCurrentActor->unk155 = 0;
            camStartPath(gCurrentActor, 4, 1);
            actorAppendActiveCallback8();
        } else {
            switch (gCurrentActor->unk155) {
            case 0:
                gCurrentActor->yaw = 0;
                actorScriptStart(gCurrentActor, 0x213);
                camStartPath(gCurrentActor, 2, 1);
                actorAppendActiveCallback8();
                gCurrentActor->unk155++;
                break;
            case 1:
                if (currentActorTestClearFlag() != 0) {
                    actorScriptStart(gCurrentActor, 0x21A);
                    gCurrentActor->unk155++;
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
                scriptState->scriptPos = 0;
                scriptState->scriptIndex++;
                scriptOpcodes = D_80035A00[scriptState->scriptIndex];
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
                break;
            }
        }
        break;
    case 0x28:
    case 0x2A:
        actorTurnTowardActorYaw(0x14, gBehaviourTargetActor);
        goto block_28;
    case 0x46:
        gCurrentActor->yaw += gBehaviourWorkState->unk2E;
        if (mathAngleSignedDistance(gCurrentActor->yaw, targetAngle) > 0) {
            turnSpeed = gBehaviourWorkState->unk2E + 2;
            if (turnSpeed < 0x32) {
                gBehaviourWorkState->unk2E = turnSpeed;
            } else {
                gBehaviourWorkState->unk2E = 0x32;
            }
        } else {
            turnSpeed = gBehaviourWorkState->unk2E - 2;
            if (turnSpeed >= -0x31) {
                gBehaviourWorkState->unk2E = turnSpeed;
            } else {
                gBehaviourWorkState->unk2E = -0x32;
            }
        }
block_28:
        switch (gCurrentActor->unk155) {
        case 0:
            scriptState->shotsLeft = scriptOpcodes[scriptState->scriptPos++];
            scriptState->shotCount = scriptState->shotsLeft;
            scriptState->delay = scriptOpcodes[scriptState->scriptPos++];
            if (gCurrentActor->state == 0x46) {
                gCurrentActor->unk155 = 2;
            } else {
                actorScriptStart(gCurrentActor, 0x214);
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            if (camIsCutsceneActive() == 0) {
                if (gCurrentActor->state == 0x46) {
                    if (mathAngleDistance(gCurrentActor->yaw, mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z)) < 0x320) {
                        actorScriptStart(gCurrentActor, 0x218);
                        gCurrentActor->unk155++;
                    }
                } else {
                    actorScriptStart(gCurrentActor, 0x215);
                    gCurrentActor->unk155++;
                }
            }
            break;
        case 4:
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xF6, 0x37, 0x7F, 1, 0x1E, 0.3f, 0);
            projectileGetTargetCoords(gCurrentActor, 2);
            switch (gCurrentActor->state) {
            case 0x2A:
                projectileAimAndSpawn(0xA9, 1, 1.0f, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y + 2.0f, gPrimaryPlayerActor->z, 450.0f, gCurrentActor);
                actorScriptStart(gCurrentActor, 0x213);
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
                break;
            case 0x46:
                projectileSpawnNodeEntry(0x1E, 0x63, 0.7f, gCurrentActor->yaw, 300.0f, 0.0f, gCurrentActor);
                gBehaviourWorkState->timer = scriptState->delay;
                gCurrentActor->unk155 = 8;
                break;
            default:
                projectileSpawnNodeEntry(0x1E, 5, 0.7f, gCurrentActor->yaw, 600.0f, 500.0f, gCurrentActor);
                gCurrentActor->unk155++;
                break;
            }
            break;
        case 6:
            actorScriptStart(gCurrentActor, 0x213);
            gCurrentActor->unk155++;
            scriptState->shotsLeft = scriptState->shotCount;
            break;
        case 7:
            angleOffset = ((randomNonNegative() >> 15) % 1024) - 0x200;
            targetX = ((f64)mathSinF(gBehaviourTargetActor->yaw + angleOffset) * ((f64)gBehaviourTargetActor->speedXZ * 1.2)) + (f64)gBehaviourTargetActor->x;
            targetZ = ((f64)mathCosF(gBehaviourTargetActor->yaw + angleOffset) * ((f64)gBehaviourTargetActor->speedXZ * 1.2)) + (f64)gBehaviourTargetActor->z;
            projectileSetTargetCoords(targetX, gBehaviourTargetActor->y + 500.0f, targetZ);
            projectileAimAndSpawn(0x1E, 0x1E, 1.0f, targetX, gBehaviourTargetActor->y, targetZ, 600.0f, gCurrentActor);
            gBehaviourWorkState->timer = scriptState->delay;
            gCurrentActor->unk155 = 9;
            /* fallthrough */
        case 9:
        case 10:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                scriptState->shotsLeft--;
                if (scriptState->shotsLeft != 0) {
                    if (gCurrentActor->state == 0x46) {
                        gCurrentActor->unk155 = 2;
                    } else {
                        gCurrentActor->unk155 = 7;
                    }
                } else {
                    actorScriptStart(gCurrentActor, 0x213);
                    gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                    gCurrentActor->unk155 = 0;
                }
            }
            break;
        }
        break;
    case 0x37:
        if (currentActorTestClearFlag() != 0) {
            bossSpawnParticleRing(0xA8, (s16)gCurrentActor->x, (s16)gCurrentActor->y, (s16)gCurrentActor->z, 0x5DC, 1);
            gCurrentActor->state = 0x40;
        }
        break;
    case 0:
        switch (gCurrentActor->unk155) {
        case 0:
        case 1:
            actorScriptStart(gCurrentActor, 0x213);
            scriptState->delay = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155 = 2;
            break;
        default:
            if (scriptState->delay != 0) {
                scriptState->delay--;
            } else {
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        actorMoveWithinZone(0x23, 0.0f, 0.0f, 0x202, 0.0f);
        break;
    default:
        bossScriptStep(scriptOpcodes, 0, 0.0f);
        break;
    }
    if (gCurrentActor->y < gCurrentActor->waterY) {
        gCurrentActor->y = gCurrentActor->waterY;
        gCurrentActor->speedY = gCurrentActor->accelY;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036160.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_8003616C.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036178.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_80036188.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/52B0/D_8003619C.s")
