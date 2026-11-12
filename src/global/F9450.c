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
extern u8 gPlayerCharacterId[];

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

// Collectable model node in a grid cell list (D_80754244[cell]) or the global list D_807FD72C.
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

// D_80753EF0: 0x2A collectable model types.
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
    s16 unkE;
    s32 timer;
} DelayedSpawn; // size = 0x14

extern PlayerInventory gPlayerInventoryTable[];

void gridRebuildNodeLists(void) {
    gridFreeAllNodeLists();
    gridBuildNodeLists();
}

extern GridBounds D_807FD740[];
extern GridBoundsNode *D_807FD780[];

typedef struct {
    u8 pad0[0x28];
    u16 modelType;
    s16 id;
    u8 pad2C[4];
} ModelAssetEntry;

extern GridTypeEntry D_80753EF0[];
extern GridNode **D_80754244;
extern DelayedSpawn *D_80754240;
extern u16 D_807F9450;
extern u16 D_807F9452;
extern u16 D_807F9454;
extern u16 D_807F9456;
extern s32 gGlobalOverlayFlags;
extern s16 D_807FD720;
extern s16 D_807FD722;
extern s16 D_807FD724;
extern s16 D_807FD726;
extern s16 D_807FD728;
extern GridNode *D_807FD72C;
extern GridActiveNode *D_807FD730;
extern u8 D_807FD738;
extern u8 D_807FD798;

void gridBuildNodeLists(void) {
    s32 cookie;
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
    ModelAssetEntry *pad;
    s32 idx;
    u8 *asset;
    u8 *sub;
    u8 *unusedOut;
    s32 entryCount;
    ModelAssetEntry *entries;
    u16 baseCount;
    u16 count;
    s16 entryId;
    s16 pad66;

    tail = NULL;
    head = NULL;
    entryCount = 0;
    D_807FD738 = 0;
    if (gGlobalOverlayFlags & 0x10000) {
        D_80754240 = heapAlloc(0x4B0);
        heapClearBlock(D_80754240);
    } else {
        D_80754240 = NULL;
    }
    baseCount = modelTypeCountBeforeMap(gCurrentMap);
    asset = assetLoad(9, gCurrentMap, 1, 1);
    if (asset != NULL) {
        modelAssetGetSubtables(asset, &sub, &unusedOut);
        entryCount = *(s32 *) sub;
        entries = (ModelAssetEntry *) (sub + 4);
    }
    D_807FD726 = 0;
    D_807FD728 = 0;
    D_807FD730 = NULL;
    D_807FD72C = NULL;
    for (i = 0; i < gPlayerCount; i++) {
        D_807FD740[i].x = 0.0f;
        D_807FD740[i].y = 0.0f;
        D_807FD740[i].z = 0.0f;
        D_807FD740[i].radius = 0.0f;
        D_807FD780[i] = NULL;
    }
    D_807FD798 = 0;
    slotQueueInit(1);
    typeEntry = D_80753EF0;
    for (i = 0; i < 0x2AU; i++) {
        type = typeEntry->modelType;
        cookie = 0;
        while (modelSlotFindByType(type, &cookie, &posX, &posY, &posZ, &modelId, &entryId) != 0) {
            node = heapAlloc(0x1C);
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
                    if (entryId == entries[idx].id) {
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
    D_80754244 = heapAlloc(D_807FD720 * 4);
    cellIdx = 0;
    for (zi = 0; zi < D_807FD724; zi++) {
        for (xi = 0; xi < D_807FD722; xi++) {
            D_80754244[cellIdx] = NULL;
            tail = NULL;
            for (node = head; node != NULL; node = node->next) {
                if (node->x >= (s16) (xi * 500) && node->x < (s16) (xi * 500 + 500)) {
                    zMin = zi * 500;
                    if (node->z >= zMin && node->z < (s16) (zi * 500 + 500)) {
                        copy = heapAlloc(0x1C);
                        memcpy(copy, node, 0x1C);
                        copy->next = NULL;
                        if (tail != NULL) {
                            tail->next = copy;
                        } else {
                            D_80754244[cellIdx] = copy;
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
    *link = heapAlloc(0x14);
    heapClearBlock(*link);
    (*link)->bounds.x = x;
    (*link)->bounds.y = y;
    (*link)->bounds.z = z;
    (*link)->bounds.radius = radius;
    heapFreeDeferred(*link);
}


s32 gridIsSpecialActorType(s16 modelType) {
    GridTypeEntry *entry;
    s32 found;
    s32 index;

    index = 0;
    found = 0;
    entry = D_80753EF0;
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

    gridX = (s32) (x / 500.0f);
    gridZ = (s32) (z / 500.0f);
    if ((D_807FD722 < gridX) || (D_807FD724 < gridZ) || (x < 0.0f) || (z < 0.0f)) {
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
        node = D_80754244[i];
        while (node != NULL && modelSlot != node->modelSlot) {
            prev = node;
            node = node->next;
        }
        if (node != NULL && modelSlot == node->modelSlot) {
            found = 1;
            if (prev != NULL) {
                prev->next = node->next;
            } else {
                D_80754244[i] = node->next;
            }
        }
        i++;
    }
    idx = gridCoordsToIndex(x, z);
    if (D_807FD720 >= idx && idx >= 0) {
        node->next = D_80754244[idx];
        D_80754244[idx] = node;
        node->x = (s16) x;
        node->y = (s16) y;
        node->z = (s16) z;
    }
}

void gridAddModelNode(s16 modelSlot, s16 modelType, s16 delay, u8 playSound, u8 collisionOverride, u8 isGlobal) {
    GridNode *node;
    f32 x;
    f32 y;
    f32 z;
    f32 u54;
    f32 u50;
    f32 u4C;
    f32 u48;
    f32 u44;
    s32 idx;
    s32 type;
    GridNode **tail;
    GridNode *cur;

    modelSlotGetTransformVectors(modelSlot, &x, &y, &z, &u54, &u50, &u4C, &u48, &u44, 1);
    if (isGlobal || ((D_807FD720 >= (idx = gridCoordsToIndex(x, z))) && (idx >= 0))) {
        node = heapAlloc(0x1C);
        node->x = (s16) x;
        node->y = (s16) y;
        node->z = (s16) z;
        node->modelSlot = modelSlot;
        type = gridIsSpecialActorType(modelType);
        node->requiredActorType = D_80753EF0[type].requiredActorType;
        node->modelType = modelType;
        node->collected = 0;
        node->delay = delay;
        node->playSound = playSound;
        node->flagIndex = -1;
        node->collisionOverride = collisionOverride;
        node->typeIndex = type;
        node->next = NULL;
        if (isGlobal) {
            tail = &D_807FD72C;
            cur = D_807FD72C;
        } else {
            cur = D_80754244[idx];
            tail = &D_80754244[idx];
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

    if (D_80754244 != NULL) {
        for (cell = 0; cell < D_807FD720; cell++) {
            node = D_80754244[cell];
            while (node != NULL) {
                next = node->next;
                heapFree(node);
                node = next;
            }
        }
        heapFree(D_80754244);
        D_80754244 = NULL;
    }
    node = D_807FD72C;
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
        func_806F54E0(0, node->modelType, node->collisionOverride);
        modelSlotFreeByIndex(node->modelSlot, 1);
        heapFree(node);
        node = next;
    }
    D_807FD730 = NULL;
}

GridActiveNode *func_806F53EC(GridNode *src) {
    GridActiveNode *node;

    node = heapAlloc(0x20);
    node->started = 0;
    node->progress = 0.0f;
    node->modelSlot = src->modelSlot;
    node->delay = src->delay;
    node->modelType = src->modelType;
    node->playSound = src->playSound;
    node->collisionOverride = src->collisionOverride;
    return node;
}

s32 gridAdjustActorCollisionType(s32 slot, s32 modelType, u8 override) {
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

void func_806F54E0(u8 playerIndex, s32 modelType, u8 collisionOverride) {
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
        entry = &D_80753EF0[gridIsSpecialActorType(modelType)];
        slot = gridAdjustActorCollisionType(entry->queueSlot, modelType, collisionOverride);
        switch (modelType) {
        case 0xDD: case 0xDE: case 0xDF: case 0xE0: case 0xE1:
            flagSet((s16) flagGridIndex(0x1D5, mapGetHubWorldIndex(gCurrentWorldId, 1), gPlayerCharacterId[playerIndex]), 1, 0);
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
                gPlayerInventoryTable[playerIndex].kong[i].unk6 += 5;
            }
            cutsceneStartFlag16CPath();
            break;
        case 0x8E:
            slotQueueAddValue(slot, playerIndex, 0x96);
            break;
        case 0x57:
            func_806C9974(playerIndex, 1);
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

void func_806F58A0(u8 playerIndex, s16 modelSlot, Actor *player) {
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
            func_806F54E0(playerIndex, modelType, 0);
        }
        delay += 3;
    }
}

void func_806F5A48(u8 playerIndex, s16 modelSlot, Actor *player, u16 parentType) {
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
            func_806F54E0(playerIndex, modelType, (parentType == 0x11) ? 1 : 0);
        }
        delay += 3;
    }
}

extern s32 D_80754248[];

s32 actorTypeIsRespawnPickup(s32 actorType) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (actorType == D_80754248[i]) {
            return 1;
        }
    }
    return 0;
}

extern s32 D_80754264[];

s32 func_806F5CE4(s32 actorType) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (actorType == D_80754264[i]) {
            return 1;
        }
    }
    return 0;
}


void func_806F5D80(s32 *actorType, s32 *delay) {
    *actorType = D_80754248[((u32) (randomNonNegative() >> 0xF) % 7U)];
    *delay = ((s32) (randomNonNegative() >> 0xF) % 32767 % 391) + 0xD2;
}

void delayedSpawnQueueAdd(s32 type, s32 isActor, s16 x, s16 y, s16 z, s32 delay) {
    s32 i;
    s32 found;

    found = 0;
    for (i = 0; i < 60 && !found; i++) {
        if (D_80754240[i].timer == 0) {
            D_80754240[i].isActor = isActor;
            D_80754240[i].type = type;
            D_80754240[i].x = x;
            D_80754240[i].y = y;
            D_80754240[i].z = z;
            D_80754240[i].timer = delay;
            found = 1;
        }
    }
}

s32 delayedSpawnQueueContains(s32 type, s32 isActor, s16 x, s16 y, s16 z) {
    s32 i;
    s32 found;

    found = 0;
    for (i = 0; i < 60 && !found; i++) {
        if (D_80754240[i].timer != 0 && type == D_80754240[i].type && isActor == D_80754240[i].isActor) {
            found = 1;
        }
    }
    return found;
}


void func_806F5F2C(s32 type, s32 delay, s16 x, s16 y, s16 z) {
    if ((func_80714608(0) != 0) && (actorTypeIsRespawnPickup(type) != 0)) {
        func_806F5D80(&type, &delay);
    }
    delayedSpawnQueueAdd(type, 1, x, y, z, delay);
}

void func_806F5FA0(s16 x, s16 y, s16 z) {
    func_806F5F2C(0x76, 0, x, y, z);
}


void func_806F5FE8(s32 type, s16 x, s16 y, s16 z, s32 delay) {
    if (func_806F5CE4(type) != 0) {
        delayedSpawnQueueAdd(type, 0, x, y, z, delay);
    }
}


void delayedSpawnQueueTick(void) {
    s32 i;

    if (menuIsTransitionType6() != 0) {
        if (!(gGlobalPauseFlags & 2)) {
            for (i = 0; i < 60; i++) {
                if (D_80754240[i].timer != 0) {
                    D_80754240[i].timer--;
                    if (D_80754240[i].timer == 5) {
                        effectSpawnParticleRingAtPosition((f32) D_80754240[i].x, (f32) D_80754240[i].y, (f32) D_80754240[i].z, 7);
                    }
                    if (D_80754240[i].timer == 0) {
                        if (D_80754240[i].isActor != 0) {
                            actorSpawnNodeEntryScaled((s16) D_80754240[i].type, (f32) D_80754240[i].x, (f32) D_80754240[i].y, (f32) D_80754240[i].z, 0, 0x19, -1, 0);
                        } else {
                            gridAddModelNode(modelSlotAppend(D_80754240[i].type, (f32) D_80754240[i].x, (f32) D_80754240[i].y, (f32) D_80754240[i].z, 0.0f, 0), (s16) D_80754240[i].type, 0, 1, 0, 0);
                        }
                    }
                }
            }
        }
    }
}

extern GridActiveNode *D_807FD734;

void func_806F6204(GridNode *node, u8 playerIndex, GridBounds *bounds) {
    Actor *player;
    s32 dist;
    GridActiveNode *newNode;
    GridActiveNode *tail;

    player = gPlayerSlots[playerIndex].actor;
    while (node != NULL) {
        dist = camDistance3D(node->x, D_80753EF0[node->typeIndex].yOffset + node->y, node->z, (s32) bounds->x, (s32) bounds->y, (s32) bounds->z);
        if ((node->collected == 0) &&
            ((f32) dist < (f32) D_80753EF0[node->typeIndex].radius + bounds->radius) &&
            ((node->requiredActorType == 0) || (player->actorType == node->requiredActorType)) &&
            (func_8063C2A8(node->modelSlot) != 0) &&
            (gridCheckNodeCondition(node->modelSlot, playerIndex, (u16) node->modelType) != 0)) {
            node->collected = 1;
            modelSlotFreeNestedBuffer(node->modelSlot, 1);
            if (node->flagIndex != -1) {
                func_8060E430((u16) node->flagIndex, 1, mapGetHubWorldIndex(gCurrentWorldId, 1));
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
                newNode = func_806F53EC(node);
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
                func_806F58A0(playerIndex, node->modelSlot, player);
                break;
            case 0x11:
            case 0x8F:
                func_806F5A48(playerIndex, node->modelSlot, player, (u16) node->modelType);
                break;
            default:
                if (gPlayerCount >= 2) {
                    func_806F54E0(playerIndex, node->modelType, node->collisionOverride);
                }
                break;
            }
            if (gPlayerCount >= 2) {
                playerStateHandleSoundEffects(node->modelType, playerIndex);
                modelSlotFreeByIndex(node->modelSlot, 1);
            }
            if (gGlobalOverlayFlags & 0x10000) {
                if (node->modelType != 0x1D2) {
                    func_806F5FE8(node->modelType, node->x, node->y, node->z, 0x258);
                }
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
        if (x <= ((f32) D_807FD726 + radius)) {
            z = bounds->z;
            if (z <= ((f32) D_807FD728 + radius)) {
                cell = gridCoordsToIndex(x, z);
                if (cell >= 0) {
                    func_806F6204(D_80754244[cell], playerIndex, bounds);
                }
            }
        }
        func_806F6204(D_807FD72C, playerIndex, bounds);
    }
}

extern ModelSlot *gModelSlots;

s32 gridCheckNodeCondition(s16 modelSlot, u8 playerIndex, u16 modelType) {
    u8 flags;
    PlayerState *playerState;
    ModelSlot *slot;

    switch (modelType) {
    case 0x11:
        if ((gPlayerInventoryTable[gCurrentPlayerIndex].kong[gPlayerCharacterId[gCurrentPlayerIndex]].unk0[2] & 3) != 3) {
            return 0;
        }
        break;
    case 0x8F:
        if ((gPlayerInventoryTable[gCurrentPlayerIndex].kong[gPlayerCharacterId[gCurrentPlayerIndex]].unk0[2] & 1) == 0) {
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
void guMtxL2F(f32 (*)[4], Mtx *);
void guMtxXFML(Mtx *, f32, f32, f32, f32 *, f32 *, f32 *);
void guMtxXFMF(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);

void gridUpdatePlayerNodes(u8 playerIndex) {
    GridBoundsNode *rect;
    GridActiveNode *node;
    GridActiveNode *prev;
    GridActiveNode *next;
    GridTypeEntry *type;
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
    f32 v3;
    f32 v4;
    f32 v5;
    f32 v6;
    f32 v7;
    s32 padC[3];
    Mtx *mtx;
    f32 pz;
    f32 py;
    f32 px;
    s16 tbl;
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
                idx = gridIsSpecialActorType(node->modelType);
                slot = D_80753EF0[idx].queueSlot;
                if (node->started == 0) {
                    modelSlotGetTransformVectors(node->modelSlot, &vx, &vy, &vz, &v3, &v4, &v5, &v6, &v7, 1);
                    guMtxXFML(mtx, vx, vy, vz, &node->startX, &node->startY, &node->startZ);
                    node->started = 1;
                    func_806398E4(node->modelSlot, 1, 0);
                    if (node->playSound != 0) {
                        playerStateHandleSoundEffects(node->modelType, playerIndex);
                    }
                    if ((slot >= 0) && !(gGlobalOverlayFlags & 0x4000) && ((slot != 0xB) || !(gGlobalOverlayFlags & 0x10000000))) {
                        slotQueueUpdate(gridAdjustActorCollisionType(slot, node->modelType, node->collisionOverride), 0, 0);
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
                        tbl = csModelSlotGetTableIndex(node->modelSlot);
                        D_807FD790[D_807FD798] = tbl;
                        D_807FD798 += 1;
                        flagSetForMapObject(gCurrentLevelIndex, tbl);
                    }
                }
                slotQueueGetPosition(slot, &px, &py, &pz);
                fx = ((px - node->startX) * node->progress) + node->startX;
                fy = ((py - node->startY) * node->progress) + node->startY;
                fz = ((pz - node->startZ) * node->progress) + node->startZ;
                guMtxXFMF(inv, fx, fy, fz, &outX, &outY, &outZ);
                next = node->next;
                type = &D_80753EF0[idx];
                node->progress += type->speed;
                if ((type->limit < node->progress) || (type->queueSlot == -2)) {
                    func_806F54E0(playerIndex, node->modelType, node->collisionOverride);
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

extern u8 D_80754238[];

s32 func_806F6E58(s16 kong) {
    u8 result;

    result = 0;
    if (kong < 5) {
        result = gPlayerInventoryTable[0].kong[kong].unk0[0] >= D_80754238[kong];
    }
    result |= flagGet(0x179, 0);
    return result;
}

s32 func_806F6EDC(void) {
    s32 i;
    u8 r;

    i = 0;
    do {
        r = func_806F6E58(i);
        i++;
    } while (i < 5 && r == 0);
    return r;
}

void gridTickPlayers(void) {
    s16 globalFlagSet;
    u8 kongDone;
    u8 i;
    PlayerState *ps;

    globalFlagSet = 0;
    kongDone = 0;
    if (gGlobalOverlayFlags & 0x10000) {
        delayedSpawnQueueTick();
    }
    if (flagGet(0x179, 0) != 0) {
        globalFlagSet = 1;
    }
    if (func_806F6E58(gPlayerCharacterId[0]) != 0) {
        kongDone = 1;
    }

    for (i = 0; i < gPlayerCount; i++) {
        ps = gPlayerSlots[i].actor->customState;
        if (globalFlagSet != 0) {
            ps->stateFlags2 |= 1;
        } else {
            ps->stateFlags2 &= -2;
        }
        if (kongDone) {
            ps->stateFlags2 |= 2;
        } else {
            ps->stateFlags2 &= -3;
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
    effectSetCallback(func_8071C48C);
    effectSetDepth(1);
    effectCreateAtPosition(&D_8071FC58, scale, x, y, z);
    half = 1000.0 / ((f64)spread + (f64)spread);
    for (i = 0; i < count; i++) {
        dx = (f32)((f64)((f32)(randomLcgNext() / 10000U % 1000U) / spread) - half);
        dy = (f32)((f64)((f32)(randomLcgNext() / 10000U % 1000U) / spread) - half);
        dz = (f32)((f64)((f32)(randomLcgNext() / 10000U % 1000U) / spread) - half);
        effectSetCallback(func_8071C620);
        effectSetAngle(i + 1);
        effectSetDepth(1);
        effectCreateAtPosition(&D_8071FC58, scale, x + dx, y + dy, z + dz);
    }
}


f32 func_806F7378(u32 actorType) {
    if (actorType == 0x8C) {
        return -13.0f;
    }
    return 0.0f;
}


// customState of a collectable pickup actor.
typedef struct PickupState {
    u8 pad0;
    u8 unk1;
    u8 pad2[8];
    s16 unkA;
} PickupState;

extern u16 gActiveActorCount;
extern ActorEntry gActiveActors[];


void gridCollectActorsInRange(u8 playerIndex) {
    Actor *player;
    s32 i;
    PlayerState *playerSub;
    Actor *actor;
    PickupState *sub;
    GridBoundsNode *node;
    s32 found;
    s32 flag;
    PlayerState *ps;
    s32 k;
    s16 slot;
    s16 tblIdx;

    player = gPlayerSlots[playerIndex].actor;
    playerSub = player->customState;
    if (gPlayerInventoryTable[playerIndex].health > 0) {
        for (k = 0; k < 0x2A; k++) {
            if (D_80753EF0[k].actorType != 0) {
                for (i = 0; i < gActiveActorCount; i++) {
                    actor = gActiveActors[i].actor;
                    if ((gGlobalPauseFlags & 0x10000) && (D_80753EF0[k].actorType == actor->actorType) && ((D_80753EF0[k].requiredActorType == 0) || (D_80753EF0[k].requiredActorType == player->actorType))) {
                        node = D_807FD780[playerIndex];
                        found = D_80753EF0[k].radius + D_807FD740[playerIndex].radius - 1.0f > camDistance3D(actor->x, D_80753EF0[k].yOffset + actor->y, actor->z, D_807FD740[playerIndex].x, D_807FD740[playerIndex].y, D_807FD740[playerIndex].z);
                        while ((found == 0) && (node != NULL)) {
                            found = D_80753EF0[k].radius + node->bounds.radius - 1.0f > camDistance3D(actor->x, D_80753EF0[k].yOffset + actor->y, actor->z, node->bounds.x, node->bounds.y, node->bounds.z);
                            node = node->next;
                        }
                        if ((actor->state == 0x64) || (found != 0)) {
                            if ((gGlobalOverlayFlags & 0x10000) && (actorTypeIsRespawnPickup(actor->actorType) != 0)) {
                                func_806F5F2C(actor->actorType, 0x258, actor->x, actor->y, actor->z);
                            }
                            sub = actor->customState;
                            if (sub->unk1 != 0) {
                                if (gPlayerCount >= 2) {
                                    switch (actor->actorType) {
                                    case 0x7A:
                                        playerStateHandleSoundEffects(0x1D2, playerIndex);
                                        func_806F54E0(playerIndex, 0x1D2, 0);
                                        break;
                                    case 0x79:
                                        playerStateHandleSoundEffects(0x8E, playerIndex);
                                        playerSub->unk264 = 0;
                                        break;
                                    case 0x2F:
                                        playerStateHandleSoundEffects(0x57, playerIndex);
                                        func_806F54E0(playerIndex, 0x57, 0);
                                        break;
                                    case 0x77:
                                        playerStateHandleSoundEffects(0x1D0, playerIndex);
                                        playerSub->unk264 = 1;
                                        break;
                                    case 0x78:
                                        playerStateHandleSoundEffects(0x1CF, playerIndex);
                                        playerSub->unk264 = 2;
                                        break;
                                    case 0x33:
                                        playerStateHandleSoundEffects(0x8F, playerIndex);
                                        if (func_80714608(0) != 0) {
                                            ps = player->customState;
                                            if (ps->gunDrawn == 0) {
                                                playerKongPlaySoundByState(player);
                                                playerResumeLocomotion(player);
                                            }
                                        }
                                        break;
                                    case 0x34:
                                        playerStateHandleSoundEffects(0x56, playerIndex);
                                        playerSub->unk264 = 3;
                                        break;
                                    case 0x76:
                                        playerStateHandleSoundEffects(0x1D1, playerIndex);
                                        playerSub->unk264 = 4;
                                        break;
                                    }
                                } else {
                                    switch (actor->actorType) {
                                    case 0x2F:
                                    case 0x48:
                                    case 0x56:
                                        flag = 1;
                                        break;
                                    default:
                                        flag = 0;
                                        break;
                                    }
                                    slot = modelSlotAppend(D_80753EF0[k].modelType, actor->x, func_806F7378(actor->actorType) + actor->y, actor->z, 0.0f, 0);
                                    tblIdx = csModelSlotGetTableIndex(slot);
                                    flagTempRegister(gCurrentLevelIndex, tblIdx, sub->unkA, flagLookupValueById(sub->unkA));
                                    tblIdx = csModelSlotGetTableIndex(slot);
                                    modelFlagsApplyState(gCurrentLevelIndex, tblIdx, &gModelSlots[hashTableLookup(slot)].unk8C);
                                    gridAddModelNode(slot, D_80753EF0[k].modelType, 0, 1, 0, flag);
                                    actor->parentActor = 0;
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
        sfxAllocateChannel(0x23, (f32) (1.0 - ((f64) D_80745838 * 0.3)));
        return;
    case 0x57:
        sfxAllocateChannel(0x21, (f32) (1.0 - ((f64) D_80745838 * 0.3)));
        return;
    case 0x56:
        sfxPlayOnFreeSlot(0x147, 0x7FFF, 63.0f, 1.0f, 5, 0);
        return;
    case 0x11:
    case 0x8F:
        sfxPlayOnFreeSlot(0x157, 0x7FFF, 63.0f, 1.0f, 5, 0);
        return;
    case 0x98:
        sfxPlayOnFreeSlot(0x263, 0x7FFF, 63.0f, 1.0f, 5, 0);
        return;
    case 0xDD:
    case 0xDE:
    case 0xDF:
    case 0xE0:
    case 0xE1:
        sfxAllocateChannel(0x45, 1.0f);
        return;
    case 0x90:
        sfxAllocateChannel(0x12, 1.0f);
        func_80687C48();
        y = gPrimaryPlayerActor->y;
        if (((y - gPrimaryPlayerActor->floorY) < 100.0f) && (gPrimaryPlayerActor->state != 0x63) && (!(gPrimaryPlayerActor->contactFlags & 4) || !((gPrimaryPlayerActor->waterY - y) > 20.0f))) {
            playerStateQueueCallback(0x29, 0, gActivePlayerState->playerIndex);
            return;
        }
        return;
    case 0x74:
    case 0x288:
        sfxAllocateChannel(0x12, 1.0f);
        y = gPrimaryPlayerActor->y;
        if (((y - gPrimaryPlayerActor->floorY) < 100.0f) && (gPrimaryPlayerActor->state != 0x63) && (!(gPrimaryPlayerActor->contactFlags & 4) || !((gPrimaryPlayerActor->waterY - y) > 20.0f))) {
            playerStateQueueCallback(0x29, 0, gActivePlayerState->playerIndex);
            return;
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
        return;
    case 0x1C:
    case 0x1D:
    case 0x23:
    case 0x24:
    case 0x27:
        sfxAllocateChannel(0x17, (f32) (1.0 - ((f64) D_80745838 * 0.3)));
        return;
    case 0x2B:
        break;
    case 0xB7:
        sfxAllocateChannel(0x91, (f32) (1.0 - ((f64) D_80745838 * 0.3)));
        return;
    case 0xEC:
    case 0x1D2:
        sfxAllocateChannel(0x20, (f32) (1.0 - ((f64) D_80745838 * 0.3)));
        return;
    case 0x13C:
        sfxAllocateChannel(0x12, 1.0f);
        callback = 0x41;
        if (gCurrentMap == 0x11) {
            callback = 0x29;
        }
        playerStateQueueCallback((s16) callback, 0, gActivePlayerState->playerIndex);
        return;
    case 0x18D:
        sfxAllocateChannel(0x12, 1.0f);
        playerStateQueueCallback(0x42, 0, gActivePlayerState->playerIndex);
        func_80687CC8();
        return;
    case 0x1D1:
        sfxPlayOnFreeSlot(0xAE, 0x7FFF, 63.0f, 1.0f, 5, 0);
        break;
    }
}
