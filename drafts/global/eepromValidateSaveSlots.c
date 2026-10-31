// eepromValidateSaveSlots (src/global/104F0.c): stage 4: frame 0x98, callee-saved s0-s7/fp/ra, array offset 0x78; failed in  () via u8 and failed |= 1; remaining diff is loop pointer scheduling
#include <ultra64.h>

extern u32 eepromCalculateCrc32(u8 *arg0, u16 arg1);
extern void eepromClearSlotData();
extern s32 func_8060C6B8(s32, u8, u8, u8);
extern void func_8060C648(s32, s32, s32, u8, s32);
extern void func_8060CB74(void);
extern void eepromDispatchCommand(s32);
extern s16 D_807ECEA0[];
extern u8 D_807ECEA8[];
extern u8 D_807ED6A8[];
extern u8 D_807EDEA8[];
extern u8 D_807550C8;
extern u8 D_80744530;

void eepromValidateSaveSlots(void) {
    s32 i;
    s32 j;
    s32 version;
    s32 found;
    s32 height;
    s32 checksumIndex;
    u8 valid[4];
    u8 sectorOrder[4];
    u32 pad[4];
    u8 failed;

    failed = 0;
    memcpy(D_807ECEA8, D_807ED6A8, 0x800);
    i = 0;
    do {
        D_807EDEA8[i] = i;
        sectorOrder[i] = 0xFF;
        i++;
    } while (i < 4);
    height = (((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7;
    height /= 8;
    for (i = 0; i < 4; i++) {
        checksumIndex = (((i + 1) * height) / 4) - 1;
        valid[i] = 1;
        if (((u32 *)D_807ED6A8)[checksumIndex] != eepromCalculateCrc32(D_807ED6A8 + ((i * height) & 0xFFFF), (height - 4) & 0xFFFF)) {
            valid[i] = 0;
            eepromClearSlotData(i & 0xFF, 0);
            func_8060C648(0xF, 0, 0, i & 0xFF, 0xFF);
        }
        failed |= (valid[i] == 0);
    }
    for (i = 0; i < 4; i++) {
        if (valid[i] == 0 || func_8060C6B8(0xD, 0, 0, i & 0xFF) == 0) continue;
        version = func_8060C6B8(0xF, 0, 0, i & 0xFF);
        sectorOrder[i] = version;
        for (j = 0; j < 4 && sectorOrder[i] == version; j++) {
            if (j != i && valid[j] != 0 && func_8060C6B8(0xD, 0, 0, j & 0xFF) != 0 && func_8060C6B8(0xF, 0, 0, j & 0xFF) == version && func_8060C6B8(0x10, 0, 0, j & 0xFF) >= func_8060C6B8(0x10, 0, 0, i & 0xFF)) {
                sectorOrder[i] = 0xFF;
                eepromClearSlotData(i & 0xFF, 0);
                func_8060C648(0xF, 0, 0, i & 0xFF, 0xFF);
                failed |= 1;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        found = 0;
        for (j = 0; j < 4; j++) if (sectorOrder[j] == i) found = 1;
        if (found == 0) for (j = 0; j < 4 && found == 0; j++) if (sectorOrder[j] == 0xFF) {
            sectorOrder[j] = i;
            found = 1;
            func_8060C648(0xF, 0, 0, j & 0xFF, i);
        }
    }
    D_807EDEA8[1] = sectorOrder[1];
    D_807EDEA8[2] = sectorOrder[2];
    D_807EDEA8[3] = sectorOrder[3];
    D_807EDEA8[0] = sectorOrder[0];
    height = (((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F;
    height /= 8;
    checksumIndex = ((height + 0x40) / 4) - 1;
    if (((u32 *)D_807ED6A8)[checksumIndex] != eepromCalculateCrc32(D_807ED6A8 + (height & 0xFFFF), 0x3C)) {
        func_8060CB74();
        failed |= 1;
    }
    D_807550C8 = func_8060C6B8(0x1F, 0, 0, 0);
    D_80744530 = func_8060C6B8(0x20, 0, 0, 0);
    if (D_807550C8 > 0) {
        D_807550C8 = 0;
        func_8060C648(0x1F, 0, 0, 0, 0);
    }
    if (failed != 0) eepromDispatchCommand(1);
}
