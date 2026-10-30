// func_80610FE8 (src/global/15050.c): stage 5: body identical to orig (n=D_807F0A40[n] reassign keeps IV n; pool->freeList->next form; || tail merged), only the 14-line prologue schedule differs (orig: sw s7..s1, lui x5, sw fp,s3,s2,s0, move s0,a0, li s2,s3,fp, addiu lo x5, sw ra last; mine all saves first, li last, sw ra early). Same pre-as1 stream as ours per cc -S; deadsweep/permuter 420s no gain
s32 func_8061116C(void);
extern s32 D_80746A34;

void *func_80610FE8(u32 size) {
    s32 n;
    HeapPool *pool;
    HeapBlock *blk;
    HeapBlock *res;

    while (1) {
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
        blk = func_806111F8(0, size);
        res = blk + 1;
        if (blk != NULL) {
            D_80746A30 = 1;
            return res;
        }
        if (D_80746A30 != 0 && func_8061116C() != 0) {
            D_80746A34 = 1;
            continue;
        }
        D_80746A30 = 1;
        return NULL;
    }
}
