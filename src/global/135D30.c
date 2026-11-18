#include "common.h"
#include "actor.h"
#include "proto/global/104F0.h"
#include "proto/global/135D30.h"
#include "proto/global/3C10.h"

typedef struct FlagTableEntry4 {
    /* 0x0 */ s16 id;
    /* 0x2 */ u8 value;
    /* 0x3 */ u8 pad3;
} FlagTableEntry4;

typedef struct FlagRange {
    s16 first;
    s16 last;
    s16 required;
    s16 rewardFlag;
} FlagRange;

FlagTableEntry gFlagTempEntries[0x18];
u8 gFlagBank2[14];
FlagTableEntry D_80755A20[0x71] = {
    { 0x25, 0, 0x1, 0x3, 2, 0 }, { 0x7, 0, 0x69, 0x4, 2, 0 }, { 0x7, 0, 0x48, 0x5, 2, 0 },
    { 0x21, 0, 0x3, 0xC, 6, 0 }, { 0x7, 0, 0x68, 0x8, 5, 0 }, { 0x7, 0, 0x4F, 0x13, 4, 0 },
    { 0x7, 0, 0x4D, 0x12, 3, 0 }, { 0x7, 0, 0x50, 0x16, 6, 0 }, { 0x7, 0, 0x4C, 0x15, 5, 0 },
    { 0x7, 0, 0x44, 0x14, 2, 0 }, { 0x7, 0, 0x52, 0x17, 3, 0 }, { 0xC, 0, 0x3F, 0x9, 5, 0 },
    { 0xD, 0, 0x4, 0xA, 4, 0 }, { 0x7, 0, 0x1E, 0x1F, 3, 0 }, { 0x26, 0, 0x23, 0x31, 6, 0 },
    { 0x26, 0, 0xA3, 0x36, 3, 0 }, { 0x15, 0, 0x6, 0x38, 3, 0 }, { 0x13, 0, 0x6, 0x39, 2, 0 },
    { 0x16, 0, 0x6, 0x3A, 5, 0 }, { 0x26, 0, 0xEB, 0x3F, 3, 0 }, { 0x10, 0, 0x9, 0x40, 6, 0 },
    { 0x10, 0, 0x7E, 0x41, 5, 0 }, { 0x10, 0, 0x5B, 0x43, 3, 0 }, { 0x14, 0, 0xAA, 0x47, 5, 0 },
    { 0x14, 0, 0x2B, 0x48, 4, 0 }, { 0xE, 0, 0x48, 0x4B, 5, 0 }, { 0x26, 0, 0x26, 0x33, 2, 0 },
    { 0x14, 0, 0x6C, 0x4D, 2, 0 }, { 0x1A, 0, 0x2C, 0x71, 3, 0 }, { 0x1A, 0, 0x29, 0x72, 6, 0 },
    { 0x1A, 0, 0x2A, 0x73, 4, 0 }, { 0x1A, 0, 0x82, 0x7C, 5, 0 }, { 0x1A, 0, 0x3E, 0x7D, 4, 0 },
    { 0x1A, 0, 0x60, 0x7E, 3, 0 }, { 0x1A, 0, 0x63, 0x79, 6, 0 }, { 0x24, 0, 0x7, 0x80, 2, 0 },
    { 0x1A, 0, 0x7E, 0x7A, 2, 0 }, { 0x1B, 0, 0x62, 0x8B, 5, 0 }, { 0x1D, 0, 0x2, 0x70, 2, 0 },
    { 0x1A, 0, 0x78, 0x76, 4, 0 }, { 0x1A, 0, 0x7C, 0x7F, 6, 0 }, { 0x1A, 0, 0x108, 0x82, 2, 0 },
    { 0x1A, 0, 0x23, 0x7B, 5, 0 }, { 0x1E, 0, 0x32, 0x9A, 6, 0 }, { 0x1E, 0, 0x2E, 0xC1, 2, 0 },
    { 0x1F, 0, 0x6, 0xA6, 6, 0 }, { 0x33, 0, 0xF, 0xA7, 3, 0 }, { 0x31, 0, 0x2F, 0x9D, 2, 0 },
    { 0x1E, 0, 0xE, 0xB6, 6, 0 }, { 0x2F, 0, 0, 0xB7, 4, 0 }, { 0x2D, 0, 0xE, 0xBF, 5, 0 },
    { 0x1E, 0, 0x6B, 0xC0, 4, 0 }, { 0x2B, 0, 0xE, 0xC7, 4, 0 }, { 0x2E, 0, 0x21, 0xC9, 5, 0 },
    { 0x1E, 0, 0x2D, 0xCC, 3, 0 }, { 0x30, 0, 0x50, 0xD1, 5, 0 }, { 0x30, 0, 0x28, 0xD6, 3, 0 },
    { 0x38, 0, 0x3, 0xD8, 3, 0 }, { 0x3A, 0, 0x2, 0xD9, 4, 0 }, { 0x30, 0, 0x2B, 0xDB, 2, 0 },
    { 0x3D, 0, 0xD, 0xDD, 6, 0 }, { 0x47, 0, 0x2, 0xE1, 6, 0 }, { 0x40, 0, 0x3, 0xE4, 2, 0 },
    { 0x34, 0, 0, 0xCD, 5, 0 }, { 0x30, 0, 0x57, 0xF9, 4, 0 }, { 0x3C, 0, 0x1, 0xF7, 5, 0 },
    { 0x30, 0, 0x3E, 0xFD, 6, 0 }, { 0x46, 0, 0, 0xE2, 4, 0 }, { 0x30, 0, 0x39, 0xFE, 2, 0 },
    { 0x48, 0, 0x28, 0x10E, 6, 0 }, { 0x54, 0, 0x2, 0x117, 5, 0 }, { 0x55, 0, 0x3, 0x119, 4, 0 },
    { 0x48, 0, 0x3E, 0x10C, 6, 0 }, { 0x5E, 0, 0x1, 0x108, 4, 0 }, { 0x5F, 0, 0, 0x116, 6, 0 },
    { 0x56, 0, 0x1, 0x113, 2, 0 }, { 0x59, 0, 0x1, 0x114, 2, 0 }, { 0x5B, 0, 0x8, 0x105, 2, 0 },
    { 0x5C, 0, 0x1, 0x106, 3, 0 }, { 0x64, 0, 0x1, 0x112, 3, 0 }, { 0x5D, 0, 0, 0x104, 5, 0 },
    { 0x52, 0, 0x1, 0x103, 4, 0 }, { 0xC8, 0, 0x4, 0x125, 3, 0 }, { 0x62, 0, 0x10, 0x10F, 4, 0 },
    { 0x48, 0, 0x29, 0x129, 5, 0 }, { 0x48, 0, 0x32, 0x12A, 2, 0 }, { 0x6C, 0, 0x3, 0x134, 4, 0 },
    { 0x6C, 0, 0xD, 0x135, 5, 0 }, { 0x70, 0, 0x8, 0x136, 3, 0 }, { 0x72, 0, 0x3, 0x139, 2, 0 },
    { 0x71, 0, 0x7, 0x13A, 6, 0 }, { 0xA4, 0, 0x8, 0x140, 2, 0 }, { 0xA6, 0, 0x6, 0x142, 6, 0 },
    { 0xA8, 0, 0x1, 0x143, 4, 0 }, { 0xA3, 0, 0xF, 0x146, 2, 0 }, { 0xA7, 0, 0x4, 0x15F, 5, 0 },
    { 0xA3, 0, 0xD, 0x161, 3, 0 }, { 0x22, 0, 0x4, 0x17D, 2, 0 }, { 0xAE, 0, 0x9, 0x193, 5, 0 },
    { 0xC2, 0, 0x5, 0x19B, 2, 0 }, { 0x22, 0, 0x4D, 0x1A3, 2, 0 }, { 0x22, 0, 0x2E, 0x1A7, 3, 0 },
    { 0x22, 0, 0x2F, 0x1A5, 4, 0 }, { 0x22, 0, 0x2B, 0x1A4, 5, 0 }, { 0x22, 0, 0x2D, 0x1A6, 6, 0 },
    { 0x61, 0, 0x3, 0x1AD, 4, 0 }, { 0x22, 0, 0x56, 0x1AF, 6, 0 }, { 0xBD, 0, 0x1E, 0x12D, 5, 0 },
    { 0x11, 0, 0x5D, 0x248, 2, 0 }, { 0x11, 0, 0x5E, 0x249, 6, 0 }, { 0x11, 0, 0x5F, 0x24A, 4, 0 },
    { 0x11, 0, 0x60, 0x24B, 5, 0 }, { 0x11, 0, 0x61, 0x24C, 3, 0 },
};
FlagTableEntry D_80755DA8[0x1F] = {
    { 0x7, 0, 0x1, 0x6, 0, 0 }, { 0x7, 0, 0x33, 0x24D, 0, 0 }, { 0xD, 0, 0x7, 0x24E, 0, 0 },
    { 0x26, 0, 0xB, 0x32, 0, 0 }, { 0x14, 0, 0x2, 0x32, 1, 0 }, { 0x14, 0, 0x1, 0x46, 0, 0 },
    { 0x10, 0, 0x13, 0x42, 0, 0 }, { 0x14, 0, 0xC, 0x258, 0, 0 }, { 0x16, 0, 0xB, 0x259, 0, 0 },
    { 0x1A, 0, 0x1, 0x75, 0, 0 }, { 0x1A, 0, 0x5C, 0x24F, 0, 0 }, { 0x1A, 0, 0x55, 0x25A, 0, 0 },
    { 0x1E, 0, 0x15, 0x250, 0, 0 }, { 0x1E, 0, 0x2, 0xA5, 0, 0 }, { 0x2E, 0, 0x8, 0x25B, 0, 0 },
    { 0x5E, 0, 0x1, 0x108, 0, 0 }, { 0x5F, 0, 0x1, 0x116, 0, 0 }, { 0x54, 0, 0x3, 0x255, 0, 0 },
    { 0xC8, 0, 0x3, 0x260, 0, 0 }, { 0x30, 0, 0x2, 0xF9, 0, 0 }, { 0x38, 0, 0x2, 0x253, 0, 0 },
    { 0x3B, 0, 0x2, 0x254, 0, 0 }, { 0x71, 0, 0x5, 0x25C, 0, 0 }, { 0xA4, 0, 0x4, 0x25D, 0, 0 },
    { 0xAF, 0, 0x2, 0x251, 0, 0 }, { 0xB2, 0, 0x1, 0x252, 0, 0 }, { 0x22, 0, 0x6, 0x25E, 0, 0 },
    { 0x22, 0, 0x7, 0x25F, 0, 0 }, { 0x11, 0, 0x19, 0x256, 0, 0 }, { 0x11, 0, 0x1A, 0x257, 0, 0 },
    { 0xFF, 0, 0, 0, 0, 0 },
};
FlagTableEntry D_80755EA0[0x16] = {
    { 0x7, 0, 0x7, 0x1B, 1, 0 }, { 0x7, 0, 0x12, 0, 0, 0 }, { 0x7, 0, 0x6, 0x2A, 1, 0 },
    { 0xD, 0, 0x2, 0xA, 0, 0 }, { 0x26, 0, 0x16, 0x5C, 1, 0 }, { 0x10, 0, 0x2, 0x5E, 1, 0 },
    { 0x14, 0, 0x2, 0x5D, 1, 0 }, { 0x26, 0, 0xC, 0x5F, 1, 0 }, { 0x1A, 0, 0xA, 0x8C, 0, 0 },
    { 0x1A, 0, 0x11, 0x8C, 1, 0 }, { 0x1E, 0, 0x16, 0xC2, 1, 0 }, { 0x30, 0, 0x1A, 0x101, 1, 0 },
    { 0x59, 0, 0x1, 0x115, 1, 0 }, { 0x64, 0, 0x1, 0x112, 0, 0 }, { 0x5F, 0, 0x1, 0x116, 0, 0 },
    { 0x48, 0, 0x19, 0x11A, 1, 0 }, { 0x56, 0, 0x1, 0x12F, 1, 0 }, { 0xA8, 0, 0x1, 0x143, 0, 0 },
    { 0x57, 0, 0x13, 0x15D, 1, 0 }, { 0x2A, 0, 0x7, 0x167, 1, 0 }, { 0xB0, 0, 0x3, 0x17A, 1, 0 },
    { 0x22, 0, 0x9, 0x186, 1, 0 },
};
extern FlagTableEntry4 D_80755F4C[];
FlagTableEntry4 D_80755F50[0x35] = {
    { 0xE0, 4, 0 }, { 0x1C4, 0, 0 }, { 0x131, 3, 0 }, { 0x132, 4, 0 }, { 0x2, 5, 0 },
    { 0x1, 4, 0 }, { 0x1C, 6, 0 }, { 0x87, 3, 0 }, { 0xE3, 5, 0 }, { 0xEB, 2, 0 },
    { 0x86, 3, 0 }, { 0x88, 6, 0 }, { 0x89, 4, 0 }, { 0xB, 4, 0 }, { 0x74, 5, 0 },
    { 0x3C, 4, 0 }, { 0x3B, 6, 0 }, { 0x107, 6, 0 }, { 0x137, 6, 0 }, { 0x13B, 5, 0 },
    { 0xD3, 3, 0 }, { 0x49, 4, 0 }, { 0xA3, 3, 0 }, { 0xA4, 4, 0 }, { 0x13C, 4, 0 },
    { 0x3E, 2, 0 }, { 0x34, 6, 0 }, { 0x13F, 6, 0 }, { 0x44, 4, 0 }, { 0x18, 3, 0 },
    { 0xB8, 5, 0 }, { 0x18E, 4, 0 }, { 0x192, 5, 0 }, { 0x194, 2, 0 }, { 0x13E, 2, 0 },
    { 0xFE, 2, 0 }, { 0x196, 6, 0 }, { 0x19A, 3, 0 }, { 0x19F, 4, 0 }, { 0x1A0, 3, 0 },
    { 0x1A8, 6, 0 }, { 0x1A9, 5, 0 }, { 0x1AC, 3, 0 }, { 0x126, 3, 0 }, { 0x127, 5, 0 },
    { 0x12A, 2, 0 }, { 0xC6, 3, 0 }, { 0xC5, 6, 0 }, { 0xC8, 2, 0 }, { 0xCA, 5, 0 },
    { 0xFA, 3, 0 }, { 0x19, 6, 0 }, { 0x15E, 3, 0 },
};
FlagRange D_80756024[0x21] = {
    { 0x24D, 0x260, 1, 0 }, { 0x24D, 0x260, 2, 0x1 }, { 0x24D, 0x260, 6, 0xE },
    { 0x24D, 0x260, 10, 0x13 }, { 0x24D, 0x260, 15, 0x21 }, { 0x24D, 0x260, 20, 0x22 },
    { 0x6, 0x6, 1, 0x1D }, { 0x46, 0x46, 1, 0x1E }, { 0x42, 0x42, 1, 0x1F },
    { 0x75, 0x75, 1, 0x20 }, { 0x261, 0x26A, 1, 0x1C }, { 0x1C5, 0x1C5, 1, 0x2 },
    { 0x1C6, 0x1C6, 1, 0x3 }, { 0x1C7, 0x1C7, 1, 0x4 }, { 0x1C8, 0x1C8, 1, 0x5 },
    { 0x1C9, 0x1C9, 1, 0x6 }, { 0x1CA, 0x1CA, 1, 0x7 }, { 0x1CB, 0x1CB, 1, 0x8 },
    { 0x1CC, 0x1CC, 1, 0x9 }, { 0x304, 0x304, 1, 0xA }, { 0x315, 0x315, 1, 0xB },
    { 0x314, 0x314, 1, 0xC }, { 0x1B0, 0x1B0, 1, 0xD }, { 0x84, 0x84, 1, 0x11 },
    { 0x17B, 0x17B, 1, 0x12 }, { 0x1A, 0x1A, 1, 0x14 }, { 0x4A, 0x4A, 1, 0x15 },
    { 0x8A, 0x8A, 1, 0x16 }, { 0xA8, 0xA8, 1, 0x17 }, { 0xEC, 0xEC, 1, 0x18 },
    { 0x124, 0x124, 1, 0x19 }, { 0x13D, 0x13D, 1, 0x1A }, { 0x1B0, 0x1B0, 1, 0x1B },
};


void flagsClearAllBank2(void) {
    s32 i;

    for (i = 0; i < 14; i++) {
        gFlagBank2[i] = 0;
    }
}

void flagsClearAllBank0(void) {
    s32 i;

    for (i = 0; i < 0x316; i++) {
        flagSet(i, 0, 0);
    }
}

void flagsClearAllBank1(void) {
    s32 i;

    for (i = 0; i < 0x2C; i++) {
        flagSet(i, 0, 1);
    }
}

u8 flagGet(s16 flag, u8 bank) {
    u8 *base;
    s16 idx;

    if (flag == -1) {
        return 0;
    }
    switch (bank) {
    case 0:
    case 1:
        base = eepromGetSectionBuffer(bank);
        break;
    case 2:
        base = gFlagBank2;
        break;
    }
    idx = flag >> 3;
    return (base[idx] >> (s16)(flag - idx * 8)) & 1;
}

void flagUpdateRangeCompletion(s16 flag) {
    s32 i;
    s32 res = -1;
    FlagRange *e;

    for (i = 0; i < sizeof(D_80756024) / sizeof(D_80756024[0]) && res == -1; i++) {
        e = &D_80756024[i];
        if (flag >= e->first && flag <= e->last) {
            if (flagCountRange(e->first, e->last - e->first + 1, 0) == e->required) {
                res = e->rewardFlag;
            }
        }
    }
    if (res >= 0) {
        flagSet(res, 1, 1);
    }
}

void flagSet(s16 flag, u8 val, u8 bank) {
    u8 *base;
    s16 idx;
    s32 pad;

    if (flag == -1) {
        return;
    }
    switch (bank) {
    case 0:
    case 1:
        base = eepromGetSectionBuffer(bank);
        break;
    case 2:
        base = gFlagBank2;
        break;
    }
    idx = flag >> 3;
    if (val) {
        base[idx] |= 1 << (s16)(flag - idx * 8);
    } else {
        base[idx] &= ~(1 << (s16)(flag - idx * 8));
    }
    if (val != 0 && bank == 0) {
        flagUpdateRangeCompletion(flag);
    }
}

void flagTempsPruneUnloadedMaps(void) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (mapFindSlotByMap(gFlagTempEntries[i].map) == 0) {
            gFlagTempEntries[i].active = 0;
        }
    }
}

void flagTempRegister(s16 map, s16 id, s16 flag, u8 val) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (gFlagTempEntries[i].active == 0) {
            gFlagTempEntries[i].map = map;
            gFlagTempEntries[i].id = id;
            gFlagTempEntries[i].flag = flag;
            gFlagTempEntries[i].value = val;
            gFlagTempEntries[i].active = 1;
            return;
        }
    }
}

void flagSetForMapObject(s16 map, s16 id) {
    s32 i;
    s32 n = sizeof(D_80755A20) / sizeof(D_80755A20[0]);

    for (i = 0; i < n; i++) {
        if (map == D_80755A20[i].map && id == D_80755A20[i].id) {
            flagSet(D_80755A20[i].flag, 1, 0);
            return;
        }
    }
    for (i = 0; i < 0x18; i++) {
        if (gFlagTempEntries[i].active != 0 && map == gFlagTempEntries[i].map && id == gFlagTempEntries[i].id) {
            flagSet(gFlagTempEntries[i].flag, 1, 0);
            gFlagTempEntries[i].active = 0;
            return;
        }
    }
}

s32 flagGetForMapObject(s16 map, s16 id) {
    s32 i;
    s32 n = sizeof(D_80755A20) / sizeof(D_80755A20[0]);

    for (i = 0; i < n; i++) {
        if (map == D_80755A20[i].map && id == D_80755A20[i].id) {
            return flagGet(D_80755A20[i].flag, 0);
        }
    }
    return 0;
}

u8 flagValueForMapObject(s16 map, s16 id) {
    s32 i;
    s32 n = sizeof(D_80755A20) / sizeof(D_80755A20[0]);

    for (i = 0; i < n; i++) {
        if (map == D_80755A20[i].map && id == D_80755A20[i].id) {
            return D_80755A20[i].value;
        }
    }
    for (i = 0; i < 0x18; i++) {
        if (gFlagTempEntries[i].active != 0 && map == gFlagTempEntries[i].map && id == gFlagTempEntries[i].id) {
            return gFlagTempEntries[i].value;
        }
    }
    return 0;
}


s32 spawnFlagLookup(s16 map, s16 id, s32 *outIdx) {
    s32 n = sizeof(D_80755DA8) / sizeof(D_80755DA8[0]);

    for (*outIdx = 0; *outIdx < n; (*outIdx)++) {
        if (map == D_80755DA8[*outIdx].map && id == D_80755DA8[*outIdx].id) {
            return D_80755DA8[*outIdx].flag;
        }
    }
    return -1;
}

s32 spawnFlagConditionMet(s16 map, s16 id) {
    s32 r;
    s32 idx;
    u8 flag;

    r = spawnFlagLookup(map, id, &idx);
    if (r >= 0) {
        flag = flagGet(r, 0);
        if (flag != 0 && D_80755DA8[idx].value != 0) {
            return 1;
        }
        if (flag == 0 && D_80755DA8[idx].value == 0) {
            return 1;
        }
        return 0;
    }
    return 1;
}

s32 flagTryTriggerOnce(s16 map, s16 id) {
    s32 n = sizeof(D_80755EA0) / sizeof(D_80755EA0[0]);
    s32 i;
    FlagTableEntry *e;

    for (i = 0; i < n; i++) {
        e = &D_80755EA0[i];
        if (map == e->map && id == e->id) {
            if (flagGet(e->flag, 0) != 0) {
                return 0;
            }
            if (e->value != 0) {
                flagSet(e->flag, 1, 0);
            }
            return 1;
        }
    }
    return 1;
}

s32 func_8073195C(s16 index) {
    if (index == 0) {
        return -1;
    }
    return D_80755F4C[index].id;
}

u8 flagLookupValueById(s16 id) {
    s32 i;
    s32 n = sizeof(D_80755F50) / sizeof(D_80755F50[0]);

    for (i = 0; i < n; i++) {
        if (id == D_80755F50[i].id) {
            return D_80755F50[i].value;
        }
    }
    return 0;
}

s32 flagGridIndex(s32 baseFlag, s32 row, s32 col) {
    s32 r = -1;

    if (row < 8) {
        if (col < 5) {
            r = baseFlag + row * 5 + col;
        }
    }
    return r;
}

s32 flagGridSumRows(s32 baseFlag, s32 startRow, s32 endRow, s32 col) {
    s32 sum = 0;
    s32 i;
    s32 r;

    if (col >= 5) {
        return 0;
    }
    for (i = startRow; i <= endRow; i++) {
        r = flagGridIndex(baseFlag, i, col);
        if (r >= 0) {
            sum += flagGet(r, 0);
        }
    }
    return sum;
}

s32 flagCountRange(s32 startFlag, s32 count, u8 bank) {
    s32 sum = 0;
    s32 i;

    for (i = startFlag; i < startFlag + count; i++) {
        sum += flagGet(i, bank);
    }
    return sum;
}
