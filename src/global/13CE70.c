#define alCSPSetChlPan alCSPSetChlPan_unused
#include "common.h"
#undef alCSPSetChlPan

void alCSPSetChlVol(ALCSPlayer *seqp, u8 chan, u8 vol) {
    ALEvent evt;

    evt.type = AL_SEQP_MIDI_EVT;
    evt.msg.midi.ticks = 0;
    evt.msg.midi.status = chan | AL_MIDI_ControlChange;
    evt.msg.midi.byte1 = AL_MIDI_FX1_CTRL;
    evt.msg.midi.byte2 = vol;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

void alCSPSetChlPan(ALCSPlayer *seqp, f32 pan, f32 volume) {
    s32 unused;
    struct {
        s16 type;
        s16 pad;
        f32 pan;
        f32 volume;
    } evt;

    evt.type = AL_VIB_OSC_EVT + 1;
    evt.pan = pan;
    evt.volume = volume;
    alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, 0);
}

void alCSPSetChlFXMix(ALCSPlayer *seqp, u8 chan, u8 fxmix) {
    ALEvent evt;

    evt.type = AL_SEQP_MIDI_EVT;
    evt.msg.midi.ticks = 0;
    evt.msg.midi.status = chan | AL_MIDI_ControlChange;
    evt.msg.midi.byte1 = AL_MIDI_FX1_CTRL + 1;
    evt.msg.midi.byte2 = fxmix;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
