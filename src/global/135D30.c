#include "common.h"
#include "actor.h"

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

u8 flagGet(s16, u8);
void flagSet(s16, u8, u8);
void flagUpdateRangeCompletion(s16);
s32 func_80731784(s16, s16, s32 *);
s32 flagCountRange(s32, s32, u8);
u8 *func_8060E25C(u8);

void func_80731030(void) {
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

u8 flagGet(s16 arg0, u8 arg1) {
    u8 *base;
    s16 idx;

    if (arg0 == -1) {
        return 0;
    }
    switch (arg1) {
    case 0:
    case 1:
        base = func_8060E25C(arg1);
        break;
    case 2:
        base = D_807FDD90;
        break;
    }
    idx = arg0 >> 3;
    return (base[idx] >> (s16)(arg0 - idx * 8)) & 1;
}

typedef struct FlagRange {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} FlagRange;

extern FlagRange D_80756024[];

void flagUpdateRangeCompletion(s16 arg0) {
    u32 i;
    s32 res = -1;
    FlagRange *e;

    for (i = 0; i < 0x21 && res == -1; i++) {
        e = &D_80756024[i];
        if (arg0 >= e->unk0 && arg0 <= e->unk2) {
            if (flagCountRange(e->unk0, e->unk2 - e->unk0 + 1, 0) == e->unk4) {
                res = e->unk6;
            }
        }
    }
    if (i == 0x99) {
    }
    if (arg0 == 0x99) {
    }
    if (res >= 0) {
        flagSet(res, 1, 1);
    }
}

void flagSet(s16 arg0, u8 arg1, u8 arg2) {
    u8 *base;
    s16 idx;
    u8 mode = arg2;
    s32 pad;

    if (arg0 == -1) {
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
    idx = arg0 >> 3;
    if (arg1) {
        base[idx] |= 1 << (s16)(arg0 - idx * 8);
    } else {
        base[idx] &= ~(1 << (s16)(arg0 - idx * 8));
    }
    if (arg1 != 0 && arg2 == 0) {
        flagUpdateRangeCompletion(arg0);
    }
}

extern FlagTableEntry D_807FDCD0[];
s32 func_805FF938(s16);

void func_807313BC(void) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (func_805FF938(D_807FDCD0[i].unk0) == 0) {
            D_807FDCD0[i].unk7 = 0;
        }
    }
}

void func_80731410(s16 arg0, s16 arg1, s16 arg2, u8 arg3) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (D_807FDCD0[i].unk7 == 0) {
            D_807FDCD0[i].unk0 = arg0;
            D_807FDCD0[i].unk2 = arg1;
            D_807FDCD0[i].unk4 = arg2;
            D_807FDCD0[i].unk6 = arg3;
            D_807FDCD0[i].unk7 = 1;
            return;
        }
    }
}

void func_807314F4(s16 arg0, s16 arg1) {
    s32 i;
    s32 n = 0x71;

    for (i = 0; i < n; i++) {
        if (arg0 == D_80755A20[i].unk0 && arg1 == D_80755A20[i].unk2) {
            flagSet(D_80755A20[i].unk4, 1, 0);
            return;
        }
    }
    for (i = 0; i < 0x18; i++) {
        if (D_807FDCD0[i].unk7 != 0 && arg0 == D_807FDCD0[i].unk0 && arg1 == D_807FDCD0[i].unk2) {
            flagSet(D_807FDCD0[i].unk4, 1, 0);
            D_807FDCD0[i].unk7 = 0;
            return;
        }
    }
}

s32 func_807315D4(s16 arg0, s16 arg1) {
    s32 i;
    s32 n = 0x71;

    for (i = 0; i < n; i++) {
        if (arg0 == D_80755A20[i].unk0 && arg1 == D_80755A20[i].unk2) {
            return flagGet(D_80755A20[i].unk4, 0);
        }
    }
    return 0;
}

u8 func_80731654(s16 arg0, s16 arg1) {
    s32 i;
    s32 n = 0x71;

    for (i = 0; i < n; i++) {
        if (arg0 == D_80755A20[i].unk0 && arg1 == D_80755A20[i].unk2) {
            return D_80755A20[i].unk6;
        }
    }
    for (i = 0; i < 0x18; i++) {
        if (D_807FDCD0[i].unk7 != 0 && arg0 == D_807FDCD0[i].unk0 && arg1 == D_807FDCD0[i].unk2) {
            return D_807FDCD0[i].unk6;
        }
    }
    return 0;
}

#ifdef NON_MATCHING
extern FlagTableEntry D_80755DA8[];

s32 func_80731784(s16 arg0, s16 arg1, s32 *arg2) {
    FlagTableEntry *e; s32 n = 0x1F; s32 i = 0; s16 val = arg0;
    *arg2 = 0; for (; i < n; ) {
        e = D_80755DA8 + i;
        if (val == e->unk0 && arg1 == e->unk2) {
            return e->unk4;
        }
        *arg2 = i + 1;
        i++;
    }
    return -1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/135D30/func_80731784.s")
#endif
s32 spawnFlagConditionMet(s16 arg0, s16 arg1) {
    s32 r;
    s32 idx;
    u8 flag;

    r = func_80731784(arg0, arg1, &idx);
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

s32 flagTryTriggerOnce(s16 arg0, s16 arg1) {
    s32 n = 0x16;
    s32 i;
    FlagTableEntry *e;

    for (i = 0; i < n; i++) {
        e = &D_80755EA0[i];
        if (arg0 == e->unk0 && arg1 == e->unk2) {
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

s32 func_8073195C(s16 arg0) {
    if (arg0 == 0) {
        return -1;
    }
    return D_80755F4C[arg0].unk0;
}

u8 func_8073198C(s16 arg0) {
    s32 i;
    s32 n = 0x35;

    for (i = 0; i < n; i++) {
        if (arg0 == D_80755F50[i].unk0) {
            return D_80755F50[i].unk2;
        }
    }
    return 0;
}

s32 flagGridIndex(s32 arg0, s32 arg1, s32 arg2) {
    s32 r = -1;

    if (arg1 < 8) {
        if (arg2 < 5) {
            r = arg0 + arg1 * 5 + arg2;
        }
    }
    return r;
}

s32 flagGridSumRows(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sum = 0;
    s32 i;
    s32 r;

    if (arg3 >= 5) {
        return 0;
    }
    for (i = arg1; i <= arg2; i++) {
        r = flagGridIndex(arg0, i, arg3);
        if (r >= 0) {
            sum += flagGet(r, 0);
        }
    }
    return sum;
}

s32 flagCountRange(s32 arg0, s32 arg1, u8 arg2) {
    s32 sum = 0;
    s32 i;

    for (i = arg0; i < arg0 + arg1; i++) {
        sum += flagGet(i, arg2);
    }
    return sum;
}
