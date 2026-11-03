#include "common.h"

extern s8 D_807F5D84;

void screenWipeReset(void) {
    D_807F5D84 = 0;
}

u8 screenWipeGetState(void) {
    return (u8)D_807F5D84;
}

extern u8 D_80747B20;

u8 screenWipeGetCooldown(void) {
    return D_80747B20;
}

extern s32 D_80744470[];
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444FC;
extern u8 D_807F5D85;
extern s16 D_807F5D86;
extern s16 D_807F5D88;
extern f32 D_807F5D8C;
extern f32 D_807F5D94;
extern u16 *D_807F5D80;
void *heapAlloc(s32);
void blurBuildDivTable(void);
void fbCopySetAlpha(void *, s32);

void screenWipeStart(arg0)
u8 arg0;
{
    s32 sel = arg0;

    if ((D_807F5D84 == 0) || (arg0 == 7)) {
        if (D_807F5D84 == 0) {
            D_807F5D80 = heapAlloc(D_80744490 * D_80744494 * 2);
        }
        fbCopySetAlpha(D_807F5D80, D_80744470[D_807444FC]);
        D_807F5D84 = 1;
        D_80747B20 = 5;
        switch (sel) {
            case 1:
                D_807F5D86 = 0xFF;
                break;
            case 2:
                D_807F5D86 = 0;
                break;
            case 0:
                D_807F5D86 = 0x136;
                break;
            case 3:
                D_807F5D86 = 0xA0;
                D_807F5D88 = 0xA0;
                break;
            case 4:
            case 5:
                D_807F5D8C = -5.0f;
                break;
            case 6:
                D_807F5D94 = 0.0f;
                break;
            case 7:
                blurBuildDivTable();
                break;
        }
        D_807F5D85 = sel;
    }
}

#define WIPE_GFX(a, b) { Gfx *_g = (Gfx *)(arg0++); _g->words.w0 = (a); _g->words.w1 = (b); }

extern u8 D_1000118;
extern u8 D_2000140;
extern u32 D_80744478;
extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;
extern s32 D_80747B24;
extern f32 D_807F5D90;
extern Mtx D_807F5D98;
extern s32 D_807FBB60;
Gfx *func_805FD030(Gfx *);
void heapFreeDeferred(void *);
void screenBlurApply(void);
void screenWipeAlphaRadialSweep(s32, s32, s32);
void screenWipeAlphaFromCorner(s32, s32, s32);
void screenWipeAlphaFromCentre(s32, s32, s32);
void func_807023E8(Gfx **, void *, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32);
void gfxDrawTexturedTileGrid(Gfx **, void *, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, s32, s32, s32, void *);

Gfx *screenWipeDraw(Gfx *arg0) {
    s32 sp54;

    sp54 = (s32)((f32)D_80744478 * 0.5f);
    if (D_80747B24 == 0) {
        guScale(&D_807F5D98, 2.0f, 2.0f, 1.0f);
        D_80747B24 = 1;
    }
    if ((D_807F5D84 == 0) && (D_80747B20 != 0)) {
        D_80747B20--;
    }
    if (D_807F5D84 < 0) {
        D_807F5D84++;
        if (D_807F5D84 == 0) {
            heapFreeDeferred(D_807F5D80);
        }
    } else if (D_807F5D84 > 0) {
        WIPE_GFX(0xDE000000, (u32)&D_1000118);
        arg0 = func_805FD030(arg0);
        WIPE_GFX(0xDA380007, (u32)&D_2000140);
        WIPE_GFX(0xDA380003, (u32)&D_807F5D98);
        WIPE_GFX(0xE7000000, 0);
        WIPE_GFX(0xE3001201, 0);
        WIPE_GFX(0xE3001801, 0xC0);
        WIPE_GFX(((s32)(D_80744498 * 4.0f) & 0xFFF) << 12 | 0xED000000 | ((s32)(D_8074449C * 4.0f) & 0xFFF), ((s32)(D_807444A0 * 4.0f) & 0xFFF) << 12 | ((s32)(D_807444A4 * 4.0f) & 0xFFF));
        WIPE_GFX(0xE200001C, 0x504240);
        switch (D_807F5D85) {
            case 7:
                screenBlurApply();
                WIPE_GFX(0xFC119623, 0xFF2FFFFF);
                WIPE_GFX(0xFA000000, -1);
                func_807023E8(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 319.0f, 239.0f, 0.0f, 0.0f);
                if (D_807FBB60 & 0x40) {
                    D_807F5D84 = -2;
                }
                break;
            case 1:
                WIPE_GFX(0xFC119623, 0xFF2FFFFF);
                WIPE_GFX(0xFA000000, (D_807F5D86 & 0xFF) | ~0xFF);
                func_807023E8(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 319.0f, 239.0f, 0.0f, 0.0f);
                D_807F5D86 -= sp54 * 5;
                if (D_807F5D86 < 0) {
                    D_807F5D84 = -2;
                }
                break;
            case 2:
                WIPE_GFX(0xFC119623, 0xFF2FFFFF);
                WIPE_GFX(0xFA000000, -1);
                func_807023E8(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, (f32)D_807F5D86, 0.0f, 319.0f, 239.0f, (f32)D_807F5D86, 0.0f);
                WIPE_GFX(0xE7000000, 0);
                WIPE_GFX(0xFC121824, 0xFF33FFFF);
                if (D_807F5D86 >= 0x11) {
                    gfxDrawTexturedTileGrid(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x10, 0x50, (f32)(D_807F5D86 - 0x10), 0.0f, (f32)D_807F5D86, 239.0f, (f32)(D_807F5D86 - 0x10), 0.0f, 1, 0x10, 1, NULL);
                }
                D_807F5D86 = D_807F5D86 + sp54 * 10;
                if (D_807F5D86 >= 0x137) {
                    D_807F5D84 = -2;
                }
                break;
            case 0:
                WIPE_GFX(0xFC119623, 0xFF2FFFFF);
                WIPE_GFX(0xFA000000, -1);
                func_807023E8(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0xA, 0x50, 0.0f, 0.0f, D_807F5D86, 239.0f, 0.0f, 0.0f);
                WIPE_GFX(0xFC121824, 0xFF33FFFF);
                if (D_807F5D86 < 0x131) {
                    gfxDrawTexturedTileGrid(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x10, 0x20, (f32)D_807F5D86, 0.0f, (f32)(D_807F5D86 + 0x10), 239.0f, (f32)D_807F5D86, 0.0f, 1, 0x10, 2, NULL);
                }
                D_807F5D86 = D_807F5D86 - sp54 * 10;
                if (D_807F5D86 < 0xB) {
                    D_807F5D84 = -2;
                }
                break;
            case 3:
                WIPE_GFX(0xFC119623, 0xFF2FFFFF);
                WIPE_GFX(0xFA000000, -1);
                func_807023E8(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, (f32)D_807F5D86, 0.0f, 319.0f, 239.0f, (f32)D_807F5D86, 0.0f);
                func_807023E8(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0xA, 0x50, 0.0f, 0.0f, D_807F5D88, 239.0f, 0.0f, 0.0f);
                WIPE_GFX(0xFC121824, 0xFF33FFFF);
                if (D_807F5D86 >= 0x11) {
                    gfxDrawTexturedTileGrid(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x10, 0x50, (f32)(D_807F5D86 - 0x10), 0.0f, (f32)D_807F5D86, 239.0f, (f32)(D_807F5D86 - 0x10), 0.0f, 1, 0x10, 1, NULL);
                }
                if (D_807F5D88 < 0x131) {
                    gfxDrawTexturedTileGrid(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x10, 0x20, (f32)D_807F5D88, 0.0f, (f32)(D_807F5D88 + 0x10), 239.0f, (f32)D_807F5D88, 0.0f, 1, 0x10, 2, NULL);
                }
                D_807F5D86 += sp54 * 10;
                D_807F5D88 = D_807F5D88 - sp54 * 10;
                if (D_807F5D86 >= 0x137) {
                    D_807F5D84 = -2;
                }
                break;
            case 4:
                WIPE_GFX(0xFC121824, 0xFF33FFFF);
                D_807F5D8C = D_807F5D8C + 5.0 * sp54;
                D_807F5D90 = D_807F5D8C + 40.0f;
                gfxDrawTexturedTileGrid(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 320.0f, 239.0f, 0.0f, 0.0f, 1, 0x10, 1, screenWipeAlphaFromCentre);
                if (D_807F5D8C > 170.0f) {
                    D_807F5D84 = -2;
                }
                break;
            case 5:
                WIPE_GFX(0xFC121824, 0xFF33FFFF);
                D_807F5D8C = D_807F5D8C + 12.0 * sp54;
                D_807F5D90 = D_807F5D8C + 40.0f;
                gfxDrawTexturedTileGrid(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 320.0f, 239.0f, 0.0f, 0.0f, 1, 0x10, 1, screenWipeAlphaFromCorner);
                if (D_807F5D8C > 350.0f) {
                    D_807F5D84 = -2;
                }
                break;
            case 6:
                WIPE_GFX(0xFC121824, 0xFF33FFFF);
                D_807F5D94 = D_807F5D94 + 15.0 * sp54;
                gfxDrawTexturedTileGrid(&arg0, D_807F5D80, 0, 0x140, 0xF0, 0x20, 0x20, 0.0f, 0.0f, 320.0f, 239.0f, 0.0f, 0.0f, 1, 0x10, 1, screenWipeAlphaRadialSweep);
                if (D_807F5D94 > 350.0f) {
                    D_807F5D84 = -2;
                }
                break;
        }
        WIPE_GFX(0xE7000000, 0);
        WIPE_GFX(0xE3001801, 0);
        WIPE_GFX(0xE3001201, 0x2000);
    }
    return arg0;
}

f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
void vtxSetColor(s32, s32, s32, s32, s32, s32);

void screenWipeAlphaRadialSweep(s32 arg0, s32 arg1, s32 arg2) {
    f32 ang;
    s16 alpha;

    ang = mathAngleBetweenPointsDeg(0xA0, 0x78, arg0, arg1);
    if (D_807F5D94 < 20.0) {
        vtxSetColor(arg2, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        return;
    }
    alpha = 0;
    if (D_807F5D94 < ang) {
        f64 diff = ang - D_807F5D94;
        if (diff < 25.0) {
            alpha = (s16)((diff / 25.0) * 255.0);
        } else {
            alpha = 0xFF;
        }
    } else {
        alpha = 0;
    }
    vtxSetColor(arg2, 0xFF, 0xFF, 0xFF, alpha, 0);
}

f32 sqrtf(f32);

void screenWipeAlphaByDistance(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void screenWipeAlphaFromCorner(s32 arg0, s32 arg1, s32 arg2) {
    screenWipeAlphaByDistance(arg0, arg1, arg2, 0, 0);
}

void screenWipeAlphaFromCentre(s32 arg0, s32 arg1, s32 arg2) {
    screenWipeAlphaByDistance(arg0, arg1, arg2, 0xA0, 0x78);
}

void screenWipeAlphaByDistance(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 dx;
    s32 dy;
    f32 dist;
    s16 alpha;

    dx = arg0 - arg3;
    dy = arg1 - arg4;
    dist = sqrtf(dx * dx + dy * dy);
    if (dist < D_807F5D8C) {
        alpha = 0;
    } else if (D_807F5D90 < dist) {
        alpha = 0xFF;
    } else {
        alpha = (s16)(((dist - D_807F5D8C) / (D_807F5D90 - D_807F5D8C)) * 255.0f);
    }
    vtxSetColor(arg2, 0xFF, 0xFF, 0xFF, alpha, 0);
}

extern s32 D_80747B28;
extern u8 *D_80747B2C;
extern s32 D_80747B38;

void blurBuildDivTable(void) {
    s32 i;

    D_80747B2C = heapAlloc((D_80747B28 << 5) + 1);
    for (i = 0; i <= (D_80747B28 << 5); i++) {
        D_80747B2C[i] = i / D_80747B28;
    }
    D_80747B38 = 0;
}

extern s32 D_80747B30;
extern s32 D_80747B34;
extern s32 D_80747B3C;
void heapFree(void *);

void screenBlurApply(void) {
    u16 *src;
    s32 row;
    u16 *dst;
    u8 *lut;
    s32 sumR;
    s32 sumG;
    s32 sumB;
    s32 i;
    s32 idx;
    u32 pix;
    u8 r[0x34];
    u8 g[0x34];
    u8 b[0x34];
    u8 vr;
    u8 vg;
    u8 vb;

    src = D_807F5D80;
    dst = D_807F5D80;
    lut = D_80747B2C;
    if ((D_80747B2C == 0) || (D_80747B3C < D_80747B38)) {
        if (D_80747B2C != 0) {
            heapFree(D_80747B2C);
            D_80747B2C = 0;
        }
    } else {
        for (row = 0; row < D_80747B34; row++) {
            sumR = 0;
            sumB = 0;
            sumG = 0;
            for (i = 0; i < D_80747B28; i++) {
                r[i] = 0;
                g[i] = 0;
                b[i] = 0;
            }
            idx = D_80747B28 / 2;
            for (i = 0; i < D_80747B28 / 2; i++) {
                pix = *src;
                vr = (pix >> 11) & 0x1F;
                r[idx] = vr;
                sumR += vr;
                vg = (pix >> 6) & 0x1F;
                vb = (pix >> 1) & 0x1F;
                idx++;
                src++;
                g[idx - 1] = vg;
                sumG += vg;
                b[idx - 1] = vb;
                sumB += vb;
            }
            idx = 0;
            for (i = 0; i < D_80747B30 - D_80747B28 / 2; i++) {
                pix = *src++;
                if (idx >= D_80747B28) {
                    idx = 0;
                }
                vr = (pix >> 11) & 0x1F;
                sumR -= r[idx];
                sumR += vr;
                r[idx] = vr;
                vg = (pix >> 6) & 0x1F;
                sumG -= g[idx];
                g[idx] = vg;
                sumG += vg;
                vb = (pix >> 1) & 0x1F;
                sumB -= b[idx];
                b[idx] = vb;
                idx++;
                sumB += vb;
                *dst = 1 | (lut[sumB] << 1) | (lut[sumG] << 6) | (lut[sumR] << 11);
                dst++;
            }
            for (i = D_80747B30 - D_80747B28 / 2; i < D_80747B30; i++) {
                if (idx >= D_80747B28) {
                    idx = 0;
                }
                sumR -= r[idx];
                sumG -= g[idx];
                sumB -= b[idx];
                r[idx] = 0;
                g[idx] = 0;
                b[idx] = 0;
                idx++;
                *dst = 1 | (lut[sumB] << 1) | (lut[sumG] << 6) | (lut[sumR] << 11);
                dst++;
            }
        }
        D_80747B38++;
    }
}

extern u8 D_80747B40;
extern u8 *D_807F5DD8;
void *_memset(u8 *, s32, u32);

void screenBufferAllocate(void) {
    if (D_80747B40 == 0) {
        D_807F5DD8 = heapAlloc(0x25800);
        _memset(D_807F5DD8, 0, 0x25800);
        D_80747B40 = 1;
    }
}

void screenBufferFree(void) {
    if (D_80747B40 != 0) {
        heapFreeDeferred(D_807F5DD8);
        D_80747B40 = 0;
    }
}

extern f32 D_80747B44;
extern f32 D_80747B48;
extern f32 D_80747B4C;
extern f32 D_80747B50;

void func_8062A808(s32 arg0, s32 arg1) {
    D_80747B4C = 2.0f;
    D_80747B50 = 2.0f;
    D_80747B44 = arg0;
    D_80747B48 = arg1;
}

s32 gfxPassThrough(s32 arg0) {
    return arg0;
}
