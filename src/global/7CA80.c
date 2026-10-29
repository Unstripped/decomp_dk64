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

void *func_80610FE8(s32);
void func_8061421C();
void func_80614A64(Actor *);
ActorSub140 *actorSub140CreateFromModel(Actor *);
void collisionClearFlags(Actor *);
void actorUpdateSubnodeRotationAndMtx(Actor *);
void actorUpdateMovementFlags(Actor *);
void func_80675EE0(Actor *);
void actorInitDamage(Actor *);
void func_80677EC8(s32);
s32 func_80678014(s32);
s32 func_80678050(s32);
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
void func_80678BBC(Actor *);
void func_80678DD8(Actor *);
void func_80678E14(Actor *);
void func_80678F64(Actor *);
void func_80678F9C(Actor *, s32);
s32 func_80679010(Actor *, s32);
void actorRegisterGlobalCallback(ActorCallbackNode *);
void actorFreeCallbackList(Actor *);
void func_806791DC(Actor *, s32);
void func_806791EC(Actor *, s32);
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void actorQueueDelayedCallback(s32, s32, s32, u8, s32, void *, s32);
ActorCallbackNode *actorAllocCallbackNode(s32, s32, u8, s32, void *);
void func_806794EC(Actor *);
void func_8067A170(s32, u8);
void func_8067A69C(s32, Actor *, f32, f32, u8, u8);
void func_8067A70C(s32, Actor *, f32, f32, f32, u8, u8);
void func_8067A784(s32, Actor *, s16, f32, s16);
void func_8067A7EC(s32, Actor *, f32, f32, f32, s32, u8);
void func_8067A99C(s32, Actor *, s32);
void func_8067A9F0(s32, Actor *, f32, f32, f32);
void func_8067AA58(s32, Actor *, f32, f32);
void func_8067AAB8(s32, Actor *, s16, f32, s16);
void func_8067ABC0(s32, Actor *, u8, s16, s16, f32, f32, f32);
void func_8067AC38(void);
void func_8067ACB4(Actor *);
u16 func_8067ACC0(u16);
void actorTableClear(void);
s32 actorTableContains();
s32 actorTableBinarySearch();
void func_8067B100(Actor *);
void func_8067B2B0(s32);
void func_8067B2B8(s32);
s32 func_8067B2C0(s32);
s32 func_8067B3F4(s32);
s32 func_8067B42C(s32);
void func_80689418(void);
void actorListRemoveByActor(void);
void playerStateDispatchQueuedCallback(void);
void faultSetMessage(s32, s32, s32, s32);
void heapFree(void *);

typedef struct R3B_StructFB630 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
    s32 unk8;
} R3B_StructFB630;

typedef struct R3B_StructFB7B0 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} R3B_StructFB7B0;

typedef struct R3B_Header {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} R3B_Header;

extern R3B_StructFB630 D_807FB630[32];
extern R3B_StructFB7B0 D_807FB7B0[32];
extern s16 D_807FBB30;
extern s16 D_807FBB32;
extern R3B_Header *D_807FBB50;
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

    D_807FBB50 = (R3B_Header *)assetLoad(0xD, 0, 1, 1);
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

typedef struct R2ASpawnInfo {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    s32 unk1C;
} R2ASpawnInfo;
void actorScriptStart(Actor *, s32);
extern u8 D_8074D8D4[];
extern s32 (*D_8074DA30[])(s32 *);

s32 actorSpawnFromInfo(R2ASpawnInfo *arg0) {
    u8 temp;
    if (func_80678050((u16)arg0->unk0)) {
        temp = D_8074D8D4[arg0->unk0];
        if (D_8074DA30[temp](&arg0->unk4)) {
            D_807FBB44->unk7C = arg0->unkC;
            D_807FBB44->unk80 = arg0->unk10;
            D_807FBB44->unk84 = arg0->unk14;
            D_807FBB44->unk124 = arg0->unk1C;
            D_807FBB44->unkE6 = arg0->unk18;
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
    if (func_80678050((u16)arg0)) {
        temp = D_8074D8D4[arg0];
        if (D_8074DA30[temp](&arg1)) {
            return 1;
        }
    }
    return 0;
}

s32 func_80678014(s32 arg0) {
    if (func_80678050(arg0 & 0xFFFF) != 0) {
        func_8067B2C0(0);
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_80678050.s")

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

void func_806136B4(void);
void effectFreeByResource(Actor *);
void pathPlaybackStopForActor(Actor *);
void actorSub140Free(ActorSub140 *);
void proxPathRemoveActor(Actor *);
void func_8070DA74(Actor *);
void renderCallbacksDisableForActor(Actor *);
void actorTableRemove();
typedef struct R2EActor {
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
} R2EActor;

void actorFreeImmediate(Actor *arg0) {
    s16 i;
    Actor *temp;

    if (((R2EActor *)arg0)->unk0 != 0) {
        func_806136B4();
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
    if (((R2EActor *)arg0)->unk118 != NULL) {
        heapFree(((R2EActor *)arg0)->unk118);
    }
    if (((R2EActor *)arg0)->unk148 != NULL) {
        heapFree(((R2EActor *)arg0)->unk148);
    }
    if (((R2EActor *)arg0)->unk14C != NULL) {
        heapFree(((R2EActor *)arg0)->unk14C);
    }
    func_8062D26C(arg0);
    if (arg0->unk58 != 0x12B) {
        func_8070DA74(arg0);
    }
    renderCallbacksDisableForActor(arg0);
    actorTableRemove(arg0);
    heapFree(arg0);
}

void func_806787CC(void) {
    func_80689418();
}

static void func_806787EC(void) {}
static void func_806787F4(void) {}
static void func_806787FC(void) {}
static void func_80678804(void) {}
static void func_8067880C(void) {}
static void func_80678814(void) {}
static void func_8067881C(void) {}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_80678824.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_8067889C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_806789E4.s")

void func_80678B04(void) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (!(actor->unk60 & 0x08000000) && (actor->unk60 & 0x500) && (actor->unk60 & 0x4000)) {
            func_80614A64(actor);
        }
        actor->unk60 &= ~0x100;
    }
}

void func_80678BBC(Actor *arg0) {
    collisionClearFlags(arg0);
    if (arg0->unk5C & 1) {
        func_8067B100(arg0);
    }
    arg0->unk88 = arg0->unk7C;
    arg0->unk8C = arg0->unk80;
    arg0->unk90 = arg0->unk84;
    arg0->unkBC = arg0->unkB8;
    D_807F94B4 = 0;
    if (arg0->unk140 != NULL) {
        arg0->unk140->unk68 = 0;
    }
    func_80678F64(arg0);
    if (arg0 == D_807FBB48) {
        func_80675EE0(arg0);
    } else {
        actorInitDamage(arg0);
    }
    func_806794EC(arg0);
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

typedef struct R3B_Actor {
    u8 pad[0x156];
    u8 unk156;
} R3B_Actor;

void actorUpdatePositionAndSub140(Actor *);
void func_80678E6C(Actor *);
void actorUpdateModelMatrices(Actor *);
void func_806790F4(s32);
void func_8067A1DC(Actor *);
void actorUpdateEffects(Actor *);
void animListUpdate(Actor *);

void func_80678CC8(Actor *actor) {
    if ((void *)func_8067B3F4 == (void *)D_8074DA30[D_8074D8D4[actor->unk58]]) {
        guTranslateF((void *)((u8 *)actor + 0xC), actor->unk7C, actor->unk80, actor->unk84);
    }
    actorUpdatePositionAndSub140(actor);
    func_80678E6C(actor);
    if (!(actor->unk60 & 0x08000000)) {
        actor->unk60 &= ~0x200;
        if (actor->unk4 != NULL) {
            func_8061421C(actor);
            if (((actor->unk60 & 0x500) || ((R3B_Actor *)actor)->unk156 != 0) && !(actor->unk60 & 0x4000)) {
                func_80614A64(actor);
            }
        }
    }
    func_80678E14(actor);
    actorUpdateModelMatrices(actor);
    func_806790F4(0);
    func_8067A1DC(actor);
    actorFreeCallbackList(actor);
    actorUpdateEffects(actor);
    animListUpdate(actor);
    actor->unk60 |= 0x10;
}

void func_80678DD8(Actor *actor) {
    func_8061421C();
    if (actor->unk60 & 0x500) {
        func_80614A64(actor);
    }
}

void func_80678E14(Actor *actor) {
    f32 temp_fv0 = actor->unk80;

    if (actor->unk8C < temp_fv0) {
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
extern u8 D_807FC929;

void func_80678E6C(Actor *actor) {
    u8 sp27;

    if ((actor->unk144 & 4) && (D_807FBE08 == 0)) {
        if (actor->unk60 & 0x10000) {
            actor->unkFC = 0;
            actor->unkFD = 0;
        }
        actor->unkFC |= actorClearTargetAngle(actor, &actor->unkF4, &actor->unkF6, &sp27);
        sp27 |= D_807FBC55;
        if (sp27 != 0) {
            if (!(actor->unk6A & 0x10)) {
                actor->unk6A |= 0x10;
                if (actor == D_807FBB48) {
                    playerStateQueueCallback(4, 0, D_807FC929);
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

void func_80678F64(Actor *actor) {
    if (actor->unk114 != NULL) {
        heapFree(actor->unk114);
        actor->unk114 = NULL;
    }
}

void func_80678F9C(Actor *actor, s32 item) {
    if (actor->unk114 == NULL) {
        actor->unk114 = func_80610FE8(sizeof(ActorList));
        actor->unk114->count = 0;
    }
    if (actor->unk114->count != 4) {
        actor->unk114->items[actor->unk114->count] = item;
        actor->unk114->count++;
    }
}

s32 func_80679010(Actor *actor, s32 item) {
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_806790F4.s")

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

void func_806791DC(Actor *actor, s32 mask) {
    actor->unk138 |= mask;
}

void func_806791EC(Actor *actor, s32 mask) {
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_80679334.s")

ActorCallbackNode *actorAllocCallbackNode(s32 arg0, s32 arg1, u8 arg2, s32 arg3, void *arg4) {
    ActorCallbackNode *node = func_80610FE8(sizeof(ActorCallbackNode));

    node->callback = (void *)arg1;
    node->unk4 = arg2;
    node->unk8 = arg0;
    node->unkC = arg3;
    node->unk10 = arg4;
    node->next = NULL;
    return node;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_806794EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_80679DC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_8067A09C.s")

void func_8067A170(s32 arg0, u8 arg1) {
    s32 i;

    for (i = 0; i < D_807FBB70.unk201; i++) {
        if ((D_807FBB70.unk244[i] == arg1) && (D_807FBB70.unk204[i] == arg0)) {
            D_807FBB70.unk244[i] = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_8067A1DC.s")

void func_8067A69C(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    ActorPayloadA69C *temp = func_80610FE8(sizeof(ActorPayloadA69C));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unk9 = arg5;
    actorAppendCallback(arg1, arg0, 0x10, 0, 1, temp);
}

void func_8067A70C(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, u8 arg6) {
    ActorPayloadA70C *temp = func_80610FE8(sizeof(ActorPayloadA70C));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unkC = arg5;
    temp->unkD = arg6;
    actorAppendCallback(arg1, arg0, 0x20, 0, 1, temp);
}

void func_8067A784(s32 arg0, Actor *arg1, s16 arg2, f32 arg3, s16 arg4) {
    ActorPayloadAAB8 *temp = func_80610FE8(sizeof(ActorPayloadAAB8));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    actorAppendCallback(arg1, arg0, 0x4000, 0, 1, temp);
}

void func_8067A7EC(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, u8 arg6) {
    ActorPayloadA7EC *temp = func_80610FE8(sizeof(ActorPayloadA7EC));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unkC = arg5;
    temp->unk10 = arg6;
    actorAppendCallback(arg1, arg0, 0x1, 0, 1, temp);
}

typedef struct R2DActorPayloadA864 {
    s16 unk0;
    s16 unk2;
    u8 unk4[0xC];
    u8 unk10[0x24];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} R2DActorPayloadA864;

void func_8067A864(s32 arg0, Actor *arg1, s16 arg2, s16 arg3, void *arg4, void *arg5, s32 arg6, s32 arg7, s32 arg8) {
    R2DActorPayloadA864 *temp = func_80610FE8(sizeof(R2DActorPayloadA864));
    temp->unk0 = arg2;
    temp->unk2 = arg3;
    memcpy(temp->unk4, arg4, 0xC);
    memcpy(temp->unk10, arg5, 0x24);
    temp->unk34 = arg6;
    temp->unk38 = arg7;
    temp->unk3C = arg8;
    actorAppendCallback(arg1, arg0, 0x10000, 0, 1, temp);
}

typedef struct R2DActorPayloadA908 {
    u8 unk0[0xC];
    u8 unkC[0x24];
    s32 unk30;
    s32 unk34;
    s32 unk38;
} R2DActorPayloadA908;

void func_8067A908(s32 arg0, Actor *arg1, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6) {
    R2DActorPayloadA908 *temp = func_80610FE8(sizeof(R2DActorPayloadA908));
    memcpy(temp, arg2, 0xC);
    memcpy((u8 *)temp + 0xC, arg3, 0x24);
    temp->unk30 = arg4;
    temp->unk34 = arg5;
    temp->unk38 = arg6;
    actorAppendCallback(arg1, arg0, 0x20000, 0, 1, temp);
}

void func_8067A99C(s32 arg0, Actor *arg1, s32 arg2) {
    s32 *temp = func_80610FE8(sizeof(s32));
    *temp = arg2;
    actorAppendCallback(arg1, arg0, 0x40000, 0, 1, temp);
}

void func_8067A9F0(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 *temp = func_80610FE8(3 * sizeof(f32));
    temp[0] = arg2;
    temp[1] = arg3;
    temp[2] = arg4;
    actorAppendCallback(arg1, arg0, 0x100000, 0, 1, temp);
}

void func_8067AA58(s32 arg0, Actor *arg1, f32 arg2, f32 arg3) {
    f32 *temp = func_80610FE8(2 * sizeof(f32));
    temp[0] = arg2;
    temp[1] = arg3;
    actorAppendCallback(arg1, arg0, 0x200000, 0, 1, temp);
}

void func_8067AAB8(s32 arg0, Actor *arg1, s16 arg2, f32 arg3, s16 arg4) {
    ActorPayloadAAB8 *temp = func_80610FE8(sizeof(ActorPayloadAAB8));
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unk0 = arg2;
    actorAppendCallback(arg1, arg0, 0x400, 0, 1, temp);
}

void func_8067AB20(s32 arg0, Actor *arg1, s32 arg2, u8 arg3, void *arg4, u8 arg5) {
    void *temp = func_80610FE8(8);
    memcpy(temp, arg4, 8);
    if (!arg5) {
        actorAppendCallback(arg1, arg0, arg2, arg3, 1, temp);
    } else {
        actorQueueDelayedCallback((s32)arg1, arg0, arg2, arg3, 1, temp, 1);
    }
}

void func_8067ABC0(s32 arg0, Actor *arg1, u8 arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6, f32 arg7) {
    ActorPayloadABC0 *temp = func_80610FE8(sizeof(ActorPayloadABC0));
    temp->unk0 = arg5;
    temp->unk4 = arg6;
    temp->unk8 = arg7;
    temp->unkC = arg3;
    temp->unkE = arg4;
    actorAppendCallback(arg1, arg0, 0x800000, arg2, 1, temp);
}

void func_8067AC38(void) {
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

s32 func_8067ACDC(arg0, arg1, arg2)
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

typedef struct R2CEntry2F0 {
    u8 unk0;
    char pad1[3];
    s32 unk4;
    char pad8[0x2F0 - 8];
} R2CEntry2F0;
extern R2CEntry2F0 *D_807FC924;
extern u8 D_807FC928;

void actorTableSort(void);

Actor *actorFindByType(u16 arg0) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (actor->unk58 == arg0) {
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
        faultSetMessage(0x13, arg0->unk58, 0, 0);
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_8067B100.s")

u8 func_8067B1E0(s32 arg0) {
    s32 i;
    for (i = 0; i < D_807FC928; i++) {
        if (D_807FC924[i].unk0 != 0 && arg0 == D_807FC924[i].unk4) {
            return (u8)i;
        }
    }
    return 0;
}

void func_8067B238(Actor *arg0, Actor *arg1, f32 arg2) {
    arg0->unk7C = arg1->unk7C;
    arg0->unk80 = arg1->unk80;
    arg0->unk84 = arg1->unk84;
    arg0->unkE6 = arg1->unkE6;
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

s32 func_806134B4(Actor *, u16, void *);

typedef struct R2EActorSub140 {
    u8 pad0[0xC];
    s32 unkC;
} R2EActorSub140;

typedef struct R2EArgB2DC {
    u8 pad0[2];
    u16 unk2;
} R2EArgB2DC;

s32 func_8067B2DC(R2EArgB2DC *arg0) {
    if (func_806134B4(D_807FBB44, arg0->unk2, arg0) != 0) {
        D_807FBB44->unk140 = actorSub140CreateFromModel(D_807FBB44);
        D_807FBB44->unk15E = (u32)(((f64)((R2EActorSub140 *)D_807FBB44->unk140)->unkC * 0.15) * 0.5);
        return 1;
    }
    return 0;
}

s32 func_8067B3F4(s32 arg0) {
    D_807FBB44->unk140 = actorSub140CreateFromModel(D_807FBB44);
    return 1;
}

s32 func_8067B42C(s32 arg0) {
    D_807FBB44->unk60 |= 0x2000;
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
