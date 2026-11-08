#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern u8 D_807FC950[][0x5E];
extern s32 gCurrentMap;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 D_807444F8;
extern u8 gGfxBufferIndex;

typedef struct HealthHudState {
    u8 pad0[0x2E0];
    u16 unk2E0;
    u8 unk2E2;
    u8 unk2E3;
    u8 unk2E4;
    u8 unk2E5;
} HealthHudState;

#define HEALTH_HUD_FLAGS(p) (*(u16 *)&(p)->unk2E2)

typedef struct HealthStats {
    u8 pad0[0x2FB];
    s8 unk2FB;
    u8 unk2FC;
} HealthStats;

Gfx *healthHudDraw();

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern s32 gFrameCounter;
extern s32 gGlobalPauseFlags;
f32 mathSinF(s16);
s32 menuIsTransitionTypeAOrE();
Gfx *renderRotatedSprite(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

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

    pips = stats->unk2FB;
    if (pips - 1 > 3) {} /* dead: stops IDO hoisting pips - 1 above the PrimColor select */
    fs0 = (f32)((f64)(u32)hudState->unk2E0 / 65535.0);
    amp = ((stats->unk2FC * 0x46) - 0x46) & 0xFF;
    if ((gGlobalPauseFlags & 3) || (menuIsTransitionTypeAOrE() != 0)) {
        return glist;
    }
    gSPDisplayList(glist++, &D_1000118);
    gDPSetCombineMode(glist++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    gSPMatrix(glist++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    i = 0;
    if (stats->unk2FC > 0) {
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
            glist = renderRotatedSprite(glist, 0x5D, 0, (0, 2), 0x30, 0x2A, y = (s32)(((f32)((i * 0x8C) + 0x280) + fs0b) - animParams[3]), x = (s32)(animParams[0] + wv), animParams[21], fs1 = -fs2, 0, 0.0f);
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
        } while (i < stats->unk2FC);
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
extern s32 func_807142D8();

void func_80708BB8(HealthHudInit *hudInit) {
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



typedef struct HealthPlayerState {
    u8 unk0;
    u8 pad1[0x2E1];
    u16 unk2E2;
    u8 unk2E4;
    u8 unk2E5;
    u8 unk2E6;
    u8 pad2E7[9];
    s8 unk2F0[0xB];
    s8 unk2FB;
    u8 unk2FC;
    s8 unk2FD;
} HealthPlayerState;

void func_80026B0C(s32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
s32 func_805FCA64(void);
s32 menuIsTransitionType6(void);
s32 menuIsTransitionTypeC(void);
s32 healthGetPerMelon(void);

void healthApplyPendingDelta(s32 playerIndex, HealthPlayerState *hudState, HealthPlayerState *playerState, s32 newHealth) {
    u8 state;
    s32 limit;

    state = hudState->unk2E2;
    if (state & 0x10) {
        hudState->unk2E2 ^= 0x10;
        if (playerState->unk2FD > 0) {
            limit = healthGetPerMelon();
            newHealth = playerState->unk2FB + playerState->unk2FD;
            limit = playerState->unk2FC * limit;
            if (newHealth < limit) {
                playerState->unk2FB = newHealth;
            } else {
                playerState->unk2FB = limit;
            }
        } else if (playerState->unk2FD < 0) {
            if ((menuIsTransitionType6() != 0) || (menuIsTransitionTypeC() != 0)) {
                playerState->unk2FB += playerState->unk2FD;
            }
            if (playerState->unk2FB <= 0) {
                playerState->unk2FB = 0;
                hudState->unk2E6 = 0xC;
                if ((s32)gPlayerCount >= 2) {
                    func_80026B0C(playerIndex);
                }
            } else {
                sfxPlayOnFreeSlot(0x24B, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
        playerState->unk2FD = 0;
    }
    if ((!(gGlobalPauseFlags & 2) && (func_805FCA64() != 0)) || (state & 0x80)) {
        hudState->unk2E5--;
        if (!hudState->unk2E5) {
            hudState->unk2E5 = 0x11;
            hudState->unk2E4 = 3;
        }
    }
}

s32 playerGetResolvedKongId(s32);
f32 sinApprox(f32);

s32 healthHudUpdateDraw(glist, playerIndex, hudState)
s32 glist;
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

    hud = (u8 *)(playerIndex * 0x306 + (s32)D_807FC950);
    idx = playerGetResolvedKongId(playerIndex);
    elem = (u8 *)((s32)hud + idx * 0x5E);
    mode = hudState->unk2E4;
    bits = hudState->unk2E3;
    single = gPlayerCount == 1;
    if (single == 0) {
        mode = 0;
    }
    if (single == 0) {
        healthApplyPendingDelta(playerIndex, (HealthPlayerState *)hudState, (HealthPlayerState *)hud, (s32)elem);
        HEALTH_HUD_FLAGS(hudState) &= 0xFFEA;
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
        HEALTH_HUD_FLAGS(hudState) ^= 1;
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
        HEALTH_HUD_FLAGS(hudState) ^= 4;
        hudState->unk2E4 = 2;
        HEALTH_HUD_FLAGS(hudState) &= 8;
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
            healthApplyPendingDelta(playerIndex, (HealthPlayerState *)hudState, (HealthPlayerState *)hud, (s32)elem);
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
    if (func_805FCA64() != 0 || (bits & 0x80)) {
        if (hudState->unk2E4 != 0 || HEALTH_HUD_FLAGS(hudState) != 0) {
            glist = (s32)healthHudDraw((Gfx *)glist, (HealthStats *)hud, elem, hudState);
        }
    }
    return glist;
}


typedef struct HealthHudPlayerView {
    u8 unk0;
    u8 pad1[0x2E1];
    u16 unk2E2;
    u8 unk2E4;
} HealthHudPlayerView;

extern s8 D_80744504;
s32 healthHudUpdateDraw();

s32 healthHudDrawAll(s32 glist) {
    s16 playerIndex;
    s32 slotOffset;
    u16 flags;
    s32 playerSlot;

    glist = glist;
    playerIndex = 0;
    if ((s32)gPlayerCount > 0) {
        do {
            slotOffset = playerIndex * 0x2F0;
            playerSlot = (s32)gPlayerSlots + slotOffset;
            if (((HealthHudPlayerView *)playerSlot)->unk0 != 0) {
                flags = ((HealthHudPlayerView *)playerSlot)->unk2E2;
                if (!(flags & 0x20) && (((((HealthHudPlayerView *)playerSlot)->unk2E4 != 0 || flags != 0) &&
                                           D_80744504 == 0) ||
                                          flags & 0x10)) {
                    glist = healthHudUpdateDraw(glist, (s16)(playerIndex + 0), (slotOffset ^ 0) + (s32)gPlayerSlots, (s32)gPlayerSlots);
                }
            }
            playerIndex += 1;
        } while (playerIndex < (s32)gPlayerCount);
    }
    return glist;
}


s32 healthGetPerMelon(void) {
    s32 ret;

    ret = 4;
    return ((s32) gPlayerCount >= 2) ? 0xA : ret;
}



void healthRefill(u8 playerIndex) {
    s32 perMelon;
    s32 playerData;
    s32 product_factor;

    perMelon = healthGetPerMelon();
    playerData = (playerIndex * 0x306) + (s32)D_807FC950;
    *(u8 *)(playerData + 0x2FD) = 0;
    *(s8 *)(playerData + 0x2FB) = (s8)(*(u8 *)(playerData + 0x2FC) * (product_factor = perMelon));
}


