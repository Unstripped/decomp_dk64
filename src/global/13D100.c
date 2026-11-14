#include "common.h"
#include "proto/global/13D100.h"
#include "seqplayer.h"

void alCSPSetFXParam(ALCSPlayer *seqp, u8 busIndex, u8 paramId, u8 delayIndex, s32 paramValue) {
    N_Event evt;

    evt.type = AL_VIB_OSC_EVT + 2;
    evt.msg.cmd.busIndex = busIndex;
    evt.msg.cmd.paramId = paramId;
    evt.msg.cmd.delayIndex = delayIndex;
    evt.msg.cmd.value = paramValue;
    alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, 0);
}
