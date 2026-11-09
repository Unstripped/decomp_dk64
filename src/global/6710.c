#include "common.h"
#include "actor.h"

typedef struct AudioDmaNode {
    struct AudioDmaNode *next;
    struct AudioDmaNode *prev;
    u32 unk8;
    u32 unkC;
    void *unk10;
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
    void *tasks[3];
} AudioContext;

typedef struct AudioSynthesizerConfig {
    u32 words[0x218 / 4];
} AudioSynthesizerConfig;

typedef struct AudioInitArgs {
    u8 pad0[0x10];
    void *dmaNew;
    ALHeap *heap;
    s32 unk18;
    u8 pad1C[4];
    void *synConfig;
    void *unk24;
} AudioInitArgs;

typedef struct AudioTaskConfig {
    u8 pad0[8];
    u32 cmdCount;
} AudioTaskConfig;

typedef struct AudioAlState {
    s32 words[0x2760 / 4];
} AudioAlState;

typedef struct AudioDmaContext {
    u8 unk0;
    u8 pad1[3];
    AudioDmaNode *unk4;
    AudioDmaNode *unk8;
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
u8 D_8076D4C0[0x10];
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
s32 *D_807701A4;
OSIoMesg D_807701A8[32];
OSMesgQueue D_807704A8;
OSMesg D_807704C0[32];
u8 D_80770540[0x18];
s32 D_80770558[2];

void *audioDmaNew(AudioDmaContext **outContext);
void n_alInit(s32 *, AudioInitArgs *);
void audioThreadMain();
#include "common.h"
#include "actor.h"


void audioThreadInit(AudioInitArgs *initArgs, s32 threadPriority, AudioTaskConfig *taskConfig) {
    AudioDmaNode *curr;
    AudioSynthesizerConfig synConfig;
    u32 i;

    initArgs->dmaNew = audioDmaNew;
    initArgs->unk18 = sAudioFreq;
    D_80770194 = 0x228;
    D_8077019C = 0x398;
    synConfig = D_807452D0;
    initArgs->synConfig = &synConfig;
    initArgs->unk24 = (u8 *)&synConfig + 0x10C;
    n_alInit((s32 *)&D_8076D708, initArgs);
    D_807701A4 = (s32 *)&D_8076D708;

    D_8076FE68[0].prev = NULL;
    D_8076FE68[0].next = NULL;

    for (i = 0; (i ^ 0) < 39; i++) { // FAKE: x ^ 0 keeps i from being strength-reduced away (steers LFTR)
        if (taskConfig != 0) {} // FAKE: dead use of taskConfig swaps $s4/$s5 and the i/prev register order
        alLink((ALLink *)&D_8076FE68[i + 1], (ALLink *)&D_8076FE68[i]);
        D_8076FE68[i].unk10 = alHeapDBAlloc(NULL, 0, initArgs->heap, 1, 0x800);
    }
    D_8076FE68[i].unk10 = alHeapDBAlloc(NULL, 0, initArgs->heap, 1, 0x800);

    for (curr = (AudioDmaNode *)D_8076D4D0.cmdBuffers; curr < (AudioDmaNode *)D_8076D4D0.tasks; ) {
        *(void **)curr = alHeapDBAlloc(NULL, 0, initArgs->heap, 1, taskConfig->cmdCount * 8);
        curr = (AudioDmaNode *)((u8 *)curr + 4);
    }

    D_807701A0 = taskConfig->cmdCount;
    for (i = 0; i < 3; i++) {
        ((AudioTask **)&D_8076D4D0)[i + 2] = alHeapDBAlloc(NULL, 0, initArgs->heap, 1, sizeof(AudioTask));
        ((AudioTask **)&D_8076D4D0)[i + 2]->msgBuf = 2;
        ((AudioTask **)&D_8076D4D0)[i + 2]->self = ((AudioTask **)&D_8076D4D0)[i + 2];
        ((AudioTask **)&D_8076D4D0)[i + 2]->sampleBuffer = alHeapDBAlloc(NULL, 0, initArgs->heap, 1, D_8077019C * 4);
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

typedef struct AudioSched {
    OSMesgQueue interruptQ;
    u8 pad[0x264 - sizeof(OSMesgQueue)];
    void *audioListHead;
} AudioSched;

extern AudioSched gScheduler;
s32 audioDmaCallback();

void schedAddClient(void *, void *, OSMesgQueue *, s32, s32);
s32 audioBuildTask();
void audioCheckAiLength(s32 unused);
void seqUpdateVolumeFades(void);
void n_alClose(void *);
void audioThreadMain(s32 isFirstFrame) {
    s32 done;
    OSMesg receivedMsg;
    s32 first;
    void *prevAiTask;
    s32 numBuffers;
    done = 0;
    prevAiTask = NULL;
    first = 1;
    schedAddClient(&gScheduler, &D_8076D4C0, &D_8076D698, 2, 2);
    osSendMesg(&D_8076D698, (OSMesg)5, 0);
    numBuffers = 3;
    do {
        osRecvMesg(&D_8076D698, &receivedMsg, 1);
        switch ((s32)receivedMsg) {
        case 5:
            if (gScheduler.audioListHead != NULL) {
                osSendMesg(&gScheduler.interruptQ, (OSMesg)0x29E, 1);
            }
            audioBuildTask(D_8076D4D0.tasks[D_807452C0 % numBuffers], prevAiTask);
            isFirstFrame = first != 0;
            first = 0;
            prevAiTask = D_8076D4D0.tasks[(D_807452C0 + 1) % numBuffers];
            if (!isFirstFrame) {
                osRecvMesg(&D_8076D6D0, &receivedMsg, 1);
                audioCheckAiLength(prevAiTask);
            }
            seqUpdateVolumeFades();
            break;
        case 10:
            done = 1;
            break;
        }
    } while (!done);
    n_alClose(&D_8076D708);
}

typedef struct AudioAiBuffer {
    void *buf;
    s16 len;
} AudioAiBuffer;


extern u32 D_805FB000[];
extern u32 D_805FB0D0[];
extern u32 func_80741310[];
extern u64 D_80760590[];

void audioDmaFrameUpdate(void);
s32 n_alAudioFrame(s32, s32 *, s32, s32);
OSMesgQueue *schedGetCmdQueue(void *);

s32 audioBuildTask(AudioTask *task, AudioAiBuffer *aiBuf) {
    u32 physSampleBuf;
    s32 pad[1];
    s32 cmdCount;
    u32 aiLen;
    s32 cmdLen;
    s32 count;
    s32 zero = 0;

    physSampleBuf = osVirtualToPhysical(task->sampleBuffer);
    audioDmaFrameUpdate();
    aiLen = IO_READ(AI_LEN_REG) >> 2;
    if (aiBuf != NULL) {
        osAiSetNextBuffer(aiBuf->buf, aiBuf->len * 4);
    }
    if (((s32)aiLen < 0x5C) && ((count = D_80770558[zero]) == 0)) {
        task->sampleCount = D_8077019C;
        count = (count & 0) + 2; // FAKE: folds to 2 after const-prop; keeps li in count's register ($v0) instead of a scratch li
        D_80770558[zero] = count;
    } else {
        count = D_80770558[zero];
        if (((s32)aiLen >= 0x115) && (count == 0)) {
            task->sampleCount = D_80770194;
            count = (count & 0) + 2; // FAKE: folds to 2 after const-prop; keeps li in count's register ($v0) instead of a scratch li
            D_80770558[zero] = count;
        } else {
            task->sampleCount = 0x2E0;
            if (count != 0) {
                count--;
                D_80770558[zero] = count;
            }
        }
    }

    cmdLen = n_alAudioFrame(D_8076D4D0.cmdBuffers[D_807452C8], &cmdCount, physSampleBuf, task->sampleCount);
    if (cmdCount == 0) {
        return 0;
    }

    task->next = NULL;
    task->msgQ = &D_8076D6D0;
    task->msg = (OSMesg)&task->msgBuf;
    task->flags = 1;
    task->client = &D_8076D4C0;
    task->task.t.data_ptr = (u64 *)D_8076D4D0.cmdBuffers[D_807452C8];
    task->task.t.data_size = ((cmdLen - (s32)D_8076D4D0.cmdBuffers[D_807452C8]) >> 3) << 3;
    task->task.t.type = 2;
    task->task.t.ucode_boot = (u64 *)&D_805FB000;
    task->task.t.ucode_boot_size = (u8 *)&D_805FB0D0 - (u8 *)&D_805FB000;
    task->task.t.flags = 0;
    task->task.t.ucode = (u64 *)&func_80741310;
    task->task.t.ucode_data = (u64 *)&D_80760590;
    task->task.t.ucode_data_size = 0x800;
    task->task.t.yield_data_ptr = NULL;
    task->task.t.yield_data_size = 0x400;

    osWritebackDCacheAll();
    osSendMesg(schedGetCmdQueue(&gScheduler), &task->next, OS_MESG_NOBLOCK);
    D_807452C8 ^= 1;
    return 1;
}

void audioCheckAiLength(s32 unused) {
    s32 zero = 0;
    if (((osAiGetLength() >> 2) == 0) && (D_807454E8[zero] == 0)) {
        D_807454E8[zero] = 0;
    }
}


s32 audioDmaCallback(u32 addr, s32 len, void *state) {
    void *dmaBuf;
    s32 pad[3];
    AudioDmaNode *node;
    AudioDmaNode *last;
    s32 head;
    s32 end;
    last = NULL;
    head = (s32)D_80770188.unk4;
    node = (AudioDmaNode *)head;
    if (head != 0) {
        do {
            end = node->unk8 + 0x800;
            if (addr < node->unk8) {
                break;
            }
            if (end >= (s32)addr + len) {
                last = node;
                node->unkC = D_807452C0;
                return osVirtualToPhysical((u8 *)node->unk10 + (addr - node->unk8));
            }
            last = node;
            node = node->next;
        } while (node != NULL);
    }

    node = D_80770188.unk8;
    if (node == NULL) {
        return osVirtualToPhysical((void *)head);
    }

    D_80770188.unk8 = node->next;
    alUnlink((ALLink *)node);
    if (last != NULL) {
        alLink((ALLink *)node, (ALLink *)last);
    } else {
        head = (s32)D_80770188.unk4;
        if (head != 0) {
            D_80770188.unk4 = node;
            node->next = (AudioDmaNode *)head;
            node->prev = NULL;
            ((AudioDmaNode *)head)->prev = node;
        } else {
            D_80770188.unk4 = node;
            node->next = NULL;
            node->prev = NULL;
        }
    }

    head = addr & 1;
    addr -= head;
    node->unk8 = addr;
    node->unkC = D_807452C0;
    dmaBuf = node->unk10;
    osPiStartDma(&D_807701A8[D_807452C4++], 1, 0, addr, dmaBuf, 0x800, &D_807704A8);
    return osVirtualToPhysical(dmaBuf) + head;
}



void *audioDmaNew(AudioDmaContext **outContext) {
    if (D_80770188.unk0 == 0) {
        D_80770188.unk4 = 0;
        D_80770188.unk8 = &D_8076FE68[0];
        D_80770188.unk0 = 1;
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
    i = 0;
    if (D_807452C4 != 0) {
        do {
            osRecvMesg(&D_807704A8, &msg, 0);
            i++;
        } while (i < D_807452C4);
    }
    for (node = D_80770188.unk4; node != NULL; node = next) {
        next = node->next;
        if ((node->unkC + 1) < D_807452C0) {
            if (node == D_80770188.unk4) {
                D_80770188.unk4 = node->next;
            }
            alUnlink((ALLink *)node);
            if (D_80770188.unk8 != NULL) {
                alLink((ALLink *)node, (ALLink *)D_80770188.unk8);
            } else {
                D_80770188.unk8 = node;
                node->next = NULL;
                node->prev = NULL;
            }
        }
    }
    D_807452C4 = 0;
    D_807452C0++;
}
