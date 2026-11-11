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

// Byte view of the same command (low bytes of a, b, c).
typedef struct CsCmdBytes {
    /* 0x0 */ u16 op;
    /* 0x2 */ u8 aHi;
    /* 0x3 */ u8 a;
    /* 0x4 */ u8 bHi;
    /* 0x5 */ u8 b;
    /* 0x6 */ u8 cHi;
    /* 0x7 */ u8 c;
} CsCmdBytes;

#define CMDB(cmd) ((CsCmdBytes *)(cmd))

// Per-cutscene playback state.
typedef struct CsState {
    /* 0x00 */ void *data;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10[2];
    /* 0x14 */ f32 unk14[9];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 pad3C[8];
    /* 0x44 */ s16 unk44[3];
    /* 0x4A */ u8 pad4A;
    /* 0x4B */ u8 unk4B[4];
    /* 0x4F */ s8 unk4F;
    /* 0x50 */ s8 unk50;
    /* 0x51 */ u8 pad51[0xB];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 unk5D;
    /* 0x5E */ u16 unk5E;
    /* 0x60 */ s8 unk60;
    /* 0x61 */ u8 pad61;
    /* 0x62 */ s16 unk62;
    /* 0x64 */ u8 pad64[2];
    /* 0x66 */ u8 unk66;
    /* 0x67 */ s8 unk67;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ s16 unk6C;
    /* 0x6E */ s8 unk6E;
    /* 0x6F */ s8 unk6F;
    /* 0x70 */ s8 unk70;
    /* 0x71 */ s8 unk71;
    /* 0x72 */ u8 pad72[6];
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[8];
    /* 0x94 */ Actor *unk94;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ u8 unk9A;
    /* 0x9B */ u8 unk9B;
} CsState;

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
    /* 0x02 */ CsCmd unk2[5];
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B;
    /* 0x2C */ CsCmd unk2C[4];
    /* 0x4C */ struct CsNode *unk4C;
} CsNode; // size = 0x50

// Whole-state layout of the cutscene state (CsState above types only part of it); 0xA4 bytes.
typedef struct CsStateFull {
    /* 0x00 */ void *unk0; // heap block (csStateFree heapFree()s it)
    /* 0x04 */ u32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14[8];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 unk40[2];
    /* 0x44 */ s16 unk44[2];
    /* 0x48 */ u8 unk48[3];
    /* 0x4B */ u8 unk4B[3];
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 unk53;
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 pad55[3];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 pad61;
    /* 0x62 */ s16 unk62;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ u8 unk66;
    /* 0x67 */ u8 unk67;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ s16 unk6C;
    /* 0x6E */ u8 unk6E;
    /* 0x6F */ u8 unk6F;
    /* 0x70 */ u8 unk70;
    /* 0x71 */ u8 unk71;
    /* 0x72 */ u8 pad72[2];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ Actor *unk94;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ u8 unk9A;
    /* 0x9B */ u8 unk9B;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ u8 pad9E[2];
    /* 0xA0 */ CsNode *unkA0;
} CsStateFull; // size = 0xA4

#endif
