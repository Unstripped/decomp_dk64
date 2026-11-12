#include "common.h"
#include "audio_synth.h"
#include "proto/global/13E160.h"
#include "proto/global/141AD0.h"
#include "proto/global/1435C0.h"

extern N_ALSynth *n_syn;

void n_alSynStartVoiceParams(ALVoice *voice, ALWaveTable *wave, f32 pitch, s16 volume, u8 pan, u8 fxmix, u8 unity, f32 fxVolume, u8 fxDelay, s32 samples) {
    SynStartParam *param;

    if (voice->pvoice != NULL) {
        param = (SynStartParam *)__n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + ((N_PVoice *)voice->pvoice)->delta;
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
