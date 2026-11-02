// hudPauseMenuRender (src/global/ACDC0.c): L890 (leftovers 6): stage 4, count EXACT (nm 0xde8 = target), frame 0x1a0, ALL sp offsets match, deadsweep full 400 (was 451 count-inexact; readable 654), 29 FAKE dead tests from a hill-climb on a structure-fixed base. Real structure fixes: (1) case 0 u8 ph=D_807FCC4C*0x34-0x34 before the if, fb=(f32)(u32)ph (v1 web); (2) case-0 clamp m separate local from case-2 accum t0; (3) hud->unk8[i] read directly in case 1/2 (web t1, ugen ring starts t3 like target); (4) case 1: s32 angv, s16 sa=angv per iter, s16 yy (yy=..+0x280; yy+=0x20) reproduces sll/sra idioms; (5) case 0: fe=func_80612794(ang) FIRST, then fa/fd/fc*=0.75, then fe=(fe*0.5+0.5)*30*0.75 (as1 hoists muls after the 4th call); (6) function-scope y is s16; shadow decls removed (case0 fb/ang, case1 fb/fc) for frame 416 and spill 168. Remaining: t-ring numbering cascade (m3 234 vs full 400), first-loop colours (target off s0,y s1,it s2,j s3,ptr s4; ours it s2,ptr s1,off s5), constant 24/200 s-reg order, &D_807FC950 t2 hoist, case-1 loop j++ hoist (bnezl copy), D_807FC840 s8 hoist; fakes tuned for these.
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
} L890HudPauseState;

f32 func_80612790(s16);
f32 func_80612794(s16);
s32 func_805FF030(s32, s32);
s32 func_80712628(void);
Gfx *hudDrawCountPair(s16, s16, s16, s16, Gfx *, s8, f32);
Gfx *hudDrawItemLabel(Gfx *, HudEntry *, s32);
extern s16 D_807FC992[];
extern u8 D_807FCC4C;
extern s8 D_807FCC4B;
extern s32 gFrameCounter;
extern u8 D_8076A0AB;
extern s8 D_80750538;
extern s16 D_8075056C[];
extern s8 D_807FC80C;
extern s8 D_807FC818[];
extern f32 D_807FC840[];
extern f32 D_807FC868[];
extern f32 D_807FC890[];

Gfx *hudPauseMenuRender(Gfx *dl, Actor *actor) {
    char buf[0x40];
    L890HudPauseState *hud;
    s16 j;
    s16 i;
    s16 y;
    s32 off;
    s32 t0;
    HudTextEntry *it;
    HudCountEntry *tab;
    Gfx *ret;
    Gfx *list;
    s32 sp138;
    s16 ang;
    s16 y0;
    s8 s2;
    u8 ph;
    f32 fa;
    f32 fb;
    f32 fc;
    f32 fd;

    if (D_807FC890 && D_807FC890) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    hud = actor->unk174;
    tab = (HudCountEntry *)((u8 *)D_807FC7F8 + 0x158);
    sp138 = func_805FF030(D_8076A0AB, 1);
    list = heapAlloc(0x1F40);
    heapFreeDeferred(list);
    if (D_80750538) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    gSPDisplayList(dl++, list);
    ret = dl;
    dl = hudSetupTextState(list);
    for (i = 0; i < 2; i++) {
        it = D_807FC7F0[i];
        if (it != 0) {
            for (j = 0; j < D_807FC7F8[i]; j++) {
                fa = hud->unk0;
                if (dl != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if ((s8)it[j].unk10 == 2) {
                    fa += hud->unk4;
                }
                off = it[j].unk8;
                y = it[j].unkA;
                off = off * 4 + (s32)(fa * it[j].unk0);
                y = y * 4 + (s32)(fa * it[j].unk4);
                off = off + it[j].unkC * 4;
                y = y + it[j].unkE * 4 + hud->unkC[i] * 4;
                dl = textDrawStringVtx(dl, 1, (s16)off, (s16)y, it[j].unk11, 1);
            }
        }
    }
    switch (hud->unk12) {
        case 0:
            if (D_807FC818) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            s2 = D_807FCC4B;
            y0 = 0x140; /* narrow var: keeps (f32)0x140 unfolded */
            y0 = 0xA0 - (s32)((f32)y0 * hud->unk0);
            j = 0;
            ph = D_807FCC4C * 0x34 - 0x34;
            if (D_807FCC4C > 0) {
                fb = (f32)(u32)ph;
                do {
                    s32 off;
                    f32 fa;
                    f32 fc;
                    f32 fd;
                    f32 fe;
                    f32 fh;
                    s16 y;
                    off = (j << 10) + gFrameCounter * 200;
                    if (gFrameCounter) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    ang = off;
                    fa = func_80612794(ang) * 0.3f + 3.0f;
                    fc = func_80612794(off + 0x800) * 0.3f + 3.0f;
                    fd = func_80612794((off >> 1) + 0x200) * 10.0f;
                    fe = func_80612794(ang);
                    fa = fa * 0.75f;
                    fd = fd * 0.75f;
                    fc = fc * 0.75f;
                    fe = (fe * 0.5f + 0.5f) * 30.0f * 0.75f;
                    gDPPipeSync(dl++);
                    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0x50);
                    y = (s32)((f32)(j * 0x69 + 0x280) + fd - fb);
                    fh = -fc;
                    dl = renderRotatedSprite(dl, 0x5D, 0, 2, 0x30, 0x2A, y, y0 + (s16)(s32)fe, fa, fh, 0, 0.0f);
                    gDPPipeSync(dl++);
                    if (!D_807FC868) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    dl->words.w1 = 0xFFFFFFFF;
                    dl->words.w0 = 0xFA000000;
                    if (D_807FC828 && D_807FC828) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    dl++;
                    if (s2 > 0) {
                        s32 m;
                        off = s2 - 1;
                        if (off < 3) {
                            m = off;
                        } else {
                            m = 3;
                        }
                        dl = renderRotatedSprite(dl, (u16)(m + 0x5A), 0, 2, 0x30, 0x2A, y, (s32)((f32)y0 + fe), fa, fh, 0, 0.0f);
                    }
                    if (s2 - 4 < 0) {
                        s2 = 0;
                    } else {
                        s2 = s2 - 4;
                    }
                    j++;
                } while (j < ((u8 *)tab)[0x2FC]);
                if (D_807FC7F8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            if (D_807FC890 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            gDPPipeSync(dl++);
            y = 0x198;
            j = 0;
            if (D_807FC950) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                    } else {
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang >> 1);
                    }
                    if (j == 2 && (sp138 == 7 || (sp138 == 8 && func_80712628() != 0 && *(s8 *)D_807505CC == 0))) {
                        j++;
                    }
                    i = j;
                    if (j == 1 && *(s8 *)D_807505CC != 0) {
                        i = 4;
                    }
                    if (i == 2 && *(s8 *)D_807505CC != 0) {
                        i = 5;
                    }
                    dl = hudDrawScaledText(dl, 0x280, y, 0.7f, D_807FC7E0[i]);
                    j++;
                    y += 0x44;
                } while (j < 3);
            } else {
                if (D_807FC992) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                dl = hudDrawScaledText(dl, 0x280, 0x198, 0.7f, D_807FC7E0[7]);
                _sprintf(buf, "q %s", D_807FC7E0[16]);
                dl = hudDrawScaledText(dl, 0x280, 0x1E8, 1.0f, buf);
                if (D_807FC7E0 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                _sprintf(buf, "b %s", D_807FC7E0[17]);
                dl = hudDrawScaledText(dl, 0x280, 0x238, 1.0f, buf);
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                s32 angv;
                off = hud->unkC[i] * 4;
                angv = -hud->unk10;
                fa = 1.0f - hud->unk0;
                if (off < 0x3B6 && off >= -0x3B5) {
                    if (fa > 0.05f) {
                        f32 fc;
                        f32 fe;
                        f32 ff;
                        s16 sa;
                        s16 yy;
                        fb = 180.0f * fa;
                        fa = fa * 3.0f;
                        fc = 32.0f * fa;
                        fd = 6.0f * fa;
                        fe = 30.0f * fa;
                        if (!D_807FC868) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        fc = 480.0f + fc;
                        ff = (f32)((f64)fa * 1.33);
                        j = 0;
                        do {
                            sa = angv;
                            yy = (s32)(func_80612794(sa) * fb) + 0x280;
                            y0 = (s32)(func_80612790(sa) * fb);
                            yy += 0x20;
                            D_807FC840[j + i * 5] = (f32)yy - fd;
                            D_807FC868[j + i * 5] = (f32)(s16)((s32)(fc - (f32)y0) + off) - fe;
                            D_807FC890[j + i * 5] = ff;
                            if (((s8 *)&D_80750530)[j] != 0) {
                                if (!dl) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                                D_807FC890[j + i * 5] = (f32)((f64)D_807FC890[j + i * 5] * 0.75);
                            }
                            j++;
                            angv += 0x333;
                        } while (j < 5);
                        gDPPipeSync(dl++);
                    }
                    dl = hudDrawItemLabel(dl, (HudEntry *)hud, i);
                }
                if (hud->unk8[i] != 8) {
                    f32 fa;
                    f32 fb;
                    f32 fc;
                    f32 fd;
                    if (D_8075056C && D_8075056C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    fa = hud->unk4;
                    if (D_807FC7F0 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    fb = hud->unk0;
                    fc = 780.0f;
                    if (fa < fb) {
                        fd = fb;
                    } else {
                        if (dl != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        fd = fa;
                    }
                    if (off == 0) {
                        fc = fc + fd * 400.0;
                    }
                    dl = hudDrawCountPair(0x2A8, (s32)((f32)off + fc), *(s16 *)((u8 *)D_807FC992 + hud->unk14 * 0x5E + D_80750560[hud->unk8[i]] * 2), 5, dl, 0, 0.8f);
                }
            }
            D_80750538++;
            if (D_80750538 >= 0xE) {
                D_80750538 = 0;
            }
            break;
            if (D_807FC7E0 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        case 2:
            for (i = 0; i < 2; i++) {
                off = hud->unkC[i] * 4;
                if (off < 0x3B6 && off >= -0x3B5) {
                    if (gFrameCounter != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    dl = hudDrawItemLabel(dl, (HudEntry *)hud, i);
                }
                if (!D_807FC868) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                t0 = 0;
                j = 0;
                do {
                    t0 += D_807FC950[j].unk42[D_80750560[hud->unk8[i]]];
                    j++;
                } while (j < 5);
                if (hud->unk8[i] != 8) {
                    f32 fa;
                    f32 fb;
                    fa = hud->unk4;
                    if (D_80750560) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    fb = hud->unk0;
                    fc = 780.0f;
                    if (fa < fb) {
                        if (D_80750560 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        fd = fb;
                    } else {
                        if (D_807FC868 && D_807FC868) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        fd = fa;
                        if (D_807FC890) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    }
                    if (off == 0) {
                        fc = fc + fd * 400.0;
                    }
                    dl = hudDrawCountPair(0x2B0, (s32)((f32)off + fc), t0, 0x19, dl, 0, 0.8f);
                }
            }
            if (D_807FC80C == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            break;
        case 3:
            if (!D_807FC828) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            dl = hudDrawScaledText(hudDrawScaledText(dl, 0x280, 0x74, 0.5f, D_807FC7E0[D_807FC818[D_807FC80C] + 18]), 0x280, 0x3C, 0.65, D_807FC7E0[6]);
            fa = hud->unk4;
            fb = hud->unk0;
            if (fa < fb) {
                if (!gFrameCounter) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (!D_807FC7F8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                fd = fb;
            } else {
                fd = fa;
            }
            fc = (1.0f - fd) * 0.65f;
            if (fc < 0.01f) {
                fc = 0.01f;
            }
            dl = hudDrawCountPair(0x280, 0x33C, (&D_807FC828)[D_807FC818[D_807FC80C]], D_8075056C[D_807FC818[D_807FC80C]], dl, 1, fc);
            break;
    }
    dl->words.w0 = 0xDF000000;
    dl->words.w1 = 0;
    if (D_807FC992 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    return ret;
}
