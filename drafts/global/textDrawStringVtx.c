// textDrawStringVtx (src/global/100180.c): stage 6 park 192/490 (count+frame exact). Re-derived: remaining diff = (1) fi (u8*) local gets a 120(sp) home store + extra lw; expected keeps it only as expression spilled at 88(sp) around calls; (2) yoff memory-resident (sb 160(sp)) where expected keeps it in a3 via move a3,v0; sll 26; sra 24; (3) line copy: expected lbu s6,199(sp) (callee-saved) before textMapCharToGlyph, 0x7000000 in s4; ours const in s6 and line copy a3 spilled; (4) vtxSetQuadGradientColors real def has 3 params: expected passes no a3 (park passes yoff as phantom 4th arg). Tried revisit8: i as s32 (184 but count 488), macro FI instead of fi local (+pads), per-local type grid, yoff via gi temp, line/center/tmp/len types, loop-form spellings, 3 anneals of dead tests/decl order/alt spellings: none beat 192 at count 490
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
    s8 pad;
    u8 center;
    u8 started;
    Gfx *g10;
    s16 w4;
    u8 h;
    s8 yoff;
    u32 i;
    Vtx *vp;
    Gfx *g8;
    s32 len;
    s32 tmp;
    Gfx *g7;
    Gfx *g3;
    u8 w;
    s16 h4;
    s16 gx;
    u8 *fi;
    u8 *glyph;
    Gfx *g2;
    s16 *v;
    s16 count;
    Gfx *g11;

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
                        if (count && count) {} // FAKE: count web
                        if (count && count) {} // FAKE: count web
                        h4 = h4 * 4;
                        gx = *(s16 *)glyph;
                        if (center) {
                            tmp = (fi[5] * 4 - w4) / 2;
                            if (tmp < 0) {
                                if (yoff == 0) {} // FAKE: yoff web
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
                            if (count && count) {} // FAKE: count web
                            v[29] = 0;
                            vp++;
                            vp++;
                            vp++;
                            vp++;
                            if (flags & 0x32) {
                                vtxSetQuadGradientColors(vp - 4, idx, flags, yoff);
                            }
                            count += 4;
                            if (count >= 0x20) {
                                TEXT_GFX_VTX(g7, osVirtualToPhysical(batch), 0x20, 0);
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
                if (count) {} // FAKE: count web
                count = 0;
            }
            str = strStart;
            line++;
        } while (line < fi[1] + 1);
    }
    TEXT_GFX_CMD(g1, 0xE7000000, 0);
    return dl;
}
