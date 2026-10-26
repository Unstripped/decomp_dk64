// func_80614130 (src/global/17B90.c): stage 3: m2c reconstruction compiles; frame grows to 0x30 when preserving unsigned count, needs target 0x18 register allocation and load ordering
typedef struct {
    s32 id;
    s32 refcount;
    void *asset;
} P17bAssetCacheEntry;

extern P17bAssetCacheEntry D_807FB7B0[];
void *func_8066B0F8(s32, s32, s32, s32);

void *func_80614130(s32 arg0) {
    P17bAssetCacheEntry *entry;
    u16 count;
    u32 i;
    void *asset;

    if (arg0 < 0) {
        return NULL;
    }
    count = D_807FBB32;
    i = 0;
    if (count != 0) {
        entry = D_807FB7B0;
        do {
            i++;
            if (arg0 == entry->id) {
                entry->refcount++;
                return entry->asset;
            }
            entry++;
        } while (i < count);
    }
    if (count >= 0x20) {
        return NULL;
    }
    asset = func_8066B0F8(0xB, arg0, 1, 1);
    *(u16 *)((u8 *)asset + 6) += 6;
    entry = &D_807FB7B0[count];
    entry->refcount++;
    entry->asset = asset;
    D_807FBB32 = count + 1;
    entry->id = arg0;
    return asset;
}
