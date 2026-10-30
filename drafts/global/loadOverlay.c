// loadOverlay (src/global/15050.c): stage 4: s0-s4/ra set + 0x100 frame + all stack slots (4C/60/70 spills, E0..F0, B8/98 arrays, 80 u64 pair copy) match; ~230/509 normalized insn diff left: bssSize colored t2 instead of memory (E0), cur a1 vs t2, loop/sched order. deadsweep stmts kept with FAKE tags.
// loadOverlay stage 4 draft (HeapL): same callee-saved set + frame 0x100; remaining regalloc/scheduling
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
void heapSortSurvivors(void);
void heapMoveWords(void *src, void *dst, s32 size);
void func_80610B84(s32 oldBase, s32 newBase, u32 size);
void heapInitGeneralPool(s32, s32, s32);
s32 heapInitBlockPool(s32 *, s32, s32, s32);
void *heapAlloc(s32);
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
        heapSortSurvivors();
        for (i = 1; i < D_807F5A68; i++) {
            {
                dst = HL(i - 1) + ((HeapBlock *)HL(i - 1) - 1)->size;
                src = (HeapBlock *)HL(i) - 1;
                HL(i) = dst + 0x10;
                total = src->size + 0x10;
                heapMoveWords(src, dst, total);
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
            heapMoveWords(first, dst, total);
            func_80610B84((s32)first, (s32)dst, total);
        }
        p = (u32 *)(HL(0) - 0x10);
        saved[0] = ((u64 *)p)[0];
        saved[1] = ((u64 *)p)[1];
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
    D_807F5A64 = heapAlloc(0x10);
    heapLockBlock(D_807F5A64);
    if (arg2 == 0) {
        D_807F0984 = 0x28000;
    } else {
        if (bssStart) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        D_807F0984 = arg2;
    }
    D_807F05A4 = heapAlloc(D_807F0984 + 0x80);
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
