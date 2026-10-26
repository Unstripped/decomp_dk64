#include "common.h"

typedef struct {
    u8 pad0[0xD];
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 pad11[0x23];
} CspApiChanState;

typedef struct {
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

void func_80737E90(CspApiCSPlayer *seqp, s32 arg1) {
    seqp->unk84 = arg1;
}

void func_80737EA4(ALCSPlayer *seqp, s32 arg1, s32 arg2) {
    ALInstrument *inst;

    arg1 &= 0xFF;
    arg2 &= 0xFF;
    if (arg1 < seqp->bank->instCount) {
        inst = seqp->bank->instArray[arg1];
        if (inst != NULL) {
            inst->flags = (arg2 * 2) | (inst->flags & 1);
        }
    }
}

void func_80737F0C(CspApiCSPlayer *seqp, s32 arg1, s32 arg2) {
    arg2 &= 0xFF;
    seqp->chanState[arg1].unk10 = arg2;
}

void func_80737F40(CspApiCSPlayer *seqp) {
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

void func_80737FD8(ALCSPlayer *seqp, s32 chan) {
    alCSPSendMidi(seqp, 0, chan | AL_MIDI_ControlChange, 0xFF, 0);
}

void func_8073801C(ALCSPlayer *seqp, s32 chan) {
    seqp->chanMask |= 1 << chan;
    alCSPSendMidi(seqp, 0, chan | AL_MIDI_ControlChange, 0xFF, 0xFF);
}

void func_80738080(ALCSPlayer *seqp, s32 chan, u8 value) {
    alCSPSendMidi(seqp, 0, chan | AL_MIDI_ControlChange, 0xFF, (u8)(s32)value);
}

void func_807380CC(ALCSPlayer *seqp, s32 chan, u8 value) {
    alCSPSendMidi(seqp, 0, chan | AL_MIDI_ControlChange, 0x41, (u8)(s32)value);
}

void func_80738118(ALCSPlayer *seqp, s32 chan, u8 value) {
    alCSPSendMidi(seqp, 0, chan | AL_MIDI_ControlChange, AL_MIDI_Stop, (u8)(s32)value);
}
