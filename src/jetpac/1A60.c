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
void jetpacSnapActorToGrid(JetpacActor *arg0);
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
void jetpacGridAddTiledSprite(JetpacSprite *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4);
void dlAppendTextureLoad(Gfx **arg0, s32 arg1);
void func_8070F2C8(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void dlAppendTextureRectangle(Gfx **arg0, s16 arg1, s16 arg2);
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
void jetpacNextPlayerOrGameOver(JetpacPlayer *arg0);
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

void jetpacUpdateExplosion(JetpacExplosion *arg0) {
    volatile s32 frame; // FAKE: volatile forces stack home
    s32 timer;

    timer = arg0->timer;
    frame = (s32)(((f32)timer / 14.0f) * 6.0f);
    if ((timer % 7) == 0) {
        if (jetpacRandFloat() < 0.5) {
            arg0->color[1] = 0;
        } else {
            arg0->color[1] = 0xFF;
        }
        if (jetpacRandFloat() < 0.5) {
            arg0->color[2] = 0;
        } else {
            arg0->color[2] = 0xFF;
        }
    }
    jetpacGridAddTiledSprite(&D_8002B9C0[frame], arg0->x, arg0->y, arg0->color, 0);
    arg0->timer++;
}

s32 jetpacGetAnimFrame(JetpacActor *arg0) {
    return (s32)(((s32)arg0->x + arg0->unk1C) / 2) % 4;
}

void jetpacSetFlying(JetpacActor *arg0, s32 arg1) {
    if (arg1 == 0 && arg0->unk30 != 0) {
        arg0->x = (f32)((s32)arg0->x & 0xFFFE);
    } else if (arg1 != 0 && arg0->unk30 == 0) {
        jetpacSnapActorToGrid(arg0);
    }
    arg0->unk1C = 0;
    arg0->unk24 = 0x10;
    arg0->unk30 = arg1;
}

JetpacActor *jetpacFindFreeLaser(JetpacState *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0->actors[i].unk14 == 0) {
            return &arg0->actors[i];
        }
    }
    return NULL;
}

void jetpacResetActorState(JetpacActor *arg0) {
    arg0->unk14 = 4;
    arg0->unk2C = 0;
}
s32 jetpacBoxOverlapsItems(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 jetpacKillActorInBox(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 jetpacCheckLedgeCollision(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4);

void jetpacUpdateLaser(JetpacActor *arg0) {
    s32 pad1;
    f32 x1;
    f32 y1;
    f32 x2;
    f32 y2;
    s32 n;
    s32 step;
    s32 a;

    if (arg0->unk14 == 3 && (u32)arg0->unk40 < (u32)arg0->unk2C) {
        jetpacResetActorState(arg0);
    }
    if (arg0->unk14 == 4 && arg0->unk24 == arg0->unk1C) {
        arg0->unk14 = 0;
        arg0->unk2C = 0;
    }
    if (arg0->unk14 != 0) {
        if (arg0->unk14 == 3) {
            n = arg0->unk2C;
            if (arg0->unk18 != 0) {
                x1 = (f32)arg0->unk1C;
                step = n < 4 ? n : 4;
                x2 = (f32)(step * 8) + x1;
            } else {
                x2 = (f32)arg0->unk24;
                step = n < 4 ? n : 4;
                x1 = x2 - (f32)(step * 8);
            }
            y1 = (f32)arg0->unk20;
            y2 = (f32)arg0->unk28;
            if (jetpacKillActorInBox(x1, y1, x2, y2) != 0) {
                jetpacResetActorState(arg0);
                return;
            }
            if (jetpacCheckLedgeCollision(x1, y1, x2, y2, 0) >= 0) {
                jetpacResetActorState(arg0);
                return;
            }
            if (jetpacBoxOverlapsItems(x1, y1, x2, y2) != 0) {
                jetpacResetActorState(arg0);
                return;
            }
            if (arg0->unk18 != 0) {
                arg0->unk1C = arg0->unk1C - 8;
                if (arg0->unk2C >= 0xD) {
                    arg0->unk24 = arg0->unk24 - 8;
                }
            } else {
                arg0->unk24 = arg0->unk24 + 8;
                if (arg0->unk2C >= 0xD) {
                    arg0->unk1C = arg0->unk1C + 8;
                }
            }
            arg0->unk2C = arg0->unk2C + 1;
            return;
        }
        if (arg0->unk14 == 4) {
            a = arg0->unk24 - arg0->unk1C;
            if (arg0->unk2C + a / 8 >= 0xD) {
                if (arg0->unk18 != 0) {
                    arg0->unk24 = arg0->unk24 - 8;
                } else {
                    arg0->unk1C = arg0->unk1C + 8;
                }
            }
            arg0->unk2C = arg0->unk2C + 1;
        }
    }
}

void jetpacDrawLaserSegment(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5) {
    jetpacGridAddTiledSprite(&D_8002C4D0[arg0], *arg1, arg3, arg4, arg5);
    *arg1 += arg2;
    if (*arg1 < 0) {
        *arg1 += 0x100;
    }
}

void jetpacDrawLaser(JetpacActor *arg0) {
    s32 pos;
    s32 dir;
    s32 frame;
    s32 sub;
    s32 count;
    s32 i;
    s32 y;
    s32 flip;

    dir = 0;
    sub = arg0->unk14;
    flip = arg0->unk18;
    frame = 0;
    if (sub >= 2) {
        y = arg0->y;
        count = (arg0->unk24 - arg0->unk1C) / 8;
        dir = -8;
        if (sub == 4) {
            frame = arg0->unk2C;
        }
        if (flip != 0) {
            dir = 8;
            pos = arg0->unk1C;
        } else {
            pos = arg0->unk24 - 8;
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
            jetpacDrawLaserSegment(spr, &pos, dir, y, arg0->color, flip);
            frame++;
        }
    }
}


void jetpacPlaySound(s32 arg0);

void jetpacFireLaser(arg0)
JetpacActor *arg0;
{
    JetpacActor *p;
    s32 ix;
    s32 iy;
    s32 col;
    f32 vy;
    f32 absVy;

    p = jetpacFindFreeLaser((JetpacState *)arg0);
    if (p == NULL) {
        vy = arg0->vy;
        if (vy > 0.0f) {
            absVy = vy;
        } else {
            absVy = -vy;
        }
        if (absVy < 0.01f && arg0->y < 152.0f) {
            jetpacPlaySound(6);
        }
    } else {
        p->unk18 = arg0->unk18;
        if (p->unk18 != 0) {
            p->x = (f32)(((s32)(arg0->x + (f32)arg0->unk1C) / 8) * 8);
            p->vx = -8.0f;
        } else {
            p->x = (f32)(((s32)(arg0->x + (f32)arg0->unk24 + 6.0f) / 8) * 8);
            p->vx = 8.0f;
        }
        ix = (s32)p->x;
        p->unk1C = ix;
        p->unk24 = ix;
        p->y = arg0->y + 10.0f;
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
s32 jetpacCheckLedgeCollision(f32, f32, f32, f32, s32);
s32 jetpacCheckLedgeEdge(s32, s32, s32);
s32 jetpacIsOverRocket(f32);
void jetpacSetState(s32);

void jetpacUpdatePlayerMovement(JetpacActor *arg0) {
    JetpacPlayer *sp54;
    f32 mx;
    f32 my;
    f32 vx;
    f32 vy;
    s32 a2;
    s32 a1;
    f32 px;
    s32 sp34;
    s32 sp30;
    s32 idx;
    s32 u;

    s32 fire;

    sp54 = &jetpacGame.players[D_8002EF74];
    fire = jetpacGame.unk0 & 0x4000;
    sp34 = jetpacGame.unk0 & 0x200;
    sp30 = jetpacGame.unk0 & 0x100;
    a2 = jetpacGame.unk0 & 0x8000;
    a1 = jetpacGame.unk0 & 0x2030;
    if (fire && arg0->unk38 >= 5) {
        jetpacFireLaser(arg0, a1, a2);
        arg0->unk38 = 0;
    } else if (arg0->unk38 < 5) {
        arg0->unk38++;
    }
    if (a2 != 0 && (arg0->unk30 == 0 || a1 == 0)) {
        jetpacSetFlying(arg0, 1);
        arg0->vy -= 0.2f;
        u = arg0->unk30;
    } else if ((u = arg0->unk30) != 0) {
        if (a1 != 0) {
            arg0->vy = 0.0f;
            u = (*(volatile s32 *)&arg0->unk30); // FAKE: volatile forces reload
        } else {
            arg0->vy += 0.2;
            u = (*(volatile s32 *)&arg0->unk30); // FAKE: volatile forces reload
        }
    }
    if (sp34 != 0) {
        arg0->vx -= 0.33333334f;
        if (arg0->unk18 == 0 && arg0->vx <= 0.0f) {
            arg0->unk18 = 1;
            jetpacSetFlying(arg0, arg0->unk30);
        }
        u = arg0->unk30;
    } else if (sp30 != 0) {
        arg0->vx += 0.33333334f;
        if (arg0->unk18 != 0 && arg0->vx >= 0.0f) {
            arg0->unk18 = 0;
            jetpacSetFlying(arg0, arg0->unk30);
        }
        u = arg0->unk30;
    } else {
        vx = arg0->vx;
        if (vx > 0.0f) {
            arg0->vx = vx - 0.16666667f;
            u = (*(volatile s32 *)&arg0->unk30); // FAKE: volatile forces reload
        } else if (vx < 0.0f) {
            arg0->vx = vx + 0.16666667f;
            u = (*(volatile s32 *)&arg0->unk30); // FAKE: volatile forces reload
        }
    }
    if (u != 0) {
        mx = 2.0f;
        my = 2.0f;
    } else {
        mx = 1.0f;
        my = 0.0f;
    }
    vx = arg0->vx;
    arg0->vx = (vx < -mx) ? -mx : ((mx < vx) ? mx : vx);
    vy = arg0->vy;
    arg0->vy = (vy < -my) ? -my : ((my < vy) ? my : vy);
    if (arg0->vx < 0.1 && arg0->vx > -0.1) {
        arg0->vx = 0.0f;
    }
    if (arg0->vy < 0.1 && arg0->vy > -0.1) {
        arg0->vy = 0.0f;
    }
    vx = arg0->vx;
    if (arg0->unk30 != 0) {
        idx = jetpacCheckLedgeCollision(arg0->unk1C + arg0->x + vx, arg0->unk20 + arg0->y + arg0->vy,
                                        arg0->unk24 + arg0->x + vx, arg0->unk28 + arg0->y + arg0->vy, 1);
        if (idx >= 0) {
            if ((f32)jetpacGame.ledges[idx].unk28 <= arg0->unk20 + arg0->y) {
                arg0->vy *= -0.4f;
                if ((arg0->vy > 0.0f ? arg0->vy : -arg0->vy) <= 0.15f) {
                    arg0->vy = 0.0f;
                }
            } else if (arg0->unk28 + arg0->y <= (f32)jetpacGame.ledges[idx].unk20) {
                arg0->unk34 = idx;
                arg0->vy = 0.0f;
                jetpacSetFlying(arg0, 0);
                arg0->y = jetpacGame.ledges[idx].unk4 - 24.0f;
            } else {
                arg0->vx *= -0.5f;
            }
        }
    } else {
        idx = jetpacCheckLedgeEdge(arg0->unk34, (s32)(arg0->unk1C + arg0->x + vx), (s32)(arg0->unk24 + arg0->x + vx));
        switch (idx) {
        case -2:
        case 2:
            jetpacSetFlying(arg0, 1);
            arg0->vy = -0.5f;
            break;
        case -1:
        case 1:
            if (arg0->unk18 == 0 && sp34 == 0) {
                arg0->vx = 1.0f;
            } else if (sp30 == 0) {
                arg0->vx = -1.0f;
            }
            break;
        }
    }
    arg0->x = arg0->x + arg0->vx;
    if (arg0->x + arg0->unk24 > 256.0f) {
        arg0->x -= 256.0f;
    }
    if (arg0->x + arg0->unk1C < 0.0f) {
        arg0->x += 256.0f;
    }
    arg0->y = arg0->y + arg0->vy;
    if (arg0->y < 18.0f) {
        arg0->y = 18.0f;
        arg0->vy = 0;
    }
    if (arg0->y > 168.0f) {
        arg0->y = 168.0f;
    }
    if (jetpacIsOverRocket(arg0->x) != 0 && sp54->unkC == 8 && arg0->y > 152.0f) {
        jetpacSetState(4);
    }
}

void jetpacUpdatePlayerDeath(JetpacActor *arg0) {
    JetpacPlayer *p = &jetpacGame.players[jetpacGame.currentSession];

    if (arg0->unk2C < 14) {
        arg0->unk2C++;
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
void jetpacPlaySound(s32);
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

void jetpacSnapActorToGrid(JetpacActor *arg0) {
    if (arg0->unk44 >= 0xE) {
        arg0->unk44 = 0;
        arg0->unk3C = (s32)arg0->x & 0xFFF8;
        arg0->unk40 = (s32)(arg0->y + 7.0f);
    }
}
