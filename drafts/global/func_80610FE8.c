// func_80610FE8 (src/global/15050.c): stage 3: logic done; IV elimination turns n==0 into ptr==base compare (extra move s6,s5 candidate, mul 0x14 becomes shifts, no s8=20 hoist); orig keeps n (a0), offset a1 and ptr v0 all decremented in loop
s32 func_8061116C(void);
extern s32 D_80746A34;

void *func_80610FE8(u32 size) {
    s32 n;
    HeapPool *pool;
    HeapBlock *blk;
    HeapBlock *next;

    while (1) {
        size = (size + 0xF) & ~0xF;
        n = D_807F0A50;
        if (n != 0) {
            while (size < D_807F0A30[n]) {
                n--;
            }
            if (size == D_807F0A30[n] && n != 0) {
                pool = &D_807F0988[D_807F0A40[n]];
                blk = pool->freeList;
                if (blk != NULL) {
                    next = blk->next;
                    pool->freeList = next;
                    if (next != NULL) {
                        next->prev = NULL;
                    }
                    ((u8 *)blk)[0xB] = 0;
                    D_80746A30 = 1;
                    return blk + 1;
                }
            }
        }
        blk = func_806111F8(0, size);
        if (blk != NULL) {
            D_80746A30 = 1;
            return blk + 1;
        }
        if (D_80746A30 == 0) {
            D_80746A30 = 1;
            return NULL;
        }
        if (func_8061116C() == 0) {
            D_80746A30 = 1;
            return NULL;
        }
        D_80746A34 = 1;
    }
}
