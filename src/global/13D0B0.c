#define alCSPGetSeq alCSPGetSeq_unused
#include "common.h"
#undef alCSPGetSeq

ALCSeq *alCSPGetSeq(ALCSPlayer *seqp) {
    if (seqp->target == NULL) {
        return NULL;
    }
    return (ALCSeq *)(s32)((f32)seqp->uspt / seqp->target->qnpt);
}
