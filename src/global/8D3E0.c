#include "common.h"
#include "actor.h"

typedef struct ActorListRecord {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ char unk10[0x20];
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ char pad36[2];
} ActorListRecord;

typedef struct ActorListEntry4 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
} ActorListEntry4;

typedef struct ActorListSub20 {
    s32 words[8];
} ActorListSub20;

typedef struct ActorListNode {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0x20];
    /* 0x44 */ Actor *unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ char unk4D[3];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ struct ActorListNode *prev;
    /* 0x68 */ struct ActorListNode *next;
} ActorListNode;

extern s32 D_8076A0A8;
extern ActorListSub20 D_807500B4;
extern ActorListSub20 D_807500D4;
extern Actor *D_807FBB40;
extern ActorListNode *D_807FC400;
extern ActorListEntry4 *D_807FC5C4;
extern u8 D_807FC5C8;
extern s16 D_807FC5D0[16];
extern s16 D_807FC5F0[16];
extern u8 D_807FC610;
extern u8 D_807FC611;

void *memcpy(void *, const void *, size_t);
void heapFree(void *);
void actorDespawn(Actor *);
s16 mapChunkFindByPosition(f32, f32, f32, s32);
s32 mapChunkIsVisible(s32, void *);
void func_8066E6C8(Actor *, s32, s32);
void func_8067AB20(s32, Actor *, s32, u8, void *, u8);
s32 func_80688C84(u16);
s16 actorListAllocId(void);
ActorListNode *actorListSpawnNodeInternal(s16, f32, f32, f32, s16, f32, void *, u8, s32, s16);
void actorListRemoveNodeInternal();
f32 playerGetMinSquaredDist3D(f32, f32, f32);
s32 mapIsBossArena(void);
u8 func_80689F80(ActorListNode *);
u8 func_80689FEC(ActorListNode *);
void func_8068A1B8(void);

extern s16 D_8076A0AA;
extern u8 D_8076A0AB;
extern s32 D_807F6010;
extern s32 D_807F6C28;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
    void *unk1C;
    void *unk20;
    u8 pad24[0xC0 - 0x24];
} ModelAssetEntry160;
extern ModelAssetEntry160 D_8076A160[];

typedef struct {
    void *ptr;
    u8 pad4[0xC0 - 4];
} ModelAssetEntry178;
extern ModelAssetEntry178 D_8076A178[];

s32 func_80600080(s32);
u16 modelTypeCountBeforeMap(u8);
void modelAssetGetSubtables(s32, s32 *, s32 **);
void modelSlotsLoadMap(s32, s32, u8, u16, s32);
void csTimerQueueFire(s16);
void actorListSpawnFromRecords(s32 *);
void modelSlotsApplyRecords(void *, void *);
void lightSetColor(f32, f32, f32, s16);
s32 func_805FF030(u8, s32);
void func_80688A6C(void);
s32 func_806C7B34(void);

void actorMapModelsSetup(s32 arg0, u8 arg1, u8 arg2) {
    s32 sp5C;
    s32 *sp58;
    s32 sp54;
    s32 pad;
    u16 sp4E;
    s32 flag;

    flag = 0;
    func_80688A6C();
    sp54 = func_80600080(D_8076A0A8);
    if (sp54 == -1) {
        switch (arg1) {
        case 0:
            D_807F6010 = arg0;
            sp4E = modelTypeCountBeforeMap(D_8076A0AB);
            flag = 1;
            break;
        case 1:
            arg0 = D_807F6010;
            break;
        }
    } else {
        D_807F6010 = arg0;
        arg0 = (s32)D_8076A178[sp54].ptr;
    }
    modelAssetGetSubtables(arg0, &sp5C, &sp58);
    if (arg2 != 0) {
        arg0 = 0;
    } else {
        arg0 = func_806C7B34();
    }
    modelSlotsLoadMap(sp5C, arg0, (u8)flag, sp4E, func_805FF030(D_8076A0AB, 1));
    csTimerQueueFire(D_8076A0AA);
    actorListSpawnFromRecords(sp58);
    if (sp54 != -1) {
        if (D_8076A160[sp54].unk20 != NULL) {
            modelSlotsApplyRecords(D_8076A160[sp54].unk20, D_8076A160[sp54].unk1C);
        }
        if (D_807F6C28 > 0) {
            flag = 0, arg0 = (s32)&D_8076A160[sp54]; do { lightSetColor( // FAKE: init + call on one line steers as1 order of the hoisted ldc1 vs addu
                (f32)((f64)(u32)((u8 *)arg0)[0x24] / 255.0),
                (f32)((f64)(u32)((u8 *)arg0)[0x25] / 255.0),
                (f32)((f64)(u32)((u8 *)arg0)[0x26] / 255.0),
                flag);
                flag++;
                arg0 += 3;
            } while (flag < D_807F6C28);
        }
    }
}

extern u8 D_807500B0;
extern s16 D_807FC408[];

void *assetLoad(s32, s32, s32, s32);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);

typedef struct ActorListContainer {
    s32 count;
    ActorListRecord items[1];
} ActorListContainer;

void actorListInitOffsets(void) {
    s32 j;
    s32 count;
    s32 total;
    void *sp60;
    ActorListContainer *container;
    ActorListRecord *items;
    s32 i;
    s32 ret;
    void *temp_v0;

    total = 0;
    if (D_807500B0 == 0) {
        D_807500B0 = 1;
        for (i = 0; i < 0xDD; i++) {
            D_807FC408[i] = total;
            temp_v0 = assetLoad(9, i, 1, 1);
            if (temp_v0 != NULL) {
                modelAssetGetSubtables((s32)temp_v0, (s32 *)&sp60, (s32 **)&container);
                count = container->count;
                items = container->items;
                for (j = 0; j < count; j++) {
                    ret = func_80688C84(items[j].unk32 + 0x10);
                    total = (u16)(total + ret);
                }
                assetSetImmediateFree();
                assetFreeBuffer(temp_v0, 0x168, 0x34);
            }
        }
    }
}

void *heapAlloc(s32);

void func_80688A6C(void) {
    s32 count;
    s32 i;
    s32 ret;
    s32 pad;
    s32 sz;
    ActorListRecord *items;
    void *asset;
    void *sp48;
    ActorListContainer *container;
    ActorListRecord *item;
    s32 var_s2;

    asset = assetLoad(9, D_8076A0A8, 1, 1);
    D_807FC5C8 = 0;
    if (asset != NULL) {
        modelAssetGetSubtables((s32)asset, (s32 *)&sp48, (s32 **)&container);
        count = container->count;
        items = container->items;
    } else {
        count = 0;
    }
    if (count > 0) {
        i = 0;
        item = items;
        do {
            if (func_80688C84(item->unk32 + 0x10) != 0) {
                D_807FC5C8++;
            }
            i++;
            item++;
        } while (i != count);
    }
    if (D_807FC5C8) {
        sz = D_807FC5C8 * sizeof(ActorListEntry4);
        i = 0;
        D_807FC5C4 = heapAlloc(sz);
    } else {
        D_807FC5C4 = NULL;
        return;
    }
    D_807FC5C8 = 0;
    var_s2 = 0;
    if (count > 0) {
        item = items;
        do {
            ret = func_80688C84(item->unk32 + 0x10);
            if (ret != 0) {
                D_807FC5C4[D_807FC5C8].unk0 = item->unk34;
                D_807FC5C4[D_807FC5C8].unk2 = ((u16 *)D_807FC408)[D_8076A0A8] + var_s2 + 0x26B;
                var_s2 += ret;
                D_807FC5C8++;
            }
            i++;
            item++;
        } while (i != count);
    }
    assetSetImmediateFree();
    assetFreeBuffer(asset, 0x1AA, 0x34);
}

s32 actorListLookupEntry(u16 arg0) {
    s32 i;

    for (i = 0; i < D_807FC5C8; i++) {
        if (arg0 == D_807FC5C4[i].unk0) {
            return D_807FC5C4[i].unk2;
        }
    }
    return -1;
}

s32 func_80688C84(u16 arg0) {
    switch (arg0) {
    case 0x5B:
    case 0x6F:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x8B:
        return 1;
    default:
        return 0;
    }
}

void actorSetCustomFloat(Actor *actor, s16 arg1, f32 arg2) {
    if (arg1 < 8) {
        ((f32 *)actor->unk124)[arg1] = arg2;
    }
}

void actorSetCustomInt(Actor *actor, s16 arg1, s32 arg2) {
    if (arg1 < 8) {
        ((s32 *)actor->unk124)[arg1] = arg2;
    }
}

void actorListSetCustomFloat(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    s32 pad[2];
    void *sp34;
    void *sp30;
    s32 temp_v0;
    s32 count;
    u8 found;
    ActorListRecord *item;

    found = 0;
    temp_v0 = func_80600080(arg0);
    if (temp_v0 != -1) {
        modelAssetGetSubtables((s32)D_8076A178[temp_v0].ptr, (s32 *)&sp34, (s32 **)&sp30);
        count = *(s32 *)sp30;
        item = sp30 = (ActorListRecord *)((s32 *)sp30 + 1);
        if (count != 0) {
            do {
                if (item->unk34 == arg1) {
                    ((f32 *)item->unk10)[arg2] = arg3;
                    found = 1;
                }
                count--;
                item++;
            } while (count != 0 && !found);
        }
    }
}

s16 actorListAllocId(void) {
    s16 id;
    s32 found;
    ActorListNode *node;

    id = 0;
    do {
        found = 0;
        node = D_807FC400;
        if (node != NULL) {
            do {
                if (node->unk5A == id) {
                    found = 1;
                }
                node = node->next;
            } while (node != NULL && !found);
        }
        if (found) {
            id++;
        }
    } while (found);

    return id;
}

s16 actorListFindIdByActor(Actor *arg0) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk44 == arg0) {
            return node->unk5A;
        }
    }
    return 0;
}

Actor *actorListFindActorById(s16 arg0) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk5A == arg0) {
            return node->unk44;
        }
    }
}

void actorListSetPosById(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk5A == arg0) {
            node->unk04 = arg1;
            node->unk08 = arg2;
            node->unk0C = arg3;
            node->unk10 = arg1;
            node->unk14 = arg2;
            node->unk18 = arg3;
            node->unk4A = mapChunkFindByPosition(arg1, arg2, arg3, 0);
            return;
        }
    }
}

void actorListSetPosByActor(Actor *arg0, f32 arg1, f32 arg2, f32 arg3) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk44 == arg0) {
            node->unk04 = arg1;
            node->unk08 = arg2;
            node->unk0C = arg3;
            return;
        }
    }
}

void actorListSpawnFromRecords(s32 *arg0) {
    ActorListRecord *item;
    s32 i;
    void *var_s2;
    s32 count;

    D_807FC400 = NULL;
    if (arg0 != NULL) {
        count = *arg0++;
        item = (ActorListRecord *)arg0;
        for (i = 0, var_s2 = (char *)item + 0x10; i < count; i++, item++, var_s2 = (char *)var_s2 + 0x38) {
            actorListSpawnNodeInternal(item->unk32, item->unk00, item->unk04, item->unk08, item->unk30, item->unk0C, var_s2, 0, 0, item->unk34);
        }
        func_8068A1B8();
    }
}

void func_80689064(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5) {
    ActorListSub20 sp38;

    sp38 = D_807500B4;
    actorListSpawnNodeInternal(arg0, arg1, arg2, arg3, (s32)arg4, arg5, &sp38, 0, 0, actorListAllocId());
}

void func_80689114(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5, s32 arg6) {
    ActorListSub20 sp38;

    sp38 = D_807500D4;
    actorListSpawnNodeInternal((s16)(arg0 - 0x10), arg1, arg2, arg3, (s32)arg4, arg5, &sp38, 1, arg6, actorListAllocId());
}

void actorListSpawnNodeEntry(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5, s32 arg6, s32 arg7) {
    actorListSpawnNodeInternal((s16)(arg0 - 0x10), arg1, arg2, arg3, (s32)arg4, arg5, (void *)arg7, 1, arg6, actorListAllocId());
}

typedef struct ActorListSpawnEntry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ char unk4[4];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ char unkA[2];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ char unk14[0x1C];
} ActorListSpawnEntry;
extern ActorListSpawnEntry D_8074E8B0[];

#ifdef NON_MATCHING
ActorListNode *actorListSpawnNodeInternal(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5, void *arg6, u8 arg7, s32 arg8, s16 arg9) {
    ActorListNode *node;
    ActorListSpawnEntry *entry;
    s32 found;
    s32 i;

    found = 0;
    i = 0;
    do {
        if ((s16)(arg0 + 0x10) == D_8074E8B0[i].unk0) {
            found = 1;
        } else {
            i++;
        }
    } while (!found && i < 0x80);
    entry = &D_8074E8B0[i];

    node = heapAlloc(sizeof(ActorListNode));
    node->unk00 = arg0;
    node->unk0C = arg3;
    node->unk18 = arg3;
    node->unk04 = arg1;
    node->unk10 = arg1;
    node->unk08 = arg2;
    node->unk14 = arg2;
    node->unk5A = arg9;
    node->unk1C = arg4;
    node->unk44 = 0;
    node->prev = NULL;
    node->unk48 = 0;
    node->unk20 = arg5;
    node->unk5C = entry->unkC;
    node->unk60 = entry->unk10;
    node->unk58 = entry->unk2;
    node->unk4A = mapChunkFindByPosition(arg1, arg2, arg3, 0);
    node->unk4C = arg7;
    node->unk50 = arg8;
    node->unk54 = (f32)entry->unk8 * (f32)entry->unk8;

    for (i = 0; i < 8; i++) {
        ((f32 *)node->unk24)[i] = ((f32 *)arg6)[i];
    }

    node->next = D_807FC400;
    if (D_807FC400 != NULL) {
        D_807FC400->prev = node;
    }
    D_807FC400 = node;

    return node;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/actorListSpawnNodeInternal.s")
#endif

typedef struct ActorListNodeInternal {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0x20];
    /* 0x44 */ Actor *unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ char unk4D[3];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s32 (*unk5C)(struct ActorListNodeInternal *);
    /* 0x60 */ s32 (*unk60)(struct ActorListNodeInternal *);
    /* 0x64 */ struct ActorListNodeInternal *prev;
    /* 0x68 */ struct ActorListNodeInternal *next;
} ActorListNodeInternal;

typedef struct ActorListSpawnInfo {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    s32 unk1C;
} ActorListSpawnInfo;



#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689418.s")

void actorListRemoveAndDespawn(s32 arg0) {
    actorListRemoveNodeInternal(arg0, 1);
}

void actorListRemoveNode(s32 arg0) {
    actorListRemoveNodeInternal(arg0, 0);
}

void actorListRemoveNodeInternal(arg0, arg1)
ActorListNode *arg0;
u8 arg1;
{
    ActorListNode *node;
    ActorListNode *prev;
    s32 found;

    found = 0;
    node = D_807FC400;
    prev = NULL;
    if (node != NULL) {
        do {
            if (node == arg0) {
                found = 1;
                if (arg1 != 0 && node->unk44 != NULL) {
                    actorDespawn(node->unk44);
                }
                if (prev != NULL) {
                    prev->next = node->next;
                } else {
                    D_807FC400 = node->next;
                }
                if (node->next != NULL) {
                    node->next->prev = prev;
                }
                heapFree(node);
            } else {
                prev = node;
                node = node->next;
            }
        } while (found == 0 && node != NULL);
    }
}

void actorListRemoveByActor(Actor *arg0) {
    ActorListNode *node;
    ActorListNode *prev;
    s32 found;

    found = 0;
    node = D_807FC400;
    prev = NULL;
    if (node != NULL) {
        do {
            if (arg0 == node->unk44) {
                found = 1;
                if (prev != NULL) {
                    prev->next = node->next;
                } else {
                    D_807FC400 = node->next;
                }
                if (node->next != NULL) {
                    node->next->prev = prev;
                }
                heapFree(node);
            } else {
                prev = node;
                node = node->next;
            }
        } while (found == 0 && node != NULL);
    }
}

void actorListFreeAll(void) {
    ActorListNode *node;
    ActorListNode *next;

    node = D_807FC400;
    if (node != NULL) {
        do {
            next = node->next;
            heapFree(node);
            node = next;
        } while (node != NULL);
    }
    D_807FC400 = NULL;
}

s32 actorListGetSerializedSize(void) {
    ActorListNode *node;
    s32 count;

    node = D_807FC400;
    count = 0;
    if (node != NULL) {
        do {
            if (node->unk4C == 0 || (node->unk44 != NULL && (node->unk44->unk64 & 0x400))) {
                count++;
            }
            node = node->next;
        } while (node != NULL);
    }
    return (count * 0x38) + 4;
}

void actorListSerialize(s32 *arg0) {
    ActorListNode *node;
    u8 *dst;
    ActorListRecord item;
    s32 count;
    node = D_807FC400;
    count = 0;
    if (node != NULL) {
        do {
            if (node->unk4C == 0 || (node->unk44 != NULL && (node->unk44->unk64 & 0x400))) {
                count++;
            }
            node = node->next;
        } while (node != NULL);
    }
    *arg0 = count;
    node = D_807FC400;
    dst = (u8 *)(arg0 + 1);
    if (node != NULL) {
        do {
            if (node->unk4C == 0 || (node->unk44 != NULL && (node->unk44->unk64 & 0x400))) {
                item.unk32 = node->unk00;
                item.unk0C = node->unk20;
                item.unk30 = node->unk1C;
                item.unk00 = node->unk04;
                item.unk04 = node->unk08;
                item.unk08 = node->unk0C;
                item.unk34 = node->unk5A;
                memcpy(item.unk10, node->unk24, 0x20);
                memcpy(dst, &item, sizeof(item));
                dst += sizeof(item);
            }
            node = node->next;
        } while (node != NULL);
    }
}

void actorListDispatchEvent(s16 arg0, void *arg1) {
    ActorListNode *node = D_807FC400;
    s32 found = 0;

    if (node != NULL) {
        do {
            if (arg0 == node->unk5A) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (found) {
        if (node->unk44 != NULL) {
            func_8067AB20((s32)D_807FBB40, node->unk44, 0x1000000, 1, arg1, 0);
        }
    }
}

s32 actorListGetOrSetState(s16 arg0, u8 arg1, u8 arg2) {
    ActorListNode *node;
    s32 found = 0;

    node = D_807FC400;
    if (node != NULL) {
        do {
            if (arg0 == node->unk5A) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (!found) {
        return 0;
    }
    if (node->unk44 == NULL) {
        return 0;
    }
    if (arg2 != 0) {
        node->unk44->unk154 = arg1;
    }
    return node->unk44->unk154;
}

s32 func_80689BAC(s16 arg0) {
    ActorListNode *node;
    s32 found = 0;

    node = D_807FC400;
    if (node != NULL) {
        do {
            if (arg0 == node->unk5A) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (!found) {
        return 0;
    }
    if (node->unk48 != 0) {
        return 1;
    }
    return 0;
}

#ifdef NON_MATCHING
s32 actorListFindClosestTargetIndex(s32 *arg0, s16 *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5) {
    s32 total = *arg0;
    u8 count = arg2;
    s32 bestIndex = -1;
    f32 minDistance = 9999999.0f;
    s32 i;
    s16 *ptr;
    s16 *end;
    f32 dx, dy, dz, dist;

    for (i = 0; i < total; i++) {
        if (count > 0) {
            s32 j = 0;
            ActorListRecord *item = (ActorListRecord *)((u8 *)arg0 + (i * 0x38) + 4);
            s16 target = item->unk32 + 0x10;
            if (count & 1) {
                if (arg1[0] == target) {
                    dx = item->unk00 - arg3;
                    dy = item->unk04 - arg4;
                    dz = item->unk08 - arg5;
                    dist = (dz * dz) + ((dx * dx) + (dy * dy));
                    if (dist < minDistance) {
                        minDistance = dist;
                        bestIndex = item->unk34;
                    }
                }
                j = 1;
                if (count == 1) {
                    continue;
                }
            }
            ptr = &arg1[j];
            end = &arg1[count];
            do {
                if (*ptr == target) {
                    dx = item->unk00 - arg3;
                    dy = item->unk04 - arg4;
                    dz = item->unk08 - arg5;
                    dist = (dz * dz) + ((dx * dx) + (dy * dy));
                    if (dist < minDistance) {
                        minDistance = dist;
                        bestIndex = item->unk34;
                    }
                }
                if (*(ptr + 1) == target) {
                    dx = item->unk00 - arg3;
                    dy = item->unk04 - arg4;
                    dz = item->unk08 - arg5;
                    dist = (dz * dz) + ((dx * dx) + (dy * dy));
                    if (dist < minDistance) {
                        minDistance = dist;
                        bestIndex = item->unk34;
                    }
                }
                ptr += 2;
            } while (ptr != end);
        }
    }
    return bestIndex;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/actorListFindClosestTargetIndex.s")
#endif

typedef struct ActorListPlayerEntry {
    u8 unk0;
    char pad1[0x210 - 1];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0x2F0 - 0x21C];
} ActorListPlayerEntry;

extern ActorListPlayerEntry *D_807FC924;
extern u8 D_807FC928;

f32 playerGetMinSquaredDist3D(f32 arg0, f32 arg1, f32 arg2) {
    f32 minDist = 100000000.0f;
    s32 i;

    for (i = 0; i < D_807FC928; i++) {
        if (D_807FC924[i].unk0 != 0) {
            f32 dist = (arg0 - D_807FC924[i].unk210) * (arg0 - D_807FC924[i].unk210) + (arg1 - D_807FC924[i].unk214) * (arg1 - D_807FC924[i].unk214) + (arg2 - D_807FC924[i].unk218) * (arg2 - D_807FC924[i].unk218);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

s32 func_80689E98(s32 arg0) {
    return 1;
}

void func_80689EA4(ActorListNode *arg0) {
    if (mapIsBossArena()) {
        mapChunkIsVisible(arg0->unk4A, arg0);
    } else {
        func_80689F80(arg0);
    }
}

u8 func_80689EE4(ActorListNode *arg0) {
    if (mapIsBossArena()) {
        return mapChunkIsVisible(*(s16 *)&arg0->unk44->unk12C, arg0) == 0;
    }
    return func_80689FEC(arg0);
}

s32 mapIsBossArena(void) {
    switch (D_8076A0A8) {
        case 0x2A:
        case 0xA9:
        case 0xAA:
        case 0xAD:
        case 0xAE:
        case 0xAF:
        case 0xB2:
        case 0xC1:
        case 0xC2:
        case 0xC3:
            return 1;
        default:
            return 0;
    }
}

u8 func_80689F80(ActorListNode *arg0) {
    s32 var_a0 = mapChunkIsVisible(arg0->unk4A, arg0) != 0;
    if (var_a0 != 0) {
        f32 dist = playerGetMinSquaredDist3D(arg0->unk10, arg0->unk14, arg0->unk18);
        var_a0 = 0;
        if (dist < arg0->unk54) {
            var_a0 = 1;
        }
    }
    return var_a0;
}

u8 func_80689FEC(ActorListNode *arg0) {
    return (mapChunkIsVisible(*(s16 *)&arg0->unk44->unk12C, arg0) == 0 || !(playerGetMinSquaredDist3D(arg0->unk10, arg0->unk14, arg0->unk18) < arg0->unk54)) && (arg0->unk44->unk114 == NULL);
}

u8 func_8068A074(ActorListNode *arg0) {
    return (mapChunkIsVisible(*(s16 *)&arg0->unk44->unk12C, arg0) == 0 || !(playerGetMinSquaredDist3D(arg0->unk10, arg0->unk14, arg0->unk18) < arg0->unk54)) && (arg0->unk44->unk114 == NULL) && (arg0->unk44->unk154 == 0);
}

s32 func_8068A10C(s32 arg0) {
    return 0;
}

u8 actorListIsPlayerInRadius(ActorListNode *arg0) {
    s32 var_v1;
    f32 dist = playerGetMinSquaredDist3D(arg0->unk10, arg0->unk14, arg0->unk18);
    var_v1 = 0;
    if (dist < arg0->unk54) {
        var_v1 = 1;
    }
    return var_v1;
}

u8 actorListIsPlayerOutsideRadius(ActorListNode *arg0) {
    return !(playerGetMinSquaredDist3D(arg0->unk44->unk7C, arg0->unk44->unk80, arg0->unk44->unk84) < arg0->unk54);
}

void func_8068A1B8(void) {
    D_807FC610 = 0;
    D_807FC611 = 0;
}

void func_8068A1CC(s16 arg0) {
    if (D_807FC610 != 0x10) {
        D_807FC5D0[D_807FC610++] = arg0;
    }
}

void func_8068A20C(s16 arg0) {
    if (D_807FC611 != 0x10) {
        D_807FC5F0[D_807FC611++] = arg0;
    }
}

s32 func_8068A24C(ActorListNode *arg0) {
    s32 i;
    for (i = 0; i < D_807FC610; i++) {
        if (arg0->unk5A == D_807FC5D0[i] && arg0->unk48 == 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_8068A2A4(ActorListNode *arg0) {
    s32 i;
    for (i = 0; i < D_807FC611; i++) {
        if (arg0->unk5A == D_807FC5F0[i] && arg0->unk48 != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8068A2FC(Actor *arg0) {
    arg0->unk128 = 0;
    arg0->unk60 &= ~0x8000;
    arg0->unk144 = 1;
    arg0->unk138 = 0;
    arg0->unk154 = 0x63;
    func_8066E6C8(arg0, 0, 0);
}
