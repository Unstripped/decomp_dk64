#include "common.h"
#include "jetpac.h"
#include "proto/jetpac/0.h"
#include "proto/jetpac/1460.h"
#include "proto/jetpac/1A60.h"
#include "proto/jetpac/3060.h"
#include "proto/jetpac/3480.h"
#include "proto/jetpac/4FC0.h"
#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
extern JetpacSprite D_8002C4D0[];
extern JetpacSprite D_8002B9C0[];


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

s32 jetpacGetAnimFrame(JetpacPlayerActor *actor) {
    return (s32)(((s32)actor->x + actor->boxX1) / 2) % 4;
}

void jetpacSetFlying(JetpacPlayerActor *actor, s32 isFlying) {
    if (isFlying == 0 && actor->flying != 0) {
        actor->x = (f32)((s32)actor->x & 0xFFFE);
    } else if (isFlying != 0 && actor->flying == 0) {
        jetpacSnapActorToGrid(actor);
    }
    actor->boxX1 = 0;
    actor->boxX2 = 0x10;
    actor->flying = isFlying;
}

JetpacActor *jetpacFindFreeLaser(JetpacState *state) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (state->lasers[i].state == 0) {
            return &state->lasers[i];
        }
    }
    return NULL;
}

void jetpacResetActorState(JetpacActor *actor) {
    actor->state = 4;
    actor->timer = 0;
}

void jetpacUpdateLaser(JetpacActor *laser) {
    s32 pad1;
    f32 x1;
    f32 y1;
    f32 x2;
    f32 y2;
    s32 n;
    s32 step;
    s32 a;

    if (laser->state == 3 && (u32)laser->lifetime < (u32)laser->timer) {
        jetpacResetActorState(laser);
    }
    if (laser->state == 4 && laser->boxX2 == laser->boxX1) {
        laser->state = 0;
        laser->timer = 0;
    }
    if (laser->state != 0) {
        if (laser->state == 3) {
            n = laser->timer;
            if (laser->flip != 0) {
                x1 = (f32)laser->boxX1;
                step = n < 4 ? n : 4;
                x2 = (f32)(step * 8) + x1;
            } else {
                x2 = (f32)laser->boxX2;
                step = n < 4 ? n : 4;
                x1 = x2 - (f32)(step * 8);
            }
            y1 = (f32)laser->boxY1;
            y2 = (f32)laser->boxY2;
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
            if (laser->flip != 0) {
                laser->boxX1 = laser->boxX1 - 8;
                if (laser->timer >= 0xD) {
                    laser->boxX2 = laser->boxX2 - 8;
                }
            } else {
                laser->boxX2 = laser->boxX2 + 8;
                if (laser->timer >= 0xD) {
                    laser->boxX1 = laser->boxX1 + 8;
                }
            }
            laser->timer = laser->timer + 1;
            return;
        }
        if (laser->state == 4) {
            a = laser->boxX2 - laser->boxX1;
            if (laser->timer + a / 8 >= 0xD) {
                if (laser->flip != 0) {
                    laser->boxX2 = laser->boxX2 - 8;
                } else {
                    laser->boxX1 = laser->boxX1 + 8;
                }
            }
            laser->timer = laser->timer + 1;
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
    sub = laser->state;
    flip = laser->flip;
    frame = 0;
    if (sub >= 2) {
        y = laser->y;
        count = (laser->boxX2 - laser->boxX1) / 8;
        dir = -8;
        if (sub == 4) {
            frame = laser->timer;
        }
        if (flip != 0) {
            dir = 8;
            pos = laser->boxX1;
        } else {
            pos = laser->boxX2 - 8;
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



void jetpacFireLaser(player)
JetpacPlayerActor *player;
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
        p->flip = player->flip;
        if (p->flip != 0) {
            p->x = (f32)(((s32)(player->x + (f32)player->boxX1) / 8) * 8);
            p->vx = -8.0f;
        } else {
            p->x = (f32)(((s32)(player->x + (f32)player->boxX2 + 6.0f) / 8) * 8);
            p->vx = 8.0f;
        }
        ix = (s32)p->x;
        p->boxX1 = ix;
        p->boxX2 = ix;
        p->y = player->y + 10.0f;
        p->vy = 0.0f;
        iy = (s32)p->y;
        p->boxY2 = iy + 1;
        p->boxY1 = iy;
        col = (s32)(jetpacRandFloat() * 3.0f);
        p->color[0] = 0xFF;
        p->color[1] = 0xFF;
        if (col < 2) {
            p->color[col] = 0;
        }
        p->color[2] = 0xFF;
        p->color[3] = 1;
        p->state = 3;
        p->timer = 0;
        p->lifetime = (s32)(jetpacRandFloat() * 8.0f) + 13;
        p->update = jetpacUpdateLaser;
        p->sprite = 0;
        jetpacPlaySound(6);
    }
}




extern s32 D_8002EF74;

void jetpacUpdatePlayerMovement(JetpacPlayerActor *player) {
    JetpacPlayer *pData;
    f32 mx;
    f32 my;
    f32 vx;
    f32 vy;
    s32 btnA;
    s32 btnZLR;
    f32 px;
    s32 btnLeft;
    s32 btnRight;
    s32 idx;
    s32 u;

    s32 fire;

    pData = &jetpacGame.players[D_8002EF74];
    fire = jetpacGame.buttons & 0x4000;
    btnLeft = jetpacGame.buttons & 0x200;
    btnRight = jetpacGame.buttons & 0x100;
    btnA = jetpacGame.buttons & 0x8000;
    btnZLR = jetpacGame.buttons & 0x2030;
    if (fire && player->fireCooldown >= 5) {
        jetpacFireLaser(player, btnZLR, btnA);
        player->fireCooldown = 0;
    } else if (player->fireCooldown < 5) {
        player->fireCooldown++;
    }
    if (btnA != 0 && (player->flying == 0 || btnZLR == 0)) {
        jetpacSetFlying(player, 1);
        player->vy -= 0.2f;
        u = player->flying;
    } else if ((u = player->flying) != 0) {
        if (btnZLR != 0) {
            player->vy = 0.0f;
            u = (*(volatile s32 *)&player->flying); // FAKE: volatile forces reload
        } else {
            player->vy += 0.2;
            u = (*(volatile s32 *)&player->flying); // FAKE: volatile forces reload
        }
    }
    if (btnLeft != 0) {
        player->vx -= 0.33333334f;
        if (player->flip == 0 && player->vx <= 0.0f) {
            player->flip = 1;
            jetpacSetFlying(player, player->flying);
        }
        u = player->flying;
    } else if (btnRight != 0) {
        player->vx += 0.33333334f;
        if (player->flip != 0 && player->vx >= 0.0f) {
            player->flip = 0;
            jetpacSetFlying(player, player->flying);
        }
        u = player->flying;
    } else {
        vx = player->vx;
        if (vx > 0.0f) {
            player->vx = vx - 0.16666667f;
            u = player->flying;
        } else if (vx < 0.0f) {
            player->vx = vx + 0.16666667f;
            u = player->flying;
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
    if (player->flying != 0) {
        idx = jetpacCheckLedgeCollision(player->boxX1 + player->x + vx, player->boxY1 + player->y + player->vy,
                                        player->boxX2 + player->x + vx, player->boxY2 + player->y + player->vy, 1);
        if (idx >= 0) {
            if ((f32)jetpacGame.ledges[idx].boxY2 <= player->boxY1 + player->y) {
                player->vy *= -0.4f;
                if ((player->vy > 0.0f ? player->vy : -player->vy) <= 0.15f) {
                    player->vy = 0.0f;
                }
            } else if (player->boxY2 + player->y <= (f32)jetpacGame.ledges[idx].boxY1) {
                player->ledge = idx;
                player->vy = 0.0f;
                jetpacSetFlying(player, 0);
                player->y = jetpacGame.ledges[idx].y - 24.0f;
            } else {
                player->vx *= -0.5f;
            }
        }
    } else {
        idx = jetpacCheckLedgeEdge(player->ledge, (s32)(player->boxX1 + player->x + vx), (s32)(player->boxX2 + player->x + vx));
        switch (idx) {
        case -2:
        case 2:
            jetpacSetFlying(player, 1);
            player->vy = -0.5f;
            break;
        case -1:
        case 1:
            if (player->flip == 0 && btnLeft == 0) {
                player->vx = 1.0f;
            } else if (btnRight == 0) {
                player->vx = -1.0f;
            }
            break;
        }
    }
    player->x = player->x + player->vx;
    if (player->x + player->boxX2 > 256.0f) {
        player->x -= 256.0f;
    }
    if (player->x + player->boxX1 < 0.0f) {
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

void jetpacUpdatePlayerDeath(JetpacPlayerActor *player) {
    JetpacPlayer *p = &jetpacGame.players[jetpacGame.activePlayer];

    if (player->timer < 14) {
        player->timer++;
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
        if (*(s32 *)&D_8002F060[4] == 4 && jetpacPlayer.player.explosion.timer >= 8) { // FAKE: punned re-read of player.state forces a second load (plain D_8002F064 is CSE'd)
            draw = 0;
        }
        idx = jetpacGetAnimFrame(&jetpacPlayer.player);
        x = jetpacPlayer.player.x;
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
        if (jetpacPlayer.player.explosion.timer < 14) {
            jetpacUpdateExplosion(&jetpacPlayer.player.explosion);
        }
    }
}

void jetpacDrawLasers(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        jetpacDrawLaser(&jetpacPlayer.lasers[i]);
    }
}

void jetpacUpdateLasers(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        JetpacActor *a = &jetpacPlayer.lasers[i];

        if (a->update != NULL) {
            a->update(a);
        }
    }
}

extern s32 D_8002F064;

void jetpacPlayerStateUpdate(void) {
    if (!jetpacIsSpawnDelay()) {
        s32 state = D_8002F064;

        if (state == 1) {
            jetpacPlaySound(3);
            state = 3;
        }
        D_8002F064 = state;
        if (state == 3) {
            jetpacUpdatePlayerMovement(&jetpacPlayer.player);
        }
        state = D_8002F064;
        if (state == 4) {
            jetpacUpdatePlayerDeath(&jetpacPlayer.player);
        }
    }
}


extern JetpacActor D_8002C518;
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
    g->state = 1;
    g->timer = 0;
    g->flip = 0;
    g->explosion.timer = 14;
    g->explosion.color[0] = 0xFF;
    g->explosion.color[3] = 1;
    g->boxY1 = 0;
    g->boxX1 = 0;
    g->boxX2 = 0x10; g->boxY2 = 0x18;
    g->flying = 1;
    g->x = 126.0f;
    g->y = 160.0f;
    jetpacSetFlying(&jetpacPlayer.player, 0);
    jetpacPlayer.player.ledge = 3;
    D_8002F088 = 4;
    {
        s32 i;
        for (i = 0; i < 4; i++) {
            jetpacPlayer.lasers[i] = tmpl;
        }
    }
}

s32 jetpacIsSpawnDelay(void) {
    s32 ret = D_8002F064 == 1;

    if (ret) {
        return jetpacPlayer.player.timer < 180;
    }
}

void jetpacSnapActorToGrid(JetpacPlayerActor *actor) {
    if (actor->explosion.timer >= 0xE) {
        actor->explosion.timer = 0;
        actor->explosion.x = (s32)actor->x & 0xFFF8;
        actor->explosion.y = (s32)(actor->y + 7.0f);
    }
}
