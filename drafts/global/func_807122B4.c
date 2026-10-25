// func_807122B4 (src/global/114270.c): stage 4: frame and saved-register set match; (f64)(u32) volume emits the target's single unsigned-conversion fixup, but pointer-register allocation and block scheduling differ
extern u8 D_80755264[];
extern void *D_807FD9F0[];
void assetFreeBuffer(void *, s32, s32);
void heapFreeDeferred(void *);

void *func_807122B4(void) {
    f64 volume;
    s16 i;
    void *queue;

    queue = D_807550E0;
    if (*(u16 *)queue != 0) {
        volume = (f64)(u32)D_8077058C[0];
        D_8077058C[0] = (u8)(u32)(volume * 0.9);
        renderCallbacksRegister((void *)func_80710CA0, NULL, 1);
        return NULL;
    }
    if (D_807FDA1C != 6) {
        D_8077058C[0] = 0;
        heapFreeDeferred(*(void **)((u8 *)queue + 4));
        i = 0;
        if ((s32)D_80755264[D_807FDA1C * 0x14] > 0) {
            do {
                assetFreeBuffer(D_807FD9F0[i], 0x34A, 0x64);
                i += 1;
            } while (i < (s32)D_80755264[D_807FDA1C * 0x14]);
        }
        D_807FDA1C = 6;
        D_807FDA28 = 0;
        queue = (void *)1;
    }
    return queue;
}
