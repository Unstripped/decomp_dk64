// func_8071509C (src/global/119370.c): Stage 3: reconstructed quad grid; target inspection confirms vertex-index/pointer increments and mode-dependent Y direction. Closest checked diff remains 1930; loop register scheduling differs.
#include "common.h"
typedef struct EffectGridNode { u8 pad0[8]; u8 columns; u8 rows; u8 padA[2]; s16 width; s16 height; } EffectGridNode;
typedef struct EffectNode EffectNode;
typedef struct EffectVertex { s16 x; s16 y; s16 z; s16 flag; s16 s; s16 t; u8 r; u8 g; u8 b; u8 a; } EffectVertex;

void func_8071509C(EffectNode *arg0) {
    EffectGridNode *node;
    EffectVertex *vertex;
    s32 column;
    s32 row;
    s32 vertexIndex;
    s32 startX;
    s32 x;
    s32 y;

    node = *(EffectGridNode **)((u8 *) arg0 + 0x330);
    startX = -(node->columns * node->width) / 2;
    if (*((u8 *) arg0 + 0x36F) == 0) {
        y = -(node->rows * node->height) / 2;
    } else {
        y = (node->rows * node->height) / 2;
    }
    vertexIndex = 0;
    for (row = 0; row < node->rows; row++) {
        x = startX;
        for (column = 0; column < node->columns; column++) {
            vertex = (EffectVertex *) ((u8 *) arg0 + 0x28) + vertexIndex;
            vertex[0].x = x;
            vertex[0].y = y;
            vertex[0].z = 0;
            vertex[0].s = 0;
            vertex[0].t = 0;
            vertex[1].y = y;
            vertex[1].z = 0;
            vertex[1].x = node->width + x;
            vertex[1].t = 0;
            vertex[2].x = x;
            vertex[1].s = node->width << 5;
            if (*((u8 *) arg0 + 0x36F) == 0) {
                vertex[2].y = node->height + y;
            } else {
                vertex[2].y = y - node->height;
            }
            vertex[2].z = 0;
            vertex[2].s = node->height << 5;
            vertex[2].t = 0;
            vertex[3].x = node->width + x;
            if (*((u8 *) arg0 + 0x36F) == 0) {
                vertex[3].y = node->height + y;
            } else {
                vertex[3].y = y - node->height;
            }
            vertex[3].z = 0;
            vertex[3].s = node->width << 5;
            vertex[3].t = node->height << 5;
            vertexIndex += 4;
            x += node->width;
        }
        if (*((u8 *) arg0 + 0x36F) == 0) {
            y += node->height;
        } else {
            y -= node->height;
        }
    }
}
