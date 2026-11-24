#include "common.h"
#include "sched.h"
#include "actor.h"
#include "map.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/136820_fault.h"
#include "proto/global/15050_heap.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/36880_model_slot.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/8D3E0_actor_list.h"
#include "proto/global/AA960_pickup_drops.h"
#include "proto/global/CC800_player_setup.h"
#include "proto/global/F9450_grid_nodes.h"
#include "proto/global/FCCD0_slot_queue.h"

typedef struct {
    s32 map;
    s32 targetMap;
    s32 exitIndex;
} Struct807447A0;

typedef struct {
    s32 overlayFlags;
    s32 cutsceneFlags;
    s32 overlayBufferSize;
} Struct8074482C;

typedef struct {
    u16 map;
    u16 targetMap;
    u8 exitIndex;
} Struct8074475C;

typedef struct {
    s32 key;
    s32 value;
} KeyValuePair;

/* Extern variables */
extern u8 gGameMode;
extern u8 gNextGameMode;
extern s32 gInitialMap;
extern s32 gInitialExit;
u8 gMapHubWorldIndex[224] = {
    0x0C, 0x0D, 0x0C, 0x09, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0C, 0x09, 0x09, 0x00, 0x00, 0x01, 0x0D,
    0x01, 0x08, 0x09, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0D, 0x02, 0x02, 0x0B, 0x02, 0x03, 0x03,
    0x09, 0x00, 0x07, 0x09, 0x02, 0x00, 0x01, 0x03, 0x0B, 0x01, 0x0D, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x04, 0x03, 0x09, 0x03, 0x04, 0x09, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x09, 0x09, 0x09, 0x09, 0x09, 0x04, 0x04, 0x05, 0x09, 0x09, 0x09, 0x0B, 0x09, 0x09, 0x09,
    0x0D, 0x0D, 0x05, 0x04, 0x05, 0x05, 0x05, 0x06, 0x06, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x09, 0x07, 0x05, 0x09, 0x05, 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x0A, 0x06, 0x0A, 0x02, 0x03,
    0x06, 0x06, 0x06, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09,
    0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09,
    0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x0B, 0x0B, 0x02, 0x09, 0x09, 0x09, 0x09, 0x09,
    0x09, 0x09, 0x09, 0x06, 0x06, 0x09, 0x06, 0x06, 0x06, 0x00, 0x08, 0x07, 0x0B, 0x01, 0x03, 0x02,
    0x07, 0x07, 0x04, 0x03, 0x07, 0x07, 0x07, 0x06, 0x09, 0x06, 0x05, 0x06, 0x04, 0x07, 0x0A, 0x09,
    0x0A, 0x06, 0x05, 0x07, 0x05, 0x01, 0x0B, 0x06, 0x05, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x0B, 0x09, 0x09, 0x09, 0x09, 0x0B, 0x08, 0x08, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x00, 0x00, 0x00,
};
u16 gWorldBananaDeliveryGoals[8] = { 60, 120, 200, 250, 300, 350, 400, 0 };
s16 gWorldGoldenBananaGoals[8] = { 0x0001, 0x0005, 0x000F, 0x001E, 0x0032, 0x0041, 0x0050, 0x0064 };
s8 gWorldSecretGoalDiscounts[16] = { // per world: { discounted gWorldGoldenBananaGoals count, kong id } (critter/3340.c)
    0x01, -1, 0x03, 0x01, 0x0A, 0x03, 0x14, 0x02, 0x23, 0x04, 0x32, 0x00, 0x41, 0x02, 0x50, 0x04,
};
u8 gWorldRequiredKongs[16] = { 0, 1, 3, 2, 4, 0, 2, 0, 0, 1, 2, 3, 4, 5, 6, 8 };
u16 gWorldBossMaps[8] = { 0x08, 0xC5, 0x9A, 0x6F, 0x53, 0xC4, 0xC7, 0xCB };
s16 gWorldClearedFlags[8] = { 0x1A, 0x4A, 0x8A, 0xA8, 0xEC, 0x124, 0x13D, 0x17C };
s32 gKongUnlockFlags[5] = { 0x181, 0x6, 0x46, 0x42, 0x75 };
u16 gWorldLobbyMaps[10] = { 0xA9, 0xAD, 0xAF, 0xAE, 0xB2, 0xC2, 0xC1, 0xAA, 0xAA, 0x00 };
u16 gWorldMainMaps[10] = { 0x07, 0x26, 0x1A, 0x1E, 0x30, 0x48, 0x57, 0x22, 0x11, 0x00 };
Struct8074475C gDeathRespawnOverrides[11] = {
    { 0x38, 0x38, 0 },
    { 0x21, 0x21, 0 },
    { 0x56, 0x56, 0 },
    { 0x5A, 0x5A, 0 },
    { 0x5B, 0x5B, 0 },
    { 0x5D, 0x5D, 0 },
    { 0xAB, 0xAB, 2 },
    { 0xB0, 0xB0, 1 },
    { 0xA3, 0xA3, 0 },
    { 0x6C, 0x6C, 0 },
    { 0x64, 0x64, 0 },
};
Struct807447A0 gMapExitDestinations[8] = {
    { 0x06, 0x07, 14 },
    { 0x0E, 0x26, 17 },
    { 0x1B, 0x1A, 16 },
    { 0x27, 0x1E, 19 },
    { 0x37, 0x30, 16 },
    { 0x52, 0x48, 6 },
    { 0x6A, 0x70, 1 },
    { 0xB9, 0x71, 1 },
};
KeyValuePair gKongActorTypeFlags[4] = {
    { 3, 0x16F },
    { 4, 0x170 },
    { 5, 0x171 },
    { 6, 0x172 },
};
u8 gPendingLoadSpawnCount = 0;
u8 gNextTransitionFadeType = 1;
u8 gHasPendingTransition = 0;
Struct8074482C gMapLevelSettings[221] = {
    { 0, 0x80, 0 },
    { 0x40000800, 0, 0 },
    { 0, 0, 0 },
    { 0x404A86, 0x80, 0 },
    { 0x80010, 0x100, 0 },
    { 0x40000800, 0, 0 },
    { 0x80800, 0, 0 },
    { 0x1000, 0, 0x31000 },
    { 0x800343, 0x1, 0 },
    { 0, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x404A86, 0x80, 0 },
    { 0x1C, 0x10, 0 },
    { 0, 0, 0 },
    { 0x802A02, 0x1, 0 },
    { 0x40000800, 0, 0 },
    { 0x1000, 0, 0 },
    { 0x8, 0, 0 },
    { 0x4802, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0x1C, 0, 0 },
    { 0x1C, 0, 0 },
    { 0x1C, 0, 0 },
    { 0x1C, 0, 0 },
    { 0x40000800, 0, 0 },
    { 0x2000000, 0, 0xA000 },
    { 0x2800, 0, 0 },
    { 0x800243, 0x1, 0 },
    { 0, 0, 0 },
    { 0x1020, 0, 0 },
    { 0, 0, 0 },
    { 0x4800, 0, 0 },
    { 0x1000, 0x80, 0 },
    { 0x1000, 0x28, 0 },
    { 0x4802, 0, 0 },
    { 0x14, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0x2800, 0, 0 },
    { 0x40000800, 0, 0 },
    { 0, 0, 0 },
    { 0x1000, 0x1, 0 },
    { 0x1000, 0, 0 },
    { 0x1120, 0, 0 },
    { 0x1000, 0, 0 },
    { 0x1000, 0, 0 },
    { 0x1000, 0, 0 },
    { 0, 0x8, 0 },
    { 0, 0, 0 },
    { 0x4802, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0x1120602, 0x1, 0 },
    { 0, 0, 0 },
    { 0x80800, 0, 0 },
    { 0x1000, 0, 0 },
    { 0, 0, 0 },
    { 0, 0x1, 0 },
    { 0, 0, 0 },
    { 0x10141, 0x1, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0x404A86, 0x80, 0 },
    { 0x404886, 0x80, 0 },
    { 0x404886, 0x80, 0 },
    { 0x404886, 0x80, 0 },
    { 0x404886, 0x80, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0x1000, 0, 0 },
    { 0x1120602, 0x1, 0 },
    { 0x404886, 0x80, 0 },
    { 0x404886, 0x80, 0 },
    { 0x1800, 0, 0 },
    { 0x80902, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x40000800, 0x8, 0 },
    { 0x800, 0, 0 },
    { 0x802A16, 0x1, 0 },
    { 0x800343, 0x1, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0x88, 0 },
    { 0, 0, 0 },
    { 0x4, 0, 0 },
    { 0x4, 0x1, 0 },
    { 0x4, 0x1, 0 },
    { 0x4, 0x1, 0 },
    { 0x4, 0x1, 0 },
    { 0x4, 0x1, 0 },
    { 0, 0x1, 0 },
    { 0x4802, 0, 0 },
    { 0x800, 0, 0 },
    { 0, 0, 0 },
    { 0x4802, 0, 0 },
    { 0, 0, 0 },
    { 0x4800, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4A02, 0, 0 },
    { 0, 0, 0 },
    { 0x80800, 0, 0 },
    { 0x5830002, 0x1, 0 },
    { 0x4, 0x4, 0 },
    { 0x4810002, 0, 0 },
    { 0x200000, 0, 0 },
    { 0x1800363, 0x1, 0 },
    { 0x4, 0x4, 0 },
    { 0x8, 0x4, 0 },
    { 0x4, 0x4, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x404884, 0x80, 0 },
    { 0x404884, 0x80, 0 },
    { 0x404A84, 0x80, 0 },
    { 0x404A84, 0x80, 0 },
    { 0x404A84, 0x80, 0 },
    { 0x80902, 0, 0 },
    { 0x80902, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4A02, 0, 0 },
    { 0x4A02, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0, 0x44, 0 },
    { 0, 0, 0 },
    { 0, 0x8, 0 },
    { 0x1840343, 0x1, 0 },
    { 0x1120602, 0x1, 0 },
    { 0x1120602, 0x1, 0 },
    { 0x1120602, 0x1, 0 },
    { 0x1120602, 0x1, 0 },
    { 0x1120602, 0x1, 0 },
    { 0x1120602, 0x1, 0 },
    { 0x1120602, 0x1, 0 },
    { 0x1120602, 0x1, 0 },
    { 0, 0x4, 0 },
    { 0, 0x24, 0 },
    { 0x4802, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0x80, 0, 0 },
    { 0x1000, 0, 0 },
    { 0x1000, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0x1000, 0x1, 0 },
    { 0x1000, 0, 0 },
    { 0x1000, 0, 0 },
    { 0x1000, 0, 0 },
    { 0x10001800, 0, 0 },
    { 0x1000, 0, 0 },
    { 0, 0, 0 },
    { 0x10001800, 0, 0 },
    { 0x10001800, 0, 0 },
    { 0x10001800, 0, 0 },
    { 0, 0x44, 0 },
    { 0x4800, 0, 0 },
    { 0x2800, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0x1000, 0, 0 },
    { 0x4810002, 0, 0 },
    { 0x4800, 0, 0 },
    { 0x4810002, 0, 0 },
    { 0x1000, 0, 0 },
    { 0x1000, 0x4, 0 },
    { 0x1000, 0, 0 },
    { 0x800343, 0x1, 0 },
    { 0x800343, 0x1, 0 },
    { 0, 0, 0 },
    { 0x800303, 0x1, 0 },
    { 0, 0, 0 },
    { 0x80004802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x800343, 0x23, 0 },
    { 0x800343, 0x23, 0 },
    { 0x800343, 0x22, 0 },
    { 0x800343, 0x23, 0 },
    { 0x800343, 0x23, 0 },
    { 0, 0, 0 },
    { 0x4A02, 0, 0 },
    { 0x1004802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0x4802, 0, 0 },
    { 0, 0x8, 0 },
    { 0x800143, 0x3, 0 },
    { 0x100, 0x2, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};
const u8 gMapTitleMaps[80] = {
    0x01, 0x0F, 0x05, 0x19, 0x07, 0x1A, 0x1E, 0x30, 0x48, 0x57, 0x2A, 0x11, 0x26, 0x0A, 0x73, 0x74,
    0x75, 0x12, 0x76, 0x77, 0x78, 0x20, 0x79, 0x7A, 0x7B, 0x42, 0x44, 0x45, 0x7C, 0x43, 0x4A, 0x4B,
    0x7D, 0x7E, 0x7F, 0x80, 0x41, 0x4D, 0x81, 0x82, 0x4E, 0x4F, 0x83, 0x60, 0x84, 0x85, 0x63, 0x86,
    0x87, 0x68, 0x88, 0x89, 0x67, 0x8A, 0x8B, 0x8C, 0x65, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93,
    0x66, 0x94, 0x95, 0x96, 0x35, 0x49, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0x00, 0x00,
};
const u8 gMapTitleTextIds[80] = {
    0x0A, 0x0B, 0x0C, 0x0D, 0x00, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0E, 0x08, 0x01, 0x0F, 0x0F, 0x0F,
    0x0F, 0x10, 0x10, 0x10, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13,
    0x13, 0x14, 0x14, 0x14, 0x14, 0x15, 0x15, 0x15, 0x16, 0x16, 0x16, 0x17, 0x17, 0x17, 0x18, 0x18,
    0x18, 0x19, 0x19, 0x19, 0x1A, 0x1A, 0x1A, 0x1A, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x1C, 0x1C, 0x1C,
    0x1D, 0x1D, 0x1D, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x27, 0x23, 0x24, 0x25, 0x22, 0x26, 0x00, 0x00,
};
extern s32 gCurrentMap;
extern u8 gCurrentWorldId;
extern u8 gScreenRenderFlags;
extern s8 gMapLoadCountdown;
extern u8 *gSavedMapModelData;
extern Actor *gPrimaryPlayerActor;
extern s32 gGlobalCutsceneFlags;
extern u16 gLevelCollectibleCounts[];
extern f32 gScreenFadeRate;

/* Function declarations */

/* External functions */
void func_8002920C(void);

// .bss 0x8076A160-0x8076AF00
Struct8076A160 gSavedMapSlots[18];
u8 gTransitionFadeType;
u8 D_8076AEE1;
s16 gSavedSlotSpawnFlags;
f32 gSavedSlotSpawnX;
f32 gSavedSlotSpawnY;
f32 gSavedSlotSpawnZ;
s16 gSavedSlotSpawnYaw;
s16 gPreviousMap;
u16 gPendingTransitionMap;
u8 gPendingTransitionExit;
u8 D_8076AEF7;
u8 D_8076AEF8[8];

s32 playerGetActorTypeFlag(s32 *outValue) {
    s32 i;
    s32 found;

    found = 0;
    for (i = 0; i < sizeof(gKongActorTypeFlags) / sizeof(gKongActorTypeFlags[0]) && !found; i++) {
        found = gPrimaryPlayerActor->actorType == gKongActorTypeFlags[i].key;
        if (found) {
            *outValue = gKongActorTypeFlags[i].value;
        }
    }
    return found;
}

s32 mapIsLobby(s32 map) {
    s32 i;

    for (i = 0; i < 9; i++) {
        if (map == gWorldLobbyMaps[i]) {
            return 1;
        }
    }
    return 0;
}

u8 mapGetWorldIndex(u8 map) {
    return gMapHubWorldIndex[map];
}

s32 mapGetConfigValue(s32 unused, s32 index) {
    s32 value = gKongUnlockFlags[index];
    return value;
}

u8 mapGetHubWorldIndex(u8 map, u8 checkBossMap) {
    u8 worldIndex;
    s32 targetMap;
    s32 exitIndex;
    s32 pad;

    targetMap = map;
    worldIndex = gMapHubWorldIndex[targetMap];
    if (worldIndex == 0xD || worldIndex == 9) {
        if (mapFindPreviousSavedMap(&targetMap, &exitIndex)) {
            worldIndex = gMapHubWorldIndex[targetMap];
        }
    }
    if (checkBossMap && mapIsLobby(targetMap)) {
        worldIndex = 7;
    }
    return worldIndex;
}

u8 mapHasCollectedSufficientItems(void) {
    s32 index = mapGetHubWorldIndex(gCurrentWorldId, 0);
    return gLevelCollectibleCounts[index] >= gWorldBananaDeliveryGoals[index];
}

void mapSlotArrayInit(void) {
    s32 i;
    for (i = 0; i < 18; i++) {
        gSavedMapSlots[i].inUse = 0;
    }
}

void screenSetTransitionFadeType(u8 fadeType) {
    gNextTransitionFadeType = fadeType;
}

void screenApplyTransitionFadeType(void) {
    gTransitionFadeType = gNextTransitionFadeType;
    gNextTransitionFadeType = 1;
}

void mapSetPendingTransition(s16 map, u8 exitIndex) {
    gHasPendingTransition = 1;
    gPendingTransitionMap = map;
    gPendingTransitionExit = exitIndex;
}

void mapExecuteDeathTransition(s32 unused) {
    u16 pad;
    u16 targetMap;
    s32 limit;
    s32 i;
    u16 exitIndex;
    u8 found;
    s32 world;

    limit = sizeof(gDeathRespawnOverrides) / sizeof(gDeathRespawnOverrides[0]);
    i = 0;
    exitIndex = 0;
    found = 0;

    if (gHasPendingTransition != 0) {
        targetMap = gPendingTransitionMap;
        exitIndex = gPendingTransitionExit;
    } else {
        if (mapIsLobby(gCurrentMap) != 0) {
            targetMap = gCurrentMap;
        } else {
            world = mapGetHubWorldIndex(gCurrentMap, 0);
            targetMap = gWorldMainMaps[world];
            for (; !found && (i < limit); i++) {
                if (gCurrentMap == gDeathRespawnOverrides[i].map) {
                    targetMap = gDeathRespawnOverrides[i].targetMap;
                    exitIndex = gDeathRespawnOverrides[i].exitIndex;
                    found = 1;
                }
            }
        }
    }
    if (!found) {
        mapSlotArrayResetAll();
    }
    mapRequestTransition(targetMap, exitIndex);
    gHasPendingTransition = 0;
}

void mapExecuteVoidTransition(void) {
    s32 targetMap;
    s32 exitIndex;

    if (gCurrentMap != 0x22) {
        mapSlotArrayResetAll();
        targetMap = gWorldLobbyMaps[mapGetHubWorldIndex(gCurrentWorldId, 0)];
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
            if (gPlayerCharacterId[0] >= 6) {
                gPlayerCharacterId[0] = playerGetResolvedKongId(0);
            }
            gScreenRenderFlags |= 1;
            gPreviousMap = gCurrentMap;
            gInitialMap = map;
            gInitialExit = exitIndex;
            gMapLoadCountdown = 3;
            screenApplyTransitionFadeType();
            gScreenFadeRate = 1.0f;
            if ((gNextGameMode != 1) && (gTransitionFadeType == 1) && !(gGlobalCutsceneFlags & 2) && (gCurrentMap != 0x4C)) {
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
    gPreviousMap = gCurrentMap;
    flagTempsPruneUnloadedMaps();
    mapLoadSavedSlotSpawn(map);
}

void mapCheckAutoTransition(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gCurrentMap == gMapExitDestinations[i].map) {
            mapRequestTransition(gMapExitDestinations[i].targetMap, gMapExitDestinations[i].exitIndex);
            return;
        }
    }
}

void mapLoadSavedSlotSpawn(s32 map) {
    s32 idx = mapFindSlotIndex(map);

    if (idx != -1) {
        gSavedSlotSpawnFlags = gSavedMapSlots[idx].flags;
        gSavedSlotSpawnX = gSavedMapSlots[idx].x;
        gSavedSlotSpawnY = gSavedMapSlots[idx].y;
        gSavedSlotSpawnZ = gSavedMapSlots[idx].z;
        gSavedSlotSpawnYaw = gSavedMapSlots[idx].yaw;
    } else {
        gSavedSlotSpawnFlags = 0;
    }
}

void mapTransitionExitCurrent(s32 map, s32 exitIndex) {
    mapSlotFree(gCurrentMap);
    mapRequestTransition(map, exitIndex);
}

void mapSetTransitionExtraCounter(u8 count) {
    gPendingLoadSpawnCount = count;
}

void mapSpawnPendingPickups(void) {
    f32 dist;
    s16 spawnX;
    s16 i;
    s16 spawnZ;

    if (gPendingLoadSpawnCount != 0) {
        camStartPath(gPrimaryPlayerActor, 2, 5);
        slotQueueUpdate(1, 0, 0);
        for (i = 0; i < gPendingLoadSpawnCount; i++) {
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
        gPendingLoadSpawnCount = 0;
    }
}

s32 mapFindPreviousSavedMap(s32 *outMap, s32 *outExitIndex) {
    s32 found = 0;
    s32 i = 0;

    while (i < 18 && !found) {
        if (gSavedMapSlots[i].inUse != 0 && (gSavedMapSlots[i].flags & 2)) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found) {
        *outMap = gSavedMapSlots[i].map;
        *outExitIndex = gSavedMapSlots[i].returnExitIndex;
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
        if (gSavedMapSlots[i].inUse != 0 && gSavedMapSlots[i].map == target) {
            found = 1;
        } else {
            i++;
        }
    }
    return found;
}

extern u8 gPlayerStateSaved;
extern s32 gMapChunkCount;
extern s32 gSavedPlayerStateFlags;
extern s16 gSavedHeldActorType;

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
        if (gSavedMapSlots[i].inUse != 0 && gCurrentMap == gSavedMapSlots[i].map) {
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
            if (gSavedMapSlots[i].inUse == 0) {
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
    modelSlotSerializeAll(&gSavedMapSlots[i].modelData, &serializedSize);
    heapRegisterSurvivor(&gSavedMapSlots[i].modelData);
    modelSlotsPackRecords(&gSavedMapSlots[i].records, &gSavedMapSlots[i].recordSize);
    if (gSavedMapSlots[i].records != NULL) {
        heapRegisterSurvivor(&gSavedMapSlots[i].records);
    }
    gSavedMapSlots[i].flags = flags;
    if (flags & 1) {
        player = gPrimaryPlayerActor;
        gSavedMapSlots[i].x = player->x;
        gSavedMapSlots[i].y = player->y;
        gSavedMapSlots[i].z = player->z;
        gSavedMapSlots[i].yaw = player->yaw;
    }
    gSavedMapSlots[i].map = gCurrentMap;
    if (flags & 2) {
        gSavedMapSlots[i].returnExitIndex = returnExitIndex;
    }
    for (k = 0; k < gMapChunkCount; k++) {
        lightGetColor(&r, &g, &b, k);
        gSavedMapSlots[i].rgb[k][0] = r * 255.0;
        gSavedMapSlots[i].rgb[k][1] = g * 255.0;
        gSavedMapSlots[i].rgb[k][2] = b * 255.0;
    }
    gPlayerStateSaved = TRUE;
    playerState = gPrimaryPlayerActor->customState;
    gSavedPlayerStateFlags = playerState->stateFlags;
    if (playerState->heldActor != NULL) {
        gSavedHeldActorType = playerState->heldActor->actorType;
    } else {
        gSavedHeldActorType = 0;
    }
    gSavedMapSlots[i].inUse = TRUE;
    mapRequestTransition(map, exitIndex);
}

s32 mapSlotSetModelRecord(s32 map, s16 recordId, s16 value) {
    s32 i = 0;
    s32 found = 0;
    Struct8076A160 *slot;

    while (!found && i < 18) {
        if (gSavedMapSlots[i].map == map) {
            found = 1;
        } else {
            i++;
        }
    }

    if (!found) {
        return 0;
    }

    slot = &gSavedMapSlots[i];
    modelRecordFindAndSet(slot->records, slot->recordSize, recordId, value);
    return 1;
}

void mapSlotFree(s32 map) {
    s32 found = 0;
    s32 i = 0;

    while (i < 18 && !found) {
        if (gSavedMapSlots[i].inUse != 0 && gSavedMapSlots[i].map == map) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found) {
        Struct8076A160 *slot = &gSavedMapSlots[i];
        heapUnregisterSurvivor(&slot->modelData);
        heapFree(slot->modelData);
        if (slot->recordSize != 0) {
            heapUnregisterSurvivor(&slot->records);
            heapFree(slot->records);
        }
        slot->inUse = 0;
        gSavedMapModelData = NULL;
    }
}

void mapSlotArrayResetAll(void) {
    s32 i;

    for (i = 0; i < 18; i++) {
        if (gSavedMapSlots[i].inUse) {
            heapUnregisterSurvivor(&gSavedMapSlots[i].modelData);
            heapFree(gSavedMapSlots[i].modelData);
            if (gSavedMapSlots[i].recordSize != 0) {
                heapUnregisterSurvivor(&gSavedMapSlots[i].records);
                heapFree(gSavedMapSlots[i].records);
            }
            gSavedMapSlots[i].inUse = 0;
        }
    }
}

void mapTransitionToWorldHub(s32 index) {
    mapSlotArrayResetAll();
    mapRequestTransition(gWorldLobbyMaps[index], 1);
}

s32 mapFindSlotIndex(s32 map) {
    s32 i;

    for (i = 0; i < 18; i++) {
        if (gSavedMapSlots[i].inUse != 0 && map == gSavedMapSlots[i].map) {
            return i;
        }
    }
    return -1;
}

s16 mapFindSavedPositionSlot(f32 *outX, f32 *outY, f32 *outZ) {
    s32 i;

    for (i = 0; i < 18; i++) {
        if (gSavedMapSlots[i].inUse != 0 && (gSavedMapSlots[i].flags & 1)) {
            *outX = gSavedMapSlots[i].x;
            *outY = gSavedMapSlots[i].y;
            *outZ = gSavedMapSlots[i].z;
            return i;
        }
    }
    return -1;
}

s32 mapFindClosestTargetNearSavedPos(s16 *typeList, u8 typeCount, s32 *outMap) {
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
    modelAssetGetSubtables(gSavedMapSlots[slot].modelData, &subtableA, &subtableB);
    *outMap = gSavedMapSlots[slot].map;
    return actorListFindClosestTargetIndex((s32 *)subtableB, typeList, typeCount, posX, posY, posZ);
}

void mapApplyLevelFlags(s16 index) {
    gGlobalOverlayFlags = gMapLevelSettings[index].overlayFlags;
    gGlobalCutsceneFlags = gMapLevelSettings[index].cutsceneFlags;
}

s32 mapGetOverlayBufferSize(s16 index) {
    return gMapLevelSettings[index].overlayBufferSize;
}

u8 mapTitleCheckShow(s16 id, u8 *outVal) {
    u8 i;
    u8 isNew;
    s16 flagId;
    s32 pad;

    i = 0;
    isNew = 0;

    while (gMapTitleMaps[i] != 0 && id != gMapTitleMaps[i]) {
        i++;
    }

    if (gMapTitleMaps[i] != 0) {
        *outVal = gMapTitleTextIds[i];
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
