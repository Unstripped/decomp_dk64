// func_80610C74 (src/global/15050.c): stage 4: frame 0x20 + s0 same, full diff 63 lines regalloc: orig spills owner(a0)/start(a1)/blockSize(a3) homes at entry because loop candidates take v0=cur v1=next a0=prev a1=bound(copy of end) a2=end a3=bs t0=stride t1=rem t2=&A28 (first-fit, 9 candidates); mine lacks the separate loop-bound candidate (a1=copy of a2) so owner stays in a0. Loop bound as recomputed (start+size-0x10) and direct D_807F0988[D_807F0A28] fields helped (86->63); permuter hint: local new_var=0x10 used in bound and end->size gives n=95/95 (full 76)
void heapSortPools(void);


s32 func_80610C74(void *owner, u8 *start, u32 size, u16 blockSize) {
    u16 bs;
    u32 stride;
    u32 rem;
    HeapBlock *cur;
    HeapBlock *prev;
    HeapBlock *next;
    HeapBlock *end;

    bs = (blockSize + 0xF) & ~0xF;
    stride = bs + 0x10;
    rem = size % stride;
    if (rem == 0) {
        rem = stride;
    }
    size = size - rem + 0x10;
    end = (HeapBlock *)(start + size - 0x10);
    D_807F0988[D_807F0A28].size = size;
    D_807F0988[D_807F0A28].blockSize = bs;
    prev = NULL;
    D_807F0988[D_807F0A28].owner = owner;
    D_807F0988[D_807F0A28].start = start;
    D_807F0988[D_807F0A28].freeList = (HeapBlock *)start;
    cur = (HeapBlock *)start;
    do {
        next = (HeapBlock *)((u8 *)cur + stride);
        cur->physPrev = prev;
        cur->prev = prev;
        cur->size = bs;
        cur->next = next;
        prev = cur;
        cur = next;
    } while (next < (HeapBlock *)(start + size - 0x10));
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
