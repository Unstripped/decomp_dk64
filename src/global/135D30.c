#include "common.h"
#include "actor.h"

typedef struct E2Ent {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} E2Ent;

typedef struct E2B8 {
    u8 unk0;
    u8 pad[7];
} E2B8;

typedef struct E2Ent4 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 pad3;
} E2Ent4;

extern u8 D_807FDD90[14];
extern E2Ent D_80755A20[];
extern E2B8 D_80755DAE[];
extern E2Ent D_80755EA0[];
extern E2Ent4 D_80755F4C[];
extern E2Ent4 D_80755F50[];

u8 func_8073110C(s16, u8);
void func_8073129C(s16, u8, u8);
void func_807311C4(s16);
s32 func_80731784(s16, s16, s32 *);
s32 func_80731AA8(s32, s32, u8);
u8 *func_8060E25C(u8);

#ifdef NON_MATCHING
extern u8 D_807FDD92[12];

void func_80731030(void) {
    s32 i;

    D_807FDD90[0] = 0;
    D_807FDD90[1] = 0;
    for (i = 0; i < 12; i++) {
        D_807FDD92[i] = 0;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/135D30/func_80731030.s")
#endif

void func_8073106C(void) {
    s32 i;

    for (i = 0; i < 0x316; i++) {
        func_8073129C(i, 0, 0);
    }
}

void func_807310BC(void) {
    s32 i;

    for (i = 0; i < 0x2C; i++) {
        func_8073129C(i, 0, 1);
    }
}

u8 func_8073110C(s16 arg0, u8 arg1) {
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

#ifdef NON_MATCHING
typedef struct E2Rng {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} E2Rng;

extern E2Rng D_80756024[];

void func_807311C4(s16 arg0) {
    u32 i;
    s32 res = -1;
    E2Rng *e = D_80756024;

    for (i = 0; i < 0x21 && res == -1; i++, e++) {
        if (arg0 >= e->unk0 && arg0 <= e->unk2) {
            if (func_80731AA8(e->unk0, e->unk2 - e->unk0 + 1, 0) == e->unk4) {
                res = e->unk6;
            }
        }
    }
    if (res >= 0) {
        func_8073129C(res, 1, 1);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/135D30/func_807311C4.s")
#endif

void func_8073129C(s16 arg0, u8 arg1, u8 arg2) {
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
        func_807311C4(arg0);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/135D30/func_807313BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/135D30/func_80731410.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/135D30/func_807314F4.s")

s32 func_807315D4(s16 arg0, s16 arg1) {
    s32 i;
    s32 n = 0x71;

    for (i = 0; i < n; i++) {
        if (arg0 == D_80755A20[i].unk0 && arg1 == D_80755A20[i].unk2) {
            return func_8073110C(D_80755A20[i].unk4, 0);
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/135D30/func_80731654.s")

#ifdef NON_MATCHING
extern E2Ent D_80755DA8[];

s32 func_80731784(s16 arg0, s16 arg1, s32 *arg2) {
    E2Ent *e;
    s32 n = 0x1F;
    s32 i;

    *arg2 = 0;
    for (i = 0; i < n; i++) {
        e = &D_80755DA8[i ^ 0];
        if (arg0 == e->unk0 && arg1 == e->unk2) {
            return e->unk4;
        }
        *arg2 = i + 1;
    }
    return -1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/135D30/func_80731784.s")
#endif
s32 func_807317FC(s16 arg0, s16 arg1) {
    s32 r;
    s32 idx;
    u8 flag;

    r = func_80731784(arg0, arg1, &idx);
    if (r >= 0) {
        flag = func_8073110C(r, 0);
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

s32 func_807318AC(s16 arg0, s16 arg1) {
    s32 n = 0x16;
    s32 i;
    E2Ent *e;

    for (i = 0; i < n; i++) {
        e = &D_80755EA0[i];
        if (arg0 == e->unk0 && arg1 == e->unk2) {
            if (func_8073110C(e->unk4, 0) != 0) {
                return 0;
            }
            if (e->unk6 != 0) {
                func_8073129C(e->unk4, 1, 0);
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

s32 func_807319D8(s32 arg0, s32 arg1, s32 arg2) {
    s32 r = -1;

    if (arg1 < 8) {
        if (arg2 < 5) {
            r = arg0 + arg1 * 5 + arg2;
        }
    }
    return r;
}

s32 func_80731A04(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sum = 0;
    s32 i;
    s32 r;

    if (arg3 >= 5) {
        return 0;
    }
    for (i = arg1; i <= arg2; i++) {
        r = func_807319D8(arg0, i, arg3);
        if (r >= 0) {
            sum += func_8073110C(r, 0);
        }
    }
    return sum;
}

s32 func_80731AA8(s32 arg0, s32 arg1, u8 arg2) {
    s32 sum = 0;
    s32 i;

    for (i = arg0; i < arg0 + arg1; i++) {
        sum += func_8073110C(i, arg2);
    }
    return sum;
}
