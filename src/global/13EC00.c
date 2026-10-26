#include "common.h"

void alSeqpStop(ALSeqPlayer *seqp) {
    ALEvent evt;

    evt.type = AL_SEQP_STOPPING_EVT;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

void alSeqpSetSeq(ALSeqPlayer *seqp, ALSeq *seq) {
    ALEvent evt;

    evt.type = AL_SEQP_SEQ_EVT;
    evt.msg.spseq.seq = seq;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
