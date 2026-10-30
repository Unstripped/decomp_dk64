// func_80610E84 (src/global/15050.c): stage 5: frame 0x18/idx home spill identical, whole body identical but regalloc: orig bs=t0,count=t1,A28addr=t2,base=t3,const20=t4 (a0 never taken by bs); mine bs=a0,count=t0,.. (all t's shifted by one) and mine hoists 'move v0,zero' to entry while orig keeps three separate or v0,zero (bnezl delay slot, FD4 block, post-jal). Direct D_807F0988[idx].field (no pool local) fixed 'move a3,a0'; deadsweep best 33 lines (3 fake ifs), permuter n/a; idx colored a0 in orig but -1 in mine (uopt trace -l 5)
s32 func_80610E84(s32 idx) {
    HeapBlock *blk;
    HeapBlock *tail;
    u8 *start;
    s32 ok;
    s32 count;
    u16 bs;

    ok = 1;
    start = D_807F0988[idx].start;
    if (idx != 0) {
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
                if (bs + (s32)tail + 0x20 != D_807F0988[idx].size + (s32)start) {
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
    }
    return 0;
}
