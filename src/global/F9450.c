#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "cutscene.h"
#include "sched.h"
#include "proto/global/104F0.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/2F550.h"
#include "proto/global/36880.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/5E020.h"
#include "proto/global/6AD90.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/AA960.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"

extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s32 gCurrentMap;

// A sphere the grid tests nodes against: the player's own (D_807FD740) and extra ones
// appended per player (D_807FD780 lists).
typedef struct GridBounds {
    f32 x;
    f32 y;
    f32 z;
    f32 radius;
} GridBounds;

typedef struct GridBoundsNode {
    GridBounds bounds;
    struct GridBoundsNode *next;
} GridBoundsNode;

// Collectable model node in a grid cell list (gGridCells[cell]) or the global list gGridGlobalNodes.
typedef struct GridNode {
    s16 modelSlot;
    s16 modelType;
    s16 requiredActorType;
    s16 flagIndex;
    s16 x;
    s16 y;
    s16 z;
    u8 collected;
    u8 padF;
    s16 delay;
    u8 playSound;
    u8 collisionOverride;
    u8 typeIndex;
    u8 pad15[3];
    struct GridNode *next;
} GridNode; // size = 0x1C

// Collected node flying to its queue slot (D_807FD730 list).
typedef struct GridActiveNode {
    s16 modelSlot;
    s16 modelType;
    f32 startX;
    f32 startY;
    f32 startZ;
    u8 started;
    u8 pad11[3];
    f32 progress;
    u8 delay;
    u8 playSound;
    u8 collisionOverride;
    u8 pad1B;
    struct GridActiveNode *next;
} GridActiveNode; // size = 0x20

// gGridTypeTable: 0x2A collectable model types.
typedef struct GridTypeEntry {
    s16 modelType;
    s8 queueSlot;
    u8 pad3;
    f32 speed;
    f32 limit;
    s16 requiredActorType;
    s16 actorType;
    s16 yOffset;
    s16 radius;
} GridTypeEntry; // size = 0x14

typedef struct DelayedSpawn {
    s32 isActor;
    s32 type;
    s16 x;
    s16 y;
    s16 z;
    s16 padE;
    s32 timer;
} DelayedSpawn; // size = 0x14

// This TU's .data (0x80753EF0-0x8075427C + 4-byte TU pad), in address order.
GridTypeEntry gGridTypeTable[42] = {
    { 0xD, 0, 0, 0.08f, 0.95f, 0x2, 0x0, 0, 0 },
    { 0xA, 0, 0, 0.08f, 0.95f, 0x3, 0x0, 0, 0 },
    { 0x1F, 0, 0, 0.08f, 0.95f, 0x6, 0x0, 0, 0 },
    { 0x1E, 0, 0, 0.08f, 0.95f, 0x4, 0x0, 0, 0 },
    { 0x16, 0, 0, 0.08f, 0.95f, 0x5, 0x0, 0, 0 },
    { 0x24, 1, 0, 0.08f, 0.95f, 0x3, 0x35, 0, 0 },
    { 0x23, 1, 0, 0.08f, 0.95f, 0x4, 0x35, 0, 0 },
    { 0x27, 1, 0, 0.08f, 0.95f, 0x6, 0x35, 0, 0 },
    { 0x1C, 1, 0, 0.08f, 0.95f, 0x5, 0x35, 0, 0 },
    { 0x1D, 1, 0, 0.08f, 0.95f, 0x2, 0x35, 0, 0 },
    { 0x2B, 0, 0, 0.08f, 0.95f, 0x2, 0x6E, 0, 0 },
    { 0x208, 0, 0, 0.08f, 0.95f, 0x3, 0x6E, 0, 0 },
    { 0x206, 0, 0, 0.08f, 0.95f, 0x6, 0x6E, 0, 0 },
    { 0x205, 0, 0, 0.08f, 0.95f, 0x4, 0x6E, 0, 0 },
    { 0x207, 0, 0, 0.08f, 0.95f, 0x5, 0x6E, 0, 0 },
    { 0x74, 8, 0, 0.08f, 0.95f, 0x0, 0x2D, 8, 4 },
    { 0x56, 4, 0, 0.08f, 0.95f, 0x0, 0x34, 0, 0 },
    { 0x8F, -2, 0, 0.08f, 0.95f, 0x0, 0x33, 0, 0 },
    { 0x11, -2, 0, 0.08f, 0.95f, 0x0, 0x0, 0, 0 },
    { 0x91, 2, 0, 0.08f, 0.95f, 0x0, 0x0, 0, 0 },
    { 0x8E, 5, 0, 0.08f, 0.95f, 0x0, 0x79, 0, 0 },
    { 0x57, -1, 0, 0.08f, 0.95f, 0x0, 0x2F, 0, 0 },
    { 0x98, 6, 0, 0.08f, 0.95f, 0x0, 0x0, 0, 0 },
    { 0x90, 10, 0, 0.08f, 0.95f, 0x0, 0x0, 0, 0 },
    { 0xEC, 11, 0, 0.08f, 0.95f, 0x0, 0x36, 0, 0 },
    { 0x13C, -1, 0, 0.08f, 0.95f, 0x0, 0x48, 25, 20 },
    { 0xDE, 12, 0, 0.08f, 0.95f, 0x2, 0x4E, 0, 0 },
    { 0xE0, 12, 0, 0.08f, 0.95f, 0x3, 0x4B, 0, 0 },
    { 0xE1, 12, 0, 0.08f, 0.95f, 0x4, 0x4D, 0, 0 },
    { 0xDD, 12, 0, 0.08f, 0.95f, 0x5, 0x4F, 0, 0 },
    { 0xDF, 12, 0, 0.08f, 0.95f, 0x6, 0x4C, 0, 0 },
    { 0x15D, 2, 0, 0.08f, 0.95f, 0x0, 0x0, 0, 0 },
    { 0x15E, 2, 0, 0.08f, 0.95f, 0x0, 0x0, 0, 0 },
    { 0x15F, 2, 0, 0.08f, 0.95f, 0x0, 0x0, 0, 0 },
    { 0x160, 2, 0, 0.08f, 0.95f, 0x0, 0x0, 0, 0 },
    { 0x18D, -1, 0, 0.08f, 0.95f, 0x0, 0x56, 0, 0 },
    { 0xB7, 1, 0, 0.08f, 0.95f, 0x0, 0x8C, 0, 0 },
    { 0x1CF, -1, 0, 0.08f, 0.95f, 0x0, 0x78, 0, 0 },
    { 0x1D0, -1, 0, 0.08f, 0.95f, 0x0, 0x77, 0, 0 },
    { 0x1D1, -1, 0, 0.08f, 0.95f, 0x0, 0x76, 0, 0 },
    { 0x1D2, 1, 0, 0.08f, 0.95f, 0x0, 0x7A, 0, 0 },
    { 0x288, 8, 0, 0.08f, 0.95f, 0x0, 0x2D, 8, 4 },
};
u8 D_80754238[8] = { 2, 2, 3, 1, 1, 0, 0, 0 }; // per-kong move level needed for ability energy
DelayedSpawn *gDelayedSpawnQueue = NULL;
GridNode **gGridCells = NULL;
s32 D_80754248[7] = { 0x34, 0x76, 0x33, 0x77, 0x78, 0x2F, 0x79 }; // respawn pickup actor types
s32 D_80754264[6] = { 0x56, 0x8F, 0x11, 0x1D2, 0x8E, 0x57 }; // respawn pickup model types

void gridRebuildNodeLists(void) {
    gridFreeAllNodeLists();
    gridBuildNodeLists();
}

extern GridBounds D_807FD740[];
extern GridBoundsNode *D_807FD780[];

// One placed model of the map's model asset (assetLoad table 9); same record as 36880.c's.
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 rotX;
    /* 0x1C */ f32 rotY;
    /* 0x20 */ f32 rotZ;
    /* 0x24 */ f32 yOffset;
    /* 0x28 */ s16 modelType;
    /* 0x2A */ s16 mapObjectId;
    /* 0x2C */ u8 pad2C[2];
    /* 0x2E */ u8 light;
    /* 0x2F */ u8 flags;
} ModelAssetEntry; /* 0x30 */

extern u16 D_807F9450;
extern u16 D_807F9452;
extern u16 D_807F9454;
extern u16 D_807F9456;
extern s16 D_807FD720;
extern s16 D_807FD722;
extern s16 D_807FD724;
extern s16 D_807FD726;
extern s16 D_807FD728;
extern GridNode *gGridGlobalNodes;
extern GridActiveNode *D_807FD730;
extern u8 D_807FD738;
extern u8 D_807FD798;

void gridBuildNodeLists(void) {
    s32 cursor;
    s32 found;
    f32 posX;
    f32 posY;
    f32 posZ;
    s16 modelId;
    s16 type;
    GridNode *head;
    GridTypeEntry *typeEntry;
    GridNode *node;
    GridNode *tail;
    GridNode *copy;
    s16 zMin;
    s32 cellIdx;
    s32 xi;
    s32 zi;
    s32 i;
    s32 pad;
    s32 idx;
    u8 *asset;
    u8 *entryData;
    u8 *unusedOut;
    s32 entryCount;
    ModelAssetEntry *entries;
    u16 baseCount;
    u16 count;
    s16 mapObjectId;

    tail = NULL;
    head = NULL;
    entryCount = 0;
    D_807FD738 = 0;
    if (gGlobalOverlayFlags & 0x10000) {
        gDelayedSpawnQueue = heapAlloc(60 * sizeof(DelayedSpawn));
        heapClearBlock(gDelayedSpawnQueue);
    } else {
        gDelayedSpawnQueue = NULL;
    }
    baseCount = modelTypeCountBeforeMap(gCurrentMap);
    asset = assetLoad(9, gCurrentMap, 1, 1);
    if (asset != NULL) {
        modelAssetGetSubtables(asset, &entryData, &unusedOut);
        entryCount = *(s32 *) entryData;
        entries = (ModelAssetEntry *) (entryData + 4);
    }
    D_807FD726 = 0;
    D_807FD728 = 0;
    D_807FD730 = NULL;
    gGridGlobalNodes = NULL;
    for (i = 0; i < gPlayerCount; i++) {
        D_807FD740[i].x = 0.0f;
        D_807FD740[i].y = 0.0f;
        D_807FD740[i].z = 0.0f;
        D_807FD740[i].radius = 0.0f;
        D_807FD780[i] = NULL;
    }
    D_807FD798 = 0;
    slotQueueInit(1);
    typeEntry = gGridTypeTable;
    for (i = 0; i < 0x2AU; i++) {
        type = typeEntry->modelType;
        cursor = 0;
        while (modelSlotFindByType(type, &cursor, &posX, &posY, &posZ, &modelId, &mapObjectId) != 0) {
            node = heapAlloc(sizeof(GridNode));
            node->x = posX;
            node->y = posY;
            node->z = posZ;
            node->modelSlot = modelId;
            node->requiredActorType = typeEntry->requiredActorType;
            node->modelType = type;
            node->collected = 0;
            node->delay = 0;
            node->playSound = 1;
            node->collisionOverride = 0;
            node->typeIndex = i;
            if (modelTypeIsCounted(typeEntry->modelType) != 0) {
                found = 0;
                idx = 0;
                count = 0;
                while (found == 0 && idx < entryCount) {
                    if (mapObjectId == entries[idx].mapObjectId) {
                        found = 1;
                    } else {
                        idx++;
                    }
                    if (found == 0 && modelTypeIsCounted(entries[idx - 1].modelType) != 0) {
                        count++;
                    }
                }
                if (found != 0) {
                    node->flagIndex = baseCount + count;
                } else {
                    node->flagIndex = -1;
                }
            } else {
                node->flagIndex = -1;
            }
            node->next = NULL;
            if (tail != NULL) {
                tail->next = node;
            } else {
                head = node;
            }
            tail = node;
        }
        typeEntry++;
    }
    D_807FD726 = D_807F9450 * D_807F9454;
    D_807FD728 = D_807F9452 * D_807F9456;
    D_807FD722 = D_807FD726 / 500 + 1;
    D_807FD724 = D_807FD728 / 500 + 1;
    D_807FD720 = D_807FD722 * D_807FD724;
    gGridCells = heapAlloc(D_807FD720 * sizeof(GridNode *));
    cellIdx = 0;
    for (zi = 0; zi < D_807FD724; zi++) {
        for (xi = 0; xi < D_807FD722; xi++) {
            gGridCells[cellIdx] = NULL;
            tail = NULL;
            for (node = head; node != NULL; node = node->next) {
                if (node->x >= (s16) (xi * 500) && node->x < (s16) (xi * 500 + 500)) {
                    zMin = zi * 500;
                    if (node->z >= zMin && node->z < (s16) (zi * 500 + 500)) {
                        copy = heapAlloc(sizeof(GridNode));
                        memcpy(copy, node, sizeof(GridNode));
                        copy->next = NULL;
                        if (tail != NULL) {
                            tail->next = copy;
                        } else {
                            gGridCells[cellIdx] = copy;
                        }
                        tail = copy;
                    }
                }
            }
            cellIdx++;
        }
    }
    while (head != NULL) {
        node = head;
        head = node->next;
        heapFree(node);
    }
    if (entryCount != 0) {
        assetSetImmediateFree();
        assetFreeBuffer(asset, 0x1C0, 0x14);
    }
}

void gridSetNodeBounds(u8 playerIndex, f32 x, f32 y, f32 z, f32 radius) {
    D_807FD740[playerIndex].x = x;
    D_807FD740[playerIndex].y = y;
    D_807FD740[playerIndex].z = z;
    D_807FD740[playerIndex].radius = radius;
    D_807FD780[playerIndex] = NULL;
}


void gridAppendPositionNode(u8 playerIndex, f32 x, f32 y, f32 z, f32 radius) {
    GridBoundsNode **link;

    link = &D_807FD780[playerIndex];
    while (*link != NULL) {
        link = &(*link)->next;
    }
    *link = heapAlloc(sizeof(GridBoundsNode));
    heapClearBlock(*link);
    (*link)->bounds.x = x;
    (*link)->bounds.y = y;
    (*link)->bounds.z = z;
    (*link)->bounds.radius = radius;
    heapFreeDeferred(*link);
}


s32 gridTypeEntryIndex(s16 modelType) {
    GridTypeEntry *entry;
    s32 found;
    s32 index;

    index = 0;
    found = 0;
    entry = gGridTypeTable;
    do {
        if (modelType == entry->modelType) {
            found = 1;
        } else {
            index++;
            entry++;
        }
    } while (found == 0);
    return index;
}


s32 gridCoordsToIndex(f32 x, f32 z) {
    s32 gridZ;
    s32 gridX;

    gridX = x / 500.0f;
    gridZ = z / 500.0f;
    if ((gridX > D_807FD722) || (gridZ > D_807FD724) || (x < 0.0f) || (z < 0.0f)) {
        return -1;
    }
    return (D_807FD722 * gridZ) + gridX;
}


void gridMoveNode(s16 modelSlot, f32 x, f32 y, f32 z) {
    s32 pad[4];
    GridNode *node;
    GridNode *prev;
    s32 i;
    s32 found;
    s32 idx;

    i = 0;
    found = 0;
    while (found == 0 && i < D_807FD720) {
        prev = NULL;
        node = gGridCells[i];
        while (node != NULL && modelSlot != node->modelSlot) {
            prev = node;
            node = node->next;
        }
        if (node != NULL && modelSlot == node->modelSlot) {
            found = 1;
            if (prev != NULL) {
                prev->next = node->next;
            } else {
                gGridCells[i] = node->next;
            }
        }
        i++;
    }
    idx = gridCoordsToIndex(x, z);
    if (idx <= D_807FD720 && idx >= 0) {
        node->next = gGridCells[idx];
        gGridCells[idx] = node;
        node->x = x;
        node->y = y;
        node->z = z;
    }
}

void gridAddModelNode(s16 modelSlot, s16 modelType, s16 delay, u8 playSound, u8 collisionOverride, u8 isGlobal) {
    GridNode *node;
    f32 x;
    f32 y;
    f32 z;
    f32 unusedA;
    f32 unusedB;
    f32 unusedC;
    f32 unusedD;
    f32 unusedE;
    s32 idx;
    s32 typeIndex;
    GridNode **tail;
    GridNode *cur;

    modelSlotGetTransformVectors(modelSlot, &x, &y, &z, &unusedA, &unusedB, &unusedC, &unusedD, &unusedE, 1);
    if (isGlobal || (((idx = gridCoordsToIndex(x, z)) <= D_807FD720) && (idx >= 0))) {
        node = heapAlloc(sizeof(GridNode));
        node->x = x;
        node->y = y;
        node->z = z;
        node->modelSlot = modelSlot;
        typeIndex = gridTypeEntryIndex(modelType);
        node->requiredActorType = gGridTypeTable[typeIndex].requiredActorType;
        node->modelType = modelType;
        node->collected = 0;
        node->delay = delay;
        node->playSound = playSound;
        node->flagIndex = -1;
        node->collisionOverride = collisionOverride;
        node->typeIndex = typeIndex;
        node->next = NULL;
        if (isGlobal) {
            cur = gGridGlobalNodes;
            tail = &gGridGlobalNodes;
        } else {
            cur = gGridCells[idx];
            tail = &gGridCells[idx];
        }
        while (cur != NULL) {
            tail = &cur->next;
            cur = cur->next;
        }
        *tail = node;
    }
}

void gridFreeAllNodeLists(void) {
    s32 cell;
    GridNode *next;
    GridNode *node;
    GridActiveNode *nextActive;
    GridActiveNode *active;

    if (gGridCells != NULL) {
        for (cell = 0; cell < D_807FD720; cell++) {
            node = gGridCells[cell];
            while (node != NULL) {
                next = node->next;
                heapFree(node);
                node = next;
            }
        }
        heapFree(gGridCells);
        gGridCells = NULL;
    }
    node = gGridGlobalNodes;
    while (node != NULL) {
        next = node->next;
        heapFree(node);
        node = next;
    }
    if (D_807FD730 != NULL) {
        active = D_807FD730;
        while (active != NULL) {
            nextActive = active->next;
            heapFree(active);
            active = nextActive;
        }
        D_807FD730 = NULL;
    }
    slotQueueReleaseAll();
}

void gridFreeAllActiveNodes(void) {
    GridActiveNode *node;
    GridActiveNode *next;

    D_807FD738 = 1;
    node = D_807FD730;
    while (node != NULL) {
        next = node->next;
        gridCollectItem(0, node->modelType, node->collisionOverride);
        modelSlotFreeByIndex(node->modelSlot, 1);
        heapFree(node);
        node = next;
    }
    D_807FD730 = NULL;
}

GridActiveNode *gridActiveNodeCreate(GridNode *src) {
    GridActiveNode *node;

    node = heapAlloc(sizeof(GridActiveNode));
    node->started = 0;
    node->progress = 0.0f;
    node->modelSlot = src->modelSlot;
    node->delay = src->delay;
    node->modelType = src->modelType;
    node->playSound = src->playSound;
    node->collisionOverride = src->collisionOverride;
    return node;
}

s32 gridResolveQueueSlot(s32 slot, s32 modelType, u8 override) {
    if ((modelType == 0x91) || (modelType == 0x15D) || (modelType == 0x15E) || (modelType == 0x15F) || (modelType == 0x160)) {
        if (override != 0) {
            slot = 3;
        }
    }
    return slot;
}


void cutsceneStartFlag16CPath(void) {
    if (flagGet(0x16C, 0) == 0) {
        camStartPath(NULL, 0x20, 5);
        flagSet(0x16C, 1, 0);
    }
}

extern s8 D_80029FA0;
extern u8 gCurrentWorldId;

void gridCollectItem(u8 playerIndex, s32 modelType, u8 collisionOverride) {
    s32 i;
    s32 slot;
    u8 shouldComplete;
    GridTypeEntry *entry;

    shouldComplete = 0;
    if ((gGlobalOverlayFlags & 0x10000000) && (modelType != 0x56)) {
        D_80029FA0--;
        return;
    }
    if (gCurrentMap != 0xF) {
        entry = &gGridTypeTable[gridTypeEntryIndex(modelType)];
        slot = gridResolveQueueSlot(entry->queueSlot, modelType, collisionOverride);
        switch (modelType) {
        case 0xDD: case 0xDE: case 0xDF: case 0xE0: case 0xE1:
            flagSet(flagGridIndex(0x1D5, mapGetHubWorldIndex(gCurrentWorldId, 1), gPlayerCharacterId[playerIndex]), 1, 0);
        case 0x74: case 0x288:
            slotQueueAddValue(slot, playerIndex, 1);
            shouldComplete = 1;
            break;
        case 0x91: case 0x15D: case 0x15E: case 0x15F: case 0x160:
            if (gPlayerCount == 1) {
                sfxPlayOnFreeSlot(0x331, 0x7FFF, 63.0f, 1.0f, 5, 0);
            }
        case 0xA: case 0xD: case 0x16: case 0x1E: case 0x1F:
            flagSet(0x18B, 1, 0);
            slotQueueAddValue(slot, playerIndex, 1);
            break;
        case 0x1C: case 0x1D: case 0x23: case 0x24: case 0x27:
            flagSet(0x18C, 1, 0);
        case 0x98: case 0xEC: case 0x1D2:
            slotQueueAddValue(slot, playerIndex, 1);
            break;
        case 0x56:
            flagSet(0x173, 1, 0);
            slotQueueAddValue(slot, playerIndex, 1);
            break;
        case 0xB7:
            for (i = 0; i < 5; i++) {
                gPlayerInventoryTable[playerIndex].kong[i].coins += 5;
            }
            cutsceneStartFlag16CPath();
            break;
        case 0x8E:
            slotQueueAddValue(slot, playerIndex, 0x96);
            break;
        case 0x57:
            playerAddHealthDelta(playerIndex, 1);
            break;
        case 0x13C:
            shouldComplete = 1;
            break;
        case 0x18D:
            shouldComplete = 1;
            break;
        }
        if (shouldComplete != 0) {
            eepromSavePlayerData();
        }
    }
}

void gridSpawnBunchItems(u8 playerIndex, s16 modelSlot, Actor *player) {
    s32 delay;
    s32 pad;
    f32 x;
    f32 y;
    f32 z;
    f32 unusedA;
    f32 unusedB;
    f32 unusedC;
    f32 unusedD;
    f32 unusedE;
    s32 i;
    s16 modelType;

    if (gPlayerCount == 1) {
        modelSlotGetTransformVectors(modelSlot, &x, &y, &z, &unusedA, &unusedB, &unusedC, &unusedD, &unusedE, 1);
    }
    switch (player->actorType) {
    case 3: modelType = 0xA; break;
    case 5: modelType = 0x16; break;
    case 4:
    case 9: modelType = 0x1E; break;
    case 6:
    case 7: modelType = 0x1F; break;
    case 2:
    case 8: modelType = 0xD; break;
    default: modelType = 0xD; break;
    }
    delay = 0;
    for (i = 0; i < 5; i++) {
        if (gPlayerCount == 1) {
            gridAddModelNode(modelSlotAppend(modelType, x, y, z, 0.0f, 0), modelType, delay, 1, 0, 1);
        } else {
            gridCollectItem(playerIndex, modelType, 0);
        }
        delay += 3;
    }
}

void gridSpawnAmmoCrateItems(u8 playerIndex, s16 modelSlot, Actor *player, u16 parentType) {
    s32 delay;
    f32 x;
    f32 y;
    f32 z;
    f32 unusedA;
    f32 unusedB;
    f32 unusedC;
    f32 unusedD;
    f32 unusedE;
    s32 i;
    s16 modelType;

    if (gPlayerCount == 1) {
        modelSlotGetTransformVectors(modelSlot, &x, &y, &z, &unusedA, &unusedB, &unusedC, &unusedD, &unusedE, 1);
    }
    switch (player->actorType) {
    case 3: modelType = 0x91; break;
    case 5: modelType = 0x15D; break;
    case 4: modelType = 0x15E; break;
    case 6:
    case 7: modelType = 0x15F; break;
    case 2: modelType = 0x160; break;
    default: modelType = 0x91; break;
    }
    delay = 0;
    for (i = 0; i < 5; i++) {
        if (gPlayerCount == 1) {
            gridAddModelNode(modelSlotAppend(modelType, x, y, z, 0.0f, 0), modelType, delay, 1, (parentType == 0x11) ? 1 : 0, 1);
        } else {
            gridCollectItem(playerIndex, modelType, (parentType == 0x11) ? 1 : 0);
        }
        delay += 3;
    }
}

s32 actorTypeIsRespawnPickup(s32 actorType) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (actorType == D_80754248[i]) {
            return 1;
        }
    }
    return 0;
}

s32 modelTypeIsRespawnPickup(s32 modelType) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (modelType == D_80754264[i]) {
            return 1;
        }
    }
    return 0;
}


void respawnPickRandomPickup(s32 *actorType, s32 *delay) {
    *actorType = D_80754248[(randomNonNegative() >> 0xF) % 7U];
    *delay = ((randomNonNegative() >> 0xF) % 32767 % 391) + 0xD2;
}

void delayedSpawnQueueAdd(s32 type, s32 isActor, s16 x, s16 y, s16 z, s32 delay) {
    s32 i;
    s32 found;

    found = 0;
    for (i = 0; i < 60 && !found; i++) {
        if (gDelayedSpawnQueue[i].timer == 0) {
            gDelayedSpawnQueue[i].isActor = isActor;
            gDelayedSpawnQueue[i].type = type;
            gDelayedSpawnQueue[i].x = x;
            gDelayedSpawnQueue[i].y = y;
            gDelayedSpawnQueue[i].z = z;
            gDelayedSpawnQueue[i].timer = delay;
            found = 1;
        }
    }
}

s32 delayedSpawnQueueContains(s32 type, s32 isActor, s16 x, s16 y, s16 z) {
    s32 i;
    s32 found;

    found = 0;
    for (i = 0; i < 60 && !found; i++) {
        if (gDelayedSpawnQueue[i].timer != 0 && type == gDelayedSpawnQueue[i].type && isActor == gDelayedSpawnQueue[i].isActor) {
            found = 1;
        }
    }
    return found;
}


void delayedSpawnQueueAddActor(s32 type, s32 delay, s16 x, s16 y, s16 z) {
    if ((mpIsMatchType(0) != 0) && (actorTypeIsRespawnPickup(type) != 0)) {
        respawnPickRandomPickup(&type, &delay);
    }
    delayedSpawnQueueAdd(type, 1, x, y, z, delay);
}

void delayedSpawnQueueAddRandomEffectPickup(s16 x, s16 y, s16 z) {
    delayedSpawnQueueAddActor(0x76, 0, x, y, z);
}


void delayedSpawnQueueAddModel(s32 type, s16 x, s16 y, s16 z, s32 delay) {
    if (modelTypeIsRespawnPickup(type) != 0) {
        delayedSpawnQueueAdd(type, 0, x, y, z, delay);
    }
}


void delayedSpawnQueueTick(void) {
    s32 i;

    if ((menuIsTransitionType6() != 0) && !(gGlobalPauseFlags & 2)) {
        for (i = 0; i < 60; i++) {
            if (gDelayedSpawnQueue[i].timer != 0) {
                gDelayedSpawnQueue[i].timer--;
                if (gDelayedSpawnQueue[i].timer == 5) {
                    effectSpawnParticleRingAtPosition(gDelayedSpawnQueue[i].x, gDelayedSpawnQueue[i].y, gDelayedSpawnQueue[i].z, 7);
                }
                if (gDelayedSpawnQueue[i].timer == 0) {
                    if (gDelayedSpawnQueue[i].isActor != 0) {
                        actorSpawnNodeEntryScaled(gDelayedSpawnQueue[i].type, gDelayedSpawnQueue[i].x, gDelayedSpawnQueue[i].y, gDelayedSpawnQueue[i].z, 0, 0x19, -1, NULL);
                    } else {
                        gridAddModelNode(modelSlotAppend(gDelayedSpawnQueue[i].type, gDelayedSpawnQueue[i].x, gDelayedSpawnQueue[i].y, gDelayedSpawnQueue[i].z, 0.0f, 0), gDelayedSpawnQueue[i].type, 0, 1, 0, 0);
                    }
                }
            }
        }
    }
}

extern GridActiveNode *D_807FD734;

void gridCollectNodesInBounds(GridNode *node, u8 playerIndex, GridBounds *bounds) {
    Actor *player;
    s32 dist;
    GridActiveNode *newNode;
    GridActiveNode *tail;

    player = gPlayerSlots[playerIndex].actor;
    while (node != NULL) {
        dist = camDistance3D(node->x, gGridTypeTable[node->typeIndex].yOffset + node->y, node->z, bounds->x, bounds->y, bounds->z);
        if ((node->collected == 0) &&
            (dist < gGridTypeTable[node->typeIndex].radius + bounds->radius) &&
            ((node->requiredActorType == 0) || (player->actorType == node->requiredActorType)) &&
            (func_8063C2A8(node->modelSlot) != 0) &&
            (gridCheckNodeCondition(node->modelSlot, playerIndex, node->modelType) != 0)) {
            node->collected = 1;
            modelSlotFreeNestedBuffer(node->modelSlot, 1);
            if (node->flagIndex != -1) {
                func_8060E430(node->flagIndex, 1, mapGetHubWorldIndex(gCurrentWorldId, 1));
            }
            if (gPlayerCount == 1) {
                if (D_807FD734 == NULL) {
                    tail = D_807FD730;
                    D_807FD734 = tail;
                    while (tail != NULL) {
                        D_807FD734 = tail;
                        tail = tail->next;
                    }
                }
                newNode = gridActiveNodeCreate(node);
                newNode->next = NULL;
                if (D_807FD730 != NULL) {
                    D_807FD734->next = newNode;
                    D_807FD734 = newNode;
                } else {
                    D_807FD730 = newNode;
                    D_807FD734 = newNode;
                }
            }
            switch (node->modelType) {
            case 0x2B:
            case 0x205:
            case 0x206:
            case 0x207:
            case 0x208:
                gridSpawnBunchItems(playerIndex, node->modelSlot, player);
                break;
            case 0x11:
            case 0x8F:
                gridSpawnAmmoCrateItems(playerIndex, node->modelSlot, player, node->modelType);
                break;
            default:
                if (gPlayerCount >= 2) {
                    gridCollectItem(playerIndex, node->modelType, node->collisionOverride);
                }
                break;
            }
            if (gPlayerCount >= 2) {
                playerStateHandleSoundEffects(node->modelType, playerIndex);
                modelSlotFreeByIndex(node->modelSlot, 1);
            }
            if ((gGlobalOverlayFlags & 0x10000) && (node->modelType != 0x1D2)) {
                delayedSpawnQueueAddModel(node->modelType, node->x, node->y, node->z, 0x258);
            }
        }
        node = node->next;
    }
}


void gridDispatchRect(u8 playerIndex, GridBounds *bounds) {
    f32 x;
    f32 z;
    f32 radius;
    s32 cell;

    if (gPlayerInventoryTable[playerIndex].health > 0) {
        radius = bounds->radius;
        x = bounds->x;
        if (x <= D_807FD726 + radius) {
            z = bounds->z;
            if (z <= D_807FD728 + radius) {
                cell = gridCoordsToIndex(x, z);
                if (cell >= 0) {
                    gridCollectNodesInBounds(gGridCells[cell], playerIndex, bounds);
                }
            }
        }
        gridCollectNodesInBounds(gGridGlobalNodes, playerIndex, bounds);
    }
}

extern ModelSlot *gModelSlots;

s32 gridCheckNodeCondition(s16 modelSlot, u8 playerIndex, u16 modelType) {
    u8 flags;
    PlayerState *playerState;
    ModelSlot *slot;

    switch (modelType) {
    case 0x11:
        if ((gPlayerInventoryTable[gCurrentPlayerIndex].kong[gPlayerCharacterId[gCurrentPlayerIndex]].weaponFlags & 3) != 3) {
            return 0;
        }
        break;
    case 0x8F:
        if ((gPlayerInventoryTable[gCurrentPlayerIndex].kong[gPlayerCharacterId[gCurrentPlayerIndex]].weaponFlags & 1) == 0) {
            return 0;
        }
        break;
    case 0x98:
        playerState = gPlayerSlots[gCurrentPlayerIndex].actor->customState;
        if ((playerState->stateFlags2 & 1) == 0) {
            return 0;
        }
        break;
    case 0x8E:
        playerState = gPlayerSlots[gCurrentPlayerIndex].actor->customState;
        if ((playerState->stateFlags2 & 2) == 0) {
            return 0;
        }
        break;
    case 0x90:
        slot = &gModelSlots[hashTableLookup(modelSlot)];
        if (slot->unk7C->unk64 != 0xFF) {
            return 0;
        }
        break;
    }
    flags = gModelSlots[hashTableLookup(modelSlot)].unk8C;
    if ((flags & 8) && (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 2)) {
        return 0;
    }
    if ((flags & 2) && (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 3)) {
        return 0;
    }
    if ((flags & 4) && (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 5)) {
        return 0;
    }
    if ((flags & 0x10) && (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 4)) {
        return 0;
    }
    if ((flags & 1) && (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 6)) {
        return 0;
    }
    return 1;
}

extern s16 D_807FD790[];
extern u8 gGfxBufferIndex;
extern s16 gCurrentLevelIndex;

void gridUpdatePlayerNodes(u8 playerIndex) {
    GridBoundsNode *rect;
    GridActiveNode *node;
    GridActiveNode *prev;
    GridActiveNode *next;
    GridTypeEntry *typeEntry;
    s32 idx;
    f32 mf[4][4];
    f32 inv[4][4];
    f32 outX;
    f32 outY;
    f32 outZ;
    s32 slot;
    f32 fx;
    f32 fy;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 unusedA;
    f32 unusedB;
    f32 unusedC;
    f32 unusedD;
    f32 unusedE;
    s32 padC[3];
    Mtx *mtx;
    f32 pz;
    f32 py;
    f32 px;
    s16 tableIndex;
    f32 fz;

    D_807FD798 = 0;
    gridCollectActorsInRange(playerIndex);
    D_807FD734 = NULL;
    gridDispatchRect(playerIndex, &D_807FD740[playerIndex]);
    rect = D_807FD780[playerIndex];
    while (rect != NULL) {
        gridDispatchRect(playerIndex, &rect->bounds);
        rect = rect->next;
    }
    if ((D_807FD730 != NULL) && (gPlayerCount == 1)) {
        mtx = &gPlayerSlots[playerIndex].viewMtx[gGfxBufferIndex];
        guMtxL2F(mf, mtx);
        matrix4Invert(inv, mf);
        node = D_807FD730;
        prev = NULL;
        while (node != NULL) {
            if (node->delay != 0) {
                node->delay--;
                prev = node;
                node = node->next;
            } else {
                idx = gridTypeEntryIndex(node->modelType);
                slot = gGridTypeTable[idx].queueSlot;
                if (node->started == 0) {
                    modelSlotGetTransformVectors(node->modelSlot, &vx, &vy, &vz, &unusedA, &unusedB, &unusedC, &unusedD, &unusedE, 1);
                    guMtxXFML(mtx, vx, vy, vz, &node->startX, &node->startY, &node->startZ);
                    node->started = 1;
                    func_806398E4(node->modelSlot, 1, 0);
                    if (node->playSound != 0) {
                        playerStateHandleSoundEffects(node->modelType, playerIndex);
                    }
                    if ((slot >= 0) && !(gGlobalOverlayFlags & 0x4000) && ((slot != 0xB) || !(gGlobalOverlayFlags & 0x10000000))) {
                        slotQueueUpdate(gridResolveQueueSlot(slot, node->modelType, node->collisionOverride), 0, 0);
                    }
                    switch (node->modelType) {
                    case 0xEC:
                        effectSpawnRandomSpread(vx, vy, vz, 0.1f, 200.0f, 0xA);
                        break;
                    case 0x18D:
                        effectSpawnRandomSpread(vx, vy, vz, 0.3f, 20.0f, 0x14);
                        break;
                    }
                    if (D_807FD798 != 4) {
                        tableIndex = csModelSlotGetTableIndex(node->modelSlot);
                        D_807FD790[D_807FD798] = tableIndex;
                        D_807FD798++;
                        flagSetForMapObject(gCurrentLevelIndex, tableIndex);
                    }
                }
                slotQueueGetPosition(slot, &px, &py, &pz);
                fx = ((px - node->startX) * node->progress) + node->startX;
                fy = ((py - node->startY) * node->progress) + node->startY;
                fz = ((pz - node->startZ) * node->progress) + node->startZ;
                guMtxXFMF(inv, fx, fy, fz, &outX, &outY, &outZ);
                next = node->next;
                typeEntry = &gGridTypeTable[idx];
                node->progress += typeEntry->speed;
                if ((node->progress > typeEntry->limit) || (typeEntry->queueSlot == -2)) {
                    gridCollectItem(playerIndex, node->modelType, node->collisionOverride);
                    modelSlotFreeByIndex(node->modelSlot, 1);
                    if (prev != NULL) {
                        prev->next = node->next;
                    } else {
                        D_807FD730 = node->next;
                    }
                    heapFree(node);
                } else {
                    modelSlotTransformBoundsAndNodes(node->modelSlot, outX, outY, outZ, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0, 0, 0, 1);
                    prev = node;
                }
                node = next;
            }
        }
    }
}

s32 kongUsesAbilityEnergy(s16 kong) {
    u8 result;

    result = 0;
    if (kong < 5) {
        result = gPlayerInventoryTable[0].kong[kong].moveLevel >= D_80754238[kong];
    }
    result |= flagGet(0x179, 0);
    return result;
}

s32 anyKongUsesAbilityEnergy(void) {
    s32 i;
    u8 uses;

    i = 0;
    do {
        uses = kongUsesAbilityEnergy(i);
        i++;
    } while (i < 5 && uses == 0);
    return uses;
}

void gridTickPlayers(void) {
    s16 globalFlagSet;
    u8 kongUsesEnergy;
    u8 i;
    PlayerState *ps;

    globalFlagSet = 0;
    kongUsesEnergy = 0;
    if (gGlobalOverlayFlags & 0x10000) {
        delayedSpawnQueueTick();
    }
    if (flagGet(0x179, 0) != 0) {
        globalFlagSet = 1;
    }
    if (kongUsesAbilityEnergy(gPlayerCharacterId[0]) != 0) {
        kongUsesEnergy = 1;
    }

    for (i = 0; i < gPlayerCount; i++) {
        ps = gPlayerSlots[i].actor->customState;
        if (globalFlagSet != 0) {
            ps->stateFlags2 |= 1;
        } else {
            ps->stateFlags2 &= ~1;
        }
        if (kongUsesEnergy) {
            ps->stateFlags2 |= 2;
        } else {
            ps->stateFlags2 &= ~2;
        }
        if ((gPlayerSlots[i].actor->state != 0x36) && (D_807FD738 == 0)) {
            gridUpdatePlayerNodes(i);
        }
    }
}


s32 listContainsS16(s16 value) {
    s32 i;

    for (i = 0; i < D_807FD798; i++) {
        if (value == D_807FD790[i]) {
            return 1;
        }
    }
    return 0;
}


extern u8 D_8071FC58;

void effectSpawnRandomSpread(f32 x, f32 y, f32 z, f32 scale, f32 spread, s32 count) {
    f32 dx;
    f32 dy;
    f32 dz;
    f64 half;
    s32 i;

    effectSetSpeed(0x1006E);
    effectSetCallback(effectLightPulseTealUpdate);
    effectSetDepth(1);
    effectCreateAtPosition(&D_8071FC58, scale, x, y, z);
    half = 1000.0 / ((f64) spread + (f64) spread);
    for (i = 0; i < count; i++) {
        dx = (randomLcgNext() / 10000U % 1000U) / spread - half;
        dy = (randomLcgNext() / 10000U % 1000U) / spread - half;
        dz = (randomLcgNext() / 10000U % 1000U) / spread - half;
        effectSetCallback(effectRandomDirectionDriftUpdate);
        effectSetAngle(i + 1);
        effectSetDepth(1);
        effectCreateAtPosition(&D_8071FC58, scale, x + dx, y + dy, z + dz);
    }
}


f32 pickupModelYOffset(u32 actorType) {
    if (actorType == 0x8C) {
        return -13.0f;
    }
    return 0.0f;
}


void gridCollectActorsInRange(u8 playerIndex) {
    Actor *player;
    s32 i;
    PlayerState *playerState;
    Actor *actor;
    DropBounceState *pickupState;
    GridBoundsNode *node;
    s32 found;
    s32 isGlobal;
    PlayerState *ps;
    s32 typeIndex;
    s16 modelSlot;
    s16 tableIndex;

    player = gPlayerSlots[playerIndex].actor;
    playerState = player->customState;
    if (gPlayerInventoryTable[playerIndex].health > 0) {
        for (typeIndex = 0; typeIndex < 0x2A; typeIndex++) {
            if (gGridTypeTable[typeIndex].actorType != 0) {
                for (i = 0; i < gActiveActorCount; i++) {
                    actor = gActiveActors[i].actor;
                    if ((gGlobalPauseFlags & 0x10000) && (gGridTypeTable[typeIndex].actorType == actor->actorType) && ((gGridTypeTable[typeIndex].requiredActorType == 0) || (gGridTypeTable[typeIndex].requiredActorType == player->actorType))) {
                        node = D_807FD780[playerIndex];
                        found = gGridTypeTable[typeIndex].radius + D_807FD740[playerIndex].radius - 1.0f > camDistance3D(actor->x, gGridTypeTable[typeIndex].yOffset + actor->y, actor->z, D_807FD740[playerIndex].x, D_807FD740[playerIndex].y, D_807FD740[playerIndex].z);
                        while ((found == 0) && (node != NULL)) {
                            found = gGridTypeTable[typeIndex].radius + node->bounds.radius - 1.0f > camDistance3D(actor->x, gGridTypeTable[typeIndex].yOffset + actor->y, actor->z, node->bounds.x, node->bounds.y, node->bounds.z);
                            node = node->next;
                        }
                        if ((actor->state == 0x64) || (found != 0)) {
                            if ((gGlobalOverlayFlags & 0x10000) && (actorTypeIsRespawnPickup(actor->actorType) != 0)) {
                                delayedSpawnQueueAddActor(actor->actorType, 0x258, actor->x, actor->y, actor->z);
                            }
                            pickupState = actor->customState;
                            if (pickupState->collectable != 0) {
                                if (gPlayerCount >= 2) {
                                    switch (actor->actorType) {
                                    case 0x7A:
                                        playerStateHandleSoundEffects(0x1D2, playerIndex);
                                        gridCollectItem(playerIndex, 0x1D2, 0);
                                        break;
                                    case 0x79:
                                        playerStateHandleSoundEffects(0x8E, playerIndex);
                                        playerState->unk264 = 0;
                                        break;
                                    case 0x2F:
                                        playerStateHandleSoundEffects(0x57, playerIndex);
                                        gridCollectItem(playerIndex, 0x57, 0);
                                        break;
                                    case 0x77:
                                        playerStateHandleSoundEffects(0x1D0, playerIndex);
                                        playerState->unk264 = 1;
                                        break;
                                    case 0x78:
                                        playerStateHandleSoundEffects(0x1CF, playerIndex);
                                        playerState->unk264 = 2;
                                        break;
                                    case 0x33:
                                        playerStateHandleSoundEffects(0x8F, playerIndex);
                                        if (mpIsMatchType(0) != 0) {
                                            ps = player->customState;
                                            if (ps->gunDrawn == 0) {
                                                playerKongDrawGun(player);
                                                playerResumeLocomotion(player);
                                            }
                                        }
                                        break;
                                    case 0x34:
                                        playerStateHandleSoundEffects(0x56, playerIndex);
                                        playerState->unk264 = 3;
                                        break;
                                    case 0x76:
                                        playerStateHandleSoundEffects(0x1D1, playerIndex);
                                        playerState->unk264 = 4;
                                        break;
                                    }
                                } else {
                                    switch (actor->actorType) {
                                    case 0x2F:
                                    case 0x48:
                                    case 0x56:
                                        isGlobal = 1;
                                        break;
                                    default:
                                        isGlobal = 0;
                                        break;
                                    }
                                    modelSlot = modelSlotAppend(gGridTypeTable[typeIndex].modelType, actor->x, pickupModelYOffset(actor->actorType) + actor->y, actor->z, 0.0f, 0);
                                    tableIndex = csModelSlotGetTableIndex(modelSlot);
                                    flagTempRegister(gCurrentLevelIndex, tableIndex, pickupState->flagId, flagLookupValueById(pickupState->flagId));
                                    tableIndex = csModelSlotGetTableIndex(modelSlot);
                                    modelFlagsApplyState(gCurrentLevelIndex, tableIndex, &gModelSlots[hashTableLookup(modelSlot)].unk8C);
                                    gridAddModelNode(modelSlot, gGridTypeTable[typeIndex].modelType, 0, 1, 0, isGlobal);
                                    actor->parentActor = NULL;
                                }
                                actorDespawn(actor);
                            }
                        }
                    }
                }
            }
        }
    }
}

extern Actor *gPrimaryPlayerActor;
extern u8 D_80745838;


void playerStateHandleSoundEffects(s16 modelType, u8 playerIndex) {
    f32 y;
    s32 callback;

    switch (modelType) {
    case 0x8E:
        sfxAllocateChannel(0x23, 1.0 - D_80745838 * 0.3);
        break;
    case 0x57:
        sfxAllocateChannel(0x21, 1.0 - D_80745838 * 0.3);
        break;
    case 0x56:
        sfxPlayOnFreeSlot(0x147, 0x7FFF, 63.0f, 1.0f, 5, 0);
        break;
    case 0x11:
    case 0x8F:
        sfxPlayOnFreeSlot(0x157, 0x7FFF, 63.0f, 1.0f, 5, 0);
        break;
    case 0x98:
        sfxPlayOnFreeSlot(0x263, 0x7FFF, 63.0f, 1.0f, 5, 0);
        break;
    case 0xDD:
    case 0xDE:
    case 0xDF:
    case 0xE0:
    case 0xE1:
        sfxAllocateChannel(0x45, 1.0f);
        break;
    case 0x90:
        sfxAllocateChannel(0x12, 1.0f);
        effectShowBananaMedalIcon();
        y = gPrimaryPlayerActor->y;
        if (((y - gPrimaryPlayerActor->floorY) < 100.0f) && (gPrimaryPlayerActor->state != 0x63) && (!(gPrimaryPlayerActor->contactFlags & 4) || !((gPrimaryPlayerActor->waterY - y) > 20.0f))) {
            playerStateQueueCallback(0x29, NULL, gActivePlayerState->playerIndex);
        }
        break;
    case 0x74:
    case 0x288:
        sfxAllocateChannel(0x12, 1.0f);
        y = gPrimaryPlayerActor->y;
        if (((y - gPrimaryPlayerActor->floorY) < 100.0f) && (gPrimaryPlayerActor->state != 0x63) && (!(gPrimaryPlayerActor->contactFlags & 4) || !((gPrimaryPlayerActor->waterY - y) > 20.0f))) {
            playerStateQueueCallback(0x29, NULL, gActivePlayerState->playerIndex);
        }
        break;
    case 0xA:
    case 0xD:
    case 0x16:
    case 0x1E:
    case 0x1F:
    case 0x1CF:
    case 0x1D0:
        sfxPlayOnFreeSlot(0x2A0, 0x7FFF, 63.0f, 1.0f, 5, 0);
        break;
    case 0x1C:
    case 0x1D:
    case 0x23:
    case 0x24:
    case 0x27:
        sfxAllocateChannel(0x17, 1.0 - D_80745838 * 0.3);
        break;
    case 0x2B:
        break;
    case 0xB7:
        sfxAllocateChannel(0x91, 1.0 - D_80745838 * 0.3);
        break;
    case 0xEC:
    case 0x1D2:
        sfxAllocateChannel(0x20, 1.0 - D_80745838 * 0.3);
        break;
    case 0x13C:
        sfxAllocateChannel(0x12, 1.0f);
        callback = 0x41;
        if (gCurrentMap == 0x11) {
            callback = 0x29;
        }
        playerStateQueueCallback(callback, NULL, gActivePlayerState->playerIndex);
        break;
    case 0x18D:
        sfxAllocateChannel(0x12, 1.0f);
        playerStateQueueCallback(0x42, NULL, gActivePlayerState->playerIndex);
        effectShowCrownIcon();
        break;
    case 0x1D1:
        sfxPlayOnFreeSlot(0xAE, 0x7FFF, 63.0f, 1.0f, 5, 0);
        break;
    }
}
