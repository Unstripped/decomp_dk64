#include "common.h"
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

s16 D_807ECEA0[4];
u8 D_807ECEA8[0x800];
u8 D_807ED6A8[0x800];
u8 D_807EDEA8[4];
s32 D_807EDEAC;
extern u8 D_807467C8;


void func_8060B7F0(void) {
    s32 i;

    D_807ECEA0[0] = 0;
    for (i = 0; i != 8; i++) {
        D_807ECEA0[0] += modelTypeCountGet(i);
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

extern s8 D_80744460;
extern void (*D_807467D0[])(void);
extern OSMesgQueue D_807F02B8;

void eepromDispatchCommand(s32 cmd) {
    if (osGetThreadId(NULL) == 9) {
        D_807467D0[cmd]();
        return;
    }
    if (D_80744460 == 0) {
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
        if (slot == D_807EDEA8[i]) {
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
    s32 size;
    s32 stride;

    original = eepromGetSectorForSlot(D_807467C8);
    replacement = eepromGetSectorForSlot(3);
    if (((menuIsTransitionType6() != 0) || (menuIsTransitionType7Or9() != 0)) && (original != replacement)) {
        stride = D_807ECEA0[0];
        stride += 0x6B7;
        stride = (stride & ~0x3F) + 0x27;
        stride = stride & ~7;
        stride = stride / 8;
        size = stride;
        src = D_807ECEA8 + (size * original);
        dst = D_807ECEA8 + (size * replacement);
        stride = stride | 0; // FAKE: no-code def extends stride's live range past dst (keeps the quotient in v0, original in a3)
        memcpy(dst, src, size);
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
        D_807EDEA8[original] ^= D_807EDEA8[replacement];
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
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
    ptr = (u32 *)D_807ECEA8 + (bitOffset >> 5);
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
    ptr = (u32 *)D_807ECEA8 + (bitOffset >> 5);
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

void func_8060BCA0(s32 field, u8 index, u8 subIndex, u16 *offset, u8 *width) {
    *offset = D_807ECEA0[0] + *offset + (index * 0xA1) + 0x320;
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
    *offset = D_807ECEA0[0] + *offset + 0x645;
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

void func_8060BF84(s32 field, u8 index, u16 *offset, u8 *width) {
    *offset = (((((((D_807ECEA0[0] + 0x6B7) & 0xFFC0) + 0x27) & 0xFFF8) * 4) + 0x3F) & 0xFFC0) + 0x40;
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
    base *= ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7);
    *offset = base;
    if (field >= 0x11) {
        func_8060BF84(field, subIndex, offset, width);
        return;
    }
    if (field >= 0xC) {
        eepromGetSaveDataSectionOffset(field, subIndex, offset, width);
        return;
    }
    if (field > 0) {
        func_8060BCA0(field, index, subIndex, offset, width);
        return;
    }
    eepromCalculateTotalModelCount(field, index, subIndex, offset, (s8 *)width);
}

extern u8 *D_80746800;

s32 func_8060C430(s32 field, u32 value, s32 encode) {
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
    eepromWriteBitfield(func_8060C430(field, value, 1), offset, width);
}


s32 eepromGetField(s32 field, u8 index, u8 subIndex, u8 slot) {
    s32 value;
    u16 offset;
    u8 width;

    value = eepromGetSectorForSlot(slot);
    eepromGetSectorOffset(&offset, &width, field, index, subIndex, value);
    value = eepromReadBitfield(offset, width);
    return func_8060C430(field, value, 0);
}


s32 func_8060C724(u8 slot) {
    return eepromGetField(0x10, 0, 0, slot) + 1;
}


void eepromClearSlotData(slot, save)
unsigned char slot;
int save;
{
    u8 *dst;
    s32 slotId;
    s32 slotArg;
    s32 size;
    s32 sector;

    do {
        slotId = slot;
        sector = eepromGetSectorForSlot(slotId);
        size = ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
        dst = D_807ECEA8 + (sector * size);
    } while (0); // FAKE: schedules addiu t0 before lui at
    D_807467C8 = slotId;
    bzero(dst, size);
    slotArg = slotId;
    eepromSetField(0xC, 0, 0, slotArg, 1);
    eepromSetField(0xF, 0, 0, slotId ^ 0, slotArg); // FAKE: prevents a3 CSE spill
    if (save != 0) {
        eepromDispatchCommand(1);
    }
}

void eepromSetCurrentSlot(slotId, save)
unsigned char slotId;
int save;
{
    u32 slot = slotId;

    D_807467C8 = slot;
    eepromClearSlotData(slot, 0);
    if (eepromGetField(0xF, 0, 0, 3) == slotId) {
        eepromClearSlotData(3, 0);
    }
    if (save != 0) {
        eepromDispatchCommand(1);
    }
}

typedef struct EepromConfig {
    s16 value;
    u8 byte2;
    u8 byte3;
    u8 byte4;
    u8 byte5;
} EepromConfig;

extern s32 D_807467EC[];
extern EepromConfig D_80744548[];
extern EepromConfig D_80744568[];

extern const EepromConfig D_80757044[];
extern const EepromConfig D_80757064[];

void eepromInitConfigs(u8 mask) {
    s32 i;

    if (mask & 1) {
        eepromSetField(0x11, 0, 0, 0, 0);
    }
    if (mask & 2) {
        for (i = 0; i != 5; i++) {
            eepromSetField(0x15, 0, i, 0, D_807467EC[i]);
            eepromSetField(0x12, 0, i, 0, 0x20);
            eepromSetField(0x13, 0, i, 0, 0x20);
            eepromSetField(0x14, 0, i, 0, 0x20);
        }
    }
    if (mask & 4) {
        for (i = 0; i != 5; i++) {
            eepromSetField(0x19, 0, i, 0, D_80757044[i].value);
            eepromSetField(0x16, 0, i, 0, D_80757044[i].byte2);
            eepromSetField(0x17, 0, i, 0, D_80757044[i].byte3);
            eepromSetField(0x18, 0, i, 0, D_80757044[i].byte4);
            D_80744548[i] = D_80757044[i];
        }
    }
    if (mask & 8) {
        for (i = 0; i != 5; i++) {
            eepromSetField(0x1D, 0, i, 0, D_80757064[i].value);
            eepromSetField(0x1A, 0, i, 0, D_80757064[i].byte2);
            eepromSetField(0x1B, 0, i, 0, D_80757064[i].byte3);
            eepromSetField(0x1C, 0, i, 0, D_80757064[i].byte4);
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


void func_8060CB74(void) {
    flagsClearAllBank1();
    eepromInitConfigs(0xFF);
}


void func_8060CB9C(void) {
    eepromDispatchCommand(3);
}

extern u8 sLanguageIndex;
extern u8 D_80744530;


void eepromValidateSaveSlots(void) {
    s32 pad;
    u8 found;
    u16 off;
    s32 i;
    u32 pad2;
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
        idx = ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7)) / 8) * (j = i + 1)) / 4) - 1;
        stored = ((u32 *)D_807ED6A8)[idx];
        len = ((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7)) / 8) - 4;
        hit = eepromCalculateCrc32(data, len);
        if (stored != hit) {
            ok = 0;
            eepromClearSlotData((u8)i & 0xFF, 0);  // FAKE: redundant (u8) cast plus mask on the K&R u8 argument; i & 0xFF or (u8)i alone recolours
            eepromSetField(0xF, 0, 0, i, 0xFF);
        }
        failed |= (ok == 0);
        valid[i] = ok;
    }
    ok = 0;
    version = 0;
    for (i = 0; i < 4; i++) {
        if (valid[i] != 0) {
            if (eepromGetField(0xD, 0, 0, i) != 0) {
                found = version = eepromGetField(0xF, 0, 0, i);
                if (D_80744530) {}  // FAKE: steers uopt colouring order of found/version
                for (j = 0; j < 4 && found == version; j++) {
                    if (j != i && valid[j] != 0) {
                        slot2 = j;
                        if (eepromGetField(0xD, 0, 0, slot2) != 0 && eepromGetField(0xF, 0, 0, slot2) == version && (u32)eepromGetField(0x10, 0, 0, i) <= (u32)eepromGetField(0x10, 0, 0, slot2)) {
                            found = 0xFF;
                            eepromClearSlotData((u8)i & 0xFF, 0);  // FAKE: redundant (u8) cast plus mask on the K&R u8 argument (as above)
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
    stored = ((u32 *)D_807ED6A8)[idx];
    hit = eepromCalculateCrc32(D_807ED6A8 + off, 0x3C);
    if (stored != hit) {
        ok = 0;
        func_8060CB74();
    }
    failed |= (ok == 0);
    sLanguageIndex = eepromGetField(0x1F, 0, 0, 0);
    D_80744530 = eepromGetField(0x20, 0, 0, 0);
    if (sLanguageIndex > 0) {
        sLanguageIndex = 0;
        eepromSetField(0x1F, 0, 0, 0, sLanguageIndex);
    }
    if (failed != 0) eepromDispatchCommand(1);
}


void func_8060D0A8(void) {
    s32 pad;
    s32 slot;
    u8 *p;
    s32 i;

    p = D_807EDEA8;
    slot = D_807467C8;
    for (i = 0; i < 4; i++) {
        *p++ = i;
    }
    bzero(D_807ECEA8, 0x800);
    func_8060CB74();
    for (i = 0; i != 4; i++) {
        eepromClearSlotData((u8)i, i == 3);
    }
    D_807467C8 = slot;
}

extern OSMesgQueue D_807ECCF0;
extern char *D_807467C0;
extern s8 D_807467C4;
extern s8 D_807467CC;

void eepromReadAllSectors(void) {
    s32 failed;
    u8 *dst;
    s32 sector;

    failed = 0;
    dst = D_807ED6A8;
    if (D_807EDEAC != 2) {
        func_8060D0A8();
        D_807467CC = 1;
        return;
    }
    D_807467C4 = 1;
    for (sector = 0; (sector < 0x100) && (failed == 0); sector++, dst += 8) {
        failed |= osEepromRead(&D_807ECCF0, (u8)sector, dst);
        sleepMilliseconds(15.0f);
        if (D_80744460 != 0) {
            D_807467C4 = 0;
            return;
        }
    }
    D_807467C4 = 0;
    D_807467CC = 1;
    if (failed == 0) {
        failed = _strcasecmp((char *)D_807ED6A8 + ((((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) + 0x207) & ~7) / 8), D_807467C0);
    }
    if (failed != 0) {
        func_8060D0A8();
    }
    func_8060CB9C();
}

extern char *D_807467C0;
extern s8 D_807467C4;
extern s8 D_807467E4;
extern f32 D_807467E8;
extern u8 D_807ECD08[];
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
    u8 *p;
    u8 *q;
    p = D_807ECD08;
    if (D_807EDEAC == 2) {
        _sprintf((char *)D_807ECEA8 + ((((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) + 0x207) & ~7) / 8), D_807467C0);
        memcpy(workingData, D_807ECEA8, 0x800);
        memcpy(savedData, D_807ED6A8, 0x800);
        if (recordsOnly == 0) {
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
            offset = (offset & ~0x3FU) + 0x27;
            offset = ((s32)(offset & ~7U) * 4) + 0x3F;
            offset = (s32)(offset & ~0x3FU);
            offset /= 8;
        } else {
            offset = (((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F);
            offset /= 8;
            sector = offset / 8;
        }
        a = offset;
        b = ((offset + 0x40) / 4) - 1;
        offset = 0;  // FAKE: dead store; the operand is redefined, so b's value is not copy-propagated into the index and b stays the variable (same colour as the loop's b)
        ((u32 *)workingData)[b] = eepromCalculateCrc32(a + workingData, 0x3C);
        bzero(strlen(D_807467C0) - (0x800 - ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) + workingData + 0x840, (0x800 - ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) - strlen(D_807467C0) - 0x40);
        if (D_807ECEA0) {}  // FAKE: deadsweep dead statement (steers uopt)
        osWritebackDCacheAll();
        if ((u32)D_807EDEAC & ~0x3FU) {}  // FAKE: an unsigned -64 use after the calls keeps the unsigned mask constants of the arm above uncoloured (li at,-64)
        memcpy(D_807ED6A8 + (u32)sector * 8, workingData + (u32)sector * 8, 0x800 - (sector << 3));  // FAKE: (u32) casts make the products read the variable, not its ucvt widening (widening keeps the shift and the loop test: move s4,s1)
        q = (u8 *)((u32)D_807ECD08);  // FAKE: a second, u32-laundered pointer to D_807ECD08 for the first poll test (p reads it in the loop)
        if (*q != 0) do sleepMilliseconds(1.0f); while (*p != 0);
        if ((u32)sector) {}  // FAKE: direct read of sector raises the variable's priority above its widening (var s1, widening s4)
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


void eepromSaveRecordsAll(void) {
    eepromSaveRecords(0);
}

void eepromSaveRecordsOffset(void) {
    eepromSaveRecords(1);
}

extern KongInventory gPlayerInventoryTable[];
extern u8 D_807FC952;
extern u8 gPlayerCharacterId;

void eepromHalveRecords(void) {
    s32 i;

    if (func_806F6EDC() != 0) {
        u32 v = slotQueueGetMaxValue(5, 0);
        *(s16 *)((u8 *)gPlayerInventoryTable + 0x2F6) = (u32)(v * 0.5);
    }
    if (flagGet(0x184, 0) != 0) {
        u32 v = slotQueueGetMaxValue(4, 0);
        *(s16 *)((u8 *)gPlayerInventoryTable + 0x2F4) = (u32)(v * 0.5);
    }
    if (flagGet(0x179, 0) != 0) {
        u32 v = slotQueueGetMaxValue(6, 0);
        *(s16 *)((u8 *)gPlayerInventoryTable + 0x2F8) = (u32)(v * 0.5);
    }
    if (D_807FC952 != 0) {
        u32 v = slotQueueGetMaxValue(2, 0);
        *(s16 *)((u8 *)gPlayerInventoryTable + 0x2F0) = (u32)(v * 0.5);
    }
    for (i = 0; i != 5; i++) {
        gPlayerCharacterId = i;
        if (gPlayerInventoryTable[i].unk0[4] != 0) {
            u32 v = slotQueueGetMaxValue(7, 0);
            gPlayerInventoryTable[i].unk8 = (u32)(v * 0.5);
        }
    }
    gPlayerCharacterId = 0;
}

extern u8 gActivePlayerCount;
extern s32 D_80750AB0;
extern u16 gLevelCollectibleCounts[];
extern u8 gPlayerCount;

void eepromLoadPlayerData(u8 slot, s32 fromCopy) {
    KongInventory *base;
    s32 i;
    KongInventory *entry;
    s32 j;
    s32 k;

    base = gPlayerInventoryTable;
    entry = base;
    gActivePlayerCount = 1;
    playerResetSpawnGlobals();
    memcpy(D_807ECEA8, D_807ED6A8, 0x800);
    D_807467C8 = slot;
    gPlayerCharacterId = 0;
    if (eepromGetField(0xD, 0, 0, slot) == 0) {
        eepromClearSlotData(slot & 0xFF, 0);  // FAKE: redundant mask on the u8 slot argument (dropping it recolours)
    }
    if (fromCopy != 0) {
        eepromCopySlot();
    }
    gPlayerCount = 0;
    ((u8 *)gPlayerInventoryTable)[0x2FC] = eepromGetField(0xC, 0, 0, slot);
    healthRefill(0);
    collectibleCountsClear();
    D_80750AB0 = eepromGetField(0xE, 0, 0, slot);
    i = 0;
    do {
        for (j = 0; j != 5; j++)
            entry->unk0[j] = eepromGetField(j + 4, (u8)i, 0, slot);
        entry->unk6 = eepromGetField(9, (u8)i, 0, slot);
        entry->unk5 = eepromGetField(0xA, (u8)i, 0, slot);
        if (eepromGetField(0xB, (u8)i, 0, slot) != 0) {
            entry->unk5 |= 0x80;
        }
        for (k = 0; k != 8; k++) {
            entry->unkA[k] = eepromGetField(1, (u8)i, (u8)k, slot);
            gLevelCollectibleCounts[k] += entry->unk26[k] = eepromGetField(2, (u8)i, (u8)k, slot);
            entry->unk42[k] = eepromGetField(3, (u8)i, (u8)k, slot);
        }
        i++;
        entry++;
    } while (i != 5);
    if (fromCopy != 0) {
        eepromHalveRecords();
    }
    gPlayerCharacterId = 0;
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
            entry = gPlayerInventoryTable;
            total = gfxSetupFrameViewports();
            value = func_8060C724(D_807467C8);
            if (total >= 0x400000U) {
                total = -1;
            }
            eepromSetField(0xD, 0, 0, D_807467C8, 1);
            eepromSetField(0xE, 0, 0, D_807467C8, total);
            eepromSetField(0xC, 0, 0, D_807467C8, ((u8 *)gPlayerInventoryTable)[0x2FC]);
            eepromSetField(0xF, 0, 0, D_807467C8, D_807467C8);
            eepromSetField(0x10, 0, 0, D_807467C8, value);
            i = 0;
            if (value && value) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            do {
                j = 0;
                do {
                    eepromSetField(j + 4, (u8)i, 0, D_807467C8, entry->unk0[j]);
                    j++;
                } while (j != 5);
                eepromSetField(9, (u8)i, 0, D_807467C8, entry->unk6);
                eepromSetField(0xA, (u8)i, 0, D_807467C8, entry->unk5 & 0x7F);
                eepromSetField(0xB, (u8)i, 0, D_807467C8, (entry->unk5 >> 7) & 1);
                k = 0;
                do {
                    u8 col_idx = k;
                    eepromSetField(1, (u8)i, col_idx, D_807467C8, entry->unkA[k]);
                    eepromSetField(2, (u8)i, col_idx, D_807467C8, entry->unk26[k]);
                    eepromSetField(3, (u8)i, col_idx, D_807467C8, entry->unk42[k]);
                    k++;
                } while (k != 8);
                i++;
                entry++;
            } while (i != 5);
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
extern u64 D_807F0298[];
extern s8 D_807467E0;

void eepromInit(void) {
    func_8060B7F0();
    D_807EDEAC = osEepromProbe(&D_807ECCF0);
    osCreateMesgQueue(&D_807EE0D0, D_807EE0B0, 8);
    osCreateMesgQueue(&D_807F02B8, D_807F0298, 8);
    osCreateThread(&D_807EE0E8, 9, eepromThreadMain, NULL, D_807F0298, 0xC);
    osStartThread(&D_807EE0E8);
    D_807467E0 = 1;
    eepromDispatchCommand(0);
}

extern u8 D_807EDEB0[];

u8 *func_8060E25C(s32 section) {
    u8 *result;
    s32 selector;

    selector = section & 0xFF;
    result = NULL;
    switch (selector) {
    case 0:
        if ((func_807142D8() != 0) || (gPlayerCount >= 2)) {
            flagsClearAllBank2();
            if (section) {}  // FAKE: dead read after the call keeps section's home-slot spill (Q0291)
            bzero(D_807EDEB0, ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8);
            result = D_807EDEB0;
        } else {
            result = D_807ECEA8 + ((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8) * eepromGetSectorForSlot(D_807467C8));
        }
        break;
    case 1:
        result = ((s32) (((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8) + D_807ECEA8;
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
        eepromGetSectorOffset(&offset, &width, 0, 0, index, eepromGetSectorForSlot(D_807467C8));
        result = eepromReadBitfield((offset + bit) & 0xFFFF, 1);
    }
    return result;
}


void func_8060E430(u16 bit, u8 value, u8 index) {
    u16 offset;
    u8 width;

    if (menuIsTransitionType6() != 0) {
        eepromGetSectorOffset(&offset, &width, 0, 0, index, eepromGetSectorForSlot(D_807467C8));
        eepromWriteBitfield(value, (offset + bit) & 0xFFFF, 1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757020.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757024.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757044.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/104F0/D_80757064.s")



