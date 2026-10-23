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

extern OSThread D_8076D4E8;
extern AudioContext D_8076D4D0;
extern s32 D_8000DCB4;
extern AudioSynthesizerConfig D_807452D0;
extern OSMesgQueue D_8076D698;
extern OSMesg D_8076D6B0[8];
extern OSMesgQueue D_8076D6D0;
extern OSMesg D_8076D6E8[8];
extern s32 D_8076D708;
extern AudioDmaNode D_8076FE68[];
extern s32 D_80770194;
extern s32 D_8077019C;
extern s32 D_807701A0;
extern s32 *D_807701A4;
extern OSMesgQueue D_807704A8;
extern OSMesg D_807704C0[32];

void *audioDmaNew();
void n_alInit(s32 *, AudioInitArgs *);
void audioThreadMain();
#ifdef NON_MATCHING
void func_80601A10(AudioInitArgs *arg0, s32 arg1, AudioTaskConfig *arg2) {
    AudioDmaNode *curr;
    AudioSynthesizerConfig sp44;
    AudioDmaNode *prev;
    u32 i;

    arg0->dmaNew = audioDmaNew;
    arg0->unk18 = D_8000DCB4;
    D_80770194 = 0x228;
    D_8077019C = 0x398;
    sp44 = D_807452D0;
    arg0->synConfig = &sp44;
    arg0->unk24 = (u8 *)&sp44 + 0x10C;
    n_alInit(&D_8076D708, arg0);
    D_807701A4 = &D_8076D708;

    D_8076FE68[0].prev = NULL;
    D_8076FE68[0].next = NULL;

    curr = &D_8076FE68[1];
    prev = &D_8076FE68[0];
    for (i = 0; (i ^ 0) < 39; i++, prev++, curr++) {
        alLink((ALLink *)curr, (ALLink *)prev);
        prev->unk10 = alHeapDBAlloc(NULL, 0, arg0->heap, 1, 0x800);
    }
    prev->unk10 = alHeapDBAlloc(NULL, 0, arg0->heap, 1, 0x800);

    for (curr = (AudioDmaNode *)D_8076D4D0.cmdBuffers; curr < (AudioDmaNode *)D_8076D4D0.tasks; ) {
        *(void **)curr = alHeapDBAlloc(NULL, 0, arg0->heap, 1, arg2->cmdCount * 8);
        curr = (AudioDmaNode *)((u8 *)curr + 4);
    }

    D_807701A0 = arg2->cmdCount;
    for (curr = (AudioDmaNode *)D_8076D4D0.cmdBuffers; curr < (AudioDmaNode *)&D_8076D4D0.tasks[1]; ) {
        AudioTask *task = alHeapDBAlloc(NULL, 0, arg0->heap, 1, sizeof(AudioTask));
        *(AudioTask **)((u8 *)curr + 8) = task;
        task->msgBuf = 2;
        task->self = task;
        task->sampleBuffer = alHeapDBAlloc(NULL, 0, arg0->heap, 1, D_8077019C * 4);
        curr = (AudioDmaNode *)((u8 *)curr + 4);
    }
    osCreateMesgQueue(&D_8076D6D0, D_8076D6E8, 8);
    osCreateMesgQueue(&D_8076D698, D_8076D6B0, 8);
    osCreateMesgQueue(&D_807704A8, D_807704C0, 0x20);

    osCreateThread(&D_8076D4E8, 4, audioThreadMain, NULL, D_8076FE68, arg1);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6710/func_80601A10.s")
#endif

extern s8 D_807452CC;

void audioThreadStart(void) {
    D_807452CC = 1;
    osStartThread(&D_8076D4E8);
}

void audioThreadStop(s32 arg0) {
    if (D_807452CC != 0) {
        osStopThread(&D_8076D4E8);
    }
}

typedef struct AudioSched {
    OSMesgQueue interruptQ;
    u8 pad[0x264 - sizeof(OSMesgQueue)];
    void *audioListHead;
} AudioSched;

extern u8 D_8076D4C0;
extern AudioSched gScheduler;
extern u32 D_807452C0;
s32 audioDmaCallback();

void schedAddClient(void *, void *, OSMesgQueue *, s32, s32);
s32 func_80601EE4();
void audioCheckAiLength();
void seqUpdateVolumeFades(void);
void n_alClose(void *);
void audioThreadMain(s32 arg0) {
    s32 done;
    OSMesg sp58;
    s32 first;
    void *var_s0;
    s32 numBuffers;
    done = 0;
    var_s0 = NULL;
    first = 1;
    schedAddClient(&gScheduler, &D_8076D4C0, &D_8076D698, 2, 2);
    osSendMesg(&D_8076D698, (OSMesg)5, 0);
    numBuffers = 3;
    do {
        osRecvMesg(&D_8076D698, &sp58, 1);
        switch ((s32)sp58) {
        case 5:
            if (gScheduler.audioListHead != NULL) {
                osSendMesg(&gScheduler.interruptQ, (OSMesg)0x29E, 1);
            }
            func_80601EE4(D_8076D4D0.tasks[D_807452C0 % numBuffers], var_s0);
            arg0 = first != 0;
            first = 0;
            var_s0 = D_8076D4D0.tasks[(D_807452C0 + 1) % numBuffers];
            if (!arg0) {
                osRecvMesg(&D_8076D6D0, &sp58, 1);
                audioCheckAiLength(var_s0);
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
extern s32 D_807452C8;
extern s32 D_80770558[];
extern u32 func_80741310[];
extern u64 D_80760590[];

void audioDmaFrameUpdate(void);
s32 n_alAudioFrame(void *, s32 *, u32, s16);
OSMesgQueue *func_8060EE58(void *);

#ifdef NON_MATCHING
s32 func_80601EE4(AudioTask *task, AudioAiBuffer *aiBuf) {
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
        count = 2;
        D_80770558[zero] = count;
    } else {
        count = D_80770558[zero];
        if (((s32)aiLen >= 0x115) && (count == 0)) {
            task->sampleCount = D_80770194;
            count = 2;
            D_80770558[zero] = count;
        } else {
            task->sampleCount = 0x2E0;
            if (count != 0) {
                D_80770558[zero] = count - 1;
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
    osSendMesg(func_8060EE58(&gScheduler), &task->next, OS_MESG_NOBLOCK);
    D_807452C8 ^= 1;
    return 1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/6710/func_80601EE4.s")
#endif

extern s32 D_807454E8[];

void audioCheckAiLength(s32 arg0) {
    s32 zero = 0;
    if (((osAiGetLength() >> 2) == 0) && (D_807454E8[zero] == 0)) {
        D_807454E8[zero] = 0;
    }
}


typedef struct AudioDmaContext {
    u8 unk0;
    u8 pad1[3];
    AudioDmaNode *unk4;
    AudioDmaNode *unk8;
} AudioDmaContext;

extern AudioDmaContext D_80770188;
extern OSIoMesg D_807701A8[];
extern u32 D_807452C4;

s32 audioDmaCallback(u32 addr, s32 len, void *state) {
    void *sp44;
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
    sp44 = node->unk10;
    osPiStartDma(&D_807701A8[D_807452C4++], 1, 0, addr, sp44, 0x800, &D_807704A8);
    return osVirtualToPhysical(sp44) + head;
}



void *audioDmaNew(AudioDmaContext **arg0) {
    if (D_80770188.unk0 == 0) {
        D_80770188.unk4 = 0;
        D_80770188.unk8 = &D_8076FE68[0];
        D_80770188.unk0 = 1;
    }
    *arg0 = &D_80770188;
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
