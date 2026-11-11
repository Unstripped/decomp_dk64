#ifndef RESQUEUE_H
#define RESQUEUE_H

#include "common.h"
#include "actor.h"

struct EffectNode;

// A laid-out glyph (text rows) or effect cell (grid rows).
typedef struct ResGlyph {
    /* 0x00 */ s16 width;
    /* 0x02 */ u8 pad2[0xE];
    /* 0x10 */ u16 attr; // text: style flags; grid: effect id
    /* 0x12 */ u8 code; // text: character; grid: sub index
    /* 0x13 */ u8 pad13;
    /* 0x14 */ struct EffectNode *effect;
    /* 0x18 */ u8 pad18[0x88];
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
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ Actor *key;
    /* 0x08 */ u16 resId;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ ResRow *rows;
    /* 0x10 */ u8 rowState;
    /* 0x11 */ u8 pad11[0x23];
    /* 0x34 */ void *unk34;
    /* 0x38 */ u8 pad38[0x1C];
    /* 0x54 */ u8 queueFlags;
} ResQueueActorState; // size = 0x58

#endif
