#include "common.h"
#include "boss.h"
#include "actor.h"
#include "sched.h"
#include "proto/boss/3840.h"
#include "proto/boss/B100.h"
#include "proto/global/10E1D0_screen_transition.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2C910.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/42630_cutscene_interp.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/8CA50_anim_list.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/A7710_countdown_timer.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/F56F0_player_weapon.h"
#include "proto/global/FCCD0_slot_queue.h"

extern const u8 D_800368C0[34];
extern const u8 D_800368E4[20];
extern const u8 D_800368F8[21];
extern const u8 D_80036910[64];
extern const u8 D_80036950[24];
extern const u8 D_80036968[24];

const u8 *gDogadonPhaseScripts[5] = { D_800368C0, D_800368E4, D_800368F8, D_80036910, D_800368C0 };
const u8 *gKRoolTinyPhaseScripts[4] = { D_80036950, D_80036968, D_80036950, D_80036968 };

// K. Rool (Tiny phase) actor: component 2 (0x178) is the script state, component 3 (0x17C) the
// array of the three actors spawned by bossKRoolTinySpawnMinion (group members 1-3; the leader is member 0).
typedef struct BossKRoolTinyActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
    /* 0x17C */ Actor **minions;
} BossKRoolTinyActor;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;

extern Actor *gPrimaryPlayerActor;

// Dogadon actor: component 2 (0x178) is the script state.
typedef struct BossDogadonActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
} BossDogadonActor;

extern PlayerStruct *gPlayerSlots;

#define DOGADON_ACTOR ((BossDogadonActor *)gCurrentActor)

void bossDogadonStep(void) {
    BossScriptState *scriptState;
    const u8 *scriptOpcodes;
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
        actorAllocBoneRotations(2, 1);
        gCurrentActor->state = 0x1E;
        gCurrentActor->subState = 0;
        if (flagGet(0x54, 2) != 0) {
            scriptState->phase = 4;
            gCurrentActor->state = 0x37;
            gCurrentActor->subState = 0;
        } else if (flagGet(0x53, 2) != 0) {
            scriptState->phase = 3;
        } else if (flagGet(0x52, 2) != 0) {
            scriptState->phase = 2;
        } else if (flagGet(0x51, 2) != 0) {
            scriptState->phase = 1;
        }
        if (scriptState->phase != 0 && gCurrentActor->state != 0x37) {
            gCurrentActor->state = 0x31;
            gCurrentActor->subState = 0;
            zoneEntryGetPosition(1, 0, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
        }
    }
    scriptOpcodes = gDogadonPhaseScripts[scriptState->phase];
    bossRoundFrame(scriptOpcodes);
    switch (gCurrentActor->state) {
    case 0x28:
        if (gActorGlobalState.bossFightPhase == 5 && gPlayerSlots->sizeMode != 1) {
            gCurrentActor->collisionMode = 1;
            gPrimaryPlayerActor->collisionMode = 1;
            camStartPath(0, 2, 1);
            gCurrentActor->state = 0x29;
            hudCountdownTimerSaveElapsed(gCurrentActor->parentActor);
            screenSetTransitionFadeType(1);
            transitionSetState(1);
            mapRequestTransition(0xD6, 0);
            gPrimaryPlayerActor->x = mathSinF(gCurrentActor->yaw + 0x320) * 30.0 + gCurrentActor->x;
            gPrimaryPlayerActor->z = mathCosF(gCurrentActor->yaw + 0x320) * 30.0 + gCurrentActor->z;
            offsetSin = mathSinF(gCurrentActor->yaw + 0x384);
            playerWaypointPathStartLineFromActor(gPrimaryPlayerActor, offsetSin * 15.0f + gCurrentActor->x, mathCosF(gCurrentActor->yaw + 0x384) * 15.0f + gCurrentActor->z, 0x50);
        } else {
            switch (gCurrentActor->subState) {
            case 0:
                if (scriptState->loopPos != 0) {
                    csSendActorMessagePayload(0, 0);
                }
                actorScriptStart(gCurrentActor, 0x3FF);
                gBehaviourWorkState->timer = scriptOpcodes[scriptState->scriptPos++] * 0x1E;
                gCurrentActor->subState++;
                break;
            case 1:
                if (gBehaviourWorkState->timer != 0) {
                    gBehaviourWorkState->timer--;
                } else {
                    actorScriptStart(gCurrentActor, 0x400);
                    gCurrentActor->subState++;
                }
                break;
            case 3:
                if (gPlayerSlots->sizeMode != 1) {
                    playerSetSizeMode(gPrimaryPlayerActor, 1);
                }
                csSendActorMessagePayload(0, 0xFF);
                actorScriptStart(gCurrentActor, 0x3E4);
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
                break;
            }
        }
        break;
    case 0x27:
        actorMoveWithinZone(0, 0.0f, 0.0f, 0x4310, 0.0f);
        switch (gCurrentActor->subState) {
        case 0:
            actorSetTargetSpeed(gCurrentActor, 0);
            scriptState->byteVars[0] = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->subState++;
            /* fallthrough */
        case 1:
            gBehaviourWorkState->timer = 4;
            actorScriptStart(gCurrentActor, 0x3E7);
            gCurrentActor->subState++;
            break;
        case 2:
            gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D(gBehaviourZone->entries->x, gBehaviourZone->entries->z, gCurrentActor->x, gCurrentActor->z), 10.0f);
            break;
        case 3:
            if (gBehaviourWorkState->timer != 0 && gFrameCounter % 5 == 0) {
                projectileSpawnWithShockwave(0xB8, 0.14f, 0x64, 0xFF, 150, 3, scriptState->phase * 0.01 + 1.04, 0.0f, 0.0f, 0.0f);
                if (gBehaviourWorkState->timer-- < 4) {
                    gSpawnedActor->yawSpeed = 0;
                } else {
                    sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x25A, 0xFF, 0x7F, 1, 0, 0.3f, 0);
                }
                controllerAnimSetStateIfChanged(gSpawnedActor, 0x4F9, 0.0f, 0.0f);
                scriptSetActorRampTarget(gSpawnedActor, 0.5f, 0.0f);
            } else if (gBehaviourWorkState->timer == 0) {
                gBehaviourWorkState->timer = scriptState->byteVars[0];
                gCurrentActor->subState++;
            }
            break;
        case 4:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                actorSetTargetSpeed(gCurrentActor, gBehaviourExtraState->targetSpeed);
                actorScriptStart(gCurrentActor, 0x3E4);
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
            }
            break;
        }
        break;
    case 0x1E:
        scriptState->phase = 0;
        scriptState->scriptPos = 0;
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->subState = 0;
        gCurrentActor->speedXZ = gBehaviourExtraState->targetSpeed;
        break;
    case 0:
        switch (gCurrentActor->subState) {
        case 0:
            actorScriptStart(gCurrentActor, 0x3EA);
            gCurrentActor->subState++;
            break;
        case 2:
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->subState = 0;
            break;
        }
        break;
    case 0x31:
        switch (gCurrentActor->subState) {
        case 0:
            playerSetSizeMode(gPrimaryPlayerActor, 0);
            playerSetSizeMode(gPrimaryPlayerActor, 1);
            camStartPath(gCurrentActor, 1, 1);
            actorScriptStart(gCurrentActor, 0x3FB);
            gCurrentActor->subState++;
            break;
        case 2:
            actorScriptStart(gCurrentActor, 0x3E4);
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->subState = 0;
            break;
        }
        break;
    case 0x37:
        switch (gCurrentActor->subState) {
        case 0:
            actorScriptStart(gCurrentActor, 0);
            camStartPath(gCurrentActor, 0x15, 1);
            gCurrentActor->subState++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                screenSetTransitionFadeType(0);
                mapRequestTransition(0xCF, 0);
                gCurrentActor->subState++;
            }
            break;
        }
        break;
    default:
        bossScriptStep(scriptOpcodes, 0x10, 0.0f);
        break;
    }
    behaviourUpdateShadowAlpha();
    if (currentActorAnimTryIdleVariant(0, &gBehaviourWorkState->idleAnimFrame) != 0) {
        currentActorAnimTryIdleVariant(0x81, &gBehaviourWorkState->idleAnimFrame);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


void bossKRoolTinyPulseBones(scaleFactor)
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
void bossFreezeAnimAtFrame(actor, frame)
Actor *actor;
u8 frame;
{
    animSetLoopLimit(actor, 0, 1);
    animSetFinished(actor, 0, 1);
    animSetFrameAndSubframe(actor, 0, frame, 0.0f);
}

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


void bossKRoolTinyCommonStep(void *leader, u8 scaleVal) {
    s32 finalScale;
    s32 animFrame;

    if (gCurrentActor->stageStatus == 2) {
        finalScale = 4;
    } else {
        finalScale = scaleVal;
    }
    bossKRoolTinyPulseBones(finalScale & 0xFF);
    if (gActorGlobalState.bossFightPhase == 4) {
        bossActorGroupCommand(leader, 0xF, 0, 0);
        animFrame = (0xA - gCurrentActor->health) & 0xFF;
        bossFreezeAnimAtFrame(gCurrentActor, animFrame);
        actorScriptStart(gCurrentActor, 0x415);
    }
    if (gActorGlobalState.bossFightPhase == 5 || gActorGlobalState.bossFightPhase == 4) {
        sfxPlayAtFBD6CPosition();
    }
}

void bossKRoolTinySpawnMinion(Actor **minions, u8 slotIndex, s32 modelId) {
    actorSpawn(0xE5, modelId);
    actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, gCurrentActor->sub4->scaleY);
    gSpawnedActor->flags |= 0x1400;
    gSpawnedActor->parentActor = gCurrentActor;
    gSpawnedActor->collisionMode = gCurrentActor->collisionMode;
    gSpawnedActor->flags = gCurrentActor->flags;
    minions[slotIndex] = gSpawnedActor;
}


#define KROOL_TINY_ACTOR ((BossKRoolTinyActor *)gCurrentActor)

extern PlayerState *gActivePlayerState;

void bossKRoolTinyStep(void) {
    BossScriptState *scriptState;
    Actor **minions;
    const u8 *scriptOpcodes;
    f32 dummyY;

    scriptState = KROOL_TINY_ACTOR->scriptState;
    minions = KROOL_TINY_ACTOR->minions;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        transitionSetState(0);
        slotQueueSetDisplayMode(2, 0, 1);
        gPrimaryPlayerActor->state = 0x5F;
        gPrimaryPlayerActor->subState = 0;
        actorScriptStartByIndex(gPrimaryPlayerActor, 0x4B);
        gCurrentActor->state = 0;
        gCurrentActor->subState = 0;
        actorAllocBoneScales(2, 1);
        bossKRoolTinySpawnMinion(minions, 0, 0x6D);
        bossKRoolTinySpawnMinion(minions, 1, 0x6E);
        bossKRoolTinySpawnMinion(minions, 2, 0x6F);
        scriptState->stagesDone = 0;
        if (flagGet(0x51, 2)) {
            bossFreezeAnimAtFrame(gCurrentActor, 4);
            gCurrentActor->stageStatus = 2;
            minions[0]->stageStatus = 1;
            scriptState->stagesDone = 1;
        }
        if (flagGet(0x52, 2)) {
            bossFreezeAnimAtFrame(minions[0], 4);
            minions[0]->stageStatus = 2;
            minions[1]->stageStatus = 1;
            scriptState->stagesDone = 2;
        }
        if (flagGet(0x53, 2)) {
            bossFreezeAnimAtFrame(minions[1], 4);
            minions[1]->stageStatus = 2;
            minions[2]->stageStatus = 1;
            scriptState->stagesDone = 3;
        }
        scriptState->phase = 0;
        bossActorGroupCommand(gCurrentActor, 0xF, 0x40E, 0);
    }
    scriptOpcodes = gKRoolTinyPhaseScripts[scriptState->phase];
    if (gCurrentActor->state) {
        ZoneEntry *p = gBehaviourZone->entries;
        camClosestPointOnSegment(gPrimaryPlayerActor->x, gPrimaryPlayerActor->y, gPrimaryPlayerActor->z, p[0].x, p[0].y, p[0].z, p[1].x, p[1].y, p[1].z, &gPrimaryPlayerActor->x, &dummyY, &gPrimaryPlayerActor->z);
        gPrimaryPlayerActor->yaw = 0xFD2;
        gActivePlayerState->targetSpeed = 150.0f;
    }
    bossKRoolTinyCommonStep(gCurrentActor, scriptState->phase);
    bossActorGroupCommand(gCurrentActor, (1 << scriptState->stagesDone) & 0xFF, 1, 0);
    switch (gCurrentActor->state) {
    case 0x1F:
        switch (gCurrentActor->subState) {
        case 0:
            gBehaviourWorkState->timer = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->subState++;
        case 1:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
            }
            break;
        }
        break;
    case 0x37:
        if (gCurrentActor->subState == 0) {
            gPrimaryPlayerActor->state = 0x5F;
            gPrimaryPlayerActor->subState = 0;
            actorScriptStartByIndex(gPrimaryPlayerActor, 0x4A);
            screenSetTransitionFadeType(1);
            transitionSetState(1);
            mapRequestTransition(0xCE, 0);
            flagSet(scriptState->stagesDone + 0x51, 1, 2);
            gCurrentActor->subState++;
        }
        break;
    case 0:
        volumeTriggerApplyActorState();
        break;
    case 1:
        bossActorGroupCommand(gCurrentActor, 0xF, 0x410, 0);
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->subState = 0;
        break;
    case 0x27:
        switch (gCurrentActor->subState) {
        case 0:
            gCurrentActor->subState++;
            bossActorGroupCommand(gCurrentActor, 0xF, -1, 0);
            scriptState->byteVars[0] = scriptOpcodes[scriptState->scriptPos++];
            scriptState->byteVars[1] = scriptOpcodes[scriptState->scriptPos++] + scriptState->stagesDone * 10;
            scriptState->vars[0] = scriptOpcodes[scriptState->scriptPos++];
            if (scriptState->byteVars[0] == 0xFF) {
                scriptState->byteVars[0] = 8 >> (s32)((gPrimaryPlayerActor->x - 117.0f) / 50.0f);
            }
            bossActorGroupCommand(gCurrentActor, scriptState->byteVars[0], 0x413, 0);
            gBehaviourWorkState->timer = 0x14;
            break;
        case 1:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->subState++;
            }
            break;
        case 2:
            gCurrentActor->subState++;
            bossActorGroupCommand(gCurrentActor, scriptState->byteVars[0], 0x414, (scriptState->byteVars[1] + scriptState->stagesDone * 15) & 0xFF);
            gBehaviourWorkState->timer = scriptState->vars[0];
        case 3:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
            }
            break;
        }
        break;
    case 0x28:
        bossActorGroupCommand(gCurrentActor, (1 << scriptState->stagesDone) & 0xFF, 2, 0);
        if (scriptState->phase == scriptState->stagesDone && gCurrentActor->callbackMask == 0) {
            gCurrentActor->state = 0x37;
            gCurrentActor->subState = 0;
            break;
        }
        switch (gCurrentActor->subState) {
        case 0:
            gBehaviourWorkState->timer = scriptOpcodes[scriptState->scriptPos++];
            bossActorGroupCommand(gCurrentActor, (1 << scriptState->stagesDone) & 0xFF, 0x411, 0);
            gCurrentActor->subState++;
            break;
        case 1:
        case 2:
            if (gBehaviourWorkState->timer) {
                gBehaviourWorkState->timer--;
            } else {
                if (gCurrentActor->subState == 1 && gCurrentActor->callbackMask) {
                    bossActorGroupCommand(gCurrentActor, (1 << scriptState->stagesDone) & 0xFF, 0x412, 0);
                }
                gBehaviourWorkState->timer = 10;
                gCurrentActor->subState++;
            }
            break;
        case 3:
            if (gCurrentActor->callbackMask == 0) {
                scriptState->phase++;
                scriptState->scriptPos = 0;
                scriptOpcodes = gKRoolTinyPhaseScripts[scriptState->phase];
            }
            gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
            gCurrentActor->subState = 0;
            break;
        }
        break;
    case 0x29:
        switch (gCurrentActor->subState) {
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
        actorAllocBoneScales(2, 1);
    }
    scaleVal = (gCurrentActor->stageStatus == 1) ? leaderState->phase : 0;
    bossKRoolTinyCommonStep(leader, (u8)scaleVal);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

const u8 D_800368C0[34] = {
    0x00, 0x54, 0x6C, 0x51, 0x03, 0xE4, 0x41, 0x01, 0x27, 0x3C, 0x41, 0x02, 0x27, 0x00, 0x28, 0x01,
    0x00, 0x51, 0x03, 0xE4, 0x4F, 0x4B, 0x01, 0x04, 0x27, 0x1E, 0x4B, 0x01, 0x04, 0x27, 0x1E, 0x28,
    0x0C, 0x50,
};

const u8 D_800368E4[20] = {
    0x6C, 0x4F, 0x4B, 0x01, 0x04, 0x27, 0x14, 0x4B, 0x01, 0x04, 0x27, 0x14, 0x4B, 0x01, 0x04, 0x27,
    0x00, 0x28, 0x0A, 0x50,
};

const u8 D_800368F8[21] = {
    0x6C, 0x4F, 0x41, 0x01, 0x27, 0x0F, 0x41, 0x03, 0x27, 0x0F, 0x41, 0x02, 0x27, 0x0F, 0x41, 0x04,
    0x27, 0x00, 0x28, 0x0A, 0x50,
};

const u8 D_80036910[64] = {
    0x6C, 0x4F, 0x4B, 0x01, 0x04, 0x27, 0x0A, 0x27, 0x0A, 0x67, 0x01, 0x04, 0x27, 0x0A, 0x27, 0x0A,
    0x67, 0x01, 0x04, 0x27, 0x00, 0x28, 0x0A, 0x50, 0x4F, 0x27, 0x01, 0x50, 0x0A, 0x27, 0xFF, 0x50,
    0x0A, 0x27, 0xFF, 0x50, 0x0A, 0x27, 0xFF, 0x50, 0x0A, 0x28, 0x50, 0x50, 0x4F, 0x27, 0xFF, 0x5A,
    0x0A, 0x27, 0xFF, 0x5A, 0x0A, 0x27, 0x05, 0x5A, 0x0A, 0x27, 0x0A, 0x5A, 0x0A, 0x28, 0x46, 0x50,
};

const u8 D_80036950[24] = {
    0x4F, 0x27, 0x05, 0x78, 0x0A, 0x27, 0x0A, 0x78, 0x0A, 0x27, 0xFF, 0x78, 0x0A, 0x27, 0x09, 0x78,
    0x0A, 0x27, 0x06, 0x78, 0x0A, 0x28, 0x3C, 0x50,
};

const u8 D_80036968[24] = {
    0x4F, 0x27, 0x0C, 0x78, 0x0A, 0x27, 0x03, 0x78, 0x0A, 0x27, 0x0A, 0x78, 0x0A, 0x27, 0xFF, 0x78,
    0x0A, 0x27, 0x05, 0x78, 0x0A, 0x28, 0x32, 0x50,
};
