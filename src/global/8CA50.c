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
            node->startFrame = 0;
            node->frame = 0;
            node->speed = 0.0f;
            node->subframe = 0.0f;
            node->loopLimit = 0;
            node->loopCount = 0;
            node->finished = unk;
            node->direction = 0;
            node->loopMode = 0;
            node->itemCount = num;
            node->endFrame = num;
            alloc_size = num * sizeof(void *);
            node->segment = src[1];
            next_ptr = &node->next;
            node->bindSegment = src[2];
            src += 3;
            node->items = heapAlloc(alloc_size);
            node->buffers = heapAlloc(alloc_size);
            unk0 = node->items;
            unk4 = node->buffers;
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
        if (node->bindSegment != 0) {
            void *addr = node->items[node->frame];
            temp->words.w0 = 0xDB060000 | ((node->segment * 4) & 0xFFFF);
            glist++;
            temp->words.w1 = osVirtualToPhysical(addr);
        }
    }
    return glist;
}

void animListUpdate(Actor *actor) {
    AnimNode *node;

    for (node = actor->animList; node != NULL; node = node->next) {
        if (node->finished == 0) {
            animNodeAdvanceTime(node);
        }
    }
}

void animNodeAdvanceTime(AnimNode *node) {
    s16 endFrame;
    s32 frameDelta;

    switch (node->direction) {
    case 0: {
        f32 subframe;
        s32 loopCount;
        s16 loopLimit;

        node->subframe += node->speed;
        subframe = node->subframe;
        frameDelta = (s32)subframe;
        node->frame += frameDelta;
        node->subframe = subframe - (f32)frameDelta;
        endFrame = node->endFrame;
        if (node->frame >= endFrame) {
            loopCount = node->frame / endFrame;
            loopLimit = node->loopLimit;
            node->loopCount += loopCount;
            if (node->loopCount >= loopLimit && loopLimit != -1) {
                node->frame = endFrame - 1;
                node->finished = 1;
                node->subframe = 1.0f;
                if (node->loopMode == 1) {
                    node->direction = 1;
                    return;
                }
            } else {
                switch (node->loopMode) {
                case 0:
                    node->frame = node->frame % endFrame;
                    if (node->frame < node->startFrame) {
                        node->frame = node->startFrame;
                        return;
                    }
                    break;
                case 1:
                    if (loopCount != 0) {
                        node->direction = 1;
                        node->frame = endFrame - 1;
                        node->subframe = 1.0f;
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

        node->subframe -= node->speed;
        subframe = node->subframe;
        if ((f64)subframe < 0.0) {
            u32 step = (s32)subframe - 1;
            node->frame += step;
            node->subframe = subframe - (f32)(s32)step;
        }
        if (node->frame < 0) {
            negFrame = -node->frame;
            endFrame = node->endFrame;
            loopLimit = node->loopLimit;
            loopCount = negFrame / endFrame;
            node->loopCount = (s16)(node->loopCount + loopCount + 1);
            if (node->loopCount >= loopLimit && loopLimit != -1) {
                node->frame = 0;
                node->finished = 1;
                node->subframe = 0.0f;
                if (node->loopMode == 1) {
                    node->direction = 0;
                    return;
                }
            } else {
                switch (node->loopMode) {
                case 0:
                    node->frame = negFrame % (endFrame - 1);
                    if (node->frame != 0) {
                        node->frame = (endFrame - node->frame) - 1;
                        return;
                    }
                    break;
                case 1:
                    inc = loopCount + 1;
                    if (inc) {} // FAKE: second read keeps lo+1 a real variable (v0) instead of folding to lo != -1
                    if (inc) {
                        node->frame = 0;
                        node->direction = 0;
                        if (node->frame < node->startFrame) {
                            node->frame = node->startFrame;
                        }
                        node->subframe = 0.0f;
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
    return ((s32 *)node->items)[itemIndex];
}

void animSetNodeItem(Actor *actor, s32 index, s16 itemIndex, s32 value) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        if (itemIndex < node->itemCount) {
            ((s32 *)node->items)[itemIndex] = value;
        }
    }
}

void animSetSpeed(Actor *actor, s32 index, f32 animSpeed) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->speed = animSpeed;
    }
}

void animSetDirection(Actor *actor, s32 index, u8 direction) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->direction = direction;
    }
}

void animSetLoopMode(Actor *actor, s32 index, u8 loopMode) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->loopMode = loopMode;
    }
}

void animSetFrameAndSubframe(Actor *actor, s32 index, s16 frame, f32 subframe) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->frame = frame;
        node->subframe = subframe;
    }
}

void animSetLoopLimit(Actor *actor, s32 index, s16 loopLimit) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->loopLimit = loopLimit;
        node->loopCount = 0;
        node->finished = 0;
    }
}

void animSetFinished(Actor *actor, s32 index, u8 finished) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->finished = finished;
    }
}

void animSetStartFrame(Actor *actor, s32 index, s16 startFrame) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->startFrame = startFrame;
    }
}

void animSetEndFrame(Actor *actor, s32 index, s16 endFrame) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->endFrame = endFrame;
    }
}

void animResetEndFrame(Actor *actor, s32 index) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->endFrame = node->itemCount;
    }
}

void animClearStartFrame(Actor *actor, s32 index) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (node != NULL) {
        node->startFrame = 0;
    }
}

s32 animIsPlaying(Actor *actor, s32 index) {
    AnimNode *node = animGetNodeByIndex(actor, index);
    if (!node) {
        return 0;
    }
    return (node->finished == 0) ? 1 : 0;
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
            buffers = node->buffers;
            for (i = 0; i < node->itemCount; i++) {
                assetFreeBuffer(buffers[i], 0x1E6, 0x2C);
            }
            heapFree(node->items);
            heapFree(node->buffers);
            next = node->next;
            heapFree(node);
            node = next;
        } while (node != NULL);
    }
    *list = NULL;
}
