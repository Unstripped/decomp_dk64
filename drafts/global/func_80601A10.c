// func_80601A10 (src/global/6710.c): stage 5, struct copy matched, frame 0x268 vs 0x260 and loop regalloc
#include "common.h"
#include "actor.h"

typedef struct Aud6710_DmaNode {
    struct Aud6710_DmaNode *next;
    struct Aud6710_DmaNode *prev;
    u32 unk8;
    u32 unkC;
    void *unk10;
} Aud6710_DmaNode;

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

typedef struct Aud6710_Config218 {
    u32 words[0x218 / 4];
} Aud6710_Config218;

typedef struct Aud6710_InitArg {
    u8 pad0[0x10];
    void *dmaNew;
    ALHeap *heap;
    s32 unk18;
    u8 pad1C[4];
    void *synConfig;
    void *unk24;
} Aud6710_InitArg;

typedef struct Aud6710_Arg2 {
    u8 pad0[8];
    u32 cmdCount;
} Aud6710_Arg2;

extern OSThread D_8076D4E8;
extern Aud6710_AudioCtx D_8076D4D0;
extern s32 D_8000DCB4;
extern Aud6710_Config218 D_807452D0;
extern OSMesgQueue D_8076D698;
extern OSMesg D_8076D6B0[8];
extern OSMesgQueue D_8076D6D0;
extern OSMesg D_8076D6E8[8];
extern s32 D_8076D708;
extern Aud6710_DmaNode D_8076FE68[];
extern s32 D_80770194;
extern s32 D_8077019C;
extern s32 D_807701A0;
extern s32 *D_807701A4;
extern OSMesgQueue D_807704A8;
extern OSMesg D_807704C0[32];

void *func_806022DC();
void n_alInit();
void func_80601D24();

void func_80601A10(Aud6710_InitArg *arg0, s32 arg1, Aud6710_Arg2 *arg2) {
    Aud6710_Config218 sp44;
    Aud6710_DmaNode *curr;
    Aud6710_DmaNode *prev;
    s32 i;

    arg0->dmaNew = func_806022DC;
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
    for (i = 0; i < 39; i++, prev++, curr++) {
        alLink((ALLink *)curr, (ALLink *)prev);
        prev->unk10 = alHeapDBAlloc(NULL, 0, arg0->heap, 1, 0x800);
    }
    prev->unk10 = alHeapDBAlloc(NULL, 0, arg0->heap, 1, 0x800);

    for (curr = (Aud6710_DmaNode *)D_8076D4D0.cmdBuffers; curr < (Aud6710_DmaNode *)D_8076D4D0.tasks; ) {
        *(void **)curr = alHeapDBAlloc(NULL, 0, arg0->heap, 1, arg2->cmdCount * 8);
        curr = (Aud6710_DmaNode *)((u8 *)curr + 4);
    }

    D_807701A0 = arg2->cmdCount;
    for (curr = (Aud6710_DmaNode *)D_8076D4D0.cmdBuffers; curr < (Aud6710_DmaNode *)&D_8076D4D0.tasks[1]; ) {
        Aud6710_AudioTask *task = alHeapDBAlloc(NULL, 0, arg0->heap, 1, sizeof(Aud6710_AudioTask));
        *(Aud6710_AudioTask **)((u8 *)curr + 8) = task;
        task->msgBuf = 2;
        task->self = task;
        task->sampleBuffer = alHeapDBAlloc(NULL, 0, arg0->heap, 1, D_8077019C * 4);
        curr = (Aud6710_DmaNode *)((u8 *)curr + 4);
    }

    osCreateMesgQueue(&D_8076D6D0, D_8076D6E8, 8);
    osCreateMesgQueue(&D_8076D698, D_8076D6B0, 8);
    osCreateMesgQueue(&D_807704A8, D_807704C0, 0x20);

    osCreateThread(&D_8076D4E8, 4, func_80601D24, NULL, D_8076FE68, arg1);
}
