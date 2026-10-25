#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern u16 D_807FD63C;

typedef struct G21Actor1A0 {
    /* 0x00 */ u8 pad0[0x8C];
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[0x1A3 - 0x8D];
    /* 0x1A3 */ u8 unk1A3;
    /* 0x1A4 */ u8 unk1A4;
} G21Actor1A0;

void func_80614E78(void *, s32);
s32 func_806F8AD4(u8, u8);
void func_806F8BC4(s32, s32, s32);

void func_806DF390(s32 arg0, G21Actor1A0 *arg1, u8 arg2) {
    s32 id;

    id = 0x4A;
    if (arg2) {
        id = 0x4C;
    }
    arg1->unk1A3 = 0;
    func_80614E78((void *)arg0, id);
}

void func_806DF3D0(s32 arg0, G21Actor1A0 *arg1, u8 arg2) {
    s32 id;
    s32 a;

    id = 0x4B;
    a = 2;
    if (func_806F8AD4(3, arg1->unk1A4)) {
        a = 3;
    }
    func_806F8BC4(a, 0, 0);
    if (arg2) {
        id = 0x4D;
    }
    func_80614E78((void *)arg0, id);
}

void func_806DF44C(s32 arg0, G21Actor1A0 *arg1, u8 arg2) {
    if (arg1->unk8C) {
        func_806DF390(arg0, arg1, arg2);
    } else {
        func_806DF3D0(arg0, arg1, arg2);
    }
}

void func_806DF494(s16 *arg0, s16 arg1, s16 arg2) {
    s16 temp_v0;
    s16 var_a2;
    s32 var_t0;
    s16 step;

    arg1 &= 0xFFF;
    temp_v0 = arg1 - *arg0;
    if (temp_v0 != 0) {
        if (temp_v0 > 0) {
            var_a2 = temp_v0;
        } else {
            var_a2 = -temp_v0;
        }
        step = arg2;
        temp_v0 = temp_v0 / var_a2;
        if (var_a2 > 0x800) {
            var_a2 = 0x1000 - var_a2;
            temp_v0 = temp_v0 * -1;
        }
        if (step > 0) {
            var_t0 = step;
        } else {
            var_t0 = -step;
        }
        if (var_a2 < var_t0) {
            *arg0 = arg1;
            return;
        }
        *arg0 = *arg0 + (temp_v0 * step);
        *arg0 &= 0xFFF;
    }
}

void func_806DF5A0(s16 *arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 temp_v0;
    s16 var_a2;

    arg1 = arg1 & 0xFFF;
    temp_v0 = arg1 - *arg0;
    if (temp_v0 != 0) {
        if (temp_v0 > 0) {
            var_a2 = temp_v0;
        } else {
            var_a2 = -temp_v0;
        }
        temp_v0 = temp_v0 & 0xFFF;
        if (var_a2 > 0x800) {
            var_a2 = 0x1000 - var_a2;
        }
        if (arg2 >= var_a2) {
            *arg0 = arg1;
        } else if (arg3 < temp_v0) {
            *arg0 = *arg0 - arg2;
        } else {
            *arg0 = *arg0 + arg2;
        }
        *arg0 &= 0xFFF;
    }
}

void func_806DF670(s16 *arg0, s16 arg1, s16 arg2) {
    s16 temp_v0;

    temp_v0 = arg1 - *arg0;
    if (temp_v0 != 0) {
        if (((s16) (temp_v0 & 0xFFF) + arg2) >= 0x1000) {
            *arg0 = arg1;
            return;
        }
        *arg0 = (*arg0 + arg2) & 0xFFF;
    }
}

typedef struct G21Table {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10[4];
    /* 0x20 */ s16 unk20[4];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ s8 unk2E;
    /* 0x2F */ s8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 pad32[2];
} G21Table; // size = 0x34

extern G21Table D_807FD610[];

#ifdef NON_MATCHING
u16 func_806DFF34(u16, u16 *);
f32 func_80611BB4(f32, f32);
f32 sqrtf(f32);

typedef struct LE40Ctl {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ s8 unk2;
    /* 0x3 */ s8 unk3;
} LE40Ctl;

typedef struct LE40Tbl {
    void (*fn[17])(void);
} LE40Tbl;

typedef struct LE40Player {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
} LE40Player;

#define LE40_P ((LE40Player *)D_807FD580)
#define LE40_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))
#define LE40_E D_807FD610[D_807FC929]
#define LE40_Q ((G21Table *)((u8 *)D_807FD610 + D_807FC929 * 0x34))
#define LE40_MAX(a, b) ((a) > (b) ? (a) : (b))
#define LE40_MIN(a, b) ((a) < (b) ? (a) : (b))

extern struct G29BtnA D_807FD63A[];
extern struct G31Cam *D_807FC924;
extern LE40Ctl *D_807ECDEC;
extern u16 D_807ECDF0;
extern u16 D_80750FF0[];
extern LE40Tbl D_80751004[];

s32 func_806DF6D4(s32 arg0) {
    f32 a;
    f32 b;
    f32 hi;
    f32 mag;
    s32 t;
    s32 i;
    s32 old;
    s16 ang;

    old = D_807FBB48->unk154;
    ang = -80;
    LE40_PAD(D_807FD63A, u16) = func_806DFF34(D_807ECDEC->unk0, D_80750FF0);
    LE40_E.unk2C = func_806DFF34(D_807ECDF0, D_80750FF0);
    if (LE40_P->unk1F4 & 0x20) {
        LE40_E.unk2A = 0;
        LE40_E.unk2C = 0;
    }
    D_807ECDEC->unk2 = LE40_MIN((D_807ECDEC->unk2 > ang ? D_807ECDEC->unk2 : -80), 80);
    D_807ECDEC->unk3 = LE40_MIN(LE40_MAX(D_807ECDEC->unk3, -80), 80);
    LE40_E.unk2E = D_807ECDEC->unk2;
    LE40_E.unk2F = D_807ECDEC->unk3;
    if (LE40_P->unk1F4 & 0x20) {
        LE40_E.unk2E = 0;
        LE40_E.unk2F = 0;
    }
    if (LE40_P->unk1F0 & 0x100) {
        LE40_E.unk2E = LE40_E.unk2E * 0.5;
        LE40_E.unk2F = LE40_E.unk2F * 0.5;
    }
    if (LE40_P->unk1F0 & 0x80) {
        LE40_E.unk2E = -LE40_E.unk2E;
        LE40_E.unk2F = -LE40_E.unk2F;
    }
    if (LE40_E.unk2E > 0) {
        LE40_E.unk30 = LE40_E.unk2E;
    } else {
        LE40_E.unk30 = -LE40_E.unk2E;
    }
    if (LE40_E.unk2F > 0) {
        LE40_E.unk31 = LE40_E.unk2F;
    } else {
        LE40_E.unk31 = -LE40_E.unk2F;
    }
    if (LE40_E.unk30 < 5 && LE40_E.unk31 < 5) {
        LE40_E.unk2E = 0;
        LE40_E.unk30 = 0;
        LE40_E.unk2F = 0;
        LE40_E.unk31 = 0;
    }
    if (LE40_E.unk30 < 2) {
        LE40_E.unk2E = 0;
        LE40_E.unk30 = 0;
    }
    if (LE40_E.unk31 < 2) {
        LE40_E.unk2F = 0;
        LE40_E.unk31 = 0;
    }
    a = LE40_E.unk30 * LE40_E.unk30;
    b = LE40_E.unk31 * LE40_E.unk31;
    mag = sqrtf(a + b);
    if (b < a) {
        hi = a;
        a = b;
        b = hi;
    }
    if (b != 0.0f) {
        hi = (f32)(1.0 - (a / b) * 0.15);
        mag = mag * hi;
    }
    if (mag > 70.0f) {
        mag = 70.0f;
    }
    LE40_Q->unkC = mag - LE40_Q->unk4;
    LE40_Q->unk4 = mag;
    if (mag != 0.0f) {
        LE40_Q->unk0 = 0;
        LE40_Q->unk8 = (mag - 5.0f) / 65.0f;
    } else {
        LE40_Q->unk8 = 0.0f;
        LE40_Q->unk0 = LE40_Q->unk0 + 1;
    }
    if (mag != 0.0f) {
        t = ang = func_80611BB4(LE40_Q->unk2E, -LE40_Q->unk2F) * 4096.0f / 6.2831855f;
        LE40_Q->unk28 = (*(s16 *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x2C8) + t) & 0xFFF;
    } else {
        ang = LE40_Q->unk20[D_807FC929 * 0];
    }
    for (i = 3; (i ^ 0) != 0; i--) {
        LE40_E.unk20[i] = LE40_E.unk20[i - 1];
        LE40_E.unk10[i] = LE40_E.unk10[i - 1];
        if (LE40_E.unk2E) {
        }
        if (D_807FC929) {
        }
    }
    LE40_Q->unk20[0] = ang;
    LE40_Q->unk10[0] = mag;
    D_80751004[arg0].fn[1]();
    if (LE40_PAD(D_807FD63A, u16) & 0x1000) {
        D_80751004[arg0].fn[0]();
    }
    if (LE40_PAD(D_807FD63A, u16) & 0x8000) {
        D_80751004[arg0].fn[2]();
    } else {
        D_80751004[arg0].fn[5]();
    }
    if (LE40_PAD(D_807FD63A, u16) & 0x4000) {
        D_80751004[arg0].fn[3]();
    } else {
        D_80751004[arg0].fn[6]();
    }
    if (LE40_PAD(D_807FD63A, u16) & 0x2000) {
        D_80751004[arg0].fn[4]();
    } else {
        D_80751004[arg0].fn[7]();
    }
    if (LE40_PAD(D_807FD63A, u16) & 0x10) {
        D_80751004[arg0].fn[9]();
    } else {
        D_80751004[arg0].fn[11]();
    }
    if (LE40_PAD(D_807FD63A, u16) & 0x20) {
        D_80751004[arg0].fn[8]();
    }
    if (LE40_PAD(D_807FD63A, u16) & 8) {
        D_80751004[arg0].fn[12]();
    }
    if (LE40_PAD(D_807FD63A, u16) & 4) {
        D_80751004[arg0].fn[15]();
    }
    if (LE40_PAD(D_807FD63A, u16) & 2) {
        D_80751004[arg0].fn[13]();
    }
    if (LE40_PAD(D_807FD63A, u16) & 1) {
        D_80751004[arg0].fn[14]();
    }
    if (!D_807FD610) {
        if (!LE40_E.unk2F) {
        }
    }
    D_80751004[arg0].fn[16]();
    return D_807FBB48->unk154 - old;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806DF6D4.s")
#endif

#ifdef NON_MATCHING
u16 func_806DFF34(u16 arg0, u16 *arg1) {
    u32 var_v0;
    u16 var_v1;
    u16 var_a2;

    var_v0 = *arg1;
    var_v1 = 0;
    var_a2 = 0;
    if (var_v0 != 0) {
        do {
            var_v1 |= var_v0;
            if (&arg0) {}
            arg1++;
            if (var_v0 & arg0) {}
            if (var_v0 & arg0) {
                var_a2 |= arg1[0];
            }
            var_v0 = arg1[1];
            arg1++;
        } while (var_v0 != 0);
    }
    return var_a2 | (arg0 & ~var_v1);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806DFF34.s")
#endif

f32 func_80612790(s16);

f32 func_806DFFA0(f32 arg0, s16 arg1, s16 arg2) {
    return func_80612790(arg2 - arg1) * arg0;
}

typedef struct G21Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ u8 pad8[2];
    /* 0x00A */ s16 unkA;
    /* 0x00C */ u8 padC[0x28];
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[0xC];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0x7E];
    /* 0x0C8 */ s16 unkC8;
    /* 0x0CA */ u8 padCA[0xC];
    /* 0x0D6 */ s16 unkD6;
    /* 0x0D8 */ u8 padD8[0x11C];
    /* 0x1F4 */ s32 unk1F4;
} G21Player;

#define G21_PLAYER ((G21Player *)D_807FD580)

void func_806DFFDC(s16 arg0) {
    f32 temp;

    temp = func_806DFFA0(G21_PLAYER->unk4, G21_PLAYER->unkA, arg0);
    if (temp > 0.0f) {
        G21_PLAYER->unk4 = temp;
    } else {
        G21_PLAYER->unk4 = 0.0f;
    }
    G21_PLAYER->unkA = arg0;
}

void func_806E0050(void) {
    G21_PLAYER->unk4 = 0.0f;
    G21_PLAYER->unkA = D_807FBB40->unkE6;
}


void func_806E007C(void) {
    f32 temp_fv1;
    f32 var_fv0;
    G21Table *temp_v1;

    var_fv0 = G21_PLAYER->unk38;
    if (G21_PLAYER->unkC8 == 0) {
        var_fv0 = var_fv0 * 0.5;
    }
    if (G21_PLAYER->unkD6 != 0) {
        var_fv0 = var_fv0 * 0.5;
    }
    temp_v1 = &D_807FD610[D_807FC929];
    if ((temp_v1->unk4 != 0.0f) && !(G21_PLAYER->unk1F4 & 8)) {
        temp_fv1 = G21_PLAYER->unk34;
        G21_PLAYER->unk4 = (temp_v1->unk8 * (var_fv0 - temp_fv1)) + temp_fv1;
        G21_PLAYER->unkA = D_807FD610[D_807FC929].unk28;
        return;
    }
    G21_PLAYER->unk4 = 0.0f;
    G21_PLAYER->unkA = D_807FBB40->unkE6;
}

typedef struct G21ActorEE {
    /* 0x00 */ u8 pad0[0xD8];
    /* 0xD8 */ s16 unkD8;
    /* 0xDA */ s16 unkDA;
    /* 0xDC */ u8 padDC[0xA];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[2];
    /* 0xEA */ s16 unkEA;
    /* 0xEC */ u8 padEC[2];
    /* 0xEE */ s16 unkEE;
} G21ActorEE;

#define G21_ACTOR_EE ((G21ActorEE *)D_807FBB40)

extern u8 D_807FD618[];

void func_806E0178(void) {
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_v0;

    func_806E007C();
    var_fv1 = *(f32 *)(D_807FD618 + D_807FC929 * 0x34);
    if ((f64)var_fv1 < 0.3) {
        var_fv1 = 0.3f;
    }
    temp_v0 = G21_ACTOR_EE->unkEE - G21_PLAYER->unkA;
    if (temp_v0 > 0) {
        var_fv0 = (f32)temp_v0;
    } else {
        var_fv0 = (f32)-temp_v0;
    }
    if (var_fv0 > 2048.0f) {
        var_fv0 = 4096.0f - var_fv0;
    }
    if (var_fv0 > 400.0f) {
        var_fv0 = 400.0f;
    }
    var_fv0 = var_fv0 * 0.2;
    func_806DF494(&G21_ACTOR_EE->unkEE, G21_PLAYER->unkA, (s16)(s32)(var_fv0 * var_fv1));
}

void func_806E0294(void) {
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_v0;

    func_806E007C();
    var_fv1 = *(f32 *)(D_807FD618 + D_807FC929 * 0x34);
    if ((f64)var_fv1 < 0.3) {
        var_fv1 = 0.3f;
    }
    temp_v0 = G21_ACTOR_EE->unkEE - G21_PLAYER->unkA;
    if (temp_v0 > 0) {
        var_fv0 = (f32)temp_v0;
    } else {
        var_fv0 = (f32)-temp_v0;
    }
    if (var_fv0 > 2048.0f) {
        var_fv0 = 4096.0f - var_fv0;
    }
    if (var_fv0 > 400.0f) {
        var_fv0 = 400.0f;
    }
    var_fv0 = var_fv0 * ((f64)G21_PLAYER->unk48 / 400.0);
    func_806DF494(&D_807FBB40->unkE6, G21_PLAYER->unkA, (s16)(s32)(var_fv0 * var_fv1));
}

extern u8 D_807FD640[];

f32 func_806E03C8(f32 arg0, f32 arg1) {
    f32 var_fv1;
    u8 temp_v0;

    temp_v0 = D_807FD640[D_807FC929 * 0x34];
    if (temp_v0 != 0) {
        temp_v0 = D_807FD640[D_807FC929 * 0x34];
        if (temp_v0 >= 0x47) {
            var_fv1 = 70.0f;
        } else {
            var_fv1 = (s32)temp_v0;
        }
        var_fv1 -= 2.0f;
        var_fv1 /= 68.0f;
        return ((arg1 - arg0) * var_fv1) + arg0;
    }
    return 0.0f;
}

extern u8 D_807FD641[];

f32 func_806E0454(f32 arg0, f32 arg1) {
    f32 var_fv1;
    u8 temp_v0;

    temp_v0 = D_807FD641[D_807FC929 * 0x34];
    if (temp_v0 != 0) {
        temp_v0 = D_807FD641[D_807FC929 * 0x34];
        if (temp_v0 >= 0x47) {
            var_fv1 = 70.0f;
        } else {
            var_fv1 = (s32)temp_v0;
        }
        var_fv1 -= 2.0f;
        var_fv1 /= 68.0f;
        return ((arg1 - arg0) * var_fv1) + arg0;
    }
    return 0.0f;
}

void func_806E04E0(void) {
    f32 temp_fv0;
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_v0;
    G21Table *temp_v1;

    func_806E007C();
    temp_v1 = &D_807FD610[D_807FC929];
    temp_fv0 = temp_v1->unkC;
    if (temp_fv0 > 0.0f) {
        var_fv1 = temp_fv0;
    } else {
        var_fv1 = -temp_fv0;
    }
    if (var_fv1 < 14.0f) {
        var_fv1 = (temp_v1->unk8 * 0.7) + 0.3;
        temp_v0 = D_807FBB40->unkE6 - G21_PLAYER->unkA;
        if (temp_v0 > 0) {
            var_fv0 = (f32)temp_v0;
        } else {
            var_fv0 = (f32)-temp_v0;
        }
        if (var_fv0 > 2048.0f) {
            var_fv0 = 4096.0f - var_fv0;
        }
        if (var_fv0 > 400.0f) {
            var_fv0 = 400.0f;
        }
        var_fv0 = var_fv0 * ((f64)G21_PLAYER->unk48 / 400.0);
        func_806DF494(&D_807FBB40->unkE6, G21_PLAYER->unkA, (s16)(s32)(var_fv0 * var_fv1));
    }
}

void func_806E0654(void) {
    func_806E007C();
    func_806DF494(&D_807FBB40->unkE6, G21_ACTOR_EE->unkEA, G21_PLAYER->unk48);
}

void func_806E0694(void) {
    func_806E007C();
    func_806DF494(&D_807FBB40->unkE6, G21_PLAYER->unkA, G21_PLAYER->unk48);
    G21_PLAYER->unk4 = 0.0f;
}

void func_806E06E8(void) {
    s16 var_a1;

    if (G21_ACTOR_EE->unkDA < 0x3C7) {
        var_a1 = G21_ACTOR_EE->unkD8 + 0x800;
    } else {
        var_a1 = G21_ACTOR_EE->unkEE + 0x800;
    }
    func_806DF494(&D_807FBB40->unkE6, var_a1, G21_PLAYER->unk48 / 4);
    G21_PLAYER->unk4 = 0.0f;
}

void func_806E077C(void) {
    s16 var_a1;

    if (G21_ACTOR_EE->unkDA < 0x3C7) {
        var_a1 = G21_ACTOR_EE->unkD8;
    } else {
        var_a1 = G21_ACTOR_EE->unkEE;
    }
    func_806DF494(&D_807FBB40->unkE6, var_a1, G21_PLAYER->unk48 / 4);
    G21_PLAYER->unk4 = 0.0f;
}

typedef struct G29StickX {
    s8 unk0;
    u8 pad1[0x33];
} G29StickX;

extern G29StickX D_807FD63E[];
extern s8 D_807FD63F;

typedef struct G22Main {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ s16 unkA;
    /* 0x00C */ u8 pad0C[0x2C];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[0xC];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0x152];
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ s16 unk1A0;
} G22Main;

typedef struct G22Sub4b {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} G22Sub4b;

typedef struct G22Sub4 {
    /* 0x00 */ G22Sub4b *unk0;
    /* 0x04 */ u8 pad4[0x60];
    /* 0x64 */ u16 unk64;
} G22Sub4;

typedef struct G22Act {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G22Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0x5C];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[0x2A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G22Act;

#define G22_M ((G22Main *)D_807FD580)
#define G22_A ((G22Act *)D_807FBB40)

extern f32 D_80753BA4[];
extern f32 D_80753BC0[];
extern f32 D_80753BDC[];
extern f32 D_80753BF8[];
extern f32 D_80753DC8[];
extern f32 D_80753DE4[];
extern u16 *D_807FBB54;
void func_80614EBC(void *, s32);
void func_80614D00(void *, f32, f32);
void func_8072FE60(f32);
s16 func_806CC14C(s16, s16);
void func_806E1630(void);

extern u8 D_8074E77C[];

void func_806E07F8(void) {
    f32 var_fv0;
    s16 temp_a1;
    s32 temp_v0;
    G21Table *temp_v1;

    func_806E007C();
    temp_a1 = G22_A->unkEE;
    temp_v0 = G22_A->unkE6 - temp_a1;
    if (temp_v0 > 0) {
        var_fv0 = (f32)temp_v0;
    } else {
        var_fv0 = (f32)-temp_v0;
    }
    if (var_fv0 > 2048.0f) {
        var_fv0 = 4096.0f - var_fv0;
    }
    if (var_fv0 > 400.0f) {
        var_fv0 = 400.0f;
    }
    var_fv0 = (f32)((f64)var_fv0 * (0.25 + 0.75 * (G22_A->unkB8 / G22_M->unk38)));
    if (var_fv0 > 1.0f) {
    }
    func_806DF494(&G22_A->unkE6, temp_a1, G22_M->unk48 / 4);
    if (G22_A->unk154 != 0x14) {
        if (G22_A->unk154 == 0xF && (G22_A->unk4->unk0->unk10 == 0x1F2 || G22_A->unk4->unk0->unk10 == 0x1B3)) {
            temp_v1 = &D_807FD610[D_807FC929];
            if (temp_v1->unk2E < -0x1E) {
                func_80614E78(D_807FBB40, 0x61);
                G22_A->unk154 = 0x10;
                G22_A->unk155 = 0;
            } else if (temp_v1->unk2E >= 0x1F) {
                func_80614E78(D_807FBB40, 0x5F);
                G22_A->unk154 = 0x11;
                G22_A->unk155 = 0;
            } else {
                if (temp_v1->unk2F >= 0x1F) {
                    func_80614E78(D_807FBB40, 0x63);
                    G22_A->unk154 = 0x12;
                    G22_A->unk155 = 0;
                } else if (temp_v1->unk2F < -0x1E) {
                    func_80614E78(D_807FBB40, 0x65);
                    G22_A->unk154 = 0x13;
                    G22_A->unk155 = 0;
                }
            }
        }
        temp_v1 = &D_807FD610[D_807FC929];
        if ((temp_v1->unk2E < 0x1E && G22_A->unk154 == 0x11) || (temp_v1->unk2F >= -0x1D && G22_A->unk154 == 0x13) || (temp_v1->unk2F < 0x1E && G22_A->unk154 == 0x12) || (temp_v1->unk2E >= -0x1D && G22_A->unk154 == 0x10)) {
            if (D_8074E77C[D_807FC929] == 2 && G22_A->unk154 != 0x12) {
                func_80614EBC(D_807FBB40, 0x191);
            } else if (G22_A->unk155 == 1) {
                switch (G22_A->unk154) {
                    case 0x11:
                        func_80614E78(D_807FBB40, 0x60);
                        break;
                    case 0x10:
                        func_80614E78(D_807FBB40, 0x62);
                        break;
                    case 0x12:
                        func_80614E78(D_807FBB40, 0x64);
                        break;
                    case 0x13:
                        func_80614E78(D_807FBB40, 0x66);
                        break;
                }
            } else {
                func_80614E78(D_807FBB40, 0x68);
            }
            G22_A->unk154 = 0xF;
            G22_A->unk155 = 0;
        }
    }
}

void func_806E0BEC(void) {
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_v0;

    func_806E007C();
    if (G22_M->unk4 != 0.0f) {
        var_fv1 = *(f32 *)(D_807FD618 + D_807FC929 * 0x34);
        var_fv1 = var_fv1 * var_fv1;
        if ((f64)var_fv1 < 0.2) {
            var_fv1 = 0.2f;
        }
        temp_v0 = D_807FBB40->unkE6 - G22_M->unkA;
        if (temp_v0 > 0) {
            var_fv0 = (f32)temp_v0;
        } else {
            var_fv0 = (f32)-temp_v0;
        }
        if (var_fv0 > 2048.0f) {
            var_fv0 = 4096.0f - var_fv0;
        }
        if (var_fv0 > 400.0f) {
            var_fv0 = 400.0f;
        }
        var_fv0 = var_fv0 * ((f64)G22_M->unk48 / 400.0);
        func_806DF494(&D_807FBB40->unkE6, G22_M->unkA, (s16)(s32)(var_fv0 * var_fv1));
    }
}

#ifdef NON_MATCHING
void func_806E0D40(void) {
    f32 var_fv0;
    s16 temp_v1;
    s16 var_v1;
    s32 temp_a0;
    G21Table *pad;

    func_806E007C();
    if (G22_M->unk4 != 0.0f) {
        pad = &D_807FD610[D_807FC929];
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
        temp_v1 = D_807FBB40->unkE6;
        temp_a0 = temp_v1 - G22_M->unkA;
        if (temp_a0 > 0) {
            var_fv0 = (f32)temp_a0;
        } else {
            var_fv0 = (f32)-temp_a0;
        }
        if (var_fv0 > 2048.0f) {
            var_fv0 = 4096.0f - var_fv0;
        }
        if (var_fv0 > 400.0f) {
            var_fv0 = 400.0f;
            if (temp_a0 && temp_a0) {
            }
        }
        if (var_fv0 > 1.0f) {
        }
        var_fv0 = (f32)((pad->unk2E * G22_M->unk48) / 400);
        D_807FBB40->unkE6 = (s16)(s32)((f32)temp_v1 - var_fv0);
        if (D_807FBB40->unkE6 >= 0x1000) {
            if (!D_807FBB40 && !D_807FBB40 && !D_807FBB40) {
            }
            D_807FBB40->unkE6 -= 0x1000;
        }
        if (D_807FBB40->unkE6 < 0) {
            D_807FBB40->unkE6 += 0x1000;
        }
    }
    pad = &D_807FD610[D_807FC929];
    if (!(pad->unk2A & 0x2000)) {
        G22_M->unk1A0 = (u32)((f64)(pad->unk2F * 0xCC) * 0.6 + 63000.0);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E0D40.s")
#endif

void func_806E0FAC(void) {
    f32 var_fv0;
    f32 var_fv1;
    s16 temp_a1;
    u16 temp_a1_2;

    func_806E007C();
    if (G22_M->unk4 != 0.0f && !G22_A->unkB8) {
        var_fv1 = *(f32 *)(D_807FD618 + D_807FC929 * 0x34);
        var_fv1 = var_fv1 * var_fv1;
        if ((f64)var_fv1 < 0.2) {
            var_fv1 = 0.2f;
        }
        temp_a1 = G22_M->unkA;
        var_fv0 = (f32)(G22_A->unkE6 - temp_a1);
        if (var_fv0 >= 2048.0f) {
            var_fv0 -= 4096.0f;
        }
        if (var_fv0 <= -2048.0f) {
            var_fv0 += 4096.0f;
        }
        if (var_fv0 > 400.0f) {
            var_fv0 = 400.0f;
        }
        if (var_fv0 < -400.0f) {
            var_fv0 = -400.0f;
        }
        var_fv0 = (f32)((f64)var_fv0 * ((f64)G22_M->unk48 / 400.0));
        var_fv0 = var_fv0 * var_fv1;
        if (var_fv0 > 0.0f) {
            var_fv1 = var_fv0;
        } else {
            var_fv1 = -var_fv0;
        }
        func_806DF494(&G22_A->unkE6, temp_a1, (s16)(s32)var_fv1);
        if (var_fv0 != 0.0f) {
            if (G22_A->unk154 != 0x3C) {
                if (G22_A->unk154 == 0x62) {
                    temp_a1_2 = D_807FBB54[G22_A->unk58 + 0x23C];
                    if (G22_A->unk4->unk64 != temp_a1_2) {
                        func_80614EBC(D_807FBB40, temp_a1_2);
                    }
                    func_80614D00(D_807FBB40, (f32)((f64)var_fv0 / 80.0), 0.0f);
                }
            } else {
                temp_a1_2 = D_807FBB54[G22_A->unk58 + 0x52];
                if (G22_A->unk4->unk64 != temp_a1_2) {
                    func_80614EBC(D_807FBB40, temp_a1_2);
                }
                func_80614D00(D_807FBB40, (f32)((f64)var_fv0 / 80.0), 0.0f);
            }
        }
    } else {
        if (G22_A->unk154 != 0x3C) {
            if (G22_A->unk154 == 0x62) {
                temp_a1_2 = D_807FBB54[G22_A->unk58 + 0x243];
                if (G22_A->unk4->unk64 != temp_a1_2) {
                    func_80614EBC(D_807FBB40, temp_a1_2);
                }
            }
        } else if (G22_A->unk155 == 1) {
            temp_a1_2 = D_807FBB54[G22_A->unk58 + 0x4B];
            if (G22_A->unk4->unk64 != temp_a1_2) {
                func_80614EBC(D_807FBB40, temp_a1_2);
            }
        }
    }
    G22_M->unk4 = 0.0f;
}

void func_806E1334(void) {
    if (((s8 *)&D_807FD63F)[D_807FC929 * 0x34] < 0) {
        G22_M->unk4 = func_806E0454(D_80753BDC[D_807FD584], D_80753BF8[D_807FD584]);
    } else {
        G22_M->unk4 = func_806E0454(D_80753BA4[D_807FD584], D_80753BC0[D_807FD584]);
    }
    if (G22_M->unk4 != 0.0f) {
        G22_M->unk8 = G22_M->unk4 > 0.0f ? 1 : -1;
    } else {
        G22_M->unk8 = 0;
    }
    func_8072FE60(((s8 *)&D_807FD63F)[D_807FC929 * 0x34] / 80.0);
    D_807FBB40->unkE6 += D_807FD63E[D_807FC929].unk0;
    D_807FBB40->unkE6 &= 0xFFF;
    func_806E1630();
}

void func_806E14DC(void) {
    if (((s8 *)&D_807FD63F)[D_807FC929 * 0x34] < 0) {
        G22_M->unk4 = func_806E0454(D_80753BDC[D_807FD584], D_80753BF8[D_807FD584]);
    } else {
        G22_M->unk4 = func_806E0454(D_80753BA4[D_807FD584], D_80753BC0[D_807FD584]);
    }
    if (G22_M->unk4 != 0.0f) {
        G22_M->unk8 = G22_M->unk4 > 0.0f ? 1 : -1;
    } else {
        G22_M->unk8 = 0;
    }
    func_8072FE60(((s8 *)&D_807FD63F)[D_807FC929 * 0x34] / 80.0);
}

void func_806E1630(void) {
    s16 lo;
    s16 sp1C;
    s16 hi;
    s16 cur;
    s32 outside = 0;

    hi = G22_M->unk19E;
    lo = G22_M->unk19C;
    if (lo < hi) {
        cur = D_807FBB40->unkE6;
        if (cur < lo || hi < cur) {
            outside = 1;
        }
    } else {
        cur = D_807FBB40->unkE6;
        if (hi < cur && cur < lo) {
            outside = 1;
        }
    }
    if (outside) {
        sp1C = func_806CC14C(cur, lo);
        if (sp1C < func_806CC14C(D_807FBB40->unkE6, G22_M->unk19E)) {
            D_807FBB40->unkE6 = G22_M->unk19C;
        } else {
            D_807FBB40->unkE6 = G22_M->unk19E;
        }
    }
}

void func_806E1728(void) {
    f32 v = func_806E03C8(D_80753DC8[D_807FD584], D_80753DE4[D_807FD584]);

    if (D_807FD63E[D_807FC929].unk0 < 0) {
        G22_M->unk4 = -v;
        G22_M->unk8 = -1;
    } else {
        G22_M->unk4 = v;
        if (v != 0.0f) {
            G22_M->unk8 = 1;
        } else {
            G22_M->unk8 = 0;
        }
    }
}

void func_806E17F4(void) {
    func_806E007C();
    func_806DF494(&G21_ACTOR_EE->unkEE, G22_M->unkA, G22_M->unk48);
    func_806DF494(&D_807FBB40->unkE6, G21_ACTOR_EE->unkEE, G22_M->unk48);
    func_806DFFDC(D_807FBB40->unkE6);
}

void func_806E1864(void) {
}

typedef struct G23Actor {
    /* 0x000 */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x4C];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[8];
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x14];
    /* 0x0DC */ s16 unkDC;
    /* 0x0DE */ u8 padDE[2];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ u8 padE6[2];
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x154 - 0xF0];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G23Actor;

typedef struct G23Player {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[8];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 pad42[0xE];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[2];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x8D - 0x5C];
    /* 0x8D */ u8 unk8D;
    /* 0x8E */ u8 pad8E[0xC8 - 0x8E];
    /* 0xC8 */ s16 unkC8;
} G23Player;

#define G23_A ((G23Actor *)D_807FBB40)
#define G23_P ((G23Player *)D_807FD580)

extern u32 D_80767CC0;
extern f32 D_807531FC[];
extern f32 D_80753250[];
extern f32 D_807535CC[];

void func_806E186C(void) {
    if (D_807FD610[D_807FC929].unk2C & 0x8000) {
        G23_P->unk58 = D_80767CC0;
    }
    G23_A->unkE8 = 0;
    G23_A->unkE4 = 0;
    if ((D_80767CC0 - G23_P->unk58 < 0xF) && (G23_P->unkC8 == -1)) {
        if (G23_A->unkE0 != 0.0f) {
            G23_A->unkEE = G23_A->unkDC;
            G23_A->unkB8 = 200.0f;
            G23_P->unk3E = 0x1E;
            G23_P->unk40 = G23_A->unkDC;
            G23_P->unk54 = D_807535CC[D_807FD584] * 0.5;
        } else {
            G23_P->unk3C = 0;
            G23_P->unk54 = D_807535CC[D_807FD584];
        }
        G23_P->unk38 = D_807531FC[D_807FD584];
        G23_P->unk30 = D_80753250[D_807FD584];
        G23_A->unk154 = 0x17;
        G23_A->unk155 = 0;
        G23_P->unk50 = 0;
        func_80614E78(D_807FBB40, 0x10);
        G23_P->unk58 = D_80767CC0 - 0x1E;
    }
}

void func_806E1A50(void) {
    if (D_807FD610[D_807FC929].unk2C & 0x8000) {
        G23_P->unk58 = D_80767CC0;
    }
    if ((D_80767CC0 - G23_P->unk58 < 0xF) && (!(G23_A->unk6A & 1) || (G23_A->unkE0 == 0.0f))) {
        G23_P->unk38 = D_807531FC[D_807FD584];
        G23_P->unk30 = D_80753250[D_807FD584];
        G23_A->unk154 = 0x17;
        G23_A->unk155 = 0;
        G23_P->unk54 = D_807535CC[D_807FD584];
        G23_P->unk50 = 0;
        func_80614EBC(D_807FBB40, 0xB0);
        G23_P->unk58 = D_80767CC0 - 0x1E;
    }
}

void func_806E1BA4(void) {
    f32 temp_fv0;
    f32 temp_fv1;

    if (D_807FD610[D_807FC929].unk2C & 0x8000) {
        G23_P->unk58 = D_80767CC0;
    }
    if ((D_80767CC0 - G23_P->unk58 < 0xF) && (!(G23_A->unk6A & 1) || (G23_A->unkE0 == 0.0f))) {
        G23_P->unk38 = D_807531FC[D_807FD584];
        if (G23_P->unk38 > (temp_fv0 = G23_A->unkB8)) {
            G23_A->unkB8 = temp_fv0;
        } else {
            G23_A->unkB8 = G23_P->unk38;
        }
        G23_P->unk30 = D_80753250[D_807FD584];
        G23_P->unk2C = 20.0f;
        G23_A->unk154 = 0x17;
        G23_A->unk155 = 0;
        G23_P->unk54 = D_807535CC[D_807FD584];
        G23_P->unk50 = 0;
        func_80614E78(D_807FBB40, 0x10);
        G23_P->unk58 = D_80767CC0 - 0x1E;
        if (!G23_P->unk38) {
        }
    }
}

void func_806E1D38(void) {
    if (D_807FD610[D_807FC929].unk2C & 0x8000) {
        G23_P->unk58 = D_80767CC0;
    }
    if ((D_80767CC0 - G23_P->unk58 < 0xF) && (!(G23_A->unk6A & 1) || (G23_A->unkE0 == 0.0f))) {
        G23_A->unk154 = 0x17;
        G23_A->unk155 = 0;
        G23_P->unk54 = D_807535CC[D_807FD584];
        G23_P->unk50 = 0;
        func_80614EBC(D_807FBB40, 0xAF);
        G23_P->unk58 = D_80767CC0 - 0x1E;
    }
}

void func_806CFE7C();

void func_806E1E54(void) {
    if (D_807FD610[D_807FC929].unk2C & 0x8000) {
        G23_P->unk58 = D_80767CC0;
    }
    if (D_80767CC0 - G23_P->unk58 < 0xF) {
        if (G23_A->unkC4 == -260.0f) {
            G23_A->unkC4 = -31.0f;
        } else {
            func_806CFE7C();
        }
        G23_A->unk154 = 0x14;
        G23_A->unk155 = 0;
        G23_P->unk54 = D_807535CC[D_807FD584];
        G23_P->unk50 = 0;
        func_80614E78(D_807FBB40, 0x67);
        G23_P->unk58 = D_80767CC0 - 0x1E;
    }
}

void func_806E1F8C(void) {
    if (D_807FD610[D_807FC929].unk2C & 0x8000) {
        G23_P->unk58 = D_80767CC0;
    }
    if ((D_80767CC0 - G23_P->unk58 < 0xF) && (G23_P->unk8D == 0)) {
        G23_A->unk154 = 0x41;
        G23_A->unk155 = 0;
        G23_P->unk54 = D_807535CC[D_807FD584];
        G23_P->unk50 = 0;
        func_80614EBC(D_807FBB40, 0x156);
        G23_P->unk58 = D_80767CC0 - 0x1E;
    }
}

extern s32 D_8076A0A8;
extern u8 D_807FCA6A[];
void func_806EB0C0(s32, s32, u8);

void func_806E208C(void) {
    if ((D_807FD610[D_807FC929].unk2C & 0x8000) && (D_807FCA6A[D_807FC929 * 0x306] >= 2) && (D_8076A0A8 != 0xE)) {
        func_806EB0C0(9, 0, D_807FC929);
        G23_P->unk58 = D_80767CC0 - 0x1E;
    }
}

void func_806E2140(void) {
    if (D_807FD610[D_807FC929].unk2C & 0x8000) {
        G23_P->unk58 = D_80767CC0;
    }
    if ((D_80767CC0 - G23_P->unk58 < 0xF) && (!(G23_A->unk6A & 1) || (G23_A->unkE0 == 0.0f))) {
        G23_A->unk154 = 0x61;
        G23_A->unk155 = 0;
        G23_P->unk54 = D_807535CC[D_807FD584];
        G23_P->unk50 = 0;
        func_80614E78(D_807FBB40, 0x50);
        G23_P->unk58 = D_80767CC0 - 0x1E;
    }
}

f32 func_80611BB4(f32, f32);
f32 sqrtf(f32);
extern struct G31Cam *D_807FC924;

typedef struct LE40BPlayer {
    /* 0x000 */ u8 pad0[0x8E];
    /* 0x08E */ u8 unk8E;
    /* 0x08F */ u8 unk8F;
    /* 0x090 */ u8 unk90;
    /* 0x091 */ u8 unk91;
    /* 0x092 */ u8 pad92[0x104 - 0x92];
    /* 0x104 */ s32 unk104;
    /* 0x108 */ u8 pad108[0x1A4 - 0x108];
    /* 0x1A4 */ u8 unk1A4;
} LE40BPlayer;

#define LE40B_S ((LE40BPlayer *)D_807FD580)
#define LE40B_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))

extern u8 D_8071FBC8;
extern u8 D_807200D4;
extern f32 D_80753E2C[];
extern u8 *D_807FD568;
void func_8071A8B0(void);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void projectileGetTargetCoords(void *, s32);
void projectileSetSpawnFlag(void);
void projectileSetTargetCoords(f32, f32, f32);
void projectileSpawnNodeEntry(s32, s32, f32, s16, f32, f32, void *);
void func_8060E7EC(u8, u8, s32);
void func_8061F0B0(s32, s32, s32);
s32 func_80672630(void *, s32, s32);
void func_80714950(s32);
s32 func_80714C08(void *, f32, Actor *, s32, s32);
f32 func_80612D10(f32);
f32 func_80612D1C(f32);
u8 func_806E2B20(void *);
void func_806E2C74(Actor *);
s32 actorIsActiveType2B(Actor *);
s32 func_80609140(s32, s32, f32, f32, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
extern s16 D_80753E64[];
s32 func_80714608(s32);
s32 func_8067ACDC(void *, s32, s32);
void func_806F0C18(void *);
void func_806CFF9C(Actor *);
void func_806F91B4(s32, s32, s32);
void func_807149B8(s32);
void func_8071498C(void *);

typedef struct LE40BObj {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
} LE40BObj;

#define LE40B_OBJ ((LE40BObj *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0))

void func_806E225C(arg0, arg1)
u8 arg0;
u8 arg1;
{
    s16 spawnId;
    f32 scale;
    u16 sfx;
    u8 vol;
    f32 dz;
    f32 dx;
    f32 ang2;
    f32 sp54;
    f32 sp50;
    s32 flags;
    s32 sel;
    s16 ang;
    s32 hasFlag;

    if ((LE40B_PAD(D_807FD63C, u16) & 0x4000) || arg1) {
        flags = D_807FD568[2];
        if ((flags & 2) && func_806F8AD4(3, D_807FC929)) {
            sel = 3;
        } else {
            flags &= ~2;
            sel = 2;
        }
        if (!arg0) {
            flags &= ~4;
        }
        func_806F8BC4(sel, 0, 0);
        if (func_806F8AD4((u8)sel, D_807FC929)) {
            if (func_8067ACDC(D_807FBB40, 4, (s32)actorIsActiveType2B) < D_80753E64[D_807FD584]) {
                hasFlag = flags & 2;
                func_806F91B4(sel, D_807FC929, -1);
                if (!arg0) {
                    s32 v = LE40B_S->unk8F + 1;
                    if (v >= 0x15) {
                        LE40B_S->unk8F = 0x14;
                    } else {
                        LE40B_S->unk8F = v;
                    }
                }
                func_8060E7EC(LE40B_S->unk1A4, 0xFF, 3);
                switch (D_807FBB40->unk58) {
                    case 7:
                        spawnId = 0xAB;
                        scale = 0.5f;
                        LE40B_S->unk8E = 0x1A;
                        sfx = 0x2A5;
                        vol = 5;
                        if (!arg0) {
                            func_8061F0B0(LE40B_S->unk104, 7, 7);
                        }
                        break;
                    case 6:
                        spawnId = 0x26;
                        scale = 0.5f;
                        LE40B_S->unk8E = 0x1A;
                        sfx = 0x2A5;
                        vol = 5;
                        if (!arg0) {
                            func_8061F0B0(LE40B_S->unk104, 7, 7);
                        }
                        break;
                    case 4:
                        sfx = 0x77;
                        vol = 2;
                        spawnId = 0x2A;
                        scale = 0.5f;
                        break;
                    case 5:
                        spawnId = 0x2B;
                        scale = 0.36f;
                        sfx = 0xEF;
                        vol = 0;
                        LE40B_S->unk8E = 4;
                        break;
                    case 2:
                        spawnId = 0x30;
                        scale = 0.3f;
                        sfx = 0x7B;
                        vol = 5;
                        LE40B_S->unk8E = 0x1A;
                        break;
                    default:
                        spawnId = 0x24;
                        scale = 0.3f;
                        sfx = 0x7A;
                        vol = 5;
                        LE40B_S->unk8E = 0x1A;
                        break;
                }
                if (arg0) {
                    func_80609140((s16)sfx, 0x7FFF, 63.0f, 1.0f, vol, 0);
                } else {
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, (s16)sfx, 0xFF, 0x7F, vol);
                }
                if (hasFlag != 0) {
                    if (arg0) {
                        func_80609140(0x1EE, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                    } else {
                        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1EE, 0xFF, 0x7F, 0xA);
                    }
                }
                LE40B_S->unk91 = LE40B_S->unk90;
                if (arg0) {
                    ang = mathAngleBetweenPoints2D(LE40B_OBJ->unk228, LE40B_OBJ->unk230, LE40B_OBJ->unk210, LE40B_OBJ->unk218);
                } else {
                    ang = D_807FBB40->unkE6;
                }
                if (D_807FBB40->unk58 == 4) {
                    if ((!arg0 && func_806E2B20(D_807FBB40)) || func_80672630(D_807FBB40, ang, 0) == 0) {
                        projectileSetSpawnFlag();
                    }
                } else if (func_80672630(D_807FBB40, ang, 0) == 0) {
                    projectileSetSpawnFlag();
                }
                if (arg0) {
                    ang2 = LE40B_OBJ->unk218;
                    projectileSetTargetCoords(LE40B_OBJ->unk210, LE40B_OBJ->unk214, ang2);
                    dz = LE40B_OBJ->unk230 - LE40B_OBJ->unk218;
                    dx = LE40B_OBJ->unk228 - LE40B_OBJ->unk210;
                    ang2 = func_80611BB4(LE40B_OBJ->unk22C - LE40B_OBJ->unk214, sqrtf(dz * dz + dx * dx));
                    sp50 = D_80753E2C[D_807FD584] * func_80612D1C(ang2);
                    sp54 = D_80753E2C[D_807FD584] * func_80612D10(ang2);
                    projectileSpawnNodeEntry(spawnId, (s16)flags, scale,
                                             mathAngleBetweenPoints2D(LE40B_OBJ->unk228, LE40B_OBJ->unk230, LE40B_OBJ->unk210, LE40B_OBJ->unk218),
                                             sp54, sp50, D_807FBB48);
                } else {
                    if ((D_807FBB40->unk58 == 2 || D_807FBB40->unk58 == 3 || D_807FBB40->unk58 == 6 || D_807FBB40->unk58 == 7)) {
                        func_807149B8(1);
                        func_80714950(0x50);
                        func_8071498C(func_8071A8B0);
                        func_80714C08(&D_807200D4, 0.5f, D_807FBB48, LE40B_S->unk90 + 9, 2);
                        if (D_807FBB40->unk58 == 6 || D_807FBB40->unk58 == 7) {
                            func_807149B8(1);
                            func_80714950(0x50);
                            func_8071498C(func_8071A8B0);
                            func_80714C08(&D_8071FBC8, 0.5f, D_807FBB48, 9, 2);
                        }
                    }
                    projectileGetTargetCoords(D_807FBB48, LE40B_S->unk90 + 9);
                    projectileSpawnNodeEntry(spawnId, (s16)flags, scale, D_807FBB48->unkE6, D_80753E2C[D_807FD584], 0.0f, D_807FBB48);
                }
                if ((func_80714608(0) != 0) && (func_806F8AD4((u8)sel, D_807FC929) == 0)) {
                    func_806F0C18(D_807FBB40);
                    func_806CFF9C(D_807FBB40);
                }
                func_806E2C74(D_807FBB40);
            }
        } else {
            switch (D_807FBB40->unk58) {
                case 6:
                case 7:
                    sfx = 0x190;
                    vol = 5;
                    break;
                case 4:
                    sfx = 0x77;
                    vol = 2;
                    break;
                case 5:
                    sfx = 0x7C;
                    vol = 0;
                    break;
                case 2:
                    sfx = 0xB0;
                    vol = 0xA;
                    LE40B_S->unk8E = 0x1A;
                    break;
                default:
                    sfx = 0x83;
                    vol = 5;
                    break;
            }
            if (arg0) {
                func_80609140((s16)sfx, 0x7FFF, 63.0f, 1.0f, vol, 0);
                return;
            }
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, (s16)sfx, 0xFF, 0x7F, vol);
        }
    }
}

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
s32 func_80671E00(f32, f32, f32, f32, void *, void *, s32, s32);

u8 func_806E2B20(void *arg0) {
    f32 temp3;
    f32 temp2;
    f32 temp1;
    f32 var_fs1;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    s16 sp66;
    s16 sp64;
    u8 sp63;

    sp63 = 0;
    var_fs1 = 0.0f;
    actorGetNodePos(arg0, 4, &sp78, &sp70, &sp68);
    actorGetNodePos(arg0, 0xA, &sp7C, &sp74, &sp6C);
    for (; var_fs1 <= 1.0 && sp63 == 0; var_fs1 += 0.2) {
        do {
            temp3 = sp68;
        } while (0);
        sp63 = func_80671E00(((sp7C - sp78) * var_fs1) + sp78, ((sp74 - sp70) * var_fs1) + sp70, temp3 = ((sp6C - sp68) * var_fs1) + temp3, 10.0f, &sp66, &sp64, 0, 0);
    }
    return sp63;
}

typedef struct G23State90 {
    /* 0x00 */ u8 pad0[0x90];
    /* 0x90 */ u8 unk90;
} G23State90;

void func_806E2C74(Actor *arg0) {
    G23State90 *state = arg0->unk174;

    switch (arg0->unk58) {
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
        state->unk90 = 1;
        return;
    default:
        state->unk90 = 1 - state->unk90;
        return;
    }
}

extern s32 D_807FBB64;
s32 func_8073110C(s32, s32);
s32 func_807142D8(void);
s32 func_8071441C(void);

s32 func_806E2CC4(void) {
    s32 var_v1;

    var_v1 = func_80714608(0) == 0;
    if (var_v1 != 0) {
        var_v1 = (D_807FBB64 & 0x200) == 0;
        if (var_v1 != 0) {
            var_v1 = func_806F8AD4(4, D_807FC929) != 0;
            if (var_v1 != 0) {
                var_v1 = D_8074E77C[D_807FC929] < 6;
                if (var_v1 != 0) {
                    var_v1 = func_8067ACDC(D_807FBB40, 4, 0) < D_80753E64[D_807FD584];
                    if (var_v1 != 0) {
                        var_v1 = func_8073110C(0x184, 0) != 0;
                        if (var_v1 == 0) {
                            var_v1 = (D_807FBB64 & 0x10000000) != 0;
                            if (var_v1 == 0) {
                                var_v1 = D_807FC928;
                                var_v1 = var_v1 >= 2;
                                if (var_v1 == 0) {
                                    var_v1 = func_807142D8() != 0;
                                    if (var_v1 == 0) {
                                        var_v1 = func_8071441C() != 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return var_v1 & 0xFF;
}

void func_806E2DE8(void) {
    if ((D_807FD610[D_807FC929].unk2C & 1) && func_806E2CC4()) {
        func_80614E78(D_807FBB40, 0x47);
        D_807FBB40->unk154 = 0x2C;
        D_807FBB40->unk155[0] = 0;
    }
}

void func_806E225C();

void func_806E2E6C(void) {
    if (D_807FD568[2] & 1) {
        func_806E225C(0, 0);
    }
}

void func_806E2EA8(void) {
    func_806E225C(1, 0);
}

void func_806E2ECC(void) {
    if ((D_807FD610[D_807FC929].unk2C & 0xC000) == 0x4000) {
        func_80614E78(D_807FBB40, 0x54);
        return;
    }
    func_806E225C(0, 0);
}

extern s16 D_80753354[];
s32 func_806E56EC();

void func_806E2F3C(void) {
    s32 var_v1;

    var_v1 = 1;
    if (D_807FC928 >= 2) {
        var_v1 = func_806E56EC() == 0;
    }
    if (var_v1 && (D_807FBB40->unk154 != 0x62) && (D_807FBB40->unk6A & 1)) {
        G21_PLAYER->unk48 = D_80753354[D_807FD584];
        D_807FBB40->unk154 = 0x62;
        D_807FBB40->unk155[0] = 0;
        func_80614E78(D_807FBB40, 0x52);
    }
}


void func_806E2FE8(void) {
    if (!(D_807FD610[D_807FC929].unk2C & 0x2000)) {
        func_806CFF9C(D_807FBB40);
    }
}

extern f32 D_8075371C[];
extern f32 D_8075378C[];

void func_806E3040(void) {
    if (D_807FD610[D_807FC929].unk2C & 0x8000) {
        G23_P->unk58 = D_80767CC0;
    }
    if ((D_80767CC0 - G23_P->unk58 < 0xF) && (D_8074E77C[D_807FC929] != 6) &&
        (!(G23_A->unk6A & 1) || (G23_A->unkE0 == 0.0f))) {
        if (G23_P->unk20 > 70.0f) {
            G23_A->unk154 = 0x1D;
            G23_A->unk155 = 0;
            G23_P->unk54 = D_8075378C[D_807FD584];
            G23_P->unk50 = 0;
            func_80614E78(D_807FBB40, 0x1A);
            if (!D_807FBB40) {
            }
            G23_P->unk58 = D_80767CC0 - 0x1E;
            return;
        }
        G23_A->unk154 = 0x3E;
        G23_A->unk155 = 0;
        G23_P->unk54 = D_8075371C[D_807FD584];
        G23_P->unk50 = 0;
        func_80614E78(D_807FBB40, 0xE);
        G23_P->unk58 = D_80767CC0 - 0x1E;
    }
}

typedef struct G24Sub {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ u32 unk58;
} G24Sub;

typedef struct G24Main {
    /* 0x000 */ u8 pad0[0x2C];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[4];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[2];
    /* 0x03E */ s16 unk3E;
    /* 0x040 */ u8 pad40[0x10];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[2];
    /* 0x054 */ f32 unk54;
    /* 0x058 */ u32 unk58;
    /* 0x05C */ u8 pad5C[0xA4];
    /* 0x100 */ s32 unk100;
    /* 0x104 */ u8 pad104[0x9C];
    /* 0x1A0 */ u16 unk1A0;
    /* 0x1A2 */ u8 unk1A2;
    /* 0x1A3 */ u8 unk1A3;
    /* 0x1A4 */ u8 pad1A4[8];
    /* 0x1AC */ G24Sub *unk1AC;
} G24Main;

typedef struct G24Act {
    /* 0x000 */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[2];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0x48];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x18];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G24Act;

#define G24_M ((G24Main *)D_807FD580)
#define G24_A ((G24Act *)D_807FBB40)
#define G24_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))


void func_806E31FC(void) {
    if (G24_PAD(D_807FD63C, u16) & 0x8000) {
        G24_M->unk58 = D_80767CC0;
    }
    if (((D_80767CC0 - G24_M->unk58) < 0xF) && (G24_A->unk154 == 0x17) && (!(G24_A->unk6A & 1) || (G24_A->unkE0 == 0.0f))) {
        G24_A->unk154 = 0x17;
        G24_A->unk155 = 0;
        G24_M->unk54 = D_807535CC[D_807FD584];
        G24_M->unk50 = 0;
        func_80614E78(D_807FBB40, 0x10);
    }
}


void func_806E330C(void) {
    if (G24_PAD(D_807FD63C, u16) & 0x8000) {
        G24_M->unk58 = D_80767CC0;
    }
    if (((D_80767CC0 - G24_M->unk58) < 0xF) && (G24_A->unk154 == 0x61) && (!(G24_A->unk6A & 1) || (G24_A->unkE0 == 0.0f))) {
        G24_A->unk154 = 0x61;
        G24_A->unk155 = 0;
        G24_M->unk54 = D_807535CC[D_807FD584];
        G24_M->unk50 = 0;
        func_80614E78(D_807FBB40, 0x50);
    }
}


#define G24_SCHED280 (*(u32 *)(gScheduler + 0x280))

extern u8 gScheduler[];

void func_806E341C(void) {
    if (G24_PAD(D_807FD63C, u16) & 0x8000) {
        G24_M->unk58 = G24_SCHED280;
    }
    if ((G24_SCHED280 - G24_M->unk58) < 0xF) {
        G24_A->unk154 = 0x58;
        G24_A->unk155 = 0;
        G24_M->unk50 = 0;
        G24_M->unk3E = 0;
        G24_M->unk58 = G24_SCHED280 - 0x1E;
    }
}


void func_806E34D8(void) {
    if (G24_PAD(D_807FD63C, u16) & 0x10) {
        G21_ACTOR_EE->unkEE = (G21_ACTOR_EE->unkEE + 0x800) & 0xFFF;
    }
}


extern s16 D_80753C94[];
extern f32 D_80753D08[];

void func_806E352C(void) {
    G24_A->unk6A &= 0xFFBF;
    G24_M->unk100 = D_80753C94[D_807FD584];
    G24_A->unk154 = 0x17;
    G24_A->unk155 = 0;
    G24_A->unkB8 = 0.0f;
    G24_M->unk54 = D_80753D08[D_807FD584];
    G24_M->unk50 = 0;
    func_80614E78(D_807FBB40, 0x10);
}


void func_806E35D8(void) {
    if (G24_PAD(D_807FD63C, u16) & 0x8000) {
        G24_M->unk58 = D_80767CC0;
    }
    if ((D_80767CC0 - G24_M->unk58) < 0xF) {
        G24_A->unk154 = 0x5A;
        G24_A->unk155 = 0;
        G24_M->unk3E = 0;
        G24_M->unk50 = 0;
        func_80614E78(D_807FBB40, 0x74);
        G24_M->unk58 = D_80767CC0 - 0x1E;
    }
}


void func_806E36B4(void) {
    u32 sel;
    G24Act *p;

    do {
        if (!D_807FBB40 && !D_807FBB40) {}
    } while (0);
    if (G24_PAD(D_807FD63C, u16) & 0x8000) {
        G24_M->unk58 = D_80767CC0;
    }
    if ((D_80767CC0 - G24_M->unk58) < 0xF) {
        p = (G24Act *)D_807FBB40;
        p->unk154 = 0x4C;
        G24_A->unk155 = 0;
        G24_M->unk54 = D_807535CC[D_807FD584];
        G24_M->unk50 = 0;
        sel = G24_M->unk1AC->unk58;
        sel ^= 0;
        switch (sel) {
            case 0x3D:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x55:
            case 0x82:
                func_80614EBC(D_807FBB40, 0x1CB);
                break;
            default:
                func_80614E78(D_807FBB40, 0x30);
                break;
        }
        G24_M->unk58 = D_80767CC0 - 0x1E;
    }
}


void func_806CFEA4(void);

void func_806E380C(void) {
    func_806CFEA4();
}


void func_806CFE7C(void);

void func_806E382C(void) {
    func_806CFE7C();
}


extern f32 D_807536E4[];
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
f32 func_80612794(s16);
void func_806CD424(s16, f32, f32);

void func_806E384C(void) {
    f32 b;
    f32 c;
    f32 a;
    s32 t;

    a = G24_M->unk1A0 + 0x9E8;
    if (a >= 32768.0f) {
        a -= 65536.0f;
    }
    a /= 16;
    if (G24_A->unk6E == -1) {
        sfxPlayActorSound(D_807FBB40, 0x114, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    t = (s16)(s32)a;
    c = func_80612790(t);
    b = D_807536E4[D_807FD584];
    G24_A->unkC4 = D_807536E4[D_807FD584] + (-2.0f * b * c);
    if (G24_A->unkC0 < 0.0f) {
        G24_A->unkC4 = G24_A->unkC4 - G24_A->unkC0 / 100.0;
    }
    if (G24_A->unk6A & 1) {
        G24_M->unk30 = D_80753250[D_807FD584];
    } else {
        c = func_80612794(t) * 8.0f;
        if (c >= 0.0f) {
            a = G24_A->unkE6;
        } else {
            a = G24_A->unkE6 + 0x800;
            if (a > 4096.0f) {
                a -= 4096.0f;
            }
        }
        if (c > 0.0f) {
            G24_M->unk2C = c;
        } else {
            G24_M->unk2C = -c;
        }
        func_806CD424((s32)a, 900.0f, G24_M->unk38);
        a = G24_A->unkB8;
        G24_M->unk30 = (a * a) / 10000.0f + 1.0f;
    }
    G24_M->unk1A2 = 1;
}


void sfxStopSlotSound();
void func_806CD8EC(void);
extern struct G29BtnA D_807FD63A[];

void func_806E3B00(void) {
    f32 temp;

    if (!(G24_PAD(D_807FD63A, u16) & 0x2000)) {
        if (func_806F8AD4(5, D_807FC929) && G24_M->unk1A3) {
            func_806E384C();
        } else {
            sfxStopSlotSound(D_807FBB40, 0);
            G24_A->unkC4 = D_807536E4[D_807FD584];
            temp = G24_A->unkB8;
            G24_M->unk30 = (temp * temp) / 10000.0f + 1.0f;
        }
    } else {
        G24_A->unkC4 = D_807536E4[D_807FD584];
    }
    func_806CD8EC();
}


void func_806F142C(Actor *);

void func_806E3C14(void) {
    func_806F142C(D_807FBB40);
}


void func_806E3C38(void) {
    f32 temp;

    if (!(G24_PAD(D_807FD63A, u16) & 0x2000)) {
        sfxStopSlotSound(D_807FBB40, 0);
    }
    G24_A->unkC4 = D_807536E4[D_807FD584];
    temp = G24_A->unkB8;
    G24_M->unk30 = (temp * temp) / 10000.0f + 1.0f;
    func_806CD8EC();
}


void func_806E3CEC(void) {
    G24_M->unk30 = D_80753250[D_807FD584];
}


void func_806E3D14(f32 arg0) {
    G24Main *m;
    f32 f;
    u16 t;

    m = G24_M;
    t = m->unk1A0;
    if ((s32)t < 0x8000) {
        f = (s32)t + 0x10000;
    } else {
        f = (u32)t;
    }
    if (arg0 < f) {
        f -= 3000.0f;
        if (f < arg0) {
            f = arg0;
        }
    }
    if (f < arg0) {
        f += 3000.0f;
        if (arg0 < f) {
            f = arg0;
        }
    }
    m->unk1A0 = (u32)f;
}


#ifdef NON_MATCHING
extern u8 D_807FD6E0;
extern u8 D_807FD6E1;

void func_806E3E40(void) {
    f32 ang;
    f32 ground;
    f32 a;
    f32 arg;
    s16 t;

    if (func_806F8AD4(5, D_807FC929) && G24_M->unk1A3) {
        if (G24_PAD(D_807FD63C, u16) & 0x2000) {
            D_807FD6E0 = 0;
            D_807FD6E1 = 0;
        }
        ang = G24_A->unkEE - G24_A->unkE6;
        if (ang < 0.0f) {
            ang += 4096.0f;
        }
        t = (s32)ang;
        ground = func_80612794(t) * G24_A->unkB8;
        if (ground > 0.0f) {
            a = ground;
        } else {
            a = -ground;
        }
        if (a > 10.0f) {
            if (ang > 2048.0f) {
                arg = 1024.0f;
            } else {
                arg = 3072.0f;
            }
            arg += G24_A->unkE6;
            if (arg >= 4096.0f) {
                arg -= 4096.0f;
            }
            G24_M->unk2C = 8.0f;
            func_806CD424((s32)arg, 0.0f, G24_M->unk38);
        }
        ang = func_80612790(t) * G24_A->unkB8;
        ground = G24_A->unkC0;
        if (ground > 0.0f) {
            ground = 0.0f;
        }
        if (ang > 0.0f) {
            a = ang;
        } else {
            a = -ang;
        }
        if (a > 10.0f) {
            if (ground > 0.0f) {
                a = ground;
            } else {
                a = -ground;
            }
            arg = (f64)(func_80611BB4(a, ang) - 1.5707964f) * 16384.0 / 1.5707963705062866 + 63000.0;
        } else {
            arg = 63000.0f;
        }
        func_806E3D14(arg);
        if (ang > 0.0f) {
            a = ang;
        } else {
            a = -ang;
        }
        if (((a > 10.0f) || (G24_A->unkC0 < 0.0f)) && (D_807FD6E1 == 0)) {
            D_807FD6E0 = 4;
        }
        if (D_807FD6E0 != 0) {
            D_807FD6E0 -= 1;
            if (D_807FD6E0 == 0) {
                D_807FD6E1 = 8;
            }
            func_806E384C();
        } else {
            sfxStopSlotSound(D_807FBB40, 0);
        }
        if (D_807FD6E1 != 0) {
            D_807FD6E1 -= 1;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E3E40.s")
#endif


void func_806E41B4(void) {
    func_80614E78(D_807FBB40, 0x15);
    G24_A->unk155 = 7;
}

typedef struct G25State {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ u32 unk58;
    /* 0x5C */ u8 pad5C[0xFC - 0x5C];
    /* 0xFC */ u8 unkFC;
} G25State;

typedef struct G25Player {
    /* 0x000 */ u8 pad0[0x20];
    /* 0x020 */ f32 unk20;
    /* 0x024 */ u8 pad24[0xC];
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[4];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[0xC];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0x12];
    /* 0x05C */ u32 unk5C;
    /* 0x060 */ u32 unk60;
    /* 0x064 */ s16 unk64;
    /* 0x066 */ u8 pad66[2];
    /* 0x068 */ f32 unk68;
    /* 0x06C */ u8 pad6C[0x20];
    /* 0x08C */ u8 unk8C;
    /* 0x08D */ u8 pad8D[0xC8 - 0x8D];
    /* 0x0C8 */ s16 unkC8;
    /* 0x0CA */ u8 padCA[0x1AC - 0xCA];
    /* 0x1AC */ G25State *unk1AC;
    /* 0x1B0 */ u8 pad1B0[0x40];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x2C];
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 unk228;
} G25Player;

typedef struct G25Actor {
    /* 0x000 */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x24];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[4];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x1C];
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 padE4[2];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[2];
    /* 0x0EA */ s16 unkEA;
    /* 0x0EC */ u8 padEC[2];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x154 - 0xF0];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G25Actor;

typedef struct G25Global {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ u8 unk14;
} G25Global;

#define G25_A ((G25Actor *)D_807FBB40)
#define G25_P ((G25Player *)D_807FD580)
#define G25_GS ((G25Global *)&D_807FBB70)
#define G25_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))

extern u8 D_807FBB8C;
extern f32 D_807531E0[];
extern f32 D_8075318C[];
extern f32 D_807534B8[];
extern s16 D_807534D4[];
extern s16 D_8075380C[];
extern s16 D_8075381C[];
extern s16 D_8075382C[];
extern s16 D_8075385C[];
extern f32 D_80750FF4;
extern u8 D_807FC9AE[];
extern u8 D_807FCA0C[];
extern u8 D_807FCAC8[];
s32 func_806E4580(void);
s32 func_806725E4();
s32 func_80671E00(f32, f32, f32, f32, void *, void *, s32, s32);
void func_80618104(void *);
void func_80617770(void *, s32, s32);
void func_806F0B34(void *);
void func_806EAB44();

void func_806E41EC(void) {
    G21Table *pad;

    if (G25_PAD(D_807FD63C, u16) & 0x4000) {
        G25_P->unk5C = D_80767CC0;
    }
    if (D_807FBB8C && (func_8073110C(0x185, 0) || (D_807FBB64 & 0x10000000) || (D_807FC928 >= 2) ||
                       func_8071441C())) {
        func_806EB0C0(3, 0, D_807FC929);
        return;
    }
    if (func_806E4580()) {
        return;
    }
    pad = &D_807FD610[D_807FC929];
    if (!(pad->unk2C & 0x4000)) {
        return;
    }
    if (!(G25_A->unk6A & 1)) {
        return;
    }
    if (D_8074E77C[D_807FC929] == 6) {
        if (pad->unk2A & 0x2000) {
            G25_A->unk154 = 0x2F;
            G25_A->unk155 = 0;
            func_80614E78(D_807FBB40, 0x48);
            G25_P->unk68 = D_8075380C[D_807FD584];
            G25_P->unk38 = D_8075381C[D_807FD584];
            G25_P->unk30 = D_8075382C[D_807FD584];
            G25_P->unk48 = D_8075385C[D_807FD584];
            G25_A->unkEE = G25_A->unkE6;
        } else {
            G25_A->unk154 = 0x29;
            G25_A->unk155 = 0;
            func_80614EBC(D_807FBB40, 0x1DF);
            G25_P->unk64 = 0;
            G25_P->unk68 = D_8075380C[D_807FD584];
        }
    } else {
        if (!func_80714608(0) && (D_807531E0[D_807FD584] <= G25_P->unk20) && (G25_A->unkE0 == 0.0f)) {
            func_80614E78(D_807FBB40, 0x44);
            G25_A->unk154 = 0x29;
            G25_A->unk155 = 0;
            G25_A->unkEA = G25_A->unkEE;
            G25_A->unkB8 = 150.0f;
            G25_P->unk38 = 150.0f;
        } else {
            func_80614E78(D_807FBB40, 0x3F);
            G25_A->unk154 = 0x26;
            G25_A->unk155 = 0;
        }
        G25_P->unkC8 = 0x32;
        G25_P->unk64 = 0;
    }
}

s32 func_806E4580(void) {
    if ((G25_PAD(D_807FD63C, u16) & 0x4000) && G25_GS->unk2 && (G25_GS->unk14 == 8)) {
        G25_P->unk220 = G25_GS->unk4;
        G25_P->unk224 = G25_GS->unk8;
        G25_P->unk228 = G25_GS->unkC;
        func_806EB0C0(0x1F, 0, D_807FC929);
        return 1;
    }
    return 0;
}

void func_806E4634(void) {
    f32 v;
    f32 w;

    if (G25_PAD(D_807FD63C, u16) & 0x4000) {
        G25_P->unk5C = D_80767CC0;
    }
    if (G25_PAD(D_807FD63C, u16) & 0x4000) {
        v = G25_A->unkB4;
        if (G25_A->unk6A & 2) {
            w = G25_A->unk80 - G25_A->unkAC;
            if (!(v < w)) {
                v = w;
            }
        }
        if ((3.0f < v) && (D_8074E77C[D_807FC929] != 6)) {
            func_806EB0C0(0xF, 0, D_807FC929);
        }
    }
}

void func_806E4740(void) {
    u8 idx;

    idx = D_807FC929;
    if (*(u16 *)((u8 *)&D_807FD63C + idx * 0x34) & 0x4000) {
        if ((D_8075318C[D_807FD584] < G25_P->unk20) &&
            ((D_8074E77C[D_807FC929] == 3) || (D_8074E77C[D_807FC929] == 0) || (D_8074E77C[D_807FC929] == 5))) {
            if (D_8074E77C[D_807FC929] == 3) {
                G25_A->unkC0 = 200.0f;
            }
            func_806CFE7C();
            G25_A->unk154 = 0x2B;
            G25_A->unk155 = 0;
            func_80614E78(D_807FBB40, 0x45);
            G25_P->unkC8 = 0x32;
        } else {
            switch (D_8074E77C[D_807FC929]) {
                case 2:
                    if (D_807FCA0C[D_807FC929 * 0x306] > 0) {
                        func_806EB0C0(0x25, 0, D_807FC929);
                    }
                    break;
                case 4:
                    if (D_807FCAC8[D_807FC929 * 0x306] >= 2) {
                        func_806EB0C0(0x26, 0, D_807FC929);
                    }
                    break;
                case 1:
                    if (D_807FC9AE[D_807FC929 * 0x306] > 0) {
                        G25_P->unk48 = 0x64;
                        G25_A->unk154 = 0x2E;
                        G25_A->unk155 = 0;
                        func_80614E78(D_807FBB40, 0x48);
                        G25_P->unk68 = D_8075380C[D_807FD584] * 4;
                        G25_P->unk38 = D_8075381C[D_807FD584] * 2;
                        G25_P->unk30 = D_8075382C[D_807FD584];
                    }
                    break;
                case 6:
                    G25_A->unk154 = 0x2F;
                    G25_A->unk155 = 0;
                    func_80614E78(D_807FBB40, 0x48);
                    G25_P->unk68 = D_8075380C[D_807FD584];
                    G25_P->unk38 = D_8075381C[D_807FD584];
                    G25_P->unk30 = D_8075382C[D_807FD584];
                    G25_P->unk48 = D_8075385C[D_807FD584];
                    G25_A->unkEE = G25_A->unkE6;
                    break;
            }
        }
    }
}

void func_806E4AD8(void) {
    s16 sp3E;
    s16 sp3C;
    u8 dead;
    u8 ok;
    f32 f;

    ok = 1;
    if (G25_PAD(D_807FD63C, u16) & 0x2000) {
        if (G25_P->unk1AC->unkFC == 0) {
            f = (G25_P->unk1AC->unk58 == 0x3D) ? D_80750FF4 : 30.0f;
            if (func_80671E00(G25_A->unk7C, G25_A->unk80, G25_A->unk84, f, &sp3E, &sp3C, 1, 0)) {
                if (!func_806725E4(sp3E, sp3C, G25_A->unkE6, 0)) {
                    ok = 0;
                }
            }
            if (ok) {
                G25_A->unk154 = 0x4A;
                G25_A->unk155 = 0;
                switch (G25_P->unk1AC->unk58) {
                    case 0x3D:
                    case 0x3F:
                    case 0x40:
                    case 0x41:
                    case 0x42:
                    case 0x55:
                    case 0x82:
                        func_80614EBC(D_807FBB40, 0x1CD);
                        break;
                    default:
                        func_80614E78(D_807FBB40, 0x2C);
                        break;
                }
            }
        }
    }
}

void func_806E4C6C(void) {
    if ((G25_P->unk1AC->unk58 != 0x55) && (G25_P->unk1AC->unk58 != 0x82)) {
        G25_A->unk154 = 0x4B;
        G25_A->unk155 = 0;
        switch (G25_P->unk1AC->unk58) {
            case 0x3D:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
                func_80614EBC(D_807FBB40, 0x1CC);
                break;
            default:
                func_80614E78(D_807FBB40, 0x2D);
                break;
        }
    }
}

void func_806E4D14(void) {
    if ((G25_P->unk1AC->unk58 != 0x55) && (G25_P->unk1AC->unk58 != 0x82)) {
        G25_A->unkC0 = 200.0f;
        G25_A->unk154 = 0x4D;
        G25_A->unk155 = 0;
        func_80614E78(D_807FBB40, 0x2D);
    }
}

void func_806E4D84(void) {
    if ((func_806E56EC() == 0) && (G25_P->unkC8 == -1)) {
        if ((D_8074E77C[D_807FC929] != 6) || (G25_A->unkB8 < D_807531E0[D_807FD584])) {
            G25_A->unk154 = 0x3C;
            G25_A->unk155 = 0;
            func_80614E78(D_807FBB40, 0xA);
            G25_P->unk48 = D_807534D4[D_807FD584];
        }
        G25_P->unk30 = D_807534B8[D_807FD584];
    }
}

void func_806E4E88(void) {
    if ((G25_PAD(D_807FD63C, u16) & 1) && func_806E2CC4()) {
        func_80618104(D_807FBB40);
        func_80617770(D_807FBB40, 0x21, 0x19);
    }
    if (G25_PAD(D_807FD63C, u16) & 2) {
        if (D_80767CC0 - G25_P->unk60 < 0xF) {
            if (G25_P->unk8C) {
                func_806F0B34(D_807FBB40);
            }
            G25_P->unk8C = 0;
            func_806EAB44(D_807FBB40, 0);
        } else if (!func_80714608(0) && !(D_807FBB64 & 0x80000200) && (D_807FD568[2] & 1) &&
                   !(G25_P->unk1F0 & 0x30) &&
                   (*((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x2C0) == 1)) {
            func_806DF44C((s32)D_807FBB40, (G21Actor1A0 *)D_807FD580, 1);
        }
        G25_P->unk60 = D_80767CC0;
    }
}

void func_806E5044(void) {
    if ((G25_PAD(D_807FD63C, u16) & 1) && func_806E2CC4()) {
        func_80618104(D_807FBB40);
        func_80617770(D_807FBB40, 0x21, 0x19);
    }
    if (G25_PAD(D_807FD63C, u16) & 2) {
        if (D_80767CC0 - G25_P->unk60 < 0xF) {
            if (G25_P->unk8C) {
                func_806F0B34(D_807FBB40);
            }
            G25_P->unk8C = 0;
            func_806EAB44(D_807FBB40, 0);
        } else if (!func_80714608(0) && !(D_807FBB64 & 0x200) && (D_807FD568[2] & 1) &&
                   (*((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x2C0) == 1)) {
            func_806DF44C((s32)D_807FBB40, (G21Actor1A0 *)D_807FD580, 1);
            *(f32 *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x27C) = 45.0f;
        }
        G25_P->unk60 = D_80767CC0;
    }
}

void func_806E521C(void) {
    if (func_80714608(0)) {
        if (((D_807FBB40->unk154 == 0x31) || (D_807FBB40->unk154 == 0x32)) && (G25_P->unk8C == 0)) {
            func_806E4D84();
        }
    }
}

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

s32 func_806E527C(void) {
    s32 ret;
    s32 i;
    Actor *actor;

    ret = 0;
    for (i = 0; i < gActiveActorCount && ret == 0; i++) {
        actor = gActiveActors[i].actor;
        ret = actor->unk60 & 0x2000000;
    }
    return ret;
}

typedef struct G26Mob {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x6A - 0x5C];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x7C - 0x6C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ f32 unk94;
    /* 0x98 */ f32 unk98;
    /* 0x9C */ u8 pad9C[0x10C - 0x9C];
    /* 0x10C */ s16 unk10C;
    /* 0x10E */ u8 pad10E[2];
    /* 0x110 */ u8 unk110;
} G26Mob;

extern u32 D_8076A064;
extern s32 D_807FBB68;
u8 func_806E5488(G26Mob *arg0);
int func_806E560C(G26Mob *arg0);

void func_806E52D0(void) {
    u8 r;
    u32 n;

    if ((G25_PAD(D_807FD63C, u16) & 8) && (D_8076A064 >= 3) && (D_807FD568[4] & 1) &&
        !(D_807FBB64 & 0x4000) && !(D_807FBB68 & 1) &&
        (*((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x2C0) != 2) &&
        (func_806E5488((G26Mob *)D_807FBB40) == 0) && (func_806E527C() == 0) &&
        (*((u8 *)D_807FD580 + 0x245) == 0)) {
        r = func_806E560C((G26Mob *)D_807FBB40);
        if ((D_8076A0A8 != 0xCD) || (r != 0)) {
            n = r;
            if ((func_806F8AD4(7, D_807FC929) != 0) || (n != 0)) {
                func_806EB0C0(0x53, 0, *((u8 *)D_807FD580 + 0x1A4));
                if (!(D_807FBB68 & 2)) {
                    D_807FBB40->unk144 = 1;
                }
                if (n == 0) {
                    func_806F91B4(7, D_807FC929, -1);
                }
            }
            if (n == 0) {
                func_806F8BC4(7, 0, 0);
            }
        }
    }
}

s32 func_8063C328();

u8 func_806E5488(G26Mob *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;

    if (arg0->unk110 == 1) {
        dx = arg0->unk94 - arg0->unk88;
        dz = arg0->unk98 - arg0->unk90;
        if (sqrtf(dx * dx + dz * dz) > 1.0) {
            return 1;
        }
    }
    if (arg0->unk6A & 8) {
        dx = arg0->unk7C - arg0->unk88;
        dz = arg0->unk80 - arg0->unk8C;
        dy = arg0->unk84 - arg0->unk90;
        if (sqrtf(dx * dx + dz * dz + dy * dy) > 1.0) {
            return 1;
        }
    }
    if ((arg0->unk110 == 1) && (func_8063C328(arg0->unk10C) == 0x88)) {
        return 1;
    }
    if ((arg0->unk110 == 1) && (func_8063C328(arg0->unk10C) == 0x219)) {
        return 1;
    }
    if ((arg0->unk110 == 1) && (func_8063C328(arg0->unk10C) == 0x132)) {
        return 1;
    }
    return 0;
}

int func_806E560C(G26Mob *arg0) {
    u8 ret;

    ret = 0;
    if (arg0->unk110 == 1) {
        switch (func_8063C328(arg0->unk10C, arg0)) {
            case 0xA8:
                if (arg0->unk58 == 2) {
                    ret = 1;
                }
                break;
            case 0xA9:
                if (arg0->unk58 == 3) {
                    ret = 1;
                }
                break;
            case 0xAA:
                if (arg0->unk58 == 5) {
                    ret = 1;
                }
                break;
            case 0xAB:
                if (arg0->unk58 == 6) {
                    ret = 1;
                }
                break;
            case 0xAC:
                if (arg0->unk58 == 4) {
                    ret = 1;
                }
                break;
        }
    }
    return ret;
}

typedef struct G26Gs {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14;
} G26Gs;

typedef struct G26Plr {
    /* 0x000 */ u8 pad0[0x50];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[2];
    /* 0x054 */ f32 unk54;
    /* 0x058 */ u8 pad58[0xC0 - 0x58];
    /* 0x0C0 */ s16 unkC0;
    /* 0x0C2 */ u8 padC2[0x1F0 - 0xC2];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x1FE - 0x1F4];
    /* 0x1FE */ s16 unk1FE;
    /* 0x200 */ u8 pad200[4];
    /* 0x204 */ f32 unk204;
    /* 0x208 */ f32 unk208;
    /* 0x20C */ f32 unk20C;
    /* 0x210 */ u8 pad210[0x21C - 0x210];
    /* 0x21C */ s16 unk21C;
    /* 0x21E */ u8 pad21E[0x242 - 0x21E];
    /* 0x242 */ s16 unk242;
    /* 0x244 */ u8 pad244[0x268 - 0x244];
    /* 0x268 */ u8 unk268;
} G26Plr;

typedef struct G26Act {
    /* 0x000 */ u8 pad0[0x7C];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0xC0 - 0x88];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x144 - 0xC8];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0x154 - 0x145];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G26Act;

#define G26_GS ((G26Gs *)&D_807FBB70)
#define G26_PL ((G26Plr *)D_807FD580)
#define G26_AC ((G26Act *)D_807FBB40)

extern u8 D_807F6903;
extern s32 D_8076A094;
extern u8 D_8076A0B2;
extern f32 D_807536AC[];
extern u8 D_8072014C[];
void func_8071F034(void);
void func_805FF158(s32);
void func_805FF9AC(s32, s32, s32, s32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_806C93E4(void *, void *);
s32 func_8061CC40(void *, s32, s32);
void func_806F1250(Actor *);
void timerQueueAdd(void *, s32, s32, s32, s32);
void func_8071496C(s16);
void func_80714CC0(void *, f32, f32, f32, f32);
void func_80686CF8(Actor *);
void func_806E5C2C(s32, s32, s32);

s32 func_806E56EC() {
    s32 i;

    if (G26_GS->unk2 != 0) {
        switch (G26_GS->unk14) {
            case 9:
                if (G26_PL->unk268 == 0) {
                    G26_PL->unk204 = G26_GS->unk4;
                    G26_PL->unk208 = G26_GS->unk8;
                    G26_PL->unk20C = G26_GS->unkC;
                    G26_PL->unk21C = G26_GS->unk10;
                    func_806EB0C0(0x1E, 0, D_807FC929);
                    func_806C93E4(D_807FBB40, D_807FD580);
                    return 1;
                }
                break;
            case 5:
                if (D_807F6903 == 0) {
                    if (++D_8076A094 < 0x5DD) {
                        G26_PL->unk204 = G26_GS->unk4;
                        G26_PL->unk208 = G26_GS->unk8;
                        G26_PL->unk20C = G26_GS->unkC;
                        func_806EB0C0(0x1C, 0, D_807FC929);
                        func_806C93E4(D_807FBB40, D_807FD580);
                        return 1;
                    }
                }
                break;
            case 3:
                if (D_807F6903 == 0) {
                    if (++D_8076A094 < 0x5DD) {
                        G26_PL->unk204 = G26_GS->unk4;
                        G26_PL->unk208 = G26_GS->unk8;
                        G26_PL->unk20C = G26_GS->unkC;
                        func_806EB0C0(0x1D, 0, D_807FC929);
                        func_806C93E4(D_807FBB40, D_807FD580);
                        return 1;
                    }
                }
                break;
            case 10:
                if (D_8076A0B2 == 0) {
                    func_806086CC(G26_AC->unk7C, G26_AC->unk80, G26_AC->unk84, 0xE6, 0xFF, 0x7F, 0, 0, 0.3f, 0);
                    func_805FF158(0);
                    func_805FF9AC(G26_GS->unk10, G26_GS->unk12, 0, 0);
                }
                return 1;
            case 4:
                if (!(G26_PL->unk1F0 & 0x40)) {
                    func_806F1250(D_807FBB4C);
                    G26_PL->unk1FE = G26_GS->unk10;
                }
                return 1;
            case 0:
                if (D_8076A064 >= 4) {
                    func_8061CC40(D_807FBB40, 0x26, 5);
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x18, 0xFF, 0x7F, 0x19);
                    G26_AC->unk154 = 0x18;
                    G26_AC->unk155 = 0;
                    G26_AC->unk144 = 1;
                    G26_PL->unk54 = D_807535CC[D_807FD584] * 2.5;
                    G26_PL->unk50 = 0x28;
                    func_80614E78(D_807FBB40, 0x22);
                    timerQueueAdd(func_806E5C2C, 0x14, G26_GS->unk10, G26_GS->unk12, 0);
                    for (i = 0; i != 0x14; i++) {
                        func_807149B8(1);
                        func_8071498C(func_8071F034);
                        func_8071496C(i);
                        func_80714CC0(D_8072014C, 0.8f, G26_AC->unk7C, G26_AC->unk80, G26_AC->unk84);
                    }
                    func_80686CF8(D_807FBB4C);
                    return 1;
                }
                break;
            case 2:
                G26_AC->unk154 = 0x1B;
                G26_AC->unk155 = 0;
                G26_PL->unk54 = D_807536AC[D_807FD584];
                G26_PL->unk50 = 0;
                func_80614E78(D_807FBB40, 0x14);
                return 1;
            case 6:
                G26_AC->unk154 = 0x6E;
                G26_AC->unk155 = 0;
                G26_AC->unkC0 = 0.0f;
                G26_AC->unkC4 = G26_GS->unk10 * 0.2 + 2.0;
                G26_PL->unkC0 = G26_GS->unk12;
                func_80614EBC(D_807FBB40, 0x169);
                return 1;
            case 7:
                G26_AC->unk144 = 1;
                G26_PL->unk242 = G26_GS->unk10;
                G26_AC->unk154 = 0x76;
                G26_AC->unk155 = 0;
                func_80614E78(D_807FBB40, 0x86);
                return 1;
        }
    }
    return 0;
}

void func_8070B308(s32);

void func_806E5C2C(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 != 0) {
        func_8070B308(2);
        func_805FF158(0);
    }
    func_805FF9AC(arg0, 0, 0, 0);
}

typedef struct G26Obj {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[0xAC - 0x8];
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0xF1 - 0xBC];
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4;
    /* 0xF5 */ u8 unkF5;
} G26Obj;

typedef struct G26Holder {
    /* 0x000 */ u8 pad0[0xB4];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ u8 padB8[0x174 - 0xB8];
    /* 0x174 */ G26Obj *unk174;
} G26Holder;

typedef struct G26Player {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ G26Holder *unk104;
    /* 0x108 */ u8 pad108[0x1CC - 0x108];
    /* 0x1CC */ f32 unk1CC;
} G26Player;

#define G26_P ((G26Player *)D_807FD580)
extern u8 D_80750AB8;

int func_806E5C74(void) {
    f32 fv;
    f32 t;

    fv = G25_A->unkB4;
    if (G25_A->unk6A & 2) {
        t = G25_A->unk80 - G25_A->unkAC;
        if (!(fv < t)) {
            fv = t;
        }
    }
    return ((G25_PAD(D_807FD63C, u16) & 0x2000) != 0) && ((f64)G26_P->unk1CC * 66.0 < (f64)fv) &&
           (D_8074E77C[D_807FC929] != 6) && (D_807FD568[1] != 0);
}

void func_80613AF8(void *, s32, f32, f32);

void func_806E5D60(void) {
    if (func_806E5C74() != 0) {
        switch (D_807FD568[1]) {
            case 2:
                func_80614E78(D_807FBB40, 0x17);
                func_80613AF8(D_807FBB40, 0x18, 0.0f, 3.0f);
                func_80614D00(D_807FBB40, 1.35f, 0.0f);
                break;
            case 3:
                func_80614E78(D_807FBB40, 0x19);
                break;
            default:
                func_80614E78(D_807FBB40, 0x16);
                func_80613AF8(D_807FBB40, 0x17, 0.0f, 3.0f);
                func_80614D00(D_807FBB40, 1.35f, 0.0f);
                break;
        }
        G25_A->unk154 = 0x1C;
        G25_A->unk155 = 0;
    }
}

void func_806E5E58(void) {
}

void func_806E5E60(void) {
}

void func_806E5E68(void) {
    if (!(G25_P->unk1F0 & 0x20)) {
        func_806EB0C0(0x24, 0, D_807FC929);
    }
}

void func_806E5EA8(void) {
    func_806EB0C0(0x24, 0, D_807FC929);
}

void func_806E5ED4(void) {
    if ((G25_PAD(D_807FD63C, u16) & 2) && (D_807FD568[2] & 1) &&
        (*((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x2C0) == 1) && !(G25_P->unk1F0 & 0x30) &&
        (func_80714608(0) == 0)) {
        func_806EB0C0(0x14, 0, D_807FC929);
    }
}

void func_806E5FA0(void) {
    if ((G25_PAD(D_807FD63C, u16) & 2) && (D_807FD568[2] & 1) && !(D_807FBB64 & 0x200) &&
        (*((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x2C0) == 1) && !(G25_P->unk1F0 & 0x30) &&
        (func_80714608(0) == 0)) {
        func_806EB0C0(0x15, 0, D_807FC929);
    }
}

void func_806261CC(void *);
void func_80626110(void *, s32, s32);

void func_806E607C(void) {
    G26Obj *obj;

    obj = G26_P->unk104->unk174;
    obj->unkAC |= 4;
    if (G25_PAD(D_807FD63C, u16) & 0x10) {
        if ((D_807FBB64 & 1) || ((D_807FC928 >= 2) && (D_80750AB8 == 0))) {
            if (obj->unkAC & 0x10000) {
                func_806261CC(G26_P->unk104);
                return;
            }
            func_80626110(G26_P->unk104, 0, 0);
            return;
        }
        if (!(obj->unkAC & 0x4000)) {
            obj->unkAC ^= 2;
            if ((obj->unkF1 < 3) && (obj->unkF5 == 0) && (obj->unkF3 != 2)) {
                obj->unkF1 = 0x14;
                obj->unkB2 = G25_A->unkE6;
                G26_P->unk104->unkB4 = obj->unkB8;
                obj->unkF5 = 0xA;
            }
        }
    }
}

void func_806E61D0(void) {
    G26Obj *obj;

    if (!(D_807FBB64 & 1) && ((D_807FC928 < 2) || (D_80750AB8 != 0))) {
        obj = G26_P->unk104->unk174;
        obj->unk4 = 0;
        obj->unkAC &= ~4;
    }
}

extern u8 D_807FC8B9;
extern s32 D_807FBB60;
extern f32 D_807FD888;
s32 func_8061CB50(void);
s32 func_8071432C(void);
s32 func_8062919C(void);
s32 func_806291A8(void);

void func_806E6234(void) {
    if ((G25_PAD(D_807FD63C, u16) & 0x1000) && (func_8061CB50() == 0) && (D_807FD888 == 0.0f) &&
        ((func_8071432C() != 0) || (func_8071441C() != 0) || (func_807142D8() != 0)) &&
        (func_8062919C() == 0) && (func_806291A8() == 0)) {
        D_807FC8B9 = D_807FC929;
        D_807FBB60 |= 1;
    }
}

typedef struct G27Player {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[0x1E];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A[0xE];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
} G27Player;

typedef struct G27Actor {
    /* 0x000 */ u8 pad0[0xE4];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x155 - 0xEA];
    /* 0x155 */ u8 unk155;
} G27Actor;

typedef struct G29BtnA {
    u16 unk0;
    u8 pad2[0x32];
} G29BtnA;
typedef G29BtnA G27Btn;

#define G27_P ((G27Player *)D_807FD580)
#define G27_A ((G27Actor *)D_807FBB40)

extern f32 D_80753988[];
extern s16 D_80753B34[];
extern f32 D_8075396C[];
extern f32 D_80753AC4[];
extern f32 D_80753AA8[];
extern s16 D_80753A98[];
extern s16 D_8075395C[];
extern s16 D_80753B44[];

void func_806E6318(void) {
    if (G25_PAD(D_807FD63C, u16) & 0x8000) {
        G27_P->unk58 = D_80767CC0;
    }
}

void func_806E6368(void) {
    if (G25_PAD(D_807FD63C, u16) & 0x4000) {
        G27_P->unk5C = D_80767CC0;
    }
}

void func_806E63B8(void) {
    f32 temp;

    if (D_807FD610[D_807FC929].unk4 != 0.0f) {
        temp = G27_P->unk34;
        G27_P->unk4 = (D_807FD610[D_807FC929].unk8 * (G27_P->unk38 - temp)) + temp;
    } else {
        G27_P->unk4 = 0.0f;
    }
    G27_P->unk4 = G27_P->unk4 / 4;
    if (D_807FD610[D_807FC929].unk4 != 0.0f) {
        func_806DF494(&G27_A->unkE6, D_807FD610[D_807FC929].unk28, G27_P->unk48);
    }
    func_806DF494(&G27_A->unkE8, 0, 0x10);
    func_806DF494(&G27_A->unkE4, 0, 0x10);
}

void func_806E64D0(void) {
    s16 var_a1;

    if (D_807FD610[D_807FC929].unk30 != 0) {
        var_a1 = D_80753B34[D_807FD584] * ((D_807FD610[D_807FC929].unk2E >= 0) ? 1 : -1);
        var_a1 &= 0xFFF;
    } else {
        var_a1 = 0;
    }
    func_806DF494(&G27_A->unkE4, var_a1, 0x10);
    func_806DF494(&G27_A->unkE8, G27_P->unk12, 0x10);
    G27_P->unk38 = D_80753988[D_807FD584];
}

extern s16 D_80753B54[];
extern s16 D_80753B64[];

void func_806E65BC(void) {
    s32 ang;
    s16 var_a1;
    s16 var_t1;

    ang = G27_A->unkE6;
    var_t1 = 0x10;
    if (D_8074E77C[D_807FC929] == 7) {
        var_t1 = 0x19;
    }
    if (D_807FD610[D_807FC929].unk30 != 0) {
        ang ^= 0;
        G27_A->unkE6 = (u16)(ang - (D_807FD610[D_807FC929].unk2E / 2)) & 0xFFF;
        var_a1 = D_80753B54[D_807FD584] * ((D_807FD610[D_807FC929].unk2E >= 0) ? 1 : -1);
        var_a1 &= 0xFFF;
    } else {
        var_a1 = 0;
    }
    func_806DF494(&G27_A->unkE4, var_a1, 0x10);
    if (D_807FD610[D_807FC929].unk2F != 0) {
        var_a1 = (D_80753B44[D_807FD584] * D_807FD610[D_807FC929].unk2F) / 70;
        var_a1 = var_a1 & 0xFFF;
        func_806DF494(&G27_A->unkE8, var_a1, (s16)(s32)((((f64)D_807FD610[D_807FC929].unk2F * 0.125) > 0.0 ? ((f64)D_807FD610[D_807FC929].unk2F * 0.125) : -((f64)D_807FD610[D_807FC929].unk2F * 0.125)) + (f64)var_t1));
        return;
    }
    func_806DF494(&G27_A->unkE8, D_80753B64[D_807FD584], 0x10);
}

void func_806E67D8(void) {
    f32 var_fv0;
    f32 var_fv1;
    s16 temp_a1;
    s32 temp_v0;

    func_806E007C();
    if (G27_P->unk4 != 0.0f) {
        var_fv1 = (f32)(((f64)*(f32 *)(D_807FD618 + D_807FC929 * 0x34) * 0.5) + 0.5);
        temp_a1 = G27_P->unkA;
        temp_v0 = G27_A->unkE6 - temp_a1;
        if (temp_v0 > 0) {
            var_fv0 = (f32)temp_v0;
        } else {
            var_fv0 = (f32)-temp_v0;
        }
        if (var_fv0 > 2048.0f) {
            var_fv0 = 4096.0f - var_fv0;
        }
        if (var_fv0 > 400.0f) {
            var_fv0 = 400.0f;
        }
        var_fv0 = var_fv0 * ((f64)G27_P->unk48 / 400.0);
        func_806DF494(&G27_A->unkE6, temp_a1, (s16)(s32)(var_fv0 * var_fv1));
    }
    func_806DF494(&G27_A->unkE8, 0, 0x10);
    func_806DF494(&G27_A->unkE4, 0, 0x10);
    G27_P->unk12 = 0;
    G27_P->unk14 = G27_A->unkE6;
    G27_P->unk10 = D_8075395C[D_807FD584];
    G27_P->unk38 = D_80753988[D_807FD584] * *(f32 *)(D_807FD618 + D_807FC929 * 0x34);
    if (D_807FD63A[D_807FC929].unk0 & 0x4000) {
        G27_P->unk38 = G27_P->unk38 * 1.33;
    }
}

void func_806E6A38(void) {
    f32 var_fv0;
    f32 var_fv1;
    s16 temp_a1;
    s32 temp_v0;

    func_806E007C();
    if (G27_P->unk4 != 0.0f) {
        var_fv1 = (f32)(((f64)*(f32 *)(D_807FD618 + D_807FC929 * 0x34) * 0.5) + 0.5);
        temp_a1 = G27_P->unkA;
        temp_v0 = G27_A->unkE6 - temp_a1;
        if (temp_v0 > 0) {
            var_fv0 = (f32)temp_v0;
        } else {
            var_fv0 = (f32)-temp_v0;
        }
        if (var_fv0 > 2048.0f) {
            var_fv0 = 4096.0f - var_fv0;
        }
        if (var_fv0 > 400.0f) {
            var_fv0 = 400.0f;
        }
        var_fv0 = var_fv0 * 0.45;
        func_806DF494(&G27_A->unkE6, temp_a1, (s16)(s32)(var_fv0 * var_fv1));
    }
    func_806DF494(&G27_A->unkE8, 0, 0x10);
    func_806DF494(&G27_A->unkE4, 0, 0x10);
}

void func_806E6B98(void) {
    s16 pad;
    s16 var_a1;
    s16 ang;
    s16 var_a2;

    ang = G27_A->unkE6;
    var_a2 = 0x10;
    if (D_807FD610[D_807FC929].unk30 != 0) {
        if (D_8074E77C[D_807FC929] == 7) {
            ang = (s16)(s32)((f64)ang - ((f64)D_807FD610[D_807FC929].unk2E * 0.8));
        } else {
            ang = (s16)(s32)((f64)ang - ((f64)D_807FD610[D_807FC929].unk2E * 0.5));
        }
        G27_A->unkE6 = ang & 0xFFF;
        var_a1 = D_80753B34[D_807FD584] * ((D_807FD610[D_807FC929].unk2E >= 0) ? 1 : -1);
        var_a1 &= 0xFFF;
    } else {
        var_a1 = 0;
    }
    func_806DF494(&G27_A->unkE4, var_a1, 0x10);
    var_a1 = (D_80753B44[D_807FD584] * D_807FD610[D_807FC929].unk2F) / 70;
    var_a1 = var_a1 & 0xFFF;
    if (D_8074E77C[D_807FC929] == 7) {
        var_a2 = (s16)(s32)((((f64)D_807FD610[D_807FC929].unk2F * 0.5) > 0.0 ? ((f64)D_807FD610[D_807FC929].unk2F * 0.5) : -((f64)D_807FD610[D_807FC929].unk2F * 0.5)) + 16.0);
    }
    func_806DF494(&G27_A->unkE8, var_a1, var_a2);
}

void func_806E6DE8(void) {
    if (G25_PAD(D_807FD63C, u16) & 0x8000) {
        G27_P->unk58 = D_80767CC0;
    }
    if (D_80767CC0 - G27_P->unk58 < 0xF) {
        func_806EB0C0(1, 0, D_807FC929);
    }
}

void func_806E6E7C(void) {
    G27_P->unk12 = 0;
    G27_P->unk14 = G27_A->unkE6;
    if (G27_P->unk10 == 0) {
        G27_P->unk10 = 1;
        G27_P->unk38 = D_8075396C[D_807FD584];
    }
}

void func_806E6EE0(void) {
    if (!(D_807FD610[D_807FC929].unk2A & 0x2000) && (D_807FD610[D_807FC929].unk2C & 0x8000)) {
        func_80614E78(D_807FBB40, 0x37);
        G27_A->unk155 = 4;
        G27_P->unk58 = D_80767CC0;
    }
}

void func_806E6F74(void) {
    if (!(D_807FD63A[D_807FC929].unk0 & 0x2000)) {
        func_80614E78(D_807FBB40, 0x37);
        G27_A->unk155 = 4;
        G27_P->unk58 = D_80767CC0;
    }
}

void func_806E6FF0(void) {
    G27_P->unk58 = D_80767CC0;
    func_80614D00(D_807FBB40, 2.0f, 0.0f);
    func_80614E78(D_807FBB40, 0x38);
    G27_A->unk155 = 7;
}

void func_806E7050(void) {
    func_80614E78(D_807FBB40, 0x39);
    G27_A->unk155 = 7;
}

void func_806E7088(void) {
    G27_A->unk155 = 6;
}

void func_806E709C(void) {

    if (!(D_807FD610[D_807FC929].unk2A & 0x2000)) {
        if (D_807FD610[D_807FC929].unk2C & 0x4000) {
            G27_P->unk12 = G27_A->unkE8;
            G27_P->unk14 = G27_A->unkE6;
            if (G27_P->unk10 == 0) {
                G27_P->unk38 = D_80753AC4[D_807FD584];
                func_80614E78(D_807FBB40, 0x36);
            } else {
                G27_P->unk38 = D_80753AA8[D_807FD584];
            }
            G27_P->unk10 = D_80753A98[D_807FD584];
            G27_P->unk5C = D_80767CC0;
        } else if (!(D_807FD610[D_807FC929].unk2C & 0x8000)) {
            G27_P->unk12 = G27_A->unkE8;
            G27_P->unk14 = G27_A->unkE6;
            if (G27_P->unk10 == 0) {
                G27_P->unk10 = 1;
                G27_P->unk38 = D_80753AA8[D_807FD584];
            }
        }
    }
}

void func_806E7230(void) {
    if (!(D_807FD63A[D_807FC929].unk0 & 0x2000)) {
        G27_P->unk12 = G27_A->unkE8;
        G27_P->unk14 = G27_A->unkE6;
        if (G27_P->unk10 == 0) {
            G27_P->unk38 = D_80753AC4[D_807FD584];
            func_80614E78(D_807FBB40, 0x36);
        } else {
            G27_P->unk38 = D_80753AA8[D_807FD584];
        }
        G27_P->unk10 = D_80753A98[D_807FD584];
        G27_P->unk5C = D_80767CC0;
    }
}

typedef struct G28State {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[0x28];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 pad30[4];
    /* 0x34 */ u8 *unk34;
    /* 0x38 */ u8 pad38[6];
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
    /* 0x40 */ u8 unk40;
    /* 0x41 */ u8 pad41;
    /* 0x42 */ u8 unk42;
} G28State;

typedef struct G28Anim0 {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} G28Anim0;

typedef struct G28Anim {
    /* 0x00 */ G28Anim0 *unk0;
} G28Anim;

typedef struct G28Actor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G28Anim *unk4;
    /* 0x008 */ u8 pad8[0xAC];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x6A];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ G28State *unk174;
} G28Actor;

typedef struct G28Player {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[0x1A];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x1C];
    /* 0x58 */ u32 unk58;
    /* 0x5C */ u32 unk5C;
    /* 0x60 */ u8 pad60[0x28];
    /* 0x88 */ G28Actor *unk88;
    /* 0x8C */ u8 pad8C[0x164];
    /* 0x1F0 */ s32 unk1F0;
} G28Player;

#define G28_P ((G28Player *)D_807FD580)
#define G28_A ((G28Actor *)D_807FBB40)
#define G28_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))
#define G28_PADS ((G21Table *)((u8 *)D_807FD610 + D_807FC929 * 0x34))

void func_806E7338(void) {
    s32 btn;

    btn = G28_PAD(D_807FD63C, u16);
    if (btn & 0x8000) {
        G28_A->unk155 = 3;
        G28_P->unk12 = G28_A->unkE8;
        G28_P->unk14 = G28_A->unkE6;
        if (G28_P->unk10 == 0) {
            G28_P->unk38 = 300.0f;
            func_80614EBC(D_807FBB40, 0x318);
        } else {
            G28_P->unk38 = 250.0f;
        }
        G28_P->unk10 = 0xF;
        G28_P->unk5C = D_80767CC0;
        return;
    }
    if (!(btn & 0x4000)) {
        G28_P->unk12 = G28_A->unkE8;
        G28_P->unk14 = G28_A->unkE6;
        if (G28_P->unk10 == 0) {
            G28_P->unk10 = 1;
            G28_P->unk38 = 250.0f;
        }
    }
}

extern f32 D_80753B18[];

void func_806E7484(void) {
    if (G28_PAD(D_807FD63C, u16) & 0x8000) {
        G28_A->unk155 = 3;
        G28_P->unk12 = G28_A->unkE8;
        G28_P->unk14 = G28_A->unkE6;
        if (G28_P->unk10 == 0) {
            G28_P->unk38 = 300.0f;
            func_80614EBC(D_807FBB40, 0x318);
        } else {
            G28_P->unk38 = 250.0f;
        }
        G28_P->unk10 = 0xF;
        G28_P->unk5C = D_80767CC0;
    }
}


void func_806E7568(void) {
    if (G28_PAD(D_807FD63C, u16) & 0x4000) {
        G28_P->unk12 = G28_A->unkE8;
        G28_P->unk14 = G28_A->unkE6;
        G28_P->unk38 = D_80753AC4[D_807FD584];
        func_80614E78(D_807FBB40, 0x36);
        G28_A->unk155 = 3;
        G28_P->unk10 = D_80753A98[D_807FD584];
        G28_P->unk5C = D_80767CC0;
    }
}

void func_806E9804();

void func_806E7658(void) {
    if ((G28_PAD(D_807FD63C, u16) & 4) && !(D_807FBB64 & 2)) {
        func_806E9804(8);
        return;
    }
    G28_P->unk12 = G28_A->unkE8;
    G28_P->unk14 = G28_A->unkE6;
    G28_P->unk10 = 0;
    G28_P->unk30 = 8.0f;
}

s32 func_806E770C(void) {
    s32 var_v1;

    var_v1 = func_8073110C(0x182, 0) != 0;
    if (var_v1 == 0) {
        var_v1 = (D_807FBB64 & 0x10000000) != 0;
        if (var_v1 == 0) {
            var_v1 = D_807FC928;
            var_v1 = var_v1 >= 2;
            if (var_v1 == 0) {
                var_v1 = func_8071441C() != 0;
            }
        }
    }
    return var_v1 & 0xFF;
}

extern s16 D_8075386C[];
extern f32 D_8075389C[];

void func_806E7780(void) {
    f32 var_fv0;
    s32 btn;

    btn = G28_PAD(D_807FD63C, u16);
    if ((btn & 4) && !(D_807FBB64 & 2)) {
        func_806E9804(8);
        return;
    }
    if (*((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x2C0) == 1) {
        var_fv0 = D_8075386C[D_807FD584];
    } else {
        var_fv0 = D_8075389C[D_807FD584];
    }
    if ((btn & 0x2000) && (var_fv0 < G28_A->unkB4) && func_806E770C()) {
        func_806EB0C0(0x3E, 0, D_807FC929);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x10, 0xFF, 0x7F, 1);
    }
}

void func_806E78B8(void) {
    G28_P->unk30 = D_80753B18[D_807FD584];
}

void func_806E78E0(void) {
    G28_P->unk30 = 1.0f;
}

void func_806E78F8(void) {
}

void func_806E7900(void) {
    G28State *st;
    G21Table *pad;
    s8 stick;
    u8 state;

    st = G28_P->unk88->unk174;
    if (G28_A->unk154 == 7) {
        pad = &D_807FD610[D_807FC929];
        if (!(pad->unk2A & 0x10)) {
            stick = pad->unk2E;
            if (stick < -0x1E && G28_A->unk4->unk0->unk10 != 0xFB) {
                func_80614E78(D_807FBB40, 0x81);
                G28_A->unk154 = 0xA;
                G28_A->unk155 = 0;
                st->unk42 = 1;
            } else if (stick >= 0x1F && G28_A->unk4->unk0->unk10 != 0xFF) {
                func_80614E78(D_807FBB40, 0x7D);
                G28_A->unk154 = 0xB;
                G28_A->unk155 = 0;
                st->unk42 = 2;
            }
        }
    }
    stick = G28_PAD(D_807FD63E, s8);
    if ((stick < 0x1E && G28_A->unk154 != 0xA) || (stick >= -0x1D && G28_A->unk154 != 0xB)) {
        st->unk42 = 0;
        state = G28_A->unk154;
        if (state != 0xA) {
            if (state == 0xB) {
                if (G28_A->unk155 == 1) {
                    func_80614E78(D_807FBB40, 0x7E);
                } else {
                    func_80614E78(D_807FBB40, 0x80);
                }
                G28_A->unk154 = 7;
                G28_A->unk155 = 0;
            }
        } else {
            if (G28_A->unk155 == 1) {
                func_80614E78(D_807FBB40, 0x82);
            } else {
                func_80614E78(D_807FBB40, 0x80);
            }
            G28_A->unk154 = 7;
            G28_A->unk155 = 0;
        }
    }
}

void func_806E7B48(void) {
    G28State *st;

    st = G28_P->unk88->unk174;
    if (G28_P->unk1F0 & 8) {
        st->unk3E = 4;
    } else {
        st->unk3E = (G28_PAD(D_807FD63F, s8) * 0.5) + 60.0;
    }
    func_806E7900();
}

void func_806E7C70(void) {
    G28State *st;

    st = G28_P->unk88->unk174;
    if (D_807FD610) {
    }
    if (st->unk0 != 0) {
        G28_PAD(D_807FD63E, s8) = 0;
    }
    func_806E7900();
    if (G28_P->unk1F0 & 8) {
        st->unk3E = 3;
    } else {
        st->unk3E = (G28_PADS->unk2F / 1.5) + 80.0;
    }
    st->unk2 = G28_PADS->unk2E;
}

extern s16 D_80750338;

void func_806E7DF4(void) {
    G28State *st;
    u8 flag;
    s32 a1;
    u8 cnt;

    st = G28_P->unk88->unk174;
    if (st->unk0 != 0) {
        G28_PAD(D_807FD63E, s8) = 0;
    } else {
        flag = (G28_P->unk88->unk154 == 5) ? 1 : 0;
        a1 = (*st->unk34 & 0x80) ? 1 : 3;
        if (flag) {
            G28_PADS->unk2E = G28_PADS->unk2E * -1;
            if (flag * -1) {}
        }
        if (G28_P->unk1F0 & 0x10000002) {
            G28_PADS->unk2E = G28_PADS->unk2E * -1;
        }
        if (G28_P->unk1F0 & 0x10000002) {
            G28_PADS->unk2F = G28_PADS->unk2F * -1;
        }
        if ((*st->unk34 & 0xC0) &&
            ((G28_PADS->unk2E >= 0x1F && st->unk3F > 0) || (G28_PADS->unk2E < -0x1E && st->unk3F < a1))) {
            G28_P->unk58 = G24_SCHED280;
            G28_P->unk88->unkC0 = D_80750338;
            G28_P->unk58 = G24_SCHED280 - 0x1E;
            cnt = st->unk3F;
            st->unk2C = 1.0f;
            st->unk40 = cnt;
            if (G28_PADS->unk2E >= 0x1F) {
                st->unk3F = cnt - 1;
                if (st->unk3F == 1) {
                    st->unk3F = 0;
                }
                a1 = flag ? 0x81 : 0x7D;
                func_80614E78(D_807FBB40, a1);
                func_80614EBC(G28_P->unk88, flag ? 0x295 : 0x296);
            } else {
                st->unk3F = cnt + 1;
                if (st->unk3F == 1 && (*st->unk34 & 0x40)) {
                    st->unk3F = 2;
                }
                a1 = flag ? 0x7D : 0x81;
                func_80614E78(D_807FBB40, a1);
                func_80614EBC(G28_P->unk88, flag ? 0x296 : 0x295);
            }
        }
    }
    if (G28_P->unk1F0 & 8) {
        st->unk3E = 3;
        G28_P->unk88->unkB8 = 3.0f;
        return;
    }
    st->unk3E = (G28_PAD(D_807FD63F, s8) / 1.5) + 80.0;
}

typedef struct G29Anim0 {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[8];
    s16 unk10;
    u8 pad12[0x12];
    f32 unk24;
} G29Anim0;

typedef struct G29Anim {
    G29Anim0 *unk0;
    u8 pad4[0x60];
    u16 unk64;
} G29Anim;

typedef struct G29AnimActor {
    u8 pad0[4];
    G29Anim *unk4;
} G29AnimActor;

typedef struct G29Parent {
    u8 pad0[0x154];
    u8 unk154;
    u8 unk155;
} G29Parent;

typedef struct G29Obj178 {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    u8 padC[8];
    f32 unk14;
} G29Obj178;

typedef struct G29State {
    u8 pad0[2];
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0xC];
    s32 unk20;
    u8 pad24[1];
    u8 unk25;
    u8 pad26[3];
    u8 unk29;
    u8 pad2A[6];
    G29Parent *unk30;
    u8 unk34;
    u8 pad35[9];
    u8 unk3E;
    u8 pad3F[3];
    u8 unk42;
    u8 pad43[2];
    u8 unk45;
} G29State;

typedef struct G29Act {
    u8 pad0[0xB8];
    f32 unkB8;
    u8 padBC[0xB8];
    G29State *unk174;
    G29Obj178 *unk178;
} G29Act;

typedef struct G29Main {
    u8 pad0[0x88];
    G29Act *unk88;
    u8 pad8C[0x1B0];
    u16 unk23C;
} G29Main;

typedef G21Table G29Stick;


#define G29_M ((G29Main *)D_807FD580)
#define G29_BB48 ((G29AnimActor *)D_807FBB48)
#define G29_BB40 ((G29AnimActor *)D_807FBB40)
#define G29_PAR ((G29Parent *)D_807FBB40)

extern f32 D_80750FF8;
extern f32 D_80750FFC;
extern f32 D_80751000;
s32 func_805FCA64(void);
void renderCallbacksRegister(void *, void *, s32);
void actorDrawAnimatedEffect(s32, void *);
void func_80613C48(void *, s16, f32, f32);
void func_80614D48(void *, f32, f32);

void func_806E8244(void) {
    G29State *st;
    G29Stick *c;
    s16 v;

    st = G29_M->unk88->unk174;
    if (func_805FCA64() != 0) {
        renderCallbacksRegister(actorDrawAnimatedEffect, G29_M->unk88, 5);
    }
    v = D_807FBB40->unkE6;
    if (v < 0x200 || v >= 0xE01) {
        st->unk2 = ((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34))->unk2E;
        c = &D_807FD610[D_807FC929];
    } else if (v >= 0x201 && v < 0x600) {
        s8 t;
        st->unk2 = ((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34))->unk2F;
        c = ((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34));
        t = c->unk2E;
        c->unk2E = c->unk2F;
        c->unk2F = t;
    } else if (v >= 0x601 && v < 0xA00) {
        st->unk2 = -((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34))->unk2E;
        c = ((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34));
        c->unk2E = -c->unk2E;
        c->unk2F = -c->unk2F;
    } else {
        s8 t;
        st->unk2 = -((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34))->unk2F;
        c = ((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34));
        t = c->unk2E;
        c->unk2E = -c->unk2F;
        c->unk2F = -t;
    }
    if (c->unk2E < -0x1E) {
        G29_M->unk23C = 0x28;
        st->unk42 = 1;
    } else if (c->unk2E >= 0x1F) {
        G29_M->unk23C = 0x28;
        st->unk42 = 2;
    } else if (G29_M->unk23C != 0) {
        G29_M->unk23C--;
    } else {
        st->unk42 = 0;
    }
}

void func_806E84A4(void) {
    G29State *st;

    st = G29_M->unk88->unk174;
    st->unk3E = 0x14;
}

void func_806E84C0(void) {
    G29State *st;

    st = G29_M->unk88->unk174;
    st->unk3E = 0x64;
    if (G29_M->unk23C != 0) {
        G29_M->unk23C--;
    }
}

void func_806E84F8(void) {
    G29State *st;

    if (!(D_807FD63A[D_807FC929].unk0 & 0xE000)) {
        st = G29_M->unk88->unk174;
        st->unk3E = 0x32;
    }
}

void func_806E854C(G29State *arg0, s32 arg1, s32 arg2) {
    G29Anim0 *sub;
    s32 n;
    f32 f;
    f32 h;
    f32 cur;

    sub = G29_BB48->unk4->unk0;
    if (arg2 != sub->unk10) {
        if (arg1 == sub->unk10) {
            func_80613C48(D_807FBB48, arg2, 0.0f, 5.0f);
            return;
        }
        if (G29_BB40->unk4->unk0->unk24 >= 0.0f && sub->unk4 > 0.0f) {
            func_80614D48(D_807FBB48, -1.0f, 0.0f);
        }
        if (G29_BB40->unk4->unk0->unk4 == 0.0f) {
            func_80613C48(D_807FBB48, arg2, 0.0f, 5.0f);
        }
    } else {
        cur = arg0->unkC;
        f = (cur > 0.0f) ? cur : -cur;
        h = f - 0.2f;
        n = arg0->unk10 > 1.0 ? 8 : 5;
        cur = sub->unk4;
        f = n * h * 1.25f;
        if (f - 1.0f <= cur && cur <= f + 1.0f) {
            n = 0;
        } else {
            n = f <= cur ? -1 : 1;
        }
        func_80614D48(D_807FBB48, n, 5.0f);
    }
}

void func_806E8724(G29Act *arg0, G29State *arg1) {
    s32 sign;
    s32 t;
    f32 f;
    f32 g;
    f32 x;

    if (arg1->unk45 == 0 && arg1->unk34 == 2) {
        t = D_807FD610[D_807FC929].unk2F < -0x14;
        sign = D_807FD610[D_807FC929].unk2E >= 0 ? 1 : -1;
        f = D_807FD610[D_807FC929].unk30;
        if (f > 80.0f) {
            g = 80.0f;
        } else {
            g = f;
        }
        x = g;
        x *= sign;
        x *= 0.0125f;
        arg1->unkC = x;
        arg1->unkC = x * D_80750FFC;
        if (arg1->unk20 == 0) {
            arg1->unk20 = (arg0->unkB8 < D_80750FF8) & t;
        } else {
            arg1->unk20 = t;
        }
    } else {
        arg1->unk20 = 0;
        arg1->unkC = 0.0f;
    }
}

void func_806E884C(void) {
    G29Act *a;

    a = G29_M->unk88;
    if (a != NULL) {
        func_806E8724(a, a->unk174);
    }
}

void func_806E8880(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        st->unk8 = D_80751000;
    }
}

void func_806E88AC(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        st->unk8 = 0.0f;
    }
}

void func_806E88D8(void) {
    G29Act *a;
    G29State *st;
    s32 sp24;
    s32 a2;
    s32 sp1C;

    a = G29_M->unk88;
    if (a != NULL) {
        if (D_807FBB40->unk58 == 4) {
            sp24 = 0x1C7;
            a2 = 0x1C5;
            sp1C = 0x1C6;
        } else {
            sp24 = 0x53;
            a2 = 0x54;
            sp1C = 0x55;
        }
        st = a->unk174;
        func_806E8724(a, st);
        if (func_8061CB50() == 0 && G29_BB48->unk4->unk64 != 0x3B5) {
            if (st->unkC < 0.2f && st->unkC > -0.2f && sp24 != G29_BB48->unk4->unk0->unk10) {
                if (G29_BB48->unk4->unk0->unk24 >= 0.0f && G29_BB48->unk4->unk0->unk4 > 0.0f) {
                    func_80614D48(D_807FBB48, -1.0f, 5.0f);
                    return;
                }
                if (G29_BB40->unk4->unk0->unk4 == 0.0f) {
                    func_80613C48(D_807FBB48, sp24, 0.0f, 5.0f);
                }
            } else {
                if (st->unkC < -0.2f) {
                    func_806E854C(st, sp24, a2);
                    return;
                }
                if (st->unkC > 0.2f) {
                    func_806E854C(st, sp24, sp1C);
                }
            }
        }
    }
}

void func_806E8A8C(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2) {
            if (st->unk25 == 0) {
                st->unk4 = 1.1f;
            }
        } else {
            st->unk4 = 0.0f;
        }
    }
}

void func_806E8AF0(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk25 == 0) {
            st->unk4 = 0.0f;
        }
    }
}

void func_806E8B28(void) {
    G29Act *a;
    G29State *st;
    G29Obj178 *o;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2) {
            o = a->unk178;
            if (((G29BtnA *)&D_807FD63C)[D_807FC929].unk0 & 0x8000) {
                o->unk4 = 1;
            }
        }
    }
}

void func_806E8BA4(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2) {
            st->unk10 = 2.0f;
        } else {
            st->unk10 = 1.0f;
        }
    }
}

void func_806E8BFC(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        st->unk10 = 1.0f;
    }
}

void func_806E8C2C(void) {
    G29Act *a;
    G29Obj178 *o;
    s32 v1;
    s32 a0;
    s8 a1;

    a = G29_M->unk88;
    if (a != NULL) {
        if (G29_BB48->unk4->unk0->unk10 != 0x22A) {
            func_80613C48(D_807FBB48, 0x22A, 0.0f, 0.0f);
        }
        if (a->unk174->unk45 == 0 && a->unk174->unk30->unk154 == 2) {
            o = a->unk178;
            a0 = o->unk1;
            v1 = o->unk0;
            a1 = D_807FD63E[D_807FC929].unk0;
            if (a0 == v1 && o->unk4 == 0) {
                if (a1 >= 0x1F && v1 < 2) {
                    o->unk1 = v1 + 1;
                } else if (a1 < -0x1E) {
                    if (v1 > 0) {
                        o->unk1 = v1 - 1;
                    }
                }
                a0 = o->unk1;
                if (a0 != v1) {
                    o->unk4 = 2;
                    o->unk8 = 0.0f;
                }
            }
        }
    }
}

void func_806E8D54(void) {
    G29Act *a;
    G29State *st;
    G29Obj178 *o;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk34 != 0 && st->unk34 < 3 && st->unk45 == 0) {
            o = a->unk178;
            st->unk4 = o->unk14 + 1.1;
        }
    }
}

void func_806E8DB4(void) {
    G29Act *a;
    G29State *st;
    G29Obj178 *o;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk34 != 0 && st->unk34 < 3 && st->unk45 == 0) {
            o = a->unk178;
            st->unk4 = o->unk14;
        }
    }
}

void func_806E8E00(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2 && (((G29BtnA *)&D_807FD63C)[D_807FC929].unk0 & 0x8000)) {
            st->unk29 = 1;
        }
    }
}

void func_806E8E78(void) {
    if (G29_PAR->unk154 == 7 && !(D_807FD63A[D_807FC929].unk0 & 0x10)) {
        func_80614E78(D_807FBB40, 0x7F);
        G29_PAR->unk154 = 8;
        G29_PAR->unk155 = 0;
    }
}

typedef struct G30State {
    /* 0x00 */ s16 unk0;
} G30State;

typedef struct G30Act {
    /* 0x00 */ u8 pad0[0x80];
    /* 0x80 */ f32 unk80;
    /* 0x84 */ u8 pad84[0x28];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[4];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ u8 padC4[0x1C];
    /* 0xE0 */ f32 unkE0;
    /* 0xE4 */ u8 padE4[0x90];
    /* 0x174 */ G30State *unk174;
} G30Act;

#define G30_A ((G30Act *)D_807FBB40)

typedef struct G30Main {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[0xE];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 pad26[0x2A];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[2];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x2C];
    /* 0x88 */ G30Act *unk88;
    /* 0x8C */ u8 pad8C[0x38];
    /* 0xC4 */ s32 unkC4;
    /* 0xC8 */ u8 padC8[0x3C];
    /* 0x104 */ void *unk104;
} G30Main;

#define G30_M ((G30Main *)D_807FD580)
#define G30_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))

extern f32 D_807537E0[];
extern s16 D_80750338;
extern s16 D_807539DC[];
extern s16 D_807539EC[];
s32 func_806E9D1C();
void func_806F8D58(s32, s32);

void func_806E8F04(void) {
    if (G29_PAR->unk155 == 1) {
        func_80614E78(D_807FBB40, 0x7B);
    } else {
        func_80614E78(D_807FBB40, 0x80);
    }
    G29_PAR->unk154 = 7;
    G29_PAR->unk155 = 0;
}

void func_806E8F68(void) {
    if ((D_807FD610[D_807FC929].unk2C & 0x8000) && !(D_807FD610[D_807FC929].unk2A & 0x10)) {
        G30_M->unk58 = D_80767CC0;
    }
    if (D_80767CC0 - G30_M->unk58 < 0xF) {
        G29_PAR->unk154 = 9;
        G29_PAR->unk155 = 0;
        G30_M->unk54 = D_807537E0[D_807FD584];
        G30_M->unk50 = 0;
        func_80614E78(D_807FBB40, 0x7C);
        G30_M->unk58 = D_80767CC0 - 0x1E;
    }
}

void func_806E9070(void) {
    G30State *st;

    st = G30_M->unk88->unk174;
    if (G30_PAD(D_807FD63C, u16) & 0x8000) {
        G30_M->unk58 = G24_SCHED280;
    }
    if ((G24_SCHED280 - G30_M->unk58 < 0xF) && (st->unk0 == 0)) {
        G30_M->unk88->unkC0 = D_80750338;
        G30_M->unk58 = G24_SCHED280 - 0x1E;
        func_80614E78(D_807FBB40, 0x7C);
        if (D_807FBB40->unk58 == 2) {
            func_80614EBC(G30_M->unk88, 0x294);
        } else {
            func_80614EBC(G30_M->unk88, 0x293);
        }
    }
}

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void func_8061C2F0(void *, f32, f32, f32, f32, f32, f32, s32);
void func_8061C6A8(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);

void func_806E918C(void) {
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
    if (!(D_807FD580->unk1F0 & 0x10000000)) {
        if ((D_807FD63A[D_807FC929].unk0 & 0x10) && (G29_PAR->unk154 == 7)) {
            actorGetNodePos(G30_M->unk88, 3, &x1, &y1, &z1);
            actorGetNodePos(G30_M->unk88, 4, &x2, &y2, &z2);
            func_8061C2F0(G30_M->unk104, x2, y2 + 8.0f, z2, (x2 - x1) + x2, (y2 - y1) + y2 + 5.0f, (z2 - z1) + z2, 1);
            D_807FD580->unk1F0 |= 2;
            D_807FBB40->unk60 |= 0x400;
        } else {
            if (D_807FD580->unk1F0 & 2) {
                D_807FD580->unk1F0 &= ~2;
                func_8061C6A8(G30_M->unk104, G30_M->unk88, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
                if (G29_PAR->unk154 == 7) {
                    func_80614E78(D_807FBB40, 0x84);
                }
            }
            D_807FBB40->unk60 &= ~0x400;
        }
    }
}

void func_806E9388(void) {
    if (G30_PAD(D_807FD63C, u16) & 0x4000) {
        G29_PAR->unk154 = 0x80;
        G29_PAR->unk155 = 0;
        func_80614EBC(D_807FBB40, 0x316);
    }
}

void func_806E93F8(void) {
    if (G30_PAD(D_807FD63C, u16) & 0x4000) {
        G29_PAR->unk154 = 0x81;
        G29_PAR->unk155 = 0;
        func_80614EBC(D_807FBB40, 0x316);
    }
}

void func_806E9468(void) {
    if (G30_PAD(D_807FD63C, u16) & 0xA000) {
        G30_M->unk12 = D_807539EC[D_807FD584];
        G30_M->unk14 = D_807FBB40->unkE6;
        G30_M->unk10 = D_807539DC[D_807FD584];
        G29_PAR->unk154 = 0x7F;
        G29_PAR->unk155 = 0;
        G29_PAR->unk155 = 1;
        if (0.0f < G30_A->unkC0) {
            G30_A->unkC0 = 0.0f;
        }
        func_80614EBC(D_807FBB40, 0x318);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x10, 0xFF, 0x7F, 1);
    }
}

extern s16 D_8075388C[];
extern s16 D_807538C8[];
void n_alSndpDeallocate(s32);
void func_806CA2AC(void);

s32 func_806E9580(void) {
    f32 diff;
    f32 lim;
    f32 t;
    u8 ret;
    s32 n;

    ret = 0;
    G30_M->unk24 = 0;
    n = 0x1E;
    if (D_807FBB40->unk6A & 4) {
        t = G30_A->unkC0;
        if (t <= 0.0f) {
            if (-150.0f < t) {
                G30_A->unkC0 = t;
            } else {
                G30_A->unkC0 = -150.0f;
            }
            diff = G30_A->unkAC - G30_A->unk80;
            if (*((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x2C0) == 2) {
                n = 0x3C;
            }
            if (((f32)n < diff) && func_806E770C()) {
                func_806EB0C0(0x3E, 0, D_807FC929);
                func_806CA2AC();
            } else if (D_807FBB40->unk6A & 1) {
                if (*((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x2C0) == 1) {
                    lim = D_8075386C[D_807FD584];
                } else {
                    lim = D_8075389C[D_807FD584];
                }
                if (lim < diff) {
                    func_806EB0C0(0x3D, 0, D_807FC929);
                    ret = 1;
                    func_806CA2AC();
                }
            } else {
                if (*((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x2C0) == 1) {
                    lim = D_8075388C[D_807FD584];
                } else {
                    lim = D_807538C8[D_807FD584];
                }
                if (lim < G30_A->unkB4 + diff) {
                    func_806EB0C0(0x3D, 0, D_807FC929);
                    func_80614EBC(D_807FBB40, 0);
                    if (G30_M->unkC4) {
                        n_alSndpDeallocate(G30_M->unkC4);
                    }
                    ret = 1;
                    func_806CA2AC();
                }
            }
        }
    }
    return ret;
}

void func_806E9804(arg0) s16 arg0; {
    if (func_8073110C(0x179, 0)) {
        if (G30_PAD(D_807FD63C, u16) & 4) {
            func_806E9D1C(arg0, 0xB, 0);
        }
    }
}

void func_806E9874(void) {
    if (!(D_807FBB64 & 2) && (D_8074E77C[D_807FC929] < 5)) {
        func_806E9804(6);
        *(f32 *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + 0x27C) = 45.0f;
    }
}

void func_806E98F8(void) {
    if ((D_807FD610[D_807FC929].unk2A & 0x2000) && ((D_807FD610[D_807FC929].unk2C & 0xC) == 4)) {
        func_806E9874();
    }
}

void func_806E9964(arg0) Struct807FD580 *arg0; {
    Actor *a;
    s32 flag;

    a = D_807FBB40;
    flag = (a->unk154 == 5) || (a->unk154 == 0x65);
    if ((D_807FD610[D_807FC929].unk2A & 0x2000) && (D_807FD610[D_807FC929].unk2C & 4)) {
        if (flag) {
            func_806E9D1C(7, 3, 0);
        } else {
            func_806E9D1C(5, 3, 0);
        }
    } else {
        func_806EAB44(a, (u8)flag);
    }
    func_806F8D58(6, 1);
    func_806F8D58(0xC, 1);
    arg0->unk1F0 &= ~0x8000;
}

void func_806E9A5C(void) {
    if (!(D_807FD580->unk1F0 & 0x8000) && ((G30_PAD(D_807FD63C, u16) & 0xC) == 8)) {
        func_806E9964(D_807FD580);
    }
}

void func_806E9ACC(void) {
    if (!(D_807FD580->unk1F0 & 0x8000) && ((G30_PAD(D_807FD63C, u16) & 0xC) == 4)) {
        func_806E9964(D_807FD580);
    }
}

void func_806E9B3C(void) {
    if (!(D_807FD580->unk1F0 & 0x8000) && (G30_PAD(D_807FD63C, u16) & 4)) {
        func_806E9964(D_807FD580);
    }
}

typedef struct G30Cam {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
} G30Cam;

void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_806E9BA8(arg0) s32 arg0; {
    G30Cam *cam;

    if (G30_PAD(D_807FD63C, u16) & 0x4000) {
        if (!(D_807FD580->unk1F0 & 0x8000)) {
            if (func_806F8AD4(6, D_807FC929) > 0) {
                func_80609140(0x263, 0x7FFF, 63.0f, 1.0f, 0xA, 0);
                G29_PAR->unk154 = arg0;
                G29_PAR->unk155 = 0;
                func_806F91B4(6, D_807FC929, -1);
                cam = (G30Cam *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0);
                lightAdd(cam->unk210, cam->unk214, cam->unk218, cam->unk228, cam->unk22C, cam->unk230, 0.0f, 1, 0xFF, 0xFF, 0xFF);
            }
        }
    }
}

void func_806E9CDC(void) {
    func_806E9BA8(0x64);
}

void func_806E9CFC(void) {
    func_806E9BA8(0x65);
}

s32 func_806EB178();

s32 func_806E9D1C(arg0, arg1, arg2) s16 arg0; u8 arg1; u8 arg2; {
    if (((D_807FC928 < 2) || (D_80750AB8 != 1)) && (D_807FD888 == 0.0f) && (G30_A->unkE0 == 0.0f)) {
        func_806EB178(D_807FC929, arg1, arg2, 0);
        func_806EB0C0(arg0, 0, D_807FC929);
        G30_A->unkB8 = 0.0f;
        return 1;
    }
    return 0;
}

typedef struct G30Player {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ struct G30Link *unk104;
} G30Player;

typedef struct G30Link {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ struct G30State2 *unk174;
} G30Link;

typedef struct G30State2 {
    /* 0x00 */ u8 pad0[0xAC];
    /* 0xAC */ u32 unkAC;
} G30State2;

void func_806E9DE0(void) {
    G30State2 *state;
    s32 act;

    if (G30_PAD(D_807FD63C, u16) & 8) {
        state = ((G30Player *)D_807FD580)->unk104->unk174;
        if ((func_80714608(0) == 0) && !(state->unkAC & 0x80000000)) {
            act = G29_PAR->unk154;
            if (((act == 0x5D || act == 0x5E || act == 0x62) && !(D_807FBB64 & 0x80000000)) || act == 0x4E || act == 0x4F ||
                act == 0xD || act == 0xC) {
                func_806E9D1C(5, 3, 0);
            }
        }
    }
}

typedef struct G31State {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 pad0A[0xA2];
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ s16 unkBC;
    /* 0xBE */ u8 padBE[0x30];
    /* 0xEE */ u8 unkEE;
    /* 0xEF */ u8 unkEF;
    /* 0xF0 */ u8 unkF0;
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[2];
    /* 0xF6 */ u8 unkF6;
    /* 0xF7 */ u8 padF7[5];
    /* 0xFC */ u8 unkFC;
} G31State;

typedef struct G31Player {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ struct G31Link *unk104;
} G31Player;

typedef struct G31Link {
    /* 0x000 */ u8 pad0[0xB4];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ u8 padB8[0xBC];
    /* 0x174 */ G31State *unk174;
} G31Link;

#define G31_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))
#define G31_PLAYER ((G31Player *)D_807FD580)

s32 func_80714608();

void func_806E9ECC(void) {
    G31State *state;

    if ((G31_PAD(D_807FD63C, u16) & 2) && (D_807FBB40->unk6A & 1)) {
        state = G31_PLAYER->unk104->unk174;
        if ((func_80714608(0) == 0) && !(state->unkAC & 0x80000000) && !(D_807FBB64 & 0x80000000)) {
            func_806E9D1C(5, 3, 1);
        }
    }
}

void func_806E9F8C(void) {
    G31State *state;

    if ((G31_PAD(D_807FD63C, u16) & 8) && (D_807FBB40->unk6A & 1)) {
        state = G31_PLAYER->unk104->unk174;
        if ((func_80714608(0) == 0) && !(state->unkAC & 0x80000000) && !(D_807FBB64 & 0x80000000)) {
            func_806E9D1C(5, 3, 1);
        }
    }
}

void func_806EA04C(void) {
    if (G31_PAD(D_807FD63C, u16) & 8) {
        func_806E9D1C(7, 3, 0);
    }
}

void func_8062217C();

void func_806EA0A4(void) {
    G31State *state;
    u8 max;
    s32 cur;

    state = G31_PLAYER->unk104->unk174;
    if ((D_807FBB64 & 1) && !(D_807FBB68 & 2)) {
        max = 2;
    } else {
        max = 3;
    }
    cur = state->unkEF;
    if ((cur != 0) && ((G31_PAD(D_807FD63C, u16) & 0xC) == 4) && ((state->unkEE == max) || (state->unkFC == 0))) {
        state->unkF0 = cur;
        if (cur < max) {
            state->unkEF = cur + 1;
        } else {
            state->unkEF = 1;
        }
        func_8062217C(G31_PLAYER->unk104, state->unkEF, &D_807FD580);
        state->unkEE = state->unkEF;
        if ((state->unkEF != state->unkF0) && ((state->unk8 == 0) || (state->unk8 >= 0x96)) && (state->unkF3 != 2)) {
            func_80609140(0x27, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        state->unkF1 = 0xB;
        state->unkF6 = 0xF;
    }
}

void func_806EA200(void) {
    G31State *state;

    state = G31_PLAYER->unk104->unk174;
    if ((G31_PAD(D_807FD63C, u16) & 2) && (state->unkF1 < 3)) {
        state->unkB0 -= 0x2D;
        state->unkF1 = 0xB;
    }
}

void func_806EA26C(void) {
    G31State *state;

    state = G31_PLAYER->unk104->unk174;
    if ((G31_PAD(D_807FD63C, u16) & 1) && (state->unkF1 < 3)) {
        state->unkB0 += 0x2D;
        state->unkF1 = 0xB;
    }
}


f32 func_806EA2D8(void) {
    return (G31_PAD(D_807FD63A, u16) & 0x2000) ? 0.2 : 1.0;
}

typedef struct G31Cam {
    /* 0x000 */ u8 pad0[0x27C];
    /* 0x27C */ f32 unk27C;
    /* 0x280 */ u8 pad280[0x70];
} G31Cam;

extern G31Cam *D_807FC924;

void func_806EA334(void) {
    f32 limit;
    f32 next;
    G31Cam *cam;
    s32 buttons;

    buttons = G31_PAD(D_807FD63A, u16);
    if (!(buttons & 0x2000) && !(buttons & 2) && (D_807FBB40->unk154 == 2)) {
        limit = (D_8076A0A8 == 0x22) ? 15.0 : 13.0;
        cam = (G31Cam *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0);
        next = cam->unk27C - 1.5f;
        if (limit < next) {
            cam->unk27C = next;
            sfxPlayActorSound(D_807FBB40, 0x1F0, 0, 0, 0, 0xFF, 1.0f, -1);
            return;
        }
        cam->unk27C = limit;
        sfxStopSlotSound(D_807FBB40, 0);
    }
}

void func_806EA460(void) {
    f32 next;
    G31Cam *cam;
    s32 buttons;

    buttons = G31_PAD(D_807FD63A, u16);
    if (!(buttons & 0x2000) && !(buttons & 1) && (D_807FBB40->unk154 == 2)) {
        cam = (G31Cam *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0);
        next = cam->unk27C + 1.5f;
        if (next < 45.0) {
            cam->unk27C = next;
            sfxPlayActorSound(D_807FBB40, 0x1F0, 0, 0, 0, 0xFF, 1.0f, -1);
            return;
        }
        cam->unk27C = 45.0f;
        sfxStopSlotSound(D_807FBB40, 0);
    }
}

void func_806EA568(void) {
    u16 buttons;

    buttons = G31_PAD(D_807FD63A, u16) & 3;
    if ((buttons != 2) && (buttons != 1)) {
        sfxStopSlotSound(D_807FBB40, 0);
    }
}

s32 func_806E9580();

void func_806EA5CC(void) {
    if (func_806E9580()) {
        func_806EAB44(D_807FBB40, 1);
    }
}

void func_806EA600(void) {
    func_806EA568();
    func_806EA5CC();
}

void func_806EA628(void) {
    G31State *state;
    s16 *angle;
    f32 *dist;
    s32 unused;

    if (!(D_807FD580->unk1F0 & 0x8000)) {
        state = G31_PLAYER->unk104->unk174;
        angle = &state->unkB2;
        *angle = (f64)*angle - (((f64)func_806EA2D8() * ((f64)G31_PAD(D_807FD63E, s8) * 0.08) * 4096.0) / 360.0);
        dist = &state->unkB8;
        *dist = ((f64)G31_PAD(D_807FD63F, s8) * 0.04 * func_806EA2D8()) + (f64)*dist;
        *angle &= 0xFFF;
        if ((f32)(state->unkBC + 0x32) < *dist) {
            *dist = state->unkBC + 0x32;
        } else if (*dist < (f32)(state->unkBC - 0x50)) {
            *dist = state->unkBC - 0x50;
        }
        G31_PLAYER->unk104->unkB4 = *dist;
        D_807FBB40->unkE6 = (state->unkB2 + 0x800) & 0xFFF;
    }
}

void func_806EA7E8(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC000) == 0x8000) {
        func_806EAB44(D_807FBB40, 0);
    }
}

void func_806EA844(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC000) == 0x4000) {
        func_806EAB44(D_807FBB40, 0);
    }
}

void func_806EA8A0(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC000) == 0x8000) {
        func_806EAB44(D_807FBB40, 1);
    }
}

void func_806EA8FC(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC000) == 0x4000) {
        func_806EAB44(D_807FBB40, 1);
    }
}

void func_806EA958(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC) == 8) {
        func_806EAB44(D_807FBB40, 0);
    }
}

void func_806E9874();

void func_806EA9B4(void) {
    if ((D_807FD610[D_807FC929].unk2A & 0x2000) && (D_807FD610[D_807FC929].unk2C & 4)) {
        func_806E9874();
        return;
    }
    if ((D_807FD610[D_807FC929].unk2C & 0xC) == 4) {
        func_806EAB44(D_807FBB40, 0);
    }
}

void func_806EAA44(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC) == 8) {
        func_806EAB44(D_807FBB40, 1);
    }
}

typedef struct G32Act {
    /* 0x000 */ u8 pad0[0x80];
    /* 0x080 */ f32 unk80;
    /* 0x084 */ u8 pad84[0x28];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[8];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x6C];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ struct G32State *unk174;
} G32Act;

typedef struct G32State {
    /* 0x000 */ u8 pad0[0x8C];
    /* 0x08C */ u8 unk8C;
    /* 0x08D */ u8 pad8D[0x77];
    /* 0x104 */ void *unk104;
    /* 0x108 */ u8 pad108[0xEC];
    /* 0x1F4 */ u32 unk1F4;
} G32State;

void func_806EAAA0(void) {
    if ((D_807FD610[D_807FC929].unk2A & 0x2000) && (D_807FD610[D_807FC929].unk2C & 4) && !(D_807FBB64 & 2)) {
        func_806E9804(8);
        return;
    }
    if ((D_807FD610[D_807FC929].unk2C & 0xC) == 4) {
        func_806EAB44(D_807FBB40, 1);
    }
}

void func_806CFECC(void);
void func_806F0D68(void *);
s16 func_8062773C(void *);

void func_806EAB44(arg0, arg1)
G32Act *arg0;
u8 arg1;
{
    G32State *state;

    state = arg0->unk174;
    if (!(state->unk1F4 & 0x10)) {
        func_80609140(0x27, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
    if (arg1) {
        if (D_8074E77C[D_807FC929] == 7) {
            if (arg0->unkAC - arg0->unk80 < 20.0f) {
                arg0->unk154 = 0x7E;
                arg0->unk155 = 0;
            } else {
                arg0->unk154 = 0x7F;
                arg0->unk155 = 0;
            }
        } else {
            arg0->unk154 = 0x4F;
            arg0->unk155 = 3;
        }
    } else {
        arg0->unk154 = 1;
        arg0->unk155 = 0;
        func_806CFF9C((Actor *)arg0);
        if (arg0->unk154 == 0xC) {
            arg0->unk155 = 0xA;
        }
    }
    if (state->unk8C) {
        func_806F0D68(arg0);
    } else {
        func_806F0C18(arg0);
    }
    arg0->unkB8 = 0.0f;
    arg0->unkE6 = func_8062773C(state->unk104);
}

typedef struct G32Inner {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ u8 unkE;
} G32Inner;

typedef struct G32Mid {
    /* 0x000 */ u8 pad0[0x154];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ G32Inner *unk178;
} G32Mid;

typedef struct G32Plr {
    /* 0x000 */ u8 pad0[0x3C];
    /* 0x03C */ s16 unk3C;
    /* 0x03E */ u8 pad3E[0x12];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[6];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0x2C];
    /* 0x088 */ G32Mid *unk88;
    /* 0x08C */ u8 pad8C[0x7C];
    /* 0x108 */ f32 unk108;
    /* 0x10C */ u8 pad10C[0xF4];
    /* 0x200 */ s16 unk200;
} G32Plr;

#define G32_P ((G32Plr *)D_807FD580)

void func_806EAC8C(void) {
    G32Inner *inner;

    inner = G32_P->unk88->unk178;
    if (inner->unkE == 5) {
        inner->unkE = 10;
    }
}

void func_806EACBC(void) {
    G32Inner *inner;

    inner = G32_P->unk88->unk178;
    if (inner->unkE == 5) {
        inner->unkE = 0xF;
    }
}

void func_806EACEC(void) {
    if (G31_PAD(D_807FD63C, u16) & 0x8000) {
        G32_P->unk58 = D_80767CC0;
    }
    if (D_807FBB40->unk6A & 1) {
        if ((D_80767CC0 - G32_P->unk58) < 0xF) {
            func_806CFECC();
            ((G32Act *)D_807FBB40)->unkC0 = D_807535CC[D_807FD584];
            G32_P->unk50 = 0;
            G32_P->unk3C = 0;
            G32_P->unk58 = D_80767CC0 - 0x1E;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x309, 0xFF, 0x7F, 0);
        }
    }
}

void func_806EAE04(void) {
    G32Mid *mid;

    mid = G32_P->unk88;
    if (mid->unk154 == 0) {
        if (G31_PAD(D_807FD63C, u16) & 0x4000) {
            mid->unk154 = 1;
        }
    }
}

void func_806EAE60(void) {
    G21Table *pad;
    s32 v;

    pad = &D_807FD610[D_807FC929];
    if ((pad->unk2E >= 0x29) || (pad->unk2F >= 0x29)) {
        if (G32_P->unk108 != 0.0f) {
            G32_P->unk108 = 0.0f;
            v = G32_P->unk200 - 5;
            if (v <= 0) {
                G32_P->unk200 = 1;
            } else {
                G32_P->unk200 = v;
            }
            return;
        }
    }
    if ((pad->unk2E < -0x28) || (pad->unk2F < -0x28)) {
        if (G32_P->unk108 == 0.0f) {
            G32_P->unk108 = 1.0f;
            v = G32_P->unk200 - 5;
            if (v <= 0) {
                G32_P->unk200 = 1;
            } else {
                G32_P->unk200 = v;
            }
        }
    }
}

void func_806EAF6C(void) {
    G32Mid *mid;

    mid = G32_P->unk88;
    if (G31_PAD(D_807FD63C, u16) & 0x8000) {
        switch (mid->unk154) {
            case 2:
                mid->unk154 = 4;
                mid->unk155 = 0;
                break;
            case 5:
                mid->unk155++;
                break;
        }
    }
}

void func_806EAFEC(void) {
}

void func_806EAFF4(void) {
    if (G31_PAD(D_807FD63A, u16) & 0x2000) {
        ((G32Act *)D_807FBB40)->unkC0 = 0.0f;
    } else {
        ((G32Act *)D_807FBB40)->unkC0 = 120.0f;
    }
}

void func_806EB058(void) {
    if (G31_PAD(D_807FD63A, u16) & 0xC) {
        ((G32Act *)D_807FBB40)->unkC0 = 0.0f;
    } else {
        ((G32Act *)D_807FBB40)->unkC0 = -120.0f;
    }
}
