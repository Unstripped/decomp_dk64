#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/10D2D0.h"
#include "proto/global/117190.h"
#include "proto/global/450.h"
#include "proto/global/7130.h"
#include "proto/global/90D80.h"
#include "proto/global/CC800.h"

extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;

extern Gfx D_1000118;
extern Mtx D_20000C0;

Gfx *healthHudDraw(Gfx *glist, PlayerInventory *inv, KongInventory *kong, PlayerStruct *player) {
    s16 i;
    s8 pips;
    u32 centerOffset;
    s16 baseY;
    s32 angle;
    f32 fade;
    f32 scaleX;
    f32 scaleY;
    f32 bobX;
    f32 waveY;
    s16 x;
    s16 y;

    pips = inv->health;
    fade = player->unk2E0 / 65535.0;
    centerOffset = ((inv->melons * 70) - 70) & 0xFF;
    if ((gGlobalPauseFlags & 3) || (menuIsTransitionTypeAOrE() != 0)) {
        return glist;
    }
    gSPDisplayList(glist++, &D_1000118);
    gDPSetCombineMode(glist++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    gSPMatrix(glist++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    baseY = fade * 200.0;
    for (i = 0; i < inv->melons; i++) {
        angle = (i << 10) + (gFrameCounter * 200);
        scaleX = mathSinF(angle) * 0.3 + 3.0;
        scaleY = mathSinF(angle + 0x800) * 0.3 + 3.0;
        bobX = mathSinF((angle >> 1) + 0x200) * 10.0;
        waveY = (mathSinF(angle) * 0.5 + 0.5) * 30.0;
        gDPPipeSync(glist++);
        gDPSetPrimColor(glist++, 0, 0, 255, 255, 255, (fade * 511.0f > 80.0f) ? 80.0f : fade * 511.0f);
        x = (i * 140) + 640 + bobX - centerOffset;
        y = baseY + waveY;
        glist = renderRotatedSprite(glist, 0x5D, 0, 2, 0x30, 0x2A, x, y, scaleX, -scaleY, 0, 0.0f);
        gDPPipeSync(glist++);
        gDPSetPrimColor(glist++, 0, 0, 255, 255, 255, (fade * 511.0f > 255.0f) ? 255.0f : fade * 511.0f);
        if (pips > 0) {
            glist = renderRotatedSprite(glist, (pips - 1 < 3 ? pips - 1 : 3) + 0x5A, 0, 2, 0x30, 0x2A, x, y, scaleX, -scaleY, 0, 0.0f);
        }
        if (pips - 4 < 0) {
            pips = 0;
        } else {
            pips = pips - 4;
        }
    }
    gDPPipeSync(glist++);
    return glist;
}


void healthHudReset(HealthHudInit *hudInit) {
    if (gGlobalOverlayFlags & 0x800) {
        hudInit->unk6 = 0x20;
    } else {
        hudInit->unk6 = 1;
    }
    if (menuIsTransitionType3Or4() != 0) {
        hudInit->unk6 = 0x20;
    }
    hudInit->unkA = 0;
    hudInit->unk8 = 0;
    hudInit->unk4 = 0;
    hudInit->unk0 = 4.0f;
}



void func_80026B0C(s32);

void healthApplyPendingDelta(s32 playerIndex, PlayerStruct *player, PlayerInventory *inv, KongInventory *kong) {
    u8 flags;
    s32 perMelon;

    flags = player->unk2E2;
    if (flags & 0x10) {
        player->unk2E2 ^= 0x10;
        if (inv->healthDelta > 0) {
            perMelon = healthGetPerMelon();
            if (inv->health + inv->healthDelta < inv->melons * perMelon) {
                inv->health += inv->healthDelta;
            } else {
                inv->health = inv->melons * perMelon;
            }
        } else if (inv->healthDelta < 0) {
            if ((menuIsTransitionType6() != 0) || (menuIsTransitionTypeC() != 0)) {
                inv->health += inv->healthDelta;
            }
            if (inv->health <= 0) {
                inv->health = 0;
                player->unk2E6 = 0xC;
                if (gPlayerCount >= 2) {
                    func_80026B0C(playerIndex);
                }
            } else {
                sfxPlayOnFreeSlot(0x24B, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
        inv->healthDelta = 0;
    }
    if ((!(gGlobalPauseFlags & 2) && (hudCanRender() != 0)) || (flags & 0x80)) {
        player->unk2E5--;
        if (!player->unk2E5) {
            player->unk2E5 = 17;
            player->unk2E4 = 3;
        }
    }
}


Gfx *healthHudUpdateDraw(Gfx *glist, s16 playerIndex, PlayerStruct *player) {
    s32 kongId;
    f32 angle;
    PlayerInventory *inv;
    KongInventory *kong;
    u8 mode;
    u8 flags;
    s32 singlePlayer;

    inv = &gPlayerInventoryTable[playerIndex];
    kongId = playerGetResolvedKongId(playerIndex);
    kong = &inv->kong[kongId];
    mode = player->unk2E4;
    flags = player->unk2E3;
    singlePlayer = gPlayerCount == 1;
    if (!singlePlayer) {
        mode = 0;
    }
    if (!singlePlayer) {
        healthApplyPendingDelta(playerIndex, player, inv, kong);
        player->unk2E2 &= 0xFFEA;
        flags = player->unk2E3;
    }
    if (flags & 0x10) {
        switch (mode) {
        case 2:
            player->unk2E5 = 50;
            break;
        case 3:
            player->unk2E5 = 18.0 - player->unk2E5;
            player->unk2E4 = 1;
            break;
        }
    }
    if (flags & 1) {
        player->unk2E2 ^= 1;
        switch (mode) {
        case 0:
            player->unk2E5 = 18;
            player->unk2E4 = 1;
            break;
        case 1:
            break;
        case 3:
            player->unk2E5 = 18.0 - player->unk2E5;
            player->unk2E4 = 1;
            break;
        }
    } else if (flags & 4) {
        player->unk2E5 = 1;
        player->unk2E2 ^= 4;
        player->unk2E4 = 2;
        player->unk2E2 &= 8;
    } else {
        switch (mode) {
        case 1:
            angle = player->unk2E5 / 18.0 * 1.5707963705062866 + 1.5707963705062866;
            player->unk2E0 = sinApprox(angle) * 65535.0;
            if (player->unk2E5-- == 0) {
                player->unk2E4 = 2;
                player->unk2E5 = 50;
            }
            break;
        case 2:
            healthApplyPendingDelta(playerIndex, player, inv, kong);
            break;
        case 3:
            angle = 1.5707963705062866 - player->unk2E5 / 18.0 * 1.5707963705062866 + 1.5707963705062866;
            player->unk2E0 = sinApprox(angle) * 65535.0;
            if (player->unk2E5-- == 0) {
                player->unk2E4 = 0;
            }
            break;
        }
    }
    if (hudCanRender() != 0 || (flags & 0x80)) {
        if (player->unk2E4 != 0 || player->unk2E2 != 0) {
            glist = healthHudDraw(glist, inv, kong, player);
        }
    }
    return glist;
}


extern s8 gMapLoadPauseFrames;

Gfx *healthHudDrawAll(Gfx *glist) {
    s16 playerIndex;
    u16 flags;

    for (playerIndex = 0; playerIndex < gPlayerCount; playerIndex++) {
        if (gPlayerSlots[playerIndex].active) {
            flags = gPlayerSlots[playerIndex].unk2E2;
            if (!(flags & 0x20) && (((gPlayerSlots[playerIndex].unk2E4 || flags) && !gMapLoadPauseFrames) || (flags & 0x10))) {
                glist = healthHudUpdateDraw(glist, playerIndex, &gPlayerSlots[playerIndex]);
            }
        }
    }
    return glist;
}


s32 healthGetPerMelon(void) {
    return (gPlayerCount >= 2) ? 10 : 4;
}



void healthRefill(u8 playerIndex) {
    PlayerInventory *inv;

    inv = &gPlayerInventoryTable[playerIndex];
    inv->health = inv->melons * healthGetPerMelon();
    inv->healthDelta = 0;
}


