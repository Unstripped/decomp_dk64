#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern s32 D_8076A0A8;
extern u8 D_8074E77C[];

void gridFreeAllNodeLists(void);
void func_806F4778(void);

void func_806F4750(void) {
    gridFreeAllNodeLists();
    func_806F4778();
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} F9N3_FloatTableEntry;

extern F9N3_FloatTableEntry D_807FD740[];
extern s32 D_807FD780[];

struct F9F1_Node;
struct F9A_LinkedNode;

typedef struct F94A_Node {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 padF;
    s16 unk10;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 pad15[3];
    struct F94A_Node *unk18;
} F94A_Node;

typedef struct {
    u8 pad0[0x28];
    u16 unk28;
    s16 unk2A;
    u8 pad2C[4];
} F94A_Entry;

typedef struct {
    s16 unk0;
    u8 pad2[0xA];
    s16 unkC;
    u8 padE[6];
} F94A_TypeEntry;

extern s16 D_80753EF0;
extern struct F9F1_Node **D_80754244;
extern struct F9N5_QueueSlot *D_80754240;
extern u16 D_807F9450;
extern u16 D_807F9452;
extern u16 D_807F9454;
extern u16 D_807F9456;
extern s32 D_807FBB64;
extern s16 D_807FD720;
extern s16 D_807FD722;
extern s16 D_807FD724;
extern s16 D_807FD726;
extern s16 D_807FD728;
extern struct F9F1_Node *D_807FD72C;
extern struct F9A_LinkedNode *D_807FD730;
extern u8 D_807FD738;
extern u8 D_807FD798;
void *heapAlloc(s32);
void heapClearBlock(void *);
void heapFree(void *);
void *memcpy(void *, const void *, unsigned int);
u16 modelTypeCountBeforeMap(u8);
s32 modelTypeIsCounted(u16);
void modelAssetGetSubtables(u8 *, u8 **, u8 **);
s32 modelSlotFindByType(s32, s32 *, f32 *, f32 *, f32 *, s16 *, s16 *);
void *assetLoad(s32, u32, u8, u8);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);
void slotQueueInit(s32);

void func_806F4778(void) {
    s32 cookie;
    s32 found;
    f32 posX;
    f32 posY;
    f32 posZ;
    s16 modelId;
    s16 type;
    F94A_Node *head;
    F94A_TypeEntry *typeEntry;
    F94A_Node *node;
    F94A_Node *tail;
    F94A_Node *copy;
    s16 zlo;
    s32 cellIdx;
    s32 xi;
    s32 zi;
    s32 i;
    F94A_Entry *p;
    s32 idx;
    u8 *asset;
    u8 *sub;
    u8 *unusedOut;
    s32 entryCount;
    F94A_Entry *entries;
    u16 baseCount;
    u16 count;
    s16 sp66;
    s16 pad66;

    tail = NULL;
    head = NULL;
    entryCount = 0;
    D_807FD738 = 0;
    if (D_807FBB64 & 0x10000) {
        D_80754240 = heapAlloc(0x4B0);
        heapClearBlock(D_80754240);
    } else {
        D_80754240 = NULL;
    }
    baseCount = modelTypeCountBeforeMap(D_8076A0A8);
    asset = assetLoad(9, D_8076A0A8, 1, 1);
    if (asset != NULL) {
        modelAssetGetSubtables(asset, &sub, &unusedOut);
        entryCount = *(s32 *) sub;
        entries = (F94A_Entry *) (sub + 4);
    }
    D_807FD726 = 0;
    D_807FD728 = 0;
    D_807FD730 = NULL;
    D_807FD72C = NULL;
    for (i = 0; i < D_807FC928; i++) {
        D_807FD740[i].unk0 = 0.0f;
        D_807FD740[i].unk4 = 0.0f;
        D_807FD740[i].unk8 = 0.0f;
        D_807FD740[i].unkC = 0.0f;
        D_807FD780[i] = 0;
    }
    D_807FD798 = 0;
    slotQueueInit(1);
    typeEntry = (F94A_TypeEntry *) &D_80753EF0;
    for (i = 0; i < 0x2AU; i++) {
        type = typeEntry->unk0;
        cookie = 0;
        if (modelSlotFindByType(type, &cookie, &posX, &posY, &posZ, &modelId, &sp66) != 0) {
            do {
                node = heapAlloc(0x1C);
                node->unk8 = posX;
                node->unkA = posY;
                node->unkC = posZ;
                node->unk0 = modelId;
                node->unk4 = typeEntry->unkC;
                node->unk2 = type;
                node->unkE = 0;
                node->unk10 = 0;
                node->unk12 = 1;
                node->unk13 = 0;
                node->unk14 = i;
                if (modelTypeIsCounted(typeEntry->unk0) != 0) {
                    found = 0;
                    idx = 0;
                    count = 0;
                    while (found == 0 && idx < entryCount) {
                        if (sp66 == entries[idx].unk2A) {
                            found = 1;
                        } else {
                            idx++;
                        }
                        if (found == 0 && modelTypeIsCounted(entries[idx - 1].unk28) != 0) {
                            count++;
                        }
                    }
                    if (found != 0) {
                        node->unk6 = baseCount + count;
                    } else {
                        node->unk6 = -1;
                    }
                } else {
                    node->unk6 = -1;
                }
                node->unk18 = NULL;
                if (tail != NULL) {
                    tail->unk18 = node;
                } else {
                    head = node;
                }
                tail = node;
            } while (modelSlotFindByType(type, &cookie, &posX, &posY, &posZ, &modelId, &sp66) != 0);
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
            ((F94A_Node **) D_80754244)[cellIdx] = NULL;
            tail = NULL;
            for (node = head; node != NULL; node = node->unk18) {
                if (node->unk8 >= (s16) (xi * 500) && node->unk8 < (s16) (xi * 500 + 500)) {
                    zlo = zi * 500;
                    if (node->unkC >= zlo && node->unkC < (s16) (zi * 500 + 500)) {
                        copy = heapAlloc(0x1C);
                        memcpy(copy, node, 0x1C);
                        copy->unk18 = NULL;
                        if (tail != NULL) {
                            tail->unk18 = copy;
                        } else {
                            ((F94A_Node **) D_80754244)[cellIdx] = copy;
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
        head = node->unk18;
        heapFree(node);
    }
    if (entryCount != 0) {
        assetSetImmediateFree();
        assetFreeBuffer(asset, 0x1C0, 0x14);
    }
}

void func_806F4D70(u8 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    unsigned short temp_t6;
    F9N3_FloatTableEntry *temp_v0;
    f32 new_var;

    temp_t6 = arg0;
    temp_v0 = &D_807FD740[temp_t6];
    temp_v0->unk0 = arg1;
    new_var = arg4;
    temp_v0->unk4 = arg2;
    temp_v0->unk8 = arg3;
    temp_v0->unkC = new_var;
    D_807FD780[temp_t6] = 0;
}

typedef struct F9A_PositionNode {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    struct F9A_PositionNode *next;
} F9A_PositionNode;

void heapFreeDeferred(void *);

void func_806F4DC0(u8 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    F9A_PositionNode **var_v1;
    F9A_PositionNode *var_v0;
    F9A_PositionNode *temp_v0;

    var_v1 = (F9A_PositionNode **) &D_807FD780[arg0];
    while (*var_v1 != NULL) {
        var_v1 = &(*var_v1)->next;
    }
    temp_v0 = heapAlloc(0x14);
    *var_v1 = temp_v0;
    heapClearBlock(temp_v0);
    (*var_v1)->unk0 = arg1;
    (*var_v1)->unk4 = arg2;
    (*var_v1)->unk8 = arg3;
    (*var_v1)->unkC = arg4;
    heapFreeDeferred(*var_v1);
}


s32 func_806F4E74(s16 arg0) {
    s16 *var_a1;
    s32 var_v0;
    s32 var_v1;

    var_v1 = 0;
    var_v0 = 0;
    var_a1 = &D_80753EF0;
    do {
        if (arg0 == *var_a1) {
            var_v0 = 1;
        } else {
            var_v1++;
            var_a1 = (s16 *) ((u8 *) var_a1 + 0x14);
        }
    } while (var_v0 == 0);
    return var_v1;
}


s32 gridCoordsToIndex(f32 arg0, f32 arg1) {
    s32 temp_ft1;
    s32 temp_ft3;

    temp_ft3 = (s32) (arg0 / 500.0f);
    temp_ft1 = (s32) (arg1 / 500.0f);
    if ((D_807FD722 < temp_ft3) || (D_807FD724 < temp_ft1) || (arg0 < 0.0f) || (arg1 < 0.0f)) {
        return -1;
    }
    return (D_807FD722 * temp_ft1) + temp_ft3;
}

typedef struct F9F1_Rect {
    f32 unk0;
    u8 pad4[4];
    f32 unk8;
    f32 unkC;
} F9F1_Rect;

typedef struct F9F1_Node {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 padF;
    s16 unk10;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 pad15[3];
    struct F9F1_Node *next;
} F9F1_Node;

extern s8 D_807FCC4B[];
extern F9F1_Node **D_80754244;
extern F9F1_Node *D_807FD72C;
void func_806F6204(F9F1_Node *, u8, F9F1_Rect *);

s32 gridCoordsToIndex(f32, f32);

void func_806F4F50(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 pad[4];
    F9F1_Node *node;
    F9F1_Node *prev;
    s32 i;
    s32 found;
    s32 idx;

    i = 0;
    found = 0;
    while (found == 0 && i < D_807FD720) {
        prev = NULL;
        node = D_80754244[i];
        while (node != NULL && arg0 != node->unk0) {
            prev = node;
            node = node->next;
        }
        if (node != NULL && arg0 == node->unk0) {
            found = 1;
            if (prev != NULL) {
                prev->next = node->next;
            } else {
                D_80754244[i] = node->next;
            }
        }
        i++;
    }
    idx = gridCoordsToIndex(arg1, arg3);
    if (D_807FD720 >= idx && idx >= 0) {
        node->next = D_80754244[idx];
        D_80754244[idx] = node;
        node->unk8 = (s16) arg1;
        node->unkA = (s16) arg2;
        node->unkC = (s16) arg3;
    }
}

extern s16 D_80753EFC[];
void modelSlotGetTransformVectors(s32, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, u8);
s32 func_806F4E74(s16);

void func_806F50C8(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    F9F1_Node *node;
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
    F9F1_Node **tail;
    F9F1_Node *cur;

    modelSlotGetTransformVectors(arg0, &x, &y, &z, &u54, &u50, &u4C, &u48, &u44, 1);
    if (arg5 || ((idx = gridCoordsToIndex(x, z), (D_807FD720 >= idx)) && (idx >= 0))) {
        node = heapAlloc(0x1C);
        node->unk8 = (s16) x;
        node->unkA = (s16) y;
        node->unkC = (s16) z;
        node->unk0 = arg0;
        type = func_806F4E74(arg1);
        node->unk4 = *(s16 *) ((u8 *) D_80753EFC + type * 20);
        node->unk2 = arg1;
        node->unkE = 0;
        node->unk10 = arg2;
        node->unk12 = arg3;
        node->unk6 = -1;
        node->unk13 = arg4;
        node->unk14 = type;
        node->next = NULL;
        if (arg5) {
            tail = &D_807FD72C;
            cur = D_807FD72C;
        } else {
            cur = D_80754244[idx];
            tail = &D_80754244[idx];
        }
        if (cur != NULL) {
            do {
                tail = &cur->next;
                cur = cur->next;
            } while (cur != NULL);
        }
        *tail = node;
    }
}

typedef struct F9A_LinkedNode {
    s16 unk0;
    s16 unk2;
    u8 pad4[0x16];
    u8 unk1A;
    u8 pad1B;
    struct F9A_LinkedNode *next;
} F9A_LinkedNode;

extern F9A_LinkedNode *D_807FD730;
void slotQueueReleaseAll(void);

void gridFreeAllNodeLists(void) {
    s32 var_s2;
    s32 var_s3;
    F9F1_Node *temp_s0;
    F9F1_Node *var_s1;
    F9A_LinkedNode *temp_s1;
    F9A_LinkedNode *var_s0;

    if (D_80754244 != NULL) {
        var_s2 = 0;
        var_s3 = 0;
        if (D_807FD720 > 0) {
            do {
                var_s1 = *(F9F1_Node **) ((u8 *) D_80754244 + var_s3);
                if (var_s1 != NULL) {
                    do {
                        temp_s0 = var_s1->next;
                        heapFree(var_s1);
                        var_s1 = temp_s0;
                    } while (temp_s0 != NULL);
                }
                var_s2 += 1;
                var_s3 += 4;
            } while (var_s2 < D_807FD720);
        }
        heapFree(D_80754244);
        D_80754244 = NULL;
    }
    var_s1 = D_807FD72C;
    if (var_s1 != NULL) {
        do {
            temp_s0 = var_s1->next;
            heapFree(var_s1);
            var_s1 = temp_s0;
        } while (temp_s0 != NULL);
    }
    if (D_807FD730 != NULL) {
        var_s0 = D_807FD730;
        if (D_807FD730 != NULL) {
            do {
                temp_s1 = var_s0->next;
                heapFree(var_s0);
                var_s0 = temp_s1;
            } while (temp_s1 != NULL);
        }
        D_807FD730 = NULL;
    }
    slotQueueReleaseAll();
}


typedef struct F9A_CleanupNode {
    u8 pad0[0x18];
    struct F9A_CleanupNode *next;
} F9A_CleanupNode;



void func_806F54E0(u8, s32, u8);
void modelSlotFreeByIndex(s16, s32);

void func_806F5378(void) {
    F9A_LinkedNode *var_s0;
    F9A_LinkedNode *var_s1;

    D_807FD738 = 1;
    var_s0 = D_807FD730;
    while (var_s0 != NULL) {
        var_s1 = var_s0->next;
        func_806F54E0(0, var_s0->unk2, var_s0->unk1A);
        modelSlotFreeByIndex(var_s0->unk0, 1);
        heapFree(var_s0);
        var_s0 = var_s1;
    }
    D_807FD730 = NULL;
}

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 pad4[0xC];
    s16 unk10;
    u8 unk12;
    u8 unk13;
} F9A_SourceNode;

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 pad4[0xC];
    u8 unk10;
    u8 pad11[3];
    f32 unk14;
    s8 unk18;
    u8 unk19;
    u8 unk1A;
} F9A_DestinationNode;


F9A_DestinationNode *func_806F53EC(F9A_SourceNode *arg0) {
    F9A_DestinationNode *temp_v0;

    temp_v0 = heapAlloc(0x20);
    temp_v0->unk10 = 0;
    temp_v0->unk14 = 0.0f;
    temp_v0->unk0 = arg0->unk0;
    temp_v0->unk18 = arg0->unk10;
    temp_v0->unk2 = arg0->unk2;
    temp_v0->unk19 = arg0->unk12;
    temp_v0->unk1A = arg0->unk13;
    return temp_v0;
}

s32 func_806F544C(s32 arg0, s32 arg1, u8 arg2) {
    if ((arg1 == 0x91) || (arg1 == 0x15D) || (arg1 == 0x15E) || (arg1 == 0x15F) || (arg1 == 0x160)) {
        if (arg2 != 0) {
            arg0 = 3;
        }
    }
    return arg0;
}

void camStartPath(Actor *, s32, s32);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);

void func_806F5498(void) {
    if (flagGet(0x16C, 0) == 0) {
        camStartPath(NULL, 0x20, 5);
        flagSet(0x16C, 1, 0);
    }
}

s32 func_805FF030(u8, s32);
s32 flagGridIndex(s32, s32, u8);
s32 func_806C9974(u8, s8);
void func_8060DEC8(void);
void slotQueueAddValue(s32, u8, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
extern s8 D_80029FA0;
extern s8 D_80753EF2[];
extern u8 D_8076A0AB;

typedef struct {
    u8 pad0[6];
    u16 unk6;
    u8 pad8[0x56];
} F9L3_Action;

typedef struct {
    F9L3_Action sub[8];
    u8 pad2F0[0x306 - 8 * 0x5E];
} F9L3_PlayerData;

extern F9L3_PlayerData D_807FC950[];

void func_806F54E0(arg0, arg1, arg2)
s32 arg0;
s32 arg1;
u8 arg2;
{
    s32 i;
    s32 temp_v0;
    u8 shouldComplete;

    shouldComplete = 0;
    if ((D_807FBB64 & 0x10000000) && (arg1 != 0x56)) {
        D_80029FA0--;
        return;
    }
    if (D_8076A0A8 != 0xF) {
        temp_v0 = func_806F4E74(arg1);
        temp_v0 = func_806F544C(D_80753EF2[temp_v0 * 0x14], arg1, arg2);
        switch (arg1) {
        case 0xDD: case 0xDE: case 0xDF: case 0xE0: case 0xE1:
            flagSet((s16) flagGridIndex(0x1D5, func_805FF030(D_8076A0AB, 1), D_8074E77C[(u8)arg0]), 1, 0);
        case 0x74: case 0x288:
            slotQueueAddValue(temp_v0, arg0, 1);
            shouldComplete = 1;
            break;
        case 0x91: case 0x15D: case 0x15E: case 0x15F: case 0x160:
            if (D_807FC928 == 1) {
                func_80609140(0x331, 0x7FFF, 63.0f, 1.0f, 5, 0);
            }
        case 0xA: case 0xD: case 0x16: case 0x1E: case 0x1F:
            flagSet(0x18B, 1, 0);
            slotQueueAddValue(temp_v0, arg0, 1);
            break;
        case 0x1C: case 0x1D: case 0x23: case 0x24: case 0x27:
            flagSet(0x18C, 1, 0);
        case 0x98: case 0xEC: case 0x1D2:
            slotQueueAddValue(temp_v0, arg0, 1);
            break;
        case 0x56:
            flagSet(0x173, 1, 0);
            slotQueueAddValue(temp_v0, arg0, 1);
            break;
        case 0xB7:
            for (i = 0; i < 5; i++) {
                D_807FC950[(u8)arg0].sub[i].unk6 += 5;
            }
            func_806F5498();
            break;
        case 0x8E:
            slotQueueAddValue(temp_v0, arg0, 0x96);
            break;
        case 0x57:
            func_806C9974(arg0, 1);
            break;
        case 0x13C:
            shouldComplete = 1;
            break;
        case 0x18D:
            shouldComplete = 1;
            break;
        }
        if (shouldComplete != 0) {
            func_8060DEC8();
        }
    }
}

typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} F9N2At58;

extern s16 modelSlotAppend(s32, f32, f32, f32, f32, u8);
extern void modelSlotGetTransformVectors(s32, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, u8);
extern void func_806F50C8(s16, s16, s16, u8, u8, u8);

void func_806F58A0(u8 arg0, s16 arg1, F9N2At58 *arg2) {
    s32 var_s0;
    s32 var_pad;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    s32 var_s1;
    s16 var_s2;

    if (D_807FC928 == 1) {
        modelSlotGetTransformVectors(arg1, &sp7C, &sp78, &sp74, &sp70, &sp6C, &sp68, &sp64, &sp60, 1);
    }
    switch (arg2->unk58) {
    case 3: var_s2 = 0xA; break;
    case 5: var_s2 = 0x16; break;
    case 4:
    case 9: var_s2 = 0x1E; break;
    case 6:
    case 7: var_s2 = 0x1F; break;
    case 2:
    case 8: var_s2 = 0xD; break;
    default: var_s2 = 0xD; break;
    }
    var_s0 = 0;
    var_s1 = 0;
    do {
        if (D_807FC928 == 1) {
            func_806F50C8(modelSlotAppend(var_s2, sp7C, sp78, sp74, 0.0f, 0), var_s2, var_s0, 1, 0, 1);
        } else {
            func_806F54E0(arg0, var_s2, 0);
        }
        var_s1++;
        var_s0 += 3;
    } while (var_s1 != 5);
}

void func_806F5A48(u8 arg0, s16 arg1, F9N2At58 *arg2, u16 arg3) {
    s32 var_s0;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    s32 var_s1;
    s16 var_s2;

    if (D_807FC928 == 1) {
        modelSlotGetTransformVectors(arg1, &sp90, &sp8C, &sp88, &sp84, &sp80, &sp7C, &sp78, &sp74, 1);
    }
    switch (arg2->unk58) {
    case 3: var_s2 = 0x91; break;
    case 5: var_s2 = 0x15D; break;
    case 4: var_s2 = 0x15E; break;
    case 6:
    case 7: var_s2 = 0x15F; break;
    case 2: var_s2 = 0x160; break;
    default: var_s2 = 0x91; break;
    }
    var_s0 = 0;
    for (var_s1 = 0; var_s1 != 5; var_s1++) {
        if (D_807FC928 == 1) {
            func_806F50C8(modelSlotAppend(var_s2, sp90, sp8C, sp88, 0.0f, 0), var_s2, var_s0, 1, (arg3 == 0x11) ? 1 : 0, 1);
        } else {
            func_806F54E0(arg0, var_s2, (arg3 == 0x11) ? 1 : 0);
        }
        var_s0 += 3;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F5C30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F5CE4.s")

extern s32 randomNonNegative(void);
extern s32 D_80754248[];

void func_806F5D80(s32 *arg0, s32 *arg1) {
    *arg0 = D_80754248[((u32) (randomNonNegative() >> 0xF) % 7U)];
    *arg1 = ((s32) ((s32) (randomNonNegative() >> 0xF) % 32767) % 391) + 0xD2;
}

typedef struct F9N5_QueueSlot {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
} F9N5_QueueSlot;

extern F9N5_QueueSlot *D_80754240;

void func_806F5DF8(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s32 arg5) {
    s32 i;
    s32 found;

    found = 0;
    for (i = 0; i < 60 && !found; i++) {
        if (D_80754240[i].unk10 == 0) {
            D_80754240[i].unk0 = arg1;
            found = 1;
            D_80754240[i].unk4 = arg0;
            D_80754240[i].unk8 = arg2;
            D_80754240[i].unkA = arg3;
            D_80754240[i].unkC = arg4;
            D_80754240[i].unk10 = arg5;
        }
    }
}

s32 func_806F5EB4(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    s32 i;
    s32 found;

    found = 0;
    for (i = 0; i < 60 && !found; i++) {
        if (D_80754240[i].unk10 != 0 && arg0 == D_80754240[i].unk4 && arg1 == D_80754240[i].unk0) {
            found = 1;
        }
    }
    return found;
}

s32 func_806F5C30(s32);
void func_806F5DF8(s32, s32, s16, s16, s16, s32);
s32 func_80714608(s32);

void func_806F5F2C(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if ((func_80714608(0) != 0) && (func_806F5C30(arg0) != 0)) {
        func_806F5D80(&arg0, &arg1);
    }
    func_806F5DF8(arg0, 1, arg2, arg3, arg4, arg1);
}

void func_806F5FA0(s16 arg0, s16 arg1, s16 arg2) {
    func_806F5F2C(0x76, 0, arg0, arg1, arg2);
}

s32 func_806F5CE4();

void func_806F5FE8(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    if (func_806F5CE4() != 0) {
        func_806F5DF8(arg0, 0, arg1, arg2, arg3, arg4);
    }
}

extern void actorSpawnNodeEntryScaled(s16, f32, f32, f32, s32, s32, s32, s32);
extern void func_80686E40(f32, f32, f32, s32);
extern s32 func_8071432C(void);
extern s32 D_807FBB60;

void func_806F603C(void) {
    s32 i;

    if (func_8071432C() != 0) {
        if (!(D_807FBB60 & 2)) {
            for (i = 0; i < 60; i++) {
                if (D_80754240[i].unk10 != 0) {
                    D_80754240[i].unk10--;
                    if (D_80754240[i].unk10 == 5) {
                        func_80686E40((f32) D_80754240[i].unk8, (f32) D_80754240[i].unkA, (f32) D_80754240[i].unkC, 7);
                    }
                    if (D_80754240[i].unk10 == 0) {
                        if (D_80754240[i].unk0 != 0) {
                            actorSpawnNodeEntryScaled((s16) D_80754240[i].unk4, (f32) D_80754240[i].unk8, (f32) D_80754240[i].unkA, (f32) D_80754240[i].unkC, 0, 0x19, -1, 0);
                        } else {
                            func_806F50C8(modelSlotAppend(D_80754240[i].unk4, (f32) D_80754240[i].unk8, (f32) D_80754240[i].unkA, (f32) D_80754240[i].unkC, 0.0f, 0), (s16) D_80754240[i].unk4, 0, 1, 0, 0);
                        }
                    }
                }
            }
        }
    }
}
typedef struct {
    u8 pad0[4];
    F9N2At58 *unk4;
    u8 pad8[0x2E8];
} F9N6_PlayerBlock;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
    u8 pad14[0];
} F9N6_TableEntry;

extern F9A_LinkedNode *D_807FD734;
extern s32 camDistance3D(s32, s32, s32, s32, s32, s32);
extern s32 func_8063C2A8(s16);
extern s32 func_806F6644(s16, u8, u16);
extern void modelSlotFreeNestedBuffer(s32, u8);
extern s32 func_805FF030(u8, s32);
extern void func_8060E430(u16, u8, u8);
extern void func_806F58A0(u8, s16, F9N2At58 *);
extern void func_806F5A48(u8, s16, F9N2At58 *, u16);
extern void playerStateHandleSoundEffects(s16, s32);

void func_806F6204(F9F1_Node *arg0, u8 arg1, F9F1_Rect *arg2) {
    F9N2At58 *player;
    s32 dist;
    F9A_LinkedNode *newNode;
    F9A_LinkedNode *tail;

    player = ((F9N6_PlayerBlock *) D_807FC924)[arg1].unk4;
    if (arg0 != NULL) {
        do {
            dist = camDistance3D(arg0->unk8, ((F9N6_TableEntry *) &D_80753EF0)[arg0->unk14].unk10 + arg0->unkA, arg0->unkC, (s32) arg2->unk0, (s32) *(f32 *) arg2->pad4, (s32) arg2->unk8);
            if ((arg0->unkE == 0) &&
                ((f32) dist < (f32) ((F9N6_TableEntry *) &D_80753EF0)[arg0->unk14].unk12 + arg2->unkC) &&
                ((arg0->unk4 == 0) || (player->unk58 == arg0->unk4)) &&
                (func_8063C2A8(arg0->unk0) != 0) &&
                (func_806F6644(arg0->unk0, arg1, (u16) arg0->unk2) != 0)) {
                arg0->unkE = 1;
                modelSlotFreeNestedBuffer(arg0->unk0, 1);
                if (arg0->unk6 != -1) {
                    func_8060E430((u16) arg0->unk6, 1, func_805FF030(D_8076A0AB, 1));
                }
                if (D_807FC928 == 1) {
                    if (D_807FD734 == NULL) {
                        tail = D_807FD730;
                        D_807FD734 = tail;
                        if (tail != NULL) {
                            do {
                                D_807FD734 = tail;
                                tail = tail->next;
                            } while (tail != NULL);
                        }
                    }
                    newNode = (F9A_LinkedNode *) func_806F53EC((F9A_SourceNode *) arg0);
                    newNode->next = NULL;
                    if (D_807FD730 != NULL) {
                        D_807FD734->next = newNode;
                        D_807FD734 = newNode;
                    } else {
                        D_807FD730 = newNode;
                        D_807FD734 = newNode;
                    }
                }
                switch (arg0->unk2) {
                case 0x2B:
                case 0x205:
                case 0x206:
                case 0x207:
                case 0x208:
                    func_806F58A0(arg1, arg0->unk0, player);
                    break;
                case 0x11:
                case 0x8F:
                    func_806F5A48(arg1, arg0->unk0, player, (u16) arg0->unk2);
                    break;
                default:
                    if (D_807FC928 >= 2) {
                        func_806F54E0(arg1, arg0->unk2, arg0->unk13);
                    }
                    break;
                }
                if (D_807FC928 >= 2) {
                    playerStateHandleSoundEffects(arg0->unk2, arg1 & 0xFF);
                    modelSlotFreeByIndex(arg0->unk0, 1);
                }
                if (D_807FBB64 & 0x10000) {
                    if (arg0->unk2 != 0x1D2) {
                        func_806F5FE8(arg0->unk2, arg0->unk8, arg0->unkA, arg0->unkC, 0x258);
                    }
                }
            }
            arg0 = arg0->next;
        } while (arg0 != NULL);
    }
}


void gridDispatchRect(u8 arg0, F9F1_Rect *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    s32 temp_v0;

    if (D_807FCC4B[arg0 * 0x306] > 0) {
        temp_fv0 = arg1->unkC;
        temp_fa0 = arg1->unk0;
        if (temp_fa0 <= ((f32) D_807FD726 + temp_fv0)) {
            temp_fa1 = arg1->unk8;
            if (temp_fa1 <= ((f32) D_807FD728 + temp_fv0)) {
                temp_v0 = gridCoordsToIndex(temp_fa0, temp_fa1);
                if (temp_v0 >= 0) {
                    func_806F6204(D_80754244[temp_v0], arg0, arg1);
                }
            }
        }
        func_806F6204(D_807FD72C, arg0, arg1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F6644.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F69A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F6E58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F6EDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F6F28.s")

extern s16 D_807FD790;

s32 listContainsS16(s16 arg0) {
    s32 step;
    s16 *var_a1;
    s16 *start;
    s32 var_v0;

    var_v0 = 0;
    start = &D_807FD790;
    step = 1;
    if ((s32) D_807FD798 > (arg0 * 0)) {
        var_a1 = start;
        do {
            var_v0 += 1;
            if (arg0 == *var_a1) {
                return 1;
            }
            var_a1 += step;
        } while (var_v0 < (s32) D_807FD798);
    }
    return 0;
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F70FC.s")

f32 func_806F7378(s32 arg0) {
    if (arg0 == 0x8C) {
        return -13.0f;
    }
    return 0.0f;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/F9450/func_806F73A0.s")

typedef struct {
    u8 pad0[0x1A4];
    u8 unk1A4;
} F9L2_PlayerState;

#define F9L2_PS ((F9L2_PlayerState *)D_807FD580)

extern Actor *D_807FBB4C;
extern u8 D_80745838;

void func_80687C48(void);
void func_80687CC8(void);
void playerStateQueueCallback();
void sfxAllocateChannel(s32, f32);

void playerStateHandleSoundEffects(s16 arg0, s32 arg1) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f64 var_ft0;
    f64 var_ft1;
    f64 var_ft1_2;
    f64 var_ft3;
    f64 var_ft4;
    s32 var_v0;

    switch (arg0) {
    case 0x8E:
        sfxAllocateChannel(0x23, (f32) (1.0 - ((f64) D_80745838 * 0.3)));
        return;
    case 0x57:
        sfxAllocateChannel(0x21, (f32) (1.0 - ((f64) D_80745838 * 0.3)));
        return;
    case 0x56:
        func_80609140(0x147, 0x7FFF, 63.0f, 1.0f, 5, 0);
        return;
    case 0x11:
    case 0x8F:
        func_80609140(0x157, 0x7FFF, 63.0f, 1.0f, 5, 0);
        return;
    case 0x98:
        func_80609140(0x263, 0x7FFF, 63.0f, 1.0f, 5, 0);
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
        temp_fv0 = D_807FBB4C->unk80;
        if (((temp_fv0 - D_807FBB4C->unkA4) < 100.0f) && (D_807FBB4C->unk154 != 0x63) && (!(D_807FBB4C->unk6A & 4) || !((D_807FBB4C->unkAC - temp_fv0) > 20.0f))) {
            playerStateQueueCallback(0x29, 0, F9L2_PS->unk1A4);
            return;
        }
        return;
    case 0x74:
    case 0x288:
        sfxAllocateChannel(0x12, 1.0f);
        temp_fv0_2 = D_807FBB4C->unk80;
        if (((temp_fv0_2 - D_807FBB4C->unkA4) < 100.0f) && (D_807FBB4C->unk154 != 0x63) && (!(D_807FBB4C->unk6A & 4) || !((D_807FBB4C->unkAC - temp_fv0_2) > 20.0f))) {
            playerStateQueueCallback(0x29, 0, F9L2_PS->unk1A4);
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
        func_80609140(0x2A0, 0x7FFF, 63.0f, 1.0f, 5, 0);
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
        var_v0 = 0x41;
        if (D_8076A0A8 == 0x11) {
            var_v0 = 0x29;
        }
        playerStateQueueCallback((s16) var_v0, 0, F9L2_PS->unk1A4);
        return;
    case 0x18D:
        sfxAllocateChannel(0x12, 1.0f);
        playerStateQueueCallback(0x42, 0, F9L2_PS->unk1A4);
        func_80687CC8();
        return;
    case 0x1D1:
        func_80609140(0xAE, 0x7FFF, 63.0f, 1.0f, 5, 0);
        break;
    }
}
