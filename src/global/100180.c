#include "common.h"
#include "actor.h"
#include "text.h"
#include "proto/boot/3630.h"
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/15050.h"
#include "proto/global/450.h"
#include "proto/global/6AD90.h"

typedef struct TextGlyph {
    s16 texX;
    u8 width;
    u8 unk3;
} TextGlyph;

typedef struct { u8 b[0x39]; } FcDStr39;
typedef struct { u8 b[0x30]; } FcDStr30;
typedef struct { u8 b[0x3A]; } FcDStr3A;

// This TU's .data (0x80754290-0x80754AD0), in address order: each font's line-start characters,
// its glyph table, the per-font pointer tables, metrics and textMapCharToGlyph's charsets.
u8 D_80754290[4] = { 0x00, 0x20, 0x40, 0x60 };
u8 D_80754294[16] = {
    0x00, 0x04, 0x0A, 0x0F, 0x13, 0x17, 0x1B, 0x1F, 0x25, 0x29, 0x2E, 0x33, 0x37, 0x3B, 0x00, 0x00,
};
u8 D_807542A4[4] = { 0x00, 0x39, 0x00, 0x00 };
u8 D_807542A8[12] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0C };
u8 D_807542B4[4] = { 0x00, 0x60, 0x00, 0x00 };
u8 D_807542B8[4] = { 0x00, 0x5F, 0x00, 0x00 };
u8 D_807542BC[4] = { 0x00, 0x12, 0x23, 0x30 };
TextGlyph D_807542C0[94] = {
    { 0, 6, 0 }, { 6, 6, 0 }, { 12, 6, 0 }, { 18, 6, 0 }, { 24, 6, 0 }, { 30, 6, 0 },
    { 36, 6, 0 }, { 42, 6, 0 }, { 48, 6, 0 }, { 54, 6, 0 }, { 60, 6, 0 }, { 66, 6, 0 },
    { 72, 6, 0 }, { 78, 6, 0 }, { 84, 6, 0 }, { 90, 6, 0 }, { 96, 6, 0 }, { 102, 6, 0 },
    { 108, 6, 0 }, { 114, 6, 0 }, { 120, 6, 0 }, { 126, 6, 0 }, { 132, 6, 0 }, { 138, 6, 0 },
    { 144, 6, 0 }, { 150, 6, 0 }, { 156, 6, 0 }, { 162, 6, 0 }, { 168, 6, 0 }, { 174, 6, 0 },
    { 180, 6, 0 }, { 186, 6, 0 }, { 192, 6, 0 }, { 198, 6, 0 }, { 204, 6, 0 }, { 210, 6, 0 },
    { 216, 6, 0 }, { 222, 6, 0 }, { 228, 6, 0 }, { 234, 6, 0 }, { 240, 6, 0 }, { 246, 6, 0 },
    { 252, 6, 0 }, { 258, 6, 0 }, { 264, 6, 0 }, { 270, 6, 0 }, { 276, 6, 0 }, { 282, 6, 0 },
    { 288, 6, 0 }, { 294, 6, 0 }, { 300, 6, 0 }, { 306, 6, 0 }, { 312, 6, 0 }, { 318, 6, 0 },
    { 324, 6, 0 }, { 330, 6, 0 }, { 336, 6, 0 }, { 342, 6, 0 }, { 348, 6, 0 }, { 354, 6, 0 },
    { 360, 6, 0 }, { 366, 6, 0 }, { 372, 6, 0 }, { 378, 6, 0 }, { 384, 6, 0 }, { 390, 6, 0 },
    { 396, 6, 0 }, { 402, 6, 0 }, { 408, 6, 0 }, { 414, 6, 0 }, { 420, 6, 0 }, { 426, 6, 0 },
    { 432, 6, 0 }, { 438, 6, 0 }, { 444, 6, 0 }, { 450, 6, 0 }, { 456, 6, 0 }, { 462, 6, 0 },
    { 468, 6, 0 }, { 474, 6, 0 }, { 480, 6, 0 }, { 486, 6, 0 }, { 492, 6, 0 }, { 498, 6, 0 },
    { 504, 6, 0 }, { 510, 6, 0 }, { 516, 6, 0 }, { 522, 6, 0 }, { 528, 6, 0 }, { 534, 6, 0 },
    { 540, 6, 0 }, { 546, 6, 0 }, { 552, 6, 0 }, { 558, 6, 0 },
};
TextGlyph D_80754438[97] = {
    { 0, 8, 0 }, { 8, 8, 0 }, { 16, 8, 0 }, { 24, 8, 0 }, { 32, 8, 0 }, { 40, 8, 0 },
    { 48, 8, 0 }, { 56, 8, 0 }, { 64, 8, 0 }, { 72, 8, 0 }, { 80, 8, 0 }, { 88, 8, 0 },
    { 96, 8, 0 }, { 104, 8, 0 }, { 112, 8, 0 }, { 120, 8, 0 }, { 128, 8, 0 }, { 136, 8, 0 },
    { 144, 8, 0 }, { 152, 8, 0 }, { 160, 8, 0 }, { 168, 8, 0 }, { 176, 8, 0 }, { 184, 8, 0 },
    { 192, 8, 0 }, { 200, 8, 0 }, { 208, 8, 0 }, { 216, 8, 0 }, { 224, 8, 0 }, { 232, 8, 0 },
    { 240, 8, 0 }, { 248, 8, 0 }, { 256, 8, 0 }, { 264, 8, 0 }, { 272, 8, 0 }, { 280, 8, 0 },
    { 288, 8, 0 }, { 296, 8, 0 }, { 304, 8, 0 }, { 312, 8, 0 }, { 320, 8, 0 }, { 328, 8, 0 },
    { 336, 8, 0 }, { 344, 8, 0 }, { 352, 8, 0 }, { 360, 8, 0 }, { 368, 8, 0 }, { 376, 8, 0 },
    { 384, 8, 0 }, { 392, 8, 0 }, { 400, 8, 0 }, { 408, 8, 0 }, { 416, 8, 0 }, { 424, 8, 0 },
    { 432, 8, 0 }, { 440, 8, 0 }, { 448, 8, 0 }, { 456, 8, 0 }, { 464, 8, 0 }, { 472, 8, 0 },
    { 480, 8, 0 }, { 488, 8, 0 }, { 496, 8, 0 }, { 504, 8, 0 }, { 512, 8, 0 }, { 520, 8, 0 },
    { 528, 8, 0 }, { 536, 8, 0 }, { 544, 8, 0 }, { 552, 8, 0 }, { 560, 8, 0 }, { 568, 8, 0 },
    { 576, 8, 0 }, { 584, 8, 0 }, { 592, 8, 0 }, { 600, 8, 0 }, { 608, 8, 0 }, { 616, 8, 0 },
    { 624, 8, 0 }, { 632, 8, 0 }, { 640, 8, 0 }, { 648, 8, 0 }, { 656, 8, 0 }, { 664, 8, 0 },
    { 672, 8, 0 }, { 680, 8, 0 }, { 688, 8, 0 }, { 696, 8, 0 }, { 704, 8, 0 }, { 712, 8, 0 },
    { 720, 8, 0 }, { 728, 8, 0 }, { 736, 8, 0 }, { 744, 8, 0 }, { 752, 8, 0 }, { 760, 8, 0 },
    { 768, 8, 0 },
};
TextGlyph D_807545BC[12] = {
    { 4, 24, 0 }, { 6, 17, 0 }, { 6, 21, 0 }, { 6, 19, 0 }, { 3, 26, 0 }, { 6, 21, 0 },
    { 4, 24, 0 }, { 5, 23, 0 }, { 4, 24, 0 }, { 5, 24, 0 }, { 6, 24, 0 }, { 37, 16, 0 },
};
TextGlyph D_807545EC[57] = {
    { 0, 8, 0 }, { 8, 8, 0 }, { 16, 8, 0 }, { 24, 8, 0 }, { 32, 8, 0 }, { 40, 8, 0 },
    { 48, 8, 0 }, { 56, 8, 0 }, { 64, 8, 0 }, { 72, 8, 0 }, { 80, 8, 0 }, { 88, 8, 0 },
    { 96, 8, 0 }, { 104, 8, 0 }, { 112, 8, 0 }, { 120, 8, 0 }, { 128, 8, 0 }, { 136, 8, 0 },
    { 144, 8, 0 }, { 152, 8, 0 }, { 160, 8, 0 }, { 168, 8, 0 }, { 176, 8, 0 }, { 184, 8, 0 },
    { 192, 8, 0 }, { 200, 8, 0 }, { 208, 8, 0 }, { 216, 8, 0 }, { 224, 8, 0 }, { 232, 8, 0 },
    { 240, 8, 0 }, { 248, 8, 0 }, { 256, 8, 0 }, { 264, 8, 0 }, { 272, 8, 0 }, { 280, 8, 0 },
    { 288, 8, 0 }, { 296, 8, 0 }, { 304, 8, 0 }, { 312, 8, 0 }, { 320, 8, 0 }, { 328, 8, 0 },
    { 336, 8, 0 }, { 344, 8, 0 }, { 352, 8, 0 }, { 360, 8, 0 }, { 368, 8, 0 }, { 376, 8, 0 },
    { 384, 8, 0 }, { 392, 8, 0 }, { 400, 8, 0 }, { 408, 8, 0 }, { 416, 8, 0 }, { 424, 8, 0 },
    { 432, 9, 0 }, { 448, 16, 0 }, { 464, 16, 0 },
};
TextGlyph D_807546D0[96] = {
    { 21, 4, 0 }, { 28, 6, 0 }, { 38, 11, 0 }, { 53, 10, 0 }, { 69, 10, 0 }, { 86, 12, 0 },
    { 103, 4, 0 }, { 109, 5, 0 }, { 120, 5, 0 }, { 128, 9, 0 }, { 139, 12, 0 }, { 155, 5, 0 },
    { 164, 7, 0 }, { 174, 4, 0 }, { 181, 9, 0 }, { 194, 9, 0 }, { 207, 5, 0 }, { 215, 10, 0 },
    { 228, 11, 0 }, { 240, 12, 0 }, { 253, 10, 0 }, { 265, 10, 0 }, { 276, 10, 0 }, { 288, 11, 0 },
    { 299, 11, 0 }, { 312, 4, 0 }, { 320, 4, 0 }, { 326, 13, 0 }, { 341, 12, 0 }, { 356, 12, 0 },
    { 372, 8, 0 }, { 383, 18, 0 }, { 21, 9, 0 }, { 35, 10, 0 }, { 49, 8, 0 }, { 63, 9, 0 },
    { 76, 8, 0 }, { 88, 9, 0 }, { 101, 8, 0 }, { 115, 10, 0 }, { 128, 4, 0 }, { 134, 7, 0 },
    { 146, 10, 0 }, { 160, 8, 0 }, { 175, 12, 0 }, { 193, 9, 0 }, { 210, 9, 0 }, { 224, 9, 0 },
    { 238, 9, 0 }, { 253, 9, 0 }, { 265, 10, 0 }, { 277, 10, 0 }, { 291, 10, 0 }, { 308, 9, 0 },
    { 324, 13, 0 }, { 344, 10, 0 }, { 360, 9, 0 }, { 373, 10, 0 }, { 387, 4, 0 }, { 394, 7, 0 },
    { 405, 5, 0 }, { 413, 11, 0 }, { 427, 10, 0 }, { 440, 5, 0 }, { 19, 8, 0 }, { 31, 8, 0 },
    { 43, 8, 0 }, { 54, 8, 0 }, { 66, 8, 0 }, { 77, 8, 0 }, { 87, 9, 0 }, { 100, 8, 0 },
    { 112, 4, 0 }, { 118, 7, 0 }, { 127, 9, 0 }, { 139, 4, 0 }, { 147, 11, 0 }, { 163, 8, 0 },
    { 177, 8, 0 }, { 190, 9, 0 }, { 202, 9, 0 }, { 214, 7, 0 }, { 225, 8, 0 }, { 235, 7, 0 },
    { 247, 8, 0 }, { 259, 8, 0 }, { 272, 11, 0 }, { 288, 7, 0 }, { 300, 8, 0 }, { 312, 9, 0 },
    { 324, 8, 0 }, { 336, 4, 0 }, { 344, 8, 0 }, { 355, 13, 0 }, { 375, 10, 0 }, { 389, 10, 0 },
};
TextGlyph D_80754850[48] = {
    { 0, 10, 0 }, { 10, 9, 0 }, { 19, 9, 0 }, { 28, 9, 0 }, { 37, 8, 0 }, { 45, 8, 0 },
    { 53, 11, 0 }, { 64, 9, 0 }, { 73, 4, 0 }, { 77, 9, 0 }, { 86, 9, 0 }, { 95, 8, 0 },
    { 103, 11, 0 }, { 114, 9, 0 }, { 123, 10, 0 }, { 133, 8, 0 }, { 141, 11, 0 }, { 152, 9, 0 },
    { 0, 9, 0 }, { 9, 9, 0 }, { 18, 9, 0 }, { 27, 12, 0 }, { 39, 8, 0 }, { 47, 9, 0 },
    { 56, 8, 0 }, { 65, 5, 0 }, { 70, 5, 0 }, { 75, 4, 0 }, { 79, 7, 0 }, { 86, 5, 0 },
    { 91, 5, 0 }, { 96, 5, 0 }, { 101, 10, 0 }, { 113, 9, 0 }, { 122, 7, 0 }, { 0, 6, 0 },
    { 6, 9, 0 }, { 15, 9, 0 }, { 24, 10, 0 }, { 34, 10, 0 }, { 44, 9, 0 }, { 53, 9, 0 },
    { 62, 10, 0 }, { 72, 10, 0 }, { 82, 10, 0 }, { 92, 5, 0 }, { 97, 5, 0 }, { 102, 12, 0 },
};
TextGlyph D_80754910[59] = {
    { 0, 19, 0 }, { 22, 13, 0 }, { 37, 13, 0 }, { 51, 16, 0 }, { 0, 11, 0 }, { 13, 11, 0 },
    { 26, 15, 0 }, { 43, 17, 0 }, { 62, 5, 0 }, { 70, 5, 0 }, { 3, 15, 0 }, { 23, 7, 0 },
    { 32, 10, 0 }, { 44, 16, 0 }, { 61, 13, 0 }, { 1, 23, 0 }, { 26, 18, 0 }, { 46, 19, 0 },
    { 68, 4, 0 }, { 0, 14, 0 }, { 16, 19, 0 }, { 36, 15, 0 }, { 52, 14, 0 }, { 0, 18, 0 },
    { 20, 15, 0 }, { 37, 16, 0 }, { 56, 18, 0 }, { 0, 23, 0 }, { 26, 16, 0 }, { 44, 16, 0 },
    { 61, 15, 0 }, { 0, 15, 0 }, { 18, 7, 0 }, { 27, 9, 0 }, { 37, 7, 0 }, { 46, 11, 0 },
    { 59, 16, 0 }, { 2, 16, 0 }, { 20, 17, 0 }, { 40, 16, 0 }, { 58, 15, 0 }, { 0, 19, 0 },
    { 20, 10, 0 }, { 31, 13, 0 }, { 45, 12, 0 }, { 58, 16, 0 }, { 0, 13, 0 }, { 14, 14, 0 },
    { 29, 13, 0 }, { 43, 14, 0 }, { 58, 14, 0 }, { 1, 15, 0 }, { 19, 15, 0 }, { 37, 15, 0 },
    { 55, 15, 0 }, { 1, 19, 0 }, { 23, 24, 0 }, { 49, 7, 0 }, { 58, 11, 0 },
};
u8 *gTextFontLineStarts[7] = {
    D_80754290, D_80754294, D_807542A4, D_807542A8, D_807542B4, D_807542B8, D_807542BC,
};
TextGlyph *gTextGlyphTables[7] = {
    D_807546D0, D_80754910, D_807545EC, D_807545BC, D_80754438, D_807542C0, D_80754850,
};
TextFontInfo gTextFonts[8] = {
    { 0, 3, 16, 5, 0, 12 },
    { 6, 13, 24, 6, 1, 16 },
    { 19, 1, 8, 8, 0, 8 },
    { 20, 11, 32, 21, 1, 24 },
    { 31, 1, 8, 8, 0, 8 },
    { 32, 1, 8, 6, 0, 6 },
    { 3, 3, 12, 5, 0, 9 },
    { 33, 10, 32, 8, 0, 32 },
};
// textMapCharToGlyph's charsets; each string fills its struct exactly (no NUL).
FcDStr39 D_80754A64 = { "ABCDEFGH,.rIJKLMNO:PQRSgTUVWXYlZ!-'?q%&bz0123456789enwsco" };
FcDStr30 D_80754AA0 = { "ABCDEFGHIJKLMNOPQRTUVWXYZ.,!?:;'S-x1234567890()%" };

void func_806FB480(void) {
}

void textBlitNoop100180(void) {
}

u8 *textBlitGlyph(u8 width, u8 *dst, void *sheet, s16 texX, u8 row, u8 *phase, u8 pitch) {
    u8 *srcRow;
    u8 *out;
    s16 j;
    s16 y;
    u8 *src;
    u8 phaseBit;
    u8 srcOdd;
    u8 oddBit;
    u8 *dstRow;
    s32 pad;
    src = sheet;
    srcRow = (u8 *)sheet + (texX >> 1);
    oddBit = width & 1;
    phaseBit = *phase & 1;
    dstRow = dst + pitch * 16 + pitch * row;
    out = dstRow;
    *phase += width;
    width >>= 1;
    srcOdd = texX & 1;
    for (y = 0; y < 0x10; y++) {
        for (j = 0; j < width; j++) {
            if (srcOdd && !phaseBit) {
                *out |= (*src++ & 0xF) << 4;
                *out++ |= (*src & 0xF0) >> 4;
            } else if (srcOdd && phaseBit) {
                *out |= *src++ & 0xF;
                out++;
                *out |= *src & 0xF0;
            } else if (!srcOdd && phaseBit) {
                *out++ |= (*src & 0xF0) >> 4;
                *out |= (*src++ & 0xF) << 4;
            } else {
                *out++ |= *src++;
            }
        }
        srcRow += 0x100;
        if (oddBit) {
            if (srcOdd && !phaseBit) {
                *out |= (*src & 0xF) << 4;
            } else if (srcOdd && phaseBit) {
                *out |= (*src & 0xF) << 4;
            } else if (!srcOdd && phaseBit) {
                *out |= (*src & 0xF0) >> 4;
            } else {
                *out |= *src;
            }
        }
        dstRow -= pitch;
        src = srcRow;
        out = dstRow;
    }
    return dst + width + (phaseBit && oddBit);
}

extern void **gTextFontSheets;

void textBlitString(u8 *dst, u8 pitch, u8 *str) {
    s32 i;
    u8 ch;
    u8 row;
    u8 phase;

    phase = 0;
    ch = *str++;
    while (ch) {
        if (ch != ' ') {
            row = textMapCharToGlyph(0, &ch);
            for (i = 1; i < gTextFonts[0].lineCount + 1; i++) {
                if (ch >= gTextFontLineStarts[0][i - 1] && ch < gTextFontLineStarts[0][i]) {
                    textFontLoadSheet(i - 1);
                    dst = textBlitGlyph(gTextGlyphTables[0][ch].width, dst, gTextFontSheets[i - 1], gTextGlyphTables[0][ch].texX, row, &phase, pitch);
                }
            }
        } else {
            dst += 3;
            phase += 6;
        }
        ch = *str++;
    }
}

void textBlitDash(u8 *dst) {
    u8 phase;

    phase = 0;
    textFontLoadSheet(2);
    // Font 0 glyph 0x5F is char 0x80 (textMapCharToGlyph subtracts 0x21); 2 is that char's yoff.
    textBlitGlyph(gTextGlyphTables[0][0x5F].width, dst, gTextFontSheets[2], gTextGlyphTables[0][0x5F].texX, 2,
                  &phase, 0x30);
}

const FcDStr3A D_8075DC20 = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-?{}:=0123456789<>m)!@#$%^&cab" };

s32 textMapCharToGlyph(s16 font, u8 *ch) {
    s8 yoff;
    FcDStr39 charsetA;
    FcDStr30 charsetB;
    FcDStr3A charsetC;

    yoff = 0;
    switch (font) {
    case 0:
        switch (*ch) {
        case 0x2E:
        case 0x67:
        case 0x70:
        case 0x71:
        case 0x80:
            yoff = 2;
            break;
        case 0x61:
        case 0x79:
            yoff = 1;
            break;
        }
        *ch -= 0x21;
        break;
    case 1:
        charsetA = D_80754A64;
        *ch = _strchr(charsetA.b, *ch) - charsetA.b;
        break;
    case 6:
        charsetB = D_80754AA0;
        *ch = _strchr(charsetB.b, *ch) - charsetB.b;
        break;
    case 2:
        charsetC = D_8075DC20;
        *ch = _strchr(charsetC.b, *ch) - charsetC.b;
        break;
    case 3:
    case 7: {
        u8 digits[] = "0123456789%/";

        *ch = _strchr(digits, *ch) - digits;
        break;
    }
    case 4:
        if (*ch == 0x40) {
            *ch = 0x60;
        } else {
            *ch -= 0x21;
        }
        break;
    case 5:
        *ch -= 0x21;
        break;
    }
    return yoff;
}

extern u8 *gTextFontSheetAges;

void textFontInitTables(void) {
    gTextFontSheets = heapAlloc(0xAC);
    gTextFontSheetAges = heapAlloc(0x2B);
    heapClearBlock(gTextFontSheetAges);
}


void *textFontLoadSheet(s16 sheet) {
    u8 *age = &gTextFontSheetAges[sheet];

    if (*age == 0) {
        gTextFontSheets[sheet] = assetLoad(0xE, sheet, 1, 1);
        gTextFontSheetAges[sheet] = 3;
    } else {
        *age = 3;
    }
    return gTextFontSheets[sheet];
}

void textFontAgeSheets(void) {
    s16 i;
    s16 j;
    s16 n;
    s32 sheet;
    TextFontInfo *e;

    n = 0;
    for (i = 0; i < 8; i++) {
        e = &gTextFonts[i];
        for (j = 0; j < e->lineCount; j++) {
            if (gTextFontSheetAges[n++]) {
                sheet = n - 1;
                gTextFontSheetAges[sheet]--;
                if (gTextFontSheetAges[sheet] == 0) {
                    assetFreeBuffer(gTextFontSheets[sheet], 0x156, 0x23);
                }
            }
        }
    }
}

s32 textGetStringWidth(s16 font, const u8 *str) {
    s32 len;
    u8 ch;
    s32 step;

    len = 0;
    if (font & 0x80) {
        font ^= 0x80;
        return strlen(str) * gTextFonts[font].fixedWidth;
    }
    ch = *str++;
    while (ch) {
        if (ch == 0x20) {
            len += gTextFonts[font].spaceWidth;
            step = gTextFonts[font].spacing;
        } else {
            textMapCharToGlyph(font, &ch);
            step = gTextFonts[font].spacing;
            len += gTextGlyphTables[font][ch].width;
        }
        len += step;
        ch = *str++;
    }
    return len;
}

s16 textCountNonSpace(const u8 *str) {
    s16 count = 0;

    while (*str++) {
        if (str[-1] != ' ') {
            count++;
        }
    }
    return count;
}

/* Loads one font glyph sheet (texture block) for the given font id and line index; case order follows the font id. */
Gfx *textLoadFontSheetGfx(Gfx *dl, u8 font, s16 line) {
    s16 sheet;

    sheet = gTextFonts[font].firstSheet + line - 1;
    textFontLoadSheet(sheet);
    switch (font) {
    case 6:
        gDPLoadTextureBlock(dl++, (u8 *)gTextFontSheets[sheet] + 0x80000000, G_IM_FMT_IA, G_IM_SIZ_8b, 176, 13, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 0:
        gDPLoadTextureBlock_4b(dl++, (u8 *)gTextFontSheets[sheet] + 0x80000000, G_IM_FMT_IA, 512, 16, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 1:
        gDPLoadTextureBlock(dl++, (u8 *)gTextFontSheets[sheet] + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 76, 24, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 2:
        gDPLoadTextureBlock_4b(dl++, (u8 *)gTextFontSheets[sheet] + 0x80000000, G_IM_FMT_I, 512, 8, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 3:
    case 7:
        gDPLoadTextureBlock(dl++, (u8 *)gTextFontSheets[sheet] + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 4:
        gDPLoadTextureBlock_4b(dl++, (u8 *)gTextFontSheets[sheet] + 0x80000000, G_IM_FMT_I, 1024, 8, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case 5:
        gDPLoadTextureBlock_4b(dl++, (u8 *)gTextFontSheets[sheet] + 0x80000000, G_IM_FMT_I, 1024, 8, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    }
    return dl;
}

extern Mtx D_20000C0;
extern Mtx D_2000180;

Gfx *textDrawStringVtx(Gfx *dl, s16 font, s16 x, s16 y, const u8 *str, u8 flags) {
    u8 line;
    u8 idx;
    u8 ch;
    s16 startX;
    const u8 *strStart;
    s32 i;
    Vtx *vp;
    s32 len;
    Vtx *batch;
    s8 leftPad;
    u8 center;
    u8 started;
    s32 count;

    idx = 0;
    startX = x;
    count = 0;
    center = 0;
    strStart = str;
    len = textCountNonSpace(str);
    if (len == 0) {
        return dl;
    }
    vp = heapAlloc(len << 6);
    heapFreeDeferred(vp);
    batch = vp;
    if (flags & 0x80) {
        flags &= ~0x80;
        x = x - textGetStringWidth(font, str) * 2;
        startX = x;
    }
    if (font & 0x80) {
        font ^= 0x80;
        center = 1;
    }
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    if (!(flags & 4)) {
        gSPMatrix(dl++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    }
    if (flags & 0x12) {
        gDPPipeSync(dl++);
        gDPSetCombineMode(dl++, G_CC_MODULATERGBA, G_CC_MODULATERGBA);
    }
    if (flags & 0x20) {
        gDPPipeSync(dl++);
        gDPSetCombineMode(dl++, G_CC_MODULATEIA, G_CC_MODULATEIA_PRIM2);
    }
    if (flags & 1) {
        gSPMatrix(dl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    dl = gfxInit2DDisplayList(dl);
    for (line = 1; line < gTextFonts[font].lineCount + 1; line++) {
        gDPPipeSync(dl++);
        started = 0;
        ch = *str++;
        if (ch) {
            do {
                if (ch != 0x20) {
                    s8 yoff;
                    s16 w4;
                    s16 h4;
                    s16 gx;
                    s16 w;
                    s16 h;

                    yoff = textMapCharToGlyph(font, &ch) * 4;
                    w4 = gTextGlyphTables[font][ch].width * 4;
                    h4 = gTextFonts[font].height * 4;
                    gx = gTextGlyphTables[font][ch].texX;
                    w = gTextGlyphTables[font][ch].width;
                    h = gTextFonts[font].height;
                    if (center) {
                        leftPad = ((gTextFonts[font].fixedWidth * 4 - w4) / 2 < 0) ? 0 : (gTextFonts[font].fixedWidth * 4 - w4) / 2;
                        x += leftPad;
                    }
                    if (ch >= gTextFontLineStarts[font][line - 1] && ch < gTextFontLineStarts[font][line]) {
                        if (started == 0) {
                            dl = textLoadFontSheetGfx(dl, font, line);
                            started = 1;
                        }
                        vp->v.ob[0] = x;
                        vp->v.ob[1] = yoff + y + h4 - 1;
                        vp->v.ob[2] = -5;
                        vp->v.tc[0] = gx << 6; vp->v.tc[1] = h << 6; // LAYOUT: one line lets as1 store tc[1] before tc[0]
                        vp++;
                        vp->v.ob[0] = x + w4 - 1;
                        vp->v.ob[1] = yoff + y + h4 - 1;
                        vp->v.ob[2] = -5;
                        vp->v.tc[0] = (gx + w) << 6;
                        vp->v.tc[1] = h << 6;
                        vp++;
                        vp->v.ob[0] = x + w4 - 1;
                        vp->v.ob[1] = yoff + y;
                        vp->v.ob[2] = -5;
                        vp->v.tc[0] = (gx + w) << 6;
                        vp->v.tc[1] = 0;
                        vp++;
                        vp->v.ob[1] = yoff + y;
                        vp->v.ob[0] = x;
                        vp->v.ob[2] = -5;
                        vp->v.tc[0] = gx << 6;
                        vp->v.tc[1] = 0;
                        vp++;
                        if (flags & 0x32) {
                            vtxSetQuadGradientColors(vp - 4, idx, flags);
                        }
                        count += 4;
                        if (count >= 0x20) {
                            gSPVertex(dl++, osVirtualToPhysical(batch), 0x20, 0);
                            i = count /= 4; // FAKE: dead store to count (reset to 0 below) keeps the quad counter's divide in the target registers
                            while (i-- > 0) {
                                gSP1Quadrangle(dl++, i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3, 0);
                            }
                            count = 0;
                            batch = vp;
                        }
                    }
                    if (center) {
                        x += (w4 < gTextFonts[font].fixedWidth * 4) ? w4 : gTextFonts[font].fixedWidth * 4;
                        if (w4 < gTextFonts[font].fixedWidth * 4) {
                            x += gTextFonts[font].fixedWidth * 4 - leftPad - w4;
                        }
                    } else {
                        x += (gTextGlyphTables[font][ch].width + gTextFonts[font].spacing) * 4;
                    }
                } else if (center) {
                    x += gTextFonts[font].fixedWidth * 4;
                } else {
                    x += gTextFonts[font].spaceWidth * 4;
                }
                idx++;
                ch = *str++;
            } while (ch);
            idx = 0;
        }
        x = startX;
        if (count != 0) {
            gSPVertex(dl++, osVirtualToPhysical(batch), count, 0);
            batch = vp;
            i = count /= 4; // FAKE: dead store to count (reset to 0 below) keeps the quad counter's divide in the target registers
            while (i-- > 0) {
                gSP1Quadrangle(dl++, i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3, 0);
            }
            count = 0;
        }
        str = strStart;
    }
    gDPPipeSync(dl++);
    return dl;
}

extern Mtx D_2000000;
extern Mtx D_2000080;

extern Mtx D_2000200[];

Gfx *textObjectDrawFlat(Gfx *dl, TextObject *textObj) {
    s32 line;
    u8 chr;
    u8 started;
    s32 idx;
    Vtx *vp;
    Vtx *vtxBase;
    Mtx *mp;
    s32 i;
    s32 gw;
    s32 gx;
    s32 gh;

    idx = 0;
    vp = heapAlloc(textObj->count << 6);
    heapFreeDeferred(vp);
    mp = heapAlloc(textObj->count << 6);
    heapFreeDeferred(mp);
    vtxBase = vp;
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    dl = playerViewSetPrimaryViewport(dl);
    for (line = 1; line < gTextFonts[textObj->font].lineCount + 1; line++) {
        started = 0;
        i = 1;
        chr = textObj->text[0];
        if (chr) {
            do {
                if (chr != 0x20) {
                    textMapCharToGlyph(textObj->font, &chr);
                    if (chr >= gTextFontLineStarts[textObj->font][line - 1] && chr < gTextFontLineStarts[textObj->font][line]) {
                        gw = gTextGlyphTables[textObj->font][chr].width;
                        gx = gTextGlyphTables[textObj->font][chr].texX;
                        gh = gTextFonts[textObj->font].height;
                        if (started == 0) {
                            started = 1;
                            dl = textLoadFontSheetGfx(dl, textObj->font, line);
                        }
                        guPosition(mp + idx, 0.0f, 0.0f, textObj->elems[idx].rotZ * 57.295776f, textObj->elems[idx].scale,
                                   textObj->elems[idx].x, textObj->elems[idx].y, 0.0f);
                        gSPMatrix(dl++, mp + idx, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                        gDPPipeSync(dl++);
                        vp->v.ob[0] = -(gw * 2); vp->v.ob[1] = gh * 2 - 1; vp->v.ob[2] = -5; // LAYOUT: one line keeps as1's ob store order
                        vp->v.tc[0] = gx << 6;
                        vp->v.tc[1] = gh << 6;
                        vp++;
                        vp->v.ob[0] = gw * 2 - 1;
                        vp->v.ob[1] = gh * 2 - 1;
                        vp->v.ob[2] = -5;
                        vp->v.tc[0] = (gx + gw) << 6;
                        vp->v.tc[1] = gh << 6;
                        vp++;
                        vp->v.ob[1] = -(gh * 2);
                        vp->v.ob[0] = gw * 2 - 1;
                        vp->v.ob[2] = -5;
                        vp->v.tc[0] = (gx + gw) << 6;
                        vp->v.tc[1] = 0;
                        vp++;
                        vp->v.ob[1] = -(gh * 2);
                        vp->v.ob[0] = -(gw * 2);
                        vp->v.ob[2] = -5;
                        vp->v.tc[0] = gx << 6;
                        vp->v.tc[1] = 0;
                        vp++;
                        gSPVertex(dl++, osVirtualToPhysical(vtxBase), 4, 0);
                        gSP1Quadrangle(dl++, 0, 1, 2, 3, 0);
                        gSPPopMatrix(dl++, G_MTX_MODELVIEW);
                        vtxBase = vp;
                    }
                    idx++;
                }
                chr = textObj->text[i++];
            } while (chr);
            idx = 0;
        }
    }
    gSPMatrix(dl++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(dl++, D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gDPPipeSync(dl++);
    return dl;
}

Gfx *textObjectDrawRotated(Gfx *dl, TextObject *textObj) {
    s32 line;
    u8 chr;
    u8 started;
    s32 idx;
    Vtx *vp;
    Vtx *vtxBase;
    Mtx *mp;
    s32 i;
    s32 gw;
    s32 gx;
    s32 gh;
    f32 pad[2];

    idx = 0;
    vp = heapAlloc(textObj->count << 6);
    heapFreeDeferred(vp);
    mp = heapAlloc(textObj->count << 6);
    heapFreeDeferred(mp);
    vtxBase = vp;
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    gSPMatrix(dl++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(dl++, D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(dl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    for (line = 1; line < gTextFonts[textObj->font].lineCount + 1; line++) {
        started = 0;
        i = 1;
        chr = textObj->text[0];
        if (chr) {
            do {
                if (chr != 0x20) {
                    textMapCharToGlyph(textObj->font, &chr);
                    if (chr >= gTextFontLineStarts[textObj->font][line - 1] && chr < gTextFontLineStarts[textObj->font][line]) {
                        gw = gTextGlyphTables[textObj->font][chr].width;
                        gx = gTextGlyphTables[textObj->font][chr].texX;
                        gh = gTextFonts[textObj->font].height;
                        if (started == 0) {
                            started = 1;
                            dl = textLoadFontSheetGfx(dl, textObj->font, line);
                        }
                        guPosition(mp + idx, textObj->elems[idx].rotX * 57.295776f,
                                   textObj->elems[idx].rotY * 57.295776f, textObj->elems[idx].rotZ * 57.295776f,
                                   textObj->elems[idx].scale, textObj->elems[idx].x, textObj->elems[idx].y,
                                   textObj->elems[idx].z);
                        gSPMatrix(dl++, mp + idx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        gDPPipeSync(dl++);
                        vp->v.ob[0] = -(gw * 2); vp->v.ob[1] = gh * 2 - 1; vp->v.ob[2] = 0; // LAYOUT: one line keeps as1's ob store order
                        vp->v.tc[0] = gx << 6;
                        vp->v.tc[1] = gh << 6;
                        vp++;
                        vp->v.ob[0] = gw * 2 - 1;
                        vp->v.ob[1] = gh * 2 - 1;
                        vp->v.ob[2] = 0;
                        vp->v.tc[0] = (gx + gw) << 6;
                        vp->v.tc[1] = gh << 6;
                        vp++;
                        vp->v.ob[1] = -(gh * 2);
                        vp->v.ob[0] = gw * 2 - 1;
                        vp->v.ob[2] = 0;
                        vp->v.tc[0] = (gx + gw) << 6;
                        vp->v.tc[1] = 0;
                        vp++;
                        vp->v.ob[1] = -(gh * 2);
                        vp->v.ob[0] = -(gw * 2);
                        vp->v.ob[2] = 0;
                        vp->v.tc[0] = gx << 6;
                        vp->v.tc[1] = 0;
                        vp++;
                        gSPVertex(dl++, osVirtualToPhysical(vtxBase), 4, 0);
                        gSP1Quadrangle(dl++, 0, 1, 2, 3, 0);
                        vtxBase = vp;
                    }
                    idx++;
                }
                chr = textObj->text[i++];
            } while (chr);
            idx = 0;
        }
    }
    gDPPipeSync(dl++);
    return dl;
}

Gfx *textDrawString(Gfx *dl, u8 font, s16 x, s16 y, const u8 *str) {
    u8 ch;
    s32 flag;

    flag = 0;
    if (font & 0x80) {
        flag = 1;
        font = font ^ 0x80;
    }
    gDPPipeSync(dl++);
    gDPSetTextureFilter(dl++, G_TF_POINT);
    gSPMatrix(dl++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(dl++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetTexturePersp(dl++, G_TP_NONE);
    dl = textLoadFontSheetGfx(dl, font, 1);
    ch = *str++;
    while (ch) {
        if (ch != 0x20) {
            textMapCharToGlyph(font, &ch);
            gSPTextureRectangle(dl++, x << 2, y << 2, (x + gTextGlyphTables[font][ch].width) << 2, (gTextFonts[font].height + y) << 2, 0, gTextGlyphTables[font][ch].texX << 5, 0, 0x400, 0x400);
            if (flag != 0) {
                x += gTextFonts[font].fixedWidth;
            } else {
                x += gTextGlyphTables[font][ch].width + gTextFonts[font].spacing;
            }
        } else if (flag != 0) {
            x += gTextFonts[font].fixedWidth;
        } else {
            x += gTextFonts[font].spaceWidth;
        }
        ch = *str++;
    }
    gDPPipeSync(dl++);
    gSPMatrix(dl++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetTexturePersp(dl++, G_TP_PERSP);
    return dl;
}

s16 textGetCharAdvance(s16 font, u8 ch) {
    s16 advance;
    TextFontInfo *info;

    if (font & 0x80) {
        font ^= 0x80;
        advance = gTextFonts[font].fixedWidth;
        info = &gTextFonts[font];
    } else if (ch == ' ') {
        advance = gTextFonts[font].spaceWidth;
        info = &gTextFonts[font];
    } else {
        textMapCharToGlyph(font, &ch);
        advance = gTextGlyphTables[font][ch].width;
        info = &gTextFonts[font];
    }
    advance += info->spacing;
    return advance;
}

u8 textGetFontHeight(s16 font) {
    if (font & 0x80) {
        font ^= 0x80;
    }
    return gTextFonts[font].height;
}
