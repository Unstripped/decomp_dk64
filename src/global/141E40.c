#include "common.h"

extern s32 *n_syn;

void n_alSynDelete(void) {
    *n_syn = 0;
}
