#include "common.h"
#include "jetpac.h"
#include "proto/jetpac/0_game.h"
#include "proto/jetpac/1460_sprite_grid.h"
#include "proto/jetpac/1A60_player.h"
#include "proto/jetpac/3060_collision_utils.h"
#include "proto/jetpac/3480_rocket_items.h"
#include "proto/jetpac/4FC0_enemies.h"
extern TextureDescriptor jetpacExplosionSprites[];

// .data 0x8002BA80-0x8002C570 (sprite pixel layout: see 0.c).
Gfx D_8002BA80[1] = { gsSPEndDisplayList() };
u8 jetpacPlayerFlyPixels[0x188] = {
#include "jetpac/jetpacPlayerFlyPixels.inc.c"
};
u8 jetpacPlayerExhaustPixels[0x108] = {
#include "jetpac/jetpacPlayerExhaustPixels.inc.c"
};
u8 D_8002BD18[0x188] = {
#include "jetpac/D_8002BD18.inc.c"
};
u8 D_8002BEA0[0x188] = {
#include "jetpac/D_8002BEA0.inc.c"
};
u8 D_8002C028[0x188] = {
#include "jetpac/D_8002C028.inc.c"
};
u8 D_8002C1B0[0x180] = {
#include "jetpac/D_8002C1B0.inc.c"
};
TextureDescriptor jetpacPlayerFlySprite = { jetpacPlayerFlyPixels, 0, 16, 16, 24, 4, 1, 0, 0, 0 };
TextureDescriptor jetpacPlayerExhaustSprites[4] = {
    { jetpacPlayerExhaustPixels, 0, 8, 8, 8, 4, 1, 0, 0, 0 },
    { jetpacPlayerExhaustPixels, 0, 8, 8, 8, 4, 1, 0, 8, 0 },
    { jetpacPlayerExhaustPixels, 0, 8, 8, 8, 4, 1, 0, 16, 0 },
    { jetpacPlayerExhaustPixels, 0, 8, 8, 8, 4, 1, 0, 24, 0 },
};
TextureDescriptor jetpacPlayerWalkSprites[4] = {
    { D_8002BD18, 0, 16, 16, 24, 4, 1, 0, 0, 0 },
    { D_8002BEA0, 0, 16, 16, 24, 4, 1, 0, 0, 0 },
    { D_8002C028, 0, 16, 16, 24, 4, 1, 0, 0, 0 },
    { D_8002C1B0, 0, 16, 16, 24, 4, 1, 0, 0, 0 },
};
Gfx D_8002C408[1] = { gsSPEndDisplayList() };
u8 jetpacLaserPixels[0xC0] = {
#include "jetpac/jetpacLaserPixels.inc.c"
};
TextureDescriptor jetpacLaserSprites[3] = {
    { jetpacLaserPixels, 0, 24, 8, 8, 4, 1, 16, 0, 0 },
    { jetpacLaserPixels, 0, 24, 8, 8, 4, 1, 8, 0, 0 },
    { jetpacLaserPixels, 0, 24, 8, 8, 4, 1, 0, 0, 0 },
};
// Idle laser template: jetpacInitPlayer copies it into every laser.
JetpacActor jetpacLaserTemplate = {
    0.0f, 0.0f, 0.0f, 0.0f, { 255, 255, 255, 1 }, 0, 0, 0, 0, 0, 0, 0, { 0, 0, 14, { 255, 255, 255, 1 } }, 0, 0, NULL, NULL,
};

void jetpacUpdateExplosion(JetpacExplosion *explosion) {
    s32 frame;

    frame = (s32)(((f32)explosion->timer / 14.0f) * 6.0f);
    if ((explosion->timer % 7) == 0) {
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
    jetpacGridAddTiledSprite(&jetpacExplosionSprites[frame], explosion->x, explosion->y, explosion->color, 0);
    explosion->timer++;
}

s32 jetpacGetAnimFrame(JetpacPlayerActor *actor) {
    return (((s32)actor->head.x + actor->head.boxX1) / 2) % 4;
}

void jetpacSetFlying(JetpacPlayerActor *actor, s32 isFlying) {
    if (isFlying == 0 && actor->flying != 0) {
        actor->head.x = (f32)((s32)actor->head.x & 0xFFFE);
    } else if (isFlying != 0 && actor->flying == 0) {
        jetpacSnapActorToGrid(actor);
    }
    actor->head.boxX1 = 0;
    actor->head.boxX2 = 0x10;
    actor->flying = isFlying;
}

JetpacActor *jetpacFindFreeLaser(JetpacState *state) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (state->lasers[i].head.state == 0) {
            return &state->lasers[i];
        }
    }
    return NULL;
}

void jetpacResetActorState(JetpacActor *actor) {
    actor->head.state = 4;
    actor->head.timer = 0;
}

void jetpacUpdateLaser(JetpacActor *laser) {
    s32 pad;
    f32 x1;
    f32 y1;
    f32 x2;
    f32 y2;
    s32 step;
    s32 width;

    if (laser->head.state == 3 && laser->lifetime < laser->head.timer) {
        jetpacResetActorState(laser);
    }
    if (laser->head.state == 4 && laser->head.boxX2 == laser->head.boxX1) {
        laser->head.state = 0;
        laser->head.timer = 0;
    }
    if (laser->head.state != 0) {
        if (laser->head.state == 3) {
            if (laser->head.flip != 0) {
                x1 = (f32)laser->head.boxX1;
                step = laser->head.timer < 4 ? laser->head.timer : 4;
                x2 = (f32)(step * 8) + x1;
            } else {
                x2 = (f32)laser->head.boxX2;
                step = laser->head.timer < 4 ? laser->head.timer : 4;
                x1 = x2 - (f32)(step * 8);
            }
            y1 = (f32)laser->head.boxY1;
            y2 = (f32)laser->head.boxY2;
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
            if (laser->head.flip != 0) {
                laser->head.boxX1 -= 8;
                if (laser->head.timer >= 0xD) {
                    laser->head.boxX2 -= 8;
                }
            } else {
                laser->head.boxX2 += 8;
                if (laser->head.timer >= 0xD) {
                    laser->head.boxX1 += 8;
                }
            }
            laser->head.timer++;
            return;
        }
        if (laser->head.state == 4) {
            width = laser->head.boxX2 - laser->head.boxX1;
            if (laser->head.timer + width / 8 >= 0xD) {
                if (laser->head.flip != 0) {
                    laser->head.boxX2 -= 8;
                } else {
                    laser->head.boxX1 += 8;
                }
            }
            laser->head.timer++;
        }
    }
}

void jetpacDrawLaserSegment(s32 spriteIndex, s32 *pX, s32 stepX, s32 y, u8 *color, s32 flip) {
    jetpacGridAddTiledSprite(&jetpacLaserSprites[spriteIndex], *pX, y, color, flip);
    *pX += stepX;
    if (*pX < 0) {
        *pX += 0x100;
    }
}

void jetpacDrawLaser(JetpacActor *laser) {
    s32 pos;
    s32 dir;
    s32 frame;
    s32 state;
    s32 count;
    s32 i;
    s32 y;
    s32 flip;

    state = laser->head.state;
    flip = laser->head.flip;
    frame = 0;
    if (state >= 2) {
        y = laser->head.y;
        count = (laser->head.boxX2 - laser->head.boxX1) / 8;
        if (state == 4) {
            frame = laser->head.timer;
        }
        if (flip != 0) {
            dir = 8;
            pos = laser->head.boxX1;
        } else {
            dir = -8;
            pos = laser->head.boxX2 - 8;
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
            jetpacDrawLaserSegment(spr, &pos, dir, y, laser->head.color, flip);
            frame++;
        }
    }
}

void jetpacFireLaser(JetpacPlayerActor *player) {
    JetpacActor *laser;
    s32 ix;
    s32 iy;
    s32 col;
    f32 vy;
    f32 absVy;

    laser = jetpacFindFreeLaser((JetpacState *)player);
    if (laser == NULL) {
        vy = player->head.vy;
        if (vy > 0.0f) {
            absVy = vy;
        } else {
            absVy = -vy;
        }
        if (absVy < 0.01f && player->head.y < 152.0f) {
            jetpacPlaySound(6);
        }
    } else {
        laser->head.flip = player->head.flip;
        if (laser->head.flip != 0) {
            laser->head.x = (f32)(((s32)(player->head.x + (f32)player->head.boxX1) / 8) * 8);
            laser->head.vx = -8.0f;
        } else {
            laser->head.x = (f32)(((s32)(player->head.x + (f32)player->head.boxX2 + 6.0f) / 8) * 8);
            laser->head.vx = 8.0f;
        }
        ix = (s32)laser->head.x;
        laser->head.boxX1 = ix;
        laser->head.boxX2 = ix;
        laser->head.y = player->head.y + 10.0f;
        laser->head.vy = 0.0f;
        iy = (s32)laser->head.y;
        laser->head.boxY2 = iy + 1;
        laser->head.boxY1 = iy;
        col = (s32)(jetpacRandFloat() * 3.0f);
        laser->head.color[0] = 0xFF;
        laser->head.color[1] = 0xFF;
        if (col < 2) {
            laser->head.color[col] = 0;
        }
        laser->head.color[2] = 0xFF;
        laser->head.color[3] = 1;
        laser->head.state = 3;
        laser->head.timer = 0;
        laser->lifetime = (s32)(jetpacRandFloat() * 8.0f) + 13;
        laser->update = jetpacUpdateLaser;
        laser->sprite = NULL;
        jetpacPlaySound(6);
    }
}

void jetpacUpdatePlayerMovement(JetpacPlayerActor *player) {
    JetpacPlayer *pData;
    f32 mx;
    f32 my;
    f32 vx;
    f32 vy;
    s32 btnA;
    s32 btnZLR;
    JetpacHead *head = &player->head;
    s32 btnLeft;
    s32 btnRight;
    s32 idx;
    s32 edge;
    s32 flying;
    s32 fire;

    pData = &jetpacGame.players[jetpacGame.activePlayer];
    fire = jetpacGame.buttons & 0x4000;
    btnLeft = jetpacGame.buttons & 0x200;
    btnRight = jetpacGame.buttons & 0x100;
    btnA = jetpacGame.buttons & 0x8000;
    btnZLR = jetpacGame.buttons & 0x2030;
    if (fire && player->fireCooldown >= 5) {
        jetpacFireLaser(player);
        player->fireCooldown = 0;
    } else if (player->fireCooldown < 5) {
        player->fireCooldown++;
    }
    if (btnA != 0 && (player->flying == 0 || btnZLR == 0)) {
        jetpacSetFlying(player, 1);
        head->vy -= 0.2f;
        flying = player->flying;
    } else if ((flying = player->flying) != 0) {
        if (btnZLR != 0) {
            head->vy = 0.0f;
            flying = player->flying;
        } else {
            head->vy += 0.2;
            flying = player->flying;
        }
    }
    if (btnLeft != 0) {
        head->vx -= 0.33333334f;
        if (head->flip == 0 && head->vx <= 0.0f) {
            head->flip = 1;
            jetpacSetFlying(player, player->flying);
        }
        flying = player->flying; // ORIG: the target reloads flying after each head update, one lw v0,48(s0) per refresh: here 0xa40 (0xa30 on the no-call path), btnRight 0xa9c (0xa8c), vx>0 0xac8, vx<0 0xaf8, flying arms 0x9c4/0x9e0
    } else if (btnRight != 0) {
        head->vx += 0.33333334f;
        if (head->flip != 0 && head->vx >= 0.0f) {
            head->flip = 0;
            jetpacSetFlying(player, player->flying);
        }
        flying = player->flying;
    } else {
        vx = head->vx;
        if (vx > 0.0f) {
            head->vx = vx - 0.16666667f;
            flying = player->flying;
        } else if (vx < 0.0f) {
            head->vx = vx + 0.16666667f;
            flying = player->flying;
        }
    }
    if (flying != 0) {
        mx = 2.0f;
        my = 2.0f;
    } else {
        mx = 1.0f;
        my = 0.0f;
    }
    vx = head->vx;
    head->vx = (vx < -mx) ? -mx : ((mx < vx) ? mx : vx);
    vy = head->vy;
    head->vy = (vy < -my) ? -my : ((my < vy) ? my : vy);
    if (head->vx < 0.1 && head->vx > -0.1) {
        head->vx = 0.0f;
    }
    if (head->vy < 0.1 && head->vy > -0.1) {
        head->vy = 0.0f;
    }
    vx = head->vx;
    if (player->flying != 0) {
        idx = jetpacCheckLedgeCollision(head->boxX1 + head->x + vx, head->boxY1 + head->y + head->vy,
                                        head->boxX2 + head->x + vx, head->boxY2 + head->y + head->vy, 1);
        if (idx >= 0) {
            if (jetpacGame.ledges[idx].boxY2 <= head->boxY1 + head->y) {
                head->vy *= -0.4f;
                if ((head->vy > 0.0f ? head->vy : -head->vy) <= 0.15f) {
                    head->vy = 0.0f;
                }
            } else if (head->boxY2 + head->y <= jetpacGame.ledges[idx].boxY1) {
                player->ledge = idx;
                head->vy = 0.0f;
                jetpacSetFlying(player, 0);
                head->y = jetpacGame.ledges[idx].y - 24.0f;
            } else {
                head->vx *= -0.5f;
            }
        }
    } else {
        edge = jetpacCheckLedgeEdge(player->ledge, head->boxX1 + head->x + vx, head->boxX2 + head->x + vx);
        switch (edge) {
        case -2:
        case 2:
            jetpacSetFlying(player, 1);
            head->vy = -0.5f;
            break;
        case -1:
        case 1:
            if (head->flip == 0 && btnLeft == 0) {
                head->vx = 1.0f;
            } else if (btnRight == 0) {
                head->vx = -1.0f;
            }
            break;
        }
    }
    head->x += head->vx;
    if (head->x + head->boxX2 > 256.0f) {
        head->x -= 256.0f;
    }
    if (head->x + head->boxX1 < 0.0f) {
        head->x += 256.0f;
    }
    head->y += head->vy;
    if (head->y < 18.0f) {
        head->y = 18.0f;
        head->vy = 0;
    }
    if (head->y > 168.0f) {
        head->y = 168.0f;
    }
    if (jetpacIsOverRocket(head->x) != 0 && pData->rocketProgress == 8 && head->y > 152.0f) {
        jetpacSetState(4);
    }
}

void jetpacUpdatePlayerDeath(JetpacPlayerActor *player) {
    JetpacPlayer *p = &jetpacGame.players[jetpacGame.activePlayer];

    if (player->head.timer < 14) {
        player->head.timer++;
    } else {
        p->lives--;
        jetpacNextPlayerOrGameOver(p);
    }
}

extern JetpacState jetpacPlayer;

void jetpacDrawPlayer(void) {
    f32 x;
    f32 y;
    u8 *color;
    s32 pad;
    s32 frame;
    s32 draw;
    JetpacPlayerActor *player;

    player = &jetpacPlayer.player;
    draw = 1;
    if (jetpacGame.player.head.state >= 2) {
        if (player->head.state == 4 && player->explosion.timer >= 8) {
            draw = 0;
        }
        frame = jetpacGetAnimFrame(player);
        x = player->head.x;
        y = jetpacPlayer.player.head.y;
        if (draw != 0) {
            color = jetpacPlayer.player.head.color;
            if (player->flying == 0) {
                x = (s16)x & 0xFFFE;
                jetpacGridAddTiledSprite(&jetpacPlayerWalkSprites[frame], x, y, color, jetpacGame.player.head.flip);
            } else {
                jetpacGridAddTiledSprite(&jetpacPlayerFlySprite, x, y, color, jetpacGame.player.head.flip);
                if (jetpacGame.player.head.flip == 0) {
                    if (frame == 4) {
                        x -= 1.0f;
                    }
                    x -= 3.0f;
                } else {
                    if (frame == 4) {
                        x += 1.0f;
                    }
                    x += 10.0f;
                }
                jetpacGridAddTiledSprite(&jetpacPlayerExhaustSprites[frame], x, y + 18.0f, color, jetpacGame.player.head.flip);
            }
        }
        if (player->explosion.timer < 14) {
            jetpacUpdateExplosion(&player->explosion);
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
        JetpacActor *laser = &jetpacPlayer.lasers[i];

        if (laser->update != NULL) {
            laser->update(laser);
        }
    }
}

void jetpacPlayerStateUpdate(void) {
    if (!jetpacIsSpawnDelay()) {
        s32 state = jetpacGame.player.head.state;

        if (state == 1) {
            jetpacPlaySound(3);
            state = 3;
        }
        jetpacGame.player.head.state = state;
        if (state == 3) {
            jetpacUpdatePlayerMovement(&jetpacPlayer.player);
        }
        state = jetpacGame.player.head.state;
        if (state == 4) {
            jetpacUpdatePlayerDeath(&jetpacPlayer.player);
        }
    }
}

void jetpacInitPlayer(void) {
    JetpacPlayerActor *player = &jetpacGame.player;
    JetpacActor tmpl;

    tmpl = jetpacLaserTemplate;
    player->head.vx = 0.0f;
    player->head.vy = 0.0f;
    player->head.color[0] = 0xFF;
    player->head.color[1] = 0xFF;
    player->head.color[2] = 0xFF;
    player->head.color[3] = 1;
    player->head.state = 1;
    player->head.timer = 0;
    player->head.flip = 0;
    player->explosion.timer = 14;
    player->explosion.color[0] = 0xFF;
    player->explosion.color[3] = 1;
    player->head.boxY1 = 0;
    player->head.boxX1 = 0;
    player->head.boxX2 = 0x10; player->head.boxY2 = 0x18; // LAYOUT: one line makes as1 store boxY2 (0x28) before boxX2 (0x24)
    player->flying = 1;
    player->head.x = 126.0f;
    player->head.y = 160.0f;
    jetpacSetFlying(player, 0);
    player->ledge = 3;
    player->fireCooldown = 4;
    {
        s32 i;
        for (i = 0; i < 4; i++) {
            jetpacPlayer.lasers[i] = tmpl;
        }
    }
}

s32 jetpacIsSpawnDelay(void) {
    s32 ret = jetpacGame.player.head.state == 1;

    if (ret) {
        return jetpacPlayer.player.head.timer < 180;
    }
}

void jetpacSnapActorToGrid(JetpacPlayerActor *actor) {
    if (actor->explosion.timer >= 0xE) {
        actor->explosion.timer = 0;
        actor->explosion.x = (s32)actor->head.x & 0xFFF8;
        actor->explosion.y = (s32)(actor->head.y + 7.0f);
    }
}
