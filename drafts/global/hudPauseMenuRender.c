// hudPauseMenuRender (src/global/ACDC0.c): hudPauseMenuRender (src/global/ACDC0.c): stage 4 (HudR, base 2256268): frame 0x1a0 + callee-saved set match; deadsweep full diff 473->451 (992 vs 993 insns, reg-blind shape 165) with 23 FAKE global dead tests (hill-climb from the 473 draft, 3 fakes less than before + minimised) plus real changes: case 1/2 read hud->unk8[i] directly (no y/j local copy: -8) and in the case-0 loop the fe statement placed before the fc*0.75 statement (mv0 order search). Readable park in ACDC0.c is now 654 (was 673). Findings: (1) target ring temps are only t3-t9: t0 (case2 accum), t1 (&D_807FC950 hoist / hud->unk8[i]), t2 are uopt webs; first loop target colours off s0,y s1,it s2,j s3,ptr(D_807FC7F8+i) s4 (ours ptr s0,off s2,it s4): ptr must have LOWEST priority, off highest; (2) case0 loop: target does the 4th func_80612794(ang) call BEFORE the three *0.75 muls (f0 survives them); every spelling that moves the call earlier (fe split into call temp + rest, whole-fe reorder) shifts the f-reg colouring (0.75 const f30/fe f26 vs target f28/f30) and loses more than it gains; (3) case 1/2 loop: y copy removal gave -8 (target loads unk8[i] once into t1 then uses for compare and index); remaining case2 diff = ours keeps hud ptr in a0/t5 and reloads lw t8,348(sp) vs target lw t3. Tried and null: textDrawStringVtx/renderRotatedSprite narrow prototypes, local type of y/j/off in case 2, field-expression statement splits (H1-H6), self-assign FAKEs, random hill-climb to 447 (52 fakes: not worth).
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
} HudPauseRenderState;

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
    HudPauseRenderState *hud;
    s16 j;
    s16 i;
    s32 y;
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
    s32 x; /* unused: reserves the frame slot the target has */
    f32 fa;
    f32 fb;
    f32 fc;
    f32 fd;

    hud = actor->unk174;
    tab = (HudCountEntry *)((u8 *)D_807FC7F8 + 0x158);
    sp138 = func_805FF030(D_8076A0AB, 1);
    list = heapAlloc(0x1F40);
    heapFreeDeferred(list);
    if (D_80750538 + D_807FC992) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    gSPDisplayList(dl++, list);
    ret = dl;
    dl = hudSetupTextState(list);
    for (i = 0; i < 2; i++) {
        it = D_807FC7F0[i];
        if (it != 0) {
            for (j = 0; j < D_807FC7F8[i]; j++) {
                fa = hud->unk0;
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
                if (ret) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
        }
    }
    switch (hud->unk12) {
        case 0:
            if (dl && dl) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            s2 = D_807FCC4B;
            y0 = 0x140; /* narrow var: keeps (f32)0x140 unfolded */
            y0 = 0xA0 - (s32)((f32)y0 * hud->unk0);
            j = 0;
            if (D_807FCC4C > 0) {
                f32 fb;
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
                    off = (j << 10) + gFrameCounter * 200;
                    ang = off;
                    fa = func_80612794(ang) * 0.3f + 3.0f;
                    fc = func_80612794(off + 0x800) * 0.3f + 3.0f;
                    fd = func_80612794((off >> 1) + 0x200) * 10.0f;
                    fa = fa * 0.75f;
                    if (!dl) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    fd = fd * 0.75f;
                    fe = (func_80612794(ang) * 0.5f + 0.5f) * 30.0f * 0.75f;
                    fc = fc * 0.75f;
                    gDPPipeSync(dl++);
                    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0x50);
                    y = (s32)((f32)(j * 0x69 + 0x280) + fd - fb);
                    fh = -fc;
                    dl = renderRotatedSprite(dl, 0x5D, 0, 2, 0x30, 0x2A, y, y0 + (s16)(s32)fe, fa, fh, 0, 0.0f);
                    if (D_807FCC4C != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    gDPPipeSync(dl++);
                    dl->words.w1 = 0xFFFFFFFF;
                    dl->words.w0 = 0xFA000000;
                    if (!D_807FC828) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    dl++;
                    if (s2 > 0) {
                        off = s2 - 1;
                        if (off < 3) {
                            t0 = off;
                        } else {
                            t0 = 3;
                        }
                        dl = renderRotatedSprite(dl, (u16)(t0 + 0x5A), 0, 2, 0x30, 0x2A, y, (s32)((f32)y0 + fe), fa, fh, 0, 0.0f);
                    }
                    if (s2 - 4 < 0) {
                        s2 = 0;
                    } else {
                        s2 = s2 - 4;
                    }
                    j++;
                    if (D_807FC7F0 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                } while (j < ((u8 *)tab)[0x2FC]);
                if (gFrameCounter || D_807FC950) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                    } else {
                        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang >> 1);
                    }
                    if (j == 2 && (sp138 == 7 || (sp138 == 8 && func_80712628() != 0 && *(s8 *)D_807505CC == 0))) {
                        j++;
                        if (list && list) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    }
                    i = j;
                    if (D_807FC828) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (!D_807FC868) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (j == 1 && *(s8 *)D_807505CC != 0) {
                        i = 4;
                    }
                    if (!dl) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (D_807FCC4B && D_807FCC4B) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (i == 2 && *(s8 *)D_807505CC != 0) {
                        i = 5;
                    }
                    if (D_8076A0AB && D_8076A0AB) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    dl = hudDrawScaledText(dl, 0x280, y, 0.7f, D_807FC7E0[i]);
                    j++;
                    y += 0x44;
                    if (D_80750538 == D_807FCC4B) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                } while (j < 3);
            } else {
                gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, ang);
                dl = hudDrawScaledText(dl, 0x280, 0x198, 0.7f, D_807FC7E0[7]);
                _sprintf(buf, "q %s", D_807FC7E0[16]);
                dl = hudDrawScaledText(dl, 0x280, 0x1E8, 1.0f, buf);
                _sprintf(buf, "b %s", D_807FC7E0[17]);
                dl = hudDrawScaledText(dl, 0x280, 0x238, 1.0f, buf);
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
                        if (dl) {} // FAKE: keeps dl (param) above hoisted D_807FC840 for s7
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
                            if (((s8 *)&D_80750530)[j] != 0) {
                                D_807FC890[j + i * 5] = (f32)((f64)D_807FC890[j + i * 5] * 0.75);
                            }
                            j++;
                            ang += 0x333;
                        } while (j < 5);
                        gDPPipeSync(dl++);
                    }
                    dl = hudDrawItemLabel(dl, (HudEntry *)hud, i);
                }
                j = hud->unk8[i];
                if (j != 8) {
                    f32 fa;
                    f32 fb;
                    f32 fc;
                    f32 fd;
                    fa = hud->unk4;
                    if (!list) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    fb = hud->unk0;
                    if (D_807FCC4B) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    fc = 780.0f;
                    if (fa < fb) {
                        fd = fb;
                    } else {
                        fd = fa;
                    }
                    if (off == 0) {
                        fc = fc + fd * 400.0;
                        if (!D_807FC950) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    }
                    if (D_807FC992 && D_807FC992) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    dl = hudDrawCountPair(0x2A8, (s32)((f32)off + fc), *(s16 *)((u8 *)D_807FC992 + hud->unk14 * 0x5E + D_80750560[j] * 2), 5, dl, 0, 0.8f);
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
                    dl = hudDrawItemLabel(dl, (HudEntry *)hud, i);
                }
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
                    if (D_807505CC || D_807FCC4C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
                    dl = hudDrawCountPair(0x2B0, (s32)((f32)off + fc), t0, 0x19, dl, 0, 0.8f);
                }
                if (ret == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            break;
        case 3:
            dl = hudDrawScaledText(hudDrawScaledText(dl, 0x280, 0x74, 0.5f, D_807FC7E0[D_807FC818[D_807FC80C] + 18]), 0x280, 0x3C, 0.65, D_807FC7E0[6]);
            fa = hud->unk4;
            if (!D_807FCC4C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
            dl = hudDrawCountPair(0x280, 0x33C, (&D_807FC828)[D_807FC818[D_807FC80C]], D_8075056C[D_807FC818[D_807FC80C]], dl, 1, fc);
            break;
    }
    dl->words.w0 = 0xDF000000;
    dl->words.w1 = 0;
    if (list) {}
    return ret;
}
