// controllerAnimCacheFree (src/global/17B90.c): W2Tiny 2026-11-03: stage 5 park score 2 unchanged ('sh t2,0(a3)' 3 slots early). as1 sinks sh past 'lw t6,0(v0)' only if ugen emitted '.noalias $last,$D' (D ptr $7 still live at the first mem op through the last pointer: ucode order lw last->id, sh D, sw entry->id); no C spelling made that. Grids: 1232 (s16/u16 D x idx var i/count/idx x E-1 spellings x last forms x D store forms x order LS/SL x direct) all >=22 except the park; 'dec at end' with shared (u16)(D-1) loses the CSE (16/29); local tid=last->id between last= and the D store / comma forms / asset-first order (>=8; 'id_local' 18, sh still early; tid coloured not ring).
typedef struct {
    void *unk0;
    void *unk4;
    void *unk8;
    void *unkC;
} ControllerAnimDataView;

typedef struct {
    void *unk0;
    ControllerAnimDataView *unk4;
} ControllerAnimRefView;

typedef struct {
    u8 pad0[0x84];
    s32 unk84;
} ControllerAnimDataBlock;


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
    if ((void *)arg1 == ((ControllerAnimRefView *)arg0)->unk4->unk4) {
        ((ControllerAnimDataBlock *)((ControllerAnimRefView *)arg0)->unk4)->unk84 = 0;
    }
}
