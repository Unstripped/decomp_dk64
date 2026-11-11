#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/103AB0.h"
#include "proto/global/109660.h"
#include "proto/global/17800.h"
#include "proto/global/201B0.h"
#include "proto/global/5E2F0.h"
#include "proto/global/6AD90.h"
#include "proto/global/8F4B0.h"
#include "proto/global/90D80.h"

extern Actor *gPrimaryPlayerActor;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern s32 gCurrentMap;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gGfxBufferIndex;

// Split-screen divider rectangle (D_80750840, terminated by players == -1); coordinates in low-res pixels.
typedef struct {
    s8 players; // player count it applies to; 2 = any multiplayer count
    u8 splitMode;
    u8 viewMask;
    u8 pad3;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} FillRectEntry;

extern FillRectEntry D_80750840[];
extern u8 gSplitScreenMode;
extern u8 D_80750ABC;
extern u8 gHiResScale;

Gfx *gfxDrawSplitScreenDividers(Gfx *dl) {
    s32 i;

    i = 0;
    gDPPipeSync(dl++);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0);
    gDPSetCycleType(dl++, G_CYC_FILL);
    gDPSetFillColor(dl++, 0x10001);
    for (; D_80750840[i].players != -1; i++) {
        if (((D_80750840[i].players == 2) && (gPlayerCount >= 2) && (D_80750840[i].viewMask & D_80750ABC)) || ((gPlayerCount == D_80750840[i].players) && (gSplitScreenMode == D_80750840[i].splitMode) && (D_80750840[i].viewMask & D_80750ABC))) {
            gDPFillRectangle(dl++, D_80750840[i].x0 * gHiResScale, D_80750840[i].y0 * gHiResScale,
                             (D_80750840[i].x1 + 1) * gHiResScale - 1, (D_80750840[i].y1 + 1) * gHiResScale - 1);
        }
    }
    gDPPipeSync(dl++);
    return dl;
}

extern f32 D_807FD968;
extern f32 D_807FD96C;
extern f32 D_807FD970;

void lightSetOverrideColor(f32 r, f32 g, f32 b) {
    D_807FD968 = r;
    D_807FD96C = g;
    D_807FD970 = b;
}

extern Actor *gCamActor;
extern u8 D_80754EF8[][12];
extern Vtx *D_80754ED8[];
extern Mtx D_2000080;
extern Mtx D_2000180;
f32 cosApprox(f32);

// Channel `off` of the sky colour table, blended from skyTypeA to skyTypeB by alpha and scaled by mul.
#define BG_BLEND(off, mul) \
    ((u32)((mul) * ((f32)D_80754EF8[skyTypeA][off] + (alpha * (f32)(D_80754EF8[skyTypeB][off] - D_80754EF8[skyTypeA][off])))))

Gfx *gfxDrawBackgroundQuad(Gfx *gdl, f32 rotX, f32 angle, Mtx *mtx, u8 skyTypeA, u8 skyTypeB, u8 colorMode, s8 lightIndex, f32 alpha) {
    f32 y;
    u32 color0;
    u32 color1;
    u32 color2;
    u32 color3;
    f32 red;
    f32 green;
    f32 blue;
    Vtx **vtxList;
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    s32 offset;
    CamState *camState;

    y = -(256.0f - (cosApprox(angle) * 300.0f)) - 80.0f;
    camState = gCamActor->customState;
    if (skyTypeA == 5) {
        y += 0.08 * gPlayerSlots->unk2CA - 75.0;
    }

    switch (colorMode) {
    case 0:
        blue = 1.0f;
        green = 1.0f;
        red = 1.0f;
        break;
    case 1:
        if (D_807FD968 >= 0.0f) {
            red = D_807FD968;
            green = D_807FD96C;
            blue = D_807FD970;
        } else {
            if (lightIndex == -1) {
                lightIndex = gPrimaryPlayerActor->chunkIndex;
            }
            lightGetColor(&red, &green, &blue, lightIndex);
        }
        break;
    }
    if ((camState->unkFA != 0) && (gPlayerSlots->unk220 < (camState->unk90 + 3.0f))) {
        red *= 0.1;
        green *= 0.1;
        blue *= 0.3;
    }

    color0 = ((BG_BLEND(0, red) & 0xFF) << 24) | ((BG_BLEND(1, green) & 0xFF) << 16) | (BG_BLEND(2, blue) & 0xFF) << 8 | 0xFF;
    color1 = ((BG_BLEND(3, red) & 0xFF) << 24) | ((BG_BLEND(4, green) & 0xFF) << 16) | (BG_BLEND(5, blue) & 0xFF) << 8 | 0xFF;
    color2 = ((BG_BLEND(6, red) & 0xFF) << 24) | ((BG_BLEND(7, green) & 0xFF) << 16) | (BG_BLEND(8, blue) & 0xFF) << 8 | 0xFF;
    color3 = ((BG_BLEND(9, red) & 0xFF) << 24) | ((BG_BLEND(10, green) & 0xFF) << 16) | (BG_BLEND(11, blue) & 0xFF) << 8 | 0xFF;

    gDPPipeSync(gdl++);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x552048);
    gDPSetCombineMode(gdl++, G_CC_SHADE, G_CC_SHADE);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gdl++, 0xFFFFFF);
    gSPSetGeometryMode(gdl++, 0x200004);
    gSPMatrix(gdl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPViewport(gdl++, osVirtualToPhysical(&gPlayerSlots->viewport[gGfxBufferIndex]));
    gDPSetScissor(gdl++, G_SC_NON_INTERLACE, gPlayerSlots->rect[0], gPlayerSlots->rect[1], gPlayerSlots->rect[2], gPlayerSlots->rect[3]);

    offset = D_80754ED8[skyTypeA][2].v.ob[1];
    vtxList = &D_80754ED8[skyTypeA];
    guTranslateF(mtxA, 0.0f, (f32)-offset, 0.0f);
    matrixMakeRotationZ(mtxB, (((0x1000 - gPlayerSlots->unk2CC) & 0xFFF) * 360) / 4096);
    guMtxCatF(mtxA, mtxB, mtxA);
    guTranslateF(mtxB, 160.0f, (f32)offset + y, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, mtx);

    gSPMatrix(gdl++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPVertex(gdl++, osVirtualToPhysical(*vtxList), 8, 0);
    gSPModifyVertex(gdl++, 0, G_MWO_POINT_RGBA, color0);
    gSPModifyVertex(gdl++, 1, G_MWO_POINT_RGBA, color0);
    gSPModifyVertex(gdl++, 2, G_MWO_POINT_RGBA, color1);
    gSPModifyVertex(gdl++, 3, G_MWO_POINT_RGBA, color1);
    gSPModifyVertex(gdl++, 4, G_MWO_POINT_RGBA, color2);
    gSPModifyVertex(gdl++, 5, G_MWO_POINT_RGBA, color2);
    gSPModifyVertex(gdl++, 6, G_MWO_POINT_RGBA, color3);
    gSPModifyVertex(gdl++, 7, G_MWO_POINT_RGBA, color3);
    gSP2Triangles(gdl++, 0, 1, 3, 0, 0, 3, 2, 0);
    gSP2Triangles(gdl++, 2, 3, 4, 0, 2, 4, 5, 0);
    gSP2Triangles(gdl++, 5, 4, 6, 0, 5, 6, 7, 0);
    gDPPipeSync(gdl++);
    return gdl;
}

typedef struct ColorBytesView {
    u8 pad0[0xC];
    s8 r;
    s8 g;
    s8 b;
} ColorBytesView;

void gfxDrawSkybox(ColorBytesView *colorView, s8 r, s8 g, s8 b) {
    colorView->r = r;
    colorView->g = g;
    colorView->b = b;
}

extern s32 D_807FD8A0;
extern Mtx D_807FD928;
extern void *D_807FD978[8];

void gfxBackgroundReset(void) {
    D_807FD8A0 = 0;
    guOrtho(&D_807FD928, 0.0f, gScreenWidth * 16.0f - 1.0, gScreenHeight * 16.0f - 1.0, 0.0f, -20000.0f, 20000.0f, 1.0f);
    D_807FD968 = -1.0f;
    D_807FD978[0] = NULL;
}

f32 mathCosF(s16);
f32 mathSinF(s16);

void lensFlareAddFromAngle(s16 azimuthAngle, s16 elevationAngle, u8 colorMode) {
    f32 lightR;
    f32 lightG;
    f32 lightB;
    s16 x;
    s16 y;
    s16 z;
    s32 pad;

    x = mathSinF(azimuthAngle) * 32767.0;
    z = mathCosF(azimuthAngle) * 32767.0;
    y = elevationAngle - 8.0 * gPlayerSlots->unk2CA;
    if (colorMode != 0) {
        if (colorMode == 1) {
            lightGetColor(&lightR, &lightG, &lightB, gPrimaryPlayerActor->chunkIndex);
            if (lightR > 0.5) {
                lensFlareAddSource(x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, (u32)(lightR * 255.0f), (u32)(lightG * 255.0f), (u32)(lightB * 255.0f));
            }
        }
    } else {
        lensFlareAddSource(x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF);
    }
}

extern f32 gBackgroundBlend;
extern Mtx D_2000100;

Gfx *gfxDrawSkySprite(Gfx *dl, s16 azimuthAngle, s16 elevationAngle, u8 mode) {
    s16 x;
    Gfx *g;
    f32 screenX, screenY;
    u8 alpha;
    f32 lightR, lightG, lightB;
    s16 y;
    s16 z;

    alpha = 0xFF;
    if (mode == 1) {
        lightGetColor(&lightR, &lightG, &lightB, gPrimaryPlayerActor->chunkIndex);
        lightR = (1.0 < (1.0 - lightG) / 0.7) ? 1.0 : (1.0 - lightG) / 0.7;
        alpha = lightR * 255.0;
    } else if (mode == 2) {
        lightR = gBackgroundBlend - 0.5;
        if (lightR < 0.0) {
            lightR = 0.0f;
        }
        lightR *= 512.0;
        if (lightR > 255.0) {
            lightR = 255.0f;
        }
        alpha = lightR;
    }
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    x = mathSinF(azimuthAngle) * 32767.0;
    z = mathCosF(azimuthAngle) * 32767.0;
    y = elevationAngle - 8.0 * gPlayerSlots->unk2CA;
    camProjectToScreen(x, y, z, &screenX, &screenY, 0, 4.0f, 0);
    if ((screenX > -320.0f) && (screenX < 1600.0f) && (screenY > -240.0f) && (screenY < 1200.0f)) {
        g = playerViewGfxSetup(dl, 0);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
        g->words.w0 = 0xDA380007; g->words.w1 = (u32)&D_2000100; dl = renderRotatedSprite(g + 1, 0x35, 3, 1, 0x40, 0x40, (s32)screenX, (s32)screenY, 4.0f, 4.0f, 0, 0.0f); // FAKE: hand-expanded gSPMatrix(g, &D_2000100, PROJECTION|LOAD|NOPUSH) on one line: the macro's block _g home grows the frame 0x78 -> 0x80 (Q0353)
    }
    return dl;
}

typedef struct RectSpan {
    f32 v[3][2];
} RectSpan;

void gfxWrapRectSpan(RectSpan *spans, u8 *pCount, u8 axis, f32 maxCoord) {
    RectSpan temp[4];
    s32 i;
    u8 out;
    f32 pos;
    f32 tex;

    out = 0;
    for (i = 0; i < *pCount; i++) {
        temp[i] = spans[i];
    }
    for (i = 0; i < *pCount; i++) {
        if ((temp[i].v[0][axis] < 0.0f) || (maxCoord < temp[i].v[1][axis])) {
            pos = (temp[i].v[0][axis] < 0.0f) ? temp[i].v[0][axis] + maxCoord : temp[i].v[0][axis];
            spans[out].v[0][axis] = pos;
            spans[out].v[0][axis ^ 1] = temp[i].v[0][axis ^ 1];
            spans[out].v[1][axis] = maxCoord;
            spans[out].v[1][axis ^ 1] = temp[i].v[1][axis ^ 1];
            spans[out].v[2][axis] = temp[i].v[2][axis];
            spans[out].v[2][axis ^ 1] = temp[i].v[2][axis ^ 1];
            tex = spans[out].v[2][axis] + (maxCoord - pos);
            out++;
            pos = (temp[i].v[0][axis] < 0.0f) ? temp[i].v[1][axis] : temp[i].v[1][axis] - maxCoord;
            spans[out].v[0][axis] = 0.0f;
            spans[out].v[0][axis ^ 1] = temp[i].v[0][axis ^ 1];
            spans[out].v[1][axis] = pos;
            spans[out].v[1][axis ^ 1] = temp[i].v[1][axis ^ 1];
            spans[out].v[2][axis] = tex;
            spans[out].v[2][axis ^ 1] = temp[i].v[2][axis ^ 1];
            out++;
        } else {
            spans[out] = temp[i];
            out++;
        }
    }
    *pCount = out;
}

typedef struct {
    s16 pos;
    u8 r;
    u8 g;
    u8 b;
    u8 pad;
} TintKeyframe;

extern TintKeyframe D_80754F58[];

void gfxGetBackgroundTint(s16 yPos, u8 *outR, u8 *outG, u8 *outB) {
    u8 idx;
    TintKeyframe *key;
    f32 t;

    switch (gCurrentMap) {
        case 0xE:
            idx = 0;
            while (yPos < D_80754F58[idx + 1].pos) {
                idx++;
            }
            key = &D_80754F58[idx];
            t = (f32)(yPos - D_80754F58[idx + 1].pos) / (f32)(key->pos - D_80754F58[idx + 1].pos);
            *outR = D_80754F58[idx + 1].r + (f32)(key->r - D_80754F58[idx + 1].r) * t;
            *outG = D_80754F58[idx + 1].g + (f32)(key->g - D_80754F58[idx + 1].g) * t;
            *outB = D_80754F58[idx + 1].b + (f32)(key->b - D_80754F58[idx + 1].b) * t;
            return;
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x4A:
        case 0x4B:
        case 0x7C:
        case 0x7D:
        case 0x7E:
        case 0x7F:
        case 0x80:
            *outR = 0x3F;
            *outG = 0x3F;
            *outB = 0x3F;
            return;
        default:
            *outR = 0xFF;
            *outG = 0xFF;
            *outB = 0xFF;
            return;
    }
}

extern Mtx D_807FD8A8[];
extern f32 D_80754CE4;

Gfx *gfxDrawRotatedTiledBackground(Gfx *glist, f32 rotX, f32 rotY, s32 assetId, f32 width, f32 height) {
    f32 scrollU;
    f32 scrollV;
    s32 i;
    RectSpan spans[5];
    u8 count;
    Actor *playerActor;
    PlayerState *playerState;
    f32 inv;
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    u8 r;
    u8 g;
    u8 b;
    f32 scale;

    scale = 5.6f / D_80754CE4;
    playerActor = gPlayerSlots->actor;
    playerState = playerActor->customState;
    guScaleF(mtxA, scale, scale, scale);
    guTranslateF(mtxB, -2560.0f, -1920.0f, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    inv = (f32)((0x1000 - playerState->camActor->pitch) & 0xFFF); // FAKE: inv doubles as the roll angle; a separate f32 angle adds a home and grows the frame 0x1B0 -> 0x1B8
    inv *= 0.087890625f;
    guRotateF(mtxB, inv, 0, 0, 1);
    guMtxCatF(mtxA, mtxB, mtxA);
    guTranslateF(mtxB, 2560.0f, 1920.0f, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, &D_807FD8A8[gGfxBufferIndex]);
    rotX = 6.2831855f - rotX;
    rotY = (width / height) * (6.2831855f - rotY);
    if (D_807FD8A0 == 0) {
        D_807FD8A0 = assetLoad(0xE, assetId, 0, 0);
    }
    gSPMatrix(glist++, &D_807FD8A8[gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glist++, &D_807FD928, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPPipeSync(glist++);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0x404240);
    gDPSetCombineMode(glist++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0);
    gfxGetBackgroundTint(playerActor->y, &r, &g, &b);
    gDPSetPrimColor(glist++, 0, 0, r, g, b, 0xFF);
    gSPClearGeometryMode(glist++, 0xFFFFFF);
    gSPSetGeometryMode(glist++, 0x200004);
    scrollU = rotX * 0.15915494f * D_80754CE4;
    scrollV = rotY * 0.15915494f * D_80754CE4;
    inv = 1.0f / scale;
    while (scrollU > 1.0f) {
        scrollU -= 1.0f;
    }
    while (scrollV > 1.0f) {
        scrollV -= 1.0f;
    }
    scrollU = scrollU * width;
    scrollV = scrollV * height;
    spans[0].v[0][0] = scrollU - 460.0f * inv * 0.5f;
    spans[0].v[0][1] = scrollV - 380.0f * inv * 0.5f;
    spans[0].v[1][0] = 460.0f * inv * 0.5f + scrollU;
    spans[0].v[1][1] = 380.0f * inv * 0.5f + scrollV;
    spans[0].v[2][1] = spans[0].v[2][0] = -70.0f * inv;
    count = 1;
    gfxWrapRectSpan(spans, &count, 0, width);
    gfxWrapRectSpan(spans, &count, 1, height);
    for (i = 0; i < count; i++) {
        gfxDrawTexturedTileGridSimple(&glist, D_807FD8A0, 0, (u32)width, (u32)height, 0x20, 0x20, spans[i].v[0][0], spans[i].v[0][1], spans[i].v[1][0], spans[i].v[1][1], spans[i].v[2][0], spans[i].v[2][1], 0x10, 0x10);
    }
    return glist;
}

extern s16 D_80754CE0;
extern s16 D_80754CEC[];
extern s16 D_80754F70;
extern s16 D_80754F74;

Gfx *gfxBuildScrollingBackground(Gfx *dl) {
    s32 x;
    s32 i;
    s32 j;
    s32 n;
    s32 y;
    s32 y2;
    u16 k;
    s16 scroll;
    void *tex;

    gSPClearGeometryMode(dl++, 0xFFFFFF);
    gSPSetGeometryMode(dl++, G_SHADE | G_SHADING_SMOOTH);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    gDPSetCombineMode(dl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetTexturePersp(dl++, G_TP_NONE);
    gDPSetTextureFilter(dl++, G_TF_POINT);
    gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPPipeSync(dl++);
    scroll = D_80754F74 + D_80754CE0;
    if (scroll < 0) {
        scroll += 0x200;
    }
    if (scroll >= 0x200) {
        scroll -= 0x200;
    }
    if (D_807FD978[0] == NULL) {
        for (n = 0; n < 8; n++) {
            D_807FD978[n] = assetLoad(0x19, D_80754CEC[n], 0, 0);
        }
    }
    k = 0;
    for (j = 0x40; j >= 0; j -= 0x40) {
        i = 0;
        y = (j << 2) - scroll;
        do {
            gDPPipeSync(dl++);
            tex = D_807FD978[k];
            gDPLoadTextureBlock(dl++, (u32)tex + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            x = (i << 2) - D_80754F70;
            for (n = 0; n < 4; n++) {
                y2 = y;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                y2 += 0x200;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                y2 += 0x200;
                gSPScisTextureRectangle(dl++, x, y2, x + 0x80, y2 + 0x100, 0, 0, 0x7FF, 0x400, -0x400);
                x += 0x200;
            }
            k++;
            i += 0x20;
        } while (i != 0x80);
    }
    i = (s16)(D_80754F70 + 4); // FAKE: loop counter i reused for the new scroll value; a separate local adds a home and grows the frame 0x100 -> 0x108
    D_80754F74 += 4;
    *(s16 *)((u8 *)D_80754F58 + 0x18) = i; // FAKE: D_80754F70 stored via D_80754F58+0x18 keeps a separate lui at/sh (no lda web in v1, Q0255)
    if (i >= 0x200) {
        *(s16 *)((u8 *)D_80754EF8 + 0x78) = 0; // FAKE: D_80754F70 stored via D_80754EF8+0x78 keeps a separate lui at/sh (Q0255)
    }
    if (D_80754F74 >= 0x200) {
        D_80754F74 = 0;
    }
    gDPPipeSync(dl++);
    gDPSetTexturePersp(dl++, G_TP_PERSP);
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    return dl;
}

extern s16 gGfxScreenLeft;
extern s16 gGfxScreenTop;
extern s16 gGfxScreenRight;
extern s16 gGfxScreenBottom;

Gfx *gfxClearScreenSetViewportScissor(Gfx *glist) {
    gDPPipeSync(glist++);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
    gDPSetFillColor(glist++, 0x00010001);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight, gGfxScreenBottom);
    gDPFillRectangle(glist++, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight - 1, gGfxScreenBottom - 1);
    gDPPipeSync(glist++);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, gPlayerSlots->rect[0], gPlayerSlots->rect[1], gPlayerSlots->rect[2], gPlayerSlots->rect[3]);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0);
    return glist;
}

extern f32 gScreenFadeRate;
extern u8 D_8076AEE0;
extern s16 D_807FD800;

Gfx *gfxDrawMapBackground(Gfx *dl, f32 rotX, f32 rotY, Mtx *mtx, s16 player) {
    f32 x;
    f32 intensity;
    f32 z;
    f32 dist;

    gDPPipeSync(dl++);
    if ((gScreenFadeRate != 0.0f) && (D_8076AEE0 == 3)) {
        dl = gfxClearScreenSetViewportScissor(dl);
    }
    switch (gCurrentMap) {
    case 0x53:
    case 0x9A:
    case 0xC5:
    case 0xC6:
        return dl;
    case 0xE:
        dl = gfxDrawRotatedTiledBackground(dl, rotX, rotY, 0x2D, 320.0f, 240.0f);
        break;
    case 0x3:
    case 0xB:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x4A:
    case 0x4B:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
    case 0x80:
        dl = gfxDrawRotatedTiledBackground(dl, rotX, rotY, 0x2E, 320.0f, 240.0f);
        break;
    case 0x26:
        switch (gPlayerSlots->unk290) {
        case 0:
        case 1:
        case 3:
        case 6:
        case 8:
        case 10:
            dl = gfxClearScreenSetViewportScissor(dl);
            break;
        default:
            lensFlareAddFromAngle(0x3E8, 0x4E20, 0);
            dl = gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 0, 0, 0, -1, 0.0f);
            break;
        }
        break;
    case 0x1E:
        if (((gPlayerSlots->unk290 != 7) && (gPlayerSlots->unk290 != 6) && (gPlayerSlots->unk290 != 8) && (gPlayerSlots->unk290 != 0)) || (D_807FD800 != 0)) {
            dl = gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 0, 0, ((gPrimaryPlayerActor->chunkIndex == 9) || (gPrimaryPlayerActor->chunkIndex == 0xB) || (gPrimaryPlayerActor->chunkIndex == 3)) ? 1 : 0, 9, 0.0f);
        }
        break;
    case 0x27:
        lensFlareAddFromAngle(0xBB8, 0x2328, 0);
        dl = gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 0, 0, 0, -1, 0.0f);
        break;
    case 0x4:
        dl = gfxClearScreenSetViewportScissor(dl);
        break;
    case 0xB0:
        dl = gfxClearScreenSetViewportScissor(dl);
        break;
    case 0x7:
        switch (gPlayerSlots->unk290) {
        case 8:
        case 9:
        case 12:
        case 16:
            dl = gfxClearScreenSetViewportScissor(dl);
            break;
        case 11:
        case 14:
            lensFlareAddFromAngle(0, 0x7530, 1);
            dl = gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 4, 4, 1, -1, 0.0f);
            break;
        default:
            lensFlareAddFromAngle(0, 0x7530, 0);
            dl = gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 4, 4, 0, -1, 0.0f);
            break;
        }
        break;
    case 0x8:
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 3, 3, 1, -1, 0.0f), 0, 0x7D00, 0);
        break;
    case 0x30:
        if ((gPlayerSlots->unk290 >= 0xC) && (gPlayerSlots->unk290 < 0x12)) {
            dl = gfxClearScreenSetViewportScissor(dl);
        } else {
            lensFlareAddFromAngle(0, 0x5DC0, 1);
            dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 2, 2, 1, -1, 0.0f), 0, 0x5DC0, 1);
        }
        break;
    case 0x37:
        dl = gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 1, 1, 1, -1, 0.0f);
        break;
    case 0x22:
        if (camIsCutsceneActive() != 0) {
            x = gPlayerSlots->camX;
            z = gPlayerSlots->camZ;
        } else {
            x = gPrimaryPlayerActor->x;
            z = gPrimaryPlayerActor->z;
        }
        dist = sqrtf(((x - 3000.0f) * (x - 3000.0f)) + ((z - 5000.0f) * (z - 5000.0f)));
        if (dist < 2500.0f) {
            intensity = ((2500.0f - dist) / 1000.0f > 1.0) ? 1.0 : (2500.0f - dist) / 1000.0f;
            func_8068B830(2.0f + intensity, intensity * 400.0f, intensity * 30.0f);
            enemyAggroSetIntensityBB(intensity * -0.6 + 1.0);
        } else {
            enemyAggroDespawnBB();
            enemyAggroSetIntensityBB(1.0f);
        }
        lensFlareAddFromAngle(0xBB8, 0x4E20, 0);
        dl = gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 5, 6, 1, -1, 0.0f);
        break;
    case 0x99:
    case 0xAC:
        lensFlareAddFromAngle(0xBB8, 0x4E20, 0);
        dl = gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 5, 5, 1, -1, 0.0f);
        break;
    case 0x6F:
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 6, 6, 1, -1, 0.0f), 0xC8, 0x4268, 0);
        break;
    case 0x57:
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 6, 6, 1, -1, 0.0f), 0x3E8, 0x2EE0, 0);
        break;
    case 0xD5:
        lensFlareAddFromAngle(0x8FC, 0x1388, 0);
        dl = gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 7, 7, 0, -1, 0.0f);
        break;
    case 0xD0:
        gDPSetFillColor(dl++, 0xFFFFFFFF);
        goto fill;
    case 0x36:
        gDPSetFillColor(dl++, 0xFFC1FFC1);
        goto fill;
    case 0x50:
        lensFlareAddFromAngle(0x8FC, 0x1388, 1);
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, rotX, rotY, mtx, 7, 6, 0, -1, gBackgroundBlend), 0xC8, 0x2EE0, 2);
        break;
    default:
        gDPSetFillColor(dl++, 0x10001);
    fill:
        gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0);
        gDPSetCycleType(dl++, G_CYC_FILL);
        gDPFillRectangle(dl++, gPlayerSlots[player].rect[0], gPlayerSlots[player].rect[1], gPlayerSlots[player].rect[2] - 1, gPlayerSlots[player].rect[3] - 1);
        gDPPipeSync(dl++);
        gDPSetCycleType(dl++, G_CYC_1CYCLE);
        break;
    }
    gBackgroundBlend = 0.0f;
    gDPPipeSync(dl++);
    return dl;
}

extern s32 gGlobalPauseFlags;
extern s32 D_807552EC;

Gfx *gfxDrawPlayerViewBackground(Gfx *glist, s16 player) {
    s32 clearView;

    if ((gPlayerCount >= 2) || !(gGlobalPauseFlags & 0x10)) {
        if (gCurrentMap == 0x50) {
            glist = gfxBuildScrollingBackground(glist);
        } else {
            clearView = !(gGlobalPauseFlags & 2);
            if (gPlayerCount >= 2) {
                s32 forceClear;
                if (gGfxBufferIndex == 0) {} // FAKE: dead read of gGfxBufferIndex ends a block before the 0xBE test: the !(flags & 2) value stays in a1 and draw_black in a2 (they swap without it)
                if (gCurrentMap == 0xBE) {
                    forceClear = 0;
                } else {
                    forceClear = 1;
                }
                forceClear |= (D_807552EC >= 2);
                clearView |= forceClear;
            }
            if (clearView == 0) {
                return glist;
            }
            gDPPipeSync(glist++);
            gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
            gDPSetFillColor(glist++, 0x00010001);
            gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
            gDPFillRectangle(glist++, gPlayerSlots[player].rect[0], gPlayerSlots[player].rect[1], gPlayerSlots[player].rect[2] - 1, gPlayerSlots[player].rect[3] - 1);
            gDPPipeSync(glist++);
            gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0);
        }
    } else {
        glist = gfxDrawMapBackground(glist, gPlayerSlots[player].bgRotX, gPlayerSlots[player].bgRotY, &gPlayerSlots[player].bgMtx[gGfxBufferIndex], player);
    }
    return glist;
}

void gfxSetBackgroundBlend(f32 blend) {
    if (blend < 0.0) {
        blend = 0.0f;
    }
    if (blend > 1.0) {
        blend = 1.0f;
    }
    gBackgroundBlend = blend;
}
