#ifndef WATER_H
#define WATER_H

#include "common.h"

// Water surface grids: gEffectNodeList nodes (63EC0 builds and animates them, sizeof = 0x54 by
// heapAlloc; 6AD90 samples their height). WaterSurfaceDef is the map's per-surface definition.
typedef struct WaterSurfaceDef {
    /* 0x00 */ f32 texScale;
    /* 0x04 */ f32 waveFreqX;
    /* 0x08 */ f32 waveFreqZ;
    /* 0x0C */ f32 waveAmpX;
    /* 0x10 */ f32 waveAmpZ;
    /* 0x14 */ s32 waveSpeedX;
    /* 0x18 */ s32 waveSpeedZ;
    /* 0x1C */ f32 wobbleFreqX;
    /* 0x20 */ f32 wobbleFreqZ;
    /* 0x24 */ f32 wobbleAmpX;
    /* 0x28 */ f32 wobbleAmpZ;
    /* 0x2C */ s32 wobbleSpeedX;
    /* 0x30 */ s32 wobbleSpeedZ;
    /* 0x34 */ f32 tileScrollStepS;
    /* 0x38 */ f32 tileScrollStepT;
    /* 0x3C */ f32 tileScrollS;
    /* 0x40 */ f32 tileScrollT;
    /* 0x44 */ s16 gridStep;
    /* 0x46 */ s16 minX;
    /* 0x48 */ s16 minZ;
    /* 0x4A */ s16 maxX;
    /* 0x4C */ s16 maxZ;
    /* 0x4E */ s16 surfaceY;
    /* 0x50 */ s16 chunkIds[8];
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 r;
    /* 0x62 */ u8 g;
    /* 0x63 */ u8 b;
    /* 0x64 */ u8 alphaBase;
    /* 0x65 */ u8 alphaRange;
    /* 0x66 */ u8 type;
    /* 0x67 */ u8 chunkCount;
    /* 0x68 */ u8 useLights;
    /* 0x69 */ u8 pad69[3];
} WaterSurfaceDef; /* 0x6C */

typedef struct WaterSurface {
    WaterSurfaceDef *sub;
    f32 level;
    f32 targetLevel;
    f32 levelStep;
    f32 targetAmpX;
    f32 targetAmpZ;
    f32 ampStep;
    Vtx *meshVtx[2];
    Gfx *meshGdl[2];
    s16 gridStep;
    u8 pad2E[2];
    s32 wavePhaseX;
    s32 wavePhaseZ;
    s32 wobblePhaseX;
    s32 wobblePhaseZ;
    s16 scissorLeft;
    s16 scissorTop;
    s16 scissorRight;
    s16 scissorBottom;
    s16 vtxCount;
    u8 unk4A;
    u8 primAlpha;
    u8 flags;
    u8 forceVisible;
    u8 pad4E[2];
    struct WaterSurface *next;
} WaterSurface;

#endif
