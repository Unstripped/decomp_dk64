#ifndef ACTOR_H
#define ACTOR_H

#include "common.h"

struct Actor;

typedef struct ActorSub4 {
    /* 0x00 */ u8 unk00[0x34];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
} ActorSub4;

typedef struct ActorSub140 {
    /* 0x00 */ u8 unk00[0x68];
    /* 0x68 */ s32 unk68;
    /* 0x6C */ u8 unk6C;
} ActorSub140;

typedef struct ActorList {
    /* 0x00 */ s32 items[4];
    /* 0x10 */ u8 count;
} ActorList; // size = 0x14

typedef struct ActorCallbackNode {
    /* 0x00 */ void *callback;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5[3];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ struct ActorCallbackNode *next;
    /* 0x18 */ struct ActorCallbackNode *prev;
} ActorCallbackNode; // size = 0x1C

typedef struct ActorQueueEntry {
    /* 0x00 */ ActorCallbackNode *node;
    /* 0x04 */ s32 arg0;
    /* 0x08 */ s32 arg6;
} ActorQueueEntry; // size = 0xC

typedef struct ActorEntry {
    /* 0x00 */ struct Actor *actor;
    /* 0x04 */ s32 unk4;
} ActorEntry; // size = 0x8

typedef struct ActorGlobalState {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1[1];
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3[0x12];
    /* 0x015 */ u8 unk15;
    /* 0x016 */ u8 unk16;
    /* 0x017 */ u8 unk17;
    /* 0x018 */ u8 unk18;
    /* 0x019 */ u8 unk19;
    /* 0x01A */ u8 unk1A;
    /* 0x01B */ u8 unk1B;
    /* 0x01C */ u8 unk1C;
    /* 0x01D */ u8 unk1D[7];
    /* 0x024 */ u8 unk24;
    /* 0x025 */ u8 unk25;
    /* 0x026 */ u8 unk26[6];
    /* 0x02C */ u8 unk2C;
    /* 0x02D */ u8 unk2D[0xB];
    /* 0x038 */ u8 unk38;
    /* 0x039 */ u8 unk39;
    /* 0x03A */ u8 unk3A[0x56];
    /* 0x090 */ u8 unk90;
    /* 0x091 */ u8 unk91;
    /* 0x092 */ u8 unk92[0x52];
    /* 0x0E4 */ u8 unkE4;
    /* 0x0E5 */ u8 unkE5;
    /* 0x0E6 */ u8 unkE6[2];
    /* 0x0E8 */ f32 unkE8;
    /* 0x0EC */ u8 unkEC[4];
    /* 0x0F0 */ f32 unkF0;
    /* 0x0F4 */ f32 unkF4;
    /* 0x0F8 */ u8 unkF8[0x100];
    /* 0x1F8 */ s32 unk1F8;
    /* 0x1FC */ s32 unk1FC;
    /* 0x200 */ u8 unk200;
    /* 0x201 */ u8 unk201;
    /* 0x202 */ u8 unk202[2];
    /* 0x204 */ s32 unk204[16];
    /* 0x244 */ u8 unk244[16];
    /* 0x254 */ u8 unk254;
    /* 0x255 */ u8 unk255[3];
    /* 0x258 */ s32 unk258[8];
    /* 0x278 */ s16 *unk278[8];
} ActorGlobalState;

typedef struct Actor {
    /* 0x000 */ u8 unk00[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 unk08[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 unk5E[2];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 unk6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ f32 unk88;
    /* 0x08C */ f32 unk8C;
    /* 0x090 */ f32 unk90;
    /* 0x094 */ u8 unk94[8];
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 unkA8[4];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 unkB0[8];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ f32 unkBC;
    /* 0x0C0 */ u8 unkC0[0x26];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 unkE8[0xC];
    /* 0x0F4 */ s16 unkF4;
    /* 0x0F6 */ s16 unkF6;
    /* 0x0F8 */ u8 unkF8[4];
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 unkFD;
    /* 0x0FE */ u8 unkFE[0x12];
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 unk111[3];
    /* 0x114 */ ActorList *unk114;
    /* 0x118 */ u8 unk118[4];
    /* 0x11C */ s32 unk11C;
    /* 0x120 */ u8 unk120[4];
    /* 0x124 */ s32 unk124;
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 unk12C[6];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ u8 unk134[4];
    /* 0x138 */ s32 unk138;
    /* 0x13C */ ActorCallbackNode *unk13C;
    /* 0x140 */ ActorSub140 *unk140;
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 unk145[0xB];
    /* 0x150 */ s32 unk150;
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155[7];
    /* 0x15C */ s16 unk15C;
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 unk160[8];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 unk16D;
    /* 0x16E */ u8 unk16E[6];
    /* 0x174 */ void *unk174;
} Actor;

#endif
