#include "common.h"
#define PROTO_SKIP_assetLoad // FAKE: callee prototype steer
#include "actor.h"
#include "text.h"
#include "proto/boot/3630.h"
#include "proto/global/100180.h"
#include "proto/global/103AB0.h"
#include "proto/global/15050.h"
#include "proto/global/450.h"
#include "proto/global/6AD90.h"

void func_806FB480(void) {
}

void textBlitNoop100180(void) {
}

s32 textBlitGlyph(u8 width, s32 dst, s32 sheet, s16 texX, u8 row, u8 *phase, u8 pitch) {
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
    src = (u8 *)sheet;
    srcRow = (u8 *)sheet + (texX >> 1);
    oddBit = width & 1;
    phaseBit = *phase & 1;
    dstRow = (u8 *)(dst + pitch * 16 + pitch * row);
    out = dstRow;
    *phase += width;
    width >>= 1;
    for (y = 0; y < 0x10; y++) {
        j = 0;
        if (width > 0) {
            srcOdd = texX & 1;
            do {
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
                j++;
            } while (j < width);
        }
        srcRow += 0x100;
        if (oddBit) {
            srcOdd = texX & 1;
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
    return (phaseBit && oddBit) + dst + (u32)width; // FAKE: the u32 widening shares width's masked copy (andi t3,a0,0xff) with the loop bound
}

typedef struct TextGlyph {
    s16 texX;
    u8 width;
    u8 unk3;
} TextGlyph;

extern TextGlyph *gTextGlyphTables[];
extern void **gTextFontSheets;
extern TextFontInfo gTextFonts[];
extern u8 *gTextFontLineStarts[];

void textBlitString(s32 dst, u8 pitch, u8 *str) {
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
                    dst = textBlitGlyph(gTextGlyphTables[0][ch].width, dst, (s32)gTextFontSheets[i - 1], gTextGlyphTables[0][ch].texX, row, &phase, pitch);
                }
            }
        } else {
            dst += 3;
            phase += 6;
        }
        ch = *str++;
    }
}

void textBlitDash(s32 dst) {
    u8 phase;

    phase = 0;
    textFontLoadSheet(2);
    textBlitGlyph(gTextGlyphTables[0][0x5F].width, dst, (s32)gTextFontSheets[2], gTextGlyphTables[0][0x5F].texX, 2,
                  &phase, 0x30);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/D_8075DC20.s")

typedef struct { u8 b[0x39]; } FcDStr39;
typedef struct { u8 b[0x30]; } FcDStr30;
typedef struct { u8 b[0x3A]; } FcDStr3A;

extern FcDStr39 D_80754A64;
extern FcDStr30 D_80754AA0;
extern FcDStr3A D_8075DC20;

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

void *assetLoad(s32, s16, u8, s32);  // FAKE: callee prototype steer

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

s32 textGetStringWidth(font, str)
s16 font;
u8 *str;
{
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

s16 textCountNonSpace(u8 *str) {
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

#define TEXT_GFX_CMD(g, a, b) \
    { (g) = dl++; (g)->words.w0 = (a); (g)->words.w1 = (b); } // FAKE: function-scope Gfx temps (g8 shared by three commands) instead of gbi's block-scoped _g steer regalloc
#define TEXT_GFX_QUAD(g, v0, v1, v2, v3) \
    TEXT_GFX_CMD(g, (_SHIFTL(G_QUAD, 24, 8) | __gsSP1Quadrangle_w1f(v0, v1, v2, v3, 0)), __gsSP1Quadrangle_w2f(v0, v1, v2, v3, 0))
#define TEXT_GFX_VTX(g, v, n, v0) \
    TEXT_GFX_CMD(g, _SHIFTL(G_VTX, 24, 8) | _SHIFTL((n), 12, 8) | _SHIFTL((v0) + (n), 1, 7), (unsigned int)(v))

Gfx *textDrawStringVtx(Gfx *dl, s16 font, s16 x, s16 y, u8 *str, u8 flags) {
    u8 line;
    u8 idx;
    u8 ch;
    s16 startX;
    u8 *strStart;
    Gfx *g1;
    Gfx *g12;
    Gfx *g6;
    Vtx *batch;
    s8 leftPad;
    u8 center;
    u8 started;
    Gfx *g10;
    s32 i;
    Vtx *vp;
    Gfx *g8;
    s32 len;
    s32 tmp;
    Gfx *g7;
    Gfx *g3;
    Gfx *g2;
    s8 yoff;
    s16 w4;
    s16 h4;
    s16 gx;
    s16 w;
    s16 h;
    TextGlyph *glyph;
    s32 pad2;
    s32 count;
    Gfx *g11;
    s32 pad3;

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
    TEXT_GFX_CMD(g8, 0xE3001201, 0x2000);
    if (!(flags & 4)) {
        TEXT_GFX_CMD(g8, 0xDA380007, (u32)&D_20000C0);
    }
    if (flags & 0x12) {
        TEXT_GFX_CMD(g3, 0xE7000000, 0);
        TEXT_GFX_CMD(g12, 0xFC121824, 0xFF33FFFF);
    }
    if (flags & 0x20) {
        TEXT_GFX_CMD(g2, 0xE7000000, 0);
        TEXT_GFX_CMD(g6, 0xFC121803, 0xFF0FFFFF);
    }
    if (flags & 1) {
        TEXT_GFX_CMD(g3, 0xDA380003, (u32)&D_2000180);
    }
    dl = gfxInit2DDisplayList(dl);
    for (line = 1; line < gTextFonts[font].lineCount + 1; line++) {
        TEXT_GFX_CMD(g8, 0xE7000000, 0);
        started = 0;
        ch = *str++;
        if (ch) {
            do {
                if (ch != 0x20) {
                    yoff = textMapCharToGlyph(font, &ch) * 4;
                    glyph = &gTextGlyphTables[font][ch];
                    w4 = glyph->width * 4;
                    h4 = gTextFonts[font].height * 4;
                    gx = glyph->texX;
                    w = glyph->width;
                    h = gTextFonts[font].height;
                    if (center) {
                        tmp = (gTextFonts[font].fixedWidth * 4 - w4) / 2;
                        leftPad = (tmp < 0) ? 0 : tmp;
                        x += leftPad;
                    }
                    if (ch >= gTextFontLineStarts[font][line - 1] && ch < gTextFontLineStarts[font][line]) {
                        if (started == 0) {
                            dl = textLoadFontSheetGfx(dl, font, line);
                            started = 1;
                        }
                        vp[0].v.ob[0] = x;
                        vp[0].v.ob[1] = yoff + y + h4 - 1;
                        vp[1].v.ob[1] = yoff + y + h4 - 1;
                        vp[0].v.ob[2] = -5;
                        vp[0].v.tc[0] = gx << 6; vp[0].v.tc[1] = h << 6; // LAYOUT: one line lets as1 store tc[1] before tc[0]
                        vp[1].v.ob[0] = x + w4 - 1;
                        vp[1].v.ob[2] = -5;
                        if (w4) {} // FAKE: splits the vertex block so its first and last temps share v0
                        vp[1].v.tc[0] = (gx + w) << 6;
                        vp[1].v.tc[1] = h << 6;
                        vp[2].v.ob[0] = x + w4 - 1;
                        vp[2].v.ob[1] = yoff + y;
                        vp[2].v.ob[2] = -5;
                        vp[2].v.tc[0] = (gx + w) << 6;
                        vp[2].v.tc[1] = 0;
                        vp[3].v.ob[1] = yoff + y;
                        vp[3].v.ob[0] = x;
                        vp[3].v.ob[2] = -5;
                        vp[3].v.tc[0] = gx << 6;
                        vp[3].v.tc[1] = 0;
                        vp++; // FAKE: four single increments (not vp += 4) keep the quad's vp steps for uopt
                        vp++;
                        vp++;
                        vp++;
                        if (flags & 0x32) {
                            vtxSetQuadGradientColors(vp - 4, idx, flags);
                        }
                        count += 4;
                        if (count >= 0x20) {
                            TEXT_GFX_VTX(g7, osVirtualToPhysical(batch), 0x20, 0);
                            i = count /= 4; // FAKE: dead store to count (reset to 0 below) keeps the quad counter's divide in the target registers
                            while (i-- > 0) {
                                TEXT_GFX_QUAD(g10, i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3);
                            }
                            count = 0;
                            batch = vp;
                        }
                    }
                    if (center) {
                        tmp = gTextFonts[font].fixedWidth * 4;
                        x += (w4 < tmp) ? w4 : tmp;
                        if (w4 < tmp) {
                            x = x + tmp - leftPad - w4;
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
            TEXT_GFX_VTX(g11, osVirtualToPhysical(batch), count, 0);
            batch = vp;
            i = count /= 4; // FAKE: dead store to count (reset to 0 below) keeps the quad counter's divide in the target registers
            while (i-- > 0) {
                TEXT_GFX_QUAD(g8, i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3);
            }
            count = 0;
        }
        str = strStart;
    }
    TEXT_GFX_CMD(g1, 0xE7000000, 0);
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
    dl = func_8070068C(dl);
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
                        vp[0].v.ob[0] = -(gw * 2); vp[0].v.ob[1] = gh * 2 - 1; vp[0].v.ob[2] = -5; // LAYOUT: one line keeps as1's ob store order
                        vp[0].v.tc[0] = gx << 6;
                        vp[0].v.tc[1] = gh << 6;
                        if (D_2000200) {} // FAKE: deadsweep class 1 dead statement (no rewrite matched)
                        vp[1].v.ob[0] = gw * 2 - 1;
                        vp[1].v.ob[1] = gh * 2 - 1;
                        vp[1].v.ob[2] = -5;
                        vp[1].v.tc[0] = (gx + gw) << 6;
                        vp[1].v.tc[1] = gh << 6;
                        vp[2].v.ob[1] = -(gh * 2);
                        vp[2].v.ob[0] = gw * 2 - 1;
                        vp[2].v.ob[2] = -5;
                        vp[2].v.tc[0] = (gx + gw) << 6;
                        vp[2].v.tc[1] = 0;
                        vp[3].v.ob[0] = -(gw * 2); vp[3].v.ob[1] = -(gh * 2); vp[3].v.ob[2] = -5; // LAYOUT: one line keeps as1's ob store order
                        vp[3].v.tc[1] = 0; vp[3].v.tc[0] = gx << 6; // LAYOUT: one line keeps as1 storing tc[1] before tc[0]
                        vp += 4;
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
                        vp[0].v.ob[0] = -(gw * 2); vp[0].v.ob[1] = gh * 2 - 1; vp[0].v.ob[2] = 0; // LAYOUT: one line keeps as1's ob store order
                        vp[0].v.tc[0] = gx << 6;
                        vp[0].v.tc[1] = gh << 6;
                        if (i && i) {} // FAKE: deadsweep class 1 dead statement (no rewrite matched)
                        vp[1].v.ob[0] = gw * 2 - 1;
                        vp[1].v.ob[1] = gh * 2 - 1;
                        vp[1].v.ob[2] = 0;
                        vp[1].v.tc[0] = (gx + gw) << 6;
                        vp[1].v.tc[1] = gh << 6;
                        vp[2].v.ob[1] = -(gh * 2);
                        vp[2].v.ob[0] = gw * 2 - 1;
                        vp[2].v.ob[2] = 0;
                        vp[2].v.tc[0] = (gx + gw) << 6;
                        vp[2].v.tc[1] = 0;
                        vp[3].v.ob[0] = -(gw * 2); vp[3].v.ob[1] = -(gh * 2); vp[3].v.ob[2] = 0; // LAYOUT: one line keeps as1's ob store order
                        vp[3].v.tc[1] = 0; vp[3].v.tc[0] = gx << 6; // LAYOUT: one line keeps as1 storing tc[1] before tc[0]
                        vp += 4;
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

Gfx *textDrawString(Gfx *dl, u8 font, s16 x, s16 y, u8 *str) {
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
    s32 f;
    s16 advance;
    TextFontInfo *info;

    f = font; // FAKE: s32 copy keeps the extended font in a2 (sll a2,a0,0x10) apart from the a0 argument
    if (f & 0x80) {
        info = &gTextFonts[(s16)(f ^ 0x80)];
        advance = info->fixedWidth;
    } else if (ch == ' ') {
        info = &gTextFonts[f];
        advance = info->spaceWidth;
    } else {
        textMapCharToGlyph(f, &ch);
        advance = gTextGlyphTables[f][ch].width;
        info = &gTextFonts[f];
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
