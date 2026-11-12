#include "common.h"
#include "proto/global/13E160.h"
#include "proto/global/140600.h"
#include "proto/global/141520.h"
#include "proto/global/141EF0.h"
#include "proto/global/1435C0.h"

typedef struct {
    u8 unk0[4];
    void *handler;
} SynFilter;

typedef struct {
    u8 unk0[0x20];
    void *field20;
    u8 unk24[0x20];
    struct SynLPFilter *field44;
} SynFXBus;

typedef struct {
    u8 unk0[0x1C];
    s32 paramSamples;
    u8 unk20[0x10];
    SynFilter *outputFilter;
    SynFXBus *fxBus;
    u8 unk38[8];
    s32 outputRate;
} SynSynth;

typedef struct SynCoreParam {
    struct SynCoreParam *next;
    s32 delta;
    s16 type;
    union {
        f32 f;
        s32 i;
    } data;
} SynVoiceParam;

typedef struct {
    u8 unk0[0x88];
    s32 delta;
} SynPVoice;

// Leading fields of the low-pass filter defined in 140600.c.
typedef struct SynLPFilter {
    s16 unk0;
    s16 unk2;
} SynLPFilter;

extern SynSynth *n_syn;

void n_alSynSetVoiceUnkC(ALVoice *voice, u8 val) {
    SynVoiceParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + ((SynPVoice *)voice->pvoice)->delta;
        param->type = 0x10;
        param->data.i = val;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void *n_alSynGetFXDelay(s16 busIndex) {
    SynFilter *outputFilter;

    outputFilter = n_syn->outputFilter;
    if (outputFilter->handler == n_alFxPull) {
        return n_syn->fxBus[busIndex].field20;
    } else {
        return NULL;
    }
}

SynLPFilter *n_alSynGetFXFeedback(s16 busIndex) {
    SynFilter *outputFilter;

    outputFilter = n_syn->outputFilter;
    if (outputFilter->handler == n_alFxPull) {
        return n_syn->fxBus[busIndex].field44;
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
        filter->unk2 = (s16)(s32)((f32)*(s32 *)valuePtr * 0.1f);
    } else if (paramId == 9) {
        filter->unk0 = (s16)*(s32 *)valuePtr;
    }
    rebuildLowPassCoefficients(filter, (f32)n_syn->outputRate);
}
