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
    /* 0x06 */ u16 frameDataOffset;       // advanced by 6 when the clip is loaded
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
    /* 0x48 */ f32 speed;                // playback speed, ramped from speedFrom to speedTo
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

// Head of the actor script asset (asset table 0xD, loaded by actorInit in 7CA80): byte offsets from the asset start
// of its sound, animation and index tables. actorScriptStart (19A00) reads script offsets as s32 words from the
// same start.
typedef struct ActorAssetHeader {
    /* 0x0 */ s32 pad0;
    /* 0x4 */ s32 soundTableOffset;
    /* 0x8 */ s32 animTableOffset;
    /* 0xC */ s32 indexTableOffset;
} ActorAssetHeader; // size = 0x10
extern ActorAssetHeader *gActorScriptAsset;

typedef struct ModelNode {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ s32 scaledX;
    /* 0x14 */ s32 scaledY;
    /* 0x18 */ s32 scaledZ;
    /* 0x1C */ s32 scaledRadius;
    /* 0x20 */ s32 mtxOffset;
    /* 0x24 */ u16 ignoredCollisionFlags;
    /* 0x26 */ u8 active;
    /* 0x27 */ u8 collisionSkipFlags;
    /* 0x28 */ struct ModelNode *next;
} ModelNode; // size = 0x2C

typedef struct ModelSubNode {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ s32 scaledX;
    /* 0x10 */ s32 scaledY;
    /* 0x14 */ s32 scaledZ;
    /* 0x18 */ s32 mtxOffset;
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
    /* 0x1C */ f32 pushTargetX; /* arc contact point x */
    /* 0x20 */ f32 pushTargetZ; /* arc contact point z */
    /* 0x24 */ u8 hasPushTarget;
    /* 0x25 */ u8 pad25;
    /* 0x26 */ s16 hitSlotId; // hit model entry id (actorBuildCollisionHit)
    /* 0x28 */ f32 hitTriX[3]; // hit triangle in the model's local space (x of the 3 vertices)
    /* 0x34 */ f32 hitTriY[3];
    /* 0x40 */ f32 hitTriZ[3];
    /* 0x4C */ f32 hitPosX; // actor position in the model's local space
    /* 0x50 */ f32 hitPosY;
    /* 0x54 */ f32 hitPosZ;
    /* 0x58 */ s16 hitBoxIndex; // hit box index in the slot's box table
    /* 0x5A */ s8 hitMtxIndex; // hit box bone
    /* 0x5B */ u8 pad5B;
    /* 0x5C */ s32 hitRadius;
    /* 0x60 */ s32 slotPushDist;
    /* 0x64 */ s16 maxPushDist;
    /* 0x66 */ s16 hitNormalYaw;
    /* 0x68 */ s32 actorPushDist;
    /* 0x6C */ u8 hasSlotHit;
    /* 0x6D */ u8 pad6D[3];
    /* 0x70 */ void *modelMtxF;
    /* 0x74 */ Mtx *nodeMtx[2]; /* per gfx buffer, indexed by gGfxBufferIndex */
    /* 0x7C */ s32 spheresFrame;
    /* 0x80 */ s32 posFrame;
    /* 0x84 */ s32 subNodesFrame;
    /* 0x88 */ s32 mtxFrame;
    /* 0x8C */ ModelNode *nodes;
    /* 0x90 */ ModelSubNode *subNodes;
    /* 0x94 */ s32 triangleCount;
    /* 0x98 */ void *triangles;
    /* 0x9C */ s32 boxCount;
    /* 0xA0 */ void *boxes;
    /* 0xA4 */ struct CollisionBox *box_start; /* transformed boxes (actorSub140BuildBoxes) */
    /* 0xA8 */ struct CollisionBox *box_end; /* one past the last valid box */
    /* 0xAC */ u8 unkAC;
    /* 0xAD */ u8 padAD[3];
    /* 0xB0 */ s32 boxContactX; // last box contact x/z (actorComputeBoxNormal)
    /* 0xB4 */ s32 boxContactZ;
    /* 0xB8 */ f32 hitBoxPosX; // actor position in the hit box's local space (actorCollisionReflectAndPush)
    /* 0xBC */ f32 hitBoxPosY;
    /* 0xC0 */ f32 hitBoxPosZ;
} ActorSub140; // size = 0xC4

// Animated-model asset header (controllerAnimStateLoadAsset relocates it, animListInit reads unk10).
typedef struct AnimInitData {
    /* 0x00 */ void *vertices;
    /* 0x04 */ void **displayLists; // pointer table; the first entry is the display list
    /* 0x08 */ void *bones;
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *animTextures; // s16 animation node list (animListInit)
    /* 0x14 */ struct ControllerSubNode *segmentNodes;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s16 height; // model height; actorCheckPlayerProximityVertical scales it by sub4->scaleY
    /* 0x1E */ u8 pad1E[2];
    /* 0x20 */ u8 boneCount;
    /* 0x21 */ u8 displayListCount;
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
    union {
        /* 0x04 */ u8 subtype;         // event node (actor->callbacks): the event's subtype argument (actorAllocCallbackNode, 7CA80.c)
        /* 0x04 */ u8 dispatchPass; // global callback node (actorRegisterGlobalCallback): 0 = after the current actor's
                                    // tick, 1 = after the frame's actor passes (actorGlobalCallbacksDispatchAndFree, 7CA80.c)
    };
    /* 0x05 */ u8 unk5[3];
    union {
        struct {
            /* 0x08 */ struct Actor *source;
            /* 0x0C */ s32 payloadCount;
            /* 0x10 */ void *payload;
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
    /* 0x08 */ s32 delay;
} ActorQueueEntry; // size = 0xC

typedef struct ActorEntry {
    /* 0x00 */ struct Actor *actor;
    /* 0x04 */ s32 unk4;
} ActorEntry; // size = 0x8

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
extern struct Actor *gCamActor; // camera actor (camera state in customState), defined in 201B0.c

typedef struct ActorCollisionHit {
    f32 pos[3];
    f32 verts[9];
    s32 mtxIndex;
    s32 hitRadius;
    s32 maxClamp;
    struct Actor *source;
} ActorCollisionHit; // size = 0x40

typedef struct ActorGlobalState {
    /* 0x000 */ u8 notifyReceived; // set by actorDispatchCallbacks for a 0x2000000 callback; cleared by actorGlobalStateClearEvents
    /* 0x001 */ u8 notifyValue[1]; // its subtype (A2F10 sends 1 to attached children, 936B0 0); a plain u8 changes C8C10 registers
    /* 0x002 */ u8 eventReceived;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ f32 eventX;
    /* 0x008 */ f32 eventY;
    /* 0x00C */ f32 eventZ;
    /* 0x010 */ s16 eventValue0;
    /* 0x012 */ s16 eventValue1;
    /* 0x014 */ u8 eventSubtype;
    /* 0x015 */ u8 damaged;
    /* 0x016 */ u8 unk16;
    /* 0x017 */ u8 unk17;
    /* 0x018 */ u8 unk18;
    /* 0x019 */ u8 unk19;
    /* 0x01A */ u8 playerLaunchReceived;
    /* 0x01B */ u8 unk1B;
    /* 0x01C */ u8 unk1C;
    /* 0x01D */ u8 unk1D[3];
    /* 0x020 */ struct Actor *unk20;
    /* 0x024 */ u8 pickupReceived;
    /* 0x025 */ u8 releaseReceived;
    /* 0x026 */ u8 unk26[2];
    /* 0x028 */ struct Actor *holderActor;
    /* 0x02C */ u8 launchReceived;
    /* 0x02D */ u8 unk2D[3];
    /* 0x030 */ f32 launchSpeedY;
    /* 0x034 */ s16 launchSpeedXZ;
    /* 0x036 */ s16 launchYaw;
    /* 0x038 */ u8 childFreed;
    /* 0x039 */ u8 riderCount;
    /* 0x03A */ u8 unk3A[2];
    /* 0x03C */ f32 riderPoints[4][3];
    /* 0x06C */ s32 riderMtxOffsets[4];
    /* 0x07C */ struct Actor *riderActors[4];
    /* 0x08C */ u8 riderSpansNodes[4];
    /* 0x090 */ u8 collisionModeReceived;
    /* 0x091 */ u8 surfaceHitReceived;
    /* 0x092 */ s16 surfaceHitYaw;
    /* 0x094 */ s16 surfaceHitSpeed;
    /* 0x096 */ u8 unk96[2];
    /* 0x098 */ f32 surfaceHitPos[3];   // surface hit payload copy (12 bytes, from payload +0x4)
    /* 0x0A4 */ f32 surfaceHitVerts[9];  // surface hit payload copy (0x24 bytes, from payload +0x10)
    /* 0x0C8 */ s32 surfaceHitMtxIndex;
    /* 0x0CC */ struct Actor *surfaceHitActor;
    /* 0x0D0 */ s32 surfaceHitRadius;
    /* 0x0D4 */ s32 surfaceHitMaxClamp;
    /* 0x0D8 */ f32 destPointX;
    /* 0x0DC */ f32 destPointY;
    /* 0x0E0 */ f32 destPointZ;
    /* 0x0E4 */ u8 destPointReceived;
    /* 0x0E5 */ u8 forcedContactReceived;
    /* 0x0E6 */ u8 unkE6[2];
    /* 0x0E8 */ f32 forcedContactSpeed;
    /* 0x0EC */ struct Actor *destPointSource;
    /* 0x0F0 */ f32 heldAlignPitch;
    /* 0x0F4 */ f32 heldAlignYaw;
    /* 0x0F8 */ ActorCollisionHit collisionHits[4];
    /* 0x1F8 */ s32 collisionHitCount;
    /* 0x1FC */ struct Actor *targetActor;
    /* 0x200 */ u8 bossFightPhase;
    /* 0x201 */ u8 collisionEventCount;
    /* 0x202 */ u8 unk202[2];
    /* 0x204 */ struct Actor *collisionEventActors[16];
    /* 0x244 */ u8 collisionEvents[16];
    /* 0x254 */ u8 volumeTriggerQueueCount;
    /* 0x255 */ u8 unk255[3];
    /* 0x258 */ s32 volumeTriggerQueueOp[8];
    /* 0x278 */ s16 *volumeTriggerQueueId[8];
} ActorGlobalState;

// Path-follow state (Actor.floorContact; pathFollowUpdateHeading allocates it, actor teardown frees it); 0x14 bytes.
typedef struct PathFollowState {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 point;
    /* 0x08 */ f32 pointFrac;
    /* 0x0C */ u8 done;
    /* 0x0D */ u8 padD;
    /* 0x0E */ s16 yaw;
    /* 0x10 */ s16 speed;
    /* 0x12 */ s16 pathId;
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
    union {
        /* 0x072 */ s16 soundTimer;       // sound frame timer: counts up while sound 0x131 plays (its pitch, 7130.c), down holding 0x130 (race/36B0.c)
        /* 0x072 */ s16 soundAnimId; // anim id slot 0's script sound is bound to, stopped when the anim changes (19A00.c, 7130.c)
    };
    /* 0x074 */ f32 soundVolume;
    /* 0x078 */ u8 floorTriSurface[4];
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
    /* 0x0A8 */ f32 meshFloorY;
    /* 0x0AC */ f32 waterY;
    /* 0x0B0 */ s8 waterPathId[4];
    /* 0x0B4 */ f32 distToFloor;
    /* 0x0B8 */ f32 speedXZ;
    /* 0x0BC */ f32 prevSpeedXZ;
    /* 0x0C0 */ f32 speedY;
    /* 0x0C4 */ f32 accelY;
    /* 0x0C8 */ f32 terminalSpeedY;
    /* 0x0CC */ u8 floorNodeId;
    /* 0x0CD */ u8 lightNodeId;
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
    /* 0x0EA */ s16 targetYaw;
    union {
        struct {
            union {
                /* 0x0EC */ s16 unkEC;      // per-type scratch (the uses below span 2+ functions; the rest stay here)
                /* 0x0EC */ s16 arrowAngle; // screen angle in degrees of the hint arrows actorDrawAnimatedEffect draws (90D80.c;
                                            // written by C8C10.c, 9DD70.c, A6280.c, race/A960.c)
                /* 0x0EC */ s16 lastRoll;   // camera actor: the pitch (up-vector roll) applied last frame, read as skyRoll (201B0.c, 8F4B0.c)
                /* 0x0EC */ s16 alphaStep;  // flying enemy: alpha fade step per frame, random 15..21 (B7490.c swoop/return)
                /* 0x0EC */ s16 sideAngle;  // minecart type 0x11C escort: side offset angle, times yawSpeed = -1/+1 (minecart/25F0.c)
            };
            /* 0x0EE */ s16 moveYaw;
        };
        /* 0x0EC */ u32 animLastFrame; // currentActorAnimTryIdleVariant frame cursor (actorSparkCutsceneUpdate, A6280.c)
    };
    /* 0x0F0 */ s16 movePitch;
    /* 0x0F2 */ s16 arcMoveYaw;
    /* 0x0F4 */ s16 arcYawMin;
    /* 0x0F6 */ s16 arcYawMax;
    /* 0x0F8 */ s16 arcSpeedCapMax;
    /* 0x0FA */ s16 arcSpeedCap;
    /* 0x0FC */ u8 hasArcBounds;
    /* 0x0FD */ u8 collisionHit;
    /* 0x0FE */ u8 padFE[2];
    /* 0x100 */ f32 attachLocalX; // attach point in the model node's local space (collisionAttachActorToObjectNode)
    /* 0x104 */ f32 attachLocalY;
    /* 0x108 */ f32 attachLocalZ;
    /* 0x10C */ s16 cutsceneId;
    /* 0x10E */ u8 unk10E;
    /* 0x10F */ s8 unk10F; // attached model bone (modelSlotBuildTransformMatrix), -1 = none
    /* 0x110 */ u8 attachMode;
    /* 0x111 */ u8 unk111[3];
    /* 0x114 */ ActorList *riderList;
    /* 0x118 */ struct PathFollowState *pathFollow;
    /* 0x11C */ struct Actor *parentActor;
    /* 0x120 */ f32 collisionScaleOverride;
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
    /* 0x144 */ u8 collisionMode;
    /* 0x145 */ u8 unk145;
    /* 0x146 */ s16 segmentFlags;
    /* 0x148 */ void *unk148[2]; // per gfx buffer (renderActorEntryBuildDisplayList indexes gGfxBufferIndex)
    /* 0x150 */ struct CollisionStaticTri *floorTriangle;
    /* 0x154 */ u8 state;
    union {
        /* 0x155 */ u8 subState;         // step / in-state counter of `state`, reset with every state change
        /* 0x155 */ u8 projectileKind; // type 0x116: ProjectileConfig.type, read by playerHandleDamageReaction (7CA80.c)
        /* 0x155 */ u8 menuCharacter;  // type 0x151: selected character index (menuCharacterSelectUpdateActor, 3E10.c)
        /* 0x155 */ u8 optionCursor;   // type 0x157: highlighted option, 2 = quit chosen (hudTwoOptionMenuUpdate, ACDC0.c)
        /* 0x155 */ u8 counterValue;   // type 0x58: number shown by textUpdateTwoDigitCounter (9DD70.c)
    };
    /* 0x156 */ u8 mirrorCount;
    /* 0x157 */ u8 unk157;
    /* 0x158 */ AnimNode *animList;
    /* 0x15C */ s16 spawnTimer;
    /* 0x15E */ u8 eyeHeight;
    union {
        /* 0x15F */ u8 unk15F;        // per-type scratch byte (the uses below span 2+ functions; the rest stay here)
        /* 0x15F */ u8 fadeValue;     // 0..0xFF level ramped in/out: text marker (9DD70.c), options menu (menu/0.c),
                                      // shop cost prompt (menu/1AF0.c), menu light (menu/E550.c)
        /* 0x15F */ u8 orbitGlow;     // tag-barrel kong highlight 3..15, copied into tintA (80150.c)
        /* 0x15F */ u8 ringCountdown; // type 0x107 sprite ring: rings (or frames) left, nonzero = hurts (936B0.c, 9BF30.c)
        /* 0x15F */ u8 wavesLeft;     // type 0x102 shockwave: generations still to spawn (936B0.c, A2F10.c)
        /* 0x15F */ u8 targetNumber;  // numbered targets: spawner's expected number, each target's own (C8C10.c, 9DD70.c)
        /* 0x15F */ u8 sequenceIndex; // next entry of the D_807506C0 actor sequence (C2A90.c, A6280.c)
        /* 0x15F */ u8 followerCount; // minecart follower spawner: followers alive (minecart/25F0.c)
        /* 0x15F */ u8 savedYaw;      // camera actor: orbit yaw in 1/255 turns for the next reset (201B0.c, CC800.c)
        /* 0x15F */ u8 stageStatus;   // K. Rool Tiny phase boss/minions: 1 = active, 2 = done (boss/B100.c)
        /* 0x15F */ u8 dropMode;      // bouncing drops: 1 = not collectable on the first bounce, 2 = never expires (AA960.c)
        /* 0x15F */ u8 timerMode;     // type 0xB0 countdown timer: 6 = seconds only, 0xB = mm:ss:hh, also runs on camera paths (A7710.c)
        /* 0x15F */ u8 textScreenId;  // type 0x156 text screen: which screen, picks the button actions (ACDC0.c)
        /* 0x15F */ u8 reelSymbol;    // bonus slot reel: symbol index under the payline (bonus/12A0.c)
        /* 0x15F */ u8 bannerId;      // type 0x104 banner: text / sprite / round number to show (A2F10.c, 1295B0.c)
        /* 0x15F */ u8 formationIndex; // type 0x94 group: 0 = leader, 1..11 children, group = index / 3 (A2F10.c)
        /* 0x15F */ u8 debrisUpright; // type 0xED tumble debris: nonzero = drawn upright, 0 = flipped (B2CE0.c)
    };
    union {
        /* 0x160 */ f64 splineT;
        /* 0x160 */ u32 frameCursor; // currentActorAnimTryIdleVariant frame cursor (critterFlutterFlyUpdate, 3340.c)
    };
    /* 0x168 */ s16 yawSpeed;
    /* 0x16A */ u8 tintR;
    /* 0x16B */ u8 tintG;
    /* 0x16C */ u8 tintB;
    /* 0x16D */ u8 tintA;
    /* 0x16E */ u8 shadowScale[6];
    // Component pointers: actorAllocate stores one pointer per entry of the type's component
    // list (gActorTypeComponents[type], 0 to 5 entries) from 0x174 on, the component data from the
    // next 8-byte boundary. 0x174 is the first component; 0x178, 0x17C... are pointers only
    // for types with that many components (for 1-component types 0x178 is already the
    // component's data), so they stay in per-type views { Actor base; T *unk178; ... }.
    /* 0x174 */ void *customState;
} Actor; // size = 0x178, the block actorAllocate gives a type with no components

// Second component (Actor 0x178) of the pulsing actor types: actorUpdatePulseIntensity (BB300) ramps the light
// intensity through phase; behaviourPulseEnemyUpdate (BB300) keeps a yaw sway there. Reached through per-type views
// { Actor base; PulseState *pulse; } (A6280, BB300).
typedef struct PulseState {
    /* 0x0 */ u8 intensity;
    /* 0x1 */ u8 phase;
    /* 0x2 */ s16 yawSway; // +-0x8C on a sharp turn, added to yaw and decayed by 1% per frame
} PulseState;

// customState of the drop-and-bounce pickups: actorDropBounceExpireUpdate (AA960) counts the bounces, sets
// collectable on landing and flagId from the spawn data; gridCollectActorsInRange (F9450) passes flagId to
// flagTempRegister. sprite is the attached EffectNode (effectSpawnAttachedSprite).
typedef struct DropBounceState {
    /* 0x0 */ u8 bounceCount;
    /* 0x1 */ u8 collectable;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ struct EffectNode *sprite;
    /* 0x8 */ u16 expireTimer;
    /* 0xA */ s16 flagId;
} DropBounceState; // size = 0xC

// Third component (Actor 0x17C) of the scripted actors (C4620.c behaviours; cutscene commands 0x33, 0x34
// and 0x3C address it in camPathCommandDispatch, 2C910.c).
typedef struct ScriptedActorState {
    /* 0x00 */ u16 animAssetId; // controllerAnimInit asset; also selects the kind's behaviour
    /* 0x02 */ s16 yawFrom;
    /* 0x04 */ s16 yawTo;
    /* 0x06 */ s16 pitchFrom;
    /* 0x08 */ s16 pitchTo;
    /* 0x0A */ s16 rollFrom;
    union {
        /* 0x0C */ s16 rollTo;
        struct {
            /* 0x0C */ u8 rollToHi;
            /* 0x0D */ u8 rollToLo; // cutscene command 0x3C ORs into this byte (lbu/sb 13, 2C910)
        };
    };
    /* 0x0E */ s16 zoneTo;
    /* 0x10 */ s16 zoneFrom;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ f32 scaleFrom;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u16 lerpSteps;
    /* 0x1E */ u16 lerpTimer;
    /* 0x20 */ u8 pad20[2];
    /* 0x22 */ u8 particleScalePct;
    /* 0x23 */ u8 yawSteps;
    /* 0x24 */ u8 yawTimer;
    /* 0x25 */ u8 pitchSteps;
    /* 0x26 */ u8 pitchTimer;
    /* 0x27 */ u8 rollSteps;
    /* 0x28 */ u8 rollTimer;
    /* 0x29 */ u8 scaleSteps;
    /* 0x2A */ u8 scaleTimer;
    /* 0x2B */ u8 pad2B;
    /* 0x2C */ u8 anchorNode;
    /* 0x2D */ u8 pathId;
    /* 0x2E */ u8 pathSpeed;
    /* 0x2F */ u8 pathPlayback;
    /* 0x30 */ u8 particlePath;
    /* 0x31 */ u8 particleCount;
    /* 0x32 */ u8 particleColor;
    /* 0x33 */ u8 particleSprite;
} ScriptedActorState; // size = 0x34

typedef struct ScriptedActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ void *chains;
    /* 0x17C */ ScriptedActorState *scriptState;
} ScriptedActor;

// One damped spring of a kong chain node (F56F0 steps it: playerWeaponCalculateTrajectory24).
typedef struct KongSpring {
    /* 0x0 */ f32 offset; // rest angle: the per-kind table value, mirrored for the second chain
    /* 0x4 */ f32 angle;
    /* 0x8 */ f32 velocity;
} KongSpring;

typedef struct KongChainNode {
    /* 0x00 */ KongSpring springX;
    /* 0x0C */ KongSpring springY;
} KongChainNode;

// Kong actor second component (Actor 0x178), filled by kongChainInit (CC800) per kind: DK (2) one chain of
// 4 nodes, Diddy (3) one of 11, Tiny (5) two mirrored chains of 8; F56F0 steps it.
typedef struct KongChain {
    /* 0x000 */ f32 prevAngle;
    /* 0x004 */ f32 prevY;
    /* 0x008 */ f32 prevVelY;
    /* 0x00C */ f32 sway;
    /* 0x010 */ f32 weight;
    /* 0x014 */ u8 holdTimer;
    /* 0x015 */ u8 pad15[3];
    /* 0x018 */ s32 kind; // the kong's actor type
    /* 0x01C */ KongChainNode nodes[12];
} KongChain; // size = 0x13C

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
    /* 0x19 */ u8 floorQueryMode;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ Actor *occupant;
    /* 0x20 */ u8 attachedCount;
    /* 0x21 */ u8 pad21[3];
} Zone; // size = 0x24

// The map's zone table (gZoneTable): count + array of Zone (1295B0.c, C2A90.c).
typedef struct ZoneTable {
    /* 0x0 */ s16 count;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ Zone *zones;
} ZoneTable;

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
        s16 unkAWide; // lh users (armadillo patrol, explodingChaserUpdate, actorUpdateLockOnCursor, behaviourPickRandomTargetY)
        struct {
            u8 unkA;
            u8 unkB;
        };
        u8 attachNode; // zone-occupant model node to ride, 0 = none (behaviourAttachToZoneOccupant, behaviourRockingWalk, behaviourFairyIdle1-3, BDEE0.c)
        struct {
            u8 targetCount; // bonus: items to collect (bonusControllerUpdate, bonus/0.c)
            u8 timeLimit;   // bonus: hudSpawnCountdownTimer seconds (bonusControllerUpdate, bonusMazeChallengeUpdate, bonus/0.c)
        };
        struct {
            u8 hoverHeight; // fly patrol: seeds FlyPatrolComponent.hoverHeight (behaviourFlyPatrolWithCallback, actorAirPatrolStep, B7490.c)
            u8 climbRate;   // fly patrol: y += climbRate / 32 (or / 64) per frame below the hover height; 0 -> 0x28 (same functions)
        };
        struct {
            u8 burstLength;   // emitters: frames (shots) per burst, loaded into timer (actorUpdatePeriodicParticleEmitter, actorUpdateAimedProjectileEmitter, actorUpdateBurstProjectileEmitter, BC3B0.c)
            u8 burstInterval; // emitters: frames between bursts (same functions)
        };
    };
    /* 0x0C */ u8 targetSpeed;
    union {
        /* 0x0D */ u8 chaseSpeed;            // run/chase speed (actorSetTargetSpeed, behaviourSetChaseState, speedXZ users)
        /* 0x0D */ u8 burstStartDelay; // burst emitter: frames before the first burst (actorUpdateBurstProjectileEmitter, BC3B0.c)
    };
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
    /* 0x2C */ f32 turnAnimScale;
    /* 0x30 */ f32 shadowScale;
    /* 0x34 */ f32 nearTurnSpeedScale;
    /* 0x38 */ f32 animSpeedScale;
    /* 0x3C */ f32 minAnimSpeed;
    /* 0x40 */ s16 chunkIndex;
    /* 0x42 */ u8 state;
    /* 0x43 */ u8 spawnCount;
    /* 0x44 */ u8 entryIndex;
    /* 0x45 */ u8 pad45;
    /* 0x46 */ u16 flags;
} SpawnNode; // size = 0x48

// The map's spawn node list (gSpawnNodeList): count + array of SpawnNode (1295B0.c).
typedef struct SpawnNodeList {
    /* 0x0 */ s16 count;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ SpawnNode *nodes;
} SpawnNodeList;

// One 0x18-byte row of the spawn table gSpawnEntryTable, indexed by SpawnNode.entryIndex
// (spawnNodeInitActorFromEntry and the spawn paths in 1295B0.c; behaviourUpdateShadowAlpha in 12E800.c).
typedef struct SpawnEntry {
    /* 0x00 */ u16 actorType;
    /* 0x02 */ u16 spawnArg;
    /* 0x04 */ s16 scriptId;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ u32 actorFlags;
    /* 0x0C */ u8 headYawLimit;
    /* 0x0D */ u8 headPitchMinDist;
    /* 0x0E */ u8 spawnRange;
    /* 0x0F */ u8 wanderInterval;
    /* 0x10 */ u8 turnRate;
    /* 0x11 */ u8 moveYawRate;
    /* 0x12 */ u8 wanderDegrees;
    /* 0x13 */ u8 acceleration;
    /* 0x14 */ u8 shadowScaleX; // shadow billboard width scale (behaviourUpdateShadowAlpha); copied to Actor.unk16E[0]
    /* 0x15 */ u8 shadowScaleZ; // shadow billboard depth scale; copied to Actor.unk16E[1]
    /* 0x16 */ u8 engageState;
    /* 0x17 */ u8 animSpeedDivisor;
} SpawnEntry; // size = 0x18

// gBehaviourWorkState: actor component 31 (gActorComponentSizes[31] = 0x40), the first component of every
// actor type whose update calls behaviourFrameBegin.
typedef struct BehaviourWorkState {
    /* 0x00 */ SpawnNode *node;
    /* 0x04 */ Actor *targetActor; // behaviourFrameBegin copies it to gBehaviourTargetActor
    /* 0x08 */ s16 targetYaw; // yaw actorTurnTowardTarget eases toward
    /* 0x0A */ s16 targetX;
    /* 0x0C */ s16 targetY;
    /* 0x0E */ s16 targetZ;
    /* 0x10 */ s16 lastValidX; // spawn position, then the last position inside the zone (restored on leaving it)
    /* 0x12 */ s16 lastValidY;
    /* 0x14 */ s16 lastValidZ;
    /* 0x16 */ s16 targetAnimId; // target model animId when last synced (behaviourFrameBegin)
    /* 0x18 */ u16 stepCount;
    /* 0x1A */ u16 flags;
    /* 0x1C */ u16 prevFlags; // flags before the current zone update
    /* 0x1E */ u8 turnRate; // SpawnEntry.turnRate
    /* 0x1F */ u8 moveYawRate; // SpawnEntry.moveYawRate
    union {
        /* 0x20 */ u8 searchTimer;       // chase countdown: reachable-point retry cooldown, state 0x35 search time (behaviourCheckTargetCollisionMode, enemyAggroStateUpdate, 12E800.c)
        /* 0x20 */ u8 stuckFrames; // patrol: +2 per frame while x/z do not move, > 0x10 forces the waypoint reached (patrolPathStep, 12E800.c)
    };
    /* 0x21 */ u8 wanderDegrees; // SpawnEntry.wanderDegrees
    /* 0x22 */ u8 wanderTimer; // counts down to the next wander turn
    /* 0x23 */ u8 wanderInterval; // SpawnEntry.wanderInterval
    union {
        /* 0x24 */ u8 wanderAngle; // random 0..179, in 2-degree steps
        /* 0x24 */ u8 routeRow; // race opponents: current route row (race/0.c)
    };
    /* 0x25 */ u8 waypointIndex; // current zone entry / path step (bit 7: direction in 12E800)
    /* 0x26 */ s16 targetSpeed;
    union {
        /* 0x28 */ u32 idleAnimFrame; // gFrameCounter when the idle variant last played (currentActorAnimTryIdleVariant)
        /* 0x28 */ u32 animBounceState; // boss/8520.c: packed anim frame (& 0xF), direction bit 0x80, flag 0x8000
    };
    /* 0x2C */ s16 timer;
    union {
        /* 0x2E */ s16 countdown;       // countdown: set, decremented to 0 (BC3B0.c, BDEE0.c, C2A90.c, C8C10.c, CB230.c, race/0.c, boss/9230.c)
        /* 0x2E */ s16 riseSpeed;   // Army Dillo rocket rise: +10/+4 per frame, capped 0x12C, copied to speedY (bossArmydilloStep, boss/0.c)
        /* 0x2E */ s16 spinSpeed;   // Mad Jack state 0x46: signed yaw step, eased by +-2 within +-0x32 (bossMadJackStep, boss/52B0.c)
        /* 0x2E */ s16 emergeDepth; // state 0x36 emerge: distance below the node the rise starts from (behaviourUpdateContactAndState, 12E800.c)
    };
    /* 0x30 */ f32 scale;
    /* 0x34 */ u8 lastMoveTier; // playerSelectMoveTier result last applied (0xFF = none)
    /* 0x35 */ u8 acceleration; // SpawnEntry.acceleration
    /* 0x36 */ u8 chaseState;
    /* 0x37 */ u8 engageState; // SpawnEntry.engageState
    /* 0x38 */ u8 stationaryFrames;
    /* 0x39 */ u8 emergeTimer;
    /* 0x3A */ u8 pad3A[6];
} BehaviourWorkState; // size = 0x40

// gActivePlayerState: typedef only; other files still declare gActivePlayerState with their own types.
typedef struct PlayerState {
    /* 0x000 */ s16 prevState;
    /* 0x002 */ u8 pad2[2];
    /* 0x004 */ f32 maxSpeed;
    /* 0x008 */ s16 moveDir;
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
    /* 0x024 */ s16 swimFrames;
    /* 0x026 */ s16 traction;
    /* 0x028 */ s16 sharpTurn;
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
    /* 0x04C */ s16 moveTier;
    /* 0x04E */ s16 animIndex;
    union {
        /* 0x050 */ s16 gravityDelay;     // air states: frames playerApplyGravity holds gravity off (CEAE0.c; set in EFDC0.c/E4090.c)
        /* 0x050 */ s16 idleDelay; // swim states 0x7F/0x4F: frames still before the idle animation (D5E10.c; playerWarpToSpawnPoint, CC800.c)
    };
    /* 0x052 */ u8 pad52[2];
    /* 0x054 */ f32 jumpVelocityY;
    /* 0x058 */ s32 jumpTimer;
    /* 0x05C */ u32 jumpStartTime;
    /* 0x060 */ u32 lastZPressTick;
    /* 0x064 */ s16 unk64;
    /* 0x066 */ u8 pad66[2];
    /* 0x068 */ f32 slideLaunchSpeed;
    /* 0x06C */ f32 launchSpeedXZ;
    /* 0x070 */ s16 launchYaw;
    /* 0x072 */ u8 pad72[2];
    /* 0x074 */ f32 launchSpeedY;
    /* 0x078 */ f32 unk78;
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ u8 pad82[2];
    /* 0x084 */ u32 unk84;
    /* 0x088 */ Actor *actor;
    /* 0x08C */ u8 gunDrawn;
    /* 0x08D */ u8 hitStatus;
    /* 0x08E */ u8 recoilTimer;
    /* 0x08F */ u8 recentShotCount;
    /* 0x090 */ u8 gunHand;
    /* 0x091 */ u8 lastFireHand;
    /* 0x092 */ u8 pad92[2];
    /* 0x094 */ f32 forwardSpeed;
    /* 0x098 */ f32 unk98;
    /* 0x09C */ f32 walkStartX;
    /* 0x0A0 */ f32 walkStartZ;
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ f32 walkProgress;
    /* 0x0B0 */ f32 launchTargetX;
    /* 0x0B4 */ f32 launchTargetY;
    /* 0x0B8 */ f32 launchTargetZ;
    /* 0x0BC */ s16 hitActorType;
    /* 0x0BE */ s16 hitActorId;
    /* 0x0C0 */ s16 unkC0;
    union {
        /* 0x0C2 */ s16 slopeFrames;    // frames on a slope, >= 0x15 slides (playerUpdateSlopeSlidePhysics, CEAE0.c)
        /* 0x0C2 */ s16 rideSpin; // state 0x38: spin added to the ridden actor, decays by 7 (playerStateRidingActor, D5E10.c; EFDC0.c)
    };
    /* 0x0C4 */ struct GfSndState *sfxHandle;
    /* 0x0C8 */ s16 chargeTimer;
    /* 0x0CA */ u8 barrelCooldown;
    /* 0x0CB */ u8 padCB;
    /* 0x0CC */ s16 tumblePhase;
    /* 0x0CE */ u8 padCE[2];
    /* 0x0D0 */ u32 unkD0;
    /* 0x0D4 */ s16 surfaceTimer;
    /* 0x0D6 */ s16 breathTimer;
    /* 0x0D8 */ u8 prevHasArcBounds;
    /* 0x0D9 */ u8 padD9[3];
    /* 0x0DC */ Actor *damageSource;
    /* 0x0E0 */ f32 wallContactX;
    /* 0x0E4 */ f32 wallContactZ;
    /* 0x0E8 */ u8 stateStep;
    /* 0x0E9 */ u8 padE9;
    /* 0x0EA */ s16 wallNormalYaw;
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ u8 padEE[2];
    /* 0x0F0 */ f32 ledgeY;
    /* 0x0F4 */ f32 prevLedgeY;
    /* 0x0F8 */ u8 hangInputDelay;
    /* 0x0F9 */ u8 padF9[3];
    /* 0x0FC */ s32 invulnTimer;
    /* 0x100 */ s32 respawnTimer;
    /* 0x104 */ Actor *camActor;
    union {
        /* 0x108 */ f32 tumbleTimer;     // frame countdown per tumble phase (playerStateKnockbackTumble, D5E10.c)
        /* 0x108 */ f32 wiggleSide; // last stick side, 0.0f/1.0f (playerInputWiggleOffStatusEffect, E4090.c)
    };
    /* 0x10C */ s8 ledgeHangOffset;
    /* 0x10D */ u8 pad10D;
    /* 0x10E */ s16 targetPitch;
    /* 0x110 */ s16 targetRoll;
    /* 0x112 */ s16 targetYawAngle;
    /* 0x114 */ s16 depthCenter;
    /* 0x116 */ s16 unk116;
    /* 0x118 */ s16 depthLeft;
    /* 0x11A */ s16 depthRight;
    /* 0x11C */ u8 stateTimer;
    /* 0x11D */ u8 swimStrokeTriggered;
    /* 0x11E */ s16 animThresholdIndex;
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
    /* 0x148 */ f32 pathAttachBlend;
    /* 0x14C */ f32 unk14C;
    /* 0x150 */ f32 unk150;
    /* 0x154 */ s16 leapYaw;
    /* 0x156 */ u8 pad156[2];
    /* 0x158 */ Actor *leapTarget;
    /* 0x15C */ f32 unk15C[4][4];
    /* 0x19C */ s16 pathYawMin;
    /* 0x19E */ s16 pathYawMax;
    /* 0x1A0 */ u16 aimPitch;
    /* 0x1A2 */ u8 unk1A2;
    /* 0x1A3 */ u8 isHoldingObject;
    /* 0x1A4 */ u8 playerIndex;
    /* 0x1A5 */ u8 pad1A5[3];
    /* 0x1A8 */ Actor *countdownTimer;
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
    /* 0x1E8 */ f32 underwaterTint;
    /* 0x1EC */ u8 photoSubjectStatus;
    /* 0x1ED */ u8 pad1ED;
    /* 0x1EE */ s16 savedActorType;
    /* 0x1F0 */ s32 stateFlags;
    /* 0x1F4 */ s32 stateFlags2;
    /* 0x1F8 */ s32 prevStateFlags;
    /* 0x1FC */ u8 cartDamage;
    /* 0x1FD */ u8 unk1FD;
    /* 0x1FE */ u16 transformTimer;
    /* 0x200 */ s16 statusEffectTimer;
    /* 0x202 */ u8 pad202[2];
    /* 0x204 */ f32 warpX;
    /* 0x208 */ f32 warpY;
    /* 0x20C */ f32 warpZ;
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ s16 unk21C;
    /* 0x21E */ u16 fadeLevel;
    union {
        /* 0x220 */ f32 heading[3];    // cutscene spark heading: [0] sine, [1] angle (s16 yaw as a float), [2] cosine (csCmdCameraVectorTargetUpdate, 478F0.c; func_806DF280, D5E10.c)
        /* 0x220 */ f32 targetPos[3]; // target point from the B-press event (playerInputCheckBButtonTarget, E4090.c; playerStateThrowCarried, D5E10.c)
    };
    /* 0x22C */ f32 savedX;
    /* 0x230 */ f32 savedY;
    /* 0x234 */ f32 savedZ;
    /* 0x238 */ f32 floatBaseY;
    union {
        /* 0x23C */ u16 stateCountdown;    // frame countdown ending a state step (D5E10.c death/tag-barrel states; EFDC0.c, E4090.c)
        /* 0x23C */ u16 rampLevel; // ramped magnitude: sparkle spin (playerStateTransformSparkles), model scale (playerStateStationaryInteraction), D5E10.c
        /* 0x23C */ u16 bobPhase;  // sine angle of the Y bob (playerStatePonytailFloat, D5E10.c)
    };
    /* 0x23E */ u8 sparkTimer;
    /* 0x23F */ u8 padHintTimer;
    /* 0x240 */ u8 attachmentExitTimer;
    /* 0x241 */ u8 pad241;
    /* 0x242 */ u16 unk242;
    /* 0x244 */ u8 idleTimeoutFlag;
    /* 0x245 */ u8 damageCooldown;
    /* 0x246 */ s8 hitSourceSpawnNodeId;
    /* 0x247 */ s8 hitSourcePlayerIndex;
    /* 0x248 */ s8 attackerPlayerIndex;
    /* 0x249 */ s8 attackerSpawnNodeId;
    /* 0x24A */ u8 attackTimer;
    /* 0x24B */ u8 pad24B;
    /* 0x24C */ u16 hitModelId;
    /* 0x24E */ u16 hitStrength;
    /* 0x250 */ s32 effectTimer;
    /* 0x254 */ void *effectObj;
    /* 0x258 */ f32 squashScaleXZ;
    /* 0x25C */ f32 squashScaleY;
    /* 0x260 */ struct EffectNode *scoreEffect; // multiplayer score/crown effect (mpUpdateScoreEffects)
    /* 0x264 */ s32 pendingPickupEffect;
    /* 0x268 */ u8 transitionTimer;
    /* 0x269 */ u8 pad269[3];
} PlayerState;

// One kong's 0x5E-byte row of gPlayerInventoryTable (EEPROM fields 1-0xB; see 104F0.c).
// The table's declarations still differ per file; this is the row type, not a new extern.
typedef struct KongInventory {
    union {
        /* 0x00 */ u8 upgrades[5]; // eeprom load/save walk all five bytes (104F0)
        struct {
            /* 0x00 */ u8 moveLevel;       // special moves bought (0-3); users read it as unk0[0]
            /* 0x01 */ u8 slamLevel;       // slam ring tiers and shake strength (D5E10); E4090 slam handlers switch on 2/3
            /* 0x02 */ u8 weaponFlags;     // bit 0 gun owned, bit 1 homing; 7 = all (CC800); the projectile spawn param (19A00)
            /* 0x03 */ u8 ammoBeltLevel;   // ammo cap 50 << level, throw cap 20 + 5 * level (FCCD0); users read it as unk0[3]
            /* 0x04 */ u8 instrumentFlags; // bit 0 instrument owned (playback, pause-menu counter); 0xF = all (CC800)
        };
    };
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u16 coins; // HUD slot 1 (max 999)
    /* 0x08 */ u16 instrumentEnergy; // HUD slot 7
    /* 0x0A */ u16 coloredBananas[14]; // per world, held (HUD slot 0)
    /* 0x26 */ u16 bananasDelivered[14]; // per world, turned in (C2A90); with coloredBananas >= 75 sets the medal
    /* 0x42 */ u16 goldenBananas[14]; // per world (HUD slot 8; slot 9 shows the total)
} KongInventory; /* sizeof 0x5E */

// One player's 0x306-byte block of gPlayerInventoryTable: eight kong rows, then the shared counters.
typedef struct PlayerInventory {
    /* 0x000 */ KongInventory kong[8];
    /* 0x2F0 */ u16 ammo; // HUD slot 2: standard shots
    /* 0x2F2 */ u16 homingAmmo; // HUD slot 3: used instead of ammo while weaponFlags bit 1 is set
    /* 0x2F4 */ u16 throwAmmo; // HUD slot 4: thrown projectiles (projectileTrySpawnFromSlot)
    /* 0x2F6 */ u16 abilityEnergy; // HUD slot 5: drained per frame by special moves, shown in units of 150
    /* 0x2F8 */ u16 cameraFilm; // HUD slot 6: one per camera shot
    /* 0x2FA */ s8 crownBestHealth; // multiplayer: best total (health + healthDelta) while holding the crown
    /* 0x2FB */ s8 health; // melon pips left
    /* 0x2FC */ u8 melons; // melon count (health capacity = melons * per-melon)
    /* 0x2FD */ s8 healthDelta; // pending change, applied by healthApplyPendingDelta
    /* 0x2FE */ u16 kills[4]; // multiplayer: kills of each player
} PlayerInventory; // size = 0x306

// Per-player inventory (4 players at 0x807FC950); gCurrentKongInventory points at the current kong's row.
extern PlayerInventory gPlayerInventoryTable[];
extern KongInventory *gCurrentKongInventory;

// Character (kong) id of each of the 4 players (0x8074E77C-F): indexes gKongCharacterTable (CC800) and
// PlayerInventory.kong; single player uses [0].
extern u8 gPlayerCharacterId[];

// One row of the two five-entry high-score tables gRambiHighScores / gEnguardeHighScores (EEPROM fields 0x16-0x19 and
// 0x1A-0x1D, see 104F0.c eepromInitConfigs; defaults sRambiDefaultHighScores / sEnguardeDefaultHighScores).
typedef struct MenuHighScoreEntry {
    /* 0x0 */ s16 score;
    /* 0x2 */ u8 initials[4]; // initials as characters, [3] the string terminator (menuLoadHighScores writes 0); stored on EEPROM as indices into gInitialsCharset
} MenuHighScoreEntry; /* sizeof 0x6 */

// Collectible totals (0x807FC828), recomputed by hudPauseMenuRefreshTotals (ACDC0): [0] golden bananas over all
// kongs, [1] set flags of sPauseCrownFlags, [2] set flags of the gWorldClearedFlags list, [3] flags 0x225-0x24C, [4] flag 0x17B,
// [5] flags 0x24D-0x260, [6] flag 0x84, [7] flags 0x1FD-0x224, [8] always 1. The first seven weigh into
// menuCalculateGamePercentage (3E10) and the 117190 gate totals; the pause menu's page 3 shows the first eight.
extern s16 gPauseCollectibleCounts[9];

// One entry of the per-map flag tables (135D30.c: gMapObjectFlags, gSpawnFlagConditions, gTriggerOnceFlags, gFlagTempEntries).
typedef struct FlagTableEntry {
    /* 0x0 */ u8 map;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 id;
    /* 0x4 */ s16 flag;
    /* 0x6 */ u8 value;
    /* 0x7 */ u8 active;
} FlagTableEntry; // size = 0x8
// 0x1F entries, ended by map 0xFF (hudPauseMenu's scan in ACDC0.c).
extern FlagTableEntry gSpawnFlagConditions[0x1F];

// One row of the per-character table gKongCharacterTable (CC800 data, 0x10 per character id): the kong actor type, the
// character index the row selects (gCurrentCharacterIndex), its model, and the actor flags.
typedef struct KongCharacterEntry {
    /* 0x0 */ s32 actorType;
    /* 0x4 */ union {
        s32 characterIndex;
        struct {
            u8 pad[3];
            u8 characterId;
        } b;
    };
    /* 0x8 */ union {
        s32 model;
        struct {
            u8 pad[2];
            u16 modelId;
        } m;
    };
    /* 0xC */ s32 actorFlags;
} KongCharacterEntry; // size = 0x10

extern const KongCharacterEntry gKongCharacterTable[];

// One loaded animation-asset cache slot (controllerAnimStateLoadAsset/controllerAnimFreeModel, 17B90);
// gModelCache[32] spans .bss 0x807FB630..0x807FB7B0 (D_807FB634 is the [0].asset split label).
typedef struct ControllerStateEntry {
    /* 0x00 */ u16 assetId;
    /* 0x02 */ u16 refCount;
    /* 0x04 */ void *asset;
    /* 0x08 */ u8 cullSwap;
    /* 0x09 */ u8 pad9[3];
} ControllerStateEntry; // size = 0xC
extern ControllerStateEntry gModelCache[32];

// One animation-clip cache slot (actorInit 7CA80; controllerAnimCacheGetOrLoad/controllerAnimCacheFree, 17B90);
// gAnimClipCache[32] spans .bss 0x807FB7B0..0x807FB930, gAnimClipCacheCount counts the used slots (packed from 0).
typedef struct AnimCacheEntry {
    /* 0x00 */ s32 id; // clip asset id, 0xFFFF when free
    /* 0x04 */ s32 refCount;
    /* 0x08 */ void *asset;
} AnimCacheEntry; // size = 0xC
extern AnimCacheEntry gAnimClipCache[32];
extern u16 gAnimClipCacheCount;

// camSetTarget's parameter block inside CamState (0x44).
typedef struct CamTargetBlock {
    /* 0x00 */ struct Actor *eyeActor;
    /* 0x04 */ struct Actor *focusActor;
    /* 0x08 */ s16 eyeYaw;
    /* 0x0A */ s16 eyeDist;
    /* 0x0C */ s16 focusYaw;
    /* 0x0E */ s16 focusDist;
    /* 0x10 */ s16 eyeHeight;
    /* 0x12 */ s16 focusHeight;
    /* 0x14 */ s16 framesLeft;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ f32 stepRatio;
} CamTargetBlock;

// customState of the camera actor (type 0xBC, component 4: 0x100 bytes, gActorComponentSizes[4]);
// reached as gCamActor->customState or PlayerState.camActor->customState.
typedef struct CamState {
    /* 0x00 */ struct Actor *followActor;
    /* 0x04 */ struct Actor *secondTarget;
    /* 0x08 */ u16 roomHeight;
    /* 0x0A */ u16 prevRoomHeight;
    /* 0x0C */ f32 ceilingY;
    /* 0x10 */ s16 targetMoveSpeed;
    /* 0x12 */ s16 secondTargetX;
    /* 0x14 */ s16 secondTargetZ;
    /* 0x16 */ u8 pad16[0x2];
    /* 0x18 */ f32 floorMargin;
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
    /* 0x44 */ CamTargetBlock target;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ u8 pad64[0x8];
    /* 0x6C */ f32 followBaseY;
    /* 0x70 */ f32 targetFloorY;
    /* 0x74 */ u8 pad74[0x4];
    /* 0x78 */ f32 focusX;
    /* 0x7C */ f32 focusY;
    /* 0x80 */ f32 focusZ;
    /* 0x84 */ f32 eyeGoalX;
    /* 0x88 */ f32 eyeGoalY;
    /* 0x8C */ f32 eyeGoalZ;
    /* 0x90 */ f32 waterY;
    /* 0x94 */ f32 lookAheadDist;
    /* 0x98 */ f32 stickLookY;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ s16 lookAheadYaw;
    /* 0xA0 */ f32 followDist;
    /* 0xA4 */ f32 followDistGoal;
    /* 0xA8 */ f32 unkA8;
    /* 0xAC */ u32 flags;
    /* 0xB0 */ s16 pendingTurn;
    /* 0xB2 */ s16 orbitYaw;
    /* 0xB4 */ s16 savedOrbitYaw;
    /* 0xB6 */ u8 padB6[0x2];
    /* 0xB8 */ f32 followHeightGoal;
    /* 0xBC */ s16 aimHeightBase;
    /* 0xBE */ u8 padBE[0x2];
    /* 0xC0 */ s32 shakeStrength;
    /* 0xC4 */ s16 activeZone;
    /* 0xC6 */ s16 triggeredZone;
    /* 0xC8 */ s16 clampYawFrom;
    /* 0xCA */ s16 clampYawTo;
    /* 0xCC */ f32 prevTargetX;
    /* 0xD0 */ f32 prevTargetY;
    /* 0xD4 */ f32 prevTargetZ;
    /* 0xD8 */ f32 targetAnchorX;
    /* 0xDC */ f32 targetAnchorY;
    /* 0xE0 */ f32 targetAnchorZ;
    /* 0xE4 */ f32 followBlendRate;
    /* 0xE8 */ s16 blendRampFramesLeft;
    /* 0xEA */ s16 blendRampFrames;
    /* 0xEC */ u8 activeZoneFlags;
    /* 0xED */ u8 activeZoneType;
    /* 0xEE */ u8 preferredZoomLevel;
    /* 0xEF */ u8 zoomLevel;
    /* 0xF0 */ u8 savedZoomLevel;
    /* 0xF1 */ u8 repositionFrames;
    /* 0xF2 */ u8 shakeFrames;
    /* 0xF3 */ u8 mode;
    /* 0xF4 */ u8 occludedFrames;
    /* 0xF5 */ u8 snapBehindFrames;
    /* 0xF6 */ u8 fastBlendFrames;
    /* 0xF7 */ u8 settleFrames;
    /* 0xF8 */ u8 unkF8;
    /* 0xF9 */ u8 railEnd;
    /* 0xFA */ u8 hasWater;
    /* 0xFB */ u8 playerIndex;
    /* 0xFC */ u8 wallCollisionMode;
    /* 0xFD */ u8 activeZoneLink;
    /* 0xFE */ u8 padFE[0x1];
    /* 0xFF */ u8 clearYawFails;
} CamState; // size = 0x100

// One floor probe result: collisionRecordTriangleS (6AD90) appends to sCamFloorHits, camSortFloorHits (201B0)
// sorts them by height and camFloorSnap reads the first.
typedef struct CamFloorHit {
    /* 0x0 */ f32 height;
    /* 0x4 */ s16 angle;
    /* 0x6 */ u8 flags;
    /* 0x7 */ u8 unk7;
} CamFloorHit; // size = 0x8

extern CamFloorHit sCamFloorHits[];
extern u8 sCamFloorHitCount;

// customState of the mirror actor 0x7B: triggerZoneSpawnTrigger (684C0) fills the plane fields from its
// TriggerZoneData; actorMirrorParentModelY/actorMirrorParentModelAxis (A2F10) reflect the parent's model.
typedef struct MirrorActorState {
    /* 0x00 */ struct Actor *parent;
    /* 0x04 */ s32 parentInstanceId;
    /* 0x08 */ u32 parentType;
    /* 0x0C */ s16 planeOffset;
    /* 0x0E */ u8 axisFlags;
    /* 0x0F */ u8 alpha;
} MirrorActorState; // size = 0x10

// Viewport layout entry (gViewportLayouts[], cameraFindViewportEntry).
typedef struct G00Entry {
    /* 0x0 */ u8 playerCount;
    /* 0x1 */ u8 splitScreenMode;
    /* 0x2 */ u8 viewMask;
    /* 0x3 */ u8 playerIndex;
    /* 0x4 */ s16 left;
    /* 0x6 */ s16 top;
    /* 0x8 */ s16 right;
    /* 0xA */ s16 bottom;
} G00Entry;

// Split-screen divider rectangle (gSplitScreenDividerRects, defined in CC800, read by gfxDrawSplitScreenDividers;
// terminated by players == -1); coordinates in low-res pixels.
typedef struct {
    s8 players; // player count it applies to; 2 = any multiplayer count
    u8 splitMode;
    u8 viewMask;
    u8 pad3;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} FillRectEntry;

// Spawn position (raceGridSpawnPoint).
typedef struct G01Pos {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 yaw;
    /* 0x7 */ u8 camMode;
    /* 0x8 */ u8 spawnKind;
    /* 0x9 */ u8 flags;
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
extern const SpawnEntry gSpawnEntryTable[];
extern Zone *gBehaviourZone; // gBehaviourAnimState->zone, latched by behaviourFrameBegin
extern ZoneTable *gZoneTable;
extern SpawnNodeList *gSpawnNodeList;
extern ActorGlobalState gActorGlobalState;
// Cutscene condition flag (0x807F6903, defined in 42630.c): cutscene command 0x96 sets it, condition 0x3D
// reads it; playerInputCheckMultiplayerPlayerTarget (E4090.c) handles gActorGlobalState.unk14 3/5 only while it is 0.
extern u8 gCsCondFlag;


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

// Per-actor-type collision tables (D_8074C604, defined in 7BBD0.c, read by 7A510.c): a slot's table
// is a list of attacker patterns ending with pattern 0, each naming a list of interactions whose
// last entry has chain 0.
typedef s32 (*CollisionFilterFn)(Actor *, Actor *, ActorCallbackNode *);

typedef struct CollisionInteractionEntry {
    s16 targetMask;
    s16 attackerMask;
    CollisionFilterFn filter;
    u8 phase;
    u8 event;
    u8 chain;
    u8 padB;
} CollisionInteractionEntry;

typedef struct CollisionTableEntry {
    s16 pattern;
    CollisionInteractionEntry *entries;
} CollisionTableEntry;

typedef struct CollisionTableSlot {
    CollisionTableEntry *table;
    u8 unk4;
    u8 pad5[3];
} CollisionTableSlot;

// Per-actor-type health and damage (D_8074D0C4, defined in 7BBD0.c).
typedef struct ActorTypeStat {
    s16 health;
    s16 damage;
} ActorTypeStat;

typedef struct MpSettings {
    s32 matchType;
    s32 gameMode;
    s32 matchPhase;
    s32 limit;
    s32 playerControllerSlots[4];
    s32 mapIndex;
} MpSettings; /* size 0x24 */

extern MpSettings gMpSettings;

// Per-player pad record (gPlayerPadState at 0x807FD610).
typedef struct PadInputState {
    /* 0x00 */ s32 stickHeldFrames;
    /* 0x04 */ f32 stickMag;
    /* 0x08 */ f32 stickMagNorm;
    /* 0x0C */ f32 stickMagDelta;
    /* 0x10 */ f32 stickMagHistory[4];
    /* 0x20 */ s16 stickAngleHistory[4];
    /* 0x28 */ s16 stickAngle;
    /* 0x2A */ u16 heldButtons;
    /* 0x2C */ u16 pressedButtons;
    /* 0x2E */ s8 stickX;
    /* 0x2F */ s8 stickY;
    /* 0x30 */ u8 stickAbsX;
    /* 0x31 */ u8 stickAbsY;
    /* 0x32 */ u8 pad32[2];
} PadInputState; // size = 0x34

extern PadInputState gPlayerPadState[];

#endif
