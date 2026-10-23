// func_80601A10 (src/global/6710.c): stage 5, behaviourally equivalent audio driver initialization
#include "common.h"
#include "actor.h"

typedef struct Aud6710_AudioTask {
    void *sampleBuffer;
    s16 sampleCount;
    s16 pad6;
    OSScTask task;
    s16 unk68;
    s16 pad6A;
    struct Aud6710_AudioTask *self;
} Aud6710_AudioTask;

typedef struct Aud6710_AudioCtx {
    u32 unk0[2];
    Aud6710_AudioTask *tasks[3];
} Aud6710_AudioCtx;

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

extern s32 D_8000DCB4;
extern u8 D_807452D0[];
extern Aud6710_AudioCtx D_8076D4D0;
extern OSThread D_8076D4E8;
extern OSMesgQueue D_8076D698;
extern OSMesg D_8076D6B0[];
extern OSMesgQueue D_8076D6D0;
extern OSMesg D_8076D6E8[];
extern ALGlobals D_8076D708;
extern ALLink D_8076FE68[];
extern s32 D_80770194;
extern s32 D_8077019C;
extern s32 D_807701A0;
extern ALGlobals *D_807701A4;
extern OSMesgQueue D_807704A8;
extern OSMesg D_807704C0[];

void func_80601D24(void *);
void *func_806022DC(void *);
void n_alInit(ALGlobals *, void *);

void func_80601A10(Aud6710_InitArg *arg0, s32 arg1, Aud6710_Arg2 *arg2) {
    u8 sp150[0xE0];
    u8 sp44[0x218];
    Aud6710_AudioTask *task;
    ALLink *curr;
    ALLink *prev;
    u32 i;

    arg0->dmaNew = func_806022DC;
    arg0->unk18 = D_8000DCB4;
    D_80770194 = 0x228;
    D_8077019C = 0x398;
    bcopy(&D_807452D0, sp44, sizeof(sp44));
    arg0->synConfig = sp44;
    arg0->unk24 = sp150;
    n_alInit(&D_8076D708, arg0);
    D_807701A4 = &D_8076D708;

    D_8076FE68[0].prev = NULL;
    D_8076FE68[0].next = NULL;

    curr = (ALLink *)((u8 *)&D_8076FE68[0] + 0x14);
    prev = &D_8076FE68[0];
    for (i = 0; i < 39; i++) {
        alLink(curr, prev);
        ((u32 *)prev)[4] = (u32)alHeapDBAlloc(NULL, 0, arg0->heap, 1, 0x800);
        prev = curr;
        curr = (ALLink *)((u8 *)curr + 0x14);
    }
    ((u32 *)prev)[4] = (u32)alHeapDBAlloc(NULL, 0, arg0->heap, 1, 0x800);

    for (i = 0; i < 2; i++) {
        D_8076D4D0.unk0[i] = (u32)alHeapDBAlloc(NULL, 0, arg0->heap, 1, arg2->cmdCount * 8);
    }

    D_807701A0 = arg2->cmdCount;
    for (i = 0; i < 3; i++) {
        task = alHeapDBAlloc(NULL, 0, arg0->heap, 1, sizeof(Aud6710_AudioTask));
        D_8076D4D0.tasks[i] = task;
        task->unk68 = 2;
        task->self = task;
        task->sampleBuffer = alHeapDBAlloc(NULL, 0, arg0->heap, 1, D_8077019C * 4);
    }

    osCreateMesgQueue(&D_8076D6D0, D_8076D6E8, 8);
    osCreateMesgQueue(&D_8076D698, D_8076D6B0, 8);
    osCreateMesgQueue(&D_807704A8, D_807704C0, 0x20);

    osCreateThread(&D_8076D4E8, 4, (void *)func_80601D24, NULL, (void *)&D_8076FE68, arg1);
}
