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

extern s32 D_8076A0A8;
extern u8 D_807FC928;

void *func_80610FE8(s32);
void *func_8066B0F8(s32, s32, u8, s32);
void animListFree(AnimNode **);
void func_80687FC8(AnimNode *);
AnimNode *animGetNodeByIndex(AnimActor *, u32);
void func_8066B434(void *, s32, s32);
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
        if (D_8076A0A8 == 0x50 || D_807FC928 >= 2) {
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
            node = func_80610FE8(sizeof(AnimNode));
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
            node->unk0 = func_80610FE8(alloc_size);
            node->unk4 = func_80610FE8(alloc_size);
            unk0 = node->unk0;
            unk4 = node->unk4;
            i = 0;
            if (num > 0) {
                do {
                    res = func_8066B0F8(0x19, *src, unk, 0);
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
            func_80687FC8(node);
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8CA50/func_80687FC8.s")

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
                    func_8066B434(*arr, 0x1E6, 0x2C);
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
