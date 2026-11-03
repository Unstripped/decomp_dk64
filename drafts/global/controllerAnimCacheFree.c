// controllerAnimCacheFree (src/global/17B90.c): Revisit 7 (Ctrl 2026-11-03): stage 5, park score 2 unchanged ('sh t2,0(a3)' 3 slots early). NEW: declaring D_807FBB32 as u16 (extern s16 in 17B90.c/7CA80.c; whole 17B90.c still TEXT OK with u16) makes the casts unnecessary: 'count = D_807FBB32; ... D_807FBB32--; last = &D_807FB7B0[D_807FBB32];' scores the same 2 with the natural spelling (grid 384: dec form x last form x dec position x count form; all 2, none lower). Same ugen stream as the park: as1 keeps 'sh' before 'addu v0' because ugen emits no '.noalias $last,$D' (the D store precedes the last pointer in ucode). Tried: store-after-last with (u16)(E-1) / E-1U / E+-1 spellings (>=12), idx var x types x store slots (>=33, D pointerised differently), tid reused from count/i/new local (>=20), struct copy *entry=*last (uses at; order 0,4,8, not the target 0,8,4), 256 pair-joins of the tail statements onto one line (no effect on scheduling).
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
