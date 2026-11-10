#include "common.h"
#include "actor.h"
#include "sched.h"
#define PROTO_SKIP_renderRotatedSprite // FAKE: callee prototype steer
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

Gfx *renderRotatedSprite(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32); // FAKE: callee prototype steer

Gfx *func_806FEF7C(Gfx *dl, Actor *player) {
    dl = playerViewGfxSetup(dl, ((PlayerState *)player->customState)->playerIndex);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    return renderRotatedSprite(dl, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, 0.001f);
}

extern u8 *D_807FD568;

Gfx *func_806FF01C(Gfx *gfx, Actor *actor) {
    u8 player;
    s32 target;
    s32 targetX;
    s32 targetY;
    s32 targetZ;
    Gfx *dl;

    player = ((PlayerState *)actor->customState)->playerIndex;
    dl = playerViewGfxSetup(gfx, player);
    if ((D_807FD568[2] & 2) && slotQueueGetValue(3, player) &&
        projectileFindHomingTarget(2, &target, actor, 1, 0, 0, &targetX, &targetY, &targetZ)) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xC8, 0, 0xFF);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 0xC8, 0, 0, 0xFF);
    }
    return renderRotatedSprite(dl, 0x38, 3, 1, 0x40, 0x40, 0xA0, 0x78, 0.5f, 0.5f, 0x2D, 0.0f);
}

Gfx *func_806FF144(Gfx *dl) {
    gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
    gDPSetCombineMode(dl++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x3E, 0x3E, 2.0f, 2.0f, 0, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, gScreenWidth - 0x3E, 0x3E, 2.0f, 2.0f, 0x5A, 0.0f);
    dl = renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, gScreenWidth - 0x3E, gScreenHeight - 0x3E, 2.0f, 2.0f, 0xB4, 0.0f);
    return renderRotatedSprite(dl, 0x3A, 3, 1, 0x40, 0x40, 0x3E, gScreenHeight - 0x3E, 2.0f, 2.0f, 0x10E, 0.0f);
}

void func_806FF32C(Gfx *dl, Actor *actor) {
    func_806FF144(playerViewGfxSetup(dl, ((PlayerState *)actor->customState)->playerIndex));
}

Gfx *func_806FF358(Gfx *dl, Actor *actor) {
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
        if (state->unk1EC == 2) {
            gDPSetPrimColor(dl++, 0, 0, 0xFF, 0, 0, 0xFF);
            dl = renderRotatedSprite(dl, 0x43, 3, 1, 0x40, 0x40, 0x118, 0x28, 0.5f, 0.5f, 0, 0.0f);
        } else if (state->unk1EC == 1) {
            gDPSetPrimColor(dl++, 0, 0, 0, 0xFF, 0, 0xFF);
            dl = renderRotatedSprite(dl, 0x2F, 3, 1, 0x40, 0x40, 0x118, 0x28, 0.5f, 0.5f, 0, 0.0f);
        }
    }
    return dl;
}

Gfx *func_806FF628(Gfx *dl, Actor *actor) {
    PlayerState *state;

    state = gPlayerSlots->actor->customState;
    dl = playerViewGfxSetup(dl, state->playerIndex);
    if (state->unk1EC == 2) {
        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0, 0, 0x64);
        dl = renderRotatedSprite(dl, 0x45, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
    } else if (state->unk1EC == 1) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xFF, 0, 0x64);
        dl = renderRotatedSprite(dl, 0x44, 3, 1, 0x40, 0x40, 0xA0, 0x78, 2.0f, 2.0f, 0, 0.0f);
    }
    return dl;
}


Gfx *func_806FF75C(Gfx *dl, Actor *actor) {
    u8 player;
    s32 target;
    s32 targetKind;
    s32 targetX;
    s32 targetY;
    s32 targetZ;

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
    if (slotQueueGetValue(3, player) && projectileFindHomingTarget((u16)targetKind, &target, actor, 1, 0, 0, &targetX, &targetY, &targetZ)) {
        gDPSetPrimColor(dl++, 0, 0, 0, 0xC8, 0, 0xFF);
    } else {
        gDPSetPrimColor(dl++, 0, 0, 0xC8, 0, 0, 0xFF);
    }
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
    return renderRotatedSprite(dl, 0x38, 3, 1, 0x40, 0x40, 0xA0, 0x78, 0.5f, 0.5f, 0x2D, 0.0f);
}

void func_806FFB2C(Gfx *gfx, Actor *actor) {
    f32 depth;
    Gfx *dl;

    depth = actor->unk155 * 1.4;
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

s16 *func_806FFEAC(s16 *dst, u16 *src) {
    s16 i;
    s16 j;

    for (i = 0; i < 0x40; i++) {
        for (j = 0; j < 0x20; j++) {
            *dst++ = color5551ToSepia(src[j + i * gScreenWidth]);
        }
    }
    return dst;
}


void func_806FFF5C(void) {
    assetLoad(0x19, 0x138B, 1, 1);
}

extern void *gFramebuffers[];

s16 *func_806FFF88(void) {
    s16 *buf;
    s16 col;
    s16 row;
    s16 *dst;
    u16 *src;

    if (gCurrentActor->actorType == 0xD9) {
        func_806FFF5C();
        return;
    }
    buf = heapAlloc(0xA000);
    dst = buf;
    src = (u16 *)gFramebuffers[gGfxBufferIndex] + gScreenWidth * 56 + 80;
    row = 0;
    do {
        col = 0;
        do {
            dst = func_806FFEAC(dst, src + col * 32);
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

    *outBuf = (s16 *)heapAlloc(0xA000);
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

extern ScreenPoint D_807FD840[2][3];

typedef struct LensFlarePoint {
    f32 x;
    f32 y;
    f32 z;
    u8 r;
    u8 g;
    u8 b;
    u8 unkF;
} LensFlarePoint;

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

extern u8 D_80754BC0;
extern LensFlarePoint D_807FD808[2];


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

    if (D_80754BC0 < 2) {
        visible = 1;
        if (minDot != 0.0f) {
            delta.x = dirX - x;
            delta.y = dirY - y;
            delta.z = dirZ - z;
            vec3fNormalize(&dir, delta);
            delta.x = gPlayerSlots->camX - x;
            delta.y = gPlayerSlots->camY - y;
            delta.z = gPlayerSlots->camZ - z;
            vec3fNormalize(&toCam, delta);
            dot = (toCam.x * dir.x) + (toCam.y * dir.y) + (toCam.z * dir.z);
            if (dot < 0.0) {
                dot = 0.0f;
            }
            if (dot < minDot) {
                visible = 0;
            }
        }
        if (visible != 0) {
            D_807FD840[gGfxBufferIndex][D_80754BC0].depth = sqrtf((gPlayerSlots->unk224 - z) * (gPlayerSlots->unk224 - z) + ((gPlayerSlots->unk21C - x) * (gPlayerSlots->unk21C - x) + (gPlayerSlots->unk220 - y) * (gPlayerSlots->unk220 - y))) > 995.0f ? 995.0f : sqrtf((gPlayerSlots->unk224 - z) * (gPlayerSlots->unk224 - z) + ((gPlayerSlots->unk21C - x) * (gPlayerSlots->unk21C - x) + (gPlayerSlots->unk220 - y) * (gPlayerSlots->unk220 - y)));
            camProjectToScreen(x, y, z, &screenX, &screenY, 0, 4.0f, 0);
            D_807FD840[gGfxBufferIndex][D_80754BC0].x = screenX * 0.25;
            D_807FD840[gGfxBufferIndex][D_80754BC0].y = screenY * 0.25;
            D_807FD808[D_80754BC0].x = x;
            D_807FD808[D_80754BC0].y = y;
            D_807FD808[D_80754BC0].z = z;
            D_807FD808[D_80754BC0].r = r;
            D_807FD808[D_80754BC0].g = g;
            D_807FD808[D_80754BC0].b = b;
            D_80754BC0 += 1;
        }
    }
}

extern u8 D_2000100[];

Gfx *func_8070068C(Gfx *dl) {
    gSPMatrix(dl++, &D_2000100, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPViewport(dl++, osVirtualToPhysical(&gPlayerSlots->viewport[gGfxBufferIndex]));
    gDPSetScissor(dl++, G_SC_NON_INTERLACE, gPlayerSlots->rect[0], gPlayerSlots->rect[1], gPlayerSlots->rect[2], gPlayerSlots->rect[3]);
    return dl;
}

extern u8 D_807FD838[2][3];
extern u8 D_2000180;

Gfx *lensFlareBuildDisplayList(Gfx *dl) {
    s16 i;

    if (D_80754BC0 != 0) {
        gDPPipeSync(dl++);
        dl = func_8070068C(dl);
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
        for (i = 0; i < D_80754BC0; i++) {
            if (D_807FD838[gGfxBufferIndex ^ 1][i] != 0) {
                dl = lensFlareDrawSource(dl, D_807FD808[i], (u32)(D_807FD838[gGfxBufferIndex ^ 1][i]--));
            }
        }
        gDPSetColorDither(dl++, G_CD_MAGICSQ);
        gDPSetAlphaDither(dl++, G_AD_PATTERN);
    }
    return dl;
}

extern s16 *D_8076A0A0;

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
        if (depth < D_8076A0A0[mid]) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
        if (depth >= D_8076A0A0[mid] && depth < D_8076A0A0[mid + 1]) {
            return mid + 8;
        }
    } while (hi >= lo);
    dist = depth - 0x7C1B;
    return dist < 0 ? 0 : dist;
}

typedef struct {
    s32 words[16]; /* (shift, offset) pairs per 3-bit exponent */
} ZbufferDecodeTable;
extern ZbufferDecodeTable D_80754BC4;
extern u16 *gGfxDepthBuffer;

s32 zbufferReadDepth(s16 x, s16 y) {
    ZbufferDecodeTable table;
    u16 z;
    u16 mantissa;
    s32 *entry;
    u16 *depth;
    s32 result;
    ZbufferDecodeTable *tablePtr;

    table = D_80754BC4;
    tablePtr = &table; // FAKE: pointer temp steers the table address registers
    depth = gGfxDepthBuffer;
    if (x < gPlayerSlots->rect[0] || gPlayerSlots->rect[2] < x || y < gPlayerSlots->rect[1] || gPlayerSlots->rect[3] < y) {
        return 0xFFFF;
    }
    depth += gScreenWidth * y + x;
    z = *depth;
    entry = tablePtr->words + (((z >> 13) & 0xFFFF & 0xFFFF & 0xFFFF & 0xFFFF & 0xFFFF & 0xFFFF & 0xFFFF & 7) * 2); // FAKE: no-op masks advance the ugen temp ring (Q0374)
    mantissa = z >> 2;
    result = ((mantissa & 0x7FF) << entry[0]) + entry[1];
    return ((u32)result >> 3) & 0xFFFF;
}

extern s32 gGlobalPauseFlags;
extern s16 D_807FD800;
extern s16 D_807FD802;
extern s16 D_807FD804;
extern s16 D_807FD806;


typedef struct {
    u8 pad0[0x2E];
    s8 stickX;
    u8 pad2F;
    u8 stickMagnitude;
    u8 pad31[3];
} PlayerSampleInfo;

extern PlayerSampleInfo gPlayerPadState[];


void func_80700BF4(void) {
    u8 i;
    PlayerState *state;
    s16 x;
    s16 y;
    u16 halfWidth;
    s32 margin;
    PlayerSampleInfo *pad;
    s32 depth;
    s32 blocked;
    s32 invalid = 0x7FFF; // FAKE: value-named constant local keeps 0x7FFF in a saved register

    if (D_80754BC0 != 0) {
        do {
            D_80754BC0--;
            if ((f32)gPlayerSlots->rect[0] < D_807FD840[gGfxBufferIndex][D_80754BC0].x &&
                D_807FD840[gGfxBufferIndex][D_80754BC0].x < (f32)gPlayerSlots->rect[2] &&
                (f32)gPlayerSlots->rect[1] < D_807FD840[gGfxBufferIndex][D_80754BC0].y &&
                D_807FD840[gGfxBufferIndex][D_80754BC0].y < (f32)gPlayerSlots->rect[3] &&
                !(gGlobalPauseFlags & 2)) {
                if (D_807FD840[gGfxBufferIndex][D_80754BC0].depth <
                    (f32)zbufferDepthToDistance(zbufferReadDepth((s16)D_807FD840[gGfxBufferIndex][D_80754BC0].x,
                                                     (s16)D_807FD840[gGfxBufferIndex][D_80754BC0].y))) {
                    D_807FD838[gGfxBufferIndex][D_80754BC0] = 5;
                }
            }
        } while (D_80754BC0 != 0);
    }
    depth = zbufferReadDepth(0xA0, 0xDC);
    blocked = invalid == depth;
    if (blocked == 0) {
        depth = zbufferReadDepth(0xC, 0x78);
        blocked = invalid == depth;
        if (blocked == 0) {
            depth = zbufferReadDepth(0x134, 0x78);
            blocked = invalid == depth;
        }
    }
    D_807FD800 = blocked;
    D_807FD802 = zbufferDepthToDistance(zbufferReadDepth(D_807FD804, D_807FD806));
    margin = 40; // FAKE: constant local (a literal shrinks the frame by 8)
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].unk0 != 0) {
            state = (PlayerState *)gPlayerSlots[i].actor->customState;
            pad = &gPlayerPadState[i];
            x = state->targetPitch;
            y = state->targetRoll - 0x14;
            x += pad->stickX;
            halfWidth = (u32)(margin + pad->stickMagnitude / 1.5);
            state->depthCenter = zbufferDepthToDistance(zbufferReadDepth(x, y));
            state->unk116 = zbufferDepthToDistance(zbufferReadDepth(x, state->targetYawAngle));
            state->depthLeft = zbufferDepthToDistance(zbufferReadDepth(x - halfWidth, y));
            state->depthRight = zbufferDepthToDistance(zbufferReadDepth(x + halfWidth, y));
        }
    }
}

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

extern LensFlareSprite D_80754AF0[];
Vec3f vec3fSub(Vec3f, Vec3f);
Vec3f vec3fAdd(Vec3f, Vec3f);
Vec3f vec3fScale(Vec3f, f32);
f32 vec3fDot(Vec3f, Vec3f);

Gfx *lensFlareDrawSource(dl, pt, fade, i) // FAKE: K&R 4th parameter `i` (callers pass 3 args) gives the loop counter no frame home
Gfx *dl;
LensFlarePoint pt;
u8 fade;
s16 i;
{
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
    f32 pad2[4];
    f32 screenY;
    f32 alpha;
    f32 facing;
    f32 colorScale;
    f32 alphaScale;

    alpha = fade / 5.0;
    vec3fSet(&src, pt.x, pt.y, pt.z);
    vec3fSet(&eye, gPlayerSlots->unk21C, gPlayerSlots->unk220, gPlayerSlots->unk224);
    vec3fSet(&at, gPlayerSlots->unk234, gPlayerSlots->unk238, gPlayerSlots->unk23C);
    vec3fNormalize(&viewDir, vec3fSub(at, eye));
    axisEnd = vec3fAdd(eye, vec3fScale(viewDir, 5000.0f));
    vec3fNormalize(&srcDir, vec3fSub(src, eye));
    facing = vec3fDot(srcDir, viewDir) < 1e-05 ? 1e-05 : vec3fDot(srcDir, viewDir);
    src = vec3fAdd(eye, vec3fScale(vec3fScale(srcDir, 5000.0f), 1.0f / facing));
    axisSpan = vec3fSub(src, axisEnd);
    if (facing < 0.0f) {
        return dl;
    }
    for (i = 0; i < 12; i++) {
        alphaScale = (facing < 0.75 ? 0.0 : facing - 0.75) * 4.0;
        colorScale = alphaScale < 0.85 ? 0.85 : alphaScale;
        switch (i) {
        case 11:
            screenX = 640.0f;
            screenY = 480.0f;
            alphaScale = (facing < 0.9 ? 0.0 : facing - 0.9) * 10.0;
            colorScale = alphaScale < 0.85 ? 0.85 : alphaScale;
            break;
        case 0:
        case 12:
            alphaScale = (facing < 0.25 ? 0.0 : facing - 0.25) * 1.333;
            colorScale = alphaScale < 0.85 ? 0.85 : alphaScale;
            camProjectToScreen(src.x, src.y, src.z, &screenX, &screenY, 0, 4.0f, 0);
            break;
        default:
            pos = vec3fAdd(axisEnd, vec3fScale(axisSpan, D_80754AF0[i].axisPos));
            camProjectToScreen(pos.x, pos.y, pos.z, &screenX, &screenY, 0, 4.0f, 0);
            break;
        }
        gDPPipeSync(dl++);
        gDPSetPrimColor(dl++, 0, 0, (u32)((pt.r / 255.0) * D_80754AF0[i].r * colorScale), (u32)((pt.g / 255.0) * D_80754AF0[i].g * colorScale), (u32)((pt.b / 255.0) * D_80754AF0[i].b * colorScale), (u32)((f32)D_80754AF0[i].a * alphaScale * alpha));
        dl = renderRotatedSprite(dl, (D_80754AF0[i].texOffset + 0x4D) & 0xFFFF, 3, 1, 0x40, 0x40, (s32)screenX, (s32)screenY, D_80754AF0[i].scale * 4.0f * alpha, D_80754AF0[i].scale * 4.0f * alpha, 0, 0.0f);
    }
    dl->words.w0 = 0xE7000000; dl->words.w1 = 0;
    dl++;
    if (facing > 0.97) {
        dl = gfxFillScreenColor(dl, pt.r, pt.g, pt.b, (u32)((facing - 0.97) * 33.0 * 128.0));
        dl->words.w0 = 0xD7000002; dl->words.w1 = 0x80008000;
        dl[1].words.w0 = 0xFC119623; dl[1].words.w1 = 0xFF2FFFFF;
        dl += 2;
    }
    return dl;
}

extern u8 D_807FD890;

void func_80701C90(void) {
    D_807FD890 = 1;
}

extern Mtx D_2000000;
extern Mtx D_2000200;

Gfx *func_80701CA0(Gfx *dl) {
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
        if ((gPlayerSlots[0].unk290 == 9 || gPlayerSlots[0].unk290 == 0xA) && flagGet(0x9C, 0) != 0) {
            return dl;
        }
    default:
        break;
    }
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].unk0 != 0) {
            playerState = gPlayerSlots[i].actor->customState;
            camActor = playerState->camActor;
            camState = camActor->customState;
            if (force != 0 || (gPlayerSlots[i].unk2E8 != 0 && gPlayerSlots[i].unk220 < gPlayerSlots[i].unk24C + 3.0f)) {
                vtx = (Vtx *)heapAlloc(0x40);
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
                depthDiff = gPlayerSlots[i].unk24C - gPlayerSlots[i].unk220;
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
                if (D_807FD890 != 0) {
                    playerState->unk1E8 = depthDiff;
                } else {
                    playerState->unk1E8 = playerState->unk1E8 + (f64)(depthDiff - playerState->unk1E8) * 0.05;
                    depthDiff = (u32)playerState->unk1E8 & 0xFF;
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
            gPlayerSlots[i].unk2E8 = camState->unkFA;
            gPlayerSlots[i].unk24C = camState->unk90;
        }
    }
    if (drew != 0) {
        gSPMatrix(dl++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(dl++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(dl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        D_807FD890 = 0;
    } else {
        D_807FD890 = 1;
    }
    return dl;
}


void gfxDrawTexturedTileGridDefault(Gfx **gfx, s32 fmt, s32 texture, s32 texWidth, s32 texHeight, s32 tileW, s32 tileH, f32 x0, f32 y0, f32 x1, f32 y1, f32 s0, f32 t0) {
    gfxDrawTexturedTileGrid(gfx, fmt, texture, texWidth, texHeight, tileW, tileH, x0, y0, x1, y1, s0, t0, 1, 0x10, 0, 0);
}

void gfxDrawTexturedTileGridSimple(Gfx **gfx, s32 fmt, s32 texture, s32 texWidth, s32 texHeight, s32 tileW, s32 tileH, f32 x0, f32 y0, f32 x1, f32 y1, f32 s0, f32 t0, u8 texScale, u8 bitSize) {
    gfxDrawTexturedTileGrid(gfx, fmt, texture, texWidth, texHeight, tileW, tileH, x0, y0, x1, y1, s0, t0, texScale, bitSize, 0, 0);
}

typedef struct VtxColorView {
    s16 x;
    s16 y;
    s16 z;
    u8 unk6[2];
    s16 s;
    s16 t;
    s8 r;
    s8 g;
    s8 b;
    u8 a;
} VtxColorView;


void gfxDrawTexturedTileGrid(Gfx **gfx, s32 fmt, s32 texture, u32 texWidth, s32 texHeight, u32 tileW, u32 tileH, f32 x0, f32 y0, f32 x1, f32 y1, f32 s0, f32 t0, u8 texScale, u8 bitSize, u8 edgeFade, void (*vtxCallback)()) {
    Gfx *dl;
    s32 y;
    VtxColorView *vtx;
    s32 u;
    s32 v;
    u32 ustep;
    s16 xa;
    s32 uls;
    s32 vb;
    s32 rowY;
    s32 x;
    s32 lrs;
    f32 xf;
    u32 xs;
    s32 ua;
    u32 ys;
    s32 rowT;
    s32 lrt;
    u32 xe;
    s32 ult;
    u32 ye;
    u8 flag;
    s32 colS;
    f32 fsc;
    u32 tw;
    f32 twf;
    u32 th;
    u32 vstep;

    ustep = texScale * tileW;
    dl = *gfx;
    flag = 1;
    vstep = texScale * tileH;
    xs = (u32)(x0 * 32.0f);
    xe = (u32)(x1 * 32.0f);
    ye = (u32)(y1 * 32.0f);
    th = tileH << 5;
    tw = tileW << 5;
    if (texWidth > 0x200) {
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        flag = 0;
    } else {
        gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    ys = (u32)(y0 * 32.0f);
    vtx = heapAlloc((((xe - xs) / tw + 1) * ((ye - ys) / th + 1)) << 6);
    heapFreeDeferred(vtx);
    gDPPipeSync(dl++);
    for (y = ys, v = (s32)((f32)texScale * t0); y < ye; y += th, v += vstep) {
        u = ((s32)((f32)texScale * s0));
        rowT = v; // FAKE: redundant copy of v steers register allocation
        rowY = y; // FAKE: redundant copy of y steers register allocation
        for (x = xs; x < xe; x += tw, u += ustep) {
            colS = u; // FAKE: redundant copy of u steers register allocation
            uls = ((x >> 5) - 1) > 0 ? ((x >> 5) - 1) : 0;
            xf = (f32)x - 16.0;
            ua = (s16)(u + ustep);
            lrs = (((x >> 5) + tileW) < ((xe >> 5) - 1) ? ((x >> 5) + tileW) : ((xe >> 5) - 1));
            ult = ((y >> 5) - 1) > 0 ? ((y >> 5) - 1) : 0;
            lrt = ((((y >> 5) + tileH) < ((ye >> 5) - 1)) ? ((y >> 5) + tileH) : ((ye >> 5) - 1));
            if (bitSize == 8) {
                gDPLoadTextureTile(dl++, fmt, texture, G_IM_SIZ_8b, texWidth, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (bitSize == 0x10) {
                gDPLoadTextureTile(dl++, fmt, texture, G_IM_SIZ_16b, texWidth, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (bitSize == 0x20) {
                gDPLoadTextureTile(dl++, fmt, texture, G_IM_SIZ_32b, texWidth, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            } else if (bitSize == 4) {
                gDPLoadTextureTile_4b(dl++, fmt, texture, texWidth, 0, uls, ult, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            }
            fsc = (f32)y - 16.0; // FAKE: dead store steers float register allocation
            twf = tileW << 5;
            vb = (s16)(v + vstep);
            if (edgeFade) {
                if (x == xs && edgeFade == 1) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (vtxCallback != NULL) {
                vtxCallback(u, v, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, colS, rowT, xf, (s16)(f32)((f32)rowY - 16.0), flag);
            if (edgeFade) {
                if (x + tw >= xe && edgeFade == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (vtxCallback != NULL) {
                vtxCallback((s16)(u + ustep), v, vtx);
            }
            xa = xf + twf;
            vtxSetPosTex((s16 *)vtx++, ua, rowT, xa, (s16)(f32)((f32)rowY - 16.0), flag);
            if (edgeFade) {
                if (x + tw >= xe && edgeFade == 2) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (vtxCallback != NULL) {
                vtxCallback(ua, vb, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, ua, vb, xa, (s16)((f32)((f32)rowY - 16.0) + (f32)th), flag);
            if (edgeFade) {
                if (x == xs && edgeFade == 1) {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0, 0);
                } else {
                    vtxSetColor(vtx, 0xFF, 0xFF, 0xFF, 0xFF, 0);
                }
            }
            if (vtxCallback != NULL) {
                vtxCallback(u, vb, vtx);
            }
            vtxSetPosTex((s16 *)vtx++, colS, vb, xf, (s16)((f32)((f32)rowY - 16.0) + (f32)th), flag);
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

extern s16 D_807444AC;
extern s16 D_807444B0;

void viewportShrinkToCenter(u8 amount) {
    f32 scale;

    scale = (f32)amount / 255.0;
    if (hudCanRender() != 0) {
        gPlayerSlots->rect[1] = (s32)((f32)gGfxScreenTop + ((f32)((gScreenHeight >> 1) - gGfxScreenTop - 1) * scale));
        gPlayerSlots->rect[3] = (s32)((f32)gGfxScreenBottom + ((f32)((gScreenHeight >> 1) - gGfxScreenBottom) * scale));
    } else {
        gPlayerSlots->rect[1] = (s32)((f32)D_807444AC + ((f32)((gScreenHeight >> 1) - D_807444AC - 1) * scale));
        gPlayerSlots->rect[3] = (s32)((f32)D_807444B0 + ((f32)((gScreenHeight >> 1) - D_807444B0) * scale));
    }
    gPlayerSlots->rect[0] = (s32)((f32)gGfxScreenLeft + ((f32)((gScreenWidth >> 1) - gGfxScreenLeft - 1) * scale));
    gPlayerSlots->rect[2] = (s32)((f32)gGfxScreenRight + ((f32)((gScreenWidth >> 1) - gGfxScreenRight) * scale));
    gPlayerSlots->unk27A = gPlayerSlots->rect[3] - gPlayerSlots->rect[1];
    gPlayerSlots->unk278 = gPlayerSlots->rect[2] - gPlayerSlots->rect[0];
    gPlayerSlots->unk280 = (f32)gPlayerSlots->unk278 / (f32)gPlayerSlots->unk27A;
}

typedef struct {
    s16 x0, y0;
    u8 pad0[0xB];
    u8 a0;
    s16 x1, y1;
    u8 pad1[0xB];
    u8 a1;
    s16 x2, y2;
    u8 pad2[0xB];
    u8 a2;
    s16 x3, y3;
    u8 pad3[0xB];
    u8 a3;
} ScreenQuadVtx;

extern ScreenQuadVtx D_80754C48[];

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
    D_80754C48[gGfxBufferIndex].a0 = (alpha * 2 >= 0x100) ? 0xFF : alpha * 2;
    D_80754C48[gGfxBufferIndex].a1 = alpha;
    D_80754C48[gGfxBufferIndex].a2 = (alpha * 2 >= 0x100) ? 0xFF : alpha * 2;
    D_80754C48[gGfxBufferIndex].a3 = alpha;
    D_80754C48[gGfxBufferIndex].x1 = gScreenWidth;
    D_80754C48[gGfxBufferIndex].x2 = gScreenWidth;
    D_80754C48[gGfxBufferIndex].y2 = gScreenHeight;
    D_80754C48[gGfxBufferIndex].y3 = gScreenHeight;
    gSPVertex(dl++, osVirtualToPhysical(&D_80754C48[gGfxBufferIndex]), 4, 0);
    gSP2Triangles(dl++, 0, 1, 2, 0, 0, 2, 3, 0);
    gDPPipeSync(dl++);
    return dl;
}


extern u8 gHiResScale;
extern u8 D_80754C08[];
f32 sinApprox(f32);

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
        mtx = (Mtx *)heapAlloc(0x40);
        heapFreeDeferred(mtx);
        gSPDisplayList(dl++, &D_1000118);
        gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504340);
        gDPSetCombineLERP(dl++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(dl++, 0, 0, 0, 0, 0, 0xFF);
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPSetTextureFilter(dl++, G_TF_BILERP);
        gDPLoadTextureBlock_4b(dl++, tex + 0x80000000, G_IM_FMT_I, 64, 64, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        wave = sinApprox((f32)((u32)alpha / 255.0 * 1.57079637050628662 + 3.14159274101257324)) + 1.0;
        scale = (f32)(wave * 40.0f + 1.4) * (u32)gHiResScale;
        guScaleF(mf, scale, scale, scale);
        matrixMakeRotationZ(tmp, (f32)((u32)alpha / 255.0 * 360.0 * 1.5));
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


extern s16 D_807FD892;

void vtxGradientSetPosition(s16 pos) {
    D_807FD892 = pos;
}

extern u8 D_807FD894;
extern u8 D_807FD895;
extern u8 D_807FD896;

void vtxGradientSetColorA(s8 r, s8 g, s8 b) {
    D_807FD894 = r;
    D_807FD895 = g;
    D_807FD896 = b;
}

extern u8 D_807FD897;
extern u8 D_807FD898;
extern u8 D_807FD899;

void vtxGradientSetColorB(s8 r, s8 g, s8 b) {
    D_807FD897 = r;
    D_807FD898 = g;
    D_807FD899 = b;
}


f32 mathSinF(s16);

void vtxSetColor(VtxColorView *vtx, u8 r, u8 g, u8 b, u8 a, u8 flags) {
    vtx->r = r;
    vtx->g = g;
    vtx->b = b;
    vtx->a = a;
    if (flags & 0x10) {
        f32 s;
        if (flags & 0x40) {
            s = mathSinF((s16)(s32)((a * 12.05) + 1024.0));
            vtx->y = (s16)(s32)((f32)vtx->y + 64.0f * s);
        } else {
            s = mathSinF((s16)(s32)((a * 12.05) + 1024.0));
            vtx->y = (s16)(s32)((f32)vtx->y - 64.0f * s);
        }
    }
}

void vtxSetQuadGradientColors(VtxColorView *vtx, u8 row, u8 flags) {
    s16 lo;
    s16 hi;
    s32 t;

    if (D_807FD892 >= 0x4000) {
        t = D_807FD892 - 0x4200;
        lo = t;
        lo += row * 20;
        hi = t;
        hi += row * 20 + 10;
    } else {
        lo = D_807FD892 - row * 20;
        hi = D_807FD892 - row * 20 - 10;
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
    vtxSetColor(vtx++, D_807FD894, D_807FD895, D_807FD896, lo, flags);
    vtxSetColor(vtx++, D_807FD894, D_807FD895, D_807FD896, hi, flags);
    vtxSetColor(vtx++, D_807FD897, D_807FD898, D_807FD899, hi, flags | 0x40);
    vtxSetColor(vtx, D_807FD897, D_807FD898, D_807FD899, lo, flags | 0x40);
}

void vtxSetPosTex(s16 *vtx, s16 s, s16 t, s16 x, s16 y, u8 shift) {
    vtx[0] = s;
    vtx[1] = t;
    vtx[2] = 0x3E8;
    vtx[4] = (x << shift) & 0xFFFF;
    vtx[5] = (y << shift) & 0xFFFF;
}


typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} ScreenFadeChannels;

extern f32 gScreenFadeProgress;
extern f32 gScreenFadeRate;
extern s16 gCurrentLevelIndex;
extern u8 gActivePlayerCount;
extern ScreenFadeChannels D_80754CC8;

Gfx *screenFadeUpdate(Gfx *dl, u8 mode) {
    s32 pad1;
    u8 textIndex;
    f32 progress;
    s32 pad2;
    ScreenFadeChannels volume;
    f32 val;
    u16 alpha;

    if (gScreenFadeRate != 0.0f) {
        gScreenFadeProgress += gScreenFadeRate * (mode == 2 ? 2 : 1);
        if (gScreenFadeProgress < 0.0f) {
            mapGetWorldIndex(gCurrentWorldId);
            if (!(gScreenRenderFlags & 0x20) && func_80600454(gCurrentLevelIndex, &textIndex)) {
                textSpawnMarkerChecked(1, 0, 0x64, textTableGetString(0x23, textIndex, 1), 0, 0x28, 6, 8);
                gScreenRenderFlags |= 0x20;
            }
            sfxStopChannel(0x2B, 0);
            if (transitionGetState() == 2) {
                transitionSetState(0);
            }
            gScreenFadeRate = 0.0f;
            gScreenFadeProgress = 0.0f;
            gScreenRenderFlags &= 0xFFBF;
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
                volume = D_80754CC8;
                transitionSetAudioVolume(1.0f - progress, gScreenFadeRate >= 0.0f, &volume);
            }
        }
    }
    return dl;
}

