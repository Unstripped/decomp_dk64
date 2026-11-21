#include "common.h"
#include "actor.h"
#include "cutscene.h"
#include "sched.h"
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/15050.h"
#include "proto/global/17800.h"
#include "proto/global/450.h"
#include "proto/global/6AD90.h"
#include "proto/global/90D80.h"

// This TU's .data (0x807501E0-0x80750270), in address order; D_807501E8 is 8-aligned (Vtx).
u8 gRenderCallbackCount = 0;
Vtx D_807501E8[4] = {
    {{ { -16, 16, 1000 }, 0, { 0, 1984 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { 16, 16, 1000 }, 0, { 1984, 1984 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { 16, -16, 1000 }, 0, { 1984, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { -16, -16, 1000 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
};
f32 D_80750228 = 0.0f;
f32 D_8075022C = 0.0f;
Vtx D_80750230[4] = {
    {{ { 0, 0, -10 }, 0, { 0, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { 320, 0, -10 }, 0, { 2016, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { 320, 240, -10 }, 0, { 2016, 2016 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
    {{ { 0, 240, -10 }, 0, { 0, 2016 }, { 0xFF, 0xFF, 0xFF, 0xFF } }},
};

typedef struct TexCacheEntry {
    /* 0x0 */ void *tex;
    /* 0x4 */ u16 texId;
    /* 0x6 */ u8 framesLeft;
    /* 0x7 */ u8 pad7;
} TexCacheEntry;

#define TEX_CACHE_SIZE 32

extern TexCacheEntry gTexCache[TEX_CACHE_SIZE];

void texCacheReset(void) {
    s16 i;

    for (i = 0; i < TEX_CACHE_SIZE; i++) {
        gTexCache[i].framesLeft = 0;
    }
}

void texCacheUpdate(void) {
    s16 i;

    for (i = 0; i < TEX_CACHE_SIZE; i++) {
        TexCacheEntry *entry = &gTexCache[i];

        if (entry->framesLeft != 0) {
            entry->framesLeft--;
            if (entry->framesLeft == 0) {
                assetFreeBuffer(entry->tex, 0x6A, 0x46);
            }
        }
    }
}

void *texCacheFindOrLoad(u16 texId) {
    s16 i;
    TexCacheEntry *entry;

    for (i = 0; i < TEX_CACHE_SIZE; i++) {
        entry = &gTexCache[i];
        if (entry->texId == texId && entry->framesLeft != 0) {
            entry->framesLeft = 2;
            return entry->tex;
        }
    }

    for (i = 0; i < TEX_CACHE_SIZE; i++) {
        entry = &gTexCache[i];
        if (entry->framesLeft == 0) {
            entry->tex = assetLoad(0xE, texId, 0, 0);
            entry->framesLeft = 2;
            entry->texId = texId;
            return entry->tex;
        }
    }

    gTexCache[0].framesLeft = 2;
    return gTexCache[0].tex;
}

typedef struct RenderCallbackEntry {
    /* 0x0 */ Gfx *(*func)(Gfx *, void *);
    /* 0x4 */ void *actor;
    /* 0x8 */ u8 layer;
} RenderCallbackEntry;

extern RenderCallbackEntry gRenderCallbacks[];

Gfx *renderCallbacksExecute(Gfx *glist, u8 layer) {
    u8 count = gRenderCallbackCount;

    if (count != 0) {
        do {
            if (layer == gRenderCallbacks[--count].layer) {
                gDPPipeSync(glist++);
                glist = gRenderCallbacks[count].func(glist, gRenderCallbacks[count].actor);
            }
        } while (count != 0);
    }
    if (layer == 7) {
        gRenderCallbackCount = 0;
    }
    return glist;
}

void renderCallbacksReset(void) {
    gRenderCallbackCount = 0;
}

void renderCallbacksDisableForActor(Actor *actor) {
    u8 i;

    for (i = 0; i < gRenderCallbackCount; i++) {
        if (actor == gRenderCallbacks[i].actor) {
            gRenderCallbacks[i].layer = 8;
        }
    }
}

void renderCallbacksRegister(void *func, void *actor, u8 layer) {
    if (gRenderCallbackCount < 8) {
        gRenderCallbacks[gRenderCallbackCount].func = func;
        gRenderCallbacks[gRenderCallbackCount].actor = actor;
        gRenderCallbacks[gRenderCallbackCount].layer = layer;
        gRenderCallbackCount++;
    }
}

typedef f32 RenderMtxF[4][4];

Gfx *renderRotatedQuad(Gfx *glist, void *tex, s16 x, s16 y, s16 angle) {
    RenderMtxF rotMtx;
    RenderMtxF transMtx;
    Mtx *mtx;
    s32 pad;

    mtx = heapAlloc(sizeof(Mtx));
    heapFreeDeferred(mtx);

    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, (u8 *)tex + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    matrixMakeRotationZ(rotMtx, angle);
    guTranslateF(transMtx, x, y, 0.0f);
    guMtxCatF(rotMtx, transMtx, rotMtx);
    guMtxF2L(rotMtx, mtx);

    gSPMatrix(glist++, mtx, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPVertex(glist++, osVirtualToPhysical(D_807501E8), 4, 0);
    gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
    gSPPopMatrix(glist++, G_MTX_MODELVIEW);
    gDPPipeSync(glist++);

    return glist;
}

extern u16 D_807FC79E;
extern Mtx D_2000080;
extern Mtx D_2000180;

Gfx *renderRotatedSprite(Gfx *glist, u16 texId, s32 fmt, u32 siz, u8 width, u8 height, s16 x, s16 y, f32 scaleX, f32 scaleY, s32 angle, f32 texScale) {
    void *tex;
    s16 tileSize;
    u16 bpp;
    Vtx *vtx;
    s32 halfW;
    s32 halfH;
    f32 scaledW;
    f32 scaledH;
    RenderMtxF scaleMtx;
    RenderMtxF tempMtx;
    Mtx *mtx;

    siz &= ~0xC000;
    if (texId == 0) {
        texId = D_807FC79E;
    }

    switch (siz) {
    case G_IM_SIZ_4b:
        bpp = 4;
        break;
    case G_IM_SIZ_8b:
        bpp = 8;
        break;
    case G_IM_SIZ_32b:
        bpp = 32;
        break;
    default:
        bpp = 16;
        break;
    }

    tex = texCacheFindOrLoad(texId);

    if (((bpp * width * height) >> 3) > 0x1000) {
        gSPMatrix(glist++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(glist++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gDPPipeSync(glist++);
        tileSize = (bpp < 32) ? 32 : 30;
        gfxDrawTexturedTileGridSimple(&glist, tex, fmt, width, height, tileSize, tileSize, 0.0f, 0.0f, width, height,
                                      x - (width >> 1), y - (height >> 1), 1, bpp);
    } else {
        mtx = heapAlloc(sizeof(Mtx));
        heapFreeDeferred(mtx);
        vtx = heapAlloc(4 * sizeof(Vtx));
        heapFreeDeferred(vtx);

        switch (siz) {
        case G_IM_SIZ_4b:
            gDPLoadTextureBlock_4b(glist++, (u8 *)tex + 0x80000000, fmt, width, height, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case G_IM_SIZ_8b:
            gDPLoadTextureBlock(glist++, (u8 *)tex + 0x80000000, fmt, G_IM_SIZ_8b, width, height, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case G_IM_SIZ_16b:
            gDPLoadTextureBlock(glist++, (u8 *)tex + 0x80000000, fmt, G_IM_SIZ_16b, width, height, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        }

        guScaleF(scaleMtx, (scaleX > 0.0f) ? scaleX : -scaleX, (scaleY > 0.0f) ? scaleY : -scaleY, 0.0f);
        matrixMakeRotationZ(tempMtx, (s16)angle);
        guMtxCatF(scaleMtx, tempMtx, scaleMtx);
        guTranslateF(tempMtx, x, y, 0.0f);
        guMtxCatF(scaleMtx, tempMtx, scaleMtx);
        guMtxF2L(scaleMtx, mtx);

        gSPMatrix(glist++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

        scaledW = width * texScale;
        scaledH = height * texScale;

        if (scaleY > 0.0f) {
            halfW = width >> 1;
            halfH = height >> 1;

            vtxSetPosTex(vtx++, -halfW, halfH, 0.0f - scaledW, (height - 1) + scaledH, 6);
            vtxSetPosTex(vtx++, halfW, halfH, (width - 1) + scaledW, (height - 1) + scaledH, 6);
            vtxSetPosTex(vtx++, halfW, -halfH, (width - 1) + scaledW, 0.0f - scaledH, 6);
            vtxSetPosTex(vtx++, -halfW, -halfH, 0.0f - scaledW, 0.0f - scaledH, 6);
        } else {
            vtxSetPosTex(vtx++, -(width >> 1), 0, 0.0f - scaledW, (height - 1) + scaledH, 6);
            vtxSetPosTex(vtx++, width >> 1, 0, (width - 1) + scaledW, (height - 1) + scaledH, 6);
            vtxSetPosTex(vtx++, width >> 1, -height, (width - 1) + scaledW, 0.0f - scaledH, 6);
            vtxSetPosTex(vtx++, -(width >> 1), -height, 0.0f - scaledW, 0.0f - scaledH, 6);
        }

        gSPVertex(glist++, osVirtualToPhysical(vtx - 4), 4, 0);
        gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
        gDPPipeSync(glist++);
    }

    return glist;
}

extern PlayerStruct *gPlayerSlots;
extern u32 gFrameDelta;
extern s32 gCurrentMap;

Gfx *renderScrollingBackdropQuad(Gfx *glist, f32 *alpha) {
    void *texBuf;
    f32 alphaVal;
    f32 scrollStep;

    alphaVal = *alpha;
    scrollStep = gFrameDelta * 0.5;
    texBuf = assetLoad(0x19, 0x173C, 1, 0);
    assetFreeBuffer(texBuf, 0x1B2, 0x46);

    gDPPipeSync(glist++);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, gPlayerSlots->rect[0], gPlayerSlots->rect[1], gPlayerSlots->rect[2], gPlayerSlots->rect[3]);
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gDPSetTextureLOD(glist++, G_TL_LOD);
    gSPClearGeometryMode(glist++, 0xFFFFFFFF);
    gSPSetGeometryMode(glist++, G_SHADE | G_SHADING_SMOOTH);
    gSPTexture(glist++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetRenderMode(glist++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if (gCurrentMap == 0x26) {
        gDPSetPrimColor(glist++, 0, 0, 0x8A, 0x52, 0x16, 200.0f * alphaVal);
    } else {
        gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 35.0f * alphaVal);
    }

    gDPLoadTextureBlock(glist++, (u8 *)texBuf + 0x80000000, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);

    gDPSetTileSize(glist++, G_TX_RENDERTILE, (s32)D_8075022C, (s32)D_80750228, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPSetTile(glist++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 1, 0, G_TX_WRAP, 6, G_TX_NOLOD, G_TX_WRAP, 6, G_TX_NOLOD);

    gSPMatrix(glist++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glist++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPVertex(glist++, osVirtualToPhysical(D_80750230), 4, 0);
    gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
    gDPPipeSync(glist++);

    switch (gCurrentMap) {
    case 0x26: {
        f64 step = scrollStep;
        D_80750228 -= 2.0 * step;
        D_8075022C -= 14.0 * step;
        break;
    }
    default: {
        f64 step = scrollStep;
        D_80750228 -= step;
        D_8075022C -= 0.5 * step;
        break;
    }
    }

    if (D_80750228 < 0.0) {
        D_80750228 = 255.0f;
    }
    if (D_8075022C < 0.0) {
        D_8075022C = 255.0f;
    }

    return glist;
}

extern Gfx D_1000118;


Gfx *renderBonusTargetMarker(Gfx *glist, Actor *actor) {
    gSPDisplayList(glist++, &D_1000118);
    gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0xA0);
    gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetRenderMode(glist++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPMatrix(glist++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    return renderRotatedSprite(glist, ((gFrameCounter >> 1) & 0xF) + 0x8F, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 280, 210, 1.0f, 1.0f, 0, 0.0f);
}


Gfx *renderHitCounterHUD(Gfx *glist, CsCountdown *countdown) {
    u8 leftStr[12];
    u8 firedStr[4];

    gSPDisplayList(glist++, &D_1000118);
    gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0x96);
    _sprintf(leftStr, "%d", (s32)countdown->left);
    glist = textDrawStringVtx(glist, 3, 0x424, 0x50, leftStr, 1);
    glist = textDrawStringVtx(glist, 1, 0x50, 0x50, (const u8 *)"HIT", 1);
    _sprintf(firedStr, "%d", (s32)countdown->fired);
    return textDrawStringVtx(glist, 3, 0x50, 0xB0, firedStr, 1);
}

Gfx *renderRemainingShotsHUD(Gfx *glist, u8 *shots) {
    u8 shotsStr[8];

    gSPDisplayList(glist++, &D_1000118);
    gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0x96);
    _sprintf(shotsStr, "%d", *shots);
    return textDrawStringVtx(glist, 3, 0x104, 0x50, shotsStr, 1);
}

Gfx *renderCountdownTimerHUD(Gfx *glist, CsCountdown *countdown) {
    u8 timeStr[12];

    gSPDisplayList(glist++, &D_1000118);
    gDPSetCombineMode(glist++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 0x96);
    _sprintf(timeStr, "%d", (s32)countdown->left);
    return textDrawStringVtx(glist, 3, 0x370, 0x50, timeStr, 1);
}


Gfx *hudDrawRollingCounter(Gfx *glist, s16 x, s16 y, s16 *curVal, s16 targetVal, u8 *timer) {
    static const u8 sOneDigit[] = "1";
    f32 rollOffset;
    u8 currTensStr[2];
    u8 currOnesStr[2];
    u8 nextTensStr[2];
    u8 nextOnesStr[2];
    u8 hundredsStr[4];
    s16 step;
    s16 hundreds;
    s16 val;
    s32 scissorX;

    val = *curVal;
    if (targetVal < val) {
        step = -1;
    } else {
        step = 1;
    }

    if (targetVal != val) {
        if (*timer != 0) {
            *timer -= 1;
            if (*timer == 0) {
                *curVal += step;
                if (targetVal != *curVal) {
                    *timer = 12;
                }
            }
        } else {
            *timer = 12;
        }
    }
    glist = gfxInit2DDisplayList(glist);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, x, y, x + 0x34, y + 0x1B);

    val = *curVal;
    for (hundreds = 0; val >= 100; hundreds++) val -= 100; // LAYOUT: body on the for line: as1 schedules val's s16 truncation (sll t2,v1) before hundreds' addiu s0 (Q0396, Q0149)
    if (val == 99) {
        hundreds++;
    }

    currTensStr[0] = (val / 10) + '0';
    currTensStr[1] = 0;
    currOnesStr[0] = (val % 10) + '0';
    currOnesStr[1] = 0;
    nextTensStr[0] = ((val + step) / 10) + '0';
    nextTensStr[1] = 0;
    nextOnesStr[0] = ((val + step) % 10) + '0';
    nextOnesStr[1] = 0;

    rollOffset = sinApprox(((*timer / 12.0) * 1.57079637050628662) + 1.57079637050628662) * 96.0;

    if (targetVal == *curVal) {
        glist = textDrawStringVtx(glist, 3, x * 4, y * 4, currTensStr, 1);
        glist = textDrawStringVtx(glist, 3, (x * 4) + 0x50, y * 4, currOnesStr, 1);
    } else if (currTensStr[0] != nextTensStr[0]) {
        glist = textDrawStringVtx(glist, 3, x * 4, y * 4 - 96 + rollOffset, nextTensStr, 1);
        glist = textDrawStringVtx(glist, 3, x * 4, y * 4 + 4 + rollOffset, currTensStr, 1);
        glist = textDrawStringVtx(glist, 3, (x * 4) + 0x50, y * 4 - 96 + rollOffset, nextOnesStr, 1);
        glist = textDrawStringVtx(glist, 3, (x * 4) + 0x50, y * 4 + 4 + rollOffset, currOnesStr, 1);
    } else {
        glist = textDrawStringVtx(glist, 3, x * 4, y * 4, currTensStr, 1);
        glist = textDrawStringVtx(glist, 3, (x * 4) + 0x50, y * 4 - 96 + rollOffset, nextOnesStr, 1);
        glist = textDrawStringVtx(glist, 3, (x * 4) + 0x50, y * 4 + 4 + rollOffset, currOnesStr, 1);
    }

    if ((*curVal + step) >= 100) {
        scissorX = x - 0x14;
        if (scissorX < 0) {
            scissorX = 0;
        }
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, scissorX, y, x + 0x34, y + 0x1B);
        _sprintf(hundredsStr, "%d", hundreds);
        if (*curVal >= 100 && *curVal != 199) {
            glist = textDrawStringVtx(glist, 3, (x * 4) - 0x50, y * 4, hundredsStr, 1);
        } else if (*curVal == 99 || *curVal == 199) {
            glist = textDrawStringVtx(glist, 3, (x * 4) - 0x50, y * 4 - 96 + rollOffset, hundredsStr, 1);
            if (*curVal == 199) {
                glist = textDrawStringVtx(glist, 3, (x * 4) - 0x50, y * 4 + 4 + rollOffset, sOneDigit, 1);
            }
        }
    }

    gDPPipeSync(glist++);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, gPlayerSlots->rect[0], gPlayerSlots->rect[1], gPlayerSlots->rect[2], gPlayerSlots->rect[3]);
    return glist;
}


extern Mtx D_20000C0;


// The owner's component (Actor.customState) as actorDrawAnimatedEffect reads it: a byte pointer at 0x34.
typedef struct AnimatedEffectOwnerState {
    u8 pad[0x34];
    u8 *routeCursor;
} AnimatedEffectOwnerState;

#define ANIM_TEX (((gFrameCounter >> 1) % 12) + 0x83)

Gfx *actorDrawAnimatedEffect(Gfx *glist, Actor *actor) {
    s16 spriteAngle = actor->arrowAngle + 90;

    gSPDisplayList(glist++, &D_1000118);
    gDPSetCombineMode(glist++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(glist++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPMatrix(glist++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

    if (gGlobalOverlayFlags & 0x80000) {
        s16 yaw = actor->yaw;
        AnimatedEffectOwnerState *state = actor->customState;
        if (yaw < 0x200 || yaw >= 0xE01 || (yaw >= 0x601 && yaw < 0xA00)) {
            if (*state->routeCursor != 0x10 && *state->routeCursor != 0x13) {
                glist = renderRotatedSprite(glist, ANIM_TEX, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 120, 480, 4.0f, 4.0f, 0, 0.0f);
                glist = renderRotatedSprite(glist, ANIM_TEX, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 1160, 480, 4.0f, 4.0f, 180, 0.0f);
            }
        } else {
            glist = renderRotatedSprite(glist, ANIM_TEX, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 640, 120, 4.0f, 4.0f, 90, 0.0f);
            glist = renderRotatedSprite(glist, ANIM_TEX, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 640, 840, 4.0f, 4.0f, 270, 0.0f);
        }
    } else {
        glist = renderRotatedSprite(glist, ANIM_TEX, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 180, 200, 8.0f, 8.0f, spriteAngle, 0.0f);
    }

    return glist;
}


Gfx *renderTimerMinutesSecondsHUD(Gfx *glist, f32 x, f32 y, s32 totalSeconds) {
    f32 curX;
    f32 baseY;
    f32 colonHalfWidth;
    u8 timeStr[16];
    s16 vtxY;
    s32 minutes;

    baseY = y - textGetFontHeight(0x86) * 0.5f;
    _sprintf(timeStr, ":");
    colonHalfWidth = textGetStringWidth(6, timeStr) * 0.5f;
    minutes = totalSeconds / 60;
    curX = x - colonHalfWidth;
    vtxY = baseY * 4.0f;
    glist = textDrawStringVtx(glist, 6, curX * 4.0f, vtxY, timeStr, 1);
    _sprintf(timeStr, "%2d", minutes);
    curX = curX - textGetStringWidth(0x86, timeStr);
    glist = textDrawStringVtx(glist, 0x86, curX * 4.0f, vtxY, timeStr, 1);
    _sprintf(timeStr, "%02d", totalSeconds - minutes * 60);
    return textDrawStringVtx(glist, 0x86, (x + colonHalfWidth) * 4.0f, vtxY, timeStr, 1);
}
