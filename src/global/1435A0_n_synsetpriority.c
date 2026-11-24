#include "common.h"
#include "proto/global/1435A0_n_synsetpriority.h"

void n_alSynSetPriority(ALVoice *voice, s16 priority) {
    voice->priority = priority;
}
