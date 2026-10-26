#include "common.h"

typedef struct SynAllocParam {
    struct SynAllocParam *next;
    s32 delta;
    s16 type;
    s16 padA;
    s32 data;
} SynAllocParam;

typedef struct SynAllocPVoice {
    u8 pad0[0x88];
    s32 delta;
} SynAllocPVoice;

typedef struct SynAllocVoice {
    u8 pad0[8];
    SynAllocPVoice *pvoice;
} SynAllocVoice;

typedef struct SynAllocSynth {
    u8 pad0[0x1C];
    s32 delta;
} SynAllocSynth;

extern SynAllocSynth *D_807563E4;
extern SynAllocParam *__n_allocParam(void);
extern s32 n_alEnvmixerParam(void *, s32, void *);

void func_8073CF00(SynAllocVoice *voice, u8 arg1) {
    SynAllocParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = D_807563E4->delta + voice->pvoice->delta;
        param->type = 12;
        param->data = arg1;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void func_8073CFB0(SynAllocVoice *voice, u8 arg1) {
    SynAllocParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = D_807563E4->delta + voice->pvoice->delta;
        param->type = 17;
        param->data = arg1;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

typedef struct SynAllocCSeq {
    u8 pad0[4];
    u32 flags;
    u8 pad8[8];
    s32 delta;
    s32 active;
    u8 pad18[0xA0];
    s32 next[16];
} SynAllocCSeq;

s32 func_8073D060(SynAllocCSeq *seq, s32 *ticks) {
    u32 i;
    s32 result = -1;
    s32 delta = seq->delta;

    if (seq->flags == 0) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        if ((seq->flags >> i) & 1) {
            if (seq->active != 0) {
                seq->next[i] -= delta;
            }
            if ((u32)seq->next[i] < (u32)result) {
                result = seq->next[i];
            }
        }
    }
    seq->active = 0;
    *ticks = result;
    return 1;
}
