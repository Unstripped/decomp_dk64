#include "common.h"
#include "jetpac.h"
#define PROTO_SKIP_jetpacSetSoundPitch // FAKE: callee prototype steer
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
    f32 fa0;
    f32 fa1;

    fa0 = item->unk8;
    fa1 = item->unkC;
    if (item->unk38 == 1) {
        return 0;
    }

    if (isOffset == 0) {
        fa0 += (f32)item->unk24;
        fa1 += (f32)item->unk28;
    }

    if (item->unk1C >= 2) {
        if (jetpacCheckAabbOverlapWrapped(fa0, fa1, item->unk8 + (f32)item->unk2C, item->unkC + (f32)item->unk30, x1, y1, x2, y2)) {
            return 1;
        }
    }

    return 0;
}

extern JetpacSprite D_8002D1A0[];
extern JetpacSprite D_8002D230[];
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
extern f32 jetpacPlayer;
extern f32 D_8002F054;
extern f32 D_8002F058;
extern f32 D_8002F05C;
extern s32 D_8002F06C;
extern s32 D_8002F070;
extern s32 D_8002F074;
extern s32 D_8002F078;

typedef struct JetW2FpABox {
    /* 0x0 */ s32 unk0;
} JetW2FpABox;

void jetpacRocketItemUpdate(JetpacItem *item) {
    JetpacPlayer *inner = &jetpacGame.players[jetpacGame.activePlayer];
    f32 *new_var;
    f32 *new_var2;
    JetW2FpABox *new_var3;

    if (item->unk1C == 0) {
        return;
    }
    if (inner->unkC >= 8) {
        return;
    }
    if (item->unk34 < 0x14) {
        item->unk34 = item->unk34 + 1;
        return;
    }
    if (item->unk1C == 1) {
        item->unk1C = 2;
    }
    new_var = &jetpacPlayer;
    new_var2 = &D_8002F054;
    new_var3 = (JetW2FpABox *)&D_8002F06C;
    if (item->unk38 == 0) {
        if (item->unk14 > 0.0f && D_8002F064 != 4) {
            f32 x = item->unk8;
            s32 hit = jetpacCheckLedgeCollision((f32)item->unk24 + x + item->unk10, (f32)item->unk28 + item->unkC + item->unk14,
                                                (f32)item->unk2C + x + item->unk10, (f32)item->unk30 + item->unkC + item->unk14, 0);
            if (hit >= 0) {
                item->unkC = jetpacGame.ledges[hit].y - 16.0f;
                item->unk14 = 0.0f;
            } else {
                item->unkC = item->unkC + item->unk14;
            }
        }
        if (D_8002F064 == 3) {
            if (jetpacCheckAabbOverlapWrapped(item->unk8 + (f32)item->unk24, item->unkC + (f32)item->unk28, item->unk8 + (f32)item->unk2C, item->unkC + (f32)item->unk30,
                              (*new_var) + (f32)D_8002F06C, (*new_var2) + (f32)D_8002F070, (*new_var) + (f32)D_8002F074,
                              (*new_var2) + (f32)D_8002F078)) {
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
            item->unk8 = (jetpacPlayer - (f32)2 * D_8002F058 + (f32)new_var3->unk0) + (D_8002F074 - D_8002F06C - item->unk2C + item->unk24) * 0.5;
            item->unkC = D_8002F054 - D_8002F05C + (f32)D_8002F078 - (f32)item->unk30;
            if (jetpacIsOverRocket(item->unk8)) {
                item->unk8 = 168.0f;
                item->unk14 = 0.8f;
                item->unk38 = 2;
            }
        }
    }
    if (item->unk38 == 2) {
        item->unkC = item->unkC + item->unk14;
        if (inner->unkC < 2) {
            f32 lim = (f32)(0x98 - (inner->unkC << 4));
            if (lim <= item->unkC) {
                item->unkC = lim;
                inner->unkC = inner->unkC + 1;
                jetpacPlaySound(2);
                if (inner->unkC < 2) {
                    inner->currentItem = inner->currentItem - 1;
                } else {
                    jetpacSpawnFuelPod(inner);
                }
            }
        } else if (168.0f <= item->unkC) {
            inner->unkC = inner->unkC + 1;
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
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} J3Color;

J3Color D_8002DCE8 = {255, 255, 255, 1};
extern s32 D_8002F3C0;

void jetpacDrawItem(JetpacItem *item, s32 mode) {
    s32 x;
    s32 y;
    JetpacPlayer *inner;
    J3Color color;
    s32 i;

    color = D_8002DCE8;
    inner = &jetpacGame.players[jetpacGame.activePlayer];
    if (D_8002F3C0) { // FAKE: empty guard steers regalloc
    }
    if (item->unk1C >= 2) {
        x = (s32)item->unk8;
        y = (s32)jetpacRoundFloat(item->unkC);
        if (mode < 3) {
            for (i = 0; i < 2; i++, y += 8) {
                if ((inner->unkC < 8 && inner->unkC + mode * 2 + i >= 8) || (inner->unkC == 8 && (D_8002F3C0 & 0x10))) {
                    color.g = 0;
                }
                if (item->sprites[i] != NULL) {
                    jetpacGridAddTiledSprite(item->sprites[i], x, y, &color, item->unk20);
                }
            }
        } else {
            jetpacGridAddTiledSprite(item->sprites[0], x, y, item->color, item->unk20);
        }
    }
}


extern u8 D_8002F3C8;
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

    if (D_8002F3C8 != 0 && player->score >= 5000 && flagGet(0x17B, 0) == 0 && flagGet(0x62, 2) == 0) {
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
    s32 v;
    s32 v1;
    s32 v34;
    f32 *new_var;
    f32 *new_var2;

    if (inner->unkC == 0) {
        return;
    }
    {
        s32 t = item->unk34;
        if (t < inner->unk144) {
            item->unk34 = t + 1;
            return;
        }
    }
    if (item->unk1C == 1) {
        item->unk1C = 2;
    }
    new_var = &jetpacPlayer;
    new_var2 = &D_8002F054;
    if (item->unk38 == 0) {
        if (item->unk14 > 0.0f) {
            f32 x = item->unk8;
            s32 hit = jetpacCheckLedgeCollision((f32)item->unk24 + x + item->unk10, (f32)item->unk28 + item->unkC + item->unk14,
                                                (f32)item->unk2C + x + item->unk10, (f32)item->unk30 + item->unkC + item->unk14, 0);
            if (hit >= 0) {
                item->unkC = jetpacGame.ledges[hit].y - 16.0f;
                item->unk14 = 0.0f;
            } else {
                item->unkC = item->unkC + item->unk14;
            }
        }
        if (jetpacGame.gameState == 2U && D_8002F064 == 3) {
            if (jetpacCheckAabbOverlapWrapped(item->unk8 + (f32)item->unk24, item->unkC + (f32)item->unk28, item->unk8 + (f32)item->unk2C, item->unkC + (f32)item->unk30,
                              (*new_var) + (f32)D_8002F06C, (*new_var2) + (f32)D_8002F070, (*new_var) + (f32)D_8002F074,
                              (*new_var2) + (f32)D_8002F078)) {
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
        v = item->unk34 - inner->unk144;
        if (v >= 0x97) {
            jetpacSpawnBonusItem(inner);
            return;
        }
        v = v % 24;
        if (v < 12) {
            item->color[2] = 0xFF;
            item->color[0] = 0;
            item->color[1] = 0;
        } else if (v < 24) {
            item->color[0] = 0xFF;
            item->color[1] = 0xFF;
            item->color[2] = 0;
        }
        break;
    case 1:
        item->unk34++;
        v1 = item->unk34 - inner->unk144;
        if (v1 >= 0x1C) {
            v1 -= 0x1C;
            item->unk34 = inner->unk144;
        }
        if (v1 < 0x1C) {
            v1 = v1 / 4 + 1;
            if (v1 & 1) {
                item->color[2] = 0xFF;
            } else {
                item->color[2] = 0;
            }
            if (v1 & 2) {
                item->color[0] = 0xFF;
            } else {
                item->color[0] = 0;
            }
            if (v1 & 4) {
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
        v34 = item->unk34 - inner->unk144;
        if (v34 >= 0x18) {
            v34 -= 0x18;
            item->unk34 = inner->unk144;
        }
        if (v34 < 12) {
            item->color[0] = 0;
            item->color[1] = 0;
            item->color[2] = 0;
        } else if (v34 < 24) {
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
    s32 unkC = inner->unkC;
    s32 i;
    JetpacItem *item;

    if (unkC < 2) {
        item = inner->items;
        i = 0;
        if (2 - unkC > 0) {
            do {
                if (jetpacItemOverlapsBox(item, x1, y1, x2, y2, 1)) {
                    return 1;
                }
                i++;
                item++;
            } while (i < 2 - inner->unkC);
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
    s32 i = 0;
    s32 count = 4;

    do {
        if (item->unk1C >= 2 && item->unk48 != NULL) {
            item->unk48(item, i);
        }
        i++;
        item++;
    } while (i != count);
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
void jetpacSetSoundPitch(s32, f32);  // FAKE: callee prototype steer

void jetpacUpdateRocketFlight(void) {
    s32 i;
    JetpacItem *item;
    f32 spd;
    f32 y;
    f32 t;

    item = jetpacGame.players[jetpacGame.activePlayer].items;

    y = item->unkC; t = (y - -8.0f) / 144.0f; t = (t < 0.0f) ? 0.0f : ((t > 1.0f) ? 1.0f : t);
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

extern s32 D_8002DD88;
typedef struct {
    s32 v;
} J3Word;
extern JetpacSprite D_8002DC38[];
void jetpacDrawRocket(void) {
    JetpacItem *item;
    s32 pad;
    J3Word flameColor;
    s32 i;

    item = jetpacGame.players[jetpacGame.activePlayer].items;
    flameColor = *(J3Word *)&D_8002DD88;
    if (116.0f > item->unkC) {
        s32 mod = ((s32)item->unkC / 3) % 2;
        s32 idx = (mod > 0) ? mod : -mod;

        jetpacGridAddTiledSprite(&D_8002DC38[idx], (s32)item->unk8, (s32)((item->unkC + 48.0f) + 4.0f), &flameColor, 0);
    }

    i = 0;
    do {
        item->unk48(item, i);
        i++;
        item++;
    } while (i != 3);
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
    ledge->boxY2 = (ledge->boxX2 = (length * 8) + x1 + 16, y1 + 12);
}
extern JetpacLedge jetpacLedges[];
extern JetpacLedge D_8002EFB4[];
extern JetpacLedge D_8002EFE8[];
extern JetpacLedge D_8002F01C[];

void jetpacInitLedges(void) {
    jetpacInitLedge(jetpacLedges, 0xC0, 0x30, 4, 0, 0xBE, 0);
    jetpacInitLedge(D_8002EFB4, 0x20, 0x48, 4, 0, 0xBE, 0);
    jetpacInitLedge(D_8002EFE8, 0x78, 0x60, 2, 0, 0xBE, 0);
    jetpacInitLedge(D_8002F01C, 0, 0xB8, 0x1E, 0xBE, 0xBE, 0);
}
s32 jetpacCheckLedgeCollision(f32 x1, f32 y1, f32 x2, f32 y2, s32 isItem) {
    JetpacLedge *ledge = jetpacLedges;
    s32 i;

    for (i = 0; i < 4; i++, ledge++) {
        f32 fv0 = ledge->boxY2;
        if (isItem == 0) {
            fv0 -= 4.0f;
        }
        if (jetpacCheckAabbOverlapWrapped(x1, y1, x2, y2, ledge->boxX1, ledge->boxY1, ledge->boxX2, fv0)) {
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



extern void *D_8002DE68;
extern void *D_8002DE80;
extern void *D_8002DE98;
extern u8 D_8002EF90[];

void jetpacDrawLedges(void) {
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    JetpacLedge *l;

    for (i = 0; i < 4; i++) {
        x = (s32)jetpacGame.ledges[i].x;
        y = (s32)jetpacGame.ledges[i].y;
        l = &jetpacLedges[i];
        jetpacGridAddTiledSprite(&D_8002DE68, x, y, &D_8002EF90[i * 0x34], 0);
        x += 8;
        for (j = 0; j < l->unk30; j++) {
            jetpacGridAddTiledSprite(&D_8002DE80, x, y, D_8002EF90 + i * 0x34, 0);
            x += 8;
        }
        jetpacGridAddTiledSprite(&D_8002DE98, x, y, D_8002EF90 + i * 0x34, 0);
    }
}

