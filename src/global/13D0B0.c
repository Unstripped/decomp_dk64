#include "common.h"
#include "proto/global/13D0B0.h"

s32 alCSPGetTempo(ALCSPlayer *seqp) {
    if (seqp->target == NULL) {
        return NULL;
    }
    return (s32)((f32)seqp->uspt / seqp->target->qnpt);
}
