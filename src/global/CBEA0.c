#include "common.h"
#include "actor.h"
#define PROTO_SKIP_viewportSetMargins // FAKE: callee prototype steer
#include "proto/global/100180.h"
#include "proto/global/15050.h"
#include "proto/global/450.h"
#include "proto/global/6AD90.h"
#include "proto/global/90D80.h"
#include "proto/global/CBEA0.h"

void actorStubCBEA0_00(void) {
}

void actorStubCBEA0_01(void) {
}

void actorStubCBEA0_02(void) {
}

void actorStubCBEA0_03(void) {
}

void actorStubCBEA0_04(void) {
}

void actorStubCBEA0_05(void) {
}

void actorStubCBEA0_06(void) {
}

void actorStubCBEA0_07(void) {
}

void actorStubCBEA0_08(void) {
}

void actorStubCBEA0_09(void) {
}

void actorStubCBEA0_10(void) {
}

void actorStubCBEA0_11(void) {
}

void actorStubCBEA0_12(void) {
}

void actorStubCBEA0_13(void) {
}

void actorStubCBEA0_14(void) {
}

void actorStubCBEA0_15(void) {
}

void actorStubCBEA0_16(void) {
}

void actorStubCBEA0_17(void) {
}

void actorStubCBEA0_18(void) {
}

void actorStubCBEA0_19(void) {
}

void actorStubCBEA0_20(void) {
}

void actorStubCBEA0_21(void) {
}

void actorStubCBEA0_22(void) {
}

void actorStubCBEA0_23(void) {
}

void actorStubCBEA0_24(void) {
}

void actorStubCBEA0_25(void) {
}

typedef struct R1C2CB_Entry {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s8 unk4;
    /* 0x5 */ s8 unk5;
} R1C2CB_Entry;

extern R1C2CB_Entry D_807506D0[];

extern Actor *gCurrentActor;
extern s8 D_80750754;
extern s16 D_80750758;
extern s8 D_807506D5[];
extern f32 D_8075075C[];
extern s16 D_807FC8E0;
extern s16 D_807FC8E2;
extern s16 D_807FC8E4;
extern f32 D_807FC8E8;
extern f32 D_807FC8EC;
extern u8 *D_807FC8F0;


void spriteLinearInterpolateFrame(void) {
    f32 frac;
    f32 pad0;
    f32 pad1;
    f32 *e;
    Actor *actor;
    s32 i;
    s32 t;
    s32 k;

    if (!(gCurrentActor->flags & 0x10)) {
        D_807FC8F0 = assetLoad(0x13, 7, 1, 1);
        D_807FC8E0 = 0;
        for (i = 0; D_807FC8F0[i] != 0x2A; i++) {
            if (D_807FC8F0[i] == 0xA) {
                D_807FC8F0[i] = 0;
                D_807FC8E0++;
            }
        }
        if (D_80750754 == -2) {
            D_807FC8E4 = 0x320;
            D_80750754 = -1;
            D_807FC8E2 = 0;
            D_807FC8E8 = 0;
        } else if (D_80750754 == -1) {
            D_807FC8E4 = 0x3C;
            D_807FC8E2 = 0;
            D_807FC8E8 = 0;
        }
    }
    actor = gCurrentActor;
    if (D_807FC8E2 > 0) {
        D_807FC8E2--;
    }
    if (D_807FC8E2 == 0) {
        D_807FC8E2 = 0;
        D_807FC8E4--;
        if (D_807FC8E4 <= 0) {
            if (D_80750754 >= 0) {
                D_80750758 += D_807506D5[D_80750754 * 6];
            }
            if (D_80750758 >= D_807FC8E0) {
                D_80750758 = 0;
            }
            D_80750754++;
            D_807FC8E2 = D_807506D0[D_80750754].unk0;
            D_807FC8E4 = D_807506D0[D_80750754].unk2;
        }
    }
    if (D_807FC8E2 < 0xB) {
        D_807FC8E8 -= 0.1f;
        if (D_807FC8E8 < 0.0f) {
            D_807FC8E8 = 0.0f;
        }
        D_807FC8EC = 1;
    } else {
        t = D_807506D0[D_80750754].unk0 - D_807FC8E2;
        k = t & 1;
        t >>= 1;
        if (t < 0x16) {
            e = &D_8075075C[t * 2];
            frac = (f64)(f32)k * 0.5;
            D_807FC8E8 = e[0] + (e[2] - e[0]) * frac;
            D_807FC8EC = e[1] + (e[3] - e[1]) * frac;
        } else {
            D_807FC8E8 = 1.0f;
            D_807FC8EC = 1.0f;
        }
    }
    renderCallbacksRegister(renderBannerText, actor, 3);
}

#define R1C2CB_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern Gfx D_1000118;
extern Mtx D_20000C0;
typedef union R1C2CB_Col {
    s32 w;
    u8 b[4];
} R1C2CB_Col;

extern R1C2CB_Col D_80750814;
extern f32 D_80750818[];
extern f32 D_80750828[];

void viewportSetMargins(u8, u8, u8, u8); // FAKE: callee prototype steer
void guScaleF(f32 mf[4][4], f32 x, f32 y, f32 z);
void guTranslateF(f32 mf[4][4], f32 x, f32 y, f32 z);
void guMtxCatF(f32 mf[4][4], f32 nf[4][4], f32 res[4][4]);
void guMtxF2L(f32 mf[4][4], Mtx *m);

Gfx *renderBannerText(Gfx *gdl, Actor *actor) {
    f32 sx;
    f32 sy;
    u8 *p;
    f32 *tbl;
    f32 x;
    f32 y;
    R1C2CB_Col col;
    f32 mf[4][4];
    f32 mf2[4][4];
    Mtx *mtx;
    s16 v;
    s16 i;
    s16 yoff;

    col = D_80750814;
    if (D_80750754 < 0) {
        return gdl;
    }
    i = D_807506D0[D_80750754].unk4;
    tbl = &D_80750818[i];
    v = ((f64)D_807FC8E8 - 0.5) * (f64)*tbl + (f64)(D_80750828[i] * D_807FC8EC);
    if (v < 0) {
        v = 0;
    }
    col.b[i] = v;
    viewportSetMargins(col.b[1], col.b[3], col.b[0], col.b[2]);
    if (D_807FC8E8 == 0.0f) {
        return gdl;
    }
    mtx = heapAlloc(0x40);
    heapFreeDeferred(mtx);
    R1C2CB_GFX(gdl++, 0xE7000000, 0);
    R1C2CB_GFX(gdl++, 0xDE000000, &D_1000118);
    R1C2CB_GFX(gdl++, 0xE3000A01, 0);
    R1C2CB_GFX(gdl++, 0xE200001C, 0x504240);
    R1C2CB_GFX(gdl++, 0xFA000000, 0xFFFFFFFF);
    R1C2CB_GFX(gdl++, 0xFC119623, 0xFF2FFFFF);
    R1C2CB_GFX(gdl++, 0xDA380007, &D_20000C0);
    R1C2CB_GFX(gdl++, 0xDA380003, mtx);
    sx = 1.0;
    sy = 1.0;
    if (i & 1) {
        sx = D_807FC8EC;
    } else {
        sy = D_807FC8EC;
    }
    guScaleF(mf, sx * 0.55, sy * 0.55, 1.0f);
    switch (i) {
    case 0:
        x = 160.0f;
        y = *tbl * D_807FC8E8 + -55.0;
        break;
    case 2:
        x = 160.0f;
        y = 265.0 - *tbl * D_807FC8E8;
        break;
    case 1:
        x = *tbl * D_807FC8E8 + -70.0;
        x += 8.0;
        y = 120.0f;
        break;
    case 3:
        x = 390.0 - *tbl * D_807FC8E8;
        x -= 8.0;
        y = 120.0f;
        break;
    }
    guTranslateF(mf2, x * 4.0, y * 4.0, 0.0f);
    guMtxCatF(mf, mf2, mf);
    guMtxF2L(mf, mtx);
    p = D_807FC8F0;
    i = 0;
    if (D_80750758 > 0) {
        do {
            if (*p == 0) {
                i++;
            }
            p++;
        } while (i < D_80750758);
        i = 0;
    }
    yoff = -D_807506D0[D_80750754].unk5 * 0x23;
    if (D_807506D0[D_80750754].unk5 > 0) {
        do {
            gdl = textDrawStringVtx(gdl, 1, -(s16)(textGetStringWidth(1, p) * 2), yoff, p, 0);
            yoff += 0x60;
            if (*p != 0) {
                do {
                    p++;
                } while (*p != 0);
            }
            i++;
            p++;
        } while (i < D_807506D0[D_80750754].unk5);
    }
    R1C2CB_GFX(gdl++, 0xD8380002, 0x40);
    R1C2CB_GFX(gdl++, 0xE7000000, 0);
    return gdl;
}

