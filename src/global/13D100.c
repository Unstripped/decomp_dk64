#include "common.h"
#include "proto/global/13D100.h"

void postCSPChannelCommand(ALCSPlayer *seqp, u8 chan, u8 priority, u8 value, s32 command) {
    s32 unused;
    struct {
        s16 type;
        u16 unused2;
        u8 chan;
        u8 priority;
        u8 value;
        u8 pad;
        s32 command;
    } evt;

    evt.type = AL_VIB_OSC_EVT + 2;
    evt.chan = chan;
    evt.priority = priority;
    evt.value = value;
    evt.command = command;
    alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, 0);
}
