#include "common.h"
#include "proto/global/141E40.h"
#include "audio_synth.h"


void n_alSynDelete(void) {
    n_syn->head = NULL;
}
