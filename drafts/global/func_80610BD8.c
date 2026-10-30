// func_80610BD8 (src/global/15050.c): stage 4: same insns/44 lines, regalloc only: orig pool ptr in a3 + &D_807F0A28 in t2, mine v0/a3 (v0,v1 never used by orig). u64 zero stores (*(u64*)blk=*(u64*)&blk->next=0 chain, s64 newSize temp, end=(HeapBlock*)(start+size); end-=1 split) found by permuter; deadsweep/permuter 185 no gain
void func_80610BD8(void *owner, u8 *start, s32 size) {
    HeapPool *pool;
    s32 tagOff;
    s64 newSize;
    HeapBlock *blk;
    HeapBlock *end;

    tagOff = 0xB;
    pool = &D_807F0988[D_807F0A28];
    pool->owner = owner;
    pool->start = start;
    pool->freeList = (HeapBlock *)start;
    pool->size = size;
    newSize = size - 0x20;
    pool->blockSize = 0;
    blk = (HeapBlock *)start;
    *(u64 *)blk = *(u64 *)&blk->next = 0;
    blk->size = newSize;
    end = (HeapBlock *)(start + size);
    end -= 1;
    *(u64 *)end = 0;
    *(u64 *)&end->next = 0;
    end->physPrev = blk;
    ((u8 *)end)[tagOff] = 2;
    D_807F0A28++;
}
