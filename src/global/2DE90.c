#include "common.h"
#include "proto/boot/3630.h"
#include "proto/global/103AB0.h"
#include "proto/global/10E1D0.h"
#include "proto/global/15050.h"
#include "proto/global/2DE90.h"
#include "proto/global/450.h"
#include "proto/global/69E60.h"

extern s8 sScreenWipeActive;
u8 sScreenWipeCooldown = 0;
s32 sScreenWipeMtxReady = 0;
s32 sBlurKernelWidth = 11;
u8 *sBlurDivTable = NULL;
s32 D_80747B30 = 320;
s32 D_80747B34 = 240;
s32 sBlurPassCount = 0;
s32 sBlurPassLimit = 0;
u8 sScreenBufferAllocated = 0;
f32 D_80747B44 = 100.0f;
f32 D_80747B48 = 150.0f;
f32 D_80747B4C = 0.0f;
f32 D_80747B50 = 0.0f;

void screenWipeReset(void) {
    sScreenWipeActive = 0;
}

u8 screenWipeGetState(void) {
    return sScreenWipeActive;
}


u8 screenWipeGetCooldown(void) {
    return sScreenWipeCooldown;
}

extern u16 *gFramebuffers[];
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gGfxBufferIndex;
extern s8 sScreenWipeType;
extern s16 sScreenWipePos;
extern s16 sScreenWipeSplitPos;
extern f32 sScreenWipeInnerRadius;
extern f32 sScreenWipeSweepAngle;
extern u16 *sScreenWipeImage;

void screenWipeStart(type)
u8 type;
{
    if ((sScreenWipeActive == 0) || (type == 7)) {
        if (sScreenWipeActive == 0) {
            sScreenWipeImage = heapAlloc(gScreenWidth * gScreenHeight * 2);
        }
        fbCopySetAlpha(sScreenWipeImage, gFramebuffers[gGfxBufferIndex]);
        sScreenWipeActive = 1;
        sScreenWipeCooldown = 5;
        switch (type) {
            case 1:
                sScreenWipePos = 0xFF;
                break;
            case 2:
                sScreenWipePos = 0;
                break;
            case 0:
                sScreenWipePos = 0x136;
                break;
            case 3:
                sScreenWipePos = 0xA0;
                sScreenWipeSplitPos = 0xA0;
                break;
            case 4:
            case 5:
                sScreenWipeInnerRadius = -5.0f;
                break;
            case 6:
                sScreenWipeSweepAngle = 0.0f;
                break;
            case 7:
                blurBuildDivTable();
                break;
        }
        sScreenWipeType = type;
    }
}

extern Gfx D_1000118;
extern Mtx D_2000140;
extern u32 gFrameDelta;
extern s16 gGfxScreenLeft;
extern s16 gGfxScreenTop;
extern s16 gGfxScreenRight;
extern s16 gGfxScreenBottom;
extern f32 sScreenWipeOuterRadius;
extern Mtx sScreenWipeScaleMtx;

Gfx *screenWipeDraw(Gfx *glist) {
    s32 stepScale;

    stepScale = gFrameDelta * 0.5f;
    if (sScreenWipeMtxReady == 0) {
        guScale(&sScreenWipeScaleMtx, 2.0f, 2.0f, 1.0f);
        sScreenWipeMtxReady = 1;
    }
    if ((sScreenWipeActive == 0) && (sScreenWipeCooldown != 0)) {
        sScreenWipeCooldown--;
    }
    if (sScreenWipeActive < 0) {
        sScreenWipeActive++;
        if (sScreenWipeActive == 0) {
            heapFreeDeferred(sScreenWipeImage);
        }
    } else if (sScreenWipeActive > 0) {
        gSPDisplayList(glist++, &D_1000118);
        glist = gfxInit2DDisplayList(glist);
        gSPMatrix(glist++, &D_2000140, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glist++, &sScreenWipeScaleMtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(glist++);
        gDPSetTextureFilter(glist++, G_TF_POINT);
        gDPSetColorDither(glist++, G_CD_DISABLE);
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight, gGfxScreenBottom);
        gDPSetRenderMode(glist++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        switch (sScreenWipeType) {
            case 7:
                screenBlurApply();
                gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                gfxDrawTexturedTileGridDefault(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 319.0f, 239.0f, 0.0f, 0.0f);
                if (gGlobalPauseFlags & 0x40) {
                    sScreenWipeActive = -2;
                }
                break;
            case 1:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, sScreenWipePos);
                gfxDrawTexturedTileGridDefault(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 319.0f, 239.0f, 0.0f, 0.0f);
                sScreenWipePos -= stepScale * 5;
                if (sScreenWipePos < 0) {
                    sScreenWipeActive = -2;
                }
                break;
            case 2:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                gfxDrawTexturedTileGridDefault(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x20, 0x20, sScreenWipePos, 0.0f, 319.0f, 239.0f, sScreenWipePos, 0.0f);
                gDPPipeSync(glist++);
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                if (sScreenWipePos >= 0x11) {
                    gfxDrawTexturedTileGrid(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x10, 0x50, sScreenWipePos - 0x10, 0.0f, sScreenWipePos, 239.0f, sScreenWipePos - 0x10, 0.0f, 1, 0x10, 1, NULL);
                }
                sScreenWipePos += stepScale * 10;
                if (sScreenWipePos >= 0x137) {
                    sScreenWipeActive = -2;
                }
                break;
            case 0:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                gfxDrawTexturedTileGridDefault(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0xA, 0x50, 0.0f, 0.0f, sScreenWipePos, 239.0f, 0.0f, 0.0f);
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                if (sScreenWipePos < 0x131) {
                    gfxDrawTexturedTileGrid(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x10, 0x20, sScreenWipePos, 0.0f, sScreenWipePos + 0x10, 239.0f, sScreenWipePos, 0.0f, 1, 0x10, 2, NULL);
                }
                sScreenWipePos -= stepScale * 10;
                if (sScreenWipePos < 0xB) {
                    sScreenWipeActive = -2;
                }
                break;
            case 3:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                gfxDrawTexturedTileGridDefault(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x20, 0x20, sScreenWipePos, 0.0f, 319.0f, 239.0f, sScreenWipePos, 0.0f);
                gfxDrawTexturedTileGridDefault(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0xA, 0x50, 0.0f, 0.0f, sScreenWipeSplitPos, 239.0f, 0.0f, 0.0f);
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                if (sScreenWipePos >= 0x11) {
                    gfxDrawTexturedTileGrid(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x10, 0x50, sScreenWipePos - 0x10, 0.0f, sScreenWipePos, 239.0f, sScreenWipePos - 0x10, 0.0f, 1, 0x10, 1, NULL);
                }
                if (sScreenWipeSplitPos < 0x131) {
                    gfxDrawTexturedTileGrid(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x10, 0x20, sScreenWipeSplitPos, 0.0f, sScreenWipeSplitPos + 0x10, 239.0f, sScreenWipeSplitPos, 0.0f, 1, 0x10, 2, NULL);
                }
                sScreenWipePos += stepScale * 10;
                sScreenWipeSplitPos -= stepScale * 10;
                if (sScreenWipePos >= 0x137) {
                    sScreenWipeActive = -2;
                }
                break;
            case 4:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                sScreenWipeInnerRadius += 5.0 * stepScale;
                sScreenWipeOuterRadius = sScreenWipeInnerRadius + 40.0f;
                gfxDrawTexturedTileGrid(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 320.0f, 239.0f, 0.0f, 0.0f, 1, 0x10, 1, screenWipeAlphaFromCentre);
                if (sScreenWipeInnerRadius > 170.0f) {
                    sScreenWipeActive = -2;
                }
                break;
            case 5:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                sScreenWipeInnerRadius += 12.0 * stepScale;
                sScreenWipeOuterRadius = sScreenWipeInnerRadius + 40.0f;
                gfxDrawTexturedTileGrid(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 320.0f, 239.0f, 0.0f, 0.0f, 1, 0x10, 1, screenWipeAlphaFromCorner);
                if (sScreenWipeInnerRadius > 350.0f) {
                    sScreenWipeActive = -2;
                }
                break;
            case 6:
                gDPSetCombineMode(glist++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                sScreenWipeSweepAngle += 15.0 * stepScale;
                gfxDrawTexturedTileGrid(&glist, sScreenWipeImage, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 320.0f, 239.0f, 0.0f, 0.0f, 1, 0x10, 1, screenWipeAlphaRadialSweep);
                if (sScreenWipeSweepAngle > 350.0f) {
                    sScreenWipeActive = -2;
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
    if (sScreenWipeSweepAngle < 20.0) {
        vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        return;
    }
    if (sScreenWipeSweepAngle < ang) {
        f64 diff = ang - sScreenWipeSweepAngle;
        if (diff < 25.0) {
            alpha = (diff / 25.0) * 255.0;
        } else {
            alpha = 0xFF;
        }
    } else {
        alpha = 0;
    }
    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, alpha, 0);
}

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
    if (dist < sScreenWipeInnerRadius) {
        alpha = 0;
    } else if (sScreenWipeOuterRadius < dist) {
        alpha = 0xFF;
    } else {
        alpha = ((dist - sScreenWipeInnerRadius) / (sScreenWipeOuterRadius - sScreenWipeInnerRadius)) * 255.0f;
    }
    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, alpha, 0);
}


void blurBuildDivTable(void) {
    s32 i;

    sBlurDivTable = heapAlloc((sBlurKernelWidth << 5) + 1);
    for (i = 0; i <= (sBlurKernelWidth << 5); i++) {
        sBlurDivTable[i] = i / sBlurKernelWidth;
    }
    sBlurPassCount = 0;
}


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

    src = sScreenWipeImage;
    dst = sScreenWipeImage;
    lut = sBlurDivTable;
    if ((sBlurDivTable == NULL) || (sBlurPassLimit < sBlurPassCount)) {
        if (sBlurDivTable != NULL) {
            heapFree(sBlurDivTable);
            sBlurDivTable = NULL;
        }
    } else {
        for (row = 0; row < D_80747B34; row++) {
            sumR = 0;
            sumB = 0;
            sumG = 0;
            for (i = 0; i < sBlurKernelWidth; i++) {
                r[i] = 0;
                g[i] = 0;
                b[i] = 0;
            }
            idx = sBlurKernelWidth / 2;
            for (i = 0; i < sBlurKernelWidth / 2; i++, idx++) {
                pix = *src++;
                vr = (pix >> 11) & 0x1F;
                r[idx] = vr;
                sumR += vr;
                vg = (pix >> 6) & 0x1F;
                g[idx] = vg;
                sumG += vg;
                vb = (pix >> 1) & 0x1F;
                b[idx] = vb;
                sumB += vb;
            }
            idx = 0;
            for (i = 0; i < D_80747B30 - sBlurKernelWidth / 2; i++, idx++) {
                pix = *src++;
                if (idx >= sBlurKernelWidth) {
                    idx = 0;
                }
                vr = (pix >> 11) & 0x1F;
                sumR -= r[idx];
                r[idx] = vr;
                sumR += vr;
                vg = (pix >> 6) & 0x1F;
                sumG -= g[idx];
                g[idx] = vg;
                sumG += vg;
                vb = (pix >> 1) & 0x1F;
                sumB -= b[idx];
                b[idx] = vb;
                sumB += vb;
                *dst++ = 1 | (lut[sumB] << 1) | (lut[sumG] << 6) | (lut[sumR] << 11);
            }
            for (i = D_80747B30 - sBlurKernelWidth / 2; i < D_80747B30; i++, idx++) {
                if (idx >= sBlurKernelWidth) {
                    idx = 0;
                }
                sumR -= r[idx];
                sumG -= g[idx];
                sumB -= b[idx];
                r[idx] = 0;
                g[idx] = 0;
                b[idx] = 0;
                *dst++ = 1 | (lut[sumB] << 1) | (lut[sumG] << 6) | (lut[sumR] << 11);
            }
        }
        sBlurPassCount++;
    }
}

extern u8 *sScreenBuffer;

void screenBufferAllocate(void) {
    if (sScreenBufferAllocated == 0) {
        sScreenBuffer = heapAlloc(0x25800);
        _memset(sScreenBuffer, 0, 0x25800);
        sScreenBufferAllocated = 1;
    }
}

void screenBufferFree(void) {
    if (sScreenBufferAllocated != 0) {
        heapFreeDeferred(sScreenBuffer);
        sScreenBufferAllocated = 0;
    }
}


void screenRectSetSize(s32 width, s32 height) {
    D_80747B4C = 2.0f;
    D_80747B50 = 2.0f;
    D_80747B44 = width;
    D_80747B48 = height;
}

Gfx *gfxPassThrough(Gfx *glist) {
    return glist;
}
