#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "common.h"
#include "actor.h"

// Cutscene script command: 16-bit opcode followed by three s16 parameters.
typedef struct CsCmd {
    /* 0x0 */ u16 op;
    /* 0x2 */ s16 a;
    /* 0x4 */ s16 b;
    /* 0x6 */ s16 c;
} CsCmd;

// Cutscene script condition (CsNode.unk2, csCondEval): opcode (bit 15 negates the result) and three
// s16 arguments. Same layout as CsCmd; csCondEval indexes the arguments, which gives its compares
// the field-first `bne` operand order of the target (CsCmd's named fields do not).
typedef struct CsCond {
    /* 0x0 */ s16 op;
    /* 0x2 */ s16 arg[3];
} CsCond;

// Per-model cutscene playback state (ModelSlot.unk7C: heapAlloc(0xA4) + csStateInit, 42630.c). csStateUpdate hands the
// same pointer to csCmdExec (gCsCmdTable handlers) and csCondEval (gCsCondTable handlers, 478F0.c).
typedef struct CsState {
    /* 0x00 */ void *data; // heap block (csStateFree heapFree()s it)
    /* 0x04 */ u32 alphaStepFrame;
    /* 0x08 */ f32 riderDriftX;
    /* 0x0C */ f32 riderDriftZ;
    /* 0x10 */ s16 sfxSources[2];
    /* 0x14 */ f32 vars[8];
    /* 0x34 */ f32 rotYDelta;
    /* 0x38 */ s32 pathHandle;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 unk40[2];
    /* 0x44 */ s16 timers[2]; // countdown timers: set by a cutscene command, decremented while non-zero (42630)
    /* 0x48 */ u8 stateBytes[3]; // read and written as bytes (478F0 csCmdBeatSyncAnimation: [0] == 2, csCmdLightPulse: [1] = 1 near the end)
    /* 0x4B */ u8 nextStateBytes[3]; // next unk48: csStateTickTimers copies unk48 in, csStateEndUpdate copies it back
    /* 0x4E */ u8 unk4E; // set when csStateUpdate moved the model, cleared each tick
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 pushMode;
    /* 0x51 */ u8 pushContact;
    /* 0x52 */ u8 pushInput;
    /* 0x53 */ u8 prevPushInput;
    /* 0x54 */ u8 updateMode;
    /* 0x55 */ u8 pad55[3];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 hitId;
    /* 0x5D */ u8 unk5D;
    /* 0x5E */ u16 hitActorType;
    /* 0x60 */ u8 alphaOverride;
    /* 0x61 */ u8 pad61;
    /* 0x62 */ s16 alphaTarget;
    /* 0x64 */ s16 alpha;
    /* 0x66 */ u8 alphaStep;
    /* 0x67 */ u8 unk67;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ s16 unk6C;
    /* 0x6E */ u8 contactCallbacks;
    /* 0x6F */ u8 unk6F;
    /* 0x70 */ u8 collisionEnabled;
    /* 0x71 */ u8 unk71;
    /* 0x72 */ u8 pad72[2];
    /* 0x74 */ f32 pushSpeed;
    /* 0x78 */ f32 pushSpeedMax;
    /* 0x7C */ f32 pushAccel;
    /* 0x80 */ s16 pushMinX;
    /* 0x82 */ s16 pushMinZ;
    /* 0x84 */ s16 pushMaxX;
    /* 0x86 */ s16 pushMaxZ;
    /* 0x88 */ s16 pushArcMin;
    /* 0x8A */ s16 pushArcMax;
    /* 0x8C */ f32 pushDirX;
    /* 0x90 */ f32 pushDirZ;
    /* 0x94 */ Actor *camPathActor;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ u8 runFlags;
    /* 0x9B */ u8 modelFlags;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ u8 pad9E[2];
    /* 0xA0 */ struct CsNode *nodes;
} CsState; // size = 0xA4

typedef struct CsPlayer {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ Actor *unk4;
} CsPlayer;

// Cutscene command handler (table gCsCmdTable, indexed by the command's a field).
typedef void (*CsCmdFunc)(CsState *, s16, s16, s16);

// Cutscene condition/command list node (one script step).
typedef struct CsNode {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ CsCond unk2[5];
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B;
    /* 0x2C */ CsCmd unk2C[4];
    /* 0x4C */ struct CsNode *unk4C;
} CsNode; // size = 0x50

// Countdown state of the cutscene countdown command (csCmdCountdownTimer, 478F0; heapAlloc(0x20) into
// CsState.data), drawn by 90D80's renderHitCounterHUD/renderCountdownTimerHUD callbacks.
typedef struct CsCountdown {
    /* 0x00 */ u64 last;
    /* 0x08 */ s64 duration;
    /* 0x10 */ s64 left;
    /* 0x18 */ s64 fired;
} CsCountdown; // size = 0x20

#endif
