// eepromHalveRecords (src/global/104F0.c): stage 4: 1-insn diff: move s1,s0 vs lui/addiu s1,D_807FC950 at loop preheader; tested 7k+ spellings/dead tests/declarations
extern s32 flagGet(s32, s32);
extern s32 func_806F6EDC(void);
extern s32 slotQueueGetMaxValue(s32, s32);
extern u8 D_807FC950[];
extern u8 D_807FC952;
extern u8 gPlayerCharacterId;

void eepromHalveRecords(void) {
    s32 i;
    u8 *entry;

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
    if (gPlayerCharacterId && gPlayerCharacterId) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    i = 0; do { // LAYOUT:
        gPlayerCharacterId = i;
        if (entry[4] != 0) {
            s32 v = slotQueueGetMaxValue(7, 0);
            *(s16 *)(entry + 8) = (s16)(u32)((f64)(u32)v * 0.5);
        }
        i++;
        entry += 0x5E;
    } while (i != 5);
    gPlayerCharacterId = 0;
}
