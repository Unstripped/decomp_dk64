#include "common.h"
#include "jetpac.h"
#include "proto/jetpac/0.h"
#include "proto/jetpac/1460.h"
#include "proto/jetpac/1A60.h"
#include "proto/jetpac/3060.h"
#include "proto/jetpac/3480.h"
#include "proto/jetpac/4FC0.h"
extern s32 jetpacBlinkPhase;
extern f32 D_8002F054;
extern s32 D_8002F078;

// .data 0x8002DEB0-0x8002E9B4 (sprite pixel layout: see 0.c).
Gfx D_8002DEB0[1] = { gsSPEndDisplayList() };
u8 D_8002DEB8[0x108] = {
#include "jetpac/D_8002DEB8.inc.c"
};
u8 D_8002DFC0[0x108] = {
#include "jetpac/D_8002DFC0.inc.c"
};
u8 D_8002E0C8[0x108] = {
#include "jetpac/D_8002E0C8.inc.c"
};
u8 D_8002E1D0[0x108] = {
#include "jetpac/D_8002E1D0.inc.c"
};
u8 D_8002E2D8[0x108] = {
#include "jetpac/D_8002E2D8.inc.c"
};
u8 D_8002E3E0[0x88] = {
#include "jetpac/D_8002E3E0.inc.c"
};
u8 D_8002E468[0x88] = {
#include "jetpac/D_8002E468.inc.c"
};
u8 D_8002E4F0[0x108] = {
#include "jetpac/D_8002E4F0.inc.c"
};
u8 D_8002E5F8[0x108] = {
#include "jetpac/D_8002E5F8.inc.c"
};
u8 D_8002E700[0x100] = {
#include "jetpac/D_8002E700.inc.c"
};
JetpacSprite D_8002E800[2] = {
    { D_8002DEB8, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002DFC0, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
};
JetpacSprite D_8002E830 = { D_8002E0C8, 0, 16, 16, 16, 4, 1, 0, 0, 0 };
JetpacSprite D_8002E848[2] = {
    { D_8002E1D0, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002E2D8, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
};
JetpacSprite D_8002E878 = { D_8002E3E0, 0, 16, 16, 8, 4, 1, 0, 0, 0 };
JetpacSprite D_8002E890 = { D_8002E468, 0, 16, 16, 8, 4, 1, 0, 0, 0 };
JetpacSprite D_8002E8A8 = { D_8002E4F0, 0, 16, 16, 16, 4, 1, 0, 0, 0 };
JetpacSprite D_8002E8C0 = { D_8002E5F8, 0, 16, 16, 16, 4, 1, 0, 0, 0 };
JetpacSprite D_8002E8D8 = { D_8002E700, 0, 16, 16, 16, 4, 1, 0, 0, 0 };
s32 jetpacSpawnTimer = 0;
void (*jetpacActorInitTable[8])(JetpacActor *) = {
    jetpacActorInitMeteor, jetpacActorInitBounce, jetpacActorInitWander, jetpacActorInitFighter,
    jetpacActorInitSaucer, jetpacActorInitHop, jetpacActorInitCross, jetpacActorInitBlob,
};
JetpacActor jetpacActorSpawnTemplate = {
    0.0f, 0.0f, 0.0f, 0.0f, { 190, 190, 190, 1 }, 0, 0, 0, 0, 16, 16, 0, { 0, 0, 14, { 255, 255, 255, 1 } }, 0, 25, NULL, NULL,
};
JetpacActor jetpacActorClearTemplate = {
    0.0f, 0.0f, 0.0f, 0.0f, { 190, 190, 190, 1 }, 0, 0, 0, 0, 16, 11, 0, { 0, 0, 14, { 255, 255, 255, 1 } }, 0, 0, NULL, NULL,
};

JetpacActor *jetpacFindFreeActor(void) {
    JetpacActor *actor = jetpacGame.actors;
    s32 i;

    for (i = 0; i < 6; i++, actor++) {
        if (actor->state == 0) {
            return actor;
        }
    }
    return NULL;
}

s32 jetpacCheckPlayerHit(JetpacActor *actor) {
    s32 pad[7];
    f32 px2;
    f32 py2;
    s32 hit;
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
    x2 = actor->boxX2 + ax;
    y2 = actor->boxY2 + ay;
    px2 = player->boxX2 + px - 2.0f;
    py2 = player->boxY2 + py;
    hit = 0;
    ax += actor->boxX1;
    ay += actor->boxY1;
    px += player->boxX1 + 2;
    py += player->boxY1 + 4;
    if (player->state == 3) {
        hit = jetpacCheckAabbOverlapWrapped(ax, ay, x2, y2, px, py, px2, py2);
    }
    if (hit != 0) {
        player->state = 4;
        player->timer = 0;
        jetpacSnapActorToGrid(player);
        jetpacActorExplode(actor);
    }
    return hit;
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
    s32 state = actor->state;

    if (state == 3) {
        jetpacGridAddTiledSprite(actor->sprite, actor->x, actor->y, actor->color, actor->flip);
        return;
    }
    if (state == 4) {
        jetpacUpdateExplosion(&actor->explosion);
        if (actor->explosion.timer < 7) {
            jetpacGridAddTiledSprite(actor->sprite, actor->x, actor->y, actor->color, actor->flip);
        }
    }
}

JetpacActor *jetpacAllocActor(void) {
    s32 pad;
    JetpacActor *actor = jetpacFindFreeActor();
    JetpacActor templateActor = jetpacActorSpawnTemplate;

    if (actor == NULL) {
        return NULL;
    }
    *actor = templateActor;
    actor->x = 0.0f;
    actor->y = ((s32)(jetpacRandFloat() * 15.0f) % 15) * 8 + 32;
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

void jetpacSpawnActor(void) {
    s32 pad[2];
    void (*init)(JetpacActor *);
    JetpacActor *actor;
    JetpacPlayer *playerData;
    s32 stage;

    playerData = &jetpacGame.players[jetpacGame.activePlayer];
    stage = playerData->stage;
    init = jetpacActorInitTable[stage % 8];
    actor = jetpacAllocActor();
    if (actor != NULL) {
        init(actor);
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
    ax1 = actor->x + actor->boxX1;
    ax2 = actor->x + actor->boxX2;
    lx1 = ledge->boxX1;
    lx2 = ledge->boxX2;
    ay1 = actor->y + actor->boxY1;
    ay2 = actor->y + actor->boxY2;
    ly1 = ledge->boxY1;
    ly2 = ledge->boxY2;
    if ((lx2 <= ax1 && lx2 <= ax2) || (ax2 <= lx1 && ax1 <= lx1)) {
        actor->vx = -actor->vx;
    }
    if ((ly2 <= ay1 && ly2 <= ay2) || (ay2 <= ly1 && ay1 <= ly1)) {
        actor->vy = -actor->vy;
    }
}

void jetpacActorInitStraight(JetpacActor *actor, f32 speedX, f32 speedY) {
    s32 diagonalCount;
    s32 levelCount;
    s32 i;
    JetpacActor *other;

    diagonalCount = levelCount = 0;
    actor->points = 25;
    if (actor->y < 88.0f) {
        actor->vx = speedX;
        actor->flip = 0;
    } else {
        actor->vx = -speedX;
        actor->flip = 1;
    }
    other = jetpacGame.actors;
    for (i = 0; i < 6; i++) {
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
        actor->vy = speedY;
    } else if (diagonalCount == 3) {
        actor->vy = 0.0f;
    } else if ((s32)(jetpacRandFloat() * 2) % 2) {
        actor->vy = 0.0f;
    } else {
        actor->vy = speedY;
    }
}

void jetpacActorUpdateStraight(JetpacActor *actor) {
    switch (actor->state) {
    case 3:
        if (jetpacCheckLedgeCollision(actor->boxX1 + actor->x + actor->vx,
                          actor->boxY1 + actor->y + actor->vy,
                          actor->boxX2 + actor->x + actor->vx,
                          actor->boxY2 + actor->y + actor->vy, 1) >= 0) {
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
    actor->boxY2 = 11;
    jetpacActorInitStraight(actor, 1.6f, 0.5f);
    actor->update = jetpacActorUpdateMeteor;
}

void jetpacActorUpdateMeteor(JetpacActor *actor) {
    jetpacActorUpdateStraight(actor);
    actor->sprite = &D_8002E800[(s32)actor->x % 2];
}

void jetpacActorInitBounce(JetpacActor *actor) {
    actor->update = jetpacActorUpdateBounce;
    actor->points = 80;
    if (actor->y < 88.0f) {
        actor->vx = -1.2f;
    } else {
        actor->vx = 1.2f;
    }
    actor->vy = -0.8f;
    actor->sprite = &D_8002E830;
}

void jetpacActorUpdateBounce(JetpacActor *actor) {
    s32 ledgeIndex;

    switch (actor->state) {
    case 3:
        ledgeIndex = jetpacCheckLedgeCollision(actor->boxX1 + actor->x + actor->vx,
                            actor->boxY1 + actor->y + actor->vy,
                            actor->boxX2 + actor->x + actor->vx,
                            actor->boxY2 + actor->y + actor->vy, 1);
        if (ledgeIndex >= 0) {
            jetpacBounceOffLedge(actor, ledgeIndex);
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
    actor->points = 40;
    if (actor->y < 88.0f) {
        actor->vx = -1.2f;
    } else {
        actor->vx = 1.2f;
    }
    jetpacActorPickWanderDirection(actor);
    actor->timer = jetpacRandFloat() * 60.0f + 10.0f;
}

void jetpacActorPickWanderDirection(JetpacActor *actor) {
    if (actor->vy == 0.0) {
        if (jetpacRandFloat() < 0.5) {
            actor->vy = -0.6f;
        } else {
            actor->vy = 0.6f;
        }
    } else {
        actor->vy = 0.0f;
    }
}

void jetpacActorUpdateWander(JetpacActor *actor) {
    s32 ledgeIndex;

    switch (actor->state) {
    case 3:
        if (--actor->timer == 0) {
            jetpacActorPickWanderDirection(actor);
            actor->timer = jetpacRandFloat() * 60.0f + 10.0f;
        }
        ledgeIndex = jetpacCheckLedgeCollision(actor->boxX1 + actor->x + actor->vx,
                            actor->boxY1 + actor->y + actor->vy,
                            actor->boxX2 + actor->x + actor->vx,
                            actor->boxY2 + actor->y + actor->vy, 1);
        if (ledgeIndex >= 0) {
            jetpacBounceOffLedge(actor, ledgeIndex);
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
    actor->points = 55;
    actor->timer = jetpacRandFloat() * 60.0f + 10.0f;
    actor->lifetime = jetpacRandFloat() * 180.0f + 10.0f;
    actor->boxY2 = 8;
    if (actor->y < 88.0f) {
        actor->flip = 0;
    } else {
        actor->flip = 1;
    }
    actor->vx = 0.0f;
    if (jetpacBlinkPhase != 0) {
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
            if (jetpacCheckLedgeCollision(actor->boxX1 + actor->x + actor->vx,
                              actor->boxY1 + actor->y + actor->vy,
                              actor->boxX2 + actor->x + actor->vx,
                              actor->boxY2 + actor->y + actor->vy, 1) >= 0) {
                jetpacActorExplode(actor);
            } else {
                actor->lifetime--;
            }
            if (actor->lifetime == 0) {
                jetpacActorExplode(actor);
            }
        } else if (jetpacBlinkPhase != 0 && actor->y < 32.0f) {
            jetpacActorExplode(actor);
        }

        if (actor->state == 3) {
            jetpacCheckPlayerHit(actor);
        }
        if (actor->state == 4) {
            JetpacPlayer *playerData = &jetpacGame.players[jetpacGame.activePlayer];
            playerData->score += actor->points;
            return;
        }

        if (actor->timer != 0) {
            actor->timer--;
            if (jetpacBlinkPhase != 0) {
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
            if (jetpacGetEntityCenterY(actor) < D_8002F054 + D_8002F078) {
                actor->vy = 0.8f;
            } else {
                actor->vy = -0.8f;
            }
        }
        actor->x += actor->vx;
        actor->y += actor->vy;
        break;
    case 4:
        actor->timer++;
        if (actor->timer >= 15) {
            actor->state = 0;
        }
        break;
    }
}

void jetpacActorInitHoming(JetpacActor *actor) {
    actor->update = jetpacActorUpdateHoming;
    actor->points = 50;
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
    if (targetDelta < 0.0f) {
        curVel -= 0.08;
    } else {
        curVel += 0.08;
    }
    return curVel < -1.2 ? -1.2 : (curVel > 1.2 ? 1.2 : curVel);
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
    cx2 = jetpacGetEntityCenterX((JetpacActor *)&jetpacGame.player);
    dx = cx2 - cx1;
    if (cx1 < cx2) {
        dxw = dx - 256.0f;
    } else {
        dxw = dx + 256.0f;
    }
    dy = D_8002F054 + D_8002F078 - jetpacGetEntityCenterY(actor);
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
    s32 ledgeIndex;

    switch (actor->state) {
    case 3:
        jetpacActorSteerToPlayer(actor);
        ledgeIndex = jetpacCheckLedgeCollision(actor->boxX1 + actor->x + actor->vx,
                            actor->boxY1 + actor->y + actor->vy,
                            actor->boxX2 + actor->x + actor->vx,
                            actor->boxY2 + actor->y + actor->vy, 1);
        if (ledgeIndex >= 0) {
            jetpacBounceOffLedge(actor, ledgeIndex);
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
    s32 divisor = actor->timer % 4 + 1;

    actor->vy = -1.2 / divisor;
    actor->timer++;
}

void jetpacActorInitHop(JetpacActor *actor) {
    actor->update = jetpacActorUpdateHop;
    actor->points = 60;
    actor->timer = jetpacRandFloat() * 16.0f;
    if (actor->y < 88.0f) {
        actor->vx = -1.2f;
    } else {
        actor->vx = 1.2f;
    }
    jetpacActorHopImpulse(actor);
    actor->sprite = &D_8002E8A8;
}

void jetpacActorUpdateHop(JetpacActor *actor) {
    s32 ledgeIndex;
    f32 prevVy;
    f32 bouncedVy;

    switch (actor->state) {
    case 3:
        actor->vy += 0.005;
        prevVy = actor->vy;
        ledgeIndex = jetpacCheckLedgeCollision(actor->boxX1 + actor->x + actor->vx,
                            actor->boxY1 + actor->y + actor->vy,
                            actor->boxX2 + actor->x + actor->vx,
                            actor->boxY2 + actor->y + actor->vy, 1);
        if (ledgeIndex >= 0) {
            jetpacBounceOffLedge(actor, ledgeIndex);
            bouncedVy = actor->vy;
            if (prevVy > 0.0f && bouncedVy < 0.0f) {
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
    actor->boxY2 = 14;
    actor->sprite = &D_8002E8C0;
    jetpacActorInitStraight(actor, 1.2f, 0.3f);
    actor->update = jetpacActorUpdateStraight;
}

void jetpacActorInitBlob(JetpacActor *actor) {
    actor->boxY2 = 14;
    actor->sprite = &D_8002E8D8;
    jetpacActorInitHoming(actor);
}

s32 jetpacKillActorInBox(f32 x1, f32 y1, f32 x2, f32 y2) {
    JetpacActor *actor = jetpacGame.actors;
    JetpacPlayer *playerData;
    s32 i;

    for (i = 0; i < 6; i++, actor++) {
        if (actor->state == 3) {
            if (jetpacCheckAabbOverlapWrapped(x1, y1, x2, y2,
                              actor->x + actor->boxX1,
                              actor->y + actor->boxY1,
                              actor->x + actor->boxX2,
                              actor->y + actor->boxY2)) {
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

    defaultActor = jetpacActorClearTemplate;
    actor = jetpacGame.actors;
    for (i = 0; i < 6; i++) {
        *actor++ = defaultActor;
    }

    for (i = 0; i < 3; i++) {
        jetpacSpawnActor();
    }
    jetpacSpawnTimer = jetpacRandFloat() * 180.0f;
}

void jetpacUpdateActors(void) {
    JetpacActor *actor = jetpacGame.actors;
    s32 activeCount = 0;
    s32 i;

    if (jetpacIsSpawnDelay() == 0) {
        if (jetpacSpawnTimer > 0) {
            jetpacSpawnTimer--;
        }
        for (i = 0; i < 6; i++, actor++) {
            if (actor->state > 0 && actor->update != NULL) {
                actor->update(actor);
                if (actor->x < 0.0f) {
                    actor->x += 256.0f;
                }
                if (actor->x > 256.0f) {
                    actor->x -= 256.0f;
                }
                activeCount++;
            }
        }
        if (activeCount < 3 && jetpacSpawnTimer >= 6) {
            jetpacSpawnTimer = jetpacRandFloat() * 5.0f;
        }
        if (jetpacSpawnTimer == 0 && jetpacGame.gameState == 2) {
            jetpacSpawnActor();
            activeCount++;
            if (activeCount < 3) {
                jetpacSpawnTimer = jetpacRandFloat() * 5.0f;
            } else {
                jetpacSpawnTimer = jetpacRandFloat() * 180.0f;
            }
        }
    }
}

void jetpacDrawActors(void) {
    JetpacActor *actor = jetpacGame.actors;
    s32 i;

    if (jetpacIsSpawnDelay() == 0) {
        for (i = 0; i < 6; i++, actor++) {
            if (actor->state >= 2 && actor->sprite != NULL) {
                jetpacDrawActor(actor);
            }
        }
    }
}
