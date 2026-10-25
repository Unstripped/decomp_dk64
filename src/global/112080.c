#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D380.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D3CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D464.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D568.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D654.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D6D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D754.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D82C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D8C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D928.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D970.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070D9AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070DA28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/112080/func_8070DA74.s")

extern void heapFreeDeferred();
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

extern s32 D_807550C0;
extern void *D_807550C4;
extern s8 D_807550CC;

void func_8070E8C8(void) {
    D_807550C0 = 0;
    D_807550C4 = 0;
}

void func_8070E8DC(s8 arg0) {
    D_807550CC = arg0;
}
