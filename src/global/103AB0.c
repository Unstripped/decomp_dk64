#include "common.h"
#include "actor.h"
#include "render.h"
#include "sched.h"
#include "proto/global/103AB0.h"
#include "proto/global/10E1D0.h"
#include "proto/global/112080.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17540.h"
#include "proto/global/17800.h"
#include "proto/global/201B0.h"
#include "proto/global/3C10.h"
#include "proto/global/450.h"
#include "proto/global/6AD90.h"
#include "proto/global/7130.h"
#include "proto/global/90D80.h"
#include "proto/global/936B0.h"
#include "proto/global/9DD70.h"
#include "proto/global/FCCD0.h"

extern Actor *gCurrentActor;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern s32 gCurrentMap;
extern u8 gCurrentWorldId;
extern u8 gScreenRenderFlags;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gGfxBufferIndex;
extern s16 gGfxScreenLeft;
extern s16 gGfxScreenTop;
extern s16 gGfxScreenRight;
extern s16 gGfxScreenBottom;

extern Gfx D_1000118;
extern Mtx D_2000080;

typedef struct {
    f32 scale;
    f32 axisPos;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    s8 texOffset;
    u8 pad[3];
} LensFlareSprite;

typedef struct {
    s32 shift;
    s32 offset;
} ZbufferDecodeEntry;

// This TU's .data (0x80754AF0-0x80754CD4 + 12-byte TU pad) is emitted in source order: these two
// objects, zbufferReadDepth's decode table, the screen-fade vertices, screenFadeUpdate's channel list.
LensFlareSprite gLensFlareSprites[13] = {
    { 1.0f, 1.0f, 255, 255, 255, 255, 3 },
    { 0.08f, 1.2f, 250, 220, 220, 200, 2 },
    { 0.8f, 1.0f, 255, 255, 255, 50, 1 },
    { 0.5f, 0.8f, 100, 255, 255, 150, 0 },
    { 0.2f, 0.7f, 255, 175, 175, 150, 2 },
    { 0.6f, 0.5f, 255, 250, 250, 175, 0 },
    { 0.1f, 0.45f, 255, 255, 255, 255, 2 },
    { 0.1f, 0.42f, 150, 255, 255, 255, 2 },
    { 0.1f, 0.38f, 255, 200, 200, 255, 2 },
    { 0.4f, 0.3f, 55, 240, 40, 150, 2 },
    { 0.3f, 0.1f, 255, 128, 128, 150, 2 },
    { 3.0f, 0.0f, 100, 255, 255, 75, 1 },
    { 1.0f, 1.0f, 255, 50, 0, 255, 4 },
};
u8 gLensFlareSourceCount = 0;

Gfx *playerViewGfxSetup(Gfx *dl, u8 playerIndex) {
    gDPPipeSync(dl++);
    gSPViewport(dl++, osVirtualToPhysical(&gPlayerSlots[playerIndex].viewport[gGfxBufferIndex]));
    gDPSetScissor(dl++, G_SC_NON_INTERLACE, gPlayerSlots[playerIndex].rect[0], gPlayerSlots[playerIndex].rect[1], gPlayerSlots[playerIndex].rect[2], gPlayerSlots[playerIndex].rect[3]);
    gSPDisplayList(dl++, &D_1000118);
    gDPSetCombineMode(dl++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    return dl;
}


Gfx *playerViewDrawCenterMask(Gfx *dl, Actor *player) {
    dl = playerViewGfxSetup(dl, ((PlayerState *)player->customState)->playerIndex);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    return renderRotatedSprite(dl, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, 0.001f);
}

Gfx *playerViewDrawCrosshair(Gfx *gfx, Actor *actor) {
    u8 player;
    Actor *target;
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    Gfx *dl;

    player = ((PlayerState *)actor->customState)->playerIndex;
    dl = playerViewGfxSetup(gfx, player);
    if ((gCurrentKongInventory->weaponFlags & 2) && slotQueueGetValue(3, player) &&
        projectileFindHomingTarget(2, &target, actor, 1, 0, 0, &targetX, &targetY, &targetZ)) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xC8, 0, 0xFF);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 0xC8, 0, 0, 0xFF);
    }
    return renderRotatedSprite(dl, 0x38, 3, 1, 0x40, 0x40, 0xA0, 0x78, 0.5f, 0.5f, 0x2D, 0.0f);
}

Gfx *playerViewDrawCornerMasks(Gfx *dl) {
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    gDPSetCombineMode(dl++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x3E, 0x3E, 2.0f, 2.0f, 0, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, gScreenWidth - 0x3E, 0x3E, 2.0f, 2.0f, 0x5A, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, gScreenWidth - 0x3E, gScreenHeight - 0x3E, 2.0f, 2.0f, 0xB4, 0.0f);
    return renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x3E, gScreenHeight - 0x3E, 2.0f, 2.0f, 0x10E, 0.0f);
}

void playerViewCornerMasksCallback(Gfx *dl, Actor *actor) {
    playerViewDrawCornerMasks(playerViewGfxSetup(dl, ((PlayerState *)actor->customState)->playerIndex));
}

Gfx *playerViewDrawCameraViewfinder(Gfx *dl, Actor *actor) {
    PlayerState *state;

    state = gPlayerSlots->actor->customState;
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xC8);
    dl = renderRotatedSprite(dl, 0x39, 3, 1, 0x40, 0x40, 0x50, 0x50, 0.5f, 0.5f, 0, 0.0f);
    dl = renderRotatedSprite(dl, 0x39, 3, 1, 0x40, 0x40, 0xF0, 0x50, 0.5f, 0.5f, 0x5A, 0.0f);
    dl = renderRotatedSprite(dl, 0x39, 3, 1, 0x40, 0x40, 0xF0, 0xA0, 0.5f, 0.5f, 0xB4, 0.0f);
    dl = renderRotatedSprite(dl, 0x39, 3, 1, 0x40, 0x40, 0x50, 0xA0, 0.5f, 0.5f, 0x10E, 0.0f);
    dl = renderRotatedSprite(dl, 0x3B, 3, 1, 0x30, 0x30, 0xA0, 0x78, 1.0f, 1.0f, 0, 0.0f);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    if (!(state->stateFlags & 0x8000)) {
        if (state->photoSubjectStatus == 2) {
            gDPSetPrimColor(dl++, 0, 0, 0xFF, 0, 0, 0xFF);
            dl = renderRotatedSprite(dl, 0x43, 3, 1, 0x40, 0x40, 0x118, 0x28, 0.5f, 0.5f, 0, 0.0f);
        } else if (state->photoSubjectStatus == 1) {
            gDPSetPrimColor(dl++, 0, 0, 0, 0xFF, 0, 0xFF);
            dl = renderRotatedSprite(dl, 0x2F, 3, 1, 0x40, 0x40, 0x118, 0x28, 0.5f, 0.5f, 0, 0.0f);
        }
    }
    return dl;
}

Gfx *playerViewDrawPhotoResult(Gfx *dl, Actor *actor) {
    PlayerState *state;

    state = gPlayerSlots->actor->customState;
    dl = playerViewGfxSetup(dl, state->playerIndex);
    if (state->photoSubjectStatus == 2) {
        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0, 0, 0x64);
        dl = renderRotatedSprite(dl, 0x45, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
    } else if (state->photoSubjectStatus == 1) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xFF, 0, 0x64);
        dl = renderRotatedSprite(dl, 0x44, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
    }
    return dl;
}


Gfx *playerViewDrawScopeCrosshair(Gfx *dl, Actor *actor) {
    u8 player;
    Actor *target;
    s32 targetKind;
    f32 targetX;
    f32 targetY;
    f32 targetZ;

    targetKind = 2;
    player = ((PlayerState *)actor->customState)->playerIndex;
    if (gPlayerCount >= 2) {
        targetKind = 3;
    }
    dl = playerViewGfxSetup(dl, player);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x100, 0x40, 3.0f, 2.0f, 0, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x40, 0x40, 2.0f, 3.0f, 0x5A, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x100, 0xB0, 2.0f, 3.0f, 0x10E, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x40, 0xB0, 3.0f, 2.0f, 0xB4, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x60, 0x60, 3.0f, 3.0f, 0, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0xE0, 0x60, 3.0f, 3.0f, 0x5A, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0xE0, 0x90, 3.0f, 3.0f, 0xB4, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x60, 0x90, 3.0f, 3.0f, 0x10E, 0.0f);
    if (slotQueueGetValue(3, player) && projectileFindHomingTarget(targetKind, &target, actor, 1, 0, 0, &targetX, &targetY, &targetZ)) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xC8, 0, 0xFF);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 0xC8, 0, 0, 0xFF);
    }
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    return renderRotatedSprite(dl, 0x38, 3, 1, 0x40, 0x40, 0xA0, 0x78, 0.5f, 0.5f, 0x2D, 0.0f);
}

void playerViewDrawCameraShutter(Gfx *gfx, Actor *actor) {
    f32 depth;
    Gfx *dl;

    depth = actor->subState * 1.4;
    dl = playerViewGfxSetup(gfx, ((PlayerState *)actor->customState)->playerIndex);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    renderRotatedSprite(dl, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, depth);
}

u16 color5551ToSepia(u16 color) {
    u16 sum;
    u8 a;
    f32 f;
    u8 lsb;

    sum = (u8)((color & 0xF800) >> 11) + (u8)((color & 0x7C0) >> 6) + (u8)((color & 0x3E) >> 1);
    lsb = color & 1;
    if (sum >= 0x30) {
        a = (sum - 0x30) / 45.0 * 18.0;
    } else {
        a = 0;
    }
    f = sum / 93.0;
    return ((u8)(28.0f * f + 3.0f) << 11) + ((u8)(19.0f * f + 3.0f) << 6) + (a << 1) + lsb;
}

u16 *sepiaCopyFramebufferTile(u16 *dst, u16 *src) {
    s16 i;
    s16 j;

    for (i = 0; i < 0x40; i++) {
        for (j = 0; j < 0x20; j++) {
            *dst++ = color5551ToSepia(src[j + i * gScreenWidth]);
        }
    }
    return dst;
}


void playerViewLoadPresetPhoto(void) {
    assetLoad(0x19, 0x138B, 1, 1);
}

extern void *gFramebuffers[];

u16 *playerViewCaptureSepiaPhoto(void) {
    u16 *buf;
    s16 col;
    s16 row;
    u16 *dst;
    u16 *src;

    if (gCurrentActor->actorType == 0xD9) {
        playerViewLoadPresetPhoto();
        return;
    }
    buf = heapAlloc(0xA000);
    dst = buf;
    src = (u16 *)gFramebuffers[gGfxBufferIndex] + gScreenWidth * 56 + 80;
    row = 0;
    do {
        col = 0;
        do {
            dst = sepiaCopyFramebufferTile(dst, src + col * 32);
            col++;
        } while (col < 5);
        src += gScreenWidth * 64;
        row++;
    } while (row < 2);
    return buf;
}

u16 color5551LerpToWhite(f32 t, u16 color) {
    u8 lsb;

    lsb = color & 1;
    return ((u8)((((color & 0xF800) >> 11) - 0x1F) * t + 31.0f) << 11) + ((u8)((((color & 0x7C0) >> 6) - 0x1F) * t + 31.0f) << 6) + ((u8)((((color & 0x3E) >> 1) - 0x1F) * t + 31.0f) << 1) + lsb;
}


void color5551CopyLerpToWhite(u16 *src, s16 **outBuf, f32 t) {
    s16 *dst;
    s16 i;

    *outBuf = heapAlloc(0xA000);
    heapFreeDeferred(*outBuf);
    dst = *outBuf;
    for (i = 0; i < 0x5000; i++) {
        *dst++ = color5551LerpToWhite(t, *src++);
    }
}

typedef struct {
    f32 x;
    f32 y;
    f32 depth;
} ScreenPoint;

extern ScreenPoint gLensFlareScreenPoints[2][3];

extern LensFlarePoint gLensFlareSources[2];

void lensFlareAddSource(f32 x, f32 y, f32 z, f32 dirX, f32 dirY, f32 dirZ, f32 minDot, u8 r, u8 g, u8 b) {
    f32 screenX;
    f32 screenY;
    u8 visible;
    Vec3f delta;
    Vec3f toCam;
    Vec3f dir;
    f32 dot;
    f32 pad0;
    f32 pad1;

    if (gLensFlareSourceCount < 2) {
        visible = 1;
        if (minDot != 0.0f) {
            delta.x = dirX - x;
            delta.y = dirY - y;
            delta.z = dirZ - z;
            dir = vec3fNormalize(delta);
            delta.x = gPlayerSlots->camX - x;
            delta.y = gPlayerSlots->camY - y;
            delta.z = gPlayerSlots->camZ - z;
            toCam = vec3fNormalize(delta);
            dot = (toCam.x * dir.x) + (toCam.y * dir.y) + (toCam.z * dir.z);
            if (dot < 0.0) {
                dot = 0.0f;
            }
            if (dot < minDot) {
                visible = 0;
            }
        }
        if (visible != 0) {
            gLensFlareScreenPoints[gGfxBufferIndex][gLensFlareSourceCount].depth = MIN(995.0f, sqrtf(SQ(gPlayerSlots->eyeZ - z) + (SQ(gPlayerSlots->eyeX - x) + SQ(gPlayerSlots->eyeY - y))));
            camProjectToScreen(x, y, z, &screenX, &screenY, 0, 4.0f, 0);
            gLensFlareScreenPoints[gGfxBufferIndex][gLensFlareSourceCount].x = screenX * 0.25;
            gLensFlareScreenPoints[gGfxBufferIndex][gLensFlareSourceCount].y = screenY * 0.25;
            gLensFlareSources[gLensFlareSourceCount].x = x;
            gLensFlareSources[gLensFlareSourceCount].y = y;
            gLensFlareSources[gLensFlareSourceCount].z = z;
            gLensFlareSources[gLensFlareSourceCount].r = r;
            gLensFlareSources[gLensFlareSourceCount].g = g;
            gLensFlareSources[gLensFlareSourceCount].b = b;
            gLensFlareSourceCount += 1;
        }
    }
}

extern Mtx D_2000100;

Gfx *playerViewSetPrimaryViewport(Gfx *dl) {
    gSPMatrix(dl++, &D_2000100, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPViewport(dl++, osVirtualToPhysical(&gPlayerSlots->viewport[gGfxBufferIndex]));
    gDPSetScissor(dl++, G_SC_NON_INTERLACE, gPlayerSlots->rect[0], gPlayerSlots->rect[1], gPlayerSlots->rect[2], gPlayerSlots->rect[3]);
    return dl;
}

extern u8 gLensFlareFade[2][3];
extern Mtx D_2000180;

Gfx *lensFlareBuildDisplayList(Gfx *dl) {
    s16 i;

    if (gLensFlareSourceCount != 0) {
        gDPPipeSync(dl++);
        dl = playerViewSetPrimaryViewport(dl);
        gSPMatrix(dl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(dl++);
        gSPClearGeometryMode(dl++, 0xFFFFFFFF);
        gSPSetGeometryMode(dl++, G_SHADE | G_SHADING_SMOOTH);
        gDPSetCycleType(dl++, G_CYC_1CYCLE);
        gDPSetTexturePersp(dl++, G_TP_PERSP);
        gDPSetTextureFilter(dl++, G_TF_BILERP);
        gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
        gDPSetCombineLERP(dl++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0);
        gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
        gDPSetColorDither(dl++, G_CD_DISABLE);
        gDPSetAlphaDither(dl++, G_AD_DISABLE);
        for (i = 0; i < gLensFlareSourceCount; i++) {
            if (gLensFlareFade[gGfxBufferIndex ^ 1][i] != 0) {
                dl = lensFlareDrawSource(dl, gLensFlareSources[i], gLensFlareFade[gGfxBufferIndex ^ 1][i]--);
            }
        }
        gDPSetColorDither(dl++, G_CD_MAGICSQ);
        gDPSetAlphaDither(dl++, G_AD_PATTERN);
    }
    return dl;
}

extern s16 *gZbufferDistanceTable;

s16 zbufferDepthToDistance(s16 depth) {
    s16 lo;
    s16 hi;
    s16 mid;
    s32 dist;

    lo = 0;
    mid = -1; // FAKE: mid preassigned (the -1 compare reads it) steers lo/hi registers
    hi = 0x1FE;
    if (depth == mid) {
        return 0;
    }
    do {
        mid = (lo + hi) / 2;
        if (depth < gZbufferDistanceTable[mid]) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
        if (depth >= gZbufferDistanceTable[mid] && depth < gZbufferDistanceTable[mid + 1]) {
            return mid + 8;
        }
    } while (hi >= lo);
    dist = depth - 0x7C1B;
    return dist < 0 ? 0 : dist;
}

extern u16 *gGfxDepthBuffer;

u16 zbufferReadDepth(s16 x, s16 y) {
    ZbufferDecodeEntry table[8] = { /* indexed by the 3-bit depth exponent */
        { 6, 0x0 },
        { 5, 0x20000 },
        { 4, 0x30000 },
        { 3, 0x38000 },
        { 2, 0x3C000 },
        { 1, 0x3E000 },
        { 0, 0x3F000 },
        { 0, 0x3F800 },
    };
    u16 z;
    u16 exponent;
    u16 mantissa;
    u16 *depth;
    u32 result;

    depth = gGfxDepthBuffer;
    if (x < gPlayerSlots->rect[0] || gPlayerSlots->rect[2] < x || y < gPlayerSlots->rect[1] || gPlayerSlots->rect[3] < y) {
        return 0xFFFF;
    }
    depth += gScreenWidth * y + x;
    z = *depth;
    exponent = (z >> 13) & 7;
    mantissa = (z >> 2) & 0x7FF;
    result = (mantissa << table[exponent].shift) + table[exponent].offset;
    return result >> 3;
}

extern s16 gViewProbeHitsFarPlane;
extern s16 gPhotoSubjectDepthDist;
extern s16 gPhotoSubjectScreenX;
extern s16 gPhotoSubjectScreenY;



void playerViewUpdateDepthProbes(void) {
    u8 i;
    PlayerState *state;
    s16 x;
    s16 y;
    u16 halfWidth;
    PadInputState *pad;

    if (gLensFlareSourceCount != 0) {
        do {
            gLensFlareSourceCount--;
            if (gPlayerSlots->rect[0] < gLensFlareScreenPoints[gGfxBufferIndex][gLensFlareSourceCount].x &&
                gLensFlareScreenPoints[gGfxBufferIndex][gLensFlareSourceCount].x < gPlayerSlots->rect[2] &&
                gPlayerSlots->rect[1] < gLensFlareScreenPoints[gGfxBufferIndex][gLensFlareSourceCount].y &&
                gLensFlareScreenPoints[gGfxBufferIndex][gLensFlareSourceCount].y < gPlayerSlots->rect[3] &&
                !(gGlobalPauseFlags & 2)) {
                if (gLensFlareScreenPoints[gGfxBufferIndex][gLensFlareSourceCount].depth <
                    zbufferDepthToDistance(zbufferReadDepth(gLensFlareScreenPoints[gGfxBufferIndex][gLensFlareSourceCount].x,
                                                            gLensFlareScreenPoints[gGfxBufferIndex][gLensFlareSourceCount].y))) {
                    gLensFlareFade[gGfxBufferIndex][gLensFlareSourceCount] = 5;
                }
            }
        } while (gLensFlareSourceCount != 0);
    }
    gViewProbeHitsFarPlane = zbufferReadDepth(0xA0, 0xDC) == 0x7FFF || zbufferReadDepth(0xC, 0x78) == 0x7FFF || zbufferReadDepth(0x134, 0x78) == 0x7FFF;
    gPhotoSubjectDepthDist = zbufferDepthToDistance(zbufferReadDepth(gPhotoSubjectScreenX, gPhotoSubjectScreenY));
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].active != 0) {
            state = gPlayerSlots[i].actor->customState;
            pad = &gPlayerPadState[i];
            x = state->targetPitch;
            y = state->targetRoll - 0x14;
            x += pad->stickX;
            halfWidth = 40;
            halfWidth += pad->stickAbsX / 1.5;
            state->depthCenter = zbufferDepthToDistance(zbufferReadDepth(x, y));
            state->unk116 = zbufferDepthToDistance(zbufferReadDepth(x, state->targetYawAngle));
            state->depthLeft = zbufferDepthToDistance(zbufferReadDepth(x - halfWidth, y));
            state->depthRight = zbufferDepthToDistance(zbufferReadDepth(x + halfWidth, y));
        }
    }
}

Gfx *lensFlareDrawSource(Gfx *dl, LensFlarePoint pt, u8 fade) {
    Vec3f axisEnd;
    Vec3f axisSpan;
    Vec3f viewDir;
    Vec3f srcDir;
    Vec3f pos;
    Vec3f eye;
    Vec3f at;
    Vec3f src;
    Vec3f pad1[7];
    f32 screenX;
    s16 i;
    f32 facing;
    f32 colorScale;
    f32 alphaScale;
    f32 screenY;
    f32 alpha;

    alpha = fade / 5.0;
    vec3fSet(&src, pt.x, pt.y, pt.z);
    vec3fSet(&eye, gPlayerSlots->eyeX, gPlayerSlots->eyeY, gPlayerSlots->eyeZ);
    vec3fSet(&at, gPlayerSlots->eyeFocusX, gPlayerSlots->eyeFocusY, gPlayerSlots->eyeFocusZ);
    viewDir = vec3fNormalize(vec3fSub(at, eye));
    axisEnd = vec3fAdd(eye, vec3fScale(viewDir, 5000.0f));
    srcDir = vec3fNormalize(vec3fSub(src, eye));
    facing = MAX(1e-05, vec3fDot(srcDir, viewDir));
    src = vec3fAdd(eye, vec3fScale(vec3fScale(srcDir, 5000.0f), 1.0f / facing));
    axisSpan = vec3fSub(src, axisEnd);
    if (facing < 0.0f) {
        return dl;
    }
    for (i = 0; i < 12; i++) {
        alphaScale = (facing < 0.75 ? 0.0 : facing - 0.75) * 4.0;
        colorScale = MAX(0.85, alphaScale);
        switch (i) {
        case 11:
            screenX = 640.0f;
            screenY = 480.0f;
            alphaScale = (facing < 0.9 ? 0.0 : facing - 0.9) * 10.0;
            colorScale = MAX(0.85, alphaScale);
            break;
        case 0:
        case 12:
            alphaScale = (facing < 0.25 ? 0.0 : facing - 0.25) * 1.333;
            colorScale = MAX(0.85, alphaScale);
            camProjectToScreen(src.x, src.y, src.z, &screenX, &screenY, 0, 4.0f, 0);
            break;
        default:
            pos = vec3fAdd(axisEnd, vec3fScale(axisSpan, gLensFlareSprites[i].axisPos));
            camProjectToScreen(pos.x, pos.y, pos.z, &screenX, &screenY, 0, 4.0f, 0);
            break;
        }
        gDPPipeSync(dl++);
        gDPSetPrimColor(dl++, 0, 0, (u32)((pt.r / 255.0) * gLensFlareSprites[i].r * colorScale), (u32)((pt.g / 255.0) * gLensFlareSprites[i].g * colorScale), (u32)((pt.b / 255.0) * gLensFlareSprites[i].b * colorScale), (u32)(gLensFlareSprites[i].a * alphaScale * alpha));
        dl = renderRotatedSprite(dl, gLensFlareSprites[i].texOffset + 0x4D, 3, 1, 0x40, 0x40, screenX, screenY, gLensFlareSprites[i].scale * 4.0f * alpha, gLensFlareSprites[i].scale * 4.0f * alpha, 0, 0.0f);
    }
    gDPPipeSync(dl++);
    if (facing > 0.97) {
        dl = gfxFillScreenColor(dl, pt.r, pt.g, pt.b, (u32)((facing - 0.97) * 33.0 * 128.0));
        gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
        gDPSetCombineMode(dl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    }
    return dl;
}

extern u8 gUnderwaterTintSnap;

void underwaterTintReset(void) {
    gUnderwaterTintSnap = 1;
}

extern Mtx D_2000000;
extern Mtx D_2000200;

Gfx *underwaterTintBuildDisplayList(Gfx *dl) {
    PlayerState *playerState;
    CamState *camState;
    Actor *camActor;
    Vtx *vtx;
    f32 depthDiff;
    u8 drew;
    u32 alphaBase;
    u8 i;
    u8 force;

    drew = 0;
    alphaBase = 100;
    force = 0;
    switch (gCurrentMap) {
    case 0x2D:
        force = 1;
        break;
    case 0x2B:
    case 0x2E:
    case 0x2F:
    case 0xB3:
        return dl;
    case 0x1E:
        if ((gPlayerSlots[0].camChunk == 9 || gPlayerSlots[0].camChunk == 0xA) && flagGet(0x9C, 0) != 0) {
            return dl;
        }
    default:
        break;
    }
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].active != 0) {
            playerState = gPlayerSlots[i].actor->customState;
            camActor = playerState->camActor;
            camState = camActor->customState;
            if (force != 0 || (gPlayerSlots[i].camHasWater != 0 && gPlayerSlots[i].eyeY < gPlayerSlots[i].camWaterY + 3.0f)) {
                vtx = heapAlloc(0x40);
                heapFreeDeferred(vtx);
                vtx[0].v.ob[0] = gPlayerSlots[i].rect[0];
                vtx[0].v.ob[1] = gPlayerSlots[i].rect[1];
                vtx[0].v.ob[2] = -10;
                vtx[1].v.ob[0] = gPlayerSlots[i].rect[2];
                vtx[1].v.ob[1] = gPlayerSlots[i].rect[1];
                vtx[1].v.ob[2] = -10;
                vtx[2].v.ob[0] = gPlayerSlots[i].rect[2];
                vtx[2].v.ob[1] = gPlayerSlots[i].rect[3];
                vtx[2].v.ob[2] = -10;
                vtx[3].v.ob[0] = gPlayerSlots[i].rect[0];
                vtx[3].v.ob[1] = gPlayerSlots[i].rect[3];
                vtx[3].v.ob[2] = -10;
                gDPPipeSync(dl++);
                dl = gfxSetViewportDisplayList(dl);
                gDPSetScissor(dl++, G_SC_NON_INTERLACE, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight, gGfxScreenBottom);
                gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
                gDPSetCombineMode(dl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
                depthDiff = gPlayerSlots[i].camWaterY - gPlayerSlots[i].eyeY;
                switch (gCurrentMap) {
                case 0x1E:
                    depthDiff = depthDiff * 0.07;
                    break;
                case 0x2C:
                    alphaBase = 0x32;
                    depthDiff = depthDiff * 0.07;
                    break;
                case 0x6F:
                    alphaBase = 0x32;
                default:
                    depthDiff = depthDiff * 0.4;
                    break;
                }
                if (depthDiff > 80.0f) {
                    depthDiff = 80.0f;
                }
                if (gUnderwaterTintSnap != 0) {
                    playerState->underwaterTint = depthDiff;
                } else {
                    playerState->underwaterTint = playerState->underwaterTint + (f64)(depthDiff - playerState->underwaterTint) * 0.05;
                    depthDiff = (u32)playerState->underwaterTint & 0xFF;
                }
                gDPSetPrimColor(dl++, 0, 0, 0, 0, 0x3C, (u32)((f32)alphaBase + depthDiff));
                gDPSetCycleType(dl++, G_CYC_1CYCLE);
                gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPMatrix(dl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPVertex(dl++, osVirtualToPhysical(vtx), 4, 0);
                gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
                drew = 1;
                gDPPipeSync(dl++);
            }
            gPlayerSlots[i].camHasWater = camState->hasWater;
            gPlayerSlots[i].camWaterY = camState->waterY;
        }
    }
    if (drew != 0) {
        gSPMatrix(dl++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(dl++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(dl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gUnderwaterTintSnap = 0;
    } else {
        gUnderwaterTintSnap = 1;
    }
    return dl;
}


void gfxDrawTexturedTileGridDefault(Gfx **gfx, void *texture, s32 fmt, s32 texWidth, s32 texHeight, s32 tileW, s32 tileH, f32 x0, f32 y0, f32 x1, f32 y1, f32 s0, f32 t0) {
    gfxDrawTexturedTileGrid(gfx, texture, fmt, texWidth, texHeight, tileW, tileH, x0, y0, x1, y1, s0, t0, 1, 0x10, 0, NULL);
}

void gfxDrawTexturedTileGridSimple(Gfx **gfx, void *texture, s32 fmt, u32 texWidth, u32 texHeight, s32 tileW, s32 tileH, f32 x0, f32 y0, f32 x1, f32 y1, f32 s0, f32 t0, u8 texScale, u8 bitSize) {
    gfxDrawTexturedTileGrid(gfx, texture, fmt, texWidth, texHeight, tileW, tileH, x0, y0, x1, y1, s0, t0, texScale, bitSize, 0, NULL);
}



void gfxDrawTexturedTileGrid(Gfx **gfx, void *texture, s32 fmt, u32 texWidth, s32 texHeight, u32 tileW, u32 tileH, f32 x0, f32 y0, f32 x1, f32 y1, f32 s0, f32 t0, u8 texScale, u8 bitSize, u8 edgeFade, void (*vtxCallback)()) {
    Gfx *dl;
    s32 y;
    Vtx *vtx;
    s32 posX;
    s32 posY;
    u32 stepX;
    s16 xa;
    s32 uls;
    s32 bottom;
    f32 thf;
    s32 x;
    s32 lrs;
    f32 xf;
    u32 xs;
    s32 right;
    u32 ys;
    s32 top;
    s32 lrt;
    u32 xe;
    s32 ult;
    u32 ye;
    u8 flag;
    s32 left;
    f32 yf;
    u32 tw;
    f32 twf;
    u32 th;
    u32 stepY;

    stepX = texScale * tileW;
    dl = *gfx;
    flag = 1;
    stepY = texScale * tileH;
    xs = x0 * 32.0f;
    xe = x1 * 32.0f;
    ye = y1 * 32.0f;
    th = tileH << 5;
    tw = tileW << 5;
    if (texWidth > 0x200) {
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        flag = 0;
    } else {
        gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    ys = y0 * 32.0f;
    vtx = heapAlloc(((xe - xs) / tw + 1) * ((ye - ys) / th + 1) * (4 * sizeof(Vtx)));
    heapFreeDeferred(vtx);
    gDPPipeSync(dl++);
    for (y = ys, posY = texScale * t0; y < ye; y += th, posY += stepY) {
        posX = texScale * s0;
        top = posY;
        for (x = xs; x < xe; x += tw, posX += stepX) {
            left = posX;
            uls = ((x >> 5) - 1) > 0 ? ((x >> 5) - 1) : 0;
            xf = (f32)x - 16.0;
            right = (s16)(posX + stepX);
            lrs = (((x >> 5) + tileW) < ((xe >> 5) - 1) ? ((x >> 5) + tileW) : ((xe >> 5) - 1));
            ult = ((y >> 5) - 1) > 0 ? ((y >> 5) - 1) : 0;
            lrt = ((((y >> 5) + tileH) < ((ye >> 5) - 1)) ? ((y >> 5) + tileH) : ((ye >> 5) - 1));
            if (bitSize == 8) {
                gDPLoadTextureTile(dl++, texture, fmt, G_IM_SIZ_8b, texWidth, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (bitSize == 0x10) {
                gDPLoadTextureTile(dl++, texture, fmt, G_IM_SIZ_16b, texWidth, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (bitSize == 0x20) {
                gDPLoadTextureTile(dl++, texture, fmt, G_IM_SIZ_32b, texWidth, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (bitSize == 4) {
                gDPLoadTextureTile_4b(dl++, texture, fmt, texWidth, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            }
            yf = (f32)y - 16.0;
            twf = tileW << 5;
            thf = tileH << 5;
            bottom = (s16)(posY + stepY);
            if (edgeFade) {
                if (x == xs && edgeFade == 1) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (vtxCallback != NULL) {
                vtxCallback(left, top, vtx);
            }
            vtxSetPosTex(vtx++, left, top, xf, yf, flag);
            if (edgeFade) {
                if (x + tw >= xe && edgeFade == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (vtxCallback != NULL) {
                vtxCallback(right, top, vtx);
            }
            xa = xf + twf;
            vtxSetPosTex(vtx++, right, top, xa, yf, flag);
            if (edgeFade) {
                if (x + tw >= xe && edgeFade == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (vtxCallback != NULL) {
                vtxCallback(right, bottom, vtx);
            }
            vtxSetPosTex(vtx++, right, bottom, xa, yf + thf, flag);
            if (edgeFade) {
                if (x == xs && edgeFade == 1) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (vtxCallback != NULL) {
                vtxCallback(left, bottom, vtx);
            }
            vtxSetPosTex(vtx++, left, bottom, xf, yf + thf, flag);
            gSPVertex(dl++, osVirtualToPhysical(vtx - 4), 4, 0);
            gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
            gDPPipeSync(dl++);
        }
    }
    *gfx = dl;
}

Gfx *gfxFillScreenColor(Gfx *dl, u8 r, u8 g, u8 b, u8 a) {
    if (a != 0) {
        gSPClearGeometryMode(dl++, 0xFFFFFFFF);
        gSPSetGeometryMode(dl++, G_SHADE | G_SHADING_SMOOTH);
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
        gDPPipeSync(dl++);
        gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
        gDPSetPrimColor(dl++, 0, 0, r, g, b, a);
        gDPSetCycleType(dl++, G_CYC_1CYCLE);
        gDPSetCombineMode(dl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetScissor(dl++, G_SC_NON_INTERLACE, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight, gGfxScreenBottom);
        gDPFillRectangle(dl++, gGfxScreenLeft, gGfxScreenTop, gGfxScreenRight, gGfxScreenBottom);
    }
    gDPPipeSync(dl++);
    return dl;
}


Gfx *gfxBuildScanlineNoise(Gfx *dl, s32 unused) {
    s16 i;
    s16 y;
    s32 r;
    s16 y2;

    gDPPipeSync(dl++);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetPrimColor(dl++, 0, 0, 0xC8, 0xC8, 0xC8, 0x80);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    gDPSetCombineLERP(dl++, NOISE, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, NOISE, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE);
    gDPSetScissor(dl++, G_SC_NON_INTERLACE, 10, 10, 0x135, 0xE5);
    gDPFillRectangle(dl++, 10, gPlayerSlots->rect[1], 0x135, gPlayerSlots->rect[3]);
    gDPPipeSync(dl++);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    gDPSetCombineMode(dl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    for (i = 0; i < 10; i++) {
        r = randomNonNegative() >> 15;
        y = r % (gPlayerSlots->rect[3] - gPlayerSlots->rect[1]) + gPlayerSlots->rect[1];
        r = randomNonNegative() >> 15;
        y2 = r % 10 + 2;
        gDPFillRectangle(dl++, 10, y, 0x135, y + y2);
    }
    gDPPipeSync(dl++);
    return dl;
}

extern s16 gLetterboxTopBarBottom;
extern s16 gLetterboxBottomBarTop;

void viewportShrinkToCenter(u8 amount) {
    f32 scale;

    scale = (f32)amount / 255.0;
    if (hudCanRender() != 0) {
        gPlayerSlots->rect[1] = (s32)((f32)gGfxScreenTop + ((f32)((gScreenHeight >> 1) - gGfxScreenTop - 1) * scale));
        gPlayerSlots->rect[3] = (s32)((f32)gGfxScreenBottom + ((f32)((gScreenHeight >> 1) - gGfxScreenBottom) * scale));
    } else {
        gPlayerSlots->rect[1] = (s32)((f32)gLetterboxTopBarBottom + ((f32)((gScreenHeight >> 1) - gLetterboxTopBarBottom - 1) * scale));
        gPlayerSlots->rect[3] = (s32)((f32)gLetterboxBottomBarTop + ((f32)((gScreenHeight >> 1) - gLetterboxBottomBarTop) * scale));
    }
    gPlayerSlots->rect[0] = (s32)((f32)gGfxScreenLeft + ((f32)((gScreenWidth >> 1) - gGfxScreenLeft - 1) * scale));
    gPlayerSlots->rect[2] = (s32)((f32)gGfxScreenRight + ((f32)((gScreenWidth >> 1) - gGfxScreenRight) * scale));
    gPlayerSlots->rectHeight = gPlayerSlots->rect[3] - gPlayerSlots->rect[1];
    gPlayerSlots->rectWidth = gPlayerSlots->rect[2] - gPlayerSlots->rect[0];
    gPlayerSlots->aspect = (f32)gPlayerSlots->rectWidth / (f32)gPlayerSlots->rectHeight;
}

Vtx D_80754C08[4] = {
    {{{ -128, -128, -10 }, 0, { -16384, 18432 }, { 0, 0, 0, 0 } }},
    {{{ 128, -128, -10 }, 0, { 18432, 18432 }, { 0, 0, 0, 0 } }},
    {{{ 128, 128, -10 }, 0, { 18432, -16384 }, { 0, 0, 0, 0 } }},
    {{{ -128, 128, -10 }, 0, { -16384, -16384 }, { 0, 0, 0, 0 } }},
};
// Full-screen gradient quad, one per framebuffer: screenFadeDrawGradient sets the right and bottom
// edges to the screen size and the corner alphas each frame.
Vtx gScreenFadeGradientVtx[2][4] = {
    {
        {{{ 0, 0, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
        {{{ 320, 0, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
        {{{ 320, 240, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
        {{{ 0, 240, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    },
    {
        {{{ 0, 0, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
        {{{ 320, 0, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
        {{{ 320, 240, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
        {{{ 0, 240, -10 }, 0, { 0, 0 }, { 0, 0, 0, 0 } }},
    },
};
Gfx *screenFadeDrawGradient(Gfx *dl, u8 alpha) {
    gSPDisplayList(dl++, &D_1000118);
    gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(dl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPClearGeometryMode(dl++, 0xFFFFFFFF);
    gSPSetGeometryMode(dl++, G_SHADE | G_SHADING_SMOOTH);
    gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    gDPPipeSync(dl++);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    gDPSetTexturePersp(dl++, G_TP_NONE);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    gDPSetCombineMode(dl++, G_CC_SHADE, G_CC_SHADE);
    gScreenFadeGradientVtx[gGfxBufferIndex][0].v.cn[3] = (alpha * 2 >= 0x100) ? 0xFF : alpha * 2;
    gScreenFadeGradientVtx[gGfxBufferIndex][1].v.cn[3] = alpha;
    gScreenFadeGradientVtx[gGfxBufferIndex][2].v.cn[3] = (alpha * 2 >= 0x100) ? 0xFF : alpha * 2;
    gScreenFadeGradientVtx[gGfxBufferIndex][3].v.cn[3] = alpha;
    gScreenFadeGradientVtx[gGfxBufferIndex][1].v.ob[0] = gScreenWidth;
    gScreenFadeGradientVtx[gGfxBufferIndex][2].v.ob[0] = gScreenWidth;
    gScreenFadeGradientVtx[gGfxBufferIndex][2].v.ob[1] = gScreenHeight;
    gScreenFadeGradientVtx[gGfxBufferIndex][3].v.ob[1] = gScreenHeight;
    gSPVertex(dl++, osVirtualToPhysical(gScreenFadeGradientVtx[gGfxBufferIndex]), 4, 0);
    gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
    gDPPipeSync(dl++);
    return dl;
}


extern u8 gHiResScale;

Gfx *screenFadeDrawSpinTexture(Gfx *dl, u8 alpha) {
    Mtx *mtx;
    f32 mf[4][4];
    f32 tmp[4][4];
    u8 *tex;
    f32 scale;
    f32 wave;

    if (alpha != 0) {
        tex = assetLoad(0xE, 0x5F, 0, 0);
        assetFreeBuffer(tex, 0x540, 0x2F);
        mtx = heapAlloc(0x40);
        heapFreeDeferred(mtx);
        gSPDisplayList(dl++, &D_1000118);
        gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
        gDPSetCombineLERP(dl++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPSetTextureFilter(dl++, G_TF_BILERP);
        gDPLoadTextureBlock_4b(dl++, tex + 0x80000000, G_IM_FMT_I, 64, 64, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        wave = sinApprox(alpha / 255.0 * 1.57079637050628662 + 3.14159274101257324) + 1.0;
        scale = (f32)(wave * 40.0f + 1.4) * gHiResScale;
        guScaleF(mf, scale, scale, scale);
        matrixMakeRotationZ(tmp, alpha / 255.0 * 360.0 * 1.5);
        guMtxCatF(mf, tmp, mf);
        guTranslateF(tmp, gScreenWidth >> 1, gScreenHeight >> 1, 0);
        guMtxCatF(mf, tmp, mf);
        guMtxF2L(mf, mtx);
        gSPMatrix(dl++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPVertex(dl++, osVirtualToPhysical(&D_80754C08), 4, 0);
        gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
        gDPPipeSync(dl++);
    }
    return dl;
}


extern s16 gVtxGradientPos;

void vtxGradientSetPosition(s16 pos) {
    gVtxGradientPos = pos;
}

extern u8 gVtxGradientRedA;
extern u8 gVtxGradientGreenA;
extern u8 gVtxGradientBlueA;

void vtxGradientSetColorA(u8 r, u8 g, u8 b) {
    gVtxGradientRedA = r;
    gVtxGradientGreenA = g;
    gVtxGradientBlueA = b;
}

extern u8 gVtxGradientRedB;
extern u8 gVtxGradientGreenB;
extern u8 gVtxGradientBlueB;

void vtxGradientSetColorB(u8 r, u8 g, u8 b) {
    gVtxGradientRedB = r;
    gVtxGradientGreenB = g;
    gVtxGradientBlueB = b;
}



void vtxSetColor(Vtx *vtx, u8 r, u8 g, u8 b, u8 a, u8 flags) {
    vtx->v.cn[0] = r;
    vtx->v.cn[1] = g;
    vtx->v.cn[2] = b;
    vtx->v.cn[3] = a;
    if (flags & 0x10) {
        f32 s;
        if (flags & 0x40) {
            s = mathSinF(a * 12.05 + 1024.0);
            vtx->v.ob[1] += 64.0f * s;
        } else {
            s = mathSinF(a * 12.05 + 1024.0);
            vtx->v.ob[1] -= 64.0f * s;
        }
    }
}

void vtxSetQuadGradientColors(Vtx *vtx, u8 row, u8 flags) {
    s16 lo;
    s16 hi;
    s16 wrapped;

    if (gVtxGradientPos >= 0x4000) {
        wrapped = gVtxGradientPos - 0x4200;
        lo = wrapped + row * 20;
        hi = wrapped + row * 20 + 10;
    } else {
        lo = gVtxGradientPos - row * 20;
        hi = gVtxGradientPos - row * 20 - 10;
    }
    if (lo < 0) {
        lo = 0;
    }
    if (lo >= 0x100) {
        lo = 0xFF;
    }
    if (hi < 0) {
        hi = 0;
    }
    if (hi >= 0x100) {
        hi = 0xFF;
    }
    vtxSetColor(vtx++, gVtxGradientRedA, gVtxGradientGreenA, gVtxGradientBlueA, lo, flags);
    vtxSetColor(vtx++, gVtxGradientRedA, gVtxGradientGreenA, gVtxGradientBlueA, hi, flags);
    vtxSetColor(vtx++, gVtxGradientRedB, gVtxGradientGreenB, gVtxGradientBlueB, hi, flags | 0x40);
    vtxSetColor(vtx, gVtxGradientRedB, gVtxGradientGreenB, gVtxGradientBlueB, lo, flags | 0x40);
}

void vtxSetPosTex(Vtx *vtx, s16 x, s16 y, s16 s, s16 t, u8 shift) {
    vtx->v.ob[0] = x;
    vtx->v.ob[1] = y;
    vtx->v.ob[2] = 0x3E8;
    vtx->v.tc[0] = (s << shift) & 0xFFFF;
    vtx->v.tc[1] = (t << shift) & 0xFFFF;
}


extern f32 gScreenFadeProgress;
extern f32 gScreenFadeRate;
extern s16 gCurrentLevelIndex;
extern u8 gActivePlayerCount;

Gfx *screenFadeUpdate(Gfx *dl, u8 mode) {
    s32 pad;
    u8 textIndex;
    u16 alpha;
    f32 progress;
    f32 val;

    if (gScreenFadeRate != 0.0f) {
        gScreenFadeProgress += gScreenFadeRate * (mode == 2 ? 2 : 1);
        if (gScreenFadeProgress < 0.0f) {
            mapGetWorldIndex(gCurrentWorldId);
            if (!(gScreenRenderFlags & 0x20) && mapTitleCheckShow(gCurrentLevelIndex, &textIndex)) {
                textSpawnMarkerChecked(1, 0, 0x64, textTableGetString(0x23, textIndex, 1), 0, 0x28, 6, 8);
                gScreenRenderFlags |= 0x20;
            }
            sfxStopChannel(0x2B, 0);
            if (transitionGetState() == 2) {
                transitionSetState(0);
            }
            gScreenFadeRate = 0.0f;
            gScreenFadeProgress = 0.0f;
            gScreenRenderFlags &= ~0x40;
        } else if (gScreenFadeProgress > 31.0f) {
            if (gScreenRenderFlags & 1) {
                sfxStopChannel(0x2C, 0);
            }
            gScreenFadeRate = 0.0f;
            gScreenFadeProgress = 31.0f;
            osViBlack(1);
            gScreenRenderFlags |= 0xC;
        } else {
            progress = gScreenFadeProgress * 0.03225806355f;
            val = gScreenFadeProgress * 255.0f / 28.0f;
            alpha = val < 0.0f ? 0.0f : (val > 255.0f ? 255.0f : val);
            if (gScreenFadeProgress < gScreenFadeRate * 2 + 31.0f && (gScreenRenderFlags & 4)) {
                gScreenRenderFlags ^= 6;
            }
            if (gScreenFadeProgress > 28.0f && mode != 3) {
                dl = gfxFillScreenColor(dl, 0, 0, 0, 0xFF);
            } else {
                switch (mode) {
                    case 3:
                        if (gActivePlayerCount == 1) {
                            viewportShrinkToCenter(alpha);
                            break;
                        }
                    case 2:
                        dl = screenFadeDrawGradient(dl, alpha);
                        break;
                    case 1:
                        dl = screenFadeDrawSpinTexture(dl, alpha);
                        break;
                    default:
                        dl = gfxFillScreenColor(dl, 0, 0, 0, alpha);
                        break;
                }
            }
            if ((gScreenRenderFlags & 0x41) || !(gScreenRenderFlags & 0x20)) {
                s32 channels[3] = { 1, 3, 0 }; /* zero-terminated sequence channels that follow the fade */
                s32 pad2;

                transitionSetAudioVolume(1.0f - progress, gScreenFadeRate >= 0.0f, channels);
            }
        }
    }
    return dl;
}

