#include "common.h"

typedef struct AnimNode {
    /* 0x00 */ void **unk0;
    /* 0x04 */ void **unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 pad9;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[0x2];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ struct AnimNode *next;
} AnimNode;

typedef struct AnimActor {
    u8 pad[0x158];
    AnimNode *unk158;
} AnimActor;

typedef struct AnimInitData {
    u8 pad[0x10];
    s16 *unk10;
} AnimInitData;

extern s32 gCurrentMap;
extern u8 gPlayerCount;

void *heapAlloc(s32);
void *assetLoad(s32, s32, u8, s32);
void animListFree(AnimNode **);
void animNodeAdvanceTime(AnimNode *);
AnimNode *animGetNodeByIndex(AnimActor *, u32);
void assetFreeBuffer(void *, s32, s32);
void heapFree(void *);

void animListInit(AnimActor *arg0, AnimInitData *arg1) {
    AnimNode **next_ptr;
    AnimNode *node;
    s16 *src;
    s16 count;
    s32 num;
    s32 i;
    s32 alloc_size;
    void *res;
    void **unk0;
    void **unk4;
    u8 unk;

    if (arg0->unk158 != NULL) {
        if (gCurrentMap == 0x50 || gPlayerCount >= 2) {
            animListFree(&arg0->unk158);
        } else {
            return;
        }
    }
    src = arg1->unk10;
    next_ptr = &arg0->unk158;
    count = *src++;
    if (count != 0) {
        unk = 1;
        do {
            node = heapAlloc(sizeof(AnimNode));
            *next_ptr = node;
            num = *src;
            node->unk1C = 0;
            node->unkC = 0;
            node->unk10 = 0.0f;
            node->unk14 = 0.0f;
            node->unk18 = 0;
            node->unk1A = 0;
            node->unk22 = unk;
            node->unk20 = 0;
            node->unk21 = 0;
            node->unkA = num;
            node->unk1E = num;
            alloc_size = num * sizeof(void *);
            node->unk8 = src[1];
            next_ptr = &node->next;
            node->unk23 = src[2];
            src += 3;
            node->unk0 = heapAlloc(alloc_size);
            node->unk4 = heapAlloc(alloc_size);
            unk0 = node->unk0;
            unk4 = node->unk4;
            i = 0;
            if (num > 0) {
                do {
                    res = assetLoad(0x19, *src, unk, 0);
                    i++;
                    *unk0 = res;
                    *unk4 = res;
                    unk0++;
                    unk4++;
                    src++;
                } while (i != num);
            }
        } while (--count != 0);
    }
    *next_ptr = NULL;
}

Gfx *animSetSegments(Gfx *glist, AnimActor *actor) {
    AnimNode *node;
    Gfx *temp;

    for (node = actor->unk158; node != NULL; node = node->next) {
        temp = glist;
        if (node->unk23 != 0) {
            void *addr = node->unk0[node->unkC];
            temp->words.w0 = 0xDB060000 | ((node->unk8 * 4) & 0xFFFF);
            glist++;
            temp->words.w1 = osVirtualToPhysical(addr);
        }
    }
    return glist;
}

void animListUpdate(AnimActor *actor) {
    AnimNode *node;

    for (node = actor->unk158; node != NULL; node = node->next) {
        if (node->unk22 == 0) {
            animNodeAdvanceTime(node);
        }
    }
}

void animNodeAdvanceTime(AnimNode *arg0) {
    s16 temp_a1;
    s32 temp_ft3;

    switch (arg0->unk20) {
    case 0: {
        f32 temp_fv0;
        s32 temp_lo;
        s16 temp_v0_2;

        arg0->unk14 += arg0->unk10;
        temp_fv0 = arg0->unk14;
        temp_ft3 = (s32)temp_fv0;
        arg0->unkC += temp_ft3;
        arg0->unk14 = temp_fv0 - (f32)temp_ft3;
        temp_a1 = arg0->unk1E;
        if (arg0->unkC >= temp_a1) {
            temp_lo = arg0->unkC / temp_a1;
            temp_v0_2 = arg0->unk18;
            arg0->unk1A += temp_lo;
            if (arg0->unk1A >= temp_v0_2 && temp_v0_2 != -1) {
                arg0->unkC = temp_a1 - 1;
                arg0->unk22 = 1;
                arg0->unk14 = 1.0f;
                if (arg0->unk21 == 1) {
                    arg0->unk20 = 1;
                    return;
                }
            } else {
                switch (arg0->unk21) {
                case 0:
                    arg0->unkC = arg0->unkC % temp_a1;
                    if (arg0->unkC < arg0->unk1C) {
                        arg0->unkC = arg0->unk1C;
                        return;
                    }
                    break;
                case 1:
                    if (temp_lo != 0) {
                        arg0->unk20 = 1;
                        arg0->unkC = temp_a1 - 1;
                        arg0->unk14 = 1.0f;
                        return;
                    }
                    break;
                default:
                    return;
                }
            }
        } else {
            return;
        }
        break;
    }
    case 1: {
        f32 temp_fv0_2;
        s32 temp_a2;
        s16 temp_v0_6;
        s32 temp_lo_2;
        s32 inc;

        arg0->unk14 -= arg0->unk10;
        temp_fv0_2 = arg0->unk14;
        if ((f64)temp_fv0_2 < 0.0) {
            s32 temp_v0_5 = (s32)temp_fv0_2 - 1;
            arg0->unkC = (s16)(arg0->unkC + (u32)temp_v0_5); // FAKE: u32 cast keeps the add unreassociated (-1 folded into v0)
            arg0->unk14 = temp_fv0_2 - (f32)temp_v0_5;
        }
        if (arg0->unkC < 0) {
            temp_a2 = -arg0->unkC;
            temp_a1 = arg0->unk1E;
            temp_v0_6 = arg0->unk18;
            temp_lo_2 = temp_a2 / temp_a1;
            arg0->unk1A = (s16)(arg0->unk1A + temp_lo_2 + 1);
            if (arg0->unk1A >= temp_v0_6 && temp_v0_6 != -1) {
                arg0->unkC = 0;
                arg0->unk22 = 1;
                arg0->unk14 = 0.0f;
                if (arg0->unk21 == 1) {
                    arg0->unk20 = 0;
                    return;
                }
            } else {
                switch (arg0->unk21) {
                case 0:
                    arg0->unkC = temp_a2 % (temp_a1 - 1);
                    if (arg0->unkC != 0) {
                        arg0->unkC = (temp_a1 - arg0->unkC) - 1;
                        return;
                    }
                    break;
                case 1:
                    inc = temp_lo_2 + 1;
                    if (inc) {} // FAKE: second read keeps lo+1 a real variable (v0) instead of folding to lo != -1
                    if (inc) {
                        arg0->unkC = 0;
                        arg0->unk20 = 0;
                        if (arg0->unkC < arg0->unk1C) {
                            arg0->unkC = arg0->unk1C;
                        }
                        arg0->unk14 = 0.0f;
                    }
                    break;
                default:
                    return;
                }
            }
        }
        break;
    }
    }
}

s32 animGetNodeItem(void *arg0, s32 arg1, s16 arg2) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node) {
        goto yes;
    }
    return 0;
yes:
    return ((s32 *)node->unk0)[arg2];
}

void animSetNodeItem(void *arg0, s32 arg1, s16 arg2, s32 arg3) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        if (arg2 < node->unkA) {
            ((s32 *)node->unk0)[arg2] = arg3;
        }
    }
}

void animSetSpeed(void *arg0, s32 arg1, f32 arg2) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk10 = arg2;
    }
}

void animSetDirection(void *arg0, s32 arg1, u8 arg2) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk20 = arg2;
    }
}

void animSetLoopMode(void *arg0, s32 arg1, u8 arg2) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk21 = arg2;
    }
}

void animSetFrameAndSubframe(void *arg0, s32 arg1, s16 arg2, f32 arg3) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unkC = arg2;
        node->unk14 = arg3;
    }
}

void animSetLoopLimit(void *arg0, s32 arg1, s16 arg2) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk18 = arg2;
        node->unk1A = 0;
        node->unk22 = 0;
    }
}

void animSetFinished(void *arg0, s32 arg1, u8 arg2) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk22 = arg2;
    }
}

void animSetStartFrame(void *arg0, s32 arg1, s16 arg2) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk1C = arg2;
    }
}

void animSetEndFrame(void *arg0, s32 arg1, s16 arg2) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk1E = arg2;
    }
}

void animResetEndFrame(void *arg0, s32 arg1) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk1E = node->unkA;
    }
}

void animClearStartFrame(void *arg0, s32 arg1) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node != NULL) {
        node->unk1C = 0;
    }
}

s32 animIsPlaying(void *arg0, s32 arg1) {
    AnimNode *node = animGetNodeByIndex(arg0, arg1);
    if (node) {
        goto yes;
    }
    return 0;
yes:
    return (node->unk22 == 0) ? 1 : 0;
}

AnimNode *animGetNodeByIndex(AnimActor *actor, u32 count) {
    AnimNode *node = actor->unk158;
    if (count != 0) {
        do {
            if (node != NULL) {
                node = node->next;
            } else {
                return NULL;
            }
        } while (--count != 0);
    }
    return node;
}

void animListFree(AnimNode **arg0) {
    AnimNode *node = *arg0;
    AnimNode *next;
    void **arr;
    void **temp;
    s32 i;

    if (node != NULL) {
        do {
            temp = node->unk4;
            i = 0;
            if (node->unkA > 0) {
                arr = temp;
                do {
                    assetFreeBuffer(*arr, 0x1E6, 0x2C);
                    i++;
                    arr++;
                } while (i < node->unkA);
            }
            heapFree(node->unk0);
            heapFree(node->unk4);
            next = node->next;
            heapFree(node);
            node = next;
        } while (node != NULL);
    }
    *arg0 = NULL;
}
