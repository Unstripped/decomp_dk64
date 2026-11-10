#ifndef AUDIO_CONFIG_H
#define AUDIO_CONFIG_H

#include "common.h"

// Synthesizer config built by audioInit (5A50.c), completed by audioThreadInit (6710.c) and
// handed to n_alInit. Rare's two-bus variant of libaudio's ALSynConfig: one effect type and
// one parameter table per aux bus (n_alFxNew reads params[bus] when fxType[bus] is AL_FX_CUSTOM).
typedef struct AudioInitArgs {
    /* 0x00 */ s32 maxVVoices;
    /* 0x04 */ s32 maxPVoices;
    /* 0x08 */ s32 maxUpdates;
    /* 0x0C */ s32 maxFXbusses;
    /* 0x10 */ void *dmaNew;      // audioDmaNew, set by audioThreadInit
    /* 0x14 */ ALHeap *heap;
    /* 0x18 */ s32 outputRate;    // set by audioThreadInit
    /* 0x1C */ ALFxId fxType[2];
    /* 0x1E */ s16 pad1E;
    /* 0x20 */ s32 *params[2];
} AudioInitArgs; // size = 0x28

// Audio manager config for audioThreadInit (the SDK's amConfig).
typedef struct AudioTaskConfig {
    /* 0x0 */ u32 outputRate;
    /* 0x4 */ u32 framesPerField;
    /* 0x8 */ u32 cmdCount;       // command-list length per frame, in Acmds
} AudioTaskConfig; // size = 0xC

// Sound player config for n_alSndpNew (13A7A0.c).
typedef struct GeSndpConfig {
    /* 0x00 */ s32 maxSounds;
    /* 0x04 */ s32 maxEvents;
    /* 0x08 */ s32 unk8;          // copied to the sound player's unk44
    /* 0x0C */ ALHeap *heap;
    /* 0x10 */ u16 maxStates;
} GeSndpConfig; // size = 0x14

#endif
