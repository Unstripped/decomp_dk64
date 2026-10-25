#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;

void func_8070D380(s32 size, void *dst, s32 *src) {
    memcpy(dst, *src, size);
    *src += size;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D3CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D464.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D568.s")

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

extern void *func_80610FE8(s32);
void func_8070D568(S112aItemList *, s32 *);

void func_8070D654(S112aItemList *arg0, s32 *arg1) {
    s32 i;
    S112aItemList *item;

    item = arg0->items = func_80610FE8(arg0->count * 8);
    for (i = 0; i < arg0->count; i++) {
        func_8070D568(item, arg1);
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D754.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D82C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D8C0.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D970.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070DB9C.s")


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

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070E2AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070E34C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070E548.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070E750.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070E808.s")

extern void *D_807550C4;
extern s8 D_807550CC;

void func_8070E8C8(void) {
    D_807550C0 = 0;
    D_807550C4 = 0;
}

void func_8070E8DC(s8 arg0) {
    D_807550CC = arg0;
}
