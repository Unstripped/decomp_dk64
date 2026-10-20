#include "common.h"
#include "heap.h"

extern u8 D_80746A37;
extern s32 D_80746A30;
extern HeapBlock *D_807F0990;
extern DeferredFree D_807F0A58[];
extern s32 D_807F5A58;
extern s32 D_807F5A5C;
extern s32 D_807F5A68;
extern void *D_807F5A70[];

s32 func_8065EA44(void);
HeapBlock *func_806111F8(s32 pool, u32 size);
void func_80611730(void);

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/loadOverlay.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_806109EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80610A88.s")

void func_80610B84(s32 oldBase, s32 newBase, u32 size) {
    s32 i;
    for (i = 0; i < D_807F5A68; i++) {
        s32 offset = (s32)D_807F5A70[i] - oldBase;
        if (offset >= 0 && (u32)offset < size) {
            D_807F5A70[i] = (void *)(offset + newBase);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80610BD8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80610C74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80610DCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80610E84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80610FE8.s")

u8 func_80611154(void) {
    return D_80746A37;
}

void func_80611160(void) {
    D_80746A30 = 0;
}

s32 func_8061116C(void) {
    return func_8065EA44();
}

s32 func_8061118C(void) {
    s32 total = 0;
    HeapBlock *block = D_807F0990;

    if (block != NULL) {
        do {
            total += block->size + 0x10;
            block = block->next;
        } while (block != NULL);
    }
    return total;
}

void *func_806111BC(s32 pool, s32 size) {
    u8 *ptr = (u8 *)func_806111F8(pool, (size + 0xF) & ~0xF);

    if (ptr != NULL) {
        ptr += 0x10;
        return ptr;
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_806111F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_8061130C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_8061134C.s")

void func_8061138C(void *ptr) {
    DeferredFree *entry;
    s32 count = D_807F5A58;

    while (count >= 0xA00) {
        func_80611730();
        count = D_807F5A58;
    }
    entry = &D_807F0A58[count];
    entry->ptr = ptr;
    entry->delay = D_807F5A5C;
    D_807F5A58 = count + 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80611408.s")

void func_80611534(HeapBlock *block) {
    HeapBlock *temp;

    if (block != NULL && block->prev != NULL && block->prev == block->physPrev) {
        temp = (HeapBlock *)((u8 *)block + block->size);
        temp = (HeapBlock *)((u8 *)temp + 0x10);
        temp->physPrev = block->prev;
        temp = block->prev;
        temp->size = temp->size + block->size + 0x10;
        temp->next = block->next;
        if (temp->next != NULL) {
            temp->next->prev = temp;
        }
    }
}

void func_80611594(u8 *ptr) {
    ptr[-5] = 0;
}

void func_8061159C(u8 *ptr) {
    ptr[-5] = 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_806115A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80611614.s")

s32 func_80611688(void *ptr) {
    return ((HeapBlock *)ptr - 1)->size;
}

void func_80611690(void *ptr) {
    u64 *cur = ptr;
    u16 count = (u32)((HeapBlock *)ptr - 1)->size >> 3;

    while (count--) {
        *cur++ = 0;
    }
}

void func_806116E0(s32 *ptr, s32 val) {
    s32 *cur = ptr;
    u16 count = (u32)((HeapBlock *)ptr - 1)->size >> 2;

    while (count--) {
        *cur++ = val;
    }
}

void func_80611724(s32 arg0, s32 arg1) {
    &arg0;
    &arg1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80611730.s")

void func_80611844(void) {
}
