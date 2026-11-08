#include "common.h"
#include "actor.h"

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
extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBE08;
extern u8 D_807FBE09;
extern Actor *D_807FBE10[];
extern s16 D_807FBF10;
extern ActorQueueEntry D_807FBF18[16];
extern s16 D_807FBFD8;
extern ActorCallbackNode *D_807FBFE0[];
extern s32 D_807FBFF0[];
extern s16 D_807FC3F0;

void *heapAlloc(s32);
void controllerStepMotionWindows();
void actorCheckWorldBounds(Actor *);
ActorSub140 *actorSub140CreateFromModel(Actor *);
void collisionClearFlags(Actor *);
void actorUpdateSubnodeRotationAndMtx(Actor *);
void actorUpdateMovementFlags(Actor *);
void actorCollisionCheckBoundingBoxes(Actor *);
void actorInitDamage(Actor *);
void func_80677EC8(s32);
s32 func_80678014(s32);
s32 actorAllocate();
void actorDespawn(Actor *);
s32 actorQueueOrDespawn(Actor *);
void actorFlushDespawnQueue(void);
void actorRegisterActive(Actor *);
void actorDespawnByOwner(s32);
void actorFreeImmediate(Actor *);
void func_806787CC(void);
static void func_806787EC(void);
static void func_806787F4(void);
static void func_806787FC(void);
static void func_80678804(void);
static void func_8067880C(void);
static void func_80678814(void);
static void func_8067881C(void);
void func_80678B04(void);
void actorPreTick(Actor *);
void func_80678DD8(Actor *);
void func_80678E14(Actor *);
void actorRiderListFree(Actor *);
void actorRiderListAdd(Actor *, s32);
s32 actorRiderListContains(Actor *, s32);
void actorRegisterGlobalCallback(ActorCallbackNode *);
void actorFreeCallbackList(Actor *);
void actorCallbackMaskEnable(Actor *, s32);
void actorCallbackMaskDisable(Actor *, s32);
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void actorQueueDelayedCallback(s32, s32, s32, u8, s32, void *, s32);
ActorCallbackNode *actorAllocCallbackNode(s32, s32, u8, s32, void *);
void actorDispatchCallbacks(Actor *);
void actorCollisionEventsCancel(s32, u8);
void func_8067A69C(s32, Actor *, f32, f32, u8, u8);
void func_8067A70C(s32, Actor *, f32, f32, f32, u8, u8);
void func_8067A784(s32, Actor *, s16, f32, s16);
void func_8067A7EC(s32, Actor *, f32, f32, f32, s32, u8);
void func_8067A99C(s32, Actor *, s32);
void func_8067A9F0(s32, Actor *, f32, f32, f32);
void func_8067AA58(s32, Actor *, f32, f32);
void func_8067AAB8(s32, Actor *, s16, f32, s16);
void func_8067ABC0(s32, Actor *, u8, s16, s16, f32, f32, f32);
void actorGlobalStateClearEvents(void);
void func_8067ACB4(Actor *);
u16 func_8067ACC0(u16);
void actorTableClear(void);
s32 actorTableContains();
s32 actorTableBinarySearch();
void playerSetActiveGlobals(Actor *);
void func_8067B2B0(s32);
void func_8067B2B8(s32);
s32 func_8067B2C0(s32);
s32 func_8067B3F4(s32);
s32 func_8067B42C(s32);
void actorListUpdateSpawns(void);
void actorListRemoveByActor(void);
void playerStateDispatchQueuedCallback(void);
void faultSetMessage(s32, s32, s32, s32);
void heapFree(void *);

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
extern ActorAssetHeader *D_807FBB50;
extern void *D_807FBB54;
extern void *D_807FBB58;
extern void *D_807FBB5C;
extern s32 D_807FBB38;

void *assetLoad(s32, s32, s32, s32);

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

    D_807FBB50 = (ActorAssetHeader *)assetLoad(0xD, 0, 1, 1);
    D_807FBB54 = (void *)(D_807FBB50->unkC + (s32)D_807FBB50);
    D_807FBB58 = (void *)(D_807FBB50->unk8 + (s32)D_807FBB50);
    D_807FBB5C = (void *)(D_807FBB50->unk4 + (s32)D_807FBB50);

    for (i = 0; i < 64; i++) {
        gActiveActors[i].actor = NULL;
        gActiveActors[i].unk4 = 0;
    }
    gActiveActorCount = 0;

    actorTableClear();

    D_807FBB38 = 0;
    D_807FBE09 = 0;
    D_807FBFD8 = 0;
    D_807FBB48 = NULL;
}

void func_80677EC8(s32 arg0) {
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
void actorScriptStart(Actor *, s32);
extern u8 D_8074D8D4[];
extern s32 (*D_8074DA30[])(s32 *);

s32 actorSpawnFromInfo(ActorSpawnInfo *arg0) {
    u8 temp;
    if (actorAllocate((u16)arg0->unk0)) {
        temp = D_8074D8D4[arg0->unk0];
        if (D_8074DA30[temp](&arg0->unk4)) {
            D_807FBB44->x = arg0->unkC;
            D_807FBB44->y = arg0->unk10;
            D_807FBB44->z = arg0->unk14;
            D_807FBB44->unk124 = arg0->unk1C;
            D_807FBB44->yaw = arg0->unk18;
            D_807FBB44->unk15C = arg0->unk1A;
            if (arg0->unk8 != 0) {
                actorScriptStart(D_807FBB44, arg0->unk8);
            }
            return 1;
        }
    }
    return 0;
}
s32 actorSpawn(s32 arg0, s32 arg1) {
    u8 temp;
    if (actorAllocate((u16)arg0)) {
        temp = D_8074D8D4[arg0];
        if (D_8074DA30[temp](&arg1)) {
            return 1;
        }
    }
    return 0;
}

s32 func_80678014(s32 arg0) {
    if (actorAllocate(arg0 & 0xFFFF) != 0) {
        func_8067B2C0(0);
        return 1;
    }
    return 0;
}

extern u16 *D_8074E218[];
extern u16 D_8074DA58[];
extern u32 D_807FBB64;
extern u16 D_80748D4A;
extern u16 D_807FBB3E;
void heapClearBlock(void *);
void actorTableInsert(Actor *);
void actorInitHealth(Actor *);

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
    /* 0x114 */ void *unk114;
    /* 0x118 */ void *unk118;
    /* 0x11C */ s32 unk11C;
    /* 0x120 */ u8 pad120[4];
    /* 0x124 */ s32 unk124;
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ s16 unk12C;
    u8 pad12E[2];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ s16 unk132;
    u8 pad134[4];
    /* 0x138 */ s32 unk138;
    /* 0x13C */ void *unk13C;
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

s32 actorAllocate(arg0)
u16 arg0;
{
    ActorAllocBlock *actor;
    u16 *types;
    void **ptrArray;
    u8 *dataPtr;
    u16 headerSize;
    u16 totalDataSize;

    types = D_8074E218[arg0];
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
        types = D_8074E218[arg0];
        ptrArray = (void **)&actor->unk174;
        dataPtr = (u8 *)actor + ((u16)((headerSize + 7) & 0xFFF8));
        if (*types != 0) {
            do {
                *ptrArray++ = dataPtr;
                dataPtr += D_8074DA58[*types++];
            } while (*types != 0);
        }
        actor->unk13C = NULL;
        actor->unk138 = -1;
        actor->unk144 = 2;
        actor->unk110 = 0;
        actor->unkF8 = 0x50;
        actor->unk60 = 0x58144;
        actor->unk64 = 0;
        actor->unk128 = 0xFF;
        actor->unk58 = arg0;
        if (D_807FBB64 & 0x100) {
            actor->unk12A = 0x7D0;
        } else {
            actor->unk12A = 0x1F4;
        }
        actor->unk68 = 0;
        actor->unk156 = 0;
        actor->unk78 = 0;
        actor->unk6A = actor->unk6C = 1;
        actor->unk132 = 1;
        actor->unk114 = NULL;
        actor->unk118 = NULL;
        actor->unk11C = 0;
        actor->unk6E = -1;
        actor->unk70 = -1;
        actor->unk150 = 0;
        actor->unk12C = -1;
        actor->unk124 = 0;
        actor->unk148 = NULL;
        actor->unk14C = NULL;
        actor->unkD4 = &D_80748D4A;
        actor->unk146 = -1;
        actor->unk5C = D_8074D624[arg0];
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
        D_807FBB44 = (Actor *)actor;
        return 1;
    }
    return 0;
}

void actorDespawn(Actor *arg0) {
    actorListRemoveByActor();
    actorQueueOrDespawn(arg0);
}

s32 actorQueueOrDespawn(Actor *arg0) {
    s32 i;

    if (D_807FBE09 != 0) {
        if (D_807FBF10 == 0x40) {
            faultSetMessage(0xC, 0, 0, 0);
        }
        if (arg0 == D_807FBB40) {
            D_807FBE08 = 1;
        }
        for (i = 0; i < D_807FBF10; i++) {
            if (arg0 == D_807FBE10[i]) {
                return 0;
            }
        }
        D_807FBE10[D_807FBF10] = arg0;
        D_807FBF10++;
    } else {
        actorFreeImmediate(arg0);
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

void actorRegisterActive(Actor *arg0) {
    gActiveActors[gActiveActorCount].actor = arg0;
    gActiveActors[gActiveActorCount].unk4 = 0;
    gActiveActorCount++;
}

void sfxStopSlotSound(Actor *, s32);
void func_8062D26C(Actor *);
void actorDeregisterActive(Actor *arg0) {
    s16 i;

    sfxStopSlotSound(arg0, 0);
    sfxStopSlotSound(arg0, 1);
    i = 0;
    if (arg0 != gActiveActors[0].actor && gActiveActorCount > 0) {
        do {
            i++;
            if (arg0 == gActiveActors[i].actor) {
                break;
            }
        } while (i < gActiveActorCount);
    }
    if (--gActiveActorCount != 0) {
        gActiveActors[i].actor = gActiveActors[gActiveActorCount].actor;
        gActiveActors[i].unk4 = gActiveActors[gActiveActorCount].unk4;
    }
    func_8062D26C(arg0);
    arg0->unk150 = 0;
}

void actorDespawnByOwner(s32 arg0) {
    s32 i;

    D_807FBE09 = 1;
    D_807FBF10 = 0;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (arg0 == actor->unk11C) {
            actorDespawn(actor);
            actor->unk11C = 0;
        }
    }
    D_807FBE09 = 0;
    actorFlushDespawnQueue();
}

void controllerAnimFree(void);
void effectFreeByResource(Actor *);
void pathPlaybackStopForActor(Actor *);
void actorSub140Free(ActorSub140 *);
void proxPathRemoveActor(Actor *);
void resQueueRemove(Actor *);
void renderCallbacksDisableForActor(Actor *);
void actorTableRemove();
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

void actorFreeImmediate(Actor *arg0) {
    s16 i;
    Actor *temp;

    if (((ActorBufferView *)arg0)->unk0 != 0) {
        controllerAnimFree();
    }
    temp = (Actor *)arg0->unk11C;
    if (temp != NULL) {
        actorAppendCallback(temp, (s32)arg0, 0x80000, 0, 0, NULL);
    }
    for (i = 0; i < gActiveActorCount; i++) {
        if ((s32)arg0 == gActiveActors[i].actor->unk11C) {
            gActiveActors[i].actor->unk11C = 0;
        }
    }
    i = 0;
    effectFreeByResource(arg0);
    pathPlaybackStopForActor(arg0);
    sfxStopSlotSound(arg0, 0);
    sfxStopSlotSound(arg0, 1);
    if (gActiveActors[0].actor != arg0) {
        if (gActiveActorCount > 0) {
            do {
                i++;
                if (gActiveActors[i].actor == arg0) {
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
    actorSub140Free(arg0->unk140);
    proxPathRemoveActor(arg0);
    if (((ActorBufferView *)arg0)->unk118 != NULL) {
        heapFree(((ActorBufferView *)arg0)->unk118);
    }
    if (((ActorBufferView *)arg0)->unk148 != NULL) {
        heapFree(((ActorBufferView *)arg0)->unk148);
    }
    if (((ActorBufferView *)arg0)->unk14C != NULL) {
        heapFree(((ActorBufferView *)arg0)->unk14C);
    }
    func_8062D26C(arg0);
    if (arg0->actorType != 0x12B) {
        resQueueRemove(arg0);
    }
    renderCallbacksDisableForActor(arg0);
    actorTableRemove(arg0);
    heapFree(arg0);
}

void func_806787CC(void) {
    actorListUpdateSpawns();
}

static void func_806787EC(void) {}
static void func_806787F4(void) {}
static void func_806787FC(void) {}
static void func_80678804(void) {}
static void func_8067880C(void) {}
static void func_80678814(void) {}
static void func_8067881C(void) {}

void actorUpdateActiveList(u8);
void actorGlobalCallbacksDispatchAndFree();
void actorDelayedCallbacksTick(void);

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
    func_80678B04();
    D_807FBE09 = 0;
    actorFlushDespawnQueue();
    actorDelayedCallbacksTick();
}

extern void (*D_8074C0A0[])(void);
void actorPostTick(Actor *);

extern u16 D_807FBB3C;

void actorUpdateActiveList(u8 arg0) {
    s32 i;

    for (i = D_807FBB3C = 0; i < gActiveActorCount; i = D_807FBB3C = i + 1) {
        D_807FBE08 = 0;
        D_807FBB40 = gActiveActors[i].actor;
        if ((arg0 == 1 && !(D_807FBB40->flags & 0x100000)) || (arg0 == 2 && (D_807FBB40->flags & 0x100000))) {
            actorPreTick(D_807FBB40);
            D_8074C0A0[D_807FBB40->actorType]();
            actorPostTick(D_807FBB40);
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
        D_807FBB40 = gActiveActors[i].actor;
        if (D_807FBB40->unk64 & 2) {
            actorPreTick(D_807FBB40);
            D_8074C0A0[D_807FBB40->actorType]();
            actorPostTick(D_807FBB40);
        }
        if (D_807FBB40->unk4 != NULL) {
            actorCheckWorldBounds(D_807FBB40);
        }
    }
    actorGlobalCallbacksDispatchAndFree(1);
    func_80678B04();
}

void func_80678B04(void) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x08000000) && (actor->flags & 0x500) && (actor->flags & 0x4000)) {
            actorCheckWorldBounds(actor);
        }
        actor->flags &= ~0x100;
    }
}

void actorPreTick(Actor *arg0) {
    collisionClearFlags(arg0);
    if (arg0->unk5C & 1) {
        playerSetActiveGlobals(arg0);
    }
    arg0->prevX = arg0->x;
    arg0->prevY = arg0->y;
    arg0->prevZ = arg0->z;
    arg0->prevSpeedXZ = arg0->speedXZ;
    D_807F94B4 = 0;
    if (arg0->unk140 != NULL) {
        arg0->unk140->unk68 = 0;
    }
    actorRiderListFree(arg0);
    if (arg0 == D_807FBB48) {
        actorCollisionCheckBoundingBoxes(arg0);
    } else {
        actorInitDamage(arg0);
    }
    actorDispatchCallbacks(arg0);
    if (arg0 == D_807FBB48) {
        playerStateDispatchQueuedCallback();
    }
    if (arg0->unk144 & 4) {
        actorUpdateMovementFlags(arg0);
    } else if (arg0->unk140 != NULL) {
        arg0->unk140->unk6C = 0;
    }
    if (arg0->unk110 != 0) {
        actorUpdateSubnodeRotationAndMtx(arg0);
    }
}

typedef struct ActorUnk156View {
    u8 pad[0x156];
    u8 unk156;
} ActorUnk156View;

void actorUpdatePositionAndSub140(Actor *);
void func_80678E6C(Actor *);
void actorUpdateModelMatrices(Actor *);
void actorDispatchCollisionResults(Actor *);
void actorUpdateEffects(Actor *);
void animListUpdate(Actor *);

void actorPostTick(Actor *actor) {
    if ((void *)func_8067B3F4 == (void *)D_8074DA30[D_8074D8D4[actor->actorType]]) {
        guTranslateF((void *)((u8 *)actor + 0xC), actor->x, actor->y, actor->z);
    }
    actorUpdatePositionAndSub140(actor);
    func_80678E6C(actor);
    if (!(actor->flags & 0x08000000)) {
        actor->flags &= ~0x200;
        if (actor->unk4 != NULL) {
            controllerStepMotionWindows(actor);
            if (((actor->flags & 0x500) || ((ActorUnk156View *)actor)->unk156 != 0) && !(actor->flags & 0x4000)) {
                actorCheckWorldBounds(actor);
            }
        }
    }
    func_80678E14(actor);
    actorUpdateModelMatrices(actor);
    actorGlobalCallbacksDispatchAndFree(0);
    actorDispatchCollisionResults(actor);
    actorFreeCallbackList(actor);
    actorUpdateEffects(actor);
    animListUpdate(actor);
    actor->flags |= 0x10;
}

void func_80678DD8(Actor *actor) {
    controllerStepMotionWindows();
    if (actor->flags & 0x500) {
        actorCheckWorldBounds(actor);
    }
}

void func_80678E14(Actor *actor) {
    f32 temp_fv0 = actor->y;

    if (actor->prevY < temp_fv0) {
        actor->unk9C = temp_fv0;
        return;
    }
    if (actor->unk6A & 5) {
        if (actor->unk6C & 5) {
            actor->unk9C = temp_fv0;
            return;
        }
        actor->unkA0 = actor->unk9C;
    }
}

u8 actorClearTargetAngle();
extern u8 D_807FBC55;
void playerStateQueueCallback(s32, s32, u8);
extern u8 gCurrentPlayerIndex;

void func_80678E6C(Actor *actor) {
    u8 sp27;

    if ((actor->unk144 & 4) && (D_807FBE08 == 0)) {
        if (actor->flags & 0x10000) {
            actor->unkFC = 0;
            actor->unkFD = 0;
        }
        actor->unkFC |= actorClearTargetAngle(actor, &actor->unkF4, &actor->unkF6, &sp27);
        sp27 |= D_807FBC55;
        if (sp27 != 0) {
            if (!(actor->unk6A & 0x10)) {
                actor->unk6A |= 0x10;
                if (actor == D_807FBB48) {
                    playerStateQueueCallback(4, 0, gCurrentPlayerIndex);
                }
            }
        }
        if (sp27 == 0) {
            actor->unk6A &= ~0x10;
        }
    } else {
        actor->unkFC = 0;
        actor->unkFD = 0;
        actor->unk6A &= ~0x10;
    }
}

void actorRiderListFree(Actor *actor) {
    if (actor->unk114 != NULL) {
        heapFree(actor->unk114);
        actor->unk114 = NULL;
    }
}

void actorRiderListAdd(Actor *actor, s32 item) {
    if (actor->unk114 == NULL) {
        actor->unk114 = heapAlloc(sizeof(ActorList));
        actor->unk114->count = 0;
    }
    if (actor->unk114->count != 4) {
        actor->unk114->items[actor->unk114->count] = item;
        actor->unk114->count++;
    }
}

s32 actorRiderListContains(Actor *actor, s32 item) {
    ActorList *list = actor->unk114;
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

void actorRegisterGlobalCallback(ActorCallbackNode *arg0) {
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
        D_807FBFE0[i] = arg0;
    }
}

void actorGlobalCallbacksDispatchAndFree(arg0)
u8 arg0;
{
    ActorCallbackNode **ptr = D_807FBFE0; do { if (((*ptr) != 0) && ((*ptr)->unk4 == arg0)) { ((void (*)(void *)) (*ptr)->callback)(&(*ptr)->unk8); heapFree(*ptr); *ptr = 0; } ptr++; } while (ptr != ((ActorCallbackNode **) (&D_807FBFF0))); // LAYOUT: one-line statement line coordinates steer mirrored-pair scheduling
}

void actorFreeCallbackList(Actor *actor) {
    ActorCallbackNode *node = actor->unk13C;
    ActorCallbackNode *next;

    if (node != NULL) {
        actor->unk13C = NULL;
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
    actor->unk138 |= mask;
}

void actorCallbackMaskDisable(Actor *actor, s32 mask) {
    actor->unk138 &= ~mask;
}

void actorAppendCallback(Actor *actor, s32 arg1, s32 arg2, u8 arg3, s32 arg4, void *arg5) {
    s32 pad;
    ActorCallbackNode **link;
    ActorCallbackNode *prev;
    ActorCallbackNode *curr;
    ActorCallbackNode *node;

    prev = NULL;
    if (actorTableContains(actor)) {
        curr = actor->unk13C;
        link = &actor->unk13C;
        if (curr != NULL) {
            do {
                link = &curr->next;
                prev = curr;
                curr = curr->next;
            } while (curr != NULL);
        }
        node = actorAllocCallbackNode(arg1, arg2, arg3, arg4, arg5);
        *link = node;
        node->prev = prev;
    }
}

void actorQueueDelayedCallback(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, void *arg5, s32 arg6) {
    if (D_807FBFD8 == 16) {
        faultSetMessage(0xF, 0, 0, 0);
    }
    D_807FBF18[D_807FBFD8].node = actorAllocCallbackNode(arg1, arg2, arg3, arg4, arg5);
    D_807FBF18[D_807FBFD8].arg0 = arg0;
    D_807FBF18[D_807FBFD8].arg6 = arg6;
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
                curr = actor->unk13C;
                link = &actor->unk13C;
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

ActorCallbackNode *actorAllocCallbackNode(s32 arg0, s32 arg1, u8 arg2, s32 arg3, void *arg4) {
    ActorCallbackNode *node = heapAlloc(sizeof(ActorCallbackNode));

    node->callback = (void *)arg1;
    node->unk4 = arg2;
    node->unk8 = arg0;
    node->unkC = arg3;
    node->unk10 = arg4;
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

void actorCollisionProcessHit(Actor *, ActorCallbackNode *);
void playerHandleDamageReaction(Actor *, Actor *, u8);
ActorCallbackNode *actorCallbackListSort(ActorCallbackNode *);
s32 actorCheckPointInAngleArc(Actor *, f32, f32);

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

#define GSTATE (*(ActorDispatchState *)&D_807FBB70)


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
void actorDispatchCallbacks(Actor *arg0) {
    s16 pad[2];
    s32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 sp40;
    s16 sp3E;
    s8 var_s7;
    u8 temp_v1_2;
    u8 temp_v1_3;
    ActorPayloadA7EC *temp_s0;
    ActorCollisionHit *temp_s0_2;
    ActorPayload10000 *temp_s0_3;
    ActorCallbackNode *temp_v0;
    f32 *temp_v0_10;
    ActorPayloadABC0 *temp_v0_11;
    ActorPlayerState *temp_v0_3;
    ActorPayloadAAB8 *temp_v0_4;
    ActorPayloadA69C *temp_v0_5;
    ActorPayloadA70C *temp_v0_6;
    f32 *temp_v0_7;
    ActorPayloadAAB8 *temp_v0_8;
    ActorSub140 *temp_v0_9;
    s32 *temp_v1_4;
    Actor *temp_v1;
    ActorCallbackNode *var_s2;

    var_s7 = -1;
    actorGlobalStateClearEvents();
    temp_v0 = actorCallbackListSort(arg0->unk13C);
    arg0->unk13C = temp_v0;
    var_s2 = temp_v0;
    sp50 = arg0->unk138;
    if (temp_v0 != NULL) {
        do {
            if ((s32)var_s2->callback == 0) {}  // FAKE: dead test steers uopt colouring of the callback id (a0 vs a1)
            if ((s32)var_s2->callback & sp50) {
                switch ((s32)var_s2->callback) {
                case 0x8000:
                    actorCollisionProcessHit(arg0, var_s2);
                    if (((GSTATE.unk200 == 9) || (GSTATE.unk200 == 0xA)) && (arg0->unk5C & 1)) {
                        playerHandleDamageReaction(arg0, GSTATE.unk1FC, (GSTATE.unk200 == 0xA));
                    }
                    break;
                case 0x2:
                    switch (var_s2->unk4) {
                    case 0:
                        GSTATE.unk16 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x10, NULL, gCurrentPlayerIndex);
                        }
                        break;
                    case 1:
                        GSTATE.unk17 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0xE, var_s2->unk8, gCurrentPlayerIndex);
                        }
                        break;
                    case 2:
                        GSTATE.unk18 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x12, NULL, gCurrentPlayerIndex);
                        }
                        break;
                    case 3:
                        GSTATE.unk19 = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x13, NULL, gCurrentPlayerIndex);
                        }
                        break;
                    case 6:
                        GSTATE.unk1B = 1;
                        if (arg0 == D_807FBB48) {
                            playerStateQueueCallback(0x36, var_s2->unk8, gCurrentPlayerIndex);
                        }
                        break;
                    case 4:
                    case 5:
                        if (arg0 == D_807FBB48) {
                            if (var_s2->unk4 == 4) {
                                playerStateQueueCallback(0x2B, var_s2->unk8, gCurrentPlayerIndex);
                            } else {
                                playerStateQueueCallback(0x32, var_s2->unk8, gCurrentPlayerIndex);
                            }
                            temp_v1 = (Actor *)var_s2->unk8;
                            if ((temp_v1 != NULL) && (temp_v1->unk5C & 2)) {
                                temp_v0_3 = (ActorPlayerState *)temp_v1->unk174;
                                temp_v0_3->unk1A = (u16)(temp_v0_3->unk1A | 0x100);
                            }
                        }
                        break;
                    }
                    break;
                case 0x8:
                    playerHandleDamageReaction(arg0, (Actor *)var_s2->unk8, 0);
                    break;
                case 0x4:
                    playerHandleDamageReaction(arg0, (Actor *)var_s2->unk8, 1);
                    break;
                case 0x800:
                    arg0->unk144 = (u8)var_s2->unk4;
                    GSTATE.unk90 = 1;
                    break;
                case 0x400:
                    temp_v0_4 = (ActorPayloadAAB8 *)var_s2->unk10;
                    PLAYER_STATE_VIEW->unk70 = temp_v0_4->unk0;
                    PLAYER_STATE_VIEW->unk74 = temp_v0_4->unk4;
                    PLAYER_STATE_VIEW->unk6C = (f32)temp_v0_4->unk8;
                    GSTATE.unk1A = 1;
                    if (arg0 == D_807FBB48) {
                        playerStateQueueCallback(0x17, var_s2->unk8, gCurrentPlayerIndex);
                    }
                    break;
                case 0x10:
                    temp_v0_5 = (ActorPayloadA69C *)var_s2->unk10;
                    temp_v1_2 = temp_v0_5->unk8;
                    if (var_s7 < (s32)temp_v1_2) {
                        sp4C = temp_v0_5->unk0;
                        var_s7 = (s8)temp_v1_2;
                        sp44 = temp_v0_5->unk4;
                        sp40 = (s32)var_s2->callback;
                        *(u8 *)&sp3E = temp_v0_5->unk9;
                    }
                    break;
                case 0x20:
                    temp_v0_6 = (ActorPayloadA70C *)var_s2->unk10;
                    temp_v1_3 = temp_v0_6->unkC;
                    if (var_s7 < (s32)temp_v1_3) {
                        sp4C = temp_v0_6->unk0;
                        var_s7 = (s8)temp_v1_3;
                        sp48 = temp_v0_6->unk4;
                        sp44 = temp_v0_6->unk8;
                        sp40 = (s32)var_s2->callback;
                        *(u8 *)&sp3E = temp_v0_6->unkD;
                    }
                    break;
                case 0x100000:
                    temp_v0_7 = (f32 *)var_s2->unk10;
                    GSTATE.unkD8 = temp_v0_7[0];
                    GSTATE.unkDC = temp_v0_7[1];
                    GSTATE.unkE0 = temp_v0_7[2];
                    GSTATE.unkE4 = 1;
                    GSTATE.unkEC = (Actor *)var_s2->unk8;
                    break;
                case 0x1000:
                    GSTATE.unk1C = 1;
                    GSTATE.unk20 = (Actor *)var_s2->unk8;
                    break;
                case 0x4000:
                    temp_v0_8 = (ActorPayloadAAB8 *)var_s2->unk10;
                    GSTATE.unk2C = 1;
                    GSTATE.unk30 = temp_v0_8->unk4;
                    GSTATE.unk34 = temp_v0_8->unk8;
                    GSTATE.unk36 = temp_v0_8->unk0;
                    break;
                case 0x2000:
                    if (var_s2->unk4 != 0) {
                        GSTATE.unk24 = 1;
                    } else {
                        GSTATE.unk25 = 1;
                    }
                    GSTATE.unk28 = (Actor *)var_s2->unk8;
                    break;
                case 0x80:
                    arg0->flags = (s32)(arg0->flags | 8);
                    if (arg0 == D_807FBB48) {
                        playerStateQueueCallback(0x16, var_s2->unk8, gCurrentPlayerIndex);
                    }
                    break;
                case 0x40:
                    if (var_s2->unk4 != 0) {
                        arg0->flags = (s32)(arg0->flags | 4);
                    } else {
                        arg0->flags = (s32)(arg0->flags & ~4);
                    }
                    break;
                case 0x1:
                    temp_s0 = (ActorPayloadA7EC *)var_s2->unk10;
                    if (actorTableContains(var_s2->unk8) != 0 && GSTATE.unk39 != 4) {
                        GSTATE.unk3C[GSTATE.unk39][0] = temp_s0->unk0;
                        GSTATE.unk3C[GSTATE.unk39][1] = temp_s0->unk4;
                        GSTATE.unk3C[GSTATE.unk39][2] = temp_s0->unk8;
                        GSTATE.unk6C[GSTATE.unk39] = temp_s0->unkC;
                        GSTATE.unk7C[GSTATE.unk39] = (Actor *)var_s2->unk8;
                        GSTATE.unk8C[GSTATE.unk39] = temp_s0->unk10;
                        GSTATE.unk39++;
                        actorRiderListAdd(arg0, var_s2->unk8);
                    }
                    break;
                case 0x20000:
                    temp_s0_2 = (ActorCollisionHit *)var_s2->unk10;
                    if (GSTATE.unk1F8 != 4) {
                        memcpy(&GSTATE.unkF8[GSTATE.unk1F8], temp_s0_2, 0xC);
                        memcpy(GSTATE.unkF8[GSTATE.unk1F8].unkC, temp_s0_2->unkC, 0x24);
                        GSTATE.unkF8[GSTATE.unk1F8].unk30 = temp_s0_2->unk30;
                        GSTATE.unkF8[GSTATE.unk1F8].unk34 = temp_s0_2->unk34;
                        GSTATE.unkF8[GSTATE.unk1F8].unk38 = temp_s0_2->unk38;
                        GSTATE.unkF8[GSTATE.unk1F8].unk3C = (Actor *)var_s2->unk8;
                        GSTATE.unk1F8++;
                    }
                    break;
                case 0x10000:
                    temp_s0_3 = (ActorPayload10000 *)var_s2->unk10;
                    GSTATE.unk91 = 1;
                    GSTATE.unk92 = temp_s0_3->unk0;
                    GSTATE.unk94 = temp_s0_3->unk2;
                    memcpy(&D_807FBC08, temp_s0_3->unk4, 0xC);
                    memcpy(&D_807FBC14, temp_s0_3->unk10, 0x24);
                    GSTATE.unkC8 = temp_s0_3->unk34;
                    GSTATE.unkCC = (Actor *)var_s2->unk8;
                    GSTATE.unkD0 = temp_s0_3->unk38;
                    GSTATE.unkD4 = temp_s0_3->unk3C;
                    break;
                case 0x40000:
                    temp_v1_4 = var_s2->unk10;
                    temp_v0_9 = arg0->unk140;
                    if (temp_v0_9 != NULL) {
                        temp_v0_9->unk68 = *temp_v1_4;
                    }
                    break;
                case 0x80000:
                    GSTATE.unk38 = 1;
                    break;
                case 0x200000:
                    temp_v0_10 = (f32 *)var_s2->unk10;
                    GSTATE.unkF0 = temp_v0_10[0];
                    GSTATE.unkF4 = temp_v0_10[1];
                    break;
                case 0x400000:
                    GSTATE.unkE8 = (f32)(u32)var_s2->unk4;
                    GSTATE.unkE5 = 1;
                    break;
                case 0x1000000:
                    if (GSTATE.unk254 < 8) {
                        GSTATE.unk258[GSTATE.unk254] = var_s2->unk4;
                        GSTATE.unk278[GSTATE.unk254] = var_s2->unk10;
                        GSTATE.unk254++;
                    }
                    break;
                case 0x800000:
                    temp_v0_11 = (ActorPayloadABC0 *)var_s2->unk10;
                    GSTATE.unk4 = temp_v0_11->unk0;
                    GSTATE.unk8 = temp_v0_11->unk4;
                    GSTATE.unkC = temp_v0_11->unk8;
                    GSTATE.unk10 = temp_v0_11->unkC;
                    GSTATE.unk12 = temp_v0_11->unkE;
                    GSTATE.unk2 = 1;
                    GSTATE.unk14 = var_s2->unk4;
                    break;
                case 0x2000000:
                    GSTATE.unk0 = 1;
                    GSTATE.unk1 = var_s2->unk4;
                    break;
                }
            }
            var_s2 = var_s2->next;
        } while (var_s2 != NULL);
    }
    if ((var_s7 != -1) && ((*(u8 *)&sp3E == 1) || (actorCheckPointInAngleArc(arg0, sp4C, sp44) != 0))) {
        switch (sp40) {
        case 16:
            arg0->x = sp4C;
            arg0->z = sp44;
            return;
        case 32:
            arg0->x = sp4C;
            arg0->y = sp48;
            arg0->z = sp44;
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
    u8 unk1A4;
    u8 pad1A5[0x1F0 - 0x1A5];
    u32 unk1F0;
    u8 pad1F4[0x200 - 0x1F4];
    u16 unk200;
} DamageReactionContext;
extern DamageReactionContext *gActivePlayerState;

extern u8 D_807FBB85;
extern s32 D_80720E2C;
void effectSpawnBurstParticleCluster(Actor *);
s32 func_80714608(s32);
u8 playerIsSmallerThanAttacker(Actor *, Actor *);
void func_807149FC(s32);
void func_807149B8(s32);
void func_8071498C(void *);
s32 func_80714C08(void *, s32, Actor *, s32, s32);
void effectPulseSpinUpdate(void);
void playerHandleDamageReaction(Actor *arg0, Actor *arg1, u8 arg2) {
    s32 sp3C;
    s32 var_a2;
    void *sp24;
    s32 pad;
    s32 var_v0;

    D_807FBB85 = 1;
    if (arg0 == D_807FBB48) {
        if (!(((DamageReactionPlayerEntry *)gPlayerSlots)[gActivePlayerState->unk1A4].unk2C0 == 2 && arg1 != NULL && (arg1->unk5C & 2))) {
            sp3C = 0x2E;
            var_a2 = 1;
            if (arg2 != 0) {
                sp3C = 0x30;
            }
            if (arg1 != NULL && arg1->actorType == 0x116) {
                effectSpawnBurstParticleCluster(arg0);
                switch (arg1->unk155[0]) {
                case 1:
                    var_a2 = 0;
                    gActivePlayerState->unk1F0 ^= 0x80;
                    break;
                case 2:
                    sp3C = 0x27;
                    break;
                case 3:
                    func_807149FC(0xF0);
                    func_807149B8(1);
                    sp24 = &effectPulseSpinUpdate;
                    func_8071498C(&effectPulseSpinUpdate);
                    func_80714C08(&D_80720E2C, 0x3ECCCCCD, arg0, 1, 2);
                    func_807149FC(0xF0);
                    func_807149B8(1);
                    func_8071498C(sp24);
                    func_80714C08(&D_80720E2C, 0x3EC28F5C, arg0, 5, 2);
                    func_807149FC(0xF0);
                    func_807149B8(1);
                    func_8071498C(sp24);
                    func_80714C08(&D_80720E2C, 0x3E99999A, arg0, 6, 2);
                    var_a2 = 0;
                    gActivePlayerState->unk1F0 |= 0x08000000;
                    break;
                }
                gActivePlayerState->unk200 = 0xF0;
            } else if (arg1 != NULL && ((arg1->unk5C & 1) || (arg1->unk5C & 4) || (arg1->unk5C & 2))) {
                if (func_80714608(0) != 0) {
                    if (playerIsSmallerThanAttacker(arg0, arg1) != 0) {
                        sp3C = 0x31;
                    } else {
                        var_v0 = 1;
                        if (arg1->unk5C & 4) {
                            var_v0 = 3;
                        }
                        if (arg1->state != 0x28 && var_v0 < 3) {
                            sp3C = 0x2B;
                        } else {
                            sp3C = 0xE;
                        }
                    }
                }
            }
            if (var_a2 != 0) {
                playerStateQueueCallback((s16)sp3C, (s32)arg1, gCurrentPlayerIndex);
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

void actorCollisionEventsCancel(s32 arg0, u8 arg1) {
    s32 i;

    for (i = 0; i < D_807FBB70.unk201; i++) {
        if ((D_807FBB70.unk244[i] == arg1) && (D_807FBB70.unk204[i] == arg0)) {
            D_807FBB70.unk244[i] = 0;
        }
    }
}

extern u8 D_807FBC68[][0x40];
extern u8 D_807FBC74[][0x40];

typedef struct ActorVec3f {
    f32 x;
    f32 y;
    f32 z;
} ActorVec3f;

typedef struct ActorCollisionSlot {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    u8 pad10[0x30];
} ActorCollisionSlot;

typedef struct ActorCollisionState {
    u8 pad0[0x3C];
    ActorVec3f unk3C[4];
    s32 unk6C[4];
    s32 unk7C[4];
    u8 unk8C[4];
    u8 unk90;
    u8 unk91;
    u8 pad92[0x36];
    s32 unkC8;
    s32 unkCC;
    s32 unkD0;
    s32 unkD4;
    u8 padD8[0x50];
    ActorCollisionSlot unk128[1];
} ActorCollisionState;

#define COLLISION_STATE ((ActorCollisionState *)&D_807FBB70)

s32 actorCollisionGetNodeHitPoint(Actor *, s32, f32 *, f32 *);
void collisionTransformPointByActorMtx(Actor *, u32, f32 *, f32, f32 *);
void actorCollisionResolveSurfaceHit(Actor *, s32, void *, void *, s32, s32, s32, s32);
void playerDropHeldActor(Actor *);

void actorDispatchCollisionResults(Actor *arg0) {
    s32 i;
    f32 sp68;
    f32 sp64;
    s32 pad60;
    f32 sp5C;
    f32 sp58;

    for (i = 0; i < D_807FBB70.unk201; i++) {
        switch (D_807FBB70.unk244[i]) {
        case 0:
            break;
        case 1:
            if (actorCollisionGetNodeHitPoint(arg0, D_807FBB70.unk204[i], &sp68, &sp64) != 0) {
                func_8067A69C((s32)arg0, (Actor *)D_807FBB70.unk204[i], sp68, sp64, 0, 1);
            }
            break;
        case 2:
            actorCollisionGetNodeHitPoint(arg0, D_807FBB70.unk204[i], &sp5C, &sp58);
            break;
        case 4:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 1, 0, 0);
            break;
        case 3:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 0, 0, 0);
            break;
        case 8:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 2, 0, 0);
            break;
        case 10:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 3, 0, 0);
            break;
        case 13:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 6, 0, 0);
            break;
        case 11:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 4, 0, 0);
            break;
        case 12:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 2, 5, 0, 0);
            break;
        case 6:
        case 7:
            if (D_807FBB70.unk244[i] == 6) {
                actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x40, 0, 0, 0);
            }
            func_8067A70C((s32)arg0, (Actor *)D_807FBB70.unk204[i], arg0->x, arg0->y, arg0->z, 2, 1);
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x80, 0, 0, 0);
            playerDropHeldActor(arg0);
            break;
        case 5:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 8, 0, 0, 0);
            break;
        case 15:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 4, 0, 0, 0);
            break;
        case 9:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x1000, 0, 0, 0);
            break;
        case 14:
            actorAppendCallback((Actor *)D_807FBB70.unk204[i], (s32)arg0, 0x02000000, 0, 0, 0);
            break;
        }
    }

    if (D_807FBB70.unk39) {
        for (i = 0; i < D_807FBB70.unk39; i++) {
            if (COLLISION_STATE->unk8C[i] == 0) {
                collisionTransformPointByActorMtx(arg0, COLLISION_STATE->unk6C[i], &COLLISION_STATE->unk3C[i].x, COLLISION_STATE->unk3C[i].y, &COLLISION_STATE->unk3C[i].z);
                func_8067A69C((s32)arg0, (Actor *)COLLISION_STATE->unk7C[i], COLLISION_STATE->unk3C[i].x, COLLISION_STATE->unk3C[i].z, 1, 1);
            }
        }
    }

    if (D_807FBB70.unk91 != 0) {
        actorCollisionResolveSurfaceHit(arg0, COLLISION_STATE->unkCC, &D_807FBC08, &D_807FBC14, COLLISION_STATE->unkC8, COLLISION_STATE->unkD0, COLLISION_STATE->unkD4, 1);
    }

    for (i = 0; i < D_807FBB70.unk1F8; i++) {
        actorCollisionResolveSurfaceHit(arg0, COLLISION_STATE->unk128[i].unkC, D_807FBC68[i], D_807FBC74[i], COLLISION_STATE->unk128[i].unk0, COLLISION_STATE->unk128[i].unk4, COLLISION_STATE->unk128[i].unk8, 0);
    }
}

void func_8067A69C(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    ActorPayloadA69C *temp = heapAlloc(sizeof(ActorPayloadA69C));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unk9 = arg5;
    actorAppendCallback(arg1, arg0, 0x10, 0, 1, temp);
}

void func_8067A70C(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, u8 arg6) {
    ActorPayloadA70C *temp = heapAlloc(sizeof(ActorPayloadA70C));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unkC = arg5;
    temp->unkD = arg6;
    actorAppendCallback(arg1, arg0, 0x20, 0, 1, temp);
}

void func_8067A784(s32 arg0, Actor *arg1, s16 arg2, f32 arg3, s16 arg4) {
    ActorPayloadAAB8 *temp = heapAlloc(sizeof(ActorPayloadAAB8));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    actorAppendCallback(arg1, arg0, 0x4000, 0, 1, temp);
}

void func_8067A7EC(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, u8 arg6) {
    ActorPayloadA7EC *temp = heapAlloc(sizeof(ActorPayloadA7EC));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unkC = arg5;
    temp->unk10 = arg6;
    actorAppendCallback(arg1, arg0, 0x1, 0, 1, temp);
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

void func_8067A864(s32 arg0, Actor *arg1, s16 arg2, s16 arg3, void *arg4, void *arg5, s32 arg6, s32 arg7, s32 arg8) {
    ActorPayloadA864 *temp = heapAlloc(sizeof(ActorPayloadA864));
    temp->unk0 = arg2;
    temp->unk2 = arg3;
    memcpy(temp->unk4, arg4, 0xC);
    memcpy(temp->unk10, arg5, 0x24);
    temp->unk34 = arg6;
    temp->unk38 = arg7;
    temp->unk3C = arg8;
    actorAppendCallback(arg1, arg0, 0x10000, 0, 1, temp);
}

typedef struct ActorPayloadA908 {
    u8 unk0[0xC];
    u8 unkC[0x24];
    s32 unk30;
    s32 unk34;
    s32 unk38;
} ActorPayloadA908;

void func_8067A908(s32 arg0, Actor *arg1, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6) {
    ActorPayloadA908 *temp = heapAlloc(sizeof(ActorPayloadA908));
    memcpy(temp, arg2, 0xC);
    memcpy((u8 *)temp + 0xC, arg3, 0x24);
    temp->unk30 = arg4;
    temp->unk34 = arg5;
    temp->unk38 = arg6;
    actorAppendCallback(arg1, arg0, 0x20000, 0, 1, temp);
}

void func_8067A99C(s32 arg0, Actor *arg1, s32 arg2) {
    s32 *temp = heapAlloc(sizeof(s32));
    *temp = arg2;
    actorAppendCallback(arg1, arg0, 0x40000, 0, 1, temp);
}

void func_8067A9F0(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 *temp = heapAlloc(3 * sizeof(f32));
    temp[0] = arg2;
    temp[1] = arg3;
    temp[2] = arg4;
    actorAppendCallback(arg1, arg0, 0x100000, 0, 1, temp);
}

void func_8067AA58(s32 arg0, Actor *arg1, f32 arg2, f32 arg3) {
    f32 *temp = heapAlloc(2 * sizeof(f32));
    temp[0] = arg2;
    temp[1] = arg3;
    actorAppendCallback(arg1, arg0, 0x200000, 0, 1, temp);
}

void func_8067AAB8(s32 arg0, Actor *arg1, s16 arg2, f32 arg3, s16 arg4) {
    ActorPayloadAAB8 *temp = heapAlloc(sizeof(ActorPayloadAAB8));
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unk0 = arg2;
    actorAppendCallback(arg1, arg0, 0x400, 0, 1, temp);
}

void func_8067AB20(s32 arg0, Actor *arg1, s32 arg2, u8 arg3, void *arg4, u8 arg5) {
    void *temp = heapAlloc(8);
    memcpy(temp, arg4, 8);
    if (!arg5) {
        actorAppendCallback(arg1, arg0, arg2, arg3, 1, temp);
    } else {
        actorQueueDelayedCallback((s32)arg1, arg0, arg2, arg3, 1, temp, 1);
    }
}

void func_8067ABC0(s32 arg0, Actor *arg1, u8 arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6, f32 arg7) {
    ActorPayloadABC0 *temp = heapAlloc(sizeof(ActorPayloadABC0));
    temp->unk0 = arg5;
    temp->unk4 = arg6;
    temp->unk8 = arg7;
    temp->unkC = arg3;
    temp->unkE = arg4;
    actorAppendCallback(arg1, arg0, 0x800000, arg2, 1, temp);
}

void actorGlobalStateClearEvents(void) {
    D_807FBB70.unkE5 = 0;
    D_807FBB70.unk15 = 0;
    D_807FBB70.unk16 = 0;
    D_807FBB70.unk17 = 0;
    D_807FBB70.unk18 = 0;
    D_807FBB70.unk19 = 0;
    D_807FBB70.unk1B = 0;
    D_807FBB70.unk1A = 0;
    D_807FBB70.unk1C = 0;
    D_807FBB70.unk24 = 0;
    D_807FBB70.unk25 = 0;
    D_807FBB70.unk2C = 0;
    D_807FBB70.unk38 = 0;
    D_807FBB70.unkE4 = 0;
    D_807FBB70.unk90 = 0;
    D_807FBB70.unk39 = 0;
    D_807FBB70.unk91 = 0;
    D_807FBB70.unk1F8 = 0;
    D_807FBB70.unk1FC = 0;
    D_807FBB70.unk200 = 0;
    D_807FBB70.unk201 = 0;
    D_807FBB70.unk254 = 0;
    D_807FBB70.unk2 = 0;
    D_807FBB70.unk0 = 0;
    D_807FBB70.unkE8 = 0.0f;
    D_807FBB70.unkF0 = 0.0f;
    D_807FBB70.unkF4 = 0.0f;
}

void func_8067ACB4(Actor *arg0) {
    arg0->unk6C = arg0->unk6A;
}

u16 func_8067ACC0(u16 arg0) {
    return D_8074D624[arg0];
}

s32 actorCountOwnedByClass(arg0, arg1, arg2)
s32 arg0;
u16 arg1;
s32 (*arg2)(Actor *);
{
    u16 count = 0;
    s32 i;

    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (arg0 == actor->unk11C && actor->unk5C == arg1) {
            if (arg2 == NULL || arg2(actor)) {
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

void actorTableSort(void);

Actor *actorFindByType(u16 arg0) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (actor->actorType == arg0) {
            return actor;
        }
    }
    return NULL;
}

s32 actorIsActive(Actor *arg0) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (arg0 == actor) {
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

void actorTableInsert(Actor *arg0) {
    if (D_807FC3F0 < 256) {
        D_807FBFF0[D_807FC3F0++] = (s32)arg0;
    } else {
        faultSetMessage(0x13, arg0->actorType, 0, 0);
    }
    actorTableSort();
}

void actorTableRemove() {
    s32 res = actorTableBinarySearch();
    s16 idx = res;
    if ((u32)res != (u32)-1) {
        D_807FBFF0[idx] = -1;
        actorTableSort();
    }
}

s32 actorTableContains(void) {
    if (actorTableBinarySearch() != -1) {
        return 1;
    }
    return 0;
}

s32 actorTableBinarySearch(u32 arg0) {
    s16 low = 0;
    s16 high = D_807FC3F0 - 1;

    if (D_807FC3F0 == 0) {
        return -1;
    }
    while (low <= high) {
        s16 mid = (low + high) >> 1;

        if (arg0 == D_807FBFF0[mid]) {
            return mid;
        }
        if (arg0 < D_807FBFF0[mid]) {
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
    u8 unk1A4;
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
extern PlayerContextArray950 D_807FC950[];
extern void *D_807FD568;
extern s32 D_807ECDEC;
extern u16 D_807ECDF0;
extern PlayerContext5C414 D_8075C414[];
extern s16 D_807FD584;

void playerSetActiveGlobals(Actor *arg0) {
    u8 temp_v0;
    PlayerContextEntry *player;

    gActivePlayerState = arg0->unk174;
    gCurrentPlayerIndex = ((PlayerContextSub174 *)gActivePlayerState)->unk1A4;
    temp_v0 = gPlayerCharacterId[gCurrentPlayerIndex];
    player = (PlayerContextEntry *)gPlayerSlots + gCurrentPlayerIndex;
    D_807FBB48 = player->actor;
    D_807FD568 = &D_807FC950[gCurrentPlayerIndex].sub[temp_v0];
    D_807ECDEC = player->unk294;
    D_807ECDF0 = *player->unk298;
    D_807FD584 = D_8075C414[temp_v0].unk0;
    player->unk2C1 = 0;
}

u8 playerFindIndexByActor(s32 arg0) {
    s32 i;
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].unk0 != 0 && arg0 == gPlayerSlots[i].unk4) {
            return (u8)i;
        }
    }
    return 0;
}

void actorCopyPoseAndScale(Actor *arg0, Actor *arg1, f32 arg2) {
    arg0->x = arg1->x;
    arg0->y = arg1->y;
    arg0->z = arg1->z;
    arg0->yaw = arg1->yaw;
    if (arg0->unk4 != NULL) {
        arg0->unk4->unk34 = arg2;
        arg0->unk4->unk38 = arg2;
        arg0->unk4->unk3C = arg2;
    }
}

void func_8067B280(void) {}
void func_8067B288(void) {}
void func_8067B290(void) {}
void func_8067B298(void) {}
void func_8067B2A0(void) {}
void func_8067B2A8(void) {}

void func_8067B2B0(s32 arg0) {
}

void func_8067B2B8(s32 arg0) {
}

s32 func_8067B2C0(s32 arg0) {
    D_807FBB44->unk144 = 1;
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

s32 func_8067B2DC(ActorInitArg *arg0) {
    if (controllerAnimInit(D_807FBB44, arg0->unk2, arg0) != 0) {
        D_807FBB44->unk140 = actorSub140CreateFromModel(D_807FBB44);
        D_807FBB44->unk15E = (u32)(((f64)((ActorSub140View *)D_807FBB44->unk140)->unkC * 0.15) * 0.5);
        return 1;
    }
    return 0;
}

s32 func_8067B3F4(s32 arg0) {
    D_807FBB44->unk140 = actorSub140CreateFromModel(D_807FBB44);
    return 1;
}

s32 func_8067B42C(s32 arg0) {
    D_807FBB44->flags |= 0x2000;
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
