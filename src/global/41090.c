#include "common.h"
#include "actor.h"

extern s32 D_8076A0A8;

typedef struct {
    void (*unk0)();
    void (*unk4)();
    void (*unk8)();
    u8 unkC;
} MapSurfaceEffect;

extern MapSurfaceEffect D_80747D80[8];
extern f32 D_807F6170;
extern f32 D_807F6174;
extern f32 D_807F6178;
extern void *D_807F617C;

void *assetLoad(s32, s32, s32, s32);
u8 fogGetEnabled(void);

void mapSurfaceEffectsReset(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_80747D80[i].unkC = 0;
    }
}

void mapSurfaceEffectInit(s16 arg0) {
    if (D_80747D80[arg0].unkC == 0) {
        D_80747D80[arg0].unk0();
        D_80747D80[arg0].unkC = 1;
    }
}

void mapSurfaceEffectDraw(s32 arg0, s16 arg1) {
    D_80747D80[arg1].unk4(arg0);
}

void mapSurfaceEffectsUpdate(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_80747D80[i].unkC != 0) {
            D_80747D80[i].unk8();
        }
    }
}

void func_8063C4A8(void) {
    D_807F6170 = 255.0f;
    D_807F6174 = 255.0f;
}

Gfx *func_8063C4C4(Gfx *g) {
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
    gDPSetTileSize(g++, 1, (s32)D_807F6170, 0, 0x7C, 0x7C);
    gDPSetTile(g++, 4, 1, 0, 0, 7, 0, 1, 5, 0, 1, 5, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x200);
    gDPTileSync(g++);
    gDPSetTile(g++, 4, 1, 4, 0, 1, 0, 0, 5, 0, 0, 5, 15);
    gDPSetTileSize(g++, 2, (s32)D_807F6174, 0, 0x7C, 0x7C);
    gDPSetTile(g++, 3, 1, 0, 0x100, 7, 0, 1, 5, 0, 1, 5, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x200);
    gDPTileSync(g++);
    gDPSetTile(g++, 3, 1, 4, 0x100, 2, 0, 0, 5, 0, 0, 5, 15);
    return g;
}

void func_8063C6D8(void) {
    D_807F6170 -= 1.0;
    if (D_807F6170 < 0.0) {
        D_807F6170 = 255.0f;
    }
    D_807F6174 -= 0.439;
    if (D_807F6174 < 0.0) {
        D_807F6174 = 255.0f;
    }
}

void func_8063C784(void) {
    D_807F6178 = 255.0f;
    D_807F617C = assetLoad(0x19, 0x565, 1, 0);
}

Gfx *func_8063C7C4(Gfx *g) {
    s32 i;
    s32 w;
    s32 h;
    s32 tmem;
    s32 j;
    s32 line;

    tmem = 0;
    w = 0x20;
    h = 0x20;
    j = 5;
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200405);
    gDPSetTextureImage(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_807F617C);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x7FF, 0);
    tmem = 0;
    for (i = 0; i < 4; i++) {
        line = (w + 3) / 4;
        gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, line, tmem, i, 0, 0, j, i, 0, j, i);
        gDPSetTileSize(g++, i, 2, (s32)D_807F6178, ((w - 1) << 2) + 2, ((h - 1) << 2) + 2);
        tmem += line * h;
        w >>= 1; h >>= 1;
        j--;
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

void func_8063CA7C(void) {
    D_807F6178 -= 1.0;
    if (D_807F6178 < 0.0) {
        D_807F6178 = 255.0f;
    }
}

extern f32 D_807F6180;
extern f32 D_807F6184;
extern void *D_807F6188;
extern void *D_807F618C;

void func_8063CADC(void) {
    D_807F6180 = 255.0f;
    D_807F6184 = 255.0f;
    D_807F6188 = assetLoad(7, 0x3B7, 0, 0);
    D_807F618C = assetLoad(7, 0x3B8, 0, 0);
}

Gfx *func_8063CB40(Gfx *g) {
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
    switch (D_8076A0A8) {
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
    gDPSetTileSize(g++, 1, 0, (s32)D_807F6180, 0x7C, 0x7C);
    gDPSetTextureImage(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_807F6188);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 5, 0, 0, 5, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x200);
    gDPTileSync(g++);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 1, 0, 0, 5, 0, 0, 5, 0);
    gDPSetTileSize(g++, 2, 0, (s32)D_807F6184, 0x7C, 0x7C);
    gDPSetTextureImage(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_807F618C);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x100, 7, 0, 0, 5, 0, 0, 5, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x200);
    gDPTileSync(g++);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x100, 2, 0, 0, 5, 0, 0, 5, 0);
    return g;
}

void func_8063CE64(void) {
    D_807F6180 -= 1.234;
    if (D_807F6180 < 0.0) {
        D_807F6180 = 255.0f;
    }
    D_807F6184 -= 0.45;
    if (D_807F6184 < 0.0) {
        D_807F6184 = 255.0f;
    }
}

extern void *D_807F6190;

void func_8063CF0C(void) {
    D_807F6190 = assetLoad(7, 0x3E0, 1, 0);
}

extern f32 D_80747E00;
extern f32 D_80747E04;
extern s16 D_80747E08;

Gfx *func_8063CF3C(Gfx *g) {
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
        gDPSetPrimColor(g++, 0, 0, 255, 255, 255, D_80747E08);
    } else {
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
        gDPSetCombine(g++, 0xFF9441, 0xFF13FFFF);
    }
    gDPSetTextureImage(g++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, (u32)D_807F6190 - 0x80000000);
    gDPSetTile(g++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 6, 0, 0, 6, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x7FF, 0x100);
    gDPPipeSync(g++); gDPSetTile(g++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 0, 0, 0, 6, 0, 0, 6, 0); gDPSetTileSize(g++, 0, 0, 0, 0xFC, 0xFC);
    gDPSetTileSize(g++, 1, 0, (s32)D_80747E00, 0xFC, 0xFC);
    gDPSetTile(g++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 1, 0, 0, 6, 1, 0, 6, 1);
    gDPSetTileSize(g++, 2, 0, (s32)D_80747E04, 0xFC, 0xFC);
    gDPSetTile(g++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 2, 0, 0, 6, 1, 0, 6, 1);
    return g;
}

void func_8063D1D8(void) {
    D_80747E00 -= 5.0;
    if (D_80747E00 < 0.0) {
        D_80747E00 = 255.0f;
    }
    D_80747E04 -= 2.0;
    if (D_80747E04 < 0.0) {
        D_80747E04 = 255.0f;
    }
}

typedef struct {
    s16 unk0;
    void *unk4;
} AssetRef;

extern AssetRef D_80747E0C[11];
extern u8 D_807F6194;

void func_8063D288(void) {
    s32 i;

    D_807F6194 = 0;
    for (i = 0; i < 11; i++) {
        D_80747E0C[i].unk4 = assetLoad(7, D_80747E0C[i].unk0, 1, 0);
    }
}

Gfx *func_8063D2E4(Gfx *g) {
    u32 tex;

    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200405);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 0, 0, 1);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
    gDPSetCombine(g++, 0xFFFFFF, 0xFFFCF279);
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, 255);
    tex = (u32)D_80747E0C[D_807F6194].unk4;
    gDPSetTextureImage(g++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, tex - 0x80000000);
    gDPSetTile(g++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 5, 0, 0, 6, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x100);
    gDPPipeSync(g++);
    gDPSetTile(g++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 0, 0, 0, 5, 0, 0, 6, 0); gDPSetTileSize(g++, 0, 0, 0, 0xFC, 0x7C);
    return g;
}

void func_8063D468(void) {
    D_807F6194++;
    if (D_807F6194 == 11) {
        D_807F6194 = 0;
    }
}

extern f32 D_807F6198;

void func_8063D494(void) {
    D_807F6198 = 0.0f;
}

Gfx *func_8063D4A4(Gfx *g) {
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200405);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 0, 0, 1);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
    gDPSetCombine(g++, 0x121804, 0xFF13FFFF);
    gDPSetPrimColor(g++, 0, 0, 255, 255, 255, 255);
    gDPSetTileSize(g++, 0, 0, (s32)D_807F6198, 0xFC, 0xFC);
    return g;
}

void func_8063D5AC(void) {
    D_807F6198 -= 0.865;
    if (D_807F6198 < 0.0) {
        D_807F6198 = 255.0f;
    }
}

extern void *D_807F619C;
extern f32 D_807F61A0;

void func_8063D608(void) {
    D_807F619C = assetLoad(0x19, 0x1765, 1, 0);
}

Gfx *func_8063D638(Gfx *g) {
    s32 alpha;

    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200405);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 0, 0, 1);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C184A50);
    gDPSetCombine(g++, 0x121803, 0xFF0FFFFF);
    switch (D_8076A0A8) {
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
    gDPSetTextureImage(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (u32)D_807F619C - 0x80000000);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 5, 0, 0, 5, 0);
    gDPLoadSync(g++); gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x100); gDPPipeSync(g++); gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0);
    gDPSetTileSize(g++, 0, 0, 0, 0x7C, 0x7C);
    gDPSetTileSize(g++, 0, 0, (s32)D_807F61A0, 0x7C, 0x7C);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 1, 0, 0, 5, 0, 0, 5, 0);
    return g;
}

void func_8063D854(void) {
    switch (D_8076A0A8) {
        case 0xBB:
            D_807F61A0 -= 2.0;
            break;
        case 0xBC:
            D_807F61A0 -= 1.0;
            break;
        default:
            D_807F61A0 -= 1.0;
            break;
    }
    if (D_807F61A0 < 0.0) {
        D_807F61A0 = 255.0f;
    }
}
