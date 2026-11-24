#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "cutscene.h"
#include "sched.h"
#include "model.h"
#define PROTO_SKIP_hudSpawnCountdownTimer // ORIG: hides the 3-parameter prototype; the target passes a fourth argument (a3 = &gCsCountdown at 0x2600/0x2604 into jal 0x261c), see the declaration in front of csCmdExec
#define PROTO_SKIP_modelAnimEntrySetUnkC // ORIG: hides the (s16, s16, s16) prototype; the target passes h without call-site narrowing into jal 0x29e0, see the declaration in front of csCmdExec
#define PROTO_SKIP_effectSetDepth // ORIG: hides the u8 prototype; the target loads li a0,1 at 0x51cc, see the s8 declaration below
#include "proto/global/10130_demo_playback.h"
#include "proto/global/104F0_eeprom.h"
#include "proto/global/10E1D0_screen_transition.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
#include "proto/global/127B00_path_playback.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/1332B0_volume_trigger.h"
#include "proto/global/133A90_prox_path.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2F550_map_render.h"
#include "proto/global/36880_model_slot.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/42630_cutscene_interp.h"
#include "proto/global/478F0_cutscene_cmds.h"
#include "proto/global/54150_model_anim.h"
#include "proto/global/55B20_map_chunk.h"
#include "proto/global/5E020_hash_table.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/63810_light_queue.h"
#include "proto/global/63EC0_effect_water.h"
#include "proto/global/6AD90_collision.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/8D3E0_actor_list.h"
#include "proto/global/8F4B0.h"
#include "proto/global/A7710_countdown_timer.h"
#include "proto/global/CC800_player_setup.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/F9450_grid_nodes.h"
#include "proto/global/FCCD0_slot_queue.h"
void effectSetDepth(s8); // ORIG: csCmdSpawnSparkAndLight loads the argument with li a0,1 at 0x51cc; the shared u8 prototype gives andi a0,s4,0xff there; owner 119370 stores a0 with sb at 0x354 (type-blind) and an s8 or s32 owner breaks 478F0/80150/89250/9DD70

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

typedef struct CsTimer {
    /* 0x0 */ s16 timerId;
    /* 0x2 */ s16 modelIndex;
    /* 0x4 */ s16 value;
    /* 0x6 */ u8 active;
    /* 0x7 */ u8 pad7;
} CsTimer;

typedef struct CsSpawnReq {
    /* 0x0 */ Actor *timerActor;
    /* 0x4 */ Actor *hostActor;
    /* 0x8 */ u8 active;
} CsSpawnReq;

CsCmdFunc gCsCmdTable[118] = {
    /* 0x00 */ csCmdVarAdd,
    /* 0x01 */ csCmdCopyTargetPosSub10,
    /* 0x02 */ csCmdVarIncrement,
    /* 0x03 */ csCmdStoreAttachLocalPos,
    /* 0x04 */ csCmdDecayTargetPosCoord,
    /* 0x05 */ csCmdRotXAdjust,
    /* 0x06 */ csCmdTransformSave,
    /* 0x07 */ csCmdTransformRestore,
    /* 0x08 */ csCmdVarSlotDelta,
    /* 0x09 */ csCmdSpawnSparkAndLight,
    /* 0x0A */ csCmdSpawnFixedNodeEffects,
    /* 0x0B */ csCmdSpawnSparksAtNodes,
    /* 0x0C */ csCmdFlickerLight,
    /* 0x0D */ csCmdBouncePos,
    /* 0x0E */ csCmdPeriodicNodeEffect,
    /* 0x0F */ csCmdBobbingLights,
    /* 0x10 */ csCmdSpawnFourNodeEntries,
    /* 0x11 */ csCmdPointCycleEffect,
    /* 0x12 */ csCmdStepSequenceProgress,
    /* 0x13 */ csCmdCamShakeOnAnim,
    /* 0x14 */ csCmdPlayAnimSlot1,
    /* 0x15 */ csCmdLookupSlotKey,
    /* 0x16 */ csCmdSetParam49,
    /* 0x17 */ csCmdModelStepAnimation,
    /* 0x18 */ csCmdSetModelSlotByte5F,
    /* 0x19 */ csCmdSpawnBurstAtNodeOrPos,
    /* 0x1A */ csCmdPlayAnimSlotB,
    /* 0x1B */ csCmdAllocAnimTracking,
    /* 0x1C */ csCmdSfxOnAnimChange,
    /* 0x1D */ csCmdPeriodicEffectPair,
    /* 0x1E */ csCmdLightPulse,
    /* 0x1F */ csCmdPeriodicSfxAlloc,
    /* 0x20 */ csCmdCountdownTimer,
    /* 0x21 */ csCmdNodeSpotLight,
    /* 0x22 */ csCmdStormLightningRain,
    /* 0x23 */ csCmdSpawnParticleTrail,
    /* 0x24 */ csCmdSetCeilAndFloorAtPos,
    /* 0x25 */ csCmdPosFromNode,
    /* 0x26 */ csCmdSpawnEffectAtNode,
    /* 0x27 */ csCmdAnimProgressFromCounter,
    /* 0x28 */ csCmdAnimProgressFromHubItems,
    /* 0x29 */ csCmdSplineLights,
    /* 0x2A */ csCmdNodeSpotLightFov,
    /* 0x2B */ csCmdSpawnRandomEffectAtPos,
    /* 0x2C */ csCmdNop,
    /* 0x2D */ csCmdFindSlotIdMatch,
    /* 0x2E */ csCmdSlotQueueSelectPlayer,
    /* 0x2F */ csCmdPeriodicPointEffect,
    /* 0x30 */ csCmdSineMotionUpdate,
    /* 0x31 */ csCmdBeatSyncAnimation,
    /* 0x32 */ csCmdRandomPointEffects,
    /* 0x33 */ csCmdGroundPointEffect,
    /* 0x34 */ csCmdStepLightColor,
    /* 0x35 */ csCmdSpawnMultiRingParticles,
    /* 0x36 */ csCmdAnimStepInterpolate,
    /* 0x37 */ csCmdChanceNodeEffect,
    /* 0x38 */ csCmdSpawnEffectsAtNodeRange,
    /* 0x39 */ csCmdSetCartDamage,
    /* 0x3A */ csCmdFindNearestActorToCamera,
    /* 0x3B */ csCmdStepCameraFrac,
    /* 0x3C */ csCmdTagBarrelSpawnSmokeAndPuffs,
    /* 0x3D */ csCmdAllocSlotPointer,
    /* 0x3E */ csCmdPeriodicSfx,
    /* 0x3F */ csCmdNodeTargetLights,
    /* 0x40 */ csCmdExtraObjectAttach,
    /* 0x41 */ csCmdPeriodicProximityEffects,
    /* 0x42 */ csCmdSeqMatchPattern5,
    /* 0x43 */ csCmdPatternBufferMatch,
    /* 0x44 */ csCmdPointHitEffectSpawn,
    /* 0x45 */ csCmdSpawnDirectionalEffects,
    /* 0x46 */ csCmdSpawnScaledSphereEffects,
    /* 0x47 */ csCmdSpawnModelNodeEffects,
    /* 0x48 */ csCmdResolveNodePair,
    /* 0x49 */ csCmdGetModelNodeAndProject,
    /* 0x4A */ csCmdSpawnRandomJitterEffects,
    /* 0x4B */ csCmdSpawnEffectAtRandomNode,
    /* 0x4C */ csCmdPointListEffect,
    /* 0x4D */ csCmdSeqMatchPattern4,
    /* 0x4E */ csCmdSpawnFallingSparkles,
    /* 0x4F */ csCmdSeqMatchPattern3,
    /* 0x50 */ csCmdSpawnTumbleBounceRing,
    /* 0x51 */ csCmdSeqMatchPattern4B,
    /* 0x52 */ csCmdPeriodicIntervalEffects,
    /* 0x53 */ csCmdSpawnBurstColoredLights,
    /* 0x54 */ csCmdSpawnOrbitingPuffs,
    /* 0x55 */ csCmdSpawnPointParticles,
    /* 0x56 */ csCmdRandomizeCutsceneTimer,
    /* 0x57 */ csCmdBlinkNodeFrames,
    /* 0x58 */ csCmdEnableEffectNodes5And6,
    /* 0x59 */ csCmdResetEffectNodes5And6,
    /* 0x5A */ csCmdEffectNodeStepAlpha,
    /* 0x5B */ csCmdSlotQueuePurchaseFlag,
    /* 0x5C */ csCmdSpawnDustPuffs,
    /* 0x5D */ csCmdCameraLookAtMatrixUpdate,
    /* 0x5E */ csCmdSpawnOrbitingSparks,
    /* 0x5F */ csCmdSpawnSphereEffects,
    /* 0x60 */ csCmdSpawnPuffBurst,
    /* 0x61 */ csCmdSpawnEffectsAtPos,
    /* 0x62 */ csCmdHubWorldItemsAdjust,
    /* 0x63 */ csCmdInterpolateFloatPair,
    /* 0x64 */ csCmdCameraShakeOnModelAnim,
    /* 0x65 */ csCmdSpawnSparksOnModelAnim,
    /* 0x66 */ csCmdSpawnPuffsOnModelAnim,
    /* 0x67 */ csCmdPlayerProximityPointCheck,
    /* 0x68 */ csCmdSfxFadeLoop,
    /* 0x69 */ csCmdSpawnActorAtPoint,
    /* 0x6A */ csCmdSetSpawnRespawnHold,
    /* 0x6B */ csCmdEnemyGridCellSet,
    /* 0x6C */ csCmdSpawnFallingWhiteSparks,
    /* 0x6D */ csCmdStepMultiModelAnimations,
    /* 0x6E */ csCmdSpawnRandomNodeParticles,
    /* 0x6F */ csCmdSpawnActorNodeByCase,
    /* 0x70 */ csCmdFreeModelSlotIndex,
    /* 0x71 */ csCmdSumFlagsE6ThroughEA,
    /* 0x72 */ csCmdSetPositionPreset,
    /* 0x73 */ csCmdShowRemainingDigits,
    /* 0x74 */ csCmdCameraVectorTargetUpdate,
    /* 0x75 */ csCmdSetFlag1C1Or1C2,
};
typedef s32 (*CsCondFunc)(CsState *, s16, s16, s16);
CsCondFunc gCsCondTable[19] = {
    /* 0x00 */ (CsCondFunc)csCondVarLess, // u8 return
    /* 0x01 */ csCondSyncActorAnim,
    /* 0x02 */ (CsCondFunc)csCondCollectedSufficientItems, // u8 return
    /* 0x03 */ (CsCondFunc)csCondActorFacingPos, // u8 return
    /* 0x04 */ csCondFlags82Or83,
    /* 0x05 */ (CsCondFunc)csCondCheckSlotMapIndex, // u8 return
    /* 0x06 */ (CsCondFunc)csCondCheckFrameTimingMap, // u8 return
    /* 0x07 */ (CsCondFunc)csCondCheckKongItems, // u8 return
    /* 0x08 */ csCondFindPlayerSlotByModel,
    /* 0x09 */ (CsCondFunc)csCondKongHasHubItems, // u8 return
    /* 0x0A */ (CsCondFunc)csCondIsMpGameMode5, // u8 return
    /* 0x0B */ csCondDepositItem,
    /* 0x0C */ (CsCondFunc)csCondAudioFlag, // u8 return
    /* 0x0D */ (CsCondFunc)csCondTrue, // u8 return
    /* 0x0E */ csCondCheckAllKongs,
    /* 0x0F */ (CsCondFunc)csCondWorldHubFlagSet, // u8 return
    /* 0x10 */ (CsCondFunc)csCondCountFlags261Ge4, // u8 return
    /* 0x11 */ csCondPlayerNearFixedPoint,
    /* 0x12 */ (CsCondFunc)csCondActorInFront, // u8 return
};
s8 gCsSfxNode = 0;
s16 D_80748098 = 7; // unreferenced
s16 gHubWorldMaps[8] = { 7, 0x26, 0x1A, 0x1E, 0x30, 0x48, 0x57, 0 };
s16 gHubWorldExits[8] = { 0xF, 0, 0, 0, 0x1B, 0, 0, 0 };
s16 gHubWorldFlags[8] = { 0x1B, 0x5F, 0x8C, 0xC2, 0x101, 0x11A, 0x15D, 0 };

// .bss 0x807F61B0-0x807F6940
CsTimer gCsTimerQueue[8];
CsSpawnReq gCsCountdown;
f32 gCsPrevPosX;
f32 gCsPrevPosY;
f32 gCsPrevPosZ;
f32 gCsPrevRotX;
f32 gCsPrevRotY;
f32 gCsPrevRotZ;
f32 gCsPrevScale;
f32 gCsPrevGroundOffset;
f32 gCsPosX;
f32 gCsPosY;
f32 gCsPosZ;
f32 gCsRotX;
f32 gCsRotY;
f32 gCsRotZ;
f32 gCsScale;
f32 gCsGroundOffset;
s32 D_807F623C;
s16 gCsModelIds[600];
u8 gCsVarsDirty[0x212];
s8 gCsInvulnerable;
u8 gCsCondFlag;
s16 gCsGroundUpdatePending;
s16 gCsShakeInnerRadius;
s16 gCsShakeOuterRadius;
s16 D_807F690A;
f32 gCsSpawnX;
f32 gCsSpawnY;
f32 gCsSpawnZ;
s16 gCsTrackedModels[16];
u8 gCsTrackedModelCount;
u8 D_807F6939;
s16 gCsLightIndex;
s16 gCsCamPathLockFlag;
u8 gCsFlagBits;
u8 gCsCamUseGlobalPaths;

void csModelIdTableReset(void) {
    s32 i = 0;
    s32 j;

    do {
        gCsModelIds[i] = -1;
        i++;
    } while (&gCsModelIds[i] < &gCsModelIds[600]); // ORIG: ordered end-address exit test, sltu at,v1,a0 at 0x18 against a0 = gCsModelIds + 1200 (0x4/0x8), not unrolled; every literal index bound (i < 600, i != 600, for/while) unrolls 4x with bne (Q1629, Q0765)
    for (j = 0; j < 0x212; j++) { gCsVarsDirty[j] = 0; } // LAYOUT: one-line loop keeps the as1 unroll schedule (Q0364)
}

extern ModelSlot *gModelSlots;

s16 csModelSlotGetTableIndex(s16 modelId) {
    return gModelSlots[hashTableLookup(modelId)].csModelId;
}

s16 csModelIdTableAlloc(s16 modelId, u8 isLowTable) {
    s32 i;

    if (isLowTable == 0) {
        i = 0x226;
    } else {
        i = 0;
    }
    while (gCsModelIds[i] != -1) {
        i++;
    }
    gCsModelIds[i] = modelId;
    return i;
}


void csModelStateSetFirstByte(s16 modelIndex, s16 val) {
    csModelStateSetByte(modelIndex, val, 0);
}

void csModelStateSetByte(s16 modelIndex, s16 val, s16 byteOffset) {
    s16 slot;

    slot = hashTableLookup(gCsModelIds[modelIndex]);
    if (slot != -1) {
        gModelSlots[slot].csState->stateBytes[byteOffset] = val;
        gModelSlots[slot].csState->updateMode = 1;
    }
}

void csTimerQueueClear(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        gCsTimerQueue[i].active = 0;
    }
}

void csTimerQueueAdd(s16 timerId, s16 modelIndex, s16 val) {
    s16 i = 0;
    s32 found = 0;

    while (!found && i < 8) {
        if (gCsTimerQueue[i].active == 0) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found) {
        gCsTimerQueue[i].active = 1;
        gCsTimerQueue[i].timerId = timerId;
        gCsTimerQueue[i].modelIndex = modelIndex;
        gCsTimerQueue[i].value = val;
    }
}

void csTimerQueueFire(s16 timerId) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gCsTimerQueue[i].active != 0 && gCsTimerQueue[i].timerId == timerId) {
            csModelStateSetFirstByte(gCsTimerQueue[i].modelIndex, gCsTimerQueue[i].value);
            gCsTimerQueue[i].active = 0;
        }
    }
}


void csScriptLoad(s16 *scriptData) {
    s16 modelCount;
    s16 *p;
    s32 slot;
    s16 modelIndex;
    s16 nodeCount;
    s16 condCount;
    s16 cmdCount;
    s32 condLen;
    s32 cmdLen;
    CsNode **tail;
    CsNode *node;

    modelCount = *scriptData;
    p = scriptData + 1;
    while (modelCount != 0) {
        modelIndex = *p;
        p++;
        slot = hashTableLookup(gCsModelIds[modelIndex]);
        if (slot != -1) {
            gModelSlots[slot].csState = heapAlloc(sizeof(CsState));
            csStateInit(gModelSlots[slot].csState);
            gModelSlots[slot].csState->nodes = NULL;
            nodeCount = p[0];
            tail = &gModelSlots[slot].csState->nodes;
            gModelSlots[slot].csState->unk9C = p[1];
            p += 2;
            while (nodeCount != 0) {
                node = heapAlloc(sizeof(CsNode));
                *tail = node;
                node->next = NULL;
                condCount = *p;
                p++;
                condLen = condCount * 4;
                tail = &node->next;
                node->condCount = condCount;
                memcpy(node->conds, p, condLen * 2);
                p += condLen;
                cmdCount = *p;
                p++;
                cmdLen = cmdCount * 4;
                node->cmdCount = cmdCount;
                memcpy(node->cmds, p, cmdLen * 2);
                p += cmdLen;
                nodeCount--;
            }
        } else {
            nodeCount = p[0];
            p += 2;
            while (nodeCount != 0) {
                condCount = *p;
                p++;
                p += condCount * 4;
                cmdCount = *p;
                p++;
                p += cmdCount * 4;
                nodeCount--;
            }
        }
        modelCount--;
    }
    gCsCamUseGlobalPaths = 0;
    gCsFlagBits = 0;
    gCsInvulnerable = 0;
    gCsCondFlag = 0;
    gCsCamPathLockFlag = 0;
    gCsCountdown.timerActor = NULL;
    gCsCountdown.hostActor = NULL;
    gCsCountdown.active = 0;
}


void csStateFree(CsState *cs) {
    CsNode *node;
    CsNode *next;

    if (cs->data != NULL) {
        heapFree(cs->data);
    }
    node = cs->nodes;
    while (node != NULL) {
        next = node->next;
        heapFree(node);
        node = next;
    }
    heapFree(cs);
}

void csStateInit(CsState *cs) {
    s32 i;

    for (i = 0; i < 8; i++) {
        cs->vars[i] = 1.0f;
    }
    cs->sfxSources[0] = -1;
    cs->sfxSources[1] = -1;
    cs->pathHandle = -1;
    cs->data = NULL;
    cs->unk40[0] = 0;
    cs->unk40[1] = 0;
    cs->timers[0] = 0;
    cs->timers[1] = 0;
    cs->stateBytes[0] = 0;
    cs->stateBytes[1] = 0;
    cs->stateBytes[2] = 0;
    cs->nextStateBytes[0] = 0;
    cs->nextStateBytes[1] = 0;
    cs->nextStateBytes[2] = 0;
    cs->transformChanged = 0;
    cs->floorGrabbable = 0;
    cs->pushMode = 0;
    cs->pushContact = 0;
    cs->pushInput = 0;
    cs->prevPushInput = 0;
    cs->pushMinX = 0;
    cs->pushMinZ = 0;
    cs->pushMaxX = 0x7FFF;
    cs->pushMaxZ = 0x7FFF;
    cs->pushArcMin = 0;
    cs->pushArcMax = 0xFFF;
    cs->camPathActor = NULL;
    cs->updateMode = 0;
    cs->hitId = 0;
    cs->collisionRebuildMode = 0;
    cs->contactCallbacks = 1;
    cs->deferredPush = 0;
    cs->alphaTarget = 0;
    cs->alpha = 0;
    cs->alphaOverride = 0;
    cs->alphaStep = 0xFF;
    cs->collisionEnabled = 1;
    cs->floorEnabled = 1;
    cs->runFlags = 0;
    cs->modelFlags = 0;
    cs->lightYOffset = 0;
    cs->alphaStepFrame = 0xFFFFFFFF;
    cs->riderDriftX = 0.0f;
    cs->riderDriftZ = 0.0f;
    cs->rotYDelta = 0.0f;
    cs->unk3C = 0.0f;
    cs->pushSpeed = 0.0f;
    cs->pushSpeedMax = 0.0f;
    cs->pushAccel = 0.0f;
    cs->pushDirX = 0.0f;
    cs->pushDirZ = 0.0f;
}

void csModelStateSetVars(s32 modelIndex, u8 *varsData) {
    s16 slot;

    slot = hashTableLookup(gCsModelIds[modelIndex]);
    if (slot != -1) {
        memcpy(gModelSlots[slot].csState->vars, varsData, 0x20);
        gCsVarsDirty[modelIndex] = 1;
    }
}

void csStateTickTimers(CsState *cs) {
    u8 i;

    for (i = 0; i < 2; i++) {
        if (cs->timers[i] != 0) {
            cs->timers[i]--;
        }
    }
    for (i = 0; i < 3; i++) {
        cs->nextStateBytes[i] = cs->stateBytes[i];
    }
    cs->transformChanged = 0;
}

void csStateUpdate(CsState *cs, s16 csId) {
    CsNode *node;
    s32 i;
    s32 j;
    u8 ok;
    s32 stepped;
    u8 moved;
    u8 rotated;
    u8 scaleXZ;
    u8 scaleY;

    node = cs->nodes;
    if (node != NULL) {
        modelSlotGetTransformVectors(csId, &gCsPrevPosX, &gCsPrevPosY, &gCsPrevPosZ, &gCsPrevRotX, &gCsPrevRotY,
                                     &gCsPrevRotZ, &gCsPrevScale, &gCsPrevGroundOffset, 1);
        modelSlotGetTransformVectors(csId, &gCsPosX, &gCsPosY, &gCsPosZ, &gCsRotX, &gCsRotY,
                                     &gCsRotZ, &gCsScale, &gCsGroundOffset, 1);
        csStateIntegrateMotion(cs);
        gCsGroundUpdatePending = 0;
        gCsShakeOuterRadius = 0x7FFF;
        gCsShakeInnerRadius = gCsShakeOuterRadius;
        gCsSpawnX = gCsPrevPosX;
        gCsSpawnY = gCsPrevPosY;
        gCsSpawnZ = gCsPrevPosZ;
        while (node != NULL) {
            i = 0;
            ok = 1;
            while (i < node->condCount && ok) {
                ok = csCondEval(&node->conds[i], cs, csId);
                i++;
            }
            if (ok) {
                for (j = 0; j < node->cmdCount; j++) {
                    csCmdExec(&node->cmds[j], cs, csId);
                }
            }
            node = node->next;
        }
        stepped = modelSlotStepAnimations(csId);
        if (gCsPrevPosX != gCsPosX || gCsPrevPosY != gCsPosY || gCsPrevPosZ != gCsPosZ ||
            gCsPrevRotX != gCsRotX || gCsPrevRotY != gCsRotY || gCsPrevRotZ != gCsRotZ ||
            gCsPrevScale != gCsScale || stepped != 0) {
            moved = gCsPrevPosX != gCsPosX || gCsPrevPosY != gCsPosY || gCsPrevPosZ != gCsPosZ;
            rotated = gCsPrevRotX != gCsRotX || gCsPrevRotY != gCsRotY || gCsPrevRotZ != gCsRotZ;
            scaleXZ = gCsPrevScale != gCsScale;
            scaleY = gCsPrevGroundOffset != gCsGroundOffset;
            modelSlotTransformBoundsAndNodes(csId, gCsPosX, gCsPosY, gCsPosZ, gCsRotX, gCsRotY, gCsRotZ, gCsScale,
                          gCsGroundOffset, moved, rotated, scaleXZ, scaleY, 1);
            cs->transformChanged = 1;
        }
        if (gCsGroundUpdatePending != 0) {
            modelSlotUpdateGroundCoords(csId, 1);
        }
        csStateEndUpdate(cs);
    }
}


void csStateEndUpdate(CsState *cs) {
    Actor *actor;

    cs->rotYDelta = gCsRotY - gCsPrevRotY;
    cs->stateBytes[0] = cs->nextStateBytes[0];
    cs->stateBytes[1] = cs->nextStateBytes[1];
    cs->stateBytes[2] = cs->nextStateBytes[2];
    cs->prevPushInput = cs->pushInput;
    cs->pushContact = 0;
    cs->pushInput = 0;
    cs->hitId = 0;
    cs->runFlags |= 1;
    if (cs->camPathActor != NULL) {
        actor = cs->camPathActor;
        actor->x = gCsPosX;
        actor->y = gCsPosY;
        actor->z = gCsPosZ;
        actor->yaw = gCsRotY * 4096.0f / 360.0f;
        if (gGlobalPauseFlags & 0x1000) {
            gGlobalPauseFlags &= ~0x1000;
            actorDespawn(cs->camPathActor);
            cs->camPathActor = NULL;
        }
    }
    gCsCamUseGlobalPaths = 0;
}


void csStepAlpha(CsState *cs) {
    s16 target;
    s16 alpha;

    if (gFrameCounter != cs->alphaStepFrame) {
        alpha = cs->alpha;
        target = cs->alphaTarget;
        cs->alphaStepFrame = gFrameCounter;
        if (alpha < target) {
            cs->alpha = alpha + cs->alphaStep;
            if (target < cs->alpha) {
                cs->alpha = target;
            }
        } else {
            cs->alpha = alpha - cs->alphaStep;
            if (cs->alpha < target) {
                cs->alpha = target;
            }
        }
    }
}

void csStateIntegrateMotion(CsState *cs) {
    switch (cs->pushMode) {
        case 0:
            break;
        case 1:
            if (cs->pushInput != 0) {
                cs->pushSpeed += cs->pushAccel;
                if (cs->pushSpeedMax < cs->pushSpeed) {
                    cs->pushSpeed = cs->pushSpeedMax;
                }
            } else {
                cs->pushSpeed -= cs->pushAccel;
                if (cs->pushSpeed < 0.0) {
                    cs->pushSpeed = 0.0f;
                }
            }
            if (cs->pushSpeed > 0.01) {
                gCsPosX += cs->pushDirX * cs->pushSpeed;
                gCsPosZ += cs->pushDirZ * cs->pushSpeed;
                if (gCsPosX < cs->pushMinX) {
                    gCsPosX = cs->pushMinX;
                }
                if (gCsPosZ < cs->pushMinZ) {
                    gCsPosZ = cs->pushMinZ;
                }
                if (cs->pushMaxX < gCsPosX) {
                    gCsPosX = cs->pushMaxX;
                }
                if (cs->pushMaxZ < gCsPosZ) {
                    gCsPosZ = cs->pushMaxZ;
                }
            }
            break;
        case 2:
            if (cs->pushInput != 0) {
                switch (cs->pushInput) {
                    case 1:
                        cs->pushSpeed += cs->pushAccel;
                        break;
                    case 2:
                        cs->pushSpeed -= cs->pushAccel;
                        break;
                }
                if (cs->pushSpeedMax < cs->pushSpeed) {
                    cs->pushSpeed = cs->pushSpeedMax;
                }
                if (cs->pushSpeed < -cs->pushSpeedMax) {
                    cs->pushSpeed = -cs->pushSpeedMax;
                }
                gCsRotY += cs->pushSpeed;
            } else {
                if (cs->pushSpeed > 0.0) {
                    cs->pushSpeed -= cs->pushAccel;
                    if (cs->pushSpeed < 0.0) {
                        cs->pushSpeed = 0.0f;
                    }
                } else {
                    cs->pushSpeed += cs->pushAccel;
                    if (cs->pushSpeed > 0.0) {
                        cs->pushSpeed = 0.0f;
                    }
                }
                gCsRotY += cs->pushSpeed;
            }
            break;
    }
}

// Cutscene condition evaluator (csCondEval): one CsCond per call, nonzero = condition holds.
// The arguments are read as cond->arg[n] (CsCond), not through CsCmd's named fields: a named field
// is canonicalised to the left compare/addu operand, the indexed read gives the target's `bne field,arg`;
// the active-actor loops use their own pointer local `activeActor` (not `actor`, the player-loop pointer) and index `j`.

// Stride view of gPlayerSlots (PlayerStruct): indexing the shared type directly swaps the
// `addu base,off` operands of the player loops (Q0606); this record type reproduces the target.
typedef struct CsCondPlayer {
    /* 0x000 */ u8 active;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *actor;
    /* 0x008 */ u8 pad8[0x2F0 - 0x8];
} CsCondPlayer; /* 0x2F0 */

extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern u8 gGameMode;
extern s16 gPreviousMap;

#define CS_COND_PLAYER ((CsCondPlayer *)gPlayerSlots)

u8 csCondEval(CsCond *cond, CsState *cs, s16 csId) {
    u8 neg;
    u8 ret;
    s16 type;
    Actor *actor;
    CsCondPlayer *player;
    u8 found;
    s32 count;
    s32 kong;
    s32 j;
    s16 animKey;
    f32 animTime;
    u8 animState;
    u8 i;
    f32 animProgress;
    u8 *moveLevel;
    PlayerState *playerState;
    u32 mask;
    Actor *activeActor;
    s32 value;

    if (cond->op & 0x8000) {
        neg = 1;
    } else {
        neg = 0;
    }
    type = cond->op & 0x7FFF;
    switch (type) {
    case 0x0:
        ret = 1;
        break;
    case 0x3D:
        ret = gCsCondFlag;
        break;
    case 0x3C:
        ret = gPlayerSlots->camChunk == cond->arg[0];
        break;
    case 0x3A:
        if ((1 << cond->arg[0]) & gCsFlagBits) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x39:
        if (cond->arg[0] & gPrimaryPlayerActor->interactionType) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x38:
        ret = gPlayerCharacterId[0] < 5;
        break;
    case 0x37:
        modelAnimEntryGetState(csId, cond->arg[0], &animKey, &animTime, &animState);
        if (animKey == cond->arg[1]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x32:
        ret = gPreviousMap == cond->arg[0];
        break;
    case 0x30:
        if (gPrimaryPlayerActor->floorSlopeType == cond->arg[0]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x35:
        if (gPrimaryPlayerActor->floorSurfaceType == cond->arg[0]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x2E:
        if (actorListGetOrSetState(cond->arg[0], 0, 0) == cond->arg[1]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x2D:
        ret = flagGet(cond->arg[0], 0);
        break;
    case 0x36:
        ret = flagGet(cond->arg[0], 2);
        break;
    case 0x3B:
        ret = flagGet(cond->arg[0], 1);
        break;
    case 0x2C:
        if (actorListIsIdActive(cond->arg[0]) != 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x28:
        if (cs->runFlags & 1) {
            ret = 0;
        } else {
            ret = 1;
        }
        break;
    case 0x26:
        playerState = gPlayerSlots->actor->customState;
        if (((cond->arg[0] << 16) + cond->arg[1]) & playerState->stateFlags) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x27:
        playerState = gPlayerSlots->actor->customState;
        if (((cond->arg[0] << 16) + cond->arg[1]) & playerState->prevStateFlags) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x25:
        if (gCurrentKongInventory->slamLevel >= cond->arg[0]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x34:
        kong = playerLookupKongByActorType(cond->arg[0]);
        moveLevel = &gPlayerInventoryTable[gCurrentPlayerIndex].kong[kong].moveLevel;
        if (*moveLevel >= cond->arg[1]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x24:
        actor = spawnNodeActivate(cond->arg[0], 0);
        if (actor->state == cond->arg[1]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x23:
        if (gGameMode == 1) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1D:
        if ((cond->arg[0] == 0 && cs->stateBytes[cond->arg[2]] < cond->arg[1]) || (cond->arg[0] == 1 && cond->arg[1] < cs->stateBytes[cond->arg[2]])) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1C:
        value = modelAnimEntryGetUnkC(csId, cond->arg[0]);
        if ((cond->arg[1] == 0 && value < cond->arg[2]) || (cond->arg[1] == 1 && cond->arg[2] < value)) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x16:
        mask = (cond->arg[0] << 16) + cond->arg[1];
        if (gGlobalPauseFlags & mask) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x15:
        ret = modelAnimEntryIsActive(csId, cond->arg[0]);
        break;
    case 0xC:
        if (gCsPrevPosX != gCsPosX || gCsPrevPosY != gCsPosY || gCsPrevPosZ != gCsPosZ ||
            gCsPrevRotX != gCsRotX || gCsPrevRotY != gCsRotY || gCsPrevRotZ != gCsRotZ ||
            gCsPrevScale != gCsScale) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x8:
        ret = cs->pushContact;
        break;
    case 0x9:
        if (cs->pushInput != 0) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x7:
        ret = csCompareVar(cs->vars, cond->arg[0], cond->arg[1]);
        break;
    case 0x31:
        if (gModelSlots[hashTableLookup(gCsModelIds[cond->arg[0]])].csState->stateBytes[cond->arg[2]] == cond->arg[1]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1:
        if (cs->stateBytes[cond->arg[1]] == cond->arg[0]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x5:
        ret = csEvaluateParamCondition(cond->arg[0], cond->arg[1]);
        break;
    case 0x4:
        if (cs->timers[cond->arg[1]] == cond->arg[0]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x2:
        ret = 0;
        for (i = 0; i < gPlayerCount; i++) {
            player = &CS_COND_PLAYER[i];
            if (player->active != 0) {
                actor = player->actor;
                if (actor->attachMode == 1 && actor->cutsceneId == csId) {
                    ret = 1;
                }
            }
        }
        break;
    case 0xD:
        ret = 0;
        for (i = 0; i < gPlayerCount; i++) {
            player = &CS_COND_PLAYER[i];
            if (player->active != 0) {
                actor = player->actor;
                if (actor->attachMode == 1 && actor->cutsceneId == csId && actor->attachPartId == cond->arg[0]) {
                    ret = 1;
                }
            }
        }
        break;
    case 0x11:
        found = 0;
        for (j = 0; j < gActiveActorCount && !found; j++) {
            activeActor = gActiveActors[j].actor;
            if (!(activeActor->flags & 0x2000) && activeActor->actorType == cond->arg[0] && activeActor->attachMode == 1 && activeActor->cutsceneId == csId) {
                found = 1;
            }
        }
        if (found) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x12:
        found = 0;
        for (j = 0; j < gActiveActorCount && !found; j++) {
            activeActor = gActiveActors[j].actor;
            if (!(activeActor->flags & 0x2000) && activeActor->actorType == cond->arg[0] && activeActor->attachMode == 1 && activeActor->cutsceneId == csId &&
                activeActor->attachPartId == cond->arg[1]) {
                found = 1;
            }
        }
        if (found) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x14:
        count = 0;
        for (j = 0; j < gActiveActorCount; j++) {
            activeActor = gActiveActors[j].actor;
            if (!(activeActor->flags & 0x2000) && activeActor->actorType == cond->arg[0] && activeActor->cutsceneId == csId && activeActor->attachPartId == cond->arg[1]) {
                count++;
            }
        }
        if (count == cond->arg[2]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0xB:
        ret = 0;
        for (i = 0; i < gPlayerCount; i++) {
            player = &CS_COND_PLAYER[i];
            if (player->active != 0) {
                actor = player->actor;
                if (actor->attachMode == 3 && actor->attachNodeIndex == cond->arg[0] && actor->cutsceneId == csId) {
                    ret = 1;
                }
            }
        }
        break;
    case 0xA:
        ret = 0;
        for (i = 0; i < gPlayerCount; i++) {
            player = &CS_COND_PLAYER[i];
            if (player->active != 0) {
                actor = player->actor;
                if (actor->attachMode == 2 && actor->cutsceneId == csId) {
                    ret = 1;
                } else {
                    ret = 0;
                }
            }
        }
        break;
    case 0xE:
        ret = csPosOnScreenOfNearPlayer(cond->arg[0]);
        break;
    case 0x13:
        ret = csPlayerNearPos(cond->arg[0]);
        break;
    case 0x20:
        ret = csPlayerSavedPosNearPos(cond->arg[0]);
        break;
    case 0x29:
        ret = csSpawnNodeNearPos(cond->arg[0], cond->arg[1], cond->arg[2]);
        break;
    case 0x6:
        ret = gCsCondTable[cond->arg[0]](cs, csId, cond->arg[1], cond->arg[2]);
        break;
    case 0xF:
        ret = pathPlaybackIsActive(cs->pathHandle);
        break;
    case 0x10:
        if (cs->hitId != 0 && (cond->arg[1] == -1 || cs->hitId == cond->arg[1]) &&
            (cond->arg[0] & actorLookupClass(cs->hitActorType)) && csIsPlayerInCutsceneState() != 0) {
            csSetDamageCooldownForModel(gModelSlots[hashTableLookup(csId)].modelType);
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x18:
        if (cs->hitId != 0 && (cond->arg[1] == -1 || cs->hitId == cond->arg[1]) && cs->hitActorType == cond->arg[0] &&
            csIsPlayerInCutsceneState() != 0) {
            csSetDamageCooldownForModel(gModelSlots[hashTableLookup(csId)].modelType);
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x17:
        ret = 0;
        for (i = 0; i < gPlayerCount; i++) {
            player = &CS_COND_PLAYER[i];
            if (player->active != 0) {
                actor = player->actor;
                if (actor->state == cond->arg[0]) {
                    if (cond->arg[1] != 0) {
                        value = cond->arg[1];
                        if (actor->subState == value) {
                            ret = 1;
                        }
                    } else {
                        ret = 1;
                    }
                }
            }
        }
        break;
    case 0x21:
        ret = 0;
        for (i = 0; i < gPlayerCount; i++) {
            player = &CS_COND_PLAYER[i];
            if (player->active != 0 && player->actor->subState == cond->arg[0]) {
                ret = 1;
            }
        }
        break;
    case 0x19:
        if (gPrimaryPlayerActor->actorType == cond->arg[0]) {
            ret = 1;
        } else {
            ret = 0;
        }
        break;
    case 0x1A:
        ret = gPlayerSlots->sizeMode == cond->arg[0];
        break;
    case 0x1B:
        ret = gPlayerSlots->sizeModeDirty;
        break;
    case 0x1E:
        ret = spawnNodeHasActor(cond->arg[0]);
        break;
    case 0x2F:
        ret = spawnNodeIsInCooldown(cond->arg[0]);
        break;
    case 0x1F:
        ret = 0;
        break;
    case 0x22:
        ret = listContainsS16(cond->arg[0]);
        break;
    case 0x2A:
        if (gCsCountdown.active != 0) {
            if (gCsCountdown.timerActor->state == 5) {
                ret = 1;
            } else {
                ret = 0;
            }
        } else {
            ret = 1;
        }
        break;
    case 0x2B:
        ret = gCsCountdown.active;
        break;
    case 0x33:
        animProgress = actorGetAnimProgress(gPrimaryPlayerActor);
        ret = 0;
        if (cond->arg[0] == 0 && cond->arg[1] < (s16)animProgress) {
            ret = 1;
        }
        if (cond->arg[0] == 1 && (s16)animProgress < cond->arg[1]) {
            ret = 1;
        }
        break;
    default:
        ret = 0;
        break;
    }
    if (neg) {
        ret = 1 - ret;
    }
    return ret;
}

// Cutscene script command interpreter (csCmdExec): one 8-byte command per call.

extern u8 gNextTransitionFadeType;
extern s32 gCurrentMap;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern u32 gGlobalCutsceneFlags;

void hudSpawnCountdownTimer(s32, s32, u8, void *); // ORIG: a3 = &gCsCountdown loaded at 0x2600/0x2604 and live into jal 0x261c (a 3-argument call puts the address in t0 instead); owner A7710 homes only a0-a2 (0x8-0x10) and never reads a3
void modelAnimEntrySetUnkC(); // ORIG: case 0x4C passes h in a2 as computed (sll/sra at 0x29cc/0x29d0) into jal 0x29e0; the shared (s16, s16, s16) prototype re-narrows a2 before the call; owner 54150 narrows a0 itself (sll/sra at 0x15c0) and an s32 owner does not fdiff

void csCmdExec(CsCmd *cmd, CsState *cs, s16 csId) {
    void *dm = &csId; // FAKE: unused escape of csId: its word keeps sel at sp+0xB3 and the address-of keeps csId memory-resident (sw a2,208(sp), lh 210(sp) per 0x2D/0x76 loop iteration); a pad gives only the word (Q0174, Q0914, Q1252)
    u8 bit; // one u8 flag: the case 0x1C found flag and the case 0xE/0x7D exclusive bit
    s32 i;
    s32 slot;
    s32 h;
    u8 sel;
    f32 x;
    f32 y;
    f32 z;
    f32 px;
    f32 py;
    f32 pz;
    f32 cr;
    f32 cg;
    f32 cb;
    s16 idx;
    s16 modelId;
    PlayerState *playerState;
    Actor *actor;
    u8 pitch7;
    s32 map;
    u8 range;
    s32 exit;
    s16 flag;
    struct EffectGridAsset *asset;
    s32 hub;
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pitch;
    u8 vol;
    u8 range7;
    f32 cx;
    f32 cy;
    f32 cz;
    u8 vol7;

    bit = 0;
    switch (cmd->op) {
    case 0x95:
        gCsCamPathLockFlag = 0x80;
        break;
    case 0x92:
        playerState = gPlayerSlots->actor->customState;
        playerState->stateFlags |= 0x40000800;
        break;
    case 0x91:
        gPrimaryPlayerActor->speedXZ = cmd->a;
        break;
    case 0x93:
        camSetZoneWeight(cmd->a, cmd->b);
        break;
    case 0x94:
        spawnNodesSendVolumeTrigger(2, cmd->a, 0, 0, 0);
        break;
    case 0x90:
        gCsInvulnerable = cmd->a;
        break;
    case 0x96:
        gCsCondFlag = cmd->a;
        break;
    case 0x8E:
        dynamicBufferFree(&gModelSlots[hashTableLookup(csId)].boxBuffer);
        break;
    case 0x8F:
        modelSlotTriBufferRelease(&gModelSlots[hashTableLookup(csId)].triBuffer);
        break;
    case 0x85:
        mapResolveNodeAssets();
        break;
    case 0x83:
        slotQueueSetDisplayMode(cmd->a, cmd->b, cmd->c);
        break;
    case 0x80:
        eepromSavePlayerData();
        break;
    case 0x81:
        gCsFlagBits |= 1 << cmd->a;
        break;
    case 0x82:
        gCsFlagBits &= ~(1 << cmd->a);
        break;
    case 0x7F:
        switch (cmd->b) {
        case 0:
            sel = 0;
            break;
        case 1:
            sel = 1;
            break;
        case 2:
            sel = 2;
            break;
        case 3:
            sel = 3;
            break;
        }
        proxPathSetEndBehavior(csId, cmd->a, sel);
        break;
    case 0x7C:
        gCsSfxNode = cmd->a;
        break;
    case 0x7B:
        modelSlotGetNodePos(csId, 1, cmd->b, &x, &y, &z);
        volumeTriggerSetPosition(cmd->a, x, y, z);
        break;
    case 0x7A:
        effectNodeSetSubVal(cmd->a, cmd->b);
        break;
    case 0x76:
        i = 0; // LAYOUT: the init on its own line schedules move t0,zero ahead of the gActiveActors address at 0x23f4 (on the for line, or one line with it: after it; Q0186)
        for (; i < gActiveActorCount; i++) {
            actor = gActiveActors[i].actor;
            if (!(actor->flags & 0x2000) && actor->attachMode == 1 && actor->cutsceneId == csId) {
                actorAppendCallback(actor, 0, 8, 0, 0, 0);
            }
        }
        break;
    case 0x75:
        volumeTriggerSetEnabled(cmd->a, cmd->b);
        break;
    case 0x78:
        modelSlotGetNodePos(csId, 1, cmd->a, &px, &py, &pz);
        playerState = gPlayerSlots->actor->customState;
        playerState->savedX = px;
        playerState->savedY = py;
        playerState->savedZ = pz;
        break;
    case 0x74:
        cs->modelFlags |= cmd->a;
        break;
    case 0x73:
        playerStateSetCallbackParameters(0, cmd->a, cmd->b, cmd->c);
        break;
    case 0x72:
        actorListGetOrSetState(cmd->a, cmd->b, 1);
        break;
    case 0x6E:
        gCsCamUseGlobalPaths = cmd->a;
        break;
    case 0x6D:
        modelSlotSetScaleXZ(csId, 1, cmd->a / 100.0);
        break;
    case 0x6C:
        modelSkipListAdd(cmd->a);
        break;
    case 0x6B:
        flagSet(cmd->a, cmd->b, 0);
        break;
    case 0x79:
        flagSet(cmd->a, cmd->b, 2);
        break;
    case 0x84:
        flagSet(cmd->a, cmd->b, 1);
        break;
    case 0x66:
        if (gCsCountdown.active == 0) {
            actorSpawn(0xB1, 0);
            actor = gCurrentActor;
            gCsCountdown.hostActor = gSpawnedActor;
            gCurrentActor = gSpawnedActor;
            hudSpawnCountdownTimer(0xDC, 0x2A, cmd->a, &gCsCountdown);
            gCsCountdown.timerActor = gSpawnedActor;
            gCsCountdown.active = 1;
            gCurrentActor = actor;
        }
        break;
    case 0x67:
        if (gCsCountdown.active != 0) {
            hudCountdownTimerStart(gCsCountdown.timerActor);
        }
        break;
    case 0x68:
        if (gCsCountdown.active != 0) {
            actorDespawn(gCsCountdown.timerActor);
            bit = (s32)gCsCountdown.hostActor; if (bit) {} // FAKE: the dead read keeps bit (a3) live between the despawns, splitting the &gCsCountdown lda range: v0 at 0x2670-0x2688, folded lui/lw %lo(gCsCountdown+4) at 0x268c/0x2694 (Q1157, Q1253)
            actorDespawn(gCsCountdown.hostActor);
            gCsCountdown.active = 0;
        }
        break;
    case 0x62:
        gCsLightIndex = cmd->a;
        break;
    case 0x60:
        actorSetTargetSlotByte(csId, cmd->a);
        break;
    case 0x5F:
        playerState = gPlayerSlots->actor->customState;
        playerState->stateFlags |= (cmd->a << 16) + cmd->b;
        break;
    case 0x3B:
        playerState = gPlayerSlots->actor->customState;
        playerState->stateFlags &= ~((cmd->a << 16) + cmd->b);
        break;
    case 0x8C:
        playerState = gPlayerSlots->actor->customState;
        playerState->stateFlags2 |= (cmd->a << 16) + cmd->b;
        break;
    case 0x8B:
        playerState = gPlayerSlots->actor->customState;
        playerState->stateFlags2 &= ~((cmd->a << 16) + cmd->b);
        break;
    case 0x5D:
        screenSetTransitionFadeType(cmd->a);
        break;
    case 0x5C:
        zoneEntrySetDisabled(cmd->a, cmd->b, cmd->c);
        break;
    case 0x5B:
        playerRespawnResetPhysics(cmd->a);
        break;
    case 0x5A:
        cs->collisionRebuildRadiusX = cmd->a;
        cs->collisionRebuildRadiusY = cmd->b;
        cs->collisionRebuildRadiusZ = cmd->c;
        break;
    case 0x57:
        lightGetColor(&cr, &cg, &cb, gCsLightIndex);
        lightSetColor(cmd->a / 1000.0 + cr, cmd->b / 1000.0 + cg, cmd->c / 1000.0 + cb, gCsLightIndex);
        break;
    case 0x4F:
        if (gCsTrackedModelCount != 16) {
            if (cmd->a != -2) {
                gCsTrackedModels[gCsTrackedModelCount] = cmd->a;
                gCsTrackedModelCount++;
            } else {
                gCsTrackedModels[gCsTrackedModelCount] = gModelSlots[hashTableLookup(csId)].csModelId;
                gCsTrackedModelCount++;
            }
        }
        break;
    case 0x50:
        if (gCsModelIds[cmd->a] != -1) {
            modelSlotGetNodePos(gCsModelIds[cmd->a], 1, cmd->b, &gCsSpawnX, &gCsSpawnY, &gCsSpawnZ);
        }
        break;
    case 0x4E:
        asset = effectGridFindByTargetId(cmd->a);
        effectSetDepth(1);
        effectCreateAtModelNode(asset, cmd->b / 100.0, csId, cmd->c, 0);
        break;
    case 0x4C:
        h = (s16)(modelAnimEntryGetUnkC(csId, cmd->a) + cmd->b);
        if (h < 0) {
            h = 0;
        }
        modelAnimEntrySetUnkC(csId, cmd->a, h);
        break;
    case 0x4B:
        proxPathSetEnabled(csId, cmd->a, cmd->b);
        break;
    case 0x46:
        cs->collisionEnabled = cmd->a;
        break;
    case 0x47:
        cs->floorEnabled = cmd->a;
        break;
    case 0x4A:
        modelSlotUpdateTailKey(csId, 1, cmd->a, cmd->b);
        break;
    case 0x45:
        cs->alphaOverride = cmd->a;
        cs->alphaTarget = cmd->b;
        cs->alphaStep = cmd->c;
        break;
    case 0x40:
        gGlobalPauseFlags |= ((u16)cmd->a << 16) + (u16)cmd->b;
        break;
    case 0x88:
        gGlobalCutsceneFlags |= ((u16)cmd->a << 16) + (u16)cmd->b;
        break;
    case 0x89:
        gGlobalCutsceneFlags &= ~(((u16)cmd->a << 16) + (u16)cmd->b);
        break;
    case 0x3F:
        cs->contactCallbacks = cmd->a;
        break;
    case 0x3E:
        cs->deferredPush = cmd->a;
        break;
    case 0x3D:
        cs->collisionRebuildMode = cmd->a;
        break;
    case 0x39:
        cs->floorGrabbable = cmd->a;
        break;
    case 0x36:
        csSetActorAlphaByType(cmd->a, cmd->b, csId);
        break;
    case 0x35:
        csSetActorScaleFadeByType(cmd->a, cmd->b, csId);
        break;
    case 0x33:
        mapOffsetSlotSetTarget(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x55:
        mapOffsetSlotSetEnabled(cmd->a, cmd->b);
        break;
    case 0x34:
        mapOffsetSlotAddTarget(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x6A:
        effectNodeAddTargetAndStep(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x69:
        effectNodeSetTargetAndStep(cmd->a, cmd->b, cmd->c / 100.0f);
        break;
    case 0x26:
        csSetObjectTrackParam(cs, cmd->a, cmd->b);
        break;
    case 0x54:
        slot = hashTableLookup(gCsModelIds[cmd->a]);
        if (slot != -1) {
            csSetObjectTrackParam(gModelSlots[slot].csState, cmd->b, cmd->c);
        }
        break;
    case 0x25:
        csStartCamPath(cs, cmd->a, cmd->b, cmd->c);
        break;
    case 0x3C:
        if (cs->camPathActor != NULL) {
            actorDespawn(cs->camPathActor);
            cs->camPathActor = NULL;
        }
        break;
    case 0x30:
        mapRequestTransition(cmd->a, 0);
        break;
    case 0x86:
        playerThrowHeldActor(gActivePlayerActor);
        mapSaveSlotAndTransition(0x2A, 0, cmd->a, 2);
        break;
    case 0x87:
        mapTransitionToPreviousOrExit();
        break;
    case 0x8D:
        gNextTransitionFadeType = 2;
        playerThrowHeldActor(gActivePlayerActor);
        hub = mapGetHubWorldIndex(gCurrentMap, 0);
        if (mapIsLobby(gCurrentMap) != 0) {
            map = gHubWorldMaps[hub];
            exit = gHubWorldExits[hub];
            if (flagGet(gHubWorldFlags[hub], 0) == 0) {
                if (map == 0x57) {
                    exit = 0x15;
                } else {
                    exit = 0;
                }
            }
            if (cutsceneTriggerCheck(map) == 0) {
                mapRequestTransition(map, exit);
            }
        } else {
            mapTransitionToWorldHub(hub);
        }
        break;
    case 0x31:
        if (cmd->c & 0x100) {
            transitionSetState(2);
            screenSetTransitionFadeType(0);
        }
        switch (cmd->c & 0xFF) {
        case 0:
            flag = 0;
            break;
        case 1:
            flag = 1;
            break;
        case 2:
            flag = 3;
            break;
        }
        mapSaveSlotAndTransition(cmd->a, cmd->b, 0, flag);
        break;
    case 0x32:
        mapTransitionExitCurrent(cmd->a, cmd->b);
        break;
    case 0x2F:
        demoPlaybackStart(gActivePlayerActor, cmd->a);
        break;
    case 0x11:
        modelAnimEntryStart(csId, cmd->a, cmd->b);
        break;
    case 0x12:
        modelAnimEntryStop(csId, cmd->a);
        break;
    case 0x13:
        modelAnimEntryClearTime(csId, cmd->a);
        break;
    case 0x14:
        modelAnimEntrySetUnkC(csId, cmd->a, cmd->b);
        break;
    case 0x15:
        modelAnimEntrySetUnkF(csId, cmd->a, cmd->b);
        break;
    case 0x16:
        modelAnimEntrySetUnk10(csId, cmd->a, cmd->b);
        break;
    case 0x17:
        modelAnimEntryResetFrame(csId, cmd->a, cmd->b);
        break;
    case 0x18:
        modelAnimEntrySetUnk12(csId, cmd->a, cmd->b);
        break;
    case 0x1A:
        modelAnimEntrySetTime(csId, cmd->a, cmd->b, cmd->c / 100.0);
        break;
    case 0xE:
        pitch = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        range = cmd->c & 0x7F;
        if (pitch == 0) {
            pitch = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 1;
        if (cs->sfxSources[i] < 0) {
            bit = cmd->b & 2;
            cs->sfxSources[i] = sfxSlotAllocateSource(csId, cmd->a, range, bit, vol, (u32)pitch / 127.0, 0);
        }
        break;
    case 0x7D:
        pitch = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        range = cmd->c & 0x7F;
        if (pitch == 0) {
            pitch = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 1;
        if (cs->sfxSources[i] < 0) {
            bit = cmd->b & 2;
            cs->sfxSources[i] = sfxSlotAllocateSource(csId, cmd->a, range, bit, vol, (u32)pitch / 127.0, gCsSfxNode);
        }
        break;
    case 0xF:
        pitch = (cmd->b / 128) & 0xFF;
        vol = (cmd->c / 128) & 0xFF;
        range = cmd->c & 0x7F;
        if (pitch == 0) {
            pitch = 0x7F;
        }
        if (vol == 0) {
            vol = 0xFF;
        }
        i = cmd->b & 0x7F; // the spread, in i as in case 0x7E
        sfxPlayFromTargetSlot(csId, cmd->a, vol, pitch, i, range, 0.3f);
        break;
    case 0x7E:
        pitch7 = (cmd->b / 128) & 0xFF;
        vol7 = (cmd->c / 128) & 0xFF;
        range7 = cmd->c & 0x7F;
        if (pitch7 == 0) {
            pitch7 = 0x7F;
        }
        if (vol7 == 0) {
            vol7 = 0xFF;
        }
        i = cmd->b & 0x7F; // ORIG: the spread is spilled to i's home sp+0xBC at 0x3268 (reloaded 0x327c), the slot the case 0x76 actor loop spills its index to (0x2450/0x2460)
        if (gCsSfxNode > 0) {
            modelSlotGetNodePos(csId, 1, gCsSfxNode, &sx, &sy, &sz);
            sfxPlayAtPositionPooled(sx, sy, sz, cmd->a, vol7, pitch7, i, range7, 0.3f, 0);
        } else {
            sfxPlayOnFreeSlot(cmd->a, 0x7FFF, 63.0f, (u32)pitch7 / 127.0, 0, 0);
        }
        break;
    case 0x10:
        if (cs->sfxSources[cmd->b] >= 0) {
            sfxSlotFreeSource(cs->sfxSources[cmd->b]);
            cs->sfxSources[cmd->b] = -1;
        }
        break;
    case 0x48:
        sfxSetVolumeAndPan(cs->sfxSources[cmd->a], cmd->b * 0.0001220703125, cmd->c);
        break;
    case 0xA:
        cs->pushMode = cmd->a;
        cs->pushSpeedMax = cmd->b / 100.0f;
        cs->pushAccel = cmd->c / 100.0f;
        break;
    case 0xB:
        cs->pushMinX = (f32)cmd->a;
        cs->pushMinZ = (f32)cmd->b;
        break;
    case 0xC:
        cs->pushMaxX = (f32)cmd->a;
        cs->pushMaxZ = (f32)cmd->b;
        break;
    case 0xD:
        cs->pushArcMin = (f32)cmd->a;
        cs->pushArcMax = (f32)cmd->b;
        break;
    case 0x9:
        if (gCsPrevPosX != gCsPosX || gCsPrevPosZ != gCsPosZ) {
            csSnapToGround(cmd->a, csId);
        }
        break;
    case 0x41:
        gCsGroundUpdatePending = 1;
        break;
    case 0x6:
        cs->vars[cmd->a] = cmd->b / 10.0f;
        break;
    case 0x0:
        csSetRot(cmd->a, cmd->b, cs, csId, 1);
        break;
    case 0x8:
        csSetPos(cmd->a, cmd->b, cs, csId, 1);
        break;
    case 0x1E:
        csSetRot(cmd->a, cmd->b, cs, csId, 0);
        break;
    case 0x1D:
        csSetPos(cmd->a, cmd->b, cs, csId, 0);
        break;
    case 0x3:
        if (cmd->a == 0) {
            cs->timers[cmd->c] = cmd->b;
        } else {
            cs->timers[cmd->c] = cs->vars[cmd->b];
        }
        break;
    case 0x65:
        cs->nextStateBytes[cmd->b] += cmd->a;
        break;
    case 0x1:
        cs->nextStateBytes[cmd->b] = cmd->a;
        break;
    case 0x5:
        if (csModelStateTrySetByte(cmd->a, cmd->b, cmd->c) == 0) {
            return;
        }
        break;
    case 0x2D:
        i = 0; // LAYOUT: the init on its own line schedules move t0,zero ahead of the gActiveActors address at 0x3664 (on the for line, or one line with it: after it; Q0186)
        for (; i < gActiveActorCount; i++) {
            actor = gActiveActors[i].actor;
            if (!(actor->flags & 0x2000) && actor->attachMode == 1 && actor->cutsceneId == csId) {
                if (cmd->a != 0) {
                    actor->flags2 |= 4;
                } else {
                    actor->flags2 &= ~4;
                }
            }
        }
        break;
    case 0x7:
        gCsCmdTable[cmd->a](cs, csId, cmd->b, cmd->c);
        break;
    case 0x37:
        actorAppendCallback(gPlayerSlots->actor, 0, 0x400000, cmd->a, 0, 0);
        break;
    case 0x19:
        playerStateQueueCallback(cmd->a, 0, 0);
        break;
    case 0x2C:
        modelSlotGetNodePos(csId, 1, cmd->a, &cx, &cy, &cz);
        actorAppendCallbackVec3f(0, gPlayerSlots->actor, cx, cy, cz);
        break;
    case 0x2B:
        modelSlotSetDistanceOverride(csId, 1, cmd->a);
        break;
    case 0x1B:
        if (gCsModelIds[cmd->a] != -1) {
            modelSlotGetNodePos(gCsModelIds[cmd->a], 1, cmd->b, &gCsPosX, &gCsPosY, &gCsPosZ);
        }
        break;
    case 0x1C:
        if (gCsModelIds[cmd->a] != -1) {
            idx = hashTableLookup(gCsModelIds[cmd->a]);
            if (idx != -1) {
                if (gModelSlots[idx].csState != NULL) {
                    bit = 1;
                    gModelSlots[idx].csState->stateBytes[cmd->b] += cmd->c;
                }
            }
        }
        if (bit == 0) {
            return;
        }
        break;
    case 0x2:
        pathPlaybackSetSpeed(cs->pathHandle, cmd->a);
        break;
    case 0x1F:
        pathPlaybackSetLoopMode(cs->pathHandle, cmd->a);
        break;
    case 0x20:
        pathPlaybackSetDirection(cs->pathHandle, cmd->a);
        break;
    case 0x21:
        pathPlaybackSetLoopLimit(cs->pathHandle, cmd->a);
        break;
    case 0x24:
        pathPlaybackSetActive(cs->pathHandle, cmd->a);
        break;
    case 0x22:
        cs->pathHandle = pathPlaybackStart(0, cmd->a, cmd->b, gCsPosX, gCsPosY, gCsPosZ, cmd->c);
        break;
    case 0x23:
        pathPlaybackFree(cs->pathHandle);
        cs->pathHandle = -1;
        break;
    case 0x4:
        pathPlaybackAdvance(cs->pathHandle);
        pathPlaybackGetPosition(cs->pathHandle, &gCsPosX, &gCsPosY, &gCsPosZ);
        break;
    case 0x27:
        modelSlotSetNodeAnimMode(csId, cmd->a, cmd->b);
        break;
    case 0x28:
        modelSlotSetNodeFrame(csId, cmd->a, cmd->b, cmd->c);
        break;
    case 0x42:
        modelSlotSetNodeScrollSpeed(csId, cmd->a, cmd->b, cmd->c);
        break;
    case 0x29:
        playerState = gPlayerSlots->actor->customState;
        camStartShakeFromPoint(playerState->camActor, cmd->a, cmd->b, gCsPosX, gCsPosY, gCsPosZ, gCsShakeInnerRadius, gCsShakeOuterRadius);
        break;
    case 0x44:
        gCsShakeInnerRadius = cmd->a;
        gCsShakeOuterRadius = cmd->b;
        break;
    case 0x2A:
        gModelSlots[hashTableLookup(csId)].boxBuffer.pushBothSides = cmd->a;
        break;
    case 0x2E:
        mapChunkSetEnabled(cmd->a, cmd->b);
        break;
    case 0x38:
        mapPortalSlotSetEnabled(cmd->a, cmd->b, cmd->c);
        break;
    case 0x61:
        if (cmd->c != 0) {
            sfxAllocateChannel(cmd->a, cmd->c / 255.0);
        } else {
            sfxAllocateChannel(cmd->a, 1.0f);
        }
        break;
    case 0x6F:
        sfxStopChannel(cmd->a, (u8)cmd->b);
        break;
    case 0x70:
        seqRouteChannelVolume(cmd->a, cmd->b / 255.0);
        break;
    case 0x71:
        sfxSetChannelTempo(cmd->a, cmd->b * 0.0001220703125);
        break;
    case 0x43:
        if (cmd->a == 1) {
            cs->riderDriftX = cs->vars[cmd->b];
            cs->riderDriftZ = cs->vars[cmd->c];
        } else {
            cs->riderDriftX = cmd->b / 10.0f;
            cs->riderDriftZ = cmd->c / 10.0f;
        }
        break;
    case 0x49:
        actorAppendEvent(0, gPlayerSlots->actor, cmd->a, cmd->b, cmd->c, gCsPosX, gCsPosY, gCsPosZ);
        break;
    case 0x4D:
        modelId = modelSlotAppend(cmd->a, gCsSpawnX, gCsSpawnY, gCsSpawnZ, gCsSpawnY - gCsPrevGroundOffset, 0);
        if (cmd->b == 0) {
            csStateShareScript(modelId, csId, cmd->c);
        }
        break;
    case 0x51:
        gridMoveNode(csId, gCsPosX, gCsPosY, gCsPosZ);
        break;
    case 0x5E:
        csSendActorMessagePayload(cmd->a, cmd->b);
        break;
    case 0x8A:
        csSendMsgByActorType(cmd->a, cmd->b);
        break;
    case 0x63:
        weatherSetMode(cmd->a, cmd->b, cmd->c);
        break;
    case 0x64:
        enemyAggroDespawnBB();
        break;
    case 0x56:
        spawnNodesSendVolumeTrigger(1, cmd->a, 0, 0, 0);
        break;
    case 0x59:
        spawnNodesSendVolumeTrigger(3, cmd->a, cmd->b, 0, 0);
        break;
    case 0x58:
        if (mapSlotSetModelRecord(cmd->a, cmd->b, cmd->c) == 0) {
            csTimerQueueAdd(cmd->a, cmd->b, cmd->c);
        }
        break;
    case 0x77:
        modelAnimEntrySetUnk13(csId, cmd->a, cmd->b, cmd->c / 1000.0);
        break;
    }
}


void csSetDamageCooldownForModel(s16 modelId) {
    PlayerState *playerState;

    playerState = gPlayerSlots->actor->customState;
    switch (modelId) {
        case 0x33:
        case 0xBC:
        case 0x125:
        case 0x126:
        case 0x127:
        case 0x128:
        case 0x129:
        case 0x229:
        case 0x22A:
        case 0x22B:
            playerState->damageCooldown = 0x3C;
            break;
    }
}


void csSendMsgByActorType(s16 actorType, s16 msgParam) {
    s32 i;
    Actor *actor;
    s16 msgPayload[2];

    msgPayload[0] = 0;
    msgPayload[1] = msgParam;
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (actor->actorType == actorType) {
            actorAppendCallbackMemcpy8(0, actor, 0x01000000, 1, msgPayload, 0);
        }
    }
}


void csSendActorMessagePayload(s16 paramA, s16 paramB) {
    s16 *msgPayload;
    Actor *targetActor;

    msgPayload = heapAlloc(4);
    heapFreeDeferred(msgPayload);
    msgPayload[1] = paramA;
    msgPayload[0] = paramB;
    actorFindActiveByType(0xE, &targetActor);
    actorAppendCallbackMemcpy8(0, targetActor, 0x01000000, 1, msgPayload, 0);
}

s32 csModelStateTrySetByte(s16 modelIndex, s16 val, s16 byteOffset) {
    s16 modelId = gCsModelIds[modelIndex];
    s16 slot;

    if (modelId != -1) {
        slot = hashTableLookup(modelId);
        if (slot != -1 && gModelSlots[slot].csState != NULL) {
            gModelSlots[slot].csState->stateBytes[byteOffset] = val;
            return 1;
        }
    }
    return 0;
}

void csSetObjectTrackParam(CsState *cs, s16 mode, s16 value) {
    cs->updateMode = mode;
    switch (mode & 0xFF) {
    case 3:
    case 4:
    case 6:
        cs->updateRangeSq = value * value;
        break;
    case 5:
        cs->queueKey = value;
        break;
    }
}


s32 csIsPlayerInCutsceneState(void) {
    PlayerState *playerState = gPlayerSlots->actor->customState;

    if ((gPrimaryPlayerActor->state == 0x42 && (playerState->hitActorType == 0x62 || playerState->hitActorType == 0x88 || playerState->hitActorType == 0x17)) || gPrimaryPlayerActor->state == 0x52 ||
        gPrimaryPlayerActor->state == 0x67 || gPlayerSlots->queuedState == 0x1C || gPlayerSlots->queuedState == 0x53) {
        return 0;
    }
    return 1;
}


void csFreeTrackedModels(void) {
    s32 i;

    for (i = 0; i < gCsTrackedModelCount; i++) {
        modelSlotFreeByIndex(gCsModelIds[gCsTrackedModels[i]], 1);
    }
}

void csStateShareScript(s16 dstModel, s16 srcModel, s16 val) {
    dstModel = hashTableLookup(dstModel);
    srcModel = hashTableLookup(srcModel);
    gModelSlots[dstModel].csState = heapAlloc(sizeof(CsState));
    csStateInit(gModelSlots[dstModel].csState);
    gModelSlots[dstModel].csState->stateBytes[0] = val;
    gModelSlots[dstModel].csState->nodes = gModelSlots[srcModel].csState->nodes;
}

void csSetActorAlphaByType(s16 actorType, s16 enable, s16 csId) {
    s32 i;
    Actor *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x2000) && actor->actorType == actorType && actor->cutsceneId == csId) {
            if (enable != 0) {
                actor->flags2 |= 4;
            } else {
                actor->flags2 &= ~4;
            }
        }
    }
}

void csSetActorScaleFadeByType(s16 actorType, s16 mode, s16 csId) {
    s32 fadeArg;
    s32 i;
    Actor *actor;

    switch (mode) {
    case 0:
        fadeArg = 1;
        break;
    case 1:
        fadeArg = 2;
        break;
    case 2:
        fadeArg = 0x3C;
        break;
    }
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x2000) && actor->actorType == actorType && actor->cutsceneId == csId) {
            actorAppendCallback(actor, 0, 0x800, fadeArg, 0, 0);
        }
    }
}


void csStartCamPath(CsState *cs, s16 camIdx, s16 mode, s16 c) {
    s32 flag;

    if (cs->camPathActor == NULL && actorSpawnSkipTypeInit(0x14) != 0) {
        cs->camPathActor = gSpawnedActor;
        gSpawnedActor->collisionMode = 1;
        gSpawnedActor->x = gCsPosX;
        gSpawnedActor->y = gCsPosY;
        gSpawnedActor->z = gCsPosZ;
        gSpawnedActor->yaw = gCsRotY * 4096.0f / 360.0f;
        if (gCsCamUseGlobalPaths != 0) {
            gSpawnedActor->eyeHeight = c;
        }
        if (gCsCamUseGlobalPaths != 0) {
            flag = 4;
        } else {
            flag = 0;
        }
        switch (mode) {
        case 0:
            camStartPath(cs->camPathActor, camIdx, flag | 1 | gCsCamPathLockFlag);
            return;
        case 1:
            camStartPath(NULL, camIdx, flag | 1 | gCsCamPathLockFlag);
            return;
        case 2:
            camStartPath(spawnNodeActivate(c, 0x400), camIdx, flag | 1 | gCsCamPathLockFlag);
            break;
        }
    }
}

void csCamPathActorUpdate(void) {
}

extern u8 gViewportCount;

u8 csPosOnScreenOfNearPlayer(s16 radius) {
    f32 sx;
    f32 sy;
    u8 i;
    Actor *actor;
    f32 dx;
    f32 dy;
    f32 dz;
    u8 ret = 0;

    for (i = 0; i < gViewportCount; i++) {
        if (gPlayerSlots[i].active != 0) {
            actor = gPlayerSlots[i].actor;
            dx = gCsPosX - actor->x;
            dy = gCsPosY - actor->y;
            dz = gCsPosZ - actor->z;
            dx *= dx;
            dy *= dy;
            dz *= dz;
            if (sqrtf(dx + dy + dz) < radius) {
                camProjectToScreen(gCsPosX, gCsPosY, gCsPosZ, &sx, &sy, 0, 1.0f, i);
                if ((s16)sx >= gPlayerSlots[i].rect[0] + 0x14 && (s16)sy >= gPlayerSlots[i].rect[1] + 0x14 &&
                    gPlayerSlots[i].rect[2] - 0x14 >= (s16)sx && gPlayerSlots[i].rect[3] - 0x14 >= (s16)sy) {
                    ret = 1;
                }
            }
        }
    }
    return ret;
}

// Stride view of gPlayerSlots (PlayerStruct camX/camY/camZ at 0x210): as CsCondPlayer, the
// shared type swaps the `addu base,off` operands of the loops below.
typedef struct CsPlayerPosView {
    /* 0x000 */ u8 active;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *actor;
    /* 0x008 */ u8 pad8[0x208];
    /* 0x210 */ f32 camX;
    /* 0x214 */ f32 camY;
    /* 0x218 */ f32 camZ;
    /* 0x21C */ u8 pad21C[0x2F0 - 0x21C];
} CsPlayerPosView; // size = 0x2F0

u8 csPosWithinRadius(s16 radius, f32 x, f32 y, f32 z) {
    f32 dx = gCsPosX - x;
    f32 dy = gCsPosY - y;
    f32 dz = gCsPosZ - z;

    dx *= dx;
    dy *= dy;
    dz *= dz;
    return sqrtf(dx + dy + dz) < radius;
}



s32 csPlayerNearPos(s16 radius) {
    u8 i;
    CsPlayerPosView *player;

    for (i = 0; i < gViewportCount; i++) {
        player = (CsPlayerPosView *)gPlayerSlots + i;
        if (player->active != 0) {
            Actor *actor = player->actor;
            if (csPosWithinRadius(radius, actor->x, actor->y, actor->z)) {
                return 1;
            }
        }
    }
    return 0;
}

s32 csPlayerSavedPosNearPos(s16 radius) {
    u8 i;
    CsPlayerPosView *player;

    for (i = 0; i < gViewportCount; i++) {
        player = (CsPlayerPosView *)gPlayerSlots + i;
        if (player->active != 0 && csPosWithinRadius(radius, player->camX, player->camY, player->camZ)) {
            return 1;
        }
    }
    return 0;
}


s32 csSpawnNodeNearPos(s16 radius, s16 minNodeIndex, s16 maxNodeIndex) {
    s16 i;
    Actor *actor;

    for (i = minNodeIndex; i <= maxNodeIndex; i++) {
        if (spawnNodeHasActor(i)) {
            actor = spawnNodeActivate(i, 0);
            if (actor != NULL) {
                if (csPosWithinRadius(radius, actor->x, actor->y, actor->z)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


void csSnapToGround(s16 mode, s16 csId) {
    s32 pad;
    f32 y;

    switch (mode) {
    case 0:
        y = gCsPosY;
        if (collisionCheckGroundAtPoint(gCsPosX, gCsPosZ, &y)) {
            gCsPosY = y + gCsGroundOffset;
        }
        break;
    case 1:
        break;
    }
}

s32 csCompareVar(f32 *varsArray, s16 packedParam, s16 compareValue) {
    u8 varIndex;
    u8 mode;
    s32 ret;
    f32 value;
    f32 threshold;

    ret = 0;
    mode = packedParam & 0xFF;
    varIndex = (packedParam >> 8) & 0xFF;
    value = varsArray[varIndex];
    switch (mode) {
    case 0:
        threshold = compareValue / 10.0f;
        if (((threshold < value) ? (value - threshold) : (threshold - value)) < 0.05) {
            ret = 1;
        }
        break;
    case 1:
        if (compareValue / 10.0f < value) {
            ret = 1;
        }
        break;
    case 2:
        if (value < compareValue / 10.0f) {
            ret = 1;
        }
        break;
    }
    return ret;
}


s32 csEvaluateParamCondition(s16 packedParam, s16 compareValue) {
    f32 value;
    f32 threshold;
    s32 ret;
    u8 mode;

    threshold = compareValue / 10.0f;
    ret = 0;
    switch ((u8)((packedParam >> 8) % 255)) {
    case 0:
        value = gCsPrevRotX;
        break;
    case 1:
        value = gCsPrevRotY;
        break;
    case 2:
        value = gCsPrevRotZ;
        break;
    }
    mode = packedParam & 0xFF;
    switch (mode) {
    case 0:
        if (((threshold < value) ? (value - threshold) : (threshold - value)) != 0.1) {
            ret = 1;
        }
        break;
    case 1:
        if (threshold < value) {
            ret = 1;
        }
        break;
    case 2:
        if (value < threshold) {
            ret = 1;
        }
        break;
    }
    return ret;
}


void csSetRot(s16 modeAndAxis, s16 rotValue, CsState *cs, s16 csId, u8 isRelative) {
    f32 v;
    u8 mode;
    u8 axis;

    mode = modeAndAxis & 0xFF;
    axis = (modeAndAxis >> 8) & 0xFF;
    v = rotValue / 10.0f;
    if (mode == 1) {
        v = cs->vars[rotValue];
    }
    switch (axis) {
    case 0:
        if (isRelative == 1) {
            gCsRotX += v;
        } else {
            gCsRotX = v;
        }
        break;
    case 1:
        if (isRelative == 1) {
            gCsRotY += v;
        } else {
            gCsRotY = v;
        }
        break;
    case 2:
        if (isRelative == 1) {
            gCsRotZ += v;
        } else {
            gCsRotZ = v;
        }
        break;
    }
}

void csSetPos(s16 modeAndAxis, s16 posValue, CsState *cs, s16 csId, u8 isRelative) {
    f32 v;
    u8 mode;
    u8 axis;

    mode = modeAndAxis & 0xFF;
    axis = (modeAndAxis >> 8) & 0xFF;
    v = posValue / 10.0f;
    if (mode == 1) {
        v = cs->vars[posValue];
    }
    switch (axis) {
    case 0:
        if (isRelative == 1) {
            gCsPosX += v;
        } else {
            gCsPosX = v;
        }
        break;
    case 1:
        if (isRelative == 1) {
            gCsPosY += v;
        } else {
            gCsPosY = v;
        }
        break;
    case 2:
        if (isRelative == 1) {
            gCsPosZ += v;
        } else {
            gCsPosZ = v;
        }
        break;
    }
}

extern EffectGridAsset gEffectSpriteSparklePurple;

void csCmdSpawnSparkAndLight(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < 1; i++) {
        x = (randomLcgNext() / 10000 % 200) / 10.0 - 10.0;
        y = (randomLcgNext() / 10000 % 200) / 10.0 - 7.0;
        z = (randomLcgNext() / 10000 % 200) / 10.0 - 10.0;
        effectSetDepth(1);
        effectSetDuration(2);
        effectSetSpeed(0x64);
        effectSetCallback(effectSinkBySpeedUpdate);
        effectCreateAtPosition(&gEffectSpriteSparklePurple, 0.5f, gCsPosX + x, gCsPosY + y, gCsPosZ + z);
    }
    lightAdd(gCsPosX, gCsPosY, gCsPosZ, 0.0f, 0.0f, 0.0f, 300.0f, 0, 0xA6, 0x30, 0xFF);
}
