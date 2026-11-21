#include "common.h"
#include "actor.h"
#include "proto/global/41090.h"
#include "proto/global/5DE10.h"
#include "proto/global/6AD90.h"

extern s32 gCurrentMap;

typedef struct {
    void (*init)(void);
    Gfx *(*draw)(Gfx *);
    void (*update)(void);
    u8 active;
} MapSurfaceEffect;

typedef struct {
    s16 assetId;
    void *data;
} AssetRef;

MapSurfaceEffect gMapSurfaceEffects[8] = {
    { NULL, NULL, NULL, 0 },
    { envTextureInitWater, envTextureDrawWater, envTextureUpdateWaterScroll, 0 },
    { envTextureInitAsset565, envTextureDrawMipChain, envTextureUpdateScroll78, 0 },
    { envTextureInitAsset3B7, envTextureDrawDualScroll, envTextureUpdateScroll80, 0 },
    { envTextureInitAsset3B9, envTextureDrawLayered, envTextureUpdateScroll8C, 0 },
    { envTextureInitAsset3BB, envTextureDrawFlipbook, envTextureUpdateScroll98, 0 },
    { envTextureInitAsset3BC, envTextureDrawScrollOnly, envTextureUpdateScrollA0, 0 },
    { envTextureInitAsset3BD, envTextureDrawSingleScroll, envTextureUpdateScrollAC, 0 },
};
f32 gEnvLayeredFastScroll = 0.0f;
f32 gEnvLayeredSlowScroll = 0.0f;
s16 gEnvLayeredFogAlpha = 150;
AssetRef gEnvFlipbookFrames[11] = {
    { 0x3AC, NULL }, { 0x3AD, NULL }, { 0x3AE, NULL }, { 0x3AF, NULL },
    { 0x3B0, NULL }, { 0x3B1, NULL }, { 0x3B2, NULL }, { 0x3B3, NULL },
    { 0x3B4, NULL }, { 0x3B5, NULL }, { 0x3B6, NULL },
};
s32 D_80747E64 = 150; // unreferenced; its label is gEnvFlipbookFrames's loop-end address
extern f32 gEnvWaterFastScroll;
extern f32 gEnvWaterSlowScroll;
extern f32 gEnvMipChainScroll;
extern void *gEnvMipChainTexture;


void mapSurfaceEffectsReset(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        gMapSurfaceEffects[i].active = 0;
    }
}

void mapSurfaceEffectInit(s16 effectIdx) {
    if (gMapSurfaceEffects[effectIdx].active == 0) {
        gMapSurfaceEffects[effectIdx].init();
        gMapSurfaceEffects[effectIdx].active = 1;
    }
}

Gfx *mapSurfaceEffectDraw(Gfx *gdl, s16 effectIdx) {
    return gMapSurfaceEffects[effectIdx].draw(gdl);
}

void mapSurfaceEffectsUpdate(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gMapSurfaceEffects[i].active != 0) {
            gMapSurfaceEffects[i].update();
        }
    }
}

void envTextureInitWater(void) {
    gEnvWaterFastScroll = 255.0f;
    gEnvWaterSlowScroll = 255.0f;
}

Gfx *envTextureDrawWater(Gfx *g) {
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200404);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 3, 1, 1);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C192008);
    gDPSetCombine(g++, 0x1114C0, 0xFFFFFEFC);
    gDPSetEnvColor(g++, 0, 0x40, 0x7F, 0xFF);
    gDPSetPrimColor(g++, 0, 0, 0x50, 0x50, 0xB4, 0x46);
    gDPSetTileSize(g++, 1, (s32)gEnvWaterFastScroll, 0, 0x7C, 0x7C);
    gDPSetTile(g++, 4, 1, 0, 0, 7, 0, 1, 5, 0, 1, 5, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x200);
    gDPTileSync(g++);
    gDPSetTile(g++, 4, 1, 4, 0, 1, 0, 0, 5, 0, 0, 5, 15);
    gDPSetTileSize(g++, 2, (s32)gEnvWaterSlowScroll, 0, 0x7C, 0x7C);
    gDPSetTile(g++, 3, 1, 0, 0x100, 7, 0, 1, 5, 0, 1, 5, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x200);
    gDPTileSync(g++);
    gDPSetTile(g++, 3, 1, 4, 0x100, 2, 0, 0, 5, 0, 0, 5, 15);
    return g;
}

void envTextureUpdateWaterScroll(void) {
    gEnvWaterFastScroll -= 1.0;
    if (gEnvWaterFastScroll < 0.0) {
        gEnvWaterFastScroll = 255.0f;
    }
    gEnvWaterSlowScroll -= 0.439;
    if (gEnvWaterSlowScroll < 0.0) {
        gEnvWaterSlowScroll = 255.0f;
    }
}

void envTextureInitAsset565(void) {
    gEnvMipChainScroll = 255.0f;
    gEnvMipChainTexture = assetLoad(0x19, 0x565, 1, 0);
}

Gfx *envTextureDrawMipChain(Gfx *g) {
    s32 i;
    s32 w;
    s32 h;
    s32 tmem;
    s32 maskBits;
    s32 line;

    tmem = 0;
    w = 0x20;
    h = 0x20;
    maskBits = 5;
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200405);
    gDPSetTextureImage(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gEnvMipChainTexture);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, tmem, 7, 0, 0, 0, 0, 0, 0, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x7FF, 0);
    tmem = 0;
    for (i = 0; i < 4; i++) {
        line = (w + 3) / 4;
        gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, line, tmem, i, 0, 0, maskBits, i, 0, maskBits, i);
        gDPSetTileSize(g++, i, 2, (s32)gEnvMipChainScroll, ((w - 1) << 2) + 2, ((h - 1) << 2) + 2);
        tmem += line * h;
        w >>= 1; h >>= 1; // LAYOUT: both shifts on one line keep as1's sra order (split: the two sra swap)
        maskBits--;
    }
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    if (fogGetEnabled()) {
        gSPSetGeometryMode(g++, 0x10000);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0xC8112230);
    } else {
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C192230);
    }
    gDPSetCombine(g++, 0x26A004, 0x1F1093FF);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 3, 0, 1);
    return g;
}

void envTextureUpdateScroll78(void) {
    gEnvMipChainScroll -= 1.0;
    if (gEnvMipChainScroll < 0.0) {
        gEnvMipChainScroll = 255.0f;
    }
}

extern f32 gEnvDualFastScroll;
extern f32 gEnvDualSlowScroll;
extern void *gEnvDualFastTexture;
extern void *D_807F618C;

void envTextureInitAsset3B7(void) {
    gEnvDualFastScroll = 255.0f;
    gEnvDualSlowScroll = 255.0f;
    gEnvDualFastTexture = assetLoad(7, 0x3B7, 0, 0);
    D_807F618C = assetLoad(7, 0x3B8, 0, 0);
}

Gfx *envTextureDrawDualScroll(Gfx *g) {
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200005);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 1, 1, 1);
    if (fogGetEnabled()) {
        gSPSetGeometryMode(g++, 0x10000);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0xC8104A50);
    } else {
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
    }
    gDPSetCombine(g++, 0xFFFE41, 0xFFFFFFD3);
    switch (gCurrentMap) {
        case 1:
            gDPSetPrimColor(g++, 0, 0, 255, 255, 255, 0xB4);
            break;
        case 0:
        case 4:
        case 7:
        case 14:
            gDPSetPrimColor(g++, 0, 0, 255, 255, 255, 0x50);
            break;
        case 16:
            gDPSetPrimColor(g++, 0, 0, 255, 255, 255, 0x3C);
            break;
        case 12:
            gDPSetPrimColor(g++, 0, 0, 255, 255, 255, 0x96);
            break;
        default:
            gDPSetPrimColor(g++, 0, 0, 255, 255, 255, 0x50);
            break;
    }
    gDPSetTileSize(g++, 1, 0, (s32)gEnvDualFastScroll, 0x7C, 0x7C);
    gDPSetTextureImage(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gEnvDualFastTexture);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 5, 0, 0, 5, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x200);
    gDPTileSync(g++);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 1, 0, 0, 5, 0, 0, 5, 0);
    gDPSetTileSize(g++, 2, 0, (s32)gEnvDualSlowScroll, 0x7C, 0x7C);
    gDPSetTextureImage(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_807F618C);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x100, 7, 0, 0, 5, 0, 0, 5, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x200);
    gDPTileSync(g++);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x100, 2, 0, 0, 5, 0, 0, 5, 0);
    return g;
}

void envTextureUpdateScroll80(void) {
    gEnvDualFastScroll -= 1.234;
    if (gEnvDualFastScroll < 0.0) {
        gEnvDualFastScroll = 255.0f;
    }
    gEnvDualSlowScroll -= 0.45;
    if (gEnvDualSlowScroll < 0.0) {
        gEnvDualSlowScroll = 255.0f;
    }
}

extern void *gEnvLayeredTexture;

void envTextureInitAsset3B9(void) {
    gEnvLayeredTexture = assetLoad(7, 0x3E0, 1, 0);
}

Gfx *envTextureDrawLayered(Gfx *g) {
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200005);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 1, 1, 1);
    if (fogGetEnabled()) {
        gSPSetGeometryMode(g++, 0x10000);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0xC8104A50);
        gDPSetCombine(g++, 0xFF9441, 0xFF0FFFFF);
        gDPSetPrimColor(g++, 0, 0, 255, 255, 255, gEnvLayeredFogAlpha);
    } else {
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
        gDPSetCombine(g++, 0xFF9441, 0xFF13FFFF);
    }
    gDPLoadTextureBlock(g++, (u32)gEnvLayeredTexture - 0x80000000, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(g++, 1, 0, (s32)gEnvLayeredFastScroll, 0xFC, 0xFC);
    gDPSetTile(g++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 1, 0, 0, 6, 1, 0, 6, 1);
    gDPSetTileSize(g++, 2, 0, (s32)gEnvLayeredSlowScroll, 0xFC, 0xFC);
    gDPSetTile(g++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 2, 0, 0, 6, 1, 0, 6, 1);
    return g;
}

void envTextureUpdateScroll8C(void) {
    gEnvLayeredFastScroll -= 5.0;
    if (gEnvLayeredFastScroll < 0.0) {
        gEnvLayeredFastScroll = 255.0f;
    }
    gEnvLayeredSlowScroll -= 2.0;
    if (gEnvLayeredSlowScroll < 0.0) {
        gEnvLayeredSlowScroll = 255.0f;
    }
}

extern u8 gEnvFlipbookFrame;

void envTextureInitAsset3BB(void) {
    s32 i;

    gEnvFlipbookFrame = 0;
    for (i = 0; i < 11; i++) {
        gEnvFlipbookFrames[i].data = assetLoad(7, gEnvFlipbookFrames[i].assetId, 1, 0);
    }
}

Gfx *envTextureDrawFlipbook(Gfx *g) {
    void *tex;

    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200405);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 0, 0, 1);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
    gDPSetCombine(g++, 0xFFFFFF, 0xFFFCF279);
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, 255);
    tex = gEnvFlipbookFrames[gEnvFlipbookFrame].data;
    gDPLoadTextureBlock(g++, (u32)tex - 0x80000000, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0, G_TX_WRAP, G_TX_WRAP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
    return g;
}

void envTextureUpdateScroll98(void) {
    gEnvFlipbookFrame++;
    if (gEnvFlipbookFrame == 11) {
        gEnvFlipbookFrame = 0;
    }
}

extern f32 gEnvScrollOnlyOffset;

void envTextureInitAsset3BC(void) {
    gEnvScrollOnlyOffset = 0.0f;
}

Gfx *envTextureDrawScrollOnly(Gfx *g) {
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200405);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 0, 0, 1);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
    gDPSetCombine(g++, 0x121804, 0xFF13FFFF);
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, 255);
    gDPSetTileSize(g++, 0, 0, (s32)gEnvScrollOnlyOffset, 0xFC, 0xFC);
    return g;
}

void envTextureUpdateScrollA0(void) {
    gEnvScrollOnlyOffset -= 0.865;
    if (gEnvScrollOnlyOffset < 0.0) {
        gEnvScrollOnlyOffset = 255.0f;
    }
}

extern void *D_807F619C;
extern f32 gEnvSingleScroll;

void envTextureInitAsset3BD(void) {
    D_807F619C = assetLoad(0x19, 0x1765, 1, 0);
}

Gfx *envTextureDrawSingleScroll(Gfx *g) {
    s32 alpha;

    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200405);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 0, 0, 1);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
    gDPSetCombine(g++, 0x121803, 0xFF0FFFFF);
    switch (gCurrentMap) {
        case 0x22:
        case 0xBB:
            alpha = 0xFF;
            break;
        case 0x36:
        case 0xBC:
            alpha = 0x96;
            break;
        default:
            alpha = 0x50;
            break;
    }
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, alpha);
    gDPLoadTextureBlock(g++, (u32)D_807F619C - 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(g++, 0, 0, (s32)gEnvSingleScroll, 0x7C, 0x7C);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 1, 0, 0, 5, 0, 0, 5, 0);
    return g;
}

void envTextureUpdateScrollAC(void) {
    switch (gCurrentMap) {
        case 0xBB:
            gEnvSingleScroll -= 2.0;
            break;
        case 0xBC:
            gEnvSingleScroll -= 1.0;
            break;
        default:
            gEnvSingleScroll -= 1.0;
            break;
    }
    if (gEnvSingleScroll < 0.0) {
        gEnvSingleScroll = 255.0f;
    }
}
