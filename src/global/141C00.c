#include "common.h"
#include "proto/global/13E160.h"
#include "proto/global/141C00.h"
#include "proto/global/1435C0.h"

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

extern SynAllocSynth *n_syn;

void n_alSynAllocVoicePriorityA(SynAllocVoice *voice, u8 priority) {
    SynAllocParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->delta + voice->pvoice->delta;
        param->type = 12;
        param->data = priority;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynAllocVoicePriorityB(SynAllocVoice *voice, u8 priority) {
    SynAllocParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->delta + voice->pvoice->delta;
        param->type = 17;
        param->data = priority;
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

s32 __n_alCSeqGetNextDelta(SynAllocCSeq *seq, s32 *ticks) {
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
