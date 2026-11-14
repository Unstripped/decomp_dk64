#include "common.h"
#include "proto/global/13D100.h"
#include "seqplayer.h"

void alCSPSetFXParam(ALCSPlayer *seqp, u8 busIndex, u8 paramId, u8 delayIndex, s32 paramValue) {
    N_Event evt;

    evt.type = AL_VIB_OSC_EVT + 2;
    evt.msg.cmd.b0 = busIndex;
    evt.msg.cmd.b1 = paramId;
    evt.msg.cmd.b2 = delayIndex;
    evt.msg.cmd.w4 = paramValue;
    alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, 0);
}
