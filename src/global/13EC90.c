#include "common.h"
#include "proto/global/13EC90.h"
#include "proto/global/13FED0.h"

void alSeqpSetVol(ALSeqPlayer *seqp, s16 vol) {
    ALEvent evt;

    evt.type = AL_SEQP_VOL_EVT;
    evt.msg.spvol.vol = vol;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
