// func_80688A6C (src/global/8D3E0.c): frame 0x68 matches; variable offset differences in loop
typedef struct R3D3B_Container {
    s32 count;
    ActorListRecord items[1];
} R3D3B_Container;

extern s32 D_8076A0A8;
extern ActorListEntry4 *D_807FC5C4;
extern u8 D_807FC5C8;
extern s16 D_807FC408[];

void *func_80610FE8(s32);
s32 func_80688C30(u16);
s32 func_80688C84(u16);
s32 func_8066B0F8(s32, s32, s32, s32);
void func_8066B424(void);
void func_8066B434(s32, s32, s32);
void func_80631F58(void *, void *, void *);

void func_80688A6C(void) {
    void *sp48;
    R3D3B_Container *container;
    s32 count;
    s32 i;
    ActorListRecord *item;
    s32 var_s2;
    s32 temp_v0;
    s32 ret;

    var_s2 = D_8076A0A8;
    ret = func_80688C30(var_s2);
    if (ret != -1) {
        temp_v0 = func_8066B0F8(9, ret, 1, 1);
        if (temp_v0 != 0) {
            func_80631F58((void *)temp_v0, &sp48, &container);
            count = container->count;
            item = container->items;
            for (i = 0; i < count; i++, item++) {
                if (func_80688C84(item->unk32 + 0x10) != 0) {
                    D_807FC5C4[D_807FC5C8].unk0 = item->unk34;
                    D_807FC5C4[D_807FC5C8].unk2 = D_807FC408[D_8076A0A8] + var_s2 + 0x26B;
                    var_s2 += temp_v0;
                    D_807FC5C8 += 1;
                }
            }
            func_8066B424();
            func_8066B434(temp_v0, 0x1AA, 0x34);
        } else {
            D_807FC5C4 = NULL;
        }
    } else {
        D_807FC5C4 = NULL;
    }
}
