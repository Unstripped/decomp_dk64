// controllerAnimCacheFree (src/global/17B90.c): SmallA W6: stage 5, count EXACT (67 insns), frame 0x28 + spill slot 24 match, score 2 (was 25 with count 68): *(u16*)&D_807FBB32 -= 1; last = &tbl[*(u16*)&D_807FBB32] (no last_idx local => ring temps t1/t2 and &D_807FBB32 in a3), locals temp_a2 i count entry last (temp_a2 declared first), 1 FAKE 'if (count && count) {}' before the guard (blocks the i<count -> bne LFTR, keeps slt at). Remaining: 'sh t2,0(a3)' scheduled 3 slots early (target after li t9,0xffff); in ours ugen emits sh right after addiu; target needs the sh later in ucode order (store after last->id load) but E-1 is not CSE'd across the s32 field stores (late store reloads E: 77-78 insns); named last_idx/i/count reuse, idx local, 'D -= 1' at every statement position, (u16)D var forms all worse
typedef struct {
    void *unk0;
    void *unk4;
    void *unk8;
    void *unkC;
} SmallAControllerAnimDataView;

typedef struct {
    void *unk0;
    SmallAControllerAnimDataView *unk4;
} SmallAControllerAnimRefView;

typedef struct {
    u8 pad0[0x84];
    s32 unk84;
} SmallAControllerAnimDataBlock;


int controllerAnimCacheFree(void *arg0, void *arg1) {
    void *temp_a2;
    s32 i;
    s32 count;
    struct AnimCacheEntry *entry;
    struct AnimCacheEntry *last;

    temp_a2 = *(void **)arg1;
    if (temp_a2 != NULL) {
        count = *(u16 *)&D_807FBB32;
        entry = D_807FB7B0;
        i = 0;
        if (count && count) {} // FAKE: steers loop-latch slt (blocks LFTR i != count)
        if (count > 0) {
            do {
                if (temp_a2 == entry->asset) {
                    if (--entry->refCount == 0) {
                        assetFreeBuffer(entry->asset, 0x298, 0x15);
                        *(u16 *)&D_807FBB32 -= 1;
                        last = &D_807FB7B0[*(u16 *)&D_807FBB32];
                        entry->id = last->id;
                        entry->asset = last->asset;
                        entry->refCount = last->refCount;
                        last->id = 0xFFFF;
                        last->asset = NULL;
                        last->refCount = 0;
                    }
                    break;
                }
                entry++;
            } while (++i < count);
        }
        *(void **)arg1 = NULL;
    }
    if ((void *)arg1 == ((SmallAControllerAnimRefView *)arg0)->unk4->unk4) {
        ((SmallAControllerAnimDataBlock *)((SmallAControllerAnimRefView *)arg0)->unk4)->unk84 = 0;
    }
}
