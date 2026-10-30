// func_80610C74 (src/global/15050.c): stage 3-4: hdr part ok (u16 bs, size reused in place, u64 zero end block, do-while block chain) but orig spills a0/a1/a3 homes at entry + a3 temp reuse; mine moves addiu sp late, no a0 home, regs shifted. permuter best ~1581
void heapSortPools(void);

s32 func_80610C74(void *owner, u8 *start, u32 size, u16 blockSize) {
    u16 bs;
    u32 stride;
    u32 rem;
    HeapPool *pool;
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
    pool = &D_807F0988[D_807F0A28];
    size = size - rem + 0x10;
    end = (HeapBlock *)(start + size - 0x10);
    pool->size = size;
    pool->blockSize = bs;
    prev = NULL;
    pool->owner = owner;
    pool->start = start;
    pool->freeList = (HeapBlock *)start;
    cur = (HeapBlock *)start;
    do {
        next = (HeapBlock *)((u8 *)cur + stride);
        cur->physPrev = prev;
        cur->prev = prev;
        cur->size = bs;
        cur->next = next;
        prev = cur;
        cur = next;
    } while (next < end);
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
