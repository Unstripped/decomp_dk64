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
void func_80027010(JetpacActor *arg0);
typedef struct JetpacState {
    u8 pad0[0x4C];
    JetpacActor actors[4];
} JetpacState;
typedef struct {
    u8 pad0[0x18];
} JetpacSprite;

extern JetpacSprite D_8002C4D0[];
extern JetpacSprite D_8002B9C0[];
f32 func_80027210(void);
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

void func_80025460(void) {
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

void func_800255D4(Gfx **arg0) {
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
    func_80025460();
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
        if (func_80027210() < 0.5) {
            arg0->color[1] = 0;
        } else {
            arg0->color[1] = 0xFF;
        }
        if (func_80027210() < 0.5) {
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
        func_80027010(arg0);
    }
    arg0->unk1C = 0;
    arg0->unk24 = 0x10;
    arg0->unk30 = arg1;
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80025C40.s")

void func_80025CA0(JetpacActor *arg0) {
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

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_800260DC.s")

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

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80026AB0.s")

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80026CA4.s")
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80026CEC.s")

extern s32 D_8002F064;
void func_80024E70(s32);
void func_80026318(JetpacActor *);
s32 func_80026FE0(void);

extern JetpacState D_8002F050;
void func_80026D48(void) {
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

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80026DC8.s")

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80026FE0.s")

void func_80027010(JetpacActor *arg0) {
    if (arg0->unk44 >= 0xE) {
        arg0->unk44 = 0;
        arg0->unk3C = (s32)arg0->x & 0xFFF8;
        arg0->unk40 = (s32)(arg0->y + 7.0f);
    }
}
