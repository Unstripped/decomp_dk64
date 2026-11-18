#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "proto/boot/3630.h"
#include "proto/boot/3D20.h"
#include "proto/global/104F0.h"
#include "proto/global/10D2D0.h"
#include "proto/global/117190.h"
#include "proto/global/135D30.h"
#include "proto/global/36880.h"
#include "proto/global/450.h"
#include "proto/global/CC800.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"

s16 D_807ECEA0; // every access is lh/sh at displacement 0; IDO 8-aligns the 0x800-byte buffer after it
u8 sEepromSlotBuffer[0x800];
u8 sEepromImage[0x800];
u8 gEepromSectorSlot[4];
s32 D_807EDEAC;
extern u8 gEepromCurrentSlot;


void eepromInitModelCount(void) {
    s32 i;

    D_807ECEA0 = 0;
    for (i = 0; i != 8; i++) {
        D_807ECEA0 += modelTypeCountGet(i);
    }
}

extern s8 D_80746834;
extern OSMesgQueue D_807EE0D0;

void sleepMilliseconds(f32 ms) {
    OSTimer timer;
    u64 pad;
    OSMesg timerMsg;
    OSMesg received;
    u64 duration;

    duration = (u64)(ms * 1000.0f);
    duration = (duration * 3000) / 64;
    osSetTimer(&timer, duration, 0, &D_807EE0D0, timerMsg);
    D_80746834 = 1;
    osRecvMesg(&D_807EE0D0, &received, 1);
    D_80746834 = 0;
}

extern s8 gMainThreadHalted;
extern void (*D_807467D0[])(void);
extern OSMesgQueue D_807F02B8;

void eepromDispatchCommand(s32 cmd) {
    if (osGetThreadId(NULL) == 9) {
        D_807467D0[cmd]();
        return;
    }
    if (gMainThreadHalted == 0) {
        osSendMesg(&D_807F02B8, (void *)cmd, 0);
    }
}




extern u32 D_807463C0[];

u32 eepromCalculateCrc32(u8 *data, u16 length) {
    u32 crc = ~0;

    while (length--) {
        crc = D_807463C0[(*data++ ^ crc) & 0xFF] ^ (crc >> 8);
    }
    return crc ^ -1;
}


u8 eepromGetSectorForSlot(s32 slot) {
    u8 i;

    for (i = 0; i < 4; i++) {
        if (slot == gEepromSectorSlot[i]) {
            return i;
        }
    }
    return 0;
}



void eepromCopySlot(void) {
    u8 original;
    u8 replacement;
    u8 *src;
    u8 *dst;

    original = eepromGetSectorForSlot(gEepromCurrentSlot);
    replacement = eepromGetSectorForSlot(3);
    if (((menuIsTransitionType6() != 0) || (menuIsTransitionType7Or9() != 0)) && (original != replacement)) {
        src = &sEepromSlotBuffer[(((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8) * original];
        dst = &sEepromSlotBuffer[(((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8) * replacement];
        memcpy(dst, src, ((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8);
        gEepromSectorSlot[replacement] ^= gEepromSectorSlot[original];
        gEepromSectorSlot[original] ^= gEepromSectorSlot[replacement];
        gEepromSectorSlot[replacement] ^= gEepromSectorSlot[original];
    }
}

void eepromWriteBitfield(value, bitOffset, bitCount)
u32 value;
unsigned short bitOffset;
unsigned char bitCount;
{
    u32 mask;
    u32 val;
    u8 bit;
    u32 *ptr;

    mask = -1;
    val = 0;
    bit = bitOffset & 0x1F;
    ptr = (u32 *)sEepromSlotBuffer + (bitOffset >> 5);
    if (bitCount) {
        do {
            mask ^= 1 << bit;
            val |= (value & 1) << bit;
            value >>= 1;
            bit++;
            bitCount--;
            if ((bit >= 0x20) || !bitCount) {
                *ptr = (*ptr & mask) | val;
                ptr++;
                bit = 0;
                val = 0;
                mask = -1;
            }
        } while (bitCount);
    }
}

s32 eepromReadBitfield(bitOffset, bitCount)
unsigned short bitOffset;
unsigned char bitCount;
{
    u32 *ptr;
    u32 data;
    u32 result;
    u8 start;
    u8 bit;
    u8 shift;
    u8 orig;

    result = 0;
    start = bitOffset & 0x1F;
    shift = 0;
    bit = bitOffset & 0x1F;
    data = 0;
    orig = bitCount;
    ptr = (u32 *)sEepromSlotBuffer + (bitOffset >> 5);
    if (bitCount) {
        do {
            data |= 1 << bit;
            bit++;
            bitCount--;
            if ((bit >= 0x20) || !bitCount) {
                result |= ((*ptr & data) >> start) << shift;
                bit = 0;
                ptr++;
                data = 0;
                start = 0;
                shift = -(bitCount - orig);
            }
        } while (bitCount);
    }
    return result;
}

void eepromGetKongFieldOffset(s32 field, u8 index, u8 subIndex, u16 *offset, u8 *width) {
    *offset = D_807ECEA0 + *offset + (index * 0xA1) + 0x320;
    *width = 0;
    switch (field) {
    case 11:
        if (*width == 0) *width = 1;
        *offset += 3;
    case 10:
        if (*width == 0) *width = 3;
        *offset += 8;
    case 9:
        if (*width == 0) *width = 8;
        *offset += 4;
    case 8:
        if (*width == 0) *width = 4;
        *offset += 2;
    case 7:
        if (*width == 0) *width = 2;
        *offset += 3;
    case 6:
        if (*width == 0) *width = 3;
        *offset += 2;
    case 5:
        if (*width == 0) *width = 2;
        *offset += 2;
    case 4:
        if (*width == 0) *width = 2;
        *offset += 0x18;
    case 3:
        if (*width == 0) {
            *width = 3;
            *offset += subIndex * 3;
        }
        *offset += 0x38;
    case 2:
        if (*width == 0) {
            *width = 7;
            *offset += subIndex * 7;
        }
        *offset += 0x38;
    case 1:
        if (*width == 0) {
            *width = 7;
            *offset += subIndex * 7;
        }
    }
}

void eepromGetSaveDataSectionOffset(s32 field, u8 index, u16 *offset, u8 *width) {
    *offset = D_807ECEA0 + *offset + 0x645;
    *width = 0;
    switch (field) {
    case 15:
        if (*width == 0) {
            *width = 2;
        }
        *offset += 0x18;
    case 16:
        if (*width == 0) {
            *width = 0x18;
        }
        *offset += 0x16;
    case 14:
        if (*width == 0) {
            *width = 0x16;
        }
        *offset += 1;
    case 13:
        if (*width == 0) {
            *width = 1;
        }
        *offset += 2;
    case 12:
        if (*width == 0) {
            *width = 2;
        }
    }
}

void eepromGetGlobalFieldOffset(s32 field, u8 index, u16 *offset, u8 *width) {
    *offset = (((((((D_807ECEA0 + 0x6B7) & 0xFFC0) + 0x27) & 0xFFF8) * 4) + 0x3F) & 0xFFC0) + 0x40;
    *width = 0;
    switch (field) {
    case 32: if (*width == 0) *width = 1; *offset += 3;
    case 31: if (*width == 0) *width = 3; *offset += 2;
    case 30: if (*width == 0) *width = 2; *offset += 0x2D;
    case 29: if (*width == 0) { *width = 9; *offset += index * 9; } *offset += 0x19;
    case 28: if (*width == 0) { *width = 5; *offset += index * 5; } *offset += 0x19;
    case 27: if (*width == 0) { *width = 5; *offset += index * 5; } *offset += 0x19;
    case 26: if (*width == 0) { *width = 5; *offset += index * 5; } *offset += 0x2D;
    case 25: if (*width == 0) { *width = 9; *offset += index * 9; } *offset += 0x19;
    case 24: if (*width == 0) { *width = 5; *offset += index * 5; } *offset += 0x19;
    case 23: if (*width == 0) { *width = 5; *offset += index * 5; } *offset += 0x19;
    case 22: if (*width == 0) { *width = 5; *offset += index * 5; } *offset += 0x4B;
    case 21: if (*width == 0) { *width = 0xF; *offset += index * 0xF; } *offset += 0x19;
    case 20: if (*width == 0) { *width = 5; *offset += index * 5; } *offset += 0x19;
    case 19: if (*width == 0) { *width = 5; *offset += index * 5; } *offset += 0x19;
    case 18: if (*width == 0) { *width = 5; *offset += index * 5; } *offset += 0x11;
    case 17: if (*width == 0) *width = 0x12;
    }
}

void eepromCalculateTotalModelCount(s32 field, s32 index, u8 count, u16 *offset, s8 *width) {
    s32 i;

    *offset += 0x320;
    for (i = 0; i < count; i++) {
        *offset += modelTypeCountGet(i);
    }
    *width = 1;
}

void eepromGetSectorOffset(offset, width, field, index, subIndex, sector)
u16 *offset;
u8 *width;
s32 field;
unsigned char index;
unsigned char subIndex;
unsigned char sector;
{
    u16 base;
    base = sector;
    base *= ((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7);
    *offset = base;
    if (field >= 0x11) {
        eepromGetGlobalFieldOffset(field, subIndex, offset, width);
        return;
    }
    if (field >= 0xC) {
        eepromGetSaveDataSectionOffset(field, subIndex, offset, width);
        return;
    }
    if (field > 0) {
        eepromGetKongFieldOffset(field, index, subIndex, offset, width);
        return;
    }
    eepromCalculateTotalModelCount(field, index, subIndex, offset, (s8 *)width);
}

extern u8 *D_80746800;

s32 eepromScaleFieldValue(s32 field, u32 value, s32 encode) {
    f32 scale;

    switch (field) {
    case 17:
        scale = 5.0f;
        if (encode != 0) {
            scale = 1.0f / scale;
        }
        value = value * scale;
        break;
    case 21:
        scale = 50.0f;
        if (encode != 0) {
            scale = 1.0f / scale;
        }
        value = value * scale;
        break;
    case 18:
    case 19:
    case 20:
    case 22:
    case 23:
    case 24:
    case 26:
    case 27:
    case 28:
        if (encode != 0) {
            value = _strchr(D_80746800, value) - D_80746800;
        } else {
            value = D_80746800[value];
        }
        break;
    }
    return value;
}


void eepromSetField(s32 field, u8 index, u8 subIndex, u8 slot, s32 value) {
    u16 offset;
    u8 width;

    eepromGetSectorOffset(&offset, &width, field, index, subIndex, eepromGetSectorForSlot(slot));
    eepromWriteBitfield(eepromScaleFieldValue(field, value, 1), offset, width);
}


s32 eepromGetField(s32 field, u8 index, u8 subIndex, u8 slot) {
    s32 value;
    u16 offset;
    u8 width;

    value = eepromGetSectorForSlot(slot);
    eepromGetSectorOffset(&offset, &width, field, index, subIndex, value);
    value = eepromReadBitfield(offset, width);
    return eepromScaleFieldValue(field, value, 0);
}


s32 func_8060C724(u8 slot) {
    return eepromGetField(0x10, 0, 0, slot) + 1;
}


void eepromClearSlotData(slot, save)
unsigned char slot;
int save;
{
    u8 *dst = sEepromSlotBuffer;
    u32 slotId;
    s32 size;
    s32 sector;

    slotId = slot;
    sector = eepromGetSectorForSlot(slotId);
    size = ((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
    dst += sector * size;
    gEepromCurrentSlot = slotId;
    bzero(dst, size);
    eepromSetField(0xC, 0, 0, slot, 1);
    eepromSetField(0xF, 0, 0, slot, slotId);
    if (save != 0) {
        eepromDispatchCommand(1);
    }
}

void eepromSetCurrentSlot(u8 slotId, s32 save) {
    u32 slot = slotId;

    gEepromCurrentSlot = slot;
    eepromClearSlotData(slot, 0);
    if (eepromGetField(0xF, 0, 0, 3) == slotId) {
        eepromClearSlotData(3, 0);
    }
    if (save != 0) {
        eepromDispatchCommand(1);
    }
}

extern s32 gEepromDefaultScores[];
extern MenuHighScoreEntry D_80744548[];
extern MenuHighScoreEntry D_80744568[];

extern const MenuHighScoreEntry D_80757044[];
extern const MenuHighScoreEntry D_80757064[];

void eepromInitConfigs(u8 mask) {
    s32 i;

    if (mask & 1) {
        eepromSetField(0x11, 0, 0, 0, 0);
    }
    if (mask & 2) {
        for (i = 0; i != 5; i++) {
            eepromSetField(0x15, 0, i, 0, gEepromDefaultScores[i]);
            eepromSetField(0x12, 0, i, 0, ' ');
            eepromSetField(0x13, 0, i, 0, ' ');
            eepromSetField(0x14, 0, i, 0, ' ');
        }
    }
    if (mask & 4) {
        for (i = 0; i != 5; i++) {
            eepromSetField(0x19, 0, i, 0, D_80757044[i].score);
            eepromSetField(0x16, 0, i, 0, D_80757044[i].initials[0]);
            eepromSetField(0x17, 0, i, 0, D_80757044[i].initials[1]);
            eepromSetField(0x18, 0, i, 0, D_80757044[i].initials[2]);
            D_80744548[i] = D_80757044[i];
        }
    }
    if (mask & 8) {
        for (i = 0; i != 5; i++) {
            eepromSetField(0x1D, 0, i, 0, D_80757064[i].score);
            eepromSetField(0x1A, 0, i, 0, D_80757064[i].initials[0]);
            eepromSetField(0x1B, 0, i, 0, D_80757064[i].initials[1]);
            eepromSetField(0x1C, 0, i, 0, D_80757064[i].initials[2]);
            D_80744568[i] = D_80757064[i];
        }
    }
    if (mask & 0x10) {
        eepromSetField(0x1E, 0, 0, 0, 0);
    }
    if (mask & 0x20) {
        eepromSetField(0x1F, 0, 0, 0, 0);
    }
}


void eepromResetGlobalData(void) {
    flagsClearAllBank1();
    eepromInitConfigs(0xFF);
}


void func_8060CB9C(void) {
    eepromDispatchCommand(3);
}

extern u8 sLanguageIndex;
extern u8 D_80744530;


void eepromValidateSaveSlots(void) {
    u32 globalOk;
    u8 found;
    u16 off;
    s32 i;
    u32 crc;
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
    memcpy(sEepromSlotBuffer, sEepromImage, 0x800);
    for (i = 0; i < 4; i++) {
        gEepromSectorSlot[i] = i;
        sectorOrder[i] = 0xFF;
    }
    for (i = 0; i < 4; i++) {
        ok = 1;
        off = ((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7)) / 8) * i;
        data = off + sEepromImage;
        idx = (((i + 1) * ((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7)) / 8)) / 4) - 1;
        stored = ((u32 *)sEepromImage)[idx];
        len = ((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7)) / 8) - 4;
        crc = eepromCalculateCrc32(data, len);
        if (stored != crc) {
            ok = 0;
            eepromClearSlotData((u8)i & 0xFF, 0);  // ORIG: andi s3,s4,0xff at 0x14ec ((u8)i) then andi a0,s3,0xff at 0x14f4 (& 0xFF) for this unprototyped K&R call
            eepromSetField(0xF, 0, 0, i, 0xFF);
        }
        failed |= (ok == 0);
        valid[i] = ok;
    }
    for (i = 0; i < 4; i++) {
        if (valid[i] != 0) {
            if (eepromGetField(0xD, 0, 0, i) != 0) {
                found = version = eepromGetField(0xF, 0, 0, i);
                for (j = 0; j < 4 && found == version; j++) {
                    if (j != i && valid[j] != 0) {
                        if (eepromGetField(0xD, 0, 0, j) != 0 && eepromGetField(0xF, 0, 0, j) == version) {
                            if ((u32)eepromGetField(0x10, 0, 0, i) > (u32)eepromGetField(0x10, 0, 0, j)) {
                                continue;
                            }
                            found = 0xFF;
                            eepromClearSlotData((u8)i & 0xFF, 0);  // ORIG: andi a0,s3,0xff at 0x1630 re-masks the (u8)i value (andi s3,s4,0xff at 0x156c) for this unprototyped K&R call
                            eepromSetField(0xF, 0, 0, i, 0xFF);
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
        for (j = 0; j < 4 && hit == 0; j++) {
            if (sectorOrder[j] == i) {
                hit = 1;
            }
        }
        if (hit == 0) {
            for (j = 0; j < 4 && hit == 0; j++) {
                if (sectorOrder[j] == 0xFF) {
                    sectorOrder[j] = i;
                    hit = 1;
                    eepromSetField(0xF, 0, 0, j, i);
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        gEepromSectorSlot[i] = sectorOrder[i];
    }
    globalOk = 1;
    off = ((((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F)) / 8);
    idx = (((((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4 + 0x3F) & ~0x3F)) / 8) + 0x40) / 4 - 1;
    stored = ((u32 *)sEepromImage)[idx];
    crc = eepromCalculateCrc32(sEepromImage + off, 0x3C);
    if (stored != crc) {
        globalOk = 0;
        eepromResetGlobalData();
    }
    failed |= (globalOk == 0);
    sLanguageIndex = eepromGetField(0x1F, 0, 0, 0);
    D_80744530 = eepromGetField(0x20, 0, 0, 0);
    if (sLanguageIndex > 0) {
        sLanguageIndex = 0;
        eepromSetField(0x1F, 0, 0, 0, sLanguageIndex);
    }
    if (failed != 0) {
        eepromDispatchCommand(1);
    }
}


void eepromResetAllSlots(void) {
    s32 pad;
    s32 slot;
    u8 *p;
    s32 i;

    p = gEepromSectorSlot;
    slot = gEepromCurrentSlot;
    for (i = 0; i < 4; i++) {
        *p++ = i;
    }
    bzero(sEepromSlotBuffer, 0x800);
    eepromResetGlobalData();
    for (i = 0; i != 4; i++) {
        eepromClearSlotData((u8)i, i == 3);
    }
    gEepromCurrentSlot = slot;
}

extern OSMesgQueue D_807ECCF0;
extern u8 *D_807467C0; // save-signature string
extern s8 gEepromWriteInProgress;
extern s8 D_807467CC;

void eepromReadAllSectors(void) {
    s32 failed;
    u8 *dst;
    s32 sector;

    failed = 0;
    dst = sEepromImage;
    if (D_807EDEAC != 2) {
        eepromResetAllSlots();
        D_807467CC = 1;
        return;
    }
    gEepromWriteInProgress = 1;
    for (sector = 0; (sector < 0x100) && (failed == 0); sector++, dst += 8) {
        failed |= osEepromRead(&D_807ECCF0, (u8)sector, dst);
        sleepMilliseconds(15.0f);
        if (gMainThreadHalted != 0) {
            gEepromWriteInProgress = 0;
            return;
        }
    }
    gEepromWriteInProgress = 0;
    D_807467CC = 1;
    if (failed == 0) {
        failed = _strcasecmp(sEepromImage + ((((((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) + 0x207) & ~7) / 8), D_807467C0);
    }
    if (failed != 0) {
        eepromResetAllSlots();
    }
    func_8060CB9C();
}

extern u8 *D_807467C0; // save-signature string
extern s8 gSaveIconTimer;
extern f32 gEepromWriteProgress;
extern OSMesgQueue D_807ECCF0;


void eepromSaveRecords(s32 recordsOnly) {
    s32 j;
    u16 sector;
    s32 offset;
    s32 height;
    u16 idx;
    u16 a;
    u16 b;
    u8 i;
    u8 workingData[0x800];
    u8 savedData[0x800];
    volatile u8 *contReadPending; // controller-read-pending flag; this runs on eepromThreadMain while the main thread (controllerUpdate) clears it
    contReadPending = &gContReadPending;
    if (D_807EDEAC == 2) {
        _sprintf(((((((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) + 0x207) & ~7) / 8) + sEepromSlotBuffer, D_807467C0);
        memcpy(workingData, sEepromSlotBuffer, 0x800);
        memcpy(savedData, sEepromImage, 0x800);
        if (recordsOnly == 0) {
            eepromCopySlot();
            for (i = 0; i < 4; i++) {
                height = ((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7);
                height /= 8;

                a = i * height;
                if (a) {}  // FAKE: keeps the narrowed index a a v1 variable (mflo v1; andi t4,v1,0xffff; move v1,t4 at 0x1c08-0x1c10) instead of folding it into the CRC call (Q1165)
                b = (((i + 1) * height) / 4) - 1;
                ((u32 *)workingData)[b] = eepromCalculateCrc32(a + workingData, height - 4);
            }
            sector = 0;
            offset = D_807ECEA0;
            offset += 0x6B7;
            offset = (offset & ~0x3FU) + 0x27;
            offset = ((offset & ~7U) * 4) + 0x3F;
            offset &= ~0x3FU;
            offset /= 8;
        } else {
            offset = (((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F);
            offset /= 8;
            sector = offset / 8;
        }
        a = offset;
        b = ((offset + 0x40) / 4) - 1;
        offset = sector << 3;
        ((u32 *)workingData)[b] = eepromCalculateCrc32(a + workingData, 0x3C);
        bzero(strlen(D_807467C0) - (0x800 - ((((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) + workingData + 0x840, (0x800 - ((((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) - strlen(D_807467C0) - 0x40);
        osWritebackDCacheAll();
        memcpy(&((u64 *)sEepromImage)[sector], &((u64 *)workingData)[sector], 0x800 - offset);
        while (*contReadPending != 0) {
            sleepMilliseconds(1.0f);
        }
        if (D_807ECEA0 & ~0x3FU) {}  // FAKE: one dead read of D_807ECEA0 through the unsigned 64-byte mask after the calls: a use of &D_807ECEA0 past bzero so -8 wins the exact adjsave tie (s4 = -8, s7 = &D_807ECEA0 at 0x1b28/0x1b38, Q0900), an unsigned -64 use that keeps the arm-0 masks uncoloured (li at,-64 at 0x1c64/0x1c88, Q0555) and a block before the halted test that keeps sector s1 above its widening s4 (move s4,s1 at 0x1dc8, Q1213)
        if (gMainThreadHalted != 0) {
            gEepromWriteInProgress = 0;
        } else {
            gEepromWriteInProgress = 1;
            for (idx = sector; idx < 0x100; idx += 2) {
                gSaveIconTimer = 0x1E;
                gEepromWriteProgress = (f32)(u32)idx * 0.00390625f;
                if (((u64 *)savedData)[idx] != ((u64 *)workingData)[idx] ||
                    ((u64 *)savedData)[idx + 1] != ((u64 *)workingData)[idx + 1]) {
                    for (j = 0; j < 2; j++) {
                        if (gMainThreadHalted != 0) {
                            gEepromWriteInProgress = 0;
                            return;
                        }
                        osEepromWrite(&D_807ECCF0, idx + j, workingData + idx * 8 + j * 8);
                        sleepMilliseconds(15.0f);
                    }
                }
            }
            gEepromWriteInProgress = 0;
        }
    }
}


void eepromSaveRecordsAll(void) {
    eepromSaveRecords(0);
}

void eepromSaveRecordsOffset(void) {
    eepromSaveRecords(1);
}

extern u8 D_807FC952; // gPlayerInventoryTable[0].kong[0].weaponFlags; that spelling CSEs into the table base (lbu 2(s0)), the target loads this label

void eepromRefillHalfConsumables(void) {
    s32 i;

    if (anyKongUsesAbilityEnergy() != 0) {
        gPlayerInventoryTable[0].abilityEnergy = slotQueueGetMaxValue(5, 0) * 0.5;
    }
    if (flagGet(0x184, 0) != 0) {
        gPlayerInventoryTable[0].throwAmmo = slotQueueGetMaxValue(4, 0) * 0.5;
    }
    if (flagGet(0x179, 0) != 0) {
        gPlayerInventoryTable[0].cameraFilm = slotQueueGetMaxValue(6, 0) * 0.5;
    }
    if (D_807FC952 != 0) {
        gPlayerInventoryTable[0].ammo = slotQueueGetMaxValue(2, 0) * 0.5;
    }
    for (i = 0; i < 5; i++) {
        gPlayerCharacterId[0] = i;
        if (gPlayerInventoryTable[0].kong[i].instrumentFlags != 0) {
            gPlayerInventoryTable[0].kong[i].instrumentEnergy = slotQueueGetMaxValue(7, 0) * 0.5;
        }
    }
    gPlayerCharacterId[0] = 0;
}

extern u8 gActivePlayerCount;
extern s32 gPlayTimeBaseSeconds;
extern u16 gLevelCollectibleCounts[];
extern u8 gPlayerCount;

void eepromLoadPlayerData(u8 slot, s32 fromCopy) {
    s32 pad;
    s32 i;
    KongInventory *entry;
    s32 j;
    s32 k;

    entry = gPlayerInventoryTable[0].kong;
    gActivePlayerCount = 1;
    playerResetSpawnGlobals();
    memcpy(sEepromSlotBuffer, sEepromImage, 0x800);
    gEepromCurrentSlot = slot;
    gPlayerCharacterId[0] = 0;
    if (eepromGetField(0xD, 0, 0, slot) == 0) {
        eepromClearSlotData(slot & 0xFF, 0);  // ORIG: the target re-masks the u8 slot for this unprototyped (K&R) call, andi a0,s5,0xff at 0x24e0
    }
    if (fromCopy != 0) {
        eepromCopySlot();
    }
    gPlayerCount = 0;
    gPlayerInventoryTable[0].melons = eepromGetField(0xC, 0, 0, slot);
    healthRefill(0);
    collectibleCountsClear();
    gPlayTimeBaseSeconds = eepromGetField(0xE, 0, 0, slot);
    i = 0;
    do {
        for (j = 0; j != 5; j++)
            entry->unk0[j] = eepromGetField(j + 4, i, 0, slot);
        entry->coins = eepromGetField(9, i, 0, slot);
        entry->unk5 = eepromGetField(0xA, i, 0, slot);
        if (eepromGetField(0xB, i, 0, slot) != 0) {
            entry->unk5 |= 0x80;
        }
        for (k = 0; k != 8; k++) {
            entry->coloredBananas[k] = eepromGetField(1, i, k, slot);
            gLevelCollectibleCounts[k] += entry->bananasDelivered[k] = eepromGetField(2, i, k, slot);
            entry->goldenBananas[k] = eepromGetField(3, i, k, slot);
        }
        i++;
        entry++;
    } while (i != 5);
    if (fromCopy != 0) {
        eepromRefillHalfConsumables();
    }
    gPlayerCharacterId[0] = 0;
}

void func_8060DEA8(void) {
    eepromDispatchCommand(2);
}


void eepromSavePlayerData(void) {
    KongInventory *entry;
    u32 total;
    u32 value;
    s32 i;
    s32 j;
    s32 k;

    if (gPlayerCount == 1) {
        if (menuIsTransitionType7Or9() != 0 || menuIsTransitionType6() != 0) {
            entry = gPlayerInventoryTable[0].kong;
            total = playTimeGetSeconds();
            value = func_8060C724(gEepromCurrentSlot);
            if (total >= 0x400000U) {
                total = -1;
            }
            eepromSetField(0xD, 0, 0, gEepromCurrentSlot, 1);
            eepromSetField(0xE, 0, 0, gEepromCurrentSlot, total);
            eepromSetField(0xC, 0, 0, gEepromCurrentSlot, gPlayerInventoryTable[0].melons);
            eepromSetField(0xF, 0, 0, gEepromCurrentSlot, gEepromCurrentSlot);
            eepromSetField(0x10, 0, 0, gEepromCurrentSlot, value);
            for (i = 0; i < 5; i++, entry++) {
                for (j = 0; j < 5; j++) {
                    eepromSetField(j + 4, i, 0, gEepromCurrentSlot, entry->unk0[j]);
                }
                eepromSetField(9, i, 0, gEepromCurrentSlot, entry->coins);
                eepromSetField(0xA, i, 0, gEepromCurrentSlot, entry->unk5 & 0x7F);
                eepromSetField(0xB, i, 0, gEepromCurrentSlot, (entry->unk5 >> 7) & 1);
                for (k = 0; k < 8; k++) {
                    eepromSetField(1, i, k, gEepromCurrentSlot, entry->coloredBananas[k]);
                    eepromSetField(2, i, k, gEepromCurrentSlot, entry->bananasDelivered[k]);
                    eepromSetField(3, i, k, gEepromCurrentSlot, entry->goldenBananas[k]);
                }
            }
            eepromDispatchCommand(1);
        }
    }
}

void eepromThreadMain(void *arg) {
    OSMesg msg;

    while (TRUE) {
        osRecvMesg(&D_807F02B8, &msg, 1);
        D_807467D0[(s32)msg]();
    }
}

extern OSMesg D_807EE0B0[];
extern OSThread D_807EE0E8;
extern OSMesg D_807F0298[];
extern s8 D_807467E0;

void eepromInit(void) {
    eepromInitModelCount();
    D_807EDEAC = osEepromProbe(&D_807ECCF0);
    osCreateMesgQueue(&D_807EE0D0, D_807EE0B0, 8);
    osCreateMesgQueue(&D_807F02B8, D_807F0298, 8);
    osCreateThread(&D_807EE0E8, 9, eepromThreadMain, NULL, D_807F0298, 0xC);
    osStartThread(&D_807EE0E8);
    D_807467E0 = 1;
    eepromDispatchCommand(0);
}

extern u8 D_807EDEB0[];

u8 *eepromGetSectionBuffer(u8 section) {
    u8 *result;

    result = NULL;
    switch (section) {
    case 0:
        if ((menuIsTransitionType3Or4() != 0) || (gPlayerCount >= 2)) {
            flagsClearAllBank2();
            bzero(D_807EDEB0, ((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8);
            result = D_807EDEB0;
        } else {
            result = sEepromSlotBuffer + ((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8) * eepromGetSectorForSlot(gEepromCurrentSlot));
        }
        break;
    case 1:
        result = ((s32) (((((((D_807ECEA0 + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8) + sEepromSlotBuffer;
        break;
    }
    return result;
}

u8 eepromReadChecksumBit(u16 bit, u8 index) {
    u8 result;
    u16 offset;
    u8 width;

    result = 0;
    if (menuIsTransitionType6() != 0) {
        eepromGetSectorOffset(&offset, &width, 0, 0, index, eepromGetSectorForSlot(gEepromCurrentSlot));
        result = eepromReadBitfield((offset + bit) & 0xFFFF, 1);
    }
    return result;
}


void func_8060E430(u16 bit, u8 value, u8 index) {
    u16 offset;
    u8 width;

    if (menuIsTransitionType6() != 0) {
        eepromGetSectorOffset(&offset, &width, 0, 0, index, eepromGetSectorForSlot(gEepromCurrentSlot));
        eepromWriteBitfield(value, (offset + bit) & 0xFFFF, 1);
    }
}

const char D_80757020[4] = "7.2";
const char D_80757024[30] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.- ";

const MenuHighScoreEntry D_80757044[5] = {
    { 100, "AAA" }, { 90, "AAA" }, { 80, "AAA" }, { 70, "AAA" }, { 60, "AAA" },
};

const MenuHighScoreEntry D_80757064[5] = {
    { 100, "AAA" }, { 90, "AAA" }, { 80, "AAA" }, { 70, "AAA" }, { 60, "AAA" },
};
