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
    /* 0x0B */ u8 fxBus;
    /* 0x0C */ u8 sustain;
    /* 0x0D */ u8 fadeVol;
    /* 0x0E */ u8 fadeTarget;
    /* 0x0F */ u8 fadeRate;
    /* 0x10 */ u8 noteNotify;
    /* 0x11 */ u8 lowpassGain;
    /* 0x12 */ u8 lowpassKeyOffset;
    /* 0x13 */ u8 rspFxLevel; // MIDI controller 0x23 value, passed to new voices as PVoice_s.rspFxLevel (see audio_synth.h)
    /* 0x14 */ f32 pitchBend;
    /* 0x18 */ s32 attackTime;
    /* 0x1C */ s32 decayTime;
    /* 0x20 */ s32 releaseTime;
    /* 0x24 */ u8 useInstCopy;
    /* 0x25 */ u8 attackVolume;
    /* 0x26 */ u8 decayVolume;
    /* 0x27 */ s8 detune;
    /* 0x28 */ u8 tremType;
    /* 0x29 */ u8 tremRate;
    /* 0x2A */ u8 tremDepth;
    /* 0x2B */ u8 tremDelay;
    /* 0x2C */ u8 vibType;
    /* 0x2D */ u8 vibRate;
    /* 0x2E */ u8 vibDepth;
    /* 0x2F */ u8 vibDelay;
    /* 0x30 */ u8 pad30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 bankSelect;
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
            u8 busIndex;
            u8 paramId;
            u8 delayIndex;
            u32 value;
        } cmd;
    } msg;
} N_Event;

// The sequence player itself (gSeqPlayers[], 0x8C bytes). Its first 0x7C bytes are libaudio.h's ALCSPlayer
// field for field; `al` is that SDK view, passed to the libaudio.h API (alCSPPlay, alCSPGetState, ...), while the
// game code uses the game-typed members (chanState/vAlloc*/nextEvent differ from the SDK element types).
typedef struct N_CSPlayer {
    union {
        /* 0x00 */ ALCSPlayer al;
        struct {
            /* 0x00 */ ALPlayer node;
            /* 0x14 */ struct N_ALSynth *drvr; // n_syn (n_alCSPlayerNew)
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
        };
    };
    /* 0x7C */ f32 fxMixOffset;
    /* 0x80 */ f32 fxMixScale;
    /* 0x84 */ OSMesgQueue *eventQueue; // song-event messages (__n_CSPHandleMIDIMsg osSendMesg; set by alCSPSetEventQueue)
    /* 0x88 */ u8 maxVoices;
    /* 0x89 */ u8 voiceCount;
} N_CSPlayer; // size = 0x8C

#endif
