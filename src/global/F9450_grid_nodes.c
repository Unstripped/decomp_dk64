#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "cutscene.h"
#include "sched.h"
#include "proto/global/104F0_eeprom.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2F550_map_render.h"
#include "proto/global/36880_model_slot.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/42630_cutscene_interp.h"
#include "proto/global/5E020_hash_table.h"
#include "proto/global/6AD90_collision.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/AA960_pickup_drops.h"
#include "proto/global/CC800_player_setup.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/F56F0_player_weapon.h"
#include "proto/global/F9450_grid_nodes.h"
#include "proto/global/FCCD0_slot_queue.h"

extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s32 gCurrentMap;

// A sphere the grid tests nodes against: the player's own (gGridPlayerBounds) and extra ones
// appended per player (gGridPlayerExtraBounds lists).
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

// Collected node flying to its queue slot (gGridActiveNodes list).
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
u8 gKongAbilityEnergyMoveLevel[8] = { 2, 2, 3, 1, 1, 0, 0, 0 }; // per-kong move level needed for ability energy
DelayedSpawn *gDelayedSpawnQueue = NULL;
GridNode **gGridCells = NULL;
s32 gRespawnPickupActorTypes[7] = { 0x34, 0x76, 0x33, 0x77, 0x78, 0x2F, 0x79 }; // respawn pickup actor types
s32 gRespawnPickupModelTypes[6] = { 0x56, 0x8F, 0x11, 0x1D2, 0x8E, 0x57 }; // respawn pickup model types

void gridRebuildNodeLists(void) {
    gridFreeAllNodeLists();
    gridBuildNodeLists();
}

extern GridBounds gGridPlayerBounds[];
extern GridBoundsNode *gGridPlayerExtraBounds[];

extern u16 gCollisionCellSizeX;
extern u16 gCollisionCellSizeZ;
extern u16 gCollisionCellsX;
extern u16 gCollisionCellsZ;
extern s16 gGridCellCount;
extern s16 gGridCellsX;
extern s16 gGridCellsZ;
extern s16 gGridMapWidth;
extern s16 gGridMapDepth;
extern GridNode *gGridGlobalNodes;
extern GridActiveNode *gGridActiveNodes;
extern u8 gGridNodesFreed;
extern u8 gCollectedTableIndexCount;

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
    gGridNodesFreed = 0;
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
    gGridMapWidth = 0;
    gGridMapDepth = 0;
    gGridActiveNodes = NULL;
    gGridGlobalNodes = NULL;
    for (i = 0; i < gPlayerCount; i++) {
        gGridPlayerBounds[i].x = 0.0f;
        gGridPlayerBounds[i].y = 0.0f;
        gGridPlayerBounds[i].z = 0.0f;
        gGridPlayerBounds[i].radius = 0.0f;
        gGridPlayerExtraBounds[i] = NULL;
    }
    gCollectedTableIndexCount = 0;
    slotQueueInit(1);
    typeEntry = gGridTypeTable;
    for (i = 0; i < sizeof(gGridTypeTable) / sizeof(gGridTypeTable[0]); i++) {
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
    gGridMapWidth = gCollisionCellSizeX * gCollisionCellsX;
    gGridMapDepth = gCollisionCellSizeZ * gCollisionCellsZ;
    gGridCellsX = gGridMapWidth / 500 + 1;
    gGridCellsZ = gGridMapDepth / 500 + 1;
    gGridCellCount = gGridCellsX * gGridCellsZ;
    gGridCells = heapAlloc(gGridCellCount * sizeof(GridNode *));
    cellIdx = 0;
    for (zi = 0; zi < gGridCellsZ; zi++) {
        for (xi = 0; xi < gGridCellsX; xi++) {
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
    gGridPlayerBounds[playerIndex].x = x;
    gGridPlayerBounds[playerIndex].y = y;
    gGridPlayerBounds[playerIndex].z = z;
    gGridPlayerBounds[playerIndex].radius = radius;
    gGridPlayerExtraBounds[playerIndex] = NULL;
}


void gridAppendPositionNode(u8 playerIndex, f32 x, f32 y, f32 z, f32 radius) {
    GridBoundsNode **link;

    link = &gGridPlayerExtraBounds[playerIndex];
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
    if ((gridX > gGridCellsX) || (gridZ > gGridCellsZ) || (x < 0.0f) || (z < 0.0f)) {
        return -1;
    }
    return (gGridCellsX * gridZ) + gridX;
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
    while (found == 0 && i < gGridCellCount) {
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
    if (idx <= gGridCellCount && idx >= 0) {
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
    if (isGlobal || (((idx = gridCoordsToIndex(x, z)) <= gGridCellCount) && (idx >= 0))) {
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
        for (cell = 0; cell < gGridCellCount; cell++) {
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
    if (gGridActiveNodes != NULL) {
        active = gGridActiveNodes;
        while (active != NULL) {
            nextActive = active->next;
            heapFree(active);
            active = nextActive;
        }
        gGridActiveNodes = NULL;
    }
    slotQueueReleaseAll();
}

void gridFreeAllActiveNodes(void) {
    GridActiveNode *node;
    GridActiveNode *next;

    gGridNodesFreed = 1;
    node = gGridActiveNodes;
    while (node != NULL) {
        next = node->next;
        gridCollectItem(0, node->modelType, node->collisionOverride);
        modelSlotFreeByIndex(node->modelSlot, 1);
        heapFree(node);
        node = next;
    }
    gGridActiveNodes = NULL;
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

    for (i = 0; i < sizeof(gRespawnPickupActorTypes) / sizeof(gRespawnPickupActorTypes[0]); i++) {
        if (actorType == gRespawnPickupActorTypes[i]) {
            return 1;
        }
    }
    return 0;
}

s32 modelTypeIsRespawnPickup(s32 modelType) {
    s32 i;

    for (i = 0; i < sizeof(gRespawnPickupModelTypes) / sizeof(gRespawnPickupModelTypes[0]); i++) {
        if (modelType == gRespawnPickupModelTypes[i]) {
            return 1;
        }
    }
    return 0;
}


void respawnPickRandomPickup(s32 *actorType, s32 *delay) {
    *actorType = gRespawnPickupActorTypes[(randomNonNegative() >> 0xF) % (sizeof(gRespawnPickupActorTypes) / sizeof(gRespawnPickupActorTypes[0]))];
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

extern GridActiveNode *gGridActiveNodesTail;

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
            (modelSlotIsAlphaVisible(node->modelSlot) != 0) &&
            (gridCheckNodeCondition(node->modelSlot, playerIndex, node->modelType) != 0)) {
            node->collected = 1;
            modelSlotFreeNestedBuffer(node->modelSlot, 1);
            if (node->flagIndex != -1) {
                eepromWriteChecksumBit(node->flagIndex, 1, mapGetHubWorldIndex(gCurrentWorldId, 1));
            }
            if (gPlayerCount == 1) {
                if (gGridActiveNodesTail == NULL) {
                    tail = gGridActiveNodes;
                    gGridActiveNodesTail = tail;
                    while (tail != NULL) {
                        gGridActiveNodesTail = tail;
                        tail = tail->next;
                    }
                }
                newNode = gridActiveNodeCreate(node);
                newNode->next = NULL;
                if (gGridActiveNodes != NULL) {
                    gGridActiveNodesTail->next = newNode;
                    gGridActiveNodesTail = newNode;
                } else {
                    gGridActiveNodes = newNode;
                    gGridActiveNodesTail = newNode;
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
        if (x <= gGridMapWidth + radius) {
            z = bounds->z;
            if (z <= gGridMapDepth + radius) {
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
        if (slot->csState->alpha != 0xFF) {
            return 0;
        }
        break;
    }
    flags = gModelSlots[hashTableLookup(modelSlot)].flags;
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

extern s16 gCollectedTableIndices[];
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

    gCollectedTableIndexCount = 0;
    gridCollectActorsInRange(playerIndex);
    gGridActiveNodesTail = NULL;
    gridDispatchRect(playerIndex, &gGridPlayerBounds[playerIndex]);
    rect = gGridPlayerExtraBounds[playerIndex];
    while (rect != NULL) {
        gridDispatchRect(playerIndex, &rect->bounds);
        rect = rect->next;
    }
    if ((gGridActiveNodes != NULL) && (gPlayerCount == 1)) {
        mtx = &gPlayerSlots[playerIndex].viewMtx[gGfxBufferIndex];
        guMtxL2F(mf, mtx);
        matrix4Invert(inv, mf);
        node = gGridActiveNodes;
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
                    modelSlotSetTranslucent(node->modelSlot, 1, 0);
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
                    if (gCollectedTableIndexCount != 4) {
                        tableIndex = csModelSlotGetTableIndex(node->modelSlot);
                        gCollectedTableIndices[gCollectedTableIndexCount] = tableIndex;
                        gCollectedTableIndexCount++;
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
                        gGridActiveNodes = node->next;
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
        result = gPlayerInventoryTable[0].kong[kong].moveLevel >= gKongAbilityEnergyMoveLevel[kong];
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
        if ((gPlayerSlots[i].actor->state != 0x36) && (gGridNodesFreed == 0)) {
            gridUpdatePlayerNodes(i);
        }
    }
}


s32 listContainsS16(s16 value) {
    s32 i;

    for (i = 0; i < gCollectedTableIndexCount; i++) {
        if (value == gCollectedTableIndices[i]) {
            return 1;
        }
    }
    return 0;
}


extern EffectGridAsset gEffectSpriteSparklePurple;

void effectSpawnRandomSpread(f32 x, f32 y, f32 z, f32 scale, f32 spread, s32 count) {
    f32 dx;
    f32 dy;
    f32 dz;
    f64 half;
    s32 i;

    effectSetSpeed(0x1006E);
    effectSetCallback(effectLightPulseTealUpdate);
    effectSetDepth(1);
    effectCreateAtPosition(&gEffectSpriteSparklePurple, scale, x, y, z);
    half = 1000.0 / ((f64) spread + (f64) spread);
    for (i = 0; i < count; i++) {
        dx = (randomLcgNext() / 10000U % 1000U) / spread - half;
        dy = (randomLcgNext() / 10000U % 1000U) / spread - half;
        dz = (randomLcgNext() / 10000U % 1000U) / spread - half;
        effectSetCallback(effectRandomDirectionDriftUpdate);
        effectSetStartDelay(i + 1);
        effectSetDepth(1);
        effectCreateAtPosition(&gEffectSpriteSparklePurple, scale, x + dx, y + dy, z + dz);
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
        for (typeIndex = 0; typeIndex < sizeof(gGridTypeTable) / sizeof(gGridTypeTable[0]); typeIndex++) {
            if (gGridTypeTable[typeIndex].actorType != 0) {
                for (i = 0; i < gActiveActorCount; i++) {
                    actor = gActiveActors[i].actor;
                    if ((gGlobalPauseFlags & 0x10000) && (gGridTypeTable[typeIndex].actorType == actor->actorType) && ((gGridTypeTable[typeIndex].requiredActorType == 0) || (gGridTypeTable[typeIndex].requiredActorType == player->actorType))) {
                        node = gGridPlayerExtraBounds[playerIndex];
                        found = gGridTypeTable[typeIndex].radius + gGridPlayerBounds[playerIndex].radius - 1.0f > camDistance3D(actor->x, gGridTypeTable[typeIndex].yOffset + actor->y, actor->z, gGridPlayerBounds[playerIndex].x, gGridPlayerBounds[playerIndex].y, gGridPlayerBounds[playerIndex].z);
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
                                        playerState->pendingPickupEffect = 0;
                                        break;
                                    case 0x2F:
                                        playerStateHandleSoundEffects(0x57, playerIndex);
                                        gridCollectItem(playerIndex, 0x57, 0);
                                        break;
                                    case 0x77:
                                        playerStateHandleSoundEffects(0x1D0, playerIndex);
                                        playerState->pendingPickupEffect = 1;
                                        break;
                                    case 0x78:
                                        playerStateHandleSoundEffects(0x1CF, playerIndex);
                                        playerState->pendingPickupEffect = 2;
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
                                        playerState->pendingPickupEffect = 3;
                                        break;
                                    case 0x76:
                                        playerStateHandleSoundEffects(0x1D1, playerIndex);
                                        playerState->pendingPickupEffect = 4;
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
                                    modelFlagsApplyState(gCurrentLevelIndex, tableIndex, &gModelSlots[hashTableLookup(modelSlot)].flags);
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
extern u8 gAudioUnderwater;


void playerStateHandleSoundEffects(s16 modelType, u8 playerIndex) {
    f32 y;
    s32 callback;

    switch (modelType) {
    case 0x8E:
        sfxAllocateChannel(0x23, 1.0 - gAudioUnderwater * 0.3);
        break;
    case 0x57:
        sfxAllocateChannel(0x21, 1.0 - gAudioUnderwater * 0.3);
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
        sfxAllocateChannel(0x17, 1.0 - gAudioUnderwater * 0.3);
        break;
    case 0x2B:
        break;
    case 0xB7:
        sfxAllocateChannel(0x91, 1.0 - gAudioUnderwater * 0.3);
        break;
    case 0xEC:
    case 0x1D2:
        sfxAllocateChannel(0x20, 1.0 - gAudioUnderwater * 0.3);
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
