#include "common.h"
#include "proto/global/15050.h"
#include "proto/global/5650.h"

typedef struct QueuedFunction {
    struct QueuedFunction *next;
    void (*callback)(s32, s32, s32);
    u32 time;
    s32 param0;
    s32 param1;
    s32 param2;
} QueuedFunction;

extern s32 gGameFrameCounter;
extern QueuedFunction *gTimerQueue;

void timerQueueInit(void) {
    gTimerQueue = NULL;
}

s32 func_8060095C(s32 funcOffset, s32 *valA, s32 *valB) {
    *valA += 0x50505050;
    *valB += 0x50505050;
    return funcOffset + 0x3FFF00FF;
}

void timerQueueAdd(void *callback, s32 delay, s32 param0, s32 param1, s32 param2) {
    QueuedFunction *curr;
    QueuedFunction *node;
    QueuedFunction *prev;
    s32 pad[2];
    s32 piIoResult;
    s32 (*piReadIo)(u32, s32 *);
    s32 expectedVal;
    s32 checkAddress;

    prev = NULL;
    node = heapAlloc(0x18);
    expectedVal = 0xC6F0AFA9;
    checkAddress = 0x5FAFBA0C;
    piReadIo = (s32 (*)(u32, s32 *))func_8060095C((s32)osPiReadIo + 0xC000FF01, &expectedVal, &checkAddress);
    piReadIo(checkAddress, &piIoResult);
    if (piIoResult != expectedVal) {
        delay *= 2;
    }
    node->callback = callback;
    node->param0 = param0;
    node->param1 = param1;
    node->param2 = param2;
    node->time = gGameFrameCounter + delay;
    node->next = NULL;
    curr = gTimerQueue;
    if (curr != NULL) {
        while (curr->next != NULL && (node->time & 0x7FFFFFFF) >= (curr->time & 0x7FFFFFFF)) {
            prev = curr;
            curr = curr->next;
        }
        if ((node->time & 0x7FFFFFFF) < (curr->time & 0x7FFFFFFF)) {
            node->next = curr;
            if (prev != NULL) {
                prev->next = node;
            } else {
                gTimerQueue = node;
            }
        } else {
            curr->next = node;
        }
    } else {
        gTimerQueue = node;
    }
}

void timerQueueUpdate(void) {
    QueuedFunction *node = gTimerQueue;
    s32 done = 0;

    while (node != NULL && done == 0) {
        if (gGameFrameCounter >= (node->time & 0x7FFFFFFF)) {
            node->callback(node->param0, node->param1, node->param2);
            heapFree(node);
            node = node->next;
        } else {
            done = 1;
        }
    }
    gTimerQueue = node;
}

void timerQueueCancel(void *callback) {
    QueuedFunction *node = gTimerQueue;
    QueuedFunction *prev = NULL;

    while (node != NULL) {
        if (((void *)node->callback == callback) || ((callback == NULL) && (node->time & 0x80000000))) {
            heapFree(node);
            node = node->next;
            if (prev != NULL) {
                prev->next = node;
            } else {
                gTimerQueue = node;
            }
        } else {
            prev = node;
            node = node->next;
        }
    }
}

void timerQueuePurgeFlagged(void) {
    QueuedFunction *node = gTimerQueue;
    QueuedFunction *prev = NULL;
    s32 done = 0;

    while (node != NULL && done == 0) {
        if ((node->time & 0x7FFFFFFF) < gGameFrameCounter) {
            if (node->time & 0x80000000) {
                if (prev != NULL) {
                    prev->next = node->next;
                } else {
                    gTimerQueue = node->next;
                }
                heapFree(node);
            } else {
                prev = node;
            }
            node = node->next;
        } else {
            done = 1;
        }
    }
}
