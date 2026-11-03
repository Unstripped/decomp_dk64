// controllerAnimCacheFree (src/global/17B90.c): W3IntA wave3 (2026-11-02): stage 5, park score 2 unchanged (only 'sh t2,0(a3)' 3 slots early). Findings: (1) var form 'last=&T[(u16)(D-1)]; tid=last->id; D-=1; entry->id=tid;' gives the exact target ORDER (lw t6 / li / sh / sw) but tid becomes a coloured var (+2 insns, a1/a0 regs, arg1 promoted to a3, 19); (2) store AFTER 'last' with E-1 CSE'd (no var: 'last=&T[(u16)(*(u16*)&D-1)]; *(u16*)&D-=1; entry->id=last->id') is count-exact (76) once D's address candidate has >=4 refs (add 'if (*(u16*)&D == 0) {}' after the store; else arg1 takes a3 and D goes to t0) but E-1 is then a coloured a0 web (29) and sh still lands before 'lw v1,24(sp)'; (3) ugen emits '.noalias $last,$D' (which lets as1 sink the sh after the first load) in FreeSub's var form but never in this function; moving the sh record in t.G (single moves 454->455..479) never reaches 0; comma/(u16)(D-=1)/--D/D-- forms, R/L/T/P comma-in-LHS forms, 648 tid types x positions, 4.8k store-position x dead-test grid all >= 10.
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
