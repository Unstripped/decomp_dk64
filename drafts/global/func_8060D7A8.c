// func_8060D7A8 (src/global/104F0.c): stage 4: 0x30 frame, callee-saved set (s0-s3, fs0, ra) and all arithmetic/control flow match; block-scoping slotQueueGetMaxValue return dropped diff to 140 lines; remaining diff is regalloc: s0 vs s2 for D_807FC950 and s1 vs s0 for entry in loop.
extern s32 flagGet(s32, s32);
extern s32 func_806F6EDC(void);
extern s32 slotQueueGetMaxValue(s32, s32);
extern u8 D_8074E77C;
extern u8 D_807FC950[];
extern u8 D_807FC952;

void func_8060D7A8(void) {
    u8 *entry;
    s32 i;

    if (func_806F6EDC() != 0) {
        s32 v = slotQueueGetMaxValue(5, 0);
        *(s16 *)(D_807FC950 + 0x2F6) = (s16)(u32)((f64)(u32)v * 0.5);
    }
    if (flagGet(0x184, 0) != 0) {
        s32 v = slotQueueGetMaxValue(4, 0);
        *(s16 *)(D_807FC950 + 0x2F4) = (s16)(u32)((f64)(u32)v * 0.5);
    }
    if (flagGet(0x179, 0) != 0) {
        s32 v = slotQueueGetMaxValue(6, 0);
        *(s16 *)(D_807FC950 + 0x2F8) = (s16)(u32)((f64)(u32)v * 0.5);
    }
    if (D_807FC952 != 0) {
        s32 v = slotQueueGetMaxValue(2, 0);
        *(s16 *)(D_807FC950 + 0x2F0) = (s16)(u32)((f64)(u32)v * 0.5);
    }
    entry = D_807FC950;
    i = 0;
    do {
        D_8074E77C = i;
        if (entry[4] != 0) {
            s32 v = slotQueueGetMaxValue(7, 0);
            *(s16 *)(entry + 8) = (s16)(u32)((f64)(u32)v * 0.5);
        }
        i++;
        entry += 0x5E;
    } while (i != 5);
    D_8074E77C = 0;
}
