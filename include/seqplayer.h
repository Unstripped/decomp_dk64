#ifndef SEQPLAYER_H
#define SEQPLAYER_H

#include "common.h"

// Rare's compressed-sequence player (n_alCSPlayerNew, 137C10.c and the __n_* voice helpers in 13ECE0.c).
// libaudio.h's ALCSPlayer is the SDK layout; the game's player keeps that field order but its channel
// and voice states are larger, its event carries game messages, and four fields follow stopOsc.

// Per-MIDI-channel state (N_CSPlayer.chanState[maxChannels]); ALChanState plus game fields, 0x34 bytes.
typedef struct N_ChanState {
    /* 0x00 */ ALInstrument *instrument;
    /* 0x04 */ s16 bendRange;
    /* 0x06 */ u8 fxId;
    /* 0x07 */ u8 pan;
    /* 0x08 */ u8 priority;
    /* 0x09 */ u8 vol;
    /* 0x0A */ u8 fxmix;
    /* 0x0B */ u8 unk0B;
    /* 0x0C */ u8 sustain;
    /* 0x0D */ u8 unk0D;
    /* 0x0E */ u8 unk0E;
    /* 0x0F */ u8 unk0F;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ f32 pitchBend;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ s8 unk27;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 pad30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 pad33;
} N_ChanState; // size = 0x34

// Allocated voice (N_CSPlayer.vAllocHead/vAllocTail/vFreeList lists); ALVoiceState plus the two oscillators, 0x40 bytes.
typedef struct N_VoiceState {
    /* 0x00 */ struct N_VoiceState *next;
    /* 0x04 */ ALVoice voice;
    /* 0x20 */ ALSound *sound;
    /* 0x24 */ s32 envEndTime;
    /* 0x28 */ f32 pitch;
    /* 0x2C */ f32 vibrato;
    /* 0x30 */ u8 envGain;
    /* 0x31 */ u8 channel;
    /* 0x32 */ u8 key;
    /* 0x33 */ u8 velocity;
    /* 0x34 */ u8 envPhase;
    /* 0x35 */ u8 phase;
    /* 0x36 */ u8 tremelo;
    /* 0x37 */ u8 flags;
    /* 0x38 */ void *tremOsc;
    /* 0x3C */ void *vibOsc;
} N_VoiceState; // size = 0x40

// Player event (N_CSPlayer.nextEvent): ALEvent plus the game's float-pair and channel-command messages, 0x10 bytes.
typedef struct N_Event {
    /* 0x00 */ u16 type;
    union {
        ALNoteEvent note;
        ALVolumeEvent vol;
        ALSeqpVolEvent spvol;
        ALSeqpPriorityEvent sppriority;
        ALSeqpSeqEvent spseq;
        ALSeqpBankEvent spbank;
        ALOscEvent osc;
        struct {
            f32 f0;
            f32 f1;
        } fpair;
        struct {
            u8 b0;
            u8 b1;
            u8 b2;
            u32 w4;
        } cmd;
    } msg;
} N_Event;

// The sequence player itself (gSeqPlayers[], 0x8C bytes).
typedef struct N_CSPlayer {
    /* 0x00 */ ALPlayer node;
    /* 0x14 */ ALSynth *drvr;
    /* 0x18 */ ALCSeq *target;
    /* 0x1C */ ALMicroTime curTime;
    /* 0x20 */ ALBank *bank;
    /* 0x24 */ s32 uspt;
    /* 0x28 */ s32 nextDelta;
    /* 0x2C */ s32 state;
    /* 0x30 */ u16 chanMask;
    /* 0x32 */ s16 vol;
    /* 0x34 */ u8 maxChannels;
    /* 0x35 */ u8 debugFlags;
    /* 0x38 */ N_Event nextEvent;
    /* 0x48 */ ALEventQueue evtq;
    /* 0x5C */ ALMicroTime frameTime;
    /* 0x60 */ N_ChanState *chanState;
    /* 0x64 */ N_VoiceState *vAllocHead;
    /* 0x68 */ N_VoiceState *vAllocTail;
    /* 0x6C */ N_VoiceState *vFreeList;
    /* 0x70 */ ALOscInit initOsc;
    /* 0x74 */ ALOscUpdate updateOsc;
    /* 0x78 */ ALOscStop stopOsc;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ u8 unk88;
    /* 0x89 */ u8 unk89;
} N_CSPlayer; // size = 0x8C

#endif
