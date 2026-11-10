#include "common.h"
#include "proto/global/137120.h"
#include "proto/global/140600.h"

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

extern SynCoreSynth *n_syn;
s32 _n_timeToSamplesNoRound(s32);
s32 __n_nextSampleTime(SynCorePlayer **);
void _n_collectPVoices(void);
Acmd *n_alFxPull(s32, Acmd *, s32);


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
    n_syn->head = NULL;
    n_syn->numPVoices = config->maxPVoices;
    n_syn->curSamples = 0;
    n_syn->paramSamples = 0;
    n_syn->outputRate = config->outputRate;
    n_syn->maxOutSamples = 0xB8;
    n_syn->dma = config->dma;
    n_syn->outBuffer = NULL;
    n_syn->unk4C = 1;
    if (config->maxFXBusses >= 3) n_syn->maxAuxBusses = 2;
    else if (config->maxFXBusses <= 0) n_syn->maxAuxBusses = 1;
    else n_syn->maxAuxBusses = config->maxFXBusses;
    n_syn->auxBuses = alHeapDBAlloc(NULL, 0, heap, n_syn->maxAuxBusses, 0x48);
    if (n_syn->maxAuxBusses > (i = 0)) do {
        n_syn->auxBuses[i].count = 0;
        n_syn->auxBuses[i].maxPVoices = config->maxPVoices;
        n_syn->auxBuses[i].pvoices = alHeapDBAlloc(NULL, 0, heap, config->maxPVoices, 4);
        if (config->fxType[i] != 0) n_syn->auxBuses[i].effect = n_alSynNewFx(i, config, heap);
        else n_syn->auxBuses[i].effect = NULL;
        n_syn->auxBuses[i].filter = alHeapDBAlloc(NULL, 0, heap, 1, 0x38);
        *(s16 *)((u8 *)n_syn->auxBuses[i].filter + 2) = 0;
        *(void **)((u8 *)n_syn->auxBuses[i].filter + 0x2C) = alHeapDBAlloc(NULL, 0, heap, 1, 8);
        *(void **)((u8 *)n_syn->auxBuses[i].filter + 0x30) = alHeapDBAlloc(NULL, 0, heap, 1, 8);
    } while (++i < n_syn->maxAuxBusses);
    n_syn->mainBus = alHeapDBAlloc(NULL, 0, heap, 1, 0x14);
    *(void **)((u8 *)n_syn->mainBus + 4) = n_alFxPull;
    n_syn->pFreeList.next = NULL;
    n_syn->pFreeList.prev = NULL;
    n_syn->pLameList.next = NULL;
    n_syn->pLameList.prev = NULL;
    n_syn->pAllocList.next = NULL;
    n_syn->pAllocList.prev = NULL;
    pvoices = alHeapDBAlloc(NULL, 0, heap, config->maxPVoices, 0xC0);
    if (config->maxPVoices > (i = 0)) do {
        pvoice = (ALLink *)&pvoices[i];
        alLink(pvoice, &n_syn->pFreeList);
        *(s32 *)((u8 *)pvoice + 8) = 0;
        alN_PVoiceNew(pvoice, n_syn->dma, heap);
        if (n_syn->maxAuxBusses > (j = 0)) do {
            n_syn->auxBuses[j].pvoices[n_syn->auxBuses[j].count] = pvoice, n_syn->auxBuses[j].count++;
        } while (++j < n_syn->maxAuxBusses);
    } while (++i < config->maxPVoices);
    params = alHeapDBAlloc(NULL, 0, heap, config->maxUpdates, 0x24);
    n_syn->paramFreeList = NULL;
    if (config->maxUpdates > (i = 0)) do {
        param = &params[i];
        param->next = (ALLink *)n_syn->paramFreeList;
        n_syn->paramFreeList = param;
    } while (++i < config->maxUpdates);
    n_syn->paramPool = heap;
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
    if (n_syn->head == NULL) {
        *cmdLen = 0;
        return cmdList;
    }
    if ((n_syn->paramSamples = __n_nextSampleTime(&player), (n_syn->paramSamples - n_syn->curSamples) < outLen)) {
        do {
            n_syn->paramSamples &= ~0xF;
            player->callTime += _n_timeToSamplesNoRound(player->handler(player));
        } while ((n_syn->paramSamples = __n_nextSampleTime(&player), (n_syn->paramSamples - n_syn->curSamples) < outLen));
    }
    n_syn->paramSamples &= ~0xF;
    if (outLen > 0) {
        do {
            samples = n_syn->maxOutSamples < outLen ? n_syn->maxOutSamples : outLen;
            original = output;
            n_syn->outBuffer = (void *)buffer;
            output = n_alSynOutputPull(n_syn->curSamples, original);
            outLen -= samples;
            buffer += samples * sizeof(s16) * 2;
            n_syn->curSamples += samples;
        } while (outLen > 0);
    }
    *cmdLen = (output - cmdList) >> 3;
    _n_collectPVoices();
    return output;
}

SynCoreParam *__n_allocParam(void) {
    SynCoreParam *param;

    param = NULL;
    if (n_syn->paramFreeList != NULL) {
        param = n_syn->paramFreeList;
        n_syn->paramFreeList = (SynCoreParam *)n_syn->paramFreeList->next;
        param->next = NULL;
    }
    return param;
}

void __n_freeParam(SynCoreParam *param) {
    param->next = (ALLink *)n_syn->paramFreeList;
    n_syn->paramFreeList = param;
}

void _n_collectPVoices(void) {
    ALLink *voice;
    ALLink *current;

    if ((voice = n_syn->pLameList.next) != NULL) {
        do {
            current = voice;
            alUnlink(voice);
            alLink(voice, &n_syn->pFreeList);
        } while ((voice = n_syn->pLameList.next) != NULL);
    }
}

void _n_freePVoice(ALLink *voice) {
    alUnlink(voice);
    alLink(voice, &n_syn->pLameList);
}

s32 _n_timeToSamplesNoRound(s32 time) {
    f32 samples;

    samples = (((f32)time * (f32)n_syn->outputRate) / 1000000.0f) + 0.5f;
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
    if ((current = n_syn->head) != NULL) {
        do {
            if ((current->callTime - n_syn->curSamples) < time) {
                *player = current;
                time = current->callTime - n_syn->curSamples;
            }
        } while ((current = current->next) != NULL);
    }
    return (*player)->callTime;
}
