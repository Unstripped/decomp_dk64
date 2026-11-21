#ifndef BOSS_H
#define BOSS_H
#include "actor.h"

// Boss script component (actor component 2, Actor+0x178): per-phase opcode script position.
typedef struct BossScriptState {
    /* 0x00 */ Actor *linkedActor;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ char pad6[2];
    /* 0x08 */ s16 vars[5];
    union {
        /* 0x12 */ u16 flags;      // bit 0 per boss: Army Dillo cannon side, round boss round started, Pufftoss phase 4 taken
        /* 0x12 */ u16 stagesDone; // K. Rool Tiny phase: stages finished 0..3 (flags 0x51..0x53), the active minion's bit index
    };
    /* 0x14 */ u8 phase;
    /* 0x15 */ u8 scriptPos;
    /* 0x16 */ u8 loopPos;
    /* 0x17 */ u8 pad17;
    union {
        /* 0x18 */ u8 byteVars[8];
        struct {
            /* 0x18 */ u8 pad18[4];
            /* 0x1C */ struct GfSndState *sndHandle; // Pufftoss voice handle (bossPufftossStep: n_alSndpStop/n_alSndpPlay)
        };
    };
} BossScriptState;

#endif
