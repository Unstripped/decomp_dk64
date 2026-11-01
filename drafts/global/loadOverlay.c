// loadOverlay (src/global/15050.c): loadOverlay stage 4 (LoadOvl, leftovers 3): same callee-saved set + 0x100 frame + 507 insns; TEXT diff ~86 insns (was ~230): run var split into separate local h (loop regs v1/a0/a1 now match), pool block matches structurally with total/dst preloads but they take s2/s3 and pool ptr a1 vs a0; remaining: bssSize coloured t3/vram not (target vram t3, bssSize/bssStart/romStart memory, cur1 t2), L1 loop HL(i) load temp (a3 vs v1), prologue lui/addiu sp order, final-loop ring temps; arrays-of-1 for bssSize/bssStart/romStart reproduce the memory-resident early block but not the late a0/a1 arg pieces
#include "common.h"
#include "heap.h"

extern HeapPool D_807F0988[];
extern s32 D_807F5A58;
extern s32 D_807F5A5C;
extern u8 *D_807F5A64;
extern s32 D_807F5A68;
extern void *D_807F5A70[];
extern s32 D_807F0A28;
extern u16 D_807F0A30[];
extern u16 D_807F0A40[];
extern s32 D_807F0A50;

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

void dmaReadAssetDecompress(s32, void *, void *, s32, s32, s32, s32);
void heapSortSurvivors(void);
void heapMoveWords(u32 *src, u32 *dst, u32 size);
void heapRebaseHandles(s32 oldBase, s32 newBase, u32 size);
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
    u8 *vram;
    u8 *bssStart;
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
    u32 *q;
    s32 i;
    s32 cur;
    HeapBlock *src;

    lo = D_8074450C * 0x25800 * D_8074450C;
    D_807F0A28 = 0;
    size = 0;
    D_807F0A50 = 0;
    D_807F0A30[0] = 0;
    romStart = 0;
    bssSize = 0;
    D_807F0A40[0] = 0;
    bssStart = NULL;
    D_807F5A60 = 0;
    D_807F5A58 = 0;
    D_807F5A5C = 2;
    vram = NULL;
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
    if (D_8074450C != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (id != -1) {
        vram = (u8 *)gSegmentTable[id].vramStart;
        romStart = gSegmentTable[id].romStart;
        size = gSegmentTable[id].bssStart - gSegmentTable[id].vramStart;
        bssSize = gSegmentTable[id].bssEnd - gSegmentTable[id].bssStart;
        bssStart = (u8 *)gSegmentTable[id].bssStart;
    }
    D_80744470 = (size + (bssSize + 0x8002403F)) & ~0x3F;
    fb1 = D_80744470 + lo;
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
            {
                dst = HL(i - 1) + ((HeapBlock *)HL(i - 1) - 1)->size;
                src = (HeapBlock *)(HL(i) - 0x10);
                HL(i) = dst + 0x10;
                total = 0x10 + src->size;
                heapMoveWords(src, dst, total);
                heapRebaseHandles((s32)src, (s32)dst, total);
            }
        }
        total = 0;
        i = 0;
        {
            first = (HeapBlock *)(HL(0)) - 1;
            dst = (u8 *)addr[0];
            if (D_807F5A68 > 0) {
                do {
                    hp = (u8 **)D_807F5A70[i];
                    i++;
                    total += ((HeapBlock *)*hp - 1)->size + 0x10;
                    *hp = *hp + (s32)dst - (s32)first;
                } while (i < D_807F5A68);
            }
            heapMoveWords(first, dst, total);
            heapRebaseHandles((s32)first, (s32)dst, total);
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
        i = 0;
        if (D_807F5A68 > 0) {
            do {
                blk = (HeapBlock *)HL(i);
                if (D_807F0988[0].start == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                i++;
                blk[-1].physPrev = last;
                blk = blk - 1;
                last = blk;
            } while (i < D_807F5A68);
        }
        ((u64 *)D_807F0988[0].start)[0] = saved[0];
        ((u64 *)D_807F0988[0].start)[1] = saved[1];
        ((HeapBlock *)D_807F0988[0].start)->physPrev = NULL;
        total = D_807F0988[0].size - 0x20;  // FAKE: pre-loads pool size before the free-list stores
        dst = D_807F0988[0].start;  // FAKE: pre-loads pool start before the free-list stores
        src = (HeapBlock *)((u8 *)blk + blk->size + 0x10);
        D_807F0988[0].freeList = src;
        src->physPrev = blk;
        D_807F0988[0].freeList->size = (u32)(total - (s32)src) + (u32)dst;
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
    if (bssSize == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (size != 0) {
        if (bssStart) {
            bzero(bssStart, bssSize);
        }
        dmaReadAssetDecompress(romStart, vram, &size, 1, 1, 1, 0);
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
