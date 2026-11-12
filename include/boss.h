#ifndef BOSS_H
#define BOSS_H
#include "actor.h"

// Boss script component (actor component 2, Actor+0x178): per-phase opcode script position.
typedef struct BossScriptState {
    /* 0x00 */ Actor *linkedActor;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ char pad6[2];
    /* 0x08 */ s16 unk8[5];
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u8 phase;
    /* 0x15 */ u8 scriptPos;
    /* 0x16 */ u8 loopPos;
    /* 0x17 */ u8 pad17;
    /* 0x18 */ u8 unk18[8];
} BossScriptState;

#endif
