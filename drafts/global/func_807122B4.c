// func_807122B4 (src/global/114270.c): Baseline cleanup reconstruction; control-flow scheduling and rodata ownership differ.
typedef struct M114aQueue {
    u16 unk0;
    u16 pad2;
    void *unk4;
} M114aQueue;

extern u16 *D_807550E0;
extern u8 D_80755264[];
extern u8 D_8077058C[];
extern void *D_807FD9F0[];
extern u8 D_807FDA1C;
extern u8 D_807FDA28;
void assetFreeBuffer(void *, s32, s32);
void heapFreeDeferred(void *);
void renderCallbacksRegister(void *, void *, s32);
void func_80710CA0(void);

void *func_807122B4(void) {
    f64 var_ft1;
    s16 var_s0;
    M114aQueue *var_v0;

    var_v0 = (M114aQueue *)D_807550E0;
    if (var_v0->unk0 != 0) {
        var_ft1 = (f64)D_8077058C[0];
        if ((s32)D_8077058C[0] < 0) {
            var_ft1 += 4294967296.0;
        }
        D_8077058C[0] = (u8)(u32)(var_ft1 * 0.9);
        renderCallbacksRegister((void *)func_80710CA0, NULL, 1);
        return NULL;
    }
    if (D_807FDA1C != 6) {
        D_8077058C[0] = 0;
        heapFreeDeferred(var_v0->unk4);
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
