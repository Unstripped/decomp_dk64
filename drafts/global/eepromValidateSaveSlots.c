// eepromValidateSaveSlots (src/global/104F0.c): Eep 2026-11-02: stage 4 (count-inexact: 319 insns vs target 315, frame 0x98 exact): deadsweep score 61 (full; text 51, reloc 10 = EDEA9/AA/AB names) vs stored 64. Changes: D_807EDEA9/AA/AB/A8 stores as 'for (j = 0; j < 4; j++) D_807EDEA8[j] = sectorOrder[j];' (text 55->51), 3 redundant FAKEs dropped. Count gap is the 4 sb stores: target shares ONE lui at for all four (only reproduced when D_807EDEA8[4] is DEFINED in the TU: score 47, 316 insns; needs a .bss carve, yaml not editable), ours emits lui+sb each; plus slti/bnezl vs li at,4/bnel on loop3 and nop after func_8060CB74 delay slot. Remaining: multu s2,t9 vs t9,s2 (i+1 left), beq s1,v0 vs v0,s1 crc compare, andi a0,s3,0xff vs move a0,s3 at clearSlot calls, loop4 flag regs s7/s5 vs s5/s2. Tried: copy local n=i+1 (171), slot u8/(slot & 0xFF) (88-97), mult operand spellings (no change), 4 loop-bound spellings x4 loops, stored index spellings, array/pointer/discrete store spellings, random dead-test hill climb 35k evals (no gain)
void eepromValidateSaveSlots(void) {
    s32 j;
    u32 slot;
    u16 len;
    u8 found;
    u8 slot2;
    u16 idx;
    s32 i;
    u8 version;
    u8 valid[4];
    u8 sectorOrder[4];
    u8 *data;
    s32 height;
    u32 stored;
    u32 ok;
    u32 padarr[1];
    u16 off;
    u8 failed;
    failed = 0;
    ok = 0;
    memcpy(D_807ECEA8, D_807ED6A8, 0x800);
    for (i = 0; i < 4; i++) {
        if (i && stored) {}  // FAKE
        D_807EDEA8[i] = i;
        sectorOrder[i] = 0xFF;
    }
    for (i = 0; i < 4; i++) {
        ok = 1;
        off = ((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7)) / 8) * i;
        data = off + D_807ED6A8;
        idx = ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7)) / 8) * (i + 1)) / 4) - 1;
        stored = ((u32 *)D_807ED6A8)[idx];
        len = ((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7)) / 8) - 4;
        if (stored != eepromCalculateCrc32(data, len)) {
            ok = 0;
            slot = i;
            eepromClearSlotData((u8)slot, 0);
            eepromSetField(0xF, 0, 0, slot, 0xFF);
        }
        failed |= (ok == 0);
        valid[i] = ok;
    }
    ok = 0;
    version = 0;
    for (i = 0; i < 4; i++) {
        if (version != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (valid[i] != 0) {
            slot = i;
            if (eepromGetField(0xD, 0, 0, slot) != 0) {
            version = eepromGetField(0xF, 0, 0, slot);
            found = version;
            for (j = 0; j < 4 && found == version; j++) {
                if (j != i && valid[j] != 0) {
                    slot2 = j;
                    if (eepromGetField(0xD, 0, 0, slot2) != 0 && eepromGetField(0xF, 0, 0, slot2) == version && (u32)eepromGetField(0x10, 0, 0, slot) <= (u32)eepromGetField(0x10, 0, 0, slot2)) {
                        found = 0xFF;
                        eepromClearSlotData((u8)slot, 0);
                        eepromSetField(0xF, 0, 0, slot, 0xFF);
                        failed |= 1;
                    }
                }
            }
            sectorOrder[i] = found;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        found = 0;
        for (j = 0; j < 4 && found == 0; j++) if (sectorOrder[j] == i) found = 1;
        if (found == 0) for (j = 0; j < 4 && found == 0; j++) if (sectorOrder[j] == 0xFF) {
            sectorOrder[j] = i;
            found = 1;
            eepromSetField(0xF, 0, 0, j, i);
        }
    }
    if (failed == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    for (j = 0; j < 4; j++) {
        D_807EDEA8[j] = sectorOrder[j];
    }
    height = ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F)) / 8);
    ok = 1;
    stored = ((u32 *)((u32)D_807ED6A8 | 0))[(u16)(((height + 0x40) / 4) - 1)];
    if (stored != eepromCalculateCrc32((u8 *)&D_807ED6A8[0] + (height & 0xFFFF), 0x3C)) {
        func_8060CB74();
        ok = 0;
    }
    if (i && found) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    failed |= (ok == 0);
    if (version != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    D_807550C8 = eepromGetField(0x1F, 0, 0, 0);
    D_80744530 = eepromGetField(0x20, 0, 0, 0);
    if (D_807550C8 > 0) {
        D_807550C8 = 0;
        eepromSetField(0x1F, 0, 0, 0, D_807550C8);
    }
    if (failed != 0) eepromDispatchCommand(1);
}
