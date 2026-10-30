// func_80613944 (src/global/17B90.c): stage 5; frame 0x28 matches target; score 29 after deadsweep; struct member copy order matches (id, asset, refCount)
typedef struct {
    s32 id;
    s32 refCount;
    void *asset;
} RvT1_CacheEntry;
extern RvT1_CacheEntry D_807FB7B0[];
extern s16 D_807FBB32;
void assetFreeBuffer(void *, s32, s32);

typedef struct {
    void *unk0;
    void *unk4;
    void *unk8;
    void *unkC;
} ControllerAnimData;

typedef struct {
    void *unk0;
    ControllerAnimData *unk4;
} ControllerAnimView;

typedef struct {
    u8 pad0[0x84];
    s32 unk84;
} RvT1_AnimData;

int func_80613944(ControllerAnimView *arg0, void **arg1) {
    void *temp_a2 = *arg1;
    s32 i;
    RvT1_CacheEntry *entry;
    s32 count;
    s32 last_idx;
    RvT1_CacheEntry *last;

    if (D_807FBB32 && D_807FBB32) {} // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (temp_a2 != NULL) {
        count = (u16)D_807FBB32;
        entry = D_807FB7B0;
        i = 0;
        if (D_807FBB32 && D_807FBB32) {} // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (count > 0) {
            do {
                if (temp_a2 == entry->asset) {
                    if (--entry->refCount == 0) {
                        assetFreeBuffer(entry->asset, 0x298, 0x15);
                        last_idx = D_807FBB32 - 1;
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
        *arg1 = NULL;
    }
    if ((void *)arg1 == arg0->unk4->unk4) {
        ((RvT1_AnimData *)arg0->unk4)->unk84 = 0;
    }
}
