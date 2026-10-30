// func_80613944 (src/global/17B90.c): stage 3: semantic C starter compiles; target uses 0x20 frame while C emits 0x28 frame due to local variable / argument slot differences
typedef struct {
    s32 unk0;
    s32 refCount;
    void *asset;
} RvE_CacheEntry;

typedef struct {
    u8 pad0[4];
    void *unk4;
    u8 pad8[0x7C];
    s32 unk84;
} RvE_AnimView;

extern RvE_CacheEntry D_807FB7B0[];
extern u16 D_807FBB32;
void assetFreeBuffer(void *, s32, s32);

void func_80613944(RvE_AnimView *arg0, void **arg1) {
    void *temp_a2;
    RvE_CacheEntry *entry;
    s32 i;
    u16 last_idx;
    RvE_CacheEntry *last;

    temp_a2 = *arg1;
    if (temp_a2 != NULL) {
        entry = D_807FB7B0;
        for (i = 0; i < (u16)D_807FBB32; i++, entry++) {
            if (temp_a2 == entry->asset) {
                if (--entry->refCount == 0) {
                    assetFreeBuffer(entry->asset, 0x298, 0x15);
                    last_idx = D_807FBB32 - 1;
                    last = &D_807FB7B0[last_idx];
                    D_807FBB32 = last_idx;
                    *entry = *last;
                    last->unk0 = 0xFFFF;
                    last->refCount = 0;
                    last->asset = NULL;
                }
                break;
            }
        }
        *arg1 = NULL;
    }
    if ((void *)arg1 == arg0->unk4->unk4) {
        arg0->unk4->unk84 = 0;
    }
}
