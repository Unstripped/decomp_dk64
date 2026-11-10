#include "common.h"
#include "actor.h"
#define PROTO_SKIP_actorClearTargetAngle // PROTO: The number of arguments doesn't agree with the number in the
#define PROTO_SKIP_actorSub140CreateFromModel // PROTO: Reference of an expression of void type or an incomplete typ
#define PROTO_SKIP_collisionClearFlags // PROTO: Type Actor *  of this argument  is incompatible with type vo
#define PROTO_SKIP_controllerAnimInit // PROTO: The number of arguments doesn't agree with the number in the
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

typedef struct ActorPayloadA69C {
    f32 unk0;
    f32 unk4;
    u8 unk8;
    u8 unk9;
} ActorPayloadA69C;

typedef struct ActorPayloadA70C {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 unkC;
    u8 unkD;
} ActorPayloadA70C;

typedef struct ActorPayloadAAB8 {
    s16 unk0;
    f32 unk4;
    s16 unk8;
} ActorPayloadAAB8;

typedef struct ActorPayloadA7EC {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    u8 unk10;
} ActorPayloadA7EC;

typedef struct ActorPayloadABC0 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
} ActorPayloadABC0;

extern u16 D_8074D624[];
extern u8 D_807F94B4;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u8 D_807FBE08;
extern u8 D_807FBE09;
extern Actor *D_807FBE10[];
extern s16 D_807FBF10;
extern ActorQueueEntry D_807FBF18[16];
extern s16 D_807FBFD8;
extern ActorCallbackNode *D_807FBFE0[];
extern s32 D_807FBFF0[];
extern s16 D_807FC3F0;

ActorSub140 *actorSub140CreateFromModel(Actor *);
void collisionClearFlags(Actor *);
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
    s32 unk4;
    s32 unk8;
    s32 unkC;
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

    gActorScriptAsset = (ActorAssetHeader *)assetLoad(0xD, 0, 1, 1);
    gActorScriptIndexTable = (void *)(gActorScriptAsset->unkC + (s32)gActorScriptAsset);
    gActorScriptAnimTable = (void *)(gActorScriptAsset->unk8 + (s32)gActorScriptAsset);
    gActorScriptSoundTable = (void *)(gActorScriptAsset->unk4 + (s32)gActorScriptAsset);

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
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    s32 unk1C;
} ActorSpawnInfo;
extern u8 D_8074D8D4[];
extern s32 (*D_8074DA30[])(s32 *);

s32 actorSpawnFromInfo(ActorSpawnInfo *info) {
    u8 temp;
    if (actorAllocate((u16)info->unk0)) {
        temp = D_8074D8D4[info->unk0];
        if (D_8074DA30[temp](&info->unk4)) {
            gSpawnedActor->x = info->unkC;
            gSpawnedActor->y = info->unk10;
            gSpawnedActor->z = info->unk14;
            gSpawnedActor->spawnData = info->unk1C;
            gSpawnedActor->yaw = info->unk18;
            gSpawnedActor->spawnTimer = info->unk1A;
            if (info->unk8 != 0) {
                actorScriptStart(gSpawnedActor, info->unk8);
            }
            return 1;
        }
    }
    return 0;
}
s32 actorSpawn(s32 type, s32 spawnArg) {
    u8 temp;
    if (actorAllocate((u16)type)) {
        temp = D_8074D8D4[type];
        if (D_8074DA30[temp](&spawnArg)) {
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

typedef struct ActorAllocBlock {
    u8 pad0[0x54];
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s16 unk5C;
    u8 pad5E[2];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u32 unk64;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ s16 unk70;
    u8 pad72[6];
    /* 0x78 */ u8 unk78;
    u8 pad79[0x37];
    /* 0xB0 */ s8 unkB0;
    u8 padB1[0x1B];
    /* 0xCC */ u8 unkCC;
    /* 0xCD */ u8 unkCD;
    /* 0xCE */ s16 unkCE;
    u8 padD0[4];
    /* 0xD4 */ void *unkD4;
    u8 padD8[2];
    /* 0xDA */ s16 unkDA;
    u8 padDC[0x1C];
    /* 0xF8 */ s16 unkF8;
    u8 padFA[0x16];
    /* 0x110 */ u8 unk110;
    u8 pad111[3];
    /* 0x114 */ void *riderList;
    /* 0x118 */ void *unk118;
    /* 0x11C */ s32 unk11C;
    /* 0x120 */ u8 pad120[4];
    /* 0x124 */ s32 unk124;
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ s16 chunkIndex;
    u8 pad12E[2];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ s16 unk132;
    u8 pad134[4];
    /* 0x138 */ s32 unk138;
    /* 0x13C */ void *callbacks;
    u8 pad140[4];
    /* 0x144 */ u8 unk144;
    u8 pad145[1];
    /* 0x146 */ s16 unk146;
    /* 0x148 */ void *unk148;
    /* 0x14C */ void *unk14C;
    /* 0x150 */ s32 unk150;
    u8 pad154[2];
    /* 0x156 */ u8 unk156;
    u8 pad157[0x16];
    /* 0x16D */ u8 unk16D;
    u8 pad16E[6];
    /* 0x174 */ void *unk174;
} ActorAllocBlock;

s32 actorAllocate(type)
u16 type;
{
    ActorAllocBlock *actor;
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
    actor = (ActorAllocBlock *)heapAlloc(totalDataSize);
    if (actor != NULL) {
        heapClearBlock(actor);
        types = D_8074E218[type];
        ptrArray = (void **)&actor->unk174;
        dataPtr = (u8 *)actor + ((u16)((headerSize + 7) & 0xFFF8));
        if (*types != 0) {
            do {
                *ptrArray++ = dataPtr;
                dataPtr += D_8074DA58[*types++];
            } while (*types != 0);
        }
        actor->callbacks = NULL;
        actor->unk138 = -1;
        actor->unk144 = 2;
        actor->unk110 = 0;
        actor->unkF8 = 0x50;
        actor->unk60 = 0x58144;
        actor->unk64 = 0;
        actor->unk128 = 0xFF;
        actor->unk58 = type;
        if (gGlobalOverlayFlags & 0x100) {
            actor->unk12A = 0x7D0;
        } else {
            actor->unk12A = 0x1F4;
        }
        actor->unk68 = 0;
        actor->unk156 = 0;
        actor->unk78 = 0;
        actor->unk6A = actor->unk6C = 1;
        actor->unk132 = 1;
        actor->riderList = NULL;
        actor->unk118 = NULL;
        actor->unk11C = 0;
        actor->unk6E = -1;
        actor->unk70 = -1;
        actor->unk150 = 0;
        actor->chunkIndex = -1;
        actor->unk124 = 0;
        actor->unk148 = NULL;
        actor->unk14C = NULL;
        actor->unkD4 = &D_80748D4A;
        actor->unk146 = -1;
        actor->unk5C = D_8074D624[type];
        actor->unkDA = 0x400;
        actor->unkCC = 0;
        actor->unkCD = 0;
        actor->unk130 = 0;
        actor->unk131 = 0;
        actor->unk16D = 0xF;
        actor->unkCE = 0;
        actor->unkB0 = -1;
        actor->unk54 = D_807FBB38;
        D_807FBB38++;
        actorTableInsert((Actor *)actor);
        actorInitHealth((Actor *)actor);
        gActiveActors[gActiveActorCount].actor = (Actor *)actor;
        gActiveActors[gActiveActorCount].unk4 = 0;
        D_807FBB3E = gActiveActorCount;
        gActiveActorCount++;
        gSpawnedActor = (Actor *)actor;
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

typedef struct ActorBufferView {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ u8 pad04[0x54];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xBC];
    /* 0x118 */ void *unk118;
    /* 0x11C */ Actor *unk11C;
    /* 0x120 */ u8 pad120[0x20];
    /* 0x140 */ ActorSub140 *unk140;
    /* 0x144 */ u8 pad144[4];
    /* 0x148 */ void *unk148;
    /* 0x14C */ void *unk14C;
} ActorBufferView;

void actorFreeImmediate(Actor *actor) {
    s16 i;
    Actor *temp;

    if (((ActorBufferView *)actor)->unk0 != 0) {
        controllerAnimFree(actor);
    }
    temp = actor->parentActor;
    if (temp != NULL) {
        actorAppendCallback(temp, (s32)actor, 0x80000, 0, 0, NULL);
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
    if (((ActorBufferView *)actor)->unk118 != NULL) {
        heapFree(((ActorBufferView *)actor)->unk118);
    }
    if (((ActorBufferView *)actor)->unk148 != NULL) {
        heapFree(((ActorBufferView *)actor)->unk148);
    }
    if (((ActorBufferView *)actor)->unk14C != NULL) {
        heapFree(((ActorBufferView *)actor)->unk14C);
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
    collisionClearFlags(actor);
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

typedef struct ActorUnk156View {
    u8 pad[0x156];
    u8 unk156;
} ActorUnk156View;


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
            if (((actor->flags & 0x500) || ((ActorUnk156View *)actor)->unk156 != 0) && !(actor->flags & 0x4000)) {
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

u8 actorClearTargetAngle();
extern u8 D_807FBC55;
extern u8 gCurrentPlayerIndex;

void actorUpdateArcBounds(Actor *actor) {
    u8 arcFlags;

    if ((actor->unk144 & 4) && (D_807FBE08 == 0)) {
        if (actor->flags & 0x10000) {
            actor->hasArcBounds = 0;
            actor->collisionHit = 0;
        }
        actor->hasArcBounds |= actorClearTargetAngle(actor, &actor->arcYawMin, &actor->arcYawMax, &arcFlags);
        arcFlags |= D_807FBC55;
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

void actorRiderListAdd(Actor *actor, s32 item) {
    if (actor->riderList == NULL) {
        actor->riderList = heapAlloc(sizeof(ActorList));
        actor->riderList->count = 0;
    }
    if (actor->riderList->count != 4) {
        actor->riderList->items[actor->riderList->count] = item;
        actor->riderList->count++;
    }
}

s32 actorRiderListContains(Actor *actor, s32 item) {
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
    ActorCallbackNode **ptr = D_807FBFE0; do { if (((*ptr) != 0) && ((*ptr)->unk4 == id)) { ((void (*)(void *)) (*ptr)->callback)(&(*ptr)->unk8); heapFree(*ptr); *ptr = 0; } ptr++; } while (ptr != ((ActorCallbackNode **) (&D_807FBFF0))); // LAYOUT: one-line statement line coordinates steer mirrored-pair scheduling
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

void actorAppendCallback(Actor *actor, s32 source, s32 type, u8 subtype, s32 ownsPayload, void *payload) {
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

void actorQueueDelayedCallback(s32 target, s32 source, s32 type, u8 subtype, s32 ownsPayload, void *payload, s32 delay) {
    if (D_807FBFD8 == 16) {
        faultSetMessage(0xF, 0, 0, 0);
    }
    D_807FBF18[D_807FBFD8].node = actorAllocCallbackNode(source, type, subtype, ownsPayload, payload);
    D_807FBF18[D_807FBFD8].arg0 = target;
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
            actor = (Actor *)D_807FBF18[i].arg0;
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
                D_807FBF18[i].arg0 = D_807FBF18[D_807FBFD8 - 1].arg0;
                D_807FBF18[i].arg6 = D_807FBF18[D_807FBFD8 - 1].arg6;
                D_807FBFD8--;
                changed = 1;
            }
        }
    } while (changed);
}

ActorCallbackNode *actorAllocCallbackNode(s32 source, s32 type, u8 subtype, s32 ownsPayload, void *payload) {
    ActorCallbackNode *node = heapAlloc(sizeof(ActorCallbackNode));

    node->callback = (void *)type;
    node->unk4 = subtype;
    node->unk8 = source;
    node->unkC = ownsPayload;
    node->unk10 = payload;
    node->next = NULL;
    return node;
}

typedef struct ActorPlayerStateView {
    u8 pad0[0x6C];
    f32 unk6C;
    s16 unk70;
    u8 pad72[2];
    f32 unk74;
} ActorPlayerStateView;
struct DamageReactionContext;
extern struct DamageReactionContext *gActivePlayerState;
#define PLAYER_STATE_VIEW ((ActorPlayerStateView *)gActivePlayerState)

extern s32 D_807FBC08;
extern s32 D_807FBC14;


typedef struct ActorCollisionHit {
    u8 unk0[0xC];
    u8 unkC[0x24];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    Actor *unk3C;
} ActorCollisionHit;

typedef struct ActorDispatchState {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 pad3;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 pad1D[3];
    Actor *unk20;
    u8 unk24;
    u8 unk25;
    u8 pad26[2];
    Actor *unk28;
    u8 unk2C;
    u8 pad2D[3];
    f32 unk30;
    s16 unk34;
    s16 unk36;
    u8 unk38;
    u8 unk39;
    u8 pad3A[2];
    f32 unk3C[4][3];
    s32 unk6C[4];
    Actor *unk7C[4];
    u8 unk8C[4];
    u8 unk90;
    u8 unk91;
    s16 unk92;
    s16 unk94;
    u8 pad96[0x32];
    s32 unkC8;
    Actor *unkCC;
    s32 unkD0;
    s32 unkD4;
    f32 unkD8;
    f32 unkDC;
    f32 unkE0;
    u8 unkE4;
    u8 unkE5;
    u8 padE6[2];
    f32 unkE8;
    Actor *unkEC;
    f32 unkF0;
    f32 unkF4;
    ActorCollisionHit unkF8[4];
    s32 unk1F8;
    Actor *unk1FC;
    u8 unk200;
    u8 unk201;
    u8 unk202[2];
    s32 unk204[16];
    u8 unk244[16];
    u8 unk254;
    u8 pad255[3];
    s32 unk258[8];
    void *unk278[8];
} ActorDispatchState;

#define GSTATE (*(ActorDispatchState *)&gActorGlobalState)


typedef struct ActorPayload10000 {
    s16 unk0;
    s16 unk2;
    u8 unk4[0xC];
    u8 unk10[0x24];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} ActorPayload10000;

typedef struct ActorPlayerState {
    u8 pad0[0x1A];
    u16 unk1A;
} ActorPlayerState;
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
    u8 priority10;
    u8 priority20;
    ActorPayloadA7EC *riderPayload;
    ActorCollisionHit *hit;
    ActorPayload10000 *surfacePayload;
    ActorCallbackNode *sorted;
    f32 *pointPair;
    ActorPayloadABC0 *eventPayload;
    ActorPlayerState *playerState;
    ActorPayloadAAB8 *viewPayload;
    ActorPayloadA69C *payload10;
    ActorPayloadA70C *payload20;
    f32 *vecPayload;
    ActorPayloadAAB8 *statePayload;
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
            if ((s32)node->callback == 0) {}  // FAKE: dead test steers uopt colouring of the callback id (a0 vs a1)
            if ((s32)node->callback & mask) {
                switch ((s32)node->callback) {
                case 0x8000:
                    actorCollisionProcessHit(actor, node);
                    if (((GSTATE.unk200 == 9) || (GSTATE.unk200 == 0xA)) && (actor->collisionFlags & 1)) {
                        playerHandleDamageReaction(actor, GSTATE.unk1FC, (GSTATE.unk200 == 0xA));
                    }
                    break;
                case 0x2:
                    switch (node->unk4) {
                    case 0:
                        GSTATE.unk16 = 1;
                        if (actor == gActivePlayerActor) {
                            playerStateQueueCallback(0x10, NULL, gCurrentPlayerIndex);
                        }
                        break;
                    case 1:
                        GSTATE.unk17 = 1;
                        if (actor == gActivePlayerActor) {
                            playerStateQueueCallback(0xE, node->unk8, gCurrentPlayerIndex);
                        }
                        break;
                    case 2:
                        GSTATE.unk18 = 1;
                        if (actor == gActivePlayerActor) {
                            playerStateQueueCallback(0x12, NULL, gCurrentPlayerIndex);
                        }
                        break;
                    case 3:
                        GSTATE.unk19 = 1;
                        if (actor == gActivePlayerActor) {
                            playerStateQueueCallback(0x13, NULL, gCurrentPlayerIndex);
                        }
                        break;
                    case 6:
                        GSTATE.unk1B = 1;
                        if (actor == gActivePlayerActor) {
                            playerStateQueueCallback(0x36, node->unk8, gCurrentPlayerIndex);
                        }
                        break;
                    case 4:
                    case 5:
                        if (actor == gActivePlayerActor) {
                            if (node->unk4 == 4) {
                                playerStateQueueCallback(0x2B, node->unk8, gCurrentPlayerIndex);
                            } else {
                                playerStateQueueCallback(0x32, node->unk8, gCurrentPlayerIndex);
                            }
                            player = (Actor *)node->unk8;
                            if ((player != NULL) && (player->collisionFlags & 2)) {
                                playerState = (ActorPlayerState *)player->customState;
                                playerState->unk1A = (u16)(playerState->unk1A | 0x100);
                            }
                        }
                        break;
                    }
                    break;
                case 0x8:
                    playerHandleDamageReaction(actor, (Actor *)node->unk8, 0);
                    break;
                case 0x4:
                    playerHandleDamageReaction(actor, (Actor *)node->unk8, 1);
                    break;
                case 0x800:
                    actor->unk144 = (u8)node->unk4;
                    GSTATE.unk90 = 1;
                    break;
                case 0x400:
                    viewPayload = (ActorPayloadAAB8 *)node->unk10;
                    PLAYER_STATE_VIEW->unk70 = viewPayload->unk0;
                    PLAYER_STATE_VIEW->unk74 = viewPayload->unk4;
                    PLAYER_STATE_VIEW->unk6C = (f32)viewPayload->unk8;
                    GSTATE.unk1A = 1;
                    if (actor == gActivePlayerActor) {
                        playerStateQueueCallback(0x17, node->unk8, gCurrentPlayerIndex);
                    }
                    break;
                case 0x10:
                    payload10 = (ActorPayloadA69C *)node->unk10;
                    priority10 = payload10->unk8;
                    if (bestPriority < (s32)priority10) {
                        targetX = payload10->unk0;
                        bestPriority = (s8)priority10;
                        targetZ = payload10->unk4;
                        bestType = (s32)node->callback;
                        skipArcCheck = payload10->unk9;
                    }
                    break;
                case 0x20:
                    payload20 = (ActorPayloadA70C *)node->unk10;
                    priority20 = payload20->unkC;
                    if (bestPriority < (s32)priority20) {
                        targetX = payload20->unk0;
                        bestPriority = (s8)priority20;
                        targetY = payload20->unk4;
                        targetZ = payload20->unk8;
                        bestType = (s32)node->callback;
                        skipArcCheck = payload20->unkD;
                    }
                    break;
                case 0x100000:
                    vecPayload = (f32 *)node->unk10;
                    GSTATE.unkD8 = vecPayload[0];
                    GSTATE.unkDC = vecPayload[1];
                    GSTATE.unkE0 = vecPayload[2];
                    GSTATE.unkE4 = 1;
                    GSTATE.unkEC = (Actor *)node->unk8;
                    break;
                case 0x1000:
                    GSTATE.unk1C = 1;
                    GSTATE.unk20 = (Actor *)node->unk8;
                    break;
                case 0x4000:
                    statePayload = (ActorPayloadAAB8 *)node->unk10;
                    GSTATE.unk2C = 1;
                    GSTATE.unk30 = statePayload->unk4;
                    GSTATE.unk34 = statePayload->unk8;
                    GSTATE.unk36 = statePayload->unk0;
                    break;
                case 0x2000:
                    if (node->unk4 != 0) {
                        GSTATE.unk24 = 1;
                    } else {
                        GSTATE.unk25 = 1;
                    }
                    GSTATE.unk28 = (Actor *)node->unk8;
                    break;
                case 0x80:
                    actor->flags = (s32)(actor->flags | 8);
                    if (actor == gActivePlayerActor) {
                        playerStateQueueCallback(0x16, node->unk8, gCurrentPlayerIndex);
                    }
                    break;
                case 0x40:
                    if (node->unk4 != 0) {
                        actor->flags = (s32)(actor->flags | 4);
                    } else {
                        actor->flags = (s32)(actor->flags & ~4);
                    }
                    break;
                case 0x1:
                    riderPayload = (ActorPayloadA7EC *)node->unk10;
                    if (actorTableContains(node->unk8) != 0 && GSTATE.unk39 != 4) {
                        GSTATE.unk3C[GSTATE.unk39][0] = riderPayload->unk0;
                        GSTATE.unk3C[GSTATE.unk39][1] = riderPayload->unk4;
                        GSTATE.unk3C[GSTATE.unk39][2] = riderPayload->unk8;
                        GSTATE.unk6C[GSTATE.unk39] = riderPayload->unkC;
                        GSTATE.unk7C[GSTATE.unk39] = (Actor *)node->unk8;
                        GSTATE.unk8C[GSTATE.unk39] = riderPayload->unk10;
                        GSTATE.unk39++;
                        actorRiderListAdd(actor, node->unk8);
                    }
                    break;
                case 0x20000:
                    hit = (ActorCollisionHit *)node->unk10;
                    if (GSTATE.unk1F8 != 4) {
                        memcpy(&GSTATE.unkF8[GSTATE.unk1F8], hit, 0xC);
                        memcpy(GSTATE.unkF8[GSTATE.unk1F8].unkC, hit->unkC, 0x24);
                        GSTATE.unkF8[GSTATE.unk1F8].unk30 = hit->unk30;
                        GSTATE.unkF8[GSTATE.unk1F8].unk34 = hit->unk34;
                        GSTATE.unkF8[GSTATE.unk1F8].unk38 = hit->unk38;
                        GSTATE.unkF8[GSTATE.unk1F8].unk3C = (Actor *)node->unk8;
                        GSTATE.unk1F8++;
                    }
                    break;
                case 0x10000:
                    surfacePayload = (ActorPayload10000 *)node->unk10;
                    GSTATE.unk91 = 1;
                    GSTATE.unk92 = surfacePayload->unk0;
                    GSTATE.unk94 = surfacePayload->unk2;
                    memcpy(&D_807FBC08, surfacePayload->unk4, 0xC);
                    memcpy(&D_807FBC14, surfacePayload->unk10, 0x24);
                    GSTATE.unkC8 = surfacePayload->unk34;
                    GSTATE.unkCC = (Actor *)node->unk8;
                    GSTATE.unkD0 = surfacePayload->unk38;
                    GSTATE.unkD4 = surfacePayload->unk3C;
                    break;
                case 0x40000:
                    collisionValue = node->unk10;
                    collision = actor->collision;
                    if (collision != NULL) {
                        collision->unk68 = *collisionValue;
                    }
                    break;
                case 0x80000:
                    GSTATE.unk38 = 1;
                    break;
                case 0x200000:
                    pointPair = (f32 *)node->unk10;
                    GSTATE.unkF0 = pointPair[0];
                    GSTATE.unkF4 = pointPair[1];
                    break;
                case 0x400000:
                    GSTATE.unkE8 = (f32)(u32)node->unk4;
                    GSTATE.unkE5 = 1;
                    break;
                case 0x1000000:
                    if (GSTATE.unk254 < 8) {
                        GSTATE.unk258[GSTATE.unk254] = node->unk4;
                        GSTATE.unk278[GSTATE.unk254] = node->unk10;
                        GSTATE.unk254++;
                    }
                    break;
                case 0x800000:
                    eventPayload = (ActorPayloadABC0 *)node->unk10;
                    GSTATE.unk4 = eventPayload->unk0;
                    GSTATE.unk8 = eventPayload->unk4;
                    GSTATE.unkC = eventPayload->unk8;
                    GSTATE.unk10 = eventPayload->unkC;
                    GSTATE.unk12 = eventPayload->unkE;
                    GSTATE.unk2 = 1;
                    GSTATE.unk14 = node->unk4;
                    break;
                case 0x2000000:
                    GSTATE.unk0 = 1;
                    GSTATE.unk1 = node->unk4;
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


struct PlayerTableEntry;
extern struct PlayerTableEntry *gPlayerSlots;

typedef struct DamageReactionPlayerEntry {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} DamageReactionPlayerEntry;

typedef struct DamageReactionContext {
    u8 pad0[0x1A4];
    u8 playerIndex;
    u8 pad1A5[0x1F0 - 0x1A5];
    u32 stateFlags;
    u8 pad1F4[0x200 - 0x1F4];
    u16 unk200;
} DamageReactionContext;
extern DamageReactionContext *gActivePlayerState;

extern u8 D_807FBB85;
extern s32 D_80720E2C;
void playerHandleDamageReaction(Actor *actor, Actor *attacker, u8 heavy) {
    s32 reaction;
    s32 queueReaction;
    void *pulseCallback;
    s32 pad;
    s32 damageLevel;

    D_807FBB85 = 1;
    if (actor == gActivePlayerActor) {
        if (!(((DamageReactionPlayerEntry *)gPlayerSlots)[gActivePlayerState->playerIndex].unk2C0 == 2 && attacker != NULL && (attacker->collisionFlags & 2))) {
            reaction = 0x2E;
            queueReaction = 1;
            if (heavy != 0) {
                reaction = 0x30;
            }
            if (attacker != NULL && attacker->actorType == 0x116) {
                effectSpawnBurstParticleCluster(actor);
                switch (attacker->unk155[0]) {
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
                    effectSetCallback(&effectPulseSpinUpdate);
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
    ActorCallbackNode *new_head = head;
    ActorCallbackNode *curr;
    ActorCallbackNode *scan;
    s32 inserted;
    ActorCallbackNode *temp;

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
                            temp = scan->next;
                            scan->next = curr;
                            curr->next = temp;
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
                    curr->next = new_head;
                    new_head->prev = curr;
                    new_head = curr;
                }
                curr = curr->next;
            } while (curr != NULL);
        }
    }
    return new_head;
}

void actorCollisionEventsCancel(s32 node, u8 event) {
    s32 i;

    for (i = 0; i < gActorGlobalState.unk201; i++) {
        if ((gActorGlobalState.unk244[i] == event) && (gActorGlobalState.unk204[i] == node)) {
            gActorGlobalState.unk244[i] = 0;
        }
    }
}

extern u8 D_807FBC68[][0x40];
extern u8 D_807FBC74[][0x40];



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
                actorAppendCallbackPayloadA69C((s32)actor, (Actor *)gActorGlobalState.unk204[i], hitX, hitZ, 0, 1);
            }
            break;
        case 2:
            actorCollisionGetNodeHitPoint(actor, gActorGlobalState.unk204[i], &otherX, &otherZ);
            break;
        case 4:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 2, 1, 0, 0);
            break;
        case 3:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 2, 0, 0, 0);
            break;
        case 8:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 2, 2, 0, 0);
            break;
        case 10:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 2, 3, 0, 0);
            break;
        case 13:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 2, 6, 0, 0);
            break;
        case 11:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 2, 4, 0, 0);
            break;
        case 12:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 2, 5, 0, 0);
            break;
        case 6:
        case 7:
            if (gActorGlobalState.unk244[i] == 6) {
                actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 0x40, 0, 0, 0);
            }
            actorAppendCallbackPayloadA70C((s32)actor, (Actor *)gActorGlobalState.unk204[i], actor->x, actor->y, actor->z, 2, 1);
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 0x80, 0, 0, 0);
            playerDropHeldActor(actor);
            break;
        case 5:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 8, 0, 0, 0);
            break;
        case 15:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 4, 0, 0, 0);
            break;
        case 9:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 0x1000, 0, 0, 0);
            break;
        case 14:
            actorAppendCallback((Actor *)gActorGlobalState.unk204[i], (s32)actor, 0x02000000, 0, 0, 0);
            break;
        }
    }

    if (gActorGlobalState.unk39) {
        for (i = 0; i < gActorGlobalState.unk39; i++) {
            if (GSTATE.unk8C[i] == 0) {
                collisionTransformPointByActorMtx(actor, GSTATE.unk6C[i], &GSTATE.unk3C[i][0], GSTATE.unk3C[i][1], &GSTATE.unk3C[i][2]);
                actorAppendCallbackPayloadA69C((s32)actor, GSTATE.unk7C[i], GSTATE.unk3C[i][0], GSTATE.unk3C[i][2], 1, 1);
            }
        }
    }

    if (gActorGlobalState.unk91 != 0) {
        actorCollisionResolveSurfaceHit(actor, GSTATE.unkCC, &D_807FBC08, &D_807FBC14, GSTATE.unkC8, GSTATE.unkD0, GSTATE.unkD4, 1);
    }

    for (i = 0; i < gActorGlobalState.unk1F8; i++) {
        actorCollisionResolveSurfaceHit(actor, GSTATE.unkF8[i].unk3C, D_807FBC68[i], D_807FBC74[i], GSTATE.unkF8[i].unk30, GSTATE.unkF8[i].unk34, GSTATE.unkF8[i].unk38, 0);
    }
}

void actorAppendCallbackPayloadA69C(s32 source, Actor *target, f32 x, f32 z, u8 arg4, u8 arg5) {
    ActorPayloadA69C *temp = heapAlloc(sizeof(ActorPayloadA69C));
    temp->unk0 = x;
    temp->unk4 = z;
    temp->unk8 = arg4;
    temp->unk9 = arg5;
    actorAppendCallback(target, source, 0x10, 0, 1, temp);
}

void actorAppendCallbackPayloadA70C(s32 source, Actor *target, f32 x, f32 y, f32 z, u8 arg5, u8 arg6) {
    ActorPayloadA70C *temp = heapAlloc(sizeof(ActorPayloadA70C));
    temp->unk0 = x;
    temp->unk4 = y;
    temp->unk8 = z;
    temp->unkC = arg5;
    temp->unkD = arg6;
    actorAppendCallback(target, source, 0x20, 0, 1, temp);
}

void actorAppendCallback4000(Actor *source, Actor *target, s16 arg2, f32 arg3, s16 arg4) {
    ActorPayloadAAB8 *temp = heapAlloc(sizeof(ActorPayloadAAB8));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    actorAppendCallback(target, source, 0x4000, 0, 1, temp);
}

void actorAppendCallback10(s32 source, Actor *target, f32 arg2, f32 arg3, f32 arg4, s32 arg5, u8 arg6) {
    ActorPayloadA7EC *temp = heapAlloc(sizeof(ActorPayloadA7EC));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unkC = arg5;
    temp->unk10 = arg6;
    actorAppendCallback(target, source, 0x1, 0, 1, temp);
}

typedef struct ActorPayloadA864 {
    s16 unk0;
    s16 unk2;
    u8 unk4[0xC];
    u8 unk10[0x24];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} ActorPayloadA864;

void actorAppendCallbackPayloadA864(s32 source, Actor *target, s16 arg2, s16 arg3, void *arg4, void *arg5, s32 arg6, s32 arg7, s32 arg8) {
    ActorPayloadA864 *temp = heapAlloc(sizeof(ActorPayloadA864));
    temp->unk0 = arg2;
    temp->unk2 = arg3;
    memcpy(temp->unk4, arg4, 0xC);
    memcpy(temp->unk10, arg5, 0x24);
    temp->unk34 = arg6;
    temp->unk38 = arg7;
    temp->unk3C = arg8;
    actorAppendCallback(target, source, 0x10000, 0, 1, temp);
}

typedef struct ActorPayloadA908 {
    u8 unk0[0xC];
    u8 unkC[0x24];
    s32 unk30;
    s32 unk34;
    s32 unk38;
} ActorPayloadA908;

void actorAppendCallbackPayloadA908(s32 source, Actor *target, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6) {
    ActorPayloadA908 *temp = heapAlloc(sizeof(ActorPayloadA908));
    memcpy(temp, arg2, 0xC);
    memcpy((u8 *)temp + 0xC, arg3, 0x24);
    temp->unk30 = arg4;
    temp->unk34 = arg5;
    temp->unk38 = arg6;
    actorAppendCallback(target, source, 0x20000, 0, 1, temp);
}

void actorAppendCallbackS32(s32 source, Actor *target, s32 value) {
    s32 *temp = heapAlloc(sizeof(s32));
    *temp = value;
    actorAppendCallback(target, source, 0x40000, 0, 1, temp);
}

void actorAppendCallbackVec3f(s32 source, Actor *target, f32 x, f32 y, f32 z) {
    f32 *temp = heapAlloc(3 * sizeof(f32));
    temp[0] = x;
    temp[1] = y;
    temp[2] = z;
    actorAppendCallback(target, source, 0x100000, 0, 1, temp);
}

void actorAppendCallbackVec2f(s32 source, Actor *target, f32 x, f32 z) {
    f32 *temp = heapAlloc(2 * sizeof(f32));
    temp[0] = x;
    temp[1] = z;
    actorAppendCallback(target, source, 0x200000, 0, 1, temp);
}

void actorAppendCallbackPayloadAAB8(s32 source, Actor *target, s16 arg2, f32 arg3, s16 arg4) {
    ActorPayloadAAB8 *temp = heapAlloc(sizeof(ActorPayloadAAB8));
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unk0 = arg2;
    actorAppendCallback(target, source, 0x400, 0, 1, temp);
}

void actorAppendCallbackMemcpy8(s32 source, Actor *target, s32 type, u8 subtype, void *data, u8 delayed) {
    void *temp = heapAlloc(8);
    memcpy(temp, data, 8);
    if (!delayed) {
        actorAppendCallback(target, source, type, subtype, 1, temp);
    } else {
        actorQueueDelayedCallback((s32)target, source, type, subtype, 1, temp, 1);
    }
}

void actorAppendCallbackPayloadABC0(s32 source, Actor *target, u8 arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6, f32 arg7) {
    ActorPayloadABC0 *temp = heapAlloc(sizeof(ActorPayloadABC0));
    temp->unk0 = arg5;
    temp->unk4 = arg6;
    temp->unk8 = arg7;
    temp->unkC = arg3;
    temp->unkE = arg4;
    actorAppendCallback(target, source, 0x800000, arg2, 1, temp);
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
    gActorGlobalState.unk200 = 0;
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

typedef struct PlayerTableEntry {
    u8 unk0;
    char pad1[3];
    s32 unk4;
    char pad8[0x2F0 - 8];
} PlayerTableEntry;
extern PlayerTableEntry *gPlayerSlots;
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
    s32 res = actorTableBinarySearch(actor);
    s16 idx = res;
    if ((u32)res != (u32)-1) {
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

typedef struct PlayerContextSub174 {
    u8 pad0[0x1A4];
    u8 playerIndex;
} PlayerContextSub174;

typedef struct PlayerContextEntry {
    u8 pad0[4];
    Actor *actor;
    u8 pad8[0x294 - 0x8];
    s32 unk294;
    u16 *unk298;
    u8 pad29C[0x2C1 - 0x29C];
    u8 unk2C1;
    u8 pad2C2[0x2F0 - 0x2C2];
} PlayerContextEntry;

typedef struct PlayerContextKongData {
    u8 pad[0x5E];
} PlayerContextKongData;

typedef struct PlayerContextArray950 {
    PlayerContextKongData sub[8];
    u8 pad[0x306 - 8 * 0x5E];
} PlayerContextArray950;

typedef struct PlayerContext5C414 {
    s32 unk0;
    u8 pad4[12];
} PlayerContext5C414;

extern u8 gPlayerCharacterId[];
extern PlayerContextArray950 gPlayerInventoryTable[];
extern void *D_807FD568;
extern s32 D_807ECDEC;
extern u16 D_807ECDF0;
extern PlayerContext5C414 D_8075C414[];
extern s16 gCurrentCharacterIndex;

void playerSetActiveGlobals(Actor *actor) {
    u8 character;
    PlayerContextEntry *player;

    gActivePlayerState = actor->customState;
    gCurrentPlayerIndex = ((PlayerContextSub174 *)gActivePlayerState)->playerIndex;
    character = gPlayerCharacterId[gCurrentPlayerIndex];
    player = (PlayerContextEntry *)gPlayerSlots + gCurrentPlayerIndex;
    gActivePlayerActor = player->actor;
    D_807FD568 = &gPlayerInventoryTable[gCurrentPlayerIndex].sub[character];
    D_807ECDEC = player->unk294;
    D_807ECDF0 = *player->unk298;
    gCurrentCharacterIndex = D_8075C414[character].unk0;
    player->unk2C1 = 0;
}

u8 playerFindIndexByActor(s32 actor) {
    s32 i;
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].unk0 != 0 && actor == gPlayerSlots[i].unk4) {
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

s32 controllerAnimInit(Actor *, u16, void *);

typedef struct ActorSub140View {
    u8 pad0[0xC];
    s32 unkC;
} ActorSub140View;

typedef struct ActorInitArg {
    u8 pad0[2];
    u16 unk2;
} ActorInitArg;

s32 actorInitAnimAndCollision(ActorInitArg *init) {
    if (controllerAnimInit(gSpawnedActor, init->unk2, init) != 0) {
        gSpawnedActor->collision = actorSub140CreateFromModel(gSpawnedActor);
        gSpawnedActor->eyeHeight = (u32)(((f64)((ActorSub140View *)gSpawnedActor->collision)->unkC * 0.15) * 0.5);
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
