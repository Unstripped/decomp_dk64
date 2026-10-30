#include "common.h"
#include "heap.h"

extern s32 D_80746A30;
extern u8 D_80746A37;
extern HeapPool D_807F0988[];
extern HeapBlock *D_807F0990; // D_807F0988[0].freeList
extern s32 D_807F0A28;
extern u16 D_807F0A30[];
extern u16 D_807F0A40[];
extern s32 D_807F0A50;
extern DeferredFree D_807F0A58[];
extern s32 D_807F5A58;
extern s32 D_807F5A5C;
extern u8 *D_807F5A64;
extern s32 D_807F5A68;
extern void *D_807F5A70[];

s32 matrixCacheDecayLimit(void);
void heapQueueDeferredFree(void *ptr);
void func_80611408(HeapBlock *block);
HeapBlock *func_806111F8(s32 pool, u32 size);
void func_80611730(void);

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/loadOverlay.s")

void func_806109EC(void) {
    s32 i;
    s32 j;
    s32 swapped;
    u32 **list = (u32 **)D_807F5A70;

    for (i = 1; i < D_807F5A68; i++) {
        swapped = 0;
        for (j = D_807F5A68 - 1; j >= i; j--) {
            if (*list[j] < *list[j - 1]) {
                u32 *a = list[j];
                list[j] = list[j - 1];
                list[j - 1] = a;
                swapped++;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
}

void func_80610A88(u32 *src, u32 *dst, u32 size) {
    u32 *s = src;
    u32 *d = dst;
    u32 i = size >> 2;

    if (dst < src) {
        for (; i != 0; i--) {
            *d++ = *s++;
        }
    } else {
        d += size >> 2;
        s += size >> 2;
        for (; i != 0; i--) {
            *--d = *--s;
        }
    }
}

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

void heapSortPools(void) {
    u32 i;
    u32 j;
    u32 prev;

    for (i = 1; i <= D_807F0A50; i++) {
        prev = D_807F0A30[i - 1];
        D_807F0A30[i] = 0xFFFF;
        for (j = 0; j < D_807F0A28; j++) {
            if (prev < D_807F0988[j].blockSize && D_807F0988[j].blockSize < D_807F0A30[i]) {
                D_807F0A30[i] = D_807F0988[j].blockSize;
                D_807F0A40[i] = j;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80610E84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/func_80610FE8.s")

u8 func_80611154(void) {
    return D_80746A37;
}

void func_80611160(void) {
    D_80746A30 = 0;
}

s32 func_8061116C(void) {
    return matrixCacheDecayLimit();
}

s32 heapFreeBytes(void) {
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

void *heapAllocFromPool(s32 pool, s32 size) {
    u8 *ptr = (u8 *)func_806111F8(pool, (size + 0xF) & ~0xF);

    if (ptr != NULL) {
        ptr += 0x10;
        return ptr;
    }
    return NULL;
}

HeapBlock *func_806111F8(s32 pool, u32 size) {
    HeapBlock *blk;
    HeapBlock *best;
    HeapBlock *newBlk;
    HeapBlock *next;
    HeapBlock *prev;
    u32 bestSize;
    u32 rem;

    if (size == 0) {
        return (HeapBlock *)(D_807F5A64 - 0x10);
    }
    best = NULL;
    bestSize = -1;
    blk = D_807F0988[pool].freeList;
    if (blk == NULL) {
        return NULL;
    }
    do {
        if ((u32)blk->size >= size && (u32)blk->size < bestSize) {
            best = blk;
            bestSize = blk->size;
        }
        blk = blk->next;
    } while (blk != NULL);
    if (best != NULL) {
        rem = best->size - size;
        if (rem >= 0x10) {
            newBlk = (HeapBlock *)((u8 *)best + rem);
            *(u64 *)newBlk = 0;
            *(u64 *)&newBlk->next = 0;
            newBlk->size = size;
            newBlk->physPrev = best;
            best->size = rem - 0x10;
            ((HeapBlock *)((u8 *)newBlk + size))[1].physPrev = newBlk;
            return newBlk;
        }
        prev = best->prev;
        next = best->next;
        *(u64 *)&best->next = 0;
        if (prev != NULL) {
            prev->next = next;
        } else {
            D_807F0988[pool].freeList = next;
        }
        if (next != NULL) {
            next->prev = prev;
        }
        return best;
    }
    return NULL;
}

void heapFree(u8 *ptr) {
    if (ptr != D_807F5A64) {
        if ((ptr -= 0x10)[0xB] == 0) {
            func_80611408((HeapBlock *)ptr);
        }
    }
}

void heapFreeDeferred(u8 *ptr) {
    if (ptr != D_807F5A64) {
        if ((ptr -= 0x10)[0xB] == 0) {
            heapQueueDeferredFree(ptr);
        }
    }
}

void heapQueueDeferredFree(void *ptr) {
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

void heapCoalesce(HeapBlock *block);

void func_80611408(HeapBlock *block) {
    s32 i;
    s32 off;
    HeapPool *pool;
    HeapBlock *cur;
    HeapBlock *nxt;

    i = 0;
    if (D_807F0A28 > 0) {
        do {
            off = (s32)block - (s32)D_807F0988[i].start;
            if (off >= 0 && (u32)off < (u32)D_807F0988[i].size) {
                break;
            }
            i++;
        } while (i < D_807F0A28);
    }
    pool = &D_807F0988[i];
    cur = pool->freeList;
    if (cur != NULL) {
        nxt = cur->next;
        while (nxt != NULL && nxt < block) {
            if (cur == NULL) {} // FAKE: steers regalloc priority of cur
            cur = nxt;
            nxt = nxt->next;
        }
    }
    if (cur != NULL && cur < block) {
        block->prev = cur;
        block->next = cur->next;
        cur->next = block;
        if (block->next != NULL) {
            block->next->prev = block;
        }
    } else {
        block->prev = NULL;
        block->next = cur;
        if (cur != NULL) {
            cur->prev = block;
        }
        pool->freeList = block;
        if (block->next != NULL) {
            block->next->prev = block;
        }
    }
    if (pool->blockSize == 0) {
        heapCoalesce(block->next);
        heapCoalesce(block);
    }
}

void heapCoalesce(HeapBlock *block) {
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

void heapUnlockBlock(u8 *ptr) {
    ptr[-5] = 0;
}

void heapLockBlock(u8 *ptr) {
    ptr[-5] = 1;
}

void faultSetMessage(s32, s32, s32, s32);

void func_806115A8(u8 **handle) {
    HeapBlock *b;

    b = (HeapBlock *)*handle;
    b = b - 1;
    if (1) { // FAKE: steers uopt candidate order (address web before the handle param)
        ((u8 *)b)[0xB] = 2;
        D_807F5A70[D_807F5A68] = handle;
        D_807F5A68++;
        if (D_807F5A68 == 0x20) {
            faultSetMessage(0xD, 0, 0, 0);
        }
    }
}

void func_80611614(u8 **handle) {
    HeapBlock *b;
    s32 i;

    b = (HeapBlock *)*handle;
    b = b - 1;
    ((u8 *)b)[0xB] = 0;
    i = 0;
    while (i < D_807F5A68) {
        if (D_807F5A70[i] == handle) {
            break;
        }
        i++;
    }
    D_807F5A68--;
    D_807F5A70[i] = D_807F5A70[D_807F5A68];
    D_807F5A70[D_807F5A68] = NULL;
}

s32 heapBlockSize(void *ptr) {
    return ((HeapBlock *)ptr - 1)->size;
}

void heapClearBlock(void *ptr) {
    u64 *cur = ptr;
    u16 count = (u32)((HeapBlock *)ptr - 1)->size >> 3;

    while (count--) {
        *cur++ = 0;
    }
}

void heapFillBlock(s32 *ptr, s32 val) {
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
