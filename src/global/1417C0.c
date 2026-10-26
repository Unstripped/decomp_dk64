#include "common.h"

typedef struct SynAllocVoiceNode SynAllocVoiceNode;

typedef struct SynAllocVoice {
    u8 pad0[8];
    SynAllocVoiceNode *pvoice;
    void *clientPrivate;
    u8 pad10[4];
    s16 state;
    s16 priority;
    s16 fxBus;
    s16 unity;
} SynAllocVoice;

typedef struct SynAllocVoiceConfig {
    s16 priority;
    s16 fxBus;
    u8 unity;
} SynAllocVoiceConfig;

struct SynAllocVoiceNode {
    SynAllocVoiceNode *next;
    u8 pad4[4];
    SynAllocVoice *voice;
    u8 padC[0x7C];
    s32 delta;
};

typedef struct SynAllocParam {
    struct SynAllocParam *next;
    s32 delta;
    s16 type;
    s16 padA;
    s32 data;
    s32 moredata;
} SynAllocParam;

typedef struct SynAllocSynth {
    u8 pad0[4];
    SynAllocVoiceNode *list4;
    u8 pad8[4];
    SynAllocVoiceNode *listC;
    u8 pad10[4];
    SynAllocVoiceNode *list14;
    u8 pad18[4];
    s32 delta;
} SynAllocSynth;

extern SynAllocSynth *D_807563E4;
s32 func_8073CC94(SynAllocVoiceNode **, s16);
extern SynAllocParam *__n_allocParam(void);
extern s32 n_alEnvmixerParam(void *, s32, void *);

s32 n_alSynAllocVoice(SynAllocVoice *voice, SynAllocVoiceConfig *config) {
    SynAllocVoiceNode *pvoice = NULL;
    s32 unused;
    SynAllocParam *param;
    s32 allocated;
    voice->priority = config->priority;
    voice->unity = config->unity;
    voice->clientPrivate = NULL;
    voice->fxBus = config->fxBus;
    voice->state = 0;
    voice->pvoice = NULL;
    allocated = func_8073CC94(&pvoice, config->priority);
    if (pvoice != NULL) {
        if (allocated != 0) {
            pvoice->delta = 0x228;
            pvoice->voice->pvoice = NULL;
            pvoice->voice = voice;
            voice->pvoice = pvoice;
            param = __n_allocParam();
            if (param != NULL) {
                param->delta = D_807563E4->delta;
                param->type = 11;
                param->data = 0;
                param->moredata = 0x170;
                n_alEnvmixerParam(voice->pvoice, 3, param);
            } else {
            }
            param = __n_allocParam();
            if (param != NULL) {
                param->delta = D_807563E4->delta + pvoice->delta;
                param->type = 15;
                param->next = NULL;
                n_alEnvmixerParam(voice->pvoice, 3, param);
            } else {
            }
        } else {
            pvoice->delta = 0;
            pvoice->voice = voice;
            voice->pvoice = pvoice;
        }
    }
    return pvoice != NULL;
}

s32 func_8073CC94(SynAllocVoiceNode **out, s16 priority) {
    SynAllocVoiceNode *pvoice;
    SynAllocVoiceNode *candidate;
    s32 allocated = 0;

    if ((pvoice = D_807563E4->list14) != NULL) {
        *out = pvoice;
        alUnlink((ALLink *)pvoice);
        alLink((ALLink *)pvoice, (ALLink *)((u8 *)D_807563E4 + 0xC));
    } else if ((pvoice = D_807563E4->list4) != NULL) {
        *out = pvoice;
        alUnlink((ALLink *)pvoice);
        alLink((ALLink *)pvoice, (ALLink *)((u8 *)D_807563E4 + 0xC));
    } else if ((pvoice = D_807563E4->listC) != NULL) {
        do {
            candidate = pvoice;
            if ((candidate->voice->priority <= priority) && (candidate->delta == 0)) {
                *out = candidate;
                priority = candidate->voice->priority;
                allocated = 1;
            }
        } while ((pvoice = pvoice->next) != NULL);
    }
    return allocated;
}
