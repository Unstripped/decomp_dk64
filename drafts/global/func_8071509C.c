// func_8071509C (src/global/119370.c): stage 5/6: structure matches (renormalized vertex pointer, 3-step index/pointer advance); remaining: register assignment (mode web should take t1, not a3) + store scheduling around v1.s
#include "common.h"
typedef struct Fx119AEffectVertex {
    s16 x;
    s16 y;
    s16 z;
    s16 flag;
    s16 s;
    s16 t;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Fx119AEffectVertex;

void func_8071509C(EffectNode *effect) {
    EffectGridNode *node;
    Fx119AEffectVertex *vertex;
    s32 column;
    s32 row;
    s32 vertexIndex;
    s32 startX;
    s32 x;
    s32 y;

    node = Fx119A_EN_FIELD(EffectGridNode *, effect, 0x330);
    vertexIndex = 0;
    startX = -(node->unk8 * node->unkC) / 2;
    if (effect->mode == 0) {
        y = -(node->unk9 * node->unkE) / 2;
    } else {
        y = (node->unk9 * node->unkE) / 2;
    }
    for (row = 0; row < node->unk9; row++) {
        x = startX;
        if (node->unk8 > 0) {
            vertex = (Fx119AEffectVertex *)((u8 *)effect + 0x28) + vertexIndex;
            column = 0;
            do {
                vertex[0].x = x;
                vertex[0].y = y;
                vertex[0].z = 0;
                vertex[0].s = 0;
                vertex[0].t = 0;
                vertex[1].y = y;
                vertex[1].z = 0;
                vertex[1].x = node->unkC + x;
                vertex[1].t = 0;
                vertex[2].x = x;
                vertex[1].s = node->unkC << 5;
                vertexIndex += 2;
                vertex += 2;
                if (effect->mode == 0) {
                    vertex[0].y = node->unkE + y;
                } else {
                    vertex[0].y = y - node->unkE;
                }
                vertex[0].z = 0;
                vertex[0].s = 0;
                vertexIndex += 1;
                vertex += 1;
                vertex[-1].t = node->unkE << 5;
                vertex[0].x = node->unkC + x;
                if (effect->mode == 0) {
                    vertex[0].y = node->unkE + y;
                } else {
                    vertex[0].y = y - node->unkE;
                }
                vertex[0].z = 0;
                vertex[0].s = node->unkC << 5;
                vertexIndex += 1;
                vertex += 1;
                vertex[-1].t = node->unkE << 5;
                x += node->unkC;
                column++;
            } while (column < node->unk8);
        }
        if (effect->mode == 0) {
            y += node->unkE;
        } else {
            y -= node->unkE;
        }
    }
}
