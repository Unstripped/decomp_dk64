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

s32 func_8060095C(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg1 += 0x50505050;
    *arg2 += 0x50505050;
    return arg0 + 0x3FFF00FF;
}

void timerQueueAdd(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    QueuedFunction *curr;
    QueuedFunction *node;
    QueuedFunction *prev;
    s32 pad1;
    s32 pad2;
    s32 sp30;
    s32 pad3;
    s32 sp28;
    s32 sp24;

    prev = NULL;
    node = heapAlloc(0x18);
    sp28 = 0xC6F0AFA9;
    sp24 = 0x5FAFBA0C;
    ((s32 (*)(u32, s32 *))func_8060095C((s32)osPiReadIo + 0xC000FF01, &sp28, &sp24))(sp24, &sp30);
    if (sp30 != sp28) {
        arg1 *= 2;
    }
    node->callback = arg0;
    node->arg0 = arg2;
    node->arg1 = arg3;
    node->arg2 = arg4;
    node->time = D_8076A068 + arg1;
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
