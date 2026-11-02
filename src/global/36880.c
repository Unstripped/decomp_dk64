#include "common.h"
#include "actor.h"

typedef struct ModelSlot {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x14];
    /* 0x20 */ void *unk20;
    /* 0x24 */ u8 *unk24;
    /* 0x28 */ u8 pad28[0x4C];
    /* 0x74 */ void *unk74;
    /* 0x78 */ u8 *unk78;
    /* 0x7C */ void *unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ u8 pad88[4];
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[3];
} ModelSlot; /* 0x90, indexed by hashTableLookup() */

extern ModelSlot *D_807F6000;

extern void *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s32 gFrameCounter;
extern s32 gCurrentMap;
extern u8 D_807444FC;

s32 hashTableLookup(s32);
void heapFree(void *);
void *heapAlloc(s32);
void assetFreeBuffer(void *, s32, s32);

extern u8 D_807F6148;

void modelSkipListClear(void) {
    D_807F6148 = 0;
}

extern s16 D_807F6140[];

void modelSkipListAdd(s16 arg0) {
    if (D_807F6148 != 4) {
        D_807F6140[D_807F6148++] = arg0;
    }
}

s32 modelSkipListContains(s16 arg0) {
    s32 i;

    for (i = 0; i < D_807F6148; i++) {
        if (D_807F6140[i] == arg0) {
            return 1;
        }
    }
    return 0;
}

extern s16 D_807F6150[];

s16 modelTypeCountGet(u8 arg0) {
    return D_807F6150[arg0];
}

u8 func_805FF030(u8, u8);
void *assetLoad(s32, s32, s32, s32);
void modelAssetGetSubtables(u8 *, u8 **, u8 **);
s32 modelTypeIsCounted(u16);
void assetSetImmediateFree(void);

extern u8 D_80747D78;

void modelTypeCountsInit(void) {
    s32 x;
    s32 i;
    void *asset;
    u8 *entries;
    u8 *sp54;
    u8 slot;
    s32 count;
    u8 *entry;
    s32 j;

    if (D_80747D78 == 0) {
        D_80747D78 = 1;
        for (i = 0; i < 8; i++) {
            D_807F6150[i] = 0;
        }
        for (i = 0; i != 0xDD; i++) {
            asset = assetLoad(9, i, 1, 1);
            if (asset != NULL) {
                slot = func_805FF030(i, 1);
                modelAssetGetSubtables(asset, &entries, &sp54);
                count = *(s32 *)entries;
                entry = entries + 4;
                for (j = 0; j < count; j++) {
                    if (modelTypeIsCounted(*(u16 *)(entry + 0x28))) {
                        D_807F6150[slot]++;
                    }
                    entry += 0x30;
                }
                assetSetImmediateFree();
                assetFreeBuffer(asset, 0x10C, 7);
            }
        }
    }
}

u16 modelTypeCountBeforeMap(u8 arg0) {
    u16 total;
    u8 slot;
    s32 i;
    void *asset;
    s32 x1;
    u8 *entries;
    u8 *sp58;
    s32 j;
    s32 count;
    u8 *entry;

    slot = func_805FF030(arg0, 1);
    total = 0;
    for (i = 0; i < arg0; i++) {
        if (slot == func_805FF030(i, 1)) {
            asset = assetLoad(9, i, 1, 1);
            if (asset != NULL) {
                modelAssetGetSubtables(asset, &entries, &sp58);
                count = *(s32 *)entries;
                entry = entries + 4;
                for (j = 0; j < count; j++) {
                    if (modelTypeIsCounted(*(u16 *)(entry + 0x28))) {
                        total++;
                    }
                    entry += 0x30;
                }
                assetSetImmediateFree();
                assetFreeBuffer(asset, 0x13A, 7);
            }
        }
    }
    return total;
}

s32 modelTypeIsCounted(u16 arg0) {
    switch (arg0) {
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

void modelAssetGetSubtables(u8 *arg0, u8 **arg1, u8 **arg2) {
    s32 n;
    u8 *r;

    if (arg0 == NULL) {
        *arg1 = NULL;
        *arg2 = NULL;
        return;
    }
    *arg1 = arg0;
    n = *(s32 *)arg0;
    arg0 += n * 0x30;
    arg0 += 4;
    r = arg0;
    r += *(s32 *)arg0 * 0x24;
    r += 4;
    *arg2 = r;
}

extern s16 D_807F614A;
void heapClearBlock(void *);

s16 modelSlotsAllocate(s32 arg0, u8 arg1) {
    switch (arg0) {
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
    if (arg1 != 0) {
        D_807F6000 = heapAlloc(D_807F614A * 0x90);
        heapClearBlock(D_807F6000);
    }
    return D_807F614A;
}

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

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[0x64];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 pad86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[3];
} ModelSlotInitView; /* 0x90 */

extern s32 D_80747D70;
extern s16 gCsModelIds[];
extern s32 D_807F6004;
void hashTableInit(void);
void csModelIdTableReset(void);
void mtxCopyQueueReset(void);
u8 eepromReadChecksumBit(u16, u8);
s32 modelSkipListContains(s16);
s32 func_807315D4(s16, s16);
s32 func_8063253C(s16, s32);
s16 modelSlotInit(s32, s32, f32, f32, f32, f32, f32, f32, f32, f32, u8, u8, s32 *);
void modelFlagsApplyState(s16, s16, u8 *);
void mapDistributeEntries(s32);
void renderEntryListFree(s32);
void func_8062D1A8(void);
void csScriptLoad(void *);
void csModelStateSetVars(s32, u8 *);
void modelSkipListClear(void);

void modelSlotsLoadMap(u8 *arg0, s32 arg1, u8 arg2, u16 arg3, u8 arg4) {
    s32 sp94;
    s32 sp90;
    u8 *sp8C;
    ModelAssetEntry *entry;
    s32 i;
    s32 n;
    u8 *rec;
    s32 outCount;
    u16 counter;
    s16 result;
    u8 found;
    u8 used;

    sp94 = 0;
    outCount = 0;
    i = 0;
    counter = 0;
    D_80747D70 = 0;
    if (arg0 == NULL) {
        sp90 = 0;
        entry = (ModelAssetEntry *)sp8C;
    } else {
        entry = (ModelAssetEntry *)(arg0 + 4);
        sp90 = *(s32 *)arg0;
    }
    D_807F6004 = 0;
    hashTableInit();
    csModelIdTableReset();
    mtxCopyQueueReset();
    if (arg0 != NULL) {
        if (sp90 > 0) {
            do {
                found = 0;
                used = 0;
                if (arg2 && modelTypeIsCounted(entry->unk28)) {
                    found = eepromReadChecksumBit(arg3 + counter, arg4);
                    used = 1;
                }
                if (found == 0 && modelSkipListContains(entry->unk28) == 0 &&
                    func_807315D4(*(s16 *)((u8 *)&gCurrentMap + 2), entry->unk2A) == 0 &&
                    func_8063253C(entry->unk28, arg1) != 0) {
                    ((ModelSlotInitView *)D_807F6000)[outCount].unk0 = entry->unk0;
                    ((ModelSlotInitView *)D_807F6000)[outCount].unk4 = entry->unk4;
                    ((ModelSlotInitView *)D_807F6000)[outCount].unk8 = entry->unk8;
                    ((ModelSlotInitView *)D_807F6000)[outCount].unkC = entry->unkC;
                    ((ModelSlotInitView *)D_807F6000)[outCount].unk10 = entry->unk18;
                    ((ModelSlotInitView *)D_807F6000)[outCount].unk14 = entry->unk1C;
                    ((ModelSlotInitView *)D_807F6000)[outCount].unk18 = entry->unk20;
                    ((ModelSlotInitView *)D_807F6000)[outCount].unk1C = entry->unk24;
                    ((ModelSlotInitView *)D_807F6000)[outCount].unk8A = entry->unk2A;
                    result = modelSlotInit(outCount, entry->unk28, entry->unk0, entry->unk4, entry->unk8,
                                           entry->unk18, entry->unk1C, entry->unk20, entry->unkC, entry->unk24,
                                           entry->unk2F, entry->unk2E, &sp94);
                    modelFlagsApplyState(*(s16 *)((u8 *)&gCurrentMap + 2), ((ModelSlotInitView *)D_807F6000)[outCount].unk8A,
                                  (u8 *)(outCount * 0x90 + (s32)D_807F6000 + 0x8C));
                    gCsModelIds[entry->unk2A] = result;
                    D_80747D70++;
                    outCount++;
                }
                if (used != 0) {
                    counter++;
                }
                i++;
                entry++;
            } while (i < sp90);
        }
        mapDistributeEntries(sp94);
        renderEntryListFree(sp94);
        func_8062D1A8();
        csScriptLoad(assetLoad(0xA, gCurrentMap, 1, 0));
        n = *(s32 *)entry;
        rec = (u8 *)entry + 4;
        while (n--) {
            csModelStateSetVars(*(s32 *)rec, rec + 4);
            rec += 0x24;
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

typedef struct ModelFlagNode {
    /* 0x00 */ ModelFlagTarget *unk0;
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ struct ModelFlagNode *unk14;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ u8 unk24;
} ModelFlagNode;

s32 flagGet(s32, s32);

void modelNodeListSyncFlags(ModelFlagNode *arg0) {
    ModelFlagTarget *obj;
    s16 flag;

    if (arg0 != NULL) {
        do {
            if (arg0->unk24 == 2) {
                obj = arg0->unk0;
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
            arg0 = arg0->unk14;
        } while (arg0 != NULL);
    }
}

s32 func_8063253C(s16 arg0, s32 arg1) {
    return 1;
}

s32 modelSlotFindByType(s32 arg0, s32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, s16 *arg5, s16 *arg6) {
    s32 i;
    u8 found;

    found = 0;
    i = *arg1;
    do {
    } while (0);
    if (i < D_80747D70) {
        do {
            if (((ModelSlotInitView *)D_807F6000)[i].unk84 == arg0) {
                found = 1;
                *arg5 = ((ModelSlotInitView *)D_807F6000)[i].unk88;
                *arg6 = ((ModelSlotInitView *)D_807F6000)[i].unk8A;
                *arg2 = ((ModelSlotInitView *)D_807F6000)[i].unk0;
                *arg3 = ((ModelSlotInitView *)D_807F6000)[i].unk4;
                *arg4 = ((ModelSlotInitView *)D_807F6000)[i].unk8;
            }
            i++;
        } while (found == 0 && i < D_80747D70);
    }
    *arg1 = i;
    return found;
}

extern u8 D_807F6008;
void faultSetMessage(s32, s32, s32, s32);
f32 func_80636A44(s32);
s16 csModelIdTableAlloc(s16, u8);

s16 modelSlotAppend(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5) {
    s32 sp5C;
    s16 sp5A;
    f32 temp;

    sp5C = 0;
    if (D_80747D70 >= D_807F614A) {
        faultSetMessage(8, 0, 0, 0);
    }
    if (arg5 == 0 && D_807F6008 != 0) {
        return -1;
    }
    temp = func_80636A44(arg0);
    ((ModelSlotInitView *)D_807F6000)[D_80747D70].unk0 = arg1;
    ((ModelSlotInitView *)D_807F6000)[D_80747D70].unk4 = arg2;
    ((ModelSlotInitView *)D_807F6000)[D_80747D70].unk8 = arg3;
    ((ModelSlotInitView *)D_807F6000)[D_80747D70].unkC = temp;
    ((ModelSlotInitView *)D_807F6000)[D_80747D70].unk10 = 0.0f;
    ((ModelSlotInitView *)D_807F6000)[D_80747D70].unk14 = 0.0f;
    ((ModelSlotInitView *)D_807F6000)[D_80747D70].unk18 = 0.0f;
    ((ModelSlotInitView *)D_807F6000)[D_80747D70].unk1C = arg2 - arg4;
    ((ModelSlotInitView *)D_807F6000)[D_80747D70].unk8C = 0;
    sp5A = modelSlotInit(D_80747D70, arg0, arg1, arg2, arg3, 0.0f, 0.0f, 0.0f, temp, arg2 - arg4, 1, 0, &sp5C);
    mapDistributeEntries(sp5C);
    renderEntryListFree(sp5C);
    ((ModelSlotInitView *)D_807F6000)[D_80747D70].unk8A = csModelIdTableAlloc(sp5A, arg5);
    D_80747D70++;
    return sp5A;
}

typedef struct ModelAssetInfo {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[0x18];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[8];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
} ModelAssetInfo;

typedef struct ModelSlotDetail {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ void *unk20;
    /* 0x24 */ ModelAssetInfo *unk24;
    /* 0x28 */ u8 unk28[0x14];
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ u8 unk3D;
    /* 0x3E */ u8 pad3E[0xA];
    /* 0x48 */ u8 unk48[0x24];
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 pad6D[0xB];
    /* 0x78 */ u8 unk78[4];
    /* 0x7C */ void *unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ u8 pad8A[6];
} ModelSlotDetail;

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
    /* 0x00 */ s32 unk0;
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

extern s32 D_807FBB64;
extern s32 D_807FBB68;

void modelSlotInitFromAsset();
void modelSlotReplaceSegment6Commands(void *);
s32 modelSlotResolveAssetTextures();
struct ModelQuadOwner;
void modelQuadBuildOutput(struct ModelQuadOwner *, f32, f32, f32, f32, f32, f32, f32, f32);
void modelSlotLinkTexAnimTextures(u8 *, ModelSlot *);
void modelSlotInitTexAnimNodes(u8 *, ModelSlot *, s32);
void modelSlotAllocAnimBuffers(void *, void *);
void collisionBuildSlotBoxes(s32, void *, f32, f32, f32, f32, f32, f32, f32);
struct ModelAssetData;
void modelSlotBuildTriangleBuffer(s32, struct ModelAssetData *, f32, f32, f32, f32, f32, f32, f32);
struct ModelTriBuffer;
void modelSlotTriBufferRelease(struct ModelTriBuffer *);
void dynamicBufferFree(void *);
void hashTableInsert(s32, s32);
s32 renderEntryAddOrUpdate(s32, u8, void *, f32, f32, f32, s32, s32, s32, s32, s32);
void modelFlagsApplyMapPairs(s16, u8 *);
void modelApplyMapOverrideValue(s32, u8 *);
s32 groundSurfaceTypeAt(f32, f32, f32);
void modelSlotUpdateGroundCoords(s16, u8);
struct ModelPathTable;
void modelSlotBuildProxPaths(s16, struct ModelPathTable *, f32);
struct ModelVertTable;
void modelSlotBuildVertPosList(s32, struct ModelVertTable *, f32, f32, f32, f32, f32, f32, f32, u8);
void modelSlotBuildNodePosList(s32, struct ModelVertTable *, f32, f32, f32, f32, f32, f32, f32, u8);
void modelSlotClearTail(s32);

#define MODEL_SLOT_BY_INDEX ((ModelSlotDetail *)((u8 *)D_807F6000 + arg0 * 0x90))
#define MODEL_SLOT_PTR ((ModelSlotDetail *)&D_807F6000[arg0])

s16 modelSlotInit(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u8 arg10, u8 arg11, s32 *arg12) {
    s32 padA[1];
    s32 sp68;
    s32 padB[1];
    ModelType1Obj *obj1;
    ModelType2ObjView *obj2;
    ModelAssetInfo *s0;
    s32 type;
    ModelSlotSubNode *node;
    void **sp4C;

    sp68 = *arg12;
    modelSlotInitFromAsset(MODEL_SLOT_PTR);
    MODEL_SLOT_BY_INDEX->unk88 = D_807F6004;
    hashTableInsert(MODEL_SLOT_BY_INDEX->unk88, arg0);
    s0 = MODEL_SLOT_BY_INDEX->unk24;
    type = s0->unk1C;
    if (D_807FBB68 & 0x100) {
        s0->unk0 &= ~0x10;
    }
    modelApplyMapOverrideValue(arg1, (u8 *)s0);
    if (D_807FBB64 & 0x100) {
        s0->unk1E = 0x7D0;
    } else if (D_807FBB64 & 0x400000) {
        s0->unk1E = 0x1F4;
    }
    modelSlotAllocAnimBuffers(MODEL_SLOT_PTR->unk78, s0);
    MODEL_SLOT_BY_INDEX->unk3C = 0;
    MODEL_SLOT_BY_INDEX->unk3D = 0;
    collisionBuildSlotBoxes(arg0, s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    dynamicBufferFree(MODEL_SLOT_PTR->unk28);
    modelSlotClearTail(arg0);
    MODEL_SLOT_BY_INDEX->unk6C = 0;
    modelSlotBuildTriangleBuffer(arg0, s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    modelSlotTriBufferRelease(MODEL_SLOT_PTR->unk48);
    modelSlotBuildVertPosList(arg0, (struct ModelVertTable *)s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, 0);
    modelSlotBuildNodePosList(arg0, (struct ModelVertTable *)s0, arg2, arg3, arg4, arg5, arg6, arg7, arg8, 0);
    modelSlotBuildProxPaths(MODEL_SLOT_BY_INDEX->unk88, (struct ModelPathTable *)s0, arg8);
    if (type == 1) {
        modelSlotReplaceSegment6Commands(MODEL_SLOT_PTR);
    }
    if (type != 1) {
        if (type == 2) {
            modelQuadBuildOutput(MODEL_SLOT_PTR, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
            modelSlotInitTexAnimNodes(s0, MODEL_SLOT_PTR, type);
            obj2 = MODEL_SLOT_BY_INDEX->unk20;
            sp4C = &obj2->unk54;
            obj2->unk4C = D_807F6004;
            obj2->unk4E = arg10;
            obj2->unk5B = arg11;
            obj2->unk58 = s0->unk1E;
            obj2->unk5A = s0->unk1D;
            obj2->unk5C = groundSurfaceTypeAt(arg2, arg3, arg4);
        }
    } else {
        obj1 = MODEL_SLOT_BY_INDEX->unk20;
        obj1->unk0 = arg2;
        obj1->unk4 = arg3;
        obj1->unk8 = arg4;
        obj1->unkC = arg8;
        obj1->unk10 = arg5;
        obj1->unk14 = arg6;
        obj1->unk18 = arg7;
        obj1->unk1C = arg9;
        obj1->unkB6 = D_807F6004;
        obj1->unkC0 = s0->unk1E;
        obj1->unkC2 = s0->unk1D;
        obj1->unkC3 = arg11;
        obj1->unkC4 = groundSurfaceTypeAt(arg2, arg3, arg4);
        obj1->unkC5 = 0;
        modelFlagsApplyMapPairs(arg1, &obj1->unkC5);
        modelSlotInitTexAnimNodes(s0, MODEL_SLOT_PTR, type);
        sp4C = &obj1->unkBC;
    }
    modelSlotResolveAssetTextures(MODEL_SLOT_PTR, 0, 0);
    if (type == 2) {
        modelSlotLinkTexAnimTextures(s0, MODEL_SLOT_PTR);
    }
    MODEL_SLOT_BY_INDEX->unk84 = arg1;
    MODEL_SLOT_BY_INDEX->unk86 = type;
    MODEL_SLOT_BY_INDEX->unk7C = NULL;
    if (s0->unk28 != -1) {
        node = heapAlloc(0x38);
        *sp4C = node;
        node->unk34 = 0;
        node->unk4 = 1.0f;
        node->unkC = s0->unk2E;
        node->unkE = s0->unk30;
        node->unkA = s0->unk34;
        node->unkB = s0->unk35;
        node->unk8 = s0->unk32;
        node->unk9 = s0->unk33;
        node->unk24 = s0->unk2A;
        node->unk28 = s0->unk2C;
        node->unk2A = s0->unk36 * 10;
        node->unk2C = s0->unk37 * 10;
        node->unk2E = s0->unk38;
        node->unk30 = s0->unk39;
        node->unk0 = (s32)assetLoad(0x19, s0->unk28, 1, 0);
        modelSlotUpdateGroundCoords(arg0, 0);
    }
    *arg12 = renderEntryAddOrUpdate(sp68, type, MODEL_SLOT_BY_INDEX->unk20, arg2, arg3, arg4, s0->unk1E, D_807F6004, 0, 0, 0);
    D_807F6004 += 1;
    return D_807F6004 - 1;
}


typedef struct ModelMapIdPair {
    /* 0x0 */ u16 map;
    /* 0x2 */ u16 id;
} ModelMapIdPair;

extern ModelMapIdPair D_80747D50[];

void modelFlagsApplyMapPairs(s16 arg0, u8 *arg1) {
    s32 i;
    s32 n;
    i = 0;
    n = 8;
    for (; i < n; i++) {
        if (gCurrentMap == D_80747D50[i].map && arg0 == D_80747D50[i].id) {
            *arg1 |= 1;
            return;
        }
    }
}

s32 func_80731654(s16, s16);

void modelFlagsApplyState(s16 arg0, s16 arg1, u8 *arg2) {
    switch (func_80731654(arg0, arg1)) {
        case 2:
            *arg2 |= 8;
            break;
        case 5:
            *arg2 |= 4;
            break;
        case 6:
            *arg2 |= 1;
            break;
        case 3:
            *arg2 |= 2;
            break;
        case 4:
            *arg2 |= 0x10;
            break;
    }
}

typedef struct ModelMapIdValueTriple {
    /* 0x0 */ u16 map;
    /* 0x2 */ u16 id;
    /* 0x4 */ u16 val;
} ModelMapIdValueTriple;

extern ModelMapIdValueTriple D_80747D30[];

void modelApplyMapOverrideValue(s32 arg0, u8 *arg1) {
    s32 i;
    s32 n;

    n = 5;
    for (i = 0; i < n; i++) {
        if (gCurrentMap == D_80747D30[i].map && arg0 == D_80747D30[i].id) {
            *(u16 *)(arg1 + 0x1E) = D_80747D30[i].val;
            return;
        }
    }
}

s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
u8 collisionGetSurfaceType(void);

s32 groundSurfaceTypeAt(f32 x, f32 y, f32 z) {
    f32 sp1C;

    sp1C = y + 10.0f;
    if (collisionCheckGroundAtPoint(x, z, &sp1C) != 0) {
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

void collisionGetCoords(s16 *, s16 *);

void modelSlotUpdateGroundCoords(s16 arg0, u8 arg1) {
    s32 padA[4];
    u8 *tbl;
    ModelGroundCoordDst *dst;
    s32 idx;
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    idx = arg0 * sizeof(ModelSlot);
    sp28 = ((ModelSlot *)((u8 *)D_807F6000 + idx))->unk4 + 20.0f;
    if (collisionCheckGroundAtPoint(((ModelSlot *)((u8 *)D_807F6000 + idx))->unk0, ((ModelSlot *)((u8 *)D_807F6000 + idx))->unk8, &sp28) != 0) {
        collisionGetCoords(&sp26, &sp24);
        switch ((tbl = ((ModelSlot *)((u8 *)D_807F6000 + idx))->unk24)[0x1C]) {
            case 1:
                dst = ((ModelSlotObjCoordHolder *)((ModelSlot *)((u8 *)D_807F6000 + idx))->unk20)->unkBC;
                break;
            case 2:
                dst = ((ModelSlotObjCoordHolder *)((ModelSlot *)((u8 *)D_807F6000 + idx))->unk20)->unk54;
                break;
        }
        if (((ModelSlot *)((u8 *)D_807F6000 + idx))->unk20) {
        }
        if (dst != NULL) {
            dst->unk20 = sp26;
            dst->unk22 = sp24;
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

typedef struct ModelPathTable {
    /* 0x00 */ u8 pad0[0x5C];
    /* 0x5C */ s32 unk5C;
} ModelPathTable;

void modelSlotGetNodePos(s32, u8, s32, f32 *, f32 *, f32 *);
void proxPathAdd(Actor *, u8, u8, u8, u8, f32, f32, f32, f32, f32, f32, u8, f32, f32, u8);
void proxPathSetSegment(Actor *, u8, u8, u8, u8, f32, f32, f32, u8, s16, s16, s16, s16);

void modelSlotBuildProxPaths(s16 arg0, ModelPathTable *arg1, f32 arg2) {
    s32 j;
    ModelPathEntry *tbl;
    s32 i;
    s32 count;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 len;

    count = *(s32 *)(arg1->unk5C + (s32)arg1);
    tbl = (ModelPathEntry *)((u8 *)(arg1->unk5C + (s32)arg1) + 4);
    for (i = 1; i <= count; i++) {
        len = 0.0f;
        for (j = 0; j < tbl[i - 1].segCount; j++) {
            modelSlotGetNodePos(arg0, 1, tbl[i - 1].segs[j].unk10, &spC0, &spB8, &spB0);
            modelSlotGetNodePos(arg0, 1, tbl[i - 1].segs[j].unk11, &spC4, &spBC, &spB4);
            len += sqrtf((spB0 - spB4) * (spB0 - spB4) + ((spC0 - spC4) * (spC0 - spC4) + (spB8 - spBC) * (spB8 - spBC)));
        }
        proxPathAdd((Actor *)arg0, 1, i, 1, tbl[i - 1].segCount, 0.0f, len, tbl[i - 1].unk0 * arg2, tbl[i - 1].unkC * arg2, tbl[i - 1].unk10 * arg2, tbl[i - 1].unk10 * arg2, tbl[i - 1].unk14, tbl[i - 1].unk4, tbl[i - 1].unk8, tbl[i - 1].unk15);
        for (j = 0; j < tbl[i - 1].segCount; j++) {
            modelSlotGetNodePos(arg0, 1, tbl[i - 1].segs[j].unk10, &spC0, &spB8, &spB0);
            modelSlotGetNodePos(arg0, 1, tbl[i - 1].segs[j].unk11, &spC4, &spBC, &spB4);
            proxPathSetSegment((Actor *)arg0, i, j, tbl[i - 1].segs[j].unk10, tbl[i - 1].segs[j].unk11, sqrtf((spB0 - spB4) * (spB0 - spB4) + ((spC0 - spC4) * (spC0 - spC4) + (spB8 - spBC) * (spB8 - spBC))), tbl[i - 1].segs[j].unk0 * arg2, tbl[i - 1].segs[j].unk4 * arg2, tbl[i - 1].segs[j].unk12, tbl[i - 1].segs[j].unk8, tbl[i - 1].segs[j].unkC, tbl[i - 1].segs[j].unkA, tbl[i - 1].segs[j].unkE);
        }
    }
}


void modelSlotBuildTransformMatrix(s16, s8, f32 (*)[4]);

typedef struct ModelPosNode {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ struct ModelPosNode *next;
} ModelPosNode;

typedef struct ModelVertTable {
    /* 0x00 */ u8 pad0[0x54];
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
} ModelVertTable;

typedef struct ModelVert {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ s8 unk6;
} ModelVert;

void modelSlotBuildVertPosList(s32 arg0, ModelVertTable *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9) {
    ModelPosNode *node;
    ModelPosNode **tail;
    f32 *pz;
    f32 sp6C[4][4];
    f32 *py;
    ModelVert *vert;
    s32 *tbl;
    s32 count;

    node = NULL;
    tail = (ModelPosNode **)((u8 *)&D_807F6000[arg0] + 0x70);
    if (arg9 == 0) {
        *tail = NULL;
    }
    tbl = (s32 *)(arg1->unk54 + (s32)arg1);
    count = *tbl;
    vert = (ModelVert *)((u8 *)tbl + 4);
    if (count != 0) {
        do {
            switch (arg9) {
                case 0:
                    node = heapAlloc(0x10);
                    *tail = node;
                    tail = &node->next;
                    node->next = NULL;
                    py = &node->y;
                    pz = &node->z;
                    break;
                case 1:
                    if (node == NULL) {
                        node = *tail;
                    } else {
                        node = node->next;
                    }
                    py = &node->y;
                    pz = &node->z;
                    break;
                default:
                    py = &node->y;
                    pz = &node->z;
                    break;
            }
            modelSlotBuildTransformMatrix(arg0, vert->unk6, sp6C);
            guMtxXFMF(sp6C, vert->x, vert->y, vert->z, &node->x, py, pz);
            count--;
            vert++;
        } while (count != 0);
    }
}

typedef struct ModelLinkedNode {
    /* 0x0 */ u8 pad0[0xC];
    /* 0xC */ struct ModelLinkedNode *next;
} ModelLinkedNode;

void modelPosNodeListFree(ModelLinkedNode *arg0) {
    ModelLinkedNode *next;

    while (arg0 != NULL) {
        next = arg0->next;
        heapFree(arg0);
        arg0 = next;
    }
}

void modelSlotGetNodePos(s32 arg0, u8 arg1, s32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    ModelPosNode *node;
    s32 n;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    node = D_807F6000[arg0].unk74;
    for (n = arg2 - 1; node != NULL && n != 0; n--) {
        node = node->next;
    }
    if (node != NULL) {
        *arg3 = node->x;
        *arg4 = node->y;
        *arg5 = node->z;
    } else {
        *arg5 = 0.0f;
        *arg4 = 0.0f;
        *arg3 = 0.0f;
    }
}

Mtx *modelSlotGetNodeMatrix(s32 arg0, u8 arg1, s32 arg2) {
    s32 idx;
    f32 sp24[4][4];
    Mtx *sp20;
    u8 *base;
    s8 *p;

    idx = arg0;
    if (arg1 == 1) {
        idx = hashTableLookup(arg0);
    }
    base = D_807F6000[idx].unk24;
    p = (s8 *)(base + *(s32 *)(base + 0x58)) + 4;
    for (arg2--; p != NULL && arg2 != 0; arg2--) {
        p += 8;
    }
    modelSlotBuildTransformMatrix(idx, p[6], sp24);
    sp20 = heapAlloc(0x40);
    guMtxF2L(sp24, sp20);
    return sp20;
}

void modelSlotBuildNodePosList(s32 arg0, ModelVertTable *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9) {
    ModelPosNode *node;
    ModelPosNode **tail;
    f32 *pz;
    f32 spAC[4][4];
    f32 sp6C[4][4];
    f32 *py;
    ModelVert *vert;
    s32 *tbl;
    s32 count;

    node = NULL;
    tail = (ModelPosNode **)((u8 *)&D_807F6000[arg0] + 0x74);
    if (arg9 == 0) {
        *tail = NULL;
    }
    tbl = (s32 *)(arg1->unk58 + (s32)arg1);
    count = *tbl;
    vert = (ModelVert *)((u8 *)tbl + 4);
    if (count != 0) {
        do {
            switch (arg9) {
                case 0:
                    node = heapAlloc(0x10);
                    *tail = node;
                    tail = &node->next;
                    node->next = NULL;
                    py = &node->y;
                    pz = &node->z;
                    break;
                case 1:
                    if (node == NULL) {
                        node = *tail;
                    } else {
                        node = node->next;
                    }
                    py = &node->y;
                    pz = &node->z;
                    break;
                default:
                    py = &node->y;
                    pz = &node->z;
                    break;
            }
            modelSlotBuildTransformMatrix(arg0, vert->unk6, spAC);
            guMtxXFMF(spAC, vert->x, vert->y, vert->z, &node->x, py, pz);
            count--;
            vert++;
        } while (count != 0);
    }
}

void modelLinkedNodeListFree(ModelLinkedNode *arg0) {
    ModelLinkedNode *next;

    while (arg0 != NULL) {
        next = arg0->next;
        heapFree(arg0);
        arg0 = next;
    }
}

typedef struct ModelSlotTailState {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25[2];
} ModelSlotTailState;

void modelSlotClearTail(s32 arg0) {
    ModelSlotTailState *p = (ModelSlotTailState *)((u8 *)&D_807F6000[arg0] + 0x48);
    u8 i;

    for (i = 0; i < 2; i++) {
        p->unk25[i] = 0xFF;
    }
    p->unk24 = 0;
}

void modelSlotUpdateTailKey(s32 arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 i = 0;
    u8 found = 0;
    u8 key;
    u8 *p;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    p = (u8 *)D_807F6000 + arg0 * 0x90 + 0x6D;
    key = arg3 ? arg2 : 0xFF;
    while (i < 2 && found == 0) {
        if (key == p[i]) {
            found = 1;
        } else {
            i++;
        }
    }
    p[i] = arg3 ? 0xFF : arg2;
}

typedef struct ModelTriBuffer {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ u8 *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC[6];
    /* 0x24 */ u8 unk24;
} ModelTriBuffer;

typedef struct ModelAssetData {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[0x4C];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 pad54[0xC];
    /* 0x60 */ s32 unk60;
} ModelAssetData;

void bboxExpandFromTriangle(f32 *, f32 *);
void boundsTransformToAabb(f32 (*)[4], void *, void *);
s32 modelTriangleTransform(void *, void *, f32 (*)[4]);
void modelBuildBoneChainMatrix(void *, void *, f32 (*)[4]);

void modelSlotBuildTriangleBuffer(s32 arg0, ModelAssetData *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    s32 count;
    u8 *anim;
    f32 sp138[4][4];
    f32 spF8[4][4];
    f32 spB8[4][4];
    f32 sp78[4][4];
    ModelTriBuffer *buf;
    u8 *entry;
    u8 *out;
    s32 i;
    void *sp64;
    u8 *sp60;
    s8 bone;
    s8 lastBone;
    s32 off;
    s32 pad2;
    s32 pad3;

    off = arg0 * 0x90;
    anim = ((ModelSlot *)((u8 *)D_807F6000 + off))->unk78;
    buf = (ModelTriBuffer *)((0, off) + (s32)D_807F6000);
    lastBone = -1;
    buf = (ModelTriBuffer *)((u8 *)buf + 0x48);
    if (anim != NULL) {
        sp64 = ((void **)anim)[D_807444FC];
    } else {
        sp64 = NULL;
    }
    sp60 = (u8 *)(arg1->unk60 + (s32)arg1);
    if (arg1->unk0 & 4) {
        buf->unk24 |= 2;
    } else {
        buf->unk24 &= ~2;
    }
    count = *(s32 *)(arg1->unk50 + (s32)arg1);
    if (count == 0) {
        buf->unk0 = NULL;
        buf->unk4 = NULL;
        buf->unk24 |= 1;
        buf->unk8 = gFrameCounter;
        return;
    }
    if (!(buf->unk24 & 1)) {
        buf->unk0 = heapAlloc(count * 0x28);
    }
    buf->unk24 |= 4;
    entry = (u8 *)(arg1->unk50 + (s32)arg1) + 0x10;
    out = buf->unk0;
    guScaleF(sp138, arg8, arg8, arg8);
    guRotateF(spF8, arg5, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp138, spF8, sp138);
    guRotateF(spF8, arg6, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp138, spF8, sp138);
    guRotateF(spF8, arg7, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp138, spF8, sp138);
    guTranslateF(spF8, arg2, arg3, arg4);
    guMtxCatF(sp138, spF8, sp138);
    boundsTransformToAabb(sp138, (u8 *)(arg1->unk50 + (s32)arg1) + 4, buf);
    for (i = 0; i < count; i++) {
        bone = entry[0x13];
        if ((bone ^ 0) == -1) {
            if (modelTriangleTransform(entry, out, sp138) != 0) {
                out += 0x28;
            }
        } else {
            if (lastBone != bone) {
                modelBuildBoneChainMatrix(sp60 + (bone << 5), sp64, spB8);
                guMtxCatF(spB8, sp138, sp78);
                lastBone = entry[0x13];
            }
            if (modelTriangleTransform(entry, out, sp78) != 0) {
                bboxExpandFromTriangle((f32 *)out, buf->unkC);
                out += 0x28;
            }
        }
        entry += 0x18;
    }
    buf->unk4 = out;
    buf->unk24 |= 1;
    buf->unk8 = gFrameCounter;
}


void bboxExpandFromTriangle(f32 *arg0, f32 *arg1) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (arg0[i] < arg1[0]) {
            arg1[0] = arg0[i];
        }
        if (arg0[i + 6] < arg1[2]) {
            arg1[2] = arg0[i + 6];
        }
        if (arg1[3] < arg0[i]) {
            arg1[3] = arg0[i];
        }
        if (arg1[5] < arg0[i + 6]) {
            arg1[5] = arg0[i + 6];
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

#define MODEL_BOUNDS_OUT ((BoundingBox *)arg2)
#define MODEL_BOUNDS_ACCUMULATE(x, y, z) \
    guMtxXFMF(arg0, (f32)((s16 *)arg1)[x], (f32)((s16 *)arg1)[y], (f32)((s16 *)arg1)[z], &sp3C, &sp38, &sp34); \
    if (MODEL_BOUNDS_OUT->minX < sp3C) { MODEL_BOUNDS_OUT->minX = MODEL_BOUNDS_OUT->minX; } else { MODEL_BOUNDS_OUT->minX = sp3C; } \
    if (MODEL_BOUNDS_OUT->minY < sp38) { MODEL_BOUNDS_OUT->minY = MODEL_BOUNDS_OUT->minY; } else { MODEL_BOUNDS_OUT->minY = sp38; } \
    if (MODEL_BOUNDS_OUT->minZ < sp34) { MODEL_BOUNDS_OUT->minZ = MODEL_BOUNDS_OUT->minZ; } else { MODEL_BOUNDS_OUT->minZ = sp34; } \
    if (sp3C < MODEL_BOUNDS_OUT->maxX) { MODEL_BOUNDS_OUT->maxX = MODEL_BOUNDS_OUT->maxX; } else { MODEL_BOUNDS_OUT->maxX = sp3C; } \
    if (sp38 < MODEL_BOUNDS_OUT->maxY) { MODEL_BOUNDS_OUT->maxY = MODEL_BOUNDS_OUT->maxY; } else { MODEL_BOUNDS_OUT->maxY = sp38; } \
    if (sp34 < MODEL_BOUNDS_OUT->maxZ) { MODEL_BOUNDS_OUT->maxZ = MODEL_BOUNDS_OUT->maxZ; } else { MODEL_BOUNDS_OUT->maxZ = sp34; }

void boundsTransformToAabb(f32 (*arg0)[4], void *arg1, void *arg2) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    guMtxXFMF(arg0, (f32)((s16 *)arg1)[0], (f32)((s16 *)arg1)[1], (f32)((s16 *)arg1)[2], &sp3C, &sp38, &sp34);
    MODEL_BOUNDS_OUT->minX = sp3C;
    MODEL_BOUNDS_OUT->minY = sp38;
    MODEL_BOUNDS_OUT->minZ = sp34;
    MODEL_BOUNDS_OUT->maxX = sp3C;
    MODEL_BOUNDS_OUT->maxY = sp38;
    MODEL_BOUNDS_OUT->maxZ = sp34;
    MODEL_BOUNDS_ACCUMULATE(3, 1, 2)
    MODEL_BOUNDS_ACCUMULATE(0, 1, 5)
    MODEL_BOUNDS_ACCUMULATE(3, 1, 5)
    MODEL_BOUNDS_ACCUMULATE(0, 4, 2)
    MODEL_BOUNDS_ACCUMULATE(3, 4, 2)
    MODEL_BOUNDS_ACCUMULATE(0, 4, 5)
    MODEL_BOUNDS_ACCUMULATE(3, 4, 5)
}

s32 modelTriangleTransform(void *arg0, void *arg1, f32 (*arg2)[4]) {
    s16 *in = arg0;
    f32 *out = arg1;

    guMtxXFMF(arg2, in[0], in[1], in[2], &out[0], &out[3], &out[6]);
    guMtxXFMF(arg2, in[3], in[4], in[5], &out[1], &out[4], &out[7]);
    guMtxXFMF(arg2, in[6], in[7], in[8], &out[2], &out[5], &out[8]);
    ((u8 *)arg1)[0x24] = ((u8 *)arg0)[0x12];
    ((u8 *)arg1)[0x25] = ((u8 *)arg0)[0x14];
    ((s8 *)arg1)[0x26] = ((s8 *)arg0)[0x13];
    ((u8 *)arg1)[0x27] = ((u8 *)arg0)[0x15];
    return 1;
}


void modelSlotTriBufferRelease(ModelTriBuffer *arg0) {
    if (arg0->unk0 != NULL && (arg0->unk24 & 1)) {
        heapFree(arg0->unk0);
    }
    arg0->unk24 &= ~1;
}


void modelSlotBuildTriangleBufferThunk(s32 arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    modelSlotBuildTriangleBuffer(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
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

void modelSlotLinkTexAnimTextures(u8 *arg0, ModelSlot *arg1) {
    TexAnimNode *node;
    s16 *p;
    s32 n;
    s32 idx;
    s32 found;
    s32 key;

    node = ((ModelSlotObj *)arg1->unk20)->unk50;
    if (node != NULL) {
        do {
            key = node->unk5C;
            n = *(s32 *)(arg0 + *(s32 *)(arg0 + 0x70));
            p = (s16 *)(arg0 + *(s32 *)(arg0 + 0x70) + 4);
            found = 0;
            idx = 0;
            if (n != 0) {
                do {
                    if (key == *p) {
                        found = 1;
                    } else {
                        n--;
                        p = (s16 *)((u8 *)p + 0x30);
                        idx++;
                    }
                } while (n != 0 && found == 0);
            }
            if (found != 0) {
                node->unk44 = ((ModelSlotObj *)arg1->unk20)->unk24[idx];
            } else {
                node->unk44 = NULL;
            }
            node = node->unkD4;
        } while (node != NULL);
    }
}


void *memcpy(void *, const void *, unsigned int);
s32 dlLengthToEndDL(u32 *);
void dlFindTextureCommands(u32 *, s32, s32, s32, u32 **, u32 **, u32 **);

void modelSlotInitTexAnimNodes(u8 *arg0, ModelSlot *arg1, s32 arg2) {
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

    tbl = (s32 *)(arg0 + *(s32 *)(arg0 + 0x6C));
    count = *tbl;
    entry = tbl + 1;
    switch (arg2) {
        case 1:
            tail = &((ModelSlotObj *)arg1->unk20)->unkB8;
            if (count != 0) {
                obj = arg1->unk20;
                len1 = dlLengthToEndDL(obj->unkA0);
                obj->unkA4 = heapAlloc(len1);
                memcpy(obj->unkA4, obj->unkA0, len1);
                len2 = dlLengthToEndDL(obj->unkA8);
                obj->unkAC = heapAlloc(len2);
                memcpy(obj->unkAC, obj->unkA8, len2);
            }
            break;
        case 2:
            tail = &((ModelSlotObj *)arg1->unk20)->unk50;
            break;
    }
    for (i = 0; i < count; i++) {
        node = heapAlloc(0xD8);
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
        if (D_807FBB64 & 0x2000000) {
            node->unkD0 = 0;
        }
        node->unk3C = 0;
        node->unk40 = 0;
        node->unk34 = 0;
        node->unk36 = 0;
        node->unk38 = 0;
        node->unk3A = 0;
        node->unk30 = -1;
        if (arg2 == 1) {
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


void modelSlotAccessNodeScrollSpeed(s32, s16, s16, s16, s16 *, s16 *, u8);
void modelSlotAccessNodeAnimMode(s32, s16, u8, u8 *, u8);
void modelSlotSetNodeFrame(s32, s16, s32, s32);

void modelSlotSetNodeScrollSpeed(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    modelSlotAccessNodeScrollSpeed(arg0, arg1, arg2, arg3, &arg2, &arg3, 0);
}

void modelSlotGetNodeScrollSpeed(s32 arg0, s16 arg1, s16 *arg2, s16 *arg3) {
    s16 sp2E;
    s16 sp2C;

    modelSlotAccessNodeScrollSpeed(arg0, arg1, sp2E, sp2C, arg2, arg3, 1);
}

void modelNodeAccessScrollSpeed(TexAnimNode *, s16, s16, s16, s16 *, s16 *, u8);

void modelSlotAccessNodeScrollSpeed(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 *arg4, s16 *arg5, u8 arg6) {
    ModelSlot *slot;
    ModelSlotObj *obj;

    slot = hashTableLookup(arg0) + ((0, D_807F6000));
    obj = slot->unk20;
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            modelNodeAccessScrollSpeed(obj->unk50, arg1, arg2, arg3, arg4, arg5, arg6);
        }
    } else {
        modelNodeAccessScrollSpeed(obj->unkB8, arg1, arg2, arg3, arg4, arg5, arg6);
    }
}

void modelNodeAccessScrollSpeed(TexAnimNode *arg0, s16 arg1, s16 arg2, s16 arg3, s16 *arg4, s16 *arg5, u8 arg6) {
    arg1--;
    while (arg0 != NULL && arg1 != 0) {
        arg0 = arg0->unkD4;
        arg1--;
    }
    if (arg0 != NULL) {
        if (arg6 != 0) {
            *arg4 = arg0->unk38;
            *arg5 = arg0->unk3A;
        } else {
            arg0->unk38 = arg2;
            arg0->unk3A = arg3;
        }
    }
}

void modelSlotSetNodeAnimMode(s32 arg0, s16 arg1, u8 arg2) {
    modelSlotAccessNodeAnimMode(arg0, arg1, arg2, &arg2, 0);
}

void modelSlotGetNodeAnimMode(s32 arg0, s16 arg1, u8 *arg2) {
    u8 sp27;

    modelSlotAccessNodeAnimMode(arg0, arg1, sp27, arg2, 1);
}

void modelNodeAccessAnimMode(TexAnimNode *, s16, u8, u8 *, u8);

void modelSlotAccessNodeAnimMode(s32 arg0, s16 arg1, u8 arg2, u8 *arg3, u8 arg4) {
    ModelSlot *slot;
    ModelSlotObj *obj;

    slot = hashTableLookup(arg0) + ((0, D_807F6000));
    obj = slot->unk20;
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            modelNodeAccessAnimMode(obj->unk50, arg1, arg2, arg3, arg4);
        }
    } else {
        modelNodeAccessAnimMode(obj->unkB8, arg1, arg2, arg3, arg4);
    }
}

void modelNodeAccessAnimMode(TexAnimNode *arg0, s16 arg1, u8 arg2, u8 *arg3, u8 arg4) {
    arg1--;
    while (arg0 != NULL && arg1 != 0) {
        arg0 = arg0->unkD4;
        arg1--;
    }
    if (arg0 != NULL) {
        if (arg4 != 0) {
            *arg3 = arg0->unk48;
        } else {
            arg0->unk48 = arg2;
        }
    }
}

void modelNodeSetFrame(TexAnimNode *, s16, s32, s32);

void modelSlotSetNodeFrame(s32 arg0, s16 arg1, s32 arg2, s32 arg3) {
    ModelSlot *slot;
    ModelSlotObj *obj;

    slot = hashTableLookup(arg0) + ((0, D_807F6000));
    obj = slot->unk20;
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            modelNodeSetFrame(obj->unk50, arg1, arg2, arg3);
        }
    } else {
        modelNodeSetFrame(obj->unkB8, arg1, arg2, arg3);
    }
}

void modelNodeSetFrame(TexAnimNode *arg0, s16 arg1, s32 arg2, s32 arg3) {
    arg1--;
    while (arg0 != NULL && arg1 != 0) {
        arg0 = arg0->unkD4;
        arg1--;
    }
    if (arg0 != NULL) {
        if (arg2 != arg0->unk54 || arg3 != arg0->unk50) {
            arg0->unk49 = 1;
        }
        arg0->unk54 = arg2;
        arg0->unk50 = arg3;
    }
}

void dlFindTextureCommands(u32 *arg0, s32 arg1, s32 arg2, s32 arg3, u32 **arg4, u32 **arg5, u32 **arg6) {
    s32 found;
    u32 cmd;

    *arg4 = NULL;
    *arg5 = NULL;
    *arg6 = NULL;
    found = 0;
    if (arg1 != 0) {
        do {
            cmd = *arg0;
            arg1 -= 8;
            if ((cmd >> 24) == ((0, 0xFD)) && arg2 == arg0[1]) {
                *arg4 = arg0;
                found = 1;
            }
            arg0 += 2;
        } while (found == 0 && arg1 != 0);
    }
    if (arg3 != 0) {
        found = 0;
        if (arg1 != 0) {
            do {
                cmd = *arg0;
                arg1 -= 8;
                if ((cmd >> 24) == ((0, 0xFD)) && arg2 == arg0[1]) {
                    *arg5 = arg0;
                    found = 1;
                }
                arg0 += 2;
            } while (found == 0 && arg1 != 0);
        }
        if (arg1 != 0) {
            found = 0;
            do {
                cmd = *arg0;
                arg1 -= 8;
                if ((cmd >> 24) == ((0, 0xFA))) {
                    *arg6 = arg0;
                    found = 1;
                }
                arg0 += 2;
            } while (found == 0 && arg1 != 0);
        }
    }
}


s32 dlLengthToEndDL(u32 *arg0) {
    s32 len;
    s32 found;
    u32 cmd;

    len = 0;
    found = 0;
    do {
        cmd = *arg0;
        len += 8;
        if ((cmd >> 24) == ((0, 0xDF))) {
            found = 1;
        }
        arg0 += 2;
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

typedef struct ModelQuadOwner {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ ModelQuadOutput *unk20;
    /* 0x24 */ u8 *unk24;
} ModelQuadOwner;

void modelQuadBuildOutput(ModelQuadOwner *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    ModelQuadOutput *out;
    ModelQuadData *q;
    u8 *data;
    s32 i;
    s32 j;
    s16 sum;

    data = arg0->unk24;
    out = arg0->unk20;
    q = (ModelQuadData *)(*(s32 *)(data + 0x70) + (s32)data + 4);
    out->unk0 = arg1;
    out->unk4 = arg2;
    out->unk8 = arg3;
    out->unkC = arg7;
    out->unk10 = arg8;
    out->unk20 = *(s32 *)(*(s32 *)(data + 0x70) + (s32)data);
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
} ModelSlotAsset;

void modelSlotLoadAssetTextures(u8 *arg0, ModelSlotAsset *arg1) {
    u8 type;
    s32 i;
    ModelSlotAsset *p;
    s16 *src;

    src = (s16 *)(arg0 + *(s32 *)(arg0 + 0x70) + 4);
    if (*(s32 *)(arg0 + *(s32 *)(arg0 + 0x6C)) != 0) {
        type = 7;
    } else {
        type = 0x19;
    }
    i = 0;
    if (arg1->unk20 > (type * 0)) {
        p = arg1;
        do {
            *(s32 *)((u8 *)p + 0x24) = (s32)assetLoad(type, src[0], 1, 0);
            if (src[1] != -1) {
                *(s32 *)((u8 *)p + 0x34) = (s32)assetLoad(type, src[1], 1, 0);
            } else {
                *(s32 *)((u8 *)p + 0x34) = 0;
            }
            i++;
            p = (ModelSlotAsset *)((u8 *)p + 4);
            src = (s16 *)((u8 *)src + 0x30);
        } while (i < arg1->unk20);
    }
}

void modelSlotClearAssetTextures(s32 arg0, u8 *arg1) {
    s32 *p;
    s32 i;

    i = 0;
    p = (s32 *)arg1;
    for (; i < arg1[0x20]; i++) {
        p[9] = 0;
        p[13] = 0;
        p++;
    }
}

void modelSlotFreeByIndex();
void hashTableClear(void);

void modelSlotsFreeAll(void) {
    s32 i;
    s32 n;

    n = D_80747D70;
    for (i = 0; i < n; i++) {
        modelSlotFreeByIndex(0, 0);
    }
    hashTableClear();
}

typedef struct ModelSlotFreeView {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 pad24[0x4C];
    /* 0x70 */ ModelLinkedNode *unk70;
    /* 0x74 */ ModelLinkedNode *unk74;
    /* 0x78 */ u8 **unk78;
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[8];
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} ModelSlotFreeView;

void actorClearEntrySlot(s16);
void hashTableRemove(s32);
void proxPathRemoveActor(s16);
void sfxSlotFreeSource(s16);
s32 mapPurgeNodeList();
void renderEntryRemove(s32, s32, s32, u8 *);
void csStateFree(void *);
void modelSlotFree(u8 **);
void modelSlotFreeTexAnimNodes(ModelSlot *);

void modelSlotFreeByIndex(arg0, arg1)
s32 arg0;
u8 arg1;
{
    s16 sp36;
    s16 sp34;
    u8 sp33;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    mapPurgeNodeList(((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk20, &sp34, 0);
    renderEntryRemove(0, ((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk20, 2, &sp33);
    dynamicBufferFree((u8 *)&D_807F6000[arg0] + 0x28);
    modelSlotTriBufferRelease((u8 *)&D_807F6000[arg0] + 0x48);
    modelPosNodeListFree(((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk70);
    modelLinkedNodeListFree(((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk74);
    modelSlotFree(((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk78);
    modelSlotFreeTexAnimNodes(&D_807F6000[arg0]);
    if (((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C != NULL) {
        csStateFree(((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C);
    }
    gCsModelIds[((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk8A] = -1;
    actorClearEntrySlot(((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk88);
    sp36 = ((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk88;
    hashTableRemove(sp36);
    proxPathRemoveActor(sp36);
    if (((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C != NULL) {
        if (*(s16 *)(((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C + 0x10) != -1) {
            sfxSlotFreeSource(*(s16 *)(((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C + 0x10));
        }
        if (*(s16 *)(((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C + 0x12) != -1) {
            sfxSlotFreeSource(*(s16 *)(((ModelSlotFreeView *)((u8 *)D_807F6000 + arg0 * 0x90))->unk7C + 0x12));
        }
    }
    if (arg0 + 1 != D_80747D70) {
        hashTableInsert(((ModelSlotFreeView *)((u8 *)D_807F6000 + D_80747D70 * 0x90 - 0x90))->unk88, arg0);
    }
    memcpy(&D_807F6000[arg0], &D_807F6000[D_80747D70] - 1, 0x90);
    D_80747D70 -= 1;
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

#define MODEL_SLOT_VEC(i) ((ModelSlotVectors *)((u8 *)D_807F6000 + (i) * 0x90))

void modelSlotGetTransformVectors(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, u8 arg9) {
    if (arg9 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    *arg1 = MODEL_SLOT_VEC(arg0)->unk0;
    *arg2 = MODEL_SLOT_VEC(arg0)->unk4;
    *arg3 = MODEL_SLOT_VEC(arg0)->unk8;
    *arg4 = MODEL_SLOT_VEC(arg0)->unk10;
    *arg5 = MODEL_SLOT_VEC(arg0)->unk14;
    *arg6 = MODEL_SLOT_VEC(arg0)->unk18;
    *arg7 = MODEL_SLOT_VEC(arg0)->unkC;
    *arg8 = MODEL_SLOT_VEC(arg0)->unk1C;
}

typedef struct ModelTransformPlayerTarget {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
} ModelTransformPlayerTarget;

typedef struct ModelTransformPlayer {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ ModelTransformPlayerTarget *unk4;
    /* 0x08 */ u8 pad8[0x2E8];
} ModelTransformPlayer;

typedef struct ModelTransformKind {
    /* 0x00 */ u8 pad0[0x67];
    /* 0x67 */ u8 unk67;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ s16 unk6C;
} ModelTransformKind;

typedef struct ModelTransformMeta {
    /* 0x00 */ u8 pad0[0x1E];
    /* 0x1E */ s16 unk1E;
} ModelTransformMeta;

typedef struct ModelTransformSlot {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ ModelSlotVectors *unk20;
    /* 0x24 */ ModelTransformMeta *unk24;
    /* 0x28 */ u8 pad28[0x54];
    /* 0x7C */ ModelTransformKind *unk7C;
    /* 0x80 */ u8 pad80[6];
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} ModelTransformSlot;

extern u8 gPlayerCount;
s32 activeActorBoxOverlapTest(f32, f32, f32, s16, s16, s16, u16);
s32 collisionCheckBoundingBoxXZ(void *, f32, f32);
s32 collisionCheckBoundingBoxY(void *, f32);
void collisionTransformNode(s32, void *, f32, f32, f32, f32, f32, f32, f32);
void modelSlotBuildTriangleBufferThunk(s32, void *, f32, f32, f32, f32, f32, f32, f32);
void actorUpdateEntryCoordinates(s16, f32, f32, f32, f32, f32);

#define MODEL_TRANSFORM_PLAYER(i) ((ModelTransformPlayer *)((u8 *)gPlayerSlots + (i) * 0x2F0U))
#define MODEL_TRANSFORM_SLOT0 ((ModelTransformSlot *)((u8 *)D_807F6000 + arg0 * 0x90))
#define MODEL_TRANSFORM_SLOT ((ModelTransformSlot *)((u8 *)D_807F6000 + off))

void modelSlotTransformBoundsAndNodes(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12, u8 arg13) {
    ModelTransformSlot *v1;
    ModelSlotVectors *p;
    s16 sp76;
    u8 flag;
    u8 sel;
    s32 i;
    s32 off;

    flag = 0;
    if (arg13 == 1) {
        if (arg0) {}  // FAKE: dead test raises arg0 candidate priority (steers uopt colouring)
        arg0 = hashTableLookup(arg0);
    }
    if (arg12) {
        MODEL_TRANSFORM_SLOT0->unk1C = arg8;
        v1 = MODEL_TRANSFORM_SLOT0;
        switch (v1->unk86) {
            case 2:
                p = v1->unk20;
                p->unk10 = arg8;
                break;
            case 1:
                p = v1->unk20;
                p->unk1C = arg8;
                break;
        }
    }
    off = arg0 * 0x90;
    if (arg9) {
        MODEL_TRANSFORM_SLOT->unk0 = arg1;
        MODEL_TRANSFORM_SLOT->unk4 = arg2;
        MODEL_TRANSFORM_SLOT->unk8 = arg3;
        if (flag) {}  // FAKE: dead test raises flag candidate priority (steers uopt colouring)
        v1 = MODEL_TRANSFORM_SLOT;
        switch (v1->unk86) {
            case 2:
                p = v1->unk20;
                p->unk0 = arg1;
                p->unk4 = arg2;
                p->unk8 = arg3;
                break;
            case 1:
                p = v1->unk20;
                p->unk0 = arg1;
                p->unk4 = arg2;
                p->unk8 = arg3;
                break;
        }
    }
    if (arg10) {
        MODEL_TRANSFORM_SLOT->unk10 = arg4;
        MODEL_TRANSFORM_SLOT->unk14 = arg5;
        MODEL_TRANSFORM_SLOT->unk18 = arg6;
        v1 = MODEL_TRANSFORM_SLOT;
        if (v1->unk86 == 1) {
            p = v1->unk20;
            p->unk10 = arg4;
            p->unk14 = arg5;
            p->unk18 = arg6;
        }
    }
    if (arg11) {
        MODEL_TRANSFORM_SLOT->unkC = arg7;
        v1 = MODEL_TRANSFORM_SLOT;
        switch (v1->unk86) {
            case 2:
                p = v1->unk20;
                p->unkC = arg7;
                break;
            case 1:
                p = v1->unk20;
                p->unkC = arg7;
                break;
        }
    }
    if ((arg9 || arg12) && mapPurgeNodeList((s32)MODEL_TRANSFORM_SLOT->unk20, &sp76, 0)) {
        v1 = MODEL_TRANSFORM_SLOT;
        renderEntryAddOrUpdate(0, ((u8 *)v1)[0x87], v1->unk20, v1->unk0, v1->unk4, v1->unk8, v1->unk24->unk1E, v1->unk88, 0, sp76, 2);
    }
    v1 = MODEL_TRANSFORM_SLOT;
    if (arg9 || arg12 || arg10) {
        actorUpdateEntryCoordinates(v1->unk88, v1->unk0, v1->unk4, v1->unk8, v1->unkC, v1->unk14);
        v1 = MODEL_TRANSFORM_SLOT;
    }
    if (v1->unk7C != NULL) {
        sel = v1->unk7C->unk67;
        switch (sel) {
            case 0:
                flag = 1;
                break;
            case 2:
                if (gPlayerSlots != 0) {
                    i = 0;
                    if (gPlayerCount > 0) {
                        do {
                            if (MODEL_TRANSFORM_PLAYER(i)->unk0 != 0) {
                                flag |= collisionCheckBoundingBoxY(((u8 *)off + (s32)D_807F6000 + 0x54), MODEL_TRANSFORM_PLAYER(i)->unk4->unk80) != 0 && collisionCheckBoundingBoxXZ(((u8 *)off + (s32)D_807F6000 + 0x54), MODEL_TRANSFORM_PLAYER(i)->unk4->unk7C, MODEL_TRANSFORM_PLAYER(i)->unk4->unk84) != 0;
                            }
                            i = (u8)(i + 1);
                        } while (i < gPlayerCount);
                        v1 = MODEL_TRANSFORM_SLOT;
                    }
                }
                break;
            case 1:
                if (gPlayerSlots != 0) {
                    i = 0;
                    if (gPlayerCount > 0) {
                        do {
                            if (MODEL_TRANSFORM_PLAYER(i)->unk0 != 0) {
                                flag |= collisionCheckBoundingBoxXZ(((u8 *)off + (s32)D_807F6000 + 0x54), MODEL_TRANSFORM_PLAYER(i)->unk4->unk7C, MODEL_TRANSFORM_PLAYER(i)->unk4->unk84);
                            }
                            i = (u8)(i + 1);
                        } while (i < gPlayerCount);
                        v1 = MODEL_TRANSFORM_SLOT;
                    }
                }
                break;
            case 3:
            case 4:
                if (gPlayerSlots != 0) {
                    flag = activeActorBoxOverlapTest(v1->unk0, v1->unk4, v1->unk8, v1->unk7C->unk68, v1->unk7C->unk6A, v1->unk7C->unk6C, sel == 3 ? 0xEF : 1);
                    v1 = MODEL_TRANSFORM_SLOT;
                }
                break;
        }
    }
    if (flag != 0) {
        collisionTransformNode(arg0, v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC);
        v1 = MODEL_TRANSFORM_SLOT;
        modelSlotBuildTriangleBufferThunk(arg0, v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC);
        v1 = MODEL_TRANSFORM_SLOT;
    }
    modelSlotBuildVertPosList(arg0, (ModelVertTable *)v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC, 1);
    v1 = MODEL_TRANSFORM_SLOT;
    modelSlotBuildNodePosList(arg0, (ModelVertTable *)v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC, 1);
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

s32 activeActorBoxOverlapTest(f32 arg0, f32 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5, u16 arg6) {
    s32 i;
    ActorBoundsView *b;
    ActorBoundsView *a;
    s16 rx;
    s16 ry;
    s16 rz;

    rx = arg3;
    ry = arg4;
    rz = arg5;
    for (i = 0; i < gActiveActorCount; i++) {
        a = gActiveActors[i].actor;
        b = a;
        if (b->unk5C & arg6) {
            if (arg0 - arg3 <= b->unk7C && arg1 - arg4 <= b->unk80 && arg2 - arg5 <= b->unk84 &&
                a->unk7C <= arg3 + arg0 && a->unk80 <= arg4 + arg1 && a->unk84 <= arg5 + arg2) {
                return 1;
            }
        }
    }
    return 0;
}

void func_8062D094(void *, u8);

void func_80636014(s32 arg0, u8 arg1, u8 arg2) {
    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    func_8062D094(D_807F6000[arg0].unk20, arg2);
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
    /* 0x54 */ s32 *unk54;
    /* 0x58 */ u8 pad58[0x60];
    /* 0xB8 */ ModelNodeChain *unkB8;
    /* 0xBC */ s32 *unkBC;
} ModelChainOwner;

void modelSegmentFreeUnusedTextures(ModelSlot *, void *, ModelChainOwner *);
void modelSlotFreeAssetEntry(void *, ModelSlotAsset *);

void modelSlotFreeTexAnimNodes(ModelSlot *arg0) {
    ModelNodeChain *node;
    ModelChainOwner *ownerA;
    s32 *sp24;
    ModelChainOwner *ownerB;
    ModelNodeChain *cur;

    switch (arg0->unk86) {
        case 2:
            ownerA = arg0->unk20;
            node = ownerA->unk50;
            sp24 = ownerA->unk54;
            modelSlotFreeAssetEntry(arg0->unk24, (ModelSlotAsset *)ownerA);
            break;
        case 1:
            ownerB = arg0->unk20;
            node = ownerB->unkB8;
            sp24 = ownerB->unkBC;
            modelSegmentFreeUnusedTextures(arg0, arg0->unk24, ownerB);
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
    if (sp24 != NULL) {
        assetFreeBuffer((void *)*sp24, 0x9E5, 7);
        heapFree(sp24);
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

void modelSlotFreeTexAnimBuffers(ModelNodeBufferOwner *arg0, u8 arg1) {
    ModelNodeBufferChain *node;

    if (arg1 != 1) {
        if (arg1 == 2) {
            node = arg0->unk50;
            goto walk;
        }
    } else {
        node = arg0->unkB8;
walk:
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
}

void modelSlotFreeAssetTextures(u8 *arg0, u8 arg1) {
    s32 *p;
    u8 *base;
    s32 *cur;
    s32 i;
    void *q;

    if (arg1 == 2 && *(s32 *)(arg0 + 0x50) == 0) {
        base = arg0;
        i = 0;
        p = (s32 *)arg0;
        if (base[0x20] > 0) {
            do {
                q = (void *)p[9];
                if (q != NULL) {
                    assetFreeBuffer(q, 0xA2B, 7);
                    p[9] = 0;
                }
                if (base) {
                }
                cur = p;
                q = (void *)cur[13];
                if (q != NULL) {
                    assetFreeBuffer(q, 0xA30, 7);
                    if (base && base && base) {
                    }
                    p[13] = 0;
                }
                i++;
                p++;
            } while (i < base[0x20]);
        }
    }
}

void modelSlotFreeNestedBuffer(s32 arg0, u8 arg1) {
    s32 *sp1C;
    s32 **sp18;
    ModelSlot *slot;
    s32 ***pp;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    slot = &D_807F6000[arg0];
    if (slot->unk86 != 1) {
        if (slot->unk86 == 2) {
            sp18 = (s32 **)((u8 *)slot->unk20 + 0x54);
        }
    } else {
        sp18 = (s32 **)((u8 *)slot->unk20 + 0xBC);
    }
    pp = &sp18;
    if (*pp != NULL) {
        sp1C = **pp;
        if (sp1C != NULL) {
            assetFreeBuffer((void *)*sp1C, 0xA56, 7);
            heapFree(sp1C);
            **pp = NULL;
        }
    }
}

void heapFreeDeferred(void *);

void modelSlotFreeAssetEntry(void *arg0, ModelSlotAsset *arg1) {
    s32 i;
    void **p;

    p = (void **)arg1;
    i = 0;
    if (arg1->unk20 > 0) {
        do {
            if (p[9] != NULL) {
                assetFreeBuffer(p[9], 0xA69, 7);
            }
            if (p[13] != NULL) {
                assetFreeBuffer(p[13], 0xA6A, 7);
            }
            i++;
            p++;
        } while (i < arg1->unk20);
    }
    assetFreeBuffer(arg0, 0xA6E, 7);
    heapFreeDeferred(arg1->unk1C);
    heapFreeDeferred(arg1);
    heapFreeDeferred(arg1->unk14);
    heapFreeDeferred(arg1->unk18);
}

typedef struct DisplayListFreeRecord {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ struct DisplayListFreeRecord *unk18;
} DisplayListFreeRecord;

extern DisplayListFreeRecord *D_807F6160;

void displayListFreeQueueReset(void) {
    D_807F6160 = 0;
}

void displayListFreeQueueAdd(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    DisplayListFreeRecord *rec;
    DisplayListFreeRecord *old;

    rec = heapAlloc(0x1C);
    old = D_807F6160;
    D_807F6160 = rec;
    rec->unk18 = old;
    rec->unk0 = arg0;
    rec->unk4 = arg1;
    rec->unk8 = arg2;
    rec->unkC = arg3;
    rec->unk14 = gFrameCounter + 2;
    rec->unk10 = arg4;
}

typedef struct DisplayListFreeCounter {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ s16 unk3C;
} DisplayListFreeCounter;

void dlFreeUnusedTextures();

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
                ((DisplayListFreeCounter *)cur->unk10)->unk3C -= 1;
                dlFreeUnusedTextures(cur->unk0, cur->unk4, 0, 0, ((DisplayListFreeCounter *)cur->unk10)->unk3C == 0);
                dlFreeUnusedTextures(cur->unk8, cur->unkC, 0, 1, ((DisplayListFreeCounter *)cur->unk10)->unk3C == 0);
                assetFreeBuffer((void *)cur->unk10, 0xAB1, 7);
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

typedef struct DisplayListTextureNode {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ void *unk18;
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ void *unk24;
    /* 0x28 */ void *unk28;
    /* 0x2C */ u8 pad2C[0xA8];
    /* 0xD4 */ struct DisplayListTextureNode *unkD4;
} DisplayListTextureNode;

typedef struct ModelSegmentData {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ u32 unkA0;
    /* 0xA4 */ u32 unkA4;
    /* 0xA8 */ u32 unkA8;
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ u32 unkB0;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ DisplayListTextureNode *unkB8;
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

void texAnimNodeUpdateBuffers(ModelSegmentNode *, s32 *, s32 *, u8 *, s16 *);
void collisionBstLookupByHash(s32, s32 *, s32 *);


void modelSegmentFreeUnusedTextures(ModelSlot *arg0, void *arg1, ModelChainOwner *arg2) {
    DisplayListTextureNode *s3;
    u32 head, tail;
    u8 flag;
    ModelSegmentData *seg;

    seg = (ModelSegmentData *)arg2;
    s3 = seg->unkB8;
    head = seg->unkA8 - seg->unkA0;
    tail = seg->unkB0 - seg->unkA8;
    if (s3 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    head >>= 3;
    tail >>= 3;
    if (s3 == NULL && (arg0->unk8C & 0x20)) {
        flag = 0;
    } else {
        flag = 1;
    }
    if (arg0->unk8C & 0x20) {
        if (flag != 0) {
            ((DisplayListFreeCounter *)arg1)->unk3C -= 1;
            dlFreeUnusedTextures(seg->unkA0, seg->unkA0 + head * 8, (s32)seg->unkB8, 0, 0);
            dlFreeUnusedTextures(seg->unkA8, seg->unkA8 + tail * 8, (s32)seg->unkB8, 1, 0);
            if (s3 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            s3 = seg->unkB8;
        } else {
            displayListFreeQueueAdd(seg->unkA0, seg->unkA0 + head * 8, seg->unkA8, seg->unkA8 + tail * 8, (s32)arg1);
            s3 = seg->unkB8;
        }
    }
    flag = flag | 0;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (s3 != NULL) {
        dlFreeUnusedTextures(seg->unkA4, seg->unkA4 + head * 8, (s32)s3, 0, 0);
        dlFreeUnusedTextures(seg->unkAC, seg->unkAC + tail * 8, (s32)seg->unkB8, 1, 0);
        heapFreeDeferred((void *)seg->unkA4);
        heapFreeDeferred((void *)seg->unkAC);
    }
    if (flag != 0) {
        assetFreeBuffer(arg1, 0xAF7, 7);
    }
    heapFreeDeferred(arg2);
}

void dlFreeUnusedTextures(arg0, arg1, arg2, arg3, arg4)
DisplayListCmd *arg0;
DisplayListCmd *arg1;
DisplayListTextureNode *arg2;
u8 arg3;
u8 arg4;
{
    u32 w;
    u32 found;
    DisplayListTextureNode *node;
    s32 sp40;
    s32 sp3C;

    if (0) {
        assetFreeBuffer(&arg3, 0, 0);
    }
    if (arg0 != arg1) {
        if (arg4 != 0) {
        }
        do {
            w = arg0->unk0;
            found = 0;
            if ((w >> 24) == 0xFD) {
                node = arg2;
                if (node != NULL) {
                    do {
                        switch (arg3) {
                            case 0:
                                if ((void *)arg0 == node->unk0) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unk4) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unkC) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unk10) {
                                    found = 1;
                                }
                                break;
                            case 1:
                                if ((void *)arg0 == node->unk18) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unk1C) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unk24) {
                                    found = 1;
                                }
                                if ((void *)arg0 == node->unk28) {
                                    found = 1;
                                }
                                break;
                        }
                        node = node->unkD4;
                    } while (found == 0 && node != NULL);
                }
                if (found == 0) {
                    if (arg4 != 0) {
                        collisionBstLookupByHash((s32)arg0->unk4, &sp40, &sp3C);
                    }
                    assetFreeBuffer((void *)arg0->unk4, 0xB27, 7);
                    if (arg4 != 0) {
                        arg0->unk4 = sp3C;
                    }
                }
            }
            arg0++;
        } while (arg0 != arg1);
    }
}

typedef struct ModelAssetHeader {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 pad1D[0x23];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
} ModelAssetHeader;

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

extern u8 D_80750AB4;
u8 func_80636A8C(s32);

void modelSlotInitFromAsset(ModelSlot *arg0, s32 arg1) {
    ModelAssetHeader *hdr;
    ModelSegmentData *seg;
    s32 pad;
    void *sp28;
    ModelType2Obj *obj;

    if (func_80636A8C(arg1) != 0) {
        arg0->unk24 = assetLoad(4, arg1, 1, 1);
    } else {
        arg0->unk24 = assetLoad(4, arg1, 1, 0);
    }
    hdr = (ModelAssetHeader *)arg0->unk24;
    arg0->unk8C = 0;
    arg0->unk86 = hdr->unk1C;
    arg0->unk84 = arg1;
    if (hdr->unk1C != 1) {
        if (hdr->unk1C == 2) {
            obj = heapAlloc(0x60);
            sp28 = obj;
            obj->unk4A = arg1;
            obj->unk50 = 0;
            obj->unk54 = 0;
            obj->unk4C = -1;
            obj->unk4E = 0;
            obj->unk5B = 0;
            obj->unk14 = heapAlloc(D_80750AB4 << 6);
            obj->unk18 = heapAlloc(D_80750AB4 << 6);
        }
    } else {
        seg = heapAlloc(0xC8);
        sp28 = seg;
        seg->unkB4 = arg1;
        seg->unkB8 = 0;
        seg->unkA0 = hdr->unk40 + (u32)hdr;
        seg->unkA8 = hdr->unk44 + (u32)hdr;
        seg->unkB0 = hdr->unk48 + (u32)hdr;
        seg->unkBC = 0;
        seg->unkB6 = -1;
        seg->unkC3 = 0;
    }
    arg0->unk20 = sp28;
}

f32 func_80636A44(s32 arg0) {
    s32 pad;
    s32 *asset;
    f32 result;

    asset = assetLoad(4, arg0, 1, 0);
    result = ((f32 *)asset)[1];
    assetFreeBuffer(asset, 0xB87, 7);
    return result;
}

u8 func_80636A8C(s32 arg0) {
    s32 pad;
    s32 *asset;
    s32 result;

    asset = assetLoad(4, arg0, 1, 0);
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

void modelSlotReplaceSegment6Commands(void *arg0) {
    u32 head;
    ModelSegmentData *seg;
    u32 mid;
    u32 count;
    u32 len;
    u32 start;

    seg = ((ModelSlotSegOwner *)arg0)->unk20;
    mid = seg->unkA8;
    head = seg->unkA0;
    start = head;
    len = seg->unkB0 - mid;
    head = (mid - head) >> 3;
    count = len >> 3;
    renderReplaceSegment6Commands(start, (0, start) + head * 8, seg, len);
    len = count;
    renderReplaceSegment6Commands(seg->unkA8, seg->unkA8 + count * 8, seg, len);
}

void dlFreeSegmentCommandTextures(DisplayListCmd *arg0, DisplayListCmd *arg1, u8 arg2) {
    u32 w;
    u32 tag;
    s32 sp34;
    s32 sp30;

    if (arg0 != arg1) {
        do {
            w = arg0->unk0;
            tag = w >> 24;
            if (0xFD == tag) {
                if (arg2) {
                    collisionBstLookupByHash(arg0->unk4, &sp34, &sp30);
                }
                assetFreeBuffer((void *)arg0->unk4, 0xBCD, 7);
                if (arg2) {
                    arg0->unk4 = sp30;
                }
            }
            arg0++;
        } while (arg0 != arg1);
    }
}


typedef struct ModelSlotObjHeader {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 pad1D[0x1F];
    /* 0x3C */ s16 unk3C;
} ModelSlotObjHeader;

extern s16 D_80747D74;

void modelSlotsStepSegmentCommands(void) {
    u32 mid;
    ModelSegmentData *seg;
    u32 head;
    u32 count;
    u8 flag;
    ModelSlotObjHeader *obj;
    ModelSlot *slot;
    u32 start;
    u32 len;

    if (D_80747D70 != 0) {
        D_80747D74 += 1;
        if (D_80747D74 >= D_80747D70) {
            D_80747D74 = 0;
        }
        slot = (ModelSlot *)((u8 *)D_807F6000 + D_80747D74 * 0x90);
        obj = (ModelSlotObjHeader *)slot->unk24;
        if (obj->unk0 & 0x10) {
            if ((slot->unk8C & 0x20) && gFrameCounter != obj->unk8) {
                slot->unk8C &= ~0x20;
                obj->unk3C -= 1;
                if (obj->unk3C != 0) {
                    flag = 0;
                } else {
                    flag = 1;
                }
                seg = ((ModelSlot *)((u8 *)D_807F6000 + D_80747D74 * 0x90))->unk20;
                mid = seg->unkA8;
                head = seg->unkA0;
                start = head;
                len = seg->unkB0 - mid;
                head = (mid - head) >> 3;
                count = len >> 3;
                dlFreeSegmentCommandTextures((DisplayListCmd *)start, (DisplayListCmd *)((0, start) + head * 8), flag);
                len = count;
                count = 0;
                dlFreeSegmentCommandTextures((DisplayListCmd *)seg->unkA8, (0, (DisplayListCmd *)(seg->unkA8 + len * 8)), flag);
            }
        }
    }
}




#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/modelSlotResolveAssetTextures.s")


s32 dlResolveNodeTextures(DisplayListCmd *arg0, DisplayListCmd *arg1, ModelSegmentNode *arg2, u8 arg3) {
    u32 w;
    u32 tag;
    s32 result;
    s32 found;
    ModelSegmentNode *node;

    result = 0;
    if (arg0 != arg1) {
        do {
            w = arg0->unk0;
            found = 0;
            tag = w >> 24;
            if (0xFD == tag) {
                node = arg2;
                if (node != NULL) {
                    do {
                        if (arg0->unk4 == node->unk5C[0]) {
                            found = 1;
                        } else {
                            node = node->unkD4;
                        }
                    } while (found == 0 && node != NULL);
                }
                if (found == 0) {
                    arg0->unk4 = (s32)assetLoad(0x19, arg0->unk4, (u8)(arg3 == 0), 0);
                    if (arg0->unk4 & 7) {
                        arg0->unk4 &= ~0xF;
                        result = 1;
                    }
                }
            }
            arg0++;
        } while (arg0 != arg1);
    }
    return result;
}

#ifdef NON_MATCHING
typedef struct {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 pad61;
    /* 0x62 */ s16 unk62;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ u8 pad66[0x32];
    /* 0x98 */ s16 unk98;
} ModelRenderSlot;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ struct ModelRenderPlayerCtl *unk4;
    /* 0x08 */ u8 pad8[0x214];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ u8 pad228[0xC8];
} ModelRenderPlayer; /* 0x2F0 */

typedef struct ModelRenderPlayerCtl {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
} ModelRenderPlayerCtl;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ Mtx unk20[2];
    /* 0xA0 */ u32 unkA0[2];
    /* 0xA8 */ u32 unkA8[2];
    /* 0xB0 */ u32 unkB0;
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

void texAnimUpdateNodes(ModelSegmentData *);
void func_8063E6B4(void *);
void lightSampleColorAtPosition(f32, f32, f32, s16, u8 *, u8 *, u8 *, s16);
void lightQueueKeyframed(u8, s16, f32, f32, f32, s32, f32, s32);
s32 func_806D0964(s32, u8, s32);
void renderCalcPlayerDistanceAlpha(f32, f32, f32, f32, s16, s16 *);
f32 renderScaleDistanceByFov(f32);
Gfx *renderSetSegment6AndFog(Gfx *, s16, u8);

#define MODEL_RENDER_PLAYER(i) (((ModelRenderPlayer *)gPlayerSlots)[i])

Gfx *renderModelAnimatedSlot(ModelRenderAnimObj *arg0, Gfx *arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, s16 arg6, s32 arg7) {
    f32 spF8[4][4];
    f32 spB8[4][4];
    f32 dx;
    f32 dy;
    f32 dz;
    u8 sel;
    u8 *sel78;
    f32 scale;
    ModelRenderSlot *model;
    s32 pad;
    u8 sp97;
    u8 sp96;
    u8 sp95;
    s16 sp92;
    s16 sp90;
    s32 pad2;
    f32 sp88;
    f32 sp84;

    if (0) {
        func_8063E6B4((void *)&arg5);
    }
    if (arg5 != 0) {
        dx = MODEL_RENDER_PLAYER(gCurrentPlayerIndex).unk21C - arg0->unk0;
        dy = MODEL_RENDER_PLAYER(gCurrentPlayerIndex).unk220 - arg0->unk4;
        dz = MODEL_RENDER_PLAYER(gCurrentPlayerIndex).unk224 - arg0->unk8;
        dx *= dx;
        dy *= dy;
        dz *= dz;
        sp88 = sqrtf(dx + dy + dz);
        sp84 = renderScaleDistanceByFov(arg0->unkC0);
        if (arg0->unkC5 & 1) {
            sp84 = arg0->unkC0;
        }
        if (sp84 < sp88) {
            return arg1;
        }
    }
    if (arg0->unkC3 != 0) {
        lightQueueKeyframed(arg0->unkC3, arg0->unkB6, arg0->unk0, arg0->unk4, arg0->unk8, arg0->unkC0, sp88 / sp84, arg6);
    }
    if (arg0->unkB4 == 0 || arg0->unkB4 == 0x241) {
        return arg1;
    }
    if (arg0->unkB4 == 0x74 || arg0->unkB4 == 0x288 || arg0->unkB4 == 0x290) {
        arg0->unk14 += 10.0;
    }
    guScaleF(spF8, arg0->unkC, arg0->unkC, arg0->unkC);
    if (arg0->unk10 != 0.0) {
        guRotateF(spB8, arg0->unk10, 1.0f, 0.0f, 0.0f);
        guMtxCatF(spF8, spB8, spF8);
    }
    if (arg0->unk14 != 0.0) {
        guRotateF(spB8, arg0->unk14, 0.0f, 1.0f, 0.0f);
        guMtxCatF(spF8, spB8, spF8);
    }
    if (arg0->unk18 != 0.0) {
        guRotateF(spB8, arg0->unk18, 0.0f, 0.0f, 1.0f);
        guMtxCatF(spF8, spB8, spF8);
    }
    guTranslateF(spB8, arg0->unk0, arg0->unk4, arg0->unk8);
    guMtxCatF(spF8, spB8, spF8);
    guMtxF2L(spF8, &arg0->unk20[D_807444FC]);
    gDPPipeSync(arg1++);
    gSPSegment(arg1++, 8, osVirtualToPhysical((void *)arg0->unkB0));
    sel78 = NULL;
    if (arg0->unkB6 != -1) {
        sp90 = hashTableLookup(arg0->unkB6);
        modelSlotResolveAssetTextures(&D_807F6000[sp90], 0, 1);
        sel78 = D_807F6000[sp90].unk78;
        if (func_806D0964(*(s32 *)D_807F6000[sp90].unk24, gCurrentPlayerIndex, (s32)sel78) != 0) {
            return arg1;
        }
    }
    if (sel78 != NULL) {
        gSPSegment(arg1++, 9, osVirtualToPhysical((void *)((u32 *)sel78)[D_807444FC]));
    }
    gSPMatrix(arg1++, osVirtualToPhysical(&arg0->unk20[D_807444FC]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    if (arg0->unkB8 != 0) {
        sel = D_807444FC;
        texAnimUpdateNodes((ModelSegmentData *)arg0);
    } else {
        sel = 0;
    }
    gSPSegment(arg1++, 10, osVirtualToPhysical((void *)arg0->unkA0[sel]));
{ s32 pad4; }
gSPClearGeometryMode(arg1++, G_FOG | G_CULL_BOTH);
    if (arg5 != 0 && arg0->unkC2 == 0) {
        model = D_807F6000[sp90].unk7C;
        if (model != NULL) {
            scale = model->unk98;
        } else {
            scale = 0.0f;
        }
        lightSampleColorAtPosition(arg0->unk0, arg0->unk4 + scale, arg0->unk8, 0, &sp97, &sp96, &sp95, arg6);
        scale = arg0->unkC4 / 15.0f;
        sp97 = sp97 * scale;
        sp96 = sp96 * scale;
        sp95 = sp95 * scale;
    } else {
        sp95 = 0xFF;
        sp96 = 0xFF;
        sp97 = 0xFF;
    }
    gDPSetPrimColor(arg1++, 0, 0xFF, sp97, sp96, sp95, 0xFF);
    if (arg5 != 0) {
        if (arg0->unkB6 != -1 && (model = D_807F6000[sp90].unk7C) != NULL && model->unk60 == 1) {
            func_8063E6B4(model);
            sp92 = ((ModelRenderSlot *)D_807F6000[sp90].unk7C)->unk64;
        } else {
            renderCalcPlayerDistanceAlpha(arg0->unk0, arg0->unk4, arg0->unk8, arg0->unkC0, arg0->unkB4, &sp92);
            if (arg0->unkB6 != -1) {
                model = D_807F6000[sp90].unk7C;
                if (model != NULL && D_80750AB4 == 1) {
                    model->unk62 = sp92;
                }
            }
            if (arg0->unkB6 != -1) {
                model = D_807F6000[sp90].unk7C;
                if (model != NULL) {
                    func_8063E6B4(model);
                }
            }
            if (arg0->unkB6 != -1) {
                model = D_807F6000[sp90].unk7C;
                if (model != NULL && D_80750AB4 == 1) {
                    sp92 = model->unk64;
                }
            }
        }
    } else {
        sp92 = 0xFF;
    }
    if (sp92 != 0) {
        if (arg0->unkB6 != -1) {
            u8 fl = D_807F6000[sp90].unk8C;
            if (arg0->unkC2 && arg0->unkC2) {}  // FAKE: extra spilled-candidate slot (holes below the spill slots, frame 0x138)
            if (fl != 0) {
                if ((D_807F6000[sp90].unk8C & 0x8) && MODEL_RENDER_PLAYER(gCurrentPlayerIndex).unk4->unk58 != 2) {
                    sp92 = 0x64;
                }
                if ((D_807F6000[sp90].unk8C & 0x2) && MODEL_RENDER_PLAYER(gCurrentPlayerIndex).unk4->unk58 != 3) {
                    sp92 = 0x64;
                }
                if ((D_807F6000[sp90].unk8C & 0x4) && MODEL_RENDER_PLAYER(gCurrentPlayerIndex).unk4->unk58 != 5) {
                    sp92 = 0x64;
                }
                if ((D_807F6000[sp90].unk8C & 0x1) && MODEL_RENDER_PLAYER(gCurrentPlayerIndex).unk4->unk58 != 6) {
                    sp92 = 0x64;
                }
                if ((D_807F6000[sp90].unk8C & 0x10) && MODEL_RENDER_PLAYER(gCurrentPlayerIndex).unk4->unk58 != 4) {
                    sp92 = 0x64;
                }
            }
        }
        arg1 = renderSetSegment6AndFog(arg1, sp92, 0);
        gDPPipeSync(arg1++);
        gSPDisplayList(arg1++, osVirtualToPhysical((void *)arg0->unkA0[sel]));
        gDPPipeSync(arg1++);
        gSPDisplayList(arg1++, osVirtualToPhysical((void *)arg0->unkA8[sel]));
    }
    { s32 pad6; }
    gDPPipeSync(arg1++);
    gSPPopMatrix(arg1++, G_MTX_MODELVIEW);
    return arg1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/renderModelAnimatedSlot.s")
#endif

typedef struct RenderQuadModelObj {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ Mtx *unk14;
    /* 0x18 */ Mtx *unk18;
    /* 0x1C */ Vtx *unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 pad28[0xC];
    /* 0x34 */ s32 unk34[4];
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45;
    /* 0x46 */ u8 unk46;
    /* 0x47 */ u8 unk47;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ u8 pad50[8];
    /* 0x58 */ s16 unk58;
    /* 0x5A */ u8 unk5A;
    /* 0x5B */ u8 unk5B;
    /* 0x5C */ u8 unk5C;
} RenderQuadModelObj;

#define WRITE_GFX_PAIR(a, b) { Gfx *_g = (Gfx *)(arg1++); _g->words.w0 = (a); _g->words.w1 = (b); }

extern u8 D_807F6009;
extern s32 D_807F600C;
extern s32 D_807F5FD8;

f32 renderScaleDistanceByFov(f32);
void lightQueueKeyframed(u8, s16, f32, f32, f32, s32, f32, s32);
s32 mapPointOutsideClipBounds(f32, f32, f32, s32, s32);
void camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
void mapSearchTableAddProbe(void *, s16, s16, s16);
u8 mapSearchTableGetValue(void *);
void lightSampleColorAtPosition(f32, f32, f32, s16, u8 *, u8 *, u8 *, s16);
void modelKongVisibilityCheck(s16, u8 *, s16 *);
void texAnimFindNodeFrame(ModelSegmentOwner *, s32, s32 *, s32 *, u8 *, s16 *);
void modelCalcFacingAngles(f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *, u8);

Gfx *renderModelQuadGfx(RenderQuadModelObj *arg0, Gfx *arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, s16 arg6) {
    f32 sp238[4][4];
    f32 sp1F8[4][4];
    f32 sp1F4;
    f32 sp1F0;
    f32 sp1EC;
    s32 sp1E8;
    s32 sp1E4;
    u8 sp1E3;
    s16 sp1E0;
    f32 dx;
    f32 sp1D8;
    f32 sp1D4;
    f32 sp1D0;
    f32 dy;
    f32 dz;
    s32 pad0;
    f32 scale;
    s16 limit;
    s32 i;
    s32 sp1B4;
    s16 pad16;
    s16 sp1B0;
    u8 sp1AF;
    u8 sp1AE;
    u8 sp1AD;
    u8 sp1AC;
    u8 sp1AB;
    Mtx *mtx;
    s32 pad[1];

    if (0) {
        modelKongVisibilityCheck(0, &arg5, 0);
    }
    sp1B4 = 0;
    sp1AF = 0;
    if (arg5 != 0) {
        dx = arg2 - arg0->unk0;
        dy = arg3 - arg0->unk4;
        dz = arg4 - arg0->unk8;
        dx *= dx;
        dy *= dy;
        dz *= dz;
        sp1D0 = sqrtf(dx + dy + dz);
        limit = renderScaleDistanceByFov((f32)arg0->unk58);
        if ((f32)limit < sp1D0) {
            return arg1;
        }
    }
    if (arg0->unk5B != 0) {
        lightQueueKeyframed(arg0->unk5B, arg0->unk4C, arg0->unk0, arg0->unk4, arg0->unk8, arg0->unk58, sp1D0 / (f32)limit, arg6);
    }
    if (arg5 != 0) {
        if (mapPointOutsideClipBounds(arg0->unk0, arg0->unk4, arg0->unk8, 0, 0) != 0) {
            return arg1;
        }
    } else {
        limit = -0x8000;
        sp1D0 = 1.0f;
    }
    if (arg0->unk4E & 0x10) {
        return arg1;
    }
    if (arg0->unk4E & 8) {
        camProjectToScreen(arg0->unk0, arg0->unk4, arg0->unk8, &sp1D8, &sp1D4, 0, 1.0f, gCurrentPlayerIndex);
        mapSearchTableAddProbe(arg0, sp1D8, sp1D4, sp1D0);
        if (mapSearchTableGetValue(arg0) != 0) {
            return arg1;
        }
    }
    D_807F5FD8 += 1;
    if (arg0->unk24 == 0) {
        modelSlotLoadAssetTextures(D_807F6000[(s16)hashTableLookup(arg0->unk4C)].unk24, (ModelSlotAsset *)arg0);
    }
    modelCalcFacingAngles(arg0->unk0, arg0->unk4, arg0->unk8, arg2, arg3, arg4, &sp1F4, &sp1F0, &sp1EC, arg0->unk4E & 4);
    guTranslateF(sp238, 0.0f, -arg0->unk48, 0.0f);
    if (sp1F4 != 0.0) {
        guRotateF(sp1F8, sp1F4, 1.0f, 0.0f, 0.0f);
        guMtxCatF(sp238, sp1F8, sp238);
    }
    if (sp1F0 != 0.0) {
        guRotateF(sp1F8, sp1F0, 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp238, sp1F8, sp238);
    }
    if (arg0->unkC != 1.0) {
        guScaleF(sp1F8, arg0->unkC, arg0->unkC, arg0->unkC);
        guMtxCatF(sp238, sp1F8, sp238);
    }
    guTranslateF(sp1F8, arg0->unk0, arg0->unk4 + arg0->unk48 * arg0->unkC, arg0->unk8);
    guMtxCatF(sp238, sp1F8, sp238);
    switch (D_807444FC) {
    case 0:
        mtx = arg0->unk14 + gCurrentPlayerIndex;
        break;
    case 1:
        mtx = arg0->unk18 + gCurrentPlayerIndex;
        break;
    }
    guMtxF2L(sp238, mtx);
    WRITE_GFX_PAIR(0xE7000000, 0);
    WRITE_GFX_PAIR(0xD9000000, 0);
    WRITE_GFX_PAIR(0xDA380000, osVirtualToPhysical(mtx));
    if (sp1D0 < (f32)((limit * 3) / 4)) {
        sp1AE = 1;
        sp1B0 = 0xFF;
    } else {
        sp1AE = 0;
        sp1B0 = ((sp1D0 - (f32)((limit * 3) / 4)) / ((f32)limit - (f32)((limit * 3) / 4))) * 255.0f;
        if (sp1B0 >= 0x100) {
            sp1B0 = 0xFF;
        }
        sp1B0 = 0xFF - sp1B0;
    }
    modelKongVisibilityCheck(arg0->unk4A, &sp1AE, &sp1B0);
    if (arg5 != 0 && arg0->unk5A == 0) {
        lightSampleColorAtPosition(arg0->unk0, arg0->unk4, arg0->unk8, 0, &sp1AD, &sp1AC, &sp1AB, arg6);
        scale = (f32)(u32)arg0->unk5C / 15.0f;
        sp1AD = (f32)(u32)sp1AD * scale;
        sp1AC = (f32)(u32)sp1AC * scale;
        sp1AB = (f32)(u32)sp1AB * scale;
    } else {
        sp1AD = sp1AC = sp1AB = 0xFF;
    }
    for (i = 0; i < arg0->unk20; i++) {
        texAnimFindNodeFrame((ModelSegmentOwner *)arg0, i, &sp1E8, &sp1E4, &sp1E3, &sp1E0);
        WRITE_GFX_PAIR(0xE7000000, 0);
        if (arg0->unk4E & 2) {
            if (sp1AE != 0) {
                gSPSetOtherMode(arg1++, G_SETOTHERMODE_L, 3, 29, 0x0C193078);
            } else {
                gSPSetOtherMode(arg1++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
            }
        } else if (arg0->unk4E & 1) {
            gSPSetOtherMode(arg1++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
        } else {
            gSPSetOtherMode(arg1++, G_SETOTHERMODE_L, 3, 29, 0x0C184240);
        }
        gSPSetOtherMode(arg1++, G_SETOTHERMODE_H, 20, 2, 0x100000);
        if ((arg0->unk4E & 1) || (arg0->unk4E & 2)) {
            WRITE_GFX_PAIR(0xD9FFFFFF, 0x210005);
        } else {
            WRITE_GFX_PAIR(0xD9FFFFFF, 0x210004);
        }
        gDPSetPrimColor(arg1++, 0, sp1E0, sp1AD, sp1AC, sp1AB, sp1B0);
        switch (sp1E3) {
        case 0:
            WRITE_GFX_PAIR(0xFC1197FF, 0xFFFFFE38);
            WRITE_GFX_PAIR(0xD7000002, 0xFFFFFFFF);
            if (D_807F6009 != 2 || sp1E8 != D_807F600C) {
                switch (arg0->unk46) {
                case 0:
                    gDPLoadTextureBlock_4b(arg1++, sp1E8 + 0x80000000, arg0->unk47, arg0->unk44, arg0->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    if (arg0->unk47 == 2) {
                        gDPSetTextureImage(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, arg0->unk34[i]);
                        gDPTileSync(arg1++); gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                        gDPLoadSync(arg1++);
                        gDPLoadTLUTCmd(arg1++, G_TX_LOADTILE, 15); gDPPipeSync(arg1++);
                        gDPSetTextureLUT(arg1++, G_TT_RGBA16);
                        sp1AF = 1;
                    }
                    break;
                case 1:
                    gDPLoadTextureBlock(arg1++, sp1E8 + 0x80000000, arg0->unk47, G_IM_SIZ_8b, arg0->unk44, arg0->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    if (arg0->unk47 == 2) {
                        gDPSetTextureImage(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, arg0->unk34[i]);
                        gDPTileSync(arg1++); gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
                        gDPLoadSync(arg1++);
                        gDPLoadTLUTCmd(arg1++, G_TX_LOADTILE, 255); gDPPipeSync(arg1++);
                        gDPSetTextureLUT(arg1++, G_TT_RGBA16);
                        sp1AF = 1;
                    }
                    break;
                case 2:
                    gDPLoadTextureBlock(arg1++, sp1E8 + 0x80000000, arg0->unk47, G_IM_SIZ_16b, arg0->unk44, arg0->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                case 3:
                    gDPLoadTextureBlock(arg1++, sp1E8 + 0x80000000, arg0->unk47, G_IM_SIZ_32b, arg0->unk44, arg0->unk45, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
                    break;
                }
            }
            D_807F600C = sp1E8;
            break;
        case 1:
            WRITE_GFX_PAIR(0xFC272C03, 0x1F1C93F8);
            WRITE_GFX_PAIR(0xD7000002, 0xFFFFFFFF);
            gSPSetOtherMode(arg1++, G_SETOTHERMODE_H, 16, 1, 0);
            gDPSetTextureImage(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sp1E8);
            gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadSync(arg1++);
            gDPLoadBlock(arg1++, G_TX_LOADTILE, 0, 0, ((arg0->unk44 * arg0->unk45 * 2) >> 1) - 1, CALC_DXT(arg0->unk44, 2));
            gDPSetTextureImage(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sp1E4);
            gDPTileSync(arg1++);
            gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x100, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
            gDPLoadSync(arg1++);
            gDPLoadBlock(arg1++, G_TX_LOADTILE, 0, 0, ((arg0->unk44 * arg0->unk45 * 2) >> 1) - 1, CALC_DXT(arg0->unk44, 2));
            gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg0->unk44 / 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
            gDPSetTileSize(arg1++, G_TX_RENDERTILE, 2, 2, ((arg0->unk44 - 1) << 2) + 2, ((arg0->unk45 - 1) << 2) + 2);
            gDPSetTile(arg1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg0->unk44 / 4, 0x100, 1, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
            gDPSetTileSize(arg1++, 1, 2, 2, ((arg0->unk44 - 1) << 2) + 2, ((arg0->unk45 - 1) << 2) + 2);
            D_807F600C = 0;
            break;
        }
        WRITE_GFX_PAIR(0x01004008, osVirtualToPhysical(arg0->unk1C + sp1B4));
        WRITE_GFX_PAIR(0x06000204, 0x406);
        sp1B4 += 4;
        D_807F6009 = 2;
    }
    WRITE_GFX_PAIR(0xD8380002, 0x40);
    WRITE_GFX_PAIR(0xE7000000, 0);
    gSPSetOtherMode(arg1++, G_SETOTHERMODE_H, 20, 2, 0);
    gSPSetOtherMode(arg1++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    if (sp1AF != 0) {
        gSPSetOtherMode(arg1++, G_SETOTHERMODE_H, 14, 2, 0);
    }
    gSPSetOtherMode(arg1++, G_SETOTHERMODE_L, 2, 1, 0);
    return arg1;
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

void modelKongVisibilityCheck(s16 arg0, u8 *arg1, s16 *arg2) {
    s32 hit = 0;
    PlayerControllerState *ctl;

    switch (arg0) {
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
        *arg1 = 0;
        if (*arg2 > 0x64) {
            *arg2 = 0x64;
        }
    }
}

typedef struct ModelSubObjectFlags {
    /* 0x00 */ u8 pad0[0x4E];
    /* 0x4E */ u8 unk4E;
} ModelSubObjectFlags;

void func_806398E4(s32 arg0, u8 arg1, u8 arg2) {
    ModelSubObjectFlags *obj;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    obj = D_807F6000[arg0].unk20;
    if (arg2 != 0) {
        obj->unk4E |= 1;
    } else {
        obj->unk4E &= ~1;
    }
    obj->unk4E &= ~2;
}

void texAnimUpdateNodes(ModelSegmentData *arg0) {
    s32 pad;
    s32 sp60;
    s32 sp5C;
    u8 sp5B;
    s16 sp58;
    ModelSegmentNode *node;
    s32 *dst;

    node = (ModelSegmentNode *)arg0->unkB8;
    if (node != NULL) {
        do {
            texAnimNodeUpdateBuffers(node, &sp60, &sp5C, &sp5B, &sp58);
            if (node->unk0[D_807444FC].unk0 != NULL) {
                node->unk0[D_807444FC].unk0->unk4 = sp60;
                if (sp5B == 0) {
                    dst = &node->unk0[D_807444FC].unk0->unk30;
                    *dst = (node->unk34 << 12) | 0xF2000000 | node->unk36;
                }
            }
            if (node->unk18[D_807444FC].unk0 != NULL) {
                node->unk18[D_807444FC].unk0->unk4 = sp60;
                if (sp5B == 0) {
                    dst = &node->unk18[D_807444FC].unk0->unk30;
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
            if (sp5B != 0) {
                if (node->unk0[D_807444FC].unk4 != NULL) {
                    node->unk0[D_807444FC].unk4->unk4 = sp5C;
                }
                if (node->unk18[D_807444FC].unk4 != NULL) {
                    node->unk18[D_807444FC].unk4->unk4 = sp5C;
                }
                if (node->unk0[D_807444FC].unk8 != NULL) {
                    *node->unk0[D_807444FC].unk8 = sp58 + 0xFA000000;
                }
                if (node->unk18[D_807444FC].unk8 != NULL) {
                    *node->unk18[D_807444FC].unk8 = sp58 + 0xFA000000;
                }
            }
            node->unk30 = gFrameCounter;
            node = node->unkD4;
        } while (node != NULL);
    }
}

void func_8066B0DC(void);

void texAnimFindNodeFrame(ModelSegmentOwner *arg0, s32 arg1, s32 *arg2, s32 *arg3, u8 *arg4, s16 *arg5) {
    ModelSegmentNode *node;
    s32 key;
    s32 found;

    node = arg0->unk50;
    if (node != NULL) {
        key = arg0->unk24[arg1];
        found = 0;
        if (node != NULL) {
            do {
                if (key == node->unk44) {
                    found = 1;
                } else {
                    node = node->unkD4;
                }
            } while (node != NULL && found == 0);
        }
        if (found != 0) {
            texAnimNodeUpdateBuffers(node, arg2, arg3, arg4, arg5);
            node->unk30 = gFrameCounter;
            return;
        }
        *arg4 = 0;
        *arg2 = key;
        return;
    }
    *arg4 = 0;
    *arg2 = arg0->unk24[arg1];
}


s32 texAnimNodeAdvance(ModelSegmentNode *, s32 *, s32 *);

void texAnimNodeUpdateBuffers(ModelSegmentNode *arg0, s32 *arg1, s32 *arg2, u8 *arg3, s16 *arg4) {
    s32 var_v1;
    s32 sp30;
    s32 sp2C;
    s32 temp_a3;
    s32 temp_a0;

    if (gFrameCounter == arg0->unk30) {
        var_v1 = 0;
    } else {
        var_v1 = (u8)texAnimNodeAdvance(arg0, &sp30, &sp2C);
    }
    if (var_v1 != 0 || arg0->unk3C == 0) {
        temp_a3 = arg0->unk3C;
        if (arg0->unk4A != 0) {
            temp_a0 = arg0->unk40;
            if (temp_a0 == 0 || arg0->unk49 != 0) {
                if (temp_a3 != 0) {
                    assetFreeBuffer((void *)temp_a3, 0xFCB, 7);
                }
                if (arg0->unkD0 != 0) {
                    func_8066B0DC();
                }
                arg0->unk3C = (s32)assetLoad(7, arg0->unk5C[sp30], 0, 0);
                temp_a0 = arg0->unk40;
                if (temp_a0 != 0) {
                    assetFreeBuffer((void *)temp_a0, 0xFCE, 7);
                }
                if (arg0->unkD0 != 0) {
                    func_8066B0DC();
                }
                arg0->unk40 = (s32)assetLoad(7, arg0->unk5C[sp2C], 0, 0);
            } else {
                if (temp_a3 != 0) {
                    assetFreeBuffer((void *)temp_a3, 0xFD5, 7);
                }
                temp_a0 = arg0->unk40;
                arg0->unk3C = temp_a0;
                if (arg0->unkD0 != 0) {
                    func_8066B0DC();
                }
                arg0->unk40 = (s32)assetLoad(7, arg0->unk5C[sp2C], 0, 0);
            }
        } else {
            if (temp_a3 != 0) {
                assetFreeBuffer((void *)temp_a3, 0xFDF, 7);
            }
            if (arg0->unkD0 != 0) {
                func_8066B0DC();
            }
            arg0->unk3C = (s32)assetLoad(7, arg0->unk5C[sp30], 0, 0);
        }
    }
    arg0->unk49 = 0;
    *arg3 = arg0->unk4A;
    if (arg0->unk4A != 0) {
        *arg4 = (s16)(((f32)arg0->unk50 / (f32)arg0->unk4C) * 255.0f);
    }
    *arg1 = arg0->unk3C;
    *arg2 = arg0->unk40;
}

s32 texAnimNodeAdvance(ModelSegmentNode *arg0, s32 *arg1, s32 *arg2) {
    s32 result;

    result = 0;
    switch (arg0->unk48) {
        case 1:
            arg0->unk50 += 1;
            if (arg0->unk50 == arg0->unk4C) {
                arg0->unk50 = 0;
                arg0->unk54 += 1;
                if (arg0->unk54 == arg0->unk58) {
                    arg0->unk54 = 0;
                }
                result = 1;
            }
            break;
        case 0:
            if (arg0->unk49 != 0) {
                result = 1;
            }
            break;
        default:
            break;
    }
    *arg1 = arg0->unk54;
    if (arg0->unk54 + 1 == arg0->unk58) {
        *arg2 = 0;
    } else {
        *arg2 = arg0->unk54 + 1U;
    }
    return result;
}

typedef struct SpriteDisplayNode {
    /* 0x00 */ u32 key;
    /* 0x04 */ u8 pad4[8];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 pad30[4];
    /* 0x34 */ struct SpriteDisplayNode *next;
} SpriteDisplayNode;

s32 func_80611E60(s32);
f32 distance3D(f32, f32, f32, f32, f32, f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);

void modelCalcFacingAngles(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 *arg6, f32 *arg7, f32 *arg8, u8 arg9) {
    f32 len;
    s16 angle;
    f32 dx;
    f32 dz;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s16 angle2;
    s32 t;

    if (arg9 == 0) {
        dx = arg3 - arg0;
        dz = arg5 - arg2;
        len = sqrtf(dx * dx + dz * dz);
        if ((f64)len < 1.0) {
            len = 1.0f;
        }
        if (arg0 <= arg3 && arg2 <= arg5) {
            angle = (s16)(func_80611E60((s32)(((f64)dx * 65535.9) / (f64)len)) >> 4);
        }
        if (arg0 <= arg3 && arg5 < arg2) {
            angle = (s16)((func_80611E60((s32)(((f64)(arg2 - arg5) * 65535.9) / (f64)len)) >> 4) + 0x400);
        }
        if (arg3 < arg0 && arg5 < arg2) {
            angle = (s16)((func_80611E60((s32)(((f64)(arg0 - arg3) * 65535.9) / (f64)len)) >> 4) + 0x800);
        }
        if (arg3 < arg0 && arg2 <= arg5) {
            angle = (s16)((func_80611E60((s32)(((f64)dz * 65535.9) / (f64)len)) >> 4) + 0xC00);
        }
        *arg8 = 0.0f;
        *arg6 = 0.0f;
        *arg7 = (f32)(((f64)angle / 4095.0) * 360.0);
    } else {
        len = distance3D(arg3, arg4, arg5, arg0, arg1, arg2);
        if ((f64)len < 0.1) {
            len = 1.0f;
        }
        dz = (arg4 - arg1) / len;
        if (dz > 0.0f) {
            dx = dz;
        } else {
            dx = -dz;
        }
        t = func_80611E60((s32)(f32)(s32)((f64)dx * 65536.0)) >> 4;
        angle2 = t;
        if (dz >= 0.0f) {
            angle2 = 0xFFF - angle2;
        }
        *arg6 = (f32)(((f64)angle2 / 4095.0) * 360.0);
        *arg7 = mathAngleBetweenPointsRad(arg3, arg5, arg0, arg2) * 57.295776f;
        *arg8 = 0.0f;
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

typedef struct ModelSpriteSourceList {
    /* 0x00 */ ModelSpriteSource *data;
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ struct ModelSpriteSourceList *next;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ u8 unk24;
} ModelSpriteSourceList;

SpriteDisplayNode *spriteListInsertByDepth(SpriteDisplayNode *, SpriteDisplayNode *);


SpriteDisplayNode *spriteListBuildDisplayChain(ModelSpriteSourceList *arg0, ModelSpriteSourceList *arg1, f32 arg2, f32 arg3, f32 arg4) {
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
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    s16 r2;

    result = NULL;
    second = 0;
    if (arg0 == NULL) {
        arg0 = arg1;
        second = 1;
    }
    if (arg0 != NULL) {
        do {
            switch (arg0->unk24) {
            case 2:
                d = arg0->data;
                if (d->unk4E & 0x10) {
                    tgt = NULL;
                } else {
                    x = d->unk0;
                    y = d->unk4 - d->unk10;
                    z = d->unk8;
                    tgt = d->unk54;
                    link = d->unk50;
                    modelCalcFacingAngles(x, y, z, arg2, arg3, arg4, &sp9C, &sp98, &sp94, 0);
                    scale = d->unkC;
                }
                break;
            case 1:
                d1 = arg0->data;
                tgt = d1->unkBC;
                link = d1->unkB8;
                x = d1->unk0;
                z = d1->unk8;
                y = d1->unk4 - d1->unk1C;
                sp98 = d1->unk14;
                scale = d1->unkC;
                break;
            default:
                tgt = NULL;
                break;
            }
            if (tgt != NULL) {
                r = tgt->unk2C;
                d2 = (arg2 - x) * (arg2 - x) + (arg3 - y) * (arg3 - y) + (arg4 - z) * (arg4 - z);
                if (d2 < (f32)(r * r)) {
                    r2 = tgt->unk2A;
                    if (d2 < (f32)(r2 * r2)) {
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
                        tgt->unk26 = (s16)(s32)sp98;
                        tgt->unk26 = (s16)(s32)((f64)tgt->unk26 + ((f64)(link->unk54 * 0x168 / link->unk58) + ((f64)link->unk50 * 360.0 / (f64)link->unk58) / (f64)link->unk4C));
                    } else {
                        tgt->unk26 = (s16)(s32)sp98;
                    }
                    tgt->unk14 = x;
                    tgt->unk26 = tgt->unk26 + tgt->unk28;
                    tgt->unk18 = y;
                    tgt->unk1C = z;
                    tgt->next = NULL;
                    tgt->unk10 = (s16)(s32)((f32)tgt->unkC * scale);
                    tgt->unk12 = (s16)(s32)((f32)tgt->unkE * scale);
                    result = spriteListInsertByDepth(result, tgt);
                }
            }
            arg0 = arg0->next;
            if (arg0 == NULL && second == 0) {
                arg0 = arg1;
                second = 1;
            }
        } while (arg0 != NULL);
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

void func_8063A8C4(s16 arg0, u8 arg1, f32 arg2) {
    u8 *obj;
    f32 *p;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    obj = D_807F6000[arg0].unk20;
    switch (D_807F6000[arg0].unk86) {
    case 2:
        p = *(f32 **)(obj + 0x54);
        break;
    case 1:
        p = *(f32 **)(obj + 0xBC);
        break;
    }
    if (p != NULL) {
        p[1] = arg2;
    }
}

typedef struct SpriteGfxNode {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u8 pad24[2];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[7];
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ struct SpriteGfxNode *unk34;
} SpriteGfxNode;

u32 osVirtualToPhysical(void *);

Gfx *spriteListRender(Gfx *arg0, SpriteGfxNode *arg1) {
    s32 lastTex;
    Vtx *vtxs;
    Mtx *mtxs;
    s32 n;
    SpriteGfxNode *p;
    s32 vtxIdx;
    s32 mtxIdx;
    f32 accum[4][4];
    f32 tmp[4][4];
    s32 flag;

    lastTex = 0;
    vtxIdx = 0;
    mtxIdx = 0;
    flag = 1;

    if (arg1 != NULL) {
        gDPPipeSync(arg0++);
        gDPSetCycleType(arg0++, G_CYC_1CYCLE);
        gSPClearGeometryMode(arg0++, -1);
        gSPSetGeometryMode(arg0++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
        gSPTexture(arg0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPSetRenderMode(arg0++, G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2);
        gDPSetCombineMode(arg0++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
        n = 0;
        p = arg1;
        if (p != NULL) {
            do {
                p = p->unk34;
                n++;
            } while (p != NULL);
        }
        vtxs = heapAlloc(n << 6);
        heapFreeDeferred(vtxs);
        mtxs = heapAlloc(n << 6);
        heapFreeDeferred(mtxs);
    }
    if (arg1 != NULL) {
        do {
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, arg1->unk2F);
            if (arg1->unk30 != 0 && flag == 0) {
                gSPSetGeometryMode(arg0++, G_ZBUFFER);
                gDPSetRenderMode(arg0++, G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2);
                flag = 1;
            }
            if (arg1->unk30 == 0 && flag != 0) {
                gSPClearGeometryMode(arg0++, G_ZBUFFER);
                gDPSetRenderMode(arg0++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
                flag = 0;
            }
            if (arg1->unk0 != lastTex) {
                switch (arg1->unkB) {
                case 0:
                    gDPLoadTextureBlock_4b(arg0++, arg1->unk0 + 0x80000000, arg1->unkA, arg1->unk8, arg1->unk9, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                case 1:
                    gDPLoadTextureBlock(arg0++, arg1->unk0 + 0x80000000, arg1->unkA, G_IM_SIZ_8b, arg1->unk8, arg1->unk9, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                case 2:
                    gDPLoadTextureBlock(arg0++, arg1->unk0 + 0x80000000, arg1->unkA, G_IM_SIZ_16b, arg1->unk8, arg1->unk9, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                }
                lastTex = arg1->unk0;
            }
            vtxs[vtxIdx + 0].v.tc[0] = 0;
            vtxs[vtxIdx + 0].v.tc[1] = 0;
            vtxs[vtxIdx + 1].v.tc[0] = arg1->unk8 << 5;
            vtxs[vtxIdx + 1].v.tc[1] = 0;
            vtxs[vtxIdx + 2].v.tc[0] = arg1->unk8 << 5;
            vtxs[vtxIdx + 2].v.tc[1] = arg1->unk9 << 5;
            vtxs[vtxIdx + 3].v.tc[0] = 0;
            vtxs[vtxIdx + 3].v.tc[1] = arg1->unk9 << 5;
            vtxs[vtxIdx + 0].v.ob[1] = 0;
            vtxs[vtxIdx + 1].v.ob[1] = 0;
            vtxs[vtxIdx + 2].v.ob[1] = 0;
            vtxs[vtxIdx + 3].v.ob[1] = 0;
            vtxs[vtxIdx + 0].v.ob[0] = -arg1->unk10;
            vtxs[vtxIdx + 0].v.ob[2] = -arg1->unk12;
            vtxs[vtxIdx + 1].v.ob[0] = arg1->unk10;
            vtxs[vtxIdx + 1].v.ob[2] = -arg1->unk12;
            vtxs[vtxIdx + 2].v.ob[0] = arg1->unk10;
            vtxs[vtxIdx + 2].v.ob[2] = arg1->unk12;
            vtxs[vtxIdx + 3].v.ob[0] = -arg1->unk10;
            vtxs[vtxIdx + 3].v.ob[2] = arg1->unk12;
            guScaleF(accum, arg1->unk4, 1.0f, arg1->unk4);
            guRotateF(tmp, (f32)arg1->unk26, 0.0f, 1.0f, 0.0f);
            guMtxCatF(accum, tmp, accum);
            if (arg1->unk22 < 0x3E8) {
                guRotateF(tmp, -((f64)arg1->unk20 / 4095.0 * 360.0), 0.0f, 1.0f, 0.0f);
                guMtxCatF(accum, tmp, accum);
            }
            guRotateF(tmp, 90.0 - (f64)arg1->unk22 / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
            guMtxCatF(accum, tmp, accum);
            if (arg1->unk22 < 0x3E8) {
                guRotateF(tmp, (f64)arg1->unk20 / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
                guMtxCatF(accum, tmp, accum);
            }
            guTranslateF(tmp, arg1->unk14, arg1->unk18, arg1->unk1C);
            guMtxCatF(accum, tmp, accum);
            guMtxF2L(accum, &mtxs[mtxIdx]);
            gSPMatrix(arg0++, osVirtualToPhysical(&mtxs[mtxIdx]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
            mtxIdx++;
            gSPVertex(arg0++, osVirtualToPhysical(&vtxs[vtxIdx]), 4, 0);
            gSP2Triangles(arg0++, 0, 1, 2, 0, 0, 2, 3, 0);
            gSPPopMatrix(arg0++, G_MTX_MODELVIEW);
            vtxIdx += 4;
            arg1 = arg1->unk34;
        } while (arg1 != NULL);
    }
    gDPPipeSync(arg0++);
    return arg0;
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
void csStateTickTimers(s32);
void csStateUpdate(s32, s16);

#ifdef NON_MATCHING
typedef struct ModelPendingEntry {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0xE];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ u8 unk24;
} ModelPendingEntry;

extern u8 D_807F7140;

typedef struct ModelPendingPlayerView { u8 u0; u8 pad1[3]; u8 *u4; u8 pad8[0x21C-8]; f32 x; f32 y; f32 z; u8 padE[0x2F0-0x228]; } ModelPendingPlayerView;
void modelPendingQueueInsert(ModelPendingEntry *arg0, u8 arg1) {
    u8 *obj;
    u8 allow;
    s32 pad1;
    s32 pad2;
    s16 idx;
    s32 pad3;
    s32 pad4;
    s32 pad5;
    u8 *tbl;
    u8 *newv;
    s32 i;
    ModelPendingQueueEntry *e;
    int nv;
    u8 *p;
    u8 flag;
    f32 *px;
    f32 *py;
    f32 *pz;
    f32 best;

    if (0) { csStateTickTimers((s32)&idx); csStateTickTimers((s32)&tbl); } allow = 1; if (arg0->unk24 == 1) { idx = hashTableLookup(arg0->unk1E); tbl = (u8 *)D_807F6000; obj = ((ModelSlot *)tbl)[idx].unk7C; if (obj != NULL) {
            switch (obj[0x54]) {
            case 2:
                allow = 0;
                break;
            case 0:
                allow = arg1;
                break;
            case 4:
                newv = (u8 *)gPlayerSlots;  // FAKE: defines newv so the dead tests below read an assigned local
                if (newv && newv) {}  // FAKE: fk
                if (newv == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (newv != 0) {}  // FAKE: fk
                allow = arg1;
            case 3:
            case 6:
                best = 1e8f;
                for (i = 0; i < D_80750AB4; i = (u8)(i + 1)) {
                    
                    if (tbl && tbl) {}  // FAKE: fk
                    if (((ModelPendingPlayerView *)gPlayerSlots)[i].u0 != 0) {
                        if (obj == 0) {}  // FAKE: fk
                        if (arg0 && arg0) {}  // FAKE: fk
                        if (arg0 != 0) {}  // FAKE: fk
                        if (obj[0x54] == 6) {
                            px = (f32 *)(((ModelPendingPlayerView *)gPlayerSlots)[i].u4 + 0x7C);
                            py = (f32 *)(((ModelPendingPlayerView *)gPlayerSlots)[i].u4 + 0x80);
                            newv = ((ModelPendingPlayerView *)gPlayerSlots)[i].u4 + 0x84;
                            pz = (f32 *)newv;
                        } else {
                            px = (f32 *)(i * 0x2F0 + (u8 *)gPlayerSlots + 0x21C);
                            if (!arg0) {
                            }
                            if (tbl && tbl) {}  // FAKE: fk
                            if (i && i) {}  // FAKE: fk
                            py = (f32 *)(i * 0x2F0 + (u8 *)gPlayerSlots + 0x220);
                            pz = (f32 *)(i * 0x2F0 + (u8 *)gPlayerSlots + 0x224);
                        }
        if (px) {} // FAKE: x
                        if (gPlayerSlots != 0) {}  // FAKE: fk
                        if ((*pz - arg0->unkC) * (*pz - arg0->unkC) + ((*px - arg0->unk4) * (*px - arg0->unk4) + (*py - arg0->unk8) * (*py - arg0->unk8)) < (0, best)) {
                            if (((ModelPendingPlayerView *)gPlayerSlots)[i].u4 != 0) {}  // FAKE: fk
                            if (px && px) {}  // FAKE: fk
                            best = (*pz - arg0->unkC) * (*pz - arg0->unkC) + ((*px - arg0->unk4) * (*px - arg0->unk4) + (*py - arg0->unk8) * (*py - arg0->unk8));
                        }
                        if (py && py) {}  // FAKE: fk
                        if (tbl && tbl) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    }
                    
                }
                allow &= best < (f32)*(s32 *)(obj + 0x58);
                break;
            case 5:
                if (D_807F6028 == 0x14) return;
                allow = 0;
                D_807F6030[D_807F6028].id = arg0->unk1E;
                D_807F6030[D_807F6028].key = *(s32 *)(obj + 0x58);
                D_807F6030[D_807F6028++].done = 0;
                break;
            }
            if (allow != 0) {
                D_807F7140++;
                if (D_807F60A8 != 0x46) {
                    D_807F60B0[D_807F60A8] = *(s16 *)(tbl + 0x8A + idx * 0x90);
                    D_807F60A8++;
                    csStateTickTimers((s32)obj);
                    csStateUpdate((s32)obj, arg0->unk1E);
                }
            }
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/modelPendingQueueInsert.s")
#endif

void modelPendingEntriesProcess(void) {
    u8 found;
    s32 i;
    s32 slot;
    s32 obj;
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
                        obj = (s32)D_807F6000[slot].unk7C;
                        if (D_807F60A8 == 0x46) {
                            return;
                        }
                        D_807F60B0[D_807F60A8] = *(s16 *)((u8 *)D_807F6000 + slot * 0x90 + 0x8A);
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

typedef struct ModelSlotSerializeView {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 *unk20;
    /* 0x24 */ u8 pad24[0x58];
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 pad88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} ModelSlotSerializeView; /* 0x90 */

extern u8 *D_807F6010;
extern u8 gCsVarsDirty[];
extern u8 D_807F6902;
s32 actorListGetSerializedSize(void);
void actorListSerialize(void *);

#define MODEL_SLOT_SERIALIZE_ENTRY ((ModelSlotSerializeView *)((u8 *)D_807F6000 + i * 0x90))

void modelSlotSerializeAll(u8 **arg0, s32 *arg1) {
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
    size = D_80747D70 * 0x30;
    size += 4;
    size += 4; // FAKE: split +8 keeps the product written into size's reg (as1 would fold `move; addiu` otherwise)
    p = gCsVarsDirty; do { // LAYOUT: statement on the do line keeps the lui/addiu hoist order
        if (*p) {
            size += 0x24;
            count++;
        }
        p++;
    } while (p < &D_807F6902);
    size += actorListGetSerializedSize();
    D_807F6010 = heapAlloc(size);
    *(s32 *)D_807F6010 = D_80747D70;
    out = (ModelSlotSerializedOut *)(D_807F6010 + 4);
    for (i = 0; i < D_80747D70; i++, out++) {
        out->unk0 = MODEL_SLOT_SERIALIZE_ENTRY->unk0;
        out->unk4 = MODEL_SLOT_SERIALIZE_ENTRY->unk4;
        out->unk8 = MODEL_SLOT_SERIALIZE_ENTRY->unk8;
        out->unkC = MODEL_SLOT_SERIALIZE_ENTRY->unkC;
        out->unk18 = MODEL_SLOT_SERIALIZE_ENTRY->unk10;
        out->unk1C = MODEL_SLOT_SERIALIZE_ENTRY->unk14;
        out->unk20 = MODEL_SLOT_SERIALIZE_ENTRY->unk18;
        out->unk28 = MODEL_SLOT_SERIALIZE_ENTRY->unk84;
        out->unk2C = MODEL_SLOT_SERIALIZE_ENTRY->unk86;
        out->unk24 = MODEL_SLOT_SERIALIZE_ENTRY->unk1C;
        out->unk2A = MODEL_SLOT_SERIALIZE_ENTRY->unk8A;
        switch (out->unk2C) {
        case 2:
            out->unk2F = MODEL_SLOT_SERIALIZE_ENTRY->unk20[0x4E];
            out->unk2E = MODEL_SLOT_SERIALIZE_ENTRY->unk20[0x5B];
            break;
        case 1:
            out->unk2F = 0;
            out->unk2E = MODEL_SLOT_SERIALIZE_ENTRY->unk20[0xC3];
            break;
        }
    }
    *(s32 *)out = count;
    dst = (u8 *)out + 4;
    for (i = 0, p = gCsVarsDirty; i != 0x212; i++, p++) {
        if (*p != 0) {
            *(s32 *)dst = i;
            memcpy(dst + 4, (u8 *)D_807F6000[hashTableLookup(gCsModelIds[i])].unk7C + 0x14, 0x20);
            dst += 0x24;
        }
    }
    actorListSerialize(dst);
    *arg0 = D_807F6010;
    if (!gCsVarsDirty) {
    }
    *arg1 = size;
}

#undef MODEL_SLOT_SERIALIZE_ENTRY

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

u32 modelSlotDataSize(s16);
void modelSlotGetNodeScrollSpeed(s32, s16, s16 *, s16 *);
void modelSlotGetNodeAnimMode(s32, s16, u8 *);
void mapOffsetSlotsGetTargets(f32 *);
void effectNodeCopyValues(f32 *);

#define MODEL_SLOT_PACKED_ENTRY(i) ((ModelSlotPackView *)((u8 *)D_807F6000 + (i) * 0x90))

void modelSlotsPackRecords(u8 **arg0, s32 *arg1) {
    s32 count = 0;
    s32 i;
    s32 pad;
    u8 *buf = NULL;
    u8 *rec;
    u8 *cur;
    s32 size = 0;
    u8 *p;
    s32 j;

    for (i = 0; i < D_80747D70; i++) {
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
        for (i = 0; i < D_80747D70; i++) {
            if (MODEL_SLOT_PACKED_ENTRY(i)->unk7C != NULL) {
                if ((MODEL_SLOT_PACKED_ENTRY(i)->unk24[0x3A] != 0 || (MODEL_SLOT_PACKED_ENTRY(i)->unk7C[0x9B] & 1)) && !(MODEL_SLOT_PACKED_ENTRY(i)->unk7C[0x9B] & 2)) {
                    rec = cur;
                    p = cur;
                    *(s16 *)p = MODEL_SLOT_PACKED_ENTRY(i)->unk8A;
                    memcpy(p + 0xCC, MODEL_SLOT_PACKED_ENTRY(i)->unk7C, 0x9C);
                    if (MODEL_SLOT_PACKED_ENTRY(i)->unk78 != NULL) {
                        memcpy(p + 4, (u8 *)MODEL_SLOT_PACKED_ENTRY(i)->unk78 + 8, 0xC8);
                        cur[0x250] = modelSlotDataSize(i) >> 6;
                        memcpy(p + 0x254, *MODEL_SLOT_PACKED_ENTRY(i)->unk78, modelSlotDataSize(i));
                    } else {
                        cur[0x250] = 0;
                    }
                    for (j = 1; j != 5; j++) {
                        modelSlotGetNodeScrollSpeed(MODEL_SLOT_PACKED_ENTRY(i)->unk88, j, (s16 *)(p + 0x232 + j * 6), (s16 *)(p + 0x234 + j * 6));
                        modelSlotGetNodeAnimMode(MODEL_SLOT_PACKED_ENTRY(i)->unk88, j, p + 0x236 + j * 6);
                    }
                    mapOffsetSlotsGetTargets((f32 *)(p + 0x168));
                    effectNodeCopyValues((f32 *)(p + 0x1B8));
                    cur += rec[0x250] * 0x40;
                    cur += 0x254;
                }
            }
        }
    }
    *arg1 = count;
    *arg0 = buf;
}

void modelRecordFindAndSet(u8 *arg0, s32 arg1, s16 arg2, s16 arg3) {
    s32 found = 0;
    s32 i = 0;

    if (arg1 > 0) {
        do {
            if (*(s16 *)arg0 == arg2) {
                found = 1;
            } else {
                i++;
                arg0 += 0x254 + arg0[0x250] * 0x40;
            }
        } while (found == 0 && i < arg1);
    }
    if (found != 0) {
        arg0[0x117] = arg3;
        arg0[0x120] = 1;
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

void mapOffsetSlotsSetValues(f32 *);
void effectNodeSetValues(f32 *);

void modelSlotsApplyRecords(u8 *arg0, s32 arg1) {
    s32 k;
    s32 off;
    s32 j;
    s16 id;
    s16 idx;
    u8 tmp[0x14];
    ModelSlotStateSnapshot snap;
    s32 pad[2];

    for (k = 0; k < arg1; k++) {
        id = gCsModelIds[*(s16 *)arg0];
        idx = hashTableLookup(id);
        memcpy(&snap, MODEL_SLOT_PACKED_ENTRY(idx)->unk7C, 0x9C);
        memcpy(MODEL_SLOT_PACKED_ENTRY(idx)->unk7C, arg0 + 0xCC, 0x9C);
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
                memcpy((u8 *)MODEL_SLOT_PACKED_ENTRY(idx)->unk78 + off + 8, arg0 + 4 + off, 0x14);
                *(u32 *)((u8 *)MODEL_SLOT_PACKED_ENTRY(idx)->unk78 + off + 8) = *(u32 *)tmp;
            }
            modelSlotCopyData(arg0 + 0x254, idx);
        }
        for (j = 1; j != 5; j++) {
            modelSlotSetNodeScrollSpeed(id, j, *(s16 *)(arg0 + 0x232 + j * 6), *(s16 *)(arg0 + 0x234 + j * 6));
            modelSlotSetNodeAnimMode(id, j, arg0[0x236 + j * 6]);
        }
        mapOffsetSlotsSetValues((f32 *)(arg0 + 0x168));
        effectNodeSetValues((f32 *)(arg0 + 0x1B8));
        arg0 += arg0[0x250] * 0x40;
        arg0 += 0x254;
    }
}

void modelSlotOrFlags(s32 arg0, u8 arg1) {
    ((u8 *)D_807F6000[hashTableLookup(gCsModelIds[arg0])].unk20)[0x4E] |= arg1;
}

void modelSlotClearFlags(s32 arg0, u8 arg1) {
    ((u8 *)D_807F6000[hashTableLookup(gCsModelIds[arg0])].unk20)[0x4E] &= ~arg1;
}

typedef struct ModelSlotStateSub {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 pad61[3];
    /* 0x64 */ s16 unk64;
} ModelSlotStateSub;

s32 func_8063C2A8(s16 arg0) {
    s16 idx = hashTableLookup(arg0);
    ModelSlotStateSub *sub = D_807F6000[idx].unk7C;

    if (sub != 0) {
        if (sub->unk60 == 1 && sub->unk64 == 0) {
            return 0;
        }
        return 1;
    }
    return 1;
}

s16 modelSlotGetType(s16 arg0) {
    s16 idx = hashTableLookup(arg0);

    if (idx == -1) {
        return -1;
    }
    return D_807F6000[idx].unk84;
}

