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

#ifdef NON_MATCHING
typedef struct {
    u32 romStart;
    u32 romEnd;
    u32 vramStart;
    u32 vramEnd;
    u32 bssStart;
    u32 bssEnd;
} HeapLSegEntry;

extern HeapLSegEntry gSegmentTable[];
extern u8 D_8074450C;
extern u32 D_80744470;
extern u32 D_80744474;
extern u32 D_80744478;
extern u8 *D_8076A060;
extern u8 *D_807F05A4;
extern s32 D_807F0974;
extern s32 D_807F0978;
extern s32 D_807F097C;
extern s32 D_807F0980;
extern s32 D_807F0984;
extern s32 D_807F5A60;

void func_8060B140(s32, void *, void *, s32, s32, s32, s32);
void func_806109EC(void);
void func_80610A88(u32 *src, u32 *dst, u32 size);
void func_80610B84(s32 oldBase, s32 newBase, u32 size);
void func_80610BD8(s32, s32, s32);
s32 func_80610C74(s32 *, s32, s32, s32);
void *func_80610FE8(s32);
void heapLockBlock(u8 *ptr);

void loadOverlay(u8 arg0, u8 arg1, s32 arg2) {
    s32 sz;
    s32 id;
    s32 lo;
    s32 size;
    s32 romStart;
    u8 *vram;
    u8 *bssStart;
    s32 bssSize;
    s32 addr[10];
    s32 sizes[8];
    s32 pad[2];
    u64 saved[2];
    s32 fb1;
    u8 *h;
    u8 **hp;
    HeapBlock *first;
    s32 total;
    u8 *dst;
    HeapBlock *last;
    HeapBlock *blk;
    u32 *p;
    u32 *q;
    s32 i;
    s32 cur;
    HeapBlock *src;

    D_807F0A28 = 0;
    D_807F0A50 = 0;
    lo = D_8074450C * 0x25800 * D_8074450C;
    D_807F0A30[0] = 0;
    D_807F0A40[0] = 0;
    D_807F5A60 = 0;
    D_807F5A58 = 0;
    D_807F5A5C = 2;
    size = 0;
    romStart = 0;
    vram = NULL;
    bssStart = NULL;
    bssSize = 0;
    id = -1;
    switch (arg1) {
        default:
            cur = lo;
            break;
        case 0:
            cur = 0;
            break;
        case 9:
            id = 8;
            cur = 0;
            break;
        case 10:
            id = 9;
            cur = 0;
            break;
        case 7:
            id = 7;
            cur = lo;
            break;
        case 6:
            id = 6;
            cur = lo;
            break;
        case 5:
            id = 5;
            cur = lo;
            break;
        case 8:
            id = 4;
            cur = lo;
            break;
        case 4:
            id = 3;
            cur = lo;
            break;
        case 3:
            id = 2;
            cur = lo;
            break;
        case 2:
            id = 10;
            cur = lo;
            break;
    }
    i = 4;
    if (id != -1) {
        bssStart = (u8 *)gSegmentTable[id].bssStart;
        bssSize = gSegmentTable[id].bssEnd - gSegmentTable[id].bssStart;
        vram = (u8 *)gSegmentTable[id].vramStart;
        size = gSegmentTable[id].bssStart - (s32)vram;
        romStart = gSegmentTable[id].romStart;
        if (bssSize) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    D_80744470 = (size + bssSize + 0x8002403F) & ~0x3F;
    fb1 = D_80744470 + lo;
    D_80744474 = fb1;
    cur = 0x805FAE00 - cur;
    D_8076A060 = (u8 *)cur;
    i = 4;
    for (; i >= 0;) {
        switch (i) {
            case 0:
                sz = cur - (fb1 + lo);
                break;
            case 1:
                sz = 0x3810;
                break;
            case 2:
                sz = 0xC010;
                break;
            case 3:
                sz = 0x2810;
                break;
            case 4:
                sz = 0x61620;
                break;
        }
        i--;
        cur -= sz;
        addr[i + 1] = cur;
        sizes[i + 1] = sz;
    }
#define HL(k) (*(u8 **)D_807F5A70[k])
    if (arg0 && D_807F5A68) {
        func_806109EC();
        for (i = 1; i < D_807F5A68; i++) {
            {
                dst = HL(i - 1) + ((HeapBlock *)HL(i - 1) - 1)->size;
                src = (HeapBlock *)HL(i) - 1;
                HL(i) = dst + 0x10;
                total = src->size + 0x10;
                func_80610A88(src, dst, total);
                func_80610B84((s32)src, (s32)dst, total);
            }
        }
        total = 0;
        i = 0;
        {
            first = (HeapBlock *)HL(0) - 1;
            dst = (u8 *)addr[0];
            if (D_807F5A68 > 0) {
                do {
                    hp = (u8 **)D_807F5A70[i];
                    i++;
                    total += ((HeapBlock *)*hp - 1)->size;
                    total += 0x10;
                    *hp = *hp + (s32)dst - (s32)first;
                } while (i < D_807F5A68);
            }
            func_80610A88(first, dst, total);
            func_80610B84((s32)first, (s32)dst, total);
        }
        p = (u32 *)(HL(0) - 0x10);
        saved[0] = ((u64 *)p)[0];
        saved[1] = ((u64 *)p)[1];
    } else {
        D_807F5A68 = 0;
        D_807F5A70[0] = NULL;
    }
    func_80610BD8(0, addr[0], sizes[0]);
    D_807F0974 = func_80610C74(&D_807F0974, addr[1], sizes[1], 0x10);
    D_807F0978 = func_80610C74(&D_807F0978, addr[2], sizes[2], 0x20);
    D_807F097C = func_80610C74(&D_807F097C, addr[3], sizes[3], 0x30);
    D_807F0980 = func_80610C74(&D_807F0980, addr[4], sizes[4], 0x1000);
    if (D_807F5A68 != 0) {
        last = NULL;
        if (total) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        i = 0;
        if (D_807F5A68 > 0) {
            do {
                blk = (HeapBlock *)HL(i);
                i++;
                blk[-1].physPrev = last;
                blk = blk - 1;
                last = blk;
            } while (i < D_807F5A68);
        }
        ((u64 *)D_807F0988[0].start)[0] = saved[0];
        ((u64 *)D_807F0988[0].start)[1] = saved[1];
        ((HeapBlock *)D_807F0988[0].start)->physPrev = NULL;
        D_807F0988[0].freeList = (HeapBlock *)((u8 *)blk + blk->size + 0x10);
        D_807F0988[0].freeList->physPrev = blk;
        D_807F0988[0].freeList->size = (D_807F0988[0].size - 0x20 - (s32)D_807F0988[0].freeList) + (s32)D_807F0988[0].start;
        D_807F0988[0].freeList->next = NULL;
        D_807F0988[0].freeList->prev = NULL;
        ((HeapBlock **)(D_807F0988[0].size + D_807F0988[0].start - 0x10))[0] = D_807F0988[0].freeList;
    }
    D_807F5A64 = func_80610FE8(0x10);
    heapLockBlock(D_807F5A64);
    if (arg2 == 0) {
        D_807F0984 = 0x28000;
    } else {
        if (bssStart) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        D_807F0984 = arg2;
    }
    D_807F05A4 = func_80610FE8(D_807F0984 + 0x80);
    heapLockBlock(D_807F05A4);
    if (size != 0) {
        if (bssStart != NULL) {
            bzero(bssStart, bssSize);
        }
        func_8060B140(romStart, vram, &size, 1, 1, 1, 0);
        osWritebackDCache(vram, size);
        osInvalICache(vram, size);
    }
    p = &D_80744470;
    do {
        q = (u32 *)*p;
        p++;
        blk = (HeapBlock *)(q + (D_8074450C * 0x12C00 * D_8074450C) / 2);
        if (q < (u32 *)blk) {
            do {
                *q++ = 0x10001;
            } while (q < (u32 *)blk);
        }
    } while (p != &D_80744478);
}
#undef HL
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/15050/loadOverlay.s")
#endif

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

void func_80611730(void) {
    s32 i = 0;
    s32 flag = 0;
    s32 a = 0x3791DFFF;
    s32 b = 0x4BFFD668;
    DeferredFree *entry;
    s32 count;

    func_80611724(a, b);
    if (~a != *(s32 *)(b + 0x54002C80)) {
        flag = 1;
    }
    count = D_807F5A58;
    if (D_807F5A58 && D_807F5A58) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (count > 0) {
        do {
            entry = &D_807F0A58[i];
            if (--entry->delay == 0 && flag == 0) {
                func_80611408(entry->ptr);
                D_807F5A58 = D_807F5A58 - 1;
                count = D_807F5A58;
                entry->ptr = D_807F0A58[count].ptr;
                entry->delay = D_807F0A58[count].delay;
            } else {
                i++;
            }
        } while (i < count);
    }
}

void func_80611844(void) {
}
