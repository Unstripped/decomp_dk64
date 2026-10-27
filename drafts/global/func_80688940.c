// func_80688940 (src/global/8D3E0.c): frame 0x70, slots 0x5C/0x60 and s0-s8 match; char pad[12]; addu and branch delay slot scheduling diff
typedef struct R3D3B_Container {
    s32 count;
    ActorListRecord items[1];
} R3D3B_Container;

s32 func_8066B0F8(s32, s32, s32, s32);
void func_8066B424(void);
void func_8066B434(s32, s32, s32);
void modelAssetGetSubtables(void *, void *, void *);
s32 func_80688C84(u16);
extern u8 D_807500B0;
extern s16 D_807FC408[];

void func_80688940(void) {
    char pad[12];
    void *sp60;
    R3D3B_Container *container;
    s32 j;
    ActorListRecord *item;
    s32 count;
    s32 total;
    s32 i;
    s32 temp_v0;

    if (D_807500B0 == 0) {
        total = 0;
        D_807500B0 = 1;
        for (i = 0; i < 0xDD; i++) {
            D_807FC408[i] = total;
            temp_v0 = func_8066B0F8(9, i, 1, 1);
            if (temp_v0 != 0) {
                modelAssetGetSubtables((void *)temp_v0, &sp60, &container);
                count = container->count;
                for (j = 0, item = container->items; j < count; j++, item++) {
                    total = (total + func_80688C84(item->unk32 + 0x10)) & 0xFFFF;
                }
                func_8066B424();
                func_8066B434(temp_v0, 0x168, 0x34);
            }
        }
    }
}
