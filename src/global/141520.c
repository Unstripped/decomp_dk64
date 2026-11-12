#include "common.h"
#include "audio_synth.h"
#include "proto/global/13E160.h"
#include "proto/global/140600.h"
#include "proto/global/141520.h"
#include "proto/global/141EF0.h"
#include "proto/global/1435C0.h"

extern N_ALSynth *n_syn;

void n_alSynSetVoiceUnkC(ALVoice *voice, u8 val) {
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + voice->pvoice->delta;
        param->type = 0x10;
        param->data.i = val;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void *n_alSynGetFXDelay(s16 busIndex) {
    N_ALMainBus *mainBus;

    mainBus = n_syn->mainBus;
    if (mainBus->handler == n_alFxPull) {
        return n_syn->auxBus[busIndex].fx;
    } else {
        return NULL;
    }
}

SynLPFilter *n_alSynGetFXFeedback(s16 busIndex) {
    N_ALMainBus *mainBus;

    mainBus = n_syn->mainBus;
    if (mainBus->handler == n_alFxPull) {
        return n_syn->auxBus[busIndex].filter;
    } else {
        return NULL;
    }
}

void n_alSynSetFXParam(void *fxType, s16 paramId, void *paramVal) {
    struct FxParamState *fx = fxType;

    n_alFxParamHdl(fx, paramId, paramVal);
}

void n_alSynSetFXFilterParam(SynLPFilter *filter, s16 paramId, void *valuePtr) {
    if (paramId == 8) {
        filter->lp.fgain = (s16)(s32)((f32)*(s32 *)valuePtr * 0.1f);
    } else if (paramId == 9) {
        filter->lp.fc = (s16)*(s32 *)valuePtr;
    }
    rebuildLowPassCoefficients(&filter->lp, (f32)n_syn->outputRate);
}
