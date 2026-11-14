#ifndef RENDER_H
#define RENDER_H

#include "common.h"

// One entry of a render list (map chunk opaque/translucent lists, BSP vis-node lists).
typedef struct RenderEntry {
    /* 0x00 */ void *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ struct RenderEntry *unk14;
    /* 0x18 */ struct RenderEntry *unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[3];
} RenderEntry; // size = 0x28

// A clip/frustum plane polygon: four s16 vertices and its plane equation.
typedef struct PlanePoly {
    /* 0x00 */ s16 v[4][3];
    /* 0x18 */ u8 type;
    /* 0x19 */ u8 pad19[7];
    /* 0x20 */ f64 a;
    /* 0x28 */ f64 b;
    /* 0x30 */ f64 c;
    /* 0x38 */ f64 d;
} PlanePoly; // size = 0x40

// Per-frame matrices and sub display list (D_80767CE8[2], gGfxCurrentFrameBuffer); 0x11B0 bytes.
typedef struct FrameMatrices {
    /* 0x000 */ Mtx perspective;
    /* 0x040 */ Mtx unk40;
    /* 0x080 */ Mtx ortho;
    /* 0x0C0 */ Mtx orthoQuad;
    /* 0x100 */ Mtx orthoViewport;
    /* 0x140 */ Mtx orthoDouble;
    /* 0x180 */ Mtx identity;
    /* 0x1C0 */ Mtx unk1C0;
    /* 0x200 */ Mtx unk200; // transition camera look-at (transitionBeginDisplayList)
    /* 0x240 */ u8 pad240[0x270 - 0x240];
    /* 0x270 */ Lights7 lightSets[24]; // per light set (gLightSetIndex: reset by commandQueueReset, capped at 0x17 by actorBuildLightDisplayList)
    /* 0xDB0 */ Gfx subDisplayList[(0x11B0 - 0xDB0) / sizeof(Gfx)];
} FrameMatrices; // size = 0x11B0

struct TexAnimNode;
struct ModelSlotSubNode;

// Type-2 model object: ModelSlot.unk20 of a textured-quad model (heapAlloc(0x60) in modelSlotInitFromAsset,
// filled by modelQuadBuildOutput/modelSlotInit, drawn by renderModelQuadGfx; renderEntryIsTranslucent reads flags bits 1/2).
typedef struct RenderQuadModelObj {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 scale;
    /* 0x10 */ f32 yOffset;
    /* 0x14 */ Mtx *frameMtx0; // per-viewport model matrix, gfx buffer 0 (heapAlloc(gViewportCount << 6))
    /* 0x18 */ Mtx *frameMtx1; // the same for gfx buffer 1
    /* 0x1C */ Vtx *verts; // 4 per quad (heapAlloc(quadCount << 6))
    /* 0x20 */ u8 quadCount;
    /* 0x21 */ u8 pad21[3];
    /* 0x24 */ void *textures[4]; // per quad (modelSlotLoadAssetTextures)
    /* 0x34 */ void *palettes[4]; // per quad or NULL; the TLUT renderModelQuadGfx loads when texFormat is G_IM_FMT_CI
    /* 0x44 */ u8 texWidth;
    /* 0x45 */ u8 texHeight;
    /* 0x46 */ u8 texSize; // G_IM_SIZ_*
    /* 0x47 */ u8 texFormat; // G_IM_FMT_*
    /* 0x48 */ s16 averageY; // mean quad vertex y (modelQuadBuildOutput)
    /* 0x4A */ s16 modelType;
    /* 0x4C */ s16 id;
    /* 0x4E */ u8 flags; // 0x10 hidden by flag (modelNodeListSyncFlags), 8 projected, 4 facing, 2/1 translucent
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ struct TexAnimNode *texAnims;
    /* 0x54 */ struct ModelSlotSubNode *subNode;
    /* 0x58 */ s16 maxDist;
    /* 0x5A */ u8 unk5A;
    /* 0x5B */ u8 light;
    /* 0x5C */ u8 surfaceType; // groundSurfaceTypeAt
} RenderQuadModelObj; // size = 0x60

// An effect sprite sheet (effectGridRegister, 119370.c) and its loaded frame cache.
typedef struct EffectGridAsset {
    /* 0x00 */ s32 id;
    /* 0x04 */ u8 width;
    /* 0x05 */ u8 height;
    /* 0x06 */ u8 format;
    /* 0x07 */ u8 size;
    /* 0x08 */ u8 red;
    /* 0x09 */ u8 green;
    /* 0x0A */ u8 blue;
    /* 0x0B */ u8 alpha;
    /* 0x0C */ u8 unlit;
    /* 0x0D */ u8 altCategory;
    /* 0x0E */ s16 cellW;
    /* 0x10 */ s16 cellH;
    /* 0x12 */ s16 frameCount;
    /* 0x14 */ u8 data[1];
} EffectGridAsset;

typedef struct EffectGridSlot {
    void *buffer;
    s32 frame;
} EffectGridSlot;

typedef struct EffectGridNode {
    /* 0x00 */ EffectGridAsset *asset;
    /* 0x04 */ s32 id;
    /* 0x08 */ u8 width;
    /* 0x09 */ u8 height;
    /* 0x0A */ u8 format;
    /* 0x0B */ u8 size;
    /* 0x0C */ s16 cellW;
    /* 0x0E */ s16 cellH;
    /* 0x10 */ u8 red;
    /* 0x11 */ u8 green;
    /* 0x12 */ u8 blue;
    /* 0x13 */ u8 alpha;
    /* 0x14 */ u8 unlit;
    /* 0x15 */ u8 altCategory;
    /* 0x16 */ s16 frameCount;
    /* 0x18 */ s32 lastUsedFrame;
    /* 0x1C */ EffectGridSlot *slots;
    /* 0x20 */ u8 *data;
    /* 0x24 */ struct EffectGridNode *next;
} EffectGridNode;

// EffectNode.speed read as two halves by the confetti and drift effects (11BC10.c).
typedef struct EffectParamPair {
    /* 0x0 */ s16 hi; // confetti: base angle
    /* 0x2 */ s16 lo; // confetti: drift radius; drift effects: heading
} EffectParamPair;

// One live 2D/3D effect (effectCreate, 119370.c); 0x3A0 bytes.
struct EffectNode;
typedef void (*EffectCallback)(struct EffectNode *effect, u8 *chunkFound);

typedef struct EffectNode {
    /* 0x000 */ Gfx *displayLists[4][2];
    /* 0x020 */ u8 viewportCount;
    /* 0x021 */ u8 displayListIndex;
    /* 0x022 */ u8 pad22[6];
    /* 0x028 */ Vtx vertices[16];
    /* 0x128 */ Mtx matrices[4][2];
    /* 0x328 */ EffectCallback callback;
    /* 0x32C */ u8 state;
    /* 0x32D */ u8 freePending;
    /* 0x32E */ u8 pad32E[2];
    /* 0x330 */ struct EffectGridNode *grid;
    /* 0x334 */ u8 anchorType;
    /* 0x335 */ u8 pad335[3];
    /* 0x338 */ struct Actor *owner;
    /* 0x33C */ s16 boneIndex;
    /* 0x33E */ u8 subIndex;
    /* 0x33F */ u8 pad33F;
    /* 0x340 */ f32 x;
    /* 0x344 */ f32 y;
    /* 0x348 */ f32 z;
    /* 0x34C */ s16 maxDistance;
    /* 0x34E */ s16 param;
    /* 0x350 */ u8 frameDelay;
    /* 0x351 */ u8 frameTimer;
    /* 0x352 */ u8 pad352[2];
    /* 0x354 */ s32 duration;
    /* 0x358 */ s32 durationTimer;
    union {
        /* 0x35C */ s32 speed; // effectSetSpeed: the per-kind creation parameter
        /* 0x35C */ struct Actor *target; // effectSetSpeed((s32)actor): the actor a light or follow effect tracks
        /* 0x35C */ void *data; // effectSetSpeed((s32)state): per-kind state (effectWaveMotionUpdate)
        /* 0x35C */ EffectParamPair pair; // effectSetSpeed((hi << 16) | lo)
    };
    /* 0x360 */ f32 scaleX;
    /* 0x364 */ f32 scaleY;
    /* 0x368 */ s16 startDelay;
    /* 0x36A */ u8 red;
    /* 0x36B */ u8 green;
    /* 0x36C */ u8 blue;
    /* 0x36D */ u8 alpha;
    /* 0x36E */ u8 depth;
    /* 0x36F */ u8 mode;
    /* 0x370 */ void *frames[4];
    /* 0x380 */ s32 frameCount;
    union {
        /* 0x384 */ void *allocation; // per-kind state a callback heapAllocs on its first frame
        /* 0x384 */ struct RadialSprayMotion *sprayMotion; // effectRadialSprayUpdate (11BC10.c)
        /* 0x384 */ struct EffectInterpolationState *interp; // effectInterpolationUpdate (11BC10.c)
    };
    /* 0x388 */ s16 chunkFilter;
    /* 0x38A */ s8 chunk;
    /* 0x38B */ u8 pad38B;
    /* 0x38C */ u16 flags;
    /* 0x38E */ s16 minX;
    /* 0x390 */ s16 minY;
    /* 0x392 */ s16 maxX;
    /* 0x394 */ s16 maxY;
    /* 0x396 */ u8 pad396[2];
    /* 0x398 */ struct EffectNode *previous;
    /* 0x39C */ struct EffectNode *next;
} EffectNode;

// A texture tile descriptor filled by dlInitTextureDescriptor (boot/6690) and loaded by
// dlAppendTextureLoad (global/1135F0); arcade double-buffers them at a 0x18-byte stride.
typedef struct TextureDescriptor {
    /* 0x00 */ void *image;
    /* 0x04 */ s32 pal;
    /* 0x08 */ s16 width;
    /* 0x0A */ s16 rectWidth;
    /* 0x0C */ s16 rectHeight;
    /* 0x0E */ u8 format;
    /* 0x0F */ u8 type;
    /* 0x10 */ s16 s;
    /* 0x12 */ s16 t;
    /* 0x14 */ u8 pad14[4];
} TextureDescriptor; // size = 0x18

// One light volume collected for lighting (lightCollectVolumesInBounds, 5E2F0.c): the
// gLightCandidates/gActiveLights entries, also copied into matrix cache nodes (61AA0.c).
typedef struct LightTrigger {
    /* 0x00 */ f32 cosOuter;
    /* 0x04 */ f32 cosInner;
    /* 0x08 */ f32 coneScale;
    /* 0x0C */ f32 dirX;
    /* 0x10 */ f32 dirY;
    /* 0x14 */ f32 dirZ;
    /* 0x18 */ s32 rangeSq;
    /* 0x1C */ f32 invFalloffLength;
    /* 0x20 */ f32 falloffStart;
    /* 0x24 */ f32 invFadeLength;
    /* 0x28 */ f32 fadeStart;
    /* 0x2C */ f32 r;
    /* 0x30 */ f32 g;
    /* 0x34 */ f32 b;
    /* 0x38 */ s16 x;
    /* 0x3A */ s16 y;
    /* 0x3C */ s16 z;
    /* 0x3E */ u8 type;
    /* 0x3F */ u8 volumeIndex;
} LightTrigger; // size = 0x40

extern LightTrigger gLightCandidates[];

#endif
