#include "common.h"
#include "actor.h"
#include "proto/global/103AB0.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/126260.h"
#include "proto/global/127B00.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/36880.h"
#include "proto/global/42630.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/8F4B0.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/A2F10.h"
#include "proto/global/C4620.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/F56F0.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

typedef struct ScriptedActorState {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 yawFrom;
    /* 0x04 */ s16 yawTo;
    /* 0x06 */ s16 pitchFrom;
    /* 0x08 */ s16 pitchTo;
    /* 0x0A */ s16 rollFrom;
    /* 0x0C */ s16 rollTo;
    /* 0x0E */ s16 zoneTo;
    /* 0x10 */ s16 zoneFrom;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ f32 scaleFrom;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u16 lerpSteps;
    /* 0x1E */ u16 lerpTimer;
    /* 0x20 */ u8 pad20[2];
    /* 0x22 */ u8 particleScalePct;
    /* 0x23 */ u8 yawSteps;
    /* 0x24 */ u8 yawTimer;
    /* 0x25 */ u8 pitchSteps;
    /* 0x26 */ u8 pitchTimer;
    /* 0x27 */ u8 rollSteps;
    /* 0x28 */ u8 rollTimer;
    /* 0x29 */ u8 scaleSteps;
    /* 0x2A */ u8 scaleTimer;
    /* 0x2B */ u8 pad2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 pathId;
    /* 0x2E */ u8 pathSpeed;
    /* 0x2F */ u8 pathPlayback;
    /* 0x30 */ u8 particlePath;
    /* 0x31 */ u8 particleCount;
    /* 0x32 */ u8 particleColor;
    /* 0x33 */ u8 particleSprite;
} ScriptedActorState;

typedef struct C4620Actor {
    /* 0x000 */ Actor base;
    /* 0x178 */ void *unk178;
    /* 0x17C */ ScriptedActorState *unk17C;
} C4620Actor;

#define C46V ((C4620Actor *)gCurrentActor)



void func_806BF920(void) {
    ScriptedActorState *state;
    s32 outCount;
    s32 bufferSize;

    state = C46V->unk17C;
    outCount = 0;
    if (!(gCurrentActor->flags & 0x10)) {
        bufferSize = 0;
        switch (state->unk0) {
            case 1:
            case 2:
            case 3:
                bufferSize = 3;
                break;
            case 9:
            case 10:
            case 11:
                bufferSize = 5;
                break;
            case 4:
            case 5:
                bufferSize = 2;
                break;
        }
        if (bufferSize != 0) {
            gCurrentActor->sub4->boneRotations = heapAlloc(0x100);
            func_806C8220(0, C46V->unk178, bufferSize);
        }
    }
    switch (state->unk0) {
        case 1:
        case 2:
        case 3:
            playerWeaponInitCrosshair(gCurrentActor, gCurrentActor->sub4->boneRotations, &outCount);
            break;
        case 9:
        case 10:
        case 11:
            playerWeaponSpawnProjectile(gCurrentActor, gCurrentActor->sub4->boneRotations, &outCount);
            break;
        case 4:
        case 5:
            playerWeaponAimTarget(gCurrentActor, gCurrentActor->sub4->boneRotations, &outCount);
            break;
    }
    if (outCount != 0) {
        gCurrentActor->sub4->boneRotations[outCount].weight = 0;
    }
}


void func_806BFA8C(u16 animId) {
    switch (animId) {
        case 0xEA:
        case 0x23E:
        case 0x23F:
        case 0x240:
        case 0x4C7:
            gCurrentActor->unk155 = 1;
            break;
        case 0x112:
            playerKongPlaySoundByState(gCurrentActor);
            /* fallthrough */
        case 0x113:
        case 0x128:
        case 0x129:
        case 0x12A:
        case 0x12B:
        case 0x12C:
        case 0x12D:
        case 0x12E:
        case 0x12F:
        case 0x130:
            playerMountBarrel(gCurrentActor, 0);
            break;
        case 0x114:
            playerKongStopSoundByState(gCurrentActor);
            playerKongSpawnTransformationSmoke(gCurrentActor);
            break;
        case 0x2CF:
            controllerAnimFreeStateAsset(gCurrentActor);
            controllerAnimSetState(gCurrentActor, 0x2CF, 0.0f, 0.0f);
            break;
    }
}


void func_806BFBB4(void) {
    controllerStepMotionWindows(gCurrentActor);
    actorUpdateModelMatrix(gCurrentActor, 0);
    actorCheckWorldBounds(gCurrentActor);
}



typedef struct ScriptCommand {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u16 opcode;
    /* 0x04 */ s16 param1;
    /* 0x06 */ s16 param2;
} ScriptCommand;


extern u8 gGameMode;
extern s32 gCurrentMap;
extern f32 D_807502E8;
extern u16 D_80747750[];
extern u16 D_80747904[];
extern u8 D_807478F4[];
extern u8 D_80747B00[];
extern void *sScriptEffectSprites[];


void actorScriptedCommandUpdate(void) {
    s16 j;
    s16 pad;
    s16 i;
    ScriptCommand *cmd;
    ScriptedActorState *state;
    f32 ratio;
    f32 ratio2;
    u8 *col;
    s32 node;
    f32 particleScale;
    f32 posX;
    f32 posY;
    f32 posZ;

    state = C46V->unk17C;
    if (!(gCurrentActor->flags & 0x10)) {
        state->unk1A = 0;
        state->unk18 = 0;
        state->particlePath = 0xFF;
        state->particleSprite = 0x12;
        state->particleScalePct = 0x64;
        playerKongStopAudioChannels(gCurrentActor, gCurrentActor->actorType);
        actorSetTargetSpeed(gCurrentActor, 0);
        gCurrentActor->flags &= 0xFFFDFFFF;
        if (gCurrentMap == 0x4C) {
            gCurrentActor->flags &= 0xFEFFFFFF;
            gCurrentActor->flags |= 0x400;
        }
        gCurrentActor->accelY = D_807502E8;
    }
    if (gGameMode != 1 && gCurrentMap != 0x4C && gCurrentActor->actorType != 0xFE) {
        gCurrentActor->flags &= 0xEFFFFFFF;
        return;
    }
    if (gCurrentMap == 0x4C) {
        lightUpdateFromActorLighting(&gCurrentActor->tintR, &gCurrentActor->tintG, &gCurrentActor->tintB);
    }
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        if (gActorGlobalState.unk258[i] == 3) {
            cmd = (ScriptCommand *)gActorGlobalState.unk278[i];
            switch (cmd->opcode) {
                case 25:
                    state->particleSprite = cmd->param1;
                    state->particleScalePct = cmd->param2;
                    break;
                case 24:
                    state->particlePath = pathPlaybackStart(gCurrentActor, state->pathId, 0, 0.0f, 0.0f, 0.0f, 0);
                    state->particleCount = cmd->param1;
                    state->particleColor = cmd->param2;
                    pathPlaybackSetSpeed(state->particlePath, state->pathSpeed / cmd->param1);
                    pathPlaybackSetLoopLimit(state->particlePath, 1);
                    pathPlaybackSetActive(state->particlePath, 1);
                    break;
                case 23:
                    state->pathId = cmd->param1;
                    state->pathSpeed = cmd->param2;
                    state->pathPlayback = pathPlaybackStart(gCurrentActor, state->pathId, 0, 0.0f, 0.0f, 0.0f, 0);
                    pathPlaybackSetSpeed(state->pathPlayback, state->pathSpeed);
                    pathPlaybackSetLoopLimit(state->pathPlayback, 1);
                    pathPlaybackSetActive(state->pathPlayback, 1);
                    gCurrentActor->state = 0xC;
                    gCurrentActor->unk155 = 0;
                    break;
                case 0:
                    gCurrentActor->speedY = cmd->param1;
                    break;
                case 7:
                    gCurrentActor->speedXZ = cmd->param1;
                    gCurrentActor->moveYaw = (cmd->param2 << 12) / 360;
                    break;
                case 2:
                    gCurrentActor->sub4->model->animId = -1;
                    actorScriptStart(gCurrentActor, D_80747750[cmd->param1]);
                    if (cmd->param2 != 0) {
                        scriptSetActorRampTarget(gCurrentActor, cmd->param2 / 100.0, 0.0f);
                    }
                    break;
                case 3:
                    if (gCurrentActor->sub4->animId != 0) {
                        actorScriptStart(gCurrentActor, 0);
                    }
                    controllerAnimSetState(gCurrentActor, cmd->param2 - (0 - D_80747904[cmd->param1]), 0.0f, 0.0f); // FAKE: param2 evaluated before the table lookup (ring order)
                    scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
                    func_806BFA8C(cmd->param2 - (0 - D_80747904[cmd->param1])); // FAKE: param2 evaluated before the table lookup (ring order)
                    break;
                case 13:
                    if (gCurrentActor->sub4->animId != 0) {
                        actorScriptStart(gCurrentActor, 0);
                    }
                    controllerAnimSetState(gCurrentActor, cmd->param2 - (0 - D_80747904[cmd->param1]), 0.0f, 8.0f); // FAKE: param2 evaluated before the table lookup (ring order)
                    scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
                    func_806BFA8C(cmd->param2 - (0 - D_80747904[cmd->param1])); // FAKE: param2 evaluated before the table lookup (ring order)
                    break;
                case 4:
                    scriptSetActorRampTarget(gCurrentActor, cmd->param1 / 100.0, cmd->param2);
                    break;
                case 5:
                    gCurrentActor->state = 2;
                    gCurrentActor->unk155 = 0;
                    if (gBehaviourAnimState->path != NULL) {
                        heapFree(gBehaviourAnimState->path);
                    }
                    gBehaviourExtraState->pathCount = 1;
                    gBehaviourAnimState->path = heapAlloc(2);
                    gBehaviourAnimState->path[0][1] = 0;
                    gBehaviourAnimState->path[0][0] = cmd->param1;
                    gBehaviourWorkState->unk25 = 0;
                    actorSetTargetSpeed(gCurrentActor, cmd->param2);
                    break;
                case 6:
                    gCurrentActor->speedXZ = 0.0f;
                    gCurrentActor->speedY = 0.0f;
                    gCurrentActor->x = D_807FDCA0->entries[cmd->param1].x;
                    gCurrentActor->y = D_807FDCA0->entries[cmd->param1].y;
                    gCurrentActor->z = D_807FDCA0->entries[cmd->param1].z;
                    gCurrentActor->yaw = (cmd->param2 << 12) / 360;
                    gCurrentActor->moveYaw = gCurrentActor->yaw;
                    break;
                case 8:
                    if (cmd->param2 != 0) {
                        state->yawFrom = gCurrentActor->yaw;
                        state->yawTo = (cmd->param1 << 12) / 360;
                        state->yawSteps = cmd->param2;
                        state->yawTimer = cmd->param2;
                    } else {
                        gCurrentActor->yaw = (cmd->param1 << 12) / 360;
                    }
                    break;
                case 19:
                    if (cmd->param2 != 0) {
                        state->pitchFrom = gCurrentActor->pitch;
                        state->pitchTo = (cmd->param1 << 12) / 360;
                        state->pitchSteps = cmd->param2;
                        state->pitchTimer = cmd->param2;
                    } else {
                        gCurrentActor->pitch = (cmd->param1 << 12) / 360;
                    }
                    break;
                case 20:
                    if (cmd->param2 != 0) {
                        state->rollFrom = gCurrentActor->roll;
                        state->rollTo = (cmd->param1 << 12) / 360;
                        state->rollSteps = cmd->param2;
                        state->rollTimer = cmd->param2;
                    } else {
                        gCurrentActor->roll = (cmd->param1 << 12) / 360;
                    }
                    break;
                case 21:
                    gCurrentActor->accelY = cmd->param1;
                    gCurrentActor->speedY = 0.0f;
                    gCurrentActor->state = 0x1D;
                    break;
                case 16:
                    if (cmd->param2 != 0) {
                        state->scaleFrom = gCurrentActor->sub4->scaleY;
                        gBehaviourWorkState->scale = cmd->param1 * 0.01;
                        state->scaleSteps = cmd->param2;
                        state->scaleTimer = cmd->param2;
                    } else {
                        actorSetUniformScale(gCurrentActor, cmd->param1 * 0.01);
                    }
                    break;
                case 9:
                    gBehaviourWorkState->unk4 = spawnNodeActivate(cmd->param1, 0);
                    break;
                case 11:
                    state->lerpSteps = cmd->param1;
                    break;
                case 12:
                    state->zoneTo = cmd->param1;
                    state->zoneFrom = cmd->param2;
                    state->lerpTimer = state->lerpSteps;
                    gCurrentActor->state = 0xE;
                    gCurrentActor->unk155 = 0;
                    break;
                case 14:
                    state->zoneTo = cmd->param1;
                    state->zoneFrom = cmd->param2;
                    state->lerpTimer = state->lerpSteps;
                    gCurrentActor->state = 0xF;
                    gCurrentActor->unk155 = 0;
                    break;
                case 10:
                    state->unk18 = (cmd->param1 << 12) / 360;
                    state->unk1A = cmd->param2;
                    break;
                case 15:
                    gCurrentActor->tintR = D_807478F4[cmd->param1 * 3];
                    gCurrentActor->tintG = D_807478F4[cmd->param1 * 3 + 1];
                    gCurrentActor->tintB = D_807478F4[cmd->param1 * 3 + 2];
                    break;
                case 17:
                    gCurrentActor->flags &= 0xFFFF7FFF;
                    gCurrentActor->state = 0x37;
                    gCurrentActor->unk155 = 0;
                    break;
                case 18:
                    gCurrentActor->flags &= 0xFF7FFFFF;
                    break;
                case 26:
                    gBehaviourWorkState->unk4 = spawnNodeActivate(cmd->param1, 0);
                    gCurrentActor->unk15F = cmd->param2;
                    gCurrentActor->state = 0xD;
                    gCurrentActor->unk155 = 0;
                    break;
                case 22:
                    gCurrentActor->state = 2;
                    gCurrentActor->unk155 = 0;
                    break;
            }
        }
    }
    if (state->rollTimer != 0) {
        ratio = (f32)state->rollTimer-- / state->rollSteps;
        gCurrentActor->roll = mathAngleLerp(state->rollTo, state->rollFrom, ratio);
    }
    if (state->pitchTimer != 0) {
        ratio = (f32)state->pitchTimer-- / state->pitchSteps;
        gCurrentActor->pitch = mathAngleLerp(state->pitchTo, state->pitchFrom, ratio);
    }
    if (state->yawTimer != 0) {
        ratio = (f32)state->yawTimer-- / state->yawSteps;
        gCurrentActor->yaw = mathAngleLerp(state->yawTo, state->yawFrom, ratio);
        gCurrentActor->moveYaw = gCurrentActor->yaw;
    }
    if (state->scaleTimer != 0) {
        ratio2 = (f32)state->scaleTimer-- / state->scaleSteps;
        actorSetUniformScale(gCurrentActor, gBehaviourWorkState->scale + (state->scaleFrom - gBehaviourWorkState->scale) * ratio2);
    }
    if (state->particlePath != 0xFF) {
        for (j = 0; j < state->particleCount && state->particlePath != 0xFF; j++) {
            if (j == 0xFE) {} // FAKE: extra 254 reference gives the 254 const a higher colouring priority (s4); dropping it costs 75 lines
            particleScale = (((randomNonNegative() >> 15) % 32767) % 51 + 0x4B) * 0.01;
            if (state->particlePath == 0xFE) {
                actorGetNodePos(gCurrentActor, 4, &posX, &posY, &posZ);
            } else if (pathPlaybackIsActive(state->particlePath) != 0) {
                pathPlaybackAdvance(state->particlePath);
                pathPlaybackGetPosition(state->particlePath, &posX, &posY, &posZ);
                posY += 10.0f;
            } else {
                state->particlePath = 0xFF;
            }
            if (state->particlePath == 0xFE || (state->particlePath != 0xFF && pathPlaybackIsActive(state->particlePath) != 0)) {
                effectSetMaxDistance(0x7D0);
                effectSetDepth(1);
                effectSetMode(2);
                col = &D_80747B00[state->particleColor * 3u]; // FAKE: unsigned 3 frees a callee-saved register (s5 otherwise)
                effectSetColor(col[0], col[1], col[2], 0xFF);
                effectSetCallback(func_80717D4C);
                effectSetSpeed(-10 - (randomNonNegative() >> 15) % 30);
                effectCreateAtPosition(sScriptEffectSprites[state->particleSprite], (f32)state->particleScalePct * 0.01 * particleScale, posX, posY, posZ);
            }
        }
    }
    switch (gCurrentActor->state) {
        case 0xD:
            if (gCurrentActor->unk15F != 0) {
                node = gCurrentActor->unk15F; // FAKE: s32 temp reproduces the original stack slot layout of posX/posY/posZ
                actorGetNodePos(gBehaviourWorkState->unk4, node, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
            } else {
                gCurrentActor->x = gBehaviourTargetActor->x;
                gCurrentActor->y = gBehaviourTargetActor->y;
                gCurrentActor->z = gBehaviourTargetActor->z;
            }
            gCurrentActor->yaw = gBehaviourWorkState->unk4->yaw;
            break;
        case 0xC:
            pathPlaybackAdvance(state->pathPlayback);
            pathPlaybackGetPosition(state->pathPlayback, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
            func_8072E320(8.0f);
            break;
        case 0xE:
        case 0xF:
            if (state->lerpTimer != 0) {
                ZoneEntry *to = &D_807FDCA0->entries[state->zoneTo];
                ZoneEntry *from = &D_807FDCA0->entries[state->zoneFrom];
                f32 frac = (f32)state->lerpTimer / state->lerpSteps;
                state->lerpTimer--;
                gCurrentActor->x = from->x + (to->x - from->x) * frac;
                gCurrentActor->z = from->z + (to->z - from->z) * frac;
                if (gCurrentActor->state == 0xF) {
                    gCurrentActor->y = from->y + (to->y - from->y) * frac;
                } else {
                    actorMoveWithinZone(0, from->x, from->z, 0x212, 0.0f);
                }
            } else {
                gCurrentActor->state = 0;
                gCurrentActor->unk155 = 0;
                actorSetTargetSpeed(gCurrentActor, 0);
            }
            break;
        case 0x2:
            actorMoveWithinZone(2, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0x210, 0.0f);
            if (patrolPathStep(2, 0) != 0) {
                gCurrentActor->state = 0;
                gCurrentActor->unk155 = 0;
                actorSetTargetSpeed(gCurrentActor, 0);
            }
            break;
        case 0x0:
            actorMoveWithinZone(0, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0x210, 0.0f);
            break;
        case 0x1D:
            actorApplyGravity();
            actorApplyVelocityCustom(gCurrentActor, 0.0f, gCurrentActor->speedY);
            break;
        case 0x37:
            if (gCurrentActor->unk155 != 0) {
                gCurrentActor->state = 0x40;
            } else {
                behaviourFadeOutWithinZone(0xA);
            }
            break;
    }
    behaviourUpdateShadowAlpha();
    if ((gBehaviourAnimState->flags & 0x1000) && func_8072881C(0, &gBehaviourWorkState->unk28) != 0 && (state->unk0 == 1 || state->unk0 == 9 || state->unk0 == 0x68)) {
        func_8072881C(0x81, &gBehaviourWorkState->unk28);
    }
}


extern Actor *gSpawnedActor;

void func_806C10A0(u8 paramA, u16 actionId, s16 scriptId) {
    f32 nodeY;

    if (!(gCurrentActor->flags & 0x10)) {
        playerKongStopSoundByState(gCurrentActor);
        gBehaviourAnimState->flags |= 0x200;
        actorSetTargetSpeed(gCurrentActor, 0);
    }
    func_80724A20();
    switch (gCurrentActor->state) {
        case 5:
            actorMoveWithinZone(0, 0.0f, 0.0f, 2, 0.0f);
        case 0:
            if (currentActorTestClearFlag()) {
                gCurrentActor->state = 0x12;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 2:
            actorMoveWithinZone(2, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
            patrolPathStep(2, 0);
            break;
        case 0x12:
            switch (gCurrentActor->unk155) {
                case 0:
                    resQueueAttachActor(gCurrentActor, actionId, paramA);
                    actorScriptStart(gCurrentActor, scriptId);
                    gCurrentActor->unk155++;
                    break;
                case 2:
                    if (!(gCurrentActor->flags & 0x2000000)) {
                        controllerAnimSetStateIfChanged(gCurrentActor, 0xE4, 0.0f, 2.0f);
                        actorSpawn(0xE1, 0x98);
                        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.21f);
                        actorGetNodePos(gCurrentActor, 1, &gSpawnedActor->x, &nodeY, &gSpawnedActor->z);
                        actorScriptStart(gSpawnedActor, 0x298);
                        gSpawnedActor->parentActor = gCurrentActor;
                        gCurrentActor->unk155++;
                    }
                    break;
                case 3:
                    gCurrentActor->y += 0.5;
                    break;
            }
            break;
    }
}

extern void *gCamActor;

void func_806C1300(void) {
    switch (gCurrentActor->unk155) {
        case 1:
            gCurrentActor->parentActor->flags &= ~4;
            gCurrentActor->unk155++;
            break;
        case 3:
            camEndPath(gCamActor);
            gCurrentActor->parentActor->state = 0x40;
            actorDespawn(gCurrentActor);
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void func_806C13AC(s16 threshold, s16 animLow, s16 animMid, s16 animHigh, s16 animMax) {
    s16 val;
    s32 ret;

    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->contactFlags |= 1;
        actorUpdatePrevContactFlags(gCurrentActor);
        gCurrentActor->floorNodeId = 1;
    }
    val = ret = playerSelectMoveTier(gCurrentActor, gCurrentActor->speedXZ, gBehaviourWorkState->unk26, gBehaviourWorkState->unk34, threshold);
    if (ret != gBehaviourWorkState->unk34) {
        switch (ret) {
            case 0:
            case 1:
            case 2:
                controllerAnimSetStateIfChanged(gCurrentActor, animLow, 0.0f, 6.0f);
                break;
            case 3:
                controllerAnimSetStateIfChanged(gCurrentActor, animMid, 0.0f, 6.0f);
                break;
            case 4:
                controllerAnimSetStateIfChanged(gCurrentActor, animHigh, 0.0f, 6.0f);
                break;
            case 5:
                controllerAnimSetStateIfChanged(gCurrentActor, animMax, 0.0f, 6.0f);
                break;
        }
        gBehaviourWorkState->unk34 = val;
    }
}


void func_806C151C(u16 actionId, u8 actionParam, s16 flagId) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 near;

    dx = gPrimaryPlayerActor->x - gCurrentActor->x;
    dy = gPrimaryPlayerActor->y - gCurrentActor->y;
    dz = gPrimaryPlayerActor->z - gCurrentActor->z;
    near = 0;
    if (dx * dx + dy * dy + dz * dz < 4900.0f) {
        near = 1;
    }
    if ((u8)near) { // FAKE: u8 truncation of the s32 flag reproduces the original andi test
        if (!flagGet(flagId, 2)) {
            resQueueAttachActor(gCurrentActor, actionId, actionParam);
            flagSet(flagId, 1, 2);
        }
    }
}

void func_806C15E8(void) {
    gBehaviourAnimState->flags |= 0x1000;
    gCurrentActor->unk146 = 0;
    actorSetTargetSpeed(gCurrentActor, 0);
    gCurrentActor->floorNodeId = 1;
}

void func_806C1640(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        func_806C15E8();
        if (gCurrentMap == 0x4C) {
            gCurrentActor->sub4->scaleX *= 0.8;
            gCurrentActor->sub4->scaleY *= 0.8;
            gCurrentActor->sub4->scaleZ *= 0.8;
        }
    }
    func_806BF920();
    if (gCurrentActor->flags & 0x10000000) {
        actorScriptedCommandUpdate();
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u32 gFrameCounter;
extern u8 D_8071FB08;
extern u8 D_807200D4;

void func_806C1734(void) {
    ActorSub4 *sub;
    s32 rnd;
    AnimSlot *inner;
    s16 animFrame;
    u8 nodeIndex;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        func_806C15E8();
    }
    func_806BF920();
    if (gCurrentActor->flags & 0x10000000) {
        animFrame = gCurrentActor->sub4->model->frame;
        actorScriptedCommandUpdate();
        sub = gCurrentActor->sub4;
        if (sub->blendFrom->clip == NULL) {
            inner = sub->model;
            switch (inner->animId) {
                case 0xBB:
                    if (30.0f < gCurrentActor->speedY && !(gFrameCounter & 3)) {
                        effectSetMode(2);
                        effectSetDepth(1);
                        effectSetCallback(effectShrinkFadeMatrixUpdate);
                        effectCreateAtActorBone(&D_8071FB08, 0.8f, gCurrentActor, 5, 0);
                    }
                    break;
                case 0x114:
                    if (0.0f == inner->speed) {
                        playerKongClearFlagsByActorType(gCurrentActor);
                    }
                    break;
                case 0xEA:
                    if (gCurrentActor->unk155 != 0 && animFrame >= 10) {
                        gCurrentActor->unk155 = 0;
                        projectileGetTargetCoords(gCurrentActor, 7);
                        projectileSpawnNodeEntry(0x29, 0xCA, 0.4f, gCurrentActor->yaw, 250.0f, 0.0f, gCurrentActor);
                    }
                    break;
                case 0x112:
                    if (animFrame >= 0x44 && animFrame < 0x64 && (gFrameCounter % 3) == 0) {
                        rnd = randomNonNegative() >> 15;
                        nodeIndex = (rnd % 0x7FFF) % 2;
                        effectSetDepth(1);
                        effectSetSpeed(0x50);
                        effectSetCallback(effectLightPulseOscillate);
                        effectCreateAtActorBone(&D_807200D4, 0.5f, gCurrentActor, nodeIndex + 9, 2);
                    }
                    break;
            }
        }
    } else {
        func_806C10A0(0, 3, 0x3D8);
        if (flagGet(4, 0)) {
            func_806C151C(3, 3, 0);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern Actor *gBehaviourTargetActor;
extern u8 D_8071FBA0;

void func_806C19F4(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        func_806C15E8();
        gCurrentActor->collision->radius = 180.0f;
        func_80724CA4(2, 1);
        playerKongStopAudioChannels(gCurrentActor, gCurrentActor->actorType);
    }
    if (gCurrentActor->flags & 0x10000000) {
        actorScriptedCommandUpdate();
        if (gCurrentActor->sub4->model->animId == 0x1A4) {
            effectSetDepth(1);
            effectSetColor(0x96, 0xFF, 0xFF, 0xFF);
            effectCreateAtActorBone(&D_8071FBA0, 0.7f, gCurrentActor, 5, 0);
        }
        func_80724E48(gBehaviourTargetActor == gPrimaryPlayerActor ? 5 : 7);
    } else {
        func_806C10A0(2, 6, 0x3D9);
        func_80724E48(0);
        func_806C151C(6, 1, 6);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 D_8071FB34;

void func_806C1B50(void) {
    u8 kind;
    u32 thr;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        func_806C15E8();
        playerKongStopAudioChannels(gCurrentActor, gCurrentActor->actorType);
    }
    func_806BF920();
    if (gCurrentActor->flags & 0x10000000) {
        actorScriptedCommandUpdate();
        if ((gCurrentActor->flags & 4) && gCurrentActor->unk155 != 0) {
            switch (gCurrentActor->sub4->model->animId) {
                case 0x23E:
                    kind = 0xD;
                    thr = 7;
                    break;
                case 0x23F:
                    kind = 0xE;
                    thr = 7;
                    break;
                case 0x240:
                    kind = 0x11;
                    thr = 3;
                    break;
                default:
                    goto done;
            }
            if ((f32)thr < gCurrentActor->sub4->model->frame) {
                effectCreateAtActorBone(&D_8071FB34, 0.5f, gCurrentActor, kind, 0);
                gCurrentActor->unk155 = 0;
            }
        }
    } else {
        func_806C10A0(2, 4, 0x3DB);
        func_806C151C(4, 1, 8);
    }
done:
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void func_806C1CCC(void) {
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->terminalSpeedY = -2000.0f;
        gCurrentActor->accelY = -200.0f;
        func_806C15E8();
        func_80724CA4(2, 1);
        if (gCurrentMap == 0x4C) {
            controllerAnimLoadStateAsset(gCurrentActor, 0xE);
        }
        playerKongStopAudioChannels(gCurrentActor, gCurrentActor->actorType);
    }
    if (gCurrentActor->flags & 0x10000000) {
        actorScriptedCommandUpdate();
        if (gCurrentActor->flags & 4) {
            if (gCurrentActor->sub4->model->animId == 0x2C4 && 25.0f < gCurrentActor->sub4->model->frame) {
                renderCallbacksRegister(gfxBuildScanlineNoise, 0, 3);
            }
        }
        func_80724E48(gBehaviourTargetActor == gPrimaryPlayerActor ? 5 : 7);
    } else {
        func_806C10A0(2, 5, 0x3DA);
        func_80724E48(0);
        func_806C151C(5, 1, 0xF);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern u8 D_8071FF58[];
extern u8 D_80720B58[];

void func_806C1E44(void) {
    s32 i;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        animSetLoopLimit(gCurrentActor, 0, 1);
        animSetFinished(gCurrentActor, 0, 1);
        switch (gCurrentMap) {
            case 0x14:
                gCurrentActor->cullMarginX = 0xFF;
                gCurrentActor->cullMarginY = 0xFF;
                if (flagGet(0x4C, 0) == 0) {
                    animSetFrameAndSubframe(gCurrentActor, 0, 1, 0);
                    actorScriptStart(gCurrentActor, 0x2BD);
                    gCurrentActor->state = 0;
                    gCurrentActor->unk155 = 0;
                } else {
                    gCurrentActor->state = 0x27;
                    gCurrentActor->unk155 = 0;
                    gCurrentActor->unk155 = 4;
                }
                break;
            case 0x26:
                animSetFrameAndSubframe(gCurrentActor, 0, 0, 0);
                gCurrentActor->state = 5;
                gCurrentActor->unk155 = 0;
                break;
        }
    }
    switch (gCurrentActor->state) {
        case 0:
            func_80724A20();
            switch (gCurrentActor->unk155) {
                case 1:
                    gBehaviourWorkState->timer = 3;
                    gCurrentActor->unk155 = 2;
                case 2:
                    if (!(gFrameCounter & 7)) {
                        if (gBehaviourWorkState->timer != 0) {
                            gBehaviourWorkState->timer--;
                            if (gBehaviourWorkState->timer == 0) {
                                gCurrentActor->unk155 = 0;
                            }
                            effectSetMode(2);
                            effectSetDepth(1);
                            effectSetDuration(0x28);
                            effectSetCallback(effectWobbleScaleUpdate);
                            effectCreateAtActorBone(D_8071FF58, 0.05f, gCurrentActor, 1, 0);
                        }
                    }
            }
            break;
        case 0x27:
            switch (gCurrentActor->unk155) {
                case 0:
                    animSetFrameAndSubframe(gCurrentActor, 0, 0, 0);
                    actorScriptStart(gCurrentActor, 0x2BE);
                    gCurrentActor->unk155 = 1;
                    break;
                case 3:
                    i = 0;
                    do {
                        effectSetDepth(1);
                        effectSetDuration(0x28);
                        effectSetCallback(effectScatterFallUpdate);
                        effectSetSpeed(gCurrentActor->yaw);
                        effectCreateAtActorBone(D_80720B58, 0.7f, gCurrentActor, 1, 0);
                        i++;
                    } while (i != 10);
                    gCurrentActor->unk155++;
                    break;
            }
            break;
        case 5:
            func_80724A20();
            func_806C151C(0xA, 1, 7);
            func_806C13AC(4, 0x4F1, 0x4F7, 0x4F7, 0x4F7);
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->state = 0x12;
                gCurrentActor->unk155 = 0;
            }
            break;
        case 0x12:
            switch (gCurrentActor->unk155) {
                case 0:
                    actorScriptStart(gCurrentActor, 0x2BF);
                    animSetFrameAndSubframe(gCurrentActor, 0, 2, 0);
                    actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
                    gCurrentActor->unk155 = 1;
                    break;
                case 2:
                    actorMoveWithinZone(2, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0, 0.0f);
                    patrolPathStep(2, 0);
                    break;
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern f32 D_807502F4;
extern s16 gCsModelIds[];
extern u8 gPlayerCharacterId;
extern u8 D_8071FC40;

void func_806C226C(void) {
    s16 i;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->accelY = D_807502F4;
        gCurrentActor->y = gCurrentActor->floorY;
        gCurrentActor->drawDistance = 0x4B0;
        if (flagGet(0x9E, 0) != 0) {
            if (gBehaviourExtraState->id == 0x16) {
                gCurrentActor->state = 0x28;
                gCurrentActor->unk155 = 0;
            } else {
                gCurrentActor->state = 0x40;
            }
        } else if (gBehaviourExtraState->id == 0x16) {
            gCurrentActor->state = 0x40;
        }
    }
    for (i = 0; i < gActorGlobalState.unk254; i++) {
        if (gActorGlobalState.unk258[i] == 3) {
            actorScriptStart(gCurrentActor, 0x2A3);
            gCurrentActor->state = 0x27;
            gCurrentActor->unk155 = 0;
            camStartPath(gCurrentActor, 0x16, 1);
            flagSet(0x9E, 1, 0);
        }
    }
    switch (gCurrentActor->state) {
        case 0x27:
            if (gCurrentActor->contactFlags & 4) {
                actorPitchEaseTowardPoint(2, 0, gBehaviourWorkState->targetX, gBehaviourWorkState->targetY, gBehaviourWorkState->targetZ, 0x46, 30.0f, 100.0f, 0);
                if (((randomNonNegative() >> 15) % 1000) >= 0x3A3) {
                    effectSetCallback(effectWobbleRiseUpdate);
                    effectSetDepth(1);
                    effectSetDuration(-1);
                    effectCreateAtPosition(&D_8071FC40, 0, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                }
            } else {
                if ((gCurrentActor->contactFlags ^ gCurrentActor->prevContactFlags) & 1) {
                    actorScriptStart(gCurrentActor, 0x2A4);
                }
                actorMoveWithinZone(2, gBehaviourWorkState->targetX, gBehaviourWorkState->targetZ, 0x200, 0.0f);
                if (gCurrentActor->speedY < -10.0f) {
                    gCurrentActor->roll = mathAngleEaseToward(gCurrentActor->roll, 0x400, 10.0f);
                }
            }
            patrolPathStep(2, 0);
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->state = 0x40;
            }
            break;
        case 0x28:
            switch (gCurrentActor->unk155) {
                case 0:
                    zoneEntryGetPosition(2, 3, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
                    actorScriptStart(gCurrentActor, 0x2A6);
                    gCurrentActor->roll = 0;
                    gCurrentActor->unk155++;
                case 1:
                    if (actorIsTargetWithinDistance(0xC8) != 0) {
                        gCurrentActor->unk155++;
                        if (flagGet(0xC1, 0) != 0) {
                            if (gPlayerCharacterId == 0 && flagGet(0xA5, 0) == 0) {
                                resQueueAttachActor(gCurrentActor, 0x1C, 2);
                            } else if (gPlayerCharacterId != 0) {
                                resQueueAttachActor(gCurrentActor, 0x1C, 0);
                            }
                        } else if (gPlayerCharacterId == 0) {
                            camStartPath(gCurrentActor, 0x1E, 1);
                            resQueueSetValue(1);
                            resQueueAttachActor(gCurrentActor, 0x1C, 1);
                            gCurrentActor->unk155 = 0x63;
                        } else {
                            resQueueAttachActor(gCurrentActor, 0x1C, 0);
                        }
                    }
                    break;
                case 2:
                    if (flagGet(0xC1, 0) == 0 && actorIsTargetWithinDistance(0x12C) == 0) {
                        gCurrentActor->unk155 = 1;
                    }
                    break;
                case 0x63:
                    if (camIsCutsceneActive() == 0 && !(gCurrentActor->flags & 0x2000000)) {
                        resQueueAttachActor(gCurrentActor, 0x1C, 2);
                        gCurrentActor->unk155 = 3;
                    }
                    break;
            }
            modelSlotGetNodePos(gCsModelIds[58], 1, 1, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
            actorTurnTowardActorYaw(0xA, gBehaviourTargetActor);
            break;
    }
    func_8072881C(0, &gBehaviourWorkState->unk28);
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void actorPlaySoundSpawnBoneEffects(void) {
    f32 scale = gCurrentActor->sub4->scaleY / 0.15;

    sfxPlayActorSound(gCurrentActor, 0x114, 0x50, 0, 0, 0xFF, 0.5f, 0);
    if (gFrameCounter & 1) {
        effectSpawnActorBone(gCurrentActor, 1, scale);
        effectSpawnActorBone(gCurrentActor, 3, scale);
    } else {
        effectSpawnActorBone(gCurrentActor, 2, scale);
        effectSpawnActorBone(gCurrentActor, 4, scale);
    }
}


void actorSpawnOctagonRingsByTimer(void) {
    f32 v;
    f32 nodeX;
    f32 nodeY;
    f32 nodeZ;
    f32 s;
    f32 pad;
    s16 i;

    v = gCurrentActor->sub4->model->frame;
    if (v > 83.0f) {
        actorPlaySoundSpawnBoneEffects();
        v = gCurrentActor->sub4->model->frame;
    }
    if (v > 2.0f && v < 90.0f) {
        i = 1;
        if (gFrameCounter % 6 == 0) {
            s = (v / 70.0 > 1.0) ? 1.0 : v / 70.0;
            do {
                actorGetNodePos(gCurrentActor, i, &nodeX, &nodeY, &nodeZ);
                effectSpawnOctagonRing((s * 0.3 < 0.15) ? 0.15 : s * 0.3, nodeX, nodeY + 3.0f, nodeZ);
                i++;
            } while (i < 5);
        }
    }
}


void effectSpawnColoredParticleAtPoint(u8 r, u8 g, u8 b, f32 x, f32 y, f32 z, void *particleGfx, f32 scale) {
    effectSetMaxDistance(1000);
    effectSetMode(0xFF);
    effectSetParam(((randomNonNegative() >> 15) % 0x7FFF) % 11);
    effectSetColor(r, g, b, 0xFF);
    effectSetCallback(effectLinearFadeAlphaUpdate);
    effectSetSpeed(2);
    effectCreateAtPosition(particleGfx, scale * 0.2, x, y, z);
}

void actorSpawnParticlesAlongNodeLoop(u8 startNode, u8 endNode, u8 colorIndex, void *particleGfx) {
    f32 scale;
    f32 node1X;
    f32 node1Y;
    f32 node1Z;
    f32 node2X;
    f32 node2Y;
    f32 node2Z;
    f32 frac;
    s16 i;
    s16 j;

    scale = gCurrentActor->sub4->scaleY / 0.15;
    scale = scale / 1.5;
    for (i = startNode; i <= endNode; i++) {
        for (j = 0; j < 3.0; j++) {
            frac = (f32)j / 3.0;
            actorGetNodePos(gCurrentActor, i, &node1X, &node1Y, &node1Z);
            if (i < endNode) {
                actorGetNodePos(gCurrentActor, i + 1, &node2X, &node2Y, &node2Z);
            } else {
                actorGetNodePos(gCurrentActor, startNode, &node2X, &node2Y, &node2Z);
            }
            effectSpawnColoredParticleAtPoint(D_80747B00[colorIndex * 3], D_80747B00[colorIndex * 3 + 1], D_80747B00[colorIndex * 3 + 2], (node2X - node1X) * frac + node1X, (node2Y - node1Y) * frac + node1Y, (node2Z - node1Z) * frac + node1Z, particleGfx, scale);
        }
    }
}

extern u8 sEffectSparkConfig[];

void actorSpawnParticlesAlongNodeRanges(void) {
    actorSpawnParticlesAlongNodeLoop(1, 0xB, 6, sEffectSparkConfig);
    actorSpawnParticlesAlongNodeLoop(0x20, 0x30, 6, sEffectSparkConfig);
    actorSpawnParticlesAlongNodeLoop(0xC, 0x16, 2, sEffectSparkConfig);
    actorSpawnParticlesAlongNodeLoop(0x17, 0x1F, 2, sEffectSparkConfig);
}



extern s32 gGlobalCutsceneFlags;

void func_806C2DF4(void) {
    ScriptedActorState *state;
    f32 nodePosX;
    f32 nodePosY;
    f32 nodePosZ;
    f32 scale;

    state = C46V->unk17C;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        scale = gCurrentActor->sub4->scaleY;
        controllerAnimFree(gCurrentActor);
        controllerAnimInit(gCurrentActor, state->unk0);
        gCurrentActor->collision = actorSub140CreateFromModel(gCurrentActor);
        gCurrentActor->unk146 = 0;
        gCurrentActor->drawDistance = 0xFA0;
        gBehaviourAnimState->flags |= 0x20;
        gCurrentActor->flags &= ~0x01000000;
        gCurrentActor->unk144 = 1;
        switch (state->unk0) {
            case 0x21:
                if (gCurrentMap == 0x98 || gCurrentMap == 0x1C) {
                    gCurrentActor->flags |= 0x400;
                    gBehaviourAnimState->flags |= 0x100;
                }
                /* fallthrough */
            case 0x22:
            case 0x23:
                func_80724CA4(2, 1);
                break;
            case 1:
            case 4:
            case 6:
            case 9:
            case 0xC:
                gBehaviourAnimState->flags |= 0x1000;
                gCurrentActor->flags |= 0x400;
                gCurrentActor->floorNodeId = 1;
                gCurrentActor->flags |= 0x1000;
                func_80724CA4(2, 1);
                playerKongStopSoundByState(gCurrentActor);
                break;
            case 0x17:
                gCurrentActor->floorNodeId = 1;
                /* fallthrough */
            case 0x18:
            case 0x49:
                state->unk2C = 9;
                /* fallthrough */
            case 0x6B:
            case 0x88:
                gCurrentActor->flags |= 0x1000;
                /* fallthrough */
            case 0x38:
            case 0x3A:
            case 0x3C:
            case 0x58:
                gBehaviourAnimState->flags |= 0x100;
                /* fallthrough */
            case 0x27:
            case 0x2D:
            case 0x66:
                gCurrentActor->flags |= 0x400;
                break;
            case 0x31:
                if (gGlobalCutsceneFlags & 2) {
                    animSetLoopLimit(gCurrentActor, 1, 1);
                    animSetFinished(gCurrentActor, 1, 1);
                    animSetFrameAndSubframe(gCurrentActor, 1, 1, 0);
                }
                gBehaviourAnimState->flags |= 0x1000;
                gBehaviourAnimState->flags |= 0x100;
                gCurrentActor->flags |= 0x400;
                break;
            case 0x12:
                gCurrentActor->floorNodeId = 1;
                if (!(gGlobalCutsceneFlags & 2)) {
                    gCurrentActor->unk146 = 1;
                }
                break;
            case 0x80:
                gCurrentActor->flags |= 0x800000;
                gBehaviourAnimState->flags |= 0x100;
                gCurrentActor->flags |= 0x400;
                break;
            case 0x37:
                gCurrentActor->flags |= 0x400;
                animSetLoopLimit(gCurrentActor, 0, 1);
                animSetFinished(gCurrentActor, 0, 1);
                animSetFrameAndSubframe(gCurrentActor, 0, gBehaviourExtraState->respawnDelay, 0);
                break;
            case 0x45:
                scale *= 10.0f;
                /* fallthrough */
            case 0x3D:
                gCurrentActor->floorNodeId = 2;
                gCurrentActor->flags |= 0x400;
                break;
            case 0x3B:
                gCurrentActor->terminalSpeedY = -10.0f;
                gCurrentActor->flags |= 0x400;
                break;
            case 0x25:
                gCurrentActor->terminalSpeedY = -2000.0f;
                gCurrentActor->flags |= 0x400;
                gCurrentActor->unk146 = -1;
                break;
            case 0x11:
                gBehaviourAnimState->flags |= 0x1000;
                if (gCurrentMap == 0x4C) {
                    gCurrentActor->unk146 = 0;
                } else {
                    gCurrentActor->unk146 = 2;
                }
                /* fallthrough */
            case 0x13:
            case 0xDC:
            case 0xDD:
            case 0xDE:
            case 0xDF:
            case 0xE3:
                gCurrentActor->flags |= 0x400;
                break;
            case 0xE2:
                scale *= 8.0f;
                actorSetUniformScale(gCurrentActor, scale);
                gCurrentActor->roll = 0xC8;
                func_806BFBB4();
                actorSpawnParticlesAlongNodeRanges();
                break;
            case 0x68:
                if (gCurrentMap == 0xCD) {
                    gCurrentActor->unk146 = 1;
                } else {
                    gCurrentActor->unk146 = 5;
                }
                /* fallthrough */
            case 0x70:
                gBehaviourAnimState->flags |= 0x1000;
                gCurrentActor->floorNodeId = 1;
                /* fallthrough */
            case 0x69:
                gCurrentActor->flags |= 0x400;
                gCurrentActor->flags |= 0x1000;
                break;
        }
        actorSetUniformScale(gCurrentActor, scale);
        if (gCurrentMap == 0xD0) {
            gBehaviourAnimState->flags |= 0x100;
            gCurrentActor->flags &= ~0x01000000;
        }
    }
    actorGetNodePosOrPosition(gCurrentActor, &nodePosX, &nodePosY, &nodePosZ);
    func_806BF920();
    actorScriptedCommandUpdate();
    gCurrentActor->contactFlags = 0;
    gCurrentActor->prevContactFlags = 0;
    if (gBehaviourTargetActor != gPrimaryPlayerActor) {
        func_80724E48(7);
    }
    switch (gCurrentActor->sub4->model->animId) {
        case 0x3EA:
            gCurrentActor->unk146 = 0;
            break;
        case 0x8E:
        case 0x320:
        case 0x32F:
        case 0x341:
        case 0x3CC:
        case 0x52F:
        case 0x63A:
            if (gBehaviourAnimState->flags & 0x1000) {
                gBehaviourAnimState->flags &= ~0x1000;
                func_80728950(0);
                if (state->unk0 == 0x68) {
                    func_80728950(1);
                }
            }
            break;
        case 0x530:
            currentActorAnimSetFrame(1, 0);
            break;
        case 0x531:
        case 0x62C:
            if (!(gBehaviourAnimState->flags & 0x1000)) {
                gBehaviourAnimState->flags |= 0x1000;
                currentActorAnimSetFrame(0, 0);
            }
            break;
        case 0x92:
            if (!(gBehaviourAnimState->flags & 0x1000) && gCurrentActor->sub4->model->frame >= 127.0f) {
                gBehaviourAnimState->flags |= 0x1000;
                currentActorAnimSetFrame(0, 0);
            }
            break;
        case 0x434:
            if (gCurrentActor->sub4->model->frame < 60.0f) {
                break;
            }
            /* fallthrough */
        case 0x436:
            if (!(gFrameCounter & 1)) {
                effectSetMaxDistance(0x7D0);
                effectSetMode(3);
                effectSetColor(0x32, 0x32, 0x32, 0xFF);
                effectSpawnBoneDefault(gCurrentActor, 1, 1.3f, 0, 0, 0, -0x50);
            }
            break;
        case 0x4DA:
        case 0x4DB:
        case 0x4DC:
        case 0x4DD:
        case 0x4DE:
            if (!(gFrameCounter & 3)) {
                effectSetDepth(1);
                effectSetCallback(effectShrinkFadeMatrixUpdate);
                effectCreateAtActorBone(&D_8071FB08, 0.6f, gCurrentActor, 2, 0);
            }
            break;
        case 0x4C7:
            if (gCurrentActor->sub4->model->frame >= 23.0f && gCurrentActor->unk155 != 0) {
                gCurrentActor->unk155 = 0;
                projectileGetTargetCoords(gCurrentActor, 2);
                projectileSpawnNodeEntry(0x29, 0xCB, 0.4f, gCurrentActor->yaw, 400.0f, 0, gCurrentActor);
            }
            break;
        case 0x54D:
            if (gCurrentActor->sub4->model->speed == 0) {
                gCurrentActor->state = 0x40;
            } else if (gCurrentActor->sub4->model->frame < 210.0f) {
                effectSpawnActorBoneEffects(2);
            } else if (gCurrentActor->sub4->model->frame < 235.0f) {
                effectSpawnActorBoneEffects(3);
            }
            break;
        case 0x549:
            if (gCurrentActor->sub4->model->frame > 65.0f && gCurrentActor->sub4->model->frame < 101.0f) {
                effectSpawnChildAtNode(2, (randomNonNegative() >> 15) % 2048 + gCurrentActor->yaw - 0x400, (randomNonNegative() >> 15) % 2048);
            }
            break;
        case 0x498:
            if (gCurrentActor->sub4->model->frame < 2.0f) {
                effectSpawnActorScale(gCurrentActor);
            }
            effectActorCheckGroundScaleSpawn(gCurrentActor);
            break;
        case 0x43E:
            actorSpawnOctagonRingsByTimer();
            break;
        case 0x43D:
        case 0x440:
            actorPlaySoundSpawnBoneEffects();
            break;
        case 0x43F:
            if (gCurrentActor->sub4->model->frame < 68.0f) {
                actorPlaySoundSpawnBoneEffects();
            }
            if (gCurrentActor->sub4->model->frame > 65.0f) {
                sfxStopSlotSound(gCurrentActor, 0);
            }
            break;
        case 0x52E:
            if (gCurrentActor->sub4->model->frame < 2.0f) {
                effectCreateAtActorBone(&D_8071FB34, 1.5f, gCurrentActor, 6, 0);
            }
            break;
        case 0x527:
        case 0x528:
            actorSetGroupState(3, 0xA);
            break;
        case 0x52A:
            actorSetGroupState(3, 3);
            break;
    }
    if (gCurrentMap == 0xD0 && (gCurrentActor->flags & 0x1000)) {
        commandQueuePush(gCurrentActor, gCurrentActor->x, gCurrentActor->y + 30.0f, gCurrentActor->z, 0xFF, 0xFF, 0xFF, 0xFF, 0);
    }
    if (gCurrentActor->sub4->animId == 0x22A) {
        if ((randomNonNegative() >> 15) % 100 >= 0x47 || gCurrentActor->unk155 != 0) {
            effectSpawnJointBeam(7, 0xB, 0x11, 0x20);
            effectSpawnJointBeam(0xC, 0x10, 0x11, 0x20);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x8A, 0x64, 0x7F, 0x28, 0, 0.3f, 0);
            gCurrentActor->flags |= 4;
        } else {
            gCurrentActor->flags &= ~4;
            sfxStopSlotSound(gCurrentActor, 0);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

extern s16 D_80750AC8;

void func_806C3A8C(void) {
    s32 dist;
    f32 pad0;
    f32 pad1;
    u8 flag1;
    u8 flag2;
    u8 flag3;
    u8 flag4;
    u8 inRange;

    dist = (gPrimaryPlayerActor->x - gCurrentActor->x) * (gPrimaryPlayerActor->x - gCurrentActor->x) + (gPrimaryPlayerActor->y - gCurrentActor->y) * (gPrimaryPlayerActor->y - gCurrentActor->y) + (gPrimaryPlayerActor->z - gCurrentActor->z) * (gPrimaryPlayerActor->z - gCurrentActor->z);
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->eyeHeight = 0x19;
        actorUpdatePrevContactFlags(gCurrentActor);
        if (flagGet(0x1E, 2) == 0) {
            camStartPath(gCurrentActor, 0x14, 1);
            flagSet(0x1E, 1, 2);
        }
        if (flagGet(0xBF, 0) == 0) {
            if (flagGet(0xBA, 0) && flagGet(0xBB, 0) && flagGet(0xBC, 0) && flagGet(0xBD, 0) && flagGet(0xBE, 0)) {
                gCurrentActor->state = 0x27;
                gCurrentActor->unk155 = 0;
            } else if (flagGet(0xBA, 0) || flagGet(0xBB, 0) || flagGet(0xBC, 0) || flagGet(0xBD, 0) || flagGet(0xBE, 0)) {
                gCurrentActor->state = 0x1F;
                gCurrentActor->unk155 = 0;
            } else {
                gCurrentActor->state = 0x1E;
                gCurrentActor->unk155 = 0;
            }
        } else {
            gCurrentActor->state = 0x20;
            gCurrentActor->unk155 = 0;
        }
    }
    actorScriptedCommandUpdate();
    switch (gCurrentActor->state) {
        case 0x1E:
            switch (gCurrentActor->unk155) {
                case 0:
                    inRange = dist < 0xF424;
                    if (inRange) {
                        gCurrentActor->unk155++;
                    }
                    break;
                case 1:
                    inRange = dist < 0x2710;
                    if (inRange) {
                        actorScriptStart(gCurrentActor, 0x3A4);
                        resQueueAttachActor(gCurrentActor, 0x17, 0);
                        gCurrentActor->unk155++;
                    }
                    break;
            }
            break;
        case 0x1F:
            inRange = dist < 0x2710;
            if (inRange && gCurrentActor->unk155 == 0) {
                flag4 = flagGet(0xBD, 0);
                flag3 = flagGet(0xBC, 0);
                flag2 = flagGet(0xBB, 0);
                flag1 = flagGet(0xBA, 0);
                D_80750AC8 = flagGet(0xBE, 0) + flag1 + flag2 + flag3 + flag4;
                resQueueAttachActor(gCurrentActor, 0x17, 2);
                gCurrentActor->unk155++;
            }
            break;
        case 0x20:
            inRange = dist < 0x2710;
            if (inRange && gCurrentActor->unk155 == 0 && camIsCutsceneActive() == 0) {
                camStartPath(gCurrentActor, 0x18, 1);
                resQueueAttachActor(gCurrentActor, 0x17, 3);
                gCurrentActor->unk155++;
            }
            break;
        case 0x27:
            if (camIsCutsceneActive() == 0) {
                switch (gCurrentActor->unk155) {
                    case 0:
                        camStartPath(gCurrentActor, 0x17, 1);
                        resQueueSetValue(1);
                        resQueueAttachActor(gCurrentActor, 0x17, 1);
                        gCurrentActor->unk155++;
                        break;
                    case 1:
                        if (!(gCurrentActor->flags & 0x2000000)) {
                            csModelStateSetFirstByte(0xE, 0xA);
                            gCurrentActor->state = 0x20;
                            gCurrentActor->unk155 = 0;
                        }
                        break;
                }
            }
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
