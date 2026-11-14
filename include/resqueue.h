#ifndef RESQUEUE_H
#define RESQUEUE_H

#include "common.h"
#include "actor.h"

struct EffectNode;

// A laid-out glyph (text rows) or effect cell (grid rows).
typedef struct ResGlyph {
    /* 0x00 */ s16 width;
    /* 0x02 */ u8 fade; // fade-in level, 0xFF = fully shown
    /* 0x03 */ u8 alpha; // min(fade, the box's textAlpha)
    /* 0x04 */ f32 x; // position inside the text box
    /* 0x08 */ f32 y;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ u16 attr; // text: style flags; grid: effect id
    /* 0x12 */ u8 code; // text: character; grid: sub index (nonzero flips the effect)
    /* 0x13 */ u8 pad13;
    /* 0x14 */ struct EffectNode *effect;
    /* 0x18 */ u8 mtx[2][0x40]; // text: per-gfx-buffer Mtx (guMtxF2L target)
    /* 0x98 */ f32 animPhase; // text: animation angle for the attr effects
    /* 0x9C */ u8 pad9C[4];
    /* 0xA0 */ struct ResGlyph *next;
} ResGlyph; // size = 0xA4

typedef struct ResRow {
    /* 0x00 */ u8 kind; // 1: text, 2: grid
    /* 0x01 */ u8 pad1[7];
    /* 0x08 */ void *data;
    /* 0x0C */ ResGlyph *glyphs;
    /* 0x10 */ u16 timer;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ f32 width;
    /* 0x18 */ f32 height;
    /* 0x1C */ struct ResRow *next;
} ResRow; // size = 0x20

// customState of the queue actor (actor 0x12B).
typedef struct ResQueueActorState {
    /* 0x00 */ u16 openTimer; // 0..30 while the box opens, counted back down on close
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ Actor *key;
    /* 0x08 */ u16 resId;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ ResRow *rows;
    /* 0x10 */ u8 rowState;
    /* 0x11 */ u8 glyphCursor; // glyph being faded in
    /* 0x12 */ u8 holdTimer; // set from ResRow.timer, counts down in state 3
    /* 0x13 */ u8 pad13;
    /* 0x14 */ f32 scrollY; // y of the first row
    /* 0x18 */ f32 scrollLeft; // scroll distance still to go
    /* 0x1C */ u8 animFrame;
    /* 0x1D */ u8 textAlpha;
    /* 0x1E */ u8 pad1E[2];
    /* 0x20 */ f32 openProgress; // 0..1
    /* 0x24 */ f32 anchorX;
    /* 0x28 */ f32 anchorY;
    /* 0x2C */ f32 targetX;
    /* 0x30 */ f32 targetY;
    /* 0x34 */ u8 *mtxBuf; // heapAlloc(0x280): box and tail matrices
    /* 0x38 */ s16 waveAngleX;
    /* 0x3A */ s16 waveAngleY;
    /* 0x3C */ u8 anchorFixed;
    /* 0x3D */ u8 pad3D[3];
    /* 0x40 */ f32 waveAmp;
    /* 0x44 */ f32 boxLeft;
    /* 0x48 */ f32 boxTop;
    /* 0x4C */ f32 boxRight;
    /* 0x50 */ f32 boxBottom;
    /* 0x54 */ u8 queueFlags;
    /* 0x55 */ u8 inputFlags; // 1 close, 2 slow, 4 fast
    /* 0x56 */ u8 pad56[2];
} ResQueueActorState; // size = 0x58

#endif
