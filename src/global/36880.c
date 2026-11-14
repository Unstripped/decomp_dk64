#include "common.h"
#include "render.h"
#include "actor.h"
#include "model.h"
#include "sched.h"
#define PROTO_SKIP_playerSlotMatchesSizeMask // FAKE: callee prototype steer (owner reads no a2; the extra argument steers it)
#define PROTO_SKIP_renderReplaceSegment6Commands // FAKE: callee prototype steer (owner reads no a2/a3; the extra arguments steer them)
#include "proto/global/104F0.h"
#include "proto/global/119370.h"
#include "proto/global/133A90.h"
#include "proto/global/135D30.h"
#include "proto/global/136820.h"
#include "proto/global/15050.h"
#include "proto/global/201B0.h"
#include "proto/global/2F550.h"
#include "proto/global/35000.h"
#include "proto/global/36880.h"
#include "proto/global/3C10.h"
#include "proto/global/42630.h"
#include "proto/global/54150.h"
#include "proto/global/55B20.h"
#include "proto/global/5E020.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/63810.h"
#include "proto/global/63EC0.h"
#include "proto/global/68EA0.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/8D3E0.h"
#include "proto/global/CEAE0.h"

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

extern ModelSlot *gModelSlots;

extern PlayerStruct *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s32 gCurrentMap;
extern u8 gGfxBufferIndex;


extern u8 D_807F6148;

void modelSkipListClear(void) {
    D_807F6148 = 0;
}

extern s16 D_807F6140[];

void modelSkipListAdd(s16 modelIndex) {
    if (D_807F6148 != 4) {
        D_807F6140[D_807F6148++] = modelIndex;
    }
}

s32 modelSkipListContains(s16 modelIndex) {
    s32 i;

    for (i = 0; i < D_807F6148; i++) {
        if (D_807F6140[i] == modelIndex) {
            return 1;
        }
    }
    return 0;
}

extern s16 D_807F6150[];

s16 modelTypeCountGet(u8 hubIndex) {
    return D_807F6150[hubIndex];
}


extern u8 D_80747D78;

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

    if (D_80747D78 == 0) {
        D_80747D78 = 1;
        for (i = 0; i < 8; i++) {
            D_807F6150[i] = 0;
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
                        D_807F6150[slot]++;
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

extern s16 D_807F614A;

s16 modelSlotsAllocate(s32 map, u8 allocate) {
    switch (map) {
        case 48:
            D_807F614A = 0x212;
            break;
        case 26:
            D_807F614A = 0x1F4;
            break;
        case 38:
            D_807F614A = 0x1F4;
            break;
        case 30:
            D_807F614A = 0x1E5;
            break;
        case 7:
            D_807F614A = 0x1D1;
            break;
        default:
            D_807F614A = 0x1C2;
            break;
    }
    if (allocate != 0) {
        gModelSlots = heapAlloc(D_807F614A * 0x90);
        heapClearBlock(gModelSlots);
    }
    return D_807F614A;
}


extern s32 gModelSlotCount;
extern s16 gCsModelIds[];
extern s32 D_807F6004;

void modelSlotsLoadMap(u8 *mapData, s32 map, u8 checkSaved, u16 saveIndex, u8 saveFile) {
    struct RenderEntry *renderList;
    s32 entryCount;
    ModelAssetEntry *entry;
    u8 *pad;
    s32 i;
    s32 n;
    struct {
        /* 0x00 */ s32 modelIndex;
        /* 0x04 */ u8 vars[0x20];
    } *rec; /* 0x24-byte records after the entry list's s32 count */
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
    D_807F6004 = 0;
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
                    func_8063253C(entry->modelType, map) != 0) {
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
                    modelFlagsApplyState(gCurrentMap, gModelSlots[outCount].csModelId, &gModelSlots[outCount].unk8C);
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
        func_8062D1A8();
        csScriptLoad(assetLoad(0xA, gCurrentMap, 1, 0));
        n = *(s32 *)entry;
        rec = (void *)((s32 *)entry + 1);
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
    /* 0xC2 */ u8 unkC2;
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
            if (node->unk24 == 2) {
                obj = node->unk0;
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
            node = node->unk14;
        } while (node != NULL);
    }
}

s32 func_8063253C(s16 type, s32 map) {
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

extern u8 D_807F6008;

s16 modelSlotAppend(s32 type, f32 x, f32 y, f32 z, f32 yOffset, u8 force) {
    struct RenderEntry *renderList;
    s16 slotId;
    f32 scale;

    renderList = NULL;
    if (gModelSlotCount >= D_807F614A) {
        faultSetMessage(8, 0, 0, 0);
    }
    if (force == 0 && D_807F6008 != 0) {
        return -1;
    }
    scale = func_80636A44(type);
    gModelSlots[gModelSlotCount].x = x;
    gModelSlots[gModelSlotCount].y = y;
    gModelSlots[gModelSlotCount].z = z;
    gModelSlots[gModelSlotCount].scale = scale;
    gModelSlots[gModelSlotCount].rotX = 0.0f;
    gModelSlots[gModelSlotCount].rotY = 0.0f;
    gModelSlots[gModelSlotCount].rotZ = 0.0f;
    gModelSlots[gModelSlotCount].yOffset = y - yOffset;
    gModelSlots[gModelSlotCount].unk8C = 0;
    slotId = modelSlotInit(gModelSlotCount, type, x, y, z, 0.0f, 0.0f, 0.0f, scale, y - yOffset, 1, 0, &renderList);
    mapDistributeEntries(renderList);
    renderEntryListFree(renderList);
    gModelSlots[gModelSlotCount].csModelId = csModelIdTableAlloc(slotId, force);
    gModelSlotCount++;
    return slotId;
}

extern s32 gGlobalOverlayFlags;
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
    gModelSlots[slot].id = D_807F6004;
    hashTableInsert(gModelSlots[slot].id, slot);
    info = gModelSlots[slot].unk24;
    type = info->unk1C;
    if (gGlobalCutsceneFlags & 0x100) {
        info->unk0 &= ~0x10;
    }
    modelApplyMapOverrideValue(modelType, info);
    if (gGlobalOverlayFlags & 0x100) {
        info->unk1E = 0x7D0;
    } else if (gGlobalOverlayFlags & 0x400000) {
        info->unk1E = 0x1F4;
    }
    modelSlotAllocAnimBuffers(&gModelSlots[slot].unk78, info);
    gModelSlots[slot].unk28.unk14 = 0;
    gModelSlots[slot].unk28.unk15 = 0;
    collisionBuildSlotBoxes(slot, info, x, y, z, rotX, rotY, rotZ, scale);
    dynamicBufferFree(&gModelSlots[slot].unk28);
    modelSlotClearTail(slot);
    gModelSlots[slot].unk48.flags = 0;
    modelSlotBuildTriangleBuffer(slot, info, x, y, z, rotX, rotY, rotZ, scale);
    modelSlotTriBufferRelease(&gModelSlots[slot].unk48);
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
            obj2 = gModelSlots[slot].unk20;
            link = &obj2->subNode;
            obj2->id = D_807F6004;
            obj2->flags = flags;
            obj2->light = light;
            obj2->maxDist = info->unk1E;
            obj2->unk5A = info->unk1D;
            obj2->surfaceType = groundSurfaceTypeAt(x, y, z);
        }
    } else {
        obj1 = gModelSlots[slot].unk20;
        obj1->x = x;
        obj1->y = y;
        obj1->z = z;
        obj1->scale = scale;
        obj1->rotX = rotX;
        obj1->rotY = rotY;
        obj1->rotZ = rotZ;
        obj1->yOffset = yOffset;
        obj1->id = D_807F6004;
        obj1->maxDist = info->unk1E;
        obj1->unkC2 = info->unk1D;
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
    gModelSlots[slot].unk86 = type;
    gModelSlots[slot].unk7C = NULL;
    if (info->unk28 != -1) {
        node = heapAlloc(0x38);
        *link = node;
        node->unk34 = 0;
        node->scaleXZ = 1.0f;
        node->baseHalfWidth = info->unk2E;
        node->baseHalfDepth = info->unk30;
        node->texFormat = info->unk34;
        node->texSize = info->unk35;
        node->texWidth = info->unk32;
        node->texHeight = info->unk33;
        node->animTextureId = info->unk2A;
        node->yawOffset = info->unk2C;
        node->fullAlphaDist = info->unk36 * 10;
        node->maxDist = info->unk37 * 10;
        node->baseAlpha = info->unk38;
        node->zBuffered = info->unk39;
        node->asset = assetLoad(0x19, info->unk28, 1, 0);
        modelSlotUpdateGroundCoords(slot, 0);
    }
    *renderListInOut = renderEntryAddOrUpdate(renderList, type, gModelSlots[slot].unk20, x, y, z, info->unk1E, D_807F6004, 0, 0, 0);
    D_807F6004 += 1;
    return D_807F6004 - 1;
}


typedef struct ModelMapIdPair {
    /* 0x0 */ u16 map;
    /* 0x2 */ u16 id;
} ModelMapIdPair;

extern ModelMapIdPair D_80747D50[8];

void modelFlagsApplyMapPairs(s16 id, u8 *flags) {
    s32 i;
    s32 count;
    i = 0;
    count = sizeof(D_80747D50) / sizeof(D_80747D50[0]);
    for (; i < count; i++) {
        if (gCurrentMap == D_80747D50[i].map && id == D_80747D50[i].id) {
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

typedef struct ModelMapIdValueTriple {
    /* 0x0 */ u16 map;
    /* 0x2 */ u16 id;
    /* 0x4 */ u16 val;
} ModelMapIdValueTriple;

extern ModelMapIdValueTriple D_80747D30[5];

void modelApplyMapOverrideValue(s32 id, ModelAssetHeader *info) {
    s32 i;
    s32 count;

    count = sizeof(D_80747D30) / sizeof(D_80747D30[0]);
    for (i = 0; i < count; i++) {
        if (gCurrentMap == D_80747D30[i].map && id == D_80747D30[i].id) {
            info->unk1E = D_80747D30[i].val;
            return;
        }
    }
}


s32 groundSurfaceTypeAt(f32 x, f32 y, f32 z) {
    f32 groundY;

    groundY = y + 10.0f;
    if (collisionCheckGroundAtPoint(x, z, &groundY) != 0) {
        return collisionGetSurfaceType();
    }
    return 0xF;
}


void modelSlotUpdateGroundCoords(s16 slot, u8 isId) {
    s32 padA[4];
    ModelAssetHeader *info;
    ModelSlotSubNode *dst;
    s32 pad;
    f32 groundY;
    s16 groundX;
    s16 groundZ;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    groundY = gModelSlots[slot].y + 20.0f;
    if (collisionCheckGroundAtPoint(gModelSlots[slot].x, gModelSlots[slot].z, &groundY) != 0) {
        collisionGetCoords(&groundX, &groundZ);
        info = gModelSlots[slot].unk24;
        switch (info->unk1C) {
            case 1:
                dst = ((ModelKindObj *)gModelSlots[slot].unk20)->type1.subNode;
                break;
            case 2:
                dst = ((ModelKindObj *)gModelSlots[slot].unk20)->type2.subNode;
                break;
        }
        if (gModelSlots[slot].unk20) {} // FAKE: dead test extends the slot pointer web (steers colouring)
        if (dst != NULL) {
            dst->groundX = groundX;
            dst->groundZ = groundZ;
        }
    }
}

typedef struct ModelPathSeg {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 minAngle;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 maxAngle;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 startNode;
    /* 0x11 */ u8 endNode;
    /* 0x12 */ u8 disabled;
    /* 0x13 */ u8 pad13;
} ModelPathSeg;

typedef struct ModelPathEntry {
    /* 0x00 */ f32 moveSpeed;
    /* 0x04 */ f32 unk4;
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

    count = *(s32 *)(paths->unk5C + (s32)paths);
    tbl = (ModelPathEntry *)((u8 *)(paths->unk5C + (s32)paths) + 4);
    for (i = 1; i <= count; i++) {
        len = 0.0f;
        for (j = 0; j < tbl[i - 1].segCount; j++) {
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].startNode, &ax, &ay, &az);
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].endNode, &bx, &by, &bz);
            len += sqrtf((az - bz) * (az - bz) + ((ax - bx) * (ax - bx) + (ay - by) * (ay - by)));
        }
        proxPathAdd((Actor *)id, 1, i, 1, tbl[i - 1].segCount, 0.0f, len, tbl[i - 1].moveSpeed * scale, tbl[i - 1].attachDist * scale, tbl[i - 1].detachDist * scale, tbl[i - 1].detachDist * scale, tbl[i - 1].endBehavior, tbl[i - 1].unk4, tbl[i - 1].unk8, tbl[i - 1].unk15);
        for (j = 0; j < tbl[i - 1].segCount; j++) {
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].startNode, &ax, &ay, &az);
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].endNode, &bx, &by, &bz);
            proxPathSetSegment((Actor *)id, i, j, tbl[i - 1].segs[j].startNode, tbl[i - 1].segs[j].endNode, sqrtf((az - bz) * (az - bz) + ((ax - bx) * (ax - bx) + (ay - by) * (ay - by))), tbl[i - 1].segs[j].unk0 * scale, tbl[i - 1].segs[j].unk4 * scale, tbl[i - 1].segs[j].disabled, tbl[i - 1].segs[j].minAngle, tbl[i - 1].segs[j].maxAngle, tbl[i - 1].segs[j].unkA, tbl[i - 1].segs[j].unkE);
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
    tail = &gModelSlots[slot].unk70;
    if (mode == 0) {
        *tail = NULL;
    }
    tbl = (s32 *)(verts->unk54 + (s32)verts);
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
    node = gModelSlots[slot].unk74;
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
    verts = gModelSlots[idx].unk24;
    vert = (ModelVert *)((s32 *)(verts->unk58 + (s32)verts) + 1);
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
    tail = &gModelSlots[slot].unk74;
    if (mode == 0) {
        *tail = NULL;
    }
    tbl = (s32 *)(verts->unk58 + (s32)verts);
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
    ModelTriBuffer *p = &gModelSlots[slot].unk48;
    u8 i;

    for (i = 0; i < 2; i++) {
        p->unk25[i] = 0xFF;
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
    p = gModelSlots[slot].unk48.unk25;
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
    s32 off;
    s32 pad2;
    s32 pad3;

    off = slot * 0x90; // FAKE: dead store keeps slot * 0x90 in v0 and the gModelSlots load in v1 (addu t6,v1,v0 / addu s6,v0,v1)
    anim = gModelSlots[slot].unk78;
    lastBone = -1;
    buf = &gModelSlots[slot].unk48;
    if (anim != NULL) {
        animFrame = anim->frames[gGfxBufferIndex];
    } else {
        animFrame = NULL;
    }
    boneTable = data->unk60 + (u8 *)data;
    if (data->unk0 & 4) {
        buf->flags |= 2;
    } else {
        buf->flags &= ~2;
    }
    count = *(s32 *)(data->unk50 + (u8 *)data);
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
    entry = (ModelAssetTri *)(data->unk50 + (u8 *)data + 0x10);
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
    boundsTransformToAabb(mtx, data->unk50 + (u8 *)data + 4, buf);
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

    node = ((ModelKindObj *)slot->unk20)->type2.texAnims;
    if (node != NULL) {
        do {
            key = node->frameTextures[0];
            n = *(s32 *)(asset->unk70 + (u8 *)asset);
            p = (s16 *)(asset->unk70 + (u8 *)asset + 4);
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
                node->texture = ((ModelKindObj *)slot->unk20)->type2.textures[idx];
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

    tbl = (s32 *)(asset->unk6C + (u8 *)asset);
    count = *tbl;
    entry = tbl + 1;
    switch (type) {
        case 1:
            tail = &((ModelKindObj *)slot->unk20)->type1.texAnims;
            if (count != 0) {
                obj = slot->unk20;
                len1 = dlLengthToEndDL(obj->type1.displayListA);
                obj->type1.displayListACopy = heapAlloc(len1);
                memcpy(obj->type1.displayListACopy, obj->type1.displayListA, len1);
                len2 = dlLengthToEndDL(obj->type1.displayListB);
                obj->type1.displayListBCopy = heapAlloc(len2);
                memcpy(obj->type1.displayListBCopy, obj->type1.displayListB, len2);
            }
            break;
        case 2:
            tail = &((ModelKindObj *)slot->unk20)->type2.texAnims;
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
    obj = gModelSlots[idx].unk20;
    if (gModelSlots[idx].unk86 != 1) {
        if (gModelSlots[idx].unk86 == 2) {
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
    obj = gModelSlots[idx].unk20;
    if (gModelSlots[idx].unk86 != 1) {
        if (gModelSlots[idx].unk86 == 2) {
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
    obj = gModelSlots[idx].unk20;
    if (gModelSlots[idx].unk86 != 1) {
        if (gModelSlots[idx].unk86 == 2) {
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

    data = owner->unk24;
    out = owner->unk20;
    q = (ModelQuadData *)(data->unk70 + (s32)data + 4);
    out->x = x;
    out->y = y;
    out->z = z;
    out->scale = scale;
    out->yOffset = yOffset;
    out->quadCount = *(s32 *)(data->unk70 + (s32)data);
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



typedef struct ModelSlotAsset {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ void *unk14;
    /* 0x18 */ void *unk18;
    /* 0x1C */ void *verts;
    /* 0x20 */ u8 quadCount;
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ void *images[4];
    /* 0x34 */ void *images2[4];
    /* 0x44 */ u8 pad44[0xC];
    /* 0x50 */ TexAnimNode *texAnims;
} ModelSlotAsset;

void modelSlotLoadAssetTextures(ModelAssetHeader *asset, ModelSlotAsset *textures) {
    u8 type;
    s32 i;
    s16 *src;

    src = (s16 *)(asset->unk70 + (u8 *)asset + 4);
    if (*(s32 *)(asset->unk6C + (u8 *)asset) != 0) {
        type = 7;
    } else {
        type = 0x19;
    }
    for (i = 0; i < textures->quadCount; i++) {
        textures->images[i] = assetLoad(type, src[0], 1, 0);
        if (src[1] != -1) {
            textures->images2[i] = assetLoad(type, src[1], 1, 0);
        } else {
            textures->images2[i] = NULL;
        }
        src += 0x18;
    }
}

void modelSlotClearAssetTextures(ModelAssetHeader *asset, ModelSlotAsset *textures) {
    s32 i;

    for (i = 0; i < textures->quadCount; i++) {
        textures->images[i] = NULL;
        textures->images2[i] = NULL;
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
    mapPurgeNodeList(gModelSlots[slot].unk20, &purgeOut, 0);
    renderEntryRemove(0, gModelSlots[slot].unk20, 2, &removed);
    dynamicBufferFree(&gModelSlots[slot].unk28);
    modelSlotTriBufferRelease(&gModelSlots[slot].unk48);
    modelPosNodeListFree(gModelSlots[slot].unk70);
    modelLinkedNodeListFree(gModelSlots[slot].unk74);
    modelSlotFree(gModelSlots[slot].unk78);
    modelSlotFreeTexAnimNodes(&gModelSlots[slot]);
    if (gModelSlots[slot].unk7C != NULL) {
        csStateFree(gModelSlots[slot].unk7C);
    }
    gCsModelIds[gModelSlots[slot].csModelId] = -1;
    modelEmitterDisable(gModelSlots[slot].id);
    entryId = gModelSlots[slot].id;
    hashTableRemove(entryId);
    proxPathRemoveOwner(entryId);
    if (gModelSlots[slot].unk7C != NULL) {
        if (gModelSlots[slot].unk7C->unk10 != -1) {
            sfxSlotFreeSource(gModelSlots[slot].unk7C->unk10);
        }
        if (gModelSlots[slot].unk7C->unk12 != -1) {
            sfxSlotFreeSource(gModelSlots[slot].unk7C->unk12);
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

#define MODEL_TRANSFORM_SLOT0 ((ModelSlot *)((u8 *)gModelSlots + slot * 0x90))
#define MODEL_TRANSFORM_SLOT ((ModelSlot *)((u8 *)gModelSlots + off))

void modelSlotTransformBoundsAndNodes(s32 slot, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 yOffset, u8 setPos, u8 setRot, u8 setScale, u8 setYOffset, u8 isId) {
    ModelSlot *xform;
    ModelKindObj *kindObj;
    s16 purgeOut;
    u8 flag;
    u8 sel;
    s32 i;
    s32 off;

    flag = 0;
    if (isId == 1) {
        if (slot) {}  // FAKE: dead test raises slot candidate priority (steers uopt colouring)
        slot = hashTableLookup(slot);
    }
    if (setYOffset) {
        MODEL_TRANSFORM_SLOT0->yOffset = yOffset;
        xform = MODEL_TRANSFORM_SLOT0;
        switch (xform->unk86) {
            case 2:
                kindObj = xform->unk20;
                kindObj->type2.yOffset = yOffset;
                break;
            case 1:
                kindObj = xform->unk20;
                kindObj->type1.yOffset = yOffset;
                break;
        }
    }
    off = slot * 0x90;
    if (setPos) {
        MODEL_TRANSFORM_SLOT->x = x;
        MODEL_TRANSFORM_SLOT->y = y;
        MODEL_TRANSFORM_SLOT->z = z;
        if (flag) {}  // FAKE: dead test raises flag candidate priority (steers uopt colouring)
        xform = MODEL_TRANSFORM_SLOT;
        switch (xform->unk86) {
            case 2:
                kindObj = xform->unk20;
                kindObj->type2.x = x;
                kindObj->type2.y = y;
                kindObj->type2.z = z;
                break;
            case 1:
                kindObj = xform->unk20;
                kindObj->type1.x = x;
                kindObj->type1.y = y;
                kindObj->type1.z = z;
                break;
        }
    }
    if (setRot) {
        MODEL_TRANSFORM_SLOT->rotX = rotX;
        MODEL_TRANSFORM_SLOT->rotY = rotY;
        MODEL_TRANSFORM_SLOT->rotZ = rotZ;
        xform = MODEL_TRANSFORM_SLOT;
        if (xform->unk86 == 1) {
            kindObj = xform->unk20;
            kindObj->type1.rotX = rotX;
            kindObj->type1.rotY = rotY;
            kindObj->type1.rotZ = rotZ;
        }
    }
    if (setScale) {
        MODEL_TRANSFORM_SLOT->scale = scale;
        xform = MODEL_TRANSFORM_SLOT;
        switch (xform->unk86) {
            case 2:
                kindObj = xform->unk20;
                kindObj->type2.scale = scale;
                break;
            case 1:
                kindObj = xform->unk20;
                kindObj->type1.scale = scale;
                break;
        }
    }
    if ((setPos || setYOffset) && mapPurgeNodeList(MODEL_TRANSFORM_SLOT->unk20, &purgeOut, 0)) {
        xform = MODEL_TRANSFORM_SLOT;
        renderEntryAddOrUpdate(0, xform->unk86, xform->unk20, xform->x, xform->y, xform->z, xform->unk24->unk1E, xform->id, 0, purgeOut, 2);
    }
    xform = MODEL_TRANSFORM_SLOT;
    if (setPos || setYOffset || setRot) {
        modelEmitterSetPosition(xform->id, xform->x, xform->y, xform->z, xform->scale, xform->rotY);
        xform = MODEL_TRANSFORM_SLOT;
    }
    if (xform->unk7C != NULL) {
        sel = xform->unk7C->unk67;
        switch (sel) {
            case 0:
                flag = 1;
                break;
            case 2:
                if (gPlayerSlots != NULL) {
                    i = 0;
                    if (gPlayerCount > 0) {
                        do {
                            if (gPlayerSlots[i].active != 0) {
                                flag |= collisionCheckBoundingBoxY((CollisionBoundingBox *)((u8 *)off + (s32)gModelSlots + 0x54), gPlayerSlots[i].actor->y) != 0 && collisionCheckBoundingBoxXZ((CollisionBoundingBox *)((u8 *)off + (s32)gModelSlots + 0x54), gPlayerSlots[i].actor->x, gPlayerSlots[i].actor->z) != 0; // FAKE: integer-base sum (u8 *)off + (s32)gModelSlots keeps the bbox address in t0 (&gModelSlots[slot].unk48.bbox flips the addu, + off takes t4)
                            }
                            i = (u8)(i + 1);
                        } while (i < gPlayerCount);
                        xform = MODEL_TRANSFORM_SLOT;
                    }
                }
                break;
            case 1:
                if (gPlayerSlots != NULL) {
                    i = 0;
                    if (gPlayerCount > 0) {
                        do {
                            if (gPlayerSlots[i].active != 0) {
                                flag |= collisionCheckBoundingBoxXZ((CollisionBoundingBox *)((u8 *)off + (s32)gModelSlots + 0x54), gPlayerSlots[i].actor->x, gPlayerSlots[i].actor->z); // FAKE: integer-base sum (u8 *)off + (s32)gModelSlots keeps the bbox address in t0 (&gModelSlots[slot].unk48.bbox flips the addu, + off takes t4)
                            }
                            i = (u8)(i + 1);
                        } while (i < gPlayerCount);
                        xform = MODEL_TRANSFORM_SLOT;
                    }
                }
                break;
            case 3:
            case 4:
                if (gPlayerSlots != NULL) {
                    flag = activeActorBoxOverlapTest(xform->x, xform->y, xform->z, xform->unk7C->unk68, xform->unk7C->unk6A, xform->unk7C->unk6C, sel == 3 ? 0xEF : 1);
                    xform = MODEL_TRANSFORM_SLOT;
                }
                break;
        }
    }
    if (flag != 0) {
        collisionTransformNode(slot, xform->unk24, xform->x, xform->y, xform->z, xform->rotX, xform->rotY, xform->rotZ, xform->scale);
        xform = MODEL_TRANSFORM_SLOT;
        modelSlotBuildTriangleBufferThunk(slot, xform->unk24, xform->x, xform->y, xform->z, xform->rotX, xform->rotY, xform->rotZ, xform->scale);
        xform = MODEL_TRANSFORM_SLOT;
    }
    modelSlotBuildVertPosList(slot, xform->unk24, xform->x, xform->y, xform->z, xform->rotX, xform->rotY, xform->rotZ, xform->scale, 1);
    xform = MODEL_TRANSFORM_SLOT;
    modelSlotBuildNodePosList(slot, xform->unk24, xform->x, xform->y, xform->z, xform->rotX, xform->rotY, xform->rotZ, xform->scale, 1);
}

s32 activeActorBoxOverlapTest(f32 x, f32 y, f32 z, s16 radiusX, s16 radiusY, s16 radiusZ, u16 mask) {
    s32 i;
    Actor *b;
    Actor *a;
    s16 rx;
    s16 ry;
    s16 rz;

    rx = radiusX;  // FAKE: dead s16 copies of the radii (rx/ry/rz never read) renumber the int webs: count a1, i a0, gActiveActors t0, mask t1 at 0x4370-0x43c4 (without them v1/v0/a1/a2)
    ry = radiusY;
    rz = radiusZ;
    for (i = 0; i < gActiveActorCount; i++) {
        a = gActiveActors[i].actor;
        b = a;  // FAKE: alias read by the first three compares keeps y/z in f14/f20 and the coordinate loads in f18/f22/f24 (0x43d4-0x4414); one pointer moves y to f20, z to f22 and grows .text by 16 bytes
        if (b->collisionFlags & mask) {
            if (x - radiusX <= b->x && y - radiusY <= b->y && z - radiusZ <= b->z &&
                a->x <= radiusX + x && a->y <= radiusY + y && a->z <= radiusZ + z) {
                return 1;
            }
        }
    }
    return 0;
}


void func_80636014(s32 slot, u8 isId, u8 value) {
    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    func_8062D094(gModelSlots[slot].unk20, value);
}


void modelSlotFreeTexAnimNodes(ModelSlot *slot) {
    TexAnimNode *node;
    ModelKindObj *owner;
    ModelSlotSubNode *nodeList;
    TexAnimNode *cur;

    switch (slot->unk86) {
        case 2:
            owner = slot->unk20;
            node = owner->type2.texAnims;
            nodeList = owner->type2.subNode;
            modelSlotFreeAssetEntry(slot->unk24, slot->unk20);
            break;
        case 1:
            owner = slot->unk20;
            node = owner->type1.texAnims;
            nodeList = owner->type1.subNode;
            modelSegmentFreeUnusedTextures(slot, slot->unk24, slot->unk20);
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
    void **p;
    ModelSlotAsset *base;
    s32 i;
    void *q;

    if (type == 2 && asset->texAnims == 0) {
        base = asset;
        i = 0;
        p = (void **)asset;
        if (base->quadCount > 0) {
            do {
                q = p[9];
                if (q != NULL) {
                    assetFreeBuffer(q, 0xA2B, 7);
                    p[9] = NULL;
                }
                if (base) {} // FAKE: dead test steers register colouring
                q = p[13];
                if (q != NULL) {
                    assetFreeBuffer(q, 0xA30, 7);
                    if (base && base && base) {} // FAKE: dead test steers register colouring
                    p[13] = NULL;
                }
                i++;
                p++;
            } while (i < base->quadCount);
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
    switch (slot->unk86) {
        case 2:
            listPtr = &((ModelKindObj *)slot->unk20)->type2.subNode;
            break;
        case 1:
            listPtr = &((ModelKindObj *)slot->unk20)->type1.subNode;
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
        if (textures->images[i] != NULL) {
            assetFreeBuffer(textures->images[i], 0xA69, 7);
        }
        if (textures->images2[i] != NULL) {
            assetFreeBuffer(textures->images2[i], 0xA6A, 7);
        }
    }
    assetFreeBuffer(asset, 0xA6E, 7);
    heapFreeDeferred(textures->verts);
    heapFreeDeferred(textures);
    heapFreeDeferred(textures->unk14);
    heapFreeDeferred(textures->unk18);
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

extern DisplayListFreeRecord *D_807F6160;

void displayListFreeQueueReset(void) {
    D_807F6160 = NULL;
}

void displayListFreeQueueAdd(s32 headStart, s32 headEnd, s32 tailStart, s32 tailEnd, ModelAssetHeader *counter) {
    DisplayListFreeRecord *rec;
    DisplayListFreeRecord *old;

    rec = heapAlloc(sizeof(DisplayListFreeRecord));
    old = D_807F6160;
    D_807F6160 = rec;
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

    cur = D_807F6160;
    prev = NULL;
    if (cur != NULL) {
        do {
            next = cur->next;
            if (gFrameCounter == cur->freeFrame) {
                cur->asset->unk3C--;
                dlFreeUnusedTextures(cur->headStart, cur->headEnd, 0, 0, cur->asset->unk3C == 0);
                dlFreeUnusedTextures(cur->tailStart, cur->tailEnd, 0, 1, cur->asset->unk3C == 0);
                assetFreeBuffer(cur->asset, 0xAB1, 7);
                if (prev == NULL) {
                    D_807F6160 = cur->next;
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
    if (nodes == NULL && (slot->unk8C & 0x20)) {
        flag = 0;
    } else {
        flag = 1;
    }
    if (slot->unk8C & 0x20) {
        if (flag) {
            asset->unk3C -= 1;
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

    if (start != end) {
        if (restore != 0) {} // FAKE: dead test steers register colouring
        do {
            w = start->w0;
            found = 0;
            if ((w >> 24) == 0xFD) {
                node = nodes;
                if (node != NULL) {
                    do {
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
                        node = node->next;
                    } while (found == 0 && node != NULL);
                }
                if (found == 0) {
                    if (restore != 0) {
                        collisionBstLookupByHash(start->w1, &bstValue, &bstNode);
                    }
                    assetFreeBuffer((void *)start->w1, 0xB27, 7);
                    if (restore != 0) {
                        start->w1 = bstNode;
                    }
                }
            }
            start++;
        } while (start != end);
    }
}

extern u8 gViewportCount;

void modelSlotInitFromAsset(ModelSlot *slot, s32 type) {
    ModelAssetHeader *hdr;
    ModelType1ObjAddrs *seg;
    s32 pad;
    void *objData;
    RenderQuadModelObj *obj;

    if (func_80636A8C(type) != 0) {
        slot->unk24 = assetLoad(4, type, 1, 1);
    } else {
        slot->unk24 = assetLoad(4, type, 1, 0);
    }
    hdr = slot->unk24;
    slot->unk8C = 0;
    slot->unk86 = hdr->unk1C;
    slot->modelType = type;
    if (hdr->unk1C != 1) {
        if (hdr->unk1C == 2) {
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
        seg->displayListA = hdr->unk40 + (u32)hdr;
        seg->displayListB = hdr->unk44 + (u32)hdr;
        seg->segmentData = hdr->unk48 + (u32)hdr;
        seg->subNode = 0;
        seg->id = -1;
        seg->light = 0;
    }
    slot->unk20 = objData;
}

f32 func_80636A44(s32 type) {
    s32 pad;
    f32 *asset;
    f32 result;

    asset = assetLoad(4, type, 1, 0);
    result = asset[1];
    assetFreeBuffer(asset, 0xB87, 7);
    return result;
}

u8 func_80636A8C(s32 type) {
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

void renderReplaceSegment6Commands();

void modelSlotReplaceSegment6Commands(void *slot) {
    u32 head;
    ModelType1ObjAddrs *seg;
    u32 mid;
    u32 count;
    u32 len;
    u32 start;
    u32 size;

    seg = ((ModelSlot *)slot)->unk20;
    mid = seg->displayListB;
    head = seg->displayListA;
    start = head;
    len = seg->segmentData - mid;
    head = (mid - head) >> 3;
    count = len >> 3;
    size = head * 8;
    renderReplaceSegment6Commands(start, start + size, seg, len);
    len = count;
    renderReplaceSegment6Commands(seg->displayListB, seg->displayListB + count * 8, seg, len);
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
                    collisionBstLookupByHash(start->w1, &bstValue, &bstNode);
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


extern s16 D_80747D74;

void modelSlotsStepSegmentCommands(void) {
    u32 mid;
    ModelType1ObjAddrs *seg;
    u32 head;
    u32 count;
    u8 flag;
    ModelAssetHeader *obj;
    ModelSlot *slot;
    u32 start;

    if (gModelSlotCount != 0) {
        D_80747D74++;
        if (D_80747D74 >= gModelSlotCount) {
            D_80747D74 = 0;
        }
        slot = (ModelSlot *)((u8 *)gModelSlots + D_80747D74 * 0x90); // FAKE: byte-offset slot address keeps li t3,0x90 with the gModelSlots base in t2 (&gModelSlots[D_80747D74] swaps t2/t3)
        obj = slot->unk24;
        if (obj->unk0 & 0x10) {
            if ((slot->unk8C & 0x20) && gFrameCounter != obj->unk8) {
                slot->unk8C &= ~0x20;
                obj->unk3C--;
                if (obj->unk3C != 0) {
                    flag = 0;
                } else {
                    flag = 1;
                }
                seg = ((ModelSlot *)((u8 *)gModelSlots + D_80747D74 * 0x90))->unk20; // FAKE: re-derives the slot from gModelSlots + D_80747D74 * 0x90 (pre-existing, now tagged; slot->unk20 loses li t3,144 and the t1 base for &D_80747D74)
                mid = seg->displayListB;
                head = seg->displayListA;
                start = head;
                count = seg->segmentData - mid;
                head = (mid - head) >> 3;
                count >>= 3;
                dlFreeSegmentCommandTextures((DisplayListCmd *)start, (DisplayListCmd *)start + head, flag);
                dlFreeSegmentCommandTextures((DisplayListCmd *)seg->displayListB, (DisplayListCmd *)seg->displayListB + count, flag);
            }
        }
    }
}





void modelSlotResolveAssetTextures(ModelSlot *slot, u8 forceLoad, u8 force) {
    ModelType1ObjAddrs *seg;
    ModelAssetHeader *obj;
    ModelSlotAsset *volatile textures; // FAKE: memory copy of seg that the else branch reads back (target reloads 0x3C(sp))
    u32 temp;
    u32 cmds;
    u32 count;
    TexAnimNode *node;
    u8 res;
    u8 flags;
    u32 size0;
    u32 size1;

    temp = (u32)slot->unk24;
    seg = slot->unk20;
    textures = (ModelSlotAsset *)seg;
    obj = (ModelAssetHeader *)temp;
    obj->unk8 = gFrameCounter;
    flags = slot->unk8C;
    if (!(flags & 0x20)) {
        if (!(obj->unk0 & 0x10) || force != 0) {
            temp = (u32)seg; // FAKE: dead redefinition keeps obj's early web (v0) separate from obj (Q0546)
            slot->unk8C = flags | 0x20;
            obj->unk3C++;
            if (obj->unk1C == 1) {
                count = seg->segmentData - seg->displayListB;
                cmds = seg->displayListA;
                temp = (seg->displayListB - cmds) >> 3;
                count = count >> 3;
                node = (TexAnimNode *)((ModelType1ObjAddrs *)slot->unk20)->texAnims; // FAKE: re-reads slot->unk20 instead of seg (pre-existing, now tagged; seg->unkB8 drops the sw a0,72(sp) slot home)
                size0 = temp * 8;
                temp = 0; // FAKE: dead store keeps size0 a variable instead of a propagated expression
                res = dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)(cmds + size0), node, force);
                cmds = seg->displayListB;
                size1 = count * 8;
                count = 0; // FAKE: dead store keeps size1 a variable instead of a propagated expression
                res |= dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)(cmds + size1), node, force);
                if (node != NULL) {
                    cmds = seg->displayListACopy;
                    res |= dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)(cmds + size0), node, force);
                    cmds = seg->displayListBCopy;
                    res |= dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)(cmds + size1), node, force);
                    if (seg->displayListA == 0) {} // FAKE: dead test keeps seg live past the last call so it stays in s0
                }
                if (res != 0) {
                    obj->unk0 &= ~0x10;
                }
            } else {
                if (textures->texAnims != 0 || forceLoad != 0) {
                    modelSlotLoadAssetTextures(obj, textures);
                } else {
                    modelSlotClearAssetTextures(obj, textures);
                }
            }
        }
    }
}


s32 dlResolveNodeTextures(DisplayListCmd *start, DisplayListCmd *end, TexAnimNode *nodes, u8 keep) {
    u32 w;
    u32 tag;
    s32 result;
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
    /* 0xC2 */ u8 unkC2;
    /* 0xC3 */ u8 light;
    /* 0xC4 */ u8 unkC4;
    /* 0xC5 */ u8 mapFlags;
} ModelType1RenderView;

s32 playerSlotMatchesSizeMask(s32, u8, s32);

Gfx *renderModelAnimatedSlot(ModelType1RenderView *obj, Gfx *gfx, f32 camX, f32 camY, f32 camZ, u8 useLight, s16 lightArg, s32 unused) {
    f32 mtx[4][4];
    f32 tmpMtx[4][4];
    f32 dx;
    f32 dy;
    f32 dz;
    u8 sel;
    ModelData *animBuffers;
    f32 scale;
    CsStateFull *model;
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
    if (obj && obj && obj) {} // FAKE: dead block pads as1's XBB window (limit 10) so the rotation compares don't hoist `addiu a0,sp,184` (6 guards needed)
    if (obj && obj && obj) {} // FAKE: same
    if (obj && obj && obj) {} // FAKE: same
    if (obj && obj && obj) {} // FAKE: same
    if (obj && obj && obj) {} // FAKE: same
    if (obj && obj && obj) {} // FAKE: same
    guTranslateF(tmpMtx, obj->x, obj->y, obj->z);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &obj->frameMtx[gGfxBufferIndex]);
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 8, osVirtualToPhysical(obj->segmentData));
    animBuffers = NULL;
    if (obj->id != -1) {
        slotIdx = hashTableLookup(obj->id);
        modelSlotResolveAssetTextures(&gModelSlots[slotIdx], 0, 1);
        animBuffers = gModelSlots[slotIdx].unk78;
        if (playerSlotMatchesSizeMask(gModelSlots[slotIdx].unk24->unk0, gCurrentPlayerIndex, (s32)animBuffers) != 0) {
            return gfx;
        }
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
    if (useLight && obj->unkC2 == 0) {
        f32 yOffset;

        model = gModelSlots[slotIdx].unk7C;
        if (model != NULL) {
            yOffset = model->unk98;
        } else {
            yOffset = 0.0f;
        }
        lightSampleColorAtPosition(obj->x, obj->y + yOffset, obj->z, 0, &red, &green, &blue, lightArg);
        scale = obj->unkC4 / 15.0f;
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
        if (obj->id != -1 && (model = gModelSlots[slotIdx].unk7C) != NULL && model->unk60 == 1) {
            csUpdateStepAndInterpolation(model);
            alpha = (gModelSlots[slotIdx].unk7C)->unk64;
        } else {
            renderCalcPlayerDistanceAlpha(obj->x, obj->y, obj->z, obj->maxDist, obj->modelType, &alpha);
            if (obj->id != -1) {
                model = gModelSlots[slotIdx].unk7C;
                if (model != NULL && gViewportCount == 1) {
                    model->unk62 = alpha;
                }
            }
            if (obj->id != -1) {
                model = gModelSlots[slotIdx].unk7C;
                if (model != NULL) {
                    csUpdateStepAndInterpolation(model);
                }
            }
            if (obj->id != -1) {
                model = gModelSlots[slotIdx].unk7C;
                if (model != NULL && gViewportCount == 1) {
                    alpha = model->unk64;
                }
            }
        }
    } else {
        alpha = 0xFF;
    }
    if (alpha != 0) {
        if (obj->id != -1) {
            u8 fl = gModelSlots[slotIdx].unk8C;
            if (fl != 0) {
                if ((gModelSlots[slotIdx].unk8C & 0x8) && gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 2) {
                    alpha = 0x64;
                }
                if ((gModelSlots[slotIdx].unk8C & 0x2) && gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 3) {
                    alpha = 0x64;
                }
                if ((gModelSlots[slotIdx].unk8C & 0x4) && gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 5) {
                    alpha = 0x64;
                }
                if ((gModelSlots[slotIdx].unk8C & 0x1) && gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 6) {
                    alpha = 0x64;
                }
                if ((gModelSlots[slotIdx].unk8C & 0x10) && gPlayerSlots[gCurrentPlayerIndex].actor->actorType != 4) {
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

extern u8 D_807F6009;
extern void *D_807F600C;
extern s32 D_807F5FD8;


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

    if (0) { // FAKE: dead call takes &useLight so it gets a stack home
        modelKongVisibilityCheck(0, &useLight, 0);
    }
    vtxOffset = 0;
    usedTlut = 0;
    if (useLight != 0) {
        dx = camX - obj->x;
        dy = camY - obj->y;
        dz = camZ - obj->z;
        dx *= dx;
        dy *= dy;
        dz *= dz;
        dist = sqrtf(dx + dy + dz);
        limit = renderScaleDistanceByFov(obj->maxDist);
        if ((f32)limit < dist) {
            return gfx;
        }
    }
    if (obj->light != 0) {
        lightQueueKeyframed(obj->light, obj->id, obj->x, obj->y, obj->z, obj->maxDist, dist / (f32)limit, lightArg);
    }
    if (useLight != 0) {
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
    D_807F5FD8 += 1;
    if (obj->textures[0] == NULL) {
        modelSlotLoadAssetTextures(gModelSlots[(s16)hashTableLookup(obj->id)].unk24, (ModelSlotAsset *)obj);
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
    if (dist < (f32)((limit * 3) / 4)) {
        opaque = 1;
        alpha = 0xFF;
    } else {
        opaque = 0;
        alpha = ((dist - (f32)((limit * 3) / 4)) / ((f32)limit - (f32)((limit * 3) / 4))) * 255.0f;
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        alpha = 0xFF - alpha;
    }
    modelKongVisibilityCheck(obj->modelType, &opaque, &alpha);
    if (useLight != 0 && obj->unk5A == 0) {
        lightSampleColorAtPosition(obj->x, obj->y, obj->z, 0, &red, &green, &blue, lightArg);
        scale = (f32)(u32)obj->surfaceType / 15.0f;
        red = (f32)(u32)red * scale;
        green = (f32)(u32)green * scale;
        blue = (f32)(u32)blue * scale;
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
            if (D_807F6009 != 2 || texA != (s32)D_807F600C) {
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
            D_807F600C = (void *)texA;
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
            D_807F600C = NULL;
            break;
        }
        gSPVertex(gfx++, osVirtualToPhysical(obj->verts + vtxOffset), 4, 0);
        gSP2Triangles(gfx++, 0, 1, 2, 0, 0, 2, 3, 0);
        vtxOffset += 4;
        D_807F6009 = 2;
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

extern u8 gPlayerCharacterId[];
extern PlayerInventory gPlayerInventoryTable[];

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
        if ((gPlayerInventoryTable[gCurrentPlayerIndex].kong[gPlayerCharacterId[gCurrentPlayerIndex]].unk0[2] & 3) != 3) {
            hit = 1;
        }
        break;
    case 0x8F:
        if (!(gPlayerInventoryTable[gCurrentPlayerIndex].kong[gPlayerCharacterId[gCurrentPlayerIndex]].unk0[2] & 1)) {
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
        if (*alphaOut > 0x64) {
            *alphaOut = 0x64;
        }
    }
}

void func_806398E4(s32 slot, u8 isId, u8 enable) {
    RenderQuadModelObj *obj;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    obj = gModelSlots[slot].unk20;
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
                    dst = &node->cmdsA[gGfxBufferIndex].texCmd->tileSizeW0; // FAKE: dst pointer temp for both 0xF2000000 stores (direct field stores fail fdiff)
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
                    collisionResolveWallContact();
                }
                node->textureBuffer = assetLoad(7, node->frameTextures[frameB], 0, 0);
                oldBufA = node->textureBuffer2;
                if (oldBufA != NULL) {
                    assetFreeBuffer(oldBufA, 0xFCE, 7);
                }
                if (node->keepBuffers != 0) {
                    collisionResolveWallContact();
                }
                node->textureBuffer2 = assetLoad(7, node->frameTextures[frameA], 0, 0);
            } else {
                if (oldBufB != NULL) {
                    assetFreeBuffer(oldBufB, 0xFD5, 7);
                }
                oldBufA = node->textureBuffer2;
                node->textureBuffer = oldBufA;
                if (node->keepBuffers != 0) {
                    collisionResolveWallContact();
                }
                node->textureBuffer2 = assetLoad(7, node->frameTextures[frameA], 0, 0);
            }
        } else {
            if (oldBufB != NULL) {
                assetFreeBuffer(oldBufB, 0xFDF, 7);
            }
            if (node->keepBuffers != 0) {
                collisionResolveWallContact();
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
            switch (listA->unk24) {
            case 2:
                d = listA->unk0;
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
                d1 = listA->unk0;
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
            listA = listA->unk14;
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

void func_8063A8C4(s16 slot, u8 isId, f32 value) {
    ModelKindObj *obj;
    ModelSlotSubNode *p;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    obj = gModelSlots[slot].unk20;
    switch (gModelSlots[slot].unk86) {
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


extern s16 D_807F6028;
extern s16 D_807F60A8;
extern u8 gCsTrackedModelCount;

void modelPendingCountsReset(void) {
    D_807F6028 = 0;
    D_807F60A8 = 0;
    gCsTrackedModelCount = 0;
}

typedef struct ModelPendingQueueEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ s16 key;
    /* 0x4 */ u8 done;
    /* 0x5 */ u8 pad5;
} ModelPendingQueueEntry;

extern ModelPendingQueueEntry D_807F6030[];
extern s16 D_807F60B0[];

extern u8 D_807F7140;

void modelPendingQueueInsert(RenderEntry *entry, u8 allowDefault) {
    CsStateFull *obj;
    u8 allow;
    s32 pad1;
    s32 pad2;
    s16 idx;
    s32 pad3;
    s32 pad4;
    s32 pad5;
    ModelSlot *slots;
    f32 *zPtr;
    u8 i;
    f32 *px;
    f32 *py;
    f32 *pz;
    f32 best;

    if (0) { csStateTickTimers((CsStateFull *)&idx); csStateTickTimers((CsStateFull *)&slots); } allow = 1; if (entry->unk24 == 1) { idx = hashTableLookup(entry->unk1E); slots = gModelSlots; obj = slots[idx].unk7C; if (obj != NULL) { // FAKE: dead if (0) takes &idx/&slots so both get stack homes; the one-line layout keeps as1 line order
            switch (obj->unk54) {
            case 2:
                allow = 0;
                break;
            case 0:
                allow = allowDefault;
                break;
            case 4:
                if (zPtr != 0) {}  // FAKE: dead test steers register colouring
                allow = allowDefault;
            case 3:
            case 6:
                best = 1e8f;
                for (i = 0; i < gViewportCount; i++) {
                    if (gPlayerSlots[i].active != 0) {
                        if (entry && entry) {}  // FAKE: dead test steers register colouring
                        if (obj->unk54 == 6) {
                            px = &gPlayerSlots[i].actor->x;
                            py = &gPlayerSlots[i].actor->y;
                            zPtr = &gPlayerSlots[i].actor->z;
                            pz = zPtr;
                        } else {
                            px = &gPlayerSlots[i].eyeX;
                            py = &gPlayerSlots[i].eyeY;
                            pz = &gPlayerSlots[i].eyeZ;
                        }
        if (px) {}  // FAKE: dead test steers register colouring
                        if ((*px - entry->unk4) * (*px - entry->unk4) + (*py - entry->unk8) * (*py - entry->unk8) + (*pz - entry->unkC) * (*pz - entry->unkC) < best) {
                            best = (*px - entry->unk4) * (*px - entry->unk4) + (*py - entry->unk8) * (*py - entry->unk8) + (*pz - entry->unkC) * (*pz - entry->unkC);
                        }
                        if (slots && slots) {}  // FAKE: dead test steers register colouring
                    }
                }
                allow &= best < (f32)obj->unk58;
                break;
            case 5:
                if (D_807F6028 == 0x14) return;
                allow = 0;
                D_807F6030[D_807F6028].id = entry->unk1E;
                D_807F6030[D_807F6028].key = obj->unk58;
                D_807F6030[D_807F6028++].done = 0;
                break;
            }
            if (allow != 0) {
                D_807F7140++;
                if (D_807F60A8 != 0x46) {
                    D_807F60B0[D_807F60A8] = slots[idx].csModelId;
                    D_807F60A8++;
                    csStateTickTimers(obj);
                    csStateUpdate(obj, entry->unk1E);
                }
            }
        }
    }
}

void modelPendingEntriesProcess(void) {
    u8 found;
    s32 i;
    s32 slot;
    struct CsStateFull *obj;
    u8 any;
    s32 j;

    do {
        any = 0;
        for (i = 0; i < D_807F6028; i++) {
            if (D_807F6030[i].done == 0) {
                found = 0;
                for (j = 0; found == 0 && j < D_807F60A8; j++) {
                    if (D_807F60B0[j] == D_807F6030[i].key) {
                        found = 1;
                        any = 1;
                        D_807F6030[i].done = 1;
                        slot = hashTableLookup(D_807F6030[i].id);
                        obj = gModelSlots[slot].unk7C;
                        if (D_807F60A8 == 0x46) {
                            return;
                        }
                        D_807F60B0[D_807F60A8] = gModelSlots[slot].csModelId;
                        D_807F60A8++;
                        csStateTickTimers(obj);
                        csStateUpdate(obj, D_807F6030[i].id);
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
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 kind;
    /* 0x2E */ u8 light;
    /* 0x2F */ u8 flags;
} ModelSlotSerializedOut; /* 0x30 */


extern u8 *D_807F6010;
extern u8 gCsVarsDirty[];


void modelSlotSerializeAll(u8 **bufOut, s32 *sizeOut) {
    s32 count;
    s32 size;
    s32 i;
    ModelSlotSerializedOut *out;
    u8 *dst;

    count = 0;
    if (D_807F6010 != NULL) {
        heapFree(D_807F6010);
    }
    size = gModelSlotCount * sizeof(ModelSlotSerializedOut) + sizeof(s32);
    size += sizeof(s32);
    for (i = 0; i < 0x212; i++) {
        if (gCsVarsDirty[i]) {
            size += 0x24;
            count++;
        }
    }
    size += actorListGetSerializedSize();
    D_807F6010 = heapAlloc(size);
    *(s32 *)D_807F6010 = gModelSlotCount;
    out = (ModelSlotSerializedOut *)(D_807F6010 + 4);
    for (i = 0; i < gModelSlotCount; i++, out++) {
        out->x = gModelSlots[i].x;
        out->y = gModelSlots[i].y;
        out->z = gModelSlots[i].z;
        out->scale = gModelSlots[i].scale;
        out->rotX = gModelSlots[i].rotX;
        out->rotY = gModelSlots[i].rotY;
        out->rotZ = gModelSlots[i].rotZ;
        out->modelType = gModelSlots[i].modelType;
        out->kind = gModelSlots[i].unk86;
        out->yOffset = gModelSlots[i].yOffset;
        out->unk2A = gModelSlots[i].csModelId;
        switch (out->kind) {
        case 2:
            out->flags = ((RenderQuadModelObj *)gModelSlots[i].unk20)->flags;
            out->light = ((RenderQuadModelObj *)gModelSlots[i].unk20)->light;
            break;
        case 1:
            out->flags = 0;
            out->light = ((ModelType1Obj *)gModelSlots[i].unk20)->light;
            break;
        }
    }
    *(s32 *)out = count;
    dst = (u8 *)out + 4;
    for (i = 0; i < 0x212; i++) {
        if (gCsVarsDirty[i] != 0) {
            *(s32 *)dst = i;
            memcpy(dst + 4, gModelSlots[hashTableLookup(gCsModelIds[i])].unk7C->unk14, 0x20);
            dst += 0x24;
        }
    }
    actorListSerialize((s32 *)dst);
    *bufOut = D_807F6010;
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
        if (gModelSlots[i].unk7C != NULL) {
            if ((gModelSlots[i].unk24->unk3A != 0 || (gModelSlots[i].unk7C->unk9B & 1)) && !(gModelSlots[i].unk7C->unk9B & 2)) {
                count++;
                if (gModelSlots[i].unk78 != NULL) {
                    size += modelSlotDataSize(i);
                }
            }
        }
    }
    if (count != 0) {
        buf = heapAlloc(count * 0x254 + size);
        cur = buf;
        for (i = 0; i < gModelSlotCount; i++) {
            if (gModelSlots[i].unk7C != NULL) {
                if ((gModelSlots[i].unk24->unk3A != 0 || (gModelSlots[i].unk7C->unk9B & 1)) && !(gModelSlots[i].unk7C->unk9B & 2)) {
                    rec = cur;
                    *(s16 *)rec = gModelSlots[i].csModelId;
                    memcpy(rec + 0xCC, gModelSlots[i].unk7C, 0x9C);
                    if (gModelSlots[i].unk78 != NULL) {
                        memcpy(rec + 4, gModelSlots[i].unk78->entries, 0xC8);
                        rec[0x250] = modelSlotDataSize(i) >> 6;
                        memcpy(rec + 0x254, gModelSlots[i].unk78->frames[0], modelSlotDataSize(i));
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

// The CsStateFull fields modelSlotsApplyRecords keeps across a restored record.
typedef struct ModelSlotStateSnapshot {
    /* 0x00 */ void *heapBlock;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 pad14[0x80];
    /* 0x94 */ Actor *actor;
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
        memcpy(&snap, gModelSlots[idx].unk7C, 0x9C);
        memcpy(gModelSlots[idx].unk7C, records + 0xCC, 0x9C);
        gModelSlots[idx].unk7C->unk0 = snap.heapBlock;
        gModelSlots[idx].unk7C->unk10 = snap.unk10;
        gModelSlots[idx].unk7C->unk12 = snap.unk12;
        gModelSlots[idx].unk7C->unk94 = snap.actor;
        gModelSlots[idx].unk7C->unk48[0] = gModelSlots[idx].unk7C->unk4B[0];
        gModelSlots[idx].unk7C->unk48[1] = gModelSlots[idx].unk7C->unk4B[1];
        gModelSlots[idx].unk7C->unk48[2] = gModelSlots[idx].unk7C->unk4B[2];
        gModelSlots[idx].unk7C->unk9A = 0;
        gModelSlots[idx].unk7C->unk38 = -1;
        if (gModelSlots[idx].unk78 != NULL) {
            for (off = 0; off != 0xC8; off += 0x14) {
                memcpy(tmp, (u8 *)gModelSlots[idx].unk78 + off + 8, 0x14);
                memcpy((u8 *)gModelSlots[idx].unk78 + off + 8, records + 4 + off, 0x14);
                *(u32 *)((u8 *)gModelSlots[idx].unk78 + off + 8) = *(u32 *)tmp;
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
    RenderQuadModelObj *obj = gModelSlots[hashTableLookup(gCsModelIds[csId])].unk20;

    obj->flags |= flags;
}

void modelSlotClearFlags(s32 csId, u8 flags) {
    RenderQuadModelObj *obj = gModelSlots[hashTableLookup(gCsModelIds[csId])].unk20;

    obj->flags &= ~flags;
}

s32 func_8063C2A8(s16 id) {
    s16 idx = hashTableLookup(id);
    CsStateFull *sub = gModelSlots[idx].unk7C;

    if (sub != NULL) {
        if (sub->unk60 == 1 && sub->unk64 == 0) {
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

