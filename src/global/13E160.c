#include "common.h"

typedef struct SynCoreParam {
    ALLink *next;
    s32 timestamp;
    s16 type;
    s16 pad;
    s32 value;
    s32 delta;
} SynCoreParam;

typedef struct SynCoreAuxBus {
    u8 pad0[0x14];
    s32 count;
    s32 maxPVoices;
    ALLink **pvoices;
    void *effect;
    u8 pad24[0x20];
    void *filter;
} SynCoreAuxBus;
typedef struct SynCorePlayer {
    struct SynCorePlayer *next;
    void *clientData;
    s32 (*handler)(void *);
    s32 padC;
    s32 callTime;
} SynCorePlayer;


typedef struct SynCoreSynth {
    SynCorePlayer *head;
    ALLink pFreeList;
    ALLink pAllocList;
    ALLink pLameList;
    s32 paramSamples;
    s32 curSamples;
    void *dma;
    void *paramPool;
    SynCoreParam *paramFreeList;
    void *mainBus;
    SynCoreAuxBus *auxBuses;
    s32 numPVoices;
    s32 maxAuxBusses;
    s32 outputRate;
    s32 maxOutSamples;
    void *outBuffer;
    s32 unk4C;
} SynCoreSynth;

typedef struct SynCoreConfig {
    s32 maxVVoices;
    s32 maxPVoices;
    s32 maxUpdates;
    s32 maxFXBusses;
    void *dma;
    ALHeap *heap;
    s32 outputRate;
    u8 fxType[4];
} SynCoreConfig;

typedef struct SynCorePVoice {
    u8 data[0xC0];
} SynCorePVoice;

extern SynCoreSynth *D_807563E4;
s32 _n_timeToSamplesNoRound(s32);
s32 __n_nextSampleTime(SynCorePlayer **);
void _n_collectPVoices(void);

#pragma GLOBAL_ASM("asm/global/nonmatchings/13E160/n_alSynNew.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/13E160/n_alAudioFrame.s")

SynCoreParam *__n_allocParam(void) {
    SynCoreParam *param;

    param = NULL;
    if (D_807563E4->paramFreeList != NULL) {
        param = D_807563E4->paramFreeList;
        D_807563E4->paramFreeList = (SynCoreParam *)D_807563E4->paramFreeList->next;
        param->next = NULL;
    }
    return param;
}

void __n_freeParam(SynCoreParam *param) {
    param->next = (ALLink *)D_807563E4->paramFreeList;
    D_807563E4->paramFreeList = param;
}

void _n_collectPVoices(void) {
    ALLink *voice;
    ALLink *current;

    if ((voice = D_807563E4->pLameList.next) != NULL) {
        do {
            current = voice;
            alUnlink(voice);
            alLink(voice, &D_807563E4->pFreeList);
        } while ((voice = D_807563E4->pLameList.next) != NULL);
    }
}

void _n_freePVoice(ALLink *voice) {
    alUnlink(voice);
    alLink(voice, &D_807563E4->pLameList);
}

s32 _n_timeToSamplesNoRound(s32 time) {
    f32 samples;

    samples = (((f32)time * (f32)D_807563E4->outputRate) / 1000000.0f) + 0.5f;
    return (s32)samples;
}

s32 _n_timeToSamples(s32 time) {
    return _n_timeToSamplesNoRound(time) & ~0xF;
}

s32 __n_nextSampleTime(SynCorePlayer **player) {
    s32 unused;
    s32 time;
    SynCorePlayer *current;

    time = 0x7FFFFFFF;
    *player = NULL;
    if ((current = D_807563E4->head) != NULL) {
        do {
            if ((current->callTime - D_807563E4->curSamples) < time) {
                *player = current;
                time = current->callTime - D_807563E4->curSamples;
            }
        } while ((current = current->next) != NULL);
    }
    return (*player)->callTime;
}
