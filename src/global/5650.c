#include "common.h"

typedef struct QueuedFunction {
    struct QueuedFunction *next;
    void (*callback)(s32, s32, s32);
    u32 time;
    s32 arg0;
    s32 arg1;
    s32 arg2;
} QueuedFunction;

extern s32 D_8076A068;
extern QueuedFunction *gTimerQueue;
void heapFree(void *);
void *heapAlloc(s32);
s32 osPiReadIo(u32, u32 *);

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
    s32 pad1;
    s32 pad2;
    s32 piIoResult;
    s32 pad3;
    s32 expectedVal;
    s32 checkAddress;

    prev = NULL;
    node = heapAlloc(0x18);
    expectedVal = 0xC6F0AFA9;
    checkAddress = 0x5FAFBA0C;
    ((s32 (*)(u32, s32 *))func_8060095C((s32)osPiReadIo + 0xC000FF01, &expectedVal, &checkAddress))(checkAddress, &piIoResult);
    if (piIoResult != expectedVal) {
        delay *= 2;
    }
    node->callback = callback;
    node->arg0 = param0;
    node->arg1 = param1;
    node->arg2 = param2;
    node->time = D_8076A068 + delay;
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
        return;
    }
    gTimerQueue = node;
}

void timerQueueUpdate(void) {
    QueuedFunction *node = gTimerQueue;
    s32 done = 0;

    if (node != NULL) {
        do {
            if (D_8076A068 >= (node->time & 0x7FFFFFFF)) {
                node->callback(node->arg0, node->arg1, node->arg2);
                heapFree(node);
                node = node->next;
            } else {
                done = 1;
            }
        } while (node != NULL && done == 0);
    }
    gTimerQueue = node;
}

void timerQueueCancel(void *callback) {
    QueuedFunction *node = gTimerQueue;
    QueuedFunction *prev = NULL;

    if (node != NULL) {
        do {
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
        } while (node != NULL);
    }
}

void timerQueuePurgeFlagged(void) {
    QueuedFunction *node = gTimerQueue;
    QueuedFunction *prev = NULL;
    s32 done = 0;

    if (node != NULL) {
        do {
            s32 time = node->time;

            if ((u32)(time & 0x7FFFFFFF) < D_8076A068) {
                if (time & 0x80000000) {
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
        } while (node != NULL && done == 0);
    }
}
