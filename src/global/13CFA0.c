#include "common.h"
#include "proto/global/13CFA0.h"
#include "proto/global/13FED0.h"

void alCSPSendMidi(ALCSPlayer *seqp, s32 ticks, u8 status, u8 byte1, u8 byte2) {
    ALEvent evt;
    s32 delta;

    evt.type = AL_SEQP_MIDI_EVT;
    evt.msg.midi.ticks = 0;
    evt.msg.midi.status = status;
    evt.msg.midi.byte1 = byte1;
    evt.msg.midi.byte2 = byte2;
    evt.msg.midi.duration = 0;
    delta = ticks;
    alEvtqPostEvent(&seqp->evtq, &evt, delta);
}
