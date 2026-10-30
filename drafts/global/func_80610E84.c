// func_80610E84 (src/global/15050.c): stage 4: structure identical (97 lines). diff: orig keeps idx in a0 spilled to 0x18(sp) (reloaded for return), start=a3, bs=t0; mine idx->a3, start t0, bs a0. Adding 's32 nz = idx != 0' flag + 'nz++;nz--' fake gets permuter 240 but adds 1 insn
s32 func_80610E84(s32 idx) {
    HeapPool *pool;
    HeapPool *last;
    HeapBlock *blk;
    HeapBlock *tail;
    u8 *start;
    s32 ok;
    s32 count;
    u16 bs;

    pool = &D_807F0988[idx];
    ok = 1;
    start = pool->start;
    if (idx != 0) {
        count = D_807F0A28;
        if (count >= 2) {
            bs = pool->blockSize;
            if (bs != 0) {
                tail = pool->freeList;
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
                if (bs + (s32)tail + 0x20 != pool->size + (s32)start) {
                    ok = 0;
                }
            } else {
                ok = 0;
            }
            if (ok != 0 && start == (u8 *)pool->freeList) {
                D_807F0A28 = count - 1;
                if (bs != 0) {
                    D_807F0A50--;
                }
                *(u32 *)D_807F0988[D_807F0A28].owner = *(u32 *)pool->owner;
                last = &D_807F0988[D_807F0A28];
                pool->owner = last->owner;
                pool->start = last->start;
                pool->freeList = last->freeList;
                pool->size = last->size;
                pool->blockSize = last->blockSize;
                heapSortPools();
                return 0;
            }
            return idx;
        }
    }
    return 0;
}
