// n_alCSPPlay (src/global/137C10.c): stage 6: text identical except fp reg numbering: target lwc1 f4,tempo(4sp) / lwc1 f6,8(t7) / mul f8,f4,f6; ours gives f6=tempo,f4=qnpt (ugen evaluates deeper operand first); tried operand swap, casts, *(&tempo), double casts
#include "common.h"

typedef struct GdVoiceState_s {
    /* 0x00 */ struct GdVoiceState_s *next;
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
} GdVoiceState;

typedef struct {
    /* 0x00 */ ALInstrument *instrument;
    /* 0x04 */ s16 bendRange;
    /* 0x06 */ u8 pad06;
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
} GdChanState;

typedef s32 (*GdOscInit)(void **, f32 *, u8, u8, u8, u8, u8);

typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ void *drvr;
    /* 0x18 */ ALCSeq *target;
    /* 0x1C */ s32 curTime;
    /* 0x20 */ ALBank *bank;
    /* 0x24 */ s32 uspt;
    /* 0x28 */ s32 nextDelta;
    /* 0x2C */ s32 state;
    /* 0x30 */ u16 chanMask;
    /* 0x32 */ s16 vol;
    /* 0x34 */ u8 maxChannels;
    /* 0x35 */ u8 debugFlags;
    /* 0x38 */ ALEvent nextEvent;
    /* 0x48 */ ALEventQueue evtq;
    /* 0x5C */ s32 frameTime;
    /* 0x60 */ GdChanState *chanState;
    /* 0x64 */ GdVoiceState *vAllocHead;
    /* 0x68 */ GdVoiceState *vAllocTail;
    /* 0x6C */ GdVoiceState *vFreeList;
    /* 0x70 */ GdOscInit initOsc;
    /* 0x74 */ void *updateOsc;
    /* 0x78 */ void *stopOsc;
    /* 0x7C */ u8 pad7C[8];
    /* 0x84 */ OSMesgQueue *msgq;
    /* 0x88 */ u8 unk88;
} GdCSPlayer;

void n_alCSPPlay(GdCSPlayer *seqp, f32 tempo) {
    if (seqp->target != NULL) {
        seqp->uspt = seqp->target->qnpt * tempo;
    } else {
        seqp->uspt = 0x1E8;
    }
}
