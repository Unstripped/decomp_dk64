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
    /* 0x00 */ s16 v[12];
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
    /* 0x240 */ u8 pad240[0xDB0 - 0x240];
    /* 0xDB0 */ Gfx subDisplayList[(0x11B0 - 0xDB0) / sizeof(Gfx)];
} FrameMatrices; // size = 0x11B0

#endif
