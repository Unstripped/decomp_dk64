#include "common.h"
typedef struct JetpacActor {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ void (*unk48)(struct JetpacActor *);
    /* 0x4C */ void *unk4C;
} JetpacActor;
#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
typedef struct {
    u8 pad[0x18];
} Struct_D_8002E800;
extern Struct_D_8002E800 D_8002E800[];
extern Struct_D_8002E800 D_8002E848[];
typedef struct {
    s32 stage;
    s32 score;
    u8 pad8[0x194 - 8];
} JetpacPlayer;

typedef struct {
    u8 pad0[0x1C];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[0x34 - 0x2C];
} J4Ledge;

typedef struct {
    u8 pad0[0x1C];
    JetpacPlayer players[2];
    s32 currentPlayer;
    u8 pad348[0x350 - 0x348];
    J4Ledge ledges[4];
    JetpacActor player;
    u8 pad470[0x790 - 0x470];
    s32 unk790;
} JetpacGlobal;

extern JetpacGlobal jetpacGame;
s32 jetpacCheckAabbOverlapWrapped(f32, f32, f32, f32, f32, f32, f32, f32);
void jetpacActorUpdateStraight(JetpacActor *actor);

extern void *D_8002E890;
extern void *D_8002E8C0;
extern void *D_8002E8D8;
extern void *D_8002E830;
extern void *D_8002E8A8;
extern s32 D_8002BA6C;
extern void *D_8002E878;
void func_80029F7C(JetpacActor *);
void jetpacActorUpdateHop(JetpacActor *);
void func_8002A67C(JetpacActor *);
void jetpacActorUpdateBounce(JetpacActor *actor);
f32 jetpacActorAccelClamp(f32 arg0, f32 arg1);
f32 jetpacRandFloat(void);
void func_80029B90(JetpacActor *);
void jetpacActorUpdateWander(JetpacActor *);
void jetpacActorInitHoming(JetpacActor *arg0);
void jetpacActorUpdateHoming(JetpacActor *actor);
f32 jetpacGetEntityCenterY(JetpacActor *);
extern f32 D_8002F054;
extern s32 D_8002F078;
void jetpacActorSteerToPlayer(JetpacActor *actor);
s32 jetpacIsSpawnDelay(void);
void jetpacDrawActor(JetpacActor *actor);
JetpacActor *jetpacFindFreeActor(void);
extern JetpacActor jetpacActors[];
extern JetpacActor D_8002E964;
extern JetpacActor D_8002E914;
JetpacActor *jetpacAllocActor(void);
extern s32 D_8002E8F0;
void jetpacSpawnActor(void);
s32 jetpacCheckLedgeCollision(f32, f32, f32, f32, s32);
s32 jetpacCheckPlayerHit(JetpacActor *);
void jetpacBounceOffLedge(JetpacActor *, s32);
void jetpacPlaySound(s32 arg0);
void jetpacGridAddTiledSprite(void *, s32, s32, void *, s32);
void jetpacUpdateExplosion(void *);
Gfx *textDrawString(Gfx *, s32, s16, s16, s32);
void func_80029640(JetpacActor *actor, f32 a1, f32 a2);
void func_800298C8(JetpacActor *actor);
extern u8 D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3;
extern u8 D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC;

JetpacActor *jetpacFindFreeActor(void) {
    JetpacActor *actor = jetpacActors;
    s32 i = 0;

    do {
        if (actor->unk14 == 0) {
            return actor;
        }
        actor++;
    } while (++i < 6);
    return NULL;
}

extern s32 D_8002F064;
extern s32 D_8002F07C;
extern JetpacActor jetpacPlayer;
void jetpacSnapActorToGrid(JetpacActor *);
void jetpacActorExplode(JetpacActor *);

s32 jetpacCheckPlayerHit(JetpacActor *arg0) {
    s32 pad[7];
    f32 loc[2];
    s32 ret;
    JetpacActor *p;
    f32 ax;
    f32 ay;
    f32 x2;
    f32 y2;
    f32 px;
    f32 py;

    p = &jetpacGame.player;
    ax = arg0->unk0;
    ay = arg0->unk4;
    px = p->unk0;
    py = p->unk4;
    x2 = (f32)arg0->unk24 + ax;
    y2 = (f32)arg0->unk28 + ay;
    loc[1] = (f32)p->unk24 + px - 2.0f;
    loc[0] = (f32)p->unk28 + py;
    ret = 0;
    ax += (f32)arg0->unk1C;
    ay += (f32)arg0->unk20;
    px += (f32)(p->unk1C + 2);
    py += (f32)(p->unk20 + 4);
    if (p->unk14 == 3) {
        ret = jetpacCheckAabbOverlapWrapped(ax, ay, x2, y2, px, py, loc[1], loc[0]);
    }
    if (ret != 0) {
        D_8002F064 = 4;
        D_8002F07C = 0;
        jetpacSnapActorToGrid(&jetpacPlayer);
        jetpacActorExplode(arg0);
    }
    return ret;
}

void jetpacActorExplode(JetpacActor *arg0) {
    arg0->unk14 = 4;
    arg0->unk2C = 0;
    arg0->unk38 = 0;
    arg0->unk30 = (s32)arg0->unk0 & 0xFFF8;
    arg0->unk34 = (s32)arg0->unk4 & 0xFFF8;
    jetpacPlaySound(5);
}

void jetpacDrawActor(JetpacActor *arg0) {
    s32 temp_v0 = arg0->unk14;

    if (temp_v0 == 3) {
        jetpacGridAddTiledSprite(arg0->unk4C, (s32)arg0->unk0, (s32)arg0->unk4, &arg0->unk10, arg0->unk18);
        return;
    }
    if (temp_v0 == 4) {
        jetpacUpdateExplosion(&arg0->unk30);
        if (arg0->unk38 < 7) {
            jetpacGridAddTiledSprite(arg0->unk4C, (s32)arg0->unk0, (s32)arg0->unk4, &arg0->unk10, arg0->unk18);
        }
    }
}

JetpacActor *jetpacAllocActor(void) {
    s32 pad;
    JetpacActor *actor;
    JetpacActor sp20;

    actor = jetpacFindFreeActor();
    sp20 = D_8002E914;
    if (actor == NULL) {
        return NULL;
    }
    *actor = sp20;
    actor->unk0 = 0.0f;
    actor->unk4 = (f32)((((s32)(jetpacRandFloat() * 15.0f) % 15) * 8) + 32);
    switch ((s32)(jetpacRandFloat() * 4.0f) % 4) {
    case 0:
        actor->unk10 = 0;
        break;
    case 1:
        actor->unk11 = 0;
        break;
    case 2:
        actor->unk10 = 0;
        actor->unk12 = 0;
        break;
    case 3:
        actor->unk11 = 0;
        actor->unk12 = 0;
        break;
    }
    return actor;
}

extern void (*D_8002E8F4[])(JetpacActor *);

void jetpacSpawnActor(void) {
    s32 pad[2];
    void (*fn)(JetpacActor *);
    JetpacActor *actor;
    JetpacPlayer *p;
    s32 idx;

    p = &jetpacGame.players[jetpacGame.currentPlayer];
    idx = p->stage;
    fn = D_8002E8F4[idx % 8];
    actor = jetpacAllocActor();
    if (actor != NULL) {
        fn(actor);
        actor->unk14 = 3;
    }
}

void jetpacBounceOffLedge(JetpacActor *arg0, s32 arg1) {
    J4Ledge *l;
    f32 ax1;
    f32 ax2;
    f32 ay1;
    f32 lx1;
    f32 lx2;
    f32 ay2;
    f32 ly1;
    f32 ly2;

    l = &jetpacGame.ledges[arg1];
    ax1 = arg0->unk0 + (f32)arg0->unk1C;
    ax2 = arg0->unk0 + (f32)arg0->unk24;
    lx1 = l->unk1C;
    lx2 = l->unk24;
    ay1 = arg0->unk4 + (f32)arg0->unk20;
    ay2 = arg0->unk4 + (f32)arg0->unk28;
    ly1 = l->unk20;
    ly2 = l->unk28;
    if ((lx2 <= ax1 && lx2 <= ax2) || (ax2 <= lx1 && ax1 <= lx1)) {
        arg0->unk8 = -arg0->unk8;
    }
    if ((ly2 <= ay1 && ly2 <= ay2) || (ay2 <= ly1 && ay1 <= ly1)) {
        arg0->unkC = -arg0->unkC;
    }
}

void func_80029640(JetpacActor *actor, f32 a1, f32 a2) {
    s32 cnt2;
    s32 cnt1;
    s32 i;
    JetpacActor *p;

    cnt2 = cnt1 = 0;
    actor->unk44 = 0x19;
    if (actor->unk4 < 88.0f) {
        actor->unk8 = a1;
        actor->unk18 = 0;
    } else {
        actor->unk8 = -a1;
        actor->unk18 = 1;
    }
    p = jetpacActors;
    for (i = 0; i != 6; i++) {
        if (p->unk14 > 0) {
            if (p->unkC == 0.0f) {
                cnt1++;
            } else {
                cnt2++;
            }
        }
        p++;
    }
    if (cnt1 == 3) {
        actor->unkC = a2;
    } else if (cnt2 == 3) {
        actor->unkC = 0.0f;
    } else {
        if ((s32)(jetpacRandFloat() * 2) % 2) {
            actor->unkC = 0.0f;
        } else {
            actor->unkC = a2;
        }
    }
}

void jetpacActorUpdateStraight(JetpacActor *arg0) {
    switch (arg0->unk14) {
    case 3:
        if (jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                          (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                          (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                          (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1) >= 0) {
            jetpacActorExplode(arg0);
        } else if (jetpacCheckPlayerHit(arg0) == 0) {
            arg0->unk0 += arg0->unk8;
            arg0->unk4 += arg0->unkC;
        }
        break;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        break;
    }
}

void func_80029884(JetpacActor *actor) {
    actor->unk28 = 0xB;
    func_80029640(actor, 1.6f, 0.5f);
    actor->unk48 = func_800298C8;
}

void func_800298C8(JetpacActor *actor) {
    jetpacActorUpdateStraight(actor);
    actor->unk4C = &D_8002E800[(s32)actor->unk0 % 2];
}

void func_8002992C(JetpacActor *arg0) {
    arg0->unk48 = jetpacActorUpdateBounce;
    arg0->unk44 = 0x50;
    if (arg0->unk4 < 88.0f) {
        arg0->unk8 = -1.2f;
    } else {
        arg0->unk8 = 1.2f;
    }
    arg0->unkC = -0.8f;
    arg0->unk4C = &D_8002E830;
}

void jetpacActorUpdateBounce(JetpacActor *arg0) {
    s32 res;

    switch (arg0->unk14) {
    case 3:
        res = jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                            (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1);
        if (res >= 0) {
            jetpacBounceOffLedge(arg0, res);
        }
        if (jetpacCheckPlayerHit(arg0) == 0) {
            if ((arg0->unk4 + arg0->unkC) < 24.0f) {
                arg0->unkC = -arg0->unkC;
            }
            arg0->unk4 += arg0->unkC;
            arg0->unk0 += arg0->unk8;
            if ((s32)arg0->unk0 & 2) {
                arg0->unk18 ^= 1;
            }
        }
        break;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        break;
    }
}

void func_80029AF8(JetpacActor *arg0) {
    arg0->unk48 = jetpacActorUpdateWander;
    arg0->unk44 = 0x28;
    if (arg0->unk4 < 88.0f) {
        arg0->unk8 = -1.2f;
    } else {
        arg0->unk8 = 1.2f;
    }
    func_80029B90(arg0);
    arg0->unk2C = (s32)((jetpacRandFloat() * 60.0f) + 10.0f);
}

void func_80029B90(JetpacActor *arg0) {
    if ((f64)arg0->unkC == 0.0) {
        if ((f64)jetpacRandFloat() < 0.5) {
            arg0->unkC = -0.6f;
            return;
        }
        arg0->unkC = 0.6f;
        return;
    }
    arg0->unkC = 0.0f;
}

void jetpacActorUpdateWander(JetpacActor *arg0) {
    s32 res;

    switch (arg0->unk14) {
    case 3:
        if (--arg0->unk2C == 0) {
            func_80029B90(arg0);
            arg0->unk2C = (s32)((jetpacRandFloat() * 60.0f) + 10.0f);
        }
        res = jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                            (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1);
        if (res >= 0) {
            jetpacBounceOffLedge(arg0, res);
            if (arg0->unk2C < 10) {
                arg0->unk2C = 10;
            }
        }
        if (jetpacCheckPlayerHit(arg0) == 0) {
            if ((arg0->unk4 + arg0->unkC) < 24.0f) {
                arg0->unkC = -arg0->unkC;
            }
            arg0->unk4 += arg0->unkC;
            arg0->unk0 += arg0->unk8;
            arg0->unk4C = &D_8002E848[(s32)(arg0->unk0 / 4) % 2];
        }
        break;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        break;
    }
}

void func_80029E0C(JetpacActor *arg0) {
    arg0->unk48 = func_80029F7C;
    arg0->unk44 = 0x37;
    arg0->unk2C = (s32)((jetpacRandFloat() * 60.0f) + 10.0f);
    arg0->unk40 = (u32)((jetpacRandFloat() * 180.0f) + 10.0f);
    arg0->unk28 = 8;
    if (arg0->unk4 < 88.0f) {
        arg0->unk18 = 0;
    } else {
        arg0->unk18 = 1;
    }
    arg0->unk8 = 0.0f;
    if (D_8002BA6C != 0) {
        arg0->unkC = -0.8f;
    } else {
        arg0->unkC = 0.8f;
    }
    arg0->unk4C = &D_8002E878;
}

void func_80029F7C(JetpacActor *arg0) {
    switch (arg0->unk14) {
    case 3:
        if (arg0->unk2C == 0) {
            if (jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                              (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                              (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                              (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1) >= 0) {
                jetpacActorExplode(arg0);
            } else {
                arg0->unk40--;
            }
            if (arg0->unk40 == 0) {
                jetpacActorExplode(arg0);
            }
        } else if (D_8002BA6C != 0 && arg0->unk4 < 32.0f) {
            jetpacActorExplode(arg0);
        }

        if (arg0->unk14 == 3) {
            jetpacCheckPlayerHit(arg0);
        }
        if (arg0->unk14 == 4) {
            JetpacPlayer *p = &jetpacGame.players[jetpacGame.currentPlayer];
            p->score += arg0->unk44;
            return;
        }

        if (arg0->unk2C != 0) {
            arg0->unk2C--;
            if (D_8002BA6C != 0) {
                arg0->unkC = -0.8f;
            } else {
                arg0->unkC = 0.8f;
            }
            if (arg0->unk2C == 0) {
                if (arg0->unk18 != 0) {
                    arg0->unk8 = -1.6f;
                } else {
                    arg0->unk8 = 1.6f;
                }
                arg0->unk10 = 0xFF;
                arg0->unk11 = 0xFF;
                arg0->unk12 = 0xFF;
            }
        }

        if (arg0->unk2C == 0 && (jetpacGame.unk790 & 2)) {
            if (jetpacGetEntityCenterY(arg0) < D_8002F054 + (f32)D_8002F078) {
                arg0->unkC = 0.8f;
            } else {
                arg0->unkC = -0.8f;
            }
        }
        arg0->unk0 += arg0->unk8;
        arg0->unk4 += arg0->unkC;
        return;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        return;
    }
}

void jetpacActorInitHoming(JetpacActor *arg0) {
    arg0->unk48 = jetpacActorUpdateHoming;
    arg0->unk44 = 0x32;
    if (arg0->unk4 < 88.0f) {
        arg0->unk18 = 0;
    } else {
        arg0->unk18 = 1;
    }
    jetpacActorSteerToPlayer(arg0);
}

void func_8002A2AC(JetpacActor *arg0) {
    arg0->unk28 = 8;
    arg0->unk4C = &D_8002E890;
    jetpacActorInitHoming(arg0);
}

f32 jetpacActorAccelClamp(f32 arg0, f32 arg1) {
    f64 d;
    f64 r;

    if (arg0 < 0.0f) {
        arg1 = arg1 - 0.08;
    } else {
        arg1 = arg1 + 0.08;
    }
    d = arg1;
    r = d < -1.2 ? -1.2 : (d > 1.2 ? 1.2 : d);
    return r;
}

f32 jetpacGetEntityCenterX(JetpacActor *);

void jetpacActorSteerToPlayer(JetpacActor *arg0) {
    f32 cx2;
    f32 dx;
    f32 dxw;
    f32 rx;
    f32 dy;
    f32 dyw;
    f32 ry;
    f32 cx1;

    cx1 = jetpacGetEntityCenterX(arg0);
    cx2 = jetpacGetEntityCenterX(&jetpacPlayer);
    dx = cx2 - cx1;
    if (cx1 < cx2) {
        dxw = dx - 256.0f;
    } else {
        dxw = dx + 256.0f;
    }
    dy = D_8002F054 + (f32)D_8002F078 - jetpacGetEntityCenterY(arg0);
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
    arg0->unk8 = jetpacActorAccelClamp(rx, arg0->unk8);
    arg0->unkC = jetpacActorAccelClamp(ry, arg0->unkC);
}

void jetpacActorUpdateHoming(JetpacActor *arg0) {
    s32 res;

    switch (arg0->unk14) {
    case 3:
        jetpacActorSteerToPlayer(arg0);
        res = jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                            (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1);
        if (res >= 0) {
            jetpacBounceOffLedge(arg0, res);
        }
        if (jetpacCheckPlayerHit(arg0) == 0) {
            if ((arg0->unk4 + arg0->unkC) < 24.0f) {
                arg0->unkC = -arg0->unkC;
            }
            arg0->unk4 += arg0->unkC;
            arg0->unk0 += arg0->unk8;
        }
        break;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        break;
    }
}

void func_8002A67C(JetpacActor *arg0) {
    s32 t = arg0->unk2C % 4 + 1;

    arg0->unkC = -1.2 / (f64)t;
    arg0->unk2C = arg0->unk2C + 1;
}

void func_8002A6C0(JetpacActor *arg0) {
    arg0->unk48 = jetpacActorUpdateHop;
    arg0->unk44 = 0x3C;
    arg0->unk2C = (s32)(jetpacRandFloat() * 16.0f);
    if (arg0->unk4 < 88.0f) {
        arg0->unk8 = -1.2f;
    } else {
        arg0->unk8 = 1.2f;
    }
    func_8002A67C(arg0);
    arg0->unk4C = &D_8002E8A8;
}

void jetpacActorUpdateHop(JetpacActor *arg0) {
    s32 res;
    f32 prev;
    f32 cur;

    switch (arg0->unk14) {
    case 3:
        arg0->unkC = arg0->unkC + 0.005;
        prev = arg0->unkC;
        res = jetpacCheckLedgeCollision((f32)arg0->unk1C + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk20 + arg0->unk4 + arg0->unkC,
                            (f32)arg0->unk24 + arg0->unk0 + arg0->unk8,
                            (f32)arg0->unk28 + arg0->unk4 + arg0->unkC, 1);
        if (res >= 0) {
            jetpacBounceOffLedge(arg0, res);
            cur = arg0->unkC;
            if (prev > 0.0f && cur < 0.0f) {
                func_8002A67C(arg0);
            }
        }
        if (jetpacCheckPlayerHit(arg0) == 0) {
            if ((arg0->unk4 + arg0->unkC) < 24.0f) {
                arg0->unkC = -arg0->unkC;
            }
            arg0->unk4 += arg0->unkC;
            arg0->unk0 += arg0->unk8;
        }
        break;
    case 4:
        arg0->unk2C++;
        if (arg0->unk2C >= 15) {
            arg0->unk14 = 0;
        }
        break;
    }
}

void func_8002A8F0(JetpacActor *actor) {
    actor->unk28 = 0xE;
    actor->unk4C = &D_8002E8C0;
    func_80029640(actor, 1.2f, 0.3f);
    actor->unk48 = jetpacActorUpdateStraight;
}

void func_8002A944(JetpacActor *arg0) {
    arg0->unk28 = 0xE;
    arg0->unk4C = &D_8002E8D8;
    jetpacActorInitHoming(arg0);
}

s32 jetpacKillActorInBox(f32 x1, f32 y1, f32 x2, f32 y2) {
    JetpacActor *actor = jetpacActors;
    JetpacPlayer *playerData;
    s32 i;

    for (i = 0; i < 6; i++, actor++) {
        if (actor->unk14 == 3) {
            if (jetpacCheckAabbOverlapWrapped(x1, y1, x2, y2,
                              actor->unk0 + (f32)actor->unk1C,
                              actor->unk4 + (f32)actor->unk20,
                              actor->unk0 + (f32)actor->unk24,
                              actor->unk4 + (f32)actor->unk28)) {
                playerData = &jetpacGame.players[jetpacGame.currentPlayer];
                jetpacActorExplode(actor);
                playerData->score += actor->unk44;
                return 1;
            }
        }
    }
    return 0;
}

void jetpacInitActors(void) {
    s32 i;
    JetpacActor sp24;
    JetpacActor *actor;

    sp24 = D_8002E964;
    actor = jetpacActors;
    i = 0;
    do {
        *actor++ = sp24;
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
            if (actor->unk14 > 0 && actor->unk48 != NULL) {
                actor->unk48(actor);
                if (actor->unk0 < 0.0f) {
                    actor->unk0 += 256.0f;
                }
                if (actor->unk0 > 256.0f) {
                    actor->unk0 -= 256.0f;
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
            if (actor->unk14 >= 2 && actor->unk4C != NULL) {
                jetpacDrawActor(actor);
            }
        }
    }
}

void jetpacSetupTextRdp(Gfx **arg0) {
    Gfx *g = *arg0;
    WRITE_GFX(g++, 0xE7000000, 0);
    WRITE_GFX(g++, 0xE3000A01, 0);
    WRITE_GFX(g++, 0xD9000000, 0);
    WRITE_GFX(g++, 0xD9FFFFFF, 0x00200004);
    WRITE_GFX(g++, 0xFC30FE61, 0x55FEF379);
    WRITE_GFX(g++, 0xE200001C, 0x0F0A4000);
    *arg0 = g;
}

void jetpacSetTextColor(s8 arg0, s8 arg1, s8 arg2, s8 arg3) {
    D_80045BE0 = arg0;
    D_80045BE1 = arg1;
    D_80045BE2 = arg2;
    D_80045BE3 = arg3;
}

void jetpacSetTextHighlightColor(s8 arg0, s8 arg1, s8 arg2, s8 arg3) {
    D_8002E9C0 = arg0;
    D_8002E9C4 = arg1;
    D_8002E9C8 = arg2;
    D_8002E9CC = arg3;
}

void jetpacDrawString(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Gfx *g = *arg0;

    if (arg4 != 0) {
        gDPSetPrimColor(g++, 0, 0, D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC);
        gDPSetEnvColor(g++, D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3);
    } else {
        gDPSetPrimColor(g++, 0, 0, D_80045BE0, D_80045BE1, D_80045BE2, D_80045BE3);
        gDPSetEnvColor(g++, D_8002E9C0, D_8002E9C4, D_8002E9C8, D_8002E9CC);
    }
    *arg0 = textDrawString(g, 4, (s16)arg2, (s16)arg3, arg1);
}
