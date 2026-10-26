#include "common.h"

typedef struct SynCoreParam {
    ALLink *next;
    s32 timestamp;
    s16 type;
    s16 pad;
    s32 value;
    s32 delta;
} SynCoreParam;

typedef struct SynCoreSynth {
    ALPlayer *head;
    ALLink pFreeList;
    ALLink pAllocList;
    ALLink pLameList;
    s32 paramSamples;
    s32 curSamples;
    void *dma;
    void *paramPool;
    SynCoreParam *paramFreeList;
    void *mainBus;
    void *auxBuses;
    s32 numPVoices;
    s32 maxAuxBusses;
    s32 outputRate;
    s32 maxOutSamples;
    void *outBuffer;
    s32 unk4C;
} SynCoreSynth;

typedef struct SynCorePVoice {
    u8 pad0[0x88];
    s32 envOffset;
} SynCorePVoice;

extern SynCoreSynth *n_syn;
SynCoreParam *__n_allocParam(void);
s32 _n_timeToSamples(s32);
void n_alEnvmixerParam(void *, s32, SynCoreParam *);

void n_alSynSetVol(ALVoice *voice, s16 volume, s32 delta) {
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->timestamp = n_syn->paramSamples + ((SynCorePVoice *)voice->pvoice)->envOffset;
        param->type = 0xB;
        param->value = volume;
        param->delta = _n_timeToSamples(delta);
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}
