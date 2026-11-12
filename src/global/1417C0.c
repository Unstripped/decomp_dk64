#include "common.h"
#include "audio_synth.h"
#include "proto/global/13E0E0.h"
#include "proto/global/13E160.h"
#include "proto/global/1417C0.h"
#include "proto/global/1435C0.h"

extern N_ALSynth *n_syn;

s32 n_alSynAllocVoice(ALVoice *voice, ALVoiceConfig *config) {
    N_PVoice *pvoice = NULL;
    s32 pad;
    SynCoreParam *param;
    s32 allocated;
    voice->priority = config->priority;
    voice->unityPitch = config->unityPitch;
    voice->table = NULL;
    voice->fxBus = config->fxBus;
    voice->state = AL_STOPPED;
    voice->pvoice = NULL;
    allocated = __n_allocPVoice(&pvoice, config->priority);
    if (pvoice != NULL) {
        if (allocated != 0) {
            pvoice->delta = 0x228;
            pvoice->vvoice->pvoice = NULL;
            pvoice->vvoice = voice;
            voice->pvoice = pvoice;
            param = __n_allocParam();
            if (param != NULL) {
                param->delta = n_syn->paramSamples;
                param->type = 11;
                param->data.i = 0;
                param->moredata.i = 0x170;
                n_alEnvmixerParam(voice->pvoice, 3, param);
            } else {
#ifdef _DEBUG
                __osError(ERR_ALSYN_NO_UPDATE, 0);
#endif
            }
            param = __n_allocParam();
            if (param != NULL) {
                param->delta = n_syn->paramSamples + pvoice->delta;
                param->type = 15;
                param->next = NULL;
                n_alEnvmixerParam(voice->pvoice, 3, param);
            } else {
#ifdef _DEBUG
                __osError(ERR_ALSYN_NO_UPDATE, 0);
#endif
            }
        } else {
            pvoice->delta = 0;
            pvoice->vvoice = voice;
            voice->pvoice = pvoice;
        }
    }
    return pvoice != NULL;
}

s32 __n_allocPVoice(N_PVoice **out, s16 priority) {
    N_PVoice *pvoice;
    N_PVoice *candidate;
    s32 allocated = 0;

    if ((pvoice = (N_PVoice *)n_syn->pLameList.next) != NULL) {
        *out = pvoice;
        alUnlink(&pvoice->node);
        alLink(&pvoice->node, &n_syn->pAllocList);
    } else if ((pvoice = (N_PVoice *)n_syn->pFreeList.next) != NULL) {
        *out = pvoice;
        alUnlink(&pvoice->node);
        alLink(&pvoice->node, &n_syn->pAllocList);
    } else if ((pvoice = (N_PVoice *)n_syn->pAllocList.next) != NULL) {
        do {
            candidate = pvoice;
            if ((candidate->vvoice->priority <= priority) && (candidate->delta == 0)) {
                *out = candidate;
                priority = candidate->vvoice->priority;
                allocated = 1;
            }
        } while ((pvoice = (N_PVoice *)pvoice->node.next) != NULL);
    }
    return allocated;
}
