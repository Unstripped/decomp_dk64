#include "common.h"
#include "jetpac.h"
#include "proto/global/135D30.h"
#include "proto/jetpac/0.h"
#include "proto/jetpac/1460.h"
#include "proto/jetpac/3060.h"
#include "proto/jetpac/3480.h"


extern s32 D_8002DC68[];
s32 jetpacRandSpawnX(void) {
    return (s32)((jetpacRandFloat() * 200.0f) + 90.0f);
}

s32 jetpacRandItemX(void) {
    return D_8002DC68[(s32)(jetpacRandFloat() * 13.0f) % 13];
}

s32 jetpacItemOverlapsBox(JetpacItem *item, f32 x1, f32 y1, f32 x2, f32 y2, s32 isOffset) {
    f32 left;
    f32 top;

    left = item->unk8;
    top = item->unkC;
    if (item->unk38 == 1) {
        return 0;
    }

    if (isOffset == 0) {
        left += (f32)item->unk24;
        top += (f32)item->unk28;
    }

    if (item->unk1C >= 2) {
        if (jetpacCheckAabbOverlapWrapped(left, top, item->unk8 + (f32)item->unk2C, item->unkC + (f32)item->unk30, x1, y1, x2, y2)) {
            return 1;
        }
    }

    return 0;
}

extern JetpacSprite D_8002D1A0[];
extern JetpacItem D_8002DC9C;

void jetpacInitRocketParts(JetpacPlayer *player) {
    s32 j;
    JetpacItem defaultItem = D_8002DC9C;
    s32 i;

    for (i = 0; i < 3; i++) {
        player->items[i] = defaultItem;
        for (j = 0; j < 2; j++) {
            player->items[i].sprites[j] = &D_8002D1A0[i * 2 + j];
        }
    }

    jetpacSetRocketSpriteFrames(player);
    player->unkC = 0;
    player->items[2].unk8 = 168.0f;
    player->items[2].unkC = 168.0f;
    player->items[0].unk8 = 48.0f;
    player->items[0].unkC = 56.0f;
    player->items[1].unk8 = 128.0f;
    player->items[1].unkC = 80.0f;
}




extern s32 D_8002F064;
extern JetpacState jetpacPlayer;
extern f32 D_8002F054;
extern f32 D_8002F058;
extern f32 D_8002F05C;
extern s32 D_8002F06C;
extern s32 D_8002F070;
extern s32 D_8002F074;
extern s32 D_8002F078;

typedef struct JetW2FpABox {
    /* 0x0 */ s32 boxX1;
} JetW2FpABox;

void jetpacRocketItemUpdate(JetpacItem *item) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.activePlayer];
    JetpacPlayerActor *player;
    JetW2FpABox *playerBox;

    if (item->unk1C == 0) {
        return;
    }
    if (inner->unkC >= 8) {
        return;
    }
    if (item->unk34 < 0x14) {
        item->unk34++;
        return;
    }
    if (item->unk1C == 1) {
        item->unk1C = 2;
    }
    player = &jetpacPlayer.player; // FAKE: pointer to the jetman keeps player->x/y uncoloured ilods loaded late for the box args (direct reads colour early)
    playerBox = (JetW2FpABox *)&D_8002F06C; // FAKE: pointer view of global steers its load
    if (item->unk38 == 0) {
        if (item->unk14 > 0.0f && D_8002F064 != 4) {
            s32 hit = jetpacCheckLedgeCollision(item->unk24 + item->unk8 + item->unk10, item->unk28 + item->unkC + item->unk14,
                                                item->unk2C + item->unk8 + item->unk10, item->unk30 + item->unkC + item->unk14, 0);
            if (hit >= 0) {
                item->unkC = jetpacGame.ledges[hit].y - 16.0f;
                item->unk14 = 0.0f;
            } else {
                item->unkC += item->unk14;
            }
        }
        if (D_8002F064 == 3) {
            if (jetpacCheckAabbOverlapWrapped(item->unk8 + item->unk24, item->unkC + item->unk28, item->unk8 + item->unk2C, item->unkC + item->unk30,
                              player->x + D_8002F06C, player->y + D_8002F070, player->x + D_8002F074,
                              player->y + D_8002F078)) {
                item->unk38 = 1;
                inner->score += item->unk3C;
                jetpacPlaySound(4);
            }
        }
    }
    if (item->unk38 == 1) {
        if (D_8002F064 == 4) {
            item->unk38 = 0;
            item->unk14 = 0.8f;
        } else {
            item->unk8 = (jetpacPlayer.player.x - 2 * D_8002F058 + playerBox->boxX1) + (D_8002F074 - D_8002F06C - item->unk2C + item->unk24) * 0.5;
            item->unkC = D_8002F054 - D_8002F05C + D_8002F078 - item->unk30;
            if (jetpacIsOverRocket(item->unk8)) {
                item->unk8 = 168.0f;
                item->unk14 = 0.8f;
                item->unk38 = 2;
            }
        }
    }
    if (item->unk38 == 2) {
        item->unkC += item->unk14;
        if (inner->unkC < 2) {
            f32 lim = 0x98 - inner->unkC * 16;
            if (lim <= item->unkC) {
                item->unkC = lim;
                inner->unkC++;
                jetpacPlaySound(2);
                if (inner->unkC < 2) {
                    inner->currentItem--;
                } else {
                    jetpacSpawnFuelPod(inner);
                }
            }
        } else if (168.0f <= item->unkC) {
            inner->unkC++;
            jetpacPlaySound(2);
            if (inner->unkC < 8) {
                jetpacSpawnFuelPod(inner);
            } else {
                item->unk1C = 0;
            }
        }
    }
}


typedef struct {
    u8 rgba[4];
} J3Color;

J3Color D_8002DCE8 = {{255, 255, 255, 1}};

void jetpacDrawItem(JetpacItem *item, s32 mode) {
    s32 x;
    s32 y;
    JetpacPlayer *inner;
    J3Color color;
    s32 i;

    color = D_8002DCE8;
    inner = &jetpacGame.players[jetpacGame.activePlayer];
    if (item->unk1C >= 2) {
        x = (s32)item->unk8;
        y = (s32)jetpacRoundFloat(item->unkC);
        if (mode < 3) {
            for (i = 0; i < 2; i++, y += 8) {
                if ((inner->unkC < 8 && inner->unkC + mode * 2 + i >= 8) || (inner->unkC == 8 && (jetpacGame.stateTimer & 0x10))) {
                    color.rgba[1] = 0;
                }
                if (item->sprites[i] != NULL) {
                    jetpacGridAddTiledSprite(item->sprites[i], x, y, color.rgba, item->unk20);
                }
            }
        } else {
            jetpacGridAddTiledSprite(item->sprites[0], x, y, item->color, item->unk20);
        }
    }
}


extern JetpacSprite D_8002D968[];

JetpacItem D_8002DCEC = {
    {NULL, NULL},
    0.0f, 16.0f, 0.0f, 0.8f,
    {255, 0, 0, 1},
    1, 0, 0, 4, 16, 16, 0, 0, 250, 0,
    jetpacBonusItemUpdate, jetpacDrawItem,
};

void jetpacSpawnBonusItem(JetpacPlayer *player) {
    JetpacItem bonusItem = D_8002DCEC;
    JetpacItem *item;
    s32 count = 5;

    if (jetpacGame.unk798 != 0 && player->score >= 5000 && flagGet(0x17B, 0) == 0 && flagGet(0x62, 2) == 0) {
        count = 6;
        bonusItem.unk40 = count;
    } else {
        bonusItem.unk40 = (s32)(jetpacRandFloat() * count) + 1;
    }

    item = &player->bonus;
    bonusItem.sprites[0] = &D_8002D968[bonusItem.unk40];
    *item = bonusItem;
    item->unk8 = (f32)jetpacRandItemX();
    player->unk144 = jetpacRandSpawnX();
}


void jetpacBonusItemUpdate(JetpacItem *item) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.activePlayer];
    s32 flashTime;
    s32 colorTime;
    s32 blinkTime;
    JetpacPlayerActor *player;

    if (inner->unkC == 0) {
        return;
    }
    if (item->unk34 < inner->unk144) {
        item->unk34++;
        return;
    }
    if (item->unk1C == 1) {
        item->unk1C = 2;
    }
    player = &jetpacPlayer.player; // FAKE: pointer to the jetman keeps player->x/y uncoloured ilods loaded late for the box args (direct reads colour early)
    if (item->unk38 == 0) {
        if (item->unk14 > 0.0f) {
            s32 hit = jetpacCheckLedgeCollision(item->unk24 + item->unk8 + item->unk10, item->unk28 + item->unkC + item->unk14,
                                                item->unk2C + item->unk8 + item->unk10, item->unk30 + item->unkC + item->unk14, 0);
            if (hit >= 0) {
                item->unkC = jetpacGame.ledges[hit].y - 16.0f;
                item->unk14 = 0.0f;
            } else {
                item->unkC += item->unk14;
            }
        }
        if (jetpacGame.gameState == 2 && D_8002F064 == 3) {
            if (jetpacCheckAabbOverlapWrapped(item->unk8 + item->unk24, item->unkC + item->unk28, item->unk8 + item->unk2C, item->unkC + item->unk30,
                              player->x + D_8002F06C, player->y + D_8002F070, player->x + D_8002F074,
                              player->y + D_8002F078)) {
                if (item->unk40 == 6) {
                    flagSet(0x62, 1, 2);
                }
                inner->score += item->unk3C;
                jetpacPlaySound(3);
                jetpacSpawnBonusItem(inner);
                return;
            }
        }
    }

    switch (item->unk40) {
    case 6:
        item->unk34++;
        flashTime = item->unk34 - inner->unk144;
        if (flashTime >= 0x97) {
            jetpacSpawnBonusItem(inner);
            return;
        }
        flashTime = flashTime % 24;
        if (flashTime < 12) {
            item->color[2] = 0xFF;
            item->color[0] = 0;
            item->color[1] = 0;
        } else if (flashTime < 24) {
            item->color[0] = 0xFF;
            item->color[1] = 0xFF;
            item->color[2] = 0;
        }
        break;
    case 1:
        item->unk34++;
        colorTime = item->unk34 - inner->unk144;
        if (colorTime >= 0x1C) {
            colorTime -= 0x1C;
            item->unk34 = inner->unk144;
        }
        if (colorTime < 0x1C) {
            colorTime = colorTime / 4 + 1;
            if (colorTime & 1) {
                item->color[2] = 0xFF;
            } else {
                item->color[2] = 0;
            }
            if (colorTime & 2) {
                item->color[0] = 0xFF;
            } else {
                item->color[0] = 0;
            }
            if (colorTime & 4) {
                item->color[1] = 0xFF;
            } else {
                item->color[1] = 0;
            }
        }
        break;
    case 2:
        item->color[0] = 0xFF;
        item->color[1] = 0xFF;
        item->color[2] = 0;
        break;
    case 5:
        item->color[1] = 0xFF;
        item->color[0] = 0;
        item->color[2] = 0;
        break;
    case 3:
    case 4:
        item->unk34++;
        blinkTime = item->unk34 - inner->unk144;
        if (blinkTime >= 0x18) {
            blinkTime -= 0x18;
            item->unk34 = inner->unk144;
        }
        if (blinkTime < 12) {
            item->color[0] = 0;
            item->color[1] = 0;
            item->color[2] = 0;
        } else if (blinkTime < 24) {
            item->color[0] = 0;
            item->color[1] = 0xFF;
            item->color[2] = 0xFF;
        }
        break;
    }
}



extern JetpacItem D_8002DD38;

void jetpacSpawnFuelPod(JetpacPlayer *player) {
    JetpacItem fuelPod = D_8002DD38;
    fuelPod.unk8 = (f32)jetpacRandItemX();
    player->items[3] = fuelPod;
    player->currentItem = 3;
}


s32 jetpacBoxOverlapsItems(f32 x1, f32 y1, f32 x2, f32 y2) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.activePlayer];
    s32 i;
    JetpacItem *item;

    if (inner->unkC < 2) {
        item = inner->items;
        for (i = 0; i < 2 - inner->unkC; i++, item++) {
            if (jetpacItemOverlapsBox(item, x1, y1, x2, y2, 1)) {
                return 1;
            }
        }
    }

    if (jetpacItemOverlapsBox(&inner->items[3], x1, y1, x2, y2, 0)) {
        return 1;
    }
    if (jetpacItemOverlapsBox(&inner->bonus, x1, y1, x2, y2, 0)) {
        return 1;
    }

    return 0;
}
void jetpacItemsUpdate(void) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];
    JetpacItem *item = player->items;
    s32 i;

    for (i = 0; i < 4; i++, item++) {
        if (item->unk1C >= 2 && item->unk48 != NULL) {
            item->unk48(item, i);
        }
    }
}
void jetpacDrawBonusItem(void) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.activePlayer];
    inner->bonus.unk48(&inner->bonus, 5);
}

void jetpacPlaceRocketOnPad(void) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.activePlayer];
    JetpacItem *item = inner->items;
    s32 i;

    inner->unkC = 8;
    for (i = 0; i < 3; i++, item++) {
        item->unk8 = 168.0f;
        item->unkC = (f32)(i * 16) + 136.0f;
    }
}

extern struct GfSndState *D_80770DF8[];

void jetpacUpdateRocketFlight(void) {
    s32 i;
    JetpacItem *item;
    f32 spd;
    f32 y;
    f32 t;

    item = jetpacGame.players[jetpacGame.activePlayer].items;

    y = item->unkC; t = (y - -8.0f) / 144.0f; t = (t < 0.0f) ? 0.0f : ((t > 1.0f) ? 1.0f : t); // LAYOUT: one line so as1 issues lwc1 $f12 (y) after the -8.0f mtc1
    if (jetpacGame.gameState == 1) {
        if (D_80770DF8[1] == 0) {
            jetpacPlaySound(1);
        }
        t = t * 0.059466f;
        t = 1.0f - t;
        jetpacSetSoundPitch(1, t);
        y = item->unkC;
        if (y >= 136.0f) {
            for (i = 0; i < 3; i++, item++) {
                item->unk8 = 168.0f;
                item->unkC = (f32)(i * 16) + 136.0f;
            }
            jetpacStopSound(1);
            jetpacSetState(2);
            return;
        }
        spd = 0.4f;
    } else if (jetpacGame.gameState == 4) {
        if (D_80770DF8[0] == 0) {
            jetpacPlaySound(0);
        }
        t = 1.0f - t;
        t = t * 0.059466f;
        t = t + 1.0f;
        jetpacSetSoundPitch(0, t);
        y = item->unkC;
        if (y < -8.0f) {
            jetpacStopSound(0);
            jetpacStartStage();
            return;
        }
        spd = -0.4f;
    }

    t = y + spd;
    for (i = 0; i < 3; i++) {
        item->unkC = t;
        t += 16.0f;
        if (!t) { // FAKE: empty guard steers regalloc
        }
        item++;
    }
}


void jetpacPlaceRocketAboveScreen(void) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.activePlayer];
    JetpacItem *item = inner->items;
    s32 i;

    inner->unkC = 2;
    for (i = 0; i < 3; i++, item++) {
        item->unk8 = 168.0f;
        item->unkC = (f32)(i * 16) + -8.0f;
    }
}

extern J3Color D_8002DD88;
extern JetpacSprite D_8002DC38[];
void jetpacDrawRocket(void) {
    JetpacItem *item;
    s32 pad;
    J3Color flameColor;
    s32 i;

    item = jetpacGame.players[jetpacGame.activePlayer].items;
    flameColor = D_8002DD88;
    if (item->unkC < 116.0f) {
        s32 mod = ((s32)item->unkC / 3) % 2;
        s32 idx = (mod > 0) ? mod : -mod;

        jetpacGridAddTiledSprite(&D_8002DC38[idx], (s32)item->unk8, (s32)((item->unkC + 48.0f) + 4.0f), flameColor.rgba, 0);
    }

    for (i = 0; i < 3; i++, item++) {
        item->unk48(item, i);
    }
}

extern void *D_8002D190[];

void jetpacSetRocketSpriteFrames(JetpacPlayer *player) {
    s32 x = player->stage / 4;
    s32 i;

    for (i = 0; i < 6; i++) {
        D_8002D1A0[i].frame = D_8002D190[x % 4];
    }
}

void jetpacInitLedge(JetpacLedge *ledge, s32 x1, s32 y1, s32 length, u8 r, u8 g, u8 b) {
    ledge->unk30 = length;
    ledge->unk8 = 0.0f;
    ledge->unkC = 0.0f;
    ledge->x = (f32)x1;
    ledge->y = (f32)y1;
    ledge->color[0] = r;
    ledge->color[1] = g;
    ledge->color[2] = b;
    ledge->color[3] = 0xFF;
    ledge->boxY1 = y1;
    ledge->boxX1 = x1;
    ledge->boxX2 = (length * 8) + x1 + 16; ledge->boxY2 = y1 + 12; // LAYOUT: one line so as1 schedules boxX2 computation before boxY2 store
}
extern JetpacLedge jetpacLedges[];

void jetpacInitLedges(void) {
    jetpacInitLedge(jetpacLedges, 0xC0, 0x30, 4, 0, 0xBE, 0);
    jetpacInitLedge(&jetpacLedges[1], 0x20, 0x48, 4, 0, 0xBE, 0);
    jetpacInitLedge(&jetpacLedges[2], 0x78, 0x60, 2, 0, 0xBE, 0);
    jetpacInitLedge(&jetpacLedges[3], 0, 0xB8, 0x1E, 0xBE, 0xBE, 0);
}
s32 jetpacCheckLedgeCollision(f32 x1, f32 y1, f32 x2, f32 y2, s32 isItem) {
    JetpacLedge *ledge = jetpacLedges;
    s32 i;

    for (i = 0; i < 4; i++, ledge++) {
        f32 boxY2 = ledge->boxY2;
        if (isItem == 0) {
            boxY2 -= 4.0f;
        }
        if (jetpacCheckAabbOverlapWrapped(x1, y1, x2, y2, ledge->boxX1, ledge->boxY1, ledge->boxX2, boxY2)) {
            return i;
        }
    }
    return -1;
}

s32 jetpacCheckLedgeEdge(s32 ledgeIndex, s32 x1, s32 x2) {
    JetpacLedge *l = jetpacGame.ledges + ledgeIndex;

    if (x1 < l->boxX1) {
        if (x2 < l->boxX1) {
            return -2;
        }
        return -1;
    }
    if (l->boxX2 < x2) {
        if (l->boxX2 < x1) {
            return 2;
        }
        return 1;
    }
    return 0;
}



extern JetpacSprite D_8002DE68;
extern JetpacSprite D_8002DE80;
extern JetpacSprite D_8002DE98;

void jetpacDrawLedges(void) {
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    JetpacLedge *l;

    for (i = 0; i < 4; i++) {
        l = &jetpacGame.ledges[i];
        x = l->x;
        y = l->y;
        jetpacGridAddTiledSprite(&D_8002DE68, x, y, l->color, 0);
        x += 8;
        for (j = 0; j < l->unk30; j++) {
            jetpacGridAddTiledSprite(&D_8002DE80, x, y, l->color, 0);
            x += 8;
        }
        jetpacGridAddTiledSprite(&D_8002DE98, x, y, l->color, 0);
    }
}

