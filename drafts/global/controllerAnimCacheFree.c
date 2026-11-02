// controllerAnimCacheFree (src/global/17B90.c): UNPARKED 2026-11-02: park was 68 insns vs target 67 (count-inexact parks stay drafts); controllerAnimCacheFree (src/global/17B90.c): stage 5; frame 0x28 matches; score 25 (down from 26): count/last_idx via `*(u16 *)&D_807FBB32` + void* params to avoid prototype warnings; remaining: &D_807FBB32 colour t1 vs a3, count a3 vs a0 (extra count spill from the `count && count` dead test), spill slot 28 vs 24
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
    void *temp_a2 = *(void **)arg1;
    s32 i;
    struct AnimCacheEntry *entry;
    s32 count;
    s32 last_idx;
    struct AnimCacheEntry *last;

    if (D_807FBB32 && D_807FBB32) {} // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (temp_a2 != NULL) {
        count = *(u16 *)&D_807FBB32;
        entry = D_807FB7B0;
        i = 0;
        if (D_807FBB32 && D_807FBB32) {} // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (count > 0) {
            do {
                if (temp_a2 == entry->asset) {
                    if (--entry->refCount == 0) {
                        assetFreeBuffer(entry->asset, 0x298, 0x15);
                        if (count && count) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        last_idx = *(u16 *)&D_807FBB32 - 1;
                        last = &D_807FB7B0[(u16)last_idx];
                        D_807FBB32 = last_idx;
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
