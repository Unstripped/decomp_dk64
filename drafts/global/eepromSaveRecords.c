// eepromSaveRecords (src/global/104F0.c): Eep 2026-11-03 (revisit 7): stage 4, parked unchanged, deadsweep full 26 (text 27, reloc 0), 296 insns = target, frame 4216 exact. Diff clusters: (a) then-arm chain: target 'li at,-64/-8/-64' (three separate uncoloured const webs, ring temps, no andi), ours '(u16)offset' andi + s3 hoisted web; needs e1/e3 constants as non-s3, non-merged webs: all-unsigned chain merges e1/e3 into one coloured v1 web (count 339), grid over 5760 cast/const spellings (~0x3FU/0xFFFFFFC0/-0x40/L/UL, u16/u32 casts) and dead tests between the statements gave nothing below 26; (b) merge-b coloured s0 vs target s2 (b var vs expression piece 90); (c) memcpy delay slot: target 'move s4,s1' (sector copy) in the jal slot and 'slti at,s4,256' unnarrowed guard + 'andi s2,s1,0xffff' idx init in the beqz slot; ours 'andi t6,s1,0xffff; slti' - tried u16 sector (spills sh 4210(sp), adjsave<0), start/sc2 copies, idx init/inc/guard spellings (u16/s32/u32 x 4 inits x 3 incs x 2 guards): no gain; (d) decl-order hill-climb 6.4k evals: no gain. Dead tests on locals anywhere in this function cost +7 insns.
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
            offset = ((u16)offset & ~0x3F) + 0x27;
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
        ((u32 *)workingData)[b] = eepromCalculateCrc32(a + workingData, 0x3C);
        bzero(strlen(D_807467C0) - (0x800 - ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) + workingData + 0x840, (0x800 - ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) - strlen(D_807467C0) - 0x40);
        if (D_807ECEA0) {}  // FAKE: deadsweep dead statement (steers uopt)
        osWritebackDCacheAll();
        memcpy(D_807ED6A8 + sector * 8, workingData + sector * 8, 0x800 - (sector << 3));
        if (D_807ECD08[0] != 0) do sleepMilliseconds(1.0f); while (*p != 0);
        if (D_807ECD08 && D_807ECD08) {}  // FAKE: colours the polled D_807ECD08 address candidate
        if (D_80744460 != 0) {
            D_807467C4 = 0;
        } else {
            D_807467C4 = 1;
            for (idx = sector; idx < 0x100; idx += 2) {
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
