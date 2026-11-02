// eepromSaveRecords (src/global/104F0.c): UNPARKED 2026-11-02: park was 297 insns vs target 296 (count-inexact parks stay drafts); eepromSaveRecords (src/global/104F0.c): stage 4: 57 insns diff (was 261): frame/callee-saved exact; remaining: then-branch masks (-64/-8 li at vs s3/s4 webs), crc loop addu a0,v1,s5 operand order, 0x800 held in s2 in target (ours rematerialised), sector copy move s4,s1/andi s2 delay slot, write-loop ring temps shifted by 2; needs 6 dead tests
void eepromSaveRecords(s32 arg0) {
    s32 j;
    s32 sector;
    s32 offset;
    s32 height;
    u16 idx;
    u16 a;
    u16 b;
    u8 i;
    u8 workingData[0x800];
    u8 savedData[0x800];
    u8 *p;
    p = D_807ECD08;
    if (D_807EDEAC == 2) {
        _sprintf((char *)D_807ECEA8 + ((((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) + 0x207) & ~7) / 8), D_807467C0);
        memcpy(workingData, D_807ECEA8, 0x800);
        memcpy(savedData, D_807ED6A8, 0x800);
        if (arg0 == 0) {
            eepromCopySlot();
            for (i = 0; i < 4; i++) {
                height = ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7);
                height /= 8;
                
                a = i * height;
                if (a) {}  // FAKE: live range / colouring of the narrowed index temp
                b = (((i + 1) * height) / 4) - 1;
                ((u32 *)workingData)[b] = eepromCalculateCrc32(a + workingData, height - 4);
            }
            sector = 0;
            offset = D_807ECEA0[0];
            offset += 0x6B7;
            offset = (s32)((u16)offset & ~0x3F) + 0x27;
            offset = ((s32)(offset & ~7U) * 4) + 0x3F;
            offset = (s32)(offset & ~0x3FU);
            offset /= 8;
        } else {
            offset = (((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F);
            offset /= 8;
            sector = (offset / 8) & 0xFFFF;
        }
        a = offset;
        if (a) {}  // FAKE: live range / colouring of the narrowed index temp
        b = ((offset + 0x40) / 4) - 1;
        if (b) {}  // FAKE: live range / colouring of the narrowed index temp
        ((u32 *)workingData)[b] = eepromCalculateCrc32(workingData + a, 0x3C);
        bzero(strlen(D_807467C0) - (0x800 - ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) + workingData + 0x840, (0x800 - ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) - strlen(D_807467C0) - 0x40);
        if (D_807ECEA0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        osWritebackDCacheAll();
        if (D_807ED6A8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        memcpy(D_807ED6A8 + sector * 8, workingData + sector * 8, 0x800 - (sector << 3));
        if (D_807ECD08[0] != 0) do sleepMilliseconds(1.0f); while (*p != 0);
        if (D_80744460 != 0) {
            D_807467C4 = 0;
        } else {
            D_807467C4 = 1;
            if (b == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            for (idx = sector; idx < 0x100; idx += 2) {
                if (b == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                D_807467E4 = 0x1E;
                D_807467E8 = (f32)(u32)idx * 0.00390625f;
                if (((u64 *)savedData)[idx] != ((u64 *)workingData)[idx] ||
                    ((u64 *)savedData)[idx + 1] != ((u64 *)workingData)[idx + 1]) {
                    for (j = 0; j < 2; j++) {
                        if (D_80744460 != 0) {
                            D_807467C4 = 0;
                            return;
                        }
                        osEepromWrite(&D_807ECCF0, idx + j, workingData + idx * 8 + j * 8);
                        sleepMilliseconds(15.0f);
                    }
                }
            }
            D_807467C4 = 0;
        }
    }
}
