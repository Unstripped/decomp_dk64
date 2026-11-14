#include "common.h"
#include "boss.h"
#include "actor.h"
#include "sched.h"
#include "proto/boss/3840.h"
#include "proto/boss/B100.h"
#include "proto/global/10E1D0.h"
#include "proto/global/1295B0.h"
#include "proto/global/135D30.h"
#include "proto/global/17B90.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/8CA50.h"
#include "proto/global/FCCD0.h"
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

// K. Rool (Tiny phase) actor: component 2 (0x178) is the script state, component 3 (0x17C) the
// array of the three actors spawned by func_8002FEC0 (group members 1-3; the leader is member 0).
typedef struct BossKRoolTinyActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
    /* 0x17C */ Actor **minions;
} BossKRoolTinyActor;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;

s32 actorSpawn(s32, s32);
void actorCopyPoseAndScale(void *, void *, f32);
void actorScriptStart(void *, s32);
void sfxPlayAtFBD6CPosition(void);




extern Actor *gPrimaryPlayerActor;

// Dogadon actor: component 2 (0x178) is the script state.
typedef struct BossDogadonActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
} BossDogadonActor;

extern u8 *D_80035A90[];
extern PlayerStruct *gPlayerSlots;
extern void *gCamActor;

void behaviourFrameBegin(void);
void camSetSecondTarget(struct CamActor *, s16, s16);
void zoneEntryGetPosition(u8, u8, f32 *, f32 *, f32 *);
u16 camStartPath(void *, s16, u8);
void hudCountdownTimerSaveElapsed(void *);
void playerWaypointPathStartLineFromActor(Actor *, s16, s16, u8);
void csSendActorMessagePayload(s16, s16);
void playerSetSizeMode(Actor *, u8);
u32 actorMoveWithinZone(u8, f32, f32, u16, f32);
void actorSetTargetSpeed(void *, s32);
s16 mathAngleEaseToward(s16, s16, f32);
void projectileSpawnWithShockwave(s16, f32, u8, u8, u8, u8, f32, f32, f32, f32);
s16 sfxPlayAtPositionPooled(f32, f32, f32, s16, u8, s16, u8, u8, f32, u8);
void scriptSetActorRampTarget(void *, f32, f32);
s32 currentActorTestClearFlag(void);
void behaviourUpdateShadowAlpha(void);

#define DOGADON_ACTOR ((BossDogadonActor *)gCurrentActor)

void bossDogadonStep(void) {
    BossScriptState *scriptState;
    u8 *scriptOpcodes;
    s32 pad[2];
    f32 offsetSin;

    scriptState = DOGADON_ACTOR->scriptState;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->interactionType = 8;
        transitionSetState(0);
        camSetSecondTarget(gCamActor, 0, 0);
        gCurrentActor->segmentFlags = 5;
        gCurrentActor->floorNodeId = 1;
        func_80724CA4(2, 1);
        gCurrentActor->state = 0x1E;
        gCurrentActor->unk155 = 0;
        if (flagGet(0x54, 2) != 0) {
            scriptState->phase = 4;
            gCurrentActor->state = 0x37;
            gCurrentActor->unk155 = 0;
        } else if (flagGet(0x53, 2) != 0) {
            scriptState->phase = 3;
        } else if (flagGet(0x52, 2) != 0) {
            scriptState->phase = 2;
        } else if (flagGet(0x51, 2) != 0) {
            scriptState->phase = 1;
        }
        if (scriptState->phase != 0 && gCurrentActor->state != 0x37) {
            gCurrentActor->state = 0x31;
            gCurrentActor->unk155 = 0;
            zoneEntryGetPosition(1, 0, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
        }
    }
    scriptOpcodes = D_80035A90[scriptState->phase];
    bossRoundFrame(scriptOpcodes);
    switch (gCurrentActor->state) {
    case 0x28:
        if (gActorGlobalState.bossFightPhase == 5 && gPlayerSlots->unk2C0 != 1) {
            gCurrentActor->unk144 = 1;
            gPrimaryPlayerActor->unk144 = 1;
            camStartPath(0, 2, 1);
            gCurrentActor->state = 0x29;
            hudCountdownTimerSaveElapsed(gCurrentActor->parentActor);
            screenSetTransitionFadeType(1);
            transitionSetState(1);
            mapRequestTransition(0xD6, 0);
            gPrimaryPlayerActor->x = mathSinF(gCurrentActor->yaw + 0x320) * 30.0 + gCurrentActor->x;
            gPrimaryPlayerActor->z = mathCosF(gCurrentActor->yaw + 0x320) * 30.0 + gCurrentActor->z;
            offsetSin = mathSinF(gCurrentActor->yaw + 0x384);
            playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, (s32)(offsetSin * 15.0f + gCurrentActor->x), (s32)(mathCosF(gCurrentActor->yaw + 0x384) * 15.0f + gCurrentActor->z), 0x50);
        } else {
            switch (gCurrentActor->unk155) {
            case 0:
                if (scriptState->loopPos != 0) {
                    csSendActorMessagePayload(0, 0);
                }
                actorScriptStart(gCurrentActor, 0x3FF);
                gBehaviourWorkState->timer = scriptOpcodes[scriptState->scriptPos] * 0x1E;
                scriptState->scriptPos++;
                gCurrentActor->unk155++;
                break;
            case 1:
                if (gBehaviourWorkState->timer != 0) {
                    gBehaviourWorkState->timer--;
                } else {
                    actorScriptStart(gCurrentActor, 0x400);
                    gCurrentActor->unk155++;
                }
                break;
            case 3:
                if (gPlayerSlots->unk2C0 != 1) {
                    playerSetSizeMode(gPrimaryPlayerActor, 1);
                }
                csSendActorMessagePayload(0, 0xFF);
                actorScriptStart(gCurrentActor, 0x3E4);
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
                scriptState->scriptPos++;
                gCurrentActor->unk155 = 0;
                break;
            }
        }
        break;
    case 0x27:
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4310, 0.0f);
        switch (gCurrentActor->unk155) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            scriptState->unk18[0] = scriptOpcodes[scriptState->scriptPos];
            scriptState->scriptPos++;
            gCurrentActor->unk155++;
            /* fallthrough */
        case 1:
            gBehaviourWorkState->timer = 4;
            actorScriptStart(gCurrentActor, 0x3E7);
            gCurrentActor->unk155++;
            break;
        case 2:
            gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D((f32)D_807FDCA0->entries->x, (f32)D_807FDCA0->entries->z, gCurrentActor->x, gCurrentActor->z), 10.0f);
            break;
        case 3:
            if (gBehaviourWorkState->timer != 0 && gFrameCounter % 5 == 0) {
                projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 150, 3, (f32)((f64)scriptState->phase * 0.01 + 1.04), 0.0f, 0.0f, 0.0f);
                if (gBehaviourWorkState->timer-- < 4) {
                    gSpawnedActor->yawSpeed = 0;
                } else {
                    sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x25A, 0xFF, 0x7F, 1, 0, 0.3f, 0);
                }
                controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0.0f, 0.0f);
                scriptSetActorRampTarget(gSpawnedActor, 0.5f, 0.0f);
            } else if (gBehaviourWorkState->timer == 0) {
                gBehaviourWorkState->timer = scriptState->unk18[0];
                gCurrentActor->unk155++;
            }
            break;
        case 4:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
                actorScriptStart(gCurrentActor, 0x3E4);
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
                scriptState->scriptPos++;
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x1E:
        scriptState->phase = 0;
        scriptState->scriptPos = 0;
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
        scriptState->scriptPos++;
        gCurrentActor->unk155 = 0;
        gCurrentActor->speedXZ = (f32)gBehaviourExtraState->targetSpeed;
        break;
    case 0:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x3EA);
            gCurrentActor->unk155++;
            break;
        case 2:
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
            scriptState->scriptPos++;
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x31:
        switch (gCurrentActor->unk155) {
        case 0:
            playerSetSizeMode(gPrimaryPlayerActor, 0);
            playerSetSizeMode(gPrimaryPlayerActor, 1);
            camStartPath(gCurrentActor, 1, 1);
            actorScriptStart(gCurrentActor, 0x3FB);
            gCurrentActor->unk155++;
            break;
        case 2:
            actorScriptStart(gCurrentActor, 0x3E4);
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
            scriptState->scriptPos++;
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x37:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0);
            camStartPath(gCurrentActor, 0x15, 1);
            gCurrentActor->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                screenSetTransitionFadeType(0);
                mapRequestTransition(0xCF, 0);
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


void func_8002FB7C(scaleFactor)
u8 scaleFactor;
{
    BoneVector *sub;
    f32 sin_val;

    sub = gCurrentActor->sub4->boneScales;
    sub->bone = 2;
    sub->lastBone = 4;
    sub->x = 1.0f;
    sin_val = mathSinF((s16)(gFrameCounter << 7));
    sub->x += (f64)scaleFactor * (0.04 + 0.04 * (f64)sin_val);
    sub->y = sub->x;
    sub->z = 1.0f;
}
void func_8002FC48(actorObj, frame)
Actor *actorObj;
u8 frame;
{
    animSetLoopLimit(actorObj, 0, 1);
    animSetFinished(actorObj, 0, 1);
    animSetFrameAndSubframe(actorObj, 0, frame, 0.0f);
}

void scriptSetActorRampTarget(void *, f32, f32);

void bossActorGroupCommand(leader, mask, command, param)
BossKRoolTinyActor *leader;
u8 mask;
s32 command;
u8 param;
{
    Actor **minions;
    Actor *actor;
    s16 i;

    minions = leader->minions;
    for (i = 0; i < 4; i++) {
        if (mask & (1 << i)) {
            actor = i != 0 ? minions[i - 1] : &leader->base;
            switch (command) {
            case 1:
            case 2:
                actor->interactionType = command;
                break;
            case -1:
            case 0:
                actor->callbackMask = command;
                break;
            default:
                actorScriptStart(actor, command);
                if (param) {
                    scriptSetActorRampTarget(actor, (f64)param * 0.01, 0.0f);
                }
                break;
            }
        }
    }
}


void func_8002FDF8(void *actorObj, u8 scaleVal) {
    s32 finalScale;
    s32 animFrame;

    if (gCurrentActor->unk15F == 2) {
        finalScale = 4;
    } else {
        finalScale = scaleVal;
    }
    func_8002FB7C(finalScale & 0xFF);
    if (gActorGlobalState.bossFightPhase == 4) {
        bossActorGroupCommand(actorObj, 0xF, 0, 0);
        animFrame = (0xA - gCurrentActor->health) & 0xFF;
        func_8002FC48(gCurrentActor, animFrame);
        actorScriptStart(gCurrentActor, 0x415);
    }
    if (gActorGlobalState.bossFightPhase == 5 || gActorGlobalState.bossFightPhase == 4) {
        sfxPlayAtFBD6CPosition();
    }
}

void func_8002FEC0(minions, slotIndex, modelId)
Actor **minions;
u8 slotIndex;
s32 modelId;
{
    actorSpawn(0xE5, modelId);
    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY);
    gSpawnedActor->flags |= 0x1400;
    gSpawnedActor->parentActor = gCurrentActor;
    gSpawnedActor->unk144 = gCurrentActor->unk144;
    gSpawnedActor->flags = gCurrentActor->flags;
    minions[slotIndex] = gSpawnedActor;
}


#define KROOL_TINY_ACTOR ((BossKRoolTinyActor *)gCurrentActor)

extern PlayerState *gActivePlayerState;
extern u8 *D_80035AA4[];

void actorScriptStartByIndex(void *, s32);
void camClosestPointOnSegment(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);


void bossKRoolTinyStep(void) {
    BossScriptState *scriptState;
    Actor **minions;
    u8 *scriptOpcodes;
    f32 dummyY;

    scriptState = KROOL_TINY_ACTOR->scriptState;
    minions = KROOL_TINY_ACTOR->minions;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        transitionSetState(0);
        slotQueueSetDisplayMode(2, 0, 1);
        gPrimaryPlayerActor->state = 0x5F;
        gPrimaryPlayerActor->unk155 = 0;
        actorScriptStartByIndex(gPrimaryPlayerActor, 0x4B);
        gCurrentActor->state = 0;
        gCurrentActor->unk155 = 0;
        func_80724DB0(2, 1);
        func_8002FEC0(minions, 0, 0x6D);
        func_8002FEC0(minions, 1, 0x6E);
        func_8002FEC0(minions, 2, 0x6F);
        scriptState->unk12 = 0;
        if (flagGet(0x51, 2)) {
            func_8002FC48(gCurrentActor, 4);
            gCurrentActor->unk15F = 2;
            minions[0]->unk15F = 1;
            scriptState->unk12 = 1;
        }
        if (flagGet(0x52, 2)) {
            func_8002FC48(minions[0], 4);
            minions[0]->unk15F = 2;
            minions[1]->unk15F = 1;
            scriptState->unk12 = 2;
        }
        if (flagGet(0x53, 2)) {
            func_8002FC48(minions[1], 4);
            minions[1]->unk15F = 2;
            minions[2]->unk15F = 1;
            scriptState->unk12 = 3;
        }
        scriptState->phase = 0;
        bossActorGroupCommand(gCurrentActor, 0xF, 0x40E, 0);
    }
    scriptOpcodes = D_80035AA4[scriptState->phase];
    if (gCurrentActor->state) {
        ZoneEntry *p = D_807FDCA0->entries;
        camClosestPointOnSegment(gPrimaryPlayerActor->x, gPrimaryPlayerActor->y, gPrimaryPlayerActor->z, p[0].x, p[0].y, p[0].z, p[1].x, p[1].y, p[1].z, &gPrimaryPlayerActor->x, &dummyY, &gPrimaryPlayerActor->z);
        gPrimaryPlayerActor->yaw = 0xFD2;
        gActivePlayerState->targetSpeed = 150.0f;
    }
    func_8002FDF8(gCurrentActor, scriptState->phase);
    bossActorGroupCommand(gCurrentActor, (1 << scriptState->unk12) & 0xFF, 1, 0);
    switch (gCurrentActor->state) {
    case 0x1F:
        switch (gCurrentActor->unk155) {
        case 0:
            gBehaviourWorkState->timer = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155++;
        case 1:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x37:
        if (gCurrentActor->unk155 == 0) {
            gPrimaryPlayerActor->state = 0x5F;
            gPrimaryPlayerActor->unk155 = 0;
            actorScriptStartByIndex(gPrimaryPlayerActor, 0x4A);
            screenSetTransitionFadeType(1);
            transitionSetState(1);
            mapRequestTransition(0xCE, 0);
            flagSet(scriptState->unk12 + 0x51, 1, 2);
            gCurrentActor->unk155++;
        }
        break;
    case 0:
        func_80724A20();
        break;
    case 1:
        bossActorGroupCommand(gCurrentActor, 0xF, 0x410, 0);
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->unk155 = 0;
        break;
    case 0x27:
        switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->unk155++;
            bossActorGroupCommand(gCurrentActor, 0xF, -1, 0);
            scriptState->unk18[0] = scriptOpcodes[scriptState->scriptPos++];
            scriptState->unk18[1] = scriptOpcodes[scriptState->scriptPos++] + scriptState->unk12 * 10;
            scriptState->unk8[0] = scriptOpcodes[scriptState->scriptPos++];
            if (scriptState->unk18[0] == 0xFF) {
                scriptState->unk18[0] = 8 >> (s32)((gPrimaryPlayerActor->x - 117.0f) / 50.0f);
            }
            bossActorGroupCommand(gCurrentActor, scriptState->unk18[0], 0x413, 0);
            gBehaviourWorkState->timer = 0x14;
            break;
        case 1:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            gCurrentActor->unk155++;
            bossActorGroupCommand(gCurrentActor, scriptState->unk18[0], 0x414, (scriptState->unk18[1] + scriptState->unk12 * 15) & 0xFF);
            gBehaviourWorkState->timer = scriptState->unk8[0];
        case 3:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x28:
        bossActorGroupCommand(gCurrentActor, (1 << scriptState->unk12) & 0xFF, 2, 0);
        if (scriptState->phase == scriptState->unk12 && gCurrentActor->callbackMask == 0) {
            gCurrentActor->state = 0x37;
            gCurrentActor->unk155 = 0;
            break;
        }
        switch (gCurrentActor->unk155) {
        case 0:
            gBehaviourWorkState->timer = scriptOpcodes[scriptState->scriptPos++];
            bossActorGroupCommand(gCurrentActor, (1 << scriptState->unk12) & 0xFF, 0x411, 0);
            gCurrentActor->unk155++;
            break;
        case 1:
        case 2:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                if (gCurrentActor->unk155 == 1 && gCurrentActor->callbackMask) {
                    bossActorGroupCommand(gCurrentActor, (1 << scriptState->unk12) & 0xFF, 0x412, 0);
                }
                gBehaviourWorkState->timer = 10;
                gCurrentActor->unk155++;
            }
            break;
        case 3:
            if (gCurrentActor->callbackMask == 0) {
                scriptState->phase++;
                scriptState->scriptPos = 0;
                scriptOpcodes = D_80035AA4[scriptState->phase];
            }
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x29:
        switch (gCurrentActor->unk155) {
        case 0:
            break;
        }
        break;
    default:
        bossScriptStep(scriptOpcodes, 0, 0);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bossKRoolTinyUpdateMinion(void) {
    BossKRoolTinyActor *leader;
    BossScriptState *leaderState;
    s32 scaleVal;

    leader = (BossKRoolTinyActor *)gCurrentActor->parentActor;
    leaderState = leader->scriptState;
    if (!(gCurrentActor->flags & 0x10)) {
        func_80724DB0(2, 1);
    }
    scaleVal = (gCurrentActor->unk15F == 1) ? leaderState->phase : 0;
    func_8002FDF8(leader, (u8)scaleVal);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368C0.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368E4.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_800368F8.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036910.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036950.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/B100/D_80036968.s")
