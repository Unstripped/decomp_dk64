#include "common.h"
#include "actor.h"
#include "proto/global/103AB0.h"
#include "proto/global/109660.h"
#include "proto/global/17800.h"
#include "proto/global/201B0.h"
#include "proto/global/5E2F0.h"
#include "proto/global/6AD90.h"
#include "proto/global/8F4B0.h"
#include "proto/global/90D80.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern u8 gPlayerInventoryTable[][0x5E];
extern s32 gCurrentMap;
extern u8 gCurrentWorldId;
extern u8 gScreenRenderFlags;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gNextGameMode;
extern u8 gGfxBufferIndex;

typedef struct {
    s8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
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
    for (; D_80750840[i].unk0 != -1; i++) {
        if (((D_80750840[i].unk0 == 2) && ((s32)gPlayerCount >= 2) && (D_80750840[i].unk2 & D_80750ABC)) || ((gPlayerCount == D_80750840[i].unk0) && (gSplitScreenMode == D_80750840[i].unk1) && (D_80750840[i].unk2 & D_80750ABC))) {
            Gfx *_g = (Gfx *)(dl++);
            _g->words.w0 = 0xF6000000 | (((((D_80750840[i].unk8 + 1) * gHiResScale) - 1) & 0x3FF) << 14) | (((((D_80750840[i].unkA + 1) * gHiResScale) - 1) & 0x3FF) << 2);
            _g->words.w1 = ((((D_80750840[i].unk4 * gHiResScale) & 0x3FF)) << 14) | ((((D_80750840[i].unk6 * gHiResScale) & 0x3FF)) << 2);
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

typedef struct {
    u8 unk0[0x174];
    CamState *unk174;
} LightActor;

typedef struct {
    u8 unk0[0x220];
    f32 unk220;
    u8 unk224[0x270 - 0x224];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 unk278[0x2CA - 0x278];
    s16 unk2CA;
    s16 unk2CC;
} BackgroundPlayerView;

extern LightActor *gCamActor;
extern u8 D_80754EF8[];
extern void *D_80754ED8[];
extern Mtx D_2000080;
extern Gfx D_2000180;
f32 cosApprox(f32);

#define BG_BLEND_B(off, mul) \
    ((u32)((mul) * ((f32)D_80754EF8[skyTypeA * 12 + (off)] + ((f32)(D_80754EF8[skyTypeB * 12 + (off)] - D_80754EF8[skyTypeA * 12 + (off)]) * alpha))))
#define BG_BLEND_C(off, mul) \
    ((u32)((mul) * ((f32)D_80754EF8[skyTypeA * 12 + (off)] + (alpha * (f32)(D_80754EF8[skyTypeB * 12 + (off)] - D_80754EF8[skyTypeA * 12 + (off)])))))
#define BG_PLAYER_VIEW ((BackgroundPlayerView *)gPlayerSlots)

Gfx *gfxDrawBackgroundQuad(Gfx *gdl, void *tex, f32 angle, void *mtx, u8 skyTypeA, u8 skyTypeB, u8 colorMode, s8 lightIndex, f32 alpha) {
    f32 y;
    u32 color0;
    u32 color1;
    u32 color2;
    u32 color3;
    f32 red;
    f32 green;
    f32 blue;
    void **table;
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    s32 offset;
    CamState *light;

    y = -(256.0f - (cosApprox(angle) * 300.0f)) - 80.0f;
    light = gCamActor->unk174;
    if ((u32)skyTypeA == 5) {
        y = (f32)((f64)y + (0.08 * (f64)BG_PLAYER_VIEW->unk2CA - 75.0));
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
                lightIndex = *((s8 *)gPrimaryPlayerActor + 0x12D);
            }
            lightGetColor(&red, &green, &blue, lightIndex);
        }
        break;
    }
    if ((light->unkFA != 0) && (BG_PLAYER_VIEW->unk220 < (light->unk90 + 3.0f))) {
        red = (f32)((f64)red * 0.1);
        green = (f32)((f64)green * 0.1);
        blue = (f32)((f64)blue * 0.3);
    }

    color0 = ((BG_BLEND_C(0, red) & 0xFF) << 24) | ((BG_BLEND_C(1, green) & 0xFF) << 16) | (BG_BLEND_B(2, blue) & 0xFF) << 8 | 0xFF;
    color1 = ((BG_BLEND_C(3, red) & 0xFF) << 24) | ((BG_BLEND_C(4, green) & 0xFF) << 16) | (BG_BLEND_B(5, blue) & 0xFF) << 8 | 0xFF;
    color2 = ((BG_BLEND_C(6, red) & 0xFF) << 24) | ((BG_BLEND_C(7, green) & 0xFF) << 16) | (BG_BLEND_B(8, blue) & 0xFF) << 8 | 0xFF;
    color3 = ((BG_BLEND_C(9, red) & 0xFF) << 24) | ((BG_BLEND_C(10, green) & 0xFF) << 16) | (BG_BLEND_B(11, blue) & 0xFF) << 8 | 0xFF;

    gDPPipeSync(gdl++);
    gSPSetOtherMode(gdl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x552048);
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0xFCFFFFFF; _g->words.w1 = 0xFFFE793C; }
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gdl++, 0xFFFFFF);
    gSPSetGeometryMode(gdl++, 0x200004);
    gSPMatrix(gdl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gdl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0xDC080008; _g->words.w1 = osVirtualToPhysical((u8 *)BG_PLAYER_VIEW + (gGfxBufferIndex << 4) + 0x250); }
    {
        Gfx *_g = (Gfx *)(gdl++);
        _g->words.w0 = ((s32)((f32)BG_PLAYER_VIEW->unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)BG_PLAYER_VIEW->unk270 * 4.0f) & 0xFFF) << 12);
        _g->words.w1 = ((s32)((f32)BG_PLAYER_VIEW->unk276 * 4.0f) & 0xFFF) | (((s32)((f32)BG_PLAYER_VIEW->unk274 * 4.0f) & 0xFFF) << 12);
    }

    offset = *(s16 *)((u8 *)D_80754ED8[skyTypeA] + 0x22);
    table = &D_80754ED8[skyTypeA];
    guTranslateF(mtxA, 0.0f, (f32)-offset, 0.0f);
    matrixMakeRotationZ(mtxB, (f32)((s32)(((0x1000 - BG_PLAYER_VIEW->unk2CC) & 0xFFF) * 0x168) / 0x1000));
    guMtxCatF(mtxA, mtxB, mtxA);
    guTranslateF(mtxB, 160.0f, (f32)offset + y, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    guMtxF2L(mtxA, mtx);

    gSPMatrix(gdl++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x01008010; _g->words.w1 = osVirtualToPhysical(*table); }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x02100000; _g->words.w1 = color0; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x02100002; _g->words.w1 = color0; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x02100004; _g->words.w1 = color1; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x02100006; _g->words.w1 = color1; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x02100008; _g->words.w1 = color2; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x0210000A; _g->words.w1 = color2; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x0210000C; _g->words.w1 = color3; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x0210000E; _g->words.w1 = color3; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x06000206; _g->words.w1 = 0x604; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x06040608; _g->words.w1 = 0x4080A; }
    { Gfx *_g = (Gfx *)(gdl++); _g->words.w0 = 0x060A080C; _g->words.w1 = 0xA0C0E; }
    gDPPipeSync(gdl++);
    return gdl;
}

typedef struct ColorBytesView {
    u8 unk0[0xC];
    s8 unkC;
    s8 unkD;
    s8 unkE;
} ColorBytesView;

void gfxDrawSkybox(ColorBytesView *colorView, s8 r, s8 g, s8 b) {
    colorView->unkC = r;
    colorView->unkD = g;
    colorView->unkE = b;
}

extern s32 D_807FD8A0;
extern Mtx D_807FD928;
extern s32 D_807FD978;

void gfxBackgroundReset(void) {
    D_807FD8A0 = 0;
    guOrtho(&D_807FD928, 0.0f, (f32)((f64)((f32)gScreenWidth * 16.0f) - 1.0), (f32)((f64)((f32)gScreenHeight * 16.0f) - 1.0), 0.0f, -20000.0f, 20000.0f, 1.0f);
    D_807FD968 = -1.0f;
    D_807FD978 = 0;
}

typedef struct {
    u8 unk0[0x2CA];
    s16 unk2CA;
} PlayerViewCamRoll;

f32 mathCosF(s16);
f32 mathSinF(s16);

void lensFlareAddFromAngle(s16 azimuthAngle, s16 elevationAngle, u8 colorMode) {
    f32 lightR;
    f32 lightG;
    f32 lightB;
    s16 cosAngle;
    s16 adjPitch;
    s16 sinAngle;
    s32 unused;

    cosAngle = (s16)(s32)((f64)mathSinF(azimuthAngle) * 32767.0);
    sinAngle = (s16)(s32)((f64)mathCosF(azimuthAngle) * 32767.0);
    adjPitch = (s16)(s32)((f64)elevationAngle - (8.0 * (f64)((PlayerViewCamRoll *)gPlayerSlots)->unk2CA));
    if (colorMode != 0) {
        if (colorMode == 1) {
            lightGetColor(&lightR, &lightG, &lightB, gPrimaryPlayerActor->chunkIndex);
            if ((f64)lightR > 0.5) {
                lensFlareAddSource((f32)cosAngle, (f32)adjPitch, (f32)sinAngle, 0.0f, 0.0f, 0.0f, 0.0f, (u32)(lightR * 255.0f), (u32)(lightG * 255.0f), (u32)(lightB * 255.0f));
            }
        }
    } else {
        lensFlareAddSource((f32)cosAngle, (f32)adjPitch, (f32)sinAngle, 0.0f, 0.0f, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF);
    }
}

extern f32 gBackgroundBlend;
extern u8 D_2000100[];

Gfx *gfxDrawSkySprite(Gfx *dl, s16 azimuthAngle, s16 elevationAngle, u8 mode) {
    s16 cosAngle;
    Gfx *g;
    f32 screenX, screenY;
    u8 alpha;
    f32 lightR, lightG, lightB;
    s16 b;
    s16 c;

    alpha = 0xFF;
    if (mode == 1) {
        lightGetColor(&lightR, &lightG, &lightB, gPrimaryPlayerActor->chunkIndex);
        lightR = (f32)(1.0 < ((1.0 - (f64)lightG) / 0.7) ? 1.0 : ((1.0 - (f64)lightG) / 0.7));
        alpha = (u32)((f64)lightR * 255.0);
    } else if (mode == 2) {
        lightR = (f32)((f64)gBackgroundBlend - 0.5);
        if (lightR < 0.0) {
            lightR = 0.0f;
        }
        lightR = (f32)((f64)lightR * 512.0);
        if (lightR > 255.0) {
            lightR = 255.0f;
        }
        alpha = (u32)lightR;
    }
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    cosAngle = (s16)(s32)((f64)mathSinF(azimuthAngle) * 32767.0);
    c = (s16)(s32)((f64)mathCosF(azimuthAngle) * 32767.0);
    b = (s16)(s32)((f64)elevationAngle - (8.0 * (f64)((PlayerViewCamRoll *)gPlayerSlots)->unk2CA));
    camProjectToScreen((f32)cosAngle, (f32)b, (f32)c, &screenX, &screenY, 0, 4.0f, 0);
    if ((screenX > -320.0f) && (screenX < 1600.0f) && (screenY > -240.0f) && (screenY < 1200.0f)) {
        g = playerViewGfxSetup(dl, 0);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
        g->words.w0 = 0xDA380007; g->words.w1 = (u32)&D_2000100; dl = renderRotatedSprite(g + 1, 0x35, 3, 1, 0x40, 0x40, (s32)screenX, (s32)screenY, 4.0f, 4.0f, 0, 0.0f);
    }
    return dl;
}

typedef struct RectSpan {
    f32 v[3][2];
} RectSpan;

void gfxWrapRectSpan(RectSpan *spans, u8 *pCount, u8 axis, f32 maxCoord) {
    RectSpan temp[4];
    s32 i;
    u8 o;
    f32 f;
    f32 g;

    o = 0;
    for (i = 0; i < *pCount; i++) {
        temp[i] = spans[i];
    }
    for (i = 0; i < *pCount; i++) {
        if ((temp[i].v[0][axis] < 0.0f) || (maxCoord < temp[i].v[1][axis])) {
            f = (temp[i].v[0][axis] < 0.0f) ? temp[i].v[0][axis] + maxCoord : temp[i].v[0][axis];
            spans[o].v[0][axis] = f;
            spans[o].v[0][axis ^ 1] = temp[i].v[0][axis ^ 1];
            spans[o].v[1][axis] = maxCoord;
            spans[o].v[1][axis ^ 1] = temp[i].v[1][axis ^ 1];
            spans[o].v[2][axis] = temp[i].v[2][axis];
            spans[o].v[2][axis ^ 1] = temp[i].v[2][axis ^ 1];
            g = spans[o].v[2][axis] + (maxCoord - f);
            o++;
            f = (temp[i].v[0][axis] < 0.0f) ? temp[i].v[1][axis] : temp[i].v[1][axis] - maxCoord;
            spans[o].v[0][axis] = 0.0f;
            spans[o].v[0][axis ^ 1] = temp[i].v[0][axis ^ 1];
            spans[o].v[1][axis] = f;
            spans[o].v[1][axis ^ 1] = temp[i].v[1][axis ^ 1];
            spans[o].v[2][axis] = g;
            spans[o].v[2][axis ^ 1] = temp[i].v[2][axis ^ 1];
            o++;
        } else {
            spans[o] = temp[i];
            o++;
        }
    }
    *pCount = o;
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
    TintKeyframe *p;
    f32 t;

    switch (gCurrentMap) {
        case 0xE:
            idx = 0;
            if (yPos < D_80754F58[1].pos) {
                do {
                    idx++;
                } while (yPos < D_80754F58[idx + 1].pos);
            }
            p = &D_80754F58[idx];
            t = (f32)(yPos - D_80754F58[idx + 1].pos) / (f32)(p->pos - D_80754F58[idx + 1].pos);
            *outR = D_80754F58[idx + 1].r + (f32)(p->r - D_80754F58[idx + 1].r) * t;
            *outG = D_80754F58[idx + 1].g + (f32)(p->g - D_80754F58[idx + 1].g) * t;
            *outB = D_80754F58[idx + 1].b + (f32)(p->b - D_80754F58[idx + 1].b) * t;
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

typedef struct {
    u8 unk0[0xE4];
    s16 unkE4;
} CameraRoll;

typedef struct {
    u8 unk0[0x104];
    CameraRoll *unk104;
} CameraLink;

typedef struct {
    u8 unk0[0x80];
    f32 unk80;
    u8 unk84[0xF0];
    CameraLink *unk174;
} CameraActorView;

typedef struct {
    u8 unk0[4];
    CameraActorView *unk4;
} PlayerCamEntry;

extern Mtx D_807FD8A8[];
extern f32 D_80754CE4;

Gfx *gfxDrawRotatedTiledBackground(Gfx *glist, f32 rotX, f32 rotY, s32 assetId, f32 width, f32 height) {
    f32 lo;
    f32 hi;
    s32 i;
    f32 rect[30];
    u8 count;
    CameraActorView *cam;
    CameraLink *cam2;
    f32 inv;
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    u8 r;
    u8 g;
    u8 b;
    f32 scale;

    scale = 5.6f / D_80754CE4;
    cam = ((PlayerCamEntry *)gPlayerSlots)->unk4;
    cam2 = cam->unk174;
    guScaleF(mtxA, scale, scale, scale);
    guTranslateF(mtxB, -2560.0f, -1920.0f, 0.0f);
    guMtxCatF(mtxA, mtxB, mtxA);
    inv = (f32)((0x1000 - cam2->unk104->unkE4) & 0xFFF);
    inv = inv * 0.087890625f;
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
    { Gfx *_g = (Gfx *)(glist++); _g->words.w0 = 0xFC11FE23; _g->words.w1 = 0xFFFFF7FB; }
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0);
    gfxGetBackgroundTint((s16)(s32)cam->unk80, &r, &g, &b);
    gDPSetPrimColor(glist++, 0, 0, r, g, b, 0xFF);
    gSPClearGeometryMode(glist++, 0xFFFFFF);
    gSPSetGeometryMode(glist++, 0x200004);
    lo = rotX * 0.15915494f * D_80754CE4;
    hi = rotY * 0.15915494f * D_80754CE4;
    inv = 1.0f / scale;
    while (lo > 1.0f) {
        lo -= 1.0f;
    }
    while (hi > 1.0f) {
        hi -= 1.0f;
    }
    lo = lo * width;
    hi = hi * height;
    rect[0] = lo - 460.0f * inv * 0.5f;
    rect[2] = 460.0f * inv * 0.5f + lo;
    count = 1;
    rect[1] = hi - 380.0f * inv * 0.5f;
    rect[2] = 460.0f * inv * 0.5f + lo;
    rect[3] = 380.0f * inv * 0.5f + hi;
    rect[5] = rect[4] = -70.0f * inv;
    gfxWrapRectSpan((RectSpan *)rect, &count, 0, width);
    gfxWrapRectSpan((RectSpan *)rect, &count, 1, height);
    for (i = 0; i < count; i++) {
        gfxDrawTexturedTileGridSimple(&glist, D_807FD8A0, 0, (u32)width, (u32)height, 0x20, 0x20, rect[i * 6], rect[i * 6 + 1], rect[i * 6 + 2], rect[i * 6 + 3], rect[i * 6 + 4], rect[i * 6 + 5], 0x10, 0x10);
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

    gSPClearGeometryMode(dl++, 0xFFFFFF);
    gSPSetGeometryMode(dl++, G_SHADE | G_SHADING_SMOOTH);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    { Gfx *_g = (Gfx *)(dl++); _g->words.w0 = 0xFC11FE23; _g->words.w1 = 0xFFFFF3F9; }
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
    if (D_807FD978 == 0) {
        for (n = 0; n < 8; n++) {
            (&D_807FD978)[n] = assetLoad(0x19, D_80754CEC[n], 0, 0);
        }
    }
    k = 0;
    j = 0x40;
    do {
        i = 0;
        y = (j << 2) - scroll;
        do {
            gDPPipeSync(dl++);
            { s32 tv = (&D_807FD978)[k];
            gDPLoadTextureBlock(dl++, (u32)tv + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD); }
            x = (i << 2) - D_80754F70;
            for (n = 0; n != 4; n++) {
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
        j -= 0x40;
    } while (j >= 0);
    /* the stores go through other base symbols: with D_80754F70 spelled directly IDO hoists its address into v1 */
    i = (s16)(D_80754F70 + 4);
    D_80754F74 += 4;
    *(s16 *)((u8 *)D_80754F58 + 0x18) = i;
    if (i >= 0x200) {
        *(s16 *)(D_80754EF8 + 0x78) = 0;
    }
    if (D_80754F74 >= 0x200) {
        D_80754F74 = 0;
    }
    gDPPipeSync(dl++);
    gDPSetTexturePersp(dl++, G_TP_PERSP);
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    return dl;
}

typedef struct {
    u8 unk0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
} PlayerViewScissor;

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
    {
        Gfx *_g = (Gfx *)(glist++);
        _g->words.w0 = ((s32)((f32)((PlayerViewScissor *)gPlayerSlots)->unk272 * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)((PlayerViewScissor *)gPlayerSlots)->unk270 * 4.0f) & 0xFFF) << 12);
        _g->words.w1 = ((s32)((f32)((PlayerViewScissor *)gPlayerSlots)->unk276 * 4.0f) & 0xFFF) | (((s32)((f32)((PlayerViewScissor *)gPlayerSlots)->unk274 * 4.0f) & 0xFFF) << 12);
    }
    gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0);
    return glist;
}

extern f32 gScreenFadeRate;
extern u8 D_8076AEE0;
extern s16 D_807FD800;

typedef struct {
    u8 pad0[0x210];
    f32 unk210;
    u8 pad214[4];
    f32 unk218;
    u8 pad21C[0x270 - 0x21C];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 pad278[0x290 - 0x278];
    u16 unk290;
} PlayerViewBackdrop;

#define PLAYER_VIEW_MODE (*(s16 *)&((PlayerViewBackdrop *)gPlayerSlots)->unk290)

Gfx *gfxDrawMapBackground(Gfx *dl, void *bgTex, void *rotAngle, void *mtx, s32 player) {
    f32 x;
    f32 r;
    f32 z;
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
        dl = gfxDrawRotatedTiledBackground(dl, *(f32 *)&bgTex, *(f32 *)&rotAngle, 0x2D, 320.0f, 240.0f);
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
        dl = gfxDrawRotatedTiledBackground(dl, *(f32 *)&bgTex, *(f32 *)&rotAngle, 0x2E, 320.0f, 240.0f);
        break;
    case 0x26:
        switch (((PlayerViewBackdrop *)gPlayerSlots)->unk290) {
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
            dl = gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 0, 0, 0, -1, 0.0f);
            break;
        }
        break;
    case 0x1E:
        if (((PLAYER_VIEW_MODE != 7) && (PLAYER_VIEW_MODE != 6) && (PLAYER_VIEW_MODE != 8) && (PLAYER_VIEW_MODE != 0)) || (D_807FD800 != 0)) {
            dl = gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 0, 0, ((gPrimaryPlayerActor->chunkIndex == 9) || (gPrimaryPlayerActor->chunkIndex == 0xB) || (gPrimaryPlayerActor->chunkIndex == 3)) ? 1 : 0, 9, 0.0f);
        }
        break;
    case 0x27:
        lensFlareAddFromAngle(0xBB8, 0x2328, 0);
        dl = gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 0, 0, 0, -1, 0.0f);
        break;
    case 0x4:
        dl = gfxClearScreenSetViewportScissor(dl);
        break;
    case 0xB0:
        dl = gfxClearScreenSetViewportScissor(dl);
        break;
    case 0x7:
        switch ((s16)((PlayerViewBackdrop *)gPlayerSlots)->unk290) {
        case 8:
        case 9:
        case 12:
        case 16:
            dl = gfxClearScreenSetViewportScissor(dl);
            break;
        case 11:
        case 14:
            lensFlareAddFromAngle(0, 0x7530, 1);
            dl = gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 4, 4, 1, -1, 0.0f);
            break;
        default:
            lensFlareAddFromAngle(0, 0x7530, 0);
            dl = gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 4, 4, 0, -1, 0.0f);
            break;
        }
        break;
    case 0x8:
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 3, 3, 1, -1, 0.0f), 0, 0x7D00, 0);
        break;
    case 0x30:
        if ((PLAYER_VIEW_MODE >= 0xC) && (PLAYER_VIEW_MODE < 0x12)) {
            dl = gfxClearScreenSetViewportScissor(dl);
        } else {
            lensFlareAddFromAngle(0, 0x5DC0, 1);
            dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 2, 2, 1, -1, 0.0f), 0, 0x5DC0, 1);
        }
        break;
    case 0x37:
        dl = gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 1, 1, 1, -1, 0.0f);
        break;
    case 0x22:
        if (camIsCutsceneActive() != 0) {
            x = ((PlayerViewBackdrop *)gPlayerSlots)->unk210;
            z = ((PlayerViewBackdrop *)gPlayerSlots)->unk218;
        } else {
            x = gPrimaryPlayerActor->x;
            z = gPrimaryPlayerActor->z;
        }
        x = sqrtf(((x - 3000.0f) * (x - 3000.0f)) + ((z - 5000.0f) * (z - 5000.0f)));
        if (x < 2500.0f) {
            r = (f32)((f64)((2500.0f - x) / 1000.0f) > 1.0 ? 1.0 : (f64)((2500.0f - x) / 1000.0f));
            func_8068B830((s16)(s32)(2.0f + r), (s16)(s32)(r * 400.0f), (s16)(s32)(r * 30.0f));
            enemyAggroSetIntensityBB((f32)(((f64)r * -0.6) + 1.0));
        } else {
            enemyAggroDespawnBB();
            enemyAggroSetIntensityBB(1.0f);
        }
        lensFlareAddFromAngle(0xBB8, 0x4E20, 0);
        dl = gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 5, 6, 1, -1, 0.0f);
        break;
    case 0x99:
    case 0xAC:
        lensFlareAddFromAngle(0xBB8, 0x4E20, 0);
        dl = gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 5, 5, 1, -1, 0.0f);
        break;
    case 0x6F:
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 6, 6, 1, -1, 0.0f), 0xC8, 0x4268, 0);
        break;
    case 0x57:
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 6, 6, 1, -1, 0.0f), 0x3E8, 0x2EE0, 0);
        break;
    case 0xD5:
        lensFlareAddFromAngle(0x8FC, 0x1388, 0);
        dl = gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 7, 7, 0, -1, 0.0f);
        break;
    case 0xD0:
        gDPSetFillColor(dl++, 0xFFFFFFFF);
        goto fill;
    case 0x36:
        gDPSetFillColor(dl++, 0xFFC1FFC1);
        goto fill;
    case 0x50:
        lensFlareAddFromAngle(0x8FC, 0x1388, 1);
        dl = gfxDrawSkySprite(gfxDrawBackgroundQuad(dl, bgTex, *(f32 *)&rotAngle, mtx, 7, 6, 0, -1, gBackgroundBlend), 0xC8, 0x2EE0, 2);
        break;
    default:
        gDPSetFillColor(dl++, 0x10001);
    fill:
        gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0);
        gDPSetCycleType(dl++, G_CYC_FILL);
        {
            Gfx *_g = (Gfx *)(dl++); _g->words.w0 = (((((PlayerViewBackdrop *)((u8 *)gPlayerSlots + (s16)player * 0x2F0))->unk276 - 1) & 0x3FF) << 2) | 0xF6000000 | (((((PlayerViewBackdrop *)((u8 *)gPlayerSlots + (s16)player * 0x2F0))->unk274 - 1) & 0x3FF) << 14);
            _g->words.w1 = (((((PlayerViewBackdrop *)((u8 *)gPlayerSlots + (s16)player * 0x2F0))->unk272) & 0x3FF) << 2) | (((((PlayerViewBackdrop *)((u8 *)gPlayerSlots + (s16)player * 0x2F0))->unk270) & 0x3FF) << 14);
        }
        gDPPipeSync(dl++);
        gDPSetCycleType(dl++, G_CYC_1CYCLE);
        break;
    }
    gBackgroundBlend = 0.0f;
    gDPPipeSync(dl++);
    return dl;
}


typedef struct {
    u8 unk0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 unk278[0x5C];
    void *unk2D4;
    void *unk2D8;
    u8 unk2DC[0x14];
} PlayerViewWithBg;

extern s32 gGlobalPauseFlags;
extern s32 D_807552EC;

Gfx *gfxDrawPlayerViewBackground(Gfx *glist, s16 player) {
    s32 draw_black;

    if ((gPlayerCount >= 2) || !(gGlobalPauseFlags & 0x10)) {
        if (gCurrentMap == 0x50) {
            glist = gfxBuildScrollingBackground(glist);
        } else {
            draw_black = !(gGlobalPauseFlags & 2);
            if (gPlayerCount >= 2) {
                s32 tmp;
                if (gGfxBufferIndex == 0) {}
                if (gCurrentMap == 0xBE) {
                    tmp = 0;
                } else {
                    tmp = 1;
                }
                tmp |= (D_807552EC >= 2);
                draw_black |= tmp;
            }
            if (draw_black == 0) {
                return glist;
            }
            gDPPipeSync(glist++);
            gSPSetOtherMode(glist++, G_SETOTHERMODE_L, 3, 29, 0);
            gDPSetFillColor(glist++, 0x00010001);
            gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0x300000);
            { Gfx *_g = (Gfx *)(glist++); _g->words.w0 = 0xF6000000 | ((((PlayerViewWithBg *)gPlayerSlots + player)->unk276 - 1) & 0x3FF) * 4 | ((((PlayerViewWithBg *)gPlayerSlots + player)->unk274 - 1) & 0x3FF) << 14; _g->words.w1 = ((((PlayerViewWithBg *)gPlayerSlots + player)->unk272 & 0x3FF) * 4) | ((((PlayerViewWithBg *)gPlayerSlots + player)->unk270 & 0x3FF) << 14); }
            gDPPipeSync(glist++);
            gSPSetOtherMode(glist++, G_SETOTHERMODE_H, 20, 2, 0);
        }
    } else {
        glist = gfxDrawMapBackground(glist, ((PlayerViewWithBg *)gPlayerSlots + player)->unk2D4, ((PlayerViewWithBg *)gPlayerSlots + player)->unk2D8,
            (u8 *)((PlayerViewWithBg *)gPlayerSlots + player) + (gGfxBufferIndex << 6) + 0x108, player);
    }
    return glist;
}


void gfxSetBackgroundBlend(f32 blend) {
    f64 blendVal;

    blendVal = (f64)blend;
    if (blendVal < 0.0) {
        blend = 0.0f;
        blendVal = (f64)blend;
    }
    if (blendVal > 1.0) {
        blend = 1.0f;
    }
    gBackgroundBlend = blend;
}
