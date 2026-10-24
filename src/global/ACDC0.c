#include "common.h"
#include "actor.h"

typedef struct ACDC0TextEntry {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ char unk11[7];
} ACDC0TextEntry; // size = 0x18

typedef struct ACDC0HudEntry {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 unk8[2];
    /* 0x0C */ s16 unkC[2];
    /* 0x10 */ u8 pad10[2];
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 pad13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
} ACDC0HudEntry;

typedef struct ACDC0TextObj {
    /* 0x000 */ u8 pad0[0x340];
    /* 0x340 */ f32 unk340;
    /* 0x344 */ f32 unk344;
    /* 0x348 */ u8 pad348[0x18];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ f32 unk364;
    /* 0x368 */ u8 pad368[2];
    /* 0x36A */ u8 unk36A;
    /* 0x36B */ u8 unk36B;
    /* 0x36C */ u8 unk36C;
    /* 0x36D */ u8 pad36D[0x17];
    /* 0x384 */ f32 *unk384;
} ACDC0TextObj;

typedef struct ACDC0CountEntry {
    /* 0x00 */ u8 pad0[0x42];
    /* 0x42 */ u16 unk42[14];
} ACDC0CountEntry; // size = 0x5E

typedef struct ACDC0Axis {
    u8 pad0[3];
    s8 unk3;
} ACDC0Axis;

typedef struct ACDC0Player {
    u8 pad0[0x294];
    ACDC0Axis *unk294;
    u16 *unk298;
    u8 pad29C[0x2F0 - 0x29C];
} ACDC0Player;

#define ACDC0_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern Gfx D_1000118;
extern Mtx D_2000180;
extern Mtx D_20000C0;

extern s8 D_80750560[9];
extern ACDC0TextEntry *D_807FC7F0[2];
extern s8 D_807FC7F8[2];
extern u32 D_807FBB60;
extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB4C;
extern char **D_807FC7E0;
extern void **D_807FC7E8;
extern s8 D_807FC80F;
extern u8 D_807FC810;
extern f32 D_807FC808;
extern s8 D_8075052C;
extern s8 D_807505D0;
extern s16 D_807FC828;
extern s16 D_807FC82A;
extern s16 D_807FC82C;
extern s16 D_807FC82E;
extern s16 D_807FC830;
extern s16 D_807FC832;
extern s16 D_807FC834;
extern s16 D_807FC836;
extern s16 D_807FC838;
extern ACDC0CountEntry D_807FC950[];
extern ACDC0CountEntry D_807FCB26[];
extern s16 D_80744710[];
extern s16 D_80744720[];
extern s16 D_807505B2[];
extern s16 D_807505B8[];
extern s16 D_807505CC[];
extern u8 D_80750530;
extern u8 D_80750531[];
extern u16 D_807ECD58;
extern s32 D_8076A0A8;
extern u8 D_807505F8[];
extern u8 D_807505F9[];
extern s8 D_807FC80E;
extern s8 D_807FC8B9;
extern ACDC0Player *D_807FC924;
extern s8 D_8076A105;

void heapFree(void *);
void heapFreeDeferred(void *);
void *func_80610FE8(s32);
s32 _sprintf(char *, const char *, ...);
Gfx *func_806FC530(Gfx *, s32, s16, s32, void *, s32);
s32 func_806FBD5C();
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *func_80703374(Gfx *, s32, s32, s32, s32);
Gfx *func_806A921C(Gfx *);
Gfx *func_806ABB98(Gfx *, s16, s16, f32, void *);
void func_806AA304(ACDC0HudEntry *, s32, s32);
void func_806AC07C();
void func_80714998(u8);
void func_8071495C(void);
void func_807149FC(s32);
void func_80714950(void *);
void func_8071498C(void (*)());
void func_80714A28(s32);
ACDC0TextObj *func_80714CC0(s32, f32, f32, f32, f32);
s32 func_806FACE8(s32);
f32 func_806119FC(void);
f32 sqrtf(f32);
void func_80609140(s32, s32, f32, f32, s32, s32);
s32 func_8073110C(s16, s32);
s32 func_80731AA8(s32, s32, s32);
void actorSpawn(s32, s32);
void actorDespawn(Actor *);
char *func_8070E750(s32, s32, s32);
void func_8061CC40(s32, s32, s32);
void func_80724994(s32, s32, s32, s32, s32);
void func_805FF378(s32, s32);
void func_805FF544(void);
void func_805FF898(void);
void func_806291B4(s32);
void func_80714638(void);
void renderCallbacksRegister(void *, void *, s32);

s32 func_806A80C0(s8 arg0) {
    s32 i;

    if (arg0 == D_80750560[0]) {
        return 0;
    }
    for (i = 1; i < 9; i++) {
        if (arg0 == D_80750560[i]) {
            return i;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806A8158.s")

void func_806A9124(void) {
    s32 i;
    u8 *sub;

    sub = D_807FBB4C->unk174;
    D_807FBB60 |= 0x40;
    if (!(*(s32 *)(sub + 0x1F0) & 0x20000000)) {
        D_807FBB60 |= 0x10030;
    }
    heapFree(D_807FC7F0[0]);
    D_807FC7F8[1] = D_807FC7F8[0] = (s32)(D_807FC7F0[1] = D_807FC7F0[0] = 0);
    for (i = 0; i < 0x6C; i += 4) {
        heapFreeDeferred(*(void **)((u8 *)D_807FC7E0 + i));
    }
    heapFreeDeferred(D_807FC7E0);
    for (i = 0; i < 0x24; i += 4) {
        heapFreeDeferred(*(void **)((u8 *)D_807FC7E8 + i));
    }
    heapFreeDeferred(D_807FC7E8);
}

Gfx *func_806A921C(Gfx *dl) {
    ACDC0_WRITE_GFX(dl++, 0xDE000000, (u32)&D_1000118);
    ACDC0_WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
    ACDC0_WRITE_GFX(dl++, 0xDA380007, (u32)&D_20000C0);
    ACDC0_WRITE_GFX(dl++, 0xE7000000, 0);
    ACDC0_WRITE_GFX(dl++, 0xFA000000, 0xFFFFFFFF);
    ACDC0_WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
    return dl;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA94.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AABC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AACC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AADC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806A92B4.s")

Gfx *func_806AA09C(s16 x, s16 y, s16 n1, s16 n2, Gfx *dl, s8 flag, f32 scale) {
    Mtx *mtx;
    s32 w;
    f32 m1[4][4];
    f32 m2[4][4];
    char buf1[8];
    char buf2[8];

    mtx = func_80610FE8(0x40);
    heapFreeDeferred(mtx);
    if (n1 >= 0x64) {
        w = 0x7C;
    } else if (n1 >= 10) {
        w = 0x5C;
    } else {
        w = 0x3C;
    }
    if (flag != 0) {
        x = (f32)x - (f32)w * scale;
    }
    guScaleF(m1, scale, scale, 1.0f);
    guTranslateF(m2, x, y, 0.0f);
    guMtxCatF(m1, m2, m1);
    guMtxF2L(m1, mtx);
    ACDC0_WRITE_GFX(dl++, 0xDA380002, (u32)mtx);
    _sprintf(buf1, "%d", n1);
    _sprintf(buf2, "%d", n2);
    dl = func_806FC530(func_806FC530(dl, 1, 0, -0x28, buf1, 0x80), 1, w, 0x28, buf2, 0);
    ACDC0_WRITE_GFX(dl++, 0xD8380002, 0x40);
    dl->words.w0 = 0xE7000000;
    dl->words.w1 = 0;
    dl++;
    return func_8068C5A8(dl, 0x9F, 0, 2, 0x20, 0x20, (s32)((f32)x + (f32)(w - 0x10) * scale), (s32)((f32)y + 45.0f * scale), scale * 3.125, scale * 3.125, 0, 0.0f);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806AA304.s")

void func_806AB4EC(ACDC0HudEntry *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, u8 arg5, s32 arg6) {
    ACDC0TextObj *obj;
    f32 *buf;
    f32 dx;
    f32 dy;
    f32 len;
    f32 fy;

    func_80714998(arg5);
    func_8071495C();
    func_807149FC(-1);
    func_80714950(arg0);
    func_8071498C(func_806AC07C);
    func_80714A28(0x101);
    if (arg1 < 0) {
        fy = arg2;
        obj = func_80714CC0(arg1, arg4, fy, (f32)arg3, -10.0f);
    } else {
        fy = arg2;
        obj = func_80714CC0(func_806FACE8(arg1), arg4, fy, (f32)arg3, -10.0f);
    }
    arg1 = 7;
    if (arg6 == 6) {
        arg1 = 10;
    }
    buf = func_80610FE8(arg1 * 4);
    obj->unk384 = buf;
    if (arg6 == 9) {
        arg6 = 7;
        obj->unk360 = -obj->unk360;
    }
    buf[0] = arg6;
    buf[1] = arg0->unk15;
    buf[2] = obj->unk340;
    buf[3] = obj->unk344;
    switch (arg6) {
    case 1:
    case 2:
    case 7:
    case 13:
        dx = 640.0f - buf[2];
        dy = 480.0f - buf[3];
        len = sqrtf(dx * dx + dy * dy);
        buf[4] = -(dx / len) * (1040.0f - len);
        buf[5] = -(dy / len) * (1040.0f - len);
        buf[6] = obj->unk364;
        if (arg6 == 13) {
            buf[0] = 2.0f;
            obj->unk36C = 0;
            obj->unk36B = 0;
            obj->unk36A = 0xFF;
        }
        break;
    case 6:
        buf[4] = 0.0f;
        buf[5] = 0.0f;
        buf[6] = 0.0f;
        buf[7] = 0.0f;
        buf[8] = func_806119FC() * 4096.0f;
        if (arg2 < 0xA0) {
            obj->unk360 = -obj->unk360;
        }
        buf[9] = 0.0f;
        break;
    case 10:
        buf[2] = fy;
        break;
    case 14:
        buf[0] = 3.0f;
        obj->unk36C = 0;
        obj->unk36B = 0;
        obj->unk36A = 0xFF;
    default:
        buf[4] = arg4;
        buf[5] = 0.0f;
        break;
    }
    if (D_807FC80F == 0) {
        obj->unk36A = 0x64;
        obj->unk36B = 0x64;
        obj->unk36C = 0x64;
    }
    D_807FC80F = 1;
}

void func_806AB808(ACDC0HudEntry *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 pad;
    s32 idx;
    s32 pad2;
    s32 pad3;
    s32 i;
    f32 len;
    s32 pad4;
    ACDC0TextEntry *list;
    s8 flag;
    u8 buf[11];

    flag = 0;
    if (arg7 & 0x80) {
        flag = 1;
        arg7 &= ~0x80;
    }
    switch (arg7) {
    case 1:
        _sprintf((char *)buf, "%02d", arg5);
        break;
    case 2:
        _sprintf((char *)buf, "%d", arg5);
        arg3 -= func_806FBD5C(1, buf) >> 1;
        break;
    default:
        _sprintf((char *)buf, "%d", arg5);
        break;
    }
    if (flag != 0) {
        arg3 -= func_806FBD5C(1, buf);
    }
    D_807FC810 = func_806FBD5C(1, buf);
    idx = D_807FC7F8[arg0->unk15];
    list = D_807FC7F0[arg0->unk15];
    len = sqrtf((640.0f - (f32)(arg1 * 4)) * (640.0f - (f32)(arg1 * 4)) + (480.0f - (f32)(arg2 * 4)) * (480.0f - (f32)(arg2 * 4)));
    list[idx].unk0 = -((640.0f - (f32)(arg1 * 4)) / len) * (1040.0f - len);
    list[idx].unk4 = -((480.0f - (f32)(arg2 * 4)) / len) * (1040.0f - len);
    list[idx].unk8 = arg1;
    list[idx].unkA = arg2;
    list[idx].unkC = arg3;
    list[idx].unkE = arg4;
    list[idx].unk10 = arg6;
    for (i = 0; buf[i] != 0; i++) {
        list[idx].unk11[i] = buf[i];
    }
    list[idx].unk11[i] = 0;
    D_807FC7F8[arg0->unk15]++;
}

Gfx *func_806ABA6C(Gfx *dl, ACDC0HudEntry *arg1, s32 arg2) {
    u8 padHi[0xC];
    s32 col;
    void *tex;
    u8 pad[0x1C];
    s32 y2;
    s32 y;

    y = arg1->unkC[arg2] * 4;
    tex = D_807FC7E8[D_80750560[arg1->unk8[arg2]]];
    if (arg1->unk12 == 1) {
        col = arg1->unk14;
    } else {
        col = 5;
    }
    ACDC0_WRITE_GFX(dl++, 0xFA000000, 0xFFFFFFFF);
    y2 = y + 0x40;
    dl = func_806ABB98(func_806ABB98(dl, 0x280, y2, 0.7f, tex), 0x280, y2 + 0x38, 0.5f, D_807FC7E0[col + 9]);
    D_807FC808 = (f32)func_806FBD5C(1, tex) * 1.4;
    return dl;
}

Gfx *func_806ABB98(Gfx *dl, s16 arg1, s16 arg2, f32 scale, void *arg4) {
    f32 m1[4][4];
    f32 m2[4][4];
    Mtx *mtx;

    mtx = func_80610FE8(0x40);
    heapFreeDeferred(mtx);
    guScaleF(m1, scale, scale, 1.0f);
    guTranslateF(m2, arg1, arg2, 0.0f);
    guMtxCatF(m1, m2, m1);
    guMtxF2L(m1, mtx);
    ACDC0_WRITE_GFX(dl++, 0xDA380002, (u32)mtx);
    dl = func_806FC530(dl, 1, 0, 0, arg4, 0x80);
    ACDC0_WRITE_GFX(dl++, 0xD8380002, 0x40);
    return dl;
}

#ifdef NON_MATCHING
s32 func_806ABC94(ACDC0HudEntry *arg0, s32 arg1, s32 arg2) {
    s32 dir;
    s32 idx;
    s32 v;
    s32 cur;
    s32 d;
    s32 idx2;

    if (arg1 == 0) {
        dir = 0;
        if (arg2 & 8) {
            dir = 1;
        } else if (arg2 & 4) {
            dir = -1;
        }
        if (dir != 0) {
            idx = arg0->unk15;
            cur = arg0->unk8[idx];
            v = cur + dir;
            if (dir) {
            }
            if (v < 0) {
                v = D_807505D0;
            }
            if (D_807505D0 < v) {
                v = 0;
            }
            if (v != cur) {
                arg0->unk15 = 1 - idx;
                arg0->unk8[arg0->unk15] = v;
                arg0->unkC[arg0->unk15] = dir * 0xFA;
                func_806AA304(arg0, 0, idx);
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
    if (arg1 != 0) {
        idx2 = arg0->unk15;
        d = arg0->unkC[idx2];
        if (d >= 0x15) {
            d = 0x14;
        }
        if (d < -0x14) {
            d = -0x14;
        }
        arg0->unkC[0] -= d;
        arg0->unkC[1] -= d;
        if (arg0->unkC[idx2] == 0) {
            arg0->unk8[1 - idx2] = arg0->unk8[idx2];
            d = arg0->unk15;
            arg1 = 0;
            D_807FC7F8[1 - d] = 0;
            func_80609140(0x97, 0x4650, 63.0f, 1.0f, 0, 0);
            D_8075052C = 3;
        }
    }
    return arg1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806ABC94.s")
#endif

#ifdef NON_MATCHING
void func_806ABE3C(void) {
    s16 *p;
    s16 *p0;
    s16 *q;
    ACDC0CountEntry *e;
    s32 n;
    s32 i;
    u8 *u;
    s32 k;
    s32 m;

    p0 = (s16 *)((u8 *)&D_807FC82A - 2);
    do {
        *p0++ = 0;
    } while (p0 < (s16 *)((u8 *)&D_807FC82A + 10));
    n = 0;
    e = D_807FC950;
    k = 0;
    do {
        n += e->unk42[0];
        n += e->unk42[1];
        for (i = 2; i < 14; i++) {
            n += D_807FC950[k].unk42[i];
        }
        e++;
        k++;
    } while (e < D_807FCB26);
    D_807FC828 = n;
    n = 0;
    p = D_80744710;
    do {
        if (func_8073110C(*p, 0) != 0) {
            n++;
        }
        p++;
    } while (p < D_80744720);
    D_807FC82C = n;
    D_807FC832 = func_80731AA8(0x24D, 0x14, 0);
    D_807FC82E = func_80731AA8(0x225, 0x28, 0);
    m = 0;
    p = D_807505B8;
    do {
        if (*p >= 0 && func_8073110C(*p, 0) != 0) {
            m++;
        }
        p++;
    } while (p < D_807505CC);
    D_807FC82A = m;
    D_807FC834 = func_8073110C(0x84, 0);
    D_807FC830 = func_8073110C(0x17B, 0);
    D_807FC836 = func_80731AA8(0x1FD, 0x28, 0);
    D_80750530 = 1;
    for (i = 0; i < 4; i++) {
        D_80750531[i] = func_8073110C(D_807505B2[i - 1], 0);
    }
    D_807FC838 = 1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806ABE3C.s")
#endif

Gfx *func_806AC048(Gfx *dl, Actor *actor) {
    return func_80703374(dl, 0, 0, 0, 0x46);
}

#ifdef NON_MATCHING
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
} L7_Item;

typedef struct {
    f32 unk0;
    f32 unk4;
    u8 pad8[4];
    s16 tbl[4];
    u8 pad14;
    s8 unk15;
} L7_Src;

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    u8 pad348[0x35C - 0x348];
    L7_Src *unk35C;
    f32 unk360;
    f32 unk364;
    u8 pad368[2];
    u8 unk36A;
    u8 unk36B;
    u8 unk36C;
    u8 unk36D;
    u8 pad36E[0x384 - 0x36E];
    L7_Item *unk384;
} L7_Hud;

f32 func_80612790(s16);
f32 func_80612794(s16);
extern f32 D_807FC840[];
extern f32 D_807FC868[];
extern f32 D_807FC890[];
extern u8 D_8075054C[][4];
extern s32 D_8076A064;

void func_806AC07C(L7_Hud *arg0, s8 *arg1) {
    L7_Src *src;
    L7_Item *item;
    f32 t;
    f32 sc;
    s32 type;
    s32 sp40;
    s32 tmp;
    s32 ang;
    s32 i;
    s16 five;

    src = arg0->unk35C;
    if (arg0->unk384 != NULL) {
        t = src->unk0;
        item = arg0->unk384;
        sp40 = (f64)src->tbl[(s32)item->unk4] * 4.0;
        type = (s32)arg0->unk384->unk0;
        switch (type) {
        case 0:
        case 4:
        case 11:
        case 12:
            t = 1.0 - src->unk0;
            if (t < 0.0f) {
                t = 0.0f;
            }
            if (t > 1.0f) {
                t = 1.0f;
            }
            arg0->unk36D = (s32)(t * 255.0f);
            if (type == 4) {
                arg0->unk360 = (f64)(item->unk10 * t) * 4.0;
                arg0->unk364 = arg0->unk360;
            }
            arg0->unk340 = item->unk8;
            arg0->unk344 = item->unkC + (f32)sp40;
            if (type == 0xB) {
                arg0->unk340 = 600.0 - D_807FC808;
            }
            if (type == 0xC) {
                arg0->unk340 = D_807FC808 + 680.0;
            }
            t = 0.0f;
            break;
        case 1:
        case 2:
        case 7:
            if (type != 1) {
                t += src->unk4;
            }
            if (type == 7) {
                ang = (D_8076A064 * 0x78) & 0xFFF;
                arg0->unk364 = (f64)func_80612794(ang) * 0.35 + item->unk18;
            }
            arg0->unk340 = item->unk10 * t + item->unk8;
            arg0->unk344 = item->unk14 * t + item->unkC + (f32)sp40;
            break;
        case 3:
        case 5:
        case 8:
        case 15:
            t = 1.0 - src->unk0;
            if (t < 0.0f) {
                t = 0.0f;
            }
            if (t > 1.0f) {
                t = 1.0f;
            }
            ang = (s32)((f64)item->unk8 * 0.25) - src->tbl[2];
            sc = 180.0f;
            if (type != 3) {
                sc = 240.0f;
            }
            sc = sc * t;
            arg0->unk360 = (f64)(item->unk10 * t) * 4.0;
            arg0->unk364 = arg0->unk360;
            t = 0.0;
            arg0->unk340 = (f64)(func_80612794(ang) * sc) + 640.0;
            arg0->unk344 = (480.0 - (f64)(func_80612790(ang) * sc)) + (f64)sp40;
            if (type == 8) {
                ang = (D_8076A064 * 0x78) & 0xFFF;
                arg0->unk344 = arg0->unk344 + func_80612794(ang) * 10.0f;
            }
            if (type == 0xF) {
                ang = (D_8076A064 * 0x78) & 0xFFF;
                arg0->unk364 = arg0->unk364 * (1.0 + (f64)func_80612794(ang) * 0.2);
            }
            if (type == 5 || type == 8 || type == 0xF) {
                i = 0xFF - (s32)(((f64)arg0->unk344 - 240.0) * 1.5);
                if (i < 0x5F) {
                    i = 0x5F;
                }
                if (i >= 0x100) {
                    i = 0xFF;
                }
                arg0->unk36A = i;
                arg0->unk36B = i;
                arg0->unk36C = i;
            }
            break;
        case 6:
            if ((item->unk14 - item->unk1C) * (item->unk14 - item->unk1C) + (item->unk10 - item->unk18) * (item->unk10 - item->unk18) < 400.0f) {
                item->unk24 = (f64)item->unk24 - 1.0;
                if ((f64)item->unk24 < 0.0) {
                    item->unk20 = (f64)item->unk20 + (1000.0 + (f64)func_806119FC() * 2000.0);
                    tmp = (s32)item->unk20 & 0xFFF;
                    item->unk20 = tmp;
                    sc = ((f64)func_806119FC() * 40.0 + 20.0) * 4.0;
                    item->unk18 = (f64)func_80612794(tmp) * ((f64)sc * 0.8);
                    item->unk1C = func_80612790(tmp) * sc;
                    if ((f64)func_806119FC() < 0.25) {
                        item->unk24 = (f64)func_806119FC() * 40.0 + 15.0;
                    } else {
                        item->unk24 = 0.0f;
                    }
                }
            }
            sc = (f64)(item->unk18 - item->unk10) * 0.1;
            if (sc < -8.0) {
                sc = -8.0f;
            }
            if (sc > 8.0) {
                sc = 8.0f;
            }
            item->unk10 = item->unk10 + sc;
            sc = (f64)(item->unk1C - item->unk14) * 0.1;
            if (sc < -8.0) {
                sc = -8.0f;
            }
            if (sc > 8.0) {
                sc = 8.0f;
            }
            item->unk14 = item->unk14 + sc;
            ang = (D_8076A064 * 0x78) & 0xFFF;
            arg0->unk340 = item->unk10 + item->unk8;
            sc = func_80612794(ang);
            arg0->unk344 = sc * 10.0f + (item->unkC + item->unk14 + (f32)sp40 + 960.0f * t);
            t = 0.0;
            break;
        case 10:
            i = (s32)item->unk8;
            arg0->unk340 = D_807FC840[i];
            arg0->unk344 = D_807FC868[i];
            arg0->unk360 = D_807FC890[i];
            arg0->unk364 = D_807FC890[i];
            D_807FC840[i] = -200.0f;
            D_807FC868[i] = -200.0f;
            five = 5;
            if (i >= five) {
                i -= five;
            }
            if (((s8 *)&D_80750530)[i] == 0) {
                arg0->unk36A = D_8075054C[i][0];
                arg0->unk36B = D_8075054C[i][1];
                arg0->unk36C = D_8075054C[i][2];
            }
            break;
        }
        if (src->unk15 != (s32)item->unk4 && (sp40 < -0x3C0 || sp40 >= 0x3C1)) {
            *arg1 = 1;
        }
        if (t > 1.0f || src->unk0 > 1.0f) {
            *arg1 = 1;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806AC07C.s")
#endif

Gfx *func_806ACA88(Gfx *dl, Actor *actor) {
    char buf[0x28];
    s32 remaining;
    s32 val;

    remaining = 0xFF - actor->unk128;
    if (remaining >= 9) {
        val = 8;
    } else {
        val = remaining;
    }
    actor->unk128 += val;
    if (actor->unk128 >= 0x80) {
        val = 0x7F;
    } else {
        val = actor->unk128;
    }
    dl = func_806A921C(func_80703374(dl, 0, 0, 0, val));
    gDPSetCombineLERP(dl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    dl->words.w0 = 0xFA000000;
    dl->words.w1 = (actor->unk128 & 0xFF) | 0xFFFFFF00;
    dl++;
    dl = func_806FC530(dl, 1, 0x168, 0x104, D_807FC7E0[0], 1);
    _sprintf(buf, "q %s", D_807FC7E0[1]);
    dl = func_806FC530(dl, 1, 0x208, 0x190, buf, 1);
    _sprintf(buf, "b %s", D_807FC7E0[2]);
    return func_806FC530(dl, 1, 0x208, 0x21C, buf, 1);
}

void func_806ACC00(u8 arg0) {
    actorSpawn(0x156, 0);
    D_807FBB44->unk15F = arg0;
    D_807FBB44->unk64 |= 2;
    D_807FBB60 |= 0x40001;
}

void func_806ACC64(void) {
    s16 i;

    D_807FBB60 |= 0x40;
    for (i = 0; i < 3; i++) {
        heapFreeDeferred(D_807FC7E0[i]);
    }
    heapFreeDeferred(D_807FC7E0);
    actorDespawn(D_807FBB40);
}

void func_806ACCE8(void) {
    s32 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk168 = 0x1E;
        D_807FBB40->unk128 = 0;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FC7E0 = func_80610FE8(0xC);
        for (i = 0; i < 3; i++) {
            D_807FC7E0[i] = func_8070E750(0x24, i + 0xF, 0);
        }
    }
    if (D_807FBB40->unk168 != 0) {
        D_807FBB40->unk168--;
    } else if (D_807FBB40->unk154 == 0) {
        if (D_807ECD58 & 0x8000) {
            switch (D_807FBB40->unk15F) {
                case 2:
                    func_8061CC40(0, 0x20, 1);
                    func_806ACC64();
                    break;
                case 3:
                case 4:
                    func_80724994(3, 7, 0x30, 0, 0);
                    func_806ACC64();
                    break;
                default:
                    func_805FF378(D_8076A0A8, 0);
                    break;
            }
            D_807FBB40->unk154 = 1;
        } else if (D_807ECD58 & 0x4000) {
            switch (D_807FBB40->unk15F) {
                case 3:
                case 4:
                    func_80724994(3, 7, 0x3C, 0, 0);
                case 2:
                    func_806ACC64();
                    break;
                case 1:
                    func_805FF544();
                    break;
                default:
                    func_805FF898();
                    break;
            }
            D_807FBB40->unk154 = 1;
        }
    }
    renderCallbacksRegister(func_806ACA88, D_807FBB40, 5);
}

Gfx *func_806ACF10(Gfx *dl, Actor *actor) {
    u8 sel;
    u8 c;

    dl = func_806A921C(dl);
    sel = actor->unk155[0] == 0;
    c = D_807505F8[sel];
    gDPSetPrimColor(dl++, 0, 0, c, c, c, 255);
    dl = func_806ABB98(dl, 0x280, 0x1B8, 0.7f, D_807FC7E0[0]);
    c = D_807505F9[-sel];
    gDPSetPrimColor(dl++, 0, 0, c, c, c, 255);
    return func_806ABB98(dl, 0x280, 0x208, 0.7f, D_807FC7E0[3]);
}

void func_806ACFFC(void) {
    s32 i;
    s32 off;
    u16 btn;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FC7E0 = func_80610FE8(0x10);
        i = 0;
        do {
            D_807FC7E0[i] = func_8070E750(0x24, i, 0);
            i++;
        } while (i != 4);
        D_807FBB60 &= ~0x10030;
        func_806291B4(7);
        D_807FC80E = 0;
        D_807FBB40->unk155[0] = 0;
    }
    i = D_807FC8B9;
    off = i * 0x2F0;
    if (((ACDC0Player *)((u8 *)D_807FC924 + off))->unk294->unk3 >= 0x33 || ((ACDC0Player *)((u8 *)D_807FC924 + off))->unk294->unk3 < -0x32) {
        if (!(D_807FC80E & 1)) {
            D_807FBB40->unk155[0] = 1 - D_807FBB40->unk155[0];
            D_807FC80E |= 1;
            func_80609140(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
    } else {
        D_807FC80E &= 0xFFFE;
    }
    btn = *((ACDC0Player *)((u8 *)D_807FC924 + off))->unk298;
    if (btn & 0x8000) {
        if (D_807FBB40->unk155[0] == 0) {
            D_807FBB60 |= 0x10070;
            for (i = 0; i < 4; i++) {
                heapFreeDeferred(D_807FC7E0[i]);
            }
            heapFreeDeferred(D_807FC7E0);
        } else if (D_807FBB40->unk155[0] == 1) {
            D_8076A105 = -1;
            func_80714638();
            D_807FBB40->unk155[0] = 2;
        }
    }
    renderCallbacksRegister(func_806AC048, D_807FBB40, 1);
    renderCallbacksRegister(func_806ACF10, D_807FBB40, 5);
}
