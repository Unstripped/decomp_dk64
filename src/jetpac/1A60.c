#include "common.h"
#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
typedef struct JetpacActor {
    f32 x;
    f32 y;
    u8 pad8[8];
    u8 unk10[4];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    u8 pad34[8];
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    void (*unk48)(struct JetpacActor *);
    u8 pad4C[4];
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
void func_80025700(JetpacSprite *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_8070E8F0(Gfx **arg0, s32 arg1);
void func_8070F2C8(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void func_8070F2FC(Gfx **arg0, s16 arg1, s16 arg2);
typedef struct {
    u8 pad0[8];
    s32 lives;
} JetpacPlayerData;

typedef struct {
    u8 pad0[0x1C];
    JetpacPlayerData data;
    u8 pad28[0x194 - 0x28];
} JetpacSession;

typedef struct {
    JetpacSession sessions[2];
    u8 pad328[0x344 - 0x328];
    s32 currentSession;
} JetpacGame;

extern JetpacGame D_8002EC30;
void func_80025368(JetpacPlayerData *arg0);
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

extern JetpacCell D_8002F3D0[24][32];


typedef struct {
    s32 x;
    s32 y;
    s32 timer;
    u8 color[4];
} JetpacExplosion;

void func_80025A60(JetpacExplosion *arg0) {
    volatile s32 frame;
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
    func_80025700(&D_8002B9C0[frame], arg0->x, arg0->y, (s32)&arg0->color[0], 0);
    arg0->timer++;
}

s32 func_80025B70(JetpacActor *arg0) {
    return (s32)(((s32)arg0->x + arg0->unk1C) / 2) % 4;
}

void func_80025BB8(JetpacActor *arg0, s32 arg1) {
    if (arg1 == 0 && arg0->unk30 != 0) {
        arg0->x = (f32)((s32)arg0->x & 0xFFFE);
    } else if (arg1 != 0 && arg0->unk30 == 0) {
        jetpacSnapActorToGrid(arg0);
    }
    arg0->unk1C = 0;
    arg0->unk24 = 0x10;
    arg0->unk30 = arg1;
}

JetpacActor *func_80025C40(JetpacState *arg0) {
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
s32 func_800283EC(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 func_8002A974(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 jetpacCheckLedgeCollision(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4);

void func_80025CB0(JetpacActor *arg0) {
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
            if (func_8002A974(x1, y1, x2, y2) != 0) {
                jetpacResetActorState(arg0);
                return;
            }
            if (jetpacCheckLedgeCollision(x1, y1, x2, y2, 0) >= 0) {
                jetpacResetActorState(arg0);
                return;
            }
            if (func_800283EC(x1, y1, x2, y2) != 0) {
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

void func_80025F48(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_80025700(&D_8002C4D0[arg0], *arg1, arg3, arg4, arg5);
    *arg1 += arg2;
    if (*arg1 < 0) {
        *arg1 += 0x100;
    }
}

void func_80025FC4(JetpacActor *arg0) {
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
            func_80025F48(spr, &pos, dir, y, (s32)arg0->unk10, flip);
            frame++;
        }
    }
}

typedef struct J1bActor {
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
    u8 pad34[8];
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    void (*unk48)(struct J1bActor *);
    s32 unk4C;
} J1bActor;

void func_80024E70(s32 arg0);

void func_800260DC(arg0)
J1bActor *arg0;
{
    J1bActor *p;
    s32 ix;
    s32 iy;
    s32 col;
    f32 vy;
    f32 absVy;

    p = (J1bActor *)func_80025C40((JetpacState *)arg0);
    if (p == NULL) {
        vy = arg0->vy;
        if (vy > 0.0f) {
            absVy = vy;
        } else {
            absVy = -vy;
        }
        if (absVy < 0.01f && arg0->y < 152.0f) {
            func_80024E70(6);
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
        p->unk48 = (void (*)(J1bActor *))func_80025CB0;
        p->unk4C = 0;
        func_80024E70(6);
    }
}

typedef struct {
    f32 x;
    f32 y;
    f32 unk8;
    f32 unkC;
    u8 pad10[8];
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[4];
    s32 unk30;
    s32 unk34;
    s32 unk38;
} J0a2Actor;

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
    u8 pad0[0xC];
    s32 unkC;
} J0a2Player;

#define J0a2A ((J0a2Actor *)arg0)
#define J0a2Flags (*(u32 *)&D_8002EC30)
extern f32 D_8002EF84[];
extern s32 D_8002EF74;
s32 jetpacCheckLedgeCollision(f32, f32, f32, f32, s32);
s32 func_80028E04(s32, s32, s32);
s32 func_80027330(f32);
void func_80024F9C(s32);

void func_80026318(JetpacActor *arg0) {
    J0a2Player *sp54;
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

    sp54 = (J0a2Player *)&D_8002EC30.sessions[D_8002EF74].data;
    fire = J0a2Flags & 0x4000;
    sp34 = J0a2Flags & 0x200;
    sp30 = J0a2Flags & 0x100;
    a2 = J0a2Flags & 0x8000;
    a1 = J0a2Flags & 0x2030;
    if (fire && J0a2A->unk38 >= 5) {
        func_800260DC((J1bActor *)arg0, a1, a2);
        J0a2A->unk38 = 0;
    } else if (J0a2A->unk38 < 5) {
        J0a2A->unk38++;
    }
    if (a2 != 0 && (J0a2A->unk30 == 0 || a1 == 0)) {
        func_80025BB8(arg0, 1);
        J0a2A->unkC -= 0.2f;
        u = J0a2A->unk30;
    } else if ((u = J0a2A->unk30) != 0) {
        if (a1 != 0) {
            J0a2A->unkC = 0.0f;
            u = (*(volatile s32 *)&J0a2A->unk30);
        } else {
            J0a2A->unkC += 0.2;
            u = (*(volatile s32 *)&J0a2A->unk30);
        }
    }
    if (sp34 != 0) {
        J0a2A->unk8 -= 0.33333334f;
        if (J0a2A->unk18 == 0 && J0a2A->unk8 <= 0.0f) {
            J0a2A->unk18 = 1;
            func_80025BB8(arg0, J0a2A->unk30);
        }
        u = J0a2A->unk30;
    } else if (sp30 != 0) {
        J0a2A->unk8 += 0.33333334f;
        if (J0a2A->unk18 != 0 && J0a2A->unk8 >= 0.0f) {
            J0a2A->unk18 = 0;
            func_80025BB8(arg0, J0a2A->unk30);
        }
        u = J0a2A->unk30;
    } else {
        vx = J0a2A->unk8;
        if (vx > 0.0f) {
            J0a2A->unk8 = vx - 0.16666667f;
            u = (*(volatile s32 *)&J0a2A->unk30);
        } else if (vx < 0.0f) {
            J0a2A->unk8 = vx + 0.16666667f;
            u = (*(volatile s32 *)&J0a2A->unk30);
        }
    }
    if (u != 0) {
        mx = 2.0f;
        my = 2.0f;
    } else {
        mx = 1.0f;
        my = 0.0f;
    }
    vx = J0a2A->unk8;
    J0a2A->unk8 = (vx < -mx) ? -mx : ((mx < vx) ? mx : vx);
    vy = J0a2A->unkC;
    J0a2A->unkC = (vy < -my) ? -my : ((my < vy) ? my : vy);
    if (J0a2A->unk8 < 0.1 && J0a2A->unk8 > -0.1) {
        J0a2A->unk8 = 0.0f;
    }
    if (J0a2A->unkC < 0.1 && J0a2A->unkC > -0.1) {
        J0a2A->unkC = 0.0f;
    }
    vx = J0a2A->unk8;
    if (J0a2A->unk30 != 0) {
        idx = jetpacCheckLedgeCollision(J0a2A->unk1C + J0a2A->x + vx, J0a2A->unk20 + J0a2A->y + J0a2A->unkC,
                                        J0a2A->unk24 + J0a2A->x + vx, J0a2A->unk28 + J0a2A->y + J0a2A->unkC, 1);
        if (idx >= 0) {
            if ((f32)*(s32 *)((u8 *)&D_8002EC30 + idx * 0x34 + 0x378) <= J0a2A->unk20 + J0a2A->y) {
                J0a2A->unkC *= -0.4f;
                if ((J0a2A->unkC > 0.0f ? J0a2A->unkC : -J0a2A->unkC) <= 0.15f) {
                    J0a2A->unkC = 0.0f;
                }
            } else if (J0a2A->unk28 + J0a2A->y <= (f32)*(s32 *)((u8 *)&D_8002EC30 + idx * 0x34 + 0x370)) {
                J0a2A->unk34 = idx;
                J0a2A->unkC = 0.0f;
                func_80025BB8(arg0, 0);
                J0a2A->y = *(f32 *)((u8 *)D_8002EF84 + idx * 0x34) - 24.0f;
            } else {
                J0a2A->unk8 *= -0.5f;
            }
        }
    } else {
        idx = func_80028E04(J0a2A->unk34, (s32)(J0a2A->unk1C + J0a2A->x + vx), (s32)(J0a2A->unk24 + J0a2A->x + vx));
        switch (idx) {
        case -2:
        case 2:
            func_80025BB8(arg0, 1);
            J0a2A->unkC = -0.5f;
            break;
        case -1:
        case 1:
            if (J0a2A->unk18 == 0 && sp34 == 0) {
                J0a2A->unk8 = 1.0f;
            } else if (sp30 == 0) {
                J0a2A->unk8 = -1.0f;
            }
            break;
        }
    }
    J0a2A->x = J0a2A->x + J0a2A->unk8;
    if (J0a2A->x + J0a2A->unk24 > 256.0f) {
        J0a2A->x -= 256.0f;
    }
    if (J0a2A->x + J0a2A->unk1C < 0.0f) {
        J0a2A->x += 256.0f;
    }
    J0a2A->y = J0a2A->y + J0a2A->unkC;
    if (J0a2A->y < 18.0f) {
        J0a2A->y = 18.0f;
        J0a2A->unkC = 0;
    }
    if (J0a2A->y > 168.0f) {
        J0a2A->y = 168.0f;
    }
    if (func_80027330(J0a2A->x) != 0 && sp54->unkC == 8 && J0a2A->y > 152.0f) {
        func_80024F9C(4);
    }
}

void func_80026A3C(JetpacActor *arg0) {
    JetpacPlayerData *p = &D_8002EC30.sessions[D_8002EC30.currentSession].data;

    if (arg0->unk2C < 14) {
        arg0->unk2C++;
    } else {
        p->lives--;
        func_80025368(p);
    }
}

extern JetpacState D_8002F050;

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

void func_80026AB0(void) {
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
        idx = func_80025B70((JetpacActor *)&D_8002F050);
        x = *(f32 *)&D_8002F050;
        y = D_8002F054;
        if (draw != 0) {
            color = D_8002F060;
            if (D_8002F080 == 0) {
                x = (s16)(s32)x & 0xFFFE;
                func_80025700(&D_8002C3A8[idx], (s32)x, (s32)y, (s32)color, D_8002F068);
            } else {
                func_80025700(&D_8002C330, (s32)x, (s32)y, (s32)color, D_8002F068);
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
                func_80025700(&D_8002C348[idx], (s32)x, (s32)(y + 18.0f), (s32)color, D_8002F068);
            }
        }
        if (D_8002F094 < 14) {
            func_80025A60(&D_8002F08C);
        }
    }
}

extern JetpacActor D_8002F09C[];
void func_80025FC4(JetpacActor *);
void func_80026CA4(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_80025FC4(&D_8002F09C[i]);
    }
}

void func_80026CEC(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        JetpacActor *a = &D_8002F050.actors[i];

        if (a->unk48 != NULL) {
            a->unk48(a);
        }
    }
}

extern s32 D_8002F064;
void func_80024E70(s32);
void func_80026318(JetpacActor *);
s32 func_80026FE0(void);

void jetpacPlayerStateUpdate(void) {
    if (!func_80026FE0()) {
        s32 state = D_8002F064;

        if (state == 1) {
            func_80024E70(3);
            state = 3;
        }
        D_8002F064 = state;
        if (state == 3) {
            func_80026318((JetpacActor *)&D_8002F050);
        }
        state = D_8002F064;
        if (state == 4) {
            func_80026A3C((JetpacActor *)&D_8002F050);
        }
    }
}

typedef struct {
    u8 pad0[0x420];
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
    u8 pad454[0x464 - 0x454];
    s32 unk44;
    u8 tint[4];
} J1bGameView;

extern JetpacActor D_8002C518;
extern s32 D_8002F084;
extern s32 D_8002F088;

void func_80026DC8(void) {
    J1bGameView *g = (J1bGameView *)&D_8002EC30;
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
    func_80025BB8((JetpacActor *)&D_8002F050, 0);
    D_8002F084 = 3;
    D_8002F088 = 4;
    {
        s32 i;
        for (i = 0; i < 4; i++) {
            D_8002F09C[i] = tmpl;
        }
    }
}

extern s32 D_8002F07C;
s32 func_80026FE0(void) {
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
