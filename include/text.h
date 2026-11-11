#ifndef TEXT_H
#define TEXT_H

#include "common.h"

// Per-font metrics table entry (D_80754A34[font]); 6 bytes.
typedef struct TextFontInfo {
    /* 0x0 */ u8 firstSheet;
    /* 0x1 */ u8 lineCount;
    /* 0x2 */ u8 height;
    /* 0x3 */ u8 spaceWidth;
    /* 0x4 */ u8 spacing;
    /* 0x5 */ u8 fixedWidth;
} TextFontInfo; // size = 0x6

// One animated-text element (textDrawAnimated eases each field toward its target); 0x38 bytes.
typedef struct TextObjectElem {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 targetX;
    /* 0x10 */ f32 targetY;
    /* 0x14 */ f32 targetZ;
    /* 0x18 */ f32 rotX;
    /* 0x1C */ f32 rotY;
    /* 0x20 */ f32 rotZ;
    /* 0x24 */ f32 targetRotX;
    /* 0x28 */ f32 targetRotY;
    /* 0x2C */ f32 targetRotZ;
    /* 0x30 */ f32 scale;
    /* 0x34 */ f32 targetScale;
} TextObjectElem; // size = 0x38

// Animated text object (gfxResourceCreate list node, textObjectDrawFlat/Rotated); 0x20 bytes.
typedef struct TextObject {
    /* 0x00 */ struct TextObject *next;
    /* 0x04 */ u8 *text;
    /* 0x08 */ TextObjectElem *elems;
    /* 0x0C */ u8 font;
    /* 0x0D */ u8 count;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ f32 phase;
    /* 0x14 */ f32 easeRate;
    /* 0x18 */ f32 timer;
    /* 0x1C */ s16 id;
} TextObject; // size = 0x20

#endif
