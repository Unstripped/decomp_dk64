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
void jetpacGridAddTiledSprite(JetpacSprite *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4);
void dlAppendTextureLoad(Gfx **arg0, s32 arg1);
void func_8070F2C8(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void dlAppendTextureRectangle(Gfx **arg0, s16 arg1, s16 arg2);
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

typedef struct {
    s32 x;
    s32 y;
    s32 unk8;
    s32 unkC;
} JetpacCellItem;

typedef struct JetpacCell {
    JetpacCellItem items[6];
    s32 count;
    u8 color[4];
} JetpacCell;

extern JetpacCell jetpacGrid[24][32];

void jetpacInitGrid(void) {
    JetpacCell *cell = &jetpacGrid[0][0];
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

void jetpacGridAddSprite(JetpacSprite *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4) {
    JetpacCell *cell;
    s32 i;
    JetpacCellItem *item;
    u8 *src;

    item = NULL;
    if (arg1 >= 0 && arg2 >= 0 && arg1 < 0x101 && arg2 < 0xC1) {
        cell = &jetpacGrid[0][0] + (arg1 / 8 + ((arg2 / 8) << 5));
        if (cell->count < 6) {
            item = &cell->items[cell->count++];
        }
        if (item != NULL) {
            item->x = arg1;
            item->y = arg2;
            item->unk8 = arg4;
            item->unkC = (s32)arg0;
            if (cell->color[3] == 0 || (cell->color[3] < 0xFF && jetpacRandFloat() > 0.97)) {
                src = arg3;
                for (i = 0; i < 4; i++) {
                    cell->color[i] = src[i];
                }
            }
        }
    }
}

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

typedef struct {
    s32 unk0;
    u8 pad4[6];
    s16 unkA;
    s16 unkC;
    u8 padE[2];
    s16 unk10;
    s16 unk12;
    u8 pad14[4];
} J1aSprite;

extern J1aSprite D_80042BD0[][256];
extern u8 D_807444FC;
void jetpacGridAddSprite(JetpacSprite *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4);

void jetpacGridAddTiledSprite(JetpacSprite *arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4) {
    s32 ya;
    s32 h;
    s32 xd;
    J1aSprite *dst;
    s32 w;
    s32 dy;
    s32 yEnd;
    s32 dx;
    s32 xEnd;

    w = ((J1aSprite *)arg0)->unkA - 1;
    h = ((J1aSprite *)arg0)->unkC - 1;

    if (D_80045BD0 < 0x100) {
        if (arg1 < 0) {
            arg1 += 0x100;
        }
        dy = 0;
        yEnd = arg2;
        if (h > 0) {
            do {
                yEnd += 8;
                yEnd &= 0xFFF8;
                yEnd -= arg2;
                dx = 0;
                xEnd = arg1;
                if (yEnd >= h) {
                    if (!h) {
                    }
                    yEnd = h;
                    if (!h) {
                    }
                }
                if (w > 0) {
                    do {
                        if (D_80045BD0 >= 0x100) {
                            return;
                        }
                        dst = &D_80042BD0[D_807444FC][D_80045BD0];
                        *(s32 *)(u32)&D_80045BD0 = D_80045BD0 + 1; // FAKE: indirect store (a direct str gets a .noalias re-emit that lets as1 hoist the sp reload above the sw)
                        *dst = *(J1aSprite *)arg0;
                        xEnd += 8;
                        xEnd &= 0xFFF8;
                        xEnd -= arg1;
                        if (xEnd >= w) {
                            xEnd = w;
                        }
                        if (arg4 != 0) {
                            dst->unk10 = dst->unk10 + w - xEnd;
                        } else {
                            dst->unk10 = dst->unk10 + dx;
                        }
                        dst->unk12 = dst->unk12 + dy;
                        dst->unkA = xEnd - dx + 1;
                        dst->unkC = yEnd - dy + 1;
                        ya = arg2 + dy;
                        xd = arg1 + dx;
                        if (xd >= 0x100) {
                            xd -= 0x100;
                        }
                        jetpacGridAddSprite((JetpacSprite *)dst, xd, ya, arg3, arg4);
                        dx = xEnd;
                        xEnd = xEnd + arg1;
                        if (!w) {
                        }
                        if (!w) {
                        }
                    } while (dx < w);
                    if (!ya) {
                    }
                    if (!yEnd) {
                    }
                }
                dy = yEnd;
                yEnd = yEnd + arg2;
            } while (dy < h);
        }
    }
}


void jetpacGridDraw(Gfx **arg0) {
    JetpacCell *cell;
    JetpacCellItem *item;
    s32 item_idx;
    Gfx *g;
    s32 col;
    s32 row;

    g = *arg0;
    cell = &jetpacGrid[0][0];
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
                    dlAppendTextureLoad(&g, item->unkC);
                    func_8070F2C8(0x400, 0x400, item->unk8, 0);
                    dlAppendTextureRectangle(&g, (item->x + 0x20) << 2, (item->y + 0x18) << 2);
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
