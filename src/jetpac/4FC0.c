#include "common.h"
#include "jetpac.h"
#include "proto/global/100180.h"
#include "proto/jetpac/0.h"
#include "proto/jetpac/1460.h"
#include "proto/jetpac/1A60.h"
#include "proto/jetpac/3060.h"
#include "proto/jetpac/3480.h"
#include "proto/jetpac/4FC0.h"
#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
extern JetpacSprite D_8002E800[];
extern JetpacSprite D_8002E848[];
extern JetpacSprite D_8002E890;
extern JetpacSprite D_8002E8C0;
extern JetpacSprite D_8002E8D8;
extern JetpacSprite D_8002E830;
extern JetpacSprite D_8002E8A8;
extern s32 D_8002BA6C;
extern JetpacSprite D_8002E878;
extern f32 D_8002F054;
extern s32 D_8002F078;
extern JetpacActor jetpacActors[];
extern JetpacActor D_8002E964;
extern JetpacActor D_8002E914;
extern s32 D_8002E8F0;
extern u8 D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3;
extern u8 D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC;

JetpacActor *jetpacFindFreeActor(void) {
    JetpacActor *actor = jetpacActors;
    s32 i = 0;

    do {
        if (actor->state == 0) {
            return actor;
        }
        actor++;
    } while (++i < 6);
    return NULL;
}

extern s32 D_8002F064;
extern s32 D_8002F07C;
extern JetpacPlayerActor jetpacPlayer;

s32 jetpacCheckPlayerHit(JetpacActor *actor) {
    s32 pad[7];
    f32 px2;
    f32 py2;
    s32 ret;
    JetpacPlayerActor *player;
    f32 ax;
    f32 ay;
    f32 x2;
    f32 y2;
    f32 px;
    f32 py;

    player = &jetpacGame.player;
    ax = actor->x;
    ay = actor->y;
    px = player->x;
    py = player->y;
    x2 = (f32)actor->boxX2 + ax;
    y2 = (f32)actor->boxY2 + ay;
    px2 = (f32)player->boxX2 + px - 2.0f;
    py2 = (f32)player->boxY2 + py;
    ret = 0;
    ax += (f32)actor->boxX1;
    ay += (f32)actor->boxY1;
    px += (f32)(player->boxX1 + 2);
    py += (f32)(player->boxY1 + 4);
    if (player->state == 3) {
        ret = jetpacCheckAabbOverlapWrapped(ax, ay, x2, y2, px, py, px2, py2);
    }
    if (ret != 0) {
        D_8002F064 = 4;
        D_8002F07C = 0;
        jetpacSnapActorToGrid(&jetpacPlayer);
        jetpacActorExplode(actor);
    }
    return ret;
}

void jetpacActorExplode(JetpacActor *actor) {
    actor->state = 4;
    actor->timer = 0;
    actor->explosion.timer = 0;
    actor->explosion.x = (s32)actor->x & 0xFFF8;
    actor->explosion.y = (s32)actor->y & 0xFFF8;
    jetpacPlaySound(5);
}

void jetpacDrawActor(JetpacActor *actor) {
    s32 status = actor->state;

    if (status == 3) {
        jetpacGridAddTiledSprite(actor->sprite, (s32)actor->x, (s32)actor->y, actor->color, actor->flip);
        return;
    }
    if (status == 4) {
        jetpacUpdateExplosion(&actor->explosion);
        if (actor->explosion.timer < 7) {
            jetpacGridAddTiledSprite(actor->sprite, (s32)actor->x, (s32)actor->y, actor->color, actor->flip);
        }
    }
}

JetpacActor *jetpacAllocActor(void) {
    s32 pad;
    JetpacActor *actor;
    JetpacActor templateActor;

    actor = jetpacFindFreeActor();
    templateActor = D_8002E914; // FAKE: template copied before the NULL check (block order)
    if (actor == NULL) {
        return NULL;
    }
    *actor = templateActor;
    actor->x = 0.0f;
    actor->y = (f32)((((s32)(jetpacRandFloat() * 15.0f) % 15) * 8) + 32);
    switch ((s32)(jetpacRandFloat() * 4.0f) % 4) {
    case 0:
        actor->color[0] = 0;
        break;
    case 1:
        actor->color[1] = 0;
        break;
    case 2:
        actor->color[0] = 0;
        actor->color[2] = 0;
        break;
    case 3:
        actor->color[1] = 0;
        actor->color[2] = 0;
        break;
    }
    return actor;
}

extern void (*D_8002E8F4[])(JetpacActor *);

void jetpacSpawnActor(void) {
    s32 pad[2];
    void (*fn)(JetpacActor *);
    JetpacActor *actor;
    JetpacPlayer *playerData;
    s32 idx;

    playerData = &jetpacGame.players[jetpacGame.activePlayer];
    idx = playerData->stage;
    fn = D_8002E8F4[idx % 8];
    actor = jetpacAllocActor();
    if (actor != NULL) {
        fn(actor);
        actor->state = 3;
    }
}

void jetpacBounceOffLedge(JetpacActor *actor, s32 ledgeIndex) {
    JetpacLedge *ledge;
    f32 ax1;
    f32 ax2;
    f32 ay1;
    f32 lx1;
    f32 lx2;
    f32 ay2;
    f32 ly1;
    f32 ly2;

    ledge = &jetpacGame.ledges[ledgeIndex];
    ax1 = actor->x + (f32)actor->boxX1;
    ax2 = actor->x + (f32)actor->boxX2;
    lx1 = ledge->boxX1;
    lx2 = ledge->boxX2;
    ay1 = actor->y + (f32)actor->boxY1;
    ay2 = actor->y + (f32)actor->boxY2;
    ly1 = ledge->boxY1;
    ly2 = ledge->boxY2;
    if ((lx2 <= ax1 && lx2 <= ax2) || (ax2 <= lx1 && ax1 <= lx1)) {
        actor->vx = -actor->vx;
    }
    if ((ly2 <= ay1 && ly2 <= ay2) || (ay2 <= ly1 && ay1 <= ly1)) {
        actor->vy = -actor->vy;
    }
}

void jetpacActorInitStraight(JetpacActor *actor, f32 a1, f32 a2) {
    s32 diagonalCount;
    s32 levelCount;
    s32 i;
    JetpacActor *other;

    diagonalCount = levelCount = 0;
    actor->points = 0x19;
    if (actor->y < 88.0f) {
        actor->vx = a1;
        actor->flip = 0;
    } else {
        actor->vx = -a1;
        actor->flip = 1;
    }
    other = jetpacActors;
    for (i = 0; i != 6; i++) {
        if (other->state > 0) {
            if (other->vy == 0.0f) {
                levelCount++;
            } else {
                diagonalCount++;
            }
        }
        other++;
    }
    if (levelCount == 3) {
        actor->vy = a2;
    } else if (diagonalCount == 3) {
        actor->vy = 0.0f;
    } else {
        if ((s32)(jetpacRandFloat() * 2) % 2) {
            actor->vy = 0.0f;
        } else {
            actor->vy = a2;
        }
    }
}

void jetpacActorUpdateStraight(JetpacActor *actor) {
    switch (actor->state) {
    case 3:
        if (jetpacCheckLedgeCollision((f32)actor->boxX1 + actor->x + actor->vx,
                          (f32)actor->boxY1 + actor->y + actor->vy,
                          (f32)actor->boxX2 + actor->x + actor->vx,
                          (f32)actor->boxY2 + actor->y + actor->vy, 1) >= 0) {
            jetpacActorExplode(actor);
        } else if (jetpacCheckPlayerHit(actor) == 0) {
            actor->x += actor->vx;
            actor->y += actor->vy;
        }
        break;
    case 4:
        actor->timer++;
        if (actor->timer >= 15) {
            actor->state = 0;
        }
        break;
    }
}

void jetpacActorInitMeteor(JetpacActor *actor) {
    actor->boxY2 = 0xB;
    jetpacActorInitStraight(actor, 1.6f, 0.5f);
    actor->update = jetpacActorUpdateMeteor;
}

void jetpacActorUpdateMeteor(JetpacActor *actor) {
    jetpacActorUpdateStraight(actor);
    actor->sprite = &D_8002E800[(s32)actor->x % 2];
}

void jetpacActorInitBounce(JetpacActor *actor) {
    actor->update = jetpacActorUpdateBounce;
    actor->points = 0x50;
    if (actor->y < 88.0f) {
        actor->vx = -1.2f;
    } else {
        actor->vx = 1.2f;
    }
    actor->vy = -0.8f;
    actor->sprite = &D_8002E830;
}

void jetpacActorUpdateBounce(JetpacActor *actor) {
    s32 res;

    switch (actor->state) {
    case 3:
        res = jetpacCheckLedgeCollision((f32)actor->boxX1 + actor->x + actor->vx,
                            (f32)actor->boxY1 + actor->y + actor->vy,
                            (f32)actor->boxX2 + actor->x + actor->vx,
                            (f32)actor->boxY2 + actor->y + actor->vy, 1);
        if (res >= 0) {
            jetpacBounceOffLedge(actor, res);
        }
        if (jetpacCheckPlayerHit(actor) == 0) {
            if ((actor->y + actor->vy) < 24.0f) {
                actor->vy = -actor->vy;
            }
            actor->y += actor->vy;
            actor->x += actor->vx;
            if ((s32)actor->x & 2) {
                actor->flip ^= 1;
            }
        }
        break;
    case 4:
        actor->timer++;
        if (actor->timer >= 15) {
            actor->state = 0;
        }
        break;
    }
}

void jetpacActorInitWander(JetpacActor *actor) {
    actor->update = jetpacActorUpdateWander;
    actor->points = 0x28;
    if (actor->y < 88.0f) {
        actor->vx = -1.2f;
    } else {
        actor->vx = 1.2f;
    }
    jetpacActorPickWanderDirection(actor);
    actor->timer = jetpacRandFloat() * 60.0f + 10.0f;
}

void jetpacActorPickWanderDirection(JetpacActor *actor) {
    if ((f64)actor->vy == 0.0) {
        if ((f64)jetpacRandFloat() < 0.5) {
            actor->vy = -0.6f;
            return;
        }
        actor->vy = 0.6f;
        return;
    }
    actor->vy = 0.0f;
}

void jetpacActorUpdateWander(JetpacActor *actor) {
    s32 res;

    switch (actor->state) {
    case 3:
        if (--actor->timer == 0) {
            jetpacActorPickWanderDirection(actor);
            actor->timer = jetpacRandFloat() * 60.0f + 10.0f;
        }
        res = jetpacCheckLedgeCollision((f32)actor->boxX1 + actor->x + actor->vx,
                            (f32)actor->boxY1 + actor->y + actor->vy,
                            (f32)actor->boxX2 + actor->x + actor->vx,
                            (f32)actor->boxY2 + actor->y + actor->vy, 1);
        if (res >= 0) {
            jetpacBounceOffLedge(actor, res);
            if (actor->timer < 10) {
                actor->timer = 10;
            }
        }
        if (jetpacCheckPlayerHit(actor) == 0) {
            if ((actor->y + actor->vy) < 24.0f) {
                actor->vy = -actor->vy;
            }
            actor->y += actor->vy;
            actor->x += actor->vx;
            actor->sprite = &D_8002E848[(s32)(actor->x / 4) % 2];
        }
        break;
    case 4:
        actor->timer++;
        if (actor->timer >= 15) {
            actor->state = 0;
        }
        break;
    }
}

void jetpacActorInitFighter(JetpacActor *actor) {
    actor->update = jetpacActorUpdateFighter;
    actor->points = 0x37;
    actor->timer = jetpacRandFloat() * 60.0f + 10.0f;
    actor->lifetime = (jetpacRandFloat() * 180.0f) + 10.0f;
    actor->boxY2 = 8;
    if (actor->y < 88.0f) {
        actor->flip = 0;
    } else {
        actor->flip = 1;
    }
    actor->vx = 0.0f;
    if (D_8002BA6C != 0) {
        actor->vy = -0.8f;
    } else {
        actor->vy = 0.8f;
    }
    actor->sprite = &D_8002E878;
}

void jetpacActorUpdateFighter(JetpacActor *actor) {
    switch (actor->state) {
    case 3:
        if (actor->timer == 0) {
            if (jetpacCheckLedgeCollision((f32)actor->boxX1 + actor->x + actor->vx,
                              (f32)actor->boxY1 + actor->y + actor->vy,
                              (f32)actor->boxX2 + actor->x + actor->vx,
                              (f32)actor->boxY2 + actor->y + actor->vy, 1) >= 0) {
                jetpacActorExplode(actor);
            } else {
                actor->lifetime--;
            }
            if (actor->lifetime == 0) {
                jetpacActorExplode(actor);
            }
        } else if (D_8002BA6C != 0 && actor->y < 32.0f) {
            jetpacActorExplode(actor);
        }

        if (actor->state == 3) {
            jetpacCheckPlayerHit(actor);
        }
        if (actor->state == 4) {
            JetpacPlayer *p = &jetpacGame.players[jetpacGame.activePlayer];
            p->score += actor->points;
            return;
        }

        if (actor->timer != 0) {
            actor->timer--;
            if (D_8002BA6C != 0) {
                actor->vy = -0.8f;
            } else {
                actor->vy = 0.8f;
            }
            if (actor->timer == 0) {
                if (actor->flip != 0) {
                    actor->vx = -1.6f;
                } else {
                    actor->vx = 1.6f;
                }
                actor->color[0] = 0xFF;
                actor->color[1] = 0xFF;
                actor->color[2] = 0xFF;
            }
        }

        if (actor->timer == 0 && (jetpacGame.stateTimer & 2)) {
            if (jetpacGetEntityCenterY(actor) < D_8002F054 + (f32)D_8002F078) {
                actor->vy = 0.8f;
            } else {
                actor->vy = -0.8f;
            }
        }
        actor->x += actor->vx;
        actor->y += actor->vy;
        return;
    case 4:
        actor->timer++;
        if (actor->timer >= 15) {
            actor->state = 0;
        }
        return;
    }
}

void jetpacActorInitHoming(JetpacActor *actor) {
    actor->update = jetpacActorUpdateHoming;
    actor->points = 0x32;
    if (actor->y < 88.0f) {
        actor->flip = 0;
    } else {
        actor->flip = 1;
    }
    jetpacActorSteerToPlayer(actor);
}

void jetpacActorInitSaucer(JetpacActor *actor) {
    actor->boxY2 = 8;
    actor->sprite = &D_8002E890;
    jetpacActorInitHoming(actor);
}

f32 jetpacActorAccelClamp(f32 targetDelta, f32 curVel) {
    f64 d;
    f64 r;

    if (targetDelta < 0.0f) {
        curVel = curVel - 0.08;
    } else {
        curVel = curVel + 0.08;
    }
    d = curVel;
    r = d < -1.2 ? -1.2 : (d > 1.2 ? 1.2 : d);
    return r;
}


void jetpacActorSteerToPlayer(JetpacActor *actor) {
    f32 cx2;
    f32 dx;
    f32 dxw;
    f32 rx;
    f32 dy;
    f32 dyw;
    f32 ry;
    f32 cx1;

    cx1 = jetpacGetEntityCenterX(actor);
    cx2 = jetpacGetEntityCenterX((JetpacActor *)&jetpacPlayer);
    dx = cx2 - cx1;
    if (cx1 < cx2) {
        dxw = dx - 256.0f;
    } else {
        dxw = dx + 256.0f;
    }
    dy = D_8002F054 + (f32)D_8002F078 - jetpacGetEntityCenterY(actor);
    if (0.0f < dy) {
        dyw = dy - 288.0;
    } else {
        dyw = dy + 192.0f;
    }
    if (((0.0f < dx) ? dx : -dx) < ((0.0f < dxw) ? dxw : -dxw)) {
        rx = dx;
    } else {
        rx = dxw;
    }
    if (((0.0f < dy) ? dy : -dy) < ((0.0f < dyw) ? dyw : -dyw)) {
        ry = dy;
    } else {
        ry = dyw;
    }
    actor->vx = jetpacActorAccelClamp(rx, actor->vx);
    actor->vy = jetpacActorAccelClamp(ry, actor->vy);
}

void jetpacActorUpdateHoming(JetpacActor *actor) {
    s32 res;

    switch (actor->state) {
    case 3:
        jetpacActorSteerToPlayer(actor);
        res = jetpacCheckLedgeCollision((f32)actor->boxX1 + actor->x + actor->vx,
                            (f32)actor->boxY1 + actor->y + actor->vy,
                            (f32)actor->boxX2 + actor->x + actor->vx,
                            (f32)actor->boxY2 + actor->y + actor->vy, 1);
        if (res >= 0) {
            jetpacBounceOffLedge(actor, res);
        }
        if (jetpacCheckPlayerHit(actor) == 0) {
            if ((actor->y + actor->vy) < 24.0f) {
                actor->vy = -actor->vy;
            }
            actor->y += actor->vy;
            actor->x += actor->vx;
        }
        break;
    case 4:
        actor->timer++;
        if (actor->timer >= 15) {
            actor->state = 0;
        }
        break;
    }
}

void jetpacActorHopImpulse(JetpacActor *actor) {
    s32 t = actor->timer % 4 + 1;

    actor->vy = -1.2 / (f64)t;
    actor->timer = actor->timer + 1;
}

void jetpacActorInitHop(JetpacActor *actor) {
    actor->update = jetpacActorUpdateHop;
    actor->points = 0x3C;
    actor->timer = (s32)(jetpacRandFloat() * 16.0f);
    if (actor->y < 88.0f) {
        actor->vx = -1.2f;
    } else {
        actor->vx = 1.2f;
    }
    jetpacActorHopImpulse(actor);
    actor->sprite = &D_8002E8A8;
}

void jetpacActorUpdateHop(JetpacActor *actor) {
    s32 res;
    f32 prev;
    f32 cur;

    switch (actor->state) {
    case 3:
        actor->vy = actor->vy + 0.005;
        prev = actor->vy;
        res = jetpacCheckLedgeCollision((f32)actor->boxX1 + actor->x + actor->vx,
                            (f32)actor->boxY1 + actor->y + actor->vy,
                            (f32)actor->boxX2 + actor->x + actor->vx,
                            (f32)actor->boxY2 + actor->y + actor->vy, 1);
        if (res >= 0) {
            jetpacBounceOffLedge(actor, res);
            cur = actor->vy;
            if (prev > 0.0f && cur < 0.0f) {
                jetpacActorHopImpulse(actor);
            }
        }
        if (jetpacCheckPlayerHit(actor) == 0) {
            if ((actor->y + actor->vy) < 24.0f) {
                actor->vy = -actor->vy;
            }
            actor->y += actor->vy;
            actor->x += actor->vx;
        }
        break;
    case 4:
        actor->timer++;
        if (actor->timer >= 15) {
            actor->state = 0;
        }
        break;
    }
}

void jetpacActorInitCross(JetpacActor *actor) {
    actor->boxY2 = 0xE;
    actor->sprite = &D_8002E8C0;
    jetpacActorInitStraight(actor, 1.2f, 0.3f);
    actor->update = jetpacActorUpdateStraight;
}

void jetpacActorInitBlob(JetpacActor *actor) {
    actor->boxY2 = 0xE;
    actor->sprite = &D_8002E8D8;
    jetpacActorInitHoming(actor);
}

s32 jetpacKillActorInBox(f32 x1, f32 y1, f32 x2, f32 y2) {
    JetpacActor *actor = jetpacActors;
    JetpacPlayer *playerData;
    s32 i;

    for (i = 0; i < 6; i++, actor++) {
        if (actor->state == 3) {
            if (jetpacCheckAabbOverlapWrapped(x1, y1, x2, y2,
                              actor->x + (f32)actor->boxX1,
                              actor->y + (f32)actor->boxY1,
                              actor->x + (f32)actor->boxX2,
                              actor->y + (f32)actor->boxY2)) {
                playerData = &jetpacGame.players[jetpacGame.activePlayer];
                jetpacActorExplode(actor);
                playerData->score += actor->points;
                return 1;
            }
        }
    }
    return 0;
}

void jetpacInitActors(void) {
    s32 i;
    JetpacActor defaultActor;
    JetpacActor *actor;

    defaultActor = D_8002E964;
    actor = jetpacActors;
    i = 0;
    do {
        *actor++ = defaultActor;
        i++;
    } while (i < 6);

    for (i = 0; i < 3; i++) {
        jetpacSpawnActor();
    }
    D_8002E8F0 = (s32)(jetpacRandFloat() * 180.0f);
}

extern s32 D_8002F3BC;

void jetpacUpdateActors(void) {
    JetpacActor *actor = jetpacActors;
    s32 cnt = 0;
    s32 i;

    if (jetpacIsSpawnDelay() == 0) {
        if (D_8002E8F0 > 0) {
            D_8002E8F0--;
        }
        for (i = 0; i != 6; i++, actor++) {
            if (actor->state > 0 && actor->update != NULL) {
                actor->update(actor);
                if (actor->x < 0.0f) {
                    actor->x += 256.0f;
                }
                if (actor->x > 256.0f) {
                    actor->x -= 256.0f;
                }
                cnt++;
            }
        }
        if (cnt < 3 && D_8002E8F0 >= 6) {
            D_8002E8F0 = (s32)(jetpacRandFloat() * 5.0f);
        }
        if (D_8002E8F0 == 0 && D_8002F3BC == 2) {
            jetpacSpawnActor();
            cnt++;
            if (cnt < 3) {
                D_8002E8F0 = (s32)(jetpacRandFloat() * 5.0f);
            } else {
                D_8002E8F0 = (s32)(jetpacRandFloat() * 180.0f);
            }
        }
    }
}

void jetpacDrawActors(void) {
    JetpacActor *actor = jetpacActors;
    s32 i;

    if (jetpacIsSpawnDelay() == 0) {
        for (i = 0; i < 6; i++, actor++) {
            if (actor->state >= 2 && actor->sprite != NULL) {
                jetpacDrawActor(actor);
            }
        }
    }
}

void jetpacSetupTextRdp(Gfx **pGlist) {
    Gfx *g = *pGlist;
    WRITE_GFX(g++, 0xE7000000, 0);
    WRITE_GFX(g++, 0xE3000A01, 0);
    WRITE_GFX(g++, 0xD9000000, 0);
    WRITE_GFX(g++, 0xD9FFFFFF, 0x00200004);
    WRITE_GFX(g++, 0xFC30FE61, 0x55FEF379);
    WRITE_GFX(g++, 0xE200001C, 0x0F0A4000);
    *pGlist = g;
}

void jetpacSetTextColor(u8 r, u8 g, u8 b, u8 a) {
    D_80045BE0 = r;
    D_80045BE1 = g;
    D_80045BE2 = b;
    D_80045BE3 = a;
}

void jetpacSetTextHighlightColor(s8 r, s8 g, s8 b, s8 a) {
    D_8002E9C0 = r;
    D_8002E9C4 = g;
    D_8002E9C8 = b;
    D_8002E9CC = a;
}

void jetpacDrawString(Gfx **pGlist, char *str, s32 x, s32 y, s32 highlight) {
    Gfx *g = *pGlist;

    if (highlight != 0) {
        gDPSetPrimColor(g++, 0, 0, D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC);
        gDPSetEnvColor(g++, D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3);
    } else {
        gDPSetPrimColor(g++, 0, 0, D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3);
        gDPSetEnvColor(g++, D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC);
    }
    *pGlist = textDrawString(g, 4, (s16)x, (s16)y, str);
}
