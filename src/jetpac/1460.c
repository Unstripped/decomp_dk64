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

void jetpacInitGrid(void) {
    JetpacCell *cell = &D_8002F3D0[0][0];
    s32 row;
    s32 col;

    for (row = 0; row < 24; row++) {
        for (col = 0; col < 32; col++) {
            cell->count = 0;
            cell->color[3] = 0;
            cell++;
        }
    }
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_800254B8.s")

extern s32 D_80045BD0;

void jetpacInitRdp(Gfx **arg0) {
    Gfx *g = *arg0;

    WRITE_GFX(g++, 0xE7000000, 0);
    WRITE_GFX(g++, 0xED080060, 0x00480360);
    WRITE_GFX(g++, 0xD9000000, 0);
    WRITE_GFX(g++, 0xD9FFFFFF, 0x00200004);
    WRITE_GFX(g++, 0xE200001C, 0x00504240);
    WRITE_GFX(g++, 0xFC11FE23, -0x00000C07);
    WRITE_GFX(g++, 0xE3001201, 0);
    WRITE_GFX(g++, 0xE3000C00, 0);
    WRITE_GFX(g++, 0xE3001402, 0x00000C00);
    WRITE_GFX(g++, 0xE3000A01, 0);
    WRITE_GFX(g++, 0xFB000000, 0);

    D_80045BD0 = 0;
    jetpacInitGrid();
    *arg0 = g;
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80025700.s")

#if 0
// Non-matching draft: temporary register allocation in inner loop (t2/t9/t0/t5 vs t3/t5/t7/t4)
void func_80025904(Gfx **arg0) {
    JetpacCell *cell;
    JetpacCellItem *item;
    s32 item_idx;
    Gfx *g;
    s32 col;
    s32 row;

    g = *arg0;
    cell = &D_8002F3D0[0][0];
    for (row = 0; row < 24; row++) {
        col = 0;
        do {
            if (cell->count != 0) {
                gDPSetPrimColor(g++, 0, 0, cell->color[0], cell->color[1], cell->color[2], 0xFF);
            }
            item = &cell->items[0];
            if (cell->count > 0) {
                item_idx = 0;
                do {
                    func_8070E8F0(&g, item->unkC);
                    func_8070F2C8(0x400, 0x400, item->unkB, 0);
                    func_8070F2FC(&g, (s16)(item->x + 0x20) * 4, (s16)(item->y + 0x18) * 4);
                    item_idx++;
                    item++;
                } while (item_idx < cell->count);
            }
            col++;
            cell++;
        } while (col != 32);
    }
    *arg0 = g;
}
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80025904.s")

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

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80025C40.s")

void jetpacResetActorState(JetpacActor *arg0) {
    arg0->unk14 = 4;
    arg0->unk2C = 0;
}
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80025CB0.s")

void func_80025F48(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_80025700(&D_8002C4D0[arg0], *arg1, arg3, arg4, arg5);
    *arg1 += arg2;
    if (*arg1 < 0) {
        *arg1 += 0x100;
    }
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80025FC4.s")

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

J1bActor *func_80025C40(J1bActor *arg0);
void func_80025CB0(J1bActor *arg0);
void func_80024E70(s32 arg0);

void func_800260DC(J1bActor *arg0) {
    J1bActor *p;
    s32 ix;
    s32 iy;
    s32 col;
    f32 vy;
    f32 absVy;

    p = func_80025C40(arg0);
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
        p->unk48 = func_80025CB0;
        p->unk4C = 0;
        func_80024E70(6);
    }
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80026318.s")

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

#ifdef NON_MATCHING
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
                func_80025700(&D_8002C3A8[idx], (s32)(f32)((s32)x & 0xFFFE), (s32)y, (s32)color, D_8002F068);
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
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80026AB0.s")
#endif

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

#ifdef NON_MATCHING
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
    g->unk24 = 0x10;
    g->unk28 = 0x18;
    g->unk30 = 1;
    g->x = 126.0f;
    g->y = 160.0f;
    func_80025BB8((JetpacActor *)&D_8002F050, 0);
    D_8002F084 = 3;
    D_8002F088 = 4;
    D_8002F09C[0] = tmpl;
    D_8002F09C[1] = tmpl;
    D_8002F09C[2] = tmpl;
    D_8002F09C[3] = tmpl;
}
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80026DC8.s")
#endif

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
