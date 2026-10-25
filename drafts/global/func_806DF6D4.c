// func_806DF6D4 (src/global/E4090.c): Stage 6: ~21 insn reg diffs left (Q ptr a1 vs a3, loop base a3 vs a1, mfc1 v0 vs v1). Permuter-found dead tests: if(LE40_E.unk2E){}+if(D_807FC929){} in loop, (i ^ 0) loop cond, ang=-80 before clamp, unk20[D_807FC929*0], hi temp for mul.s order.
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
