#include "common.h"
#include "actor.h"
#include "proto/global/104F0.h"
#include "proto/global/135D30.h"
#include "proto/global/3C10.h"

typedef struct FlagTableEntry {
    /* 0x0 */ u8 map;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 id;
    /* 0x4 */ s16 flag;
    /* 0x6 */ u8 value;
    /* 0x7 */ u8 active;
} FlagTableEntry;

typedef struct FlagTableEntry4 {
    /* 0x0 */ s16 id;
    /* 0x2 */ u8 value;
    /* 0x3 */ u8 pad3;
} FlagTableEntry4;

FlagTableEntry gFlagTempEntries[0x18];
u8 gFlagBank2[14];
extern FlagTableEntry D_80755A20[];
extern FlagTableEntry D_80755DA8[];
extern FlagTableEntry D_80755EA0[];
extern FlagTableEntry4 D_80755F4C[];
extern FlagTableEntry4 D_80755F50[];


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

typedef struct FlagRange {
    s16 first;
    s16 last;
    s16 required;
    s16 rewardFlag;
} FlagRange;

extern FlagRange D_80756024[];

void flagUpdateRangeCompletion(s16 flag) {
    u32 i;
    s32 res = -1;
    FlagRange *e;

    for (i = 0; i < 0x21 && res == -1; i++) {
        e = &D_80756024[i];
        if (flag >= e->first && flag <= e->last) {
            if (flagCountRange(e->first, e->last - e->first + 1, 0) == e->required) {
                res = e->rewardFlag;
            }
        }
    }
    if (i == 0x99) {}  // FAKE: dead read of i after the loop keeps counter s1 beside pointer s0 (no LFTR end pointer, Q0262)
    if (flag == 0x99) {}  // FAKE: with the i read keeps flag in s3 and res in s2 (Q0262)
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
    s32 n = 0x71; // FAKE: bound local blocks LFTR (a literal bound compares an end pointer instead of the counter, Q0582)

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
    s32 n = 0x71; // FAKE: bound local blocks LFTR (a literal bound compares an end pointer instead of the counter, Q0582)

    for (i = 0; i < n; i++) {
        if (map == D_80755A20[i].map && id == D_80755A20[i].id) {
            return flagGet(D_80755A20[i].flag, 0);
        }
    }
    return 0;
}

u8 flagValueForMapObject(s16 map, s16 id) {
    s32 i;
    s32 n = 0x71; // FAKE: bound local blocks LFTR (a literal bound compares an end pointer instead of the counter, Q0582)

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
    FlagTableEntry *e; s32 n = 0x1F; s32 i; s16 val = map; // FAKE: n/val copies keep map in a0, id in a3, base in t0 (Q0582); LAYOUT: one line (as1 prologue order)
    *outIdx = 0; for (i = 0; i < n; ) { // LAYOUT: joined with the loop header
        e = D_80755DA8 + i;
        if (val == e->map && id == e->id) {
            return e->flag;
        }
        *outIdx = i + 1;
        i |= 0; // FAKE: no-code def keeps i + 1 in ring temp t3 instead of reusing a1 (Q0500)
        i = *outIdx;
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
    s32 n = 0x16; // FAKE: bound local blocks LFTR (a literal bound compares an end pointer instead of the counter, Q0582)
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
    s32 n = 0x35; // FAKE: bound local blocks LFTR (a literal bound compares an end pointer instead of the counter, Q0582)

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
