#include "common.h"
#include "sched.h"
#include "actor.h"
#include "proto/global/117190.h"
#include "proto/global/135D30.h"
#include "proto/global/136820.h"
#include "proto/global/15050.h"
#include "proto/global/201B0.h"
#include "proto/global/36880.h"
#include "proto/global/3C10.h"
#include "proto/global/5E2F0.h"
#include "proto/global/7130.h"
#include "proto/global/8D3E0.h"
#include "proto/global/AA960.h"
#include "proto/global/CC800.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"

typedef struct {
    u8 inUse;
    u8 pad1;
    s16 flags;
    f32 x;
    f32 y;
    f32 z;
    s16 yaw;
    s16 map;
    u8 returnExitIndex;
    u8 *modelData;
    s32 recordSize;
    u8 *records;
    u8 rgb[52][3];
} Struct8076A160;

typedef struct {
    s32 map;
    s32 targetMap;
    s32 exitIndex;
} Struct807447A0;

typedef struct {
    s32 overlayFlags;
    s32 cutsceneFlags;
    s32 unk8;
} Struct8074482C;

typedef struct {
    u16 map;
    u16 targetMap;
    u8 exitIndex;
} Struct8074475C;

/* Extern variables */
extern u8 gGameMode;
extern u8 gNextGameMode;
extern s32 gInitialMap;
extern s32 gInitialExit;
extern u8 D_807445E0[];
extern u16 D_807446C0[];
extern s32 D_80744720[];
extern u16 D_80744734[];
extern u16 D_80744736[];
extern u16 D_80744748[];
extern Struct8074475C D_8074475C[11];
extern Struct807447A0 D_807447A0[];
extern u8 D_80744820;
extern u8 D_80744824;
extern u8 D_80744828;
extern Struct8074482C D_8074482C[];
extern u8 gPlayerCharacterId;
const u8 D_807565E0[80] = {
    0x01, 0x0F, 0x05, 0x19, 0x07, 0x1A, 0x1E, 0x30, 0x48, 0x57, 0x2A, 0x11, 0x26, 0x0A, 0x73, 0x74,
    0x75, 0x12, 0x76, 0x77, 0x78, 0x20, 0x79, 0x7A, 0x7B, 0x42, 0x44, 0x45, 0x7C, 0x43, 0x4A, 0x4B,
    0x7D, 0x7E, 0x7F, 0x80, 0x41, 0x4D, 0x81, 0x82, 0x4E, 0x4F, 0x83, 0x60, 0x84, 0x85, 0x63, 0x86,
    0x87, 0x68, 0x88, 0x89, 0x67, 0x8A, 0x8B, 0x8C, 0x65, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93,
    0x66, 0x94, 0x95, 0x96, 0x35, 0x49, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0x00, 0x00,
};
const u8 D_80756630[80] = {
    0x0A, 0x0B, 0x0C, 0x0D, 0x00, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0E, 0x08, 0x01, 0x0F, 0x0F, 0x0F,
    0x0F, 0x10, 0x10, 0x10, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13,
    0x13, 0x14, 0x14, 0x14, 0x14, 0x15, 0x15, 0x15, 0x16, 0x16, 0x16, 0x17, 0x17, 0x17, 0x18, 0x18,
    0x18, 0x19, 0x19, 0x19, 0x1A, 0x1A, 0x1A, 0x1A, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x1C, 0x1C, 0x1C,
    0x1D, 0x1D, 0x1D, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x27, 0x23, 0x24, 0x25, 0x22, 0x26, 0x00, 0x00,
};
extern s32 gCurrentMap;
extern u8 gCurrentWorldId;
extern u8 gScreenRenderFlags;
extern s8 D_8076A0B2;
extern s32 D_807F6010;
extern Actor *gPrimaryPlayerActor;
extern s32 gGlobalPauseFlags;
extern s32 gGlobalOverlayFlags;
extern s32 gGlobalCutsceneFlags;
extern u16 gLevelCollectibleCounts[];
extern f32 gScreenFadeRate;

/* Function declarations */

/* External functions */
void func_8002920C(void);
f32 mathCosF(s16);
f32 mathSinF(s16);

// .bss 0x8076A160-0x8076AF00
Struct8076A160 D_8076A160[18];
u8 D_8076AEE0;
u8 D_8076AEE1;
s16 D_8076AEE2;
f32 D_8076AEE4;
f32 D_8076AEE8;
f32 D_8076AEEC;
s16 D_8076AEF0;
s16 D_8076AEF2;
u16 D_8076AEF4;
u8 D_8076AEF6;
u8 D_8076AEF7;
u8 D_8076AEF8[8];

typedef struct {
    s32 key;
    s32 value;
} KeyValuePair;


extern KeyValuePair D_80744800[];

s32 func_805FEF10(s32 *outValue) {
    s32 i;
    s32 found;

    found = 0;
    for (i = 0; i < 4U && !found; i++) {
        found = gPrimaryPlayerActor->actorType == D_80744800[i].key;
        if (found) {
            *outValue = D_80744800[i].value;
        }
    }
    return found;
}

s32 func_805FEF74(s32 map) {
    s32 i;

    if (map == D_80744734[0]) {
        return 1;
    }
    for (i = 0; i < 8; i++) {
        if (map == D_80744736[i]) {
            return 1;
        }
    }
    return 0;
}

u8 mapGetWorldIndex(u8 map) {
    return D_807445E0[map];
}

s32 mapGetConfigValue(s32 unused, s32 index) {
    s32 value = D_80744720[index];
    return value;
}

u8 mapGetHubWorldIndex(u8 map, u8 checkBossMap) {
    u8 val;
    s32 targetMap;
    s32 exitIndex;
    s32 pad;

    targetMap = map;
    val = D_807445E0[targetMap];
    if (val == 0xD || val == 9) {
        if (mapFindPreviousSavedMap(&targetMap, &exitIndex)) {
            val = D_807445E0[targetMap];
        }
    }
    if (checkBossMap != 0) {
        if (func_805FEF74(targetMap)) {
            val = 7;
        }
    }
    return val;
}

u8 mapHasCollectedSufficientItems(void) {
    s32 index = mapGetHubWorldIndex(gCurrentWorldId, 0);
    return gLevelCollectibleCounts[index] >= D_807446C0[index];
}

void mapSlotArrayInit(void) {
    s32 i;
    for (i = 0; i < 18; i++) {
        D_8076A160[i].inUse = 0;
    }
}

void screenSetTransitionFadeType(u8 fadeType) {
    D_80744824 = fadeType;
}

void screenApplyTransitionFadeType(void) {
    D_8076AEE0 = D_80744824;
    D_80744824 = 1;
}

void mapSetPendingTransition(s16 map, u8 exitIndex) {
    D_80744828 = 1;
    D_8076AEF4 = map;
    D_8076AEF6 = exitIndex;
}

void mapExecuteDeathTransition(s32 unused) {
    u16 pad;
    u16 targetMap;
    s32 limit;
    s32 i;
    u16 exitIndex;
    u8 found;
    s32 world;

    limit = 11;
    i = 0;
    exitIndex = 0;
    found = 0;

    if (D_80744828 != 0) {
        targetMap = D_8076AEF4;
        exitIndex = D_8076AEF6;
    } else {
        if (func_805FEF74(gCurrentMap) != 0) {
            targetMap = gCurrentMap;
        } else {
            world = mapGetHubWorldIndex(gCurrentMap, 0);
            targetMap = D_80744748[world];
            for (; !found && (i < limit); i++) {
                if (gCurrentMap == D_8074475C[i].map) {
                    targetMap = D_8074475C[i].targetMap;
                    exitIndex = D_8074475C[i].exitIndex;
                    found = 1;
                }
            }
        }
    }
    if (!found) {
        mapSlotArrayResetAll();
    }
    mapRequestTransition(targetMap, exitIndex);
    D_80744828 = 0;
}

void mapExecuteVoidTransition(void) {
    s32 targetMap;
    s32 exitIndex;

    if (gCurrentMap != 0x22) {
        mapSlotArrayResetAll();
        targetMap = D_80744734[mapGetHubWorldIndex(gCurrentWorldId, 0)];
        exitIndex = 1;
    } else {
        targetMap = gCurrentMap;
        exitIndex = 0;
    }
    flagSet(0x6E, 1, 2);
    mapRequestTransition(targetMap, exitIndex);
}

void mapRequestTransition(s32 map, s32 exitIndex) {
    gridFreeAllActiveNodes();
    if ((gGameMode == 6) || (menuIsTransitionActive() == 0)) {
        menuCheckCutsceneTransition(&map, &exitIndex);
        if (map != -1) {
            if (gPlayerCharacterId >= 6) {
                gPlayerCharacterId = playerGetResolvedKongId(0);
            }
            gScreenRenderFlags |= 1;
            D_8076AEF2 = gCurrentMap;
            gInitialMap = map;
            gInitialExit = exitIndex;
            D_8076A0B2 = 3;
            screenApplyTransitionFadeType();
            gScreenFadeRate = 1.0f;
            if ((gNextGameMode != 1) && (D_8076AEE0 == 1) && !(gGlobalCutsceneFlags & 2) && (gCurrentMap != 0x4C)) {
                sfxAllocateChannel(0x2C, 1.0f);
            }
            flagTempsPruneUnloadedMaps();
            mapLoadSavedSlotSpawn(map);
            if (gGlobalOverlayFlags & 1) {
                func_8002920C();
            }
        }
    }
}

void mapRequestTransitionFast(s32 map, s32 exitIndex) {
    gridFreeAllActiveNodes();
    gGlobalPauseFlags |= 0x100;
    gInitialMap = map;
    gInitialExit = exitIndex;
    D_8076AEF2 = gCurrentMap;
    flagTempsPruneUnloadedMaps();
    mapLoadSavedSlotSpawn(map);
}

void mapCheckAutoTransition(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gCurrentMap == D_807447A0[i].map) {
            mapRequestTransition(D_807447A0[i].targetMap, D_807447A0[i].exitIndex);
            return;
        }
    }
}

void mapLoadSavedSlotSpawn(s32 map) {
    s32 idx = mapFindSlotIndex(map);

    if (idx != -1) {
        D_8076AEE2 = D_8076A160[idx].flags;
        D_8076AEE4 = D_8076A160[idx].x;
        D_8076AEE8 = D_8076A160[idx].y;
        D_8076AEEC = D_8076A160[idx].z;
        D_8076AEF0 = D_8076A160[idx].yaw;
    } else {
        D_8076AEE2 = 0;
    }
}

void mapTransitionExitCurrent(s32 map, s32 exitIndex) {
    mapSlotFree(gCurrentMap);
    mapRequestTransition(map, exitIndex);
}

void mapSetTransitionExtraCounter(u8 count) {
    D_80744820 = count;
}

void func_805FF670(void) {
    f32 dist;
    s16 spawnX;
    s16 i;
    s16 spawnZ;

    if (D_80744820 != 0) {
        camStartPath(gPrimaryPlayerActor, 2, 5);
        slotQueueUpdate(1, 0, 0);
        for (i = 0; i < D_80744820; i++) {
            dist = (i * 2) + 30;
            spawnX = gPrimaryPlayerActor->x - mathSinF(gPrimaryPlayerActor->yaw) * dist;
            spawnZ = gPrimaryPlayerActor->z - mathCosF(gPrimaryPlayerActor->yaw) * dist;
            actorSpawnNodeEntryScaled(
                0x35,
                spawnX,
                gPrimaryPlayerActor->y + 20.0f + i * 5,
                spawnZ,
                gPrimaryPlayerActor->yaw,
                1,
                -1,
                0
            );
        }
        D_80744820 = 0;
    }
}

s32 mapFindPreviousSavedMap(s32 *outMap, s32 *outExitIndex) {
    s32 found = 0;
    s32 i = 0;

    while (i < 18 && !found) {
        if (D_8076A160[i].inUse != 0 && (D_8076A160[i].flags & 2)) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found) {
        *outMap = D_8076A160[i].map;
        *outExitIndex = D_8076A160[i].returnExitIndex;
    }
    return found;
}

void mapTransitionToPreviousOrExit(void) {
    s32 targetMap;
    s32 exitIndex;

    if (mapFindPreviousSavedMap(&targetMap, &exitIndex) != 0) {
        mapSlotFree(gCurrentMap);
        mapRequestTransition(targetMap, exitIndex);
    } else if (menuIsTransitionTypeD() != 0) {
        mapRequestTransition(0xF, 0);
    }
}

void mapTransitionToMenuOrPrevious(void) {
    if (menuIsTransitionTypeC() != 0) {
        mapRequestTransition(0x50, 0);
    } else {
        mapTransitionToPreviousOrExit();
    }
}

s32 mapFindSlotByMap(s16 target) {
    s32 i = 0;
    s32 found = 0;
    while (i < 18 && !found) {
        if (D_8076A160[i].inUse != 0 && D_8076A160[i].map == target) {
            found = 1;
        } else {
            i++;
        }
    }
    return found;
}

extern s8 D_80750ACC;
extern s32 gMapChunkCount;
extern s32 D_807FD56C;
extern s16 D_807FD570;

void mapSaveSlotAndTransition(s32 map, s32 exitIndex, s32 returnExitIndex, s16 flags) {
    Actor *player;
    s32 serializedSize;
    s32 i;
    s32 found;
    s32 k;
    f32 r;
    f32 g;
    f32 b;
    s32 pad;
    PlayerState *playerState;

    found = 0;
    i = 0;
    while (i < 18 && !found) {
        if (D_8076A160[i].inUse != 0 && gCurrentMap == D_8076A160[i].map) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found) {
        mapSlotFree(gCurrentMap);
    } else {
        found = 0;
        i = 0;
        while (i < 18 && !found) {
            if (D_8076A160[i].inUse == 0) {
                found = 1;
            } else {
                i++;
            }
        }
        if (!found) {
            faultSetMessage(0xA, 0, 0, 0);
        }
    }
    gridFreeAllActiveNodes();
    modelSlotSerializeAll(&D_8076A160[i].modelData, &serializedSize);
    heapRegisterSurvivor(&D_8076A160[i].modelData);
    modelSlotsPackRecords(&D_8076A160[i].records, &D_8076A160[i].recordSize);
    if (D_8076A160[i].records != NULL) {
        heapRegisterSurvivor(&D_8076A160[i].records);
    }
    D_8076A160[i].flags = flags;
    if (flags & 1) {
        player = gPrimaryPlayerActor;
        D_8076A160[i].x = player->x;
        D_8076A160[i].y = player->y;
        D_8076A160[i].z = player->z;
        D_8076A160[i].yaw = player->yaw;
    }
    D_8076A160[i].map = gCurrentMap;
    if (flags & 2) {
        D_8076A160[i].returnExitIndex = returnExitIndex;
    }
    for (k = 0; k < gMapChunkCount; k++) {
        lightGetColor(&r, &g, &b, k);
        D_8076A160[i].rgb[k][0] = (u32)(r * 255.0);
        D_8076A160[i].rgb[k][1] = (u32)(g * 255.0);
        D_8076A160[i].rgb[k][2] = (u32)(b * 255.0);
    }
    k = 1; // FAKE: reuses loop counter k as the constant 1 stored to D_80750ACC and inUse (regalloc)
    D_80750ACC = k;
    playerState = (PlayerState *)gPrimaryPlayerActor->customState;
    D_807FD56C = playerState->stateFlags;
    if (playerState->heldActor != NULL) {
        D_807FD570 = playerState->heldActor->actorType;
    } else {
        D_807FD570 = 0;
    }
    D_8076A160[i].inUse = k;
    mapRequestTransition(map, exitIndex);
}

s32 func_805FFE50(s32 map, s16 recordId, s16 value) {
    s32 i = 0;
    s32 found = 0;
    Struct8076A160 *slot;

    while (!found && i < 18) {
        if (D_8076A160[i].map == map) {
            found = 1;
        } else {
            i++;
        }
    }

    if (!found) {
        return 0;
    }

    slot = &D_8076A160[i];
    modelRecordFindAndSet(slot->records, slot->recordSize, recordId, value);
    return 1;
}

void mapSlotFree(s32 map) {
    s32 found = 0;
    s32 i = 0;

    while (i < 18 && !found) {
        if (D_8076A160[i].inUse != 0 && D_8076A160[i].map == map) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found) {
        Struct8076A160 *slot = &D_8076A160[i];
        heapUnregisterSurvivor(&slot->modelData);
        heapFree(slot->modelData);
        if (slot->recordSize != 0) {
            heapUnregisterSurvivor(&slot->records);
            heapFree(slot->records);
        }
        slot->inUse = 0;
        D_807F6010 = 0;
    }
}

void mapSlotArrayResetAll(void) {
    s32 i;

    for (i = 0; i < 18; i++) {
        if (D_8076A160[i].inUse) {
            heapUnregisterSurvivor(&D_8076A160[i].modelData);
            heapFree(D_8076A160[i].modelData);
            if (D_8076A160[i].recordSize != 0) {
                heapUnregisterSurvivor(&D_8076A160[i].records);
                heapFree(D_8076A160[i].records);
            }
            D_8076A160[i].inUse = 0;
        }
    }
}

void mapTransitionToWorldHub(s32 index) {
    mapSlotArrayResetAll();
    mapRequestTransition(D_80744734[index], 1);
}

s32 mapFindSlotIndex(s32 map) {
    s32 i;

    for (i = 0; i < 18; i++) {
        if (D_8076A160[i].inUse != 0 && map == D_8076A160[i].map) {
            return i;
        }
    }
    return -1;
}

s16 mapFindSavedPositionSlot(f32 *outX, f32 *outY, f32 *outZ) {
    s32 i;

    for (i = 0; i < 18; i++) {
        if (D_8076A160[i].inUse != 0 && (D_8076A160[i].flags & 1)) {
            *outX = D_8076A160[i].x;
            *outY = D_8076A160[i].y;
            *outZ = D_8076A160[i].z;
            return i;
        }
    }
    return -1;
}

s32 func_80600340(s16 *typeList, u8 typeCount, s32 *outMap) {
    u8 *subtableA;
    u8 *subtableB;
    f32 posX;
    f32 posY;
    f32 posZ;
    u8 slot;

    slot = mapFindSavedPositionSlot(&posX, &posY, &posZ);
    if (slot == -1) {
        return -1;
    }
    modelAssetGetSubtables(D_8076A160[slot].modelData, &subtableA, &subtableB);
    *outMap = D_8076A160[slot].map;
    return actorListFindClosestTargetIndex((s32 *)subtableB, typeList, typeCount, posX, posY, posZ);
}

void func_806003EC(s16 index) {
    gGlobalOverlayFlags = D_8074482C[index].overlayFlags;
    gGlobalCutsceneFlags = D_8074482C[index].cutsceneFlags;
}

s32 func_8060042C(s16 index) {
    return D_8074482C[index].unk8;
}

u8 func_80600454(s16 id, u8 *outVal) {
    u8 i;
    u8 isNew;
    s16 flagId;
    s32 pad;

    i = 0;
    isNew = 0;

    while (D_807565E0[i] != 0 && id != D_807565E0[i]) {
        i++;
    }

    if (D_807565E0[i] != 0) {
        *outVal = D_80756630[i];
        if (i < 13) {
            flagId = i + 0x307;
            isNew = flagGet(flagId, 0) == 0;
            flagSet(flagId, 1, 0);
        } else {
            isNew = 1;
        }
    }
    return isNew;
}
