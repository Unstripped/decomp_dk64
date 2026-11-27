#include "common.h"
#include "jetpac.h"
#include "proto/jetpac/0_game.h"
#include "proto/jetpac/1460_sprite_grid.h"
#include "proto/jetpac/1A60_player.h"
#include "proto/jetpac/3060_collision_utils.h"
#include "proto/jetpac/3480_rocket_items.h"
#include "proto/jetpac/4FC0_enemies.h"
extern s32 jetpacBlinkPhase;

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
TextureDescriptor jetpacMeteorSprites[2] = {
    { D_8002DEB8, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002DFC0, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
};
TextureDescriptor jetpacBounceSprite = { D_8002E0C8, 0, 16, 16, 16, 4, 1, 0, 0, 0 };
TextureDescriptor jetpacWanderSprites[2] = {
    { D_8002E1D0, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
    { D_8002E2D8, 0, 16, 16, 16, 4, 1, 0, 0, 0 },
};
TextureDescriptor jetpacFighterSprite = { D_8002E3E0, 0, 16, 16, 8, 4, 1, 0, 0, 0 };
TextureDescriptor jetpacSaucerSprite = { D_8002E468, 0, 16, 16, 8, 4, 1, 0, 0, 0 };
TextureDescriptor jetpacHopSprite = { D_8002E4F0, 0, 16, 16, 16, 4, 1, 0, 0, 0 };
TextureDescriptor jetpacCrossSprite = { D_8002E5F8, 0, 16, 16, 16, 4, 1, 0, 0, 0 };
TextureDescriptor jetpacBlobSprite = { D_8002E700, 0, 16, 16, 16, 4, 1, 0, 0, 0 };
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
        if (actor->head.state == 0) {
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
    ax = actor->head.x;
    ay = actor->head.y;
    px = player->head.x;
    py = player->head.y;
    x2 = actor->head.boxX2 + ax;
    y2 = actor->head.boxY2 + ay;
    px2 = player->head.boxX2 + px - 2.0f;
    py2 = player->head.boxY2 + py;
    hit = 0;
    ax += actor->head.boxX1;
    ay += actor->head.boxY1;
    px += player->head.boxX1 + 2;
    py += player->head.boxY1 + 4;
    if (player->head.state == 3) {
        hit = jetpacCheckAabbOverlapWrapped(ax, ay, x2, y2, px, py, px2, py2);
    }
    if (hit != 0) {
        player->head.state = 4;
        player->head.timer = 0;
        jetpacSnapActorToGrid(player);
        jetpacActorExplode(actor);
    }
    return hit;
}

void jetpacActorExplode(JetpacActor *actor) {
    actor->head.state = 4;
    actor->head.timer = 0;
    actor->explosion.timer = 0;
    actor->explosion.x = (s32)actor->head.x & 0xFFF8;
    actor->explosion.y = (s32)actor->head.y & 0xFFF8;
    jetpacPlaySound(5);
}

void jetpacDrawActor(JetpacActor *actor) {
    s32 state = actor->head.state;

    if (state == 3) {
        jetpacGridAddTiledSprite(actor->sprite, actor->head.x, actor->head.y, actor->head.color, actor->head.flip);
        return;
    }
    if (state == 4) {
        jetpacUpdateExplosion(&actor->explosion);
        if (actor->explosion.timer < 7) {
            jetpacGridAddTiledSprite(actor->sprite, actor->head.x, actor->head.y, actor->head.color, actor->head.flip);
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
    actor->head.x = 0.0f;
    actor->head.y = ((s32)(jetpacRandFloat() * 15.0f) % 15) * 8 + 32;
    switch ((s32)(jetpacRandFloat() * 4.0f) % 4) {
    case 0:
        actor->head.color[0] = 0;
        break;
    case 1:
        actor->head.color[1] = 0;
        break;
    case 2:
        actor->head.color[0] = 0;
        actor->head.color[2] = 0;
        break;
    case 3:
        actor->head.color[1] = 0;
        actor->head.color[2] = 0;
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
        actor->head.state = 3;
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
    ax1 = actor->head.x + actor->head.boxX1;
    ax2 = actor->head.x + actor->head.boxX2;
    lx1 = ledge->boxX1;
    lx2 = ledge->boxX2;
    ay1 = actor->head.y + actor->head.boxY1;
    ay2 = actor->head.y + actor->head.boxY2;
    ly1 = ledge->boxY1;
    ly2 = ledge->boxY2;
    if ((lx2 <= ax1 && lx2 <= ax2) || (ax2 <= lx1 && ax1 <= lx1)) {
        actor->head.vx = -actor->head.vx;
    }
    if ((ly2 <= ay1 && ly2 <= ay2) || (ay2 <= ly1 && ay1 <= ly1)) {
        actor->head.vy = -actor->head.vy;
    }
}

void jetpacActorInitStraight(JetpacActor *actor, f32 speedX, f32 speedY) {
    s32 diagonalCount;
    s32 levelCount;
    s32 i;
    JetpacActor *other;

    diagonalCount = levelCount = 0;
    actor->points = 25;
    if (actor->head.y < 88.0f) {
        actor->head.vx = speedX;
        actor->head.flip = 0;
    } else {
        actor->head.vx = -speedX;
        actor->head.flip = 1;
    }
    other = jetpacGame.actors;
    for (i = 0; i < 6; i++) {
        if (other->head.state > 0) {
            if (other->head.vy == 0.0f) {
                levelCount++;
            } else {
                diagonalCount++;
            }
        }
        other++;
    }
    if (levelCount == 3) {
        actor->head.vy = speedY;
    } else if (diagonalCount == 3) {
        actor->head.vy = 0.0f;
    } else if ((s32)(jetpacRandFloat() * 2) % 2) {
        actor->head.vy = 0.0f;
    } else {
        actor->head.vy = speedY;
    }
}

void jetpacActorUpdateStraight(JetpacActor *actor) {
    switch (actor->head.state) {
    case 3:
        if (jetpacCheckLedgeCollision(actor->head.boxX1 + actor->head.x + actor->head.vx,
                          actor->head.boxY1 + actor->head.y + actor->head.vy,
                          actor->head.boxX2 + actor->head.x + actor->head.vx,
                          actor->head.boxY2 + actor->head.y + actor->head.vy, 1) >= 0) {
            jetpacActorExplode(actor);
        } else if (jetpacCheckPlayerHit(actor) == 0) {
            actor->head.x += actor->head.vx;
            actor->head.y += actor->head.vy;
        }
        break;
    case 4:
        actor->head.timer++;
        if (actor->head.timer >= 15) {
            actor->head.state = 0;
        }
        break;
    }
}

void jetpacActorInitMeteor(JetpacActor *actor) {
    actor->head.boxY2 = 11;
    jetpacActorInitStraight(actor, 1.6f, 0.5f);
    actor->update = jetpacActorUpdateMeteor;
}

void jetpacActorUpdateMeteor(JetpacActor *actor) {
    jetpacActorUpdateStraight(actor);
    actor->sprite = &jetpacMeteorSprites[(s32)actor->head.x % 2];
}

void jetpacActorInitBounce(JetpacActor *actor) {
    actor->update = jetpacActorUpdateBounce;
    actor->points = 80;
    if (actor->head.y < 88.0f) {
        actor->head.vx = -1.2f;
    } else {
        actor->head.vx = 1.2f;
    }
    actor->head.vy = -0.8f;
    actor->sprite = &jetpacBounceSprite;
}

void jetpacActorUpdateBounce(JetpacActor *actor) {
    s32 ledgeIndex;

    switch (actor->head.state) {
    case 3:
        ledgeIndex = jetpacCheckLedgeCollision(actor->head.boxX1 + actor->head.x + actor->head.vx,
                            actor->head.boxY1 + actor->head.y + actor->head.vy,
                            actor->head.boxX2 + actor->head.x + actor->head.vx,
                            actor->head.boxY2 + actor->head.y + actor->head.vy, 1);
        if (ledgeIndex >= 0) {
            jetpacBounceOffLedge(actor, ledgeIndex);
        }
        if (jetpacCheckPlayerHit(actor) == 0) {
            if ((actor->head.y + actor->head.vy) < 24.0f) {
                actor->head.vy = -actor->head.vy;
            }
            actor->head.y += actor->head.vy;
            actor->head.x += actor->head.vx;
            if ((s32)actor->head.x & 2) {
                actor->head.flip ^= 1;
            }
        }
        break;
    case 4:
        actor->head.timer++;
        if (actor->head.timer >= 15) {
            actor->head.state = 0;
        }
        break;
    }
}

void jetpacActorInitWander(JetpacActor *actor) {
    actor->update = jetpacActorUpdateWander;
    actor->points = 40;
    if (actor->head.y < 88.0f) {
        actor->head.vx = -1.2f;
    } else {
        actor->head.vx = 1.2f;
    }
    jetpacActorPickWanderDirection(actor);
    actor->head.timer = jetpacRandFloat() * 60.0f + 10.0f;
}

void jetpacActorPickWanderDirection(JetpacActor *actor) {
    if (actor->head.vy == 0.0) {
        if (jetpacRandFloat() < 0.5) {
            actor->head.vy = -0.6f;
        } else {
            actor->head.vy = 0.6f;
        }
    } else {
        actor->head.vy = 0.0f;
    }
}

void jetpacActorUpdateWander(JetpacActor *actor) {
    s32 ledgeIndex;

    switch (actor->head.state) {
    case 3:
        if (--actor->head.timer == 0) {
            jetpacActorPickWanderDirection(actor);
            actor->head.timer = jetpacRandFloat() * 60.0f + 10.0f;
        }
        ledgeIndex = jetpacCheckLedgeCollision(actor->head.boxX1 + actor->head.x + actor->head.vx,
                            actor->head.boxY1 + actor->head.y + actor->head.vy,
                            actor->head.boxX2 + actor->head.x + actor->head.vx,
                            actor->head.boxY2 + actor->head.y + actor->head.vy, 1);
        if (ledgeIndex >= 0) {
            jetpacBounceOffLedge(actor, ledgeIndex);
            if (actor->head.timer < 10) {
                actor->head.timer = 10;
            }
        }
        if (jetpacCheckPlayerHit(actor) == 0) {
            if ((actor->head.y + actor->head.vy) < 24.0f) {
                actor->head.vy = -actor->head.vy;
            }
            actor->head.y += actor->head.vy;
            actor->head.x += actor->head.vx;
            actor->sprite = &jetpacWanderSprites[(s32)(actor->head.x / 4) % 2];
        }
        break;
    case 4:
        actor->head.timer++;
        if (actor->head.timer >= 15) {
            actor->head.state = 0;
        }
        break;
    }
}

void jetpacActorInitFighter(JetpacActor *actor) {
    actor->update = jetpacActorUpdateFighter;
    actor->points = 55;
    actor->head.timer = jetpacRandFloat() * 60.0f + 10.0f;
    actor->lifetime = jetpacRandFloat() * 180.0f + 10.0f;
    actor->head.boxY2 = 8;
    if (actor->head.y < 88.0f) {
        actor->head.flip = 0;
    } else {
        actor->head.flip = 1;
    }
    actor->head.vx = 0.0f;
    if (jetpacBlinkPhase != 0) {
        actor->head.vy = -0.8f;
    } else {
        actor->head.vy = 0.8f;
    }
    actor->sprite = &jetpacFighterSprite;
}

void jetpacActorUpdateFighter(JetpacActor *actor) {
    switch (actor->head.state) {
    case 3:
        if (actor->head.timer == 0) {
            if (jetpacCheckLedgeCollision(actor->head.boxX1 + actor->head.x + actor->head.vx,
                              actor->head.boxY1 + actor->head.y + actor->head.vy,
                              actor->head.boxX2 + actor->head.x + actor->head.vx,
                              actor->head.boxY2 + actor->head.y + actor->head.vy, 1) >= 0) {
                jetpacActorExplode(actor);
            } else {
                actor->lifetime--;
            }
            if (actor->lifetime == 0) {
                jetpacActorExplode(actor);
            }
        } else if (jetpacBlinkPhase != 0 && actor->head.y < 32.0f) {
            jetpacActorExplode(actor);
        }

        if (actor->head.state == 3) {
            jetpacCheckPlayerHit(actor);
        }
        if (actor->head.state == 4) {
            JetpacPlayer *playerData = &jetpacGame.players[jetpacGame.activePlayer];
            playerData->score += actor->points;
            return;
        }

        if (actor->head.timer != 0) {
            actor->head.timer--;
            if (jetpacBlinkPhase != 0) {
                actor->head.vy = -0.8f;
            } else {
                actor->head.vy = 0.8f;
            }
            if (actor->head.timer == 0) {
                if (actor->head.flip != 0) {
                    actor->head.vx = -1.6f;
                } else {
                    actor->head.vx = 1.6f;
                }
                actor->head.color[0] = 0xFF;
                actor->head.color[1] = 0xFF;
                actor->head.color[2] = 0xFF;
            }
        }

        if (actor->head.timer == 0 && (jetpacGame.stateTimer & 2)) {
            JetpacPlayerActor *player = &jetpacGame.player;

            if (jetpacGetEntityCenterY(&actor->head) < player->head.y + player->head.boxY2) {
                actor->head.vy = 0.8f;
            } else {
                actor->head.vy = -0.8f;
            }
        }
        actor->head.x += actor->head.vx;
        actor->head.y += actor->head.vy;
        break;
    case 4:
        actor->head.timer++;
        if (actor->head.timer >= 15) {
            actor->head.state = 0;
        }
        break;
    }
}

void jetpacActorInitHoming(JetpacActor *actor) {
    actor->update = jetpacActorUpdateHoming;
    actor->points = 50;
    if (actor->head.y < 88.0f) {
        actor->head.flip = 0;
    } else {
        actor->head.flip = 1;
    }
    jetpacActorSteerToPlayer(actor);
}

void jetpacActorInitSaucer(JetpacActor *actor) {
    actor->head.boxY2 = 8;
    actor->sprite = &jetpacSaucerSprite;
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
    JetpacPlayerActor *player = &jetpacGame.player;

    cx1 = jetpacGetEntityCenterX(&actor->head);
    cx2 = jetpacGetEntityCenterX(&player->head);
    dx = cx2 - cx1;
    if (cx1 < cx2) {
        dxw = dx - 256.0f;
    } else {
        dxw = dx + 256.0f;
    }
    dy = player->head.y + player->head.boxY2 - jetpacGetEntityCenterY(&actor->head);
    if (dy > 0.0f) {
        dyw = dy - 288.0;
    } else {
        dyw = dy + 192.0f;
    }
    if (((dx > 0.0f) ? dx : -dx) < ((dxw > 0.0f) ? dxw : -dxw)) {
        rx = dx;
    } else {
        rx = dxw;
    }
    if (((dy > 0.0f) ? dy : -dy) < ((dyw > 0.0f) ? dyw : -dyw)) {
        ry = dy;
    } else {
        ry = dyw;
    }
    actor->head.vx = jetpacActorAccelClamp(rx, actor->head.vx);
    actor->head.vy = jetpacActorAccelClamp(ry, actor->head.vy);
}

void jetpacActorUpdateHoming(JetpacActor *actor) {
    s32 ledgeIndex;

    switch (actor->head.state) {
    case 3:
        jetpacActorSteerToPlayer(actor);
        ledgeIndex = jetpacCheckLedgeCollision(actor->head.boxX1 + actor->head.x + actor->head.vx,
                            actor->head.boxY1 + actor->head.y + actor->head.vy,
                            actor->head.boxX2 + actor->head.x + actor->head.vx,
                            actor->head.boxY2 + actor->head.y + actor->head.vy, 1);
        if (ledgeIndex >= 0) {
            jetpacBounceOffLedge(actor, ledgeIndex);
        }
        if (jetpacCheckPlayerHit(actor) == 0) {
            if ((actor->head.y + actor->head.vy) < 24.0f) {
                actor->head.vy = -actor->head.vy;
            }
            actor->head.y += actor->head.vy;
            actor->head.x += actor->head.vx;
        }
        break;
    case 4:
        actor->head.timer++;
        if (actor->head.timer >= 15) {
            actor->head.state = 0;
        }
        break;
    }
}

void jetpacActorHopImpulse(JetpacActor *actor) {
    s32 divisor = actor->head.timer % 4 + 1;

    actor->head.vy = -1.2 / divisor;
    actor->head.timer++;
}

void jetpacActorInitHop(JetpacActor *actor) {
    actor->update = jetpacActorUpdateHop;
    actor->points = 60;
    actor->head.timer = jetpacRandFloat() * 16.0f;
    if (actor->head.y < 88.0f) {
        actor->head.vx = -1.2f;
    } else {
        actor->head.vx = 1.2f;
    }
    jetpacActorHopImpulse(actor);
    actor->sprite = &jetpacHopSprite;
}

void jetpacActorUpdateHop(JetpacActor *actor) {
    s32 ledgeIndex;
    f32 prevVy;
    f32 bouncedVy;

    switch (actor->head.state) {
    case 3:
        actor->head.vy += 0.005;
        prevVy = actor->head.vy;
        ledgeIndex = jetpacCheckLedgeCollision(actor->head.boxX1 + actor->head.x + actor->head.vx,
                            actor->head.boxY1 + actor->head.y + actor->head.vy,
                            actor->head.boxX2 + actor->head.x + actor->head.vx,
                            actor->head.boxY2 + actor->head.y + actor->head.vy, 1);
        if (ledgeIndex >= 0) {
            jetpacBounceOffLedge(actor, ledgeIndex);
            bouncedVy = actor->head.vy;
            if (prevVy > 0.0f && bouncedVy < 0.0f) {
                jetpacActorHopImpulse(actor);
            }
        }
        if (jetpacCheckPlayerHit(actor) == 0) {
            if ((actor->head.y + actor->head.vy) < 24.0f) {
                actor->head.vy = -actor->head.vy;
            }
            actor->head.y += actor->head.vy;
            actor->head.x += actor->head.vx;
        }
        break;
    case 4:
        actor->head.timer++;
        if (actor->head.timer >= 15) {
            actor->head.state = 0;
        }
        break;
    }
}

void jetpacActorInitCross(JetpacActor *actor) {
    actor->head.boxY2 = 14;
    actor->sprite = &jetpacCrossSprite;
    jetpacActorInitStraight(actor, 1.2f, 0.3f);
    actor->update = jetpacActorUpdateStraight;
}

void jetpacActorInitBlob(JetpacActor *actor) {
    actor->head.boxY2 = 14;
    actor->sprite = &jetpacBlobSprite;
    jetpacActorInitHoming(actor);
}

s32 jetpacKillActorInBox(f32 x1, f32 y1, f32 x2, f32 y2) {
    JetpacActor *actor = jetpacGame.actors;
    JetpacPlayer *playerData;
    s32 i;

    for (i = 0; i < 6; i++, actor++) {
        if (actor->head.state == 3) {
            if (jetpacCheckAabbOverlapWrapped(x1, y1, x2, y2,
                              actor->head.x + actor->head.boxX1,
                              actor->head.y + actor->head.boxY1,
                              actor->head.x + actor->head.boxX2,
                              actor->head.y + actor->head.boxY2)) {
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
            if (actor->head.state > 0 && actor->update != NULL) {
                actor->update(actor);
                if (actor->head.x < 0.0f) {
                    actor->head.x += 256.0f;
                }
                if (actor->head.x > 256.0f) {
                    actor->head.x -= 256.0f;
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
            if (actor->head.state >= 2 && actor->sprite != NULL) {
                jetpacDrawActor(actor);
            }
        }
    }
}
