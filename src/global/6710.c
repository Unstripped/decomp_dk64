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
u32 sAudioFrameCount = 0;
u32 sAudioDmaCount = 0;
s32 sAudioCmdBufferIndex = 0;
s8 sAudioThreadStarted = 0;
AudioSynthesizerConfig sAudioSynthConfig = { {
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

// .bss 0x8076D4C0-0x80770560
SchedClient sAudioSchedClient;
AudioContext sAudioMgr;
OSThread sAudioThread;
OSMesgQueue sAudioFrameMsgQ;
OSMesg sAudioFrameMsgBuf[8];
OSMesgQueue sAudioTaskDoneMsgQ;
OSMesg sAudioTaskDoneMsgBuf[8];
AudioAlState sAudioAlGlobals;
AudioDmaNode sAudioDmaBuffers[40];
AudioDmaContext sAudioDmaState;
s32 sAudioMinFrameSize;
s32 D_80770198;
s32 sAudioMaxFrameSize;
s32 sAudioMaxCmdCount;
AudioAlState *sAudioAlGlobalsPtr;
OSIoMesg sAudioDmaIoMsgs[32];
OSMesgQueue sAudioDmaMsgQ;
OSMesg sAudioDmaMsgBuf[32];
u8 D_80770540[0x18];

#include "common.h"
#include "actor.h"


void audioThreadInit(AudioInitArgs *initArgs, s32 threadPriority, AudioTaskConfig *taskConfig) {
    u32 i;
    AudioSynthesizerConfig synConfig;

    initArgs->dmaNew = audioDmaNew;
    initArgs->outputRate = sAudioFreq;
    sAudioMinFrameSize = 0x228;
    sAudioMaxFrameSize = 0x398;
    synConfig = sAudioSynthConfig;
    initArgs->params[0] = synConfig.fxParams[0];
    initArgs->params[1] = synConfig.fxParams[1];
    n_alInit(&sAudioAlGlobals.globals, initArgs);
    sAudioAlGlobalsPtr = &sAudioAlGlobals;

    sAudioDmaBuffers[0].prev = NULL;
    sAudioDmaBuffers[0].next = NULL;

    for (i = 0; i < 39; i++) {
        alLink((ALLink *)&sAudioDmaBuffers[i + 1], (ALLink *)&sAudioDmaBuffers[i]);
        sAudioDmaBuffers[i].ptr = alHeapAlloc(initArgs->heap, 1, 0x800);
    }
    sAudioDmaBuffers[i].ptr = alHeapAlloc(initArgs->heap, 1, 0x800);

    for (i = 0; i < 2; i++) {
        sAudioMgr.cmdBuffers[i] = alHeapAlloc(initArgs->heap, 1, taskConfig->cmdCount * sizeof(Acmd));
    }

    sAudioMaxCmdCount = taskConfig->cmdCount;
    for (i = 0; i < 3; i++) {
        sAudioMgr.tasks[i] = alHeapAlloc(initArgs->heap, 1, sizeof(AudioTask));
        sAudioMgr.tasks[i]->msgBuf = 2;
        sAudioMgr.tasks[i]->self = sAudioMgr.tasks[i];
        sAudioMgr.tasks[i]->sampleBuffer = alHeapAlloc(initArgs->heap, 1, sAudioMaxFrameSize * 4);
    }
    osCreateMesgQueue(&sAudioTaskDoneMsgQ, sAudioTaskDoneMsgBuf, 8);
    osCreateMesgQueue(&sAudioFrameMsgQ, sAudioFrameMsgBuf, 8);
    osCreateMesgQueue(&sAudioDmaMsgQ, sAudioDmaMsgBuf, 0x20);

    osCreateThread(&sAudioThread, 4, audioThreadMain, NULL, sAudioDmaBuffers, threadPriority);
}

void audioThreadStart(void) {
    sAudioThreadStarted = 1;
    osStartThread(&sAudioThread);
}

void audioThreadStop(s32 unused) {
    if (sAudioThreadStarted != 0) {
        osStopThread(&sAudioThread);
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
    schedAddClient(&gScheduler, &sAudioSchedClient, &sAudioFrameMsgQ, 2, 2);
    osSendMesg(&sAudioFrameMsgQ, (OSMesg)5, OS_MESG_NOBLOCK);
    numBuffers = 3;
    do {
        osRecvMesg(&sAudioFrameMsgQ, &receivedMsg, OS_MESG_BLOCK);
        switch ((s32)receivedMsg) {
        case 5:
            if (gScheduler.audioListHead != NULL) {
                osSendMesg(&gScheduler.interruptQ, (OSMesg)0x29E, OS_MESG_BLOCK);
            }
            audioBuildTask(sAudioMgr.tasks[sAudioFrameCount % numBuffers], prevAiTask);
            prevAiTask = sAudioMgr.tasks[(sAudioFrameCount + 1) % numBuffers];
            if (!first) {
                osRecvMesg(&sAudioTaskDoneMsgQ, &receivedMsg, OS_MESG_BLOCK);
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
    n_alClose(&sAudioAlGlobals.globals);
}

extern u8 D_805FB000[];
extern u8 D_805FB0D0[];
extern u64 func_80741310[];
extern u64 D_80760590[];


s32 audioBuildTask(AudioTask *task, AudioTask *prevTask) {
    static s32 sAudioFrameHoldCount;
    s16 *physSampleBuf;
    s32 pad[1];
    s32 cmdCount;
    s32 aiLen;
    Acmd *cmdEnd;
    s32 pad2[2];

    physSampleBuf = (s16 *)osVirtualToPhysical(task->sampleBuffer);
    audioDmaFrameUpdate();
    aiLen = IO_READ(AI_LEN_REG) >> 2;
    if (prevTask != NULL) {
        osAiSetNextBuffer(prevTask->sampleBuffer, prevTask->sampleCount * 4);
    }
    if ((aiLen < 0x5C) && (sAudioFrameHoldCount == 0)) {
        task->sampleCount = sAudioMaxFrameSize;
        sAudioFrameHoldCount = 2;
    } else if ((aiLen >= 0x115) && (sAudioFrameHoldCount == 0)) {
        task->sampleCount = sAudioMinFrameSize;
        sAudioFrameHoldCount = 2;
    } else {
        task->sampleCount = 0x2E0;
        if (sAudioFrameHoldCount != 0) {
            sAudioFrameHoldCount--;
        }
    }

    cmdEnd = n_alAudioFrame(sAudioMgr.cmdBuffers[sAudioCmdBufferIndex], &cmdCount, physSampleBuf, task->sampleCount);
    if (cmdCount == 0) {
        return 0;
    }

    task->next = NULL;
    task->msgQ = &sAudioTaskDoneMsgQ;
    task->msg = (OSMesg)&task->msgBuf;
    task->flags = 1;
    task->client = &sAudioSchedClient;
    task->task.t.data_ptr = (u64 *)sAudioMgr.cmdBuffers[sAudioCmdBufferIndex];
    task->task.t.data_size = (cmdEnd - (Acmd *)sAudioMgr.cmdBuffers[sAudioCmdBufferIndex]) * sizeof(Acmd);
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
    sAudioCmdBufferIndex ^= 1;
    return 1;
}

void audioCheckAiLength(AudioTask *unused) {
    static s32 sAiIdleFlag = 1;
    if (((osAiGetLength() >> 2) == 0) && (sAiIdleFlag == 0)) {
        sAiIdleFlag = 0; // ORIG: the target stores 0 back after reading 0 (sw zero,552(at) at 0x720); without the store the whole test folds away and the function shrinks by 0x20
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
    node = sAudioDmaState.firstUsed;
    while (node != NULL) {
        end = node->startAddr + 0x800;
        if (addr < node->startAddr) {
            break;
        }
        if ((s32)addr + len <= end) {
            node->lastFrame = sAudioFrameCount;
            dmaBuf = (u8 *)node->ptr + (addr - node->startAddr);
            return osVirtualToPhysical(dmaBuf);
        }
        last = node;
        node = node->next;
    }

    node = sAudioDmaState.firstFree;
    if (node == NULL) {
        return osVirtualToPhysical(sAudioDmaState.firstUsed);
    }

    sAudioDmaState.firstFree = node->next;
    alUnlink((ALLink *)node);
    if (last != NULL) {
        alLink((ALLink *)node, (ALLink *)last);
    } else if (sAudioDmaState.firstUsed != NULL) {
        last = sAudioDmaState.firstUsed;
        sAudioDmaState.firstUsed = node;
        node->next = last;
        node->prev = NULL;
        last->prev = node;
    } else {
        sAudioDmaState.firstUsed = node;
        node->next = NULL;
        node->prev = NULL;
    }

    delta = addr & 1;
    addr -= delta;
    node->startAddr = addr;
    node->lastFrame = sAudioFrameCount;
    dmaBuf = node->ptr;
    osPiStartDma(&sAudioDmaIoMsgs[sAudioDmaCount++], OS_MESG_PRI_HIGH, OS_READ, addr, dmaBuf, 0x800, &sAudioDmaMsgQ);
    return osVirtualToPhysical(dmaBuf) + delta;
}



void *audioDmaNew(AudioDmaContext **outContext) {
    if (sAudioDmaState.initialized == 0) {
        sAudioDmaState.firstUsed = NULL;
        sAudioDmaState.firstFree = &sAudioDmaBuffers[0];
        sAudioDmaState.initialized = 1;
    }
    *outContext = &sAudioDmaState;
    return audioDmaCallback;
}


void audioDmaFrameUpdate(void) {
    s32 pad;
    OSMesg msg;
    AudioDmaNode *node;
    AudioDmaNode *next;
    u32 i;

    msg = NULL;
    for (i = 0; i < sAudioDmaCount; i++) {
        osRecvMesg(&sAudioDmaMsgQ, &msg, OS_MESG_NOBLOCK);
    }
    for (node = sAudioDmaState.firstUsed; node != NULL; node = next) {
        next = node->next;
        if ((node->lastFrame + 1) < sAudioFrameCount) {
            if (node == sAudioDmaState.firstUsed) {
                sAudioDmaState.firstUsed = node->next;
            }
            alUnlink((ALLink *)node);
            if (sAudioDmaState.firstFree != NULL) {
                alLink((ALLink *)node, (ALLink *)sAudioDmaState.firstFree);
            } else {
                sAudioDmaState.firstFree = node;
                node->next = NULL;
                node->prev = NULL;
            }
        }
    }
    sAudioDmaCount = 0;
    sAudioFrameCount++;
}
