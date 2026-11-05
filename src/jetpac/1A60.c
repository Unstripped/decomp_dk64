#include "common.h"
#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
typedef struct JetpacActor {
    f32 x;
    f32 y;
    f32 vx;
    f32 vy;
    u8 color[4];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    void (*unk48)(struct JetpacActor *);
    s32 unk4C;
} JetpacActor;
void jetpacSnapActorToGrid(JetpacActor *actor);
typedef struct JetpacState {
    u8 pad0[0x4C];
    JetpacActor actors[4];
} JetpacState;
typedef struct {
    u8 pad0[0x18];
} JetpacSprite;

extern JetpacSprite D_8002C4D0[];
extern JetpacSprite D_8002B9C0[];
f32 jetpacRandFloat(void);
void jetpacGridAddTiledSprite(JetpacSprite *, s32, s32, u8 *, s32);
typedef struct {
    s32 stage;
    s32 score;
    s32 lives;
    s32 unkC;
    u8 pad10[0x194 - 0x10];
} JetpacPlayer;

typedef struct {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x18];
    s32 unk20;
    u8 pad24[4];
    s32 unk28;
    u8 pad2C[8];
} J0a2Ledge;

typedef struct {
    f32 x;
    f32 y;
    f32 vx;
    f32 vy;
    u8 color[4];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    u8 pad34[0x44 - 0x34];
    s32 unk44;
    u8 tint[4];
} JetpacPlayerActor;

typedef struct {
    u32 unk0;
    u8 pad4[0x1C - 4];
    JetpacPlayer players[2];
    s32 currentSession;
    u8 pad348[0x350 - 0x348];
    J0a2Ledge ledges[4];
    JetpacPlayerActor player;
} JetpacGame;

extern JetpacGame jetpacGame;
void jetpacNextPlayerOrGameOver(JetpacPlayer *);
typedef struct {
    s32 x;
    s32 y;
    u8 pad8[3];
    u8 unkB;
    s32 unkC;
} JetpacCellItem;

typedef struct JetpacCell {
    JetpacCellItem items[6];
    s32 count;
    u8 color[4];
} JetpacCell;

extern JetpacCell jetpacGrid[24][32];


typedef struct {
    s32 x;
    s32 y;
    s32 timer;
    u8 color[4];
} JetpacExplosion;

void jetpacUpdateExplosion(JetpacExplosion *explosion) {
    volatile s32 frame; // FAKE: volatile forces stack home
    s32 timer;

    timer = explosion->timer;
    frame = (s32)(((f32)timer / 14.0f) * 6.0f);
    if ((timer % 7) == 0) {
        if (jetpacRandFloat() < 0.5) {
            explosion->color[1] = 0;
        } else {
            explosion->color[1] = 0xFF;
        }
        if (jetpacRandFloat() < 0.5) {
            explosion->color[2] = 0;
        } else {
            explosion->color[2] = 0xFF;
        }
    }
    jetpacGridAddTiledSprite(&D_8002B9C0[frame], explosion->x, explosion->y, explosion->color, 0);
    explosion->timer++;
}

s32 jetpacGetAnimFrame(JetpacActor *actor) {
    return (s32)(((s32)actor->x + actor->unk1C) / 2) % 4;
}

void jetpacSetFlying(JetpacActor *actor, s32 isFlying) {
    if (isFlying == 0 && actor->unk30 != 0) {
        actor->x = (f32)((s32)actor->x & 0xFFFE);
    } else if (isFlying != 0 && actor->unk30 == 0) {
        jetpacSnapActorToGrid(actor);
    }
    actor->unk1C = 0;
    actor->unk24 = 0x10;
    actor->unk30 = isFlying;
}

JetpacActor *jetpacFindFreeLaser(JetpacState *state) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (state->actors[i].unk14 == 0) {
            return &state->actors[i];
        }
    }
    return NULL;
}

void jetpacResetActorState(JetpacActor *actor) {
    actor->unk14 = 4;
    actor->unk2C = 0;
}
s32 jetpacBoxOverlapsItems(f32, f32, f32, f32);
s32 jetpacKillActorInBox(f32, f32, f32, f32);
s32 jetpacCheckLedgeCollision(f32, f32, f32, f32, s32);

void jetpacUpdateLaser(JetpacActor *laser) {
    s32 pad1;
    f32 x1;
    f32 y1;
    f32 x2;
    f32 y2;
    s32 n;
    s32 step;
    s32 a;

    if (laser->unk14 == 3 && (u32)laser->unk40 < (u32)laser->unk2C) {
        jetpacResetActorState(laser);
    }
    if (laser->unk14 == 4 && laser->unk24 == laser->unk1C) {
        laser->unk14 = 0;
        laser->unk2C = 0;
    }
    if (laser->unk14 != 0) {
        if (laser->unk14 == 3) {
            n = laser->unk2C;
            if (laser->unk18 != 0) {
                x1 = (f32)laser->unk1C;
                step = n < 4 ? n : 4;
                x2 = (f32)(step * 8) + x1;
            } else {
                x2 = (f32)laser->unk24;
                step = n < 4 ? n : 4;
                x1 = x2 - (f32)(step * 8);
            }
            y1 = (f32)laser->unk20;
            y2 = (f32)laser->unk28;
            if (jetpacKillActorInBox(x1, y1, x2, y2) != 0) {
                jetpacResetActorState(laser);
                return;
            }
            if (jetpacCheckLedgeCollision(x1, y1, x2, y2, 0) >= 0) {
                jetpacResetActorState(laser);
                return;
            }
            if (jetpacBoxOverlapsItems(x1, y1, x2, y2) != 0) {
                jetpacResetActorState(laser);
                return;
            }
            if (laser->unk18 != 0) {
                laser->unk1C = laser->unk1C - 8;
                if (laser->unk2C >= 0xD) {
                    laser->unk24 = laser->unk24 - 8;
                }
            } else {
                laser->unk24 = laser->unk24 + 8;
                if (laser->unk2C >= 0xD) {
                    laser->unk1C = laser->unk1C + 8;
                }
            }
            laser->unk2C = laser->unk2C + 1;
            return;
        }
        if (laser->unk14 == 4) {
            a = laser->unk24 - laser->unk1C;
            if (laser->unk2C + a / 8 >= 0xD) {
                if (laser->unk18 != 0) {
                    laser->unk24 = laser->unk24 - 8;
                } else {
                    laser->unk1C = laser->unk1C + 8;
                }
            }
            laser->unk2C = laser->unk2C + 1;
        }
    }
}

void jetpacDrawLaserSegment(s32 spriteIndex, s32 *pX, s32 stepX, s32 y, u8 *color, s32 flip) {
    jetpacGridAddTiledSprite(&D_8002C4D0[spriteIndex], *pX, y, color, flip);
    *pX += stepX;
    if (*pX < 0) {
        *pX += 0x100;
    }
}

void jetpacDrawLaser(JetpacActor *laser) {
    s32 pos;
    s32 dir;
    s32 frame;
    s32 sub;
    s32 count;
    s32 i;
    s32 y;
    s32 flip;

    dir = 0;
    sub = laser->unk14;
    flip = laser->unk18;
    frame = 0;
    if (sub >= 2) {
        y = laser->y;
        count = (laser->unk24 - laser->unk1C) / 8;
        dir = -8;
        if (sub == 4) {
            frame = laser->unk2C;
        }
        if (flip != 0) {
            dir = 8;
            pos = laser->unk1C;
        } else {
            pos = laser->unk24 - 8;
        }
        for (i = 0; i < count; i++) {
            s32 spr;

            if (frame < 4) {
                spr = 0;
            } else if (frame < 9) {
                spr = 1;
            } else {
                spr = 2;
            }
            jetpacDrawLaserSegment(spr, &pos, dir, y, laser->color, flip);
            frame++;
        }
    }
}


void jetpacPlaySound(s32);

void jetpacFireLaser(player)
JetpacActor *player;
{
    JetpacActor *p;
    s32 ix;
    s32 iy;
    s32 col;
    f32 vy;
    f32 absVy;

    p = jetpacFindFreeLaser((JetpacState *)player);
    if (p == NULL) {
        vy = player->vy;
        if (vy > 0.0f) {
            absVy = vy;
        } else {
            absVy = -vy;
        }
        if (absVy < 0.01f && player->y < 152.0f) {
            jetpacPlaySound(6);
        }
    } else {
        p->unk18 = player->unk18;
        if (p->unk18 != 0) {
            p->x = (f32)(((s32)(player->x + (f32)player->unk1C) / 8) * 8);
            p->vx = -8.0f;
        } else {
            p->x = (f32)(((s32)(player->x + (f32)player->unk24 + 6.0f) / 8) * 8);
            p->vx = 8.0f;
        }
        ix = (s32)p->x;
        p->unk1C = ix;
        p->unk24 = ix;
        p->y = player->y + 10.0f;
        p->vy = 0.0f;
        iy = (s32)p->y;
        p->unk28 = iy + 1;
        p->unk20 = iy;
        col = (s32)(jetpacRandFloat() * 3.0f);
        p->color[0] = 0xFF;
        p->color[1] = 0xFF;
        if (col < 2) {
            p->color[col] = 0;
        }
        p->color[2] = 0xFF;
        p->color[3] = 1;
        p->unk14 = 3;
        p->unk2C = 0;
        p->unk40 = (s32)(jetpacRandFloat() * 8.0f) + 13;
        p->unk48 = jetpacUpdateLaser;
        p->unk4C = 0;
        jetpacPlaySound(6);
    }
}




extern s32 D_8002EF74;
s32 jetpacCheckLedgeEdge(s32, s32, s32);
s32 jetpacIsOverRocket(f32);
void jetpacSetState(s32);

void jetpacUpdatePlayerMovement(JetpacActor *player) {
    JetpacPlayer *pData;
    f32 mx;
    f32 my;
    f32 vx;
    f32 vy;
    s32 a2;
    s32 a1;
    f32 px;
    s32 btnLeft;
    s32 btnRight;
    s32 idx;
    s32 u;

    s32 fire;

    pData = &jetpacGame.players[D_8002EF74];
    fire = jetpacGame.unk0 & 0x4000;
    btnLeft = jetpacGame.unk0 & 0x200;
    btnRight = jetpacGame.unk0 & 0x100;
    a2 = jetpacGame.unk0 & 0x8000;
    a1 = jetpacGame.unk0 & 0x2030;
    if (fire && player->unk38 >= 5) {
        jetpacFireLaser(player, a1, a2);
        player->unk38 = 0;
    } else if (player->unk38 < 5) {
        player->unk38++;
    }
    if (a2 != 0 && (player->unk30 == 0 || a1 == 0)) {
        jetpacSetFlying(player, 1);
        player->vy -= 0.2f;
        u = player->unk30;
    } else if ((u = player->unk30) != 0) {
        if (a1 != 0) {
            player->vy = 0.0f;
            u = (*(volatile s32 *)&player->unk30); // FAKE: volatile forces reload
        } else {
            player->vy += 0.2;
            u = (*(volatile s32 *)&player->unk30); // FAKE: volatile forces reload
        }
    }
    if (btnLeft != 0) {
        player->vx -= 0.33333334f;
        if (player->unk18 == 0 && player->vx <= 0.0f) {
            player->unk18 = 1;
            jetpacSetFlying(player, player->unk30);
        }
        u = player->unk30;
    } else if (btnRight != 0) {
        player->vx += 0.33333334f;
        if (player->unk18 != 0 && player->vx >= 0.0f) {
            player->unk18 = 0;
            jetpacSetFlying(player, player->unk30);
        }
        u = player->unk30;
    } else {
        vx = player->vx;
        if (vx > 0.0f) {
            player->vx = vx - 0.16666667f;
            u = (*(volatile s32 *)&player->unk30); // FAKE: volatile forces reload
        } else if (vx < 0.0f) {
            player->vx = vx + 0.16666667f;
            u = (*(volatile s32 *)&player->unk30); // FAKE: volatile forces reload
        }
    }
    if (u != 0) {
        mx = 2.0f;
        my = 2.0f;
    } else {
        mx = 1.0f;
        my = 0.0f;
    }
    vx = player->vx;
    player->vx = (vx < -mx) ? -mx : ((mx < vx) ? mx : vx);
    vy = player->vy;
    player->vy = (vy < -my) ? -my : ((my < vy) ? my : vy);
    if (player->vx < 0.1 && player->vx > -0.1) {
        player->vx = 0.0f;
    }
    if (player->vy < 0.1 && player->vy > -0.1) {
        player->vy = 0.0f;
    }
    vx = player->vx;
    if (player->unk30 != 0) {
        idx = jetpacCheckLedgeCollision(player->unk1C + player->x + vx, player->unk20 + player->y + player->vy,
                                        player->unk24 + player->x + vx, player->unk28 + player->y + player->vy, 1);
        if (idx >= 0) {
            if ((f32)jetpacGame.ledges[idx].unk28 <= player->unk20 + player->y) {
                player->vy *= -0.4f;
                if ((player->vy > 0.0f ? player->vy : -player->vy) <= 0.15f) {
                    player->vy = 0.0f;
                }
            } else if (player->unk28 + player->y <= (f32)jetpacGame.ledges[idx].unk20) {
                player->unk34 = idx;
                player->vy = 0.0f;
                jetpacSetFlying(player, 0);
                player->y = jetpacGame.ledges[idx].unk4 - 24.0f;
            } else {
                player->vx *= -0.5f;
            }
        }
    } else {
        idx = jetpacCheckLedgeEdge(player->unk34, (s32)(player->unk1C + player->x + vx), (s32)(player->unk24 + player->x + vx));
        switch (idx) {
        case -2:
        case 2:
            jetpacSetFlying(player, 1);
            player->vy = -0.5f;
            break;
        case -1:
        case 1:
            if (player->unk18 == 0 && btnLeft == 0) {
                player->vx = 1.0f;
            } else if (btnRight == 0) {
                player->vx = -1.0f;
            }
            break;
        }
    }
    player->x = player->x + player->vx;
    if (player->x + player->unk24 > 256.0f) {
        player->x -= 256.0f;
    }
    if (player->x + player->unk1C < 0.0f) {
        player->x += 256.0f;
    }
    player->y = player->y + player->vy;
    if (player->y < 18.0f) {
        player->y = 18.0f;
        player->vy = 0;
    }
    if (player->y > 168.0f) {
        player->y = 168.0f;
    }
    if (jetpacIsOverRocket(player->x) != 0 && pData->unkC == 8 && player->y > 152.0f) {
        jetpacSetState(4);
    }
}

void jetpacUpdatePlayerDeath(JetpacActor *player) {
    JetpacPlayer *p = &jetpacGame.players[jetpacGame.currentSession];

    if (player->unk2C < 14) {
        player->unk2C++;
    } else {
        p->lives--;
        jetpacNextPlayerOrGameOver(p);
    }
}

extern JetpacState jetpacPlayer;

extern f32 D_8002F054;
extern u8 D_8002F060[];
extern s32 D_8002F064;
extern s32 D_8002F068;
extern s32 D_8002F080;
extern JetpacExplosion D_8002F08C;
extern s32 D_8002F094;
extern JetpacSprite D_8002C330;
extern JetpacSprite D_8002C348[];
extern JetpacSprite D_8002C3A8[];

void jetpacDrawPlayer(void) {
    f32 x;
    f32 y;
    u8 *color;
    s32 pad;
    s32 idx;
    s32 draw;

    pad = 0;
    draw = 1;
    if (D_8002F064 >= 2) {
        if (*(s32 *)&D_8002F060[4] == 4 && D_8002F094 >= 8) {
            draw = 0;
        }
        idx = jetpacGetAnimFrame((JetpacActor *)&jetpacPlayer);
        x = *(f32 *)&jetpacPlayer;
        y = D_8002F054;
        if (draw != 0) {
            color = D_8002F060;
            if (D_8002F080 == 0) {
                x = (s16)(s32)x & 0xFFFE;
                jetpacGridAddTiledSprite(&D_8002C3A8[idx], (s32)x, (s32)y, color, D_8002F068);
            } else {
                jetpacGridAddTiledSprite(&D_8002C330, (s32)x, (s32)y, color, D_8002F068);
                if (D_8002F068 == 0) {
                    if (idx == 4) {
                        x -= 1.0f;
                    }
                    x -= 3.0f;
                } else {
                    if (idx == 4) {
                        x += 1.0f;
                    }
                    x += 10.0f;
                }
                jetpacGridAddTiledSprite(&D_8002C348[idx], (s32)x, (s32)(y + 18.0f), color, D_8002F068);
            }
        }
        if (D_8002F094 < 14) {
            jetpacUpdateExplosion(&D_8002F08C);
        }
    }
}

extern JetpacActor jetpacLasers[];
void jetpacDrawLaser(JetpacActor *);
void jetpacDrawLasers(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        jetpacDrawLaser(&jetpacLasers[i]);
    }
}

void jetpacUpdateLasers(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        JetpacActor *a = &jetpacPlayer.actors[i];

        if (a->unk48 != NULL) {
            a->unk48(a);
        }
    }
}

extern s32 D_8002F064;
void jetpacUpdatePlayerMovement(JetpacActor *);
s32 jetpacIsSpawnDelay(void);

void jetpacPlayerStateUpdate(void) {
    if (!jetpacIsSpawnDelay()) {
        s32 state = D_8002F064;

        if (state == 1) {
            jetpacPlaySound(3);
            state = 3;
        }
        D_8002F064 = state;
        if (state == 3) {
            jetpacUpdatePlayerMovement((JetpacActor *)&jetpacPlayer);
        }
        state = D_8002F064;
        if (state == 4) {
            jetpacUpdatePlayerDeath((JetpacActor *)&jetpacPlayer);
        }
    }
}


extern JetpacActor D_8002C518;
extern s32 D_8002F084;
extern s32 D_8002F088;

void jetpacInitPlayer(void) {
    JetpacPlayerActor *g = &jetpacGame.player;
    JetpacActor tmpl;

    tmpl = D_8002C518;
    g->vx = 0.0f;
    g->vy = 0.0f;
    g->color[0] = 0xFF;
    g->color[1] = 0xFF;
    g->color[2] = 0xFF;
    g->color[3] = 1;
    g->unk14 = 1;
    g->unk2C = 0;
    g->unk18 = 0;
    g->unk44 = 14;
    g->tint[0] = 0xFF;
    g->tint[3] = 1;
    g->unk20 = 0;
    g->unk1C = 0;
    g->unk24 = 0x10; g->unk28 = 0x18;
    g->unk30 = 1;
    g->x = 126.0f;
    g->y = 160.0f;
    jetpacSetFlying((JetpacActor *)&jetpacPlayer, 0);
    D_8002F084 = 3;
    D_8002F088 = 4;
    {
        s32 i;
        for (i = 0; i < 4; i++) {
            jetpacLasers[i] = tmpl;
        }
    }
}

extern s32 D_8002F07C;
s32 jetpacIsSpawnDelay(void) {
    s32 ret = D_8002F064 == 1;

    if (ret) {
        return D_8002F07C < 180;
    }
}

void jetpacSnapActorToGrid(JetpacActor *actor) {
    if (actor->unk44 >= 0xE) {
        actor->unk44 = 0;
        actor->unk3C = (s32)actor->x & 0xFFF8;
        actor->unk40 = (s32)(actor->y + 7.0f);
    }
}
