// func_8065E138 (src/global/61AA0.c): stage 6, parked under NON_MATCHING in 61AA0.c (RenderA): text identical except (1) loop-preheader temp regs for sll i<<6 / lui D_807F78C0 / sll zero,6 are t7,t9,t8 vs target t9,t8,t7; (2) found block: target keeps node+0x30 in a0 (addiu a0,t1,0x30; return addu v0,t7,a0) while ours folds it into addu t7,t1 + addiu 0x30. Natural form = for(i;!mismatch&&i<arg0) / for(j;mismatch&&j<arg0) with u8 mismatch; deadsweep + permuter 240s found nothing natural (permuter hint: reassigning node after sub=node->sub materialises a0).
#include "common.h"

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    u8 unk3E;
    u8 pad3F;
} RenderASub;

typedef struct RenderANode {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    s32 unk10;
    struct RenderANode *hash_next;
    struct RenderANode *hash_prev;
    struct RenderANode *list_next;
    struct RenderANode *list_prev;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
    u8 pad2A[6];
    RenderASub sub[1];
} RenderANode;

extern RenderANode *D_807F8EC0[100];
extern RenderANode *D_807F9050;
extern RenderANode *D_807F9054;
extern s16 D_807F9058;
extern s16 D_807F905A;
extern s32 D_8076A064;
extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern RenderASub D_807F78C0[];
s32 matrixCacheHash(s32, s16, u8);
void *func_80610FE8(s32);
void heapFree(void *);
void heapFreeDeferred(void *);
#define DIFF(a, b) (((b) < (a)) ? ((a) - (b)) : -((a) - (b)))

void *func_8065E138(s32 arg0, s32 arg1, s16 arg2, u8 arg3) {
    RenderANode *node;
    s32 i;
    s32 j;
    u8 mismatch;
    RenderASub *a;
    RenderASub *b;

    D_807F9058++;
    node = D_807F8EC0[matrixCacheHash(arg0, arg2, arg3)];
    while (node != NULL) {
        if (arg0 == node->unk29 && arg2 == node->unk24 && node->unk28 == arg3) {
            if (node->unk0 == D_8076A0B4[arg1] && node->unk4 == D_8076A0B8[arg1]) {
                if (node->unk8 == D_8076A0BC[arg1]) {
                    i = 0;
                    mismatch = 0;
                    for (; !mismatch && i < arg0; i++) {
                        mismatch = 1;
                        a = &node->sub[i];
                        for (j = 0; mismatch && j < arg0; j++) {
                            b = &D_807F78C0[j];
                            if (b->unk3E == 1) {
                                if (a->unk38 == b->unk38 && a->unk3A == b->unk3A && a->unk3C == b->unk3C &&
                                    (double)DIFF(b->unkC, a->unkC) < 0.05 &&
                                    (double)DIFF(b->unk10, a->unk10) < 0.05 &&
                                    (double)DIFF(b->unk14, a->unk14) < 0.05 &&
                                    (double)DIFF(b->unk2C, a->unk2C) < 0.05 &&
                                    (double)DIFF(b->unk30, a->unk30) < 0.05 &&
                                    (double)DIFF(b->unk34, a->unk34) < 0.05 &&
                                    a->unk0 == b->unk0 && a->unk4 == b->unk4) {
                                    mismatch = 0;
                                }
                            } else if (a->unk38 == b->unk38 && a->unk3A == b->unk3A && a->unk3C == b->unk3C &&
                                       (double)DIFF(b->unk2C, a->unk2C) < 0.05 &&
                                       (double)DIFF(b->unk30, a->unk30) < 0.05 &&
                                       (double)DIFF(b->unk34, a->unk34) < 0.05 &&
                                       a->unk1C == b->unk1C) {
                                mismatch = 0;
                            }
                        }
                    }
                    if (!mismatch) {
                        RenderASub *sub = node->sub;
                        node->unkC = D_8076A064;
                        D_807F905A++;
                        if (node->list_prev != NULL) {
                            if (node->list_next == NULL) {
                                D_807F9054 = node->list_prev;
                            }
                            node->list_prev->list_next = node->list_next;
                            if (node->list_next != NULL) {
                                node->list_next->list_prev = node->list_prev;
                            }
                            D_807F9050->list_prev = node;
                            node->list_prev = NULL;
                            node->list_next = D_807F9050;
                            D_807F9050 = node;
                        }
                        return &sub[arg0];
                    }
                }
            }
        }
        node = node->hash_next;
    }
    return 0;
}
