#include "common.h"
#include "audio_config.h"
#include "proto/global/140600.h"
#include "proto/global/141E60.h"

typedef struct SynAllocFx {
    u8 pad0[0x24];
    void *result;
    u8 pad28[0x20];
} SynAllocFx;

typedef struct SynAllocSynthFx {
    u8 pad0[0x34];
    SynAllocFx *fx;
} SynAllocSynthFx;

extern SynAllocSynthFx *n_syn;

void *n_alSynNewFx(s16 fxId, void *config, void *heap) {
    n_alFxNew(&n_syn->fx[fxId].result, config, fxId, heap);
    return n_syn->fx[fxId].result;
}
