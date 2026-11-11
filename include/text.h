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

#endif
