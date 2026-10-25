// func_807122B4 (src/global/114270.c): stage 4: target frame and saved-register set match; callback volume conversion, pointer-register choice, and control-flow scheduling differ
extern u8 D_80755264[];
extern void *D_807FD9F0[];
void assetFreeBuffer(void *, s32, s32);
void heapFreeDeferred(void *);

void *func_807122B4(void) {
    f64 var_ft1;
    s16 var_s0;
    void *var_v0;
    u8 *var_v1;

    var_v0 = D_807550E0;
    var_v1 = D_8077058C;
    if (*(u16 *)var_v0 != 0) {
        var_ft1 = (f64)*var_v1;
        *var_v1 = (u8)(u32)(var_ft1 * 0.9);
        renderCallbacksRegister((void *)func_80710CA0, NULL, 1);
        return NULL;
    }
    if (D_807FDA1C != 6) {
        *var_v1 = 0;
        heapFreeDeferred(*(void **)((u8 *)var_v0 + 4));
        var_s0 = 0;
        if ((s32)D_80755264[D_807FDA1C * 0x14] > 0) {
            do {
                assetFreeBuffer(D_807FD9F0[var_s0], 0x34A, 0x64);
                var_s0 += 1;
            } while (var_s0 < (s32)D_80755264[D_807FDA1C * 0x14]);
        }
        D_807FDA1C = 6;
        D_807FDA28 = 0;
        var_v0 = (void *)1;
    }
    return var_v0;
}
