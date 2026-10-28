#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

void func_806FB480(void) {
}

void func_806FB488(void) {
}

s32 func_806FB490(u8, s32, s32, s16, u8, s8 *, u8);

#ifdef NON_MATCHING
s32 func_806FB490(u8 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s8 *arg5, u8 arg6) {
    u8 *src;
    u8 *srcRow;
    u8 *dst;
    s32 w2;
    s32 phase;
    s32 odd;
    s16 row;
    s16 j;
    u8 *dstRow;
    u8 lead;
    u8 *p5;

    p5 = (u8 *)arg5;
    srcRow = (u8 *)arg2 + (arg3 >> 1);
    dst = (u8 *)(arg6 * 16 + arg1 + arg6 * arg4);
    src = (u8 *)arg2;
    dstRow = dst;
    phase = (*p5 & 1) != 0;
    *p5 += arg0;
    odd = (arg0 & 1) != 0;
    arg0 = arg0 >> 1;
    w2 = arg0;
    row = 0;
    do {
        j = 0;
        if (w2 > 0) {
            lead = arg3 & 1;
            do {
                if (lead && phase == 0) {
                    *dst |= *src++ << 4;
                    *dst++ |= (*src & 0xF0) >> 4;
                } else if (lead && phase != 0) {
                    *dst |= *src++ & 0xF;
                    *++dst |= *src & 0xF0;
                } else if (lead == 0 && phase != 0) {
                    *dst++ |= (*src & 0xF0) >> 4;
                    *dst |= *src++ << 4;
                } else {
                    *dst++ |= *src++;
                }
                j++;
            } while (j < w2);
        }
        srcRow += 0x100;
        if (odd != 0) {
            lead = arg3 & 1;
            if (lead && phase == 0) {
                *dst |= *src << 4;
            } else if (lead && phase != 0) {
                *dst |= *src << 4;
            } else if (lead == 0 && phase != 0) {
                *dst |= (*src & 0xF0) >> 4;
            } else {
                *dst |= *src;
            }
        }
        row++;
        dstRow -= arg6;
        src = srcRow;
        dst = dstRow;
    } while (row < 0x10);
    if (phase != 0) {
        phase = odd;
    }
    return phase + arg1 + arg0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FB490.s")
#endif





typedef struct FcDGlyph {
    s16 unk0;
    u8 unk2;
    u8 unk3;
} FcDGlyph;

typedef struct {
    u8 unk0[0x17C];
    s16 unk17C;
    u8 unk17E;
} R1F100180_Entry;

s32 func_806FB914(s16, u8 *);
void *func_806FBB9C(s16);
extern R1F100180_Entry *D_80754A18[];
extern void *D_807FD7F0;
extern u8 D_80754A35[];
extern u8 *D_807549FC[];

void func_806FB714(s32 arg0, u8 arg1, u8 *arg2) {
    s32 i;
    u8 sp63;
    u8 sp3;
    u8 sp61;

    sp61 = 0;
    sp63 = *arg2++;
    while (sp63) {
        if (sp63 != 32) {
            sp3 = func_806FB914(0, &sp63);
            for (i = 1; i < D_80754A35[0] + 1; i++) {
                if (sp63 >= D_807549FC[0][i - 1] && sp63 < D_807549FC[0][i]) {
                    func_806FBB9C(i - 1);
                    arg0 = func_806FB490(((FcDGlyph *)D_80754A18[0])[sp63].unk2, arg0, ((s32 *)D_807FD7F0)[i - 1], ((FcDGlyph *)D_80754A18[0])[sp63].unk0, sp3, (s8 *)&sp61, arg1);
                }
            }
        } else {
            arg0 += 3;
            sp61 += 6;
        }
        sp63 = *arg2;
        arg2++;
    }
}



typedef struct {
    u8 unk0[8];
    s32 unk8;
} R1F100180_Heap;

void func_806FB8B0(s32 arg0) {
    s8 sp2F;

    sp2F = 0;
    func_806FBB9C(2);
    func_806FB490(D_80754A18[0]->unk17E, arg0, ((R1F100180_Heap *) D_807FD7F0)->unk8, D_80754A18[0]->unk17C, 2,
                  &sp2F, 0x30);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/D_8075DC20.s")

typedef struct { u8 b[0x39]; } FcDStr39;
typedef struct { u8 b[0x30]; } FcDStr30;
typedef struct { u8 b[0x3A]; } FcDStr3A;

extern FcDStr39 D_80754A64;
extern FcDStr30 D_80754AA0;
extern FcDStr3A D_8075DC20;
u8 *_strchr(u8 *, s32);

s32 func_806FB914(s16 arg0, u8 *arg1) {
    s8 spDF;
    FcDStr39 spA4;
    FcDStr30 sp74;
    FcDStr3A sp38;

    spDF = 0;
    switch (arg0) {
    case 0:
        switch (*arg1) {
        case 0x2E:
        case 0x67:
        case 0x70:
        case 0x71:
        case 0x80:
            spDF = 2;
            break;
        case 0x61:
        case 0x79:
            spDF = 1;
            break;
        }
        *arg1 -= 0x21;
        break;
    case 1:
        spA4 = D_80754A64;
        *arg1 = _strchr((u8 *)&spA4, *arg1) - (u8 *)&spA4;
        break;
    case 6:
        sp74 = D_80754AA0;
        *arg1 = _strchr((u8 *)&sp74, *arg1) - (u8 *)&sp74;
        break;
    case 2:
        sp38 = D_8075DC20;
        *arg1 = _strchr((u8 *)&sp38, *arg1) - (u8 *)&sp38;
        break;
    case 3:
    case 7: {
        u8 sp28[] = "0123456789%/";

        *arg1 = _strchr(sp28, *arg1) - sp28;
        break;
    }
    case 4:
        if (*arg1 == 0x40) {
            *arg1 = 0x60;
        } else {
            *arg1 -= 0x21;
        }
        break;
    case 5:
        *arg1 -= 0x21;
        break;
    }
    return spDF;
}

s32 func_80610FE8(s32);
void heapClearBlock(s32);
extern u8 *D_807FD7F4;

void func_806FBB58(void) {
    s32 allocation;
    s32 *allocation_slot;
    s32 temp_v0;
    u8 **heap_buffer;

    D_807FD7F0 = func_80610FE8(0xAC);
    temp_v0 = func_80610FE8(0x2B);
    heap_buffer = &D_807FD7F4;
    allocation_slot = (s32 *)heap_buffer;
    allocation = (*allocation_slot = temp_v0);
    heapClearBlock(allocation);
}

void *func_8066B0F8(s32, s16, u8, s32);


void *func_806FBB9C(s16 arg0) {
    s16 temp_a1;
    s32 var_v1;
    u8 *temp_v0;

    temp_v0 = arg0 + D_807FD7F4;
    temp_a1 = arg0;
    var_v1 = temp_a1 * 4;
    if (*temp_v0 == 0) {
        arg0 = arg0;
        var_v1 = arg0 * 4;
        *(void **)((u8 *) D_807FD7F0 + var_v1) = func_8066B0F8(0xE, temp_a1, 1, 1);
        *(D_807FD7F4 + arg0) = 3;
    } else {
        *temp_v0 = 3;
    }
    return *(void **)((u8 *) D_807FD7F0 + var_v1);
}

extern u8 D_80754A34[];
void assetFreeBuffer(void *, s32, s32);

void func_806FBC34(void) {
    s16 i;
    s16 j;
    s16 n;
    u8 *e;

    n = 0;
    for (i = 0; i < 8; i++) {
        j = 0;
        e = D_80754A34 + i * 6;
        if (e[1] > 0) {
            do {
                if (D_807FD7F4[n++]) {
                    D_807FD7F4[n - 1]--;
                    if (*(u8 *)((s32)D_807FD7F4 + n - 1) == 0) {
                        assetFreeBuffer(((void **)D_807FD7F0)[n - 1], 0x156, 0x23);
                    }
                }
                j++;
            } while (j < e[1]);
        }
    }
}

s32 strlen(u8 *);
extern u8 D_80754A39[];

s32 func_806FBD5C(arg0, arg1)
s16 arg0;
u8 *arg1;
{
    s32 len;
    u8 sp4B;
    s32 step;

    len = 0;
    if (arg0 & 0x80) {
        arg0 ^= 0x80;
        return strlen(arg1) * D_80754A39[arg0 * 6];
    }
    sp4B = *arg1++;
    while (sp4B) {
        if (sp4B == 0x20) {
            len += D_80754A34[arg0 * 6 + 3];
            step = D_80754A34[arg0 * 6 + 4];
        } else {
            func_806FB914(arg0, &sp4B);
            step = D_80754A34[arg0 * 6 + 4];
            len += ((u8 **)D_80754A18)[arg0][sp4B * 4 + 2];
        }
        len += step;
        sp4B = *arg1++;
    }
    return len;
}

s16 func_806FBEAC(u8 *arg0) {
    s16 var_v1;
    u8 temp_v0;

    temp_v0 = *arg0;
    var_v1 = 0;
    arg0 += 1;
    if (temp_v0 != 0) {
        do {
            if (arg0[-1] != 0x20) {
                var_v1 += 1;
            }
            temp_v0 = arg0[0];
            arg0 += 1;
        } while (temp_v0 != 0);
    }
    return var_v1;
}

#define R1F100180_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

/* Loads one font glyph sheet (texture block) for the given font id and line index; case order follows the font id. */
Gfx *func_806FBEF0(Gfx *arg0, u8 arg1, s32 arg2) {
    s16 var_s0;
    u8 *keep_arg1 = &arg1; /* params stay memory resident (home stores, lbu reloads) */
    s32 *keep_arg2 = &arg2;

    s32 line = *keep_arg2;
    var_s0 = D_80754A34[(u8)(arg1 & 0xFF) * 6] + line - 1;
    func_806FBB9C(var_s0);
    switch (arg1) {
    case 6:
        R1F100180_WRITE_GFX(arg0++, 0xFD700000, ((s32 *) D_807FD7F0)[var_s0] + 0x80000000);
        R1F100180_WRITE_GFX(arg0++, 0xF5700000, 0x07080200); R1F100180_WRITE_GFX(arg0++, 0xE6000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF3000000, 0x0747705E); R1F100180_WRITE_GFX(arg0++, 0xE7000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF5682C00, 0x00080200); R1F100180_WRITE_GFX(arg0++, 0xF2000000, 0x002BC030); break;
    case 0:
        R1F100180_WRITE_GFX(arg0++, 0xFD700000, ((s32 *) D_807FD7F0)[var_s0] + 0x80000000);
        R1F100180_WRITE_GFX(arg0++, 0xF5700000, 0x07080200); R1F100180_WRITE_GFX(arg0++, 0xE6000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF3000000, 0x077FF040); R1F100180_WRITE_GFX(arg0++, 0xE7000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF5604000, 0x00080200); R1F100180_WRITE_GFX(arg0++, 0xF2000000, 0x007FC03C); break;
    case 1:
        R1F100180_WRITE_GFX(arg0++, 0xFD100000, ((s32 *) D_807FD7F0)[var_s0] + 0x80000000);
        R1F100180_WRITE_GFX(arg0++, 0xF5100000, 0x07080200); R1F100180_WRITE_GFX(arg0++, 0xE6000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF3000000, 0x0771F06C); R1F100180_WRITE_GFX(arg0++, 0xE7000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF5102600, 0x00080200); R1F100180_WRITE_GFX(arg0++, 0xF2000000, 0x0012C05C); break;
    case 2:
        R1F100180_WRITE_GFX(arg0++, 0xFD900000, ((s32 *) D_807FD7F0)[var_s0] + 0x80000000);
        R1F100180_WRITE_GFX(arg0++, 0xF5900000, 0x07080200); R1F100180_WRITE_GFX(arg0++, 0xE6000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF3000000, 0x073FF040); R1F100180_WRITE_GFX(arg0++, 0xE7000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF5804000, 0x00080200); R1F100180_WRITE_GFX(arg0++, 0xF2000000, 0x007FC01C); break;
    case 3:
    case 7:
        R1F100180_WRITE_GFX(arg0++, 0xFD100000, ((s32 *) D_807FD7F0)[var_s0] + 0x80000000);
        R1F100180_WRITE_GFX(arg0++, 0xF5100000, 0x07080200); R1F100180_WRITE_GFX(arg0++, 0xE6000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF3000000, 0x073FF100); R1F100180_WRITE_GFX(arg0++, 0xE7000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF5101000, 0x00080200); R1F100180_WRITE_GFX(arg0++, 0xF2000000, 0x0007C07C); break;
    case 4:
        R1F100180_WRITE_GFX(arg0++, 0xFD900000, ((s32 *) D_807FD7F0)[var_s0] + 0x80000000);
        R1F100180_WRITE_GFX(arg0++, 0xF5900000, 0x07080200); R1F100180_WRITE_GFX(arg0++, 0xE6000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF3000000, 0x077FF020); R1F100180_WRITE_GFX(arg0++, 0xE7000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF5808000, 0x00080200); R1F100180_WRITE_GFX(arg0++, 0xF2000000, 0x00FFC01C); break;
    case 5:
        R1F100180_WRITE_GFX(arg0++, 0xFD900000, ((s32 *) D_807FD7F0)[var_s0] + 0x80000000);
        R1F100180_WRITE_GFX(arg0++, 0xF5900000, 0x07080200); R1F100180_WRITE_GFX(arg0++, 0xE6000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF3000000, 0x077FF020); R1F100180_WRITE_GFX(arg0++, 0xE7000000, 0); R1F100180_WRITE_GFX(arg0++, 0xF5808000, 0x00080200); R1F100180_WRITE_GFX(arg0++, 0xF2000000, 0x00FFC01C); break;
    }
    return arg0;
}

#ifdef NON_MATCHING
extern Mtx D_20000C0;
extern Gfx D_2000180;
Gfx *func_806FBEF0(Gfx *, u8, s32);
void heapFreeDeferred(void *);
Gfx *func_805FD030(Gfx *);
void func_80704298(void *, u8, u8, s8);

#define L3CMD(g, a, b) \
    { (g) = (Gfx *)(dl++); (g)->words.w0 = (a); (g)->words.w1 = (b); }
#define L3QUAD(g, v0, v1, v2, v3) \
    L3CMD(g, (_SHIFTL(G_QUAD, 24, 8) | __gsSP1Quadrangle_w1f(v0, v1, v2, v3, 0)), __gsSP1Quadrangle_w2f(v0, v1, v2, v3, 0))
#define L3VTX(g, v, n, v0) \
    L3CMD(g, _SHIFTL(G_VTX, 24, 8) | _SHIFTL((n), 12, 8) | _SHIFTL((v0) + (n), 1, 7), (unsigned int)(v))

Gfx *func_806FC530(Gfx *dl, s16 font, s16 x, s16 y, u8 *str, u8 flags) {
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
    Gfx *g7;
    Gfx *g8;
    Gfx *g9;
    Gfx *g10;
    Gfx *g11;
    Gfx *g12;
    s8 yoff;
    s16 gx;
    s16 h4;
    s16 w4;
    s16 w;
    s16 h;
    s32 count;
    s32 i;
    u8 *fi;
    u8 *glyph;
    Vtx *vp;
    s16 *v;

    idx = 0;
    startX = x;
    count = 0;
    center = 0;
    strStart = str;
    i = func_806FBEAC(str);
    if (i == 0) {
        return dl;
    }
    vp = (Vtx *)func_80610FE8(i << 6);
    heapFreeDeferred(vp);
    batch = vp;
    if (flags & 0x80) {
        flags &= ~0x80;
        x = x - func_806FBD5C(font, str) * 2;
        startX = x;
    }
    if (font & 0x80) {
        font ^= 0x80;
        center = 1;
    }
    L3CMD(g1, 0xE3001201, 0x2000);
    if (!(flags & 4)) {
        L3CMD(g2, 0xDA380007, (u32)&D_20000C0);
    }
    if (flags & 0x12) {
        L3CMD(g3, 0xE7000000, 0);
        L3CMD(g4, 0xFC121824, 0xFF33FFFF);
    }
    if (flags & 0x20) {
        L3CMD(g5, 0xE7000000, 0);
        L3CMD(g6, 0xFC121803, 0xFF0FFFFF);
    }
    if (flags & 1) {
        L3CMD(g7, 0xDA380003, (u32)&D_2000180);
    }
    dl = func_805FD030(dl);
    fi = D_80754A34 + font * 6;
    line = 1;
    if (fi[1] + 1 >= 2) {
        do {
            L3CMD(g8, 0xE7000000, 0);
            started = 0;
            ch = *str++;
            if (ch) {
                do {
                    if (ch != 0x20) {
                        yoff = func_806FB914(font, &ch) * 4;
                        glyph = (u8 *)((u8 **)D_80754A18)[font] + ch * 4;
                        w = glyph[2];
                        h = fi[2];
                        if (count && count) {}
                        w4 = w * 4;
                        h4 = h * 4;
                        gx = *(s16 *)glyph;
                        if (center) {
                            i = (fi[5] * 4 - w4) / 2;
                            if (i < 0) {
                                pad = 0;
                            } else {
                                pad = i;
                            }
                            x += pad;
                        }
                        if (ch >= (D_807549FC[font] + line)[-1] && ch < (D_807549FC[font] + line)[0]) {
                            if (started == 0) {
                                started = 1;
                                dl = func_806FBEF0(dl, font, (s16)line);
                                if (w && w) {}
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
                            v[29] = 0;
                            vp++;
                            vp++;
                            vp++;
                            vp++;
                            if (flags & 0x32) {
                                if (yoff) {}
                                func_80704298(vp - 4, idx, flags, yoff);
                            }
                            count += 4;
                            if (count >= 0x20) {
                                L3VTX(g9, osVirtualToPhysical(batch), 0x20, 0);
                                i = count / 4;
                                while (i-- > 0) {
                                    L3QUAD(g10, i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3);
                                }
                                count = 0;
                                batch = vp;
                            }
                        }
                        if (center) {
                            if (center) {}
                            i = fi[5] * 4;
                            x += (w4 < i) ? w4 : i;
                            if (w4 < i) {
                                x = x + i - pad - w4;
                            }
                        } else {
                            if (flags) {}
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
                L3VTX(g11, osVirtualToPhysical(batch), count, 0);
                if (batch) {}
                batch = vp;
                i = count / 4;
                while (i-- > 0) {
                    L3QUAD(g12, i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3);
                }
                if (count) {}
                count = 0;
            }
            str = strStart;
            line++;
        } while (line < fi[1] + 1);
    }
    L3CMD(g1, 0xE7000000, 0);
    return dl;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FC530.s")
#endif

extern Mtx D_2000000;
extern Mtx D_2000080;
extern Gfx D_2000180;
Gfx *func_806FBEF0(Gfx *, u8, s32);

#ifdef NON_MATCHING
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0xC];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    u8 pad24[0xC];
    f32 unk30;
    u8 pad34[4];
} HbTextElem;

typedef struct {
    u8 pad0[4];
    u8 *unk4;
    HbTextElem *unk8;
    u8 unkC;
    u8 unkD;
} HbTextObj;

extern u8 D_80754A36[];
extern u8 D_2000200[];
void heapFreeDeferred(void *);
Gfx *func_8070068C(Gfx *);

Gfx *func_806FCC88(Gfx *dl, HbTextObj *arg1) {
    s32 line;
    u8 chr;
    u8 started;
    s32 idx;
    Vtx *vp;
    Vtx *spB4;
    Mtx *mp;
    s32 i;
    s32 gw;
    s32 gx;
    s32 gh;

    idx = 0;
    vp = (Vtx *)func_80610FE8(arg1->unkD << 6);
    heapFreeDeferred(vp);
    mp = (Mtx *)func_80610FE8(arg1->unkD << 6);
    heapFreeDeferred(mp);
    spB4 = vp;
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    dl = func_8070068C(dl);
    line = 1;
    if (D_80754A35[arg1->unkC * 6] + 1 >= 2) {
        do {
            started = 0;
            i = 1;
            chr = arg1->unk4[0];
            if (chr) {
                do {
                    if (chr != 0x20) {
                        func_806FB914(arg1->unkC, &chr);
                        if (chr >= (D_807549FC[arg1->unkC] + line)[-1] && chr < (D_807549FC[arg1->unkC] + line)[0]) {
                            gw = ((u8 *)((u8 **)D_80754A18)[arg1->unkC])[chr * 4 + 2];
                            gx = *(s16 *)((u8 *)((u8 **)D_80754A18)[arg1->unkC] + chr * 4);
                            gh = D_80754A36[arg1->unkC * 6];
                            if (started == 0) {
                                started = 1;
                                dl = func_806FBEF0(dl, arg1->unkC, line);
                            }
                            guPosition(mp + idx, 0.0f, 0.0f, arg1->unk8[idx].unk20 * 57.295776f, arg1->unk8[idx].unk30,
                                       arg1->unk8[idx].unk0, arg1->unk8[idx].unk4, 0.0f);
                            gSPMatrix(dl++, mp + idx, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                            gDPPipeSync(dl++);
                            ((s16 *)vp)[0] = -(gw * 2);
                            ((s16 *)vp)[1] = gh * 2 - 1;
                            ((s16 *)vp)[2] = -5;
                            ((s16 *)vp)[4] = gx << 6;
                            ((s16 *)vp)[5] = gh << 6;
                            ((s16 *)vp)[8] = gw * 2 - 1;
                            ((s16 *)vp)[9] = gh * 2 - 1;
                            ((s16 *)vp)[10] = -5;
                            ((s16 *)vp)[12] = (gx + gw) << 6;
                            ((s16 *)vp)[13] = gh << 6;
                            ((s16 *)vp)[17] = -(gh * 2);
                            ((s16 *)vp)[16] = gw * 2 - 1;
                            ((s16 *)vp)[18] = -5;
                            ((s16 *)vp)[20] = (gx + gw) << 6;
                            ((s16 *)vp)[21] = 0;
                            ((s16 *)vp)[25] = -(gh * 2);
                            ((s16 *)vp)[24] = -(gw * 2);
                            ((s16 *)vp)[26] = -5;
                            ((s16 *)vp)[28] = gx << 6;
                            ((s16 *)vp)[29] = 0;
                            vp += 4;
                            gSPVertex(dl++, osVirtualToPhysical(spB4), 4, 0);
                            gSP1Quadrangle(dl++, 0, 1, 2, 3, 0);
                            gSPPopMatrix(dl++, G_MTX_MODELVIEW);
                            spB4 = vp;
                        }
                        idx++;
                    }
                    chr = arg1->unk4[i];
                    i++;
                } while (chr);
                idx = 0;
            }
            line++;
        } while (line < D_80754A35[arg1->unkC * 6] + 1);
    }
    gSPMatrix(dl++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(dl++, D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gDPPipeSync(dl++);
    return dl;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FCC88.s")
#endif

#ifdef NON_MATCHING

Gfx *func_806FD094(Gfx *dl, HbTextObj *arg1) {
    s32 line;
    u8 chr;
    u8 started;
    s32 idx;
    Vtx *vp;
    Vtx *spB4;
    Mtx *mp;
    s32 i;
    s32 gw;
    s32 gx;
    s32 gh;
    f32 fa;
    f32 fb;

    idx = 0;
    vp = (Vtx *)func_80610FE8(arg1->unkD << 6);
    heapFreeDeferred(vp);
    mp = (Mtx *)func_80610FE8(arg1->unkD << 6);
    heapFreeDeferred(mp);
    spB4 = vp;
    gDPSetTextureFilter(dl++, G_TF_BILERP);
    gSPMatrix(dl++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(dl++, D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(dl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    line = 1;
    if (D_80754A35[arg1->unkC * 6] + 1 >= 2) {
        do {
            started = 0;
            i = 1;
            chr = arg1->unk4[0];
            if (chr) {
                do {
                    if (chr != 0x20) {
                        func_806FB914(arg1->unkC, &chr);
                        if (chr >= (D_807549FC[arg1->unkC] + line)[-1] && chr < (D_807549FC[arg1->unkC] + line)[0]) {
                            gw = ((u8 *)((u8 **)D_80754A18)[arg1->unkC])[chr * 4 + 2];
                            gx = *(s16 *)((u8 *)((u8 **)D_80754A18)[arg1->unkC] + chr * 4);
                            gh = D_80754A36[arg1->unkC * 6];
                            if (started == 0) {
                                started = 1;
                                dl = func_806FBEF0(dl, arg1->unkC, line);
                            }
                            guPosition(mp + idx, arg1->unk8[idx].unk18 * 57.295776f,
                                       arg1->unk8[idx].unk1C * 57.295776f, arg1->unk8[idx].unk20 * 57.295776f,
                                       arg1->unk8[idx].unk30, arg1->unk8[idx].unk0, arg1->unk8[idx].unk4,
                                       arg1->unk8[idx].unk8);
                            gSPMatrix(dl++, mp + idx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                            gDPPipeSync(dl++);
                            ((s16 *)vp)[0] = -(gw * 2);
                            ((s16 *)vp)[1] = gh * 2 - 1;
                            ((s16 *)vp)[2] = 0;
                            ((s16 *)vp)[4] = gx << 6;
                            ((s16 *)vp)[5] = gh << 6;
                            ((s16 *)vp)[8] = gw * 2 - 1;
                            ((s16 *)vp)[9] = gh * 2 - 1;
                            ((s16 *)vp)[10] = 0;
                            ((s16 *)vp)[12] = (gx + gw) << 6;
                            ((s16 *)vp)[13] = gh << 6;
                            ((s16 *)vp)[17] = -(gh * 2);
                            ((s16 *)vp)[16] = gw * 2 - 1;
                            ((s16 *)vp)[18] = 0;
                            ((s16 *)vp)[20] = (gx + gw) << 6;
                            ((s16 *)vp)[21] = 0;
                            ((s16 *)vp)[25] = -(gh * 2);
                            ((s16 *)vp)[24] = -(gw * 2);
                            ((s16 *)vp)[26] = 0;
                            ((s16 *)vp)[28] = gx << 6;
                            ((s16 *)vp)[29] = 0;
                            vp += 4;
                            gSPVertex(dl++, osVirtualToPhysical(spB4), 4, 0);
                            gSP1Quadrangle(dl++, 0, 1, 2, 3, 0);
                            spB4 = vp;
                        }
                        idx++;
                    }
                    chr = arg1->unk4[i];
                    i++;
                } while (chr);
                idx = 0;
            }
            line++;
        } while (line < D_80754A35[arg1->unkC * 6] + 1);
    }
    gDPPipeSync(dl++);
    return dl;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/100180/func_806FD094.s")
#endif

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
} HcFontInfo;

#define HcFONTS ((HcFontInfo *)D_80754A34)

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
} HcGlyph;

#define HcGLYPH(f, c) (((HcGlyph *)D_80754A18[f])[c])

Gfx *func_806FD490(Gfx *dl, u8 font, s16 x, s16 y, u8 *str) {
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
    dl = func_806FBEF0(dl, font, 1);
    ch = *str++;
    while (ch) {
        if (ch != 0x20) {
            func_806FB914(font, &ch);
            gSPTextureRectangle(dl++, x << 2, y << 2, (x + HcGLYPH(font, ch).unk2) << 2, (HcFONTS[font].unk2 + y) << 2, 0, HcGLYPH(font, ch).unk0 << 5, 0, 0x400, 0x400);
            if (flag != 0) {
                x += HcFONTS[font].unk5;
            } else {
                x += HcGLYPH(font, ch).unk2 + HcFONTS[font].unk4;
            }
        } else if (flag != 0) {
            x += HcFONTS[font].unk5;
        } else {
            x += HcFONTS[font].unk3;
        }
        ch = *str++;
    }
    gDPPipeSync(dl++);
    gSPMatrix(dl++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetTexturePersp(dl++, G_TP_PERSP);
    return dl;
}

s16 func_806FD7A8(s16 arg0, u8 arg1) {
    s32 idx;
    s16 var_v1;
    HcFontInfo *var_a0;

    idx = arg0;
    if (idx & 0x80) {
        var_a0 = &HcFONTS[(s16)(idx ^ 0x80)];
        var_v1 = var_a0->unk5;
    } else if (arg1 == 0x20) {
        var_a0 = &HcFONTS[idx];
        var_v1 = var_a0->unk3;
    } else {
        func_806FB914(idx, &arg1);
        var_v1 = ((u8 *)D_80754A18[idx])[arg1 * 4 + 2];
        var_a0 = &HcFONTS[idx];
    }
    var_v1 += var_a0->unk4;
    return var_v1;
}

extern u8 D_80754A36[];

u8 func_806FD894(s16 arg0) {
    if (arg0 & 0x80) {
        arg0 ^= 0x80;
    }
    return D_80754A36[arg0 * 6];
}
