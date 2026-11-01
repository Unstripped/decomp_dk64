// eepromSaveRecords (src/global/104F0.c): stage 4: recovered 4-word comparison, D_80744460 early exit, double strlen and sp5C caching; remaining diff is regalloc/stack layout
extern s32 _sprintf();
extern s32 eepromCalculateCrc32();
extern void eepromCopySlot(void);
extern void sleepMilliseconds(f32);
extern char *D_807467C0;
extern s8 D_807467C4;
extern s8 D_807467E4;
extern f32 D_807467E8;
extern s8 D_80744460;
extern u8 D_807ECD08[];
extern s32 D_807EDEAC;
extern OSMesgQueue D_807ECCF0;
extern s16 D_807ECEA0[];
extern u8 D_807ECEA8[];
extern u8 D_807ED6A8[];

void eepromSaveRecords(s32 arg0) {
    s32 i;
    s32 textOffset;
    s32 offset;
    s32 sector;
    s32 dataLength;
    s32 height;
    u8 savedData[0x800];
    u8 workingData[0x800];
    u8 *sp5C;
    s32 after_1;
    s32 after_2;

    if (D_807EDEAC != 2) return;
    textOffset = (((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F;
    textOffset = (textOffset + 0x207) & ~7;
    textOffset /= 8;
    _sprintf((char *)D_807ECEA8 + textOffset, D_807467C0);
    memcpy(workingData, D_807ECEA8, 0x800);
    memcpy(savedData, D_807ED6A8, 0x800);
    if (arg0 == 0) {
        eepromCopySlot();
        for (i = 0; i < 4; i++) {
            height = (((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7;
            height /= 8;
            ((u32 *)workingData)[(((i + 1) * height) / 4) - 1] = eepromCalculateCrc32(workingData + ((i * height) & 0xFFFF), (height - 4) & 0xFFFF);
        }
        sector = 0;
        offset = (((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F;
        offset /= 8;
    } else {
        offset = (((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F;
        offset /= 8;
        sector = offset & 0xFFFF;
    }
    ((u32 *)workingData)[((offset + 0x40) / 4) - 1] = eepromCalculateCrc32(workingData + (offset & 0xFFFF), 0x3C);
    strlen(D_807467C0);
    bzero(workingData + strlen(D_807467C0) + offset + 0x40, 0x800 - offset - strlen(D_807467C0) - 0x40);
    osWritebackDCacheAll();
    memcpy(D_807ED6A8 + sector * 8, workingData + sector * 8, 0x800 - sector * 8);
    if (D_807ECD08[0] != 0) do sleepMilliseconds(1.0f); while (*sp5C != 0);
    if (D_80744460 == 0) {
        D_807467C4 = 1;
        for (sector &= 0xFFFF; sector < 0x100; sector += 2) {
            D_807467E4 = 0x1E;
            D_807467E8 = (f32)sector * 0.00390625f;
            if (((u32 *)(savedData + sector * 8))[0] != ((u32 *)(workingData + sector * 8))[0] ||
                ((u32 *)(savedData + sector * 8))[1] != ((u32 *)(workingData + sector * 8))[1] ||
                ((u32 *)(savedData + sector * 8))[2] != ((u32 *)(workingData + sector * 8))[2] ||
                ((u32 *)(savedData + sector * 8))[3] != ((u32 *)(workingData + sector * 8))[3]) {
                for (i = 0; i < 2; i++) {
                    if (D_80744460 != 0) {
                        D_807467C4 = 0;
                        return;
                    }
                    osEepromWrite(&D_807ECCF0, (sector + i) & 0xFF, workingData + (sector + i) * 8);
                    sleepMilliseconds(15.0f);
                }
            }
        }
        D_807467C4 = 0;
    }
}
