// func_80688940 (src/global/8D3E0.c): regalloc: s3/s4 swapped, stack slot 0x5c vs 0x60
s32 func_8066B0F8(s32, s32, s32, s32);
void func_8066B424(void);
void func_8066B434(s32, s32, s32);
void func_80631F58(void *, void *, void *);
s32 func_80688C84(u16);

extern u8 D_807500B0;
extern s16 D_807FC408[];

void func_80688940(void) {
    void *sp60;
    ActD3A_Container *container;
    s32 j;
    ActD3A_Sub38 *item;
    s32 count;
    u16 total;
    s32 i;
    s32 temp_v0;

    total = 0;
    if (D_807500B0 == 0) {
        D_807500B0 = 1;
        for (i = 0; i < 0xDD; i++) {
            D_807FC408[i] = total;
            temp_v0 = func_8066B0F8(9, i, 1, 1);
            if (temp_v0 != 0) {
                func_80631F58((void *)temp_v0, &sp60, &container);
                count = container->count;
                item = container->items;
                for (j = 0; j < count; j++, item++) {
                    total = func_80688C84(item->unk32 + 0x10) + total;
                }
                func_8066B424();
                func_8066B434(temp_v0, 0x168, 0x34);
            }
        }
    }
}
