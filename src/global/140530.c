#include "common.h"
#include "audio_synth.h"
#include "proto/global/13E160.h"
#include "proto/global/140530.h"
#include "proto/global/1435C0.h"

extern N_ALSynth *n_syn;

void n_alSynSetVol(ALVoice *voice, s16 volume, s32 delta) {
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + voice->pvoice->delta;
        param->type = 0xB;
        param->data.i = volume;
        param->moredata.i = _n_timeToSamples(delta);
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}
