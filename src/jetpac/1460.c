#include "common.h"
#include "jetpac.h"
#include "proto/global/1135F0.h"
#include "proto/jetpac/1460.h"
#include "proto/jetpac/3060.h"
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

void jetpacGridAddSprite(JetpacSprite *sprite, s32 x, s32 y, u8 *color, s32 flipFlag) {
    JetpacCell *cell;
    s32 i;
    JetpacCellItem *item;
    s32 pad;

    item = NULL;
    if (x >= 0 && y >= 0 && x < 0x101 && y < 0xC1) {
        cell = &jetpacGrid[0][0] + (x / 8 + (y / 8) * 32);
        if (cell->count < 6) {
            item = &cell->items[cell->count++];
        }
        if (item != NULL) {
            item->x = x;
            item->y = y;
            item->flip = flipFlag;
            item->texture = sprite;
            if (cell->color[3] == 0 || (cell->color[3] < 0xFF && jetpacRandFloat() > 0.97)) {
                for (i = 0; i < 4; i++) {
                    cell->color[i] = color[i];
                }
            }
        }
    }
}

extern s32 jetpacTiledSpriteCount;

void jetpacInitRdp(Gfx **glistp) {
    Gfx *g = *glistp;

    gDPPipeSync(g++);
    gDPSetScissor(g++, G_SC_NON_INTERLACE, 32, 24, 288, 216);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, G_SHADE | G_SHADING_SMOOTH);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x00504240);
    gDPSetCombine(g++, 0x11FE23, 0xFFFFF3F9);
    gDPSetTextureFilter(g++, G_TF_POINT);
    gDPSetTexturePersp(g++, G_TP_NONE);
    gDPSetTextureConvert(g++, G_TC_FILT);
    gDPSetCycleType(g++, G_CYC_1CYCLE);
    gDPSetEnvColor(g++, 0, 0, 0, 0);

    jetpacTiledSpriteCount = 0;
    jetpacInitGrid();
    *glistp = g;
}

extern JetpacSprite D_80042BD0[][256];
extern u8 gGfxBufferIndex;

void jetpacGridAddTiledSprite(JetpacSprite *sprite, s32 x, s32 y, u8 *color, s32 flipFlag) {
    s32 ya;
    s32 h;
    s32 xd;
    JetpacSprite *dst;
    s32 w;
    s32 dy;
    s32 yEnd;
    s32 dx;
    s32 xEnd;

    w = sprite->unkA - 1;
    h = sprite->unkC - 1;

    if (jetpacTiledSpriteCount < 0x100) {
        if (x < 0) {
            x += 0x100;
        }
        dy = 0;
        yEnd = y;
        if (h > 0) {
            do {
                yEnd += 8;
                yEnd &= 0xFFF8;
                yEnd -= y;
                dx = 0;
                xEnd = x;
                yEnd = MIN(yEnd, h);
                if (w > 0) {
                    do {
                        if (jetpacTiledSpriteCount >= 0x100) {
                            return;
                        }
                        dst = &D_80042BD0[gGfxBufferIndex][jetpacTiledSpriteCount];
                        *(s32 *)(u32)&jetpacTiledSpriteCount = jetpacTiledSpriteCount + 1; // FAKE: indirect store (a direct str gets a .noalias re-emit that lets as1 hoist the sp reload above the sw)
                        *dst = *sprite;
                        xEnd += 8;
                        xEnd &= 0xFFF8;
                        xEnd -= x;
                        xEnd = MIN(xEnd, w);
                        if (flipFlag != 0) {
                            dst->unk10 += w - xEnd;
                        } else {
                            dst->unk10 += dx;
                        }
                        dst->unk12 += dy;
                        dst->unkA = xEnd - dx + 1;
                        dst->unkC = yEnd - dy + 1;
                        ya = y + dy;
                        xd = x + dx;
                        xd = (xd >= 0x100) ? xd - 0x100 : xd;
                        jetpacGridAddSprite(dst, xd, ya, color, flipFlag);
                        dx = xEnd;
                        xEnd += x;
                    } while (dx < w);
                }
                dy = yEnd;
                yEnd += y;
            } while (dy < h);
        }
    }
}

void jetpacGridDraw(Gfx **glistp) {
    JetpacCell *cell;
    JetpacCellItem *item;
    s32 item_idx;
    Gfx *g;
    s32 col;
    s32 row;

    g = *glistp;
    cell = &jetpacGrid[0][0];
    for (row = 0; row < 24; row++) {
        for (col = 0; col < 32; col++) {
            if (cell->count != 0) {
                gDPSetPrimColor(g++, 0, 0, cell->color[0], cell->color[1], cell->color[2], 0xFF);
            }
            item = &cell->items[0];
            for (item_idx = 0; item_idx < cell->count; item_idx++) {
                dlAppendTextureLoad(&g, item->texture);
                dlSetTextureScaleAndFlip(0x400, 0x400, item->flip, 0);
                dlAppendTextureRectangle(&g, (item->x + 0x20) << 2, (item->y + 0x18) << 2);
                item++;
            }
            cell++;
        }
    }
    *glistp = g;
}
