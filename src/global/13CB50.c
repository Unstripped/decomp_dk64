#include "common.h"

typedef struct {
    u8 pad0[0xD];
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 pad11[0x23];
} CspApiChanState;

typedef struct CspApiCSPlayer {
    u8 pad0[0x30];
    u16 chanMask;
    u8 pad32[2];
    u8 maxChannels;
    u8 pad35[0x13];
    ALEventQueue evtq;
    u8 pad5C[4];
    CspApiChanState *chanState;
    u8 pad64[0x20];
    s32 unk84;
} CspApiCSPlayer;

void alCSPPlay(ALCSPlayer *seqp) {
    ALEvent evt;

    evt.type = AL_SEQP_PLAY_EVT;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

void alCSPSetUnk84(CspApiCSPlayer *seqp, s32 val) {
    seqp->unk84 = val;
}

void setCSPInstrumentFlags(ALCSPlayer *seqp, s32 instIndex, s32 flags) {
    ALInstrument *inst;

    instIndex &= 0xFF;
    flags &= 0xFF;
    if (instIndex < seqp->bank->instCount) {
        inst = seqp->bank->instArray[instIndex];
        if (inst != NULL) {
            inst->flags = (flags * 2) | (inst->flags & 1);
        }
    }
}

void setCSPChannelStateValue(CspApiCSPlayer *seqp, s32 chan, s32 value) {
    value &= 0xFF;
    seqp->chanState[chan].unk10 = value;
}

void resetCSPChannelStates(CspApiCSPlayer *seqp) {
    s32 i;

    seqp->chanMask = 0xFFFF;
    i = 0;
    if (seqp->maxChannels > 0) {
        do {
            seqp->chanState[i].unkE = 0xFF;
            seqp->chanState[i].unkD = 0xFF;
        } while ((i += 1) < seqp->maxChannels);
    }
}

void alCSPChannelResetControl(ALCSPlayer *seqp, s32 chan) {
    alCSPSendMidi(seqp, 0, chan | AL_MIDI_ControlChange, 0xFF, 0);
}

void enableCSPChannel(ALCSPlayer *seqp, s32 chan) {
    seqp->chanMask |= 1 << chan;
    alCSPSendMidi(seqp, 0, chan | AL_MIDI_ControlChange, 0xFF, 0xFF);
}

void alCSPChannelSetControl(ALCSPlayer *seqp, s32 chan, u8 value) {
    alCSPSendMidi(seqp, 0, chan | AL_MIDI_ControlChange, 0xFF, (u8)(s32)value);
}

void setCSPChannelPortamento(ALCSPlayer *seqp, s32 chan, u8 value) {
    alCSPSendMidi(seqp, 0, chan | AL_MIDI_ControlChange, 0x41, (u8)(s32)value);
}

void setCSPChannelStopControl(ALCSPlayer *seqp, s32 chan, u8 value) {
    alCSPSendMidi(seqp, 0, chan | AL_MIDI_ControlChange, AL_MIDI_Stop, (u8)(s32)value);
}
