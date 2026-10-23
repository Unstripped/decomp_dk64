// func_80601EE4 (src/global/6710.c): stage 5, frame 0x38 vs 0x40, task struct field stores
#include "common.h"
#include "actor.h"

typedef struct Aud6710_AiBuf {
    void *buf;
    s16 len;
} Aud6710_AiBuf;

typedef struct Aud6710_AudioTask {
    void *sampleBuffer;
    s16 sampleCount;
    s16 pad6;
    struct Aud6710_AudioTask *next;
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
} Aud6710_AudioTask;

typedef struct Aud6710_AudioCtx {
    void *cmdBuffers[2];
    void *tasks[3];
} Aud6710_AudioCtx;

extern Aud6710_AudioCtx D_8076D4D0;
extern u32 D_805FB000[];
extern u32 D_805FB0D0[];
extern s32 D_807452C8;
extern u8 D_8076D4C0;
extern OSMesgQueue D_8076D6D0;
extern s32 D_80770194;
extern s32 D_8077019C;
extern s32 D_80770558;
extern u32 func_80741310[];
extern u64 D_80760590[];
extern u8 gScheduler[];

void func_80602314(void);
s32 n_alAudioFrame(void *, s32 *, u32, s16);
OSMesgQueue *func_8060EE58(void *);

s32 func_80601EE4(Aud6710_AudioTask *task, Aud6710_AiBuf *aiBuf) {
    u32 physSampleBuf;
    s32 cmdCount;
    u32 aiLen;
    s32 cmdLen;

    physSampleBuf = osVirtualToPhysical(task->sampleBuffer);
    func_80602314();
    aiLen = IO_READ(AI_LEN_REG) >> 2;
    if (aiBuf != NULL) {
        osAiSetNextBuffer(aiBuf->buf, aiBuf->len * 4);
    }
    if ((s32)aiLen < 0x5C) {
        if (D_80770558 == 0) {
            task->sampleCount = D_8077019C;
            D_80770558 = 2;
            goto done_sample;
        }
    }
    if ((s32)aiLen >= 0x115) {
        if (D_80770558 == 0) {
            task->sampleCount = D_80770194;
            D_80770558 = 2;
            goto done_sample;
        }
    }
    task->sampleCount = 0x2E0;
    if (D_80770558 != 0) {
        D_80770558--;
    }
done_sample:

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
    task->task.t.type = 2;
    task->task.t.ucode_boot = (u64 *)&D_805FB000;
    task->task.t.ucode_boot_size = (u8 *)&D_805FB0D0 - (u8 *)&D_805FB000;
    task->task.t.flags = 0;
    task->task.t.ucode = (u64 *)&func_80741310;
    task->task.t.ucode_data = (u64 *)&D_80760590;
    task->task.t.ucode_data_size = 0x800;
    task->task.t.yield_data_size = 0x400;
    task->task.t.data_size = ((cmdLen - (s32)D_8076D4D0.cmdBuffers[D_807452C8]) >> 3) << 3;
    task->task.t.yield_data_ptr = NULL;

    osWritebackDCacheAll();
    osSendMesg(func_8060EE58(&gScheduler), &task->next, OS_MESG_NOBLOCK);
    D_807452C8 ^= 1;
    return 1;
}
