// eepromValidateSaveSlots (src/global/104F0.c): W2Frame 2026-11-03 (revisit 7 wave 2): park 44 -> 42 (text 39 -> 37, reloc 6 = EDEA9/AA/AB names, shape 11). NEW: 'eepromClearSlotData((u8)slot & 0xFF, 0)' (both calls) emits the target's 'andi a0,s3,0xff' with the existing unprototyped decl (plain '(u8)slot' / 'slot & 0xFF' / (u8)(u32) give 'move a0,s3' or worse): no prototype change needed. Dropped the dead '| 0' on the stored load ('((u32 *)D_807ED6A8)[idx]', same score). Remaining: (1) multu s2,t9 vs t9,s2 (i+1 forms, dead tests on i+1 expressions: no effect), (2) loop-3 found s5/255 s6 vs s2/s5, (3) final block: target hi 'lui s1; addu s1,s1,t6; lw lo(s1)' + separate 'lui t7/addiu t7' crc base + a2 chain, ours one pointerized t9 + li s1,4; 6 spellings of the stored load x 6 of the crc base are all identical (42), anneal2 (dead tests, 2x10k evals) only reaches count-padding (+2 insn 'failed|0') with no real gain; ours is 2 lines shorter than the target in that block (real structure, not regalloc).
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
        ok = ok | 0;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
        if (stored != (eepromCalculateCrc32(data, len) ^ 0)) {  // FAKE: keeps stored on the left of beq
            ok = 0;
            slot = i;
            eepromClearSlotData((u8)slot & 0xFF, 0);
            eepromSetField(0xF, 0, 0, slot, 0xFF);
        }
        failed |= (ok == 0);
        valid[i] = ok;
    }
    ok = 0;
    version = 0;
    for (i = 0; i < 4; i++) {
        if (valid[i] != 0) {
            slot = i;
            if (version != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (eepromGetField(0xD, 0, 0, slot) != 0) {
            version = eepromGetField(0xF, 0, 0, slot);
            found = version;
            for (j = 0; j < 4 && found == version; j++) {
                if (j != i && valid[j] != 0) {
                    slot2 = j;
                    if (eepromGetField(0xD, 0, 0, slot2) != 0 && eepromGetField(0xF, 0, 0, slot2) == version && (u32)eepromGetField(0x10, 0, 0, slot) <= (u32)eepromGetField(0x10, 0, 0, slot2)) {
                        found = 0xFF;
                        eepromClearSlotData((u8)slot & 0xFF, 0);
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
    for (j = 0; j < 4; j++) {
        D_807EDEA8[j] = sectorOrder[j];
    }
    height = ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F)) / 8);
    if (version != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (j != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    ok = 1;
    stored = ((u32 *)D_807ED6A8)[(u16)(((height + 0x40) / 4) - 1)];
    if (stored != (eepromCalculateCrc32((u8 *)&D_807ED6A8[0] + (height & 0xFFFF), 0x3C) ^ 0)) {  // FAKE: keeps stored on the left of beql
        ok = 0;
        func_8060CB74();
    }
    if (i && found) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    failed |= (ok == 0);
    D_807550C8 = eepromGetField(0x1F, 0, 0, 0);
    D_80744530 = eepromGetField(0x20, 0, 0, 0);
    if (D_807550C8 > 0) {
        D_807550C8 = 0;
        eepromSetField(0x1F, 0, 0, 0, D_807550C8);
    }
    if (failed != 0) eepromDispatchCommand(1);
}
