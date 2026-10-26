#include "common.h"

s32 alCSPGetTempo(ALCSPlayer *seqp) {
    if (seqp->target == NULL) {
        return NULL;
    }
    return (s32)((f32)seqp->uspt / seqp->target->qnpt);
}
