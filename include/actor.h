struct CollisionStaticTri;
#ifndef ACTOR_H
#define ACTOR_H

#include "common.h"

struct Actor;

// Bone override lists of an actor's animation state (ActorSub4), applied when the model's
// bone matrices are built. Each list is heap-allocated by its owner and ends with a
// terminator record.
typedef struct BoneRotation {
    /* 0x0 */ s8 weight;   // constant writers use 0x7F or -0x80; 0 ends the list
    /* 0x1 */ u8 bone;
    /* 0x2 */ u16 rotX;    // binary angles, 0x10000 = one turn
    /* 0x4 */ u16 rotY;
    /* 0x6 */ u16 rotZ;
} BoneRotation; // size = 0x8

typedef struct BoneVector {
    /* 0x0 */ u8 bone;     // 0xFF ends the list
    /* 0x1 */ u8 lastBone; // last bone of the range, or 0xFF
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ f32 x;
    /* 0x8 */ f32 y;
    /* 0xC */ f32 z;
} BoneVector; // size = 0x10

// Animation clip asset (asset table 0xB), shared through controllerAnimCacheGetOrLoad's
// reference-counted cache. Only the fields animation code reads are named; its size is
// not known.
typedef struct AnimClip {
    /* 0x00 */ f32 speed;      // a slot's starting speed
    /* 0x04 */ u16 flags;      // a slot's starting flags
    /* 0x06 */ u16 unk6;       // advanced by 6 when the clip is loaded
    /* 0x08 */ u8 pad8[0xA];
    /* 0x12 */ u8 frameCount;
} AnimClip;

// One playing animation: four of these follow the ActorSub4 head (controllerAnimInit).
typedef struct AnimSlot {
    /* 0x00 */ AnimClip *clip;
    /* 0x04 */ f32 frame;            // playback position, firstFrame..lastFrame
    /* 0x08 */ f32 frameFrac;        // frame - frameIndex
    /* 0x0C */ s16 frameIndex;
    /* 0x0E */ s16 nextFrameIndex;
    /* 0x10 */ s16 animId;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ f32 firstFrame;
    /* 0x18 */ f32 lastFrame;        // clip->frameCount - 1
    /* 0x1C */ s16 flags;            // 2 loop, 4 ping-pong, 8 jump from jumpFrom to jumpTo
    /* 0x1E */ s16 jumpFrom;
    /* 0x20 */ s16 jumpTo;
    /* 0x22 */ u8 pad22[2];
    /* 0x24 */ f32 speed;            // frames per step, ramped from speedFrom to speedTo
    /* 0x28 */ f32 speedFrom;
    /* 0x2C */ f32 speedTo;
    /* 0x30 */ f32 speedRampTime;
    /* 0x34 */ f32 speedRampDuration; // 0: no ramp
} AnimSlot; // size = 0x38

// Animation state: the 0x90-byte head of the block controllerAnimInit allocates
// (boneCount * 0x80 + 0x170 bytes: this head, four 0x38-byte animation slots at 0x90,
// then two arrays of boneCount matrices at 0x170). Its tail (0x5C..0x8C) is the state of
// the animation script the actor runs (actorScriptExecute).
typedef struct ActorSub4 {
    /* 0x00 */ AnimSlot *model;          // current animation
    /* 0x04 */ AnimSlot *layer;          // layered animation, weighted by layerWeight
    /* 0x08 */ AnimSlot *blendFrom;      // previous animation while blendTime < blendDuration
    /* 0x0C */ AnimSlot *blendFromLayer; // previous layer, weighted by blendFromLayerWeight
    /* 0x10 */ f32 blendWeight;          // (blendDuration - blendTime) / blendDuration
    /* 0x14 */ Mtx *boneMtx[2];          // boneCount matrices each, indexed by gGfxBufferIndex
    /* 0x1C */ BoneRotation *boneRotations;
    /* 0x20 */ BoneVector *boneScales;
    /* 0x24 */ BoneVector *boneOffsets;
    /* 0x28 */ s16 layerWeight;          // steps by layerWeightStep towards layerWeightTarget
    /* 0x2A */ s16 blendFromLayerWeight;
    /* 0x2C */ s16 layerWeightTarget;
    /* 0x2E */ s16 layerWeightStep;
    /* 0x30 */ s16 motionFlags;          // 1: step by the frame delta
    /* 0x32 */ u8 pad32[2];
    union {
        struct {
            /* 0x34 */ f32 scaleX;
            /* 0x38 */ f32 scaleY;
            /* 0x3C */ f32 scaleZ;
        };
        /* 0x34 */ f32 scale[3]; // indexed by axis (raceManagerBehaviorUpdate's per-axis loop)
    };
    /* 0x40 */ f32 blendTime;
    /* 0x44 */ f32 blendDuration;
    /* 0x48 */ f32 unk48;                // playback speed, ramped from speedFrom to speedTo
    /* 0x4C */ f32 speedFrom;
    /* 0x50 */ f32 speedTo;
    /* 0x54 */ f32 speedRampTime;
    /* 0x58 */ f32 speedRampDuration;    // 0: no ramp
    /* 0x5C */ u16 returnScriptId;       // script call: animId and offset to resume at
    /* 0x5E */ u8 pad5E[2];
    /* 0x60 */ s32 returnOffset;
    /* 0x64 */ u16 animId;               // id of the running script (actorScriptStart)
    /* 0x66 */ u8 pad66[2];
    /* 0x68 */ u8 *scriptStart;          // NULL: no script
    /* 0x6C */ u8 *scriptPc;
    /* 0x70 */ void (*scriptCommand)(struct Actor *); // run after the script each frame
    /* 0x74 */ u8 *scriptCommandPc;
    /* 0x78 */ s32 scriptWaitFlags;      // the script runs while this is 0
    /* 0x7C */ s32 loopCount;
    /* 0x80 */ f32 waitFrame;
    /* 0x84 */ s32 waitOnLayer;          // script waits watch layer instead of model
    /* 0x88 */ s32 scriptResult;         // comparison result of animation script commands
    /* 0x8C */ f32 scriptTimer;
} ActorSub4; // size = 0x90

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
    /* 0x1C */ f32 unk1C; /* arc contact point x */
    /* 0x20 */ f32 unk20; /* arc contact point z */
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25;
    /* 0x26 */ s16 unk26; // hit model entry id (actorBuildCollisionHit)
    /* 0x28 */ f32 unk28[3]; // hit triangle in the model's local space (x of the 3 vertices)
    /* 0x34 */ f32 unk34[3];
    /* 0x40 */ f32 unk40[3];
    /* 0x4C */ f32 unk4C; // actor position in the model's local space
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s16 unk58; // hit box index in the slot's box table
    /* 0x5A */ s8 unk5A; // hit box bone
    /* 0x5B */ u8 pad5B;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ s16 unk66;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 pad6D[3];
    /* 0x70 */ void *boxBounds;
    /* 0x74 */ Mtx *unk74[2]; /* per gfx buffer, indexed by gGfxBufferIndex */
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
    /* 0xA4 */ struct CollisionBox *unkA4; /* transformed boxes (actorSub140BuildBoxes) */
    /* 0xA8 */ struct CollisionBox *unkA8; /* one past the last valid box */
    /* 0xAC */ u8 unkAC;
    /* 0xAD */ u8 padAD[3];
    /* 0xB0 */ s32 unkB0; // last box contact x/z (actorComputeBoxNormal)
    /* 0xB4 */ s32 unkB4;
    /* 0xB8 */ u8 padB8[0xC4 - 0xB8];
} ActorSub140; // size = 0xC4

// Animated-model asset header (controllerAnimStateLoadAsset relocates it, animListInit reads unk10).
typedef struct AnimInitData {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void **unk4; // pointer table; the first entry is the display list
    /* 0x08 */ void *unk8;
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10; // s16 animation node list (animListInit)
    /* 0x14 */ struct ControllerSubNode *unk14;
    /* 0x18 */ u8 pad18[8];
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
} AnimInitData; // size = 0x24

typedef struct ActorList {
    /* 0x00 */ struct Actor *items[4];
    /* 0x10 */ u8 count;
} ActorList; // size = 0x14

// Payloads of global callback nodes registered by the player's held-actor code (CEAE0.c);
// the step callback receives &node->heldFollow / &node->heldAlign.
typedef struct HeldActorFollowArg {
    /* 0x0 */ f32 blend;
    /* 0x4 */ struct Actor *player;
    /* 0x8 */ struct Actor *held;
} HeldActorFollowArg;

typedef struct HeldActorAlignArg {
    /* 0x0 */ struct Actor *player;
    /* 0x4 */ struct Actor *held;
} HeldActorAlignArg;

typedef struct ActorCallbackNode {
    /* 0x00 */ void *callback;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5[3];
    union {
        struct {
            /* 0x08 */ struct Actor *source;
            /* 0x0C */ s32 unkC;
            /* 0x10 */ void *unk10;
        };
        /* 0x08 */ HeldActorFollowArg heldFollow; // playerRegisterHeldActorFollow (CEAE0.c)
        /* 0x08 */ HeldActorAlignArg heldAlign; // playerRegisterHeldActorAlign (CEAE0.c)
    };
    /* 0x14 */ struct ActorCallbackNode *next;
    /* 0x18 */ struct ActorCallbackNode *prev;
} ActorCallbackNode; // size = 0x1C

typedef struct ActorQueueEntry {
    /* 0x00 */ ActorCallbackNode *node;
    /* 0x04 */ struct Actor *target;
    /* 0x08 */ s32 arg6;
} ActorQueueEntry; // size = 0xC

typedef struct ActorEntry {
    /* 0x00 */ struct Actor *actor;
    /* 0x04 */ s32 unk4;
} ActorEntry; // size = 0x8

typedef struct ActorCollisionHit {
    f32 unk0[3];
    f32 unkC[9];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    struct Actor *unk3C;
} ActorCollisionHit; // size = 0x40

typedef struct ActorGlobalState {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1[1];
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ f32 unk4;
    /* 0x008 */ f32 unk8;
    /* 0x00C */ f32 unkC;
    /* 0x010 */ s16 unk10;
    /* 0x012 */ s16 unk12;
    /* 0x014 */ u8 unk14;
    /* 0x015 */ u8 unk15;
    /* 0x016 */ u8 unk16;
    /* 0x017 */ u8 unk17;
    /* 0x018 */ u8 unk18;
    /* 0x019 */ u8 unk19;
    /* 0x01A */ u8 unk1A;
    /* 0x01B */ u8 unk1B;
    /* 0x01C */ u8 unk1C;
    /* 0x01D */ u8 unk1D[3];
    /* 0x020 */ struct Actor *unk20;
    /* 0x024 */ u8 unk24;
    /* 0x025 */ u8 unk25;
    /* 0x026 */ u8 unk26[2];
    /* 0x028 */ struct Actor *unk28;
    /* 0x02C */ u8 unk2C;
    /* 0x02D */ u8 unk2D[3];
    /* 0x030 */ f32 unk30;
    /* 0x034 */ s16 unk34;
    /* 0x036 */ s16 unk36;
    /* 0x038 */ u8 unk38;
    /* 0x039 */ u8 unk39;
    /* 0x03A */ u8 unk3A[2];
    /* 0x03C */ f32 unk3C[4][3];
    /* 0x06C */ s32 unk6C[4];
    /* 0x07C */ struct Actor *unk7C[4];
    /* 0x08C */ u8 unk8C[4];
    /* 0x090 */ u8 unk90;
    /* 0x091 */ u8 unk91;
    /* 0x092 */ s16 unk92;
    /* 0x094 */ s16 unk94;
    /* 0x096 */ u8 unk96[2];
    /* 0x098 */ f32 unk98[3];   // surface hit payload copy (12 bytes, from payload +0x4)
    /* 0x0A4 */ f32 unkA4[9];  // surface hit payload copy (0x24 bytes, from payload +0x10)
    /* 0x0C8 */ s32 unkC8;
    /* 0x0CC */ struct Actor *unkCC;
    /* 0x0D0 */ s32 unkD0;
    /* 0x0D4 */ s32 unkD4;
    /* 0x0D8 */ f32 unkD8;
    /* 0x0DC */ f32 unkDC;
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ u8 unkE4;
    /* 0x0E5 */ u8 unkE5;
    /* 0x0E6 */ u8 unkE6[2];
    /* 0x0E8 */ f32 unkE8;
    /* 0x0EC */ struct Actor *unkEC;
    /* 0x0F0 */ f32 unkF0;
    /* 0x0F4 */ f32 unkF4;
    /* 0x0F8 */ ActorCollisionHit unkF8[4];
    /* 0x1F8 */ s32 unk1F8;
    /* 0x1FC */ struct Actor *targetActor;
    /* 0x200 */ u8 bossFightPhase;
    /* 0x201 */ u8 unk201;
    /* 0x202 */ u8 unk202[2];
    /* 0x204 */ struct Actor *unk204[16];
    /* 0x244 */ u8 unk244[16];
    /* 0x254 */ u8 unk254;
    /* 0x255 */ u8 unk255[3];
    /* 0x258 */ s32 unk258[8];
    /* 0x278 */ s16 *unk278[8];
} ActorGlobalState;

// Path-follow state (Actor.floorContact; pathFollowUpdateHeading allocates it, actor teardown frees it); 0x14 bytes.
typedef struct PathFollowState {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 padD;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} PathFollowState; // size = 0x14

// One entry of an actor's segment-animation list (Actor.animList; 8CA50 animListInit builds it from
// the model asset, animListUpdate steps it, animSetSegments binds each node's current frame to its segment).
typedef struct AnimNode {
    /* 0x00 */ void **items;
    /* 0x04 */ void **buffers;
    /* 0x08 */ u8 segment;
    /* 0x09 */ u8 pad9;
    /* 0x0A */ s16 itemCount;
    /* 0x0C */ s16 frame;
    /* 0x0E */ u8 padE[0x2];
    /* 0x10 */ f32 speed;
    /* 0x14 */ f32 subframe;
    /* 0x18 */ s16 loopLimit;
    /* 0x1A */ s16 loopCount;
    /* 0x1C */ s16 startFrame;
    /* 0x1E */ s16 endFrame;
    /* 0x20 */ u8 direction;
    /* 0x21 */ u8 loopMode;
    /* 0x22 */ u8 finished;
    /* 0x23 */ u8 bindSegment;
    /* 0x24 */ struct AnimNode *next;
} AnimNode;

typedef struct Actor {
    /* 0x000 */ void *animState;
    /* 0x004 */ ActorSub4 *sub4;
    /* 0x008 */ Mtx *boneMtx;               // sub4->boneMtx[gGfxBufferIndex] (actorCheckWorldBounds)
    /* 0x00C */ f32 modelMtx[4][4];
    /* 0x04C */ void *overrideModel;        // drawn instead of animState when set
    /* 0x050 */ void *stateModel;           // drawn instead of both when set
    /* 0x054 */ s32 instanceId;
    /* 0x058 */ u32 actorType;
    /* 0x05C */ u16 collisionFlags;
    /* 0x05E */ u8 unk5E[2];
    /* 0x060 */ u32 flags;
    /* 0x064 */ u32 renderFlags;
    /* 0x068 */ u16 flags2;
    /* 0x06A */ u16 contactFlags;
    /* 0x06C */ u16 prevContactFlags;
    /* 0x06E */ s16 soundSlots[2];
    /* 0x072 */ s16 unk72;
    /* 0x074 */ f32 unk74;
    /* 0x078 */ u8 unk78[4];
    /* 0x07C */ f32 x;
    /* 0x080 */ f32 y;
    /* 0x084 */ f32 z;
    /* 0x088 */ f32 prevX;
    /* 0x08C */ f32 prevY;
    /* 0x090 */ f32 prevZ;
    /* 0x094 */ f32 unk94;
    /* 0x098 */ f32 unk98;
    /* 0x09C */ f32 peakY;
    /* 0x0A0 */ f32 prevPeakY;
    /* 0x0A4 */ f32 floorY;
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ f32 waterY;
    /* 0x0B0 */ s8 unkB0[4];
    /* 0x0B4 */ f32 distToFloor;
    /* 0x0B8 */ f32 speedXZ;
    /* 0x0BC */ f32 prevSpeedXZ;
    /* 0x0C0 */ f32 speedY;
    /* 0x0C4 */ f32 accelY;
    /* 0x0C8 */ f32 terminalSpeedY;
    /* 0x0CC */ u8 floorNodeId;
    /* 0x0CD */ u8 unkCD;
    /* 0x0CE */ s16 boundingRadius;
    /* 0x0D0 */ u8 floorSurfaceType;
    /* 0x0D1 */ u8 floorSlopeType;
    /* 0x0D2 */ u8 padD2[2];
    /* 0x0D4 */ void *unkD4;
    /* 0x0D8 */ s16 floorTiltYaw;
    /* 0x0DA */ s16 floorTiltPitch;
    /* 0x0DC */ s16 floorSlopeYaw;
    /* 0x0DE */ s16 floorSlopePitch;
    /* 0x0E0 */ f32 floorSlopeFactor;
    /* 0x0E4 */ s16 pitch;
    /* 0x0E6 */ s16 yaw;
    /* 0x0E8 */ s16 roll;
    /* 0x0EA */ s16 unkEA;
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ s16 moveYaw;
    /* 0x0F0 */ s16 movePitch;
    /* 0x0F2 */ s16 unkF2;
    /* 0x0F4 */ s16 arcYawMin;
    /* 0x0F6 */ s16 arcYawMax;
    /* 0x0F8 */ s16 unkF8;
    /* 0x0FA */ s16 unkFA;
    /* 0x0FC */ u8 hasArcBounds;
    /* 0x0FD */ u8 collisionHit;
    /* 0x0FE */ u8 padFE[2];
    /* 0x100 */ f32 unk100; // attach point in the model node's local space (collisionAttachActorToObjectNode)
    /* 0x104 */ f32 unk104;
    /* 0x108 */ f32 unk108;
    /* 0x10C */ s16 cutsceneId;
    /* 0x10E */ u8 unk10E;
    /* 0x10F */ s8 unk10F; // attached model bone (modelSlotBuildTransformMatrix), -1 = none
    /* 0x110 */ u8 attachMode;
    /* 0x111 */ u8 unk111[3];
    /* 0x114 */ ActorList *riderList;
    /* 0x118 */ struct PathFollowState *pathFollow;
    /* 0x11C */ struct Actor *parentActor;
    /* 0x120 */ f32 unk120;
    /* 0x124 */ void *spawnData;
    /* 0x128 */ s16 alpha;
    /* 0x12A */ s16 drawDistance;
    /* 0x12C */ s16 chunkIndex;
    /* 0x12E */ u8 pad12E;
    /* 0x12F */ u8 unk12F;
    /* 0x130 */ u8 cullMarginX;
    /* 0x131 */ u8 cullMarginY;
    /* 0x132 */ s16 interactionType;
    /* 0x134 */ s16 health;
    /* 0x136 */ s16 damage;
    /* 0x138 */ s32 callbackMask;
    /* 0x13C */ ActorCallbackNode *callbacks;
    /* 0x140 */ ActorSub140 *collision;
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 unk145;
    /* 0x146 */ s16 unk146;
    /* 0x148 */ void *unk148[2]; // per gfx buffer (renderActorEntryBuildDisplayList indexes gGfxBufferIndex)
    /* 0x150 */ struct CollisionStaticTri *floorTriangle;
    /* 0x154 */ u8 state;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 unk156;
    /* 0x157 */ u8 unk157;
    /* 0x158 */ AnimNode *animList;
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
    // Component pointers: actorAllocate stores one pointer per entry of the type's component
    // list (D_8074E218[type], 0 to 5 entries) from 0x174 on, the component data from the
    // next 8-byte boundary. 0x174 is the first component; 0x178, 0x17C... are pointers only
    // for types with that many components (for 1-component types 0x178 is already the
    // component's data), so they stay in per-type views { Actor base; T *unk178; ... }.
    /* 0x174 */ void *customState;
} Actor; // size = 0x178, the block actorAllocate gives a type with no components

typedef struct ZoneVertex {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} ZoneVertex;

typedef struct ZoneEntry {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 flags;
    /* 0x7 */ u8 radius;
    /* 0x8 */ u8 height;
    /* 0x9 */ u8 pad9;
} ZoneEntry; // size = 0xA

typedef struct Zone {
    /* 0x00 */ s16 minX;
    /* 0x02 */ s16 minZ;
    /* 0x04 */ s16 maxX;
    /* 0x06 */ s16 maxZ;
    /* 0x08 */ s16 vertexCount;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ ZoneVertex *vertices;
    /* 0x10 */ s16 entryCount;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ ZoneEntry *entries;
    /* 0x18 */ u8 id;
    /* 0x19 */ s8 unk19;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ Actor *occupant;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[3];
} Zone; // size = 0x24

// Map spawn node; a behaviour actor's gBehaviourAnimState and gBehaviourExtraState both point
// at its node (behaviourFrameBegin: both = gBehaviourWorkState->node).
typedef struct SpawnNode {
    /* 0x00 */ u8 baseEntryIndex;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ s16 yaw;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 z;
    /* 0x0A */ union {
        s16 unkAWide; // lh users (armadillo patrol, func_806B640C, func_806B7EA0, func_8072AA80)
        struct {
            u8 unkA;
            u8 unkB;
        };
    };
    /* 0x0C */ u8 targetSpeed;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 zoneId;
    /* 0x0F */ u8 scale;
    /* 0x10 */ u8 actorState;
    /* 0x11 */ u8 pathCount;
    /* 0x12 */ u8 initialState;
    /* 0x13 */ u8 id;
    /* 0x14 */ u8 respawnDelay;
    /* 0x15 */ u8 pad15[3];
    /* 0x18 */ Actor *actor;
    /* 0x1C */ Zone *zone;
    /* 0x20 */ u8 (*path)[2];
    /* 0x24 */ s16 respawnTimer;
    /* 0x26 */ s16 animId0;
    /* 0x28 */ s16 animId1;
    /* 0x2A */ s16 animId2;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 chunkIndex;
    /* 0x42 */ u8 state;
    /* 0x43 */ u8 spawnCount;
    /* 0x44 */ u8 entryIndex;
    /* 0x45 */ u8 pad45;
    /* 0x46 */ u16 flags;
} SpawnNode; // size = 0x48

// gBehaviourWorkState: actor component 31 (D_8074DA58[31] = 0x40), the first component of every
// actor type whose update calls behaviourFrameBegin.
typedef struct BehaviourWorkState {
    /* 0x00 */ SpawnNode *node;
    /* 0x04 */ Actor *unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 targetX;
    /* 0x0C */ s16 targetY;
    /* 0x0E */ s16 targetZ;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u16 stepCount;
    /* 0x1A */ u16 flags;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u32 unk28;
    /* 0x2C */ s16 timer;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 scale;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 pad3A[6];
} BehaviourWorkState; // size = 0x40

// gActivePlayerState: typedef only; other files still declare gActivePlayerState with their own types.
typedef struct PlayerState {
    /* 0x000 */ s16 prevState;
    /* 0x002 */ u8 pad2[2];
    /* 0x004 */ f32 maxSpeed;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ s16 targetYaw;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ s16 unkE;
    /* 0x010 */ s16 actionTimer;
    /* 0x012 */ s16 subTimer;
    /* 0x014 */ s16 pitchAngle;
    /* 0x016 */ s16 homingStrength;
    /* 0x018 */ s16 unk18;
    /* 0x01A */ u16 unk1A;
    /* 0x01C */ f32 slideSpeed;
    /* 0x020 */ f32 unk20;
    /* 0x024 */ s16 unk24;
    /* 0x026 */ s16 unk26;
    /* 0x028 */ s16 unk28;
    /* 0x02A */ u8 pad2A[2];
    /* 0x02C */ f32 airAccel;
    /* 0x030 */ f32 decelRate;
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 targetSpeed;
    /* 0x03C */ s16 airTimer;
    /* 0x03E */ s16 approachTimer;
    /* 0x040 */ s16 approachYaw;
    /* 0x042 */ u8 fallTimer;
    /* 0x043 */ u8 pad43[5];
    /* 0x048 */ s16 turnRate;
    /* 0x04A */ u8 pad4A[2];
    /* 0x04C */ s16 unk4C;
    /* 0x04E */ s16 unk4E;
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[2];
    /* 0x054 */ f32 jumpVelocityY;
    /* 0x058 */ s32 jumpTimer;
    /* 0x05C */ u32 jumpStartTime;
    /* 0x060 */ u32 unk60;
    /* 0x064 */ s16 unk64;
    /* 0x066 */ u8 pad66[2];
    /* 0x068 */ f32 slideLaunchSpeed;
    /* 0x06C */ f32 unk6C;
    /* 0x070 */ s16 unk70;
    /* 0x072 */ u8 pad72[2];
    /* 0x074 */ f32 unk74;
    /* 0x078 */ f32 unk78;
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ u8 pad82[2];
    /* 0x084 */ u32 unk84;
    /* 0x088 */ Actor *actor;
    /* 0x08C */ u8 gunDrawn;
    /* 0x08D */ u8 hitStatus;
    /* 0x08E */ u8 unk8E;
    /* 0x08F */ u8 unk8F;
    /* 0x090 */ u8 unk90;
    /* 0x091 */ u8 unk91;
    /* 0x092 */ u8 pad92[2];
    /* 0x094 */ f32 unk94;
    /* 0x098 */ f32 unk98;
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ f32 unkB0;
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ s16 hitActorType;
    /* 0x0BE */ s16 hitActorId;
    /* 0x0C0 */ s16 unkC0;
    /* 0x0C2 */ s16 unkC2;
    /* 0x0C4 */ struct GfSndState *sfxHandle;
    /* 0x0C8 */ s16 unkC8;
    /* 0x0CA */ u8 unkCA;
    /* 0x0CB */ u8 padCB;
    /* 0x0CC */ s16 unkCC;
    /* 0x0CE */ u8 padCE[2];
    /* 0x0D0 */ u32 unkD0;
    /* 0x0D4 */ s16 surfaceTimer;
    /* 0x0D6 */ s16 breathTimer;
    /* 0x0D8 */ u8 prevHasArcBounds;
    /* 0x0D9 */ u8 padD9[3];
    /* 0x0DC */ Actor *damageSource;
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ f32 unkE4;
    /* 0x0E8 */ u8 stateStep;
    /* 0x0E9 */ u8 padE9;
    /* 0x0EA */ s16 unkEA;
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ u8 padEE[2];
    /* 0x0F0 */ f32 unkF0;
    /* 0x0F4 */ f32 unkF4;
    /* 0x0F8 */ u8 unkF8;
    /* 0x0F9 */ u8 padF9[3];
    /* 0x0FC */ s32 invulnTimer;
    /* 0x100 */ s32 respawnTimer;
    /* 0x104 */ Actor *camActor;
    /* 0x108 */ f32 unk108;
    /* 0x10C */ s8 unk10C;
    /* 0x10D */ u8 pad10D;
    /* 0x10E */ s16 targetPitch;
    /* 0x110 */ s16 targetRoll;
    /* 0x112 */ s16 targetYawAngle;
    /* 0x114 */ s16 depthCenter;
    /* 0x116 */ s16 unk116;
    /* 0x118 */ s16 depthLeft;
    /* 0x11A */ s16 depthRight;
    /* 0x11C */ u8 unk11C;
    /* 0x11D */ u8 unk11D;
    /* 0x11E */ s16 unk11E;
    /* 0x120 */ s32 lastFrame;
    /* 0x124 */ f32 unk124;
    /* 0x128 */ f32 unk128;
    /* 0x12C */ u8 unk12C;
    /* 0x12D */ u8 pad12D[3];
    /* 0x130 */ Actor *pathOwner;
    /* 0x134 */ u8 pathIndex;
    /* 0x135 */ u8 pad135[3];
    /* 0x138 */ f32 pathDist;
    /* 0x13C */ f32 unk13C;
    /* 0x140 */ f32 unk140;
    /* 0x144 */ f32 unk144;
    /* 0x148 */ f32 unk148;
    /* 0x14C */ f32 unk14C;
    /* 0x150 */ f32 unk150;
    /* 0x154 */ s16 unk154;
    /* 0x156 */ u8 pad156[2];
    /* 0x158 */ Actor *unk158;
    /* 0x15C */ u8 unk15C[0x40];
    /* 0x19C */ s16 pathYawMin;
    /* 0x19E */ s16 pathYawMax;
    /* 0x1A0 */ u16 unk1A0;
    /* 0x1A2 */ u8 unk1A2;
    /* 0x1A3 */ u8 isHoldingObject;
    /* 0x1A4 */ u8 playerIndex;
    /* 0x1A5 */ u8 pad1A5[7];
    /* 0x1AC */ Actor *heldActor;
    /* 0x1B0 */ Actor *queuedHeldActor;
    /* 0x1B4 */ s32 queuedHeldActorId;
    /* 0x1B8 */ u16 heldActorType;
    /* 0x1BA */ u8 pad1BA[2];
    /* 0x1BC */ f32 holdPitch;
    /* 0x1C0 */ f32 targetScale[3];
    /* 0x1CC */ f32 currentScale[3];
    /* 0x1D8 */ f32 scaleChangeRate;
    /* 0x1DC */ f32 targetScaleFactor;
    /* 0x1E0 */ f32 scaleStep;
    /* 0x1E4 */ s32 scaleMode;
    /* 0x1E8 */ f32 unk1E8;
    /* 0x1EC */ u8 unk1EC;
    /* 0x1ED */ u8 pad1ED;
    /* 0x1EE */ s16 savedActorType;
    /* 0x1F0 */ s32 stateFlags;
    /* 0x1F4 */ s32 stateFlags2;
    /* 0x1F8 */ s32 prevStateFlags;
    /* 0x1FC */ u8 cartDamage;
    /* 0x1FD */ u8 unk1FD;
    /* 0x1FE */ u16 unk1FE;
    /* 0x200 */ s16 unk200;
    /* 0x202 */ u8 pad202[2];
    /* 0x204 */ f32 unk204;
    /* 0x208 */ f32 unk208;
    /* 0x20C */ f32 unk20C;
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ s16 unk21C;
    /* 0x21E */ u16 unk21E;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 savedX;
    /* 0x230 */ f32 savedY;
    /* 0x234 */ f32 savedZ;
    /* 0x238 */ f32 unk238;
    /* 0x23C */ u16 unk23C;
    /* 0x23E */ u8 sparkTimer;
    /* 0x23F */ u8 padHintTimer;
    /* 0x240 */ u8 unk240;
    /* 0x241 */ u8 pad241;
    /* 0x242 */ u16 unk242;
    /* 0x244 */ u8 idleTimeoutFlag;
    /* 0x245 */ u8 damageCooldown;
    /* 0x246 */ s8 hitSourceSpawnNodeId;
    /* 0x247 */ s8 hitSourcePlayerIndex;
    /* 0x248 */ s8 attackerPlayerIndex;
    /* 0x249 */ u8 attackerSpawnNodeId;
    /* 0x24A */ u8 attackTimer;
    /* 0x24B */ u8 pad24B;
    /* 0x24C */ u16 hitModelId;
    /* 0x24E */ u16 hitStrength;
    /* 0x250 */ s32 effectTimer;
    /* 0x254 */ void *effectObj;
    /* 0x258 */ f32 unk258;
    /* 0x25C */ f32 unk25C;
    /* 0x260 */ struct EffectNode *scoreEffect; // multiplayer score/crown effect (mpUpdateScoreEffects)
    /* 0x264 */ s32 unk264;
    /* 0x268 */ u8 transitionTimer;
    /* 0x269 */ u8 pad269[3];
} PlayerState;

// One kong's 0x5E-byte row of gPlayerInventoryTable (EEPROM fields 1-0xB; see 104F0.c).
// The table's declarations still differ per file; this is the row type, not a new extern.
typedef struct KongInventory {
    /* 0x00 */ u8 unk0[5];
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u16 unkA[14];
    /* 0x26 */ u16 unk26[14];
    /* 0x42 */ u16 unk42[14];
} KongInventory; /* sizeof 0x5E */

// One player's 0x306-byte block of gPlayerInventoryTable: eight kong rows, then the shared counters.
typedef struct PlayerInventory {
    /* 0x000 */ KongInventory kong[8];
    /* 0x2F0 */ s16 unk2F0;
    /* 0x2F2 */ s16 unk2F2;
    /* 0x2F4 */ s16 unk2F4;
    /* 0x2F6 */ s16 unk2F6;
    /* 0x2F8 */ s16 unk2F8;
    /* 0x2FA */ s8 unk2FA; // multiplayer: best total (health + healthDelta) so far
    /* 0x2FB */ s8 health; // melon pips left
    /* 0x2FC */ u8 melons; // melon count (health capacity = melons * per-melon)
    /* 0x2FD */ s8 healthDelta; // pending change, applied by healthApplyPendingDelta
    /* 0x2FE */ u16 kills[4]; // multiplayer: kills of each player
} PlayerInventory; // size = 0x306

// camSetTarget's parameter block inside CamState (0x44).
typedef struct CamTargetBlock {
    /* 0x00 */ struct Actor *unk0;
    /* 0x04 */ struct Actor *unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ f32 unk18;
} CamTargetBlock;

// customState of the camera actor (type 0xBC, component 4: 0x100 bytes, D_8074DA58[4]);
// reached as gCamActor->customState or PlayerState.camActor->customState.
typedef struct CamState {
    /* 0x00 */ struct Actor *unk0;
    /* 0x04 */ struct Actor *unk4;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[0x2];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ CamTargetBlock unk44;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ u8 pad64[0x8];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ u8 pad74[0x4];
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ f32 unk94;
    /* 0x98 */ f32 unk98;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ f32 unkA8;
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ u8 padB6[0x2];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ s16 unkBC;
    /* 0xBE */ u8 padBE[0x2];
    /* 0xC0 */ s32 unkC0;
    /* 0xC4 */ s16 unkC4;
    /* 0xC6 */ s16 unkC6;
    /* 0xC8 */ s16 unkC8;
    /* 0xCA */ s16 unkCA;
    /* 0xCC */ f32 unkCC;
    /* 0xD0 */ f32 unkD0;
    /* 0xD4 */ f32 unkD4;
    /* 0xD8 */ f32 unkD8;
    /* 0xDC */ f32 unkDC;
    /* 0xE0 */ f32 unkE0;
    /* 0xE4 */ f32 unkE4;
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ s16 unkEA;
    /* 0xEC */ u8 unkEC;
    /* 0xED */ u8 unkED;
    /* 0xEE */ u8 unkEE;
    /* 0xEF */ u8 unkEF;
    /* 0xF0 */ u8 unkF0;
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 unkF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 unkF4;
    /* 0xF5 */ u8 unkF5;
    /* 0xF6 */ u8 unkF6;
    /* 0xF7 */ u8 unkF7;
    /* 0xF8 */ u8 unkF8;
    /* 0xF9 */ u8 unkF9;
    /* 0xFA */ u8 unkFA;
    /* 0xFB */ u8 unkFB;
    /* 0xFC */ u8 unkFC;
    /* 0xFD */ u8 unkFD;
    /* 0xFE */ u8 padFE[0x1];
    /* 0xFF */ u8 unkFF;
} CamState; // size = 0x100

// Viewport layout entry (D_80750948[], cameraFindViewportEntry).
typedef struct G00Entry {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
} G00Entry;

// Spawn position (func_806C96C4).
typedef struct G01Pos {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
} G01Pos;

// Spawn request read by actorSpawnFromInfo (7CA80.c); spawnArg onward is passed to the type's init function.
typedef struct ActorSpawnInfo {
    s32 type;
    s32 spawnArg;
    s32 scriptId;
    f32 x;
    f32 y;
    f32 z;
    s16 yaw;
    s16 spawnTimer;
    void *spawnData;
} ActorSpawnInfo;

extern BehaviourWorkState *gBehaviourWorkState;
extern Actor *gBehaviourTargetActor;
extern SpawnNode *gBehaviourAnimState;
extern SpawnNode *gBehaviourExtraState;
extern Zone *D_807FDCA0; // gBehaviourAnimState->zone, latched by behaviourFrameBegin
extern ActorGlobalState gActorGlobalState;


// Collision/hit list passed to the 7AF60 interaction predicates (count @0xC, entries @0x10).
typedef struct ActorCollisionEntry {
    u8 pad0[0x14];
    s32 id;
    u8 pad18[4];
} ActorCollisionEntry; // size = 0x1C

typedef struct ActorCollisionList {
    u8 pad0[0xC];
    s32 count;
    ActorCollisionEntry *entries;
} ActorCollisionList;

#endif
