// func_8060D7A8 (src/global/104F0.c): stage 4: D_807FC950 base is s2 while target uses s0, and loop pointer/counter registers are shifted. Tried local declaration reordering, early entry-base materialization, uopt tracing, and a 600-second permuter run; best score 573 but required moving entry advance outside the loop, so retained semantic baseline draft.
extern s32 flagGet(s32, s32);
extern s32 func_806F6EDC(void);
extern s32 func_806F8EDC(s32, s32);
extern u8 D_8074E77C;
extern u8 D_807FC950[];
extern u8 D_807FC952;

void func_8060D7A8(void) {
    s32 value;
    u8 *entry;
    s32 i;

    if (func_806F6EDC() != 0) {
        value = func_806F8EDC(5, 0);
        *(s16 *)(D_807FC950 + 0x2F6) = (s16)(u32)((f64)(u32)value * 0.5);
    }
    if (flagGet(0x184, 0) != 0) {
        value = func_806F8EDC(4, 0);
        *(s16 *)(D_807FC950 + 0x2F4) = (s16)(u32)((f64)(u32)value * 0.5);
    }
    if (flagGet(0x179, 0) != 0) {
        value = func_806F8EDC(6, 0);
        *(s16 *)(D_807FC950 + 0x2F8) = (s16)(u32)((f64)(u32)value * 0.5);
    }
    if (D_807FC952 != 0) {
        value = func_806F8EDC(2, 0);
        *(s16 *)(D_807FC950 + 0x2F0) = (s16)(u32)((f64)(u32)value * 0.5);
    }
    entry = D_807FC950;
    i = 0;
    do {
        D_8074E77C = i;
        if (entry[4] != 0) {
            value = func_806F8EDC(7, 0);
            *(s16 *)(entry + 8) = (s16)(u32)((f64)(u32)value * 0.5);
        }
        i++;
        entry += 0x5E;
    } while (i != 5);
    D_8074E77C = 0;
}
