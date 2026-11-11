#include "common.h"
#include "proto/global/13E160.h"
#include "proto/global/141AD0.h"
#include "proto/global/1435C0.h"

typedef struct SynAllocStartPVoice {
    u8 pad0[0x88];
    s32 delta;
} SynAllocStartPVoice;

typedef struct SynAllocStartParam {
    struct SynAllocStartParam *next;
    s32 delta;
    s16 type;
    s16 unity;
    f32 pitch;
    s16 volume;
    u8 pan;
    u8 fxmix;
    u8 fxDelay;
    u8 fxPitch;
    f32 fxVolume;
    s32 samples;
    ALWaveTable *wave;
} SynAllocStartParam;

typedef struct SynAllocStartSynth {
    u8 pad0[0x1C];
    s32 delta;
} SynAllocStartSynth;

extern SynAllocStartSynth *n_syn;

void n_alSynStartVoiceParams(ALVoice *voice, ALWaveTable *wave, f32 pitch, s16 volume, u8 pan, u8 fxmix, u8 unity, f32 fxVolume, u8 fxDelay, s32 samples) {
    SynAllocStartParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->delta + ((SynAllocStartPVoice *)voice->pvoice)->delta;
        param->next = NULL;
        param->type = 13;
        param->unity = voice->unityPitch;
        param->pan = pan;
        param->volume = volume;
        param->fxmix = fxmix;
        param->pitch = pitch;
        param->fxDelay = fxDelay;
        param->fxPitch = unity;
        param->fxVolume = fxVolume;
        param->samples = _n_timeToSamples(samples);
        param->wave = wave;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}
