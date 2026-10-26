// func_80631C3C (src/global/36880.c): stage 6/text-identical, reloc only: zero loop 'for (i=0;i<8;i++) D_807F6150[i]=0' emits %lo(D_807F6150+0x10) (REL addend 0x10) vs expected %lo(D_807F6160) at 0x100/0x10c; every insn identical; needs ROM-hash check. Locals order/dummy 's32 x' required for stack layout (entries 0x58, sp54 0x54). do-while ptr loop 'p<D_807F6160' CSEs s4 hoist before loop (stage 5).
extern u8 D_80747D78;
extern s16 D_807F6150[];
u8 func_805FF030(u8, u8);
void *func_8066B0F8(s32, s32, s32, s32);
void func_80631F58(u8 *, u8 **, u8 **);
s32 func_80631EB8(u16);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);

void func_80631C3C(void) {
    s32 x;
    s32 i;
    void *asset;
    u8 *entries;
    u8 *sp54;
    u8 slot;
    s32 count;
    u8 *entry;
    s32 j;

    if (D_80747D78 == 0) {
        D_80747D78 = 1;
        for (i = 0; i < 8; i++) {
            D_807F6150[i] = 0;
        }
        for (i = 0; i != 0xDD; i++) {
            asset = func_8066B0F8(9, i, 1, 1);
            if (asset != NULL) {
                slot = func_805FF030(i, 1);
                func_80631F58(asset, &entries, &sp54);
                count = *(s32 *)entries;
                entry = entries + 4;
                for (j = 0; j < count; j++) {
                    if (func_80631EB8(*(u16 *)(entry + 0x28))) {
                        D_807F6150[slot]++;
                    }
                    entry += 0x30;
                }
                assetSetImmediateFree();
                assetFreeBuffer(asset, 0x10C, 7);
            }
        }
    }
}
