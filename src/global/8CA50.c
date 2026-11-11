#include "common.h"
#include "actor.h"
#include "proto/global/15050.h"
#include "proto/global/6AD90.h"
#include "proto/global/8CA50.h"

extern s32 gCurrentMap;
extern u8 gPlayerCount;


void animListInit(Actor *actor, AnimInitData *initData) {
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

    if (actor->animList != NULL) {
        if (gCurrentMap == 0x50 || gPlayerCount >= 2) {
            animListFree(&actor->animList);
        } else {
            return;
        }
    }
    src = initData->unk10;
    next_ptr = &actor->animList;
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

Gfx *animSetSegments(Gfx *glist, Actor *actor) {
    AnimNode *node;
    Gfx *temp;

    for (node = actor->animList; node != NULL; node = node->next) {
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

void animListUpdate(Actor *actor) {
    AnimNode *node;

    for (node = actor->animList; node != NULL; node = node->next) {
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

s32 animGetNodeItem(Actor *actor, s32 index, s16 itemIndex) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (!node) {
        return 0;
    }
    return ((s32 *)node->unk0)[itemIndex];
}

void animSetNodeItem(Actor *actor, s32 index, s16 itemIndex, s32 value) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        if (itemIndex < node->unkA) {
            ((s32 *)node->unk0)[itemIndex] = value;
        }
    }
}

void animSetSpeed(Actor *actor, s32 index, f32 animSpeed) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk10 = animSpeed;
    }
}

void animSetDirection(Actor *actor, s32 index, u8 direction) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk20 = direction;
    }
}

void animSetLoopMode(Actor *actor, s32 index, u8 loopMode) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk21 = loopMode;
    }
}

void animSetFrameAndSubframe(Actor *actor, s32 index, s16 frame, f32 subframe) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unkC = frame;
        node->unk14 = subframe;
    }
}

void animSetLoopLimit(Actor *actor, s32 index, s16 loopLimit) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk18 = loopLimit;
        node->unk1A = 0;
        node->unk22 = 0;
    }
}

void animSetFinished(Actor *actor, s32 index, u8 finished) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk22 = finished;
    }
}

void animSetStartFrame(Actor *actor, s32 index, s16 startFrame) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk1C = startFrame;
    }
}

void animSetEndFrame(Actor *actor, s32 index, s16 endFrame) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk1E = endFrame;
    }
}

void animResetEndFrame(Actor *actor, s32 index) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk1E = node->unkA;
    }
}

void animClearStartFrame(Actor *actor, s32 index) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->unk1C = 0;
    }
}

s32 animIsPlaying(Actor *actor, s32 index) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (!node) {
        return 0;
    }
    return (node->unk22 == 0) ? 1 : 0;
}

AnimNode *animGetNodeByIndex(Actor *actor, u32 count) {
    AnimNode *node = actor->animList;
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
    void **buffers;
    s32 i;

    if (node != NULL) {
        do {
            buffers = node->unk4;
            for (i = 0; i < node->unkA; i++) {
                assetFreeBuffer(buffers[i], 0x1E6, 0x2C);
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
