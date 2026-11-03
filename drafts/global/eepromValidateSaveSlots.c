// eepromValidateSaveSlots (src/global/104F0.c): Eep rev8: 42->5 (text 1: multu operand order; +4 reloc lines from D_807EDEA9..AB carve). Levers: tail E spelled out twice (off/idx locals), separate u32 hit local for loop 3, found = version = get(), ok=1 before chain, D_807ECEA8+0x800 for stored base. Remaining: multu s2,t9 (i+1 left) vs ours t9,s2
void eepromValidateSaveSlots(void) {
    s32 height;
    u8 found;
    u16 off;
    s32 i;
    u32 slot;
    u8 slot2;
    u16 len;
    u32 hit;
    u8 valid[4];
    u8 sectorOrder[4];
    s32 j;
    u16 idx;
    u32 ok;
    u32 stored;
    u8 *data;
    u8 failed;
    u8 version;
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
            if (eepromGetField(0xD, 0, 0, slot) != 0) {
            found = version = eepromGetField(0xF, 0, 0, slot);
            if (D_80744530) {}  // FAKE: steers uopt colouring order of found/version
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
        hit = 0;
        for (j = 0; j < 4 && hit == 0; j++) if (sectorOrder[j] == i) hit = 1;
        if (hit == 0) for (j = 0; j < 4 && hit == 0; j++) if (sectorOrder[j] == 0xFF) {
            sectorOrder[j] = i;
            hit = 1;
            eepromSetField(0xF, 0, 0, j, i);
        }
    }
    for (j = 0; j < 4; j++) {
        D_807EDEA8[j] = sectorOrder[j];
    }
    ok = 1;
    off = ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F)) / 8);
    idx = (((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F)) / 8) + 0x40) / 4 - 1;
    stored = ((u32 *)(D_807ECEA8 + 0x800))[idx];
    if (stored != (eepromCalculateCrc32(D_807ED6A8 + off, 0x3C) ^ 0)) {  // FAKE: keeps stored on the left of beql
        ok = 0;
        func_8060CB74();
    }
    failed |= (ok == 0);
    D_807550C8 = eepromGetField(0x1F, 0, 0, 0);
    if (i && i) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    D_80744530 = eepromGetField(0x20, 0, 0, 0);
    if (D_807550C8 > 0) {
        D_807550C8 = 0;
        eepromSetField(0x1F, 0, 0, 0, D_807550C8);
    }
    if (failed != 0) eepromDispatchCommand(1);
}
