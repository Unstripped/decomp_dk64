#include "sched.h"
#include "common.h"
#include "actor.h"
#include "audio_config.h"
#include "proto/global/137120.h"
#include "proto/global/13980.h"
#include "proto/global/13D170.h"
#include "proto/global/13E0E0.h"
#include "proto/global/13E160.h"
#include "proto/global/6710.h"
#include "proto/global/7130.h"

typedef struct AudioDmaNode {
    struct AudioDmaNode *next;
    struct AudioDmaNode *prev;
    u32 startAddr;
    u32 lastFrame;
    void *ptr;
} AudioDmaNode;

typedef struct AudioTask {
    void *sampleBuffer;
    s16 sampleCount;
    s16 pad6;
    struct AudioTask *next;
    s32 state;
    u32 flags;
    void *framebuffer;
    OSTask task;
    void *client;
    OSMesgQueue *msgQ;
    OSMesg msg;
    u32 pad64;
    s16 msgBuf;
    s16 pad6A;
    void *self;
} AudioTask;

typedef struct AudioContext {
    void *cmdBuffers[2];
    AudioTask *tasks[3];
} AudioContext;

// Effect parameter tables for the two aux buses (AudioInitArgs.params).
typedef struct AudioSynthesizerConfig {
    s32 fxParams[2][0x10C / 4];
} AudioSynthesizerConfig;

// n_audio globals passed to n_alInit/n_alClose. n_alInit also points n_syn at this block, and
// n_audio's synthesizer outgrows libaudio's ALGlobals, hence the tail.
typedef struct AudioAlState {
    ALGlobals globals;
    u8 synthState[0x2760 - sizeof(ALGlobals)];
} AudioAlState;

typedef struct AudioDmaContext {
    u8 initialized;
    u8 pad1[3];
    AudioDmaNode *firstUsed;
    AudioDmaNode *firstFree;
} AudioDmaContext;

extern s32 sAudioFreq;

// .data 0x807452C0-0x807454F0
u32 D_807452C0 = 0;
u32 D_807452C4 = 0;
s32 D_807452C8 = 0;
s8 D_807452CC = 0;
AudioSynthesizerConfig D_807452D0 = { {
    0x8, 0x2270, 0x0, 0xC0, 0x2666, 0xFFFFD99A,
    0x0, 0x0, 0x0, 0x0, 0xC0, 0x188,
    0x2666, 0xFFFFD99A, 0x2B84, 0x0, 0x0, 0x0,
    0x370, 0xB00, 0x4000, 0xFFFFC000, 0x11EB, 0x0,
    0x0, 0x0, 0x420, 0x840, 0x2000, 0xFFFFE000,
    0x0, 0x0, 0x0, 0x0, 0xDC8, 0x1818,
    0x4000, 0xFFFFC000, 0x11EB, 0x0, 0x0, 0x0,
    0xE78, 0x14A8, 0x2000, 0xFFFFE000, 0x0, 0x0,
    0x0, 0x0, 0x14A8, 0x1740, 0x2000, 0xFFFFE000,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1978,
    0x32C8, 0xFFFFCD38, 0x0, 0x17C, 0xA, 0x0,
    0x0, 0x1, 0xA50, 0x0, 0x898, 0x3334,
    0x0, 0x7335, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0,
} };
s32 D_807454E8[2] = { 1, 0 };

// .bss 0x8076D4C0-0x80770560
SchedClient D_8076D4C0;
AudioContext D_8076D4D0;
OSThread D_8076D4E8;
OSMesgQueue D_8076D698;
OSMesg D_8076D6B0[8];
OSMesgQueue D_8076D6D0;
OSMesg D_8076D6E8[8];
AudioAlState D_8076D708;
AudioDmaNode D_8076FE68[40];
AudioDmaContext D_80770188;
s32 D_80770194;
s32 D_80770198;
s32 D_8077019C;
s32 D_807701A0;
AudioAlState *D_807701A4;
OSIoMesg D_807701A8[32];
OSMesgQueue D_807704A8;
OSMesg D_807704C0[32];
u8 D_80770540[0x18];
s32 D_80770558[2];

#include "common.h"
#include "actor.h"


void audioThreadInit(AudioInitArgs *initArgs, s32 threadPriority, AudioTaskConfig *taskConfig) {
    void **cmdBuf;
    AudioSynthesizerConfig synConfig;
    u32 i;

    initArgs->dmaNew = audioDmaNew;
    initArgs->outputRate = sAudioFreq;
    D_80770194 = 0x228;
    D_8077019C = 0x398;
    synConfig = D_807452D0;
    initArgs->params[0] = synConfig.fxParams[0];
    initArgs->params[1] = synConfig.fxParams[1];
    n_alInit(&D_8076D708.globals, initArgs);
    D_807701A4 = &D_8076D708;

    D_8076FE68[0].prev = NULL;
    D_8076FE68[0].next = NULL;

    for (i = 0; (i ^ 0) < 39; i++) { // FAKE: x ^ 0 keeps i from being strength-reduced away (steers LFTR)
        if (taskConfig != 0) {} // FAKE: dead use of taskConfig swaps $s4/$s5 and the i/prev register order
        alLink((ALLink *)&D_8076FE68[i + 1], (ALLink *)&D_8076FE68[i]);
        D_8076FE68[i].ptr = alHeapDBAlloc(NULL, 0, initArgs->heap, 1, 0x800);
    }
    D_8076FE68[i].ptr = alHeapDBAlloc(NULL, 0, initArgs->heap, 1, 0x800);

    for (cmdBuf = D_8076D4D0.cmdBuffers; cmdBuf < &D_8076D4D0.cmdBuffers[2]; cmdBuf++) {
        *cmdBuf = alHeapDBAlloc(NULL, 0, initArgs->heap, 1, taskConfig->cmdCount * 8);
    }

    D_807701A0 = taskConfig->cmdCount;
    for (i = 0; i < 3; i++) {
        D_8076D4D0.tasks[i] = alHeapDBAlloc(NULL, 0, initArgs->heap, 1, sizeof(AudioTask));
        D_8076D4D0.tasks[i]->msgBuf = 2;
        D_8076D4D0.tasks[i]->self = D_8076D4D0.tasks[i];
        D_8076D4D0.tasks[i]->sampleBuffer = alHeapDBAlloc(NULL, 0, initArgs->heap, 1, D_8077019C * 4);
    }
    osCreateMesgQueue(&D_8076D6D0, D_8076D6E8, 8);
    osCreateMesgQueue(&D_8076D698, D_8076D6B0, 8);
    osCreateMesgQueue(&D_807704A8, D_807704C0, 0x20);

    osCreateThread(&D_8076D4E8, 4, audioThreadMain, NULL, D_8076FE68, threadPriority);
}

void audioThreadStart(void) {
    D_807452CC = 1;
    osStartThread(&D_8076D4E8);
}

void audioThreadStop(s32 unused) {
    if (D_807452CC != 0) {
        osStopThread(&D_8076D4E8);
    }
}

extern SchedStruct gScheduler;

void audioThreadMain(void *arg) {
    s32 done;
    OSMesg receivedMsg;
    s32 first;
    AudioTask *prevAiTask;
    s32 numBuffers;
    done = 0;
    prevAiTask = NULL;
    first = 1;
    schedAddClient(&gScheduler, &D_8076D4C0, &D_8076D698, 2, 2);
    osSendMesg(&D_8076D698, (OSMesg)5, OS_MESG_NOBLOCK);
    numBuffers = 3;
    do {
        osRecvMesg(&D_8076D698, &receivedMsg, OS_MESG_BLOCK);
        switch ((s32)receivedMsg) {
        case 5:
            if (gScheduler.audioListHead != NULL) {
                osSendMesg(&gScheduler.interruptQ, (OSMesg)0x29E, OS_MESG_BLOCK);
            }
            audioBuildTask(D_8076D4D0.tasks[D_807452C0 % numBuffers], prevAiTask);
            prevAiTask = D_8076D4D0.tasks[(D_807452C0 + 1) % numBuffers];
            if (!first) {
                osRecvMesg(&D_8076D6D0, &receivedMsg, OS_MESG_BLOCK);
                audioCheckAiLength(prevAiTask);
            }
            first = 0;
            seqUpdateVolumeFades();
            break;
        case 10:
            done = 1;
            break;
        }
    } while (!done);
    n_alClose(&D_8076D708.globals);
}

extern u8 D_805FB000[];
extern u8 D_805FB0D0[];
extern u64 func_80741310[];
extern u64 D_80760590[];


s32 audioBuildTask(AudioTask *task, AudioTask *prevTask) {
    s16 *physSampleBuf;
    s32 pad[1];
    s32 cmdCount;
    s32 aiLen;
    Acmd *cmdEnd;
    s32 count;
    s32 *holdFrames;

    physSampleBuf = (s16 *)osVirtualToPhysical(task->sampleBuffer);
    audioDmaFrameUpdate();
    aiLen = IO_READ(AI_LEN_REG) >> 2;
    if (prevTask != NULL) {
        osAiSetNextBuffer(prevTask->sampleBuffer, prevTask->sampleCount * 4);
    }
    holdFrames = &D_80770558[0];
    if ((aiLen < 0x5C) && ((count = *holdFrames) == 0)) {
        task->sampleCount = D_8077019C;
        count = (count & 0) + 2; // FAKE: folds to 2 after const-prop; keeps li in count's register ($v0) instead of a scratch li
        *holdFrames = count;
    } else {
        count = *holdFrames;
        if ((aiLen >= 0x115) && (count == 0)) {
            task->sampleCount = D_80770194;
            count = (count & 0) + 2; // FAKE: folds to 2 after const-prop; keeps li in count's register ($v0) instead of a scratch li
            *holdFrames = count;
        } else {
            task->sampleCount = 0x2E0;
            if (count != 0) {
                count--;
                *holdFrames = count;
            }
        }
    }

    cmdEnd = n_alAudioFrame(D_8076D4D0.cmdBuffers[D_807452C8], &cmdCount, physSampleBuf, task->sampleCount);
    if (cmdCount == 0) {
        return 0;
    }

    task->next = NULL;
    task->msgQ = &D_8076D6D0;
    task->msg = (OSMesg)&task->msgBuf;
    task->flags = 1;
    task->client = &D_8076D4C0;
    task->task.t.data_ptr = (u64 *)D_8076D4D0.cmdBuffers[D_807452C8];
    task->task.t.data_size = (cmdEnd - (Acmd *)D_8076D4D0.cmdBuffers[D_807452C8]) * sizeof(Acmd);
    task->task.t.type = M_AUDTASK;
    task->task.t.ucode_boot = (u64 *)D_805FB000;
    task->task.t.ucode_boot_size = D_805FB0D0 - D_805FB000;
    task->task.t.flags = 0;
    task->task.t.ucode = func_80741310;
    task->task.t.ucode_data = D_80760590;
    task->task.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    task->task.t.yield_data_ptr = NULL;
    task->task.t.yield_data_size = OS_YIELD_AUDIO_SIZE;

    osWritebackDCacheAll();
    osSendMesg(schedGetCmdQueue(&gScheduler), &task->next, OS_MESG_NOBLOCK);
    D_807452C8 ^= 1;
    return 1;
}

void audioCheckAiLength(AudioTask *unused) {
    s32 zero = 0; // FAKE: variable index keeps a lui/%lo pair per D_807454E8 access instead of &D_807454E8 CSE'd into $v0 (Q0099)
    if (((osAiGetLength() >> 2) == 0) && (D_807454E8[zero] == 0)) {
        D_807454E8[zero] = 0;
    }
}


s32 audioDmaCallback(u32 addr, s32 len, void *state) {
    void *dmaBuf;
    s32 pad[3];
    AudioDmaNode *node;
    AudioDmaNode *last;
    s32 delta;
    s32 end;

    last = NULL;
    node = D_80770188.firstUsed;
    while (node != NULL) {
        end = node->startAddr + 0x800;
        if (addr < node->startAddr) {
            break;
        }
        if ((s32)addr + len <= end) {
            node->lastFrame = D_807452C0;
            dmaBuf = (u8 *)node->ptr + (addr - node->startAddr);
            return osVirtualToPhysical(dmaBuf);
        }
        last = node;
        node = node->next;
    }

    node = D_80770188.firstFree;
    if (node == NULL) {
        return osVirtualToPhysical(D_80770188.firstUsed);
    }

    D_80770188.firstFree = node->next;
    alUnlink((ALLink *)node);
    if (last != NULL) {
        alLink((ALLink *)node, (ALLink *)last);
    } else if (D_80770188.firstUsed != NULL) {
        last = D_80770188.firstUsed;
        D_80770188.firstUsed = node;
        node->next = last;
        node->prev = NULL;
        last->prev = node;
    } else {
        D_80770188.firstUsed = node;
        node->next = NULL;
        node->prev = NULL;
    }

    delta = addr & 1;
    addr -= delta;
    node->startAddr = addr;
    node->lastFrame = D_807452C0;
    dmaBuf = node->ptr;
    osPiStartDma(&D_807701A8[D_807452C4++], OS_MESG_PRI_HIGH, OS_READ, addr, dmaBuf, 0x800, &D_807704A8);
    return osVirtualToPhysical(dmaBuf) + delta;
}



void *audioDmaNew(AudioDmaContext **outContext) {
    if (D_80770188.initialized == 0) {
        D_80770188.firstUsed = NULL;
        D_80770188.firstFree = &D_8076FE68[0];
        D_80770188.initialized = 1;
    }
    *outContext = &D_80770188;
    return audioDmaCallback;
}


void audioDmaFrameUpdate(void) {
    s32 pad;
    OSMesg msg;
    AudioDmaNode *node;
    AudioDmaNode *next;
    u32 i;

    msg = NULL;
    for (i = 0; i < D_807452C4; i++) {
        osRecvMesg(&D_807704A8, &msg, OS_MESG_NOBLOCK);
    }
    for (node = D_80770188.firstUsed; node != NULL; node = next) {
        next = node->next;
        if ((node->lastFrame + 1) < D_807452C0) {
            if (node == D_80770188.firstUsed) {
                D_80770188.firstUsed = node->next;
            }
            alUnlink((ALLink *)node);
            if (D_80770188.firstFree != NULL) {
                alLink((ALLink *)node, (ALLink *)D_80770188.firstFree);
            } else {
                D_80770188.firstFree = node;
                node->next = NULL;
                node->prev = NULL;
            }
        }
    }
    D_807452C4 = 0;
    D_807452C0++;
}
