// actorListInitOffsets (src/global/8D3E0.c): Stage 5: frame 0x70, 1-insn diff at 2f8 (addiu v0,t8,4; move s1,v0 vs addiu s1,t8,4)
extern u8 D_807500B0;
extern s16 D_807FC408[];

void *assetLoad(s32, s32, s32, s32);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);

typedef struct ActorListContainer {
    s32 count;
    ActorListRecord items[1];
} ActorListContainer;

void actorListInitOffsets(void) {
    char pad[12];
    void *sp60;
    ActorListContainer *container;
    s32 j;
    ActorListRecord *item;
    s32 count;
    u16 total;
    s32 i;
    void *temp_v0;

    total = 0;
    if (D_807500B0 == 0) {
        D_807500B0 = 1;
        for (i = 0; i < 0xDD; i++) {
            D_807FC408[i] = total;
            temp_v0 = assetLoad(9, i, 1, 1);
            if (temp_v0 != NULL) {
                modelAssetGetSubtables((s32)temp_v0, (s32 *)&sp60, (s32 **)&container);
                count = container->count;
                item = (ActorListRecord *)((s32 *)container + 1);
                for (j = 0; j < count; j++, item++) {
                    total += func_80688C84(item->unk32 + 0x10);
                }
                assetSetImmediateFree();
                assetFreeBuffer(temp_v0, 0x168, 0x34);
            }
        }
    }
}
