#include "common.h"
#include "actor.h"
#define PROTO_SKIP_gfxDrawTexturedTileGridSimple // FAKE: callee prototype steer (width/height u8: 103AB0.c declares s32)
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/15050.h"
#include "proto/global/17800.h"
#include "proto/global/450.h"
#include "proto/global/6AD90.h"
#include "proto/global/90D80.h"


typedef struct TexCacheEntry {
    /* 0x0 */ void *unk0;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} TexCacheEntry;

extern TexCacheEntry D_807FC690[];

void texCacheReset(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        D_807FC690[i].unk6 = 0;
    }
}


void texCacheUpdate(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        TexCacheEntry *entry = &D_807FC690[i];

        if (entry->unk6 != 0) {
            entry->unk6--;
            if (entry->unk6 == 0) {
                assetFreeBuffer(entry->unk0, 0x6A, 0x46);
            }
        }
    }
}

void *texCacheFindOrLoad(u16 texId) {
    s16 i;
    TexCacheEntry *entry;

    for (i = 0; i < 0x20; i++) {
        entry = &D_807FC690[i];
        if (entry->unk4 == texId && entry->unk6 != 0) {
            entry->unk6 = 2;
            return entry->unk0;
        }
    }

    for (i = 0; i < 0x20; i++) {
        entry = &D_807FC690[i];
        if (entry->unk6 == 0) {
            entry->unk0 = assetLoad(0xE, texId, 0, 0);
            entry->unk6 = 2;
            entry->unk4 = texId;
            return entry->unk0;
        }
    }

    D_807FC690[0].unk6 = 2;
    return D_807FC690[0].unk0;
}

typedef struct RenderCallbackEntry {
    /* 0x0 */ Gfx *(*func)(Gfx *, void *);
    /* 0x4 */ void *actor;
    /* 0x8 */ u8 layer;
} RenderCallbackEntry;

extern u8 D_807501E0;
extern RenderCallbackEntry D_807FC630[];

Gfx *renderCallbacksExecute(Gfx *glist, u8 layer) {
    u8 count = D_807501E0;

    if (count != 0) {
        do {
            if (layer == D_807FC630[--count].layer) {
                gDPPipeSync(glist++);
                glist = D_807FC630[count].func(glist, D_807FC630[count].actor);
            }
        } while (count != 0);
    }
    if (layer == 7) {
        D_807501E0 = 0;
    }
    return glist;
}

void renderCallbacksReset(void) {
    D_807501E0 = 0;
}

void renderCallbacksDisableForActor(Actor *actor) {
    u8 i;

    for (i = 0; i < D_807501E0; i++) {
        if (actor == D_807FC630[i].actor) {
            D_807FC630[i].layer = 8;
        }
    }
}

void renderCallbacksRegister(void *func, void *actor, u8 layer) {
    if (D_807501E0 < 8) {
        D_807FC630[D_807501E0].func = func;
        D_807FC630[D_807501E0].actor = actor;
        D_807FC630[D_807501E0].layer = layer;
        D_807501E0++;
    }
}

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

typedef f32 RenderMtxF[4][4];
extern u32 D_807501E8;

Gfx *renderRotatedQuad(Gfx *glist, s32 tex, s16 x, s16 y, s16 angle) {
    RenderMtxF rotMtx;
    RenderMtxF transMtx;
    Mtx *mtx;
    s32 pad;
    mtx = heapAlloc(sizeof(Mtx));
    heapFreeDeferred(mtx);

    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, (u8 *)tex + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);

    matrixMakeRotationZ(rotMtx, (f32)angle);
    guTranslateF(transMtx, (f32)x, (f32)y, 0.0f);
    guMtxCatF(rotMtx, transMtx, rotMtx);
    guMtxF2L(rotMtx, mtx);

    WRITE_GFX(glist++, 0xDA380000, (u32)mtx);
    WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(&D_807501E8));
    WRITE_GFX(glist++, 0x06000204, 0x00000406);
    WRITE_GFX(glist++, 0xD8380002, 0x00000040);
    gDPPipeSync(glist++);

    return glist;
}

extern u16 D_807FC79E;
extern Mtx D_2000080;
extern Mtx D_2000180;
void gfxDrawTexturedTileGridSimple(Gfx **, void *, s32, u8, u8, s32, s32, f32, f32, f32, f32, f32, f32, u8, u8);  // FAKE: callee prototype steer (width/height u8: 103AB0.c declares s32)

Gfx *renderRotatedSprite(Gfx *glist, u16 texId, s32 fmt, s32 siz, u8 width, u8 height, s16 x, s16 y, f32 scaleX, f32 scaleY, s32 angle, f32 texScale) {
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
    Mtx *mtx1;

    siz &= ~0xC000;
    if (texId == 0) {
        texId = D_807FC79E;
    }

    switch (siz) {
    case 0:
        bpp = 4;
        break;
    case 1:
        bpp = 8;
        break;
    case 3:
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
        tileSize = (bpp < 0x20) ? 0x20 : 0x1E;
        gfxDrawTexturedTileGridSimple(&glist, tex, fmt, width, height, tileSize, tileSize, 0.0f, 0.0f,
                      (f32)(u32)width, (f32)(u32)height,
                      (f32)(x - (width >> 1)), (f32)(y - (height >> 1)),
                      1, bpp);
    } else {
        mtx1 = heapAlloc(sizeof(Mtx));
        heapFreeDeferred(mtx1);
        vtx = heapAlloc(sizeof(Mtx));
        heapFreeDeferred(vtx);

        switch (siz) {
        case 0:
            gDPLoadTextureBlock_4b(glist++, (u8 *)tex + 0x80000000, fmt, width, height, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            break;
        case 1:
            gDPLoadTextureBlock(glist++, (u8 *)tex + 0x80000000, fmt, G_IM_SIZ_8b, width, height, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            break;
        case 2:
            gDPLoadTextureBlock(glist++, (u8 *)tex + 0x80000000, fmt, G_IM_SIZ_16b, width, height, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            break;
        }

        guScaleF(scaleMtx, (scaleX > 0.0f) ? scaleX : -scaleX, (scaleY > 0.0f) ? scaleY : -scaleY, 0.0f);
        matrixMakeRotationZ(tempMtx, (f32)(s16)angle);
        guMtxCatF(scaleMtx, tempMtx, scaleMtx);
        guTranslateF(tempMtx, (f32)x, (f32)y, 0.0f);
        guMtxCatF(scaleMtx, tempMtx, scaleMtx);
        guMtxF2L(scaleMtx, mtx1);

        gSPMatrix(glist++, mtx1, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

        scaledW = (f32)(u32)width * texScale;
        scaledH = (f32)(u32)height * texScale;

        if (scaleY > 0.0f) {
            halfW = width >> 1;
            halfH = height >> 1;

            vtxSetPosTex(vtx++, -halfW, halfH, 0.0f - scaledW, (f32)(height - 1) + scaledH, 6);
            vtxSetPosTex(vtx++, halfW, halfH, (f32)(width - 1) + scaledW, (f32)(height - 1) + scaledH, 6);
            vtxSetPosTex(vtx++, halfW, -halfH, (f32)(width - 1) + scaledW, 0.0f - scaledH, 6);
            vtxSetPosTex(vtx++, -halfW, -halfH, 0.0f - scaledW, 0.0f - scaledH, 6);
        } else {
            vtxSetPosTex(vtx++, -(width >> 1), 0, 0.0f - scaledW, (f32)(height - 1) + scaledH, 6);
            vtxSetPosTex(vtx++, width >> 1, 0, (f32)(width - 1) + scaledW, (f32)(height - 1) + scaledH, 6);
            vtxSetPosTex(vtx++, width >> 1, -height, (f32)(width - 1) + scaledW, 0.0f - scaledH, 6);
            vtxSetPosTex(vtx++, -(width >> 1), -height, 0.0f - scaledW, 0.0f - scaledH, 6);
        }

        gSPVertex(glist++, osVirtualToPhysical(vtx - 4), 4, 0);
        gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
        gDPPipeSync(glist++);
    }

    return glist;
}

typedef struct PlayerRect {
    u8 pad[0x270];
    s16 rect[4];
} PlayerRect;
extern PlayerRect *gPlayerSlots;
extern u32 gFrameDelta;
extern f32 D_8075022C, D_80750228;
extern u32 D_80750230;
extern s32 gCurrentMap;
extern Mtx D_2000080;
extern Mtx D_2000180;

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
    WRITE_GFX(glist++, 0xE3000A01, 0);
    WRITE_GFX(glist++, 0xE3000F00, 0x10000);
    WRITE_GFX(glist++, 0xD9000000, 0);
    WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200004);
    WRITE_GFX(glist++, 0xD7000002, -1);
    WRITE_GFX(glist++, 0xE200001C, 0x00504340);
    WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);

    if (gCurrentMap == 0x26) {
        gDPSetPrimColor(glist++, 0, 0, 0x8A, 0x52, 0x16, 200.0f * alphaVal);
    } else {
        gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 35.0f * alphaVal);
    }

    gDPLoadTextureBlock(glist++, (u8 *)texBuf + 0x80000000, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, 0, 0);

    gDPSetTileSize(glist++, 0, (s32)D_8075022C, (s32)D_80750228, 63 << 2, 63 << 2);
    gDPSetTile(glist++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 1, 0, G_TX_WRAP, 6, 0, G_TX_WRAP, 6, 0);

    WRITE_GFX(glist++, 0xDA380007, (u32)&D_2000080);
    if (gFrameDelta == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    WRITE_GFX(glist++, 0xDA380003, (u32)&D_2000180);
    WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(&D_80750230));
    WRITE_GFX(glist++, 0x06000204, 0x00000406);
    gDPPipeSync(glist++);

    if (gCurrentMap == 0x26) {
        f64 temp = scrollStep;
        D_80750228 -= 2.0 * temp;
        D_8075022C -= 14.0 * temp;
    } else {
        f64 temp = scrollStep;
        D_80750228 -= temp;
        D_8075022C -= 0.5 * temp;
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
extern u32 gFrameCounter;


Gfx *renderBonusTargetMarker(Gfx *glist, s32 pad) {
    WRITE_GFX(glist++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(glist++, 0xFA000000, 0xFFFFFFA0);
    WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(glist++, 0xE200001C, 0x00504240);
    WRITE_GFX(glist++, 0xDA380007, (u32)&D_2000080);
    return renderRotatedSprite(glist, (u16)((((gFrameCounter >> 1) & 0xF) + 0x8F)), 0, 2, 0x20, 0x20, 0x118, 0xD2, 1.0f, 1.0f, 0, 0.0f);
}


typedef struct CsCountdown {
    u64 last;
    s64 duration;
    s64 left;
    s64 fired;
} CsCountdown;

Gfx *renderHitCounterHUD(Gfx *glist, CsCountdown *countdown) {
    u8 leftStr[12];
    u8 firedStr[4];

    WRITE_GFX(glist++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(glist++, 0xFA000000, 0xFFFFFF96);
    _sprintf(leftStr, "%d", (s32)countdown->left);
    glist = textDrawStringVtx(textDrawStringVtx(glist, 3, 0x424, 0x50, leftStr, 1), 1, 0x50, 0x50, "HIT", 1);
    _sprintf(firedStr, "%d", (s32)countdown->fired);
    return textDrawStringVtx(glist, 3, 0x50, 0xB0, firedStr, 1);
}

Gfx *renderRemainingShotsHUD(Gfx *glist, u8 *shots) {
    u8 shotsStr[8];

    WRITE_GFX(glist++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(glist++, 0xFA000000, 0xFFFFFF96);
    _sprintf(shotsStr, "%d", *shots);
    return textDrawStringVtx(glist, 3, 0x104, 0x50, shotsStr, 1);
}

Gfx *renderCountdownTimerHUD(Gfx *glist, CsCountdown *countdown) {
    u8 timeStr[12];

    WRITE_GFX(glist++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);
    WRITE_GFX(glist++, 0xFA000000, 0xFFFFFF96);
    _sprintf(timeStr, "%d", (s32)countdown->left);
    return textDrawStringVtx(glist, 3, 0x370, 0x50, timeStr, 1);
}

f32 sinApprox(f32);

Gfx *hudDrawRollingCounter(Gfx *glist, s16 x, s16 y, s16 *curVal, s16 targetVal, u8 *timer) {
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
                    *timer = 0xC;
                }
            }
        } else {
            *timer = 0xC;
        }
    }
    glist = gfxInit2DDisplayList(glist);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, x, y, x + 0x34, y + 0x1B);

    hundreds = 0;
    val = *curVal;
    while (val >= 100) {
        (val -= 100), hundreds++;
    }
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

    rollOffset = sinApprox((((f64)*timer / 12.0) * 1.57079637050628662) + 1.57079637050628662) * 96.0;

    if (targetVal == *curVal) {
        glist = textDrawStringVtx(glist, 3, x * 4, y * 4, currTensStr, 1);
        glist = textDrawStringVtx(glist, 3, (x * 4) + 0x50, y * 4, currOnesStr, 1);
    } else if (currTensStr[0] != nextTensStr[0]) {
        glist = textDrawStringVtx(glist, 3, x * 4, (s16)((f32)(y * 4 - 0x60) + rollOffset), nextTensStr, 1);
        glist = textDrawStringVtx(glist, 3, x * 4, (s16)((f32)(y * 4 + 4) + rollOffset), currTensStr, 1);
        glist = textDrawStringVtx(glist, 3, (x * 4) + 0x50, (s16)((f32)(y * 4 - 0x60) + rollOffset), nextOnesStr, 1);
        glist = textDrawStringVtx(glist, 3, (x * 4) + 0x50, (s16)((f32)(y * 4 + 4) + rollOffset), currOnesStr, 1);
    } else {
        glist = textDrawStringVtx(glist, 3, x * 4, y * 4, currTensStr, 1);
        glist = textDrawStringVtx(glist, 3, (x * 4) + 0x50, (s16)((f32)(y * 4 - 0x60) + rollOffset), nextOnesStr, 1);
        glist = textDrawStringVtx(glist, 3, (x * 4) + 0x50, (s16)((f32)(y * 4 + 4) + rollOffset), currOnesStr, 1);
    }

    if ((*curVal + step) >= 100) {
        scissorX = x - 0x14;
        if (scissorX < 0) {
            scissorX = 0;
        }
        gDPSetScissor(glist++, G_SC_NON_INTERLACE, scissorX, y, x + 0x34, y + 0x1B);
        _sprintf(hundredsStr, "%d", hundreds);
        if (*curVal >= 100 && *curVal != 0xC7) {
            glist = textDrawStringVtx(glist, 3, (x * 4) - 0x50, y * 4, hundredsStr, 1);
        } else if (*curVal == 0x63 || *curVal == 0xC7) {
            glist = textDrawStringVtx(glist, 3, (x * 4) - 0x50, (s16)((f32)(y * 4 - 0x60) + rollOffset), hundredsStr, 1);
            if (*curVal == 0xC7) {
                glist = textDrawStringVtx(glist, 3, (x * 4) - 0x50, (s16)((f32)(y * 4 + 4) + rollOffset), "1", 1);
            }
        }
    }

    gDPPipeSync(glist++);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, gPlayerSlots->rect[0], gPlayerSlots->rect[1], gPlayerSlots->rect[2], gPlayerSlots->rect[3]);
    return glist;
}


extern Mtx D_20000C0;
extern s32 gGlobalOverlayFlags;


// The owner's component (Actor.customState) as actorDrawAnimatedEffect reads it: a byte pointer at 0x34.
typedef struct ActorEffect174 {
    u8 pad[0x34];
    u8 *unk34;
} ActorEffect174;
#define ANIM_TEX ((u16)(((gFrameCounter >> 1) % 12) + 0x83))

Gfx *actorDrawAnimatedEffect(Gfx *glist, Actor *actor) {
    s16 spriteAngle = actor->unkEC + 0x5A;

    WRITE_GFX(glist++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(glist++, 0xFCFFFFFF, 0xFFFCF279);
    WRITE_GFX(glist++, 0xE200001C, 0x00504240);
    WRITE_GFX(glist++, 0xDA380007, (u32)&D_20000C0);

    if (gGlobalOverlayFlags & 0x80000) {
        s16 yaw = actor->yaw;
        ActorEffect174 *state = actor->customState;
        if (yaw < 0x200 || yaw >= 0xE01 || (yaw >= 0x601 && yaw < 0xA00)) {
            if (*state->unk34 != 0x10 && *state->unk34 != 0x13) {
                glist = renderRotatedSprite(glist, ANIM_TEX, 0, 2, 0x20, 0x10, 0x78, 0x1E0, 4.0f, 4.0f, 0, 0.0f);
                glist = renderRotatedSprite(glist, ANIM_TEX, 0, 2, 0x20, 0x10, 0x488, 0x1E0, 4.0f, 4.0f, 0xB4, 0.0f);
            }
        } else {
            glist = renderRotatedSprite(glist, ANIM_TEX, 0, 2, 0x20, 0x10, 0x280, 0x78, 4.0f, 4.0f, 0x5A, 0.0f);
            glist = renderRotatedSprite(glist, ANIM_TEX, 0, 2, 0x20, 0x10, 0x280, 0x348, 4.0f, 4.0f, 0x10E, 0.0f);
        }
    } else {
        glist = renderRotatedSprite(glist, ANIM_TEX, 0, 2, 0x20, 0x10, 0xB4, 0xC8, 8.0f, 8.0f, spriteAngle, 0.0f);
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

    baseY = y - ((f32)(u32)textGetFontHeight(0x86) * 0.5f);
    _sprintf(timeStr, ":");
    colonHalfWidth = (f32)textGetStringWidth(6, timeStr) * 0.5f;
    minutes = totalSeconds / 60;
    curX = x - colonHalfWidth;
    vtxY = (s16)(s32)(baseY * 4.0f);
    glist = textDrawStringVtx(glist, 6, (s16)(s32)(curX * 4.0f), vtxY, timeStr, 1);
    minutes = totalSeconds / 60;
    _sprintf(timeStr, "%2d", minutes);
    curX = curX - (f32)textGetStringWidth(0x86, timeStr);
    glist = textDrawStringVtx(glist, 0x86, (s16)(s32)(curX * 4.0f), vtxY, timeStr, 1);
    _sprintf(timeStr, "%02d", totalSeconds - minutes * 60);
    return textDrawStringVtx(glist, 0x86, (s16)(s32)((x + colonHalfWidth) * 4.0f), vtxY, timeStr, 1);
}
