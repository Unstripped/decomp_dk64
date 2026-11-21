#ifndef MODEL_H
#define MODEL_H

#include "common.h"
#include "collision.h"
#include "heap.h"

// Model asset file header (asset table 4, ModelSlot.unk24); the fields seen so far.
typedef struct ModelAssetHeader {
    /* 0x00 */ u32 flags;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s32 lastUsedFrame;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u8 modelKind;
    /* 0x1D */ u8 fullBright;
    /* 0x1E */ s16 maxDist;
    /* 0x20 */ s32 collisionRadius; // collision sphere radius (collisionBuildSlotBoxes)
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ s16 spriteTexture;
    /* 0x2A */ s16 spriteAnimTextureId;
    /* 0x2C */ s16 spriteYawOffset;
    /* 0x2E */ s16 spriteHalfWidth;
    /* 0x30 */ s16 spriteHalfDepth;
    /* 0x32 */ u8 spriteTexWidth;
    /* 0x33 */ u8 spriteTexHeight;
    /* 0x34 */ u8 spriteTexFormat;
    /* 0x35 */ u8 spriteTexSize;
    /* 0x36 */ u8 spriteFullAlphaDist;
    /* 0x37 */ u8 spriteMaxDist;
    /* 0x38 */ u8 spriteBaseAlpha;
    /* 0x39 */ u8 spriteZBuffered;
    /* 0x3A */ u8 saveState;
    /* 0x3B */ u8 pad3B;
    /* 0x3C */ s16 textureRefCount;
    /* 0x3E */ u8 pad3E[2];
    /* 0x40 */ s32 displayListAOff;
    /* 0x44 */ s32 displayListBOff;
    /* 0x48 */ s32 segmentDataOff;
    /* 0x4C */ s32 boxesOff; // offset of the collision box table (collisionBuildSlotBoxes)
    /* 0x50 */ s32 trisOff;
    /* 0x54 */ s32 attachPointsOff;
    /* 0x58 */ s32 nodesOff;
    /* 0x5C */ s32 proxPathsOff;
    /* 0x60 */ s32 bonesOff;
    /* 0x64 */ s32 animNodesOff;
    /* 0x68 */ s32 animDataOff; // offset of the animation data block (modelSlotDataSize)
    /* 0x6C */ s32 texAnimsOff; // offset of the texture-animation table (modelSlotInitTexAnimNodes)
    /* 0x70 */ s32 quadsOff; // offset of the texture / quad table (modelSlotLinkTexAnimTextures, modelQuadBuildOutput)
} ModelAssetHeader;

// One placed model of the map's model asset (assetLoad table 9: an s32 count, then count records;
// modelAssetGetSubtables, 36880.c).
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 rotX;
    /* 0x1C */ f32 rotY;
    /* 0x20 */ f32 rotZ;
    /* 0x24 */ f32 yOffset;
    /* 0x28 */ s16 modelType;
    /* 0x2A */ s16 mapObjectId;
    /* 0x2C */ u8 pad2C[2];
    /* 0x2E */ u8 light;
    /* 0x2F */ u8 flags;
} ModelAssetEntry; /* 0x30 */

// Animation node header of a ModelAnimEntry (54150): keyCount key times, then matrixCount
// matrix records of keyCount * 0x24 + 8 bytes each.
typedef struct ModelAnimNodeHeader {
    /* 0x00 */ u8 keyCount;
    /* 0x01 */ u8 times[0x38];
    /* 0x39 */ u8 matrixCount;
    /* 0x3A */ u8 pad3A[2];
} ModelAnimNodeHeader; // size = 0x3C

// One animation channel of a model slot (ModelData.entries, 54150).
typedef struct ModelAnimEntry {
    /* 0x00 */ ModelAnimNodeHeader *node;
    /* 0x04 */ f32 keyFrac;
    /* 0x08 */ s16 loopCount;
    /* 0x0A */ s16 loopLimit;
    /* 0x0C */ s16 speed;
    /* 0x0E */ u8 active;
    /* 0x0F */ u8 direction;
    /* 0x10 */ u8 loopMode;
    /* 0x11 */ s8 keyIndex;
    /* 0x12 */ u8 motionFlags;
    /* 0x13 */ u8 scaleMode;
} ModelAnimEntry; // size = 0x14

// Per-slot animation state (ModelSlot.unk78, modelSlotAllocAnimBuffers).
typedef struct ModelData {
    /* 0x00 */ u8 *frames[2]; // per-gfx-buffer animation data
    /* 0x08 */ ModelAnimEntry entries[10];
} ModelData; // size = 0xD0

// Per-slot triangle buffer (ModelSlot.unk48, modelSlotTriBufferRelease); 0x28 bytes.
typedef struct ModelTriBuffer {
    /* 0x00 */ CollisionTriF *tri_start;
    /* 0x04 */ CollisionTriF *tri_end; // one past the last built triangle
    /* 0x08 */ u32 timestamp; // gFrameCounter at the last build
    /* 0x0C */ CollisionBoundingBox bbox;
    /* 0x24 */ u8 flags; // 1 = built (tri_start owned), 2 = model data flag 4, 4 = has triangles
    /* 0x25 */ u8 unk25[2];
} ModelTriBuffer; // size = 0x28

// Model position list node (ModelSlot.unk70/unk74, modelPosNodeListFree); 0x10 bytes.
typedef struct ModelPosNode {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ struct ModelPosNode *next;
} ModelPosNode; // size = 0x10

// One placed map model (gModelSlots[], indexed by hashTableLookup()); 0x90 bytes.
typedef struct ModelSlot {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ f32 rotX;
    /* 0x14 */ f32 rotY;
    /* 0x18 */ f32 rotZ;
    /* 0x1C */ f32 yOffset;
    /* 0x20 */ void *renderObj;
    /* 0x24 */ ModelAssetHeader *asset;
    /* 0x28 */ DynamicBuffer boxBuffer;
    /* 0x48 */ ModelTriBuffer triBuffer;
    /* 0x70 */ struct ModelPosNode *attachPoints;
    /* 0x74 */ struct ModelPosNode *unk74;
    /* 0x78 */ ModelData *anim;
    /* 0x7C */ struct CsState *csState; // per-model cutscene state (csStateInit)
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 modelType;
    /* 0x86 */ s16 modelKind;
    /* 0x88 */ s16 id;
    /* 0x8A */ s16 csModelId;
    /* 0x8C */ u8 flags;
    /* 0x8D */ u8 pad8D[3];
} ModelSlot; // size = 0x90

#endif
