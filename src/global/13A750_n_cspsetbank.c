#include "common.h"
#include "proto/global/13A750_n_cspsetbank.h"

void alCSPSetBank(ALCSPlayer *seqp, ALBank *b) {
    ALEvent evt;

    evt.type = AL_SEQP_BANK_EVT;
    evt.msg.spbank.bank = b;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
