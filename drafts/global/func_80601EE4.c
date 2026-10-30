// func_80601EE4 (src/global/6710.c): stage 5-6: frame and all stores match; AI_LEN_REG lui 0xa450 vs symbol is reloc only; only diff: li v0,2 (x2) vs mine addiu v0,v0,2 via FAKE count += 2 (plain count = 2 is const-propagated to a scratch-ring li and shifts t-regs by 2). Need a form that keeps 'count = 2' as a non-propagated v0 web.
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
        count += 2; // FAKE: count is 0 here; keeps the 2 in $v0 instead of a scratch li
        D_80770558[zero] = count;
    } else {
        count = D_80770558[zero];
        if (((s32)aiLen >= 0x115) && (count == 0)) {
            task->sampleCount = D_80770194;
            count += 2; // FAKE: count is 0 here; keeps the 2 in $v0 instead of a scratch li
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
    osSendMesg(func_8060EE58(&gScheduler), &task->next, OS_MESG_NOBLOCK);
    D_807452C8 ^= 1;
    return 1;
}
