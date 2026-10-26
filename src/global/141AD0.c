#include "common.h"

typedef struct SynAllocStartPVoice {
    u8 pad0[0x88];
    s32 delta;
} SynAllocStartPVoice;

typedef struct SynAllocStartVoice {
    u8 pad0[8];
    SynAllocStartPVoice *pvoice;
    u8 padC[0xE];
    s16 unity;
} SynAllocStartVoice;

typedef struct SynAllocStartParam {
    struct SynAllocStartParam *next;
    s32 delta;
    s16 type;
    s16 unity;
    f32 pitch;
    s16 volume;
    u8 pan;
    u8 fxmix;
    u8 arg8;
    u8 arg9;
    f32 arg7;
    s32 samples;
    void *wave;
} SynAllocStartParam;

typedef struct SynAllocStartSynth {
    u8 pad0[0x1C];
    s32 delta;
} SynAllocStartSynth;

extern SynAllocStartSynth *n_syn;
extern SynAllocStartParam *__n_allocParam(void);
extern s32 n_alEnvmixerParam(void *, s32, void *);
extern s32 _n_timeToSamples(s32);

void n_alSynStartVoiceParams(SynAllocStartVoice *voice, void *wave, f32 pitch, s16 volume, u8 pan, u8 fxmix, u8 unity, f32 arg7, u8 arg8, s32 samples) {
    SynAllocStartParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->delta + voice->pvoice->delta;
        param->next = NULL;
        param->type = 13;
        param->unity = voice->unity;
        param->pan = pan;
        param->volume = volume;
        param->fxmix = fxmix;
        param->pitch = pitch;
        param->arg8 = arg8;
        param->arg9 = unity;
        param->arg7 = arg7;
        param->samples = _n_timeToSamples(samples);
        param->wave = wave;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}
