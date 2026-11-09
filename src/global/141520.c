#include "common.h"

typedef struct {
    u8 unk0[4];
    void *handler;
} SynFilter;

typedef struct {
    u8 unk0[0x20];
    s32 field20;
    u8 unk24[0x20];
    s32 field44;
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

typedef struct SynVoiceParam {
    struct SynVoiceParam *next;
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

typedef struct SynFXFilter {
    s16 unk0;
    s16 unk2;
} SynFXFilter;

extern SynSynth *n_syn;
SynVoiceParam *__n_allocParam(void);
s32 n_alEnvmixerParam(void *, s32, SynVoiceParam *);
void n_alFxPull(void);
void n_alFxParamHdl(s32, s16, s32);
void rebuildLowPassCoefficients(SynFXFilter *, f32);

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

s32 n_alSynGetFXDelay(s16 busIndex) {
    SynFilter *sp4;

    sp4 = n_syn->outputFilter;
    if (sp4->handler == n_alFxPull) {
        return n_syn->fxBus[busIndex].field20;
    } else {
        return 0;
    }
}

s32 n_alSynGetFXFeedback(s16 busIndex) {
    SynFilter *sp4;

    sp4 = n_syn->outputFilter;
    if (sp4->handler == n_alFxPull) {
        return n_syn->fxBus[busIndex].field44;
    } else {
        return 0;
    }
}

void n_alSynSetFXParam(s32 fxType, s16 paramId, s32 paramVal) {
    s32 fxParam;

    fxParam = fxType;
    n_alFxParamHdl(fxParam, paramId, paramVal);
}

void n_alSynSetFXFilterParam(SynFXFilter *filter, s16 paramId, s32 *valuePtr) {
    if (paramId == 8) {
        filter->unk2 = (s16)(s32)((f32)*valuePtr * 0.1f);
    } else if (paramId == 9) {
        filter->unk0 = (s16)*valuePtr;
    }
    rebuildLowPassCoefficients(filter, (f32)n_syn->outputRate);
}
