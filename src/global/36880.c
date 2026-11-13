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
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ u8 pad2C[2];
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
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
                    if (modelTypeIsCounted(entry->unk28)) {
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
                    if (modelTypeIsCounted(entry->unk28)) {
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
                if (checkSaved && modelTypeIsCounted(entry->unk28)) {
                    found = eepromReadChecksumBit(saveIndex + counter, saveFile);
                    used = 1;
                }
                if (found == 0 && modelSkipListContains(entry->unk28) == 0 &&
                    flagGetForMapObject(gCurrentMap, entry->unk2A) == 0 &&
                    func_8063253C(entry->unk28, map) != 0) {
                    gModelSlots[outCount].x = entry->unk0;
                    gModelSlots[outCount].y = entry->unk4;
                    gModelSlots[outCount].z = entry->unk8;
                    gModelSlots[outCount].scale = entry->unkC;
                    gModelSlots[outCount].rotY = entry->unk18;
                    gModelSlots[outCount].unk14 = entry->unk1C;
                    gModelSlots[outCount].unk18 = entry->unk20;
                    gModelSlots[outCount].unk1C = entry->unk24;
                    gModelSlots[outCount].unk8A = entry->unk2A;
                    result = modelSlotInit(outCount, entry->unk28, entry->unk0, entry->unk4, entry->unk8,
                                           entry->unk18, entry->unk1C, entry->unk20, entry->unkC, entry->unk24,
                                           entry->unk2F, entry->unk2E, &renderList);
                    modelFlagsApplyState(gCurrentMap, gModelSlots[outCount].unk8A, &gModelSlots[outCount].unk8C);
                    gCsModelIds[entry->unk2A] = result;
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

typedef struct ModelFlagTarget {
    /* 0x00 */ u8 pad0[0x4A];
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8 pad4C[2];
    /* 0x4E */ u8 unk4E;
} ModelFlagTarget;



void modelNodeListSyncFlags(RenderEntry *node) {
    ModelFlagTarget *obj;
    s16 flag;

    if (node != NULL) {
        do {
            if (node->unk24 == 2) {
                obj = node->unk0;
                switch (obj->unk4A) {
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
                        obj->unk4E |= 0x10;
                    } else {
                        obj->unk4E &= ~0x10;
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
            *csIdOut = gModelSlots[i].unk8A;
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
    gModelSlots[gModelSlotCount].rotY = 0.0f;
    gModelSlots[gModelSlotCount].unk14 = 0.0f;
    gModelSlots[gModelSlotCount].unk18 = 0.0f;
    gModelSlots[gModelSlotCount].unk1C = y - yOffset;
    gModelSlots[gModelSlotCount].unk8C = 0;
    slotId = modelSlotInit(gModelSlotCount, type, x, y, z, 0.0f, 0.0f, 0.0f, scale, y - yOffset, 1, 0, &renderList);
    mapDistributeEntries(renderList);
    renderEntryListFree(renderList);
    gModelSlots[gModelSlotCount].unk8A = csModelIdTableAlloc(slotId, force);
    gModelSlotCount++;
    return slotId;
}

typedef struct ModelType1Obj {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x96];
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ u8 padB8[4];
    /* 0xBC */ void *unkBC;
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 unkC2;
    /* 0xC3 */ u8 unkC3;
    /* 0xC4 */ u8 unkC4;
    /* 0xC5 */ u8 unkC5;
} ModelType1Obj;

typedef struct ModelType2ObjView {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F[5];
    /* 0x54 */ void *unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ u8 unk5A;
    /* 0x5B */ u8 unk5B;
    /* 0x5C */ u8 unk5C;
} ModelType2ObjView;

typedef struct ModelSlotSubNode {
    /* 0x00 */ void *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x14];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 pad26[2];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 pad2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ s32 unk34;
} ModelSlotSubNode;

extern s32 gGlobalOverlayFlags;
extern s32 gGlobalCutsceneFlags;


s16 modelSlotInit(s32 slot, s32 modelType, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 yOffset, u8 flags, u8 light, struct RenderEntry **renderListInOut) {
    s32 padA[1];
    struct RenderEntry *renderList;
    s32 padB[1];
    ModelType1Obj *obj1;
    ModelType2ObjView *obj2;
    ModelAssetHeader *info;
    s32 type;
    ModelSlotSubNode *node;
    void **link;

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
            link = &obj2->unk54;
            obj2->unk4C = D_807F6004;
            obj2->unk4E = flags;
            obj2->unk5B = light;
            obj2->unk58 = info->unk1E;
            obj2->unk5A = info->unk1D;
            obj2->unk5C = groundSurfaceTypeAt(x, y, z);
        }
    } else {
        obj1 = gModelSlots[slot].unk20;
        obj1->unk0 = x;
        obj1->unk4 = y;
        obj1->unk8 = z;
        obj1->unkC = scale;
        obj1->unk10 = rotX;
        obj1->unk14 = rotY;
        obj1->unk18 = rotZ;
        obj1->unk1C = yOffset;
        obj1->unkB6 = D_807F6004;
        obj1->unkC0 = info->unk1E;
        obj1->unkC2 = info->unk1D;
        obj1->unkC3 = light;
        obj1->unkC4 = groundSurfaceTypeAt(x, y, z);
        obj1->unkC5 = 0;
        modelFlagsApplyMapPairs(modelType, &obj1->unkC5);
        modelSlotInitTexAnimNodes(info, &gModelSlots[slot], type);
        link = &obj1->unkBC;
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
        node->unk4 = 1.0f;
        node->unkC = info->unk2E;
        node->unkE = info->unk30;
        node->unkA = info->unk34;
        node->unkB = info->unk35;
        node->unk8 = info->unk32;
        node->unk9 = info->unk33;
        node->unk24 = info->unk2A;
        node->unk28 = info->unk2C;
        node->unk2A = info->unk36 * 10;
        node->unk2C = info->unk37 * 10;
        node->unk2E = info->unk38;
        node->unk30 = info->unk39;
        node->unk0 = assetLoad(0x19, info->unk28, 1, 0);
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

extern ModelMapIdPair D_80747D50[];

void modelFlagsApplyMapPairs(s16 id, u8 *flags) {
    s32 i;
    s32 n;
    i = 0;
    n = 8; // FAKE: constant bound in a variable keeps the loop test in a register
    for (; i < n; i++) {
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

extern ModelMapIdValueTriple D_80747D30[];

void modelApplyMapOverrideValue(s32 id, ModelAssetHeader *info) {
    s32 i;
    s32 n;

    n = 5; // FAKE: constant bound in a variable keeps the loop test in a register
    for (i = 0; i < n; i++) {
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

typedef struct ModelGroundCoordDst {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
} ModelGroundCoordDst;

typedef struct ModelSlotObjCoordHolder {
    /* 0x00 */ u8 pad0[0x54];
    /* 0x54 */ ModelGroundCoordDst *unk54;
    /* 0x58 */ u8 pad58[0x64];
    /* 0xBC */ ModelGroundCoordDst *unkBC;
} ModelSlotObjCoordHolder;


void modelSlotUpdateGroundCoords(s16 slot, u8 isId) {
    s32 padA[4];
    ModelAssetHeader *info;
    ModelGroundCoordDst *dst;
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
                dst = ((ModelSlotObjCoordHolder *)gModelSlots[slot].unk20)->unkBC;
                break;
            case 2:
                dst = ((ModelSlotObjCoordHolder *)gModelSlots[slot].unk20)->unk54;
                break;
        }
        if (gModelSlots[slot].unk20) {} // FAKE: dead test extends the slot pointer web (steers colouring)
        if (dst != NULL) {
            dst->unk20 = groundX;
            dst->unk22 = groundZ;
        }
    }
}

typedef struct ModelPathSeg {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13;
} ModelPathSeg;

typedef struct ModelPathEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 unk14;
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
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].unk10, &ax, &ay, &az);
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].unk11, &bx, &by, &bz);
            len += sqrtf((az - bz) * (az - bz) + ((ax - bx) * (ax - bx) + (ay - by) * (ay - by)));
        }
        proxPathAdd((Actor *)id, 1, i, 1, tbl[i - 1].segCount, 0.0f, len, tbl[i - 1].unk0 * scale, tbl[i - 1].unkC * scale, tbl[i - 1].unk10 * scale, tbl[i - 1].unk10 * scale, tbl[i - 1].unk14, tbl[i - 1].unk4, tbl[i - 1].unk8, tbl[i - 1].unk15);
        for (j = 0; j < tbl[i - 1].segCount; j++) {
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].unk10, &ax, &ay, &az);
            modelSlotGetNodePos(id, 1, tbl[i - 1].segs[j].unk11, &bx, &by, &bz);
            proxPathSetSegment((Actor *)id, i, j, tbl[i - 1].segs[j].unk10, tbl[i - 1].segs[j].unk11, sqrtf((az - bz) * (az - bz) + ((ax - bx) * (ax - bx) + (ay - by) * (ay - by))), tbl[i - 1].segs[j].unk0 * scale, tbl[i - 1].segs[j].unk4 * scale, tbl[i - 1].segs[j].unk12, tbl[i - 1].segs[j].unk8, tbl[i - 1].segs[j].unkC, tbl[i - 1].segs[j].unkA, tbl[i - 1].segs[j].unkE);
        }
    }
}



typedef struct ModelVert {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ s8 unk6;
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
            modelSlotBuildTransformMatrix(slot, vert->unk6, mtx);
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
    modelSlotBuildTransformMatrix(idx, vert->unk6, mtxF);
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
            modelSlotBuildTransformMatrix(slot, vert->unk6, nodeMtx);
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

typedef struct TexAnimNode {
    /* 0x00 */ u32 *unk0[12];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ void *unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 pad4B;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60[28];
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 padD1[3];
    /* 0xD4 */ struct TexAnimNode *unkD4;
} TexAnimNode;

typedef struct ModelSlotObj {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ void *unk24[11];
    /* 0x50 */ TexAnimNode *unk50;
    /* 0x54 */ u8 pad54[0x4C];
    /* 0xA0 */ u32 *unkA0;
    /* 0xA4 */ u32 *unkA4;
    /* 0xA8 */ u32 *unkA8;
    /* 0xAC */ u32 *unkAC;
    /* 0xB0 */ u8 padB0[8];
    /* 0xB8 */ TexAnimNode *unkB8;
} ModelSlotObj;

void modelSlotLinkTexAnimTextures(ModelAssetHeader *asset, ModelSlot *slot) {
    TexAnimNode *node;
    s16 *p;
    s32 n;
    s32 idx;
    s32 found;
    s32 key;

    node = ((ModelSlotObj *)slot->unk20)->unk50;
    if (node != NULL) {
        do {
            key = node->unk5C;
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
                node->unk44 = ((ModelSlotObj *)slot->unk20)->unk24[idx];
            } else {
                node->unk44 = NULL;
            }
            node = node->unkD4;
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
    ModelSlotObj *obj;
    s32 len1;
    s32 len2;
    s32 *tbl;

    tbl = (s32 *)(asset->unk6C + (u8 *)asset);
    count = *tbl;
    entry = tbl + 1;
    switch (type) {
        case 1:
            tail = &((ModelSlotObj *)slot->unk20)->unkB8;
            if (count != 0) {
                obj = slot->unk20;
                len1 = dlLengthToEndDL(obj->unkA0);
                obj->unkA4 = heapAlloc(len1);
                memcpy(obj->unkA4, obj->unkA0, len1);
                len2 = dlLengthToEndDL(obj->unkA8);
                obj->unkAC = heapAlloc(len2);
                memcpy(obj->unkAC, obj->unkA8, len2);
            }
            break;
        case 2:
            tail = &((ModelSlotObj *)slot->unk20)->unk50;
            break;
    }
    for (i = 0; i < count; i++) {
        node = heapAlloc(sizeof(TexAnimNode));
        node->unk48 = 1;
        node->unk49 = 0;
        node->unk4A = entry[1];
        node->unk4C = entry[2];
        node->unk50 = 0;
        node->unk54 = 0;
        node->unk58 = entry[3];
        node->unk5C = entry[0];
        for (j = 0; j < node->unk58 - 1; j++) {
            node->unk60[j] = entry[4 + j];
        }
        node->unkD0 = entry[0x20];
        if (gGlobalOverlayFlags & 0x2000000) {
            node->unkD0 = 0;
        }
        node->unk3C = 0;
        node->unk40 = 0;
        node->unk34 = 0;
        node->unk36 = 0;
        node->unk38 = 0;
        node->unk3A = 0;
        node->unk30 = -1;
        if (type == 1) {
            dlFindTextureCommands(obj->unkA0, len1, entry[0], entry[1], &node->unk0[0], &node->unk0[1], &node->unk0[2]);
            dlFindTextureCommands(obj->unkA4, len1, entry[0], entry[1], &node->unk0[3], &node->unk0[4], &node->unk0[5]);
            dlFindTextureCommands(obj->unkA8, len2, entry[0], entry[1], &node->unk0[6], &node->unk0[7], &node->unk0[8]);
            dlFindTextureCommands(obj->unkAC, len2, entry[0], entry[1], &node->unk0[9], &node->unk0[10], &node->unk0[11]);
        }
        *tail = node;
        tail = &node->unkD4;
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
    ModelSlot *slot;
    ModelSlotObj *obj;

    slot = hashTableLookup(id) + ((0, gModelSlots)); // FAKE: comma swaps the index and global load temps (Q0304)
    obj = slot->unk20;
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            modelNodeAccessScrollSpeed(obj->unk50, node, speedX, speedY, speedXOut, speedYOut, get);
        }
    } else {
        modelNodeAccessScrollSpeed(obj->unkB8, node, speedX, speedY, speedXOut, speedYOut, get);
    }
}

void modelNodeAccessScrollSpeed(TexAnimNode *list, s16 node, s16 speedX, s16 speedY, s16 *speedXOut, s16 *speedYOut, u8 get) {
    node--;
    while (list != NULL && node != 0) {
        list = list->unkD4;
        node--;
    }
    if (list != NULL) {
        if (get != 0) {
            *speedXOut = list->unk38;
            *speedYOut = list->unk3A;
        } else {
            list->unk38 = speedX;
            list->unk3A = speedY;
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
    ModelSlot *slot;
    ModelSlotObj *obj;

    slot = hashTableLookup(id) + ((0, gModelSlots)); // FAKE: comma swaps the index and global load temps (Q0304)
    obj = slot->unk20;
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            modelNodeAccessAnimMode(obj->unk50, node, mode, modeOut, get);
        }
    } else {
        modelNodeAccessAnimMode(obj->unkB8, node, mode, modeOut, get);
    }
}

void modelNodeAccessAnimMode(TexAnimNode *list, s16 node, u8 mode, u8 *modeOut, u8 get) {
    node--;
    while (list != NULL && node != 0) {
        list = list->unkD4;
        node--;
    }
    if (list != NULL) {
        if (get != 0) {
            *modeOut = list->unk48;
        } else {
            list->unk48 = mode;
        }
    }
}


void modelSlotSetNodeFrame(s32 id, s16 node, s32 frame, s32 tick) {
    ModelSlot *slot;
    ModelSlotObj *obj;

    slot = hashTableLookup(id) + ((0, gModelSlots)); // FAKE: comma swaps the index and global load temps (Q0304)
    obj = slot->unk20;
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            modelNodeSetFrame(obj->unk50, node, frame, tick);
        }
    } else {
        modelNodeSetFrame(obj->unkB8, node, frame, tick);
    }
}

void modelNodeSetFrame(TexAnimNode *list, s16 node, s32 frame, s32 tick) {
    node--;
    while (list != NULL && node != 0) {
        list = list->unkD4;
        node--;
    }
    if (list != NULL) {
        if (frame != list->unk54 || tick != list->unk50) {
            list->unk49 = 1;
        }
        list->unk54 = frame;
        list->unk50 = tick;
    }
}

void dlFindTextureCommands(u32 *dl, s32 len, s32 addr, s32 findSecond, u32 **imgOut, u32 **img2Out, u32 **primOut) {
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
                *imgOut = dl;
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
                    *img2Out = dl;
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


typedef struct ModelQuadVertex {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 pad6;
    /* 0x08 */ s16 s;
    /* 0x0A */ s16 t;
    /* 0x0C */ u8 pad[4];
} ModelQuadVertex;

typedef struct ModelQuadData {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s16 x[4];
    /* 0x0C */ s16 y[4];
    /* 0x14 */ s16 z[4];
    /* 0x1C */ s16 uv[4][2];
    /* 0x2C */ u8 rgba[4];
} ModelQuadData;

typedef struct ModelQuadOutput {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 pad14[8];
    /* 0x1C */ ModelQuadVertex *unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[0x23];
    /* 0x44 */ u8 rgba[4];
    /* 0x48 */ s16 unk48;
} ModelQuadOutput;

void modelQuadBuildOutput(ModelSlot *owner, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 yOffset) {
    ModelQuadOutput *out;
    ModelQuadData *q;
    ModelAssetHeader *data;
    s32 i;
    s32 j;
    s16 sum;

    data = owner->unk24;
    out = owner->unk20;
    q = (ModelQuadData *)(data->unk70 + (s32)data + 4);
    out->unk0 = x;
    out->unk4 = y;
    out->unk8 = z;
    out->unkC = scale;
    out->unk10 = yOffset;
    out->unk20 = *(s32 *)(data->unk70 + (s32)data);
    sum = 0;
    out->unk1C = heapAlloc(out->unk20 << 6);
    for (i = 0; i < out->unk20; i++) {
        out->rgba[0] = q->rgba[0];
        out->rgba[1] = q->rgba[1];
        out->rgba[2] = q->rgba[2];
        out->rgba[3] = q->rgba[3];
        for (j = 0; j < 4; j++) {
            out->unk1C[(i << 2) + j].x = q->x[j];
            out->unk1C[(i << 2) + j].y = q->y[j];
            out->unk1C[(i << 2) + j].z = q->z[j];
            out->unk1C[(i << 2) + j].s = q->uv[j][0];
            out->unk1C[(i << 2) + j].t = q->uv[j][1];
            sum += q->y[j];
        }
        q++;
    }
    out->unk48 = sum / (out->unk20 * 4);
}



typedef struct ModelSlotAsset {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ void *unk14;
    /* 0x18 */ void *unk18;
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ void *unk24[4];
    /* 0x34 */ void *unk34[4];
    /* 0x44 */ u8 pad44[0xC];
    /* 0x50 */ s32 unk50;
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
    for (i = 0; i < textures->unk20; i++) {
        textures->unk24[i] = assetLoad(type, src[0], 1, 0);
        if (src[1] != -1) {
            textures->unk34[i] = assetLoad(type, src[1], 1, 0);
        } else {
            textures->unk34[i] = NULL;
        }
        src += 0x18;
    }
}

void modelSlotClearAssetTextures(ModelAssetHeader *asset, ModelSlotAsset *textures) {
    s32 i;

    for (i = 0; i < textures->unk20; i++) {
        textures->unk24[i] = NULL;
        textures->unk34[i] = NULL;
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
    gCsModelIds[gModelSlots[slot].unk8A] = -1;
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

typedef struct ModelSlotVectors {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} ModelSlotVectors;


void modelSlotGetTransformVectors(s32 slot, f32 *xOut, f32 *yOut, f32 *zOut, f32 *rotXOut, f32 *rotYOut, f32 *rotZOut, f32 *scaleOut, f32 *yOffsetOut, u8 isId) {
    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    *xOut = gModelSlots[slot].x;
    *yOut = gModelSlots[slot].y;
    *zOut = gModelSlots[slot].z;
    *rotXOut = gModelSlots[slot].rotY;
    *rotYOut = gModelSlots[slot].unk14;
    *rotZOut = gModelSlots[slot].unk18;
    *scaleOut = gModelSlots[slot].scale;
    *yOffsetOut = gModelSlots[slot].unk1C;
}

extern u8 gPlayerCount;

#define MODEL_TRANSFORM_SLOT0 ((ModelSlot *)((u8 *)gModelSlots + slot * 0x90))
#define MODEL_TRANSFORM_SLOT ((ModelSlot *)((u8 *)gModelSlots + off))

void modelSlotTransformBoundsAndNodes(s32 slot, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 scale, f32 yOffset, u8 setPos, u8 setRot, u8 setScale, u8 setYOffset, u8 isId) {
    ModelSlot *xform;
    ModelSlotVectors *vecs;
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
        MODEL_TRANSFORM_SLOT0->unk1C = yOffset;
        xform = MODEL_TRANSFORM_SLOT0;
        switch (xform->unk86) {
            case 2:
                vecs = xform->unk20;
                vecs->unk10 = yOffset;
                break;
            case 1:
                vecs = xform->unk20;
                vecs->unk1C = yOffset;
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
                vecs = xform->unk20;
                vecs->unk0 = x;
                vecs->unk4 = y;
                vecs->unk8 = z;
                break;
            case 1:
                vecs = xform->unk20;
                vecs->unk0 = x;
                vecs->unk4 = y;
                vecs->unk8 = z;
                break;
        }
    }
    if (setRot) {
        MODEL_TRANSFORM_SLOT->rotY = rotX;
        MODEL_TRANSFORM_SLOT->unk14 = rotY;
        MODEL_TRANSFORM_SLOT->unk18 = rotZ;
        xform = MODEL_TRANSFORM_SLOT;
        if (xform->unk86 == 1) {
            vecs = xform->unk20;
            vecs->unk10 = rotX;
            vecs->unk14 = rotY;
            vecs->unk18 = rotZ;
        }
    }
    if (setScale) {
        MODEL_TRANSFORM_SLOT->scale = scale;
        xform = MODEL_TRANSFORM_SLOT;
        switch (xform->unk86) {
            case 2:
                vecs = xform->unk20;
                vecs->unkC = scale;
                break;
            case 1:
                vecs = xform->unk20;
                vecs->unkC = scale;
                break;
        }
    }
    if ((setPos || setYOffset) && mapPurgeNodeList(MODEL_TRANSFORM_SLOT->unk20, &purgeOut, 0)) {
        xform = MODEL_TRANSFORM_SLOT;
        renderEntryAddOrUpdate(0, xform->unk86, xform->unk20, xform->x, xform->y, xform->z, xform->unk24->unk1E, xform->id, 0, purgeOut, 2);
    }
    xform = MODEL_TRANSFORM_SLOT;
    if (setPos || setYOffset || setRot) {
        modelEmitterSetPosition(xform->id, xform->x, xform->y, xform->z, xform->scale, xform->unk14);
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
        collisionTransformNode(slot, xform->unk24, xform->x, xform->y, xform->z, xform->rotY, xform->unk14, xform->unk18, xform->scale);
        xform = MODEL_TRANSFORM_SLOT;
        modelSlotBuildTriangleBufferThunk(slot, xform->unk24, xform->x, xform->y, xform->z, xform->rotY, xform->unk14, xform->unk18, xform->scale);
        xform = MODEL_TRANSFORM_SLOT;
    }
    modelSlotBuildVertPosList(slot, xform->unk24, xform->x, xform->y, xform->z, xform->rotY, xform->unk14, xform->unk18, xform->scale, 1);
    xform = MODEL_TRANSFORM_SLOT;
    modelSlotBuildNodePosList(slot, xform->unk24, xform->x, xform->y, xform->z, xform->rotY, xform->unk14, xform->unk18, xform->scale, 1);
}

typedef struct ActorBoundsView {
    /* 0x00 */ u8 pad0[0x5C];
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u8 pad5E[0x1E];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
} ActorBoundsView;

typedef struct ActorBoundsRef {
    /* 0x0 */ ActorBoundsView *actor;
    /* 0x4 */ s32 unk4;
} ActorBoundsRef;

extern ActorBoundsRef gActiveActors[];
extern u16 gActiveActorCount;

s32 activeActorBoxOverlapTest(f32 x, f32 y, f32 z, s16 radiusX, s16 radiusY, s16 radiusZ, u16 mask) {
    s32 i;
    ActorBoundsView *b;
    ActorBoundsView *a;
    s16 rx;
    s16 ry;
    s16 rz;

    rx = radiusX;
    ry = radiusY;
    rz = radiusZ;
    for (i = 0; i < gActiveActorCount; i++) {
        a = gActiveActors[i].actor;
        b = a;
        if (b->unk5C & mask) {
            if (x - radiusX <= b->unk7C && y - radiusY <= b->unk80 && z - radiusZ <= b->unk84 &&
                a->unk7C <= radiusX + x && a->unk80 <= radiusY + y && a->unk84 <= radiusZ + z) {
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

typedef struct ModelNodeChain {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ void *unk3C;
    /* 0x40 */ void *unk40;
    /* 0x44 */ u8 pad44[0x90];
    /* 0xD4 */ struct ModelNodeChain *unkD4;
} ModelNodeChain;

typedef struct ModelChainOwner {
    /* 0x00 */ u8 pad0[0x50];
    /* 0x50 */ ModelNodeChain *unk50;
    /* 0x54 */ ModelSlotSubNode *unk54;
    /* 0x58 */ u8 pad58[0x60];
    /* 0xB8 */ ModelNodeChain *unkB8;
    /* 0xBC */ ModelSlotSubNode *unkBC;
} ModelChainOwner;


void modelSlotFreeTexAnimNodes(ModelSlot *slot) {
    ModelNodeChain *node;
    ModelChainOwner *owner;
    ModelSlotSubNode *nodeList;
    ModelNodeChain *cur;

    switch (slot->unk86) {
        case 2:
            owner = slot->unk20;
            node = owner->unk50;
            nodeList = owner->unk54;
            modelSlotFreeAssetEntry(slot->unk24, slot->unk20);
            break;
        case 1:
            owner = slot->unk20;
            node = owner->unkB8;
            nodeList = owner->unkBC;
            modelSegmentFreeUnusedTextures(slot, slot->unk24, slot->unk20);
            break;
    }
    if (node != NULL) {
        do {
            if (node->unk3C != NULL) {
                assetFreeBuffer(node->unk3C, 0x9DB, 7);
            }
            if (node->unk40 != NULL) {
                assetFreeBuffer(node->unk40, 0x9DC, 7);
            }
            cur = node;
            node = node->unkD4;
            heapFree(cur);
        } while (node != NULL);
    }
    if (nodeList != NULL) {
        assetFreeBuffer(nodeList->unk0, 0x9E5, 7);
        heapFree(nodeList);
    }
}

typedef struct ModelNodeBufferChain {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ void *unk3C;
    /* 0x40 */ void *unk40;
    /* 0x44 */ u8 pad44[0x8C];
    /* 0xD0 */ u8 unkD0;
    /* 0xD4 */ struct ModelNodeBufferChain *unkD4;
} ModelNodeBufferChain;

typedef struct ModelNodeBufferOwner {
    /* 0x00 */ u8 pad0[0x50];
    /* 0x50 */ ModelNodeBufferChain *unk50;
    /* 0x54 */ u8 pad54[0x64];
    /* 0xB8 */ ModelNodeBufferChain *unkB8;
} ModelNodeBufferOwner;

void modelSlotFreeTexAnimBuffers(ModelNodeBufferOwner *owner, u8 type) {
    ModelNodeBufferChain *node;

    if (type != 1) {
        if (type == 2) {
            node = owner->unk50;
        } else {
            return;
        }
    } else {
        node = owner->unkB8;
    }
    if (node != NULL) {
        do {
            if (node->unk3C != NULL && node->unkD0 == 0) {
                assetFreeBuffer(node->unk3C, 0xA09, 7);
                node->unk3C = NULL;
            }
            if (node->unk40 != NULL && node->unkD0 == 0) {
                assetFreeBuffer(node->unk40, 0xA0E, 7);
                node->unk40 = NULL;
            }
            node = node->unkD4;
        } while (node != NULL);
    }
}

void modelSlotFreeAssetTextures(ModelSlotAsset *asset, u8 type) {
    void **p;
    ModelSlotAsset *base;
    s32 i;
    void *q;

    if (type == 2 && asset->unk50 == 0) {
        base = asset;
        i = 0;
        p = (void **)asset;
        if (base->unk20 > 0) {
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
            } while (i < base->unk20);
        }
    }
}

void modelSlotFreeNestedBuffer(s32 slotIndex, u8 isId) {
    ModelSlotSubNode *buffer;
    ModelSlotSubNode **listPtr;
    ModelSlot *slot;
    ModelSlotSubNode ***pp;

    if (isId == 1) {
        slotIndex = hashTableLookup(slotIndex);
    }
    slot = &gModelSlots[slotIndex];
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            listPtr = &((ModelChainOwner *)slot->unk20)->unk54;
        }
    } else {
        listPtr = &((ModelChainOwner *)slot->unk20)->unkBC;
    }
    pp = &listPtr; // FAKE: re-read through pp keeps listPtr in memory (direct use costs 1064)
    if (*pp != NULL) {
        buffer = **pp;
        if (buffer != NULL) {
            assetFreeBuffer(buffer->unk0, 0xA56, 7);
            heapFree(buffer);
            **pp = NULL;
        }
    }
}


void modelSlotFreeAssetEntry(void *asset, ModelSlotAsset *textures) {
    s32 i;

    for (i = 0; i < textures->unk20; i++) {
        if (textures->unk24[i] != NULL) {
            assetFreeBuffer(textures->unk24[i], 0xA69, 7);
        }
        if (textures->unk34[i] != NULL) {
            assetFreeBuffer(textures->unk34[i], 0xA6A, 7);
        }
    }
    assetFreeBuffer(asset, 0xA6E, 7);
    heapFreeDeferred(textures->unk1C);
    heapFreeDeferred(textures);
    heapFreeDeferred(textures->unk14);
    heapFreeDeferred(textures->unk18);
}

typedef struct DisplayListFreeRecord {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ ModelAssetHeader *unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ struct DisplayListFreeRecord *unk18;
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
    rec->unk18 = old;
    rec->unk0 = headStart;
    rec->unk4 = headEnd;
    rec->unk8 = tailStart;
    rec->unkC = tailEnd;
    rec->unk14 = gFrameCounter + 2;
    rec->unk10 = counter;
}



void displayListFreeQueueProcess(void) {
    DisplayListFreeRecord *cur;
    DisplayListFreeRecord *prev;
    DisplayListFreeRecord *next;

    cur = D_807F6160;
    prev = NULL;
    if (cur != NULL) {
        do {
            next = cur->unk18;
            if (gFrameCounter == cur->unk14) {
                cur->unk10->unk3C--;
                dlFreeUnusedTextures(cur->unk0, cur->unk4, 0, 0, cur->unk10->unk3C == 0);
                dlFreeUnusedTextures(cur->unk8, cur->unkC, 0, 1, cur->unk10->unk3C == 0);
                assetFreeBuffer(cur->unk10, 0xAB1, 7);
                if (prev == NULL) {
                    D_807F6160 = cur->unk18;
                } else {
                    prev->unk18 = cur->unk18;
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
    /* 0x0 */ u32 unk0;
    /* 0x4 */ s32 unk4;
} DisplayListCmd;

typedef struct ModelSegmentData {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ u32 unkA0;
    /* 0xA4 */ u32 unkA4;
    /* 0xA8 */ u32 unkA8;
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ u32 unkB0;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ TexAnimNode *unkB8;
    /* 0xBC */ s32 unkBC;
    /* 0xC0 */ u8 padC0[3];
    /* 0xC3 */ u8 unkC3;
} ModelSegmentData;

typedef struct ModelDisplayListObj {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[0x28];
    /* 0x30 */ s32 unk30;
} ModelDisplayListObj;

typedef struct ModelDisplayListPtrSet {
    /* 0x0 */ ModelDisplayListObj *unk0;
    /* 0x4 */ ModelDisplayListObj *unk4;
    /* 0x8 */ s32 *unk8;
} ModelDisplayListPtrSet;

typedef struct ModelSegmentNode {
    /* 0x00 */ ModelDisplayListPtrSet unk0[2];
    /* 0x18 */ ModelDisplayListPtrSet unk18[2];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 pad4B;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C[29];
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 padD1[3];
    /* 0xD4 */ struct ModelSegmentNode *unkD4;
} ModelSegmentNode;

typedef struct ModelSegmentOwner {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ s32 unk24[8];
    /* 0x44 */ u8 pad44[0xC];
    /* 0x50 */ ModelSegmentNode *unk50;
} ModelSegmentOwner;



void modelSegmentFreeUnusedTextures(ModelSlot *slot, ModelAssetHeader *asset, ModelSegmentData *seg) {
    TexAnimNode *nodes;
    u32 head, tail;
    u8 flag;

    nodes = seg->unkB8;
    head = seg->unkA8 - seg->unkA0;
    tail = seg->unkB0 - seg->unkA8;
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
            dlFreeUnusedTextures(seg->unkA0, seg->unkA0 + head * 8, seg->unkB8, 0, 0);
            dlFreeUnusedTextures(seg->unkA8, seg->unkA8 + tail * 8, seg->unkB8, 1, 0);
            nodes = seg->unkB8;
        } else {
            displayListFreeQueueAdd(seg->unkA0, seg->unkA0 + head * 8, seg->unkA8, seg->unkA8 + tail * 8, asset);
            nodes = seg->unkB8;
        }
    }
    if (nodes != NULL) {
        dlFreeUnusedTextures(seg->unkA4, seg->unkA4 + head * 8, nodes, 0, 0);
        dlFreeUnusedTextures(seg->unkAC, seg->unkAC + tail * 8, seg->unkB8, 1, 0);
        heapFreeDeferred((void *)seg->unkA4);
        heapFreeDeferred((void *)seg->unkAC);
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
            w = start->unk0;
            found = 0;
            if ((w >> 24) == 0xFD) {
                node = nodes;
                if (node != NULL) {
                    do {
                        switch (tail) {
                            case 0:
                                if ((u32 *)start == node->unk0[0]) {
                                    found = 1;
                                }
                                if ((u32 *)start == node->unk0[1]) {
                                    found = 1;
                                }
                                if ((u32 *)start == node->unk0[3]) {
                                    found = 1;
                                }
                                if ((u32 *)start == node->unk0[4]) {
                                    found = 1;
                                }
                                break;
                            case 1:
                                if ((u32 *)start == node->unk0[6]) {
                                    found = 1;
                                }
                                if ((u32 *)start == node->unk0[7]) {
                                    found = 1;
                                }
                                if ((u32 *)start == node->unk0[9]) {
                                    found = 1;
                                }
                                if ((u32 *)start == node->unk0[10]) {
                                    found = 1;
                                }
                                break;
                        }
                        node = node->unkD4;
                    } while (found == 0 && node != NULL);
                }
                if (found == 0) {
                    if (restore != 0) {
                        collisionBstLookupByHash(start->unk4, &bstValue, &bstNode);
                    }
                    assetFreeBuffer((void *)start->unk4, 0xB27, 7);
                    if (restore != 0) {
                        start->unk4 = bstNode;
                    }
                }
            }
            start++;
        } while (start != end);
    }
}

typedef struct ModelType2Obj {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ void *unk14;
    /* 0x18 */ void *unk18;
    /* 0x1C */ u8 pad1C[0x2E];
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ u8 pad58[3];
    /* 0x5B */ u8 unk5B;
} ModelType2Obj;

extern u8 gViewportCount;

void modelSlotInitFromAsset(ModelSlot *slot, s32 type) {
    ModelAssetHeader *hdr;
    ModelSegmentData *seg;
    s32 pad;
    void *objData;
    ModelType2Obj *obj;

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
            obj->unk4A = type;
            obj->unk50 = 0;
            obj->unk54 = 0;
            obj->unk4C = -1;
            obj->unk4E = 0;
            obj->unk5B = 0;
            obj->unk14 = heapAlloc(gViewportCount << 6);
            obj->unk18 = heapAlloc(gViewportCount << 6);
        }
    } else {
        seg = heapAlloc(0xC8);
        objData = seg;
        seg->unkB4 = type;
        seg->unkB8 = 0;
        seg->unkA0 = hdr->unk40 + (u32)hdr;
        seg->unkA8 = hdr->unk44 + (u32)hdr;
        seg->unkB0 = hdr->unk48 + (u32)hdr;
        seg->unkBC = 0;
        seg->unkB6 = -1;
        seg->unkC3 = 0;
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

typedef struct ModelSlotSegOwner {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ ModelSegmentData *unk20;
} ModelSlotSegOwner;

void renderReplaceSegment6Commands();

void modelSlotReplaceSegment6Commands(void *slot) {
    u32 head;
    ModelSegmentData *seg;
    u32 mid;
    u32 count;
    u32 len;
    u32 start;
    u32 size;

    seg = ((ModelSlotSegOwner *)slot)->unk20;
    mid = seg->unkA8;
    head = seg->unkA0;
    start = head;
    len = seg->unkB0 - mid;
    head = (mid - head) >> 3;
    count = len >> 3;
    size = head * 8;
    renderReplaceSegment6Commands(start, start + size, seg, len);
    len = count;
    renderReplaceSegment6Commands(seg->unkA8, seg->unkA8 + count * 8, seg, len);
}

void dlFreeSegmentCommandTextures(DisplayListCmd *start, DisplayListCmd *end, u8 restore) {
    s32 pad;
    u32 tag;
    s32 bstValue;
    s32 bstNode;

    if (start != end) {
        do {
            tag = start->unk0 >> 24;
            if (tag == 0xFD) {
                if (restore) {
                    collisionBstLookupByHash(start->unk4, &bstValue, &bstNode);
                }
                assetFreeBuffer((void *)start->unk4, 0xBCD, 7);
                if (restore) {
                    start->unk4 = bstNode;
                }
            }
            start++;
        } while (start != end);
    }
}


extern s16 D_80747D74;

void modelSlotsStepSegmentCommands(void) {
    u32 mid;
    ModelSegmentData *seg;
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
                mid = seg->unkA8;
                head = seg->unkA0;
                start = head;
                count = seg->unkB0 - mid;
                head = (mid - head) >> 3;
                count >>= 3;
                dlFreeSegmentCommandTextures((DisplayListCmd *)start, (DisplayListCmd *)start + head, flag);
                dlFreeSegmentCommandTextures((DisplayListCmd *)seg->unkA8, (DisplayListCmd *)seg->unkA8 + count, flag);
            }
        }
    }
}





void modelSlotResolveAssetTextures(ModelSlot *slot, u8 forceLoad, u8 force) {
    ModelSegmentData *seg;
    ModelAssetHeader *obj;
    ModelSlotAsset *volatile textures; // FAKE: memory copy of seg that the else branch reads back (target reloads 0x3C(sp))
    u32 temp;
    u32 cmds;
    u32 count;
    ModelSegmentNode *node;
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
                count = seg->unkB0 - seg->unkA8;
                cmds = seg->unkA0;
                temp = (seg->unkA8 - cmds) >> 3;
                count = count >> 3;
                node = (ModelSegmentNode *)((ModelSegmentData *)slot->unk20)->unkB8; // FAKE: re-reads slot->unk20 instead of seg (pre-existing, now tagged; seg->unkB8 drops the sw a0,72(sp) slot home)
                size0 = temp * 8;
                temp = 0; // FAKE: dead store keeps size0 a variable instead of a propagated expression
                res = dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)(cmds + size0), node, force);
                cmds = seg->unkA8;
                size1 = count * 8;
                count = 0; // FAKE: dead store keeps size1 a variable instead of a propagated expression
                res |= dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)(cmds + size1), node, force);
                if (node != NULL) {
                    cmds = seg->unkA4;
                    res |= dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)(cmds + size0), node, force);
                    cmds = seg->unkAC;
                    res |= dlResolveNodeTextures((DisplayListCmd *)cmds, (DisplayListCmd *)(cmds + size1), node, force);
                    if (seg->unkA0 == 0) {} // FAKE: dead test keeps seg live past the last call so it stays in s0
                }
                if (res != 0) {
                    obj->unk0 &= ~0x10;
                }
            } else {
                if (textures->unk50 != 0 || forceLoad != 0) {
                    modelSlotLoadAssetTextures(obj, textures);
                } else {
                    modelSlotClearAssetTextures(obj, textures);
                }
            }
        }
    }
}


s32 dlResolveNodeTextures(DisplayListCmd *start, DisplayListCmd *end, ModelSegmentNode *nodes, u8 keep) {
    u32 w;
    u32 tag;
    s32 result;
    s32 found;
    ModelSegmentNode *node;

    result = 0;
    if (start != end) {
        do {
            w = start->unk0;
            found = 0;
            tag = w >> 24;
            if (0xFD == tag) {
                node = nodes;
                if (node != NULL) {
                    do {
                        if (start->unk4 == node->unk5C[0]) {
                            found = 1;
                        } else {
                            node = node->unkD4;
                        }
                    } while (found == 0 && node != NULL);
                }
                if (found == 0) {
                    start->unk4 = (s32)assetLoad(0x19, start->unk4, keep == 0, 0);
                    if (start->unk4 & 7) {
                        start->unk4 &= ~0xF;
                        result = 1;
                    }
                }
            }
            start++;
        } while (start != end);
    }
    return result;
}

typedef struct ModelRenderAnimObj {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ Mtx unk20[2];
    /* 0xA0 */ Gfx *unkA0[2];
    /* 0xA8 */ Gfx *unkA8[2];
    /* 0xB0 */ void *unkB0;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ void *unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 unkC2;
    /* 0xC3 */ u8 unkC3;
    /* 0xC4 */ u8 unkC4;
    /* 0xC5 */ u8 unkC5;
} ModelRenderAnimObj;

s32 playerSlotMatchesSizeMask(s32, u8, s32);

Gfx *renderModelAnimatedSlot(ModelRenderAnimObj *obj, Gfx *gfx, f32 camX, f32 camY, f32 camZ, u8 useLight, s16 lightArg, s32 unused) {
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
        dx = gPlayerSlots[gCurrentPlayerIndex].eyeX - obj->unk0;
        dy = gPlayerSlots[gCurrentPlayerIndex].eyeY - obj->unk4;
        dz = gPlayerSlots[gCurrentPlayerIndex].eyeZ - obj->unk8;
        dx *= dx;
        dy *= dy;
        dz *= dz;
        dist = sqrtf(dx + dy + dz);
        drawDist = renderScaleDistanceByFov(obj->unkC0);
        if (obj->unkC5 & 1) {
            drawDist = obj->unkC0;
        }
        if (drawDist < dist) {
            return gfx;
        }
    }
    if (obj->unkC3 != 0) {
        lightQueueKeyframed(obj->unkC3, obj->unkB6, obj->unk0, obj->unk4, obj->unk8, obj->unkC0, dist / drawDist, lightArg);
    }
    if (obj->unkB4 == 0 || obj->unkB4 == 0x241) {
        return gfx;
    }
    if (obj->unkB4 == 0x74 || obj->unkB4 == 0x288 || obj->unkB4 == 0x290) {
        obj->unk14 += 10.0;
    }
    guScaleF(mtx, obj->unkC, obj->unkC, obj->unkC);
    if (obj->unk10 != 0.0) {
        guRotateF(tmpMtx, obj->unk10, 1.0f, 0.0f, 0.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
    }
    if (obj->unk14 != 0.0) {
        guRotateF(tmpMtx, obj->unk14, 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
    }
    if (obj->unk18 != 0.0) {
        guRotateF(tmpMtx, obj->unk18, 0.0f, 0.0f, 1.0f);
        guMtxCatF(mtx, tmpMtx, mtx);
    }
    if (obj && obj && obj) {} // FAKE: dead block pads as1's XBB window (limit 10) so the rotation compares don't hoist `addiu a0,sp,184` (6 guards needed)
    if (obj && obj && obj) {} // FAKE: same
    if (obj && obj && obj) {} // FAKE: same
    if (obj && obj && obj) {} // FAKE: same
    if (obj && obj && obj) {} // FAKE: same
    if (obj && obj && obj) {} // FAKE: same
    guTranslateF(tmpMtx, obj->unk0, obj->unk4, obj->unk8);
    guMtxCatF(mtx, tmpMtx, mtx);
    guMtxF2L(mtx, &obj->unk20[gGfxBufferIndex]);
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 8, osVirtualToPhysical(obj->unkB0));
    animBuffers = NULL;
    if (obj->unkB6 != -1) {
        slotIdx = hashTableLookup(obj->unkB6);
        modelSlotResolveAssetTextures(&gModelSlots[slotIdx], 0, 1);
        animBuffers = gModelSlots[slotIdx].unk78;
        if (playerSlotMatchesSizeMask(gModelSlots[slotIdx].unk24->unk0, gCurrentPlayerIndex, (s32)animBuffers) != 0) {
            return gfx;
        }
    }
    if (animBuffers != NULL) {
        gSPSegment(gfx++, 9, osVirtualToPhysical(animBuffers->frames[gGfxBufferIndex]));
    }
    gSPMatrix(gfx++, osVirtualToPhysical(&obj->unk20[gGfxBufferIndex]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    if (obj->unkB8 != NULL) {
        sel = gGfxBufferIndex;
        texAnimUpdateNodes((ModelSegmentData *)obj);
    } else {
        sel = 0;
    }
    gSPSegment(gfx++, 10, osVirtualToPhysical(obj->unkA0[sel]));
    gSPClearGeometryMode(gfx++, G_FOG | G_CULL_BOTH);
    if (useLight && obj->unkC2 == 0) {
        f32 yOffset;

        model = gModelSlots[slotIdx].unk7C;
        if (model != NULL) {
            yOffset = model->unk98;
        } else {
            yOffset = 0.0f;
        }
        lightSampleColorAtPosition(obj->unk0, obj->unk4 + yOffset, obj->unk8, 0, &red, &green, &blue, lightArg);
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
        if (obj->unkB6 != -1 && (model = gModelSlots[slotIdx].unk7C) != NULL && model->unk60 == 1) {
            csUpdateStepAndInterpolation(model);
            alpha = (gModelSlots[slotIdx].unk7C)->unk64;
        } else {
            renderCalcPlayerDistanceAlpha(obj->unk0, obj->unk4, obj->unk8, obj->unkC0, obj->unkB4, &alpha);
            if (obj->unkB6 != -1) {
                model = gModelSlots[slotIdx].unk7C;
                if (model != NULL && gViewportCount == 1) {
                    model->unk62 = alpha;
                }
            }
            if (obj->unkB6 != -1) {
                model = gModelSlots[slotIdx].unk7C;
                if (model != NULL) {
                    csUpdateStepAndInterpolation(model);
                }
            }
            if (obj->unkB6 != -1) {
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
        if (obj->unkB6 != -1) {
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
        gSPDisplayList(gfx++, osVirtualToPhysical(obj->unkA0[sel]));
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(obj->unkA8[sel]));
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


Gfx *renderModelQuadGfx(RenderQuadModelObj *obj, Gfx *gfx, f32 camX, f32 camY, f32 camZ, u8 useLight, s16 lightArg) {
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
        dx = camX - obj->unk0;
        dy = camY - obj->unk4;
        dz = camZ - obj->unk8;
        dx *= dx;
        dy *= dy;
        dz *= dz;
        dist = sqrtf(dx + dy + dz);
        limit = renderScaleDistanceByFov(obj->unk58);
        if ((f32)limit < dist) {
            return gfx;
        }
    }
    if (obj->unk5B != 0) {
        lightQueueKeyframed(obj->unk5B, obj->unk4C, obj->unk0, obj->unk4, obj->unk8, obj->unk58, dist / (f32)limit, lightArg);
    }
    if (useLight != 0) {
        if (mapPointOutsideClipBounds(obj->unk0, obj->unk4, obj->unk8, 0, 0) != 0) {
            return gfx;
        }
    } else {
        limit = -0x8000;
        dist = 1.0f;
    }
    if (obj->unk4E & 0x10) {
        return gfx;
    }
    if (obj->unk4E & 8) {
        camProjectToScreen(obj->unk0, obj->unk4, obj->unk8, &screenX, &screenY, 0, 1.0f, gCurrentPlayerIndex);
        mapSearchTableAddProbe(obj, screenX, screenY, dist);
        if (mapSearchTableGetValue(obj) != 0) {
            return gfx;
        }
    }
    D_807F5FD8 += 1;
    if (obj->unk24 == 0) {
        modelSlotLoadAssetTextures(gModelSlots[(s16)hashTableLookup(obj->unk4C)].unk24, (ModelSlotAsset *)obj);
    }
    modelCalcFacingAngles(obj->unk0, obj->unk4, obj->unk8, camX, camY, camZ, &angleX, &angleY, &angleZ, obj->unk4E & 4);
    guTranslateF(modelMtx, 0.0f, -obj->unk48, 0.0f);
    if (angleX != 0.0) {
        guRotateF(tmpMtx, angleX, 1.0f, 0.0f, 0.0f);
        guMtxCatF(modelMtx, tmpMtx, modelMtx);
    }
    if (angleY != 0.0) {
        guRotateF(tmpMtx, angleY, 0.0f, 1.0f, 0.0f);
        guMtxCatF(modelMtx, tmpMtx, modelMtx);
    }
    if (obj->unkC != 1.0) {
        guScaleF(tmpMtx, obj->unkC, obj->unkC, obj->unkC);
        guMtxCatF(modelMtx, tmpMtx, modelMtx);
    }
    guTranslateF(tmpMtx, obj->unk0, obj->unk4 + obj->unk48 * obj->unkC, obj->unk8);
    guMtxCatF(modelMtx, tmpMtx, modelMtx);
    switch (gGfxBufferIndex) {
    case 0:
        mtx = obj->unk14 + gCurrentPlayerIndex;
        break;
    case 1:
        mtx = obj->unk18 + gCurrentPlayerIndex;
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
    modelKongVisibilityCheck(obj->unk4A, &opaque, &alpha);
    if (useLight != 0 && obj->unk5A == 0) {
        lightSampleColorAtPosition(obj->unk0, obj->unk4, obj->unk8, 0, &red, &green, &blue, lightArg);
        scale = (f32)(u32)obj->unk5C / 15.0f;
        red = (f32)(u32)red * scale;
        green = (f32)(u32)green * scale;
        blue = (f32)(u32)blue * scale;
    } else {
        red = green = blue = 0xFF;
    }
    for (i = 0; i < obj->unk20; i++) {
        texAnimFindNodeFrame((ModelSegmentOwner *)obj, i, &texA, &texB, &dualTex, &primLod);
        gDPPipeSync(gfx++);
        if (obj->unk4E & 2) {
            if (opaque != 0) {
                gSPSetOtherMode(gfx++, G_SETOTHERMODE_L, 3, 29, 0x0C193078);
            } else {
                gSPSetOtherMode(gfx++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
            }
        } else if (obj->unk4E & 1) {
            gSPSetOtherMode(gfx++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
        } else {
            gSPSetOtherMode(gfx++, G_SETOTHERMODE_L, 3, 29, 0x0C184240);
        }
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, 20, 2, 0x100000);
        if ((obj->unk4E & 1) || (obj->unk4E & 2)) {
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
                switch (obj->unk46) {
                case 0:
                    gDPLoadTextureBlock_4b(gfx++, texA + 0x80000000, obj->unk47, obj->unk44, obj->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    if (obj->unk47 == 2) {
                        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj->unk34[i]);
                        gDPTileSync(gfx++); gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                        gDPLoadSync(gfx++);
                        gDPLoadTLUTCmd(gfx++, G_TX_LOADTILE, 15); gDPPipeSync(gfx++);
                        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
                        usedTlut = 1;
                    }
                    break;
                case 1:
                    gDPLoadTextureBlock(gfx++, texA + 0x80000000, obj->unk47, G_IM_SIZ_8b, obj->unk44, obj->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    if (obj->unk47 == 2) {
                        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj->unk34[i]);
                        gDPTileSync(gfx++); gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                        gDPLoadSync(gfx++);
                        gDPLoadTLUTCmd(gfx++, G_TX_LOADTILE, 255); gDPPipeSync(gfx++);
                        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
                        usedTlut = 1;
                    }
                    break;
                case 2:
                    gDPLoadTextureBlock(gfx++, texA + 0x80000000, obj->unk47, G_IM_SIZ_16b, obj->unk44, obj->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 3:
                    gDPLoadTextureBlock(gfx++, texA + 0x80000000, obj->unk47, G_IM_SIZ_32b, obj->unk44, obj->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
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
            gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, ((obj->unk44 * obj->unk45 * 2) >> 1) - 1, CALC_DXT(obj->unk44, 2));
            gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texB);
            gDPTileSync(gfx++);
            gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadSync(gfx++);
            gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, ((obj->unk44 * obj->unk45 * 2) >> 1) - 1, CALC_DXT(obj->unk44, 2));
            gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, obj->unk44 / 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
            gDPSetTileSize(gfx++, G_TX_RENDERTILE, 2, 2, ((obj->unk44 - 1) << 2) + 2, ((obj->unk45 - 1) << 2) + 2);
            gDPSetTile(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, obj->unk44 / 4, 0x100, 1, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
            gDPSetTileSize(gfx++, 1, 2, 2, ((obj->unk44 - 1) << 2) + 2, ((obj->unk45 - 1) << 2) + 2);
            D_807F600C = NULL;
            break;
        }
        gSPVertex(gfx++, osVirtualToPhysical(obj->unk1C + vtxOffset), 4, 0);
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

typedef struct PlayerCtlRef {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ struct PlayerControllerState *unk174;
} PlayerCtlRef;

typedef struct PlayerControllerState {
    /* 0x000 */ u8 pad0[0x1F4];
    /* 0x1F4 */ s32 unk1F4;
} PlayerControllerState;

typedef struct PlayerActorRef {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
} PlayerActorRef;

typedef struct PlayerSlotEntry {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ PlayerActorRef *unk4;
    /* 0x008 */ u8 pad8[0x2E8];
} PlayerSlotEntry; /* 0x2F0 */

extern u8 gPlayerCharacterId[];
typedef struct PlayerKongRecord {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[0x5D];
} PlayerKongRecord; /* 0x5E */

typedef struct PlayerKongArray {
    /* 0x000 */ PlayerKongRecord kong[8];
    /* 0x2F0 */ u8 pad2F0[0x16];
} PlayerKongArray; /* 0x306 */

extern PlayerKongArray D_807FC952[];

#define PLAYER_CURRENT_OBJ ((PlayerSlotEntry *)gPlayerSlots)[gCurrentPlayerIndex].unk4

void modelKongVisibilityCheck(s16 type, u8 *visibleOut, s16 *alphaOut) {
    s32 hit = 0;
    PlayerControllerState *ctl;

    switch (type) {
    case 0x24:
        if (PLAYER_CURRENT_OBJ->unk58 != 3) {
            hit = 1;
        }
        break;
    case 0x1D:
        if (PLAYER_CURRENT_OBJ->unk58 != 2) {
            hit = 1;
        }
        break;
    case 0x1C:
        if (PLAYER_CURRENT_OBJ->unk58 != 5) {
            hit = 1;
        }
        break;
    case 0x23:
        if (PLAYER_CURRENT_OBJ->unk58 != 4) {
            hit = 1;
        }
        break;
    case 0x27:
        if (PLAYER_CURRENT_OBJ->unk58 != 6) {
            hit = 1;
        }
        break;
    case 0xD:
        if (PLAYER_CURRENT_OBJ->unk58 != 2) {
            hit = 1;
        }
        break;
    case 0xA:
        if (PLAYER_CURRENT_OBJ->unk58 != 3) {
            hit = 1;
        }
        break;
    case 0x16:
        if (PLAYER_CURRENT_OBJ->unk58 != 5) {
            hit = 1;
        }
        break;
    case 0x1E:
        if (PLAYER_CURRENT_OBJ->unk58 != 4) {
            hit = 1;
        }
        break;
    case 0x1F:
        if (PLAYER_CURRENT_OBJ->unk58 != 6) {
            hit = 1;
        }
        break;
    case 0x2B:
        if (PLAYER_CURRENT_OBJ->unk58 != 2) {
            hit = 1;
        }
        break;
    case 0x208:
        if (PLAYER_CURRENT_OBJ->unk58 != 3) {
            hit = 1;
        }
        break;
    case 0x207:
        if (PLAYER_CURRENT_OBJ->unk58 != 5) {
            hit = 1;
        }
        break;
    case 0x205:
        if (PLAYER_CURRENT_OBJ->unk58 != 4) {
            hit = 1;
        }
        break;
    case 0x206:
        if (PLAYER_CURRENT_OBJ->unk58 != 6) {
            hit = 1;
        }
        break;
    case 0x11:
        if ((D_807FC952[gCurrentPlayerIndex].kong[gPlayerCharacterId[gCurrentPlayerIndex]].unk0 & 3) != 3) {
            hit = 1;
        }
        break;
    case 0x8F:
        if (!(D_807FC952[gCurrentPlayerIndex].kong[gPlayerCharacterId[gCurrentPlayerIndex]].unk0 & 1)) {
            hit = 1;
        }
        break;
    case 0x98:
        ctl = ((PlayerCtlRef *)PLAYER_CURRENT_OBJ)->unk174;
        if (!(ctl->unk1F4 & 1)) {
            hit = 1;
        }
        break;
    case 0x8E:
        ctl = ((PlayerCtlRef *)PLAYER_CURRENT_OBJ)->unk174;
        if (!(ctl->unk1F4 & 2)) {
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

typedef struct ModelSubObjectFlags {
    /* 0x00 */ u8 pad0[0x4E];
    /* 0x4E */ u8 unk4E;
} ModelSubObjectFlags;

void func_806398E4(s32 slot, u8 isId, u8 enable) {
    ModelSubObjectFlags *obj;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    obj = gModelSlots[slot].unk20;
    if (enable != 0) {
        obj->unk4E |= 1;
    } else {
        obj->unk4E &= ~1;
    }
    obj->unk4E &= ~2;
}

void texAnimUpdateNodes(ModelSegmentData *seg) {
    s32 pad;
    s32 texA;
    s32 texB;
    u8 dualTex;
    s16 primLod;
    ModelSegmentNode *node;
    s32 *dst;

    node = (ModelSegmentNode *)seg->unkB8;
    if (node != NULL) {
        do {
            texAnimNodeUpdateBuffers(node, &texA, &texB, &dualTex, &primLod);
            if (node->unk0[gGfxBufferIndex].unk0 != NULL) {
                node->unk0[gGfxBufferIndex].unk0->unk4 = texA;
                if (dualTex == 0) {
                    dst = &node->unk0[gGfxBufferIndex].unk0->unk30; // FAKE: dst pointer temp for both 0xF2000000 stores (direct field stores fail fdiff)
                    *dst = (node->unk34 << 12) | 0xF2000000 | node->unk36;
                }
            }
            if (node->unk18[gGfxBufferIndex].unk0 != NULL) {
                node->unk18[gGfxBufferIndex].unk0->unk4 = texA;
                if (dualTex == 0) {
                    dst = &node->unk18[gGfxBufferIndex].unk0->unk30;
                    *dst = (node->unk34 << 12) | 0xF2000000 | node->unk36;
                }
            }
            if (gFrameCounter != node->unk30) {
                node->unk34 += node->unk38;
                if (node->unk34 >= 0x1000) {
                    node->unk34 = 0;
                }
                if (node->unk34 < 0) {
                    node->unk34 = 0xFFF;
                }
                node->unk36 += node->unk3A;
                if (node->unk36 >= 0x1000) {
                    node->unk36 = 0;
                }
                if (node->unk36 < 0) {
                    node->unk36 = 0xFFF;
                }
            }
            if (dualTex != 0) {
                if (node->unk0[gGfxBufferIndex].unk4 != NULL) {
                    node->unk0[gGfxBufferIndex].unk4->unk4 = texB;
                }
                if (node->unk18[gGfxBufferIndex].unk4 != NULL) {
                    node->unk18[gGfxBufferIndex].unk4->unk4 = texB;
                }
                if (node->unk0[gGfxBufferIndex].unk8 != NULL) {
                    *node->unk0[gGfxBufferIndex].unk8 = primLod + 0xFA000000;
                }
                if (node->unk18[gGfxBufferIndex].unk8 != NULL) {
                    *node->unk18[gGfxBufferIndex].unk8 = primLod + 0xFA000000;
                }
            }
            node->unk30 = gFrameCounter;
            node = node->unkD4;
        } while (node != NULL);
    }
}


void texAnimFindNodeFrame(ModelSegmentOwner *owner, s32 index, s32 *texAOut, s32 *texBOut, u8 *dualOut, s16 *lodOut) {
    ModelSegmentNode *node;
    s32 key;
    s32 found;

    node = owner->unk50;
    if (node != NULL) {
        key = owner->unk24[index];
        found = 0;
        while (node != NULL && found == 0) {
            if (key == node->unk44) {
                found = 1;
            } else {
                node = node->unkD4;
            }
        }
        if (found != 0) {
            texAnimNodeUpdateBuffers(node, texAOut, texBOut, dualOut, lodOut);
            node->unk30 = gFrameCounter;
            return;
        }
        *dualOut = 0;
        *texAOut = key;
        return;
    }
    *dualOut = 0;
    *texAOut = owner->unk24[index];
}



void texAnimNodeUpdateBuffers(ModelSegmentNode *node, s32 *texAOut, s32 *texBOut, u8 *dualOut, s16 *lodOut) {
    s32 advanced;
    s32 frameB;
    s32 frameA;
    s32 oldBufB;
    s32 oldBufA;

    if (gFrameCounter == node->unk30) {
        advanced = 0;
    } else {
        advanced = (u8)texAnimNodeAdvance(node, &frameB, &frameA);
    }
    if (advanced != 0 || node->unk3C == 0) {
        oldBufB = node->unk3C;
        if (node->unk4A != 0) {
            oldBufA = node->unk40;
            if (oldBufA == 0 || node->unk49 != 0) {
                if (oldBufB != 0) {
                    assetFreeBuffer((void *)oldBufB, 0xFCB, 7);
                }
                if (node->unkD0 != 0) {
                    collisionResolveWallContact();
                }
                node->unk3C = (s32)assetLoad(7, node->unk5C[frameB], 0, 0);
                oldBufA = node->unk40;
                if (oldBufA != 0) {
                    assetFreeBuffer((void *)oldBufA, 0xFCE, 7);
                }
                if (node->unkD0 != 0) {
                    collisionResolveWallContact();
                }
                node->unk40 = (s32)assetLoad(7, node->unk5C[frameA], 0, 0);
            } else {
                if (oldBufB != 0) {
                    assetFreeBuffer((void *)oldBufB, 0xFD5, 7);
                }
                oldBufA = node->unk40;
                node->unk3C = oldBufA;
                if (node->unkD0 != 0) {
                    collisionResolveWallContact();
                }
                node->unk40 = (s32)assetLoad(7, node->unk5C[frameA], 0, 0);
            }
        } else {
            if (oldBufB != 0) {
                assetFreeBuffer((void *)oldBufB, 0xFDF, 7);
            }
            if (node->unkD0 != 0) {
                collisionResolveWallContact();
            }
            node->unk3C = (s32)assetLoad(7, node->unk5C[frameB], 0, 0);
        }
    }
    node->unk49 = 0;
    *dualOut = node->unk4A;
    if (node->unk4A != 0) {
        *lodOut = (s16)(((f32)node->unk50 / (f32)node->unk4C) * 255.0f);
    }
    *texAOut = node->unk3C;
    *texBOut = node->unk40;
}

s32 texAnimNodeAdvance(ModelSegmentNode *node, s32 *frameOut, s32 *nextFrameOut) {
    s32 result;
    s32 frame;

    result = 0;
    switch (node->unk48) {
        case 1:
            node->unk50 += 1;
            if (node->unk50 == node->unk4C) {
                node->unk50 = 0;
                node->unk54 += 1;
                if (node->unk54 == node->unk58) {
                    node->unk54 = 0;
                }
                result = 1;
            }
            break;
        case 0:
            if (node->unk49 != 0) {
                result = 1;
            }
            break;
        default:
            break;
    }
    *frameOut = node->unk54;
    if (node->unk54 + 1 == node->unk58) {
        *nextFrameOut = 0;
    } else {
        frame = node->unk54;
        *nextFrameOut = frame + 1;
    }
    return result;
}

// Sprite draw node: built by spriteListBuildDisplayChain (depth-sorted), drawn by spriteListRender; 0x38 bytes.
typedef struct SpriteDisplayNode {
    /* 0x00 */ u32 key;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30;
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

typedef struct ModelAnimTrackLink {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 pad60[0x74];
    /* 0xD4 */ struct ModelAnimTrackLink *unkD4;
} ModelAnimTrackLink;


typedef struct ModelSpriteSource {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x2E];
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ ModelAnimTrackLink *unk50;
    /* 0x54 */ SpriteDisplayNode *unk54;
    /* 0x58 */ u8 pad58[0x60];
    /* 0xB8 */ ModelAnimTrackLink *unkB8;
    /* 0xBC */ SpriteDisplayNode *unkBC;
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
    ModelAnimTrackLink *link;
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
                if (d->unk4E & 0x10) {
                    tgt = NULL;
                } else {
                    x = d->unk0;
                    y = d->unk4 - d->unk10;
                    z = d->unk8;
                    tgt = d->unk54;
                    link = d->unk50;
                    modelCalcFacingAngles(x, y, z, camX, camY, camZ, &angleX, &angleY, &angleZ, 0);
                    scale = d->unkC;
                }
                break;
            case 1:
                d1 = listA->unk0;
                tgt = d1->unkBC;
                link = d1->unkB8;
                x = d1->unk0;
                z = d1->unk8;
                y = d1->unk4 - d1->unk1C;
                angleY = d1->unk14;
                scale = d1->unkC;
                break;
            default:
                tgt = NULL;
                break;
            }
            if (tgt != NULL) {
                r = tgt->unk2C;
                d2 = (camX - x) * (camX - x) + (camY - y) * (camY - y) + (camZ - z) * (camZ - z);
                if (d2 < r * r) {
                    r2 = tgt->unk2A;
                    if (d2 < r2 * r2) {
                        tgt->unk2F = tgt->unk2E;
                    } else {
                        d2 = sqrtf(d2);
                        tgt->unk2F = (u32)((f32)(u32)tgt->unk2E - ((f32)(u32)tgt->unk2E * (d2 - (f32)tgt->unk2A)) / (f32)(tgt->unk2C - tgt->unk2A));
                    }
                    if (tgt->unk24 != -1) {
                        found = 0;
                        if (link != NULL) {
                            do {
                                if (link->unk5C == tgt->unk24) {
                                    found = 1;
                                } else {
                                    link = link->unkD4;
                                }
                            } while (found == 0 && link != NULL);
                        }
                        tgt->unk26 = angleY;
                        tgt->unk26 += link->unk54 * 0x168 / link->unk58 + link->unk50 * 360.0 / link->unk58 / link->unk4C;
                    } else {
                        tgt->unk26 = angleY;
                    }
                    tgt->unk14 = x;
                    tgt->unk26 += tgt->unk28;
                    tgt->unk18 = y;
                    tgt->unk1C = z;
                    tgt->next = NULL;
                    tgt->unk10 = tgt->unkC * scale;
                    tgt->unk12 = tgt->unkE * scale;
                    result = spriteListInsertByDepth(result, tgt);
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

SpriteDisplayNode *spriteListInsertByDepth(SpriteDisplayNode *head, SpriteDisplayNode *node) {
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
    ModelSlotObjCoordHolder *obj;
    f32 *p;

    if (isId == 1) {
        slot = hashTableLookup(slot);
    }
    obj = gModelSlots[slot].unk20;
    switch (gModelSlots[slot].unk86) {
    case 2:
        p = (f32 *)obj->unk54;
        break;
    case 1:
        p = (f32 *)obj->unkBC;
        break;
    }
    if (p != NULL) {
        p[1] = value;
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
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, list->unk2F);
            if (list->unk30 != 0 && flag == 0) {
                gSPSetGeometryMode(gfx++, G_ZBUFFER);
                gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2);
                flag = 1;
            }
            if (list->unk30 == 0 && flag != 0) {
                gSPClearGeometryMode(gfx++, G_ZBUFFER);
                gDPSetRenderMode(gfx++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
                flag = 0;
            }
            if (list->key != lastTex) {
                switch (list->unkB) {
                case 0:
                    gDPLoadTextureBlock_4b(gfx++, list->key + 0x80000000, list->unkA, list->unk8, list->unk9, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                case 1:
                    gDPLoadTextureBlock(gfx++, list->key + 0x80000000, list->unkA, G_IM_SIZ_8b, list->unk8, list->unk9, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                case 2:
                    gDPLoadTextureBlock(gfx++, list->key + 0x80000000, list->unkA, G_IM_SIZ_16b, list->unk8, list->unk9, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                }
                lastTex = list->key;
            }
            vtxs[vtxIdx].v.tc[0] = 0;
            vtxs[vtxIdx].v.tc[1] = 0;
            vtxs[vtxIdx + 1].v.tc[0] = list->unk8 << 5;
            vtxs[vtxIdx + 1].v.tc[1] = 0;
            vtxs[vtxIdx + 2].v.tc[0] = list->unk8 << 5;
            vtxs[vtxIdx + 2].v.tc[1] = list->unk9 << 5;
            vtxs[vtxIdx + 3].v.tc[0] = 0;
            vtxs[vtxIdx + 3].v.tc[1] = list->unk9 << 5;
            vtxs[vtxIdx].v.ob[1] = 0;
            vtxs[vtxIdx + 1].v.ob[1] = 0;
            vtxs[vtxIdx + 2].v.ob[1] = 0;
            vtxs[vtxIdx + 3].v.ob[1] = 0;
            vtxs[vtxIdx].v.ob[0] = -list->unk10;
            vtxs[vtxIdx].v.ob[2] = -list->unk12;
            vtxs[vtxIdx + 1].v.ob[0] = list->unk10;
            vtxs[vtxIdx + 1].v.ob[2] = -list->unk12;
            vtxs[vtxIdx + 2].v.ob[0] = list->unk10;
            vtxs[vtxIdx + 2].v.ob[2] = list->unk12;
            vtxs[vtxIdx + 3].v.ob[0] = -list->unk10;
            vtxs[vtxIdx + 3].v.ob[2] = list->unk12;
            guScaleF(accum, list->unk4, 1.0f, list->unk4);
            guRotateF(tmp, list->unk26, 0.0f, 1.0f, 0.0f);
            guMtxCatF(accum, tmp, accum);
            if (list->unk22 < 0x3E8) {
                guRotateF(tmp, -(list->unk20 / 4095.0 * 360.0), 0.0f, 1.0f, 0.0f);
                guMtxCatF(accum, tmp, accum);
            }
            guRotateF(tmp, 90.0 - list->unk22 / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
            guMtxCatF(accum, tmp, accum);
            if (list->unk22 < 0x3E8) {
                guRotateF(tmp, list->unk20 / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
                guMtxCatF(accum, tmp, accum);
            }
            guTranslateF(tmp, list->unk14, list->unk18, list->unk1C);
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
                    D_807F60B0[D_807F60A8] = slots[idx].unk8A;
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
                        D_807F60B0[D_807F60A8] = gModelSlots[slot].unk8A;
                        D_807F60A8++;
                        csStateTickTimers(obj);
                        csStateUpdate(obj, D_807F6030[i].id);
                    }
                }
            }
        }
    } while (any == 1);
}

typedef struct ModelSlotSerializedOut {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
} ModelSlotSerializedOut; /* 0x30 */


extern u8 *D_807F6010;
extern u8 gCsVarsDirty[];


void modelSlotSerializeAll(u8 **bufOut, s32 *sizeOut) {
    s32 count;
    s32 size;
    u8 *p;
    s32 i;
    ModelSlotSerializedOut *out;
    u8 *dst;

    count = 0;
    if (D_807F6010 != NULL) {
        heapFree(D_807F6010);
    }
    size = gModelSlotCount * sizeof(ModelSlotSerializedOut) + sizeof(s32);
    size += sizeof(s32);
    for (p = gCsVarsDirty; p < &gCsVarsDirty[0x212]; p++) {
        if (*p) {
            size += 0x24;
            count++;
        }
    }
    size += actorListGetSerializedSize();
    D_807F6010 = heapAlloc(size);
    *(s32 *)D_807F6010 = gModelSlotCount;
    out = (ModelSlotSerializedOut *)(D_807F6010 + 4);
    for (i = 0; i < gModelSlotCount; i++, out++) {
        out->unk0 = gModelSlots[i].x;
        out->unk4 = gModelSlots[i].y;
        out->unk8 = gModelSlots[i].z;
        out->unkC = gModelSlots[i].scale;
        out->unk18 = gModelSlots[i].rotY;
        out->unk1C = gModelSlots[i].unk14;
        out->unk20 = gModelSlots[i].unk18;
        out->unk28 = gModelSlots[i].modelType;
        out->unk2C = gModelSlots[i].unk86;
        out->unk24 = gModelSlots[i].unk1C;
        out->unk2A = gModelSlots[i].unk8A;
        switch (out->unk2C) {
        case 2:
            out->unk2F = ((ModelType2ObjView *)gModelSlots[i].unk20)->unk4E;
            out->unk2E = ((ModelType2ObjView *)gModelSlots[i].unk20)->unk5B;
            break;
        case 1:
            out->unk2F = 0;
            out->unk2E = ((ModelType1Obj *)gModelSlots[i].unk20)->unkC3;
            break;
        }
    }
    *(s32 *)out = count;
    dst = (u8 *)out + 4;
    for (i = 0, p = gCsVarsDirty; i != 0x212; i++, p++) {
        if (*p != 0) {
            *(s32 *)dst = i;
            memcpy(dst + 4, gModelSlots[hashTableLookup(gCsModelIds[i])].unk7C->unk14, 0x20);
            dst += 0x24;
        }
    }
    actorListSerialize((s32 *)dst);
    *bufOut = D_807F6010;
    if (!gCsVarsDirty) {} // FAKE: dead test keeps the table address live (steers colouring)
    *sizeOut = size;
}


typedef struct ModelSlotPackView {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ u8 *unk24;
    /* 0x28 */ u8 pad28[0x50];
    /* 0x78 */ u8 **unk78;
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[8];
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} ModelSlotPackView; /* 0x90 */


#define MODEL_SLOT_PACKED_ENTRY(i) ((ModelSlotPackView *)((u8 *)gModelSlots + (i) * 0x90))

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
        if (MODEL_SLOT_PACKED_ENTRY(i)->unk7C != NULL) {
            if ((MODEL_SLOT_PACKED_ENTRY(i)->unk24[0x3A] != 0 || (MODEL_SLOT_PACKED_ENTRY(i)->unk7C[0x9B] & 1)) && !(MODEL_SLOT_PACKED_ENTRY(i)->unk7C[0x9B] & 2)) {
                count++;
                if (MODEL_SLOT_PACKED_ENTRY(i)->unk78 != NULL) {
                    size += modelSlotDataSize(i);
                }
            }
        }
    }
    if (count != 0) {
        buf = heapAlloc(count * 0x254 + size);
        cur = buf;
        for (i = 0; i < gModelSlotCount; i++) {
            if (MODEL_SLOT_PACKED_ENTRY(i)->unk7C != NULL) {
                if ((MODEL_SLOT_PACKED_ENTRY(i)->unk24[0x3A] != 0 || (MODEL_SLOT_PACKED_ENTRY(i)->unk7C[0x9B] & 1)) && !(MODEL_SLOT_PACKED_ENTRY(i)->unk7C[0x9B] & 2)) {
                    rec = cur;
                    *(s16 *)rec = MODEL_SLOT_PACKED_ENTRY(i)->unk8A;
                    memcpy(rec + 0xCC, MODEL_SLOT_PACKED_ENTRY(i)->unk7C, 0x9C);
                    if (MODEL_SLOT_PACKED_ENTRY(i)->unk78 != NULL) {
                        memcpy(rec + 4, (u8 *)MODEL_SLOT_PACKED_ENTRY(i)->unk78 + 8, 0xC8);
                        rec[0x250] = modelSlotDataSize(i) >> 6;
                        memcpy(rec + 0x254, *MODEL_SLOT_PACKED_ENTRY(i)->unk78, modelSlotDataSize(i));
                    } else {
                        rec[0x250] = 0;
                    }
                    for (j = 1; j != 5; j++) {
                        modelSlotGetNodeScrollSpeed(MODEL_SLOT_PACKED_ENTRY(i)->unk88, j, (s16 *)(rec + 0x232 + j * 6), (s16 *)(rec + 0x234 + j * 6));
                        modelSlotGetNodeAnimMode(MODEL_SLOT_PACKED_ENTRY(i)->unk88, j, rec + 0x236 + j * 6);
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

typedef struct ModelSlotStateSnapshot {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 pad14[0x80];
    /* 0x94 */ u32 unk94;
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
        memcpy(&snap, MODEL_SLOT_PACKED_ENTRY(idx)->unk7C, 0x9C);
        memcpy(MODEL_SLOT_PACKED_ENTRY(idx)->unk7C, records + 0xCC, 0x9C);
        *(u32 *)MODEL_SLOT_PACKED_ENTRY(idx)->unk7C = snap.unk0;
        *(s16 *)(MODEL_SLOT_PACKED_ENTRY(idx)->unk7C + 0x10) = snap.unk10;
        *(s16 *)(MODEL_SLOT_PACKED_ENTRY(idx)->unk7C + 0x12) = snap.unk12;
        *(u32 *)(MODEL_SLOT_PACKED_ENTRY(idx)->unk7C + 0x94) = snap.unk94;
        MODEL_SLOT_PACKED_ENTRY(idx)->unk7C[0x48] = MODEL_SLOT_PACKED_ENTRY(idx)->unk7C[0x4B];
        MODEL_SLOT_PACKED_ENTRY(idx)->unk7C[0x49] = MODEL_SLOT_PACKED_ENTRY(idx)->unk7C[0x4C];
        MODEL_SLOT_PACKED_ENTRY(idx)->unk7C[0x4A] = MODEL_SLOT_PACKED_ENTRY(idx)->unk7C[0x4D];
        MODEL_SLOT_PACKED_ENTRY(idx)->unk7C[0x9A] = 0;
        *(s32 *)(MODEL_SLOT_PACKED_ENTRY(idx)->unk7C + 0x38) = -1;
        if (MODEL_SLOT_PACKED_ENTRY(idx)->unk78 != NULL) {
            for (off = 0; off != 0xC8; off += 0x14) {
                memcpy(tmp, (u8 *)MODEL_SLOT_PACKED_ENTRY(idx)->unk78 + off + 8, 0x14);
                memcpy((u8 *)MODEL_SLOT_PACKED_ENTRY(idx)->unk78 + off + 8, records + 4 + off, 0x14);
                *(u32 *)((u8 *)MODEL_SLOT_PACKED_ENTRY(idx)->unk78 + off + 8) = *(u32 *)tmp;
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
    ModelSubObjectFlags *obj = gModelSlots[hashTableLookup(gCsModelIds[csId])].unk20;

    obj->unk4E |= flags;
}

void modelSlotClearFlags(s32 csId, u8 flags) {
    ModelSubObjectFlags *obj = gModelSlots[hashTableLookup(gCsModelIds[csId])].unk20;

    obj->unk4E &= ~flags;
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

