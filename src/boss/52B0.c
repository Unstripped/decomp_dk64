#include "common.h"
#include "actor.h"
#include "boss.h"
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

extern const u8 D_80036160[9];
extern const u8 D_8003616C[12];
extern const u8 D_80036178[15];
extern const u8 D_80036188[17];
extern const u8 D_8003619C[20];

const u8 *gMadJackPhaseScripts[5] = { D_80036160, D_8003616C, D_80036178, D_80036188, D_8003619C };

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
    effectSetFrameDelay(3);
    effectSetColor(0x78, 0x78, 0x78, 0xC8);
    effectSpawnBoneDefault(gCurrentActor, (((randomNonNegative() >> 15) % 0x7FFF) % 16) + 3, 2.0f, 0.0f, 0.0f, 0.0f, -0x96);
}

// Mad Jack boss actor: Actor plus its script component (0x178).
typedef struct BossMadJackActor {
    Actor base;
    BossScriptState *scriptState;
} BossMadJackActor;

extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;

void bossMadJackStep(void) {
    BossScriptState *scriptState;
    s32 turnSpeed;
    const u8 *scriptOpcodes;
    s16 targetAngle;
    s16 angleOffset;
    f32 targetX;
    f32 targetZ;

    scriptState = ((BossMadJackActor *) gCurrentActor)->scriptState;
    scriptOpcodes = gMadJackPhaseScripts[scriptState->phase];
    targetAngle = mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z);
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->boundingRadius = 0x64;
        gCurrentActor->unk15F = 0;
        gBehaviourAnimState->flags |= 0x20;
        gCurrentActor->renderFlags |= 4;
        gCurrentActor->collisionMode = 0x24;
        lightSetColor(0.0f, 0.0f, 0.0f, -1);
        scriptState->phase = 0;
        scriptState->scriptPos = 0;
        gCurrentActor->state = 0x1E;
        gCurrentActor->subState = 0;
    }
    volumeTriggerApplyActorState();
    switch (gCurrentActor->state) {
    case 0x2D:
        switch (gCurrentActor->subState) {
        case 0:
            actorScriptStart(gCurrentActor, 0x219);
            gCurrentActor->subState++;
            break;
        case 2:
            bossMadJackSpawnShockwave(1.8f);
            gBehaviourWorkState->timer = 0x14;
            gCurrentActor->subState++;
            break;
        case 3:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                bossMadJackSpawnShockwave(1.0f);
                gCurrentActor->subState++;
            }
            break;
        case 5:
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->subState = 0;
            break;
        }
        break;
    case 0x1E:
        switch (gCurrentActor->subState) {
        case 0:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B1);
                actorScriptStart(gActivePlayerState->actor, 0x3B7);
                gCurrentActor->subState++;
            }
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B2);
                actorScriptStart(gActivePlayerState->actor, 0x3B8);
                gCurrentActor->subState++;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B3);
                actorScriptStart(gActivePlayerState->actor, 0x3B9);
                gCurrentActor->subState++;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gCurrentActor, 0x217);
                gCurrentActor->subState++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gPrimaryPlayerActor, 0x3B4);
                actorScriptStart(gActivePlayerState->actor, 0x3BA);
                gCurrentActor->subState++;
            }
            break;
        case 5:
            if (currentActorTestClearFlag() != 0) {
                controllerAnimSetStateIfChanged(gPrimaryPlayerActor, 0x1C7, 0.0f, 0.0f);
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
            }
            break;
        }
        break;
    case 0x2C:
        csModelStateSetFirstByte(scriptOpcodes[scriptState->scriptPos++], 0xA);
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->subState = 0;
        break;
    case 0x2B:
        csModelStateSetFirstByte(scriptOpcodes[scriptState->scriptPos++], 0);
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->subState = 0;
        break;
    case 0x4D:
        if (scriptState->phase == 4) {
            gCurrentActor->state = 0x37;
            gCurrentActor->subState = 0;
            camStartPath(gCurrentActor, 4, 1);
            actorAppendActiveCallback8();
        } else {
            switch (gCurrentActor->subState) {
            case 0:
                gCurrentActor->yaw = 0;
                actorScriptStart(gCurrentActor, 0x213);
                camStartPath(gCurrentActor, 2, 1);
                actorAppendActiveCallback8();
                gCurrentActor->subState++;
                break;
            case 1:
                if (currentActorTestClearFlag() != 0) {
                    actorScriptStart(gCurrentActor, 0x21A);
                    gCurrentActor->subState++;
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
                scriptState->phase++;
                scriptOpcodes = gMadJackPhaseScripts[scriptState->phase];
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
                break;
            }
        }
        break;
    case 0x28:
    case 0x2A:
        actorTurnTowardActorYaw(0x14, gBehaviourTargetActor);
        goto attackSequence;
    case 0x46:
        gCurrentActor->yaw += gBehaviourWorkState->spinSpeed;
        if (mathAngleSignedDistance(gCurrentActor->yaw, targetAngle) > 0) {
            turnSpeed = gBehaviourWorkState->spinSpeed + 2;
            if (turnSpeed < 0x32) {
                gBehaviourWorkState->spinSpeed = turnSpeed;
            } else {
                gBehaviourWorkState->spinSpeed = 0x32;
            }
        } else {
            turnSpeed = gBehaviourWorkState->spinSpeed - 2;
            if (turnSpeed > -0x32) {
                gBehaviourWorkState->spinSpeed = turnSpeed;
            } else {
                gBehaviourWorkState->spinSpeed = -0x32;
            }
        }
attackSequence:
        switch (gCurrentActor->subState) {
        case 0:
            scriptState->byteVars[0] = scriptOpcodes[scriptState->scriptPos++];
            scriptState->byteVars[1] = scriptState->byteVars[0];
            scriptState->vars[0] = scriptOpcodes[scriptState->scriptPos++];
            if (gCurrentActor->state == 0x46) {
                gCurrentActor->subState = 2;
            } else {
                actorScriptStart(gCurrentActor, 0x214);
                gCurrentActor->subState++;
            }
            break;
        case 2:
            if (camIsCutsceneActive() == 0) {
                if (gCurrentActor->state == 0x46) {
                    if (mathAngleDistance(gCurrentActor->yaw, mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z)) < 0x320) {
                        actorScriptStart(gCurrentActor, 0x218);
                        gCurrentActor->subState++;
                    }
                } else {
                    actorScriptStart(gCurrentActor, 0x215);
                    gCurrentActor->subState++;
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
                gCurrentActor->subState = 0;
                break;
            case 0x46:
                projectileSpawnNodeEntry(0x1E, 0x63, 0.7f, gCurrentActor->yaw, 300.0f, 0.0f, gCurrentActor);
                gBehaviourWorkState->timer = scriptState->vars[0];
                gCurrentActor->subState = 8;
                break;
            default:
                projectileSpawnNodeEntry(0x1E, 5, 0.7f, gCurrentActor->yaw, 600.0f, 500.0f, gCurrentActor);
                gCurrentActor->subState++;
                break;
            }
            break;
        case 6:
            actorScriptStart(gCurrentActor, 0x213);
            gCurrentActor->subState++;
            scriptState->byteVars[0] = scriptState->byteVars[1];
            break;
        case 7:
            angleOffset = ((randomNonNegative() >> 15) % 1024) - 0x200;
            targetX = mathSinF(gBehaviourTargetActor->yaw + angleOffset) * (gBehaviourTargetActor->speedXZ * 1.2) + gBehaviourTargetActor->x;
            targetZ = mathCosF(gBehaviourTargetActor->yaw + angleOffset) * (gBehaviourTargetActor->speedXZ * 1.2) + gBehaviourTargetActor->z;
            projectileSetTargetCoords(targetX, gBehaviourTargetActor->y + 500.0f, targetZ);
            projectileAimAndSpawn(0x1E, 0x1E, 1.0f, targetX, gBehaviourTargetActor->y, targetZ, 600.0f, gCurrentActor);
            gBehaviourWorkState->timer = scriptState->vars[0];
            gCurrentActor->subState = 9;
            /* fallthrough */
        case 9:
        case 10:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                scriptState->byteVars[0]--;
                if (scriptState->byteVars[0] != 0) {
                    if (gCurrentActor->state == 0x46) {
                        gCurrentActor->subState = 2;
                    } else {
                        gCurrentActor->subState = 7;
                    }
                } else {
                    actorScriptStart(gCurrentActor, 0x213);
                    gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                    gCurrentActor->subState = 0;
                }
            }
            break;
        }
        break;
    case 0x37:
        if (currentActorTestClearFlag() != 0) {
            bossSpawnParticleRing(0xA8, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x5DC, 1);
            gCurrentActor->state = 0x40;
        }
        break;
    case 0:
        switch (gCurrentActor->subState) {
        case 0:
        case 1:
            actorScriptStart(gCurrentActor, 0x213);
            scriptState->vars[0] = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->subState = 2;
            break;
        default:
            if (scriptState->vars[0] != 0) {
                scriptState->vars[0]--;
            } else {
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
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

const u8 D_80036160[9] = { 0x2C, 0x01, 0x00, 0x3C, 0x4F, 0x46, 0x0A, 0x00, 0x50 };

const u8 D_8003616C[12] = { 0x2B, 0x01, 0x2C, 0x0C, 0x00, 0x1E, 0x4F, 0x46, 0x05, 0x00, 0x2D, 0x50 };

const u8 D_80036178[15] = { 0x2B, 0x0C, 0x2C, 0x11, 0x00, 0x1E, 0x4F, 0x46, 0x05, 0x00, 0x2D, 0x28, 0x14, 0x08, 0x50 };

const u8 D_80036188[17] = {
    0x2B, 0x11, 0x2C, 0x16, 0x00, 0x14, 0x4F, 0x46, 0x05, 0x00, 0x28, 0x14, 0x05, 0x2A, 0x00, 0x00,
    0x50,
};

const u8 D_8003619C[20] = {
    0x2B, 0x16, 0x2C, 0x1B, 0x00, 0x1E, 0x4F, 0x46, 0x05, 0x00, 0x2A, 0x00, 0x00, 0x46, 0x05, 0x00,
    0x28, 0x14, 0x05, 0x50,
};
