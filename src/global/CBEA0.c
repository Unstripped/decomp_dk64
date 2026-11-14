#include "common.h"
#include "actor.h"
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

typedef struct BannerTextStep {
    /* 0x0 */ s16 duration;
    /* 0x2 */ s16 gap;
    /* 0x4 */ s8 side;
    /* 0x5 */ s8 lineCount;
} BannerTextStep;

extern BannerTextStep gBannerTextSteps[];

extern Actor *gCurrentActor;
extern s8 gBannerTextStepIndex;
extern s16 gBannerTextLine;
extern f32 D_8075075C[];
extern s16 D_807FC8E0;
extern s16 gBannerShowTimer;
extern s16 gBannerGapTimer;
extern f32 D_807FC8E8;
extern f32 D_807FC8EC;
extern u8 *D_807FC8F0;


void bannerTextUpdate(void) {
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
        if (gBannerTextStepIndex == -2) {
            gBannerGapTimer = 0x320;
            gBannerTextStepIndex = -1;
            gBannerShowTimer = 0;
            D_807FC8E8 = 0;
        } else if (gBannerTextStepIndex == -1) {
            gBannerGapTimer = 0x3C;
            gBannerShowTimer = 0;
            D_807FC8E8 = 0;
        }
    }
    actor = gCurrentActor;
    if (gBannerShowTimer > 0) {
        gBannerShowTimer--;
    }
    if (gBannerShowTimer == 0) {
        gBannerShowTimer = 0;
        gBannerGapTimer--;
        if (gBannerGapTimer <= 0) {
            if (gBannerTextStepIndex >= 0) {
                gBannerTextLine += gBannerTextSteps[gBannerTextStepIndex].lineCount;
            }
            if (gBannerTextLine >= D_807FC8E0) {
                gBannerTextLine = 0;
            }
            gBannerTextStepIndex++;
            gBannerShowTimer = gBannerTextSteps[gBannerTextStepIndex].duration;
            gBannerGapTimer = gBannerTextSteps[gBannerTextStepIndex].gap;
        }
    }
    if (gBannerShowTimer < 0xB) {
        D_807FC8E8 -= 0.1f;
        if (D_807FC8E8 < 0.0f) {
            D_807FC8E8 = 0.0f;
        }
        D_807FC8EC = 1;
    } else {
        t = gBannerTextSteps[gBannerTextStepIndex].duration - gBannerShowTimer;
        k = t & 1;
        t >>= 1;
        if (t < 0x16) {
            e = &D_8075075C[t * 2];
            frac = (f32)k * 0.5;
            D_807FC8E8 = e[0] + (e[2] - e[0]) * frac;
            D_807FC8EC = e[1] + (e[3] - e[1]) * frac;
        } else {
            D_807FC8E8 = 1.0f;
            D_807FC8EC = 1.0f;
        }
    }
    renderCallbacksRegister(renderBannerText, actor, 3);
}

extern Gfx D_1000118;
extern Mtx D_20000C0;
typedef union ViewportMargins {
    s32 word;
    u8 margin[4];
} ViewportMargins;

extern ViewportMargins gBannerViewportMargins;
extern f32 D_80750818[];
extern f32 D_80750828[];


Gfx *renderBannerText(Gfx *gdl, Actor *actor) {
    f32 sx;
    f32 sy;
    u8 *p;
    f32 *tbl;
    f32 x;
    f32 y;
    ViewportMargins margins;
    f32 mf[4][4];
    f32 mf2[4][4];
    Mtx *mtx;
    s16 v;
    s16 i;
    s16 yoff;

    margins = gBannerViewportMargins;
    if (gBannerTextStepIndex < 0) {
        return gdl;
    }
    i = gBannerTextSteps[gBannerTextStepIndex].side;
    tbl = &D_80750818[i];
    v = ((f64)D_807FC8E8 - 0.5) * (f64)*tbl + (f64)(D_80750828[i] * D_807FC8EC);
    if (v < 0) {
        v = 0;
    }
    margins.margin[i] = v;
    viewportSetMargins(margins.margin[1], margins.margin[3], margins.margin[0], margins.margin[2]);
    if (D_807FC8E8 == 0.0f) {
        return gdl;
    }
    mtx = heapAlloc(0x40);
    heapFreeDeferred(mtx);
    gDPPipeSync(gdl++);
    gSPDisplayList(gdl++, &D_1000118);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gDPSetRenderMode(gdl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(gdl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPSetCombineLERP(gdl++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0);
    gSPMatrix(gdl++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gdl++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
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
    if (gBannerTextLine > 0) {
        do {
            if (*p == 0) {
                i++;
            }
            p++;
        } while (i < gBannerTextLine);
        i = 0;
    }
    yoff = -gBannerTextSteps[gBannerTextStepIndex].lineCount * 0x23;
    if (gBannerTextSteps[gBannerTextStepIndex].lineCount > 0) {
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
        } while (i < gBannerTextSteps[gBannerTextStepIndex].lineCount);
    }
    gSPPopMatrix(gdl++, G_MTX_MODELVIEW);
    gDPPipeSync(gdl++);
    return gdl;
}

