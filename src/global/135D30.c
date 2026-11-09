#include "common.h"
#include "actor.h"
#define PROTO_SKIP_func_8060E25C // FAKE: callee prototype steer
#include "proto/global/104F0.h"
#include "proto/global/135D30.h"
#include "proto/global/3C10.h"

typedef struct FlagTableEntry {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} FlagTableEntry;

typedef struct FlagTableByte8 {
    u8 unk0;
    u8 pad[7];
} FlagTableByte8;

typedef struct FlagTableEntry4 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 pad3;
} FlagTableEntry4;

FlagTableEntry D_807FDCD0[0x18];
u8 D_807FDD90[14];
extern FlagTableEntry D_80755A20[];
extern FlagTableByte8 D_80755DAE[];
extern FlagTableEntry D_80755EA0[];
extern FlagTableEntry4 D_80755F4C[];
extern FlagTableEntry4 D_80755F50[];

u8 *func_8060E25C(u8); // FAKE: callee prototype steer

void flagsClearAllBank2(void) {
    s32 i;

    for (i = 0; i < 14; i++) {
        D_807FDD90[i] = 0;
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
        base = func_8060E25C(bank);
        break;
    case 2:
        base = D_807FDD90;
        break;
    }
    idx = flag >> 3;
    return (base[idx] >> (s16)(flag - idx * 8)) & 1;
}

typedef struct FlagRange {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} FlagRange;

extern FlagRange D_80756024[];

void flagUpdateRangeCompletion(s16 flag) {
    u32 i;
    s32 res = -1;
    FlagRange *e;

    for (i = 0; i < 0x21 && res == -1; i++) {
        e = &D_80756024[i];
        if (flag >= e->unk0 && flag <= e->unk2) {
            if (flagCountRange(e->unk0, e->unk2 - e->unk0 + 1, 0) == e->unk4) {
                res = e->unk6;
            }
        }
    }
    if (i == 0x99) {
    }
    if (flag == 0x99) {
    }
    if (res >= 0) {
        flagSet(res, 1, 1);
    }
}

void flagSet(s16 flag, u8 val, u8 bank) {
    u8 *base;
    s16 idx;
    u8 mode = bank;
    s32 pad;

    if (flag == -1) {
        return;
    }
    switch (mode) {
    case 0:
    case 1:
        base = func_8060E25C(mode);
        break;
    case 2:
        base = D_807FDD90;
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

extern FlagTableEntry D_807FDCD0[];

void func_807313BC(void) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (mapFindSlotByMap(D_807FDCD0[i].unk0) == 0) {
            D_807FDCD0[i].unk7 = 0;
        }
    }
}

void func_80731410(s16 map, s16 id, s16 flag, u8 val) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (D_807FDCD0[i].unk7 == 0) {
            D_807FDCD0[i].unk0 = map;
            D_807FDCD0[i].unk2 = id;
            D_807FDCD0[i].unk4 = flag;
            D_807FDCD0[i].unk6 = val;
            D_807FDCD0[i].unk7 = 1;
            return;
        }
    }
}

void func_807314F4(s16 map, s16 id) {
    s32 i;
    s32 n = 0x71;

    for (i = 0; i < n; i++) {
        if (map == D_80755A20[i].unk0 && id == D_80755A20[i].unk2) {
            flagSet(D_80755A20[i].unk4, 1, 0);
            return;
        }
    }
    for (i = 0; i < 0x18; i++) {
        if (D_807FDCD0[i].unk7 != 0 && map == D_807FDCD0[i].unk0 && id == D_807FDCD0[i].unk2) {
            flagSet(D_807FDCD0[i].unk4, 1, 0);
            D_807FDCD0[i].unk7 = 0;
            return;
        }
    }
}

s32 func_807315D4(s16 map, s16 id) {
    s32 i;
    s32 n = 0x71;

    for (i = 0; i < n; i++) {
        if (map == D_80755A20[i].unk0 && id == D_80755A20[i].unk2) {
            return flagGet(D_80755A20[i].unk4, 0);
        }
    }
    return 0;
}

u8 func_80731654(s16 map, s16 id) {
    s32 i;
    s32 n = 0x71;

    for (i = 0; i < n; i++) {
        if (map == D_80755A20[i].unk0 && id == D_80755A20[i].unk2) {
            return D_80755A20[i].unk6;
        }
    }
    for (i = 0; i < 0x18; i++) {
        if (D_807FDCD0[i].unk7 != 0 && map == D_807FDCD0[i].unk0 && id == D_807FDCD0[i].unk2) {
            return D_807FDCD0[i].unk6;
        }
    }
    return 0;
}

extern FlagTableEntry D_80755DA8[];

s32 spawnFlagLookup(s16 map, s16 id, s32 *outIdx) {
    FlagTableEntry *e; s32 n = 0x1F; s32 i; s16 val = map; // LAYOUT: one line (as1 prologue order)
    *outIdx = 0; for (i = 0; i < n; ) { // LAYOUT: joined with the loop header
        e = D_80755DA8 + i;
        if (val == e->unk0 && id == e->unk2) {
            return e->unk4;
        }
        *outIdx = i + 1;
        i |= 0; // FAKE: no-code def kills the i + 1 CSE so the store keeps a ring temp
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
        if (flag != 0 && D_80755DAE[idx].unk0 != 0) {
            return 1;
        }
        if (flag == 0 && D_80755DAE[idx].unk0 == 0) {
            return 1;
        }
        return 0;
    }
    return 1;
}

s32 flagTryTriggerOnce(s16 map, s16 id) {
    s32 n = 0x16;
    s32 i;
    FlagTableEntry *e;

    for (i = 0; i < n; i++) {
        e = &D_80755EA0[i];
        if (map == e->unk0 && id == e->unk2) {
            if (flagGet(e->unk4, 0) != 0) {
                return 0;
            }
            if (e->unk6 != 0) {
                flagSet(e->unk4, 1, 0);
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
    return D_80755F4C[index].unk0;
}

u8 func_8073198C(s16 id) {
    s32 i;
    s32 n = 0x35;

    for (i = 0; i < n; i++) {
        if (id == D_80755F50[i].unk0) {
            return D_80755F50[i].unk2;
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
