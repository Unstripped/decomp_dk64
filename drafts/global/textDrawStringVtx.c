// textDrawStringVtx (src/global/100180.c): Stage 6: parked NON_MATCHING; full=197 shape=77 (493 vs 490 lines). vtxSetQuadGradientColors has 3 params (definition in 103AB0.c, target passes a0-a2 only): the old 4th arg yoff was a phantom that pinned yoff to a3; replaced by trailing dead 'if (yoff && yoff) {}' after the line loop (FAKE, same score 197/77). Target spills around textLoadFontSheetGfx: yoff 131(sp) h4 126 w 122 h 120 (a3,t0,t1,t2) + t3 at 88, flags at 92, fi in a reg; mine spills fi (108) and 64/72/84. Callee void<->s32 toggles (heapFreeDeferred, vtxSet) no effect. deadsweep rounds incl. 25 locals: no improvement.
extern Mtx D_20000C0;
extern Gfx D_2000180;
Gfx *textLoadFontSheetGfx(Gfx *, u8, s32);
void heapFreeDeferred(void *);
Gfx *func_805FD030(Gfx *);
void vtxSetQuadGradientColors(void *, u8, u8);

#define TEXT_GFX_CMD(g, a, b) \
    { (g) = (Gfx *)(dl++); (g)->words.w0 = (a); (g)->words.w1 = (b); }
#define TEXT_GFX_QUAD(g, v0, v1, v2, v3) \
    TEXT_GFX_CMD(g, (_SHIFTL(G_QUAD, 24, 8) | __gsSP1Quadrangle_w1f(v0, v1, v2, v3, 0)), __gsSP1Quadrangle_w2f(v0, v1, v2, v3, 0))
#define TEXT_GFX_VTX(g, v, n, v0) \
    TEXT_GFX_CMD(g, _SHIFTL(G_VTX, 24, 8) | _SHIFTL((n), 12, 8) | _SHIFTL((v0) + (n), 1, 7), (unsigned int)(v))

// deadsweep round 1: full=197 text=197 inserted `if (yoff && yoff) {}` at line 182
Gfx *textDrawStringVtx(Gfx *dl, s16 font, s16 x, s16 y, u8 *str, u8 flags) {
    u8 line;
    u8 idx;
    u8 ch;
    s16 startX;
    u8 *strStart;
    Gfx *g1;
    Gfx *g2;
    Gfx *g3;
    Vtx *batch;
    s8 pad;
    u8 center;
    u8 started;
    Gfx *g4;
    Gfx *g5;
    Gfx *g6;
    Gfx *g8;
    Gfx *g9;
    Gfx *g10;
    Gfx *g11;
    s8 yoff;
    s16 gx;
    s16 h4;
    s16 w4;
    s16 w;
    s16 h;
    s32 count;
    s32 i;
    s32 len;
    s32 tmp;
    u8 *fi;
    u8 *glyph;
    Vtx *vp;
    s16 *v;

    idx = 0;
    startX = x;
    count = 0;
    center = 0;
    strStart = str;
    len = textCountNonSpace(str);
    if (len == 0) {
        return dl;
    }
    vp = (Vtx *)heapAlloc(len << 6);
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
    TEXT_GFX_CMD(g1, 0xE3001201, 0x2000);
    if (!(flags & 4)) {
        TEXT_GFX_CMD(g2, 0xDA380007, (u32)&D_20000C0);
    }
    if (flags & 0x12) {
        TEXT_GFX_CMD(g3, 0xE7000000, 0);
        TEXT_GFX_CMD(g4, 0xFC121824, 0xFF33FFFF);
    }
    if (flags & 0x20) {
        TEXT_GFX_CMD(g5, 0xE7000000, 0);
        TEXT_GFX_CMD(g6, 0xFC121803, 0xFF0FFFFF);
    }
    if (flags & 1) {
        TEXT_GFX_CMD(g3, 0xDA380003, (u32)&D_2000180);
    }
    dl = func_805FD030(dl);
    fi = D_80754A34 + font * 6;
    line = 1;
    if (fi[1] + 1 >= 2) {
        do {
            TEXT_GFX_CMD(g8, 0xE7000000, 0);
            started = 0;
            ch = *str++;
            if (ch) {
                do {
                    if (ch != 0x20) {
                        yoff = textMapCharToGlyph(font, &ch) * 4;
                        glyph = (u8 *)((u8 **)D_80754A18)[font] + ch * 4;
                        w4 = glyph[2];
                        h4 = fi[2];
                        w = w4;
                        h = h4;
                        w4 = w4 * 4;
                        if (count && count) {}
                        if (count && count) {}
                        h4 = h4 * 4;
                        gx = *(s16 *)glyph;
                        if (center) {
                            tmp = (fi[5] * 4 - w4) / 2;
                            if (tmp < 0) {
                                if (yoff == 0) {}
                                pad = 0;
                            } else {
                                pad = tmp;
                            }
                            x += pad;
                        }
                        if (ch >= D_807549FC[font][line - 1] && ch < D_807549FC[font][line]) {
                            if (started == 0) {
                                started = 1;
                                dl = textLoadFontSheetGfx(dl, font, (s16)line);
                            }
                            v = (s16 *)vp;
                            v[0] = x;
                            v[1] = yoff + y + h4 - 1;
                            v[9] = yoff + y + h4 - 1;
                            v[2] = -5;
                            v[4] = gx << 6;
                            v[5] = h << 6;
                            v[8] = x + w4 - 1;
                            v[10] = -5;
                            v[12] = (gx + w) << 6;
                            v[13] = h << 6;
                            v[16] = x + w4 - 1;
                            v[17] = yoff + y;
                            v[18] = -5;
                            v[20] = (gx + w) << 6;
                            v[21] = 0;
                            v[25] = yoff + y;
                            v[24] = x;
                            v[26] = -5;
                            v[28] = gx << 6;
                            if (count && count) {}
                            v[29] = 0;
                            vp++;
                            vp++;
                            vp++;
                            vp++;
                            if (flags & 0x32) {
                                vtxSetQuadGradientColors(vp - 4, idx, flags);
                            }
                            count += 4;
                            if (count >= 0x20) {
                                TEXT_GFX_VTX(g9, osVirtualToPhysical(batch), 0x20, 0);
                                i = count / 4;
                                while (i-- > 0) {
                                    TEXT_GFX_QUAD(g10, i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3);
                                }
                                count = 0;
                                batch = vp;
                            }
                        }
                        if (center) {
                            tmp = fi[5] * 4;
                            x += (w4 < tmp) ? w4 : tmp;
                            if (w4 < tmp) {
                                x = x + tmp - pad - w4;
                            }
                        } else {
                            x += (((u8 **)D_80754A18)[font][ch * 4 + 2] + fi[4]) * 4;
                        }
                    } else if (center) {
                        x += fi[5] * 4;
                    } else {
                        x += fi[3] * 4;
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
                i = count / 4;
                while (i-- > 0) {
                    TEXT_GFX_QUAD(g1, i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3);
                }
                if (count) {}
                count = 0;
            }
            str = strStart;
            line++;
        } while (line < fi[1] + 1);
        if (yoff && yoff) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    TEXT_GFX_CMD(g1, 0xE7000000, 0);
    return dl;
}
