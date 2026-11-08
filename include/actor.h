#ifndef ACTOR_H
#define ACTOR_H

#include "common.h"

struct Actor;

typedef struct ActorSub4 {
    /* 0x00 */ void *model;
    /* 0x04 */ u8 pad04[0x30];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ u8 pad40[0x24];
    /* 0x64 */ u16 animId;
} ActorSub4;

typedef struct ModelNode {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ struct ModelNode *next;
} ModelNode; // size = 0x2C

typedef struct ModelSubNode {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ struct ModelSubNode *next;
} ModelSubNode; // size = 0x20

typedef struct ActorSub140 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x8];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[0x3B];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 pad64[4];
    /* 0x68 */ s32 unk68;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 pad6D[3];
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ ModelNode *unk8C;
    /* 0x90 */ ModelSubNode *unk90;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ void *unk98;
    /* 0x9C */ s32 unk9C;
    /* 0xA0 */ void *unkA0;
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ u8 unkAC;
    /* 0xAD */ u8 padAD[0x17];
} ActorSub140; // size = 0xC4

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
    /* 0x058 */ s32 actorType;
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 unk5E[2];
    /* 0x060 */ u32 flags;
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u16 contactFlags;
    /* 0x06C */ u16 prevContactFlags;
    /* 0x06E */ s16 soundSlot;
    /* 0x070 */ u8 unk70[0xC];
    /* 0x07C */ f32 x;
    /* 0x080 */ f32 y;
    /* 0x084 */ f32 z;
    /* 0x088 */ f32 prevX;
    /* 0x08C */ f32 prevY;
    /* 0x090 */ f32 prevZ;
    /* 0x094 */ u8 unk94[8];
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ f32 floorY;
    /* 0x0A8 */ u8 unkA8[4];
    /* 0x0AC */ f32 waterY;
    /* 0x0B0 */ s8 unkB0[8];
    /* 0x0B8 */ f32 speedXZ;
    /* 0x0BC */ f32 prevSpeedXZ;
    /* 0x0C0 */ f32 speedY;
    /* 0x0C4 */ f32 accelY;
    union {
        /* 0x0C8 */ u8 unkC8[0x1C];
        struct {
            /* 0x0C8 */ f32 terminalSpeedY;
            /* 0x0CC */ u8 padCC[4];
            /* 0x0D0 */ u8 floorSurfaceType;
            /* 0x0D1 */ u8 unkD1;
            /* 0x0D2 */ u8 padD2[6];
            /* 0x0D8 */ s16 floorTiltYaw;
            /* 0x0DA */ s16 floorTiltPitch;
            /* 0x0DC */ s16 unkDC;
            /* 0x0DE */ s16 unkDE;
            /* 0x0E0 */ f32 unkE0;
        };
    };
    /* 0x0E4 */ s16 pitch;
    /* 0x0E6 */ s16 yaw;
    /* 0x0E8 */ s16 roll;
    /* 0x0EA */ u8 unkEA[4];
    /* 0x0EE */ s16 moveYaw;
    /* 0x0F0 */ s16 movePitch;
    /* 0x0F2 */ u8 unkF2[2];
    /* 0x0F4 */ s16 arcYawMin;
    /* 0x0F6 */ s16 arcYawMax;
    /* 0x0F8 */ u8 unkF8[4];
    /* 0x0FC */ u8 hasArcBounds;
    /* 0x0FD */ u8 unkFD;
    /* 0x0FE */ u8 unkFE[0xE];
    /* 0x10C */ s16 unk10C;
    /* 0x10E */ u8 unk10E[2];
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 unk111[3];
    /* 0x114 */ ActorList *riderList;
    /* 0x118 */ u8 unk118[4];
    /* 0x11C */ struct Actor *owner;
    /* 0x120 */ u8 unk120[4];
    /* 0x124 */ s32 unk124;
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 unk12C[6];
    /* 0x132 */ s16 unk132;
    /* 0x134 */ s16 health;
    /* 0x136 */ s16 damage;
    /* 0x138 */ s32 callbackMask;
    /* 0x13C */ ActorCallbackNode *callbacks;
    /* 0x140 */ ActorSub140 *unk140;
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 unk145[0xB];
    /* 0x150 */ s32 unk150;
    /* 0x154 */ u8 state;
    /* 0x155 */ u8 unk155[7];
    /* 0x15C */ s16 unk15C;
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 unk16D;
    /* 0x16E */ u8 unk16E[6];
    /* 0x174 */ void *customState;
} Actor;
#define unk6A contactFlags
#define unk6E soundSlot
#define unkF0 movePitch
#define unkF4 arcYawMin
#define unkF6 arcYawMax
#define unkFC hasArcBounds
#define unk11C owner
#define unk138 callbackMask
#define unk174 customState

// Per-behaviour state objects reached through D_807FDC90..D_807FDC9C.
// Fields are named by offset; sizes are the largest offset seen so far.
typedef struct Struct807FDC90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[0xE];
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ f32 unk30;
} Struct807FDC90;

typedef struct Struct807FDC98 {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ u16 unk46;
} Struct807FDC98;

typedef struct Struct807FDC9C {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 padD[3];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ u8 unk14;
} Struct807FDC9C;

// gActivePlayerState: typedef only; other files still declare gActivePlayerState with their own types.
typedef struct Struct807FD580 {
    /* 0x000 */ u8 pad0[0x88];
    /* 0x088 */ Actor *actor;
    /* 0x08C */ u8 pad8C[0x104 - 0x8C];
    /* 0x104 */ Actor *camActor;
    /* 0x108 */ u8 pad108[0x1A4 - 0x108];
    /* 0x1A4 */ u8 playerIndex;
    /* 0x1A5 */ u8 pad1A5[0x1AC - 0x1A5];
    /* 0x1AC */ Actor *heldActor;
    /* 0x1B0 */ Actor *queuedHeldActor;
    /* 0x1B4 */ u8 pad1B4[0x1B8 - 0x1B4];
    /* 0x1B8 */ u16 heldActorType;
    /* 0x1BA */ u8 pad1BA[0x1C0 - 0x1BA];
    /* 0x1C0 */ f32 targetScale[3];
    /* 0x1CC */ f32 currentScale[3];
    /* 0x1D8 */ f32 scaleChangeRate;
    /* 0x1DC */ f32 targetScaleFactor;
    /* 0x1E0 */ f32 scaleStep;
    /* 0x1E4 */ s32 scaleMode;
    /* 0x1E8 */ u8 pad1E8[0x1F0 - 0x1E8];
    /* 0x1F0 */ s32 stateFlags;
} Struct807FD580;
#define unk104 camActor
#define unk1AC heldActor
#define unk1B0 queuedHeldActor
#define unk1B8 heldActorType
#define unk1F0 stateFlags
#define unk1D8 scaleChangeRate

extern Struct807FDC90 *D_807FDC90;
extern Actor *D_807FDC94;
extern Struct807FDC98 *D_807FDC98;
extern Struct807FDC9C *D_807FDC9C;

#endif
