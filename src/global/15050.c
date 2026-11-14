#include "common.h"
#include "segment.h"
#include "heap.h"
#include "proto/global/136820.h"
#include "proto/global/15050.h"
#include "proto/global/61AA0.h"
#include "proto/global/FE40.h"



extern s32 sHeapReclaimFlag;
extern s32 sHeapReclaimMatrixFlag;
extern u8 sHeapFlags;
extern HeapPool gHeapPools[];
extern s32 gHeapPoolCount;
extern u16 gHeapPoolSizes[];
extern u16 gHeapPoolIndices[];
extern s32 gHeapBlockPoolCount;
extern DeferredFree gHeapDeferredFrees[];
extern s32 gHeapDeferredFreeCount;
extern s32 gHeapDeferredFreeDelay;
extern u8 *gHeapGuardBlock;
extern s32 gHeapSurvivorCount;
extern u8 **gHeapSurvivorList[];


extern u8 gHiResScale;
extern s32 gFramebuffers[];
extern s32 D_80744474;
extern u16 *gGfxDepthBuffer;
extern u8 *D_807F05A4;
extern s32 D_807F0974;
extern s32 D_807F0978;
extern s32 D_807F097C;
extern s32 D_807F0980;
extern s32 D_807F0984;
extern s32 gHeapUnused5A60;



void loadOverlay(u8 keepSurvivors, u8 overlayId, s32 bufferSize) {
    s32 sz;
    s32 id;
    s32 fbSize;
    s32 size;
    s32 romStart;
    s32 vram;
    s32 bssStart;
    s32 bssSize;
    u8 *addr[10];
    s32 sizes[8];
    s32 pad[2];
    u64 saved[2];
    s32 fb1;
    u32 top;
    u8 **hp;
    HeapBlock *first;
    s32 total;
    u8 *dst;
    s32 pad2;
    HeapBlock *blk;
    u32 *p;
    u8 *q;
    s32 i;
    s32 depthSize;

    fbSize = gHiResScale * 0x25800 * gHiResScale;
    gHeapPoolCount = 0;
    size = 0;
    gHeapBlockPoolCount = 0;
    gHeapPoolSizes[0] = 0;
    romStart = 0;
    vram = 0;
    gHeapPoolIndices[0] = 0;
    bssStart = 0;
    gHeapUnused5A60 = 0;
    gHeapDeferredFreeCount = 0;
    gHeapDeferredFreeDelay = 2;
    bssSize = 0;
    id = -1;
    switch (overlayId) {
        default:
            depthSize = fbSize;
            break;
        case 0:
            depthSize = 0;
            break;
        case 9:
            id = 8;
            depthSize = 0;
            break;
        case 10:
            id = 9;
            depthSize = 0;
            break;
        case 7:
            id = 7;
            depthSize = fbSize;
            break;
        case 6:
            id = 6;
            depthSize = fbSize;
            break;
        case 5:
            id = 5;
            depthSize = fbSize;
            break;
        case 8:
            id = 4;
            depthSize = fbSize;
            break;
        case 4:
            id = 3;
            depthSize = fbSize;
            break;
        case 3:
            id = 2;
            depthSize = fbSize;
            break;
        case 2:
            id = 10;
            depthSize = fbSize;
            break;
    }
    if (id != -1) {
        vram = gSegmentTable[id].vramStart;
        romStart = gSegmentTable[id].romStart;
        bssStart = gSegmentTable[id].bssStart;
        bssSize = gSegmentTable[id].bssEnd - gSegmentTable[id].bssStart;
        size = (s32)gSegmentTable[id].bssStart - vram;
    }
    gFramebuffers[0] = (size + (bssSize + 0x8002403F)) & ~0x3F;
    fb1 = ((size + (bssSize + 0x8002403F)) & ~0x3F) + fbSize;
    D_80744474 = fb1;
    gGfxDepthBuffer = (u16 *)(0x805FAE00 - depthSize);
    top = 0x805FAE00 - depthSize;
    for (i = 4; i >= 0; i--) {
        switch (i) {
            case 0:
                sz = top - (fb1 + fbSize);
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
        top -= sz;
        addr[i] = (u8 *)top;
        sizes[i] = sz;
    }
    if (keepSurvivors && gHeapSurvivorCount) {
        heapSortSurvivors();
        for (i = 1; i < gHeapSurvivorCount; i++) {
            q = *gHeapSurvivorList[i - 1];
            dst = q + ((HeapBlock *)q - 1)->size;
            hp = gHeapSurvivorList[i];
            q = *hp;
            *hp = dst + 0x10;
            total = 0x10 + ((HeapBlock *)((u32)q - 0x10))->size;
            heapMoveWords((u32)q - 0x10, (u32)dst, total);
            heapRebaseHandles((u32)q - 0x10, (u32)dst, total);
        }
        dst = addr[0];
        total = 0;
        first = (HeapBlock *)*gHeapSurvivorList[0] - 1;
        for (i = 0; i < gHeapSurvivorCount; i++) {
            hp = gHeapSurvivorList[i];
            p = (u32 *)*hp;
            total += ((HeapBlock *)p - 1)->size + 0x10;
            *hp = (u8 *)p + (s32)dst - (s32)first;
        }
        heapMoveWords((u32)first, (u32)dst, total);
        heapRebaseHandles((u32)first, (u32)dst, total);
        q = *gHeapSurvivorList[0] - 0x10;
        saved[0] = ((u64 *)q)[0]; // FAKE: punned u64 copy of the 16-byte block header (Q0405 pairwise lw/sw)
        saved[1] = ((u64 *)q)[1]; // FAKE: punned u64 copy of the 16-byte block header (Q0405 pairwise lw/sw)
    } else {
        gHeapSurvivorCount = 0;
        gHeapSurvivorList[0] = NULL;
    }
    heapInitGeneralPool(NULL, addr[0], sizes[0]);
    D_807F0974 = heapInitBlockPool(&D_807F0974, addr[1], sizes[1], 0x10);
    D_807F0978 = heapInitBlockPool(&D_807F0978, addr[2], sizes[2], 0x20);
    D_807F097C = heapInitBlockPool(&D_807F097C, addr[3], sizes[3], 0x30);
    D_807F0980 = heapInitBlockPool(&D_807F0980, addr[4], sizes[4], 0x1000);
    if (gHeapSurvivorCount != 0) {
        q = NULL;
        for (i = 0; i < gHeapSurvivorCount; i++) {
            blk = (HeapBlock *)*gHeapSurvivorList[i] - 1;
            if (gHeapPools[0].start == 0) {}  // FAKE: extra block in the rebuild loop keeps the vram home store (t3, sp+0xE8) ahead of the sz spill
            blk->physPrev = (HeapBlock *)q;
            q = (u8 *)blk;
        }
        ((u64 *)gHeapPools[0].start)[0] = saved[0]; // FAKE: punned u64 copy of the 16-byte block header (Q0405 pairwise lw/sw)
        ((u64 *)gHeapPools[0].start)[1] = saved[1]; // FAKE: punned u64 copy of the 16-byte block header (Q0405 pairwise lw/sw)
        ((HeapBlock *)gHeapPools[0].start)->physPrev = NULL;
        sz = gHeapPools[0].size - 0x20;
        gHeapPools[0].freeList = (HeapBlock *)((u32)blk + blk->size + 0x10);
        sz = (u32)gHeapPools[0].start + (sz - (u32)gHeapPools[0].freeList);
        gHeapPools[0].freeList->physPrev = blk;
        gHeapPools[0].freeList->size = sz;
        gHeapPools[0].freeList->next = NULL;
        gHeapPools[0].freeList->prev = NULL;
        blk = (HeapBlock *)(gHeapPools[0].start + gHeapPools[0].size) - 1;
        blk->physPrev = gHeapPools[0].freeList;
    }
    gHeapGuardBlock = heapAlloc(0x10);
    heapLockBlock(gHeapGuardBlock);
    D_807F0984 = (bufferSize == 0) ? 0x28000 : bufferSize;
    D_807F05A4 = heapAlloc(D_807F0984 + 0x80);
    heapLockBlock(D_807F05A4);
    if (size != 0) {
        if (bssStart) {
            bzero((void *)bssStart, bssSize);
        }
        dmaReadAssetDecompress(romStart, (void *)vram, &size, 1, 1, 1, NULL);
        osWritebackDCache((void *)vram, size);
        osInvalICache((void *)vram, size);
    }
    for (id = 0; id < 2; id++) {
        q = (u8 *)gFramebuffers[id];
        p = (u32 *)(q + (gHiResScale * 0x12C00 * gHiResScale) / 2 * 4);
        while (q < (u8 *)p) {
            *(u32 *)q = 0x10001;
            q += 4;
        }
    }
}

void heapSortSurvivors(void) {
    s32 i;
    s32 j;
    s32 swapped;
    u8 ***list = gHeapSurvivorList;

    for (i = 1; i < gHeapSurvivorCount; i++) {
        swapped = 0;
        for (j = gHeapSurvivorCount - 1; j >= i; j--) {
            if (*list[j] < *list[j - 1]) {
                u8 **a = list[j];
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
        d += i;
        s += i;
        for (; i != 0; i--) {
            *--d = *--s;
        }
    }
}

void heapRebaseHandles(u32 oldBase, u32 newBase, u32 size) {
    s32 i;
    for (i = 0; i < gHeapSurvivorCount; i++) {
        s32 offset = (s32)gHeapSurvivorList[i] - (s32)oldBase;
        if (offset >= 0 && (u32)offset < size) {
            gHeapSurvivorList[i] = (u8 **)(offset + newBase);
        }
    }
}

s32 heapInitGeneralPool(s32 *owner, u8 *start, s32 size) {
    HeapBlock *blk;
    HeapBlock *end;

    gHeapPools[gHeapPoolCount].owner = owner;
    gHeapPools[gHeapPoolCount].start = start;
    gHeapPools[gHeapPoolCount].freeList = (HeapBlock *)start;
    gHeapPools[gHeapPoolCount].size = size;
    gHeapPools[gHeapPoolCount].blockSize = 0;
    blk = (HeapBlock *)start;
    *(u64 *)blk = 0; // FAKE: punned u64 store zeroes physPrev+size as one 64-bit store pair (Q0137)
    *(u64 *)&blk->next = 0; // FAKE: punned u64 store zeroes next+prev as one 64-bit store pair (Q0137)
    blk->size = size - 0x20;
    end = (HeapBlock *)(start + size);
    end -= 1;
    *(u64 *)end = 0; // FAKE: punned u64 store zeroes physPrev+size as one 64-bit store pair (Q0137)
    *(u64 *)&end->next = 0; // FAKE: punned u64 store zeroes next+prev as one 64-bit store pair (Q0137)
    end->physPrev = blk;
    ((u8 *)end)[0xB] = 2;
    return gHeapPoolCount++;
}


s32 heapInitBlockPool(s32 *owner, u8 *start, u32 size, u16 blockSize) {
    u32 bs;
    u32 stride;
    u32 rem;
    HeapBlock *cur;
    HeapBlock *prev;
    HeapBlock *next;
    HeapBlock *end;

    blockSize = (blockSize + 0xF) & ~0xF;
    bs = blockSize;
    stride = blockSize + 0x10;
    rem = size % stride;
    if (rem == 0) {
        rem = stride;
    }
    size = size - rem + 0x10;
    gHeapPools[gHeapPoolCount].size = size;
    gHeapPools[gHeapPoolCount].blockSize = bs;
    gHeapPools[gHeapPoolCount].owner = owner;
    gHeapPools[gHeapPoolCount].start = start;
    gHeapPools[gHeapPoolCount].freeList = (HeapBlock *)start;
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
    *(u64 *)end = 0; // FAKE: punned u64 store zeroes physPrev+size as one 64-bit store pair (Q0137)
    *(u64 *)&end->next = 0; // FAKE: punned u64 store zeroes next+prev as one 64-bit store pair (Q0137)
    end->size = rem - 0x10;
    ((u8 *)end)[0xB] = 2;
    end->physPrev = prev;
    gHeapPoolCount++;
    gHeapBlockPoolCount++;
    heapSortPools();
    return gHeapPoolCount - 1;
}

void heapSortPools(void) {
    u32 i;
    u32 j;
    u32 prev;

    for (i = 1; i <= gHeapBlockPoolCount; i++) {
        prev = gHeapPoolSizes[i - 1];
        gHeapPoolSizes[i] = 0xFFFF;
        for (j = 0; j < gHeapPoolCount; j++) {
            if (prev < gHeapPools[j].blockSize && gHeapPools[j].blockSize < gHeapPoolSizes[i]) {
                gHeapPoolSizes[i] = gHeapPools[j].blockSize;
                gHeapPoolIndices[i] = j;
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
    s32 tailEnd;
    s32 poolEnd;

    ok = 1;
    start = gHeapPools[idx].start;
    if (idx != 0) {
        if (start && start) {} // FAKE: two extra uses lift start (a3) above the bs conversion (t0) in uopt colouring
        count = gHeapPoolCount;
        if (count >= 2) {
            bs = gHeapPools[idx].blockSize;
            if (bs != 0) {
                tail = gHeapPools[idx].freeList;
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
                tailEnd = bs + (s32)tail;
                tailEnd += 0x20;
                if (tailEnd == 0) {} // FAKE: second use keeps the tailEnd sum a coloured candidate in a0
                poolEnd = gHeapPools[idx].size + (s32)start;
                if (tailEnd != poolEnd) {
                    ok = 0;
                }
            } else {
                ok = 0;
            }
            if (ok != 0 && start == (u8 *)gHeapPools[idx].freeList) {
                gHeapPoolCount = count - 1;
                if (bs != 0) {
                    gHeapBlockPoolCount--;
                }
                *gHeapPools[gHeapPoolCount].owner = *gHeapPools[idx].owner;
                gHeapPools[idx].owner = gHeapPools[gHeapPoolCount].owner;
                gHeapPools[idx].start = gHeapPools[gHeapPoolCount].start;
                gHeapPools[idx].freeList = gHeapPools[gHeapPoolCount].freeList;
                gHeapPools[idx].size = gHeapPools[gHeapPoolCount].size;
                gHeapPools[idx].blockSize = gHeapPools[gHeapPoolCount].blockSize;
                heapSortPools();
                return 0;
            }
            return idx;
        }
        if (gHeapPools[idx].owner) {} // FAKE: block boundary keeps v0 = 0 out of the entry block (bnezl delay slot at the count exit)
    }
    return 0;
}

void *heapAlloc(u32 size) { while (1) { // LAYOUT: loop header on the function line; a later .loc line makes as1 schedule the prologue differently
        s32 n;
        HeapPool *pool;
        HeapBlock *blk;
        HeapBlock *res;

        size = (size + 0xF) & ~0xF;
        n = gHeapBlockPoolCount;
        if (n != 0) {
            while (size < gHeapPoolSizes[n]) {
                n--;
            }
            if (size == gHeapPoolSizes[n] && n != 0) {
                n = gHeapPoolIndices[n];
                pool = &gHeapPools[n];
                blk = pool->freeList;
                if (blk != NULL) {
                    pool->freeList = blk->next;
                    if (pool->freeList != NULL) {
                        pool->freeList->prev = NULL;
                    }
                    ((u8 *)blk)[0xB] = 0;
                    sHeapReclaimFlag = 1;
                    return blk + 1;
                }
            }
        }
        blk = heapBestFitAlloc(0, size);
        res = blk + 1;
        if (blk != NULL) {
            sHeapReclaimFlag = 1;
            return res;
        }
        if (sHeapReclaimFlag != 0 && heapReclaimMatrixCache() != 0) {
            sHeapReclaimMatrixFlag = 1;
            continue;
        }
        sHeapReclaimFlag = 1;
        return NULL;
    }
}

u8 heapGetFlags(void) {
    return sHeapFlags;
}

void heapClearReclaimFlag(void) {
    sHeapReclaimFlag = 0;
}

s32 heapReclaimMatrixCache(void) {
    return matrixCacheDecayLimit();
}

s32 heapFreeBytes(void) {
    s32 total = 0;
    HeapBlock *block;

    for (block = gHeapPools[0].freeList; block != NULL; block = block->next) {
        total += block->size + 0x10;
    }
    return total;
}

void *heapAllocFromPool(s32 pool, s32 size) {
    HeapBlock *blk = heapBestFitAlloc(pool, (size + 0xF) & ~0xF);

    if (blk != NULL) {
        blk++;
        return blk;
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
        return (HeapBlock *)gHeapGuardBlock - 1;
    }
    best = NULL;
    bestSize = -1;
    blk = gHeapPools[pool].freeList;
    if (blk == NULL) {
        return NULL;
    }
    do {
        if (blk->size >= size && blk->size < bestSize) {
            best = blk;
            bestSize = blk->size;
        }
        blk = blk->next;
    } while (blk != NULL);
    if (best != NULL) {
        rem = best->size - size;
        if (rem >= 0x10) {
            newBlk = (HeapBlock *)((u8 *)best + rem);
            *(u64 *)newBlk = 0; // FAKE: punned u64 store zeroes physPrev+size as one 64-bit store pair (Q0137)
            *(u64 *)&newBlk->next = 0; // FAKE: punned u64 store zeroes next+prev as one 64-bit store pair (Q0137)
            newBlk->size = size;
            newBlk->physPrev = best;
            best->size = rem - 0x10;
            ((HeapBlock *)((u8 *)newBlk + size))[1].physPrev = newBlk;
            return newBlk;
        }
        prev = best->prev;
        next = best->next;
        *(u64 *)&best->next = 0; // FAKE: punned u64 store zeroes next+prev as one 64-bit store pair (Q0137)
        if (prev != NULL) {
            prev->next = next;
        } else {
            gHeapPools[pool].freeList = next;
        }
        if (next != NULL) {
            next->prev = prev;
        }
        return best;
    }
    return NULL;
}

void heapFree(void *ptr) {
    HeapBlock *block = (HeapBlock *)ptr - 1;

    if (ptr != gHeapGuardBlock) {
        if (((u8 *)block)[0xB] == 0) {
            heapFreeToPool(block);
        }
    }
}

void heapFreeDeferred(void *ptr) {
    HeapBlock *block = (HeapBlock *)ptr - 1;

    if (ptr != gHeapGuardBlock) {
        if (((u8 *)block)[0xB] == 0) {
            heapQueueDeferredFree(block);
        }
    }
}

void heapQueueDeferredFree(void *ptr) {
    DeferredFree *entry;
    s32 count = gHeapDeferredFreeCount;

    while (count >= 0xA00) {
        heapTickDeferredFrees();
        count = gHeapDeferredFreeCount;
    }
    entry = &gHeapDeferredFrees[count];
    entry->ptr = ptr;
    entry->delay = gHeapDeferredFreeDelay;
    gHeapDeferredFreeCount = count + 1;
}


void heapFreeToPool(HeapBlock *block) {
    s32 i;
    s32 off;
    HeapPool *pool;
    HeapBlock *cur;

    for (i = 0; i < gHeapPoolCount; i++) {
        off = (s32)block - (s32)gHeapPools[i].start;
        if (off >= 0 && (u32)off < (u32)gHeapPools[i].size) {
            break;
        }
    }
    pool = &gHeapPools[i];
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
        temp = (HeapBlock *)((u8 *)(block + 1) + block->size);
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


void heapRegisterSurvivor(u8 **handle) {
    HeapBlock *b;

    b = (HeapBlock *)*handle;
    b = b - 1;
    if (1) { // FAKE: steers uopt candidate order (address web before the handle param)
        ((u8 *)b)[0xB] = 2;
        gHeapSurvivorList[gHeapSurvivorCount] = handle;
        gHeapSurvivorCount++;
        if (gHeapSurvivorCount == 0x20) {
            faultSetMessage(0xD, 0, 0, 0);
        }
    }
}

void heapUnregisterSurvivor(u8 **handle) {
    HeapBlock *b;
    s32 i;

    b = (HeapBlock *)*handle - 1;
    ((u8 *)b)[0xB] = 0;
    for (i = 0; i < gHeapSurvivorCount; i++) {
        if (gHeapSurvivorList[i] == handle) {
            break;
        }
    }
    gHeapSurvivorCount--;
    gHeapSurvivorList[i] = gHeapSurvivorList[gHeapSurvivorCount];
    gHeapSurvivorList[gHeapSurvivorCount] = NULL;
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

void heapTickDeferredFreesHook(s32 notExpected, s32 addrBias) {
}

void heapTickDeferredFrees(void) {
    s32 i = 0;
    s32 flag = 0;
    s32 notExpected = 0x3791DFFF;
    s32 addrBias = 0x4BFFD668;
    DeferredFree *entry;
    s32 count;

    heapTickDeferredFreesHook(notExpected, addrBias);
    if (~notExpected != *(s32 *)(addrBias + 0x54002C80)) {
        flag = 1;
    }
    count = gHeapDeferredFreeCount;
    if (gHeapDeferredFreeCount && gHeapDeferredFreeCount) {}  // FAKE: second count read keeps count in a0 (v1 without it)
    while (i < count) {
        entry = &gHeapDeferredFrees[i];
        if (--entry->delay == 0 && flag == 0) {
            heapFreeToPool(entry->ptr);
            gHeapDeferredFreeCount--;
            count = gHeapDeferredFreeCount;
            entry->ptr = gHeapDeferredFrees[count].ptr;
            entry->delay = gHeapDeferredFrees[count].delay;
        } else {
            i++;
        }
    }
}

void heapCodeEnd(void) {
}
