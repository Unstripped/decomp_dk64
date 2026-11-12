#include "common.h"
#include "proto/global/13E160.h"
#include "proto/global/141C00.h"
#include "proto/global/1435C0.h"

typedef struct SynCoreParam {
    struct SynCoreParam *next;
    s32 delta;
    s16 type;
    s16 padA;
    s32 data;
} SynAllocParam;

// The physical voice behind ALVoice.pvoice (libaudio leaves struct PVoice_s opaque); only its delta is read here.
struct PVoice_s {
    u8 pad0[0x88];
    s32 delta;
};

typedef struct SynAllocSynth {
    u8 pad0[0x1C];
    s32 delta;
} SynAllocSynth;

extern SynAllocSynth *n_syn;

void n_alSynAllocVoicePriorityA(ALVoice *voice, u8 priority) {
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

void n_alSynAllocVoicePriorityB(ALVoice *voice, u8 priority) {
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
