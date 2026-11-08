#include "common.h"
#include "actor.h"

typedef struct ActorListRecord {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ char unk10[0x20];
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ char pad36[2];
} ActorListRecord;

typedef struct ActorListEntry4 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
} ActorListEntry4;

typedef struct ActorListSub20 {
    s32 words[8];
} ActorListSub20;

typedef struct ActorListNode {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0x20];
    /* 0x44 */ Actor *unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ char unk4D[3];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ struct ActorListNode *prev;
    /* 0x68 */ struct ActorListNode *next;
} ActorListNode;

extern s32 gCurrentMap;
extern ActorListSub20 D_807500B4;
extern ActorListSub20 D_807500D4;
extern Actor *D_807FBB40;
extern ActorListNode *D_807FC400;
extern ActorListEntry4 *D_807FC5C4;
extern u8 D_807FC5C8;
extern s16 D_807FC5D0[16];
extern s16 D_807FC5F0[16];
extern u8 D_807FC610;
extern u8 D_807FC611;

void *memcpy(void *, const void *, size_t);
void heapFree(void *);
void actorDespawn(Actor *);
s16 mapChunkFindByPosition(f32, f32, f32, s32);
s32 mapChunkIsVisible(s32, void *);
void func_8066E6C8(Actor *, s32, s32);
void func_8067AB20(s32, Actor *, s32, u8, void *, u8);
s32 actorListGetTypeIdCount(u16);
s16 actorListAllocId(void);
ActorListNode *actorListSpawnNodeInternal(s16, f32, f32, f32, s16, f32, void *, u8, s32, s16);
void actorListRemoveNodeInternal();
f32 playerGetMinSquaredDist3D(f32, f32, f32);
s32 mapIsBossArena(void);
u8 actorListSpawnIfNear(ActorListNode *);
u8 actorListDespawnIfFar(ActorListNode *);
void actorListClearForcedIds(void);

extern s16 D_8076A0AA;
extern u8 D_8076A0AB;
extern s32 D_807F6010;
extern s32 gMapChunkCount;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
    void *unk1C;
    void *unk20;
    u8 pad24[0xC0 - 0x24];
} ModelAssetEntry160;
extern ModelAssetEntry160 D_8076A160[];

typedef struct {
    void *ptr;
    u8 pad4[0xC0 - 4];
} ModelAssetEntry178;
extern ModelAssetEntry178 D_8076A178[];

s32 func_80600080(s32);
u16 modelTypeCountBeforeMap(u8);
void modelAssetGetSubtables(s32, s32 *, s32 **);
void modelSlotsLoadMap(s32, s32, u8, u16, s32);
void csTimerQueueFire(s16);
void actorListSpawnFromRecords(s32 *);
void modelSlotsApplyRecords(void *, void *);
void lightSetColor(f32, f32, f32, s16);
s32 func_805FF030(u8, s32);
void actorListBuildLookupTable(void);
s32 func_806C7B34(void);

void actorMapModelsSetup(s32 modelAsset, u8 loadMode, u8 skipExtra) {
    s32 subtableCount;
    s32 *records;
    s32 mapIndex;
    s32 pad;
    u16 preMapModelCount;
    s32 flag;

    flag = 0;
    actorListBuildLookupTable();
    mapIndex = func_80600080(gCurrentMap);
    if (mapIndex == -1) {
        switch (loadMode) {
        case 0:
            D_807F6010 = modelAsset;
            preMapModelCount = modelTypeCountBeforeMap(D_8076A0AB);
            flag = 1;
            break;
        case 1:
            modelAsset = D_807F6010;
            break;
        }
    } else {
        D_807F6010 = modelAsset;
        modelAsset = (s32)D_8076A178[mapIndex].ptr;
    }
    modelAssetGetSubtables(modelAsset, &subtableCount, &records);
    if (skipExtra != 0) {
        modelAsset = 0;
    } else {
        modelAsset = func_806C7B34();
    }
    modelSlotsLoadMap(subtableCount, modelAsset, (u8)flag, preMapModelCount, func_805FF030(D_8076A0AB, 1));
    csTimerQueueFire(D_8076A0AA);
    actorListSpawnFromRecords(records);
    if (mapIndex != -1) {
        if (D_8076A160[mapIndex].unk20 != NULL) {
            modelSlotsApplyRecords(D_8076A160[mapIndex].unk20, D_8076A160[mapIndex].unk1C);
        }
        if (gMapChunkCount > 0) {
            flag = 0, modelAsset = (s32)&D_8076A160[mapIndex]; do { lightSetColor( // LAYOUT: init + call on one line steers as1 order of the hoisted ldc1 vs addu
                (f32)((f64)(u32)((u8 *)modelAsset)[0x24] / 255.0),
                (f32)((f64)(u32)((u8 *)modelAsset)[0x25] / 255.0),
                (f32)((f64)(u32)((u8 *)modelAsset)[0x26] / 255.0),
                flag);
                flag++;
                modelAsset += 3;
            } while (flag < gMapChunkCount);
        }
    }
}

extern u8 D_807500B0;
extern s16 D_807FC408[];

void *assetLoad(s32, s32, s32, s32);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);

typedef struct ActorListContainer {
    s32 count;
    ActorListRecord items[1];
} ActorListContainer;

void actorListInitOffsets(void) {
    s32 j;
    s32 count;
    s32 total;
    void *subtableA;
    ActorListContainer *container;
    ActorListRecord *items;
    s32 i;
    s32 ret;
    void *asset;

    total = 0;
    if (D_807500B0 == 0) {
        D_807500B0 = 1;
        for (i = 0; i < 0xDD; i++) {
            D_807FC408[i] = total;
            asset = assetLoad(9, i, 1, 1);
            if (asset != NULL) {
                modelAssetGetSubtables((s32)asset, (s32 *)&subtableA, (s32 **)&container);
                count = container->count;
                items = container->items;
                for (j = 0; j < count; j++) {
                    ret = actorListGetTypeIdCount(items[j].unk32 + 0x10);
                    total = (u16)(total + ret);
                }
                assetSetImmediateFree();
                assetFreeBuffer(asset, 0x168, 0x34);
            }
        }
    }
}

void *heapAlloc(s32);

void actorListBuildLookupTable(void) {
    s32 count;
    s32 i;
    s32 ret;
    s32 pad;
    s32 sz;
    ActorListRecord *items;
    void *asset;
    void *subtableA;
    ActorListContainer *container;
    ActorListRecord *item;
    s32 offset;

    asset = assetLoad(9, gCurrentMap, 1, 1);
    D_807FC5C8 = 0;
    if (asset != NULL) {
        modelAssetGetSubtables((s32)asset, (s32 *)&subtableA, (s32 **)&container);
        count = container->count;
        items = container->items;
    } else {
        count = 0;
    }
    if (count > 0) {
        i = 0;
        item = items;
        do {
            if (actorListGetTypeIdCount(item->unk32 + 0x10) != 0) {
                D_807FC5C8++;
            }
            i++;
            item++;
        } while (i != count);
    }
    if (D_807FC5C8) {
        sz = D_807FC5C8 * sizeof(ActorListEntry4);
        i = 0;
        D_807FC5C4 = heapAlloc(sz);
    } else {
        D_807FC5C4 = NULL;
        return;
    }
    D_807FC5C8 = 0;
    offset = 0;
    if (count > 0) {
        item = items;
        do {
            ret = actorListGetTypeIdCount(item->unk32 + 0x10);
            if (ret != 0) {
                D_807FC5C4[D_807FC5C8].unk0 = item->unk34;
                D_807FC5C4[D_807FC5C8].unk2 = ((u16 *)D_807FC408)[gCurrentMap] + offset + 0x26B;
                offset += ret;
                D_807FC5C8++;
            }
            i++;
            item++;
        } while (i != count);
    }
    assetSetImmediateFree();
    assetFreeBuffer(asset, 0x1AA, 0x34);
}

s32 actorListLookupEntry(u16 targetId) {
    s32 i;

    for (i = 0; i < D_807FC5C8; i++) {
        if (targetId == D_807FC5C4[i].unk0) {
            return D_807FC5C4[i].unk2;
        }
    }
    return -1;
}

s32 actorListGetTypeIdCount(u16 typeId) {
    switch (typeId) {
    case 0x5B:
    case 0x6F:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x8B:
        return 1;
    default:
        return 0;
    }
}

void actorSetCustomFloat(Actor *actor, s16 index, f32 val) {
    if (index < 8) {
        ((f32 *)actor->unk124)[index] = val;
    }
}

void actorSetCustomInt(Actor *actor, s16 index, s32 val) {
    if (index < 8) {
        ((s32 *)actor->unk124)[index] = val;
    }
}

void actorListSetCustomFloat(s16 mapIndex, s16 targetId, s16 index, f32 val) {
    s32 pad[2];
    void *subtableA;
    void *container;
    s32 modelIndex;
    s32 count;
    u8 found;
    ActorListRecord *item;

    found = 0;
    modelIndex = func_80600080(mapIndex);
    if (modelIndex != -1) {
        modelAssetGetSubtables((s32)D_8076A178[modelIndex].ptr, (s32 *)&subtableA, (s32 **)&container);
        count = *(s32 *)container;
        item = container = (ActorListRecord *)((s32 *)container + 1);
        if (count != 0) {
            do {
                if (item->unk34 == targetId) {
                    ((f32 *)item->unk10)[index] = val;
                    found = 1;
                }
                count--;
                item++;
            } while (count != 0 && !found);
        }
    }
}

s16 actorListAllocId(void) {
    s16 id;
    s32 found;
    ActorListNode *node;

    id = 0;
    do {
        found = 0;
        node = D_807FC400;
        if (node != NULL) {
            do {
                if (node->unk5A == id) {
                    found = 1;
                }
                node = node->next;
            } while (node != NULL && !found);
        }
        if (found) {
            id++;
        }
    } while (found);

    return id;
}

s16 actorListFindIdByActor(Actor *actor) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk44 == actor) {
            return node->unk5A;
        }
    }
    return 0;
}

Actor *actorListFindActorById(s16 targetId) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk5A == targetId) {
            return node->unk44;
        }
    }
}

void actorListSetPosById(s16 targetId, f32 posX, f32 posY, f32 posZ) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk5A == targetId) {
            node->unk04 = posX;
            node->unk08 = posY;
            node->unk0C = posZ;
            node->unk10 = posX;
            node->unk14 = posY;
            node->unk18 = posZ;
            node->unk4A = mapChunkFindByPosition(posX, posY, posZ, 0);
            return;
        }
    }
}

void actorListSetPosByActor(Actor *actor, f32 posX, f32 posY, f32 posZ) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk44 == actor) {
            node->unk04 = posX;
            node->unk08 = posY;
            node->unk0C = posZ;
            return;
        }
    }
}

void actorListSpawnFromRecords(s32 *records) {
    ActorListRecord *item;
    s32 i;
    void *recordExtData;
    s32 count;

    D_807FC400 = NULL;
    if (records != NULL) {
        count = *records++;
        item = (ActorListRecord *)records;
        for (i = 0, recordExtData = (char *)item + 0x10; i < count; i++, item++, recordExtData = (char *)recordExtData + 0x38) {
            actorListSpawnNodeInternal(item->unk32, item->unk00, item->unk04, item->unk08, item->unk30, item->unk0C, recordExtData, 0, 0, item->unk34);
        }
        actorListClearForcedIds();
    }
}

void actorListSpawnNodePersistent(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale) {
    ActorListSub20 subData;

    subData = D_807500B4;
    actorListSpawnNodeInternal(actorType, posX, posY, posZ, (s32)yaw, scale, &subData, 0, 0, actorListAllocId());
}

void actorListSpawnNodeEntryDefault(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale, s32 extraParam) {
    ActorListSub20 subData;

    subData = D_807500D4;
    actorListSpawnNodeInternal((s16)(actorType - 0x10), posX, posY, posZ, (s32)yaw, scale, &subData, 1, extraParam, actorListAllocId());
}

void actorListSpawnNodeEntry(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale, s32 extraParam, s32 customData) {
    actorListSpawnNodeInternal((s16)(actorType - 0x10), posX, posY, posZ, (s32)yaw, scale, (void *)customData, 1, extraParam, actorListAllocId());
}

typedef struct ActorListSpawnEntry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ char unk4[4];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ char unkA[2];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ char unk14[0x1C];
} ActorListSpawnEntry;
extern ActorListSpawnEntry D_8074E8B0[];

ActorListNode *actorListSpawnNodeInternal(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale, void *customData, u8 spawnMode, s32 extraParam, s16 targetId) {
    ActorListNode *node;
    s32 i;
    s32 found;
    s16 n;
    s16 key;

    n = 0x80; // FAKE: loop bound in a local keeps IDO's entry-search loop in registers (frame 0x30)
    i = 0;
    found = 0;
    key = actorType + 0x10;
    while (!found && i < n) {
        if (key == D_8074E8B0[i].unk0) {
            found = 1;
        } else {
            i++;
        }
    }

    node = heapAlloc(sizeof(ActorListNode));
    node->unk00 = actorType;
    node->unk5A = targetId;
    node->unk0C = posZ;
    node->unk18 = posZ;
    node->unk04 = posX;
    node->unk10 = posX;
    node->unk08 = posY;
    node->unk14 = posY;
    node->unk1C = yaw;
    node->unk20 = scale;
    node->unk44 = 0;
    node->prev = NULL;
    node->unk48 = 0;
    node->unk5C = D_8074E8B0[i].unkC;
    node->unk60 = D_8074E8B0[i].unk10;
    node->unk58 = D_8074E8B0[i].unk2;
    node->unk4A = mapChunkFindByPosition(posX, posY, posZ, 0);
    node->unk4C = spawnMode;
    node->unk50 = extraParam;
    node->unk54 = (f32)D_8074E8B0[i].unk8 * (f32)D_8074E8B0[i].unk8;

    for (i = 0; i < 8; i++) {
        ((f32 *)node->unk24)[i] = ((f32 *)customData)[i];
    }

    node->next = D_807FC400;
    if (D_807FC400 != NULL) {
        D_807FC400->prev = node;
    }
    D_807FC400 = node;

    return node;
}

typedef struct ActorListNodeInternal {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0x20];
    /* 0x44 */ Actor *unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ char unk4D[3];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s32 (*unk5C)(struct ActorListNodeInternal *);
    /* 0x60 */ s32 (*unk60)(struct ActorListNodeInternal *);
    /* 0x64 */ struct ActorListNodeInternal *prev;
    /* 0x68 */ struct ActorListNodeInternal *next;
} ActorListNodeInternal;

typedef struct ActorListSpawnInfo {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    s32 unk1C;
} ActorListSpawnInfo;



void actorDeregisterActive(Actor *);
void actorRegisterActive(Actor *);
s32 actorSpawnFromInfo(ActorListSpawnInfo *);
s32 controllerAnimStateLoadAsset();
void controllerAnimFreeSub(Actor *, u8);
extern Actor *D_807FBB44;

void actorListUpdateSpawns(void) {
    s32 pad;
    ActorListSpawnInfo spawnInfo;
    Actor *actor;
    ActorListNodeInternal *node;
    s32 n;
    u8 found;
    s32 i;
    s16 target;

    n = 0x80; // FAKE: loop bound in a local keeps IDO's entry-search loop (and 0x80) in registers
    node = (ActorListNodeInternal *)D_807FC400;
    if (node != NULL) {
        do {
            if (node->unk48 != 0) {
                if (node->unk60(node) != 0) {
                    actor = node->unk44;
                    if (!(actor->unk60 & 0x200000)) {
                        actorDeregisterActive(actor);
                        actor = node->unk44;
                        node->unk48 = 0;
                        node->unk10 = actor->x;
                        node->unk14 = actor->y;
                        node->unk18 = actor->z;
                        node->unk4A = *(s16 *)&actor->unk12C[0];
                        controllerAnimFreeSub(actor, 0);
                        controllerAnimFreeSub(node->unk44, 1);
                        controllerAnimFreeSub(node->unk44, 2);
                    }
                }
            } else if (node->unk5C(node) != 0) {
                actor = node->unk44;
                i = 0;
                found = 0;
                if (actor == NULL) {
                    target = node->unk00 + 0x10;
                    while (!found && i < n) {
                        if (target == D_8074E8B0[i].unk0) {
                            found = 1;
                        } else {
                            i++;
                        }
                    }

                    spawnInfo.unk0 = target;
                    spawnInfo.unk8 = *(s32 *)&D_8074E8B0[i].unk4;
                    spawnInfo.unk4 = D_8074E8B0[i].unk2;
                    spawnInfo.unkC = node->unk04;
                    spawnInfo.unk10 = node->unk08;
                    spawnInfo.unk14 = node->unk0C;
                    spawnInfo.unk18 = node->unk1C;
                    spawnInfo.unk1A = 0;
                    spawnInfo.unk1C = (s32)node->unk24;
                    if (actorSpawnFromInfo(&spawnInfo) != 0) {
                        node->unk44 = D_807FBB44;
                        node->unk48 = 1;
                        D_807FBB44->unk11C = node->unk50;
                        if (D_807FBB44->unk4 != NULL) {
                            D_807FBB44->unk4->unk34 = (f32)(node->unk20 * 0.15);
                            D_807FBB44->unk4->unk38 = (f32)(node->unk20 * 0.15);
                            D_807FBB44->unk4->unk3C = (f32)(node->unk20 * 0.15);
                        }
                    }
                } else if (node->unk48 == 0) {
                    if (node->unk58 != 0) {
                        *(s32 *)node->unk44 = controllerAnimStateLoadAsset(actor, node->unk58, 0);
                        actor = node->unk44;
                    }
                    actorRegisterActive(actor);
                    node->unk48 = 1;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
    actorListClearForcedIds();
}

void actorListRemoveAndDespawn(s32 node) {
    actorListRemoveNodeInternal(node, 1);
}

void actorListRemoveNode(s32 node) {
    actorListRemoveNodeInternal(node, 0);
}

void actorListRemoveNodeInternal(targetNode, despawnActor)
ActorListNode *targetNode;
u8 despawnActor;
{
    ActorListNode *node;
    ActorListNode *prev;
    s32 found;

    found = 0;
    node = D_807FC400;
    prev = NULL;
    if (node != NULL) {
        do {
            if (node == targetNode) {
                found = 1;
                if (despawnActor != 0 && node->unk44 != NULL) {
                    actorDespawn(node->unk44);
                }
                if (prev != NULL) {
                    prev->next = node->next;
                } else {
                    D_807FC400 = node->next;
                }
                if (node->next != NULL) {
                    node->next->prev = prev;
                }
                heapFree(node);
            } else {
                prev = node;
                node = node->next;
            }
        } while (found == 0 && node != NULL);
    }
}

void actorListRemoveByActor(Actor *actor) {
    ActorListNode *node;
    ActorListNode *prev;
    s32 found;

    found = 0;
    node = D_807FC400;
    prev = NULL;
    if (node != NULL) {
        do {
            if (actor == node->unk44) {
                found = 1;
                if (prev != NULL) {
                    prev->next = node->next;
                } else {
                    D_807FC400 = node->next;
                }
                if (node->next != NULL) {
                    node->next->prev = prev;
                }
                heapFree(node);
            } else {
                prev = node;
                node = node->next;
            }
        } while (found == 0 && node != NULL);
    }
}

void actorListFreeAll(void) {
    ActorListNode *node;
    ActorListNode *next;

    node = D_807FC400;
    if (node != NULL) {
        do {
            next = node->next;
            heapFree(node);
            node = next;
        } while (node != NULL);
    }
    D_807FC400 = NULL;
}

s32 actorListGetSerializedSize(void) {
    ActorListNode *node;
    s32 count;

    node = D_807FC400;
    count = 0;
    if (node != NULL) {
        do {
            if (node->unk4C == 0 || (node->unk44 != NULL && (node->unk44->unk64 & 0x400))) {
                count++;
            }
            node = node->next;
        } while (node != NULL);
    }
    return (count * 0x38) + 4;
}

void actorListSerialize(s32 *outBuf) {
    ActorListNode *node;
    u8 *dst;
    ActorListRecord item;
    s32 count;
    node = D_807FC400;
    count = 0;
    if (node != NULL) {
        do {
            if (node->unk4C == 0 || (node->unk44 != NULL && (node->unk44->unk64 & 0x400))) {
                count++;
            }
            node = node->next;
        } while (node != NULL);
    }
    *outBuf = count;
    node = D_807FC400;
    dst = (u8 *)(outBuf + 1);
    if (node != NULL) {
        do {
            if (node->unk4C == 0 || (node->unk44 != NULL && (node->unk44->unk64 & 0x400))) {
                item.unk32 = node->unk00;
                item.unk0C = node->unk20;
                item.unk30 = node->unk1C;
                item.unk00 = node->unk04;
                item.unk04 = node->unk08;
                item.unk08 = node->unk0C;
                item.unk34 = node->unk5A;
                memcpy(item.unk10, node->unk24, 0x20);
                memcpy(dst, &item, sizeof(item));
                dst += sizeof(item);
            }
            node = node->next;
        } while (node != NULL);
    }
}

void actorListDispatchEvent(s16 targetId, void *eventData) {
    ActorListNode *node = D_807FC400;
    s32 found = 0;

    if (node != NULL) {
        do {
            if (targetId == node->unk5A) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (found) {
        if (node->unk44 != NULL) {
            func_8067AB20((s32)D_807FBB40, node->unk44, 0x1000000, 1, eventData, 0);
        }
    }
}

s32 actorListGetOrSetState(s16 targetId, u8 newState, u8 setFlag) {
    ActorListNode *node;
    s32 found = 0;

    node = D_807FC400;
    if (node != NULL) {
        do {
            if (targetId == node->unk5A) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (!found) {
        return 0;
    }
    if (node->unk44 == NULL) {
        return 0;
    }
    if (setFlag != 0) {
        node->unk44->state = newState;
    }
    return node->unk44->state;
}

s32 actorListIsIdActive(s16 targetId) {
    ActorListNode *node;
    s32 found = 0;

    node = D_807FC400;
    if (node != NULL) {
        do {
            if (targetId == node->unk5A) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (!found) {
        return 0;
    }
    if (node->unk48 != 0) {
        return 1;
    }
    return 0;
}

s32 actorListFindClosestTargetIndex(s32 *recordList, s16 *typeList, u8 typeCount, f32 posX, f32 posY, f32 posZ) {
    s32 total = *recordList;
    s32 bestIndex = -1;
    f32 minDistance = 9999999.0f;
    s32 i;
    s32 j;
    ActorListRecord *item;
    s32 *list;
    f32 dist;

    list = recordList; // FAKE: second pointer to the list moves the item/j colours (permuter find)
    for (i = 0; i < total; i++) {
        item = &((ActorListRecord *)(list + 1))[i];
        for (j = 0; j < typeCount; j++) {
            if (typeList[j] == (0, item->unk32 + 0x10U)) { // FAKE: 0x10U keeps IDO from rewriting the compare to x - 16 == y; the comma wrapper puts the typeList[j] operand first in bnel
                dist = ((item->unk08 - posZ) * (item->unk08 - posZ)) + (((item->unk00 - posX) * (item->unk00 - posX)) + ((item->unk04 - posY) * (item->unk04 - posY)));
                if (dist < minDistance) {
                    minDistance = dist;
                    bestIndex = item->unk34;
                }
            }
        }
    }
    return bestIndex;
}

typedef struct ActorListPlayerEntry {
    u8 unk0;
    char pad1[0x210 - 1];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0x2F0 - 0x21C];
} ActorListPlayerEntry;

extern ActorListPlayerEntry *gPlayerSlots;
extern u8 gPlayerCount;

f32 playerGetMinSquaredDist3D(f32 posX, f32 posY, f32 posZ) {
    f32 minDist = 100000000.0f;
    s32 i;

    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].unk0 != 0) {
            f32 dist = (posX - gPlayerSlots[i].unk210) * (posX - gPlayerSlots[i].unk210) + (posY - gPlayerSlots[i].unk214) * (posY - gPlayerSlots[i].unk214) + (posZ - gPlayerSlots[i].unk218) * (posZ - gPlayerSlots[i].unk218);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

s32 actorListSpawnAlways(s32 node) {
    return 1;
}

void func_80689EA4(ActorListNode *node) {
    if (mapIsBossArena()) {
        mapChunkIsVisible(node->unk4A, node);
    } else {
        actorListSpawnIfNear(node);
    }
}

u8 func_80689EE4(ActorListNode *node) {
    if (mapIsBossArena()) {
        return mapChunkIsVisible(*(s16 *)&node->unk44->unk12C, node) == 0;
    }
    return actorListDespawnIfFar(node);
}

s32 mapIsBossArena(void) {
    switch (gCurrentMap) {
        case 0x2A:
        case 0xA9:
        case 0xAA:
        case 0xAD:
        case 0xAE:
        case 0xAF:
        case 0xB2:
        case 0xC1:
        case 0xC2:
        case 0xC3:
            return 1;
        default:
            return 0;
    }
}

u8 actorListSpawnIfNear(ActorListNode *node) {
    s32 shouldSpawn = mapChunkIsVisible(node->unk4A, node) != 0;
    if (shouldSpawn != 0) {
        f32 dist = playerGetMinSquaredDist3D(node->unk10, node->unk14, node->unk18);
        shouldSpawn = 0;
        if (dist < node->unk54) {
            shouldSpawn = 1;
        }
    }
    return shouldSpawn;
}

u8 actorListDespawnIfFar(ActorListNode *node) {
    return (mapChunkIsVisible(*(s16 *)&node->unk44->unk12C, node) == 0 || !(playerGetMinSquaredDist3D(node->unk10, node->unk14, node->unk18) < node->unk54)) && (node->unk44->unk114 == NULL);
}

u8 actorListDespawnIfFarAndIdle(ActorListNode *node) {
    return (mapChunkIsVisible(*(s16 *)&node->unk44->unk12C, node) == 0 || !(playerGetMinSquaredDist3D(node->unk10, node->unk14, node->unk18) < node->unk54)) && (node->unk44->unk114 == NULL) && (node->unk44->state == 0);
}

s32 actorListDespawnNever(s32 node) {
    return 0;
}

u8 actorListIsPlayerInRadius(ActorListNode *node) {
    s32 isInRadius;
    f32 dist = playerGetMinSquaredDist3D(node->unk10, node->unk14, node->unk18);
    isInRadius = 0;
    if (dist < node->unk54) {
        isInRadius = 1;
    }
    return isInRadius;
}

u8 actorListIsPlayerOutsideRadius(ActorListNode *node) {
    return !(playerGetMinSquaredDist3D(node->unk44->x, node->unk44->y, node->unk44->z) < node->unk54);
}

void actorListClearForcedIds(void) {
    D_807FC610 = 0;
    D_807FC611 = 0;
}

void actorListForceSpawnId(s16 targetId) {
    if (D_807FC610 != 0x10) {
        D_807FC5D0[D_807FC610++] = targetId;
    }
}

void actorListForceDespawnId(s16 targetId) {
    if (D_807FC611 != 0x10) {
        D_807FC5F0[D_807FC611++] = targetId;
    }
}

s32 actorListSpawnIfForced(ActorListNode *node) {
    s32 i;
    for (i = 0; i < D_807FC610; i++) {
        if (node->unk5A == D_807FC5D0[i] && node->unk48 == 0) {
            return 1;
        }
    }
    return 0;
}

s32 actorListDespawnIfForced(ActorListNode *node) {
    s32 i;
    for (i = 0; i < D_807FC611; i++) {
        if (node->unk5A == D_807FC5F0[i] && node->unk48 != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8068A2FC(Actor *actor) {
    actor->unk128 = 0;
    actor->unk60 &= ~0x8000;
    actor->unk144 = 1;
    actor->unk138 = 0;
    actor->state = 0x63;
    func_8066E6C8(actor, 0, 0);
}
