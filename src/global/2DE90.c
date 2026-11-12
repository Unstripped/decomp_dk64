#include "common.h"
#include "proto/boot/3630.h"
#include "proto/global/103AB0.h"
#include "proto/global/10E1D0.h"
#include "proto/global/15050.h"
#include "proto/global/2DE90.h"
#include "proto/global/450.h"
#include "proto/global/69E60.h"

extern s8 D_807F5D84;

void screenWipeReset(void) {
    D_807F5D84 = 0;
}

u8 screenWipeGetState(void) {
    return (u8)D_807F5D84;
}

extern u8 D_80747B20;

u8 screenWipeGetCooldown(void) {
    return D_80747B20;
}

extern u16 *gFramebuffers[];
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gGfxBufferIndex;
extern u8 D_807F5D85;
extern s16 D_807F5D86;
extern s16 D_807F5D88;
extern f32 D_807F5D8C;
extern f32 D_807F5D94;
extern u16 *D_807F5D80;

void screenWipeStart(type)
u8 type;
{
    s32 sel = type; // FAKE: s32 copy of the K&R u8 param steers the switch dispatch registers (Q0140)

    if ((D_807F5D84 == 0) || (type == 7)) {
        if (D_807F5D84 == 0) {
            D_807F5D80 = heapAlloc(gScreenWidth * gScreenHeight * 2);
        }
        fbCopySetAlpha(D_807F5D80, gFramebuffers[gGfxBufferIndex]);
        D_807F5D84 = 1;
        D_80747B20 = 5;
        switch (sel) {
            case 1:
                D_807F5D86 = 0xFF;
                break;
            case 2:
                D_807F5D86 = 0;
                break;
            case 0:
                D_807F5D86 = 0x136;
                break;
            case 3:
                D_807F5D86 = 0xA0;
                D_807F5D88 = 0xA0;
                break;
            case 4:
            case 5:
                D_807F5D8C = -5.0f;
                break;
            case 6:
                D_807F5D94 = 0.0f;
                break;
            case 7:
                blurBuildDivTable();
                break;
        }
        D_807F5D85 = sel;
    }
}

extern u8 D_1000118;
extern u8 D_2000140;
extern u32 gFrameDelta;
extern s16 gGfxScreenLeft;
extern s16 gGfxScreenTop;
extern s16 gGfxScreenRight;
extern s16 gGfxScreenBottom;
extern s32 D_80747B24;
extern f32 D_807F5D90;
extern Mtx D_807F5D98;

Gfx *screenWipeDraw(Gfx *glist) {
    s32 stepScale;

    stepScale = (s32)((f32)gFrameDelta * 0.5f);
    if (D_80747B24 == 0) {
        guScale(&D_807F5D98, 2.0f, 2.0f, 1.0f);
        D_80747B24 = 1;
    }
    if ((D_807F5D84 == 0) && (D_80747B20 != 0)) {
        D_80747B20--;
    }
    if (D_807F5D84 < 0) {
        D_807F5D84++;
        if (D_807F5D84 == 0) {
            heapFreeDeferred(D_807F5D80);
        }
    } else if (D_807F5D84 > 0) {
        gSPDisplayList(glist++, &D_1000118);
        glist = gfxInit2DDisplayList(glist);
        gSPMatrix(glist++, &D_2000140, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glist++, &D_807F5D98, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(glist++);
        gDPSetTextureFilter(glist++, G_TF_POINT);
        gDPSetColorDither(glist++, G_CD_DISABLE);
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight, gGfxScreenBottom);
        gDPSetRenderMode(glist++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        switch (D_807F5D85) {
            case 7:
                screenBlurApply();
                gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                gfxDrawTexturedTileGridDefault(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 319.0f, 239.0f, 0.0f, 0.0f);
                if (gGlobalPauseFlags & 0x40) {
                    D_807F5D84 = -2;
                }
                break;
            case 1:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, D_807F5D86);
                gfxDrawTexturedTileGridDefault(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 319.0f, 239.0f, 0.0f, 0.0f);
                D_807F5D86 -= stepScale * 5;
                if (D_807F5D86 < 0) {
                    D_807F5D84 = -2;
                }
                break;
            case 2:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                gfxDrawTexturedTileGridDefault(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, (f32)D_807F5D86, 0.0f, 319.0f, 239.0f, (f32)D_807F5D86, 0.0f);
                gDPPipeSync(glist++);
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                if (D_807F5D86 >= 0x11) {
                    gfxDrawTexturedTileGrid(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x10, 0x50, (f32)(D_807F5D86 - 0x10), 0.0f, (f32)D_807F5D86, 239.0f, (f32)(D_807F5D86 - 0x10), 0.0f, 1, 0x10, 1, NULL);
                }
                D_807F5D86 = D_807F5D86 + stepScale * 10;
                if (D_807F5D86 >= 0x137) {
                    D_807F5D84 = -2;
                }
                break;
            case 0:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                gfxDrawTexturedTileGridDefault(&glist, D_807F5D80, 0, 0x140, 0xF0, 0xA, 0x50, 0.0f, 0.0f, D_807F5D86, 239.0f, 0.0f, 0.0f);
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                if (D_807F5D86 < 0x131) {
                    gfxDrawTexturedTileGrid(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x10, 0x20, (f32)D_807F5D86, 0.0f, (f32)(D_807F5D86 + 0x10), 239.0f, (f32)D_807F5D86, 0.0f, 1, 0x10, 2, NULL);
                }
                D_807F5D86 = D_807F5D86 - stepScale * 10;
                if (D_807F5D86 < 0xB) {
                    D_807F5D84 = -2;
                }
                break;
            case 3:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                gfxDrawTexturedTileGridDefault(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, (f32)D_807F5D86, 0.0f, 319.0f, 239.0f, (f32)D_807F5D86, 0.0f);
                gfxDrawTexturedTileGridDefault(&glist, D_807F5D80, 0, 0x140, 0xF0, 0xA, 0x50, 0.0f, 0.0f, D_807F5D88, 239.0f, 0.0f, 0.0f);
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                if (D_807F5D86 >= 0x11) {
                    gfxDrawTexturedTileGrid(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x10, 0x50, (f32)(D_807F5D86 - 0x10), 0.0f, (f32)D_807F5D86, 239.0f, (f32)(D_807F5D86 - 0x10), 0.0f, 1, 0x10, 1, NULL);
                }
                if (D_807F5D88 < 0x131) {
                    gfxDrawTexturedTileGrid(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x10, 0x20, (f32)D_807F5D88, 0.0f, (f32)(D_807F5D88 + 0x10), 239.0f, (f32)D_807F5D88, 0.0f, 1, 0x10, 2, NULL);
                }
                D_807F5D86 += stepScale * 10;
                D_807F5D88 = D_807F5D88 - stepScale * 10;
                if (D_807F5D86 >= 0x137) {
                    D_807F5D84 = -2;
                }
                break;
            case 4:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                D_807F5D8C = D_807F5D8C + 5.0 * stepScale;
                D_807F5D90 = D_807F5D8C + 40.0f;
                gfxDrawTexturedTileGrid(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 320.0f, 239.0f, 0.0f, 0.0f, 1, 0x10, 1, screenWipeAlphaFromCentre);
                if (D_807F5D8C > 170.0f) {
                    D_807F5D84 = -2;
                }
                break;
            case 5:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                D_807F5D8C = D_807F5D8C + 12.0 * stepScale;
                D_807F5D90 = D_807F5D8C + 40.0f;
                gfxDrawTexturedTileGrid(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 320.0f, 239.0f, 0.0f, 0.0f, 1, 0x10, 1, screenWipeAlphaFromCorner);
                if (D_807F5D8C > 350.0f) {
                    D_807F5D84 = -2;
                }
                break;
            case 6:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                D_807F5D94 = D_807F5D94 + 15.0 * stepScale;
                gfxDrawTexturedTileGrid(&glist, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 320.0f, 239.0f, 0.0f, 0.0f, 1, 0x10, 1, screenWipeAlphaRadialSweep);
                if (D_807F5D94 > 350.0f) {
                    D_807F5D84 = -2;
                }
                break;
        }
        gDPPipeSync(glist++);
        gDPSetColorDither(glist++, G_CD_MAGICSQ);
        gDPSetTextureFilter(glist++, G_TF_BILERP);
    }
    return glist;
}


void screenWipeAlphaRadialSweep(s32 x, s32 y, Vtx *vtx) {
    f32 ang;
    s16 alpha;

    ang = mathAngleBetweenPointsDeg(0xA0, 0x78, x, y);
    if (D_807F5D94 < 20.0) {
        vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        return;
    }
    alpha = 0;
    if (D_807F5D94 < ang) {
        f64 diff = ang - D_807F5D94;
        if (diff < 25.0) {
            alpha = (s16)((diff / 25.0) * 255.0);
        } else {
            alpha = 0xFF;
        }
    } else {
        alpha = 0;
    }
    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, alpha, 0);
}

f32 sqrtf(f32);


void screenWipeAlphaFromCorner(s32 x, s32 y, Vtx *vtx) {
    screenWipeAlphaByDistance(x, y, vtx, 0, 0);
}

void screenWipeAlphaFromCentre(s32 x, s32 y, Vtx *vtx) {
    screenWipeAlphaByDistance(x, y, vtx, 0xA0, 0x78);
}

void screenWipeAlphaByDistance(s32 x, s32 y, Vtx *vtx, s32 originX, s32 originY) {
    s32 dx;
    s32 dy;
    f32 dist;
    s16 alpha;

    dx = x - originX;
    dy = y - originY;
    dist = sqrtf(dx * dx + dy * dy);
    if (dist < D_807F5D8C) {
        alpha = 0;
    } else if (D_807F5D90 < dist) {
        alpha = 0xFF;
    } else {
        alpha = (s16)(((dist - D_807F5D8C) / (D_807F5D90 - D_807F5D8C)) * 255.0f);
    }
    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, alpha, 0);
}

extern s32 D_80747B28;
extern u8 *D_80747B2C;
extern s32 D_80747B38;

void blurBuildDivTable(void) {
    s32 i;

    D_80747B2C = heapAlloc((D_80747B28 << 5) + 1);
    for (i = 0; i <= (D_80747B28 << 5); i++) {
        D_80747B2C[i] = i / D_80747B28;
    }
    D_80747B38 = 0;
}

extern s32 D_80747B30;
extern s32 D_80747B34;
extern s32 D_80747B3C;

void screenBlurApply(void) {
    u16 *src;
    s32 row;
    u16 *dst;
    u8 *lut;
    s32 sumR;
    s32 sumG;
    s32 sumB;
    s32 i;
    s32 idx;
    u32 pix;
    u8 r[0x34];
    u8 g[0x34];
    u8 b[0x34];
    u8 vr;
    u8 vg;
    u8 vb;

    src = D_807F5D80;
    dst = D_807F5D80;
    lut = D_80747B2C;
    if ((D_80747B2C == 0) || (D_80747B3C < D_80747B38)) {
        if (D_80747B2C != 0) {
            heapFree(D_80747B2C);
            D_80747B2C = 0;
        }
    } else {
        for (row = 0; row < D_80747B34; row++) {
            sumR = 0;
            sumB = 0;
            sumG = 0;
            for (i = 0; i < D_80747B28; i++) {
                r[i] = 0;
                g[i] = 0;
                b[i] = 0;
            }
            idx = D_80747B28 / 2;
            for (i = 0; i < D_80747B28 / 2; i++) {
                pix = *src;
                vr = (pix >> 11) & 0x1F;
                r[idx] = vr;
                sumR += vr;
                vg = (pix >> 6) & 0x1F;
                vb = (pix >> 1) & 0x1F;
                idx++; // FAKE: early increment + idx - 1 stores steer schedule (Q0483)
                src++;
                g[idx - 1] = vg;
                sumG += vg;
                b[idx - 1] = vb;
                sumB += vb;
            }
            idx = 0;
            for (i = 0; i < D_80747B30 - D_80747B28 / 2; i++) {
                pix = *src++;
                if (idx >= D_80747B28) {
                    idx = 0;
                }
                vr = (pix >> 11) & 0x1F;
                sumR -= r[idx];
                sumR += vr;
                r[idx] = vr;
                vg = (pix >> 6) & 0x1F;
                sumG -= g[idx];
                g[idx] = vg;
                sumG += vg;
                vb = (pix >> 1) & 0x1F;
                sumB -= b[idx];
                b[idx] = vb;
                idx++;
                sumB += vb;
                *dst = 1 | (lut[sumB] << 1) | (lut[sumG] << 6) | (lut[sumR] << 11);
                dst++;
            }
            for (i = D_80747B30 - D_80747B28 / 2; i < D_80747B30; i++) {
                if (idx >= D_80747B28) {
                    idx = 0;
                }
                sumR -= r[idx];
                sumG -= g[idx];
                sumB -= b[idx];
                r[idx] = 0;
                g[idx] = 0;
                b[idx] = 0;
                idx++;
                *dst = 1 | (lut[sumB] << 1) | (lut[sumG] << 6) | (lut[sumR] << 11);
                dst++;
            }
        }
        D_80747B38++;
    }
}

extern u8 D_80747B40;
extern u8 *D_807F5DD8;

void screenBufferAllocate(void) {
    if (D_80747B40 == 0) {
        D_807F5DD8 = heapAlloc(0x25800);
        _memset(D_807F5DD8, 0, 0x25800);
        D_80747B40 = 1;
    }
}

void screenBufferFree(void) {
    if (D_80747B40 != 0) {
        heapFreeDeferred(D_807F5DD8);
        D_80747B40 = 0;
    }
}

extern f32 D_80747B44;
extern f32 D_80747B48;
extern f32 D_80747B4C;
extern f32 D_80747B50;

void func_8062A808(s32 width, s32 height) {
    D_80747B4C = 2.0f;
    D_80747B50 = 2.0f;
    D_80747B44 = width;
    D_80747B48 = height;
}

Gfx *gfxPassThrough(Gfx *glist) {
    return glist;
}
