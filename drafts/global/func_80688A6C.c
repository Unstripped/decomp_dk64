// func_80688A6C (src/global/8D3E0.c): stage 5 (near-miss): frame 0x68 matches (pad[2] at end of locals), deadsweep full=18 text=14 shape=17
typedef struct KaS1_R3D3B_Container {
    s32 count;
    ActorListRecord items[1];
} KaS1_R3D3B_Container;

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
    s32 count;
    s32 i;
    s32 ret;
    s32 pad[2];
    ActorListRecord *items;
    void *asset;
    void *sp48;
    KaS1_R3D3B_Container *container;
    ActorListRecord *item;
    s32 var_s2;

    asset = assetLoad(9, D_8076A0A8, 1, 1);
    D_807FC5C8 = 0;
    if (asset != NULL) {
        modelAssetGetSubtables((s32)asset, (s32 *)&sp48, (s32 **)&container);
        count = container->count;
        items = container->items;
    } else {
        count = 0;
    }
    if (count > 0) {
        i = 0;
        item = items;
        do {
            if (func_80688C84(item->unk32 + 0x10) != 0) {
                D_807FC5C8++;
            }
            i++;
            item++;
        } while (i != count);
    }
    if (D_807FC5C8) {
        D_807FC5C4 = func_80610FE8(D_807FC5C8 * sizeof(ActorListEntry4));
        i = 0;
    } else {
        D_807FC5C4 = NULL;
        return;
    }
    D_807FC5C8 = 0;
    if (count > 0) {
        var_s2 = 0;
        item = items;
        do {
            ret = func_80688C84(item->unk32 + 0x10);
            if (ret != 0) {
                D_807FC5C4[D_807FC5C8].unk0 = item->unk34;
                D_807FC5C4[D_807FC5C8].unk2 = ((u16 *)D_807FC408)[D_8076A0A8] + var_s2 + 0x26B;
                var_s2 += ret;
                D_807FC5C8++;
            }
            i++;
            item++;
        } while (i != count);
    }
    assetSetImmediateFree();
    assetFreeBuffer(asset, 0x1AA, 0x34);
}
