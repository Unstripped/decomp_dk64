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

void func_800254B8(JetpacSprite *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    JetpacCell *cell;
    s32 i;
    JetpacCellItem *item;

    item = NULL;
    if (arg1 >= 0 && arg2 >= 0 && arg1 < 0x101 && arg2 < 0xC1) {
        cell = &D_8002F3D0[0][0] + (arg1 / 8 + ((arg2 / 8) << 5));
        if (cell->count < 6) {
            item = &cell->items[cell->count++];
        }
        if (item != NULL) {
            item->x = arg1;
            item->y = arg2;
            *(s32 *)&item->pad8[0] = arg4;
            item->unkC = (s32)arg0;
            if (cell->color[3] == 0 || (cell->color[3] < 0xFF && jetpacRandFloat() > 0.97)) {
                if (1) { }
                if (1) { }
                if (1) { }
                cell->color[0] = ((u8 *)arg3)[0];
                cell->color[1] = ((u8 *)arg3)[1];
                cell->color[i = 2] = ((u8 *)arg3)[i];
                cell->color[3] = ((u8 *)arg3)[3];
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

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80025700.s")

#ifdef NON_MATCHING
// Non-matching: temporary register allocation in inner loop (t2/t9/t0/t5 vs t3/t5/t7/t4)
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
#else

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/1460/func_80025904.s")
#endif
