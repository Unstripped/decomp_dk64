#include "common.h"
#include "proto/global/13D0B0.h"

s32 alCSPGetTempo(ALCSPlayer *seqp) {
    if (seqp->target == NULL) {
        return 0;
    }
    return (s32)(seqp->uspt / seqp->target->qnpt);
}
