#include "common.h"
#include "actor.h"

extern s8 D_807F7F00;

void renderSetSegment6Override(s8 arg0) {
    D_807F7F00 = arg0;
}

extern Gfx D_80748310[6][2];

void renderReplaceSegment6Commands(Gfx *arg0, Gfx *arg1) {
    while (arg0 != arg1) {
        int found = 0;
        int i = 0;

        for (; i < 6 && !found; ) {
            if (arg0->words.w0 == D_80748310[i][0].words.w0 && arg0->words.w1 == D_80748310[i][0].words.w1) {
                found = 1;
            } else {
                i++;
            }
        }
        if (found) {
            gSPDisplayList(arg0++, 0x06000000 + i * 0x10);
        } else {
            arg0++;
        }
    }
}

typedef struct {
    u8 pad0[0x21C];
    f32 x;
    f32 y;
    f32 z;
    u8 pad228[0x27C - 0x228];
    f32 unk27C;
    u8 pad280[0x2F0 - 0x280];
} PlayerCameraData;
extern PlayerCameraData *D_807FC924;
extern u8 D_807FC929;
extern s32 D_8076A0A8;
f32 renderAdjustActorDistance(s16, f32);
f32 renderScaleDistanceByFov(f32);
#define R2A_SQ(x) ((x) * (x))

void renderCalcPlayerDistanceAlpha(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 *arg5) {
    s32 pad;
    f32 dist;
    f32 fv1;

    dist = sqrtf(R2A_SQ(arg0 - D_807FC924[D_807FC929].x) + R2A_SQ(arg1 - D_807FC924[D_807FC929].y) + R2A_SQ(arg2 - D_807FC924[D_807FC929].z));
    if (D_8076A0A8 == 0x26) {
        arg3 = renderAdjustActorDistance(arg4, arg3);
        if (arg3 < dist) {
            *arg5 = 0;
            return;
        }
    }
    arg0 = renderScaleDistanceByFov(arg3);
    fv1 = (arg0 * 3.0f) / (f32)4;
    if (dist < fv1) {
        *arg5 = 0xFF;
        return;
    }
    *arg5 = (s32)(((dist - fv1) / (arg0 - fv1)) * 255.0f);
    if (*arg5 >= 0x100) {
        *arg5 = 0xFF;
    }
    *arg5 = 0xFF - *arg5;
}

extern f32 D_807F6940;

f32 renderAdjustActorDistance(s16 arg0, f32 arg1) {
    if ((arg0 == 0xB2) || (arg0 == 0x253)) {
        arg1 = (f64)arg1 + (600.0 - (f64)arg1) * (f64)D_807F6940;
    }
    return arg1;
}

extern Gfx D_80748370[6][2];
extern Gfx D_807483D0[6][2];

Gfx *renderSetSegment6AndFog(Gfx *gdl, s16 arg1, u8 arg2) {
    if (arg1 == 0xFF) {
        if ((u8)D_807F7F00 != 0 || arg2) {
            gSPSegment(gdl++, 6, osVirtualToPhysical(&D_80748310));
        } else {
            gSPSegment(gdl++, 6, osVirtualToPhysical(&D_80748370));
        }
    } else {
        gDPSetFogColor(gdl++, 0, 0, 0, arg1);
        gSPSegment(gdl++, 6, osVirtualToPhysical(&D_807483D0));
    }
    return gdl;
}

extern f32 D_807F5FDC;
extern f32 D_807F5FE0;

f32 renderScaleDistanceByFov(f32 arg0) {
    if ((f64)D_807FC924[D_807FC929].unk27C == 45.0) {
        return arg0;
    }
    return (arg0 / D_807F5FDC) * D_807F5FE0;
}

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    void *unk8;
} BillboardCacheEntry;
extern BillboardCacheEntry D_807F8E90[4];
extern s16 D_807F8E8A;

void billboardCacheInit(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        D_807F8E90[i].unk0 = -1;
    }
    D_807F8E8A = 0;
}

extern s8 D_807F8E88;
extern s32 D_8076A064;
void assetFreeBuffer(void *, s32, s32);

void func_8065D1AC(void) {
    s32 i;

    D_807F8E88 = 0;
    for (i = 0; i < 4; i++) {
        if (D_807F8E90[i].unk0 != -1 && (u32)(D_8076A064 - D_807F8E90[i].unk0) >= 21) {
            assetFreeBuffer(D_807F8E90[i].unk8, 0x65, 0x4D);
            D_807F8E90[i].unk0 = -1;
        }
    }
}

void billboardSetFlags(s16 arg0) {
    D_807F8E8A = arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/61AA0/func_8065D254.s")

void billboardSetVertex(s16 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    arg0[0] = arg1;
    arg0[1] = 0;
    arg0[2] = arg2;
    arg0[4] = arg3 << 5;
    arg0[5] = arg4 << 5;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/61AA0/func_8065D994.s")

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
extern s32 D_807F905C;
extern u16 D_807F9060;
extern s32 D_807F9064;
s32 mapIsBonusOrSpecial(void);

void func_8065E040(s32 arg0) {
    s32 i;
    for (i = 0; i < 100; i++) {
        D_807F8EC0[i] = NULL;
    }
    D_807F9050 = NULL;
    D_807F9054 = NULL;
    D_807F905C = 0;
    D_807F9060 = 0;
    if (mapIsBonusOrSpecial()) {
        D_807F9064 = arg0 + 0x70000;
    } else {
        D_807F9064 = arg0;
    }
}


s32 mapIsBonusOrSpecial(void) {
    if ((D_8076A0A8 == 6) || (D_8076A0A8 == 8) || (D_8076A0A8 == 0x37) || (D_8076A0A8 == 0x53) || (D_8076A0A8 == 0x6A) || (D_8076A0A8 == 0xC4) || (D_8076A0A8 == 0xC5)) {
        return 0;
    }
    return 1;
}

extern s16 D_807F9058;
extern s16 D_807F905A;

void matrixCacheResetStats(void) {
    D_807F9058 = 0;
    D_807F905A = 0;
}

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern RenderASub D_807F78C0[];
s32 matrixCacheHash(s32, s16, u8);
void *func_80610FE8(s32);
void heapFree(void *);
void heapFreeDeferred(void *);
#ifdef NON_MATCHING
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/61AA0/func_8065E138.s")
#endif

void *func_8065E634(s32 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4, u8 arg5) {
    void *sp18;
    u32 sp1C;
    s32 dummy;
    RenderANode *sp30;
    RenderANode **bucket;
    RenderANode *head;

    sp1C = (arg0 << 6) + (arg4 * 0x10) + 0x30;
    sp30 = func_80610FE8(sp1C);

    bucket = &D_807F8EC0[matrixCacheHash(arg0, arg2, arg3)];
    head = *bucket;
    *bucket = sp30;
    sp30->hash_next = head;
    if (head != NULL) {
        head->hash_prev = sp30;
    }
    sp30->hash_prev = NULL;

    sp18 = (u8 *)sp30 + 0x30;
    sp30->unk0 = D_8076A0B4[arg1];
    sp30->unk4 = D_8076A0B8[arg1];
    sp30->unk8 = D_8076A0BC[arg1];
    sp30->unk24 = arg2;
    sp30->unk29 = arg0;
    sp30->unk28 = arg3;
    memcpy(sp18, &D_807F78C0, arg0 << 6);
    sp30->unkC = D_8076A064;
    sp30->unk26 = arg4;
    D_807F905C += sp1C;
    D_807F9060++;
    sp30->unk10 = sp1C;

    if (arg5 == 0) {
        sp30->list_next = D_807F9050;
        if (D_807F9050 != NULL) {
            D_807F9050->list_prev = sp30;
        }
        sp30->list_prev = NULL;
        D_807F9050 = sp30;
        if (D_807F9054 == NULL) {
            D_807F9054 = sp30;
        }
    } else {
        sp30->list_prev = D_807F9054;
        if (D_807F9054 != NULL) {
            D_807F9054->list_next = sp30;
        }
        sp30->list_next = NULL;
        D_807F9054 = sp30;
        if (D_807F9050 == NULL) {
            D_807F9050 = sp30;
        }
    }

    return arg0 * 0x40 + (u8 *)sp18;
}

s32 func_8065E81C(u8 arg0, s16 arg1) {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;
    u8 sp43;
    RenderANode *node;
    RenderANode *next;
    RenderANode **bucket;
    u32 cond;

    cond = arg0;
    node = D_807F9054;
    sp43 = 0;
    if (cond != 0) {
        arg1 = 1;
    }

    while (1) {
        if (cond != 0) {
            if (!((u32)D_807F9064 < (u32)D_807F905C)) {
                break;
            }
        }
        if (node == NULL) {
            break;
        }
        next = node->list_prev;
        if ((cond == 0 && (u32)D_807F9064 < (u32)D_807F905C) || (u32)arg1 < (u32)(D_8076A064 - node->unkC)) {
            if (node == D_807F9054) {
                D_807F9054 = node->list_prev;
            }
            if (node == D_807F9050) {
                D_807F9050 = node->list_next;
            }
            if (node->list_next != NULL) {
                node->list_next->list_prev = node->list_prev;
            }
            if (node->list_prev != NULL) {
                node->list_prev->list_next = node->list_next;
            }
            D_807F905C -= node->unk10;
            D_807F9060--;
            bucket = &D_807F8EC0[matrixCacheHash(node->unk29, node->unk24, node->unk28)];
            if (node == *bucket) {
                *bucket = node->hash_next;
                if (node->hash_next != NULL) {
                    node->hash_next->hash_prev = NULL;
                }
            } else {
                if (node->hash_next != NULL) {
                    node->hash_next->hash_prev = node->hash_prev;
                }
                if (node->hash_prev != NULL) {
                    node->hash_prev->hash_next = node->hash_next;
                }
            }
            if ((u32)(D_8076A064 - node->unkC) >= 2) {
                heapFree(node);
                sp43 = 1;
            } else {
                heapFreeDeferred(node);
            }
        }
        node = next;
    }
    return sp43;
}


s32 matrixCacheDecayLimit(void) {
    D_807F9064 = ((u32)D_807F9064 * 3) >> 2;
    if ((u32)D_807F9064 < 0x10000) {
        return 0;
    }
    return func_8065E81C(1, 0);
}

s32 matrixCacheHash(s32 arg0, s16 arg1, u8 arg2) {
    return (arg1 * 16 + arg0 * 4 + arg2) % 100;
}

extern s32 D_807F9068;

void matrixCacheSetDefaultLimit(void) {
    if (D_807F9064 != 0x9C40) {
        D_807F9068 = D_807F9064;
    }
    D_807F9064 = 0x9C40;
}

void matrixCacheRestoreLimit(void) {
    D_807F9064 = D_807F9068;
}
