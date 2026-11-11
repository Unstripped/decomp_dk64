#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/127B00.h"
#include "proto/global/133A90.h"
#include "proto/global/136820.h"
#include "proto/global/15050.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/2F550.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/79890.h"
#include "proto/global/7A510.h"
#include "proto/global/7BBD0.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/8D3E0.h"
#include "proto/global/90D80.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"

typedef struct ActorMovePayload2D {
    f32 x;
    f32 z;
    u8 priority;
    u8 skipArcCheck;
} ActorMovePayload2D;

typedef struct ActorMovePayload3D {
    f32 x;
    f32 y;
    f32 z;
    u8 priority;
    u8 skipArcCheck;
} ActorMovePayload3D;

typedef struct ActorStatePayload {
    s16 unk0;
    f32 unk4;
    s16 unk8;
} ActorStatePayload;

typedef struct ActorRiderPayload {
    f32 x;
    f32 y;
    f32 z;
    s32 pointIndex;
    u8 unk10;
} ActorRiderPayload;

typedef struct ActorEventPayload {
    f32 x;
    f32 y;
    f32 z;
    s16 unkC;
    s16 unkE;
} ActorEventPayload;

extern u16 D_8074D624[];
extern u8 D_807F94B4;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern ActorGlobalState gActorGlobalState;
extern PlayerState *gActivePlayerState;
extern u8 D_807FBE08;
extern u8 D_807FBE09;
extern Actor *D_807FBE10[];
extern s16 D_807FBF10;
extern ActorQueueEntry D_807FBF18[16];
extern s16 D_807FBFD8;
extern ActorCallbackNode *D_807FBFE0[];
extern s32 D_807FBFF0[];
extern s16 D_807FC3F0;

static void actorStub7CA80_00(void);
static void actorStub7CA80_01(void);
static void actorStub7CA80_02(void);
static void actorStub7CA80_03(void);
static void actorStub7CA80_04(void);
static void actorStub7CA80_05(void);
static void actorStub7CA80_06(void);

typedef struct Struct807FB630 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
    s32 unk8;
} Struct807FB630;

typedef struct Struct807FB7B0 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Struct807FB7B0;

typedef struct ActorAssetHeader {
    s32 unk0;
    s32 soundTableOffset;
    s32 animTableOffset;
    s32 indexTableOffset;
} ActorAssetHeader;

extern Struct807FB630 D_807FB630[32];
extern Struct807FB7B0 D_807FB7B0[32];
extern s16 D_807FBB30;
extern s16 D_807FBB32;
extern ActorAssetHeader *gActorScriptAsset;
extern void *gActorScriptIndexTable;
extern void *gActorScriptAnimTable;
extern void *gActorScriptSoundTable;
extern s32 D_807FBB38;

void actorInit(void) {
    u16 i;

    for (i = 0; i < 32; i++) {
        D_807FB630[i].unk0 = 0;
        D_807FB630[i].unk2 = 0;
        D_807FB630[i].unk4 = 0;
    }
    D_807FBB30 = 0;

    for (i = 0; i < 32; i++) {
        D_807FB7B0[i].unk0 = 0xFFFF;
        D_807FB7B0[i].unk4 = 0;
        D_807FB7B0[i].unk8 = 0;
    }
    D_807FBB32 = 0;

    gActorScriptAsset = assetLoad(0xD, 0, 1, 1);
    gActorScriptIndexTable = (void *)(gActorScriptAsset->indexTableOffset + (s32)gActorScriptAsset);
    gActorScriptAnimTable = (void *)(gActorScriptAsset->animTableOffset + (s32)gActorScriptAsset);
    gActorScriptSoundTable = (void *)(gActorScriptAsset->soundTableOffset + (s32)gActorScriptAsset);

    for (i = 0; i < 64; i++) {
        gActiveActors[i].actor = NULL;
        gActiveActors[i].unk4 = 0;
    }
    gActiveActorCount = 0;

    actorTableClear();

    D_807FBB38 = 0;
    D_807FBE09 = 0;
    D_807FBFD8 = 0;
    gActivePlayerActor = NULL;
}

void func_80677EC8(s32 unused) {
}

typedef struct ActorSpawnInfo {
    s32 type;
    s32 spawnArg;
    s32 scriptId;
    f32 x;
    f32 y;
    f32 z;
    s16 yaw;
    s16 spawnTimer;
    s32 spawnData;
} ActorSpawnInfo;
extern u8 D_8074D8D4[];
extern s32 (*D_8074DA30[])(s32 *);

s32 actorSpawnFromInfo(ActorSpawnInfo *info) {
    u8 initIndex;
    if (actorAllocate((u16)info->type)) {
        initIndex = D_8074D8D4[info->type];
        if (D_8074DA30[initIndex](&info->spawnArg)) {
            gSpawnedActor->x = info->x;
            gSpawnedActor->y = info->y;
            gSpawnedActor->z = info->z;
            gSpawnedActor->spawnData = info->spawnData;
            gSpawnedActor->yaw = info->yaw;
            gSpawnedActor->spawnTimer = info->spawnTimer;
            if (info->scriptId != 0) {
                actorScriptStart(gSpawnedActor, info->scriptId);
            }
            return 1;
        }
    }
    return 0;
}
s32 actorSpawn(s32 type, s32 spawnArg) {
    u8 initIndex;
    if (actorAllocate((u16)type)) {
        initIndex = D_8074D8D4[type];
        if (D_8074DA30[initIndex](&spawnArg)) {
            return 1;
        }
    }
    return 0;
}

s32 func_80678014(s32 type) {
    if (actorAllocate(type & 0xFFFF) != 0) {
        actorInitFloorAttachment(0);
        return 1;
    }
    return 0;
}

extern u16 *D_8074E218[];
extern u16 D_8074DA58[];
extern u32 gGlobalOverlayFlags;
extern u16 D_80748D4A;
extern u16 D_807FBB3E;

s32 actorAllocate(type)
u16 type;
{
    Actor *actor;
    u16 *types;
    void **ptrArray;
    u8 *dataPtr;
    u16 headerSize;
    u16 totalDataSize;

    types = D_8074E218[type];
    headerSize = 0x174;
    totalDataSize = 0;
    if (*types != 0) {
        do {
            if (headerSize) {}  // FAKE: raises headerSize priority so it gets a1 (tds a2)
            totalDataSize += D_8074DA58[*types];
            headerSize += 4;
            types++;
        } while (*types != 0);
    }
    totalDataSize += (u16)((headerSize + 7) & 0xFFF8);
    actor = heapAlloc(totalDataSize);
    if (actor != NULL) {
        heapClearBlock(actor);
        types = D_8074E218[type];
        ptrArray = (void **)&actor->customState;
        dataPtr = (u8 *)actor + ((u16)((headerSize + 7) & 0xFFF8));
        if (*types != 0) {
            do {
                *ptrArray++ = dataPtr;
                dataPtr += D_8074DA58[*types++];
            } while (*types != 0);
        }
        actor->callbacks = NULL;
        actor->callbackMask = -1;
        actor->unk144 = 2;
        actor->attachMode = 0;
        actor->unkF8 = 0x50;
        actor->flags = 0x58144;
        actor->renderFlags = 0;
        actor->alpha = 0xFF;
        actor->actorType = type;
        if (gGlobalOverlayFlags & 0x100) {
            actor->drawDistance = 0x7D0;
        } else {
            actor->drawDistance = 0x1F4;
        }
        actor->flags2 = 0;
        actor->unk156 = 0;
        actor->unk78[0] = 0;
        actor->contactFlags = actor->prevContactFlags = 1;
        actor->interactionType = 1;
        actor->riderList = NULL;
        actor->floorContact = NULL;
        actor->parentActor = NULL;
        actor->soundSlots[0] = -1;
        actor->soundSlots[1] = -1;
        actor->floorTriangle = NULL;
        actor->chunkIndex = -1;
        actor->spawnData = NULL;
        actor->unk148 = NULL;
        actor->unk14C = NULL;
        actor->unkD4 = &D_80748D4A;
        actor->unk146 = -1;
        actor->collisionFlags = D_8074D624[type];
        actor->floorTiltPitch = 0x400;
        actor->floorNodeId = 0;
        actor->unkCD = 0;
        actor->cullMarginX = 0;
        actor->cullMarginY = 0;
        actor->tintA = 0xF;
        actor->unkCE = 0;
        actor->unkB0[0] = -1;
        actor->instanceId = D_807FBB38;
        D_807FBB38++;
        actorTableInsert(actor);
        actorInitHealth(actor);
        gActiveActors[gActiveActorCount].actor = actor;
        gActiveActors[gActiveActorCount].unk4 = 0;
        D_807FBB3E = gActiveActorCount;
        gActiveActorCount++;
        gSpawnedActor = actor;
        return 1;
    }
    return 0;
}

void actorDespawn(Actor *actor) {
    actorListRemoveByActor(actor);
    actorQueueOrDespawn(actor);
}

s32 actorQueueOrDespawn(Actor *actor) {
    s32 i;

    if (D_807FBE09 != 0) {
        if (D_807FBF10 == 0x40) {
            faultSetMessage(0xC, 0, 0, 0);
        }
        if (actor == gCurrentActor) {
            D_807FBE08 = 1;
        }
        for (i = 0; i < D_807FBF10; i++) {
            if (actor == D_807FBE10[i]) {
                return 0;
            }
        }
        D_807FBE10[D_807FBF10] = actor;
        D_807FBF10++;
    } else {
        actorFreeImmediate(actor);
    }
    return 1;
}

void actorFlushDespawnQueue(void) {
    s32 i;
    for (i = 0; i < D_807FBF10; i++) {
        actorFreeImmediate(D_807FBE10[i]);
    }
    D_807FBF10 = 0;
}

void actorRegisterActive(Actor *actor) {
    gActiveActors[gActiveActorCount].actor = actor;
    gActiveActors[gActiveActorCount].unk4 = 0;
    gActiveActorCount++;
}

void actorDeregisterActive(Actor *actor) {
    s16 i;

    sfxStopSlotSound(actor, 0);
    sfxStopSlotSound(actor, 1);
    i = 0;
    if (actor != gActiveActors[0].actor && gActiveActorCount > 0) {
        do {
            i++;
            if (actor == gActiveActors[i].actor) {
                break;
            }
        } while (i < gActiveActorCount);
    }
    if (--gActiveActorCount != 0) {
        gActiveActors[i].actor = gActiveActors[gActiveActorCount].actor;
        gActiveActors[i].unk4 = gActiveActors[gActiveActorCount].unk4;
    }
    func_8062D26C(actor);
    actor->floorTriangle = NULL;
}

void actorDespawnByOwner(s32 owner) {
    s32 i;

    D_807FBE09 = 1;
    D_807FBF10 = 0;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (owner == (s32)actor->parentActor) {
            actorDespawn(actor);
            actor->parentActor = NULL;
        }
    }
    D_807FBE09 = 0;
    actorFlushDespawnQueue();
}

void actorFreeImmediate(Actor *actor) {
    s16 i;
    Actor *parent;

    if (actor->animState != NULL) {
        controllerAnimFree(actor);
    }
    parent = actor->parentActor;
    if (parent != NULL) {
        actorAppendCallback(parent, actor, 0x80000, 0, 0, NULL);
    }
    for (i = 0; i < gActiveActorCount; i++) {
        if (actor == gActiveActors[i].actor->parentActor) {
            gActiveActors[i].actor->parentActor = NULL;
        }
    }
    i = 0;
    effectFreeByResource(actor);
    pathPlaybackStopForActor(actor);
    sfxStopSlotSound(actor, 0);
    sfxStopSlotSound(actor, 1);
    if (gActiveActors[0].actor != actor) {
        if (gActiveActorCount > 0) {
            do {
                i++;
                if (gActiveActors[i].actor == actor) {
                    break;
                }
            } while (i < gActiveActorCount);
        }
    }
    if (i != gActiveActorCount) {
        if (--gActiveActorCount != 0) {
            gActiveActors[i].actor = gActiveActors[gActiveActorCount].actor;
            gActiveActors[i].unk4 = gActiveActors[gActiveActorCount].unk4;
        }
    }
    actorSub140Free(actor->collision);
    proxPathRemoveActor(actor);
    if (actor->floorContact != NULL) {
        heapFree(actor->floorContact);
    }
    if (actor->unk148 != NULL) {
        heapFree(actor->unk148);
    }
    if (actor->unk14C != NULL) {
        heapFree(actor->unk14C);
    }
    func_8062D26C(actor);
    if (actor->actorType != 0x12B) {
        resQueueRemove(actor);
    }
    renderCallbacksDisableForActor(actor);
    actorTableRemove(actor);
    heapFree(actor);
}

void actorUpdateSpawnsWrapper(void) {
    actorListUpdateSpawns();
}

static void actorStub7CA80_00(void) {}
static void actorStub7CA80_01(void) {}
static void actorStub7CA80_02(void) {}
static void actorStub7CA80_03(void) {}
static void actorStub7CA80_04(void) {}
static void actorStub7CA80_05(void) {}
static void actorStub7CA80_06(void) {}

ActorCallbackNode *D_807FBFE0[4];

void actorGlobalCallbacksReset(void) {
    s32 i;

    D_807FBE09 = 1;
    D_807FBF10 = 0;
    for (i = 0; i < 4; i++) {
        D_807FBFE0[i] = NULL;
    }
    actorUpdateActiveList(1);
    actorUpdateActiveList(2);
    actorGlobalCallbacksDispatchAndFree(1);
    actorUpdateLightingAndFog();
    D_807FBE09 = 0;
    actorFlushDespawnQueue();
    actorDelayedCallbacksTick();
}

extern void (*D_8074C0A0[])(void);

extern u16 D_807FBB3C;

void actorUpdateActiveList(u8 flags) {
    s32 i;

    for (i = D_807FBB3C = 0; i < gActiveActorCount; i = D_807FBB3C = i + 1) {
        D_807FBE08 = 0;
        gCurrentActor = gActiveActors[i].actor;
        if ((flags == 1 && !(gCurrentActor->flags & 0x100000)) || (flags == 2 && (gCurrentActor->flags & 0x100000))) {
            actorPreTick(gCurrentActor);
            D_8074C0A0[gCurrentActor->actorType]();
            actorPostTick(gCurrentActor);
        }
        i = D_807FBB3C;
    }
}

void actorUpdateWhilePaused(void) {
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        D_807FBFE0[j] = NULL;
    }
    for (i = D_807FBB3C = 0; i < gActiveActorCount; i = ++D_807FBB3C) {
        gCurrentActor = gActiveActors[i].actor;
        if (gCurrentActor->renderFlags & 2) {
            actorPreTick(gCurrentActor);
            D_8074C0A0[gCurrentActor->actorType]();
            actorPostTick(gCurrentActor);
        }
        if (gCurrentActor->sub4 != NULL) {
            actorCheckWorldBounds(gCurrentActor);
        }
    }
    actorGlobalCallbacksDispatchAndFree(1);
    actorUpdateLightingAndFog();
}

void actorUpdateLightingAndFog(void) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x08000000) && (actor->flags & 0x500) && (actor->flags & 0x4000)) {
            actorCheckWorldBounds(actor);
        }
        actor->flags &= ~0x100;
    }
}

void actorPreTick(Actor *actor) {
    collisionClearFlags();
    if (actor->collisionFlags & 1) {
        playerSetActiveGlobals(actor);
    }
    actor->prevX = actor->x;
    actor->prevY = actor->y;
    actor->prevZ = actor->z;
    actor->prevSpeedXZ = actor->speedXZ;
    D_807F94B4 = 0;
    if (actor->collision != NULL) {
        actor->collision->unk68 = 0;
    }
    actorRiderListFree(actor);
    if (actor == gActivePlayerActor) {
        actorCollisionCheckBoundingBoxes(actor);
    } else {
        actorInitDamage(actor);
    }
    actorDispatchCallbacks(actor);
    if (actor == gActivePlayerActor) {
        playerStateDispatchQueuedCallback();
    }
    if (actor->unk144 & 4) {
        actorUpdateMovementFlags(actor);
    } else if (actor->collision != NULL) {
        actor->collision->unk6C = 0;
    }
    if (actor->attachMode != 0) {
        actorUpdateSubnodeRotationAndMtx(actor);
    }
}

void actorPostTick(Actor *actor) {
    if ((void *)actorInitCollisionFromModel == (void *)D_8074DA30[D_8074D8D4[actor->actorType]]) {
        guTranslateF(actor->modelMtx, actor->x, actor->y, actor->z);
    }
    actorUpdatePositionAndSub140(actor);
    actorUpdateArcBounds(actor);
    if (!(actor->flags & 0x08000000)) {
        actor->flags &= ~0x200;
        if (actor->sub4 != NULL) {
            controllerStepMotionWindows(actor);
            if (((actor->flags & 0x500) || actor->unk156 != 0) && !(actor->flags & 0x4000)) {
                actorCheckWorldBounds(actor);
            }
        }
    }
    actorUpdatePeakHeight(actor);
    actorUpdateModelMatrices(actor);
    actorGlobalCallbacksDispatchAndFree(0);
    actorDispatchCollisionResults(actor);
    actorFreeCallbackList(actor);
    actorUpdateEffects(actor);
    animListUpdate(actor);
    actor->flags |= 0x10;
}

void actorCheckBoundsAndMotion(Actor *actor) {
    controllerStepMotionWindows(actor);
    if (actor->flags & 0x500) {
        actorCheckWorldBounds(actor);
    }
}

void actorUpdatePeakHeight(Actor *actor) {
    f32 y = actor->y;

    if (actor->prevY < y) {
        actor->peakY = y;
        return;
    }
    if (actor->contactFlags & 5) {
        if (actor->prevContactFlags & 5) {
            actor->peakY = y;
            return;
        }
        actor->prevPeakY = actor->peakY;
    }
}

extern u8 gCurrentPlayerIndex;

void actorUpdateArcBounds(Actor *actor) {
    u8 arcFlags;

    if ((actor->unk144 & 4) && (D_807FBE08 == 0)) {
        if (actor->flags & 0x10000) {
            actor->hasArcBounds = 0;
            actor->collisionHit = 0;
        }
        actor->hasArcBounds |= actorClearTargetAngle(actor, &actor->arcYawMin, &actor->arcYawMax, &arcFlags);
        arcFlags |= gActorGlobalState.unkE5;
        if (arcFlags != 0) {
            if (!(actor->contactFlags & 0x10)) {
                actor->contactFlags |= 0x10;
                if (actor == gActivePlayerActor) {
                    playerStateQueueCallback(4, 0, gCurrentPlayerIndex);
                }
            }
        }
        if (arcFlags == 0) {
            actor->contactFlags &= ~0x10;
        }
    } else {
        actor->hasArcBounds = 0;
        actor->collisionHit = 0;
        actor->contactFlags &= ~0x10;
    }
}

void actorRiderListFree(Actor *actor) {
    if (actor->riderList != NULL) {
        heapFree(actor->riderList);
        actor->riderList = NULL;
    }
}

void actorRiderListAdd(Actor *actor, Actor *item) {
    if (actor->riderList == NULL) {
        actor->riderList = heapAlloc(sizeof(ActorList));
        actor->riderList->count = 0;
    }
    if (actor->riderList->count != 4) {
        actor->riderList->items[actor->riderList->count] = item;
        actor->riderList->count++;
    }
}

s32 actorRiderListContains(Actor *actor, Actor *item) {
    ActorList *list = actor->riderList;
    s32 i;

    if (list == NULL) {
        return 0;
    }
    for (i = 0; i < list->count; i++) {
        if (list->items[i] == item) {
            return 1;
        }
    }
    return 0;
}

void actorRegisterGlobalCallback(ActorCallbackNode *node) {
    s32 i = 0;
    s32 found = 0;

    while ((i < 4) && (!found)) {
        if (D_807FBFE0[i] == NULL) {
            found = 1;
        } else {
            i++;
        }
    }
    if (!found) {
        faultSetMessage(0xE, 0, 0, 0);
    } else {
        D_807FBFE0[i] = node;
    }
}

void actorGlobalCallbacksDispatchAndFree(id)
u8 id;
{
    ActorCallbackNode **ptr = D_807FBFE0; do { if (((*ptr) != 0) && ((*ptr)->unk4 == id)) { ((void (*)(void *)) (*ptr)->callback)(&(*ptr)->source); heapFree(*ptr); *ptr = 0; } ptr++; } while (ptr != ((ActorCallbackNode **) (&D_807FBFF0))); // LAYOUT: one-line statement line coordinates steer mirrored-pair scheduling
}

void actorFreeCallbackList(Actor *actor) {
    ActorCallbackNode *node = actor->callbacks;
    ActorCallbackNode *next;

    if (node != NULL) {
        actor->callbacks = NULL;
    }
    while (node != NULL) {
        next = node->next;
        if (node->unk10 != NULL) {
            heapFree(node->unk10);
        }
        heapFree(node);
        node = next;
    }
}

void actorCallbackMaskEnable(Actor *actor, s32 mask) {
    actor->callbackMask |= mask;
}

void actorCallbackMaskDisable(Actor *actor, s32 mask) {
    actor->callbackMask &= ~mask;
}

void actorAppendCallback(Actor *actor, Actor *source, s32 type, u8 subtype, s32 ownsPayload, void *payload) {
    s32 pad;
    ActorCallbackNode **link;
    ActorCallbackNode *prev;
    ActorCallbackNode *curr;
    ActorCallbackNode *node;

    prev = NULL;
    if (actorTableContains(actor)) {
        curr = actor->callbacks;
        link = &actor->callbacks;
        if (curr != NULL) {
            do {
                link = &curr->next;
                prev = curr;
                curr = curr->next;
            } while (curr != NULL);
        }
        node = actorAllocCallbackNode(source, type, subtype, ownsPayload, payload);
        *link = node;
        node->prev = prev;
    }
}

void actorQueueDelayedCallback(Actor *target, Actor *source, s32 type, u8 subtype, s32 ownsPayload, void *payload, s32 delay) {
    if (D_807FBFD8 == 16) {
        faultSetMessage(0xF, 0, 0, 0);
    }
    D_807FBF18[D_807FBFD8].node = actorAllocCallbackNode(source, type, subtype, ownsPayload, payload);
    D_807FBF18[D_807FBFD8].target = target;
    D_807FBF18[D_807FBFD8].arg6 = delay;
    D_807FBFD8++;
}

void actorDelayedCallbacksTick(void) {
    s32 i;
    Actor *actor;
    ActorCallbackNode *node;
    ActorCallbackNode *curr;
    ActorCallbackNode **link;
    ActorCallbackNode *prev;
    s32 changed;

    for (i = 0; i < D_807FBFD8; i++) {
        D_807FBF18[i].arg6--;
        if (D_807FBF18[i].arg6 == 0) {
            actor = D_807FBF18[i].target;
            if (actorTableContains(actor)) {
                curr = actor->callbacks;
                link = &actor->callbacks;
                prev = NULL;
                if (curr != NULL) {
                    do {
                        link = &curr->next;
                        prev = curr;
                        curr = curr->next;
                    } while (curr != NULL);
                }
                *link = D_807FBF18[i].node;
                (*link)->prev = prev;
            } else {
                node = D_807FBF18[i].node;
                if (node->unk10 != NULL) {
                    heapFree(node->unk10);
                }
                heapFree(node);
            }
        }
    }
    do {
        changed = 0;
        for (i = 0; i < D_807FBFD8; i++) {
            if (D_807FBF18[i].arg6 == 0) {
                D_807FBF18[i].node = D_807FBF18[D_807FBFD8 - 1].node;
                D_807FBF18[i].target = D_807FBF18[D_807FBFD8 - 1].target;
                D_807FBF18[i].arg6 = D_807FBF18[D_807FBFD8 - 1].arg6;
                D_807FBFD8--;
                changed = 1;
            }
        }
    } while (changed);
}

ActorCallbackNode *actorAllocCallbackNode(Actor *source, s32 type, u8 subtype, s32 ownsPayload, void *payload) {
    ActorCallbackNode *node = heapAlloc(sizeof(ActorCallbackNode));

    node->callback = (void *)type;
    node->unk4 = subtype;
    node->source = source;
    node->unkC = ownsPayload;
    node->unk10 = payload;
    node->next = NULL;
    return node;
}

typedef struct ActorSurfacePayload {
    s16 unk0;
    s16 unk2;
    u8 unk4[0xC];
    u8 unk10[0x24];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} ActorSurfacePayload;

typedef struct ActorHitPayload {
    u8 unk0[0xC];
    u8 unkC[0x24];
    s32 unk30;
    s32 unk34;
    s32 unk38;
} ActorHitPayload;

void actorDispatchCallbacks(Actor *actor) {
    s16 pad[2];
    s32 mask;
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    s32 bestType;
    u8 pad1;
    u8 skipArcCheck;
    s8 bestPriority;
    s32 priority10;
    s32 priority20;
    ActorRiderPayload *riderPayload;
    ActorHitPayload *hit;
    ActorSurfacePayload *surfacePayload;
    ActorCallbackNode *sorted;
    f32 *pointPair;
    ActorEventPayload *eventPayload;
    PlayerState *playerState;
    ActorStatePayload *viewPayload;
    ActorMovePayload2D *payload10;
    ActorMovePayload3D *payload20;
    f32 *vecPayload;
    ActorStatePayload *statePayload;
    ActorSub140 *collision;
    s32 *collisionValue;
    Actor *player;
    ActorCallbackNode *node;

    bestPriority = -1;
    actorGlobalStateClearEvents();
    sorted = actorCallbackListSort(actor->callbacks);
    actor->callbacks = sorted;
    node = sorted;
    mask = actor->callbackMask;
    if (sorted != NULL) {
        do {
            if ((s32)node->callback & mask) {
                switch ((s32)node->callback) {
                case 0x8000:
                    actorCollisionProcessHit(actor, node);
                    if (((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.bossFightPhase == 0xA)) && (actor->collisionFlags & 1)) {
                        playerHandleDamageReaction(actor, gActorGlobalState.targetActor, (gActorGlobalState.bossFightPhase == 0xA));
                    }
                    break;
                case 0x2:
                    switch (node->unk4) {
                    case 0:
                        gActorGlobalState.unk16 = 1;
                        if (actor == gActivePlayerActor) {
                            playerStateQueueCallback(0x10, NULL, gCurrentPlayerIndex);
                        }
                        break;
                    case 1:
                        gActorGlobalState.unk17 = 1;
                        if (actor == gActivePlayerActor) {
                            playerStateQueueCallback(0xE, node->source, gCurrentPlayerIndex);
                        }
                        break;
                    case 2:
                        gActorGlobalState.unk18 = 1;
                        if (actor == gActivePlayerActor) {
                            playerStateQueueCallback(0x12, NULL, gCurrentPlayerIndex);
                        }
                        break;
                    case 3:
                        gActorGlobalState.unk19 = 1;
                        if (actor == gActivePlayerActor) {
                            playerStateQueueCallback(0x13, NULL, gCurrentPlayerIndex);
                        }
                        break;
                    case 6:
                        gActorGlobalState.unk1B = 1;
                        if (actor == gActivePlayerActor) {
                            playerStateQueueCallback(0x36, node->source, gCurrentPlayerIndex);
                        }
                        break;
                    case 4:
                    case 5:
                        if (actor == gActivePlayerActor) {
                            if (node->unk4 == 4) {
                                playerStateQueueCallback(0x2B, node->source, gCurrentPlayerIndex);
                            } else {
                                playerStateQueueCallback(0x32, node->source, gCurrentPlayerIndex);
                            }
                            player = node->source;
                            if ((player != NULL) && (player->collisionFlags & 2)) {
                                playerState = player->customState;
                                playerState->unk1A |= 0x100;
                            }
                        }
                        break;
                    }
                    break;
                case 0x8:
                    playerHandleDamageReaction(actor, node->source, 0);
                    break;
                case 0x4:
                    playerHandleDamageReaction(actor, node->source, 1);
                    break;
                case 0x800:
                    actor->unk144 = node->unk4;
                    gActorGlobalState.unk90 = 1;
                    break;
                case 0x400:
                    viewPayload = node->unk10;
                    gActivePlayerState->unk70 = viewPayload->unk0;
                    gActivePlayerState->unk74 = viewPayload->unk4;
                    gActivePlayerState->unk6C = viewPayload->unk8;
                    gActorGlobalState.unk1A = 1;
                    if (actor == gActivePlayerActor) {
                        playerStateQueueCallback(0x17, node->source, gCurrentPlayerIndex);
                    }
                    break;
                case 0x10:
                    payload10 = node->unk10;
                    priority10 = payload10->priority;
                    if (bestPriority < priority10) {
                        targetX = payload10->x;
                        bestPriority = priority10;
                        targetZ = payload10->z;
                        bestType = (s32)node->callback;
                        skipArcCheck = payload10->skipArcCheck;
                    }
                    break;
                case 0x20:
                    payload20 = node->unk10;
                    priority20 = payload20->priority;
                    if (bestPriority < priority20) {
                        targetX = payload20->x;
                        bestPriority = priority20;
                        targetY = payload20->y;
                        targetZ = payload20->z;
                        bestType = (s32)node->callback;
                        skipArcCheck = payload20->skipArcCheck;
                    }
                    break;
                case 0x100000:
                    vecPayload = node->unk10;
                    gActorGlobalState.unkD8 = vecPayload[0];
                    gActorGlobalState.unkDC = vecPayload[1];
                    gActorGlobalState.unkE0 = vecPayload[2];
                    gActorGlobalState.unkE4 = 1;
                    gActorGlobalState.unkEC = node->source;
                    break;
                case 0x1000:
                    gActorGlobalState.unk1C = 1;
                    gActorGlobalState.unk20 = node->source;
                    break;
                case 0x4000:
                    statePayload = node->unk10;
                    gActorGlobalState.unk2C = 1;
                    gActorGlobalState.unk30 = statePayload->unk4;
                    gActorGlobalState.unk34 = statePayload->unk8;
                    gActorGlobalState.unk36 = statePayload->unk0;
                    break;
                case 0x2000:
                    if (node->unk4 != 0) {
                        gActorGlobalState.unk24 = 1;
                    } else {
                        gActorGlobalState.unk25 = 1;
                    }
                    gActorGlobalState.unk28 = node->source;
                    break;
                case 0x80:
                    actor->flags |= 8;
                    if (actor == gActivePlayerActor) {
                        playerStateQueueCallback(0x16, node->source, gCurrentPlayerIndex);
                    }
                    break;
                case 0x40:
                    if (node->unk4 != 0) {
                        actor->flags |= 4;
                    } else {
                        actor->flags &= ~4;
                    }
                    break;
                case 0x1:
                    riderPayload = node->unk10;
                    if (actorTableContains(node->source) != 0 && gActorGlobalState.unk39 != 4) {
                        gActorGlobalState.unk3C[gActorGlobalState.unk39][0] = riderPayload->x;
                        gActorGlobalState.unk3C[gActorGlobalState.unk39][1] = riderPayload->y;
                        gActorGlobalState.unk3C[gActorGlobalState.unk39][2] = riderPayload->z;
                        gActorGlobalState.unk6C[gActorGlobalState.unk39] = riderPayload->pointIndex;
                        gActorGlobalState.unk7C[gActorGlobalState.unk39] = node->source;
                        gActorGlobalState.unk8C[gActorGlobalState.unk39] = riderPayload->unk10;
                        gActorGlobalState.unk39++;
                        actorRiderListAdd(actor, node->source);
                    }
                    break;
                case 0x20000:
                    hit = node->unk10;
                    if (gActorGlobalState.unk1F8 != 4) {
                        memcpy(gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unk0, hit->unk0, 0xC);
                        memcpy(gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unkC, hit->unkC, 0x24);
                        gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unk30 = hit->unk30;
                        gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unk34 = hit->unk34;
                        gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unk38 = hit->unk38;
                        gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unk3C = node->source;
                        gActorGlobalState.unk1F8++;
                    }
                    break;
                case 0x10000:
                    surfacePayload = node->unk10;
                    gActorGlobalState.unk91 = 1;
                    gActorGlobalState.unk92 = surfacePayload->unk0;
                    gActorGlobalState.unk94 = surfacePayload->unk2;
                    memcpy(gActorGlobalState.unk98, surfacePayload->unk4, 0xC);
                    memcpy(gActorGlobalState.unkA4, surfacePayload->unk10, 0x24);
                    gActorGlobalState.unkC8 = surfacePayload->unk34;
                    gActorGlobalState.unkCC = node->source;
                    gActorGlobalState.unkD0 = surfacePayload->unk38;
                    gActorGlobalState.unkD4 = surfacePayload->unk3C;
                    break;
                case 0x40000:
                    collisionValue = node->unk10;
                    collision = actor->collision;
                    if (collision != NULL) {
                        collision->unk68 = *collisionValue;
                    }
                    break;
                case 0x80000:
                    gActorGlobalState.unk38 = 1;
                    break;
                case 0x200000:
                    pointPair = node->unk10;
                    gActorGlobalState.unkF0 = pointPair[0];
                    gActorGlobalState.unkF4 = pointPair[1];
                    break;
                case 0x400000:
                    gActorGlobalState.unkE8 = node->unk4;
                    gActorGlobalState.unkE5 = 1;
                    break;
                case 0x1000000:
                    if (gActorGlobalState.unk254 < 8) {
                        gActorGlobalState.unk258[gActorGlobalState.unk254] = node->unk4;
                        gActorGlobalState.unk278[gActorGlobalState.unk254] = node->unk10;
                        gActorGlobalState.unk254++;
                    }
                    break;
                case 0x800000:
                    eventPayload = node->unk10;
                    gActorGlobalState.unk4 = eventPayload->x;
                    gActorGlobalState.unk8 = eventPayload->y;
                    gActorGlobalState.unkC = eventPayload->z;
                    gActorGlobalState.unk10 = eventPayload->unkC;
                    gActorGlobalState.unk12 = eventPayload->unkE;
                    gActorGlobalState.unk2 = 1;
                    gActorGlobalState.unk14 = node->unk4;
                    break;
                case 0x2000000:
                    gActorGlobalState.unk0 = 1;
                    gActorGlobalState.unk1[0] = node->unk4;
                    break;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
    if ((bestPriority != -1) && ((skipArcCheck == 1) || (actorCheckPointInAngleArc(actor, targetX, targetZ) != 0))) {
        switch (bestType) {
        case 16:
            actor->x = targetX;
            actor->z = targetZ;
            return;
        case 32:
            actor->x = targetX;
            actor->y = targetY;
            actor->z = targetZ;
            break;
        }
    }
}

extern PlayerStruct *gPlayerSlots;

extern s32 D_80720E2C;
void playerHandleDamageReaction(Actor *actor, Actor *attacker, u8 heavy) {
    s32 reaction;
    s32 queueReaction;
    void *pulseCallback;
    s32 pad;
    s32 damageLevel;

    gActorGlobalState.unk15 = 1;
    if (actor == gActivePlayerActor) {
        if (!(gPlayerSlots[gActivePlayerState->playerIndex].unk2C0 == 2 && attacker != NULL && (attacker->collisionFlags & 2))) {
            reaction = 0x2E;
            queueReaction = 1;
            if (heavy != 0) {
                reaction = 0x30;
            }
            if (attacker != NULL && attacker->actorType == 0x116) {
                effectSpawnBurstParticleCluster(actor);
                switch (attacker->unk155) {
                case 1:
                    queueReaction = 0;
                    gActivePlayerState->stateFlags ^= 0x80;
                    break;
                case 2:
                    reaction = 0x27;
                    break;
                case 3:
                    effectSetDuration(0xF0);
                    effectSetDepth(1);
                    pulseCallback = &effectPulseSpinUpdate;
                    effectSetCallback(pulseCallback);
                    effectCreateAtActorBone(&D_80720E2C, 0.4f, actor, 1, 2);
                    effectSetDuration(0xF0);
                    effectSetDepth(1);
                    effectSetCallback(pulseCallback);
                    effectCreateAtActorBone(&D_80720E2C, 0.38f, actor, 5, 2);
                    effectSetDuration(0xF0);
                    effectSetDepth(1);
                    effectSetCallback(pulseCallback);
                    effectCreateAtActorBone(&D_80720E2C, 0.3f, actor, 6, 2);
                    queueReaction = 0;
                    gActivePlayerState->stateFlags |= 0x08000000;
                    break;
                }
                gActivePlayerState->unk200 = 0xF0;
            } else if (attacker != NULL && ((attacker->collisionFlags & 1) || (attacker->collisionFlags & 4) || (attacker->collisionFlags & 2))) {
                if (func_80714608(0) != 0) {
                    if (playerIsSmallerThanAttacker(actor, attacker) != 0) {
                        reaction = 0x31;
                    } else {
                        damageLevel = 1;
                        if (attacker->collisionFlags & 4) {
                            damageLevel = 3;
                        }
                        if (attacker->state != 0x28 && damageLevel < 3) {
                            reaction = 0x2B;
                        } else {
                            reaction = 0xE;
                        }
                    }
                }
            }
            if (queueReaction != 0) {
                playerStateQueueCallback((s16)reaction, (s32)attacker, gCurrentPlayerIndex);
            }
        }
    }
}

ActorCallbackNode *actorCallbackListSort(ActorCallbackNode *head) {
    ActorCallbackNode *newHead = head;
    ActorCallbackNode *curr;
    ActorCallbackNode *scan;
    s32 inserted;
    ActorCallbackNode *next;

    if (head != NULL) {
        curr = head->next;
        if (curr != NULL) {
            do {
                scan = curr->prev;
                inserted = 0;
                if (scan != NULL) {
                    do {
                        if ((s32)curr->callback >= (s32)scan->callback) {
                            inserted = 1;
                            curr->prev->next = curr->next;
                            if (curr->next != NULL) {
                                curr->next->prev = curr->prev;
                            }
                            next = scan->next;
                            scan->next = curr;
                            curr->next = next;
                            if (curr->next != NULL) {
                                curr->next->prev = curr;
                            }
                            curr->prev = scan;
                        }
                        scan = scan->prev;
                    } while ((scan != NULL) && (!inserted));
                }
                if (!inserted) {
                    curr->prev->next = curr->next;
                    if (curr->next != NULL) {
                        curr->next->prev = curr->prev;
                    }
                    curr->prev = NULL;
                    curr->next = newHead;
                    newHead->prev = curr;
                    newHead = curr;
                }
                curr = curr->next;
            } while (curr != NULL);
        }
    }
    return newHead;
}

void actorCollisionEventsCancel(s32 node, u8 event) {
    s32 i;

    for (i = 0; i < gActorGlobalState.unk201; i++) {
        if ((gActorGlobalState.unk244[i] == event) && (gActorGlobalState.unk204[i] == node)) {
            gActorGlobalState.unk244[i] = 0;
        }
    }
}

void actorDispatchCollisionResults(Actor *actor) {
    s32 i;
    f32 hitX;
    f32 hitZ;
    s32 pad60;
    f32 otherX;
    f32 otherZ;

    for (i = 0; i < gActorGlobalState.unk201; i++) {
        switch (gActorGlobalState.unk244[i]) {
        case 0:
            break;
        case 1:
            if (actorCollisionGetNodeHitPoint(actor, gActorGlobalState.unk204[i], &hitX, &hitZ) != 0) {
                actorAppendMoveTarget2D(actor, (Actor *)gActorGlobalState.unk204[i], hitX, hitZ, 0, 1);
            }
            break;
        case 2:
            actorCollisionGetNodeHitPoint(actor, gActorGlobalState.unk204[i], &otherX, &otherZ);
            break;
        case 4:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 2, 1, 0, 0);
            break;
        case 3:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 2, 0, 0, 0);
            break;
        case 8:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 2, 2, 0, 0);
            break;
        case 10:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 2, 3, 0, 0);
            break;
        case 13:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 2, 6, 0, 0);
            break;
        case 11:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 2, 4, 0, 0);
            break;
        case 12:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 2, 5, 0, 0);
            break;
        case 6:
        case 7:
            if (gActorGlobalState.unk244[i] == 6) {
                actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 0x40, 0, 0, 0);
            }
            actorAppendMoveTarget3D(actor, (Actor *)gActorGlobalState.unk204[i], actor->x, actor->y, actor->z, 2, 1);
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 0x80, 0, 0, 0);
            playerDropHeldActor(actor);
            break;
        case 5:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 8, 0, 0, 0);
            break;
        case 15:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 4, 0, 0, 0);
            break;
        case 9:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 0x1000, 0, 0, 0);
            break;
        case 14:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], actor, 0x02000000, 0, 0, 0);
            break;
        }
    }

    if (gActorGlobalState.unk39) {
        for (i = 0; i < gActorGlobalState.unk39; i++) {
            if (gActorGlobalState.unk8C[i] == 0) {
                collisionTransformPointByActorMtx(actor, gActorGlobalState.unk6C[i], &gActorGlobalState.unk3C[i][0], gActorGlobalState.unk3C[i][1], &gActorGlobalState.unk3C[i][2]);
                actorAppendMoveTarget2D(actor, gActorGlobalState.unk7C[i], gActorGlobalState.unk3C[i][0], gActorGlobalState.unk3C[i][2], 1, 1);
            }
        }
    }

    if (gActorGlobalState.unk91 != 0) {
        actorCollisionResolveSurfaceHit(actor, gActorGlobalState.unkCC, gActorGlobalState.unk98, gActorGlobalState.unkA4, gActorGlobalState.unkC8, gActorGlobalState.unkD0, gActorGlobalState.unkD4, 1);
    }

    for (i = 0; i < gActorGlobalState.unk1F8; i++) {
        actorCollisionResolveSurfaceHit(actor, gActorGlobalState.unkF8[i].unk3C, gActorGlobalState.unkF8[i].unk0, gActorGlobalState.unkF8[i].unkC, gActorGlobalState.unkF8[i].unk30, gActorGlobalState.unkF8[i].unk34, gActorGlobalState.unkF8[i].unk38, 0);
    }
}

void actorAppendMoveTarget2D(Actor *source, Actor *target, f32 x, f32 z, u8 priority, u8 skipArcCheck) {
    ActorMovePayload2D *payload = heapAlloc(sizeof(ActorMovePayload2D));
    payload->x = x;
    payload->z = z;
    payload->priority = priority;
    payload->skipArcCheck = skipArcCheck;
    actorAppendCallback(target, source, 0x10, 0, 1, payload);
}

void actorAppendMoveTarget3D(Actor *source, Actor *target, f32 x, f32 y, f32 z, u8 priority, u8 skipArcCheck) {
    ActorMovePayload3D *payload = heapAlloc(sizeof(ActorMovePayload3D));
    payload->x = x;
    payload->y = y;
    payload->z = z;
    payload->priority = priority;
    payload->skipArcCheck = skipArcCheck;
    actorAppendCallback(target, source, 0x20, 0, 1, payload);
}

void actorAppendCallback4000(Actor *source, Actor *target, s16 param0, f32 param4, s16 param8) {
    ActorStatePayload *payload = heapAlloc(sizeof(ActorStatePayload));
    payload->unk0 = param0;
    payload->unk4 = param4;
    payload->unk8 = param8;
    actorAppendCallback(target, source, 0x4000, 0, 1, payload);
}

void actorAppendCallback10(Actor *source, Actor *target, f32 x, f32 y, f32 z, s32 pointIndex, u8 param10) {
    ActorRiderPayload *payload = heapAlloc(sizeof(ActorRiderPayload));
    payload->x = x;
    payload->y = y;
    payload->z = z;
    payload->pointIndex = pointIndex;
    payload->unk10 = param10;
    actorAppendCallback(target, source, 0x1, 0, 1, payload);
}

void actorAppendCallbackPayloadA864(Actor *source, Actor *target, s16 param0, s16 param2, void *src4, void *src10, s32 param34, s32 param38, s32 param3C) {
    ActorSurfacePayload *payload = heapAlloc(sizeof(ActorSurfacePayload));
    payload->unk0 = param0;
    payload->unk2 = param2;
    memcpy(payload->unk4, src4, 0xC);
    memcpy(payload->unk10, src10, 0x24);
    payload->unk34 = param34;
    payload->unk38 = param38;
    payload->unk3C = param3C;
    actorAppendCallback(target, source, 0x10000, 0, 1, payload);
}

void actorAppendCallbackPayloadA908(Actor *source, Actor *target, void *src0, void *srcC, s32 param30, s32 param34, s32 param38) {
    ActorHitPayload *payload = heapAlloc(sizeof(ActorHitPayload));
    memcpy(payload->unk0, src0, 0xC);
    memcpy(payload->unkC, srcC, 0x24);
    payload->unk30 = param30;
    payload->unk34 = param34;
    payload->unk38 = param38;
    actorAppendCallback(target, source, 0x20000, 0, 1, payload);
}

void actorAppendCallbackS32(Actor *source, Actor *target, s32 value) {
    s32 *payload = heapAlloc(sizeof(s32));
    *payload = value;
    actorAppendCallback(target, source, 0x40000, 0, 1, payload);
}

void actorAppendCallbackVec3f(Actor *source, Actor *target, f32 x, f32 y, f32 z) {
    f32 *payload = heapAlloc(3 * sizeof(f32));
    payload[0] = x;
    payload[1] = y;
    payload[2] = z;
    actorAppendCallback(target, source, 0x100000, 0, 1, payload);
}

void actorAppendCallbackVec2f(Actor *source, Actor *target, f32 x, f32 z) {
    f32 *payload = heapAlloc(2 * sizeof(f32));
    payload[0] = x;
    payload[1] = z;
    actorAppendCallback(target, source, 0x200000, 0, 1, payload);
}

void actorAppendCallbackPayloadAAB8(Actor *source, Actor *target, s16 param0, f32 param4, s16 param8) {
    ActorStatePayload *payload = heapAlloc(sizeof(ActorStatePayload));
    payload->unk4 = param4;
    payload->unk8 = param8;
    payload->unk0 = param0;
    actorAppendCallback(target, source, 0x400, 0, 1, payload);
}

void actorAppendCallbackMemcpy8(Actor *source, Actor *target, s32 type, u8 subtype, void *data, u8 delayed) {
    void *payload = heapAlloc(8);
    memcpy(payload, data, 8);
    if (!delayed) {
        actorAppendCallback(target, source, type, subtype, 1, payload);
    } else {
        actorQueueDelayedCallback(target, source, type, subtype, 1, payload, 1);
    }
}

void actorAppendCallbackPayloadABC0(Actor *source, Actor *target, u8 subtype, s16 paramC, s16 paramE, f32 x, f32 y, f32 z) {
    ActorEventPayload *payload = heapAlloc(sizeof(ActorEventPayload));
    payload->x = x;
    payload->y = y;
    payload->z = z;
    payload->unkC = paramC;
    payload->unkE = paramE;
    actorAppendCallback(target, source, 0x800000, subtype, 1, payload);
}

void actorGlobalStateClearEvents(void) {
    gActorGlobalState.unkE5 = 0;
    gActorGlobalState.unk15 = 0;
    gActorGlobalState.unk16 = 0;
    gActorGlobalState.unk17 = 0;
    gActorGlobalState.unk18 = 0;
    gActorGlobalState.unk19 = 0;
    gActorGlobalState.unk1B = 0;
    gActorGlobalState.unk1A = 0;
    gActorGlobalState.unk1C = 0;
    gActorGlobalState.unk24 = 0;
    gActorGlobalState.unk25 = 0;
    gActorGlobalState.unk2C = 0;
    gActorGlobalState.unk38 = 0;
    gActorGlobalState.unkE4 = 0;
    gActorGlobalState.unk90 = 0;
    gActorGlobalState.unk39 = 0;
    gActorGlobalState.unk91 = 0;
    gActorGlobalState.unk1F8 = 0;
    gActorGlobalState.targetActor = 0;
    gActorGlobalState.bossFightPhase = 0;
    gActorGlobalState.unk201 = 0;
    gActorGlobalState.unk254 = 0;
    gActorGlobalState.unk2 = 0;
    gActorGlobalState.unk0 = 0;
    gActorGlobalState.unkE8 = 0.0f;
    gActorGlobalState.unkF0 = 0.0f;
    gActorGlobalState.unkF4 = 0.0f;
}

void actorUpdatePrevContactFlags(Actor *actor) {
    actor->prevContactFlags = actor->contactFlags;
}

u16 actorLookupClass(u16 type) {
    return D_8074D624[type];
}

s32 actorCountOwnedByClass(owner, actorClass, filter)
s32 owner;
u16 actorClass;
s32 (*filter)(Actor *);
{
    u16 count = 0;
    s32 i;

    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (owner == (s32)actor->parentActor && actor->collisionFlags == actorClass) {
            if (filter == NULL || filter(actor)) {
                count++;
            }
        }
    }
    return count;
}

extern u8 gPlayerCount;

Actor *actorFindByType(u16 type) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (actor->actorType == type) {
            return actor;
        }
    }
    return NULL;
}

s32 actorIsActive(Actor *target) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (target == actor) {
            return 1;
        }
    }
    return 0;
}

void actorTableClear(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        D_807FBFF0[i] = -1;
    }
    D_807FC3F0 = 0;
}

void actorTableInsert(Actor *actor) {
    if (D_807FC3F0 < 256) {
        D_807FBFF0[D_807FC3F0++] = (s32)actor;
    } else {
        faultSetMessage(0x13, actor->actorType, 0, 0);
    }
    actorTableSort();
}

void actorTableRemove(Actor *actor) {
    u32 res = actorTableBinarySearch(actor);
    s16 idx = res;
    if (res != -1) {
        D_807FBFF0[idx] = -1;
        actorTableSort();
    }
}

s32 actorTableContains(Actor *actor) {
    if (actorTableBinarySearch(actor) != -1) {
        return 1;
    }
    return 0;
}

s32 actorTableBinarySearch(Actor *key) {
    s16 low = 0;
    s16 high = D_807FC3F0 - 1;

    if (D_807FC3F0 == 0) {
        return -1;
    }
    while (low <= high) {
        s16 mid = (low + high) >> 1;

        if (key == (Actor *)D_807FBFF0[mid]) {
            return mid;
        }
        if (key < (Actor *)D_807FBFF0[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

void actorTableSort(void) {
    s32 done = FALSE;
    s16 i;
    s16 j;

    for (i = 1; i < D_807FC3F0; i++) {
        u32 val = D_807FBFF0[i];

        j = i;
        if (val < (u32)D_807FBFF0[j - 1]) {
            do {
                D_807FBFF0[j] = D_807FBFF0[j - 1];
                j--;
            } while (val < (u32)D_807FBFF0[j - 1]);
        }
        D_807FBFF0[j] = val;
    }
    D_807FC3F0 = 0;
    do {
        if (D_807FBFF0[D_807FC3F0] == -1) {
            done = TRUE;
        } else {
            D_807FC3F0++;
        }
    } while (!done);
}

typedef struct PlayerInventory {
    KongInventory kongs[8];
    u8 pad[0x306 - 8 * 0x5E];
} PlayerInventory;

typedef struct PlayerContext5C414 {
    s32 unk0;
    u8 pad4[12];
} PlayerContext5C414;

extern u8 gPlayerCharacterId[];
extern PlayerInventory gPlayerInventoryTable[];
extern KongInventory *D_807FD568;
extern OSContPad *D_807ECDEC;
extern u16 D_807ECDF0;
extern PlayerContext5C414 D_8075C414[];
extern s16 gCurrentCharacterIndex;

void playerSetActiveGlobals(Actor *actor) {
    u8 character;
    PlayerStruct *player;

    gActivePlayerState = actor->customState;
    gCurrentPlayerIndex = gActivePlayerState->playerIndex;
    character = gPlayerCharacterId[gCurrentPlayerIndex];
    player = (PlayerStruct *)gPlayerSlots + gCurrentPlayerIndex;  // FAKE: same-type cast steers uopt t0/t9 for the slot base/offset
    gActivePlayerActor = player->actor;
    D_807FD568 = &gPlayerInventoryTable[gCurrentPlayerIndex].kongs[character];
    D_807ECDEC = player->contPad;
    D_807ECDF0 = *player->heldButtonsPtr;
    gCurrentCharacterIndex = D_8075C414[character].unk0;
    player->sizeModeDirty = 0;
}

u8 playerFindIndexByActor(s32 actor) {
    s32 i;
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].unk0 != 0 && actor == (s32)gPlayerSlots[i].actor) {
            return (u8)i;
        }
    }
    return 0;
}

void actorCopyPoseAndScale(Actor *dest, Actor *src, f32 scale) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
    dest->yaw = src->yaw;
    if (dest->sub4 != NULL) {
        dest->sub4->scaleX = scale;
        dest->sub4->scaleY = scale;
        dest->sub4->scaleZ = scale;
    }
}

void func_8067B280(void) {}
void func_8067B288(void) {}
void func_8067B290(void) {}
void func_8067B298(void) {}
void func_8067B2A0(void) {}
void func_8067B2A8(void) {}

void func_8067B2B0(s32 unused) {
}

void func_8067B2B8(s32 unused) {
}

s32 actorInitFloorAttachment(s32 unused) {
    gSpawnedActor->unk144 = 1;
    return 1;
}

typedef struct ActorInitArg {
    u8 pad0[2];
    u16 animId;
} ActorInitArg;

s32 actorInitAnimAndCollision(ActorInitArg *init) {
    if (controllerAnimInit(gSpawnedActor, init->animId) != 0) {
        gSpawnedActor->collision = actorSub140CreateFromModel(gSpawnedActor);
        gSpawnedActor->eyeHeight = (u32)(((f64)gSpawnedActor->collision->scaledRadius * 0.15) * 0.5);
        return 1;
    }
    return 0;
}

s32 actorInitCollisionFromModel(s32 unused) {
    gSpawnedActor->collision = actorSub140CreateFromModel(gSpawnedActor);
    return 1;
}

s32 actorInitStaticMeshFlag(s32 unused) {
    gSpawnedActor->flags |= 0x2000;
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759260.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759268.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759270.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759278.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759280.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759288.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759290.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759298.s")
