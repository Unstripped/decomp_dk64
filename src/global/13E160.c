#include "common.h"

typedef struct SynCoreParam {
    ALLink *next;
    s32 timestamp;
    s16 type;
    s16 pad;
    s32 value;
    s32 delta;
    u8 pad14[0x10];
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
void n_alFxPull(void);


void n_alSynNew(SynCoreConfig *config) {
    s32 i;
    s32 j;
    s32 padI;
    ALLink *pvoice;
    s32 padPVoice;
    SynCorePVoice *pvoices;
    ALHeap *heap;
    s32 padParams;
    SynCoreParam *params;
    SynCoreParam *param;

    heap = config->heap;
    D_807563E4->head = NULL;
    D_807563E4->numPVoices = config->maxPVoices;
    D_807563E4->curSamples = 0;
    D_807563E4->paramSamples = 0;
    D_807563E4->outputRate = config->outputRate;
    D_807563E4->maxOutSamples = 0xB8;
    D_807563E4->dma = config->dma;
    D_807563E4->outBuffer = NULL;
    D_807563E4->unk4C = 1;
    if (config->maxFXBusses >= 3) D_807563E4->maxAuxBusses = 2;
    else if (config->maxFXBusses <= 0) D_807563E4->maxAuxBusses = 1;
    else D_807563E4->maxAuxBusses = config->maxFXBusses;
    D_807563E4->auxBuses = alHeapDBAlloc(NULL, 0, heap, D_807563E4->maxAuxBusses, 0x48);
    if (D_807563E4->maxAuxBusses > (i = 0)) do {
        D_807563E4->auxBuses[i].count = 0;
        D_807563E4->auxBuses[i].maxPVoices = config->maxPVoices;
        D_807563E4->auxBuses[i].pvoices = alHeapDBAlloc(NULL, 0, heap, config->maxPVoices, 4);
        if (config->fxType[i] != 0) D_807563E4->auxBuses[i].effect = func_8073D160(i, config, heap);
        else D_807563E4->auxBuses[i].effect = NULL;
        D_807563E4->auxBuses[i].filter = alHeapDBAlloc(NULL, 0, heap, 1, 0x38);
        *(s16 *)((u8 *)D_807563E4->auxBuses[i].filter + 2) = 0;
        *(void **)((u8 *)D_807563E4->auxBuses[i].filter + 0x2C) = alHeapDBAlloc(NULL, 0, heap, 1, 8);
        *(void **)((u8 *)D_807563E4->auxBuses[i].filter + 0x30) = alHeapDBAlloc(NULL, 0, heap, 1, 8);
    } while (++i < D_807563E4->maxAuxBusses);
    D_807563E4->mainBus = alHeapDBAlloc(NULL, 0, heap, 1, 0x14);
    *(void **)((u8 *)D_807563E4->mainBus + 4) = n_alFxPull;
    D_807563E4->pFreeList.next = NULL;
    D_807563E4->pFreeList.prev = NULL;
    D_807563E4->pLameList.next = NULL;
    D_807563E4->pLameList.prev = NULL;
    D_807563E4->pAllocList.next = NULL;
    D_807563E4->pAllocList.prev = NULL;
    pvoices = alHeapDBAlloc(NULL, 0, heap, config->maxPVoices, 0xC0);
    if (config->maxPVoices > (i = 0)) do {
        pvoice = (ALLink *)&pvoices[i];
        alLink(pvoice, &D_807563E4->pFreeList);
        *(s32 *)((u8 *)pvoice + 8) = 0;
        alN_PVoiceNew(pvoice, D_807563E4->dma, heap);
        if (D_807563E4->maxAuxBusses > (j = 0)) do {
            D_807563E4->auxBuses[j].pvoices[D_807563E4->auxBuses[j].count] = pvoice, D_807563E4->auxBuses[j].count++;
        } while (++j < D_807563E4->maxAuxBusses);
    } while (++i < config->maxPVoices);
    params = alHeapDBAlloc(NULL, 0, heap, config->maxUpdates, 0x24);
    D_807563E4->paramFreeList = NULL;
    if (config->maxUpdates > (i = 0)) do {
        param = &params[i];
        param->next = (ALLink *)D_807563E4->paramFreeList;
        D_807563E4->paramFreeList = param;
    } while (++i < config->maxUpdates);
    D_807563E4->paramPool = heap;
}

s32 n_alAudioFrame(s32 cmdList, s32 *cmdLen, s32 outBuf, s32 outLen) {
    SynCorePlayer *player;
    s16 unused;
    s32 output;
    s32 original;
    s32 samples;
    s32 buffer;

    unused = 0;
    output = cmdList;
    buffer = outBuf;
    if (D_807563E4->head == NULL) {
        *cmdLen = 0;
        return cmdList;
    }
    if ((D_807563E4->paramSamples = __n_nextSampleTime(&player), (D_807563E4->paramSamples - D_807563E4->curSamples) < outLen)) {
        do {
            D_807563E4->paramSamples &= ~0xF;
            player->callTime += _n_timeToSamplesNoRound(player->handler(player));
        } while ((D_807563E4->paramSamples = __n_nextSampleTime(&player), (D_807563E4->paramSamples - D_807563E4->curSamples) < outLen));
    }
    D_807563E4->paramSamples &= ~0xF;
    if (outLen > 0) {
        do {
            samples = D_807563E4->maxOutSamples < outLen ? D_807563E4->maxOutSamples : outLen;
            original = output;
            D_807563E4->outBuffer = (void *)buffer;
            output = func_8073E800(D_807563E4->curSamples, original);
            outLen -= samples;
            buffer += samples * sizeof(s16) * 2;
            D_807563E4->curSamples += samples;
        } while (outLen > 0);
    }
    *cmdLen = (output - cmdList) >> 3;
    _n_collectPVoices();
    return output;
}

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
