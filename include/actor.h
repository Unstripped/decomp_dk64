struct CollisionStaticTri;
#ifndef ACTOR_H
#define ACTOR_H

#include "common.h"

struct Actor;

typedef struct ActorSub4 {
    /* 0x00 */ void *model;
    /* 0x04 */ u8 pad04[0x30];
    /* 0x34 */ f32 scaleX;
    /* 0x38 */ f32 scaleY;
    /* 0x3C */ f32 scaleZ;
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
    /* 0x18 */ s32 matrixIndex;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u8 active;
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
    /* 0x00 */ s32 scaledX;
    /* 0x04 */ s32 scaledY;
    /* 0x08 */ s32 scaledZ;
    /* 0x0C */ s32 scaledRadius;
    /* 0x10 */ s32 scaledHeight;
    /* 0x14 */ f32 radius;
    /* 0x18 */ f32 height;
    /* 0x1C */ u8 pad1C[0x8];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[0x3B];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 pad64[4];
    /* 0x68 */ s32 unk68;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 pad6D[3];
    /* 0x70 */ s32 boxBounds;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
    /* 0x8C */ ModelNode *nodes;
    /* 0x90 */ ModelSubNode *subNodes;
    /* 0x94 */ s32 triangleCount;
    /* 0x98 */ void *triangles;
    /* 0x9C */ s32 boxCount;
    /* 0xA0 */ void *boxes;
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
    /* 0x004 */ ActorSub4 *sub4;
    /* 0x008 */ u8 unk08[0x50];
    /* 0x058 */ s32 actorType;
    /* 0x05C */ u16 collisionFlags;
    /* 0x05E */ u8 unk5E[2];
    /* 0x060 */ u32 flags;
    /* 0x064 */ u32 renderFlags;
    /* 0x068 */ u16 flags2;
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
    /* 0x09C */ f32 peakY;
    /* 0x0A0 */ f32 prevPeakY;
    /* 0x0A4 */ f32 floorY;
    /* 0x0A8 */ u8 unkA8[4];
    /* 0x0AC */ f32 waterY;
    /* 0x0B0 */ s8 unkB0[4];
    /* 0x0B4 */ f32 distToFloor;
    /* 0x0B8 */ f32 speedXZ;
    /* 0x0BC */ f32 prevSpeedXZ;
    /* 0x0C0 */ f32 speedY;
    /* 0x0C4 */ f32 accelY;
    /* 0x0C8 */ f32 terminalSpeedY;
    /* 0x0CC */ u8 floorNodeId;
    /* 0x0CD */ u8 padCD[3];
    /* 0x0D0 */ u8 floorSurfaceType;
    /* 0x0D1 */ u8 floorSlopeType;
    /* 0x0D2 */ u8 padD2[6];
    /* 0x0D8 */ s16 floorTiltYaw;
    /* 0x0DA */ s16 floorTiltPitch;
    /* 0x0DC */ s16 floorSlopeYaw;
    /* 0x0DE */ s16 floorSlopePitch;
    /* 0x0E0 */ f32 floorSlopeFactor;
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
    /* 0x0FD */ u8 collisionHit;
    /* 0x0FE */ u8 unkFE[0xE];
    /* 0x10C */ s16 cutsceneId;
    /* 0x10E */ u8 unk10E[2];
    /* 0x110 */ u8 attachMode;
    /* 0x111 */ u8 unk111[3];
    /* 0x114 */ ActorList *riderList;
    /* 0x118 */ u8 unk118[4];
    /* 0x11C */ struct Actor *parentActor;
    /* 0x120 */ u8 unk120[4];
    /* 0x124 */ void *spawnData;
    /* 0x128 */ s16 alpha;
    /* 0x12A */ s16 drawDistance;
    /* 0x12C */ s16 chunkIndex;
    /* 0x12E */ u8 pad12E[2];
    /* 0x130 */ u8 cullMarginX;
    /* 0x131 */ u8 cullMarginY;
    /* 0x132 */ s16 interactionType;
    /* 0x134 */ s16 health;
    /* 0x136 */ s16 damage;
    /* 0x138 */ s32 callbackMask;
    /* 0x13C */ ActorCallbackNode *callbacks;
    /* 0x140 */ ActorSub140 *collision;
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 unk145[0xB];
    /* 0x150 */ struct CollisionStaticTri *floorTriangle;
    /* 0x154 */ u8 state;
    /* 0x155 */ u8 unk155[7];
    /* 0x15C */ s16 spawnTimer;
    /* 0x15E */ u8 eyeHeight;
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 splineT;
    /* 0x168 */ s16 yawSpeed;
    /* 0x16A */ u8 tintR;
    /* 0x16B */ u8 tintG;
    /* 0x16C */ u8 tintB;
    /* 0x16D */ u8 tintA;
    /* 0x16E */ u8 unk16E[6];
    /* 0x174 */ void *customState;
} Actor;

// Per-behaviour state objects reached through gBehaviourWorkState..gBehaviourExtraState.
typedef struct BehaviourWorkState {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 targetX;
    /* 0x0C */ s16 targetY;
    /* 0x0E */ s16 targetZ;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ u16 stepCount;
    /* 0x1A */ u16 flags;
    /* 0x1C */ u8 pad1C[0xC];
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ s16 timer;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ f32 scale;
} BehaviourWorkState;

typedef struct BehaviourAnimState {
    /* 0x00 */ u8 pad0[0x26];
    /* 0x26 */ s16 animId0;
    /* 0x28 */ s16 animId1;
    /* 0x2A */ s16 animId2;
    /* 0x2C */ u8 pad2C[0x46 - 0x2C];
    /* 0x46 */ u16 unk46;
} BehaviourAnimState;

typedef struct BehaviourExtraState {
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
} BehaviourExtraState;

// gActivePlayerState: typedef only; other files still declare gActivePlayerState with their own types.
typedef struct PlayerState {
    /* 0x000 */ s16 prevState;
    /* 0x002 */ u8 pad2[2];
    /* 0x004 */ f32 maxSpeed;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ s16 targetYaw;
    /* 0x00C */ u8 padC[4];
    /* 0x010 */ s16 actionTimer;
    /* 0x012 */ s16 subTimer;
    /* 0x014 */ s16 pitchAngle;
    /* 0x016 */ u8 pad16[6];
    /* 0x01C */ f32 slideSpeed;
    /* 0x020 */ u8 pad20[6];
    /* 0x026 */ s16 unk26;
    /* 0x028 */ s16 unk28;
    /* 0x02A */ u8 pad2A[2];
    /* 0x02C */ f32 airAccel;
    /* 0x030 */ f32 decelRate;
    /* 0x034 */ u8 pad34[4];
    /* 0x038 */ f32 targetSpeed;
    /* 0x03C */ s16 airTimer;
    /* 0x03E */ s16 approachTimer;
    /* 0x040 */ s16 approachYaw;
    /* 0x042 */ u8 fallTimer;
    /* 0x043 */ u8 pad43[5];
    /* 0x048 */ s16 turnRate;
    /* 0x04A */ u8 pad4A[0xA];
    /* 0x054 */ f32 jumpVelocityY;
    /* 0x058 */ s32 jumpTimer;
    /* 0x05C */ u32 jumpStartTime;
    /* 0x060 */ u8 pad60[8];
    /* 0x068 */ f32 slideLaunchSpeed;
    /* 0x06C */ u8 pad6C[0x1C];
    /* 0x088 */ Actor *actor;
    /* 0x08C */ u8 gunDrawn;
    /* 0x08D */ u8 hitStatus;
    /* 0x08E */ u8 pad8E[0x46];
    /* 0x0D4 */ s16 surfaceTimer;
    /* 0x0D6 */ s16 breathTimer;
    /* 0x0D8 */ u8 padD8[0x10];
    /* 0x0E8 */ u8 stateStep;
    /* 0x0E9 */ u8 padE9[0x13];
    /* 0x0FC */ s32 invulnTimer;
    /* 0x100 */ s32 respawnTimer;
    /* 0x104 */ Actor *camActor;
    /* 0x108 */ u8 pad108[6];
    /* 0x10E */ s16 targetPitch;
    /* 0x110 */ s16 targetRoll;
    /* 0x112 */ s16 targetYawAngle;
    /* 0x114 */ u8 pad114[0xC];
    /* 0x120 */ s32 lastFrame;
    /* 0x124 */ u8 pad124[0x7F];
    /* 0x1A3 */ u8 isHoldingObject;
    /* 0x1A4 */ u8 playerIndex;
    /* 0x1A5 */ u8 pad1A5[7];
    /* 0x1AC */ Actor *heldActor;
    /* 0x1B0 */ Actor *queuedHeldActor;
    /* 0x1B4 */ u8 pad1B4[4];
    /* 0x1B8 */ u16 heldActorType;
    /* 0x1BA */ u8 pad1BA[6];
    /* 0x1C0 */ f32 targetScale[3];
    /* 0x1CC */ f32 currentScale[3];
    /* 0x1D8 */ f32 scaleChangeRate;
    /* 0x1DC */ f32 targetScaleFactor;
    /* 0x1E0 */ f32 scaleStep;
    /* 0x1E4 */ s32 scaleMode;
    /* 0x1E8 */ u8 pad1E8[8];
    /* 0x1F0 */ s32 stateFlags;
    /* 0x1F4 */ s32 stateFlags2;
    /* 0x1F8 */ s32 prevStateFlags;
    /* 0x1FC */ s32 cartDamage;
    /* 0x200 */ s16 unk200;
    /* 0x202 */ u8 pad202[0x42];
    /* 0x244 */ u8 idleTimeoutFlag;
    /* 0x245 */ u8 damageCooldown;
    /* 0x246 */ s8 attackerValid;
    /* 0x247 */ s8 attackerType;
    /* 0x248 */ s8 attackerPlayerIndex;
    /* 0x249 */ u8 attackerSpawnNodeId;
    /* 0x24A */ u8 attackTimer;
    /* 0x24B */ u8 pad24B[5];
    /* 0x250 */ s32 effectTimer;
    /* 0x254 */ void *effectObj;
    /* 0x258 */ u8 pad258[0x10];
    /* 0x268 */ u8 transitionTimer;
    /* 0x269 */ u8 pad269[3];
} PlayerState;

extern BehaviourWorkState *gBehaviourWorkState;
extern Actor *gBehaviourTargetActor;
extern BehaviourAnimState *gBehaviourAnimState;
extern BehaviourExtraState *gBehaviourExtraState;

#endif
