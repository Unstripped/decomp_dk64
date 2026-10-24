// func_806A92B4 (src/global/ACDC0.c): stage 4: frame 0x1a0 + callee-saved set match, behaviourally equivalent C; text 80B short; regalloc differs (tab/list/ret not spilled like target; 0.75f/0xFA000000/2 hoist differs, multu vs shifts for *0x69)
Gfx *func_806A921C(Gfx *);
Gfx *func_806ABB98(Gfx *, s32, s32, f32, char *);
Gfx *func_806FC530(Gfx *, s32, s32, s32, char *, s32);
s32 _sprintf(char *, const char *, ...);
extern char **D_807FC7E0;
void heapFreeDeferred(void *);
void *func_80610FE8(s32);
s32 func_805FF030(u8, s32);
s32 func_80712628(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
Gfx *func_806AA09C(s32, s16, s16, s32, Gfx *, s32, f32);
Gfx *func_806ABA6C(Gfx *, void *, s16);

typedef struct {
    f32 unk0;
    f32 unk4;
    s16 unk8[2];
    s16 unkC[2];
    s16 unk10;
    s8 unk12;
    u8 pad13;
    s8 unk14;
    u8 pad15[2];
    s8 unk17;
} L8_Hud;

typedef struct {
    f32 unk0;
    f32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s8 unk10;
    char unk11[7];
} L8_Item;

typedef struct {
    u8 pad0[0x42];
    u16 unk42[8];
    u8 pad52[0xC];
} L8_Row;

typedef struct {
    u8 pad0[0x2FC];
    u8 unk2FC;
} L8_Tab;

extern L8_Item *D_807FC7F0[];
extern s8 D_807FC7F8[];
extern L8_Tab D_807FC950;
extern s16 D_807FC992[];
extern u8 D_807FCC4C;
extern s8 D_807FCC4B;
extern s32 D_8076A064;
extern u8 D_8076A0AB;
extern s8 D_807505CC;
extern s8 D_80750538;
extern s8 D_80750530[];
extern s8 D_80750560[];
extern s16 D_8075056C[];
extern s8 D_807FC80C;
extern s8 D_807FC818[];
extern s16 D_807FC828[];
extern f32 D_807FC840[];
extern f32 D_807FC868[];
extern f32 D_807FC890[];

Gfx *func_806A92B4(Gfx *dl, Actor *actor) {
    char buf[0x40];
    L8_Hud *hud;
    s16 i;
    L8_Tab *tab;
    Gfx *ret;
    Gfx *list;
    s32 sp138;
    s16 j;
    s32 x;
    s32 y;
    s16 ang;
    s16 y0;
    s8 s2;
    s32 off;
    L8_Item *it;
    f32 fa;
    f32 fb;
    f32 fc;
    f32 fd;
    f32 fe;
    f32 ff;
    f32 fh;
    s32 t0;

    hud = actor->unk174;
    tab = &D_807FC950;
    sp138 = func_805FF030(D_8076A0AB, 1);
    list = func_80610FE8(0x1F40);
    heapFreeDeferred(list);
    gSPDisplayList(dl++, list);
    ret = dl;
    dl = func_806A921C(list);
    for (i = 0; i < 2; i++) {
        it = D_807FC7F0[i];
        if (it != 0) {
            for (j = 0; j < D_807FC7F8[i]; j++) {
                fa = hud->unk0;
                if (it[j].unk10 == 2) {
                    fa += hud->unk4;
                }
                x = it[j].unk8;
                y = it[j].unkA;
                x = x * 4 + (s32)(fa * it[j].unk0);
                y = y * 4 + (s32)(fa * it[j].unk4);
                x = x + it[j].unkC * 4;
                y = y + it[j].unkE * 4 + hud->unkC[i] * 4;
                dl = func_806FC530(dl, 1, (s16)x, (s16)y, it[j].unk11, 1);
            }
        }
    }
    switch (hud->unk12) {
        case 0:
            s2 = D_807FCC4B;
            y0 = 0xA0 - (s32)((f32)0x140 * hud->unk0);
            j = 0;
            if (D_807FCC4C > 0) {
                fb = (f32)(u32)((D_807FCC4C * 0x34 - 0x34) & 0xFF);
                do {
                    s32 off;
                    s16 ang;
                    f32 fa;
                    f32 fc;
                    f32 fd;
                    f32 fe;
                    f32 fh;
                    s16 y;
                    off = (j << 10) + D_8076A064 * 200;
                    ang = off;
                    fa = func_80612794(ang) * 0.3f + 3.0f;
                    fc = func_80612794(off + 0x800) * 0.3f + 3.0f;
                    fd = func_80612794((off >> 1) + 0x200) * 10.0f;
                    fa = fa * 0.75f;
                    fd = fd * 0.75f;
                    fc = fc * 0.75f;
                    fe = (func_80612794(ang) * 0.5f + 0.5f) * 30.0f * 0.75f;
                    gDPPipeSync(dl++);
                    dl->words.w1 = 0xFFFFFF50;
                    dl->words.w0 = 0xFA000000;
                    dl++;
                    y = (s32)((f32)(j * 0x69 + 0x280) + fd - fb);
                    fh = -fc;
                    dl = func_8068C5A8(dl, 0x5D, 0, 2, 0x30, 0x2A, y, y0 + (s16)(s32)fe, fa, fh, 0, 0.0f);
                    gDPPipeSync(dl++);
                    dl->words.w1 = 0xFFFFFFFF;
                    dl->words.w0 = 0xFA000000;
                    dl++;
                    if (s2 > 0) {
                        off = s2 - 1;
                        if (off < 3) {
                            t0 = off;
                        } else {
                            t0 = 3;
                        }
                        dl = func_8068C5A8(dl, (u16)(t0 + 0x5A), 0, 2, 0x30, 0x2A, y, (s32)((f32)y0 + fe), fa, fh, 0, 0.0f);
                    }
                    if (s2 - 4 < 0) {
                        s2 = 0;
                    } else {
                        s2 = s2 - 4;
                    }
                    j++;
                } while (j < tab->unk2FC);
            }
            gDPPipeSync(dl++);
            y = 0x198;
            j = 0;
            off = (s32)((1.0f - hud->unk0) * 255.0f);
            ang = off;
            if (ang < 0) {
                ang = 0;
            }
            if (ang >= 0x100) {
                ang = 0xFF;
            }
            if (hud->unk17 != 3) {
                do {
                    if (j == hud->unk17) {
                        dl->words.w1 = (ang & 0xFF) | 0xFFFFFF00;
                        dl->words.w0 = 0xFA000000;
                        dl++;
                    } else {
                        dl->words.w0 = 0xFA000000;
                        dl->words.w1 = ((ang >> 1) & 0xFF) | 0xFFFFFF00;
                        dl++;
                    }
                    if (j == 2 && (sp138 == 7 || (sp138 == 8 && func_80712628() != 0 && D_807505CC == 0))) {
                        j++;
                    }
                    i = j;
                    if (j == 1 && D_807505CC != 0) {
                        i = 4;
                    }
                    if (i == 2 && D_807505CC != 0) {
                        i = 5;
                    }
                    dl = func_806ABB98(dl, 0x280, y, 0.7f, D_807FC7E0[i]);
                    j++;
                    y += 0x44;
                } while (j < 3);
            } else {
                dl->words.w1 = (ang & 0xFF) | 0xFFFFFF00;
                dl->words.w0 = 0xFA000000;
                dl = func_806ABB98(dl + 1, 0x280, 0x198, 0.7f, D_807FC7E0[7]);
                _sprintf(buf, "q %s", D_807FC7E0[16]);
                dl = func_806ABB98(dl, 0x280, 0x1E8, 1.0f, buf);
                _sprintf(buf, "b %s", D_807FC7E0[17]);
                dl = func_806ABB98(dl, 0x280, 0x238, 1.0f, buf);
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                off = hud->unkC[i] * 4;
                ang = -hud->unk10;
                fa = 1.0f - hud->unk0;
                if (off < 0x3B6 && off >= -0x3B5) {
                    if (fa > 0.05f) {
                        f32 fb;
                        f32 fc;
                        f32 fd;
                        f32 fe;
                        f32 ff;
                        fb = 180.0f * fa;
                        fa = fa * 3.0f;
                        fc = 32.0f * fa;
                        fd = 6.0f * fa;
                        fe = 30.0f * fa;
                        fc = 480.0f + fc;
                        ff = (f32)((f64)fa * 1.33);
                        j = 0;
                        do {
                            y = (s32)(func_80612794(ang) * fb) + 0x280;
                            y0 = (s32)(func_80612790(ang) * fb);
                            D_807FC840[j + i * 5] = (f32)(s16)(y + 0x20) - fd;
                            D_807FC868[j + i * 5] = (f32)(s16)((s32)(fc - (f32)y0) + off) - fe;
                            D_807FC890[j + i * 5] = ff;
                            if (D_80750530[j] != 0) {
                                D_807FC890[j + i * 5] = (f32)((f64)D_807FC890[j + i * 5] * 0.75);
                            }
                            j++;
                            ang += 0x333;
                        } while (j < 5);
                        gDPPipeSync(dl++);
                    }
                    dl = func_806ABA6C(dl, hud, i);
                }
                j = hud->unk8[i];
                if (j != 8) {
                    f32 fa;
                    f32 fb;
                    f32 fc;
                    f32 fd;
                    fa = hud->unk4;
                    fb = hud->unk0;
                    fc = 780.0f;
                    if (fa < fb) {
                        fd = fb;
                    } else {
                        fd = fa;
                    }
                    if (off == 0) {
                        fc = fc + fd * 400.0;
                    }
                    dl = func_806AA09C(0x2A8, (s32)((f32)off + fc), *(s16 *)((u8 *)D_807FC992 + hud->unk14 * 0x5E + D_80750560[j] * 2), 5, dl, 0, 0.8f);
                }
            }
            D_80750538++;
            if (D_80750538 >= 0xE) {
                D_80750538 = 0;
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                off = hud->unkC[i] * 4;
                if (off < 0x3B6 && off >= -0x3B5) {
                    dl = func_806ABA6C(dl, hud, i);
                }
                y = hud->unk8[i];
                t0 = 0;
                j = 0;
                do {
                    t0 += ((L8_Row *)&D_807FC950)[j].unk42[D_80750560[y]];
                    j++;
                } while (j < 5);
                if (y != 8) {
                    f32 fa;
                    f32 fb;
                    fa = hud->unk4;
                    fb = hud->unk0;
                    fc = 780.0f;
                    if (fa < fb) {
                        fd = fb;
                    } else {
                        fd = fa;
                    }
                    if (off == 0) {
                        fc = fc + fd * 400.0;
                    }
                    dl = func_806AA09C(0x2B0, (s32)((f32)off + fc), t0, 0x19, dl, 0, 0.8f);
                }
            }
            break;
        case 3:
            dl = func_806ABB98(func_806ABB98(dl, 0x280, 0x74, 0.5f, D_807FC7E0[D_807FC818[D_807FC80C] + 18]), 0x280, 0x3C, 0.65f, D_807FC7E0[6]);
            fa = hud->unk4;
            fb = hud->unk0;
            if (fa < fb) {
                fd = fb;
            } else {
                fd = fa;
            }
            fc = (1.0f - fd) * 0.65f;
            if (fc < 0.01f) {
                fc = 0.01f;
            }
            dl = func_806AA09C(0x280, 0x33C, D_807FC828[D_807FC818[D_807FC80C]], D_8075056C[D_807FC818[D_807FC80C]], dl, 1, fc);
            break;
    }
    dl->words.w0 = 0xDF000000;
    dl->words.w1 = 0;
    return ret;
}
