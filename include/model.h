#ifndef MODEL_H
#define MODEL_H

#include "common.h"
#include "collision.h"
#include "heap.h"

// Model asset file header (asset table 4, ModelSlot.unk24); the fields seen so far.
typedef struct ModelAssetHeader {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s32 unk20; // collision sphere radius (collisionBuildSlotBoxes)
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
    /* 0x3B */ u8 pad3B;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 pad3E[2];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C; // offset of the collision box table (collisionBuildSlotBoxes)
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68; // offset of the animation data block (modelSlotDataSize)
    /* 0x6C */ s32 unk6C; // offset of the texture-animation table (modelSlotInitTexAnimNodes)
    /* 0x70 */ s32 unk70; // offset of the texture / quad table (modelSlotLinkTexAnimTextures, modelQuadBuildOutput)
} ModelAssetHeader;

// One animation channel of a model slot (ModelData.entries, 54150).
typedef struct ModelAnimEntry {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ s8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
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
    /* 0x08 */ s32 timestamp; // gFrameCounter at the last build
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
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ void *unk20;
    /* 0x24 */ ModelAssetHeader *unk24;
    /* 0x28 */ DynamicBuffer unk28;
    /* 0x48 */ ModelTriBuffer unk48;
    /* 0x70 */ struct ModelPosNode *unk70;
    /* 0x74 */ struct ModelPosNode *unk74;
    /* 0x78 */ ModelData *unk78;
    /* 0x7C */ struct CsStateFull *unk7C; // per-model cutscene state (csStateInit)
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[3];
} ModelSlot; // size = 0x90

#endif
