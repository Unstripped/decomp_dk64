// func_80626264 (src/global/201B0.c): stage 6 reached: text-identical, reloc only. Only diff: expected relocs name D_807476CC / D_807476D4 (asm data labels) where C emits D_807476C8+0x4 / D_807476D0+0x4 (u64 zero stores), plus .rodata jtbl naming. Needs ROM-hash check (paste via drafts.py paste).
void *func_8066B0F8(s32, s32, s32, s32);
void splineSetBasisTension(f32);
void assetFreeBuffer(void *, s32, s32);
void func_80625C30(void);

void func_80626264(void *arg0) {
    void *buf = func_8066B0F8(8, 0, 1, 1);

    splineSetBasisTension(0.5f);
    D_807476FC = &D_807F5B10;
    D_807F5CF4 = 0;
    D_807476C0 = NULL;
    D_80747704 = NULL;
    func_806261EC(arg0, D_807476FC, 1);
    func_806261EC(buf, D_80747700, 0);
    assetFreeBuffer(buf, 0x10B4, 0xC);
    func_80625C30();
    D_807476B4 = 0;
    D_807476B8 = 0;
    D_807476BC = 0;
    D_807F5CCC = 6.0f;
    if (D_807FBB64 & 1) {
        D_807F5CCC = 12.0f;
    }
    switch (D_8076A0A8) {
        case 0x4E:
        case 0x4F:
        case 0x83:
            D_807476B4 = 0x1E;
            break;
        case 0x25:
        case 0x29:
            D_807476B8 = 0x1F4;
            break;
        case 0x36:
            D_807476B8 = 0xFA;
            break;
        case 0x6E:
            D_807476B8 = 0x226;
            break;
        case 0xBA:
            D_807476B8 = 0xFA;
            break;
        case 0xBB:
        case 0xBC:
            D_807476B8 = 0x12C;
            break;
        case 0x27:
            D_807F5CCC = 10.0f;
            break;
        case 0x2D:
            D_807476BC = 0x78;
            break;
    }
    D_807476C8 = 0;
    D_807476D0 = 0;
}
