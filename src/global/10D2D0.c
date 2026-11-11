#include "common.h"
#include "actor.h"
#define PROTO_SKIP_renderRotatedSprite // FAKE: callee prototype steer
#include "proto/global/10D2D0.h"
#include "proto/global/117190.h"
#include "proto/global/450.h"
#include "proto/global/7130.h"
#include "proto/global/90D80.h"
#include "proto/global/CC800.h"

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

typedef struct HealthHudState {
    u8 unk0;
    u8 pad1[0x2DF];
    u16 unk2E0;
    union {
        u16 flags;
        struct {
            u8 unk2E2;
            u8 unk2E3;
        };
    };
    u8 unk2E4;
    u8 unk2E5;
    u8 unk2E6;
} HealthHudState;

typedef struct HealthStats {
    u8 pad0[0x2FB];
    s8 health;
    u8 melons;
    s8 healthDelta;
} HealthStats;


struct HealthHudState; struct HealthStats;
extern Gfx D_1000118;
extern Mtx D_20000C0;
extern s32 gFrameCounter;
extern s32 gGlobalPauseFlags;
f32 mathSinF(s16);
Gfx *renderRotatedSprite(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32); // FAKE: callee prototype steer

Gfx *healthHudDraw(Gfx *glist, HealthStats *stats, void *elem, HealthHudState *hudState) {
    s16 i;
    s8 pips;
    u32 amp;
    s16 phase;
    s32 raw;
    f32 fs0;
    f32 animParams[22]; /* only [0] [3] [4] [21] are used: a non-volatile array keeps them memory-resident with IDO's reload pattern */
    f32 fs1;
    f32 fs2;
    f32 fs0b;
    f32 wv;
    s16 y;
    s16 x;

    pips = stats->health;
    if (pips - 1 > 3) {} /* dead: stops IDO hoisting pips - 1 above the PrimColor select */
    fs0 = (f32)((f64)(u32)hudState->unk2E0 / 65535.0);
    amp = ((stats->melons * 0x46) - 0x46) & 0xFF;
    if ((gGlobalPauseFlags & 3) || (menuIsTransitionTypeAOrE() != 0)) {
        return glist;
    }
    gSPDisplayList(glist++, &D_1000118);
    gDPSetCombineMode(glist++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    gSPMatrix(glist++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    i = 0;
    if (stats->melons > 0) {
        animParams[4] = fs0 * 511.0f;
        animParams[3] = (f32)amp;
        animParams[0] = (f32)(s16)(s32)((f64)fs0 * 200.0);
        do {
            raw = (i << 10) + (gFrameCounter * 0xC8);
            phase = raw;
            animParams[21] = (f32)(((f64)mathSinF(phase) * 0.3) + 3.0);
            fs2 = (f32)(((f64)mathSinF((s16)(raw + 0x800)) * 0.3) + 3.0);
            fs0b = (f32)((f64)mathSinF((s16)((raw >> 1) + 0x200)) * 10.0);
            wv = (f32)(((f64)mathSinF(phase) * 0.5 + 0.5) * 30.0);
            gDPPipeSync(glist++);
            gDPSetPrimColor(glist++, 0, 0, 255, 255, 255, (u32)((animParams[4] > 80.0f) ? (f32)80 : animParams[4]));
            glist = renderRotatedSprite(glist, 0x5D, 0, 2, 0x30, 0x2A, y = (s32)(((f32)((i * 0x8C) + 0x280) + fs0b) - animParams[3]), x = (s32)(animParams[0] + wv), animParams[21], -fs2, 0, 0.0f); // FAKE: y/x assigned inside the argument list (separate statements break the match)
            fs1 = -fs2;
            gDPPipeSync(glist++);
            gDPSetPrimColor(glist++, 0, 0, 255, 255, 255, (u32)((animParams[4] > 255.0f) ? 255.0f : animParams[4]));
            if (pips > 0) {
                glist = renderRotatedSprite(glist, ((pips - 1 < 3 ? pips - 1 : 3) + 0x5A) & 0xFFFF, 0, 2, 0x30, 0x2A, y, x, animParams[21], fs1, 0, 0.0f);
            }
            if (pips - 4 < 0) {
                pips = 0;
            } else {
                pips = pips - 4;
            }
            i += 1;
        } while (i < stats->melons);
    }
    gDPPipeSync(glist++);
    return glist;
}


typedef struct HealthHudInit {
    f32 unk0;
    s16 unk4;
    s16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
} HealthHudInit;

extern s32 gGlobalOverlayFlags;

void hudDrawItemWithAlpha(HealthHudInit *hudInit) {
    if (gGlobalOverlayFlags & 0x800) {
        hudInit->unk6 = 0x20;
    } else {
        hudInit->unk6 = 1;
    }
    if (func_807142D8() != 0) {
        hudInit->unk6 = 0x20;
    }
    hudInit->unkA = 0;
    hudInit->unk8 = 0;
    hudInit->unk4 = 0;
    hudInit->unk0 = 4.0f;
}



void func_80026B0C(s32);

void healthApplyPendingDelta(s32 playerIndex, HealthHudState *hudState, HealthStats *playerState, s32 newHealth) {
    u8 state;
    s32 limit;

    state = hudState->flags;
    if (state & 0x10) {
        hudState->flags ^= 0x10;
        if (playerState->healthDelta > 0) {
            limit = healthGetPerMelon();
            newHealth = playerState->health + playerState->healthDelta;
            limit = playerState->melons * limit;
            if (newHealth < limit) {
                playerState->health = newHealth;
            } else {
                playerState->health = limit;
            }
        } else if (playerState->healthDelta < 0) {
            if ((menuIsTransitionType6() != 0) || (menuIsTransitionTypeC() != 0)) {
                playerState->health += playerState->healthDelta;
            }
            if (playerState->health <= 0) {
                playerState->health = 0;
                hudState->unk2E6 = 0xC;
                if ((s32)gPlayerCount >= 2) {
                    func_80026B0C(playerIndex);
                }
            } else {
                sfxPlayOnFreeSlot(0x24B, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
        playerState->healthDelta = 0;
    }
    if ((!(gGlobalPauseFlags & 2) && (hudCanRender() != 0)) || (state & 0x80)) {
        hudState->unk2E5--;
        if (!hudState->unk2E5) {
            hudState->unk2E5 = 0x11;
            hudState->unk2E4 = 3;
        }
    }
}

f32 sinApprox(f32);

Gfx *healthHudUpdateDraw(glist, playerIndex, hudState)
Gfx *glist;
s16 playerIndex;
HealthHudState *hudState;
{
    s32 idx;
    f32 angle;
    u8 *hud;
    u8 *elem;
    u8 mode;
    u8 bits;
    s32 single;

    hud = (u8 *)(playerIndex * 0x306 + (s32)gPlayerInventoryTable);
    idx = playerGetResolvedKongId(playerIndex);
    elem = (u8 *)((s32)hud + idx * 0x5E);
    mode = hudState->unk2E4;
    bits = hudState->unk2E3;
    single = gPlayerCount == 1;
    if (single == 0) {
        mode = 0;
    }
    if (single == 0) {
        healthApplyPendingDelta(playerIndex, hudState, (HealthStats *)hud, (s32)elem);
        hudState->flags &= 0xFFEA;
        bits = hudState->unk2E3;
    }
    if (bits & 0x10) {
        switch (mode) {
        case 2:
            hudState->unk2E5 = 50;
            break;
        case 3:
            hudState->unk2E5 = 18.0 - hudState->unk2E5;
            hudState->unk2E4 = 1;
            break;
        }
    }
    if (bits & 1) {
        hudState->flags ^= 1;
        switch (mode) {
        case 0:
            hudState->unk2E5 = 18;
            hudState->unk2E4 = 1;
            break;
        case 1:
            break;
        case 3:
            hudState->unk2E5 = 18.0 - hudState->unk2E5;
            hudState->unk2E4 = 1;
            break;
        }
    } else if (bits & 4) {
        hudState->unk2E5 = 1;
        hudState->flags ^= 4;
        hudState->unk2E4 = 2;
        hudState->flags &= 8;
    } else {
        switch (mode) {
        case 1:
            angle = hudState->unk2E5 / 18.0 * 1.5707963705062866 + 1.5707963705062866;
            hudState->unk2E0 = sinApprox(angle) * 65535.0;
            if (hudState->unk2E5-- == 0) {
                hudState->unk2E4 = 2;
                hudState->unk2E5 = 50;
            }
            break;
        case 2:
            healthApplyPendingDelta(playerIndex, hudState, (HealthStats *)hud, (s32)elem);
            break;
        case 3:
            angle = 1.5707963705062866 - hudState->unk2E5 / 18.0 * 1.5707963705062866 + 1.5707963705062866;
            hudState->unk2E0 = sinApprox(angle) * 65535.0;
            if (hudState->unk2E5-- == 0) {
                hudState->unk2E4 = 0;
            }
            break;
        }
    }
    if (hudCanRender() != 0 || (bits & 0x80)) {
        if (hudState->unk2E4 != 0 || hudState->flags != 0) {
            glist = healthHudDraw(glist, (HealthStats *)hud, elem, hudState);
        }
    }
    return glist;
}


extern s8 D_80744504;

Gfx *healthHudDrawAll(Gfx *glist) {
    s16 playerIndex;
    s32 slotOffset;
    u16 flags;
    s32 playerSlot;

    playerIndex = 0;
    if ((s32)gPlayerCount > 0) {
        do {
            slotOffset = playerIndex * 0x2F0;
            playerSlot = (s32)gPlayerSlots + slotOffset;
            if (((HealthHudState *)playerSlot)->unk0 != 0) {
                flags = ((HealthHudState *)playerSlot)->flags;
                if (!(flags & 0x20) && (((((HealthHudState *)playerSlot)->unk2E4 != 0 || flags != 0) &&
                                           D_80744504 == 0) ||
                                          flags & 0x10)) {
                    glist = healthHudUpdateDraw(glist, (s16)(playerIndex + 0), (slotOffset ^ 0) + (s32)gPlayerSlots, (s32)gPlayerSlots); // FAKE: extra argument to the K&R callee (removing it breaks the match)
                }
            }
            playerIndex += 1;
        } while (playerIndex < (s32)gPlayerCount);
    }
    return glist;
}


s32 healthGetPerMelon(void) {
    return ((s32)gPlayerCount >= 2) ? 0xA : 4;
}



void healthRefill(u8 playerIndex) {
    s32 perMelon;
    s32 product_factor;
    HealthStats *stats;

    perMelon = healthGetPerMelon();
    stats = (HealthStats *)((playerIndex * 0x306) + (s32)gPlayerInventoryTable);
    stats->healthDelta = 0;
    stats->health = stats->melons * (product_factor = perMelon); // FAKE: assignment-in-expression (plain multiply breaks the match)
}


