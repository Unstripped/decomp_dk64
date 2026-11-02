// textDrawStringVtx (src/global/100180.c): UNPARKED 2026-11-02: park was 473 insns vs target 470 (count-inexact parks stay drafts); Text R5: stage 6, parked NON_MATCHING; deadsweep score full=183 shape=66 (was 198/78), 493 vs 490 lines; first 126 lines of the objdump now identical (flags spill 92(sp) fixed). Lever: gfx-pointer local sites remapped (hill-climb over which of g1..g12 each TEXT_GFX_* macro site uses, cfe-level homes per declared local shift the uopt spill slots): 'g8,g8,g3,g12,g2,g6,g3,g8,g7,g10,g11,g1,g1'; merge of g5->g2 alone gives 186. Left: fi (t3) spilled at 112 in prologue where target keeps it in t3 until 88; ring numbering t5/t6/t7 vs target t6/t7/t8 after func_805FD030; target spills yoff/h4/w/h at 131/126/122/120. Dead-test hill-climb (38k iters, guards on locals/params), self-store ring steps, FAKE-free decl merges: no further gain.
extern Mtx D_20000C0;
extern Gfx D_2000180;
Gfx *textLoadFontSheetGfx(Gfx *, u8, s32);
void heapFreeDeferred(void *);
Gfx *func_805FD030(Gfx *);
void vtxSetQuadGradientColors(void *, u8, u8, s8);

#define TEXT_GFX_CMD(g, a, b) \
    { (g) = (Gfx *)(dl++); (g)->words.w0 = (a); (g)->words.w1 = (b); }
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
    Gfx *g2;
    Gfx *g3;
    Vtx *batch;
    s8 pad;
    u8 center;
    u8 started;
    Gfx *g6;
    Gfx *g8;
    Gfx *g10;
    Gfx *g11;
    Gfx *g7;
    Gfx *g12;
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
                if (count) {}
                count = 0;
            }
            str = strStart;
            line++;
        } while (line < fi[1] + 1);
    }
    TEXT_GFX_CMD(g1, 0xE7000000, 0);
    return dl;
}
