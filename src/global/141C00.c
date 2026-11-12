#include "common.h"
#include "audio_synth.h"
#include "proto/global/13E160.h"
#include "proto/global/141C00.h"
#include "proto/global/1435C0.h"

extern N_ALSynth *n_syn;

void n_alSynAllocVoicePriorityA(ALVoice *voice, u8 priority) {
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + voice->pvoice->delta;
        param->type = 12;
        param->data.i = priority;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynAllocVoicePriorityB(ALVoice *voice, u8 priority) {
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + voice->pvoice->delta;
        param->type = 17;
        param->data.i = priority;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

s32 __n_alCSeqGetNextDelta(ALCSeq *seq, s32 *ticks) {
    u32 i;
    s32 result = -1;
    s32 delta = seq->lastDeltaTicks;

    if (seq->validTracks == 0) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        if ((seq->validTracks >> i) & 1) {
            if (seq->deltaFlag != 0) {
                seq->evtDeltaTicks[i] -= delta;
            }
            if (seq->evtDeltaTicks[i] < (u32)result) {
                result = seq->evtDeltaTicks[i];
            }
        }
    }
    seq->deltaFlag = 0;
    *ticks = result;
    return 1;
}
