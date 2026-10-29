// func_80614130 (src/global/17B90.c): stage 4; closest permuter result 1840; remaining scoped cache-entry lifetime and unsigned-count scheduling
void *func_80614130(s32 id) {
    s32 i;
    Perm3bEntry *entry;
    void *asset;

    if (id < 0) {
        return NULL;
    }
    entry = D_807FB7B0;
    for (i = 0; i < D_807FBB32; i++, entry++) {
        if (entry->id == id) {
            entry->refcount++;
            return entry->asset;
        }
    }
    if (D_807FBB32 >= 0x20) {
        return NULL;
    }
    asset = (void *)assetLoad(0xB, id, 1, 1);
    *(u16 *)((u8 *)asset + 6) += 6;
    entry->id = id;
    entry->asset = asset;
    entry->refcount++;
    D_807FBB32++;
    return asset;
}
