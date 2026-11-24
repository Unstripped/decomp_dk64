#include "common.h"
#include "render.h"
#include "actor.h"
#include "model.h"
#include "sched.h"
#include "proto/global/104F0_eeprom.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/133A90_prox_path.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/136820_fault.h"
#include "proto/global/15050_heap.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2F550_map_render.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/36880_model_slot.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/42630_cutscene_interp.h"
#include "proto/global/54150_model_anim.h"
#include "proto/global/55B20_map_chunk.h"
#include "proto/global/5E020_hash_table.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/61AA0_render_caches.h"
#include "proto/global/63810_light_queue.h"
#include "proto/global/63EC0_effect_water.h"
#include "proto/global/68EA0_model_emitter.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/6AD90_collision.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/8D3E0_actor_list.h"
#include "proto/global/CEAE0_player_update.h"

typedef struct ModelMapIdValueTriple {
    /* 0x0 */ u16 map;
    /* 0x2 */ u16 id;
    /* 0x4 */ u16 val;
} ModelMapIdValueTriple;

typedef struct ModelMapIdPair {
    /* 0x0 */ u16 map;
    /* 0x2 */ u16 id;
} ModelMapIdPair;

u16 D_80747CE0[20][2] = { // unreferenced
    { 0x0A, 2 }, { 0x16, 2 }, { 0x1E, 2 }, { 0x1F, 2 },
    { 0x0D, 3 }, { 0x16, 3 }, { 0x1E, 3 }, { 0x1F, 3 },
    { 0x0A, 5 }, { 0x0D, 5 }, { 0x1E, 5 }, { 0x1F, 5 },
    { 0x0A, 6 }, { 0x16, 6 }, { 0x1E, 6 }, { 0x0D, 6 },
    { 0x0A, 4 }, { 0x16, 4 }, { 0x0D, 4 }, { 0x1F, 4 },
};
ModelMapIdValueTriple gMapModelOverrideValues[5] = {
    { 0x69, 0x128, 2000 },
    { 0xAA, 0x129, 2000 },
    { 0xAA, 0x1A4, 2000 },
    { 0x52, 0xEC, 900 },
    { 0x22, 0x74, 900 },
};
ModelMapIdPair gMapModelFlagPairs[8] = {
    { 0x1E, 0x153 },
    { 0x1E, 0x210 },
    { 0x1E, 0x211 },
    { 0x1E, 0x212 },
    { 0x1E, 0x213 },
    { 0x1E, 0x214 },
    { 0x1E, 0x124 },
    { 0x1E, 0x7A },
};
s32 gModelSlotCount = 0;
s16 gModelSegmentStepIndex = 0;
u8 gModelTypeCountsReady = 0;

extern ModelSlot *gModelSlots;

extern PlayerStruct *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s32 gCurrentMap;
extern u8 gGfxBufferIndex;


extern u8 gModelSkipListCount;

void modelSkipListClear(void) {
    gModelSkipListCount = 0;
}

extern s16 gModelSkipList[];

void modelSkipListAdd(s16 modelIndex) {
    if (gModelSkipListCount != 4) {
        gModelSkipList[gModelSkipListCount++] = modelIndex;
    }
}

s32 modelSkipListContains(s16 modelIndex) {
    s32 i;

    for (i = 0; i < gModelSkipListCount; i++) {
        if (gModelSkipList[i] == modelIndex) {
            return 1;
        }
    }
    return 0;
}

extern s16 gHubCountedModelCounts[];

s16 modelTypeCountGet(u8 hubIndex) {
    return gHubCountedModelCounts[hubIndex];
}



void modelTypeCountsInit(void) {
    s32 pad;
    s32 i;
    void *asset;
    u8 *entries;
    u8 *subtables;
    u8 slot;
    s32 count;
    ModelAssetEntry *entry;
    s32 j;

    if (gModelTypeCountsReady == 0) {
        gModelTypeCountsReady = 1;
        for (i = 0; i < 8; i++) {
            gHubCountedModelCounts[i] = 0;
        }
        for (i = 0; i != 0xDD; i++) {
            asset = assetLoad(9, i, 1, 1);
            if (asset != NULL) {
                slot = mapGetHubWorldIndex(i, 1);
                modelAssetGetSubtables(asset, &entries, &subtables);
                count = *(s32 *)entries;
                entry = (ModelAssetEntry *)(entries + 4);
                for (j = 0; j < count; j++) {
                    if (modelTypeIsCounted(entry->modelType)) {
                        gHubCountedModelCounts[slot]++;
                    }
                    entry++;
                }
                assetSetImmediateFree();
                assetFreeBuffer(asset, 0x10C, 7);
            }
        }
    }
}

u16 modelTypeCountBeforeMap(u8 map) {
    u16 total;
    u8 slot;
    s32 i;
    void *asset;
    s32 pad;
    u8 *entries;
    u8 *subtables;
    s32 j;
    s32 count;
    ModelAssetEntry *entry;

    slot = mapGetHubWorldIndex(map, 1);
    total = 0;
    for (i = 0; i < map; i++) {
        if (slot == mapGetHubWorldIndex(i, 1)) {
            asset = assetLoad(9, i, 1, 1);
            if (asset != NULL) {
                modelAssetGetSubtables(asset, &entries, &subtables);
                count = *(s32 *)entries;
                entry = (ModelAssetEntry *)(entries + 4);
                for (j = 0; j < count; j++) {
                    if (modelTypeIsCounted(entry->modelType)) {
                        total++;
                    }
                    entry++;
                }
                assetSetImmediateFree();
                assetFreeBuffer(asset, 0x13A, 7);
            }
        }
    }
    return total;
}

s32 modelTypeIsCounted(u16 type) {
    switch (type) {
        case 0xA:
        case 0xD:
        case 0x16:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x23:
        case 0x24:
        case 0x27:
        case 0x2B:
        case 0x205:
        case 0x206:
        case 0x207:
        case 0x208:
            return 1;
        default:
            return 0;
    }
}

void modelAssetGetSubtables(u8 *asset, u8 **entriesOut, u8 **subtablesOut) {
    s32 n;
    u8 *r;

    if (asset == NULL) {
        *entriesOut = NULL;
        *subtablesOut = NULL;
        return;
    }
    *entriesOut = asset;
    n = *(s32 *)asset;
    asset += n * 0x30;
    asset += 4;
    r = asset;
    r += *(s32 *)asset * 0x24;
    r += 4;
    *subtablesOut = r;
}

extern s16 gModelSlotCapacity;

s16 modelSlotsAllocate(s32 map, u8 allocate) {
    switch (map) {
        case 48:
            gModelSlotCapacity = 0x212;
            break;
        case 26:
            gModelSlotCapacity = 0x1F4;
            break;
        case 38:
            gModelSlotCapacity = 0x1F4;
            break;
        case 30:
            gModelSlotCapacity = 0x1E5;
            break;
        case 7:
            gModelSlotCapacity = 0x1D1;
            break;
        default:
            gModelSlotCapacity = 0x1C2;
            break;
    }
    if (allocate != 0) {
        gModelSlots = heapAlloc(gModelSlotCapacity * 0x90);
        heapClearBlock(gModelSlots);
    }
    return gModelSlotCapacity;
}


extern s16 gCsModelIds[];
extern s32 gModelSlotNextId;

// One model's saved cutscene variables: modelSlotSerializeAll writes these after the slots, modelSlotsLoadMap
// reads them after the map's entry list; an s32 count precedes them.
typedef struct ModelCsVarsRecord {
    /* 0x00 */ s32 modelIndex; // gCsModelIds index
    /* 0x04 */ u8 vars[0x20]; // CsState.unk14
} ModelCsVarsRecord; /* 0x24 */

void modelSlotsLoadMap(u8 *mapData, s32 map, u8 checkSaved, u16 saveIndex, u8 saveFile) {
    struct RenderEntry *renderList;
    s32 entryCount;
    ModelAssetEntry *entry;
    u8 *pad;
    s32 i;
    s32 n;
    ModelCsVarsRecord *rec;
    s32 outCount;
    u16 counter;
    s16 result;
    u8 found;
    u8 used;

    renderList = NULL;
    outCount = 0;
    i = 0;
    counter = 0;
    gModelSlotCount = 0;
    if (mapData == NULL) {
        entryCount = 0;
    } else {
        entry = (ModelAssetEntry *)(mapData + 4);
        entryCount = *(s32 *)mapData;
    }
    gModelSlotNextId = 0;
    hashTableInit();
    csModelIdTableReset();
    mtxCopyQueueReset();
    if (mapData != NULL) {
        if (entryCount > 0) {
            do {
                found = 0;
                used = 0;
                if (checkSaved && modelTypeIsCounted(entry->modelType)) {
                    found = eepromReadChecksumBit(saveIndex + counter, saveFile);
                    used = 1;
                }
                if (found == 0 && modelSkipListContains(entry->modelType) == 0 &&
                    flagGetForMapObject(gCurrentMap, entry->mapObjectId) == 0 &&
                    modelTypeAllowedOnMap(entry->modelType, map) != 0) {
                    gModelSlots[outCount].x = entry->x;
                    gModelSlots[outCount].y = entry->y;
                    gModelSlots[outCount].z = entry->z;
                    gModelSlots[outCount].scale = entry->scale;
                    gModelSlots[outCount].rotX = entry->rotX;
                    gModelSlots[outCount].rotY = entry->rotY;
                    gModelSlots[outCount].rotZ = entry->rotZ;
                    gModelSlots[outCount].yOffset = entry->yOffset;
                    gModelSlots[outCount].csModelId = entry->mapObjectId;
                    result = modelSlotInit(outCount, entry->modelType, entry->x, entry->y, entry->z,
                                           entry->rotX, entry->rotY, entry->rotZ, entry->scale, entry->yOffset,
                                           entry->flags, entry->light, &renderList);
                    modelFlagsApplyState(gCurrentMap, gModelSlots[outCount].csModelId, &gModelSlots[outCount].flags);
                    gCsModelIds[entry->mapObjectId] = result;
                    gModelSlotCount++;
                    outCount++;
                }
                if (used != 0) {
                    counter++;
                }
                i++;
                entry++;
            } while (i < entryCount);
        }
        mapDistributeEntries(renderList);
        renderEntryListFree(renderList);
        mapResolveNodeAssets();
        csScriptLoad(assetLoad(0xA, gCurrentMap, 1, 0));
        n = *(s32 *)entry;
        rec = (ModelCsVarsRecord *)((s32 *)entry + 1);
        while (n--) {
            csModelStateSetVars(rec->modelIndex, rec->vars);
            rec++;
        }
        modelSkipListClear();
    }
}

// A model's sprite draw node as modelSlotInit builds it; spriteListBuildDisplayChain reads the same 0x38 bytes as
// SpriteDisplayNode (asset is the texture its key holds; unk34 is its chain link, cleared here).
typedef struct ModelSlotSubNode {
    /* 0x00 */ void *asset;
    /* 0x04 */ f32 scaleXZ;
    /* 0x08 */ u8 texWidth;
    /* 0x09 */ u8 texHeight;
    /* 0x0A */ u8 texFormat;
    /* 0x0B */ u8 texSize;
    /* 0x0C */ s16 baseHalfWidth;
    /* 0x0E */ s16 baseHalfDepth;
    /* 0x10 */ u8 pad10[0x10];
    /* 0x20 */ s16 groundX;
    /* 0x22 */ s16 groundZ;
    /* 0x24 */ s16 animTextureId;
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ s16 yawOffset;
    /* 0x2A */ s16 fullAlphaDist;
    /* 0x2C */ s16 maxDist;
    /* 0x2E */ u8 baseAlpha;
    /* 0x2F */ u8 pad2F;
    /* 0x30 */ u8 zBuffered;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ s32 unk34;
} ModelSlotSubNode;

// Display-list span starting at a texture's G_SETTIMG command (0xFD).
typedef struct TexImageCmdSpan {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 texAddr;
    /* 0x08 */ u8 pad8[0x28];
    /* 0x30 */ s32 tileSizeW0;
} TexImageCmdSpan;

// Commands a TexAnimNode patches in one copy of a display list (dlFindTextureCommands).
typedef struct TexAnimCmdSet {
    /* 0x0 */ TexImageCmdSpan *texCmd;
    /* 0x4 */ TexImageCmdSpan *texCmd2;
    /* 0x8 */ u32 *primColorCmd;
} TexAnimCmdSet;

// Texture animation of one model texture; its command sets are per display list (A/B) and gfx buffer.
typedef struct TexAnimNode {
    /* 0x00 */ TexAnimCmdSet cmdsA[2];
    /* 0x18 */ TexAnimCmdSet cmdsB[2];
    /* 0x30 */ s32 lastFrame;
    /* 0x34 */ s16 scrollS;
    /* 0x36 */ s16 scrollT;
    /* 0x38 */ s16 scrollSpeedX;
    /* 0x3A */ s16 scrollSpeedY;
    /* 0x3C */ void *textureBuffer;
    /* 0x40 */ void *textureBuffer2;
    /* 0x44 */ void *texture;
    /* 0x48 */ u8 animMode;
    /* 0x49 */ u8 frameChanged;
    /* 0x4A */ u8 findSecond;
    /* 0x4B */ u8 pad4B;
    /* 0x4C */ s32 frameTicks;
    /* 0x50 */ s32 tick;
    /* 0x54 */ s32 frame;
    /* 0x58 */ s32 frameCount;
    /* 0x5C */ s32 frameTextures[29];
    /* 0xD0 */ u8 keepBuffers;
    /* 0xD1 */ u8 padD1[3];
    /* 0xD4 */ struct TexAnimNode *next;
} TexAnimNode;

typedef struct ModelType1Obj {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ f32 rotX;
    /* 0x14 */ f32 rotY;
    /* 0x18 */ f32 rotZ;
    /* 0x1C */ f32 yOffset;
    /* 0x20 */ u8 pad20[0x80];
    /* 0xA0 */ u32 *displayListA;
    /* 0xA4 */ u32 *displayListACopy;
    /* 0xA8 */ u32 *displayListB;
    /* 0xAC */ u32 *displayListBCopy;
    /* 0xB0 */ u8 padB0[6];
    /* 0xB6 */ s16 id;
    /* 0xB8 */ TexAnimNode *texAnims;
    /* 0xBC */ ModelSlotSubNode *subNode;
    /* 0xC0 */ s16 maxDist;
    /* 0xC2 */ u8 fullBright;
    /* 0xC3 */ u8 light;
    /* 0xC4 */ u8 surfaceType;
    /* 0xC5 */ u8 mapFlags;
} ModelType1Obj;

// ModelSlot.unk20 seen as either kind (ModelSlot.unk86 / ModelAssetHeader.unk1C: 1 or 2).
typedef union ModelKindObj {
    ModelType1Obj type1;
    RenderQuadModelObj type2;
} ModelKindObj;

void modelNodeListSyncFlags(RenderEntry *node) {
    RenderQuadModelObj *obj;
    s16 flag;

    if (node != NULL) {
        do {
            if (node->type == 2) {
                obj = node->object;
                switch (obj->modelType) {
                    case 0xA:
                    case 0x24:
                    case 0x208:
                        flag = 6;
                        break;
                    case 0x1F:
                    case 0x27:
                    case 0x206:
                        flag = 0x75;
                        break;
                    case 0x16:
                    case 0x1C:
                    case 0x207:
                        flag = 0x42;
                        break;
                    case 0x1E:
                    case 0x23:
                    case 0x205:
                        flag = 0x46;
                        break;
                    default:
                        flag = -1;
                        break;
                }
                if (flag != -1) {
                    if (flagGet(flag, 0) == 0) {
                        obj->flags |= 0x10;
                    } else {
                        obj->flags &= ~0x10;
                    }
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}

s32 modelTypeAllowedOnMap(s16 type, s32 map) {
    return 1;
}

s32 modelSlotFindByType(s32 type, s32 *cursor, f32 *xOut, f32 *yOut, f32 *zOut, s16 *idOut, s16 *csIdOut) {
    s32 i;
    u8 found;

    found = 0;
    i = *cursor;
    while (found == 0 && i < gModelSlotCount) {
        if (gModelSlots[i].modelType == type) {
            found = 1;
            *idOut = gModelSlots[i].id;
            *csIdOut = gModelSlots[i].csModelId;
            *xOut = gModelSlots[i].x;
            *yOut = gModelSlots[i].y;
            *zOut = gModelSlots[i].z;
        }
        i++;
    }
    *cursor = i;
    return found;
}

extern u8 gModelSlotAppendBlocked;

s16 modelSlotAppend(s32 type, f32 x, f32 y, f32 z, f32 yOffset, u8 force) {
    struct RenderEntry *renderList;
    s16 slotId;
    f32 scale;

    renderList = NULL;
    if (gModelSlotCount >= gModelSlotCapacity) {
        faultSetMessage(8, 0, 0, 0);
    }
    if (force == 0 && gModelSlotAppendBlocked != 0) {
        return -1;
    }
    scale = modelTypeGetDefaultScale(type);
    gModelSlots[gModelSlotCount].x = x;
    gModelSlots[gModelSlotCount].y = y;
    gModelSlots[gModelSlotCount].z = z;
    gModelSlots[gModelSlotCount].scale = scale;
    gModelSlots[gModelSlotCount].rotX = 0.0f;
    gModelSlots[gModelSlotCount].rotY = 0.0f;
    gModelSlots[gModelSlotCount].rotZ = 0.0f;
    gModelSlots[gModelSlotCount].yOffset = y - yOffset;
    gModelSlots[gModelSlotCount].flags = 0;
    slotId = modelSlotInit(gModelSlotCount, type, x, y, z, 0.0f, 0.0f, 0.0f, scale, y - yOffset, 1, 0, &renderList);
    mapDistributeEntries(renderList);
    renderEntryListFree(renderList);
    gModelSlots[gModelSlotCount].csModelId = csModelIdTableAlloc(slotId, force);
    gModelSlotCount++;
    return slotId;
}

extern s32 gGlobalCutsceneFlags;


s16 modelSlotInit(s32 slot, s32 modelType, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 yOffset, u8 flags, u8 light, struct RenderEntry **renderListInOut) {
    s32 padA[1];
    struct RenderEntry *renderList;
    s32 padB[1];
    ModelType1Obj *obj1;
    RenderQuadModelObj *obj2;
    ModelAssetHeader *info;
    s32 type;
    ModelSlotSubNode *node;
    ModelSlotSubNode **link;

    renderList = *renderListInOut;
    modelSlotInitFromAsset(&gModelSlots[slot], modelType);
    gModelSlots[slot].id = gModelSlotNextId;
    hashTableInsert(gModelSlots[slot].id, slot);
    info = gModelSlots[slot].asset;
    type = info->modelKind;
    if (gGlobalCutsceneFlags & 0x100) {
        info->flags &= ~0x10;
    }
    modelApplyMapOverrideValue(modelType, info);
    if (gGlobalOverlayFlags & 0x100) {
        info->maxDist = 0x7D0;
    } else if (gGlobalOverlayFlags & 0x400000) {
        info->maxDist = 0x1F4;
    }
    modelSlotAllocAnimBuffers(&gModelSlots[slot].anim, info);
    gModelSlots[slot].boxBuffer.unk14 = 0;
    gModelSlots[slot].boxBuffer.flags = 0;
    collisionBuildSlotBoxes(slot, info, x, y, z, rotX, rotY, rotZ, scale);
    dynamicBufferFree(&gModelSlots[slot].boxBuffer);
    modelSlotClearTail(slot);
    gModelSlots[slot].triBuffer.flags = 0;
    modelSlotBuildTriangleBuffer(slot, info, x, y, z, rotX, rotY, rotZ, scale);
    modelSlotTriBufferRelease(&gModelSlots[slot].triBuffer);
    modelSlotBuildVertPosList(slot, info, x, y, z, rotX, rotY, rotZ, scale, 0);
    modelSlotBuildNodePosList(slot, info, x, y, z, rotX, rotY, rotZ, scale, 0);
    modelSlotBuildProxPaths(gModelSlots[slot].id, info, scale);
    if (type == 1) {
        modelSlotReplaceSegment6Commands(&gModelSlots[slot]);
    }
    if (type != 1) {
        if (type == 2) {
            modelQuadBuildOutput(&gModelSlots[slot], x, y, z, rotX, rotY, rotZ, scale, yOffset);
            modelSlotInitTexAnimNodes(info, &gModelSlots[slot], type);
            obj2 = gModelSlots[slot].renderObj;
            link = &obj2->subNode;
            obj2->id = gModelSlotNextId;
            obj2->flags = flags;
            obj2->light = light;
            obj2->maxDist = info->maxDist;
            obj2->fullBright = info->fullBright;
            obj2->surfaceType = groundSurfaceTypeAt(x, y, z);
        }
    } else {
        obj1 = gModelSlots[slot].renderObj;
        obj1->x = x;
        obj1->y = y;
        obj1->z = z;
        obj1->scale = scale;
        obj1->rotX = rotX;
        obj1->rotY = rotY;
        obj1->rotZ = rotZ;
        obj1->yOffset = yOffset;
        obj1->id = gModelSlotNextId;
        obj1->maxDist = info->maxDist;
        obj1->fullBright = info->fullBright;
        obj1->light = light;
        obj1->surfaceType = groundSurfaceTypeAt(x, y, z);
        obj1->mapFlags = 0;
        modelFlagsApplyMapPairs(modelType, &obj1->mapFlags);
        modelSlotInitTexAnimNodes(info, &gModelSlots[slot], type);
        link = &obj1->subNode;
    }
    modelSlotResolveAssetTextures(&gModelSlots[slot], 0, 0);
    if (type == 2) {
        modelSlotLinkTexAnimTextures(info, &gModelSlots[slot]);
    }
    gModelSlots[slot].modelType = modelType;
    gModelSlots[slot].modelKind = type;
    gModelSlots[slot].csState = NULL;
    if (info->spriteTexture != -1) {
        node = heapAlloc(0x38);
        *link = node;
        node->unk34 = 0;
        node->scaleXZ = 1.0f;
        node->baseHalfWidth = info->spriteHalfWidth;
        node->baseHalfDepth = info->spriteHalfDepth;
        node->texFormat = info->spriteTexFormat;
        node->texSize = info->spriteTexSize;
        node->texWidth = info->spriteTexWidth;
        node->texHeight = info->spriteTexHeight;
        node->animTextureId = info->spriteAnimTextureId;
        node->yawOffset = info->spriteYawOffset;
        node->fullAlphaDist = info->spriteFullAlphaDist * 10;
        node->maxDist = info->spriteMaxDist * 10;
        node->baseAlpha = info->spriteBaseAlpha;
        node->zBuffered = info->spriteZBuffered;
        node->asset = assetLoad(0x19, info->spriteTexture, 1, 0);
        modelSlotUpdateGroundCoords(slot, 0);
    }
    *renderListInOut = renderEntryAddOrUpdate(renderList, type, gModelSlots[slot].renderObj, x, y, z, info->maxDist, gModelSlotNextId, 0, 0, 0);
    gModelSlotNextId += 1;
    return gModelSlotNextId - 1;
}

void modelFlagsApplyMapPairs(s16 id, u8 *flags) {
    s32 i;
    s32 count;
    i = 0;
    count = sizeof(gMapModelFlagPairs) / sizeof(gMapModelFlagPairs[0]);
    for (; i < count; i++) {
        if (gCurrentMap == gMapModelFlagPairs[i].map && id == gMapModelFlagPairs[i].id) {
            *flags |= 1;
            return;
        }
    }
}


void modelFlagsApplyState(s16 map, s16 id, u8 *flags) {
    switch (flagValueForMapObject(map, id)) {
        case 2:
            *flags |= 8;
            break;
        case 5:
            *flags |= 4;
            break;
        case 6:
            *flags |= 1;
            break;
        case 3:
            *flags |= 2;
            break;
        case 4:
            *flags |= 0x10;
            break;
    }
}

void modelApplyMapOverrideValue(s32 id, ModelAssetHeader *info) {
    s32 i;
    s32 count;

    count = sizeof(gMapModelOverrideValues) / sizeof(gMapModelOverrideValues[0]);
    for (i = 0; i < count; i++) {
        if (gCurrentMap == gMapModelOverrideValues[i].map && id == gMapModelOverrideValues[i].id) {
            info->maxDist = gMapModelOverrideValues[i].val;
            return;
        }
    }
}


s32 groundSurfaceTypeAt(f32 x, f32 y, f32 z) {
    f32 groundY;

    groundY = y + 10.0f;
    if (collisionCheckGroundAtPoint(x, z, &groundY) != 0) {
        return collisionGetFloorLightLevel();
    }
    return 0xF;
}


void modelSlotUpdateGroundCoords(s16 slot, u8 isId) {
    s32 padA[4];
    ModelAssetHeader *info;
    ModelSlotSubNode *dst;
    ModelKindObj *obj;
    f32 groundY;
    s16 groundX;
    s16 groundZ;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    groundY = gModelSlots[slot].y + 20.0f;
    if (collisionCheckGroundAtPoint(gModelSlots[slot].x, gModelSlots[slot].z, &groundY) != 0) {
        collisionGetFloorTilt(&groundX, &groundZ);
        info = gModelSlots[slot].asset;
        switch (info->modelKind) {
            case 1:
                obj = gModelSlots[slot].renderObj;
                dst = obj->type1.subNode;
                break;
            case 2:
                obj = gModelSlots[slot].renderObj;
                dst = obj->type2.subNode;
                break;
        }
        if (dst != NULL) {
            dst->groundX = groundX;
            dst->groundZ = groundZ;
        }
    }
}

typedef struct ModelPathSeg {
    /* 0x00 */ f32 startOffset;
    /* 0x04 */ f32 endOffset;
    /* 0x08 */ s16 minAngle;
    /* 0x0A */ s16 endMinAngle;
    /* 0x0C */ s16 maxAngle;
    /* 0x0E */ s16 endMaxAngle;
    /* 0x10 */ u8 startNode;
    /* 0x11 */ u8 endNode;
    /* 0x12 */ u8 disabled;
    /* 0x13 */ u8 pad13;
} ModelPathSeg;

typedef struct ModelPathEntry {
    /* 0x00 */ f32 moveSpeed;
    /* 0x04 */ f32 exitSpeedXZ;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 attachDist;
    /* 0x10 */ f32 detachDist;
    /* 0x14 */ u8 endBehavior;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 segCount;
    /* 0x17 */ u8 pad17;
    /* 0x18 */ ModelPathSeg segs[8];
} ModelPathEntry;


void modelSlotBuildProxPaths(s16 id, ModelAssetHeader *paths, f32 scale) {
    s32 j;
    ModelPathEntry *tbl;
    s32 i;
    s32 count;
    f32 bx;
    f32 ax;
    f32 by;
    f32 ay;
    f32 bz;
    f32 az;
    f32 len;

    count = *(s32 *)(paths->proxPathsOff + (s32)paths);
    tbl = (ModelPathEntry *)((u8 *)(paths->proxPathsOff + (s32)paths) + 4);
    for (i = 1; i <= count; i++) {
        len = 0.0f;
        for (j = 0; j < tbl[i - 1].segCount; j++) {
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].startNode, &ax, &ay, &az);
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].endNode, &bx, &by, &bz);
            len += sqrtf((az - bz) * (az - bz) + ((ax - bx) * (ax - bx) + (ay - by) * (ay - by)));
        }
        proxPathAdd((Actor *)id, 1, i, 1, tbl[i - 1].segCount, 0.0f, len, tbl[i - 1].moveSpeed * scale, tbl[i - 1].attachDist * scale, tbl[i - 1].detachDist * scale, tbl[i - 1].detachDist * scale, tbl[i - 1].endBehavior, tbl[i - 1].exitSpeedXZ, tbl[i - 1].unk8, tbl[i - 1].unk15);
        for (j = 0; j < tbl[i - 1].segCount; j++) {
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].startNode, &ax, &ay, &az);
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].endNode, &bx, &by, &bz);
            proxPathSetSegment((Actor *)id, i, j, tbl[i - 1].segs[j].startNode, tbl[i - 1].segs[j].endNode, sqrtf((az - bz) * (az - bz) + ((ax - bx) * (ax - bx) + (ay - by) * (ay - by))), tbl[i - 1].segs[j].startOffset * scale, tbl[i - 1].segs[j].endOffset * scale, tbl[i - 1].segs[j].disabled, tbl[i - 1].segs[j].minAngle, tbl[i - 1].segs[j].maxAngle, tbl[i - 1].segs[j].endMinAngle, tbl[i - 1].segs[j].endMaxAngle);
        }
    }
}



typedef struct ModelVert {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ s8 bone;
} ModelVert;

void modelSlotBuildVertPosList(s32 slot, ModelAssetHeader *verts, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale, u8 mode) {
    ModelVert *vert;
    ModelPosNode *node;
    ModelPosNode **tail;
    f32 mtx[4][4];
    s32 *tbl;
    s32 count;

    node = NULL;
    tail = &gModelSlots[slot].attachPoints;
    if (mode == 0) {
        *tail = NULL;
    }
    tbl = (s32 *)(verts->attachPointsOff + (s32)verts);
    count = *tbl;
    vert = (ModelVert *)(tbl + 1);
    if (count != 0) {
        do {
            switch (mode) {
                case 0:
                    node = heapAlloc(sizeof(ModelPosNode));
                    *tail = node;
                    tail = &node->next;
                    node->next = NULL;
                    break;
                case 1:
                    if (node == NULL) {
                        node = *tail;
                    } else {
                        node = node->next;
                    }
                    break;
            }
            modelSlotBuildTransformMatrix(slot, vert->bone, mtx);
            guMtxXFMF(mtx, vert->x, vert->y, vert->z, &node->x, &node->y, &node->z);
            count--;
            vert++;
        } while (count != 0);
    }
}

void modelPosNodeListFree(ModelPosNode *node) {
    ModelPosNode *next;

    while (node != NULL) {
        next = node->next;
        heapFree(node);
        node = next;
    }
}

void modelSlotGetNodePos(s32 slot, u8 isId, s32 index, f32 *xOut, f32 *yOut, f32 *zOut) {
    ModelPosNode *node;
    s32 n;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    node = gModelSlots[slot].nodePosList;
    for (n = index - 1; node != NULL && n != 0; n--) {
        node = node->next;
    }
    if (node != NULL) {
        *xOut = node->x;
        *yOut = node->y;
        *zOut = node->z;
    } else {
        *xOut = *yOut = *zOut = 0.0f;
    }
}

Mtx *modelSlotGetNodeMatrix(s32 slot, u8 isId, s32 index) {
    s32 idx;
    f32 mtxF[4][4];
    Mtx *mtx;
    ModelAssetHeader *verts;
    ModelVert *vert;

    idx = slot;
    if (isId == 1) {
        idx = hashTableLookup(slot);
    }
    verts = gModelSlots[idx].asset;
    vert = (ModelVert *)((s32 *)(verts->nodesOff + (s32)verts) + 1);
    for (index--; vert != NULL && index != 0; index--) {
        vert++;
    }
    modelSlotBuildTransformMatrix(idx, vert->bone, mtxF);
    mtx = heapAlloc(sizeof(Mtx));
    guMtxF2L(mtxF, mtx);
    return mtx;
}

void modelSlotBuildNodePosList(s32 slot, ModelAssetHeader *verts, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale, u8 mode) {
    ModelVert *vert;
    ModelPosNode *node;
    ModelPosNode **tail;
    f32 nodeMtx[4][4];
    f32 pad[4][4];
    s32 *tbl;
    s32 count;

    node = NULL;
    tail = &gModelSlots[slot].nodePosList;
    if (mode == 0) {
        *tail = NULL;
    }
    tbl = (s32 *)(verts->nodesOff + (s32)verts);
    count = *tbl;
    vert = (ModelVert *)(tbl + 1);
    if (count != 0) {
        do {
            switch (mode) {
                case 0:
                    node = heapAlloc(sizeof(ModelPosNode));
                    *tail = node;
                    tail = &node->next;
                    node->next = NULL;
                    break;
                case 1:
                    if (node == NULL) {
                        node = *tail;
                    } else {
                        node = node->next;
                    }
                    break;
            }
            modelSlotBuildTransformMatrix(slot, vert->bone, nodeMtx);
            guMtxXFMF(nodeMtx, vert->x, vert->y, vert->z, &node->x, &node->y, &node->z);
            count--;
            vert++;
        } while (count != 0);
    }
}

void modelLinkedNodeListFree(ModelPosNode *node) {
    ModelPosNode *next;

    while (node != NULL) {
        next = node->next;
        heapFree(node);
        node = next;
    }
}

void modelSlotClearTail(s32 slot) {
    ModelTriBuffer *p = &gModelSlots[slot].triBuffer;
    u8 i;

    for (i = 0; i < 2; i++) {
        p->disabledPartIds[i] = 0xFF;
    }
    p->flags = 0;
}

void modelSlotUpdateTailKey(s32 slot, u8 isId, u8 newKey, u8 remove) {
    s32 i = 0;
    u8 found = 0;
    u8 key;
    u8 *p;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    p = gModelSlots[slot].triBuffer.disabledPartIds;
    key = remove ? newKey : 0xFF;
    while (i < 2 && found == 0) {
        if (key == p[i]) {
            found = 1;
        } else {
            i++;
        }
    }
    p[i] = remove ? 0xFF : newKey;
}


// One model collision triangle in the asset (ModelAssetHeader.unk50 table, after a 0x10 header); 0x18 bytes.
typedef struct ModelAssetTri {
    /* 0x00 */ s16 v[9]; // three vertices x/y/z
    /* 0x12 */ u8 unk12;
    /* 0x13 */ s8 bone; // -1: in model space
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 pad16[2];
} ModelAssetTri; // size = 0x18

void modelSlotBuildTriangleBuffer(s32 slot, ModelAssetHeader *data, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale) {
    s32 count;
    ModelData *anim;
    f32 mtx[4][4];
    f32 rotMtx[4][4];
    f32 boneMtx[4][4];
    f32 boneWorldMtx[4][4];
    ModelTriBuffer *buf;
    ModelAssetTri *entry;
    CollisionTriF *out;
    s32 i;
    u8 *animFrame;
    u8 *boneTable;
    s8 lastBone;
    s32 pad[2];

    lastBone = -1;
    buf = &gModelSlots[slot].triBuffer;
    anim = gModelSlots[slot].anim;
    if (anim != NULL) {
        animFrame = anim->frames[gGfxBufferIndex];
    } else {
        animFrame = NULL;
    }
    boneTable = data->bonesOff + (u8 *)data;
    if (data->flags & 4) {
        buf->flags |= 2;
    } else {
        buf->flags &= ~2;
    }
    count = *(s32 *)(data->trisOff + (u8 *)data);
    if (count == 0) {
        buf->tri_start = NULL;
        buf->tri_end = NULL;
        buf->flags |= 1;
        buf->timestamp = gFrameCounter;
        return;
    }
    if (!(buf->flags & 1)) {
        buf->tri_start = heapAlloc(count * 0x28);
    }
    buf->flags |= 4;
    entry = (ModelAssetTri *)(data->trisOff + (u8 *)data + 0x10);
    out = buf->tri_start;
    guScaleF(mtx, scale, scale, scale);
    guRotateF(rotMtx, rotX, 1.0f, 0.0f, 0.0f);
    guMtxCatF(mtx, rotMtx, mtx);
    guRotateF(rotMtx, rotY, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtx, rotMtx, mtx);
    guRotateF(rotMtx, rotZ, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtx, rotMtx, mtx);
    guTranslateF(rotMtx, x, y, z);
    guMtxCatF(mtx, rotMtx, mtx);
    boundsTransformToAabb(mtx, data->trisOff + (u8 *)data + 4, buf);
    for (i = 0; i < count; i++) {
        if (entry->bone == -1) {
            if (modelTriangleTransform(entry, out, mtx) != 0) {
                out++;
            }
        } else {
            if (lastBone != entry->bone) {
                modelBuildBoneChainMatrix((s32 *)(boneTable + (entry->bone << 5)), animFrame, boneMtx);
                guMtxCatF(boneMtx, mtx, boneWorldMtx);
                lastBone = entry->bone;
            }
            if (modelTriangleTransform(entry, out, boneWorldMtx) != 0) {
                bboxExpandFromTriangle(out, &buf->bbox);
                out++;
            }
        }
        entry++;
    }
    buf->tri_end = out;
    buf->flags |= 1;
    buf->timestamp = gFrameCounter;
}


void bboxExpandFromTriangle(CollisionTriF *tri, CollisionBoundingBox *bounds) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (tri->x[i] < bounds->minX) {
            bounds->minX = tri->x[i];
        }
        if (tri->z[i] < bounds->minZ) {
            bounds->minZ = tri->z[i];
        }
        if (bounds->maxX < tri->x[i]) {
            bounds->maxX = tri->x[i];
        }
        if (bounds->maxZ < tri->z[i]) {
            bounds->maxZ = tri->z[i];
        }
    }
}


typedef struct {
    /* 0x00 */ u8 padL80633DC0[0xC];
    /* 0x0C */ f32 minX;
    /* 0x10 */ f32 minY;
    /* 0x14 */ f32 minZ;
    /* 0x18 */ f32 maxX;
    /* 0x1C */ f32 maxY;
    /* 0x20 */ f32 maxZ;
} BoundingBox;

#define MODEL_BOUNDS_OUT ((BoundingBox *)bounds)
#define MODEL_BOUNDS_ACCUMULATE(x, y, z) \
    guMtxXFMF(mtx, (f32)((s16 *)verts)[x], (f32)((s16 *)verts)[y], (f32)((s16 *)verts)[z], &tx, &ty, &tz); \
    if (MODEL_BOUNDS_OUT->minX < tx) { MODEL_BOUNDS_OUT->minX = MODEL_BOUNDS_OUT->minX; } else { MODEL_BOUNDS_OUT->minX = tx; } \
    if (MODEL_BOUNDS_OUT->minY < ty) { MODEL_BOUNDS_OUT->minY = MODEL_BOUNDS_OUT->minY; } else { MODEL_BOUNDS_OUT->minY = ty; } \
    if (MODEL_BOUNDS_OUT->minZ < tz) { MODEL_BOUNDS_OUT->minZ = MODEL_BOUNDS_OUT->minZ; } else { MODEL_BOUNDS_OUT->minZ = tz; } \
    if (tx < MODEL_BOUNDS_OUT->maxX) { MODEL_BOUNDS_OUT->maxX = MODEL_BOUNDS_OUT->maxX; } else { MODEL_BOUNDS_OUT->maxX = tx; } \
    if (ty < MODEL_BOUNDS_OUT->maxY) { MODEL_BOUNDS_OUT->maxY = MODEL_BOUNDS_OUT->maxY; } else { MODEL_BOUNDS_OUT->maxY = ty; } \
    if (tz < MODEL_BOUNDS_OUT->maxZ) { MODEL_BOUNDS_OUT->maxZ = MODEL_BOUNDS_OUT->maxZ; } else { MODEL_BOUNDS_OUT->maxZ = tz; }

void boundsTransformToAabb(f32 (*mtx)[4], void *verts, void *bounds) {
    f32 tx;
    f32 ty;
    f32 tz;

    guMtxXFMF(mtx, (f32)((s16 *)verts)[0], (f32)((s16 *)verts)[1], (f32)((s16 *)verts)[2], &tx, &ty, &tz);
    MODEL_BOUNDS_OUT->minX = tx;
    MODEL_BOUNDS_OUT->minY = ty;
    MODEL_BOUNDS_OUT->minZ = tz;
    MODEL_BOUNDS_OUT->maxX = tx;
    MODEL_BOUNDS_OUT->maxY = ty;
    MODEL_BOUNDS_OUT->maxZ = tz;
    MODEL_BOUNDS_ACCUMULATE(3, 1, 2)
    MODEL_BOUNDS_ACCUMULATE(0, 1, 5)
    MODEL_BOUNDS_ACCUMULATE(3, 1, 5)
    MODEL_BOUNDS_ACCUMULATE(0, 4, 2)
    MODEL_BOUNDS_ACCUMULATE(3, 4, 2)
    MODEL_BOUNDS_ACCUMULATE(0, 4, 5)
    MODEL_BOUNDS_ACCUMULATE(3, 4, 5)
}

s32 modelTriangleTransform(void *src, void *dst, f32 (*mtx)[4]) {
    s16 *in = src;
    f32 *out = dst;

    guMtxXFMF(mtx, in[0], in[1], in[2], &out[0], &out[3], &out[6]);
    guMtxXFMF(mtx, in[3], in[4], in[5], &out[1], &out[4], &out[7]);
    guMtxXFMF(mtx, in[6], in[7], in[8], &out[2], &out[5], &out[8]);
    ((u8 *)dst)[0x24] = ((u8 *)src)[0x12];
    ((u8 *)dst)[0x25] = ((u8 *)src)[0x14];
    ((s8 *)dst)[0x26] = ((s8 *)src)[0x13];
    ((u8 *)dst)[0x27] = ((u8 *)src)[0x15];
    return 1;
}


void modelSlotTriBufferRelease(ModelTriBuffer *buf) {
    if (buf->tri_start != NULL && (buf->flags & 1)) {
        heapFree(buf->tri_start);
    }
    buf->flags &= ~1;
}


void modelSlotBuildTriangleBufferThunk(s32 slot, void *data, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale) {
    modelSlotBuildTriangleBuffer(slot, data, x, y, z, rotX, rotY, rotZ, scale);
}

void modelSlotLinkTexAnimTextures(ModelAssetHeader *asset, ModelSlot *slot) {
    TexAnimNode *node;
    s16 *p;
    s32 n;
    s32 idx;
    s32 found;
    s32 key;

    node = ((ModelKindObj *)slot->renderObj)->type2.texAnims;
    if (node != NULL) {
        do {
            key = node->frameTextures[0];
            n = *(s32 *)(asset->quadsOff + (u8 *)asset);
            p = (s16 *)(asset->quadsOff + (u8 *)asset + 4);
            found = 0;
            idx = 0;
            if (n != 0) {
                do {
                    if (key == *p) {
                        found = 1;
                    } else {
                        n--;
                        p += 0x18;
                        idx++;
                    }
                } while (n != 0 && found == 0);
            }
            if (found != 0) {
                node->texture = ((ModelKindObj *)slot->renderObj)->type2.textures[idx];
            } else {
                node->texture = NULL;
            }
            node = node->next;
        } while (node != NULL);
    }
}


void *memcpy(void *, const void *, unsigned int);

void modelSlotInitTexAnimNodes(ModelAssetHeader *asset, ModelSlot *slot, s32 type) {
    s32 count;
    s32 *entry;
    s32 i;
    TexAnimNode *node;
    s32 j;
    TexAnimNode **tail;
    ModelKindObj *obj;
    s32 len1;
    s32 len2;
    s32 *tbl;

    tbl = (s32 *)(asset->texAnimsOff + (u8 *)asset);
    count = *tbl;
    entry = tbl + 1;
    switch (type) {
        case 1:
            tail = &((ModelKindObj *)slot->renderObj)->type1.texAnims;
            if (count != 0) {
                obj = slot->renderObj;
                len1 = dlLengthToEndDL(obj->type1.displayListA);
                obj->type1.displayListACopy = heapAlloc(len1);
                memcpy(obj->type1.displayListACopy, obj->type1.displayListA, len1);
                len2 = dlLengthToEndDL(obj->type1.displayListB);
                obj->type1.displayListBCopy = heapAlloc(len2);
                memcpy(obj->type1.displayListBCopy, obj->type1.displayListB, len2);
            }
            break;
        case 2:
            tail = &((ModelKindObj *)slot->renderObj)->type2.texAnims;
            break;
    }
    for (i = 0; i < count; i++) {
        node = heapAlloc(sizeof(TexAnimNode));
        node->animMode = 1;
        node->frameChanged = 0;
        node->findSecond = entry[1];
        node->frameTicks = entry[2];
        node->tick = 0;
        node->frame = 0;
        node->frameCount = entry[3];
        node->frameTextures[0] = entry[0];
        for (j = 0; j < node->frameCount - 1; j++) {
            node->frameTextures[j + 1] = entry[4 + j];
        }
        node->keepBuffers = entry[0x20];
        if (gGlobalOverlayFlags & 0x2000000) {
            node->keepBuffers = 0;
        }
        node->textureBuffer = NULL;
        node->textureBuffer2 = NULL;
        node->scrollS = 0;
        node->scrollT = 0;
        node->scrollSpeedX = 0;
        node->scrollSpeedY = 0;
        node->lastFrame = -1;
        if (type == 1) {
            dlFindTextureCommands(obj->type1.displayListA, len1, entry[0], entry[1], &node->cmdsA[0].texCmd, &node->cmdsA[0].texCmd2, &node->cmdsA[0].primColorCmd);
            dlFindTextureCommands(obj->type1.displayListACopy, len1, entry[0], entry[1], &node->cmdsA[1].texCmd, &node->cmdsA[1].texCmd2, &node->cmdsA[1].primColorCmd);
            dlFindTextureCommands(obj->type1.displayListB, len2, entry[0], entry[1], &node->cmdsB[0].texCmd, &node->cmdsB[0].texCmd2, &node->cmdsB[0].primColorCmd);
            dlFindTextureCommands(obj->type1.displayListBCopy, len2, entry[0], entry[1], &node->cmdsB[1].texCmd, &node->cmdsB[1].texCmd2, &node->cmdsB[1].primColorCmd);
        }
        *tail = node;
        tail = &node->next;
        entry += 0x21;
    }
    *tail = NULL;
}



void modelSlotSetNodeScrollSpeed(s32 id, s16 node, s16 speedX, s16 speedY) {
    modelSlotAccessNodeScrollSpeed(id, node, speedX, speedY, &speedX, &speedY, 0);
}

void modelSlotGetNodeScrollSpeed(s32 id, s16 node, s16 *speedXOut, s16 *speedYOut) {
    s16 unusedX;
    s16 unusedY;

    modelSlotAccessNodeScrollSpeed(id, node, unusedX, unusedY, speedXOut, speedYOut, 1);
}


void modelSlotAccessNodeScrollSpeed(s32 id, s16 node, s16 speedX, s16 speedY, s16 *speedXOut, s16 *speedYOut, u8 get) {
    s32 idx;
    ModelKindObj *obj;

    idx = hashTableLookup(id);
    obj = gModelSlots[idx].renderObj;
    if (gModelSlots[idx].modelKind != 1) {
        if (gModelSlots[idx].modelKind == 2) {
            modelNodeAccessScrollSpeed(obj->type2.texAnims, node, speedX, speedY, speedXOut, speedYOut, get);
        }
    } else {
        modelNodeAccessScrollSpeed(obj->type1.texAnims, node, speedX, speedY, speedXOut, speedYOut, get);
    }
}

void modelNodeAccessScrollSpeed(TexAnimNode *list, s16 node, s16 speedX, s16 speedY, s16 *speedXOut, s16 *speedYOut, u8 get) {
    node--;
    while (list != NULL && node != 0) {
        list = list->next;
        node--;
    }
    if (list != NULL) {
        if (get != 0) {
            *speedXOut = list->scrollSpeedX;
            *speedYOut = list->scrollSpeedY;
        } else {
            list->scrollSpeedX = speedX;
            list->scrollSpeedY = speedY;
        }
    }
}

void modelSlotSetNodeAnimMode(s32 id, s16 node, u8 mode) {
    modelSlotAccessNodeAnimMode(id, node, mode, &mode, 0);
}

void modelSlotGetNodeAnimMode(s32 id, s16 node, u8 *modeOut) {
    u8 unusedMode;

    modelSlotAccessNodeAnimMode(id, node, unusedMode, modeOut, 1);
}


void modelSlotAccessNodeAnimMode(s32 id, s16 node, u8 mode, u8 *modeOut, u8 get) {
    s32 idx;
    ModelKindObj *obj;

    idx = hashTableLookup(id);
    obj = gModelSlots[idx].renderObj;
    if (gModelSlots[idx].modelKind != 1) {
        if (gModelSlots[idx].modelKind == 2) {
            modelNodeAccessAnimMode(obj->type2.texAnims, node, mode, modeOut, get);
        }
    } else {
        modelNodeAccessAnimMode(obj->type1.texAnims, node, mode, modeOut, get);
    }
}

void modelNodeAccessAnimMode(TexAnimNode *list, s16 node, u8 mode, u8 *modeOut, u8 get) {
    node--;
    while (list != NULL && node != 0) {
        list = list->next;
        node--;
    }
    if (list != NULL) {
        if (get != 0) {
            *modeOut = list->animMode;
        } else {
            list->animMode = mode;
        }
    }
}


void modelSlotSetNodeFrame(s32 id, s16 node, s32 frame, s32 tick) {
    s32 idx;
    ModelKindObj *obj;

    idx = hashTableLookup(id);
    obj = gModelSlots[idx].renderObj;
    if (gModelSlots[idx].modelKind != 1) {
        if (gModelSlots[idx].modelKind == 2) {
            modelNodeSetFrame(obj->type2.texAnims, node, frame, tick);
        }
    } else {
        modelNodeSetFrame(obj->type1.texAnims, node, frame, tick);
    }
}

void modelNodeSetFrame(TexAnimNode *list, s16 node, s32 frame, s32 tick) {
    node--;
    while (list != NULL && node != 0) {
        list = list->next;
        node--;
    }
    if (list != NULL) {
        if (frame != list->frame || tick != list->tick) {
            list->frameChanged = 1;
        }
        list->frame = frame;
        list->tick = tick;
    }
}

void dlFindTextureCommands(u32 *dl, s32 len, s32 addr, s32 findSecond, TexImageCmdSpan **imgOut, TexImageCmdSpan **img2Out, u32 **primOut) {
    s32 found;
    u32 opcode;

    *imgOut = NULL;
    *img2Out = NULL;
    *primOut = NULL;
    found = 0;
    if (len != 0) {
        do {
            opcode = *dl >> 24;
            len -= 8;
            if (opcode == 0xFD && addr == dl[1]) {
                *imgOut = (TexImageCmdSpan *)dl;
                found = 1;
            }
            dl += 2;
        } while (found == 0 && len != 0);
    }
    if (findSecond != 0) {
        found = 0;
        if (len != 0) {
            do {
                opcode = *dl >> 24;
                len -= 8;
                if (opcode == 0xFD && addr == dl[1]) {
                    *img2Out = (TexImageCmdSpan *)dl;
                    found = 1;
                }
                dl += 2;
            } while (found == 0 && len != 0);
        }
        if (len != 0) {
            found = 0;
            do {
                opcode = *dl >> 24;
                len -= 8;
                if (opcode == 0xFA) {
                    *primOut = dl;
                    found = 1;
                }
                dl += 2;
            } while (found == 0 && len != 0);
        }
    }
}


s32 dlLengthToEndDL(u32 *dl) {
    s32 len;
    s32 found;
    u32 opcode;

    len = 0;
    found = 0;
    do {
        opcode = *dl >> 24;
        len += 8;
        if (opcode == 0xDF) {
            found = 1;
        }
        dl += 2;
    } while (found == 0);
    return len;
}


typedef struct ModelQuadData {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s16 x[4];
    /* 0x0C */ s16 y[4];
    /* 0x14 */ s16 z[4];
    /* 0x1C */ s16 uv[4][2];
    /* 0x2C */ u8 texWidth; // RenderQuadModelObj.texWidth..texFormat
    /* 0x2D */ u8 texHeight;
    /* 0x2E */ u8 texSize;
    /* 0x2F */ u8 texFormat;
} ModelQuadData;

void modelQuadBuildOutput(ModelSlot *owner, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 yOffset) {
    RenderQuadModelObj *out;
    ModelQuadData *q;
    ModelAssetHeader *data;
    s32 i;
    s32 j;
    s16 sum;

    data = owner->asset;
    out = owner->renderObj;
    q = (ModelQuadData *)(data->quadsOff + (u8 *)data + 4);
    out->x = x;
    out->y = y;
    out->z = z;
    out->scale = scale;
    out->yOffset = yOffset;
    out->quadCount = *(s32 *)(data->quadsOff + (u8 *)data);
    sum = 0;
    out->verts = heapAlloc(out->quadCount << 6);
    for (i = 0; i < out->quadCount; i++) {
        out->texWidth = q->texWidth;
        out->texHeight = q->texHeight;
        out->texSize = q->texSize;
        out->texFormat = q->texFormat;
        for (j = 0; j < 4; j++) {
            out->verts[(i << 2) + j].v.ob[0] = q->x[j];
            out->verts[(i << 2) + j].v.ob[1] = q->y[j];
            out->verts[(i << 2) + j].v.ob[2] = q->z[j];
            out->verts[(i << 2) + j].v.tc[0] = q->uv[j][0];
            out->verts[(i << 2) + j].v.tc[1] = q->uv[j][1];
            sum += q->y[j];
        }
        q++;
    }
    out->averageY = sum / (out->quadCount * 4);
}



// RenderQuadModelObj (kind 2) as the texture loaders see it; same offsets and names. Kept as a view because
// modelSlotLoadAssetTextures/modelSlotClearAssetTextures/modelSlotFreeAssetTextures/modelSlotFreeAssetEntry take it.
typedef struct ModelSlotAsset {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ Mtx *frameMtx0;
    /* 0x18 */ Mtx *frameMtx1;
    /* 0x1C */ Vtx *verts;
    /* 0x20 */ u8 quadCount;
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ void *textures[4];
    /* 0x34 */ void *palettes[4];
    /* 0x44 */ u8 pad44[0xC];
    /* 0x50 */ TexAnimNode *texAnims;
} ModelSlotAsset;

void modelSlotLoadAssetTextures(ModelAssetHeader *asset, ModelSlotAsset *textures) {
    u8 type;
    s32 i;
    s16 *src;

    src = (s16 *)(asset->quadsOff + (u8 *)asset + 4);
    if (*(s32 *)(asset->texAnimsOff + (u8 *)asset) != 0) {
        type = 7;
    } else {
        type = 0x19;
    }
    for (i = 0; i < textures->quadCount; i++) {
        textures->textures[i] = assetLoad(type, src[0], 1, 0);
        if (src[1] != -1) {
            textures->palettes[i] = assetLoad(type, src[1], 1, 0);
        } else {
            textures->palettes[i] = NULL;
        }
        src += 0x18;
    }
}

void modelSlotClearAssetTextures(ModelAssetHeader *asset, ModelSlotAsset *textures) {
    s32 i;

    for (i = 0; i < textures->quadCount; i++) {
        textures->textures[i] = NULL;
        textures->palettes[i] = NULL;
    }
}


void modelSlotsFreeAll(void) {
    s32 i;
    s32 n;

    n = gModelSlotCount;
    for (i = 0; i < n; i++) {
        modelSlotFreeByIndex(0, 0);
    }
    hashTableClear();
}


void modelSlotFreeByIndex(slot, isId)
s32 slot;
u8 isId;
{
    s16 entryId;
    s16 purgeOut;
    u8 removed;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    mapPurgeNodeList(gModelSlots[slot].renderObj, &purgeOut, 0);
    renderEntryRemove(0, gModelSlots[slot].renderObj, 2, &removed);
    dynamicBufferFree(&gModelSlots[slot].boxBuffer);
    modelSlotTriBufferRelease(&gModelSlots[slot].triBuffer);
    modelPosNodeListFree(gModelSlots[slot].attachPoints);
    modelLinkedNodeListFree(gModelSlots[slot].nodePosList);
    modelSlotFree(gModelSlots[slot].anim);
    modelSlotFreeTexAnimNodes(&gModelSlots[slot]);
    if (gModelSlots[slot].csState != NULL) {
        csStateFree(gModelSlots[slot].csState);
    }
    gCsModelIds[gModelSlots[slot].csModelId] = -1;
    modelEmitterDisable(gModelSlots[slot].id);
    entryId = gModelSlots[slot].id;
    hashTableRemove(entryId);
    proxPathRemoveOwner(entryId);
    if (gModelSlots[slot].csState != NULL) {
        if (gModelSlots[slot].csState->sfxSources[0] != -1) {
            sfxSlotFreeSource(gModelSlots[slot].csState->sfxSources[0]);
        }
        if (gModelSlots[slot].csState->sfxSources[1] != -1) {
            sfxSlotFreeSource(gModelSlots[slot].csState->sfxSources[1]);
        }
    }
    if (slot + 1 != gModelSlotCount) {
        hashTableInsert(gModelSlots[gModelSlotCount - 1].id, slot);
    }
    memcpy(&gModelSlots[slot], &gModelSlots[gModelSlotCount - 1], sizeof(ModelSlot));
    gModelSlotCount -= 1;
}


void modelSlotGetTransformVectors(s32 slot, f32 *xOut, f32 *yOut, f32 *zOut, f32 *rotXOut, f32 *rotYOut, f32 *rotZOut, f32 *scaleOut, f32 *yOffsetOut, u8 isId) {
    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    *xOut = gModelSlots[slot].x;
    *yOut = gModelSlots[slot].y;
    *zOut = gModelSlots[slot].z;
    *rotXOut = gModelSlots[slot].rotX;
    *rotYOut = gModelSlots[slot].rotY;
    *rotZOut = gModelSlots[slot].rotZ;
    *scaleOut = gModelSlots[slot].scale;
    *yOffsetOut = gModelSlots[slot].yOffset;
}

extern u8 gPlayerCount;

void modelSlotTransformBoundsAndNodes(s32 slot, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 yOffset, u8 setPos, u8 setRot, u8 setScale, u8 setYOffset, u8 isId) {
    RenderQuadModelObj *quad;
    ModelType1Obj *model;
    s16 purgeOut;
    u8 flag;
    u8 sel;
    u8 i;
    s32 pad;

    flag = 0;
    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    if (setYOffset) {
        gModelSlots[slot].yOffset = yOffset;
        switch (gModelSlots[slot].modelKind) {
            case 2:
                quad = gModelSlots[slot].renderObj;
                quad->yOffset = yOffset;
                break;
            case 1:
                model = gModelSlots[slot].renderObj;
                model->yOffset = yOffset;
                break;
        }
    }
    if (setPos) {
        gModelSlots[slot].x = x;
        gModelSlots[slot].y = y;
        gModelSlots[slot].z = z;
        switch (gModelSlots[slot].modelKind) {
            case 2:
                quad = gModelSlots[slot].renderObj;
                quad->x = x;
                quad->y = y;
                quad->z = z;
                break;
            case 1:
                model = gModelSlots[slot].renderObj;
                model->x = x;
                model->y = y;
                model->z = z;
                break;
        }
    }
    if (setRot) {
        gModelSlots[slot].rotX = rotX;
        gModelSlots[slot].rotY = rotY;
        gModelSlots[slot].rotZ = rotZ;
        if (gModelSlots[slot].modelKind == 1) {
            model = gModelSlots[slot].renderObj;
            model->rotX = rotX;
            model->rotY = rotY;
            model->rotZ = rotZ;
        }
    }
    if (setScale) {
        gModelSlots[slot].scale = scale;
        switch (gModelSlots[slot].modelKind) {
            case 2:
                quad = gModelSlots[slot].renderObj;
                quad->scale = scale;
                break;
            case 1:
                model = gModelSlots[slot].renderObj;
                model->scale = scale;
                break;
        }
    }
    if ((setPos || setYOffset) && mapPurgeNodeList(gModelSlots[slot].renderObj, &purgeOut, 0)) {
        renderEntryAddOrUpdate(0, gModelSlots[slot].modelKind, gModelSlots[slot].renderObj, gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, gModelSlots[slot].asset->maxDist, gModelSlots[slot].id, 0, purgeOut, 2);
    }
    if (setPos || setYOffset || setRot) {
        modelEmitterSetPosition(gModelSlots[slot].id, gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, gModelSlots[slot].scale, gModelSlots[slot].rotY);
    }
    if (gModelSlots[slot].csState != NULL) {
        sel = gModelSlots[slot].csState->collisionRebuildMode;
        switch (sel) {
            case 0:
                flag = 1;
                break;
            case 2:
                if (gPlayerSlots == NULL) {
                    break;
                }
                for (i = 0; i < gPlayerCount; i++) { if (gPlayerSlots[i].active == 0) { continue; } flag |= collisionCheckBoundingBoxY(&gModelSlots[slot].triBuffer.bbox, gPlayerSlots[i].actor->y) != 0 && collisionCheckBoundingBoxXZ(&gModelSlots[slot].triBuffer.bbox, gPlayerSlots[i].actor->x, gPlayerSlots[i].actor->z) != 0; } // LAYOUT: keeps loop-latch loads after flag truncation
                break;
            case 1:
                if (gPlayerSlots == NULL) {
                    break;
                }
                for (i = 0; i < gPlayerCount; i++) { if (gPlayerSlots[i].active == 0) { continue; } flag |= collisionCheckBoundingBoxXZ(&gModelSlots[slot].triBuffer.bbox, gPlayerSlots[i].actor->x, gPlayerSlots[i].actor->z); } // LAYOUT: keeps loop-latch loads after flag truncation
                break;
            case 3:
            case 4:
                if (gPlayerSlots != NULL) {
                    flag = activeActorBoxOverlapTest(gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, gModelSlots[slot].csState->collisionRebuildRadiusX, gModelSlots[slot].csState->collisionRebuildRadiusY, gModelSlots[slot].csState->collisionRebuildRadiusZ, sel == 3 ? 0xEF : 1);
                }
                break;
        }
    }
    if (flag != 0) {
        collisionTransformNode(slot, gModelSlots[slot].asset, gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, gModelSlots[slot].rotX, gModelSlots[slot].rotY, gModelSlots[slot].rotZ, gModelSlots[slot].scale);
        modelSlotBuildTriangleBufferThunk(slot, gModelSlots[slot].asset, gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, gModelSlots[slot].rotX, gModelSlots[slot].rotY, gModelSlots[slot].rotZ, gModelSlots[slot].scale);
    }
    modelSlotBuildVertPosList(slot, gModelSlots[slot].asset, gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, gModelSlots[slot].rotX, gModelSlots[slot].rotY, gModelSlots[slot].rotZ, gModelSlots[slot].scale, 1);
    modelSlotBuildNodePosList(slot, gModelSlots[slot].asset, gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, gModelSlots[slot].rotX, gModelSlots[slot].rotY, gModelSlots[slot].rotZ, gModelSlots[slot].scale, 1);
}

s32 activeActorBoxOverlapTest(f32 x, f32 y, f32 z, s16 radiusX, s16 radiusY, s16 radiusZ, u16 mask) {
    s32 i;
    Actor *a;
    f32 minX;
    f32 minY;
    f32 minZ;
    f32 maxX;
    f32 maxY;
    f32 maxZ;

    minX = x - radiusX;
    maxX = x + radiusX;
    minY = y - radiusY;
    maxY = y + radiusY;
    minZ = z - radiusZ;
    maxZ = z + radiusZ;
    for (i = 0; i < gActiveActorCount; i++) {
        a = gActiveActors[i].actor;
        if (a->collisionFlags & mask) {
            if (minX <= a->x && minY <= a->y && minZ <= a->z &&
                a->x <= maxX && a->y <= maxY && a->z <= maxZ) {
                return 1;
            }
        }
    }
    return 0;
}


void modelSlotSetDistanceOverride(s32 slot, u8 isId, u8 value) {
    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    mapSetDistanceOverride(gModelSlots[slot].renderObj, value);
}


void modelSlotFreeTexAnimNodes(ModelSlot *slot) {
    TexAnimNode *node;
    ModelKindObj *owner;
    ModelSlotSubNode *nodeList;
    TexAnimNode *cur;

    switch (slot->modelKind) {
        case 2:
            owner = slot->renderObj;
            node = owner->type2.texAnims;
            nodeList = owner->type2.subNode;
            modelSlotFreeAssetEntry(slot->asset, slot->renderObj);
            break;
        case 1:
            owner = slot->renderObj;
            node = owner->type1.texAnims;
            nodeList = owner->type1.subNode;
            modelSegmentFreeUnusedTextures(slot, slot->asset, slot->renderObj);
            break;
    }
    if (node != NULL) {
        do {
            if (node->textureBuffer != NULL) {
                assetFreeBuffer(node->textureBuffer, 0x9DB, 7);
            }
            if (node->textureBuffer2 != NULL) {
                assetFreeBuffer(node->textureBuffer2, 0x9DC, 7);
            }
            cur = node;
            node = node->next;
            heapFree(cur);
        } while (node != NULL);
    }
    if (nodeList != NULL) {
        assetFreeBuffer(nodeList->asset, 0x9E5, 7);
        heapFree(nodeList);
    }
}

typedef struct ModelNodeBufferOwner {
    /* 0x00 */ u8 pad0[0x50];
    /* 0x50 */ TexAnimNode *type2TexAnims;
    /* 0x54 */ u8 pad54[0x64];
    /* 0xB8 */ TexAnimNode *type1TexAnims;
} ModelNodeBufferOwner;

void modelSlotFreeTexAnimBuffers(ModelNodeBufferOwner *owner, u8 type) {
    TexAnimNode *node;

    if (type != 1) {
        if (type == 2) {
            node = owner->type2TexAnims;
        } else {
            return;
        }
    } else {
        node = owner->type1TexAnims;
    }
    if (node != NULL) {
        do {
            if (node->textureBuffer != NULL && node->keepBuffers == 0) {
                assetFreeBuffer(node->textureBuffer, 0xA09, 7);
                node->textureBuffer = NULL;
            }
            if (node->textureBuffer2 != NULL && node->keepBuffers == 0) {
                assetFreeBuffer(node->textureBuffer2, 0xA0E, 7);
                node->textureBuffer2 = NULL;
            }
            node = node->next;
        } while (node != NULL);
    }
}

void modelSlotFreeAssetTextures(ModelSlotAsset *asset, u8 type) {
    ModelSlotAsset *base;
    s32 i;
    void *q;

    if (type == 2 && asset->texAnims == NULL) {
        base = asset; // FAKE: alias of asset; base (s3) carries quadCount while the empty guards keep asset live in s1
        for (i = 0; i < base->quadCount; i++) {
            q = asset->textures[i];
            if (q != NULL) {
                assetFreeBuffer(q, 0xA2B, 7);
                asset->textures[i] = NULL;
            }
            if (base) {} // FAKE: dead test steers register colouring
            q = asset->palettes[i];
            if (q != NULL) {
                assetFreeBuffer(q, 0xA30, 7);
                if (base && base && base) {} // FAKE: dead test steers register colouring
                asset->palettes[i] = NULL;
            }
        }
    }
}

void modelSlotFreeNestedBuffer(s32 slotIndex, u8 isId) {
    ModelSlotSubNode *buffer;
    ModelSlotSubNode **listPtr;
    ModelSlot *slot;

    if (isId == 1) {
        slotIndex = hashTableLookup(slotIndex);
    }
    slot = &gModelSlots[slotIndex];
    switch (slot->modelKind) {
        case 2:
            listPtr = &((ModelKindObj *)slot->renderObj)->type2.subNode;
            break;
        case 1:
            listPtr = &((ModelKindObj *)slot->renderObj)->type1.subNode;
            break;
    }
    if (listPtr != NULL) {
        buffer = *listPtr;
        if (buffer != NULL) {
            assetFreeBuffer(buffer->asset, 0xA56, 7);
            heapFree(buffer);
            *listPtr = NULL;
        }
    }
}


void modelSlotFreeAssetEntry(void *asset, ModelSlotAsset *textures) {
    s32 i;

    for (i = 0; i < textures->quadCount; i++) {
        if (textures->textures[i] != NULL) {
            assetFreeBuffer(textures->textures[i], 0xA69, 7);
        }
        if (textures->palettes[i] != NULL) {
            assetFreeBuffer(textures->palettes[i], 0xA6A, 7);
        }
    }
    assetFreeBuffer(asset, 0xA6E, 7);
    heapFreeDeferred(textures->verts);
    heapFreeDeferred(textures);
    heapFreeDeferred(textures->frameMtx0);
    heapFreeDeferred(textures->frameMtx1);
}

typedef struct DisplayListFreeRecord {
    /* 0x00 */ s32 headStart;
    /* 0x04 */ s32 headEnd;
    /* 0x08 */ s32 tailStart;
    /* 0x0C */ s32 tailEnd;
    /* 0x10 */ ModelAssetHeader *asset;
    /* 0x14 */ s32 freeFrame;
    /* 0x18 */ struct DisplayListFreeRecord *next;
} DisplayListFreeRecord;

extern DisplayListFreeRecord *gDisplayListFreeQueue;

void displayListFreeQueueReset(void) {
    gDisplayListFreeQueue = NULL;
}

void displayListFreeQueueAdd(s32 headStart, s32 headEnd, s32 tailStart, s32 tailEnd, ModelAssetHeader *counter) {
    DisplayListFreeRecord *rec;
    DisplayListFreeRecord *old;

    rec = heapAlloc(sizeof(DisplayListFreeRecord));
    old = gDisplayListFreeQueue;
    gDisplayListFreeQueue = rec;
    rec->next = old;
    rec->headStart = headStart;
    rec->headEnd = headEnd;
    rec->tailStart = tailStart;
    rec->tailEnd = tailEnd;
    rec->freeFrame = gFrameCounter + 2;
    rec->asset = counter;
}



void displayListFreeQueueProcess(void) {
    DisplayListFreeRecord *cur;
    DisplayListFreeRecord *prev;
    DisplayListFreeRecord *next;

    cur = gDisplayListFreeQueue;
    prev = NULL;
    if (cur != NULL) {
        do {
            next = cur->next;
            if (gFrameCounter == cur->freeFrame) {
                cur->asset->textureRefCount--;
                dlFreeUnusedTextures(cur->headStart, cur->headEnd, 0, 0, cur->asset->textureRefCount == 0);
                dlFreeUnusedTextures(cur->tailStart, cur->tailEnd, 0, 1, cur->asset->textureRefCount == 0);
                assetFreeBuffer(cur->asset, 0xAB1, 7);
                if (prev == NULL) {
                    gDisplayListFreeQueue = cur->next;
                } else {
                    prev->next = cur->next;
                }
                heapFree(cur);
            } else {
                prev = cur;
            }
            cur = next;
        } while (next != NULL);
    }
}

typedef struct DisplayListCmd {
    /* 0x0 */ u32 w0;
    /* 0x4 */ s32 w1;
} DisplayListCmd;

// ModelType1Obj (ModelSlot.unk20, kind 1) with its display-list pointers held as integer addresses.
typedef struct ModelType1ObjAddrs {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ u32 displayListA;
    /* 0xA4 */ u32 displayListACopy;
    /* 0xA8 */ u32 displayListB;
    /* 0xAC */ u32 displayListBCopy;
    /* 0xB0 */ u32 segmentData;
    /* 0xB4 */ s16 modelType;
    /* 0xB6 */ s16 id;
    /* 0xB8 */ TexAnimNode *texAnims;
    /* 0xBC */ s32 subNode;
    /* 0xC0 */ u8 padC0[3];
    /* 0xC3 */ u8 light;
} ModelType1ObjAddrs;

// RenderQuadModelObj (kind 2) with its texture table read as texture keys.
typedef struct RenderQuadTexKeysView {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ s32 textures[8];
    /* 0x44 */ u8 pad44[0xC];
    /* 0x50 */ TexAnimNode *texAnims;
} RenderQuadTexKeysView;



void modelSegmentFreeUnusedTextures(ModelSlot *slot, ModelAssetHeader *asset, ModelType1ObjAddrs *seg) {
    TexAnimNode *nodes;
    u32 head, tail;
    u8 flag;

    nodes = seg->texAnims;
    head = seg->displayListB - seg->displayListA;
    tail = seg->segmentData - seg->displayListB;
    head >>= 3;
    tail >>= 3;
    if (nodes == NULL && (slot->flags & 0x20)) {
        flag = 0;
    } else {
        flag = 1;
    }
    if (slot->flags & 0x20) {
        if (flag) {
            asset->textureRefCount -= 1;
            dlFreeUnusedTextures(seg->displayListA, seg->displayListA + head * 8, seg->texAnims, 0, 0);
            dlFreeUnusedTextures(seg->displayListB, seg->displayListB + tail * 8, seg->texAnims, 1, 0);
            nodes = seg->texAnims;
        } else {
            displayListFreeQueueAdd(seg->displayListA, seg->displayListA + head * 8, seg->displayListB, seg->displayListB + tail * 8, asset);
            nodes = seg->texAnims;
        }
    }
    if (nodes != NULL) {
        dlFreeUnusedTextures(seg->displayListACopy, seg->displayListACopy + head * 8, nodes, 0, 0);
        dlFreeUnusedTextures(seg->displayListBCopy, seg->displayListBCopy + tail * 8, seg->texAnims, 1, 0);
        heapFreeDeferred((void *)seg->displayListACopy);
        heapFreeDeferred((void *)seg->displayListBCopy);
    }
    if (flag != 0) {
        assetFreeBuffer(asset, 0xAF7, 7);
    }
    heapFreeDeferred(seg);
}

void dlFreeUnusedTextures(start, end, nodes, tail, restore)
DisplayListCmd *start;
DisplayListCmd *end;
TexAnimNode *nodes;
u8 tail;
u8 restore;
{
    u32 w;
    u32 found;
    TexAnimNode *node;
    s32 bstValue;
    s32 bstNode;

    for (; start != end; start++) {
        w = start->w0;
        found = 0;
        if ((w >> 24) == 0xFD) {
            for (node = nodes; found == 0 && node != NULL; node = node->next) {
                switch (tail) {
                    case 0:
                        if ((TexImageCmdSpan *)start == node->cmdsA[0].texCmd) {
                            found = 1;
                        }
                        if ((TexImageCmdSpan *)start == node->cmdsA[0].texCmd2) {
                            found = 1;
                        }
                        if ((TexImageCmdSpan *)start == node->cmdsA[1].texCmd) {
                            found = 1;
                        }
                        if ((TexImageCmdSpan *)start == node->cmdsA[1].texCmd2) {
                            found = 1;
                        }
                        break;
                    case 1:
                        if ((TexImageCmdSpan *)start == node->cmdsB[0].texCmd) {
                            found = 1;
                        }
                        if ((TexImageCmdSpan *)start == node->cmdsB[0].texCmd2) {
                            found = 1;
                        }
                        if ((TexImageCmdSpan *)start == node->cmdsB[1].texCmd) {
                            found = 1;
                        }
                        if ((TexImageCmdSpan *)start == node->cmdsB[1].texCmd2) {
                            found = 1;
                        }
                        break;
                }
            }
            if (found == 0) {
                if (restore) {
                    assetRefBstLookupByHash(start->w1, &bstValue, &bstNode);
                }
                assetFreeBuffer((void *)start->w1, 0xB27, 7);
                if (restore) {
                    start->w1 = bstNode;
                }
            }
        }
    }
}

extern u8 gViewportCount;

void modelSlotInitFromAsset(ModelSlot *slot, s32 type) {
    ModelAssetHeader *hdr;
    ModelType1ObjAddrs *seg;
    s32 pad;
    void *objData;
    RenderQuadModelObj *obj;

    if (modelTypeNeedsPrivateAsset(type) != 0) {
        slot->asset = assetLoad(4, type, 1, 1);
    } else {
        slot->asset = assetLoad(4, type, 1, 0);
    }
    hdr = slot->asset;
    slot->flags = 0;
    slot->modelKind = hdr->modelKind;
    slot->modelType = type;
    if (hdr->modelKind != 1) {
        if (hdr->modelKind == 2) {
            obj = heapAlloc(0x60);
            objData = obj;
            obj->modelType = type;
            obj->texAnims = NULL;
            obj->subNode = NULL;
            obj->id = -1;
            obj->flags = 0;
            obj->light = 0;
            obj->frameMtx0 = heapAlloc(gViewportCount << 6);
            obj->frameMtx1 = heapAlloc(gViewportCount << 6);
        }
    } else {
        seg = heapAlloc(0xC8);
        objData = seg;
        seg->modelType = type;
        seg->texAnims = 0;
        seg->displayListA = hdr->displayListAOff + (u32)hdr;
        seg->displayListB = hdr->displayListBOff + (u32)hdr;
        seg->segmentData = hdr->segmentDataOff + (u32)hdr;
        seg->subNode = 0;
        seg->id = -1;
        seg->light = 0;
    }
    slot->renderObj = objData;
}

f32 modelTypeGetDefaultScale(s32 type) {
    s32 pad;
    f32 *asset;
    f32 result;

    asset = assetLoad(4, type, 1, 0);
    result = asset[1];
    assetFreeBuffer(asset, 0xB87, 7);
    return result;
}

u8 modelTypeNeedsPrivateAsset(s32 type) {
    s32 pad;
    s32 *asset;
    s32 result;

    asset = assetLoad(4, type, 1, 0);
    if (*asset & 8) {
        result = 1;
    } else {
        result = 0;
    }
    assetFreeBuffer(asset, 0xBA3, 7);
    return result;
}

void modelSlotReplaceSegment6Commands(ModelSlot *slot) {
    u32 start;
    ModelType1ObjAddrs *seg;
    u32 head;
    u32 tail;

    seg = slot->renderObj;
    tail = seg->segmentData - seg->displayListB;
    start = seg->displayListA;
    head = seg->displayListB - start;
    head >>= 3;
    tail >>= 3;
    renderReplaceSegment6Commands((Gfx *)start, (Gfx *)start + head);
    renderReplaceSegment6Commands((Gfx *)seg->displayListB, (Gfx *)seg->displayListB + tail);
}

void dlFreeSegmentCommandTextures(DisplayListCmd *start, DisplayListCmd *end, u8 restore) {
    s32 pad;
    u32 tag;
    s32 bstValue;
    s32 bstNode;

    if (start != end) {
        do {
            tag = start->w0 >> 24;
            if (tag == 0xFD) {
                if (restore) {
                    assetRefBstLookupByHash(start->w1, &bstValue, &bstNode);
                }
                assetFreeBuffer((void *)start->w1, 0xBCD, 7);
                if (restore) {
                    start->w1 = bstNode;
                }
            }
            start++;
        } while (start != end);
    }
}



void modelSlotsStepSegmentCommands(void) {
    u32 start;
    ModelType1ObjAddrs *seg;
    u32 head;
    u32 tail;
    u8 restore;
    ModelAssetHeader *asset;

    if (gModelSlotCount != 0) {
        gModelSegmentStepIndex++;
        if (gModelSegmentStepIndex >= gModelSlotCount) {
            gModelSegmentStepIndex = 0;
        }
        asset = gModelSlots[gModelSegmentStepIndex].asset;
        if (asset->flags & 0x10) {
            if ((gModelSlots[gModelSegmentStepIndex].flags & 0x20) && gFrameCounter != asset->lastUsedFrame) {
                gModelSlots[gModelSegmentStepIndex].flags &= ~0x20;
                asset->textureRefCount--;
                if (asset->textureRefCount != 0) {
                    restore = 0;
                } else {
                    restore = 1;
                }
                seg = gModelSlots[gModelSegmentStepIndex].renderObj;
                tail = seg->segmentData - seg->displayListB;
                start = seg->displayListA;
                head = seg->displayListB - start;
                head >>= 3;
                tail >>= 3;
                dlFreeSegmentCommandTextures((DisplayListCmd *)start, (DisplayListCmd *)start + head, restore);
                dlFreeSegmentCommandTextures((DisplayListCmd *)seg->displayListB, (DisplayListCmd *)seg->displayListB + tail, restore);
            }
        }
    }
}





void modelSlotResolveAssetTextures(ModelSlot *slot, u8 forceLoad, u8 force) {
    ModelType1ObjAddrs *seg;
    ModelAssetHeader *obj;
    ModelSlotAsset *textures;
    u32 head;
    u32 cmds;
    u32 tail;
    TexAnimNode *node;
    u8 res;

    obj = slot->asset;
    seg = slot->renderObj;
    textures = slot->renderObj;
    slot->asset->lastUsedFrame = gFrameCounter; // FAKE: store spelled as a re-read through slot->unk24 instead of obj; the target has ONE lw v0,36(a0) at 0x24 for both obj and the store (sw t8,8(v0) at 0x34, move s1,v0 at 0x40): the spelling only numbers that load candidate ahead of the slot->unk20 load
    if (!(slot->flags & 0x20)) {
        if (!(obj->flags & 0x10) || force != 0) {
            slot->flags |= 0x20;
            obj->textureRefCount++;
            switch (obj->modelKind) {
                case 1:
                    tail = seg->segmentData - seg->displayListB;
                    cmds = seg->displayListA;
                    head = seg->displayListB - cmds;
                    head >>= 3;
                    tail >>= 3;
                    node = ((ModelType1ObjAddrs *)slot->renderObj)->texAnims; // ORIG: the target reloads slot (lw t6,72(sp) at 0x90) and slot->unk20 (lw t7,32(t6) at 0xA0) for texAnims instead of reading seg (s0)
                    res = dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)cmds + head, node, force);
                    cmds = seg->displayListB;
                    res |= dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)cmds + tail, node, force);
                    if (node != NULL) {
                        cmds = seg->displayListACopy;
                        res |= dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)cmds + head, node, force);
                        cmds = seg->displayListBCopy;
                        res |= dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)cmds + tail, node, force);
                    }
                    if (res != 0) {
                        obj->flags &= ~0x10;
                    }
                    return;
            }
            if (textures->texAnims != NULL || forceLoad != 0) {
                modelSlotLoadAssetTextures(obj, textures);
            } else {
                modelSlotClearAssetTextures(obj, textures);
            }
        }
    }
}


u8 dlResolveNodeTextures(DisplayListCmd *start, DisplayListCmd *end, TexAnimNode *nodes, u8 keep) {
    u32 w;
    u32 tag;
    u8 result;
    s32 found;
    TexAnimNode *node;

    result = 0;
    if (start != end) {
        do {
            w = start->w0;
            found = 0;
            tag = w >> 24;
            if (0xFD == tag) {
                node = nodes;
                if (node != NULL) {
                    do {
                        if (start->w1 == node->frameTextures[0]) {
                            found = 1;
                        } else {
                            node = node->next;
                        }
                    } while (found == 0 && node != NULL);
                }
                if (found == 0) {
                    start->w1 = (s32)assetLoad(0x19, start->w1, keep == 0, 0);
                    if (start->w1 & 7) {
                        start->w1 &= ~0xF;
                        result = 1;
                    }
                }
            }
            start++;
        } while (start != end);
    }
    return result;
}

// ModelType1Obj (kind 1) as renderModelAnimatedSlot draws it: per-gfx-buffer matrices and display-list copies.
typedef struct ModelType1RenderView {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ f32 rotX;
    /* 0x14 */ f32 rotY;
    /* 0x18 */ f32 rotZ;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ Mtx frameMtx[2];
    /* 0xA0 */ Gfx *displayListsA[2];
    /* 0xA8 */ Gfx *displayListsB[2];
    /* 0xB0 */ void *segmentData;
    /* 0xB4 */ s16 modelType;
    /* 0xB6 */ s16 id;
    /* 0xB8 */ void *texAnims;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ s16 maxDist;
    /* 0xC2 */ u8 fullBright;
    /* 0xC3 */ u8 light;
    /* 0xC4 */ u8 surfaceType;
    /* 0xC5 */ u8 mapFlags;
} ModelType1RenderView;

Gfx *renderModelAnimatedSlot(ModelType1RenderView *obj, Gfx *gfx, f32 camX, f32 camY, f32 camZ, u8 useLight, s16 lightArg, s32 unused) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 dx;
    f32 dy;
    f32 dz;
    u8 sel;
    ModelData *animBuffers;
    f32 scale;
    CsState *model;
    s32 pad;
    u8 red;
    u8 green;
    u8 blue;
    s16 alpha;
    s16 slotIdx;
    s32 pad2;
    f32 dist;
    f32 drawDist;

    if (useLight) {
        dx = gPlayerSlots[gCurrentPlayerIndex].eyeX - obj->x;
        dy = gPlayerSlots[gCurrentPlayerIndex].eyeY - obj->y;
        dz = gPlayerSlots[gCurrentPlayerIndex].eyeZ - obj->z;
        dx *= dx;
        dy *= dy;
        dz *= dz;
        dist = sqrtf(dx + dy + dz);
        drawDist = renderScaleDistanceByFov(obj->maxDist);
        if (obj->mapFlags & 1) {
            drawDist = obj->maxDist;
        }
        if (drawDist < dist) {
            return gfx;
        }
    }
    if (obj->light != 0) {
        lightQueueKeyframed(obj->light, obj->id, obj->x, obj->y, obj->z, obj->maxDist, dist / drawDist, lightArg);
    }
    if (obj->modelType == 0 || obj->modelType == 0x241) {
        return gfx;
    }
    if (obj->modelType == 0x74 || obj->modelType == 0x288 || obj->modelType == 0x290) {
        obj->rotY += 10.0;
    }
    guScaleF(mtx, obj->scale, obj->scale, obj->scale);
    if (obj->rotX != 0.0) {
        guRotateF(tmpMtx, obj->rotX, 1.0f, 0.0f, 0.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
    }
    if (obj->rotY != 0.0) {
        guRotateF(tmpMtx, obj->rotY, 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
    }
    if (obj->rotZ != 0.0) {
        guRotateF(tmpMtx, obj->rotZ, 0.0f, 0.0f, 1.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
    }
    guTranslateF(tmpMtx, obj->x, obj->y, obj->z);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &obj->frameMtx[gGfxBufferIndex]);
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 8, osVirtualToPhysical(obj->segmentData));
    if (obj->id != -1) {
        slotIdx = hashTableLookup(obj->id);
        modelSlotResolveAssetTextures(&gModelSlots[slotIdx], 0, 1);
        animBuffers = gModelSlots[slotIdx].anim;
        if (playerSlotMatchesSizeMask(gModelSlots[slotIdx].asset->flags, gCurrentPlayerIndex) != 0) {
            return gfx;
        }
    } else {
        animBuffers = NULL;
    }
    if (animBuffers != NULL) {
        gSPSegment(gfx++, 9, osVirtualToPhysical(animBuffers->frames[gGfxBufferIndex]));
    }
    gSPMatrix(gfx++, osVirtualToPhysical(&obj->frameMtx[gGfxBufferIndex]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    if (obj->texAnims != NULL) {
        sel = gGfxBufferIndex;
        texAnimUpdateNodes((ModelType1ObjAddrs *)obj);
    } else {
        sel = 0;
    }
    gSPSegment(gfx++, 10, osVirtualToPhysical(obj->displayListsA[sel]));
    gSPClearGeometryMode(gfx++, G_FOG | G_CULL_BOTH);
    if (useLight && obj->fullBright == 0) {
        f32 yOffset;

        model = gModelSlots[slotIdx].csState;
        if (model != NULL) {
            yOffset = model->lightYOffset;
        } else {
            yOffset = 0.0f;
        }
        lightSampleColorAtPosition(obj->x, obj->y + yOffset, obj->z, 0, &red, &green, &blue, lightArg);
        scale = obj->surfaceType / 15.0f;
        red = red * scale;
        green = green * scale;
        blue = blue * scale;
    } else {
        blue = 0xFF;
        green = 0xFF;
        red = 0xFF;
    }
    gDPSetPrimColor(gfx++, 0, 0xFF, red, green, blue, 0xFF);
    if (useLight) {
        if (obj->id != -1 && (model = gModelSlots[slotIdx].csState) != NULL && model->alphaOverride == 1) {
            csStepAlpha(model);
            alpha = gModelSlots[slotIdx].csState->alpha;
        } else {
            renderCalcPlayerDistanceAlpha(obj->x, obj->y, obj->z, obj->maxDist, obj->modelType, &alpha);
            if (obj->id != -1) {
                model = gModelSlots[slotIdx].csState;
                if (model != NULL && gViewportCount == 1) {
                    model->alphaTarget = alpha;
                }
            }
            if (obj->id != -1) {
                model = gModelSlots[slotIdx].csState;
                if (model != NULL) {
                    csStepAlpha(model);
                }
            }
            if (obj->id != -1) {
                model = gModelSlots[slotIdx].csState;
                if (model != NULL && gViewportCount == 1) {
                    alpha = model->alpha;
                }
            }
        }
    } else {
        alpha = 0xFF;
    }
    if (alpha != 0) {
        if (obj->id != -1) {
            u8 fl = gModelSlots[slotIdx].flags;
            if (fl != 0) {
                if ((gModelSlots[slotIdx].flags & 0x8) && gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 2) {
                    alpha = 0x64;
                }
                if ((gModelSlots[slotIdx].flags & 0x2) && gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 3) {
                    alpha = 0x64;
                }
                if ((gModelSlots[slotIdx].flags & 0x4) && gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 5) {
                    alpha = 0x64;
                }
                if ((gModelSlots[slotIdx].flags & 0x1) && gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 6) {
                    alpha = 0x64;
                }
                if ((gModelSlots[slotIdx].flags & 0x10) && gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 4) {
                    alpha = 0x64;
                }
            }
        }
        gfx = renderSetSegment6AndFog(gfx, alpha, 0);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(obj->displayListsA[sel]));
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(obj->displayListsB[sel]));
    }
    { s32 pad6; } // FAKE: block-scoped pad keeps the gfx spill slot at 88(sp) (Q0251/Q0331); pre-existing, now tagged
    gDPPipeSync(gfx++);
    gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
    return gfx;
}

#define WRITE_GFX_PAIR(a, b) { Gfx *_g = (Gfx *)(gfx++); _g->words.w0 = (a); _g->words.w1 = (b); }

extern u8 gRenderSetupKind;
extern void *gRenderLoadedTexture;
extern s32 gModelQuadDrawCount;


Gfx *renderModelQuadGfx(RenderQuadModelObj *obj, Gfx *gfx, f32 camX, f32 camY, f32 camZ, u8 useLight, s16 lightArg, s32 unused) {
    f32 modelMtx[4][4];
    f32 tmpMtx[4][4];
    f32 angleX;
    f32 angleY;
    f32 angleZ;
    s32 texA;
    s32 texB;
    u8 dualTex;
    s16 primLod;
    f32 dx;
    f32 screenX;
    f32 screenY;
    f32 dist;
    f32 dy;
    f32 dz;
    s32 pad0;
    f32 scale;
    s16 limit;
    s32 i;
    s32 vtxOffset;
    s16 pad16;
    s16 alpha;
    u8 usedTlut;
    u8 opaque;
    u8 red;
    u8 green;
    u8 blue;
    Mtx *mtx;
    s32 pad[1];

    vtxOffset = 0;
    usedTlut = 0;
    if (useLight) {
        dx = camX - obj->x;
        dy = camY - obj->y;
        dz = camZ - obj->z;
        dx *= dx;
        dy *= dy;
        dz *= dz;
        dist = sqrtf(dx + dy + dz);
        limit = renderScaleDistanceByFov(obj->maxDist);
        if (limit < dist) {
            return gfx;
        }
    }
    if (obj->light != 0) {
        lightQueueKeyframed(obj->light, obj->id, obj->x, obj->y, obj->z, obj->maxDist, dist / limit, lightArg);
    }
    if (useLight) {
        if (mapPointOutsideClipBounds(obj->x, obj->y, obj->z, 0, 0) != 0) {
            return gfx;
        }
    } else {
        limit = -0x8000;
        dist = 1.0f;
    }
    if (obj->flags & 0x10) {
        return gfx;
    }
    if (obj->flags & 8) {
        camProjectToScreen(obj->x, obj->y, obj->z, &screenX, &screenY, 0, 1.0f, gCurrentPlayerIndex);
        mapSearchTableAddProbe(obj, screenX, screenY, dist);
        if (mapSearchTableGetValue(obj) != 0) {
            return gfx;
        }
    }
    gModelQuadDrawCount += 1;
    if (obj->textures[0] == NULL) {
        modelSlotLoadAssetTextures(gModelSlots[(s16)hashTableLookup(obj->id)].asset, (ModelSlotAsset *)obj);
    }
    modelCalcFacingAngles(obj->x, obj->y, obj->z, camX, camY, camZ, &angleX, &angleY, &angleZ, obj->flags & 4);
    guTranslateF(modelMtx, 0.0f, -obj->averageY, 0.0f);
    if (angleX != 0.0) {
        guRotateF(tmpMtx, angleX, 1.0f, 0.0f, 0.0f);
        guMtxCatF(modelMtx, tmpMtx, modelMtx);
    }
    if (angleY != 0.0) {
        guRotateF(tmpMtx, angleY, 0.0f, 1.0f, 0.0f);
        guMtxCatF(modelMtx, tmpMtx, modelMtx);
    }
    if (obj->scale != 1.0) {
        guScaleF(tmpMtx, obj->scale, obj->scale, obj->scale);
        guMtxCatF(modelMtx, tmpMtx, modelMtx);
    }
    guTranslateF(tmpMtx, obj->x, obj->y + obj->averageY * obj->scale, obj->z);
    guMtxCatF(modelMtx, tmpMtx, modelMtx);
    switch (gGfxBufferIndex) {
    case 0:
        mtx = obj->frameMtx0 + gCurrentPlayerIndex;
        break;
    case 1:
        mtx = obj->frameMtx1 + gCurrentPlayerIndex;
        break;
    }
    guMtxF2L(modelMtx, mtx);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, ~0);
    WRITE_GFX_PAIR(0xDA380000, osVirtualToPhysical(mtx));
    if (dist < (limit * 3) / 4) {
        opaque = 1;
        alpha = 0xFF;
    } else {
        opaque = 0;
        alpha = ((dist - (limit * 3) / 4) / ((f32)limit - (limit * 3) / 4)) * 255.0f;
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        alpha = 0xFF - alpha;
    }
    modelKongVisibilityCheck(obj->modelType, &opaque, &alpha);
    if (useLight && obj->fullBright == 0) {
        lightSampleColorAtPosition(obj->x, obj->y, obj->z, 0, &red, &green, &blue, lightArg);
        scale = obj->surfaceType / 15.0f;
        red = red * scale;
        green = green * scale;
        blue = blue * scale;
    } else {
        red = green = blue = 0xFF;
    }
    for (i = 0; i < obj->quadCount; i++) {
        texAnimFindNodeFrame((RenderQuadTexKeysView *)obj, i, &texA, &texB, &dualTex, &primLod);
        gDPPipeSync(gfx++);
        if (obj->flags & 2) {
            if (opaque != 0) {
                gSPSetOtherMode(gfx++, G_SETOTHERMODE_L, 3, 29, 0x0C193078);
            } else {
                gSPSetOtherMode(gfx++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
            }
        } else if (obj->flags & 1) {
            gSPSetOtherMode(gfx++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
        } else {
            gSPSetOtherMode(gfx++, G_SETOTHERMODE_L, 3, 29, 0x0C184240);
        }
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, 20, 2, 0x100000);
        if ((obj->flags & 1) || (obj->flags & 2)) {
            WRITE_GFX_PAIR(0xD9FFFFFF, 0x210005);
        } else {
            WRITE_GFX_PAIR(0xD9FFFFFF, 0x210004);
        }
        gDPSetPrimColor(gfx++, 0, primLod, red, green, blue, alpha);
        switch (dualTex) {
        case 0:
            WRITE_GFX_PAIR(0xFC1197FF, 0xFFFFFE38);
            gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            if (gRenderSetupKind != 2 || texA != (s32)gRenderLoadedTexture) {
                switch (obj->texSize) {
                case 0:
                    gDPLoadTextureBlock_4b(gfx++, texA + 0x80000000, obj->texFormat, obj->texWidth, obj->texHeight, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    if (obj->texFormat == 2) {
                        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj->palettes[i]);
                        gDPTileSync(gfx++); gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                        gDPLoadSync(gfx++);
                        gDPLoadTLUTCmd(gfx++, G_TX_LOADTILE, 15); gDPPipeSync(gfx++);
                        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
                        usedTlut = 1;
                    }
                    break;
                case 1:
                    gDPLoadTextureBlock(gfx++, texA + 0x80000000, obj->texFormat, G_IM_SIZ_8b, obj->texWidth, obj->texHeight, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    if (obj->texFormat == 2) {
                        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj->palettes[i]);
                        gDPTileSync(gfx++); gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                        gDPLoadSync(gfx++);
                        gDPLoadTLUTCmd(gfx++, G_TX_LOADTILE, 255); gDPPipeSync(gfx++);
                        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
                        usedTlut = 1;
                    }
                    break;
                case 2:
                    gDPLoadTextureBlock(gfx++, texA + 0x80000000, obj->texFormat, G_IM_SIZ_16b, obj->texWidth, obj->texHeight, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 3:
                    gDPLoadTextureBlock(gfx++, texA + 0x80000000, obj->texFormat, G_IM_SIZ_32b, obj->texWidth, obj->texHeight, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                }
            }
            gRenderLoadedTexture = (void *)texA;
            break;
        case 1:
            WRITE_GFX_PAIR(0xFC272C03, 0x1F1C93F8);
            gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, 16, 1, 0);
            gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texA);
            gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadSync(gfx++);
            gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, ((obj->texWidth * obj->texHeight * 2) >> 1) - 1, CALC_DXT(obj->texWidth, 2));
            gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texB);
            gDPTileSync(gfx++);
            gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadSync(gfx++);
            gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, ((obj->texWidth * obj->texHeight * 2) >> 1) - 1, CALC_DXT(obj->texWidth, 2));
            gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, obj->texWidth / 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
            gDPSetTileSize(gfx++, G_TX_RENDERTILE, 2, 2, ((obj->texWidth - 1) << 2) + 2, ((obj->texHeight - 1) << 2) + 2);
            gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, obj->texWidth / 4, 0x100, 1, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
            gDPSetTileSize(gfx++, 1, 2, 2, ((obj->texWidth - 1) << 2) + 2, ((obj->texHeight - 1) << 2) + 2);
            gRenderLoadedTexture = NULL;
            break;
        }
        gSPVertex(gfx++, osVirtualToPhysical(obj->verts + vtxOffset), 4, 0);
        gSP2Triangles(gfx++, 0, 1, 2, 0, 0, 2, 3, 0);
        vtxOffset += 4;
        gRenderSetupKind = 2;
    }
    gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
    gDPPipeSync(gfx++);
    gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, 20, 2, 0);
    gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    if (usedTlut != 0) {
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, 14, 2, 0);
    }
    gSPSetOtherMode(gfx++, G_SETOTHERMODE_L, 2, 1, 0);
    return gfx;
}

void modelKongVisibilityCheck(s16 type, u8 *visibleOut, s16 *alphaOut) {
    s32 hit = 0;
    PlayerState *playerState;

    switch (type) {
    case 0x24:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 3) {
            hit = 1;
        }
        break;
    case 0x1D:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 2) {
            hit = 1;
        }
        break;
    case 0x1C:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 5) {
            hit = 1;
        }
        break;
    case 0x23:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 4) {
            hit = 1;
        }
        break;
    case 0x27:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 6) {
            hit = 1;
        }
        break;
    case 0xD:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 2) {
            hit = 1;
        }
        break;
    case 0xA:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 3) {
            hit = 1;
        }
        break;
    case 0x16:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 5) {
            hit = 1;
        }
        break;
    case 0x1E:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 4) {
            hit = 1;
        }
        break;
    case 0x1F:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 6) {
            hit = 1;
        }
        break;
    case 0x2B:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 2) {
            hit = 1;
        }
        break;
    case 0x208:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 3) {
            hit = 1;
        }
        break;
    case 0x207:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 5) {
            hit = 1;
        }
        break;
    case 0x205:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 4) {
            hit = 1;
        }
        break;
    case 0x206:
        if (gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 6) {
            hit = 1;
        }
        break;
    case 0x11:
        if ((gPlayerInventoryTable[gCurrentPlayerIndex].kong[gPlayerCharacterId[gCurrentPlayerIndex]].weaponFlags & 3) != 3) {
            hit = 1;
        }
        break;
    case 0x8F:
        if (!(gPlayerInventoryTable[gCurrentPlayerIndex].kong[gPlayerCharacterId[gCurrentPlayerIndex]].weaponFlags & 1)) {
            hit = 1;
        }
        break;
    case 0x98:
        playerState = gPlayerSlots[gCurrentPlayerIndex].actor->customState;
        if (!(playerState->stateFlags2 & 1)) {
            hit = 1;
        }
        break;
    case 0x8E:
        playerState = gPlayerSlots[gCurrentPlayerIndex].actor->customState;
        if (!(playerState->stateFlags2 & 2)) {
            hit = 1;
        }
        break;
    }
    if (hit != 0) {
        *visibleOut = 0;
        if (*alphaOut > 100) {
            *alphaOut = 100;
        }
    }
}

void modelSlotSetTranslucent(s32 slot, u8 isId, u8 enable) {
    RenderQuadModelObj *obj;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    obj = gModelSlots[slot].renderObj;
    if (enable != 0) {
        obj->flags |= 1;
    } else {
        obj->flags &= ~1;
    }
    obj->flags &= ~2;
}

void texAnimUpdateNodes(ModelType1ObjAddrs *seg) {
    s32 pad;
    s32 texA;
    s32 texB;
    u8 dualTex;
    s16 primLod;
    TexAnimNode *node;
    s32 *dst;

    node = seg->texAnims;
    if (node != NULL) {
        do {
            texAnimNodeUpdateBuffers(node, &texA, &texB, &dualTex, &primLod);
            if (node->cmdsA[gGfxBufferIndex].texCmd != NULL) {
                node->cmdsA[gGfxBufferIndex].texCmd->texAddr = texA;
                if (dualTex == 0) {
                    dst = &node->cmdsA[gGfxBufferIndex].texCmd->tileSizeW0; // ORIG: the target materialises the tile-size word address in v0 (addiu v0,v0,0x30 at 0x7eb8 and 0x7f18) and stores through it (sw 0(v0)); a field store folds 0x30 into the sw
                    *dst = (node->scrollS << 12) | 0xF2000000 | node->scrollT;
                }
            }
            if (node->cmdsB[gGfxBufferIndex].texCmd != NULL) {
                node->cmdsB[gGfxBufferIndex].texCmd->texAddr = texA;
                if (dualTex == 0) {
                    dst = &node->cmdsB[gGfxBufferIndex].texCmd->tileSizeW0;
                    *dst = (node->scrollS << 12) | 0xF2000000 | node->scrollT;
                }
            }
            if (gFrameCounter != node->lastFrame) {
                node->scrollS += node->scrollSpeedX;
                if (node->scrollS >= 0x1000) {
                    node->scrollS = 0;
                }
                if (node->scrollS < 0) {
                    node->scrollS = 0xFFF;
                }
                node->scrollT += node->scrollSpeedY;
                if (node->scrollT >= 0x1000) {
                    node->scrollT = 0;
                }
                if (node->scrollT < 0) {
                    node->scrollT = 0xFFF;
                }
            }
            if (dualTex != 0) {
                if (node->cmdsA[gGfxBufferIndex].texCmd2 != NULL) {
                    node->cmdsA[gGfxBufferIndex].texCmd2->texAddr = texB;
                }
                if (node->cmdsB[gGfxBufferIndex].texCmd2 != NULL) {
                    node->cmdsB[gGfxBufferIndex].texCmd2->texAddr = texB;
                }
                if (node->cmdsA[gGfxBufferIndex].primColorCmd != NULL) {
                    *node->cmdsA[gGfxBufferIndex].primColorCmd = primLod + 0xFA000000;
                }
                if (node->cmdsB[gGfxBufferIndex].primColorCmd != NULL) {
                    *node->cmdsB[gGfxBufferIndex].primColorCmd = primLod + 0xFA000000;
                }
            }
            node->lastFrame = gFrameCounter;
            node = node->next;
        } while (node != NULL);
    }
}


void texAnimFindNodeFrame(RenderQuadTexKeysView *owner, s32 index, s32 *texAOut, s32 *texBOut, u8 *dualOut, s16 *lodOut) {
    TexAnimNode *node;
    s32 key;
    s32 found;

    node = owner->texAnims;
    if (node != NULL) {
        key = owner->textures[index];
        found = 0;
        while (node != NULL && found == 0) {
            if (key == (s32)node->texture) {
                found = 1;
            } else {
                node = node->next;
            }
        }
        if (found != 0) {
            texAnimNodeUpdateBuffers(node, texAOut, texBOut, dualOut, lodOut);
            node->lastFrame = gFrameCounter;
            return;
        }
        *dualOut = 0;
        *texAOut = key;
        return;
    }
    *dualOut = 0;
    *texAOut = owner->textures[index];
}



void texAnimNodeUpdateBuffers(TexAnimNode *node, s32 *texAOut, s32 *texBOut, u8 *dualOut, s16 *lodOut) {
    s32 advanced;
    s32 frameB;
    s32 frameA;
    void *oldBufB;
    void *oldBufA;

    if (gFrameCounter == node->lastFrame) {
        advanced = 0;
    } else {
        advanced = (u8)texAnimNodeAdvance(node, &frameB, &frameA);
    }
    if (advanced != 0 || node->textureBuffer == NULL) {
        oldBufB = node->textureBuffer;
        if (node->findSecond != 0) {
            oldBufA = node->textureBuffer2;
            if (oldBufA == NULL || node->frameChanged != 0) {
                if (oldBufB != NULL) {
                    assetFreeBuffer(oldBufB, 0xFCB, 7);
                }
                if (node->keepBuffers != 0) {
                    assetSetLoadPersistent();
                }
                node->textureBuffer = assetLoad(7, node->frameTextures[frameB], 0, 0);
                oldBufA = node->textureBuffer2;
                if (oldBufA != NULL) {
                    assetFreeBuffer(oldBufA, 0xFCE, 7);
                }
                if (node->keepBuffers != 0) {
                    assetSetLoadPersistent();
                }
                node->textureBuffer2 = assetLoad(7, node->frameTextures[frameA], 0, 0);
            } else {
                if (oldBufB != NULL) {
                    assetFreeBuffer(oldBufB, 0xFD5, 7);
                }
                oldBufA = node->textureBuffer2;
                node->textureBuffer = oldBufA;
                if (node->keepBuffers != 0) {
                    assetSetLoadPersistent();
                }
                node->textureBuffer2 = assetLoad(7, node->frameTextures[frameA], 0, 0);
            }
        } else {
            if (oldBufB != NULL) {
                assetFreeBuffer(oldBufB, 0xFDF, 7);
            }
            if (node->keepBuffers != 0) {
                assetSetLoadPersistent();
            }
            node->textureBuffer = assetLoad(7, node->frameTextures[frameB], 0, 0);
        }
    }
    node->frameChanged = 0;
    *dualOut = node->findSecond;
    if (node->findSecond != 0) {
        *lodOut = (s16)(((f32)node->tick / (f32)node->frameTicks) * 255.0f);
    }
    *texAOut = (s32)node->textureBuffer;
    *texBOut = (s32)node->textureBuffer2;
}

s32 texAnimNodeAdvance(TexAnimNode *node, s32 *frameOut, s32 *nextFrameOut) {
    s32 result;
    s32 frame;

    result = 0;
    switch (node->animMode) {
        case 1:
            node->tick += 1;
            if (node->tick == node->frameTicks) {
                node->tick = 0;
                node->frame += 1;
                if (node->frame == node->frameCount) {
                    node->frame = 0;
                }
                result = 1;
            }
            break;
        case 0:
            if (node->frameChanged != 0) {
                result = 1;
            }
            break;
        default:
            break;
    }
    *frameOut = node->frame;
    if (node->frame + 1 == node->frameCount) {
        *nextFrameOut = 0;
    } else {
        frame = node->frame;
        *nextFrameOut = frame + 1;
    }
    return result;
}

// Sprite draw node (the ModelSlotSubNode a model owns): chained by spriteListBuildDisplayChain in ascending texture
// key order (spriteListInsertByTexture) so spriteListRender reloads a texture only when the key changes; 0x38 bytes.
typedef struct SpriteDisplayNode {
    /* 0x00 */ u32 key;
    /* 0x04 */ f32 scaleXZ;
    /* 0x08 */ u8 texWidth;
    /* 0x09 */ u8 texHeight;
    /* 0x0A */ u8 texFormat;
    /* 0x0B */ u8 texSize;
    /* 0x0C */ s16 baseHalfWidth;
    /* 0x0E */ s16 baseHalfDepth;
    /* 0x10 */ s16 halfWidth;
    /* 0x12 */ s16 halfDepth;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 y;
    /* 0x1C */ f32 z;
    /* 0x20 */ s16 groundX;
    /* 0x22 */ s16 groundZ;
    /* 0x24 */ s16 animTextureId;
    /* 0x26 */ s16 yaw;
    /* 0x28 */ s16 yawOffset;
    /* 0x2A */ s16 fullAlphaDist;
    /* 0x2C */ s16 maxDist;
    /* 0x2E */ u8 baseAlpha;
    /* 0x2F */ u8 alpha;
    /* 0x30 */ u8 zBuffered;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ struct SpriteDisplayNode *next;
} SpriteDisplayNode; // size = 0x38


void modelCalcFacingAngles(f32 x, f32 y, f32 z, f32 targetX, f32 targetY, f32 targetZ, f32 *angleXOut, f32 *angleYOut, f32 *angleZOut, u8 mode) {
    f32 len;
    s16 angle;
    f32 dx;
    f32 dz;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s16 angle2;
    s32 t;

    if (mode == 0) {
        dx = targetX - x;
        dz = targetZ - z;
        len = sqrtf(dx * dx + dz * dz);
        if ((f64)len < 1.0) {
            len = 1.0f;
        }
        if (x <= targetX && z <= targetZ) {
            angle = (s16)(mathAsinFixed((s32)(((f64)dx * 65535.9) / (f64)len)) >> 4);
        }
        if (x <= targetX && targetZ < z) {
            angle = (s16)((mathAsinFixed((s32)(((f64)(z - targetZ) * 65535.9) / (f64)len)) >> 4) + 0x400);
        }
        if (targetX < x && targetZ < z) {
            angle = (s16)((mathAsinFixed((s32)(((f64)(x - targetX) * 65535.9) / (f64)len)) >> 4) + 0x800);
        }
        if (targetX < x && z <= targetZ) {
            angle = (s16)((mathAsinFixed((s32)(((f64)dz * 65535.9) / (f64)len)) >> 4) + 0xC00);
        }
        *angleZOut = 0.0f;
        *angleXOut = 0.0f;
        *angleYOut = (f32)(((f64)angle / 4095.0) * 360.0);
    } else {
        len = distance3D(targetX, targetY, targetZ, x, y, z);
        if ((f64)len < 0.1) {
            len = 1.0f;
        }
        dz = (targetY - y) / len;
        if (dz > 0.0f) {
            dx = dz;
        } else {
            dx = -dz;
        }
        t = mathAsinFixed((s32)(f32)(s32)((f64)dx * 65536.0)) >> 4;
        angle2 = t;
        if (dz >= 0.0f) {
            angle2 = 0xFFF - angle2;
        }
        *angleXOut = (f32)(((f64)angle2 / 4095.0) * 360.0);
        *angleYOut = mathAngleBetweenPointsRad(targetX, targetZ, x, z) * 57.295776f;
        *angleZOut = 0.0f;
    }
}

// ModelKindObj as spriteListBuildDisplayChain reads it: kind-2 fields at their RenderQuadModelObj offsets, type1* at ModelType1Obj's.
typedef struct ModelSpriteSource {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ f32 type2YOffset;
    /* 0x14 */ f32 type1RotY;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ f32 type1YOffset;
    /* 0x20 */ u8 pad20[0x2E];
    /* 0x4E */ u8 flags;
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ TexAnimNode *texAnims;
    /* 0x54 */ SpriteDisplayNode *subNode;
    /* 0x58 */ u8 pad58[0x60];
    /* 0xB8 */ TexAnimNode *type1TexAnims;
    /* 0xBC */ SpriteDisplayNode *type1SubNode;
} ModelSpriteSource;




SpriteDisplayNode *spriteListBuildDisplayChain(RenderEntry *listA, RenderEntry *listB, f32 camX, f32 camY, f32 camZ) {
    SpriteDisplayNode *result;
    u8 second;
    f32 x;
    f32 y;
    f32 z;
    f32 d2;
    u32 found;
    f32 scale;
    f32 base;
    SpriteDisplayNode *tgt;
    ModelSpriteSource *d;
    ModelSpriteSource *d1;
    TexAnimNode *link;
    s16 idx;
    s16 r;
    f32 angleX;
    f32 angleY;
    f32 angleZ;
    s16 r2;

    result = NULL;
    second = 0;
    if (listA == NULL) {
        listA = listB;
        second = 1;
    }
    if (listA != NULL) {
        do {
            switch (listA->type) {
            case 2:
                d = listA->object;
                if (d->flags & 0x10) {
                    tgt = NULL;
                } else {
                    x = d->x;
                    y = d->y - d->type2YOffset;
                    z = d->z;
                    tgt = d->subNode;
                    link = d->texAnims;
                    modelCalcFacingAngles(x, y, z, camX, camY, camZ, &angleX, &angleY, &angleZ, 0);
                    scale = d->scale;
                }
                break;
            case 1:
                d1 = listA->object;
                tgt = d1->type1SubNode;
                link = d1->type1TexAnims;
                x = d1->x;
                z = d1->z;
                y = d1->y - d1->type1YOffset;
                angleY = d1->type1RotY;
                scale = d1->scale;
                break;
            default:
                tgt = NULL;
                break;
            }
            if (tgt != NULL) {
                r = tgt->maxDist;
                d2 = (camX - x) * (camX - x) + (camY - y) * (camY - y) + (camZ - z) * (camZ - z);
                if (d2 < r * r) {
                    r2 = tgt->fullAlphaDist;
                    if (d2 < r2 * r2) {
                        tgt->alpha = tgt->baseAlpha;
                    } else {
                        d2 = sqrtf(d2);
                        tgt->alpha = (u32)((f32)(u32)tgt->baseAlpha - ((f32)(u32)tgt->baseAlpha * (d2 - (f32)tgt->fullAlphaDist)) / (f32)(tgt->maxDist - tgt->fullAlphaDist));
                    }
                    if (tgt->animTextureId != -1) {
                        found = 0;
                        if (link != NULL) {
                            do {
                                if (link->frameTextures[0] == tgt->animTextureId) {
                                    found = 1;
                                } else {
                                    link = link->next;
                                }
                            } while (found == 0 && link != NULL);
                        }
                        tgt->yaw = angleY;
                        tgt->yaw += link->frame * 0x168 / link->frameCount + link->tick * 360.0 / link->frameCount / link->frameTicks;
                    } else {
                        tgt->yaw = angleY;
                    }
                    tgt->x = x;
                    tgt->yaw += tgt->yawOffset;
                    tgt->y = y;
                    tgt->z = z;
                    tgt->next = NULL;
                    tgt->halfWidth = tgt->baseHalfWidth * scale;
                    tgt->halfDepth = tgt->baseHalfDepth * scale;
                    result = spriteListInsertByTexture(result, tgt);
                }
            }
            listA = listA->next;
            if (listA == NULL && second == 0) {
                listA = listB;
                second = 1;
            }
        } while (listA != NULL);
    }
    return result;
}

SpriteDisplayNode *spriteListInsertByTexture(SpriteDisplayNode *head, SpriteDisplayNode *node) {
    SpriteDisplayNode *prev;
    SpriteDisplayNode *ret;
    s32 inserted;

    prev = NULL;
    ret = head;
    inserted = 0;
    if (head != NULL) {
        do {
            if (head->key >= node->key) {
                inserted = 1;
                node->next = head;
                if (prev != NULL) {
                    prev->next = node;
                } else {
                    ret = node;
                }
            }
            prev = head;
            if (inserted == 0) {
                head = head->next;
            }
        } while (head != NULL && inserted == 0);
    }
    if (inserted == 0) {
        if (prev == NULL) {
            ret = node;
        } else {
            prev->next = node;
        }
    }
    return ret;
}

void modelSlotSetScaleXZ(s16 slot, u8 isId, f32 value) {
    ModelKindObj *obj;
    ModelSlotSubNode *p;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    obj = gModelSlots[slot].renderObj;
    switch (gModelSlots[slot].modelKind) {
    case 2:
        p = obj->type2.subNode;
        break;
    case 1:
        p = obj->type1.subNode;
        break;
    }
    if (p != NULL) {
        p->scaleXZ = value;
    }
}

u32 osVirtualToPhysical(void *);

Gfx *spriteListRender(Gfx *gfx, SpriteDisplayNode *list) {
    s32 lastTex;
    Vtx *vtxs;
    Mtx *mtxs;
    s32 n;
    SpriteDisplayNode *p;
    s32 vtxIdx;
    s32 mtxIdx;
    f32 accum[4][4];
    f32 tmp[4][4];
    s32 flag;

    lastTex = 0;
    vtxIdx = 0;
    mtxIdx = 0;
    flag = 1;

    if (list != NULL) {
        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_1CYCLE);
        gSPClearGeometryMode(gfx++, -1);
        gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
        gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2);
        gDPSetCombineMode(gfx++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
        n = 0;
        p = list;
        if (p != NULL) {
            do {
                p = p->next;
                n++;
            } while (p != NULL);
        }
        vtxs = heapAlloc(n << 6);
        heapFreeDeferred(vtxs);
        mtxs = heapAlloc(n << 6);
        heapFreeDeferred(mtxs);
    }
    if (list != NULL) {
        do {
            gDPPipeSync(gfx++);
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, list->alpha);
            if (list->zBuffered != 0 && flag == 0) {
                gSPSetGeometryMode(gfx++, G_ZBUFFER);
                gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2);
                flag = 1;
            }
            if (list->zBuffered == 0 && flag != 0) {
                gSPClearGeometryMode(gfx++, G_ZBUFFER);
                gDPSetRenderMode(gfx++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
                flag = 0;
            }
            if (list->key != lastTex) {
                switch (list->texSize) {
                case 0:
                    gDPLoadTextureBlock_4b(gfx++, list->key + 0x80000000, list->texFormat, list->texWidth, list->texHeight, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                case 1:
                    gDPLoadTextureBlock(gfx++, list->key + 0x80000000, list->texFormat, G_IM_SIZ_8b, list->texWidth, list->texHeight, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                case 2:
                    gDPLoadTextureBlock(gfx++, list->key + 0x80000000, list->texFormat, G_IM_SIZ_16b, list->texWidth, list->texHeight, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                }
                lastTex = list->key;
            }
            vtxs[vtxIdx].v.tc[0] = 0;
            vtxs[vtxIdx].v.tc[1] = 0;
            vtxs[vtxIdx + 1].v.tc[0] = list->texWidth << 5;
            vtxs[vtxIdx + 1].v.tc[1] = 0;
            vtxs[vtxIdx + 2].v.tc[0] = list->texWidth << 5;
            vtxs[vtxIdx + 2].v.tc[1] = list->texHeight << 5;
            vtxs[vtxIdx + 3].v.tc[0] = 0;
            vtxs[vtxIdx + 3].v.tc[1] = list->texHeight << 5;
            vtxs[vtxIdx].v.ob[1] = 0;
            vtxs[vtxIdx + 1].v.ob[1] = 0;
            vtxs[vtxIdx + 2].v.ob[1] = 0;
            vtxs[vtxIdx + 3].v.ob[1] = 0;
            vtxs[vtxIdx].v.ob[0] = -list->halfWidth;
            vtxs[vtxIdx].v.ob[2] = -list->halfDepth;
            vtxs[vtxIdx + 1].v.ob[0] = list->halfWidth;
            vtxs[vtxIdx + 1].v.ob[2] = -list->halfDepth;
            vtxs[vtxIdx + 2].v.ob[0] = list->halfWidth;
            vtxs[vtxIdx + 2].v.ob[2] = list->halfDepth;
            vtxs[vtxIdx + 3].v.ob[0] = -list->halfWidth;
            vtxs[vtxIdx + 3].v.ob[2] = list->halfDepth;
            guScaleF(accum, list->scaleXZ, 1.0f, list->scaleXZ);
            guRotateF(tmp, list->yaw, 0.0f, 1.0f, 0.0f);
            guMtxCatF(accum, tmp, accum);
            if (list->groundZ < 0x3E8) {
                guRotateF(tmp, -(list->groundX / 4095.0 * 360.0), 0.0f, 1.0f, 0.0f);
                guMtxCatF(accum, tmp, accum);
            }
            guRotateF(tmp, 90.0 - list->groundZ / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
            guMtxCatF(accum, tmp, accum);
            if (list->groundZ < 0x3E8) {
                guRotateF(tmp, list->groundX / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
                guMtxCatF(accum, tmp, accum);
            }
            guTranslateF(tmp, list->x, list->y, list->z);
            guMtxCatF(accum, tmp, accum);
            guMtxF2L(accum, &mtxs[mtxIdx]);
            gSPMatrix(gfx++, osVirtualToPhysical(&mtxs[mtxIdx]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
            mtxIdx++;
            gSPVertex(gfx++, osVirtualToPhysical(&vtxs[vtxIdx]), 4, 0);
            gSP2Triangles(gfx++, 0, 1, 2, 0, 0, 2, 3, 0);
            gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
            vtxIdx += 4;
            list = list->next;
        } while (list != NULL);
    }
    gDPPipeSync(gfx++);
    return gfx;
}


extern s16 gModelPendingQueueCount;
extern s16 gUpdatedCsModelIdCount;
extern u8 gCsTrackedModelCount;

void modelPendingCountsReset(void) {
    gModelPendingQueueCount = 0;
    gUpdatedCsModelIdCount = 0;
    gCsTrackedModelCount = 0;
}

typedef struct ModelPendingQueueEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ s16 key;
    /* 0x4 */ u8 done;
    /* 0x5 */ u8 pad5;
} ModelPendingQueueEntry;

extern ModelPendingQueueEntry gModelPendingQueue[];
extern s16 gUpdatedCsModelIds[];

extern u8 gCsModelUpdateCount;

void modelPendingQueueInsert(RenderEntry *entry, u8 allowDefault) {
    CsState *obj;
    u8 allow;
    s32 pad1;
    s32 pad2;
    s16 idx;
    s32 pad3;
    s32 pad4;
    s32 pad5;
    ModelSlot *slots;
    u8 i;
    f32 *px = NULL, *py = NULL, *pz = NULL; // FAKE: dead initialisers number px/py/pz first (cand 0/3/6) ahead of i*752 (umpy cand 54) and &gPlayerSlots[i] (uixa cand 55); on their 15.00 adjsave tie the earlier candidate wins (Q1551), so px/py/pz take v1/a0/a1 (0x9a54-0x9a70) and umpy/uixa a2/a3 (0x9a2c/0x9a30)
    f32 best;

    allow = 1;
    if (entry->type == 1) {
        idx = hashTableLookup(entry->modelId);
        slots = gModelSlots; obj = slots[idx].csState; // LAYOUT: one-line join lets as1 schedule addu t9,t8,t7 (0x99a0) ahead of the slots home store sw t8,52(sp) (0x99a4); on two lines the store goes first
        if (obj != NULL) {
            switch (obj->updateMode) {
            case 2:
                allow = 0;
                break;
            case 0:
                allow = allowDefault;
                break;
            case 4:
                allow = allowDefault;
            case 3:
            case 6:
                best = 1e8f;
                for (i = 0; i < gViewportCount; i++) {
                    if (gPlayerSlots[i].active == 0) {
                        continue;
                    }
                    switch (obj->updateMode) {
                    case 6:
                        px = &gPlayerSlots[i].actor->x;
                        py = &gPlayerSlots[i].actor->y;
                        pz = &gPlayerSlots[i].actor->z;
                        break;
                    default:
                        px = &gPlayerSlots[i].eyeX;
                        py = &gPlayerSlots[i].eyeY;
                        pz = &gPlayerSlots[i].eyeZ;
                        break;
                    }
                    if ((*px - entry->x) * (*px - entry->x) + (*py - entry->y) * (*py - entry->y) + (*pz - entry->z) * (*pz - entry->z) < best) {
                        best = (*px - entry->x) * (*px - entry->x) + (*py - entry->y) * (*py - entry->y) + (*pz - entry->z) * (*pz - entry->z);
                    }
                }
                allow &= best < obj->updateRangeSq;
                break;
            case 5:
                if (gModelPendingQueueCount == 0x14) return;
                allow = 0;
                gModelPendingQueue[gModelPendingQueueCount].id = entry->modelId;
                gModelPendingQueue[gModelPendingQueueCount].key = obj->queueKey;
                gModelPendingQueue[gModelPendingQueueCount++].done = 0;
                break;
            }
            if (allow != 0) {
                gCsModelUpdateCount++;
                if (gUpdatedCsModelIdCount != 0x46) {
                    gUpdatedCsModelIds[gUpdatedCsModelIdCount] = slots[idx].csModelId;
                    gUpdatedCsModelIdCount++;
                    csStateTickTimers(obj);
                    csStateUpdate(obj, entry->modelId);
                }
            }
        }
    }
}

void modelPendingEntriesProcess(void) {
    u8 found;
    s32 i;
    s32 slot;
    struct CsState *obj;
    u8 any;
    s32 j;

    do {
        any = 0;
        for (i = 0; i < gModelPendingQueueCount; i++) {
            if (gModelPendingQueue[i].done == 0) {
                found = 0;
                for (j = 0; found == 0 && j < gUpdatedCsModelIdCount; j++) {
                    if (gUpdatedCsModelIds[j] == gModelPendingQueue[i].key) {
                        found = 1;
                        any = 1;
                        gModelPendingQueue[i].done = 1;
                        slot = hashTableLookup(gModelPendingQueue[i].id);
                        obj = gModelSlots[slot].csState;
                        if (gUpdatedCsModelIdCount == 0x46) {
                            return;
                        }
                        gUpdatedCsModelIds[gUpdatedCsModelIdCount] = gModelSlots[slot].csModelId;
                        gUpdatedCsModelIdCount++;
                        csStateTickTimers(obj);
                        csStateUpdate(obj, gModelPendingQueue[i].id);
                    }
                }
            }
        }
    } while (any == 1);
}

// One ModelSlot as modelSlotSerializeAll saves it.
typedef struct ModelSlotSerializedOut {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ f32 rotX;
    /* 0x1C */ f32 rotY;
    /* 0x20 */ f32 rotZ;
    /* 0x24 */ f32 yOffset;
    /* 0x28 */ s16 modelType;
    /* 0x2A */ s16 csModelId;
    /* 0x2C */ s16 kind;
    /* 0x2E */ u8 light;
    /* 0x2F */ u8 flags;
} ModelSlotSerializedOut; /* 0x30 */


extern u8 *gSavedMapModelData;
extern u8 gCsVarsDirty[];


void modelSlotSerializeAll(u8 **bufOut, s32 *sizeOut) {
    s32 count;
    s32 size;
    s32 i;
    ModelSlotSerializedOut *out;
    ModelCsVarsRecord *rec;

    count = 0;
    if (gSavedMapModelData != NULL) {
        heapFree(gSavedMapModelData);
    }
    size = gModelSlotCount * sizeof(ModelSlotSerializedOut) + sizeof(s32);
    size += sizeof(s32);
    for (i = 0; i < 0x212; i++) {
        if (gCsVarsDirty[i]) {
            size += sizeof(ModelCsVarsRecord);
            count++;
        }
    }
    size += actorListGetSerializedSize();
    gSavedMapModelData = heapAlloc(size);
    *(s32 *)gSavedMapModelData = gModelSlotCount;
    out = (ModelSlotSerializedOut *)(gSavedMapModelData + 4);
    for (i = 0; i < gModelSlotCount; i++, out++) {
        out->x = gModelSlots[i].x;
        out->y = gModelSlots[i].y;
        out->z = gModelSlots[i].z;
        out->scale = gModelSlots[i].scale;
        out->rotX = gModelSlots[i].rotX;
        out->rotY = gModelSlots[i].rotY;
        out->rotZ = gModelSlots[i].rotZ;
        out->modelType = gModelSlots[i].modelType;
        out->kind = gModelSlots[i].modelKind;
        out->yOffset = gModelSlots[i].yOffset;
        out->csModelId = gModelSlots[i].csModelId;
        switch (out->kind) {
        case 2:
            out->flags = ((RenderQuadModelObj *)gModelSlots[i].renderObj)->flags;
            out->light = ((RenderQuadModelObj *)gModelSlots[i].renderObj)->light;
            break;
        case 1:
            out->flags = 0;
            out->light = ((ModelType1Obj *)gModelSlots[i].renderObj)->light;
            break;
        }
    }
    *(s32 *)out = count;
    rec = (ModelCsVarsRecord *)((s32 *)out + 1);
    for (i = 0; i < 0x212; i++) {
        if (gCsVarsDirty[i] != 0) {
            rec->modelIndex = i;
            memcpy(rec->vars, gModelSlots[hashTableLookup(gCsModelIds[i])].csState->vars, sizeof(rec->vars));
            rec++;
        }
    }
    actorListSerialize((s32 *)rec);
    *bufOut = gSavedMapModelData;
    *sizeOut = size;
}

void modelSlotsPackRecords(u8 **bufOut, s32 *countOut) {
    s32 count = 0;
    s32 i;
    s32 pad;
    u8 *buf = NULL;
    u8 *rec;
    u8 *cur;
    s32 size = 0;
    s32 j;

    for (i = 0; i < gModelSlotCount; i++) {
        if (gModelSlots[i].csState != NULL) {
            if ((gModelSlots[i].asset->saveState != 0 || (gModelSlots[i].csState->modelFlags & 1)) && !(gModelSlots[i].csState->modelFlags & 2)) {
                count++;
                if (gModelSlots[i].anim != NULL) {
                    size += modelSlotDataSize(i);
                }
            }
        }
    }
    if (count != 0) {
        buf = heapAlloc(count * 0x254 + size);
        cur = buf;
        for (i = 0; i < gModelSlotCount; i++) {
            if (gModelSlots[i].csState != NULL) {
                if ((gModelSlots[i].asset->saveState != 0 || (gModelSlots[i].csState->modelFlags & 1)) && !(gModelSlots[i].csState->modelFlags & 2)) {
                    rec = cur;
                    *(s16 *)rec = gModelSlots[i].csModelId;
                    memcpy(rec + 0xCC, gModelSlots[i].csState, 0x9C);
                    if (gModelSlots[i].anim != NULL) {
                        memcpy(rec + 4, gModelSlots[i].anim->entries, 0xC8);
                        rec[0x250] = modelSlotDataSize(i) >> 6;
                        memcpy(rec + 0x254, gModelSlots[i].anim->frames[0], modelSlotDataSize(i));
                    } else {
                        rec[0x250] = 0;
                    }
                    for (j = 1; j != 5; j++) {
                        modelSlotGetNodeScrollSpeed(gModelSlots[i].id, j, (s16 *)(rec + 0x232 + j * 6), (s16 *)(rec + 0x234 + j * 6));
                        modelSlotGetNodeAnimMode(gModelSlots[i].id, j, rec + 0x236 + j * 6);
                    }
                    mapOffsetSlotsGetTargets((f32 *)(rec + 0x168));
                    effectNodeCopyValues((f32 *)(rec + 0x1B8));
                    cur += rec[0x250] * 0x40;
                    cur += 0x254;
                }
            }
        }
    }
    *countOut = count;
    *bufOut = buf;
}

void modelRecordFindAndSet(u8 *records, s32 count, s16 id, s16 value) {
    s32 found = 0;
    s32 i = 0;

    if (count > 0) {
        do {
            if (*(s16 *)records == id) {
                found = 1;
            } else {
                i++;
                records += 0x254 + records[0x250] * 0x40;
            }
        } while (found == 0 && i < count);
    }
    if (found != 0) {
        records[0x117] = value;
        records[0x120] = 1;
    }
}

// The CsState fields modelSlotsApplyRecords keeps across a restored record.
typedef struct ModelSlotStateSnapshot {
    /* 0x00 */ void *heapBlock;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 sfxSources[2];
    /* 0x14 */ u8 pad14[0x80];
    /* 0x94 */ Actor *camPathActor;
    /* 0x98 */ u8 pad98[4];
} ModelSlotStateSnapshot; /* 0x9C */


void modelSlotsApplyRecords(u8 *records, s32 count) {
    s32 k;
    s32 off;
    s32 j;
    s16 id;
    s16 idx;
    u8 tmp[0x14];
    ModelSlotStateSnapshot snap;
    s32 pad[2];

    for (k = 0; k < count; k++) {
        id = gCsModelIds[*(s16 *)records];
        idx = hashTableLookup(id);
        memcpy(&snap, gModelSlots[idx].csState, 0x9C);
        memcpy(gModelSlots[idx].csState, records + 0xCC, 0x9C);
        gModelSlots[idx].csState->data = snap.heapBlock;
        gModelSlots[idx].csState->sfxSources[0] = snap.sfxSources[0];
        gModelSlots[idx].csState->sfxSources[1] = snap.sfxSources[1];
        gModelSlots[idx].csState->camPathActor = snap.camPathActor;
        gModelSlots[idx].csState->stateBytes[0] = gModelSlots[idx].csState->nextStateBytes[0];
        gModelSlots[idx].csState->stateBytes[1] = gModelSlots[idx].csState->nextStateBytes[1];
        gModelSlots[idx].csState->stateBytes[2] = gModelSlots[idx].csState->nextStateBytes[2];
        gModelSlots[idx].csState->runFlags = 0;
        gModelSlots[idx].csState->pathHandle = -1;
        if (gModelSlots[idx].anim != NULL) {
            for (off = 0; off != 0xC8; off += 0x14) {
                memcpy(tmp, (u8 *)gModelSlots[idx].anim + off + 8, 0x14);
                memcpy((u8 *)gModelSlots[idx].anim + off + 8, records + 4 + off, 0x14);
                *(u32 *)((u8 *)gModelSlots[idx].anim + off + 8) = *(u32 *)tmp;
            }
            modelSlotCopyData(records + 0x254, idx);
        }
        for (j = 1; j != 5; j++) {
            modelSlotSetNodeScrollSpeed(id, j, *(s16 *)(records + 0x232 + j * 6), *(s16 *)(records + 0x234 + j * 6));
            modelSlotSetNodeAnimMode(id, j, records[0x236 + j * 6]);
        }
        mapOffsetSlotsSetValues((f32 *)(records + 0x168));
        effectNodeSetValues((f32 *)(records + 0x1B8));
        records += records[0x250] * 0x40;
        records += 0x254;
    }
}

void modelSlotOrFlags(s32 csId, u8 flags) {
    RenderQuadModelObj *obj = gModelSlots[hashTableLookup(gCsModelIds[csId])].renderObj;

    obj->flags |= flags;
}

void modelSlotClearFlags(s32 csId, u8 flags) {
    RenderQuadModelObj *obj = gModelSlots[hashTableLookup(gCsModelIds[csId])].renderObj;

    obj->flags &= ~flags;
}

s32 modelSlotIsAlphaVisible(s16 id) {
    s16 idx = hashTableLookup(id);
    CsState *sub = gModelSlots[idx].csState;

    if (sub != NULL) {
        if (sub->alphaOverride == 1 && sub->alpha == 0) {
            return 0;
        }
        return 1;
    }
    return 1;
}

s16 modelSlotGetType(s16 id) {
    s16 idx = hashTableLookup(id);

    if (idx == -1) {
        return -1;
    }
    return gModelSlots[idx].modelType;
}

