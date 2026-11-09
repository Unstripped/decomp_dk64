#include "common.h"
#include "proto/global/15050.h"
#include "proto/global/6AD90.h"
#include "proto/global/8CA50.h"

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


void animListInit(AnimActor *actor, AnimInitData *initData) {
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

    if (actor->unk158 != NULL) {
        if (gCurrentMap == 0x50 || gPlayerCount >= 2) {
            animListFree(&actor->unk158);
        } else {
            return;
        }
    }
    src = initData->unk10;
    next_ptr = &actor->unk158;
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

void animNodeAdvanceTime(AnimNode *node) {
    s16 endFrame;
    s32 frameDelta;

    switch (node->unk20) {
    case 0: {
        f32 subframe;
        s32 loopCount;
        s16 loopLimit;

        node->unk14 += node->unk10;
        subframe = node->unk14;
        frameDelta = (s32)subframe;
        node->unkC += frameDelta;
        node->unk14 = subframe - (f32)frameDelta;
        endFrame = node->unk1E;
        if (node->unkC >= endFrame) {
            loopCount = node->unkC / endFrame;
            loopLimit = node->unk18;
            node->unk1A += loopCount;
            if (node->unk1A >= loopLimit && loopLimit != -1) {
                node->unkC = endFrame - 1;
                node->unk22 = 1;
                node->unk14 = 1.0f;
                if (node->unk21 == 1) {
                    node->unk20 = 1;
                    return;
                }
            } else {
                switch (node->unk21) {
                case 0:
                    node->unkC = node->unkC % endFrame;
                    if (node->unkC < node->unk1C) {
                        node->unkC = node->unk1C;
                        return;
                    }
                    break;
                case 1:
                    if (loopCount != 0) {
                        node->unk20 = 1;
                        node->unkC = endFrame - 1;
                        node->unk14 = 1.0f;
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
        f32 subframe;
        s32 negFrame;
        s16 loopLimit;
        s32 loopCount;
        s32 inc;

        node->unk14 -= node->unk10;
        subframe = node->unk14;
        if ((f64)subframe < 0.0) {
            u32 step = (s32)subframe - 1;
            node->unkC += step;
            node->unk14 = subframe - (f32)(s32)step;
        }
        if (node->unkC < 0) {
            negFrame = -node->unkC;
            endFrame = node->unk1E;
            loopLimit = node->unk18;
            loopCount = negFrame / endFrame;
            node->unk1A = (s16)(node->unk1A + loopCount + 1);
            if (node->unk1A >= loopLimit && loopLimit != -1) {
                node->unkC = 0;
                node->unk22 = 1;
                node->unk14 = 0.0f;
                if (node->unk21 == 1) {
                    node->unk20 = 0;
                    return;
                }
            } else {
                switch (node->unk21) {
                case 0:
                    node->unkC = negFrame % (endFrame - 1);
                    if (node->unkC != 0) {
                        node->unkC = (endFrame - node->unkC) - 1;
                        return;
                    }
                    break;
                case 1:
                    inc = loopCount + 1;
                    if (inc) {} // FAKE: second read keeps lo+1 a real variable (v0) instead of folding to lo != -1
                    if (inc) {
                        node->unkC = 0;
                        node->unk20 = 0;
                        if (node->unkC < node->unk1C) {
                            node->unkC = node->unk1C;
                        }
                        node->unk14 = 0.0f;
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

s32 animGetNodeItem(void *actor, s32 index, s16 itemIndex) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (!node) {
        return 0;
    }
    return ((s32 *)node->unk0)[itemIndex];
}

void animSetNodeItem(void *actor, s32 index, s16 itemIndex, s32 value) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        if (itemIndex < node->unkA) {
            ((s32 *)node->unk0)[itemIndex] = value;
        }
    }
}

void animSetSpeed(void *actor, s32 index, f32 animSpeed) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk10 = animSpeed;
    }
}

void animSetDirection(void *actor, s32 index, u8 direction) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk20 = direction;
    }
}

void animSetLoopMode(void *actor, s32 index, u8 loopMode) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk21 = loopMode;
    }
}

void animSetFrameAndSubframe(void *actor, s32 index, s16 frame, f32 subframe) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unkC = frame;
        node->unk14 = subframe;
    }
}

void animSetLoopLimit(void *actor, s32 index, s16 loopLimit) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk18 = loopLimit;
        node->unk1A = 0;
        node->unk22 = 0;
    }
}

void animSetFinished(void *actor, s32 index, u8 finished) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk22 = finished;
    }
}

void animSetStartFrame(void *actor, s32 index, s16 startFrame) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk1C = startFrame;
    }
}

void animSetEndFrame(void *actor, s32 index, s16 endFrame) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk1E = endFrame;
    }
}

void animResetEndFrame(void *actor, s32 index) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk1E = node->unkA;
    }
}

void animClearStartFrame(void *actor, s32 index) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk1C = 0;
    }
}

s32 animIsPlaying(void *actor, s32 index) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (!node) {
        return 0;
    }
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

void animListFree(AnimNode **list) {
    AnimNode *node = *list;
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
    *list = NULL;
}
