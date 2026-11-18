#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
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

// Spawn id -> flag index pair built per map (sActorListFlagEntries, sActorListFlagEntryCount entries).
typedef struct ActorListFlagEntry {
    /* 0x0 */ u8 id;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 flagIndex;
} ActorListFlagEntry;

// The 8-word custom data block a spawner copies into a node's customData.
typedef struct ActorListCustomData {
    s32 words[8];
} ActorListCustomData;

typedef struct ActorListNode {
    /* 0x00 */ s16 actorType;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ f32 spawnX;
    /* 0x08 */ f32 spawnY;
    /* 0x0C */ f32 spawnZ;
    /* 0x10 */ f32 x;
    /* 0x14 */ f32 y;
    /* 0x18 */ f32 z;
    /* 0x1C */ s16 yaw;
    /* 0x1E */ s16 pad1E;
    /* 0x20 */ f32 scale;
    /* 0x24 */ f32 customData[8];
    /* 0x44 */ Actor *actor;
    /* 0x48 */ u8 spawned;
    /* 0x49 */ u8 pad49;
    /* 0x4A */ s16 chunkIndex;
    /* 0x4C */ u8 spawnMode;
    /* 0x4D */ char pad4D[3];
    /* 0x50 */ Actor *parentActor;
    /* 0x54 */ f32 radiusSq;
    /* 0x58 */ s16 animAssetId;
    /* 0x5A */ s16 id;
    /* 0x5C */ s32 (*shouldSpawn)(struct ActorListNode *);
    /* 0x60 */ s32 (*shouldDespawn)(struct ActorListNode *);
    /* 0x64 */ struct ActorListNode *prev;
    /* 0x68 */ struct ActorListNode *next;
} ActorListNode;

extern s32 gCurrentMap;
extern ActorListCustomData D_807500B4;
extern ActorListCustomData D_807500D4;
extern Actor *gCurrentActor;
extern ActorListNode *gActorListHead;
extern ActorListFlagEntry *sActorListFlagEntries;
extern u8 sActorListFlagEntryCount;
extern s16 D_807FC5D0[16];
extern s16 D_807FC5F0[16];
extern u8 D_807FC610;
extern u8 D_807FC611;


extern s16 gCurrentLevelIndex;
extern u8 gCurrentWorldId;
extern u8 *gSavedMapModelData;
extern s32 gMapChunkCount;

extern Struct8076A160 D_8076A160[];


void actorMapModelsSetup(u8 *modelData, u8 loadMode, u8 skipExtra) {
    u8 *modelEntries;
    u8 *records;
    s32 slot;
    s32 modelAsset;
    u16 preMapModelCount;
    u8 checkSaved;
    s32 chunk;

    checkSaved = 0;
    actorListBuildLookupTable();
    slot = mapFindSlotIndex(gCurrentMap);
    if (slot == -1) {
        switch (loadMode) {
        case 0:
            gSavedMapModelData = modelData;
            preMapModelCount = modelTypeCountBeforeMap(gCurrentWorldId);
            checkSaved = 1;
            break;
        case 1:
            modelData = gSavedMapModelData;
            break;
        }
    } else {
        gSavedMapModelData = modelData;
        modelData = D_8076A160[slot].modelData;
    }
    modelAssetGetSubtables(modelData, &modelEntries, &records);
    if (skipExtra != 0) {
        modelAsset = 0;
    } else {
        modelAsset = playerGetModelAssetId();
    }
    modelSlotsLoadMap(modelEntries, modelAsset, checkSaved, preMapModelCount, mapGetHubWorldIndex(gCurrentWorldId, 1));
    csTimerQueueFire(gCurrentLevelIndex);
    actorListSpawnFromRecords(records);
    if (slot != -1) {
        if (D_8076A160[slot].records != NULL) {
            modelSlotsApplyRecords(D_8076A160[slot].records, D_8076A160[slot].recordSize);
        }
        for (chunk = 0; chunk < gMapChunkCount; chunk++) {
            lightSetColor(
                D_8076A160[slot].rgb[chunk][0] / 255.0,
                D_8076A160[slot].rgb[chunk][1] / 255.0,
                D_8076A160[slot].rgb[chunk][2] / 255.0,
                chunk);
        }
    }
}

extern u8 sActorListOffsetsReady;
extern u16 sActorListMapFlagBase[];


typedef struct ActorListContainer {
    s32 count;
    ActorListRecord items[1];
} ActorListContainer;

void actorListInitOffsets(void) {
    s32 j;
    s32 count;
    u16 total;
    u8 *modelEntries;
    u8 *records;
    ActorListContainer *container;
    ActorListRecord *items;
    s32 i;
    u8 *asset;

    total = 0;
    if (sActorListOffsetsReady == 0) {
        sActorListOffsetsReady = 1;
        for (i = 0; i < 0xDD; i++) {
            sActorListMapFlagBase[i] = total;
            asset = assetLoad(9, i, 1, 1);
            if (asset != NULL) {
                modelAssetGetSubtables(asset, &modelEntries, &records);
                container = (ActorListContainer *)records;
                count = container->count;
                items = container->items;
                for (j = 0; j < count; j++) {
                    total += actorListGetTypeIdCount(items[j].actorType + 0x10);
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
    s32 idCount;
    s32 pad;
    ActorListRecord *items;
    u8 *asset;
    u8 *modelEntries;
    u8 *records;
    s32 offset;

    asset = assetLoad(9, gCurrentMap, 1, 1);
    sActorListFlagEntryCount = 0;
    if (asset != NULL) {
        modelAssetGetSubtables(asset, &modelEntries, &records);
        container = (ActorListContainer *)records;
        count = container->count;
        items = container->items;
    } else {
        count = 0;
    }
    for (i = 0; i < count; i++) {
        if (actorListGetTypeIdCount(items[i].actorType + 0x10) != 0) {
            sActorListFlagEntryCount++;
        }
    }
    if (sActorListFlagEntryCount) {
        sActorListFlagEntries = heapAlloc(sActorListFlagEntryCount * sizeof(ActorListFlagEntry));
    } else {
        sActorListFlagEntries = NULL;
        return;
    }
    sActorListFlagEntryCount = 0;
    offset = 0;
    for (i = 0; i < count; i++) {
        idCount = actorListGetTypeIdCount(items[i].actorType + 0x10);
        if (idCount != 0) {
            sActorListFlagEntries[sActorListFlagEntryCount].id = items[i].id;
            sActorListFlagEntries[sActorListFlagEntryCount].flagIndex = sActorListMapFlagBase[gCurrentMap] + offset + 0x26B;
            offset += idCount;
            sActorListFlagEntryCount++;
        }
    }
    assetSetImmediateFree();
    assetFreeBuffer(asset, 0x1AA, 0x34);
}

s32 actorListLookupEntry(u16 targetId) {
    s32 i;

    for (i = 0; i < sActorListFlagEntryCount; i++) {
        if (targetId == sActorListFlagEntries[i].id) {
            return sActorListFlagEntries[i].flagIndex;
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

void actorListSetCustomFloat(s16 map, s16 targetId, s16 index, f32 val) {
    s32 pad[2];
    u8 *modelEntries;
    u8 *records;
    s32 slot;
    s32 count;
    u8 found;
    ActorListRecord *item;

    found = 0;
    slot = mapFindSlotIndex(map);
    if (slot != -1) {
        modelAssetGetSubtables(D_8076A160[slot].modelData, &modelEntries, &records);
        count = *(s32 *)records;
        records += sizeof(s32);
        item = (ActorListRecord *)records;
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
        node = gActorListHead;
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

    for (node = gActorListHead; node != NULL; node = node->next) {
        if (node->actor == actor) {
            return node->id;
        }
    }
    return 0;
}

Actor *actorListFindActorById(s16 targetId) {
    ActorListNode *node;

    for (node = gActorListHead; node != NULL; node = node->next) {
        if (node->id == targetId) {
            return node->actor;
        }
    }
}

void actorListSetPosById(s16 targetId, f32 posX, f32 posY, f32 posZ) {
    ActorListNode *node;

    for (node = gActorListHead; node != NULL; node = node->next) {
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

    for (node = gActorListHead; node != NULL; node = node->next) {
        if (node->actor == actor) {
            node->spawnX = posX;
            node->spawnY = posY;
            node->spawnZ = posZ;
            return;
        }
    }
}

void actorListSpawnFromRecords(u8 *records) {
    ActorListContainer *container;
    ActorListRecord *items;
    s32 i;
    s32 count;

    gActorListHead = NULL;
    if (records != NULL) {
        container = (ActorListContainer *)records;
        count = container->count;
        items = container->items;
        for (i = 0; i < count; i++) {
            actorListSpawnNodeInternal(items[i].actorType, items[i].x, items[i].y, items[i].z, items[i].yaw, items[i].scale, items[i].customData, 0, 0, items[i].id);
        }
        actorListClearForcedIds();
    }
}

void actorListSpawnNodePersistent(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale) {
    ActorListCustomData customData;

    customData = D_807500B4;
    actorListSpawnNodeInternal(actorType, posX, posY, posZ, yaw, scale, &customData, 0, 0, actorListAllocId());
}

void actorListSpawnNodeEntryDefault(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale, Actor *parentActor) {
    ActorListCustomData customData;

    customData = D_807500D4;
    actorListSpawnNodeInternal(actorType - 0x10, posX, posY, posZ, yaw, scale, &customData, 1, parentActor, actorListAllocId());
}

void actorListSpawnNodeEntry(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale, Actor *parentActor, void *customData) {
    actorListSpawnNodeInternal(actorType - 0x10, posX, posY, posZ, yaw, scale, customData, 1, parentActor, actorListAllocId());
}

typedef struct ActorListSpawnEntry {
    /* 0x00 */ s16 actorType;
    /* 0x02 */ s16 animAssetId;
    /* 0x04 */ s32 scriptId;
    /* 0x08 */ s16 radius;
    /* 0x0A */ char padA[2];
    /* 0x0C */ s32 (*shouldSpawn)(ActorListNode *);
    /* 0x10 */ s32 (*shouldDespawn)(ActorListNode *);
    /* 0x14 */ char pad14[0x1C];
} ActorListSpawnEntry;
extern ActorListSpawnEntry gActorListSpawnTable[128];

ActorListNode *actorListSpawnNodeInternal(s16 actorType, f32 posX, f32 posY, f32 posZ, s16 yaw, f32 scale, void *customData, u8 spawnMode, Actor *parentActor, s16 targetId) {
    ActorListNode *node;
    s32 i;
    s32 found;
    s16 entryCount = sizeof(gActorListSpawnTable) / sizeof(gActorListSpawnTable[0]);
    s16 key;

    i = 0;
    found = 0;
    key = actorType + 0x10;
    while (!found && i < entryCount) {
        if (key == gActorListSpawnTable[i].actorType) {
            found = 1;
        } else {
            i++;
        }
    }

    node = heapAlloc(sizeof(ActorListNode));
    node->actorType = actorType;
    node->id = targetId;
    node->spawnX = posX;
    node->spawnY = posY;
    node->spawnZ = posZ;
    node->x = posX;
    node->y = posY;
    node->z = posZ;
    node->yaw = yaw;
    node->scale = scale;
    node->actor = NULL;
    node->prev = NULL;
    node->spawned = 0;
    node->shouldSpawn = gActorListSpawnTable[i].shouldSpawn;
    node->shouldDespawn = gActorListSpawnTable[i].shouldDespawn;
    node->animAssetId = gActorListSpawnTable[i].animAssetId;
    node->chunkIndex = mapChunkFindByPosition(posX, posY, posZ, 0);
    node->spawnMode = spawnMode;
    node->parentActor = parentActor;
    node->radiusSq = (f32)gActorListSpawnTable[i].radius * gActorListSpawnTable[i].radius;

    for (i = 0; i < 8; i++) {
        node->customData[i] = ((f32 *)customData)[i];
    }

    node->next = gActorListHead;
    if (gActorListHead != NULL) {
        gActorListHead->prev = node;
    }
    gActorListHead = node;

    return node;
}





extern Actor *gSpawnedActor;

void actorListUpdateSpawns(void) {
    s32 pad;
    ActorSpawnInfo spawnInfo;
    Actor *actor;
    ActorListNode *node;
    s32 entryCount = sizeof(gActorListSpawnTable) / sizeof(gActorListSpawnTable[0]);
    u8 found;
    s32 i;
    s16 target;

    for (node = gActorListHead; node != NULL; node = node->next) {
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
                    controllerAnimFreeModel(actor, 0);
                    controllerAnimFreeModel(node->actor, 1);
                    controllerAnimFreeModel(node->actor, 2);
                }
            }
        } else if (node->shouldSpawn(node) != 0) {
            actor = node->actor;
            if (actor == NULL) {
                i = 0;
                found = 0;
                target = node->actorType + 0x10;
                while (!found && i < entryCount) {
                    if (target == gActorListSpawnTable[i].actorType) {
                        found = 1;
                    } else {
                        i++;
                    }
                }

                spawnInfo.type = target;
                spawnInfo.scriptId = gActorListSpawnTable[i].scriptId;
                spawnInfo.spawnArg = gActorListSpawnTable[i].animAssetId;
                spawnInfo.x = node->spawnX;
                spawnInfo.y = node->spawnY;
                spawnInfo.z = node->spawnZ;
                spawnInfo.yaw = node->yaw;
                spawnInfo.spawnTimer = 0;
                spawnInfo.spawnData = node->customData;
                if (actorSpawnFromInfo(&spawnInfo) != 0) {
                    node->actor = gSpawnedActor;
                    node->spawned = 1;
                    gSpawnedActor->parentActor = node->parentActor;
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

void actorListRemoveAndDespawn(ActorListNode *node) {
    actorListRemoveNodeInternal(node, 1);
}

void actorListRemoveNode(ActorListNode *node) {
    actorListRemoveNodeInternal(node, 0);
}

void actorListRemoveNodeInternal(ActorListNode *targetNode, u8 despawnActor) {
    ActorListNode *node;
    ActorListNode *prev;
    s32 found;

    found = 0;
    node = gActorListHead;
    prev = NULL;
    while (!found && node != NULL) {
        if (node == targetNode) {
            found = 1;
            if (despawnActor != 0 && node->actor != NULL) {
                actorDespawn(node->actor);
            }
            if (prev != NULL) {
                prev->next = node->next;
            } else {
                gActorListHead = node->next;
            }
            if (node->next != NULL) {
                node->next->prev = prev;
            }
            heapFree(node);
        } else {
            prev = node;
            node = node->next;
        }
    }
}

void actorListRemoveByActor(Actor *actor) {
    ActorListNode *node;
    ActorListNode *prev;
    s32 found;

    found = 0;
    node = gActorListHead;
    prev = NULL;
    if (node != NULL) {
        do {
            if (actor == node->actor) {
                found = 1;
                if (prev != NULL) {
                    prev->next = node->next;
                } else {
                    gActorListHead = node->next;
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

    node = gActorListHead;
    if (node != NULL) {
        do {
            next = node->next;
            heapFree(node);
            node = next;
        } while (node != NULL);
    }
    gActorListHead = NULL;
}

s32 actorListGetSerializedSize(void) {
    ActorListNode *node;
    s32 count;

    node = gActorListHead;
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
    node = gActorListHead;
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
    node = gActorListHead;
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
    ActorListNode *node = gActorListHead;
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

    node = gActorListHead;
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

    node = gActorListHead;
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

extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;

f32 playerGetMinSquaredDist3D(f32 posX, f32 posY, f32 posZ) {
    f32 minDist = 100000000.0f;
    s32 i;

    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].active != 0) {
            f32 dist = (posX - gPlayerSlots[i].camX) * (posX - gPlayerSlots[i].camX) + (posY - gPlayerSlots[i].camY) * (posY - gPlayerSlots[i].camY) + (posZ - gPlayerSlots[i].camZ) * (posZ - gPlayerSlots[i].camZ);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

s32 actorListSpawnAlways(ActorListNode *node) {
    return 1;
}

s32 actorListSpawnIfNearOrBossChunkVisible(ActorListNode *node) {
    if (mapIsBossArena()) {
        return mapChunkIsVisible(node->chunkIndex);
    }
    return actorListSpawnIfNear(node);
}

u8 actorListDespawnIfFarOrBossChunkHidden(ActorListNode *node) {
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

s32 actorListDespawnNever(ActorListNode *node) {
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

void actorHideAndDisable(Actor *actor) {
    actor->alpha = 0;
    actor->flags &= ~0x8000;
    actor->unk144 = 1;
    actor->callbackMask = 0;
    actor->state = 0x63;
    actorSetTriangleEnableById(actor, 0, 0);
}
