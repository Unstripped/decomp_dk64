// textDrawStringVtx (src/global/100180.c): stage 6: R12_fable_5 (base f826d6ee) as1-XBB survey: park full=165 text=165 reloc=0 shape=55 is unchanged under as1 candidate-limit variants L0/L1/L2/L3/L5/L10/L20 (all 165); -xbbdbg 31 lists 25 moves, all between loop-adjacent blocks (in-loop limit-100 regime), so no hunk is an as1 function-level hoist and Q0548 guards cannot steer it; the diff is uopt's callee-save rotation (s2/s4/s6, h4 vs line spill) as noted. Pure colouring: no C changed, park kept. | Prior: stage 6: R11_textDrawStringVtx (base 9d6acd9dc66f1deacad36794631e27332c87412b): retained stage-6 park full=165 text=165 reloc=0 shape=55, 470 insns/frame 0xC8. Dissected uopt candidate register coloring via -l5/-l6 and as1probe: discovered that the core remaining diff is a 4-way callee-save rotation (s2=h4, s4=gx, s6=0x07000000, line spilled to stack in built vs s2=gx, s4=0x07000000, s6=line, h4 homed at 126($sp) in target). In target, all 9 callee-saves (s0=dl, s1=vp, s2=gx, s3=w4, s4=0x07000000, s5=x, s6=line, s7=font-ptr/flags, fp=count) are fully occupied, forcing h4 to spill to 126($sp); in built, uopt assigns s2 to h4 (cand 153, adjsave 75.0), pushing gx->s4, 0x07000000->s6, and displacing line out of s6 into stack, leaving fp unused and count assigned to s6 (cand 8, adjsave 58.0). Replacing TEXT_GFX_CMD dummy g* pointers with direct dl updates collapses stack frame (full 338). as1probe scan confirmed no single-record as1 reordering bridges the register allocation gap. Exact stage-6 park fdiff OK. | Prior: stage 6 park: 470 instructions / 1880 bytes, frame 0xC8 and saved-register set exact; normalized full=165 text=165 reloc=0 shape=55 (490 lines incl relocations), improved from full=192/shape=72. Plain fdiff CURRENT (5936); .text built/expected 9312 bytes. w/h s16; count/i s32; fi direct font-table expression removes home; reordered yoff/w/h homes plus padFrame. Five baseline FAKEs and four-arg gradient prototype retained: correcting phantom arity alone or in grids regresses. Tried scalar/type/arity combinations, all FAKE subsets, yoff reuse/narrowing, glyph inlining, width assignment forms, stack-home arrangements, bounded live-range probes, scaled-height lifetime/CSE forms. Permuter -j2 --seconds600 best7079 vs7919 baseline had invalid conditional height scaling; other leading hints corrupt h4 or strStart; safe height-motion adaptations worsen165->186+. No better equivalent candidate found. Input prior note incorrectly claimed changes absent from its stored C body.
extern Mtx D_20000C0;
extern Gfx D_2000180;
Gfx *textLoadFontSheetGfx(Gfx *, u8, s32);
void heapFreeDeferred(void *);
Gfx *gfxInit2DDisplayList(Gfx *);
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
    Gfx *g12;
    Gfx *g6;
    Vtx *batch;
    s8 pad;
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
    u8 *glyph;
    s16 *v;
    s32 count;
    Gfx *g11;
    s32 padFrame;

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
    dl = gfxInit2DDisplayList(dl);
    line = 1;
    if (D_80754A34[font * 6 + 1] + 1 >= 2) {
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
                        h4 = D_80754A34[font * 6 + 2];
                        w = w4;
                        h = h4;
                        w4 = w4 * 4;
                        if (count && count) {} // FAKE: count web
                        if (count && count) {} // FAKE: count web
                        h4 = h4 * 4;
                        gx = *(s16 *)glyph;
                        if (center) {
                            tmp = (D_80754A34[font * 6 + 5] * 4 - w4) / 2;
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
                            tmp = D_80754A34[font * 6 + 5] * 4;
                            x += (w4 < tmp) ? w4 : tmp;
                            if (w4 < tmp) {
                                x = x + tmp - pad - w4;
                            }
                        } else {
                            x += (((u8 **)D_80754A18)[font][ch * 4 + 2] + D_80754A34[font * 6 + 4]) * 4;
                        }
                    } else if (center) {
                        x += D_80754A34[font * 6 + 5] * 4;
                    } else {
                        x += D_80754A34[font * 6 + 3] * 4;
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
        } while (line < D_80754A34[font * 6 + 1] + 1);
    }
    TEXT_GFX_CMD(g1, 0xE7000000, 0);
    return dl;
}
