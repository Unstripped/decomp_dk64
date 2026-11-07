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
void heapFreeToPool(HeapBlock *block);
HeapBlock *heapBestFitAlloc(s32 pool, u32 size);
void heapTickDeferredFrees(void);

typedef struct {
    u32 romStart;
    u32 romEnd;
    u32 vramStart;
    u32 vramEnd;
    u32 bssStart;
    u32 bssEnd;
} SegmentTableEntry;

extern SegmentTableEntry gSegmentTable[];
extern u8 D_8074450C;
extern s32 D_80744470;
extern s32 D_80744474;
extern s32 D_80744478;
extern u8 *D_8076A060;
extern u8 *D_807F05A4;
extern s32 D_807F0974;
extern s32 D_807F0978;
extern s32 D_807F097C;
extern s32 D_807F0980;
extern s32 D_807F0984;
extern s32 D_807F5A60;

void dmaReadAssetDecompress(s32, void *, void *, s32, s32, s32, s32);
void heapSortSurvivors(void);
void heapMoveWords(u32 src, u32 dst, u32 size);
void heapRebaseHandles(u32 oldBase, u32 newBase, u32 size);
s32 heapInitGeneralPool(s32, s32, s32);
s32 heapInitBlockPool(void *, u8 *, u32, u16);
void *heapAlloc(u32);
void heapLockBlock(u8 *ptr);


void loadOverlay(u8 arg0, u8 arg1, s32 arg2) {
    s32 sz;
    s32 id;
    s32 lo;
    s32 size;
    s32 romStart;
    u32 vram;
    s32 bssStart;
    s32 bssSize;
    s32 addr[10];
    s32 sizes[8];
    s32 pad[2];
    u64 saved[2];
    s32 fb1;
    u32 h;
    u8 **hp;
    HeapBlock *first;
    s32 total;
    u8 *dst;
    HeapBlock *last;
    HeapBlock *blk;
    u32 *p;
    u8 *q;
    s32 i;
    s32 cur;

    lo = D_8074450C * 0x25800 * D_8074450C;
    D_807F0A28 = 0;
    size = 0;
    D_807F0A50 = 0;
    D_807F0A30[0] = 0;
    romStart = 0;
    vram = 0;
    D_807F0A40[0] = 0;
    bssStart = 0;
    D_807F5A60 = 0;
    D_807F5A58 = 0;
    D_807F5A5C = 2;
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
    if (id != -1) {
        vram = (u32)gSegmentTable[id].vramStart;
        romStart = gSegmentTable[id].romStart;
        bssStart = (s32)gSegmentTable[id].bssStart;
        bssSize = gSegmentTable[id].bssEnd - gSegmentTable[id].bssStart;
        size = (s32)gSegmentTable[id].bssStart - (s32)vram;
    }
    D_80744470 = (size + (bssSize + 0x8002403F)) & ~0x3F;
    fb1 = ((size + (bssSize + 0x8002403F)) & ~0x3F) + lo;
    D_80744474 = fb1;
    D_8076A060 = (u8 *)(0x805FAE00 - cur);
    h = 0x805FAE00 - cur;
    i = 4;
    for (; i >= 0;) {
        switch (i) {
            case 0:
                sz = h - (fb1 + lo);
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
        h -= sz;
        addr[i + 1] = h;
        sizes[i + 1] = sz;
    }
#define HL(k) (*(u8 **)D_807F5A70[k])
    if (arg0 && D_807F5A68) {
        heapSortSurvivors();
        for (i = 1; i < D_807F5A68; i++) {
            q = HL(i - 1);
            dst = q + ((HeapBlock *)q - 1)->size;
            hp = (u8 **)D_807F5A70[i];
            q = *hp;
            *hp = dst + 0x10;
            total = 0x10 + ((HeapBlock *)((u32)q - 0x10))->size;
            heapMoveWords((u32)q - 0x10, (u32)dst, total);
            heapRebaseHandles((u32)q - 0x10, (u32)dst, total);
        }
        dst = (u8 *)addr[0];
        total = 0;
        first = (HeapBlock *)(HL(0) - 0x10);
        for (i = 0; i < D_807F5A68; i++) {
            hp = (u8 **)D_807F5A70[i];
            p = (u32 *)*hp;
            total += ((HeapBlock *)(u8 *)p - 1)->size + 0x10;
            *hp = (u8 *)p + (s32)dst - (s32)first;
        }
        heapMoveWords((u32)first, (u32)dst, total);
        heapRebaseHandles((u32)first, (u32)dst, total);
        q = HL(0) - 0x10;
        saved[0] = ((u64 *)q)[0];
        saved[1] = ((u64 *)q)[1];
    } else {
        D_807F5A68 = 0;
        D_807F5A70[0] = NULL;
    }
    heapInitGeneralPool(0, addr[0], sizes[0]);
    D_807F0974 = heapInitBlockPool(&D_807F0974, addr[1], sizes[1], 0x10);
    D_807F0978 = heapInitBlockPool(&D_807F0978, addr[2], sizes[2], 0x20);
    D_807F097C = heapInitBlockPool(&D_807F097C, addr[3], sizes[3], 0x30);
    D_807F0980 = heapInitBlockPool(&D_807F0980, addr[4], sizes[4], 0x1000);
    if (D_807F5A68 != 0) {
        q = NULL;
        i = 0;
        if (D_807F5A68 > 0) {
            do {
                blk = (HeapBlock *)HL(i);
                if (D_807F0988[0].start == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                i++;
                blk[-1].physPrev = (HeapBlock *)q;
                blk = blk - 1;
                q = (u8 *)blk;
            } while (i < D_807F5A68);
        }
        ((u64 *)D_807F0988[0].start)[0] = saved[0];
        ((u64 *)D_807F0988[0].start)[1] = saved[1];
        ((HeapBlock *)D_807F0988[0].start)->physPrev = NULL;
        sz = D_807F0988[0].size - 0x20;
        D_807F0988[0].freeList = (HeapBlock *)((u32)blk + blk->size + 0x10);
        sz = (u32)D_807F0988[0].start + (sz - (u32)D_807F0988[0].freeList);
        D_807F0988[0].freeList->physPrev = blk;
        D_807F0988[0].freeList->size = sz;
        D_807F0988[0].freeList->next = NULL;
        D_807F0988[0].freeList->prev = NULL;
        blk = (HeapBlock *)(D_807F0988[0].start + D_807F0988[0].size) - 1;
        blk->physPrev = D_807F0988[0].freeList;
    }
    D_807F5A64 = heapAlloc(0x10);
    heapLockBlock(D_807F5A64);
    D_807F0984 = (arg2 == 0) ? 0x28000 : arg2;
    D_807F05A4 = heapAlloc(D_807F0984 + 0x80);
    heapLockBlock(D_807F05A4);
    if (size != 0) {
        if (bssStart) {
            bzero((void *)bssStart, bssSize);
        }
        dmaReadAssetDecompress(romStart, (void *)vram, &size, 1, 1, 1, 0);
        osWritebackDCache((void *)vram, size);
        osInvalICache((void *)vram, size);
    }
    for (id = 0; id < 2; id++) {
        q = (u8 *)(&D_80744470)[id];
        p = (u32 *)(q + (D_8074450C * 0x12C00 * D_8074450C) / 2 * 4);
        if (q < (u8 *)p) {
            do {
                *(u32 *)q = 0x10001;
                q += 4;
            } while (q < (u8 *)p);
        }
    }
}

#undef HL

void heapSortSurvivors(void) {
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

void heapMoveWords(u32 src, u32 dst, u32 size) {
    u32 *s = (u32 *)src;
    u32 *d = (u32 *)dst;
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

void heapRebaseHandles(u32 oldBase, u32 newBase, u32 size) {
    s32 i;
    for (i = 0; i < D_807F5A68; i++) {
        s32 offset = (s32)D_807F5A70[i] - (s32)oldBase;
        if (offset >= 0 && (u32)offset < size) {
            D_807F5A70[i] = (void *)(offset + newBase);
        }
    }
}

s32 heapInitGeneralPool(s32 owner, s32 start, s32 size) {
    HeapBlock *blk;
    HeapBlock *end;

    D_807F0988[D_807F0A28].owner = (void *)owner;
    D_807F0988[D_807F0A28].start = (u8 *)start;
    D_807F0988[D_807F0A28].freeList = (HeapBlock *)start;
    D_807F0988[D_807F0A28].size = size;
    D_807F0988[D_807F0A28].blockSize = 0;
    blk = (HeapBlock *)start;
    *(u64 *)blk = 0;
    *(u64 *)&blk->next = 0;
    blk->size = size - 0x20;
    end = (HeapBlock *)(start + size);
    end -= 1;
    *(u64 *)end = 0;
    *(u64 *)&end->next = 0;
    end->physPrev = blk;
    ((u8 *)end)[0xB] = 2;
    return D_807F0A28++;
}

void heapSortPools(void);

s32 heapInitBlockPool(void *owner, u8 *start, u32 size, u16 blockSize) {
    u32 bs;
    u32 stride;
    u32 rem;
    HeapBlock *cur;
    HeapBlock *prev;
    HeapBlock *next;
    HeapBlock *end;

    blockSize = (blockSize + 0xF) & ~0xF;
    bs = (u32)blockSize;
    stride = blockSize + 0x10;
    rem = size % stride;
    if (rem == 0) {
        rem = stride;
    }
    size = size - rem + 0x10;
    D_807F0988[D_807F0A28].size = size;
    D_807F0988[D_807F0A28].blockSize = bs;
    D_807F0988[D_807F0A28].owner = owner;
    D_807F0988[D_807F0A28].start = start;
    D_807F0988[D_807F0A28].freeList = (HeapBlock *)start;
    cur = (HeapBlock *)start;
    end = (HeapBlock *)(start + size - 0x10);
    prev = NULL;
    do {
        next = (HeapBlock *)((u8 *)cur + stride);
        cur->physPrev = prev;
        cur->prev = prev;
        cur->size = bs;
        cur->next = next;
        prev = cur;
        cur = next;
    } while (cur < end);
    prev->next = NULL;
    *(u64 *)end = 0;
    *(u64 *)&end->next = 0;
    end->size = rem - 0x10;
    ((u8 *)end)[0xB] = 2;
    end->physPrev = prev;
    D_807F0A28++;
    D_807F0A50++;
    heapSortPools();
    return D_807F0A28 - 1;
}

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

s32 heapReleasePool(s32 idx) {
    HeapBlock *blk;
    HeapBlock *tail;
    u8 *start;
    s32 ok;
    s32 count;
    u16 bs;
    s32 x;
    s32 y;

    ok = 1;
    start = D_807F0988[idx].start;
    if (idx != 0) {
        if (start && start) {} // FAKE: steers uopt coloring (start live range / x as a candidate)
        count = D_807F0A28;
        if (count >= 2) {
            bs = D_807F0988[idx].blockSize;
            if (bs != 0) {
                tail = D_807F0988[idx].freeList;
                blk = tail->next;
                if (blk != NULL) {
                    do {
                        tail = blk;
                        if (blk->prev != blk->physPrev) {
                            ok = 0;
                            break;
                        }
                        blk = tail->next;
                    } while (blk != NULL);
                }
                x = bs + (s32)tail;
                x += 0x20;
                if (x == 0) {} // FAKE: steers uopt coloring (start live range / x as a candidate)
                y = D_807F0988[idx].size + (s32)start;
                if (x != y) {
                    ok = 0;
                }
            } else {
                ok = 0;
            }
            if (ok != 0 && start == (u8 *)D_807F0988[idx].freeList) {
                D_807F0A28 = count - 1;
                if (bs != 0) {
                    D_807F0A50--;
                }
                *(u32 *)D_807F0988[D_807F0A28].owner = *(u32 *)D_807F0988[idx].owner;
                D_807F0988[idx].owner = D_807F0988[D_807F0A28].owner;
                D_807F0988[idx].start = D_807F0988[D_807F0A28].start;
                D_807F0988[idx].freeList = D_807F0988[D_807F0A28].freeList;
                D_807F0988[idx].size = D_807F0988[D_807F0A28].size;
                D_807F0988[idx].blockSize = D_807F0988[D_807F0A28].blockSize;
                heapSortPools();
                return 0;
            }
            return idx;
        }
        if (D_807F0988[idx].owner) {} // FAKE: steers uopt coloring (permuter-found)
    }
    return 0;
}

s32 heapReclaimMatrixCache(void);
extern s32 D_80746A34;

void *heapAlloc(u32 size) { while (1) { // LAYOUT: loop header on the function line; a later .loc line makes as1 schedule the prologue differently
        s32 n;
        HeapPool *pool;
        HeapBlock *blk;
        HeapBlock *res;

        size = (size + 0xF) & ~0xF;
        n = D_807F0A50;
        if (n != 0) {
            while (size < D_807F0A30[n]) {
                n--;
            }
            if (size == D_807F0A30[n] && n != 0) {
                n = D_807F0A40[n];
                pool = &D_807F0988[n];
                blk = pool->freeList;
                if (blk != NULL) {
                    pool->freeList = blk->next;
                    if (pool->freeList != NULL) {
                        pool->freeList->prev = NULL;
                    }
                    ((u8 *)blk)[0xB] = 0;
                    D_80746A30 = 1;
                    return blk + 1;
                }
            }
        }
        blk = heapBestFitAlloc(0, size);
        res = blk + 1;
        if (blk != NULL) {
            D_80746A30 = 1;
            return res;
        }
        if (D_80746A30 != 0 && heapReclaimMatrixCache() != 0) {
            D_80746A34 = 1;
            continue;
        }
        D_80746A30 = 1;
        return NULL;
    }
}

u8 func_80611154(void) {
    return D_80746A37;
}

void func_80611160(void) {
    D_80746A30 = 0;
}

s32 heapReclaimMatrixCache(void) {
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
    u8 *ptr = (u8 *)heapBestFitAlloc(pool, (size + 0xF) & ~0xF);

    if (ptr != NULL) {
        ptr += 0x10;
        return ptr;
    }
    return NULL;
}

HeapBlock *heapBestFitAlloc(s32 pool, u32 size) {
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
            heapFreeToPool((HeapBlock *)ptr);
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
        heapTickDeferredFrees();
        count = D_807F5A58;
    }
    entry = &D_807F0A58[count];
    entry->ptr = ptr;
    entry->delay = D_807F5A5C;
    D_807F5A58 = count + 1;
}

void heapCoalesce(HeapBlock *block);

void heapFreeToPool(HeapBlock *block) {
    s32 i;
    s32 off;
    HeapPool *pool;
    HeapBlock *cur;

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
        while (cur->next != NULL && cur->next < block) {
            cur = cur->next;
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

void heapRegisterSurvivor(u8 **handle) {
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

void heapUnregisterSurvivor(u8 **handle) {
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

void heapTickDeferredFrees(void) {
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
                heapFreeToPool(entry->ptr);
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
