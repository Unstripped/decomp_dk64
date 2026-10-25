#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;

void func_8070D380(s32 size, void *dst, s32 *src) {
    memcpy(dst, *src, size);
    *src += size;
}

typedef struct S112a2Record {
    u8 count;
    u8 pad1[3];
    u8 *data;
} S112a2Record;

extern void *func_80610FE8(s32);

void func_8070D3CC(S112a2Record *arg0, s32 *arg1) {
    s32 i;
    u8 *data;

    func_8070D380(1, arg0, arg1);
    data = arg0->data = func_80610FE8(arg0->count * 8);
    for (i = 0; i < arg0->count; i++) {
        func_8070D380(8, data, arg1);
        data += 8;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D464.s")

typedef struct S112a2ItemList {
    u8 count;
    u8 pad1[3];
    void *items;
} S112a2ItemList;

typedef struct S112a2Item {
    u8 flags;
    u8 pad1[3];
    u8 *data;
    u8 pad8[4];
    u8 tail[4];
} S112a2Item;

void func_8070D464(void *, s32 *);
void func_8070D568(S112a2ItemList *arg0, s32 *arg1) {
    s32 i;
    S112a2Item *item;

    func_8070D380(1, arg0, arg1);
    item = arg0->items = func_80610FE8(arg0->count * 16);
    for (i = 0; i < arg0->count; i++, item++) {
        func_8070D380(1, item, arg1);
        if (item->flags & 4) {
            item->data = func_80610FE8(4);
            func_8070D380(4, item->data, arg1);
        } else {
            item->data = NULL;
        }
        func_8070D464(item, arg1);
        func_8070D380(4, item->tail, arg1);
    }
}

extern s32 D_807550C0;

typedef struct S112aListNode {
    u16 id;
    u8 count;
    u8 pad3[9];
    struct S112aListNode *next;
} S112aListNode;

#define S112aListHead ((S112aListNode *)D_807550C0)

typedef struct S112aItemList {
    u8 count;
    u8 pad1[3];
    void *items;
} S112aItemList;

void func_8070D568(S112a2ItemList *, s32 *);

void func_8070D654(S112aItemList *arg0, s32 *arg1) {
    s32 i;
    S112aItemList *item;

    item = arg0->items = func_80610FE8(arg0->count * 8);
    for (i = 0; i < arg0->count; i++) {
        func_8070D568((S112a2ItemList *)item, arg1);
        item = (S112aItemList *)((u8 *)item + 8);
    }
}

typedef struct S112aParsedList {
    u8 count;
    u8 pad1[3];
    void *items;
    u16 length;
    u8 padA[2];
    void *payload;
} S112aParsedList;

S112aParsedList *func_8070D6D8(s32 arg0) {
    void *payload;
    s32 length;
    S112aParsedList *header;

    header = func_80610FE8(0x10);
    func_8070D380(1, header, &arg0);
    func_8070D654((S112aItemList *)header, &arg0);
    func_8070D380(2, (u8 *)header + 8, &arg0);
    length = header->length;
    payload = func_80610FE8(length);
    header->payload = payload;
    memcpy(payload, arg0, length);
    return header;
}

typedef struct S112dLink {
    void *key;
    Actor *actor;
    void *entries;
    struct S112dLink *next;
} S112dLink;

typedef struct S112dActorKeyState {
    u8 pad0[4];
    void *key;
} S112dActorKeyState;

extern void *D_807550C4;
extern s8 D_807550CC;
extern void heapClearBlock(void *);
extern unsigned long actorSpawn(s32, s32, void *);

void *func_8070D754(void *arg0) {
    S112dLink **link;
    S112dActorKeyState *state;
    link = (S112dLink **)&D_807550C4;
    if ((*link != NULL) && ((*link)->key != arg0)) {
        do {
            link = &(*link)->next;
        } while ((*link != NULL) && ((*link)->key != arg0));
    }
    if (*link == NULL) {
        *link = func_80610FE8(0x10);
        heapClearBlock(*link);
        (*link)->key = arg0;
        actorSpawn(0x12B, 0, arg0);
        D_807FBB44->unk154 = 0;
        (*link)->actor = D_807FBB44;
        state = (S112dActorKeyState *)D_807FBB44->unk174;
        state->key = arg0;
    }
    return *link;
}

typedef struct S112dEntry {
    u16 id;
    u8 count;
    u8 pad3;
    struct S112dEntry *next;
} S112dEntry;

typedef struct S112dContainer {
    u8 pad0[4];
    Actor *actor;
    S112dEntry *entries;
} S112dContainer;

void func_8070D82C(S112dContainer *arg0, u16 arg1, u8 arg2) {
    S112dEntry **entry;

    entry = &arg0->entries;
    while (*entry != NULL) {
        entry = &(*entry)->next;
    }
    *entry = func_80610FE8(8);
    (*entry)->id = arg1;
    (*entry)->count = arg2;
    (*entry)->next = NULL;
    if (arg0->actor->unk154 == 4) {
        arg0->actor->unk154 = 0;
    }
}

typedef struct S112dActorValueState {
    u8 pad0[0x54];
    u8 value;
} S112dActorValueState;

void func_8070D8C0(Actor *arg0, s32 arg1, u8 arg2) {
    S112dActorValueState *state;
    Actor *actor;
    S112dLink *node;
    u8 value;

    node = func_8070D754(arg0);
    if (1) {
        value = D_807550CC;
    }
    state = (S112dActorValueState *)node->actor->unk174;
    state->value = value & 0xFFu;
    if (1) {
        D_807550CC = 0;
        actor = arg0;
        func_8070D82C((S112dContainer *)node, arg1, arg2);
        actor->unk60 |= 0x2000000;
    }
}

S112aListNode *func_8070D928(u16 id) {
    S112aListNode *node;

    node = S112aListHead;
    if ((node != NULL) && (node->id != id)) {
        do {
            node = node->next;
        } while ((node != NULL) && (node->id != id));
    }
    return node;
}

void func_8070D970(arg0)
u16 arg0;
{
    S112aListNode *node;

    node = func_8070D928(arg0);
    if (node != NULL) {
        node->count--;
    }
}

typedef struct S112aChildNode {
    u8 pad0[0x14];
    s32 handle;
    u8 pad18[0x88];
    struct S112aChildNode *next;
} S112aChildNode;

typedef struct S112aFreeNode {
    u8 flags;
    u8 pad1[0xB];
    S112aChildNode *children;
    u8 pad10[0xC];
    struct S112aFreeNode *next;
} S112aFreeNode;

void func_80715908(s32);
extern void heapFreeDeferred();

void func_8070D9AC(S112aFreeNode *arg0) {
    s32 handle;
    s32 flags;
    S112aChildNode *current;
    S112aChildNode *node;

    node = arg0->children;
    flags = arg0->flags & 2;
    if (node != NULL) {
        do {
            current = node;
            node = node->next;
            if (flags != 0) {
                handle = current->handle;
                if (handle != 0) {
                    func_80715908(handle);
                }
            }
            heapFreeDeferred(current);
        } while (node != NULL);
    }
    heapFreeDeferred(arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070DA28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070DA74.s")

typedef struct M112bFreeEntry {
    void *unk0;
    void *unk4;
} M112bFreeEntry;


void func_8070DB7C(M112bFreeEntry *arg0) {
    heapFreeDeferred(arg0->unk4);
}

typedef struct M112bRecord {
    u8 flags;
    u8 pad1[3];
    void *unk4;
    M112bFreeEntry *unk8;
    void *unkC;
} M112bRecord;

typedef struct M112bRecordList {
    u8 count;
    u8 pad1[3];
    M112bRecord *entries;
} M112bRecordList;

typedef struct M112bRecordListArray {
    u8 count;
    u8 pad1[3];
    M112bRecordList *entries;
    void *unk8;
    void *unkC;
} M112bRecordListArray;

void func_8070DB9C(M112bRecord *arg0) {
    s32 i;
    s32 flags;
    void *temp;

    temp = arg0->unk4;
    if (temp != NULL) {
        heapFreeDeferred(temp);
    }
    flags = arg0->flags;
    i = 0;
    if (flags & 1) {
        do {
            func_8070DB7C(&arg0->unk8[i]);
            i++;
        } while (i != 1);
        heapFreeDeferred(arg0->unk8);
        return;
    }
    if (flags & 2) {
        heapFreeDeferred(arg0->unk8->unk4);
        heapFreeDeferred(arg0->unk8);
    }
}


void func_8070DC40(M112bRecordList *arg0) {
    s32 i;

    i = 0;
    if (arg0->count > 0) {
        do {
            func_8070DB9C(&arg0->entries[i]);
            i++;
        } while (i < arg0->count);
    }
    heapFreeDeferred(arg0->entries);
}


void func_8070DCA4(M112bRecordListArray *arg0) {
    s32 i;

    i = 0;
    if (arg0->count > 0) {
        do {
            func_8070DC40(&arg0->entries[i]);
            i++;
        } while (i < arg0->count);
    }
    heapFreeDeferred(arg0->entries);
    heapFreeDeferred(arg0->unkC);
    heapFreeDeferred(arg0);
}

typedef struct M112bRecordListHolder {
    void *unk0;
    M112bRecordListArray *unk4;
} M112bRecordListHolder;

void func_8070DD18(M112bRecordListHolder *arg0) {
    func_8070DCA4(arg0->unk4);
    heapFreeDeferred(arg0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070DD44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070DDDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070DED4.s")

extern s32 func_8070DED4(s32, s32, u16);
extern u8 D_807550C8;

typedef struct R112cDrawCommand {
    s32 unk0;
    u16 unk4;
} R112cDrawCommand;

typedef struct R112cDrawList {
    u8 count;
    u8 pad1[3];
    void *commands;
} R112cDrawList;

typedef struct R112cDrawListContainer {
    u8 pad0[8];
    R112cDrawList *list;
} R112cDrawListContainer;

typedef struct R112cDrawContext {
    u8 pad0[0xC];
    s32 unkC;
} R112cDrawContext;

void func_8070E2AC(s32 arg0, void *arg1, void *arg2) {
    s32 var_s0;
    s32 var_s1;
    R112cDrawList *temp_s2;
    R112cDrawCommand *temp_v0;
    R112cDrawContext *var_s3;
    s32 var_s4;

    temp_s2 = (R112cDrawList *) ((u8 *) ((R112cDrawListContainer *) arg1)->list + (D_807550C8 * 8));
    var_s3 = arg2;
    var_s4 = arg0;
    var_s0 = 0;
    var_s1 = 0;
    if (temp_s2->count > 0) {
        do {
            temp_v0 = (R112cDrawCommand *) ((u8 *) temp_s2->commands + var_s1);
            func_8070DED4(var_s4, temp_v0->unk0 + var_s3->unkC, temp_v0->unk4);
            var_s0 += 1;
            var_s1 += 8;
        } while (var_s0 < temp_s2->count);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070E34C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070E548.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070E750.s")

extern void *func_8070D754(void *);
extern void func_8070E548(Actor *, u16, u8);
extern void timerQueueAdd();
extern void func_8061DA84(void);

typedef struct R112cE808State {
    u8 pad0[0x54];
    u8 unk54;
} R112cE808State;

typedef struct R112cE808Item {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    void *unk4;
} R112cE808Item;

typedef struct R112cE808Node {
    u8 pad0[8];
    R112cE808Item *unk8;
} R112cE808Node;

typedef struct R112cE808Arg1 {
    u8 pad0[0x60];
    s32 unk60;
} R112cE808Arg1;

void func_8070E808(Actor *arg0, void *arg1) {
    R112cE808State *sp24;
    R112cE808Node *temp_v0;
    

    sp24 = arg0->unk174;
    temp_v0 = func_8070D754(arg1);
    if (temp_v0->unk8 == NULL) {
        ((R112cE808Arg1 *) arg1)->unk60 &= 0xFDFFFFFF;
        if (sp24->unk54 & 1) {
            timerQueueAdd(func_8061DA84, 0x1E, 0, 0, 0);
        }
        arg0->unk154 = 4;
        return;
    }
    func_8070E548(arg0, temp_v0->unk8->unk0, temp_v0->unk8->unk2);
    arg1 = temp_v0->unk8;
    temp_v0->unk8 = ((R112cE808Item *) arg1)->unk4;
    heapFreeDeferred(arg1);
}



void func_8070E8C8(void) {
    D_807550C0 = 0;
    D_807550C4 = 0;
}

void func_8070E8DC(s8 arg0) {
    D_807550CC = arg0;
}
