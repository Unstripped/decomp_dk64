#include "common.h"
#include "jetpac.h"
#include "proto/global/135D30_flags.h"
#include "proto/jetpac/0_game.h"
#include "proto/jetpac/1460_sprite_grid.h"
#include "proto/jetpac/3060_collision_utils.h"
#include "proto/jetpac/3480_rocket_items.h"

typedef struct {
    u8 rgba[4];
} JetpacColor;

// .data 0x8002C570-0x8002DEB0 (sprite pixel layout: see 0.c).
Gfx D_8002C570[1] = { gsSPEndDisplayList() };
u8 D_8002C578[0x308] = {
#include "jetpac/D_8002C578.inc.c"
};
u8 D_8002C880[0x308] = {
#include "jetpac/D_8002C880.inc.c"
};
u8 D_8002CB88[0x308] = {
#include "jetpac/D_8002CB88.inc.c"
};
u8 D_8002CE90[0x300] = {
#include "jetpac/D_8002CE90.inc.c"
};
// Rocket pixels per four stages (jetpacSetRocketSpriteFrames).
void *jetpacRocketPixels[4] = { D_8002C578, D_8002C880, D_8002CB88, D_8002CE90 };
TextureDescriptor jetpacRocketSprites[6] = {
    { NULL, 0, 16, 16, 8, 4, 1, 0, 0, 0 },
    { NULL, 0, 16, 16, 8, 4, 1, 0, 8, 0 },
    { NULL, 0, 16, 16, 8, 4, 1, 0, 16, 0 },
    { NULL, 0, 16, 16, 8, 4, 1, 0, 24, 0 },
    { NULL, 0, 16, 16, 8, 4, 1, 0, 32, 0 },
    { NULL, 0, 16, 16, 8, 4, 1, 0, 40, 0 },
};
Gfx D_8002D230[1] = { gsSPEndDisplayList() };
u8 D_8002D238[0x108] = {
#include "jetpac/D_8002D238.inc.c"
};
u8 D_8002D340[0x108] = {
#include "jetpac/D_8002D340.inc.c"
};
u8 D_8002D448[0x108] = {
#include "jetpac/D_8002D448.inc.c"
};
u8 D_8002D550[0x108] = {
#include "jetpac/D_8002D550.inc.c"
};
u8 D_8002D658[0x108] = {
#include "jetpac/D_8002D658.inc.c"
};
u8 D_8002D760[0x108] = {
#include "jetpac/D_8002D760.inc.c"
};
u8 D_8002D868[0x100] = {
#include "jetpac/D_8002D868.inc.c"
};
TextureDescriptor jetpacItemSprites[8] = {
    { D_8002D238, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002D340, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002D448, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002D550, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002D658, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002D760, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002D868, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
Gfx D_8002DA28[1] = { gsSPEndDisplayList() };
u8 D_8002DA30[0x108] = {
#include "jetpac/D_8002DA30.inc.c"
};
u8 D_8002DB38[0x100] = {
#include "jetpac/D_8002DB38.inc.c"
};
TextureDescriptor jetpacRocketFlameSprites[2] = {
    { D_8002DA30, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002DB38, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
};
s32 jetpacItemSpawnXTable[13] = { 8, 32, 40, 48, 56, 64, 88, 96, 120, 128, 136, 192, 224 };
JetpacItem jetpacRocketPartTemplate = {
    {NULL, NULL},
    0.0f, 0.0f, 0.0f, 0.0f,
    {255, 255, 255, 1},
    2, 0, 0, 4, 16, 16, 20, 0, 100, 8,
    jetpacRocketItemUpdate, jetpacDrawItem,
};
JetpacColor jetpacRocketPartColor = {{255, 255, 255, 1}};
JetpacItem jetpacBonusItemTemplate = {
    {NULL, NULL},
    0.0f, 16.0f, 0.0f, 0.8f,
    {255, 0, 0, 1},
    1, 0, 0, 4, 16, 16, 0, 0, 250, 0,
    jetpacBonusItemUpdate, jetpacDrawItem,
};
JetpacItem jetpacFuelPodTemplate = {
    {jetpacItemSprites, NULL},
    0.0f, 16.0f, 0.0f, 0.8f,
    {255, 0, 255, 1},
    1, 0, 0, 4, 16, 16, 0, 0, 100, 0,
    jetpacRocketItemUpdate, jetpacDrawItem,
};
s32 D_8002DD84 = 0; // unreferenced
JetpacColor jetpacRocketFlameColor = {{255, 0, 0, 1}};
Gfx D_8002DD90[1] = { gsSPEndDisplayList() };
u8 D_8002DD98[0x48] = {
#include "jetpac/D_8002DD98.inc.c"
};
u8 D_8002DDE0[0x48] = {
#include "jetpac/D_8002DDE0.inc.c"
};
u8 D_8002DE28[0x40] = {
#include "jetpac/D_8002DE28.inc.c"
};
TextureDescriptor jetpacLedgeLeftSprite = { D_8002DD98, 0, 8, 8, 8, 4, 1, 0, 0, 0 };
TextureDescriptor jetpacLedgeMidSprite = { D_8002DDE0, 0, 8, 8, 8, 4, 1, 0, 0, 0 };
TextureDescriptor jetpacLedgeRightSprite = { D_8002DE28, 0, 8, 8, 8, 4, 1, 0, 0, 0 };

s32 jetpacRandBonusDelay(void) {
    return jetpacRandFloat() * 200.0f + 90.0f;
}

s32 jetpacRandItemX(void) {
    return jetpacItemSpawnXTable[(s32)(jetpacRandFloat() * 13.0f) % 13];
}

s32 jetpacItemOverlapsBox(JetpacItem *item, f32 x1, f32 y1, f32 x2, f32 y2, s32 isOffset) {
    f32 left;
    f32 top;

    left = item->x;
    top = item->y;
    if (item->carryState == 1) {
        return 0;
    }

    if (isOffset == 0) {
        left += item->boxX1;
        top += item->boxY1;
    }

    if (item->spawnState >= 2) {
        if (jetpacCheckAabbOverlapWrapped(left, top, item->x + item->boxX2, item->y + item->boxY2, x1, y1, x2, y2)) {
            return 1;
        }
    }

    return 0;
}

void jetpacInitRocketParts(JetpacPlayer *player) {
    s32 j;
    JetpacItem defaultItem = jetpacRocketPartTemplate;
    s32 i;

    for (i = 0; i < 3; i++) {
        player->items[i] = defaultItem;
        for (j = 0; j < 2; j++) {
            player->items[i].sprites[j] = &jetpacRocketSprites[i * 2 + j];
        }
    }

    jetpacSetRocketSpriteFrames(player);
    player->rocketProgress = 0;
    player->items[2].x = 168.0f;
    player->items[2].y = 168.0f;
    player->items[0].x = 48.0f;
    player->items[0].y = 56.0f;
    player->items[1].x = 128.0f;
    player->items[1].y = 80.0f;
}

void jetpacRocketItemUpdate(JetpacItem *item) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];
    JetpacPlayerActor *jetman;

    if (item->spawnState == 0) {
        return;
    }
    if (player->rocketProgress >= 8) {
        return;
    }
    if (item->timer < 20) {
        item->timer++;
        return;
    }
    if (item->spawnState == 1) {
        item->spawnState = 2;
    }
    jetman = &jetpacGame.player;
    if (item->carryState == 0) {
        if (item->vy > 0.0f && jetman->head.state != 4) {
            s32 hit = jetpacCheckLedgeCollision(item->boxX1 + item->x + item->vx, item->boxY1 + item->y + item->vy,
                                                item->boxX2 + item->x + item->vx, item->boxY2 + item->y + item->vy, 0);
            if (hit >= 0) {
                item->y = jetpacGame.ledges[hit].y - 16.0f;
                item->vy = 0.0f;
            } else {
                item->y += item->vy;
            }
        }
        if (jetman->head.state == 3) {
            if (jetpacCheckAabbOverlapWrapped(item->x + item->boxX1, item->y + item->boxY1, item->x + item->boxX2, item->y + item->boxY2,
                              jetman->head.x + jetman->head.boxX1, jetman->head.y + jetman->head.boxY1, jetman->head.x + jetman->head.boxX2,
                              jetman->head.y + jetman->head.boxY2)) {
                item->carryState = 1;
                player->score += item->points;
                jetpacPlaySound(4);
            }
        }
    }
    if (item->carryState == 1) {
        if (jetman->head.state == 4) {
            item->carryState = 0;
            item->vy = 0.8f;
        } else {
            item->x = (jetman->head.x - 2 * jetman->head.vx + jetman->head.boxX1) + (jetman->head.boxX2 - jetman->head.boxX1 - item->boxX2 + item->boxX1) * 0.5;
            item->y = jetman->head.y - jetman->head.vy + jetman->head.boxY2 - item->boxY2;
            if (jetpacIsOverRocket(item->x)) {
                item->x = 168.0f;
                item->vy = 0.8f;
                item->carryState = 2;
            }
        }
    }
    if (item->carryState == 2) {
        item->y += item->vy;
        if (player->rocketProgress < 2) {
            f32 landY = 152 - player->rocketProgress * 16;
            if (item->y >= landY) {
                item->y = landY;
                player->rocketProgress++;
                jetpacPlaySound(2);
                if (player->rocketProgress < 2) {
                    player->currentItem--;
                } else {
                    jetpacSpawnFuelPod(player);
                }
            }
        } else if (item->y >= 168.0f) {
            player->rocketProgress++;
            jetpacPlaySound(2);
            if (player->rocketProgress < 8) {
                jetpacSpawnFuelPod(player);
            } else {
                item->spawnState = 0;
            }
        }
    }
}

void jetpacDrawItem(JetpacItem *item, s32 mode) {
    s32 x;
    s32 y;
    JetpacPlayer *player;
    JetpacColor color;
    s32 i;

    color = jetpacRocketPartColor;
    player = &jetpacGame.players[jetpacGame.activePlayer];
    if (item->spawnState >= 2) {
        x = item->x;
        y = jetpacRoundFloat(item->y);
        if (mode < 3) {
            for (i = 0; i < 2; i++, y += 8) {
                if ((player->rocketProgress < 8 && player->rocketProgress + mode * 2 + i >= 8) || (player->rocketProgress == 8 && (jetpacGame.stateTimer & 0x10))) {
                    color.rgba[1] = 0;
                }
                if (item->sprites[i] != NULL) {
                    jetpacGridAddTiledSprite(item->sprites[i], x, y, color.rgba, item->flip);
                }
            }
        } else {
            jetpacGridAddTiledSprite(item->sprites[0], x, y, item->color, item->flip);
        }
    }
}

void jetpacSpawnBonusItem(JetpacPlayer *player) {
    JetpacItem bonusItem = jetpacBonusItemTemplate;
    JetpacItem *item;
    s32 count = 5;

    if (jetpacGame.coinChallenge != 0 && player->score >= 5000 && flagGet(0x17B, 0) == 0 && flagGet(0x62, 2) == 0) {
        count = 6;
        bonusItem.kind = count;
    } else {
        bonusItem.kind = (s32)(jetpacRandFloat() * count) + 1;
    }

    item = &player->bonus;
    bonusItem.sprites[0] = &jetpacItemSprites[bonusItem.kind];
    *item = bonusItem;
    item->x = jetpacRandItemX();
    player->bonusDelay = jetpacRandBonusDelay();
}

void jetpacBonusItemUpdate(JetpacItem *item) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];
    s32 flashTime;
    s32 colorTime;
    s32 blinkTime;
    JetpacPlayerActor *jetman;

    if (player->rocketProgress == 0) {
        return;
    }
    if (item->timer < player->bonusDelay) {
        item->timer++;
        return;
    }
    if (item->spawnState == 1) {
        item->spawnState = 2;
    }
    jetman = &jetpacGame.player;
    if (item->carryState == 0) {
        if (item->vy > 0.0f) {
            s32 hit = jetpacCheckLedgeCollision(item->boxX1 + item->x + item->vx, item->boxY1 + item->y + item->vy,
                                                item->boxX2 + item->x + item->vx, item->boxY2 + item->y + item->vy, 0);
            if (hit >= 0) {
                item->y = jetpacGame.ledges[hit].y - 16.0f;
                item->vy = 0.0f;
            } else {
                item->y += item->vy;
            }
        }
        if (jetpacGame.gameState == 2 && jetman->head.state == 3) {
            if (jetpacCheckAabbOverlapWrapped(item->x + item->boxX1, item->y + item->boxY1, item->x + item->boxX2, item->y + item->boxY2,
                              jetman->head.x + jetman->head.boxX1, jetman->head.y + jetman->head.boxY1, jetman->head.x + jetman->head.boxX2,
                              jetman->head.y + jetman->head.boxY2)) {
                if (item->kind == 6) {
                    flagSet(0x62, 1, 2);
                }
                player->score += item->points;
                jetpacPlaySound(3);
                jetpacSpawnBonusItem(player);
                return;
            }
        }
    }

    switch (item->kind) {
    case 6:
        item->timer++;
        flashTime = item->timer - player->bonusDelay;
        if (flashTime >= 151) {
            jetpacSpawnBonusItem(player);
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
        item->timer++;
        colorTime = item->timer - player->bonusDelay;
        if (colorTime >= 28) {
            colorTime -= 28;
            item->timer = player->bonusDelay;
        }
        if (colorTime < 28) {
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
        item->timer++;
        blinkTime = item->timer - player->bonusDelay;
        if (blinkTime >= 24) {
            blinkTime -= 24;
            item->timer = player->bonusDelay;
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

void jetpacSpawnFuelPod(JetpacPlayer *player) {
    JetpacItem fuelPod = jetpacFuelPodTemplate;
    fuelPod.x = jetpacRandItemX();
    player->items[3] = fuelPod;
    player->currentItem = 3;
}

s32 jetpacBoxOverlapsItems(f32 x1, f32 y1, f32 x2, f32 y2) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];
    s32 i;
    JetpacItem *item;

    if (player->rocketProgress < 2) {
        item = player->items;
        for (i = 0; i < 2 - player->rocketProgress; i++, item++) {
            if (jetpacItemOverlapsBox(item, x1, y1, x2, y2, 1)) {
                return 1;
            }
        }
    }

    if (jetpacItemOverlapsBox(&player->items[3], x1, y1, x2, y2, 0)) {
        return 1;
    }
    if (jetpacItemOverlapsBox(&player->bonus, x1, y1, x2, y2, 0)) {
        return 1;
    }

    return 0;
}

void jetpacDrawItems(void) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];
    JetpacItem *item = player->items;
    s32 i;

    for (i = 0; i < 4; i++, item++) {
        if (item->spawnState >= 2 && item->draw != NULL) {
            item->draw(item, i);
        }
    }
}

void jetpacDrawBonusItem(void) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];
    player->bonus.draw(&player->bonus, 5);
}

void jetpacPlaceRocketOnPad(void) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];
    JetpacItem *item = player->items;
    s32 i;

    player->rocketProgress = 8;
    for (i = 0; i < 3; i++, item++) {
        item->x = 168.0f;
        item->y = i * 16 + 136.0f;
    }
}

extern struct GfSndState *gLoopSfxHandles[];

void jetpacUpdateRocketFlight(void) {
    s32 i;
    JetpacItem *item;
    f32 speed;
    f32 y;
    f32 t;
    f32 pos;

    item = jetpacGame.players[jetpacGame.activePlayer].items;

    y = item->y; t = (y - -8.0f) / 144.0f; t = (t < 0.0f) ? 0.0f : ((t > 1.0f) ? 1.0f : t); // LAYOUT: one line so as1 issues lwc1 $f12 (y) after the -8.0f mtc1
    if (jetpacGame.gameState == 1) {
        if (gLoopSfxHandles[1] == NULL) {
            jetpacPlaySound(1);
        }
        t = t * 0.059466f;
        t = 1.0f - t;
        jetpacSetSoundPitch(1, t);
        y = item->y;
        if (y >= 136.0f) {
            for (i = 0; i < 3; i++, item++) {
                item->x = 168.0f;
                item->y = i * 16 + 136.0f;
            }
            jetpacStopSound(1);
            jetpacSetState(2);
            return;
        }
        speed = 0.4f;
    } else if (jetpacGame.gameState == 4) {
        if (gLoopSfxHandles[0] == NULL) {
            jetpacPlaySound(0);
        }
        t = 1.0f - t;
        t = t * 0.059466f;
        t = t + 1.0f;
        jetpacSetSoundPitch(0, t);
        y = item->y;
        if (y < -8.0f) {
            jetpacStopSound(0);
            jetpacStartStage();
            return;
        }
        speed = -0.4f;
    }

    pos = y + speed;
    for (i = 0; i < 3; i++) {
        item->y = pos;
        pos += 16.0f;
        item++;
    }
}

void jetpacPlaceRocketAboveScreen(void) {
    JetpacPlayer *player = &jetpacGame.players[jetpacGame.activePlayer];
    JetpacItem *item = player->items;
    s32 i;

    player->rocketProgress = 2;
    for (i = 0; i < 3; i++, item++) {
        item->x = 168.0f;
        item->y = -8.0f + i * 16;
    }
}

void jetpacDrawRocket(void) {
    JetpacItem *item;
    s32 pad;
    JetpacColor flameColor;
    s32 i;

    item = jetpacGame.players[jetpacGame.activePlayer].items;
    flameColor = jetpacRocketFlameColor;
    if (item->y < 116.0f) {
        s32 mod = ((s32)item->y / 3) % 2;
        s32 frame = (mod > 0) ? mod : -mod;

        jetpacGridAddTiledSprite(&jetpacRocketFlameSprites[frame], item->x, item->y + 48.0f + 4.0f, flameColor.rgba, 0);
    }

    for (i = 0; i < 3; i++, item++) {
        item->draw(item, i);
    }
}

void jetpacSetRocketSpriteFrames(JetpacPlayer *player) {
    s32 rocket = player->stage / 4;
    s32 i;

    for (i = 0; i < 6; i++) {
        jetpacRocketSprites[i].image = jetpacRocketPixels[rocket % 4];
    }
}

void jetpacInitLedge(JetpacLedge *ledge, s32 x1, s32 y1, s32 length, u8 r, u8 g, u8 b) {
    ledge->length = length;
    ledge->unk8 = 0.0f;
    ledge->unkC = 0.0f;
    ledge->x = x1;
    ledge->y = y1;
    ledge->color[0] = r;
    ledge->color[1] = g;
    ledge->color[2] = b;
    ledge->color[3] = 0xFF;
    ledge->boxY1 = y1;
    ledge->boxX1 = x1;
    ledge->boxX2 = (length * 8) + x1 + 16; ledge->boxY2 = y1 + 12; // LAYOUT: one line so as1 schedules boxX2 computation before boxY2 store
}

void jetpacInitLedges(void) {
    jetpacInitLedge(&jetpacGame.ledges[0], 192, 48, 4, 0, 0xBE, 0);
    jetpacInitLedge(&jetpacGame.ledges[1], 32, 72, 4, 0, 0xBE, 0);
    jetpacInitLedge(&jetpacGame.ledges[2], 120, 96, 2, 0, 0xBE, 0);
    jetpacInitLedge(&jetpacGame.ledges[3], 0, 184, 30, 0xBE, 0xBE, 0);
}

s32 jetpacCheckLedgeCollision(f32 x1, f32 y1, f32 x2, f32 y2, s32 isItem) {
    JetpacLedge *ledge = jetpacGame.ledges;
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
    JetpacLedge *ledge = &jetpacGame.ledges[ledgeIndex];

    if (x1 < ledge->boxX1) {
        if (x2 < ledge->boxX1) {
            return -2;
        }
        return -1;
    }
    if (x2 > ledge->boxX2) {
        if (x1 > ledge->boxX2) {
            return 2;
        }
        return 1;
    }
    return 0;
}

void jetpacDrawLedges(void) {
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    JetpacLedge *ledge;

    for (i = 0; i < 4; i++) {
        ledge = &jetpacGame.ledges[i];
        x = ledge->x;
        y = ledge->y;
        jetpacGridAddTiledSprite(&jetpacLedgeLeftSprite, x, y, ledge->color, 0);
        x += 8;
        for (j = 0; j < ledge->length; j++) {
            jetpacGridAddTiledSprite(&jetpacLedgeMidSprite, x, y, ledge->color, 0);
            x += 8;
        }
        jetpacGridAddTiledSprite(&jetpacLedgeRightSprite, x, y, ledge->color, 0);
    }
}

