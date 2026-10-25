// func_8071509C (src/global/119370.c): Stage 3: reconstructed the four-vertex quad grid from asm. Direct fdiff compiles; vertex pointer representation needs register/block-order work.
#include "common.h"
typedef struct Ua1ListNode { u8 pad0[8]; u8 columns; u8 rows; u8 padA[2]; s16 width; s16 height; } Ua1ListNode;
typedef struct Ua1Effect Ua1Effect;
typedef struct Ua1Vertex { s16 x; s16 y; s16 z; s16 flag; s16 s; s16 t; u8 r; u8 g; u8 b; u8 a; } Ua1Vertex;

void func_8071509C(Ua1Effect *arg0) {
    Ua1ListNode *node;
    Ua1Vertex *vertex;
    s32 column;
    s32 row;
    s32 vertexIndex;
    s32 x;
    s32 y;

    node = *(Ua1ListNode **)((u8 *) arg0 + 0x330);
    if (*((u8 *) arg0 + 0x36F) == 0) {
        y = -(node->rows * node->height) / 2;
    } else {
        y = (node->rows * node->height) / 2;
    }
    vertexIndex = 0;
    for (row = 0; row < node->rows; row++) {
        x = -(node->columns * node->width) / 2;
        for (column = 0; column < node->columns; column++) {
            vertex = (Ua1Vertex *) ((u8 *) arg0 + 0x28) + vertexIndex;
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
