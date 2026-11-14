#include "common.h"
#include "audio_synth.h"
#include "audio_config.h"
#include "proto/global/140600.h"
#include "proto/global/141E60.h"

void *n_alSynNewFx(s16 fxId, AudioInitArgs *config, ALHeap *heap) {
    n_alFxNew(&n_syn->auxBus[fxId].newFx, config, fxId, heap);
    return n_syn->auxBus[fxId].newFx;
}
