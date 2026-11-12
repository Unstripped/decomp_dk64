#include "common.h"
#include "audio_config.h"
#include "audio_synth.h"
#include "proto/global/137120.h"
#include "proto/global/140600.h"
#include "proto/global/141E60.h"
#include "proto/global/141EF0.h"

extern N_ALSynth *n_syn;
s32 _n_timeToSamplesNoRound(s32);
s32 __n_nextSampleTime(ALPlayer **);
void _n_collectPVoices(void);


void n_alSynNew(AudioInitArgs *config) {
    s32 i;
    s32 j;
    s32 padI;
    N_PVoice *pvoice;
    s32 padPVoice;
    N_PVoice *pvoices;
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
    n_syn->dma = config->dmaNew;
    n_syn->outBuffer = NULL;
    n_syn->unk4C = 1;
    if (config->maxFXbusses >= 3) {
        n_syn->maxAuxBusses = 2;
    } else if (config->maxFXbusses <= 0) {
        n_syn->maxAuxBusses = 1;
    } else {
        n_syn->maxAuxBusses = config->maxFXbusses;
    }
    n_syn->auxBus = alHeapDBAlloc(NULL, 0, heap, n_syn->maxAuxBusses, sizeof(N_ALAuxBus));
    for (i = 0; i < n_syn->maxAuxBusses; i++) {
        n_syn->auxBus[i].sourceCount = 0;
        n_syn->auxBus[i].maxSources = config->maxPVoices;
        n_syn->auxBus[i].sources = alHeapDBAlloc(NULL, 0, heap, config->maxPVoices, sizeof(N_PVoice *));
        if (config->fxType[i] != 0) {
            n_syn->auxBus[i].fx = n_alSynNewFx(i, config, heap);
        } else {
            n_syn->auxBus[i].fx = NULL;
        }
        n_syn->auxBus[i].filter = alHeapDBAlloc(NULL, 0, heap, 1, sizeof(SynLPFilter));
        n_syn->auxBus[i].filter->lp.fgain = 0;
        n_syn->auxBus[i].filter->lp.fstate = alHeapDBAlloc(NULL, 0, heap, 1, 8);
        n_syn->auxBus[i].filter->unk30 = alHeapDBAlloc(NULL, 0, heap, 1, 8);
    }
    n_syn->mainBus = alHeapDBAlloc(NULL, 0, heap, 1, sizeof(N_ALMainBus));
    n_syn->mainBus->handler = n_alFxPull;
    n_syn->pFreeList.next = NULL;
    n_syn->pFreeList.prev = NULL;
    n_syn->pLameList.next = NULL;
    n_syn->pLameList.prev = NULL;
    n_syn->pAllocList.next = NULL;
    n_syn->pAllocList.prev = NULL;
    pvoices = alHeapDBAlloc(NULL, 0, heap, config->maxPVoices, sizeof(N_PVoice));
    for (i = 0; i < config->maxPVoices; i++) {
        pvoice = &pvoices[i];
        alLink(&pvoice->node, &n_syn->pFreeList);
        pvoice->vvoice = NULL;
        alN_PVoiceNew(pvoice, n_syn->dma, heap);
        for (j = 0; j < n_syn->maxAuxBusses; j++) {
            n_syn->auxBus[j].sources[n_syn->auxBus[j].sourceCount++] = pvoice;
        }
    }
    params = alHeapDBAlloc(NULL, 0, heap, config->maxUpdates, sizeof(SynCoreParam));
    n_syn->paramList = NULL;
    for (i = 0; i < config->maxUpdates; i++) {
        param = &params[i];
        param->next = n_syn->paramList;
        n_syn->paramList = param;
    }
    n_syn->heap = heap;
}

Acmd *n_alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen) {
    ALPlayer *player;
    s16 unused;
    Acmd *output;
    Acmd *original;
    s32 samples;
    s16 *buffer;

    unused = 0;
    output = cmdList;
    buffer = outBuf;
    if (n_syn->head == NULL) {
        *cmdLen = 0;
        return cmdList;
    }
    while (n_syn->paramSamples = __n_nextSampleTime(&player), (n_syn->paramSamples - n_syn->curSamples) < outLen) {
        n_syn->paramSamples &= ~0xF;
        player->samplesLeft += _n_timeToSamplesNoRound(player->handler(player));
    }
    n_syn->paramSamples &= ~0xF;
    while (outLen > 0) {
        samples = n_syn->maxOutSamples < outLen ? n_syn->maxOutSamples : outLen;
        original = output;
        n_syn->outBuffer = buffer;
        output = n_alSynOutputPull(n_syn->curSamples, original);
        outLen -= samples;
        buffer += samples * 2;
        n_syn->curSamples += samples;
    }
    *cmdLen = output - cmdList;
    _n_collectPVoices();
    return output;
}

SynCoreParam *__n_allocParam(void) {
    SynCoreParam *param;

    param = NULL;
    if (n_syn->paramList != NULL) {
        param = n_syn->paramList;
        n_syn->paramList = n_syn->paramList->next;
        param->next = NULL;
    }
    return param;
}

void __n_freeParam(SynCoreParam *param) {
    param->next = n_syn->paramList;
    n_syn->paramList = param;
}

void _n_collectPVoices(void) {
    ALLink *voice;
    N_PVoice *pvoice;

    while ((voice = n_syn->pLameList.next) != NULL) {
        pvoice = (N_PVoice *)voice;
        alUnlink(voice);
        alLink(voice, &n_syn->pFreeList);
    }
}

void _n_freePVoice(N_PVoice *pvoice) {
    alUnlink(&pvoice->node);
    alLink(&pvoice->node, &n_syn->pLameList);
}

s32 _n_timeToSamplesNoRound(s32 time) {
    f32 samples;

    samples = (((f32)time * (f32)n_syn->outputRate) / 1000000.0f) + 0.5f;
    return (s32)samples;
}

s32 _n_timeToSamples(s32 time) {
    return _n_timeToSamplesNoRound(time) & ~0xF;
}

s32 __n_nextSampleTime(ALPlayer **player) {
    s32 pad;
    s32 time;
    ALPlayer *current;

    time = 0x7FFFFFFF;
    *player = NULL;
    for (current = n_syn->head; current != NULL; current = current->next) {
        if ((current->samplesLeft - n_syn->curSamples) < time) {
            *player = current;
            time = current->samplesLeft - n_syn->curSamples;
        }
    }
    return (*player)->samplesLeft;
}
