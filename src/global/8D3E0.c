#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "map.h"
#include "proto/global/15050.h"
#include "proto/global/17B90.h"
#include "proto/global/36880.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7CA80.h"
#include "proto/global/8D3E0.h"
#include "proto/global/CC800.h"

typedef struct ActorListRecord {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ f32 customData[8];
    /* 0x30 */ s16 yaw;
    /* 0x32 */ s16 actorType;
    /* 0x34 */ s16 id;
    /* 0x36 */ char pad36[2];
} ActorListRecord;

typedef struct ActorListEntry4 {
    /* 0x0 */ u8 id;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 flagIndex;
} ActorListEntry4;

typedef struct ActorListSub20 {
    s32 words[8];
} ActorListSub20;

typedef struct ActorListNode {
    /* 0x00 */ s16 actorType;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ f32 spawnX;
    /* 0x08 */ f32 spawnY;
    /* 0x0C */ f32 spawnZ;
    /* 0x10 */ f32 x;
    /* 0x14 */ f32 y;
    /* 0x18 */ f32 z;
    /* 0x1C */ s16 yaw;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ f32 scale;
    /* 0x24 */ f32 customData[8];
    /* 0x44 */ Actor *actor;
    /* 0x48 */ u8 spawned;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ s16 chunkIndex;
    /* 0x4C */ u8 spawnMode;
    /* 0x4D */ char unk4D[3];
    /* 0x50 */ Actor *extraParam;
    /* 0x54 */ f32 radiusSq;
    /* 0x58 */ s16 animAssetId;
    /* 0x5A */ s16 id;
    /* 0x5C */ s32 (*shouldSpawn)(struct ActorListNode *);
    /* 0x60 */ s32 (*shouldDespawn)(struct ActorListNode *);
    /* 0x64 */ struct ActorListNode *prev;
    /* 0x68 */ struct ActorListNode *next;
} ActorListNode;

extern s32 gCurrentMap;
extern ActorListSub20 D_807500B4;
extern ActorListSub20 D_807500D4;
extern Actor *gCurrentActor;
extern ActorListNode *D_807FC400;
extern ActorListEntry4 *D_807FC5C4;
extern u8 D_807FC5C8;
extern s16 D_807FC5D0[16];
extern s16 D_807FC5F0[16];
extern u8 D_807FC610;
extern u8 D_807FC611;


extern s16 gCurrentLevelIndex;
extern u8 gCurrentWorldId;
extern s32 D_807F6010;
extern s32 gMapChunkCount;

extern Struct8076A160 D_8076A160[];


void actorMapModelsSetup(s32 modelAsset, u8 loadMode, u8 skipExtra) {
    u8 *subtables;
    u8 *records;
    s32 mapIndex;
    s32 pad;
    u16 preMapModelCount;
    s32 flag;

    flag = 0;
    actorListBuildLookupTable();
    mapIndex = mapFindSlotIndex(gCurrentMap);
    if (mapIndex == -1) {
        switch (loadMode) {
        case 0:
            D_807F6010 = modelAsset;
            preMapModelCount = modelTypeCountBeforeMap(gCurrentWorldId);
            flag = 1;
            break;
        case 1:
            modelAsset = D_807F6010;
            break;
        }
    } else {
        D_807F6010 = modelAsset;
        modelAsset = (s32)D_8076A160[mapIndex].modelData;
    }
    modelAssetGetSubtables(modelAsset, &subtables, &records);
    if (skipExtra != 0) {
        modelAsset = 0;
    } else {
        modelAsset = playerGetModelAssetId();
    }
    modelSlotsLoadMap(subtables, modelAsset, flag, preMapModelCount, mapGetHubWorldIndex(gCurrentWorldId, 1));
    csTimerQueueFire(gCurrentLevelIndex);
    actorListSpawnFromRecords(records);
    if (mapIndex != -1) {
        if (D_8076A160[mapIndex].records != NULL) {
            modelSlotsApplyRecords(D_8076A160[mapIndex].records, D_8076A160[mapIndex].recordSize);
        }
        if (gMapChunkCount > 0) {
            flag = 0; modelAsset = (s32)&D_8076A160[mapIndex]; do { lightSetColor( // LAYOUT: init + call on one line steers as1 order of the hoisted ldc1 vs addu
                (u32)((u8 *)modelAsset)[0x24] / 255.0,
                (u32)((u8 *)modelAsset)[0x25] / 255.0,
                (u32)((u8 *)modelAsset)[0x26] / 255.0,
                flag);
                flag++;
                modelAsset += 3;
            } while (flag < gMapChunkCount);
        }
    }
}

extern u8 D_807500B0;
extern s16 D_807FC408[];


typedef struct ActorListContainer {
    s32 count;
    ActorListRecord items[1];
} ActorListContainer;

void actorListInitOffsets(void) {
    s32 j;
    s32 count;
    s32 total;
    u8 *subtableA;
    u8 *subtables;
    ActorListContainer *container;
    ActorListRecord *items;
    s32 i;
    s32 ret;
    u8 *asset;

    total = 0;
    if (D_807500B0 == 0) {
        D_807500B0 = 1;
        for (i = 0; i < 0xDD; i++) {
            D_807FC408[i] = total;
            asset = assetLoad(9, i, 1, 1);
            if (asset != NULL) {
                modelAssetGetSubtables(asset, &subtableA, &subtables);
                container = (ActorListContainer *)subtables;
                count = container->count;
                items = container->items;
                for (j = 0; j < count; j++) {
                    ret = actorListGetTypeIdCount(items[j].actorType + 0x10);
                    total = (u16)(total + ret);
                }
                assetSetImmediateFree();
                assetFreeBuffer(asset, 0x168, 0x34);
            }
        }
    }
}


void actorListBuildLookupTable(void) {
    ActorListContainer *container;
    s32 count;
    s32 i;
    s32 ret;
    s32 sz;
    ActorListRecord *items;
    u8 *asset;
    u8 *subtableA;
    u8 *subtables;
    ActorListRecord *item;
    s32 offset;

    asset = assetLoad(9, gCurrentMap, 1, 1);
    D_807FC5C8 = 0;
    if (asset != NULL) {
        modelAssetGetSubtables(asset, &subtableA, &subtables);
        container = (ActorListContainer *)subtables;
        count = container->count;
        items = container->items;
    } else {
        count = 0;
    }
    if (count > 0) {
        i = 0;
        item = items;
        do {
            if (actorListGetTypeIdCount(item->actorType + 0x10) != 0) {
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
            ret = actorListGetTypeIdCount(item->actorType + 0x10);
            if (ret != 0) {
                D_807FC5C4[D_807FC5C8].id = item->id;
                D_807FC5C4[D_807FC5C8].flagIndex = ((u16 *)D_807FC408)[gCurrentMap] + offset + 0x26B;
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
        if (targetId == D_807FC5C4[i].id) {
            return D_807FC5C4[i].flagIndex;
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
        ((f32 *)actor->spawnData)[index] = val;
    }
}

void actorSetCustomInt(Actor *actor, s16 index, s32 val) {
    if (index < 8) {
        ((s32 *)actor->spawnData)[index] = val;
    }
}

void actorListSetCustomFloat(s16 mapIndex, s16 targetId, s16 index, f32 val) {
    s32 pad[2];
    u8 *subtableA;
    u8 *subtables;
    s32 modelIndex;
    s32 count;
    u8 found;
    ActorListRecord *item;

    found = 0;
    modelIndex = mapFindSlotIndex(mapIndex);
    if (modelIndex != -1) {
        modelAssetGetSubtables(D_8076A160[modelIndex].modelData, &subtableA, &subtables);
        count = *(s32 *)subtables;
        subtables += sizeof(s32);
        item = (ActorListRecord *)subtables;
        while (count != 0 && !found) {
            if (item->id == targetId) {
                item->customData[index] = val;
                found = 1;
            }
            count--;
            item++;
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
                if (node->id == id) {
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
        if (node->actor == actor) {
            return node->id;
        }
    }
    return 0;
}

Actor *actorListFindActorById(s16 targetId) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->id == targetId) {
            return node->actor;
        }
    }
}

void actorListSetPosById(s16 targetId, f32 posX, f32 posY, f32 posZ) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->id == targetId) {
            node->spawnX = posX;
            node->spawnY = posY;
            node->spawnZ = posZ;
            node->x = posX;
            node->y = posY;
            node->z = posZ;
            node->chunkIndex = mapChunkFindByPosition(posX, posY, posZ, 0);
            return;
        }
    }
}

void actorListSetPosByActor(Actor *actor, f32 posX, f32 posY, f32 posZ) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->actor == actor) {
            node->spawnX = posX;
            node->spawnY = posY;
            node->spawnZ = posZ;
            return;
        }
    }
}

void actorListSpawnFromRecords(u8 *records) {
    ActorListRecord *items;
    s32 i;
    s32 count;

    D_807FC400 = NULL;
    if (records != NULL) {
        count = *(s32 *)records;
        items = (ActorListRecord *)(records + 4);
        for (i = 0; i < count; i++) {
            actorListSpawnNodeInternal(items[i].actorType, items[i].x, items[i].y, items[i].z, items[i].yaw, items[i].scale, items[i].customData, 0, 0, items[i].id);
        }
        actorListClearForcedIds();
    }
}

void actorListSpawnNodePersistent(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale) {
    ActorListSub20 subData;

    subData = D_807500B4;
    actorListSpawnNodeInternal(actorType, posX, posY, posZ, yaw, scale, &subData, 0, 0, actorListAllocId());
}

void actorListSpawnNodeEntryDefault(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale, Actor *extraParam) {
    ActorListSub20 subData;

    subData = D_807500D4;
    actorListSpawnNodeInternal((s16)(actorType - 0x10), posX, posY, posZ, yaw, scale, &subData, 1, extraParam, actorListAllocId());
}

void actorListSpawnNodeEntry(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale, Actor *extraParam, void *customData) {
    actorListSpawnNodeInternal((s16)(actorType - 0x10), posX, posY, posZ, yaw, scale, customData, 1, extraParam, actorListAllocId());
}

typedef struct ActorListSpawnEntry {
    /* 0x00 */ s16 actorType;
    /* 0x02 */ s16 animAssetId;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 radius;
    /* 0x0A */ char unkA[2];
    /* 0x0C */ s32 (*shouldSpawn)(struct ActorListNode *);
    /* 0x10 */ s32 (*shouldDespawn)(struct ActorListNode *);
    /* 0x14 */ char unk14[0x1C];
} ActorListSpawnEntry;
extern ActorListSpawnEntry D_8074E8B0[];

ActorListNode *actorListSpawnNodeInternal(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale, void *customData, u8 spawnMode, Actor *extraParam, s16 targetId) {
    ActorListNode *node;
    s32 i;
    s32 found;
    s16 n;
    s16 key;

    n = 0x80;
    i = 0;
    found = 0;
    key = actorType + 0x10;
    while (!found && i < n) {
        if (key == D_8074E8B0[i].actorType) {
            found = 1;
        } else {
            i++;
        }
    }

    node = heapAlloc(sizeof(ActorListNode));
    node->actorType = actorType;
    node->id = targetId;
    node->spawnZ = posZ;
    node->z = posZ;
    node->spawnX = posX;
    node->x = posX;
    node->spawnY = posY;
    node->y = posY;
    node->yaw = yaw;
    node->scale = scale;
    node->actor = NULL;
    node->prev = NULL;
    node->spawned = 0;
    node->shouldSpawn = D_8074E8B0[i].shouldSpawn;
    node->shouldDespawn = D_8074E8B0[i].shouldDespawn;
    node->animAssetId = D_8074E8B0[i].animAssetId;
    node->chunkIndex = mapChunkFindByPosition(posX, posY, posZ, 0);
    node->spawnMode = spawnMode;
    node->extraParam = extraParam;
    node->radiusSq = (f32)D_8074E8B0[i].radius * (f32)D_8074E8B0[i].radius;

    for (i = 0; i < 8; i++) {
        node->customData[i] = ((f32 *)customData)[i];
    }

    node->next = D_807FC400;
    if (D_807FC400 != NULL) {
        D_807FC400->prev = node;
    }
    D_807FC400 = node;

    return node;
}





extern Actor *gSpawnedActor;

void actorListUpdateSpawns(void) {
    s32 pad;
    ActorSpawnInfo spawnInfo;
    Actor *actor;
    ActorListNode *node;
    s32 n;
    u8 found;
    s32 i;
    s16 target;

    n = 0x80;
    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->spawned != 0) {
            if (node->shouldDespawn(node) != 0) {
                actor = node->actor;
                if (!(actor->flags & 0x200000)) {
                    actorDeregisterActive(actor);
                    actor = node->actor;
                    node->spawned = 0;
                    node->x = actor->x;
                    node->y = actor->y;
                    node->z = actor->z;
                    node->chunkIndex = actor->chunkIndex;
                    controllerAnimFreeSub(actor, 0);
                    controllerAnimFreeSub(node->actor, 1);
                    controllerAnimFreeSub(node->actor, 2);
                }
            }
        } else if (node->shouldSpawn(node) != 0) {
            actor = node->actor;
            i = 0;
            found = 0;
            if (actor == NULL) {
                target = node->actorType + 0x10;
                while (!found && i < n) {
                    if (target == D_8074E8B0[i].actorType) {
                        found = 1;
                    } else {
                        i++;
                    }
                }

                spawnInfo.type = target;
                spawnInfo.scriptId = D_8074E8B0[i].unk4;
                spawnInfo.spawnArg = D_8074E8B0[i].animAssetId;
                spawnInfo.x = node->spawnX;
                spawnInfo.y = node->spawnY;
                spawnInfo.z = node->spawnZ;
                spawnInfo.yaw = node->yaw;
                spawnInfo.spawnTimer = 0;
                spawnInfo.spawnData = node->customData;
                if (actorSpawnFromInfo(&spawnInfo) != 0) {
                    node->actor = gSpawnedActor;
                    node->spawned = 1;
                    gSpawnedActor->parentActor = node->extraParam;
                    if (gSpawnedActor->sub4 != NULL) {
                        gSpawnedActor->sub4->scaleX = node->scale * 0.15;
                        gSpawnedActor->sub4->scaleY = node->scale * 0.15;
                        gSpawnedActor->sub4->scaleZ = node->scale * 0.15;
                    }
                }
            } else if (node->spawned == 0) {
                if (node->animAssetId != 0) {
                    node->actor->animState = controllerAnimStateLoadAsset(actor, node->animAssetId, 0);
                    actor = node->actor;
                }
                actorRegisterActive(actor);
                node->spawned = 1;
            }
        }
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
                if (despawnActor != 0 && node->actor != NULL) {
                    actorDespawn(node->actor);
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
            if (actor == node->actor) {
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
            if (node->spawnMode == 0 || (node->actor != NULL && (node->actor->renderFlags & 0x400))) {
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
            if (node->spawnMode == 0 || (node->actor != NULL && (node->actor->renderFlags & 0x400))) {
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
            if (node->spawnMode == 0 || (node->actor != NULL && (node->actor->renderFlags & 0x400))) {
                item.actorType = node->actorType;
                item.scale = node->scale;
                item.yaw = node->yaw;
                item.x = node->spawnX;
                item.y = node->spawnY;
                item.z = node->spawnZ;
                item.id = node->id;
                memcpy(item.customData, node->customData, 0x20);
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
            if (targetId == node->id) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (found) {
        if (node->actor != NULL) {
            actorAppendCallbackMemcpy8(gCurrentActor, node->actor, 0x1000000, 1, eventData, 0);
        }
    }
}

s32 actorListGetOrSetState(s16 targetId, u8 newState, u8 setFlag) {
    ActorListNode *node;
    s32 found = 0;

    node = D_807FC400;
    if (node != NULL) {
        do {
            if (targetId == node->id) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (!found) {
        return 0;
    }
    if (node->actor == NULL) {
        return 0;
    }
    if (setFlag != 0) {
        node->actor->state = newState;
    }
    return node->actor->state;
}

s32 actorListIsIdActive(s16 targetId) {
    ActorListNode *node;
    s32 found = 0;

    node = D_807FC400;
    if (node != NULL) {
        do {
            if (targetId == node->id) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (!found) {
        return 0;
    }
    if (node->spawned != 0) {
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
    ActorListRecord *records;
    f32 dist;

    records = (ActorListRecord *)(recordList + 1);
    for (i = 0; i < total; i++) {
        for (j = 0; j < typeCount; j++) {
            if (typeList[j] == records[i].actorType + 0x10) {
                dist = (records[i].x - posX) * (records[i].x - posX) + (records[i].y - posY) * (records[i].y - posY) + (records[i].z - posZ) * (records[i].z - posZ);
                if (dist < minDistance) {
                    minDistance = dist;
                    bestIndex = records[i].id;
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
        mapChunkIsVisible(node->chunkIndex);
    } else {
        actorListSpawnIfNear(node);
    }
}

u8 func_80689EE4(ActorListNode *node) {
    if (mapIsBossArena()) {
        return mapChunkIsVisible(node->actor->chunkIndex) == 0;
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
    s32 shouldSpawn = mapChunkIsVisible(node->chunkIndex) != 0;
    if (shouldSpawn != 0) {
        f32 dist = playerGetMinSquaredDist3D(node->x, node->y, node->z);
        shouldSpawn = 0;
        if (dist < node->radiusSq) {
            shouldSpawn = 1;
        }
    }
    return shouldSpawn;
}

u8 actorListDespawnIfFar(ActorListNode *node) {
    return (mapChunkIsVisible(node->actor->chunkIndex) == 0 || !(playerGetMinSquaredDist3D(node->x, node->y, node->z) < node->radiusSq)) && (node->actor->riderList == NULL);
}

u8 actorListDespawnIfFarAndIdle(ActorListNode *node) {
    return (mapChunkIsVisible(node->actor->chunkIndex) == 0 || !(playerGetMinSquaredDist3D(node->x, node->y, node->z) < node->radiusSq)) && (node->actor->riderList == NULL) && (node->actor->state == 0);
}

s32 actorListDespawnNever(s32 node) {
    return 0;
}

u8 actorListIsPlayerInRadius(ActorListNode *node) {
    s32 isInRadius;
    f32 dist = playerGetMinSquaredDist3D(node->x, node->y, node->z);
    isInRadius = 0;
    if (dist < node->radiusSq) {
        isInRadius = 1;
    }
    return isInRadius;
}

u8 actorListIsPlayerOutsideRadius(ActorListNode *node) {
    return !(playerGetMinSquaredDist3D(node->actor->x, node->actor->y, node->actor->z) < node->radiusSq);
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
        if (node->id == D_807FC5D0[i] && node->spawned == 0) {
            return 1;
        }
    }
    return 0;
}

s32 actorListDespawnIfForced(ActorListNode *node) {
    s32 i;
    for (i = 0; i < D_807FC611; i++) {
        if (node->id == D_807FC5F0[i] && node->spawned != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8068A2FC(Actor *actor) {
    actor->alpha = 0;
    actor->flags &= ~0x8000;
    actor->unk144 = 1;
    actor->callbackMask = 0;
    actor->state = 0x63;
    func_8066E6C8(actor, 0, 0);
}
