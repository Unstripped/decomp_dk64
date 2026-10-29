// func_80688A6C (src/global/8D3E0.c): Stage 4: frame 0x60 vs 0x68, exact body control flow matches
typedef struct KaE_R3D3B_Container {
    s32 count;
    ActorListRecord items[1];
} KaE_R3D3B_Container;

void *assetLoad(s32, s32, s32, s32);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);
void *func_80610FE8(s32);
s32 func_80688C84(u16);
void modelAssetGetSubtables(s32, s32 *, s32 **);

extern s32 D_8076A0A8;
extern ActorListEntry4 *D_807FC5C4;
extern u8 D_807FC5C8;
extern s16 D_807FC408[];

void func_80688A6C(void) {
    void *sp48;
    KaE_R3D3B_Container *container;
    s32 count;
    s32 i;
    ActorListRecord *item;
    s32 var_s2;
    void *asset;
    s32 ret;

    asset = assetLoad(9, D_8076A0A8, 1, 1);
    D_807FC5C8 = 0;
    if (asset != NULL) {
        modelAssetGetSubtables((s32)asset, (s32 *)&sp48, (s32 **)&container);
        count = container->count;
        item = container->items;
    } else {
        count = 0;
    }
    for (i = 0; i < count; i++, item++) {
        if (func_80688C84(item->unk32 + 0x10) != 0) {
            D_807FC5C8++;
        }
    }
    if (D_807FC5C8 != 0) {
        D_807FC5C4 = func_80610FE8(D_807FC5C8 * sizeof(ActorListEntry4));
        D_807FC5C8 = 0;
        for (i = 0, var_s2 = 0; i < count; i++, item++) {
            ret = func_80688C84(item->unk32 + 0x10);
            if (ret != 0) {
                D_807FC5C4[D_807FC5C8].unk0 = item->unk34;
                D_807FC5C4[D_807FC5C8].unk2 = D_807FC408[D_8076A0A8] + var_s2 + 0x26B;
                var_s2 += ret;
                D_807FC5C8++;
            }
        }
        assetSetImmediateFree();
        assetFreeBuffer(asset, 0x1AA, 0x34);
    } else {
        D_807FC5C4 = NULL;
    }
}
