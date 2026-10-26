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

typedef struct {
    s16 unk0;
    s16 unk2;
} SynFXFilter;

extern SynSynth *D_807563E4;
SynVoiceParam *__n_allocParam(void);
s32 n_alEnvmixerParam(void *, s32, SynVoiceParam *);
void n_alFxPull(void);
void n_alFxParamHdl(s32, s16, s32);
void func_8073BE54(SynFXFilter *, f32);

void func_8073C820(ALVoice *voice, u8 arg1) {
    SynVoiceParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = D_807563E4->paramSamples + ((SynPVoice *)voice->pvoice)->delta;
        param->type = 0x10;
        param->data.i = arg1;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

s32 func_8073C8D0(s16 arg0) {
    SynFilter *sp4;

    sp4 = D_807563E4->outputFilter;
    if (sp4->handler == n_alFxPull) {
        return D_807563E4->fxBus[arg0].field20;
    } else {
        return 0;
    }
}

s32 func_8073C948(s16 arg0) {
    SynFilter *sp4;

    sp4 = D_807563E4->outputFilter;
    if (sp4->handler == n_alFxPull) {
        return D_807563E4->fxBus[arg0].field44;
    } else {
        return 0;
    }
}

void func_8073C9C0(s32 arg0, s16 arg1, s32 arg2) {
    s32 sp1C;

    sp1C = arg0;
    n_alFxParamHdl(sp1C, arg1, arg2);
}

void func_8073CA04(SynFXFilter *arg0, s16 arg1, s32 *arg2) {
    if (arg1 == 8) {
        arg0->unk2 = (s16)(s32)((f32)*arg2 * 0.1f);
    } else if (arg1 == 9) {
        arg0->unk0 = (s16)*arg2;
    }
    func_8073BE54(arg0, (f32)D_807563E4->outputRate);
}
