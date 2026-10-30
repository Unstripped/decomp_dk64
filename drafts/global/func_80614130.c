// func_80614130 (src/global/17B90.c): stage 5; closest permuter score 30; frame 0x20 vs 0x18 and a0/a2 swap in loop count
typedef struct {
    s32 id;
    s32 refCount;
    void *asset;
} RvE_CacheEntry;
extern RvE_CacheEntry D_807FB7B0[];
extern u16 D_807FBB32;
void *assetLoad(s32, s32, s32, s32);
void *func_80614130(s32 id) {
    s32 key = id;
    u16 count;
    u32 i;
    RvE_CacheEntry *entry;
    void *asset;
    int new_var;

    if (key < 0) {
        return NULL;
    }

    count = D_807FBB32;
    i = 0;
    if ((id = count) != 0) {
        entry = D_807FB7B0;
        do {
            if (key == entry->id) {
                entry->refCount++;
                return entry->asset;
            }
            entry++;
        } while (++i < (u32)id);
    }

    if (count >= 0x20) {
        return NULL;
    }

    new_var = 0xB;
    asset = assetLoad(new_var, key, 1, 1);
    *(u16 *)((u8 *)asset + 6) += 6;
    {
        u16 new_count = D_807FBB32;
        entry = &D_807FB7B0[new_count];
        entry->asset = asset;
        entry->refCount++;
        D_807FBB32 = new_count + 1;
        entry->id = key;
    }
    return asset;
}
