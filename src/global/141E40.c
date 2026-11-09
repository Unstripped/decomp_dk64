#include "common.h"
#include "proto/global/141E40.h"

extern s32 *n_syn;

void n_alSynDelete(void) {
    *n_syn = 0;
}
